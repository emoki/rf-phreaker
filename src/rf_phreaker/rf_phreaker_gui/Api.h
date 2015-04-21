#pragma once
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QMutex>
#include <QTimer>
#include "rf_phreaker/rf_phreaker_gui/CollectionInfoList.h"
#include "rf_phreaker/rf_phreaker_gui/Device.h"
#include "rf_phreaker/rf_phreaker_gui/Gps.h"
#include "rf_phreaker/rf_phreaker_gui/Gsm.h"
#include "rf_phreaker/rf_phreaker_gui/Wcdma.h"
#include "rf_phreaker/rf_phreaker_gui/Lte.h"
#include "rf_phreaker/rf_phreaker_gui/Sweep.h"

//namespace rf_phreaker { namespace gui {

class ApiThread;

class Api : public QObject {
	Q_OBJECT
	Q_PROPERTY(ApiTypes::DeviceStatus status READ status WRITE setStatus NOTIFY statusChanged)
	Q_PROPERTY(QString statusStr READ statusStr NOTIFY statusStrChanged)
	Q_PROPERTY(CollectionInfoList* collectionList READ collectionList WRITE setCollectionList NOTIFY collectionListChanged)
	Q_PROPERTY(QStringList log READ log NOTIFY logChanged)
	Q_PROPERTY(QStringList messages READ messages NOTIFY messagesChanged)
	Q_PROPERTY(Device* connectedDevice READ connectedDevice NOTIFY connectedDeviceChanged)
	Q_PROPERTY(Gps* gps READ gps NOTIFY gpsChanged)
	Q_PROPERTY(QList<QObject*> wcdmaList READ wcdmaList NOTIFY wcdmaListChanged)
	Q_PROPERTY(QList<QObject*> lteList READ lteList NOTIFY lteListChanged)
	//	Q_PROPERTY( READ WRITE set NOTIFY Changed)

	Q_PROPERTY(QStringList availableDevices READ availableDevices NOTIFY availableDevicesChanged)
	//Q_PROPERTY(QString deviceSerial READ deviceSerial WRITE setDeviceSerial NOTIFY deviceSerialChanged)
	//Q_PROPERTY( READ NOTIFY Changed)
	//	Q_PROPERTY( READ WRITE set NOTIFY Changed)

public:
	~Api();
	static Api* instance();

	ApiTypes::DeviceStatus status() { return status_; }
	QString statusStr() { return ApiTypes::toQString(status_); }
	CollectionInfoList* collectionList() { return collectionList_; }
	QStringList log() { return log_; }
	QStringList messages() { return messages_; }
	//QString deviceSerial() const { return deviceSerial_; }
	Device* connectedDevice() { return &connectedDevice_; }
	Gps* gps() { return &gps_; }
	QList<QObject*> wcdmaList() { return wcdmaList_; }
	QList<QObject*> lteList() { return lteList_; }
	QStringList availableDevices() { return availableDevices_; }


	void setCollectionList(const CollectionInfoList *list) {
		collectionList_->setList(list->qlist());
		emit collectionListChanged();
	}
	void setStatus(ApiTypes::DeviceStatus s) {
		if(status_ != s) {
			status_ = s;
			emit statusChanged();
			emit statusStrChanged();
		}
	}

	Q_INVOKABLE void listDevices();
	Q_INVOKABLE void connectDevice(QString qserial = "");
	Q_INVOKABLE void disconnectDevice();
	Q_INVOKABLE void startCollection();
	Q_INVOKABLE void stopCollection();

signals:
	void collectionListChanged();
	void logChanged();
	void messagesChanged();
	void statusChanged();
	void statusStrChanged();
	void availableDevicesChanged();
	void connectedDeviceChanged();
	void gpsChanged();
	void wcdmaListChanged();
	void lteListChanged();

	// Signals for state machine
	void numDevicesConnected(int numDevices);
	void deviceConnected();
	void deviceDisconnected();
	void scanningStarted();
	void scanningStopped();

protected:
	bool event(QEvent *);

private slots:
	void emitSignals();

private:
	explicit Api(QObject *parent = 0);
	void handle_message(rp_status status, const QString &s);

	static Api *instance_;
	static QMutex instance_mutex_;
	ApiTypes::DeviceStatus status_;
	CollectionInfoList *collectionList_;
	QStringList availableDevices_;
	QStringList log_;
	QStringList messages_;
	//QString deviceSerial_;
	Device connectedDevice_;
	Gps gps_;
	QList<QObject*> wcdmaList_;
	QList<QObject*> lteList_;

	QMap<int64_t, QObject*> wcdmaMap_;
	QMap<int64_t, QObject*> lteMap_;

	// Perhaps in the future we allow for multiple devices.
	// This for the most part should be opaque to the user.
	rp_callbacks callbacks_;

	ApiThread *thread_;

	QTimer *updateTimer_;
	bool canUpdateLog_;
	bool canUpdateMessages_;
	bool canUpdateDevice_;
	bool canUpdateGps_;
	bool canUpdateGsm_;
	bool canUpdateWcdma_;
	bool canUpdateLte_;
};

//}}
