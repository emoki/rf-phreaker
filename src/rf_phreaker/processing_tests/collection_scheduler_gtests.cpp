#include "gtest/gtest.h"

#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/processing/collection_scheduler.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/benchmark.h"
#include "rf_phreaker/common/settings.h"

using namespace rf_phreaker;
using namespace rf_phreaker::processing;

class CollectionScheduler : public ::testing::Test
{
protected:
	CollectionScheduler() 
		: c1(rf_phreaker::UMTS_LAYER_3_DECODE, false, false) 
		, c2(rf_phreaker::LTE_LAYER_3_DECODE, false, false) 
		, c3(rf_phreaker::GSM_LAYER_3_DECODE, false, false)
		, c3_empty(rf_phreaker::GSM_LAYER_3_DECODE, false, false)
		, c4(rf_phreaker::GSM_SWEEP, false, false) {
		info_c1a = collection_info(mhz(11), 10000, 0, mhz(5), 0, UMTS_LAYER_3_DECODE, OPERATING_BAND_UNKNOWN, true);
		info_c2a = collection_info(mhz(21), 10000, 0, mhz(5), 0, LTE_LAYER_3_DECODE, OPERATING_BAND_UNKNOWN, true);
		info_c2b = collection_info(mhz(22), 10000, 0, mhz(5), 0, LTE_LAYER_3_DECODE, OPERATING_BAND_UNKNOWN, true);
		info_c2c = collection_info(mhz(23), 10000, 0, mhz(5), 0, LTE_LAYER_3_DECODE, OPERATING_BAND_UNKNOWN, true);
		info_c2d = collection_info(mhz(24), 10000, 0, mhz(5), 0, LTE_LAYER_3_DECODE, OPERATING_BAND_UNKNOWN, true);
		info_c2e = collection_info(mhz(25), 10000, 0, mhz(5), 0, LTE_LAYER_3_DECODE, OPERATING_BAND_UNKNOWN, true);
		info_c2f = collection_info(mhz(26), 10000, 0, mhz(5), 0, LTE_LAYER_3_DECODE, OPERATING_BAND_UNKNOWN, true);
		info_c3a = collection_info(mhz(31), 10000, 0, mhz(5), 0, GSM_LAYER_3_DECODE, OPERATING_BAND_UNKNOWN, true);
		info_c4a = collection_info(mhz(41), 10000, 0, mhz(5), 0, GSM_SWEEP, OPERATING_BAND_UNKNOWN, true);
		info_c4b = collection_info(mhz(42), 10000, 0, mhz(5), 0, GSM_SWEEP, OPERATING_BAND_UNKNOWN, true);
		info_c4c = collection_info(mhz(43), 10000, 0, mhz(5), 0, GSM_SWEEP, OPERATING_BAND_UNKNOWN, true);
		info_c4d = collection_info(mhz(44), 10000, 0, mhz(5), 0, GSM_SWEEP, OPERATING_BAND_UNKNOWN, true);
		info_c4e = collection_info(mhz(45), 10000, 0, mhz(5), 0, GSM_SWEEP, OPERATING_BAND_UNKNOWN, true);

		c1.adjust(add_collection_info(info_c1a));
		c2.adjust(add_collection_info(info_c2a));
		c2.adjust(add_collection_info(info_c2b));
		c2.adjust(add_collection_info(info_c2c));
		c2.adjust(add_collection_info(info_c2d));
		c2.adjust(add_collection_info(info_c2e));
		c2.adjust(add_collection_info(info_c2f));
		c3.adjust(add_collection_info(info_c3a));
		c4.adjust(add_collection_info(info_c4a));
		c4.adjust(add_collection_info(info_c4b));
		c4.adjust(add_collection_info(info_c4c));
		c4.adjust(add_collection_info(info_c4d));
		c4.adjust(add_collection_info(info_c4e));
	}
	collection_info_container c1;
	collection_info_container c2;
	collection_info_container c3;
	collection_info_container c4;

	collection_info_container c3_empty;

	collection_info info_c1a;
	collection_info info_c2a;
	collection_info info_c2b;
	collection_info info_c2c;
	collection_info info_c2d;
	collection_info info_c2e;
	collection_info info_c2f;
	collection_info info_c3a;
	collection_info info_c4a;
	collection_info info_c4b;
	collection_info info_c4c;
	collection_info info_c4d;
	collection_info info_c4e;

	bool verify(const std::vector<collection_info> &g, collection_info_container &con, int num, bool check_freq = true) {
		bool is_good = true;
		auto count = 0;
		auto it = con.collection_info_group_.begin();
		std::for_each(g.begin(), g.end(), [&](const collection_info &i) {
			if(i.specs_.front() == con.specs_.front()) {
				++count;
				if(check_freq && it->freq_ != i.freq_)
					is_good = false;
				if(++it == con.collection_info_group_.end())
					it = con.collection_info_group_.begin();
			}
		});
		return is_good && count == num;
	}
};

TEST_F(CollectionScheduler, TestTechBased) {

	collection_info_containers containers;
	containers.push_back(c1);
	c2.finish_after_iteration_ = true;
	containers.push_back(c2);
	containers.push_back(c3);

	settings s;
	s.umts_layer_3_collection_.priority_ = 4;
	s.lte_layer_3_collection_.priority_ = 16;
	s.scheduling_algorithm_ = tech_based;

	collection_scheduler scheduler(&containers, &s);
	collection_info info;
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c1a, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c1a, info);

	containers[0].adjust(remove_collection_info(info_c1a));

	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2a, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2b, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2c, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2d, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2e, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2f, info);

	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c3a, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c3a, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c3a, info);

	containers[2].adjust(remove_collection_info(info_c3a));

	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2a, info);

	EXPECT_EQ(false, scheduler.is_done());
}

TEST_F(CollectionScheduler, TestTechBasedIsDone) {

	collection_info_containers containers;
	c2.finish_after_iteration_ = true;
	containers.push_back(c2);

	settings s;
	s.umts_layer_3_collection_.priority_ = 4;
	s.lte_layer_3_collection_.priority_ = 16;
	s.scheduling_algorithm_ = tech_based;

	collection_scheduler scheduler(&containers, &s, false);
	collection_info info;
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2a, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2b, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2c, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2d, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2e, info);
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(info_c2f, info);


	EXPECT_EQ(false, scheduler.is_done());
	scheduler.get_next_collection_info(info);
	EXPECT_EQ(true, scheduler.is_done());
}

TEST_F(CollectionScheduler, TestPacketBasedSamePriorityExhaustive) {
	collection_info_containers containers;
	containers.push_back(c1);
	containers.push_back(c2);
	containers.push_back(c3);
	containers.push_back(c4);

	settings s;
	s.umts_layer_3_collection_.priority_ = 1;
	s.lte_layer_3_collection_.priority_ = 1;
	s.gsm_layer_3_collection_.priority_ = 1;
	s.gsm_sweep_collection_.priority_ = 1;
	s.scheduling_algorithm_ = packet_based;

	collection_scheduler scheduler(&containers, &s);
	std::vector<collection_info> group;
	collection_info info;
	for(int i = 0; i < 24; ++i) {
		scheduler.get_next_collection_info(info);
		group.push_back(info);
	}
	EXPECT_TRUE(verify(group, c1, 6));
	EXPECT_TRUE(verify(group, c2, 6));
	EXPECT_TRUE(verify(group, c3, 6));
	EXPECT_TRUE(verify(group, c4, 6));
}

TEST_F(CollectionScheduler, TestPacketBasedDiffPriority) {
	collection_info_containers containers;
	containers.push_back(c1);
	containers.push_back(c2);
	containers.push_back(c3);
	containers.push_back(c4);

	settings s;
	s.umts_layer_3_collection_.priority_ = 10;
	s.lte_layer_3_collection_.priority_ = 5;
	s.gsm_layer_3_collection_.priority_ = 7;
	s.gsm_sweep_collection_.priority_ = 1;
	s.scheduling_algorithm_ = packet_based;

	collection_scheduler scheduler(&containers, &s);
	std::vector<collection_info> group;
	collection_info info;
	for(int i = 0; i < 23; ++i) {
		scheduler.get_next_collection_info(info);
		group.push_back(info);
	}
	EXPECT_TRUE(verify(group, c1, 10));
	EXPECT_TRUE(verify(group, c2, 5));
	EXPECT_TRUE(verify(group, c3, 7));
	EXPECT_TRUE(verify(group, c4, 1));
}

TEST_F(CollectionScheduler, TestPacketBasedDifferentPriority) {
	collection_info_containers containers;
	containers.push_back(c1);
	containers.push_back(c2);

	settings s;
	s.umts_layer_3_collection_.priority_ = 4;
	s.lte_layer_3_collection_.priority_ = 16;
	s.scheduling_algorithm_ = packet_based;

	collection_scheduler scheduler(&containers, &s);
	std::vector<collection_info> group;
	collection_info info;
	for(int i = 0; i < 6; ++i) {
		scheduler.get_next_collection_info(info);
		group.push_back(info);
	}
	EXPECT_TRUE(verify(group, c1, 2));
	EXPECT_TRUE(verify(group, c2, 4));
}

TEST_F(CollectionScheduler, TestCRBasedSamePriority) {
	collection_info_containers containers;
	containers.push_back(c1);
	containers.push_back(c2);
	containers.push_back(c3);
	containers.push_back(c4);

	settings s;
	s.umts_layer_3_collection_.priority_ = 1;
	s.lte_layer_3_collection_.priority_ = 1;
	s.gsm_layer_3_collection_.priority_ = 1;
	s.gsm_sweep_collection_.priority_ = 1;
	s.scheduling_algorithm_ = collection_round_based;

	collection_scheduler scheduler(&containers, &s);
	std::vector<collection_info> group;
	collection_info info;
	for(int i = 0; i < 9; ++i) {
		scheduler.get_next_collection_info(info);
		group.push_back(info);
	}
	EXPECT_TRUE(verify(group, c1, 1));
	EXPECT_TRUE(verify(group, c2, 6));
	EXPECT_TRUE(verify(group, c3, 1));
	EXPECT_TRUE(verify(group, c4, 1));
}

TEST_F(CollectionScheduler, TestCRBasedDiffPriority) {
	collection_info_containers containers;
	containers.push_back(c1);
	containers.push_back(c2);
	containers.push_back(c3);
	containers.push_back(c4);

	settings s;
	s.umts_layer_3_collection_.priority_ = 5;
	s.lte_layer_3_collection_.priority_ = 1;
	s.gsm_layer_3_collection_.priority_ = 1;
	s.gsm_sweep_collection_.priority_ = 5;
	s.scheduling_algorithm_ = collection_round_based;

	collection_scheduler scheduler(&containers, &s);
	std::vector<collection_info> group;
	collection_info info;
	for(int i = 0; i < 17; ++i) {
		scheduler.get_next_collection_info(info);
		group.push_back(info);
	}
	EXPECT_TRUE(verify(group, c1, 5));
	EXPECT_TRUE(verify(group, c2, 6));
	EXPECT_TRUE(verify(group, c3, 1));
	EXPECT_TRUE(verify(group, c4, 5));
}

TEST_F(CollectionScheduler, TestCRBasedEmptyContainer) {
	collection_info_containers containers;
	containers.push_back(c3_empty);
	containers.push_back(c4);

	settings s;
	s.gsm_layer_3_collection_.priority_ = 4;
	s.gsm_sweep_collection_.priority_ = 1;
	s.scheduling_algorithm_ = collection_round_based;

	collection_scheduler scheduler(&containers, &s);
	std::vector<collection_info> group;
	collection_info info;
	for(int i = 0; i < 8; ++i) {
		scheduler.get_next_collection_info(info);
		group.push_back(info);
	}
	EXPECT_TRUE(verify(group, c3, 0));
	EXPECT_TRUE(verify(group, c4, 8));

	containers[0].adjust(add_collection_info(info_c3a));

	// Reset so c3 freqs match..
	scheduler.reset();
	scheduler.update();
	group.clear();
	for(int i = 0; i < 10; ++i) {
		scheduler.get_next_collection_info(info);
		group.push_back(info);
	}
	EXPECT_TRUE(verify(group, c3, 8));
	EXPECT_TRUE(verify(group, c4, 2));
}

TEST_F(CollectionScheduler, TestSweepFirstPacketPriority) {
	collection_info_containers containers;
	containers.push_back(c1);
	containers.push_back(c2);
	containers.push_back(c3);
	containers.push_back(c4);

	settings s;
	s.umts_layer_3_collection_.priority_ = 10;
	s.lte_layer_3_collection_.priority_ = 5;
	s.gsm_layer_3_collection_.priority_ = 7;
	s.gsm_sweep_collection_.priority_ = 1;
	s.scheduling_algorithm_ = sweep_first_packet_based;

	collection_scheduler scheduler(&containers, &s);
	std::vector<collection_info> group;
	collection_info info;
	auto sweep_size = containers[3].collection_info_group_.size();
	for(size_t i = 0; i < sweep_size; ++i) {
		scheduler.update();
		scheduler.get_next_collection_info(info);
		group.push_back(info);
		info_c1a.freq_ = i * 100;
		if(i == 0)
			containers[0].adjust(add_collection_info(info_c1a));
	}
	EXPECT_TRUE(verify(group, c4, sweep_size));

	// Collect another so that it rolls collection round over.
	scheduler.get_next_collection_info(info);

	group.clear();
	for(int i = 0; i < 23; ++i) {
		scheduler.update();
		scheduler.get_next_collection_info(info);
		group.push_back(info);
	}
	// The freq order for c1 and c4 will be off so don't check it.
	EXPECT_TRUE(verify(group, c1, 10, false));
	EXPECT_TRUE(verify(group, c2, 5));
	EXPECT_TRUE(verify(group, c3, 7));
	EXPECT_TRUE(verify(group, c4, 1, false));
}