#include "rf_phreaker/rf_phreaker_gui/CollectionInfoSearch.h"
#include <functional>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
//namespace rf_phreaker { namespace gui {

using namespace rf_phreaker;

rf_phreaker::channel_conversion CollectionInfoSearcher::finder_;

CollectionInfoSearcher::CollectionInfoSearcher()
	: searchIq_(false)
	, searchCw_(false)
	, searchSpectrum_(false)
	, searchGsm_(false)
	, searchCdma_(false)
	, searchWcdma_(false)
	, searchLte_(false)
	, sweep_(false)
	, scan_(false)
{}

CollectionInfoSearcher::~CollectionInfoSearcher()
{}

void CollectionInfoSearcher::search(QList<QObject*> &results) {
	results_ = &results;
	tmp_freq_a_ = -1; tmp_channel_a_ = -1;
	tmp_freq_b_ = -1; tmp_channel_b_ = -1;

	QRegularExpression regex("([0-9.]+)");
	auto match = regex.globalMatch(filter_);
	if(match.hasNext())
		matchNumbers(match.next().captured(), tmp_freq_a_, tmp_channel_a_);
	if(match.hasNext())
		matchNumbers(match.next().captured(), tmp_freq_b_, tmp_channel_b_);

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
		populateWithFreq(ApiTypes::IQ_DATA, false);
	if(tmpSearchCw_)
		populateWithFreq(ApiTypes::CW, false);
	if(tmpSearchSpectrum_)
		populateWithFreq(ApiTypes::POWER_SPECTRUM, true);
}

void CollectionInfoSearcher::matchNumbers(const QString &cap, frequency_type &freq, int &channel) {
	auto str = cap.toStdString();
	bool ok = false;
	freq = (frequency_type)(cap.toDouble(&ok) * 1e6);
	if(!ok) freq = -1;
	channel = (channel_type)(cap.toInt(&ok));
	if(!ok) channel = -1;
}

void CollectionInfoSearcher::determineFilters() {
	tmpSearchIq_ = searchIq_ | (filter_.indexOf(QRegularExpression("iq", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpSearchSpectrum_ = searchSpectrum_ | (filter_.indexOf(QRegularExpression("spec", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpSearchCw_ = searchCw_ | (filter_.indexOf(QRegularExpression("cw", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpSearchGsm_ = searchGsm_ | (filter_.indexOf(QRegularExpression("gsm", QRegularExpression::CaseInsensitiveOption)) != -1);
	//tmpSearchCdma_ = searchCdma_ | (filter_.indexOf(QRegularExpression("cdma", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpSearchWcdma_ = searchWcdma_ | (filter_.indexOf(QRegularExpression("wcdma", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpSearchLte_ = searchLte_ | (filter_.indexOf(QRegularExpression("lte", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpSweep_ = sweep_ | (filter_.indexOf(QRegularExpression("sweep", QRegularExpression::CaseInsensitiveOption)) != -1)
		| (filter_.indexOf(QRegularExpression("band", QRegularExpression::CaseInsensitiveOption)) != -1);
	tmpScan_ = scan_ | (filter_.indexOf(QRegularExpression("scan", QRegularExpression::CaseInsensitiveOption)) != -1);

	// If no tech filters have been specified then we search all techs.
	if(!tmpSearchGsm_ /*&& !tmpSearchCdma_*/ && !tmpSearchWcdma_ && !tmpSearchLte_ && !tmpSearchIq_ && !tmpSearchSpectrum_ && ! tmpSearchCw_) {
		tmpSearchGsm_ = true;
		//tmpSearchCdma_ = true;
		tmpSearchWcdma_ = true;
		tmpSearchLte_ = true;
		tmpSearchIq_ = true;
		tmpSearchSpectrum_ = true;
		tmpSearchCw_ = true;
	}

	// If neither sweep nor scan has been specified then do both.
	if(!tmpSweep_ && !tmpScan_) {
		tmpSweep_ = true;
		tmpScan_ = true;
	}
}

void CollectionInfoSearcher::populateWithGsm() {
	// Try to treat query as channel.  If successful add it to list.
	if(tmpScan_) {
		auto cfs_a = finder_.arfcn_to_frequency(tmp_channel_a_);
		if(tmp_channel_a_ != -1 && tmp_channel_b_ != -1) {
			auto cfs_b = finder_.arfcn_to_frequency(tmp_channel_b_);
			for(auto cf_a : cfs_a) {
				for(auto cf_b : cfs_b) {
					if(cf_a.is_valid() && cf_b.is_valid() && cf_a.band_ == cf_b.band_) {
						results_->append(new CollectionInfo(cf_a, cf_b, ApiTypes::GSM_FULL_SCAN));
					}
				}
			}
		}
		else {
			for(auto cf_a : cfs_a) {
				if(cf_a.is_valid()) {
					results_->append(new CollectionInfo(cf_a, ApiTypes::GSM_FULL_SCAN));
					if(tmpSweep_)
						populateWithGsmFreqRange(cf_a);
				}
			}
		}
	}

	// Find all possible options if it was a frequency.
	auto ranges_a = finder_.ranges_.find_avaliable_gsm_operating_bands(tmp_freq_a_);
	if(tmp_freq_a_ != -1 && tmp_freq_b_ != -1) {
		auto ranges_b = finder_.ranges_.find_avaliable_gsm_operating_bands(tmp_freq_b_);
		for(auto r_a : ranges_a) {
			auto cf_a = finder_.frequency_to_arfcn(tmp_freq_a_, r_a.band_);
			if(!cf_a.is_valid())
				continue;
			for(auto r_b : ranges_b) {
				auto cf_b = finder_.frequency_to_arfcn(tmp_freq_b_, r_a.band_);
				if(cf_b.is_valid() && cf_a.band_ == cf_b.band_) {
					if(tmpScan_)
						results_->append(new CollectionInfo(cf_a, cf_b, ApiTypes::GSM_FULL_SCAN));
				}
			}
		}
	}
	else {
		for(auto r_a : ranges_a) {
			auto cf_a = finder_.frequency_to_arfcn(tmp_freq_a_, r_a.band_);
			if(cf_a.is_valid()) {
				if(tmpScan_)
					results_->append(new CollectionInfo(cf_a, ApiTypes::GSM_FULL_SCAN));
				if(tmpSweep_)
					populateWithGsmFreqRange(cf_a);
			}
		}
	}
	if(tmp_channel_a_ == -1 && tmp_freq_a_ == -1 && tmpSweep_)
		populateWithBands(rf_phreaker::FIRST_GSM_OPERATING_BAND, rf_phreaker::LAST_GSM_OPERATING_BAND);
}

void CollectionInfoSearcher::populateWithGsmFreqRange(const rf_phreaker::channel_freq &cf) {
	auto r = finder_.ranges_.get_band_freq_range(cf.band_);
	auto cf_low = finder_.frequency_to_arfcn(r.low_freq_hz_, r.band_);
	auto cf_high = finder_.frequency_to_arfcn(r.high_freq_hz_, r.band_);
	results_->append(new CollectionInfo(cf_low, cf_high, ApiTypes::GSM_SWEEP));
}

void CollectionInfoSearcher::populateWithCdma() {
	// TODO - finish CDMA.
}

void CollectionInfoSearcher::populateWithWcdma() {
	if(tmp_freq_b_ != -1 || tmp_channel_b_ != -1)
		return;
	// Try to treat query as channel.  If successful add it to list.
	if(tmpScan_) {
		auto cf = finder_.uarfcn_to_frequency(tmp_channel_a_);
		if(cf.is_valid()) {
			results_->append(new CollectionInfo(cf, ApiTypes::WCDMA_FULL_SCAN));
			if(tmpSweep_)
				populateWithWcdmaFreqRange(cf);
		}
	}
	// Find all possible options if it was a frequency.
	auto ranges = finder_.ranges_.find_avaliable_umts_operating_bands(tmp_freq_a_);
	for(auto r : ranges) {
		auto cf = finder_.frequency_to_uarfcn(tmp_freq_a_, r.band_);
		if(cf.is_valid()) {
			if(tmpScan_)
				results_->append(new CollectionInfo(cf, ApiTypes::WCDMA_FULL_SCAN));
			if(tmpSweep_)
				populateWithWcdmaFreqRange(cf);
		}
	}
	if(tmp_channel_a_ == -1 && tmp_freq_a_ == -1 && tmpSweep_)
		populateWithBands(rf_phreaker::FIRST_UMTS_OPERATING_BAND, rf_phreaker::LAST_UMTS_OPERATING_BAND);
}

void CollectionInfoSearcher::populateWithWcdmaFreqRange(const rf_phreaker::channel_freq &cf) {
	auto r = finder_.ranges_.get_band_freq_range(cf.band_);
	auto cf_low = finder_.frequency_to_uarfcn(r.low_freq_hz_, r.band_);
	auto cf_high = finder_.frequency_to_uarfcn(r.high_freq_hz_, r.band_);
	results_->append(new CollectionInfo(cf_low, cf_high, ApiTypes::WCDMA_SWEEP));
}

void CollectionInfoSearcher::populateWithLte() {
	if(tmp_freq_b_ != -1 || tmp_channel_b_ != -1)
		return;
	// Try to treat query as channel.  If successful add it to list.
	if(tmpScan_) {
		auto cf = finder_.earfcn_to_frequency(tmp_channel_a_);
		if(cf.is_valid()) {
			results_->append(new CollectionInfo(cf, ApiTypes::LTE_FULL_SCAN));
			if(tmpSweep_)
				populateWithLteFreqRange(cf);
		}
	}
	// Find all possible options if it was a frequency.
	auto ranges = finder_.ranges_.find_avaliable_lte_operating_bands(tmp_freq_a_);
	for(auto r : ranges) {
		auto cf = finder_.frequency_to_earfcn(tmp_freq_a_, r.band_);
		if(cf.is_valid()) {
			if(tmpScan_)
				results_->append(new CollectionInfo(cf, ApiTypes::LTE_FULL_SCAN));
			if(tmpSweep_)
				populateWithLteFreqRange(cf);
		}
	}
	if(tmp_channel_a_ == -1 && tmp_freq_a_ == -1 && tmpSweep_)
		populateWithBands(rf_phreaker::FIRST_LTE_OPERATING_BAND, rf_phreaker::LAST_LTE_OPERATING_BAND);
}

void CollectionInfoSearcher::populateWithLteFreqRange(const rf_phreaker::channel_freq &cf) {
	auto r = finder_.ranges_.get_band_freq_range(cf.band_);
	auto cf_low = finder_.frequency_to_earfcn(r.low_freq_hz_, r.band_);
	auto cf_high = finder_.frequency_to_earfcn(r.high_freq_hz_, r.band_);
	results_->append(new CollectionInfo(cf_low, cf_high, ApiTypes::LTE_SWEEP));
}

void CollectionInfoSearcher::populateWithFreq(ApiTypes::Tech tech, bool isRange) {
	if(tmp_freq_a_ > 300e6L && tmp_freq_a_ < 3800e6L) {
		channel_freq cf;
		cf.freq_ = tmp_freq_a_;
		if(!isRange && tmp_freq_b_ == -1)
			results_->append(new CollectionInfo(cf, tech));
		else if(isRange && tmp_freq_b_ > 300e6L && tmp_freq_b_ < 3800e6L) {
			channel_freq cf_b;
			cf_b.freq_ = tmp_freq_b_;
			results_->append(new CollectionInfo(cf, cf_b, tech));
		}
	}
}

void CollectionInfoSearcher::populateWithBands(rf_phreaker::operating_band begin, rf_phreaker::operating_band end) {
	assert(begin <= end);
	auto bands = finder_.ranges_.get_all_operating_bands(begin, end);
	for(const auto &b : bands) {
		auto cf_low = finder_.frequency_to_channel(b.low_freq_hz_, b.band_);
		auto cf_high = finder_.frequency_to_channel(b.high_freq_hz_, b.band_);
		results_->append(new CollectionInfo(cf_low, cf_high, ApiTypes::toTech(b.band_, true)));
	}
}



CollectionInfoSearch::CollectionInfoSearch(QObject *parent)
	: QObject(parent)
{}

CollectionInfoSearch::~CollectionInfoSearch() {}

void CollectionInfoSearch::search() {
	//QMetaObject::invokeMethod(this, "search_",
	//	Qt::QueuedConnection, Q_ARG(CollectionInfoSearcher, searcher_));
	search_(searcher_);
}

void CollectionInfoSearch::search_(CollectionInfoSearcher s) {
	QList<QObject*> list;
	s.search(list);
	setResults(list);
}