#include "rf_phreaker/common/operating_band_range_specifier.h"
#include "rf_phreaker/common/common_utility.h"

namespace rf_phreaker {


operating_band_range_specifier::operating_band_range_specifier(void) {
	// Push back the ranges in the same order as they are in the operating_band_enum.
	// The edges of the bands start at the center frequency of the first channel 
	// and end at the center frequency of the last channel - no point scanning outside them.
	operating_bands_.push_back(operating_band_range(OPERATING_BAND_UNKNOWN, -1, -1));

	operating_bands_.push_back(operating_band_range(GSM_T_380, khz(390200) + khz(200), khz(399800) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_T_410, khz(420200) + khz(200), khz(429800) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_450, khz(460400) + khz(200), khz(467600) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_480, khz(488800) + khz(200), mhz(496) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_710, khz(728000) + khz(200), khz(746000) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_750, khz(747000) + khz(200), khz(763000) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_T_810, khz(851000) + khz(200), khz(866000) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_850, khz(869000) + khz(200), khz(894000) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_P_900, mhz(935) + khz(200), mhz(960) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_E_900, mhz(925) + khz(200), mhz(960) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_R_900, mhz(921) + khz(200), mhz(960) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_ER_900, mhz(918) + khz(200), mhz(960) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_T_900, khz(915400) + khz(200), khz(921000) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_DCS_1800, khz(1805000) + khz(200), khz(1880000) - khz(200)));
	operating_bands_.push_back(operating_band_range(GSM_PCS_1900, khz(1930000) + khz(200), khz(1990000) - khz(200)));

	// Channels are only valid to +- 2.4khz from the end of the band.
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_1, khz(2112400LL), khz(2167600LL)));	//  2100	IMT	1920 - 1980	2110 – 2170
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_2, khz(1932400), khz(1987600)));	//  1900	PCS A-F	1850 – 1910	1930 – 1990
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_3, khz(1807400), khz(1877600)));	//	1800	DCS	1710 – 1785	1805 – 1880
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_4, khz(2112400LL), khz(2152600LL)));	//	1700	AWS A-F	1710 – 1755	2110 – 2155			
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_5, khz(871400), khz(891600)));	//	850	CLR	824 – 849	869 – 894				
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_6, khz(877400), khz(882600)));	//	800		830 – 840	875 – 885				
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_7, khz(2622400LL), khz(2687600LL)));	//	2600	IMT-E	2500 – 2570	2620 – 2690
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_8, khz(927400), khz(957600)));	//	900	E-GSM	880 – 915	925 – 960
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_9, khz(1847400), khz(1877400)));	//	1700		1749.9 – 1784.9	1844.9 – 1879.9
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_10, khz(2112400LL), khz(2167600LL)));	//	1700	EAWS A-G	1710 – 1770	2110 – 2170
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_11, khz(1478400), khz(1493400)));	//	1500	LPDC	1427.9 – 1447.9	1475.9 – 1495.9
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_12, khz(731400), khz(743600)));	//	700	LSMH A/B/C	699 – 716	729 – 746
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_13, khz(748400), khz(753600)));	//	700	USMH C	777 – 787	746 – 756
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_14, khz(760400), khz(765600)));	//	700	USMH D	788 – 798	758 – 768
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_19, khz(877400), khz(887600)));	//	800		832.4 – 842.6	877.4 – 887.6
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_20, khz(793400), khz(818600)));	//	800	EUDD	832 – 862	791 – 821
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_21, khz(1498400), khz(1508400)));	//	1500	UPDC	1447.9 – 1462.9	1495.9 – 1510.9
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_22, khz(3512400LL), khz(3587600LL)));	//	3500		3410 – 3490	3510 – 3590
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_25, khz(1932400), khz(1992600)));	//	1900	EPCS A-G	1850 – 1915	1930 – 1995
	operating_bands_.push_back(operating_band_range(UMTS_OPERATING_BAND_26, khz(861400), khz(891600)));	//	850	ECLR	814 – 849	859 – 894

	// Channels are valid all the way to the edges of the band.  
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_1, khz(2110000LL), khz(2170000LL)));	//	1920 - 1980	2110 - 2170	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_2, khz(1930000), khz(1990000)));	//	1850 - 1910	1930 - 1990	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_3, khz(1805000), khz(1880000)));	//	1710 - 1785	1805 - 1880	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_4, khz(2110000LL), khz(2155000LL)));	//	1710 - 1755	2110 - 2155	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_5, khz(869000), khz(894000)));	//	824 - 849	869 - 894	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_6, khz(875000), khz(885000)));	//	830 - 840	875 - 885	FDD			
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_7, khz(2620000LL), khz(2690000LL)));	//	2500 - 2570	2620 - 2690	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_8, khz(925000), khz(960000)));	//	880 - 915	925 - 960	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_9, khz(1844900), khz(1879900)));	//	1749.9 - 1784.9	1844.9 - 1879.9	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_10, khz(2110000LL), khz(2170000LL)));	//	1710 - 1770	2110 - 2170	FDD			
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_11, khz(1475900), khz(1495900)));	//	1427.9 - 1447.9	1475.9 - 1495.9	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_12, khz(729000), khz(746000)));	//	699 - 716	729 - 746	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_13, khz(746000), khz(756000)));	//	777 - 787	746 - 756	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_14, khz(758000), khz(768000)));	//	788 - 798	758 - 768	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_17, khz(734000), khz(746000)));	//	704 - 716	734 - 746	FDD			
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_18, khz(860000), khz(875000)));	//	815 - 830	860 - 875	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_19, khz(875000), khz(890000)));	//	830 - 845	875 - 890	FDD			
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_20, khz(791000), khz(821000)));	//	832 - 862	791 - 821	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_21, khz(1495900), khz(1510900)));	//	1447.9 - 1462.9	1495.9 - 1510.9	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_22, khz(3510000LL), khz(3590000LL)));	//	3410 - 3490	3510 - 3590	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_23, khz(2180000LL), khz(2200000LL)));	//	2000 - 2020	2180 - 2200	FDD			
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_24, khz(1525000), khz(1559000)));	//	1626.5 - 1660.5	1525 - 1559	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_25, khz(1930000), khz(1995000)));	//	1850 - 1915	1930 - 1995	FDD			
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_26, khz(859000), khz(894000)));	//	814 - 849	859 - 894	FDD			
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_27, khz(852000), khz(869000)));	//	807 - 824	852 - 869	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_28, khz(758000), khz(803000)));	//	703 - 748	758 - 803	FDD
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_29, khz(717000), khz(728000)));	//	N/A	716 - 728	FDD		
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_30, khz(2350000LL), khz(2360000LL)));	//	2305 - 2315 	2350 - 2360	FDD		
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_33, khz(1900000), khz(1920000)));	//	
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_34, khz(2010000LL), khz(2025000LL)));	//
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_35, khz(1850000), khz(1910000)));	//
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_36, khz(1930000), khz(1990000)));	//	
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_37, khz(1910000), khz(1930000)));	//	
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_38, khz(2570000LL), khz(2620000LL)));	//	
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_39, khz(1880000), khz(1920000)));	//	
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_40, khz(2300000LL), khz(2400000LL)));	//	
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_41, khz(2496000LL), khz(2690000LL)));	//	
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_42, khz(3400000LL), khz(3600000LL)));	//	
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_43, khz(3600000LL), khz(3800000LL)));	//	
	operating_bands_.push_back(operating_band_range(LTE_OPERATING_BAND_44, khz(703000), khz(803000)));	//	

	for(int i = FIRST_GSM_OPERATING_BAND; i <= LAST_GSM_OPERATING_BAND; ++i) {
		gsm_lookup_ += std::make_pair(interval_t::closed(operating_bands_[i].low_freq_hz_, operating_bands_[i].high_freq_hz_), std::set<int>{i});
	}
	for(int i = FIRST_UMTS_OPERATING_BAND; i <= LAST_UMTS_OPERATING_BAND; ++i) {
		umts_lookup_ += std::make_pair(interval_t::closed(operating_bands_[i].low_freq_hz_, operating_bands_[i].high_freq_hz_), std::set<int>{i});
	}
	for(int i = FIRST_LTE_OPERATING_BAND; i <= LAST_LTE_OPERATING_BAND; ++i) {
		lte_lookup_ += std::make_pair(interval_t::closed(operating_bands_[i].low_freq_hz_, operating_bands_[i].high_freq_hz_), std::set<int>{i});
	}
}

operating_band_range_specifier::~operating_band_range_specifier(void) {}

operating_band_range operating_band_range_specifier::get_band_freq_range(operating_band band) const {
	return operating_bands_[band];
}

std::vector<operating_band_range> operating_band_range_specifier::find_avaliable_gsm_operating_bands(frequency_type freq) const {
	//return find_avaliable_operating_bands(freq, FIRST_GSM_OPERATING_BAND, LAST_GSM_OPERATING_BAND);
	return find_avaliable_operating_bands(freq, gsm_lookup_);
}

std::vector<operating_band_range> operating_band_range_specifier::find_avaliable_umts_operating_bands(frequency_type freq) const {
	//return find_avaliable_operating_bands(freq, FIRST_UMTS_OPERATING_BAND, LAST_UMTS_OPERATING_BAND);
	return find_avaliable_operating_bands(freq, umts_lookup_);
}

std::vector<operating_band_range> operating_band_range_specifier::find_avaliable_lte_operating_bands(frequency_type freq) const {
	//return find_avaliable_operating_bands(freq, FIRST_LTE_OPERATING_BAND, LAST_LTE_OPERATING_BAND);
	return find_avaliable_operating_bands(freq, lte_lookup_);
}

std::vector<operating_band_range> operating_band_range_specifier::find_avaliable_operating_bands(frequency_type freq, const map_t &m) const {
	using namespace boost::icl;
	std::vector<operating_band_range> valid_bands;

	auto f = interval_t::closed(freq, freq);

	auto t = m.find(f);

	if(t != m.end()) {
		for(auto i : t->second)
			valid_bands.push_back(operating_bands_[i]);
	}

	return valid_bands;
}

std::vector<operating_band_range> operating_band_range_specifier::find_avaliable_operating_bands(frequency_type freq, operating_band begin, operating_band inclusive_end) const {
	std::vector<operating_band_range> valid_bands;

	for(int i = begin; i <= inclusive_end; ++i) {
		if(operating_bands_[i].low_freq_hz_ <= freq && operating_bands_[i].high_freq_hz_ >= freq)
			valid_bands.push_back(operating_bands_[i]);
	}

	return valid_bands;
}

std::vector<operating_band_range> operating_band_range_specifier::get_all_operating_bands(operating_band begin, operating_band inclusive_end) const {
	std::vector<operating_band_range> valid_bands;

	valid_bands.reserve(inclusive_end - begin + 1);

	for(int i = begin; i <= inclusive_end; ++i) {
		valid_bands.push_back(operating_bands_[i]);
	}

	return valid_bands;
}


}