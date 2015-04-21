#pragma once
#include <QObject>
#include <QDateTime>
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"
#include "rf_phreaker/rf_phreaker_gui/ApiTypes.h"

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
	Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
	Q_PROPERTY(QDate utcDate READ utcDate NOTIFY utcChanged)
	Q_PROPERTY(QString utcTime READ utcTime NOTIFY utcChanged)
	Q_PROPERTY(QString utcDateTime READ utcDateTime NOTIFY utcChanged)

public:
	explicit Gps(QObject *parent = 0)
		: QObject(parent) {
		dt_.setTimeSpec(Qt::UTC);
		memset(&gps_, 0, sizeof(gps_));
	}
	explicit Gps(const rp_gps& gps, QObject *parent = 0)
		: QObject(parent)
		, gps_(gps) {
		dt_.setTimeSpec(Qt::UTC);
	}

	~Gps() {}

	void copy(const Gps &a) {
		if(memcmp(gps_.serial_.serial_, a.gps_.serial_.serial_, RP_SERIAL_LENGTH)) {
			memcpy(gps_.serial_.serial_, a.gps_.serial_.serial_, RP_SERIAL_LENGTH);
			emit serialChanged();
		}
		if(gps_.lock_ != a.gps_.lock_) {
			gps_.lock_ = a.gps_.lock_;
			emit gpsLockChanged();
		}
		if(gps_.visible_satellites_ != a.gps_.visible_satellites_) {
			gps_.visible_satellites_ = a.gps_.visible_satellites_;
			emit visibleSatellitesChanged();
		}
		if(gps_.tracking_satellites_ != a.gps_.tracking_satellites_) {
			gps_.tracking_satellites_ = a.gps_.tracking_satellites_;
			emit trackingSatellitesChanged();
		}
		if(gps_.latitude_ != a.gps_.latitude_) {
			gps_.latitude_ = a.gps_.latitude_;
			emit latitudeChanged();
		}
		if(gps_.longitude_ != a.gps_.longitude_) {
			gps_.longitude_ = a.gps_.longitude_;
			emit longitudeChanged();
		}
		if(gps_.speed_ != a.gps_.speed_) {
			gps_.speed_ = a.gps_.speed_;
			emit speedChanged();
		}
		if(gps_.coordinated_universal_time_ != a.gps_.coordinated_universal_time_) {
			gps_.coordinated_universal_time_ = a.gps_.coordinated_universal_time_;
			emit utcChanged();
		}
	}

	void copy(const rp_gps &a) {
		if(memcmp(gps_.serial_.serial_, a.serial_.serial_, RP_SERIAL_LENGTH)) {
			memcpy(gps_.serial_.serial_, a.serial_.serial_, RP_SERIAL_LENGTH);
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
		if(gps_.speed_ != a.speed_) {
			gps_.speed_ = a.speed_;
			emit speedChanged();
		}
		if(gps_.coordinated_universal_time_ != a.coordinated_universal_time_) {
			gps_.coordinated_universal_time_ = a.coordinated_universal_time_;
			emit utcChanged();
		}
	}

	QString serial() { return ApiTypes::toQString(gps_.serial_); }
	bool gpsLock() { return gps_.lock_; }
	int visibleSatellites() { return gps_.visible_satellites_; }
	int trackingSatellites() { return gps_.tracking_satellites_; }
	int latitude() { return gps_.latitude_; }
	int longitude() { return gps_.longitude_; }
	int speed() { return gps_.speed_; }
	QDate utcDate() { return dt_.fromTime_t(gps_.coordinated_universal_time_).date(); }
	QString utcTime() {
		if(gps_.coordinated_universal_time_)
			return dt_.fromTime_t(gps_.coordinated_universal_time_).toString("HH:mm:ss");
		else
			return "Unknown";
	}
	QString utcDateTime() {
		if(gps_.coordinated_universal_time_)
			return dt_.fromTime_t(gps_.coordinated_universal_time_, Qt::UTC).toString(Qt::TextDate);
		else
			return "Unknown";
	}

signals:
	void serialChanged();
	void gpsLockChanged();
	void visibleSatellitesChanged();
	void trackingSatellitesChanged();
	void latitudeChanged();
	void longitudeChanged();
	void speedChanged();
	void utcChanged();

public slots:

private:
	rp_gps gps_;
	QDateTime dt_;
};

//}}
