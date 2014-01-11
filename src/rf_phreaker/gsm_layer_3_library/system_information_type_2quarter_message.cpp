

#include "rf_phreaker/gsm_layer_3_library/system_information_type_2quarter_message.h"
#include <boost/lexical_cast.hpp>


system_information_type_2quarter_message::system_information_type_2quarter_message(void)
	                                     : si_2_quarter_rest_octets_(value_only_format)
{

	information_elements_.push_back(&si_2_quarter_rest_octets_);

}


system_information_type_2quarter_message::~system_information_type_2quarter_message(void)
{
}

void system_information_type_2quarter_message::verify()
{

}
