#include "rf_phreaker/gsm_layer_3_library/control_channel_description.h"

control_channel_description::control_channel_description(format_of_information_elements format)
								: information_element_type_3(format, control_channel_description_value_bit_size)
{

}

control_channel_description::~control_channel_description()
{

}

void control_channel_description::info_element_specific_decode()
{


}

void control_channel_description::verify()
{

}