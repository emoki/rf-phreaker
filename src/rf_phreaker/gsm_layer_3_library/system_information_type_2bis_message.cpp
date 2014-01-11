

#include "rf_phreaker/gsm_layer_3_library/system_information_type_2bis_message.h"
#include <boost/lexical_cast.hpp>


system_information_type_2bis_message::system_information_type_2bis_message(void)
	: neighbour_cell_description_(type_and_value_format)
	 ,rach_control_parameters_(value_only_format)
	 ,si_2_bis_rest_octets_(value_only_format)
{
	information_elements_.push_back(&neighbour_cell_description_);
	information_elements_.push_back(&rach_control_parameters_);
	information_elements_.push_back(&si_2_bis_rest_octets_);

}


system_information_type_2bis_message::~system_information_type_2bis_message(void)
{
}

void system_information_type_2bis_message::verify()
{

}

