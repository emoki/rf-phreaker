#pragma once

#include <string>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/protobuf_specific/rf_phreaker_serialization.h"

namespace rf_phreaker { namespace api {

class log_handler {
public:
	log_handler(rp_callbacks *cb) 
		: callbacks_(cb) { 
		int i = 0; }

	log_handler(const log_handler &handler) 
		: callbacks_(handler.callbacks_) { 
		int i = 0; }

	log_handler(log_handler &&handler)
		: callbacks_(std::move(handler.callbacks_)) { 
		int i = 0; }

	~log_handler() { int i = 0; }

	void receive_log_message(std::string message) {
		if(callbacks_) {
			// We remove the first element in the string because it's a '\n'.
			auto s = message.substr(1, message.size());
			if(callbacks_->rp_log_update) {
				callbacks_->rp_log_update(s.c_str());
			}
			if(callbacks_->rp_update) {
				update_.populate_log(s);
				update_.serialize();
				callbacks_->rp_update(update_.to_bytes(), update_.size());
			}
		}
	}
	rp_callbacks *callbacks_;
	protobuf::update_pb update_;
};

}}