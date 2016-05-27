#include "gtest/gtest.h"
#include <iostream>
#include <thread>
#include "rf_phreaker/umts_analysis/umts_measurement_container.h"

using namespace rf_phreaker;

TEST(UmtsMeasurementContainerTests, TestGeneral) {
	umts_measurements group;
	std::chrono::milliseconds current_time(30000);
	for(int i = 0; i < 100; ++i) {
		umts_measurement meas;
		meas.cpich_ = i;
		auto tmp = current_time + std::chrono::seconds(i);
		meas.time_ = tmp.count();
		group.push_back(meas);
	}

	auto freq = 1;

	umts_measurement_container container;
	container.update_meas(freq, group);

	auto g = container.get_meas(freq);

	EXPECT_EQ(100, g.size());

	container.remove_old_meas(freq, std::chrono::seconds(40), std::chrono::seconds(5));

	g = container.get_meas(freq);

	EXPECT_EQ(95, g.size());
	EXPECT_EQ(5, g[0].cpich_);


}