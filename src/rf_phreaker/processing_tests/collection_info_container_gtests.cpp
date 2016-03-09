#include "gtest/gtest.h"

#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/benchmark.h"

using namespace rf_phreaker::processing;

class CollectionManagerTest : public ::testing::Test 
{
protected:
	CollectionManagerTest(int num = 1000)
		: cp(0, milli_to_nano(50), 0, mhz(5), mhz(10), rf_phreaker::specifier::LTE_LAYER_3_DECODE, rf_phreaker::LTE_OPERATING_BAND_1, true)
		, cp_manager(rf_phreaker::specifier::LTE_LAYER_3_DECODE, false, true)
		, max_num(num)
	{

	}

	add_remove_collection_info create_add_params(int start, int stop)
	{
		add_remove_collection_info params;
		params.add_.reserve(stop - start);
		for(int i = start; i < stop; ++i) {
			cp.freq_ = i;
			params.add_.push_back(cp);
		}

		return params;
	}

	add_remove_collection_info create_remove_params(int start_remove, int stop_remove)
	{
		add_remove_collection_info params;
		params.remove_.reserve(stop_remove - start_remove);
		for(int i = start_remove; i < stop_remove; ++i) {
			cp.freq_ = i;
			params.remove_.push_back(cp);
		}

		return params;
	}
	
	collection_info_container cp_manager;
	
	collection_info cp;

	add_remove_collection_info params_blank;

	const int max_num;

};

TEST_F(CollectionManagerTest, ResetTest)
{
	auto params = create_add_params(0, max_num);

	cp_manager.adjust(params);
	EXPECT_FALSE(cp_manager.finished_);
	EXPECT_EQ(0, cp_manager.try_get_next_info().freq_);

	add_remove_collection_info params_blank;

	for(int i = 1; i < max_num / 2; ++i) {
		EXPECT_FALSE(cp_manager.finished_);
		EXPECT_EQ(i, cp_manager.try_get_next_info().freq_);
	}
	EXPECT_FALSE(cp_manager.finished_);

	cp_manager.reset();

	for(int i = 0; i < max_num; ++i) {
		EXPECT_FALSE(cp_manager.finished_);
		EXPECT_EQ(i, cp_manager.try_get_next_info().freq_);
	}
	EXPECT_FALSE(cp_manager.finished_);
	EXPECT_EQ(0, cp_manager.try_get_next_info().freq_);
	EXPECT_TRUE(cp_manager.finished_);
}

TEST_F(CollectionManagerTest, AddRemoveTest)
{
	const int start_remove = 10;
	const int end_remove = 20;

	auto params = create_add_params(0, max_num);

	cp_manager.adjust(params);
	EXPECT_EQ(0, cp_manager.try_get_next_info().freq_);

	for(int i = 1; i < max_num; ++i) {
		EXPECT_FALSE(cp_manager.finished_);
		EXPECT_EQ(i, cp_manager.try_get_next_info().freq_);
	}

	cp_manager.reset();

	auto remove_params = create_remove_params(start_remove, end_remove);

	cp_manager.adjust(remove_params);

	for(int i = 0; i < start_remove; ++i) {
		EXPECT_FALSE(cp_manager.finished_);
		EXPECT_EQ(i, cp_manager.try_get_next_info().freq_);
	}
	for(int i = end_remove; i < max_num; ++i) {
		EXPECT_FALSE(cp_manager.finished_);
		EXPECT_EQ(i, cp_manager.try_get_next_info().freq_);
	}
	EXPECT_FALSE(cp_manager.finished_);
	EXPECT_EQ(0, cp_manager.try_get_next_info().freq_);
	EXPECT_TRUE(cp_manager.finished_);
}

TEST_F(CollectionManagerTest, RemoveBeforeCurrentTest)
{
	const int start_remove = 10;
	const int end_remove = 20;
	const int current_pos = 100;

	add_remove_collection_info params = create_add_params(0, max_num);

	cp_manager.adjust(params);

	for(int i = 0; i < current_pos; ++i) {
		EXPECT_FALSE(cp_manager.finished_);
		EXPECT_EQ(i, cp_manager.try_get_next_info().freq_);
	}

	auto remove_params = create_remove_params(start_remove, end_remove);
	
	cp_manager.adjust(remove_params);

	EXPECT_EQ(current_pos - 1, cp_manager.try_get_current_info().freq_);
	EXPECT_EQ(current_pos, cp_manager.try_get_next_info().freq_);
}

TEST_F(CollectionManagerTest, RemoveCurrentTest)
{
	const int start_remove = 90;
	const int end_remove = 120;
	const int current_pos = 100;

	add_remove_collection_info params = create_add_params(0, max_num);

	cp_manager.adjust(params);

	for(int i = 0; i < current_pos; ++i)
		EXPECT_EQ(i, cp_manager.try_get_next_info().freq_);

	auto remove_params = create_remove_params(start_remove, end_remove);

	cp_manager.adjust(remove_params);

	EXPECT_EQ(start_remove - 1, cp_manager.try_get_current_info().freq_);
	EXPECT_EQ(end_remove, cp_manager.try_get_next_info().freq_);
}

TEST_F(CollectionManagerTest, RemoveOneTest)
{
	collection_info c(1, 1, 1,1);
	collection_info_container info;
	info.adjust(add_collection_info(c));
	info.adjust(remove_collection_info(c));

	EXPECT_EQ(0, cp_manager.collection_info_group_.size());
}

TEST_F(CollectionManagerTest, RemoveAfterCurrentTest)
{
	const int start_remove = 120;
	const int end_remove = 150;
	const int current_pos = 100;

	add_remove_collection_info params = create_add_params(0, max_num);

	cp_manager.adjust(params);

	for(int i = 0; i < current_pos; ++i)
		EXPECT_EQ(i, cp_manager.try_get_next_info().freq_);

	auto remove_params = create_remove_params(start_remove, end_remove);

	cp_manager.adjust(remove_params);

	EXPECT_EQ(current_pos - 1, cp_manager.try_get_current_info().freq_);
	EXPECT_EQ(current_pos, cp_manager.try_get_next_info().freq_);
}

TEST_F(CollectionManagerTest, RemoveEndOfRangeTest)
{
	const int start_remove = 190;
	const int end_remove = max_num;
	const int current_pos = 191;

	add_remove_collection_info params = create_add_params(0, max_num);

	cp_manager.adjust(params);

	for(int i = 0; i < current_pos; ++i)
		EXPECT_EQ(i, cp_manager.try_get_next_info().freq_);

	auto remove_params = create_remove_params(start_remove, end_remove);

	cp_manager.adjust(remove_params);

	EXPECT_FALSE(cp_manager.finished_);
	EXPECT_EQ(start_remove - 1, cp_manager.try_get_current_info().freq_);
	EXPECT_EQ(0, cp_manager.try_get_next_info().freq_);
	EXPECT_TRUE(cp_manager.finished_);
}

TEST_F(CollectionManagerTest, RemoveBeginOfRangeTest)
{
	const int start_remove = 0;
	const int end_remove = 50;
	const int current_pos = 25;

	add_remove_collection_info params = create_add_params(0, max_num);

	cp_manager.adjust(params);

	for(int i = 0; i < current_pos; ++i)
		EXPECT_EQ(i, cp_manager.try_get_next_info().freq_);

	auto remove_params = create_remove_params(start_remove, end_remove);

	cp_manager.adjust(remove_params);

	EXPECT_FALSE(cp_manager.finished_);
	EXPECT_EQ(end_remove, cp_manager.try_get_current_info().freq_);
	EXPECT_EQ(end_remove, cp_manager.try_get_next_info().freq_);
}

TEST_F(CollectionManagerTest, ShouldNotRemoveUsingDifferentParametersTest) {
	const int start_remove = 190;
	const int end_remove = max_num;
	const int current_pos = 100;

	add_remove_collection_info params = create_add_params(0, max_num);

	cp_manager.adjust(params);

	cp.sampling_rate_ = 20000;

	auto remove_params = create_remove_params(start_remove, end_remove);

	cp_manager.adjust(remove_params);

	for(int i = 0; i < max_num; ++i)
		EXPECT_EQ(i, cp_manager.try_get_next_info().freq_);
}

TEST_F(CollectionManagerTest, TestAdditionalSpecs) {
	const int start_remove = 190;
	const int end_remove = max_num;
	const int current_pos = 100;

	add_remove_collection_info params = create_add_params(0, max_num);
	for(auto &i : params.add_) {
		i.specs_.add_spec(rf_phreaker::UMTS_LAYER_3_DECODE);
	}

	cp_manager.adjust(params);

	auto remove_params = create_remove_params(start_remove, end_remove);

	cp_manager.adjust(remove_params);

	for(int i = 0; i < start_remove; ++i) {
		auto k = cp_manager.try_get_next_info();
		EXPECT_EQ(i, k.freq_);
		EXPECT_TRUE(k.specs_.has_spec(rf_phreaker::LTE_LAYER_3_DECODE));
		EXPECT_TRUE(k.specs_.has_spec(rf_phreaker::UMTS_LAYER_3_DECODE));
	}
	for(int i = start_remove; i < max_num; ++i) {
		auto k = cp_manager.try_get_next_info();
		EXPECT_EQ(i, k.freq_);
		EXPECT_FALSE(k.specs_.has_spec(rf_phreaker::LTE_LAYER_3_DECODE));
		EXPECT_TRUE(k.specs_.has_spec(rf_phreaker::UMTS_LAYER_3_DECODE));
	}
}


TEST(CollectionManagerBenchmark, DISABLED_Benchmark)
{
	//for(int j = 0; j < 100; ++j) {
	//	tbb::flow::graph g;
	//	collection_info_manager old_cp_manager(g);
	//	collection_info_manager new_cp_manager(g);

	//	add_remove_collection_info_ old_param;
	//	add_remove_collection_info new_param;

	//	collection_info cp(0, 50, 10000000);

	//	for(int i = 0; i < 5000; ++i) {
	//		cp.freq_ = i + ghz(1);
	//		std::get<0>(old_param).insert(std::make_pair(cp.freq_, cp));		
	//		std::get<0>(new_param).push_back(cp);
	//	}

	//	benchmark b_old("cp_manager_old.txt", true);

	//	b_old.start_timer();
	//	old_cp_manager.operator()(old_param);
	//	b_old.stop_timer();
	//	b_old.output_time_elapsed("added 5000 params");

	//	benchmark b_new("cp_manager_new.txt", true);
	//	b_new.start_timer();
	//	new_cp_manager.operator()(new_param);
	//	b_new.stop_timer();
	//	b_new.output_time_elapsed("added 5000 params");
	//}

	//for(int j = 0; j < 100; ++j) {
	//	tbb::flow::graph g;
	//	collection_info_manager old_cp_manager(g);
	//	collection_info_manager new_cp_manager(g);

	//	add_remove_collection_info_ old_param;
	//	add_remove_collection_info new_param;

	//	collection_info cp(0, 50, 10000000);

	//	for(int i = 0; i < 5000; ++i) {
	//		cp.freq_ = i + ghz(1);
	//		std::get<0>(old_param).insert(std::make_pair(cp.freq_, cp));		
	//		std::get<0>(new_param).push_back(cp);
	//	}
	//	
	//	old_cp_manager.operator()(old_param);
	//	new_cp_manager.operator()(new_param);

	//	std::get<0>(old_param).clear();
	//	std::get<0>(new_param).clear();

	//	for(int i = 5000; i <= 0; --i) {
	//		cp.freq_ = i + ghz(1);
	//		std::get<1>(old_param).insert(std::make_pair(cp.freq_, cp));		
	//		std::get<1>(new_param).push_back(cp);
	//	}



	//	benchmark b_old("cp_manager_old.txt", true);

	//	b_old.start_timer();
	//	b_old.stop_timer();
	//	old_cp_manager.operator()(old_param);
	//	b_old.output_time_elapsed("removed 5000 params - all matching");

	//	benchmark b_new("cp_manager_new.txt", true);
	//	b_new.start_timer();
	//	b_new.stop_timer();
	//	new_cp_manager.operator()(new_param);
	//	b_new.output_time_elapsed("removed 5000 params - all matching but worst case");
	//}

}

