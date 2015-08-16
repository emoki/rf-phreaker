#include <stdio.h>
#include "L3Downlink.h"
#include "PLENDownlink.h"
#include "L3Uplink.h"
#include "ed_c_access.h"
#include "ed_c_recog.h"
#include "AccessDump.h"
#include "bitencode.h"

/*===========================================================================
	EXAMPLE 1
===========================================================================*/
void Example1 ()
{
	c_ALERTING_DN data1;
	long ret1;
	int len;
	const char* string = BitEncode ("x83 x01 x1E x02 xE2 x88", &len);
	
	INIT_c_ALERTING_DN (&data1);
	
	ret1 = DECODE_c_ALERTING_DN (string, 0, &data1, len);


	TEDDataBase* EDDb = AccessGet_c_ALERTING_DN	(&data1);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " STANDARD DUMP" << endl
		<< "----------------------------------------------" << endl;
	EDDb->Print (cout, 0);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " CUSTOM DUMP" << endl
		<< "----------------------------------------------" << endl;
	AccessDump (EDDb, cout);
	
	delete EDDb;
}

/*===========================================================================
	EXAMPLE 2
===========================================================================*/
void Example2 ()
{
	c_CM_SERVICE_REQUEST_UP data1;
	long ret1;
	int len;
	const char* string = BitEncode ("x05 x24 x01 x03 x57 x58 x81 x08 x29 x43 x02 x00 x10 x00 x91 x97", &len);
	
	INIT_c_CM_SERVICE_REQUEST_UP (&data1);
	
	ret1 = DECODE_c_CM_SERVICE_REQUEST_UP (string, 0, &data1, len);


	TEDDataBase* EDDb = AccessGet_c_CM_SERVICE_REQUEST_UP	(&data1);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " STANDARD DUMP" << endl
		<< "----------------------------------------------" << endl;
	EDDb->Print (cout, 0);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " CUSTOM DUMP" << endl
		<< "----------------------------------------------" << endl;
	AccessDump (EDDb, cout);
	
	delete EDDb;

}

/*===========================================================================
	EXAMPLE 3
===========================================================================*/
void Example3 ()
{
	c_SYSTEM_INFORMATION_TYPE_1_UP data1;
	long ret1;
	int len;
	const char* string = BitEncode ("x00 x06 x19 x8F x18 x00 x01 x10 x00 x00 x01 x00 x00 x00 x00 x00 x00 x00 x00 xBD x00 x00 x2B", &len);
	
	INIT_c_SYSTEM_INFORMATION_TYPE_1_UP (&data1);
	
	ret1 = DECODE_c_SYSTEM_INFORMATION_TYPE_1_UP (string, 0, &data1, len);


	TEDDataBase* EDDb = AccessGet_c_SYSTEM_INFORMATION_TYPE_1_UP	(&data1);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " STANDARD DUMP" << endl
		<< "----------------------------------------------" << endl;
	EDDb->Print (cout, 0);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " CUSTOM DUMP" << endl
		<< "----------------------------------------------" << endl;
	AccessDump (EDDb, cout);
	
	delete EDDb;

}

/*===========================================================================
	EXAMPLE 4
===========================================================================*/
void Example4 ()
{
	TXTIDUplink_Data data1;
	long ret1;
	int len;
	const char* string = BitEncode ("$0A4105030B00001F0000000000000000020121280D036973700863696E67756C6172277880C22323010100231048D81F436481B0DFF63EFFBC6AE97E19554D54535F434841505F53525652C2232F0201002F107CF480F6C91784187BD1C17C5CD9CDFD57495844433030314057352E4D5943494E47554C41522E434F4D80211C0100001C810600000000820600000000830600000000840600000000$", &len);
	
	INIT_TXTIDUplink_Data (&data1);
	
	ret1 = SetDecode_XTIDUplink (string, &data1, len);

	TEDDataBase* EDDb = AccessGet_XTIDUplink (&data1);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " TXTIDUplink_Data ret=" << ret1 << endl
		<< "----------------------------------------------" << endl;
	AccessDump (EDDb, cout);
	
	delete EDDb;
}

/*===========================================================================
	EXAMPLE 5
===========================================================================*/
void Example5 ()
{
	c_SYSTEM_INFORMATION_TYPE_2_UP data1;
	long ret1;
	int len;
	const char* string = BitEncode ("d00 $061A157C5940000000000000000000000000FFA90000$", &len);
	
	INIT_c_SYSTEM_INFORMATION_TYPE_2_UP (&data1);
	
	ret1 = DECODE_c_SYSTEM_INFORMATION_TYPE_2_UP (string, 0, &data1, len);


	TEDDataBase* EDDb = AccessGet_c_SYSTEM_INFORMATION_TYPE_2_UP	(&data1);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " SYSTEM_INFORMATION_TYPE_2_UP ret=" << ret1 << endl
		<< "----------------------------------------------" << endl;
	AccessDump (EDDb, cout);
	
	delete EDDb;
}


/*===========================================================================
	EXAMPLE 6
===========================================================================*/
void Example6 ()
{
	c_SYSTEM_INFORMATION_TYPE_2TER_UP data1;
	long ret1;
	int len;
	const char* string = BitEncode ("d00 $0603500000000801000000010000000000212B2B2B2B$", &len);
	
	INIT_c_SYSTEM_INFORMATION_TYPE_2TER_UP (&data1);
	
	ret1 = DECODE_c_SYSTEM_INFORMATION_TYPE_2TER_UP (string, 0, &data1, len);


	TEDDataBase* EDDb = AccessGet_c_SYSTEM_INFORMATION_TYPE_2TER_UP	(&data1);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " SYSTEM_INFORMATION_TYPE_2TER_UP ret=" << ret1 << endl
		<< "----------------------------------------------" << endl;
	AccessDump (EDDb, cout);
	
	delete EDDb;
}

/*===========================================================================
	EXAMPLE 7
===========================================================================*/
void Example7 ()
{
	c_SYSTEM_INFORMATION_TYPE_5_UP data1;
	long ret1;
	int len;
	const char* string = BitEncode ("d00 $061D8F000888800008008000000000000000$", &len);
	
	INIT_c_SYSTEM_INFORMATION_TYPE_5_UP (&data1);
	
	ret1 = DECODE_c_SYSTEM_INFORMATION_TYPE_5_UP (string, 0, &data1, len);


	TEDDataBase* EDDb = AccessGet_c_SYSTEM_INFORMATION_TYPE_5_UP	(&data1);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " SYSTEM_INFORMATION_TYPE_5_UP ret=" << ret1 << endl
		<< "----------------------------------------------" << endl;
	AccessDump (EDDb, cout);
	
	delete EDDb;
}

/*===========================================================================
	EXAMPLE 8
===========================================================================*/
void Example8 ()
{
	c_IMMEDIATE_ASSIGNMENT_EXTENDED_UP data1;
	long ret1;
	int len;
	const char* string = BitEncode ("d0 $0639004171451C856E0251714507854D0201FF2B2B2B$", &len);
	
	INIT_c_IMMEDIATE_ASSIGNMENT_EXTENDED_UP (&data1);
	
	ret1 = DECODE_c_IMMEDIATE_ASSIGNMENT_EXTENDED_UP (string, 0, &data1, len);


	TEDDataBase* EDDb = AccessGet_c_IMMEDIATE_ASSIGNMENT_EXTENDED_UP	(&data1);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " IMMEDIATE_ASSIGNMENT_EXTENDED_UP ret=" << ret1 << endl
		<< "----------------------------------------------" << endl;
	AccessDump (EDDb, cout);
	
	delete EDDb;
}

/*===========================================================================
	EXAMPLE 9
===========================================================================*/
void Example9 ()
{
	c_SYSTEM_INFORMATION_TYPE_2TER_UP data1;
	long ret1;
	int len;
	const char* string = BitEncode ("d00 $0603500000000801000000000008000001202B2B2B2B$", &len);
	
	INIT_c_SYSTEM_INFORMATION_TYPE_2TER_UP (&data1);
	
	ret1 = DECODE_c_SYSTEM_INFORMATION_TYPE_2TER_UP (string, 0, &data1, len);


	TEDDataBase* EDDb = AccessGet_c_SYSTEM_INFORMATION_TYPE_2TER_UP	(&data1);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " SYSTEM_INFORMATION_TYPE_2TER_UP ret=" << ret1 << endl
		<< "----------------------------------------------" << endl;
	AccessDump (EDDb, cout);
	
	delete EDDb;
}

/*===========================================================================
	EXAMPLE 10
===========================================================================*/
void Example10 ()
{
	c_CHANNEL_RELEASE_UP data1;
	long ret1;
	int len;
	const char* string = BitEncode ("$060D00730100$", &len);
	
	INIT_c_CHANNEL_RELEASE_UP (&data1);
	
	ret1 = DECODE_c_CHANNEL_RELEASE_UP (string, 0, &data1, len);


	TEDDataBase* EDDb = AccessGet_c_CHANNEL_RELEASE_UP	(&data1);
	
	cout 
		<< endl
		<< "----------------------------------------------" << endl
		<< " CHANNEL_RELEASE_UP ret=" << ret1 << endl
		<< "----------------------------------------------" << endl;
	AccessDump (EDDb, cout);
	
	delete EDDb;
}


extern TAccessDumpCustom MyAccessDumpTable [];

int main ()
{
	/* Activate the custom Access Dump table */
	AccessDumpCustomTable = MyAccessDumpTable;
	
	//Example1 ();
	//Example2 ();
	//Example3 ();
	//Example4 ();
	//Example5 ();
	//Example6 ();
	//Example7 ();
	//Example8 ();
	//Example9 ();
	Example10 ();
	return 0;
}

