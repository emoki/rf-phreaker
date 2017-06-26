#include "rf_phreaker/rf_phreaker_gui/SettingsIO.h"
#include "rf_phreaker/rf_phreaker_gui/Settings.h"


void SettingsIO::readSettings(Settings &settings) {
	settings.apiOutput_ = qs_.value(apiOutputKey, false).toBool();
	settings.rpfTrackMinDistance_ = qs_.value(rpfTrackMinDistanceKey, 3).toDouble();
	settings.themePrimaryColor_ = qs_.value(themePrimaryColorKey, "indigo").toString();
	settings.themeAccentColor_ = qs_.value(themeAccentColorkey, "green").toString();
	settings.themeTabHighlightColor_ = qs_.value(themeTabHighlightColorKey, "white").toString();
	settings.measurementRemovalTime_ = qs_.value(measurementRemovalTimeKey, 60).toInt();
	settings.convertRfpToAscii_ = qs_.value(convertRfpToAsciiKey, false).toBool();
	settings.isSpectrumLogged_ = qs_.value(isSpectrumLoggedKey, false).toBool();
	settings.spectrumBinSize_ = qs_.value(spectrumBinSizeKey, 2000).toInt();
	settings.spectrumDwellTime_= qs_.value(spectrumDwellTimeKey, 25000000).toInt();
	settings.cwBinSize_ = qs_.value(cwBinSizeKey, 2000).toInt();
	settings.cwSpanFactor_ = qs_.value(cwSpanKey, 6).toInt();
	settings.cwDwellTime_ = qs_.value(cwDwellTimeKey, 25000000).toInt();
	settings.cwOffsetFactor_ = qs_.value(cwOffsetKey, 2).toInt();
	settings.iqBandwidth_= qs_.value(iqBandwidthKey, 5000000).toInt();
	settings.iqSamplingRate_ = qs_.value(iqSamplingRateKey, 10000000).toInt();
	settings.iqDwellTime_ = qs_.value(iqDwellTimeKey, 50000000).toInt();
}

void SettingsIO::writeSettings(const Settings &settings) {
	qs_.setValue(apiOutputKey, settings.apiOutput_);
	qs_.setValue(rpfTrackMinDistanceKey, settings.rpfTrackMinDistance_);
	qs_.setValue(themePrimaryColorKey, settings.themePrimaryColor_);
	qs_.setValue(themeAccentColorkey, settings.themeAccentColor_);
	qs_.setValue(themeTabHighlightColorKey, settings.themeTabHighlightColor_);
	qs_.setValue(measurementRemovalTimeKey, settings.measurementRemovalTime_);
	qs_.setValue(convertRfpToAsciiKey, settings.convertRfpToAscii_);
	qs_.setValue(isSpectrumLoggedKey, settings.isSpectrumLogged_);
	qs_.setValue(spectrumBinSizeKey, settings.spectrumBinSize_);
	qs_.setValue(spectrumDwellTimeKey, settings.spectrumDwellTime_);
	qs_.setValue(cwBinSizeKey, settings.cwBinSize_);
	qs_.setValue(cwSpanKey, settings.cwSpanFactor_);
	qs_.setValue(cwDwellTimeKey, settings.cwDwellTime_);
	qs_.setValue(cwOffsetKey, settings.cwOffsetFactor_);
	qs_.setValue(iqBandwidthKey, settings.iqBandwidth_);
	qs_.setValue(iqSamplingRateKey, settings.iqSamplingRate_);
	qs_.setValue(iqDwellTimeKey, settings.iqDwellTime_);
}
