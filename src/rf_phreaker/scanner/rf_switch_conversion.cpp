#include "rf_phreaker/scanner/rf_switch_conversion.h"
#include "rf_phreaker/scanner/packet_typedefs.h"
#include "rf_phreaker/common/common_types.h"

using namespace rf_phreaker::scanner;

rf_switch_conversion::rf_switch_conversion(void)
{
}


rf_switch_conversion::~rf_switch_conversion(void)
{
}
int rf_switch = 0;
packet_container rf_switch_conversion::get_rf_switches(rf_phreaker::frequency_type /*freq*/)
{
	packet_container container;

	container.add_packet(std::make_shared<set_switch_input_select_packet>(3));

	return container;
}
