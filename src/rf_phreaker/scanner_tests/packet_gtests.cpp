#include "gtest/gtest.h"

#include "rf_phreaker/scanner/packet.h"
#include "rf_phreaker/scanner/packet_typedefs.h"
#include "rf_phreaker/scanner/packet_helper.h"

using namespace rf_phreaker::scanner;

TEST(PacketTest, TestHeaderArrayStorage)
{
	const int num_param = 4;
	header_array_storage<mem_test, num_param> test_header_array;
	for(int i = 0; i < num_param; ++i)
		test_header_array.send_data_[i] = i + num_param;

	for(int i = 0; i < num_param; ++i)
		EXPECT_EQ(i + num_param, test_header_array.send_data_[i]);

	EXPECT_STREQ("test,value", header_names[mem_test]);
	EXPECT_EQ(mem_test, test_header_array.header_);

}

TEST(PacketTest, TestHeaderArrayKnownReturnBytesStorage)
{
	const int num_param = 4;
	const int ret = 4;
	header_array_known_return_bytes_storage<mem_test, num_param, ret> test_header_array;
	EXPECT_EQ(ret, test_header_array.expected_return_bytes_);
}

TEST(PacketTest, TestStringReturnBytesStorage)
{
	std::string header("test_hdihfapw3hfnldsf");
	const int ret = 4;

	string_return_bytes_storage test_storage;

	test_storage.send_data_ = header;
	test_storage.expected_return_bytes_ = ret;

	EXPECT_STREQ(test_storage.send_data_.c_str(), header.c_str());
	EXPECT_EQ(ret, test_storage.expected_return_bytes_);
}

TEST(PacketTest, TestReturnBytesKnownPolicy)
{
	const int num = 5;
	string_return_bytes_storage storage;
	storage.expected_return_bytes_ = num;

	return_bytes_known_policy<string_return_bytes_storage> test;
	
	EXPECT_EQ(num, test.return_bytes_expected(storage));
}

TEST(PacketTest, TestReturnBytesCalcUsingSamplesPolicy)
{
	const int num = 4;
	header_array_storage<mem_test, num> header_array;
	header_array.send_data_[0] = num;

	return_bytes_calc_using_samples_policy<header_array_storage<mem_test, num>> test;
		
	EXPECT_EQ(num*4, test.return_bytes_expected(header_array));
}



TEST(PacketTest, TestSerializeMax2ParamsPolicy)
{
	const int num_param = 2;
	header_array_storage<mem_test, num_param> test_header_array;
	for(int i = 0; i < num_param; ++i)
		test_header_array.send_data_[i] = i;

	std::vector<char> buf(100);
	

	serialize_max_2_params_policy<header_array_storage<mem_test, num_param>> test_serialize;

	buf_type::iterator in_it = buf.begin();
	buf_type::iterator out_it = test_serialize.serialize(in_it, test_header_array);

	EXPECT_STREQ("test,value,00,value,01;\r", &buf[0]);
	EXPECT_EQ(sizeof("test,value,00,value,01;\r") - 1, out_it - in_it); 	
}

TEST(PacketTest, TestSerializeMax2ParamsSixCharactersPolicy)
{
	const int num_param = 2;
	header_array_storage<mem_test, num_param> test_header_array;
	for(int i = 0; i < num_param; ++i)
		test_header_array.send_data_[i] = i;

	std::vector<char> buf(100);
	

	serialize_max_2_params_policy<header_array_storage<mem_test, num_param>, true> test_serialize;

	buf_type::iterator in_it = buf.begin();
	buf_type::iterator out_it = test_serialize.serialize(in_it, test_header_array);

	EXPECT_STREQ("test,value,000000,value,000001;\r", &buf[0]);
	EXPECT_EQ(sizeof("test,value,000000,value,000001;\r") - 1, out_it - in_it); 	
}

TEST(PacketTest, TestSerializeMax2ParamsAndGoPolicy)
{
	const int num_param = 2;
	header_array_storage<mem_test, num_param> test_header_array;
	for(int i = 0; i < num_param; ++i)
		test_header_array.send_data_[i] = i;

	std::vector<char> buf(100);
	

	serialize_max_2_params_and_go_policy<header_array_storage<mem_test, num_param>, true> test_serialize;

	buf_type::iterator in_it = buf.begin();
	buf_type::iterator out_it = test_serialize.serialize(in_it, test_header_array);

	EXPECT_STREQ("test,value,000000,value,000001;\rgo;\r", &buf[0]);
	EXPECT_EQ(sizeof("test,value,000000,value,000001\r;go;\r") - 1, out_it - in_it); 	
}

TEST(PacketTest, TestSerializeIteratorPolicy)
{
	serialize_iterator_policy<string_return_bytes_storage> test_serialize;

	string_return_bytes_storage storage;
	storage.send_data_ = "test_string";

	std::vector<char> buf(100);

	buf_type::iterator in_it = buf.begin();
	buf_type::iterator out_it = test_serialize.serialize(in_it, storage);

	storage.send_data_ += packet_terminator;

	EXPECT_STREQ(storage.send_data_.c_str(), &buf[0]);
	EXPECT_EQ(storage.send_data_.size(), out_it - in_it); 	
}

TEST(PacketTest, TestPacketDefinitions)
{
	accelerometer_read_packet p;
	lime_read_packet p1;
	set_sample_size_and_go_packet p2;

	p2.set_sample_size(10000);

	auto str = p2.serialize_to_string();

	str.size();
}
