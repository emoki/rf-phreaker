#pragma once

#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/scanner/eeprom.h"
#include "libbladeRF.h"

#include <string>

namespace rf_phreaker { namespace scanner {

class scanner_blade_rf_impl
{
public:
	scanner_blade_rf_impl()
		: usb_speed_(BLADERF_DEVICE_SPEED_UNKNOWN) {}

	scanner_blade_rf_impl(const scanner_blade_rf_impl &impl)
		: blade_rf_version_(impl.blade_rf_version_)
		, fpga_version_(impl.fpga_version_)
		, firmware_version_(impl.firmware_version_)
		, dev_info_(impl.dev_info_)
		, usb_speed_(impl.usb_speed_)
		//, stats_(impl.stats_)
		, sampling_(impl.sampling_)
		, vctcxo_trim_value_(impl.vctcxo_trim_value_)
		, rx_timeout_(impl.rx_timeout_)
		, eeprom_(impl.eeprom_) {}

	~scanner_blade_rf_impl() {};

	scanner_blade_rf_impl& operator =(const scanner_blade_rf_impl &impl) {
		blade_rf_version_ = impl.blade_rf_version_;
		fpga_version_ = impl.fpga_version_;
		firmware_version_ = impl.firmware_version_;
		dev_info_ = impl.dev_info_;
		usb_speed_ = impl.usb_speed_;
		//stats_ = impl.stats_;
		sampling_ = impl.sampling_;
		vctcxo_trim_value_ = impl.vctcxo_trim_value_;
		rx_timeout_ = impl.rx_timeout_;
		eeprom_ = impl.eeprom_;
		return *this;
	}

	hardware get_hardware() const {
		rf_phreaker::hardware hw;
		switch(usb_speed_) {
		case BLADERF_DEVICE_SPEED_HIGH:
			hw.device_speed_ = USB_HI_SPEED;
			break;
		case BLADERF_DEVICE_SPEED_SUPER:
			hw.device_speed_ = USB_SUPER_SPEED;
			break;
		case BLADERF_DEVICE_SPEED_UNKNOWN:
		default:
			hw.device_speed_ = UNKNOWN_SPEED;
		}
		hw.scanner_id_ = serial();
		hw.frequency_correction_calibration_date_ = get_frequency_correction_date();
		hw.rf_calibration_date_ = eeprom_.cal_.rf_board_calibration_date_;
		
		for(auto rf_switch : eeprom_.cal_.rf_switches_) {
			if(rf_switch.second.identifier_)
				hw.frequency_paths_.push_back(rf_switch.second.path_);
		}
		
		return hw;
	}
	time_t get_rf_calibration_date() const {
		return eeprom_.cal_.rf_board_calibration_date_;
	}
	uint32_t get_frequency_correction_value() const {
		return eeprom_.cal_.nuand_freq_correction_value_;
	}
	time_t get_frequency_correction_date() const {
		return eeprom_.cal_.nuand_freq_correction_date_;
	}
	void set_frequency_correction_value(uint32_t freq_correction_value) {
		eeprom_.cal_.nuand_freq_correction_value_ = freq_correction_value;
	}
	void set_frequency_correction_date(time_t freq_correction_date) {
		eeprom_.cal_.nuand_freq_correction_date_ = freq_correction_date;
	}


	std::string serial() const {
		return dev_info_.serial;
	}
	int back_end() const {
		return dev_info_.backend;
	}
	uint8_t usb_bus() const {
		return dev_info_.usb_bus;
	}
	uint8_t usb_address() const {
		return dev_info_.usb_addr;
	}
	unsigned int instance() const {
		return dev_info_.instance;
	}
	uint16_t vctcxo_trim() const {
		return vctcxo_trim_value_;
	}
	int usb_speed() const { return usb_speed_; }

	uint16_t blade_rf_version_major() const {
		return blade_rf_version_.major;
	}
	uint16_t blade_rf_version_minor() const {
		return blade_rf_version_.minor;
	}
	uint16_t blade_rf_version_patch() const {
		return blade_rf_version_.patch;
	}
	std::string blade_rf_version_description() const {
		return blade_rf_version_.describe;
	}

	uint16_t fpga_version_major() const {
		return fpga_version_.major;
	}
	uint16_t fpga_version_minor() const {
		return fpga_version_.minor;
	}
	uint16_t fpga_version_patch() const {
		return fpga_version_.patch;
	}
	std::string fpga_version_description() const {
		return fpga_version_.describe;
	}

	uint16_t firmware_version_major() const {
		return firmware_version_.major;
	}
	uint16_t firmware_version_minor() const {
		return firmware_version_.minor;
	}
	uint16_t firmware_version_patch() const {
		return firmware_version_.patch;
	}
	std::string firmware_version_description() const {
		return firmware_version_.describe;
	}
	unsigned int receive_timeout() const {
		return rx_timeout_;
	}

	struct bladerf_version blade_rf_version_;
	struct bladerf_version fpga_version_;
	struct bladerf_version firmware_version_;
	bladerf_devinfo dev_info_;
	bladerf_dev_speed usb_speed_;
	//struct bladerf_stats stats_;
	bladerf_sampling sampling_;
	uint16_t vctcxo_trim_value_;
	unsigned int rx_timeout_;
	eeprom eeprom_;
};

}}
