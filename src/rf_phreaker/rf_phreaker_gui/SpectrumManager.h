#pragma once
#include <unordered_map>
#include <QObject>
#include <QtCharts/QXYSeries>
#include <QtCharts/QLineSeries>
#include <QtDataVisualization/QSurface3DSeries>
#include "rf_phreaker/rf_phreaker_gui/FreqLimits.h"
#include "rf_phreaker/rf_phreaker_gui/SpectrumModel.h"
#include "rf_phreaker/rf_phreaker_gui/Spectrum3d.h"


class SpectrumManager : public QObject {
	Q_OBJECT
	Q_PROPERTY(int numItems MEMBER numItems_ NOTIFY numItemsChanged)
	Q_PROPERTY(int capacity READ capacity NOTIFY capacityChanged)
	Q_PROPERTY(int maxDataLimit READ maxDataLimit NOTIFY maxDataLimitChanged)
	Q_PROPERTY(FreqLimits* freqLimits READ freqLimits NOTIFY freqLimitsChanged)
	Q_PROPERTY(bool isDisabled READ isDisabled NOTIFY isDisabledChanged)

signals:
	void numItemsChanged(int numItems);
	void capacityChanged(int capacity);
	void maxDataLimitChanged(int limit);
	void isDisabledChanged(int isDisabled);
	void freqLimitsChanged();
	void aboutToReset();
	void finishedReset();

public:
	SpectrumManager(QObject *parent = 0)
		: QObject(parent)
		, numItems_(0)
		, capacity_(30)
		, isDisabled_(false)
		, maxDataLimit_(100000) {}

	Q_INVOKABLE QtCharts::QLineSeries* createLineSeries(int index) {
		if(index >= numItems_)
			return nullptr;
		QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
		series->setName(std::to_string(index).c_str());
		series->setUseOpenGL(true);
		return series;
	}

	Q_INVOKABLE QtDataVisualization::QSurface3DSeries* createSurfaceSeries(int index) {
		if(index >= numItems_)
			return nullptr;
		QtDataVisualization::QSurface3DSeries *series = new QtDataVisualization::QSurface3DSeries();
		series->setDrawMode(QtDataVisualization::QSurface3DSeries::DrawSurface);
		series->setMeshSmooth(false);
		series->setFlatShadingEnabled(false);
		return series;
	}

	Q_INVOKABLE void updateLineSeries(QtCharts::QAbstractSeries *series, int index) {
		auto model = models_[identiferLookup_[index]];
		if(model && series) {
			model->updateSeries((QtCharts::QXYSeries*)series);
		}
	}

	Q_INVOKABLE void updateSurfaceSeries(QtDataVisualization::QSurface3DSeries *series, int index) {
		auto model3d = models3d_[identiferLookup_[index]];
		if(model3d && series) {
			model3d->updateSeries(series);
			if(model3d->isDisabled()) {
				setIsDisabled(true);
			}
			else
				setIsDisabled(false);
		}
	}

	void update(rf_phreaker::power_spectrum_data &&spec) {
		auto &model = models_[spec.params_.identifier_];
		auto &model3d = models3d_[spec.params_.identifier_];
		if(!model) {
			model = std::make_shared<SpectrumModel>();
			model3d = std::make_shared<Spectrum3d>();
			identiferLookup_.insert({numItems_++, spec.params_.identifier_});
			emit numItemsChanged(numItems_);
		}

		if(model->isNewCollectionRound(spec))
			model3d->updateStorage(model->internalModel());

		model->update(std::move(spec));
	}

	void clear() {
		emit aboutToReset();
		freqLimits_.clear();
		identiferLookup_.clear();
		models_.clear();
		models3d_.clear();
		numItems_ = 0;
		emit numItemsChanged(numItems_);
		emit finishedReset();
	}

	void setCapacity(int cap) {
		if(cap != capacity_ && capacity_ > 0) {
			capacity_ = cap;
			for(auto &i : models3d_)
				i.second->setCapacity(capacity_);
			emit capacityChanged(capacity_);
		}
	}
	int capacity() { return capacity_; }
	int maxDataLimit() { return maxDataLimit_; }
	void setMaxDataLimit(int dataLimit) {
		if(maxDataLimit_ != dataLimit) {
			maxDataLimit_ = dataLimit;
			for(auto &i : models3d_)
				i.second->setMaxDataLimit(maxDataLimit_);
			emit maxDataLimitChanged(maxDataLimit_);
		}
	}
	bool isDisabled() { return isDisabled_; }
	void setIsDisabled(bool dis) {
		if(isDisabled_ != dis) {
			isDisabled_ = dis;
			emit isDisabledChanged(isDisabled_);
		}
	}

	int numItems() { return numItems_; }

	FreqLimits* freqLimits() { return &freqLimits_; }

private:
	typedef int64_t identifer_type;
	int numItems_;
	int capacity_;
	int maxDataLimit_;
	bool isDisabled_;
	FreqLimits freqLimits_;
	std::unordered_map<int, identifer_type> identiferLookup_;
	std::unordered_map<identifer_type, std::shared_ptr<SpectrumModel>> models_;
	std::unordered_map<identifer_type, std::shared_ptr<Spectrum3d>> models3d_;
};
