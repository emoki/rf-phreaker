#include "rf_phreaker/umts_analysis/cpich_generator.h"
#include "rf_phreaker/common/exception_types.h"
#include <memory.h>

namespace rf_phreaker {

// NOTE: uninitialized static class members must be defined at file scope
// in addition to declared in the class definition
__int8* cpich_generator::m_Zn[N_CPICH_CODES][2];


cpich_generator::cpich_generator()
{
	unsigned int code_num[N_CPICH_CODES];
	const unsigned int znSize = N_TOTAL_CHIPS_CPICH * sizeof(m_Zn[0][0][0]);

	for ( unsigned int i=0; i<512; i++ )
	{
		m_Zn[i][0] = new __int8[N_TOTAL_CHIPS_CPICH];
		memset(m_Zn[i][0], 0, znSize);

		m_Zn[i][1] = new __int8[N_TOTAL_CHIPS_CPICH];
		memset(m_Zn[i][1], 0, znSize);

		code_num[i] = i<<4;
	}

	const unsigned int mSeq_len = m_GOLDCODE_LEN - 1;
	__int8 x[mSeq_len], y[mSeq_len], bin_num;

	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));

	// Initialize register 
	x[0] = 1;
	for ( unsigned int i=0; i<18; i++ ) y[i] = 1;

	//	% m-sequences
	// MATLAB code uses a + b + ... MODULO 2, but we can use
	// bit-wise XOR, assuming that x,y values are constrained (0,1)
	for ( unsigned int i=0; i<(mSeq_len-18); i++ )
	{
		x[i+18] = x[i+7] ^ x[i];
		y[i+18] = y[i+10] ^ y[i+7] ^ y[i+5] ^ y[i];
	}

	for ( unsigned int n=0; n<N_CPICH_CODES; n++ )
	{
	// Gold code sequence, z_n
	// z_n will be either +1 or -1
		for ( unsigned int i=0, j=m_GOLDCODE_LEN/2; i<N_TOTAL_CHIPS_CPICH; i++, j++ )
		{
			bin_num = x[i+code_num[n]] ^ y[i];
			m_Zn[n][0][i] = 1 - 2*bin_num;

			bin_num = x[j+code_num[n]] ^ y[j];
			m_Zn[n][1][i] = 1 - 2*bin_num;
		}
	}
}

cpich_generator::~cpich_generator()
{
	for ( unsigned int i=0; i<512; i++ )
	{
		delete m_Zn[i][0];
		delete m_Zn[i][1];
	}
}


void cpich_generator::create_cpich_signal(Ipp32fc *dst, uint32_t cpich_num, uint32_t num_chips, uint32_t start_chip) const
{
	const unsigned int end_chip = start_chip + num_chips;

	if (end_chip > N_TOTAL_CHIPS_CPICH ) 
		throw(rf_phreaker::umts_analysis_error("Requested chip positions exceed N_TOTAL_CHIPS_CPICH"));

	if(cpich_num > N_CPICH_CODES) 
		throw(rf_phreaker::umts_analysis_error("CodeNum requested exceeds N_CPICH_CODES"));

	// n-th complex scrambling code
	Ipp32f tmp, jtmp;
	for(uint32_t i = start_chip, j=0; i < end_chip; i++, j++ )
	{
		tmp = (Ipp32f)m_Zn[cpich_num][0][i];
		jtmp = (Ipp32f)m_Zn[cpich_num][1][i];
		dst[j].re = tmp - jtmp;
		dst[j].im = tmp + jtmp;
	}
}

}