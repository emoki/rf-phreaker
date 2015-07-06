#pragma once


#define CONVDEC_NUM_STATES			16

typedef enum {
	OUT_OF_MEMORY = -256,
	INIT_ERROR,
	UNKNOWN_ERROR = -1,
	CONVDECODE_NO_ERROR = 0,
	CONVDECODE_STATE0 = 0x1,
	CONVDECODE_ACCUM_ERR = 0x2,
	BLK_DECODE_MSB_NONZERO = 0x4,
	BLK_DECODE_T2 = 0x8,
	BLK_DECODE_T3 = 0x10,
	BLK_DECODE_PARITY = 0x12,
} ConvDecoderMsgType;

typedef unsigned __int64 ConvDecodedType;

// Convolutional Decoder state table

class gsm_convolutional_decoder {
public:
	gsm_convolutional_decoder(unsigned int num_bit_periods);
	~gsm_convolutional_decoder();
	int Decode(const float *Encoded, ConvDecodedType *Decoded);
	int Decode(const float *Encoded, char *Decoded);
protected:

	typedef struct {
		int NextState;
		int Bit;
		int PrevState;
		float Out0;
		float Out1;
	} ConvDecStateType;

	static const unsigned int num_states_;
	static const ConvDecStateType STATE_TABLE_[CONVDEC_NUM_STATES*2];
	unsigned int num_bit_periods_;
	unsigned int num_columns_;
	float *trellis_;
	int *traceback_;
};

// Decoder function declarations
//BSICDecoderMsgType BlockDecode(const ConvDecodedType Encoded, BSICChannelInfoType *SyncInfo);
