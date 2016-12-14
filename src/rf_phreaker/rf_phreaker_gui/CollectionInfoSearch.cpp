#include "rf_phreaker/rf_phreaker_gui/CollectionInfoSearch.h"

//namespace rf_phreaker { namespace gui {

using namespace rf_phreaker;

CollectionInfoSearch::CollectionInfoSearch(QObject *parent)
	: QObject(parent)
{}

CollectionInfoSearch::~CollectionInfoSearch()
{}

void CollectionInfoSearch::search() {
	results_.clear();
	bool ok = false;

	tmp_freq_ = (frequency_type)(filter_.toDouble(&ok) * 1e6);
	if(!ok)
		tmp_freq_ = -1;

	tmp_channel_ = (channel_type)(filter_.toInt(&ok));
	if(!ok)
		tmp_channel_ = -1;

	// Populate results with different technologies.
	populateWithGsm();
	populateWithCdma();
	populateWithWcdma();
	populateWithLte();
	populateWithRaw();

	emit resultsChanged();
}

void CollectionInfoSearch::populateWithGsm() {
	// Try to treat query as channel.  If successful add it to list.
	auto cfs = finder_.arfcn_to_frequency(tmp_channel_);
	if(cfs.size()) {
		for(auto cf : cfs)
		if(cf.is_valid()) {
			results_.append(new CollectionInfo(cf, ApiTypes::GSM_FULL_SCAN));
			populateWithGsmFreqRange(cf);
		}
	}
	// Find all possible options if it was a frequency.
	auto ranges = finder_.ranges_.find_avaliable_gsm_operating_bands(tmp_freq_);
	for(auto r : ranges) {
		auto cf = finder_.frequency_to_arfcn(tmp_freq_, r.band_);
		if(cf.is_valid()) {
			results_.append(new CollectionInfo(cf, ApiTypes::GSM_FULL_SCAN));
			populateWithGsmFreqRange(cf);
		}
	}
}

void CollectionInfoSearch::populateWithGsmFreqRange(const rf_phreaker::channel_freq &cf) {
	auto r = finder_.ranges_.get_band_freq_range(cf.band_);
	auto cf_low = finder_.frequency_to_arfcn(r.low_freq_hz_, r.band_);
	auto cf_high = finder_.frequency_to_arfcn(r.high_freq_hz_, r.band_);
	results_.append(new CollectionInfo(cf_low, cf_high, ApiTypes::GSM_SWEEP));
}

void CollectionInfoSearch::populateWithCdma() {
	// TODO - finish CDMA.
}

void CollectionInfoSearch::populateWithWcdma() {
	// Try to treat query as channel.  If successful add it to list.
	auto cf = finder_.uarfcn_to_frequency(tmp_channel_);
	if(cf.is_valid()) {
		results_.append(new CollectionInfo(cf, ApiTypes::WCDMA_FULL_SCAN));
		populateWithWcdmaFreqRange(cf);
	}
	// Find all possible options if it was a frequency.
	auto ranges = finder_.ranges_.find_avaliable_umts_operating_bands(tmp_freq_);
	for(auto r : ranges) {
		auto cf = finder_.frequency_to_uarfcn(tmp_freq_, r.band_);
		if(cf.is_valid()) {
			results_.append(new CollectionInfo(cf, ApiTypes::WCDMA_FULL_SCAN));
			populateWithWcdmaFreqRange(cf);
		}
	}
}

void CollectionInfoSearch::populateWithWcdmaFreqRange(const rf_phreaker::channel_freq &cf) {
	auto r = finder_.ranges_.get_band_freq_range(cf.band_);
	auto cf_low = finder_.frequency_to_uarfcn(r.low_freq_hz_, r.band_);
	auto cf_high = finder_.frequency_to_uarfcn(r.high_freq_hz_, r.band_);
	results_.append(new CollectionInfo(cf_low, cf_high, ApiTypes::WCDMA_SWEEP));
}

void CollectionInfoSearch::populateWithLte() {
	// Try to treat query as channel.  If successful add it to list.
	auto cf = finder_.earfcn_to_frequency(tmp_channel_);
	if(cf.is_valid()) {
		results_.append(new CollectionInfo(cf, ApiTypes::LTE_FULL_SCAN));
		populateWithLteFreqRange(cf);
	}
	// Find all possible options if it was a frequency.
	auto ranges = finder_.ranges_.find_avaliable_lte_operating_bands(tmp_freq_);
	for(auto r : ranges) {
		auto cf = finder_.frequency_to_earfcn(tmp_freq_, r.band_);
		if(cf.is_valid()) {
			results_.append(new CollectionInfo(cf, ApiTypes::LTE_FULL_SCAN));
			populateWithLteFreqRange(cf);
		}
	}
}

void CollectionInfoSearch::populateWithLteFreqRange(const rf_phreaker::channel_freq &cf) {
	auto r = finder_.ranges_.get_band_freq_range(cf.band_);
	auto cf_low = finder_.frequency_to_earfcn(r.low_freq_hz_, r.band_);
	auto cf_high = finder_.frequency_to_earfcn(r.high_freq_hz_, r.band_);
	results_.append(new CollectionInfo(cf_low, cf_high, ApiTypes::LTE_SWEEP));
}

void CollectionInfoSearch::populateWithRaw() {
	if(tmp_freq_ > 300e6 && tmp_freq_ < 3800e6) {
		channel_freq cf;
		cf.freq_ = tmp_freq_;
		results_.append(new CollectionInfo(cf, ApiTypes::RAW_DATA));
	}
}
