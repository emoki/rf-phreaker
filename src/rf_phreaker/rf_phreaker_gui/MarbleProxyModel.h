#pragma once
#include <QObject.h>
#include <QIdentityProxyModel.h>
#include "marble/GeoDataTreeModel.h"
#include "marble/MarblePlacemarkModel.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleHelper.h"

class MarbleProxyModel : public QIdentityProxyModel {
	Q_OBJECT
	Q_ENUMS(MarbleModelRole)
public:
	enum MarbleModelRole {
		DisplayRole = Qt::DisplayRole,
		CheckStateRole = Qt::CheckStateRole,
		DecorationRole = Qt::DecorationRole,
		ToolTipRole = Qt::ToolTipRole,
		PlacemarkObjectPointerRole = Marble::MarblePlacemarkModel::ObjectPointerRole,
		PlacemarkPopularityRole = Marble::MarblePlacemarkModel::PopularityRole,
		PlacemarkPopularityIndexRole = Marble::MarblePlacemarkModel::PopularityIndexRole,
		PlacemarkCoodinateRole = Marble::MarblePlacemarkModel::CoordinateRole,
		BackgroundRole = Qt::BackgroundRole
	};
	explicit MarbleProxyModel(QObject* parent = Q_NULLPTR)
		: QIdentityProxyModel(parent) {
		roles_[DisplayRole] = "display";
		roles_[CheckStateRole] = "checkState";
		roles_[DecorationRole] = "decoration";
		roles_[ToolTipRole] = "toolTip";
		roles_[PlacemarkObjectPointerRole] = "objectPointer";
		roles_[PlacemarkPopularityRole] = "popularity";
		roles_[PlacemarkPopularityIndexRole] = "popularityIndex";
		roles_[PlacemarkCoodinateRole] = "coordinate";
		roles_[BackgroundRole] = "background";

	}

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
		using namespace Marble;
		if(role == CheckStateRole) {
			auto placemark = MarbleHelper::toPlacemark(QIdentityProxyModel::data(index, PlacemarkObjectPointerRole));
			if(placemark != 0) {
				if(placemark->isGloballyVisible()) {
					return QVariant(Qt::Checked);
				}
				else if(placemark->isVisible()) {
					return QVariant(Qt::PartiallyChecked);
				}
				else {
					return QVariant(Qt::Unchecked);
				}
			}
		}

		return QIdentityProxyModel::data(index, role);

	}

protected:
	QHash<int, QByteArray> roleNames() const {
		return roles_;
	}

private:
	QHash<int, QByteArray> roles_;
};
