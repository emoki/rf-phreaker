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

#include <atomic>
#include "rf_phreaker/gsm_analysis/gsm_measurement.h"
#include "rf_phreaker/gsm_analysis/gsm_config.h"
#include "rf_phreaker/common/raw_signal.h"

namespace rf_phreaker {

	class gsm_analysis_impl;

	class DLL_PUBLIC gsm_analysis
	{
	public:
		gsm_analysis(const gsm_config &config, std::atomic_bool *is_cancelled = nullptr);

		gsm_analysis(const gsm_analysis &analysis);

		~gsm_analysis();

		int cell_search(const rf_phreaker::raw_signal &raw_signal, gsm_measurements &gsm_meas, bool do_octet_decoding = false);

		//int decode_layer_3(const rf_phreaker::raw_signal &raw_signal, gsm_measurements &gsm_meas);

	private:
		gsm_analysis_impl *impl_;
	};

}