#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/gsm_layer_3_decoder/gsm_layer_3_decoder.h"
#include "rf_phreaker/rf_phreaker_gui/RawLayer3.h"

//namespace rf_phreaker { namespace gui {

class Gsm : public Base
{
	Q_OBJECT
	Q_PROPERTY(int arfcn READ arfcn NOTIFY arfcnChanged)
	Q_PROPERTY(ApiTypes::OperatingBand band READ band NOTIFY bandChanged)
	Q_PROPERTY(int bsic READ bsic NOTIFY bsicChanged)
	Q_PROPERTY(double ctoi READ ctoi NOTIFY ctoiChanged)
	Q_PROPERTY(double bcchSignalLevel READ bcchSignalLevel NOTIFY bcchSignalLevelChanged)
	Q_PROPERTY(QString bandStr READ bandStr NOTIFY bandChanged)
	Q_PROPERTY(QString ctoiStr READ ctoiStr NOTIFY ctoiChanged)
	Q_PROPERTY(QString bcchSignalLevelStr READ bcchSignalLevelStr NOTIFY bcchSignalLevelChanged)

public:
	explicit Gsm(QObject *parent = 0)
		: Base(gsm_, ApiTypes::GSM_FULL_SCAN, parent) {
		make_connections();
	}
	explicit Gsm(const rf_phreaker::gsm_data &gsm, QObject *parent = 0)
		: Base(gsm_, ApiTypes::GSM_FULL_SCAN, parent)
		, gsm_(gsm) {
		make_connections();
		if(gsm_.layer_3_.raw_layer_3_.size())
			updateLayer3Model(layer3Converter_, gsm_.layer_3_.raw_layer_3_, 0);
	}

	~Gsm() {}

	void make_connections() {
		QObject::connect(this, &Gsm::bandChanged, this, &Base::cellBandChanged);
		QObject::connect(this, &Gsm::bsicChanged, this, &Base::cellIdChanged);
		QObject::connect(this, &Gsm::arfcnChanged, this, &Base::cellChannelChanged);
		QObject::connect(this, &Gsm::bcchSignalLevelChanged, this, &Base::cellSignalLevelChanged);
		QObject::connect(this, &Gsm::ctoiChanged, this, &Base::cellInterferenceChanged);
	}

	virtual void update(const rf_phreaker::basic_data &t) {
		Base::update(t);
		const auto &a = (const rf_phreaker::gsm_data &)t;
		if(gsm_.arfcn_ != a.arfcn_) {
			gsm_.arfcn_ = a.arfcn_;
			emit arfcnChanged();
		}
		if(gsm_.operating_band_ != a.operating_band_) {
			gsm_.operating_band_ = a.operating_band_;
			emit bandChanged();
		}
		if(gsm_.bsic_ != a.bsic_) {
			gsm_.bsic_ = a.bsic_;
			emit bsicChanged();
		}
		if(gsm_.ctoi_ != a.ctoi_) {
			gsm_.ctoi_ = a.ctoi_;
			emit ctoiChanged();
		}
		if(gsm_.cell_signal_level_ != a.cell_signal_level_) {
			gsm_.cell_signal_level_ = a.cell_signal_level_;
			emit bcchSignalLevelChanged();
		}
		if(a.layer_3_.raw_layer_3_.size()) {
			auto &l3 = gsm_.layer_3_.raw_layer_3_;
			auto lsize = l3.size();
			gsm_.layer_3_.update_info(a.layer_3_);
			if(lsize != l3.size())
				updateLayer3Model(layer3Converter_, l3, lsize);
			emit cellLayer3Changed();
		}
	}

	ApiTypes::OperatingBand cellBand() const { return ApiTypes::toOperatingBand(gsm_.operating_band_); }
	int32_t cellId() const { return gsm_.bsic_; }
	int32_t cellChannel() const { return gsm_.arfcn_; }
	double cellSignalLevel() const { return gsm_.cell_signal_level_; }
	double cellInterference() const { return gsm_.ctoi_; }
	virtual QString cellMccStr() const {
		if(gsm_.layer_3_.si_3_.is_decoded())
			return QString(gsm_.layer_3_.si_3_.plmn_.mcc_.to_string());
		else if(gsm_.layer_3_.si_4_.is_decoded())
			return QString(gsm_.layer_3_.si_4_.plmn_.mcc_.to_string());
		else
			return "";
	}
	virtual QString cellMncStr() const {
		if(gsm_.layer_3_.si_3_.is_decoded())
			return QString(gsm_.layer_3_.si_3_.plmn_.mnc_.to_string());
		else if(gsm_.layer_3_.si_4_.is_decoded())
			return QString(gsm_.layer_3_.si_4_.plmn_.mnc_.to_string());
		else
			return "";
	}
	virtual QString cellLacTacStr() const {
		if(gsm_.layer_3_.si_3_.is_decoded())
			return QString::number(gsm_.layer_3_.si_3_.location_area_code_);
		else if(gsm_.layer_3_.si_4_.is_decoded())
			return QString::number(gsm_.layer_3_.si_4_.location_area_code_);
		else
			return "";
	}
	virtual QString cellCidStr() const {
		if(gsm_.layer_3_.si_3_.is_decoded())
			return QString::number(gsm_.layer_3_.si_3_.cell_id_);
		else if(gsm_.layer_3_.si_4_.is_decoded() && gsm_.layer_3_.si_4_.cell_id_ != -1)
			return QString::number(gsm_.layer_3_.si_4_.cell_id_);
		else
			return "";
	}

	int32_t arfcn() const { return gsm_.arfcn_; }
	int32_t bsic() const { return gsm_.bsic_; }
	ApiTypes::OperatingBand band() const { return ApiTypes::toOperatingBand(gsm_.operating_band_); }
	double ctoi() const { return gsm_.ctoi_; }
	double bcchSignalLevel() const { return gsm_.cell_signal_level_; }
	QString bandStr() const { return ApiTypes::toQString(gsm_.operating_band_); }
	QString ctoiStr() const { return QString::number(gsm_.ctoi_, 'f', 1); }
	QString bcchSignalLevelStr() const { return QString::number(gsm_.cell_signal_level_, 'f', 1); }

signals:
	void arfcnChanged();
	void bandChanged();
	void bsicChanged();
	void ctoiChanged();
	void bcchSignalLevelChanged();
	void bandStrChanged();
	void ctoiStrChanged();
	void bcchSignalLevelStrChanged();

private:
	rf_phreaker::gsm_data gsm_;
	RawLayer3<gsm_layer_3_decoder, layer_3_information::gsm_layer_3_message_aggregate> layer3Converter_;
};

//}}
