/*******************************************************************************
  ts44.018_support.c - (c) by Dafocus
*******************************************************************************/
#include "ed_user.h"

/*------------------------------------------------------------------------------
	TS 44.018 Table 9.1.54.1a - p-function
------------------------------------------------------------------------------*/
unsigned DECODE_FDD_CELL_INFORMATION_p (unsigned n)
{
	switch (n) {
		case     0: return     0;
		case     1: return    10;
		case     2: return    19;
		case     3: return    28;
		case     4: return    36;
		case     5: return    44;
		case     6: return    52;
		case     7: return    60;
		case     8: return    67;
		case     9: return    74;
		case    10: return    81;
		case    11: return    88;
		case    12: return    95;
		case    13: return   102;
		case    14: return   109;
		case    15: return   116;
		case    16: return   122;
		default   : return     0;
	}
}


/*------------------------------------------------------------------------------
	TS 44.018 Table 9.1.54.1b - q-function
------------------------------------------------------------------------------*/
unsigned DECODE_TDD_CELL_INFORMATION_q (unsigned n)
{
	switch (n) {
		case     0: return     0;
		case     1: return     9;
		case     2: return    17;
		case     3: return    25;
		case     4: return    32;
		case     5: return    39;
		case     6: return    46;
		case     7: return    53;
		case     8: return    59;
		case     9: return    65;
		case    10: return    71;
		case    11: return    77;
		case    12: return    83;
		case    13: return    89;
		case    14: return    95;
		case    15: return   101;
		case    16: return   106;
		case    17: return   111;
		case    18: return   116;
		case    19: return   121;
		case    20: return   126;
		default   : return     0;
	}
}


/*------------------------------------------------------------------------------
	Used by Annex.J
------------------------------------------------------------------------------*/
static unsigned greatestPowerOf2LesserOrEqualTo (unsigned n)
{
	unsigned ret;
	ret = 0x8000000;
	
	while (ret > n) ret >>= 1;
	
	return ret;
}

/*------------------------------------------------------------------------------
	Decodes 44.018 Annex J compression
------------------------------------------------------------------------------*/
unsigned DECODE_AnnexJ (const unsigned* inputValues, unsigned noOfInputItems, unsigned* outputValues, unsigned maxNoOfOutputValues, unsigned originalRange, unsigned offset)
{
	unsigned INDEX;
	int RANGE;
	int N;
	unsigned K;
	unsigned noOfReturnedItems = 0;

	for (K=1; K<=noOfInputItems; K++) {

		/* The next loop follows the tree from child to parent, from the node */
		/* of index K to the root (index 1). For each iteration the node of   */
		/* index INDEX is tackled. The corresponding range is RANGE, and N is */
		/* the value of the element in the range defined by the node.         */
		/* The data are set to their initial values :                         */
		
		INDEX = K;
		RANGE = originalRange / greatestPowerOf2LesserOrEqualTo(INDEX);
		N = inputValues [INDEX-1] - 1;
		
		while (INDEX>1) {

			/* Due to the assumption that the original range is a power of two  */
			/* minus one, the range for the parent node can be easily computed, */ 
			/* and does not depend upon whether the current node is a left or   */
			/* right child:                                                     */
			RANGE = 2*RANGE + 1;

			/* Let us note J = 2g-1, g being the generation of node INDEX.   */
			/* We have J = greatestPowerOf2LesserOrEqualTo(INDEX).     */
			/* The numbering used in the tree is such that the nodes of index */
			/* J to J + J/2 - 1 are left children, and the nodes of index J/2 */
			/* to J+J-1 are right children. Hence an easy test to distinguish */
			/* left and right children:                                       */
			if (2*INDEX < 3*greatestPowerOf2LesserOrEqualTo(INDEX)) { /* left child */

				/* The next computation gives the index of the parent node of the */
				/* node of index INDEX, for a left child: */
 				INDEX = INDEX - greatestPowerOf2LesserOrEqualTo(INDEX)/2;

				/* The next formula is the inverse of the renumbering appearing in the encoding */
				/* for a left child. It gives the value of the parent node in the range defined */
				/* by the grand-parent node: */
				N = (N + inputValues [INDEX-1] - 1 + (RANGE-1)/2 + 1)	% RANGE;
			}
			else { /* right child */

				/* The next computation gives the index of the parent node of the node */
				/* of index INDEX, for a right child: */
 				INDEX = INDEX - greatestPowerOf2LesserOrEqualTo(INDEX);

				/* The next formula is the inverse of the renumbering appearing in the */
				/* encoding for a right child: */
	 			N = (N + inputValues [INDEX-1] - 1 + 1) % RANGE;
	 		}
		}
		if (noOfReturnedItems < maxNoOfOutputValues) {
			outputValues [noOfReturnedItems] = N + offset;
		}
		noOfReturnedItems++;
	}
	
	return noOfReturnedItems;
}
