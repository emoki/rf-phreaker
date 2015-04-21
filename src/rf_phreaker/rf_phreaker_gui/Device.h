#pragma once
#include <QObject>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"

//namespace rf_phreaker { namespace gui {

class Device : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString serial READ serial NOTIFY serialChanged)
//	Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)
//	Q_PROPERTY( READ WRITE set NOTIFY Changed)

public:
	explicit Device(QObject *parent = 0)
		:QObject(parent)
	{
		memset(device_.serial_.serial_, 0, RP_SERIAL_LENGTH);
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
			//emit gpsLockChanged();
		}
		if(device_.frequency_correction_calibration_date_ != a.device_.frequency_correction_calibration_date_) {
			device_.frequency_correction_calibration_date_ = a.device_.frequency_correction_calibration_date_;
			//emit visibleSatellitesChanged();
		}
		if(device_.rf_calibration_date_ != a.device_.rf_calibration_date_) {
			device_.rf_calibration_date_ = a.device_.rf_calibration_date_;
			//emit trackingSatellitesChanged();
		}
		if(device_.num_frequency_paths_ != a.device_.num_frequency_paths_) {
			device_.num_frequency_paths_ = a.device_.num_frequency_paths_;
			//emit latitudeChanged();
		}
		if(memcmp(device_.frequency_paths_, a.device_.frequency_paths_, RP_FREQUENCY_PATH_SIZE)) {
			memcpy(device_.frequency_paths_, a.device_.frequency_paths_, RP_FREQUENCY_PATH_SIZE);
			//emit longitudeChanged();
		}
		if(device_.num_licenses_ != a.device_.num_licenses_) {
			device_.num_licenses_ = a.device_.num_licenses_;
			//emit speedChanged();
		}
	}

	void copy(const rp_device_info &a) {
		if(memcmp(device_.serial_.serial_, a.serial_.serial_, RP_SERIAL_LENGTH)) {
			memcpy(device_.serial_.serial_, a.serial_.serial_, RP_SERIAL_LENGTH);
			emit serialChanged();
		}
		if(device_.device_communication_ != a.device_communication_) {
			device_.device_communication_ = a.device_communication_;
			//emit gpsLockChanged();
		}
		if(device_.frequency_correction_calibration_date_ != a.frequency_correction_calibration_date_) {
			device_.frequency_correction_calibration_date_ = a.frequency_correction_calibration_date_;
			//emit visibleSatellitesChanged();
		}
		if(device_.rf_calibration_date_ != a.rf_calibration_date_) {
			device_.rf_calibration_date_ = a.rf_calibration_date_;
			//emit trackingSatellitesChanged();
		}
		if(device_.num_frequency_paths_ != a.num_frequency_paths_) {
			device_.num_frequency_paths_ = a.num_frequency_paths_;
			//emit latitudeChanged();
		}
		if(memcmp(device_.frequency_paths_, a.frequency_paths_, RP_FREQUENCY_PATH_SIZE)) {
			memcpy(device_.frequency_paths_, a.frequency_paths_, RP_FREQUENCY_PATH_SIZE);
			//emit longitudeChanged();
		}
		if(device_.num_licenses_ != a.num_licenses_) {
			device_.num_licenses_ = a.num_licenses_;
			//emit speedChanged();
		}
	}

	QString serial() { return ApiTypes::toQString(device_.serial_); }
//	bool isConnected() { return isConnected_; }
//	void setIsConnected(bool c) {
//		if(isConnected_ != c) {
//			isConnected_ = c;
//			emit isConnectedChanged();
//		}
//	}
signals:
	void serialChanged();
//	void isConnectedChanged();

public slots:

private:
	rp_device_info device_;
//	bool isConnected_;
};

//}}
