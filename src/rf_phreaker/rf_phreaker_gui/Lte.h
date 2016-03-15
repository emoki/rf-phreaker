#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"
#include "rf_phreaker/common/measurements.h"

//namespace rf_phreaker { namespace gui {

class Lte : public Base {
	Q_OBJECT
		Q_PROPERTY(int earfcn READ earfcn NOTIFY earfcnChanged)
		Q_PROPERTY(QString band READ band NOTIFY bandChanged)
		Q_PROPERTY(int physicalCellID READ physicalCellID NOTIFY physicalCellIDChanged)
		Q_PROPERTY(double rsrp READ rsrp NOTIFY rsrpChanged)
		Q_PROPERTY(double rsrq READ rsrq NOTIFY rsrqChanged)
		Q_PROPERTY(double rssi READ rssi NOTIFY rssiChanged)
		Q_PROPERTY(int pschID READ pschID NOTIFY pschIDChanged)
		Q_PROPERTY(double pschQuality READ pschQuality NOTIFY pschQualityChanged)
		Q_PROPERTY(double sschQuality READ sschQuality NOTIFY sschQualityChanged)
		Q_PROPERTY(double syncQuality READ syncQuality NOTIFY syncQualityChanged)
		Q_PROPERTY(double syncSignalLevel READ syncSignalLevel NOTIFY syncSignalLevelChanged)
		Q_PROPERTY(int sschID READ sschID NOTIFY sschIDChanged)
		Q_PROPERTY(int numAntennaPorts READ numAntennaPorts NOTIFY numAntennaPortsChanged)
		Q_PROPERTY(int downlinkBandwidth READ downlinkBandwidth NOTIFY downlinkBandwidthChanged)
		Q_PROPERTY(int frameNumber READ frameNumber NOTIFY frameNumberChanged)
		Q_PROPERTY(QString bandStr READ bandStr NOTIFY bandChanged)
		Q_PROPERTY(QString rsrpStr READ rsrpStr NOTIFY rsrpChanged)
		Q_PROPERTY(QString rsrqStr READ rsrqStr NOTIFY rsrqChanged)
		Q_PROPERTY(QString rssiStr READ rssiStr NOTIFY rssiChanged)
		Q_PROPERTY(QString pschQualityStr READ pschQualityStr NOTIFY pschQualityChanged)
		Q_PROPERTY(QString sschQualityStr READ sschQualityStr NOTIFY sschQualityChanged)
		Q_PROPERTY(QString syncQualityStr READ syncQualityStr NOTIFY syncQualityChanged)
		Q_PROPERTY(QString syncSignalLevelStr READ syncSignalLevelStr NOTIFY syncSignalLevelChanged)
		Q_PROPERTY(QString cyclicPrefixStr READ cyclicPrefixStr NOTIFY cyclicPrefixChanged)
	//	Q_PROPERTY( READ NOTIFY Changed)

public:
	explicit Lte(QObject *parent = 0)
		: Base(lte_, ApiTypes::LTE_FULL_SCAN, parent) {
		make_connections();
	}
	explicit Lte(const rf_phreaker::lte_data &lte, QObject *parent = 0)
		: Base(lte_, ApiTypes::LTE_FULL_SCAN, parent)
		, lte_(lte) {
		make_connections();
	}

	~Lte() {}

	void make_connections() {
		QObject::connect(this, &Lte::bandChanged, this, &Base::cellBandChanged);
		QObject::connect(this, &Lte::physicalCellIDChanged, this, &Base::cellIdChanged);
		QObject::connect(this, &Lte::earfcnChanged, this, &Base::cellChannelChanged);
		QObject::connect(this, &Lte::syncSignalLevelChanged, this, &Base::cellSignalLevelChanged);
		QObject::connect(this, &Lte::syncQualityChanged, this, &Base::cellInterferenceChanged);

		QObject::connect(this, &Lte::syncQualityChanged, this, &Lte::syncSignalLevelChanged);
		QObject::connect(this, &Base::carrierSignalLevelChanged, this, &Lte::syncSignalLevelChanged);
	}

	void update(const rf_phreaker::basic_data &t) {
		Base::update(t);
		const auto &a = (const rf_phreaker::lte_data &)t;
		if(lte_.earfcn_ != a.earfcn_) {
			lte_.earfcn_ = a.earfcn_;
			emit earfcnChanged();
		}
		if(lte_.operating_band_ != a.operating_band_) {
			lte_.operating_band_ = a.operating_band_;
			emit bandChanged();
		}
		if(lte_.physical_cell_id_ != a.physical_cell_id_) {
			lte_.physical_cell_id_ = a.physical_cell_id_;
			emit physicalCellIDChanged();
		}
		if(lte_.rsrp_ != a.rsrp_) {
			lte_.rsrp_ = a.rsrp_;
			emit rsrpChanged();
		}
		if(lte_.rsrq_ != a.rsrq_) {
			lte_.rsrq_ = a.rsrq_;
			emit rsrqChanged();
		}
		if(lte_.rssi_ != a.rssi_) {
			lte_.rssi_ = a.rssi_;
			emit rssiChanged();
		}
		if(lte_.psch_id_ != a.psch_id_) {
			lte_.psch_id_ = a.psch_id_;
			emit pschIDChanged();
		}
		if(lte_.psch_quality_ != a.psch_quality_) {
			lte_.psch_quality_ = a.psch_quality_;
			emit pschQualityChanged();
		}
		if(lte_.ssch_id_ != a.ssch_id_) {
			lte_.ssch_id_ = a.ssch_id_;
			emit sschIDChanged();
		}
		if(lte_.ssch_quality_ != a.ssch_quality_) {
			lte_.ssch_quality_ = a.ssch_quality_;
			emit sschQualityChanged();
		}
		if(lte_.sync_quality_ != a.sync_quality_) {
			lte_.sync_quality_ = a.sync_quality_;
			emit syncQualityChanged();
			//emit syncSignalLevelChanged();
		}
		if(lte_.cyclic_prefix_ != a.cyclic_prefix_) {
			lte_.cyclic_prefix_ = a.cyclic_prefix_;
			emit cyclicPrefixChanged();
		}
		if(lte_.num_antenna_ports_ != a.num_antenna_ports_) {
			lte_.num_antenna_ports_ = a.num_antenna_ports_;
			emit numAntennaPortsChanged();
		}
		if(lte_.dl_bandwidth_ != a.dl_bandwidth_) {
			lte_.dl_bandwidth_ = a.dl_bandwidth_;
			emit downlinkBandwidthChanged();
		}
		if(lte_.frame_number_ != a.frame_number_) {
			lte_.frame_number_ = a.frame_number_;
			emit frameNumberChanged();
		}
	}

	ApiTypes::OperatingBand cellBand() const { return ApiTypes::toOperatingBand(lte_.operating_band_); }
	int32_t cellId() const { return lte_.physical_cell_id_; }
	int32_t cellChannel() const { return lte_.earfcn_; }
	double cellSignalLevel() const { return syncSignalLevel(); }
	double cellInterference() const { return lte_.sync_quality_; }

	int32_t earfcn() const { return lte_.earfcn_; }
	ApiTypes::OperatingBand band() const { return ApiTypes::toOperatingBand(lte_.operating_band_); }
	int32_t physicalCellID() const { return lte_.physical_cell_id_; }
	double rsrp() const { return lte_.rsrp_; }
	double rsrq() const { return lte_.rsrq_; }
	double rssi() const { return lte_.rssi_; }
	int32_t pschID() const { return lte_.psch_id_; }
	double pschQuality() const { return lte_.psch_quality_; }
	int32_t sschID() const { return lte_.ssch_id_; }
	double sschQuality() const { return lte_.ssch_quality_; }
	double syncQuality() const { return lte_.sync_quality_; }
	double syncSignalLevel() const { return lte_.carrier_signal_level_ + lte_.sync_quality_; }
	int numAntennaPorts() const { return lte_.num_antenna_ports_; }
	int downlinkBandwidth() const { return lte_.dl_bandwidth_; }
	int frameNumber() const { return lte_.frame_number_; }

	QString bandStr() const { return ApiTypes::toQString(lte_.operating_band_); }
	QString rsrpStr() const { return QString::number(lte_.rsrp_, 'f', 1); }
	QString rsrqStr() const { return QString::number(lte_.rsrq_, 'f', 1); }
	QString rssiStr() const { return QString::number(lte_.rssi_, 'f', 1); }
	QString pschQualityStr() const { return QString::number(lte_.psch_quality_, 'f', 1); }
	QString sschQualityStr() const { return QString::number(lte_.ssch_quality_, 'f', 1); }
	QString syncQualityStr() const { return QString::number(lte_.sync_quality_, 'f', 1); }
	QString syncSignalLevelStr() const { return QString::number(lte_.carrier_signal_level_ + lte_.sync_quality_, 'f', 1); }
	QString cyclicPrefixStr() const { return lte_.cyclic_prefix_ == 1 ? "Normal" : "Extended"; }

signals:
	void earfcnChanged();
	void bandChanged();
	void physicalCellIDChanged();
	void rsrpChanged();
	void rsrqChanged();
	void rssiChanged();
	void pschIDChanged();
	void pschQualityChanged();
	void sschIDChanged();
	void sschQualityChanged();
	void syncQualityChanged();
	void syncSignalLevelChanged();
	void cyclicPrefixChanged();
	void numAntennaPortsChanged();
	void downlinkBandwidthChanged();
	void frameNumberChanged();

public slots:

private:
	rf_phreaker::lte_data lte_;
};

//}}
