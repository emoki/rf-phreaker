#pragma once
#include <QtQml/qqml.h>
#include "Rp.h"

void registerQmlTypes()
{
    QLatin1String uri("RfPhreaker");

    //qmlRegisterUncreatableType<RpChannelFreq>(uri.latin1(), 1, 0, "RpChannelFreq", QLatin1String("Use the Context property instead."));
    //qmlRegisterUncreatableType<RpChannelFreqList>(uri.latin1(), 1, 0, "RpChannelFreqList", QLatin1String("Use the Context property instead."));

    qmlRegisterType<RpConversion>(uri.latin1(), 1, 0, "RpConversion");
    qmlRegisterType<RpChannelFreq>(uri.latin1(), 1, 0, "RpChannelFreq");
    qmlRegisterType<RpChannelFreqList>(uri.latin1(), 1, 0, "RpChannelFreqList");
    qmlRegisterType<RpChannelFreqConversion>(uri.latin1(), 1, 0, "RpChannelFreqConversion");
}

