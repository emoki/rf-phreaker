#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "helper_structs.h"


namespace cappeen_scanner {

static std::string beagle_delimiter = "\t";
static std::string beagle_spacer = " | ";


template<typename beagle_wrapper> void output_beagle_api_header(std::ostream &f);

std::ostream& operator<<( std::ostream &os, const cappeen_scanner::band_group_type &t);

std::ostream& operator<<( std::ostream &os, const cappeen_scanner::technologies_and_band_group_type &t);

std::ostream& operator<<( std::ostream &os, const cappeen_scanner::neighbor_intra_type &t);

std::ostream& operator<<( std::ostream &os, const cappeen_scanner::neighbor_inter_type &t);

std::ostream& operator<<( std::ostream &os, const cappeen_scanner::gsm_neighbor_inter_rat_type &t);

std::ostream& operator<<(std::ostream &os, const cappeen_scanner::plmns_type &t);

std::ostream& operator<<(std::ostream &os, const cappeen_scanner::umts_sib_18_type &t);

std::ostream& operator<<(std::ostream &os, const cappeen_scanner::lte_sib_1_type &t);

std::ostream& operator<<(std::ostream &os, const cappeen_scanner::beagle_info_wrapper &t);

std::ostream& operator<<( std::ostream &os, const cappeen_scanner::gps_info_wrapper &t);

std::ostream& operator<<(std::ostream &os, const cappeen_scanner::gsm_sector_info_wrapper &t);

std::ostream& operator<<(std::ostream &os, const cappeen_scanner::gsm_sweep_info_wrapper &t);

std::ostream& operator<<(std::ostream &os, const cappeen_scanner::umts_sector_info_wrapper &t);

std::ostream& operator<<( std::ostream &os, const cappeen_scanner::umts_sweep_info_wrapper &t);

std::ostream& operator<<( std::ostream &os, const cappeen_scanner::lte_sector_info_wrapper &t);

std::ostream& operator<<( std::ostream &os, const cappeen_scanner::lte_sweep_info_wrapper &t);

std::ostream& operator<<( std::ostream &os, const cappeen_scanner::api_string &t);

}
