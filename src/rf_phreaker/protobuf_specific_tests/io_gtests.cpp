#include "gtest/gtest.h"
#include <QFile>
#include <QtCore/QCoreApplication>
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

TEST_F(MeasManager, QFileTest) {
	{
		QFile f("test.rpf");
		auto success = f.open(QIODevice::WriteOnly | QIODevice::Unbuffered);
		EXPECT_TRUE(success);
		if(success) {
			auto p = std::make_unique<google::protobuf::io::FileOutputStream>(f.handle());
//			p->SetCloseOnDelete(true);
			for(int i = 0; i < 500; i++) {
				update_pb pb;
				auto &t = umts_[0];
				t.carrier_bandwidth_ = i;
				t.carrier_frequency_ = i + 1;
				t.cpich_ = i + 2;
				pb.populate_wcdma_full_scan(umts_, umts_[0]);
				EXPECT_TRUE(rf_phreaker::protobuf::write_delimited_to(pb.protobuf(), p.get()));
			}
		}

	}
	{
		QFile f("test.rpf");
		auto success = f.open(QIODevice::ReadOnly | QIODevice::Unbuffered);
		EXPECT_TRUE(success);
		if(success) {
			auto p = std::make_unique<google::protobuf::io::FileInputStream>(f.handle()); 
//			p->SetCloseOnDelete(true);
			for(int i = 0; i < 500; i++) {
				update_pb pb;
				EXPECT_TRUE(rf_phreaker::protobuf::read_delimited_from(p.get(), &pb.protobuf()));
				EXPECT_TRUE(pb.protobuf().has_wcdma_full_scan());
				EXPECT_EQ(i, pb.get_wcdma_full_scan()[0].carrier_bandwidth_);
				EXPECT_EQ(i + 1, pb.get_wcdma_full_scan()[0].carrier_frequency_);
				EXPECT_EQ(i + 2, pb.get_wcdma_full_scan()[0].cpich_);
				EXPECT_EQ(i, pb.get_wcdma_full_scan_basic().carrier_bandwidth_);
				EXPECT_EQ(i + 1, pb.get_wcdma_full_scan_basic().carrier_frequency_);
			}
		}
	}
}