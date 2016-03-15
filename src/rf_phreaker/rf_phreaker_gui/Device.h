#pragma once
#include <QObject>
#include <QDateTime>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/common/measurements.h"

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
		device_.device_communication_ = rf_phreaker::UNKNOWN_SPEED;
		device_.frequency_correction_calibration_date_  = 0;
		device_.rf_calibration_date_ = 0;
	}
	explicit Device(const rf_phreaker::hardware &device, QObject *parent = 0)
		: QObject(parent)
		, device_(device)
	{}

	~Device() {}

	void copy(const Device &a) {
		if(device_.serial_ != a.device_.serial_) {
			device_.serial_ = a.device_.serial_;
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
		if(device_.frequency_paths_ != a.device_.frequency_paths_) {
			device_.frequency_paths_ = a.device_.frequency_paths_;
			format_frequency_paths();
			emit calibratedFreqListChanged();
		}
//		if(memcmp(device_.licenses_, a.device_.licenses_, RP_FREQUENCY_PATH_SIZE)) {
//			memcpy(device_.licenses_, a.device_.licenses_, RP_FREQUENCY_PATH_SIZE);
//			emit licenseListChanged();
//		}
	}

	void copy(const rf_phreaker::hardware &a) {
		if(device_.serial_ != a.serial_) {
			device_.serial_ = a.serial_;
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
		if(device_.frequency_paths_ != a.frequency_paths_) {
			device_.frequency_paths_ = a.frequency_paths_;
			format_frequency_paths();
			emit calibratedFreqListChanged();
		}
//		if(memcmp(device_.licenses_, a.device_.licenses_, RP_FREQUENCY_PATH_SIZE)) {
//			memcpy(device_.licenses_, a.device_.licenses_, RP_FREQUENCY_PATH_SIZE);
//			emit licenseListChanged();
//		}
	}

	QString serial() { return QString(device_.serial_.c_str()); }
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

	void format_frequency_paths() {
		calibratedFreqList_.clear();
		for(auto &i : device_.frequency_paths_) {
			calibratedFreqList_.push_back(QString(QString::number(i.low_freq_)
				+ " - " +
				QString::number(i.high_freq_)
				+ " mhz"));
		}
	}
signals:
	void serialChanged();
	void deviceCommunicationChanged();
	void freqCorrectionDateChanged();
	void rfCalibrationDateChanged();
	void licenseListChanged();
	void calibratedFreqListChanged();

public slots:

private:
	rf_phreaker::hardware device_;
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
