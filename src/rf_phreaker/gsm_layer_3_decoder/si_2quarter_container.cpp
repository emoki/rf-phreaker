#include "rf_phreaker/gsm_layer_3_decoder/si_2quarter_container.h"


si_2quarter_container::si_2quarter_container(void)
{
}


si_2quarter_container::~si_2quarter_container(void)
{
}

void si_2quarter_container::populate_data(gsm_bit_stream &bit_stream, layer_3_information::gsm_layer_3_message_aggregate &message)
{
	si_2quarter.decode(bit_stream);

	
}
	
	