#include "gtest\gtest.h"

#include "rf_phreaker/scanner/packet.h"
#include "rf_phreaker/scanner/packet_typedefs.h"
#include "rf_phreaker/scanner/packet_helper.h"
#include "rf_phreaker/scanner/scanner_initialization.h"
#include "rf_phreaker/scanner_tests/mock_scanner_comm.h"

TEST(PacketTest, TestScannerInitializationLimeRecommendations)
{
	mock_scanner_comm comm;

	rf_phreaker::scanner::scanner_initialization init;

	init.send_lime_recommendations(comm);
}
