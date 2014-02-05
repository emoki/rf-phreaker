#include "rf_phreaker/umts_analysis/umts_analysis_impl.h"

umts_analysis_impl::umts_analysis_impl()
{
}

umts_analysis_impl::~umts_analysis_impl()
{
}

int umts_analysis_impl::cell_search(const rf_phreaker::raw_signal &raw_signal, umts_measurement *umts_meas, int &num_umts_meas, uint32_t num_cpich_chips, umts_scan_type scan_type)
{
	int status = 0;

	try {
		auto trackign_meas = umts_meas_container_.get_meas(raw_signal.frequency());

		auto new_meas = brute_force_->process(raw_signal.get_iq(), trackign_meas, num_cpich_chips, scan_type);

		consolidate_measurements(new_meas);
		
		num_umts_meas = new_meas.size();

		int i = 0;
		for(auto it = new_meas.begin(), end = new_meas.end(); it != end; ++it) {
			if(i >= num_umts_meas) {
				status = -1;
				break;
			}
			umts_meas[i++] = *it;
		}
	} catch(const std::exception &err) {
		// Log error.
		std::cout << err.what() << std::endl;
		status = -2;
	}

	return status;
}

void umts_analysis_impl::consolidate_measurements(umts_measurements &group)
{
	std::sort(group.begin(), group.end(), [=](const umts_measurement &a, const umts_measurement &b) {
		if(a.cpich_ == b.cpich_)
			return a.ecio_ > b.ecio_;
		else
			return a.cpich_ < b.cpich_;
	});

	group.erase(std::unique(group.begin(), group.end(), [=](const umts_measurement &a, const umts_measurement &b) {
		return a.cpich_ == b.cpich_;
	}), group.end());
}

int umts_analysis_impl::decode_layer_3(const rf_phreaker::raw_signal &raw_signal, umts_measurement &umts_meas)
{
	int status = 0;

	try {
		status = decoder_->process(raw_signal.get_iq().get(), raw_signal.get_iq().length(), umts_meas.cpich_, umts_meas.sample_num_, umts_meas.layer_3_);
	}
	catch(const std::exception &err) {
		// Log error.
		std::cout << err.what() << std::endl;
		status = -2;
	}

	return status;
}

void umts_analysis_impl::set_config(const umts_config &config)
{
	config_ = config;

	cpich_table_.reset(new cpich_table_container);
	cpich_table_->generate_resampled_cpich_table(config.up_factor(), config.down_factor());

	brute_force_.reset(new umts_psch_with_brute_force(config, *cpich_table_));

	tmp_cpich_table_.reset(new cpich_table_container);
	tmp_cpich_table_->generate_raw_cpich_table();
	
	decoder_.reset(new umts_bch_decoder(config, *tmp_cpich_table_));
}

void umts_analysis_impl::cancel_processing()
{
	if(brute_force_.get() != nullptr)
		brute_force_->cancel_processing();
}

