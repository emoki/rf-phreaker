#include "rf_phreaker/scanner/frequency_v_tune.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;

frequency_v_tune::frequency_v_tune(void)
{
}


frequency_v_tune::~frequency_v_tune(void)
{
}

packet_container frequency_v_tune::convert_freq_and_determine_vtune(scanner_comm &comm, frequency_type freq)
{
	packet_container container = frequency_conversion_.convert_to_packet_container(freq);

	container.add_container(vtune_.determine_vtune(comm, container));

	return container;
}


