#pragma once

class cpich_tables
{
public:
	cpich_tables()
		: brute_force_cpich_table_(nullptr)
		, bch_decoder_cpich_table_(nullptr)
	{}

	~cpich_tables()
	{
		auto ptr = brute_force_cpich_table_.load(std::memory_order_relaxed)
	}

};
