#pragma once
#include <QDebug>
#include <QEvent>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/Device.h"
#include "rf_phreaker/rf_phreaker_gui/Gps.h"
#include "rf_phreaker/rf_phreaker_gui/Gsm.h"
#include "rf_phreaker/rf_phreaker_gui/Wcdma.h"
#include "rf_phreaker/rf_phreaker_gui/Lte.h"
#include "rf_phreaker/rf_phreaker_gui/Sweep.h"

//namespace rf_phreaker { namespace gui {


template<typename T>
class TypeInterface {
public:
	static QEvent::Type getType() {
		static auto t = QEvent::registerEventType();
		return static_cast<QEvent::Type>(t);
	}
};

// Thread worker events /////////////
class ExitEvent : public QEvent, public TypeInterface<ExitEvent> {
public:
	ExitEvent() : QEvent(getType()) {}
};

class InitializeApiEvent : public QEvent, public TypeInterface<InitializeApiEvent> {
public:
	InitializeApiEvent(rp_callbacks *rp_callbacks) : QEvent(getType()), callbacks_(rp_callbacks) {}
	rp_callbacks *callbacks_;
};

class ApiInitializedEvent : public QEvent, public TypeInterface<ApiInitializedEvent> {
public:
	ApiInitializedEvent() : QEvent(getType()) {}
};

class CleanUpApiEvent : public QEvent, public TypeInterface<CleanUpApiEvent> {
public:
	CleanUpApiEvent() : QEvent(getType()) {}
};

class ApiCleanedUpEvent : public QEvent, public TypeInterface<ApiCleanedUpEvent> {
public:
	ApiCleanedUpEvent() : QEvent(getType()) {}
};

class ListDevicesEvent : public QEvent, public TypeInterface<ListDevicesEvent> {
public:
	ListDevicesEvent() : QEvent(getType()) {}
};

class AvailableDevicesEvent : public QEvent, public TypeInterface<AvailableDevicesEvent> {
public:
	AvailableDevicesEvent(QStringList deviceList) : QEvent(getType()), deviceList_(deviceList) {}
	QStringList deviceList() { return deviceList_; }
private:
	QStringList deviceList_;
};

class ConnectDeviceEvent : public QEvent, public TypeInterface<ConnectDeviceEvent> {
public:
	ConnectDeviceEvent(QString serial) : QEvent(getType()), serial_(serial) {}
	QString serial() { return serial_; }
private:
	QString serial_;
};

class DisconnectDeviceEvent : public QEvent, public TypeInterface<DisconnectDeviceEvent> {
public:
	DisconnectDeviceEvent() : QEvent(getType()) {}
};

class StartCollectionEvent : public QEvent, public TypeInterface<StartCollectionEvent> {
public:
	StartCollectionEvent(const api_storage<rp_operating_band, rp_operating_band_group> &sweep,
					const api_storage<rp_frequency_type, rp_frequency_group> &raw,
					const QMap<ApiTypes::Tech, api_storage<rp_frequency_band, rp_frequency_band_group>> &techs)
		: QEvent(getType())
		, sweep_(sweep)
		, raw_(raw)
		, techs_(techs)
	{}

	api_storage<rp_operating_band, rp_operating_band_group>& sweep() { return sweep_; }
	api_storage<rp_frequency_type, rp_frequency_group>& raw() { return raw_; }
	QMap<ApiTypes::Tech, api_storage<rp_frequency_band, rp_frequency_band_group>>& techs() { return techs_; }

private:
	api_storage<rp_operating_band, rp_operating_band_group> sweep_;
	api_storage<rp_frequency_type, rp_frequency_group> raw_;
	QMap<ApiTypes::Tech, api_storage<rp_frequency_band, rp_frequency_band_group>> techs_;
};

class CollectionStartedEvent : public QEvent, public TypeInterface<CollectionStartedEvent> {
public:
	CollectionStartedEvent() : QEvent(getType()) {}
};

class StopCollectionEvent : public QEvent, public TypeInterface<StopCollectionEvent> {
public:
	StopCollectionEvent() : QEvent(getType()) {}
};

class CollectionStoppedEvent : public QEvent, public TypeInterface<CollectionStoppedEvent> {
public:
	CollectionStoppedEvent() : QEvent(getType()) {}
};

class DeviceDisconnectedEvent : public QEvent, public TypeInterface<DeviceDisconnectedEvent> {
public:
	DeviceDisconnectedEvent() : QEvent(getType()) {}
};



class LogUpdateEvent : public QEvent, public TypeInterface<LogUpdateEvent> {
public:
	LogUpdateEvent(const QString &msg) : QEvent(getType()), msg_(msg) {}
	QString& msg() { return msg_; }
private:
	QString msg_;
};

class MessageUpdateEvent : public QEvent, public TypeInterface<MessageUpdateEvent> {
public:
	MessageUpdateEvent(rp_status status, const QString &msg) : QEvent(getType()), status_(status), msg_(msg) {}
	QString& msg() { return msg_; }
	rp_status status() { return status_; }
private:
	rp_status status_;
	QString msg_;
};

class DeviceUpdateEvent : public QEvent, public TypeInterface<DeviceUpdateEvent> {
public:
	DeviceUpdateEvent(const rp_device_info &device) : QEvent(getType()), device_(device) {}
	rp_device_info& device() { return device_; }
private:
	rp_device_info device_;
};

class GpsUpdateEvent : public QEvent, public TypeInterface<GpsUpdateEvent> {
public:
	GpsUpdateEvent(const rp_gps &gps) : QEvent(getType()), gps_(gps) {}
	rp_gps& gps() { return gps_; }
private:
	rp_gps gps_;
};

class WcdmaUpdateEvent : public QEvent, public TypeInterface<WcdmaUpdateEvent> {
public:
	WcdmaUpdateEvent(const rp_base *base, const rp_wcdma *wcdma, int num_wcdma)
		: QEvent(getType())
		, base_(*base) {
		for(int i = 0; i < num_wcdma; ++i)
			list_.push_back(wcdma[i]);
	}
	rp_base& base() { return base_; }
	QList<rp_wcdma>& wcdmaList() { return list_; }
private:
	rp_base base_;
	QList<rp_wcdma> list_;
};

class LteUpdateEvent : public QEvent, public TypeInterface<LteUpdateEvent> {
public:
	LteUpdateEvent(const rp_base *base, const rp_lte *lte, int num_lte)
		: QEvent(getType())
		, base_(*base) {
		for(int i = 0; i < num_lte; ++i)
			list_.push_back(lte[i]);
	}
	rp_base& base() { return base_; }
	QList<rp_lte>& lteList() { return list_; }
private:
	rp_base base_;
	QList<rp_lte> list_;
};

//}}
