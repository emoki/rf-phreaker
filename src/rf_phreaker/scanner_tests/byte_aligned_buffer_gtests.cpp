#include "gtest/gtest.h"
 
#include "rf_phreaker/scanner/byte_aligned_buffer.h"


TEST(ByteAlignedArrayTest, TestByteAligned)
{
	const auto size = 4000;
	auto return_bytes = sizeof(Ipp16sc) * size;

	rf_phreaker::scanner::byte_aligned_buffer<Ipp16sc> buf;

	for(int i = 0; i <= sizeof(Ipp16sc); ++i)
	{
		auto tmp = i % sizeof(Ipp16sc);
		buf.align_array(return_bytes + i);
		if(i % sizeof(Ipp16sc) == 0)
			EXPECT_EQ((char*)buf.get_unaligned_array().get(), buf.get_aligned_array()); 
		else
			EXPECT_EQ((char*)buf.get_unaligned_array().get() + sizeof(Ipp16sc) - (i % sizeof(Ipp16sc)), buf.get_aligned_array()); 
	}
}