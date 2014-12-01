#pragma once

#include <string>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"


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
		if(callbacks_ && callbacks_->rp_log_update)
			callbacks_->rp_log_update(message.c_str());
	}
	rp_callbacks *callbacks_;
};

}}