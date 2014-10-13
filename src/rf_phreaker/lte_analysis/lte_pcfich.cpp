/*
*********************************************************************************************************
* Copyright (c) 
* File : LtePcfich.cpp
* Brief : Decoding LTE Physical Control Format Indicator Channel (PCFICH)
* Author:Rajesh S. Bagul
* History : 
*********************************************************************************************************
*/


#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include "lte_common.h"
#include "lte_analysis.h"

namespace rf_phreaker {

int lteGetFrequencyIndicesPHICH( unsigned int *ltePCFICHFreqIndices,
	                             lte_measurements &LteData,
					             unsigned int cellNo);
 
/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/

int lteDecodePCFICH(Ipp32fc* inSignal,
	                Ipp32fc* hEst,
	                Ipp32f* hNoiseVar,	
	                lte_measurements &LteData,
					unsigned int cellNo,
					unsigned int subFrameIndex,
					unsigned int subframeStartSampleIndex)

{

	Ipp32fc fftOutput[4096],fftOutputShifted[4096]; // Static Allocation for Maximum size FFT 
	Ipp32f detLLR[32]; //32 Bits of PCFICH
	Ipp32f deScrambledLLRPcfich[32];
	unsigned int ltePCFICHFreqIndices[16];
	Ipp32fc rEsPcfich[NUM_PCFICH_MODULATION_SYMBOLS];
	Ipp32fc HestPcfich[NUM_PCFICH_MODULATION_SYMBOLS * NUM_ANTENNA_MAX];
	unsigned int ofdmSymbolIndex = 0,c_init;
	unsigned int scramblingSeqPcfich[NUM_PCFICH_MODULATION_SYMBOLS * 2];
	double nSlotNum =0.0;
	double correlation[4],correlationMax= 0;//correlationMax=0;
	double CFI[4][32] = { 1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1, //5.3.4.1 TS36.212
	                     -1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,
	                     -1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,
                          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


	hNoiseVar[0] = hNoiseVar[1] = 169800.0;
	//hNoiseVar[0] = hNoiseVar[1] = 298800.0;
	//hNoiseVar[1] = hNoiseVar[0];

	/* FFT Operation */

	myfft(fftOutput, //Frequency Domain Output
		  inSignal + subframeStartSampleIndex + LteData[cellNo].cPSamplesSymbol0, //Time Domain Input
		  LteData[cellNo].fftSize); //FFT Size


	myfftshift(fftOutputShifted, //Destination
		       fftOutput, //Source
		       LteData[cellNo].fftSize); //FFT Size

	/* Determine the Frequency Indices of PCFICH modulation sysmbols -- FFT Index */

	lteGetFrequencyIndicesPHICH( ltePCFICHFreqIndices,
	                             LteData,
					             cellNo);

	for(unsigned int jj=0;jj<NUM_PCFICH_MODULATION_SYMBOLS;jj++)
	{
	rEsPcfich[jj]= fftOutputShifted[ltePCFICHFreqIndices[jj]];
	}

	for (unsigned int antNum =0 ; antNum < LteData[cellNo].NumAntennaPorts; antNum++)
	{
	
		for (unsigned int ii=0;ii<NUM_PCFICH_MODULATION_SYMBOLS;++ii )
		{
		HestPcfich[antNum * NUM_PCFICH_MODULATION_SYMBOLS + ii] = hEst[antNum * LteData[cellNo].fftSize * OFDM_SYMBOLS_PER_FRAME
		                                                               + subFrameIndex * OFDM_SYMBOLS_PER_SUBFRAME *LteData[cellNo].fftSize
																	   + ofdmSymbolIndex * LteData[cellNo].fftSize
		                                                               + ltePCFICHFreqIndices[ii]
		                                                              ];
			
		}
	}

	//TODO - Proper Noise Variance Calculation --Raj,4 Oct 2011

	/* MIMO Detection - Transmit Diversity */
	     stDiversityDet(detLLR,
		                rEsPcfich, // PCFICH Modulation Symbols - Resource Elements
						HestPcfich,
		                NUM_PCFICH_MODULATION_SYMBOLS,
	                    LteData[cellNo].NumAntennaPorts, // Number of Antennas 
	                    MQPSK,//Modulation Type == QPSK
	                    hNoiseVar);
	 
	/* Descrambling */
   nSlotNum = 2*subFrameIndex;
	c_init = (unsigned int)(floor(nSlotNum/2) + 1)*(2*LteData[cellNo].RsRecord.ID + 1)*(1<<9) + LteData[cellNo].RsRecord.ID; //6.7.1 TS36.211
	
	generate_PN_seq(scramblingSeqPcfich, //PCFICH Scambling Sequence
		             c_init, //c_init
					 NUM_PCFICH_MODULATION_SYMBOLS * 2); // Sequence Lenght = 16(mod sym)*2(2bits per OPSK sym) = 32
	

	softDeSrambling(deScrambledLLRPcfich,// Output Descrambled LLR Data
		            detLLR,//Input LLR data
		            NUM_PCFICH_MODULATION_SYMBOLS * 2,//lenght of the sequence
		            scramblingSeqPcfich);//Scrambling bits

	/* Correlate Descrambled LLRs with CFI to determine the control symbol lenght - 5.3.4.1 TS36.212 */
	LteData[cellNo].lteControlSysmbolLenght = 0;
    for (unsigned int cc=0;cc < 3; cc++)
	{
		correlation[cc] = 0;

			for (unsigned int kk=0;kk < 32;kk++)
				{
				correlation[cc] = correlation[cc] + deScrambledLLRPcfich[kk]*CFI[cc][kk];
	
				}
			if(correlation[cc] > correlationMax)
			{
			 LteData[cellNo].lteControlSysmbolLenght = cc + 1;
			 correlationMax = correlation[cc];
			}
	}

	return LTE_SUCCESS;


}


/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lteGetFrequencyIndicesPHICH( unsigned int *ltePCFICHFreqIndices,
	                             lte_measurements &LteData,
					             unsigned int cellNo)

{

	unsigned int kb; // Resource Element number of the first PCFICH quadruplet
	unsigned int refSignalStartIndex,k;
	unsigned int index[4];
	unsigned int jj = 0,ii;
	unsigned int fftSubcarrierStartIndex;

	fftSubcarrierStartIndex =((LteData[cellNo].fftSize) - (LteData[cellNo].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK))/2;

	refSignalStartIndex = LteData[cellNo].RsRecord.ID % 3;

	for(ii=0;ii<3;ii++)
	{
		if(ii!=refSignalStartIndex)
		{
			index[jj] = ii; // Indexing the non reference signal resource element in the 1st 6 REs of the resource block
			index[jj+2]= ii+3;
			++jj;            
		}
	}


kb = 6* ((LteData[cellNo].RsRecord.ID) % (2* LteData[cellNo].numResouceBlocks)); //6.7.4 TS 36.211

for(unsigned int zp = 0; zp < 4; zp++)
{
	//Calculating PCFICH Subcarrier Index - Resource Element
k = ((kb + (unsigned int)floor((double)zp*LteData[cellNo].numResouceBlocks/2)
	                         * NUM_SUBCARRIER_PER_RESOURCE_BLOCK/2 ))
							 %
							 (LteData[cellNo].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK);
	                          //6.7.4 TS 36.211

//Calculate the actual frequency indices -FFT Index
if(k >(LteData[cellNo].numResouceBlocks *NUM_SUBCARRIER_PER_RESOURCE_BLOCK/2))
		{
	       	k = k + fftSubcarrierStartIndex + 1; //Adding the DC Subcarrier offset for the Subcarriers beyond the central DC subcarrier
		}
		else
		{

		     k= k + fftSubcarrierStartIndex ;
		}
ltePCFICHFreqIndices[4*zp]    = k + index[0];
ltePCFICHFreqIndices[4*zp +1] = k + index[1];
ltePCFICHFreqIndices[4*zp +2] = k + index[2];
ltePCFICHFreqIndices[4*zp +3] = k + index[3];
}

return LTE_SUCCESS;

}

}