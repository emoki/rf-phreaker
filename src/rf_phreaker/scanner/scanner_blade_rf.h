#pragma once

#include "rf_phreaker/scanner/scanner.h"
#include "rf_phreaker/common/common_types.h"

#include <memory>
#include <string>

namespace rf_phreaker {
	namespace scanner {

		class scanner_blade_rf_impl;

		class scanner_blade_rf : public scanner
		{
		public:
			scanner_blade_rf(const scanner_blade_rf_impl &impl);

			hardware get_hardware() const;
			std::string scanner_id() const;
			std::string serial() const;
			int back_end() const;
			uint8_t usb_bus() const;
			uint8_t usb_address() const;
			unsigned int instance() const;
			uint64_t rx_overruns() const;
			uint64_t rx_throughput() const; // samples/second
			uint64_t tx_underruns() const;
			uint64_t tx_throughput() const; // samples/second
			uint16_t vctcxo_trim() const;
			int usb_speed() const;

			uint16_t blade_rf_version_major() const;
			uint16_t blade_rf_version_minor() const;
			uint16_t blade_rf_version_patch() const;
			std::string blade_rf_version_description() const;

			uint16_t fpga_version_major() const;
			uint16_t fpga_version_minor() const;
			uint16_t fpga_version_patch() const;
			std::string fpga_version_description() const;

			uint16_t firmware_version_major() const;
			uint16_t firmware_version_minor() const;
			uint16_t firmware_version_patch() const;
			std::string firmware_version_description() const;

		private:
			std::unique_ptr<scanner_blade_rf_impl> impl_;
		};

	}
}