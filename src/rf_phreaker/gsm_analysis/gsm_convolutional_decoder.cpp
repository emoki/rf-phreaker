#include "rf_phreaker/gsm_analysis/gsm_convolutional_decoder.h"
#include <cstdlib>
#include <cmath>

const unsigned int gsm_convolutional_decoder::num_states_ = CONVDEC_NUM_STATES;

const gsm_convolutional_decoder::ConvDecStateType gsm_convolutional_decoder::STATE_TABLE_[CONVDEC_NUM_STATES*2] = {
	{0, 0, 0, 1, 1},	{0, 0, 8, -1, -1},
	{1, 1, 0, -1, -1},	{1, 1, 8, 1, 1},
	{2, 0, 1, 1, -1},	{2, 0, 9, -1, 1},
	{3, 1, 1, -1, 1},	{3, 1, 9, 1, -1},
	{4, 0, 2, 1, 1},	{4, 0, 10, -1, -1},
	{5, 1, 2, -1, -1},	{5, 1, 10, 1, 1},
	{6, 0, 3, 1, -1},	{6, 0, 11, -1, 1},
	{7, 1, 3, -1, 1},	{7, 1, 11, 1, -1},
	{8, 0, 4, -1, -1},	{8, 0, 12, 1, 1},
	{9, 1, 4, 1, 1},	{9, 1, 12, -1, -1},
	{10, 0, 5, -1, 1},	{10, 0, 13, 1, -1},
	{11, 1, 5, 1, -1},	{11, 1, 13, -1, 1},
	{12, 0, 6, -1, -1},	{12, 0, 14, 1, 1},
	{13, 1, 6, 1, 1},	{13, 1, 14, -1, -1},
	{14, 0, 7, -1, 1},	{14, 0, 15, 1, -1},
	{15, 1, 7, 1, -1},	{15, 1, 15, -1, 1}
};


gsm_convolutional_decoder::gsm_convolutional_decoder(unsigned int num_bit_periods) :
num_bit_periods_(num_bit_periods),
num_columns_(num_bit_periods + 1),
trellis_(NULL),
traceback_(NULL)
{
	trellis_ = new float[num_states_ * num_columns_];
	traceback_ = new int[num_columns_];
}

gsm_convolutional_decoder::~gsm_convolutional_decoder()
{
	delete [] trellis_;
	delete [] traceback_;
}


int gsm_convolutional_decoder::Decode(const float *Encoded, ConvDecodedType *Decoded)
{
// The encoded input should be interleaved
// so that the "low" stream is at positions [0,2,4,...2n]
// and the "high" stream is at positions [1,3,5,...2n+1].
// The decoded bit stream is half the length of the encoded, i.e. n records

	int returnval = CONVDECODE_NO_ERROR;

	int BitPeriod, StateIndex, StateNum;
	float DataLow, DataHi;

	int PrevState, NextState;
	int PrevStateLow, PrevStateHi;
	float DistanceLow, DistanceHi;
	float AccumulatedDistanceLow, AccumulatedDistanceHi;

	const float *Conv = Encoded;
	float (*Trellis)[CONVDEC_NUM_STATES] =
		reinterpret_cast<float(*)[CONVDEC_NUM_STATES]>(trellis_);

	int *TraceBack = traceback_;

	unsigned int i, j;

	// Set up the return value
	*Decoded = 0;

	// Init the trellis
	for ( i=0; i < num_states_; i++ ) {
		for ( j=0; j < num_columns_; j++ ) {
			Trellis[i][j] = 99.f;
		}
	}
	Trellis[0][0] = 0;

	// Populate the trellis
	for ( BitPeriod=0; BitPeriod < (int)num_bit_periods_; BitPeriod++)
	{
		DataLow = *Conv++;
		DataHi = *Conv++;

		// Loop through all possible state transitions for the current BitPeriod
		for (StateNum=0; StateNum<num_states_; StateNum++)
		{
			StateIndex = StateNum << 1;

			PrevStateLow =  STATE_TABLE_[StateIndex].PrevState;
			PrevStateHi = PrevStateLow + 8;

			DistanceLow = (float)( fabs(DataLow - STATE_TABLE_[StateIndex].Out0)
				+ fabs(DataHi - STATE_TABLE_[StateIndex].Out1) );
			DistanceHi = (float)( fabs(DataLow - STATE_TABLE_[StateIndex+1].Out0)
				+ fabs(DataHi - STATE_TABLE_[StateIndex+1].Out1) );

			AccumulatedDistanceLow = Trellis[BitPeriod][PrevStateLow];
			AccumulatedDistanceHi = Trellis[BitPeriod][PrevStateHi];

			Trellis[BitPeriod+1][StateNum] = __min(DistanceLow + AccumulatedDistanceLow,
				DistanceHi + AccumulatedDistanceHi);
		}
	}
	//if ( GsmDebugSettings.bBSIC > 0 ) {
	//	// save the trellis
	//	//fnwrite( (void *)Trellis, sizeof(Trellis[0][0]), sizeof(Trellis), "Trellis.bin" );
	//}

	// The trellis should have ended with State0.
	TraceBack[num_bit_periods_] = 0;
	DistanceLow = Trellis[num_bit_periods_][0];
	// Verify State0 is the minimum, or else set the error flag
	for (StateNum=1; StateNum<num_states_; StateNum++) {
		if ( Trellis[num_bit_periods_][StateNum] < DistanceLow ) {
			// This condition really shouldn't happen!
			// Start with State0 anyway, but return info msg
			returnval |= CONVDECODE_STATE0;
		}
	}

	// Do the traceback
	for ( BitPeriod=(int)num_bit_periods_-1; BitPeriod>=0; BitPeriod--)
	{
		*Decoded <<= 1;

		// determine the two possible previous states to the state at timeperiod
		PrevStateLow = STATE_TABLE_[TraceBack[BitPeriod+1]<<1].PrevState;
		PrevStateHi = PrevStateLow + 8;

		AccumulatedDistanceLow = Trellis[BitPeriod][PrevStateLow];
		AccumulatedDistanceHi = Trellis[BitPeriod][PrevStateHi];

		if ( AccumulatedDistanceLow < AccumulatedDistanceHi )
			TraceBack[BitPeriod] = PrevStateLow;
		else
			TraceBack[BitPeriod] = PrevStateHi;

		PrevState  = TraceBack[BitPeriod];
		NextState  = TraceBack[BitPeriod+1];
    
		// uses the StateTable to determine what bit must have entered the encoder
		// to change state from previous state to next state
		*Decoded |= STATE_TABLE_[(NextState<<1)+(PrevState>>3)].Bit;
	}
	return (ConvDecoderMsgType)returnval;
}



int gsm_convolutional_decoder::Decode(const float *Encoded, char *Decoded)
{
// The encoded input should be interleaved
// so that the "low" stream is at positions [0,2,4,...2n]
// and the "high" stream is at positions [1,3,5,...2n+1].
// The decoded bit stream is half the length of the encoded, i.e. n records

	int BitPeriod, StateIndex, StateNum;
	float DataLow, DataHi;

	int PrevState, NextState;
	int PrevStateLow, PrevStateHi;
	float DistanceLow, DistanceHi;
	float AccumulatedDistanceLow, AccumulatedDistanceHi;

	const float *Conv = Encoded;
	float (*Trellis)[CONVDEC_NUM_STATES] =
		reinterpret_cast<float(*)[CONVDEC_NUM_STATES]>(trellis_);

	int returnval = CONVDECODE_NO_ERROR;

	int *TraceBack = traceback_;

	unsigned int i, j;

	// Set up the return value
	*Decoded = 0;

	// Init the trellis
	for ( i=0; i < num_states_; i++ ) {
		for ( j=0; j < num_columns_; j++ ) {
			Trellis[i][j] = 99.f;
		}
	}
	Trellis[0][0] = 0;

	// Populate the trellis
	for ( BitPeriod=0; BitPeriod < (int)num_bit_periods_; BitPeriod++)
	{
		DataLow = *Conv++;
		DataHi = *Conv++;

		// Loop through all possible state transitions for the current BitPeriod
		for (StateNum=0; StateNum<num_states_; StateNum++)
		{
			StateIndex = StateNum << 1;

			PrevStateLow =  STATE_TABLE_[StateIndex].PrevState;
			PrevStateHi = PrevStateLow + 8;

			DistanceLow = (float)( fabs(DataLow - STATE_TABLE_[StateIndex].Out0)
				+ fabs(DataHi - STATE_TABLE_[StateIndex].Out1) );
			DistanceHi = (float)( fabs(DataLow - STATE_TABLE_[StateIndex+1].Out0)
				+ fabs(DataHi - STATE_TABLE_[StateIndex+1].Out1) );

			AccumulatedDistanceLow = Trellis[BitPeriod][PrevStateLow];
			AccumulatedDistanceHi = Trellis[BitPeriod][PrevStateHi];

			Trellis[BitPeriod+1][StateNum] = __min(DistanceLow + AccumulatedDistanceLow,
				DistanceHi + AccumulatedDistanceHi);
		}
	}

	// The trellis should have ended with State0.
	TraceBack[num_bit_periods_] = 0;
	DistanceLow = Trellis[num_bit_periods_][0];
	returnval = (int)(DistanceLow + 0.5f);
	// Verify State0 is the minimum, or else set the error flag
	for (StateNum=1; StateNum<num_states_; StateNum++) {
		if ( Trellis[num_bit_periods_][StateNum] < DistanceLow ) {
			// This condition really shouldn't happen!
			// Start with State0 anyway, but return info msg
			returnval |= CONVDECODE_STATE0;
		}
	}

	// Do the traceback
	for ( BitPeriod=(int)num_bit_periods_-1; BitPeriod>=0; BitPeriod--)
	{
		// determine the two possible previous states to the state at timeperiod
		PrevStateLow = STATE_TABLE_[TraceBack[BitPeriod+1]<<1].PrevState;
		PrevStateHi = PrevStateLow + 8;

		AccumulatedDistanceLow = Trellis[BitPeriod][PrevStateLow];
		AccumulatedDistanceHi = Trellis[BitPeriod][PrevStateHi];

		if ( AccumulatedDistanceLow < AccumulatedDistanceHi )
			TraceBack[BitPeriod] = PrevStateLow;
		else
			TraceBack[BitPeriod] = PrevStateHi;

		PrevState  = TraceBack[BitPeriod];
		NextState  = TraceBack[BitPeriod+1];
    
		// uses the StateTable to determine what bit must have entered the encoder
		// to change state from previous state to next state
		Decoded[BitPeriod] = STATE_TABLE_[(NextState<<1)+(PrevState>>3)].Bit;
	}
	return returnval;
}
