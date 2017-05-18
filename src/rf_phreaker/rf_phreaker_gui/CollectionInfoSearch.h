#pragma once
#include <memory>
#include <QObject>
#include "rf_phreaker/common/channel_conversion.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/CollectionInfoList.h"

//namespace rf_phreaker { namespace gui {

class CollectionInfoSearch : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QList<QObject*> results READ results NOTIFY resultsChanged)
	Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY queryChanged)
	Q_PROPERTY(bool searchIq MEMBER searchIq_ NOTIFY searchIqChanged)
	Q_PROPERTY(bool searchGsm MEMBER searchGsm_ NOTIFY searchGsmChanged)
	Q_PROPERTY(bool searchCdma MEMBER searchCdma_ NOTIFY searchCdmaChanged)
	Q_PROPERTY(bool searchWcdma MEMBER searchWcdma_ NOTIFY searchWcdmaChanged)
	Q_PROPERTY(bool searchLte MEMBER searchLte_ NOTIFY searchLteChanged)
	Q_PROPERTY(bool sweep MEMBER sweep_ NOTIFY sweepChanged)
	Q_PROPERTY(bool scan MEMBER scan_ NOTIFY scanChanged)

public:
	explicit CollectionInfoSearch(QObject *parent = 0);
	~CollectionInfoSearch();

	QList<QObject*> results() const{ return results_; }
	QString filter() const { return filter_; }

	void setFilter(QString t) {
		if(t != filter_) {
			filter_ = t;
			emit queryChanged();
		}
	}

	Q_INVOKABLE void search();

signals:
	void resultsChanged();
	void queryChanged();
	void searchIqChanged();
	void searchGsmChanged();
	void searchCdmaChanged();
	void searchWcdmaChanged();
	void searchLteChanged();
	void sweepChanged();
	void scanChanged();

private:
	void populateWithGsm();
	void populateWithCdma();
	void populateWithWcdma();
	void populateWithLte();
	void populateWithIq();
	void populateWithGsmFreqRange(const rf_phreaker::channel_freq &cf);
	void populateWithWcdmaFreqRange(const rf_phreaker::channel_freq &cf);
	void populateWithLteFreqRange(const rf_phreaker::channel_freq &cf);
	void determineFilters();
	void populateWithBands(rf_phreaker::operating_band begin, rf_phreaker::operating_band end);

	QList<QObject*> results_;
	QString filter_;
	rf_phreaker::channel_conversion finder_;
	rf_phreaker::frequency_type tmp_freq_;
	rf_phreaker::channel_type tmp_channel_;

	bool searchIq_;
	bool searchGsm_;
	bool searchCdma_;
	bool searchWcdma_;
	bool searchLte_;
	bool sweep_;
	bool scan_;
	bool tmpSearchIq_;
	bool tmpSearchGsm_;
	bool tmpSearchCdma_;
	bool tmpSearchWcdma_;
	bool tmpSearchLte_;
	bool tmpSweep_;
	bool tmpScan_;
};

//}}
