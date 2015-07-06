#include "gtest/gtest.h"
#include "rf_phreaker/lte_analysis/lte_si_tracker.h"

using namespace rf_phreaker;
using namespace layer_3_information;

TEST(LteFrameInfo, TestGeneral)
{
	layer_3_information::scheduling_info s;
	s.periodicity_in_frames_ = 64;
	s.sib_mapping_info_.push_back(lte_sib_type::SIB_3);
	{
		lte_si_info info1(s, 2, 20);
		EXPECT_EQ(0, info1.starting_subframe());
		EXPECT_EQ(false, info1.is_relevant_frame(640));
		EXPECT_EQ(false, info1.is_relevant_frame(641));
		EXPECT_EQ(true, info1.is_relevant_frame(642));
		EXPECT_EQ(true, info1.is_relevant_frame(643));
		EXPECT_EQ(false, info1.is_relevant_frame(644));

		lte_si_info info2(s, 2, 2);
		EXPECT_EQ(2, info2.starting_subframe());
		EXPECT_EQ(true, info2.is_relevant_frame(640));
		EXPECT_EQ(false, info2.is_relevant_frame(641));
		EXPECT_EQ(false, info2.is_relevant_frame(642));
		EXPECT_EQ(false, info2.is_relevant_frame(643));

		lte_si_info info3(s, 2, 5);
		EXPECT_EQ(5, info3.starting_subframe());
		EXPECT_EQ(true, info3.is_relevant_frame(640));
		EXPECT_EQ(false, info3.is_relevant_frame(641));
		EXPECT_EQ(false, info3.is_relevant_frame(642));
		EXPECT_EQ(false, info3.is_relevant_frame(643));

		s.periodicity_in_frames_ = 16;
		lte_si_info info4(s, 2, 20);
		EXPECT_EQ(0, info4.starting_subframe());
		EXPECT_EQ(false, info4.is_relevant_frame(16));
		EXPECT_EQ(false, info4.is_relevant_frame(17));
		EXPECT_EQ(true, info4.is_relevant_frame(18));
		EXPECT_EQ(true, info4.is_relevant_frame(19));
		EXPECT_EQ(false, info4.is_relevant_frame(20));
		EXPECT_EQ(false, info4.is_relevant_frame(32));
		EXPECT_EQ(false, info4.is_relevant_frame(33));
		EXPECT_EQ(true, info4.is_relevant_frame(34));
		EXPECT_EQ(true, info4.is_relevant_frame(35));
		EXPECT_EQ(false, info4.is_relevant_frame(36));

		s.periodicity_in_frames_ = 16;
		lte_si_info info5(s, 1, 2);
		EXPECT_EQ(0, info5.starting_subframe());
		EXPECT_EQ(false, info5.is_relevant_frame(15));
		EXPECT_EQ(true, info5.is_relevant_frame(16));
		EXPECT_EQ(false, info5.is_relevant_frame(17));

	}
}

TEST(CellsOnChannel, TestAllScheduling) {
	si_tracker s;
	lte_measurements measurements;
	frequency_type f = 1;
	for(int i = 0; i < 5; ++i) {
		lte_measurement meas;
		meas.RsRecord.ID = i;
		meas.layer_3_.sib1_.is_decoded_ = std::rand() % 2 == 0;
		if(meas.layer_3_.sib1_.is_decoded_) {
			meas.layer_3_.sib1_.si_window_length_ms_ = 20;
			meas.layer_3_.sib1_.scheduling_info_list_.push_back(scheduling_info{16, {SIB_3, SIB_4}});
			meas.layer_3_.sib1_.scheduling_info_list_.push_back(scheduling_info{64, {SIB_5, SIB_6}});
		}
		measurements.push_back(meas);
	}
	s.update(f, measurements);

	for(auto &meas : measurements) {
		auto group = s.get_all_scheduling_info(f, meas);
		if(meas.layer_3_.sib1_.is_decoded_)
			EXPECT_EQ(2, group.g_.size());
		else
			EXPECT_EQ(0, group.g_.size());

		auto g = s.get_all_scheduling_info(0, meas);
		EXPECT_EQ(0, g.g_.size());
	}
}

TEST(CellsOnChannel, TestNeededScheduling) {
	si_tracker s;
	lte_measurements measurements;
	frequency_type f = 1;
	for(int i = 0; i < 5; ++i) {
		lte_measurement meas;
		meas.RsRecord.ID = i;
		meas.layer_3_.sib1_.is_decoded_ = i % 2 == 0;
		if(meas.layer_3_.sib1_.is_decoded_) {
			meas.layer_3_.sib1_.si_window_length_ms_ = 20;
			meas.layer_3_.sib1_.scheduling_info_list_.push_back(scheduling_info{16, {SIB_3, SIB_4}});
			meas.layer_3_.sib1_.scheduling_info_list_.push_back(scheduling_info{64, {SIB_5, SIB_6}});
		}
		measurements.push_back(meas);
	}
	s.update(f, measurements);

	measurements[0].layer_3_.sib3_.is_decoded_ = true;
	measurements[0].layer_3_.sib4_.is_decoded_ = true;
	measurements[0].layer_3_.sib5_.is_decoded_ = true;
	measurements[0].layer_3_.sib6_.is_decoded_ = true;

	measurements[2].layer_3_.sib3_.is_decoded_ = true;
	measurements[2].layer_3_.sib4_.is_decoded_ = true;
	measurements[2].layer_3_.sib5_.is_decoded_ = false;
	measurements[2].layer_3_.sib6_.is_decoded_ = false;

	s.update(f, measurements);

	int i = 0;
	for(auto &meas : measurements) {
		auto group = s.get_all_scheduling_info(f, meas);
		if(meas.layer_3_.sib1_.is_decoded_) {
			EXPECT_EQ(2, group.g_.size());
			EXPECT_EQ(true, s.has_scheduling_info(f, meas));
		}
		else {
			EXPECT_EQ(0, group.g_.size());
			EXPECT_EQ(false, s.has_scheduling_info(f, meas));
		}
		if(i == 0) {
			auto g = s.get_needed_scheduling_info(f, meas);
			EXPECT_EQ(0, g.g_.size());
		}
		else if(i == 2) {
			auto g = s.get_needed_scheduling_info(f, meas);
			EXPECT_EQ(1, g.g_.size());
			EXPECT_EQ(64, g.g_.begin()->scheduling_info_.periodicity_in_frames_);
		}
		else {
			auto g = s.get_needed_scheduling_info(f, meas);
			if(meas.layer_3_.sib1_.is_decoded_)
				EXPECT_EQ(2, g.g_.size());
			else
				EXPECT_EQ(0, g.g_.size());
		}

		EXPECT_EQ(0, s.get_all_scheduling_info(33, meas).g_.size());
		EXPECT_EQ(0, s.get_needed_scheduling_info(33, meas).g_.size());
		EXPECT_EQ(false, s.has_scheduling_info(33, meas));

		++i;
	}

}

