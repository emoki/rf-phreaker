#include "gtest/gtest.h"
#include "rf_phreaker/protobuf_specific/rf_phreaker_serialization.h"
#include "rf_phreaker/protobuf_specific_tests/meas_manager.h"

using namespace rf_phreaker;
using namespace layer_3_information;
using namespace rf_phreaker::protobuf;

TEST_F(MeasManager, HardwareTranslationTest) {
	{
		std::ofstream fs("test.bin", std::ios::binary);
		update_pb p;
		p.populate_device_info(h_);
		EXPECT_TRUE(p.protobuf().SerializeToOstream(&fs));
	}
	{
		std::ifstream fs("test.bin", std::ios::binary);
		update_pb p;
		EXPECT_TRUE(p.protobuf().ParseFromIstream(&fs));
		EXPECT_TRUE(p.protobuf().has_device());
		auto t = p.get_hardware();
	}
}

TEST_F(MeasManager, GpsTranslationTest) {
	{
		std::ofstream fs("test.bin", std::ios::binary);
		update_pb p;
		p.populate_gps(gps_);
		EXPECT_TRUE(p.protobuf().SerializeToOstream(&fs));
	}
	{
		std::ifstream fs("test.bin", std::ios::binary);
		update_pb p;
		EXPECT_TRUE(p.protobuf().ParseFromIstream(&fs));
		EXPECT_TRUE(p.protobuf().has_gps());
		auto t = p.get_gps();
	}
}

TEST_F(MeasManager, GsmTranslationTest) {
	{
		std::ofstream fs("test.bin", std::ios::binary);
		update_pb p;
		p.populate_gsm_full_scan(gsm_, gsm_[0]);
		EXPECT_TRUE(p.protobuf().SerializeToOstream(&fs));
	}
	{
		std::ifstream fs("test.bin", std::ios::binary);
		update_pb p;
		EXPECT_TRUE(p.protobuf().ParseFromIstream(&fs));
		EXPECT_TRUE(p.protobuf().has_gsm_full_scan());
		auto t = p.get_gsm_full_scan();
	}
}

TEST_F(MeasManager, UmtsTranslationTest) {
	{
		std::ofstream fs("test.bin", std::ios::binary);
		update_pb p;
		p.populate_wcdma_full_scan(umts_, umts_[0]);
		EXPECT_TRUE(p.protobuf().SerializeToOstream(&fs));
	}
	{
		std::ifstream fs("test.bin", std::ios::binary);
		update_pb p;
		EXPECT_TRUE(p.protobuf().ParseFromIstream(&fs));
		EXPECT_TRUE(p.protobuf().has_wcdma_full_scan());
		auto t = p.get_wcdma_full_scan();
	}
}

TEST_F(MeasManager, LteTranslationTest) {
	{
		std::ofstream fs("test.bin", std::ios::binary);
		update_pb p;
		p.populate_lte_full_scan(lte_, lte_[0]);
		EXPECT_TRUE(p.protobuf().SerializeToOstream(&fs));
	}
	{
		std::ifstream fs("test.bin", std::ios::binary);
		update_pb p;
		EXPECT_TRUE(p.protobuf().ParseFromIstream(&fs));
		EXPECT_TRUE(p.protobuf().has_lte_full_scan());
		auto t = p.get_lte_full_scan();
	}
}