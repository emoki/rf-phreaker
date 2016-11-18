#pragma once
#ifndef MARBLEMANAGER_H
#define MARBLEMANAGER_H

#include <memory>
#include <QObject>
#include <QMutex>
#include "marble/declarative/MarbleQuickItem.h"
#include "marble/declarative/Coordinate.h"
#include "marble/declarative/Placemark.h"
#include "marble/MarbleGlobal.h"
#include "marble/MarbleMap.h"
#include "marble/MarbleWidget.h"
#include "marble/MarbleModel.h"
#include "marble/MarbleDebug.h"
#include "marble/DownloadRegion.h"
#include "marble/ViewportParams.h"
#include "marble/HttpDownloadManager.h"
#include "marble/layers/TextureLayer.h"
#include "marble/TileCoordsPyramid.h"
#include "marble/FileManager.h"
#include "marble/MarbleInputHandler.h"
#include "marble/PluginManager.h"
#include "marble/PositionTracking.h"
#include "marble/MarblePlacemarkModel.h"
#include "marble/MarbleDirs.h"
#include "marble/GeoDataTreeModel.h"
#include "marble/TreeViewDecoratorModel.h"
#include "marble/routing/RouteRequest.h"
#include "marble/routing/RoutingManager.h"
#include "marble/kdescendantsproxymodel.h"
#include "marble/geodata/data/GeoDataPlacemark.h"
#include "marble/geodata/data/GeoDataDocument.h"
#include "marble/geodata/data/GeoDataStyle.h"
#include "marble/geodata/data/GeoDataStyleMap.h"
#include "marble/geodata/data/GeoDataMultiTrack.h"
#include "marble/geodata/data/GeoDataTrack.h"
#include "rf_phreaker/protobuf_specific/rf_phreaker_serialization.h"
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "rf_phreaker/protobuf_specific/io.h"
#include "rf_phreaker/rf_phreaker_gui/RpPositionProviderPlugin.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleProxyModel.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleHelper.h"
#include "rf_phreaker/rf_phreaker_gui/Settings.h"

class MarbleManager : public Marble::MarbleQuickItem {
	Q_OBJECT
	Q_PROPERTY(QAbstractItemModel* treeViewModel READ treeViewModel NOTIFY treeViewModelChanged)
	Q_PROPERTY(QAbstractItemModel* proxyTreeViewModel READ proxyTreeViewModel NOTIFY proxyTreeViewModelChanged)
	Q_PROPERTY(MarbleProxyModel* placemarkModel READ placemarkModel NOTIFY placemarkModelChanged)
	Q_PROPERTY(double downloadProgess READ downloadProgess NOTIFY downloadProgressChanged)
	Q_PROPERTY(bool iscurrentPositionGloballyVisible READ iscurrentPositionGloballyVisible NOTIFY isCurrentPositionGloballyVisibleChanged)
	Q_PROPERTY(bool isTrackingEnabled READ isTrackingEnabled WRITE setIsTrackingEnabled NOTIFY isTrackingEnabledChanged)

signals:
	void downloadProgressChanged();
	void treeViewModelChanged();
	void proxyTreeViewModelChanged();
	void placemarkModelChanged();
	void isCurrentPositionGloballyVisibleChanged();
	void isTrackingEnabledChanged();

public:
	MarbleManager(QQuickItem *parent = 0)
		: Marble::MarbleQuickItem(parent)
		, numDownloadJobs_(0)
		, currentDownloadJobValue_(0)
		, rpDoc_(nullptr) {
		loadSettings();
		init();
	}

	~MarbleManager() {
		writeSettings();
		storePreviousLayers();
	}

	Q_INVOKABLE QPointF currentPositionScreenCoordinates() {
		qreal x;
		qreal y;
		Marble::GeoDataCoordinates coord(currentPosition()->longitude(), currentPosition()->latitude(), 0, Marble::GeoDataCoordinates::Degree);
		map()->viewport()->screenCoordinates(coord, x, y);
		return QPointF(x,y);
	}

	Q_INVOKABLE void downloadMapRegion() {
		numDownloadJobs_ = 0;
		currentDownloadJobValue_ = 0;

		auto &geoLatLonBox = map()->viewport()->viewLatLonAltBox();
		Marble::DownloadRegion region;
		region.setTileLevelRange(1, 19);
		region.setMarbleModel(map()->model());
		region.setVisibleTileLevel(map()->textureLayer()->tileZoomLevel());
		auto tilesCoordPyramid = region.region(map()->textureLayer(), geoLatLonBox);
		map()->downloadRegion(tilesCoordPyramid);
	}

	Q_INVOKABLE void setCurrentTrackVisible(bool beVisible) {
		auto positionTracking = map()->model()->positionTracking();
		positionTracking->setTrackVisible(beVisible);
	}

	Q_INVOKABLE void setPlacemarkGloballyVisible(int placemarkIndex, bool beVisible) {
		using namespace Marble;
		auto placemark = MarbleHelper::toPlacemark(placemarkModel_.data(placemarkModel_.index(placemarkIndex, 0), MarbleProxyModel::PlacemarkObjectPointerRole));
		if(placemark != nullptr) {
			placemark->setVisible(beVisible);
			if(placemark->name() == "Current Position") {
				emit isCurrentPositionGloballyVisibleChanged();
			}
			map()->model()->treeModel()->updateFeature(placemark);
		}
	}

	Q_INVOKABLE void centerOnPlacemark(int placemarkIndex) {
		using namespace Marble;
		using namespace Marble;
		auto placemark = MarbleHelper::toPlacemark(placemarkModel_.data(placemarkModel_.index(placemarkIndex, 0), MarbleProxyModel::PlacemarkObjectPointerRole));
		if(placemark != nullptr) {
			placemark->setVisible(true);
			map()->model()->treeModel()->updateFeature(placemark);
			centerOn(*placemark, true);
		}
	}

	Q_INVOKABLE void removePlacemark(int placemarkIndex) {
		using namespace Marble;
		auto placemark = MarbleHelper::toPlacemark(placemarkModel_.data(placemarkModel_.index(placemarkIndex, 0), MarbleProxyModel::PlacemarkObjectPointerRole));
		if(placemark != nullptr ) {
			// Cannot delete current track or current position!
			if(!isPositionTrackingRelated(placemark)) {
				map()->model()->treeModel()->removeFeature(placemark);
			}
		}
	}

	Q_INVOKABLE void saveCurrentTrack() {
		auto positionTracking = map()->model()->positionTracking();
		positionTracking->saveTrack("currentTrack.txt");
	}

	Q_INVOKABLE void beginSimulation() {
		//using namespace Marble;
		//// Access the shared route request (start, destination and parameters)
		//RoutingManager* manager = map()->model()->routingManager();
		//RouteRequest* request = manager->routeRequest();

		//// Use default routing settings for cars
		//request->setRoutingProfile(manager->defaultProfile(RoutingProfile::Motorcar));

		//// Set start and destination
		//// nyc to atl
		//request->append(GeoDataCoordinates(-73.994503, 40.717055, 0.0, GeoDataCoordinates::Degree));
		//request->append(GeoDataCoordinates(-84.325821, 33.835247, 0.0, GeoDataCoordinates::Degree));
		//// rapid city to sioux falls
		////request->append(GeoDataCoordinates(-103.096297,44.117466, 0.0, GeoDataCoordinates::Degree));
		////request->append(GeoDataCoordinates(-96.872103, 43.608914, 0.0, GeoDataCoordinates::Degree));

		//// Calculate the route
		//manager->retrieveRoute();
		//centerOn(request->at(0));

		//Marble::PositionProviderPlugin* plugin = nullptr;
		//auto list = map()->model()->pluginManager()->positionProviderPlugins();
		//for(auto &i : list) {
		//	if(i->nameId() == "RouteSimulationPositionProviderPlugin")
		//		plugin = i->newInstance();
		//}
		//map()->model()->positionTracking()->setPositionProviderPlugin(plugin);
	}

	Q_INVOKABLE void addRpf(QString filename) {
		// Can reduce number of measurements by using a distance calculation.
		// Do if neccessary.

		// When filename comes from QML it as a URL, however when we store the filename
		// it is native therefore only use tmp if it is valid, otherwise use native.
		QUrl url(filename);
		auto tmp = url.toLocalFile();
		if(!tmp.isEmpty())
			filename = tmp;
		qDebug() << "Converting RPF file. " << filename << ".";
		QFile f(filename);
		if(!f.open(QIODevice::ReadOnly | QIODevice::Unbuffered)) {
			qDebug() << "Failed to open RPF file. " << f.errorString();
		}
		else {
			if(rpDoc_ == nullptr)
				createTrackingDocument();

			auto name = filename;
			auto multiTrack = std::make_unique<Marble::GeoDataMultiTrack>();
			multiTrack->setId("multitrack_" + name);
			auto track = std::make_unique<Marble::GeoDataTrack>();
			auto input_file = std::make_unique<google::protobuf::io::FileInputStream>(f.handle());
			rf_phreaker::protobuf::update_pb message;
			auto &proto = message.protobuf();
			rf_phreaker::gps gps;
			bool previously_had_lock = true; // Inital condition = true.
			while(rf_phreaker::protobuf::read_delimited_from(input_file.get(), &proto)) {
				if(proto.update_case() == rf_phreaker::protobuf::rp_update::UpdateCase::kGps) {
					gps = message.get_gps();
					if(gps.lock_) {
						if(!previously_had_lock) {
							if(track->size())
								multiTrack->append(track.get());
							track.release();
							track = std::make_unique<Marble::GeoDataTrack>();
							previously_had_lock = true;
						}
						track->addPoint(QDateTime::fromTime_t(gps.coordinated_universal_time_),
							Marble::GeoDataCoordinates(gps.longitude_, gps.latitude_, gps.altitude_, Marble::GeoDataCoordinates::Degree));
					}
					else {
						previously_had_lock = false;
					}
					proto.Clear();
				}
			}
			// Not sure if we can alter track after it's added to multitrack so we wait to add a track until it's finished.
			// This means the last track is added here (if there are points within).
			if(track->size()) {
				multiTrack->append(track.get());
				track.release();
			}
			auto placemark = std::make_unique<Marble::GeoDataPlacemark>();
			placemark->setName(name);
			placemark->setGeometry(multiTrack.get());
			placemark->setVisible(true);
			multiTrack.release();
			map()->model()->treeModel()->removeDocument(rpDoc_);
			rpDoc_->append(placemark.get());
			placemark->setStyleUrl("#ptrack");
			map()->model()->treeModel()->addDocument(rpDoc_);
			placemark.release();
		}
	}

	double downloadProgess() {
		if(numDownloadJobs_ == 0)
			return 0;
		else
			return std::min(1.0, currentDownloadJobValue_ / numDownloadJobs_);
	}

	bool isPositionTrackingRelated(Marble::GeoDataPlacemark* p) {
		return p->name() == "Current Position" || p->name() == "Current Track";
	}

	QAbstractItemModel* treeViewModel() { return map()->model()->treeModel(); }

	QAbstractItemModel* proxyTreeViewModel() { return &proxyTreeViewModel_; }

	MarbleProxyModel* placemarkModel() { return &placemarkModel_; }

	bool iscurrentPositionGloballyVisible() const {
		auto placemark = currentPositionGeoDataPlacemark();
		if(placemark != nullptr) {
			return placemark->isGloballyVisible();
		}
		return false;
	}

	bool isTrackingEnabled() const { return isTrackingEnabled_; }

	void setIsTrackingEnabled(bool t) { isTrackingEnabled_ = t; emit isTrackingEnabledChanged(); }

	Marble::GeoDataPlacemark* currentPositionGeoDataPlacemark() const {
		auto placemark = MarbleHelper::toPlacemark(placemarkModel_.data(placemarkModel_.index(0, 0), MarbleProxyModel::PlacemarkObjectPointerRole));
		if(placemark != nullptr) 
			Q_ASSERT(placemark->name() == QObject::tr("Current Position"));
		return placemark;
	}

public slots:
	void handleDownloadProgess(int active, int queued) {
		auto tmp = std::max(numDownloadJobs_, (double)(active + queued));
		if(numDownloadJobs_ != tmp) {
			numDownloadJobs_ = tmp;
			emit downloadProgressChanged();
		}
	}

	void handleDownloadJobRemoved() {
		++currentDownloadJobValue_;
		emit downloadProgressChanged();
	}

private:
	void init() {
		using namespace Marble;
		//MarbleDebug::setEnabled(true);

		// Unlimited persistent cache!
		map()->model()->setPersistentTileCacheLimit(0);

		// Connect to give user input on downloading tiles.
		QObject::connect(map()->model()->downloadManager(), &HttpDownloadManager::progressChanged,
			this, &MarbleManager::handleDownloadProgess);
		QObject::connect(map()->model()->downloadManager(), &HttpDownloadManager::jobRemoved,
			this, &MarbleManager::handleDownloadJobRemoved);

		// Add our position plugin which gives Marble our location.
		auto pluginManager = map()->model()->pluginManager();
		pluginManager->addPositionProviderPlugin(&rpPositionProviderPlugin_);


		placemarkModel_.setSourceModel(map()->model()->placemarkModel());
		placemarkModelChanged();
		auto tree = map()->model()->treeModel();
		auto tmp = tree->data(tree->index(0, 0), MarbleProxyModel::PlacemarkObjectPointerRole).value<GeoDataObject*>();
		positionDoc_ = static_cast<GeoDataDocument*>(tmp);
		Q_ASSERT(positionDoc_->name() == "Position Tracking");

		// Connect for isTrackingEnabled - Stops us from tracking current location when user interacts with map.
		QObject::connect(inputHandler(), &MarbleInputHandler::mouseEventDoubleClickOrWheelSeen,
			this, &MarbleManager::mouseEventDoubleClickOrWheelSeen);

		// Open rf_phreaker.kml which contains our styles.
		// We wait for document to finish opening (GeoObjectAdded).
		// Once open we config previous layers and positiontracking.
		QObject::connect(map()->model()->treeModel(), &GeoDataTreeModel::added,
			this, &MarbleManager::GeoObjectAdded);
		QFileInfo rpFile(MarbleDirs::path("rf_phreaker/rf_phreaker.kml"));
		//if(!rpFile.exists())
		//	 Signal error
		map()->model()->addGeoDataFile(rpFile.absoluteFilePath());
	}

	void mouseEventDoubleClickOrWheelSeen() {
		// This means the user has clicked on the map stopping the tracking from occurring.
		setIsTrackingEnabled(false);
	}

	void GeoObjectAdded(Marble::GeoDataObject *object) {
		if(rpDoc_ == nullptr && object->nodeType() == Marble::GeoDataTypes::GeoDataDocumentType) {
			auto doc = static_cast<Marble::GeoDataDocument*>(object);
			if(doc->name() == "RfPhreaker") {
				rpDoc_ = doc;
				configPositionTracking();
				openPreviousLayers();
			}
		}
	}

	void configPositionTracking() {
		// Disable PositionTracking current position and use our own built in QML
		using namespace Marble;

		map()->model()->treeModel()->removeDocument(positionDoc_);
		auto styles = rpDoc_->styles();
		for(auto i : styles) {
			positionDoc_->addStyle(i);
		}
		auto stylemaps = rpDoc_->styleMaps();
		for(auto &i : stylemaps) {
			positionDoc_->addStyleMap(i);
		}

		auto feature = positionDoc_->child(0);
		if(feature != nullptr) {
			Q_ASSERT(feature->name() == QObject::tr("Current Position"));
			feature->setStyleUrl("#dpos");
			feature->setVisible(true);
			emit isCurrentPositionGloballyVisibleChanged();
		}
		feature = positionDoc_->child(1);
		if(feature != nullptr) {
			Q_ASSERT(feature->name() == QObject::tr("Current Track"));
			feature->setStyleUrl("#ctrack");
		}
		map()->model()->treeModel()->addDocument(positionDoc_);
	}

	void openPreviousLayers() {
		// Open any layers from previous instance.
		SettingsIO s;
		QStringList placemarkList = s.readMarbleLayers();
		for(auto &i : placemarkList)
			addRpf(i);
	}

	void storePreviousLayers() {
		QStringList placemarkList;
		for(auto i = 0; i < placemarkModel_.rowCount(); ++i) {
			auto placemark = MarbleHelper::toPlacemark(placemarkModel_.data(placemarkModel_.index(i, 0), MarbleProxyModel::PlacemarkObjectPointerRole));
			if(isPositionTrackingRelated(placemark))
				continue;
			placemarkList << placemark->name();
		}
		SettingsIO s;
		s.writeMarbleLayers(placemarkList);
	}

	void storeLastKnownCoordinate() {
		auto position = currentPositionGeoDataPlacemark();
		if(position != nullptr) {
			auto c = position->coordinate();
			SettingsIO sIO;
			if(c.isValid())
				sIO.writeLastKnownCoordinate(c);
		}
	}

	void createTrackingDocument() {
		if(rpDoc_ == nullptr) {
			auto doc = std::make_unique<Marble::GeoDataDocument>();
			doc->setName("rp_tracking_doc");
			doc->setDocumentRole(Marble::TrackingDocument);
			// Marble is managing the memory now.
			map()->model()->treeModel()->addDocument(doc.get());
			rpDoc_ = doc.get();
			doc.release();
		}
	}

	double currentDownloadJobValue_;
	double numDownloadJobs_;
	bool isTrackingEnabled_;
	RpPositionProviderPlugin rpPositionProviderPlugin_;
	Marble::KDescendantsProxyModel proxyTreeViewModel_;
	MarbleProxyModel placemarkModel_;
	Marble::GeoDataDocument *rpDoc_;
	Marble::GeoDataDocument *positionDoc_;
};


#endif // MARBLEMANAGER_H
