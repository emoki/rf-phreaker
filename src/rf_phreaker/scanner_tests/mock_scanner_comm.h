#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rf_phreaker/scanner/scanner_comm.h"
#include <fstream>

class mock_scanner_comm : public rf_phreaker::scanner::scanner_comm
{
public:
	MOCK_METHOD0(list_scanners, std::vector<rf_phreaker::scanner::comm_info_ptr>());

	MOCK_METHOD1(open_scanner, bool(const rf_phreaker::scanner::scanner_serial_type &id));

	MOCK_METHOD0(close_scanner, bool());

	MOCK_METHOD1(transfer_packet, void(rf_phreaker::scanner::packet &p));

	MOCK_METHOD1(transfer_packet_container, void(rf_phreaker::scanner::packet_container &p));

	MOCK_METHOD2(transfer_packet_container, void(rf_phreaker::scanner::packet_container &p, char *buf));

	MOCK_METHOD2(write, void(const char *write_buf, size_t bytes));

	MOCK_METHOD2(read, void(char *read_buf, size_t bytes));

	MOCK_METHOD0(reset, void());

	MOCK_CONST_METHOD0(is_scanner_open, bool());

	MOCK_CONST_METHOD0(connected_scanner_description, std::string());

	MOCK_CONST_METHOD0(connected_scanner_id, rf_phreaker::scanner::scanner_serial_type());

};

