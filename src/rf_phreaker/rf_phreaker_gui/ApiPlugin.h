#pragma once
#include <QtQml/qqml.h>
#include "rf_phreaker/rf_phreaker_gui/Api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/ApiMessage.h"
#include "rf_phreaker/rf_phreaker_gui/ChannelFreq.h"
#include "rf_phreaker/rf_phreaker_gui/CollectionInfoList.h"
#include "rf_phreaker/rf_phreaker_gui/CollectionInfoSearch.h"
#include "rf_phreaker/rf_phreaker_gui/RpDevice.h"
#include "rf_phreaker/rf_phreaker_gui/Gps.h"
#include "rf_phreaker/rf_phreaker_gui/Gsm.h"
#include "rf_phreaker/rf_phreaker_gui/Wcdma.h"
#include "rf_phreaker/rf_phreaker_gui/Lte.h"
#include "rf_phreaker/rf_phreaker_gui/Sweep.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"
#include "rf_phreaker/rf_phreaker_gui/Serialization.h"
#include "rf_phreaker/rf_phreaker_gui/FileSaveDialog.h"
#include "rf_phreaker/rf_phreaker_gui/ModelGroup.h"
#include "rf_phreaker/rf_phreaker_gui/MeasurementModel.h"
#include "rf_phreaker/rf_phreaker_gui/ProxyMeasurementModel.h"
#include "rf_phreaker/rf_phreaker_gui/RawLayer3Model.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleManager.h"
#include "rf_phreaker/rf_phreaker_gui/MarbleProxyModel.h"
#include "rf_phreaker/rf_phreaker_gui/SpectrumModel.h"
#include "rf_phreaker/rf_phreaker_gui/Spectrum3d.h"
#include "rf_phreaker/rf_phreaker_gui/Settings.h"
#include "rf_phreaker/rf_phreaker_gui/FreqLimits.h"
#include "rf_phreaker/rf_phreaker_gui/CollectionInfoSearch.h"
#include "marble/geodata/data/GeoDataPlacemark.h"

//namespace rf_phreaker { namespace gui {

Q_DECLARE_METATYPE(CollectionInfo*)
Q_DECLARE_METATYPE(Base*)
Q_DECLARE_METATYPE(RawLayer3Model*)
Q_DECLARE_METATYPE(GenericMeasurement*)
Q_DECLARE_METATYPE(Gsm*)
Q_DECLARE_METATYPE(Wcdma*)
Q_DECLARE_METATYPE(Lte*)
Q_DECLARE_METATYPE(Sweep*)
Q_DECLARE_METATYPE(Cw*)
Q_DECLARE_METATYPE(Marble::GeoDataPlacemark*)
Q_DECLARE_METATYPE(MeasurementModel::MeasurementRole)
Q_DECLARE_METATYPE(MeasurementModel::MeasurementColumn)
Q_DECLARE_METATYPE(CwMeasurementModel::CwMeasurementRole)
Q_DECLARE_METATYPE(CwMeasurementModel::CwMeasurementColumn)
Q_DECLARE_METATYPE(Settings::CollectionProfile)
Q_DECLARE_METATYPE(CollectionInfoSearcher)

QObject* ApiInterfaceSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine) {
	Q_UNUSED(engine);
	Q_UNUSED(scriptEngine);
	return Api::instance();
}

QObject* SettingsSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine) {
	Q_UNUSED(engine);
	Q_UNUSED(scriptEngine);
	return Settings::instance();
}

QObject* MarbleLayersSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine) {
	Q_UNUSED(engine);
	Q_UNUSED(scriptEngine);
	auto marble = &MarbleLayers::instance();
	static std::once_flag once_flag_;
	std::call_once(once_flag_, [&]() {
		engine->setObjectOwnership(marble, QQmlEngine::CppOwnership);
	});
	return marble;
}

void registerQmlTypes()
{
	QLatin1String uri("RfPhreaker");

	qmlRegisterSingletonType<Api>(uri.latin1(), 1, 0, "Api", ApiInterfaceSingletonTypeProvider);
	qmlRegisterType<ApiTypes>(uri.latin1(), 1, 0, "ApiTypes");
	qmlRegisterType<ApiMessage>(uri.latin1(), 1, 0, "ApiMessage");
	qmlRegisterType<ChannelFreq>(uri.latin1(), 1, 0, "ChannelFreq");
	qmlRegisterType<CollectionInfo>(uri.latin1(), 1, 0, "CollectionInfo");
	qmlRegisterType<CollectionInfoList>(uri.latin1(), 1, 0, "CollectionInfoList");
	qmlRegisterType<CollectionInfoSearch>(uri.latin1(), 1, 0, "CollectionInfoSearch");
	qmlRegisterType<RpDevice>(uri.latin1(), 1, 0, "Device");
	qmlRegisterType<Gps>(uri.latin1(), 1, 0, "Gps");
	qmlRegisterType<Gsm>(uri.latin1(), 1, 0, "Gsm");
	qmlRegisterType<Wcdma>(uri.latin1(), 1, 0, "Wcdma");
	qmlRegisterType<Lte>(uri.latin1(), 1, 0, "Lte");
	qmlRegisterType<Sweep>(uri.latin1(), 1, 0, "Sweep");
	qmlRegisterType<GenericMeasurement>(uri.latin1(), 1, 0, "GenericMeasurement");
	qmlRegisterType<Sweep>(uri.latin1(), 1, 0, "Base");
	qmlRegisterType<FileSaveDialog>(uri.latin1(), 1, 0, "FileSaveDialog");
	qmlRegisterType<MeasurementModel>(uri.latin1(), 1, 0, "MeasurementModel");
	qmlRegisterType<CwMeasurementModel>(uri.latin1(), 1, 0, "CwMeasurementModel");
	qmlRegisterType<SpectrumModel>(uri.latin1(), 1, 0, "SpectrumModel");
	qmlRegisterType<Spectrum3d>(uri.latin1(), 1, 0, "Spectrum3d");
	qmlRegisterType<FreqLimits>(uri.latin1(), 1, 0, "FreqLimits");
	qmlRegisterType<FilterProxyMeasurementModel>(uri.latin1(), 1, 0, "FilterProxyMeasurementModel");
	qmlRegisterType<BarGraphProxyMeasurementModel>(uri.latin1(), 1, 0, "BarGraphProxyMeasurementModel");
	qmlRegisterType<MarbleManager>(uri.latin1(), 1, 0, "MarbleManager");
	qmlRegisterType<MarbleProxyModel>(uri.latin1(), 1, 0, "MarbleProxyModel");
	qmlRegisterType<RawLayer3Model>(uri.latin1(), 1, 0, "RawLayer3Model");

	qmlRegisterSingletonType<Settings>(uri.latin1(), 1, 0, "GuiSettings", SettingsSingletonTypeProvider);
	qmlRegisterSingletonType<MarbleLayerManager>(uri.latin1(), 1, 0, "MarbleLayerManager", MarbleLayersSingletonTypeProvider);

	qRegisterMetaTypeStreamOperators<rf_phreaker::channel_freq>("channel_freq");
	qRegisterMetaTypeStreamOperators<ApiTypes::Tech>("ApiTech");

	qRegisterMetaType<Marble::GeoDataPlacemark*>();
	qRegisterMetaType<CollectionInfoSearcher>();
}

//}}
