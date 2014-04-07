#include <stdlib.h>
#include <stdio.h>

#include "lte_fft.h"

namespace rf_phreaker {

/*****************************************************************************/
/*
* fft512()
*
* Function to perform a 512-point fft.
*/
/*****************************************************************************/
static IppsFFTSpec_C_32fc *fftSpec1024 = NULL;
// order must be an int such that 2^order == size of FFT
static const int order1024 = 10;


static IppsFFTSpec_C_32fc *fftSpec512 = NULL;
// order must be an int such that 2^order == size of FFT
static const int order512 = 9;

static IppsFFTSpec_C_32fc *fftSpec256 = NULL;
// order must be an int such that 2^order == size of FFT
static const int order256 = 8;

static IppsFFTSpec_C_32fc *fftSpec128 = NULL;
// order must be an int such that 2^order == size of FFT
static const int order128 = 7;

static IppsFFTSpec_C_32fc *fftSpec64 = NULL;
// order must be an int such that 2^order == size of FFT
static const int order64 = 6;



int Init_FFT_1024( int init )
{
	if ( init ) // this means we are initializing the fft
	{
		if ( fftSpec1024 != NULL ) return 1;

		// initialize the twiddle tables.
		// If there's an error, free the spec structure as needed.
		// TODO:: revisit normalization and hint arguments
		//if ( ippsFFTInitAlloc_C_32fc(&fftSpec512, order512, IPP_FFT_DIV_BY_SQRTN, //Commented -Raj 3rd Nov 2011
		//	ippAlgHintAccurate) != ippStsNoErr )

		//if ( ippsFFTInitAlloc_C_32fc(&fftSpec512, order512, IPP_FFT_DIV_FWD_BY_N, 
			//ippAlgHintAccurate) != ippStsNoErr )
		if ( ippsFFTInitAlloc_C_32fc(&fftSpec1024, order1024, IPP_FFT_NODIV_BY_ANY, 
		ippAlgHintAccurate) != ippStsNoErr )
		{
			if ( fftSpec1024 != NULL )
			{
				ippsFFTFree_C_32fc(fftSpec1024);
				fftSpec1024 = NULL;
			}
			return -1;
		}
	}
	else // this means we are de-allocating the fft
	{
		if ( fftSpec1024 == NULL ) return 1;
		ippsFFTFree_C_32fc(fftSpec1024);
		fftSpec1024 = NULL;
	}
	return 0;
}

int FFT_1024( const Ipp32fc *Src, Ipp32fc *Dst )
{
	if ( fftSpec1024 == NULL ) return -1;

	// TODO:: use external work buffer in stead of NULL as parm3
	if ( ippsFFTFwd_CToC_32fc( Src, Dst, fftSpec1024, NULL ) != ippStsNoErr ) return -2;
	return 0;
}

int InverseFFT_1024( const Ipp32fc *Src, Ipp32fc *Dst )
{
	if ( fftSpec1024 == NULL ) return -1;

	// TODO:: use external work buffer in stead of NULL as parm3
	if ( ippsFFTInv_CToC_32fc( Src, Dst, fftSpec1024, NULL ) != ippStsNoErr ) return -2;
	return 0;
}




int Init_FFT_512( int init )
{
	if ( init ) // this means we are initializing the fft
	{
		if ( fftSpec512 != NULL ) return 1;

		// initialize the twiddle tables.
		// If there's an error, free the spec structure as needed.
		// TODO:: revisit normalization and hint arguments
		//if ( ippsFFTInitAlloc_C_32fc(&fftSpec512, order512, IPP_FFT_DIV_BY_SQRTN, //Commented -Raj 3rd Nov 2011
		//	ippAlgHintAccurate) != ippStsNoErr )

		//if ( ippsFFTInitAlloc_C_32fc(&fftSpec512, order512, IPP_FFT_DIV_FWD_BY_N, 
			//ippAlgHintAccurate) != ippStsNoErr )
		if ( ippsFFTInitAlloc_C_32fc(&fftSpec512, order512, IPP_FFT_NODIV_BY_ANY, 
		ippAlgHintAccurate) != ippStsNoErr )
		{
			if ( fftSpec512 != NULL )
			{
				ippsFFTFree_C_32fc(fftSpec512);
				fftSpec512 = NULL;
			}
			return -1;
		}
	}
	else // this means we are de-allocating the fft
	{
		if ( fftSpec512 == NULL ) return 1;
		ippsFFTFree_C_32fc(fftSpec512);
		fftSpec512 = NULL;
	}
	return 0;
}

int FFT_512( const Ipp32fc *Src, Ipp32fc *Dst )
{
	if ( fftSpec512 == NULL ) return -1;

	// TODO:: use external work buffer in stead of NULL as parm3
	if ( ippsFFTFwd_CToC_32fc( Src, Dst, fftSpec512, NULL ) != ippStsNoErr ) return -2;
	return 0;
}

int InverseFFT_512( const Ipp32fc *Src, Ipp32fc *Dst )
{
	if ( fftSpec512 == NULL ) return -1;

	// TODO:: use external work buffer in stead of NULL as parm3
	if ( ippsFFTInv_CToC_32fc( Src, Dst, fftSpec512, NULL ) != ippStsNoErr ) return -2;
	return 0;
}


int Init_FFT_256( int init )
{
	if ( init ) // this means we are initializing the fft
	{
		if ( fftSpec256 != NULL ) return 1;

		// initialize the twiddle tables.
		// If there's an error, free the spec structure as needed.
		// TODO:: revisit normalization and hint arguments
//		if ( ippsFFTInitAlloc_C_32fc(&fftSpec256, order256, IPP_FFT_DIV_BY_SQRTN, 
		if ( ippsFFTInitAlloc_C_32fc(&fftSpec256, order256, IPP_FFT_DIV_FWD_BY_N,			
			ippAlgHintAccurate) != ippStsNoErr )
		{
			if ( fftSpec256 != NULL )
			{
				ippsFFTFree_C_32fc(fftSpec256);
				fftSpec256 = NULL;
			}
			return -1;
		}
	}
	else // this means we are de-allocating the fft
	{
		if ( fftSpec256 == NULL ) return 1;
		ippsFFTFree_C_32fc(fftSpec256);
		fftSpec256 = NULL;
	}
	return 0;
}

int FFT_256( const Ipp32fc *Src, Ipp32fc *Dst )
{
	if ( fftSpec256 == NULL ) return -1;

	// TODO:: use external work buffer in stead of NULL as parm3
	if ( ippsFFTFwd_CToC_32fc( Src, Dst, fftSpec256, NULL ) != ippStsNoErr ) return -2;
	return 0;
}

int InverseFFT_256( const Ipp32fc *Src, Ipp32fc *Dst )
{
	if ( fftSpec256 == NULL ) return -1;

	// TODO:: use external work buffer in stead of NULL as parm3
	if ( ippsFFTInv_CToC_32fc( Src, Dst, fftSpec256, NULL ) != ippStsNoErr ) return -2;
	return 0;
}


int Init_FFT_128(int init )
{
	if ( init ) // this means we are initializing the fft
	{
		if ( fftSpec128 != NULL ) return 1;

		// initialize the twiddle tables.
		// If there's an error, free the spec structure as needed.
		// TODO:: revisit normalization and hint arguments

		// Changed 25 Oct 2009, Dhaval Dave'
		// don't normalize FFT so that algorithm matches Matlab
		// TODO: change back to IPP_FFT_DIV_BY_SQRTN?
		//if ( ippsFFTInitAlloc_C_32fc(&fftSpec128, order128, IPP_FFT_NODIV_BY_ANY, 
		if ( ippsFFTInitAlloc_C_32fc(&fftSpec128, order128, IPP_FFT_DIV_BY_SQRTN, 
			ippAlgHintAccurate) != ippStsNoErr )
		{
			if ( fftSpec128 != NULL )
			{
				ippsFFTFree_C_32fc(fftSpec128);
				fftSpec128 = NULL;
			}
			return -1;
		}
	}
	else // this means we are de-allocating the fft
	{
		if ( fftSpec128 == NULL ) return 1;
		ippsFFTFree_C_32fc(fftSpec128);
		fftSpec128 = NULL;
	}
	return 0;
}

int FFT_128( const Ipp32fc *Src, Ipp32fc *Dst )
{
	if ( fftSpec128 == NULL ) return -1;

	// TODO:: use external work buffer in stead of NULL as parm3
	if ( ippsFFTFwd_CToC_32fc( Src, Dst, fftSpec128, NULL ) != ippStsNoErr ) return -2;
	return 0;
}

int InverseFFT_128( const Ipp32fc *Src, Ipp32fc *Dst )
{
	if ( fftSpec128 == NULL ) return -1;

	// TODO:: use external work buffer in stead of NULL as parm3
	if ( ippsFFTInv_CToC_32fc( Src, Dst, fftSpec128, NULL ) != ippStsNoErr ) return -2;
	return 0;
}






int Init_FFT_64(int init )
{
	if ( init ) // this means we are initializing the fft
	{
		if ( fftSpec64 != NULL ) return 1;

		// initialize the twiddle tables.
		// If there's an error, free the spec structure as needed.
		// TODO:: revisit normalization and hint arguments

		// Changed 25 Oct 2009, Dhaval Dave'
		// don't normalize FFT so that algorithm matches Matlab
		// TODO: change back to IPP_FFT_DIV_BY_SQRTN?
		//if ( ippsFFTInitAlloc_C_32fc(&fftSpec128, order128, IPP_FFT_NODIV_BY_ANY, 
		if ( ippsFFTInitAlloc_C_32fc(&fftSpec64, order64, IPP_FFT_DIV_BY_SQRTN, 
			ippAlgHintAccurate) != ippStsNoErr )
		{
			if ( fftSpec64 != NULL )
			{
				ippsFFTFree_C_32fc(fftSpec64);
				fftSpec64 = NULL;
			}
			return -1;
		}
	}
	else // this means we are de-allocating the fft
	{
		if ( fftSpec64 == NULL ) return 1;
		ippsFFTFree_C_32fc(fftSpec64);
		fftSpec64 = NULL;
	}
	return 0;
}

int FFT_64( const Ipp32fc *Src, Ipp32fc *Dst )
{
	if ( fftSpec64 == NULL ) return -1;

	// TODO:: use external work buffer in stead of NULL as parm3
	if ( ippsFFTFwd_CToC_32fc( Src, Dst, fftSpec64, NULL ) != ippStsNoErr ) return -2;
	return 0;
}

int InverseFFT_64( const Ipp32fc *Src, Ipp32fc *Dst )
{
	if ( fftSpec64 == NULL ) return -1;

	// TODO:: use external work buffer in stead of NULL as parm3
	if ( ippsFFTInv_CToC_32fc( Src, Dst, fftSpec64, NULL ) != ippStsNoErr ) return -2;
	return 0;
}












LteDFT::LteDFT(unsigned int DftLen, int Normalization) :
	m_DftSpec(NULL), m_Len(0)
{
	if ( DftLen > (1<<16) )
		throw("Lte DFT init error");

	m_Len = (int)DftLen;

	if ( ippsDFTInitAlloc_C_32fc((IppsDFTSpec_C_32fc**)(&m_DftSpec), m_Len, Normalization, ippAlgHintAccurate) != ippStsNoErr )
		throw("Lte DFT init error");
}

LteDFT::~LteDFT()
{
	ippsDFTFree_C_32fc(m_DftSpec);
}

int LteDFT::DftFwd(const Ipp32fc *Src, Ipp32fc *Dst) const
{
	if ( ippsDFTFwd_CToC_32fc( Src, Dst, m_DftSpec, NULL ) != ippStsNoErr ) return -2;
	return 0;
}

int LteDFT::DftInverse(const Ipp32fc *Src, Ipp32fc *Dst) const
{
	if ( ippsDFTInv_CToC_32fc( Src, Dst, m_DftSpec, NULL ) != ippStsNoErr ) return -2;
	return 0;
}



LteFFT::LteFFT(unsigned int FftOrder, int Normalization) :
	m_FftSpec(NULL), m_Order(0)
{
	if ( FftOrder > 16 )
		throw("Lte FFT init error");

	m_Order = (int)FftOrder;

	if ( ippsFFTInitAlloc_C_32fc((IppsFFTSpec_C_32fc**)(&m_FftSpec), m_Order, Normalization, ippAlgHintAccurate) != ippStsNoErr )
		throw("Lte FFT init error");
}

LteFFT::~LteFFT()
{
	ippsFFTFree_C_32fc(m_FftSpec);
}

int LteFFT::FftFwd(const Ipp32fc *Src, Ipp32fc *Dst) const
{
	if ( ippsFFTFwd_CToC_32fc( Src, Dst, m_FftSpec, NULL ) != ippStsNoErr ) return -2;
	return 0;
}

int LteFFT::FftInverse(const Ipp32fc *Src, Ipp32fc *Dst) const
{
	if ( ippsFFTInv_CToC_32fc( Src, Dst, m_FftSpec, NULL ) != ippStsNoErr ) return -2;
	return 0;
}

int LteFFT::FftShift(const Ipp32fc *Src, Ipp32fc *Dst) const
{
	int halfLen;

	if ( Src == Dst ) return -1;
	if ( m_Order <= 0 ) return -2;

	halfLen = 1 << (m_Order-1);

	ippsCopy_32fc(Src, Dst+halfLen, halfLen);
	ippsCopy_32fc(Src+halfLen, Dst, halfLen);

	return 0;
}

}