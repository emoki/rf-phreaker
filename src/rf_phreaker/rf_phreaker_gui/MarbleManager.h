#pragma once
#ifndef MARBLEMANAGER_H
#define MARBLEMANAGER_H

#include <QObject>
#include <QMutex>
#include "marble/MarbleGlobal.h"
#include "marble/MarbleMap.h"
#include "marble/MarbleWidget.h"
#include "marble/MarbleModel.h"
#include "marble/DownloadRegion.h"
#include "marble/ViewportParams.h"
#include "marble/HttpDownloadManager.h"
#include "marble/layers/TextureLayer.h"
#include "marble/PluginManager.h"
#include "marble/PositionTracking.h"
#include "rf_phreaker/rf_phreaker_gui/RpPositionProviderPlugin.h"

class MarbleManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(Marble::MarbleMap* marbleMap READ marbleMap WRITE setMarbleMap NOTIFY marbleMapChanged)
	Q_PROPERTY(double downloadProgess READ downloadProgess NOTIFY downloadProgressChanged)
	Q_PROPERTY(bool isTracking READ isTracking WRITE setIsTracking NOTIFY isTrackingChanged)

signals:
	void marbleMapChanged();
	void downloadProgressChanged();
	void isTrackingChanged();

public:
	MarbleManager(QObject *parent = 0)
		: QObject(parent)
		, map_(nullptr)
		, numDownloadJobs_(0)
		, currentDownloadJobValue_(0)
		, isTracking_(true) {}

	static MarbleManager* instance() {
		static MarbleManager manager;
		return &manager;
	}

	Q_INVOKABLE void downloadMapRegion() {
		Q_ASSERT(map_ != nullptr);
		numDownloadJobs_ = 0;
		currentDownloadJobValue_ = 0;

		auto geoLatLonBox = map_->viewport()->viewLatLonAltBox();
		Marble::DownloadRegion region;
		region.setTileLevelRange(1, 19);
		region.setMarbleModel(map_->model());
		region.setVisibleTileLevel(map_->textureLayer()->tileZoomLevel());
		auto tilesCoordPyramid = region.region(map_->textureLayer(), geoLatLonBox);
		map_->downloadRegion(tilesCoordPyramid);
	}

	Marble::MarbleMap* marbleMap() { return map_; }
	void setMarbleMap(Marble::MarbleMap *map) {
		if(map_ != map) {
			map_ = map;
			init();
			emit marbleMapChanged();
		}
	}

	double downloadProgess() {
		if(numDownloadJobs_ == 0)
			return 0;
		else
			return std::min(1.0, currentDownloadJobValue_ / numDownloadJobs_);
	}

	bool isTracking() { return isTracking_; }
	void setIsTracking(bool isTracking) { isTracking_ = isTracking; }

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
		map_->model()->setPersistentTileCacheLimit(0);
		QObject::connect(map_->model()->downloadManager(), &Marble::HttpDownloadManager::progressChanged,
			this, &MarbleManager::handleDownloadProgess);
		QObject::connect(map_->model()->downloadManager(), &Marble::HttpDownloadManager::jobRemoved,
			this, &MarbleManager::handleDownloadJobRemoved);
		auto pluginManager = map_->model()->pluginManager();
		pluginManager->addPositionProviderPlugin(&rpPositionProviderPlugin_);
		auto positionTracking = map_->model()->positionTracking();
		positionTracking->setPositionProviderPlugin(rpPositionProviderPlugin_.newInstance());
		//positionTracking->setTrackVisible();
	}

	Marble::MarbleMap *map_;
	double currentDownloadJobValue_;
	double numDownloadJobs_;
	bool isTracking_;
	RpPositionProviderPlugin rpPositionProviderPlugin_;
};


#endif // MARBLEMANAGER_H
