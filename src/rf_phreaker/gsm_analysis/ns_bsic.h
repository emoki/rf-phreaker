#pragma once

#include "rf_phreaker/gsm_analysis/modulated_signal_correlator.h"
#include "rf_phreaker/gsm_analysis/gsm_convolutional_decoder.h"

// TODO:: this is defined here because Sync needs it to calculate
// if an adequate number of data samples is available for decoding.
// However, we should eventually move that calculation into BSIC.CPP
#define BSIC_BURST_NUM_BITS_PAD		2


typedef enum {
	BSIC_OUT_OF_MEMORY = -256,
	BSIC_INIT_ERROR,
	BSIC_LPF_ERROR,
	BSIC_RESAMPLE_ERROR,
	BSIC_DEMOD_ERROR,
	BSIC_SCORR_ERROR,
	BSIC_NSP_ERROR = -2,
	BSIC_OTHER_ERROR = -1,
	BSIC_NO_ERROR = 0,
	BSIC_BLK_DECODE_MSB_NONZERO = 0x2,
	BSIC_BLK_DECODE_T2 = 0x4,
	BSIC_BLK_DECODE_T3 = 0x8,
	BSIC_BLK_DECODE_PARITY = 0x10,
	BSIC_OTHER_MSG = 0x0800
} BSICDecoderMsgType;

typedef struct {
	int : 0; // guarantees storage on an integer boundary
	unsigned int BCC : 4;
	unsigned int NCC : 4;
	unsigned int T1 : 11;
	unsigned int : 1;
	unsigned int T2 : 5;
	unsigned int : 3;
	unsigned int T3 : 3;
	unsigned int : 1;
} BSICChannelInfoType;


class GsmBsicDecoder
{
public:
	GsmBsicDecoder();
	~GsmBsicDecoder();
	BSICDecoderMsgType DecodeBSIC(const DATASTRUCT *data, int IF_Freq_Hz, BSICChannelInfoType *SyncInfo,
		modulated_signal_correlator& sync_correlator);
protected:
	int BurstResample(DATASTRUCT *In, DATASTRUCT *Out);
	int DemodulateBurst148(const DATASTRUCT* BurstMod, float* Demod, double PhaseShift) const;
	BSICDecoderMsgType BlockDecode(const ConvDecodedType Encoded, BSICChannelInfoType *SyncInfo) const;

	const unsigned int samples_per_symbol_;
	const unsigned int xcorr_len_;
	gsm_convolutional_decoder conv_decoder_;

	DATATYPE *XCorrMag;
	float SyncBits[GSM_BITS_PER_BURST];
};

unsigned int GetTDMAFrameNumber(const BSICChannelInfoType SyncInfo);
