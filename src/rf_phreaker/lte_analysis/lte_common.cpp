
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <cmath>


#include "lte_common.h"
#include "cc_tb.h"
#include "lte_fft.h"
#include "rf_phreaker/common/ipp_array.h"


namespace rf_phreaker {

static const double sqrt_10 = 3.1622776601683793319988935444327;
static const double sqrt_42 = 6.480740698407860230965967436088;

void generate_cell_RS(Ipp32fc *cell_RS, unsigned int *OFDM_SymbNos, unsigned int *pSymbNum, 
	Ipp16u *frquencyIdx, unsigned int slotNo, unsigned int cellID, CYCLICPREFIX cyclicPrefixMode, 
	unsigned int N_RB_DL, unsigned int N_RB_max_DL, unsigned int antPort)
{
	int N_CP, N_DL_Symb;
	int v[2], v_shift;
	int c_init[2]; 
	unsigned int c[440];
	int ii, jj, m;
	Ipp32fc r[2][220];

	if(cyclicPrefixMode==Normal)
	{
		N_CP = 1;
		N_DL_Symb = 7;
	}
	else
	{
		N_CP = 0;
		N_DL_Symb = 6;
	}

	switch(antPort){
		case 0:
			OFDM_SymbNos[0] = 0;
			if(N_CP==1)
			{
				OFDM_SymbNos[1] = 4;
			}
			else
			{
				OFDM_SymbNos[1] = 3;
			}
			*pSymbNum = 2;
			v[0] = 0; v[1] = 3;
			break;
		case 1:
			OFDM_SymbNos[0] = 0;
			if(N_CP==1)
			{
				OFDM_SymbNos[1] = 4;
			}
			else
			{
				OFDM_SymbNos[1] = 3;
			}
			*pSymbNum = 2;
			v[0] = 3; v[1] = 0;
			break;
		case 2:
			OFDM_SymbNos[0] = 1;
			*pSymbNum = 1;
			v[0] = 3*(slotNo%2);
			break;
		case 3:
			OFDM_SymbNos[0] = 1;
			*pSymbNum = 1;
			v[0] = 3+3*(slotNo%2);
			break;		
		default:
			printf("not supported antenna port\n");
			//exit(-1);
			break;
	}

	for(ii=0;ii<(*pSymbNum);ii++)
	{
		c_init[ii] = (1<<10)*(7*(slotNo+1)+OFDM_SymbNos[ii]+1)*(2*cellID+1)+2*cellID+N_CP;
	}

	
	for(ii=0;ii<(*pSymbNum);ii++)
	{
		generate_PN_seq(c, c_init[ii], 4*N_RB_max_DL);
		for(jj=0;jj<2*N_RB_max_DL;jj++)
		{
			r[ii][jj].re = 0.707f*(1.0-2*c[2*jj]);
			r[ii][jj].im = 0.707f*(1.0-2*c[2*jj+1]);
		}
	}

	for(ii=0;ii<(*pSymbNum);ii++)
	{
		for(jj=N_RB_max_DL - N_RB_DL;jj<N_RB_max_DL + N_RB_DL;jj++)
		{
			m = jj - (N_RB_max_DL - N_RB_DL);
			cell_RS[ii*2*N_RB_DL+m].re = r[ii][jj].re;
			cell_RS[ii*2*N_RB_DL+m].im = r[ii][jj].im;
		}
	}

	v_shift = cellID%6;

	for(ii=0;ii<(*pSymbNum);ii++)
	{
		m = (v[ii]+v_shift)%6;
		for(jj=0;jj<2*N_RB_DL;jj++)
		{
			frquencyIdx[ii*2*N_RB_DL+jj] = 6*jj + m;
		}
	}
	
}


void generate_PN_seq(unsigned int *c, int c_init, int len)
{
	int N_C =1600;
	
	int ii, len2;

	Ipp8u* x1 = ippsMalloc_8u(N_C+len); 
	Ipp8u* x2 = ippsMalloc_8u(N_C+len); 

	x1[0] = 1;
	
	for(ii=1;ii<31;ii++)
	{
		x1[ii] = 0;
	}

	len2 = N_C + len - 31;

	for(ii=0;ii<len2;ii++)
	{
		x1[ii+31] = (x1[ii+3] + x1[ii])%2; 
	}

	dec2binvec(x2, c_init, 31);

	for(ii=0;ii<len2;ii++)
	{
		x2[ii+31] = (x2[ii+3]+x2[ii+2]+x2[ii+1]+x2[ii])%2; 
	}

	for(ii=0;ii<len;ii++)
	{
		c[ii] = (x1[ii+N_C]+x2[ii+N_C])%2;
	}

	ippsFree(x1);
	ippsFree(x2);
}


void dec2binvec(Ipp8u *pDest, int src, int len)
{
	int ii, iTmp;

	for(ii=0;ii<len;ii++)
	{
		pDest[ii] = 0;
	}

	iTmp = src;

	ii = 0;
	while(iTmp>0)
	{
		pDest[ii] = iTmp%2;
		iTmp = iTmp>>1;
		ii++;
	}
}


void myfftshift(Ipp32fc *pDest, Ipp32fc *pSrc, int len)
{
	int ii;

	for(ii=0;ii<len/2;ii++)
	{
		pDest[ii].re = pSrc[ii+len/2].re;
		pDest[ii].im = pSrc[ii+len/2].im;

		pDest[ii+len/2].re = pSrc[ii].re;
		pDest[ii+len/2].im = pSrc[ii].im;
	}
}


void myfft(Ipp32fc *pSeq_F, const Ipp32fc *pSeq_T, int len)
{
	switch(len)
	{
		case 128:
			Init_FFT_128(TRUE);
			FFT_128(pSeq_T, pSeq_F);
			Init_FFT_128(FALSE);
			break;
		case 256:
			Init_FFT_256(TRUE);
			FFT_256(pSeq_T, pSeq_F);
			Init_FFT_256(FALSE);
			break;
		case 512:
			Init_FFT_512(TRUE);
			FFT_512(pSeq_T, pSeq_F);
			Init_FFT_512(FALSE);
			break;
		case 1024:
			Init_FFT_1024(TRUE);
			FFT_1024(pSeq_T, pSeq_F);
			Init_FFT_1024(FALSE);
			break;
		case 1536:
			Init_DFT_1536(TRUE);
			DFT_1536(pSeq_T, pSeq_F);
			Init_DFT_1536(FALSE);
			break;
		case 2048:
			Init_FFT_2048(TRUE);
			FFT_2048(pSeq_T, pSeq_F);
			Init_FFT_2048(FALSE);
			break;
		default: 
			printf("Not supported FFT length");
			//exit(-1);
			
	}
}


void myifft(Ipp32fc *pSeq_T, const Ipp32fc *pSeq_F, int len)
{
	switch(len)
	{
	
		case 64:
			Init_FFT_64(TRUE);
			InverseFFT_64(pSeq_F, pSeq_T);
			Init_FFT_64(FALSE);
			break;
	    case 128:
			Init_FFT_128(TRUE);
			InverseFFT_128(pSeq_F, pSeq_T);
			Init_FFT_128(FALSE);
			break;
		case 256:
			Init_FFT_256(TRUE);
			InverseFFT_256(pSeq_F, pSeq_T);
			Init_FFT_256(FALSE);
			break;
		case 512:
			Init_FFT_512(TRUE);
			InverseFFT_512(pSeq_F, pSeq_T);
			Init_FFT_512(FALSE);
			break;
		case 1024:
			Init_FFT_1024(TRUE);
			InverseFFT_1024(pSeq_F, pSeq_T);
			Init_FFT_1024(FALSE);
			break;
		default: 
			printf("Not supported IFFT length");
			//exit(-1);
	}
}


void myfir(Ipp32fc* pDest, Ipp32fc* pSrc, int signalLen, Ipp32f* firCoef, int firLen)
{
	Ipp32fc* pDlyLine; 
	IppsFIRState_32fc* pState;
	Ipp32fc* pTaps;

	int ii, ippStatus;
	
	pTaps = (Ipp32fc*)calloc(firLen, sizeof(Ipp32fc));
	for(ii=0;ii<firLen;ii++)
	{
		pTaps[ii].re = firCoef[ii];
	}
	pDlyLine = NULL;
		
	ippStatus = ippsFIRInitAlloc_32fc(&pState, pTaps, firLen, pDlyLine);

	// Modified: 22 Oct 2009, Dhaval Dave'
	// For some reason, the FIR operation is giving incorrect results for signalLen>255.
	// Change was made here to do the FIR operation in a loop of length signalLen.
	// This should be tested to see if results are any different.

	//	ippStatus = ippsFIR_32fc(pSrc, pDest, signalLen, pState);
//	for (ii=0; ii<signalLen; ii++)
//	{
//		ippStatus = ippsFIROne_32fc(*pSrc, pDest, pState);
//		pSrc++; pDest++;
//	}
	ippsFIR_32fc(pSrc, pDest, signalLen, pState);

	ippsFIRFree_32fc(pState);

	free(pTaps);
}


//
void bit2byte(unsigned char *byteSeq, unsigned int *bitSeq,  unsigned int bitLen, 
		unsigned char reflect)
{
	unsigned int byteLen, remBitLen;
	unsigned char current_byte;

	byteLen = ceil((float)bitLen/8);

	if(reflect)
	{
		if(bitLen!=(8*byteLen))
		{
			unsigned int ii;

			remBitLen = bitLen - 8*(byteLen-1);
			
			for(ii=0;ii<byteLen-1;ii++)
			{
				current_byte = 0;
				for(unsigned int jj=0;jj<8;jj++)
				{
					current_byte = current_byte + (bitSeq[ii*8+jj]<<jj);
				}
				byteSeq[ii] = current_byte;
			}

			current_byte = 0;
			for(unsigned int jj=0;jj<remBitLen;jj++)
			{
				current_byte = current_byte + (bitSeq[ii*8+jj]<<jj);
			}
			byteSeq[ii] = current_byte;
		}
		else
		{	
			for(unsigned int ii=0;ii<byteLen;ii++)
			{
				current_byte = 0;
				for(unsigned int jj=0;jj<8;jj++)
				{
					current_byte = current_byte + (bitSeq[ii*8+jj]<<jj);
				}
				byteSeq[ii] = current_byte;
			}
		}
	}
	else
	{
		if(bitLen!=(8*byteLen))
		{
			unsigned int ii;

			remBitLen = bitLen - 8*(byteLen-1);
			
			for(ii=0;ii<byteLen-1;ii++)
			{
				current_byte = 0;
				for(unsigned int jj=0;jj<8;jj++)
				{
					current_byte = current_byte + (bitSeq[ii*8+jj]<<(8-jj-1));
				}
				byteSeq[ii] = current_byte;
			}

			current_byte = 0;
			for(unsigned int jj=0;jj<remBitLen;jj++)
			{
				current_byte = current_byte + (bitSeq[ii*8+jj]<<(8-jj-1));
			}
			byteSeq[ii] = current_byte;
		}
		else
		{	
			for(unsigned int ii=0;ii<byteLen;ii++)
			{
				current_byte = 0;
				for(unsigned int jj=0;jj<8;jj++)
				{
					current_byte = current_byte + (bitSeq[ii*8+jj]<<(8-jj-1));
				}
				byteSeq[ii] = current_byte;
			}
		}	
	}
}


void computeLLR(Ipp32f *detLLR, Ipp32fc *signal, Ipp32fc *H, unsigned int len, 
	LTEMODULATION modulate_mode,  Ipp32f noiseVar)
{
	unsigned int moduSize, moduBitNum;
	unsigned int moduSymb[64];
	Ipp32fc moduSignal[64];
	float dist[64];
	float real, imag;
	float LLR0[32], LLR1[32], LLRAll0, LLRAll1;
	
	switch(modulate_mode)
	{
		case MBPSK:
			moduSize = 2;
        	moduBitNum = 1;
			break;
		case MQPSK:
			moduSize = 4;
        	moduBitNum = 2;
			break;
		case M16QAM:
			moduSize = 16;                                                                                                 
        	moduBitNum = 4;
			break;
		case M64QAM:
			moduSize = 64;
        	moduBitNum = 6;
			break;
		default:
			printf("unsupported modulation\n");
			break;
	}

	for(unsigned int ii=0;ii<moduSize;ii++)
	{
		moduSymb[ii] = ii;
	}

	for(unsigned int ii=0;ii<len;ii++)
	{
		LTE_modulate(moduSignal, moduSymb, moduSize, modulate_mode);

		for(unsigned int jj=0;jj<moduSize;jj++)
		{
			real = signal[ii].re - H[ii].re*moduSignal[jj].re + H[ii].im*moduSignal[jj].im;
			imag = signal[ii].im - H[ii].re*moduSignal[jj].im - H[ii].im*moduSignal[jj].re;

			dist[jj] = -(real*real+imag*imag)/noiseVar;	
		}

		for(unsigned kk=0;kk<moduBitNum;kk++)
		{
			unsigned int count0, count1;
			count0 = 0; count1= 0;
			for(unsigned int jj=0;jj<moduSize;jj++)
			{
				if(jj&(1<<(moduBitNum-kk-1)))
				{
					LLR1[count1++] = dist[jj];
				}
				else
				{
					LLR0[count0++] = dist[jj];
				}
			}

			LLRAll0 = compute_log_sum(LLR0, moduSize/2);
			LLRAll1 = compute_log_sum(LLR1, moduSize/2);

			detLLR[ii*moduBitNum+kk] = LLRAll0 - LLRAll1;
		}

	}
}


void LTE_modulate(Ipp32fc* outSignal, unsigned int* inSymb, unsigned int len, 
	LTEMODULATION modulate_mode)
{
	switch(modulate_mode)
	{
		case MBPSK:
		{	Ipp32fc constellation[2] = {{0.707f,0.707f}, {-0.707f,0.707f}};
			for(unsigned int ii=0;ii<len;ii++)
			{
				outSignal[ii] = constellation[inSymb[ii]];
			}
			break;
		}
		case MQPSK:
		{
			Ipp32fc constellation[4] = {{0.707f, 0.707f}, {0.707f, -0.707f},
				{-0.707f, 0.707f}, {-0.707f, -0.707f}};
			for(unsigned int ii = 0; ii<len; ii++)
			{
				outSignal[ii] = constellation[inSymb[ii]];
			}
			break;
		}
		case M16QAM:
		{
			Ipp32fc constellation[16] = {
					{1 / sqrt_10, 1 / sqrt_10},
					{1 / sqrt_10, 3 / sqrt_10},
					{3 / sqrt_10, 1 / sqrt_10},
					{3 / sqrt_10, 3 / sqrt_10},
					{1 / sqrt_10, -1 / sqrt_10},
					{1 / sqrt_10, -3 / sqrt_10},
					{3 / sqrt_10, -1 / sqrt_10},
					{3 / sqrt_10, -3 / sqrt_10},
					{-1 / sqrt_10, 1 / sqrt_10},
					{-1 / sqrt_10, 3 / sqrt_10},
					{-3 / sqrt_10, 1 / sqrt_10},
					{-3 / sqrt_10, 3 / sqrt_10},
					{-1 / sqrt_10, -1 / sqrt_10},
					{-1 / sqrt_10, -3 / sqrt_10},
					{-3 / sqrt_10, -1 / sqrt_10},
					{-3 / sqrt_10, -3 / sqrt_10}};
			for(unsigned int ii = 0; ii < len; ii++) {
				outSignal[ii] = constellation[inSymb[ii]];
			}
			break;
		}
		case M64QAM:
		{
			Ipp32fc constellation[64] = {
					{3 / sqrt_42, 3 / sqrt_42},
					{3 / sqrt_42, 1 / sqrt_42},
					{1 / sqrt_42, 3 / sqrt_42},
					{1 / sqrt_42, 1 / sqrt_42},
					{3 / sqrt_42, 5 / sqrt_42},
					{3 / sqrt_42, 7 / sqrt_42},
					{1 / sqrt_42, 5 / sqrt_42},
					{1 / sqrt_42, 7 / sqrt_42},

					{5 / sqrt_42, 3 / sqrt_42},
					{5 / sqrt_42, 1 / sqrt_42},
					{7 / sqrt_42, 3 / sqrt_42},
					{7 / sqrt_42, 1 / sqrt_42},
					{5 / sqrt_42, 5 / sqrt_42},
					{5 / sqrt_42, 7 / sqrt_42},
					{7 / sqrt_42, 5 / sqrt_42},
					{7 / sqrt_42, 7 / sqrt_42},

					{3 / sqrt_42, -3 / sqrt_42},
					{3 / sqrt_42, -1 / sqrt_42},
					{1 / sqrt_42, -3 / sqrt_42},
					{1 / sqrt_42, -1 / sqrt_42},
					{3 / sqrt_42, -5 / sqrt_42},
					{3 / sqrt_42, -7 / sqrt_42},
					{1 / sqrt_42, -5 / sqrt_42},
					{1 / sqrt_42, -7 / sqrt_42},

					{5 / sqrt_42, -3 / sqrt_42},
					{5 / sqrt_42, -1 / sqrt_42},
					{7 / sqrt_42, -3 / sqrt_42},
					{7 / sqrt_42, -1 / sqrt_42},
					{5 / sqrt_42, -5 / sqrt_42},
					{5 / sqrt_42, -7 / sqrt_42},
					{7 / sqrt_42, -5 / sqrt_42},
					{7 / sqrt_42, -7 / sqrt_42},

					{-3 / sqrt_42, 3 / sqrt_42},
					{-3 / sqrt_42, 1 / sqrt_42},
					{-1 / sqrt_42, 3 / sqrt_42},
					{-1 / sqrt_42, 1 / sqrt_42},
					{-3 / sqrt_42, 5 / sqrt_42},
					{-3 / sqrt_42, 7 / sqrt_42},
					{-1 / sqrt_42, 5 / sqrt_42},
					{-1 / sqrt_42, 7 / sqrt_42},

					{-5 / sqrt_42, 3 / sqrt_42},
					{-5 / sqrt_42, 1 / sqrt_42},
					{-7 / sqrt_42, 3 / sqrt_42},
					{-7 / sqrt_42, 1 / sqrt_42},
					{-5 / sqrt_42, 5 / sqrt_42},
					{-5 / sqrt_42, 7 / sqrt_42},
					{-7 / sqrt_42, 5 / sqrt_42},
					{-7 / sqrt_42, 7 / sqrt_42},

					{-3 / sqrt_42, -3 / sqrt_42},
					{-3 / sqrt_42, -1 / sqrt_42},
					{-1 / sqrt_42, -3 / sqrt_42},
					{-1 / sqrt_42, -1 / sqrt_42},
					{-3 / sqrt_42, -5 / sqrt_42},
					{-3 / sqrt_42, -7 / sqrt_42},
					{-1 / sqrt_42, -5 / sqrt_42},
					{-1 / sqrt_42, -7 / sqrt_42},

					{-5 / sqrt_42, -3 / sqrt_42},
					{-5 / sqrt_42, -1 / sqrt_42},
					{-7 / sqrt_42, -3 / sqrt_42},
					{-7 / sqrt_42, -1 / sqrt_42},
					{-5 / sqrt_42, -5 / sqrt_42},
					{-5 / sqrt_42, -7 / sqrt_42},
					{-7 / sqrt_42, -5 / sqrt_42},
					{-7 / sqrt_42, -7 / sqrt_42},

			};
			for(unsigned int ii = 0; ii < len; ii++) {
				outSignal[ii] = constellation[inSymb[ii]];
			}
			break;
		}
		default:
			printf("unsupported modulation\n");
			break;
	}
}



float compute_log_sum(float *input, int length)
{
    int i;
    float max, temp, tmp1;

	if(length==1)
	{
		return(input[0]); 
	}
	else
	{
	    max=input[0];

	    for (i=1; i<length; i++)
	        if (max < input[i]) max=input[i];

        temp=0;
        for (i=0; i<length; i++)
        {
        	//peng 050106
        	tmp1 = input[i]-max;	
      //    	if(tmp1>-20)
            		temp+= exp(tmp1);
		}

	    return(max + log(temp));
	}
}



void linearInterplate_fc(Ipp32fc* outSeq, Ipp32fc* inSeq, Ipp16u* inIdx, 
	unsigned int inLen, unsigned int startIdx0, unsigned int endIdx0)
{
	float realCoef, imagCoef;
	int pos, startIdx, endIdx, done;
	Ipp32fc fcTmp;

	startIdx = startIdx0;
	endIdx = endIdx0;

	pos = startIdx;
	
	done = 0;
	for(int ii=0;ii<inLen-1;ii++)
	{
		realCoef= (inSeq[ii+1].re-inSeq[ii].re)/(inIdx[ii+1]-inIdx[ii]);
		imagCoef= (inSeq[ii+1].im-inSeq[ii].im)/(inIdx[ii+1]-inIdx[ii]);

		if((ii==0)&&(pos<inIdx[0]))
		{
			fcTmp = inSeq[ii];
			if(inIdx[0]<=endIdx)
				outSeq[inIdx[0]-startIdx] = fcTmp;
			for(int jj=inIdx[0]-1;jj>=(int)startIdx;jj--)
			{
				fcTmp.re = fcTmp.re - realCoef;
				fcTmp.im = fcTmp.im - imagCoef;
				if(jj<=endIdx)
					outSeq[jj-startIdx] = fcTmp;
			}
			pos = inIdx[0]+1;

			if(pos>endIdx)
			{
				done=1;
				break;
			}
		}
		
		if(pos>inIdx[ii+1])
		{
			continue;
		}
		else //inIdx[ii]<pos<=inIdx[ii+1]
		{
			fcTmp = inSeq[ii+1];
			if(inIdx[ii+1]<=endIdx)
				outSeq[inIdx[ii+1]-startIdx] = fcTmp;
			for(int jj=inIdx[ii+1]-1;jj>=pos;jj--)
			{
				fcTmp.re = fcTmp.re - realCoef;
				fcTmp.im = fcTmp.im - imagCoef;
				if(jj<=endIdx)
					outSeq[jj-startIdx] = fcTmp;
			}
			pos = inIdx[ii+1]+1;

			if(pos>endIdx)
			{
				done=1;
				break;
			}

		}
	}

	if(done==0)
	{
		for(unsigned int jj=pos;jj<=endIdx;jj++)
		{
			outSeq[jj-startIdx].re = outSeq[jj-startIdx-1].re+realCoef;
			outSeq[jj-startIdx].im = outSeq[jj-startIdx-1].im+imagCoef;
		}
		
	}
}


//rate 1/3 CC codes used by LTE only
void LTE_CC_decoding(unsigned int *bitSeq, Ipp32f* inLLR, unsigned int inLen)
{
	unsigned int genPoly[21] = 
		  {1, 0, 1, 1, 0, 1, 1,
           1, 1, 1, 1, 0, 0, 1,
           1, 1, 1, 0, 1, 0, 1};


	Ipp32f* inLLR2 = ippsMalloc_32f(inLen);

	for(unsigned int ii=0;ii<inLen/3;ii++)
	{
		inLLR2[ii*3] = -inLLR[ii]; 
		inLLR2[ii*3+1] = -inLLR[inLen/3+ii]; 
		inLLR2[ii*3+2] = -inLLR[2*inLen/3+ii]; 
	}

	cc_decoding(bitSeq, inLLR2, inLen, genPoly, 3, 7);

/*	for(unsigned int ii=0;ii<20;ii++)
	{
		for(unsigned int jj=0;jj<6;jj++)
			printf("%f ", inLLR2[ii*6+jj]);
		printf("\n");
	}
	
	printf("\n");
	printf("\n");
	printf("\n");

	for(unsigned int ii=0;ii<8;ii++)
	{
		for(unsigned int jj=0;jj<5;jj++)
			printf("%d ", bitSeq[ii*5+jj]);
		printf("\n");
	}*/
	
	ippsFree(inLLR2);
}


void multMatVect_fc(Ipp32fc *destVec,  Ipp32fc *srcMat, unsigned int rows, 
	unsigned int cols, Ipp32fc *srcVec) 
{
	Ipp32fc fcTmp1, fcTmp2;
	
	for(unsigned int ii=0;ii<rows;ii++)
	{	
		destVec[ii].re = 0; destVec[ii].im = 0; 
		
		for(unsigned int jj=0;jj<cols;jj++)
		{
			fcTmp1.re = srcMat[ii*cols+jj].re;
			fcTmp1.im = srcMat[ii*cols+jj].im;
			ippsMul_32fc(&fcTmp1, srcVec+jj, &fcTmp2, 1);
			destVec[ii].re+=fcTmp2.re;
			destVec[ii].im+=fcTmp2.im;
		}
	}
}

void multMatVect_fc_fast(Ipp32fc *destVec, Ipp32fc *srcMat, unsigned int rows,
	unsigned int cols, Ipp32fc *srcVec) {
	Ipp32fc fcTmp1, fcTmp2;

	static ipp_32fc_array tmp(cols);
	if(tmp.length() < cols)
		tmp.reset(cols);

	for(int i = 0; i < rows; ++i) {
		ipp_helper::check_status(ippsMul_32fc(&srcMat[i*cols], srcVec, tmp.get(), cols));
		ipp_helper::check_status(ippsSum_32fc(tmp.get(), cols, &destVec[i], ippAlgHintAccurate));
	}
}



void stDiversityDet(Ipp32f* detLLR, Ipp32fc* signalF, Ipp32fc* H, unsigned int subcarrierNum, 
	unsigned int antNum,  LTEMODULATION modulate_mode,  Ipp32f *noiseVar)
{	
	Ipp32f noiseVar1;

	noiseVar1 = 0;
	for(unsigned int ii=0;ii<antNum;ii++)
	{
		noiseVar1+=noiseVar[ii];
	}
	noiseVar1/=antNum;
		
	switch(antNum)
	{
		case 1:
			computeLLR(detLLR, signalF, H, subcarrierNum, modulate_mode, noiseVar1);
			break;
		case 2:
		{
			Ipp32fc *H2 = ippsMalloc_32fc(subcarrierNum);
			Ipp32fc *H3 = ippsMalloc_32fc(subcarrierNum);
			Ipp32fc *signalF2 = ippsMalloc_32fc(subcarrierNum);
			float real0, imag0, real1, imag1;
			for(unsigned int ii=0;ii<subcarrierNum;ii+=2)
			{
				real0 = (H[ii].re + H[ii+1].re)/2; 
				imag0 = (H[ii].im + H[ii+1].im)/2; 
				real1 = (H[ii+subcarrierNum].re + H[ii+1+subcarrierNum].re)/2; 
				imag1 = (H[ii+subcarrierNum].im + H[ii+1+subcarrierNum].im)/2;

				H3[ii].re = sqrt(real0*real0+real1*real1+imag0*imag0+imag1*imag1);
				H3[ii].im = 0;
				H3[ii+1].re = H3[ii].re;
				H3[ii+1].im = 0;

				signalF2[ii].re = (real0*signalF[ii].re+imag0*signalF[ii].im+
					real1*signalF[ii+1].re+imag1*signalF[ii+1].im)/H3[ii].re;

				signalF2[ii].im = (real0*signalF[ii].im-imag0*signalF[ii].re-
					real1*signalF[ii+1].im+imag1*signalF[ii+1].re)/H3[ii].re;

				signalF2[ii+1].re = (real0*signalF[ii+1].re+imag0*signalF[ii+1].im-
					real1*signalF[ii].re-imag1*signalF[ii].im)/H3[ii].re;

				signalF2[ii+1].im = (real0*signalF[ii+1].im-imag0*signalF[ii+1].re+
					real1*signalF[ii].im-imag1*signalF[ii].re)/H3[ii].re;	
			}

			computeLLR(detLLR, signalF2, H3, subcarrierNum, modulate_mode, noiseVar1);
			
			ippsFree(H2);
			ippsFree(H3);
			ippsFree(signalF2);
			break;
		}
		case 4:
		{
			Ipp32fc *H1 = ippsMalloc_32fc(2*subcarrierNum);
			ippsZero_32fc(H1, 2*subcarrierNum);
			Ipp32fc *H2 = ippsMalloc_32fc(subcarrierNum);
			Ipp32fc *H3 = ippsMalloc_32fc(subcarrierNum);
			Ipp32fc *signalF2 = ippsMalloc_32fc(subcarrierNum);
			float real0, imag0, real1, imag1;

			for(unsigned int ii=subcarrierNum;ii<2*subcarrierNum;ii++)
			{
				H1[ii] = H[ii+subcarrierNum];
			}
			for(unsigned int ii=0;ii<subcarrierNum;ii+=4)
			{
				H1[2+ii] = H[subcarrierNum+2+ii];
				H1[3+ii] = H[subcarrierNum+3+ii];

				H1[subcarrierNum+2+ii] = H[3*subcarrierNum+2+ii];
				H1[subcarrierNum+3+ii] = H[3*subcarrierNum+3+ii];
			}
			
			for(unsigned int ii=0;ii<subcarrierNum;ii+=2)
			{
				real0 = (H1[ii].re + H1[ii+1].re)/2; 
				imag0 = (H1[ii].im + H1[ii+1].im)/2; 
				real1 = (H1[ii+subcarrierNum].re + H1[ii+1+subcarrierNum].re)/2; 
				imag1 = (H1[ii+subcarrierNum].im + H1[ii+1+subcarrierNum].im)/2;

				H3[ii].re = sqrt(real0*real0+real1*real1+imag0*imag0+imag1*imag1);
				H3[ii].im = 0;
				H3[ii+1].re = H3[ii].re;
				H3[ii+1].im = 0;

				signalF2[ii].re = (real0*signalF[ii].re+imag0*signalF[ii].im+
					real1*signalF[ii+1].re+imag1*signalF[ii+1].im)/H3[ii].re;
				signalF2[ii].im = (real0*signalF[ii].im-imag0*signalF[ii].re-
					real1*signalF[ii+1].im+imag1*signalF[ii+1].re)/H3[ii].re;

				signalF2[ii+1].re = (real0*signalF[ii+1].re+imag0*signalF[ii+1].im-
					real1*signalF[ii].re-imag1*signalF[ii].im)/H3[ii].re;
				signalF2[ii+1].im = (real0*signalF[ii+1].im-imag0*signalF[ii+1].re+
					real1*signalF[ii].im-imag1*signalF[ii].re)/H3[ii].re;	
			}

			computeLLR(detLLR, signalF2, H3, subcarrierNum, modulate_mode, noiseVar1);
			
			ippsFree(H1);
			ippsFree(H2);
			ippsFree(H3);
			ippsFree(signalF2); 
			break;
		}
		default:
			printf("Unsupported antenna numbers\n");
			break;
	}

	
}



void softDeSrambling(Ipp32f* outLLR, Ipp32f* inLLR, unsigned int len, 
	unsigned int *scramblingBits)
{
	for(unsigned int ii=0;ii<len;ii++)
	{
		if(scramblingBits[ii])
			outLLR[ii] = -inLLR[ii];
	    else
	        outLLR[ii] = inLLR[ii];
	}
}


void *allocate(unsigned N, unsigned size)
{

    void    *p;

    if ((p = (void *) calloc(N,size)) == NULL)
    {
        printf("** Unable to allocate vector of chars..");
    }
		
    memset(p, 0x00, N*size);

    return p;

}


}