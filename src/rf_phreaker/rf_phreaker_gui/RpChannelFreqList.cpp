#include "rf_phreaker/rf_phreaker_gui/RpChannelFreqList.h"

//namespace rf_phreaker { namespace gui {

RpChannelFreqList::RpChannelFreqList(QObject *parent)
    : QObject(parent) {
    list_.append(new RpChannelFreq("1000", "1960.0", "UMTS_OPERATING_BAND_1", "WCDMA"));
    list_.append(new RpChannelFreq("1000", "1960.0", "UMTS_OPERATING_BAND_1", "WCDMA"));
    list_.append(new RpChannelFreq("1000", "1960.0", "UMTS_OPERATING_BAND_1", "WCDMA"));
    list_.append(new RpChannelFreq("1000", "1960.0", "UMTS_OPERATING_BAND_1", "WCDMA"));
}


QQmlListProperty<RpChannelFreq> RpChannelFreqList::ChannelFreqList() {
    return QQmlListProperty<RpChannelFreq>(this, &list_, &RpChannelFreqList::append,
                                         &RpChannelFreqList::count,
                                         &RpChannelFreqList::at,
                                         &RpChannelFreqList::clear);
}

void RpChannelFreqList::remove(int index) {
    if(index < list_.count()) {
        list_.removeAt(index);
        emit channelFreqListChanged();
    }
}

void RpChannelFreqList::append(QQmlListProperty<RpChannelFreq> *list, RpChannelFreq *item) {
    auto tmp = qobject_cast<RpChannelFreqList*>(list->object);
    if(tmp) {
        item->setParent(tmp);
        tmp->list_.append(item);
        tmp->channelFreqListChanged();
    }
}

RpChannelFreq* RpChannelFreqList::at(QQmlListProperty<RpChannelFreq> *list, int index) {
    auto tmp = qobject_cast<RpChannelFreqList*>(list->object);
    if(tmp) {
        return tmp->list_.at(index);
    }
    else
        return nullptr;
}

void RpChannelFreqList::clear(QQmlListProperty<RpChannelFreq> *list) {
    auto tmp = qobject_cast<RpChannelFreqList*>(list->object);
    if(tmp) {
        tmp->list_.clear();
        tmp->channelFreqListChanged();
    }
}

int RpChannelFreqList::count(QQmlListProperty<RpChannelFreq> *list) {
    auto tmp = qobject_cast<RpChannelFreqList*>(list->object);
    if(tmp)
        return tmp->list_.count();
    else
        return 0;
}


//}}
