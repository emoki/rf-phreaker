#pragma once
#include <QVariant>
#include "marble/geodata/data/GeoDataPlacemark.h"
#include "marble/geodata/parser/GeoDataTypes.h"

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
};