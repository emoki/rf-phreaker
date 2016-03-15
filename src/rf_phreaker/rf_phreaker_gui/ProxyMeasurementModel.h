#pragma once
#include "boost/multi_index_container.hpp"
#include <QSortFilterProxyModel>
#include <QIdentityProxyModel>
#include <QDebug>
#include "rf_phreaker/rf_phreaker_gui/MeasurementModel.h"
#include "rf_phreaker/common/operating_band_range_specifier.h"

//namespace rf_phreaker { namespace gui {


class FilterProxyMeasurementModel : public QSortFilterProxyModel {
	Q_OBJECT
	Q_ENUMS(MeasFilterRole)
	Q_PROPERTY(QString stringFilter READ stringFilter WRITE setStringFilter)
	Q_PROPERTY(int expirationTimeFilter READ expirationTimeFilter WRITE setExpirationTimeFilter)
	Q_PROPERTY(ApiTypes::OperatingBand operatingBandFilter READ operatingBandFilter WRITE setOperatingBandFilter)
	Q_PROPERTY(double lowFreqFilter READ lowFreqFilter WRITE setLowFreqFilter NOTIFY lowFreqFilterChanged)
	Q_PROPERTY(double highFreqFilter READ highFreqFilter WRITE setHighFreqFilter NOTIFY  highFreqFilterChanged)
public:
	FilterProxyMeasurementModel(QObject *parent = 0)
		: QSortFilterProxyModel(parent)
		, expirationTimeFilter_(-1)
		, stringFilter_("-1")
		, operatingBandFilter_(ApiTypes::OPERATING_BAND_UNKNOWN)
		, lowFreqFilter_(-1)
		, highFreqFilter_(-1) {
		setFilterRole(NoFilterRole);
	}

	enum MeasFilterRole {
		NoFilterRole = MeasurementModel::MeasurementRoleSize,
		TimeFilter,
		FreqRangeFilter
	};

	Q_INVOKABLE void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) Q_DECL_OVERRIDE {
		QSortFilterProxyModel::sort(column, order);
	}

	Q_INVOKABLE int rowCount() {
		return QSortFilterProxyModel::rowCount();
	}

	bool filterAcceptsRow(int sourceRow, const QModelIndex & sourceParent) const Q_DECL_OVERRIDE {
		if(filterRole() < NoFilterRole)
			return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);

		QModelIndex idx = sourceModel()->index(sourceRow, 0, sourceParent);
		if(!idx.isValid())
			return true;

		switch(filterRole()) {
		case NoFilterRole:
			return true;
		case FreqRangeFilter: {
			auto freq = idx.data(MeasurementModel::CarrierFreqRole).toDouble();
			return (lowFreqFilter_ != -1 && highFreqFilter_ != -1) && freq >= lowFreqFilter_
					&& freq <= highFreqFilter_;
		}
		case TimeFilter: {
			auto meas = idx.data(MeasurementModel::BasicMeasRole).value<Base*>();
			return expirationTimeFilter_ != -1 && meas->timeElapsed().elapsed() < expirationTimeFilter_ * 1000;
		}
		default:
			return idx.data(filterRole()).toString() == stringFilter_;
		}
	}

	void invalidateFilter() {
		expirationTimeFilter_ = -1;
		stringFilter_ = "-1";
		lowFreqFilter_ = -1;
		highFreqFilter_ = -1;
		QSortFilterProxyModel::invalidateFilter();
	}

	int expirationTimeFilter() const { return expirationTimeFilter_; }
	void setExpirationTimeFilter(int seconds) {
		expirationTimeFilter_ = seconds;
	}

	QString stringFilter() const { return stringFilter_; }
	void setStringFilter(QString s) { stringFilter_ = s; }

	ApiTypes::OperatingBand operatingBandFilter() const { return operatingBandFilter_; }
	void setOperatingBandFilter(ApiTypes::OperatingBand t) {
		static rf_phreaker::operating_band_range_specifier spec;
		auto range = spec.get_band_freq_range(ApiTypes::toOperatingBand(t));
		operatingBandFilter_ = t;
		lowFreqFilter_ = range.low_freq_hz_ / 1e6;
		highFreqFilter_ = range.high_freq_hz_ / 1e6;
	}

	int64_t lowFreqFilter() const { return lowFreqFilter_; }
	void setLowFreqFilter(int64_t f) { lowFreqFilter_ = f; emit lowFreqFilterChanged(); }

	int64_t highFreqFilter() const { return highFreqFilter_; }
	void setHighFreqFilter(int64_t f) { highFreqFilter_ = f; emit highFreqFilterChanged(); }

signals:
	void lowFreqFilterChanged();
	void highFreqFilterChanged();

private:
	int expirationTimeFilter_;
	QString stringFilter_;
	ApiTypes::OperatingBand operatingBandFilter_;
	double lowFreqFilter_;
	double highFreqFilter_;
};

class BarGraphProxyMeasurementModel : public QIdentityProxyModel {
	Q_OBJECT
public:
	Q_INVOKABLE int rowCount() {
		return QIdentityProxyModel::rowCount();
	}

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
		auto v = QIdentityProxyModel::data(index, role);
		auto column = index.column();
		if(column == MeasurementModel::CarrierSignalLevelColumn ||
				role == MeasurementModel::CarrierSignalLevelRole ||
				column == MeasurementModel::CellSignalLevelColumn ||
				role == MeasurementModel::CellSignalLevelRole ||
				column == MeasurementModel::CellInterferenceColumn ||
				role == MeasurementModel::CellInterferenceRole) {
				return QVariant(v.toDouble() * -1);
		}
		else
			return v;
	}
};

//}}
