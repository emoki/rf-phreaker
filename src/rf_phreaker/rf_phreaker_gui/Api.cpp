#include <QDebug>
#include <QtCore/QCoreApplication>
#include <QRegularExpression>
#include "rf_phreaker/rf_phreaker_gui/Api.h"
#include "rf_phreaker/rf_phreaker_gui/Utility.h"
#include "rf_phreaker/rf_phreaker_gui/Events.h"
#include "rf_phreaker/rf_phreaker_gui/ApiThreadWorker.h"
#include "rf_phreaker/rf_phreaker_gui/SettingsIO.h"
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
	QCoreApplication::postEvent(Api::instance(), new MessageUpdateEvent(status, "", message));
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

void (RP_CALLCONV rp_raw_data_update)(const rp_iq_data *raw, int num_iq_data) {

}

Api *Api::instance_ = nullptr;
QMutex Api::instance_mutex_;

// To used with ApiInterfaceSingletonTypeProvider so that the pointer is owned by the qml engine.
Api* Api::instance() {
	if(instance_ == nullptr) {
		QMutexLocker lock(&instance_mutex_);
		if(instance_ == nullptr) {
			instance_ = new Api;
		}
	}
	return instance_;
}

Api::Api(QObject *parent)
	: QObject(parent)
	, deviceStatus_(ApiTypes::OFF)
	, connectionStatus_(ApiTypes::DISCONNECTED)
	, thread_(new ApiThread)
	, allTechModels_(highestCellPerChannelModel_, ApiTypes::FIRST_GSM_OPERATING_BAND, ApiTypes::LAST_LTE_OPERATING_BAND)
	, gsmModels_(highestCellPerChannelModel_, ApiTypes::FIRST_GSM_OPERATING_BAND, ApiTypes::LAST_GSM_OPERATING_BAND)
	, wcdmaModels_(highestCellPerChannelModel_, ApiTypes::FIRST_WCDMA_OPERATING_BAND, ApiTypes::LAST_WCDMA_OPERATING_BAND)
	, lteModels_(highestCellPerChannelModel_, ApiTypes::FIRST_LTE_OPERATING_BAND, ApiTypes::LAST_LTE_OPERATING_BAND)
	, specIdentifier_(SPECTRUM_MIN_IDENTIFIER) {
	canRecordData_ = false;
	shouldUpdateLog_ = false;
	callbacks_.rp_update = rp_update;
	callbacks_.rp_log_update = nullptr;
	callbacks_.rp_message_update = nullptr;
	callbacks_.rp_device_info_update = nullptr;
	callbacks_.rp_gps_update = nullptr;
	callbacks_.rp_gsm_full_scan_update = nullptr;
	callbacks_.rp_wcdma_full_scan_update = nullptr;
	callbacks_.rp_lte_full_scan_update = nullptr;
	callbacks_.rp_iq_data_update = nullptr;
	callbacks_.rp_gsm_sweep_update = nullptr;
	callbacks_.rp_wcdma_sweep_update = nullptr;
	callbacks_.rp_lte_sweep_update = nullptr;
	callbacks_.rp_power_spectrum_update = nullptr;

	apiOutput_ = Settings::instance()->apiOutput_;
	QObject::connect(Settings::instance(), &Settings::apiOutputChanged, [&](bool apiOutput) {
		this->apiOutput_ = apiOutput;
	});

	isSpectrumLogged_ = Settings::instance()->isSpectrumLogged_;
	QObject::connect(Settings::instance(), &Settings::isSpectrumLoggedChanged, [&](bool isSpectrumLogged) {
		this->isSpectrumLogged_ = isSpectrumLogged;
	});


	auto timer = new QTimer(this);
	QObject::connect(timer, &QTimer::timeout, [&] () {
		if(this->shouldUpdateLog_) {
			emit this->logChanged();
			this->shouldUpdateLog_ = false;
		}
	});
	timer->start(1000);

	//connect(&scanList_, SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), this, SLOT(findFreqMinMax()));
	//connect(&scanList_, SIGNAL(modelReset()), this, SLOT(findFreqMinMax()));
	//connect(&scanList_, SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(findFreqMinMax()));
	//connect(&scanList_, SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(findFreqMinMax()));

	thread_->start();
}

Api::~Api() {
	SettingsIO settingsIO;
	settingsIO.writeScanList(scanList_.list());
	thread_->quit();
	thread_->wait();
	rp_clean_up();
	closeCollectionFile();
}

void Api::initializeApi() {
	QCoreApplication::postEvent(thread_->worker(), new InitializeApiEvent(&callbacks_));

	// We have to initialize the channel list here so that QML is properly updated.
	SettingsIO settingsIO;
	scanList_.setList(settingsIO.readScanList(this));
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

	clearModels();
	cwLookup_.clear();

	// Create storage for all possible techs.  Note, QMap automatically inserts a default item if it is empty.
	api_storage<rp_operating_band, rp_operating_band_group> sweep;
	api_storage<rp_iq_data_spec, rp_iq_data_spec_group> iq_data;
	api_storage<rp_power_spectrum_spec, rp_power_spectrum_spec_group> spec_data;
	QMap<ApiTypes::Tech, api_storage<rp_frequency_band, rp_frequency_band_group>> techs;

	foreach(const auto &ci, scanList_.list()) {
		auto cfLow = ci->channelFreqLow();
		auto cfHigh = ci->channelFreqHigh();
		if(!cfLow->isValid())
			continue;

		if(ci->isSweep()) {
			sweep.push_back(cfLow->toRpBand());
			// Add operating band to sweep models
			auto sweepModel = sweepModels_.insert(cfLow->band(), std::make_shared<MeasurementModel>());
			QQmlEngine::setObjectOwnership(sweepModel->get(), QQmlEngine::CppOwnership);
		}
		else if(ci->isGsm() || ci->isWcdma() || ci->isLte()) {
			techs[cfLow->tech()].push_back(cfLow->toRpFrequencyBand());
		}
		else if(ci->isSpectrum()) {
			if(!cfHigh->isValid())
				continue;
			rp_power_spectrum_spec spec;
			spec.start_frequency_ = cfLow->toRpFreq() < cfHigh->toRpFreq() ? cfLow->toRpFreq() : cfHigh->toRpFreq();
			spec.span_ = abs(cfHigh->toRpFreq() - cfLow->toRpFreq());
			spec.bin_size_ = Settings::instance()->spectrumBinSize_;
			spec.dwell_time_ = Settings::instance()->spectrumDwellTime_;
			spec.identifier_ = specIdentifier_++;
			spec_data.push_back(spec);
			spectrumManager_.freqLimits()->update(spec);
		}
		else if(ci->isCw()) {
			rp_power_spectrum_spec spec;
			spec.start_frequency_ = cfLow->toRpFreq() - Settings::instance()->cwOffsetFactor_ * Settings::instance()->cwBinSize_;
			spec.span_ = Settings::instance()->cwSpanFactor_ * Settings::instance()->cwBinSize_;
			spec.bin_size_ = Settings::instance()->cwBinSize_;
			spec.dwell_time_ = Settings::instance()->cwDwellTime_;
			spec.identifier_ = cfLow->toRpFreq();
			spec_data.push_back(spec);
			cwLookup_.insert(spec);
		}
		else if(ci->isIq()) {
			rp_iq_data_spec spec;
			spec.center_frequency_ = cfLow->toRpFreq();
			spec.bandwidth_ = Settings::instance()->iqBandwidth_;
			spec.dwell_time_ = Settings::instance()->iqDwellTime_;
			spec.sampling_rate_ = Settings::instance()->iqSamplingRate_;
		}
	}

	updateModels();

	findFreqMinMax();

	QCoreApplication::postEvent(thread_->worker(), new StartCollectionEvent(sweep, iq_data, spec_data, techs));
}

void Api::clearModels() {
	allTechModels_.clear();
	gsmModels_.clear();
	wcdmaModels_.clear();
	lteModels_.clear();
	highestCellPerChannelModel_.clear();
	sweepModels_.clear();
	spectrumManager_.clear();
	cwModel_.clear();
}

void Api::updateModels() {
	allTechModels_.setSweepModels(sweepModels_);
	gsmModels_.setSweepModels(sweepModels_);
	wcdmaModels_.setSweepModels(sweepModels_);
	lteModels_.setSweepModels(sweepModels_);
}

void Api::findFreqMinMax() {
	auto list = scanList_.list();
	allTechModels_.findFreqMinMax(list);
	gsmModels_.findFreqMinMax(list);
	wcdmaModels_.findFreqMinMax(list);
	lteModels_.findFreqMinMax(list);
	// spectrum is done within model
}

void Api::stopCollection() {
	QCoreApplication::postEvent(thread_->worker(), new StopCollectionEvent());
}

void Api::updateLicense() {

}

bool Api::event(QEvent *e) {
	if(e->type() == ProtobufUpdateEvent::getType()) {
		auto ev = static_cast<ProtobufUpdateEvent*>(e);
		auto &proto = update_pb_.protobuf();
		proto.ParseFromArray(ev->data().data(), ev->data().size());
		stats_.update_benchmark(proto.update_case());

		if(canRecordData_) {
			if(proto.update_case() != rf_phreaker::protobuf::rp_update::UpdateCase::kLog && 
				!(proto.update_case() == rf_phreaker::protobuf::rp_update::UpdateCase::kPowerSpectrum && !isSpectrumLogged_))
				rf_phreaker::protobuf::write_delimited_to(proto, output_file_.get());
			if(apiOutput_) {
				api_debug_output_.output_api_data(update_pb_, collectionFilename_, current_gps_);
			}
		}

		switch(proto.update_case()) {
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLog: {
			appendLog(QString(update_pb_.protobuf().log().msg().c_str()));
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kMsg: {
			auto &msg = update_pb_.protobuf().msg();
			handle_message(ApiMessage((rp_status)msg.status(), "", msg.msg().c_str()));
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kDevice: {
			auto &device = update_pb_.get_hardware();
			connectedDevice_.copy(device);
			emit connectedDeviceChanged();
			deviceConnected();
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGps: {
			current_gps_ = update_pb_.get_gps();
			gps_.copy(current_gps_);
			emit gpsChanged();
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmFullScan: {
			auto &t = update_pb_.get_gsm_full_scan();
			if(t.empty()) {
				//auto &k = update_pb_.get_gsm_full_scan_basic();
				//gsmFullScanModel_.update_with_basic_data(k, ApiTypes::GSM_FULL_SCAN);
			}
			else {
				gsmModels_.fullScanModel()->update(t);
				// Manually sort vector and only pass in the first meas (hopefully with a decoded bsic) for each freq
				less_than_freq_id cmp;
				std::sort(t.begin(), t.end(), cmp);
				// We at least have one measurement.
				less_than_freq less_than_f;
				auto p = std::equal_range(t.begin(), t.end(), *t.begin(), less_than_f);
				while(1) {
					highestCellPerChannelModel_.update_freq<less_than_cell_sl>(*p.first);
					if(p.second == t.end()) break;
					p = std::equal_range(p.second, t.end(), *p.second, less_than_f);
				}
			}
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaFullScan: {
			auto &t = update_pb_.get_wcdma_full_scan();
			if(t.empty()) {
				//auto &k = update_pb_.get_wcdma_full_scan_basic();
				//wcdmaFullScanModel_.update_with_basic_data(k, ApiTypes::WCDMA_FULL_SCAN);
			}
			else {
				wcdmaModels_.fullScanModel()->update(t);
				highestCellPerChannelModel_.update_freq_using_highest<less_than_cell_sl>(t);
			}
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLteFullScan: {
			auto &t = update_pb_.get_lte_full_scan();
			if(t.empty()) {
				//auto &k = update_pb_.get_lte_full_scan_basic();
				//lteFullScanModel_.update_with_basic_data(k, ApiTypes::LTE_FULL_SCAN);
			}
			else {
				lteModels_.fullScanModel()->update(t);
				highestCellPerChannelModel_.update_freq_using_highest<less_than_cell_sl>(t);
			}
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kGsmSweep: {
			auto &t = update_pb_.get_gsm_sweep_basic();
			auto bands = band_specifier_.find_avaliable_gsm_operating_bands(t.measurement_frequency_);
			for(auto i : bands) {
				if(sweepModels_.contains(ApiTypes::toOperatingBand(i.band_)))
					sweepModels_[ApiTypes::toOperatingBand(i.band_)]->update_with_basic_data(t, ApiTypes::GSM_SWEEP);
			}
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kWcdmaSweep: {
			auto &t = update_pb_.get_wcdma_sweep_basic();
			auto bands = band_specifier_.find_avaliable_umts_operating_bands(t.measurement_frequency_);
			for(auto i : bands) {
				if(sweepModels_.contains(ApiTypes::toOperatingBand(i.band_)))
					sweepModels_[ApiTypes::toOperatingBand(i.band_)]->update_with_basic_data(t, ApiTypes::WCDMA_SWEEP);
			}
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kLteSweep: {
			auto &t = update_pb_.get_lte_sweep_basic();
			auto bands = band_specifier_.find_avaliable_lte_operating_bands(t.measurement_frequency_);
			for(auto i : bands) {
				if(sweepModels_.contains(ApiTypes::toOperatingBand(i.band_)))
					sweepModels_[ApiTypes::toOperatingBand(i.band_)]->update_with_basic_data(t, ApiTypes::LTE_SWEEP);
			}
			break;
		}
		case rf_phreaker::protobuf::rp_update::UpdateCase::kPowerSpectrum: {
			auto t = update_pb_.get_power_spectrum();
			if(t.params_.identifier_ >= SPECTRUM_MIN_IDENTIFIER) {
				spectrumManager_.update(std::move(t));
			}
			else {
				cwModel_.update(std::vector<rf_phreaker::power_spectrum_data>{t});
			}
			break;
		}
		default:
			qDebug() << "Unknown protobuf message.";
		}
	}
	else if(e->type() == LogUpdateEvent::getType()) {
		appendLog(static_cast<LogUpdateEvent*>(e)->msg());
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
		gps_.clear();
		clearModels();
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
	else if(e->type() == MessageUpdateEvent::getType()) {
		auto ev = static_cast<MessageUpdateEvent*>(e);
		handle_message(ev->msg());
		e->accept();
		return true;
	}

	return QObject::event(e);
}

void Api::handle_message(const ApiMessage &t) {
	qDebug() << t.mainDescription_ << " | " << t.statusStr_ << " | " << t.details_;

	auto main = t.mainDescription_;

	// Remove any line number and filenames that may be in the message.
	// These can be observed using the log file.
	auto details = t.details_;
	details.remove(QRegularExpression("\\[.*\\] ", QRegularExpression::NoPatternOption));

	auto msg = new ApiMessage(t.status_, main, details, this);
	switch(msg->status_) {
	case RP_STATUS_OK:
	case RP_STATUS_FREQUENCY_CORRECTION_SUCCESSFUL:
	case RP_STATUS_COLLECTION_FINISHED:
		if(msg->mainDescription_.isEmpty())
			msg->mainDescription_ = "Internal RF Phreaker Message";
		messages_.prepend(msg);
		emit messagesChanged();
		break;
	default:
		if(msg->mainDescription_.isEmpty())
			msg->mainDescription_ = "Internal RF Phreaker Error";
		errors_.prepend(msg);
		emit errorsChanged();
	}

	switch(msg->status_) {
	// If it's a "good" message no signals needed.
	case RP_STATUS_OK:
	case RP_STATUS_FREQUENCY_CORRECTION_SUCCESSFUL:
	case RP_STATUS_COLLECTION_FINISHED:
		break;
	case RP_STATUS_FREQUENCY_CORRECTION_FAILED:
	case RP_STATUS_FREQUENCY_CORRECTION_VALUE_INVALID:
	case RP_STATUS_INVALID_PARAMETER: // This means the API has been initialized successfully and we only need to stop scanning.
	case RP_STATUS_CALIBRATION_ERROR:
	case RP_STATUS_EEPROM_ERROR:
	case RP_STATUS_HARDWARE_INFO_ERROR:
	case RP_STATUS_MISC_ERROR:
	case RP_STATUS_FILE_IO_ERROR:
	case RP_STATUS_IPP_ERROR:
	case RP_STATUS_FILTER_ERROR:
	case RP_STATUS_GSM_ANALYSIS_ERROR:
	case RP_STATUS_UMTS_ANALYSIS_ERROR:
	case RP_STATUS_LTE_ANALYSIS_ERROR:
	case RP_STATUS_PROCESSING_ERROR:
	case RP_STATUS_LICENSE_ERROR:
	case RP_STATUS_CONVERSION_ERROR:
	case RP_STATUS_RF_PHREAKER_API_ERROR:
		errorGoIdle();
		break;
	case RP_STATUS_NOT_INITIALIZED:
	case RP_STATUS_COMMUNICATION_ERROR:
	case RP_STATUS_SCANNER_INIT_ERROR:
	case RP_STATUS_BLADE_RF_ERROR:
	case RP_STATUS_GPS_COMMUNICATION_ERROR:
	case RP_STATUS_CONFIGURATION_FILE_NOT_FOUND:
	default:
		errorReinitialize();
	}
}

void Api::appendLog(const QString &s) {
	auto msg = new ApiMessage(RP_STATUS_OK, "", s, this);
	log_.prepend(msg);
	shouldUpdateLog_ = true;
}

bool Api::openCollectionFile(){
	QUrl url(collectionFilename_);
	collectionFilename_ = url.toLocalFile();
	qDebug() << "Opening collection file. " << collectionFilename_ << ".";
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
	stats_.stop_benchmark();
}

void Api::convertRfp(QString filename) {
	rpf_conversions_.push_back(std::async(std::launch::async, [=](QString fn) {
		try {
			fn.remove("file:///");
			IO::convert_rpf(fn);
			qInfo() << fn << " text conversion successfully.";
			Api::instance()->addMessageAsync(fn + " text conversion successfully.");
		}
		catch(const std::exception &err) {
			qWarning() << fn << " text conversion failed!";
			Api::instance()->addMessageAsync(fn + " text conversion failed!  " + err.what());
		}
	}, filename));
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
