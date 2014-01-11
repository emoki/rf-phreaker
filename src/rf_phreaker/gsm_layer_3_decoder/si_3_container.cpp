#include "rf_phreaker/gsm_layer_3_decoder/si_3_container.h"


si_3_container::si_3_container(void)
{
}


si_3_container::~si_3_container(void)
{
}

void si_3_container::populate_data(gsm_bit_stream &bit_stream, layer_3_information::gsm_layer_3_message_aggregate &message)
{
	si_3.decode(bit_stream);
	
	message.mcc_ = *si_3.location_area_identification_.mcc_.get();
	message.mnc_ = *si_3.location_area_identification_.mnc_.get();
	message.lac_ = si_3.location_area_identification_.lac_;
	message.cid_ = si_3.cell_identity_.cell_identity_;
}
