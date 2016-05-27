#pragma once
#include <QObject>
#include <QList>
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/ProxyMeasurementModel.h"
#include "rf_phreaker/rf_phreaker_gui/CollectionInfoList.h"

class ModelGroup  : public QObject {
	Q_OBJECT
	Q_PROPERTY(FilterProxyMeasurementModel* highestCellPerChannelModel READ highestCellPerChannelModel NOTIFY highestCellPerChannelModelChanged)
	Q_PROPERTY(MeasurementModel* fullScanModel READ fullScanModel NOTIFY fullScanModelChanged)
	Q_PROPERTY(QList<QObject*> sweepModelList READ sweepModelList NOTIFY sweepModelListChanged)
	Q_PROPERTY(int lowestFreq READ lowestFreq NOTIFY lowestFreqChanged)
	Q_PROPERTY(int highestFreq READ highestFreq NOTIFY highestFreqChanged)

signals:
	void highestCellPerChannelModelChanged();
	void fullScanModelChanged();
	void sweepModelListChanged();
	void lowestFreqChanged();
	void highestFreqChanged();

public:
	ModelGroup(MeasurementModel &highestCellSourceModel, ApiTypes::OperatingBand lowBand,
			   ApiTypes::OperatingBand highBand, QObject *parent = 0)
		: QObject(parent)
		, lowestFreq_(lowestFreqDefault_)
		, highestFreq_(highestFreqDefault_)
		, lowBand_(lowBand)
		, highBand_(highBand) {
		setHighestCellSourceModel(highestCellSourceModel);
	}

	void setHighestCellSourceModel(MeasurementModel &highestCellSourceModel) {
		highestCellPerChannelModel_.setSourceModel(&highestCellSourceModel);
		highestCellPerChannelModel_.setLowBandFilter(lowBand_);
		highestCellPerChannelModel_.setHighBandFilter(highBand_);
		highestCellPerChannelModel_.setFilterRole(FilterProxyMeasurementModel::BandRangeFilter);
		emit highestCellPerChannelModelChanged();
	}

	void setSweepModels(const QMap<ApiTypes::OperatingBand, std::shared_ptr<MeasurementModel>> &sweepModels) {
		QMapIterator<ApiTypes::OperatingBand, std::shared_ptr<MeasurementModel>> i(sweepModels);
		while(i.hasNext()){
			i.next();
			if(i.key() >= lowBand_ && i.key() <= highBand_)
				sweepModelList_.append(i.value().get());
		}
		emit sweepModelListChanged();
	}

	void findFreqMinMax(const QList<CollectionInfo*> &scanList) {
		auto &list = scanList;
		int low = lowestFreqDefault_;
		int high = highestFreqDefault_;
		bool hasValidBand = false;
		foreach(const auto &ci, list) {
			auto band = ci->channelFreqLow()->band();
			if(band >= lowBand_ && band <= highBand_) {
				hasValidBand = true;
				low = ci->channelFreqLow()->freqMhz();
				high = ci->isSweep() ? ci->channelFreqHigh()->freqMhz() : ci->channelFreqLow()->freqMhz();
			}
		}
		if(!list.empty()) {
			foreach(const auto &ci, list) {
				auto band = ci->channelFreqLow()->band();
				if(band >= lowBand_ && band <= highBand_) {
					if(ci->channelFreqLow()->freqMhz() < low)
						low = ci->channelFreqLow()->freqMhz();
					if(ci->isSweep() && ci->channelFreqHigh()->freqMhz() > high)
						high = ci->channelFreqHigh()->freqMhz();
					else if(ci->channelFreqLow()->freqMhz() > high)
						high = ci->channelFreqLow()->freqMhz();
				}
			}
			// Add some additional clearance due to bandwidth of LTE channels.
			low -= 15;
			high += 15;
			// Make it look more consistent.
			low = low - (low % 20);
			high = high + (20 - high % 20);
		}
		if(low != lowestFreq_) {
			lowestFreq_ = low;
			emit lowestFreqChanged();
		}
		if(high != highestFreq_) {
			highestFreq_ = high;
			emit highestFreqChanged();
		}
	}

	void clear() {
		fullScanModel_.clear();
		sweepModelList_.clear();
	}

	FilterProxyMeasurementModel* highestCellPerChannelModel() { return &highestCellPerChannelModel_; }
	MeasurementModel* fullScanModel() { return &fullScanModel_; }
	QList<QObject*> sweepModelList() { return sweepModelList_; }
	int lowestFreq() { return lowestFreq_; }
	int highestFreq() { return highestFreq_; }

private:
	MeasurementModel fullScanModel_;
	FilterProxyMeasurementModel highestCellPerChannelModel_;
	QList<QObject*> sweepModelList_;
	int lowestFreq_;
	int highestFreq_;
	ApiTypes::OperatingBand lowBand_;
	ApiTypes::OperatingBand highBand_;
	static const int lowestFreqDefault_ = 700;
	static const int highestFreqDefault_ = 2600;
};
