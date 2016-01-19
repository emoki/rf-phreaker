#pragma once

#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_conversion.h"
#include "rf_phreaker/rf_phreaker_api/data_wrappers.h"
#include "rf_phreaker/processing/data_output_async.h"

namespace rf_phreaker { namespace api {

class rf_phreaker_handler {
public:
	rf_phreaker_handler(processing::data_output_async *output, rp_callbacks *cb) 
	: callbacks_(cb) {
		// Do not connect error or message.  This are handled outside of this class because they 
		// can affect behavior.

		LOG_IF(LWARNING, (cb == nullptr)) << "No callbacks will be connected.";

		if(callbacks_ && callbacks_->rp_device_info_update)
			output->connect_hardware(boost::bind(&rf_phreaker_handler::output_device_info, this, _1)).get();
		if(callbacks_ && callbacks_->rp_gps_update)
			output->connect_gps(boost::bind(&rf_phreaker_handler::output_gps, this, _1)).get();
		if(callbacks_ && callbacks_->rp_sweep_update)
			output->connect_sweep(boost::bind(&rf_phreaker_handler::output_sweep, this, _1, _2, _3, _4)).get();
		//if(callbacks_ && callbacks_->rp_gsm_update)
			//output->connect_hardware(boost::bind(&rf_phreaker_handler::output_gsm, this, _1, _2)).get();
		if(callbacks_ && callbacks_->rp_wcdma_update)
			output->connect_umts_layer_3(boost::bind(&rf_phreaker_handler::output_umts, this, _1, _2)).get();
		if(callbacks_ && callbacks_->rp_lte_update)
			output->connect_lte_layer_3(boost::bind(&rf_phreaker_handler::output_lte, this, _1, _2)).get();
	}

	void output_message(rp_status stat, const std::string &str) {
		callbacks_->rp_message_update(stat, str.c_str());
	}

	void output_device_info(const hardware &t) {
		hardware_wrap wrap(t);
		callbacks_->rp_device_info_update(&wrap.buf_);
	}

	void output_gps(const gps &t) {
		gps_wrap wrap(t);
		callbacks_->rp_gps_update(&wrap.buf_);
	}

	void output_sweep(const basic_data &b, const std::vector<gsm_data> &g, const std::vector<umts_data> &u,
		const std::vector<lte_data> &l) {
		basic_wrap base(b);
		vector_wrap<umts_wrap, umts_data> wrap_u(u);
		vector_wrap<lte_wrap, lte_data> wrap_l(l);
		callbacks_->rp_sweep_update(&base.buf_, 0, 0, wrap_u.get(), wrap_u.size(), wrap_l.get(), wrap_l.size());
	}

	void output_gsm(const std::vector<gsm_data> &t, const basic_data &b) {
		vector_wrap<gsm_wrap, gsm_data> wrap(t);
		basic_wrap base(b);
		callbacks_->rp_gsm_update(&base.buf_, wrap.get(), wrap.size());
	}

	void output_umts(const std::vector<umts_data> &t, const basic_data &b) {
		vector_wrap<umts_wrap, umts_data> wrap(t);
		basic_wrap base(b);
		callbacks_->rp_wcdma_update(&base.buf_, wrap.get(), wrap.size());
	}

	void output_lte(const std::vector<lte_data> &t, const basic_data &b) {
		vector_wrap<lte_wrap, lte_data> wrap(t);
		basic_wrap base(b);
		callbacks_->rp_lte_update(&base.buf_, wrap.get(), wrap.size());
	}

private:
	rp_callbacks *callbacks_;
};


}}