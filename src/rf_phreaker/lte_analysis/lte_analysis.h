#pragma once



#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>  

#include "rf_phreaker/ipp_custom/ipp.h"
#include "rf_phreaker/lte_analysis/lte_errors.h"

#define LTE_ANALYSIS_IF_STEPSIZE_KHZ			100
#define LTE_ANALYSIS_PSS_SEARCH_MAX_IF_KHZ		1500
#define LTE_ANALYSIS_PSS_SEARCH_MAX_NUM_IF		(((2*LTE_ANALYSIS_PSS_SEARCH_MAX_IF_KHZ)/LTE_ANALYSIS_IF_STEPSIZE_KHZ) + 1)

enum hardware_sampling_rate
{

	data_sampling_rate_4875 = 0,
	data_sampling_rate_9750 = 1


};


struct WindLteData
{
	LteMeasurement* const Measurements;
	const unsigned int MaxNumMeasurements;
	unsigned int NumMeasurements;
	double AvgChannelRMSVoltage;
	WindLteData(LteMeasurement *Meas, unsigned int MaxNum=0) :
		Measurements(Meas), MaxNumMeasurements(MaxNum), NumMeasurements(0),
		AvgChannelRMSVoltage(0.0) {};
	WindLteData(const WindLteData &a) :
		Measurements(a.Measurements), MaxNumMeasurements(a.MaxNumMeasurements), NumMeasurements(a.NumMeasurements),
		AvgChannelRMSVoltage(a.AvgChannelRMSVoltage) {};

	void clear()
	{
		memset(Measurements, 0, sizeof(LteMeasurement) * MaxNumMeasurements);
		AvgChannelRMSVoltage = 0;
	}
};

struct WindPssSearchData
{
	CORR_RECORD_TYPE CorrelationResult;
	bool IsValidLteChannel;
};

/*LTE_API*/ int LtePssSearcher(const Ipp32fc* SignalSamples, unsigned int NumSamples,
	unsigned int NumIFChannelsToProcess, int StartIF_kHz,
	double SampleRate, WindPssSearchData *PssSearchData);

/*LTE_API*/ int lte_decode_data(const Ipp32fc* SignalSamples,
					unsigned int NumSamples,
					unsigned int NumHalfFramesToProcess,
					hardware_sampling_rate hw_sampling_rate,
					WindLteData &LteData);

/*LTE_API*/ int lte_cell_search(const Ipp32fc* SignalSamples,
					unsigned int NumSamples,
					unsigned int NumHalfFramesToProcess,
					hardware_sampling_rate hw_sampling_rate,
					WindLteData &LteData);




#ifdef __cplusplus
}
#endif
