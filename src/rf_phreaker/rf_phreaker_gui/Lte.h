#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/rf_phreaker_gui/Base.h"

//namespace rf_phreaker { namespace gui {

class Lte : public Base {
	Q_OBJECT
		Q_PROPERTY(int earfcn READ earfcn NOTIFY earfcnChanged)
		Q_PROPERTY(QString band READ band NOTIFY bandChanged)
		Q_PROPERTY(int physicalCellID READ physicalCellID NOTIFY physicalCellIDChanged)
		Q_PROPERTY(QString rsrp READ rsrp NOTIFY rsrpChanged)
		Q_PROPERTY(QString rsrq READ rsrq NOTIFY rsrqChanged)
		Q_PROPERTY(QString rssi READ rssi NOTIFY rssiChanged)
		Q_PROPERTY(int pschID READ pschID NOTIFY pschIDChanged)
		Q_PROPERTY(QString pschQuality READ pschQuality NOTIFY pschQualityChanged)
		Q_PROPERTY(int sschID READ sschID NOTIFY sschIDChanged)
		Q_PROPERTY(QString sschQuality READ sschQuality NOTIFY sschQualityChanged)
		Q_PROPERTY(QString syncQuality READ syncQuality NOTIFY syncQualityChanged)
		Q_PROPERTY(QString cyclicPrefix READ cyclicPrefix NOTIFY cyclicPrefixChanged)
		Q_PROPERTY(int numAntennaPorts READ numAntennaPorts NOTIFY numAntennaPortsChanged)
		Q_PROPERTY(int downlinkBandwidth READ downlinkBandwidth NOTIFY downlinkBandwidthChanged)
		Q_PROPERTY(int frameNumber READ frameNumber NOTIFY frameNumberChanged)
	//	Q_PROPERTY( READ NOTIFY Changed)

public:
	explicit Lte(QObject *parent = 0)
		: Base(parent)
	{}
	explicit Lte(const rp_lte &lte , QObject *parent = 0)
		: Base(lte.base_, parent)
	{}

	~Lte() {}

	void copy(const Lte &a) {
		Base::copy(a.base_);
		lte_.base_ = a.base_;
		if(lte_.earfcn_ != a.lte_.earfcn_) {
			lte_.earfcn_ = a.lte_.earfcn_;
			emit earfcnChanged();
		}
		if(lte_.operating_band_ != a.lte_.operating_band_) {
			lte_.operating_band_ = a.lte_.operating_band_;
			emit bandChanged();
		}
		if(lte_.physical_cell_id_ != a.lte_.physical_cell_id_) {
			lte_.physical_cell_id_ = a.lte_.physical_cell_id_;
			emit physicalCellIDChanged();
		}
		if(lte_.rsrp_ != a.lte_.rsrp_) {
			lte_.rsrp_ = a.lte_.rsrp_;
			emit rsrpChanged();
		}
		if(lte_.rsrq_ != a.lte_.rsrq_) {
			lte_.rsrq_ = a.lte_.rsrq_;
			emit rsrqChanged();
		}
		if(lte_.rssi_ != a.lte_.rssi_) {
			lte_.rssi_ = a.lte_.rssi_;
			emit rssiChanged();
		}
		if(lte_.psch_id_ != a.lte_.psch_id_) {
			lte_.psch_id_ = a.lte_.psch_id_;
			emit pschIDChanged();
		}
		if(lte_.psch_quality_ != a.lte_.psch_quality_) {
			lte_.psch_quality_ = a.lte_.psch_quality_;
			emit pschQualityChanged();
		}
		if(lte_.ssch_id_ != a.lte_.ssch_id_) {
			lte_.ssch_id_ = a.lte_.ssch_id_;
			emit sschIDChanged();
		}
		if(lte_.ssch_quality_ != a.lte_.ssch_quality_) {
			lte_.ssch_quality_ = a.lte_.ssch_quality_;
			emit sschQualityChanged();
		}
		if(lte_.sync_quality_ != a.lte_.sync_quality_) {
			lte_.sync_quality_ = a.lte_.sync_quality_;
			emit syncQualityChanged();
		}
		if(lte_.cyclic_prefix_ != a.lte_.cyclic_prefix_) {
			lte_.cyclic_prefix_ = a.lte_.cyclic_prefix_;
			emit cyclicPrefixChanged();
		}
		if(lte_.num_antenna_ports_ != a.lte_.num_antenna_ports_) {
			lte_.num_antenna_ports_ = a.lte_.num_antenna_ports_;
			emit numAntennaPortsChanged();
		}
		if(lte_.downlink_bandwidth_ != a.lte_.downlink_bandwidth_) {
			lte_.downlink_bandwidth_ = a.lte_.downlink_bandwidth_;
			emit downlinkBandwidthChanged();
		}
		if(lte_.frame_number_ != a.lte_.frame_number_) {
			lte_.frame_number_ = a.lte_.frame_number_;
			emit frameNumberChanged();
		}
	}

	void copy(const rp_lte &a) {
		Base::copy(a.base_);
		lte_.base_ = a.base_;
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
		}
		if(lte_.cyclic_prefix_ != a.cyclic_prefix_) {
			lte_.cyclic_prefix_ = a.cyclic_prefix_;
			emit cyclicPrefixChanged();
		}
		if(lte_.num_antenna_ports_ != a.num_antenna_ports_) {
			lte_.num_antenna_ports_ = a.num_antenna_ports_;
			emit numAntennaPortsChanged();
		}
		if(lte_.downlink_bandwidth_ != a.downlink_bandwidth_) {
			lte_.downlink_bandwidth_ = a.downlink_bandwidth_;
			emit downlinkBandwidthChanged();
		}
		if(lte_.frame_number_ != a.frame_number_) {
			lte_.frame_number_ = a.frame_number_;
			emit frameNumberChanged();
		}
	}

	int32_t earfcn() { return lte_.earfcn_; }
	QString band() { return ApiTypes::toQString(lte_.operating_band_); }
	int32_t physicalCellID() { return lte_.physical_cell_id_; }
	QString rsrp() { return QString::number(lte_.rsrp_, 'f', 1); }
	QString rsrq() { return QString::number(lte_.rsrq_, 'f', 1); }
	QString rssi() { return QString::number(lte_.rssi_, 'f', 1); }
	int32_t pschID() { return lte_.psch_id_; }
	QString pschQuality() { return QString::number(lte_.psch_quality_, 'f', 1); }
	int32_t sschID() { return lte_.ssch_id_; }
	QString sschQuality() { return QString::number(lte_.ssch_quality_, 'f', 1); }
	QString syncQuality() { return QString::number(lte_.sync_quality_, 'f', 1); }
	QString cyclicPrefix() { return lte_.cyclic_prefix_ == 1 ? "Normal" : "Extended"; }
	int numAntennaPorts() { return lte_.num_antenna_ports_; }
	int downlinkBandwidth() { return lte_.downlink_bandwidth_; }
	int frameNumber() { return lte_.frame_number_; }

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
	void cyclicPrefixChanged();
	void numAntennaPortsChanged();
	void downlinkBandwidthChanged();
	void frameNumberChanged();

public slots:

private:
	rp_lte lte_;
};

//}}
