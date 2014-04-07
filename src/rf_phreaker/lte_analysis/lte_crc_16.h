
#ifndef __LTE__CRC16___H__
#define __LTE__CRC16___H__

#include <stdlib.h>

namespace rf_phreaker {

//#ifdef __cplusplus
//extern "C" {
//#endif




void LteCRC16(unsigned char *outSeq, unsigned char *inSeq, unsigned int len);

//void lte_crc_16(unsigned char *outSeq, unsigned char *inSeq, unsigned int len);

void lte_crc_16(unsigned int *outSeq, unsigned char *inSeq, unsigned int len);

void lte_crc_24(unsigned int *outSeq, unsigned char *inSeq, unsigned int num_bytes);



//#ifdef __cplusplus
//}           /* closing brace for extern "C" */
//#endif

}

#endif      /* __CRC___H__ */
