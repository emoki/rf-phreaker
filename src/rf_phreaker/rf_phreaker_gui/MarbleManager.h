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
#include "marble/TreeViewDecoratorModel.h"
#include "marble/routing/RouteRequest.h"
#include "marble/routing/RoutingManager.h"
#include "marble/kdescendantsproxymodel.h"
#include "marble/geodata/data/GeoDataPlacemark.h"
#include "marble/geodata/data/GeoDataDocument.h"
#include "rf_phreaker/protobuf_specific/rf_phreaker_serialization.h"
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "rf_phreaker/protobuf_specific/io.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleProxyModel.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleLayerManager.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleHelper.h"
#include "rf_phreaker/rf_phreaker_gui/Settings.h"
#include "rf_phreaker/rf_phreaker_gui/SettingsIO.h"
#include "rf_phreaker/rf_phreaker_gui/RpPositionProviderPlugin.h"

class MarbleManager : public Marble::MarbleQuickItem {
	Q_OBJECT
	Q_PROPERTY(QAbstractItemModel* treeViewModel READ treeViewModel NOTIFY treeViewModelChanged)
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
		, currentDownloadJobValue_(0) {
		loadSettings();
	}

	~MarbleManager() {
		writeSettings();
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
			if(!MarbleHelper::isPositionTrackingRelated(placemark)) {
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

	Q_INVOKABLE void addLayer(QString filename) {
		MarbleLayers::instance().addLayer(filename);
	}

	double downloadProgess() {
		if(numDownloadJobs_ == 0)
			return 0;
		else
			return std::min(1.0, currentDownloadJobValue_ / numDownloadJobs_);
	}

	QAbstractItemModel* treeViewModel() { return map()->model()->treeModel(); }

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

	void componentComplete() {
		using namespace Marble;
		MarbleQuickItem::componentComplete();

		//MarbleDebug::setEnabled(true);
		//map()->setShowFrameRate(true);
		//map()->setShowRuntimeTrace(true);
		//map()->setShowDebugBatchRender(true);

		MarbleLayers::instance().init();

		// Force update so that on consecutive uses of the model the map correctly
		// displays everything.
		forceMapThemeUpdate();  

		// Force update of position plugin.
		setPositionProvider("");
		setPositionProvider("RfPhreakerPositioning");

		// Unlimited persistent cache!
		map()->model()->setPersistentTileCacheLimit(0);

		// Connect to give user input on downloading tiles.
		QObject::connect(map()->model()->downloadManager(), &HttpDownloadManager::progressChanged,
			this, &MarbleManager::handleDownloadProgess);
		QObject::connect(map()->model()->downloadManager(), &HttpDownloadManager::jobRemoved,
			this, &MarbleManager::handleDownloadJobRemoved);

		placemarkModel_.setSourceModel(map()->model()->placemarkModel());
		placemarkModelChanged();

		// Connect for isTrackingEnabled - Stops us from tracking current location when user interacts with map.
		QObject::connect(inputHandler(), &MarbleInputHandler::mouseEventDoubleClickOrWheelSeen,
			this, &MarbleManager::mouseEventDoubleClickOrWheelSeen);
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

	void forceMapThemeUpdate() {
		map()->forceMapThemeUpdate();
	}

private:
	void mouseEventDoubleClickOrWheelSeen() {
		// This means the user has clicked on the map stopping the tracking from occurring.
		setIsTrackingEnabled(false);
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

	double currentDownloadJobValue_;
	double numDownloadJobs_;
	bool isTrackingEnabled_;
	MarbleProxyModel placemarkModel_;
};


#endif // MARBLEMANAGER_H
