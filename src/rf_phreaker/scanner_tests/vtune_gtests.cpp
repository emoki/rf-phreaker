#include "gtest/gtest.h"

#include "rf_phreaker/scanner/vtune.h"
#include "rf_phreaker/scanner/scanner_comm_usb.h"
#include "rf_phreaker/scanner/fake_usb_ftdi.h"
#include "rf_phreaker/scanner/packet_container.h"

using namespace rf_phreaker::scanner::lms;
using namespace rf_phreaker::scanner;

class vtune_scanner_comm : public scanner_comm_usb
{
public:
	vtune_scanner_comm() : scanner_comm_usb(FAKE_USB_FTDI_DEVICE) {}

	const fake_usb_ftdi& usb_interface() { return *reinterpret_cast<fake_usb_ftdi*>(usb_interface_.get()); }
};

TEST(VtuneTest, TestVtuneValue)
{
	vtune_scanner_comm comm; 

	comm.open_scanner(comm.list_scanners().begin()->get()->id());

	vtune vtune_test;

	for(int i = 0; i < 128; ++i)
	{
		int value = vtune_test.find_optimum_vtune(comm);
		
		ASSERT_EQ((comm.usb_interface().vtune_lower_ + comm.usb_interface().vtune_higher_) / 2, value) 
			<< "i == " << i;
	}
}

TEST(VtuneTest, TestVtunePacketContainer)
{
	vtune_scanner_comm comm;

	comm.open_scanner(comm.list_scanners().begin()->get()->id());

	vtune vtune_test;

	for(int i = 0; i < 128; ++i)
	{		
		auto container = vtune_test.determine_vtune(comm);
		auto packet_it = container.begin();
		auto packet = packet_it->get();
		lime_write_packet *p = dynamic_cast<lime_write_packet*>(packet);

		int value = ((p->get_register_value() & 0xFF) & ~vcocap_program_default);

		ASSERT_EQ(((comm.usb_interface().vtune_lower_ + comm.usb_interface().vtune_higher_) / 2), value)
			<< "i == " << i;

		ASSERT_EQ(vcocap_program_register, p->get_register_address())
			<< "i == " << i;
	}
}
