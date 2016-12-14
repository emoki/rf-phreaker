#include "rf_phreaker/rf_phreaker_gui/SettingsIO.h"
#include "rf_phreaker/rf_phreaker_gui/Settings.h"


void SettingsIO::readSettings(Settings &settings) {
	settings.apiOutput_ = qs_.value(apiOutputKey, false).toBool();
	settings.rpfTrackMinDistance_ = qs_.value(rpfTrackMinDistanceKey, 3).toDouble();
	settings.themePrimaryColor_ = qs_.value(themePrimaryColorKey, "indigo").toString();
	settings.themeAccentColor_ = qs_.value(themeAccentColorkey, "green").toString();
	settings.themeTabHighlightColor_ = qs_.value(themeTabHighlightColorKey, "white").toString();
	settings.measurementRemovalTime_ = qs_.value(measurementRemovalTimeKey, 30).toInt();
	settings.convertRfpToAscii_ = qs_.value(convertRfpToAsciiKey, false).toBool();
}

void SettingsIO::writeSettings(const Settings &settings) {
	qs_.setValue(apiOutputKey, settings.apiOutput_);
	qs_.setValue(rpfTrackMinDistanceKey, settings.rpfTrackMinDistance_);
	qs_.setValue(themePrimaryColorKey, settings.themePrimaryColor_);
	qs_.setValue(themeAccentColorkey, settings.themeAccentColor_);
	qs_.setValue(themeTabHighlightColorKey, settings.themeTabHighlightColor_);
	qs_.setValue(measurementRemovalTimeKey, settings.measurementRemovalTime_);
	qs_.setValue(convertRfpToAsciiKey, settings.convertRfpToAscii_);
}
