#pragma once

#include "rf_phreaker/layer_3_decoder_common/per_decoder_interface.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_sib_1_parser.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_sib_3_parser.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_sib_4_parser.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_sib_5_parser.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_sib_6_parser.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_sib_7_parser.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_sib_8_parser.h"

class lte_bcch_dl_sch_message : public per_decoder_interface
{
public:
	lte_bcch_dl_sch_message(void);
	~lte_bcch_dl_sch_message(void);

	void parse_data(layer_3_information::lte_rrc_message_aggregate &message);

private:
	lte_sib_1_parser lte_sib_1_parser_;
	lte_sib_3_parser lte_sib_3_parser_;
	lte_sib_4_parser lte_sib_4_parser_;
	lte_sib_5_parser lte_sib_5_parser_;
	lte_sib_6_parser lte_sib_6_parser_;
	lte_sib_7_parser lte_sib_7_parser_;
	lte_sib_8_parser lte_sib_8_parser_;
};

