#pragma once
#include "rf_phreaker/common/common_utility.h"

namespace rf_phreaker { namespace scanner {

#define RF_PHREAKER_FLASH_PAGE_SIZE 256
#define RF_PHREAKER_FLASH_ADDR 0x00040000
#define RF_PHREAKER_FLASH_PAGE_ADDR (RF_PHREAKER_FLASH_ADDR / RF_PHREAKER_FLASH_PAGE_SIZE)
#define RF_PHREAKER_FLASH_EB_SIZE     (64 * 1024)
#define RF_PHREAKER_FLASH_EB_ADDR (RF_PHREAKER_FLASH_ADDR / RF_PHREAKER_FLASH_EB_SIZE)
#define RF_PHREAKER_FLASH_BYTE_LEN 0x00370000
#define RF_PHREAKER_FLASH_METADATA_BYTE_LEN 2*256

inline uint32_t convert_to_page(uint32_t num) {
	return add_mod(num, RF_PHREAKER_FLASH_PAGE_SIZE) / RF_PHREAKER_FLASH_PAGE_SIZE;
}

inline uint32_t convert_to_erase_block(uint32_t num) {
	return add_mod(num, RF_PHREAKER_FLASH_EB_SIZE) / RF_PHREAKER_FLASH_EB_SIZE;
}

inline uint32_t add_eb_padding(uint32_t num) {
	return add_mod(num, RF_PHREAKER_FLASH_EB_SIZE);
}

}}