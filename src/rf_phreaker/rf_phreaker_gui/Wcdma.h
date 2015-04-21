#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"

//namespace rf_phreaker { namespace gui {

class Wcdma : public Base {
	Q_OBJECT
	Q_PROPERTY(int uarfcn READ uarfcn NOTIFY uarfcnChanged)
	Q_PROPERTY(QString band READ band NOTIFY bandChanged)
	Q_PROPERTY(int cpich READ cpich NOTIFY cpichChanged)
	Q_PROPERTY(QString ecio READ ecio NOTIFY ecioChanged)
	Q_PROPERTY(QString rscp READ rscp NOTIFY rscpChanged)

public:
	explicit Wcdma(QObject *parent = 0)
		: Base(parent)
	{}
	explicit Wcdma(const rp_wcdma &wcdma, QObject *parent = 0)
		: Base(wcdma.base_, parent)
		, wcdma_(wcdma)
	{}

	~Wcdma() {}

	void copy(const Wcdma &a) {
		Base::copy(a.base_);
		wcdma_.base_ = a.base_;
		if(wcdma_.uarfcn_ != a.wcdma_.uarfcn_) {
			wcdma_.uarfcn_ = a.wcdma_.uarfcn_;
			emit uarfcnChanged();
		}
		if(wcdma_.operating_band_ != a.wcdma_.operating_band_) {
			wcdma_.operating_band_ = a.wcdma_.operating_band_;
			emit bandChanged();
		}
		if(wcdma_.cpich_ != a.wcdma_.cpich_) {
			wcdma_.cpich_ = a.wcdma_.cpich_;
			emit cpichChanged();
		}
		if(wcdma_.ecio_ != a.wcdma_.ecio_) {
			wcdma_.ecio_ = a.wcdma_.ecio_;
			emit ecioChanged();
		}
		if(wcdma_.rscp_ != a.wcdma_.rscp_) {
			wcdma_.rscp_ = a.wcdma_.rscp_;
			emit rscpChanged();
		}
	}

	void copy(const rp_wcdma &a) {
		Base::copy(a.base_);
		wcdma_.base_ = a.base_;
		if(wcdma_.uarfcn_ != a.uarfcn_) {
			wcdma_.uarfcn_ = a.uarfcn_;
			emit uarfcnChanged();
		}
		if(wcdma_.operating_band_ != a.operating_band_) {
			wcdma_.operating_band_ = a.operating_band_;
			emit bandChanged();
		}
		if(wcdma_.cpich_ != a.cpich_) {
			wcdma_.cpich_ = a.cpich_;
			emit cpichChanged();
		}
		if(wcdma_.ecio_ != a.ecio_) {
			wcdma_.ecio_ = a.ecio_;
			emit ecioChanged();
		}
		if(wcdma_.rscp_ != a.rscp_) {
			wcdma_.rscp_ = a.rscp_;
			emit rscpChanged();
		}
	}

	int32_t uarfcn() { return wcdma_.uarfcn_; }
	QString band() { return ApiTypes::toQString(wcdma_.operating_band_); }
	int32_t cpich() { return wcdma_.cpich_; }
	QString ecio() { return QString::number(wcdma_.ecio_, 'f', 1); }
	QString rscp() { return QString::number(wcdma_.rscp_, 'f', 1); }

signals:
	void uarfcnChanged();
	void bandChanged();
	void cpichChanged();
	void ecioChanged();
	void rscpChanged();

public slots:

protected:
	rp_wcdma wcdma_;
};

//}}
