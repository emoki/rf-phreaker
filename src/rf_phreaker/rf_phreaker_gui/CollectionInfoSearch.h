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

private:
	void populateWithGsm();
	void populateWithCdma();
	void populateWithWcdma();
	void populateWithLte();
	void populateWithRaw();
	void populateWithWcdmaFreqRange(const rf_phreaker::channel_freq &cf);
	void populateWithLteFreqRange(const rf_phreaker::channel_freq &cf);

	QList<QObject*> results_;
	QString filter_;
	rf_phreaker::channel_conversion finder_;
	rf_phreaker::frequency_type tmp_freq_;
	rf_phreaker::channel_type tmp_channel_;
};

//}}
