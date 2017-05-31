#pragma once
#include <mutex>
#include <QMutex>
#include <QList>
#include <QString>
#include <QDebug>
#include "rf_phreaker/rf_phreaker_gui/Serialization.h"
#include "rf_phreaker/rf_phreaker_gui/CollectionInfo.h"
#include "rf_phreaker/common/settings.h"
#include "marble/geodata/data/GeoDataCoordinates.h"

//namespace rf_phreaker { namespace gui {

// Does not support multithreaded operations.
class Settings : public QObject {
	Q_OBJECT
	Q_PROPERTY(bool apiOutput MEMBER apiOutput_ NOTIFY apiOutputChanged)
	Q_PROPERTY(qreal rpfTrackMinDistance MEMBER rpfTrackMinDistance_ NOTIFY rpfTrackMinDistanceChanged)
	Q_PROPERTY(QString themePrimaryColor MEMBER themePrimaryColor_ NOTIFY themePrimaryColorChanged)
	Q_PROPERTY(QString themeAccentColor MEMBER themeAccentColor_ NOTIFY themeAccentColorChanged)
	Q_PROPERTY(QString themeTabHighlightColor MEMBER themeTabHighlightColor_ NOTIFY themeTabHighlightColorChanged)
	Q_PROPERTY(int measurementRemovalTime MEMBER measurementRemovalTime_ NOTIFY measurementRemovalTimeChanged)
	Q_PROPERTY(bool convertRfpToAscii MEMBER convertRfpToAscii_ NOTIFY convertRfpToAsciiChanged)
	Q_PROPERTY(int logLevelAppVerbosity MEMBER logLevelAppVerbosity_ NOTIFY logLevelAppVerbosityChanged)
	Q_PROPERTY(int logLevelHardwareVerbosity MEMBER logLevelHardwareVerbosity_ NOTIFY logLevelHardwareVerbosityChanged)
	Q_PROPERTY(bool loggingGps MEMBER loggingGps_ NOTIFY loggingGpsChanged)
	Q_PROPERTY(bool loggingCollection MEMBER loggingCollection_ NOTIFY loggingCollectionChanged)
	Q_PROPERTY(bool loggingPackets MEMBER loggingPackets_ NOTIFY loggingPacketsChanged)

signals:
	void apiOutputChanged(bool);
	void rpfTrackMinDistanceChanged(qreal);
	void themePrimaryColorChanged(QString);
	void themeAccentColorChanged(QString);
	void themeTabHighlightColorChanged(QString);
	void measurementRemovalTimeChanged(int);
	void convertRfpToAsciiChanged(bool);
	void logLevelAppVerbosityChanged(int);
	void logLevelHardwareVerbosityChanged(int);
	void loggingGpsChanged(bool);
	void loggingCollectionChanged(bool);
	void loggingPacketsChanged(bool);

public:
	Settings(QObject *parent = nullptr) 
		: QObject(parent) {
		loadSettings();
	}

	static Settings* instance();
	
	Q_INVOKABLE void loadSettings();
	
	Q_INVOKABLE void saveSettings();

	Q_INVOKABLE bool shouldReinitializeApi();

	rf_phreaker::settings readRpSettings();

	void writeRpSettings(rf_phreaker::settings &s);

	void emitSignals() {
		emit apiOutputChanged(apiOutput_);
		emit rpfTrackMinDistanceChanged(rpfTrackMinDistance_);
		emit themePrimaryColorChanged(themePrimaryColor_);
		emit themeAccentColorChanged(themeAccentColor_);
		emit themeTabHighlightColorChanged(themeTabHighlightColor_);
		emit measurementRemovalTimeChanged(measurementRemovalTime_);
		emit convertRfpToAsciiChanged(convertRfpToAscii_);
		emit logLevelAppVerbosityChanged(logLevelAppVerbosity_);
		emit logLevelHardwareVerbosityChanged(logLevelAppVerbosity_);
		emit loggingGpsChanged(loggingGps_);
		emit loggingCollectionChanged(loggingCollection_);
		emit loggingPacketsChanged(loggingPackets_);
	}

	bool apiOutput_;
	double rpfTrackMinDistance_;
	QString themePrimaryColor_;
	QString themeAccentColor_;
	QString themeTabHighlightColor_;
	int measurementRemovalTime_;
	bool convertRfpToAscii_;
	int logLevelAppVerbosity_;
	int logLevelHardwareVerbosity_;
	bool loggingGps_;
	bool loggingCollection_;
	bool loggingPackets_;
private:
	friend class SettingsIO;
	static Settings *instance_;
	static QMutex instance_mutex_;
};

//}}
