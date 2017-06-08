#pragma once
#include <unordered_map>
#include <QAbstractTableModel>
#include <QtCharts/QXYSeries>
#include <QVector>
#include "boost/circular_buffer.hpp"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/Utility.h"
#include "rf_phreaker/rf_phreaker_gui/FreqLimits.h"

class SpectrumModel : public QAbstractTableModel {
	Q_OBJECT
	Q_ENUMS(SpectrumRole)
	Q_ENUMS(SpectrumColumn)

public:
	enum SpectrumRole {
		FrequencyRole = Qt::UserRole + 1,
		SignalLevelRole,
		RoleSize
	};
	
	enum SpectrumColumn {
		FrequencyColumn,
		SignalLevelColumn,
		ColumnSize
	};

	typedef std::map<size_t, rf_phreaker::power_spectrum_data> modelType;

	SpectrumModel(QObject *parent = nullptr)
		: QAbstractTableModel(parent)
		, collectionRound_(-1)
		, isDirty_(false) {
		roles_[FrequencyRole] = "frequency";
		roles_[SignalLevelRole] = "signalLevel";

	}

	~SpectrumModel() {
		clear();
	}

	Q_INVOKABLE void clear() {
		beginResetModel();
		storage_.clear();
		endResetModel();
		collectionRound_ = -1;
	}

	Q_INVOKABLE void updateSeries(QtCharts::QXYSeries *series) {
		if(isDirty_ && series && storage_.size()) {
			QVector<QPointF> vec(storage_.rbegin()->first);
			int i = 0;
			for(auto &spec : storage_) {
				auto freq = spec.second.params_.start_frequency_;
				auto step = spec.second.params_.step_size_;
				for(const auto &p : spec.second.power_) {
					vec[i].setX(freq / 1e6f);
					vec[i++].setY(p);
					freq += step;
				}
			}
			series->replace(vec);
			isDirty_ = false;
		}
	}

	void update(rf_phreaker::power_spectrum_data &&spec) {
		isDirty_ = true;
		collectionRound_ = spec.collection_round_;
		auto k = storageLookup_.find(spec);
		if(k == storageLookup_.end()) {
			// Insert 
			SpecSort sort(spec);
			size_t numRows = storage_.size() ? storage_.rbegin()->first : 0;
			size_t key = numRows + spec.power_.size();
			//beginInsertRows(QModelIndex(), numRows, key - 1);
			storage_.emplace(key, spec);
			//endInsertRows();
			storageLookup_.emplace(sort, key);
		}
		else {
			// Update
			auto it = storage_.lower_bound(k->second);
			if(it != storage_.end()) {
				std::swap(it->second, spec);
				//emit dataChanged(createIndex(it->first - it->second.power_.size(), 0),
				//	createIndex(it->first - 1, ColumnSize - 1));
			}
		}
	}

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
		if(index.column() < 0 || index.column() >= (int)ColumnSize)
			return QVariant();

		auto it = storage_.upper_bound(index.row());
		if(index.row() < 0 || it == storage_.end() || index.row() >= (int)it->second.power_.size())
			return QVariant();

		auto spec = it->second;
		auto rowInPower = index.row() - (it->first - spec.power_.size());

		if(role != Qt::DisplayRole) {
			switch(role) {
				case FrequencyRole:
					return (spec.params_.start_frequency_ + (rowInPower * spec.params_.step_size_)) / 1e6;
				case SignalLevelRole:
					return spec.power_[rowInPower];
				default:
					return QVariant();
			}
		}
		else {
			switch(index.column()) {
				case FrequencyColumn:
					return (spec.params_.start_frequency_ + (rowInPower * spec.params_.step_size_)) / 1e6;
				case SignalLevelColumn:
					return spec.power_[rowInPower];
				default:
					return QVariant();
			}
		}
	}

	int rowCount(const QModelIndex &) const {
		return storage_.size() ? storage_.rbegin()->first : 0;
	}

	int columnCount(const QModelIndex &) const {
		return ColumnSize;
	}

	bool isNewCollectionRound(const rf_phreaker::power_spectrum_data &spec) {
		return collectionRound_ != spec.collection_round_ && collectionRound_ != -1;
	}

	const modelType& internalModel() {	return storage_; }

protected:
	QHash<int, QByteArray> roleNames() const {
		return roles_;
	}

private:
	QHash<int, QByteArray> roles_;
	modelType storage_;
	std::map<SpecSort, size_t> storageLookup_;
	int64_t collectionRound_;
	bool isDirty_;
};
