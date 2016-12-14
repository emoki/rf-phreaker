#pragma once
#include <QVariant>
#include "marble/geodata/data/GeoDataPlacemark.h"
#include "marble/geodata/parser/GeoDataTypes.h"
#include "marble/MarbleMath.h"
#include "marble/MarbleModel.h"

class MarbleHelper {
public:
	static Marble::GeoDataPlacemark* toPlacemark(const QVariant &var) {
		using namespace Marble;
		auto geoData = var.value<GeoDataObject*>();
		if(geoData != nullptr && geoData->nodeType() == GeoDataTypes::GeoDataPlacemarkType) {
			return static_cast<GeoDataPlacemark*>(geoData);
		}
		else
			return nullptr;
	}

	static bool isPositionTrackingRelated(Marble::GeoDataPlacemark* p) {
		return p->name() == "Current Position" || p->name() == "Current Track";
	}

	static double calculateDistanceMeters(const Marble::GeoDataCoordinates &a, const Marble::GeoDataCoordinates &b,
	    const Marble::MarbleModel &model) {
		return model.planetRadius() * Marble::distanceSphere(a, b);
	}

	static double calculateDistanceMeters(qreal lon1, qreal lat1, qreal lon2, qreal lat2, const Marble::MarbleModel &model) {
		return model.planetRadius() * Marble::distanceSphere(lon1, lat1, lon2, lat2);
	}
};
