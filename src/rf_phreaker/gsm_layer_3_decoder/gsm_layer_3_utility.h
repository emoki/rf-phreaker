#pragma once
#include <vector>
#include "rf_phreaker/gsm_layer_3_library/ed_lib.h"
#include "rf_phreaker/gsm_layer_3_library/bitencode.h"
#include "rf_phreaker/gsm_layer_3_library/ed_c_recog_RR.h"
#include "rf_phreaker/gsm_layer_3_library/RRPLENDownlink_RR.h"
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"

namespace layer_3_information {

class gsm_layer_3_utility {
public:
	static int smod(int n, int m) {
		int32_t val;
		val = n % m;
		if(val <= 0)
			val += m;
		return val;
	}

	static void decode_bcch_cell_channels(const c_CellChannel& cell_des, std::vector<bcch_neighbor> &neighbors) {
		switch(cell_des.Present) {
		case U_c_CellChannel_BitMap0:
			for(int i = 0; i < cell_des.u.BitMap0->items; ++i) {
				if(cell_des.u.BitMap0->data[i])
					neighbors.push_back(-(i - 124));
			}
			break;
		case U_c_CellChannel_Range1024: {
			auto w = cell_des.u.Range1024->W.data;
			auto count = 0;
			if(count++ < cell_des.u.Range1024->W.items && w[0])
				neighbors.push_back(w[0]);
			if(count++ < cell_des.u.Range1024->W.items && w[1])
				neighbors.push_back(smod(w[0] - 512 + w[1], 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[2])
				neighbors.push_back(smod(w[0] + w[2], 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[3])
				neighbors.push_back(smod(w[0] - 512 + smod(w[1] - 256 + w[3], 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[4])
				neighbors.push_back(smod(w[0] + smod(w[2] - 256 + w[4], 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[5])
				neighbors.push_back(smod(w[0] - 512 + smod(w[1] + w[5], 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[6])
				neighbors.push_back(smod(w[0] + smod(w[2] + w[6], 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[7])
				neighbors.push_back(smod(w[0] - 512 + smod(w[1] - 256 + smod(w[3] - 128 + w[7], 255), 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[8])
				neighbors.push_back(smod(w[0] + smod(w[2] - 256 + smod(w[4] - 128 + w[8], 255), 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[9])
				neighbors.push_back(smod(w[0] - 512 + smod(w[1] + smod(w[5] - 128 + w[9], 255), 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[10])
				neighbors.push_back(smod(w[0] + smod(w[2] + smod(w[6] - 128 + w[10], 255), 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[11])
				neighbors.push_back(smod(w[0] - 512 + smod(w[1] - 256 + smod(w[3] + w[11], 255), 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[12])
				neighbors.push_back(smod(w[0] + smod(w[2] - 256 + smod(w[4] + w[12], 255), 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[13])
				neighbors.push_back(smod(w[0] - 512 + smod(w[1] + smod(w[5] + w[13], 255), 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[14])
				neighbors.push_back(smod(w[0] + smod(w[2] + smod(w[6] + w[14], 255), 511), 1023));
			if(count++ < cell_des.u.Range1024->W.items && w[15])
				neighbors.push_back(smod(w[0] - 512 + smod(w[1] - 256 + smod(w[3] - 128 + smod(w[7] - 64 + w[15], 127), 255), 511), 1023));
		}
										break;
		case U_c_CellChannel_Range512: {
			auto orig = cell_des.u.Range512->OrigARFCN;
			auto w = cell_des.u.Range512->W.data;
			auto count = 0;
			if(count++ < cell_des.u.Range512->W.items && w[0])
				neighbors.push_back((orig + w[0]) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[1])
				neighbors.push_back((orig + smod(w[0] - 256 + w[1], 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[2])
				neighbors.push_back((orig + smod(w[0] + w[2], 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[3])
				neighbors.push_back((orig + smod(w[0] - 256 + smod(w[1] - 128 + w[3], 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[4])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 128 + w[4], 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[5])
				neighbors.push_back((orig + smod(w[0] - 256 + smod(w[1] + w[5], 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[6])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + w[6], 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[7])
				neighbors.push_back((orig + smod(w[0] - 256 + smod(w[1] - 128 + smod(w[3] - 64 + w[7], 127), 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[8])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 128 + smod(w[4] - 64 + w[8], 127), 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[9])
				neighbors.push_back((orig + smod(w[0] - 256 + smod(w[1] + smod(w[5] - 64 + w[9], 127), 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[10])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + smod(w[6] - 64 + w[10], 127), 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[11])
				neighbors.push_back((orig + smod(w[0] - 256 + smod(w[1] - 128 + smod(w[3] + w[11], 127), 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[12])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 128 + smod(w[4] + w[12], 127), 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[13])
				neighbors.push_back((orig + smod(w[0] - 256 + smod(w[1] + smod(w[5] + w[13], 127), 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[14])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + smod(w[6] + w[14], 127), 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[15])
				neighbors.push_back((orig + smod(w[0] - 256 + smod(w[1] - 128 + smod(w[3] - 64 + smod(w[7] - 32 + w[15], 63), 127), 255), 511)) % 1024);
			if(count++ < cell_des.u.Range512->W.items && w[16])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 128 + smod(w[4] - 64 + smod(w[8] - 32 + w[16], 63), 127), 255), 511)) % 1024);

		}
									   break;
		case U_c_CellChannel_Range256: {
			auto orig = cell_des.u.Range256->OrigARFCN;
			auto w = cell_des.u.Range256->W.data;
			auto count = 0;
			if(count++ < cell_des.u.Range256->W.items && w[0])
				neighbors.push_back((orig + w[0]) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[1])
				neighbors.push_back((orig + smod(w[0] - 128 + w[1], 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[2])
				neighbors.push_back((orig + smod(w[0] + w[2], 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[3])
				neighbors.push_back((orig + smod(w[0] - 128 + smod(w[1] - 64 + w[3], 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[4])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 64 + w[4], 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[5])
				neighbors.push_back((orig + smod(w[0] - 128 + smod(w[1] + w[5], 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[6])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + w[6], 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[7])
				neighbors.push_back((orig + smod(w[0] - 128 + smod(w[1] - 64 + smod(w[3] - 32 + w[7], 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[8])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 64 + smod(w[4] - 32 + w[8], 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[9])
				neighbors.push_back((orig + smod(w[0] - 128 + smod(w[1] + smod(w[5] - 32 + w[9], 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[10])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + smod(w[6] - 32 + w[10], 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[11])
				neighbors.push_back((orig + smod(w[0] - 128 + smod(w[1] - 64 + smod(w[3] + w[11], 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[12])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 64 + smod(w[4] + w[12], 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[13])
				neighbors.push_back((orig + smod(w[0] - 128 + smod(w[1] + smod(w[5] + w[13], 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[14])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + smod(w[6] + w[14], 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[15])
				neighbors.push_back((orig + smod(w[0] - 128 + smod(w[1] - 64 + smod(w[3] - 32 + smod(w[7] - 16 + w[15], 31), 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[16])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 64 + smod(w[4] - 32 + smod(w[8] - 16 + w[16], 31), 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[17])
				neighbors.push_back((orig + smod(w[0] - 128 + smod(w[1] + smod(w[5] - 32 + smod(w[9] - 16 + w[17], 31), 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[18])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + smod(w[6] - 32 + smod(w[10] - 16 + w[18], 31), 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[19])
				neighbors.push_back((orig + smod(w[0] - 128 + smod(w[1] - 64 + smod(w[3] + smod(w[11] - 16 + w[19], 31), 63), 127), 255)) % 1024);
			if(count++ < cell_des.u.Range256->W.items && w[20])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 64 + smod(w[4] + smod(w[12] - 16 + w[20], 31), 63), 127), 255)) % 1024);
		}
									   break;
		case U_c_CellChannel_Range128: {
			auto orig = cell_des.u.Range128->OrigARFCN;
			auto w = cell_des.u.Range128->W.data;
			auto count = 0;
			if(count++ < cell_des.u.Range128->W.items && w[0])
				neighbors.push_back((orig + w[0]) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[1])
				neighbors.push_back((orig + smod(w[0] - 64 + w[1], 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[2])
				neighbors.push_back((orig + smod(w[0] + w[2], 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[3])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] - 32 + w[3], 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[4])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 32 + w[4], 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[5])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] + w[5], 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[6])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + w[6], 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[7])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] - 32 + smod(w[3] - 16 + w[7], 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[8])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 32 + smod(w[4] - 16 + w[8], 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[9])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] + smod(w[5] - 16 + w[9], 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[10])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + smod(w[6] - 16 + w[10], 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[11])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] - 32 + smod(w[3] + w[11], 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[12])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 32 + smod(w[4] + w[12], 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[13])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] + smod(w[5] + w[13], 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[14])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + smod(w[6] + w[14], 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[15])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] - 32 + smod(w[3] - 16 + smod(w[7] - 8 + w[15], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[16])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 32 + smod(w[4] - 16 + smod(w[8] - 8 + w[16], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[17])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] + smod(w[5] - 16 + smod(w[9] - 8 + w[17], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[18])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + smod(w[6] - 16 + smod(w[10] - 8 + w[18], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[19])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] - 32 + smod(w[3] + smod(w[11] - 8 + w[19], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[20])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 32 + smod(w[4] + smod(w[12] - 8 + w[20], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[21])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] + smod(w[5] + smod(w[13] - 8 + w[21], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[22])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + smod(w[6] + smod(w[14] - 8 + w[22], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[23])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] - 32 + smod(w[3] - 16 + smod(w[7] + w[23], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[24])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] - 32 + smod(w[4] - 16 + smod(w[8] + w[24], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[25])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] + smod(w[5] - 16 + smod(w[9] + w[25], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[26])
				neighbors.push_back((orig + smod(w[0] + smod(w[2] + smod(w[6] - 16 + smod(w[10] + w[26], 15), 31), 63), 127)) % 1024);
			if(count++ < cell_des.u.Range128->W.items && w[27])
				neighbors.push_back((orig + smod(w[0] - 64 + smod(w[1] - 32 + smod(w[3] + smod(w[11] + w[27], 15), 31), 63), 127)) % 1024);
		}
									   break;
		case U_c_CellChannel_Variable: {
			for(int i = 0; i < cell_des.u.Variable->RRFCN.items; ++i) {
				if(cell_des.u.Variable->RRFCN.data[i])
					neighbors.push_back((cell_des.u.Variable->OrigARFCN + i % 1024));
			}
		}
									   break;
		case U_c_CellChannel_NONE:
		default:
			;
		}
	}

	static utran_bandwidth_type determine_utran_bandwidth(unsigned char bw) {
		switch(bw) {
		case 0x000:
			return utran_3_84_mcps;
		case 0x001:
			return utran_1_24_mcps;
		default:
			return (utran_bandwidth_type)bw; // Any other value is considered correct and should be used as a binary number.
		}
	}

	static void decode_utran_neighbors(const _c_SI2terRestOctets_UTRAN_FDD_Description &des, std::vector<utran_neighbor> &utran) {
		utran_neighbor n;
		n.duplexing_ = fdd;
		if(des.Bandwidth_FDD_Present)
			n.bandwidth_ = determine_utran_bandwidth(des.Bandwidth_FDD);
		else
			n.bandwidth_ = utran_default_mcps;
		n.arfcn_ = des.FDD_ARFCN;
		utran.push_back(n);
	}

	static void decode_utran_neighbors(const _c_SI2quaterRestOctets_p3G_Neighbour_Cell_Description_UTRAN_FDD_Description &des, std::vector<utran_neighbor> &utran) {
		auto &arfcns = des.Repeated_UTRAN_FDD_Neighbour_Cells;
		for(int i = 0; i < arfcns.items; ++i) {
			utran_neighbor n;
			n.duplexing_ = fdd;
			if(des.Bandwidth_FDD_Present)
				n.bandwidth_ = determine_utran_bandwidth(des.Bandwidth_FDD);
			else
				n.bandwidth_ = utran_default_mcps;
			n.arfcn_ = arfcns.data[i]->FDD_ARFCN;
			auto &cells = arfcns.data[i]->FDD_CELL_INFORMATION_Field;
			for(int j = 0; j < cells.items; ++j) {
				n.scrambling_codes_.push_back(cells.data[j]->ScramblingCode);
			}
			utran.push_back(n);
		}
	}

	static void decode_utran_neighbors(const _c_SI2terRestOctets_UTRAN_TDD_Description &des, std::vector<utran_neighbor> &utran) {
		utran_neighbor n;
		n.duplexing_ = tdd;
		if(des.Bandwidth_TDD_Present)
			n.bandwidth_ = determine_utran_bandwidth(des.Bandwidth_TDD);
		else
			n.bandwidth_ = utran_default_mcps;
		if(des.Bandwidth_TDD_Present)
			n.arfcn_ = des.TDD_ARFCN;
		else
			n.arfcn_ = -1;
		utran.push_back(n);
	}

	static void decode_utran_neighbors(const _c_SI2quaterRestOctets_p3G_Neighbour_Cell_Description_UTRAN_TDD_Description &des, std::vector<utran_neighbor> &utran) {
		auto &arfcns = des.Repeated_UTRAN_TDD_Neighbour_Cells;
		for(int i = 0; i < arfcns.items; ++i) {
			utran_neighbor n;
			n.duplexing_ = tdd;
			if(des.Bandwidth_TDD_Present)
				n.bandwidth_ = determine_utran_bandwidth(des.Bandwidth_TDD);
			else
				n.bandwidth_ = utran_default_mcps;
			if(arfcns.data[i]->TDD_ARFCN_INDEX_Present)
				n.arfcn_ = arfcns.data[i]->TDD_ARFCN;
			else
				n.arfcn_ = -1;
			auto &cells = arfcns.data[i]->TDD_CELL_INFORMATION_Field;
			for(int j = 0; j < cells.items; ++j) {
				n.scrambling_codes_.push_back(cells.data[j]);
			}
			utran.push_back(n);
		}
	}

	static eutran_bandwidth_type determine_eutran_bandwidth(unsigned char bw) {
		switch(bw) {
		case 0x000:
			return num_resource_blocks_6;
		case 0x001:
			return num_resource_blocks_15;
		case 0x010:
			return num_resource_blocks_25;
		case 0x011:
			return num_resource_blocks_50;
		case 0x100:
			return num_resource_blocks_75;
		case 0x101:
		default: // Spec states for other values num_resource_blocks_100 is used.
			return num_resource_blocks_100;
		}
	}
	
	static void decode_eutran_neighbors(const _c_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_E_UTRAN_Parameters_Description &des, std::vector<eutran_neighbor> &eutran) {
		std::vector<eutran_neighbor> nieghbors;
		for(int i = 0; i < des.Repeated_E_UTRAN_Neighbour_Cells.items; ++i) {
			auto repeated = des.Repeated_E_UTRAN_Neighbour_Cells.data[i];
			for(int j = 0; j < repeated->cell.items; ++j) {
				eutran_neighbor n;
				n.earfcn_ = repeated->cell.data[i]->EARFCN;
				if(repeated->cell.data[i]->Measurement_Bandwidth_Present)
					n.bandwidth_ = determine_eutran_bandwidth(repeated->cell.data[i]->Measurement_Bandwidth);
				else
					n.bandwidth_ = num_resource_blocks_6;
				nieghbors.push_back(n);
			}
		}
		// If no index is preset in the not_allowed then it is applicable to all eutran freqs.
		for(int i = 0; i < des.Repeated_E_UTRAN_Not_Allowed_Cells.items; ++i) {
			auto not_allowed_ie = des.Repeated_E_UTRAN_Not_Allowed_Cells.data[i];
			std::vector<int32_t> allowed;
			std::vector<int32_t> not_allowed;
			
			// Handle regular pcids.
			for(int j = 0; j < not_allowed_ie->Not_Allowed_Cells.PCID.items; ++j) {
				not_allowed.push_back(not_allowed_ie->Not_Allowed_Cells.PCID.data[j]);
			}

			// Handle pcid bitmaps.
			if(not_allowed_ie->Not_Allowed_Cells.PCID_BITMAP_GROUP_Present) {
				for(int n = 0; n < 6; ++n) {
					auto mask = 1 << n;
					if((not_allowed_ie->Not_Allowed_Cells.PCID_BITMAP_GROUP & mask) == 0) {
						for(int k = 0; k < 83; ++k) {
							not_allowed.push_back(k * n);
						}
					}
					else {
						for(int k = 0; k < 83; ++k) {
							allowed.push_back(k * n);
						}
					}
				}
			}

			//// Handle bitpatterns.
			auto pat = not_allowed_ie->Not_Allowed_Cells.PCID_Pattern;
			auto p_sense = not_allowed_ie->Not_Allowed_Cells.PCID_pattern_sense;
			auto p_length = not_allowed_ie->Not_Allowed_Cells.PCID_Pattern_length;
			if(p_length.items || pat.items) {
				if(pat.items != p_sense.items || pat.items != p_length.items) {
					std::wcerr << "GSM PCID GROUP IE items do have the same length! Skipping group.\n";
					break;
				}
				for(int j = 0; j < pat.items; ++j) {
					// All pcids do NOT match are selected.
					if(p_sense.data[j]) {
						auto mask = *pat.data[j]->value << (7 - p_length.data[j]);
						for(int k = 0; k < 504; ++k) {
							if((mask & k) == mask)
								not_allowed.push_back(k);
						}
					}
					// All pcids that match are selected.
					else {
						for(int k = 0; k < 504; ++k) {
							auto mask = *pat.data[j]->value << (7 - p_length.data[j]);
							for(int k = 0; k < 504; ++k) {
								if((mask & k) != mask)
									not_allowed.push_back(k);
							}
						}
					}
				}
			}

			if(not_allowed_ie->E_UTRAN_FREQUENCY_INDEX.items == 0) {
				// This applies to all eutran freqs.
				for(auto &j : nieghbors) {
					for(auto &k : not_allowed)
						j.pcids_not_allowed_.push_back(k);
					for(auto &k : allowed)
						j.pcids_allowed_.push_back(k);
				}
			}
			else{
				for(int j = 0; j < not_allowed_ie->E_UTRAN_FREQUENCY_INDEX.items; ++j) {
					auto index = not_allowed_ie->E_UTRAN_FREQUENCY_INDEX.data[j];
					if(index < nieghbors.size()) {
						for(auto &k : not_allowed)
							nieghbors[index].pcids_not_allowed_.push_back(k);
						for(auto &k : allowed)
							nieghbors[index].pcids_allowed_.push_back(k);
					}
				}
			}
		}
		for(int i = 0; i < des.Repeated_E_UTRAN_PCID_to_TA_mapping.items; ++i) {
			auto ta_mapping = des.Repeated_E_UTRAN_PCID_to_TA_mapping.data[i];
			std::vector<std::vector<int32_t>> same_tas;
			std::vector<std::vector<int32_t>> different_tas;

			for(int j = 0; j < ta_mapping->PCID_to_TA_mapping.items; ++j) {
				auto ta_mapping_item = ta_mapping->PCID_to_TA_mapping.data[j];

				std::vector<int32_t> same_ta_group;
				std::vector<int32_t> different_ta_group;

				// Handle regular pcids.
				for(int j = 0; j < ta_mapping_item->PCID.items; ++j) {
					same_ta_group.push_back(ta_mapping_item->PCID.data[j]);
				}

				// Handle pcid bitmaps.
				if(ta_mapping_item->PCID_BITMAP_GROUP_Present) {
					for(int n = 0; n < 6; ++n) {
						auto mask = 1 << n;
						if((ta_mapping_item->PCID_BITMAP_GROUP & mask) == 0) {
							for(int k = 0; k < 83; ++k) {
								different_ta_group.push_back(k * n);
							}
						}
						else {
							for(int k = 0; k < 83; ++k) {
								same_ta_group.push_back(k * n);
							}
						}
					}
				}

				//// Handle bitpatterns.
				auto pat = ta_mapping_item->PCID_Pattern;
				auto p_sense = ta_mapping_item->PCID_pattern_sense;
				auto p_length = ta_mapping_item->PCID_Pattern_length;
				if(p_length.items || pat.items) {
					if(pat.items != p_sense.items || pat.items != p_length.items) {
						std::wcerr << "GSM PCID GROUP IE items do have the same length! Skipping group.\n";
						break;
					}
					for(int j = 0; j < pat.items; ++j) {
						// All pcids do NOT match are selected.
						if(p_sense.data[j]) {
							auto mask = *pat.data[j]->value << (7 - p_length.data[j]);
							for(int k = 0; k < 504; ++k) {
								if((mask & k) == mask)
									same_ta_group.push_back(k);
							}
						}
						// All pcids that match are selected.
						else {
							for(int k = 0; k < 504; ++k) {
								auto mask = *pat.data[j]->value << (7 - p_length.data[j]);
								for(int k = 0; k < 504; ++k) {
									if((mask & k )!= mask)
										same_ta_group.push_back(k);
								}
							}
						}
					}
				}

				same_tas.push_back(same_ta_group);
				different_tas.push_back(different_ta_group);
			}

			if(ta_mapping->E_UTRAN_FREQUENCY_INDEX.items == 0) {
				// This applies to all eutran freqs.
				for(auto &j : nieghbors) {
					for(auto &k : same_tas)
						j.pcids_same_tracking_area_.push_back(k);
					for(auto &k : different_tas)
						j.pcids_different_tracking_area_.push_back(k);
				}
			}
			else {
				for(int j = 0; j < ta_mapping->E_UTRAN_FREQUENCY_INDEX.items; ++j) {
					auto index = ta_mapping->E_UTRAN_FREQUENCY_INDEX.data[j];
					if(index < nieghbors.size()) {
						for(auto &k : same_tas)
							nieghbors[index].pcids_same_tracking_area_.push_back(k);
						for(auto &k : different_tas)
							nieghbors[index].pcids_different_tracking_area_.push_back(k);
					}
				}
			}
		}
	}
};

}