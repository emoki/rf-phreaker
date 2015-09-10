#include <atomic>
#include "rf_phreaker/common/raw_signal.h"
#include "rf_phreaker/common/delegate_sink.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/gsm_analysis/gsm_measurement.h"
#include "rf_phreaker/gsm_analysis/gsm_config.h"
#include "rf_phreaker/gsm_analysis/gsm_analysis_interface.h"
#include "rf_phreaker/gsm_layer_3_decoder/gsm_layer_3_decoder.h"

namespace rf_phreaker {

class gsm_analysis_impl {
public:
	gsm_analysis_impl(const gsm_config &config, std::atomic_bool *is_cancelled = nullptr) 
	: processor_(false, config.max_signal_length())
	, config_(config) {
		if(config.sampling_rate() != 4875000)
			throw gsm_analysis_error("GSM sampling rate must be 4.875mhz.");
	}
	
	~gsm_analysis_impl() {}

	int cell_search(const rf_phreaker::raw_signal &raw_signal, gsm_measurements &meas_group) {
		int status = 0;
		try {
			meas_group.clear();
			gsm_analysis_output_list *head = nullptr;

			uint32_t freq_offset = 0;
			if(raw_signal.frequency() % 200000 != 0)
				freq_offset = 100000;

			auto samples_to_process = raw_signal.get_iq().length();
			status = processor_.GsmAnalysis(raw_signal.get_iq().get(), samples_to_process, &head, (float)config_.band_pow(), (float)config_.side_pow(), freq_offset);
			if(status != 0)
				throw gsm_analysis_error(to_string(status));

			auto row = head;
			while(row != nullptr) {
				gsm_measurement meas;
				meas.channel_index_ = row->data.ChannelIndex;
				meas.intermediate_frequency_ = row->data.IFFreq;
				meas.center_frequency_ = raw_signal.frequency() + meas.intermediate_frequency_;
				meas.channel_power_ = sqrt(row->data.ChannelPower);
				meas.fcch_freq_index_ = row->data.FCCH_FreqIndex;
				meas.fcch_peak_freq_ = row->data.FCCH_PeakFreq;
				meas.fcch_peak_power_ = row->data.FCCH_PeakPower;
				meas.band_power_ = row->data.BandPow;
				meas.side_power_ = row->data.SidePow;
				meas.rms_corr_power_ = row->data.RMSCorrPower;
				meas.norm_sync_corr_ = row->data.NormSyncCorr;
				meas.c_i_ratio_ = 10 * log10(row->data.C_I_Ratio);
				meas.sync_sample_num_ = row->data.SyncSampleNum;
				meas.bsic_ = -1; row->data.BSIC;// (row->data.BSIC == 0x99 || row->data.NormSyncCorr < .1) ? -1 : std::stoi(hex_conversion::to_string<2>(row->data.BSIC), 0, 10);
				meas.tdma_frame_number_ = -1;
				meas.sync_burst_decoded_ = (row->data.MeasurementInfo & SyncBurstDecoded) == SyncBurstDecoded;
				meas.cgi_decoded_ = (row->data.MeasurementInfo & CGIDecoded) == CGIDecoded;
				meas.bcch_burst_decoded_ = (row->data.MeasurementInfo & BcchBurstDecoded) == BcchBurstDecoded;
				meas.extended_bcch_burst_decoded_ = (row->data.MeasurementInfo & ExtendedBcchBurstDecoded) == ExtendedBcchBurstDecoded;
				if(meas.bcch_burst_decoded_)
					memcpy(meas.bcch_octets_, row->data.BcchOctets, sizeof(meas.bcch_octets_[0]) * gsm_measurement::bcch_octet_size_);
				else
					memset(meas.bcch_octets_, 0, sizeof(meas.bcch_octets_[0]) * gsm_measurement::bcch_octet_size_);
				if(meas.extended_bcch_burst_decoded_)
					memcpy(meas.extended_bcch_octets_, row->data.ExtendedBcchOctets, sizeof(meas.extended_bcch_octets_[0]) * gsm_measurement::bcch_octet_size_);
				else
					memset(meas.extended_bcch_octets_, 0, sizeof(meas.extended_bcch_octets_[0]) * gsm_measurement::bcch_octet_size_);

				meas_group.push_back(meas);

				row = row->next;
			}

			processor_.GsmClearOutput(head);

		}
		catch(const rf_phreaker_error &err) {
			rf_phreaker::delegate_sink::instance().log_error(err);
			std::cout << err.what() << std::endl;
			status = -1;
		}
		catch(const std::exception &err) {
			delegate_sink::instance().log_error(err.what(), generic_error_type, STD_EXCEPTION_ERROR);
			std::cout << err.what() << std::endl;
			status = -2;
		}

		return status;
	}

	int decode_bsic(const rf_phreaker::raw_signal &raw_signal, gsm_measurement &meas) {
		int status = 0;
		try {
			auto samples_to_process = raw_signal.get_iq().length();
			status = processor_.DecodeBsic(raw_signal.get_iq().get(), samples_to_process, meas);
			if(status != 0)
				throw gsm_analysis_error(to_string(status));

			meas.bsic_ = (meas.bsic_ == -1 || meas.bsic_ == 0x99 || meas.norm_sync_corr_ < .1) ? -1 : std::stoi(hex_conversion::to_string<2>(meas.bsic_), 0, 10);
			if(meas.bsic_ == -1)
				meas.tdma_frame_number_ = -1;
		}
		catch(const rf_phreaker_error &err) {
			rf_phreaker::delegate_sink::instance().log_error(err);
			std::cout << err.what() << std::endl;
			status = -1;
		}
		catch(const std::exception &err) {
			delegate_sink::instance().log_error(err.what(), generic_error_type, STD_EXCEPTION_ERROR);
			std::cout << err.what() << std::endl;
			status = -2;
		}

		return status;
	}

	int decode_bcch_bursts(const rf_phreaker::raw_signal &raw_signal, gsm_measurement &meas) {
		int status = 0;
		try {
			auto samples_to_process = raw_signal.get_iq().length();
			status = processor_.DecodeBcchBurst(raw_signal.get_iq().get(), samples_to_process, meas);
			if(status != 0)
				throw gsm_analysis_error(to_string(status));
		}
		catch(const rf_phreaker_error &err) {
			rf_phreaker::delegate_sink::instance().log_error(err);
			std::cout << err.what() << std::endl;
			status = -1;
		}
		catch(const std::exception &err) {
			delegate_sink::instance().log_error(err.what(), generic_error_type, STD_EXCEPTION_ERROR);
			std::cout << err.what() << std::endl;
			status = -2;
		}

		return status;
	}

	int decode_layer_3(gsm_measurement &meas) {
		int status = 0;
		try {
			meas.layer_3_.clear();
			if(meas.bcch_burst_decoded_)
				decoder_.decode_bcch_message(meas.bcch_octets_, meas.bcch_octet_size_, 0, meas.layer_3_);
			if(meas.extended_bcch_burst_decoded_)
				decoder_.decode_bcch_message(meas.extended_bcch_octets_, meas.bcch_octet_size_, 0, meas.layer_3_);
		}
		catch(const rf_phreaker_error &err) {
			rf_phreaker::delegate_sink::instance().log_error(err);
			std::cout << err.what() << std::endl;
			status = -1;
		}
		catch(const std::exception &err) {
			delegate_sink::instance().log_error(err.what(), generic_error_type, STD_EXCEPTION_ERROR);
			std::cout << err.what() << std::endl;
			status = -2;
		}

		return status;
	}

	std::string to_string(int error) {
		switch(error) {
			case GSM_ANALYSIS_NO_ERROR:
				return "no gsm analysis error";
			case GSM_INIT_OUT_OF_MEMORY:
			return "gsm analysis out of memory";
			case GSM_ANALYSIS_NOT_INITIALIZED:
			return "gsm analysis not initialized";
			case GSM_ANALYSIS_WIN_ALLOC_ERROR:
			return "gsm analysis windows allocation error";
			case GSM_ANALYSIS_ADD_ROW_ERROR:
			return "gsm analysis row allocation error";
			case GSM_ANALYSIS_SYNC_MEMORY_ALLOC:
			return "gsm analysis sync allocation error";
			case GSM_ANALYSIS_SYNC_LPF_ERROR:
			return "gsm analysis sync lpf error";
			case GSM_ANALYSIS_CGI_INIT_ERROR:
			return "gsm analysis cgi initialization error";
			case GSM_UNDEFINED_ERROR:
			return "gsm analysis undefined error";
			case GSM_FCCH_UNDEFINED_ERROR:
			return "gsm analysis fcch undefined error";
			case GSM_SYNC_UNDEFINED_ERROR:
			return "gsm analysis sync undefined error";
			case GSM_INIT_ALREADY_INITIALIZED:
			return "gsm analysis already initialized";
			case GSM_INIT_ERROR_READING_TEMPLATES:
			return "gsm analysis reading templates error";
			case GSM_INIT_ERROR_READING_WIN_COEFFS:
			return "gsm analysis reading window coefficients error";
			case GSM_ANALYSIS_DATASIZE_ERROR:
			return "gsm analysis datasize error";
			case GSM_ANALYSIS_NULL_INPUT:
			return "gsm analysis null input error";
			case GSM_ANALYSIS_BSIC_INIT_ERROR:
			return "gsm analysis bsic initialization error";
			case GSM_DEBUG_FILES_DIRECTORY_ERROR:
			return "gsm analysis directory error";
		default:
			return "unknown gsm analysis error";
		}
	}
private:
	gsm_layer_3_decoder decoder_;
	gsm_processor processor_;
	gsm_config config_;
};

}