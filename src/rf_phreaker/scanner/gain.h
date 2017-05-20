#pragma once

#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/common/common_types.h"
#include "ipp.h"



namespace rf_phreaker { namespace scanner {

// lna gain (MAX, MID, BYPASS)
// vga1 (dB, min = 5, max = 30)
// vga2 (dB, min = 0, ~max = 30)

struct lna_gain_values {
	lna_gain_values(double bypass, double mid, double max)
		: bypass_(bypass)
		, mid_(mid)
		, max_(max) {}
	lna_gain_values() 
		: bypass_(0)
		, mid_(0)
		, max_(0) {}
	double bypass_;
	double mid_;
	double max_;
};

class gain_type
{
public:
	gain_type() : lna_gain_(lms::LNA_MAX), rxvga1_(30), rxvga2_(0)
	{}

	gain_type(const gain_type &g) : lna_gain_(g.lna_gain_), rxvga1_(g.rxvga1_), rxvga2_(g.rxvga2_)
	{}

	gain_type(lms::lna_gain_enum lna_gain, int rxvga1, int rxvga2)
		: lna_gain_(lna_gain)
		, rxvga1_(rxvga1)
		, rxvga2_(rxvga2)
	{}

	void swap(gain_type &&g)
	{
		std::swap(lna_gain_, g.lna_gain_);
		std::swap(rxvga1_, g.rxvga1_);
		std::swap(rxvga2_, g.rxvga2_);
	}

	gain_type& operator =(gain_type g)
	{
		this->swap(std::move(g));
		return *this;
	}

	bool operator ==(const gain_type &g) const
	{
		return lna_gain_ == g.lna_gain_ && rxvga1_ == g.rxvga1_ && rxvga2_ == g.rxvga2_;
	}

	bool operator !=(const gain_type &g)
	{
		return !operator==(g);
	}

	lms::lna_gain_enum lna_gain_;
	int rxvga1_;
	int rxvga2_;
};

}}