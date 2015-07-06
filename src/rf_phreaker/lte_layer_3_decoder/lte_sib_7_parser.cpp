#include "rf_phreaker/lte_layer_3_decoder/lte_sib_7_parser.h"
#include "rf_phreaker/layer_3_decoder_common/decode_support_functions.h"
#include <iostream>

using namespace layer_3_information;

lte_sib_7_parser::lte_sib_7_parser(void)
{}


lte_sib_7_parser::~lte_sib_7_parser(void)
{}

void lte_sib_7_parser::parse_data(const SystemInformationBlockType7_t &data, lte_rrc_message_aggregate &message)
{
//	std::cout << "lte_sib7!" << std::endl;

	message.sib7_.is_decoded_ = true;

	if(data.carrierFreqsInfoList) {

		auto &info_list = data.carrierFreqsInfoList->list;		
		for(int i = 0; i < info_list.count; ++i) {

			carrier_freqs_info_geran geran_info;

			geran_info.carrier_freqs_.starting_arfcn_ = info_list.array[i]->carrierFreqs.startingARFCN;

			switch((BandIndicatorGERAN)info_list.array[i]->carrierFreqs.bandIndicator)
			{
			case BandIndicatorGERAN_dcs1800:
				geran_info.carrier_freqs_.band_indicator_ = dcs_1800_was_used;
				break;
			case BandIndicatorGERAN_pcs1900:
				geran_info.carrier_freqs_.band_indicator_ = pcs_1900_was_used;
				break;
			default:
				geran_info.carrier_freqs_.band_indicator_ = unknown_band_was_used;
			}

			switch((CarrierFreqsGERAN__followingARFCNs_PR)info_list.array[i]->carrierFreqs.followingARFCNs.present)
			{
			case CarrierFreqsGERAN__followingARFCNs_PR_explicitListOfARFCNs:
				geran_info.carrier_freqs_.following_arfcns_ = convert_explicit(info_list.array[i]->carrierFreqs.followingARFCNs.choice.explicitListOfARFCNs, geran_info.carrier_freqs_.starting_arfcn_);
				break;
			case CarrierFreqsGERAN__followingARFCNs_PR_equallySpacedARFCNs:
				geran_info.carrier_freqs_.following_arfcns_ = convert_equally_spaced(info_list.array[i]->carrierFreqs.followingARFCNs.choice.equallySpacedARFCNs.arfcn_Spacing,
					info_list.array[i]->carrierFreqs.followingARFCNs.choice.equallySpacedARFCNs.numberOfFollowingARFCNs, geran_info.carrier_freqs_.starting_arfcn_);
				break;
			case CarrierFreqsGERAN__followingARFCNs_PR_variableBitMapOfARFCNs:
				geran_info.carrier_freqs_.following_arfcns_ = convert_variable_bitmap(info_list.array[i]->carrierFreqs.followingARFCNs.choice.variableBitMapOfARFCNs, geran_info.carrier_freqs_.starting_arfcn_);
				break;
			case CarrierFreqsGERAN__followingARFCNs_PR_NOTHING:
			default:
				;
			}

			geran_info.common_info_.cell_reselection_priority_ = info_list.array[i]->commonInfo.cellReselectionPriority == nullptr ?
				*info_list.array[i]->commonInfo.cellReselectionPriority : -1;

			geran_info.common_info_.threshold_x_high_ = info_list.array[i]->commonInfo.threshX_High;
			geran_info.common_info_.threshold_x_low_ = info_list.array[i]->commonInfo.threshX_Low;

			message.sib7_.carrier_freqs_info_list_geran_.push_back(geran_info);
		}
	}
}

std::vector<int> lte_sib_7_parser::convert_explicit(const ExplicitListOfARFCNs_t &arfcns, int start)
{
	std::vector<int> v;

	v.push_back(start);
	
	for(int i =0; i < arfcns.list.count; ++i) {
		v.push_back(*arfcns.list.array[i]);
	}
	
	return v;
}

std::vector<int> lte_sib_7_parser::convert_equally_spaced(long arfcn_Spacing, long numberOfFollowingARFCNs, int start)
{
	std::vector<int> v;
	
	for(int i = 0; i <= numberOfFollowingARFCNs; ++i)
	{
		v.push_back((start + i * arfcn_Spacing) % 1024);
	}

	return v;
}

std::vector<int> lte_sib_7_parser::convert_variable_bitmap(const OCTET_STRING_t &octets, int start)
{
	std::vector<int> v;

	v.push_back(start);

	for(int i = 0; i < octets.size; ++i) {
		for(int j = 7; j >= 0; --j) {
			uint8_t bit = octets.buf[i] >> j;
			bit &= 0x1;
			if(bit)
				v.push_back((start + ((8 - j) * (i + 1))) % 1024);
		}
	}

	return v;
}

