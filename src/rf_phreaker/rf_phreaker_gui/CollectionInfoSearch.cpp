#include "rf_phreaker/rf_phreaker_gui/CollectionInfoSearch.h"
#include <QRegularExpression>
//namespace rf_phreaker { namespace gui {

using namespace rf_phreaker;

CollectionInfoSearch::CollectionInfoSearch(QObject *parent)
	: QObject(parent)
	, searchIq_(false)
	, searchGsm_(false)
	, searchCdma_(false)
	, searchWcdma_(false)
	, searchLte_(false)
	, sweep_(false)
	, scan_(false)
{}

CollectionInfoSearch::~CollectionInfoSearch()
{}

void CollectionInfoSearch::search() {
	results_.clear();

	auto numOnly = filter_;
	numOnly.remove(QRegularExpression("[a-zA-z]"));
	std::string tmp = numOnly.toStdString();
	bool ok = false;
	tmp_freq_ = (frequency_type)(numOnly.toDouble(&ok) * 1e6);
	if(!ok)
		tmp_freq_ = -1;
	tmp_channel_ = (channel_type)(numOnly.toInt(&ok));
	if(!ok)
		tmp_channel_ = -1;

	determineFilters();

	// Populate results with different technologies.
	if(tmpSearchGsm_)
		populateWithGsm();
	//if(tmpSearchCdma)
	//	populateWithCdma();
	if(tmpSearchWcdma_)
		populateWithWcdma();
	if(tmpSearchLte_)
		populateWithLte();
	if(tmpSearchIq_)
		populateWithIq();
		
	emit resultsChanged();
}

void CollectionInfoSearch::determineFilters() {
	tmpSearchIq_ = searchIq_ | (filter_.indexOf(QRegularExpression("raw", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpSearchGsm_ = searchGsm_ | (filter_.indexOf(QRegularExpression("gsm", QRegularExpression::CaseInsensitiveOption)) != -1);
	//tmpSearchCdma_ = searchCdma_ | (filter_.indexOf(QRegularExpression("cdma", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpSearchWcdma_ = searchWcdma_ | (filter_.indexOf(QRegularExpression("wcdma", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpSearchLte_ = searchLte_ | (filter_.indexOf(QRegularExpression("lte", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpSweep_ = sweep_ | (filter_.indexOf(QRegularExpression("sweep", QRegularExpression::CaseInsensitiveOption)) != -1) 
		| (filter_.indexOf(QRegularExpression("band", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpScan_ = scan_ | (filter_.indexOf(QRegularExpression("scan", QRegularExpression::CaseInsensitiveOption)) != -1);

	// If no tech filters have been specified then we search all techs.
	if(!tmpSearchGsm_ /*&& !tmpSearchCdma_*/ && !tmpSearchWcdma_ && !tmpSearchLte_ && !tmpSearchIq_) {
		tmpSearchGsm_ = true;
		//tmpSearchCdma_ = true;
		tmpSearchWcdma_ = true;
		tmpSearchLte_ = true;
		tmpSearchIq_ = true;
	}

	// If neither sweep nor scan has been specified then do both.
	if(!tmpSweep_ && !tmpScan_) {
		tmpSweep_ = true;
		tmpScan_ = true;
	}
}

void CollectionInfoSearch::populateWithGsm() {
	// Try to treat query as channel.  If successful add it to list.
	if(tmpScan_) {
		auto cfs = finder_.arfcn_to_frequency(tmp_channel_);
		if(cfs.size()) {
			for(auto cf : cfs) {
				if(cf.is_valid()) {
					results_.append(new CollectionInfo(cf, ApiTypes::GSM_FULL_SCAN));
					if(tmpSweep_)
						populateWithGsmFreqRange(cf);
				}
			}
		}
	}
	// Find all possible options if it was a frequency.
	auto ranges = finder_.ranges_.find_avaliable_gsm_operating_bands(tmp_freq_);
	for(auto r : ranges) {
		auto cf = finder_.frequency_to_arfcn(tmp_freq_, r.band_);
		if(cf.is_valid()) {
			if(tmpScan_)
				results_.append(new CollectionInfo(cf, ApiTypes::GSM_FULL_SCAN));
			if(tmpSweep_)
				populateWithGsmFreqRange(cf);
		}
	}
	if(tmp_channel_ == -1 && tmp_freq_ == -1 && tmpSweep_)
		populateWithBands(rf_phreaker::FIRST_GSM_OPERATING_BAND, rf_phreaker::LAST_GSM_OPERATING_BAND);
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
	if(tmpScan_) {
		auto cf = finder_.uarfcn_to_frequency(tmp_channel_);
		if(cf.is_valid()) {
			results_.append(new CollectionInfo(cf, ApiTypes::WCDMA_FULL_SCAN));
			if(tmpSweep_)
				populateWithWcdmaFreqRange(cf);
		}
	}
	// Find all possible options if it was a frequency.
	auto ranges = finder_.ranges_.find_avaliable_umts_operating_bands(tmp_freq_);
	for(auto r : ranges) {
		auto cf = finder_.frequency_to_uarfcn(tmp_freq_, r.band_);
		if(cf.is_valid()) {
			if(tmpScan_)
				results_.append(new CollectionInfo(cf, ApiTypes::WCDMA_FULL_SCAN));
			if(tmpSweep_)
				populateWithWcdmaFreqRange(cf);
		}
	}
	if(tmp_channel_ == -1 && tmp_freq_ == -1 && tmpSweep_)
		populateWithBands(rf_phreaker::FIRST_UMTS_OPERATING_BAND, rf_phreaker::LAST_UMTS_OPERATING_BAND);
}

void CollectionInfoSearch::populateWithWcdmaFreqRange(const rf_phreaker::channel_freq &cf) {
	auto r = finder_.ranges_.get_band_freq_range(cf.band_);
	auto cf_low = finder_.frequency_to_uarfcn(r.low_freq_hz_, r.band_);
	auto cf_high = finder_.frequency_to_uarfcn(r.high_freq_hz_, r.band_);
	results_.append(new CollectionInfo(cf_low, cf_high, ApiTypes::WCDMA_SWEEP));
}

void CollectionInfoSearch::populateWithLte() {
	// Try to treat query as channel.  If successful add it to list.
	if(tmpScan_) {
		auto cf = finder_.earfcn_to_frequency(tmp_channel_);
		if(cf.is_valid()) {
			results_.append(new CollectionInfo(cf, ApiTypes::LTE_FULL_SCAN));
			if(tmpSweep_)
				populateWithLteFreqRange(cf);
		}
	}
	// Find all possible options if it was a frequency.
	auto ranges = finder_.ranges_.find_avaliable_lte_operating_bands(tmp_freq_);
	for(auto r : ranges) {
		auto cf = finder_.frequency_to_earfcn(tmp_freq_, r.band_);
		if(cf.is_valid()) {
			if(tmpScan_)
				results_.append(new CollectionInfo(cf, ApiTypes::LTE_FULL_SCAN));
			if(tmpSweep_)
				populateWithLteFreqRange(cf);
		}
	}
	if(tmp_channel_ == -1 && tmp_freq_ == -1 && tmpSweep_)
		populateWithBands(rf_phreaker::FIRST_LTE_OPERATING_BAND, rf_phreaker::LAST_LTE_OPERATING_BAND);
}

void CollectionInfoSearch::populateWithLteFreqRange(const rf_phreaker::channel_freq &cf) {
	auto r = finder_.ranges_.get_band_freq_range(cf.band_);
	auto cf_low = finder_.frequency_to_earfcn(r.low_freq_hz_, r.band_);
	auto cf_high = finder_.frequency_to_earfcn(r.high_freq_hz_, r.band_);
	results_.append(new CollectionInfo(cf_low, cf_high, ApiTypes::LTE_SWEEP));
}

void CollectionInfoSearch::populateWithIq() {
	if(tmp_freq_ > 300e6 && tmp_freq_ < 3800e6) {
		channel_freq cf;
		cf.freq_ = tmp_freq_;
		results_.append(new CollectionInfo(cf, ApiTypes::IQ_DATA));
	}
}

void CollectionInfoSearch::populateWithBands(rf_phreaker::operating_band begin, rf_phreaker::operating_band end) {
	assert(begin <= end);
	auto bands = finder_.ranges_.get_all_operating_bands(begin, end);
	for(const auto &b : bands) {
		auto cf_low = finder_.frequency_to_channel(b.low_freq_hz_, b.band_);
		auto cf_high = finder_.frequency_to_channel(b.high_freq_hz_, b.band_);
		results_.append(new CollectionInfo(cf_low, cf_high, ApiTypes::toTech(b.band_, true)));
	}
}