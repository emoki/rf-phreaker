#include "gtest/gtest.h"

#include "rf_phreaker/common/common_utility.h"

using namespace rf_phreaker;

TEST(CommonUtility, Round) {
	EXPECT_EQ(110, round_to_nearest<10>(106));
}