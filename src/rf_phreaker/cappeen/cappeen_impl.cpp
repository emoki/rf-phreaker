#include "rf_phreaker/cappeen/cappeen_impl.h"
#include "rf_phreaker/cappeen/operating_band_conversion.h"
#include "rf_phreaker/cappeen/beagle_defines.h"
#include "rf_phreaker/qt_specific/settings_io.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/processing/frequency_range_creation.h"
#include "rf_phreaker/common/log.h"

using namespace rf_phreaker;
using namespace rf_phreaker::cappeen_api;
using namespace beagle_api;

cappeen_impl::cappeen_impl()
: is_initialized_(false)
{
}

cappeen_impl::~cappeen_impl()
{}

long cappeen_impl::initialize(beagle_api::beagle_delegate *del)
{
	int status = 0;
	try{	
		// If logging fails continue anyway.
		try {
			logger_.reset(new init_log("cappeen_api", ""));
		}
		catch(...) {}

		LOG(INFO) << "Initializing cappeen api version " << api_version();

		is_initialized_ = false;

		LOG(DEBUG) << "Reading settings.";
		read_settings();

		// Release all components before changing delegate.
		delegate_.release();
		scanner_.release();
		data_output_.release();
		if(processing_graph_) {
			LOG(DEBUG) << "Found processing graph on heap.  Sending cancel request and releasing it.";
			processing_graph_->cancel();
			processing_graph_.release();
		}
		if(gps_graph_) {
			LOG(DEBUG) << "Found gps graph on heap.  Sending cancel request and releasing it.";
			gps_graph_->cancel();
			gps_graph_.release();
		}

		LOG(DEBUG) << "Constructing cappeen_delegate.";
		delegate_.reset(new cappeen_delegate(del));
		LOG(DEBUG) << "Constructing blade_rf_controller_async.";
		scanner_.reset(new scanner::blade_rf_controller_async(scanner::USB_BLADE_RF));
		LOG(DEBUG) << "Constructing data_output_async.";
		data_output_.reset(new processing::data_output_async());
		LOG(DEBUG) << "Constructing processing_graph.";
		processing_graph_.reset(new processing::processing_graph());
		LOG(DEBUG) << "Constructing gps_graph.";
		gps_graph_.reset(new processing::gps_graph());

		LOG(DEBUG) << "Initializing cappeen_delegate.";
		delegate_->initialize(data_output_.get());
		//log_worker_->connect_sink(boost::bind(&cappeen_delegate::output_error, delegate_.get(), _1, _2));

		LOG(INFO) << "Initialization complete.";
		is_initialized_ = true;
	}
	catch(const rf_phreaker::rf_phreaker_error &err) {
		if(delegate_) delegate_->output_message(err);
		status = (long)err.error_code_;
		LOG(ERROR) << err.what() << "  Error code: " << err.error_code_ << ".";
	}
	catch(const std::exception &err) {
		if(delegate_) delegate_->output_message(err);
		status = STD_EXCEPTION_ERROR;
		LOG(ERROR) << err.what();
	}
	catch(...) {
		if(delegate_) delegate_->output_message("Unknown error has occurred.", UNKNOWN_ERROR);
		status = UNKNOWN_ERROR;
		LOG(ERROR) << "Unknown error.";
	}
	return status;
}

void cappeen_impl::read_settings()
{
//	settings_io io("cappeen_api_v1", "cappeen");
	settings_io io("cappeen_api.ini");

	io.read(config_);
}

long cappeen_impl::clean_up()
{
	long status = 0;
	try {
		LOG(INFO) << "Cleaning up...";

		// Do more!
		processing_graph_->cancel();
		gps_graph_->cancel();

		delegate_.release();
		scanner_.release();
		data_output_.release();
		processing_graph_.release();
		gps_graph_.release();
		LOG(INFO) << "Cleaned up successfully.";
	}
	catch(const rf_phreaker::rf_phreaker_error &err) {
		if(delegate_) delegate_->output_message(err);
		status = (long)err.error_code_;
	}
	catch(const std::exception &err) {
		if(delegate_) delegate_->output_message(err);
		status = STD_EXCEPTION_ERROR;
	}
	catch(...) {
		if(delegate_) delegate_->output_message("Unknown error has occurred.", UNKNOWN_ERROR);
		status = UNKNOWN_ERROR;
	}

	try {
		logger_.release();
	}
	catch(...) {}
	return status;
}


long cappeen_impl::list_available_units(char *list, unsigned int buf_size)
{
	long status = 0;
	try {
		LOG(INFO) << "Listing units...";
		verify_init();

		memset(list, 0, buf_size);

		auto scanner_list = scanner_->list_available_scanners().get();
		// Sometimes the libbladeRF reports there is a connected unit but does not give serial.
		// Requesting the list again seems to fix it.
		if(scanner_list.size() && (*scanner_list.begin())->id() == "")
			scanner_list = scanner_->list_available_scanners().get();

		std::string str;
		for(auto &scanner : scanner_list) {
			str += scanner->id() + ";";
		}
		if(buf_size < str.size() + 1)
			throw rf_phreaker_error("Error while listing available units.  buf_size is not large enough.  buf_size should be at least "
			+ boost::lexical_cast<std::string>(str.size() + 1) + ".", BUFFER_TOO_SMALL);
		else
			memcpy(list, str.c_str(), str.size() + 1);
		LOG(INFO) << "Listed units successfully.";
	}
	catch(const rf_phreaker::rf_phreaker_error &err) {
		if(delegate_) delegate_->output_message(err);
		status = (long)err.error_code_;
	}
	catch(const std::exception &err) {
		if(delegate_) delegate_->output_message(err);
		status = STD_EXCEPTION_ERROR;
	}
	catch(...) {
		if(delegate_) delegate_->output_message("Unknown error has occurred.", UNKNOWN_ERROR);
		status = UNKNOWN_ERROR;
	}
	return status;
}

void cappeen_impl::verify_init()
{
	if(!is_initialized_)
		throw rf_phreaker::cappeen_api_error("Cappeen API not initialized correctly.", BEAGLENOTINITIALIZED);
}

long cappeen_impl::open_unit(const char *serial, unsigned int buf_size)
{
	long status = 0;
	try {
		LOG(INFO) << "Opening unit " << serial << "...";
		verify_init();

		scanner_->open_scanner(serial).get();

		auto hw = scanner_->get_scanner().get()->get_hardware();
		delegate_->initialize_beagle_info(hw);
		delegate_->change_beagle_state(BEAGLE_USBOPENED);

		scanner_->do_initial_scanner_config().get();

		gps_graph_->initialize_comm(scanner_.get(), data_output_.get(), config_);
		gps_graph_->start();
		LOG(INFO) << "Opened unit " << serial << " successfully.";
	}
	catch(const rf_phreaker::rf_phreaker_error &err) {
		if(delegate_) delegate_->output_message(err);
		status = (long)err.error_code_;
	}
	catch(const std::exception &err) {
		if(delegate_) delegate_->output_message(err);
		status = STD_EXCEPTION_ERROR;
	}
	catch(...) {
		if(delegate_) delegate_->output_message("Unknown error has occurred.", UNKNOWN_ERROR);
		status = UNKNOWN_ERROR;
	}
	return status;
}

long cappeen_impl::close_unit(const char *serial, unsigned int buf_size)
{
	long status = 0;
	try{
		LOG(INFO) << "Closing unit " << serial << "...";
		verify_init();

		gps_graph_->cancel();
		
		processing_graph_->cancel();

		scanner_->close_scanner().get();
		delegate_->change_beagle_state(BEAGLE_USBCLOSED);
		LOG(INFO) << "Closed unit " << serial << " successfully.";
	}
	catch(const rf_phreaker::rf_phreaker_error &err) {
		if(delegate_) delegate_->output_message(err);
		status = (long)err.error_code_;
	}
	catch(const std::exception &err) {
		if(delegate_) delegate_->output_message(err);
		status = STD_EXCEPTION_ERROR;
	}
	catch(...) {
		if(delegate_) delegate_->output_message("Unknown error has occurred.", UNKNOWN_ERROR);
		status = UNKNOWN_ERROR;
	}
	return status;
}

long cappeen_impl::stop_collection()
{
	long status = 0;
	try {
		LOG(INFO) << "Stopping collection...";
		processing_graph_->cancel();
		delegate_->change_beagle_state(BEAGLE_READY);
		LOG(INFO) << "Stopped collection successfully.";
	}
	catch(const rf_phreaker::rf_phreaker_error &err) {
		if(delegate_) delegate_->output_message(err);
		status = (long)err.error_code_;
	}
	catch(const std::exception &err) {
		if(delegate_) delegate_->output_message(err);
		status = STD_EXCEPTION_ERROR;
	}
	catch(...) {
		if(delegate_) delegate_->output_message("Unknown error has occurred.", UNKNOWN_ERROR);
		status = UNKNOWN_ERROR;
	}
	return status;
}

long cappeen_impl::start_collection(const beagle_api::collection_info &collection)
{
	long status = 0;
	try {
		LOG(INFO) << "Starting collection...";
		// Initialize packet sizes.
		read_settings();
		processing::initialize_collection_info_defaults(config_);

		auto collection_containers = create_collection_info_containers(collection);

		processing_graph_->initialize_collection(scanner_.get(), data_output_.get(), collection_containers, config_);

		processing_graph_->start();

		delegate_->change_beagle_state(BEAGLE_COLLECTING);
		LOG(INFO) << "Started collection successfully.";
	}
	catch(const rf_phreaker::rf_phreaker_error &err) {
		if(delegate_) delegate_->output_message(err);
		status = (long)err.error_code_;
	}
	catch(const std::exception &err) {
		if(delegate_) delegate_->output_message(err);
		status = STD_EXCEPTION_ERROR;
	}
	catch(...) {
		if(delegate_) delegate_->output_message("Unknown error has occurred.", UNKNOWN_ERROR);
		status = UNKNOWN_ERROR;
	}
	return status;
}

processing::collection_info_containers cappeen_impl::create_collection_info_containers(const beagle_api::collection_info &collection)
{
	using namespace processing;

	collection_info_containers containers;

	for(uint32_t i = 0, end = collection.tech_and_bands_to_sweep_.num_elements_; i < end; ++i) {
		auto band = convert_band(collection.tech_and_bands_to_sweep_.elements_[i]);

		collection_info_container *container = nullptr;

		// Temporarily ignore LTE
		if(band >= FIRST_UMTS_OPERATING_BAND && band <= LAST_UMTS_OPERATING_BAND) {
			auto it = std::find_if(containers.begin(), containers.end(), [&](const collection_info_container &c) {
				return c.tech_ == UMTS_SWEEP;
			});

			if(it == containers.end()) {
				containers.push_back(collection_info_container(UMTS_SWEEP, true));
				containers.push_back(collection_info_container(UMTS_LAYER_3_DECODE, false));
				it = std::find_if(containers.begin(), containers.end(), [&](const collection_info_container &c) {
					return c.tech_ == UMTS_SWEEP;
				});
			}

			frequency_range_creation::adjust_umts_sweep_collection_info(operating_bands_.get_band_freq_range(band), *it);
		}
		else if(band >= FIRST_LTE_OPERATING_BAND && band <= LAST_LTE_OPERATING_BAND) {
			auto it = std::find_if(containers.begin(), containers.end(), [&](const collection_info_container &c) {
				return c.tech_ == LTE_SWEEP;
			});

			if(it == containers.end()) {
				containers.push_back(collection_info_container(LTE_SWEEP, true));
				containers.push_back(collection_info_container(LTE_LAYER_3_DECODE, false));
				it = std::find_if(containers.begin(), containers.end(), [&](const collection_info_container &c) {
					return c.tech_ == LTE_SWEEP;
				});
			}

			frequency_range_creation::adjust_lte_sweep_collection_info(operating_bands_.get_band_freq_range(band), *it);
		}
	}
	return containers;
}

long cappeen_impl::input_new_license(const char *serial, uint32_t serial_buf_size, const char *new_license_filename, uint32_t license_buf_size)
{
	long status = 0;
	try {
		LOG(INFO) << "Updating new license...";
		throw std::exception("Updating the license is not currently supported.");
		LOG(INFO) << "Updated license successfully.";
	}
	catch(const rf_phreaker::rf_phreaker_error &err) {
		if(delegate_) delegate_->output_message(err);
		status = (long)err.error_code_;
	}
	catch(const std::exception &err) {
		if(delegate_) delegate_->output_message(err);
		status = STD_EXCEPTION_ERROR;
	}
	catch(...) {
		if(delegate_) delegate_->output_message("Unknown error has occurred.", UNKNOWN_ERROR);
		status = UNKNOWN_ERROR;
	}
	return status;
}

const char* cappeen_impl::api_version()
{
	return "0.9.3";
}
