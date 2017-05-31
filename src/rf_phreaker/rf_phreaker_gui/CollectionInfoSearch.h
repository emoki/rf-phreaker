#pragma once
#include <memory>
#include <future>
#include <QObject>
#include "rf_phreaker/common/channel_conversion.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/CollectionInfoList.h"

//namespace rf_phreaker { namespace gui {

class CollectionInfoSearch;
class CollectionInfoSearchSingleton {
public:
	static CollectionInfoSearch& instance() {
		if(!ptr_) {
			std::lock_guard<std::mutex> lock(mutex_);
			if(!ptr_) {
				ptr_ = std::make_unique<CollectionInfoSearch>();
			}
		}
		return *ptr_.get();
	}
	static void destroy() {
		ptr_.reset();
	}
private:
	static std::unique_ptr<CollectionInfoSearch> ptr_;
	static std::mutex mutex_;
};

class CollectionInfoSearcher {
public:
	CollectionInfoSearcher();
	~CollectionInfoSearcher();
	void search(QList<QObject*> &results);



	static rf_phreaker::channel_conversion finder_;
	QString filter_;

	bool searchGsm_;
	bool searchCdma_;
	bool searchWcdma_;
	bool searchLte_;
	bool searchIq_;
	bool searchCw_;
	bool searchSpectrum_;
	bool sweep_;
	bool scan_;

private:
	QList<QObject*> *results_;

	void populateWithGsm();
	void populateWithCdma();
	void populateWithWcdma();
	void populateWithLte();
	void populateWithFreq(ApiTypes::Tech tech, bool isRange);
	void populateWithGsmFreqRange(const rf_phreaker::channel_freq &cf);
	void populateWithWcdmaFreqRange(const rf_phreaker::channel_freq &cf);
	void populateWithLteFreqRange(const rf_phreaker::channel_freq &cf);
	void determineFilters();
	void populateWithBands(rf_phreaker::operating_band begin, rf_phreaker::operating_band end);
	void matchNumbers(const QString &cap, rf_phreaker::frequency_type &freq, int &channel);
	rf_phreaker::frequency_type tmp_freq_a_;
	rf_phreaker::channel_type tmp_channel_a_;
	rf_phreaker::frequency_type tmp_freq_b_;
	rf_phreaker::channel_type tmp_channel_b_;
	bool tmpSearchGsm_;
	bool tmpSearchCdma_;
	bool tmpSearchWcdma_;
	bool tmpSearchLte_;
	bool tmpSearchIq_;
	bool tmpSearchCw_;
	bool tmpSearchSpectrum_;
	bool tmpSweep_;
	bool tmpScan_;
};

class CollectionInfoSearch : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QList<QObject*> results READ results NOTIFY resultsChanged)
	Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY queryChanged)
	Q_PROPERTY(bool searchGsm READ searchGsm WRITE setSearchGsm NOTIFY searchGsmChanged)
	Q_PROPERTY(bool searchCdma READ searchCdma WRITE setSearchCdma NOTIFY searchCdmaChanged)
	Q_PROPERTY(bool searchWcdma READ searchWcdma WRITE setSearchWcdma NOTIFY searchWcdmaChanged)
	Q_PROPERTY(bool searchLte READ searchLte WRITE setSearchLte NOTIFY searchLteChanged)
	Q_PROPERTY(bool searchSpectrum READ searchSpectrum WRITE setSearchSpectrum NOTIFY searchSpectrumChanged)
	Q_PROPERTY(bool searchCw READ searchCw WRITE setSearchCw NOTIFY searchCwChanged)
	Q_PROPERTY(bool searchIq READ searchIq WRITE setSearchIq NOTIFY searchIqChanged)
	Q_PROPERTY(bool sweep READ sweep WRITE setSweep NOTIFY sweepChanged)
	Q_PROPERTY(bool scan READ scan WRITE setScan NOTIFY scanChanged)

signals:
	void resultsChanged();
	void queryChanged();
	void searchGsmChanged();
	void searchCdmaChanged();
	void searchWcdmaChanged();
	void searchLteChanged();
	void searchIqChanged();
	void searchCwChanged();
	void searchSpectrumChanged();
	void sweepChanged();
	void scanChanged();

public:
	explicit CollectionInfoSearch(QObject *parent = 0);
	~CollectionInfoSearch();

	QList<QObject*> results() const{ return results_; }
	Q_INVOKABLE void setResults(QList<QObject*> list) {
		if(results_ != list) {
			results_ = list;
			emit resultsChanged();
		}
	}

	QString filter() const { return searcher_.filter_; }
	void setFilter(QString t) {
		if(t != searcher_.filter_) {
			searcher_.filter_ = t;
			emit queryChanged();
		}
	}

	Q_INVOKABLE void search();

	void setSearchGsm(bool s) {
		if(s != searcher_.searchGsm_) {
			searcher_.searchGsm_ = s;
			emit searchGsmChanged();
		}
	}
	void setSearchCdma(bool s) {
		if(s != searcher_.searchCdma_) {
			searcher_.searchCdma_ = s;
			emit searchCdmaChanged();
		}
	}
	void setSearchWcdma(bool s) {
		if(s != searcher_.searchWcdma_) {
			searcher_.searchWcdma_ = s;
			emit searchWcdmaChanged();
		}
	}
	void setSearchLte(bool s) {
		if(s != searcher_.searchLte_) {
			searcher_.searchLte_ = s;
			emit searchLteChanged();
		}
	}
	void setSearchIq(bool s) {
		if(s != searcher_.searchIq_) {
			searcher_.searchIq_ = s;
			emit searchIqChanged();
		}
	}
	void setSearchCw(bool s) {
		if(s != searcher_.searchCw_) {
			searcher_.searchCw_ = s;
			emit searchCwChanged();
		}
	}
	void setSearchSpectrum(bool s) {
		if(s != searcher_.searchSpectrum_) {
			searcher_.searchSpectrum_ = s;
			emit searchSpectrumChanged();
		}
	}
	void setSweep(bool s) {
		if(s != searcher_.sweep_) {
			searcher_.sweep_ = s;
			emit sweepChanged();
		}
	}
	void setScan(bool s) {
		if(s != searcher_.scan_) {
			searcher_.scan_ = s;
			emit scanChanged();
		}
	}

	bool searchGsm() { return searcher_.searchGsm_; }
	bool searchCdma() { return searcher_.searchCdma_; }
	bool searchWcdma() { return searcher_.searchWcdma_; }
	bool searchLte() { return searcher_.searchLte_; }
	bool searchIq() { return searcher_.searchIq_; }
	bool searchCw() { return searcher_.searchCw_; }
	bool searchSpectrum() { return searcher_.searchSpectrum_; }
	bool sweep() { return searcher_.sweep_; }
	bool scan() { return searcher_.scan_; }

private:
	Q_INVOKABLE void search_(CollectionInfoSearcher s);

	CollectionInfoSearcher searcher_;
	QList<QObject*> results_;
};

//}}
