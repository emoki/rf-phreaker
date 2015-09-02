#pragma once
#include "rf_phreaker/gsm_analysis/modulated_signal_correlator.h"
#include "rf_phreaker/gsm_analysis/netstart.h"
#include "rf_phreaker/gsm_analysis/ns_bsic.h"
#include "rf_phreaker/gsm_analysis/ns_cgi.h"
#include "rf_phreaker/gsm_analysis/gsm_measurement.h"

#define SYNC_NO_ERROR			0
#define SYNC_OUT_OF_MEMORY		1
#define SYNC_LPF_ERROR			2



typedef struct _SyncStruct {
	const TemplateStruct	*t;
	const DATASTRUCT		*data;
	int						datasize;
	DATATYPE				nspb;
	DATATYPE				tb;
	DATATYPE				blocksize;
	int						step_size;
	int						num_windows;
	int						window_offset;
	int						window_size;
	int						sync_size;
	int						fs;
} SyncStruct;



class GsmSyncProcessor
{
public:
	GsmSyncProcessor( const SyncStruct *s,
		//const TemplateStruct& t,
		// TODO: sampling_freq should be an enum of defined values,
		// limited to a specific set such as (1083333, 4875000, 9750000)
//		unsigned int sampling_freq,
		unsigned int upsample_factor, unsigned int downsample_factor
//		unsigned int blocksize, unsigned int step_size,
//		unsigned int num_windows*/
	);
	~GsmSyncProcessor();
	int sync_analysis(const DATASTRUCT *data, unsigned int datasize,
		float bandpow_threshold, float sidepow_threshold,
		gsm_analysis_output_list *head);

	int bsic_analysis(const DATASTRUCT *data, unsigned int datasize, rf_phreaker::gsm_measurement &meas);
	int bcch_burst_analysis(const DATASTRUCT *data, unsigned int datasize, rf_phreaker::gsm_measurement &meas);

protected:
	bool ValidBcchData(BSICChannelInfoType RFN, unsigned int sync_location);

	SyncStruct s_;
	const TemplateStruct *t;

	bool ProcessBSIC_;
	bool ProcessCGI_;
	unsigned int downfac_;
	unsigned int upfac_;
	unsigned int offset_length_;
	unsigned int tsstart_;
	double t_delta_fcch_;
	double t_delta_sync_;
	unsigned int datasize_;
	Ipp32f   *xcorr_mag_fcch_;
	Ipp32f   *xcorr_mag_sync_;
	Ipp32f   *xcorr_mag_;
	modulated_signal_correlator *fcch_correlator_;
	modulated_signal_correlator *sync_correlator_;
	GsmBsicDecoder *BSIC_Decoder_;
	GsmCgiDecoder *CGI_Decoder_;
};
