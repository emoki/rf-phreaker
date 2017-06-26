#pragma once
#include <QAbstractListModel>
#include <QDebug>
#include "rf_phreaker/rf_phreaker_gui/CollectionInfo.h"

//namespace rf_phreaker { namespace gui {

class CollectionInfoList : public QAbstractListModel {
	Q_OBJECT
	Q_ENUMS(CollectionInfoRole)
	Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
public:
	enum CollectionInfoRole {
		COLLECTIONINFO = Qt::UserRole,
		CHANNELS,
		FREQS,
		BAND,
		INFO,
		TECH,
		ISSWEEP,
		ISGSM,
		ISWCDMA,
		ISLTE,
		ISSPECTRUM,
		ISCW,
		ISIQ,
		RADIOTYPE,
		MAXCOLUMNS
	};

	CollectionInfoList(QObject* parent = nullptr)
		: QAbstractListModel(parent) {
		roleNames_[COLLECTIONINFO] = "collectionInfo";
		roleNames_[CHANNELS] = "channels";
		roleNames_[FREQS] = "freqs";
		roleNames_[BAND] = "band";
		roleNames_[INFO] = "info";
		roleNames_[TECH] = "tech";
		roleNames_[ISSWEEP] = "isSweep";
		roleNames_[ISGSM] = "isGsm";
		roleNames_[ISWCDMA] = "isWcdma";
		roleNames_[ISLTE] = "isLte";
		roleNames_[ISSPECTRUM] = "isSpectrum";
		roleNames_[ISCW] = "isCw";
		roleNames_[ISIQ] = "isIq";
		roleNames_[RADIOTYPE] = "radioType";
	}

	QHash<int, QByteArray> roleNames() const {
		return roleNames_;
	}

	QVariant headerData(int /*section*/, Qt::Orientation /*orientation*/, int role) const {
		if(role > roleNames_.size())
			return QVariant();
		else {
			switch(role) {
			case COLLECTIONINFO:
				return "Collection Info";
			 case CHANNELS:
				return "Channel(s)";
			 case FREQS:
				return "Frequency(ies)";
			 case BAND:
				return "Band";
			 case INFO:
				return "Common Name";
			 case TECH:
				return "Tech";
			 case ISSWEEP:
				 return "Is Sweeping";
			 case ISGSM:
				 return "Is Gsm";
			 case ISWCDMA:
				 return "Is Wcdma";
			 case ISLTE:
				 return "Is Lte";
			 case ISSPECTRUM:
				 return "Is Spectrum";
			 case ISCW:
				 return "Is Cw";
			 case ISIQ:
				 return "Is Iq";
			 case RADIOTYPE:
			   return "Radio Type";
			default:
				return QVariant();
			}
		}
	}

	int rowCount(const QModelIndex & = QModelIndex()) const {
		return list_.size();
	}

	QVariant data(const QModelIndex &index, int role) const {
		if(index.row() < 0 || index.row() >= (int)list_.size())
			return QVariant();
		if(index.column() < 0 || index.column() >= 1)
			return QVariant();

		auto r = static_cast<CollectionInfoRole>(role);
		switch(r) {
		case Qt::DisplayRole:
		case COLLECTIONINFO:
			return QVariant::fromValue(list_[index.row()]);
		case CHANNELS:
			return QVariant::fromValue(list_[index.row()]->toChannelsStr());
		case FREQS:
			return QVariant::fromValue(list_[index.row()]->toFreqsStr());
		case BAND:
			return QVariant::fromValue(list_[index.row()]->toBandStr());
		case INFO:
			return QVariant::fromValue(list_[index.row()]->toInfoStr());
		case TECH:
			return QVariant::fromValue(list_[index.row()]->toTechStr());
		case ISSWEEP:
			return QVariant::fromValue(list_[index.row()]->isSweep());
		case ISGSM:
			return QVariant::fromValue(list_[index.row()]->isGsm());
		case ISWCDMA:
			return QVariant::fromValue(list_[index.row()]->isWcdma());
		case ISLTE:
			return QVariant::fromValue(list_[index.row()]->isLte());
		case ISSPECTRUM:
			return QVariant::fromValue(list_[index.row()]->isSpectrum());
		case ISCW:
			return QVariant::fromValue(list_[index.row()]->isCw());
		case ISIQ:
			return QVariant::fromValue(list_[index.row()]->isIq());
		case RADIOTYPE:
			return QVariant::fromValue(list_[index.row()]->toRadioTypeStr());
		default:
			return QVariant();
		}
	}

	Q_INVOKABLE QVariant at(int i) {
		if(i < list_.size())
			return QVariant::fromValue(list_[i]);
		else
			return QVariant();
	}

	Q_INVOKABLE bool remove(int i) {
		if(i < list_.size()) {
			beginRemoveRows(QModelIndex(), i, i);
			list_.removeAt(i);
			endRemoveRows();
			return true;
		}
		else
			return false;
	}

	bool setData(const QModelIndex &, const QVariant &, int ) {
		return true;
	}

	Qt::ItemFlags flags(const QModelIndex &) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled /*| Qt::ItemIsEditable*/;
	}

	Q_INVOKABLE bool add(CollectionInfo *info) {
		if(info == nullptr)
			return false;
		beginInsertRows(QModelIndex(), list_.size(), list_.size());
		auto ci = new CollectionInfo(info->channelFreqLow()->channelFreq(), info->channelFreqHigh()->channelFreq(),
									 info->channelFreqLow()->tech(), this);
		list_.push_back(ci);
		endInsertRows();
		emit rowCountChanged();
		return true;
	}

	bool removeRows(int row, int count, const QModelIndex &parent) {
		beginRemoveRows(parent, row, row + count - 1);
		for(int i = row; i < count; ++i)
			list_.removeAt(row);
		endRemoveRows();
		emit rowCountChanged();
		return true;
	}

	void setList(const QList<CollectionInfo*> &list) {
		beginResetModel();
		list_.clear();
		for(auto &i : list) {
			i->setParent(this);
			list_.push_back(i);
		}
		endResetModel();

	}

	const QList<CollectionInfo*>& list() { return list_; }

signals:
	void rowCountChanged();

private:
	QHash<int, QByteArray> roleNames_;
	QList<CollectionInfo*> list_;
};

//}}
