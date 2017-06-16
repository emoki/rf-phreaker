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
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"


class gsm_layer_3_container;

class DLL_PUBLIC gsm_layer_3_decoder
{
public:
	gsm_layer_3_decoder();

	~gsm_layer_3_decoder();

	int32_t decode_bcch_message(const uint8_t *bit_stream, uint32_t num_of_bytes, uint32_t unused_bits, layer_3_information::gsm_layer_3_message_aggregate &message);

	void update_message_decode_list(layer_3_information::gsm_bcch_si_type message_t);

	std::vector<std::string> get_text_description();

	void store_descriptions(bool store);

	std::vector<std::string> get_sib_description();

	void output_debug_bit_stream(bool out) { debug_ = out; }

private:
	bool debug_;
	bool store_text_description_;
	std::string text_description_;
};

