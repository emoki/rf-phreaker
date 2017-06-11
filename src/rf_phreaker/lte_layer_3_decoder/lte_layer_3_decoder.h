#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_DLL
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllimport))
#else
#define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#endif
#define DLL_LOCAL
#else
#if __GNUC__ >= 4
#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define DLL_PUBLIC
#define DLL_LOCAL
#endif
#endif

#include <stdint.h>
#include <string>
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/layer_3_common/pdu_element_types.h"

class lte_bcch_dl_sch_message;



class DLL_PUBLIC lte_asn1_decoder
{
public:
	lte_asn1_decoder();
	~lte_asn1_decoder();
	
	int specify_sibs_for_decoding(const layer_3_information::pdu_element_type *elements, size_t num_elements);

	int decode_bcch_bch_message(const uint8_t* bit_stream, uint32_t num_of_bytes, uint32_t unused_bits, layer_3_information::lte_rrc_message_aggregate &message);

	std::vector<std::string> get_text_description();

	void store_text_description(bool store_text);

	void output_debug_bit_stream(bool out) { debug_ = out; }

private:
	lte_bcch_dl_sch_message * lte_bcch_bch_message_;
	bool debug_;
};





