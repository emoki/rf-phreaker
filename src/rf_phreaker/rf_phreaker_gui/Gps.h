#pragma once
#include <QObject>
#include <QDateTime>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"
#include "rf_phreaker/common/measurements.h"

//namespace rf_phreaker { namespace gui {

class Gps : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString serial READ serial NOTIFY serialChanged)
	Q_PROPERTY(bool gpsLock READ gpsLock NOTIFY gpsLockChanged)
	Q_PROPERTY(int visibleSatellites READ visibleSatellites NOTIFY visibleSatellitesChanged)
	Q_PROPERTY(int trackingSatellites READ trackingSatellites NOTIFY trackingSatellitesChanged)
	Q_PROPERTY(double latitude READ latitude NOTIFY latitudeChanged)
	Q_PROPERTY(double longitude READ longitude NOTIFY longitudeChanged)
	Q_PROPERTY(double altitude READ altitude NOTIFY altitudeChanged)
	Q_PROPERTY(double angle READ angle NOTIFY angleChanged)
	Q_PROPERTY(double speed READ speed NOTIFY speedChanged)
	Q_PROPERTY(double dilutionOfPrecision READ dilutionOfPrecision NOTIFY dilutionOfPrecisionChanged)
	Q_PROPERTY(double horizontalAccuracyMeters READ horizontalAccuracyMeters NOTIFY horizontalAccuracyMetersChanged)
	Q_PROPERTY(double verticalAccuracyMeters READ verticalAccuracyMeters NOTIFY verticalAccuracyMetersChanged)
	Q_PROPERTY(QDate utcDate READ utcDate NOTIFY utcChanged)
	Q_PROPERTY(QString utcTimeStr READ utcTimeStr NOTIFY utcChanged)
	Q_PROPERTY(QString utcDateTimeStr READ utcDateTimeStr NOTIFY utcChanged)

public:
	explicit Gps(QObject *parent = 0)
		: QObject(parent) {
		dt_.setTimeSpec(Qt::UTC);
		gps_.lock_ = false;
	}
	explicit Gps(const rf_phreaker::gps& gps, QObject *parent = 0)
		: QObject(parent)
		, gps_(gps) {
		dt_.setTimeSpec(Qt::UTC);
	}

	~Gps() {}

	void copy(const Gps &a) {
		copy(a.gps_);
	}

	void copy(const rf_phreaker::gps &a) {
		if(gps_.serial_ != a.serial_) {
			gps_.serial_ = a.serial_;
			emit serialChanged();
		}
		if(gps_.lock_ != a.lock_) {
			gps_.lock_ = a.lock_;
			emit gpsLockChanged();
		}
		if(gps_.visible_satellites_ != a.visible_satellites_) {
			gps_.visible_satellites_ = a.visible_satellites_;
			emit visibleSatellitesChanged();
		}
		if(gps_.tracking_satellites_ != a.tracking_satellites_) {
			gps_.tracking_satellites_ = a.tracking_satellites_;
			emit trackingSatellitesChanged();
		}
		if(gps_.latitude_ != a.latitude_) {
			gps_.latitude_ = a.latitude_;
			emit latitudeChanged();
		}
		if(gps_.longitude_ != a.longitude_) {
			gps_.longitude_ = a.longitude_;
			emit longitudeChanged();
		}
		if(gps_.coordinated_universal_time_ != a.coordinated_universal_time_) {
			gps_.coordinated_universal_time_ = a.coordinated_universal_time_;
			emit utcChanged();
		}
		if(gps_.altitude_ != a.altitude_) {
			gps_.altitude_ = a.altitude_;
			emit altitudeChanged();
		}
		if(gps_.angle_ != a.angle_) {
			gps_.angle_ = a.angle_;
			emit angleChanged();
		}
		if(gps_.speed_ != a.speed_) {
			gps_.speed_ = a.speed_;
			emit speedChanged();
		}
		if(gps_.dilution_of_precision_ != a.dilution_of_precision_) {
			gps_.dilution_of_precision_ = a.dilution_of_precision_;
			emit dilutionOfPrecisionChanged();
		}
		if(gps_.horizontal_accuracy_meters_ != a.horizontal_accuracy_meters_) {
			gps_.horizontal_accuracy_meters_ = a.horizontal_accuracy_meters_;
			emit horizontalAccuracyMetersChanged();
		}
		if(gps_.vertical_accuracy_meters_ != a.vertical_accuracy_meters_) {
			gps_.vertical_accuracy_meters_ = a.vertical_accuracy_meters_;
			emit verticalAccuracyMetersChanged();
		}
	}

	QString serial() { return gps_.serial_.c_str(); }
	bool gpsLock() { return gps_.lock_; }
	int visibleSatellites() { return gps_.visible_satellites_; }
	int trackingSatellites() { return gps_.tracking_satellites_; }
	double latitude() { return gps_.latitude_; }
	double longitude() { return gps_.longitude_; }
	QDate utcDate() { return dt_.fromTime_t(gps_.coordinated_universal_time_).date(); }
	QDateTime utcDateTime() { return dt_.fromTime_t(gps_.coordinated_universal_time_); }
	QString utcTimeStr() {
		if(gps_.coordinated_universal_time_)
			return dt_.fromTime_t(gps_.coordinated_universal_time_).toString("HH:mm:ss");
		else
			return "Unknown";
	}
	QString utcDateTimeStr() {
		if(gps_.coordinated_universal_time_)
			return dt_.fromTime_t(gps_.coordinated_universal_time_, Qt::UTC).toString(Qt::TextDate);
		else
			return "Unknown";
	}
	double altitude() { return gps_.altitude_; }
	double angle() { return gps_.angle_; }
	double speed() { return gps_.speed_; }
	double dilutionOfPrecision() { return gps_.dilution_of_precision_; }
	double horizontalAccuracyMeters() { return gps_.horizontal_accuracy_meters_; }
	double verticalAccuracyMeters() { return gps_.vertical_accuracy_meters_; }

signals:
	void serialChanged();
	void gpsLockChanged();
	void visibleSatellitesChanged();
	void trackingSatellitesChanged();
	void latitudeChanged();
	void longitudeChanged();
	void utcChanged();
	void altitudeChanged();
	void angleChanged();
	void speedChanged();
	void dilutionOfPrecisionChanged();
	void horizontalAccuracyMetersChanged();
	void verticalAccuracyMetersChanged();

public slots:

private:
	rf_phreaker::gps gps_;
	QDateTime dt_;
};

//}}
