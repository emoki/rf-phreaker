#include "gtest/gtest.h"

#include "rf_phreaker/processing/layer_3_tracker.h"
#include "rf_phreaker/common/common_types.h"


struct t_data {
	t_data(int id, int ci) {
		cid = ci;
		RsRecord.ID = id;
	}
	struct {
		int ID;
	} RsRecord;
	int cid;
};

enum test_layer_3_enum
{
	TEST_SIB,
	NUM_LAYER_3
};

template<> template<> inline int rf_phreaker::processing::all_layer_3_decoded<test_layer_3_enum, bool>::create_unique_identifier<>(const t_data &data) { return data.RsRecord.ID; }
template<> template<> inline void rf_phreaker::processing::all_layer_3_decoded<test_layer_3_enum, bool>::update(const t_data &data)
{ ++num_updated_;  if(data.cid != 0xFFFFFFFF) all_layer_3_[TEST_SIB] = true; }

TEST(Layer3Tracker, TestGeneral) {
	using namespace rf_phreaker;
	using namespace rf_phreaker::processing;

	try {
		
		::t_data t(1, 0xFFFFFFFF);
		
		frequency_type f = 100;
		frequency_type f2 = 1000;

		int max_update = 150;
		int min_collection_round = 10;
		int min_decode_count_ = 5;
		layer_3_tracker<test_layer_3_enum, bool> tracker(max_update, min_collection_round, min_decode_count_, std::vector<test_layer_3_enum>{ TEST_SIB });
		
		// No entries so everything is considered decoded.
        EXPECT_TRUE(tracker.is_all_decoded());
        EXPECT_TRUE(tracker.is_all_decoded_on_freq(f));
        EXPECT_FALSE(tracker.in_history(f, t));

		tracker.update(f, t);

		// With an entry now things are not decoded.
        EXPECT_FALSE(tracker.is_all_decoded());
        EXPECT_FALSE(tracker.is_all_decoded_on_freq(f));
        EXPECT_TRUE(tracker.is_all_decoded_on_freq(f2));

        EXPECT_TRUE(tracker.in_history(f, t));

		for(int i = 0; i < max_update; ++i) {
			tracker.update(f, t);
			tracker.update_freq(f);
		}

		// Should still be not decoded.
        EXPECT_FALSE(tracker.is_all_decoded());
        EXPECT_FALSE(tracker.is_all_decoded_on_freq(f));

		tracker.update(f, t);
		tracker.update_freq(f);

		// Max update exceeded.
        EXPECT_TRUE(tracker.has_freq_exceeded_max_updates(f));
        EXPECT_TRUE(tracker.has_data_exceeded_max_updates(f, t));

		tracker.clear();

		// Test clearing
        EXPECT_TRUE(tracker.is_all_decoded());
        EXPECT_TRUE(tracker.is_all_decoded_on_freq(f));
        EXPECT_FALSE(tracker.in_history(f, t));

		// Test has valid layer_3
		t.cid = 9;
		tracker.update(f, t);
        EXPECT_TRUE(tracker.is_all_decoded());
        EXPECT_TRUE(tracker.is_all_decoded_on_freq(f));
        EXPECT_TRUE(tracker.in_history(f, t));

		// Test additional freq
		t.cid = 0xffffffff;
		tracker.update(f2, t);
        EXPECT_FALSE(tracker.is_all_decoded());
        EXPECT_TRUE(tracker.is_all_decoded_on_freq(f));
        EXPECT_FALSE(tracker.is_all_decoded_on_freq(f2));
        EXPECT_TRUE(tracker.in_history(f, t));
        EXPECT_TRUE(tracker.in_history(f2, t));

		// Test additional freq has valid layer_3
		t.cid = 2;
		tracker.update(f2, t);
        EXPECT_TRUE(tracker.is_all_decoded());
        EXPECT_TRUE(tracker.is_all_decoded_on_freq(f));
        EXPECT_TRUE(tracker.is_all_decoded_on_freq(f2));
        EXPECT_TRUE(tracker.in_history(f, t));
        EXPECT_TRUE(tracker.in_history(f2, t));

	}
	catch (const std::exception &err) {
		std::cout << err.what() << std::endl;
		EXPECT_TRUE(0);
	}
}

TEST(Layer3Tracker, TestDecodeCount) {
	using namespace rf_phreaker;
	using namespace rf_phreaker::processing;

	::t_data t(1, 0xFFFFFFFF);

	frequency_type f = 100;
	frequency_type f2 = 1000;

	int max_update = 150;
	int min_collection_round = 10;
	int min_decode_count_ = 5;
	layer_3_tracker<test_layer_3_enum, bool> tracker(max_update, min_collection_round, min_decode_count_, std::vector<test_layer_3_enum>{ TEST_SIB });

	EXPECT_FALSE(tracker.has_freq_exceeded_max_no_decodes(f));

	for(int i = 0; i < min_collection_round; ++i) {
		tracker.update_decodes(f, false);
	}
	EXPECT_FALSE(tracker.has_freq_exceeded_max_no_decodes(f));
	tracker.update_decodes(f, false);
	EXPECT_TRUE(tracker.has_freq_exceeded_max_no_decodes(f));

	tracker.clear_decodes(f);
	for(int i = 0; i < min_decode_count_; ++i) {
		tracker.update_decodes(f, true);
	}
	EXPECT_FALSE(tracker.has_freq_exceeded_max_no_decodes(f));
	for(int i = 0; i < min_collection_round; ++i) {
		tracker.update_decodes(f, false);
	}
	EXPECT_FALSE(tracker.has_freq_exceeded_max_no_decodes(f));

	tracker.clear();
	for(int i = 0; i < min_collection_round + 1; ++i) {
		tracker.update_decodes(f, false);
	}
	EXPECT_TRUE(tracker.has_freq_exceeded_max_no_decodes(f));
}

TEST(Layer3Tracker, TestBitIndex) {
	using namespace rf_phreaker;
	using namespace rf_phreaker::processing;
	bit_index bits;
	EXPECT_FALSE(bits);
	bits = true;
	EXPECT_TRUE(bits);
	bits = false;
	bits.set_mask(6);
	bits.add_bit(5);
	EXPECT_FALSE(bits);
	bits.add_bit(0);
	bits.add_bit(1);
	bits.add_bit(2);
	EXPECT_FALSE(bits);
	bits.add_bit(3);
	bits.add_bit(4);
	EXPECT_TRUE(bits);
}