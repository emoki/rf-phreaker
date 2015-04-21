#pragma once
#include <QtQml/qqml.h>
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/ChannelFreq.h"
#include "rf_phreaker/rf_phreaker_gui/CollectionInfoList.h"
#include "rf_phreaker/rf_phreaker_gui/CollectionInfoSearch.h"
#include "rf_phreaker/rf_phreaker_gui/Api.h"
#include "rf_phreaker/rf_phreaker_gui/Device.h"
#include "rf_phreaker/rf_phreaker_gui/Gps.h"
#include "rf_phreaker/rf_phreaker_gui/Gsm.h"
#include "rf_phreaker/rf_phreaker_gui/Wcdma.h"
#include "rf_phreaker/rf_phreaker_gui/Lte.h"
#include "rf_phreaker/rf_phreaker_gui/Sweep.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"

//namespace rf_phreaker { namespace gui {

QObject* ApiInterfaceSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine) {
	Q_UNUSED(engine);
	Q_UNUSED(scriptEngine);
	return Api::instance();
}

void registerQmlTypes()
{
	QLatin1String uri("RfPhreaker");

	qmlRegisterSingletonType<Api>(uri.latin1(), 1, 0, "Api", ApiInterfaceSingletonTypeProvider);
	qmlRegisterType<ApiTypes>(uri.latin1(), 1, 0, "ApiTypes");
	qmlRegisterType<CollectionInfo>(uri.latin1(), 1, 0, "CollectionInfo");
	qmlRegisterType<CollectionInfoList>(uri.latin1(), 1, 0, "CollectionInfoList");
	qmlRegisterType<CollectionInfoSearch>(uri.latin1(), 1, 0, "CollectionInfoSearch");
	qmlRegisterType<Device>(uri.latin1(), 1, 0, "Device");
	qmlRegisterType<Gps>(uri.latin1(), 1, 0, "Gps");
	qmlRegisterType<Gsm>(uri.latin1(), 1, 0, "Gsm");
	qmlRegisterType<Wcdma>(uri.latin1(), 1, 0, "Wcdma");
	qmlRegisterType<Lte>(uri.latin1(), 1, 0, "Lte");
	qmlRegisterType<Sweep>(uri.latin1(), 1, 0, "Sweep");
	qmlRegisterType<Sweep>(uri.latin1(), 1, 0, "Base");
}

