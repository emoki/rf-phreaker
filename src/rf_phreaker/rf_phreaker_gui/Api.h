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
#include "rf_phreaker/rf_phreaker_gui/Settings.h"

//namespace rf_phreaker { namespace gui {

class ApiThread;

class Api : public QObject {
	Q_OBJECT
	Q_PROPERTY(ApiTypes::DeviceStatus deviceStatus READ deviceStatus WRITE setDeviceStatus NOTIFY deviceStatusChanged)
	Q_PROPERTY(QString deviceStatusStr READ deviceStatusStr NOTIFY deviceStatusStrChanged)
	Q_PROPERTY(ApiTypes::ConnectionStatus connectionStatus READ connectionStatus WRITE setConnectionStatus NOTIFY connectionStatusChanged)
	Q_PROPERTY(QString connectionStatusStr READ connectionStatusStr NOTIFY connectionStatusStrChanged)
	Q_PROPERTY(CollectionInfoList* scanList READ scanList WRITE setScanList NOTIFY scanListChanged)
	Q_PROPERTY(CollectionInfoList* backgroundScanList READ backgroundScanList WRITE setBackgroundScanList NOTIFY backgroundScanListChanged)
	Q_PROPERTY(QStringList log READ log NOTIFY logChanged)
	Q_PROPERTY(QStringList messages READ messages NOTIFY messagesChanged)
	Q_PROPERTY(Device* connectedDevice READ connectedDevice NOTIFY connectedDeviceChanged)
	Q_PROPERTY(Gps* gps READ gps NOTIFY gpsChanged)
	Q_PROPERTY(QList<QObject*> wcdmaList READ wcdmaList NOTIFY wcdmaListChanged)
	Q_PROPERTY(QList<QObject*> lteList READ lteList NOTIFY lteListChanged)
	//Q_PROPERTY(bool canRecordData READ canRecordData WRITE setCanRecordData NOTIFY canRecordDataChanged)
	//	Q_PROPERTY( READ WRITE set NOTIFY Changed)

	Q_PROPERTY(QStringList availableDevices READ availableDevices NOTIFY availableDevicesChanged)
	Q_PROPERTY(QString deviceSerial READ deviceSerial WRITE setDeviceSerial NOTIFY deviceSerialChanged)
	//Q_PROPERTY( READ NOTIFY Changed)
	//	Q_PROPERTY( READ WRITE set NOTIFY Changed)

public:
	~Api();
	static Api* instance();

	ApiTypes::DeviceStatus deviceStatus() { return deviceStatus_; }
	QString deviceStatusStr() { return ApiTypes::toQString(deviceStatus_); }
	ApiTypes::ConnectionStatus connectionStatus() { return connectionStatus_; }
	QString connectionStatusStr() { return ApiTypes::toQString(connectionStatus_); }
	CollectionInfoList* scanList() { return scanList_; }
	CollectionInfoList* backgroundScanList() { return backgroundScanList_; }
	QStringList log() { return log_; }
	QStringList messages() { return messages_; }
	QString deviceSerial() const { return deviceSerial_; }
	Device* connectedDevice() { return &connectedDevice_; }
	Gps* gps() { return &gps_; }
	QList<QObject*> wcdmaList() { return wcdmaList_; }
	QList<QObject*> lteList() { return lteList_; }
	QStringList availableDevices() { return availableDevices_; }
	//bool canRecordData() { return canRecordData_; }

	void setScanList(const CollectionInfoList *list) {
		scanList_->setList(list->qlist());
		emit scanListChanged();
	}

	void setBackgroundScanList(const CollectionInfoList *list) {
		backgroundScanList_->setList(list->qlist());
		emit backgroundScanListChanged();
	}

	void setDeviceStatus(ApiTypes::DeviceStatus s) {
		if(deviceStatus_ != s) {
			deviceStatus_ = s;
			emit deviceStatusChanged();
			emit deviceStatusStrChanged();
		}
	}

	void setConnectionStatus(ApiTypes::ConnectionStatus s) {
		if(connectionStatus_ != s) {
			connectionStatus_ = s;
			emit connectionStatusChanged();
			emit connectionStatusStrChanged();
		}
	}

//	void setCanRecordData(bool r) {
//		if(canRecordData_ != r) {
//			canRecordData_ = r;
//			emit canRecordDataChanged();
//		}
//	}

	void setDeviceSerial(QString s) {
		if(deviceSerial_ != s) {
			deviceSerial_ = s;
			emit deviceSerialChanged();
		}
	}

	Q_INVOKABLE void initializeApi();
	Q_INVOKABLE void listDevices();
	Q_INVOKABLE void connectDevice(QString qserial = "");
	Q_INVOKABLE void disconnectDevice();
	Q_INVOKABLE void startCollection();
	Q_INVOKABLE void stopCollection();
	Q_INVOKABLE void updateLicense();
	Q_INVOKABLE void cleanUpApi();

signals:
	void scanListChanged();
	void backgroundScanListChanged();
	void logChanged();
	void messagesChanged();
	void deviceStatusChanged();
	void deviceStatusStrChanged();
	void connectionStatusChanged();
	void connectionStatusStrChanged();
	void availableDevicesChanged();
	void connectedDeviceChanged();
	void gpsChanged();
	void wcdmaListChanged();
	void lteListChanged();
	//void canRecordDataChanged();
	void deviceSerialChanged();

	// Signals for state machine
	void numDevicesConnected(int numDevices);
	void deviceConnected();
	void deviceDisconnected();
	void scanningStarted();
	void scanningStopped();
	void apiInitialized();
	void licenseUpdateSucceeded();
	void licenseUpdateFailed();
	void errorMessage(int status, QString msg);
	void message(int status, QString msg);

protected:
	bool event(QEvent *);

private slots:
	void emitSignals();

private:
	explicit Api(QObject *parent = 0);
	void handle_message(rp_status status, const QString &s);

	static Api *instance_;
	static QMutex instance_mutex_;
	ApiTypes::DeviceStatus deviceStatus_;
	ApiTypes::ConnectionStatus connectionStatus_;
	CollectionInfoList *scanList_;
	CollectionInfoList *backgroundScanList_;
	QStringList availableDevices_;
	QStringList log_;
	QStringList messages_;
	QStringList error_messages_;
	QString deviceSerial_;
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

	Settings settings_;
	SettingsIO settingsIO_;

	//bool canRecordData_;
};

//}}
