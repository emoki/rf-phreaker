#pragma once
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/common/signal_slot.h"
#include "rf_phreaker/common/measurement_io.h"
#include "rf_phreaker/umts_analysis/umts_io.h"
#include "rf_phreaker/lte_analysis/lte_io.h"

namespace rf_phreaker { namespace processing {


template<typename Data, typename Signal>
class d_output
{
public:
	d_output(bool standard_output = false)
		: output_to_standard_output_(standard_output)
	{}

	d_output(typename Signal::slot_type &slot, bool standard_output = false)
		: output_to_standard_output_(standard_output)
	{
		signal_.connect(slot);
	}

	//d_output(d_output &&meas)
	//{
	//	std::swap(output_to_standard_output_, meas.output_to_standard_output_);
	//	std::swap(signal_, meas.signal_);
	//}

	void output(std::vector<Data> data)
	{
		if(output_to_standard_output_) {
			for(const auto &it : data)
				std::cout << it << "\n";
		}
		if(connection_.connected())
			signal_(data);
	}

	void output(Data data)
	{
		if(output_to_standard_output_)
			std::cout << data << "\n";

		if(connection_.connected())
			signal_(data);
	}

	template<typename Func>
	void connect(Func f)
	{
		connection_ = signal_.connect(f);
	}

	void disconnect()
	{
		connection_.disconnect();
	}

	void set_standard_output(bool std_output) 
	{
		output_to_standard_output_ = std_output;
	}

private:
	Signal signal_;
	boost::signals2::connection connection_;
	bool output_to_standard_output_;
	// Implement google protocol buffer for file output?
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
		, lte_sweep_output_(std::make_shared<d_output<basic_data, basic_signal_type>>())
	{}

	data_output(data_output &out)
		: hardware_output_(out.hardware_output_)
		, gps_output_(out.gps_output_)
		, umts_layer_3_output_(out.umts_layer_3_output_)
		, lte_layer_3_output_(out.lte_layer_3_output_)
		, umts_sweep_output_(out.umts_sweep_output_)
		, lte_sweep_output_(out.lte_sweep_output_)
	{}


	data_output(data_output &&out)
	{
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

	void disconnect()
	{
		hardware_output_->disconnect();
		gps_output_->disconnect();
		umts_layer_3_output_->disconnect();
		lte_layer_3_output_->disconnect();
		umts_sweep_output_->disconnect();
		lte_sweep_output_->disconnect();
	}
	
	void set_standard_output(bool set_std_output)
	{
		hardware_output_->set_standard_output(set_std_output);
		gps_output_->set_standard_output(set_std_output);
		umts_layer_3_output_->set_standard_output(set_std_output);
		lte_layer_3_output_->set_standard_output(set_std_output);
		umts_sweep_output_->set_standard_output(set_std_output);
		lte_sweep_output_->set_standard_output(set_std_output);
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
