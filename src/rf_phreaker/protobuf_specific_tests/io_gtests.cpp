#include "gtest/gtest.h"
#include "rf_phreaker/protobuf_specific/rf_phreaker_serialization.h"
#include "rf_phreaker/protobuf_specific_tests/meas_manager.h"
#include "rf_phreaker/protobuf_specific/io.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/io/coded_stream.h"

using namespace rf_phreaker;
using namespace layer_3_information;
using namespace rf_phreaker::protobuf;

TEST_F(MeasManager, DelimitedTest) {
	{
		std::ofstream fs("io.bin", std::ios::binary);
		google::protobuf::io::OstreamOutputStream gos(&fs);
		for(int i = 0; i < 500; i++) {
			update_pb pb;
			gps_.coordinated_universal_time_ = i;
			pb.populate_gps(gps_);
			EXPECT_TRUE(rf_phreaker::protobuf::write_delimited_to(pb.protobuf(), &gos));
		}
	}
	{
		std::ifstream fs("io.bin", std::ios::binary);
		google::protobuf::io::IstreamInputStream gis(&fs);
		for(int i = 0; i < 500; i++) {
			update_pb p;
			EXPECT_TRUE(rf_phreaker::protobuf::read_delimited_from(&gis, &p.protobuf()));
			EXPECT_TRUE(p.protobuf().has_gps());
			EXPECT_EQ(i, p.get_gps().coordinated_universal_time_);
		}
	}
}
