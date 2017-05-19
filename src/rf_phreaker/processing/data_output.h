#pragma once
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/signal_slot.h"
#include "rf_phreaker/common/measurement_io.h"
#include "rf_phreaker/common/log.h"
#include "rf_phreaker/umts_analysis/umts_io.h"
#include "rf_phreaker/lte_analysis/lte_io.h"

namespace rf_phreaker { namespace processing {

template<typename Signal, typename MainData, typename... Args>
class d_output
{
public:
	d_output(bool output_to_signal = true, bool output_to_file = false, bool standard_output = false)
		: output_to_signal_(output_to_signal)
		, output_to_file_(output_to_file)
		, output_to_standard_output_(standard_output) {}

	d_output(typename Signal::slot_type &slot, bool output_to_signal = true, bool output_to_file = false, bool standard_output = false)
		: output_to_signal_(output_to_signal)
		, output_to_file_(output_to_file)
		, output_to_standard_output_(standard_output) {
		signal_.connect(slot);
	}

	void output(MainData data, Args... args) {
		if(output_to_standard_output_)
			output_to_std(data, is_vector<MainData>{});
		if(output_to_file_) {
			check_file_and_header();
			output_to_file(data, is_vector<MainData>{});
		}
		if(output_to_signal_)
			signal_(data, args...);
	}

	void check_file_and_header() {
		if(!file_.is_open()) {
			file_.open(filename_);
			if(!file_) {
				LOG(LERROR) << "Error opening file: " << filename_ << ".  errno: " << std::strerror(errno);
			}
			header(file_, MainData()) << std::endl;
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

	void set_filename(const std::string &filename) {
		filename_ = filename;
	}

private:
	void output_to_std(const MainData &data, std::true_type) {
		for(auto &i : data)
			std::cout << i << std::endl;
	}

	void output_to_std(const MainData &data, std::false_type) {
		std::cout << data << std::endl;
	}

	void output_to_file(const MainData &data, std::true_type) {
		for(auto &i : data)
			file_ << i << std::endl;
	}

	void output_to_file(const MainData &data, std::false_type) {
		file_ << data << std::endl;
	}

	Signal signal_;
	bool output_to_standard_output_;
	bool output_to_file_;
	bool output_to_signal_;
	std::ofstream file_;
	std::string filename_;
};

// This class consolidates the data output and using data_output_async we can serialize access to it.
class data_output
{
public:
	data_output()
		: hardware_output_(std::make_shared<hardware_output_type>())
		, gps_output_(std::make_shared<gps_output_type>())
		, gsm_layer_3_output_(std::make_shared<gsm_layer_3_output_type>())
		, umts_layer_3_output_(std::make_shared<umts_layer_3_output_type>())
		, lte_layer_3_output_(std::make_shared<lte_layer_3_output_type>())
		, gsm_sweep_output_(std::make_shared<gsm_sweep_output_type>())
		, umts_sweep_output_(std::make_shared<umts_sweep_output_type>())
		, lte_sweep_output_(std::make_shared<lte_sweep_output_type>())
		, sweep_output_(std::make_shared<sweep_output_type>())
		, power_spectrum_output_(std::make_shared<power_spectrum_output_type>())
		, iq_data_output_(std::make_shared<iq_data_output_type>()) {
		auto time = static_timestamp::to_string();
		hardware_output_->set_filename("scanner_" + time + ".txt");
		gps_output_->set_filename("gps_" + time + ".txt");
		gsm_layer_3_output_->set_filename("gsm_layer_3_" + time + ".txt");
		umts_layer_3_output_->set_filename("umts_layer_3_" + time + ".txt");
		lte_layer_3_output_->set_filename("lte_layer_3_" + time + ".txt");
		gsm_sweep_output_->set_filename("gsm_sweep_" + time + ".txt");
		umts_sweep_output_->set_filename("umts_sweep_" + time + ".txt");
		lte_sweep_output_->set_filename("lte_sweep_" + time + ".txt");
		sweep_output_->set_filename("sweep_" + time + ".txt");
		power_spectrum_output_->set_filename("power_spectrum_" + time + ".txt");
		iq_data_output_->set_filename("iq_data_" + time + ".txt");
	}

	data_output(data_output &out)
		: hardware_output_(out.hardware_output_)
		, gps_output_(out.gps_output_)
		, gsm_layer_3_output_(out.gsm_layer_3_output_)
		, umts_layer_3_output_(out.umts_layer_3_output_)
		, lte_layer_3_output_(out.lte_layer_3_output_)
		, gsm_sweep_output_(out.gsm_sweep_output_)
		, umts_sweep_output_(out.umts_sweep_output_)
		, lte_sweep_output_(out.lte_sweep_output_)
		, sweep_output_(std::make_shared<sweep_output_type>()) // why is sweep different?
		, power_spectrum_output_(out.power_spectrum_output_)
		, iq_data_output_(out.iq_data_output_) {}


	data_output(data_output &&out) {
		std::swap(hardware_output_, out.hardware_output_);
		std::swap(gps_output_, out.gps_output_);
		std::swap(gsm_layer_3_output_, out.gsm_layer_3_output_);
		std::swap(umts_layer_3_output_, out.umts_layer_3_output_);
		std::swap(lte_layer_3_output_, out.lte_layer_3_output_);
		std::swap(gsm_sweep_output_, out.gsm_sweep_output_);
		std::swap(umts_sweep_output_, out.umts_sweep_output_);
		std::swap(lte_sweep_output_, out.lte_sweep_output_);
		std::swap(sweep_output_, out.sweep_output_);
		std::swap(power_spectrum_output_, out.power_spectrum_output_);
		std::swap(iq_data_output_, out.iq_data_output_);
	}

	void output(hardware d) { hardware_output_->output(d); }
	void output(gps d) { gps_output_->output(d); }
	void output(std::vector<gsm_data> t, basic_data b) { gsm_layer_3_output_->output(t, b); }
	void output(std::vector<umts_data> t, basic_data b) { umts_layer_3_output_->output(t, b); }
	void output(std::vector<lte_data> t, basic_data b) { lte_layer_3_output_->output(t, b); }
	void output(basic_data b, std::vector<gsm_data> t) { gsm_sweep_output_->output(b, t); }
	void output(basic_data b, std::vector<umts_data> t) { umts_sweep_output_->output(b, t); }
	void output(basic_data b, std::vector<lte_data> t) { lte_sweep_output_->output(b, t); }
	void output(basic_data b, std::vector<gsm_data> g, std::vector<umts_data> u, std::vector<lte_data> l) {
		sweep_output_->output(b, g, u, l);
	}
	void output(power_spectrum_data t) { power_spectrum_output_->output(t); }
	void output(iq_data t) { iq_data_output_->output(t); }

	template<typename Func> void connect_hardware(Func &f) { hardware_output_->connect(f); }
	template<typename Func> void connect_gps(Func &f) { gps_output_->connect(f); }
	template<typename Func> void connect_gsm_layer_3(Func &f) { gsm_layer_3_output_->connect(f); }
	template<typename Func> void connect_umts_layer_3(Func &f) { umts_layer_3_output_->connect(f); }
	template<typename Func> void connect_lte_layer_3(Func &f) { lte_layer_3_output_->connect(f); }
	template<typename Func> void connect_gsm_sweep(Func &f) { gsm_sweep_output_->connect(f); }
	template<typename Func> void connect_umts_sweep(Func &f) { umts_sweep_output_->connect(f); }
	template<typename Func> void connect_lte_sweep(Func &f) { lte_sweep_output_->connect(f); }
	template<typename Func> void connect_sweep(Func &f) { sweep_output_->connect(f); }
	template<typename Func> void connect_power_spectrum(Func &f) { power_spectrum_output_->connect(f); }
	template<typename Func> void connect_iq_data(Func &f) { iq_data_output_->connect(f); }

	void disconnect() {
		hardware_output_->disconnect();
		gps_output_->disconnect();
		gsm_layer_3_output_->disconnect();
		umts_layer_3_output_->disconnect();
		lte_layer_3_output_->disconnect();
		gsm_sweep_output_->disconnect();
		umts_sweep_output_->disconnect();
		lte_sweep_output_->disconnect();
		sweep_output_->disconnect();
		power_spectrum_output_->disconnect();
		iq_data_output_->disconnect();
	}

	void set_standard_output(const output_settings &settings) {
		hardware_output_->set_standard_output(settings.scanner_);
		gps_output_->set_standard_output(settings.gps_);
		gsm_layer_3_output_->set_standard_output(settings.gsm_layer_3_);
		umts_layer_3_output_->set_standard_output(settings.umts_layer_3_);
		lte_layer_3_output_->set_standard_output(settings.lte_layer_3_);
		gsm_sweep_output_->set_standard_output(settings.gsm_sweep_);
		umts_sweep_output_->set_standard_output(settings.umts_sweep_);
		lte_sweep_output_->set_standard_output(settings.lte_sweep_);
		sweep_output_->set_standard_output(settings.sweep_);
		power_spectrum_output_->set_standard_output(settings.power_spectrum_);
		iq_data_output_->set_standard_output(settings.iq_data_);
	}

	void set_file_output(const output_settings &settings) {
		hardware_output_->set_file_output(settings.scanner_);
		gps_output_->set_file_output(settings.gps_);
		gsm_layer_3_output_->set_file_output(settings.gsm_layer_3_);
		umts_layer_3_output_->set_file_output(settings.umts_layer_3_);
		lte_layer_3_output_->set_file_output(settings.lte_layer_3_);
		gsm_sweep_output_->set_file_output(settings.gsm_sweep_);
		umts_sweep_output_->set_file_output(settings.umts_sweep_);
		lte_sweep_output_->set_file_output(settings.lte_sweep_);
		sweep_output_->set_file_output(settings.sweep_);
		power_spectrum_output_->set_file_output(settings.power_spectrum_);
		iq_data_output_->set_file_output(settings.iq_data_);
	}

	void set_signal_output(const output_settings &settings) {
		hardware_output_->set_signal_output(settings.scanner_);
		gps_output_->set_signal_output(settings.gps_);
		gsm_layer_3_output_->set_signal_output(settings.gsm_layer_3_);
		umts_layer_3_output_->set_signal_output(settings.umts_layer_3_);
		lte_layer_3_output_->set_signal_output(settings.lte_layer_3_);
		gsm_sweep_output_->set_signal_output(settings.gsm_sweep_);
		umts_sweep_output_->set_signal_output(settings.umts_sweep_);
		sweep_output_->set_signal_output(settings.sweep_);
		power_spectrum_output_->set_signal_output(settings.power_spectrum_);
		iq_data_output_->set_signal_output(settings.iq_data_);
	}

	void set_output_path(const std::string &path) {
		auto time = static_timestamp::to_string();
		hardware_output_->set_filename(path + "scanner_" + time + ".txt");
		gps_output_->set_filename(path + "gps_" + time + ".txt");
		gsm_layer_3_output_->set_filename(path + "gsm_layer_3_" + time + ".txt");
		umts_layer_3_output_->set_filename(path + "umts_layer_3_" + time + ".txt");
		lte_layer_3_output_->set_filename(path + "lte_layer_3_" + time + ".txt");
		gsm_sweep_output_->set_filename(path + "gsm_sweep_" + time + ".txt");
		umts_sweep_output_->set_filename(path + "umts_sweep_" + time + ".txt");
		lte_sweep_output_->set_filename(path + "lte_sweep_" + time + ".txt");
		sweep_output_->set_filename(path + "sweep_" + time + ".txt");
		power_spectrum_output_->set_filename(path + "power_spectrum_" + time + ".txt");
		iq_data_output_->set_filename(path + "iq_data_" + time + ".txt");
	}

private:
	typedef d_output<hardware_signal_type, hardware> hardware_output_type;
	typedef d_output<gps_signal_type, gps> gps_output_type;
	typedef d_output<basic_signal_type, basic_data> basic_output_type;
	typedef d_output<gsm_signal_type, std::vector<gsm_data>, basic_data> gsm_layer_3_output_type;
	typedef d_output<umts_signal_type, std::vector<umts_data>, basic_data> umts_layer_3_output_type;
	typedef d_output<lte_signal_type, std::vector<lte_data>, basic_data> lte_layer_3_output_type;
	typedef d_output<gsm_sweep_signal_type, basic_data, std::vector<gsm_data>> gsm_sweep_output_type;
	typedef d_output<umts_sweep_signal_type, basic_data, std::vector<umts_data>> umts_sweep_output_type;
	typedef d_output<lte_sweep_signal_type, basic_data, std::vector<lte_data>> lte_sweep_output_type;
	typedef d_output<sweep_signal_type, basic_data, std::vector<gsm_data>,
		std::vector<umts_data>, std::vector<lte_data>> sweep_output_type;
	typedef d_output<lte_sweep_signal_type, basic_data, std::vector<lte_data>> lte_sweep_output_type;
	typedef d_output<power_spectrum_signal_type, power_spectrum_data> power_spectrum_output_type;
	typedef d_output<iq_data_signal_type, iq_data> iq_data_output_type;

	std::shared_ptr<hardware_output_type> hardware_output_;
	std::shared_ptr<gps_output_type> gps_output_;
	std::shared_ptr<gsm_layer_3_output_type> gsm_layer_3_output_;
	std::shared_ptr<umts_layer_3_output_type> umts_layer_3_output_;
	std::shared_ptr<lte_layer_3_output_type> lte_layer_3_output_;
	std::shared_ptr<gsm_sweep_output_type> gsm_sweep_output_;
	std::shared_ptr<umts_sweep_output_type> umts_sweep_output_;
	std::shared_ptr<lte_sweep_output_type> lte_sweep_output_;
	std::shared_ptr<sweep_output_type> sweep_output_;
	std::shared_ptr<power_spectrum_output_type> power_spectrum_output_;
	std::shared_ptr<iq_data_output_type> iq_data_output_;
};

}}
