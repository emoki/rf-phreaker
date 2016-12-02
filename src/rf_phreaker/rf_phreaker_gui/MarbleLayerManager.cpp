#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include "marble/geodata/data/GeoDataPlacemark.h"
#include "marble/geodata/data/GeoDataDocument.h"
#include "marble/geodata/data/GeoDataStyle.h"
#include "marble/geodata/data/GeoDataStyleMap.h"
#include "marble/geodata/data/GeoDataMultiTrack.h"
#include "marble/geodata/data/GeoDataTrack.h"
#include "marble/GeoDataTreeModel.h"
#include "marble/MarbleDirs.h"
#include "marble/PluginManager.h"
#include "marble/MarbleModelPrimary.h"
#include "rf_phreaker/rf_phreaker_gui/Api.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleLayerManager.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleHelper.h"
#include "rf_phreaker/rf_phreaker_gui/Settings.h"
#include "rf_phreaker/protobuf_specific/rf_phreaker_serialization.h"
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "rf_phreaker/protobuf_specific/io.h"

using namespace Marble;

MarbleLayerManager::MarbleLayerManager(QObject *parent)
 : QObject(parent)
 , model_(this) 
 , rpDoc_(nullptr)
 , positionDoc_(nullptr)
 , recordingPlacemark_(nullptr)
 , multiTrack_(nullptr)
 , currentTrack_(nullptr) 
 , minDistance_(0) {
	init_ = false;
	collecting_ = false;
	rpPositionProviderPlugin_.initialize();
	MarbleModelPrimary::setMarbleModel(&model_);
	QObject::connect(&rpPositionProviderPlugin_, &RpPositionProviderPlugin::positionChanged, this, &MarbleLayerManager::updateRecordingTrack);
	QObject::connect(&rpPositionProviderPlugin_, &RpPositionProviderPlugin::statusChanged, this, &MarbleLayerManager::updatePositionStatus);
	QObject::connect(Api::instance(), &Api::deviceStatusChanged, this, &MarbleLayerManager::deviceStatusChanged);
	SettingsIO sio;
	Settings s;
	sio.readSettings(s);
	minDistance_ = s.rpf_track_min_distance_;
}

void MarbleLayerManager::init() {
	if(!init_) {
		std::lock_guard<std::recursive_mutex> lock(mutex_);
		if(!init_) {
			// Open rf_phreaker.kml which contains our styles.
			// We wait for document to finish opening (GeoObjectAdded).
			// Once open we config previous layers and positiontracking.
			QObject::connect(model_.treeModel(), &GeoDataTreeModel::added,
				this, &MarbleLayerManager::GeoObjectAdded);

			// Add the recording document before styles so that it will be there when we 
			// configure the doc styles
			recordingDoc_ = new GeoDataDocument();
			recordingDoc_->setDocumentRole(DocumentRole::TrackingDocument);
			model_.treeModel()->addDocument(recordingDoc_);

			QFileInfo rpFile(MarbleDirs::path("rf_phreaker/rf_phreaker.kml"));
			//if(!rpFile.exists())
			//	 Signal error
			model_.addGeoDataFile(rpFile.absoluteFilePath());

			// Add our position plugin which gives Marble our location.
			auto pluginManager = model_.pluginManager();
			pluginManager->addPositionProviderPlugin(&rpPositionProviderPlugin_);

			// Initialize positionDoc.
			auto tmp = model_.treeModel()->data(model_.treeModel()->index(0, 0), MarbleProxyModel::PlacemarkObjectPointerRole).value<GeoDataObject*>();
			positionDoc_ = static_cast<GeoDataDocument*>(tmp);
			Q_ASSERT(positionDoc_->name() == "Position Tracking");

			init_ = true;
		}
	}
}

MarbleLayerManager::~MarbleLayerManager() {
	if(init_)
		storePreviousLayers();
}

void MarbleLayerManager::GeoObjectAdded(Marble::GeoDataObject *object) {
	if(rpDoc_ == nullptr && object->nodeType() == Marble::GeoDataTypes::GeoDataDocumentType) {
		auto doc = static_cast<Marble::GeoDataDocument*>(object);
		if(doc->name() == "RfPhreaker") {
			rpDoc_ = doc;
			configureStyles();
			openPreviousLayers();
		}
	}
}

void MarbleLayerManager::configureStyles() {
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	// Disable PositionTracking current position and use our own built in QML
	using namespace Marble;

	model_.treeModel()->removeDocument(positionDoc_);
	auto styles = rpDoc_->styles();
	for(auto i : styles) {
		positionDoc_->addStyle(i);
		recordingDoc_->addStyle(i);
	}
	auto stylemaps = rpDoc_->styleMaps();
	for(auto &i : stylemaps) {
		positionDoc_->addStyleMap(i);
		recordingDoc_->addStyleMap(i);
	}

	auto feature = positionDoc_->child(0);
	if(feature != nullptr) {
		Q_ASSERT(feature->name() == QObject::tr("Current Position"));
		feature->setStyleUrl("#dpos");
		feature->setVisible(true);
	}
	feature = positionDoc_->child(1);
	if(feature != nullptr) {
		Q_ASSERT(feature->name() == QObject::tr("Current Track"));
		feature->setStyleUrl("#ctrack");
	}
	model_.treeModel()->addDocument(positionDoc_);
}

void MarbleLayerManager::openPreviousLayers() {
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	// Open any layers from previous instance.
	SettingsIO s;
	QStringList placemarkList = s.readMarbleLayers();
	for(auto &i : placemarkList)
		addLayer(i);
}

void MarbleLayerManager::storePreviousLayers() {
	std::lock_guard<std::recursive_mutex> lock(mutex_);
	QStringList placemarkList;
	for(auto i = 0; i < rpDoc_->size(); ++i) {
		auto placemark = static_cast<GeoDataPlacemark*>(rpDoc_->child(i));
		if(placemark == nullptr)
			continue;
		placemarkList << placemark->name();
	}
	SettingsIO s;
	s.writeMarbleLayers(placemarkList);
}

void MarbleLayerManager::addLayer(const QString &filename) {
	// When filename comes from QML it as a URL, however when we store the filename
	// it is native therefore only use tmp if it is valid, otherwise use native.
	auto tmp_filename = filename;
	QUrl url(tmp_filename);
	auto tmp = url.toLocalFile();
	if(!tmp.isEmpty())
		tmp_filename = tmp;

	QFileInfo info(tmp_filename);

	if(info.suffix() == "rpf")
		addRpf(tmp_filename);
	else // See if Marble handles the file...
		addMapFile(tmp_filename);

	// Update saved layers.
	storePreviousLayers();
}

void MarbleLayerManager::addMapFile(const QString &filename) {
	std::lock_guard<std::recursive_mutex> lock(mutex_);

	qDebug() << "Adding file. " << filename << ".";
	model_.addGeoDataFile(filename);
}

void MarbleLayerManager::addRpf(const QString &filename) {
	std::lock_guard<std::recursive_mutex> lock(mutex_);

	qDebug() << "Converting RPF file. " << filename << ".";
	QFile f(filename);
	if(!f.open(QIODevice::ReadOnly | QIODevice::Unbuffered)) {
		qDebug() << "Failed to open RPF file. " << f.errorString();
	}
	else {
		auto multiTrack = std::make_unique<Marble::GeoDataMultiTrack>();
		multiTrack->setId("multitrack_" + filename);
		auto track = std::make_unique<Marble::GeoDataTrack>();
		auto input_file = std::make_unique<google::protobuf::io::FileInputStream>(f.handle());
		rf_phreaker::protobuf::update_pb message;
		auto &proto = message.protobuf();
		rf_phreaker::gps previousGps, gps;
		previousGps.coordinated_universal_time_ = -1;
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
						previousGps.coordinated_universal_time_ = -1;
					}
					bool addPoint = false;
					if(previousGps.coordinated_universal_time_ == -1) {
						addPoint = true;
					}
					else {
						auto distance = MarbleHelper::calculateDistanceMeters(previousGps.longitude_, previousGps.latitude_, gps.longitude_, gps.latitude_, model_);
						if(distance > minDistance_)
							addPoint = true;
					}
					if(addPoint) {
						track->addPoint(QDateTime::fromTime_t(gps.coordinated_universal_time_),
							Marble::GeoDataCoordinates(gps.longitude_, gps.latitude_, gps.altitude_, Marble::GeoDataCoordinates::Degree));
						previousGps = gps;
					}
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
		placemark->setName(filename);
		placemark->setGeometry(multiTrack.get());
		placemark->setVisible(true);
		multiTrack.release();
	
		model_.treeModel()->removeDocument(rpDoc_);
		rpDoc_->append(placemark.get());
		// Style needs to be set after placemark has been added to the document.
		placemark->setStyleUrl("#ptrack");
		model_.treeModel()->addDocument(rpDoc_);
		Api::instance()->addMessage(placemark->name() + " layer added.");
		placemark.release();
	}
}

Marble::MarbleModel* MarbleLayerManager::model() {
	return &model_;
}

void MarbleLayerManager::updateRecordingTrack(const GeoDataCoordinates& position,
	const GeoDataAccuracy& accuracy) {
	if(!collecting_)
		return;

	if(checkPositionStatus()) {
		if(!previousPosition_.isValid()) {
			addRecordingTrackPoint(position);
		}
		else if(previousPosition_.isValid() && position.isValid()) {
			auto distance = MarbleHelper::calculateDistanceMeters(previousPosition_, position, model_);
			if(distance > minDistance_) {
				addRecordingTrackPoint(position);
			}
		}
	}
}

void MarbleLayerManager::addRecordingTrackPoint(const GeoDataCoordinates &position) {
	model_.treeModel()->removeFeature(recordingPlacemark_);
	currentTrack_->addPoint(rpPositionProviderPlugin_.timestamp(), position);
	model_.treeModel()->addFeature(recordingDoc_, recordingPlacemark_);
	previousPosition_ = position;
}

void MarbleLayerManager::deviceStatusChanged() {
	if(Api::instance()->deviceStatus() == ApiTypes::RECORDING) {
		if(!collecting_)
			createRecordingTrack();
		collecting_ = true;
	}
	else {
		if(collecting_)
			transferRecordingTrack();
		collecting_ = false;
	}
}

bool MarbleLayerManager::checkPositionStatus() {
	auto status = rpPositionProviderPlugin_.status();

	if(previousStatus_ != PositionProviderStatus::PositionProviderStatusAvailable &&
		status == PositionProviderStatus::PositionProviderStatusAvailable) {
		currentTrack_ = new Marble::GeoDataTrack();
		model_.treeModel()->removeFeature(recordingPlacemark_);
		multiTrack_->append(currentTrack_);
		model_.treeModel()->addFeature(recordingDoc_, recordingPlacemark_);
	}
	previousStatus_ = status;
	return status == PositionProviderStatus::PositionProviderStatusAvailable;
}

void MarbleLayerManager::updatePositionStatus() {
	// We only do this because updateRecordTrack is not called when there is no valid GPS.
	auto status = rpPositionProviderPlugin_.status();
	if(status != PositionProviderStatus::PositionProviderStatusAvailable)
		previousStatus_ = status;
}

void MarbleLayerManager::createRecordingTrack() {
	auto filename = Api::instance()->collectionFilename();

	multiTrack_ = new Marble::GeoDataMultiTrack();
	multiTrack_->setId("multitrack_" + filename);

	previousStatus_ = PositionProviderStatus::PositionProviderStatusUnavailable;
	previousPosition_ = GeoDataCoordinates();
	filename.insert(filename.lastIndexOf("/") + 1, "recording ");
	auto str = filename.toStdString();
	recordingPlacemark_ = new Marble::GeoDataPlacemark();
	recordingPlacemark_->setName(filename);
	recordingPlacemark_->setGeometry(multiTrack_);

	model_.treeModel()->removeDocument(recordingDoc_);
	recordingDoc_->append(recordingPlacemark_);
	recordingPlacemark_->setStyleUrl("#rtrack");
	model_.treeModel()->addDocument(recordingDoc_);

	// Remove/Add rpDoc so that the imported layers will be below position and recording
	// docs.
	model_.treeModel()->removeDocument(rpDoc_);
	model_.treeModel()->addDocument(rpDoc_);
}

void MarbleLayerManager::transferRecordingTrack() {
	auto filename = recordingPlacemark_->name().remove("recording ");
	model_.treeModel()->removeDocument(recordingDoc_);
	if(recordingDoc_->size())
		recordingDoc_->remove(0);
	model_.treeModel()->addDocument(recordingDoc_);
	recordingPlacemark_ = nullptr;
	multiTrack_ = nullptr;
	currentTrack_ = nullptr;
	addRpf(filename);
}