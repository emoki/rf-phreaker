#include "rf_phreaker/umts_analysis/umts_analysis_impl.h"

umts_analysis_impl::umts_analysis_impl()
{
}

umts_analysis_impl::~umts_analysis_impl()
{
}

int umts_analysis_impl::cell_search(rf_phreaker::raw_signal &raw_signal, umts_measurement *umts_meas, int &num_umts_meas, uint32_t num_cpich_chips, umts_scan_type scan_type)
{
	int status = 0;

	try {
		auto trackign_meas = umts_meas_container_.get_meas(raw_signal.frequency());

		auto new_meas = brute_force_->process(raw_signal.get_iq(), trackign_meas, num_cpich_chips, scan_type);

		int i = 0;
		for(auto it = new_meas.begin(), end = new_meas.end(); it != end; ++it) {
			if(i >= num_umts_meas) {
				status = -1;
				break;
			}
			umts_meas[i] = *it;
		}
	} catch(const std::exception &err) {
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
	//cpich_table_->generate_resampled_cpich_table(config.up_factor(), config.down_factor());
	cpich_table_->generate_resampled_cpich_table("E:\\werk\\maharashtra\\projects\\rf_phreaker\\rf_phreaker\\output\\Debug\\cpich_taps.txt");

	brute_force_.reset(new umts_psch_with_brute_force(config, *cpich_table_));

	//decoder_.reset(new umts_bch_decoder(*cpich_table_, config));
}

