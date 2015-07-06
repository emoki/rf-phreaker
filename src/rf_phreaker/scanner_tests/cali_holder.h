#pragma once

#include "rf_phreaker/scanner/calibration.h"

double offset_lna = 3.5;

class cali_holder
{
public:
	cali_holder() {
		using namespace rf_phreaker;
		using namespace rf_phreaker::scanner;
		cal_.nuand_serial_ = "123";
		cal_.nuand_calibration_date_ = 123;
		cal_.hw_id_ = 9999;
		cal_.rf_board_serial_ = "456";
		cal_.rf_board_calibration_date_ = 0123;
		rf_adjustment rf_adj;
		rf_adj.path_.low_freq_ = mhz(200);
		rf_adj.path_.high_freq_ = mhz(300);
		rf_adj.spacing_ = mhz(50);
		rf_adj.rf_adjustments_.push_back(10);
		rf_adj.rf_adjustments_.push_back(20);
		rf_adj.rf_adjustments_.push_back(30);
		lna_adjustment lna_adj;
		lna_adj.lna_gain_ = lms::LNA_MAX;
		lna_adj.adj_ = rf_adj;
		cal_.nuand_adjustments_.insert(std::make_pair(lna_adj.lna_gain_, lna_adj));
		lna_adj.lna_gain_ = lms::LNA_MID;
		for(auto &i : lna_adj.adj_.rf_adjustments_) { i -= offset_lna; }
		cal_.nuand_adjustments_.insert(std::make_pair(lna_adj.lna_gain_, lna_adj));
		lna_adj.lna_gain_ = lms::LNA_BYPASS;
		for(auto &i : lna_adj.adj_.rf_adjustments_) { i -= offset_lna; }
		cal_.nuand_adjustments_.insert(std::make_pair(lna_adj.lna_gain_, lna_adj));
		rf_path_adjustment path_adj;
		path_adj.identifier_ = 1;
		path_adj.adj_ = rf_adj;
		cal_.rf_board_adjustments_.insert(std::make_pair(path_adj.identifier_, path_adj));
		path_adj.identifier_ = 2;
		path_adj.adj_.path_.low_freq_ = mhz(400);
		path_adj.adj_.path_.high_freq_ = mhz(500);
		cal_.rf_board_adjustments_.insert(std::make_pair(path_adj.identifier_, path_adj));
		
		std::map<frequency_type, rf_switch_setting> tmp1;
		tmp1.insert(std::make_pair(mhz(230), rf_switch_setting(1, 100000, mhz(200), mhz(230), 0x12345, 0x000FF)));
		tmp1.insert(std::make_pair(mhz(330), rf_switch_setting(1, 100000, mhz(300), mhz(330), 0x67890, 0xF00FF)));
		cal_.rf_switches_.insert(std::make_pair(100000, tmp1));

		std::map<frequency_type, rf_switch_setting> tmp2;
		tmp2.insert(std::make_pair(mhz(230), rf_switch_setting(1, 500000, mhz(200), mhz(230), 0x12345, 0x000FF)));
		tmp2.insert(std::make_pair(mhz(330), rf_switch_setting(1, 500000, mhz(300), mhz(330), 0x67890, 0xF00FF)));
		cal_.rf_switches_.insert(std::make_pair(500000, tmp2));
	}
	rf_phreaker::scanner::calibration cal_;
};
