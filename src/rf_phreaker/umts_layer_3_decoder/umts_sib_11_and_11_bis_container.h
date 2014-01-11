#pragma once

#include "rf_phreaker/umts_layer_3_decoder/umts_system_information_container.h"
#include <boost/scoped_ptr.hpp>


class umts_sib_11_and_11_bis_container : public umts_system_information_container
{
public:
	umts_sib_11_and_11_bis_container(void);

	~umts_sib_11_and_11_bis_container(void);

	virtual decode_status decode_data(const bit_stream_container &bit_stream, pdu_element_container &pdu_element);

	virtual void parse_data(layer_3_information::umts_bcch_bch_message_aggregate &message);

private:
	void parse_sib_11_bis();

	void parse_sib_11();

	void remove_decoded_pdu_element();

	bool last_decode_was_sib_11_bis_;

	boost::scoped_ptr<pdu_element_container> current_pdu_;

	layer_3_information::umts_bcch_bch_message_aggregate *current_message_;

	template<typename Data>
	void parse_intra_measurement_sys_info(const Data &data);

	template<typename Data>
	void parse_inter_measurement_sys_info(const Data &data);

	template<typename Data>
	void parse_inter_rat_measurement_sys_info(const Data &data);

};

