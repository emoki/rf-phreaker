#include <QDebug>
#include <QtCore/QCoreApplication>
#include "rf_phreaker/rf_phreaker_gui/Api.h"
#include "rf_phreaker/rf_phreaker_gui/Utility.h"
#include "rf_phreaker/rf_phreaker_gui/Events.h"
#include "rf_phreaker/rf_phreaker_gui/ApiThreadWorker.h"
#include "rf_phreaker/protobuf_specific/io.h"

//namespace rf_phreaker { namespace gui {

void (RP_CALLCONV rp_update)(const int8_t *google_protocol_buffer_stream, int32_t size) {
	QCoreApplication::postEvent(Api::instance(), 
		new ProtobufUpdateEvent(google_protocol_buffer_stream, size));
}

void (RP_CALLCONV rp_log_update)(const char *message) {
	QCoreApplication::postEvent(Api::instance(), new LogUpdateEvent(message));
}

void (RP_CALLCONV rp_message_update)(rp_status status, const char *message) {
	QCoreApplication::postEvent(Api::instance(), new MessageUpdateEvent(status, message));
}

void (RP_CALLCONV rp_device_info_update)(const rp_device_info *info) {
	QCoreApplication::postEvent(Api::instance(), new DeviceUpdateEvent(*info));
}

void (RP_CALLCONV rp_gps_update)(const rp_gps *gps) {
	QCoreApplication::postEvent(Api::instance(), new GpsUpdateEvent(*gps));
}

void (RP_CALLCONV rp_gsm_full_scan_update)(const rp_base *base, const rp_gsm *gsm, int num_gsm) {}

void (RP_CALLCONV rp_wcdma_full_scan_update)(const rp_base *base, const rp_wcdma *wcdma, int num_umts) {
	QCoreApplication::postEvent(Api::instance(), new WcdmaUpdateEvent(base, wcdma, num_umts));
}

void (RP_CALLCONV rp_lte_full_scan_update)(const rp_base *base, const rp_lte *lte, int num_lte) {
	QCoreApplication::postEvent(Api::instance(), new LteUpdateEvent(base, lte, num_lte));
}

void (RP_CALLCONV rp_gsm_sweep_update)(const rp_base *base, const rp_gsm *gsm, int num_gsm) {}

void (RP_CALLCONV rp_wcdma_sweep_update)(const rp_base *base, const rp_wcdma *wcdma, int num_umts) {
	//QCoreApplication::postEvent(Api::instance(), new WcdmaUpdateEvent(base, wcdma, num_umts));
}

void (RP_CALLCONV rp_lte_sweep_update)(const rp_base *base, const rp_lte *lte, int num_lte) {
	//QCoreApplication::postEvent(Api::instance(), new LteUpdateEvent(base, lte, num_lte));
}

void (RP_CALLCONV rp_raw_data_update)(const rp_raw_data *raw, int num_raw_data) {

}

Api *Api::instance_ = nullptr;
QMutex Api::instance_mutex_;

// To used with ApiInterfaceSingletonTypeProvider so that the pointer is owned by the qml engine.
Api* Api::instance() {
	if(instance_ == nullptr) {
		QMutexLocker lock(&instance_mutex_);
		if(instance_ == nullptr) {
			qDebug() << "Instantiating instance pointer." << instance_;
			instance_ = new Api;
			qDebug() << "New instance pointer." << instance_;
		}
	}
	return instance_;
}

Api::Api(QObject *parent)
	: QObject(parent)
	, deviceStatus_(ApiTypes::OFF)
	, connectionStatus_(ApiTypes::DISCONNECTED)
	, scanList_(new CollectionInfoList(this))
	, backgroundScanList_(new CollectionInfoList(this))
	, thread_(new ApiThread)
	, updateTimer_(new QTimer(this))
	, canUpdateLog_(false)
	, canUpdateMessages_(false)
	, canUpdateDevice_(false)
	, canUpdateGps_(false)
	, canUpdateGsm_(false)
	, canUpdateWcdma_(false)
    , canUpdateLte_(false) {
    canRecordData_ = false;
	callbacks_.rp_update = rp_update;
	callbacks_.rp_log_update = rp_log_update;
	callbacks_.rp_message_update = rp_message_update;
	callbacks_.rp_device_info_update = rp_device_info_update;
	callbacks_.rp_gps_update = rp_gps_update;
	callbacks_.rp_gsm_full_scan_update = rp_gsm_full_scan_update;
	callbacks_.rp_wcdma_full_scan_update = rp_wcdma_full_scan_update;
	callbacks_.rp_lte_full_scan_update = rp_lte_full_scan_update;
	callbacks_.rp_raw_data_update = /*rp_raw_data_update*/0;
	callbacks_.rp_gsm_sweep_update = rp_gsm_sweep_update;
	callbacks_.rp_wcdma_sweep_update = rp_wcdma_sweep_update;
	callbacks_.rp_lte_sweep_update = rp_lte_sweep_update;

	connect(updateTimer_, SIGNAL(timeout()), this, SLOT(emitSignals()));
	updateTimer_->start(800);

	thread_->start();
}

Api::~Api() {
	thread_->quit();
	settingsIO_.writeSettings(settings_);
	settingsIO_.writeScanList(scanList_->qlist());
	thread_->wait();
	rp_clean_up();
	closeCollectionFile();
}

void Api::initializeApi() {
	QCoreApplication::postEvent(thread_->worker(), new InitializeApiEvent(&callbacks_));
	settingsIO_.readSettings(settings_);
	scanList_->setList(settingsIO_.readScanList());
}

void Api::cleanUpApi() {
	QCoreApplication::postEvent(thread_->worker(), new CleanUpApiEvent());
}

void Api::listDevices() {
	QCoreApplication::postEvent(thread_->worker(), new ListDevicesEvent());
}

void Api::connectDevice(QString qserial) {
	// If qserial is empty, check to see if we have already connected a device
	// previously and use that if possible.
	if(qserial.isEmpty() && !connectedDevice_.serial().isEmpty())
		qserial = connectedDevice_.serial();

	QCoreApplication::postEvent(thread_->worker(), new ConnectDeviceEvent(qserial));
}

void Api::disconnectDevice() {
	QCoreApplication::postEvent(thread_->worker(), new DisconnectDeviceEvent());
}

void Api::startCollection() {
	qDebug() << "Starting collection.";

	// Create storage for all possible techs.  Note, QMap automatically inserts a default item if it is empty.
	api_storage<rp_operating_band, rp_operating_band_group> sweep;
	api_storage<rp_frequency_type, rp_frequency_group> raw_data;
	QMap<ApiTypes::Tech, api_storage<rp_frequency_band, rp_frequency_band_group>> techs;

	foreach(const auto &ci, scanList_->qlist()) {
		auto cf = ci->channelFreqLow();
		if(ci->isSweep()) {
			sweep.push_back(cf->toRpBand());
		}
		else if(cf->tech() == ApiTypes::RAW_DATA) {
			raw_data.push_back(cf->toRpFreq());
		}
		else {
			techs[cf->tech()].push_back(cf->toRpFrequencyBand());
		}
	}

	QCoreApplication::postEvent(thread_->worker(), new StartCollectionEvent(sweep, raw_data, techs));
}

void Api::stopCollection() {
	QCoreApplication::postEvent(thread_->worker(), new StopCollectionEvent());
	stats_.stop_benchmark();
}

void Api::updateLicense() {

}

void Api::emitSignals() {
	if(canUpdateLog_) {
		emit logChanged();
		canUpdateLog_ = false;
	}
	if(canUpdateMessages_) {
		emit messagesChanged();
		canUpdateMessages_ = false;
	}
	if(canUpdateDevice_) {
		emit connectedDeviceChanged();
		canUpdateDevice_ = false;
	}
	if(canUpdateGps_) {
		emit gpsChanged();
		canUpdateGps_ = false;
	}
//	if(canUpdateGsm_) {
//		emit gsmListChanged();
//	    canUpdateGsm_ = false;
//	}
	if(canUpdateWcdma_) {
		emit wcdmaListChanged();
		wcdmaList_ = wcdmaMap_.values();
		canUpdateWcdma_ = false;
	}
	if(canUpdateLte_) {
		emit lteListChanged();
		lteList_ = lteMap_.values();
		canUpdateLte_ = false;
	}
}

bool Api::event(QEvent *e) {
	if(e->type() == ProtobufUpdateEvent::getType()) {
		auto ev = static_cast<ProtobufUpdateEvent*>(e);
		auto &proto = update_pb_.protobuf();
		proto.ParseFromArray(ev->data().data(), ev->data().size());
		stats_.update_benchmark(proto.update_case());

		if(canRecordData_) {
			if(proto.update_case() != rf_phreaker::protobuf::rp_update::UpdateCase::kLog)
				rf_phreaker::protobuf::write_delimited_to(proto, output_file_.get());
			if(settings_.api_output_) {
				api_debug_output_.output_api_data(update_pb_, collectionFilename_, current_gps_);
			}
		}

		switch(proto.update_case()) {
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLog:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kMsg:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kDevice:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGps:
			current_gps_ = update_pb_.get_gps();
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmFullScan:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaFullScan:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLteFullScan:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmSweep:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaSweep:
			break;
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLteSweep:
			break;
		default:
			qDebug() << "Unknown protobuf message.";
		}
	}
	if(e->type() == WcdmaUpdateEvent::getType()) {
		auto ev = static_cast<WcdmaUpdateEvent*>(e);
		for(auto i = ev->wcdmaList().begin(); i != ev->wcdmaList().end(); ++i) {
			auto it = wcdmaMap_.find(to_hash(*i));
			if(it == wcdmaMap_.end())
				wcdmaMap_.insert(to_hash(*i), new Wcdma(*i, this));
			else
				static_cast<Wcdma*>(it.value())->copy(*i);
		}
		canUpdateWcdma_ = true;
		e->accept();
		return true;
	}
	else if(e->type() == LteUpdateEvent::getType()) {
		auto ev = static_cast<LteUpdateEvent*>(e);
		for(auto i = ev->lteList().begin(); i != ev->lteList().end(); ++i) {
			auto it = lteMap_.find(to_hash(*i));
			if(it == lteMap_.end())
				lteMap_.insert(to_hash(*i), new Lte(*i, this));
			else
				static_cast<Lte*>(it.value())->copy(*i);
		}
		canUpdateLte_ = true;
		e->accept();
		return true;
	}
	else if(e->type() == GpsUpdateEvent::getType()) {
		auto ev = static_cast<GpsUpdateEvent*>(e);
		gps_.copy(ev->gps());
		canUpdateGps_ = true;
		e->accept();
		return true;
	}
	else if(e->type() == LogUpdateEvent::getType()) {
		auto ev = static_cast<LogUpdateEvent*>(e);
		qDebug() << ev->msg();
		log_.prepend(ev->msg());
		canUpdateLog_ = true;
		e->accept();
		return true;
	}
	else if(e->type() == MessageUpdateEvent::getType()) {
		auto ev = static_cast<MessageUpdateEvent*>(e);
		handle_message(ev->status(), ev->msg());
		canUpdateMessages_ = true;
		e->accept();
		return true;
	}
	else if(e->type() == DeviceUpdateEvent::getType()) {
		auto ev = static_cast<DeviceUpdateEvent*>(e);
		connectedDevice_.copy(ev->device());
		canUpdateDevice_ = true;
		deviceConnected();
		e->accept();
		return true;
	}
	else if(e->type() == AvailableDevicesEvent::getType()) {
		auto ev = static_cast<AvailableDevicesEvent*>(e);
		availableDevices_ = ev->deviceList();
		emit availableDevicesChanged();
		numDevicesConnected(availableDevices_.size());
		e->accept();
		return true;
	}
	else if(e->type() == CollectionStartedEvent::getType()) {
		scanningStarted();
		e->accept();
		return true;
	}
	else if(e->type() == CollectionStoppedEvent::getType()) {
		scanningStopped();
		e->accept();
		return true;
	}
	else if(e->type() == DeviceDisconnectedEvent::getType()) {
		deviceDisconnected();
		e->accept();
		return true;
	}
	else if(e->type() == ApiInitializedEvent::getType()) {
		apiInitialized();
		e->accept();
		return true;
	}
	else if(e->type() == CloseCollectionFileEvent::getType()) {
		close_collection_file();
		e->accept();
		return true;
	}

	return QObject::event(e);
}

void Api::handle_message(rp_status status, const QString &s) {
	auto status_str = rp_status_message(status);

	switch(status) {
	case RP_STATUS_OK:
		break;
	//case RP_OTHER_GOOD_THINGS:
	// Handle other messages that may not be errors?
	default:
		errorMessage(status, s);
	}
	qDebug() << status_str + s;

	messages_.prepend(status_str + s);
	emit messagesChanged();
}

bool Api::openCollectionFile(){
	qDebug() << "Opening collection file. " << collectionFilename_ << ".";
	collectionFilename_.remove("file:///");
	output_qfile_.setFileName(collectionFilename_);
	if(!output_qfile_.open(QIODevice::WriteOnly | QIODevice::Unbuffered)) {
		qDebug() << "Failed to open collection file. " << output_qfile_.errorString();
		canRecordData_ = false;
	}
	else {
		output_file_ = std::make_unique<google::protobuf::io::FileOutputStream>(output_qfile_.handle());
		canRecordData_ = true;
		stats_.start_benchmark(collectionFilename_.toStdString());
	}

	return canRecordData_;
}

void Api::closeCollectionFile() {
	QCoreApplication::postEvent(Api::instance(), new CloseCollectionFileEvent());
}

void Api::close_collection_file() {
	canRecordData_ = false;
	if(output_file_) {
		output_file_->Flush();
		output_file_.reset();
		output_qfile_.close();
	}
	api_debug_output_.close();
}

