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
	Q_PROPERTY(QString stringFilter READ stringFilter WRITE setStringFilter NOTIFY stringFilterChanged)
	Q_PROPERTY(int expirationTimeFilter READ expirationTimeFilter WRITE setExpirationTimeFilter NOTIFY expirationTimeFilterChanged)
	Q_PROPERTY(ApiTypes::OperatingBand operatingBandFilter READ operatingBandFilter WRITE setOperatingBandFilter NOTIFY operatingBandFilterChanged)
	Q_PROPERTY(double lowFreqFilter READ lowFreqFilter WRITE setLowFreqFilter NOTIFY lowFreqFilterChanged)
	Q_PROPERTY(double highFreqFilter READ highFreqFilter WRITE setHighFreqFilter NOTIFY  highFreqFilterChanged)
	Q_PROPERTY(ApiTypes::OperatingBand lowBandFilter READ lowBandFilter WRITE setLowBandFilter NOTIFY lowBandFilterChanged)
	Q_PROPERTY(ApiTypes::OperatingBand highBandFilter READ highBandFilter WRITE setHighBandFilter NOTIFY  highBandFilterChanged)
public:
	FilterProxyMeasurementModel(QObject *parent = 0)
		: QSortFilterProxyModel(parent)
		, expirationTimeFilter_(-1)
		, stringFilter_("-1")
		, operatingBandFilter_(ApiTypes::OPERATING_BAND_UNKNOWN)
		, lowFreqFilter_(-1)
		, highFreqFilter_(-1)
		, lowBandFilter_(ApiTypes::OPERATING_BAND_UNKNOWN)
		, highBandFilter_(ApiTypes::OPERATING_BAND_UNKNOWN) {
		setFilterRole(NoFilterRole);
	}

	enum MeasFilterRole {
		NoFilterRole = MeasurementModel::MeasurementRoleSize,
		TimeFilter,
		FreqRangeFilter,
		BandRangeFilter
	};

	Q_INVOKABLE void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) Q_DECL_OVERRIDE {
		QSortFilterProxyModel::sort(column, order);
	}

	Q_INVOKABLE int rowCount() {
		return QSortFilterProxyModel::rowCount();
	}

	Q_INVOKABLE void resetFilters() {
		expirationTimeFilter_ = -1;
		stringFilter_ = "-1";
		lowFreqFilter_ = -1;
		highFreqFilter_ = -1;
		lowBandFilter_ = ApiTypes::OPERATING_BAND_UNKNOWN;
		highBandFilter_ = ApiTypes::OPERATING_BAND_UNKNOWN;
		operatingBandFilter_ = ApiTypes::OPERATING_BAND_UNKNOWN;
		invalidateFilter();
	}

	Q_INVOKABLE void reset() {
		QSortFilterProxyModel::beginResetModel();
		QSortFilterProxyModel::endResetModel();
	}

	Q_INVOKABLE void refilter() {
		QSortFilterProxyModel::invalidateFilter();
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
			//qDebug() << "sourceRow: " << sourceRow << "   filtered: " << ((lowFreqFilter_ != -1 && highFreqFilter_ != -1) && freq >= lowFreqFilter_
			//			&& freq <= highFreqFilter_) << "  freq:" << freq;
			return (lowFreqFilter_ != -1 && highFreqFilter_ != -1) && freq >= lowFreqFilter_
					&& freq <= highFreqFilter_;
		}
		case BandRangeFilter: {
			auto band = (ApiTypes::OperatingBand)idx.data(MeasurementModel::CellBandRole).toInt();
			return (lowBandFilter_ != ApiTypes::OPERATING_BAND_UNKNOWN && highBandFilter_ != ApiTypes::OPERATING_BAND_UNKNOWN)
					&& band >= lowBandFilter_ && band <= highBandFilter_;
		}
		case TimeFilter: {
			auto meas = idx.data(MeasurementModel::BasicMeasRole).value<Base*>();
//			qDebug() << "sourceRow: " << sourceRow << "   filtered: " << (expirationTimeFilter_ == -1 || meas->timeElapsed().elapsed() < expirationTimeFilter_ * 1000)
//				<< "  channel:" << meas->cellChannel() << "  cid: " << meas->cellId();
			return expirationTimeFilter_ == -1 || meas->timeElapsed().elapsed() < expirationTimeFilter_ * 1000;
		}
		default:
			return idx.data(filterRole()).toString() == stringFilter_;
		}
	}

	int expirationTimeFilter() const { return expirationTimeFilter_; }
	void setExpirationTimeFilter(int seconds) {
		expirationTimeFilter_ = seconds;
		emit expirationTimeFilterChanged();
	}

	QString stringFilter() const { return stringFilter_; }
	void setStringFilter(QString s) { stringFilter_ = s; emit stringFilterChanged(); }

	ApiTypes::OperatingBand operatingBandFilter() const { return operatingBandFilter_; }
	void setOperatingBandFilter(ApiTypes::OperatingBand t) {
		static rf_phreaker::operating_band_range_specifier spec;
		auto range = spec.get_band_freq_range(ApiTypes::toOperatingBand(t));
		operatingBandFilter_ = t;
		lowFreqFilter_ = range.low_freq_hz_ / 1e6;
		highFreqFilter_ = range.high_freq_hz_ / 1e6;
		emit operatingBandFilterChanged();
	}

	int64_t lowFreqFilter() const { return lowFreqFilter_; }
	void setLowFreqFilter(int64_t f) { lowFreqFilter_ = f; emit lowFreqFilterChanged(); }

	int64_t highFreqFilter() const { return highFreqFilter_; }
	void setHighFreqFilter(int64_t f) { highFreqFilter_ = f; emit highFreqFilterChanged(); }

	ApiTypes::OperatingBand lowBandFilter() const { return lowBandFilter_; }
	void setLowBandFilter(ApiTypes::OperatingBand f) { lowBandFilter_ = f; emit lowBandFilterChanged(); }

	ApiTypes::OperatingBand highBandFilter() const { return highBandFilter_; }
	void setHighBandFilter(ApiTypes::OperatingBand f) { highBandFilter_ = f; emit highBandFilterChanged(); }

signals:
	void stringFilterChanged();
	void expirationTimeFilterChanged();
	void operatingBandFilterChanged();
	void lowFreqFilterChanged();
	void highFreqFilterChanged();
	void lowBandFilterChanged();
	void highBandFilterChanged();

private:
	int expirationTimeFilter_;
	QString stringFilter_;
	ApiTypes::OperatingBand operatingBandFilter_;
	double lowFreqFilter_;
	double highFreqFilter_;
	ApiTypes::OperatingBand lowBandFilter_;
	ApiTypes::OperatingBand highBandFilter_;
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
