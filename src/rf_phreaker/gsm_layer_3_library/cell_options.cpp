#include "rf_phreaker/gsm_layer_3_library/cell_options.h"

cell_options::cell_options(format_of_information_elements format)
								: information_element_type_3(format, cell_options_value_bit_size)
{

}

cell_options::~cell_options()
{

}

void cell_options::info_element_specific_decode()
{


}

void cell_options::verify()
{

}