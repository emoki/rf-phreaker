#pragma once
#include <type_traits>
#include <QStringList>
#include <QRegularExpression>
#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate_io.h"
#include "rf_phreaker/gsm_layer_3_decoder/gsm_layer_3_decoder.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_layer_3_decoder.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_layer_3_decoder.h"

template<typename Decoder, typename Message>
class RawLayer3 {
public:
	RawLayer3() {
		init();
		decoder_.store_descriptions(true);
	}

	void init() {}

	void update(const layer_3_information::bit_stream &bits, std::string &bitString, std::string &messageType, std::string &description) {
		bitString.reserve(bits.bytes_.size() * 2);
		for(size_t i = 0; i < bits.bytes_.size(); ++i)
			bitString += rf_phreaker::hex_conversion::to_string<1>(bits.bytes_[i]);
		decode_text(bits);
		auto str = decoder_.get_text_description();
		format_text(str, description);
		// We change the str to the sib description for lte to avoid the overhead of parsing.
		if(std::is_same<Decoder, lte_asn1_decoder>::value)
			str = decoder_.get_sib_description();
		format_message_type(str, messageType);
	}

	void decode_text(const layer_3_information::bit_stream &bits) {
		decoder_.decode_bcch_bch_message(bits.bytes_.data(), bits.bytes_.size(), bits.unused_bits_, Message{});
	}

	void format_message_type(std::vector<std::string> &list, std::string &message_type) {}

	void format_text(std::vector<std::string> &list, std::string &description) {
		for(auto &k : list)
			description.append(k);
	}

private:
	Decoder decoder_;
	QRegularExpression regex_;
};

template<>
void RawLayer3<umts_asn1_decoder, layer_3_information::umts_bcch_bch_message_aggregate>::init() {
	using namespace layer_3_information;
	std::vector<pdu_element_type> pdus{umts_bcch_bch, umts_mib, umts_sib1, umts_sib2, umts_sib3, umts_sib4, umts_sib11, umts_sib11_bis, umts_sib18};
	decoder_.specify_sibs_for_decoding(pdus.data(), pdus.size());
}

template<>
void RawLayer3<gsm_layer_3_decoder, layer_3_information::gsm_layer_3_message_aggregate>::format_message_type(std::vector<std::string> &list, std::string &message_type) {
	// Formats as SYSTEM_INFORMATION_TYPE_4_DN
	size_t i = 0;
	for(auto &k : list) {
		auto end_ptr_1 = k.find_first_of(" {");
		if(end_ptr_1 != std::string::npos) {
			message_type.append(k.data(), k.data() + end_ptr_1);
		}
		if(++i < list.size())
			message_type.append(" : ");
	}
}

template<>
void RawLayer3<umts_asn1_decoder, layer_3_information::umts_bcch_bch_message_aggregate>::format_message_type(std::vector<std::string> &list, std::string &message_type) {
	// Umts has multiple data decoded so we only take the first string from each description.
	size_t i = 0;
	for(auto &k : list) {
		auto end_ptr_1 = k.find_first_of(" ");
		if(end_ptr_1 != std::string::npos) {
			message_type.append(k.data(), k.data() + end_ptr_1);
		}
		if(++i < list.size())
			message_type.append(" : ");
	}
}

template<>
void RawLayer3<lte_asn1_decoder, layer_3_information::lte_rrc_message_aggregate>::format_message_type(std::vector<std::string> &list, std::string &message_type) {
	// Formats as BCCH-DL-SCH-Message :: SystemInformationBlockType1
	size_t i = 0;
	for(auto &k : list) {
		message_type.append(k);
		if(++i < list.size())
			message_type.append(" : ");
	}
}

template<> 
void RawLayer3<gsm_layer_3_decoder, layer_3_information::gsm_layer_3_message_aggregate>::decode_text(const layer_3_information::bit_stream &bits) {
	decoder_.decode_bcch_message(bits.bytes_.data(), bits.bytes_.size(), bits.unused_bits_, layer_3_information::gsm_layer_3_message_aggregate{});
}
