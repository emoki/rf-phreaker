#pragma once

#include <QtQml/QQmlListProperty>
#include "rf_phreaker/rf_phreaker_gui/RpChannelFreq.h"

//namespace rf_phreaker { namespace gui {

class RpChannelFreqList : public QObject {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<RpChannelFreq> channelFreqList READ ChannelFreqList NOTIFY channelFreqListChanged)

signals:
    void channelFreqListChanged();

public:
    RpChannelFreqList(QObject *parent = 0);

    QQmlListProperty<RpChannelFreq> ChannelFreqList();

    Q_INVOKABLE void remove(int index);

    static void append(QQmlListProperty<RpChannelFreq> *list, RpChannelFreq *item);
    static RpChannelFreq* at(QQmlListProperty<RpChannelFreq> *list, int index);
    static void clear(QQmlListProperty<RpChannelFreq> *list);
    static int count(QQmlListProperty<RpChannelFreq> *list);

private:
    QList<RpChannelFreq*> list_;
};

//}}
