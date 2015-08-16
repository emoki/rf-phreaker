#include "ed_lib.h"
#include "bitencode.h"
#include "ed_c_recog_RR.h"
#include "RRPLENDownlink_RR.h"


void Test_RRPLENDownlink (const char* desc, const char* message)
{
	const char* buffer;
	int len;
	int ret;
	TRRPLENDownlink_Data data;
	
	INIT_TRRPLENDownlink_Data (&data);
	
	buffer = BitEncode (message, &len);
	ret = SetDecode_RRPLENDownlink (buffer, &data, len);

	printf ("RRPLENDownlink decoded value (ret=%d len=%d) for %s:\n", ret, len, desc);

	#if 0
	/* No "ACCESS" license */
	TEDDataBase* accessData = AccessGet_RRPLENDownlink (&data);
	if (accessData) {
		accessData->Print (cout, 0);
		delete accessData;
	}	
	#endif
	
	FREE_TRRPLENDownlink_Data (&data);
}

void Test_RRDownlink (const char* desc, const char* message)
{
	const char* buffer;
	int len;
	int ret;
	TRRDownlink_Data data;
	
	INIT_TRRDownlink_Data (&data);
	
	buffer = BitEncode (message, &len);
	ret = SetDecode_RRDownlink (buffer, &data, len);

	printf ("RRDownlink decoded value (ret=%d len=%d) for %s:\n", ret, len, desc);
	
	#if 0
	/* No "ACCESS" license */
	TEDDataBase* accessData = AccessGet_RRDownlink (&data);
	if (accessData) {
		accessData->Print (cout, 0);
		delete accessData;
	}	
	#endif
		
	FREE_TRRDownlink_Data (&data);
}

int main ()
{
	Test_RRPLENDownlink ("SI4", "$55 06 1c 54 f4 61 03 e8 60 00 79 00 00 64 51 d0 3b 72 03 00 00 3f 05");
	Test_RRDownlink ("HANDOVER_COMMAND", "$06 2b d4 3c 1d 83 3c 02 00 D0 62 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 63 41 90 03 02 28 04 76 04 90 00 00 00");
	return 0;
}
