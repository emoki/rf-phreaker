#pragma once

#include "rf_phreaker/scanner/packet_container.h"
#include "rf_phreaker/scanner/scanner_types.h"
#include "rf_phreaker/scanner/scanner_comm.h"
#include "rf_phreaker/scanner/packet_typedefs.h"
#include "rf_phreaker/scanner/lms_defines.h"

namespace rf_phreaker { namespace scanner {

class vtune
{
public:
	vtune(void);
	~vtune(void);

	packet_container determine_vtune(scanner_comm &comm, packet_container &freq_container);

	packet_container determine_vtune(scanner_comm &comm);

	lms_value_type find_optimum_vtune(scanner_comm &comm);

private:
	void sweep_vco_down(int &vco_low, int &vco_high);
	void sweep_vco_up(int &vco_low, int &vco_high);
	void sweep_vco_down_up(int &vco_low, int &vco_high);
	
	inline void write_vcocap_and_check_vtune(lime_write_packet& vcocap_program_packet, int vcocap_value, lime_read_packet &comparator_packet);

	void check_vco_values(int vco_low, int vco_high);

	static const int vcocap_value_invalid = -1;

	scanner_comm *comm_;
};

}}