#include "gtest/gtest.h"
#include <iostream>
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "rf_phreaker/gsm_analysis/gsm_analysis_interface.h"
#include "rf_phreaker/common/raw_signal.h"
#include "rf_phreaker/common/common_serialization.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/scanner/measurement_info_serialization.h"
#include "rf_phreaker/common/ipp_array.h"
#include "rf_phreaker/common/frequency_bin_calculator.h"
#include "rf_phreaker/common/ipp_helper.h"


using namespace rf_phreaker;

void PrintRows(const gsm_analysis_output_list *head_row) {
	const gsm_analysis_output_list *current = head_row;
	unsigned int num_rows = 0;
	while(current != NULL) {
		num_rows++;
		printf("\nRow %d:\nIF: %04d Hz, ChannelPow=%.2f, BandPow=%.2f, F_Win=%03d, C/I= %.2f, BSIC=%d, RMSCorrPower=%f\n",
			num_rows,
			current->data.IFFreq,
			20*log10(sqrt(current->data.ChannelPower)),
			current->data.BandPow,
			current->data.FCCH_Win,
			10 * log10(current->data.C_I_Ratio),
			current->data.BSIC,
			20*log10(current->data.RMSCorrPower)
			);
		if(current->data.MeasurementInfo & GsmAnalysisMeasurementInfoMask::BcchBurstDecoded) {
			printf("BCCH decoded\n");
		}
		if(current->data.MeasurementInfo & GsmAnalysisMeasurementInfoMask::CGIDecoded) {
			printf("CGI Info: %d\t%d\t%d\t%d\n\n",
				current->data.MCC,
				current->data.MNC,
				current->data.LAC,
				current->data.CellID);
		}
		current = current->next;
	}
}

TEST(GsmInterfaceTests, TestGeneral) {
	try {
		const unsigned int GSM_ANALYSIS_DATA_LENGTH = 250000;
		ipp_32fc_array gsm_data(GSM_ANALYSIS_DATA_LENGTH);
		//Ipp32fc gsm_data[GSM_ANALYSIS_DATA_LENGTH];
		//	std::ifstream gsm_data_file("..\\Wind3G_005.dat", std::ios_base::binary | std::ios_base::in);
		std::ifstream gsm_data_file("../../../../rf_phreaker/test_files/GSM4875.dat", std::ios_base::binary | std::ios_base::in);
		if(gsm_data_file.fail()) {
			printf("Opening file failed\n");
		}
		unsigned int data_len = GSM_ANALYSIS_DATA_LENGTH;
		short data_complex[2];
		for(unsigned int idx = 0; idx<GSM_ANALYSIS_DATA_LENGTH; idx++) {
			gsm_data_file.read(reinterpret_cast<char *>(data_complex), sizeof(data_complex));
			if(gsm_data_file.gcount() != (sizeof data_complex))
				throw - 1;
			gsm_data[idx].re = (Ipp32f)data_complex[0];
			gsm_data[idx].im = (Ipp32f)data_complex[1];
		}
		gsm_data_file.close();
		gsm_analysis_output_list *head_row = NULL;
		gsm_processor processor(false);
		processor.GsmAnalysis(gsm_data.get(), gsm_data.length(), &head_row, 25, 5, 100000);
		PrintRows(head_row);

		frequency_bin_calculator calc;
		//calc.calculate_power_in_bins(gsm_data, 4875000, khz(100), 32768);
		//auto avg_rms = ipp_helper::calculate_average_rms(gsm_data.get(), 32768);
		

		ipp_32fc_array tmp(/*262144*/131072);
		tmp.zero_out();
		tmp.copy(gsm_data.get(), 131072/*gsm_data.length()*/);
		calc.calculate_power_in_bins(tmp, 4875000, khz(100), 131072);
		auto avg_rms = ipp_helper::calculate_average_rms(tmp.get(), 131072);

		int i = 100000;
		double p = calc.get_power_in_bin(i);
		auto pdb = 20 * log10(p);
		int j = 0;

		

		processor.GsmClearOutput(head_row);
		head_row = NULL;
		data_len = 100000;
		gsm_processor sweeper(true, gsm_data.length());
		sweeper.GsmAnalysis(gsm_data.get(), gsm_data.length(), &head_row, 100, 15, 00000);
		PrintRows(head_row);
		sweeper.GsmClearOutput(head_row);
	}
	catch(const std::exception &err) {
		std::cout << "gsm_analysis_gtests exception:  " << err.what() << std::endl;
	}
}