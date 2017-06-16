#pragma once

#include <regex>
#include <locale>
#include <chrono>
#include <type_traits>
#include "boost/date_time.hpp"
#include "boost/format.hpp"
#include "rf_phreaker/common/common_types.h"

#define khz(x) (static_cast<rf_phreaker::frequency_type>(x)*1000L)             /**< Convenience for kHz */
#define mhz(x) (static_cast<rf_phreaker::frequency_type>(x)*1000000L)          /**< Convenience for MHz */
#define ghz(x) (static_cast<rf_phreaker::frequency_type>(x)*1000000000L)       /**< Convenience for GHz */
#define milli_to_nano(x) (static_cast<rf_phreaker::time_type>(x)*1000000L)       /**< Convenience for nano */

namespace rf_phreaker {

//template<frequency_type N>
//struct khz_ {
//	enum { v = N * 1000 };
//};
//
//template<frequency_type N>
//struct mhz {
//	enum { v = N * 1000000 };
//};
//
//template<frequency_type N>
//struct hz {
//	enum { v = N * 1000000000 };
//};
//
//template<time_type N>
//struct nano
//{
//	enum {v = N * 1000000000};
//};
//
//template<time_type N>
//struct micro
//{
//	enum { v = N * 1000000 };
//};
//
//template<time_type N>
//struct milli
//{
//	enum { v = N * 1000 };
//};

inline bool is_little_endian() {
	uint16_t number = 0x1;
	auto *numPtr = (unsigned char*)&number;
	return (numPtr[0] == 1);
}

template<typename Data>
inline bool is_round_number(Data num, Data tolerance = 1) {
	return abs(num - std::floor(num)) < std::numeric_limits<Data>::epsilon() * tolerance;
}

template<typename Data>
inline bool is_approx_zero(Data num, Data tolerance = 1) {
	return abs(num) < std::numeric_limits<Data>::epsilon() * tolerance;
}

inline int16_t sign_extend_12_bits(int16_t &var) {
	if(var & 0x0800)
		var |= 0xF000;
	else
		var &= 0x0FFF;

	return var;
}

template<int nearest, typename num>
inline frequency_type round_to_nearest(num f) {
	return static_cast<frequency_type>(std::floor((f + (nearest / 2.0)) / nearest) * nearest);
}

inline int32_t largest_pow_of_2(uint32_t length) {
	int pos = 32;
	while(((length << (32 - pos)) & 0x80000000) == 0 && pos >= 0) {
		--pos;
	}
	return 1 << (pos - 1);
}

inline void copy_serial(const std::string &serial, char *s, size_t size) {
	memset(s, 0, size);
	memcpy(s, serial.c_str(), serial.size() > size ? size : serial.size());
}

template<typename Type>
typename Type add_mod(Type num, int mod) {
	if(num % mod)
		return num + (mod - (num % mod));
	else
		return num;
}

inline int convert_to_samples(time_type time_ns, frequency_type actual_sampling_rate_used) {
	return static_cast<int>(time_ns / 1e9 * actual_sampling_rate_used);
}

inline int convert_to_samples_and_mod_1024(time_type time_ns, frequency_type actual_sampling_rate_used) {
	return add_mod(static_cast<int>(time_ns / 1e9 * actual_sampling_rate_used), 0124);
}

inline time_type convert_to_time(int num_samples, frequency_type actual_sampling_rate_used) {
	return static_cast<time_type>(((double)num_samples / actual_sampling_rate_used) * 1e9);
}

inline std::vector<std::string> tokenize(const std::string& input, const std::regex& pattern) {
	if(input.empty())
		return std::vector<std::string>();
	// Passing -1 as the submatch index parameter performs splitting
	std::sregex_token_iterator first(input.begin(), input.end(), pattern, -1);
	std::sregex_token_iterator last;
	return std::vector<std::string>(first, last);
}

inline std::string split_file_name(const std::string& str) {
	size_t found;
	found = str.find_last_of("(/\\");
	return str.substr(found + 1);
}

inline std::string& trim_whitespace(std::string &s) {
	s.erase(std::remove_if(s.begin(), s.end(), [&](char ch) { return std::isspace<char>(ch, std::locale::classic()); }));
	return s;
}

inline std::string timestamp_string() {
	return std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
}

class static_timestamp
{
public:
	static std::string to_string();
	static void clear();
private:
	static std::string timestamp_;
};

inline std::string to_date_time_string(time_t t) {
	auto str = boost::posix_time::to_simple_string(boost::posix_time::from_time_t(t));
	boost::replace_all(str, " ", "__");
	boost::replace_all(str, ":", "_");
	return str;
}

inline std::string current_date_time_string() {
	return to_date_time_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
}

template<typename T> struct is_vector : public std::false_type {};
template<typename T, typename A>
struct is_vector<std::vector<T, A>> : public std::true_type{};

struct cout_redirect {
	cout_redirect(std::streambuf * new_buffer)
		: old(std::cout.rdbuf(new_buffer)) {}

	~cout_redirect() {
		std::cout.rdbuf(old);
	}

private:
	std::streambuf * old;
};

inline bool is_within_freq_paths(const std::vector<frequency_path> &paths, frequency_type f) {
	bool found_freq = false;
	for(auto path : paths) {
		// Increase range by a 1 mhz on each to account for when we jump from
		// one path to the next.
		if(f >= path.low_freq_ - mhz(1) && f <= path.high_freq_ + mhz(1)) {
			found_freq = true;
			break;
		}
	}
	return found_freq;
}

inline bool is_within_freq_paths(const std::vector<frequency_path> &paths, frequency_type start, frequency_type stop) {
	for(auto f = start; f <= stop; f += khz(100)) {
		if(!is_within_freq_paths(paths, f))
			return false;
	}
	return true;
}

inline std::string to_string(const operating_band &b) {
	std::string s;
	switch(b) {
	case GSM_T_380: //	380	380.2–389.8	390.2–399.8	dynamic
		s = "gsm_operating_band_t_380";
		break;
	case GSM_T_410: //	410	410.2–419.8	420.2–429.8	dynamic
		s = "gsm_operating_band_t_410";
		break;
	case GSM_450: //	450	450.6–457.6	460.6–467.6	259–293
		s = "gsm_operating_band_450";
		break;
	case GSM_480: //	480	479.0–486.0	489.0–496.0	306–340
		s = "gsm_operating_band_480";
		break;
	case GSM_710: //	710	698.2–716.2	728.2–746.2	dynamic
		s = "gsm_operating_band_710";
		break;
	case GSM_750: //	750	747.2–762.2	777.2–792.2	438–511
		s = "gsm_operating_band_750";
		break;
	case GSM_T_810: //	810	806.2–821.2	851.2–866.2	dynamic
		s = "gsm_operating_band_t_810";
		break;
	case GSM_850: //	850	824.2–849.2	869.2–894.2	128–251
		s = "gsm_operating_band_850";
		break;
	case GSM_P_900: //	900	890.0–915.0	935.0–960.0	1–124
		s = "gsm_operating_band_p_900";
		break;
	case GSM_E_900: //	900	880.0–915.0	925.0–960.0	975–1023: 0-124
		s = "gsm_operating_band_e_900";
		break;
	case GSM_R_900: //	900	876.0–915.0	921.0–960.0	955–1023: 0-124
		s = "gsm_operating_band_r_900";
		break;
	case GSM_ER_900: //	900	872.0–915.0	917.0–960.0	955–1023: 0-124
		s = "gsm_operating_band_er_900";
		break;
	case GSM_T_900: //	900	870.4–876.0	915.4–921.0	dynamic^
		s = "gsm_operating_band_t_900";
		break;
	case GSM_DCS_1800: //	1800	1:710.2–1:784.8	1:805.2–1:879.8	512–885
		s = "gsm_operating_band_dcs_1800";
		break;
	case GSM_PCS_1900: //	1900	1:850.2–1:909.8	1:930.2–1:989.8	512–810
		s = "gsm_operating_band_pcs_1900";
		break;
	case UMTS_OPERATING_BAND_1:	//  2100	IMT	1920 - 1980	2110 – 2170
		s = "umts_operating_band_1";
		break;
	case UMTS_OPERATING_BAND_2:	//  1900	PCS A-F	1850 – 1910	1930 – 1990
		s = "umts_operating_band_2";
		break;
	case UMTS_OPERATING_BAND_3:	//	1800	DCS	1710 – 1785	1805 – 1880
		s = "umts_operating_band_3";
		break;
	case UMTS_OPERATING_BAND_4:	//	1700	AWS A-F	1710 – 1755	2110 – 2155
		s = "umts_operating_band_4";
		break;
	case UMTS_OPERATING_BAND_5:	//	850	CLR	824 – 849	869 – 894
		s = "umts_operating_band_5";
		break;
	case UMTS_OPERATING_BAND_6:	//	800		830 – 840	875 – 885
		s = "umts_operating_band_6";
		break;
	case UMTS_OPERATING_BAND_7:	//	2600	IMT-E	2500 – 2570	2620 – 2690
		s = "umts_operating_band_7";
		break;
	case UMTS_OPERATING_BAND_8:	//	900	E-GSM	880 – 915	925 – 960
		s = "umts_operating_band_8";
		break;
	case UMTS_OPERATING_BAND_9:	//	1700		1749.9 – 1784.9	1844.9 – 1879.9
		s = "umts_operating_band_9";
		break;
	case UMTS_OPERATING_BAND_10:	//	1700	EAWS A-G	1710 – 1770	2110 – 2170
		s = "umts_operating_band_10";
		break;
	case UMTS_OPERATING_BAND_11:	//	1500	LPDC	1427.9 – 1447.9	1475.9 – 1495.9
		s = "umts_operating_band_11";
		break;
	case UMTS_OPERATING_BAND_12:	//	700	LSMH A/B/C	699 – 716	729 – 746
		s = "umts_operating_band_12";
		break;
	case UMTS_OPERATING_BAND_13:	//	700	USMH C	777 – 787	746 – 756
		s = "umts_operating_band_13";
		break;
	case UMTS_OPERATING_BAND_14:	//	700	USMH D	788 – 798	758 – 768
		s = "umts_operating_band_14";
		break;
	case UMTS_OPERATING_BAND_19:	//	800		832.4 – 842.6	877.4 – 887.6
		s = "umts_operating_band_19";
		break;
	case UMTS_OPERATING_BAND_20:	//	800	EUDD	832 – 862	791 – 821
		s = "umts_operating_band_20";
		break;
	case UMTS_OPERATING_BAND_21:	//	1500	UPDC	1447.9 – 1462.9	1495.9 – 1510.9
		s = "umts_operating_band_21";
		break;
	case UMTS_OPERATING_BAND_22:	//	3500		3410 – 3490	3510 – 3590
		s = "umts_operating_band_22";
		break;
	case UMTS_OPERATING_BAND_25:	//	1900	EPCS A-G	1850 – 1915	1930 – 1995
		s = "umts_operating_band_25";
		break;
	case UMTS_OPERATING_BAND_26:	//	850	ECLR	814 – 849	859 – 894
		s = "umts_operating_band_26";
		break;
	case LTE_OPERATING_BAND_1:	//	1920 - 1980	2110 - 2170	FDD
		s = "lte_operating_band_1";
		break;
	case LTE_OPERATING_BAND_2:	//	1850 - 1910	1930 - 1990	FDD
		s = "lte_operating_band_2";
		break;
	case LTE_OPERATING_BAND_3:	//	1710 - 1785	1805 - 1880	FDD
		s = "lte_operating_band_3";
		break;
	case LTE_OPERATING_BAND_4:	//	1710 - 1755	2110 - 2155	FDD
		s = "lte_operating_band_4";
		break;
	case LTE_OPERATING_BAND_5:	//	824 - 849	869 - 894	FDD
		s = "lte_operating_band_5";
		break;
	case LTE_OPERATING_BAND_6:	//	830 - 840	875 - 885	FDD
		s = "lte_operating_band_6";
		break;
	case LTE_OPERATING_BAND_7:	//	2500 - 2570	2620 - 2690	FDD
		s = "lte_operating_band_7";
		break;
	case LTE_OPERATING_BAND_8:	//	880 - 915	925 - 960	FDD
		s = "lte_operating_band_8";
		break;
	case LTE_OPERATING_BAND_9:	//	1749.9 - 1784.9	1844.9 - 1879.9	FDD
		s = "lte_operating_band_9";
		break;
	case LTE_OPERATING_BAND_10:	//	1710 - 1770	2110 - 2170	FDD
		s = "lte_operating_band_10";
		break;
	case LTE_OPERATING_BAND_11:	//	1427.9 - 1447.9	1475.9 - 1495.9	FDD
		s = "lte_operating_band_11";
		break;
	case LTE_OPERATING_BAND_12:	//	699 - 716	729 - 746	FDD
		s = "lte_operating_band_12";
		break;
	case LTE_OPERATING_BAND_13:	//	777 - 787	746 - 756	FDD
		s = "lte_operating_band_13";
		break;
	case LTE_OPERATING_BAND_14:	//	788 - 798	758 - 768	FDD
		s = "lte_operating_band_14";
		break;
	case LTE_OPERATING_BAND_17:	//	704 - 716	734 - 746	FDD
		s = "lte_operating_band_17";
		break;
	case LTE_OPERATING_BAND_18:	//	815 - 830	860 - 875	FDD
		s = "lte_operating_band_18";
		break;
	case LTE_OPERATING_BAND_19:	//	830 - 845	875 - 890	FDD
		s = "lte_operating_band_19";
		break;
	case LTE_OPERATING_BAND_20:	//	832 - 862	791 - 821	FDD
		s = "lte_operating_band_20";
		break;
	case LTE_OPERATING_BAND_21:	//	1447.9 - 1462.9	1495.9 - 1510.9	FDD
		s = "lte_operating_band_21";
		break;
	case LTE_OPERATING_BAND_22:	//	3410 - 3490	3510 - 3590	FDD
		s = "lte_operating_band_22";
		break;
	case LTE_OPERATING_BAND_23:	//	2000 - 2020	2180 - 2200	FDD
		s = "lte_operating_band_23";
		break;
	case LTE_OPERATING_BAND_24:	//	1626.5 - 1660.5	1525 - 1559	FDD
		s = "lte_operating_band_24";
		break;
	case LTE_OPERATING_BAND_25:	//	1850 - 1915	1930 - 1995	FDD
		s = "lte_operating_band_25";
		break;
	case LTE_OPERATING_BAND_26:	//	814 - 849	859 - 894	FDD
		s = "lte_operating_band_26";
		break;
	case LTE_OPERATING_BAND_27:	//	807 - 824	852 - 869	FDD
		s = "lte_operating_band_27";
		break;
	case LTE_OPERATING_BAND_28:	//	703 - 748	758 - 803	FDD
		s = "lte_operating_band_28";
		break;
	case LTE_OPERATING_BAND_29:	//	N/A	716 - 728	FDD
		s = "lte_operating_band_29";
		break;
	case LTE_OPERATING_BAND_30:	//	2305 - 2315	 2350 - 2360 FDD
		s = "lte_operating_band_30";
		break;
	case LTE_OPERATING_BAND_33:	//	1900 - 1920		TDD
		s = "lte_operating_band_33";
		break;
	case LTE_OPERATING_BAND_34:	//	2010 - 2025		TDD
		s = "lte_operating_band_34";
		break;
	case LTE_OPERATING_BAND_35:	//	1850 - 1910		TDD
		s = "lte_operating_band_35";
		break;
	case LTE_OPERATING_BAND_36:	//	1930 - 1990		TDD
		s = "lte_operating_band_36";
		break;
	case LTE_OPERATING_BAND_37:	//	1910 - 1930		TDD
		s = "lte_operating_band_37";
		break;
	case LTE_OPERATING_BAND_38:	//	2570 - 2620		TDD
		s = "lte_operating_band_38";
		break;
	case LTE_OPERATING_BAND_39:	//	1880 - 1920		TDD
		s = "lte_operating_band_39";
		break;
	case LTE_OPERATING_BAND_40:	//	2300 - 2400		TDD
		s = "lte_operating_band_40";
		break;
	case LTE_OPERATING_BAND_41:	//	2496 - 2690		TDD
		s = "lte_operating_band_41";
		break;
	case LTE_OPERATING_BAND_42:	//	3400 - 3600		TDD
		s = "lte_operating_band_42";
		break;
	case LTE_OPERATING_BAND_43:	//	3600 - 3800		TDD
		s = "lte_operating_band_43";
		break;
	case LTE_OPERATING_BAND_44:	//	703 - 803		TDD
		s = "lte_operating_band_44";
		break;
	case OPERATING_BAND_UNKNOWN:
	default:
		s = "unknown_operating_band";
	}
	return s;
}

class hex_conversion
{
public:
	//template<size_t Size>
	//static long convert_hex(const std::iterator &it)
	//{
	//	char tmp[Size];
	//	char *endptr;
	//	std::copy(it, it + Size, tmp);
	//	return strtol(tmp, &endptr, 16);
	//}
	template<size_t Size>
	static long convert_hex(const char* ptr)
	{
		char tmp[Size];
		char *endptr;
		std::copy(ptr, ptr + Size, tmp);
		return strtol(tmp, &endptr, 16);
	}

	// We accept the largest int possible then set the width accordingly to how bytes the user wants outputted.
	// This is done because with smaller integers (int8, etc) boost won't actually convert properly to hex.
	template<size_t Size>
	static std::string to_string(uint64_t value) {
		return std::move(str(boost::format("%x") % boost::io::group(std::setw(Size), std::setfill('0'), value)));
	}
};

template<typename Map> typename Map::const_iterator
	greatest_less(Map const& m, typename Map::key_type const& k) {
	typename Map::const_iterator it = m.lower_bound(k);
	if(it != m.begin()) {
		return --it;
	}
	return m.end();
}

template<typename Map> typename Map::iterator
	greatest_less(Map & m, typename Map::key_type const& k) {
	typename Map::iterator it = m.lower_bound(k);
	if(it != m.begin()) {
		return --it;
	}
	return m.end();
}

#if defined(WIN32)
inline int setenv(const char *name, const char *value, int overwrite) {
	int errcode = 0;
	if(!overwrite) {
		size_t envsize = 0;
		errcode = getenv_s(&envsize, NULL, 0, name);
		if(errcode || envsize) return errcode;
	}
	return _putenv_s(name, value);
}
#else
inline int setenv(const char *name, const char *value, int overwrite) {
	return setenv(name, value, overwrite);
}
#endif
}