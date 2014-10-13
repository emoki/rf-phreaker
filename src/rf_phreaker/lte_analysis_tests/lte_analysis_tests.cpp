#include "stdafx.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"


int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);

	RUN_ALL_TESTS();

	return 0;
}

