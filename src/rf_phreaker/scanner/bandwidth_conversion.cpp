#include "rf_phreaker/scanner/bandwidth_conversion.h"
#include "rf_phreaker/scanner/packet_typedefs.h"
#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;
using namespace rf_phreaker::scanner::lms;

const bandwidth_type uint_bandwidths[] = {
    mhz(28),
    mhz(20),
    mhz(14),
    mhz(12),
    mhz(10),
    khz(8750),
    mhz(7),
    mhz(6),
    khz(5500),
    mhz(5),
    khz(3840),
    mhz(3),
    khz(2750),
    khz(2500),
    khz(1750),
    khz(1500)
};

packet_container bandwidth_conversion::get_bandwidth_and_enable_lpf(bandwidth_type bw)
{
	packet_container container;

	container.add_packet(std::make_shared<lime_write_packet>(lpf_bandwidth_register, get_bandwidth_and_enable_lpf_value(bw)));

	return container;
}

lms_value_type bandwidth_conversion::get_bandwidth_and_enable_lpf_value(bandwidth_type bw)
{
	bandwidth_enum lms_bw = find_lower_bound_bandwidth(bw);

	return (lms_value_type)decode_control_signals(enable_lpf((lms_value_type)lms_bw << 2));
}

lms::bandwidth_enum bandwidth_conversion::find_lower_bound_bandwidth(bandwidth_type bw)
{
    if(      bw <= khz(1500) ) return BANDWIDTH_1P5_MHZ;
    else if( bw <= khz(1750) ) return BANDWIDTH_1P75_MHZ;
    else if( bw <= khz(2500) ) return BANDWIDTH_2P5_MHZ;
    else if( bw <= khz(2750) ) return BANDWIDTH_2P75_MHZ;
    else if( bw <= mhz(3)    ) return BANDWIDTH_3_MHZ;
    else if( bw <= khz(3840) ) return BANDWIDTH_3P84_MHZ;
    else if( bw <= mhz(5)    ) return BANDWIDTH_5_MHZ;
    else if( bw <= khz(5500) ) return BANDWIDTH_5P5_MHZ;
    else if( bw <= mhz(6)    ) return BANDWIDTH_6_MHZ ;
    else if( bw <= mhz(7)    ) return BANDWIDTH_7_MHZ ;
    else if( bw <= khz(8750) ) return BANDWIDTH_8P75_MHZ ;
    else if( bw <= mhz(10)   ) return BANDWIDTH_10_MHZ ;
    else if( bw <= mhz(12)   ) return BANDWIDTH_12_MHZ ;
    else if( bw <= mhz(14)   ) return BANDWIDTH_14_MHZ ;
    else if( bw <= mhz(20)   ) return BANDWIDTH_20_MHZ ;
    else if( bw <= mhz(28)   ) return BANDWIDTH_28_MHZ ;

	throw misc_error(str(boost::format("Specified bandwidth of %d is too large.") % bw));
}

bandwidth_type bandwidth_conversion::convert_to_bandwidth_type(lms::bandwidth_enum bw)
{
    return uint_bandwidths[bw&0xf];
}
