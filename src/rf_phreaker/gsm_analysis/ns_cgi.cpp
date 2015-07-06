#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <string.h>
#include <direct.h>

#include "rf_phreaker/gsm_analysis/netstart.h"
#include "rf_phreaker/gsm_analysis/ns_cgi.h"


// For outputting Bcch data; TEST PURPOSES ONLY
//static FILE* BcchFile = NULL;


//********************************************************
//              For CGI demodulation
//********************************************************

// Number of GSM bits BEFORE the start of the reported TS
// at which we start correlation
#define CGI_BURST_NUM_BITS_PAD		5
// TODO:: Change resampling parameters so they are derived, not defined constants.
#define CGI_UPSAMPLE_RATE			_NETSTART_HW_DECIMATION_FACTOR
#define CGI_DOWNSAMPLE_RATE			9
#define CGI_RESAMPLE_RATE			(CGI_UPSAMPLE_RATE) / (CGI_DOWNSAMPLE_RATE)
#define CGI_RESAMP_PER_GSM_BIT		(NETSTART_SAMPLES_PER_GSM_BIT * CGI_RESAMPLE_RATE)
#define CGI_MAX_INPUT_LEN			(NETSTART_SAMPLES_PER_GSM_BIT * (GSM_BITS_PER_BURST + CGI_BURST_NUM_BITS_PAD*2) + 1)
#define CGI_MAX_DCVT_LEN			((CGI_MAX_INPUT_LEN * CGI_RESAMPLE_RATE) + 1)

#define CGI_LPF_FREQ		(135000/CGI_UPSAMPLE_RATE)
// TODO:: setup filter length to be a minimum length depending on cutoff freqs desired
#define CGI_LPF_LEN			256

// put into GSM_Defs.h as appropriate
#define CGI_NUM_CONV_BITS 228
#define CGI_NUM_DATA_BITS 184
#define CGI_NUM_PARITY_BITS 40
#define CGI_MAX_CONV_ERR 150
#define CGI_NUM_TOTAL_BLKDECODE_BITS (CGI_NUM_DATA_BITS + CGI_NUM_PARITY_BITS)
#define CGI_CONVDEC_NUM_BIT_PERIODS (CGI_NUM_CONV_BITS)

//TODO: fix this!
//const float CGIResampleFactor = (float)CGI_RESAMPLE_RATE;
const float CGIResampleFactor = 2.f/9.f;



/***********************************************************************
* INIT function
*
* Inputs:
*	Burst: None
* Outputs:
*	<return>: Error code
*
* Calculates the required length of the buffers that will store
* the down-converted and filtered data.  Memory for these buffers
* is allocated.  The CGI_Initialized state variable is set upon success.
* This function corresponds to a C++ constructor.
/**********************************************************************/
GsmCgiDecoder::GsmCgiDecoder(const TemplateStruct *psuTemplate) :
samples_per_symbol_(4),
xcorr_len_(2 * CGI_BURST_NUM_BITS_PAD * samples_per_symbol_ + 1),
conv_decoder_(CGI_CONVDEC_NUM_BIT_PERIODS),
Len_TS_04_(psuTemplate->ts[0].length),
bcch_correlator_(NULL)
{
	// This would imply a coding error!
	if (CGI_NUM_DATA_BITS % 8) throw CGI_OTHER_ERROR;

	TAPTYPE TempBuf[CGI_LPF_LEN];
	double rFreq;
	int i;

	if ( Len_TS_04_ != GSM_NUM_NORMTS_BITS * samples_per_symbol_ )
		throw(CGI_INIT_ERROR);

	double input_samples_per_symbol = (double)(samples_per_symbol_ * CGI_DOWNSAMPLE_RATE) /
		(double)CGI_UPSAMPLE_RATE;
	DataLen = ROUND( (GSM_BITS_PER_BURST + (CGI_BURST_NUM_BITS_PAD*2)) * input_samples_per_symbol );
	BurstPadLen = ROUND( CGI_BURST_NUM_BITS_PAD * input_samples_per_symbol );
	RESAMPLE_ITERATIONS = DataLen / CGI_DOWNSAMPLE_RATE;
	dDataLen = RESAMPLE_ITERATIONS * CGI_UPSAMPLE_RATE;
	XCorrLen = xcorr_len_;

	if ( (DataLen > CGI_MAX_INPUT_LEN)
		|| (dDataLen > CGI_MAX_DCVT_LEN)
		|| (XCorrLen > CGI_MAX_DCVT_LEN))
	{
		throw (CGI_INIT_ERROR);
	}

	// Create the down-conversion / resampling filter
	// and store it in filter native datatype format
	RESAMP_LPF_TAPS = ALLOCSTRUCT(CGI_LPF_LEN);
	ippsZero_32fc(RESAMP_LPF_TAPS, CGI_LPF_LEN);
	rFreq = (double)CGI_LPF_FREQ/(double)(input_samples_per_symbol * GSM_BIT_RATE);
	if ( GET_LPF_FIR((Ipp64f)rFreq, TempBuf, CGI_LPF_LEN, ippWinHamming, ippTrue) != ippStsNoErr )
	{
		throw(CGI_LPF_ERROR);
	}
	for ( i=0; i<CGI_LPF_LEN; i++ ) REALPART(RESAMP_LPF_TAPS[i]) = (DATATYPE)TempBuf[i];

	// Initialize the multi-rate FIR filter for multi-rate resampling.
	// Initialize and allocate the filter state variable.
	// This copies the filter coeffs into the state as well as inits the delay lines
	if ( ippsFIRMRInitAlloc_32fc(&ResampleFIRstate, RESAMP_LPF_TAPS, CGI_LPF_LEN,
		CGI_UPSAMPLE_RATE, 0, CGI_DOWNSAMPLE_RATE, 0, NULL) != ippStsNoErr )
	{
		throw(CGI_INIT_ERROR);
	}


	DcvtData = ALLOCSTRUCT(CGI_MAX_INPUT_LEN);
	dData = ALLOCSTRUCT(CGI_MAX_DCVT_LEN);
	XCorr = ALLOCSTRUCT(CGI_MAX_DCVT_LEN);
	XCorrMag = ALLOCTYPE(CGI_MAX_DCVT_LEN);


	// Get the normal training sequence templates from the DLL resource
	for (i=0; i<GSM_NUM_TS; i++ )
	{
		NORMAL_TS_04_[i] = psuTemplate->ts[i].data;
	}
	//bcch_correlator_ = new modulated_signal_correlator(
	//	psuTemplate->ts[0].data, psuTemplate->ts[0].length,
	//	dDataLen, CGI_UPSAMPLE_RATE, CGI_DOWNSAMPLE_RATE, rFreq, CGI_LPF_LEN);
//#ifdef _DEBUG
//	BcchFile = fopen("BcchData.txt", "wt");
//#endif
}


/***********************************************************************
* DECODE function
*
* Inputs:
*	Burst: Address of GSM data where the first CGI burst starts.
*	IF_Freq: IF freq; used to correct the Doppler and freq errors
*	BSIC: decoded BSIC; used to select the proper TS template
*	CGIInfo: Address of buffer which will contain the decoded CGI data
* Outputs:
*	<return>: Error code
*
* Ensure the CGI Decode package has been initialized properly.
* Then demodulate and de-interleave four BCCH bursts.
* Finally, perform convolutional and block decoding and return results.
/**********************************************************************/
CGIDecoderMsgType GsmCgiDecoder::DecodeCGI(const DATASTRUCT *Burst, int IF_Freq, int BSIC, CGIChannelInfoType *CGIInfo, GSM_BCCH_DATA_TYPE& BcchData)
{
	int i;
	const double PI = acos(-1.0);
	const int WiderFrameLength = ROUND(GSM_BITS_PER_FRAME * NETSTART_SAMPLES_PER_GSM_BIT);

	// Allocate space to hold one demodulated GSM burst
	float Demod[ROUND(GSM_BITS_PER_BURST * 4)];
	// and the entire CGI encoded bitstream (4 bursts)
	float CGIBits[456];

	int BCC = BSIC & 0x7;
	const double w_delta = (-2*PI*(double)IF_Freq)/NETSTART_SAMPLING_RATE_HZ;

	int decoderError = 0;
	char Decoded[CGI_NUM_CONV_BITS];
	CGIDecoderMsgType returnval = CGI_NO_ERROR;

	// take current burst and increase by one GSM frame ahead of input Sync burst location
	//TODO: don't want this hard-coded!
	const DATASTRUCT *CurrentBurst = Burst + WiderFrameLength;

	// For correlation, choose the TS that corresponds to the BCC
	CGI_TS_04_ = NORMAL_TS_04_[BCC];

	for ( i=0; i<4; i++ ) {
		if ( BCCHDemodulate(CurrentBurst, w_delta, Demod) ) return CGI_DEMOD_ERROR;
		DeInterleave(i, Demod, CGIBits);
		CurrentBurst += WiderFrameLength;
	}

	decoderError = conv_decoder_.Decode(CGIBits, Decoded);
	if ( decoderError < 0 ) return (CGI_CONV_DECODE_ERROR);
	if ( decoderError > CGI_MAX_CONV_ERR ) return (CGI_CONV_DECODE_ACCUM_ERR);

	decoderError = CGIBlockDecode(Decoded, CGIInfo);
	if ( decoderError != 0 ) return CGI_BLK_DECODE_PARITY;

	memset(CGIInfo,0,sizeof(*CGIInfo));

	//i = CGI_NUM_CONV_BITS;
	//j = 0;
	//while ( i > 0 ) {
	//	BurstData[j] <<= 1;
	//	BurstData[j] |= (unsigned int)Decoded[--i];
	//	if ( (i % 64) == 0 ) j++;
	//}

	unsigned int octet_idx = 0;
	unsigned int bit_idx = 0;
	// According to 3GPP TS 44.004, Sec 7.3.1,
	// the BCCH DL bits start at octet 1, bit 1.
	// However, according to TS 44.006, Sec 5.8,
	// the numbering scheme is that bit 8 is the MSB,
	// and increasing octets are in decreasing significance.
	// Thus to get the octets, we start at Decoded[7:0] as the MS Byte (octet 1),
	// and then Decoded[15:8] = octet 2, etc.
	while ( bit_idx < (unsigned int)CGI_NUM_DATA_BITS )
	{
		BcchData[octet_idx] >>= 1;
		BcchData[octet_idx] |= (unsigned __int8)(Decoded[bit_idx++] ? 0x80 : 0x00);
		if ( (bit_idx % 8) == 0 )
		{
//#ifdef _DEBUG
//			fprintf(BcchFile, "%02X", BcchData[octet_idx]);
//#endif
			octet_idx++;
		}
	}
//#ifdef _DEBUG
//	fprintf(BcchFile, "\n");
//#endif
//

	CGIInfo->CI = ((unsigned int)BcchData[3])<<8 | BcchData[4];
	CGIInfo->LAC = ((unsigned int)BcchData[8])<<8 | BcchData[9];

	CGIInfo->MCC_1 = BcchData[6] & 0x0F;
	CGIInfo->MCC_10 = (BcchData[5]>>4) & 0x0F;
	CGIInfo->MCC_100 = BcchData[5] & 0x0F;

	CGIInfo->MNC_1 = (BcchData[6]>>4) & 0x0F;
	CGIInfo->MNC_10 = (BcchData[7]>>4) & 0x0F;
	CGIInfo->MNC_100 = BcchData[7] & 0x0F;

	// If MNC_1 > 9 (i.e. is not a decimal digit),
	// then fall back to 2-digit MNC
	if ( CGIInfo->MNC_1 == 0x0F ) {
		CGIInfo->MNC_1 = CGIInfo->MNC_10;
		CGIInfo->MNC_10 = CGIInfo->MNC_100;
		CGIInfo->MNC_100 = 0;
	}

	return CGI_NO_ERROR;
}


/***********************************************************************
* BCCHDEMODULATE function
*
* Inputs:
*	Start: Address of GSM data where the CGI burst starts.
*	w_delta: used to correct the Doppler and freq errors
*	Demod: Address of buffer where the demod data will be stored
* Outputs:
*	<return>: Error code
*
* Calculate predicted TS location and correlation parameters.
* Down-convert to baseband and then resample to 4 samps/GSM bit.
* Correlate against the TS to find phase shift and location.
* Finally, demodulate and return the 148 bits.
/**********************************************************************/
int GsmCgiDecoder::BCCHDemodulate(const DATASTRUCT *CGIBurst, double w_delta, float *Demod)
{
	// Offset from actual start of burst at which the TS starts
	// For CGI bursts, this is 3 GSM start bits + 58 data bits
	const int TSOffset = (58+3) * samples_per_symbol_;

	const DATASTRUCT *Start = CGIBurst - BurstPadLen;
	DATASTRUCT *BurstData;
	DATATYPE Peak;

	unsigned int i, PeakLoc;
	double w, PhaseShift;


	// Downconvert to baseband
	// remember that the input data is real, so only 2 mults needed
	for( i = 0, w = 0.0; i < DataLen; i++, w += w_delta )
	{
		REALPART(DcvtData[i]) = REALPART(Start[i]) * (DATATYPE)cos(w)
			- IMAGPART(Start[i]) * (DATATYPE)sin(w);
		IMAGPART(DcvtData[i]) = REALPART(Start[i]) * (DATATYPE)sin(w)
			+ IMAGPART(Start[i]) * (DATATYPE)cos(w);
	}

	// Lowpass filter and resample the data to get 4 complex samples per bit
	if ( BurstResample(DcvtData, dData) != 0 ) return CGI_RESAMPLE_ERROR;

	// Normalize to 1 for proper operation of the convolutional decoder
	normalizeEach(dData, dDataLen);

	// Correlate against the TS template to find phase and location
	// We can reuse the Dcvt array since we don't need them anymore
	// and we know they are longer than the xcorr length
	CROSSCORR( CGI_TS_04_, Len_TS_04_,
		dData, dDataLen,
		XCorr, XCorrLen, TSOffset );

	// get the magnitudes
	MAG( XCorr, XCorrMag, XCorrLen );

	// Find the peak
	Peak = 0.0;
	PeakLoc = 0;
	for( i = 0; i < XCorrLen; i++ ) {
		if( XCorrMag[i] > Peak ) {
			Peak = XCorrMag[i];
			PeakLoc = i;
		}
	}

	PhaseShift = atan2( IMAGPART(XCorr[PeakLoc]), REALPART(XCorr[PeakLoc]) );
	BurstData = dData + PeakLoc;

	// Phase correction is done with the demod
	if ( DemodulateBurst148(BurstData, Demod, PhaseShift) ) return CGI_DEMOD_ERROR;

	if ( GsmDebugSettings.bCGI > 0 ) {
		//// save the normalized burst
		//fnwrite( BurstData, sizeof(DATASTRUCT), GSM_BITS_PER_BURST*CGI_RESAMP_PER_GSM_BIT, "CGIData.bin" );
		//// save the demodulated data
		//fnwrite( Demod, sizeof(DATATYPE), GSM_BITS_PER_BURST, "Demod.bin" );
	}

	return 0;
}


/***********************************************************************
* DEMODULATEBURST148 function
*
* Inputs:
*	BurstMod: Address of the start of the GSM data
*	PhaseShift: used to correct for the average phase shift as
*			determined by the TS correlation.
*	Demod: Address of buffer where the demod data will be stored
* Outputs:
*	<return>: Error code {0=OK, -1=input buffers invalid}
*
* Demodulate 148 GSM bits based on 4 samples/GSM bit.
* Use the input PhaseShift to account for phase noise.
/**********************************************************************/
int GsmCgiDecoder::DemodulateBurst148(const DATASTRUCT *BurstMod, float *Demod, double PhaseShift) const
{
	int BitPos = 0;
	const DATASTRUCT *BM = BurstMod;
	const float CosPS = (float)cos(PhaseShift);
	const float SinPS = (float)sin(PhaseShift);
	const int SampPerBit = ROUND( CGI_RESAMP_PER_GSM_BIT );

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


/***********************************************************************
* CGI_RESAMPLE function
*
* Inputs:
*	In: Pointer to sequence (normal BCCH burst) to be resampled
*	Out: Pointer to where results will be stored
*
* Outputs: returns error code (0=no error)
*
* Resamples from 50MHz to 4 samps/bit
/**********************************************************************/
int GsmCgiDecoder::BurstResample(DATASTRUCT *In, DATASTRUCT *Out)
{
	if ( (In==NULL) || (Out==NULL) ) return -1;

	if ( ippsFIR_32fc(In, Out, RESAMPLE_ITERATIONS, ResampleFIRstate) != ippStsNoErr )
	{
		return -1;
	}
	return 0;
}


/***********************************************************************
* DEINTERLEAVE function
*
* Inputs:
*	BurstNum: Specifies which one of the four BCCH bursts
*			will be deinterleaved
*	PhaseShift: used to correct for the average phase shift as
*			determined by the TS correlation.
*	Demod: Address of buffer where the demod data will be stored
* Outputs: NONE
*
* Deinterleaves a specified one of the four 148-bit BCCH CGI bursts.
***********************************************************************/
void GsmCgiDecoder::DeInterleave(int BurstNum, float *In, float *Out) const
{
	int i;

	const int NumTotalBits = CGI_NUM_CONV_BITS * 2;
	const int NumBitsBlock = NumTotalBits / 8;

#define GSM_NUM_TAIL_BITS 3
#define GSM_NORMTS_LEN_BITS 26

	int DeIntIdx = BurstNum * NumBitsBlock;

	const float *fTemp = In + GSM_NUM_TAIL_BITS;
	for ( i=0; i<NumBitsBlock; i++ ) {
		Out[DeIntIdx] = *fTemp++;
		if ( i % 2 ) DeIntIdx = (DeIntIdx + 292) % 456;
		else DeIntIdx = (DeIntIdx + 228) % 456;
	}

	// skip training sequence and stealing bits.
	// also note that the DeIntIdx increment has changed!!
	fTemp += GSM_NORMTS_LEN_BITS + 2;
	for ( i=0; i<NumBitsBlock; i++ ) {
		Out[DeIntIdx] = *fTemp++;
		if ( i % 2 ) DeIntIdx = (DeIntIdx + 228) % 456;
		else DeIntIdx = (DeIntIdx + 292) % 456;
	}
}


/***********************************************************************
* BLOCKDECODE function
*
* Inputs:
*	Encoded: Pointer to the GSM block encoded data
*	Decoded: Address where the decoded data will be stored.
* Outputs: Error Code
*
* GSM block decoding algorithm.
* Uses a binary "division" algorithm the GSM bit
* stream that produced the encoded data.  Decoding error is
* detected by the parity bit stream that results from division.
* Additioanlly, errors are detected if the resulting GSM data
* includes invalid values.
***********************************************************************/
int GsmCgiDecoder::CGIBlockDecode(const char * const Encoded, CGIChannelInfoType *CGIInfo) const
{

	static const char CGI_BLK_DIVIDER[] =
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1};

	unsigned __int64 BurstData[4] = {0,0,0,0};
	int NumParityErrs = 0;
	unsigned int ShiftCount, XorCount;
	const char *Divisor = CGI_BLK_DIVIDER;

	char Dividend[CGI_NUM_TOTAL_BLKDECODE_BITS];
	// Initialize Dividend = Encoded
	memcpy( Dividend, Encoded, CGI_NUM_TOTAL_BLKDECODE_BITS * sizeof(Dividend[0]) );

	for ( ShiftCount=0; ShiftCount<CGI_NUM_DATA_BITS; ShiftCount++ ) {
		if ( Dividend[ShiftCount] ) {
			for ( XorCount=0; XorCount<=CGI_NUM_PARITY_BITS; XorCount++ ) {
				// implement logical XOR
				if ( Divisor[XorCount] ) Dividend[ShiftCount+XorCount] = !Dividend[ShiftCount+XorCount];
			}
		}
	}

	for ( XorCount = 0; XorCount < CGI_NUM_PARITY_BITS; XorCount++ ) {
		if ( !Dividend[ShiftCount+XorCount] ) NumParityErrs++;
	}

	return NumParityErrs;
}


GsmCgiDecoder::~GsmCgiDecoder()
{
	ippsFree(DcvtData);
	ippsFree(dData);
	ippsFree(XCorr);
	ippsFree(XCorrMag);
	ippsFree(RESAMP_LPF_TAPS);
	ippsFIRFree_32fc(ResampleFIRstate);
//#ifdef _DEBUG
//	fclose(BcchFile);
//#endif
}
