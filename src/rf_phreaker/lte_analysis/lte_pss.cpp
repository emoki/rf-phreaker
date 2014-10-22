#include "lte_pss.h"
#include "lte_fft.h"
#include <cmath>

namespace rf_phreaker {

#define LTE_SUBCARRIER_BW_HZ	15000
#define PI						3.1415926


const int LtePrimarySyncSequence::m_ZCRoots[LTE_NUM_PSS] = {25, 29, 34};
const int LtePrimarySyncSequence::m_ZCLen = 63;

LtePrimarySyncSequence::LtePrimarySyncSequence(unsigned int SampleRatekHz) :
	m_SampleRateHz(SampleRatekHz*1000), m_SeqLen(0)
{
	if ( (m_SampleRateHz % LTE_SUBCARRIER_BW_HZ) || (SampleRatekHz>LTE_MAX_SAMPLE_RATE_KHZ) )
	{
		throw("LtePSSInitError");
	}
	m_SeqLen = m_SampleRateHz / LTE_SUBCARRIER_BW_HZ;

	// Create a DFT such that the inverse DFT will create a time-domain PSS
	// where the sum(abs(PSS).^2) = (1/128)
	LteDFT PssDFT(m_SeqLen, IPP_FFT_DIV_INV_BY_N);

	// allocate memory for all the PSS arrays
	int psid, idx;

	for(psid=0; psid<LTE_NUM_PSS; psid++)
	{
		m_SeqT[psid] = ippsMalloc_32fc(m_SeqLen);
		m_SeqF[psid] = ippsMalloc_32fc(m_SeqLen);
		ippsZero_32fc(m_SeqF[psid], m_SeqLen);

		// From LTE: From Theory To Practice, page 148:
		// ZC(n) = exp[-j*pi*M*n*(n+1)/63] for n = 0 ... 62.
		Ipp32fc zc[m_ZCLen];
		double dTmp;
		Ipp32f energyNorm = (Ipp32f)sqrt((float)(m_ZCLen - 1));
		// idx=0 corresponds to the most negative PSS freq component.
		// idx = 31 (ZCLen/2) corresponds to DC,
		// and thus will be zeroed out in the PSS_F array.
		// Divide values by sqrt(ZCLen) so that the total energy of the PSS = 1.0
		for ( idx=0; idx<m_ZCLen; idx++ )
		{
			dTmp = PI*m_ZCRoots[psid]*idx*(idx+1)/m_ZCLen;
			zc[idx].re = (Ipp32f)cos(dTmp)/energyNorm;
			zc[idx].im = -(Ipp32f)sin(dTmp)/energyNorm;
		}
		// Copy the positive freqs from zc into the positive PssF freq space,
		// starting at the first freq bin AFTER DC (i.e. leave DC component = 0).
		ippsCopy_32fc(zc+32, m_SeqF[psid]+1, m_ZCLen/2);
		// Then copy the negative freqs from zc into the negative PssF freq space.
		ippsCopy_32fc(zc, m_SeqF[psid]+m_SeqLen-m_ZCLen/2, m_ZCLen/2);

		PssDFT.DftInverse(m_SeqF[psid], m_SeqT[psid]);
	}
}

LtePrimarySyncSequence::~LtePrimarySyncSequence()
{
	for(int psid=0; psid<LTE_NUM_PSS; psid++)
	{
		ippsFree(m_SeqT[psid]);
		ippsFree(m_SeqF[psid]);
	}
}

}