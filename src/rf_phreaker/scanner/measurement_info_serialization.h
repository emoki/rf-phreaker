#include "boost/serialization/access.hpp"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/common/common_serialization.h"

namespace boost { namespace serialization {

template<class Archive>
void save(Archive & ar, const rf_phreaker::scanner::measurement_info &sig, const unsigned int version) {
	ar & boost::serialization::base_object<rf_phreaker::raw_signal>(sig);

	int64_t collection_round = sig.collection_round();
	rf_phreaker::scanner::gain_type gain = sig.gain();
	rf_phreaker::operating_bands operating_bands = sig.get_operating_bands();
	auto blade_adjustments = sig.blade_adjustments();
	auto rf_board_adjustments =  sig.rf_board_adjustments();
	std::string serial = sig.serial();
	
	ar & collection_round;
	ar & gain.lna_gain_;
	ar & gain.rxvga1_;
	ar & gain.rxvga2_;
	ar & operating_bands;
	ar & blade_adjustments;
	ar & rf_board_adjustments;
	ar & serial;
}

template<class Archive>
void load(Archive & ar, rf_phreaker::scanner::measurement_info &sig, const unsigned int version) {
	using namespace rf_phreaker::scanner;

	ar & boost::serialization::base_object<rf_phreaker::raw_signal>(sig);

	int64_t collection_round;
	gain_type gain;
	rf_phreaker::operating_bands operating_bands;
	double tmp_blade_adjustment;
	double tmp_rf_board_adjustment;
	rf_adjustment blade_adjustment;
	rf_adjustment rf_board_adjustment;
	std::string serial;
	ar & collection_round;
	sig.collection_round(collection_round);
	ar & gain.lna_gain_;
	ar & gain.rxvga1_;
	ar & gain.rxvga2_;
	sig.gain(gain);
	if(version <= 1) {
		rf_phreaker::operating_band b;
		rf_phreaker::operating_bands bs;
		ar & b;
		operating_bands.add_band(b);
	}
	else {
		ar & operating_bands;
	}
	sig.set_operating_bands(operating_bands);

	if(version == 0) {
		ar & tmp_blade_adjustment;
		ar & tmp_rf_board_adjustment;
		sig.blade_adjustments(rf_adjustment(rf_phreaker::frequency_path(sig.frequency(), sig.frequency()), tmp_blade_adjustment));
		sig.rf_board_adjustments(rf_adjustment(rf_phreaker::frequency_path(sig.frequency(), sig.frequency()),tmp_rf_board_adjustment));
	}
	else {
		ar & blade_adjustment;
		sig.blade_adjustments(blade_adjustment);
		ar & rf_board_adjustment;
		sig.rf_board_adjustments(rf_board_adjustment);
	}
	ar & serial;
	sig.serial(serial);

}

template<class Archive>
void serialize(Archive & ar, rf_phreaker::scanner::measurement_info &sig, const unsigned int version) {
	boost::serialization::split_free(ar, sig, version);
}


}}


BOOST_CLASS_VERSION(rf_phreaker::scanner::measurement_info, 2)
