#pragma once
#include <atomic>
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QMutex>
#include <QTimer>
#include <QFile>
#include "rf_phreaker/rf_phreaker_gui/CollectionInfoList.h"
#include "rf_phreaker/rf_phreaker_gui/RpDevice.h"
#include "rf_phreaker/rf_phreaker_gui/Gps.h"
#include "rf_phreaker/rf_phreaker_gui/Gsm.h"
#include "rf_phreaker/rf_phreaker_gui/Wcdma.h"
#include "rf_phreaker/rf_phreaker_gui/Lte.h"
#include "rf_phreaker/rf_phreaker_gui/Sweep.h"
#include "rf_phreaker/rf_phreaker_gui/Settings.h"
#include "rf_phreaker/rf_phreaker_gui/IO.h"
#include "rf_phreaker/rf_phreaker_gui/Stats.h"
#include "rf_phreaker/rf_phreaker_gui/ModelGroup.h"
#include "rf_phreaker/rf_phreaker_gui/MeasurementModel.h"
#include "rf_phreaker/rf_phreaker_gui/ProxyMeasurementModel.h"
#include "rf_phreaker/rf_phreaker_gui/ApiMessage.h"
#include "rf_phreaker/rf_phreaker_gui/SpectrumManager.h"
#include "rf_phreaker/rf_phreaker_gui/Utility.h"
#include "rf_phreaker/protobuf_specific/rf_phreaker_serialization.h"
#include <google/protobuf/io/zero_copy_stream_impl.h>
//namespace rf_phreaker { namespace gui {

class ApiThread;

class Api : public QObject {
	Q_OBJECT
	Q_PROPERTY(ApiTypes::DeviceStatus deviceStatus READ deviceStatus WRITE setDeviceStatus NOTIFY deviceStatusChanged)
	Q_PROPERTY(QString deviceStatusStr READ deviceStatusStr NOTIFY deviceStatusStrChanged)
	Q_PROPERTY(ApiTypes::ConnectionStatus connectionStatus READ connectionStatus WRITE setConnectionStatus NOTIFY connectionStatusChanged)
	Q_PROPERTY(QString connectionStatusStr READ connectionStatusStr NOTIFY connectionStatusStrChanged)
	Q_PROPERTY(CollectionInfoList* scanList READ scanList NOTIFY scanListChanged)
	Q_PROPERTY(CollectionInfoList* backgroundScanList READ backgroundScanList NOTIFY backgroundScanListChanged)
	Q_PROPERTY(QList<QObject*> log READ log NOTIFY logChanged)
	Q_PROPERTY(QList<QObject*> errors READ errors NOTIFY errorsChanged)
	Q_PROPERTY(ApiMessage* newestError READ newestError NOTIFY errorsChanged)
	Q_PROPERTY(QList<QObject*> messages READ messages NOTIFY messagesChanged)
	Q_PROPERTY(ApiMessage* newestMessage READ newestMessage NOTIFY messagesChanged)
	Q_PROPERTY(RpDevice* connectedDevice READ connectedDevice NOTIFY connectedDeviceChanged)
	Q_PROPERTY(Gps* gps READ gps NOTIFY gpsChanged)
	Q_PROPERTY(QStringList availableDevices READ availableDevices NOTIFY availableDevicesChanged)
	Q_PROPERTY(QString deviceSerial READ deviceSerial WRITE setDeviceSerial NOTIFY deviceSerialChanged)
	Q_PROPERTY(QString collectionFilename READ collectionFilename WRITE setCollectionFilename NOTIFY collectionFilenameChanged)
	Q_PROPERTY(ModelGroup* allTechModels READ allTechModels NOTIFY allTechModelsChanged)
	Q_PROPERTY(ModelGroup* gsmModels READ gsmModels NOTIFY gsmModelsChanged)
	Q_PROPERTY(ModelGroup* wcdmaModels READ wcdmaModels NOTIFY wcdmaModelsChanged)
	Q_PROPERTY(ModelGroup* lteModels READ lteModels NOTIFY lteModelsChanged)
	Q_PROPERTY(MeasurementModel* cwModel READ cwModel NOTIFY cwModelChanged)
	Q_PROPERTY(SpectrumManager* spectrumManager READ spectrumManager NOTIFY spectrumManagerChanged)

public:
	Q_INVOKABLE void initializeApi();
	Q_INVOKABLE void listDevices();
	Q_INVOKABLE void connectDevice(QString qserial = "");
	Q_INVOKABLE void disconnectDevice();
	Q_INVOKABLE void startCollection();
	Q_INVOKABLE void stopCollection();
	Q_INVOKABLE void updateLicense();
	Q_INVOKABLE void cleanUpApi();
	Q_INVOKABLE bool openCollectionFile();
	Q_INVOKABLE void closeCollectionFile();
	Q_INVOKABLE void convertRpf(QString filename);
	Q_INVOKABLE QString getColorTheme(Base *b);
	Q_INVOKABLE MeasurementModel* getSweepModel(Base *b);
	Q_INVOKABLE void addMessageAsync(QString details, int status = 0) {
		QMetaObject::invokeMethod(Api::instance(), "addMessage",
			Qt::QueuedConnection, Q_ARG(QString, details), Q_ARG(int, status));
	}
	Q_INVOKABLE void addMessage(QString details, int status = 0) {
		messages_.prepend(new ApiMessage(static_cast<rp_status>(status), "", details));
		emit messagesChanged();
	}
	Q_INVOKABLE void saveScanList();

signals:
	void scanListChanged();
	void backgroundScanListChanged();
	void logChanged();
	void messagesChanged();
	void errorsChanged();
	void deviceStatusChanged();
	void deviceStatusStrChanged();
	void connectionStatusChanged();
	void connectionStatusStrChanged();
	void availableDevicesChanged();
	void connectedDeviceChanged();
	void gpsChanged();
	void deviceSerialChanged();
	void collectionFilenameChanged();
	void allTechModelsChanged();
	void gsmModelsChanged();
	void wcdmaModelsChanged();
	void lteModelsChanged();
	void cwModelChanged();
	void spectrumManagerChanged();


	// Signals for state machine
	void numDevicesConnected(int numDevices);
	void deviceConnected();
	void deviceDisconnected();
	void scanningStarted();
	void scanningStopped();
	void apiInitialized();
	void licenseUpdateSucceeded();
	void licenseUpdateFailed();
	void errorReinitialize();
	void errorGoIdle();

public slots:
	void findFreqMinMax();

public:
	~Api();
	static Api* instance();

	ApiTypes::DeviceStatus deviceStatus() { return deviceStatus_; }
	QString deviceStatusStr() { return ApiTypes::toQString(deviceStatus_); }
	ApiTypes::ConnectionStatus connectionStatus() { return connectionStatus_; }
	QString connectionStatusStr() { return ApiTypes::toQString(connectionStatus_); }
	CollectionInfoList* scanList() { return &scanList_; }
	CollectionInfoList* backgroundScanList() { return &backgroundScanList_; }
	QList<QObject*> log() { return log_; }
	QList<QObject*> messages() { return messages_; }
	ApiMessage* newestMessage() { return messages_.isEmpty() ? new ApiMessage(RP_STATUS_OK, "", "No error.") : static_cast<ApiMessage*>(messages_.front()); }
	QList<QObject*> errors() { return errors_; }
	ApiMessage* newestError() { return errors_.isEmpty() ? new ApiMessage(RP_STATUS_OK, "", "No error.") : static_cast<ApiMessage*>(errors_.front()); }
	QString deviceSerial() const { return deviceSerial_; }
	QString collectionFilename() const { return collectionFilename_; }
	RpDevice* connectedDevice() { return &connectedDevice_; }
	Gps* gps() { return &gps_; }
	QStringList availableDevices() { return availableDevices_; }
	ModelGroup* allTechModels() { return &allTechModels_; }
	ModelGroup* gsmModels() { return &gsmModels_; }
	ModelGroup* wcdmaModels() { return &wcdmaModels_; }
	ModelGroup* lteModels() { return &lteModels_; }
	SpectrumManager* spectrumManager() { return &spectrumManager_; }
	MeasurementModel* cwModel() { return &cwModel_; }

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

	void setDeviceSerial(QString s) {
		if(deviceSerial_ != s) {
			deviceSerial_ = s;
			emit deviceSerialChanged();
		}
	}

	void setCollectionFilename(QString s) {
		if(collectionFilename_ != s) {
			collectionFilename_ = s;
			emit collectionFilenameChanged();
		}
	}

protected:
	bool event(QEvent *);

private:
	explicit Api(QObject *parent = 0);
	void handle_message(const ApiMessage &msg);
	void close_collection_file(); // Handled internally using the event loop so we don't have to worry about threading issues.
	void clearModels();
	void updateModels();
	void appendLog(const QString &s);

	static Api *instance_;
	static QMutex instance_mutex_;
	ApiTypes::DeviceStatus deviceStatus_;
	ApiTypes::ConnectionStatus connectionStatus_;
	CollectionInfoList scanList_;
	CollectionInfoList backgroundScanList_;
	QStringList availableDevices_;
	QList<QObject*> log_;
	QList<QObject*> errors_;
	QList<QObject*> messages_;
	QString deviceSerial_;
	QString collectionFilename_;
	RpDevice connectedDevice_;
	Gps gps_;

	// Perhaps in the future we allow for multiple devices.
	// This for the most part should be opaque to the user.
	rp_callbacks callbacks_;

	ApiThread *thread_;

	std::atomic_bool canRecordData_;
	std::atomic_bool shouldUpdateLog_;

	rf_phreaker::protobuf::update_pb update_pb_;
	rf_phreaker::gps current_gps_;

	QFile output_qfile_;
	std::unique_ptr<google::protobuf::io::FileOutputStream> output_file_;

	IO api_debug_output_;
	bool apiOutput_;
	bool isSpectrumLogged_;

	Stats stats_;

	rf_phreaker::operating_band_range_specifier band_specifier_;
	MeasurementModel highestCellPerChannelModel_;
	QMap<ApiTypes::OperatingBand, std::shared_ptr<MeasurementModel>> sweepModels_;
	ModelGroup allTechModels_;
	ModelGroup gsmModels_;
	ModelGroup wcdmaModels_;
	ModelGroup lteModels_;
	CwMeasurementModel cwModel_;
	SpectrumManager spectrumManager_;

	std::vector<std::future<void>> rpf_conversions_;

	int64_t specIdentifier_;
};


//}}
