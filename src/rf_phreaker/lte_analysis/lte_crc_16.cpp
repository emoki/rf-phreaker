

/*****************************************************************************/
#include <stdlib.h>

#include "lte_crc_16.h"

#include "crc.h"

namespace rf_phreaker {

#define WIDTH    (8 * sizeof(crc))
#define TOPBIT   (1 << (WIDTH - 1))

void LteCRC16(unsigned char *outSeq, unsigned char *inSeq, unsigned int len)
{
	crc results;
	crcInit(16);
	results = crcFast(inSeq, 3,16);
	outSeq[0] = results>>8;
	outSeq[1] = results&0x00FF;
}


void lte_crc_16(unsigned int *outSeq, unsigned char *inSeq, unsigned int len)
{
	//crc results,remainder;
	unsigned int results,remainder;
	unsigned int num_bytes,extra_bits;
	unsigned char bit,temp;
	crcInit(16);

	num_bytes = len/8;

	extra_bits = len - (num_bytes * 8);

	results = crcFast(inSeq, num_bytes,16);
	if(results == 0x8000)
	{
	temp=0;
	}

	if(extra_bits)
	{
	  remainder = results;
	  remainder ^= (inSeq[num_bytes]) << (WIDTH - 8);
	   for (bit = 0; bit < extra_bits; bit++)
        {
            /*
             * Try to divide the current data bit.
             */
            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
	
	}

	//outSeq[0] = results>>8;
	//outSeq[1] = results&0x00FF;

	 *outSeq = remainder;
	 if(remainder==0)
	 {
	 temp = 0;
	 }
}

void lte_crc_24(unsigned int *outSeq, unsigned char *inSeq, unsigned int num_bytes)
{
	unsigned int results1/*,results2*/;

	crcInit(24);
	results1 = crcFast(inSeq, num_bytes,24);
	//results2 = crcSlow(inSeq,num_bytes);
	*outSeq = results1;

}

}