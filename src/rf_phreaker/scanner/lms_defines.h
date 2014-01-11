#pragma once

#include <boost/utility/binary.hpp>
#include <stdint.h>

#include "rf_phreaker/scanner/scanner_types.h"

namespace rf_phreaker { namespace scanner { namespace lms
{

// Top level configuration //////////////////////////////////////////////////////




// Bandwidth //////////////////////////////////////////////////////

/*
Bits		Description
7–6			Not Used
5–2			BWC_LPF[3:0]: LPF bandwidth control:
				code Bandwidth [MHz]
				=======================
				0000  14 (default)
				0001  10
				0010  7
				0011  6
				0100  5
				0101  4.375
				0110  3.5
				0111  3
				1000  2.75
				1001  2.5
				1010  1.92
				1011  1.5
				1100  1.375
				1101  1.25
				1110  0.875
				1111  0.75
1			EN_LPF : LPF modules enable
				0 – LPF modules powered down
				1 – LPF modules enabled (default)
0			DECODE:
				0 – decode control signals (default)
				1 – use control signals from test mode registers
*/


enum bandwidth_enum
{
	BANDWIDTH_28_MHZ,
	BANDWIDTH_20_MHZ,
	BANDWIDTH_14_MHZ,
	BANDWIDTH_12_MHZ,
	BANDWIDTH_10_MHZ,
	BANDWIDTH_8P75_MHZ,
	BANDWIDTH_7_MHZ,
	BANDWIDTH_6_MHZ,
	BANDWIDTH_5P5_MHZ,
	BANDWIDTH_5_MHZ,
	BANDWIDTH_3P84_MHZ,
	BANDWIDTH_3_MHZ,
	BANDWIDTH_2P75_MHZ,
	BANDWIDTH_2P5_MHZ,
	BANDWIDTH_1P75_MHZ,
	BANDWIDTH_1P5_MHZ
};

static const lms_register_type  lpf_bandwidth_register = 0x54;

inline lms_value_type enable_lpf(lms_value_type v) { return v | 0x02; }
inline lms_value_type disable_lpf(lms_value_type v) { return v & ~0x02; }
inline lms_value_type decode_control_signals(lms_value_type v) { return v & ~0x01; }
inline lms_value_type use_control_signals_test_mode_registers(lms_value_type v) { return v | 0x01; }



// Frequency //////////////////////////////////////////////////////

/*  FREQSEL Chart
Low(ghz)	High(ghz)	Low(mhz)High(mhz)Binary	Hex
0.232500	0.285625	233		286		100111	27
0.285625	0.336875	286		337		101111	2F
0.336875	0.405000	337		405		110111	37
0.405000	0.465000	405		465		111111	3F
0.465000	0.571250	465		571		100110	26
0.571250	0.673750	571		674		101110	2E
0.673750	0.810000	674		810		110110	36
0.810000	0.930000	810		930		111110	3E
0.930000	1.142500	930		1143	100101	25
1.142500	1.347500	1143	1348	101101	2D
1.347500	1.620000	1348	1620	110101	35
1.620000	1.860000	1620	1860	111101	3D
1.860000	2.285000	1860	2285	100100	24
2.285000	2.695000	2285	2695	101100	2C
2.695000	3.240000	2695	3240	110100	34
3.240000	3.720000	3240	3720	111100	3C
*/

/* Freq calculations
x = 2^(freq_sel[2..0] - 3);
nint = (x * f_lo) / f_ref;
nfrac = 2^23*((x*f_lo/f_ref)-nint);
*/


/**
 * Information about the frequency calculation for the LMS6002D PLL
 * Calculation taken from the LMS6002D Programming and Calibration Guide
 * version 1.1r1.
 */
struct lms_freq {
    uint8_t     x_;             /**< VCO division ratio */
    uint16_t    nint_;          /**< Integer portion of f_LO given f_REF */
    uint32_t    nfrac_;         /**< Fractional portion of f_LO given nint and f_REF */
    uint8_t     freq_select_;       /**< Choice of VCO and dision ratio */
    uint32_t    reference_;     /**< Reference frequency going to the LMS6002D */
} ;


static const lms_register_type rx_nint_register = 0x20;
static const lms_register_type rx_nfractional_msb_register = 0x21;
static const lms_register_type rx_nfractional_middle_register = 0x22;
static const lms_register_type rx_nfractional_lsb_register = 0x23;
static const lms_register_type rx_freq_select_register = 0x25;

enum output_buffer_enum
{
	output_buffers_powered_down = BOOST_BINARY(000000 00),
	first_buffer_enabled = BOOST_BINARY(000000 01), // default
	second_buffer_enabled = BOOST_BINARY(000000 10),
	third_buffer_enabled = BOOST_BINARY(000000 11)
};



// vtune //////////////////////////////////////////////////////

static const lms_register_type vcocap_program_register = 0x29;
static const lms_register_type vtune_comparator_register = 0x2A;
static const lms_register_type vtune_comparator_power_up_register = 0x2B;

static const lms_value_type vco_comparator_default = 0x76;

static const lms_value_type vcocap_program_default = 0x80;
static const lms_value_type vcocap_min_cap = 0;
static const lms_value_type vcocap_max_cap = 63;
static const lms_value_type vcocap_median_cap = 31;

enum v_tune_enum
{
	VTUNE_IN_RANGE,
	VTUNE_LOW,
	VTUNE_HIGH,
	VTUNE_INVALID
};

inline bool is_vco_comparator_power_enabled(lms_value_type v) { return (v & (1 << 3)) != (1 << 3); }
inline lms_value_type enable_vco_comparator_power(lms_value_type v = vco_comparator_default) { return v & ~(1 << 3); }
inline lms_value_type disable_vco_comparator_power(lms_value_type v = vco_comparator_default) { return v | (1 << 3); }

inline v_tune_enum get_vtune(lms_value_type v) { return (v_tune_enum)(v >> 6); }
inline lms_value_type convert_vtune(v_tune_enum v) { return (lms_value_type)(v << 6); }

inline lms_value_type set_vco_cap(lms_value_type vco_cap_value, lms_value_type v = vcocap_program_default) { return vco_cap_value | v; } 


// gain //////////////////////////////////////////////////////

/* LNA options */
enum lna_select_enum {
    LNA_NONE,   /**< Disable all LNAs */
    LNA_1,      /**< Enable LNA1 (300MHz - 2.8GHz) */
    LNA_2,      /**< Enable LNA2 (1.5GHz - 3.8GHz) */
    LNA_3       /**< Enable LNA3 (300MHz - 3.0GHz) */
} ;

/* LNA gain options */
enum lna_gain_enum{
    LNA_UNKNOWN,    /**< Invalid LNA gain */
    LNA_BYPASS,     /**< LNA bypassed - 0dB gain */
    LNA_MID,        /**< LNA Mid Gain (MAX-6dB) */
    LNA_MAX         /**< LNA Max Gain */
};

static const lms_register_type rx_vga2_voltage_control_register = 0x64;
static const lms_register_type rx_vga2_gain_control_register = 0x65;

static const lms_register_type lna_gain_and_select_register = 0x75;
static const lms_register_type rfb_tia_rxfe_mixer_gain_control_register = 0x76;
static const lms_register_type bias_current_mixer_and_lna_register = 0x7a;
static const lms_register_type bias_current_tia_and_mixer_lo_register = 0x7b;


inline  lms_value_type set_lna_gain(lms_value_type v, lna_gain_enum gain) { return (v & 0x3F) | (static_cast<lms_value_type>(gain) << 6); }
inline  lna_gain_enum get_lna_gain(lms_value_type v) { return  static_cast<lna_gain_enum>(((v & 0x3F) >> 6) & 0x03); }

inline lms_value_type set_lna_select(lms_value_type v, lna_select_enum lna) { return (v & 0xCF) | (static_cast<lms_value_type>(lna) << 4); }
inline lna_select_enum get_lna_select(lms_value_type v) { return static_cast<lna_select_enum>(((v & 0xCF) >> 4) & 0x03); }

inline lms_value_type mask_rfb_tia_rxfe(lms_value_type v) { return v & 0x7F; }

inline lms_value_type set_ict_mix_rxfe_bias_current(lms_value_type v) { return v & 0x0F; }
inline lms_value_type set_ict_mix_rxfe_nomimal_bias_current(lms_value_type v) { return (v & 0x0F) | 0x70; }
inline lms_value_type set_ict_mix_rxfe_2_1_x_nomimal_bias_current(lms_value_type v) { return (v & 0x0F) | 0xF0; }
inline lms_value_type set_ict_mix_rxfe_custom_current(lms_value_type v, lms_value_type custom) { return (v & 0x0F) | ((custom << 4) & 0xF0); }

inline lms_value_type set_ict_lna_rxfe_bias_current(lms_value_type v) { return v & 0xF0; }
inline lms_value_type set_ict_lna_rxfe_nomimal_bias_current(lms_value_type v) { return (v & 0xF0) | 0x07; }
inline lms_value_type set_ict_lna_rxfe_2_1_x_nomimal_bias_current(lms_value_type v) { return (v & 0xF0) | 0x0F; }
inline lms_value_type set_ict_lna_rxfe_custom_current(lms_value_type v, lms_value_type custom) { return (v & 0xF0) | (custom & 0x0F); }

inline lms_value_type set_ict_tia_rxfe_bias_current(lms_value_type v) { return v & 0x0F; }
inline lms_value_type set_ict_tia_rxfe_nomimal_bias_current(lms_value_type v) { return (v & 0x0F) | 0x70; }
inline lms_value_type set_ict_tia_rxfe_2_1_x_nomimal_bias_current(lms_value_type v) { return (v & 0x0F) | 0xF0; }
inline lms_value_type set_ict_tia_rxfe_custom_current(lms_value_type v, lms_value_type custom) { return (v & 0x0F) | ((custom << 4) & 0xF0); }

inline lms_value_type set_ict_mxlob_rxfe_bias_current(lms_value_type v) { return v & 0xF0; }
inline lms_value_type set_ict_mxlob_rxfe_nomimal_bias_current(lms_value_type v) { return (v & 0xF0) | 0x07; }
inline lms_value_type set_ict_mxlob_rxfe_2_1_x_nomimal_bias_current(lms_value_type v) { return (v & 0xF0) | 0x0F; }
inline lms_value_type set_ict_mxlob_rxfe_custom_current(lms_value_type v, lms_value_type custom) { return (v & 0xF0) | (custom & 0x0F); }

inline lms_value_type convert_and_mask_rx_vga2_gain_control(lms_value_type v) { v = v / 3; return (v & 0x1F); }

inline lms_value_type enable_rx_vga2(lms_value_type v) { return (v & ~0x03) | 0x03; }
inline lms_value_type disable_rx_vga2(lms_value_type v) { return (v & ~0x03); }


// Figure out how this works!
//inline lms_value_type set_and_convert_rx_vga2_voltage_control(lms_value_type v, int voltage) { voltage = voltage / 7; return (v & 0xC3) | (static_cast<lms_value_type>(voltage) & 0x0F) << 2; }
inline lms_value_type get_default_rx_vga2_voltage_control(lms_value_type v) { return (v & 0xC3) | 0x1C; }





}}}