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
		output_settings settings = {true, true, true, true, true};
		io_.set_standard_output(settings).wait();
		reset_lte_meas();
	}
	
	void reset_lte_meas() 
	{
		lte_info.measurement_package_.measurement_info_.reset(new measurement_info(0, start_freq_, mhz(2.5), mhz(3.84), gain_type(), std::chrono::milliseconds(0)));
		power_info_group a{power_info(start_freq_, mhz(2.5), mhz(3.84))};
		lte_info.power_info_group_ = a;
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
	auto meas = lte_info.measurement_package_.measurement_info_.get();
	for(int i = start_freq_; i < start_freq_ + mhz(9); i += khz(200)) {
		meas->frequency(i);
		body_(lte_info, out_);
	}

	meas->frequency(start_freq_ + mhz(10));
	lte_info.processed_data_[0].Bandwidth = LteBandwidth_20MHZ;
	lte_info.processed_data_[0].sync_quality -= 1;
	body_(lte_info, out_);

	lte_info.processed_data_[0].sync_quality += 1;
	for(int i = start_freq_ + mhz(11); i <= start_freq_ + mhz(20); i += khz(200)) {
		meas->frequency(i);
		body_(lte_info, out_);
	}

	meas->frequency(start_freq_ + mhz(10));
	lte_info.processed_data_[0].Bandwidth = LteBandwidth_20MHZ;
	lte_info.processed_data_[0].sync_quality += 1;
	body_(lte_info, out_);
}
 