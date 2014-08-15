#include "boost/serialization/access.hpp"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/common/common_serialization.h"

namespace boost { namespace serialization {

template<class Archive>
void save(Archive & ar, const rf_phreaker::scanner::measurement_info &sig, const unsigned int version) {
	ar & boost::serialization::base_object<rf_phreaker::raw_signal>(sig);

	int64_t collection_round = sig.collection_round();
	rf_phreaker::scanner::gain_type gain = sig.gain();
	rf_phreaker::operating_band operating_band = sig.get_operating_band();
	double blade_adjustment = sig.blade_adjustment();
	double rf_board_adjustment =  sig.rf_board_adjustment();
	std::string serial = sig.serial();
	
	ar & collection_round;
	ar & gain.lna_gain_;
	ar & gain.rxvga1_;
	ar & gain.rxvga2_;
	ar & operating_band;
	ar & blade_adjustment;
	ar & rf_board_adjustment;
	ar & serial;
}

template<class Archive>
void load(Archive & ar, rf_phreaker::scanner::measurement_info &sig, const unsigned int version) {
	ar & boost::serialization::base_object<rf_phreaker::raw_signal>(sig);

	int64_t collection_round;
	rf_phreaker::scanner::gain_type gain;
	rf_phreaker::operating_band operating_band;
	double blade_adjustment;
	double rf_board_adjustment;
	std::string serial;
	ar & collection_round;
	sig.collection_round(collection_round);
	ar & gain.lna_gain_;
	ar & gain.rxvga1_;
	ar & gain.rxvga2_;
	sig.gain(gain);
	ar & operating_band;
	sig.set_operating_band(operating_band);
	ar & blade_adjustment;
	sig.blade_adjustment(blade_adjustment);
	ar & rf_board_adjustment;
	sig.rf_board_adjustment(rf_board_adjustment);
	ar & serial;
	sig.serial(serial);

}

template<class Archive>
void serialize(Archive & ar, rf_phreaker::scanner::measurement_info &sig, const unsigned int version) {
	boost::serialization::split_free(ar, sig, version);
}


}}
