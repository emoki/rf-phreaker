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

void (RP_CALLCONV rp_gsm_full_scan_update)(const rp_base *base, const rp_gsm *gsm, int num_gsm) {
	//QCoreApplication::postEvent(Api::instance(), new GsmUpdateEvent(base, gsm, num_gsm));
}

void (RP_CALLCONV rp_wcdma_full_scan_update)(const rp_base *base, const rp_wcdma *wcdma, int num_umts) {
	QCoreApplication::postEvent(Api::instance(), new WcdmaUpdateEvent(base, wcdma, num_umts));
}

void (RP_CALLCONV rp_lte_full_scan_update)(const rp_base *base, const rp_lte *lte, int num_lte) {
	QCoreApplication::postEvent(Api::instance(), new LteUpdateEvent(base, lte, num_lte));
}

void (RP_CALLCONV rp_gsm_sweep_update)(const rp_base *base, const rp_gsm *gsm, int num_gsm) {
	//QCoreApplication::postEvent(Api::instance(), new GsmUpdateEvent(base, gsm, num_gsm));
}

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
	, lowestFreq_(lowestFreqDefault_)
	, highestFreq_(highestFreqDefault_)
	, canUpdateLog_(false)
	, canUpdateMessages_(false)
	, canUpdateDevice_(false)
	, canUpdateGps_(false) {
	canRecordData_ = false;
	callbacks_.rp_update = rp_update;
	callbacks_.rp_log_update = nullptr;
	callbacks_.rp_message_update = nullptr;
	callbacks_.rp_device_info_update = nullptr;
	callbacks_.rp_gps_update = nullptr;
	callbacks_.rp_gsm_full_scan_update = nullptr;
	callbacks_.rp_wcdma_full_scan_update = nullptr;
	callbacks_.rp_lte_full_scan_update = nullptr;
	callbacks_.rp_raw_data_update = nullptr;
	callbacks_.rp_gsm_sweep_update = nullptr;
	callbacks_.rp_wcdma_sweep_update = nullptr;
	callbacks_.rp_lte_sweep_update = nullptr;

	connect(updateTimer_, SIGNAL(timeout()), this, SLOT(emitSignals()));
	updateTimer_->start(800);

	connect(scanList_, SIGNAL(listChanged()), this, SLOT(findFreqMinMax()));

	thread_->start();
}

Api::~Api() {
	settingsIO_.writeSettings(settings_);
	settingsIO_.writeScanList(scanList_->qlist());
	thread_->quit();
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

	gsmFullScanModel_.clear();
	wcdmaFullScanModel_.clear();
	lteFullScanModel_.clear();
	highestCellPerChannelModel_.clear();
	sweepModelList_.clear();
	sweepModels_.clear();

	// Create storage for all possible techs.  Note, QMap automatically inserts a default item if it is empty.
	api_storage<rp_operating_band, rp_operating_band_group> sweep;
	api_storage<rp_frequency_type, rp_frequency_group> raw_data;
	QMap<ApiTypes::Tech, api_storage<rp_frequency_band, rp_frequency_band_group>> techs;

	foreach(const auto &ci, scanList_->qlist()) {
		auto cf = ci->channelFreqLow();
		if(ci->isSweep()) {
			sweep.push_back(cf->toRpBand());

			// Add operating band to sweep models
			auto sweepModel = sweepModels_.insert(cf->band(), std::make_shared<MeasurementModel>());
			QQmlEngine::setObjectOwnership(sweepModel->get(), QQmlEngine::CppOwnership);
			sweepModelList_.push_back(sweepModel->get());
		}
		else if(cf->tech() == ApiTypes::RAW_DATA) {
			raw_data.push_back(cf->toRpFreq());
		}
		else {
			techs[cf->tech()].push_back(cf->toRpFrequencyBand());
		}
	}

	// Alert the GUI that the sweep models have changed.
	emit sweepModelListChanged();

	QCoreApplication::postEvent(thread_->worker(), new StartCollectionEvent(sweep, raw_data, techs));
}

void Api::findFreqMinMax() {
	int low;
	int high;
	auto list = scanList_->qlist();
	if(list.empty()) {
		low = lowestFreqDefault_;
		high = highestFreqDefault_;
	}
	else {
		low = list[0]->channelFreqLow()->freqMhz();
		high = list[0]->isSweep() ? list[0]->channelFreqHigh()->freqMhz() : list[0]->channelFreqLow()->freqMhz();
		foreach(const auto &ci, list) {
			if(ci->channelFreqLow()->freqMhz() < low)
				low = ci->channelFreqLow()->freqMhz();
			if(ci->isSweep() && ci->channelFreqHigh()->freqMhz() > high)
				high = ci->channelFreqHigh()->freqMhz();
			else if(ci->channelFreqLow()->freqMhz() > high)
				high = ci->channelFreqLow()->freqMhz();
		}
		// Add some additional clearance due to bandwidth of LTE channels.
		low -= 15;
		high += 15;
		// Make it look more consistent.
		low = low - (low % 20);
		high = high + (20 - high % 20);
	}
	if(low != lowestFreq_) {
		lowestFreq_ = low;
		emit lowestFreqChanged();
	}
	if(high != highestFreq_) {
		highestFreq_ = high;
		emit highestFreqChanged();
	}

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
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLog: {
			QString msg(update_pb_.protobuf().log().msg().c_str());
			qDebug() << msg;
			log_.prepend(msg);
			canUpdateLog_ = true;
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kMsg: {
			auto &msg = update_pb_.protobuf().msg();
			handle_message((rp_status)msg.status(), msg.msg().c_str());
			canUpdateMessages_ = true;
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kDevice: {
			auto &device = update_pb_.get_hardware();
			connectedDevice_.copy(device);
			canUpdateDevice_ = true;
			deviceConnected();
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGps: {
			current_gps_ = update_pb_.get_gps();
			gps_.copy(current_gps_);
			canUpdateGps_ = true;
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmFullScan: {
			auto &t = update_pb_.get_gsm_full_scan();
			if(t.empty()) {
				auto &k = update_pb_.get_gsm_full_scan_basic();
				gsmFullScanModel_.update_with_basic_data(k, ApiTypes::GSM_FULL_SCAN);
			}
			else {
				gsmFullScanModel_.update(t);
				highestCellPerChannelModel_.update_freq_using_highest<less_than_cell_sl>(t);
			}
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaFullScan: {
			auto &t = update_pb_.get_wcdma_full_scan();
			if(t.empty()) {
				auto &k = update_pb_.get_wcdma_full_scan_basic();
				wcdmaFullScanModel_.update_with_basic_data(k, ApiTypes::WCDMA_FULL_SCAN);
			}
			else {
				wcdmaFullScanModel_.update(t);
				highestCellPerChannelModel_.update_freq_using_highest<less_than_cell_sl>(t);
			}
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLteFullScan: {
			auto &t = update_pb_.get_lte_full_scan();
			if(t.empty()) {
				auto &k = update_pb_.get_lte_full_scan_basic();
				lteFullScanModel_.update_with_basic_data(k, ApiTypes::LTE_FULL_SCAN);
			}
			else {
				lteFullScanModel_.update(t);
				highestCellPerChannelModel_.update_freq_using_highest<less_than_cell_sl>(t);
			}
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmSweep: {
			auto &t = update_pb_.get_gsm_sweep_basic();
			auto bands = band_specifier_.find_avaliable_gsm_operating_bands(t.carrier_frequency_);
			for(auto i : bands) {
				if(sweepModels_.contains(ApiTypes::toOperatingBand(i.band_)))
					sweepModels_[ApiTypes::toOperatingBand(i.band_)]->update_with_basic_data(t, ApiTypes::GSM_SWEEP);
			}
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaSweep: {
			auto &t = update_pb_.get_wcdma_sweep_basic();
			auto bands = band_specifier_.find_avaliable_umts_operating_bands(t.carrier_frequency_);
			for(auto i : bands) {
				if(sweepModels_.contains(ApiTypes::toOperatingBand(i.band_)))
					sweepModels_[ApiTypes::toOperatingBand(i.band_)]->update_with_basic_data(t, ApiTypes::WCDMA_SWEEP);
			}
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLteSweep: {
			auto &t = update_pb_.get_lte_sweep_basic();
			auto bands = band_specifier_.find_avaliable_lte_operating_bands(t.carrier_frequency_);
			for(auto i : bands) {
				if(sweepModels_.contains(ApiTypes::toOperatingBand(i.band_)))
					sweepModels_[ApiTypes::toOperatingBand(i.band_)]->update_with_basic_data(t, ApiTypes::LTE_SWEEP);
			}
			break;
		}
		default:
			qDebug() << "Unknown protobuf message.";
		}
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
	case RP_STATUS_FREQUENCY_CORRECTION_SUCCESSFUL:
		message(status, s);
		break;
	case RP_STATUS_FREQUENCY_CORRECTION_FAILED:
		message(status, s);
		break;
	case RP_STATUS_FREQUENCY_CORRECTION_VALUE_INVALID:
		message(status, s);
		break;
	case RP_STATUS_NOT_INITIALIZED:
		message(status, s);
		break;
	case RP_STATUS_INVALID_PARAMETER:
		message(status, s);
		break;
	case RP_STATUS_CALIBRATION_ERROR:
		message(status, s);
		break;
	case RP_STATUS_EEPROM_ERROR:
		message(status, s);
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

void Api::convertRfp(QString filename) {
	filename.remove("file:///");
	IO::convert_rpf(filename);
}

QString Api::getColorTheme(Base *b) {
	if(b == nullptr)
		return "dimgrey";
	switch(b->cellTech()) {
	case ApiTypes::GSM_SWEEP:
	case ApiTypes::WCDMA_SWEEP:
	case ApiTypes::LTE_SWEEP:
		return "seagreen";
	case ApiTypes::GSM_FULL_SCAN:
		return "paleturquoise";
	case ApiTypes::WCDMA_FULL_SCAN:
		return "firebrick";
	case ApiTypes::LTE_FULL_SCAN:
		return "mediumslateblue";
	default:
		return "dimgrey";
	}
}

MeasurementModel* Api::getSweepModel(Base *b) {
	if(sweepModels_.contains(b->cellBand()))
		return sweepModels_[b->cellBand()].get();
	else
		return nullptr;
}
