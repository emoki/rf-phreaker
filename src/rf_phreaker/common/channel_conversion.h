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
	channel_type frequency_to_channel(frequency_type freq, operating_band band)
	{
		if(band >= FIRST_GSM_OPERATING_BAND && band <= LAST_GSM_OPERATING_BAND)
			return frequency_to_arfcn(freq, band);
		else if(band >= FIRST_UMTS_OPERATING_BAND && band <= LAST_UMTS_OPERATING_BAND)
			return frequency_to_uarfcn(freq, band);
		else if(band >= FIRST_LTE_OPERATING_BAND && band <= LAST_LTE_OPERATING_BAND)
			return frequency_to_earfcn(freq, band);
		else
			throw misc_error("Error converting frequency to channel. Unknown operating band (" + std::to_string((int)band) + ").");
	}

	channel_type frequency_to_arfcn(frequency_type freq, operating_band band)
	{
		channel_type channel;
		throw misc_error("Converting ARFCN is not supported.");
		return channel;
	}
	channel_type frequency_to_uarfcn(frequency_type freq, operating_band band)
	{
		if(freq % khz(200) != 0 && freq % khz(500) != 0)
			throw misc_error("Error converting to UARFCN.  Frequency (" + std::to_string(freq) + ") is not a valid channel.");

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
		case UMTS_OPERATING_BAND_10:	//	1700	EAWS A-G	1710 – 1770	2110 – 2170
		case UMTS_OPERATING_BAND_11:	//	1500	LPDC	1427.9 – 1447.9	1475.9 – 1495.9
		case UMTS_OPERATING_BAND_12:	//	700	LSMH A/B/C	699 – 716	729 – 746
		case UMTS_OPERATING_BAND_13:	//	700	USMH C	777 – 787	746 – 756
		case UMTS_OPERATING_BAND_14:	//	700	USMH D	788 – 798	758 – 768
		case UMTS_OPERATING_BAND_19:	//	800		832.4 – 842.6	877.4 – 887.6
		case UMTS_OPERATING_BAND_20:	//	800	EUDD	832 – 862	791 – 821
			channel = calc_uarfcn(freq, mhz(-109));
			break;
		case UMTS_OPERATING_BAND_21:	//	1500	UPDC	1447.9 – 1462.9	1495.9 – 1510.9
		case UMTS_OPERATING_BAND_22:	//	3500		3410 – 3490	3510 – 3590
		case UMTS_OPERATING_BAND_25:	//	1900	EPCS A-G	1850 – 1915	1930 – 1995
		case UMTS_OPERATING_BAND_26:    //	850	ECLR	814 – 849	859 – 894
		default:
			throw misc_error("Error converting to UARFCN.  Frequency and band are not supported.");
		}
		return channel;
	}
	void check_umts_freq(frequency_type freq, operating_band band)
	{
		auto r = ranges_.get_band_freq_range(band);
		if(freq < r.low_freq_hz_ || freq > r.high_freq_hz_)
			throw misc_error("Error converting to UARFCN.  Frequency (" + std::to_string(freq) + 
				") out of range for specified band (" + std::to_string((int)band) + ".");
	}
	
	channel_type calc_uarfcn(frequency_type freq, int offset)
	{
		return (channel_type)boost::math::tr1::round((freq - offset) / 1e6 * 5);
	}
	
	channel_type frequency_to_earfcn(frequency_type freq, operating_band band)
	{
		if(freq % khz(100) != 0)
			throw misc_error("Error converting to EARFCN.  Frequency (" + std::to_string(freq) + ") is not a valid channel.");

		channel_type channel;
		switch(band)
		{
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
			throw misc_error("Error converting to EARFCN.  Frequency and band are not supported.");
		}
		return channel;
	}

	// 3gpp36.101 - 5.7.3
	// Fdl = Fdl_low + 0.1(Ndl - Noffset)
	channel_type calc_earfcn(frequency_type freq, operating_band band, int n_offset)
	{
		auto r = ranges_.get_band_freq_range(band);
		return static_cast<channel_type>(boost::math::tr1::round((freq - r.low_freq_hz_) / 1e5) + n_offset);
	}

	operating_band_range_specifier ranges_;
};


}