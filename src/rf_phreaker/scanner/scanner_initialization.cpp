#include "rf_phreaker/scanner/scanner_initialization.h"
#include "rf_phreaker/scanner/packet_container.h"
#include "rf_phreaker/scanner/packet_typedefs.h"
#include "rf_phreaker/scanner/scanner_utility.h"
#include "rf_phreaker/common/exception_types.h"

using namespace rf_phreaker::scanner;

const uint8_t lime_recommendations_register_values[] = 
{
	0x1F,
	0x08,
	0x36,
	0x0D,
	0x00,
	0x00,
	0x84,
	0x00,
	0x08,
	0x73,
	0x1A,
	0xAA,
	0xAA,
	0x88,
	0xFB,
	0x8C,
	0xE3,
	0x40,
	//0xA7,
	//0x03,
	//0x76,
	0x38,
	0x1F,
	0x08,
	0x0A,
	0x0C,
	0x30,
	0x94,
	0x00,
	0x29,
	0x20,
	0x00,
	0x00,
	0x00,
	0x00,
	0x9F,
	0x1F,
	0x08,
	0x36,
	0x01,
	0x00,
	0x00,
	0x13,
	0xC0,
	0x01,
	0x80,
	0x80,
	0x00,
	0x00,
	0xF0,
	0x78,
	0x00,
	0x1C,
	0x36,
	0x77,
	0x77,
	0x18,
	0x00
};

scanner_initialization::scanner_initialization(void)
{
}

scanner_initialization::~scanner_initialization(void)
{
}

void scanner_initialization::initialize_scanner(scanner_comm &comm)
{
	// If reseting we must reopen comm.
	//comm.transfer_packet(reset_all_packet());

	//buf_type buf(1000000);
	//comm.read(&buf[0], 100000);

	send_lime_recommendations_default(comm);
}

void scanner_initialization::send_lime_recommendations_default(scanner_comm &comm)
{
	packet_container send_container;
	send_container.add_packet(std::make_shared<lime_write_packet>(0x02, 0x1F));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x03, 0x08));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x05, 0x36));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x06, 0x0D));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x07, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x08, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x09, 0x84));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x0A, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x0B, 0x08));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x20, 0x73));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x21, 0x1A));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x22, 0xAA));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x23, 0xAA));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x24, 0x88));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x25, 0xFB));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x26, 0x8C));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x27, 0xE3));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x28, 0x40));
	//send_container.add_packet(std::make_shared<lime_write_packet>(0x29, 0xA7));
	//send_container.add_packet(std::make_shared<lime_write_packet>(0x2A, 0x03));
	//send_container.add_packet(std::make_shared<lime_write_packet>(0x2B, 0x76));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x2C, 0x38));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x52, 0x1F));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x53, 0x08));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x54, 0x0A));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x55, 0x0C));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x56, 0x30));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x57, 0x94));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x58, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x59, 0x29));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x5A, 0x20));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x5B, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x5C, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x5D, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x5E, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x5F, 0x9F));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x62, 0x1F));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x63, 0x08));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x64, 0x36));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x65, 0x01));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x66, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x67, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x68, 0x13));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x6E, 0xC0));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x70, 0x01));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x71, 0x80));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x72, 0x80));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x73, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x74, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x75, 0xF0));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x76, 0x78));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x77, 0x00));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x78, 0x1C));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x79, 0x36));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x7A, 0x77));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x7B, 0x77));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x7C, 0x18));
	send_container.add_packet(std::make_shared<lime_write_packet>(0x7D, 0x00));

	send_container.add_packet(std::make_shared<lime_read_packet>(0x02));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x03));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x05));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x06));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x07));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x08));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x09));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x0A));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x0B));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x20));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x21));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x22));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x23));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x24));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x25));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x26));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x27));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x28));
	//send_container.add_packet(std::make_shared<lime_read_packet>(0x29));
	//send_container.add_packet(std::make_shared<lime_read_packet>(0x2A));
	//send_container.add_packet(std::make_shared<lime_read_packet>(0x2B));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x2C));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x52));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x53));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x54));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x55));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x56));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x57));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x58));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x59));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x5A));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x5B));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x5C));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x5D));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x5E));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x5F));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x62));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x63));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x64));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x65));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x66));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x67));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x68));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x6E));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x70));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x71));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x72));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x73));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x74));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x75));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x76));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x77));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x78));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x79));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x7A));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x7B));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x7C));
	send_container.add_packet(std::make_shared<lime_read_packet>(0x7D));

	buf_type read_buffer(send_container.return_bytes_expected());

	comm.transfer_packet_container(send_container, &read_buffer[0]);


	// Assumes data 
	auto it = read_buffer.begin();
	for(size_t pos = 0; pos <= sizeof(lime_recommendations_register_values); ++pos)
	{
		if(lime_recommendations_register_values[pos] != hex_conversion::convert_hex<2>(it))
			throw scanner_init_error("Register was not set correctly during initialization.");

		if(++it == read_buffer.end() || ++it == read_buffer.end())
			break;
	}
}

void scanner_initialization::send_lime_recommendations(scanner_comm &comm, const std::string &filename)
{
	comm; filename;
}
