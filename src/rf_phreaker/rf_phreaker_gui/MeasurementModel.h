#pragma once
#include "boost/multi_index_container.hpp"
#include <QAbstractListModel>
#include "rf_phreaker/rf_phreaker_gui/MeasurementIndex.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"
#include "rf_phreaker/rf_phreaker_gui/Gsm.h"
#include "rf_phreaker/rf_phreaker_gui/Wcdma.h"
#include "rf_phreaker/rf_phreaker_gui/Lte.h"
#include "rf_phreaker/rf_phreaker_gui/Sweep.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/exception_types.h"

//namespace rf_phreaker { namespace gui {


class MeasurementModel : public QAbstractTableModel {
	Q_OBJECT
	Q_ENUMS(MeasurementRole)
	Q_ENUMS(MeasurementColumn)
public:
	enum MeasurementRole {
		BasicMeasRole = Qt::UserRole + 1,
		GsmRole,
		WcdmaRole,
		LteRole,
		TimeElapsedRole,
		CarrierFreqRole,
		CarrierSignalLevelRole,
		CarrierBandwidthRole,
		CellTechRole,
		CellBandRole,
		CellChannelRole,
		CellIdRole,
		CellSignalLevelRole,
		CellInterferenceRole,
		LteDownlinkBandwidthRole,
		MeasurementRoleSize
	};

	enum MeasurementColumn {
		BasicMeasColumn,
		GsmColumn,
		WcdmaColumn,
		LteColumn,
		TimeElapsedColumn,
		CarrierFreqColumn,
		CarrierSignalLevelColumn,
		CarrierBandwidthColumn,
		CellTechColumn,
		CellBandColumn,
		CellChannelColumn,
		CellIdColumn,
		CellSignalLevelColumn,
		CellInterferenceColumn,
		LteDownlinkBandwidthColumn,
		ColumnSize
	};


	MeasurementModel(QObject *parent = 0)
		: QAbstractTableModel(parent) {}

	~MeasurementModel() {
		clear();
	}

	void clear() {
		beginResetModel();
		index_.clear();
		endResetModel();
	}

	void update_with_basic_data(const rf_phreaker::basic_data &t, ApiTypes::Tech tech) {
		index_frequency ifreq;
		index_id id;
		// If the id is -1 (we haven't decoded bsic, or no valid cells have been detected) and
		// there are no other valid freqs for this tech/freq then add a generic measurement.
		auto range = index_.get<unique_lookup>().equal_range(std::make_tuple(tech, ifreq(t)));
		auto distance = std::distance(range.first, range.second);
		// Nothing there insert generic meas.
		if(distance == 0) {
			 insert(std::vector<Base*> {new GenericMeasurement(t, tech, this)});
		}
		// The only available data is a generic meas.  Update it.
		else if(distance == 1 && id(*range.first) == -1) {
			modify(range.first, t);
//			auto success = index_.modify(range.first, index_update<rf_phreaker::basic_data>(t));
//			if(!success)
//				throw rf_phreaker::rf_phreaker_gui_error("Failed to modify measurement model.");
		}
	}

	// Assumes incoming measurements are unique.
	template<typename Data>
	void update(const std::vector<Data> &v) {
		index_frequency freq;
		index_tech tech;
		index_id id;

		std::vector<Base*> new_items;
		//std::vector<by_unique_lookup::type::iterator> removal_items;
		for(auto &t : v) {
			auto it = index_.get<unique_lookup>().find(std::make_tuple(tech(t), freq(t), id(t)));

			// If the id is valid then we can update or insert measurement, making sure to remove the
			// generic measurement if there.
			if(id(t) != -1) {
				if(it != index_.get<unique_lookup>().end()) {
					modify(it, t);
//					auto success = index_.modify(it, index_update<Data>(t));
//					if(!success)
//						throw rf_phreaker::rf_phreaker_gui_error("Failed to modify measurement model.");
				}
				// If valid measurement and it's new, insert it! At this point remove a generic measurement if present.
				else {
					new_items.push_back(create_data(t));
					auto range = index_.get<unique_lookup>().equal_range(std::make_tuple(tech(t), freq(t)));
					if(std::distance(range.first, range.second) == 1 && id(*range.first) == -1)
						erase(range.first);
				}
			}
			// If we are here then we're dealing with gsm.  I
			else if(it == index_.get<unique_lookup>().end()) {
				auto range = index_.get<unique_lookup>().equal_range(std::make_tuple(tech(t), freq(t)));
				auto distance = std::distance(range.first, range.second);
				// Nothing there insert generic meas.
				if(distance == 0)
					insert(std::vector<Base*>{new GenericMeasurement(t, tech(t), this)});
				// The only available data is a generic meas.  Update it.
				else if(distance == 1 && id(*range.first) == -1) {
					modify(range.first, t);
					//index_.modify(range.first, index_update<Data>(t));
				}
			}
		}
		insert(new_items);
		//erase(removal_items);
	}

	Base* create_data(const rf_phreaker::gsm_data &t) {
		return new Gsm(t, this);
	}

	Base* create_data(const rf_phreaker::umts_data &t) {
		return new Wcdma(t, this);
	}

	Base* create_data(const rf_phreaker::lte_data &t) {
		return new Lte(t, this);
	}

	template<typename Data>
	void modify(const by_unique_lookup::type::iterator &it, const Data &t) {
		auto success = index_.modify(it, index_update<Data>(t));
		if(!success)
			throw rf_phreaker::rf_phreaker_gui_error("Failed to modify measurement model.");

		auto pos = index_position(index_, it);
		// Assume that if something is using one of the measurement classes then it
		// using connections to update the object.
		emit dataChanged(createIndex(pos, TimeElapsedColumn), createIndex(pos, ColumnSize - 1));
	}

	template<typename Comparator, typename Data>
	void update_freq_using_highest(const std::vector<Data> &v) {
		if(v.empty())
			return;

		// Find highest within incoming data.
		Comparator cmp;
		auto highest = v[0];
		for(auto i = v.begin() + 1; i != v.end(); ++i) {
			if(cmp(highest, *i))
				highest = *i;
		}

		index_frequency freq;
		index_tech tech;
		index_id id;

		auto range = index_.get<unique_lookup>().equal_range(std::make_tuple(tech(highest), freq(highest)));
		auto distance = std::distance(range.first, range.second);
		if(distance == 0) {
			insert(create_data(highest));
		}
		else {
			Q_ASSERT(distance == 1);
			if((id(*range.first) == -1 && id(highest) != -1) || cmp(*range.first, highest) || id(*range.first) == id(highest)) {
				modify(range.first, highest);
			}
		}
	}

	int rowCount(const QModelIndex &) const {
		return index_.size();
	}

	int columnCount(const QModelIndex &) const {
		return ColumnSize;
	}

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
		if(index.row() < 0 || index.row() >= (int)index_.size())
			return QVariant();
		if(index.column() < 0 || index.column() >= (int)ColumnSize)
			return QVariant();

		if(role != Qt::DisplayRole) {
			switch(role) {
			case BasicMeasRole:
				return QVariant::fromValue((Base*)index_.get<random_access>()[index.row()]);
			case GsmRole:
				return QVariant::fromValue((Gsm*)index_.get<random_access>()[index.row()]);
			case WcdmaRole:
				return QVariant::fromValue((Wcdma*)index_.get<random_access>()[index.row()]);
			case LteRole:
				return QVariant::fromValue((Lte*)index_.get<random_access>()[index.row()]);
			case TimeElapsedRole:
				return QVariant(index_.get<random_access>()[index.row()]->timeElapsed());
			case CarrierFreqRole:
				return QVariant(index_.get<random_access>()[index.row()]->carrierFreq());
			case CarrierBandwidthRole:
				return QVariant(index_.get<random_access>()[index.row()]->carrierBandwidth());
			case CarrierSignalLevelRole:
				return QVariant(index_.get<random_access>()[index.row()]->carrierSignalLevel());
			case CellTechRole:
				return QVariant(index_.get<random_access>()[index.row()]->cellTech());
			case CellBandRole:
				return QVariant(index_.get<random_access>()[index.row()]->cellBand());
			case CellChannelRole:
				return QVariant(index_.get<random_access>()[index.row()]->cellChannel());
			case CellIdRole:
				return QVariant(index_.get<random_access>()[index.row()]->cellId());
			case CellSignalLevelRole:
				return QVariant(index_.get<random_access>()[index.row()]->cellSignalLevel());
			case CellInterferenceRole:
				return QVariant(index_.get<random_access>()[index.row()]->cellInterference());
			case LteDownlinkBandwidthRole:
				return QVariant(reinterpret_cast<Lte*>(index_.get<random_access>()[index.row()])->downlinkBandwidth());
			default:
				return QVariant();
			}
		}
		else {
			switch(index.column()) {
			case BasicMeasColumn:
				return QVariant::fromValue((Base*)index_.get<random_access>()[index.row()]);
			case GsmColumn:
				return QVariant::fromValue((Gsm*)index_.get<random_access>()[index.row()]);
			case WcdmaColumn:
				return QVariant::fromValue((Wcdma*)index_.get<random_access>()[index.row()]);
			case LteColumn:
				return QVariant::fromValue((Lte*)index_.get<random_access>()[index.row()]);
			case TimeElapsedColumn:
				return QVariant(index_.get<random_access>()[index.row()]->timeElapsed());
			case CarrierFreqColumn:
				return QVariant(index_.get<random_access>()[index.row()]->carrierFreq());
			case CarrierBandwidthColumn:
				return QVariant(index_.get<random_access>()[index.row()]->carrierBandwidth());
			case CarrierSignalLevelColumn:
				return QVariant(index_.get<random_access>()[index.row()]->carrierSignalLevel());
			case CellChannelColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellChannel());
			case CellIdColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellId());
			case CellSignalLevelColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellSignalLevel());
			case CellInterferenceColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellInterference());
			case LteDownlinkBandwidthColumn:
				return QVariant(reinterpret_cast<Lte*>(index_.get<random_access>()[index.row()])->downlinkBandwidth());
			default:;
				return QVariant();
			}
		}
	}

protected:
	QHash<int, QByteArray> roleNames() const {
		QHash<int, QByteArray> roles;
		roles[BasicMeasRole] = "basic";
		roles[GsmRole] = "gsm";
		roles[WcdmaRole] = "wcdma";
		roles[LteRole] = "lte";
		roles[TimeElapsedRole] = "timeElapsed";
		roles[CarrierFreqRole] = "carrierFreq";
		roles[CarrierSignalLevelRole] = "carrierSignalLevel";
		roles[CellTechRole] = "cellTech";
		roles[CellBandRole] = "cellBand";
		roles[CellChannelRole] = "cellChannel";
		roles[CellIdRole] = "cellId";
		roles[CellSignalLevelRole] = "cellSignalLevel";
		roles[CellInterferenceRole] = "cellInterference";
		return roles;
	}
private:
	void insert(Base* t) {
		// Always append to the end.
		auto size = index_.get<random_access>().size();
		beginInsertRows(QModelIndex(), size, size);
			index_.get<random_access>().push_back(t);
		endInsertRows();
	}

	void insert(const std::vector<Base*> &v) {
		if(v.empty())
			return;
		// Always append to the end.
		auto size = index_.get<random_access>().size();
		beginInsertRows(QModelIndex(), size, size + v.size() - 1);
		for(auto &i : v) {
			index_.get<random_access>().push_back(i);
		}
		endInsertRows();
	}

	void erase(const by_unique_lookup::type::iterator &i) {
		auto pos = index_position(index_, i);
		beginRemoveRows(QModelIndex(), pos, pos);
		index_.get<unique_lookup>().erase(i);
		endRemoveRows();
	}

	void erase(const std::vector<by_unique_lookup::type::iterator> &v) {
		for(auto &i : v)
			erase(i);
	}

	data_index index_;

	QVector<int> rolesToUpdate_;
};


//}}
