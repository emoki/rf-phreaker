// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ASN1C_OPEN_SOURCE_DLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ASN1C_OPEN_SOURCE_DLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ASN1C_OPEN_SOURCE_DLL_EXPORTS
#define ASN1C_OPEN_SOURCE_DLL_API __declspec(dllexport)
#else
#define ASN1C_OPEN_SOURCE_DLL_API __declspec(dllimport)
#endif

#include <stdint.h>
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/pdu_element_types.h"

class umts_bcch_bch_message;
class lte_bcch_sch_message;

class ASN1C_OPEN_SOURCE_DLL_API umts_asn1_decoder
{
public:
	umts_asn1_decoder();
	~umts_asn1_decoder();
	
	int specify_sibs_for_decoding(const layer_3_information::pdu_element_type *elements, size_t num_elements);

	int decode_bcch_bch_message(const uint8_t* bit_stream, uint32_t num_of_bytes, uint32_t unused_bits, layer_3_information::umts_bcch_bch_message_aggregate &message);

private:
	umts_bcch_bch_message *umts_bcch_bch_message_;
};










