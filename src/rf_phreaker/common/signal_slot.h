#pragma once

#include <vector>
#include <boost/signals2.hpp>
#include "rf_phreaker/common/measurements.h"


namespace rf_phreaker {
	
typedef boost::signals2::signal<void(const hardware&)> hardware_signal_type;
typedef boost::signals2::signal<void(const gps&)> gps_signal_type;
typedef boost::signals2::signal<void(const basic_data&)> basic_signal_type;
typedef boost::signals2::signal<void(const std::vector<gsm_data>&, const basic_data&)> gsm_signal_type;
typedef boost::signals2::signal<void(const std::vector<umts_data>&, const basic_data&)> umts_signal_type;
typedef boost::signals2::signal<void(const std::vector<lte_data>&, const basic_data&)> lte_signal_type;
typedef boost::signals2::signal<void(const basic_data&, const std::vector<gsm_data>&)> gsm_sweep_signal_type;
typedef boost::signals2::signal<void(const basic_data&, const std::vector<umts_data>&)> umts_sweep_signal_type;
typedef boost::signals2::signal<void(const basic_data&, const std::vector<lte_data>&)> lte_sweep_signal_type;
typedef boost::signals2::signal<void(const basic_data&, const std::vector<gsm_data>&,
	const std::vector<umts_data>&, const std::vector<lte_data>&)> sweep_signal_type;

typedef hardware_signal_type::slot_type hardware_slot_type;
typedef gps_signal_type::slot_type gps_slot_type;
typedef basic_signal_type::slot_type basic_slot_type;
typedef gsm_signal_type::slot_type gsm_slot_type;
typedef umts_signal_type::slot_type umts_slot_type;
typedef lte_signal_type::slot_type lte_slot_type;
typedef sweep_signal_type::slot_type sweep_slot_type;

}