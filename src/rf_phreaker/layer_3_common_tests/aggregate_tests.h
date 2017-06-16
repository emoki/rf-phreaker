#pragma once

#include "rf_phreaker\layer_3_common\bcch_bch_message_aggregate.h"

class aggregate_tests {
public:
	void run_automated_tests() {
		test_update();
	}

private:
	void test_update() {
		using namespace layer_3_information;
		
		bcch_bch_message_aggregate message;
		std::vector<uint8_t> v(30);

		for(int i = 0; i < 30*255; ++i) {
			size_t idx = 0;
			for(; idx < v.size() - 1; idx++) {
				if(v[idx] < 0xFF)
					break;
			}
			++(v[idx]);

			bcch_bch_message_aggregate m;
			m.raw_layer_3_.push_back(bit_stream(v.data(), v.size(), 0));

			message.update_info(m);

			if(message.raw_layer_3_.size() != i + 1)
				throw std::runtime_error("Overwrote layer 3!");

			message.update_info(m);
			if(message.raw_layer_3_.size() != i + 1)
				throw std::runtime_error("Added duplicate layer 3!");
		}
	}
};