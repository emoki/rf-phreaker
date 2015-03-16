#pragma once

#include "boost/math/tr1.hpp"
#include "rf_phreaker/common/operating_band_range_specifier.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/exception_types.h"
//#include "rf_phreaker/common/log.h"

namespace rf_phreaker
{

// TODO - Look into creating a class that encapsulates band and channel and freq.
class channel_conversion
{
public:
	channel_freq channel_to_frequency(channel_type c, specifier s) {
		switch(s) {
		case GSM_LAYER_3_DECODE:
		case GSM_SWEEP:
			return arfcn_to_frequency(c)[0];
		case UMTS_LAYER_3_DECODE:
		case UMTS_SWEEP:
			return uarfcn_to_frequency(c);
		case LTE_LAYER_3_DECODE:
		case LTE_SWEEP:
			return earfcn_to_frequency(c);
		default:
			throw misc_error("Error converting channel to freq. Specifier not correct (" + std::to_string((int)s) + ").");
		}
	}

	std::vector<channel_freq> arfcn_to_frequency(channel_type c) {
		std::vector<channel_freq> freqs;

		if(c >= 128 && c <= 251) { // gsm850 = 869.2 + .2(c-128)
			freqs.push_back({c, round_to_nearest<khz(100)>(mhz(869.2 + .2 * (c - 128))), GSM_850});
		}
		else if(c >= 0 && c <= 124) {
			frequency_type f = round_to_nearest<khz(100)>(mhz(935 + c * .2));
			freqs.push_back({c, f, GSM_E_900}); //e-gsm900 = 935 + c *.2
			freqs.push_back({c, f, GSM_R_900}); //r-gsm900 = 935 + c *.2
			if(c >= 1 && c <= 124)
				freqs.push_back({c, f, GSM_P_900}); // p-gsm900 = 935 + c*.2
		}
		else if(c >= 955 && c <= 1023) { // gsm 900
			frequency_type f = round_to_nearest<khz(100)>(mhz(935 + (c - 1024) * .2));
			freqs.push_back({c, f, GSM_R_900}); //r-gsm900 = 935 + c *.2
			if(c >= 975 && c <= 1023)
				freqs.push_back({c, f, GSM_E_900}); //e-gsm900 = 935 + c *.2
		}
		else if(c >= 512 && c <= 885) { // gsm 1800
			freqs.push_back({c, round_to_nearest<khz(100)>(mhz(1805.2 + (c - 512) * .2)), GSM_DCS_1800});
			if(c >= 512 && c <= 810)  // gsm 1900
				freqs.push_back({c, round_to_nearest<khz(100)>(mhz(1930.2 + (c - 512) * .2)), GSM_PCS_1900});
		}
		else if(c >= 259 && c <= 293) { // gsm 450
			freqs.push_back({c, round_to_nearest<khz(100)>(mhz(460.6 + (c - 259) * .2)), GSM_450});
		}
		else if(c >= 306 && c <= 340) { // gsm 480
			freqs.push_back({c, round_to_nearest<khz(100)>(mhz(489 + (c - 306) * .2)), GSM_480});
		}
		else if(c >= 438 && c <= 511) { // gsm 750
			freqs.push_back({c, round_to_nearest<khz(100)>(mhz(777.2 + (c - 438) * .2)), GSM_750});
		}
		else {
			//LOG(LVERBOSE) << "Unknown GSM channel.";
		}
		return freqs;
	}

	channel_freq uarfcn_to_frequency(channel_type c) {
		channel_freq cf;
		if(c >= 10562 && c <= 10838) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * c / 5.0)), UMTS_OPERATING_BAND_1};
		}
		else if(c >= 9662 && c <= 9938) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * c / 5.0)), UMTS_OPERATING_BAND_2};
		}
		else if(c >= 1162 && c <= 1513) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 1575))), UMTS_OPERATING_BAND_3};
		}
		else if(c >= 1537 && c <= 1738) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 1805) )), UMTS_OPERATING_BAND_4};
		}
		else if(c >= 4357 && c <= 4458) {
			cf = {c, round_to_nearest<khz(100.0)>(khz(1000 * c / 5.0)), UMTS_OPERATING_BAND_5};
		}
		else if(c >= 2237 && c <= 2563) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 2175))), UMTS_OPERATING_BAND_7};
		}
		else if(c >= 2937 && c <= 3088) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 340))), UMTS_OPERATING_BAND_8};
		}
		else if(c >= 9237 && c <= 9387) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * c / 5.0)), UMTS_OPERATING_BAND_9};
		}
		else if(c >= 3112 && c <= 3388) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 1490))), UMTS_OPERATING_BAND_10};
		}
		else if(c >= 3712 && c <= 3787) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 736))), UMTS_OPERATING_BAND_11};
		}
		else if(c >= 3842 && c <= 3902) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 - 37))), UMTS_OPERATING_BAND_12};
		}
		else if(c >= 4017 && c <= 4043) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 - 55))), UMTS_OPERATING_BAND_13};
		}
		else if(c >= 4117 && c <= 4143) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 - 63))), UMTS_OPERATING_BAND_14};
		}
		else if(c >= 712 && c <= 763) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 735))), UMTS_OPERATING_BAND_19};
		}
		else if(c >= 4512 && c <= 4638) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 - 109))), UMTS_OPERATING_BAND_20};
		}
		else if(c >= 862 && c <= 912) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 1326))), UMTS_OPERATING_BAND_21};
		}
		else if(c >= 5112 && c <= 5263) {
			cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 910))), UMTS_OPERATING_BAND_21};
		}
		else { // special cases
			switch(c) {
			case 412:
			case 437:
			case 462:
			case 487:
			case 512:
			case 537:
			case 562:
			case 587:
			case 612:
			case 637:
			case 662:
			case 687:
				cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.0 + 1850.1))), UMTS_OPERATING_BAND_2};
				break;
			case 1887:
			case 1912:
			case 1937:
			case 1962:
			case 1987:
			case 2012:
			case 2037:
			case 2062:
			case 2087:
				cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 1735.1))), UMTS_OPERATING_BAND_4};
				break;
			case 1007:
			case 1012:
			case 1032:
			case 1037:
			case 1062:
			case 1087:
				cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 670.1))), UMTS_OPERATING_BAND_5};
				break;

				// NO band 6

			case 2587:
			case 2612:
			case 2637:
			case 2662:
			case 2687:
			case 2712:
			case 2737:
			case 2762:
			case 2787:
			case 2812:
			case 2837:
			case 2862:
			case 2887:
			case 2912:
				cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 2105.1))), UMTS_OPERATING_BAND_7};
				break;
			case 3412:
			case 3437:
			case 3462:
			case 3487:
			case 3512:
			case 3537:
			case 3562:
			case 3587:
			case 3612:
			case 3637:
			case 3662:
			case 3687:
				cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 1430.1))), UMTS_OPERATING_BAND_10};
				break;
			case 3932:
			case 3957:
			case 3962:
			case 3987:
			case 3992:
				cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 - 54.9 ))), UMTS_OPERATING_BAND_12};
				break;
			case 4067:
			case 4092:
				cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 - 64.9))), UMTS_OPERATING_BAND_13};
				break;
			case 4167:
			case 4192:
				cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 - 72.9))), UMTS_OPERATING_BAND_14};
				break;
			case 787:
			case 812:
			case 837:
				cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 720.1))), UMTS_OPERATING_BAND_19};
				break;
			case 6292:
			case 6317:
			case 6342:
			case 6367:
			case 6392:
			case 6417:
			case 6442:
			case 6467:
			case 6492:
			case 6517:
			case 6542:
			case 6567:
			case 6592:
				cf = {c, round_to_nearest<khz(100)>(khz(1000 * (c / 5.00 + 674.1))), UMTS_OPERATING_BAND_25};
				break;
			default:
				//LOG(LVERBOSE) << "Unknown WCDMA channel.";
				cf = channel_freq(c, -1, OPERATING_BAND_UNKNOWN);
			}
		}
		return cf;
	}

	channel_freq earfcn_to_frequency(channel_type c) {
		channel_freq cf;
		if(c >= 0 && c < 600) {
			cf = earfcn_to_frequency(c, 0, LTE_OPERATING_BAND_1);
		}
		else if(c >= 600 && c < 1200) {
			cf = earfcn_to_frequency(c, 600, LTE_OPERATING_BAND_2);
		}
		else if(c >= 1200 && c < 1950) {
			cf = earfcn_to_frequency(c, 1200, LTE_OPERATING_BAND_3);
		}
		else if(c >= 1950 && c < 2400) {
			cf = earfcn_to_frequency(c, 1950, LTE_OPERATING_BAND_4);
		}
		else if(c >= 2400 && c < 2650) {
			cf = earfcn_to_frequency(c, 2400, LTE_OPERATING_BAND_5);
		}
		else if(c >= 2650 && c < 2750) {
			cf = earfcn_to_frequency(c, 2650, LTE_OPERATING_BAND_6);
		}
		else if(c >= 2750 && c < 3450) {
			cf = earfcn_to_frequency(c, 2750, LTE_OPERATING_BAND_7);
		}
		else if(c >= 3450 && c < 3800) {
			cf = earfcn_to_frequency(c, 3450, LTE_OPERATING_BAND_8);
		}
		else if(c >= 3800 && c < 4150) {
			cf = earfcn_to_frequency(c, 3800, LTE_OPERATING_BAND_9);
		}
		else if(c >= 4150 && c < 4750) {
			cf = earfcn_to_frequency(c, 4150, LTE_OPERATING_BAND_10);
		}
		else if(c >= 4750 && c < 5010) {
			cf = earfcn_to_frequency(c, 4750, LTE_OPERATING_BAND_11);
		}
		else if(c >= 5010 && c < 5180) {
			cf = earfcn_to_frequency(c, 5010, LTE_OPERATING_BAND_12);
		}
		else if(c >= 5180 && c < 5280) {
			cf = earfcn_to_frequency(c, 5180, LTE_OPERATING_BAND_13);
		}
		else if(c >= 5280 && c < 5380) {
			cf = earfcn_to_frequency(c, 5280, LTE_OPERATING_BAND_14);
		}
		else if(c >= 5730 && c < 5850) {
			cf = earfcn_to_frequency(c, 5730, LTE_OPERATING_BAND_17);
		}
		else if(c >= 5850 && c < 6000) {
			cf = earfcn_to_frequency(c, 5850, LTE_OPERATING_BAND_18);
		}
		else if(c >= 6000 && c < 6150) {
			cf = earfcn_to_frequency(c, 6000, LTE_OPERATING_BAND_19);
		}
		else if(c >= 6150 && c < 6450) {
			cf = earfcn_to_frequency(c, 6150, LTE_OPERATING_BAND_20);
		}
		else if(c >= 6450 && c < 6600) {
			cf = earfcn_to_frequency(c, 6450, LTE_OPERATING_BAND_21);
		}
		else if(c >= 6600 && c < 7400) {
			cf = earfcn_to_frequency(c, 6600, LTE_OPERATING_BAND_22);
		}
		else if(c >= 7500 && c < 7700) {
			cf = earfcn_to_frequency(c, 7500, LTE_OPERATING_BAND_23);
		}
		else if(c >= 7700 && c < 8040) {
			cf = earfcn_to_frequency(c, 7700, LTE_OPERATING_BAND_24);
		}
		else if(c >= 8040 && c < 8690) {
			cf = earfcn_to_frequency(c, 8040, LTE_OPERATING_BAND_25);
		}
		else if(c >= 8690 && c < 9040) {
			cf = earfcn_to_frequency(c, 8690, LTE_OPERATING_BAND_26);
		}
		else if(c >= 9040 && c < 9210) {
			cf = earfcn_to_frequency(c, 9040, LTE_OPERATING_BAND_27);
		}
		else if(c >= 9210 && c < 9660) {
			cf = earfcn_to_frequency(c, 9210, LTE_OPERATING_BAND_28);
		}
		else if(c >= 9660 && c < 9770) {
			cf = earfcn_to_frequency(c, 9660, LTE_OPERATING_BAND_29);
		}
		else if(c >= 36000 && c < 36200) {
			cf = earfcn_to_frequency(c, 36000, LTE_OPERATING_BAND_33);
		}
		else if(c >= 36200 && c < 36350) {
			cf = earfcn_to_frequency(c, 36200, LTE_OPERATING_BAND_34);
		}
		else if(c >= 36350 && c < 36950) {
			cf = earfcn_to_frequency(c, 36350, LTE_OPERATING_BAND_35);
		}
		else if(c >= 36950 && c < 37550) {
			cf = earfcn_to_frequency(c, 36950, LTE_OPERATING_BAND_36);
		}
		else if(c >= 37550 && c < 37750) {
			cf = earfcn_to_frequency(c, 37550, LTE_OPERATING_BAND_37);
		}
		else if(c >= 37750 && c < 38250) {
			cf = earfcn_to_frequency(c, 37750, LTE_OPERATING_BAND_38);
		}
		else if(c >= 38250 && c < 38650) {
			cf = earfcn_to_frequency(c, 38250, LTE_OPERATING_BAND_39);
		}
		else if(c >= 38650 && c < 39650) {
			cf = earfcn_to_frequency(c, 38650, LTE_OPERATING_BAND_40);
		}
		else if(c >= 39650 && c < 41590) {
			cf = earfcn_to_frequency(c, 39650, LTE_OPERATING_BAND_41);
		}
		else if(c >= 41590 && c < 43590) {
			cf = earfcn_to_frequency(c, 41590, LTE_OPERATING_BAND_42);
		}
		else if(c >= 43590 && c < 45590) {
			cf = earfcn_to_frequency(c, 43590, LTE_OPERATING_BAND_43);
		}
		else if(c >= 45590 && c < 46590) {
			cf = earfcn_to_frequency(c, 45590, LTE_OPERATING_BAND_44);
		}
		else
			cf = channel_freq(c, -1, OPERATING_BAND_UNKNOWN);
		return cf;
	}

	channel_freq earfcn_to_frequency(channel_type c, channel_type offset, operating_band band) {
		auto r = ranges_.get_band_freq_range(band);
		// F DL = F DL_low + 0.1(N DL – N Offs - DL)
		return channel_freq(c, round_to_nearest<khz(100)>(((c - offset) * 100000 + r.low_freq_hz_)), band);
	}

	channel_freq frequency_to_channel(frequency_type freq, operating_band band) {
		if(band >= FIRST_GSM_OPERATING_BAND && band <= LAST_GSM_OPERATING_BAND)
			return frequency_to_arfcn(freq, band);
		else if(band >= FIRST_UMTS_OPERATING_BAND && band <= LAST_UMTS_OPERATING_BAND)
			return frequency_to_uarfcn(freq, band);
		else if(band >= FIRST_LTE_OPERATING_BAND && band <= LAST_LTE_OPERATING_BAND)
			return frequency_to_earfcn(freq, band);
		else
			throw misc_error("Error converting frequency to channel. Unknown operating band (" + std::to_string((int)band) + ").", CONVERSION_ERROR);
	}

	channel_freq frequency_to_arfcn(frequency_type /*freq*/, operating_band /*band*/) {
		channel_freq cf;
		throw misc_error("Converting ARFCN is not supported.", CONVERSION_ERROR);
		return cf;
	}

	channel_freq frequency_to_uarfcn(frequency_type freq, operating_band band) {
		// 3gpp ts 25.101 5.4.3
		channel_freq cf(-1, freq, band);

		if(!check_umts_freq(freq, band))
			return cf;

		switch(band) {
		case UMTS_OPERATING_BAND_1:	//  2100	IMT	1920 - 1980	2110 – 2170
			cf.channel_ = calc_uarfcn(freq, 0);
			break;
		case UMTS_OPERATING_BAND_2:	//  1900	PCS A-F	1850 – 1910	1930 – 1990
			cf.channel_ = calc_uarfcn(freq, freq % khz(200) == 0 ? 0 : khz(1850100));
			break;
		case UMTS_OPERATING_BAND_3:	//	1800	DCS	1710 – 1785	1805 – 1880
			cf.channel_ = calc_uarfcn(freq, mhz(1575));
			break;
		case UMTS_OPERATING_BAND_4:	//	1700	AWS A-F	1710 – 1755	2110 – 2155
			cf.channel_ = calc_uarfcn(freq, freq % khz(200) == 0 ? mhz(1805) : khz(1735100));
			break;
		case UMTS_OPERATING_BAND_5:	//	850	CLR	824 – 849	869 – 894
			cf.channel_ = calc_uarfcn(freq, freq % khz(200) == 0 ? 0 : khz(670100));
			break;
		case UMTS_OPERATING_BAND_6:	//	800		830 – 840	875 – 885
			cf.channel_ = calc_uarfcn(freq, freq % khz(200) == 0 ? 0 : khz(670100));
			break;
		case UMTS_OPERATING_BAND_7:	//	2600	IMT-E	2500 – 2570	2620 – 2690
			cf.channel_ = calc_uarfcn(freq, freq % khz(200) == 0 ? mhz(2175) : 2105100000LL);
			break;
		case UMTS_OPERATING_BAND_8:	//	900	E-GSM	880 – 915	925 – 960
			cf.channel_ = calc_uarfcn(freq, mhz(340));
			break;
		case UMTS_OPERATING_BAND_9:	//	1700		1749.9 – 1784.9	1844.9 – 1879.9
			cf.channel_ = calc_uarfcn(freq, 0);
			break;
		case UMTS_OPERATING_BAND_10:	//	1700	EAWS A-G	1710 – 1770	2110 – 2170
			cf.channel_ = calc_uarfcn(freq, freq %  khz(200) == 0 ? mhz(1490) : khz(1430100));
			break;
		case UMTS_OPERATING_BAND_11:	//	1500	LPDC	1427.9 – 1447.9	1475.9 – 1495.9
			cf.channel_ = calc_uarfcn(freq, mhz(736));
			break;
		case UMTS_OPERATING_BAND_12:	//	700	LSMH A/B/C	699 – 716	729 – 746
			cf.channel_ = calc_uarfcn(freq, freq %  khz(200) == 0 ? mhz(-37) : khz(-54900));
			break;
		case UMTS_OPERATING_BAND_13:	//	700	USMH C	777 – 787	746 – 756
			cf.channel_ = calc_uarfcn(freq, freq %  khz(200) == 0 ? mhz(-55) : khz(-64900));
			break;
		case UMTS_OPERATING_BAND_14:	//	700	USMH D	788 – 798	758 – 768
			cf.channel_ = calc_uarfcn(freq, freq %  khz(200) == 0 ? mhz(-63) : khz(-72900));
			break;
		case UMTS_OPERATING_BAND_19:	//	800		832.4 – 842.6	877.4 – 887.6
			cf.channel_ = calc_uarfcn(freq, freq %  khz(200) == 0 ? mhz(735) : khz(720100));
			break;
		case UMTS_OPERATING_BAND_20:	//	800	EUDD	832 – 862	791 – 821
			cf.channel_ = calc_uarfcn(freq, mhz(-109));
			break;
		case UMTS_OPERATING_BAND_21:	//	1500	UPDC	1447.9 – 1462.9	1495.9 – 1510.9
			cf.channel_ = calc_uarfcn(freq, mhz(1326));
			break;
		case UMTS_OPERATING_BAND_25:	//	1900	EPCS A-G	1850 – 1915	1930 – 1995
			cf.channel_ = calc_uarfcn(freq, freq % khz(200) == 0 ? mhz(910) : khz(674100));
			break;

		case UMTS_OPERATING_BAND_26:    //	850	ECLR	814 – 849	859 – 894
		case UMTS_OPERATING_BAND_22:	//	3500		3410 – 3490	3510 – 3590
		default:
			;//LOG(LVERBOSE) << "Error converting to UARFCN.  Frequency and band are not supported.";
		}

		return cf;
	}

	bool check_umts_freq(frequency_type freq, operating_band band) {
		// Refactor this incredibly ugly if statement.
		bool valid  = false;
		auto r = ranges_.get_band_freq_range(band);
		if(freq < r.low_freq_hz_ || freq > r.high_freq_hz_) {
			//LOG(LVERBOSE) << "Error converting to UARFCN.  Frequency (" + std::to_string(freq) +
			//") out of range for specified band (" + std::to_string((int)band) + ".";
		}
		else if(freq % khz(200) == 0) {
			valid = true;
			//LOG(LVERBOSE) << "Error converting to UARFCN.  Frequency (" + std::to_string(freq) + ") is not a valid channel.";
		}
		else if(freq % khz(500) == 0) {
			// Check specific freqs.
			switch(band) {
			case UMTS_OPERATING_BAND_2:
				switch(freq) {
				case khz(1932500):
				case khz(1937500):
				case khz(1942500):
				case khz(1947500):
				case khz(1952500):
				case khz(1957500):
				case khz(1962500):
				case khz(1967500):
				case khz(1972500):
				case khz(1977500):
				case khz(1982500):
				case khz(1987500):
					valid = true; break;
				default:
					;
				}
				break;

			case UMTS_OPERATING_BAND_4:
				switch(freq) {
				case khz(2112500):
				case khz(2117500):
				case khz(2122500):
				case khz(2127500):
				case khz(2132500):
				case khz(2137500):
				case khz(2142500):
				case khz(2147500):
				case khz(2152500):
					valid = true; break;
				default:
					;
				}
				break;

			case UMTS_OPERATING_BAND_5:
				switch(freq) {
				case khz(871500):
				case khz(872500):
				case khz(876500):
				case khz(877500):
				case khz(882500):
				case khz(887500):
					valid = true; break;
				default:
					;
				}
				break;

			case UMTS_OPERATING_BAND_6:
				switch(freq) {
				case khz(877500):
				case khz(882500):
					valid = true; break;
				default:
					;
				}
				break;

			case UMTS_OPERATING_BAND_7:
				switch(freq) {
				case khz(2622500):
				case khz(2627500):
				case khz(2632500):
				case khz(2637500):
				case khz(2642500):
				case khz(2647500):
				case khz(2652500):
				case khz(2657500):
				case khz(2662500):
				case khz(2667500):
				case khz(2672500):
				case khz(2677500):
				case khz(2682500):
				case khz(2687500):
					valid = true; break;
				default:
					;
				}
				break;

			case UMTS_OPERATING_BAND_10:
				switch(freq) {
				case khz(2112500):
				case khz(2117500):
				case khz(2122500):
				case khz(2127500):
				case khz(2132500):
				case khz(2137500):
				case khz(2142500):
				case khz(2147500):
				case khz(2152500):
				case khz(2157500):
				case khz(2162500):
				case khz(2167500):
					valid = true; break;
				default:
					;
				}
				break;

			case UMTS_OPERATING_BAND_12:
				switch(freq) {
				case khz(731500):
				case khz(736500):
				case khz(737500):
				case khz(742500):
				case khz(743500):
					valid = true; break;
				default:
					;
				}
				break;

			case UMTS_OPERATING_BAND_13:
				switch(freq) {
				case khz(748500):
				case khz(753500):
					valid = true; break;
				default:
					;
				}
				break;

			case UMTS_OPERATING_BAND_14:
				switch(freq) {
				case khz(760500):
				case khz(765500):
					valid = true; break;
				default:
					;
				}
				break;

			case UMTS_OPERATING_BAND_19:
				switch(freq) {
				case khz(877500):
				case khz(882500):
				case khz(887500):
					valid = true; break;
				default:
					;
				}
				break;

			case UMTS_OPERATING_BAND_25:
				switch(freq) {
				case khz(1932500):
				case khz(1937500):
				case khz(1942500):
				case khz(1947500):
				case khz(1952500):
				case khz(1957500):
				case khz(1962500):
				case khz(1967500):
				case khz(1972500):
				case khz(1977500):
				case khz(1982500):
				case khz(1987500):
				case khz(1992500):
					valid = true; break;
				default:
					;
				}
				break;

			default:;
			}
		}
		else
			valid = true;

		return valid;
	}

	channel_type calc_uarfcn(frequency_type freq, frequency_type offset) {
		return (channel_type)boost::math::tr1::round((freq - offset) / 1e6 * 5);
	}

	channel_freq frequency_to_earfcn(frequency_type freq, operating_band band) {
		channel_freq cf;
		cf.band_ = band;
		cf.freq_ = freq;

		if(freq % khz(100) != 0) {
			//LOG(LVERBOSE) << "Error converting to EARFCN.  Frequency (" + std::to_string(freq) + ") is not a valid channel.";
			cf.channel_ = -1;
			cf.band_ = OPERATING_BAND_UNKNOWN;
			return cf;
		}

		switch(band) {
		case LTE_OPERATING_BAND_1:
			cf.channel_ = calc_earfcn(freq, band, 0);
			break;
		case LTE_OPERATING_BAND_2:
			cf.channel_ = calc_earfcn(freq, band, 600);
			break;
		case LTE_OPERATING_BAND_3:
			cf.channel_ = calc_earfcn(freq, band, 1200);
			break;
		case LTE_OPERATING_BAND_4:
			cf.channel_ = calc_earfcn(freq, band, 1950);
			break;
		case LTE_OPERATING_BAND_5:
			cf.channel_ = calc_earfcn(freq, band, 2400);
			break;
		case LTE_OPERATING_BAND_6:
			cf.channel_ = calc_earfcn(freq, band, 2650);
			break;
		case LTE_OPERATING_BAND_7:
			cf.channel_ = calc_earfcn(freq, band, 2750);
			break;
		case LTE_OPERATING_BAND_8:
			cf.channel_ = calc_earfcn(freq, band, 3450);
			break;
		case LTE_OPERATING_BAND_9:
			cf.channel_ = calc_earfcn(freq, band, 3800);
			break;
		case LTE_OPERATING_BAND_10:
			cf.channel_ = calc_earfcn(freq, band, 4150);
			break;
		case LTE_OPERATING_BAND_11:
			cf.channel_ = calc_earfcn(freq, band, 4750);
			break;
		case LTE_OPERATING_BAND_12:
			cf.channel_ = calc_earfcn(freq, band, 5010);
			break;
		case LTE_OPERATING_BAND_13:
			cf.channel_ = calc_earfcn(freq, band, 5180);
			break;
		case LTE_OPERATING_BAND_14:
			cf.channel_ = calc_earfcn(freq, band, 5280);
			break;
		case LTE_OPERATING_BAND_17:
			cf.channel_ = calc_earfcn(freq, band, 5730);
			break;
		case LTE_OPERATING_BAND_18:
			cf.channel_ = calc_earfcn(freq, band, 5850);
			break;
		case LTE_OPERATING_BAND_19:
			cf.channel_ = calc_earfcn(freq, band, 6000);
			break;
		case LTE_OPERATING_BAND_20:
			cf.channel_ = calc_earfcn(freq, band, 6150);
			break;
		case LTE_OPERATING_BAND_21:
			cf.channel_ = calc_earfcn(freq, band, 6450);
			break;
		case LTE_OPERATING_BAND_22:
			cf.channel_ = calc_earfcn(freq, band, 6600);
			break;
		case LTE_OPERATING_BAND_23:
			cf.channel_ = calc_earfcn(freq, band, 7500);
			break;
		case LTE_OPERATING_BAND_24:
			cf.channel_ = calc_earfcn(freq, band, 7700);
			break;
		case LTE_OPERATING_BAND_25:
			cf.channel_ = calc_earfcn(freq, band, 8040);
			break;
		case LTE_OPERATING_BAND_26:
			cf.channel_ = calc_earfcn(freq, band, 8690);
			break;
		case LTE_OPERATING_BAND_27:
			cf.channel_ = calc_earfcn(freq, band, 9040);
			break;
		case LTE_OPERATING_BAND_28:
			cf.channel_ = calc_earfcn(freq, band, 9210);
			break;
		case LTE_OPERATING_BAND_29:
			cf.channel_ = calc_earfcn(freq, band, 9660);
			break;
		case LTE_OPERATING_BAND_33:
			cf.channel_ = calc_earfcn(freq, band, 36000);
			break;
		case LTE_OPERATING_BAND_34:
			cf.channel_ = calc_earfcn(freq, band, 36200);
			break;
		case LTE_OPERATING_BAND_35:
			cf.channel_ = calc_earfcn(freq, band, 36350);
			break;
		case LTE_OPERATING_BAND_36:
			cf.channel_ = calc_earfcn(freq, band, 36950);
			break;
		case LTE_OPERATING_BAND_37:
			cf.channel_ = calc_earfcn(freq, band, 37550);
			break;
		case LTE_OPERATING_BAND_38:
			cf.channel_ = calc_earfcn(freq, band, 37750);
			break;
		case LTE_OPERATING_BAND_39:
			cf.channel_ = calc_earfcn(freq, band, 38250);
			break;
		case LTE_OPERATING_BAND_40:
			cf.channel_ = calc_earfcn(freq, band, 38650);
			break;
		case LTE_OPERATING_BAND_41:
			cf.channel_ = calc_earfcn(freq, band, 39650);
			break;
		case LTE_OPERATING_BAND_42:
			cf.channel_ = calc_earfcn(freq, band, 41590);
			break;
		case LTE_OPERATING_BAND_43:
			cf.channel_ = calc_earfcn(freq, band, 43590);
			break;
		case LTE_OPERATING_BAND_44:
			cf.channel_ = calc_earfcn(freq, band, 45590);
			break;
		default:
			cf.channel_ = -1;
			cf.band_ = OPERATING_BAND_UNKNOWN;
			//LOG(LVERBOSE) << "Error converting to EARFCN.  Frequency and band are not supported.";
		}
		return cf;
	}

	channel_type calc_earfcn(frequency_type freq, operating_band band, frequency_type n_offset) {
		// 3gpp36.101 - 5.7.3
		// Fdl = Fdl_low + 0.1(Ndl - Noffset)
		// It doesn't appear the channel range is inclusive on the upper bound.  For example there is no
		// channel 600 / freq 2170mhz in band 1
		auto r = ranges_.get_band_freq_range(band);
		return static_cast<channel_type>(boost::math::tr1::round((freq - r.low_freq_hz_) / 1e5) + n_offset);
	}

	operating_band_range_specifier ranges_;
};


}
