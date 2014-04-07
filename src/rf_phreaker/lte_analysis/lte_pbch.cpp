
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>


#include "lte_fft.h"
#include "lte_pbch.h"
#include "lte_common.h"
#include "lte_crc_16.h"
#include "pbch_interleaver_idx.h"

namespace rf_phreaker {

void getPBCHFreqIdx(unsigned int *PBCHFreqIdx0, CYCLICPREFIX cyclicPrefixMode, 
	CELLIDTYPE cellID, unsigned int FFTSize)
{
	unsigned int RSStartIdx = cellID%3;

	unsigned int idx[2];

	unsigned int PBCHFreqIdx[4][73];

	unsigned jj = 0;
	for(unsigned int ii=0;ii<3;ii++)
	{
		if(ii!=RSStartIdx)
		{
			idx[jj++] = ii;
		}
	}

	unsigned int dataIdx1[48];

	dataIdx1[0] = idx[0];
	dataIdx1[1] = idx[1];

	for(unsigned int ii=2;ii<48;ii+=2)
	{
		dataIdx1[ii] = dataIdx1[ii-2]+3;  
		dataIdx1[ii+1] = dataIdx1[ii-1]+3;  
	}

	PBCHFreqIdx[0][0] = 48; //the first one is the length of frequency index
	PBCHFreqIdx[1][0] = 48;
	for(unsigned int ii=1;ii<=48;ii++)
	{
		PBCHFreqIdx[0][ii] = dataIdx1[ii-1];
		PBCHFreqIdx[1][ii] = dataIdx1[ii-1];
	}
	PBCHFreqIdx[2][0] = 72;
	for(unsigned int ii=1;ii<=72;ii++)
		PBCHFreqIdx[2][ii] = ii-1;

	if(cyclicPrefixMode==Normal)
	{
		PBCHFreqIdx[3][0] = 72;
		for(unsigned int ii=1;ii<=72;ii++)
			PBCHFreqIdx[3][ii] = ii-1;
	}
	else
	{
		PBCHFreqIdx[3][0] = 48;
		for(unsigned int ii=1;ii<=48;ii++)
			PBCHFreqIdx[3][ii] = dataIdx1[ii-1];
	}

	unsigned int usedSubCarriers = 72;

	for(unsigned int ii=0;ii<4;ii++)
	{
		unsigned int len = PBCHFreqIdx[ii][0];

		for(unsigned int jj=0;jj<len/2;jj++)
		{
			PBCHFreqIdx[ii][jj+1] = PBCHFreqIdx[ii][jj+1] + (FFTSize-usedSubCarriers)/2;
			PBCHFreqIdx[ii][jj+1+len/2] = PBCHFreqIdx[ii][jj+1+len/2] + 1 
				+ (FFTSize-usedSubCarriers)/2;
		}
	}

	for(unsigned int ii=0;ii<4;ii++)
	{
		for(unsigned int jj=0;jj<73;jj++)
		{
			PBCHFreqIdx0[ii*73+jj] = PBCHFreqIdx[ii][jj];
		}
	}
}



void softPBCHDeSrambling(Ipp32f* outLLR, Ipp32f* inLLR, unsigned int frameNo, 
	CYCLICPREFIX cyclicPrefixMode, CELLIDTYPE cellID)
{
	unsigned int len, pbchSeq[1920];
	
	if(cyclicPrefixMode==Normal)
	{
		len = 1920;
	}
	else
	{
		len = 1728;
	}

	generate_PN_seq(pbchSeq, cellID, len);
	
	unsigned int startPos = len/4*frameNo;

	softDeSrambling(outLLR, inLLR, len/4, pbchSeq+startPos);
}



void softPBCHRateDeMatching(Ipp32f* outLLR, Ipp32f* inLLR, unsigned int frameNo, 
	CYCLICPREFIX cyclicPrefixMode)
{
	unsigned int *interleaverIdx; 
	unsigned int len, jj;
	
	if(cyclicPrefixMode==Normal)
	{
		len = 1920/4;
		interleaverIdx = PBCHInterIdx0; //generated in matlab, so need adjust index for C
	}
	else
	{
		len = 1728/4;
		interleaverIdx = PBCHInterIdx1;
	}

	for(unsigned int ii=0;ii<120;ii++)
		outLLR[ii] = 0.0;
	
	for(unsigned int ii=frameNo*len;ii<(frameNo+1)*len;ii++)
	{
		jj = interleaverIdx[ii]-1;
		outLLR[jj] = outLLR[jj] + inLLR[ii-frameNo*len];		
	}
}


unsigned int PBCHCRCVerify(unsigned int* bitSeq, unsigned int antNum)
{
	unsigned int *CRCSeq;
	unsigned int CRCSeq2[16]; 
	unsigned char CRCByteSeq[2], CRCByteSeq2[2], dateByteSeq[3];

	CRCSeq = bitSeq+24;
	
	switch(antNum)
	{
		case 1:
			for(unsigned ii=0;ii<16;ii++)
				CRCSeq2[ii] = CRCSeq[ii];
			break;
		case 2:
			for(unsigned ii=0;ii<16;ii++)
			{
				if(CRCSeq[ii])
					CRCSeq2[ii] = 0;
				else
					CRCSeq2[ii] = 1;
			}
			break;
		case 4:
			for(unsigned ii=0;ii<16;ii+=2)
			{
				CRCSeq2[ii] = CRCSeq[ii];
				if(CRCSeq[ii+1])
					CRCSeq2[ii+1] = 0;
				else
					CRCSeq2[ii+1] = 1;
			}
			break;
		default:
			printf("Unsupported antenna numbers\n");
			break;
				
	}

	bit2byte(CRCByteSeq, CRCSeq2, 16, 0);
	bit2byte(dateByteSeq, bitSeq, 24, 0);

	LteCRC16(CRCByteSeq2, dateByteSeq, 3);

	if((CRCByteSeq[0]==CRCByteSeq2[0])&&(CRCByteSeq[1]==CRCByteSeq2[1]))
		return(1);
	else
		return(0);
}


void getPBCH(PBCHINFO* pbchInfo, unsigned int* bitSeq, unsigned int SFN0, 
	unsigned int antNum, unsigned int frameNo)
{
	unsigned int idx = (bitSeq[0]<<2)+(bitSeq[1]<<1)+bitSeq[2];
	
	switch(idx)
	{
		case 0:
			pbchInfo->MasterIB.Bandwidth = LteBandwidth_1_4MHZ;
			break;
		case 1:
			pbchInfo->MasterIB.Bandwidth = LteBandwidth_3MHZ;
			break;
		case 2:
			pbchInfo->MasterIB.Bandwidth = LteBandwidth_5MHZ;
			break;
		case 3:
			pbchInfo->MasterIB.Bandwidth = LteBandwidth_10MHZ;
			break;
		case 4:
			pbchInfo->MasterIB.Bandwidth = LteBandwidth_15MHZ;
			break;
		case 5:
			pbchInfo->MasterIB.Bandwidth = LteBandwidth_20MHZ;
			break;
		default:
			pbchInfo->MasterIB.Bandwidth = LteBandwidth_Unknown;
			break;
	}

	if(bitSeq[3])
		pbchInfo->MasterIB.PHICHConfig.PhichDuration = PHICH_Extended;
	else
		pbchInfo->MasterIB.PHICHConfig.PhichDuration = PHICH_Normal;

	idx = (bitSeq[4]<<1)+bitSeq[5];

	switch(idx)
	{
		case 0:
			pbchInfo->MasterIB.PHICHConfig.PhichResource= PHICH_oneSixth;
			break;
		case 1:
			pbchInfo->MasterIB.PHICHConfig.PhichResource= PHICH_half;
			break;
		case 2:
			pbchInfo->MasterIB.PHICHConfig.PhichResource= PHICH_one;
			break;
		case 3:
			pbchInfo->MasterIB.PHICHConfig.PhichResource= PHICH_two;
			break;
		default:
			pbchInfo->MasterIB.PHICHConfig.PhichResource= PHICH_Unknown;
			break;
	}

	unsigned int SFN = 0;

	for(unsigned int ii=6;ii<14;ii++)
	{
		SFN = (SFN<<1)+bitSeq[ii];
	}

	pbchInfo->MasterIB.systemFrameNum = (SFN<<2)+SFN0-frameNo;

	pbchInfo->NumAntPorts = (LteNumAntennaPorts)antNum;
	
	
}


int BCH_decoding(PBCHINFO* pbchInfo, Ipp32fc* inSignal, Ipp32fc* H,  Ipp32f* noiseVar, 
	CELLIDTYPE cellID, CYCLICPREFIX cyclicPrefixMode, unsigned int frameStart, 
	unsigned int framesToProcess, LteChannelBandwidth Bandwidth)
{
	unsigned int FFTSize, usedSubCarriers;

	
	switch(Bandwidth)
	{
		case LteBandwidth_1_4MHZ:
			FFTSize = 128;
			usedSubCarriers = 72;
			break;
		case LteBandwidth_3MHZ:
			FFTSize = 256;
			usedSubCarriers = 180;
			break;
		case LteBandwidth_5MHZ:
			FFTSize = 512;
			usedSubCarriers = 300;
			break;
		case LteBandwidth_10MHZ:
			FFTSize = 1024;
			usedSubCarriers = 600;
			break;
		case LteBandwidth_15MHZ:
			FFTSize = 1536;
			usedSubCarriers = 900;
			break;
		case LteBandwidth_20MHZ:
			FFTSize = 2048;
			usedSubCarriers = 1200;
			break;
		default:
			printf("unknown bandwidth\n");
			break;
	}

	unsigned int RBNumMax = 110;
	unsigned int RBNum = usedSubCarriers/12;
	unsigned int slotLength = 960*FFTSize/128;
	unsigned int subFrameLength = slotLength*2;
	unsigned int frameLength = subFrameLength*10;

	unsigned int curCPLength[2];
	unsigned int OFDMSymbsPerSlot;
	
	if(cyclicPrefixMode==Normal)
	{
		curCPLength[0] = 10*FFTSize/128;
		curCPLength[1] = 9*FFTSize/128;
		OFDMSymbsPerSlot = 7;
	}
	else
	{
		curCPLength[0] = 32*FFTSize/128;
		curCPLength[1] = 32*FFTSize/128;
		OFDMSymbsPerSlot = 6;
	}

	Ipp32fc* signal1 = inSignal + frameStart + slotLength;
	
	Ipp32f CCInLLR[1440];

	for(unsigned int ii=0;ii<1440;ii++)
		CCInLLR[ii] = 0;

	 Ipp32f noiseVar0[4];

	unsigned int frameShift = 0;
		
	Ipp32fc* signalF = ippsMalloc_32fc(FFTSize*4); 
	Ipp32fc* signal2 = ippsMalloc_32fc(FFTSize);

	Ipp32fc signalF2[72];
	Ipp32fc H2[288];

	Ipp32f detLLR1[480], detLLR2[480], detLLR3[120];

	unsigned int bitSeq[40];

	unsigned int bTrue;

	unsigned antNum[3]={1, 2, 4};

	unsigned int PBCHFreqIdx1[4][73];

	LTEMODULATION moduMode = MQPSK;

	getPBCHFreqIdx((unsigned int*)PBCHFreqIdx1, cyclicPrefixMode, cellID, FFTSize);

	for(unsigned int ii=0;ii<(4<framesToProcess?4:framesToProcess);ii++) // 4 frames of PBCH to process
	{
		for(unsigned int jj=0;jj<4;jj++) // 4 symbols have PBCH in each frame
		{
			unsigned int symbStart = curCPLength[0]+jj*(curCPLength[1]+FFTSize)+frameShift;

			myfft(signal2, signal1+symbStart, FFTSize);
			myfftshift(signalF+jj*FFTSize, signal2, FFTSize);
		}

		for(unsigned int jj=0;jj<3;jj++) 
		{
			noiseVar0[jj] = (noiseVar[jj*2*framesToProcess+ii]+
				noiseVar[jj*2*framesToProcess+ii+1])/2;
		}
		
		for(unsigned int jj=0;jj<3;jj++)  // 3 antenna setup assumption:  [1, 2, 4]
		{
			unsigned int bitNum = 0;
			for(unsigned int kk=0;kk<4;kk++)
			{
				unsigned int symbolIdx = kk + ii*20*OFDMSymbsPerSlot+OFDMSymbsPerSlot;
			
				unsigned numIdx = PBCHFreqIdx1[kk][0];

				for(unsigned int nn=0;nn<numIdx;nn++)
				{
					signalF2[nn] = signalF[kk*FFTSize + PBCHFreqIdx1[kk][nn+1]];
					
					for(unsigned int ll=0;ll<antNum[jj];ll++)
					{
						H2[ll*numIdx+nn] = H[ll*140*framesToProcess*FFTSize+
							symbolIdx*FFTSize+PBCHFreqIdx1[kk][nn+1]]; 
					}
				}
				
				stDiversityDet(detLLR1+bitNum, signalF2, H2, numIdx,antNum[jj], moduMode, noiseVar0);
				bitNum = bitNum + 2*numIdx;
			}

			for(unsigned int kk=0;kk<4;kk++) // 4 assumptions for current frame No.
			{
				unsigned frameNo = (ii+kk)%4;

				softPBCHDeSrambling(detLLR2, detLLR1, frameNo, cyclicPrefixMode, cellID);
                softPBCHRateDeMatching(detLLR3, detLLR2, frameNo, cyclicPrefixMode);

				for(unsigned int nn=0;nn<120;nn++)
				{
					CCInLLR[jj*480+kk*120+nn] = CCInLLR[jj*480+kk*120+nn] + detLLR3[nn];
				}
                

//				printf("frames %d  antennas %d current frame no %d\n", ii, antNum[jj], kk);
                LTE_CC_decoding(bitSeq, CCInLLR+jj*480+kk*120, 120);
                bTrue = PBCHCRCVerify(bitSeq, antNum[jj]);

                if(bTrue==1)
                {
                    getPBCH(pbchInfo, bitSeq, kk, antNum[jj], ii); //TODO::
                    break;
                }
			}
            
            if(bTrue==1)
           		break;
		}

		if(bTrue==1)
            break;
        
        frameShift = frameShift+frameLength;
	}

	

	ippsFree(signalF);
	ippsFree(signal2);

    if(bTrue==1)
		return 1;
	else
		return 0;

}

}