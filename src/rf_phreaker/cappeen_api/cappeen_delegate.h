#pragma once

#include "rf_phreaker/cappeen_api/beagle_defines.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker { namespace cappeen_api {

class cappeen_delegate
{
public:
	cappeen_delegate(beagle_api::beagle_delegate *del)
		: delegate_(del)
	{
		if(del == nullptr)
			throw rf_phreaker::cappeen_api_error("Beagle delegate is NULL.", beagle_api::BEAGLEUNABLETOINITIALIZE);
	}
	
	~cappeen_delegate()
	{}

	void initialize(processing::data_output_async *data_output)
	{
		data_output->connect_hardware(boost::bind(&cappeen_delegate::output_hardware, this, _1)).wait();
		data_output->connect_gps(boost::bind(&cappeen_delegate::output_gps, this, _1)).wait();
		data_output->connect_umts_sweep(boost::bind(&cappeen_delegate::output_umts_sweep, this, _1)).wait();
		data_output->connect_umts_layer_3(boost::bind(&cappeen_delegate::output_umts_layer_3, this, _1)).wait();
		data_output->connect_lte_sweep(boost::bind(&cappeen_delegate::output_lte_sweep, this, _1)).wait();
		data_output->connect_lte_layer_3(boost::bind(&cappeen_delegate::output_lte_layer_3, this, _1)).wait();
	}

	void output_hardware(const hardware &t)
	{
		delegate_->available_beagle_info(beagle_info_->beagle_id_, *beagle_info_);
	}
	
	void output_gps(const gps &t)
	{
		beagle_api::gps_info g;
		g.gps_locked_ = t.lock_;
		g.hw_calibrated_ = false;
		g.lat_ = t.latitude_;
		g.lon_ = t.longitude_;
		g.num_track_sat_ = t.tracking_satellites_;
		g.num_visible_sat_ = t.visible_satellites_;
		g.raw_gps_status_ = (uint16_t)t.raw_status_;
		g.utc_time_ = t.coordinated_universal_time_;

		delegate_->available_gps_info(beagle_info_->beagle_id_, g);
	}
	
	void output_umts_sweep(const basic_data &t)
	{
	}
	
	void output_umts_layer_3(const std::vector<umts_data> &t)
	{
	}
	
	void output_lte_sweep(const basic_data &t)
	{}
	
	void output_lte_layer_3(const std::vector<lte_data> &t)
	{}

	void output_message(const std::exception &err)
	{
		output_error(err.what(), beagle_api::STD_EXCEPTION_ERROR);
	}

	void output_message(const rf_phreaker::rf_phreaker_error &err)
	{
		output_message(err.what(), (int)err.error_code_);
	}

	void output_error(const std::string &s, int code)
	{
		if(delegate_ != nullptr)
			delegate_->available_error(beagle_id_, code, s.c_str(), s.size() + 1);
	}

	void output_message(const std::string &s, int code)
	{
		if(delegate_ != nullptr)
			delegate_->available_error(beagle_id_, code, s.c_str(), s.size() + 1);
	}

private:
	beagle_api::beagle_delegate *delegate_;

	std::unique_ptr<beagle_api::beagle_info> beagle_info_;

	static const int beagle_id_ = 1;

};

}}