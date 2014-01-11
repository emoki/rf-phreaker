

#include "rf_phreaker/gsm_layer_3_library/rach_control_parameters.h"

rach_control_parameters::rach_control_parameters(format_of_information_elements format)
								: information_element_type_3(format, rach_control_parameters_value_bit_size)
{

}

rach_control_parameters::~rach_control_parameters()
{

}

void rach_control_parameters::info_element_specific_decode()
{


}

void rach_control_parameters::verify()
{

}