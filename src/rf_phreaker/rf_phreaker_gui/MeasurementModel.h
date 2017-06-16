#pragma once
#include "boost/multi_index_container.hpp"
#include <QAbstractListModel>
#include <QDebug>
#include "rf_phreaker/rf_phreaker_gui/MeasurementIndex.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"
#include "rf_phreaker/rf_phreaker_gui/Gsm.h"
#include "rf_phreaker/rf_phreaker_gui/Wcdma.h"
#include "rf_phreaker/rf_phreaker_gui/Lte.h"
#include "rf_phreaker/rf_phreaker_gui/Sweep.h"
#include "rf_phreaker/rf_phreaker_gui/Cw.h"
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
		CwRole,
		TimeElapsedRole,
		MeasurementFreqRole,
		MeasurementSignalLevelRole,
		MeasurementBandwidthRole,
		CellTechRole,
		CellBandRole,
		CellChannelRole,
		CellIdRole,
		CellSignalLevelRole,
		CellInterferenceRole,
		CellMccRole,
		CellMncRole,
		CellLacTacRole,
		CellCidRole,
		LteDownlinkBandwidthRole,
		GraphLabelRole,
		MeasurementRoleSize
	};

	enum MeasurementColumn {
		BasicMeasColumn,
		GsmColumn,
		WcdmaColumn,
		LteColumn,
		CwColumn,
		TimeElapsedColumn,
		MeasurementFreqColumn,
		MeasurementSignalLevelColumn,
		MeasurementBandwidthColumn,
		CellTechColumn,
		CellBandColumn,
		CellChannelColumn,
		CellIdColumn,
		CellSignalLevelColumn,
		CellInterferenceColumn,
		CellMccColumn,
		CellMncColumn,
		CellLacTacColumn,
		CellCidColumn,
		LteDownlinkBandwidthColumn,
		GraphLabelColumn,
		ColumnSize
	};

	MeasurementModel(QObject *parent = 0)
		: QAbstractTableModel(parent) {
		roles_[BasicMeasRole] = "basic";
		roles_[GsmRole] = "gsm";
		roles_[WcdmaRole] = "wcdma";
		roles_[LteRole] = "lte";
		roles_[CwRole] = "cw";
		roles_[TimeElapsedRole] = "timeElapsed";
		roles_[MeasurementFreqRole] = "measurementFreq";
		roles_[MeasurementSignalLevelRole] = "measurementSignalLevel";
		roles_[CellTechRole] = "cellTech";
		roles_[CellBandRole] = "cellBand";
		roles_[CellChannelRole] = "cellChannel";
		roles_[CellIdRole] = "cellId";
		roles_[CellSignalLevelRole] = "cellSignalLevel";
		roles_[CellInterferenceRole] = "cellInterference";
		roles_[CellMccRole] = "mcc";
		roles_[CellMncRole] = "mnc";
		roles_[CellLacTacRole] = "lactac";
		roles_[CellCidRole] = "cid";
		roles_[LteDownlinkBandwidthRole] = "lteDownlinkBandwidth";
		roles_[GraphLabelRole] = "graphLabelRole";

		for(auto i = roles_.begin(); i != roles_.end(); ++i)
			roleLookup_.insert(i.value(), i.key());
	}

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
					new_items.push_back(create_data(t));
				// The only available data is a generic meas.  Erase the original measurement and
				// insert a new one.  We do this rather than update it so that views that depend on
				// the cellId will be able to keep track.
				else if(distance == 1 && id(*range.first) == -1) {
					erase(range.first);
					new_items.push_back(create_data(t));
				}
			}
		}

		// Take any duplicates and aggregate them into one measurement.  This
		// ensures we are able to keep all available layer 3.
		if(!new_items.empty()) {
			less_than_freq_id freq_id;
			std::vector<Base*> after_dup_removal;
			std::sort(new_items.begin(), new_items.end(), freq_id);
			auto p = std::equal_range(new_items.begin(), new_items.end(), *new_items.begin(), freq_id);
			while(auto distance = std::distance(p.first, p.second)) {
				after_dup_removal.push_back(*p.first);
				auto it = p.first;
				++it;
				while(it != p.second) {
					after_dup_removal.back()->update((*it)->base());
					++it;
				}
				if(p.second == new_items.end()) break;
				p = std::equal_range(p.second, new_items.end(), *p.second, freq_id);
			}
			insert(after_dup_removal);
		}
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

	Base* create_data(const rf_phreaker::power_spectrum_data &t) {
		return new Cw(t, this);
	}

	template<typename Data>
	void modify(const by_unique_lookup::type::iterator &it, const Data &t) {
		auto success = index_.modify(it, index_update<Data>(t));
		if(!success)
			throw rf_phreaker::rf_phreaker_gui_error("Failed to modify measurement model.");

		auto pos = index_position(index_, it);
		// Assume that if something is using one of the measurement classes then it
		// using connections to update the object.
		emit dataChanged(createIndex(pos, BasicMeasColumn), createIndex(pos, columnCount() - 1));
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

		update_freq<Comparator>(highest);
	}

	template<typename Comparator, typename Data>
	void update_freq(const Data &highest) {
		Comparator cmp;
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
		return columnCount();
	}

	virtual int columnCount() const {
		return ColumnSize;
	}

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
		if(index.row() < 0 || index.row() >= (int)index_.size())
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
			case CwRole:
				return QVariant::fromValue((Cw*)index_.get<random_access>()[index.row()]);
			case TimeElapsedRole:
				return QVariant(index_.get<random_access>()[index.row()]->timeElapsed());
			case MeasurementFreqRole:
				return QVariant(index_.get<random_access>()[index.row()]->measurementFreq());
			case MeasurementBandwidthRole:
				return QVariant(index_.get<random_access>()[index.row()]->measurementBandwidth());
			case MeasurementSignalLevelRole:
				return QVariant(index_.get<random_access>()[index.row()]->measurementSignalLevel());
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
			case CellMccRole:
				return QVariant(index_.get<random_access>()[index.row()]->cellMccStr());
			case CellMncRole:
				return QVariant(index_.get<random_access>()[index.row()]->cellMncStr());
			case CellLacTacRole:
				return QVariant(index_.get<random_access>()[index.row()]->cellLacTacStr());
			case CellCidRole:
				return QVariant(index_.get<random_access>()[index.row()]->cellCidStr());
			case LteDownlinkBandwidthRole:
				return QVariant(reinterpret_cast<Lte*>(index_.get<random_access>()[index.row()])->downlinkBandwidth());
			case GraphLabelRole: {
				return QVariant(graphLabel(index.row()));
			}
			default:
				return QVariant();
			}
		}
		else {
			if(index.column() < 0 || index.column() >= (int)ColumnSize)
				return QVariant();

			switch(index.column()) {
			case BasicMeasColumn:
				return QVariant::fromValue((Base*)index_.get<random_access>()[index.row()]);
			case GsmColumn:
				return QVariant::fromValue((Gsm*)index_.get<random_access>()[index.row()]);
			case WcdmaColumn:
				return QVariant::fromValue((Wcdma*)index_.get<random_access>()[index.row()]);
			case LteColumn:
				return QVariant::fromValue((Lte*)index_.get<random_access>()[index.row()]);
			case CwColumn:
				return QVariant::fromValue((Cw*)index_.get<random_access>()[index.row()]);
			case TimeElapsedColumn:
				return QVariant(index_.get<random_access>()[index.row()]->timeElapsed());
			case MeasurementFreqColumn:
				return QVariant(index_.get<random_access>()[index.row()]->measurementFreq());
			case MeasurementBandwidthColumn:
				return QVariant(index_.get<random_access>()[index.row()]->measurementBandwidth());
			case MeasurementSignalLevelColumn:
				return QVariant(index_.get<random_access>()[index.row()]->measurementSignalLevel());
			case CellChannelColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellChannel());
			case CellIdColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellId());
			case CellSignalLevelColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellSignalLevel());
			case CellInterferenceColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellInterference());
			case CellMccColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellMccStr());
			case CellMncColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellMncStr());
			case CellLacTacColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellLacTacStr());
			case CellCidColumn:
				return QVariant(index_.get<random_access>()[index.row()]->cellCidStr());
			case LteDownlinkBandwidthColumn:
				return QVariant(reinterpret_cast<Lte*>(index_.get<random_access>()[index.row()])->downlinkBandwidth());
			case GraphLabelColumn: 
				return QVariant(graphLabel(index.row()));
			default:;
				return QVariant();
			}
		}
	}

	virtual QString graphLabel(int row) const {
		auto meas = index_.get<random_access>()[row];
		QString t(" ");
		t += QString::number(meas->cellChannel());
		if(meas->cellId() != -1)
			t += " - " + QString::number(meas->cellId());
		return t;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {
		if(role != Qt::DisplayRole) {
			switch(role) {
			case BasicMeasRole:
				return "Measurement";
			case GsmRole:
				return "Gsm";
			case WcdmaRole:
				return "Wcdma";
			case LteRole:
				return "Lte";
			case CwRole:
				return "Cw";
			case TimeElapsedRole:
				return "Time Elapsed";
			case MeasurementFreqRole:
				return "Frequency";
			case MeasurementBandwidthRole:
				return "Measurement Bandwidth";
			case MeasurementSignalLevelRole:
				return "Measurement SL";
			case CellTechRole:
				return "Tech";
			case CellBandRole:
				return "Band";
			case CellChannelRole:
				return "Channel";
			case CellIdRole:
				return "ID";
			case CellSignalLevelRole:
				return "Signal Level";
			case CellInterferenceRole:
				return "Interference";
			case CellMccRole:
				return "MCC";
			case CellMncRole:
				return "MNC";
			case CellLacTacRole:
				return "LAC/TAC";
			case CellCidRole:
				return "CELLID";
			case LteDownlinkBandwidthRole:
				return "Downlink Bandwidth";
			case GraphLabelRole:
				return "Graph Label";
			default:
				return QVariant();
			}
		}
		return QVariant();
	}

	Q_INVOKABLE virtual int convertRoleToColumn(QString role) {
		auto r = findRole(role);
		switch(r) {
		case BasicMeasRole:
			return BasicMeasColumn;
		case GsmRole:
			return GsmColumn;
		case WcdmaRole:
			return WcdmaColumn;
		case LteRole:
			return LteColumn;
		case CwRole:
			return CwColumn;
		case TimeElapsedRole:
			return TimeElapsedColumn;
		case MeasurementFreqRole:
			return MeasurementFreqColumn;
		case MeasurementBandwidthRole:
			return MeasurementBandwidthColumn;
		case MeasurementSignalLevelRole:
			return MeasurementSignalLevelColumn;
		case CellTechRole:
			return CellTechColumn;
		case CellBandRole:
			return CellBandColumn;
		case CellChannelRole:
			return CellChannelColumn;
		case CellIdRole:
			return CellIdColumn;
		case CellSignalLevelRole:
			return CellSignalLevelColumn;
		case CellInterferenceRole:
			return CellInterferenceColumn;
		case CellMccRole:
			return CellMccColumn;
		case CellMncRole:
			return CellMncColumn;
		case CellLacTacRole:
			return CellLacTacColumn;
		case CellCidRole:
			return CellCidColumn;
		case LteDownlinkBandwidthRole:
			return LteDownlinkBandwidthColumn;
		case GraphLabelRole:
			return GraphLabelColumn;
		default:
			qDebug() << "Unknown role when converting to column.";
			return MeasurementFreqColumn;
		}
	}

	Q_INVOKABLE int findRole(QString role) {
		return roleLookup_.find(role.toLocal8Bit()).value();
	}

protected:
	QHash<int, QByteArray> roleNames() const {
		return roles_;
	}
	
	data_index index_;

	QVector<int> rolesToUpdate_;

	QHash<int, QByteArray> roles_;

	QHash<QByteArray, int> roleLookup_;

private:
	void insert(Base* t) {
		// Always append to the end.
		auto size = index_.get<random_access>().size();
		beginInsertRows(QModelIndex(), size, size);
		index_.get<random_access>().push_back(t);
		endInsertRows();

//		qDebug() << "Insert pos:" << size << "  channel:" << (t->cellChannel() == -1 ? t->measurementFreq() : t->cellChannel())
//																				   << "  cid: " << t->cellId();
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
		//qDebug() << "Remove pos:" << pos << "  channel:" << (*i)->cellChannel() << "  cid: " << (*i)->cellId();
		beginRemoveRows(QModelIndex(), pos, pos);
		index_.get<unique_lookup>().erase(i);
		endRemoveRows();
	}

	void erase(const std::vector<by_unique_lookup::type::iterator> &v) {
		for(auto &i : v)
			erase(i);
	}

};

class GsmMeasurementModel : public MeasurementModel {
	Q_OBJECT
public:
	GsmMeasurementModel(QObject *parent = nullptr)
		: MeasurementModel(parent) {}
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {
		if(role != Qt::DisplayRole) {
			switch(role) {
			case CellChannelRole:
				return "ARFCN";
			case CellIdRole:
				return "BSIC";
			case CellInterferenceRole:
				return "C/I";
			case CellSignalLevelRole:
				return "BCCH Signal Level";
			case CellLacTacRole:
				return "LAC";
			default:
				return MeasurementModel::headerData(section, orientation, role);
			}
		}
		return QVariant();
	}
};

class WcdmaMeasurementModel : public MeasurementModel {
	Q_OBJECT
public:
	WcdmaMeasurementModel(QObject *parent = nullptr)
		: MeasurementModel(parent) {}
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {
		if(role != Qt::DisplayRole) {
			switch(role) {
			case CellChannelRole:
				return "UARFCN";
			case CellIdRole:
				return "CPICH";
			case CellSignalLevelRole:
				return "RSCP";
			case CellInterferenceRole:
				return "Ec/Io";
			case CellLacTacRole:
				return "LAC";
			default:
				return MeasurementModel::headerData(section, orientation, role);
			}
		}
		return QVariant();
	}
};

class LteMeasurementModel : public MeasurementModel {
	Q_OBJECT
public:
	LteMeasurementModel(QObject *parent = nullptr)
		: MeasurementModel(parent) {}
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {
		if(role != Qt::DisplayRole) {
			switch(role) {
				case CellChannelRole:
					return "EARFCN";
				case CellIdRole:
					return "Physical CID";
				case CellSignalLevelRole:
					return "Sync Signal Level";
				case CellInterferenceRole:
					return "Sync Quality";
				case CellLacTacRole:
					return "TAC";
				default:
					return MeasurementModel::headerData(section, orientation, role);
			}
		}
		return QVariant();
	}
};

class CwMeasurementModel : public MeasurementModel {
	Q_OBJECT
	Q_ENUMS(CwMeasurementRole)
	Q_ENUMS(CwMeasurementColumn)
public:
	enum CwMeasurementRole {
		IdentifierRole = MeasurementRoleSize,
		BinSizeRole,
		DwellTimeRole,
		CwRoleSize
	};

	enum CwMeasurementColumn {
		IdentifierColumn = ColumnSize,
		BinSizeColumn,
		DwellTimeColumn,
		CwColumnSize
	};

public:
	CwMeasurementModel(QObject *parent = nullptr)
		: MeasurementModel(parent) {
		roles_[IdentifierRole] = "identifierRole";
		roles_[BinSizeRole] = "binSizeRole";
		roles_[DwellTimeRole] = "dwellTimeRole";

		for(auto i = (int)IdentifierRole; i <= CwRoleSize; ++i)
			roleLookup_.insert(roles_[i], i);
	}


	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {
		if(role != Qt::DisplayRole) {
			switch(role) {
				case BinSizeRole:
					return "Bandwidth (kHz)";
				case IdentifierRole:
					return "Frequency";
				case DwellTimeRole:
					return "Dwell Time (ms)";
				case CellSignalLevelRole:
					return "Signal Level";
				default:
					return MeasurementModel::headerData(section, orientation, role);
			}
		}
		return QVariant();
	}
	virtual QString graphLabel(int row) const {
		auto meas = reinterpret_cast<Cw*>(index_.get<random_access>()[row]);
		QString t(" ");
		t += QString::number(meas->identifier(), 'f', 1);
		return t;
	}

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
		if(role != Qt::DisplayRole) {
			switch(role) {
				case IdentifierRole:
					return MeasurementModel::data(index, CwRole).value<Cw*>()->identifier();
				case BinSizeRole:
					return MeasurementModel::data(index, CwRole).value<Cw*>()->binSize();
				case DwellTimeRole:
					return MeasurementModel::data(index, CwRole).value<Cw*>()->dwellTime();
				default:
					return MeasurementModel::data(index, role);
			}
		}
		else {
			switch(index.column()) {
				case IdentifierColumn:
					return MeasurementModel::data(index, CwRole).value<Cw*>()->identifier();
				case BinSizeColumn:
					return MeasurementModel::data(index, CwRole).value<Cw*>()->binSize();
				case DwellTimeColumn:
					return MeasurementModel::data(index, CwRole).value<Cw*>()->dwellTime();
				default:
					return MeasurementModel::data(index, role);
			}
		}
	}

	int columnCount(const QModelIndex &) const {
		return columnCount();
	}

	virtual int columnCount() const {
		return CwColumnSize;
	}

	Q_INVOKABLE int convertRoleToColumn(QString role) {
		int r = roleLookup_.find(role.toLocal8Bit()).value();
		switch(r) {
			case IdentifierRole:
				return IdentifierColumn;
			case BinSizeRole:
				return BinSizeColumn;
			case DwellTimeRole:
				return DwellTimeColumn;
			default:
				return MeasurementModel::convertRoleToColumn(role);
		}
	}
};

//}}
