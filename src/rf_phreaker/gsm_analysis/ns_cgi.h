#pragma once

#include "rf_phreaker/gsm_analysis/modulated_signal_correlator.h"
#include "rf_phreaker/gsm_analysis/gsm_convolutional_decoder.h"

typedef enum {
	CGI_OUT_OF_MEMORY = -256,
	CGI_INIT_ERROR,
	CGI_LPF_ERROR,
	CGI_RESAMPLE_ERROR,
	CGI_DEMOD_ERROR,
	CGI_XCORR_ERROR,
    CGI_CONV_DECODE_ERROR = -4,
	CGI_NSP_ERROR = -2,
	CGI_OTHER_ERROR = -1,
	CGI_NO_ERROR = 0,
    CGI_BLK_DECODE_MSB_NONZERO = 0x4,
    CGI_CONV_DECODE_ACCUM_ERR = 0x10,
    CGI_BLK_DECODE_PARITY = 0x12,
    CGI_OTHER_MSG = 0x0800
} CGIDecoderMsgType;

typedef struct {
	int : 0; // guarantees storage on an integer boundary
	unsigned int CI : 16;
	unsigned int MCC_100 : 4;
	unsigned int MCC_10 : 4;
	unsigned int MCC_1 : 4;
	unsigned int MNC_100 : 4;
	unsigned int MNC_10 : 4;
	unsigned int MNC_1 : 4;
	unsigned int LAC : 16;
} CGIChannelInfoType;


class GsmCgiDecoder
{
public:
	GsmCgiDecoder(const TemplateStruct *psuTemplate);
	~GsmCgiDecoder();
	CGIDecoderMsgType DecodeCGI(const DATASTRUCT *Burst, int IF_Freq, int BSIC, CGIChannelInfoType *CGIInfo, GSM_BCCH_DATA_TYPE& BcchData);
protected:
	int BurstResample(DATASTRUCT *In, DATASTRUCT *Out);
	int DemodulateBurst148(const DATASTRUCT* BurstMod, float* Demod, double PhaseShift) const;
	int BCCHDemodulate(const DATASTRUCT *Start, double w_delta, float *Demod);
	void DeInterleave(int BurstNum, float *In, float *Out) const;
//	int CGIBlockDecode(const ConvDecodedType *const Encoded, CGIChannelInfoType *CGIInfo) const;
	int CGIBlockDecode(const char *const Encoded, CGIChannelInfoType *CGIInfo) const;

	const unsigned int samples_per_symbol_;
	const unsigned int xcorr_len_;
	gsm_convolutional_decoder conv_decoder_;
	IppsFIRState_32fc* ResampleFIRstate;
	unsigned int DataLen;
	unsigned int dDataLen;
	unsigned int RESAMPLE_ITERATIONS;
	unsigned int BurstPadLen;
	unsigned int XCorrLen;

	DATASTRUCT *DcvtData;
	DATASTRUCT *dData;
	DATASTRUCT *XCorr;
	DATATYPE *XCorrMag;
	DATASTRUCT *RESAMP_LPF_TAPS;

	modulated_signal_correlator *bcch_correlator_;
	DATASTRUCT const *NORMAL_TS_04_[GSM_NUM_TS];
	const unsigned int Len_TS_04_;
	// used to point to the correct training seq template
	// based on the BCC that is passed into the Decode function.
	const DATASTRUCT *CGI_TS_04_;
};
