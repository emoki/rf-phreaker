#pragma once
#include <QDataStream>
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api.h"

//namespace rf_phreaker { namespace gui {

Q_DECLARE_METATYPE(rf_phreaker::channel_freq)
Q_DECLARE_METATYPE(ApiTypes::Tech)

QDataStream &operator<<(QDataStream &out, const rf_phreaker::channel_freq &t);
QDataStream &operator>>(QDataStream &in, rf_phreaker::channel_freq &t);
QDataStream &operator<<(QDataStream &out, const ApiTypes::Tech &t);
QDataStream &operator>>(QDataStream &in, ApiTypes::Tech &t);

inline QDataStream &operator<<(QDataStream &out, const rf_phreaker::channel_freq &t) {
	out << (int32_t)t.band_;
	out << t.channel_;
	out << t.freq_;
	return out;
}

inline QDataStream &operator>>(QDataStream &in, rf_phreaker::channel_freq &t) {
	int32_t band;
	in >> band;
	t.band_ = (rf_phreaker::operating_band)band;
	in >> t.channel_;
	in >> t.freq_;
	return in;
}

inline QDataStream &operator<<(QDataStream &out, const ApiTypes::Tech &t) {
	out << (int32_t)t;
	return out;
}

inline QDataStream &operator>>(QDataStream &in, ApiTypes::Tech &t) {
	int32_t tech;
	in >> tech;
	t = (ApiTypes::Tech)tech;
	return in;
}

//}}