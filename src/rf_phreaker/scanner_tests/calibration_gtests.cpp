#include "gtest/gtest.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "rf_phreaker/scanner/calibration.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/scanner_tests/cali_holder.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;


TEST(CalibrationTest, GeneralTest)
{
	cali_holder cal_holder;
	calibration &cal1 = cal_holder.cal_;

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

	EXPECT_TRUE(cal1 == cal2);

	EXPECT_EQ(cal1.nuand_serial_, cal2.nuand_serial_);
	EXPECT_EQ(cal1.nuand_calibration_date_, cal2.nuand_calibration_date_);
	EXPECT_EQ(cal1.hw_id_, cal2.hw_id_);
	EXPECT_EQ(cal1.rf_board_serial_, cal2.rf_board_serial_);
	EXPECT_EQ(cal1.rf_board_calibration_date_, cal2.rf_board_calibration_date_);
	auto n2 = cal2.nuand_adjustments_.begin();
	for(auto &n1 : cal1.nuand_adjustments_) {
		EXPECT_EQ(n1, *n2++);
	}
	auto c2 = cal2.rf_board_adjustments_.begin();
	for(auto &c1 : cal1.rf_board_adjustments_) {
		EXPECT_EQ(c1, *c2++);
	}
	auto s2 = cal2.rf_switches_.begin();
	for(auto &s1 : cal1.rf_switches_) {
		EXPECT_EQ(s1, *s2++);
	}

	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(199)), 0);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(200)), 10.1);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(204)), 10.1);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(205)), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(210)), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(211)), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(216)), 30.3);

	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(199)), 0);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(200)), 10.1 - offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(204)), 10.1 - offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(205)), 20.2 - offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(210)), 20.2 - offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(211)), 20.2 - offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(216)), 30.3 - offset_lna);

	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(199)), 0);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(200)), 10.1 - 2 * offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(204)), 10.1 - 2 * offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(205)), 20.2 - 2 * offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(210)), 20.2 - 2 * offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(211)), 20.2 - 2 * offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(216)), 30.3 - 2 * offset_lna);

	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(199), 100000), 0);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(200), 100000), 10.1);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(204), 100000), 10.1);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(205), 100000), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(210), 100000), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(211), 100000), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(216), 100000), 30.3);

	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(199), 500000), 0);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(200), 500000), 10.1);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(204), 500000), 10.1);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(205), 500000), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(210), 500000), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(211), 500000), 20.2);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(216), 500000), 30.3);
}

TEST(CalibrationTest, DISABLED_MatlabReadTest)
{
	std::string base_filename = "../../../../rf_phreaker/test_files/calibration_files/";
	std::string nuand_filename_v1 = base_filename + "nuand_format_example_v1.txt";
	std::string nuand_filename_v2 = base_filename + "nuand_format_example_v2.txt";
	std::string rf_board_filename = base_filename + "rf_board_format_example.txt";
	std::string rf_switch_filename = base_filename + "rf_switch_settings_format_example_v2.txt";

	calibration cal;

	cal.read_nuand_calibration_file(nuand_filename_v1);
	cal.read_nuand_calibration_file(nuand_filename_v2);
	cal.read_rf_board_calibration_file(rf_board_filename);
	cal.read_rf_switch_file(rf_switch_filename);

	{
		std::ofstream f("test_cali.txt");
		boost::archive::text_oarchive oa(f);
		oa & cal;
	}

	calibration cal2;
	{
		std::ifstream f("test_cali.txt");
		boost::archive::text_iarchive ia(f);
		ia & cal2;
	}

	EXPECT_TRUE(cal == cal2);
}
