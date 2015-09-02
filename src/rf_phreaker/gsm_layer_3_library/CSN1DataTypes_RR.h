/**************************************************************************
	Generated automatically by Codegenix(TM) - (c) 2000-2004 Dafocus
	EnDec version 1.0.152
	GENERATOR: ed-c-encodeco
	http://www.Dafocus.it/
**************************************************************************/

#ifndef __CSN1DataTypes_RR_h
#define __CSN1DataTypes_RR_h
#include "csn1clib.h"
#include "ed_lib.h"
#include "ed_c_RR.h"
#include "ed_user.h"
#include "endec_configs_RR.h"
#if ED_VERSION != 10152
#error Invalid Encodix library files linked; used those distributed with Encodix 1.0.152
#endif


#ifdef __cplusplus
	extern "C" {
#endif

extern TCSN1CProgram Program_RR_Program;


#ifdef CSN1C_LABEL_NAMES
/* List of label names */
extern const char* const Program_RR_Labels [];
#endif

/* LABELS */

#define CSN1_TMGI_IE_MCC                98
#define CSN1_TMGI_IE_MCC_SIZE           12
#define CSN1_TMGI_IE_MNC                99
#define CSN1_TMGI_IE_MNC_SIZE           12
#define CSN1_ChReqDesc2_PFI            156
#define CSN1_ChReqDesc2_PFI_SIZE         7
#define CSN1_cell_info_bsic            1199
#define CSN1_cell_info_bsic_SIZE         6
#define CSN1_RTD6_Struct_RTD            52
#define CSN1_RTD6_Struct_RTD_SIZE        6
#define CSN1_A5_CM3_bits_A5_4           82
#define CSN1_A5_CM3_bits_A5_4_SIZE       1
#define CSN1_A5_CM3_bits_A5_5           81
#define CSN1_A5_CM3_bits_A5_5_SIZE       1
#define CSN1_A5_CM3_bits_A5_6           80
#define CSN1_A5_CM3_bits_A5_6_SIZE       1
#define CSN1_A5_CM3_bits_A5_7           79
#define CSN1_A5_CM3_bits_A5_7_SIZE       1
#define CSN1_P2RestOctets_CN3          1238
#define CSN1_P2RestOctets_CN3_SIZE       2
#define CSN1_P2RestOctets_NLN          1239
#define CSN1_P2RestOctets_NLN_SIZE       2
#define CSN1_P3RestOctets_CN3          180
#define CSN1_P3RestOctets_CN3_SIZE       2
#define CSN1_P3RestOctets_CN4          181
#define CSN1_P3RestOctets_CN4_SIZE       2
#define CSN1_P3RestOctets_NLN          182
#define CSN1_P3RestOctets_NLN_SIZE       2
#define CSN1_PSC_Group_IE_PSC          267
#define CSN1_PSC_Group_IE_PSC_SIZE       9
#define CSN1_RTD12_Struct_RTD           53
#define CSN1_RTD12_Struct_RTD_SIZE      12
#define CSN1_SI6RestOctet_RAC          606
#define CSN1_SI6RestOctet_RAC_SIZE       8
#define CSN1_IARestOctets_MAIO         560
#define CSN1_IARestOctets_MAIO_SIZE      6
#define CSN1_BA_List_Pref_Range        143
#define CSN1_BA_List_Pref_Range_SIZE    20
#define CSN1_LSA_Parameters_MCC        595
#define CSN1_LSA_Parameters_MCC_SIZE    12
#define CSN1_LSA_Parameters_MNC        596
#define CSN1_LSA_Parameters_MNC_SIZE    12
#define CSN1_PCID_Group_IE_PCID        100
#define CSN1_PCID_Group_IE_PCID_SIZE     9
#define CSN1_PLMN_ID_struct_MCC        105
#define CSN1_PLMN_ID_struct_MCC_SIZE    12
#define CSN1_PLMN_ID_struct_MNC        106
#define CSN1_PLMN_ID_struct_MNC_SIZE    12
#define CSN1_SI13RestOctets_RAC        890
#define CSN1_SI13RestOctets_RAC_SIZE     8
#define CSN1_LSA_identity_LSA_ID       274
#define CSN1_LSA_identity_LSA_ID_SIZE   24
#define CSN1_BA_List_Pref_BA_FREQ      146
#define CSN1_BA_List_Pref_BA_FREQ_SIZE  10
#define CSN1_P1RestOctets_NLN_PCH      1214
#define CSN1_P1RestOctets_NLN_PCH_SIZE   2
#define CSN1_RRPktDownlinkAssi_P0      814
#define CSN1_RRPktDownlinkAssi_P0_SIZE   4
#define CSN1_SI13RestOctets_SGSNR      903
#define CSN1_SI13RestOctets_SGSNR_SIZE   1
#define CSN1_NTNRestOctets_NLN_PCH     800
#define CSN1_NTNRestOctets_NLN_PCH_SIZE   2
#define CSN1_P1RestOctets_Priority1    1216
#define CSN1_P1RestOctets_Priority1_SIZE   3
#define CSN1_P1RestOctets_Priority2    1217
#define CSN1_P1RestOctets_Priority2_SIZE   3
#define CSN1_P1RestOctets_VSTK_RAND    1222
#define CSN1_P1RestOctets_VSTK_RAND_SIZE  36
#define CSN1_P2RestOctets_Priority1    1241
#define CSN1_P2RestOctets_Priority1_SIZE   3
#define CSN1_P2RestOctets_Priority2    1242
#define CSN1_P2RestOctets_Priority2_SIZE   3
#define CSN1_P2RestOctets_Priority3    1243
#define CSN1_P2RestOctets_Priority3_SIZE   3
#define CSN1_P3RestOctets_Priority1    184
#define CSN1_P3RestOctets_Priority1_SIZE   3
#define CSN1_P3RestOctets_Priority2    185
#define CSN1_P3RestOctets_Priority2_SIZE   3
#define CSN1_P3RestOctets_Priority3    186
#define CSN1_P3RestOctets_Priority3_SIZE   3
#define CSN1_P3RestOctets_Priority4    187
#define CSN1_P3RestOctets_Priority4_SIZE   3
#define CSN1_RRPktDownlinkAssi_FANR    834
#define CSN1_RRPktDownlinkAssi_FANR_SIZE   1
#define CSN1_SI13RestOctets_NoPBCCH    889
#define CSN1_SI13RestOctets_NoPBCCH_SIZE   0
#define CSN1_SI2bisRestOctets_dummy    230
#define CSN1_SI2bisRestOctets_dummy_SIZE   0
#define CSN1_SI4_Rest_Octets_S_CBQ3    598
#define CSN1_SI4_Rest_Octets_S_CBQ3_SIZE   2
#define CSN1_SI6RestOctet_MAX_LAPDm    607
#define CSN1_SI6RestOctet_MAX_LAPDm_SIZE   3
#define CSN1_LSA_Parameters_PRIO_THR   593
#define CSN1_LSA_Parameters_PRIO_THR_SIZE   3
#define CSN1_P1RestOctets_AMR_Config   1227
#define CSN1_P1RestOctets_AMR_Config_SIZE   4
#define CSN1_P1RestOctets_NLN_status   1215
#define CSN1_P1RestOctets_NLN_status_SIZE   1
#define CSN1_P2RestOctets_NLN_status   1240
#define CSN1_P2RestOctets_NLN_status_SIZE   1
#define CSN1_P3RestOctets_NLN_status   183
#define CSN1_P3RestOctets_NLN_status_SIZE   1
#define CSN1_SI10_rest_octets_BA_ind   1197
#define CSN1_SI10_rest_octets_BA_ind_SIZE   1
#define CSN1_SI16_LSA_Parameters_MCC   909
#define CSN1_SI16_LSA_Parameters_MCC_SIZE  12
#define CSN1_SI16_LSA_Parameters_MNC   910
#define CSN1_SI16_LSA_Parameters_MNC_SIZE  12
#define CSN1_SI18RestOctet_SI18_LAST   278
#define CSN1_SI18RestOctet_SI18_LAST_SIZE   1
#define CSN1_SI6RestOctet_AMR_Config   611
#define CSN1_SI6RestOctet_AMR_Config_SIZE   4
#define CSN1_TMGI_IE_MBMS_SERVICE_ID    97
#define CSN1_TMGI_IE_MBMS_SERVICE_ID_SIZE  24
#define CSN1_UTRANFreqList_FDD_ARFCN   147
#define CSN1_UTRANFreqList_FDD_ARFCN_SIZE  14
#define CSN1_UTRANFreqList_TDD_ARFCN   148
#define CSN1_UTRANFreqList_TDD_ARFCN_SIZE  14
#define CSN1__3GTargetCell_Diversity   310
#define CSN1__3GTargetCell_Diversity_SIZE   1
#define CSN1__3GTargetCell_FDD_ARFCN   309
#define CSN1__3GTargetCell_FDD_ARFCN_SIZE  14
#define CSN1__3GTargetCell_Sync_Case   316
#define CSN1__3GTargetCell_Sync_Case_SIZE   1
#define CSN1__3GTargetCell_TDD_ARFCN   313
#define CSN1__3GTargetCell_TDD_ARFCN_SIZE  14
#define CSN1_cell_barred_cell_barred     0
#define CSN1_cell_barred_cell_barred_SIZE   0
#define CSN1_ChReqDesc2_Uplink_EGPRS2  160
#define CSN1_ChReqDesc2_Uplink_EGPRS2_SIZE   2
#define CSN1_GPRS_Cell_Options_IE_NMO  660
#define CSN1_GPRS_Cell_Options_IE_NMO_SIZE   2
#define CSN1_GPRS_Cell_Options_IE_ext  670
#define CSN1_GPRS_Cell_Options_IE_ext_SIZE   0
#define CSN1_GPRS_Indicator_RA_COLOUR  591
#define CSN1_GPRS_Indicator_RA_COLOUR_SIZE   3
#define CSN1_IARestOctets_HH_detected  519
#define CSN1_IARestOctets_HH_detected_SIZE   0
#define CSN1_IARestOctets_LH_detected  478
#define CSN1_IARestOctets_LH_detected_SIZE   0
#define CSN1_IARestOctets_LL_detected  562
#define CSN1_IARestOctets_LL_detected_SIZE   0
#define CSN1_LSA_identity_ShortLSA_ID  275
#define CSN1_LSA_identity_ShortLSA_ID_SIZE  10
#define CSN1_P1RestOctets_IPA_Support  1237
#define CSN1_P1RestOctets_IPA_Support_SIZE   1
#define CSN1_P1RestOctets_Reduced_GCR  1221
#define CSN1_P1RestOctets_Reduced_GCR_SIZE  28
#define CSN1_P2RestOctets_IPA_Support  1250
#define CSN1_P2RestOctets_IPA_Support_SIZE   1
#define CSN1_P3RestOctets_IPA_Support  190
#define CSN1_P3RestOctets_IPA_Support_SIZE   1
#define CSN1_PSC_Group_IE_PSC_Pattern  269
#define CSN1_PSC_Group_IE_PSC_Pattern_SIZE   0
#define CSN1_RANGE_LIMITS_RANGE_LOWER  144
#define CSN1_RANGE_LIMITS_RANGE_LOWER_SIZE  10
#define CSN1_RANGE_LIMITS_RANGE_UPPER  145
#define CSN1_RANGE_LIMITS_RANGE_UPPER_SIZE  10
#define CSN1_RLC_Entity_Struct_DN_PFI  220
#define CSN1_RLC_Entity_Struct_DN_PFI_SIZE   7
#define CSN1_RLC_Entity_Struct_UP_PFI  216
#define CSN1_RLC_Entity_Struct_UP_PFI_SIZE   7
#define CSN1_SI10bis_Rest_Octets_BSIC  641
#define CSN1_SI10bis_Rest_Octets_BSIC_SIZE   6
#define CSN1_SI18RestOctet_SI18_INDEX  277
#define CSN1_SI18RestOctet_SI18_INDEX_SIZE   3
#define CSN1_SI6RestOctet_DTM_support  605
#define CSN1_SI6RestOctet_DTM_support_SIZE   0
#define CSN1_Selection_Parameters_CBQ  577
#define CSN1_Selection_Parameters_CBQ_SIZE   1
#define CSN1_LSA_Parameters_LSA_OFFSET 594
#define CSN1_LSA_Parameters_LSA_OFFSET_SIZE   3
#define CSN1_MPRACH_description_IE_USF 1189
#define CSN1_MPRACH_description_IE_USF_SIZE   3
#define CSN1_MultirateSpeechCfgIE_ICMI 174
#define CSN1_MultirateSpeechCfgIE_ICMI_SIZE   1
#define CSN1_MultirateSpeechCfgIE_NSCB 173
#define CSN1_MultirateSpeechCfgIE_NSCB_SIZE   1
#define CSN1_RRPktDownlinkAssi_PR_MODE 816
#define CSN1_RRPktDownlinkAssi_PR_MODE_SIZE   1
#define CSN1_SI14RestOctets_SI14_COUNT 284
#define CSN1_SI14RestOctets_SI14_COUNT_SIZE   2
#define CSN1_SI14RestOctets_SI14_INDEX 283
#define CSN1_SI14RestOctets_SI14_INDEX_SIZE   2
#define CSN1_SI15RestOctets_SI15_COUNT 288
#define CSN1_SI15RestOctets_SI15_COUNT_SIZE   2
#define CSN1_SI15RestOctets_SI15_INDEX 287
#define CSN1_SI15RestOctets_SI15_INDEX_SIZE   2
#define CSN1_SI6RestOctet_MNCI_SUPPORT 610
#define CSN1_SI6RestOctet_MNCI_SUPPORT_SIZE   1
#define CSN1_ChReqDesc2_Downlink_EGPRS2 161
#define CSN1_ChReqDesc2_Downlink_EGPRS2_SIZE   2
#define CSN1_ChReqDesc2_FANR_Capability 164
#define CSN1_ChReqDesc2_FANR_Capability_SIZE   1
#define CSN1_EGPRS_Level_IE_EGPRS_Level 540
#define CSN1_EGPRS_Level_IE_EGPRS_Level_SIZE   2
#define CSN1_Fixed_Allocation_struct_P0 203
#define CSN1_Fixed_Allocation_struct_P0_SIZE   4
#define CSN1_GPRS_Cell_Options_IE_T3168 661
#define CSN1_GPRS_Cell_Options_IE_T3168_SIZE   3
#define CSN1_GPRS_Cell_Options_IE_T3192 662
#define CSN1_GPRS_Cell_Options_IE_T3192_SIZE   3
#define CSN1_MBMS_Sessions_List_IE_TMGI 399
#define CSN1_MBMS_Sessions_List_IE_TMGI_SIZE   0
#define CSN1_MeasurementResults_BA_USED 565
#define CSN1_MeasurementResults_BA_USED_SIZE   1
#define CSN1_MultirateSpeechCfgIE_codec 177
#define CSN1_MultirateSpeechCfgIE_codec_SIZE   0
#define CSN1_PCH_and_NCH_info_NLN_SACCH 601
#define CSN1_PCH_and_NCH_info_NLN_SACCH_SIZE   2
#define CSN1_PCID_Group_IE_PCID_Pattern 103
#define CSN1_PCID_Group_IE_PCID_Pattern_SIZE   0
#define CSN1_RRPktDownlinkAssi_MAC_MODE 810
#define CSN1_RRPktDownlinkAssi_MAC_MODE_SIZE   2
#define CSN1_RRPktDownlinkAssi_RLC_MODE 811
#define CSN1_RRPktDownlinkAssi_RLC_MODE_SIZE   1
#define CSN1_SI1RestOctets_NCH_Position 228
#define CSN1_SI1RestOctets_NCH_Position_SIZE   5
#define CSN1_SI21RestOctets_SI_21_COUNT 293
#define CSN1_SI21RestOctets_SI_21_COUNT_SIZE   3
#define CSN1_SI21RestOctets_SI_21_INDEX 292
#define CSN1_SI21RestOctets_SI_21_INDEX_SIZE   3
#define CSN1_SI22RestOctets_SI_22_COUNT 298
#define CSN1_SI22RestOctets_SI_22_COUNT_SIZE   3
#define CSN1_SI22RestOctets_SI_22_INDEX 297
#define CSN1_SI22RestOctets_SI_22_INDEX_SIZE   3
#define CSN1_SI23RestOctets_SI_23_COUNT 1138
#define CSN1_SI23RestOctets_SI_23_COUNT_SIZE   3
#define CSN1_SI23RestOctets_SI_23_INDEX 1137
#define CSN1_SI23RestOctets_SI_23_INDEX_SIZE   3
#define CSN1_SI2quaterRestOctets_BA_IND 993
#define CSN1_SI2quaterRestOctets_BA_IND_SIZE   1
#define CSN1_differential_cell_info_BCC 1207
#define CSN1_differential_cell_info_BCC_SIZE   3
#define CSN1_DTMInfoRestOctets_MAX_LAPDm 165
#define CSN1_DTMInfoRestOctets_MAX_LAPDm_SIZE   3
#define CSN1_Emergency_Ind_Emergency_Ind  22
#define CSN1_Emergency_Ind_Emergency_Ind_SIZE   0
#define CSN1_Frequency_Parameters_IE_TSC 911
#define CSN1_Frequency_Parameters_IE_TSC_SIZE   3
#define CSN1_GSM_Description_struct_BSIC 477
#define CSN1_GSM_Description_struct_BSIC_SIZE   6
#define CSN1_IARRestOctets_Extended_RA_1  15
#define CSN1_IARRestOctets_Extended_RA_1_SIZE   5
#define CSN1_IARRestOctets_Extended_RA_2  16
#define CSN1_IARRestOctets_Extended_RA_2_SIZE   5
#define CSN1_IARRestOctets_Extended_RA_3  17
#define CSN1_IARRestOctets_Extended_RA_3_SIZE   5
#define CSN1_IARRestOctets_Extended_RA_4  18
#define CSN1_IARRestOctets_Extended_RA_4_SIZE   5
#define CSN1_MeasurementResults_DTX_USED 566
#define CSN1_MeasurementResults_DTX_USED_SIZE   1
#define CSN1_NTNRestOctets_FR_AMR_Config 806
#define CSN1_NTNRestOctets_FR_AMR_Config_SIZE   4
#define CSN1_NTNRestOctets_HR_AMR_Config 807
#define CSN1_NTNRestOctets_HR_AMR_Config_SIZE   4
#define CSN1_PBCCH_Description_struct_Pb 898
#define CSN1_PBCCH_Description_struct_Pb_SIZE   4
#define CSN1_PBCCH_Description_struct_TN 900
#define CSN1_PBCCH_Description_struct_TN_SIZE   3
#define CSN1_PCH_and_NCH_info_NLN_status 603
#define CSN1_PCH_and_NCH_info_NLN_status_SIZE   1
#define CSN1_PacketChannelDescription_TN 192
#define CSN1_PacketChannelDescription_TN_SIZE   3
#define CSN1_Packet_Uplink_Assignment_P0 545
#define CSN1_Packet_Uplink_Assignment_P0_SIZE   4
#define CSN1_SI13RestOctets_SI2n_SUPPORT 906
#define CSN1_SI13RestOctets_SI2n_SUPPORT_SIZE   2
#define CSN1_SI23RestOctets_SI_23_BA_IND 1135
#define CSN1_SI23RestOctets_SI_23_BA_IND_SIZE   1
#define CSN1__3GTargetCell_Bandwidth_FDD 311
#define CSN1__3GTargetCell_Bandwidth_FDD_SIZE   3
#define CSN1__3GTargetCell_Bandwidth_TDD 314
#define CSN1__3GTargetCell_Bandwidth_TDD_SIZE   3
#define CSN1_differential_cell_info_bsic 1208
#define CSN1_differential_cell_info_bsic_SIZE   6
#define CSN1_BSIC_Description_struct_BSIC 700
#define CSN1_BSIC_Description_struct_BSIC_SIZE   6
#define CSN1_Direct_encoding_2_struct_HSN 922
#define CSN1_Direct_encoding_2_struct_HSN_SIZE   6
#define CSN1_Dynamic_Allocation_struct_P0  24
#define CSN1_Dynamic_Allocation_struct_P0_SIZE   4
#define CSN1_GPRS_Cell_Options_IE_PAN_DEC 667
#define CSN1_GPRS_Cell_Options_IE_PAN_DEC_SIZE   3
#define CSN1_GPRS_Cell_Options_IE_PAN_INC 668
#define CSN1_GPRS_Cell_Options_IE_PAN_INC_SIZE   3
#define CSN1_GPRS_Cell_Options_IE_PAN_MAX 669
#define CSN1_GPRS_Cell_Options_IE_PAN_MAX_SIZE   3
#define CSN1_GPRS_Indicator_SI13_POSITION 592
#define CSN1_GPRS_Indicator_SI13_POSITION_SIZE   1
#define CSN1_GSM_Description_struct_ARFCN 476
#define CSN1_GSM_Description_struct_ARFCN_SIZE  10
#define CSN1_Measurement_information_PWRC 691
#define CSN1_Measurement_information_PWRC_SIZE   1
#define CSN1_PBCCH_Description_struct_TSC 899
#define CSN1_PBCCH_Description_struct_TSC_SIZE   3
#define CSN1_PacketChannelDescription_HSN 199
#define CSN1_PacketChannelDescription_HSN_SIZE   6
#define CSN1_PacketChannelDescription_TSC 193
#define CSN1_PacketChannelDescription_TSC_SIZE   3
#define CSN1_Packet_Uplink_Assignment_PFI 557
#define CSN1_Packet_Uplink_Assignment_PFI_SIZE   7
#define CSN1_Packet_Uplink_Assignment_USF 548
#define CSN1_Packet_Uplink_Assignment_USF_SIZE   3
#define CSN1_RRPacketUplinkAssignment_TSH 969
#define CSN1_RRPacketUplinkAssignment_TSH_SIZE   2
#define CSN1_SI13RestOctets_SI_STATUS_IND 904
#define CSN1_SI13RestOctets_SI_STATUS_IND_SIZE   1
#define CSN1_SI13RestOctets_SPGC_CCCH_SUP 891
#define CSN1_SI13RestOctets_SPGC_CCCH_SUP_SIZE   1
#define CSN1_SI16_LSA_Parameters_PRIO_THR 907
#define CSN1_SI16_LSA_Parameters_PRIO_THR_SIZE   3
#define CSN1_Single_Band_Support_GSM_Band 352
#define CSN1_Single_Band_Support_GSM_Band_SIZE   4
#define CSN1__3GTargetCell_Cell_Parameter 315
#define CSN1__3GTargetCell_Cell_Parameter_SIZE   7
#define CSN1_Additional_PFCs_struct_DN_PFI  51
#define CSN1_Additional_PFCs_struct_DN_PFI_SIZE   7
#define CSN1_Additional_PFCs_struct_UP_PFI  48
#define CSN1_Additional_PFCs_struct_UP_PFI_SIZE   7
#define CSN1_Band_indicator_BAND_INDICATOR 229
#define CSN1_Band_indicator_BAND_INDICATOR_SIZE   1
#define CSN1_ChReqDesc2_EMSR_MS_Capability 163
#define CSN1_ChReqDesc2_EMSR_MS_Capability_SIZE   1
#define CSN1_ChReqDesc2_EMST_MS_Capability 162
#define CSN1_ChReqDesc2_EMST_MS_Capability_SIZE   1
#define CSN1_Direct_encoding_1_struct_MAIO 913
#define CSN1_Direct_encoding_1_struct_MAIO_SIZE   6
#define CSN1_Direct_encoding_2_struct_MAIO 921
#define CSN1_Direct_encoding_2_struct_MAIO_SIZE   6
#define CSN1_Frequency_Parameters_IE_ARFCN 925
#define CSN1_Frequency_Parameters_IE_ARFCN_SIZE  10
#define CSN1_GPRS_Mobile_Allocation_IE_HSN 394
#define CSN1_GPRS_Mobile_Allocation_IE_HSN_SIZE   6
#define CSN1_Indirect_encoding_struct_MAIO 916
#define CSN1_Indirect_encoding_struct_MAIO_SIZE   6
#define CSN1_Iu_Indicator_SI13alt_POSITION 589
#define CSN1_Iu_Indicator_SI13alt_POSITION_SIZE   1
#define CSN1_MeasurementResults_MEAS_VALID 569
#define CSN1_MeasurementResults_MEAS_VALID_SIZE   1
#define CSN1_MeasurementResults_NO_NCELL_M 574
#define CSN1_MeasurementResults_NO_NCELL_M_SIZE   3
#define CSN1_PBCCH_Description_2_struct_Pb 1148
#define CSN1_PBCCH_Description_2_struct_Pb_SIZE   4
#define CSN1_PBCCH_Description_2_struct_TN 1149
#define CSN1_PBCCH_Description_2_struct_TN_SIZE   3
#define CSN1_PBCCH_Description_struct_MAIO 902
#define CSN1_PBCCH_Description_struct_MAIO_SIZE   6
#define CSN1_PacketChannelDescription_MAIO 194
#define CSN1_PacketChannelDescription_MAIO_SIZE   6
#define CSN1_Packet_Downlink_Assignment_P0 529
#define CSN1_Packet_Downlink_Assignment_P0_SIZE   4
#define CSN1_RLC_Entity_Struct_DN_RLC_MODE 218
#define CSN1_RLC_Entity_Struct_DN_RLC_MODE_SIZE   1
#define CSN1_RLC_Entity_Struct_UP_RLC_MODE 213
#define CSN1_RLC_Entity_Struct_UP_RLC_MODE_SIZE   1
#define CSN1_RRClassmark3Value_VAMOS_Level 382
#define CSN1_RRClassmark3Value_VAMOS_Level_SIZE   2
#define CSN1_SI13_GPRS_Indicator_RA_COLOUR 584
#define CSN1_SI13_GPRS_Indicator_RA_COLOUR_SIZE   3
#define CSN1_SI14RestOctets_DM_CHANGE_MARK 285
#define CSN1_SI14RestOctets_DM_CHANGE_MARK_SIZE   4
#define CSN1_SI15RestOctets_DM_CHANGE_MARK 289
#define CSN1_SI15RestOctets_DM_CHANGE_MARK_SIZE   4
#define CSN1_SI18RestOctet_Non_GSM_Message 279
#define CSN1_SI18RestOctet_Non_GSM_Message_SIZE   0
#define CSN1_SI2terRestOctets_SI2ter_COUNT 234
#define CSN1_SI2terRestOctets_SI2ter_COUNT_SIZE   3
#define CSN1_SI2terRestOctets_SI2ter_INDEX 233
#define CSN1_SI2terRestOctets_SI2ter_INDEX_SIZE   3
#define CSN1_SI6RestOctet_VBS_VGCS_options 604
#define CSN1_SI6RestOctet_VBS_VGCS_options_SIZE   2
#define CSN1_SI_CHANGE_ALT_SI_CHANGE_ALT_H   2
#define CSN1_SI_CHANGE_ALT_SI_CHANGE_ALT_H_SIZE   0
#define CSN1_Scheduling_if_and_where_WHERE 583
#define CSN1_Scheduling_if_and_where_WHERE_SIZE   3
#define CSN1__3GTargetCell_SCRAMBLING_CODE 312
#define CSN1__3GTargetCell_SCRAMBLING_CODE_SIZE   9
#define CSN1_next_frequency_next_frequency 1206
#define CSN1_next_frequency_next_frequency_SIZE   1
#define CSN1_DTMInfoRestOctets_MNCI_SUPPORT 169
#define CSN1_DTMInfoRestOctets_MNCI_SUPPORT_SIZE   1
#define CSN1_DYNAMIC_ARFCN_MAPPING_GSM_Band  10
#define CSN1_DYNAMIC_ARFCN_MAPPING_GSM_Band_SIZE   4
#define CSN1_GPRS_Cell_Options_IE_BS_CV_MAX 666
#define CSN1_GPRS_Cell_Options_IE_BS_CV_MAX_SIZE   4
#define CSN1_IARestOctets_Mobile_Allocation 561
#define CSN1_IARestOctets_Mobile_Allocation_SIZE   0
#define CSN1_MPRACH_Control_Parameters_IE_S 1193
#define CSN1_MPRACH_Control_Parameters_IE_S_SIZE   4
#define CSN1_MeasurementResults__3G_BA_USED 568
#define CSN1_MeasurementResults__3G_BA_USED_SIZE   1
#define CSN1_Measurement_information_BA_IND 686
#define CSN1_Measurement_information_BA_IND_SIZE   1
#define CSN1_MultirateSpeechCfgIE_Threshold 178
#define CSN1_MultirateSpeechCfgIE_Threshold_SIZE   6
#define CSN1_NCELL_Report_struct_BSIC_NCELL  21
#define CSN1_NCELL_Report_struct_BSIC_NCELL_SIZE   6
#define CSN1_P1RestOctets_CELL_GLOBAL_COUNT 1220
#define CSN1_P1RestOctets_CELL_GLOBAL_COUNT_SIZE   2
#define CSN1_PBCCH_Description_struct_ARFCN 901
#define CSN1_PBCCH_Description_struct_ARFCN_SIZE  10
#define CSN1_PCH_and_NCH_info_Call_priority 602
#define CSN1_PCH_and_NCH_info_Call_priority_SIZE   3
#define CSN1_PSC_Group_IE_PSC_pattern_sense 270
#define CSN1_PSC_Group_IE_PSC_pattern_sense_SIZE   1
#define CSN1_PacketChannelDescription_ARFCN 198
#define CSN1_PacketChannelDescription_ARFCN_SIZE  10
#define CSN1_Packet_Downlink_Assignment_PFI 535
#define CSN1_Packet_Downlink_Assignment_PFI_SIZE   7
#define CSN1_Packet_Uplink_Assignment_ALPHA 552
#define CSN1_Packet_Uplink_Assignment_ALPHA_SIZE   4
#define CSN1_Packet_Uplink_Assignment_GAMMA 553
#define CSN1_Packet_Uplink_Assignment_GAMMA_SIZE   5
#define CSN1_RRPktDownlinkAssi_RLC_Entity_2 842
#define CSN1_RRPktDownlinkAssi_RLC_Entity_2_SIZE   0
#define CSN1_RRPktDownlinkAssi_RLC_Entity_3 843
#define CSN1_RRPktDownlinkAssi_RLC_Entity_3_SIZE   0
#define CSN1_SI10bis_Rest_Octets_BCCH_ARFCN 640
#define CSN1_SI10bis_Rest_Octets_BCCH_ARFCN_SIZE  10
#define CSN1_SI13RestOctets_SI_CHANGE_FIELD 886
#define CSN1_SI13RestOctets_SI_CHANGE_FIELD_SIZE   4
#define CSN1_SI16_LSA_Parameters_LSA_OFFSET 908
#define CSN1_SI16_LSA_Parameters_LSA_OFFSET_SIZE   3
#define CSN1_SI18RestOctet_SI18_CHANGE_MARK 276
#define CSN1_SI18RestOctet_SI18_CHANGE_MARK_SIZE   2
#define CSN1_SI21RestOctets_EAB_Subcategory 295
#define CSN1_SI21RestOctets_EAB_Subcategory_SIZE   2
#define CSN1_SI2quaterRestOctets_p3G_BA_IND 994
#define CSN1_SI2quaterRestOctets_p3G_BA_IND_SIZE   1
#define CSN1_SI6RestOctet_Random_bit_stream 612
#define CSN1_SI6RestOctet_Random_bit_stream_SIZE   0
#define CSN1_UPLINK_FREE_BODY_Emergency_Ind 121
#define CSN1_UPLINK_FREE_BODY_Emergency_Ind_SIZE   1
#define CSN1_further_cell_info_penalty_time 1204
#define CSN1_further_cell_info_penalty_time_SIZE   5
#define CSN1_Break_Indicator_Break_Indicator 884
#define CSN1_Break_Indicator_Break_Indicator_SIZE   0
#define CSN1_CDMA2000_Description_struct_QOF 736
#define CSN1_CDMA2000_Description_struct_QOF_SIZE   2
#define CSN1_DTMInfoRestOctets_Cell_identity 167
#define CSN1_DTMInfoRestOctets_Cell_identity_SIZE  16
#define CSN1_Dynamic_Allocation_struct_ALPHA  29
#define CSN1_Dynamic_Allocation_struct_ALPHA_SIZE   4
#define CSN1_Fixed_Allocation_struct_PR_MODE 205
#define CSN1_Fixed_Allocation_struct_PR_MODE_SIZE   1
#define CSN1_GPRSBCastInfo_GPRS_Cell_Options 798
#define CSN1_GPRSBCastInfo_GPRS_Cell_Options_SIZE   0
#define CSN1_IARestOctets_Implicit_Reject_CS 563
#define CSN1_IARestOctets_Implicit_Reject_CS_SIZE   1
#define CSN1_IARestOctets_Implicit_Reject_PS 564
#define CSN1_IARestOctets_Implicit_Reject_PS_SIZE   1
#define CSN1_IPA_Uplink_Assignment_struct_TN 1159
#define CSN1_IPA_Uplink_Assignment_struct_TN_SIZE   3
#define CSN1_List_of_Reduced_GCR_Reduced_GCR 802
#define CSN1_List_of_Reduced_GCR_Reduced_GCR_SIZE  28
#define CSN1_MeasurementResults_NCELL_Report 575
#define CSN1_MeasurementResults_NCELL_Report_SIZE  17
#define CSN1_MeasurementResults_SI23_BA_USED 571
#define CSN1_MeasurementResults_SI23_BA_USED_SIZE   1
#define CSN1_MultirateSpeechCfgIE_Hysteresis 179
#define CSN1_MultirateSpeechCfgIE_Hysteresis_SIZE   4
#define CSN1_MultirateSpeechCfgIE_MR_version 172
#define CSN1_MultirateSpeechCfgIE_MR_version_SIZE   3
#define CSN1_MultirateSpeechCfgIE_Start_mode 175
#define CSN1_MultirateSpeechCfgIE_Start_mode_SIZE   2
#define CSN1_NCELL_Report_struct_RXLEV_NCELL  19
#define CSN1_NCELL_Report_struct_RXLEV_NCELL_SIZE   6
#define CSN1_NTNRestOctets_CELL_GLOBAL_COUNT 801
#define CSN1_NTNRestOctets_CELL_GLOBAL_COUNT_SIZE   2
#define CSN1_P1RestOctets_Implicit_Reject_CS 1235
#define CSN1_P1RestOctets_Implicit_Reject_CS_SIZE   1
#define CSN1_P1RestOctets_Implicit_Reject_PS 1236
#define CSN1_P1RestOctets_Implicit_Reject_PS_SIZE   1
#define CSN1_P2RestOctets_Implicit_Reject_CS 1248
#define CSN1_P2RestOctets_Implicit_Reject_CS_SIZE   1
#define CSN1_P2RestOctets_Implicit_Reject_PS 1249
#define CSN1_P2RestOctets_Implicit_Reject_PS_SIZE   1
#define CSN1_P3RestOctets_Implicit_Reject_CS 188
#define CSN1_P3RestOctets_Implicit_Reject_CS_SIZE   1
#define CSN1_P3RestOctets_Implicit_Reject_PS 189
#define CSN1_P3RestOctets_Implicit_Reject_PS_SIZE   1
#define CSN1_PCID_Group_IE_PCID_BITMAP_GROUP 101
#define CSN1_PCID_Group_IE_PCID_BITMAP_GROUP_SIZE   6
#define CSN1_PSC_Group_IE_PSC_Pattern_length 268
#define CSN1_PSC_Group_IE_PSC_Pattern_length_SIZE   3
#define CSN1_Packet_Downlink_Assignment_TLLI 520
#define CSN1_Packet_Downlink_Assignment_TLLI_SIZE  32
#define CSN1_SI13RestOctets_BCCH_CHANGE_MARK 885
#define CSN1_SI13RestOctets_BCCH_CHANGE_MARK_SIZE   3
#define CSN1_SI13RestOctets_SI13_CHANGE_MARK 887
#define CSN1_SI13RestOctets_SI13_CHANGE_MARK_SIZE   2
#define CSN1_SI4_Rest_Octets_S_Cell_Identity 597
#define CSN1_SI4_Rest_Octets_S_Cell_Identity_SIZE  16
#define CSN1_Serving_cell_data_struct_CV_BEP 436
#define CSN1_Serving_cell_data_struct_CV_BEP_SIZE   3
#define CSN1_VGCSCipheringParameters_LAC_IND  72
#define CSN1_VGCSCipheringParameters_LAC_IND_SIZE   1
#define CSN1_neighbour_information_InfoField 1205
#define CSN1_neighbour_information_InfoField_SIZE   0
#define CSN1_CDMA2000_Description_struct_QOF1 739
#define CSN1_CDMA2000_Description_struct_QOF1_SIZE   2
#define CSN1_CDMA2000_Description_struct_QOF2 742
#define CSN1_CDMA2000_Description_struct_QOF2_SIZE   2
#define CSN1_EGPRS_Window_Size_IE_Window_Size 215
#define CSN1_EGPRS_Window_Size_IE_Window_Size_SIZE   5
#define CSN1_Extension_Information_BEP_PERIOD 672
#define CSN1_Extension_Information_BEP_PERIOD_SIZE   4
#define CSN1_Extension_Information_CCN_ACTIVE 676
#define CSN1_Extension_Information_CCN_ACTIVE_SIZE   1
#define CSN1_IPA_Uplink_Assignment_struct_USF 1156
#define CSN1_IPA_Uplink_Assignment_struct_USF_SIZE   3
#define CSN1_Measurement_information_MI_COUNT 690
#define CSN1_Measurement_information_MI_COUNT_SIZE   4
#define CSN1_Measurement_information_MI_INDEX 689
#define CSN1_Measurement_information_MI_INDEX_SIZE   4
#define CSN1_Non_GSM_Message_struct_CONTAINER 282
#define CSN1_Non_GSM_Message_struct_CONTAINER_SIZE   8
#define CSN1_P1RestOctets_MBMS_Notification_1 1223
#define CSN1_P1RestOctets_MBMS_Notification_1_SIZE   0
#define CSN1_P1RestOctets_MBMS_Notification_2 1224
#define CSN1_P1RestOctets_MBMS_Notification_2_SIZE   0
#define CSN1_P2RestOctets_MBMS_Notification_3 1245
#define CSN1_P2RestOctets_MBMS_Notification_3_SIZE   0
#define CSN1_PCID_Group_IE_PCID_pattern_sense 104
#define CSN1_PCID_Group_IE_PCID_pattern_sense_SIZE   1
#define CSN1_Packet_Downlink_Assignment_ALPHA 523
#define CSN1_Packet_Downlink_Assignment_ALPHA_SIZE   4
#define CSN1_Packet_Downlink_Assignment_GAMMA 524
#define CSN1_Packet_Downlink_Assignment_GAMMA_SIZE   5
#define CSN1_Packet_Uplink_Assignment_POLLING 542
#define CSN1_Packet_Uplink_Assignment_POLLING_SIZE   1
#define CSN1_Packet_Uplink_Assignment_PR_MODE 547
#define CSN1_Packet_Uplink_Assignment_PR_MODE_SIZE   1
#define CSN1_Paging_Information_channel_first 415
#define CSN1_Paging_Information_channel_first_SIZE   2
#define CSN1_RRClassmark3Value_UCS2_treatment 333
#define CSN1_RRClassmark3Value_UCS2_treatment_SIZE   1
#define CSN1_Relative_Frame_Number_Encoding_k 992
#define CSN1_Relative_Frame_Number_Encoding_k_SIZE  13
#define CSN1_SI13RestOctets_GPRS_Cell_Options 894
#define CSN1_SI13RestOctets_GPRS_Cell_Options_SIZE   0
#define CSN1_SI13RestOctets_PBCCH_Description 897
#define CSN1_SI13RestOctets_PBCCH_Description_SIZE   0
#define CSN1_SI21RestOctets_SI_21_CHANGE_MARK 291
#define CSN1_SI21RestOctets_SI_21_CHANGE_MARK_SIZE   2
#define CSN1_SI22RestOctets_SI_22_CHANGE_MARK 296
#define CSN1_SI22RestOctets_SI_22_CHANGE_MARK_SIZE   2
#define CSN1_SI23RestOctets_SI_23_CHANGE_MARK 1136
#define CSN1_SI23RestOctets_SI_23_CHANGE_MARK_SIZE   2
#define CSN1_SI2quaterRestOctets_INIT_PWR_RED 1129
#define CSN1_SI2quaterRestOctets_INIT_PWR_RED_SIZE   1
#define CSN1_SI3RestOctet_SI2quater_Indicator 587
#define CSN1_SI3RestOctet_SI2quater_Indicator_SIZE   1
#define CSN1_Uplink_TBF_Assignment_struct_PFI 945
#define CSN1_Uplink_TBF_Assignment_struct_PFI_SIZE   7
#define CSN1_VGCSCipheringParameters_CELL_IND  73
#define CSN1_VGCSCipheringParameters_CELL_IND_SIZE   1
#define CSN1_VGCSCipheringParameters_RAND_IND  71
#define CSN1_VGCSCipheringParameters_RAND_IND_SIZE   1
#define CSN1_Absolute_Frame_Number_Encoding_T1 989
#define CSN1_Absolute_Frame_Number_Encoding_T1_SIZE   5
#define CSN1_Absolute_Frame_Number_Encoding_T2 991
#define CSN1_Absolute_Frame_Number_Encoding_T2_SIZE   5
#define CSN1_Absolute_Frame_Number_Encoding_T3 990
#define CSN1_Absolute_Frame_Number_Encoding_T3_SIZE   6
#define CSN1_DYNAMIC_ARFCN_MAPPING_ARFCN_FIRST  11
#define CSN1_DYNAMIC_ARFCN_MAPPING_ARFCN_FIRST_SIZE  10
#define CSN1_DYNAMIC_ARFCN_MAPPING_ARFCN_RANGE  13
#define CSN1_DYNAMIC_ARFCN_MAPPING_ARFCN_RANGE_SIZE   7
#define CSN1_DYNAMIC_ARFCN_MAPPING_BAND_OFFSET  12
#define CSN1_DYNAMIC_ARFCN_MAPPING_BAND_OFFSET_SIZE  10
#define CSN1_Dynamic_Allocation_struct_PR_MODE  25
#define CSN1_Dynamic_Allocation_struct_PR_MODE_SIZE   1
#define CSN1_Dynamic_Allocation_struct_USF_TN0  30
#define CSN1_Dynamic_Allocation_struct_USF_TN0_SIZE   3
#define CSN1_Dynamic_Allocation_struct_USF_TN1  32
#define CSN1_Dynamic_Allocation_struct_USF_TN1_SIZE   3
#define CSN1_Dynamic_Allocation_struct_USF_TN2  34
#define CSN1_Dynamic_Allocation_struct_USF_TN2_SIZE   3
#define CSN1_Dynamic_Allocation_struct_USF_TN3  36
#define CSN1_Dynamic_Allocation_struct_USF_TN3_SIZE   3
#define CSN1_Dynamic_Allocation_struct_USF_TN4  38
#define CSN1_Dynamic_Allocation_struct_USF_TN4_SIZE   3
#define CSN1_Dynamic_Allocation_struct_USF_TN5  40
#define CSN1_Dynamic_Allocation_struct_USF_TN5_SIZE   3
#define CSN1_Dynamic_Allocation_struct_USF_TN6  42
#define CSN1_Dynamic_Allocation_struct_USF_TN6_SIZE   3
#define CSN1_Dynamic_Allocation_struct_USF_TN7  44
#define CSN1_Dynamic_Allocation_struct_USF_TN7_SIZE   3
#define CSN1_EGPRS_Packet_Uplink_Assignment_P0 485
#define CSN1_EGPRS_Packet_Uplink_Assignment_P0_SIZE   4
#define CSN1_E_UTRAN_Description_struct_EARFCN 456
#define CSN1_E_UTRAN_Description_struct_EARFCN_SIZE  16
#define CSN1_Enhanced_Measurement_report_SCALE 430
#define CSN1_Enhanced_Measurement_report_SCALE_SIZE   1
#define CSN1_Extension_Information_DTM_SUPPORT 674
#define CSN1_Extension_Information_DTM_SUPPORT_SIZE   1
#define CSN1_Extension_Information_NW_EXT_UTBF 677
#define CSN1_Extension_Information_NW_EXT_UTBF_SIZE   1
#define CSN1_GERAN_Iu_Mode_Capabilities_Length 359
#define CSN1_GERAN_Iu_Mode_Capabilities_Length_SIZE   4
#define CSN1_GPRS_BSIC_Description_struct_BSIC 1006
#define CSN1_GPRS_BSIC_Description_struct_BSIC_SIZE   6
#define CSN1_IPA_Downlink_Assignment_struct_TN 1167
#define CSN1_IPA_Downlink_Assignment_struct_TN_SIZE   3
#define CSN1_Multiple_TBF_Allocation_struct_P0 931
#define CSN1_Multiple_TBF_Allocation_struct_P0_SIZE   4
#define CSN1_NOTIFICATION_FACCH_BODY_B22_COUNT 418
#define CSN1_NOTIFICATION_FACCH_BODY_B22_COUNT_SIZE   1
#define CSN1_NOTIFICATION_FACCH_BODY_VSTK_RAND 419
#define CSN1_NOTIFICATION_FACCH_BODY_VSTK_RAND_SIZE  36
#define CSN1_PCID_Group_IE_PCID_Pattern_length 102
#define CSN1_PCID_Group_IE_PCID_Pattern_length_SIZE   3
#define CSN1_Paging_Information_eMLPP_priority 416
#define CSN1_Paging_Information_eMLPP_priority_SIZE   3
#define CSN1_Power_Control_Parameters_IE_ALPHA  88
#define CSN1_Power_Control_Parameters_IE_ALPHA_SIZE   4
#define CSN1_RFL_number_list_struct_RFL_NUMBER  83
#define CSN1_RFL_number_list_struct_RFL_NUMBER_SIZE   4
#define CSN1_RRClassmark3Value_ER_Band_Support 389
#define CSN1_RRClassmark3Value_ER_Band_Support_SIZE   1
#define CSN1_RRClassmark3Value_Offset_required 370
#define CSN1_RRClassmark3Value_Offset_required_SIZE   1
#define CSN1_RRClassmark3Value_Single_Slot_DTM 350
#define CSN1_RRClassmark3Value_Single_Slot_DTM_SIZE   1
#define CSN1_RRPacketUplinkAssignment_RLC_MODE 959
#define CSN1_RRPacketUplinkAssignment_RLC_MODE_SIZE   1
#define CSN1_SI13RestOctets_PSI1_REPEAT_PERIOD 896
#define CSN1_SI13RestOctets_PSI1_REPEAT_PERIOD_SIZE   4
#define CSN1_SI13_GPRS_Indicator_SI13_POSITION 585
#define CSN1_SI13_GPRS_Indicator_SI13_POSITION_SIZE   1
#define CSN1_Selection_Parameters_PENALTY_TIME 580
#define CSN1_Selection_Parameters_PENALTY_TIME_SIZE   5
#define CSN1_Serving_cell_data_struct_DTX_USED 432
#define CSN1_Serving_cell_data_struct_DTX_USED_SIZE   1
#define CSN1_Serving_cell_data_struct_MEAN_BEP 435
#define CSN1_Serving_cell_data_struct_MEAN_BEP_SIZE   5
#define CSN1_Single_Block_Allocation_struct_P0 986
#define CSN1_Single_Block_Allocation_struct_P0_SIZE   4
#define CSN1_Timeslot_description_struct_ALPHA 934
#define CSN1_Timeslot_description_struct_ALPHA_SIZE   4
#define CSN1_VGCSCipheringParameters_B22_COUNT  74
#define CSN1_VGCSCipheringParameters_B22_COUNT_SIZE   1
#define CSN1_VGCSCipheringParameters_VSTK_RAND  78
#define CSN1_VGCSCipheringParameters_VSTK_RAND_SIZE  40
#define CSN1_ChReqDesc2_Multiple_TBF_Capability 157
#define CSN1_ChReqDesc2_Multiple_TBF_Capability_SIZE   1
#define CSN1_Downlink_TBF_assignment_struct_PFI 829
#define CSN1_Downlink_TBF_assignment_struct_PFI_SIZE   7
#define CSN1_EGPRS_Packet_Uplink_Assignment_PFI 508
#define CSN1_EGPRS_Packet_Uplink_Assignment_PFI_SIZE   7
#define CSN1_EGPRS_Packet_Uplink_Assignment_TSH 506
#define CSN1_EGPRS_Packet_Uplink_Assignment_TSH_SIZE   2
#define CSN1_EGPRS_Packet_Uplink_Assignment_USF 488
#define CSN1_EGPRS_Packet_Uplink_Assignment_USF_SIZE   3
#define CSN1_Extension_Information_MNCI_SUPPORT 682
#define CSN1_Extension_Information_MNCI_SUPPORT_SIZE   1
#define CSN1_GPRS_Cell_Options_IE_DRX_TIMER_MAX 663
#define CSN1_GPRS_Cell_Options_IE_DRX_TIMER_MAX_SIZE   3
#define CSN1_IPA_Uplink_Assignment_struct_GAMMA 1153
#define CSN1_IPA_Uplink_Assignment_struct_GAMMA_SIZE   5
#define CSN1_Indirect_encoding_struct_MA_NUMBER 917
#define CSN1_Indirect_encoding_struct_MA_NUMBER_SIZE   4
#define CSN1_MS_Measurement_capability_SM_VALUE 336
#define CSN1_MS_Measurement_capability_SM_VALUE_SIZE   4
#define CSN1_Measurement_information__3G_BA_IND 687
#define CSN1_Measurement_information__3G_BA_IND_SIZE   1
#define CSN1_NOTIFICATION_FACCH_BODY_AMR_Config 422
#define CSN1_NOTIFICATION_FACCH_BODY_AMR_Config_SIZE   4
#define CSN1_Optional_Power_Offset_Power_Offset  70
#define CSN1_Optional_Power_Offset_Power_Offset_SIZE   2
#define CSN1_Packet_Downlink_Assignment_POLLING 525
#define CSN1_Packet_Downlink_Assignment_POLLING_SIZE   1
#define CSN1_Packet_Downlink_Assignment_PR_MODE 531
#define CSN1_Packet_Downlink_Assignment_PR_MODE_SIZE   1
#define CSN1_Paging_Information_mobile_identity 414
#define CSN1_Paging_Information_mobile_identity_SIZE   1
#define CSN1_RRPacketUplinkAssignment_RESEGMENT 956
#define CSN1_RRPacketUplinkAssignment_RESEGMENT_SIZE   1
#define CSN1_RRPktDownlinkAssi_EVENT_BASED_FANR 836
#define CSN1_RRPktDownlinkAssi_EVENT_BASED_FANR_SIZE   1
#define CSN1_SI13RestOctets_LB_MS_TXPWR_MAX_CCH 905
#define CSN1_SI13RestOctets_LB_MS_TXPWR_MAX_CCH_SIZE   5
#define CSN1_SI13RestOctets_PRIORITY_ACCESS_THR 892
#define CSN1_SI13RestOctets_PRIORITY_ACCESS_THR_SIZE   3
#define CSN1_SI2quaterRestOctets_MP_CHANGE_MARK 995
#define CSN1_SI2quaterRestOctets_MP_CHANGE_MARK_SIZE   1
#define CSN1_SI2quaterRestOctets__3G_CCN_ACTIVE 1067
#define CSN1_SI2quaterRestOctets__3G_CCN_ACTIVE_SIZE   1
#define CSN1_SI4_Rest_Octets_S_SI13alt_Position 599
#define CSN1_SI4_Rest_Octets_S_SI13alt_Position_SIZE   1
#define CSN1_SI6RestOctet_GPRS_MS_TXPWR_MAX_CCH 608
#define CSN1_SI6RestOctet_GPRS_MS_TXPWR_MAX_CCH_SIZE   5
#define CSN1_Serving_cell_data_struct_RXLEV_VAL 433
#define CSN1_Serving_cell_data_struct_RXLEV_VAL_SIZE   6
#define CSN1_further_cell_info_ms_txpwr_max_cch 1200
#define CSN1_further_cell_info_ms_txpwr_max_cch_SIZE   5
#define CSN1_further_cell_info_rxlev_access_min 1201
#define CSN1_further_cell_info_rxlev_access_min_SIZE   6
#define CSN1_further_cell_info_temporary_offset 1203
#define CSN1_further_cell_info_temporary_offset_SIZE   3
#define CSN1_ARFCN_index_list_struct_ARFCN_INDEX  84
#define CSN1_ARFCN_index_list_struct_ARFCN_INDEX_SIZE   6
#define CSN1_CDMA2000_Description_struct_TD_MODE 748
#define CSN1_CDMA2000_Description_struct_TD_MODE_SIZE   2
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN0  31
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN0_SIZE   5
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN1  33
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN1_SIZE   5
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN2  35
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN2_SIZE   5
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN3  37
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN3_SIZE   5
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN4  39
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN4_SIZE   5
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN5  41
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN5_SIZE   5
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN6  43
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN6_SIZE   5
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN7  45
#define CSN1_Dynamic_Allocation_struct_GAMMA_TN7_SIZE   5
#define CSN1_EGPRS_Packet_Uplink_Assignment_USF2 503
#define CSN1_EGPRS_Packet_Uplink_Assignment_USF2_SIZE   3
#define CSN1_Enhanced_Measurement_report_BA_USED 427
#define CSN1_Enhanced_Measurement_report_BA_USED_SIZE   1
#define CSN1_GPRS_Mobile_Allocation_IE_MA_BITMAP 398
#define CSN1_GPRS_Mobile_Allocation_IE_MA_BITMAP_SIZE   0
#define CSN1_GPRS_Mobile_Allocation_IE_MA_LENGTH 397
#define CSN1_GPRS_Mobile_Allocation_IE_MA_LENGTH_SIZE   6
#define CSN1_IPA_Downlink_Assignment_struct_TLLI 1161
#define CSN1_IPA_Downlink_Assignment_struct_TLLI_SIZE  32
#define CSN1_IndividualPriorities_GERAN_PRIORITY 642
#define CSN1_IndividualPriorities_GERAN_PRIORITY_SIZE   3
#define CSN1_MBMS_Information_MBMS_Sessions_List 1225
#define CSN1_MBMS_Information_MBMS_Sessions_List_SIZE   0
#define CSN1_MPRACH_Control_Parameters_IE_TX_INT 1194
#define CSN1_MPRACH_Control_Parameters_IE_TX_INT_SIZE   4
#define CSN1_MS_Measurement_capability_SMS_VALUE 335
#define CSN1_MS_Measurement_capability_SMS_VALUE_SIZE   4
#define CSN1_Measurement_information_REPORT_TYPE 692
#define CSN1_Measurement_information_REPORT_TYPE_SIZE   1
#define CSN1_NCELL_Report_struct_BCCH_FREQ_NCELL  20
#define CSN1_NCELL_Report_struct_BCCH_FREQ_NCELL_SIZE   5
#define CSN1_NOTIFY_APPLICATION_DATA_BODY_MSISDN 141
#define CSN1_NOTIFY_APPLICATION_DATA_BODY_MSISDN_SIZE   0
#define CSN1_P1RestOctets_Priority_Uplink_Access 1228
#define CSN1_P1RestOctets_Priority_Uplink_Access_SIZE   1
#define CSN1_PacketChannelDescription_spare_bits 196
#define CSN1_PacketChannelDescription_spare_bits_SIZE   2
#define CSN1_Packet_Downlink_Assignment_RLC_MODE 522
#define CSN1_Packet_Downlink_Assignment_RLC_MODE_SIZE   1
#define CSN1_Packet_Downlink_Assignment_TA_VALID 526
#define CSN1_Packet_Downlink_Assignment_TA_VALID_SIZE   1
#define CSN1_RRPktDownlinkAssi_BTS_PWR_CTRL_MODE 815
#define CSN1_RRPktDownlinkAssi_BTS_PWR_CTRL_MODE_SIZE   1
#define CSN1_RRPktDownlinkAssi_EGPRS_Window_Size 822
#define CSN1_RRPktDownlinkAssi_EGPRS_Window_Size_SIZE   5
#define CSN1_RRPktDownlinkAssi_NPM_Transfer_Time 835
#define CSN1_RRPktDownlinkAssi_NPM_Transfer_Time_SIZE   5
#define CSN1_SI13altRestOctets_PBCCH_Description 1146
#define CSN1_SI13altRestOctets_PBCCH_Description_SIZE   0
#define CSN1_SI2quaterRestOctets_SI2quater_COUNT 997
#define CSN1_SI2quaterRestOctets_SI2quater_COUNT_SIZE   4
#define CSN1_SI2quaterRestOctets_SI2quater_INDEX 996
#define CSN1_SI2quaterRestOctets_SI2quater_INDEX_SIZE   4
#define CSN1__8_PSK_Struct_Modulation_Capability 339
#define CSN1__8_PSK_Struct_Modulation_Capability_SIZE   1
#define CSN1_further_diff_cell_info_penalty_time 1213
#define CSN1_further_diff_cell_info_penalty_time_SIZE   5
#define CSN1_Downlink_TBF_assignment_2_struct_PFI 221
#define CSN1_Downlink_TBF_assignment_2_struct_PFI_SIZE   7
#define CSN1_EGPRS_Packet_Uplink_Assignment_ALPHA 496
#define CSN1_EGPRS_Packet_Uplink_Assignment_ALPHA_SIZE   4
#define CSN1_EGPRS_Packet_Uplink_Assignment_GAMMA 497
#define CSN1_EGPRS_Packet_Uplink_Assignment_GAMMA_SIZE   5
#define CSN1_ETWS_Primary_Notification_struct_PNI 1232
#define CSN1_ETWS_Primary_Notification_struct_PNI_SIZE   1
#define CSN1_IPA_Downlink_Assignment_struct_GAMMA 1163
#define CSN1_IPA_Downlink_Assignment_struct_GAMMA_SIZE   5
#define CSN1_NOTIFICATION_FACCH_BODY_Paging_Cause 423
#define CSN1_NOTIFICATION_FACCH_BODY_Paging_Cause_SIZE   2
#define CSN1_NTNRestOctets_Priority_Uplink_access 805
#define CSN1_NTNRestOctets_Priority_Uplink_access_SIZE   1
#define CSN1_Packet_Uplink_Assignment_Extended_RA 556
#define CSN1_Packet_Uplink_Assignment_Extended_RA_SIZE   5
#define CSN1_RRClassmark3Value_E_UTRA_FDD_support 377
#define CSN1_RRClassmark3Value_E_UTRA_FDD_support_SIZE   1
#define CSN1_RRClassmark3Value_E_UTRA_TDD_support 378
#define CSN1_RRClassmark3Value_E_UTRA_TDD_support_SIZE   1
#define CSN1_RRClassmark3Value_TIGHTER_Capability 383
#define CSN1_RRClassmark3Value_TIGHTER_Capability_SIZE   2
#define CSN1_RRPacketDownlinkAssignmentType2_FANR 867
#define CSN1_RRPacketDownlinkAssignmentType2_FANR_SIZE   1
#define CSN1_RRPktDownlinkAssi_MEASUREMENT_BITMAP 821
#define CSN1_RRPktDownlinkAssi_MEASUREMENT_BITMAP_SIZE   8
#define CSN1_SI10bis_Rest_Octets_SI10bis_Sequence 638
#define CSN1_SI10bis_Rest_Octets_SI10bis_Sequence_SIZE   2
#define CSN1_SI13RestOctets_NETWORK_CONTROL_ORDER 893
#define CSN1_SI13RestOctets_NETWORK_CONTROL_ORDER_SIZE   2
#define CSN1_SI2quaterRestOctets_extension_length 1035
#define CSN1_SI2quaterRestOctets_extension_length_SIZE   8
#define CSN1_Single_Block_Allocation_struct_ALPHA 984
#define CSN1_Single_Block_Allocation_struct_ALPHA_SIZE   4
#define CSN1_USF_Assignment_struct_USF_ALLOCATION 953
#define CSN1_USF_Assignment_struct_USF_ALLOCATION_SIZE   3
#define CSN1_Validity_Information_Validity_bitmap 454
#define CSN1_Validity_Information_Validity_bitmap_SIZE   3
#define CSN1_ChReqDesc2_PACKET_ESTABLISHMENT_CAUSE 149
#define CSN1_ChReqDesc2_PACKET_ESTABLISHMENT_CAUSE_SIZE   2
#define CSN1_ChReqDesc2_Reduced_Latency_Capability 159
#define CSN1_ChReqDesc2_Reduced_Latency_Capability_SIZE   1
#define CSN1_EGPRS_Modulation_and_Coding_IE_Scheme 491
#define CSN1_EGPRS_Modulation_and_Coding_IE_Scheme_SIZE   4
#define CSN1_Enhanced_Measurement_report_BSIC_Seen 429
#define CSN1_Enhanced_Measurement_report_BSIC_Seen_SIZE   1
#define CSN1_Extension_Information_EXT_UTBF_NODATA 679
#define CSN1_Extension_Information_EXT_UTBF_NODATA_SIZE   1
#define CSN1_GPRS_Cell_Options_IE_CONTROL_ACK_TYPE 665
#define CSN1_GPRS_Cell_Options_IE_CONTROL_ACK_TYPE_SIZE   1
#define CSN1_GSM_Description_struct_Band_Indicator 475
#define CSN1_GSM_Description_struct_Band_Indicator_SIZE   1
#define CSN1_NOTIFICATION_FACCH_BODY_Emergency_Ind 421
#define CSN1_NOTIFICATION_FACCH_BODY_Emergency_Ind_SIZE   1
#define CSN1_P1RestOctets_Packet_Page_Indication_1 1218
#define CSN1_P1RestOctets_Packet_Page_Indication_1_SIZE   1
#define CSN1_P1RestOctets_Packet_Page_Indication_2 1219
#define CSN1_P1RestOctets_Packet_Page_Indication_2_SIZE   1
#define CSN1_P2RestOctets_Packet_Page_Indication_3 1244
#define CSN1_P2RestOctets_Packet_Page_Indication_3_SIZE   1
#define CSN1_PacketChannelDescription_Channel_type 191
#define CSN1_PacketChannelDescription_Channel_type_SIZE   5
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN0  89
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN0_SIZE   5
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN1  90
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN1_SIZE   5
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN2  91
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN2_SIZE   5
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN3  92
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN3_SIZE   5
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN4  93
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN4_SIZE   5
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN5  94
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN5_SIZE   5
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN6  95
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN6_SIZE   5
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN7  96
#define CSN1_Power_Control_Parameters_IE_GAMMA_TN7_SIZE   5
#define CSN1_Pulse_Format_IE_Pulse_Format_Coding_1 967
#define CSN1_Pulse_Format_IE_Pulse_Format_Coding_1_SIZE   3
#define CSN1_Pulse_Format_IE_Pulse_Format_Coding_2 963
#define CSN1_Pulse_Format_IE_Pulse_Format_Coding_2_SIZE   0
#define CSN1_RRClassmark3Value_Multiband_supported 328
#define CSN1_RRClassmark3Value_Multiband_supported_SIZE   3
#define CSN1_RRPacketDownlinkAssignmentType2_P0_C1 848
#define CSN1_RRPacketDownlinkAssignmentType2_P0_C1_SIZE   4
#define CSN1_RRPacketDownlinkAssignmentType2_P0_C2 850
#define CSN1_RRPacketDownlinkAssignmentType2_P0_C2_SIZE   4
#define CSN1_RRPacketUplinkAssignment_Pulse_Format 962
#define CSN1_RRPacketUplinkAssignment_Pulse_Format_SIZE   0
#define CSN1_RRPacketUplinkAssignment_RLC_Entity_2 974
#define CSN1_RRPacketUplinkAssignment_RLC_Entity_2_SIZE   0
#define CSN1_RRPacketUplinkAssignment_RLC_Entity_3 975
#define CSN1_RRPacketUplinkAssignment_RLC_Entity_3_SIZE   0
#define CSN1_RRPktDownlinkAssi_TIMESLOT_ALLOCATION 812
#define CSN1_RRPktDownlinkAssi_TIMESLOT_ALLOCATION_SIZE   8
#define CSN1_SI10bis_Neighbour_Cell_Info_B22_COUNT 320
#define CSN1_SI10bis_Neighbour_Cell_Info_B22_COUNT_SIZE   1
#define CSN1_SI13RestOctets_GPRS_Mobile_Allocation 888
#define CSN1_SI13RestOctets_GPRS_Mobile_Allocation_SIZE   0
#define CSN1_SI21RestOctets_EAB_Authorization_Mask 294
#define CSN1_SI21RestOctets_EAB_Authorization_Mask_SIZE  10
#define CSN1_Selection_Parameters_TEMPORARY_OFFSET 579
#define CSN1_Selection_Parameters_TEMPORARY_OFFSET_SIZE   3
#define CSN1_Serving_cell_data_struct_RX_QUAL_FULL 434
#define CSN1_Serving_cell_data_struct_RX_QUAL_FULL_SIZE   3
#define CSN1_Timeslot_description_struct_GAMMA_TN0 936
#define CSN1_Timeslot_description_struct_GAMMA_TN0_SIZE   5
#define CSN1_Timeslot_description_struct_GAMMA_TN1 937
#define CSN1_Timeslot_description_struct_GAMMA_TN1_SIZE   5
#define CSN1_Timeslot_description_struct_GAMMA_TN2 938
#define CSN1_Timeslot_description_struct_GAMMA_TN2_SIZE   5
#define CSN1_Timeslot_description_struct_GAMMA_TN3 939
#define CSN1_Timeslot_description_struct_GAMMA_TN3_SIZE   5
#define CSN1_Timeslot_description_struct_GAMMA_TN4 940
#define CSN1_Timeslot_description_struct_GAMMA_TN4_SIZE   5
#define CSN1_Timeslot_description_struct_GAMMA_TN5 941
#define CSN1_Timeslot_description_struct_GAMMA_TN5_SIZE   5
#define CSN1_Timeslot_description_struct_GAMMA_TN6 942
#define CSN1_Timeslot_description_struct_GAMMA_TN6_SIZE   5
#define CSN1_Timeslot_description_struct_GAMMA_TN7 943
#define CSN1_Timeslot_description_struct_GAMMA_TN7_SIZE   5
#define CSN1_UPLINK_FREE_BODY_Uplink_Identity_Code 120
#define CSN1_UPLINK_FREE_BODY_Uplink_Identity_Code_SIZE   6
#define CSN1_UPLINK_FREE_BODY_short_layer_2_header 118
#define CSN1_UPLINK_FREE_BODY_short_layer_2_header_SIZE   2
#define CSN1_Uplink_TBF_Assignment_struct_RLC_MODE 946
#define CSN1_Uplink_TBF_Assignment_struct_RLC_MODE_SIZE   1
#define CSN1_VGCSCipheringParameters_Cell_Identity  76
#define CSN1_VGCSCipheringParameters_Cell_Identity_SIZE  16
#define CSN1_la_different_cell_reselect_hysteresis   6
#define CSN1_la_different_cell_reselect_hysteresis_SIZE   3
#define CSN1_neighbour_information_first_frequency 1198
#define CSN1_neighbour_information_first_frequency_SIZE   5
#define CSN1_BSIC_Description_struct_Remaining_BSIC 702
#define CSN1_BSIC_Description_struct_Remaining_BSIC_SIZE   7
#define CSN1_ChReqDesc2_Channel_Request_Description 150
#define CSN1_ChReqDesc2_Channel_Request_Description_SIZE  24
#define CSN1_EGPRS_Packet_Uplink_Assignment_POLLING 482
#define CSN1_EGPRS_Packet_Uplink_Assignment_POLLING_SIZE   1
#define CSN1_EGPRS_Packet_Uplink_Assignment_PR_MODE 487
#define CSN1_EGPRS_Packet_Uplink_Assignment_PR_MODE_SIZE   1
#define CSN1_E_UTRAN_CSG_Description_struct_CSG_PCI 1118
#define CSN1_E_UTRAN_CSG_Description_struct_CSG_PCI_SIZE   0
#define CSN1_E_UTRAN_Description_struct_TARGET_PCID 459
#define CSN1_E_UTRAN_Description_struct_TARGET_PCID_SIZE   9
#define CSN1_Extension_Information_PFC_FEATURE_MODE 673
#define CSN1_Extension_Information_PFC_FEATURE_MODE_SIZE   1
#define CSN1_Fixed_Allocation_struct_Message_escape 1400
#define CSN1_Fixed_Allocation_struct_Message_escape_SIZE   0
#define CSN1_GPRS_Cell_Options_IE_ACCESS_BURST_TYPE 664
#define CSN1_GPRS_Cell_Options_IE_ACCESS_BURST_TYPE_SIZE   1
#define CSN1_GPRS_Power_Control_Parameters_IE_ALPHA 107
#define CSN1_GPRS_Power_Control_Parameters_IE_ALPHA_SIZE   4
#define CSN1_IPA_Uplink_Assignment_struct_FN_OFFSET 1152
#define CSN1_IPA_Uplink_Assignment_struct_FN_OFFSET_SIZE   8
#define CSN1_Indirect_encoding_struct_CHANGE_MARK_1 918
#define CSN1_Indirect_encoding_struct_CHANGE_MARK_1_SIZE   2
#define CSN1_Indirect_encoding_struct_CHANGE_MARK_2 919
#define CSN1_Indirect_encoding_struct_CHANGE_MARK_2_SIZE   2
#define CSN1_MBMS_Information_P2_MBMS_Sessions_List 1246
#define CSN1_MBMS_Information_P2_MBMS_Sessions_List_SIZE   0
#define CSN1_Measurement_information_MP_CHANGE_MARK 688
#define CSN1_Measurement_information_MP_CHANGE_MARK_SIZE   1
#define CSN1_Measurement_information_REPORTING_RATE 693
#define CSN1_Measurement_information_REPORTING_RATE_SIZE   1
#define CSN1_Multiple_TBF_Allocation_struct_PR_MODE 932
#define CSN1_Multiple_TBF_Allocation_struct_PR_MODE_SIZE   1
#define CSN1_Network_Sharing_Information_struct_MCC 304
#define CSN1_Network_Sharing_Information_struct_MCC_SIZE  12
#define CSN1_Network_Sharing_Information_struct_MNC 305
#define CSN1_Network_Sharing_Information_struct_MNC_SIZE  12
#define CSN1_P1RestOctets_ETWS_Primary_Notification 1229
#define CSN1_P1RestOctets_ETWS_Primary_Notification_SIZE   0
#define CSN1_PacketChannelDescription_CHANGE_MARK_1 197
#define CSN1_PacketChannelDescription_CHANGE_MARK_1_SIZE   2
#define CSN1_PacketChannelDescription_MA_NUMBER_IND 195
#define CSN1_PacketChannelDescription_MA_NUMBER_IND_SIZE   1
#define CSN1_Packet_Downlink_Assignment_BEP_PERIOD2 534
#define CSN1_Packet_Downlink_Assignment_BEP_PERIOD2_SIZE   4
#define CSN1_RLC_Entity_Struct_DN_EGPRS_Window_Size 219
#define CSN1_RLC_Entity_Struct_DN_EGPRS_Window_Size_SIZE   5
#define CSN1_RLC_Entity_Struct_UP_EGPRS_Window_Size 214
#define CSN1_RLC_Entity_Struct_UP_EGPRS_Window_Size_SIZE   5
#define CSN1_RRPktDownlinkAssi_Downlink_EGPRS_Level 837
#define CSN1_RRPktDownlinkAssi_Downlink_EGPRS_Level_SIZE   2
#define CSN1_RRPktDownlinkAssi_MEASUREMENT_INTERVAL 820
#define CSN1_RRPktDownlinkAssi_MEASUREMENT_INTERVAL_SIZE   5
#define CSN1_SI10bis_Neighbour_Cell_Info_Tx_Integer 327
#define CSN1_SI10bis_Neighbour_Cell_Info_Tx_Integer_SIZE   4
#define CSN1_SI2terRestOctets_SI2ter_3G_CHANGE_MARK 232
#define CSN1_SI2terRestOctets_SI2ter_3G_CHANGE_MARK_SIZE   1
#define CSN1_SI2terRestOctets_SI2ter_MP_CHANGE_MARK 231
#define CSN1_SI2terRestOctets_SI2ter_MP_CHANGE_MARK_SIZE   1
#define CSN1_SI2terRestOctets_UTRAN_FDD_Description 235
#define CSN1_SI2terRestOctets_UTRAN_FDD_Description_SIZE   0
#define CSN1_SI2terRestOctets_UTRAN_TDD_Description 238
#define CSN1_SI2terRestOctets_UTRAN_TDD_Description_SIZE   0
#define CSN1_Single_Block_Allocation_struct_PR_MODE 987
#define CSN1_Single_Block_Allocation_struct_PR_MODE_SIZE   1
#define CSN1_UPLINK_FREE_BODY_Uplink_Access_Request 119
#define CSN1_UPLINK_FREE_BODY_Uplink_Access_Request_SIZE   1
#define CSN1_UTRAN_CSG_Measurement_Report_IE_CSG_ID 410
#define CSN1_UTRAN_CSG_Measurement_Report_IE_CSG_ID_SIZE  27
#define CSN1_further_cell_info_cell_reselect_offset 1202
#define CSN1_further_cell_info_cell_reselect_offset_SIZE   6
#define CSN1_CDMA2000_Description_struct_WALSH_LEN_A 749
#define CSN1_CDMA2000_Description_struct_WALSH_LEN_A_SIZE   3
#define CSN1_CDMA2000_Description_struct_WALSH_LEN_B 745
#define CSN1_CDMA2000_Description_struct_WALSH_LEN_B_SIZE   3
#define CSN1_CDMA2000_Description_struct_WALSH_LEN_C 737
#define CSN1_CDMA2000_Description_struct_WALSH_LEN_C_SIZE   3
#define CSN1_Channel_Request_Description_IE_RLC_MODE 153
#define CSN1_Channel_Request_Description_IE_RLC_MODE_SIZE   1
#define CSN1_DTMInfoRestOctets_GPRS_MS_TXPWR_MAX_CCH 166
#define CSN1_DTMInfoRestOctets_GPRS_MS_TXPWR_MAX_CCH_SIZE   5
#define CSN1_Downlink_TBF_assignment_struct_RLC_MODE 830
#define CSN1_Downlink_TBF_assignment_struct_RLC_MODE_SIZE   1
#define CSN1_Enhanced_Measurement_report__3G_BA_USED 428
#define CSN1_Enhanced_Measurement_report__3G_BA_USED_SIZE   1
#define CSN1_IPA_Downlink_Assignment_struct_RLC_MODE 1166
#define CSN1_IPA_Downlink_Assignment_struct_RLC_MODE_SIZE   1
#define CSN1_List_of_VSTK_RAND_information_VSTK_RAND 804
#define CSN1_List_of_VSTK_RAND_information_VSTK_RAND_SIZE  36
#define CSN1_Packet_Uplink_Assignment_TFI_ASSIGNMENT 541
#define CSN1_Packet_Uplink_Assignment_TFI_ASSIGNMENT_SIZE   5
#define CSN1_RRPacketUplinkAssignment_EGPRS_MCS_MODE 955
#define CSN1_RRPacketUplinkAssignment_EGPRS_MCS_MODE_SIZE   4
#define CSN1_RRPktDownlinkAssi_Packet_Timing_Advance 813
#define CSN1_RRPktDownlinkAssi_Packet_Timing_Advance_SIZE   0
#define CSN1_RRPktDownlinkAssi_UTRAN_FREQUENCY_INDEX 841
#define CSN1_RRPktDownlinkAssi_UTRAN_FREQUENCY_INDEX_SIZE   5
#define CSN1_SI10bis_Neighbour_Cell_Info_Max_retrans 326
#define CSN1_SI10bis_Neighbour_Cell_Info_Max_retrans_SIZE   2
#define CSN1_SI2quaterRestOctets__3G_CSG_Description 1116
#define CSN1_SI2quaterRestOctets__3G_CSG_Description_SIZE   0
#define CSN1_Segmented_SMS_Description_struct_Length 130
#define CSN1_Segmented_SMS_Description_struct_Length_SIZE   8
#define CSN1_Single_Block_Allocation_struct_GAMMA_TN 985
#define CSN1_Single_Block_Allocation_struct_GAMMA_TN_SIZE   5
#define CSN1_UTRAN_CSG_Measurement_Report_IE_PLMN_ID 409
#define CSN1_UTRAN_CSG_Measurement_Report_IE_PLMN_ID_SIZE  24
#define CSN1_VBS_VGCS_RECONFIGURE_BODY_Starting_Time 116
#define CSN1_VBS_VGCS_RECONFIGURE_BODY_Starting_Time_SIZE  16
#define CSN1_further_diff_cell_info_ms_txpwr_max_cch 1209
#define CSN1_further_diff_cell_info_ms_txpwr_max_cch_SIZE   5
#define CSN1_further_diff_cell_info_rxlev_access_min 1210
#define CSN1_further_diff_cell_info_rxlev_access_min_SIZE   6
#define CSN1_further_diff_cell_info_temporary_offset 1212
#define CSN1_further_diff_cell_info_temporary_offset_SIZE   3
#define CSN1_CDMA2000_Description_struct_AUX_TD_WALSH 746
#define CSN1_CDMA2000_Description_struct_AUX_TD_WALSH_SIZE   0
#define CSN1_EGPRS_Packet_Uplink_Assignment_RESEGMENT 494
#define CSN1_EGPRS_Packet_Uplink_Assignment_RESEGMENT_SIZE   1
#define CSN1_Enhanced_Measurement_report_SI23_BA_USED 450
#define CSN1_Enhanced_Measurement_report_SI23_BA_USED_SIZE   1
#define CSN1_Fixed_Allocation_struct_FINAL_ALLOCATION 201
#define CSN1_Fixed_Allocation_struct_FINAL_ALLOCATION_SIZE   1
#define CSN1_Fixed_Allocation_struct_HALF_DUPLEX_MODE 208
#define CSN1_Fixed_Allocation_struct_HALF_DUPLEX_MODE_SIZE   1
#define CSN1_GPRS_Power_Control_Parameters_IE_N_AVG_I 111
#define CSN1_GPRS_Power_Control_Parameters_IE_N_AVG_I_SIZE   4
#define CSN1_GPRS_Power_Control_Parameters_IE_T_AVG_T 109
#define CSN1_GPRS_Power_Control_Parameters_IE_T_AVG_T_SIZE   5
#define CSN1_GPRS_Power_Control_Parameters_IE_T_AVG_W 108
#define CSN1_GPRS_Power_Control_Parameters_IE_T_AVG_W_SIZE   5
#define CSN1_IndividualPriorities_T3230_timeout_value 654
#define CSN1_IndividualPriorities_T3230_timeout_value_SIZE   3
#define CSN1_List_of_VSTK_RAND_information_Segment_Id 803
#define CSN1_List_of_VSTK_RAND_information_Segment_Id_SIZE   1
#define CSN1_MBMS_Information_MBMS_Channel_Parameters 1226
#define CSN1_MBMS_Information_MBMS_Channel_Parameters_SIZE   0
#define CSN1_MPRACH_Control_Parameters_IE_MAX_RETRANS 1192
#define CSN1_MPRACH_Control_Parameters_IE_MAX_RETRANS_SIZE   2
#define CSN1_Measurement_information_BSIC_Description 698
#define CSN1_Measurement_information_BSIC_Description_SIZE   0
#define CSN1_Measurement_information_extension_length 721
#define CSN1_Measurement_information_extension_length_SIZE   8
#define CSN1_NTNRestOctets_SMS_Guaranteed_Privacy_Ind 809
#define CSN1_NTNRestOctets_SMS_Guaranteed_Privacy_Ind_SIZE   1
#define CSN1_Packet_Uplink_Assignment_USF_GRANULARITY 549
#define CSN1_Packet_Uplink_Assignment_USF_GRANULARITY_SIZE   1
#define CSN1_RRPacketDownlinkAssignmentType2_RLC_MODE 847
#define CSN1_RRPacketDownlinkAssignmentType2_RLC_MODE_SIZE   1
#define CSN1_RRPktDownlinkAssi_EMSR_Additional_PFCs_1 844
#define CSN1_RRPktDownlinkAssi_EMSR_Additional_PFCs_1_SIZE   0
#define CSN1_RRPktDownlinkAssi_EMSR_Additional_PFCs_2 845
#define CSN1_RRPktDownlinkAssi_EMSR_Additional_PFCs_2_SIZE   0
#define CSN1_RRPktDownlinkAssi_EMSR_Additional_PFCs_3 846
#define CSN1_RRPktDownlinkAssi_EMSR_Additional_PFCs_3_SIZE   0
#define CSN1_SI10bis_Rest_Octets_Position_in_SI5_list 639
#define CSN1_SI10bis_Rest_Octets_Position_in_SI5_list_SIZE   5
#define CSN1_Serving_cell_data_struct_NBR_RCVD_BLOCKS 437
#define CSN1_Serving_cell_data_struct_NBR_RCVD_BLOCKS_SIZE   5
#define CSN1__3G_CSG_Description_struct_CSG_PSC_SPLIT 266
#define CSN1__3G_CSG_Description_struct_CSG_PSC_SPLIT_SIZE   0
#define CSN1_CDMA2000_Description_struct_AUX_WALSH_LEN 738
#define CSN1_CDMA2000_Description_struct_AUX_WALSH_LEN_SIZE   0
#define CSN1_CDMA2000_Description_struct_WALSH_LENGTH1 740
#define CSN1_CDMA2000_Description_struct_WALSH_LENGTH1_SIZE   3
#define CSN1_CDMA2000_Description_struct_WALSH_LENGTH2 743
#define CSN1_CDMA2000_Description_struct_WALSH_LENGTH2_SIZE   3
#define CSN1_Downlink_TBF_assignment_2_struct_RLC_MODE 222
#define CSN1_Downlink_TBF_assignment_2_struct_RLC_MODE_SIZE   1
#define CSN1_Dynamic_Allocation_struct_USF_GRANULARITY  26
#define CSN1_Dynamic_Allocation_struct_USF_GRANULARITY_SIZE   1
#define CSN1_EGPRS_Modulation_and_coding_Scheme_Scheme 950
#define CSN1_EGPRS_Modulation_and_coding_Scheme_Scheme_SIZE   4
#define CSN1_E_UTRAN_CSG_Description_struct_CSG_EARFCN 1121
#define CSN1_E_UTRAN_CSG_Description_struct_CSG_EARFCN_SIZE  16
#define CSN1_Enhanced_Measurement_report_BITMAP_LENGTH 443
#define CSN1_Enhanced_Measurement_report_BITMAP_LENGTH_SIZE   7
#define CSN1_Fixed_Allocation_struct_ALLOCATION_BITMAP 211
#define CSN1_Fixed_Allocation_struct_ALLOCATION_BITMAP_SIZE   0
#define CSN1_Fixed_Allocation_struct_BTS_PWR_CTRL_MODE 204
#define CSN1_Fixed_Allocation_struct_BTS_PWR_CTRL_MODE_SIZE   1
#define CSN1_Frequency_Parameters_IE_Direct_encoding_1 912
#define CSN1_Frequency_Parameters_IE_Direct_encoding_1_SIZE   0
#define CSN1_Frequency_Parameters_IE_Direct_encoding_2 920
#define CSN1_Frequency_Parameters_IE_Direct_encoding_2_SIZE   0
#define CSN1_Frequency_Parameters_IE_Indirect_encoding 915
#define CSN1_Frequency_Parameters_IE_Indirect_encoding_SIZE   0
#define CSN1_GPRS_Mobile_Allocation_IE_RFL_number_list 395
#define CSN1_GPRS_Mobile_Allocation_IE_RFL_number_list_SIZE   0
#define CSN1_MeasurementResults_RXLEV_SUB_SERVING_CELL 570
#define CSN1_MeasurementResults_RXLEV_SUB_SERVING_CELL_SIZE   6
#define CSN1_NOTIFICATION_FACCH_BODY_CELL_GLOBAL_COUNT 417
#define CSN1_NOTIFICATION_FACCH_BODY_CELL_GLOBAL_COUNT_SIZE   2
#define CSN1_Network_Sharing_Information_struct_PS_ACC 308
#define CSN1_Network_Sharing_Information_struct_PS_ACC_SIZE  16
#define CSN1_Packet_Downlink_Assignment_TFI_ASSIGNMENT 521
#define CSN1_Packet_Downlink_Assignment_TFI_ASSIGNMENT_SIZE   5
#define CSN1_RRClassmark3Value_GERAN_Feature_Package_1 355
#define CSN1_RRClassmark3Value_GERAN_Feature_Package_1_SIZE   1
#define CSN1_RRClassmark3Value_GERAN_Feature_Package_2 361
#define CSN1_RRClassmark3Value_GERAN_Feature_Package_2_SIZE   1
#define CSN1_RRClassmark3Value_GSM_400_Bands_Supported 342
#define CSN1_RRClassmark3Value_GSM_400_Bands_Supported_SIZE   2
#define CSN1_RRPacketUplinkAssignment_Fixed_Allocation 981
#define CSN1_RRPacketUplinkAssignment_Fixed_Allocation_SIZE   0
#define CSN1_RRPktDownlinkAssi_DOWNLINK_TFI_ASSIGNMENT 818
#define CSN1_RRPktDownlinkAssi_DOWNLINK_TFI_ASSIGNMENT_SIZE   5
#define CSN1_RRPktDownlinkAssi_E_UTRAN_FREQUENCY_INDEX 839
#define CSN1_RRPktDownlinkAssi_E_UTRAN_FREQUENCY_INDEX_SIZE   3
#define CSN1_SI10bis_Neighbour_Cell_Info_FR_AMR_Config 322
#define CSN1_SI10bis_Neighbour_Cell_Info_FR_AMR_Config_SIZE   4
#define CSN1_SI10bis_Neighbour_Cell_Info_HR_AMR_Config 323
#define CSN1_SI10bis_Neighbour_Cell_Info_HR_AMR_Config_SIZE   4
#define CSN1_SI2quaterRestOctets_GPRS_BSIC_Description 1004
#define CSN1_SI2quaterRestOctets_GPRS_BSIC_Description_SIZE   0
#define CSN1_SI2quaterRestOctets__700_REPORTING_OFFSET 1068
#define CSN1_SI2quaterRestOctets__700_REPORTING_OFFSET_SIZE   3
#define CSN1_SI2quaterRestOctets__810_REPORTING_OFFSET 1070
#define CSN1_SI2quaterRestOctets__810_REPORTING_OFFSET_SIZE   3
#define CSN1_Second_Part_Packet_Assignment_Extended_RA 558
#define CSN1_Second_Part_Packet_Assignment_Extended_RA_SIZE   5
#define CSN1_Selection_Parameters_CELL_RESELECT_OFFSET 578
#define CSN1_Selection_Parameters_CELL_RESELECT_OFFSET_SIZE   6
#define CSN1_UTRAN_CSG_Measurement_Report_IE_UTRAN_CGI 408
#define CSN1_UTRAN_CSG_Measurement_Report_IE_UTRAN_CGI_SIZE  28
#define CSN1_UTRAN_FDD_Description_struct_CS_Diversity 465
#define CSN1_UTRAN_FDD_Description_struct_CS_Diversity_SIZE   1
#define CSN1_UTRAN_FDD_Description_struct_CS_FDD_ARFCN 462
#define CSN1_UTRAN_FDD_Description_struct_CS_FDD_ARFCN_SIZE  14
#define CSN1_UTRAN_TDD_Description_struct_CS_TDD_ARFCN 470
#define CSN1_UTRAN_TDD_Description_struct_CS_TDD_ARFCN_SIZE  14
#define CSN1_VGCSCipheringParameters_CELL_GLOBAL_COUNT  75
#define CSN1_VGCSCipheringParameters_CELL_GLOBAL_COUNT_SIZE   2
#define CSN1_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY_BSIC 453
#define CSN1_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY_BSIC_SIZE   6
#define CSN1__3G_CSG_Description_struct_CSG_FDD_UARFCN 272
#define CSN1__3G_CSG_Description_struct_CSG_FDD_UARFCN_SIZE  14
#define CSN1__3G_CSG_Description_struct_CSG_TDD_UARFCN 273
#define CSN1__3G_CSG_Description_struct_CSG_TDD_UARFCN_SIZE  14
#define CSN1_CDMA2000_Description_struct_SR3_PRIM_PILOT 733
#define CSN1_CDMA2000_Description_struct_SR3_PRIM_PILOT_SIZE   2
#define CSN1_CDMA2000_Description_struct_TD_POWER_LEVEL 751
#define CSN1_CDMA2000_Description_struct_TD_POWER_LEVEL_SIZE   3
#define CSN1_Downlink_TBF_assignment_struct_CONTROL_ACK 832
#define CSN1_Downlink_TBF_assignment_struct_CONTROL_ACK_SIZE   1
#define CSN1_EGPRS_Packet_Uplink_Assignment_BEP_PERIOD2 493
#define CSN1_EGPRS_Packet_Uplink_Assignment_BEP_PERIOD2_SIZE   4
#define CSN1_EGPRS_Packet_Uplink_Assignment_Extended_RA 479
#define CSN1_EGPRS_Packet_Uplink_Assignment_Extended_RA_SIZE   5
#define CSN1_GPRS_Mobile_Allocation_IE_ARFCN_index_list 396
#define CSN1_GPRS_Mobile_Allocation_IE_ARFCN_index_list_SIZE   0
#define CSN1_MPRACH_description_IE_Frequency_Parameters 1187
#define CSN1_MPRACH_description_IE_Frequency_Parameters_SIZE   0
#define CSN1_MeasurementResults_RXLEV_FULL_SERVING_CELL 567
#define CSN1_MeasurementResults_RXLEV_FULL_SERVING_CELL_SIZE   6
#define CSN1_MeasurementResults_RXQUAL_SUB_SERVING_CELL 573
#define CSN1_MeasurementResults_RXQUAL_SUB_SERVING_CELL_SIZE   3
#define CSN1_NOTIFY_APPLICATION_DATA_BODY_MSISDN_length 140
#define CSN1_NOTIFY_APPLICATION_DATA_BODY_MSISDN_length_SIZE   4
#define CSN1_NOTIFY_APPLICATION_DATA_BODY_data_identity 139
#define CSN1_NOTIFY_APPLICATION_DATA_BODY_data_identity_SIZE   8
#define CSN1_NTNRestOctets_SMS_Data_Confidentiality_Ind 808
#define CSN1_NTNRestOctets_SMS_Data_Confidentiality_Ind_SIZE   1
#define CSN1_Packet_Uplink_Assignment_ALLOCATION_BITMAP 544
#define CSN1_Packet_Uplink_Assignment_ALLOCATION_BITMAP_SIZE   0
#define CSN1_Packet_Uplink_Assignment_BTS_PWR_CTRL_MODE 546
#define CSN1_Packet_Uplink_Assignment_BTS_PWR_CTRL_MODE_SIZE   1
#define CSN1_Packet_Uplink_Assignment_TBF_STARTING_TIME 555
#define CSN1_Packet_Uplink_Assignment_TBF_STARTING_TIME_SIZE  16
#define CSN1_RLC_Entity_Struct_UP_UPLINK_TFI_ASSIGNMENT 212
#define CSN1_RLC_Entity_Struct_UP_UPLINK_TFI_ASSIGNMENT_SIZE   5
#define CSN1_RRClassmark3Value_Repeated_ACCH_Capability 372
#define CSN1_RRClassmark3Value_Repeated_ACCH_Capability_SIZE   1
#define CSN1_RRClassmark3Value_UTRA_CSG_Cells_Reporting 381
#define CSN1_RRClassmark3Value_UTRA_CSG_Cells_Reporting_SIZE   1
#define CSN1_RRPacketDownlinkAssignmentType2_PR_MODE_C1 849
#define CSN1_RRPacketDownlinkAssignmentType2_PR_MODE_C1_SIZE   1
#define CSN1_RRPacketDownlinkAssignmentType2_PR_MODE_C2 851
#define CSN1_RRPacketDownlinkAssignmentType2_PR_MODE_C2_SIZE   1
#define CSN1_RRPacketUplinkAssignment_EGPRS_Window_Size 957
#define CSN1_RRPacketUplinkAssignment_EGPRS_Window_Size_SIZE   5
#define CSN1_RRPacketUplinkAssignment_NPM_Transfer_Time 960
#define CSN1_RRPacketUplinkAssignment_NPM_Transfer_Time_SIZE   5
#define CSN1_RRPktDownlinkAssi_Power_Control_Parameters 817
#define CSN1_RRPktDownlinkAssi_Power_Control_Parameters_SIZE   0
#define CSN1_SI10bis_Neighbour_Cell_Info_Frequency_List 318
#define CSN1_SI10bis_Neighbour_Cell_Info_Frequency_List_SIZE   0
#define CSN1_SI22RestOctets_Network_Sharing_Information 299
#define CSN1_SI22RestOctets_Network_Sharing_Information_SIZE   0
#define CSN1_SI2_UTRAN_FDD_Description_struct_FDD_ARFCN 236
#define CSN1_SI2_UTRAN_FDD_Description_struct_FDD_ARFCN_SIZE  14
#define CSN1_SI2_UTRAN_TDD_Description_struct_TDD_ARFCN 239
#define CSN1_SI2_UTRAN_TDD_Description_struct_TDD_ARFCN_SIZE  14
#define CSN1_SI2quaterRestOctets_NC2_CSG_PCCN_permitted 1130
#define CSN1_SI2quaterRestOctets_NC2_CSG_PCCN_permitted_SIZE   1
#define CSN1_UTRAN_FDD_Description_struct_Bandwidth_FDD 249
#define CSN1_UTRAN_FDD_Description_struct_Bandwidth_FDD_SIZE   3
#define CSN1_UTRAN_FDD_Description_struct_CS_FDD_Indic0 463
#define CSN1_UTRAN_FDD_Description_struct_CS_FDD_Indic0_SIZE   1
#define CSN1_UTRAN_TDD_Description_struct_Bandwidth_TDD 255
#define CSN1_UTRAN_TDD_Description_struct_Bandwidth_TDD_SIZE   3
#define CSN1_UTRAN_TDD_Description_struct_CS_TDD_Indic0 471
#define CSN1_UTRAN_TDD_Description_struct_CS_TDD_Indic0_SIZE   1
#define CSN1__8_PSK_Struct__8_PSK_RF_Power_Capability_1 340
#define CSN1__8_PSK_Struct__8_PSK_RF_Power_Capability_1_SIZE   2
#define CSN1__8_PSK_Struct__8_PSK_RF_Power_Capability_2 341
#define CSN1__8_PSK_Struct__8_PSK_RF_Power_Capability_2_SIZE   2
#define CSN1_Additional_PFCs_struct_DN_NPM_Transfer_Time  50
#define CSN1_Additional_PFCs_struct_DN_NPM_Transfer_Time_SIZE   5
#define CSN1_Additional_PFCs_struct_UP_NPM_Transfer_Time  47
#define CSN1_Additional_PFCs_struct_UP_NPM_Transfer_Time_SIZE   5
#define CSN1_BSIC_Description_struct_BA_Index_Start_BSIC 699
#define CSN1_BSIC_Description_struct_BA_Index_Start_BSIC_SIZE   5
#define CSN1_BSIC_Description_struct_Frequency_Scrolling 703
#define CSN1_BSIC_Description_struct_Frequency_Scrolling_SIZE   1
#define CSN1_CCN_Support_Description_struct_Number_Cells 1037
#define CSN1_CCN_Support_Description_struct_Number_Cells_SIZE   7
#define CSN1_CDMA2000_Description_struct_AUX_PILOT_WALSH 750
#define CSN1_CDMA2000_Description_struct_AUX_PILOT_WALSH_SIZE   0
#define CSN1_CDMA2000_Description_struct_Pilot_PN_offset 732
#define CSN1_CDMA2000_Description_struct_Pilot_PN_offset_SIZE   9
#define CSN1_E_UTRAN_Measurement_Report_struct_N_E_UTRAN 445
#define CSN1_E_UTRAN_Measurement_Report_struct_N_E_UTRAN_SIZE   2
#define CSN1_Fixed_Allocation_struct_TIMESLOT_ALLOCATION 207
#define CSN1_Fixed_Allocation_struct_TIMESLOT_ALLOCATION_SIZE   8
#define CSN1_GPRSBCastInfo_GPRS_Power_Control_Parameters 799
#define CSN1_GPRSBCastInfo_GPRS_Power_Control_Parameters_SIZE  19
#define CSN1_Group_Call_information_Group_Call_Reference 142
#define CSN1_Group_Call_information_Group_Call_Reference_SIZE  36
#define CSN1_Group_Channel_Description_Mobile_Allocation   8
#define CSN1_Group_Channel_Description_Mobile_Allocation_SIZE   0
#define CSN1_IARestOctets_Length_of_frequency_parameters 559
#define CSN1_IARestOctets_Length_of_frequency_parameters_SIZE   6
#define CSN1_IPA_Uplink_Assignment_struct_TFI_ASSIGNMENT 1155
#define CSN1_IPA_Uplink_Assignment_struct_TFI_ASSIGNMENT_SIZE   5
#define CSN1_MBMS_Information_P2_MBMS_Channel_Parameters 1247
#define CSN1_MBMS_Information_P2_MBMS_Channel_Parameters_SIZE   0
#define CSN1_MBMS_Sessions_List_IE_MBMS_Session_Identity 400
#define CSN1_MBMS_Sessions_List_IE_MBMS_Session_Identity_SIZE   8
#define CSN1_MeasurementResults_RXQUAL_FULL_SERVING_CELL 572
#define CSN1_MeasurementResults_RXQUAL_FULL_SERVING_CELL_SIZE   3
#define CSN1_Measurement_information__3G_CSG_Description 793
#define CSN1_Measurement_information__3G_CSG_Description_SIZE   0
#define CSN1_MultirateSpeechCfgIE_Set_of_AMR_codec_modes 176
#define CSN1_MultirateSpeechCfgIE_Set_of_AMR_codec_modes_SIZE   8
#define CSN1_Non_Segmented_SMS_Description_struct_Length 134
#define CSN1_Non_Segmented_SMS_Description_struct_Length_SIZE   8
#define CSN1_Packet_Downlink_Assignment_EVENT_BASED_FANR 537
#define CSN1_Packet_Downlink_Assignment_EVENT_BASED_FANR_SIZE   1
#define CSN1_RRClassmark3Value_DTM_GPRS_Multi_Slot_Class 349
#define CSN1_RRClassmark3Value_DTM_GPRS_Multi_Slot_Class_SIZE   2
#define CSN1_RRClassmark3Value_High_Multislot_Capability 358
#define CSN1_RRClassmark3Value_High_Multislot_Capability_SIZE   2
#define CSN1_RRClassmark3Value_T_GSM_400_Bands_Supported 364
#define CSN1_RRClassmark3Value_T_GSM_400_Bands_Supported_SIZE   2
#define CSN1_RRPacketUplinkAssignment_Dynamic_Allocation 980
#define CSN1_RRPacketUplinkAssignment_Dynamic_Allocation_SIZE   0
#define CSN1_RRPacketUplinkAssignment_EMST_NW_Capability 976
#define CSN1_RRPacketUplinkAssignment_EMST_NW_Capability_SIZE   1
#define CSN1_RRPacketUplinkAssignment_REPORTED_TIMESLOTS 968
#define CSN1_RRPacketUplinkAssignment_REPORTED_TIMESLOTS_SIZE   8
#define CSN1_RRPacketUplinkAssignment_Uplink_EGPRS_Level 961
#define CSN1_RRPacketUplinkAssignment_Uplink_EGPRS_Level_SIZE   2
#define CSN1_RRPktDownlinkAssi_MEASUREMENT_STARTING_TIME 819
#define CSN1_RRPktDownlinkAssi_MEASUREMENT_STARTING_TIME_SIZE  16
#define CSN1_RRPktDownlinkAssi_Measurement_Control_UTRAN 840
#define CSN1_RRPktDownlinkAssi_Measurement_Control_UTRAN_SIZE   1
#define CSN1_SI2quaterRestOctets_E_UTRAN_CSG_Description 1117
#define CSN1_SI2quaterRestOctets_E_UTRAN_CSG_Description_SIZE   0
#define CSN1_Timeslot_description_struct_USF_GRANULARITY 935
#define CSN1_Timeslot_description_struct_USF_GRANULARITY_SIZE   1
#define CSN1_UTRAN_CSG_Measurement_Report_IE_Access_Mode 411
#define CSN1_UTRAN_CSG_Measurement_Report_IE_Access_Mode_SIZE   1
#define CSN1_Uplink_TBF_Assignment_struct_USF_ALLOCATION 954
#define CSN1_Uplink_TBF_Assignment_struct_USF_ALLOCATION_SIZE   3
#define CSN1_Uplink_TBF_Assignment_struct_USF_Assignment 952
#define CSN1_Uplink_TBF_Assignment_struct_USF_Assignment_SIZE   0
#define CSN1_further_diff_cell_info_cell_reselect_offset 1211
#define CSN1_further_diff_cell_info_cell_reselect_offset_SIZE   6
#define CSN1_CCN_Support_Description_struct_CCN_SUPPORTED 1038
#define CSN1_CCN_Support_Description_struct_CCN_SUPPORTED_SIZE   0
#define CSN1_CDMA2000_Description_struct_AUX_PILOT_WALSH1 741
#define CSN1_CDMA2000_Description_struct_AUX_PILOT_WALSH1_SIZE   0
#define CSN1_CDMA2000_Description_struct_AUX_PILOT_WALSH2 744
#define CSN1_CDMA2000_Description_struct_AUX_PILOT_WALSH2_SIZE   0
#define CSN1_CDMA2000_Description_struct_SR3_PILOT_POWER1 734
#define CSN1_CDMA2000_Description_struct_SR3_PILOT_POWER1_SIZE   3
#define CSN1_CDMA2000_Description_struct_SR3_PILOT_POWER2 735
#define CSN1_CDMA2000_Description_struct_SR3_PILOT_POWER2_SIZE   3
#define CSN1_Channel_Request_Description_IE_LLC__PDU_TYPE 154
#define CSN1_Channel_Request_Description_IE_LLC__PDU_TYPE_SIZE   1
#define CSN1_Downlink_TBF_assignment_2_struct_CONTROL_ACK 224
#define CSN1_Downlink_TBF_assignment_2_struct_CONTROL_ACK_SIZE   1
#define CSN1_EGPRS_Packet_Uplink_Assignment_RTTI_USF_MODE 500
#define CSN1_EGPRS_Packet_Uplink_Assignment_RTTI_USF_MODE_SIZE   1
#define CSN1_E_UTRAN_CSG_Description_struct_CSG_PCI_SPLIT 1119
#define CSN1_E_UTRAN_CSG_Description_struct_CSG_PCI_SPLIT_SIZE   0
#define CSN1_E_UTRAN_Description_struct_Not_Allowed_Cells 458
#define CSN1_E_UTRAN_Description_struct_Not_Allowed_Cells_SIZE   0
#define CSN1_Extension_Information_REDUCED_LATENCY_ACCESS 683
#define CSN1_Extension_Information_REDUCED_LATENCY_ACCESS_SIZE   1
#define CSN1_GERAN_Iu_Mode_Capabilities_FLO_Iu_Capability 360
#define CSN1_GERAN_Iu_Mode_Capabilities_FLO_Iu_Capability_SIZE   1
#define CSN1_GPRS_BSIC_Description_struct_Remaining_BSICs 1008
#define CSN1_GPRS_BSIC_Description_struct_Remaining_BSICs_SIZE   0
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_TN 1174
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_TN_SIZE   3
#define CSN1_MPRACH_Control_Parameters_IE_ACC_CONTR_CLASS 1191
#define CSN1_MPRACH_Control_Parameters_IE_ACC_CONTR_CLASS_SIZE  16
#define CSN1_MPRACH_description_IE_MPRACH_TIMESLOT_NUMBER 1188
#define CSN1_MPRACH_description_IE_MPRACH_TIMESLOT_NUMBER_SIZE   3
#define CSN1_Measurement_information_Short_layer_2_header 685
#define CSN1_Measurement_information_Short_layer_2_header_SIZE   2
#define CSN1_NOTIFICATION_FACCH_BODY_short_layer_2_header 413
#define CSN1_NOTIFICATION_FACCH_BODY_short_layer_2_header_SIZE   2
#define CSN1_Packet_Downlink_Assignment_BTS_PWR_CTRL_MODE 530
#define CSN1_Packet_Downlink_Assignment_BTS_PWR_CTRL_MODE_SIZE   1
#define CSN1_Packet_Downlink_Assignment_EGPRS_Window_Size 532
#define CSN1_Packet_Downlink_Assignment_EGPRS_Window_Size_SIZE   5
#define CSN1_Packet_Downlink_Assignment_NPM_Transfer_Time 536
#define CSN1_Packet_Downlink_Assignment_NPM_Transfer_Time_SIZE   5
#define CSN1_Packet_Downlink_Assignment_TBF_STARTING_TIME 528
#define CSN1_Packet_Downlink_Assignment_TBF_STARTING_TIME_SIZE  16
#define CSN1_RLC_Entity_Struct_DN_DOWNLINK_TFI_ASSIGNMENT 217
#define CSN1_RLC_Entity_Struct_DN_DOWNLINK_TFI_ASSIGNMENT_SIZE   5
#define CSN1_RRClassmark3Value_DTM_EGPRS_Multi_Slot_Class 351
#define CSN1_RRClassmark3Value_DTM_EGPRS_Multi_Slot_Class_SIZE   2
#define CSN1_RRPacketDownlinkAssignmentType2_RLC_Entity_2 878
#define CSN1_RRPacketDownlinkAssignmentType2_RLC_Entity_2_SIZE   0
#define CSN1_RRPacketDownlinkAssignmentType2_RLC_Entity_3 879
#define CSN1_RRPacketDownlinkAssignmentType2_RLC_Entity_3_SIZE   0
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_cell 1107
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_cell_SIZE   0
#define CSN1_SI13RestOctets_GPRS_Power_Control_Parameters 895
#define CSN1_SI13RestOctets_GPRS_Power_Control_Parameters_SIZE  19
#define CSN1_SI2quaterRestOctets__700_REPORTING_THRESHOLD 1069
#define CSN1_SI2quaterRestOctets__700_REPORTING_THRESHOLD_SIZE   3
#define CSN1_SI2quaterRestOctets__810_REPORTING_THRESHOLD 1071
#define CSN1_SI2quaterRestOctets__810_REPORTING_THRESHOLD_SIZE   3
#define CSN1_Segmented_SMS_Description_struct_SMS_Content 132
#define CSN1_Segmented_SMS_Description_struct_SMS_Content_SIZE   0
#define CSN1_VBS_VGCS_RECONFIGURE_BODY_Additional_Segment 117
#define CSN1_VBS_VGCS_RECONFIGURE_BODY_Additional_Segment_SIZE   1
#define CSN1_VGCS_ADDITIONAL_INFORMATION_BODY_filler_bits 124
#define CSN1_VGCS_ADDITIONAL_INFORMATION_BODY_filler_bits_SIZE   3
#define CSN1_BSIC_Description_struct_Number_Remaining_BSIC 701
#define CSN1_BSIC_Description_struct_Number_Remaining_BSIC_SIZE   7
#define CSN1_ChReqDesc2_RLC_Non_persistent_Mode_Capability 158
#define CSN1_ChReqDesc2_RLC_Non_persistent_Mode_Capability_SIZE   1
#define CSN1_Channel_Request_Description_IE_RADIO_PRIORITY 152
#define CSN1_Channel_Request_Description_IE_RADIO_PRIORITY_SIZE   2
#define CSN1_EGPRS_Packet_Uplink_Assignment_Additional_USF 502
#define CSN1_EGPRS_Packet_Uplink_Assignment_Additional_USF_SIZE   0
#define CSN1_EGPRS_Packet_Uplink_Assignment_TFI_ASSIGNMENT 481
#define CSN1_EGPRS_Packet_Uplink_Assignment_TFI_ASSIGNMENT_SIZE   5
#define CSN1_Enhanced_Measurement_report_Serving_cell_data 431
#define CSN1_Enhanced_Measurement_report_Serving_cell_data_SIZE  23
#define CSN1_Extension_Information_BSS_PAGING_COORDINATION 675
#define CSN1_Extension_Information_BSS_PAGING_COORDINATION_SIZE   1
#define CSN1_Extension_Information_MULTIPLE_TBF_CAPABILITY 678
#define CSN1_Extension_Information_MULTIPLE_TBF_CAPABILITY_SIZE   1
#define CSN1_Fixed_Allocation_struct_UPLINK_TFI_ASSIGNMENT 200
#define CSN1_Fixed_Allocation_struct_UPLINK_TFI_ASSIGNMENT_SIZE   5
#define CSN1_GPRS_Power_Control_Parameters_IE_PC_MEAS_CHAN 110
#define CSN1_GPRS_Power_Control_Parameters_IE_PC_MEAS_CHAN_SIZE   1
#define CSN1_Group_Channel_Description_Channel_Description   7
#define CSN1_Group_Channel_Description_Channel_Description_SIZE  24
#define CSN1_IPA_Downlink_Assignment_struct_TFI_ASSIGNMENT 1162
#define CSN1_IPA_Downlink_Assignment_struct_TFI_ASSIGNMENT_SIZE   5
#define CSN1_IPA_Uplink_Assignment_struct_Random_Reference 1151
#define CSN1_IPA_Uplink_Assignment_struct_Random_Reference_SIZE  11
#define CSN1_MBMS_Channel_Parameters_IE_MPRACH_description 1186
#define CSN1_MBMS_Channel_Parameters_IE_MPRACH_description_SIZE   0
#define CSN1_Measurement_information__700_REPORTING_OFFSET 765
#define CSN1_Measurement_information__700_REPORTING_OFFSET_SIZE   3
#define CSN1_Measurement_information__810_REPORTING_OFFSET 767
#define CSN1_Measurement_information__810_REPORTING_OFFSET_SIZE   3
#define CSN1_NOTIFY_APPLICATION_DATA_BODY_application_data 138
#define CSN1_NOTIFY_APPLICATION_DATA_BODY_application_data_SIZE  72
#define CSN1_Non_GSM_Message_struct_NR_OF_CONTAINER_OCTETS 281
#define CSN1_Non_GSM_Message_struct_NR_OF_CONTAINER_OCTETS_SIZE   5
#define CSN1_PBCCH_Description_2_struct_PSI1_REPEAT_PERIOD 1147
#define CSN1_PBCCH_Description_2_struct_PSI1_REPEAT_PERIOD_SIZE   4
#define CSN1_Packet_Timing_Advance_IE_TIMING_ADVANCE_INDEX  86
#define CSN1_Packet_Timing_Advance_IE_TIMING_ADVANCE_INDEX_SIZE   4
#define CSN1_Packet_Timing_Advance_IE_TIMING_ADVANCE_VALUE  85
#define CSN1_Packet_Timing_Advance_IE_TIMING_ADVANCE_VALUE_SIZE   6
#define CSN1_Packet_Uplink_Assignment_TIMING_ADVANCE_INDEX 554
#define CSN1_Packet_Uplink_Assignment_TIMING_ADVANCE_INDEX_SIZE   4
#define CSN1_RRClassmark3Value_DTM_Enhancements_Capability 368
#define CSN1_RRClassmark3Value_DTM_Enhancements_Capability_SIZE   1
#define CSN1_RRClassmark3Value_Extended_EARFCN_value_range 393
#define CSN1_RRClassmark3Value_Extended_EARFCN_value_range_SIZE   1
#define CSN1_RRPktDownlinkAssi_Measurement_Control_E_UTRAN 838
#define CSN1_RRPktDownlinkAssi_Measurement_Control_E_UTRAN_SIZE   1
#define CSN1_Repeated_Invalid_BSIC_Information_struct_BSIC 440
#define CSN1_Repeated_Invalid_BSIC_Information_struct_BSIC_SIZE   6
#define CSN1_SI10bis_Neighbour_Cell_Info_CELL_GLOBAL_COUNT 319
#define CSN1_SI10bis_Neighbour_Cell_Info_CELL_GLOBAL_COUNT_SIZE   2
#define CSN1_SI2quaterRestOctets_NC_Measurement_Parameters 1030
#define CSN1_SI2quaterRestOctets_NC_Measurement_Parameters_SIZE   0
#define CSN1_SI2quater_Indicator_struct_SI2quater_POSITION 588
#define CSN1_SI2quater_Indicator_struct_SI2quater_POSITION_SIZE   1
#define CSN1_System_Information_21_Indicator_SI21_POSITION 590
#define CSN1_System_Information_21_Indicator_SI21_POSITION_SIZE   1
#define CSN1_UTRAN_FDD_Description_struct_CS_Bandwidth_FDD 461
#define CSN1_UTRAN_FDD_Description_struct_CS_Bandwidth_FDD_SIZE   3
#define CSN1_UTRAN_TDD_Description_struct_CS_Bandwidth_TDD 469
#define CSN1_UTRAN_TDD_Description_struct_CS_Bandwidth_TDD_SIZE   3
#define CSN1_CDMA2000_Description_struct_AUX_TD_POWER_LEVEL 747
#define CSN1_CDMA2000_Description_struct_AUX_TD_POWER_LEVEL_SIZE   2
#define CSN1_CDMA2000_Description_struct_cdma2000_frequency 730
#define CSN1_CDMA2000_Description_struct_cdma2000_frequency_SIZE  11
#define CSN1_Channel_Request_Description_IE_RLC_OCTET_COUNT 155
#define CSN1_Channel_Request_Description_IE_RLC_OCTET_COUNT_SIZE  16
#define CSN1_EGPRS_Packet_Uplink_Assignment_Additional_USF2 504
#define CSN1_EGPRS_Packet_Uplink_Assignment_Additional_USF2_SIZE   0
#define CSN1_EGPRS_Packet_Uplink_Assignment_USF_GRANULARITY 489
#define CSN1_EGPRS_Packet_Uplink_Assignment_USF_GRANULARITY_SIZE   1
#define CSN1_Enhanced_Measurement_report_REPORTING_QUANTITY 442
#define CSN1_Enhanced_Measurement_report_REPORTING_QUANTITY_SIZE   6
#define CSN1_Group_Channel_Description_Frequency_Short_List   9
#define CSN1_Group_Channel_Description_Frequency_Short_List_SIZE  64
#define CSN1_IAXRestOctets_Compressed_Inter_RAT_HO_INFO_IND 171
#define CSN1_IAXRestOctets_Compressed_Inter_RAT_HO_INFO_IND_SIZE   1
#define CSN1_MPRACH_Control_Parameters_IE_PERSISTENCE_LEVEL 1195
#define CSN1_MPRACH_Control_Parameters_IE_PERSISTENCE_LEVEL_SIZE   4
#define CSN1_Measurement_information_INVALID_BSIC_REPORTING 694
#define CSN1_Measurement_information_INVALID_BSIC_REPORTING_SIZE   1
#define CSN1_NOTIFICATION_FACCH_BODY_Priority_Uplink_Access 420
#define CSN1_NOTIFICATION_FACCH_BODY_Priority_Uplink_Access_SIZE   1
#define CSN1_RRClassmark3Value_GMSK_Multislot_Power_Profile 362
#define CSN1_RRClassmark3Value_GMSK_Multislot_Power_Profile_SIZE   2
#define CSN1_RRPacketUplinkAssignment_Packet_Timing_Advance 928
#define CSN1_RRPacketUplinkAssignment_Packet_Timing_Advance_SIZE   0
#define CSN1_RRPacketUplinkAssignment_UTRAN_FREQUENCY_INDEX 973
#define CSN1_RRPacketUplinkAssignment_UTRAN_FREQUENCY_INDEX_SIZE   5
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_EARFCN 1108
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_EARFCN_SIZE  16
#define CSN1_SI2_UTRAN_FDD_Description_struct_Bandwidth_FDD 237
#define CSN1_SI2_UTRAN_FDD_Description_struct_Bandwidth_FDD_SIZE   3
#define CSN1_SI2_UTRAN_TDD_Description_struct_Bandwidth_TDD 240
#define CSN1_SI2_UTRAN_TDD_Description_struct_Bandwidth_TDD_SIZE   3
#define CSN1_Single_Block_Allocation_struct_TIMESLOT_NUMBER 983
#define CSN1_Single_Block_Allocation_struct_TIMESLOT_NUMBER_SIZE   3
#define CSN1_UTRAN_FDD_TDD_Description_struct_Bandwidth_FDD 617
#define CSN1_UTRAN_FDD_TDD_Description_struct_Bandwidth_FDD_SIZE   3
#define CSN1_UTRAN_FDD_TDD_Description_struct_Bandwidth_TDD 618
#define CSN1_UTRAN_FDD_TDD_Description_struct_Bandwidth_TDD_SIZE   3
#define CSN1_Uplink_TBF_Assignment_struct_EGPRS_Window_Size 951
#define CSN1_Uplink_TBF_Assignment_struct_EGPRS_Window_Size_SIZE   5
#define CSN1_VBS_VGCS_RECONFIGURE_BODY_short_layer_2_header 112
#define CSN1_VBS_VGCS_RECONFIGURE_BODY_short_layer_2_header_SIZE   2
#define CSN1_VGCS_SMS_INFORMATION_BODY_short_layer_2_header 126
#define CSN1_VGCS_SMS_INFORMATION_BODY_short_layer_2_header_SIZE   2
#define CSN1_Additional_PFCs_struct_UP_UPLINK_TFI_ASSIGNMENT  46
#define CSN1_Additional_PFCs_struct_UP_UPLINK_TFI_ASSIGNMENT_SIZE   5
#define CSN1_Direct_encoding_1_struct_GPRS_Mobile_Allocation 914
#define CSN1_Direct_encoding_1_struct_GPRS_Mobile_Allocation_SIZE   0
#define CSN1_Downlink_TBF_assignment_2_struct_TFI_Assignment 223
#define CSN1_Downlink_TBF_assignment_2_struct_TFI_Assignment_SIZE   5
#define CSN1_Dynamic_Allocation_struct_UPLINK_TFI_ASSIGNMENT  27
#define CSN1_Dynamic_Allocation_struct_UPLINK_TFI_ASSIGNMENT_SIZE   5
#define CSN1_ETWS_Primary_Notification_struct_Segment_Number 1231
#define CSN1_ETWS_Primary_Notification_struct_Segment_Number_SIZE   4
#define CSN1_E_UTRAN_CSG_Description_struct_RR_CSG_PCI_SPLIT 791
#define CSN1_E_UTRAN_CSG_Description_struct_RR_CSG_PCI_SPLIT_SIZE   0
#define CSN1_E_UTRAN_Measurement_Report_struct_CELL_IDENTITY 447
#define CSN1_E_UTRAN_Measurement_Report_struct_CELL_IDENTITY_SIZE   9
#define CSN1_Fixed_Allocation_struct_BLOCKS_OR_BLOCK_PERIODS 209
#define CSN1_Fixed_Allocation_struct_BLOCKS_OR_BLOCK_PERIODS_SIZE   1
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_GAMMA 1171
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_GAMMA_SIZE   5
#define CSN1_MPRACH_description_IE_MPRACH_Control_Parameters 1190
#define CSN1_MPRACH_description_IE_MPRACH_Control_Parameters_SIZE   0
#define CSN1_MeasurementResults_UTRAN_CSG_Measurement_Report 576
#define CSN1_MeasurementResults_UTRAN_CSG_Measurement_Report_SIZE   0
#define CSN1_Measurement_information_E_UTRAN_CSG_Description 790
#define CSN1_Measurement_information_E_UTRAN_CSG_Description_SIZE   0
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_TMGI 517
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_TMGI_SIZE   0
#define CSN1_Packet_Downlink_Assignment_Downlink_EGPRS_Level 539
#define CSN1_Packet_Downlink_Assignment_Downlink_EGPRS_Level_SIZE   2
#define CSN1_Packet_Downlink_Assignment_PDCH_PAIR_INDICATION 538
#define CSN1_Packet_Downlink_Assignment_PDCH_PAIR_INDICATION_SIZE   3
#define CSN1_Packet_Downlink_Assignment_TIMING_ADVANCE_INDEX 527
#define CSN1_Packet_Downlink_Assignment_TIMING_ADVANCE_INDEX_SIZE   4
#define CSN1_Packet_Uplink_Assignment_CHANNEL_CODING_COMMAND 550
#define CSN1_Packet_Uplink_Assignment_CHANNEL_CODING_COMMAND_SIZE   2
#define CSN1_REPORT_PRIORITY_Description_struct_Number_Cells 705
#define CSN1_REPORT_PRIORITY_Description_struct_Number_Cells_SIZE   7
#define CSN1_REPORT_PRIORITY_Description_struct_REP_PRIORITY 706
#define CSN1_REPORT_PRIORITY_Description_struct_REP_PRIORITY_SIZE   0
#define CSN1_RRClassmark3Value_Associated_Radio_Capability_1 330
#define CSN1_RRClassmark3Value_Associated_Radio_Capability_1_SIZE   4
#define CSN1_RRClassmark3Value_Associated_Radio_Capability_2 329
#define CSN1_RRClassmark3Value_Associated_Radio_Capability_2_SIZE   4
#define CSN1_RRClassmark3Value_GERAN_Network_Sharing_support 387
#define CSN1_RRClassmark3Value_GERAN_Network_Sharing_support_SIZE   1
#define CSN1_RRPacketUplinkAssignment_CHANNEL_CODING_COMMAND 926
#define CSN1_RRPacketUplinkAssignment_CHANNEL_CODING_COMMAND_SIZE   2
#define CSN1_RRPacketUplinkAssignment_EMSR_Additional_PFCs_1 977
#define CSN1_RRPacketUplinkAssignment_EMSR_Additional_PFCs_1_SIZE   0
#define CSN1_RRPacketUplinkAssignment_EMSR_Additional_PFCs_2 978
#define CSN1_RRPacketUplinkAssignment_EMSR_Additional_PFCs_2_SIZE   0
#define CSN1_RRPacketUplinkAssignment_EMSR_Additional_PFCs_3 979
#define CSN1_RRPacketUplinkAssignment_EMSR_Additional_PFCs_3_SIZE   0
#define CSN1_RRPktDownlinkAssi_LINK_QUALITY_MEASUREMENT_MODE 823
#define CSN1_RRPktDownlinkAssi_LINK_QUALITY_MEASUREMENT_MODE_SIZE   2
#define CSN1_Segmented_SMS_Description_struct_Segment_Number 129
#define CSN1_Segmented_SMS_Description_struct_Segment_Number_SIZE   4
#define CSN1_UTRAN_FDD_Description_struct_CS_NR_OF_FDD_CELLS 464
#define CSN1_UTRAN_FDD_Description_struct_CS_NR_OF_FDD_CELLS_SIZE   5
#define CSN1_UTRAN_FDD_Description_struct_CS_Scrambling_code 466
#define CSN1_UTRAN_FDD_Description_struct_CS_Scrambling_code_SIZE   9
#define CSN1_UTRAN_TDD_Description_struct_CS_NR_OF_TDD_CELLS 472
#define CSN1_UTRAN_TDD_Description_struct_CS_NR_OF_TDD_CELLS_SIZE   5
#define CSN1_new_Group_Channel_Description_Mobile_Allocation 114
#define CSN1_new_Group_Channel_Description_Mobile_Allocation_SIZE   1
#define CSN1_Downlink_TBF_assignment_struct_EGPRS_Window_Size 833
#define CSN1_Downlink_TBF_assignment_struct_EGPRS_Window_Size_SIZE   5
#define CSN1_ECSD_Multi_Slot_Capability_ECSD_Multi_Slot_Class 338
#define CSN1_ECSD_Multi_Slot_Capability_ECSD_Multi_Slot_Class_SIZE   5
#define CSN1_EGPRS_Packet_Uplink_Assignment_ALLOCATION_BITMAP 484
#define CSN1_EGPRS_Packet_Uplink_Assignment_ALLOCATION_BITMAP_SIZE   0
#define CSN1_EGPRS_Packet_Uplink_Assignment_BTS_PWR_CTRL_MODE 486
#define CSN1_EGPRS_Packet_Uplink_Assignment_BTS_PWR_CTRL_MODE_SIZE   1
#define CSN1_EGPRS_Packet_Uplink_Assignment_EGPRS_Window_Size 495
#define CSN1_EGPRS_Packet_Uplink_Assignment_EGPRS_Window_Size_SIZE   5
#define CSN1_EGPRS_Packet_Uplink_Assignment_TBF_STARTING_TIME 499
#define CSN1_EGPRS_Packet_Uplink_Assignment_TBF_STARTING_TIME_SIZE  16
#define CSN1_E_UTRAN_Description_struct_Measurement_Bandwidth 457
#define CSN1_E_UTRAN_Description_struct_Measurement_Bandwidth_SIZE   3
#define CSN1_Enhanced_Measurement_report_Short_layer_2_header 426
#define CSN1_Enhanced_Measurement_report_Short_layer_2_header_SIZE   2
#define CSN1_Fixed_Allocation_struct_ALLOCATION_BITMAP_LENGTH 210
#define CSN1_Fixed_Allocation_struct_ALLOCATION_BITMAP_LENGTH_SIZE   7
#define CSN1_Fixed_Allocation_struct_Power_Control_Parameters 206
#define CSN1_Fixed_Allocation_struct_Power_Control_Parameters_SIZE   0
#define CSN1_GPRS_BSIC_Description_struct_BA_Index_Start_BSIC 1005
#define CSN1_GPRS_BSIC_Description_struct_BA_Index_Start_BSIC_SIZE   5
#define CSN1_GPRS_BSIC_Description_struct_Frequency_Scrolling 1009
#define CSN1_GPRS_BSIC_Description_struct_Frequency_Scrolling_SIZE   1
#define CSN1_GPRS_Real_Time_Difference_Description_struct_RTD 1003
#define CSN1_GPRS_Real_Time_Difference_Description_struct_RTD_SIZE   0
#define CSN1_Measurement_information__700_REPORTING_THRESHOLD 766
#define CSN1_Measurement_information__700_REPORTING_THRESHOLD_SIZE   3
#define CSN1_Measurement_information__810_REPORTING_THRESHOLD 768
#define CSN1_Measurement_information__810_REPORTING_THRESHOLD_SIZE   3
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_ALPHA 515
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_ALPHA_SIZE   4
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_GAMMA 516
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_GAMMA_SIZE   5
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_MS_ID 513
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_MS_ID_SIZE   0
#define CSN1_Network_Sharing_Information_struct_NCC_Permitted 306
#define CSN1_Network_Sharing_Information_struct_NCC_Permitted_SIZE   8
#define CSN1_Pulse_Format_Coding_2_struct_Pulse_Format_Bitmap 965
#define CSN1_Pulse_Format_Coding_2_struct_Pulse_Format_Bitmap_SIZE   0
#define CSN1_RRClassmark3Value_DTM_GPRS_High_Multi_Slot_Class 369
#define CSN1_RRClassmark3Value_DTM_GPRS_High_Multi_Slot_Class_SIZE   3
#define CSN1_RRClassmark3Value__8_PSK_Multislot_Power_Profile 363
#define CSN1_RRClassmark3Value__8_PSK_Multislot_Power_Profile_SIZE   2
#define CSN1_RRPacketUplinkAssignment_E_UTRAN_FREQUENCY_INDEX 971
#define CSN1_RRPacketUplinkAssignment_E_UTRAN_FREQUENCY_INDEX_SIZE   3
#define CSN1_RRPacketUplinkAssignment_Multiple_TBF_Allocation 929
#define CSN1_RRPacketUplinkAssignment_Multiple_TBF_Allocation_SIZE   0
#define CSN1_RRPacketUplinkAssignment_Single_Block_Allocation 982
#define CSN1_RRPacketUplinkAssignment_Single_Block_Allocation_SIZE   0
#define CSN1_R_Support_R_GSM_band_Associated_Radio_Capability 331
#define CSN1_R_Support_R_GSM_band_Associated_Radio_Capability_SIZE   3
#define CSN1_SI10bis_Neighbour_Cell_Info_Frequency_Short_List 317
#define CSN1_SI10bis_Neighbour_Cell_Info_Frequency_Short_List_SIZE  64
#define CSN1_SI14RestOctets_DYNAMIC_ARFCN_MAPPING_Description 286
#define CSN1_SI14RestOctets_DYNAMIC_ARFCN_MAPPING_Description_SIZE   0
#define CSN1_SI15RestOctets_DYNAMIC_ARFCN_MAPPING_Description 290
#define CSN1_SI15RestOctets_DYNAMIC_ARFCN_MAPPING_Description_SIZE   0
#define CSN1_SI23RestOctets_IRAT_Cell_Reselection_Information 1139
#define CSN1_SI23RestOctets_IRAT_Cell_Reselection_Information_SIZE   0
#define CSN1_SI2quaterRestOctets_Extended_EARFCNs_Description 1131
#define CSN1_SI2quaterRestOctets_Extended_EARFCNs_Description_SIZE   0
#define CSN1_Single_Block_Allocation_struct_TBF_Starting_Time 988
#define CSN1_Single_Block_Allocation_struct_TBF_Starting_Time_SIZE   0
#define CSN1_VGCS_ADDITIONAL_INFORMATION_BODY_talker_identity 125
#define CSN1_VGCS_ADDITIONAL_INFORMATION_BODY_talker_identity_SIZE   0
#define CSN1__3G_CSG_Description_struct_UTRAN_FREQUENCY_INDEX 271
#define CSN1__3G_CSG_Description_struct_UTRAN_FREQUENCY_INDEX_SIZE   5
#define CSN1_Additional_PFCs_struct_DN_DOWNLINK_TFI_ASSIGNMENT  49
#define CSN1_Additional_PFCs_struct_DN_DOWNLINK_TFI_ASSIGNMENT_SIZE   5
#define CSN1_CDMA2000_Description_struct_number_cdma2000_cells 731
#define CSN1_CDMA2000_Description_struct_number_cdma2000_cells_SIZE   5
#define CSN1_CellSelIndAfterReleaseTCHandSDCCH_GSM_Description 474
#define CSN1_CellSelIndAfterReleaseTCHandSDCCH_GSM_Description_SIZE  17
#define CSN1_Downlink_TBF_assignment_2_struct_EVENT_BASED_FANR 226
#define CSN1_Downlink_TBF_assignment_2_struct_EVENT_BASED_FANR_SIZE   1
#define CSN1_Dynamic_Allocation_struct_RLC_DATA_BLOCKS_GRANTED  28
#define CSN1_Dynamic_Allocation_struct_RLC_DATA_BLOCKS_GRANTED_SIZE   8
#define CSN1_EGPRS_Packet_Uplink_Assignment_REPORTED_TIMESLOTS 505
#define CSN1_EGPRS_Packet_Uplink_Assignment_REPORTED_TIMESLOTS_SIZE   8
#define CSN1_Extension_Information_DTM_ENHANCEMENTS_CAPABILITY 680
#define CSN1_Extension_Information_DTM_ENHANCEMENTS_CAPABILITY_SIZE   1
#define CSN1_Fixed_Allocation_struct_DOWNLINK_CONTROL_TIMESLOT 202
#define CSN1_Fixed_Allocation_struct_DOWNLINK_CONTROL_TIMESLOT_SIZE   3
#define CSN1_IPA_Uplink_Assignment_struct_Frequency_Parameters 1160
#define CSN1_IPA_Uplink_Assignment_struct_Frequency_Parameters_SIZE   0
#define CSN1_IPA_Uplink_Assignment_struct_TIMING_ADVANCE_VALUE 1154
#define CSN1_IPA_Uplink_Assignment_struct_TIMING_ADVANCE_VALUE_SIZE   6
#define CSN1_MBMS_Session_Parameters_List_IE_EGPRS_Window_Size 1184
#define CSN1_MBMS_Session_Parameters_List_IE_EGPRS_Window_Size_SIZE   5
#define CSN1_MBMS_Session_Parameters_List_IE_NPM_Transfer_Time 1185
#define CSN1_MBMS_Session_Parameters_List_IE_NPM_Transfer_Time_SIZE   5
#define CSN1_NOTIFY_APPLICATION_DATA_BODY_short_layer_2_header 137
#define CSN1_NOTIFY_APPLICATION_DATA_BODY_short_layer_2_header_SIZE   2
#define CSN1_Network_Sharing_Information_struct_Additional_ACC 307
#define CSN1_Network_Sharing_Information_struct_Additional_ACC_SIZE  16
#define CSN1_Network_Sharing_Information_struct_SI23_Indicator 300
#define CSN1_Network_Sharing_Information_struct_SI23_Indicator_SIZE   1
#define CSN1_Packet_Uplink_Assignment_ALLOCATION_BITMAP_LENGTH 543
#define CSN1_Packet_Uplink_Assignment_ALLOCATION_BITMAP_LENGTH_SIZE   5
#define CSN1_RRClassmark3Value_DTM_EGPRS_High_Multi_Slot_Class 371
#define CSN1_RRClassmark3Value_DTM_EGPRS_High_Multi_Slot_Class_SIZE   3
#define CSN1_RRClassmark3Value_Extended_Measurement_Capability 334
#define CSN1_RRClassmark3Value_Extended_Measurement_Capability_SIZE   1
#define CSN1_RRPacketDownlinkAssignmentType2_EGPRS_Window_Size 855
#define CSN1_RRPacketDownlinkAssignmentType2_EGPRS_Window_Size_SIZE   5
#define CSN1_RRPktDownlinkAssi_Packet_Extended_Ttiming_Advance 824
#define CSN1_RRPktDownlinkAssi_Packet_Extended_Ttiming_Advance_SIZE   2
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_RR_EARFCN 782
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_RR_EARFCN_SIZE  16
#define CSN1_SYSTEM_INFORMATION_TYPE_10ter_SI10ter_Rest_Octets   5
#define CSN1_SYSTEM_INFORMATION_TYPE_10ter_SI10ter_Rest_Octets_SIZE  32
#define CSN1__3G_Neighbour_Cell_Description_struct_RR__3G_Wait 723
#define CSN1__3G_Neighbour_Cell_Description_struct_RR__3G_Wait_SIZE   3
#define CSN1_new_Group_Channel_Description_Channel_Description 113
#define CSN1_new_Group_Channel_Description_Channel_Description_SIZE  24
#define CSN1_Downlink_TBF_assignment_2_struct_NPM_Transfer_Time 225
#define CSN1_Downlink_TBF_assignment_2_struct_NPM_Transfer_Time_SIZE   5
#define CSN1_ETWS_Primary_Notification_struct_Length_Of_Segment 1233
#define CSN1_ETWS_Primary_Notification_struct_Length_Of_Segment_SIZE   7
#define CSN1_E_UTRAN_Parameters_Description_struct_E_UTRAN_Stop 1094
#define CSN1_E_UTRAN_Parameters_Description_struct_E_UTRAN_Stop_SIZE   1
#define CSN1_GPRS_BSIC_Description_struct_Number_Remaining_BSIC 1007
#define CSN1_GPRS_BSIC_Description_struct_Number_Remaining_BSIC_SIZE   7
#define CSN1_HSCSD_Multi_Slot_Capability_HSCSD_Multi_Slot_Class 332
#define CSN1_HSCSD_Multi_Slot_Capability_HSCSD_Multi_Slot_Class_SIZE   5
#define CSN1_NC_Measurement_Parameters_struct_NC_NON_DRX_PERIOD 1032
#define CSN1_NC_Measurement_Parameters_struct_NC_NON_DRX_PERIOD_SIZE   3
#define CSN1_NOTIFICATION_FACCH_BODY_SMS_Guaranteed_Privacy_Ind 425
#define CSN1_NOTIFICATION_FACCH_BODY_SMS_Guaranteed_Privacy_Ind_SIZE   1
#define CSN1_Packet_Uplink_Assignment_TLLI_BLOCK_CHANNEL_CODING 551
#define CSN1_Packet_Uplink_Assignment_TLLI_BLOCK_CHANNEL_CODING_SIZE   1
#define CSN1_RRPacketUplinkAssignment_Measurement_Control_UTRAN 972
#define CSN1_RRPacketUplinkAssignment_Measurement_Control_UTRAN_SIZE   1
#define CSN1_RRPacketUplinkAssignment_TLLI_BLOCK_CHANNEL_CODING 927
#define CSN1_RRPacketUplinkAssignment_TLLI_BLOCK_CHANNEL_CODING_SIZE   1
#define CSN1_RRPktDownlinkAssi_Multiple_Downlink_TBF_Assignment 825
#define CSN1_RRPktDownlinkAssi_Multiple_Downlink_TBF_Assignment_SIZE   0
#define CSN1_Real_Time_Difference_Description_struct_RTD_Struct 697
#define CSN1_Real_Time_Difference_Description_struct_RTD_Struct_SIZE   0
#define CSN1_SI10bis_Neighbour_Cell_Info_Priority_Uplink_access 321
#define CSN1_SI10bis_Neighbour_Cell_Info_Priority_Uplink_access_SIZE   1
#define CSN1_SI2q_Extension_Information_CCN_Support_Description 1036
#define CSN1_SI2q_Extension_Information_CCN_Support_Description_SIZE   0
#define CSN1_SI2quaterRestOctets_p3G_Neighbour_Cell_Description 1039
#define CSN1_SI2quaterRestOctets_p3G_Neighbour_Cell_Description_SIZE   0
#define CSN1_SYSTEM_INFORMATION_TYPE_10ter_short_layer_2_header   3
#define CSN1_SYSTEM_INFORMATION_TYPE_10ter_short_layer_2_header_SIZE   2
#define CSN1_Segmented_SMS_Description_struct_SMS_Final_Content 131
#define CSN1_Segmented_SMS_Description_struct_SMS_Final_Content_SIZE   0
#define CSN1_UTRAN_CSG_Measurement_Report_IE_REPORTING_QUANTITY 412
#define CSN1_UTRAN_CSG_Measurement_Report_IE_REPORTING_QUANTITY_SIZE   6
#define CSN1_Uplink_TBF_Assignment_struct_UPLINK_TFI_ASSIGNMENT 947
#define CSN1_Uplink_TBF_Assignment_struct_UPLINK_TFI_ASSIGNMENT_SIZE   5
#define CSN1_new_Group_Channel_Description_Frequency_Short_List 115
#define CSN1_new_Group_Channel_Description_Frequency_Short_List_SIZE  64
#define CSN1_CDMA2000_Description_struct_cdma2000_frequency_band 729
#define CSN1_CDMA2000_Description_struct_cdma2000_frequency_band_SIZE   5
#define CSN1_Direct_encoding_2_struct_MA_Frequency_List_contents 924
#define CSN1_Direct_encoding_2_struct_MA_Frequency_List_contents_SIZE   0
#define CSN1_EGPRS_Packet_Uplink_Assignment_PDCH_PAIR_INDICATION 501
#define CSN1_EGPRS_Packet_Uplink_Assignment_PDCH_PAIR_INDICATION_SIZE   3
#define CSN1_EGPRS_Packet_Uplink_Assignment_TIMING_ADVANCE_INDEX 498
#define CSN1_EGPRS_Packet_Uplink_Assignment_TIMING_ADVANCE_INDEX_SIZE   4
#define CSN1_E_UTRAN_Parameters_Description_struct_E_UTRAN_Start 1093
#define CSN1_E_UTRAN_Parameters_Description_struct_E_UTRAN_Start_SIZE   1
#define CSN1_Extended_EARFCNs_Description_struct_EARFCN_extended 1132
#define CSN1_Extended_EARFCNs_Description_struct_EARFCN_extended_SIZE  18
#define CSN1_Extension_Information_EGPRS_PACKET__CHANNEL_REQUEST 671
#define CSN1_Extension_Information_EGPRS_PACKET__CHANNEL_REQUEST_SIZE   1
#define CSN1_IPA_Downlink_Assignment_struct_Frequency_Parameters 1168
#define CSN1_IPA_Downlink_Assignment_struct_Frequency_Parameters_SIZE   0
#define CSN1_IPA_Downlink_Assignment_struct_TIMING_ADVANCE_VALUE 1164
#define CSN1_IPA_Downlink_Assignment_struct_TIMING_ADVANCE_VALUE_SIZE   6
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_FN_OFFSET 1170
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_FN_OFFSET_SIZE   8
#define CSN1_IRAT_Cell_Reselection_Information_struct_PLMN_index 1143
#define CSN1_IRAT_Cell_Reselection_Information_struct_PLMN_index_SIZE   2
#define CSN1_Measurement_information_REPORT_PRIORITY_Description 704
#define CSN1_Measurement_information_REPORT_PRIORITY_Description_SIZE   0
#define CSN1_Multiple_TBF_Allocation_struct_Timeslot_description 933
#define CSN1_Multiple_TBF_Allocation_struct_Timeslot_description_SIZE   0
#define CSN1_RRClassmark3Value_CS_to_PS_SRVCC_from_GERAN_to_UTRA 385
#define CSN1_RRClassmark3Value_CS_to_PS_SRVCC_from_GERAN_to_UTRA_SIZE   2
#define CSN1_RRClassmark3Value_Ciphering_Mode_Setting_Capability 375
#define CSN1_RRClassmark3Value_Ciphering_Mode_Setting_Capability_SIZE   1
#define CSN1_Repeated_UTRAN_FDD_Neighbour_Cells_struct_FDD_ARFCN 251
#define CSN1_Repeated_UTRAN_FDD_Neighbour_Cells_struct_FDD_ARFCN_SIZE  14
#define CSN1_Repeated_UTRAN_TDD_Neighbour_Cells_struct_TDD_ARFCN 257
#define CSN1_Repeated_UTRAN_TDD_Neighbour_Cells_struct_TDD_ARFCN_SIZE  14
#define CSN1_SI2quaterRestOctets_CSG_Cells_Reporting_Description 1123
#define CSN1_SI2quaterRestOctets_CSG_Cells_Reporting_Description_SIZE   0
#define CSN1_Uplink_TBF_Assignment_struct_CHANNEL_CODING_COMMAND 948
#define CSN1_Uplink_TBF_Assignment_struct_CHANNEL_CODING_COMMAND_SIZE   2
#define CSN1_VGCS_SMS_INFORMATION_BODY_Segmented_SMS_Description 127
#define CSN1_VGCS_SMS_INFORMATION_BODY_Segmented_SMS_Description_SIZE   0
#define CSN1_Channel_Request_Description_IE_PEAK_THROUGHPUT_CLASS 151
#define CSN1_Channel_Request_Description_IE_PEAK_THROUGHPUT_CLASS_SIZE   4
#define CSN1_E_UTRAN_Measurement_Report_struct_REPORTING_QUANTITY 448
#define CSN1_E_UTRAN_Measurement_Report_struct_REPORTING_QUANTITY_SIZE   6
#define CSN1_GPRS_REPORT_PRIORITY_Description_struct_Number_Cells 1011
#define CSN1_GPRS_REPORT_PRIORITY_Description_struct_Number_Cells_SIZE   7
#define CSN1_GPRS_REPORT_PRIORITY_Description_struct_REP_PRIORITY 1012
#define CSN1_GPRS_REPORT_PRIORITY_Description_struct_REP_PRIORITY_SIZE   0
#define CSN1_MBMS_Session_Parameters_List_IE_MBMS_Bearer_Identity 1181
#define CSN1_MBMS_Session_Parameters_List_IE_MBMS_Bearer_Identity_SIZE   0
#define CSN1_Multiple_TBF_Allocation_struct_Uplink_TBF_Assignment 944
#define CSN1_Multiple_TBF_Allocation_struct_Uplink_TBF_Assignment_SIZE   0
#define CSN1_NOTIFICATION_FACCH_BODY_SMS_Data_Confidentiality_Ind 424
#define CSN1_NOTIFICATION_FACCH_BODY_SMS_Data_Confidentiality_Ind_SIZE   1
#define CSN1_RRClassmark3Value_Extended_DTM_GPRS_Multi_Slot_Class 356
#define CSN1_RRClassmark3Value_Extended_DTM_GPRS_Multi_Slot_Class_SIZE   2
#define CSN1_RRClassmark3Value_Priority_based_reselection_support 380
#define CSN1_RRClassmark3Value_Priority_based_reselection_support_SIZE   1
#define CSN1_RRPacketDownlinkAssignmentType2_Downlink_EGPRS_Level 873
#define CSN1_RRPacketDownlinkAssignmentType2_Downlink_EGPRS_Level_SIZE   2
#define CSN1_RRPacketDownlinkAssignmentType2_UPLINK_PDCH_PAIRS_C1 859
#define CSN1_RRPacketDownlinkAssignmentType2_UPLINK_PDCH_PAIRS_C1_SIZE   8
#define CSN1_RRPacketDownlinkAssignmentType2_UPLINK_PDCH_PAIRS_C2 860
#define CSN1_RRPacketDownlinkAssignmentType2_UPLINK_PDCH_PAIRS_C2_SIZE   8
#define CSN1_RRPacketUplinkAssignment_Measurement_Control_E_UTRAN 970
#define CSN1_RRPacketUplinkAssignment_Measurement_Control_E_UTRAN_SIZE   1
#define CSN1_Repeated_Invalid_BSIC_Information_struct_RXLEV_NCELL 441
#define CSN1_Repeated_Invalid_BSIC_Information_struct_RXLEV_NCELL_SIZE   6
#define CSN1_Repeated_UTRAN_FDD_Neighbour_Cells_struct_FDD_Indic0 252
#define CSN1_Repeated_UTRAN_FDD_Neighbour_Cells_struct_FDD_Indic0_SIZE   1
#define CSN1_Repeated_UTRAN_TDD_Neighbour_Cells_struct_TDD_Indic0 259
#define CSN1_Repeated_UTRAN_TDD_Neighbour_Cells_struct_TDD_Indic0_SIZE   1
#define CSN1_SI2quaterRestOctets_GPRS_REPORT_PRIORITY_Description 1010
#define CSN1_SI2quaterRestOctets_GPRS_REPORT_PRIORITY_Description_SIZE   0
#define CSN1_SYSTEM_INFORMATION_TYPE_10_BODY_short_layer_2_header 1196
#define CSN1_SYSTEM_INFORMATION_TYPE_10_BODY_short_layer_2_header_SIZE   2
#define CSN1_VGCSCipheringParameters_Location_Area_Identification  77
#define CSN1_VGCSCipheringParameters_Location_Area_Identification_SIZE  32
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_Ignore 1401
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_Ignore_SIZE   0
#define CSN1__3G_Neighbour_Cell_Description_struct_Index_Start_3G 1040
#define CSN1__3G_Neighbour_Cell_Description_struct_Index_Start_3G_SIZE   7
#define CSN1_CellSelIndAfterReleaseTCHandSDCCH_E_UTRAN_Description 455
#define CSN1_CellSelIndAfterReleaseTCHandSDCCH_E_UTRAN_Description_SIZE   0
#define CSN1_DynamicARFCNMapping_DYNAMIC_ARFCN_MAPPING_Description 170
#define CSN1_DynamicARFCNMapping_DYNAMIC_ARFCN_MAPPING_Description_SIZE   0
#define CSN1_Dynamic_Allocation_struct_Extended_Dynamic_Allocation  23
#define CSN1_Dynamic_Allocation_struct_Extended_Dynamic_Allocation_SIZE   1
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_E_UTRAN_Stop 779
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_E_UTRAN_Stop_SIZE   1
#define CSN1_MEASUREMENT_PARAMETERS_Description_Struct_REPORT_TYPE 999
#define CSN1_MEASUREMENT_PARAMETERS_Description_Struct_REPORT_TYPE_SIZE   1
#define CSN1_Network_Sharing_Information_struct_Common_PLMN_PS_ACC 302
#define CSN1_Network_Sharing_Information_struct_Common_PLMN_PS_ACC_SIZE  16
#define CSN1_Non_GSM_Message_struct_Non_GSM_Protocol_Discriminator 280
#define CSN1_Non_GSM_Message_struct_Non_GSM_Protocol_Discriminator_SIZE   3
#define CSN1_RRClassmark3Value_Additional_Positioning_Capabilities 376
#define CSN1_RRClassmark3Value_Additional_Positioning_Capabilities_SIZE   1
#define CSN1_RRClassmark3Value_CS_to_PS_SRVCC_from_GERAN_to_E_UTRA 386
#define CSN1_RRClassmark3Value_CS_to_PS_SRVCC_from_GERAN_to_E_UTRA_SIZE   2
#define CSN1_RRClassmark3Value_Extended_DTM_EGPRS_Multi_Slot_Class 357
#define CSN1_RRClassmark3Value_Extended_DTM_EGPRS_Multi_Slot_Class_SIZE   2
#define CSN1_RRClassmark3Value_Extended_TSC_Set_Capability_support 392
#define CSN1_RRClassmark3Value_Extended_TSC_Set_Capability_support_SIZE   1
#define CSN1_RRClassmark3Value_GSM_400_Associated_Radio_Capability 343
#define CSN1_RRClassmark3Value_GSM_400_Associated_Radio_Capability_SIZE   4
#define CSN1_RRClassmark3Value_GSM_710_Associated_Radio_Capability 373
#define CSN1_RRClassmark3Value_GSM_710_Associated_Radio_Capability_SIZE   4
#define CSN1_RRClassmark3Value_GSM_750_Associated_Radio_Capability 353
#define CSN1_RRClassmark3Value_GSM_750_Associated_Radio_Capability_SIZE   4
#define CSN1_RRClassmark3Value_GSM_850_Associated_Radio_Capability 344
#define CSN1_RRClassmark3Value_GSM_850_Associated_Radio_Capability_SIZE   4
#define CSN1_RRPacketDownlinkAssignmentType2_UTRAN_FREQUENCY_INDEX 877
#define CSN1_RRPacketDownlinkAssignmentType2_UTRAN_FREQUENCY_INDEX_SIZE   5
#define CSN1_SI6RestOctet_DEDICATED_MODE_MBMS_NOTIFICATION_SUPPORT 609
#define CSN1_SI6RestOctet_DEDICATED_MODE_MBMS_NOTIFICATION_SUPPORT_SIZE   1
#define CSN1_Segmented_SMS_Description_struct_SMS_Reference_Number 128
#define CSN1_Segmented_SMS_Description_struct_SMS_Reference_Number_SIZE   4
#define CSN1_VGCS_ADDITIONAL_INFORMATION_BODY_short_layer_2_header 122
#define CSN1_VGCS_ADDITIONAL_INFORMATION_BODY_short_layer_2_header_SIZE   2
#define CSN1_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY_SI10bis_Sequence 452
#define CSN1_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY_SI10bis_Sequence_SIZE   2
#define CSN1__3G_Priority_Parameters_Description_struct_UTRAN_Stop 1081
#define CSN1__3G_Priority_Parameters_Description_struct_UTRAN_Stop_SIZE   1
#define CSN1_Downlink_TBF_assignment_struct_DOWNLINK_TFI_ASSIGNMENT 831
#define CSN1_Downlink_TBF_assignment_struct_DOWNLINK_TFI_ASSIGNMENT_SIZE   5
#define CSN1_E_UTRAN_CSG_Description_struct_E_UTRAN_FREQUENCY_INDEX 1120
#define CSN1_E_UTRAN_CSG_Description_struct_E_UTRAN_FREQUENCY_INDEX_SIZE   3
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_E_UTRAN_Start 778
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_E_UTRAN_Start_SIZE   1
#define CSN1_Enhanced_Measurement_report_E_UTRAN_Measurement_Report 444
#define CSN1_Enhanced_Measurement_report_E_UTRAN_Measurement_Report_SIZE   0
#define CSN1_MBMS_p_t_m_channel_description_IE_Frequency_Parameters 1177
#define CSN1_MBMS_p_t_m_channel_description_IE_Frequency_Parameters_SIZE   0
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR_SCALE_ORD 710
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR_SCALE_ORD_SIZE   2
#define CSN1_MS_Positioning_Method_Capability_MS_Positioning_Method 337
#define CSN1_MS_Positioning_Method_Capability_MS_Positioning_Method_SIZE   5
#define CSN1_Measurement_information_E_UTRAN_Parameters_Description 777
#define CSN1_Measurement_information_E_UTRAN_Parameters_Description_SIZE   0
#define CSN1_Measurement_information__3G_Neighbour_Cell_Description 722
#define CSN1_Measurement_information__3G_Neighbour_Cell_Description_SIZE   0
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_TLLI_G_RNTI 511
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_TLLI_G_RNTI_SIZE  32
#define CSN1_NC_Measurement_Parameters_struct_NC_REPORTING_PERIOD_I 1033
#define CSN1_NC_Measurement_Parameters_struct_NC_REPORTING_PERIOD_I_SIZE   3
#define CSN1_NC_Measurement_Parameters_struct_NC_REPORTING_PERIOD_T 1034
#define CSN1_NC_Measurement_Parameters_struct_NC_REPORTING_PERIOD_T_SIZE   3
#define CSN1_NC_Measurement_Parameters_struct_NETWORK_CONTROL_ORDER 1031
#define CSN1_NC_Measurement_Parameters_struct_NETWORK_CONTROL_ORDER_SIZE   2
#define CSN1_Network_Sharing_Information_struct_Common_PLMN_Allowed 301
#define CSN1_Network_Sharing_Information_struct_Common_PLMN_Allowed_SIZE   1
#define CSN1_Network_Sharing_Information_struct_Nb_Additional_PLMNs 303
#define CSN1_Network_Sharing_Information_struct_Nb_Additional_PLMNs_SIZE   2
#define CSN1_Non_Segmented_SMS_Description_struct_SMS_Final_Content 136
#define CSN1_Non_Segmented_SMS_Description_struct_SMS_Final_Content_SIZE   0
#define CSN1_PBCCH_Description_2_struct_PBCCH_Frequency_Description 1150
#define CSN1_PBCCH_Description_2_struct_PBCCH_Frequency_Description_SIZE   0
#define CSN1_RRClassmark3Value_GSM_1900_Associated_Radio_Capability 345
#define CSN1_RRClassmark3Value_GSM_1900_Associated_Radio_Capability_SIZE   4
#define CSN1_RRPacketDownlinkAssignmentType2_DOWNLINK_PDCH_PAIRS_C1 857
#define CSN1_RRPacketDownlinkAssignmentType2_DOWNLINK_PDCH_PAIRS_C1_SIZE   8
#define CSN1_RRPacketDownlinkAssignmentType2_DOWNLINK_PDCH_PAIRS_C2 858
#define CSN1_RRPacketDownlinkAssignmentType2_DOWNLINK_PDCH_PAIRS_C2_SIZE   8
#define CSN1_RRPacketDownlinkAssignmentType2_EMSR_Additional_PFCs_1 880
#define CSN1_RRPacketDownlinkAssignmentType2_EMSR_Additional_PFCs_1_SIZE   0
#define CSN1_RRPacketDownlinkAssignmentType2_EMSR_Additional_PFCs_2 881
#define CSN1_RRPacketDownlinkAssignmentType2_EMSR_Additional_PFCs_2_SIZE   0
#define CSN1_RRPacketDownlinkAssignmentType2_EMSR_Additional_PFCs_3 882
#define CSN1_RRPacketDownlinkAssignmentType2_EMSR_Additional_PFCs_3_SIZE   0
#define CSN1_SI10bis_Neighbour_Cell_Info_SMS_Guaranteed_Privacy_Ind 325
#define CSN1_SI10bis_Neighbour_Cell_Info_SMS_Guaranteed_Privacy_Ind_SIZE   1
#define CSN1_SI2quaterRestOctets_Measurement_Parameters_Description 998
#define CSN1_SI2quaterRestOctets_Measurement_Parameters_Description_SIZE   3
#define CSN1_SYSTEM_INFORMATION_TYPE_10ter_Cell_Channel_Description   4
#define CSN1_SYSTEM_INFORMATION_TYPE_10ter_Cell_Channel_Description_SIZE 128
#define CSN1__3G_Priority_Parameters_Description_struct_UTRAN_Start 1080
#define CSN1__3G_Priority_Parameters_Description_struct_UTRAN_Start_SIZE   1
#define CSN1_CellSelIndAfterReleaseTCHandSDCCH_UTRAN_FDD_Description 460
#define CSN1_CellSelIndAfterReleaseTCHandSDCCH_UTRAN_FDD_Description_SIZE   0
#define CSN1_CellSelIndAfterReleaseTCHandSDCCH_UTRAN_TDD_Description 468
#define CSN1_CellSelIndAfterReleaseTCHandSDCCH_UTRAN_TDD_Description_SIZE   0
#define CSN1_EGPRS_Packet_Uplink_Assignment_ALLOCATION_BITMAP_LENGTH 483
#define CSN1_EGPRS_Packet_Uplink_Assignment_ALLOCATION_BITMAP_LENGTH_SIZE   5
#define CSN1_MBMS_Channel_Parameters_IE_MBMS_Session_Parameters_List 1179
#define CSN1_MBMS_Channel_Parameters_IE_MBMS_Session_Parameters_List_SIZE   0
#define CSN1_Packet_Timing_Advance_IE_TIMING_ADVANCE_TIMESLOT_NUMBER  87
#define CSN1_Packet_Timing_Advance_IE_TIMING_ADVANCE_TIMESLOT_NUMBER_SIZE   3
#define CSN1_Pulse_Format_Coding_2_struct_Pulse_Format_Bitmap_Length 964
#define CSN1_Pulse_Format_Coding_2_struct_Pulse_Format_Bitmap_Length_SIZE   7
#define CSN1_RRClassmark3Value_Selective_Ciphering_of_Downlink_SACCH 384
#define CSN1_RRClassmark3Value_Selective_Ciphering_of_Downlink_SACCH_SIZE   1
#define CSN1_RRClassmark3Value_T_GSM_400_Associated_Radio_Capability 365
#define CSN1_RRClassmark3Value_T_GSM_400_Associated_Radio_Capability_SIZE   4
#define CSN1_RRClassmark3Value_T_GSM_810_Associated_Radio_Capability 374
#define CSN1_RRClassmark3Value_T_GSM_810_Associated_Radio_Capability_SIZE   4
#define CSN1_RRClassmark3Value_T_GSM_900_Associated_Radio_Capability 366
#define CSN1_RRClassmark3Value_T_GSM_900_Associated_Radio_Capability_SIZE   4
#define CSN1_RRPacketDownlinkAssignmentType2_DOWNLINK_TFI_ASSIGNMENT 854
#define CSN1_RRPacketDownlinkAssignmentType2_DOWNLINK_TFI_ASSIGNMENT_SIZE   5
#define CSN1_RRPacketDownlinkAssignmentType2_E_UTRAN_FREQUENCY_INDEX 875
#define CSN1_RRPacketDownlinkAssignmentType2_E_UTRAN_FREQUENCY_INDEX_SIZE   3
#define CSN1_RRPacketUplinkAssignment_Packet_Extended_Timing_Advance 958
#define CSN1_RRPacketUplinkAssignment_Packet_Extended_Timing_Advance_SIZE   2
#define CSN1_SI2terRestOctets__3G_MEASUREMENT_Parameters_Description 241
#define CSN1_SI2terRestOctets__3G_MEASUREMENT_Parameters_Description_SIZE   0
#define CSN1_SYSTEM_INFORMATION_TYPE_10bis_BODY_short_layer_2_header 684
#define CSN1_SYSTEM_INFORMATION_TYPE_10bis_BODY_short_layer_2_header_SIZE   2
#define CSN1_VGCS_ADDITIONAL_INFORMATION_BODY_talker_identity_length 123
#define CSN1_VGCS_ADDITIONAL_INFORMATION_BODY_talker_identity_length_SIZE   5
#define CSN1_VGCS_SMS_INFORMATION_BODY_Non_Segmented_SMS_Description 133
#define CSN1_VGCS_SMS_INFORMATION_BODY_Non_Segmented_SMS_Description_SIZE   0
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_Qsearch_C 753
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_Qsearch_C_SIZE   4
#define CSN1__3G_Neighbour_Cell_Description_struct_RR_Index_Start_3G 724
#define CSN1__3G_Neighbour_Cell_Description_struct_RR_Index_Start_3G_SIZE   7
#define CSN1_EGPRS_Packet_Uplink_Assignment_TLLI_BLOCK_CHANNEL_CODING 492
#define CSN1_EGPRS_Packet_Uplink_Assignment_TLLI_BLOCK_CHANNEL_CODING_SIZE   1
#define CSN1_E_UTRAN_Parameters_Description_struct_E_UTRAN_CCN_ACTIVE 1092
#define CSN1_E_UTRAN_Parameters_Description_struct_E_UTRAN_CCN_ACTIVE_SIZE   1
#define CSN1_Enhanced_Measurement_report_UTRAN_CSG_Measurement_Report 449
#define CSN1_Enhanced_Measurement_report_UTRAN_CSG_Measurement_Report_SIZE   0
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_SCALE_ORD 1019
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_SCALE_ORD_SIZE   2
#define CSN1_MBMS_p_t_m_channel_description_IE_DL_TIMESLOT_ALLOCATION 1178
#define CSN1_MBMS_p_t_m_channel_description_IE_DL_TIMESLOT_ALLOCATION_SIZE   8
#define CSN1_Measurement_information_Real_Time_Difference_Description 695
#define CSN1_Measurement_information_Real_Time_Difference_Description_SIZE   0
#define CSN1_Packet_Downlink_Assignment_LINK_QUALITY_MEASUREMENT_MODE 533
#define CSN1_Packet_Downlink_Assignment_LINK_QUALITY_MEASUREMENT_MODE_SIZE   2
#define CSN1_RRClassmark3Value_Downlink_Advanced_Receiver_Performance 367
#define CSN1_RRClassmark3Value_Downlink_Advanced_Receiver_Performance_SIZE   2
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_E_UTRAN_PRIORITY 1110
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_E_UTRAN_PRIORITY_SIZE   3
#define CSN1_Repeated_Invalid_BSIC_Information_struct_BCCH_FREQ_NCELL 439
#define CSN1_Repeated_Invalid_BSIC_Information_struct_BCCH_FREQ_NCELL_SIZE   5
#define CSN1_Repeated_UTRAN_Priority_Parameters_struct_UTRAN_PRIORITY 1087
#define CSN1_Repeated_UTRAN_Priority_Parameters_struct_UTRAN_PRIORITY_SIZE   3
#define CSN1_SI10bis_Neighbour_Cell_Info_SMS_Data_Confidentiality_Ind 324
#define CSN1_SI10bis_Neighbour_Cell_Info_SMS_Data_Confidentiality_Ind_SIZE   1
#define CSN1_Access_Technologies_Request_struct_Access_Technology_Type  14
#define CSN1_Access_Technologies_Request_struct_Access_Technology_Type_SIZE   4
#define CSN1_E_UTRAN_CSG_Description_struct_RR_E_UTRAN_FREQUENCY_INDEX 792
#define CSN1_E_UTRAN_CSG_Description_struct_RR_E_UTRAN_FREQUENCY_INDEX_SIZE   3
#define CSN1_E_UTRAN_Measurement_Report_struct_E_UTRAN_FREQUENCY_INDEX 446
#define CSN1_E_UTRAN_Measurement_Report_struct_E_UTRAN_FREQUENCY_INDEX_SIZE   3
#define CSN1_IPA_Uplink_Assignment_struct_EGPRS_CHANNEL_CODING_COMMAND 1157
#define CSN1_IPA_Uplink_Assignment_struct_EGPRS_CHANNEL_CODING_COMMAND_SIZE   4
#define CSN1_MBMS_Channel_Parameters_IE_MBMS_p_t_m_channel_description 1176
#define CSN1_MBMS_Channel_Parameters_IE_MBMS_p_t_m_channel_description_SIZE   0
#define CSN1_Non_Segmented_SMS_Description_struct_SMS_Reference_Number 135
#define CSN1_Non_Segmented_SMS_Description_struct_SMS_Reference_Number_SIZE   4
#define CSN1_RRPacketDownlinkAssignmentType2_Measurement_Control_UTRAN 876
#define CSN1_RRPacketDownlinkAssignmentType2_Measurement_Control_UTRAN_SIZE   1
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_E_UTRAN_QRXLEVMIN 1113
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_E_UTRAN_QRXLEVMIN_SIZE   5
#define CSN1_Repeated_UTRAN_FDD_Neighbour_Cells_struct_NR_OF_FDD_CELLS 253
#define CSN1_Repeated_UTRAN_FDD_Neighbour_Cells_struct_NR_OF_FDD_CELLS_SIZE   5
#define CSN1_Repeated_UTRAN_Priority_Parameters_struct_UTRAN_QRXLEVMIN 1090
#define CSN1_Repeated_UTRAN_Priority_Parameters_struct_UTRAN_QRXLEVMIN_SIZE   5
#define CSN1_Repeated_UTRAN_TDD_Neighbour_Cells_struct_NR_OF_TDD_CELLS 260
#define CSN1_Repeated_UTRAN_TDD_Neighbour_Cells_struct_NR_OF_TDD_CELLS_SIZE   5
#define CSN1_Repeated_UTRAN_TDD_Neighbour_Cells_struct_TDD_ARFCN_INDEX 258
#define CSN1_Repeated_UTRAN_TDD_Neighbour_Cells_struct_TDD_ARFCN_INDEX_SIZE   3
#define CSN1_SI2_3G_MEASUREMENT_Parameters_Description_struct_FDD_Qmin 244
#define CSN1_SI2_3G_MEASUREMENT_Parameters_Description_struct_FDD_Qmin_SIZE   3
#define CSN1_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description 1001
#define CSN1_SI2quaterRestOctets_GPRS_Real_Time_Difference_Description_SIZE   0
#define CSN1_System_Information_2ter_Indicator_System_Information_2ter 581
#define CSN1_System_Information_2ter_Indicator_System_Information_2ter_SIZE   0
#define CSN1_Uplink_TBF_Assignment_struct_EGPRS_Channel_Coding_Command 949
#define CSN1_Uplink_TBF_Assignment_struct_EGPRS_Channel_Coding_Command_SIZE   4
#define CSN1_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY_short_layer_2_header 451
#define CSN1_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY_short_layer_2_header_SIZE   2
#define CSN1_paging_channel_restructuring_paging_channel_restructuring 600
#define CSN1_paging_channel_restructuring_paging_channel_restructuring_SIZE   1
#define CSN1_DTMInfoRestOctets_DEDICATED_MODE_MBMS_NOTIFICATION_SUPPORT 168
#define CSN1_DTMInfoRestOctets_DEDICATED_MODE_MBMS_NOTIFICATION_SUPPORT_SIZE   1
#define CSN1_EGPRS_Packet_Uplink_Assignment_Access_Technologies_Request 480
#define CSN1_EGPRS_Packet_Uplink_Assignment_Access_Technologies_Request_SIZE   0
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_REPORT_TYPE 1014
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_REPORT_TYPE_SIZE   1
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_Random_Reference 1169
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_Random_Reference_SIZE  11
#define CSN1_MBMS_Session_Parameters_List_IE_Estimated_Session_Duration 1182
#define CSN1_MBMS_Session_Parameters_List_IE_Estimated_Session_Duration_SIZE   8
#define CSN1_Measurement_information_MEASUREMENT_Parameters_Description 707
#define CSN1_Measurement_information_MEASUREMENT_Parameters_Description_SIZE   0
#define CSN1_Multiple_TBF_Allocation_struct_EXTENDED_DYNAMIC_ALLOCATION 930
#define CSN1_Multiple_TBF_Allocation_struct_EXTENDED_DYNAMIC_ALLOCATION_SIZE   1
#define CSN1_RRClassmark3Value_E_UTRA_Measurement_and_Reporting_support 379
#define CSN1_RRClassmark3Value_E_UTRA_Measurement_and_Reporting_support_SIZE   1
#define CSN1_Real_Time_Difference_Description_struct_BA_Index_Start_RTD 696
#define CSN1_Real_Time_Difference_Description_struct_BA_Index_Start_RTD_SIZE   5
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_THRESH_E_UTRAN_low 1112
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_THRESH_E_UTRAN_low_SIZE   5
#define CSN1_Repeated_UTRAN_Priority_Parameters_struct_THRESH_UTRAN_low 1089
#define CSN1_Repeated_UTRAN_Priority_Parameters_struct_THRESH_UTRAN_low_SIZE   5
#define CSN1_SI2_3G_MEASUREMENT_Parameters_Description_struct_Qsearch_I 242
#define CSN1_SI2_3G_MEASUREMENT_Parameters_Description_struct_Qsearch_I_SIZE   4
#define CSN1_SI2quaterRestOctets_p3G_Measurement_Parameters_Description 1044
#define CSN1_SI2quaterRestOctets_p3G_Measurement_Parameters_Description_SIZE   0
#define CSN1_Serving_Cell_Priority_Parameters_Description_struct_H_PRIO 1077
#define CSN1_Serving_Cell_Priority_Parameters_Description_struct_H_PRIO_SIZE   2
#define CSN1_UTRAN_FDD_Description_struct_CS_FDD_CELL_INFORMATION_Field 467
#define CSN1_UTRAN_FDD_Description_struct_CS_FDD_CELL_INFORMATION_Field_SIZE   0
#define CSN1_UTRAN_TDD_Description_struct_CS_TDD_CELL_INFORMATION_Field 473
#define CSN1_UTRAN_TDD_Description_struct_CS_TDD_CELL_INFORMATION_Field_SIZE   0
#define CSN1__3G_Supplementary_Parameters_Description_struct_UTRAN_Stop 771
#define CSN1__3G_Supplementary_Parameters_Description_struct_UTRAN_Stop_SIZE   1
#define CSN1_Downlink_TBF_assignment_2_struct_Downlink_EGPRS_Window_Size 227
#define CSN1_Downlink_TBF_assignment_2_struct_Downlink_EGPRS_Window_Size_SIZE   5
#define CSN1_EGPRS_Packet_Uplink_Assignment_EGPRS_CHANNEL_CODING_COMMAND 490
#define CSN1_EGPRS_Packet_Uplink_Assignment_EGPRS_CHANNEL_CODING_COMMAND_SIZE   4
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_Qsearch_P 1054
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_Qsearch_P_SIZE   4
#define CSN1_Multiple_Downlink_TBF_Assignment_struct_TIMESLOT_ALLOCATION 827
#define CSN1_Multiple_Downlink_TBF_Assignment_struct_TIMESLOT_ALLOCATION_SIZE   8
#define CSN1_RRClassmark3Value_E_UTRA_Wideband_RSRQ_measurements_support 388
#define CSN1_RRClassmark3Value_E_UTRA_Wideband_RSRQ_measurements_support_SIZE   1
#define CSN1_RRPacketDownlinkAssignmentType2_Measurement_Control_E_UTRAN 874
#define CSN1_RRPacketDownlinkAssignmentType2_Measurement_Control_E_UTRAN_SIZE   1
#define CSN1_RRPacketDownlinkAssignmentType2_Power_Control_Parameters_C1 852
#define CSN1_RRPacketDownlinkAssignmentType2_Power_Control_Parameters_C1_SIZE   0
#define CSN1_RRPacketDownlinkAssignmentType2_Power_Control_Parameters_C2 853
#define CSN1_RRPacketDownlinkAssignmentType2_Power_Control_Parameters_C2_SIZE   0
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_THRESH_E_UTRAN_high 1111
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_THRESH_E_UTRAN_high_SIZE   5
#define CSN1_Repeated_E_UTRAN_Not_Allowed_Cells_struct_Not_Allowed_Cells 262
#define CSN1_Repeated_E_UTRAN_Not_Allowed_Cells_struct_Not_Allowed_Cells_SIZE   0
#define CSN1_Repeated_UTRAN_Priority_Parameters_struct_THRESH_UTRAN_high 1088
#define CSN1_Repeated_UTRAN_Priority_Parameters_struct_THRESH_UTRAN_high_SIZE   5
#define CSN1_SI2quaterRestOctets_GPRS_MEASUREMENT_Parameters_Description 1013
#define CSN1_SI2quaterRestOctets_GPRS_MEASUREMENT_Parameters_Description_SIZE   0
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REP_QUANT 754
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REP_QUANT_SIZE   1
#define CSN1__3G_Neighbour_Cell_Description_struct_UTRAN_FDD_Description 1042
#define CSN1__3G_Neighbour_Cell_Description_struct_UTRAN_FDD_Description_SIZE   0
#define CSN1__3G_Neighbour_Cell_Description_struct_UTRAN_TDD_Description 1043
#define CSN1__3G_Neighbour_Cell_Description_struct_UTRAN_TDD_Description_SIZE   0
#define CSN1__3G_Supplementary_Parameters_Description_struct_UTRAN_Start 770
#define CSN1__3G_Supplementary_Parameters_Description_struct_UTRAN_Start_SIZE   1
#define CSN1_IPA_Downlink_Assignment_struct_LINK_QUALITY_MEASUREMENT_MODE 1165
#define CSN1_IPA_Downlink_Assignment_struct_LINK_QUALITY_MEASUREMENT_MODE_SIZE   2
#define CSN1_IRAT_Cell_Reselection_Information_struct_Nb_Additional_PLMNs 1142
#define CSN1_IRAT_Cell_Reselection_Information_struct_Nb_Additional_PLMNs_SIZE   2
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_TBF_STARTING_TIME 509
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_TBF_STARTING_TIME_SIZE  16
#define CSN1_SI2_3G_MEASUREMENT_Parameters_Description_struct_FDD_Qoffset 243
#define CSN1_SI2_3G_MEASUREMENT_Parameters_Description_struct_FDD_Qoffset_SIZE   4
#define CSN1_SI2_3G_MEASUREMENT_Parameters_Description_struct_TDD_Qoffset 245
#define CSN1_SI2_3G_MEASUREMENT_Parameters_Description_struct_TDD_Qoffset_SIZE   4
#define CSN1_Direct_encoding_2_struct_Length_of_MA_Frequency_List_contents 923
#define CSN1_Direct_encoding_2_struct_Length_of_MA_Frequency_List_contents_SIZE   4
#define CSN1_Enhanced_Measurement_report_Repeated_Invalid_BSIC_Information 438
#define CSN1_Enhanced_Measurement_report_Repeated_Invalid_BSIC_Information_SIZE  17
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_REPORTING_RATE 1015
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_REPORTING_RATE_SIZE   1
#define CSN1_Measurement_information_UTRAN_CSG_Cells_Reporting_Description 794
#define CSN1_Measurement_information_UTRAN_CSG_Cells_Reporting_Description_SIZE   0
#define CSN1_Pulse_Format_Coding_2_struct_Non_Hopping_Carrier_Pulse_Format 966
#define CSN1_Pulse_Format_Coding_2_struct_Non_Hopping_Carrier_Pulse_Format_SIZE   0
#define CSN1_RRClassmark3Value_UMTS_FDD_Radio_Access_Technology_Capability 346
#define CSN1_RRClassmark3Value_UMTS_FDD_Radio_Access_Technology_Capability_SIZE   1
#define CSN1_RRPacketDownlinkAssignmentType2_LINK_QUALITY_MEASUREMENT_MODE 856
#define CSN1_RRPacketDownlinkAssignmentType2_LINK_QUALITY_MEASUREMENT_MODE_SIZE   2
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_Measurement_Bandwidth 1109
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_Measurement_Bandwidth_SIZE   3
#define CSN1_Repeated_E_UTRAN_PCID_to_TA_mapping_struct_PCID_to_TA_mapping 264
#define CSN1_Repeated_E_UTRAN_PCID_to_TA_mapping_struct_PCID_to_TA_mapping_SIZE   0
#define CSN1__3G_Neighbour_Cell_Description_struct_RR_CDMA2000_Description 728
#define CSN1__3G_Neighbour_Cell_Description_struct_RR_CDMA2000_Description_SIZE   0
#define CSN1_Extension_Information_DEDICATED_MODE_MBMS_NOTIFICATION_SUPPORT 681
#define CSN1_Extension_Information_DEDICATED_MODE_MBMS_NOTIFICATION_SUPPORT_SIZE   1
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_Frequency_Parameters 1175
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_Frequency_Parameters_SIZE   0
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_STARTING_TIME_OFFSET 1173
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_STARTING_TIME_OFFSET_SIZE   6
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_TIMING_ADVANCE_VALUE 1172
#define CSN1_IPA_Single_Block_Uplink_Assignment_struct_TIMING_ADVANCE_VALUE_SIZE   6
#define CSN1_IPA_Uplink_Assignment_struct_Radio_Access_Capabilities_Request 1158
#define CSN1_IPA_Uplink_Assignment_struct_Radio_Access_Capabilities_Request_SIZE   1
#define CSN1_MBMS_Session_Parameters_List_IE_Length_of_MBMS_Bearer_Identity 1180
#define CSN1_MBMS_Session_Parameters_List_IE_Length_of_MBMS_Bearer_Identity_SIZE   3
#define CSN1_Measurement_information__3G_MEASUREMENT_Parameters_Description 752
#define CSN1_Measurement_information__3G_MEASUREMENT_Parameters_Description_SIZE   0
#define CSN1_RRClassmark3Value_CDMA_2000_Radio_Access_Technology_Capability 348
#define CSN1_RRClassmark3Value_CDMA_2000_Radio_Access_Technology_Capability_SIZE   1
#define CSN1_RRPacketDownlinkAssignmentType2_PDCH_pairs_configuration_error 1402
#define CSN1_RRPacketDownlinkAssignmentType2_PDCH_pairs_configuration_error_SIZE   2
#define CSN1_Repeated_Individual_UTRAN_Priority_Parameters_struct_FDD_ARFCN 646
#define CSN1_Repeated_Individual_UTRAN_Priority_Parameters_struct_FDD_ARFCN_SIZE  14
#define CSN1_Repeated_Individual_UTRAN_Priority_Parameters_struct_TDD_ARFCN 647
#define CSN1_Repeated_Individual_UTRAN_Priority_Parameters_struct_TDD_ARFCN_SIZE  14
#define CSN1_SI2quaterRestOctets_Extended_EARFCNs_Description_for_CSG_Cells 1133
#define CSN1_SI2quaterRestOctets_Extended_EARFCNs_Description_for_CSG_Cells_SIZE   0
#define CSN1_SI2quaterRestOctets_GPRS_3G_MEASUREMENT_Parameters_Description 1053
#define CSN1_SI2quaterRestOctets_GPRS_3G_MEASUREMENT_Parameters_Description_SIZE   0
#define CSN1__3G_Neighbour_Cell_Description_struct_Absolute_Index_Start_EMR 1041
#define CSN1__3G_Neighbour_Cell_Description_struct_Absolute_Index_Start_EMR_SIZE   7
#define CSN1__3G_Neighbour_Cell_Description_struct_RR_UTRAN_FDD_Description 726
#define CSN1__3G_Neighbour_Cell_Description_struct_RR_UTRAN_FDD_Description_SIZE   0
#define CSN1__3G_Neighbour_Cell_Description_struct_RR_UTRAN_TDD_Description 727
#define CSN1__3G_Neighbour_Cell_Description_struct_RR_UTRAN_TDD_Description_SIZE   0
#define CSN1_EGPRS_Packet_Uplink_Assignment_NUMBER_OF_RADIO_BLOCKS_ALLOCATED 507
#define CSN1_EGPRS_Packet_Uplink_Assignment_NUMBER_OF_RADIO_BLOCKS_ALLOCATED_SIZE   2
#define CSN1_ETWS_Primary_Notification_struct_ETWS_Primary_Notification_Data 1234
#define CSN1_ETWS_Primary_Notification_struct_ETWS_Primary_Notification_Data_SIZE   0
#define CSN1_Early_Classmark_Sending_Control_Early_Classmark_Sending_Control 582
#define CSN1_Early_Classmark_Sending_Control_Early_Classmark_Sending_Control_SIZE   0
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REP_QUANT 1056
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REP_QUANT_SIZE   1
#define CSN1_GPRS_Real_Time_Difference_Description_struct_BA_Index_Start_RTD 1002
#define CSN1_GPRS_Real_Time_Difference_Description_struct_BA_Index_Start_RTD_SIZE   5
#define CSN1_MBMS_Session_Parameters_List_IE_MBMS_Radio_Bearer_Starting_Time 1183
#define CSN1_MBMS_Session_Parameters_List_IE_MBMS_Radio_Bearer_Starting_Time_SIZE  16
#define CSN1_Multiple_Downlink_TBF_Assignment_struct_Downlink_TBF_assignment 828
#define CSN1_Multiple_Downlink_TBF_Assignment_struct_Downlink_TBF_assignment_SIZE   0
#define CSN1_Multiple_Downlink_TBF_Assignment_struct_Uplink_Control_Timeslot 826
#define CSN1_Multiple_Downlink_TBF_Assignment_struct_Uplink_Control_Timeslot_SIZE   3
#define CSN1_Repeated_UTRAN_Priority_Parameters_struct_UTRAN_FREQUENCY_INDEX 1086
#define CSN1_Repeated_UTRAN_Priority_Parameters_struct_UTRAN_FREQUENCY_INDEX_SIZE   5
#define CSN1_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description 1072
#define CSN1_SI2quaterRestOctets_Priority_and_E_UTRAN_Parameters_Description_SIZE   0
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_Qmin 1050
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_Qmin_SIZE   3
#define CSN1_UTRAN_FDD_Description_struct_Repeated_UTRAN_FDD_Neighbour_Cells 250
#define CSN1_UTRAN_FDD_Description_struct_Repeated_UTRAN_FDD_Neighbour_Cells_SIZE   0
#define CSN1_UTRAN_TDD_Description_struct_Repeated_UTRAN_TDD_Neighbour_Cells 256
#define CSN1_UTRAN_TDD_Description_struct_Repeated_UTRAN_TDD_Neighbour_Cells_SIZE   0
#define CSN1__3G_Priority_Parameters_Description_struct_DEFAULT_THRESH_UTRAN 1083
#define CSN1__3G_Priority_Parameters_Description_struct_DEFAULT_THRESH_UTRAN_SIZE   5
#define CSN1_MEASUREMENT_PARAMETERS_Description_Struct_SERVING_BAND_REPORTING 1000
#define CSN1_MEASUREMENT_PARAMETERS_Description_Struct_SERVING_BAND_REPORTING_SIZE   2
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR_MULTIBAND_REPORTING 708
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR_MULTIBAND_REPORTING_SIZE   2
#define CSN1_Measurement_information__3G_Supplementary_Parameters_Description 769
#define CSN1_Measurement_information__3G_Supplementary_Parameters_Description_SIZE   0
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_MBMS_Session_Identity 518
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_MBMS_Session_Identity_SIZE   8
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_PACKET_TIMING_ADVANCE 514
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_PACKET_TIMING_ADVANCE_SIZE   0
#define CSN1_Repeated_E_UTRAN_NC_with_extended_EARFCNs_struct_EARFCN_extended 796
#define CSN1_Repeated_E_UTRAN_NC_with_extended_EARFCNs_struct_EARFCN_extended_SIZE  18
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_RR_Measurement_Bandwidth 783
#define CSN1_Repeated_E_UTRAN_Neighbour_Cells_struct_RR_Measurement_Bandwidth_SIZE   3
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_Qsearch_I 1045
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_Qsearch_I_SIZE   4
#define CSN1_Compressed_Inter_RAT_HO_INFO_IND_Compressed_Inter_RAT_HO_INFO_IND   1
#define CSN1_Compressed_Inter_RAT_HO_INFO_IND_Compressed_Inter_RAT_HO_INFO_IND_SIZE   0
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_p3G_SEARCH_PRIO 1055
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_p3G_SEARCH_PRIO_SIZE   1
#define CSN1_RRClassmark3Value_UTRA_Multiple_Frequency_Band_Indicators_support 390
#define CSN1_RRClassmark3Value_UTRA_Multiple_Frequency_Band_Indicators_support_SIZE   1
#define CSN1_Repeated_E_UTRAN_Not_Allowed_Cells_struct_E_UTRAN_FREQUENCY_INDEX 263
#define CSN1_Repeated_E_UTRAN_Not_Allowed_Cells_struct_E_UTRAN_FREQUENCY_INDEX_SIZE   3
#define CSN1_Serving_Cell_Priority_Parameters_Description_struct_T_Reselection 1078
#define CSN1_Serving_Cell_Priority_Parameters_Description_struct_T_Reselection_SIZE   2
#define CSN1__3G_Neighbour_Cell_Description_struct_RR_Absolute_Index_Start_EMR 725
#define CSN1__3G_Neighbour_Cell_Description_struct_RR_Absolute_Index_Start_EMR_SIZE   7
#define CSN1__3G_Priority_Parameters_Description_struct_DEFAULT_UTRAN_PRIORITY 1082
#define CSN1__3G_Priority_Parameters_Description_struct_DEFAULT_UTRAN_PRIORITY_SIZE   3
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_MULTIBAND_REPORTING 1017
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_MULTIBAND_REPORTING_SIZE   2
#define CSN1_IndividualPriorities_E_UTRAN_IPP_with_extended_EARFCNs_Description 655
#define CSN1_IndividualPriorities_E_UTRAN_IPP_with_extended_EARFCNs_Description_SIZE   0
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__400_REPORTING_OFFSET 715
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__400_REPORTING_OFFSET_SIZE   3
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__850_REPORTING_OFFSET 719
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__850_REPORTING_OFFSET_SIZE   3
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__900_REPORTING_OFFSET 711
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__900_REPORTING_OFFSET_SIZE   3
#define CSN1_Repeated_E_UTRAN_PCID_to_TA_mapping_struct_E_UTRAN_FREQUENCY_INDEX 265
#define CSN1_Repeated_E_UTRAN_PCID_to_TA_mapping_struct_E_UTRAN_FREQUENCY_INDEX_SIZE   3
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_Qoffset 1047
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_Qoffset_SIZE   4
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_Qoffset 1051
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_Qoffset_SIZE   4
#define CSN1_SI2terRestOctets__3G_Additional_Measurement_Parameters_Description 246
#define CSN1_SI2terRestOctets__3G_Additional_Measurement_Parameters_Description_SIZE   7
#define CSN1_Serving_Cell_Priority_Parameters_Description_struct_GERAN_PRIORITY 1074
#define CSN1_Serving_Cell_Priority_Parameters_Description_struct_GERAN_PRIORITY_SIZE   3
#define CSN1_Serving_Cell_Priority_Parameters_Description_struct_THRESH_GSM_low 1076
#define CSN1_Serving_Cell_Priority_Parameters_Description_struct_THRESH_GSM_low_SIZE   4
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REPORTING_OFFSET 756
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REPORTING_OFFSET_SIZE   3
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_REPORTING_OFFSET 759
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_REPORTING_OFFSET_SIZE   3
#define CSN1__3G_Priority_Parameters_Description_struct_DEFAULT_UTRAN_QRXLEVMIN 1084
#define CSN1__3G_Priority_Parameters_Description_struct_DEFAULT_UTRAN_QRXLEVMIN_SIZE   5
#define CSN1_BTTI_Multiple_Downlink_TBF_Assignment_struct_TIMESLOT_ALLOCATION_C1 870
#define CSN1_BTTI_Multiple_Downlink_TBF_Assignment_struct_TIMESLOT_ALLOCATION_C1_SIZE   8
#define CSN1_BTTI_Multiple_Downlink_TBF_Assignment_struct_TIMESLOT_ALLOCATION_C2 871
#define CSN1_BTTI_Multiple_Downlink_TBF_Assignment_struct_TIMESLOT_ALLOCATION_C2_SIZE   8
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_REP_QUANT  56
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_REP_QUANT_SIZE   1
#define CSN1_IndividualPriorities__3G_Individual_Priority_Parameters_Description 643
#define CSN1_IndividualPriorities__3G_Individual_Priority_Parameters_Description_SIZE   0
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR_SERVING_BAND_REPORTING 709
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR_SERVING_BAND_REPORTING_SIZE   2
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__1800_REPORTING_OFFSET 713
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__1800_REPORTING_OFFSET_SIZE   3
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__1900_REPORTING_OFFSET 717
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__1900_REPORTING_OFFSET_SIZE   3
#define CSN1_RRClassmark3Value_E_UTRA_Multiple_Frequency_Band_Indicators_support 391
#define CSN1_RRClassmark3Value_E_UTRA_Multiple_Frequency_Band_Indicators_support_SIZE   1
#define CSN1_RTTI_Multiple_Downlink_Assignment_DC_struct_Downlink_TBF_assignment 863
#define CSN1_RTTI_Multiple_Downlink_Assignment_DC_struct_Downlink_TBF_assignment_SIZE   0
#define CSN1_RTTI_Multiple_Downlink_Assignment_SC_struct_Downlink_TBF_assignment 866
#define CSN1_RTTI_Multiple_Downlink_Assignment_SC_struct_Downlink_TBF_assignment_SIZE   0
#define CSN1_Repeated_Individual_UTRAN_Priority_Parameters_struct_UTRAN_PRIORITY 648
#define CSN1_Repeated_Individual_UTRAN_Priority_Parameters_struct_UTRAN_PRIORITY_SIZE   3
#define CSN1_BTTI_Multiple_Downlink_TBF_Assignment_struct_Downlink_TBF_assignment 872
#define CSN1_BTTI_Multiple_Downlink_TBF_Assignment_struct_Downlink_TBF_assignment_SIZE   0
#define CSN1_BTTI_Multiple_Downlink_TBF_Assignment_struct_Uplink_Control_Timeslot 869
#define CSN1_BTTI_Multiple_Downlink_TBF_Assignment_struct_Uplink_Control_Timeslot_SIZE   3
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p400_REPORTING_OFFSET 1024
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p400_REPORTING_OFFSET_SIZE   3
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p850_REPORTING_OFFSET 1028
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p850_REPORTING_OFFSET_SIZE   3
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p900_REPORTING_OFFSET 1020
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p900_REPORTING_OFFSET_SIZE   3
#define CSN1_Measurement_information_E_UTRAN_NC_with_extended_EARFCNs_Description 795
#define CSN1_Measurement_information_E_UTRAN_NC_with_extended_EARFCNs_Description_SIZE   0
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_Length_Indicator_of_MS_ID 512
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_Length_Indicator_of_MS_ID_SIZE   2
#define CSN1_RRPacketDownlinkAssignmentType2_RTTI_Multiple_Downlink_Assignment_DC 861
#define CSN1_RRPacketDownlinkAssignmentType2_RTTI_Multiple_Downlink_Assignment_DC_SIZE   0
#define CSN1_RRPacketDownlinkAssignmentType2_RTTI_Multiple_Downlink_Assignment_SC 864
#define CSN1_RRPacketDownlinkAssignmentType2_RTTI_Multiple_Downlink_Assignment_SC_SIZE   0
#define CSN1_Repeated_UTRAN_FDD_Neighbour_Cells_struct_FDD_CELL_INFORMATION_Field 254
#define CSN1_Repeated_UTRAN_FDD_Neighbour_Cells_struct_FDD_CELL_INFORMATION_Field_SIZE   0
#define CSN1_Repeated_UTRAN_TDD_Neighbour_Cells_struct_TDD_CELL_INFORMATION_Field 261
#define CSN1_Repeated_UTRAN_TDD_Neighbour_Cells_struct_TDD_CELL_INFORMATION_Field_SIZE   0
#define CSN1_SI2quaterRestOctets_Enhanced_Cell_Reselection_Parameters_Description 1122
#define CSN1_SI2quaterRestOctets_Enhanced_Cell_Reselection_Parameters_Description_SIZE   0
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REP_QUANT 1048
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REP_QUANT_SIZE   1
#define CSN1__3G_Additional_Measurement_Parameters_Description_struct_FDD_RSCPmin 1065
#define CSN1__3G_Additional_Measurement_Parameters_Description_struct_FDD_RSCPmin_SIZE   4
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_MULTIRAT_REPORTING 755
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_MULTIRAT_REPORTING_SIZE   2
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_MULTIRAT_REPORTING 758
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_MULTIRAT_REPORTING_SIZE   2
#define CSN1_Extended_EARFCNs_Description_for_CSG_Cells_struct_CSG_EARFCN_extended 1134
#define CSN1_Extended_EARFCNs_Description_for_CSG_Cells_struct_CSG_EARFCN_extended_SIZE  18
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_INVALID_BSIC_REPORTING 1016
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_INVALID_BSIC_REPORTING_SIZE   1
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_SERVING_BAND_REPORTING 1018
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_SERVING_BAND_REPORTING_SIZE   2
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p1800_REPORTING_OFFSET 1022
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p1800_REPORTING_OFFSET_SIZE   3
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p1900_REPORTING_OFFSET 1026
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p1900_REPORTING_OFFSET_SIZE   3
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__400_REPORTING_THRESHOLD 716
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__400_REPORTING_THRESHOLD_SIZE   3
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__850_REPORTING_THRESHOLD 720
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__850_REPORTING_THRESHOLD_SIZE   3
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__900_REPORTING_THRESHOLD 712
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__900_REPORTING_THRESHOLD_SIZE   3
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_NUMBER_OF_ALLOCATED_BLOCKS 510
#define CSN1_Multiple_Blocks_Packet_Downlink_Assignment_NUMBER_OF_ALLOCATED_BLOCKS_SIZE   4
#define CSN1_RRPacketDownlinkAssignmentType2_BTTI_Multiple_Downlink_TBF_Assignment 868
#define CSN1_RRPacketDownlinkAssignmentType2_BTTI_Multiple_Downlink_TBF_Assignment_SIZE   0
#define CSN1_SI2quaterRestOctets__3G_Additional_Measurement_Parameters_Description 1063
#define CSN1_SI2quaterRestOctets__3G_Additional_Measurement_Parameters_Description_SIZE   7
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REPORTING_THRESHOLD 757
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_REPORTING_THRESHOLD 760
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1_E_UTRAN_Parameters_Description_struct_Repeated_E_UTRAN_Neighbour_Cells 1106
#define CSN1_E_UTRAN_Parameters_Description_struct_Repeated_E_UTRAN_Neighbour_Cells_SIZE   0
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REPORTING_OFFSET 1058
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REPORTING_OFFSET_SIZE   3
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_REPORTING_OFFSET 1061
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_REPORTING_OFFSET_SIZE   3
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__1800_REPORTING_THRESHOLD 714
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__1800_REPORTING_THRESHOLD_SIZE   3
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__1900_REPORTING_THRESHOLD 718
#define CSN1_MEASUREMENT_PARAMETERS_Description_struct_RR__1900_REPORTING_THRESHOLD_SIZE   3
#define CSN1_Repeated_E_UTRAN_NC_with_extended_EARFCNs_struct_Measurement_Bandwidth 797
#define CSN1_Repeated_E_UTRAN_NC_with_extended_EARFCNs_struct_Measurement_Bandwidth_SIZE   3
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_REPORTING_GRANULARITY  64
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_REPORTING_GRANULARITY_SIZE   1
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p400_REPORTING_THRESHOLD 1025
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p400_REPORTING_THRESHOLD_SIZE   3
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p850_REPORTING_THRESHOLD 1029
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p850_REPORTING_THRESHOLD_SIZE   3
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p900_REPORTING_THRESHOLD 1021
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p900_REPORTING_THRESHOLD_SIZE   3
#define CSN1_IndividualPriorities_E_UTRAN_Individual_Priority_Parameters_Description 649
#define CSN1_IndividualPriorities_E_UTRAN_Individual_Priority_Parameters_Description_SIZE   0
#define CSN1_Priority_and_UTRAN_Parameters_Description_struct_DEFAULT_UTRAN_PRIORITY 613
#define CSN1_Priority_and_UTRAN_Parameters_Description_struct_DEFAULT_UTRAN_PRIORITY_SIZE   3
#define CSN1_RRClassmark3Value_UMTS_1_28_Mcps_TDD_Radio_Access_Technology_Capability 354
#define CSN1_RRClassmark3Value_UMTS_1_28_Mcps_TDD_Radio_Access_Technology_Capability_SIZE   1
#define CSN1_RRClassmark3Value_UMTS_3_84_Mcps_TDD_Radio_Access_Technology_Capability 347
#define CSN1_RRClassmark3Value_UMTS_3_84_Mcps_TDD_Radio_Access_Technology_Capability_SIZE   1
#define CSN1_SI2_3G_Additional_Measurement_Parameters_Description_struct_FDD_RSCPmin 248
#define CSN1_SI2_3G_Additional_Measurement_Parameters_Description_struct_FDD_RSCPmin_SIZE   4
#define CSN1_SI2quaterRestOctets__3G_ADDITIONAL_MEASUREMENT_Parameters_Description_2 1066
#define CSN1_SI2quaterRestOctets__3G_ADDITIONAL_MEASUREMENT_Parameters_Description_2_SIZE   0
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_CDMA2000_REPORTING_OFFSET 762
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_CDMA2000_REPORTING_OFFSET_SIZE   3
#define CSN1_E_UTRAN_Parameters_Description_struct_Repeated_E_UTRAN_Not_Allowed_Cells 1114
#define CSN1_E_UTRAN_Parameters_Description_struct_Repeated_E_UTRAN_Not_Allowed_Cells_SIZE   0
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_MULTIRAT_REPORTING 1057
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_MULTIRAT_REPORTING_SIZE   2
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_MULTIRAT_REPORTING 1060
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_MULTIRAT_REPORTING_SIZE   2
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_REP_QUANT 1098
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_REP_QUANT_SIZE   1
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_Qsearch_P_E_UTRAN 1097
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_Qsearch_P_E_UTRAN_SIZE   4
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p1800_REPORTING_THRESHOLD 1023
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p1800_REPORTING_THRESHOLD_SIZE   3
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p1900_REPORTING_THRESHOLD 1027
#define CSN1_GPRS_MEASUREMENT_PARAMETERS_Description_struct_p1900_REPORTING_THRESHOLD_SIZE   3
#define CSN1_Priority_and_UTRAN_Parameters_Description_struct_DEFAULT_UTRAN_QRXLEVMIN 615
#define CSN1_Priority_and_UTRAN_Parameters_Description_struct_DEFAULT_UTRAN_QRXLEVMIN_SIZE   5
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_EARFCN_extended 629
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_EARFCN_extended_SIZE  18
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_Qsearch_C_Initial 1046
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_Qsearch_C_Initial_SIZE   1
#define CSN1__3G_Additional_Measurement_Parameters_Description_struct_FDD_Qmin_Offset 1064
#define CSN1__3G_Additional_Measurement_Parameters_Description_struct_FDD_Qmin_Offset_SIZE   3
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_Repeated_E_UTRAN_Neighbour_Cells 781
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_Repeated_E_UTRAN_Neighbour_Cells_SIZE   0
#define CSN1_E_UTRAN_Parameters_Description_struct_Repeated_E_UTRAN_PCID_to_TA_mapping 1115
#define CSN1_E_UTRAN_Parameters_Description_struct_Repeated_E_UTRAN_PCID_to_TA_mapping_SIZE   0
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REPORTING_THRESHOLD 1059
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_REPORTING_THRESHOLD 1062
#define CSN1_GPRS_3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1_Priority_and_UTRAN_Parameters_Description_struct_DEFAULT_THRESH_UTRAN_low 614
#define CSN1_Priority_and_UTRAN_Parameters_Description_struct_DEFAULT_THRESH_UTRAN_low_SIZE   5
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_E_UTRAN_Qmin 407
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_E_UTRAN_Qmin_SIZE   4
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_E_UTRAN_PRIORITY 631
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_E_UTRAN_PRIORITY_SIZE   3
#define CSN1_Repeated_Individual_E_UTRAN_Priority_Parameters_Description_struct_EARFCN 652
#define CSN1_Repeated_Individual_E_UTRAN_Priority_Parameters_Description_struct_EARFCN_SIZE  16
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_CDMA2000_MULTIRAT_REPORTING 761
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_CDMA2000_MULTIRAT_REPORTING_SIZE   2
#define CSN1_Priority_and_UTRAN_Parameters_Description_struct_UTRAN_FDD_TDD_Description 616
#define CSN1_Priority_and_UTRAN_Parameters_Description_struct_UTRAN_FDD_TDD_Description_SIZE   0
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_E_UTRAN_QRXLEVMIN 634
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_E_UTRAN_QRXLEVMIN_SIZE   5
#define CSN1_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_struct_UTRAN_ARFCN 620
#define CSN1_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_struct_UTRAN_ARFCN_SIZE  14
#define CSN1_Repeated_UTRAN_Measurement_Control_Parameters_struct_UTRAN_FREQUENCY_INDEX 775
#define CSN1_Repeated_UTRAN_Measurement_Control_Parameters_struct_UTRAN_FREQUENCY_INDEX_SIZE   5
#define CSN1_Serving_Cell_Priority_Parameters_Description_struct_THRESH_Priority_Search 1075
#define CSN1_Serving_Cell_Priority_Parameters_Description_struct_THRESH_Priority_Search_SIZE   4
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_CDMA2000_REPORTING_THRESHOLD 763
#define CSN1__3G_MEASUREMENT_PARAMETERS_Description_struct_CDMA2000_REPORTING_THRESHOLD_SIZE   3
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_Qsearch_C_E_UTRAN_Initial  55
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_Qsearch_C_E_UTRAN_Initial_SIZE   4
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_Repeated_E_UTRAN_Not_Allowed_Cells 784
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_Repeated_E_UTRAN_Not_Allowed_Cells_SIZE   0
#define CSN1_Measurement_information__3G_ADDITIONAL_MEASUREMENT_Parameters_Description_2 764
#define CSN1_Measurement_information__3G_ADDITIONAL_MEASUREMENT_Parameters_Description_2_SIZE   0
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_THRESH_E_UTRAN_low 633
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_THRESH_E_UTRAN_low_SIZE   5
#define CSN1_SI2_3G_Additional_Measurement_Parameters_Description_struct_FDD_Qmin_Offset 247
#define CSN1_SI2_3G_Additional_Measurement_Parameters_Description_struct_FDD_Qmin_Offset_SIZE   3
#define CSN1_CSG_Cells_Reporting_Description_struct_UTRAN_CSG_Cells_Reporting_Description 1124
#define CSN1_CSG_Cells_Reporting_Description_struct_UTRAN_CSG_Cells_Reporting_Description_SIZE   0
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_MULTIRAT_REPORTING  57
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_MULTIRAT_REPORTING_SIZE   2
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_E_UTRAN_RSRPmin 406
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_E_UTRAN_RSRPmin_SIZE   5
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_THRESH_E_UTRAN_high 632
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_THRESH_E_UTRAN_high_SIZE   5
#define CSN1__3G_Individual_Priority_Parameters_Description_struct_DEFAULT_UTRAN_PRIORITY 644
#define CSN1__3G_Individual_Priority_Parameters_Description_struct_DEFAULT_UTRAN_PRIORITY_SIZE   3
#define CSN1_E_UTRAN_IPP_with_extended_EARFCNs_Description_struct_DEFAULT_E_UTRAN_PRIORITY 656
#define CSN1_E_UTRAN_IPP_with_extended_EARFCNs_Description_struct_DEFAULT_E_UTRAN_PRIORITY_SIZE   3
#define CSN1_RRPacketDownlinkAssignmentType2_EGPRS_Packet_Downlink_Ack_Nack_Type_3_Support 883
#define CSN1_RRPacketDownlinkAssignmentType2_EGPRS_Packet_Downlink_Ack_Nack_Type_3_Support_SIZE   1
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_E_UTRAN_QQUALMIN 405
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_E_UTRAN_QQUALMIN_SIZE   4
#define CSN1_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_struct_UTRAN_PRIORITY 621
#define CSN1_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_struct_UTRAN_PRIORITY_SIZE   3
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_MULTIRAT_REPORTING 1049
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_FDD_MULTIRAT_REPORTING_SIZE   2
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_MULTIRAT_REPORTING 1052
#define CSN1_SI2quater_3G_MEASUREMENT_PARAMETERS_Description_struct_TDD_MULTIRAT_REPORTING_SIZE   2
#define CSN1__3G_Priority_Parameters_Description_struct_Repeated_UTRAN_Priority_Parameters 1085
#define CSN1__3G_Priority_Parameters_Description_struct_Repeated_UTRAN_Priority_Parameters_SIZE   0
#define CSN1_CSG_Cells_Reporting_Description_struct_E_UTRAN_CSG_Cells_Reporting_Description 1125
#define CSN1_CSG_Cells_Reporting_Description_struct_E_UTRAN_CSG_Cells_Reporting_Description_SIZE   0
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_OFFSET  60
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_OFFSET_SIZE   3
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_OFFSET  63
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_OFFSET_SIZE   3
#define CSN1_Repeated_E_UTRAN_Measurement_Control_Parameters_struct_E_UTRAN_FREQUENCY_INDEX 788
#define CSN1_Repeated_E_UTRAN_Measurement_Control_Parameters_struct_E_UTRAN_FREQUENCY_INDEX_SIZE   3
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_Measurement_Bandwidth 630
#define CSN1_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_struct_Measurement_Bandwidth_SIZE   3
#define CSN1_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_struct_UTRAN_QRXLEVMIN 624
#define CSN1_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_struct_UTRAN_QRXLEVMIN_SIZE   5
#define CSN1_Repeated_UTRAN_Measurement_Control_Parameters_struct_Measurement_Control_UTRAN 776
#define CSN1_Repeated_UTRAN_Measurement_Control_Parameters_struct_Measurement_Control_UTRAN_SIZE   1
#define CSN1_UTRAN_CSG_Cells_Reporting_Description_struct_UTRAN_CSG_FDD_REPORTING_THRESHOLD  67
#define CSN1_UTRAN_CSG_Cells_Reporting_Description_struct_UTRAN_CSG_FDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1_UTRAN_CSG_Cells_Reporting_Description_struct_UTRAN_CSG_TDD_REPORTING_THRESHOLD  69
#define CSN1_UTRAN_CSG_Cells_Reporting_Description_struct_UTRAN_CSG_TDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_DEFAULT_E_UTRAN_PRIORITY 625
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_DEFAULT_E_UTRAN_PRIORITY_SIZE   3
#define CSN1_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_struct_THRESH_UTRAN_low 623
#define CSN1_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_struct_THRESH_UTRAN_low_SIZE   5
#define CSN1__3G_Early_Classmark_Sending_Restriction__3G_Early_Classmark_Sending_Restriction 586
#define CSN1__3G_Early_Classmark_Sending_Restriction__3G_Early_Classmark_Sending_Restriction_SIZE   0
#define CSN1_E_UTRAN_Parameters_Description_struct_E_UTRAN_Measurement_Parameters_Description 1095
#define CSN1_E_UTRAN_Parameters_Description_struct_E_UTRAN_Measurement_Parameters_Description_SIZE   0
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_DEFAULT_E_UTRAN_QRXLEVMIN 627
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_DEFAULT_E_UTRAN_QRXLEVMIN_SIZE   5
#define CSN1_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_struct_THRESH_UTRAN_high 622
#define CSN1_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_struct_THRESH_UTRAN_high_SIZE   5
#define CSN1_UTRAN_CSG_Cells_Reporting_Description_struct_UTRAN_CSG_FDD_REPORTING_THRESHOLD_2  68
#define CSN1_UTRAN_CSG_Cells_Reporting_Description_struct_UTRAN_CSG_FDD_REPORTING_THRESHOLD_2_SIZE   6
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_THRESHOLD  65
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_THRESHOLD  66
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_MULTIRAT_REPORTING 1099
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_MULTIRAT_REPORTING_SIZE   2
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_DEFAULT_THRESH_E_UTRAN_low 626
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_DEFAULT_THRESH_E_UTRAN_low_SIZE   5
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_E_UTRAN_Parameters_Description 1091
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_E_UTRAN_Parameters_Description_SIZE   0
#define CSN1_RTTI_Multiple_Downlink_Assignment_DC_struct_RTTI_DOWNLINK_PDCH_PAIR_ASSIGNMENT_DC 862
#define CSN1_RTTI_Multiple_Downlink_Assignment_DC_struct_RTTI_DOWNLINK_PDCH_PAIR_ASSIGNMENT_DC_SIZE   8
#define CSN1_RTTI_Multiple_Downlink_Assignment_SC_struct_RTTI_DOWNLINK_PDCH_PAIR_ASSIGNMENT_SC 865
#define CSN1_RTTI_Multiple_Downlink_Assignment_SC_struct_RTTI_DOWNLINK_PDCH_PAIR_ASSIGNMENT_SC_SIZE   4
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_THRESH_E_UTRAN_low_Q 404
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_THRESH_E_UTRAN_low_Q_SIZE   5
#define CSN1_E_UTRAN_CSG_Cells_Reporting_Description_struct_E_UTRAN_CSG_FDD_REPORTING_THRESHOLD 1126
#define CSN1_E_UTRAN_CSG_Cells_Reporting_Description_struct_E_UTRAN_CSG_FDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1_E_UTRAN_CSG_Cells_Reporting_Description_struct_E_UTRAN_CSG_TDD_REPORTING_THRESHOLD 1128
#define CSN1_E_UTRAN_CSG_Cells_Reporting_Description_struct_E_UTRAN_CSG_TDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1_E_UTRAN_Individual_Priority_Parameters_Description_struct_DEFAULT_E_UTRAN_PRIORITY 650
#define CSN1_E_UTRAN_Individual_Priority_Parameters_Description_struct_DEFAULT_E_UTRAN_PRIORITY_SIZE   3
#define CSN1_IRAT_Cell_Reselection_Information_struct_Priority_and_UTRAN_Parameters_Description 1144
#define CSN1_IRAT_Cell_Reselection_Information_struct_Priority_and_UTRAN_Parameters_Description_SIZE   0
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_THRESH_E_UTRAN_high_Q 403
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_THRESH_E_UTRAN_high_Q_SIZE   5
#define CSN1_Repeated_E_UTRAN_Measurement_Control_Parameters_struct_Measurement_Control_E_UTRAN 789
#define CSN1_Repeated_E_UTRAN_Measurement_Control_Parameters_struct_Measurement_Control_E_UTRAN_SIZE   1
#define CSN1_ETWS_Primary_Notification_struct_Total_No_Of_Segments_For_ETWS_Primary_Notification 1230
#define CSN1_ETWS_Primary_Notification_struct_Total_No_Of_Segments_For_ETWS_Primary_Notification_SIZE   4
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_THRESHOLD_2  59
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_THRESHOLD_2_SIZE   6
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_THRESHOLD_2  62
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_THRESHOLD_2_SIZE   6
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_E_UTRAN_Measurement_Parameters_Description 780
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_E_UTRAN_Measurement_Parameters_Description_SIZE   0
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_OFFSET 1102
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_OFFSET_SIZE   3
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_OFFSET 1105
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_OFFSET_SIZE   3
#define CSN1_Repeated_Individual_E_UTRAN_Priority_Parameters_Description_struct_E_UTRAN_PRIORITY 653
#define CSN1_Repeated_Individual_E_UTRAN_Priority_Parameters_Description_struct_E_UTRAN_PRIORITY_SIZE   3
#define CSN1_E_UTRAN_CSG_Cells_Reporting_Description_struct_E_UTRAN_CSG_FDD_REPORTING_THRESHOLD_2 1127
#define CSN1_E_UTRAN_CSG_Cells_Reporting_Description_struct_E_UTRAN_CSG_FDD_REPORTING_THRESHOLD_2_SIZE   6
#define CSN1_IRAT_Cell_Reselection_Information_struct_Priority_and_E_UTRAN_Parameters_Description 1145
#define CSN1_IRAT_Cell_Reselection_Information_struct_Priority_and_E_UTRAN_Parameters_Description_SIZE   0
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_E_UTRAN_FREQUENCY_INDEX 402
#define CSN1_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_E_UTRAN_FREQUENCY_INDEX_SIZE   3
#define CSN1__3G_Additional_Measurement_Parameters_Description_2_struct_FDD_REPORTING_THRESHOLD_2  54
#define CSN1__3G_Additional_Measurement_Parameters_Description_2_struct_FDD_REPORTING_THRESHOLD_2_SIZE   6
#define CSN1_E_UTRAN_Parameters_Description_struct_GPRS_E_UTRAN_Measurement_Parameters_Description 1096
#define CSN1_E_UTRAN_Parameters_Description_struct_GPRS_E_UTRAN_Measurement_Parameters_Description_SIZE   0
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_THRESHOLD 1100
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_THRESHOLD 1103
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_THRESHOLD_SIZE   3
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct__3G_Priority_Parameters_Description 1079
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct__3G_Priority_Parameters_Description_SIZE   0
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_MEASUREMENT_REPORT_OFFSET  58
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_MEASUREMENT_REPORT_OFFSET_SIZE   6
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_MEASUREMENT_REPORT_OFFSET  61
#define CSN1_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_MEASUREMENT_REPORT_OFFSET_SIZE   6
#define CSN1_Repeated_Individual_E_UTRAN_PP_with_extended_EARFCNs_Description_struct_EARFCN_extended 658
#define CSN1_Repeated_Individual_E_UTRAN_PP_with_extended_EARFCNs_Description_struct_EARFCN_extended_SIZE  18
#define CSN1__3G_Measurement_Control_Parameters_Description_struct_DEFAULT_Measurement_Control_UTRAN 773
#define CSN1__3G_Measurement_Control_Parameters_Description_struct_DEFAULT_Measurement_Control_UTRAN_SIZE   1
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_THRESHOLD_2 1101
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_FDD_REPORTING_THRESHOLD_2_SIZE   6
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_THRESHOLD_2 1104
#define CSN1_GPRS_E_UTRAN_Measurement_Parameters_Description_struct_E_UTRAN_TDD_REPORTING_THRESHOLD_2_SIZE   6
#define CSN1_Repeated_Individual_E_UTRAN_PP_with_extended_EARFCNs_Description_struct_E_UTRAN_PRIORITY 659
#define CSN1_Repeated_Individual_E_UTRAN_PP_with_extended_EARFCNs_Description_struct_E_UTRAN_PRIORITY_SIZE   3
#define CSN1_UTRAN_FDD_TDD_Description_struct_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority 619
#define CSN1_UTRAN_FDD_TDD_Description_struct_Repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_SIZE   0
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_Repeated_E_UTRAN_Not_Allowed_Cells 635
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_Repeated_E_UTRAN_Not_Allowed_Cells_SIZE   0
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_Repeated_E_UTRAN_PCID_to_TA_mapping 636
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_Repeated_E_UTRAN_PCID_to_TA_mapping_SIZE   0
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_E_UTRAN_Measurement_Control_Parameters_Description 785
#define CSN1_E_UTRAN_Parameters_Description_struct_RR_E_UTRAN_Measurement_Control_Parameters_Description_SIZE   0
#define CSN1_E_UTRAN_Measurement_Control_Parameters_Description_struct_DEFAULT_Measurement_Control_E_UTRAN 786
#define CSN1_E_UTRAN_Measurement_Control_Parameters_Description_struct_DEFAULT_Measurement_Control_E_UTRAN_SIZE   1
#define CSN1_Enhanced_Cell_Reselection_Parameters_IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters 401
#define CSN1_Enhanced_Cell_Reselection_Parameters_IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_SIZE   0
#define CSN1__3G_Supplementary_Parameters_Description_struct__3G_Measurement_Control_Parameters_Description 772
#define CSN1__3G_Supplementary_Parameters_Description_struct__3G_Measurement_Control_Parameters_Description_SIZE   0
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_Serving_Cell_Priority_Parameters_Description 1073
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_Serving_Cell_Priority_Parameters_Description_SIZE  15
#define CSN1__3G_Individual_Priority_Parameters_Description_struct_Repeated_Individual_UTRAN_Priority_Parameters 645
#define CSN1__3G_Individual_Priority_Parameters_Description_struct_Repeated_Individual_UTRAN_Priority_Parameters_SIZE   0
#define CSN1__3G_Measurement_Control_Parameters_Description_struct_Repeated_UTRAN_Measurement_Control_Parameters 774
#define CSN1__3G_Measurement_Control_Parameters_Description_struct_Repeated_UTRAN_Measurement_Control_Parameters_SIZE   0
#define CSN1_IRAT_Cell_Reselection_Information_struct_Priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN 1140
#define CSN1_IRAT_Cell_Reselection_Information_struct_Priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN_SIZE   0
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_Enhanced_Cell_Reselection_Parameters_Description 637
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_Enhanced_Cell_Reselection_Parameters_Description_SIZE   0
#define CSN1_IRAT_Cell_Reselection_Information_struct_Priority_and_E_UTRAN_Parameters_Description_for_the_Common_PLMN 1141
#define CSN1_IRAT_Cell_Reselection_Information_struct_Priority_and_E_UTRAN_Parameters_Description_for_the_Common_PLMN_SIZE   0
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority 628
#define CSN1_Priority_and_E_UTRAN_Parameters_Description_struct_37o_Repeated_E_UTRAN_Neighbour_Frequency_and_Priority_SIZE   0
#define CSN1_E_UTRAN_IPP_with_extended_EARFCNs_Description_struct_Repeated_Individual_E_UTRAN_PP_with_extended_EARFCNs 657
#define CSN1_E_UTRAN_IPP_with_extended_EARFCNs_Description_struct_Repeated_Individual_E_UTRAN_PP_with_extended_EARFCNs_SIZE   0
#define CSN1_E_UTRAN_Individual_Priority_Parameters_Description_struct_Repeated_Individual_E_UTRAN_Priority_Parameters 651
#define CSN1_E_UTRAN_Individual_Priority_Parameters_Description_struct_Repeated_Individual_E_UTRAN_Priority_Parameters_SIZE   0
#define CSN1_E_UTRAN_Measurement_Control_Parameters_Description_struct_Repeated_E_UTRAN_Measurement_Control_Parameters 787
#define CSN1_E_UTRAN_Measurement_Control_Parameters_Description_struct_Repeated_E_UTRAN_Measurement_Control_Parameters_SIZE   0


/* DEFINITIONS */
#define CSN1C_DEF_cell_barred            0
#define CSN1C_DEF_bit                    6
#define CSN1C_DEF_bit_string             8
#define CSN1C_DEF_spare_L               10
#define CSN1C_DEF_spare_bits            12
#define CSN1C_DEF_no_string             31
#define CSN1C_DEF_Compressed_Inter_RAT_HO_INFO_IND  32
#define CSN1C_DEF_Extension2            49
#define CSN1C_DEF_SI_CHANGE_ALT         50
#define CSN1C_DEF_SYSTEM_INFORMATION_TYPE_10ter  67
#define CSN1C_DEF_la_different          87
#define CSN1C_DEF_spare_bit            103
#define CSN1C_DEF_octet                105
#define CSN1C_DEF_spare_padding        107
#define CSN1C_DEF_padding_bits         123
#define CSN1C_DEF_zero_padding         131
#define CSN1C_DEF_Group_Channel_Description 147
#define CSN1C_DEF_DYNAMIC_ARFCN_MAPPING 189
#define CSN1C_DEF_Access_Technologies_Request_struct 206
#define CSN1C_DEF_IARRestOctets        226
#define CSN1C_DEF_NCELL_Report_struct  308
#define CSN1C_DEF_List_of_Emergency_information 321
#define CSN1C_DEF_Dynamic_Allocation_struct 355
#define CSN1C_DEF_Additional_PFCs_struct_UP 718
#define CSN1C_DEF_Additional_PFCs_struct_DN 743
#define CSN1C_DEF_RTD6_Struct          768
#define CSN1C_DEF_RTD12_Struct         781
#define CSN1C_DEF__3G_Additional_Measurement_Parameters_Description_2_struct 794
#define CSN1C_DEF_E_UTRAN_Measurement_Parameters_Description_struct 811
#define CSN1C_DEF_UTRAN_CSG_Cells_Reporting_Description_struct 1030
#define CSN1C_DEF_Optional_Power_Offset 1067
#define CSN1C_DEF_VGCSCipheringParameters 1084
#define CSN1C_DEF_A5_CM3_bits          1124
#define CSN1C_DEF_RFL_number_list_struct 1141
#define CSN1C_DEF_ARFCN_index_list_struct 1161
#define CSN1C_DEF_Packet_Timing_Advance_IE 1181
#define CSN1C_DEF_Power_Control_Parameters_IE 1218
#define CSN1C_DEF_TMGI_IE              1351
#define CSN1C_DEF_PCID_Group_IE        1378
#define CSN1C_DEF_PLMN_ID_struct       1442
#define CSN1C_DEF_GPRS_Power_Control_Parameters_IE 1451
#define CSN1C_DEF_VBS_VGCS_RECONFIGURE_BODY 1472
#define CSN1C_DEF_UPLINK_FREE_BODY     1521
#define CSN1C_DEF_VGCS_ADDITIONAL_INFORMATION_BODY 1578
#define CSN1C_DEF_VGCS_SMS_INFORMATION_BODY 1611
#define CSN1C_DEF_NOTIFY_APPLICATION_DATA_BODY 1719
#define CSN1C_DEF_Group_Call_information 1778
#define CSN1C_DEF_BA_List_Pref         1798
#define CSN1C_DEF_UTRANFreqList        1835
#define CSN1C_DEF_ChReqDesc2           1862
#define CSN1C_DEF_DTMInfoRestOctets    1999
#define CSN1C_DEF_DynamicARFCNMapping  2048
#define CSN1C_DEF_IAXRestOctets        2088
#define CSN1C_DEF_MultirateSpeechCfgIE 2095
#define CSN1C_DEF_P3RestOctets         2161
#define CSN1C_DEF_PacketChannelDescription 2318
#define CSN1C_DEF_Fixed_Allocation_struct 2391
#define CSN1C_DEF_RLC_Entity_Struct_UP 2545
#define CSN1C_DEF_RLC_Entity_Struct_DN 2580
#define CSN1C_DEF_Downlink_TBF_assignment_2_struct 2615
#define CSN1C_DEF_SI1RestOctets        2674
#define CSN1C_DEF_SI2bisRestOctets     2697
#define CSN1C_DEF_SI2terRestOctets     2706
#define CSN1C_DEF_UTRAN_FDD_Description_struct 2915
#define CSN1C_DEF_UTRAN_TDD_Description_struct 2975
#define CSN1C_DEF_Repeated_E_UTRAN_Not_Allowed_Cells_struct 3048
#define CSN1C_DEF_Repeated_E_UTRAN_PCID_to_TA_mapping_struct 3070
#define CSN1C_DEF__3G_CSG_Description_struct 3100
#define CSN1C_DEF_LSA_ID_information   3200
#define CSN1C_DEF_SI18RestOctet        3234
#define CSN1C_DEF_SI14RestOctets       3287
#define CSN1C_DEF_SI15RestOctets       3319
#define CSN1C_DEF_SI21RestOctets       3351
#define CSN1C_DEF_SI22RestOctets       3386
#define CSN1C_DEF__3GTargetCell        3542
#define CSN1C_DEF_SI10bis_Neighbour_Cell_Info 3635
#define CSN1C_DEF_RRClassmark3Value    3798
#define CSN1C_DEF_GPRS_Mobile_Allocation_IE 4486
#define CSN1C_DEF_MBMS_Sessions_List_IE 4566
#define CSN1C_DEF_Enhanced_Cell_Reselection_Parameters_IE 4600
#define CSN1C_DEF_UTRAN_CSG_Measurement_Report_IE 4693
#define CSN1C_DEF_NOTIFICATION_FACCH_BODY 4743
#define CSN1C_DEF_Enhanced_Measurement_report 4911
#define CSN1C_DEF_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY 5226
#define CSN1C_DEF_CellSelIndAfterReleaseTCHandSDCCH 5288
#define CSN1C_DEF_IARestOctets         5589
#define CSN1C_DEF_MeasurementResults   6859
#define CSN1C_DEF_List_of_Group_Call_NCH_information 7013
#define CSN1C_DEF_SI3RestOctet         7032
#define CSN1C_DEF_SI4_Rest_Octets_O    7229
#define CSN1C_DEF_SI4_Rest_Octets_S    7286
#define CSN1C_DEF_SI6RestOctet         7390
#define CSN1C_DEF_Priority_and_UTRAN_Parameters_Description_struct 7568
#define CSN1C_DEF_Priority_and_E_UTRAN_Parameters_Description_struct_37o 7777
#define CSN1C_DEF_SI10bis_Rest_Octets  7999
#define CSN1C_DEF_IndividualPriorities 8053
#define CSN1C_DEF_GPRS_Cell_Options_IE 8314
#define CSN1C_DEF_SYSTEM_INFORMATION_TYPE_10bis_BODY 8484
#define CSN1C_DEF_Measurement_information 8542
#define CSN1C_DEF_GPRSBCastInfo        10085
#define CSN1C_DEF_NTNRestOctets        10106
#define CSN1C_DEF_RRPktDownlinkAssi    10295
#define CSN1C_DEF_RRPacketDownlinkAssignmentType2 10897
#define CSN1C_DEF_SI4_Rest_Octets      11607
#define CSN1C_DEF_SI7_Rest_Octets      11648
#define CSN1C_DEF_SI8_Rest_Octets      11666
#define CSN1C_DEF_SI13RestOctets       11684
#define CSN1C_DEF_SI16RestOctet        11934
#define CSN1C_DEF_Frequency_Parameters_IE 11980
#define CSN1C_DEF_RRPacketUplinkAssignment 12115
#define CSN1C_DEF_SI2quaterRestOctets  13840
#define CSN1C_DEF_SI23RestOctets       15650
#define CSN1C_DEF_SI13altRestOctets    15758
#define CSN1C_DEF_IPARestOctets        15788
#define CSN1C_DEF_MBMS_Channel_Parameters_IE 16026
#define CSN1C_DEF_SYSTEM_INFORMATION_TYPE_10_BODY 16309
#define CSN1C_DEF_P1RestOctets         16539
#define CSN1C_DEF_P2RestOctets         17025
/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NOTIFICATION_FACCH_BODY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NOTIFICATION_FACCH_BODY (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFICATION_FACCH_BODY* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NOTIFICATION_FACCH_BODY (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFICATION_FACCH_BODY* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VBS_VGCS_RECONFIGURE_BODY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VBS_VGCS_RECONFIGURE_BODY (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VBS_VGCS_RECONFIGURE_BODY* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VBS_VGCS_RECONFIGURE_BODY (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VBS_VGCS_RECONFIGURE_BODY* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "UPLINK_FREE_BODY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UPLINK_FREE_BODY (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UPLINK_FREE_BODY* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UPLINK_FREE_BODY (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UPLINK_FREE_BODY* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VGCS_ADDITIONAL_INFORMATION_BODY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCS_ADDITIONAL_INFORMATION_BODY (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_ADDITIONAL_INFORMATION_BODY* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCS_ADDITIONAL_INFORMATION_BODY (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_ADDITIONAL_INFORMATION_BODY* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VGCS_SMS_INFORMATION_BODY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCS_SMS_INFORMATION_BODY (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_SMS_INFORMATION_BODY* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCS_SMS_INFORMATION_BODY (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_SMS_INFORMATION_BODY* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_10_BODY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_10_BODY (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10_BODY* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_10_BODY (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10_BODY* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_10bis_BODY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_10bis_BODY (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10bis_BODY* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_10bis_BODY (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10bis_BODY* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SYSTEM_INFORMATION_TYPE_10ter".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SYSTEM_INFORMATION_TYPE_10ter (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SYSTEM_INFORMATION_TYPE_10ter* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SYSTEM_INFORMATION_TYPE_10ter (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SYSTEM_INFORMATION_TYPE_10ter* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Measurement_information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Measurement_information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Measurement_information* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Measurement_information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Measurement_information* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Enhanced_Measurement_report".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Enhanced_Measurement_report (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Enhanced_Measurement_report* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Enhanced_Measurement_report (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Enhanced_Measurement_report* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VGCS_NEIGHBOUR_CELL_INFORMATION_BODY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCS_NEIGHBOUR_CELL_INFORMATION_BODY* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NOTIFY_APPLICATION_DATA_BODY".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NOTIFY_APPLICATION_DATA_BODY (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NOTIFY_APPLICATION_DATA_BODY* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NOTIFY_APPLICATION_DATA_BODY (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NOTIFY_APPLICATION_DATA_BODY* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Group_Call_information".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Group_Call_information (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Group_Call_information* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Group_Call_information (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Group_Call_information* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "BA_List_Pref".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_BA_List_Pref (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_BA_List_Pref* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_BA_List_Pref (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_BA_List_Pref* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "UTRANFreqList".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_UTRANFreqList (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_UTRANFreqList* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_UTRANFreqList (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_UTRANFreqList* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "CellSelIndAfterReleaseTCHandSDCCH".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_CellSelIndAfterReleaseTCHandSDCCH (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_CellSelIndAfterReleaseTCHandSDCCH* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_CellSelIndAfterReleaseTCHandSDCCH (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_CellSelIndAfterReleaseTCHandSDCCH* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "ChReqDesc2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_ChReqDesc2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_ChReqDesc2* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_ChReqDesc2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_ChReqDesc2* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DTMInfoRestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DTMInfoRestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DTMInfoRestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DTMInfoRestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DTMInfoRestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "DynamicARFCNMapping".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_DynamicARFCNMapping (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_DynamicARFCNMapping* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_DynamicARFCNMapping (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_DynamicARFCNMapping* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "GPRSBCastInfo".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_GPRSBCastInfo (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_GPRSBCastInfo* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_GPRSBCastInfo (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_GPRSBCastInfo* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IARestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IARestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IARestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IARestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IARestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IARRestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IARRestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IARRestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IARRestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IARRestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IAXRestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IAXRestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IAXRestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IAXRestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IAXRestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MeasurementResults".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MeasurementResults (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MeasurementResults* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MeasurementResults (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MeasurementResults* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NCELL_Report_struct".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NCELL_Report_struct (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NCELL_Report_struct* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NCELL_Report_struct (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NCELL_Report_struct* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "MultirateSpeechCfgIE".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_MultirateSpeechCfgIE (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_MultirateSpeechCfgIE* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_MultirateSpeechCfgIE (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_MultirateSpeechCfgIE* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "NTNRestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_NTNRestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_NTNRestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_NTNRestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_NTNRestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "P1RestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_P1RestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_P1RestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_P1RestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_P1RestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "P2RestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_P2RestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_P2RestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_P2RestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_P2RestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "P3RestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_P3RestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_P3RestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_P3RestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_P3RestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "PacketChannelDescription".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_PacketChannelDescription (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_PacketChannelDescription* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_PacketChannelDescription (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_PacketChannelDescription* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RRPacketUplinkAssignment".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RRPacketUplinkAssignment (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RRPacketUplinkAssignment* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RRPacketUplinkAssignment (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RRPacketUplinkAssignment* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Dynamic_Allocation_struct".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Dynamic_Allocation_struct (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Dynamic_Allocation_struct* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Dynamic_Allocation_struct (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Dynamic_Allocation_struct* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "Fixed_Allocation_struct".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_Fixed_Allocation_struct (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_Fixed_Allocation_struct* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_Fixed_Allocation_struct (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_Fixed_Allocation_struct* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RRPktDownlinkAssi".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RRPktDownlinkAssi (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RRPktDownlinkAssi* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RRPktDownlinkAssi (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RRPktDownlinkAssi* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RRPacketDownlinkAssignmentType2".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RRPacketDownlinkAssignmentType2 (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RRPacketDownlinkAssignmentType2* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RRPacketDownlinkAssignmentType2 (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RRPacketDownlinkAssignmentType2* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI1RestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI1RestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI1RestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI1RestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI1RestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI2bisRestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI2bisRestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI2bisRestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI2bisRestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI2bisRestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI2terRestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI2terRestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI2terRestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI2terRestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI2terRestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI2quaterRestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI2quaterRestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI2quaterRestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI2quaterRestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI2quaterRestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI3RestOctet".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI3RestOctet (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI3RestOctet* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI3RestOctet (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI3RestOctet* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI4_Rest_Octets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI4_Rest_Octets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI4_Rest_Octets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI4_Rest_Octets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI4_Rest_Octets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI7_Rest_Octets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI7_Rest_Octets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI7_Rest_Octets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI7_Rest_Octets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI7_Rest_Octets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI8_Rest_Octets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI8_Rest_Octets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI8_Rest_Octets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI8_Rest_Octets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI8_Rest_Octets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI6RestOctet".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI6RestOctet (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI6RestOctet* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI6RestOctet (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI6RestOctet* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI13RestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI13RestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI13RestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI13RestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI13RestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI_CHANGE_ALT".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI_CHANGE_ALT (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI_CHANGE_ALT* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI_CHANGE_ALT (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI_CHANGE_ALT* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI16RestOctet".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI16RestOctet (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI16RestOctet* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI16RestOctet (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI16RestOctet* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI18RestOctet".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI18RestOctet (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI18RestOctet* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI18RestOctet (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI18RestOctet* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI14RestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI14RestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI14RestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI14RestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI14RestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI15RestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI15RestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI15RestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI15RestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI15RestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI13altRestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI13altRestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI13altRestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI13altRestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI13altRestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI21RestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI21RestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI21RestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI21RestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI21RestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI22RestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI22RestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI22RestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI22RestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI22RestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI23RestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI23RestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI23RestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI23RestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI23RestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "VGCSCipheringParameters".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_VGCSCipheringParameters (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_VGCSCipheringParameters* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_VGCSCipheringParameters (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_VGCSCipheringParameters* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "_3GTargetCell".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c__3GTargetCell (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c__3GTargetCell* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c__3GTargetCell (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c__3GTargetCell* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "SI10bis_Rest_Octets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_SI10bis_Rest_Octets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_SI10bis_Rest_Octets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_SI10bis_Rest_Octets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_SI10bis_Rest_Octets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IndividualPriorities".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IndividualPriorities (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IndividualPriorities* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IndividualPriorities (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IndividualPriorities* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "IPARestOctets".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_IPARestOctets (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_IPARestOctets* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_IPARestOctets (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_IPARestOctets* ED_CONST Destin, ED_EXLONG Length));

/*----------------------------------------------------------------------------
	Encoding/decoding functions for "RRClassmark3Value".
	It returns number of bits used or <0 in case of error.
----------------------------------------------------------------------------*/
ED_EXPORT_CALL (ED_EXLONG, ENCODE_c_RRClassmark3Value (char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, const c_RRClassmark3Value* ED_CONST Source));

ED_EXPORT_CALL (ED_EXLONG, DECODE_c_RRClassmark3Value (const char* ED_CONST Buffer, ED_CONST ED_EXLONG BitOffset, c_RRClassmark3Value* ED_CONST Destin, ED_EXLONG Length));


#ifdef __cplusplus
	}
#endif
#endif

