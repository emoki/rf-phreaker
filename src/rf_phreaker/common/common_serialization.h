#include "boost/serialization/access.hpp"
#include "boost/serialization/vector.hpp"
#include "boost/serialization/map.hpp"
#include "rf_phreaker/common/raw_signal.h"

namespace boost { namespace serialization {

template<class Archive>
void serialize(Archive & ar, rf_phreaker::bandwidth_type &a, const unsigned int version) {
	ar & a;
}

template<class Archive>
void serialize(Archive & ar, rf_phreaker::frequency_type &a, const unsigned int version) {
	ar & a;
}

template<class Archive>
void serialize(Archive & ar, Ipp32fc &a, const unsigned int version) {
	ar & a.re;
	ar & a.im;
}

template<class Archive, class Ipp_Type>
void save(Archive & ar, const rf_phreaker::ipp_array<Ipp_Type> &ipp, const unsigned int version) {
	int length = ipp.length();
	ar & length;
	for(int i = 0; i < length; ++i) {
		ar & ipp[i];
	}
}

template<class Archive, class Ipp_Type>
void load(Archive & ar, rf_phreaker::ipp_array<Ipp_Type> &ipp, const unsigned int version) {
	int length = 0;
	ar & length;
	ipp.reset(length);
	for(int i = 0; i < length; ++i) {
		ar & ipp[i];
	}
}

template<class Archive, class Ipp_Type>
void serialize(Archive & ar, rf_phreaker::ipp_array<Ipp_Type> &ipp, const unsigned int version) {
	boost::serialization::split_free(ar, ipp, version);			
}

template<class Archive>
void save(Archive & ar, const rf_phreaker::raw_signal &sig, const unsigned int version) {
	rf_phreaker::bandwidth_type bandwidth = sig.bandwidth();
	rf_phreaker::frequency_type sampling_rate = sig.sampling_rate();
	rf_phreaker::frequency_type frequency = sig.frequency();
	ar & bandwidth;
	ar & sampling_rate;
	ar & frequency;
	ar & sig.get_iq();
}

template<class Archive>
void load(Archive & ar, rf_phreaker::raw_signal &sig, const unsigned int version) {
	rf_phreaker::bandwidth_type bandwidth = 0;
	rf_phreaker::frequency_type sampling_rate = 0;
	rf_phreaker::frequency_type frequency = 0;
	ar & bandwidth;
	ar & sampling_rate;
	ar & frequency;
	sig.bandwidth(bandwidth);
	sig.sampling_rate(sampling_rate);
	sig.frequency(frequency);
	ar & sig.get_iq();
}

template<class Archive>
void serialize(Archive & ar, rf_phreaker::raw_signal &sig, const unsigned int version) {
	boost::serialization::split_free(ar, sig, version);
}


}}
