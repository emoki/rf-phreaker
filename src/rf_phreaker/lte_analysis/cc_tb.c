#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

#include "CC_Tb.h"

#define MAXLOG 1e10  /* Define infinity */

static int parity_counter( int symbol, int length )
{
	int counter;
	int temp_parity = 0;

	for (counter=0;counter<length;counter++) {
		temp_parity = temp_parity^(symbol&1);
		symbol = symbol>>1;
	}

	return( temp_parity );
}


/* function that creates the transit and output vectors */
static int nsc_enc_bit(int* state_out_p, int input, int state_in, 
	int* g, int KK, int nn)
{
	/* declare variables */
	int state, i;
	int out = 0;	

	/* create a word made up of state and new input */
	state = (input<<(KK-1))^state_in;
	
	/* AND the word with the generators */
	for (i=0;i<nn;i++)
    {		
		/* update output symbol */
		out = (out<<1) + parity_counter( state&g[i], KK ); 		
    }
	
	/* shift the state to make the new state */
	state_out_p[0] = state>>1; 	
	return(out);
}


static float Gamma(float* rec_array, int symbol, int nn)				   
{
	float rm = 0;
	int i;
	int mask;
	
	mask = 1;
	for (i=0;i<nn;i++) {
		if (symbol&mask)
			rm += rec_array[nn-i-1];
		mask = mask<<1;
	} 
	
	return(rm);
} 


void nsc_transit(int* output_p, int* trans_p, int input, int* g,
	int KK,	int nn )										
{
	int nextstate[1];
	int state, states;
	states = (1<<(KK-1));  /* The number of states: 2^mm */

	/* Determine the output and next state for each possible starting state */
	for(state=0;state<states;state++) {
		output_p[state]  = nsc_enc_bit( nextstate, input, state, g, KK, nn ); 
		trans_p[state]  = nextstate[0];
	}
	return;
}


void viterbiTb(int* output_u_int, int* out0, int* state0, int* out1, int* state1,
	Ipp32f* input_c, int KK, int nn, int LL, int depth)
{
	int i, t, state, mm, states, max_state;
	int number_symbols, starting_bit;
	float metric;
	float *prev_section, *next_section;
	int *prev_bit;
	int *prev_state;
	float *metric_c;	/* Set of all possible branch metrics */
	float *rec_array;   /* Received values for one trellis section */
	float max_val;

	
	/* some derived constants */
	mm = KK-1;
	states = 1 << mm;			/* 2^mm */
	number_symbols = 1 << nn;	    /* 2^nn */
	
	/* dynamically allocate memory */ 
	prev_section = (float*)allocate( states, sizeof(float) );
	next_section = (float*)allocate( states, sizeof(float) );
	prev_bit = (int*)allocate( states*(LL+depth), sizeof(int) );
	prev_state = (int*)allocate( states*(LL+depth), sizeof(int) );
	rec_array = (float*)allocate( nn, sizeof(float) );
	metric_c = (float*)allocate( number_symbols, sizeof(float) );
	
	/* initialize trellis */
	for (state=0;state<states;state++) {
		prev_section[state] = 0; /* equally likely starting state */
		next_section[state] = -MAXLOG;
	}
	
	/* go through trellis */
	for (t=-depth;t<LL+depth;t++) {
		/* determine the corresponding data bits */
		starting_bit = nn*(t%LL);
		if (starting_bit < 0 )
			starting_bit = nn*LL + starting_bit;
		
		/* printf( "start at %d\n", starting_bit ); */
		for (i=0;i<nn;i++) {
			rec_array[i] = input_c[starting_bit+i];
			/* printf( "%1f\n", rec_array[i] ); */
		}

		/* precompute all possible branch metrics */
		for (i=0;i<number_symbols;i++)
			metric_c[i] = Gamma( rec_array, i, nn ); 
		
		/* step through all states */
		for (state=0;state<states;state++) {
			
			/* hypothesis: info bit is a zero */
			metric = prev_section[state] + metric_c[ out0[ state ] ];
			
			/* store new metric if more than metric in storage */
			if ( metric > next_section[state0[state]] ) {
				next_section[state0[state]] = metric;
				if (t>=0) {				
					prev_state[t*states+state0[state]] = state;
					prev_bit[t*states+state0[state]] = 0;
				}
			}
			
			/* hypothesis: info bit is a one */
			metric = prev_section[state] + metric_c[ out1[ state ] ];
			
			/* store new metric if more than metric in storage */
			if ( metric > next_section[state1[state]] ) {
				next_section[state1[state]] = metric;
				if (t>=0) {				
					prev_state[t*states+state1[state]] = state;				
					prev_bit[t*states+state1[state]] = 1;
				}
			}
		}
		
		/* normalize */
		max_val = 0;
		max_state = 0;
		for (state=0;state<states;state++) {
			if (next_section[state]>max_val){
				max_val = next_section[state];
				max_state = state;
			}
		}
		for (state=0;state<states;state++) {
			prev_section[state] = next_section[state] - max_val;
			next_section[state] = -MAXLOG;
		}
	}
	
	/* trace-back operation */
	state = max_state;

	/* tail, no need to output */
	for (t=LL+depth-1; t>=LL; t--) {
		state = prev_state[t*states+state];
	}

	for (t=LL-1; t>=0; t--) {		
		output_u_int[t] = prev_bit[t*states+state];
		state = prev_state[t*states+state];
	}
	
	/* free the dynamically allocated memory */
	free(prev_section);
	free(next_section);
	free(prev_bit);
	free(prev_state);
	free(rec_array);
	free(metric_c); 
	
}

static void itob(int *binvec_p, int symbol, int length)
{
	int counter;

	/* Go through each bit in the vector */
	for (counter=0;counter<length;counter++) {
		binvec_p[length-counter-1] = (symbol&1);
		symbol = symbol>>1;
	}

	return;
}



void cc_decoding( unsigned int *decBits, Ipp32f* inLLR, unsigned int codeLen, 
	unsigned int *genPoly, unsigned int row, unsigned int col)
{
	int *decBits_i; 
	int cc, mm, outBits, maxStates, convergeDepth, infoLen; 
	int *out0, *out1, *states0, *states1, tail;
	int ii, jj;
	int *genPoly2;

	outBits = row;
	cc = col;
	mm = cc - 1;	
	maxStates = 1 << mm;

	genPoly2 = (int*)allocate(outBits, sizeof(int));
	
	for (ii=0;ii<outBits;ii++) 
	{
		for(jj=0;jj<cc;jj++) 
		{
			if (genPoly[ii*cc+jj]!= 0) 
			{
				genPoly2[ii] = genPoly2[ii] + (1<<(cc-jj-1)); 
			}
		}
	}

		
	infoLen = codeLen/outBits;

	decBits_i = (int *)allocate(infoLen, sizeof(int));

	convergeDepth = 6*cc; //can be other values

	out0 = (int*)allocate( maxStates, sizeof(int) );
	out1 = (int*)allocate( maxStates, sizeof(int) );
	states0 = (int*)allocate( maxStates, sizeof(int) );
	states1 = (int*)allocate( maxStates, sizeof(int) );

	nsc_transit( out0, states0, 0, genPoly2, cc, outBits);
	nsc_transit( out1, states1, 1, genPoly2, cc, outBits);

	viterbiTb(decBits_i, out0, states0, out1, states1,
		inLLR, cc, outBits, infoLen, convergeDepth); 

	for (ii=0;ii<infoLen;ii++) 
		decBits[ii] = decBits_i[ii];

	
	free(out0);
	free(out1);
	free(states0);
	free(states1);
	free(decBits_i);
	free(genPoly2);
	
}


