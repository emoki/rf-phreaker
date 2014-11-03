#pragma once

#include "Ipp.h"

namespace rf_phreaker {

int Init_FFT_2048(int init);
int FFT_2048(const Ipp32fc *Src, Ipp32fc *Dst);
int InverseFFT_2048(const Ipp32fc *Src, Ipp32fc *Dst);

int Init_DFT_1536(int init);
int DFT_1536(const Ipp32fc *Src, Ipp32fc *Dst);
int InverseDFT_1536(const Ipp32fc *Src, Ipp32fc *Dst);

int Init_FFT_1024(int init );
int FFT_1024( const Ipp32fc *Src, Ipp32fc *Dst );
int InverseFFT_1024( const Ipp32fc *Src, Ipp32fc *Dst );

int Init_FFT_512(int init );
int FFT_512( const Ipp32fc *Src, Ipp32fc *Dst );
int InverseFFT_512( const Ipp32fc *Src, Ipp32fc *Dst );

int Init_FFT_256( int init );
int FFT_256( const Ipp32fc *Src, Ipp32fc *Dst );
int InverseFFT_256( const Ipp32fc *Src, Ipp32fc *Dst );

int Init_FFT_128( int init );
int FFT_128( const Ipp32fc *Src, Ipp32fc *Dst );
int InverseFFT_128( const Ipp32fc *Src, Ipp32fc *Dst );

int Init_FFT_64( int init );
int FFT_64( const Ipp32fc *Src, Ipp32fc *Dst );
int InverseFFT_64( const Ipp32fc *Src, Ipp32fc *Dst );




class LteDFT
{
public:
	LteDFT(unsigned int DftLen = 0, int Normalization=IPP_FFT_DIV_BY_SQRTN);
	~LteDFT();
	int DftFwd(const Ipp32fc *Src, Ipp32fc *Dst) const;
	int DftInverse(const Ipp32fc *Src, Ipp32fc *Dst) const;
	int DftShift(const Ipp32fc *Src, Ipp32fc *Dst) const;
protected:
	IppsDFTSpec_C_32fc* const m_DftSpec;
	int m_Len;
};


class LteFFT
{
public:
	LteFFT(unsigned int FftOrder = 0, int Normalization=IPP_FFT_DIV_BY_SQRTN);
	~LteFFT();
	int FftFwd(const Ipp32fc *Src, Ipp32fc *Dst) const;
	int FftInverse(const Ipp32fc *Src, Ipp32fc *Dst) const;
	int FftShift(const Ipp32fc *Src, Ipp32fc *Dst) const;
protected:
	IppsFFTSpec_C_32fc* const m_FftSpec;
	int m_Order;
};

}