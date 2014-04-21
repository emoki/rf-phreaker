#include <stdlib.h>
#include <math.h>
#include <memory.h>

#include "lte_synchronization.h"
#include "lte_fft.h"
#include "lte_pss.h"
#include "lte_common.h"

namespace rf_phreaker {

#define _LTE_PROC_MAX_NUM_PSCH_PEAKS	100
#define WINDIPP_MEM_ALIGN_SIZE			32


// for use for reference signals
LteFFT FftRS(8, IPP_FFT_DIV_FWD_BY_N);


Ipp32f *totalEnergy=NULL, avgPower=0.f,energy_ss21[128],energy_ss22[128],total_energy_ss21,total_energy_ss22;
Ipp32fc PSS_Buffer[2*3*128 + WINDIPP_MEM_ALIGN_SIZE*2];
Ipp32fc SSS_Buffer[2*3*168*128 + WINDIPP_MEM_ALIGN_SIZE*2];
Ipp32fc *PSS_seqT[3], *PSS_seqF[3];
Ipp32fc *SSS_seqT[168][3], *SSS_seqF[168][3];

void generate_PSS(Ipp32fc *PSS_seq_T, Ipp32fc *PSS_seq_F, int len, int id);

void generate_SSS(Ipp32fc *SSS_seq, int cellID1, int cellID2);

void getChannelEstFromSSS(Ipp32fc *H_est, const Ipp32fc *signal192, unsigned int PSSStartSample,
		int halfFrameFlag, unsigned int cellID1, unsigned int cellID2, int PSS_No,
		const CYCLICPREFIX cyclicPrefixMode);

void computeSSSStrength(const Ipp32fc *signal192, unsigned int numSamplesToProcess,
		const unsigned int* pHalfFrameFlag, const CYCLICPREFIX *pCyclicPrefixMode, const unsigned int *pPSSStartSample,
		unsigned int numSSS, LTEProc_CorrRecordType *pSSCHCorrRecord);
						

void sampleRateConv2(Ipp32fc *signal192, Ipp32fc *signal384, unsigned int signalLength, 
		double *pDelayTime,int sampling_factor)
{
	Ipp32f fir1[24]={
		-0.000673657479391135f, -0.000575239214281984f, 0.00491737714592471f, 0.0188657352410765f, 0.0327237428779071f, 0.0259822905778505f,
		-0.0125594088000091f, -0.0574381674363662f, -0.0507182204372469f, 0.0479116521719395f, 0.207175659160200f, 0.330205583916852f,
		0.330205583916852f, 0.207175659160200f, 0.0479116521719395f, -0.0507182204372469f, -0.0574381674363662f, -0.0125594088000091f,
		0.0259822905778505f, 0.0327237428779071f, 0.0188657352410765f, 0.00491737714592471f, -0.000575239214281984f, -0.000673657479391135f
	};

	int firLen = 24;
	int phase;
	Ipp32fc *signal1;
	int signalLength1;
	//double sampleRate=3.84e6;//--RB
	double sampleRate=7.68e6;

	switch (sampling_factor)
	{
	case 2:
		sampleRate = 3.84e6;
		break;
	case 4:
		sampleRate = 7.68e6;
		break;
	case 8:
		sampleRate = 15.36e6;
		break;
	
	
	}
	
	signal1 = (Ipp32fc*)calloc(signalLength+firLen-1, sizeof(Ipp32fc));
	phase = 0;

	myfir(signal1, signal384, signalLength, fir1, firLen); //??

	//ippsSampleDown_32fc(signal1, signalLength, signal192, &signalLength1, 2, &phase);

	ippsSampleDown_32fc(signal1, signalLength, signal192, &signalLength1, sampling_factor, &phase);

	*pDelayTime = firLen/2/sampleRate;
	
	
	free(signal1);
	
}


class LteProcInitializer
{
public:
	LteProcInitializer();
protected:
	const LtePrimarySyncSequence Pss192;
};
LteProcInitializer::LteProcInitializer():
Pss192(1920)
{
	//TODO: currently PSS is normalized so that sum(pss^2) = 1.0000
	// We want sum(pss^2) = 1/128 = .0078, so let's divide pss by sqrt(128)
	// And then we will want to change the power/energy calculations as well as
	// what we do with corrs to determine power/AvgDV.
	int psid, ssid;

	Ipp32fc *pssPtr = (Ipp32fc*)ippAlignPtr(PSS_Buffer, WINDIPP_MEM_ALIGN_SIZE);
	Ipp32fc *sssPtr = (Ipp32fc*)ippAlignPtr(SSS_Buffer, WINDIPP_MEM_ALIGN_SIZE);

	for(psid=0; psid<3; psid++)
	{
		PSS_seqT[psid] = pssPtr;
		ippsCopy_32fc(Pss192[psid], PSS_seqT[psid], 128);
		pssPtr += 128;

		PSS_seqF[psid] = pssPtr;
		ippsCopy_32fc(Pss192.GetSeqF(psid), PSS_seqF[psid], 128);
		pssPtr += 128;

		generate_PSS(PSS_seqT[psid], PSS_seqF[psid], 128, psid);

		for (ssid=0; ssid<168; ssid++)
		{
			SSS_seqT[ssid][psid] = sssPtr;
			sssPtr += 128;
			SSS_seqF[ssid][psid] = sssPtr;
			sssPtr += 128;
			generate_SSS(SSS_seqF[ssid][psid], ssid, psid);
		}
	}
}
LteProcInitializer TempPI;


int getSignalPower(const Ipp32fc *signal384, unsigned int signalLength)
{
	return 0;
}


void getHalfFrameTiming(LTEProc_CorrRecordType *pPSCHCorrRecord,
		unsigned int *pNumPschPeaks, const Ipp32fc *signal192, 
		unsigned int NumHalfFramesToProcess)
{
	const unsigned int numSamplesHalfFrame192 = 9600;

	Ipp32f corAll[numSamplesHalfFrame192*3], cor1[numSamplesHalfFrame192], maxVal, fTmp1, val1[_LTE_PROC_MAX_NUM_PSCH_PEAKS];
	unsigned int symb, id, ii, jj, num, maxIdx, idx1[_LTE_PROC_MAX_NUM_PSCH_PEAKS],  sortIdx[_LTE_PROC_MAX_NUM_PSCH_PEAKS], idx2;
	unsigned int totalSamples, pidx;
	int startPos;
	Ipp32fc cor0[numSamplesHalfFrame192];


	unsigned int corAllLength = sizeof(corAll)/sizeof(corAll[0]);

	// Calculate the power spectrum of the signal as the first step towards
	// (1) calculating the total average power of the input and
	// (2) calculating the 128-sample moving-window energy to be used for correlation normalization
	totalSamples = NumHalfFramesToProcess*numSamplesHalfFrame192;
	totalEnergy = ippsMalloc_32f(totalSamples+128);
	ippsPowerSpectr_32fc(signal192, totalEnergy, totalSamples+128);
	ippsMean_32f(totalEnergy, totalSamples, &avgPower, ippAlgHintAccurate);
	for (pidx=0; pidx<totalSamples; pidx++)
	{
		ippsSum_32f(&totalEnergy[pidx], 128, &totalEnergy[pidx], ippAlgHintAccurate);
	}

	ippsZero_32f(corAll, corAllLength);

	// Calculate the running non-coherent sum of the xcorr over each subframe
	for(symb=0;symb<NumHalfFramesToProcess;symb++)
	{
		startPos = symb*numSamplesHalfFrame192;

		for(id=0;id<3;id++)
		{
			// get each of the PSCH cross corrs
			// and normalize the xcorr energy by the total energy (in the xcorr window).
			// Accumulate the running sum of the normalized xcorr for each half-frame processed.
			ippsCrossCorr_32fc(PSS_seqT[id], 128, signal192+startPos,
				numSamplesHalfFrame192+128, cor0, numSamplesHalfFrame192, 0);
			ippsPowerSpectr_32fc(cor0, cor1, numSamplesHalfFrame192);
			ippsDiv_32f_I(totalEnergy+startPos, cor1, numSamplesHalfFrame192);
			ippsAdd_32f_I(cor1, &corAll[id*numSamplesHalfFrame192], numSamplesHalfFrame192);
		}
	}
	ippsDivC_32f_I((Ipp32f)NumHalfFramesToProcess, corAll, corAllLength);

	ippsMaxIndx_32f(corAll, corAllLength , &maxVal, (int *)&maxIdx);

	pPSCHCorrRecord[0].ID = maxIdx/numSamplesHalfFrame192;
	pPSCHCorrRecord[0].StartSampleNum = maxIdx%numSamplesHalfFrame192;
	*pNumPschPeaks = 1;

	fTmp1 = maxVal/9.0f;
	if(fTmp1 < 0.05f) fTmp1 = 0.05f;
	//fTmp1 = 0.02f; //RB: Works for Matlab 5 Mhz File

	//if (maxVal <= 0.25f) fTmp1 = 0.25f;
	//else fTmp1 = maxVal/3; //Used as threshold to find peak
	//fTmp1 = .3f; //Used as threshold to find peak

	// Ignore any peak one sample before or after the max peak,
	// unless of course in the rare instance that the max occurs
	// exactly at the beginning or end of the half-frame.
	if (pPSCHCorrRecord[0].StartSampleNum > 0) corAll[maxIdx-1] = 0;
	if (pPSCHCorrRecord[0].StartSampleNum < (numSamplesHalfFrame192-1)) corAll[maxIdx+1] = 0;

	// Now find the all peaks above the threshold.
	// Is it possible that this detects multi-paths?
	jj = 0;
	for(ii=0; ii<corAllLength; ii++)
	{
		if(corAll[ii]>fTmp1)
		{
			val1[jj] = corAll[ii];
			idx1[jj] = ii;
			jj++;
			if ( jj == _LTE_PROC_MAX_NUM_PSCH_PEAKS ) break;
		}
	}	
	num = jj;

	// Remember we must initialize the first element of the idx Dst = 0.
	*sortIdx = 0;
	ippsSortIndexDescend_32f_I(val1,  (int *)sortIdx, num);

	for(ii=1;ii<num;ii++)
	{
		idx2 = idx1[sortIdx[ii]];
		pPSCHCorrRecord[ii].ID = idx2/numSamplesHalfFrame192;
		pPSCHCorrRecord[ii].StartSampleNum = idx2%numSamplesHalfFrame192;
	}

	// TODO: consider calculating avgpower directly above by using ippsMean instead of ippsSum,
	// or normalize the PSS template by 128 (using FFT scaling perhaps),
	// or divide the RMS normCorr by 128 above.
	// Now calculate the average rms power for the found peaks
	for(ii=0;ii<num;ii++)
	{
		pPSCHCorrRecord[ii].RMSCorr = 0;
		for(symb=0;symb<NumHalfFramesToProcess;symb++)
		{
			startPos = symb*numSamplesHalfFrame192 + pPSCHCorrRecord[ii].StartSampleNum;
			pPSCHCorrRecord[ii].RMSCorr += (CORRELATIONTYPE)totalEnergy[startPos];
		}
		pPSCHCorrRecord[ii].NormCorr = (CORRELATIONTYPE)sqrt(corAll[idx1[sortIdx[ii]]]);
		//printf("PSS Norm Corr == %f\n",corAll[idx1[sortIdx[ii]]]);
		pPSCHCorrRecord[ii].RMSCorr = pPSCHCorrRecord[ii].NormCorr *
			(CORRELATIONTYPE)sqrt(pPSCHCorrRecord[ii].RMSCorr / (NumHalfFramesToProcess*128));
	}

	*pNumPschPeaks = num;
	ippsFree(totalEnergy);
}



void getCPMode(CYCLICPREFIX *pCyclicPrefixMode, Ipp32fc *signal192, unsigned int PSSStartSample, 
		unsigned int numSamplesToProcess)
{
	int start, halfFrameSamples, CP_len_min, CP_len_max, signalStart, offset;
	unsigned int kk, ii, count;
	Ipp32fc cor[34], apt0, cor0;
	Ipp32f apt[34], normCor;

	start = 0;
	halfFrameSamples = 9600;
	CP_len_min = 9;
	CP_len_max = 32;
	signalStart = PSSStartSample;

	for(ii=0;ii<34;ii++)
	{
		cor[ii].re = 0;
		cor[ii].im = 0;
		apt[ii] = 0;
	}

	for(kk=0;kk<numSamplesToProcess;kk++)
	{
		for(ii=0;ii<34;ii++)
		{
			offset = -((int)ii);

			ippsCrossCorr_32fc(signal192+signalStart+offset+128, CP_len_min, 
				signal192+signalStart+offset, CP_len_min, &cor0, 1, 0);
			ippsCrossCorr_32fc(signal192+signalStart+offset, CP_len_min, 
				signal192+signalStart+offset, CP_len_min, &apt0, 1, 0);

			cor[ii].re = cor[ii].re + cor0.re;
			cor[ii].im = cor[ii].im + cor0.im;
			apt[ii] = apt[ii] + (Ipp32f)sqrt(apt0.re*apt0.re+apt0.im*apt0.im);
		}
		
		signalStart = signalStart + halfFrameSamples;
	}

	count = 0;
	for(ii=0;ii<34;ii++)
	{
		normCor = (Ipp32f)sqrt(cor[ii].re*cor[ii].re+cor[ii].im*cor[ii].im)/apt[ii];
		if(normCor>0.7)
			count++;
	}

	if(count>24)
		*pCyclicPrefixMode = Extended;
	else
		*pCyclicPrefixMode = Normal;
	
}


void getChannelEstFromPSS(Ipp32fc *H_est, Ipp32fc *signal192, unsigned int PSSStartSample, 
		unsigned int cellID2, int PSS_No, CYCLICPREFIX cyclicPrefixMode, int freqOffset)
{
	int curCPLen, signalStart;
	Ipp32fc signal1[128], signal2[128];
		
	if(cyclicPrefixMode==Normal)
		curCPLen = 9;
	else
		curCPLen = 32;

	signalStart = PSSStartSample + PSS_No*9600;

	myfft(signal1, signal192+signalStart, 128);
	myfftshift(signal2, signal1, 128);

	ippsDiv_32fc(&(PSS_seqF[cellID2][33]), signal2+33+freqOffset, H_est, 31);
	ippsDiv_32fc(&(PSS_seqF[cellID2][65]), signal2+65+freqOffset, H_est+31, 31);

	// TODO:: DFT based channel estimation
	
	
}


void getChannelEstFromSSS(Ipp32fc *H_est, const Ipp32fc *signal192, unsigned int PSSStartSample,
		int halfFrameFlag, unsigned int cellID1, unsigned int cellID2, int PSS_No,
		const CYCLICPREFIX cyclicPrefixMode)
{
	int curCPLen, signalStart, offset;
	Ipp32fc signal1[128], signal2[128];
		
	if(cyclicPrefixMode==Normal)
		curCPLen = 9;
	else
		curCPLen = 32;

	offset = -curCPLen-128;

	signalStart = PSSStartSample + PSS_No*9600 + offset;

	myfft(signal1, signal192+signalStart, 128);
	myfftshift(signal2, signal1, 128);

	ippsCopy_32fc(signal2+33, H_est, 31);
	ippsCopy_32fc(signal2+65, H_est+31, 31);
}

#define _USE_HEST 0
#define _USE_SSCH_REAL 0
void getFrameTiming(Ipp32fc *signal192, unsigned int NumHalfFramesToProcess,
		LTEProc_CorrRecordType *pPSCHCorrRecord, unsigned int numPschPeaks,
		LTEProc_CorrRecordType *pSSCHCorrRecord, unsigned int *pNumCellID,
		CYCLICPREFIX *pCyclicPrefixMode)
{
	int curCPLen, signalStart, signalStart2,signalStart3, offset;
	Ipp32f *cor, ftmp, maxVal, H2_PSS, H2_PSS2[2], threshold, val1[50], PSchStrength[100],cor_mean,cor_var,cor_sum;
	Ipp64f dNorm;
	Ipp32fc signal1[128], signal21[128], signal22[128], signal3[62],signal33[62], H_est1[62], signal4[62],signal44[64] ,fcTmp,signal3_1[62],signal4_1[62];
	Ipp32fc *SSS_seq;
	unsigned int ii, jj, kk, kk2, maxIdx, cid2, cpMode, pschID, idx2,
		sschID, cellIDAll, numCellID, idx1[50], sortIdx[50], numIdx, peakFlag, 
		repeatedFlag, halfFrameFlag[100], pPSSStartSample2[100];
	unsigned int CPLen[2];
	CYCLICPREFIX cyclicPrefixMode[2];
	LTEProc_CorrRecordType *currPschRecord;

	CPLen[0] = 9;
	CPLen[1] = 32;
	cyclicPrefixMode[0] = Normal;
	cyclicPrefixMode[1] = Extended;
	
	cor = ippsMalloc_32f(168*2*2);
	numCellID = 0;

	currPschRecord = pPSCHCorrRecord;
	for(cid2=0;cid2<numPschPeaks;cid2++)
	{
		ippsZero_32f(cor, 168*2*2);
		pschID = currPschRecord->ID;
		signalStart = currPschRecord->StartSampleNum;

		for(cpMode=0;cpMode<2;cpMode++)
		{
			curCPLen = CPLen[cpMode];
			offset = -curCPLen - 128;

			H2_PSS = 0;
			for(ii=0;ii<NumHalfFramesToProcess/2;ii++)
			{
				signalStart2 = signalStart + ii*19200 + offset;
				myfft(signal1, signal192+signalStart2, 128);
				myfftshift(signal21, signal1, 128);

			ippsPowerSpectr_32fc(signal21, energy_ss21, 128);
			//ippsPowerSpectr_32fc(signal192+signalStart2, energy_ss21, 128);
			ippsSum_32f(energy_ss21, 128, &total_energy_ss21, ippAlgHintAccurate);

				signalStart2 = signalStart2+9600;
				//signalStart3 = signalStart2+9600;
				myfft(signal1, signal192+signalStart2, 128);
				//myfft(signal1, signal192+signalStart3, 128);
				myfftshift(signal22, signal1, 128);

			ippsPowerSpectr_32fc(signal22, energy_ss22, 128);
			//ippsPowerSpectr_32fc(signal192+signalStart2, energy_ss22, 128);
			ippsSum_32f(energy_ss22, 128, &total_energy_ss22, ippAlgHintAccurate);

				for(jj=0;jj<31;jj++)
				{
					signal3[jj] = signal21[33+jj];
					signal3[jj+31] = signal21[65+jj];
				}

				// Note there that we get PSCH channel est. for both normal/extended CP
				// but since we are referencing relative to the max PSCH corr, does it matter
				// what the CP is?  shouldn't the estimate come from the same part of the signal?
				getChannelEstFromPSS(H_est1, signal192, signalStart, pschID, 
					2*ii, cyclicPrefixMode[cpMode], 0); 

				ftmp = 0;
				//for(jj=0;jj<62;jj++)
				//{
				//	ftmp += H_est1[jj].re*H_est1[jj].re+H_est1[jj].im*H_est1[jj].im;
				//}
				//H2_PSS += ftmp;
				dNorm = 0;
				ippsNorm_L2_32fc64f(H_est1, 62, &dNorm);
				H2_PSS += (Ipp32f)(dNorm * dNorm);
				//ippsNormalize_32fc(H_est1, H_est2, 62, 0, ftmp);

				for(jj=0;jj<168;jj++)
				{
					SSS_seq = SSS_seqF[jj][pschID];

					for(kk=0;kk<2;kk++)
					{
#if _USE_HEST > 0
						ippsMul_32fc(SSS_seq+kk*62, H_est1, signal4, 62);
#else
						ippsCopy_32fc(SSS_seq+kk*62, signal4, 62);

						
#endif
						ippsCrossCorr_32fc(signal3, 62, signal4, 62, &fcTmp, 1, 0);

						//myifft(signal44,signal4,64);
						//ippsCrossCorr_32fc(signal192+signalStart2, 62, signal44, 62, &fcTmp, 1, 0);

#if _USE_SSCH_REAL > 0
						cor[kk*168+jj] += fcTmp.re;
#else
						cor[kk*168+jj] += (fcTmp.re*fcTmp.re + fcTmp.im*fcTmp.im);

						//Parseval Theorem - Scaling by the factor of Sequence lenght when its done in the freq domain - Raj
						cor[kk*168+jj] = cor[kk*168+jj] /(total_energy_ss21*62);
						//if((cor[kk*168+jj]) > 20)
						//printf("SSS Corr signal SS1 = %f\n",cor[kk*168+jj]);
#endif
					}
				}


				for(jj=0;jj<31;jj++)
				{
					signal3[jj] = signal22[33+jj];
					signal3[jj+31] = signal22[65+jj];
				}

				getChannelEstFromPSS(H_est1, signal192, signalStart, pschID, 
					2*ii+1, cyclicPrefixMode[cpMode], 0); 

				ftmp = 0;
				//for(jj=0;jj<62;jj++)
				//{
				//	ftmp += H_est1[jj].re*H_est1[jj].re+H_est1[jj].im*H_est1[jj].im;
				//}
				//H2_PSS += ftmp;
				dNorm = 0;
				ippsNorm_L2_32fc64f(H_est1, 62, &dNorm);
				H2_PSS += (Ipp32f)(dNorm * dNorm);
				//ippsNormalize_32fc(H_est1, H_est2, 62, 0, ftmp);

				for(jj=0;jj<168;jj++)
				{
					SSS_seq = SSS_seqF[jj][pschID];

					for(kk=0;kk<2;kk++)
					{
#if _USE_HEST > 0
						ippsMul_32fc(SSS_seq+kk*62, H_est1, signal4, 62);
#else
						ippsCopy_32fc(SSS_seq+kk*62, signal4, 62);
					    //for(int jj=0;jj<62;jj++)
						//{
						//	(signal4+jj)->re = 	(signal4+jj)->re/10;
						//    (signal4+jj)->im =   (signal4+jj)->im/10;
						//}
#endif
						kk2 =(kk+1)%2;
						ippsCrossCorr_32fc(signal3, 62, signal4, 62, &fcTmp, 1, 0);
						//myifft(signal44,signal4,64);
						//ippsCrossCorr_32fc(signal192+signalStart3, 62, signal44, 62, &fcTmp, 1, 0);
#if _USE_SSCH_REAL > 0
						cor[kk2*168+jj] += fcTmp.re;
#else
						cor[kk2*168+jj] += (fcTmp.re*fcTmp.re + fcTmp.im*fcTmp.im);

						//Parseval Theorem - Scaling by the factor of Sequence lenght when its done in the freq domain - Raj
						cor[kk2*168+jj] = cor[kk2*168+jj]/(total_energy_ss22*62);

						//if((cor[kk2*168+jj]) > 20)
						//printf("SSS Corr signal SS2 = %f\n",cor[kk2*168+jj]);
#endif
					}
				}
			}
			// don't know why it works w/o the 62, but the numbers match up
//			H2_PSS2[cpMode] = H2_PSS/(numSamplesToProcess*62); 
			H2_PSS2[cpMode] = (Ipp32f)sqrt(H2_PSS/NumHalfFramesToProcess);

			cor += 168*2;
		}//end for cpMode

		cor -= 168*4;

		// Added as bug fix from Jonathan Peng
		// 03 Nov 2009
		//for(ii=0;ii<168*4;ii++)
		//	cor[ii] = fabs(cor[ii]);

#if 0 //Raj
		ippsAbs_32f_I(cor, 168*4);

		ippsDivC_32f_I((Ipp32f)(128*62*NumHalfFramesToProcess), cor, 168*4);
		ippsSqrt_32f_I(cor, 168*4);
#endif

		//findMax_32f(cor, 336, &maxIdx);
		ippsMaxIndx_32f(cor, 336*2, &maxVal, (int *)&maxIdx);
		threshold = maxVal/1.5f;

		//ippsMeanVarColumn_32f_D2(cor,168*4,1,&cor_mean,&cor_var,1);

		//ippsSum_32f(cor,168*4,&cor_mean,ippAlgHintNone);

		//cor_mean = cor_mean / (168*4);

		//for(unsigned int mm=0;mm<168*4;mm++)
		//{
		//cor_sum = (cor[mm] - cor_mean) * (cor[mm] - cor_mean);
		//}
		//cor_sum = cor_sum / (168*4);
		//cor_var = sqrt(cor_sum);
		

		// this loop goes thru all the peaks to find how many are
		// above the threshold (which seems to be arbitrarily set by Peng).
		// If more than 10 peaks are found (above the threshold), then
		// the PeakFlag is reset to 0.  Presumably this means that b/c
		// there were so many peaks, then the peaks must all be false?
		// Or maybe it is looking for multiple SSCHs that occur for a given PSCH.
		// This I guess could happen with co-located sectors?
		jj = 0;
		peakFlag = 1;
		for(ii=0;ii<336*2;ii++)
		{
			if(cor[ii]>threshold)
			{
				val1[jj] = cor[ii];
				idx1[jj] = ii;
				jj++;
				if(jj>10)
				{
					peakFlag = 0;
					break;
				}
			}
		}

		// Block added by Dhaval 12/06/09
		// jj>10 means it's trash
		// but if jj>1, we just want to keep the max value only.
		if(jj>10) peakFlag = 0;
		jj = 1;
		val1[0] = maxVal;
		idx1[0] = maxIdx;


		// peakFlag == 1 means that there were less than 10 peaks for the given PSCH.
		// this could be multiple sectors with the same PSCH timing.  The SSCH ID and timing
		// could/should be different.
		// numIdx is the number of SSCH peaks found.
		// repeatedFlag denotes that a peak corresponds to a cellID that's already in the list,
		// in which case there's no need to repeat all the ssch/psch strength calculations.
		// BUT !!!!  why would this occur, and what does it mean if it does occur?
		// Really it means you have the same psch/ssch combo, and there are 2 peaks for that with
		// different CP types and/or sub-frame timing.  So why discard those occurences?
		if(peakFlag==1)
		{
			numIdx = jj;

			if(numIdx>1)
				ippsSortIndexDescend_32f_I(val1, (int *)sortIdx, numIdx);
			else
				sortIdx[0] = 0;

			for(ii=0;ii<numIdx;ii++)
			{
				idx2 = idx1[sortIdx[ii]];
				sschID = idx2%168;
				cellIDAll = sschID*3 + pschID;

				repeatedFlag = 0;
				for(jj=0;jj<numCellID;jj++)
				{
					if(cellIDAll==pSSCHCorrRecord[jj].ID)
						repeatedFlag = 1;
				}

				if(repeatedFlag==0)
				{
					// Because each psch peak can have multiple ssch peaks,
					// ( TODO: is this behavior OK? )
					// we need to make sure to fill in the psch record that
					// corresponds to each ssch record.
					pPSCHCorrRecord[numCellID].ID = pschID;
					pPSCHCorrRecord[numCellID].NormCorr = currPschRecord->NormCorr;
					//printf("PSS Norm Corr ==%f\n",pPSCHCorrRecord[numCellID].NormCorr);
					pPSCHCorrRecord[numCellID].RMSCorr = currPschRecord->RMSCorr;
					pPSCHCorrRecord[numCellID].StartSampleNum = currPschRecord->StartSampleNum;

					pSSCHCorrRecord[numCellID].ID = cellIDAll;
					//pSSCHCorrRecord[numCellID].NormCorr = val1[ii];
					pSSCHCorrRecord[numCellID].NormCorr = (CORRELATIONTYPE)sqrt(val1[ii]);
					//printf("SS Norm Corr ==%f  vali = =%f\n",pSSCHCorrRecord[numCellID].NormCorr,val1[ii]);
					jj = idx2/168;
					if(jj<2)
					{
						pCyclicPrefixMode[numCellID] =Normal;
						PSchStrength[numCellID] = H2_PSS2[0];
					}
					else
					{
						pCyclicPrefixMode[numCellID] =Extended;
						PSchStrength[numCellID] = H2_PSS2[1];
					}

					pPSSStartSample2[numCellID] = currPschRecord->StartSampleNum;
					if(jj%2==1)
					{
						pSSCHCorrRecord[numCellID].StartSampleNum = currPschRecord->StartSampleNum + 9600 + 128 -960;
						halfFrameFlag[numCellID] = 1;
					}
					else
					{
						if(pPSCHCorrRecord[cid2].StartSampleNum+128<=960)
							pSSCHCorrRecord[numCellID].StartSampleNum = 19200 + currPschRecord->StartSampleNum + 128 -960;
						else
							pSSCHCorrRecord[numCellID].StartSampleNum = currPschRecord->StartSampleNum + 128 -960;
						halfFrameFlag[numCellID] = 0;
					
					}
					numCellID++;
				}
	
			}
			currPschRecord++;
		}
	}

	*pNumCellID = numCellID;

	//computeSSSStrength(pSSchStrength, numCellID, signal192, numSamplesToProcess, pCellID, pPSSStartSample2,  
	//					halfFrameFlag, pCyclicPrefixMode);
	computeSSSStrength(signal192, NumHalfFramesToProcess,
		halfFrameFlag, pCyclicPrefixMode, pPSSStartSample2,
		numCellID, pSSCHCorrRecord);

	ippsFree(cor);

}


void computeSSSStrength(const Ipp32fc *signal192, unsigned int numSamplesToProcess,
		const unsigned int* pHalfFrameFlag, const CYCLICPREFIX *pCyclicPrefixMode, const unsigned int *pPSSStartSample,
		unsigned int numSSS, LTEProc_CorrRecordType *pSSCHCorrRecord)
{
	Ipp32f H2_SSS = 0;
	unsigned int ii, jj, halfFrameFlag, kk, cellID1, cellID2;
	Ipp32f ftmp;
	Ipp32fc H_est1[62];


	for(kk=0;kk<numSSS;kk++)
	{
		halfFrameFlag = pHalfFrameFlag[kk];
		cellID2 = pSSCHCorrRecord[kk].ID%3;
		cellID1 = pSSCHCorrRecord[kk].ID/3;

		for(ii=0;ii<numSamplesToProcess/2;ii++)
		{
			getChannelEstFromSSS(H_est1, signal192, pPSSStartSample[kk], 
				halfFrameFlag, cellID1, cellID2, 2*ii, pCyclicPrefixMode[kk]);

			ftmp = 0;
			for(jj=0;jj<62;jj++)
			{
				ftmp += H_est1[jj].re*H_est1[jj].re+H_est1[jj].im*H_est1[jj].im;
			}
			H2_SSS += ftmp;

			halfFrameFlag = (halfFrameFlag + 1)%2;

			getChannelEstFromSSS(H_est1, signal192, pPSSStartSample[kk], 
				halfFrameFlag, cellID1, cellID2, 2*ii+1, pCyclicPrefixMode[kk]);
			ftmp = 0;
			for(jj=0;jj<62;jj++)
			{
				ftmp += H_est1[jj].re*H_est1[jj].re+H_est1[jj].im*H_est1[jj].im;
			}
			H2_SSS += ftmp;

		}

		// Average the SSS strength over the number of subframes summed over
		// TODO: figure out how to avoid this scaling by fft-length
		pSSCHCorrRecord[kk].RMSCorr = H2_SSS/(numSamplesToProcess * sqrt(128.f * 62.f));
		pSSCHCorrRecord[kk].RMSCorr = sqrt(pSSCHCorrRecord[kk].RMSCorr);
	}
}

unsigned char verifyCellIDFromRS(const Ipp32fc *signal384, unsigned int cellID,
		unsigned int frameStartSample, CYCLICPREFIX cyclicPrefixMode,
		CORRELATIONTYPE *RSStrength, CORRELATIONTYPE *RSNorm)
{
	int slotNumToProcess = 10;
	Ipp32fc cor[2][6];
	Ipp32f ampt[2][6];
	Ipp32fc cor2[6];
	Ipp32f ampt2[6];
	Ipp32f cor3[6];

	int slotSampleShift = 0;
	int slotNo;

	Ipp32fc cell_RS[60], cell_RS_conj[60], signal1[256], signal2[256], signal3[180], signal3_conj[180]; //size??
	Ipp32fc fcTmp0, fcTmp1;
	Ipp32f fTmp0, maxVal;
	unsigned int OFDM_SymbNos[2];
	int ii, jj, kk, nn;
	Ipp16u frquencyIdx[60];  //size ??
	int symbStart;
	int maxIdx;
	unsigned int symbNum;

	ippsZero_32fc(cor2, 6);
	ippsZero_32f(ampt2, 6);

	for(slotNo=0;slotNo<slotNumToProcess;slotNo++)
	{
		generate_cell_RS(cell_RS,OFDM_SymbNos, &symbNum, frquencyIdx, slotNo, cellID, 
			cyclicPrefixMode, 15, 110, 0);

		ippsConj_32fc(cell_RS, cell_RS_conj, 60);

		// for each RS OFDM symbol in this slot (=2 for 1 ant port)
		for(ii=0;ii<symbNum;ii++)
		{
			if(cyclicPrefixMode==Normal)
			{
				symbStart = 20 + OFDM_SymbNos[ii]*(18+256)+frameStartSample+slotSampleShift;
			}
			else
			{
				symbStart = 64 + OFDM_SymbNos[ii]*(64+256)+frameStartSample+slotSampleShift;
			}

			myfft(signal1, signal384+symbStart, 256);
			myfftshift(signal2, signal1, 256);

			ippsCopy_32fc(signal2+128-90, signal3, 90);
			ippsCopy_32fc(signal2+129, signal3+90, 90);

			ippsConj_32fc(signal3, signal3_conj, 180);

			for(nn=0;nn<6;nn++)
			{
				kk = 0;
				fcTmp0.re = fcTmp0.im = fTmp0 = 0;
				for(jj=nn;jj<(nn+174);jj+=6)
				{
					ippsMul_32fc(signal3+jj, signal3_conj+jj+6, &fcTmp1, 1);
					ippsMul_32fc_I(cell_RS+ii*30+kk+1, &fcTmp1, 1);
					ippsMul_32fc_I(cell_RS_conj+ii*30+kk, &fcTmp1, 1);
					fcTmp0.re += fcTmp1.re;
					fcTmp0.im += fcTmp1.im;
					fTmp0 += signal3[jj].re*signal3[jj].re+signal3[jj].im*signal3[jj].im;
					kk++;
				}

				cor[ii][nn].re = fcTmp0.re;
				cor[ii][nn].im = fcTmp0.im;
				ampt[ii][nn] = fTmp0;
			}
		}	

		if(symbNum==2)
		{
			for(nn=0;nn<6;nn++)
			{
				cor2[nn].re += cor[0][nn].re + cor[1][(nn+3)%6].re;
				cor2[nn].im += cor[0][nn].im + cor[1][(nn+3)%6].im;
				ampt2[nn] += ampt[0][nn] + ampt[1][(nn+3)%6];
			}
		}
		else
		{
			for(nn=0;nn<6;nn++)
			{
				cor2[nn].re += cor[0][nn].re;
				cor2[nn].im += cor[0][nn].im;
				ampt2[nn] += ampt[0][nn];
			}
		}
		slotSampleShift += 1920;
	}

	
	for(nn=0;nn<6;nn++)
	{
//		TODO: check w/J. Peng
		// is the /ampt2 supposed to be inside the sqrt?
//		cor3[nn] = (Ipp32f)sqrt(cor2[nn].re*cor2[nn].re+cor2[nn].im*cor2[nn].im)/ampt2[nn];
		cor3[nn] = (Ipp32f)sqrt( (cor2[nn].re*cor2[nn].re+cor2[nn].im*cor2[nn].im) / ampt2[nn] );
	}

	//findMax_32f(cor3, 6, &maxIdx);
	ippsMaxIndx_32f(ampt2, 6, &maxVal, &maxIdx);
	*RSStrength = sqrt(maxVal/(kk*symbNum*slotNumToProcess));

	ippsMaxIndx_32f(cor3, 6, &maxVal, &maxIdx);
	*RSNorm = maxVal / *RSStrength;

	if(maxIdx==frquencyIdx[0])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int calculateRSValues(const Ipp32fc *signal384, unsigned int cellID,
		unsigned int frameStartSample, CYCLICPREFIX cyclicPrefixMode,
		CORRELATIONTYPE *RSStrength, CORRELATIONTYPE *RSNorm, double *AvgDigitalVoltage)
{
	int slotNumToProcess = 10;
	Ipp32f ampt[2][6];
	Ipp32f ampt2[6];

	int slotSampleShift = 0;
	int slotNo;

	Ipp32fc cell_RS[60], cell_RS_conj[60];
	Ipp32fc signal1[256], signal2[256], signal3[180]; //size??
	Ipp32f sigPSD[180];
	unsigned int OFDM_SymbNos[2];
	int ii, jj, nn;
	Ipp16u frquencyIdx[60];  //size ??
	int symbStart;

	unsigned int symbNum;

	ippsZero_32f(ampt2, 6);

	Ipp32fc DigitalDC;
	Ipp32f rssi = 0, rsrp = 0, rsrq = 0;
	Ipp64f L2Norm;

	// Calculate over N Resource Blocks
	// N = num RBs that encompass the num of subcarriers kept after the FFT
	for(slotNo=0;slotNo<slotNumToProcess;slotNo++)
	{
		// get RS template and RS conjugate for cellID and CP
		generate_cell_RS(cell_RS,OFDM_SymbNos, &symbNum, frquencyIdx, slotNo, cellID, 
			cyclicPrefixMode, 15, 110, 0);
		ippsConj_32fc(cell_RS, cell_RS_conj, 60);

		ippsZero_32f(&(ampt[0][0]), 12);
		// for each RS OFDM symbol in this slot
		// =2 for 1 ant port, i.e. slots 0 and 4 for normal CP
		for(ii=0;ii<symbNum;ii++)
		{
			// calculate start of RS in signal based on CP and PSS location
			if(cyclicPrefixMode==Normal)
			{
				symbStart = 20 + OFDM_SymbNos[ii]*(18+256)+frameStartSample+slotSampleShift;
			}
			else
			{
				symbStart = 64 + OFDM_SymbNos[ii]*(64+256)+frameStartSample+slotSampleShift;
			}

			// get fft of the signal of length=SymbolLength at location of RS
			// restructure freq bins to eliminate the DC
			// Right now we have 180 sub carriers = 15 RBs
			FftRS.FftFwd(signal384+symbStart, signal1);
			FftRS.FftShift(signal1, signal2);
			ippsCopy_32fc(signal2+128-90, signal3, 90);
			ippsCopy_32fc(signal2+129, signal3+90, 90);
			//ippsNorm_L2_32fc64f(signal1, 256, &L2Norm);
			//ippsNorm_L2_32fc64f(signal3, 180, &L2Norm);
			//ippsNorm_L2_32fc64f(signal384+symbStart, 256, &L2Norm);
			//ippsMean_32fc(signal384+symbStart, 256, &DigitalDC, ippAlgHintAccurate);
			//L2Norm = sqrt(L2Norm*L2Norm - DigitalDC.re*DigitalDC.re - DigitalDC.im*DigitalDC.im);
			//rssi += (Ipp32f)L2Norm*(Ipp32f)L2Norm;

			// Sum the power spectrum of every 6th subcarrier
			ippsPowerSpectr_32fc(signal3, sigPSD, 180);
			for( jj=0; jj<180; jj++ )
			{
				ampt[ii][jj%6] += sigPSD[jj];
			}
		}

		if(symbNum==2)
		{
			for(nn=0;nn<6;nn++)
			{
				ampt2[nn] += ampt[0][nn] + ampt[1][(nn+3)%6];
			}
		}
		else
		{
			for(nn=0;nn<6;nn++)
			{
				ampt2[nn] += ampt[0][nn];
			}
		}
		slotSampleShift += 1920;
	}

	// Num RBs is TotNumSlots * total num of subcarriers / (12 subcarriers per RB per slot)
	unsigned int NumRB = (180/12) * slotNo;
	// Num REs is NumRB * Num RS OFDM symbols per slot * (12/6) Num RS subcarriers per RB
	unsigned int NumRE = NumRB * symbNum * 2;

	// rssi = wideband total avg power per OFDM symbol period
	// (calculated over only those symbols periods that contain RS)
//	rssi /= (symbNum*slotNumToProcess);
	ippsSum_32f(ampt2, 6, &rssi, ippAlgHintAccurate);
	rssi /= (Ipp32f)(symbNum);
	if ( rssi == 0 ) 
		return -1;

	rsrp = ampt2[cellID%6] / (Ipp32f)NumRE;
	rsrq = (Ipp32f)NumRB * rsrp / rssi;
	*RSNorm = (CORRELATIONTYPE)sqrt(rsrq);
	*RSStrength = (CORRELATIONTYPE)sqrt(rsrp);
	*AvgDigitalVoltage = (CORRELATIONTYPE)sqrt(rssi/slotNo);

	return 0;
}



/*
TODO: Create class and associated PSS objects.
There are only 3 unique PSS.
The templates can be created at run-time and stored in static memory.
The only reason not to include them directly in the src code is if we
want to change the PSS length.
*/
void generate_PSS(Ipp32fc *PSS_seq_T, Ipp32fc *PSS_seq_F, int len, int id)
{
	int u[3] = {25, 29, 34};
	Ipp32fc d_u[62];
	double dTmp;
	Ipp32fc *fcTmp;
	Ipp64f normFactor = 1;
	
	int ii;
	int uid;

	uid = u[id];

	for(ii=0;ii<31;ii++)
	{
		dTmp = PI*uid*ii*(ii+1)/63;
		d_u[ii].re = (Ipp32f)cos(dTmp);
		d_u[ii].im = -(Ipp32f)sin(dTmp);

		dTmp = PI*uid*(ii+31+1)*(ii+31+2)/63;
		d_u[ii+31].re = (Ipp32f)cos(dTmp);
		d_u[ii+31].im = -(Ipp32f)sin(dTmp);
	}

	ippsZero_32fc(PSS_seq_F, len);

	ippsCopy_32fc(d_u, PSS_seq_F+33, 31);
	ippsCopy_32fc(d_u+31, PSS_seq_F+65, 31);

	fcTmp = ippsMalloc_32fc(len);
	
	myfftshift(fcTmp, PSS_seq_F, len);
	myifft(PSS_seq_T, fcTmp, len);

	ippsNorm_L2_32fc64f(PSS_seq_T, len, &normFactor);
	fcTmp->re = (Ipp32f)normFactor;
	fcTmp->im = (Ipp32f)0;
	ippsDivC_32fc_I( *fcTmp, PSS_seq_T, len );

	ippsFree(fcTmp);
}



void generate_SSS(Ipp32fc *SSS_seq, int cellID1, int cellID2)
{
	int qr, q, mr, m0, m1;
	int x[31], sh[31], s0[31], s1[31], ch[31], c0[31], c1[31], 
		zh[31], z10[31], z11[31];
	int ii;

	qr = cellID1/30;
	q = (cellID1 + (qr*(qr+1))/2)/30;
	mr = cellID1 + (q*(q+1))/2;

	m0 = mr%31; 
	m1 = (int)(m0+(mr/31)+1)%31;

	x[0] = 0; x[1] = 0; x[2] = 0; x[3] = 0; x[4] = 1;

	for(ii=0;ii<26;ii++)
	{
		x[ii+5] = (x[ii+2]+x[ii])%2;
	}

	for(ii=0;ii<31;ii++)
	{
		sh[ii] = 1-2*x[ii];
	}

	for(ii=0;ii<31;ii++)
	{
		s0[ii] = sh[(ii+m0)%31];
		s1[ii] = sh[(ii+m1)%31];
	}

	
	for(ii=0;ii<26;ii++)
	{
		x[ii+5] = (x[ii+3]+x[ii])%2;
	}

	for(ii=0;ii<31;ii++)
	{
		ch[ii] = 1-2*x[ii];
	}

	
	for(ii=0;ii<31;ii++)
	{
		c0[ii] = ch[(ii+cellID2)%31];
		c1[ii] = ch[(ii+cellID2+3)%31];
	}

	for(ii=0;ii<26;ii++)
	{
		x[ii+5] = (x[ii+4]+x[ii+2]+x[ii+1]+x[ii])%2;
	}

	for(ii=0;ii<31;ii++)
	{
		zh[ii] = 1-2*x[ii];
	}

	
	for(ii=0;ii<31;ii++)
	{
		z10[ii] = zh[(ii+m0%8)%31];
		z11[ii] = zh[(ii+m1%8)%31];
	}

	// set the imag part to 0.
	// the real part will be filled in thru the for loop.
	ippsZero_32fc(SSS_seq, 124);
	for(ii=0;ii<31;ii++)
	{
		SSS_seq[2*ii].re = (Ipp32f)(s0[ii]*c0[ii]);
		SSS_seq[2*ii+1].re = (Ipp32f)(s1[ii]*c1[ii]*z10[ii]);

		SSS_seq[2*ii+62].re = (Ipp32f)(s1[ii]*c0[ii]);
		SSS_seq[2*ii+63].re = (Ipp32f)(s0[ii]*c1[ii]*z11[ii]);
	}
}


//const unsigned int WIND_LtePssSearcher::m_MaxNumIFChannels = LTE_ANALYSIS_PSS_SEARCH_MAX_NUM_IF;
//
//WIND_LtePssSearcher::WIND_LtePssSearcher(unsigned int SampleRateHz) :
//m_SampleRateHz(0), m_DownConverterFrame(NULL)
//{
//	ippsZero_32fc( m_DownConverter_OneLteFrameBuffer,
//		sizeof(m_DownConverter_OneLteFrameBuffer)/sizeof(m_DownConverter_OneLteFrameBuffer[0]));
//	m_DownConverterFrame = (Ipp32fc *)ippAlignPtr(m_DownConverter_OneLteFrameBuffer, WINDIPP_MEM_ALIGN_SIZE);
//
//	ippsZero_32fc( m_DownConverterBuffer,
//		sizeof(m_DownConverterBuffer)/sizeof(m_DownConverterBuffer[0]));
//	m_DownConverterRandom = (Ipp32fc *)ippAlignPtr(m_DownConverterBuffer, WINDIPP_MEM_ALIGN_SIZE);
//
//	SetNewSampleRate(SampleRateHz);
//}
//
//WIND_LtePssSearcher::~WIND_LtePssSearcher()
//{
//	for ( unsigned int idx=0; idx<m_MaxNumIFChannels; idx++ )
//	{
//		delete m_PssTemplates[idx];
//	}
//}
//
//int WIND_LtePssSearcher::SetNewSampleRate(unsigned int SampleRateHz)
//{
//	if ( SampleRateHz == m_SampleRateHz ) return 0;
//
//	// Create all new PSS templates
//	for ( unsigned int idx=0; idx<m_MaxNumIFChannels; idx++ )
//	{
//		delete m_PssTemplates[idx];
//		m_PssTemplates[idx] = new LtePrimarySyncSequence(SampleRateHz/1000);
//	}
//	m_SampleRateHz = SampleRateHz;
//
//	// create the down-converter which will step up one IF channel
//	float Phase = 0.f;
//	ippsTone_Direct_32fc(m_DownConverterFrame, 48750, 1.f,
//		1000.f * LTE_ANALYSIS_IF_STEPSIZE_KHZ/m_SampleRateHz, &Phase, ippAlgHintAccurate);
//
//	// Down-convert the PSS templates for each IF.
//	// Start by down-converting template 0 by the max IF offset,
//	// and then step up one IF channel for each successive template.
//	for ( unsigned int psid=0; psid<LTE_NUM_PSS; psid++ )
//	{
//		DownConvert(m_PssTemplates[0]->GetSeqT(psid),
//			m_PssTemplates[0]->GetBufferT(psid),
//			m_PssTemplates[0]->GetSeqLength(),
//			-LTE_ANALYSIS_PSS_SEARCH_MAX_IF_KHZ/LTE_ANALYSIS_IF_STEPSIZE_KHZ
//		);
//
//		for ( unsigned int idx=1; idx<m_MaxNumIFChannels; idx++ )
//		{
//			IFUpShiftOne(m_PssTemplates[idx-1]->GetSeqT(psid),
//				m_PssTemplates[idx]->GetBufferT(psid),
//				m_PssTemplates[idx]->GetSeqLength());
//		}
//	}
//	return 0;
//}
//
//int WIND_LtePssSearcher::Search(const Ipp32fc *Signal, unsigned int NumSamples, WindPssSearchData *Results)
//{
//	const CORRELATIONTYPE pssThresh = 0.50;
//	unsigned int i, psid, maxIdx;
//	Ipp32f maxVal;
//	unsigned int CorrLen = NumSamples - m_PssTemplates[0]->GetSeqLength();
//
//	Ipp32f *AvgEnergy = ippsMalloc_32f(NumSamples);
//	Ipp32f *CorrPower = ippsMalloc_32f(CorrLen);
//	Ipp32fc *XCorr = ippsMalloc_32fc(CorrLen);
//
//	// TODO: delete this, for testing only!
//	const Ipp32fc *NewSignal = Signal;
//	//Ipp32fc *NewSignal = ippsMalloc_32fc(NumSamples);
//	//DownConvert(Signal, NewSignal, NumSamples, -10);
//
//	// Calculate the moving-avg energy sequence that will be used for normalization
//	ippsPowerSpectr_32fc(NewSignal, AvgEnergy, NumSamples);
//	for ( i=0; i<CorrLen; i++ )
//	{
//		ippsMean_32f(&AvgEnergy[i], m_PssTemplates[0]->GetSeqLength(), &AvgEnergy[i], ippAlgHintAccurate);
//	}
//
//	// Calculate the xcorrs for only IF = 0.
//	i = 15;
//	{
//		Results[0].CorrelationResult.NormCorr = 0;
//		Results[0].IsValidLteChannel = false;
//		for( psid=0; psid<3; psid++ )
//		{
//			// get each of the PSCH cross corrs
//			// and normalize the xcorr energy by the energy (in the xcorr window).
//			ippsCrossCorr_32fc(m_PssTemplates[i]->GetSeqT(psid), m_PssTemplates[i]->GetSeqLength(),
//				NewSignal, NumSamples, XCorr, CorrLen, 0);
//			ippsPowerSpectr_32fc(XCorr, CorrPower, CorrLen);
//			ippsDiv_32f_I(AvgEnergy, CorrPower, CorrLen);
//
//			// Find highest normalized corr value (over all PSS IDs) and store in Results
//			ippsMaxIndx_32f(CorrPower, CorrLen , &maxVal, (int *)&maxIdx);
//			maxVal = sqrt(maxVal);
//			if ( maxVal > Results[0].CorrelationResult.NormCorr )
//			{
//				Results[0].CorrelationResult.NormCorr = (CORRELATIONTYPE)maxVal;
//				Results[0].CorrelationResult.RMSCorr = (CORRELATIONTYPE)(maxVal*sqrt(AvgEnergy[maxIdx]));
//				Results[0].CorrelationResult.StartSampleNum = maxIdx;
//				Results[0].CorrelationResult.ID = psid;
//				if ( Results[0].CorrelationResult.NormCorr < pssThresh )
//					Results[0].IsValidLteChannel = false;
//				else Results[0].IsValidLteChannel = true;
//			}
//		}
//	}
//
//	//// Calculate the xcorrs for each IF channel
//	//for( i=0; i<LTE_ANALYSIS_PSS_SEARCH_MAX_NUM_IF; i++ )
//	//{
//	//	Results[i].CorrelationResult.NormCorr = 0;
//	//	Results[i].IsValidLteChannel = false;
//	//	for( psid=0; psid<3; psid++ )
//	//	{
//	//		// get each of the PSCH cross corrs
//	//		// and normalize the xcorr energy by the energy (in the xcorr window).
//	//		ippsCrossCorr_32fc(m_PssTemplates[i]->GetSeqT(psid), m_PssTemplates[i]->GetSeqLength(),
//	//			NewSignal, NumSamples, XCorr, CorrLen, 0);
//	//		ippsPowerSpectr_32fc(XCorr, CorrPower, CorrLen);
//	//		ippsDiv_32f_I(AvgEnergy, CorrPower, CorrLen);
//
//	//		// Find highest normalized corr value (over all PSS IDs) and store in Results
//	//		ippsMaxIndx_32f(CorrPower, CorrLen , &maxVal, (int *)&maxIdx);
//	//		maxVal = sqrt(maxVal);
//	//		if ( maxVal > Results[i].CorrelationResult.NormCorr )
//	//		{
//	//			Results[i].CorrelationResult.NormCorr = (CORRELATIONTYPE)maxVal;
//	//			Results[i].CorrelationResult.RMSCorr = (CORRELATIONTYPE)(maxVal*sqrt(AvgEnergy[maxIdx]));
//	//			Results[i].CorrelationResult.StartSampleNum = maxIdx;
//	//			Results[i].CorrelationResult.ID = psid;
//	//			if ( Results[i].CorrelationResult.NormCorr < pssThresh )
//	//				Results[i].IsValidLteChannel = false;
//	//			else Results[i].IsValidLteChannel = true;
//	//		}
//	//	}
//	//}
//
//	//// Determine which are potentially valid Lte channels:
//	//// Search "valid" records in Results for strongest NormCorr that is < previous strongest.
//	//// If it passes the absolute threshold, "invalidate" the 5 IF subcarriers on either side.
//	//// Then repeat the process.
//	//int j, k1, k2, tmp, currIdx;
//	//CORRELATIONTYPE PreviousMax = 2.0, CurrentMax = 0;
//	//for ( tmp=0; tmp<LTE_ANALYSIS_PSS_SEARCH_MAX_NUM_IF; tmp++ )
//	//{
//	//	for ( i=0; i<LTE_ANALYSIS_PSS_SEARCH_MAX_NUM_IF; i++ )
//	//	{
//	//		if ( Results[i].IsValidLteChannel
//	//			&& (Results[i].CorrelationResult.NormCorr > CurrentMax)
//	//			&& (Results[i].CorrelationResult.NormCorr < PreviousMax) )
//	//		{
//	//			CurrentMax = Results[i].CorrelationResult.NormCorr;
//	//			currIdx = i;
//	//		}
//	//	}
//	//	if ( CurrentMax < pssThresh ) break;
//	//	for ( j=1; j<=14; j++ )
//	//	{
//	//		k1 = currIdx - j;
//	//		if ( k1 >= 0 )
//	//			Results[k1].IsValidLteChannel = false;
//	//		k2 = currIdx + j;
//	//		if ( k2 < LTE_ANALYSIS_PSS_SEARCH_MAX_NUM_IF )
//	//			Results[k2].IsValidLteChannel = false;
//	//	}
//	//	PreviousMax = CurrentMax;
//	//	CurrentMax = 0;
//	//}
//
//	ippsFree(AvgEnergy);
//	ippsFree(CorrPower);
//	ippsFree(XCorr);
//	return 0;
//}
//
//int WIND_LtePssSearcher::DownConvert(const Ipp32fc *Src, Ipp32fc *Dst,
//	unsigned int NumSamples, int NumIFChannelShift)
//{
//	float Phase = 0.f;
//	float FreqShift = 1000.f*NumIFChannelShift*LTE_ANALYSIS_IF_STEPSIZE_KHZ/m_SampleRateHz;
//	if ( FreqShift < 0 ) FreqShift += 1;
//	int result = ippsTone_Direct_32fc(m_DownConverterRandom, NumSamples, 1.f,
//		FreqShift, &Phase, ippAlgHintAccurate);
//	return ippsMul_32fc(Src, m_DownConverterRandom, Dst, NumSamples);
//}
//
//int WIND_LtePssSearcher::IFUpShiftOne(const Ipp32fc *Src, Ipp32fc *Dst, unsigned int NumSamples) const
//{
//	return ippsMul_32fc(Src, m_DownConverterFrame, Dst, NumSamples);
//}
//
//

}