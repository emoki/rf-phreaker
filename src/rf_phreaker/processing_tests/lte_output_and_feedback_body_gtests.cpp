#pragma once

#include "gtest/gtest.h"
#include "rf_phreaker/processing/lte_output_and_feedback_body.h"
#include "rf_phreaker/processing/data_output_async.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;
using namespace rf_phreaker::processing;

class LteOutputAndFeedbackBodyTest : public ::testing::Test
{
protected:
	LteOutputAndFeedbackBodyTest()
		: body_(&io_)
	{
		io_.set_standard_output(true).wait();
		reset_lte_meas();
	}
	
	void reset_lte_meas() 
	{
		lte_info.meas_.reset(new measurement_info(0, start_freq_, mhz(2.5), mhz(3.84), gain_type(), 0));
		lte_info.avg_rms_ = 400;
		lte_info.remove_ = false;
		lte_measurements meas_group;
		lte_measurement meas;
		meas.sync_quality = -10;
		meas.estimated_rsrp = .22;
		meas.estimated_rssi = .22;
		meas.estimated_rsrq = .22;
		for(int i = 0; i < 8; ++i) {
			meas_group.push_back(meas);
		}
		lte_info.processed_data_ = meas_group;
	}
	data_output_async io_;
	lte_sweep_output_and_feedback_body body_;
	lte_output_and_feedback_node::output_ports_type out_;
	lte_info lte_info;
	const static frequency_type start_freq_ = mhz(2100);
};

TEST_F(LteOutputAndFeedbackBodyTest, TestSweepBandwidth)
{
	for(int i = start_freq_; i < start_freq_ + mhz(9); i += khz(200)) {
		lte_info.meas_->frequency(i);
		body_(lte_info, out_);
	}

	lte_info.meas_->frequency(start_freq_ + mhz(10));
	lte_info.processed_data_[0].Bandwidth = LteBandwidth_20MHZ;
	lte_info.processed_data_[0].sync_quality -= 1;
	body_(lte_info, out_);

	lte_info.processed_data_[0].sync_quality += 1;
	for(int i = start_freq_ + mhz(11); i <= start_freq_ + mhz(20); i += khz(200)) {
		lte_info.meas_->frequency(i);
		body_(lte_info, out_);
	}

	lte_info.meas_->frequency(start_freq_ + mhz(10));
	lte_info.processed_data_[0].Bandwidth = LteBandwidth_20MHZ;
	lte_info.processed_data_[0].sync_quality += 1;
	body_(lte_info, out_);
}
