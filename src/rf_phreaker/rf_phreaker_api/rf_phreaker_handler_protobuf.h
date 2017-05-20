#pragma once

#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_conversion.h"
#include "rf_phreaker/processing/data_output_async.h"
#include "rf_phreaker/protobuf_specific/rf_phreaker_serialization.h"

namespace rf_phreaker { namespace api {

class rf_phreaker_handler_protobuf {
public:
	rf_phreaker_handler_protobuf(processing::data_output_async *output, rp_callbacks *cb)
		: callbacks_(cb) {
		// Do not connect error or message.  This are handled outside of this class because they 
		// can affect behavior.

		LOG_IF(LWARNING, (cb == nullptr)) << "No callbacks will be connected to rf_phreaker_handler_pb.";

		if(callbacks_ && callbacks_->rp_update) {
			output->connect_hardware(boost::bind(&rf_phreaker_handler_protobuf::output_device_info, this, _1)).get();
			output->connect_gps(boost::bind(&rf_phreaker_handler_protobuf::output_gps, this, _1)).get();
			output->connect_gsm_sweep(boost::bind(&rf_phreaker_handler_protobuf::output_gsm_sweep, this, _1, _2)).get();
			output->connect_umts_sweep(boost::bind(&rf_phreaker_handler_protobuf::output_wcdma_sweep, this, _1, _2)).get();
			output->connect_lte_sweep(boost::bind(&rf_phreaker_handler_protobuf::output_lte_sweep, this, _1, _2)).get();
			output->connect_gsm_layer_3(boost::bind(&rf_phreaker_handler_protobuf::output_gsm_full_scan, this, _1, _2)).get();
			output->connect_umts_layer_3(boost::bind(&rf_phreaker_handler_protobuf::output_umts_full_scan, this, _1, _2)).get();
			output->connect_lte_layer_3(boost::bind(&rf_phreaker_handler_protobuf::output_lte_full_scan, this, _1, _2)).get();
			output->connect_power_spectrum(boost::bind(&rf_phreaker_handler_protobuf::output_power_spectrum, this, _1)).get();
			output->connect_iq_data(boost::bind(&rf_phreaker_handler_protobuf::output_iq_data, this, _1)).get();
		}
	}

	void output_device_info(const hardware &t) {
		update_.populate_device_info(t);
		update_.serialize();
		callbacks_->rp_update(update_.to_bytes(), update_.size());
	}

	void output_gps(const gps &t) {
		update_.populate_gps(t);
		update_.serialize();
		callbacks_->rp_update(update_.to_bytes(), update_.size());
	}

	void output_gsm_sweep(const basic_data &b, const std::vector<gsm_data> &g) {
		update_.populate_gsm_sweep(g, b);
		update_.serialize();
		callbacks_->rp_update(update_.to_bytes(), update_.size());
	}

	void output_wcdma_sweep(const basic_data &b, const std::vector<umts_data> &u) {
		update_.populate_wcdma_sweep(u, b);
		update_.serialize();
		callbacks_->rp_update(update_.to_bytes(), update_.size());
	}

	void output_lte_sweep(const basic_data &b, const std::vector<lte_data> &l) {
		update_.populate_lte_sweep(l, b);
		update_.serialize();
		callbacks_->rp_update(update_.to_bytes(), update_.size());
	}

	void output_gsm_full_scan(const std::vector<gsm_data> &t, const basic_data &b) {
		update_.populate_gsm_full_scan(t, b);
		update_.serialize();
		callbacks_->rp_update(update_.to_bytes(), update_.size());
	}

	void output_umts_full_scan(const std::vector<umts_data> &t, const basic_data &b) {
		update_.populate_wcdma_full_scan(t, b);
		update_.serialize();
		callbacks_->rp_update(update_.to_bytes(), update_.size());
	}

	void output_lte_full_scan(const std::vector<lte_data> &t, const basic_data &b) {
		update_.populate_lte_full_scan(t, b);
		update_.serialize();
		callbacks_->rp_update(update_.to_bytes(), update_.size());
	}

	void output_power_spectrum(const power_spectrum_data &t) {
		update_.populate_power_spectrum(t);
		update_.serialize();
		callbacks_->rp_update(update_.to_bytes(), update_.size());
	}

	void output_iq_data(const iq_data &t) {
		update_.populate_iq_data(t);
		update_.serialize();
		callbacks_->rp_update(update_.to_bytes(), update_.size());
	}

private:
	rp_callbacks *callbacks_;
	protobuf::update_pb update_;
};

}}