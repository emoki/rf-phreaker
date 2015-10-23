#pragma once
#include <QObject>
#include <QDateTime>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"

//namespace rf_phreaker { namespace gui {

class Device : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString serial READ serial NOTIFY serialChanged)
	Q_PROPERTY(QString serialShort READ serialShort NOTIFY serialChanged)
	Q_PROPERTY(ApiTypes::DeviceCommunication deviceCommunication READ deviceCommunication NOTIFY deviceCommunicationChanged)
	Q_PROPERTY(QString deviceCommunicationStr READ deviceCommunicationStr NOTIFY deviceCommunicationChanged)
	Q_PROPERTY(QDate freqCorrectionDate READ freqCorrectionDate NOTIFY freqCorrectionDateChanged)
	Q_PROPERTY(QString freqCorrectionDateStr READ freqCorrectionDateStr NOTIFY freqCorrectionDateChanged)
	Q_PROPERTY(QDate rfCalibrationDate READ rfCalibrationDate NOTIFY rfCalibrationDateChanged)
	Q_PROPERTY(QString rfCalibrationDateStr READ rfCalibrationDateStr NOTIFY rfCalibrationDateChanged)
	Q_PROPERTY(QStringList calibratedFreqList READ calibratedFreqList NOTIFY calibratedFreqListChanged)
	Q_PROPERTY(QList<QObject*> licenseList READ licenseList NOTIFY licenseListChanged)
	//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
	//	Q_PROPERTY( READ WRITE set NOTIFY Changed)

public:
	explicit Device(QObject *parent = 0)
		:QObject(parent)
	{
		memset(device_.serial_.serial_, 0, RP_SERIAL_LENGTH);
		device_.device_communication_ = UNKNOWN_DEVICE_COMMUNICATION;
		device_.frequency_correction_calibration_date_  = 0;
		device_.rf_calibration_date_ = 0;
		device_.num_frequency_paths_ = 0;
		device_.num_licenses_ = 0;
	}
	explicit Device(const rp_device_info &rp_device, QObject *parent = 0)
		: QObject(parent)
		, device_(rp_device)
	{}

	~Device() {}

	void copy(const Device &a) {
		if(memcmp(device_.serial_.serial_, a.device_.serial_.serial_, RP_SERIAL_LENGTH)) {
			memcpy(device_.serial_.serial_, a.device_.serial_.serial_, RP_SERIAL_LENGTH);
			emit serialChanged();
		}
		if(device_.device_communication_ != a.device_.device_communication_) {
			device_.device_communication_ = a.device_.device_communication_;
			emit deviceCommunicationChanged();
		}
		if(device_.frequency_correction_calibration_date_ != a.device_.frequency_correction_calibration_date_) {
			device_.frequency_correction_calibration_date_ = a.device_.frequency_correction_calibration_date_;
			emit freqCorrectionDateChanged();
		}
		if(device_.rf_calibration_date_ != a.device_.rf_calibration_date_) {
			device_.rf_calibration_date_ = a.device_.rf_calibration_date_;
			emit rfCalibrationDateChanged();
		}
		if(device_.num_frequency_paths_ != a.device_.num_frequency_paths_) {
			device_.num_frequency_paths_ = a.device_.num_frequency_paths_;
			emit calibratedFreqListChanged();
		}
		if(memcmp(device_.frequency_paths_, a.device_.frequency_paths_, RP_FREQUENCY_PATH_SIZE)) {
			memcpy(device_.frequency_paths_, a.device_.frequency_paths_, RP_FREQUENCY_PATH_SIZE);
			calibratedFreqList_.clear();
			for(auto i = 0; i < device_.num_frequency_paths_; ++i) {
				calibratedFreqList_.push_back(QString(QString::number(device_.frequency_paths_[i].low_freq_)
													  + " - " +
													  QString::number(device_.frequency_paths_[i].high_freq_)
													  + " mhz"));
			}
			emit calibratedFreqListChanged();
		}
		if(device_.num_licenses_ != a.device_.num_licenses_) {
			device_.num_licenses_ = a.device_.num_licenses_;
			emit licenseListChanged();
		}
//		if(memcmp(device_.licenses_, a.device_.licenses_, RP_FREQUENCY_PATH_SIZE)) {
//			memcpy(device_.licenses_, a.device_.licenses_, RP_FREQUENCY_PATH_SIZE);
//			emit licenseListChanged();
//		}
	}

	void copy(const rp_device_info &a) {
		if(memcmp(device_.serial_.serial_, a.serial_.serial_, RP_SERIAL_LENGTH)) {
			memcpy(device_.serial_.serial_, a.serial_.serial_, RP_SERIAL_LENGTH);
			emit serialChanged();
		}
		if(device_.device_communication_ != a.device_communication_) {
			device_.device_communication_ = a.device_communication_;
			emit deviceCommunicationChanged();
		}
		if(device_.frequency_correction_calibration_date_ != a.frequency_correction_calibration_date_) {
			device_.frequency_correction_calibration_date_ = a.frequency_correction_calibration_date_;
			emit freqCorrectionDateChanged();
		}
		if(device_.rf_calibration_date_ != a.rf_calibration_date_) {
			device_.rf_calibration_date_ = a.rf_calibration_date_;
			emit rfCalibrationDateChanged();
		}
		if(device_.num_frequency_paths_ != a.num_frequency_paths_) {
			device_.num_frequency_paths_ = a.num_frequency_paths_;
			emit calibratedFreqListChanged();
		}
		if(memcmp(device_.frequency_paths_, a.frequency_paths_, RP_FREQUENCY_PATH_SIZE)) {
			memcpy(device_.frequency_paths_, a.frequency_paths_, RP_FREQUENCY_PATH_SIZE);
			emit calibratedFreqListChanged();
		}
		if(device_.num_licenses_ != a.num_licenses_) {
			device_.num_licenses_ = a.num_licenses_;
			emit licenseListChanged();
		}
//		if(memcmp(device_.licenses_, a.device_.licenses_, RP_FREQUENCY_PATH_SIZE)) {
//			memcpy(device_.licenses_, a.device_.licenses_, RP_FREQUENCY_PATH_SIZE);
//			emit licenseListChanged();
//		}
	}

	QString serial() { return ApiTypes::toQString(device_.serial_); }
	QString serialShort() { return ApiTypes::toQStringShort(device_.serial_); }
	ApiTypes::DeviceCommunication deviceCommunication() { return (ApiTypes::DeviceCommunication)device_.device_communication_; }
	QString deviceCommunicationStr() { return ApiTypes::toQString(device_.device_communication_); }
	QDate freqCorrectionDate() { return dt_.fromTime_t(device_.frequency_correction_calibration_date_).date(); }
	QString freqCorrectionDateStr() {
		if(device_.frequency_correction_calibration_date_)
			return dt_.fromTime_t(device_.frequency_correction_calibration_date_, Qt::UTC).toString(Qt::TextDate);
		else
			return "Unknown";
	}
	QDate rfCalibrationDate() { return dt_.fromTime_t(device_.rf_calibration_date_).date(); }
	QString rfCalibrationDateStr() {
		if(device_.rf_calibration_date_)
			return dt_.fromTime_t(device_.rf_calibration_date_, Qt::UTC).toString(Qt::TextDate);
		else
			return "Unknown";
	}
	QStringList calibratedFreqList() { return calibratedFreqList_; }
	QList<QObject*> licenseList() { return licenseList_; }

signals:
	void serialChanged();
	void deviceCommunicationChanged();
	void freqCorrectionDateChanged();
	void rfCalibrationDateChanged();
	void licenseListChanged();
	void calibratedFreqListChanged();

public slots:

private:
	rp_device_info device_;
	QDateTime dt_;
	QStringList calibratedFreqList_;
	QList<QObject*> licenseList_;


	//	bool isConnected() { return isConnected_; }
	//	void setIsConnected(bool c) {
	//		if(isConnected_ != c) {
	//			isConnected_ = c;
	//			emit isConnectedChanged();
	//		}
	//	}
		//void isConnectedChanged();
		//	bool isConnected_;
};

//}}
