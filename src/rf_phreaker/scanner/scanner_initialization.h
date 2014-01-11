#pragma once

#include "rf_phreaker/scanner/scanner_comm.h"

namespace rf_phreaker { namespace scanner {

class scanner_initialization
{
public:
	scanner_initialization(void);

	~scanner_initialization(void);

	void initialize_scanner(scanner_comm &comm);

public:
	void send_lime_recommendations_default(scanner_comm &comm);

	void send_lime_recommendations(scanner_comm &comm, const std::string &filename = "lime_recommendations.txt");
};

}}