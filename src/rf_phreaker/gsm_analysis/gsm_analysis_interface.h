#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_DLL
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllimport))
#else
#define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#endif
#define DLL_LOCAL
#else
#if __GNUC__ >= 4
#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define DLL_PUBLIC
#define DLL_LOCAL
#endif
#endif

#include "rf_phreaker/gsm_analysis/gsm_analysis_data.h"
#include "rf_phreaker/gsm_analysis/netstart.h"
#include <ipp.h>


#define GSM_ANALYSIS_MAX_NUM_IF_FREQS			19

class DLL_PUBLIC gsm_processor
{
public:
	gsm_processor(
		bool do_sweep,
		unsigned int max_num_data_samples=NETSTART_SNAPSHOT_MAX_NUM_SAMPLES,
		unsigned int samples_per_symbol=4,
		unsigned int upsample_factor=2, unsigned int downsample_factor=9
	);
	~gsm_processor();
	int GsmAnalysis(
		const Ipp32fc *pData, const int iDataLength,
		gsm_analysis_output_list **head_row,
		const float bandPowThresh, const float sidePowThresh,
		const unsigned int IFFreqOffsetHz=0,
		const bool ProcessFreq[GSM_ANALYSIS_MAX_NUM_IF_FREQS]=NULL
	);
	gsm_analysis_output_list* GsmClearOutput( gsm_analysis_output_list *psuHead );
	int CopySignalFromTemplate(Ipp32fc *Data);
	double input_data_sampling_rate_hz() const { return input_data_sampling_rate_hz_; };
	unsigned int upsample_factor() const { return upsample_factor_; };
	unsigned int downsample_factor() const { return downsample_factor_; };

	int DecodeBsic(
		const Ipp32fc *pData, const int iDataLength,
		rf_phreaker::gsm_measurement &meas);

	int DecodeBcchBurst(
		const Ipp32fc *pData, const int iDataLength,
		rf_phreaker::gsm_measurement &meas);

protected:
	static const unsigned int data_bits_per_symbol_;
	const unsigned int samples_per_symbol_;
	double input_data_sampling_rate_hz_;
	const unsigned int upsample_factor_, downsample_factor_;
	GSMStruct m_suGSMStruct;
	bool m_bInitialized;
};

