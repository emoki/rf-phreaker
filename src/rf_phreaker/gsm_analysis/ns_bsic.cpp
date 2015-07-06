#include "rf_phreaker/gsm_analysis/netstart.h"
#include "rf_phreaker/gsm_analysis/ns_bsic.h"
#include <cmath>


// For Convolutional Decoding
#define BSIC_CONVDEC_NUM_BIT_PERIODS		39


GsmBsicDecoder::GsmBsicDecoder() :
samples_per_symbol_(4),
xcorr_len_(2 * BSIC_BURST_NUM_BITS_PAD * samples_per_symbol_ + 1),
conv_decoder_(BSIC_CONVDEC_NUM_BIT_PERIODS)
{
	XCorrMag = ALLOCTYPE( xcorr_len_ );
	if ( !XCorrMag ) throw BSIC_INIT_ERROR;
}


BSICDecoderMsgType GsmBsicDecoder::DecodeBSIC(const DATASTRUCT *SyncBurst, int IF_Freq_Hz, BSICChannelInfoType *SyncInfo,
	modulated_signal_correlator& sync_correlator)
{
	double input_samples_per_symbol = (double)(samples_per_symbol_ * sync_correlator.Downsample_Factor()) /
		(double)sync_correlator.Upsample_Factor();

	unsigned int DataLen = ROUND( (GSM_BITS_PER_BURST + (BSIC_BURST_NUM_BITS_PAD*2)) * input_samples_per_symbol );

	const int Sync_TS_Offset = (39+3) * samples_per_symbol_;

	unsigned int i, PeakLoc;
	double PhaseShift;

	const DATASTRUCT *Start, *BSICData;
	DATATYPE Peak;

	float *Encoded;
	ConvDecodedType Decoded;
	int returnval = BSIC_NO_ERROR;

	Start = SyncBurst - ROUND( BSIC_BURST_NUM_BITS_PAD * input_samples_per_symbol );

	// decimate the input and calculate sync correlation
	float rNorm = (float)-IF_Freq_Hz/(float)(input_samples_per_symbol * GSM_BIT_RATE);
	sync_correlator.Correlate(Start, DataLen, rNorm, Sync_TS_Offset, xcorr_len_);
	ippsMagnitude_32fc(sync_correlator.Correlation_Data(), XCorrMag, xcorr_len_);
	const DATASTRUCT *dData = sync_correlator.Resampled_Data();
	const DATASTRUCT *XCorr = sync_correlator.Correlation_Data();


	// Find the peak
	Peak = 0.0;
	PeakLoc = 0;
	for( i = 0; i < xcorr_len_; i++ ) {
		if( XCorrMag[i] > Peak ) {
			Peak = XCorrMag[i];
			PeakLoc = i;
		}
	}

	PhaseShift = atan2( IMAGPART(XCorr[PeakLoc]), REALPART(XCorr[PeakLoc]) );
	BSICData = dData + PeakLoc;

	// Phase correction is done with the demod
	if ( DemodulateBurst148(BSICData, SyncBits, PhaseShift) ) return BSIC_DEMOD_ERROR;


	// re-format the Sync data to remove the training sequence
	// and interleave the two convolutionally encoded streams
	// Note that the first 39 data points are OK as is
	// so just moved the last 39 bits adjacent to the first 39
	// Skip the first 3 tail bits
	Encoded = SyncBits + 3;
	memmove( Encoded + BSIC_CONVDEC_NUM_BIT_PERIODS,
		Encoded + BSIC_CONVDEC_NUM_BIT_PERIODS + 64,
		BSIC_CONVDEC_NUM_BIT_PERIODS * sizeof(Encoded[0]) );

	returnval |= conv_decoder_.Decode(Encoded, &Decoded);
	returnval |= BlockDecode(Decoded, SyncInfo);

	return (BSICDecoderMsgType)returnval;
}



int GsmBsicDecoder::DemodulateBurst148(const DATASTRUCT* BurstMod, float* Demod, double PhaseShift) const
{
	int BitPos = 0;
	const DATASTRUCT *BM = BurstMod;
	const float CosPS = (float)cos(PhaseShift);
	const float SinPS = (float)sin(PhaseShift);
	const int SampPerBit = samples_per_symbol_;

	if ( (BurstMod==NULL) || (Demod==NULL) ) return -1;

	while ( BitPos < GSM_BITS_PER_BURST )
	{
		// BitPos % 4 = 0, i.e. BitPos = 4*k + 0
		BM += SampPerBit;
		Demod[BitPos++] = IMAGPART(*BM) * CosPS
			- REALPART(*BM) * SinPS;

		// BitPos % 4 = 1, i.e. BitPos = 4*k + 1
		BM += SampPerBit;
		Demod[BitPos++] = -REALPART(*BM) * CosPS
			- IMAGPART(*BM) * SinPS;

		// BitPos % 4 = 2, i.e. BitPos = 4*k + 2
		BM += SampPerBit;
		Demod[BitPos++] = -IMAGPART(*BM) * CosPS
			+ REALPART(*BM) * SinPS;

		// BitPos % 4 = 3, i.e. BitPos = 4*k + 3
		BM += SampPerBit;
		Demod[BitPos++] = REALPART(*BM) * CosPS
			+ IMAGPART(*BM) * SinPS;
	}
	return 0;
}


BSICDecoderMsgType GsmBsicDecoder::BlockDecode(const ConvDecodedType Encoded, BSICChannelInfoType *SyncInfo) const
{
	const unsigned int Divisor = 0x575;

	// Least significant 25 bits are data
	// then the next 10 bits are parity
	// and the next 4 bits should be 0
	const unsigned __int32 Parity = (unsigned __int32)(Encoded >> 25) & 0x3FF;
	unsigned __int32 Dividend = (unsigned __int32)(Encoded & 0x1FFFFFF);

	unsigned int T1, T2, T3;
	int ShiftCount;
	int returnval = BSIC_NO_ERROR;

	SyncInfo->BCC = (Dividend >> 2) & 0x7;
	SyncInfo->NCC = (Dividend >> 5) & 0x7;

	T1 = (Dividend & 0x00000003) << 9;
	T1 |= ( (Dividend & 0x0000FF00) >> 7 );
	T1 |= ( (Dividend & 0x00800000) >> 23 );
	SyncInfo->T1 = T1;

	T2 = (Dividend >> 18) & 0x1F;
	if ( T2 > 25 ) {
		T2 = 0;
		returnval |= BSIC_BLK_DECODE_T2;
	}
	SyncInfo->T2 = T2;

	T3 = (Dividend & 0x00030000) >> 15;
	T3 |= ( (Dividend & 0x01000000) >> 24);
	if ( T3 > 4 ) {
		T3 = 0;
		returnval |= BSIC_BLK_DECODE_T3;
	}
	SyncInfo->T3 = T3;

	// The 4 MSB's should all be 0
	if ( Encoded >> 35 ) returnval |= BSIC_BLK_DECODE_MSB_NONZERO;

	for ( ShiftCount=0; ShiftCount<25; ShiftCount++ ) {
		if ( Dividend & 0x1 ) Dividend ^= Divisor;
		Dividend >>= 1;
	}
	if ( (Dividend + Parity) != 0x3FF ) returnval |= BSIC_BLK_DECODE_PARITY;

	return (BSICDecoderMsgType)returnval;
}


GsmBsicDecoder::~GsmBsicDecoder()
{
	ippsFree(XCorrMag);
}


unsigned int GetTDMAFrameNumber(const BSICChannelInfoType RFN)
{
	unsigned int T3, TMod;

	if ( RFN.T2 > 25 ) return 0;
	if ( RFN.T3 > 4 ) return 0;

	T3 = RFN.T3 * 10 + 1;
	TMod = (T3 + 26 - RFN.T2) % 26;
	return ( T3 + (51 * TMod) + (51 * 26 * RFN.T1) );
}
