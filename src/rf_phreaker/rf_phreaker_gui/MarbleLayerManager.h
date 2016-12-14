#pragma once
#include <mutex>
#include <future>
#include <vector>
#include <atomic>
#include <QString>
#include "marble/MarbleMap.h"
#include "marble/MarbleModel.h"
#include "marble/geodata/data/GeoDataCoordinates.h"
#include "marble/geodata/data/GeoDataAccuracy.h"
#include "marble/geodata/data/GeoDataStyle.h"
#include "marble/geodata/data/GeoDataStyleMap.h"
#include "marble/geodata/data/GeoDataMultiTrack.h"
#include "marble/geodata/data/GeoDataTrack.h"
#include "rf_phreaker/common/singleton.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleProxyModel.h"
#include "rf_phreaker/rf_phreaker_gui/RpPositionProviderPlugin.h"

class MarbleLayerManager;
typedef rf_phreaker::singleton<MarbleLayerManager> MarbleLayers;

class MarbleLayerManager : public QObject {
	Q_OBJECT

public:
	MarbleLayerManager(QObject *parent = 0);

	~MarbleLayerManager();

	void init();

	void openPreviousLayers();

	void storePreviousLayers(/*MarbleProxyModel &placemarkModel*/);

	Marble::MarbleModel* model();

signals:
	void updateMapTheme();

public slots:
	void updateRecordingTrack(const Marble::GeoDataCoordinates& position,
		const Marble::GeoDataAccuracy& accuracy);

	void deviceStatusChanged();

	void updatePositionStatus();

	bool checkPositionStatus();

	void addLayer(const QString &filename);

	void addPreviousTrack(Marble::GeoDataPlacemark *placemark);

private:
	void GeoObjectAdded(Marble::GeoDataObject *object);

	void configureStyles();

	void addMapFile(const QString &filename);

	void addRpf(const QString &filename);

	void createRecordingTrack();

	void transferRecordingTrack();

	void addRecordingTrackPoint(const Marble::GeoDataCoordinates &position);

	std::unique_ptr<Marble::GeoDataPlacemark> createPlacemarkMultiTrack(const QString &filename);

	Marble::MarbleModel model_;

	RpPositionProviderPlugin rpPositionProviderPlugin_;

	Marble::GeoDataDocument *rpDoc_;

	Marble::GeoDataDocument *positionDoc_;

	Marble::GeoDataDocument *recordingDoc_;

	Marble::GeoDataPlacemark *recordingPlacemark_;

	Marble::GeoDataMultiTrack *multiTrack_;

	Marble::GeoDataTrack  *currentTrack_;

	Marble::GeoDataCoordinates previousPosition_;

	Marble::PositionProviderStatus previousStatus_;

	std::recursive_mutex mutex_;

	std::atomic_bool init_;

	std::atomic_bool collecting_;

	double minDistance_;

	std::vector<std::future<void>> addLayerFutures_;
};
