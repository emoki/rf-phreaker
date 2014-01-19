#pragma once

#include "rf_phreaker/scanner/comm_info.h"
#include "libbladeRF.h"

namespace rf_phreaker {
	namespace scanner {

		class comm_blade_rf : public comm_info
		{
		public:
            comm_blade_rf() : blade_rf_(nullptr), is_open_(false) {}

			comm_blade_rf(bladerf_devinfo &blade)
				: blade_rf_(nullptr)
				, is_open_(false)
			{
				memcpy(&device_info_, &blade, sizeof(bladerf_devinfo));
			}

			comm_blade_rf(bladerf_devinfo &blade, bladerf *blade_rf)
				: blade_rf_(blade_rf)
				, is_open_(false)
			{
				memcpy(&device_info_, &blade, sizeof(bladerf_devinfo));
			}

			virtual scanner_id_type id() const
			{
				return device_info_.serial;
			}

			virtual std::string description() const
			{
				return device_info_.serial;
			}

			virtual bool is_open() const
			{
				return is_open_;
			}

			virtual comm_type type() const
			{
				return USB_BLADE_RF;
			}

			bladerf *blade_rf() const
			{
				return blade_rf_;
			}

			bladerf_devinfo device_info_;

			bladerf *blade_rf_;

			bool is_open_;

		};
	}
}
