#include "gtest/gtest.h"
#include <fstream>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "rf_phreaker/common/serialization_helper.h"

using namespace rf_phreaker;

struct test_serial {
public:
	test_serial() : a_(0), b_(0), c_(0) {}
	test_serial(int a, int b, int c) : a_(a), b_(b), c_(c) {}
	int a_;
	int b_;
	int c_;
	void clear() { a_ = 0; b_ = 0; c_ = 0; }
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & a_;
		ar & b_;
		ar & c_;
	}
};

TEST(SerializationHelperTest, GeneralTest) {
	test_serial test(1, 2, 3);
	auto bytes = serialization_helper::serialize_to_bytes(test);
	test_serial ret;
	EXPECT_TRUE(serialization_helper::init(bytes, ret));
	EXPECT_EQ(test.a_, ret.a_);
	EXPECT_EQ(test.b_, ret.b_);
	EXPECT_EQ(test.c_, ret.c_);
}
TEST(SerializationHelperTest, ModTest) {
	test_serial test(1, 2, 3);
	auto bytes = serialization_helper::serialize_to_bytes(test, 256);
	EXPECT_EQ(0, bytes.size() % 256);
	test_serial ret;
	EXPECT_TRUE(serialization_helper::init(bytes, ret));
	EXPECT_EQ(test.a_, ret.a_);
	EXPECT_EQ(test.b_, ret.b_);
	EXPECT_EQ(test.c_, ret.c_);
}
TEST(SerializationHelperTest, ShaTest) {
	test_serial test(1, 2, 3);
	auto bytes = serialization_helper::serialize_to_bytes(test, 256, true);
	EXPECT_EQ(0, bytes.size() % 256);
	test_serial ret;
	EXPECT_TRUE(serialization_helper::init(bytes, ret, true));
	EXPECT_EQ(test.a_, ret.a_);
	EXPECT_EQ(test.b_, ret.b_);
	EXPECT_EQ(test.c_, ret.c_);

	// Change c_ from 3 to 4.
	bytes[37] = '4';
	EXPECT_FALSE(serialization_helper::init(bytes, ret, true));
	EXPECT_EQ(1, ret.a_);
	EXPECT_EQ(2, ret.b_);
	EXPECT_EQ(4, ret.c_);
}

TEST(SerializationHelperTest, ClearTest) {
	test_serial ret(1, 2, 3);
	auto bytes = serialization_helper::serialize_to_bytes(ret, 256, true);

	bytes.clear();
	EXPECT_NO_THROW(serialization_helper::init(bytes, ret, true), boost::archive::archive_exception);
	EXPECT_EQ(0, ret.a_);
	EXPECT_EQ(0, ret.b_);
	EXPECT_EQ(0, ret.c_);
}