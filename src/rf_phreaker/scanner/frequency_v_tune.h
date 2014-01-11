#pragma once

#include "rf_phreaker/scanner/packet_container.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/scanner/scanner_comm.h"
#include "rf_phreaker/scanner/frequency_conversion.h"
#include "rf_phreaker/scanner/vtune.h"

#include <map>

namespace rf_phreaker { namespace scanner {

//class frequency_v_tune_interface
//{
//public:
//	virtual packet_container convert_freq_and_determine_vtune(scanner_comm &comm, rf_phreaker::frequency_type freq) = 0;
//};
//

class frequency_v_tune /*: public frequency_v_tune_interface*/
{
public:
	frequency_v_tune(void);

	~frequency_v_tune(void);

	packet_container convert_freq_and_determine_vtune(scanner_comm &comm, rf_phreaker::frequency_type freq);

private:
	frequency_conversion frequency_conversion_;
	vtune vtune_;

	// include a struct that maintains history of freqpackets and proper vtune.. consider adding gain as well

};

}}