/*==========================================================================
						REVISION HISTORY

	Dhaval Dave'
		Re-worked for decimated input 18 samples per GSM bit period.

==========================================================================*/

#include "stdafx.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "rf_phreaker/gsm_analysis/gsm_analysis_interface.h"
#include "rf_phreaker/gsm_analysis/gsm_sync_templates.h"
#include "rf_phreaker/gsm_analysis/gsm_measurement.h"
#include "rf_phreaker/gsm_analysis/netstart.h"
#include <fstream>


int gsm_analysis( GSMStruct *in );
int gsm_init( GSMStruct *s );
void mem_cleanup_gsm( GSMStruct *s );


const unsigned int gsm_processor::data_bits_per_symbol_ = GSM_BITS_PER_SYMBOL;


gsm_processor::~gsm_processor()
{
	mem_cleanup_gsm( &m_suGSMStruct );
	m_bInitialized = false;
}


gsm_processor::gsm_processor(bool do_sweep,
	unsigned int max_num_data_samples,
	unsigned int samples_per_symbol,
	unsigned int upsample_factor, unsigned int downsample_factor
) :
m_bInitialized(false),
samples_per_symbol_(samples_per_symbol),
upsample_factor_(upsample_factor),
downsample_factor_(downsample_factor)
{
	memset(&m_suGSMStruct, 0, sizeof m_suGSMStruct);

	if ( !upsample_factor_ || !downsample_factor_  || !samples_per_symbol_ )
		throw GSM_UNDEFINED_ERROR;

	// TODO: right now only allow up/down factors = 2, 9
	// and native processor rate = 4 samples per bit
	// This can be changed once we have a list of allowable values in a lookup table.
	if ( (upsample_factor_ != 2) || (downsample_factor_ != 9)
		|| (samples_per_symbol_ != 4) )
		throw GSM_UNDEFINED_ERROR;

	// Here, "resampling" refers to the change in sampling rate required
	// to convert from the native processing data sample rate to the
	// input data sample rate.
	// Hence, we would multiply the native rate by (down rate)/(up rate)
	// to calculate the input data rate.
	unsigned int resample_rate_remainder = downsample_factor_ % upsample_factor_;
	bool integer_resampling = !resample_rate_remainder;

	unsigned int i_samples_per_input_data_symbol = samples_per_symbol_ * (downsample_factor_ / upsample_factor_);
	double d_samples_per_input_data_symbol = (double)i_samples_per_input_data_symbol;
	double samples_per_GSM_Bit = d_samples_per_input_data_symbol / (double)data_bits_per_symbol_;
	input_data_sampling_rate_hz_ = samples_per_GSM_Bit * (double)GSM_BIT_RATE;
	// If not integer resampling, we can be a little more accurate
	// by adding in the fractional part separately,
	if ( !integer_resampling )
	{
		double fractional_symbols = (double)(samples_per_symbol_ * resample_rate_remainder) / (double)upsample_factor_;
		d_samples_per_input_data_symbol += fractional_symbols;
		samples_per_GSM_Bit += fractional_symbols * (double)data_bits_per_symbol_;
		input_data_sampling_rate_hz_ += fractional_symbols * (double)data_bits_per_symbol_ * (double)GSM_BIT_RATE;
		i_samples_per_input_data_symbol = (unsigned int)(d_samples_per_input_data_symbol + 0.5);
	}
	m_suGSMStruct.fs = (unsigned int)(input_data_sampling_rate_hz_ + 0.5);
	m_suGSMStruct.nspb = (DATATYPE) (samples_per_GSM_Bit);


	// TODO: blocksize should be picked based on input sampling rate.
	// It's probably best to have a lookup-table instead of an equation.
	const int iBLOCKSIZE_2	=	4096 / upsample_factor_;
	const int iMAX_DOPPLER	=	RF_PHREAKER_MAX_DOPPLER;
	const int iFREQ_DRIFT	=	RF_PHREAKER_MAX_FREQ_DRIFT;
	const int iFREQ_OFFSET	=	(iMAX_DOPPLER + iFREQ_DRIFT);
	const int iLPF_BW		=	200;
	const double dTb		=	1.0/(double)GSM_BIT_RATE;
	const double dTslot		=	dTb * (double)GSM_BURST_LEN_BITS;

	double dBlocksize = input_data_sampling_rate_hz_ * dTslot;
	// Amount of header information to skip
	double dLeadingZeros = 0;

	// Max num of samples - initially for 60ms = 292500 with sample at 4875000
	// 60ms is equal to 13 bursts, which guarantees at least one full
	// FCCH and SYNC burst inside the data vector.
	// TODO : this should go in RF_PHREAKER_Defs.h
	//unsigned int MaxDataSize = (unsigned int)(13.0 * GSM_BITS_PER_FRAME * samples_per_GSM_Bit) + 1;
	// TODO - testing to see if this helps us decode layer 3 faster...
	unsigned int MaxDataSize = (unsigned int)(2 * 13.0 * GSM_BITS_PER_FRAME * samples_per_GSM_Bit) + 1;
	if(max_num_data_samples > MaxDataSize)
		m_suGSMStruct.datasize = MaxDataSize;
	else m_suGSMStruct.datasize = max_num_data_samples;

	m_suGSMStruct.blocksize = (DATATYPE) dBlocksize;
	m_suGSMStruct.step_size = (int)(dBlocksize * 0.3);
	m_suGSMStruct.fft_size = iBLOCKSIZE_2;
	m_suGSMStruct.ps_size = iBLOCKSIZE_2;
	m_suGSMStruct.downfac = downsample_factor_;
	m_suGSMStruct.upfac = upsample_factor_;
	// Check only FCCHs within th1 dB of peak across ALL channels
	m_suGSMStruct.fcch_s.fcch_th1 = 60;
	m_suGSMStruct.tb = (DATATYPE) dTb;
	m_suGSMStruct.FreqToProcess = NULL;
	m_suGSMStruct.NumFreqs = 0;

	////////////////////////////////////////////////////////////
	//       Template initialization
	// Get from embedded resource.
	// NOTE: the initialization here MUST be performed in this
	// EXACT order so that the template pointers align properly!
	////////////////////////////////////////////////////////////

	m_suGSMStruct.templates.fcch.data = 0;
	m_suGSMStruct.templates.fcch.length = 0;
	m_suGSMStruct.templates.dummy.data = 0;
	m_suGSMStruct.templates.dummy.length = 0;
	m_suGSMStruct.templates.sync.data = &template_sync[0];
	m_suGSMStruct.templates.sync.length = template_sync.size(); //GSM_NUM_SYNCTS_BITS * samples_per_symbol_
	for(int i = 0; i<8; i++) {
		m_suGSMStruct.templates.ts[i].data = &templates_ts[i][0];
		m_suGSMStruct.templates.ts[i].length = templates_ts[i].size(); // GSM_NUM_NORMTS_BITS * samples_per_symbol_;
	}

	// If we want sweep mode, then set the sync_size to 0.
	// This flag will inhibit the init and processing of the sync.
	if (do_sweep) m_suGSMStruct.sync_s.sync_size = 0;
	else m_suGSMStruct.sync_s.sync_size = m_suGSMStruct.datasize;
	int iErrorNum = gsm_init(&m_suGSMStruct);
	if ( iErrorNum )
	{
		throw iErrorNum;
	}

	m_bInitialized = true;


}


int gsm_processor::GsmAnalysis(
	const Ipp32fc *pData, const int iDataLength,
	gsm_analysis_output_list **head_row,
	const float bandPowThresh, const float sidePowThresh,
	const unsigned int IFFreqOffsetHz,
	const bool ProcessFreq[GSM_ANALYSIS_MAX_NUM_IF_FREQS]
)
{
	int iGSMError;

	if ( ! m_bInitialized ) return GSM_ANALYSIS_NOT_INITIALIZED;
	if ( pData == NULL ) return GSM_ANALYSIS_NULL_INPUT;

	m_suGSMStruct.filedata = NULL;
	m_suGSMStruct.datalength = iDataLength;
	ippsCopy_32fc(pData, m_suGSMStruct.data, m_suGSMStruct.datalength);
	// TODO: maybe just do m_suGSMStruct.data = pData??  need to re-configure s_.data then.
	m_suGSMStruct.NumFreqs = ( IFFreqOffsetHz );
	m_suGSMStruct.fcch_th2 = bandPowThresh;
	m_suGSMStruct.fcch_th3 = sidePowThresh;
	m_suGSMStruct.ProcessBCCH = false;

	iGSMError = gsm_analysis( &m_suGSMStruct );
	*head_row = m_suGSMStruct.head_row;
	if ( (iGSMError != 0) && (*head_row != NULL) )
	// ... which would mean that there was an error during processing,
	// like an FCCH or SYNC processing error OR it could also mean
	// that though there were FCCHs found, no SYNCs were found
	{
		// TODO: is this the right thing to do?
		// i.e., clear out row #1 and delete all others?
		memset( *head_row, 0, sizeof(GsmAnalysisDataType) );
		GsmClearOutput( (*head_row)->next );
		(*head_row)->next = NULL;
	}
	return iGSMError;
}

int gsm_processor::DecodeBsic(
	const Ipp32fc *pData, const int iDataLength,
	rf_phreaker::gsm_measurement &meas) {
	int iGSMError;
	if(!m_bInitialized) return GSM_ANALYSIS_NOT_INITIALIZED;
	iGSMError = m_suGSMStruct.sync_processor->bsic_analysis(pData, iDataLength, meas);
	return iGSMError;
}

int gsm_processor::DecodeBcchBurst(
	const Ipp32fc *pData, const int iDataLength,
	rf_phreaker::gsm_measurement &meas) {
	int iGSMError;
	if(!m_bInitialized) return GSM_ANALYSIS_NOT_INITIALIZED;
	iGSMError = m_suGSMStruct.sync_processor->bcch_burst_analysis(pData, iDataLength, meas);
	return iGSMError;
}

gsm_analysis_output_list* gsm_processor::GsmClearOutput(gsm_analysis_output_list *psuHead)
{
	if(m_bInitialized)
		return del_rows(psuHead);
	else
		return 0;
}


int gsm_processor::CopySignalFromTemplate(Ipp32fc *Data)
{
	return 0;
}
