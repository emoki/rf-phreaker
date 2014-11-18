#pragma once

#include "rf_phreaker/common/operating_band_range_specifier.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/exception_types.h"
#include "boost/math/tr1.hpp"

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
		else
			throw misc_error("Unknown GSM channel.", CONVERSION_ERROR);
		return freqs;
	}
	
	channel_freq uarfcn_to_frequency(channel_type c) {
		channel_freq f;
		if(c >= 10562 && c <= 10838) {
			f = {c, round_to_nearest<khz(100)>(mhz(c / 5)), UMTS_OPERATING_BAND_1};
		}
		else if(c >= 9662 && c <= 9938) {
			f = {c, round_to_nearest<khz(100)>(mhz(c / 5)), UMTS_OPERATING_BAND_2};
		}
		else if(c >= 1162 && c <= 1513) {
			f = {c, round_to_nearest<khz(100)>(mhz((c - 1875) / 5)), UMTS_OPERATING_BAND_3};
		}
		else if(c >= 1537 && c <= 1738) {
			f = {c, round_to_nearest<khz(100)>(mhz((c - 1805) / 5)), UMTS_OPERATING_BAND_4};
		}
		else if(c >= 4357 && c <= 4458) {
			f = {c, round_to_nearest<khz(100)>(mhz((c) / 5)), UMTS_OPERATING_BAND_5};
		}
		else if(c >= 2237 && c <= 2563) {
			f = {c, round_to_nearest<khz(100)>(mhz((c - 2175) / 5)), UMTS_OPERATING_BAND_7};
		}
		else if(c >= 2937 && c <= 3088) {
			f = {c, round_to_nearest<khz(100)>(mhz((c - 340) / 5)), UMTS_OPERATING_BAND_8};
		}
		else if(c >= 9237 && c <= 9387) {
			f = {c, round_to_nearest<khz(100)>(mhz((c) / 5)), UMTS_OPERATING_BAND_9};
		}
		else if(c >= 3112 && c <= 3388) {
			f = {c, round_to_nearest<khz(100)>(mhz((c - 1490) / 5)), UMTS_OPERATING_BAND_10};
		}
		else if(c >= 3712 && c <= 3787) {
			f = {c, round_to_nearest<khz(100)>(mhz((c - 736) / 5)), UMTS_OPERATING_BAND_11};
		}
		else if(c >= 3842 && c <= 3902) {
			f = {c, round_to_nearest<khz(100)>(mhz((c + 37) / 5)), UMTS_OPERATING_BAND_12};
		}
		else if(c >= 4017 && c <= 4043) {
			f = {c, round_to_nearest<khz(100)>(mhz((c + 55) / 5)), UMTS_OPERATING_BAND_13};
		}
		else if(c >= 4117 && c <= 4143) {
			f = {c, round_to_nearest<khz(100)>(mhz((c + 63) / 5)), UMTS_OPERATING_BAND_14};
		}
		else if(c >= 712 && c <= 763) {
			f = {c, round_to_nearest<khz(100)>(mhz((c - 735) / 5)), UMTS_OPERATING_BAND_19};
		}
		else if(c >= 4512 && c <= 4638) {
			f = {c, round_to_nearest<khz(100)>(mhz((c + 109) / 5)), UMTS_OPERATING_BAND_20};
		}
		else if(c >= 862 && c <= 912) {
			f = {c, round_to_nearest<khz(100)>(mhz((c - 1326) / 5)), UMTS_OPERATING_BAND_21};
		}
		else if(c >= 5112 && c <= 5263) {
			f = {c, round_to_nearest<khz(100)>(mhz((c - 910) / 5)), UMTS_OPERATING_BAND_21};
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
				f = {c, round_to_nearest<khz(100)>(mhz((c - 1850.1) / 5)), UMTS_OPERATING_BAND_2};
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
				f = {c, round_to_nearest<khz(100)>(mhz((c - 1735.1) / 5)), UMTS_OPERATING_BAND_4};
				break;
			case 1007:
			case 1012:
			case 1032:
			case 1037:
			case 1062:
			case 1087:
				f = {c, round_to_nearest<khz(100)>(mhz((c - 670.1) / 5)), UMTS_OPERATING_BAND_5};
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
				f = {c, round_to_nearest<khz(100)>(mhz((c - 2105.1) / 5)), UMTS_OPERATING_BAND_7};
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
				f = {c, round_to_nearest<khz(100)>(mhz((c - 1430.1) / 5)), UMTS_OPERATING_BAND_10};
				break;
			case 3932:
			case 3957:
			case 3962:
			case 3987:
			case 3992:
				f = {c, round_to_nearest<khz(100)>(mhz((c + 54.9 ) / 5)), UMTS_OPERATING_BAND_12};
				break;
			case 4067:
			case 4092:
				f = {c, round_to_nearest<khz(100)>(mhz((c + 64.9) / 5)), UMTS_OPERATING_BAND_13};
				break;
			case 4167:
			case 4192:
				f = {c, round_to_nearest<khz(100)>(mhz((c + 72.9) / 5)), UMTS_OPERATING_BAND_14};
				break;
			case 787:
			case 812:
			case 837:
				f = {c, round_to_nearest<khz(100)>(mhz((c - 720.1) / 5)), UMTS_OPERATING_BAND_19};
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
				f = {c, round_to_nearest<khz(100)>(mhz((c - 674.1) / 5)), UMTS_OPERATING_BAND_25};
				break;
			default:
				throw misc_error("Unknown WCDMA channel.", CONVERSION_ERROR);
			}
		}
		return f;
	}
	
	channel_freq earfcn_to_frequency(channel_type c) {
		channel_freq f;
		if(c >= 0 && c < 600) {
			auto r = ranges_.get_band_freq_range(LTE_OPERATING_BAND_1);
			f = {c, round_to_nearest<khz(100)>(c - 0) + r.low_freq_hz_, LTE_OPERATING_BAND_1};
		}
		if(c >= 600 && c < 1200) {
			f = earfcn_to_frequency(c, 600, LTE_OPERATING_BAND_2);
		}
		if(c >= 1200 && c < 1950) {
			f = earfcn_to_frequency(c, 1200, LTE_OPERATING_BAND_3);
		}
		if(c >= 1950 && c < 2400) {
			f = earfcn_to_frequency(c, 1950, LTE_OPERATING_BAND_4);
		}
		if(c >= 2400 && c < 2650) {
			f = earfcn_to_frequency(c, 2400, LTE_OPERATING_BAND_5);
		}
		if(c >= 2650 && c < 2750) {
			f = earfcn_to_frequency(c, 2650, LTE_OPERATING_BAND_6);
		}
		if(c >= 2750 && c < 3450) {
			f = earfcn_to_frequency(c, 2750, LTE_OPERATING_BAND_7);
		}
		if(c >= 3450 && c < 3800) {
			f = earfcn_to_frequency(c, 3450, LTE_OPERATING_BAND_8);
		}
		if(c >= 3800 && c < 4150) {
			f = earfcn_to_frequency(c, 3800, LTE_OPERATING_BAND_9);
		}
		if(c >= 4150 && c < 4750) {
			f = earfcn_to_frequency(c, 4150, LTE_OPERATING_BAND_10);
		}
		if(c >= 4750 && c < 5010) {
			f = earfcn_to_frequency(c, 4750, LTE_OPERATING_BAND_11);
		}
		if(c >= 5010 && c < 5180) {
			f = earfcn_to_frequency(c, 5010, LTE_OPERATING_BAND_12);
		}
		if(c >= 5180 && c < 5280) {
			f = earfcn_to_frequency(c, 5180, LTE_OPERATING_BAND_13);
		}
		if(c >= 5280 && c < 5340) {
			f = earfcn_to_frequency(c, 5280, LTE_OPERATING_BAND_14);
		}
		if(c >= 5730 && c < 5850) {
			f = earfcn_to_frequency(c, 5730, LTE_OPERATING_BAND_17);
		}
		if(c >= 5850 && c < 6000) {
			f = {c, round_to_nearest<khz(100)>(c - 5850), LTE_OPERATING_BAND_18};
		}
		if(c >= 6000 && c < 6150) {
			f = earfcn_to_frequency(c, 6000, LTE_OPERATING_BAND_19);
		}
		if(c >= 6150 && c < 6450) {
			f = earfcn_to_frequency(c, 6150, LTE_OPERATING_BAND_20);
		}
		if(c >= 6450 && c < 7500) {
			f = earfcn_to_frequency(c, 6450, LTE_OPERATING_BAND_21);
		}
		if(c >= 7500 && c < 7700) {
			f = earfcn_to_frequency(c, 7500, LTE_OPERATING_BAND_23);
		}
		if(c >= 7700 && c < 8040) {
			f = earfcn_to_frequency(c, 7700, LTE_OPERATING_BAND_24);
		}
		if(c >= 8040 && c < 8690) {
			f = earfcn_to_frequency(c, 8040, LTE_OPERATING_BAND_25);
		}
		if(c >= 36000 && c < 36200) {
			f = earfcn_to_frequency(c, 36000, LTE_OPERATING_BAND_33);
		}
		if(c >= 36200 && c < 36350) {
			f = earfcn_to_frequency(c, 36200, LTE_OPERATING_BAND_34);
		}
		if(c >= 36350 && c < 36950) {
			f = earfcn_to_frequency(c, 36350, LTE_OPERATING_BAND_35);
		}
		if(c >= 36950 && c < 37550) {
			f = earfcn_to_frequency(c, 36950, LTE_OPERATING_BAND_36);
		}
		if(c >= 37550 && c < 37750) {
			f = earfcn_to_frequency(c, 37550, LTE_OPERATING_BAND_37);
		}
		if(c >= 37750 && c < 38250) {
			f = earfcn_to_frequency(c, 37750, LTE_OPERATING_BAND_38);
		}
		if(c >= 38250 && c < 38650) {
			f = earfcn_to_frequency(c, 38250, LTE_OPERATING_BAND_39);
		}
		if(c >= 38650 && c < 39650) {
			f = earfcn_to_frequency(c, 38650, LTE_OPERATING_BAND_40);
		}
		if(c >= 39650 && c < 41590) {
			f = earfcn_to_frequency(c, 39650, LTE_OPERATING_BAND_41);
		}
		if(c >= 41590 && c < 43590) {
			f = earfcn_to_frequency(c, 41590, LTE_OPERATING_BAND_42);
		}
		if(c >= 43590 && c < 45590) {
			f = earfcn_to_frequency(c, 43590, LTE_OPERATING_BAND_43);
		}
		if(c >= 45590 && c < 46590) {
			f = earfcn_to_frequency(c, 45590, LTE_OPERATING_BAND_44);
		}
		return f;
	}
	
	channel_freq earfcn_to_frequency(channel_type c, channel_type offset, operating_band band) {
		auto r = ranges_.get_band_freq_range(band);
		return {c, round_to_nearest<khz(100)>(c - offset), band};
	}

	channel_type frequency_to_channel(frequency_type freq, operating_band band) {
		if(band >= FIRST_GSM_OPERATING_BAND && band <= LAST_GSM_OPERATING_BAND)
			return frequency_to_arfcn(freq, band);
		else if(band >= FIRST_UMTS_OPERATING_BAND && band <= LAST_UMTS_OPERATING_BAND)
			return frequency_to_uarfcn(freq, band);
		else if(band >= FIRST_LTE_OPERATING_BAND && band <= LAST_LTE_OPERATING_BAND)
			return frequency_to_earfcn(freq, band);
		else
			throw misc_error("Error converting frequency to channel. Unknown operating band (" + std::to_string((int)band) + ").", CONVERSION_ERROR);
	}

	channel_type frequency_to_arfcn(frequency_type freq, operating_band band) {
		channel_type channel;
		throw misc_error("Converting ARFCN is not supported.", CONVERSION_ERROR);
		return channel;
	}

	// 3gpp ts 25.101 5.4.3
	channel_type frequency_to_uarfcn(frequency_type freq, operating_band band) {
		if(freq % khz(200) != 0 && freq % khz(500) != 0)
			throw misc_error("Error converting to UARFCN.  Frequency (" + std::to_string(freq) + ") is not a valid channel.", CONVERSION_ERROR);

		check_umts_freq(freq, band);

		channel_type channel;
		switch(band) {
		case UMTS_OPERATING_BAND_1:	//  2100	IMT	1920 - 1980	2110 – 2170
			channel = calc_uarfcn(freq, 0);
			break;
		case UMTS_OPERATING_BAND_2:	//  1900	PCS A-F	1850 – 1910	1930 – 1990
			channel = calc_uarfcn(freq, freq % khz(200) == 0 ? 0 : khz(1850100));
			break;
		case UMTS_OPERATING_BAND_3:	//	1800	DCS	1710 – 1785	1805 – 1880
			channel = calc_uarfcn(freq, mhz(1575));
			break;
		case UMTS_OPERATING_BAND_4:	//	1700	AWS A-F	1710 – 1755	2110 – 2155			
			channel = calc_uarfcn(freq, freq % khz(200) == 0 ? mhz(1805) : khz(1735100));
			break;
		case UMTS_OPERATING_BAND_5:	//	850	CLR	824 – 849	869 – 894		
			channel = calc_uarfcn(freq, freq % khz(200) == 0 ? 0 : khz(670100));
			break;
		case UMTS_OPERATING_BAND_6:	//	800		830 – 840	875 – 885				
			channel = calc_uarfcn(freq, freq % khz(200) == 0 ? 0 : khz(670100));
			break;
		case UMTS_OPERATING_BAND_7:	//	2600	IMT-E	2500 – 2570	2620 – 2690
			channel = calc_uarfcn(freq, freq % khz(200) == 0 ? mhz(2175) : khz(2105100));
			break;
		case UMTS_OPERATING_BAND_8:	//	900	E-GSM	880 – 915	925 – 960
			channel = calc_uarfcn(freq, mhz(340));
			break;
		case UMTS_OPERATING_BAND_9:	//	1700		1749.9 – 1784.9	1844.9 – 1879.9
			channel = calc_uarfcn(freq, 0);
			break;
		case UMTS_OPERATING_BAND_10:	//	1700	EAWS A-G	1710 – 1770	2110 – 2170
			channel = calc_uarfcn(freq, freq %  khz(200) == 0 ? mhz(1490) : khz(1430100));
			break;
		case UMTS_OPERATING_BAND_11:	//	1500	LPDC	1427.9 – 1447.9	1475.9 – 1495.9
			channel = calc_uarfcn(freq, mhz(736));
			break;
		case UMTS_OPERATING_BAND_12:	//	700	LSMH A/B/C	699 – 716	729 – 746
			channel = calc_uarfcn(freq, freq %  khz(200) == 0 ? mhz(-37) : khz(-54900));
			break;
		case UMTS_OPERATING_BAND_13:	//	700	USMH C	777 – 787	746 – 756
			channel = calc_uarfcn(freq, freq %  khz(200) == 0 ? mhz(-55) : khz(-64900));
			break;
		case UMTS_OPERATING_BAND_14:	//	700	USMH D	788 – 798	758 – 768
			channel = calc_uarfcn(freq, freq %  khz(200) == 0 ? mhz(-63) : khz(-72900));
			break;
		case UMTS_OPERATING_BAND_19:	//	800		832.4 – 842.6	877.4 – 887.6
			channel = calc_uarfcn(freq, freq %  khz(200) == 0 ? mhz(735) : khz(720100));
			break;
		case UMTS_OPERATING_BAND_20:	//	800	EUDD	832 – 862	791 – 821
			channel = calc_uarfcn(freq, mhz(-109));
			break;
		case UMTS_OPERATING_BAND_21:	//	1500	UPDC	1447.9 – 1462.9	1495.9 – 1510.9
			channel = calc_uarfcn(freq, mhz(1326));
			break;
		case UMTS_OPERATING_BAND_25:	//	1900	EPCS A-G	1850 – 1915	1930 – 1995
			channel = calc_uarfcn(freq, freq % khz(200) == 0 ? mhz(910) : khz(674100));
			break;

		case UMTS_OPERATING_BAND_26:    //	850	ECLR	814 – 849	859 – 894
		case UMTS_OPERATING_BAND_22:	//	3500		3410 – 3490	3510 – 3590
		default:
			throw misc_error("Error converting to UARFCN.  Frequency and band are not supported.", CONVERSION_ERROR);
		}
		return channel;
	}

	void check_umts_freq(frequency_type freq, operating_band band) {
		auto r = ranges_.get_band_freq_range(band);
		if(freq < r.low_freq_hz_ || freq > r.high_freq_hz_)
			throw misc_error("Error converting to UARFCN.  Frequency (" + std::to_string(freq) +
			") out of range for specified band (" + std::to_string((int)band) + ".", CONVERSION_ERROR);
	}

	channel_type calc_uarfcn(frequency_type freq, int offset) {
		return (channel_type)boost::math::tr1::round((freq - offset) / 1e6 * 5);
	}

	channel_type frequency_to_earfcn(frequency_type freq, operating_band band) {
		if(freq % khz(100) != 0)
			throw misc_error("Error converting to EARFCN.  Frequency (" + std::to_string(freq) + ") is not a valid channel.", CONVERSION_ERROR);

		channel_type channel;
		switch(band) {
		case LTE_OPERATING_BAND_1:
			channel = calc_earfcn(freq, band, 0);
			break;
		case LTE_OPERATING_BAND_2:
			channel = calc_earfcn(freq, band, 600);
			break;
		case LTE_OPERATING_BAND_3:
			channel = calc_earfcn(freq, band, 1200);
			break;
		case LTE_OPERATING_BAND_4:
			channel = calc_earfcn(freq, band, 1950);
			break;
		case LTE_OPERATING_BAND_5:
			channel = calc_earfcn(freq, band, 2400);
			break;
		case LTE_OPERATING_BAND_6:
			channel = calc_earfcn(freq, band, 2650);
			break;
		case LTE_OPERATING_BAND_7:
			channel = calc_earfcn(freq, band, 2750);
			break;
		case LTE_OPERATING_BAND_8:
			channel = calc_earfcn(freq, band, 3450);
			break;
		case LTE_OPERATING_BAND_9:
			channel = calc_earfcn(freq, band, 3800);
			break;
		case LTE_OPERATING_BAND_10:
			channel = calc_earfcn(freq, band, 4150);
			break;
		case LTE_OPERATING_BAND_11:
			channel = calc_earfcn(freq, band, 4750);
			break;
		case LTE_OPERATING_BAND_12:
			channel = calc_earfcn(freq, band, 5010);
			break;
		case LTE_OPERATING_BAND_13:
			channel = calc_earfcn(freq, band, 5180);
			break;
		case LTE_OPERATING_BAND_14:
			channel = calc_earfcn(freq, band, 5280);
			break;
		case LTE_OPERATING_BAND_17:
			channel = calc_earfcn(freq, band, 5730);
			break;
		case LTE_OPERATING_BAND_18:
			channel = calc_earfcn(freq, band, 5850);
			break;
		case LTE_OPERATING_BAND_19:
			channel = calc_earfcn(freq, band, 6000);
			break;
		case LTE_OPERATING_BAND_20:
			channel = calc_earfcn(freq, band, 6150);
			break;
		case LTE_OPERATING_BAND_21:
			channel = calc_earfcn(freq, band, 6450);
			break;
		case LTE_OPERATING_BAND_23:
			channel = calc_earfcn(freq, band, 7500);
			break;
		case LTE_OPERATING_BAND_24:
			channel = calc_earfcn(freq, band, 7700);
			break;
		case LTE_OPERATING_BAND_25:
			channel = calc_earfcn(freq, band, 8040);
			break;
		case LTE_OPERATING_BAND_33:
			channel = calc_earfcn(freq, band, 36000);
			break;
		case LTE_OPERATING_BAND_34:
			channel = calc_earfcn(freq, band, 36200);
			break;
		case LTE_OPERATING_BAND_35:
			channel = calc_earfcn(freq, band, 36350);
			break;
		case LTE_OPERATING_BAND_36:
			channel = calc_earfcn(freq, band, 36950);
			break;
		case LTE_OPERATING_BAND_37:
			channel = calc_earfcn(freq, band, 37550);
			break;
		case LTE_OPERATING_BAND_38:
			channel = calc_earfcn(freq, band, 37750);
			break;
		case LTE_OPERATING_BAND_39:
			channel = calc_earfcn(freq, band, 38250);
			break;
		case LTE_OPERATING_BAND_40:
			channel = calc_earfcn(freq, band, 38650);
			break;
		case LTE_OPERATING_BAND_41:
			channel = calc_earfcn(freq, band, 39650);
			break;
		case LTE_OPERATING_BAND_42:
			channel = calc_earfcn(freq, band, 41590);
			break;
		case LTE_OPERATING_BAND_43:
			channel = calc_earfcn(freq, band, 43590);
			break;

			break;
		default:
			throw misc_error("Error converting to EARFCN.  Frequency and band are not supported.", CONVERSION_ERROR);
		}
		return channel;
	}

	// 3gpp36.101 - 5.7.3
	// Fdl = Fdl_low + 0.1(Ndl - Noffset)
	channel_type calc_earfcn(frequency_type freq, operating_band band, int n_offset) {
		auto r = ranges_.get_band_freq_range(band);
		return static_cast<channel_type>(boost::math::tr1::round((freq - r.low_freq_hz_) / 1e5) + n_offset);
	}

	operating_band_range_specifier ranges_;
};


}