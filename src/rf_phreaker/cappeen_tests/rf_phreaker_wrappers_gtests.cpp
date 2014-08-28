#include "gtest/gtest.h"
#include "rf_phreaker/cappeen/rf_phreaker_wrappers.h"

TEST(RfPhreakerWrappers, Sib1)
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

TEST(RfPhreakerWrappers, Sib3) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;
	
	int var = 0;
	lte_sib3_type sib;
	sib.cell_reselection_serving_freq_info_.cell_reselection_priority_ = var++;
	sib.cell_reselection_serving_freq_info_.s_non_intra_search_ = var++;
	sib.cell_reselection_serving_freq_info_.threshold_serving_low_ = var++;
	sib.intra_freq_cell_reselection_info_.s_intra_search_ = var++;
	sib.s_intra_search_v920_.p_ = var++;
	sib.s_intra_search_v920_.q_ = var++;
	sib.s_non_intra_search_v920_.p_ = var++;
	sib.s_non_intra_search_v920_.q_ = var++;
	sib.threshold_serving_low_q_ = var++;

	std::vector<lte_sib3_wrapper> sib_wrappers;
	sib_wrappers.reserve(1);
	sib_wrappers.push_back(lte_sib3_wrapper(sib));
	auto test = sib_wrappers[0];

	EXPECT_EQ(sib.decoded_,
		test.s_.decoded_);

	EXPECT_EQ(sib.cell_reselection_serving_freq_info_.cell_reselection_priority_,
		test.s_.cell_reselection_serving_freq_info_.cell_reselection_priority_);
	EXPECT_EQ(sib.cell_reselection_serving_freq_info_.s_non_intra_search_.reselection_threshold(),
		test.s_.cell_reselection_serving_freq_info_.s_non_intra_search_);
	EXPECT_EQ(sib.cell_reselection_serving_freq_info_.threshold_serving_low_.reselection_threshold(),
		test.s_.cell_reselection_serving_freq_info_.threshold_serving_low_);
	
	EXPECT_EQ(sib.intra_freq_cell_reselection_info_.s_intra_search_.reselection_threshold(),
		test.s_.intra_freq_cell_reselection_info_.s_intra_search_);
	
	EXPECT_EQ(sib.s_intra_search_v920_.p_.reselection_threshold(),
		test.s_.s_intra_search_v920_.reselection_threshold_p_);
	EXPECT_EQ(sib.s_intra_search_v920_.q_,
		test.s_.s_intra_search_v920_.reselection_threshold_q_);
	
	EXPECT_EQ(sib.s_non_intra_search_v920_.p_.reselection_threshold(),
		test.s_.s_non_intra_search_v920_.reselection_threshold_p_);
	EXPECT_EQ(sib.s_non_intra_search_v920_.q_,
		test.s_.s_non_intra_search_v920_.reselection_threshold_q_);

	EXPECT_EQ(sib.threshold_serving_low_q_,
		test.s_.threshold_serving_low_q_);
}

TEST(RfPhreakerWrappers, Sib4) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;
	
	int var = 0;
	lte_sib4_type sib;
	sib.decoded_ = true;
	sib.csg_physical_cellid_range_.range_ = var++;
	sib.csg_physical_cellid_range_.start_ = var++;
	physical_cellid_range tmp;
	tmp.range_ = var++; tmp.start_ = var++;
	sib.intra_freq_black_cell_list_.push_back(tmp);
	tmp.range_ = var++; tmp.start_ = var++;
	sib.intra_freq_black_cell_list_.push_back(tmp);
	neighbor_cell tmp1;
	tmp1.physical_cell_id_ = var++; tmp1.q_offset_cell_ = var++;
	sib.intra_freq_neighbor_cell_list_.push_back(tmp1);
	tmp1.physical_cell_id_ = var++; tmp1.q_offset_cell_ = var++;
	sib.intra_freq_neighbor_cell_list_.push_back(tmp1);

	std::vector<lte_sib4_wrapper> sib_wrappers;
	sib_wrappers.reserve(1);
	sib_wrappers.push_back(lte_sib4_wrapper(sib));
	auto test = sib_wrappers[0];

	EXPECT_EQ(sib.decoded_,
		test.s_.decoded_);

	EXPECT_EQ(sib.csg_physical_cellid_range_.range_,
		test.s_.csg_physical_cellid_range_.range_);
	EXPECT_EQ(sib.csg_physical_cellid_range_.start_,
		test.s_.csg_physical_cellid_range_.start_);

	EXPECT_EQ(sib.intra_freq_black_cell_list_[0].range_,
		test.s_.intra_freq_black_cell_list_.elements_[0].range_);
	EXPECT_EQ(sib.intra_freq_black_cell_list_[0].start_,
		test.s_.intra_freq_black_cell_list_.elements_[0].start_);

	EXPECT_EQ(sib.intra_freq_neighbor_cell_list_[0].physical_cell_id_,
		test.s_.intra_freq_neighbor_cell_list_.elements_[0].physical_cell_id_);
	EXPECT_EQ(sib.intra_freq_neighbor_cell_list_[0].q_offset_cell_,
		test.s_.intra_freq_neighbor_cell_list_.elements_[0].q_offset_cell_);
}

TEST(RfPhreakerWrappers, Sib5) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;

	int var = 0;
	lte_sib5_type sib;
	sib.decoded_ = true;
	inter_freq_carrier_freq_info tmp;
	tmp.allowed_measurement_bandwidth_ = var++;
	tmp.cell_reselection_priority_ = var++;
	tmp.downlink_arfcn_value_eutra_ = var++;
	tmp.presence_antenna_port_1_ = true;
	tmp.q_offset_freq_ = var++;
	tmp.q_rx_lev_min_ = var++;
	tmp.threshold_x_high_ = var++;
	tmp.threshold_x_high_q_r9_ = var++;
	tmp.threshold_x_low_ = var++;
	tmp.threshold_x_low_q_r9_ = var++;
	physical_cellid_range tmp1;
	tmp1.range_ = var++; tmp1.start_ = var++;
	tmp.inter_freq_black_cell_list_.push_back(tmp1);
	tmp1.range_ = var++; tmp1.start_ = var++;
	tmp.inter_freq_black_cell_list_.push_back(tmp1);
	neighbor_cell tmp2;
	tmp2.physical_cell_id_ = var++; tmp2.q_offset_cell_ = var++;
	tmp.inter_freq_neighbor_cell_list_.push_back(tmp2);
	tmp2.physical_cell_id_ = var++; tmp2.q_offset_cell_ = var++;
	tmp.inter_freq_neighbor_cell_list_.push_back(tmp2);

	sib.inter_freq_carrier_info_list_.push_back(tmp);

	std::vector<lte_sib5_wrapper> sib_wrappers;
	sib_wrappers.reserve(1);
	sib_wrappers.push_back(lte_sib5_wrapper(sib));
	auto test = sib_wrappers[0];

	EXPECT_EQ(sib.decoded_,
		test.s_.decoded_);

	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].allowed_measurement_bandwidth_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].allowed_measurement_bandwidth_);

	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].cell_reselection_priority_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].cell_reselection_priority_);
	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].downlink_arfcn_value_eutra_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].downlink_arfcn_value_eutra_);
	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].presence_antenna_port_1_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].presence_antenna_port_1_);
	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].q_offset_freq_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].q_offset_freq_);
	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].q_rx_lev_min_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].q_rx_lev_min_);
	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].threshold_x_high_.reselection_threshold(),
		test.s_.inter_freq_carrier_info_list_.elements_[0].threshold_x_high_);
	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].threshold_x_high_q_r9_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].threshold_x_high_q_r9_);
	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].threshold_x_low_.reselection_threshold(),
		test.s_.inter_freq_carrier_info_list_.elements_[0].threshold_x_low_);
	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].threshold_x_low_q_r9_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].threshold_x_low_q_r9_);

	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].inter_freq_black_cell_list_[0].range_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].inter_freq_black_cell_list_.elements_[0].range_);
	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].inter_freq_black_cell_list_[0].start_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].inter_freq_black_cell_list_.elements_[0].start_);
	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].inter_freq_neighbor_cell_list_[0].physical_cell_id_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].inter_freq_neighbor_cell_list_.elements_[0].physical_cell_id_);
	EXPECT_EQ(sib.inter_freq_carrier_info_list_[0].inter_freq_neighbor_cell_list_[0].q_offset_cell_,
		test.s_.inter_freq_carrier_info_list_.elements_[0].inter_freq_neighbor_cell_list_.elements_[0].q_offset_cell_);
}

TEST(RfPhreakerWrappers, Sib6) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;

	int var = 0;
	lte_sib6_type sib;
	sib.decoded_ = true;
	layer_3_information::carrier_freq_utra tmp;
	tmp.arfcn_value_utra_ = var++;
	tmp.cell_reselection_priority_ = var++;
	tmp.threshold_x_high_ = var++;
	tmp.threshold_x_high_q_r9_ = var++;
	tmp.threshold_x_low_ = var++;
	tmp.threshold_x_low_q_r9_ = var++;
	sib.carrier_freq_list_utra_fdd_.push_back(tmp);
	
	tmp.arfcn_value_utra_ = var++;
	tmp.cell_reselection_priority_ = var++;
	tmp.threshold_x_high_ = var++;
	tmp.threshold_x_high_q_r9_ = var++;
	tmp.threshold_x_low_ = var++;
	tmp.threshold_x_low_q_r9_ = var++;
	sib.carrier_freq_list_utra_tdd_.push_back(tmp);
	
	std::vector<lte_sib6_wrapper> sib_wrappers;
	sib_wrappers.reserve(1);
	sib_wrappers.push_back(lte_sib6_wrapper(sib));
	auto test = sib_wrappers[0];

	EXPECT_EQ(sib.decoded_,
		test.s_.decoded_);

	EXPECT_EQ(sib.carrier_freq_list_utra_fdd_[0].arfcn_value_utra_,
		test.s_.carrier_freq_list_utra_fdd_.elements_[0].arfcn_value_utra_);
	EXPECT_EQ(sib.carrier_freq_list_utra_fdd_[0].cell_reselection_priority_,
		test.s_.carrier_freq_list_utra_fdd_.elements_[0].cell_reselection_priority_);
	EXPECT_EQ(sib.carrier_freq_list_utra_fdd_[0].threshold_x_high_.reselection_threshold(),
		test.s_.carrier_freq_list_utra_fdd_.elements_[0].threshold_x_high_);
	EXPECT_EQ(sib.carrier_freq_list_utra_fdd_[0].threshold_x_high_q_r9_,
		test.s_.carrier_freq_list_utra_fdd_.elements_[0].threshold_x_high_q_r9_);
	EXPECT_EQ(sib.carrier_freq_list_utra_fdd_[0].threshold_x_low_.reselection_threshold(),
		test.s_.carrier_freq_list_utra_fdd_.elements_[0].threshold_x_low_);
	EXPECT_EQ(sib.carrier_freq_list_utra_fdd_[0].threshold_x_low_q_r9_,
		test.s_.carrier_freq_list_utra_fdd_.elements_[0].threshold_x_low_q_r9_);

	EXPECT_EQ(sib.carrier_freq_list_utra_tdd_[0].arfcn_value_utra_,
		test.s_.carrier_freq_list_utra_tdd_.elements_[0].arfcn_value_utra_);
	EXPECT_EQ(sib.carrier_freq_list_utra_tdd_[0].cell_reselection_priority_,
		test.s_.carrier_freq_list_utra_tdd_.elements_[0].cell_reselection_priority_);
	EXPECT_EQ(sib.carrier_freq_list_utra_tdd_[0].threshold_x_high_.reselection_threshold(),
		test.s_.carrier_freq_list_utra_tdd_.elements_[0].threshold_x_high_);
	EXPECT_EQ(sib.carrier_freq_list_utra_tdd_[0].threshold_x_high_q_r9_,
		test.s_.carrier_freq_list_utra_tdd_.elements_[0].threshold_x_high_q_r9_);
	EXPECT_EQ(sib.carrier_freq_list_utra_tdd_[0].threshold_x_low_.reselection_threshold(),
		test.s_.carrier_freq_list_utra_tdd_.elements_[0].threshold_x_low_);
	EXPECT_EQ(sib.carrier_freq_list_utra_tdd_[0].threshold_x_low_q_r9_,
		test.s_.carrier_freq_list_utra_tdd_.elements_[0].threshold_x_low_q_r9_);
}

TEST(RfPhreakerWrappers, Sib7) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;

	int var = 0;
	lte_sib7_type sib;
	sib.decoded_ = true;
	carrier_freqs_info_geran tmp;
	tmp.carrier_freqs_.band_indicator_ = dcs_1800_was_used;
	tmp.carrier_freqs_.following_arfcns_.push_back(var);
	tmp.carrier_freqs_.starting_arfcn_ = var++;
	tmp.carrier_freqs_.following_arfcns_.push_back(var++);
	tmp.common_info_.cell_reselection_priority_ = var++;
	tmp.common_info_.threshold_x_high_ = var++;
	tmp.common_info_.threshold_x_low_ = var++;
	sib.carrier_freqs_info_list_geran_.push_back(tmp);

	std::vector<lte_sib7_wrapper> sib_wrappers;
	sib_wrappers.reserve(1);
	sib_wrappers.push_back(lte_sib7_wrapper(sib));
	auto test = sib_wrappers[0];

	EXPECT_EQ(sib.decoded_,
		test.s_.decoded_);

	EXPECT_EQ(sib.carrier_freqs_info_list_geran_[0].carrier_freqs_.band_indicator_,
		test.s_.carrier_freqs_.elements_[0].band_indicator_);
	EXPECT_EQ(sib.carrier_freqs_info_list_geran_[0].carrier_freqs_.starting_arfcn_,
		test.s_.carrier_freqs_.elements_[0].arfcns_.elements_[0]);
	EXPECT_EQ(sib.carrier_freqs_info_list_geran_[0].carrier_freqs_.following_arfcns_[0],
		test.s_.carrier_freqs_.elements_[0].arfcns_.elements_[0]);

	EXPECT_EQ(sib.carrier_freqs_info_list_geran_[0].common_info_.cell_reselection_priority_,
		test.s_.carrier_freqs_.elements_[0].common_info_.cell_reselection_priority_);
	EXPECT_EQ(sib.carrier_freqs_info_list_geran_[0].common_info_.threshold_x_high_.reselection_threshold(),
		test.s_.carrier_freqs_.elements_[0].common_info_.threshold_x_high_);
	EXPECT_EQ(sib.carrier_freqs_info_list_geran_[0].common_info_.threshold_x_low_.reselection_threshold(),
		test.s_.carrier_freqs_.elements_[0].common_info_.threshold_x_low_);
}
 
TEST(RfPhreakerWrappers, Sib8) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;

	int var = 0;
	lte_sib8_type sib;
	sib.decoded_ = true;

	neighbor_cell_cdma_2000 tmp;
	tmp.band_ = bc4;
	neighbor_cells_per_band_class_cdma_2000 tmp1;
	tmp1.arfcn_value_cmda_2000_ = var++;
	tmp1.physical_cell_ids_.push_back(var++);
	tmp1.physical_cell_ids_.push_back(var++);
	tmp.neighbor_cells_per_freq_list_.push_back(tmp1);
	sib.parameters_1xrtt_.neighbor_cell_list_.push_back(tmp);
	
	tmp.neighbor_cells_per_freq_list_.clear();
	tmp1.physical_cell_ids_.clear();
	tmp.band_ = bc3;
	tmp1.arfcn_value_cmda_2000_ = var++;
	tmp1.physical_cell_ids_.push_back(var++);
	tmp1.physical_cell_ids_.push_back(var++);
	tmp.neighbor_cells_per_freq_list_.push_back(tmp1);
	sib.parameters_hrpd_.neighbor_cell_list_.push_back(tmp);

	std::vector<lte_sib8_wrapper> sib_wrappers;
	sib_wrappers.reserve(1);
	sib_wrappers.push_back(lte_sib8_wrapper(sib));
	auto test = sib_wrappers[0];

	EXPECT_EQ(sib.decoded_,
		test.s_.decoded_);

	EXPECT_EQ(sib.parameters_1xrtt_.neighbor_cell_list_[0].band_,
		test.s_.parameters_1xrtt_.elements_[0].band_);
	EXPECT_EQ(sib.parameters_1xrtt_.neighbor_cell_list_[0].neighbor_cells_per_freq_list_[0].arfcn_value_cmda_2000_,
		test.s_.parameters_1xrtt_.elements_[0].arfcn_value_cmda_2000_);
	EXPECT_EQ(sib.parameters_1xrtt_.neighbor_cell_list_[0].neighbor_cells_per_freq_list_[0].physical_cell_ids_[0],
		test.s_.parameters_1xrtt_.elements_[0].physical_cell_ids_.elements_[0]);

	EXPECT_EQ(sib.parameters_hrpd_.neighbor_cell_list_[0].band_,
		test.s_.parameters_hrpd_.elements_[0].band_);
	EXPECT_EQ(sib.parameters_hrpd_.neighbor_cell_list_[0].neighbor_cells_per_freq_list_[0].arfcn_value_cmda_2000_,
		test.s_.parameters_hrpd_.elements_[0].arfcn_value_cmda_2000_);
	EXPECT_EQ(sib.parameters_hrpd_.neighbor_cell_list_[0].neighbor_cells_per_freq_list_[0].physical_cell_ids_[0],
		test.s_.parameters_hrpd_.elements_[0].physical_cell_ids_.elements_[0]);
}

