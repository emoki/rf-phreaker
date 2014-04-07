#pragma once

#include <rf_phreaker/ipp_custom/ipp.h>
#include "rf_phreaker/common/ipp_array.h"

#include <stdexcept>
#include <boost/lexical_cast.hpp>

namespace rf_phreaker
{

class ipp_helper
{
public:
	static void check_status(IppStatus status)
	{
		if(status != ippStsNoErr)
			throw std::runtime_error(std::string("Error executing Ipp function.  Status = ") + boost::lexical_cast<std::string>(status));
	}

	static void normalize_signal(Ipp32fc *source_destination, int length)
	{
		Ipp64f l2_norm = calculate_average_rms(source_destination, length);

		Ipp32fc sig_rms_inverse;
		sig_rms_inverse.re = static_cast<Ipp32f>(1.0 / l2_norm);
		sig_rms_inverse.im = 0;
		ipp_helper::check_status(ippsMulC_32fc_I(sig_rms_inverse, source_destination, length));
	}
	static void normalize_signal(Ipp32fc *source, Ipp32fc * destination, int length)
	{
		Ipp64f l2_norm = calculate_average_rms(source, length);

		Ipp32fc sig_rms_inverse;
		sig_rms_inverse.re = static_cast<Ipp32f>(1.0f / l2_norm);
		sig_rms_inverse.im = 0;
		ipp_helper::check_status(ippsMulC_32fc(source, sig_rms_inverse, destination, length));
	}

	static double calculate_average_rms(const Ipp32fc *source, int length)
	{
		Ipp64f l2_norm;

		ipp_helper::check_status(ippsNorm_L2_32fc64f(source, length, &l2_norm));

		l2_norm /= sqrt((double)length);

		return l2_norm;
	}

	static void subtract_dc(Ipp32fc *srcdst, int length)
	{
		Ipp32fc mean;
		ipp_helper::check_status(ippsMean_32fc(srcdst, length, &mean, ippAlgHintAccurate));
		ipp_helper::check_status(ippsSubC_32fc_I(mean, srcdst, length));
	}
};

}