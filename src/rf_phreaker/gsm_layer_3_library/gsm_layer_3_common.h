#pragma once

#include <stdint.h>

static const int32_t skip_indicator_value_bit_size = 4;
static const int32_t transaction_identifier_value_bit_size = 4;
static const int32_t protocol_discriminator_value_bit_size = 4;
static const int32_t message_type_value_bit_size = 8;
static const int32_t l2_pseudo_length_value_bit_size = 8;
static const int32_t cell_identity_value_bit_size = 16;
static const int32_t location_area_identification_value_bit_size = 40;

/*
3GPP TS 24.007 version 10.0.0 Release 10
11.2.1.1 Format of standard information elements
Format Meaning IEI present LI present Value part present
T Type only yes no no
V Value only no no yes
TV Type and Value yes no yes
LV Length and Value no yes yes
TLV Type, Length and Value yes yes yes
LV-E Length and Value no yes yes
TLV-E Type, Length and Value yes yes yes
*/
enum format_of_information_elements
{
	type_only_format,
	value_only_format,
	type_and_value_format,
	length_and_value_format,
	type_length_and_value_format,
	length_and_value_eps_format,
	type_length_and_value_eps_format,
	variable_length
};

/*
bits 4 3 2 1
0 0 0 0 group call control
0 0 0 1 broadcast call control
0 0 1 0 EPS session management messages
0 0 1 1 call control; call related SS messages
0 1 0 0 GPRS Transparent Transport Protocol (GTTP)
0 1 0 1 mobility management messages
0 1 1 0 radio resources management messages
0 1 1 1 EPS mobility management messages
1 0 0 0 GPRS mobility management messages
1 0 0 1 SMS messages
1 0 1 0 GPRS session management messages
1 0 1 1 non call related SS messages
1 1 0 0 Location services specified in 3GPP TS 44.071 [8a]
1 1 1 0 reserved for extension of the PD to one octet length
1 1 1 1 used by tests procedures described in 3GPP TS 44.014 [5a], 3GPP TS
34.109 [17a] and 3GPP TS 36.509 [26].
*/
enum protocol_discriminator_code
{
	group_call_control = 0x00,
	broadcast_call_control = 0x01,
	eps_session_management_messages = 0x02,
	call_control_call_related_ss_messages = 0x03,
	gprs_transparent_transport_protocol = 0x04,
	mobility_management_messages = 0x05,
	radio_resources_management_messages = 0x06,
	eps_mobility_management_messages = 0x07,
	gprs_mobility_management_messages = 0x08,
	sms_messages = 0x09,
	gprs_session_management_messages = 0x0a,
	non_call_related_ss_messages = 0x0b,
	location_services = 0x0c,
	reserved_for_extension_pd_one_octet_length = 0x0e,
	test_procedures = 0x0f
};


/*
Channel establishment messages:
0 0 1 1 1 1 0 0 Reserved (see NOTE)
0 0 1 1 1 0 1 1 ADDITIONAL ASSIGNMENT
0 0 1 1 1 1 1 1 IMMEDIATE ASSIGNMENT
0 0 1 1 1 0 0 1 IMMEDIATE ASSIGNMENT EXTENDED
0 0 1 1 1 0 1 0 IMMEDIATE ASSIGNMENT REJECT
Ciphering messages:
0 0 1 1 0 1 0 1 CIPHERING MODE COMMAND
0 0 1 1 0 0 1 0 CIPHERING MODE COMPLETE
Configuration change messages:
0 0 1 1 0 0 0 0 CONFIGURATION CHANGE COMMAND
0 0 1 1 0 0 0 1 CONFIGURATION CHANGE ACK.
0 0 1 1 0 0 1 1 CONFIGURATION CHANGE REJECT
Handover messages:
0 0 1 0 1 1 1 0 ASSIGNMENT COMMAND
0 0 1 0 1 0 0 1 ASSIGNMENT COMPLETE
0 0 1 0 1 1 1 1 ASSIGNMENT FAILURE
0 0 1 0 1 0 1 1 HANDOVER COMMAND
0 0 1 0 1 1 0 0 HANDOVER COMPLETE
0 0 1 0 1 0 0 0 HANDOVER FAILURE
0 0 1 0 1 1 0 1 PHYSICAL INFORMATION
0 0 0 0 1 0 0 0 Reserved (see NOTE)
0 0 1 0 0 0 1 1 Reserved (see NOTE)
Channel release messages:
0 0 0 0 1 1 0 1 CHANNEL RELEASE
0 0 0 0 1 0 1 0 PARTIAL RELEASE
0 0 0 0 1 1 1 1 PARTIAL RELEASE COMPLETE
Paging and Notification messages:
0 0 1 0 0 0 0 1 PAGING REQUEST TYPE 1
0 0 1 0 0 0 1 0 PAGING REQUEST TYPE 2
0 0 1 0 0 1 0 0 PAGING REQUEST TYPE 3
0 0 1 0 0 1 1 1 PAGING RESPONSE
0 0 1 0 0 0 0 0 NOTIFICATION/NCH
0 0 1 0 0 1 0 1 Reserved (see NOTE)
0 0 1 0 0 1 1 0 NOTIFICATION/RESPONSE
0 0 0 0 1 0 1 1 Reserved (see NOTE)
System information messages:
0 0 0 1 1 0 0 0 SYSTEM INFORMATION TYPE 8
0 0 0 1 1 0 0 1 SYSTEM INFORMATION TYPE 1
0 0 0 1 1 0 1 0 SYSTEM INFORMATION TYPE 2
0 0 0 1 1 0 1 1 SYSTEM INFORMATION TYPE 3
0 0 0 1 1 1 0 0 SYSTEM INFORMATION TYPE 4
0 0 0 1 1 1 0 1 SYSTEM INFORMATION TYPE 5
0 0 0 1 1 1 1 0 SYSTEM INFORMATION TYPE 6
0 0 0 1 1 1 1 1 SYSTEM INFORMATION TYPE 7
System information messages:
0 0 0 0 0 0 1 0 SYSTEM INFORMATION TYPE 2bis
0 0 0 0 0 0 1 1 SYSTEM INFORMATION TYPE 2ter
0 0 0 0 0 1 1 1 SYSTEM INFORMATION TYPE 2quater
0 0 0 0 0 1 0 1 SYSTEM INFORMATION TYPE 5bis
0 0 0 0 0 1 1 0 SYSTEM INFORMATION TYPE 5ter
0 0 0 0 0 1 0 0 SYSTEM INFORMATION TYPE 9
0 0 0 0 0 0 0 0 SYSTEM INFORMATION TYPE 13
System information messages:
0 0 1 1 1 1 0 1 SYSTEM INFORMATION TYPE 16
0 0 1 1 1 1 1 0 SYSTEM INFORMATION TYPE 17
Miscellaneous messages:
0 0 0 1 0 0 0 0 CHANNEL MODE MODIFY
0 0 0 1 0 0 1 0 RR STATUS
0 0 0 1 0 1 1 1 CHANNEL MODE MODIFY ACKNOWLEDGE
0 0 0 1 0 1 0 0 FREQUENCY REDEFINITION
0 0 0 1 0 1 0 1 MEASUREMENT REPORT
0 0 0 1 0 1 1 0 CLASSMARK CHANGE
0 0 0 1 0 0 1 1 CLASSMARK ENQUIRY
0 0 1 1 0 1 1 0 EXTENDED MEASUREMENT REPORT
0 0 1 1 0 1 1 1 EXTENDED MEASUREMENT ORDER
0 0 1 1 0 1 0 0 GPRS SUSPENSION REQUEST
0 0 0 1 0 1 1 0 MBMS ANNOUNCEMENT
0 0 1 1 0 1 1 0 SERVICE INFORMATION
VGCS uplink control messages:
0 0 0 0 1 0 0 1 VGCS UPLINK GRANT
0 0 0 0 1 1 1 0 UPLINK RELEASE
0 0 0 0 1 1 0 0 Reserved (see NOTE)
0 0 1 0 1 0 1 0 UPLINK BUSY
0 0 0 1 0 0 0 1 TALKER INDICATION
0 1 1 0 0 1 1 0 PRIORITY UPLINK REQUEST
0 1 1 0 0 1 1 1 DATA INDICATION
0 1 1 0 1 0 0 0 DATA INDICATION 2
Application messages:
0 0 1 1 1 0 0 0 APPLICATION INFORMATION
System information messages:
0 0 0 0 0 0 0 1 SYSTEM INFORMATION TYPE 14
0 1 0 0 0 0 1 1 SYSTEM INFORMATION TYPE 15
0 1 0 0 0 0 0 0 SYSTEM INFORMATION TYPE 18
0 1 0 0 0 0 0 1 SYSTEM INFORMATION TYPE 19
0 1 0 0 0 0 1 0 SYSTEM INFORMATION TYPE 20
0 1 0 0 0 1 0 0 SYSTEM INFORMATION TYPE 13alt
0 1 0 0 0 1 0 1 SYSTEM INFORMATION TYPE 2n
0 1 0 0 0 1 1 0 SYSTEM INFORMATION TYPE 21
DTM control messages:
0 1 0 0 1 0 0 0 DTM ASSIGNMENT FAILURE
0 1 0 0 1 0 0 1 DTM REJECT
0 1 0 0 1 0 1 0 DTM REQUEST
0 1 0 0 1 0 1 1 PACKET ASSIGNMENT
0 1 0 0 1 1 0 0 DTM ASSIGNMENT COMMAND
0 1 0 0 1 1 0 1 DTM INFORMATION
0 1 0 0 1 1 1 0 PACKET NOTIFICATION
3G specific messages:
0 1 1 0 0 0 0 0 UTRAN CLASSMARK CHANGE
0 1 1 0 0 0 1 0 CDMA 2000 CLASSMARK CHANGE
0 1 1 0 0 0 1 1 INTER SYSTEM TO UTRAN HANDOVER COMMAND
0 1 1 0 0 1 0 0 INTER SYSTEM TO CDMA2000 HANDOVER COMMAND
0 1 1 0 0 1 0 1 GERAN IU MODE CLASSMARK CHANGE
*/

enum message_type_code
{
	reserved_channel_establishment = 0x3c,
	addition_assignment = 0x3b,
	immediate_assignment = 0x3f,
	immediate_assignment_extended = 0x39,
	immediate_assignment_reject = 0x3a,
	ciphering_mode_command = 0x35,
	ciphering_mode_complete = 0x32,
	configuration_change_command = 0x30,
	configuration_change_ack = 0x31,
	configuration_change_reject = 0x33,
	assignment_command = 0x2e,
	assignment_complete = 0x29,
	assignment_failure = 0x2f,
	handover_command = 0x2b,
	handover_complete = 0x2c,
	handover_failure = 0x28,
	physical_information = 0x2d,
	reserved_handover_1 = 0x08,
	reserved_handover_2 = 0x23,
	channel_release = 0x0d,
	partial_release = 0x0a,
	partial_release_complete = 0x0f,
	paging_request_type_1 = 0x21,
	paging_request_type_2 = 0x22,
	paging_request_type_3 = 0x24,
	paging_response = 0x27,
	notification_nch = 0x20,
	reserved_paging_notification_1 = 0x25,
	notification_response = 0x26,
	reserved_paging_notification_2 = 0x0b,
	system_information_type_8 = 0x18,
	system_information_type_1 = 0x19,
	system_information_type_2 = 0x1a,
	system_information_type_3 = 0x1b,
	system_information_type_4 = 0x1c,
	system_information_type_5 = 0x1d,
	system_information_type_6 = 0x1e,
	system_information_type_7 = 0x1f,
	system_information_type_2_bis = 0x02,
	system_information_type_2_ter = 0x03,
	system_information_type_2_quater = 0x07,
	system_information_type_5_bis = 0x05,
	system_information_type_5_ter = 0x06,
	system_information_type_9 = 0x04,
	system_information_type_13 = 0x00,
	system_information_type_16 = 0x3d,
	system_information_type_17 = 0x3e,
	channel_mode_modify = 0x10,
	rr_status = 0x12,
	channel_mode_modify_acknowledge = 0x17,
	frequency_redefinition = 0x14,
	measurement_report = 0x15,
	classmark_change = 0x16,
	classmark_enquiry = 0x13,
	extended_measurement_report = 0x36,
	extended_measurement_order = 0x37,
	gprs_suspension_request = 0x34,
	mbms_announcment = 0x16,
	service_information = 0x36,
	vgcs_uplink_grant = 0x09,
	uplink_release = 0x0e,
	reserved_vgcs_uplink = 0x0c,
	uplink_busy = 0x2a,
	talker_indication = 0x11,
	priority_uplink_request = 0x66,
	data_indication_1 = 0x67,
	data_indication_2 = 0x68,
	application_information = 0x38,
	system_information_type_14 = 0x01,
	system_information_type_15 = 0x43,
	system_information_type_18 = 0x40,
	system_information_type_19 = 0x41,
	system_information_type_20 = 0x42,
	system_information_type_13_alt = 0x44,
	system_information_type_2_n = 0x45,
	system_information_type_21 = 0x46,
	dtm_assignment_failure = 0x48,
	dtm_reject = 0x49,
	dtm_request = 0x4a,
	packet_assignment = 0x4b,
	dtm_assignment_command = 0x4c,
	dtm_information = 0x4d,
	packet_notification = 0x4e,
	utran_classmark_change = 0x60,
	cdma_2000_classmark_change = 0x62,
	inter_system_to_utran_handover_command = 0x63,
	inter_system_to_cmda2000_handover_command = 0x64,
	geran_iu_mode_classmark_change = 0x65,
};











