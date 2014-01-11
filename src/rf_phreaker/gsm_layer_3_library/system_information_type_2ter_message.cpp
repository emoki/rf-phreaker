

#include "rf_phreaker/gsm_layer_3_library/system_information_type_2ter_message.h"
#include <boost/lexical_cast.hpp>


system_information_type_2ter_message::system_information_type_2ter_message(void)
	:  neighbour_cell_description2_(value_only_format)
	 , si_2_ter_rest_octets_(value_only_format)
{
	information_elements_.push_back(&neighbour_cell_description2_);
	information_elements_.push_back(&si_2_ter_rest_octets_);

}


system_information_type_2ter_message::~system_information_type_2ter_message(void)
{
}

void system_information_type_2ter_message::verify()
{

}
