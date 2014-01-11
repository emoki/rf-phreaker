#include "rf_phreaker/scanner/vtune.h"
#include "rf_phreaker/common/exception_types.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;
using namespace rf_phreaker::scanner::lms;

vtune::vtune(void)
{
}

vtune::~vtune(void)
{
}

packet_container vtune::determine_vtune(scanner_comm &comm, packet_container &freq_container)
{
	comm.transfer_packet_container(freq_container);

	return determine_vtune(comm);
}

packet_container vtune::determine_vtune(scanner_comm &comm)
{
	lms_value_type vtune_value = find_optimum_vtune(comm);

	auto packet = packet_ptr(new lime_write_packet(vcocap_program_register, vtune_value));
	
	packet_container container;

	container.add_packet(packet);

	return container;
}

lms_value_type vtune::find_optimum_vtune(scanner_comm &comm)
{
	comm_ = &comm;
	// TODO - Assumes the given loop filter value with a loop BW of 50kHz is used.
	// TODO - Should we make sure Rx DSM SPI clock is enabled, reg: 0x09.
	// TODO - Should we set the PLL Ichp, Iup and Idn currents, regs: 0x26 - 0x28.  Currently done with lime recomendations.

	lime_write_packet write_packet(vtune_comparator_power_up_register, enable_vco_comparator_power());

	comm.transfer_packet(write_packet);
	
	 write_packet.set_register_address_and_value(vcocap_program_register, set_vco_cap(vcocap_median_cap));

	lime_read_packet read_packet(vtune_comparator_register);

	comm_->transfer_packet(write_packet);
	comm_->transfer_packet(read_packet);

	int vco_low = vcocap_value_invalid, vco_high = vcocap_value_invalid;

	switch(get_vtune(read_packet.get_register_value()))
	{
	case VTUNE_IN_RANGE:
		sweep_vco_down_up(vco_low, vco_high);
		break;
	case VTUNE_LOW:
		sweep_vco_down(vco_low, vco_high);
		break;
	case VTUNE_HIGH:
		sweep_vco_up(vco_low, vco_high);
		break;
	case VTUNE_INVALID:
		throw hardware_error("VTUNE was invalid.");
		break;
	default:
		throw misc_error("Unknown value in switch case.");
	};

	check_vco_values(vco_low, vco_high);

	write_packet.set_register_address_and_value(vtune_comparator_power_up_register, disable_vco_comparator_power());

	comm.transfer_packet(write_packet);

	return (lms_value_type)(vco_low + vco_high) / 2;
}

void vtune::sweep_vco_up(int &vco_low, int &vco_high)
{
	lime_write_packet vcocap_program_packet(vcocap_program_register, set_vco_cap(vcocap_median_cap));
	lime_read_packet comparator_packet(vtune_comparator_register);

	int i = vcocap_median_cap + 1;
	for(; i <= vcocap_max_cap; ++i)
	{
		write_vcocap_and_check_vtune(vcocap_program_packet, i, comparator_packet);

		if(get_vtune(comparator_packet.get_register_value()) == VTUNE_IN_RANGE)
		{
			vco_low = i;
			break;
		}
	}
	for(; i <= vcocap_max_cap; ++i)
	{
		write_vcocap_and_check_vtune(vcocap_program_packet, i, comparator_packet);

		if(get_vtune(comparator_packet.get_register_value()) == VTUNE_LOW)
		{
			vco_high = --i;
			break;
		}
	}
	
	// Assumes vco_high is highest possible value.
	if(vco_low != vcocap_value_invalid && vco_high == vcocap_value_invalid)
		vco_high = vcocap_max_cap;
}

void vtune::sweep_vco_down(int &vco_low, int &vco_high)
{
	lime_write_packet vcocap_program_packet(vcocap_program_register, set_vco_cap(vcocap_median_cap));
	lime_read_packet comparator_packet(vtune_comparator_register);

	int i = vcocap_median_cap - 1;
	for(; i >= vcocap_min_cap; --i)
	{
		write_vcocap_and_check_vtune(vcocap_program_packet, i, comparator_packet);

		if(get_vtune(comparator_packet.get_register_value()) == VTUNE_IN_RANGE)
		{
			vco_high = i;
			break;
		}
	}
	for(; i >= vcocap_min_cap; --i)
	{
		write_vcocap_and_check_vtune(vcocap_program_packet, i, comparator_packet);

		if(get_vtune(comparator_packet.get_register_value()) == VTUNE_HIGH)
		{
			vco_low = ++i;
			break;
		}
	}

	// Assumes vco_low is lowest possible value.
	if(vco_high != vcocap_value_invalid && vco_low == vcocap_value_invalid)
		vco_low = vcocap_min_cap;
}

void vtune::sweep_vco_down_up(int &vco_low, int &vco_high)
{
	lime_write_packet vcocap_program_packet(vcocap_program_register, set_vco_cap(vcocap_median_cap));
	lime_read_packet comparator_packet(vtune_comparator_register);

	
	for(int i = vcocap_median_cap - 1; i >= vcocap_min_cap; --i)
	{
		write_vcocap_and_check_vtune(vcocap_program_packet, i, comparator_packet);

		if(get_vtune(comparator_packet.get_register_value()) == VTUNE_HIGH)
		{
			vco_low = i + 1;
			break;
		}
	}

	for(int i = vcocap_median_cap + 1; i <= vcocap_max_cap; ++i)
	{
		write_vcocap_and_check_vtune(vcocap_program_packet, i, comparator_packet);

		if(get_vtune(comparator_packet.get_register_value()) == VTUNE_LOW)
		{
			vco_high = i - 1;
			break;
		}
	}

	if(vco_low == vcocap_value_invalid)
		vco_low = vcocap_min_cap;

	if(vco_high == vcocap_value_invalid)
		vco_high = vcocap_max_cap;
}

void vtune::write_vcocap_and_check_vtune(lime_write_packet& vcocap_program_packet, int vcocap_value, lime_read_packet &comparator_packet)
{
	vcocap_program_packet.set_register_value(set_vco_cap((lms_value_type)vcocap_value));
	comm_->transfer_packet(vcocap_program_packet);
	comm_->transfer_packet(comparator_packet);

	if(get_vtune(comparator_packet.get_register_value()) == VTUNE_INVALID)
		throw hardware_error("VTUNE was invalid.");
}

void vtune::check_vco_values(int vco_low, int vco_high)
{
	if(vco_low == vcocap_value_invalid )
		throw hardware_error("Invalid vtune value for vco_low.");

	else if(vco_high == vcocap_value_invalid)
		throw hardware_error("Invalid vtune value for vco_high.");
}
