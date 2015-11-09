#pragma once

#include <stdint.h>
#include <string>
#include <set>
#include <vector>

namespace rf_phreaker {

typedef std::string scanner_serial_type; // Includes NULL terminator.

typedef int64_t frequency_type;

typedef int32_t channel_type;

typedef int32_t bandwidth_type;

typedef int64_t time_type;

enum specifier
{
	GSM_SWEEP,
	GSM_LAYER_3_DECODE,
	CDMA_SWEEP,
	CDMA_LAYER_3_DECODE,
	UMTS_SWEEP,
	UMTS_LAYER_3_DECODE,
	LTE_SWEEP,
	LTE_LAYER_3_DECODE,
	RAW_DATA,
	UNKOWN_SPECIFIER
};

class specifiers {
public:
	specifiers() {}
	specifiers(specifier spec) : specs_({spec}) {}
	specifiers(std::vector<specifier> specs) {
		for(auto &i : specs)
			specs_.insert(i);
	}
	void add_spec(specifier spec) { specs_.insert(spec); }
	void remove_spec(specifier spec) { specs_.erase(spec); }
	bool has_spec(specifier spec) const { return specs_.find(spec) != specs_.end(); }
	bool does_overlap(const specifiers &specs) {
		for(const auto &i : specs.specs_) {
			if(specs_.find(i) != specs_.end())
				return true;
		}
		return false;
	}
	bool operator==(const specifiers& s) const { return specs_ == s.specs_; }
	bool operator!=(const specifiers& s) const { return specs_ != s.specs_; }
private:
	std::set<specifier> specs_;
};

struct frequency_path
{
	frequency_path() : low_freq_(-1), high_freq_(-1) {}
	frequency_path(frequency_type start, frequency_type end) : low_freq_(start), high_freq_(end) {}
	frequency_type low_freq_;
	frequency_type high_freq_;
};

enum device_communication
{
	USB_HI_SPEED,
	USB_SUPER_SPEED,
	UNKNOWN_SPEED
};

enum message_codes
{
	FREQUENCY_CORRECTION_SUCCESSFUL,
	GENERAL_ERROR,
	STD_EXCEPTION_ERROR,
	UNKNOWN_ERROR,
	FREQUENCY_CORRECTION_FAILED,
	EEPROM_ERROR,
	CALIBRATION_ERROR,
	CONVERSION_ERROR
};

// See bottom for more on operating bands.
enum operating_band
{
	OPERATING_BAND_UNKNOWN,

	GSM_T_380, //	380	380.2–389.8	390.2–399.8	dynamic
	GSM_T_410, //	410	410.2–419.8	420.2–429.8	dynamic
	GSM_450, //	450	450.6–457.6	460.6–467.6	259–293
	GSM_480, //	480	479.0–486.0	489.0–496.0	306–340
	GSM_710, //	710	698.2–716.2	728.2–746.2	dynamic
	GSM_750, //	750	747.2–762.2	777.2–792.2	438–511
	GSM_T_810, //	810	806.2–821.2	851.2–866.2	dynamic
	GSM_850, //	850	824.2–849.2	869.2–894.2	128–251
	GSM_P_900, //	900	890.0–915.0	935.0–960.0	1–124
	GSM_E_900, //	900	880.0–915.0	925.0–960.0	975–1023, 0-124
	GSM_R_900, //	900	876.0–915.0	921.0–960.0	955–1023, 0-124
	GSM_ER_900, //	900	873.0–915.0	918.0–960.0	945–1023, 0-124
	GSM_T_900, //	900	870.4–876.0	915.4–921.0	dynamic^
	GSM_DCS_1800, //	1800	1,710.2–1,784.8	1,805.2–1,879.8	512–885
	GSM_PCS_1900, //	1900	1,850.2–1,909.8	1,930.2–1,989.8	512–810

	UMTS_OPERATING_BAND_1,	//  2100	IMT	1920 - 1980	2110 – 2170
	UMTS_OPERATING_BAND_2,	//  1900	PCS A-F	1850 – 1910	1930 – 1990
	UMTS_OPERATING_BAND_3,	//	1800	DCS	1710 – 1785	1805 – 1880
	UMTS_OPERATING_BAND_4,	//	1700	AWS A-F	1710 – 1755	2110 – 2155
	UMTS_OPERATING_BAND_5,	//	850	CLR	824 – 849	869 – 894
	UMTS_OPERATING_BAND_6,	//	800		830 – 840	875 – 885
	UMTS_OPERATING_BAND_7,	//	2600	IMT-E	2500 – 2570	2620 – 2690
	UMTS_OPERATING_BAND_8,	//	900	E-GSM	880 – 915	925 – 960
	UMTS_OPERATING_BAND_9,	//	1700		1749.9 – 1784.9	1844.9 – 1879.9
	UMTS_OPERATING_BAND_10,	//	1700	EAWS A-G	1710 – 1770	2110 – 2170
	UMTS_OPERATING_BAND_11,	//	1500	LPDC	1427.9 – 1447.9	1475.9 – 1495.9
	UMTS_OPERATING_BAND_12,	//	700	LSMH A/B/C	699 – 716	729 – 746
	UMTS_OPERATING_BAND_13,	//	700	USMH C	777 – 787	746 – 756
	UMTS_OPERATING_BAND_14,	//	700	USMH D	788 – 798	758 – 768
	UMTS_OPERATING_BAND_19,	//	800		832.4 – 842.6	877.4 – 887.6
	UMTS_OPERATING_BAND_20,	//	800	EUDD	832 – 862	791 – 821
	UMTS_OPERATING_BAND_21,	//	1500	UPDC	1447.9 – 1462.9	1495.9 – 1510.9
	UMTS_OPERATING_BAND_22,	//	3500		3410 – 3490	3510 – 3590
	UMTS_OPERATING_BAND_25,	//	1900	EPCS A-G	1850 – 1915	1930 – 1995
	UMTS_OPERATING_BAND_26,	//	850	ECLR	814 – 849	859 – 894

	LTE_OPERATING_BAND_1,	//	1920 - 1980	2110 - 2170	FDD
	LTE_OPERATING_BAND_2,	//	1850 - 1910	1930 - 1990	FDD
	LTE_OPERATING_BAND_3,	//	1710 - 1785	1805 - 1880	FDD
	LTE_OPERATING_BAND_4,	//	1710 - 1755	2110 - 2155	FDD
	LTE_OPERATING_BAND_5,	//	824 - 849	869 - 894	FDD
	LTE_OPERATING_BAND_6,	//	830 - 840	875 - 885	FDD
	LTE_OPERATING_BAND_7,	//	2500 - 2570	2620 - 2690	FDD
	LTE_OPERATING_BAND_8,	//	880 - 915	925 - 960	FDD
	LTE_OPERATING_BAND_9,	//	1749.9 - 1784.9	1844.9 - 1879.9	FDD
	LTE_OPERATING_BAND_10,	//	1710 - 1770	2110 - 2170	FDD
	LTE_OPERATING_BAND_11,	//	1427.9 - 1447.9	1475.9 - 1495.9	FDD
	LTE_OPERATING_BAND_12,	//	699 - 716	729 - 746	FDD
	LTE_OPERATING_BAND_13,	//	777 - 787	746 - 756	FDD
	LTE_OPERATING_BAND_14,	//	788 - 798	758 - 768	FDD
	LTE_OPERATING_BAND_17,	//	704 - 716	734 - 746	FDD
	LTE_OPERATING_BAND_18,	//	815 - 830	860 - 875	FDD
	LTE_OPERATING_BAND_19,	//	830 - 845	875 - 890	FDD
	LTE_OPERATING_BAND_20,	//	832 - 862	791 - 821	FDD
	LTE_OPERATING_BAND_21,	//	1447.9 - 1462.9	1495.9 - 1510.9	FDD
	LTE_OPERATING_BAND_22,	//	3410 - 3490	3510 - 3590	FDD
	LTE_OPERATING_BAND_23,	//	2000 - 2020	2180 - 2200	FDD
	LTE_OPERATING_BAND_24,	//	1626.5 - 1660.5	1525 - 1559	FDD
	LTE_OPERATING_BAND_25,	//	1850 - 1915	1930 - 1995	FDD
	LTE_OPERATING_BAND_26,	//	814 - 849	859 - 894	FDD
	LTE_OPERATING_BAND_27,	//	807 - 824	852 - 869	FDD
	LTE_OPERATING_BAND_28,	//	703 - 748	758 - 803	FDD
	LTE_OPERATING_BAND_29,	//	N/A	716 - 728	FDD
	LTE_OPERATING_BAND_30,	//	2305 - 2315	 2350 - 2360 FDD
	LTE_OPERATING_BAND_33,	//	1900 - 1920		TDD
	LTE_OPERATING_BAND_34,	//	2010 - 2025		TDD
	LTE_OPERATING_BAND_35,	//	1850 - 1910		TDD
	LTE_OPERATING_BAND_36,	//	1930 - 1990		TDD
	LTE_OPERATING_BAND_37,	//	1910 - 1930		TDD
	LTE_OPERATING_BAND_38,	//	2570 - 2620		TDD
	LTE_OPERATING_BAND_39,	//	1880 - 1920		TDD
	LTE_OPERATING_BAND_40,	//	2300 - 2400		TDD
	LTE_OPERATING_BAND_41,	//	2496 - 2690		TDD
	LTE_OPERATING_BAND_42,	//	3400 - 3600		TDD
	LTE_OPERATING_BAND_43,	//	3600 - 3800		TDD
	LTE_OPERATING_BAND_44,	//	703 - 803		TDD

	FIRST_GSM_OPERATING_BAND = GSM_T_380,
	LAST_GSM_OPERATING_BAND = GSM_PCS_1900,
	FIRST_UMTS_OPERATING_BAND = UMTS_OPERATING_BAND_1,
	LAST_UMTS_OPERATING_BAND = UMTS_OPERATING_BAND_26,
	FIRST_LTE_OPERATING_BAND = LTE_OPERATING_BAND_1,
	LAST_LTE_OPERATING_BAND = LTE_OPERATING_BAND_44,
};

class operating_bands {
public:
	operating_bands() {}
	operating_bands(operating_band band) : bands_({band}) {}
	operating_bands(std::vector<operating_band> bands) {
		for(auto &i : bands)
			bands_.insert(i);
	}
	void add_band(operating_band band) { bands_.insert(band); }
	void remove_band(operating_band band) { bands_.erase(band); }
	bool has_band(operating_band band) const { return bands_.find(band) != bands_.end(); }
	bool operator==(const operating_bands& s) const { return bands_ == s.bands_; }
	bool operator!=(const operating_bands& s) const { return bands_ != s.bands_; }
	operating_band get_first_band() const { return bands_.size() ? *bands_.begin() : OPERATING_BAND_UNKNOWN; }
	operating_band find_lte_band() const { return find_band(FIRST_LTE_OPERATING_BAND, LAST_LTE_OPERATING_BAND); }
	operating_band find_gsm_band() const { return find_band(FIRST_GSM_OPERATING_BAND, LAST_GSM_OPERATING_BAND); }
	operating_band find_umts_band() const { return find_band(FIRST_UMTS_OPERATING_BAND, LAST_UMTS_OPERATING_BAND); }
	operating_band find_band(operating_band begin, operating_band end) const {
		for(const auto& i : bands_) {
			if(i >= begin && i <= end)
				return i;
		}
		return OPERATING_BAND_UNKNOWN;
	}
	std::set<operating_band> bands_;
};

struct channel_freq
{
	channel_freq() : channel_(-1), freq_(-1), band_(OPERATING_BAND_UNKNOWN) {}
	channel_freq(channel_type c, frequency_type f, operating_band b)
		: channel_(c), freq_(f), band_(b) {}
	channel_freq& operator=(const channel_freq &cf) {
		channel_ = cf.channel_;
		freq_ = cf.freq_;
		band_ = cf.band_;
		return *this;
	}
	bool operator==(const channel_freq &cf) {
		return channel_ == cf.channel_ && freq_ == cf.freq_ && band_ == cf.band_;
	}
	bool is_valid() const { return channel_ != -1 && freq_ != -1 && band_ != OPERATING_BAND_UNKNOWN; }
	channel_type channel_;
	frequency_type freq_;
	operating_band band_;
};


}


