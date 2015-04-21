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
	// TODO - finish GSM.
}

void CollectionInfoSearch::populateWithCdma() {
	// TODO - finish CDMA.
}

void CollectionInfoSearch::populateWithWcdma() {
	// Try to treat query as channel.  If successful add it to list.
	auto cf = finder_.uarfcn_to_frequency(tmp_channel_);
	if(cf.is_valid())
		results_.append(new CollectionInfo(cf, ApiTypes::WCDMA));

	// Find all possible options if it was a frequency.
	auto ranges = finder_.ranges_.find_avaliable_umts_operating_bands(tmp_freq_);
	for(auto r : ranges) {
		auto cf = finder_.frequency_to_uarfcn(tmp_freq_, r.band_);
		if(cf.is_valid())
			results_.append(new CollectionInfo(cf, ApiTypes::WCDMA));
	}
}

void CollectionInfoSearch::populateWithLte() {
	// Try to treat query as channel.  If successful add it to list.
	auto cf = finder_.earfcn_to_frequency(tmp_channel_);
	if(cf.is_valid())
		results_.append(new CollectionInfo(cf, ApiTypes::LTE));

	// Find all possible options if it was a frequency.
	auto ranges = finder_.ranges_.find_avaliable_lte_operating_bands(tmp_freq_);
	for(auto r : ranges) {
		auto cf = finder_.frequency_to_earfcn(tmp_freq_, r.band_);
		if(cf.is_valid())
			results_.append(new CollectionInfo(cf, ApiTypes::LTE));
	}
}

void CollectionInfoSearch::populateWithRaw() {
	if(tmp_freq_ > 300e6 && tmp_freq_ < 3800e6) {
		channel_freq cf;
		cf.freq_ = tmp_freq_;
		results_.append(new CollectionInfo(cf, ApiTypes::RAW_DATA));
	}
}
