#include "rf_phreaker/scanner/gain.h"
#include "rf_phreaker/scanner/packet_typedefs.h"
#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;
using namespace rf_phreaker::scanner::lms;


int vga1_gain = 120;
int vga2_gain = 30;

packet_container gain::get_default_gain(rf_phreaker::frequency_type freq)
{
	packet_container container;
	
	lms_value_type v = 0;

	// set lna 
	v = set_lna_gain(v, LNA_MAX);
	
	if(freq < mhz(1500))
		v = set_lna_select(v, LNA_1);
	else
		v = set_lna_select(v, LNA_2);

	container.add_packet(std::make_shared<lime_write_packet>(lna_gain_and_select_register, v));


	// Enable vga1 -- parameters taken from lms.c
	v = 0;
	v = lms::set_ict_tia_rxfe_custom_current(v, 0x3);
	v = lms::set_ict_mxlob_rxfe_custom_current(v, 0x3);
	container.add_packet(std::make_shared<lime_write_packet>(bias_current_tia_and_mixer_lo_register, v));


	// Set vga1 gain control.
	v = 60;//--vga1_gain < 1 ? 90 : vga1_gain;
	v = mask_rfb_tia_rxfe(v);

	container.add_packet(std::make_shared<lime_write_packet>(rfb_tia_rxfe_mixer_gain_control_register, v));


	// Enable vga2 and output common mode voltage control
	v = 0;
	v = get_default_rx_vga2_voltage_control(v);
	v = enable_rx_vga2(v);
	v = decode_control_signals(v);

	container.add_packet(std::make_shared<lime_write_packet>(rx_vga2_voltage_control_register, v));


	// Set vga2 gain control  
	v = 30;
	v = convert_and_mask_rx_vga2_gain_control(v);

	container.add_packet(std::make_shared<lime_write_packet>(rx_vga2_gain_control_register, v));





	return container;
}
