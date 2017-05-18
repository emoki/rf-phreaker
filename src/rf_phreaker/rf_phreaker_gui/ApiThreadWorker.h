#pragma once
#include <QObject>
#include <QThread>
#include <rf_phreaker/rf_phreaker_api/rf_phreaker_api.h>
#include <rf_phreaker/rf_phreaker_gui/ApiTypes.h>
#include <rf_phreaker/rf_phreaker_gui/Events.h>

class ApiThreadWorker : public QObject {
public:

	ApiThreadWorker() : QObject(0), device_(0) {}

	bool event(QEvent *e) {
		if(e->type() == InitializeApiEvent::getType()) {
			auto ev = static_cast<InitializeApiEvent*>(e);
			auto status = InitializeApi(ev->callbacks_);
			if(status == RP_STATUS_OK)
				QCoreApplication::postEvent(Api::instance(), new ApiInitializedEvent());
			else
				QCoreApplication::postEvent(Api::instance(), new MessageUpdateEvent(status, QString("API Initialization Failure"), rp_last_error_message()));
			e->accept();
			return true;
		}
		if(e->type() == CleanUpApiEvent::getType()) {
			auto status = CleanUpApi();
			if(status == RP_STATUS_OK)
				QCoreApplication::postEvent(Api::instance(), new ApiCleanedUpEvent());
			else {
				QCoreApplication::postEvent(Api::instance(), new ApiCleanedUpEvent());
				QCoreApplication::postEvent(Api::instance(), new MessageUpdateEvent(status, QString("API Deinitialization Failure"), rp_last_error_message()));
			}
			e->accept();
			return true;
		}
		if(e->type() == ListDevicesEvent::getType()) {
			auto list = listDevices();
			QCoreApplication::postEvent(Api::instance(), new AvailableDevicesEvent(list));
			e->accept();
			return true;
		}
		else if(e->type() == ConnectDeviceEvent::getType()) {
			auto ev = static_cast<ConnectDeviceEvent*>(e);
			auto status = connectDevice(ev->serial());
			if(!ApiTypes::statusOk(status))
				QCoreApplication::postEvent(Api::instance(), new MessageUpdateEvent(status, QString("Scanner Communication Failure"), rp_last_error_message()));
			e->accept();
			return true;
		}
		else if(e->type() == DisconnectDeviceEvent::getType()) {
			auto status = disconnectDevice();
			if(ApiTypes::statusOk(status))
				QCoreApplication::postEvent(Api::instance(), new DeviceDisconnectedEvent());
			// Do not show error.
			e->accept();
			return true;
		}
		else if(e->type() == StartCollectionEvent::getType()) {
			auto ev = static_cast<StartCollectionEvent*>(e);
			auto status = startCollection(ev->sweep(), ev->iq(), ev->spec(), ev->techs());
			if(ApiTypes::statusOk(status))
				QCoreApplication::postEvent(Api::instance(), new CollectionStartedEvent());
			else
				QCoreApplication::postEvent(Api::instance(), new MessageUpdateEvent(status, QString("Data Recording Failure"), rp_last_error_message()));
			e->accept();
			return true;
		}
		else if(e->type() == StopCollectionEvent::getType()) {
			auto status = stopCollection();
			if(ApiTypes::statusOk(status))
				QCoreApplication::postEvent(Api::instance(), new CollectionStoppedEvent());
			else
				QCoreApplication::postEvent(Api::instance(), new MessageUpdateEvent(status, QString("Stop Data Recording Failed"), rp_last_error_message()));
			e->accept();
			return true;
		}

		return QObject::event(e);
	}
private:
	rp_status InitializeApi(rp_callbacks *callbacks) {
		qDebug() << "Initializing API.";
		auto status = rp_initialize(callbacks);
		if(!ApiTypes::statusOk(status)) {
			qWarning() << "Failed to initialize API.  Error message \"" << rp_last_error_message() << "\".";
		}
		return status;
	}

	rp_status CleanUpApi() {
		qDebug() << "Cleaning up API.";
		auto status = rp_clean_up();
		if(!ApiTypes::statusOk(status)) {
			qWarning() << "Failed to clean up API.  Error message \"" << rp_last_error_message() << "\".";
		}
		return status;
	}

	QStringList listDevices() {
		qDebug() << "Listing devices";
		std::vector<rp_serial> serials{100};
		int32_t size = serials.size();
		auto status = rp_list_devices(&serials[0], &size);

		if(!ApiTypes::statusOk(status)) {
			qWarning() << "Failed to list devices.  Error message \"" << rp_last_error_message() << "\".";
			size = 0;
		}
		QStringList list;
		for(int i = 0; i < size; ++i) {
			list.push_back(serials[i].serial_);
			qDebug() << "Available device:" << serials[i].serial_;
		}
		return list;
	}

	rp_status connectDevice(QString qserial) {

		// First time thru qserial can be empty
		// If empty we attempt to use deviceSerial (in case we are reopening the device).
		// If deviceSerial is empty or not in list, we open the first device.
		auto list = listDevices();
		if(!list.contains(qserial) && !list.isEmpty()) {
			qWarning() << "Opening first device available.";
			qserial = list.at(0);
		}

		if(qserial.size() != RP_SERIAL_LENGTH - 1)
			qWarning() << "Unable to open device.  Serial" << qserial << "is not the correct length" << RP_SERIAL_LENGTH;

		qDebug() << "Connecting device" << qserial;
		auto byteArray = qserial.toLocal8Bit();
		rp_serial serial;
		memset(serial.serial_, 0, RP_SERIAL_LENGTH);
		memcpy(serial.serial_, byteArray.data(), RP_SERIAL_LENGTH);

		auto status = rp_connect_device(serial, &device_);

		if(!ApiTypes::statusOk(status))
			qWarning() << "Unable to connnect to" << qserial << ".  Error message \"" << rp_last_error_message();
		else {
			qDebug() << "Connected device handle:" << device_;
		}
		return status;
	}

	rp_status disconnectDevice() {
		qDebug() << "Disconnecting device handle" << device_;

		auto status = RP_STATUS_OK;

		if(device_ == 0)
			qDebug() << "Device handle zero, skipping rp_disconnect_device.";

		else {
			status = rp_disconnect_device(device_);
			device_ = 0;

			if(!ApiTypes::statusOk(status))
				qWarning() << "Error disconnecting device" << device_ << ". Error message \"" << rp_last_error_message() << "\".";
		}
		return status;
	}

	rp_status startCollection(api_storage<rp_operating_band, rp_operating_band_group> sweep,
							  api_storage<rp_frequency_type, rp_frequency_group> iq,
							  api_storage<rp_power_spectrum_spec, rp_power_spectrum_spec_group> &spec,
							  QMap<ApiTypes::Tech, api_storage<rp_frequency_band, rp_frequency_band_group>> techs) {
		qDebug() << "Starting collection.";

		rp_collection_info info;
		info.gsm_ = techs[ApiTypes::GSM_FULL_SCAN].get_group();
		info.wcdma_ = techs[ApiTypes::WCDMA_FULL_SCAN].get_group();
		info.lte_ = techs[ApiTypes::LTE_FULL_SCAN].get_group();
		info.iq_data_ = iq.get_group();
		info.power_spectrum_spec_ = spec.get_group();
		info.sweep_ = sweep.get_group();

		auto status = rp_start_collection(device_, &info);
		if(!ApiTypes::statusOk(status))
			qWarning() << "Unable to start collection.  Error message \"" << rp_last_error_message() << "\".";

		return status;
	}

	rp_status stopCollection() {
		qDebug() << "Stopping collection.";

		auto status = rp_stop_collection(device_);
		if(!ApiTypes::statusOk(status))
			qWarning() << "Unable to stop collection.  Error message \"" << rp_last_error_message() << "\".";

		return status;
	}

	rp_device *device_;
};

class ApiThread : public QThread {
public:
	ApiThread(QObject *parent = 0) : QThread(parent), worker_(nullptr) {}
	void run() {
		worker_ = new ApiThreadWorker;
		exec();
		delete worker_;
		worker_ = nullptr;
	}
	ApiThreadWorker* worker() { return worker_; }
private:
	ApiThreadWorker *worker_;
};
