#pragma once

#include <boost/shared_ptr.hpp>
#include "rf_phreaker/umts_rrc_asn_library/BCCH-BCH-Message.h"
#include "rf_phreaker/layer_3_decoder_common/pdu_element.h"
#include "rf_phreaker/layer_3_decoder_common/bit_stream_container.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_system_information_container.h"
#include "rf_phreaker/umts_layer_3_decoder/segmented_sib_container.h"


class umts_bcch_bch_message : public per_decoder_interface
{
public:
	umts_bcch_bch_message(void);
	~umts_bcch_bch_message(void);

	void set_system_information_to_decode(const std::vector<layer_3_information::pdu_element_type> &pdu_elements);

	void parse_data(layer_3_information::umts_bcch_bch_message_aggregate &message);

private:
	void handle_first_segment(const FirstSegmentShort_t &first_segment);
	void handle_first_segment(const FirstSegment_t &first_segment);

	void handle_subsequent_segment(const SubsequentSegment_t &subsequent_segment);

	void handle_last_segment(const LastSegmentShort_t &last_segment);
	void handle_last_segment(const LastSegment_t &last_segment);

	void handle_complete_sib(const CompleteSIBshort &complete_sib);
	void handle_complete_sib(const CompleteSIB_t &complete_sib);

	void handle_complete_sib_list(const CompleteSIB_List_t &complete_sib_list);

	umts_system_information_container * find_available_system_information(sib_type sib);
	
	void check_for_complete_sib_and_process(umts_system_information_container *sys_info, const unique_sector_sib &key);

	std::vector<boost::shared_ptr<umts_system_information_container>> system_information_to_decode_;

	segmented_sib_container segmented_sibs_container_;
	
	layer_3_information::umts_bcch_bch_message_aggregate *current_message_aggregate_;
};




