#pragma once

namespace layer_3_information
{

enum pdu_element_type
{
	umts_bcch_bch,
	umts_mib,
	umts_sib1,
	umts_sib2,
	umts_sib3,
	umts_sib4,
	umts_sib11,
	umts_sib11_bis,
	umts_sib18,


	lte_bcch_sch,
	lte_sib1,
	lte_sib2,
	lte_sib3,
	lte_sib4,
	lte_sib5,
	lte_sib6,
	lte_sib7,
	lte_sib8,
	lte_sib9,
	lte_sib10,
	lte_sib11,

	number_pdu_elements
};

}