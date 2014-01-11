#pragma once

#include "libbladeRF.h"

#include <string>

namespace rf_phreaker {
	namespace scanner {

		class scanner_blade_rf_impl
		{
		public:
			scanner_blade_rf_impl() {};

			scanner_blade_rf_impl(const scanner_blade_rf_impl &impl)
				: dev_info_(impl.dev_info_)
				, usb_speed_(impl.usb_speed_)
				, stats_(impl.stats_)
				, blade_rf_version_(impl.blade_rf_version_)
				, fpga_version_(impl.fpga_version_)
				, firmware_version_(impl.firmware_version_)
				, sampling_(impl.sampling_)
				, vctcxo_trim_(impl.vctcxo_trim_)
			{}

			~scanner_blade_rf_impl() {};

			std::string serial() const
			{
				return dev_info_.serial;
			}
			int back_end() const
			{
				return dev_info_.backend;
			}
			uint8_t usb_bus() const
			{
				return dev_info_.usb_bus;
			}
			uint8_t usb_address() const
			{
				return dev_info_.usb_addr;
			}
			unsigned int instance() const
			{
				return dev_info_.instance;
			}
			uint64_t rx_overruns() const
			{
				return stats_.rx_overruns;
			}
			uint64_t rx_throughput() const // samples/second
			{
				return stats_.rx_throughput;
			}
			uint64_t tx_underruns() const
			{
				return stats_.tx_underruns;
			}
			uint64_t tx_throughput() const // samples/second
			{
				return stats_.tx_throughput;
			}
			uint16_t vctcxo_trim() const
			{
				return vctcxo_trim_;
			}
			int usb_speed() const { return usb_speed_; }

			uint16_t blade_rf_version_major() const
			{
				return blade_rf_version_.major;
			}
			uint16_t blade_rf_version_minor() const
			{
				return blade_rf_version_.minor;
			}
			uint16_t blade_rf_version_patch() const
			{
				return blade_rf_version_.patch;
			}
			std::string blade_rf_version_description() const
			{
				return blade_rf_version_.describe;
			}

			uint16_t fpga_version_major() const
			{
				return fpga_version_.major;
			}
			uint16_t fpga_version_minor() const
			{
				return fpga_version_.minor;
			}
			uint16_t fpga_version_patch() const
			{
				return fpga_version_.patch;
			}
			std::string fpga_version_description() const
			{
				return fpga_version_.describe;
			}

			uint16_t firmware_version_major() const
			{
				return firmware_version_.major;
			}
			uint16_t firmware_version_minor() const
			{
				return firmware_version_.minor;
			}
			uint16_t firmware_version_patch() const
			{
				return firmware_version_.patch;
			}
			std::string firmware_version_description() const
			{
				return firmware_version_.describe;
			}

			struct bladerf_version blade_rf_version_;
			struct bladerf_version fpga_version_;
			struct bladerf_version firmware_version_;
			bladerf_devinfo dev_info_;
			bladerf_dev_speed usb_speed_;
			struct bladerf_stats stats_;
			bladerf_sampling sampling_;
			uint16_t vctcxo_trim_;
		};

	}
}