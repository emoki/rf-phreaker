
#include "rf_phreaker/gsm_layer_3_library/cell_selection_parameters.h"

cell_selection_parameters::cell_selection_parameters(format_of_information_elements format)
								: information_element_type_3(format, cell_selection_parameters_value_bit_size)
{

}

cell_selection_parameters::~cell_selection_parameters()
{

}

void cell_selection_parameters::info_element_specific_decode()
{
	
	ms_txpwr_max_cch_  = raw_bit_stream_[value_byte_position()] & 0x1F;

	cell_reselect_hysteresis_ =  raw_bit_stream_[value_byte_position()] >> 5;

	acs_ = raw_bit_stream_[value_byte_position() + 1] >> 7;

	neci_ =  (raw_bit_stream_[value_byte_position() + 1] >> 7) & 0x2;

	rxlev_access_min_ = raw_bit_stream_[value_byte_position() + 1] & 0x3F;

}

void cell_selection_parameters::verify()
{

}