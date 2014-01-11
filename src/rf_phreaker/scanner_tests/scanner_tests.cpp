// scanner_api_unit_tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gmock\gmock.h"
#include "gtest\gtest.h"


int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

	RUN_ALL_TESTS();

	system("pause");
	
	return 0;
}

