#include "gtest\gtest.h"

#include "rf_phreaker/processing/collection_manager.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/benchmark.h"

using namespace rf_phreaker::processing;

class CollectionManagerTest : public ::testing::Test 
{
protected:
	CollectionManagerTest()
		: cp(0, 50, 10000000)
		, cp_manager(g)
		, max_num(1000)
	{

	}

	add_remove_parameters create_add_params(int start, int stop)
	{
		add_remove_parameters params;
		std::get<0>(params).reserve(stop - start);
		for(int i = start; i < stop; ++i) {
			cp.freq_ = i;
			std::get<0>(params).push_back(cp);
		}

		return params;
	}

	add_remove_parameters create_remove_params(int start_remove, int stop_remove)
	{
		add_remove_parameters remove_params;
		std::get<1>(remove_params).reserve(stop_remove - start_remove);
		for(int i = start_remove; i < stop_remove; ++i) {
			cp.freq_ = i;
			std::get<1>(remove_params).push_back(cp);
		}

		return remove_params;
	}

	tbb::flow::graph g;
	
	collection_parameter_manager cp_manager;
	
	collection_parameters cp;

	add_remove_parameters params_blank;

	const int max_num;

};

TEST_F(CollectionManagerTest, ResetTest)
{
	auto params = create_add_params(0, max_num);

	EXPECT_EQ(0, cp_manager.operator()(params).freq_);

	add_remove_parameters params_blank;

	for(int i = 1; i < max_num / 2; ++i)
		EXPECT_EQ(i, cp_manager.operator()(params_blank).freq_);

	cp_manager.reset();

	for(int i = 0; i < max_num; ++i)
		EXPECT_EQ(i, cp_manager.operator()(params_blank).freq_);
}



TEST_F(CollectionManagerTest, AddRemoveTest)
{
	const int start_remove = 10;
	const int end_remove = 20;

	auto params = create_add_params(0, max_num);

	EXPECT_EQ(0, cp_manager.operator()(params).freq_);

	for(int i = 1; i < max_num; ++i)
		EXPECT_EQ(i, cp_manager.operator()(params_blank).freq_);

	for(int i = 0; i < max_num; ++i)
		EXPECT_EQ(i, cp_manager.operator()(params_blank).freq_);

	auto remove_params = create_remove_params(start_remove, end_remove);
	
	EXPECT_EQ(0, cp_manager.operator()(remove_params).freq_);

	for(int i = 1; i < start_remove; ++i)
		EXPECT_EQ(i, cp_manager.operator()(params_blank).freq_);

	for(int i = end_remove; i < max_num; ++i)
		EXPECT_EQ(i, cp_manager.operator()(params_blank).freq_);
}

TEST_F(CollectionManagerTest, RemoveBeforeCurrentTest)
{
	const int start_remove = 10;
	const int end_remove = 20;
	const int current_pos = 100;

	add_remove_parameters params = create_add_params(0, max_num);

	EXPECT_EQ(0, cp_manager.operator()(params).freq_);

	for(int i = 1; i < current_pos; ++i)
		EXPECT_EQ(i, cp_manager.operator()(params_blank).freq_);

	auto remove_params = create_remove_params(start_remove, end_remove);

	EXPECT_EQ(current_pos, cp_manager.operator()(remove_params).freq_);
}

TEST_F(CollectionManagerTest, RemoveCurrentTest)
{
	const int start_remove = 90;
	const int end_remove = 120;
	const int current_pos = 100;

	add_remove_parameters params = create_add_params(0, max_num);

	EXPECT_EQ(0, cp_manager.operator()(params).freq_);

	for(int i = 1; i < current_pos; ++i)
		EXPECT_EQ(i, cp_manager.operator()(params_blank).freq_);

	auto remove_params = create_remove_params(start_remove, end_remove);

	EXPECT_EQ(end_remove, cp_manager.operator()(remove_params).freq_);
}

TEST_F(CollectionManagerTest, RemoveAfterCurrentTest)
{
	const int start_remove = 120;
	const int end_remove = 150;
	const int current_pos = 100;

	add_remove_parameters params = create_add_params(0, max_num);

	EXPECT_EQ(0, cp_manager.operator()(params).freq_);

	for(int i = 1; i < current_pos; ++i)
		EXPECT_EQ(i, cp_manager.operator()(params_blank).freq_);

	auto remove_params = create_remove_params(start_remove, end_remove);

	EXPECT_EQ(current_pos, cp_manager.operator()(remove_params).freq_);
}

TEST_F(CollectionManagerTest, RemoveEndOfRangeTest)
{
	const int start_remove = 190;
	const int end_remove = max_num;
	const int current_pos = 191;

	add_remove_parameters params = create_add_params(0, max_num);

	EXPECT_EQ(0, cp_manager.operator()(params).freq_);

	for(int i = 1; i < current_pos; ++i)
		EXPECT_EQ(i, cp_manager.operator()(params_blank).freq_);

	auto remove_params = create_remove_params(start_remove, end_remove);

	EXPECT_EQ(0, cp_manager.operator()(remove_params).freq_);
}

TEST_F(CollectionManagerTest, ShouldNotRemoveUsingDifferentParametersTest)
{
	const int start_remove = 190;
	const int end_remove = max_num;
	const int current_pos = 100;

	add_remove_parameters params = create_add_params(0, max_num);

	EXPECT_EQ(0, cp_manager.operator()(params).freq_);

	cp.sampling_rate_ = 20000;

	auto remove_params = create_remove_params(start_remove, end_remove);

	EXPECT_EQ(1, cp_manager.operator()(params).freq_);

	cp_manager.reset();

	for(int i = 0; i < max_num; ++i)
		EXPECT_EQ(i, cp_manager.operator()(params_blank).freq_);
}


TEST(CollectionManagerBenchmark, Benchmark)
{
	 std::cout << "disabled benchmark!";
	//for(int j = 0; j < 100; ++j) {
	//	tbb::flow::graph g;
	//	collection_parameter_manager old_cp_manager(g);
	//	collection_parameter_manager new_cp_manager(g);

	//	add_remove_parameters_ old_param;
	//	add_remove_parameters new_param;

	//	collection_parameters cp(0, 50, 10000000);

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
	//	collection_parameter_manager old_cp_manager(g);
	//	collection_parameter_manager new_cp_manager(g);

	//	add_remove_parameters_ old_param;
	//	add_remove_parameters new_param;

	//	collection_parameters cp(0, 50, 10000000);

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

