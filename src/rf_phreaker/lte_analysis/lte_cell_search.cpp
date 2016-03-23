#include <stdlib.h>
#include <memory.h>
#include <cmath>
#include <stdio.h>

#include "lte_analysis.h"
#include "lte_synchronization.h"

#include "lte_channel_estimation.h"
#include "lte_pbch.h" 
#include "lte_pcfich.h"
#include "lte_pdcch.h"
#include "lte_pdsch.h"
#include "lte_turbo_code_rate_match.h"
#include "lte_turbo_code.h"
#include <iostream>

namespace rf_phreaker {

#define _LTEANALYSIS_PSCHSSCH_

// LTE_CORR_METHOD will find peak correlations for combined PSCH/SSCH templates
#define _LTE_USE_CORR_METHOD 0

/* LTE Sample Rates */
const double SampleRate384=3.84e6;
//const double SampleRate384=7.68e6; //--RB
const double SampleRate192=1.92e6;
const double SampleRate768=7.68e6;

//const unsigned int SamplesPerSlot384 = 1920; //--RB
const unsigned int SamplesPerSlot384 = 3840;

const int signal_max_size = 655345;

/* Static Allocation of  memory for Channel Estimates per frame for all the antennas */	
Ipp32fc hEst[OFDM_SYMBOLS_PER_FRAME * NUM_FRAMES * MAX_FFT_SIZE * NUM_ANTENNA_MAX];

Ipp32f hNoiseVariance[256];



/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lte_cell_search(const Ipp32fc* SignalSamples,
					unsigned int NumSamples,
					unsigned int NumHalfFramesToProcess,
					lte_measurements &LteData, int &tmp_num_meas)
{
	const int record_size = 100;
	LTEProc_CorrRecordType pschCorrRecord[record_size] = {};
	LTEProc_CorrRecordType sschCorrRecord[record_size] = {};
	PBCHINFO pbchInfo[record_size] = {};
	CYCLICPREFIX cyclicPrefixMode[record_size] = {};

	unsigned int signalLength384, processSignalLength,current_frame_number;
	double delayTime1, delayTime2;
	Ipp32fc *signal192;
	Ipp32fc *corr192; Ipp32f *abscorr192; // for the PssSss corr
	unsigned int frameStartSampleIndex,subframeStartSampleIndex;
	CORRELATIONTYPE RSStrength, RSNorm;
	int bTrue;
	unsigned int numPschPeaks = 0, temp = 0, num_cell_id = 0;
	unsigned int ii,mib_decode_status;


	int status;
	unsigned int sampling_factor = 1;	
	double SampleRate;

	// Buffer at least a full second's worth of data.  Doing so prevents access violations 
	// from occurring when lte analysis oversteps.
	static ipp_32fc_array signal_buffer(NumSamples + 19200 * 4);
	if(signal_buffer.length() < NumSamples + 19200 * 4)
		signal_buffer.reset(NumSamples + 19200 * 4);
	signal_buffer.zero_out();
	signal192 = signal_buffer.get();
	ippsCopy_32fc(SignalSamples, signal192, NumSamples);

	unsigned int num_filter_output =0;

	mib_decode_status = 0;

	getHalfFrameTiming(pschCorrRecord, &numPschPeaks, signal192, NumHalfFramesToProcess);

	if(numPschPeaks > LteData.size())
		throw rf_phreaker::lte_analysis_error("Number of psch peaks exceed the maximum number of lte measurements.");

	//std::cout << "Lte PSS Time elapsed: " << lte_diffclock(end,begin) << " ms\n";

	for(ii=0;ii<numPschPeaks;ii++)
	{
		if(pschCorrRecord[ii].StartSampleNum<128+32)
		{
			pschCorrRecord[ii].StartSampleNum += (10*SamplesPerSlot384/2);
		}
	}


	getFrameTiming(signal192, NumHalfFramesToProcess, pschCorrRecord, numPschPeaks,
		sschCorrRecord, &num_cell_id, cyclicPrefixMode);

	if(num_cell_id > LteData.size())
		throw rf_phreaker::lte_analysis_error("Number of cells exceed the maximum number of lte measurements.");


	//std::cout << "Lte SSS Time elapsed: " << lte_diffclock(end,begin) << " ms\n";

	
	unsigned int uTmp1 = 140*NumHalfFramesToProcess/2*128; 
	unsigned int uTmp2 = NumHalfFramesToProcess/2*10;
		

	for(ii=0;ii<num_cell_id;ii++)
	{
		
		(pbchInfo+ii)->MasterIB.Bandwidth = LteBandwidth_Unknown;
		(pbchInfo+ii)->NumAntPorts = LteAntPorts_Unknown;

		mib_decode_status = 0;

		// Attempt PBCH decode only if we have a psch corr > threshold 
		// and DecodeBandwidthAntennaPort == true
		if (pschCorrRecord[ii].NormCorr >= 0.1f /*0.6f*/ /*0.8f*/ )
		{
			for(unsigned int antNum=0;antNum<4;antNum++)
			{
				if(antNum !=2)
				{
				LteChannelEst(hEst+antNum*uTmp1, hNoiseVariance+antNum*uTmp2, signal192,  
					sschCorrRecord[ii].StartSampleNum, sschCorrRecord[ii].ID, cyclicPrefixMode[ii],   
					antNum, NumHalfFramesToProcess/2,  LteBandwidth_1_4MHZ);
				}

			}

			mib_decode_status = BCH_decoding(pbchInfo+ii, signal192, hEst, hNoiseVariance, sschCorrRecord[ii].ID, cyclicPrefixMode[ii],
				                            sschCorrRecord[ii].StartSampleNum, NumHalfFramesToProcess/2, LteBandwidth_1_4MHZ);

			// std::cout << "Lte PBCH Time elapsed: " << lte_diffclock(end,begin) << " ms\n";
		}

		sschCorrRecord[ii].RMSCorr *= sschCorrRecord[ii].NormCorr;

		memcpy(&(LteData[ii].PschRecord), pschCorrRecord + ii, sizeof(*pschCorrRecord));
		memcpy(&(LteData[ii].SschRecord), sschCorrRecord + ii, sizeof(*sschCorrRecord));
		LteData[ii].RsRecord.ID = sschCorrRecord[ii].ID;
		LteData[ii].SschRecord.ID /= 3;

		LteData[ii].sync_quality = (LteData[ii].PschRecord.NormCorr + LteData[ii].SschRecord.NormCorr) / 2;

		LteData[ii].CyclicPrefix = cyclicPrefixMode[ii];

		LteData[ii].RsRecord.NormCorr = 0;
		LteData[ii].RsRecord.RMSCorr = 0;

		bTrue = calculateRSValues(signal192, sschCorrRecord[ii].ID, sschCorrRecord[ii].StartSampleNum, cyclicPrefixMode[ii], &RSStrength, &RSNorm, &(LteData[ii].AvgDigitalVoltage));

		//std::cout << "Lte Calculate RS Values Time elapsed: " << lte_diffclock(end,begin) << " ms\n";

		LteData[ii].RsRecord.RMSCorr = RSStrength;//RSRP
		LteData[ii].RsRecord.NormCorr = RSNorm; //RSRQ
		LteData[ii].RsRecord.StartSampleNum = sschCorrRecord[ii].StartSampleNum;

		LteData[ii].estimated_rssi = LteData[ii].AvgDigitalVoltage; 
		LteData[ii].estimated_rsrp = RSStrength;
		LteData[ii].estimated_rsrq = RSNorm;

		if(mib_decode_status == 0)
		{			
		 //ippsFree(signal_384);
		 continue;
		}

		LteData[ii].phich_duration = (pbchInfo + ii)->MasterIB.PHICHConfig.PhichDuration;
		LteData[ii].phich_resources = (pbchInfo + ii)->MasterIB.PHICHConfig.PhichResource;

		LteData[ii].NumAntennaPorts = (pbchInfo + ii)->NumAntPorts;
		LteData[ii].Bandwidth = (pbchInfo + ii)->MasterIB.Bandwidth;
	
		LteData[ii].frame_number = (pbchInfo+ii)->MasterIB.systemFrameNum;			
        

	}

    	
	tmp_num_meas = num_cell_id;
	

	return 0;

	
}

}