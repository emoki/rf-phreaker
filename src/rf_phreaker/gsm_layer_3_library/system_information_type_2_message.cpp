

#include "rf_phreaker/gsm_layer_3_library/system_information_type_2_message.h"
#include <boost/lexical_cast.hpp>


system_information_type_2_message::system_information_type_2_message(void)
	: neighbour_cell_description_(value_only_format)
{
	information_elements_.push_back(&neighbour_cell_description_);

}


system_information_type_2_message::~system_information_type_2_message(void)
{
}

void system_information_type_2_message::verify()
{

}

