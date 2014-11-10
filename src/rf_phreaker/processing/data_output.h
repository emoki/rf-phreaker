#pragma once
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/signal_slot.h"
#include "rf_phreaker/common/measurement_io.h"
#include "rf_phreaker/common/log.h"
#include "rf_phreaker/umts_analysis/umts_io.h"
#include "rf_phreaker/lte_analysis/lte_io.h"

namespace rf_phreaker { namespace processing {


template<typename Data, typename Signal>
class d_output
{
public:
	d_output(bool output_to_signal = true, bool output_to_file = false, bool standard_output = false)
		: output_to_signal_(output_to_signal)
		, output_to_file_(output_to_file_)
		, output_to_standard_output_(standard_output) {}

	d_output(typename Signal::slot_type &slot, bool output_to_signal = true, bool output_to_file = false, bool standard_output = false)
		: output_to_signal_(output_to_signal)
		, output_to_file_(output_to_file_)
		, output_to_standard_output_(standard_output) {
		signal_.connect(slot);
	}

	void output(std::vector<Data> data) {
		if(output_to_standard_output_) {
			for(const auto &d : data)
				std::cout << d << "\n";
		}
		if(output_to_file_) {
			check_file_and_header();
			for(const auto &d : data)
				file_ << d << std::endl;
		}
		if(output_to_signal_)
			signal_(data);
	}

	void output(Data data) {
		if(output_to_standard_output_)
			std::cout << data << "\n";
		if(output_to_file_) {
			check_file_and_header();
			file_ << data << std::endl;
		}
		if(output_to_signal_)
			signal_(data);
	}

	void check_file_and_header() {
		if(!file_.is_open()) {
			file_.open(filename_);
			if(!file_) {
				LOG(LERROR) << "Error opening file: " << filename_ << ".  errno: " << std::strerror(errno);
			}
			header(file_, Data()) << std::endl;
		}
	}

	template<typename Func>
	void connect(Func f) {
		signal_.connect(f);
	}

	void disconnect() {
		signal_.disconnect_all_slots();
	}

	void set_standard_output(bool std_output) {
		output_to_standard_output_ = std_output;
	}

	void set_file_output(bool file_output) {
		output_to_file_ = file_output;
	}

	void set_signal_output(bool signal_output) {
		output_to_signal_ = signal_output;
	}

	void append_filename(const std::string &filename) {
		filename_ = file_base(Data()) + filename + ".txt";
	}

	void set_filename(const std::string &filename) {
		filename_ = filename;
	}

private:
	Signal signal_;
	bool output_to_standard_output_;
	bool output_to_file_;
	bool output_to_signal_;
	std::ofstream file_;
	std::string filename_;
};

class data_output
{
public:
	data_output()
		: hardware_output_(std::make_shared<d_output<hardware, hardware_signal_type>>())
		, gps_output_(std::make_shared<d_output<gps, gps_signal_type>>())
		, umts_layer_3_output_(std::make_shared<d_output<umts_data, umts_signal_type>>())
		, lte_layer_3_output_(std::make_shared<d_output<lte_data, lte_signal_type>>())
		, umts_sweep_output_(std::make_shared<d_output<basic_data, basic_signal_type>>())
		, lte_sweep_output_(std::make_shared<d_output<basic_data, basic_signal_type>>()) {
		auto time = static_timestamp_string();
		hardware_output_->set_filename("scanner_" + time + ".txt");
		gps_output_->set_filename("gps_" + time + ".txt");
		umts_layer_3_output_->set_filename("umts_layer_3_" + time + ".txt");
		lte_layer_3_output_->set_filename("lte_layer_3_" + time + ".txt");
		umts_sweep_output_->set_filename("umts_sweep_" + time + ".txt");
		lte_sweep_output_->set_filename("lte_sweep_" + time + ".txt");
	}

	data_output(data_output &out)
		: hardware_output_(out.hardware_output_)
		, gps_output_(out.gps_output_)
		, umts_layer_3_output_(out.umts_layer_3_output_)
		, lte_layer_3_output_(out.lte_layer_3_output_)
		, umts_sweep_output_(out.umts_sweep_output_)
		, lte_sweep_output_(out.lte_sweep_output_) {
		auto time = static_timestamp_string();
		hardware_output_->set_filename("scanner_" + time + ".txt");
		gps_output_->set_filename("gps_" + time + ".txt");
		umts_layer_3_output_->set_filename("umts_layer_3_" + time + ".txt");
		lte_layer_3_output_->set_filename("lte_layer_3_" + time + ".txt");
		umts_sweep_output_->set_filename("umts_sweep_" + time + ".txt");
		lte_sweep_output_->set_filename("lte_sweep_" + time + ".txt");
	}


	data_output(data_output &&out) {
		std::swap(hardware_output_, out.hardware_output_);
		std::swap(gps_output_, out.gps_output_);
		std::swap(umts_layer_3_output_, out.umts_layer_3_output_);
		std::swap(lte_layer_3_output_, out.lte_layer_3_output_);
		std::swap(umts_sweep_output_, out.umts_sweep_output_);
		std::swap(lte_sweep_output_, out.lte_sweep_output_);
	}

	void output(hardware data) { hardware_output_->output(data); }
	void output(gps data) { gps_output_->output(data); }
	void output(std::vector<umts_data> data) { umts_layer_3_output_->output(data); }
	void output(std::vector<lte_data> data) { lte_layer_3_output_->output(data); }
	void output_umts_sweep(basic_data data) { umts_sweep_output_->output(data); }
	void output_lte_sweep(basic_data data) { lte_sweep_output_->output(data); }

	template<typename Func> void connect_hardware(Func &f) { hardware_output_->connect(f); }
	template<typename Func> void connect_gps(Func &f) { gps_output_->connect(f); }
	template<typename Func> void connect_umts_layer_3(Func &f) { umts_layer_3_output_->connect(f); }
	template<typename Func> void connect_lte_layer_3(Func &f) { lte_layer_3_output_->connect(f); }
	template<typename Func> void connect_umts_sweep(Func &f) { umts_sweep_output_->connect(f); }
	template<typename Func> void connect_lte_sweep(Func &f) { lte_sweep_output_->connect(f); }

	void disconnect() {
		hardware_output_->disconnect();
		gps_output_->disconnect();
		umts_layer_3_output_->disconnect();
		lte_layer_3_output_->disconnect();
		umts_sweep_output_->disconnect();
		lte_sweep_output_->disconnect();
	}

	void set_standard_output(const output_settings &settings) {
		hardware_output_->set_standard_output(settings.scanner_);
		gps_output_->set_standard_output(settings.gps_);
		umts_layer_3_output_->set_standard_output(settings.umts_layer_3_);
		lte_layer_3_output_->set_standard_output(settings.lte_layer_3_);
		umts_sweep_output_->set_standard_output(settings.umts_sweep_);
		lte_sweep_output_->set_standard_output(settings.lte_sweep_);
	}

	void set_file_output(const output_settings &settings) {
		hardware_output_->set_file_output(settings.scanner_);
		gps_output_->set_file_output(settings.gps_);
		umts_layer_3_output_->set_file_output(settings.umts_layer_3_);
		lte_layer_3_output_->set_file_output(settings.lte_layer_3_);
		umts_sweep_output_->set_file_output(settings.umts_sweep_);
		lte_sweep_output_->set_file_output(settings.lte_sweep_);
	}

	void set_signal_output(const output_settings &settings) {
		hardware_output_->set_signal_output(settings.scanner_);
		gps_output_->set_signal_output(settings.gps_);
		umts_layer_3_output_->set_signal_output(settings.umts_layer_3_);
		lte_layer_3_output_->set_signal_output(settings.lte_layer_3_);
		umts_sweep_output_->set_signal_output(settings.umts_sweep_);
		lte_sweep_output_->set_signal_output(settings.lte_sweep_);
	}

	void append_filename(const std::string &filename) {
		hardware_output_->append_filename(filename);
		gps_output_->append_filename(filename);
		umts_layer_3_output_->append_filename(filename);
		lte_layer_3_output_->append_filename(filename);
		umts_sweep_output_->append_filename(filename);
		lte_sweep_output_->append_filename(filename);
	}

private:
	std::shared_ptr<d_output<hardware, hardware_signal_type>> hardware_output_;
	std::shared_ptr<d_output<gps, gps_signal_type>> gps_output_;
	std::shared_ptr<d_output<umts_data, umts_signal_type>> umts_layer_3_output_;
	std::shared_ptr<d_output<lte_data, lte_signal_type>> lte_layer_3_output_;
	std::shared_ptr<d_output<basic_data, basic_signal_type>> umts_sweep_output_;
	std::shared_ptr<d_output<basic_data, basic_signal_type>> lte_sweep_output_;

};

}}
