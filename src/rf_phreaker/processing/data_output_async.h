#pragma once
#include "rf_phreaker/processing/data_output.h"
#include "rf_phreaker/common/concurrent.h"

namespace rf_phreaker {	namespace processing {



class data_output_async
{
public:
	data_output_async() {}

	template<typename... Args>
	std::future<void> output(Args... args) {
		return out_([=](data_output out) {
			out.output(args...);
		});
	}

	std::future<void> set_standard_output(const output_settings &settings) {
		return out_([=](data_output out) {
			out.set_standard_output(settings);
		});
	}

	std::future<void> set_file_output(const output_settings &settings) {
		return out_([=](data_output out) {
			out.set_file_output(settings);
		});
	}

	std::future<void> set_signal_output(const output_settings &settings) {
		return out_([=](data_output out) {
			out.set_signal_output(settings);
		});
	}

	std::future<void> set_output_path(const std::string &path) {
		return out_([=](data_output out) {
			out.set_output_path(path);
		});
	}

	template<typename Func>
	std::future<void> connect_hardware(Func &f) {
		return out_([=](data_output out) {
			out.connect_hardware(f);
		});
	}

	template<typename Func>
	std::future<void> connect_gps(Func &f) {
		return out_([=](data_output out) {
			out.connect_gps(f);
		});
	}

	template<typename Func>
	std::future<void> connect_gsm_layer_3(Func &f) {
		return out_([=](data_output out) {
			out.connect_gsm_layer_3(f);
		});
	}

	template<typename Func>
	std::future<void> connect_umts_layer_3(Func &f) {
		return out_([=](data_output out) {
			out.connect_umts_layer_3(f);
		});
	}

	template<typename Func>
	std::future<void> connect_lte_layer_3(Func &f) {
		return out_([=](data_output out) {
			out.connect_lte_layer_3(f);
		});
	}

	template<typename Func>
	std::future<void> connect_gsm_sweep(Func &f) {
		return out_([=](data_output out) {
			out.connect_gsm_sweep(f);
		});
	}

	template<typename Func>
	std::future<void> connect_umts_sweep(Func &f) {
		return out_([=](data_output out) {
			out.connect_umts_sweep(f);
		});
	}

	template<typename Func>
	std::future<void> connect_lte_sweep(Func &f) {
		return out_([=](data_output out) {
			out.connect_lte_sweep(f);
		});
	}

	template<typename Func>
	std::future<void> connect_sweep(Func &f) {
		return out_([=](data_output out) {
			out.connect_sweep(f);
		});
	}

	template<typename Func>
	std::future<void> connect_power_spectrum(Func &f) {
		return out_([=](data_output out) {
			out.connect_power_spectrum(f);
		});
	}

	void clear_queue() {
		out_.clear_queue();
	}

	void clear_and_wait(int loop, int ms_wait) {
		out_.clear_and_wait(loop, ms_wait);
	}

private:
	concurrent<data_output> out_;
};


}}