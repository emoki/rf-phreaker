/*
*********************************************************************************************************
* Copyright (c)
* File : lte_turbo_code.cpp
* Brief : LTE Turbo Code
* Author:Rajesh S. Bagul
* History :
*********************************************************************************************************
*/
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <cmath>

#include "lte_common.h"
#include "lte_analysis.h"
#include "lte_turbo_code_init_data.h"
#include "lte_turbo_code.h"

namespace rf_phreaker {

/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lte_turbocode_internal_interleaver_param(unsigned int k_block_size, unsigned int &f1, unsigned int &f2) {
	unsigned int ii;

	for(ii = 0; ii < 188; ii++) {
		if(lte_turbo_code_interleaver_k_f1_f2[ii].k_i == k_block_size) {
			f1 = lte_turbo_code_interleaver_k_f1_f2[ii].f1;
			f2 = lte_turbo_code_interleaver_k_f1_f2[ii].f2;
		}
	}

	return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/

int lte_turbo_bcjr_maxlogmap(Ipp32f* received_data, Ipp32f* apriori_probability, Ipp32f* llr, unsigned int block_size) {
	Ipp32f alpha[LTE_TURBO_CODE_NUM_STATES], alpha2[LTE_TURBO_CODE_NUM_STATES], alpha_temp[LTE_TURBO_CODE_NUM_STATES]; //forward state metric
	Ipp32f beta[6144][LTE_TURBO_CODE_NUM_STATES], beta_temp[LTE_TURBO_CODE_NUM_STATES]; //reverse (backward) state metric
	Ipp32f branch_metric[LTE_TURBO_CODE_NUM_STATES]; //branch metric
	Ipp32f numerator_conditional_llr[LTE_TURBO_CODE_NUM_STATES], denominator_conditional_llr[LTE_TURBO_CODE_NUM_STATES], llr_temp, max_numerator_llr, max_denominator_llr;

	//Initializing forward state metric(aplha) and reverse(backward) state metric (beta)
	for(unsigned int state_num = 0; state_num < LTE_TURBO_CODE_NUM_STATES; state_num++) {

		if(state_num != 0)
			alpha[state_num] = -1 * LTE_TURBO_CODE_INFINITY;
		else
			alpha[state_num] = 0;

		//for(unsigned int ii=0;ii<block_size;ii++)
		{
			if(state_num != 0)
				//beta[ii][state_num] = -1 * LTE_TURBO_CODE_INFINITY;
				beta[block_size - 1][state_num] = -1 * LTE_TURBO_CODE_INFINITY;
			else
				//beta[ii][state_num] = 0;
				beta[block_size - 1][state_num] = 0;
		}
	}

	//Calculating reverse(backward) state metric (beta)
	for(int kk = block_size - 2; kk >= 0; kk--) {
		for(unsigned int state_index = 0; state_index < LTE_TURBO_CODE_NUM_STATES; state_index++) {
			beta[kk][state_index] = -1 * LTE_TURBO_CODE_INFINITY;

			for(unsigned int ll = 0; ll < LTE_TURBO_CODE_NUM_STATES; ++ll) {
				branch_metric[ll] = -1 * LTE_TURBO_CODE_INFINITY; //Initiaslise the branch metric for all the states per time interval to minus infinity
				beta_temp[ll] = -1 * LTE_TURBO_CODE_INFINITY;
			}

			//Calculating Manhattan distance between received data and trellis ouput data for data input == 0
			branch_metric[next_state[state_index][0]] =
				received_data[2 * (kk + 1)] * next_state_output[state_index][0] +
				received_data[2 * (kk + 1) + 1] * next_state_output[state_index][1] -
				apriori_probability[kk + 1] / 2;

			//Calculating Manhattan distance between received data and trellis ouput data for data input == 1
			branch_metric[next_state[state_index][1]] =
				received_data[2 * (kk + 1)] * next_state_output[state_index][2] +
				received_data[2 * (kk + 1) + 1] * next_state_output[state_index][3] +
				apriori_probability[kk + 1] / 2;

			for(unsigned int ll = 0; ll < LTE_TURBO_CODE_NUM_STATES; ++ll) {
				beta_temp[ll] = branch_metric[ll] + beta[kk + 1][ll];
				if(beta_temp[ll] > beta[kk][state_index]) //Calculating MAX beta
					beta[kk][state_index] = beta_temp[ll];
			}


		}//state_index loop
	}//kk loop


	//Calculating forward state metric(alpha)
	for(unsigned int kk = 0; kk < block_size; kk++) {
		for(unsigned int state_index = 0; state_index < LTE_TURBO_CODE_NUM_STATES; state_index++) {

			for(unsigned int ll = 0; ll < LTE_TURBO_CODE_NUM_STATES; ++ll) {
				branch_metric[ll] = -1 * LTE_TURBO_CODE_INFINITY; //Initiaslise the branch metric for all the states per time interval to minus infinity
				alpha_temp[ll] = -1 * LTE_TURBO_CODE_INFINITY;
			}

			//Calculating Manhattan distance between received data and trellis ouput data for data input == 0
			branch_metric[last_state[state_index][0]] =
				received_data[2 * kk] * last_state_output[state_index][0] +
				received_data[2 * kk + 1] * last_state_output[state_index][1] -
				apriori_probability[kk] / 2;

			//Calculating Manhattan distance between received data and trellis ouput data for data input == 1
			branch_metric[last_state[state_index][1]] =
				received_data[2 * kk] * last_state_output[state_index][2] +
				received_data[2 * kk + 1] * last_state_output[state_index][3] +
				apriori_probability[kk] / 2;



			numerator_conditional_llr[state_index] = alpha[last_state[state_index][1]] +
				branch_metric[last_state[state_index][1]] +
				beta[kk][state_index];

			denominator_conditional_llr[state_index] = alpha[last_state[state_index][0]] +
				branch_metric[last_state[state_index][0]] +
				beta[kk][state_index];

			alpha2[state_index] = -1 * LTE_TURBO_CODE_INFINITY;

			for(unsigned int ll = 0; ll < LTE_TURBO_CODE_NUM_STATES; ++ll) {
				alpha_temp[ll] = branch_metric[ll] + alpha[ll];
				if(alpha_temp[ll] > alpha2[state_index]) //Calculating MAX beta
					alpha2[state_index] = alpha_temp[ll];
			}

		}//state_index loop

		llr[kk] = -1 * LTE_TURBO_CODE_INFINITY;
		max_numerator_llr = max_denominator_llr = -1 * LTE_TURBO_CODE_INFINITY;

		for(unsigned int ll = 0; ll < LTE_TURBO_CODE_NUM_STATES; ++ll) {
			alpha[ll] = alpha2[ll];

			if(numerator_conditional_llr[ll] > max_numerator_llr)
				max_numerator_llr = numerator_conditional_llr[ll];

			if(denominator_conditional_llr[ll] > max_denominator_llr)
				max_denominator_llr = denominator_conditional_llr[ll];

		}

		llr[kk] = max_numerator_llr - max_denominator_llr;

	}//kk loop

	return LTE_SUCCESS;
}

/*
*********************************************************************************************************
* Function:
* Description:
* Arguments:
* Return Value:
**********************************************************************************************************
*/
int lte_turbo_code_decoder(Ipp32f* received_data, unsigned int *turbo_decoded_bits, unsigned int num_bits, unsigned int num_turbo_iterations) {
	unsigned int ii, f1, f2, block_size;
	unsigned int interleaver_indices[6144];
	Ipp32f apriori_probability[6144], extrinsic[6144], llr[6144], data_received_1[6144], data_received_2[6144], weight = 0.75;

	block_size = num_bits + (LTE_TURBO_CODE_CONSTRAINT_LENGHT - 1);
	lte_turbocode_internal_interleaver_param(num_bits, f1, f2);

	for(ii = 0; ii < num_bits; ii++) {
		interleaver_indices[ii] = (f1*ii + f2*ii*ii) % (num_bits);
	}

	for(ii = 0; ii < num_bits; ii++) {
		data_received_1[2 * ii] = received_data[ii * 3] / 2; //Systematic bits
		data_received_1[2 * ii + 1] = received_data[ii * 3 + 1] / 2;

		data_received_2[2 * ii] = received_data[interleaver_indices[ii] * 3] / 2;//Interleaved Systematic bits
		data_received_2[2 * ii + 1] = received_data[ii * 3 + 2] / 2;
	}

	//Trellis Termination
	for(ii = 0; ii < 2 * (LTE_TURBO_CODE_CONSTRAINT_LENGHT - 1); ii++) {
		data_received_1[2 * num_bits + ii] = received_data[3 * num_bits + ii] / 2;
		data_received_2[2 * num_bits + ii] = received_data[3 * num_bits + 2 * (LTE_TURBO_CODE_CONSTRAINT_LENGHT - 1) + ii] / 2;
	}

	for(ii = 0; ii < block_size; ii++) {
		apriori_probability[ii] = extrinsic[ii] = 0;
	}

	for(unsigned int iteration = 0; iteration < num_turbo_iterations; iteration++) {
		//First Decoder
		for(unsigned int kk = 0; kk < num_bits; kk++)//Deinterleaving
		{ apriori_probability[interleaver_indices[kk]] = extrinsic[kk]; }

		lte_turbo_bcjr_maxlogmap(data_received_1, apriori_probability, llr, block_size);

		for(unsigned int ll = 0; ll < block_size; ll++) {
			extrinsic[ll] = weight*(llr[ll] - (2 * data_received_1[2 * ll]) - apriori_probability[ll]);
		}

		//Second Decoder
		for(unsigned int kk = 0; kk < num_bits; kk++)//Interleaving
		{ apriori_probability[kk] = extrinsic[interleaver_indices[kk]]; }

		lte_turbo_bcjr_maxlogmap(data_received_2, apriori_probability, llr, block_size);

		for(unsigned int ll = 0; ll < block_size; ll++) {
			extrinsic[ll] = weight*(llr[ll] - (2 * data_received_2[2 * ll]) - apriori_probability[ll]);
		}

	}

	for(unsigned int mm = 0; mm < num_bits; mm++) {
		if(llr[mm] > 0)
			turbo_decoded_bits[interleaver_indices[mm]] = 1;
		else
			turbo_decoded_bits[interleaver_indices[mm]] = 0;

	}

	return LTE_SUCCESS;
}

}