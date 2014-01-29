#pragma once

#include "rf_phreaker/umts_analysis/umts_types.h"
#include "ipp.h"
#include <stdint.h>

class cpich_generator
{
public:
	cpich_generator();
	~cpich_generator();
	
	void create_cpich_signal(Ipp32fc *dst, uint32_t cpich_num, uint32_t num_chips = N_TOTAL_CHIPS_CPICH, uint32_t start_chip = 0) const;

protected:
	static const unsigned int m_GOLDCODE_DEGREE = 18;
	static const unsigned int m_GOLDCODE_LEN = (1<<m_GOLDCODE_DEGREE);
	static __int8 *m_Zn[N_CPICH_CODES][2];
};

