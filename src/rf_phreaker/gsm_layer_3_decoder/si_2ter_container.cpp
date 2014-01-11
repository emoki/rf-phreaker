#include "rf_phreaker/gsm_layer_3_decoder/si_2ter_container.h"


si_2ter_container::si_2ter_container(void)
{
}


si_2ter_container::~si_2ter_container(void)
{
}

void si_2ter_container::populate_data(gsm_bit_stream &bit_stream, layer_3_information::gsm_layer_3_message_aggregate &message)
{
	si_2ter.decode(bit_stream);

	for(uint8_t ii = 0 ; ii< si_2ter.neighbour_cell_description2_.num_ba ; ii++)
	{
		message.neighbour_list_.push_back(si_2ter.neighbour_cell_description2_.f[ii]) ;
	
	
	}
}
	
	