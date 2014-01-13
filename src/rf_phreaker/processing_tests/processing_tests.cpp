// processing_tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"



int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}

