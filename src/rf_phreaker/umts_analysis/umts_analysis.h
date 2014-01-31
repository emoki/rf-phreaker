#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_DLL
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllimport))
#else
#define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#endif
#define DLL_LOCAL
#else
#if __GNUC__ >= 4
#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define DLL_PUBLIC
#define DLL_LOCAL
#endif
#endif

#include "rf_phreaker/umts_analysis/umts_measurement.h"
#include "rf_phreaker/umts_analysis/umts_config.h"
#include "rf_phreaker/common/raw_signal.h"

class umts_analysis_impl;


class DLL_PUBLIC umts_analysis
{
public:
	umts_analysis();
	
	~umts_analysis();

	int cell_search(const rf_phreaker::raw_signal &raw_signal, umts_measurement *umts_meas, int &num_umts_meas, uint32_t num_cpich_chips, umts_scan_type scan_type);

	int decode_layer_3(const rf_phreaker::raw_signal &raw_signal, umts_measurement &umts_meas);
	
	void set_config(const umts_config &config);

private:
	umts_analysis_impl *impl_;
};