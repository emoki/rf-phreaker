#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <iostream>
#include "lte_fft.h"
#include "q_channel.h"
#include "lte_channel_estimation.h"
#include "lte_common.h"


// Output full format of channel matrix for a subframe
/*
void LteLsEstPilot(Ipp32fc* H_LS, Ipp32fc* pilotF, Ipp32fc* signalF, unsigned int* pilotSymbIdx, 
			unsigned int* pilotSubCarrierIdx, unsigned int*pPilotSymbNum, Ipp32fc* subFrameSignal, 
			unsigned int subFrameNo, unsigned int cellID, CYCLICPREFIX cyclicPrefixMode, 
			unsigned int slotLength, unsigned int RBNum, unsigned int RBNumMax, 
			unsigned int useSubCarriers, unsigned int FFTSize, unsigned int antPort)		
{
	unsigned int symbNum =*pPilotSymbNum;
	unsigned int curCpLen[2];
	Ipp32fc* signal1;
	Ipp32fc* H_LS0 = ippsMalloc_32fc(useSubCarriers);
	Ipp32fc* signalF2 = ippsMalloc_32fc(useSubCarriers);
	Ipp32fc* signal2 = ippsMalloc_32fc(FFTSize);
	

	if(cyclicPrefixMode==Normal)
	{
		curCpLen[0]=10;
		curCpLen[1]=9;
	}
	else
	{
		curCpLen[0] = 32;
		curCpLen[1] = 32;
	}
	
	for(unsigned int ii=0;ii<2;ii++)
	{
		unsigned int slotNo=2*subFrameNo+ii;
		unsigned int slotSampleShift = slotLength*ii; 

		generate_cell_RS(pilotF, pilotSymbIdx, &symbNum, pilotSubCarrierIdx, slotNo, cellID, 
			cyclicPrefixMode, RBNum, RBNumMax, antPort);

		for(unsigned int jj=0;jj<symbNum;jj++)
		{
			ippsZero_32fc(H_LS0, useSubCarriers); 

			unsigned int symbStart = curCpLen[0]+pilotSymbIdx[ii]*(curCpLen[1]+FFTSize)
				+slotSampleShift;

			signal1 = subFrameSignal + symbStart; 

			myfft(signal2, signal1, FFTSize);
			myfftshift(signalF+(2*ii+jj)*FFTSize, signal2, FFTSize);

			for(unsigned int kk=0;kk<useSubCarriers/2;kk++)
			{
				signalF2[kk].re = signalF[(2*ii+jj)*FFTSize+(FFTSize-useSubCarriers)/2+kk].re;
				signalF2[kk].im = signalF[(2*ii+jj)*FFTSize+(FFTSize-useSubCarriers)/2+kk].im;
				signalF2[kk+useSubCarriers/2].re = signalF[(2*ii+jj)*FFTSize+FFTSize/2+1+kk].re;
				signalF2[kk+useSubCarriers/2].im = signalF[(2*ii+jj)*FFTSize+FFTSize/2+1+kk].im;
			}


			for(unsigned int kk=0;kk<RBNum*2;kk++)
			{
				ippsDiv_32fc(signalF2+pilotSubCarrierIdx[RBNum*2*jj+kk], pilotF+RBNum*2*jj+kk, 
					H_LS0+pilotSubCarrierIdx[RBNum*2*jj+kk], 1);
				
			}

			for(unsigned int kk=0;kk<useSubCarriers/2;kk++)
			{
				H_LS[(2*ii+jj)*FFTSize+(FFTSize-useSubCarriers)/2+kk].re = H_LS0[kk].re;
				H_LS[(2*ii+jj)*FFTSize+(FFTSize-useSubCarriers)/2+kk].im = H_LS0[kk].im;
				H_LS[(2*ii+jj)*FFTSize+FFTSize/2+1+kk].re = H_LS0[kk+useSubCarriers/2].re;
				H_LS[(2*ii+jj)*FFTSize+FFTSize/2+1+kk].im = H_LS0[kk+useSubCarriers/2].im;
			}
			
		}
	}

	ippsFree(H_LS0);
	ippsFree(signalF2);
	ippsFree(signal2);
}
*/

// Output channel matrix for a subframe at pilot positions

void LteLsEstPilot(Ipp32fc* H_LS, Ipp32fc* pilotF, Ipp32fc* signalF, unsigned int* pilotSymbIdx, 
			unsigned int*pPilotSymbNum, Ipp16u* pilotSubCarrierIdx, Ipp32fc* subFrameSignal, 
			unsigned int subFrameNo, unsigned int cellID, CYCLICPREFIX cyclicPrefixMode, 
			unsigned int slotLength, unsigned int RBNum, unsigned int RBNumMax, 
			unsigned int useSubCarriers, unsigned int FFTSize, unsigned int antPort)		
{
	unsigned int symbNum;
	unsigned int curCpLen[2];
	Ipp32fc* signal1;

	Ipp32fc* signalF2 = ippsMalloc_32fc(useSubCarriers);
	Ipp32fc* signal2 = ippsMalloc_32fc(FFTSize);
	
	Ipp16u* pilotSubCarrierIdx1;

	if(cyclicPrefixMode==Normal)
	{
		switch(RBNum) //Added handling for other bandwidths --Raj,4 Oct 2011
				{
				case 6: //Bandwidth 1.4 Mhz
					curCpLen[0]=10;
					curCpLen[1]=9;
					break;

				case 15: //Bandwidth 3 Mhz
				curCpLen[0]=20;
				curCpLen[1]=18;
				break;

				case 25: //Bandwidth 5 Mhz
				curCpLen[0]=40;
				curCpLen[1]=36;
				break;

				case 50: //Bandwidth 10 Mhz
				curCpLen[0]=80;
				curCpLen[1]=72;
				break;

				case 75: //Bandwidth 15 Mhz
				curCpLen[0]=120;
				curCpLen[1]=108;
				break;

				case 100: //Bandwidth 20 Mhz
				curCpLen[0]=160;
				curCpLen[1]=144;
				break;

				default:
					printf("\nFunction %s:line %d --Unknown Bandwidth\n",__FUNCTION__,__LINE__);
					break;	
		
				}
		
		
	}
	else
	{
		curCpLen[0] = 32;
		curCpLen[1] = 32;
	}
	
	for(unsigned int ii=0;ii<2;ii++) //for two slots
	{
		unsigned int slotNo=2*subFrameNo+ii;
		unsigned int slotSampleShift = slotLength*ii; 

		if(antPort>1)
		{
			pilotSubCarrierIdx1 = pilotSubCarrierIdx+ii*2*RBNum;
		}
		else
		{
			pilotSubCarrierIdx1 = pilotSubCarrierIdx;
		}

		generate_cell_RS(pilotF+2*RBNum*2*ii, pilotSymbIdx, &symbNum, pilotSubCarrierIdx1, slotNo, cellID, 
			cyclicPrefixMode, RBNum, RBNumMax, antPort); //antPort

		for(unsigned int jj=0;jj<symbNum;jj++) //symbNum
		{
			unsigned int symbStart = curCpLen[0]+pilotSymbIdx[jj]*(curCpLen[1]+FFTSize)
				+slotSampleShift;

			signal1 = subFrameSignal + symbStart; 

			myfft(signal2, signal1, FFTSize);
			myfftshift(signalF+(2*ii+jj)*FFTSize, signal2, FFTSize); //possible wrong for number of antenan >2

			for(unsigned int kk=0;kk<useSubCarriers/2;kk++)
			{
				signalF2[kk].re = signalF[(2*ii+jj)*FFTSize+(FFTSize-useSubCarriers)/2+kk].re;
				signalF2[kk].im = signalF[(2*ii+jj)*FFTSize+(FFTSize-useSubCarriers)/2+kk].im;
				signalF2[kk+useSubCarriers/2].re = signalF[(2*ii+jj)*FFTSize+FFTSize/2+1+kk].re;
				signalF2[kk+useSubCarriers/2].im = signalF[(2*ii+jj)*FFTSize+FFTSize/2+1+kk].im;
			}


			for(unsigned int kk=0;kk<RBNum*2;kk++)
			{
				ippsDiv_32fc(pilotF+RBNum*2*(2*ii+jj)+kk, signalF2+pilotSubCarrierIdx1[RBNum*2*jj+kk], 
					H_LS+RBNum*2*(2*ii+jj)+kk, 1);
				
			}
			
		}
	}

	*pPilotSymbNum = symbNum;
	
	ippsFree(signalF2);
	ippsFree(signal2);
}

/*

	pilotSymbIdx: Reference symbol index in an LTE slot
	RSNumPerSlot: Number of Reference symbols in a LTE slot
	pilotSubCarrierIdx: Subcarrier index of Reference symbols in an OFDM symbol
	RSNumPerSymb: Number of Reference symbols in an OFDM symbol 
*/
void LteLinearInterpolat(Ipp32fc* H, unsigned int *subframesProcessed, Ipp32fc* H_LS, 
	unsigned int* pilotSymbIdx, unsigned int RSNumPerSlot, Ipp16u* pilotSubCarrierIdx,  
	unsigned int RSNumPerSymb, CYCLICPREFIX cyclicPrefixMode, unsigned int useSubCarriers, 
	unsigned int FFTSize, unsigned int subframesToProcess)
{
	unsigned int numSymbsPerSubframe;
	
	if(cyclicPrefixMode==Normal)
	{
		numSymbsPerSubframe = 14;
	}
	else
	{
		numSymbsPerSubframe = 12;
	}

	unsigned int subframes = subframesToProcess;

	if(RSNumPerSlot==2)
	{
		Ipp32fc* H1 = ippsMalloc_32fc((numSymbsPerSubframe+1)*useSubCarriers);
		ippsZero_32fc(H1, (numSymbsPerSubframe+1)*useSubCarriers);
		Ipp16u idx1[5];
		idx1[0] = pilotSymbIdx[0];
		idx1[1] = pilotSymbIdx[1];
		idx1[2] = pilotSymbIdx[0]+numSymbsPerSubframe/2;
		idx1[3] = pilotSymbIdx[1]+numSymbsPerSubframe/2;
		idx1[4] = numSymbsPerSubframe;
		
		Ipp32fc* H2 = ippsMalloc_32fc((numSymbsPerSubframe+4)*useSubCarriers);
		ippsZero_32fc(H2, (numSymbsPerSubframe+4)*useSubCarriers);
		Ipp16u idx2[6];
		idx2[0] = 0;
		idx2[1] = pilotSymbIdx[0]+3;
		idx2[2] = pilotSymbIdx[1]+3;
		idx2[3] = pilotSymbIdx[0]+3+numSymbsPerSubframe/2;
		idx2[4] = pilotSymbIdx[1]+3+numSymbsPerSubframe/2;
		idx2[5] = numSymbsPerSubframe+3;

		Ipp32fc* H3 = ippsMalloc_32fc((numSymbsPerSubframe+3)*useSubCarriers);
		ippsZero_32fc(H3, (numSymbsPerSubframe+3)*useSubCarriers);
		Ipp16u idx3[5];
		idx3[0] = 0;
		idx3[1] = pilotSymbIdx[0]+3;
		idx3[2] = pilotSymbIdx[1]+3;
		idx3[3] = pilotSymbIdx[0]+3+numSymbsPerSubframe/2;
		idx3[4] = pilotSymbIdx[1]+3+numSymbsPerSubframe/2;

		float t1 = pilotSymbIdx[1]-pilotSymbIdx[0]-1;
		float t2 = numSymbsPerSubframe/2-pilotSymbIdx[1]-1; 
    	float ratio[2];
		ratio[0] = t1/(t1+t2); 
		ratio[1] = t2/(t1+t2);

		Ipp32fc* H_Last = ippsMalloc_32fc(2*useSubCarriers);
		ippsZero_32fc(H_Last, 2*useSubCarriers);

		Ipp16u* freqIdx2 = ippsMalloc_16u(RSNumPerSymb*RSNumPerSlot); 

		Ipp32fc* H_LS2 = ippsMalloc_32fc(RSNumPerSymb*RSNumPerSlot);
//		Ipp32fc H_LS2[24]; //debug only

		Ipp32fc* H4 = ippsMalloc_32fc(numSymbsPerSubframe+4);
		ippsZero_32fc(H4, numSymbsPerSubframe+4);

		Ipp32fc* H5 = ippsMalloc_32fc(numSymbsPerSubframe+4);
		ippsZero_32fc(H5, numSymbsPerSubframe+4);

		for(unsigned int ii=0;ii<subframes;ii++)
		{
			//first subframe
			if(ii==0)
			{
				//combine pilot in time domain for the first pilot symbol	
				if(pilotSubCarrierIdx[0]<pilotSubCarrierIdx[RSNumPerSymb])
				{
					for(unsigned int jj=0;jj<2;jj++)
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
						{
							H_LS2[kk*2+jj].re = H_LS[jj*RSNumPerSymb+kk].re;
							H_LS2[kk*2+jj].im = H_LS[jj*RSNumPerSymb+kk].im;

							freqIdx2[kk*2+jj] = pilotSubCarrierIdx[jj*RSNumPerSymb+kk];
						}
					}
				}
				else
				{
					for(unsigned int jj=0;jj<2;jj++)
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
						{
							H_LS2[kk*2+jj].re = H_LS[((jj+1)%2)*RSNumPerSymb+kk].re;
							H_LS2[kk*2+jj].im = H_LS[((jj+1)%2)*RSNumPerSymb+kk].im;

							freqIdx2[kk*2+jj] = pilotSubCarrierIdx[((jj+1)%2)*RSNumPerSymb+kk];
						}
					}
				}

				//Linear interpolation in frequency domain
				linearInterplate_fc(H1+idx1[0]*useSubCarriers, H_LS2, freqIdx2, 2*RSNumPerSymb, 
					0, useSubCarriers-1); //TODO:: 

				//Combine pilot in time domain for the middle pilot symbols	
				for(unsigned int jj=1;jj<5;jj++)
				{
					if(pilotSubCarrierIdx[0]<pilotSubCarrierIdx[RSNumPerSymb])
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
						{
							if((jj%2)==1)
							{
								H_LS2[kk*2].re = ratio[0]*H_LS[(jj-1)*RSNumPerSymb+kk].re+ratio[1]*H_LS[(jj+1)*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = ratio[0]*H_LS[(jj-1)*RSNumPerSymb+kk].im+ratio[1]*H_LS[(jj+1)*RSNumPerSymb+kk].im;

								H_LS2[kk*2+1].re = H_LS[jj*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = H_LS[jj*RSNumPerSymb+kk].im;
							}
							else
							{
								H_LS2[kk*2+1].re = ratio[1]*H_LS[(jj-1)*RSNumPerSymb+kk].re+ratio[0]*H_LS[(jj+1)*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = ratio[1]*H_LS[(jj-1)*RSNumPerSymb+kk].im+ratio[0]*H_LS[(jj+1)*RSNumPerSymb+kk].im;

								H_LS2[kk*2].re = H_LS[jj*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = H_LS[jj*RSNumPerSymb+kk].im;

							}
						}
					}
					else
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
						{
							if((jj%2)==1)
							{
								H_LS2[kk*2+1].re = ratio[0]*H_LS[(jj-1)*RSNumPerSymb+kk].re+ratio[1]*H_LS[(jj+1)*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = ratio[0]*H_LS[(jj-1)*RSNumPerSymb+kk].im+ratio[1]*H_LS[(jj+1)*RSNumPerSymb+kk].im;

								H_LS2[kk*2].re = H_LS[jj*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = H_LS[jj*RSNumPerSymb+kk].im;
							}
							else
							{
								H_LS2[kk*2].re = ratio[1]*H_LS[(jj-1)*RSNumPerSymb+kk].re+ratio[0]*H_LS[(jj+1)*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = ratio[1]*H_LS[(jj-1)*RSNumPerSymb+kk].im+ratio[0]*H_LS[(jj+1)*RSNumPerSymb+kk].im;

								H_LS2[kk*2+1].re = H_LS[jj*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = H_LS[jj*RSNumPerSymb+kk].im;

							}
						}
					}
					
					//Linear interpolation in frequency domain
					linearInterplate_fc(H1+idx1[jj]*useSubCarriers, H_LS2, freqIdx2, RSNumPerSymb*2, 0, useSubCarriers-1);  //TODO::
					
				}

				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					H_Last[jj].re = H1[idx1[3]*useSubCarriers+jj].re;
					H_Last[jj].im = H1[idx1[3]*useSubCarriers+jj].im;
					H_Last[jj+useSubCarriers].re = H1[idx1[4]*useSubCarriers+jj].re;
					H_Last[jj+useSubCarriers].im = H1[idx1[4]*useSubCarriers+jj].im;
				}

				//Linear interpolation in time domain
				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					for(unsigned int kk=0;kk<5;kk++)
					{
						H4[kk].re = H1[idx1[kk]*useSubCarriers+jj].re;
						H4[kk].im = H1[idx1[kk]*useSubCarriers+jj].im;
					}
					linearInterplate_fc(H5, H4, idx1, 5, 0, numSymbsPerSubframe-1); //TODO::

					for(unsigned int kk=0;kk<numSymbsPerSubframe;kk++)
					{
						if(jj<useSubCarriers/2)
						{
							H[kk*FFTSize+jj+(FFTSize-useSubCarriers)/2].re = H5[kk].re;
							H[kk*FFTSize+jj+(FFTSize-useSubCarriers)/2].im = H5[kk].im;
						}
						else
						{
							H[kk*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].re = H5[kk].re;
							H[kk*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].im = H5[kk].im;
						}
					}
				}
			}
			else if(ii==subframes-1)
			{
				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					H3[idx3[0]*useSubCarriers+jj].re = H_Last[jj].re;
					H3[idx3[0]*useSubCarriers+jj].im = H_Last[jj].im;
					H3[idx3[1]*useSubCarriers+jj].re = H_Last[jj+useSubCarriers].re;
					H3[idx3[1]*useSubCarriers+jj].im = H_Last[jj+useSubCarriers].im;
				}

				unsigned int tIdx = 2*RSNumPerSlot*ii;

				for(unsigned int jj=1;jj<3;jj++)
				{
					if(pilotSubCarrierIdx[0]<pilotSubCarrierIdx[RSNumPerSymb])
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
						{
							if((jj%2)==1)
							{
								H_LS2[kk*2].re = ratio[0]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re+ratio[1]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = ratio[0]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im+ratio[1]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].im;

								H_LS2[kk*2+1].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;
							}
							else
							{
								H_LS2[kk*2+1].re = ratio[1]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re+ratio[0]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = ratio[1]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im+ratio[0]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].im;

								H_LS2[kk*2].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;

							}
						}
					}
					else
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
						{
							if((jj%2)==1)
							{
								H_LS2[kk*2+1].re = ratio[0]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re+ratio[1]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = ratio[0]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im+ratio[1]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].im;

								H_LS2[kk*2].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;
							}
							else
							{
								H_LS2[kk*2].re = ratio[1]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re+ratio[0]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = ratio[1]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im+ratio[0]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].im;

								H_LS2[kk*2+1].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;

							}
						}
					}
					
					//Linear interpolation in frequency domain
					linearInterplate_fc(H3+idx3[jj+1]*useSubCarriers, H_LS2, freqIdx2, 2*RSNumPerSymb, 0, useSubCarriers-1); //TODO:: 
				}

				unsigned int jj=3;

				if(pilotSubCarrierIdx[0]<pilotSubCarrierIdx[RSNumPerSymb])
				{
					for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
					{
						if((jj%2)==1)
						{
							H_LS2[kk*2].re = H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re;
							H_LS2[kk*2].im = H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im;

							H_LS2[kk*2+1].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
							H_LS2[kk*2+1].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;
						}
						else
						{
							H_LS2[kk*2+1].re = H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re;
							H_LS2[kk*2+1].im = H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im;

							H_LS2[kk*2].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
							H_LS2[kk*2].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;

						}
					}
				}
				else
				{
					for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
					{
						if((jj%2)==1)
						{
							H_LS2[kk*2+1].re = H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re;
							H_LS2[kk*2+1].im = H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im;
							
							H_LS2[kk*2].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
							H_LS2[kk*2].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;
						}
						else
						{
							H_LS2[kk*2].re = H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re;
							H_LS2[kk*2].im = H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im;

							H_LS2[kk*2+1].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
							H_LS2[kk*2+1].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;
						}
					}
				}
				
				//Linear interpolation in frequency domain
				linearInterplate_fc(H3+idx3[jj+1]*useSubCarriers, H_LS2, freqIdx2, RSNumPerSymb*2, 0, useSubCarriers-1); //TODO:;

				//Linear interpolation in time domain
				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					for(unsigned int kk=0;kk<5;kk++)
					{
						H4[kk].re = H3[idx3[kk]*useSubCarriers+jj].re;
						H4[kk].im = H3[idx3[kk]*useSubCarriers+jj].im;
					}
					linearInterplate_fc(H5, H4, idx3, 5, 3, numSymbsPerSubframe+2); //TODO:: 

					for(unsigned int kk=0;kk<numSymbsPerSubframe;kk++)
					{
						if(jj<useSubCarriers/2)
						{
							H[(kk+14*ii)*FFTSize+jj+(FFTSize-useSubCarriers)/2].re = H5[kk].re;
							H[(kk+14*ii)*FFTSize+jj+(FFTSize-useSubCarriers)/2].im = H5[kk].im;
						}
						else
						{
							H[(kk+14*ii)*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].re = H5[kk].re;
							H[(kk+14*ii)*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].im = H5[kk].im;
						}
					}
				}
				
			}
			else
			{
				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					H2[idx2[0]*useSubCarriers+jj].re = H_Last[jj].re;
					H2[idx2[0]*useSubCarriers+jj].im = H_Last[jj].im;
					H2[idx2[1]*useSubCarriers+jj].re = H_Last[jj+useSubCarriers].re;
					H2[idx2[1]*useSubCarriers+jj].im = H_Last[jj+useSubCarriers].im;
				}

				unsigned int tIdx = 2*RSNumPerSlot*ii;

				for(unsigned int jj=1;jj<5;jj++)
				{
					if(pilotSubCarrierIdx[0]<pilotSubCarrierIdx[RSNumPerSymb])
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
						{
							if((jj%2)==1)
							{
								H_LS2[kk*2].re = ratio[0]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re+ratio[1]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = ratio[0]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im+ratio[1]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].im;

								H_LS2[kk*2+1].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;
							}
							else
							{
								H_LS2[kk*2+1].re = ratio[1]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re+ratio[0]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = ratio[1]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im+ratio[0]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].im;

								H_LS2[kk*2].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;

							}
						}
					}
					else
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
						{
							if((jj%2)==1)
							{
								H_LS2[kk*2+1].re = ratio[0]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re+ratio[1]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = ratio[0]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im+ratio[1]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].im;

								H_LS2[kk*2].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;
							}
							else
							{
								H_LS2[kk*2].re = ratio[1]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].re+ratio[0]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2].im = ratio[1]*H_LS[(jj-1+tIdx)*RSNumPerSymb+kk].im+ratio[0]*H_LS[(jj+1+tIdx)*RSNumPerSymb+kk].im;

								H_LS2[kk*2+1].re = H_LS[(jj+tIdx)*RSNumPerSymb+kk].re;
								H_LS2[kk*2+1].im = H_LS[(jj+tIdx)*RSNumPerSymb+kk].im;

							}
						}
					}
					
					//Linear interpolation in frequency domain
					linearInterplate_fc(H2+idx2[jj+1]*useSubCarriers, H_LS2, freqIdx2, 2*RSNumPerSymb, 0, useSubCarriers-1);  //TODO::
				}

				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					H_Last[jj].re = H2[idx2[4]*useSubCarriers+jj].re;
					H_Last[jj].im = H2[idx2[4]*useSubCarriers+jj].im;
					H_Last[jj+useSubCarriers].re = H2[idx2[5]*useSubCarriers+jj].re;
					H_Last[jj+useSubCarriers].im = H2[idx2[5]*useSubCarriers+jj].im;
				}

				//Linear interpolation in time domain
				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					for(unsigned int kk=0;kk<6;kk++)
					{
						H4[kk].re = H2[idx2[kk]*useSubCarriers+jj].re;
						H4[kk].im = H2[idx2[kk]*useSubCarriers+jj].im;
					}
					linearInterplate_fc(H5, H4, idx2, 6, 3, numSymbsPerSubframe+2); //TODO::

					for(unsigned int kk=0;kk<numSymbsPerSubframe;kk++)
					{
						if(jj<useSubCarriers/2)
						{
							H[(kk+14*ii)*FFTSize+jj+(FFTSize-useSubCarriers)/2].re = H5[kk].re;
							H[(kk+14*ii)*FFTSize+jj+(FFTSize-useSubCarriers)/2].im = H5[kk].im;
						}
						else
						{
							H[(kk+14*ii)*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].re = H5[kk].re;
							H[(kk+14*ii)*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].im = H5[kk].im;
						}
					}
				}
				
			}
		}
		
		ippsFree(H1);
		ippsFree(H2);
		ippsFree(H3);
		ippsFree(H4);
		ippsFree(H5);
		ippsFree(H_Last);
		ippsFree(H_LS2);

		ippsFree(freqIdx2);
	}
	else  //for case only one RS in each slot
	{
		Ipp32fc* H1 = ippsMalloc_32fc((numSymbsPerSubframe+2)*useSubCarriers);
		ippsZero_32fc(H1, (numSymbsPerSubframe+2)*useSubCarriers);
		Ipp16u idx1[3];
		idx1[0] = pilotSymbIdx[0];
		idx1[1] = pilotSymbIdx[0]+numSymbsPerSubframe/2;
		idx1[2] = numSymbsPerSubframe+1;
		
		Ipp32fc* H2 = ippsMalloc_32fc((3*numSymbsPerSubframe/2+1)*useSubCarriers);
		ippsZero_32fc(H2, (3*numSymbsPerSubframe/2+1)*useSubCarriers);
		Ipp16u idx2[4];
		idx2[0] = 0;
		idx2[1] = pilotSymbIdx[0]+numSymbsPerSubframe/2-1;
		idx2[2] = pilotSymbIdx[0]+numSymbsPerSubframe-1;
		idx2[3] = 3*numSymbsPerSubframe/2;

		Ipp32fc* H3 = ippsMalloc_32fc((numSymbsPerSubframe*3/2+1)*useSubCarriers);
		ippsZero_32fc(H3, (numSymbsPerSubframe*3/2+1)*useSubCarriers);
		Ipp16u idx3[3];
		idx3[0] = 0;
		idx3[1] = pilotSymbIdx[0]+numSymbsPerSubframe/2-1;
		idx3[2] = pilotSymbIdx[0]+numSymbsPerSubframe-1;


		Ipp32fc* H_Last = ippsMalloc_32fc(2*useSubCarriers);
		ippsZero_32fc(H_Last, 2*useSubCarriers);

		Ipp16u* freqIdx2 = ippsMalloc_16u(RSNumPerSymb*RSNumPerSlot); 

		Ipp32fc* H_LS2 = ippsMalloc_32fc(RSNumPerSymb*RSNumPerSlot);
//		Ipp32fc H_LS2[24]; //debug only
		Ipp32fc* H4 = ippsMalloc_32fc(numSymbsPerSubframe+4);
		ippsZero_32fc(H4, numSymbsPerSubframe+4);

		Ipp32fc* H5 = ippsMalloc_32fc(numSymbsPerSubframe+4);
		ippsZero_32fc(H5, numSymbsPerSubframe+4);


		for(unsigned int ii=0;ii<subframes;ii++)
		{
			//first subframe
			if(ii==0)
			{
				for(unsigned int jj=0;jj<3;jj++)
				{
					for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
					{
						H_LS2[kk].re = H_LS[jj*2*RSNumPerSymb+kk].re;
						H_LS2[kk].im = H_LS[jj*2*RSNumPerSymb+kk].im;
					}

					if((idx1[jj]%numSymbsPerSubframe)>numSymbsPerSubframe/2)
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
							freqIdx2[kk] = pilotSubCarrierIdx[RSNumPerSymb+kk];
					}
					else
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
							freqIdx2[kk] = pilotSubCarrierIdx[kk];
					}

					linearInterplate_fc(H1+idx1[jj]*useSubCarriers, H_LS2, freqIdx2, RSNumPerSymb, 
						0, useSubCarriers-1); 
				}
							
				
				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					H_Last[jj].re = H1[idx1[1]*useSubCarriers+jj].re;
					H_Last[jj].im = H1[idx1[1]*useSubCarriers+jj].im;
					H_Last[jj+useSubCarriers].re = H1[idx1[2]*useSubCarriers+jj].re;
					H_Last[jj+useSubCarriers].im = H1[idx1[2]*useSubCarriers+jj].im;
				}

				//Linear interpolation in time domain
				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					for(unsigned int kk=0;kk<3;kk++)
					{
						H4[kk].re = H1[idx1[kk]*useSubCarriers+jj].re;
						H4[kk].im = H1[idx1[kk]*useSubCarriers+jj].im;
					}
					linearInterplate_fc(H5, H4, idx1, 3, 0, numSymbsPerSubframe-1); //TODO::

					for(unsigned int kk=0;kk<numSymbsPerSubframe;kk++)
					{
						if(jj<useSubCarriers/2)
						{
							H[kk*FFTSize+jj+(FFTSize-useSubCarriers)/2].re = H5[kk].re;
							H[kk*FFTSize+jj+(FFTSize-useSubCarriers)/2].im = H5[kk].im;
						}
						else
						{
							H[kk*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].re = H5[kk].re;
							H[kk*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].im = H5[kk].im;
						}
					}
				}
			}
			else if(ii==subframes-1)
			{
				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					H3[idx3[0]*useSubCarriers+jj].re = H_Last[jj].re;
					H3[idx3[0]*useSubCarriers+jj].im = H_Last[jj].im;
					H3[idx3[1]*useSubCarriers+jj].re = H_Last[jj+useSubCarriers].re;
					H3[idx3[1]*useSubCarriers+jj].im = H_Last[jj+useSubCarriers].im;
				}

				unsigned int tIdx = 2*RSNumPerSlot*ii;

				for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
				{
					H_LS2[kk].re = H_LS[(tIdx+1)*2*RSNumPerSymb+kk].re;
					H_LS2[kk].im = H_LS[(tIdx+1)*2*RSNumPerSymb+kk].im;

					freqIdx2[kk] = pilotSubCarrierIdx[kk];
				}

				linearInterplate_fc(H3+idx3[2]*useSubCarriers, H_LS2, freqIdx2, RSNumPerSymb, 
						0, useSubCarriers-1); 

				//Linear interpolation in time domain
				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					for(unsigned int kk=0;kk<3;kk++)
					{
						H4[kk].re = H3[idx3[kk]*useSubCarriers+jj].re;
						H4[kk].im = H3[idx3[kk]*useSubCarriers+jj].im;
					}
					linearInterplate_fc(H5, H4, idx3, 3, 6, numSymbsPerSubframe+5); //TODO:: 

					for(unsigned int kk=0;kk<numSymbsPerSubframe;kk++)
					{
						if(jj<useSubCarriers/2)
						{
							H[(kk+14*ii)*FFTSize+jj+(FFTSize-useSubCarriers)/2].re = H5[kk].re;
							H[(kk+14*ii)*FFTSize+jj+(FFTSize-useSubCarriers)/2].im = H5[kk].im;
						}
						else
						{
							H[(kk+14*ii)*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].re = H5[kk].re;
							H[(kk+14*ii)*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].im = H5[kk].im;
						}
					}
				}
				
			}
			else
			{
				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					H2[idx2[0]*useSubCarriers+jj].re = H_Last[jj].re;
					H2[idx2[0]*useSubCarriers+jj].im = H_Last[jj].im;
					H2[idx2[1]*useSubCarriers+jj].re = H_Last[jj+useSubCarriers].re;
					H2[idx2[1]*useSubCarriers+jj].im = H_Last[jj+useSubCarriers].im;
				}

				unsigned int tIdx = 2*RSNumPerSlot*ii;

				for(unsigned int jj=1;jj<3;jj++)
				{
					for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
					{
						H_LS2[kk].re = H_LS[(jj+tIdx)*2*RSNumPerSymb+kk].re;
						H_LS2[kk].im = H_LS[(jj+tIdx)*2*RSNumPerSymb+kk].im;
					}

					if((idx2[jj+1]%numSymbsPerSubframe)>numSymbsPerSubframe/2)
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
							freqIdx2[kk] = pilotSubCarrierIdx[RSNumPerSymb+kk];
					}
					else
					{
						for(unsigned int kk=0;kk<RSNumPerSymb;kk++)
							freqIdx2[kk] = pilotSubCarrierIdx[kk];
					}

					linearInterplate_fc(H2+idx2[jj+1]*useSubCarriers, H_LS2, freqIdx2, RSNumPerSymb, 
						0, useSubCarriers-1); 
				}

				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					H_Last[jj].re = H2[idx2[2]*useSubCarriers+jj].re;
					H_Last[jj].im = H2[idx2[2]*useSubCarriers+jj].im;
					H_Last[jj+useSubCarriers].re = H2[idx2[3]*useSubCarriers+jj].re;
					H_Last[jj+useSubCarriers].im = H2[idx2[3]*useSubCarriers+jj].im;
				}
				
				//Linear interpolation in time domain
				for(unsigned int jj=0;jj<useSubCarriers;jj++)
				{
					for(unsigned int kk=0;kk<4;kk++)
					{
						H4[kk].re = H2[idx2[kk]*useSubCarriers+jj].re;
						H4[kk].im = H2[idx2[kk]*useSubCarriers+jj].im;
					}
					linearInterplate_fc(H5, H4, idx2, 4, 6, numSymbsPerSubframe+5); //TODO::

					for(unsigned int kk=0;kk<numSymbsPerSubframe;kk++)
					{
						if(jj<useSubCarriers/2)
						{
							H[(kk+14*ii)*FFTSize+jj+(FFTSize-useSubCarriers)/2].re = H5[kk].re;
							H[(kk+14*ii)*FFTSize+jj+(FFTSize-useSubCarriers)/2].im = H5[kk].im;
						}
						else
						{
							H[(kk+14*ii)*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].re = H5[kk].re;
							H[(kk+14*ii)*FFTSize+jj+FFTSize/2-useSubCarriers/2+1].im = H5[kk].im;
						}
					}
				}
				
			}
		}

		
		ippsFree(H1);
		ippsFree(H2);
		ippsFree(H3);
		ippsFree(H_Last);
		ippsFree(H4);
		ippsFree(H5);
	
		ippsFree(H_LS2);

		ippsFree(freqIdx2);
	}
}



void LteNoiseVarEst(Ipp32f* noiseVar, Ipp32fc* H, CYCLICPREFIX cyclicPrefixMode, 
	unsigned int useSubCarriers, unsigned int FFTSize, unsigned int RBNum, 
	unsigned int subframesToProcess, unsigned int DLBW)
{
	unsigned int numSymbsPerSubframe, curCPLen;

	if(cyclicPrefixMode==Normal)
		curCPLen = 10*FFTSize/128;
	else
		curCPLen = 32*FFTSize/128;

	if(cyclicPrefixMode==Normal)
	{
		numSymbsPerSubframe = 14;
	}
	else
	{
		numSymbsPerSubframe = 12;
	}

	Ipp32fc* H1 = ippsMalloc_32fc(numSymbsPerSubframe*subframesToProcess*useSubCarriers);

	for(unsigned int ii=0;ii<subframesToProcess;ii++)
	{
		for(unsigned int jj=0;jj<numSymbsPerSubframe;jj++)
		{
//			printf("jj = %d\n", jj);
			for(unsigned int kk=0;kk<useSubCarriers/2;kk++)
			{
				H1[ii*numSymbsPerSubframe*useSubCarriers+jj*useSubCarriers+kk].re = 
					H[14*ii*FFTSize+jj*FFTSize+FFTSize/2-useSubCarriers/2].re;
				H1[ii*numSymbsPerSubframe*useSubCarriers+jj*useSubCarriers+kk].im = 
					H[14*ii*FFTSize+jj*FFTSize+FFTSize/2-useSubCarriers/2].im;

				H1[ii*numSymbsPerSubframe*useSubCarriers+jj*useSubCarriers+kk+useSubCarriers/2].re = 
					H[14*ii*FFTSize+jj*FFTSize+kk+FFTSize/2+1].re;
				H1[ii*numSymbsPerSubframe*useSubCarriers+jj*useSubCarriers+kk+useSubCarriers/2].im = 
					H[14*ii*FFTSize+jj*FFTSize+kk+FFTSize/2+1].im;
			}
		}
	}

	//Q matrix can be precomputed to reduce complexity
	Ipp32fc* QmatConj; // = ippsMalloc_32fc(useSubCarriers*useSubCarriers); 
	//GetQmat(QmatConj, DLBW); //TODO::
	
	//QmatConj = QcChannelP[DLBW]; --Temporarily commented to work for other DLBW values -Raj,4 Oct 2011
	QmatConj = QcChannelP[0];//--Hardcoded DLBW == 0 -Raj,4 Oct 2011

	Ipp32fc* vec1 = ippsMalloc_32fc(useSubCarriers); 

	for(unsigned int ii=0;ii<subframesToProcess;ii++)
	{
		double noise0=0;

		for(unsigned int jj=0;jj<numSymbsPerSubframe;jj++)
		{
			multMatVect_fc(vec1, QmatConj, useSubCarriers, useSubCarriers, 
				H1+ii*numSymbsPerSubframe*useSubCarriers+jj*useSubCarriers);

			for(unsigned int kk=curCPLen;kk<useSubCarriers;kk++)
			{
				noise0 = noise0 + vec1[kk].re*vec1[kk].re+vec1[kk].im*vec1[kk].im;
			}
		}

		noiseVar[ii] = noise0/(numSymbsPerSubframe*(useSubCarriers-curCPLen));
		noiseVar[ii+1] = noise0/(numSymbsPerSubframe*(useSubCarriers-curCPLen));
		noiseVar[ii+2] = noise0/(numSymbsPerSubframe*(useSubCarriers-curCPLen));
		noiseVar[ii+3] = noise0/(numSymbsPerSubframe*(useSubCarriers-curCPLen));
		noiseVar[ii+4] = noise0/(numSymbsPerSubframe*(useSubCarriers-curCPLen));

		ii = ii+5;
	}

	ippsFree(H1);
	ippsFree(vec1);
	
}


/*
void GetQmat(Ipp32fc *QmatConj, unsigned int FFTSize, unsigned int useSubCarriers, 
	unsigned int curCPLen) //TODO::
{
	unsigned int row = 0;
	
	Ipp32fc *subFMat = ippsMalloc_32fc(useSubCarriers*curCPLen);
	
	for(unsigned int ii=FFTSize/2-useSubCarriers/2;ii<FFTSize/2;ii++)
	{
		for(unsigned int jj=0;jj<curCPLen;jj++)
		{
			subFMat[row*curCPLen+jj].re = cos(2*PI*ii*jj/FFTSize);
			subFMat[row*curCPLen+jj].im = sin(-2*PI*ii*jj/FFTSize);
		}
		row++;
	}

	for(unsigned int ii=FFTSize/2+1;ii<FFTSize/2+useSubCarriers/2+1;ii++)
	{
		for(unsigned int jj=0;jj<curCPLen;jj++)
		{
			subFMat[row*curCPLen+jj].re = cos(2*PI*ii*jj/FFTSize);
			subFMat[row*curCPLen+jj].im = sin(-2*PI*ii*jj/FFTSize);
		}
		row++;
	}

	
}*/



/* ----------------------------------------------
	
 	Description: Perform channel estimation from Reference signal for each antenna
  	Input: 
	Output: 
		H: Channel matrix (140*framesToProcess)x(FFTSize) for each antenna
		pVar: point to average variance
		
	Notes: use interpolation for initial version. May upgrade to MMSE later
	Log: Created by J Peng 11/13/2010
	
--------------------------------------------------*/

void LteChannelEst(Ipp32fc* H, Ipp32f* pVar, Ipp32fc* inSignal, 
	unsigned int frameStart, unsigned int cellID, CYCLICPREFIX cyclicPrefixMode,   
	unsigned int antPort, unsigned int framesToProcess, unsigned int DLBW)
{
	unsigned int FFTSize, useSubCarriers;
	
	switch(DLBW)
	{
		case LteBandwidth_1_4MHZ:
			FFTSize = 128;
        	useSubCarriers = 72;
			break;
		case LteBandwidth_3MHZ:
	        FFTSize = 256;
	        useSubCarriers = 180;
			break;
	    case LteBandwidth_5MHZ:
	        FFTSize = 512;
	        useSubCarriers = 300;
			break;
	    case LteBandwidth_10MHZ:
	        FFTSize = 1024;
	        useSubCarriers = 600;
			break;
		case LteBandwidth_15MHZ:
	        FFTSize = 1536;
	        useSubCarriers = 900;
			break;
	    case LteBandwidth_20MHZ:
	        FFTSize = 2048;
	        useSubCarriers = 1200;
			break;
		default:
			printf("Unsupport bandwidth\n");
			//exit(-1);
			break;		

	}

	unsigned int RBNumTx = useSubCarriers/12; //RB number transmitted  
	unsigned int RBNumRx; //RB number received by LTE receiver. 
						  //Since the BW of LTE scanner is not equal to acutal BW of LTE signal
						  //RBNumRx<=RBNumTx
	
	
	// For 4.875MHz receiver
	if(FFTSize == 512) // the scanner BW 4.875MHz, can receive 26 RBs = 312 subcarriers
	{
		FFTSize = 512;
		if ((RBNumTx % 2) == 1)
			  RBNumRx = 25; 
		  else
			  RBNumRx = 26;	
		  //RBNumRx = 50;//Raj
		  //FFTSize = 1024;//Raj
		  useSubCarriers = RBNumRx*12;
	}

	if(FFTSize == 1024)
	{
		RBNumRx = 50;//Raj
		FFTSize = 1024;//Raj
	}
	
	// For 8 MHz receiver
/*	if(FFTSize > 512) 
	{
		FFTSize = 512;
		if((RBNumTx%2)==1)
			RBNumRx = 41; 
		else
			RBNumRx = 42; 
		
		useSubCarriers = RBNumRx*12;
	}*/
	
	RBNumRx = useSubCarriers/12;

	
	unsigned int RBNumMax = 110;
	
	unsigned int slotLength = 960*FFTSize/128;
	unsigned int subFrameLength = 2*slotLength;
	unsigned int frameLength = 10*subFrameLength;
	
	Ipp32fc* subFrameSignal;

	//Free memory later
	Ipp32fc* H_LS0 = ippsMalloc_32fc(40*framesToProcess*2*RBNumRx); //store H matrix only at pilot positions
	Ipp32fc* signalF = ippsMalloc_32fc(4*FFTSize);
	Ipp32fc* pilotF = ippsMalloc_32fc(4*2*RBNumRx);

	ippsZero_32fc(H_LS0, 40*framesToProcess*2*RBNumRx);
	ippsZero_32fc(signalF, 4*FFTSize);
	ippsZero_32fc(pilotF, 4*2*RBNumRx);
	
	unsigned int pilotSymbIdx[2];
	Ipp16u* pilotSubCarrierIdx = ippsMalloc_16u(RBNumRx*2*2);
//	unsigned int pilotSubCarrierIdx[440]; 

	unsigned int pilotSymbNum;

	Ipp32fc *H_LS;

	H_LS = H_LS0;
	

	for(unsigned int frames=0;frames<framesToProcess;frames++)
	{
		unsigned int subframeStart=frameStart;
		
		for(unsigned int subFrameNo=0;subFrameNo<10;subFrameNo++)
		{
			subFrameSignal = inSignal+ subframeStart;

			//First perform Least square (LS) channel estimation
			LteLsEstPilot(H_LS, pilotF, signalF, pilotSymbIdx, &pilotSymbNum, pilotSubCarrierIdx, 
				subFrameSignal, subFrameNo, cellID, cyclicPrefixMode, slotLength, RBNumRx, 
				RBNumMax, useSubCarriers, FFTSize, antPort);


			H_LS = H_LS+4*2*RBNumRx;;
			subframeStart += subFrameLength;
		}
		frameStart += frameLength;	
	}

	unsigned int subframesToProcess = framesToProcess*10;
	unsigned int subframesProcessed = 0;
	
	LteLinearInterpolat(H, &subframesProcessed, H_LS0, pilotSymbIdx, pilotSymbNum, pilotSubCarrierIdx, 
		2*RBNumRx, cyclicPrefixMode, useSubCarriers, FFTSize, subframesToProcess);

clock_t begin_nvar=clock();	
	LteNoiseVarEst(pVar, H, cyclicPrefixMode, useSubCarriers, FFTSize, 
    	RBNumRx, subframesToProcess, DLBW); //average noise variance  estimate
clock_t end_nvar=clock();
//std::cout << "Lte Noise Var Time elapsed: " << lte_diffclock(end_nvar,begin_nvar) << " ms\n";

	
	ippsFree(H_LS0);
	ippsFree(signalF);
	ippsFree(pilotF);
	
	ippsFree(pilotSubCarrierIdx);

//	free(pilotSubCarrierIdx);

}







