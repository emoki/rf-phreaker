/*******************************************************************************
  ts44.018_support.h - (c) by Dafocus
*******************************************************************************/
#ifndef __TS44018_SUPPORT_H
#define __TS44018_SUPPORT_H

#ifdef __cplusplus
	extern "C" {
#endif

/*------------------------------------------------------------------------------
	TS 44.018 Table 9.1.54.1a - p-function
------------------------------------------------------------------------------*/
extern unsigned DECODE_FDD_CELL_INFORMATION_p (unsigned n);

/*------------------------------------------------------------------------------
	TS 44.018 Table 9.1.54.1b - q-function
------------------------------------------------------------------------------*/
extern unsigned DECODE_TDD_CELL_INFORMATION_q (unsigned n);

/*------------------------------------------------------------------------------
	Decodes 44.018 Annex J compression
------------------------------------------------------------------------------*/
extern unsigned DECODE_AnnexJ (const unsigned* inputValues, unsigned noOfInputItems, unsigned* outputValues, unsigned maxNoOfOutputValues, unsigned originalRange, unsigned offset);


#ifdef __cplusplus
	}
#endif

#endif

