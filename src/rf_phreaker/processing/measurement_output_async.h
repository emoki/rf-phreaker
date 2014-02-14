#pragma once
#include "rf_phreaker/processing/measurement_output.h"
#include "rf_phreaker/common/concurrent.h"

namespace rf_phreaker { namespace processing {



class measurement_output_async
{
public:
	measurement_output_async()
	{}

	measurement_output_async(measurement_output_async &&meas)
	{}

	template<typename Data>
	void output(const Data &data)
	{
		out_([=](measurement_output &out) {
			out.output(data);
		});
	}

	//void output_umts(const umts_measurements &data)
	//{
	//	out_([&](measurement_output &out) {
	//		out.output_umts(data);
	//	}
	//}

	//void output_lte(const lte_measurements &data)
	//{
	//	out_([&](measurement_output &out) {
	//		out.output_lte(data);
	//	}
	//}


	//void output_basic_tech(const basic_data &data){
	//	out_([&](measurement_output &out) {
	//		out.output_basic_tech(data);
	//	}
	//}

	//void output_umts(const umts_data &data){
	//	out_([&](measurement_output &out) {
	//		out.output_umts(data);
	//	}
	//}

	//void output_lte(const lte_data &data){
	//	out_([&](measurement_output &out) {
	//		out.output_lte(data);
	//	}
	//}

private:
	concurrent<measurement_output> out_;
};





}}