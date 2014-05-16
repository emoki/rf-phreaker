#include "gtest/gtest.h"
#include "rf_phreaker/cappeen/rf_phreaker_wrappers.h"

TEST(RfPhreakerWrappers, TestMain)
{
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;
	lte_sib1_type sib1;
	sib1.decoded_ = true;
	sib1.cell_id_ = 1000;
	sib1.tracking_area_code_ = 2000;
	for(int i = 0; i < 4; ++i) {
		layer_3_information::plmn p;
		p.mcc_ = std::string("310");
		p.mnc_ = std::to_string(i);
		sib1.multiple_plmn_.push_back(p);
	}

	std::vector<lte_sib1_wrapper> sib1s;
	sib1s.reserve(1);
	sib1s.push_back(lte_sib1_wrapper(sib1));

	lte_sib_1 b_sib1;
	b_sib1 = sib1s.back().s_;

	for(uint32_t i = 0; i < b_sib1.plmns_.num_elements_; ++i) {
		EXPECT_STREQ("310", b_sib1.plmns_.elements_[i].mcc_);
		EXPECT_STREQ(std::to_string(i).c_str(), b_sib1.plmns_.elements_[i].mnc_);
	}
}
