#pragma once
#include <QAbstractTableModel>
#include "rf_phreaker/rf_phreaker_gui/RawLayer3.h"


class RawLayer3Model : public QAbstractTableModel {
	Q_OBJECT
	Q_ENUMS(RawLayer3Role)
	Q_ENUMS(RawLayer3Column)

public:
	enum RawLayer3Role {
		BitStringRole = Qt::UserRole + 1,
		MessageTypeRole,
		DescriptionRole,
		RoleSize
	};

	enum RawLayer3Column {
		BitStringColumn,
		MessageTypeColumn,
		DescriptionColumn,
		ColumnSize
	};

	RawLayer3Model(QObject *parent = nullptr) :
		QAbstractTableModel(parent) {
		roles_[BitStringRole] = "bitString";
		roles_[MessageTypeRole] = "messageType";
		roles_[DescriptionRole] = "description";
	}

	Q_INVOKABLE void clear() {
		beginResetModel();
		bits_.clear();
		messageTypes_.clear();
		descriptions_.clear();
		endResetModel();
	}

	void pushBack(std::string &&bits, std::string &&messageType, std::string &&description) {
		beginInsertRows(QModelIndex(), bits_.size(), bits_.size());
		bits_.emplace_back(std::move(bits));
		messageTypes_.emplace_back(std::move(messageType));
		descriptions_.emplace_back(std::move(description));
		endInsertRows();
	}

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
		if(index.row() < 0 || index.row() >= (int)bits_.size())
			return QVariant();
		if(role != Qt::DisplayRole) {
			switch(role) {
			case BitStringRole:
				return QString(bits_[index.row()].c_str());
			case MessageTypeRole:
				return QString(messageTypes_[index.row()].c_str());
			case DescriptionRole:
				return QString(descriptions_[index.row()].c_str());
			default:
				return QVariant{};
			}
		}
		else {
			if(index.column() < 0 || index.column() >= (int)ColumnSize)
				return QVariant();
			
			switch(index.column()) {
			case BitStringColumn:
				return QString(bits_[index.row()].c_str());
			case MessageTypeColumn:
				return QString(messageTypes_[index.row()].c_str());
			case DescriptionColumn:
				return QString(descriptions_[index.row()].c_str());
			default:
				return QVariant{};
			}
		}
	}

	int rowCount(const QModelIndex &) const {
		return bits_.size();
	}

	int columnCount(const QModelIndex &) const {
		return ColumnSize;
	}

protected:
	QHash<int, QByteArray> roleNames() const {
		return roles_;
	}

private:
	QHash<int, QByteArray> roles_;
	std::vector<std::string> bits_;
	std::vector<std::string> messageTypes_;
	std::vector<std::string> descriptions_;
};
