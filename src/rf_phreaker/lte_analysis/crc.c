/**********************************************************************
 *
 * Filename:    crc.c
 * 
 * Description: Slow and fast implementations of the CRC standards.
 *
 * Notes:       The parameters for each supported CRC standard are
 *				defined in the header file crc.h.  The implementations
 *				here should stand up to further additions to that list.
 *
 * 
 * Copyright (c) 2000 by Michael Barr.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/
 

#include "crc.h"

/*
 * Derive parameters from the standard-specific parameters in crc.h.
 */
#define WIDTH    (8 * sizeof(crc))
#define TOPBIT   (1 << (WIDTH - 1))

#if (REFLECT_DATA == TRUE)
#undef  REFLECT_DATA
#define REFLECT_DATA(X)			((unsigned char) reflect((X), 8))
#else
#undef  REFLECT_DATA
#define REFLECT_DATA(X)			(X)
#endif

#if (REFLECT_REMAINDER == TRUE)
#undef  REFLECT_REMAINDER
#define REFLECT_REMAINDER(X)	((crc) reflect((X), WIDTH))
#else
#undef  REFLECT_REMAINDER
#define REFLECT_REMAINDER(X)	(X)
#endif


/*********************************************************************
 *
 * Function:    reflect()
 * 
 * Description: Reorder the bits of a binary sequence, by reflecting
 *				them about the middle position.
 *
 * Notes:		No checking is done that nBits <= 32.
 *
 * Returns:		The reflection of the original data.
 *
 *********************************************************************/
static unsigned long
reflect(unsigned long data, unsigned char nBits)
{
	unsigned long  reflection = 0x00000000;
	unsigned char  bit;

	/*
	 * Reflect the data about the center bit.
	 */
	for (bit = 0; bit < nBits; ++bit)
	{
		/*
		 * If the LSB bit is set, set the reflection of it.
		 */
		if (data & 0x01)
		{
			reflection |= (1 << ((nBits - 1) - bit));
		}

		data = (data >> 1);
	}

	return (reflection);

}	/* reflect() */


/*********************************************************************
 *
 * Function:    crcSlow()
 * 
 * Description: Compute the CRC of a given message.
 *
 * Notes:		
 *
 * Returns:		The CRC of the message.
 *
 *********************************************************************/
//crc
unsigned int
crcSlow(unsigned char const message[], int nBytes)
{
   // crc            remainder = INITIAL_REMAINDER;
	int            byte,temp;
	unsigned char  bit;
    unsigned int polynomial,mask,width,topbit,remainder = 0x0000;

	mask = 0xFFFFFF;
	polynomial = 0x864cfb;
	width = 24;

	//mask = 0xFFFF;
	//polynomial = 0x1021;
	//width = 16;

	topbit = 1<<(width-1);


    /*
     * Perform modulo-2 division, a byte at a time.
     */
    for (byte = 0; byte < nBytes; ++byte)
    {
        /*
         * Bring the next byte into the remainder.
         */
		remainder = remainder & mask;
       // remainder ^= (REFLECT_DATA(message[byte]) << (WIDTH - 8));
		remainder ^= (REFLECT_DATA(message[byte]) << (width - 8));
		remainder = remainder & mask;

        /*
         * Perform modulo-2 division, a bit at a time.
         */
        for (bit = 8; bit > 0; --bit)
        {
            /*
             * Try to divide the current data bit.
             */
          // if ((remainder) & TOPBIT)
			if (((remainder) & topbit)&mask)
            {
                //remainder = ((remainder << 1) ^ POLYNOMIAL);
				remainder = ((remainder << 1) ^ polynomial) ;
            }
            else
            {
                //remainder = ((remainder << 1)&mask);
				remainder = (remainder << 1);
            }
			remainder = remainder & mask;
        }
    }

	temp=0;
    /*
     * The final remainder is the CRC result.
     */
    return (REFLECT_REMAINDER(remainder) ^ FINAL_XOR_VALUE);

}   /* crcSlow() */


//crc  crcTable[256];

unsigned int crc_table_24_bit[256],crc_table_16_bit[256];
//crc crc_table_24_bit[256],crc_table_16_bit[256];


/*********************************************************************
 *
 * Function:    crcInit()
 * 
 * Description: Populate the partial CRC lookup table.
 *
 * Notes:		This function must be rerun any time the CRC standard
 *				is changed.  If desired, it can be run "offline" and
 *				the table results stored in an embedded system's ROM.
 *
 * Returns:		None defined.
 *
 *********************************************************************/
void
crcInit(unsigned int crc_num_bits)
{
    //crc			   remainder,*crcTable;	
	int			   dividend;
	unsigned char  bit;
	unsigned int width,polynomial,topbit,mask;
	unsigned int *crcTable,remainder=0x00000000;

	if(crc_num_bits==16)
	{
		crcTable = crc_table_16_bit;
	    width = 16;
		polynomial = 0x1021;
		topbit= (1 << (width - 1));
		mask = 0x0000FFFF;
	}
	else
	{
        crcTable = crc_table_24_bit;
	    width = 24;
		polynomial = 0x864cfb;
		topbit= (1 << (width - 1));
		mask = 0x00FFFFFF;
	}


    /*
     * Compute the remainder of each possible dividend.
     */
    for (dividend = 0; dividend < 256; ++dividend)
    {
        /*
         * Start with the dividend followed by zeros.
         */
       //remainder = dividend << (WIDTH - 8);
		 remainder = (dividend << (width - 8));

        /*
         * Perform modulo-2 division, a bit at a time.
         */
        for (bit = 8; bit > 0; --bit)
        {
            /*
             * Try to divide the current data bit.
             */			
           // if (remainder & TOPBIT)
			if (remainder & topbit)
            {
                //remainder = (remainder << 1) ^ POLYNOMIAL;
				remainder = ((remainder << 1) ^ polynomial);

            }
            else
            {
                remainder = (remainder << 1);
            }
			
        }

        /*
         * Store the result into the table.
         */
        crcTable[dividend] = remainder & mask;
    }

	//lte_debug_filewrite("lte_crc_16_table_test.h",crcTable, 256);

}   /* crcInit() */


/*********************************************************************
 *
 * Function:    crcFast()
 * 
 * Description: Compute the CRC of a given message.
 *
 * Notes:		crcInit() must be called first.
 *
 * Returns:		The CRC of the message.
 *
 *********************************************************************/
crc crcFast(unsigned char const message[], int nBytes,unsigned int crc_num_bits)
//unsigned int crcFast(unsigned char const message[], int nBytes,unsigned int crc_num_bits)
{
   // crc	           remainder = INITIAL_REMAINDER, *crcTable;
    unsigned char  data;
	int            byte;
	unsigned int width,polynomial,topbit;
	unsigned int *crcTable,mask,remainder = INITIAL_REMAINDER;

	if(crc_num_bits==16)
	{
		crcTable = crc_table_16_bit;
	    width = 16;
		polynomial = 0x1021;
		topbit= (1 << (width - 1));
		mask = 0x0000FFFF;
	}
	else
	{
        crcTable = crc_table_24_bit;
	    width = 24;
		polynomial = 0x0;
		topbit= (1 << (width - 1));
		mask = 0x00FFFFFF;
		//remainder = 0xFFFFFF;
	}

    
	
	
	/*
     * Divide the message by the polynomial, a byte at a time.
     */
    for (byte = 0; byte < nBytes; ++byte)
    {
        //data = REFLECT_DATA(message[byte]) ^ (remainder >> (WIDTH - 8));
		data = REFLECT_DATA(message[byte]) ^ (remainder >> (width - 8));
  		remainder = crcTable[data] ^ (remainder << 8);
		remainder = remainder & mask;
    }

    /*
     * The final remainder is the CRC.
     */
    return (REFLECT_REMAINDER(remainder) ^ FINAL_XOR_VALUE);

}   /* crcFast() */
