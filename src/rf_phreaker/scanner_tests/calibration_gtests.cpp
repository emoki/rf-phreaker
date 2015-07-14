#include "gtest/gtest.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "rf_phreaker/scanner/calibration.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/scanner_tests/cali_holder.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;


TEST(CalibrationTest, GeneralTest) {
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
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(200)), 10);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(225)), 15);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(250)), 20);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(275)), 25);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(300)), 30);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MAX, mhz(301)), 0);

	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(199)), 0);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(200)), 10 - offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(225)), 15 - offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(250)), 20 - offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(275)), 25 - offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(300)), 30 - offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_MID, mhz(301)), 0);

	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(199)), 0);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(200)), 10 - 2 * offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(225)), 15 - 2 * offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(250)), 20 - 2 * offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(275)), 25 - 2 * offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(300)), 30 - 2 * offset_lna);
	EXPECT_DOUBLE_EQ(cal1.get_nuand_adjustment(lms::LNA_BYPASS, mhz(301)), 0);


	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(199), 10000), 0);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(200), 10000), 10);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(225), 10000), 15);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(250), 10000), 20);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(275), 10000), 25);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(300), 10000), 30);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(301), 10000), 0);

	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(199), 5000), 0);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(200), 5000), 10);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(225), 5000), 15);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(250), 5000), 20);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(275), 5000), 25);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(300), 5000), 30);
	EXPECT_DOUBLE_EQ(cal1.get_rf_board_adjustment(mhz(301), 5000), 0);
}

TEST(CalibrationTest, AdjustmentTest) {
	cali_holder cal_holder;
	calibration &cal1 = cal_holder.cal_;

	auto bypass_nuand = cal1.get_nuand_adjustments(lms::LNA_MAX, mhz(250), mhz(100));
	EXPECT_DOUBLE_EQ(bypass_nuand.find_adjustment(mhz(199)), 0);
	EXPECT_DOUBLE_EQ(bypass_nuand.find_adjustment(mhz(200)), 10);
	EXPECT_DOUBLE_EQ(bypass_nuand.find_adjustment(mhz(225)), 15);
	EXPECT_DOUBLE_EQ(bypass_nuand.find_adjustment(mhz(250)), 20);
	EXPECT_DOUBLE_EQ(bypass_nuand.find_adjustment(mhz(275)), 25);
	EXPECT_DOUBLE_EQ(bypass_nuand.find_adjustment(mhz(300)), 30);
	EXPECT_DOUBLE_EQ(bypass_nuand.find_adjustment(mhz(301)), 0);

	auto tmp_rf = cal1.get_rf_board_adjustments(mhz(250), 10000, mhz(100));
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(199)), 0);
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(200)), 10);
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(225)), 15);
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(250)), 20);
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(275)), 25);
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(300)), 30);
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(301)), 0);

	tmp_rf = cal1.get_rf_board_adjustments(mhz(250), 10000, mhz(50));
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(225)), 15);
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(250)), 20);
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(275)), 25);

	tmp_rf = cal1.get_rf_board_adjustments(mhz(225), 10000, mhz(25));
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(200)), 10);
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(225)), 15);
	EXPECT_DOUBLE_EQ(tmp_rf.find_adjustment(mhz(250)), 20);
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

TEST(CalibrationTest, MatlabReadTest) {
	std::string base_filename = "../../../../rf_phreaker/test_files/calibration_files/two_old_nst+/";
	std::string nuand_filename = base_filename + "Nuand_Board_77ecda454d25738ee419f6fd676170d5_141021.txt";
	std::string rf_board_filename = base_filename + "RF_Board_77ecda454d25738ee419f6fd676170d5_141021.txt";
	std::string rf_switch_filename = base_filename + "RF_Switch_77ecda454d25738ee419f6fd676170d5_141021.txt";
//	std::string tmp_cali_filename = base_filename + "tmp_77ecda454d25738ee419f6fd676170d5_141021_cali.bin";

	std::string tmp_cali_filename = base_filename + "fad9939798da46e9f4271a9451f8b647_cali.bin";
	calibration cal;
	{
		std::ifstream f(tmp_cali_filename, std::ios::binary);
		boost::archive::binary_iarchive a(f);
		a & cal;
	}
	//{
	//	std::ofstream f(tmp_cali_filename, std::ios::binary);
	//	boost::archive::binary_oarchive a(f);
	//	cal.hw_id_ = 39999;
	//	a & cal;
	//}

}