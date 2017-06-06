#pragma once
#include <map>
#include <set>
#include "rf_phreaker/lte_analysis/lte_measurement.h"
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/common/exception_types.h"

namespace rf_phreaker {


//// See 3gpp 36.331 RRC protocol spec - 5.2.3 - Acquisition of an SI message
//	determine the start of the SI - window for the concerned SI message as follows :
//	2> for the concerned SI message, determine the number n which corresponds to the order of entry in the list of
//		SI messages configured by schedulingInfoList in SystemInformationBlockType1;
//	2> determine the integer value x = (n – 1)*w, where w is the si - WindowLength;
//	2> the SI - window starts at the subframe #a, where a = x mod 10, in the radio frame for which SFN mod T =
//		FLOOR(x / 10), where T is the si - Periodicity of the concerned SI message;
//NOTE:  E - UTRAN should configure an SI - window of 1 ms only if all SIs are scheduled before subframe #5 in
//	radio frames for which SFN mod 2 = 0.
struct lte_si_info {
	lte_si_info(const layer_3_information::scheduling_info &scheduling, int n, int si_win)
		: scheduling_info_(scheduling)
		, n_(n)
		, is_decoded_(false)
		, si_window_ms_(si_win) {
		x_ = (n_ - 1) * si_win;
		subframe_ = x_ % 10;
	}

	lte_si_info(const lte_si_info &a) : scheduling_info_(a.scheduling_info_), n_(a.n_), 
		is_decoded_(a.is_decoded_), x_(a.x_), subframe_(a.subframe_), si_window_ms_(a.si_window_ms_) {}

	lte_si_info(lte_si_info &&a) {
		swap(a);
	}

	void swap(lte_si_info &a) {
		std::swap(scheduling_info_, a.scheduling_info_);
		std::swap(n_, a.n_);
		std::swap(is_decoded_, a.is_decoded_);
		std::swap(x_, a.x_);
		std::swap(subframe_, a.subframe_);
		std::swap(si_window_ms_, a.si_window_ms_);
	}

	bool is_relevant_frame(int frame_num) const {
		//return frame_num % (scheduling_info_.periodicity_in_frames_) == (int)std::floor(x_ / 10);
		auto mod_frame = frame_num % scheduling_info_.periodicity_in_frames_;
		auto offset = (int)std::floor(x_ / 10);
		return mod_frame >= offset && mod_frame < offset + std::ceil(si_window_ms_ / 10.0);
	}

	int starting_subframe() const { return subframe_; }

	bool has_wanted_si(const std::set<layer_3_information::lte_sib_type> &wanted) const {
		bool is_wanted = false;
		for(auto &i : scheduling_info_.sib_mapping_info_) {
			if(wanted.find(i) != wanted.end())
				is_wanted = true;
		}
		return is_wanted;
	}

	layer_3_information::scheduling_info scheduling_info_;
	int n_;
	int x_;
	int subframe_;
	int si_window_ms_;
	bool is_decoded_;
};

struct lte_si_info_group {
	lte_si_info_group() : dci_format_(lte_dci_format_unknown), si_window_length_ms_(LTE_NULL) {}

	lte_si_info_group(const lte_si_info_group &a) : g_(a.g_), dci_format_(a.dci_format_), si_window_length_ms_(a.si_window_length_ms_) {}

	lte_si_info_group(lte_si_info_group &&a) {
		swap(a);
	}

	void swap(lte_si_info_group &a) {
		std::swap(dci_format_, a.dci_format_);
		std::swap(si_window_length_ms_, a.si_window_length_ms_);
		std::swap(g_, a.g_);
	}

	lte_si_info_group& operator=(lte_si_info_group a) {
		this->swap(a);
		return *this;
	}

	int si_window_length_ms() const { return si_window_length_ms_; }

	lte_dci_format_type dci_format() const { return dci_format_; }

	static lte_si_info_group create_lte_si_info_group(const lte_measurement &meas) {
		lte_si_info_group group;
		group.si_window_length_ms_ = meas.layer_3_.sib1_.si_window_length_ms_;
		group.dci_format_ = meas.dci_format;
		int n = 1;
		for(auto &s : meas.layer_3_.sib1_.scheduling_info_list_)
			group.g_.push_back(lte_si_info(s, n++, group.si_window_length_ms_));
		return group;
	}

	std::vector<lte_si_info> g_;
	lte_dci_format_type dci_format_;
	int si_window_length_ms_;
};


struct cells_on_channel
{
	typedef int cid_type;
	std::map<cid_type, lte_si_info_group> cells_;

	cells_on_channel() {}

	cells_on_channel(const lte_measurements &measurements) {
		update(measurements);
	}

	void clear() {
		cells_.clear();
	}

	void update(const lte_measurements &measurements) {
		for(auto &meas : measurements) {
			update(meas);
		}
	}

	void update(const lte_measurement &meas) {
		auto it = cells_.find(identifier(meas));
		if(meas.layer_3_.sib1_.is_decoded() && it == cells_.end()) {
			it = cells_.insert(std::make_pair(meas.RsRecord.ID, lte_si_info_group::create_lte_si_info_group(meas))).first;
		}

		if(it != cells_.end() && has_decoded_sib(meas)) {
			for(auto &s : it->second.g_) {
				if(is_decoded(meas, s))
					s.is_decoded_ = true;
			}
		}
	}

	bool has_scheduling_info(const lte_measurement &meas) const {
		return cells_.find(identifier(meas)) != cells_.end();
	}

	lte_si_info_group get_needed_scheduling_info(const lte_measurement &meas, const std::set<layer_3_information::lte_sib_type> &wanted_si) const {
		lte_si_info_group group;
		auto it = cells_.find(identifier(meas));
		if(it != cells_.end()) {
			group.dci_format_ = it->second.dci_format();
			group.si_window_length_ms_ = it->second.si_window_length_ms();
			for(auto &i : it->second.g_) {
				if(!i.is_decoded_ && i.has_wanted_si(wanted_si))
					group.g_.push_back(i);
			}
		}
		return group;
	}

	lte_si_info_group get_all_scheduling_info(const lte_measurement &meas) const {
		lte_si_info_group group;
		auto it = cells_.find(identifier(meas));
		if(it != cells_.end()) {
			group = it->second;
		}
		return group;
	}

	void reset_decoded() {
		for(auto &i : cells_) {
			for(auto &j : i.second.g_)
				j.is_decoded_ = false;
		}

	}

	cells_on_channel::cid_type identifier(const lte_measurement &meas) const {
		return (cid_type)meas.RsRecord.ID;
	}

	bool has_decoded_sib(const lte_measurement &meas) const {
		return meas.layer_3_.sib1_.is_decoded() || meas.layer_3_.sib3_.is_decoded() || meas.layer_3_.sib4_.is_decoded() || meas.layer_3_.sib5_.is_decoded()
			|| meas.layer_3_.sib6_.is_decoded() || meas.layer_3_.sib7_.is_decoded() || meas.layer_3_.sib8_.is_decoded();
	}

	bool is_decoded(const lte_measurement &meas, const lte_si_info &info) {
		using namespace layer_3_information;
		for(auto &i : info.scheduling_info_.sib_mapping_info_) {
			switch(i) {
			case SIB_3:
				return meas.layer_3_.sib3_.is_decoded();
			case SIB_4:
				return meas.layer_3_.sib4_.is_decoded();
			case SIB_5:
				return meas.layer_3_.sib5_.is_decoded();
			case SIB_6:
				return meas.layer_3_.sib6_.is_decoded();
			case SIB_7:
				return meas.layer_3_.sib7_.is_decoded();
			case SIB_8:
				return meas.layer_3_.sib8_.is_decoded();
			default:;
			}
		}
		return false;
	}
};

class si_tracker {
public:
	void set_wanted_si(const std::vector<layer_3_information::lte_sib_type> &wanted_si) {
		wanted_si_.clear();
		for(auto &i : wanted_si)
			wanted_si_.insert(i);
		if(wanted_si_.size() && wanted_si_.find(layer_3_information::lte_sib_type::SIB_1) == wanted_si_.end())
			throw lte_analysis_error("To decode and track LTE SI SIB_1 decoding/tracking is required.");
	}

	std::vector<layer_3_information::lte_sib_type> wanted_si() {
		std::vector<layer_3_information::lte_sib_type> si;
		for(auto &i : wanted_si_)
			si.push_back(i);
		return si;
	}
	void update(frequency_type freq, const lte_measurements &measurements) {
		auto i = freq_group_.find(freq);
		if(i == freq_group_.end())
			i = freq_group_.insert(std::make_pair(freq, cells_on_channel{})).first;
		i->second.update(measurements);
	}

	void update(frequency_type freq, const lte_measurement &measurement) {
		auto i = freq_group_.find(freq);
		if(i == freq_group_.end())
			i = freq_group_.insert(std::make_pair(freq, cells_on_channel{})).first;
		i->second.update(measurement);
	}

	void clear(frequency_type freq) {
		auto i = freq_group_.find(freq);
		if(i != freq_group_.end())
			i->second.clear();
	}

	void clear() {
		freq_group_.clear();
	}

	void reset_decoded() {
		for(auto &i : freq_group_) {
			i.second.reset_decoded();
		}
	}

	bool has_scheduling_info(frequency_type freq, const lte_measurement &meas) {
		auto i = freq_group_.find(freq);
		if(i != freq_group_.end())
			return i->second.has_scheduling_info(meas);
		else
			return false;
	}

	lte_si_info_group get_needed_scheduling_info(frequency_type freq, const lte_measurement &meas) {
		auto i = freq_group_.find(freq);
		if(i != freq_group_.end())
			return i->second.get_needed_scheduling_info(meas, wanted_si_);
		else
			return lte_si_info_group{};
	}

	lte_si_info_group get_all_scheduling_info(frequency_type freq, const lte_measurement &meas) {
		auto i = freq_group_.find(freq);
		if(i != freq_group_.end())
			return i->second.get_all_scheduling_info(meas);
		else
			return lte_si_info_group{};
	}

	std::map<frequency_type, cells_on_channel> freq_group_;
	std::set<layer_3_information::lte_sib_type> wanted_si_;
};


}