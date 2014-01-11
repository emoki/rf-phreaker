#pragma once

#include "rf_phreaker/gsm_layer_3_library/decode_interface.h"
#include <vector>
#include <boost/shared_ptr.hpp>

class generic_message : public decode_interface
{
public:
	generic_message(void);
	virtual ~generic_message(void);

	void decode(gsm_bit_stream &bs);

	void verify();

protected:
	std::vector</*boost::shared_ptr<decode_interface>*/decode_interface*> information_elements_;
};

