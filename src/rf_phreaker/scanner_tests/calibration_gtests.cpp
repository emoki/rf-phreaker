#include "gtest/gtest.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "rf_phreaker/scanner/calibration.h"
#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;

TEST(CalibrationTest, GeneralTest)
{
	calibration cal1;
	cal1.nuand_serial_ = "123";
	cal1.nuand_calibration_date_ = 123;
	cal1.nuand_freq_correction_value_ = 456;
	cal1.nuand_freq_correction_date_ = 789;
	cal1.rf_board_serial_ = "456";
	cal1.rf_board_calibration_date_ = 0123;
	cal1.nuand_adjustment_.path_.low_freq_ = mhz(200);
	cal1.nuand_adjustment_.path_.high_freq_ = mhz(230);
	cal1.nuand_adjustment_.spacing_ = mhz(10);
	cal1.nuand_adjustment_.rf_adjustments_.push_back(10.1);
	cal1.nuand_adjustment_.rf_adjustments_.push_back(20.2);
	cal1.nuand_adjustment_.rf_adjustments_.push_back(30.3);
	rf_path_adjustment adj;
	adj.identifier_ = 1;
	adj.adj_ = cal1.nuand_adjustment_;
	cal1.rf_board_adjustments_.insert(std::make_pair(adj.identifier_, adj));
	adj.identifier_ = 2;
	adj.adj_.path_.low_freq_ = mhz(300);
	adj.adj_.path_.high_freq_ = mhz(330);
	cal1.rf_board_adjustments_.insert(std::make_pair(adj.identifier_, adj));
	cal1.rf_switches_.insert(std::make_pair(mhz(230), rf_switch_setting(1, mhz(200), mhz(230), 0x12345, 0x000FF)));
	cal1.rf_switches_.insert(std::make_pair(mhz(330), rf_switch_setting(2, mhz(300), mhz(330), 0x67890, 0x000FF)));

	{
		std::ofstream f("test_cali.txt");
		boost::archive::text_oarchive oa(f);
		oa & cal1;
	}
	calibration cal2;
	{
		std::ifstream f("test_cali.txt");
		boost::archive::text_iarchive ia(f);
		ia & cal2;
	}

	EXPECT_EQ(cal1.nuand_serial_, cal2.nuand_serial_);
	EXPECT_EQ(cal1.nuand_calibration_date_, cal2.nuand_calibration_date_);
	EXPECT_EQ(cal1.nuand_freq_correction_value_, cal2.nuand_freq_correction_value_);
	EXPECT_EQ(cal1.nuand_freq_correction_date_, cal2.nuand_freq_correction_date_);
	EXPECT_EQ(cal1.rf_board_serial_, cal2.rf_board_serial_);
	EXPECT_EQ(cal1.rf_board_calibration_date_, cal2.rf_board_calibration_date_);
	EXPECT_EQ(cal1.nuand_adjustment_, cal2.nuand_adjustment_);
	auto c2 = cal2.rf_board_adjustments_.begin();
	for(auto &c1 : cal1.rf_board_adjustments_) {
		EXPECT_EQ(c1, *c2++);
	}
	auto s2 = cal2.rf_switches_.begin();
	for(auto &s1 : cal1.rf_switches_) {
		EXPECT_EQ(s1, *s2++);
	}

	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(mhz(199)), 0);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(mhz(200)), 10.1);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(mhz(204)), 10.1);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(mhz(205)), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(mhz(210)), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(mhz(211)), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(mhz(216)), 30.3);

	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(199)), 0);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(200)), 10.1);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(204)), 10.1);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(205)), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(210)), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(211)), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(216)), 30.3);
}

TEST(CalibrationTest, DISABLED_MatlabReadTest)
{
	std::string base_filename = "../../../../rf_phreaker/test_files/calibration_files/";
	std::string nuand_filename = base_filename + "nuand_format_example.txt";
	std::string rf_board_filename = base_filename + "rf_board_format_example.txt";
	std::string rf_switch_filename = base_filename + "rf_switch_settings_format_example.txt";

	calibration cal;

	cal.read_nuand_calibration_file(nuand_filename);
	cal.read_rf_board_calibration_file(rf_board_filename);
	cal.read_rf_switch_file(rf_switch_filename);

	{
		std::ofstream f("test_cali.txt");
		boost::archive::text_oarchive oa(f);
		oa & cal;
	}

}