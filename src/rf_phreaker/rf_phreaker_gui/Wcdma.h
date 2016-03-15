#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"
#include "rf_phreaker/common/measurements.h"

//namespace rf_phreaker { namespace gui {

class Wcdma : public Base {
	Q_OBJECT
	Q_PROPERTY(int uarfcn READ uarfcn NOTIFY uarfcnChanged)
	Q_PROPERTY(ApiTypes::OperatingBand band READ band NOTIFY bandChanged)
	Q_PROPERTY(int cpich READ cpich NOTIFY cpichChanged)
	Q_PROPERTY(double ecio READ ecio NOTIFY ecioChanged)
	Q_PROPERTY(double rscp READ rscp NOTIFY rscpChanged)
	Q_PROPERTY(QString bandStr READ bandStr NOTIFY bandChanged)
	Q_PROPERTY(QString ecioStr READ ecioStr NOTIFY ecioChanged)
	Q_PROPERTY(QString rscpStr READ rscpStr NOTIFY rscpChanged)

public:
	explicit Wcdma(QObject *parent = 0)
		: Base(wcdma_, ApiTypes::WCDMA_FULL_SCAN, parent) {
		make_connections();
	}
	explicit Wcdma(const rf_phreaker::umts_data &wcdma, QObject *parent = 0)
		: Base(wcdma_, ApiTypes::WCDMA_FULL_SCAN, parent)
		, wcdma_(wcdma) {
		make_connections();
	}

	~Wcdma() {}

	void make_connections() {
		QObject::connect(this, &Wcdma::bandChanged, this, &Base::cellBandChanged);
		QObject::connect(this, &Wcdma::cpichChanged, this, &Base::cellIdChanged);
		QObject::connect(this, &Wcdma::uarfcnChanged, this, &Base::cellChannelChanged);
		QObject::connect(this, &Wcdma::rscpChanged, this, &Base::cellSignalLevelChanged);
		QObject::connect(this, &Wcdma::ecioChanged, this, &Base::cellInterferenceChanged);
	}

	virtual void update(const rf_phreaker::basic_data &t) {
		Base::update(t);
		const auto &a = (const rf_phreaker::umts_data &)t;
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

	ApiTypes::OperatingBand cellBand() const { return ApiTypes::toOperatingBand(wcdma_.operating_band_); }
	int32_t cellId() const { return wcdma_.cpich_; }
	int32_t cellChannel() const { return wcdma_.uarfcn_; }
	double cellSignalLevel() const { return wcdma_.rscp_; }
	double cellInterference() const { return wcdma_.ecio_; }

	int32_t uarfcn() const { return wcdma_.uarfcn_; }
	int32_t cpich() const { return wcdma_.cpich_; }
	ApiTypes::OperatingBand band() const { return ApiTypes::toOperatingBand(wcdma_.operating_band_); }
	double ecio() const { return wcdma_.ecio_; }
	double rscp() const { return wcdma_.rscp_; }
	QString bandStr() const { return ApiTypes::toQString(wcdma_.operating_band_); }
	QString ecioStr() const { return QString::number(wcdma_.ecio_, 'f', 1); }
	QString rscpStr() const { return QString::number(wcdma_.rscp_, 'f', 1); }
signals:
	void uarfcnChanged();
	void bandChanged();
	void cpichChanged();
	void ecioChanged();
	void rscpChanged();
	void bandStrChanged();
	void ecioStrChanged();
	void rscpStrChanged();

public slots:

protected:
	rf_phreaker::umts_data wcdma_;
};

//}}
