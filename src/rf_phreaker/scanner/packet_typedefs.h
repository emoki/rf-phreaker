#pragma once

#include "rf_phreaker/scanner/packet_class_definitions.h"

namespace rf_phreaker { namespace scanner {

typedef generic_packet_type<string_return_bytes_storage> generic_string_packet;
typedef accelerometer_read_packet_type<header_array_known_return_bytes_storage<accelerator_read, 1>> accelerometer_read_packet;
typedef accelerometer_write_packet_type<header_array_known_return_bytes_storage<accelerometer_write, 2>> accelerometer_write_packet;
typedef calibrate_dds_packet_type<header_array_known_return_bytes_storage<calibrate_dds>> calibrate_dds_packet;
typedef read_1pps_clock_packet_type<header_array_known_return_bytes_storage<read_1pps_clock>> read_1pps_clock_packet;
typedef dds_reset_packet_type<header_array_known_return_bytes_storage<dds_reset>> dds_reset_packet;
typedef dds_read_packet_type<header_array_known_return_bytes_storage<dds_read, 1>> dds_read_packet;
typedef dds_update_packet_type<header_array_known_return_bytes_storage<dds_update>> dds_update_packet;
typedef dds_write_packet_type<header_array_known_return_bytes_storage<dds_write, 2>> dds_write_packet;
typedef set_decimation_packet_type<header_array_known_return_bytes_storage<set_decimation, 1>> set_decimation_packet;
typedef eeprom_read_packet_type<header_array_known_return_bytes_storage<eeprom_read, 1>> eeprom_read_packet;
typedef eeprom_write_packet_type<header_array_known_return_bytes_storage<eeprom_write, 2>> eeprom_write_packet;
typedef fpga_reset_packet_type<header_array_known_return_bytes_storage<fpga_reset>> fpga_reset_packet;
//typedef go_packet_type<header_array_known_return_bytes_storage<go>> go_packet;
typedef gps_off_packet_type<header_array_known_return_bytes_storage<gps_off>> gps_off_packet;
typedef gps_on_packet_type<header_array_known_return_bytes_storage<gps_on>> gps_on_packet;
typedef gps_reset_packet_type<header_array_known_return_bytes_storage<gps_reset>> gps_reset_packet;
typedef gps_read_packet_type<header_array_known_return_bytes_storage<gps_read>> gps_read_packet;
typedef gps_send_ascii_packet_type<header_array_known_return_bytes_storage<gps_send_ascii, 2>> gps_send_ascii_packet;
typedef lime_reset_packet_type<header_array_known_return_bytes_storage<lime_reset>> lime_reset_packet;
typedef lime_read_packet_type<header_array_known_return_bytes_storage<lime_read, 1, 2, 1>> lime_read_packet;
typedef lime_write_packet_type<header_array_known_return_bytes_storage<lime_write, 2>> lime_write_packet;
typedef reset_all_packet_type<header_array_known_return_bytes_storage<reset_all>> reset_all_packet;
typedef set_sample_size_packet_type<header_array_known_return_bytes_storage<set_sample_size, 1>> set_sample_size_packet;
typedef fpga_status_packet_type<header_array_known_return_bytes_storage<fpga_status>> fpga_status_packet;
typedef set_switch_channel_select_packet_type<header_array_known_return_bytes_storage<set_switch_channel_select, 1>> set_switch_channel_select_packet;
typedef set_switch_7_9_packet_type<header_array_known_return_bytes_storage<set_switch_7_9, 1>> set_switch_7_9_packet;
typedef set_switch_input_select_packet_type<header_array_known_return_bytes_storage<set_switch_input_select, 1>> set_switch_input_select_packet;
typedef mem_test_packet_type<header_array_known_return_bytes_storage<mem_test, 1>> mem_test_packet;
typedef usb_reset_packet_type<header_array_known_return_bytes_storage<usb_reset, 0>> usb_reset_packet;
typedef set_sample_size_and_go_packet_type<header_array_buf_iterator_storage<set_sample_size, 1>> set_sample_size_and_go_packet;

}}



