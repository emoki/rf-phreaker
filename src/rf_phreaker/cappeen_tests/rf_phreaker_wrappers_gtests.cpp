#include "gtest/gtest.h"
#include "rf_phreaker/cappeen/rf_phreaker_wrappers.h"

TEST(RfPhreakerWrappers, Sib1)
{
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;
	lte_sib1_type sib1;
	sib1.is_decoded_ = true;
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

	EXPECT_EQ(sib1.is_decoded(),
		b_sib1.decoded_);

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
	sib.is_decoded_ = true;
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

	EXPECT_EQ(sib.is_decoded(),
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
	sib.is_decoded_ = true;
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

	EXPECT_EQ(sib.is_decoded(),
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
	sib.is_decoded_ = true;
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

	EXPECT_EQ(sib.is_decoded(),
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
	sib.is_decoded_ = true;
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

	EXPECT_EQ(sib.is_decoded(),
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
	sib.is_decoded_ = true;
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

	EXPECT_EQ(sib.is_decoded(),
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
	sib.is_decoded_ = true;

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

	EXPECT_EQ(sib.is_decoded(),
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

TEST(RfPhreakerWrappers, GsmSib2) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;
	layer_3_information::gsm_si_2 si;
	int32_t tmp = 0;

	si.is_decoded_ = rand() % 2 == 0;
	si.bcch_neighbors_has_extension_ = rand() % 2 == 0;
	si.gsm_ba_ind_ = tmp++;
	for(int i = 0; i < 5; ++i)
		si.bcch_neighbors_.push_back(tmp++);

	tmp = 0;
	gsm_si_2_wrapper w(si);
	ASSERT_EQ(si.is_decoded_, w.s_.decoded_);
	ASSERT_EQ(si.bcch_neighbors_has_extension_ == true ? 1 : 0, w.s_.ext_ind_);
	ASSERT_EQ(tmp++, w.s_.ba_ind_);

	ASSERT_EQ(si.bcch_neighbors_.size(), w.s_.bcch_neighbors_.num_elements_);
	for(size_t i = 0; i < si.bcch_neighbors_.size(); ++i) {
		ASSERT_EQ(tmp++, w.s_.bcch_neighbors_.elements_[i]);
	}
}

TEST(RfPhreakerWrappers, GsmSib2bis) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;
	layer_3_information::gsm_si_2bis si;
	int32_t tmp = 0;

	si.is_decoded_ = rand() % 2 == 0;
	si.bcch_neighbors_has_extension_ = rand() % 2 == 0;
	si.gsm_ba_ind_ = tmp++;
	si.rest_octet_count_ = tmp++;
	si.rest_octet_index_ = tmp++;
	for(int i = 0; i < 5; ++i)
		si.extended_bcch_neighbors_.push_back(tmp++);

	tmp = 0;
	gsm_si_2bis_wrapper w(si);
	ASSERT_EQ(si.is_decoded_, w.s_.decoded_);
	ASSERT_EQ(si.bcch_neighbors_has_extension_ == true ? 1 : 0, w.s_.ext_ind_);
	ASSERT_EQ(tmp++, w.s_.ba_ind_);
	ASSERT_EQ(tmp++, w.s_.rest_octet_count_);
	ASSERT_EQ(tmp++, w.s_.rest_octet_index_);

	ASSERT_EQ(si.extended_bcch_neighbors_.size(), w.s_.bcch_neighbors_.num_elements_);
	for(size_t i = 0; i < si.extended_bcch_neighbors_.size(); ++i) {
		ASSERT_EQ(tmp++, w.s_.bcch_neighbors_.elements_[i]);
	}
}

TEST(RfPhreakerWrappers, GsmSib2ter) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;
	layer_3_information::gsm_si_2ter si;
	int32_t tmp = 0;

	si.is_decoded_ = rand() % 2 == 0;
	si.bcch_neighbors_multiband_reporting_ = tmp++;
	si.gsm_ba_ind_ = tmp++;
	si.rest_octet_count_ = tmp++;
	si.rest_octet_index_ = tmp++;
	for(int i = 0; i < 5; ++i)
		si.extended_bcch_neighbors_.push_back(tmp++);

	for(int i = 0; i < 5; ++i) {
		layer_3_information::utran_neighbor u;
		u.arfcn_ = tmp++;
		u.duplexing_ = rand() % 2 == 0 ? fdd : tdd;
		u.bandwidth_ = (utran_bandwidth_type)(rand() % 6);
		for(int j = 0; j < 5; ++j)
			u.scrambling_codes_.push_back(tmp++);
		si.utran_neighbors_.push_back(u);
	}

	tmp = 0;
	gsm_si_2ter_wrapper w(si);
	ASSERT_EQ(si.is_decoded_, w.s_.decoded_);
	ASSERT_EQ(tmp++, w.s_.bcch_neighbor_multiband_reporting_);
	ASSERT_EQ(tmp++, w.s_.ba_ind_);
	ASSERT_EQ(tmp++, w.s_.rest_octet_count_);
	ASSERT_EQ(tmp++, w.s_.rest_octet_index_);

	ASSERT_EQ(si.extended_bcch_neighbors_.size(), w.s_.bcch_neighbors_.num_elements_);
	for(size_t i = 0; i < si.extended_bcch_neighbors_.size(); ++i) {
		ASSERT_EQ(tmp++, w.s_.bcch_neighbors_.elements_[i]);
	}

	ASSERT_EQ(si.utran_neighbors_.size(), w.s_.utran_neighbors_.num_elements_);
	for(size_t i = 0; i < si.utran_neighbors_.size(); ++i) {
		auto &e = si.utran_neighbors_[i];
		auto &t = w.s_.utran_neighbors_.elements_[i];
		ASSERT_EQ(e.arfcn_, t.uarfcn_);
		ASSERT_EQ((int)e.bandwidth_, (int)t.bandwidth_);
		ASSERT_EQ((int)e.duplexing_, (int)t.duplexing_);
		ASSERT_EQ(e.scrambling_codes_.size(), t.scrambling_codes_.num_elements_);
		for(size_t j = 0; j < e.scrambling_codes_.size(); ++j) {
			auto &ee = e.scrambling_codes_[j];
			auto &tt = t.scrambling_codes_.elements_[j];
			ASSERT_EQ(ee, tt);
		}
	}
}

TEST(RfPhreakerWrappers, GsmSib2quater) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;
	layer_3_information::gsm_si_2quater si;
	int32_t tmp = 0;

	si.is_decoded_ = rand() % 2 == 0;
	si.gsm_ba_ind_ = tmp++;
	si.p3g_ba_ind_ = tmp++;
	si.rest_octet_count_ = tmp++;
	si.rest_octet_index_ = tmp++;

	for(int i = 0; i < 5; ++i) {
		layer_3_information::utran_neighbor u;
		u.arfcn_ = tmp++;
		u.duplexing_ = rand() % 2 == 0 ? fdd : tdd;
		u.bandwidth_ = (utran_bandwidth_type)(rand() % 6);
		for(int j = 0; j < 5; ++j)
			u.scrambling_codes_.push_back(tmp++);
		si.utran_neighbors_.push_back(u);
	}

	for(int i = 0; i < 5; ++i) {
		layer_3_information::eutran_neighbor e;
		e.earfcn_ = tmp++;
		e.bandwidth_ = (eutran_bandwidth_type)(rand() % 6);
		for(int j = 0; j < 5; ++j)
			e.pcids_allowed_.push_back(tmp++);
		for(int j = 0; j < 5; ++j)
			e.pcids_not_allowed_.push_back(tmp++);
		for(int j = 0; j < 5; ++j) {
			std::vector<int32_t> pcids;
			for(int k = 0; k < 5; ++k)
				pcids.push_back(tmp++);
			e.pcids_same_tracking_area_.push_back(pcids);
		}
		for(int j = 0; j < 5; ++j) {
			std::vector<int32_t> pcids;
			for(int k = 0; k < 5; ++k)
				pcids.push_back(tmp++);
			e.pcids_different_tracking_area_.push_back(pcids);
		}

		e.priority_ = tmp++;
		e.threshold_high_db_ = tmp++;
		e.threshold_low_db_ = tmp++;
		e.qrxlevmin_db_ = tmp++;

		si.eutran_neighbors_.push_back(e);
	}

	for(int i = 0; i < 5; ++i)
		si.extended_eutran_neighbors_.push_back(tmp++);

	tmp = 0;
	gsm_si_2quater_wrapper w(si);
	ASSERT_EQ(si.is_decoded_, w.s_.decoded_);
	ASSERT_EQ(tmp++, w.s_.ba_ind_);
	ASSERT_EQ(tmp++, w.s_.ba_ind_3g_);
	ASSERT_EQ(tmp++, w.s_.rest_octet_count_);
	ASSERT_EQ(tmp++, w.s_.rest_octet_index_);

	ASSERT_EQ(si.utran_neighbors_.size(), w.s_.utran_neighbors_.num_elements_);
	for(size_t i = 0; i < si.utran_neighbors_.size(); ++i) {
		auto &e = si.utran_neighbors_[i];
		auto &t = w.s_.utran_neighbors_.elements_[i];
		ASSERT_EQ(e.arfcn_, t.uarfcn_);
		ASSERT_EQ((int)e.bandwidth_, (int)t.bandwidth_);
		ASSERT_EQ((int)e.duplexing_, (int)t.duplexing_);
		ASSERT_EQ(e.scrambling_codes_.size(), t.scrambling_codes_.num_elements_);
		for(size_t j = 0; j < e.scrambling_codes_.size(); ++j) {
			auto &ee = e.scrambling_codes_[j];
			auto &tt = t.scrambling_codes_.elements_[j];
			ASSERT_EQ(ee, tt);
		}
	}

	ASSERT_EQ(si.eutran_neighbors_.size(), w.s_.eutran_neighbors_.num_elements_);
	for(size_t i = 0; i < si.eutran_neighbors_.size(); ++i) {
		auto &e = si.eutran_neighbors_[i];
		auto &t = w.s_.eutran_neighbors_.elements_[i];
		ASSERT_EQ(e.earfcn_, t.earfcn_);
		ASSERT_EQ(convert(e.bandwidth_), (int)t.bandwidth_in_resource_blocks_);

		ASSERT_EQ(e.pcids_allowed_.size(), t.pcids_allowed_.num_elements_);
		for(size_t j = 0; j < e.pcids_allowed_.size(); ++j) {
			auto &ee = e.pcids_allowed_[j];
			auto &tt = t.pcids_allowed_.elements_[j];
			ASSERT_EQ(ee, tt);
		}

		ASSERT_EQ(e.pcids_not_allowed_.size(), t.pcids_not_allowed_.num_elements_);
		for(size_t j = 0; j < e.pcids_not_allowed_.size(); ++j) {
			auto &ee = e.pcids_not_allowed_[j];
			auto &tt = t.pcids_not_allowed_.elements_[j];
			ASSERT_EQ(ee, tt);
		}

		ASSERT_EQ(e.pcids_same_tracking_area_.size(), t.pcids_same_tracking_area_.num_elements_);
		for(size_t j = 0; j < e.pcids_same_tracking_area_.size(); ++j) {
			auto &ee = e.pcids_same_tracking_area_[j];
			auto &tt = t.pcids_same_tracking_area_.elements_[j];
			ASSERT_EQ(ee.size(), tt.num_elements_);
			for(size_t k = 0; k < ee.size(); ++k)
				ASSERT_EQ(ee[k], tt.elements_[k]);
		}

		ASSERT_EQ(e.pcids_different_tracking_area_.size(), t.pcids_different_tracking_area_.num_elements_);
		for(size_t j = 0; j < e.pcids_different_tracking_area_.size(); ++j) {
			auto &ee = e.pcids_different_tracking_area_[j];
			auto &tt = t.pcids_different_tracking_area_.elements_[j];
			ASSERT_EQ(ee.size(), tt.num_elements_);
			for(size_t k = 0; k < ee.size(); ++k)
				ASSERT_EQ(ee[k], tt.elements_[k]);
		}

		ASSERT_EQ(e.priority_, t.priority_);
		ASSERT_EQ(e.threshold_high_db_, t.threshold_high_db_);
		ASSERT_EQ(e.threshold_low_db_, t.threshold_low_db_);
		ASSERT_EQ(e.qrxlevmin_db_, t.qrxlevmin_db_);
	}

	ASSERT_EQ(si.extended_eutran_neighbors_.size(), w.s_.extended_earfcns_.num_elements_);
	for(size_t i = 0; i < si.extended_eutran_neighbors_.size(); ++i)
		ASSERT_EQ(si.extended_eutran_neighbors_[i], w.s_.extended_earfcns_.elements_[i]);
}

TEST(RfPhreakerWrappers, GsmSib3) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;
	layer_3_information::gsm_si_3 si;
	int32_t tmp = 0;

	si.is_decoded_ = rand() % 2 == 0;
	si.plmn_.mcc_ = std::string("010");
	si.plmn_.mnc_ = std::string("230");
	si.location_area_code_ = tmp++;
	si.cell_id_ = tmp++;
	si.selection_parameters_.cell_reselect_offset_db_ = tmp++;
	si.cell_reselect_hysteresis_db_ = tmp++;
	si.is_2ter_present_ = rand() % 2 == 0;
	si.is_2quater_present_ = rand() % 2 == 0;

	tmp = 0;
	gsm_si_3_wrapper w(si);
	ASSERT_EQ(si.is_decoded_, w.s_.decoded_);
	ASSERT_STREQ(si.plmn_.mcc_.to_string(), w.s_.plmn_.mcc_);
	ASSERT_STREQ(si.plmn_.mnc_.to_string(), w.s_.plmn_.mnc_);
	ASSERT_EQ(si.location_area_code_, w.s_.lac_);
	ASSERT_EQ(si.cell_id_, w.s_.cid_);
	ASSERT_EQ(si.selection_parameters_.cell_reselect_offset_db_, w.s_.cell_reselect_offset_db_);
	ASSERT_EQ(si.cell_reselect_hysteresis_db_, w.s_.cell_reselect_hysteresis_db_);
	ASSERT_EQ(si.is_2ter_present_, w.s_.is_2ter_present_);
	ASSERT_EQ(si.is_2quater_present_, w.s_.is_2quater_present_);
}

TEST(RfPhreakerWrappers, GsmSib4TestBadMnc) {
	using namespace beagle_api;
	using namespace layer_3_information;
	using namespace rf_phreaker::cappeen_api;
	layer_3_information::gsm_si_4 si;
	int32_t tmp = 0;

	si.is_decoded_ = rand() % 2 == 0;
	si.plmn_.mcc_ = std::string("0023");
	si.plmn_.mnc_ = tmp++;
	si.location_area_code_ = tmp++;
	si.cell_id_ = tmp++;
	si.selection_parameters_.cell_reselect_offset_db_ = tmp++;
	si.cell_reselect_hysteresis_db_ = tmp++;
	si.is_cbch_present_ = rand() % 2 == 0;

	tmp = 0;
	gsm_si_4_wrapper w(si);
	ASSERT_EQ(si.is_decoded_, w.s_.decoded_);
	ASSERT_STREQ("002", w.s_.plmn_.mcc_);
	ASSERT_STREQ(si.plmn_.mnc_.to_string(), w.s_.plmn_.mnc_);
	ASSERT_EQ(si.location_area_code_, w.s_.lac_);
	ASSERT_EQ(si.cell_id_, w.s_.cid_);
	ASSERT_EQ(si.selection_parameters_.cell_reselect_offset_db_, w.s_.cell_reselect_offset_db_);
	ASSERT_EQ(si.cell_reselect_hysteresis_db_, w.s_.cell_reselect_hysteresis_db_);
	ASSERT_EQ(si.is_cbch_present_, w.s_.is_cbch_present_);
}