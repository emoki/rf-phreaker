#include "rf_phreaker/umts_analysis/umts_analysis_impl.h"
#include "rf_phreaker/umts_analysis/umts_utilities.h"
#include "rf_phreaker/common/delegate_sink.h"

namespace rf_phreaker {

std::shared_ptr<cpich_table_container> umts_analysis_impl::brute_force_cpich_table_;
std::shared_ptr<cpich_table_container> umts_analysis_impl::bch_decoder_cpich_table_;
std::mutex umts_analysis_impl::mutex_;

umts_analysis_impl::umts_analysis_impl(const umts_config &config)
	: config_(config)
{
}

umts_analysis_impl::~umts_analysis_impl()
{
}

int umts_analysis_impl::cell_search(const rf_phreaker::raw_signal &raw_signal, umts_measurement *umts_meas, int &num_umts_meas, double sensitivity, umts_scan_type scan_type, double *rms)
{
	int status = 0;

	try {
		if(sensitivity < -30.0)
			throw rf_phreaker::umts_analysis_error("UMTS sensitivity threshold is too low.");

		if(sensitivity > 0.0)
			throw rf_phreaker::umts_analysis_error("UMTS sensitivity threshold is invalid.");

		uint32_t num_cpich_chips = umts_utilities::calculate_num_chips_from_ecio_threshold(sensitivity);

		auto &tracking_meas = umts_meas_container_.get_meas(raw_signal.frequency());

		if(!brute_force_)
			brute_force_.reset(new umts_psch_with_brute_force(config_, brute_force_cpich_table_ptr()->cpich_table_ptr()));

		auto new_meas = brute_force_->process(raw_signal.get_iq(), tracking_meas, num_cpich_chips, scan_type);

		consolidate_measurements(new_meas);

		umts_meas_container_.update_meas(raw_signal.frequency(), new_meas);
		
		int i = 0;
		for(auto it = new_meas.begin(), end = new_meas.end(); it != end; ++it) {
			if(i >= num_umts_meas) {
				status = -1;
				break;
			}
			umts_meas[i++] = *it;
		}

		num_umts_meas = new_meas.size();

		if(rms != nullptr)
			*rms = brute_force_->average_rms();

	} catch(const std::exception &err) {
		rf_phreaker::delegate_sink_async::instance().log_error(err.what(), GENERAL_ERROR);
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
		if(!decoder_)
			decoder_.reset(new umts_bch_decoder(config_, bch_decoder_cpich_table_ptr()->cpich_table_ptr()));
		
		// TODO - Make better unique_key.
		umts_meas.layer_3_.unique_sector_key_ = raw_signal.frequency() << 32;
		umts_meas.layer_3_.unique_sector_key_ |= umts_meas.cpich_;

		status = decoder_->process(raw_signal.get_iq().get(), raw_signal.get_iq().length(), umts_meas.cpich_, umts_meas.sample_num_, umts_meas.layer_3_);
	}
	catch(const std::exception &err) {
		rf_phreaker::delegate_sink_async::instance().log_error(err.what(), GENERAL_ERROR);
		std::cout << err.what() << std::endl;
		status = -2;
	}

	return status;
}

int umts_analysis_impl::set_num_coherent_slots_for_psch(int num_coherent_slots)
{
	brute_force_->set_num_coherent_psch_slots_and_reset_iterations(num_coherent_slots);
	return 0;
}

void umts_analysis_impl::cancel_processing()
{
	if(brute_force_.get() != nullptr)
		brute_force_->cancel_processing();
}

const cpich_table_container* umts_analysis_impl::brute_force_cpich_table_ptr()
{
	auto ptr = std::atomic_load(&brute_force_cpich_table_);

	std::atomic_thread_fence(std::memory_order_acquire);
	if(!ptr) {
		std::lock_guard<std::mutex> lock(mutex_);
		ptr = std::atomic_load(&brute_force_cpich_table_);
		if(!ptr) {
			ptr = std::make_shared<cpich_table_container>();
			ptr->generate_resampled_cpich_table(config_.sampling_rate());
			std::atomic_thread_fence(std::memory_order_release);
			std::atomic_store(&brute_force_cpich_table_, ptr);
		}
	}

	return ptr.get();
}

const cpich_table_container* umts_analysis_impl::bch_decoder_cpich_table_ptr()
{
	auto ptr = std::atomic_load(&bch_decoder_cpich_table_);

	std::atomic_thread_fence(std::memory_order_acquire);
	if(!ptr) {
		std::lock_guard<std::mutex> lock(mutex_);
		ptr = std::atomic_load(&bch_decoder_cpich_table_);
		if(!ptr) {
			ptr = std::make_shared<cpich_table_container>();
			ptr->generate_raw_cpich_table();
			std::atomic_thread_fence(std::memory_order_release);
			std::atomic_store(&bch_decoder_cpich_table_, ptr);
		}
	}

	return ptr.get();
}


}