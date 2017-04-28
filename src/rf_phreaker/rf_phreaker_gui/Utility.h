#pragma once
#include <thread>
#include <mutex>
#include <atomic>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"

//namespace rf_phreaker { namespace gui {

inline int64_t to_hash(const rp_wcdma &a) {
	int64_t t = a.base_.measurement_frequency_;
	t = t << 32;
	t |= a.cpich_;
	return t;
}

inline int64_t to_hash(const rp_lte &a) {
	int64_t t = a.base_.measurement_frequency_;
	t = t << 32;
	t |= a.physical_cell_id_;
	return t;
}

template<typename Data, typename Group>
class api_storage {
public:
	api_storage() {}

	template<typename Group>
	api_storage(const Group &s) {
		for(int i = 0; i < s.size_; ++i) {
			v_.push_back(s.e_[i]);
		}
	}

	Group get_group() {
		Group t;
		t.size_ = v_.size();
		if(t.size_)
			t.e_ = &v_[0];
		else
			t.e_ = nullptr;
		return t;
	}

	const std::vector<Data>& get_data() {
		return v_;
	}

	void push_back(const Data &t) {
		v_.push_back(t);
	}

	void clear() {
		v_.clear();
	}

private:
	std::vector<Data> v_;
};

template<typename Data>
class thread_safe_storage {
public:
	thread_safe_storage();

	void size() const {
		std::lock_guard<std::mutex> guard(mutex_);
		return v_.size();
	}

	void store(const Data &t) {
		std::lock_guard<std::mutex> guard(mutex_);
		v_.push_back(t);
	}

	void store(Data &&t) {
		std::lock_guard<std::mutex> guard(mutex_);
		v_.push_back(t);
	}

	std::vector<Data> get_and_clear() {
		std::lock_guard<std::mutex> guard(mutex_);
		std::vector<Data> t(v_);
		v_.clear();
		return t;
	}

private:
	std::vector<Data> v_;
	std::mutex mutex_;

};

class callback_manager {
public:
	callback_manager() : sleep_duration_ms_(800) {
		is_running_ = true;
	}

	void run() {
		while(is_running_) {
			std::this_thread::sleep_for(sleep_duration_ms_);
		}
	}

	void stop() {
		is_running_ = false;
	}

	void (RP_CALLCONV rp_log_update)(const char *message) {
		log_storage_.store(message);
	}

	void (RP_CALLCONV rp_message_update)(rp_status status, const char *message);

	void (RP_CALLCONV rp_device_info_update)(const rp_device_info *info);

	void (RP_CALLCONV rp_gps_update)(const rp_gps *gps);

	void (RP_CALLCONV rp_gsm_update)(const rp_base *base, const rp_gsm *gsm, int num_gsm);

	void (RP_CALLCONV rp_umts_update)(const rp_base *base, const rp_wcdma *wcmda, int num_umts);

	void (RP_CALLCONV rp_lte_update)(const rp_base *base, const rp_lte *lte, int num_lte);

	void (RP_CALLCONV rp_sweep_update)(const rp_base *base, const rp_gsm *gsm, int num_gsm, const rp_wcdma *wcdma, int num_wcdma, const rp_lte *lte, int num_lte);

private:
	thread_safe_storage<std::string> log_storage_;
	std::atomic_bool is_running_;
	std::chrono::milliseconds sleep_duration_ms_;
};


//}
