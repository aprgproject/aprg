/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_GLOBAL/tags/GLOBAL_ENV_13_168/I_Interface/Global_Env/Definitions/Glo_bs.h $
* @version               $LastChangedRevision: 4690 $
* @date                  $LastChangedDate: 2018-03-22 17:13:06 +0800 (Thu, 22 Mar 2018) $
* @author                $Author: kotikang $
*
* Original author        <nn>
*
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

/*----------------------------------------------------------------------------
Nokia Networks/RAS                                          SW Module document
Helena SW
                    GLOBAL BASE STATION DEFINITIONS
                    -------------------------------
Revision history:

VERSION DATE/AUTHORS    COMMENT
0.0.193 07.02.2017/Juha Alaspaa Added FPFx and FSEx defines
0.0.192 27.01.2017/Juha Niemimaki 3DAAS BEAMER & AE defines modified
0.0.191 30.11.2016/Juha Niemimaki Added 3DAAS BEAMER & AE defines
0.0.190 01.02.2016/Damian Henke Added BTS_NID, VLAN, STREAMING IP  defines per RP000776-Q-b.
0.0.189 17.06.2014/Monisha Jain Added RROM defines per LTE1919-A-b and made the CPU defines hardware-agnostic.
0.0.188 29.04.2014/Monisha Jain Added NIDs for Sprint 3C hardware per LTE1919-A-b.
0.0.187 11.11.2013/Juhana Alaruikka Added CHIPx_CPUy definitions for 8 DSP cores.
0.0.186 07.11.2013/Chaitanya Khadilkar BTS-OAM Add define for new unit Id for Internal GPS
0.0.185 15.08.2013/RT-CC&S Update NID definitions.
0.0.182 11.07.2013/Mikko Rahkila added SSD for smartmodular update
0.0.183 27.06.2013/RT-CC&S Add define for FZM_K2_LINUX and FZM_K2_LINUX_NID.
0.0.182 10.06.2013/RT-CC&S Add define for FZM K2 Linux NID.
0.0.181 31.05.2013/Juhana Alaruikka Node ID definitions for SM3 updated with CHIP7 - CHIP9.
0.0.180 22.05.2013/RT-CC&S Update comments in code for LRC NID.
0.0.179 21.05.2013/RT-CC&S Updated defines for EMGRP1_NID
0.0.178 08.05.2013/RT-CC&S Updated bits assignment for LRC NID components (8/4/4)
0.0.177 19.04.2013/RT-CC&S Updated macro names for LRC/FZM NIDs per SACK document template requirements****** AWAITING EFS APPROVAL ********
0.0.176 18.04.2013/RT-CC&S Updated with UDP and UDPCP port used by LSP SysComGW****** AWAITING EFS APPROVAL ********
0.0.175 18.04.2013/RT-CC&S Updated with LRC/FZM NIDs ****** AWAITING EFS APPROVAL ********
0.0.174 28.02.2013/Juhana Alaruikka Added CHIP definitions for DSPs 8 and 9.
0.0.173 05.12.2012/Piotr Gajowiak added Node Ids for Sic communication with HDLC modems
0.0.172 26.11.2012/Piotr Sachnowski Added RF MAC addresses for CN5229
0.0.171 20.09.2012/Yang Xiaohui Modify some dual mode RRU IP
0.0.170 15.08.2012/Yang Xiaohui Add new OAM master IP and FR IP for Dual Mode
0.0.169 29.05.2012/Juhana Alaruikka Added CHIPX_CPU5 definitions.
0.0.168 17.04.2012/Jari Mattila Added MURKKU_ASIC id for FSM3
0.0.167 24.03.2012/Juha Pirttikangas Added BMU_FPGA id for FSM3
0.0.166 13.01.2012/Cai Yibin Added SYNC_OCXO and CLK_OCXO id for MicroREC
0.0.165 28.11.2011/Oleg Martos Added new DSP CPUs
0.0.164 08.07.2011/Juha Pirttikangas Added CCSSA_FPGA id for FSM3
0.0.163 22.06.2011/Stefan Guzik RAN2394-a. Fix problem with Filter Id for ESM.
0.0.162 14.04.2011/ Stefan Guzik LTE999,LTE977,LTE106-c, Added Id and Ip to RF and Filter connected to OptIf and remove old one
0.0.161 21.03.2011/KiT define FSM_FAN3 added for FSMr3
0.0.160 06.01.2011/Huijuan Zhu added shared IP addresses for Filter and remove some comments from FRx_y_z_FF_IP_ADDR and FRx_y_z_IP_ADDR
0.0.159 05.11.2010/Henna Vaarala Fixed FSM1_FCT_MCU, FSM2_FCT_MCU, FSM3_FCT_MCU definitions
0.0.158 02.11.2010/Henna Vaarala Added FSM1_FCT_MCU, FSM2_FCT_MCU, FSM3_FCT_MCU.
0.0.157 01.11.2010/Juha Niemimaki added CONVERTER_1 operation mode
0.0.156 24.09.2010/Jaroslaw Bober added shared IP addresses
0.0.155 21.09.2010/Henna Vaarala Added new node id definitions for SM3 (FSM1_FSP1_MCU, FSM1_FSP1_CHIP1 etc.)
0.0.154 04.03.2010/Maciej Narojczyk Added changes made by Roman Konieczny.
0.0.153 23.02.2010/Hannu Heikkinen Cleaned unnecessary out defines which does not belong to GLOBAL_ENV level.
0.0.152 04.02.2010/Roman Konieczny Added FRx_y_z antenna related definitions (RXs, TXs, FFs, TILTs, MHAs etc.) for RF chaining purposes
0.0.151 18.01.2010/Juhana Alaruikka Updated DSP CHIP and CPU numbers to support Nyquist.
0.0.150 10.11.2009/Jari-Pekka Tuikka. Added new FR, LTX and Filter defines to support FR module chaining
0.0.149 04.11.2009/Marcin Baran IP addresses for Medusa added
0.0.148 25.09.2009/Jaroslaw Bober Added fan to fangruop
0.0.147 04.06.2009/Teppo Kotikangas Added RX13-RX24 ids for FRs
0.0.146 01.06.2009/Hannu Lantto Added SV id area.
0.0.145 28.04.2009/Tomasz Antczak Added Faradays Chip IP adresses for FSM3.
0.0.144 27.03.2009/Hannu Lantto Added lte cabinet id = FLEXI_LTE_BTS.
0.0.143 18.03.2009/Mikolaj Szuta Added MAX_RACK_DSP_MODULE_PER_WSPF for inc. 17 and 18 starting from: WN60ENV_17.1-12 .
0.0.142 06.02.2009/Jari Piipponen Added FEC_FPGA_ALL and FYB_FPGA_ALL for inc 18 / WX2.0
0.0.141 02.02.2009/kotikang Added FR1_TX7 - FR1_TX12, FR2_TX7 - FR2_TX12 and FR3_TX7 - FR3_TX12
          Removed old unused MHA, TILT and combiner IDs.
0.0.140 23.01.2009/Jari Piipponen Added DCM_SYSTEM_MODULE_3 for inc 18 and LTE (WBTS_OPR_58462). Added MAC_PDU_DUMP_NID for LTE.
0.0.139 17.11.2008/heikkiha Added FSM2_FT, FSM3_FT, AXC1, DCT1, AXC1_IP_ADDR,
                            FSM2_FT_IP_ADDR, FSM3_FT_IP_ADDR, FAM1_IP_ADDR and DCT1_IP_ADDR.
0.0.138 06.10.2008/pviljama RAN1671 EUBB: moved defines MAX_NUM_OF_CONTROL_UNITS, MAX_NUM_OF_DSP_RESOURCES and MAX_DSP_RESOURCES_PER_CONTROL_UNIT
                            to WNxxENV \BsEnv\Definitons\DOpenIUBCommonDefs.h, starting from WN50ENV_12_20 and WN60ENV_16_3.
0.0.137 22.08.2008/pviljama RAN1671 EUBB: changed the define MAX_NUM_OF_CONTROL_UNITS from 8 to 9.
0.0.136 18.09.2008/MartKall Added FYR1_LTX, FYR2_LTX and FYR3_LTX.
0.0.135 12.09.2008/Roman Bryling Added SOAP_ADET_SERVER_PORT, SOAP_MODULE_SERVER_PORT - changes needed by FUM
0.0.134 07.08.2008/heikkiha Added FAM1, DCM_SYSTEM_MODULE_1, DCM_SYSTEM_MODULE_2.
0.0.133 07.08.2008/heikkiha Added BOFU_FPGA
0.0.132 24.06.2008/MartKall Added RF module's FAN1, FAN2 and FANGROUP id's for both Flexi WCDMA and WiMAX.
0.0.131 11.03.2008/leipyora Added RX9-12, TX5-6, modified TX ids. MHA and TILT values shifted for 0xA to get linearic values for RXs and TXs.
                            FR1_FA_5, FR2_FA_5, FR1_FA_5 added
0.0.130 10.03.2008/Kotikang Added FR1_FF3, FR2_FF3 and FR3_FF3
0.0.129 25.02.2008/jaakvanh Added RANSU_FPGA, FEC1_FPGA, FEC2_FPGA, FEC3_FPGA for FYBA.
0.0.128 17.01.2008/Kotikang Added unit id definition for Remote Azimuth Steering devices
0.0.127 03.01.2008/Kotikang Added FRx_ANTy definitions and changed FYRx_ANTLy definitions
0.0.126 01.11.2007/HiMa Added MAX_NUM_OF_RADIO_RESOURCES
0.0.125 27.08.2007/ipelli removed #define TCOM_MCU.
0.0.124 04.06.2007/Kotikang #define FYR1 FR1 changed to FYR1 FR1_MODULE, and same change for FYR2 and FYR3.
0.0.123 01.06.2007/MartKall Added FYS1_FYB2 and FYS1_FYB3 objects (and _BB1, _BB2, _BB3)
0.0.122 17.04.2007/Kotikang Added FYR antenna line objects
0.0.121 12.04.2007/MSalonpa Added FYR1_TX2, FYR2_TX2 and FYR3_TX2
0.0.120 12.03.2007/Kotikang Added wimax cabinet id = FLEXI_WIMAX_BTS. Added FYR RP3-01 object IDs
0.0.119 21.02.2007/HiMa Added MAX_NUM_OF_CONTROL_UNITS, MAX_NUM_OF_DSP_RESOURCES and MAX_DSP_RESOURCES_PER_CONTROL_UNIT
0.0.118 07.02.2007/Kotikang Added MHA, TILT and Combiner IDs
0.0.117 07.02.2007/AKoistinen Added definition for GPS
0.0.117 29.01.2007/Kotikang Added id for flexi I-HSPA Adapter
0.0.116 21.12.2006/Kotikang Added virtual unit id's needed by BTSOM (wbts4.1 and wx1.0)
0.0.115 13.10.2006/JAlaruikka Added CHIP_ALL and CPU_ALL.
0.0.114 11.10.2006/JMoberg  Added FR1_MODULE, FR2_MODULE, FR3_MODULE
0.0.113 28.09.2006/JAlaruikka Added IP and MAC addresses for Faradays, and ports for FSPB
0.0.112 30.06.2006/SKarjalainen Added virtual unit ids max and min values for passive units
0.0.111 31.05.2006/MVaarala Added virtual unit ids for TILTs: FR1_TILT_1 ... FR3_TILT_3
                            and SameBand Combiners: FR1_FA_1 ... FR3_FA_3
0.0.110 21.04.2006/JaVa UNKNOWN_SYSTEM_MODULE value changed from 0xBEEF to 0xFF.
0.0.109 13.03.2006/JaVa Added System and Extension module mode definitions: MASTER_SYSTEM_MODULE, EXTENSION_SYSTEM_MODULE_1,
                        EXTENSION_SYSTEM_MODULE_2, UNKNOWN_SYSTEM_MODULE and MODULE_MODE_NOT_SET.
0.0.108 10.03.2006 / MartKall Added Licence Management server (LICM_SERVER_PORT) and client (LICM_CLIENT_PORT) ports.
0.0.107 2.3.2006 / JMoberg PR 22481ES09P. Added virtual unit ids for MHAs: FR1_MHA_1 ... FR3_MHA_4
0.0.106 4.1.2006 / JMoberg Added virtual unit ids for FSM3_OIC1...5
0.0.105 30.12.2005/JMoberg Added virtual unit ids for FSM1_OIC1...5 and FSM2_OIC1...5
0.0.104 28.12.2005/JTuik Updated FSM1_FT and FSM_FT to 0xE1 and MAX_UNITS to 0xE1
0.0.103 21.12.2005/JTuik MAX_UNITS updated to 0xE0
0.0.102 19.12.2005/JTuik Updated FR1_FF1...FR3_FF2 values
0.0.101 13.12.2005/JaVa Corrected FSM1, FSM2 and FSM3 values.  Added virtual unit ID's.
0.0.100 12.12.2005/IPelli PR 20809ES09P, Added #define RNC_NBAP 0x57
0.0.99  14.11.2005/JaVa Added boards FSM1_FCM, FSM2_FCM, FSM3_FCM, FSM1_FSP1, FSM1_FSP2, FSM1_FSP3, FSM2_FSP1, FSM2_FSP2, FSM2_FSP3,
                        FSM3_FSP1, FSM3_FSP2, FSM3_FSP3 and subracks FSM1, FSM2, FSM3 and FSM_UNKNOWN and IP's for
                        System/Extension Module + corresponding FSP's.
0.0.98  21.09.2005/HaH  Added FLEXI_SUBNETMASK definition.
0.0.97  25.08.2005/jmoberg  Definitions of FR1  FR2 and FR3 added back and changed comments
                            from FR1 FR2 and FR3 Flexi RF Mofule to Linear Transceiver because
                            change would affect to EFS documents.
0.0.96  04.08.2005/jmoberg  Removed definitions of FR1, FR2, and FR3.
0.0.95  14.06.2005/HaH  Added L2X.
0.0.94  25.05.2005/HaH  Added Radio module & STuF IP/MAC addresses. Added FLEXI_BTS cabinet type and
                        changed FSM_FT IP address according to the IP Management EFS.
0.0.93  25.04.2005/HaH  Changed FSM_FT and FSM_FT_MCU defines into different than AXU correspondents,
                        as defined in the HW Management EFS.
0.0.92  14.02.2005/TeK  Added timeouts for communications (TIMEOUT_SIGNALING_DEFAULT,
                                                TIMEOUT_MANAGEMENT_INTRA_CPU_DEFAULT and TIMEOUT_MANAGEMENT_INTER_CPU_DEFAULT)
                                                from WCDMA BTS SW Architecture Specification.
0.0.91  21.01.2005/PeJ  Added MUKSU_ASIC, OIC_FPGA, CASA2_FPGA.
                                                Modified some Flexi FSM based definitions.
0.0.90  19.01.2005/HaH  Changed FSM_FT definition value to AXU correspondent, instead of own value. Added
                        FSM_FSP1, FSM_FSP2 and FSM_FSP3 boards. Added comment to CTRL_MCU CPU definition
                        that it is used also in some Flexi boards, e.g. LTX. Added FSP_MCU and FSM_FT_MCU
                        CPU definitions. Added IP address, MAC address and UDP port number definitions for Flexi units.
0.0.89  10.01.2005/tovayryn Added ULTRASITE cabinet and WEH / WPA unit definitions for extended BTS cabinets
0.0.88  09.11.2004/MaMe Added MAX_NUM_OF_TX_RESOURCES and MAX_NUM_OF_RX_RESOURCES
0.0.87  12.11.2004/HaH  Added Flexi BTS related definitions.
0.0.86  29.09.2004/sikarjal new defines for CN264 #define WOC_10 0xC0, #define WOC_20 0xC1,
                   #define WOC_30 0xC2, #define WPD_10 0xC3, #define WPD_20 0xC4 and #define WPD_30 0xC5.
                   Removed define for WPD and WOC
0.0.85  06.08.2004/karjsim added #define WIA 0xBF, #define WOC 0xC0 and #define WPD 0xC1
0.0.84  29.6.2004/NPu   Added definitions for API_BTS_LOG_TCP_PORT and API_TESTER_INTERFACE_TCP_PORT
0.0.83  19.3.2004/AnKu Included new cabinet type CS3000 (Connect Site 3000) and two new sub units (WMC_DSAX and WMC_UMAX) for WMCM12 unit.
0.0.82  03.12.2003/MiRu Added #define WOU_MCU 0x28 (AIR Support)
0.0.81  05.11.2003/jussheik Removed unnecessary #define WPA_12  0x9a id
                            Redefinition fro MHA_30 from 0x9C to 0xDA
                            MAX_UNITS updated from 0xD6 to 0xDA
0.0.80  30.10.2003/TKahila  Removed unnecessary #define WTR_12  0x99 id (accepted by Heikki Komulainen)
0.0.79  21.10.2003/MiRu Added AIR board (WOM, WRU) definitions and MAX_UNITS increased (with 20)
0.0.78  06.06.2003/IkGa Added MAX_OF_LOCAL_CELL_GROUPS_PER_WAM
0.0.77  17.04.2002/AnKu New definitions for Cost Reduction Optima Compact (Doris indoor and outdoor):
                        #define DORIS_INDOOR 0xC, #define DORIS_OUTDOOR 0xD
                        #define MAX_UNITS 0xC2 (increased by four)
                        #define RF_FAN_LEFT 0x99, #define RF_FAN_RIGHT 0x9A, #define BB_FAN 0x9B, #define WFD 0x9C
                        #define WPA_WFA3 0x37, #define WPA_WFA4 0x38, #define WPA_WFA5 0x39, #define WPA_WFA6 0x3A
                        #define HEX_FAN 0x3B, #define WPA_WFA_GR1 0x75, #define WPA_WFA_GR2 0x76, #define WPA_WFA_GR3 0x77
0.0.76  09.08.2002/TuK  Redefinition for BTU_31
0.0.75  04.06.2002/JaTP WSP_xx IP address and MAC address definitions added.
                        WSP_MCU ID value changed.
0.0.74  25.04.2002/RGR  changed MAX_NUM_OF_WAMS to value 6
0.0.73  30 01 2002/MiRu BTU ID's added and MAX_UNITS number increased
0.0.72  16.01.2002/SaMe Fan names and ID's changed when the control board is WHX
0.0.71  03.01.2002/SaMe Definition NOZOMI_OUTDOOR removed
0.0.70  11.12.2001/MiRu Redifinitions for MHA-units corrected and MAX_UNITS number increased.
0.0.69  05.11.2001/JaTP Definitions BIST_SERVER_PORT and BIST_CLIENT_PORT added.
0.0.68  17.10.2001/SaMe MAX_UNITS number increased, WPA_12 and WTR_12 units added
0.0.67  09.10.2001/PeJ  DSP_BROWSER_TCP_PORT changed to TASSU_BROWSER_TCP_PORT
                        and defined API_BROWSER_TCP_PORT
0.0.66  05.10.2001/SaMe MHA's added for WAF_12, WAF_22 and WAF_32
0.0.65  26.09.2001/OMa  WSC 0x84 removed
0.0.64  12.09.2001/PeJ  Added reserved WAM CTRL_MCU UDP port numbers (WAM - WAM) as comment
0.0.63  10.09.2001/Ojar Added RACK_NOT_SET definition
0.0.62  27.08.2001/OMa  Added TR_WFA_EXT definition
0.0.61  24.08.2001/OMa  Removed double mentioning of adding BB_WFA_EXT in revision history,
                        removed WIC_22 definition, since WIC_20 is used for that purpose,
                        plus some corrections in revision history.
0.0.60  09.08.2001/SaMe WTR_WMP_WFAS added TRIPLE mode cabinet fans. Also WHX_WFA1 and WHX_WFA2
                        added for WHX
0.0.59  08.05.2001/OMa  BB_WFA_EXT units added and MAX_UNITS changed from 0x95 to 0x97.
0.0.58  18.04.2001/SaMe definition RESET_ENABLE added
0.0.57  10.04.2001/PaHu Added Max number of WTR in subrack
0.0.56  10.04.2001/KiT  Name of WCC changed to WID
0.0.55  30.03.2001/KiT  WSM_TR, WPS_TR, WIC_31, WAF_22 and WAF_32 units added and
                        MAX_UNITS changed from 0x91 to 0x95.
0.0.54  16.03.2001/KiT  Type of cabinet names have changed. DSC_ASIC definition modified.
0.0.53  15.03.2001/JaTP Loop mode definitions added
0.0.52  26.02.2001/KiT  Number of MAX_UNITS changed, units WAF_22 and WAF_32
                        removed, WIC_11 added
0.0.51  22.02.2001/PeJ  Added RNC_SUBNETMASK
0.0.50  21.02.2001/PaHu Added DSP module and Max number of local cells a WPA unit definitions
0.0.49  18.01.2001/Kit  TRIPLE_MODE_INDOOR and TRIPLE_MODE_OUTDOOR definitions added
0.0.48  18.01.2001/PaHu Edited Max number of WAM in subrack
0.0.47  12.01.2001/PaHu Added Max number of subrack, Max number of WAM in subrack, Max number of WSP in subrack
                        and Max number of DSP module in WSP
0.0.46  10.01.2001/PeJ  Fixed TCP port numbers for sWPA
0.0.45  20.12.2000/KiT  WMC_WSC and WMC_WSM units added
0.0.44  19.12.2000/KiT  WMC unit added and number of MAX_UNITS changed
0.0.43  18.12.2000/KiT  WIB unit added and number of MAX_UNITS changed
0.0.42  15.12.2000/KiT  NOZOMI_INDOOR and NOZOMI_OUTDOOR versions added
0.0.41  27.11.2000/KiT  WSC_10, WSC_20 and WCI unit added. MAX_UNITS changed.
0.0.40  22.11.2000/KiT  Changes the types of cabinets
0.0.39  21.11.2000/KiT  Added number for OPTIMA Secondary cabinets WPS_EXT (0x8B)
                        and changed amount of MAX_UNITS
0.0.38  16.11.2000/KiT  WAF_12, WAF_22 and WAF_32 definitions added for OPTIMA cabinet
                        and number of MAX_UNITS changed
0.0.37  14.11.2000/PaHu Added local cell definitions and modofication to Max number of AAL2TP's per WAM unit
0.0.36  10.10.2000/JaTP ATM3_MCU_AIF_ADDR definition added
0.0.35  06.10.2000/KiT  Types of cabinets added
0.0.34  30.10.2000/PaHu Added number of ATM MCUs (excluding ATMHOST)
0.0.33  24.10.2000/PaHu Added MHA units
0.0.32  03.10.2000/PaHu Added BB_SUBRACK_ALL and WTR_ALL
0.0.31  26.09.2000/KiT  WPA_WFA changed to WPA_WFA_ALL
0.0.30  06.09.2000/KiT  MAX_NUM_OF_TEMP_SENSORS changed
0.0.29  06.09.2000/KiT  BB_WFA_10, BB_WFA_20 and BB_WFA_30 added. MAX_UNITS
                        changed to 0x87
0.0.28  28.08.2000/JaTP CPU definitions modified
0.0.27  24.08.2000/KiT  MHA1, MHA2, PORT0, PORT1 and RESET removed
0.0.26  22.08.2000/SaMe /SaMe Removed version 0.0.24 and 0.0.23 modifications
0.0.25  22.08.2000/PaHu Added constants 'max number of AAL2TP's per WAM unit'
                        and 'maximum number of carrier frequencies'
                  /JaTP Subrack definitions for DSC-bus added
0.0.24  17.08.2000/SaMe WMP IP, MAC adresses and Port numbers for TCP/UDP
0.0.23  15.08.2000/SaMe WMP definitions added
0.0.22  30.06.2000/SaMe Two GENIO reset register outputs added as CPU's
0.0.21  28.06.2000/KiT  WAM_10 IP-address corrected
0.0.20  26.06.2000/KiT  Address for LNA1 and LNA2 added
0.0.19  21.06.2000/KiT  Number of MAX_UNITS changed bigger
0.0.18  19.06.2000/KiT  Passive unit names and some MCU defines changed
0.0.17  10.05.2000/KiT  WSM definitions changed and WPA_WFA passive unit addded
0.0.16  05.05.2000/TaP  Added WAM_ALL definition
0.0.15  26.04.2000/TaP  Updated MAX_UNITS
0.0.14  25.04.2000/TaP  Added literal AXU_UDP_PORT
0.0.13  18.04.2000/PaHu Added literals of max number of units WAM, WSP, WTR, WPA and WSM
0.0.12  18.04.2000/PeJ  Added literals BOARD_ANY, CPU_ANY, INVALID_BOARD, INVALID_CPU
0.0.11  10.04.2000/PeJ  Added PVCS header-note
0.0.10  06.04.2000/JaTP DSC_ASIC_AIF_ADDR added
0.0.9   03.04.2000/JaTP Board numbers rearranged, AXU and RNC added
0.0.8   22.03.2000/KiT  Some I2C device literals moved from "cpu" to "board"
0.0.7   20.03.2000/TaP  Added TCP port number literal for subcontracetd WPA
                        Added UDP port number literals for WAMs
0.0.6   29.02.2000/PeJ  Added TCP port number literal for DSP Browser
0.0.5   17.02.2000/TaP  MAX_CPUS added, MAX_UNITS nro changed
0.0.4   28.01.2000/JaTP Board and CPU DSC/AIF-bus addresses added
0.0.3   28.01.2000/TaP  Board and CPU numbers rearranged
0.0.2   25.01.2000/PeJ  Target environment flags removed
0.0.1   24.01.2000/TaP  First draft

*/

#ifndef _GLO_BS_H
#define _GLO_BS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Types of cabinets */
#define SUPREME_INDOOR                 0x1
#define SUPREME_OUTDOOR                0x2
#define OPTIMA_INDOOR                  0x3
#define OPTIMA_OUTDOOR                 0x4
#define TRIPLE_MODE_INDOOR             0x5
#define TRIPLE_MODE_OUTDOOR            0x6

#define OPTIMA_COMPACT_INDOOR_IBBU     0x7
#define OPTIMA_COMPACT_INDOOR_RF_EXT   0x8

#define OPTIMA_COMPACT_OUTDOOR_IBBU    0x9
#define OPTIMA_COMPACT_OUTDOOR_RF_EXT  0xA

#define NOZOMI_INDOOR                  0xB

#define DORIS_INDOOR                   0xC
#define DORIS_OUTDOOR                  0xD

#define CS3000                         0xE

#define ULTRASITE_INDOOR               0xF
#define ULTRASITE_OUTDOOR              0x10

#define FLEXI_BTS                      0x11
#define FLEXI_WIMAX_BTS                0x12
#define FLEXI_LTE_BTS                  0x13


/* Literals for boards and CPU amounts */
#define MAX_UNITS                 0xE1  /* Biggest number of units (boards) */
#define MAX_CPUS                  0x40  /* Biggest number of CPUs */
#define MAX_NUM_OF_TEMP_SENSORS   12    /* Number of expected temperature sensors */
#define MAX_NUM_OF_FANS           13    /* Number of expected FANs */
#define MAX_POLL_OF_UNITS         37    /* Number of expected units to be polled */

/* Value of unknown board ID */
#define BOARD_ANY                 0xFF

/* Value of unknown cpu ID */
#define CPU_ANY                   0xFF

/* Value for undefined board */
#define INVALID_BOARD             0

/* Value for undefined cpu */
#define INVALID_CPU               0

/* Number of WAM units */
#define MAX_NUM_OF_WAMS           6

/* Number of WSP units */
#define MAX_NUM_OF_WSPS           0x12

/* Number of WTR units */
#define MAX_NUM_OF_WTRS           0x06

/* Number of WPA units */
#define MAX_NUM_OF_WPAS           0x06

/* Number of WSM units */
#define MAX_NUM_OF_WSMS            0x03

/* Number of Trx modules per WTR unit */
#define MAX_NUM_OF_TRX_PER_WTR    2

/* Number of TrxModules per BTS*/
#define MAX_NUM_OF_TRXS            12

/* Number of local cells */
#define MAX_NUM_OF_LOCAL_CELLS    24

/* Max number of AAL2TP's per WAM unit*/
#define MAX_NUM_OF_AAL2TP_PER_WAM 3

/* Number of ATM MCUs (excluding ATMHOST). */
#define MAX_NUM_OF_ATM_MCUS   3

/* Maximum number of carrier frequencies that can be given by LMT*/
#define MAX_NUM_OF_CARRIER_CANDIDATES 8

/* Max number of carrier resources */
#define MAX_NUM_OF_TX_RESOURCES  48
#define MAX_NUM_OF_RX_RESOURCES  48
#define MAX_SIZE_OF_CR_ID  16

/* Max number of local cells a WSM unit can be shared with */
#define MAX_NUM_OF_CELLS_ASSOCIATED_TO_WSM 6

/* Value for undefined local cell resource ID */
#define UNDEFINED_LCR_ID 0xFFFFFFFF

/* Max number of subrack*/
#define MAX_SUBRACK  3

/* Max number of WAM in subrack*/
#define MAX_WAM_PER_SUBRACK  MAX_NUM_OF_WAMS/MAX_SUBRACK

/* Max number of WSP in subrack*/
#define MAX_WSP_PER_SUBRACK 6

/* Max number of DSP module in WSP*/
#define MAX_DSP_MODULE_PER_WSP 4

/* Max number of DSP module in WSPF (excluding the CODEC) */
#define MAX_RACK_DSP_MODULE_PER_WSPF 6

/*DSP modules*/
#define DSP_MODULE_1  0x01 /* WSP RAKE1-CODEC1 pair */
#define DSP_MODULE_2  0x02 /* WSP RAKE2-CODEC2 pair */
#define DSP_MODULE_3  0x03 /* WSP RAKE3-CODEC3 pair */
#define DSP_MODULE_4  0x04 /* WSP RAKE4-CODEC4 pair*/

/* Max number of local cells a WPA unit can be shared with */
#define MAX_NUM_OF_CELLS_ASSOCIATED_TO_WPA 2

/*Max number of WTR in subrack*/
#define MAX_WTR_PER_SUBRACK  (MAX_NUM_OF_WTRS/MAX_SUBRACK)
#define RACK_NOT_SET        0xffffffff

#define MAX_NUM_OF_POOLS 4

/* Number of local cells groups in each WAM */
#define MAX_OF_LOCAL_CELL_GROUPS_PER_WAM 2

/* Max number of radio resources for a cell */
#define MAX_NUM_OF_RADIO_RESOURCES 8

/* Number of DL-PHY entity for Beam Forming */
#define MAX_NUM_OF_DL_PHY_ENT_IN_BF  4
/* Number of UL PUSCH entity for Beam Forming */
#define MAX_NUM_OF_UL_PUSCH_ENT_IN_BF   4

/******************************************************************************/
/* Subrack's logical name definitions.                                       */
/*                                                                           */

#define BB_SUBRACK_1    0x0
#define BB_SUBRACK_2    0x1
#define BB_SUBRACK_3    0x2
#define BB_SUBRACK_ALL  0x1F

/*****************************************************************************/
/* Flexi BTS module mode definition.                                         */
/*                                                                           */
/* These values are used in FlexiBTS to detect System modules mode.          */
/* Flash memory contains master mode information and RPRAM contains extension*/
/* mode information.                                                         */

#define MODULE_MODE_NOT_SET         0x0     /* Mode is not set */
#define MASTER_SYSTEM_MODULE        0x1     /* Master mode system module */
#define EXTENSION_SYSTEM_MODULE_1   0x2     /* Extension mode system module 1 */
#define EXTENSION_SYSTEM_MODULE_2   0x4     /* Extension mode system module 2 */
#define DCM_SYSTEM_MODULE_1         0x5     /* LTE DoCoMo system module 1 */
#define DCM_SYSTEM_MODULE_2         0x6     /* LTE DoCoMo system module 2 */
#define DCM_SYSTEM_MODULE_3         0x7     /* LTE DoCoMo system module 3 */

#define CONVERTER_1                 0x8     /* TD-LTE 4 OptIF support (LTE545) */

#define UNKNOWN_SYSTEM_MODULE       0xFF    /* Mode could not be detected. */

/*****************************************************************************/
/* Board's logical name definitions.                                         */
/*                                                                           */
/* WSP and WAM board's numbers maps to physical addresses for DSC-bus.       */
/* Address is 8 bit wide, first 4 bits (MSB) is BSA address and second 4     */
/* bits (LSB) is BNA address.                                                */

/* DSC-ASIC is sub-node 0 at every DSC-BUS unit and we have agreed that 4 LSB
   bits have to be zeroes because some SWs use this definition as an address
   but INVALID_CPU is also 0x0 and that's why we have defined it 0xf0 */
#define DSC_ASIC 0xf0


/* WSP boards */
#define WSP_10  0x12    /* Rack 1, Wideband Signal Processor 0 */
#define WSP_11  0x13    /* Rack 1, Wideband Signal Processor 1 */
#define WSP_12  0x14    /* Rack 1, Wideband Signal Processor 2 */
#define WSP_13  0x15    /* Rack 1, Wideband Signal Processor 3 */
#define WSP_14  0x16    /* Rack 1, Wideband Signal Processor 4 */
#define WSP_15  0x17    /* Rack 1, Wideband Signal Processor 5 */
#define WSP_20  0x22    /* Rack 2, Wideband Signal Processor 0 */
#define WSP_21  0x23    /* Rack 2, Wideband Signal Processor 1 */
#define WSP_22  0x24    /* Rack 2, Wideband Signal Processor 2 */
#define WSP_23  0x25    /* Rack 2, Wideband Signal Processor 3 */
#define WSP_24  0x26    /* Rack 2, Wideband Signal Processor 4 */
#define WSP_25  0x27    /* Rack 2, Wideband Signal Processor 5 */
#define WSP_30  0x32    /* Rack 3, Wideband Signal Processor 0 */
#define WSP_31  0x33    /* Rack 3, Wideband Signal Processor 1 */
#define WSP_32  0x34    /* Rack 3, Wideband Signal Processor 2 */
#define WSP_33  0x35    /* Rack 3, Wideband Signal Processor 3 */
#define WSP_34  0x36    /* Rack 3, Wideband Signal Processor 4 */
#define WSP_35  0x37    /* Rack 3, Wideband Signal Processor 5 */

/* WAM boards */
#define WAM_10  0x10    /* Rack 1, Wideband Application Manager 0 */
#define WAM_11  0x11    /* Rack 1, Wideband Application Manager 1 */
#define WAM_20  0x20    /* Rack 2, Wideband Application Manager 0 */
#define WAM_21  0x21    /* Rack 2, Wideband Application Manager 1 */
#define WAM_30  0x30    /* Rack 3, Wideband Application Manager 0 */
#define WAM_31  0x31    /* Rack 3, Wideband Application Manager 1 */
#define WAM_ALL 0x1F    /* All Wideband Application Manager */


/* WTR boards */
#define WTR_10  0x40    /* Rack 1, Wideband Transmitter and Receiver 0 */
#define WTR_11  0x41    /* Rack 1, Wideband Transmitter and Receiver 1 */
#define WTR_20  0x42    /* Rack 2, Wideband Transmitter and Receiver 0 */
#define WTR_21  0x43    /* Rack 2, Wideband Transmitter and Receiver 1 */
#define WTR_30  0x44    /* Rack 3, Wideband Transmitter and Receiver 0 */
#define WTR_31  0x45    /* Rack 3, Wideband Transmitter and Receiver 1 */
#define WTR_ALL 0x1F    /* All Wideband Transmitter and Receiver */

/* WPA boards */
#define WPA_10  0x50    /* Rack 1, Wideband Power Amplifier 0 */
#define WPA_11  0x51    /* Rack 1, Wideband Power Amplifier 1 */
#define WPA_20  0x52    /* Rack 2, Wideband Power Amplifier 0 */
#define WPA_21  0x53    /* Rack 2, Wideband Power Amplifier 1 */
#define WPA_30  0x54    /* Rack 3, Wideband Power Amplifier 0 */
#define WPA_31  0x55    /* Rack 3, Wideband Power Amplifier 1 */
#define WPA_12  0x65    /* Rack 1, Wideband Power Amplifier 2 */
#define WPA_13  0x66    /* Rack 1, Wideband Power Amplifier 3 */
#define WPA_22  0x67    /* Rack 2, Wideband Power Amplifier 2 */
#define WPA_23  0x68    /* Rack 2, Wideband Power Amplifier 3 */
#define WPA_32  0x69    /* Rack 3, Wideband Power Amplifier 2 */
#define WPA_33  0x6A    /* Rack 3, Wideband Power Amplifier 3 */

/* WOM boards */
#define WOM_10  0xC6    /* Rack 1, Wideband Optical Module */
#define WOM_20  0xC7    /* Rack 2, Wideband Optical Module */
#define WOM_30  0xC8    /* Rack 3, Wideband Optical Module */
#define WOM_40  0xD9    /* Rack 4, Wideband Optical Module, MetroAIR */

/* WRU boards */
#define WRU_11  0xC9    /* Rack 1, Wideband Remote Unit for WOM_10 */
#define WRU_12  0xCA    /* Rack 1, Wideband Remote Unit for WOM_10 */
#define WRU_13  0xCB    /* Rack 2, Wideband Remote Unit for WOM_10 */
#define WRU_14  0xCC    /* Rack 2, Wideband Remote Unit for WOM_10 */
#define WRU_21  0xCD    /* Rack 3, Wideband Remote Unit for WOM_20 */
#define WRU_22  0xCE    /* Rack 3, Wideband Remote Unit for WOM_20 */
#define WRU_23  0xCF    /* Rack 1, Wideband Remote Unit for WOM_20 */
#define WRU_24  0xD0    /* Rack 1, Wideband Remote Unit for WOM_20 */
#define WRU_31  0xD1    /* Rack 1, Wideband Remote Unit for WOM_30 */
#define WRU_32  0xD2    /* Rack 2, Wideband Remote Unit for WOM_30 */
#define WRU_33  0xD3    /* Rack 2, Wideband Remote Unit for WOM_30 */
#define WRU_34  0xD4    /* Rack 3, Wideband Remote Unit for WOM_30 */
#define WRU_41  0xD5    /* Rack 3, Wideband Remote Unit for WOM_40, MetroAIR */
#define WRU_42  0xD6    /* Rack 4, Wideband Remote Unit for WOM_40, MetroAIR */
#define WRU_43  0xD7    /* Rack 4, Wideband Remote Unit for WOM_40, MetroAIR */
#define WRU_44  0xD8    /* Rack 4, Wideband Remote Unit for WOM_40, MetroAIR */


#define RNC_NBAP 0x57    /* Radio Network Controller NBAP/Iub connection */
#define AXU     0x58    /* ATM Switching Unit */
#define RNC     0x59    /* Radio Network Controller */

/* Sector hubs */
#define HUB_0   0x60    /* Sector0's sector HUB */
#define HUB_1   0x61    /* Sector1's sector HUB */
#define HUB_2   0x62    /* Sector2's sector HUB */
#define WEH_10  0x63    /* Rack1, Wideband Ethernet Hub */
#define WEH_20  0x64    /* Rack2, Wideband Ethernet Hub */


/* Passive units in I2C buses. Some of the "sub-units" (CPUs)
are controlled via these units */
#define BB_WFA_10   0x70  /* Rack 1,Baseband Wideband Fan Unit */
#define BB_WFA_20   0x71  /* Rack 2,Baseband Wideband Fan Unit */
#define BB_WFA_30   0x72  /* Rack 3,Baseband Wideband Fan Unit */

#define TR_WFA      0x73    /* Transmission Wideband Fan Unit */
#define WPA_WFA_ALL 0x74    /* Wideband Power Amplifier Fan unit (2 fans inside) */
#define WID         0x75    /* Wideband Cabinet Core Unit */

#define WPS_10      0x76    /* Rack 1,Wideband Power Supply Unit */
#define WPS_20      0x77    /* Rack 2,Wideband Power Supply Unit */
#define WPS_30      0x78    /* Rack 3,Wideband Power Supply Unit */
#define WAF_10      0x79    /* Rack 1,Wideband Antenna Filter Unit */
#define WAF_11      0x7A    /* Rack 1,Wideband Antenna Filter Unit */
#define WAF_12      0x7B    /* Wideband Antenna Filter Unit (in OPTIMA Cabinet) */
#define WAF_20      0x7C    /* Rack 2,Wideband Antenna Filter Unit */
#define WAF_21      0x7D    /* Rack 2,Wideband Antenna Filter Unit */
#define WAF_30      0x7F    /* Rack 3,Wideband Antenna Filter Unit */
#define WAF_31      0x80    /* Rack 3,Wideband Antenna Filter Unit */
#define WAF_32      0x81    /* Rack 3,Wideband Antenna Filter Unit */
#define WHX         0x82    /* Wideband Heat Exchanger Unit */
#define WEA         0x83    /* Wideband External Alarm Unit */
#define WIC_10      0x85    /* Rack 1,Wideband Input Combiner Unit */
#define WIC_20      0x86    /* Rack 2,Wideband Input Combiner Unit */
#define WIC_30      0x87    /* Rack 3,Wideband Input Combiner Unit */
#define WSM_10      0x88    /* Rack 1,Wideband Summing and Mplexing Unit */
#define WSM_20      0x89    /* Rack 2,Wideband Summing and Mplexing Unit */
#define WSM_30      0x8A    /* Rack 3,Wideband Summing and Mplexing Unit */
#define WPS_EXT     0x8B    /* Wideband Power Supply Unit in OPTIMA */  /* Secondary cabinet*/
#define WCI         0x8C    /* Wideband Clock Interface unit */
#define WSC_10      0x8D    /* Wideband System Clock Unit, master */
#define WSC_20      0x8E    /* Wideband System Clock Unit, redundant */
#define WIB         0x8F    /* Wideband Internal Battery (in NOZOMI cabinet) */
#define WMC         0x90    /* Wideband Summing and clock module (in NOZOMI cabinet) */
#define WIC_11      0x91    /* Rack 1,Wideband Input Combiner Unit 2 */
#define WIC_31      0x92    /* Rack 3,Wideband Input Combiner Unit 2 */
#define WSM_TR      0x93    /* Wideband Summing and Mplexing Unit, TR-extension cabinet */
#define WPS_TR      0x94    /* Wideband Power Supply Unit, TR-extension cabinet */
#define WAF_22      0x95    /* Rack 2,Wideband Antenna Filter Unit */

#define BB_WFA_EXT  0x96    /* Rack 2,Baseband Wideband Fan Unit in OPTIMA COMPACT */
#define TR_WFA_EXT  0x97    /* Transmission Wideband Fan Unit, in Optima family */
#define WTR_WMP_WFAS 0x98   /* TRIPLE mode cabinet fans (three fans) */

#define RF_FAN_LEFT  0x99    /* Left side RF MFUA fan, in DORIS */
#define RF_FAN_RIGHT 0x9A    /* Right side RF MFUA fan, in DORIS */
#define BB_FAN       0x9B    /* Basemand MFUA fan, in DORIS */
#define WFD          0x9C    /* Wideband Fan Driver, in DORIS */

/* FSEB/FSEE boards */
#define FSE1         WEA
#define FSE2         0x84


/* Flexi System module boards */
#define FSM_FCM      WAM_10  /* Flexi System Module, Flexi Control & Multiplexing, will be removed in INC5!!! */

#define FSM1_FCM     WAM_10  /* Flexi System Module, Flexi Control & Multiplexing */
#define FSM2_FCM     WAM_20  /* Flexi Extension Module 1, Flexi Control & Multiplexing */
#define FSM3_FCM     WAM_30  /* Flexi Extension Module 2, Flexi Control & Multiplexing */

#define LTX_10       0x9D    /* Linear Transceiver 1 */
#define LTX_20       0x9E    /* Linear Transceiver 2 */
#define LTX_30       0x9F    /* Linear Transceiver 3 */
/* Begin LTE 106-c */
#define LTX_40       0xBC    /* Linear Transceiver 4 */
#define LTX_50       0xC0    /* Linear Transceiver 5 */
#define LTX_60       0xD4    /* Linear Transceiver 6 */




#define FR1          LTX_10  /* Linear Transceiver 1 */
#define FR2          LTX_20  /* Linear Transceiver 2 */
#define FR3          LTX_30  /* Linear Transceiver 3 */
#define FR4          0xBC    /* Linear Transceiver 4 */
#define FR5          0xC0    /* Linear Transceiver 5 */
#define FR6          0xD4    /* Linear Transceiver 6 */

/* LTXs in optif 1 */
#define FR1_1_1   0x9D          /*1st FR/LTX in chain of optif 1 */
#define FR1_1_2   0xB0          /*2nd FR/LTX in chain of optif 1 */
#define FR1_1_3   0xB1          /*3rd FR/LTX in chain of optif 1 */
#define FR1_1_4   0xB2          /*4th FR/LTX in chain of optif 1 */
/* LTXs in optif 2 */
#define FR1_2_1   0x9E          /*1st FR/LTX in chain of optif 2 */
#define FR1_2_2   0xB3          /*2nd FR/LTX in chain of optif 2 */
#define FR1_2_3   0xB4          /*3rd FR/LTX in chain of optif 2 */
#define FR1_2_4   0xB5          /*4th FR/LTX in chain of optif 2 */
/* LTXs in optif 3 */
#define FR1_3_1   0x9F          /*1st FR/LTX in chain of optif 3 */
#define FR1_3_2   0xB6          /*2nd FR/LTX in chain of optif 3 */
#define FR1_3_3   0xB7          /*3rd FR/LTX in chain of optif 3 */
#define FR1_3_4   0xB8          /*4th FR/LTX in chain of optif 3 */
/* LTXs in optif 4 */
#define FR1_4_1   0xBC          /*1st FR/LTX in chain of optif 4 */
#define FR1_4_2   0xBD          /*2nd FR/LTX in chain of optif 4 */
#define FR1_4_3   0xBE          /*3rd FR/LTX in chain of optif 4 */
#define FR1_4_4   0xBF          /*4th FR/LTX in chain of optif 4 */
/* LTXs in optif 5 */
#define FR1_5_1   0xC0          /*1st FR/LTX in chain of optif 5 */
#define FR1_5_2   0xC1          /*2nd FR/LTX in chain of optif 5 */
#define FR1_5_3   0xC2          /*3rd FR/LTX in chain of optif 5 */
#define FR1_5_4   0xC3          /*4th FR/LTX in chain of optif 5 */
/* LTXs in optif 6 */
#define FR1_6_1   0xD4          /*1st FR/LTX in chain of optif 6 */
#define FR1_6_2   0xD5          /*2nd FR/LTX in chain of optif 6 */
#define FR1_6_3   0xD6          /*3rd FR/LTX in chain of optif 6 */
#define FR1_6_4   0xD7          /*4th FR/LTX in chain of optif 6 */
/* LTXs in optif 1 on FSM2 */
#define FR2_1_1   0xBC          /*1st FR/LTX in chain of optif 1 on FSM2 */
#define FR2_1_2   0xBD          /*2nd FR/LTX in chain of optif 1 on FSM2 */
#define FR2_1_3   0xBE          /*3rd FR/LTX in chain of optif 1 on FSM2 */
#define FR2_1_4   0xBF          /*4th FR/LTX in chain of optif 1 on FSM2 */
/* LTXs in optif 2 FSM2 */
#define FR2_2_1   0xD4          /*1st FR/LTX in chain of optif 2 on FSM2 */
#define FR2_2_2   0xD5          /*2nd FR/LTX in chain of optif 2 on FSM2 */
#define FR2_2_3   0xD6          /*3rd FR/LTX in chain of optif 2 on FSM2 */
#define FR2_2_4   0xD7          /*4th FR/LTX in chain of optif 2 on FSM2 */
/* LTXs in optif 3 on FSM2 */
#define FR2_3_1   0xB9          /*1st FR/LTX in chain of optif 3 on FSM2 */
#define FR2_3_2   0xBA          /*2nd FR/LTX in chain of optif 3 on FSM2 */
#define FR2_3_3   0xBB          /*3rd FR/LTX in chain of optif 3 on FSM2 */
#define FR2_3_4   0xFE          /*4th FR/LTX in chain of optif 3 on FSM2 */

/* 2G GF1.0 RFM chain depth 5&6 ID:s for SIC addrs, these are not used by any else */
#define FR1_1_5   0x01          /* reuse RAKE_1 */
#define FR1_1_6   0x02          /* reuse RAKE_2 */
#define FR1_2_5   0x03          /* reuse RAKE_3 */
#define FR1_2_6   0x04          /* reuse RAKE_4 */
#define FR1_3_5   0x05          /* reuse CODEC_1 */
#define FR1_3_6   0x06          /* reuse CODEC_2 */
#define FR1_4_5   0x07          /* reuse CODEC_3 */
#define FR1_4_6   0x08          /* reuse CODEC_4 */
#define FR1_5_5   0x09          /* reuse All WSP RAKE CPUs */
#define FR1_5_6   0x0A          /* reuse All WSP CODEC CPUs */
#define FR1_6_5   0x0B          /* reuse All WSP DSP CPUs */
#define FR1_6_6   0x0C          /* reuse All WSP CPUs including WSP_MCU */
#define FEA          WEA     /* Flexi External Alarm Unit */

#define FR1_FF1      0xDB    /* Flexi RF Module1, Flexi Filter1 (STuF) */
#define FR1_FF2      0xDC    /* Flexi RF Module1, Flexi Filter2 (STuF) */

#define FR2_FF1      0xDD    /* Flexi RF Module2, Flexi Filter1 (STuF) */
#define FR2_FF2      0xDE    /* Flexi RF Module2, Flexi Filter2 (STuF) */

#define FR3_FF1      0xDF    /* Flexi RF Module3, Flexi Filter1 (STuF) */
#define FR3_FF2      0xE0    /* Flexi RF Module3, Flexi Filter2 (STuF) */

#define FR1_FF3      0xE3    /* Flexi RF Module1, Flexi Filter3 (STuF) */
#define FR2_FF3      0xE4    /* Flexi RF Module2, Flexi Filter3 (STuF) */
#define FR3_FF3      0xE5    /* Flexi RF Module3, Flexi Filter3 (STuF) */

/* Filters in RadioModule 4 */
#define FR4_FF1  0x7B          /* Flexi RF Module4, Flexi Filter1 (STuF) */
#define FR4_FF2  0x7C          /* Flexi RF Module4, Flexi Filter2 (STuF) */
#define FR4_FF3  0x7D          /* Flexi RF Module4, Flexi Filter3 (STuF) */
/* Filters in RadioModule 5 */
#define FR5_FF1  0xA7          /* Flexi RF Module5, Flexi Filter1 (STuF) */
#define FR5_FF2  0xA8          /* Flexi RF Module5, Flexi Filter2 (STuF) */
#define FR5_FF3  0xA9          /* Flexi RF Module5, Flexi Filter3 (STuF) */
/* Filters in RadioModule 6 */
#define FR6_FF1  0xF2          /* Flexi RF Module6, Flexi Filter1 (STuF) */
#define FR6_FF2  0xF3          /* Flexi RF Module6, Flexi Filter2 (STuF) */
#define FR6_FF3  0xF4          /* Flexi RF Module6, Flexi Filter3 (STuF) */

/* Filters in optif 1 */
#define FR1_1_1_FF1   0xDB          /*1st Filter in RF 1 connected to optif 1 in FSM 1 */
#define FR1_1_1_FF2   0xDC          /*2nd Filter in RF 1 connected to optif 1 in FSM 1 */
#define FR1_1_1_FF3   0xE3          /*3rd Filter in RF 1 connected to optif 1 in FSM 1 */
#define FR1_1_2_FF1   0x4A          /*1st Filter in RF 2 connected to optif 1 in FSM 1 */
#define FR1_1_2_FF2   0x4B          /*2nd Filter in RF 2 connected to optif 1 in FSM 1 */
#define FR1_1_2_FF3   0x4C          /*3rd Filter in RF 2 connected to optif 1 in FSM 1 */
#define FR1_1_3_FF1   0x4D          /*1st Filter in RF 3 connected to optif 1 in FSM 1 */
#define FR1_1_3_FF2   0x4E          /*2nd Filter in RF 3 connected to optif 1 in FSM 1 */
#define FR1_1_3_FF3   0x4F          /*3rd Filter in RF 3 connected to optif 1 in FSM 1 */
#define FR1_1_4_FF1   0x51          /*1st Filter in RF 4 connected to optif 1 in FSM 1 */
#define FR1_1_4_FF2   0x52          /*2nd Filter in RF 4 connected to optif 1 in FSM 1 */
#define FR1_1_4_FF3   0x53          /*3rd Filter in RF 4 connected to optif 1 in FSM 1 */
/* Filters in optif 2 */
#define FR1_2_1_FF1   0xDD          /*1st Filter in RF 1 connected to optif 2 in FSM 1 */
#define FR1_2_1_FF2   0xDE          /*2nd Filter in RF 1 connected to optif 2 in FSM 1 */
#define FR1_2_1_FF3   0xE4          /*3rd Filter in RF 1 connected to optif 2 in FSM 1 */
#define FR1_2_2_FF1   0x54          /*1st Filter in RF 2 connected to optif 2 in FSM 1 */
#define FR1_2_2_FF2   0x55          /*2nd Filter in RF 2 connected to optif 2 in FSM 1 */
#define FR1_2_2_FF3   0x56          /*3rd Filter in RF 2 connected to optif 2 in FSM 1 */
#define FR1_2_3_FF1   0x5A          /*1st Filter in RF 3 connected to optif 2 in FSM 1 */
#define FR1_2_3_FF2   0x5B          /*2nd Filter in RF 3 connected to optif 2 in FSM 1 */
#define FR1_2_3_FF3   0x5C          /*3rd Filter in RF 3 connected to optif 2 in FSM 1 */
#define FR1_2_4_FF1   0x5D          /*1st Filter in RF 4 connected to optif 2 in FSM 1 */
#define FR1_2_4_FF2   0x5E          /*2nd Filter in RF 4 connected to optif 2 in FSM 1 */
#define FR1_2_4_FF3   0x5F          /*3rd Filter in RF 4 connected to optif 2 in FSM 1 */
/* Filters in optif 3 */
#define FR1_3_1_FF1   0xDF          /*1st Filter in RF 1 connected to optif 3 in FSM 1 */
#define FR1_3_1_FF2   0xE0          /*2nd Filter in RF 1 connected to optif 3 in FSM 1 */
#define FR1_3_1_FF3   0xE5          /*3rd Filter in RF 1 connected to optif 3 in FSM 1 */
#define FR1_3_2_FF1   0x65          /*1st Filter in RF 2 connected to optif 3 in FSM 1 */
#define FR1_3_2_FF2   0x66          /*2nd Filter in RF 2 connected to optif 3 in FSM 1 */
#define FR1_3_2_FF3   0x67          /*3rd Filter in RF 2 connected to optif 3 in FSM 1 */
#define FR1_3_3_FF1   0x68          /*1st Filter in RF 3 connected to optif 3 in FSM 1 */
#define FR1_3_3_FF2   0x6A          /*2nd Filter in RF 3 connected to optif 3 in FSM 1 */
#define FR1_3_3_FF3   0x6B          /*3rd Filter in RF 3 connected to optif 3 in FSM 1 */
#define FR1_3_4_FF1   0x6C          /*1st Filter in RF 4 connected to optif 3 in FSM 1 */
#define FR1_3_4_FF2   0x6D          /*2nd Filter in RF 4 connected to optif 3 in FSM 1 */
#define FR1_3_4_FF3   0x6E          /*3rd Filter in RF 4 connected to optif 3 in FSM 1 */
/* Filters in optif 4 */
#define FR1_4_1_FF1   0x7B          /*1st Filter in RF 1 connected to optif 4 in FSM 1 */
#define FR1_4_1_FF2   0x7C          /*2nd Filter in RF 1 connected to optif 4 in FSM 1 */
#define FR1_4_1_FF3   0x7D          /*3rd Filter in RF 1 connected to optif 4 in FSM 1 */
#define FR1_4_2_FF1   0x85          /*1st Filter in RF 2 connected to optif 4 in FSM 1 */
#define FR1_4_2_FF2   0x86          /*2nd Filter in RF 2 connected to optif 4 in FSM 1 */
#define FR1_4_2_FF3   0x87          /*3rd Filter in RF 2 connected to optif 4 in FSM 1 */
#define FR1_4_3_FF1   0xA1          /*1st Filter in RF 3 connected to optif 4 in FSM 1 */
#define FR1_4_3_FF2   0xA2          /*2nd Filter in RF 3 connected to optif 4 in FSM 1 */
#define FR1_4_3_FF3   0xA3          /*3rd Filter in RF 3 connected to optif 4 in FSM 1 */
#define FR1_4_4_FF1   0xA4          /*1st Filter in RF 4 connected to optif 4 in FSM 1 */
#define FR1_4_4_FF2   0xA5          /*2nd Filter in RF 4 connected to optif 4 in FSM 1 */
#define FR1_4_4_FF3   0xA6          /*3rd Filter in RF 4 connected to optif 4 in FSM 1 */
/* Filters in optif 5 */
#define FR1_5_1_FF1   0xA7          /*1st Filter in RF 1 connected to optif 5 in FSM 1 */
#define FR1_5_1_FF2   0xA8          /*2nd Filter in RF 1 connected to optif 5 in FSM 1 */
#define FR1_5_1_FF3   0xA9          /*3rd Filter in RF 1 connected to optif 5 in FSM 1 */
#define FR1_5_2_FF1   0xAA          /*1st Filter in RF 2 connected to optif 5 in FSM 1 */
#define FR1_5_2_FF2   0xAB          /*2nd Filter in RF 2 connected to optif 5 in FSM 1 */
#define FR1_5_2_FF3   0xAC          /*3rd Filter in RF 2 connected to optif 5 in FSM 1 */
#define FR1_5_3_FF1   0xEB          /*1st Filter in RF 3 connected to optif 5 in FSM 1 */
#define FR1_5_3_FF2   0xEC          /*2nd Filter in RF 3 connected to optif 5 in FSM 1 */
#define FR1_5_3_FF3   0xED          /*3rd Filter in RF 3 connected to optif 5 in FSM 1 */
#define FR1_5_4_FF1   0xEE          /*1st Filter in RF 4 connected to optif 5 in FSM 1 */
#define FR1_5_4_FF2   0xEF          /*2nd Filter in RF 4 connected to optif 5 in FSM 1 */
#define FR1_5_4_FF3   0xF1          /*3rd Filter in RF 4 connected to optif 5 in FSM 1 */
/* Filters in optif 6 */
#define FR1_6_1_FF1   0xF2          /*1st Filter in RF 1 connected to optif 6 in FSM 1 */
#define FR1_6_1_FF2   0xF3          /*2nd Filter in RF 1 connected to optif 6 in FSM 1 */
#define FR1_6_1_FF3   0xF4          /*3rd Filter in RF 1 connected to optif 6 in FSM 1 */
#define FR1_6_2_FF1   0xF5          /*1st Filter in RF 2 connected to optif 6 in FSM 1 */
#define FR1_6_2_FF2   0xF6          /*2nd Filter in RF 2 connected to optif 6 in FSM 1 */
#define FR1_6_2_FF3   0xF7          /*3rd Filter in RF 2 connected to optif 6 in FSM 1 */
#define FR1_6_3_FF1   0xF8          /*1st Filter in RF 3 connected to optif 6 in FSM 1 */
#define FR1_6_3_FF2   0xF9          /*2nd Filter in RF 3 connected to optif 6 in FSM 1 */
#define FR1_6_3_FF3   0xFA          /*3rd Filter in RF 3 connected to optif 6 in FSM 1 */
#define FR1_6_4_FF1   0xFB          /*1st Filter in RF 4 connected to optif 6 in FSM 1 */
#define FR1_6_4_FF2   0xFC          /*2nd Filter in RF 4 connected to optif 6 in FSM 1 */
#define FR1_6_4_FF3   0xFD          /*3rd Filter in RF 4 connected to optif 6 in FSM 1 */
/* Filters in optif 1 on FSM 2 */
#define FR2_1_1_FF1   0x7B          /*1st Filter in RF 1 connected to optif 1 in FSM 2 */
#define FR2_1_1_FF2   0x7C          /*2nd Filter in RF 1 connected to optif 1 in FSM 2 */
#define FR2_1_1_FF3   0x7D          /*3rd Filter in RF 1 connected to optif 1 in FSM 2 */
#define FR2_1_2_FF1   0x85          /*1st Filter in RF 2 connected to optif 1 in FSM 2 */
#define FR2_1_2_FF2   0x86          /*2nd Filter in RF 2 connected to optif 1 in FSM 2 */
#define FR2_1_2_FF3   0x87          /*3rd Filter in RF 2 connected to optif 1 in FSM 2 */
#define FR2_1_3_FF1   0xA1          /*1st Filter in RF 3 connected to optif 1 in FSM 2 */
#define FR2_1_3_FF2   0xA2          /*2nd Filter in RF 3 connected to optif 1 in FSM 2 */
#define FR2_1_3_FF3   0xA3          /*3rd Filter in RF 3 connected to optif 1 in FSM 2 */
#define FR2_1_4_FF1   0xA4          /*1st Filter in RF 4 connected to optif 1 in FSM 2 */
#define FR2_1_4_FF2   0xA5          /*2nd Filter in RF 4 connected to optif 1 in FSM 2 */
#define FR2_1_4_FF3   0xA6          /*3rd Filter in RF 4 connected to optif 1 in FSM 2 */
/* Filters in optif 2 on FSM 2 */
#define FR2_2_1_FF1   0xA7          /*1st Filter in RF 1 connected to optif 2 in FSM 2 */
#define FR2_2_1_FF2   0xA8          /*2nd Filter in RF 1 connected to optif 2 in FSM 2 */
#define FR2_2_1_FF3   0xA9          /*3rd Filter in RF 1 connected to optif 2 in FSM 2 */
#define FR2_2_2_FF1   0xAA          /*1st Filter in RF 2 connected to optif 2 in FSM 2 */
#define FR2_2_2_FF2   0xAB          /*2nd Filter in RF 2 connected to optif 2 in FSM 2 */
#define FR2_2_2_FF3   0xAC          /*3rd Filter in RF 2 connected to optif 2 in FSM 2 */
#define FR2_2_3_FF1   0xEB          /*1st Filter in RF 3 connected to optif 2 in FSM 2 */
#define FR2_2_3_FF2   0xEC          /*2nd Filter in RF 3 connected to optif 2 in FSM 2 */
#define FR2_2_3_FF3   0xED          /*3rd Filter in RF 3 connected to optif 2 in FSM 2 */
#define FR2_2_4_FF1   0xEE          /*1st Filter in RF 4 connected to optif 2 in FSM 2 */
#define FR2_2_4_FF2   0xEF          /*2nd Filter in RF 4 connected to optif 2 in FSM 2 */
#define FR2_2_4_FF3   0xF1          /*3rd Filter in RF 4 connected to optif 2 in FSM 2 */
/* Filters in optif 3 on FSM 2 */
#define FR2_3_1_FF1   0xF2          /*1st Filter in RF 1 connected to optif 3 in FSM 2 */
#define FR2_3_1_FF2   0xF3          /*2nd Filter in RF 1 connected to optif 3 in FSM 2 */
#define FR2_3_1_FF3   0xF4          /*3rd Filter in RF 1 connected to optif 3 in FSM 2 */
#define FR2_3_2_FF1   0xF5          /*1st Filter in RF 2 connected to optif 3 in FSM 2 */
#define FR2_3_2_FF2   0xF6          /*2nd Filter in RF 2 connected to optif 3 in FSM 2 */
#define FR2_3_2_FF3   0xF7          /*3rd Filter in RF 2 connected to optif 3 in FSM 2 */
#define FR2_3_3_FF1   0xF8          /*1st Filter in RF 3 connected to optif 3 in FSM 2 */
#define FR2_3_3_FF2   0xF9          /*2nd Filter in RF 3 connected to optif 3 in FSM 2 */
#define FR2_3_3_FF3   0xFA          /*3rd Filter in RF 3 connected to optif 3 in FSM 2 */
#define FR2_3_4_FF1   0xFB          /*1st Filter in RF 4 connected to optif 3 in FSM 2 */
#define FR2_3_4_FF2   0xFC          /*2nd Filter in RF 4 connected to optif 3 in FSM 2 */
#define FR2_3_4_FF3   0xFD          /*3rd Filter in RF 4 connected to optif 3 in FSM 2 */


/* end LTE106-c */

#define FSM_FSP1     WSP_10  /* Flexi Signal Processing 1, will be removed in INC5!!! */
#define FSM_FSP2     WSP_11  /* Flexi Signal Processing 2, will be removed in INC5!!! */
#define FSM_FSP3     WSP_12  /* Flexi Signal Processing 3, will be removed in INC5!!! */

#define FSM_FT       0xE1     /* Flexi Transport Submodule, will be removed in INC5 !!! */
#define FSM1_FT      0xE1     /* Flexi Transport Submodule1 */
#define FSM2_FT      0xE8     /* Flexi Transport Submodule2 */
#define FSM3_FT      0xE9     /* Flexi Transport Submodule3 */
#define FSM4_FT      0x96     /* Flexi Transport Submodule4 */
#define FSM5_FT      0x97     /* Flexi Transport Submodule5 */
#define FSM6_FT      0x98     /* Flexi Transport Submodule6 */
#define FSM7_FT      0x1B     /* Flexi Transport Submodule7 */
#define FSM8_FT      0x29     /* Flexi Transport Submodule8 */
#define FSM9_FT      0x2B     /* Flexi Transport Submodule9 */
#define FSM10_FT     0x2C     /* Flexi Transport Submodule10 */
#define FSM11_FT     0x2F     /* Flexi Transport Submodule11 */
#define FSM12_FT     0x3C     /* Flexi Transport Submodule12 */
#define FSM13_FT     0x3E     /* Flexi Transport Submodule13 */
#define FSM14_FT     0x7E     /* Flexi Transport Submodule14 */


#define FSM1_FSP1    WSP_10  /* Flexi System Module, Flexi Signal Processing 1 */
#define FSM1_FSP2    WSP_11  /* Flexi System Module, Flexi Signal Processing 2 */
#define FSM1_FSP3    WSP_12  /* Flexi System Module, Flexi Signal Processing 3 */

#define FSM2_FSP1    WSP_20  /* Flexi Extension Module 1, Flexi Signal Processing 1 */
#define FSM2_FSP2    WSP_21  /* Flexi Extension Module 1, Flexi Signal Processing 2 */
#define FSM2_FSP3    WSP_22  /* Flexi Extension Module 1, Flexi Signal Processing 3 */

#define FSM3_FSP1    WSP_30  /* Flexi Extension Module 2, Flexi Signal Processing 1 */
#define FSM3_FSP2    WSP_31  /* Flexi Extension Module 2, Flexi Signal Processing 2 */
#define FSM3_FSP3    WSP_32  /* Flexi Extension Module 2, Flexi Signal Processing 3 */

#define FSM4_FSP1    0x42    /* Flexi Extension Module 3, Flexi Signal Processing 1 */
#define FSM4_FSP2    0x43    /* Flexi Extension Module 3, Flexi Signal Processing 2 */
#define FSM4_FSP3    0x44    /* Flexi Extension Module 3, Flexi Signal Processing 3 */

#define FSM5_FSP1    0x52    /* Flexi Extension Module 4, Flexi Signal Processing 1 */
#define FSM5_FSP2    0x53    /* Flexi Extension Module 4, Flexi Signal Processing 2 */
#define FSM5_FSP3    0x54    /* Flexi Extension Module 4, Flexi Signal Processing 3 */

#define FSM6_FSP1    0x62    /* Flexi Extension Module 5, Flexi Signal Processing 1 */
#define FSM6_FSP2    0x63    /* Flexi Extension Module 5, Flexi Signal Processing 2 */
#define FSM6_FSP3    0x64    /* Flexi Extension Module 5, Flexi Signal Processing 3 */

#define FSM7_FSP1    0x72    /* Flexi Extension Module 6, Flexi Signal Processing 1 */
#define FSM7_FSP2    0x73    /* Flexi Extension Module 6, Flexi Signal Processing 2 */
#define FSM7_FSP3    0x74    /* Flexi Extension Module 6, Flexi Signal Processing 3 */

#define FSM8_FSP1    0x82    /* Flexi Extension Module 7, Flexi Signal Processing 1 */
#define FSM8_FSP2    0x83    /* Flexi Extension Module 7, Flexi Signal Processing 2 */
#define FSM8_FSP3    0x84    /* Flexi Extension Module 7, Flexi Signal Processing 3 */

#define FSM9_FSP1    0x92    /* Flexi Extension Module 8, Flexi Signal Processing 1 */
#define FSM9_FSP2    0x93    /* Flexi Extension Module 8, Flexi Signal Processing 2 */
#define FSM9_FSP3    0x94    /* Flexi Extension Module 8, Flexi Signal Processing 3 */

#define FSM10_FSP1   0xA2    /* Flexi Extension Module 9, Flexi Signal Processing 1 */
#define FSM10_FSP2   0xA3    /* Flexi Extension Module 9, Flexi Signal Processing 2 */
#define FSM10_FSP3   0xA4    /* Flexi Extension Module 9, Flexi Signal Processing 3 */

#define FSM11_FSP1   0xB2    /* Flexi Extension Module 10, Flexi Signal Processing 1 */
#define FSM11_FSP2   0xB3    /* Flexi Extension Module 10, Flexi Signal Processing 2 */
#define FSM11_FSP3   0xB4    /* Flexi Extension Module 10, Flexi Signal Processing 3 */

#define FSM12_FSP1   0xC2    /* Flexi Extension Module 11, Flexi Signal Processing 1 */
#define FSM12_FSP2   0xC3    /* Flexi Extension Module 11, Flexi Signal Processing 2 */
#define FSM12_FSP3   0xC4    /* Flexi Extension Module 11, Flexi Signal Processing 3 */

#define FSM13_FSP1   0xD2    /* Flexi Extension Module 12, Flexi Signal Processing 1 */
#define FSM13_FSP2   0xD3    /* Flexi Extension Module 12, Flexi Signal Processing 2 */
#define FSM13_FSP3   0xD4    /* Flexi Extension Module 12, Flexi Signal Processing 3 */

#define FSM14_FSP1   0xE2    /* Flexi Extension Module 13, Flexi Signal Processing 1 */
#define FSM14_FSP2   0xE3    /* Flexi Extension Module 13, Flexi Signal Processing 2 */
#define FSM14_FSP3   0xE4    /* Flexi Extension Module 13, Flexi Signal Processing 3 */

#define FAM1         0xE6    /* LTE FAM, CTRL_MCU should be used as CPU value */
#define DCT1         0xE7    /* LTE Data collection tool, CTRL_MCU should be used as CPU value */

#define AXC1         0xEA    /* ATM Switching Controller 1, CTRL_MCU should be used as CPU value  */

#define FSM1            0xAD     /* Flexi System Module */
#define FSM2            0xAE     /* Flexi Extension Module 1 */
#define FSM3            0xAF     /* Flexi Extension Module 2 */
#define FSM_UNKNOWN     0xFF    /* Unknown Module */

/* Hannu H: In below defines there are probably also something that could be removed, but as there are
   also some Wimax board & CPU definitions I did not dare to clean this up */
#define FYS1_FCM      FSM1_FCM            /* Flexi WiMAX System Module, Flexi Control & Multiplexing */
#define FYS1          FSM1                /* Flexi WiMAX System Module */
#define FYS1_FT       FSM1_FT             /* Flexi WiMAX Transport Submodule */
#define FYS1_FYB1     FSM1_FSP1           /* Flexi WiMAX System Module, Flexi Signal Processing 1 */
#define FYS1_FYB1_BB1 FSM1_FSP1_FARADAY1  /* Flexi WiMAX System Module, Flexi Signal Processing 1, BaseBand Function 1 */
#define FYS1_FYB1_BB2 FSM1_FSP1_FARADAY2  /* Flexi WiMAX System Module, Flexi Signal Processing 1, BaseBand Function 2 */
#define FYS1_FYB1_BB3 FSM1_FSP1_FARADAY3  /* Flexi WiMAX System Module, Flexi Signal Processing 1, BaseBand Function 3 */
#define FYS1_FYB2     FSM1_FSP2           /* Flexi WiMAX System Module, Flexi Signal Processing 2 */
#define FYS1_FYB2_BB1 FSM1_FSP2_FARADAY1  /* Flexi WiMAX System Module, Flexi Signal Processing 2, BaseBand Function 1 */
#define FYS1_FYB2_BB2 FSM1_FSP2_FARADAY2  /* Flexi WiMAX System Module, Flexi Signal Processing 2, BaseBand Function 2 */
#define FYS1_FYB2_BB3 FSM1_FSP2_FARADAY3  /* Flexi WiMAX System Module, Flexi Signal Processing 2, BaseBand Function 3 */
#define FYS1_FYB3     FSM1_FSP3           /* Flexi WiMAX System Module, Flexi Signal Processing 3 */
#define FYS1_FYB3_BB1 FSM1_FSP3_FARADAY1  /* Flexi WiMAX System Module, Flexi Signal Processing 3, BaseBand Function 1 */
#define FYS1_FYB3_BB2 FSM1_FSP3_FARADAY2  /* Flexi WiMAX System Module, Flexi Signal Processing 3, BaseBand Function 2 */
#define FYS1_FYB3_BB3 FSM1_FSP3_FARADAY3  /* Flexi WiMAX System Module, Flexi Signal Processing 3, BaseBand Function 3 */
#define FYS1_OIC1     FSM1_OIC1           /* Flexi WiMAX System Module, Optical interface 1 */
#define FYS1_OIC2     FSM1_OIC2           /* Flexi WiMAX System Module, Optical interface 2 */
#define FYS1_OIC3     FSM1_OIC3           /* Flexi WiMAX System Module, Optical interface 3 */
#define FYS1_OIC4     FSM1_OIC4           /* Flexi WiMAX System Module, Optical interface 4 */
#define FYS1_OIC5     FSM1_OIC5           /* Flexi WiMAX System Module, Optical interface 5 */
#define FYR1          FR1_MODULE          /* Flexi WiMAX RF Module 1 */
#define FYR2          FR2_MODULE          /* Flexi WiMAX RF Module 2 */
#define FYR3          FR3_MODULE          /* Flexi WiMAX RF Module 3 */
#define FYR1_LTX      LTX_10        /* CORE_FYR for FYR1 */
#define FYR1_RX1      FR1_RX1             /* Flexi WiMAX RF Module 1, Receiver 1 */
#define FYR1_RX2      FR1_RX2             /* Flexi WiMAX RF Module 1, Receiver 2 */
#define FYR1_TX1      FR1_TX1             /* Flexi WiMAX RF Module 1, Transmitter 1 */
#define FYR1_TX2      FR1_TX2             /* Flexi WiMAX RF Module 1, Transmitter 2 */
#define FYR1_FAN1     FR1_FAN1            /* Flexi WiMAX RF Module 1, FAN 1 */
#define FYR1_FAN2     FR1_FAN2            /* Flexi WiMAX RF Module 1, FAN 2 */
#define FYR1_FANGROUP FR1_FANGROUP        /* Flexi WiMAX RF Module 1, FANGROUP */
#define FYR2_LTX      LTX_20        /* CORE_FYR for FYR2 */
#define FYR2_RX1      FR2_RX1             /* Flexi WiMAX RF Module 2, Receiver 1 */
#define FYR2_RX2      FR2_RX2             /* Flexi WiMAX RF Module 2, Receiver 2 */
#define FYR2_TX1      FR2_TX1             /* Flexi WiMAX RF Module 2, Transmitter 1 */
#define FYR2_TX2      FR2_TX2             /* Flexi WiMAX RF Module 2, Transmitter 2 */
#define FYR2_FAN1     FR2_FAN1            /* Flexi WiMAX RF Module 2, FAN 1 */
#define FYR2_FAN2     FR2_FAN2            /* Flexi WiMAX RF Module 2, FAN 2 */
#define FYR2_FANGROUP FR2_FANGROUP        /* Flexi WiMAX RF Module 2, FANGROUP */
#define FYR3_LTX      LTX_30        /* CORE_FYR for FYR3 */
#define FYR3_RX1      FR3_RX1             /* Flexi WiMAX RF Module 3, Receiver 1 */
#define FYR3_RX2      FR3_RX2             /* Flexi WiMAX RF Module 3, Receiver 2 */
#define FYR3_TX1      FR3_TX1             /* Flexi WiMAX RF Module 3, Transmitter 1 */
#define FYR3_TX2      FR3_TX2             /* Flexi WiMAX RF Module 3, Transmitter 2 */
#define FYR3_FAN1     FR3_FAN1            /* Flexi WiMAX RF Module 3, FAN 1 */
#define FYR3_FAN2     FR3_FAN2            /* Flexi WiMAX RF Module 3, FAN 2 */
#define FYR3_FANGROUP FR3_FANGROUP        /* Flexi WiMAX RF Module 3, FANGROUP */

/* HD-BDE BoardId's */
#define LCP1 0x10
#define LCP2 0x11
#define LSP1  0x12
#define LSP2  0x13
#define LSP3  0x14
#define LSP4  0x15
#define LSP5  0x16
#define LSP6  0x17
#define LSP7  0x18
#define LSP8  0x19
#define LSP9  0x1A
#define LSP10 0x1B
#define LSP11 0x1C
#define LSP12 0x1D
#define LSP13 0x1E
#define LSP14 0x1F
#define LSP15 0x20
#define LSP16 0x21
#define LCA1 0x40 /* SCA */
#define LBI1 0x41 /* BPI */
#define LBR1 0x42 /* BBR0 */
#define LBR2 0x43 /* BBR1 */
#define LBR3 0x44 /* BBR2 */
#define LBR4 0x45 /* BBR3 */
#define LNI1 0x46 /* NIC0 */
#define LNI2 0x47 /* NIC1 */
#define LPS1 0x48 /* PSU0 */
#define LPS2 0x49 /* PSU1 */
#define LPS3 0x4A /* PSU2 */
#define LPS4 0x4B /* PSU3 */
#define LPS5 0x4C /* PSU4 */
#define LPS6 0x4D /* PSU5 */

/* FPFD/FPFH  BoardIds */
#define FPF1 LPS1
#define FPF2 LPS2
#define FPF3 LPS3
#define FPF4 LPS4
#define FPF5 LPS5
#define FPF6 LPS6

#define FSM1_FPF1   0x1048                             // first FPF connected to FSM1_FCT
#define FSM1_FPF2   0x1049
#define FSM1_FPF3   0x104A
#define FSM1_FPF4   0x104B
#define FSM1_FPF5   0x104C
#define FSM1_FPF6   0x104D
#define FSM1_FSE1   0x1083                             // first FSE connected to FSM1_FCT
#define FSM1_FSE2   0x1084

#define FSM2_FPF1   0x2048
#define FSM2_FPF2   0x2049
#define FSM2_FPF3   0x204A
#define FSM2_FPF4   0x204B
#define FSM2_FPF5   0x204C
#define FSM2_FPF6   0x204D
#define FSM2_FSE1   0x2083
#define FSM2_FSE2   0x2084

#define FSM3_FPF1   0x3048
#define FSM3_FPF2   0x3049
#define FSM3_FPF3   0x304A
#define FSM3_FPF4   0x304B
#define FSM3_FPF5   0x304C
#define FSM3_FPF6   0x304D
#define FSM3_FSE1   0x3083
#define FSM3_FSE2   0x3084

#define FSM4_FPF1   0x4048
#define FSM4_FPF2   0x4049
#define FSM4_FPF3   0x404A
#define FSM4_FPF4   0x404B
#define FSM4_FPF5   0x404C
#define FSM4_FPF6   0x404D
#define FSM4_FSE1   0x4083
#define FSM4_FSE2   0x4084

#define FSM5_FPF1   0x5048
#define FSM5_FPF2   0x5049
#define FSM5_FPF3   0x504A
#define FSM5_FPF4   0x504B
#define FSM5_FPF5   0x504C
#define FSM5_FPF6   0x504D
#define FSM5_FSE1   0x5083
#define FSM5_FSE2   0x5084

#define FSM6_FPF1   0x6048
#define FSM6_FPF2   0x6049
#define FSM6_FPF3   0x604A
#define FSM6_FPF4   0x604B
#define FSM6_FPF5   0x604C
#define FSM6_FPF6   0x604D
#define FSM6_FSE1   0x6083
#define FSM6_FSE2   0x6084

#define FSM7_FPF1   0x7048
#define FSM7_FPF2   0x7049
#define FSM7_FPF3   0x704A
#define FSM7_FPF4   0x704B
#define FSM7_FPF5   0x704C
#define FSM7_FPF6   0x704D
#define FSM7_FSE1   0x7083
#define FSM7_FSE2   0x7084

#define FSM8_FPF1   0x8048
#define FSM8_FPF2   0x8049
#define FSM8_FPF3   0x804A
#define FSM8_FPF4   0x804B
#define FSM8_FPF5   0x804C
#define FSM8_FPF6   0x804D
#define FSM8_FSE1   0x8083
#define FSM8_FSE2   0x8084

#define FSM9_FPF1   0x9048
#define FSM9_FPF2   0x9049
#define FSM9_FPF3   0x904A
#define FSM9_FPF4   0x904B
#define FSM9_FPF5   0x904C
#define FSM9_FPF6   0x904D
#define FSM9_FSE1   0x9083
#define FSM9_FSE2   0x9084

#define FSM10_FPF1   0xA048
#define FSM10_FPF2   0xA049
#define FSM10_FPF3   0xA04A
#define FSM10_FPF4   0xA04B
#define FSM10_FPF5   0xA04C
#define FSM10_FPF6   0xA04D
#define FSM10_FSE1   0xA083
#define FSM10_FSE2   0xA084

#define FSM11_FPF1   0xB048
#define FSM11_FPF2   0xB049
#define FSM11_FPF3   0xB04A
#define FSM11_FPF4   0xB04B
#define FSM11_FPF5   0xB04C
#define FSM11_FPF6   0xB04D
#define FSM11_FSE1   0xB083
#define FSM11_FSE2   0xB084

#define FSM12_FPF1   0xC048
#define FSM12_FPF2   0xC049
#define FSM12_FPF3   0xC04A
#define FSM12_FPF4   0xC04B
#define FSM12_FPF5   0xC04C
#define FSM12_FPF6   0xC04D
#define FSM12_FSE1   0xC083
#define FSM12_FSE2   0xC084

#define FSM13_FPF1   0xD048
#define FSM13_FPF2   0xD049
#define FSM13_FPF3   0xD04A
#define FSM13_FPF4   0xD04B
#define FSM13_FPF5   0xD04C
#define FSM13_FPF6   0xD04D
#define FSM13_FSE1   0xD083
#define FSM13_FSE2   0xD084

#define FSM14_FPF1   0xE048
#define FSM14_FPF2   0xE049
#define FSM14_FPF3   0xE04A
#define FSM14_FPF4   0xE04B
#define FSM14_FPF5   0xE04C
#define FSM14_FPF6   0xE04D
#define FSM14_FSE1   0xE083
#define FSM14_FSE2   0xE084

/* AMOC Airscale Outdoor Compact Subrack - Control Board ID */
#define FSM_CTRL     WID
#define FSM1_CTRL    0x1075
#define FSM2_CTRL    0x2075
#define FSM3_CTRL    0x3075
#define FSM4_CTRL    0x4075
#define FSM5_CTRL    0x5075
#define FSM6_CTRL    0x6075
#define FSM7_CTRL    0x7075
#define FSM8_CTRL    0x8075
#define FSM9_CTRL    0x9075
#define FSM10_CTRL   0xA075
#define FSM11_CTRL   0xB075
#define FSM12_CTRL   0xC075
#define FSM13_CTRL   0xD075
#define FSM14_CTRL   0xE075

/* Active LCP Logical Board ID */
#define LCP_ACT 0xFE

/**********************************************************************************/
/* CPU's logical name definitions. CPU is an active processor, a passive device   */
/* or a "sub-unit".                                                               */
/*                                                                                */
/* WSP- and WAM-board's CPU's numbers maps to physical addresses in AIF-bus.      */
/* Address is 8 bit wide, first 4 bits (MSB) are not used as an address and       */
/* second 4 bits (LSB) is NSA address.                                            */


/* WSP processors */
#define RAKE_1      0x01    /* WSP RAKE1 */
#define RAKE_2      0x02    /* WSP RAKE2 */
#define RAKE_3      0x03    /* WSP RAKE3 */
#define RAKE_4      0x04    /* WSP RAKE4 */
#define CODEC_1     0x05    /* WSP CODEC1 */
#define CODEC_2     0x06    /* WSP CODEC2 */
#define CODEC_3     0x07    /* WSP CODEC3 */
#define CODEC_4     0x08    /* WSP CODEC4 */
#define RAKE_ALL    0x09    /* All WSP RAKE CPUs */
#define CODEC_ALL   0x0A    /* All WSP CODEC CPUs */
#define DSP_ALL     0x0B    /* All WSP DSP CPUs */
#define WSP_ALL     0x0C    /* All WSP CPUs including WSP_MCU */
#define WSP_MCU     0x0D    /* WSP MCU */

#define WSPC_RAKE_1     0x71  /* WSPC RAKE1 */
#define WSPC_RAKE_2     0x72  /* WSPC RAKE2 */
#define WSPC_RAKE_3     0x73  /* WSPC RAKE3 */
#define WSPC_RAKE_4     0x74  /* WSPC RAKE4, reserved for the future use */
#define WSPC_CODEC_1    0x75  /* WSPC CODEC1 */
#define WSPC_CODEC_2    0x76  /* WSPC CODEC2, reserved for the future use */
#define WSPC_CODEC_3    0x77  /* WSPC CODEC3, reserved for the future use */
#define WSPC_CODEC_4    0x78  /* WSPC CODEC4, reserved for the future use */
#define WSPC_RAKE_ALL   0x79  /* All WSPC RAKE CPUs */
#define WSPC_CODEC_ALL  0x7A  /* All WSPC CODEC CPUs */

/* WAM processors */
#define CTRL_MCU    0x11    /* WAM O&M MCU, this is used also in new Flexi units */
#define ATM1_MCU    0x17    /* WAM AAL2 MCU1 */
#define ATM2_MCU    0x1A    /* WAM AAL2 MCU2 */
#define ATM3_MCU    0x1D    /* WAM AAL2 MCU3 */
#define ATMHOST_MCU 0x14    /* WAM ATM host MCU */
#define ATM_ALL     0x1F    /* All WAM ATM CPUs */
#define DNBAP       0x12    /* DNBAP ATM channel to RNC */
#define CNBAP       0x13    /* CNBAP ATM channel to RNC */
#define AAL2S       0x15    /* ATM internal channel to RNC */

/* WTR, WPA and AXU processors */
#define WTR_MCU     0x20    /* WTR MCU */
#define WPA_MCU     0x21    /* WPA MCU */
#define AXU_MCU     0x22    /* AXU MCU */
#define WOU_MCU     0x28    /* WOU MCU (AIR) */

/* Fans inside BB_WFA and TR_WFA units (Optima, Supreme and Triple)  */
#define WFA_1       0x30    /* WFA1, a base band fan in the case of Triple mode */
#define WFA_2       0x31    /* WFA2, a cabinet fan 1 in the case of Triple mode */
#define WFA_3       0x32    /* WFA3, a cabinet fan 2 in the case of Triple mode */
#define WFA_4       0x33    /* WFA4, a cabinet fan 3 in the case of Triple mode */

/* WPA and WTR fans when control board is BB_WFA or WFD */
#define WTR_WFA     0x34    /* WTR-fan, used when ctrl board is BB_WFA  */
#define WPA_WFA1    0x35    /* WPA-fan1, used when ctrl board is BB_WFA or WFD */
#define WPA_WFA2    0x36    /* WPA-fan2, used when ctrl board is BB_WFA or WFD */
#define WPA_WFA3    0x37    /* WPA-fan3, used when ctrl board is WFD */
#define WPA_WFA4    0x38    /* WPA-fan4, used when ctrl board is WFD */
#define WPA_WFA5    0x39    /* WPA-fan5, used when ctrl board is WFD */
#define WPA_WFA6    0x3A    /* WPA-fan6, used when ctrl board is WFD */

#define HEX_FAN     0x3B    /* HEX fan, used when ctrl board is WFD */

/* These groups are used with WPA axial fans when control board is WFD */
#define WPA_WFA_GR1 0x75    /* Wideband Power Amplifier Fan unit group 1 (WPA_WFF1 and WPA_WFA2) */
#define WPA_WFA_GR2 0x76    /* Wideband Power Amplifier Fan unit group 2 (WPA_WFF3 and WPA_WFA4) */
#define WPA_WFA_GR3 0x77    /* Wideband Power Amplifier Fan unit group 3 (WPA_WFF5 and WPA_WFA6) */

/* Fans when control board is WHX  */
#define WHX_EXT_WFA     0x45    /* External fan, used when ctrl board is WHX */
#define WHX_INT_WFA     0x46    /* Internal fan, used when ctrl board is WHX */
#define WHX_WTR_WFA     0x47    /* WTR-fan,  used when ctrl board is WHX */
#define WHX_WPA_WFA1    0x48    /* WPA-fan1, used when ctrl board is WHX */
#define WHX_WPA_WFA2    0x49    /* WPA-fan2, used when ctrl board is WHX */

/* WSC and WSM units inside NOZOMI WMC unit */
#define WMC_WSC     0x37
#define WMC_WSM     0x38
#define WMC_DSAX    0x39
#define WMC_UMAX    0x40

/* Passive I2C devices in some board (unit) */
#define WFA_LED     0x39    /* BB-WFA,TR-WFA */
#define TEMP_SEN    0x40    /* Board's temperature sensor */
#define FLASH       0x41    /* Board's flash memory */
#define EEPROM      0x42    /* Board's eeprom */

#define LNA1        0x43    /* WAF LNA1 */
#define LNA2        0x44    /* WAF LNA2 */
#define MHA_10      0xA1    /* WAF_10 MHA_10*/
#define MHA_11      0xA2    /* WAF_10 MHA_11*/
#define MHA_12      0xA3    /* WAF_11 MHA_12*/
#define MHA_13      0xA4    /* WAF_11 MHA_13*/
#define MHA_14      0xA5    /* WAF_12 MHA_14*/
#define MHA_15      0xA6    /* WAF_12 MHA_15*/
#define MHA_20      0xA7    /* WAF_20 MHA_20*/
#define MHA_21      0xA8    /* WAF_20 MHA_21*/
#define MHA_22      0xA9    /* WAF_21 MHA_22*/
#define MHA_23      0xAA    /* WAF_21 MHA_23*/
#define MHA_24      0xAB    /* WAF_22 MHA_24*/
#define MHA_25      0xAC    /* WAF_22 MHA_25*/
#define MHA_30      0xDA    /* WAF_30 MHA_30*/
#define MHA_31      0x9D    /* WAF_30 MHA_31*/
#define MHA_32      0x9E    /* WAF_31 MHA_32*/
#define MHA_33      0x9F    /* WAF_31 MHA_33*/
#define MHA_34      0x9B    /* WAF_32 MHA_34*/
#define MHA_35      0xA0    /* WAF_32 MHA_35*/

#define BTU_10      0xAD    /* WAF_10 BTU_10*/
#define BTU_11      0xAE    /* WAF_10 BTU_11*/
#define BTU_12      0xAF    /* WAF_11 BTU_12*/
#define BTU_13      0xB0    /* WAF_11 BTU_13*/
#define BTU_14      0xB1    /* WAF_12 BTU_14*/
#define BTU_15      0xB2    /* WAF_12 BTU_15*/
#define BTU_20      0xB3    /* WAF_20 BTU_20*/
#define BTU_21      0xB4    /* WAF_20 BTU_21*/
#define BTU_22      0xB5    /* WAF_21 BTU_22*/
#define BTU_23      0xB6    /* WAF_21 BTU_23*/
#define BTU_24      0xB7    /* WAF_22 BTU_24*/
#define BTU_25      0xB8    /* WAF_22 BTU_25*/
#define BTU_30      0xB9    /* WAF_30 BTU_30*/
#define BTU_31      0xBA    /* WAF_30 BTU_31*/
#define BTU_32      0xBB    /* WAF_31 BTU_32*/
#define BTU_33      0xBC    /* WAF_31 BTU_33*/
#define BTU_34      0xBD    /* WAF_32 BTU_34*/
#define BTU_35      0xBE    /* WAF_32 BTU_35*/

#define WIA         0xBF    /*Wideband integrated antenna*/
#define WOC_10      0xC0    /*Wideband output combiner*/
#define WOC_20      0xC1    /*Wideband output combiner*/
#define WOC_30      0xC2    /*Wideband output combiner*/
#define WPD_10      0xC3    /*Wideband power divider*/
#define WPD_20      0xC4    /*Wideband power divider*/
#define WPD_30      0xC5    /*Wideband power divider*/

#define MUKSU_ASIC   0xC6    /* Flexi Control & Multiplexing, Muksu ASIC */
#define MURKKU_ASIC  MUKSU_ASIC    /* Flexi Control & Multiplexing, Murkku ASIC, FSM-r3 */
#define OIC_FPGA     0xC7    /* Flexi Control & Multiplexing, OIC FPGA */
#define CASA2_FPGA   0xC8    /* Flexi Control & Multiplexing, CASA2 FPGA */

#define FSM_FAN1    0xC9    /* Flexi System/Extension Module Fan1 */
#define FSM_FAN2    0xCA    /* Flexi System/Extension Module Fan2 */
#define FSM_FAN3    0xCB    /* Flexi System/Extension Module Fan3 */

#define RANSU_FPGA  0xCD    /* RANSU FPGA on FYBA */
#define FEC1_FPGA   0xCE    /* FEC1 FPGA on FYBA */
#define FEC2_FPGA   0xCF    /* FEC2 FPGA on FYBA */
#define FEC3_FPGA   0xD0    /* FEC3 FPGA on FYBA */
#define FEC_FPGA_ALL 0xD2   /* All FEC FPGAs on FYBA */
#define FYB_FPGA_ALL 0xD3   /* All FPGAs on FYBA */

/* HD-BDE FPGA's */
#define AGUSTA_FPGA  0xCD    /* Agusta FPGA on LCA */
#define SIDECAR_FPGA 0xCE    /* Sidecar FPGA on LBR */
#define HARLEY_FPGA  0xCF    /* Harley FPGA on LBR */
#define TRIUMPH_FPGA 0xD0    /* Triumph FPGA on LNI */
#define NINJA_FPGA   0xD1    /* Ninja FPGA on LCP */

#define BOFU_FPGA   0xD1    /* BOFU FPGA */

#define CCSSA_FPGA  0xD4    /* CCSSA FPGA on FCT */
#define BMU_FPGA    0xDE    /* BMU FPGA on Rel3 FSP */

#define PEX_FPGA    0xCD    /* Rel4 FCT PEX FPGA */
#define PCO2_FPGA   0xCE    /* Rel4 FCT PCO2 FPGA */
#define PCO_FPGA    PCO2_FPGA    /* FCT PCO FPGA */

#define SYNC_OCXO   0xD5    /* 30.72MHz OCXO on FCT */
#define CLK_OCXO    0xD6    /* 10MHz OCXO on DCMAUX board */

#define TILF_INF  0xD7  /*It represents the TILT interface on FCT board*/
#define PORT_INF 0xD8  /*It represents the PORT interface on FCT board*/

#define CPRI_MUX_1  0xD9  /*It represents the #1 cpri link between Murkku and Radio*/
#define CPRI_MUX_2  0xDA  /*It represents the #1 cpri link between Murkku and Radio*/

#define CODEC0_FPGA 0xE5    /* 5G PoC Codec 0 FPGA */
#define CODEC1_FPGA 0xE6    /* 5G PoC Codec 1 FPGA */
#define FE_FPGA     0xE7    /* 5G PoC Frontend FPGA */

#define SDMA 0xDB  /*represents a part of flash memory which used to store lte software*/
#define SDMB 0xDC  /*represents a part of flash memory which used to store lte software*/
#define SDMN 0xDD  /*represents a part of flash memory which used to store 3g software*/
#define SDME 0xEE  /*represents a part of flash memory which used to store 3g software*/
#define LTEFM 0xEF  /*represents a part of flash memory which used for temporarily storing various types of files */
#define WCDMAFM 0xE0  /*represents a part of flash memory which used for temporarily storing various types of files */
#define VENDORFM 0xE1  /*represents a part of flash memory which used for temporarily storing NSN SW technical logs and some PNS share files*/
#define LTBBRESOURCE 0xE4 /*It represents the 3 lte DSP on MicroREC*/
#define WCDMABBRESOURCE 0xE3 /*It represents the 3 wcdma DSP on MicroREC*/

#define FSM1_BBRESOURCE_1    0x4A  /* For DCM MacroR3 use, Flexi System Module 1, logic BBRESOURCE 1*/
#define FSM1_BBRESOURCE_2    0x4B  /* For DCM MacroR3 use, Flexi System Module 1, logic BBRESOURCE 2 */
#define FSM1_BBRESOURCE_3    0x4C  /* For DCM MacroR3 use, Flexi System Module 1, logic BBRESOURCE 3 */

#define FSM2_BBRESOURCE_1    0x5A  /* For DCM MacroR3 use, Flexi System Module 2, logic BBRESOURCE 1*/
#define FSM2_BBRESOURCE_2    0x5B  /* For DCM MacroR3 use, Flexi System Module 2, logic BBRESOURCE 2 */
#define FSM2_BBRESOURCE_3    0x5C  /* For DCM MacroR3 use, Flexi System Module 2, logic BBRESOURCE 3 */

#define FSM3_BBRESOURCE_1    0x6A  /* For DCM MacroR3 use, Flexi System Module 3, logic BBRESOURCE 1*/
#define FSM3_BBRESOURCE_2    0x6B  /* For DCM MacroR3 use, Flexi System Module 3, logic BBRESOURCE 2 */
#define FSM3_BBRESOURCE_3    0x6C  /* For DCM MacroR3 use, Flexi System Module 4, logic BBRESOURCE 3 */

#define SSD                  0x6F  /* For SolidStateDisk update */

/* Ethernet controllers for ASIK (10GE & RRC) */
#define ETH10G_MCU_CTRL       0xE8  /* For 10GE controller on master Xeon of ASIK boad */
#define ETH10G_MCU_CTRL_SLAVE 0xE9  /* For 10GE controller on slave Xeon of ASIK boad*/
#define RRC                   0xED  /* For Red Rock Canyon switch on ASIK boad*/

/* Logical CPU ID for FCT MCU */
#define FCT_MCU_LOGICAL1    0x11
#define FCT_MCU_LOGICAL2    0x12
#define FCT_MCU_LOGICAL3    0x13
#define FCT_MCU_LOGICAL4    0x14

/* Logical CPU ID for FSP MCU */
#define FSP_MCU_LOGICAL1    0x0D
#define FSP_MCU_LOGICAL2    0x0E
#define FSP_MCU_LOGICAL3    0x0F
#define FSP_MCU_LOGICAL4    0x10

#define AXC1          0xEA    /* ATM Switching Controller 1, CTRL_MCU should be used as CPU value  */

#define FSM1_FIFC    0xEB    /* FIFC unit id for DCM MicroREC */

#define FSM1          0xAD    /* Flexi System Module */

/* Flexi processors */
#define FSP_MCU     WSP_MCU /* FSP MCU */
#define FSM_FT_MCU  0xCB    /* Flexi transport MCU (MRS) */
/* notice that CTRL_MCU is used for LTX */

#define GPS         0xE2    /* GSP Power Switch*/
#define INT_GPS     0x2E    /* Integrated GPS receiver */
/* DSP CPU addresses. CPU address consists of CHIP address and CPU address,
   4 MSBs defines CHIP within board and 4 LSBs defines CPU within chip.
   E.g. if there is need to address CHIP2 and its CPU3, CPU address is 0x43
   *
   * In FSM-r4 CHIP1 means K2A, CHIP2 = K2B, CHIP3 = K2C and CHIP4 = K2D
   *
*/
#define CHIP1       0x30 /* DSP 1 on BB */
#define CHIP2       0x40 /* DSP 2 on BB */
#define CHIP3       0x50 /* DSP 3 on BB */
#define CHIP4       0x60 /* DSP 4 on BB */
#define CHIP5       0x70 /* DSP 5 on BB */
#define CHIP6       0x80 /* DSP 6 on BB */
#define CHIP7       0x90 /* DSP 7 on BB */
#define CHIP8       0xA0 /* DSP 8 on BB */
#define CHIP9       0xB0 /* DSP 9 on BB */
/* These addresses reserved for the future use
#define CHIPA       0xC0
#define CHIPB       0xD0
#define CHIPC       0xE0
#define CHIPD       0xF0
*/
#define CHIP_ALL    0xF0 /* All CHIPs */

#define CPU1        0x01 /* CPU 1 */
#define CPU2        0x02 /* CPU 2 */
#define CPU3        0x03 /* CPU 3 */
#define CPU4        0x04 /* CPU 4 */
#define CPU5        0x05 /* CPU 5 */
#define CPU6        0x06 /* CPU 6 */
#define CPU7        0x07 /* CPU 7 */
#define CPU8        0x08 /* CPU 8 */
#define CPU9        0x09 /* CPU 9 */
#define CPU10       0x0A /* CPU 10 */
#define CPU11       0x0B /* CPU 11 */
#define CPU12       0x0C /* CPU 12 */
#define SMP1        0x0D /* SMP1, initially added for LRC, reused at least in FSM-r4 */
#define CPU_ALL     0x0F /* All CPUs */

/* Combined CHIPX_CPUY addresses */
#define CHIP1_CPU1  (CHIP1+CPU1) /* DSP 1 CPU 1 on BB */
#define CHIP1_CPU2  (CHIP1+CPU2) /* DSP 1 CPU 2 on BB */
#define CHIP1_CPU3  (CHIP1+CPU3) /* DSP 1 CPU 3 on BB */
#define CHIP1_CPU4  (CHIP1+CPU4) /* DSP 1 CPU 4 on BB */
#define CHIP1_CPU5  (CHIP1+CPU5) /* DSP 1 CPU 5 on BB */
#define CHIP1_CPU6  (CHIP1+CPU6) /* DSP 1 CPU 6 on BB */
#define CHIP1_CPU7  (CHIP1+CPU7) /* DSP 1 CPU 7 on BB */
#define CHIP1_CPU8  (CHIP1+CPU8) /* DSP 1 CPU 8 on BB */
#define CHIP2_CPU1  (CHIP2+CPU1) /* DSP 2 CPU 1 on BB */
#define CHIP2_CPU2  (CHIP2+CPU2) /* DSP 2 CPU 2 on BB */
#define CHIP2_CPU3  (CHIP2+CPU3) /* DSP 2 CPU 3 on BB */
#define CHIP2_CPU4  (CHIP2+CPU4) /* DSP 2 CPU 4 on BB */
#define CHIP2_CPU5  (CHIP2+CPU5) /* DSP 2 CPU 5 on BB */
#define CHIP2_CPU6  (CHIP2+CPU6) /* DSP 2 CPU 6 on BB */
#define CHIP2_CPU7  (CHIP2+CPU7) /* DSP 2 CPU 7 on BB */
#define CHIP2_CPU8  (CHIP2+CPU8) /* DSP 2 CPU 8 on BB */
#define CHIP3_CPU1  (CHIP3+CPU1) /* DSP 3 CPU 1 on BB */
#define CHIP3_CPU2  (CHIP3+CPU2) /* DSP 3 CPU 2 on BB */
#define CHIP3_CPU3  (CHIP3+CPU3) /* DSP 3 CPU 3 on BB */
#define CHIP3_CPU4  (CHIP3+CPU4) /* DSP 3 CPU 4 on BB */
#define CHIP3_CPU5  (CHIP3+CPU5) /* DSP 3 CPU 5 on BB */
#define CHIP3_CPU6  (CHIP3+CPU6) /* DSP 3 CPU 6 on BB */
#define CHIP3_CPU7  (CHIP3+CPU7) /* DSP 3 CPU 7 on BB */
#define CHIP3_CPU8  (CHIP3+CPU8) /* DSP 3 CPU 8 on BB */
#define CHIP4_CPU1  (CHIP4+CPU1) /* DSP 4 CPU 1 on BB */
#define CHIP4_CPU2  (CHIP4+CPU2) /* DSP 4 CPU 2 on BB */
#define CHIP4_CPU3  (CHIP4+CPU3) /* DSP 4 CPU 3 on BB */
#define CHIP4_CPU4  (CHIP4+CPU4) /* DSP 4 CPU 4 on BB */
#define CHIP4_CPU5  (CHIP4+CPU5) /* DSP 4 CPU 5 on BB */
#define CHIP4_CPU6  (CHIP4+CPU6) /* DSP 4 CPU 6 on BB */
#define CHIP4_CPU7  (CHIP4+CPU7) /* DSP 4 CPU 7 on BB */
#define CHIP4_CPU8  (CHIP4+CPU8) /* DSP 4 CPU 8 on BB */
#define CHIP5_CPU1  (CHIP5+CPU1) /* DSP 5 CPU 1 on BB */
#define CHIP5_CPU2  (CHIP5+CPU2) /* DSP 5 CPU 2 on BB */
#define CHIP5_CPU3  (CHIP5+CPU3) /* DSP 5 CPU 3 on BB */
#define CHIP5_CPU4  (CHIP5+CPU4) /* DSP 5 CPU 4 on BB */
#define CHIP5_CPU5  (CHIP5+CPU5) /* DSP 5 CPU 5 on BB */
#define CHIP5_CPU6  (CHIP5+CPU6) /* DSP 5 CPU 6 on BB */
#define CHIP5_CPU7  (CHIP5+CPU7) /* DSP 5 CPU 7 on BB */
#define CHIP5_CPU8  (CHIP5+CPU8) /* DSP 5 CPU 8 on BB */
#define CHIP6_CPU1  (CHIP6+CPU1) /* DSP 6 CPU 1 on BB */
#define CHIP6_CPU2  (CHIP6+CPU2) /* DSP 6 CPU 2 on BB */
#define CHIP6_CPU3  (CHIP6+CPU3) /* DSP 6 CPU 3 on BB */
#define CHIP6_CPU4  (CHIP6+CPU4) /* DSP 6 CPU 4 on BB */
#define CHIP6_CPU5  (CHIP6+CPU5) /* DSP 6 CPU 5 on BB */
#define CHIP6_CPU6  (CHIP6+CPU6) /* DSP 6 CPU 6 on BB */
#define CHIP6_CPU7  (CHIP6+CPU7) /* DSP 6 CPU 7 on BB */
#define CHIP6_CPU8  (CHIP6+CPU8) /* DSP 6 CPU 8 on BB */
#define CHIP7_CPU1  (CHIP7+CPU1) /* DSP 7 CPU 1 on BB */
#define CHIP7_CPU2  (CHIP7+CPU2) /* DSP 7 CPU 2 on BB */
#define CHIP7_CPU3  (CHIP7+CPU3) /* DSP 7 CPU 3 on BB */
#define CHIP7_CPU4  (CHIP7+CPU4) /* DSP 7 CPU 4 on BB */
#define CHIP7_CPU5  (CHIP7+CPU5) /* DSP 7 CPU 5 on BB */
#define CHIP7_CPU6  (CHIP7+CPU6) /* DSP 7 CPU 6 on BB */
#define CHIP7_CPU7  (CHIP7+CPU7) /* DSP 7 CPU 7 on BB */
#define CHIP7_CPU8  (CHIP7+CPU8) /* DSP 7 CPU 8 on BB */
#define CHIP8_CPU1  (CHIP8+CPU1) /* DSP 8 CPU 1 on BB */
#define CHIP8_CPU2  (CHIP8+CPU2) /* DSP 8 CPU 2 on BB */
#define CHIP8_CPU3  (CHIP8+CPU3) /* DSP 8 CPU 3 on BB */
#define CHIP8_CPU4  (CHIP8+CPU4) /* DSP 8 CPU 4 on BB */
#define CHIP8_CPU5  (CHIP8+CPU5) /* DSP 8 CPU 5 on BB */
#define CHIP8_CPU6  (CHIP8+CPU6) /* DSP 8 CPU 6 on BB */
#define CHIP8_CPU7  (CHIP8+CPU7) /* DSP 8 CPU 7 on BB */
#define CHIP8_CPU8  (CHIP8+CPU8) /* DSP 8 CPU 8 on BB */
#define CHIP9_CPU1  (CHIP9+CPU1) /* DSP 9 CPU 1 on BB */
#define CHIP9_CPU2  (CHIP9+CPU2) /* DSP 9 CPU 2 on BB */
#define CHIP9_CPU3  (CHIP9+CPU3) /* DSP 9 CPU 3 on BB */
#define CHIP9_CPU4  (CHIP9+CPU4) /* DSP 9 CPU 4 on BB */
#define CHIP9_CPU5  (CHIP9+CPU5) /* DSP 9 CPU 5 on BB */
#define CHIP9_CPU6  (CHIP9+CPU6) /* DSP 9 CPU 6 on BB */
#define CHIP9_CPU7  (CHIP9+CPU7) /* DSP 9 CPU 7 on BB */
#define CHIP9_CPU8  (CHIP9+CPU8) /* DSP 9 CPU 8 on BB */
/* These addresses reserved for the future use
#define CHIPA_CPU1  (CHIPA+CPU1)
#define CHIPA_CPU2  (CHIPA+CPU2)
#define CHIPA_CPU3  (CHIPA+CPU3)
#define CHIPA_CPU4  (CHIPA+CPU4)
#define CHIPA_CPU5  (CHIPA+CPU5)
#define CHIPA_CPU6  (CHIPA+CPU6)
#define CHIPA_CPU7  (CHIPA+CPU7)
#define CHIPA_CPU8  (CHIPA+CPU8)
#define CHIPB_CPU1  (CHIPB+CPU1)
#define CHIPB_CPU2  (CHIPB+CPU2)
#define CHIPB_CPU3  (CHIPB+CPU3)
#define CHIPB_CPU4  (CHIPB+CPU4)
#define CHIPB_CPU5  (CHIPB+CPU5)
#define CHIPB_CPU6  (CHIPB+CPU6)
#define CHIPB_CPU7  (CHIPB+CPU7)
#define CHIPB_CPU8  (CHIPB+CPU8)
#define CHIPC_CPU1  (CHIPC+CPU1)
#define CHIPC_CPU2  (CHIPC+CPU2)
#define CHIPC_CPU3  (CHIPC+CPU3)
#define CHIPC_CPU4  (CHIPC+CPU4)
#define CHIPC_CPU5  (CHIPC+CPU5)
#define CHIPC_CPU6  (CHIPC+CPU6)
#define CHIPC_CPU7  (CHIPC+CPU7)
#define CHIPC_CPU8  (CHIPC+CPU8)
#define CHIPD_CPU1  (CHIPD+CPU1)
#define CHIPD_CPU2  (CHIPD+CPU2)
#define CHIPD_CPU3  (CHIPD+CPU3)
#define CHIPD_CPU4  (CHIPD+CPU4)
#define CHIPD_CPU5  (CHIPD+CPU5)
#define CHIPD_CPU6  (CHIPD+CPU6)
#define CHIPD_CPU7  (CHIPD+CPU7)
#define CHIPD_CPU8  (CHIPD+CPU8)
*/

/*
 * K2 SMP1 defines for FSM-r4
 * */
#define CHIP1_SMP1 (CHIP1+SMP1)
#define CHIP2_SMP1 (CHIP2+SMP1)
#define CHIP3_SMP1 (CHIP3+SMP1)
#define CHIP4_SMP1 (CHIP4+SMP1)

#define L2X         0xCC    /* Flexi L2 switch */

#define CHIP1_EMGRP1  0x3A  /* K2A ARM real-time node */
#define CHIP2_EMGRP1  0x4A  /* K2B ARM real-time node */
#define CHIP3_EMGRP1  0x5A  /* K2C ARM real-time node */
#define CHIP4_EMGRP1  0x6A  /* K2D ARM real-time node */

#define CHIP1_CPU_ALL 0x3F  /* All K2A DSP cores */
#define CHIP2_CPU_ALL 0x4F  /* All K2B DSP cores */
#define CHIP3_CPU_ALL 0x5F  /* All K2C DSP cores */
#define CHIP4_CPU_ALL 0x6F  /* All K2D DSP cores */

/* ***************************************************************************/
/* NodeId definitions:                                                       */
/* In CC&S syscom addressing the NodeId is a 16-bit value. For backwards     */
/* compatibility the old reserved BoardId+CpuId can be used as the           */
/* sysCom Nid. As the boardId range seems to be exhausting quite soon        */
/* if we continue to allocate a new boardId always when a new Nid is needed  */
/* it is adviced to instead to re-use the boardId's as much as possible to   */
/* save the boardId address space. Here are defined Nid's for those units    */
/* which re-use a previously defined BoardId                                 */
/* If needed the AaSysCom interface functions can be used to extract boardId */
/* and CpuId from the given Nid                                              */
/* Notice that list below this comment does not list all reserved Nid's as   */
/* you also have to look at the old BoardId+CpuId combinations               */

#define MAC_PDU_DUMP_NID 0xE701 /* NodeId for LTE MacPduDump tool */

/* GENIO Reset register outputs, defined as CPU's even if are not such */
#define RESET_ENABLE 0x45    /* Reset primary subnode 0 */
#define PRIMARY_ENA 0x45    /* Reset primary subnode 0*/
#define CIF_CK_SEL  0x46    /* CIF_CK_SEL select's the UX asic reference clock source */


/*****************************************************************************/
/* Board's physical addresses in DSC-bus definitions. Address is 8 bit wide,
first 4 bits (MSB) is BSA address and second 4 bits (LSB) is BNA address */

/* WSP boards */
#define WSP_10_DSC_ADDR     0x12    /* Rack 1, Wideband Signal Processor 0 */
#define WSP_11_DSC_ADDR     0x13    /* Rack 1, Wideband Signal Processor 1 */
#define WSP_12_DSC_ADDR     0x14    /* Rack 1, Wideband Signal Processor 2 */
#define WSP_13_DSC_ADDR     0x15    /* Rack 1, Wideband Signal Processor 3 */
#define WSP_14_DSC_ADDR     0x16    /* Rack 1, Wideband Signal Processor 4 */
#define WSP_15_DSC_ADDR     0x17    /* Rack 1, Wideband Signal Processor 5 */
#define WSP_20_DSC_ADDR     0x22    /* Rack 2, Wideband Signal Processor 0 */
#define WSP_21_DSC_ADDR     0x23    /* Rack 2, Wideband Signal Processor 1 */
#define WSP_22_DSC_ADDR     0x24    /* Rack 2, Wideband Signal Processor 2 */
#define WSP_23_DSC_ADDR     0x25    /* Rack 2, Wideband Signal Processor 3 */
#define WSP_24_DSC_ADDR     0x26    /* Rack 2, Wideband Signal Processor 4 */
#define WSP_25_DSC_ADDR     0x27    /* Rack 2, Wideband Signal Processor 5 */
#define WSP_30_DSC_ADDR     0x32    /* Rack 3, Wideband Signal Processor 0 */
#define WSP_31_DSC_ADDR     0x33    /* Rack 3, Wideband Signal Processor 1 */
#define WSP_32_DSC_ADDR     0x34    /* Rack 3, Wideband Signal Processor 2 */
#define WSP_33_DSC_ADDR     0x35    /* Rack 3, Wideband Signal Processor 3 */
#define WSP_34_DSC_ADDR     0x36    /* Rack 3, Wideband Signal Processor 4 */
#define WSP_35_DSC_ADDR     0x37    /* Rack 3, Wideband Signal Processor 5 */

/* WAM boards */
#define WAM_10_DSC_ADDR     0x10    /* Rack 1, Wideband Application Manager 0 */
#define WAM_11_DSC_ADDR     0x11    /* Rack 1, Wideband Application Manager 1 */
#define WAM_20_DSC_ADDR     0x20    /* Rack 2, Wideband Application Manager 0 */
#define WAM_21_DSC_ADDR     0x21    /* Rack 2, Wideband Application Manager 1 */
#define WAM_30_DSC_ADDR     0x30    /* Rack 3, Wideband Application Manager 0 */
#define WAM_31_DSC_ADDR     0x31    /* Rack 3, Wideband Application Manager 1 */


/**********************************************************************************/
/* CPU's physical addresses in AIF-bus definitions. CPU is an active processor or a passive device
Address is 8 bit wide, first 4 bits (MSB) are not used as an address and second 4 bits (LSB) is NSA address  */

/* WSP processors */
#define RAKE_1_AIF_ADDR         0x01    /* WSP RAKE1 */
#define RAKE_2_AIF_ADDR         0x02    /* WSP RAKE2 */
#define RAKE_3_AIF_ADDR         0x03    /* WSP RAKE3 */
#define RAKE_4_AIF_ADDR         0x04    /* WSP RAKE4 */
#define CODEC_1_AIF_ADDR        0x05    /* WSP CODEC1 */
#define CODEC_2_AIF_ADDR        0x06    /* WSP CODEC2 */
#define CODEC_3_AIF_ADDR        0x07    /* WSP CODEC3 */
#define CODEC_4_AIF_ADDR        0x08    /* WSP CODEC4 */
#define WSP_MCU_AIF_ADDR        0x0D    /* WSP MCU */

#define WSPC_RAKE_1_AIF_ADDR     0x01   /* WSPC RAKE1 */
#define WSPC_RAKE_2_AIF_ADDR     0x02   /* WSPC RAKE2 */
#define WSPC_RAKE_3_AIF_ADDR     0x03   /* WSPC RAKE3 */
#define WSPC_RAKE_4_AIF_ADDR     0x04   /* WSPC RAKE4, reserved for the future use */
#define WSPC_CODEC_1_AIF_ADDR    0x05   /* WSPC CODEC1 */
#define WSPC_CODEC_2_AIF_ADDR    0x06   /* WSPC CODEC2, reserved for the future use */
#define WSPC_CODEC_3_AIF_ADDR    0x07   /* WSPC CODEC3, reserved for the future use */
#define WSPC_CODEC_4_AIF_ADDR    0x08   /* WSPC CODEC4, reserved for the future use */
#define WSPC_MCU_AIF_ADDR        0x0D   /* WSPC MCU */

/* WAM processors */
#define CTRL_MCU_AIF_ADDR       0x01    /* WAM O&M MCU */
#define TCOM_MCU_AIF_ADDR       0x01    /* WAM Telecom MCU. NOTE: the same as O&M processor */
#define ATM1_MCU_AIF_ADDR       0x07    /* WAM AAL2 MCU1 */
#define ATM2_MCU_AIF_ADDR       0x0A    /* WAM AAL2 MCU2 */
#define ATM3_MCU_AIF_ADDR       0x0D    /* WAM AAL2 MCU3 */
#define ATMHOST_MCU_AIF_ADDR    0x04    /* WAM ATM host MCU */

/* Other aif-bus addresses*/
#define DSC_ASIC_AIF_ADDR       0x00    /* DSC-ASIC's AIF-BUS address is same at WAM and WSP */
#define DNBAP_AIF_ADDR          0x04    /* DNBAP ATM channel to RNC */
#define CNBAP_AIF_ADDR          0x04    /* CNBAP ATM channel to RNC */
#define AAL2S_AIF_ADDR          0x04    /* ATM internal channel to RNC */


/*************************************************************************/
/* Unit's IP and MAC addresses, and port numbers */

/* Default gateway for BS subnet */
#define BS_DEFAULT_GATEWAY "192.168.255.32"

/* Default gateway for LMT subnet */
#define LMT_DEFAULT_GATEWAY "192.168.255.129"

/* Mask for BS subnet */
#define BS_SUBNETMASK "255.255.255.128"

/* Mask for LMT subnet */
#define LMT_SUBNETMASK "255.255.255.128"

/* Mask for RNC subnet */
#define RNC_SUBNETMASK "255.255.255.255"

/* Subnet mask for Flexi */
#define FLEXI_SUBNETMASK "255.255.254.0"

/* LMT IP address */
#define LMT_IP_ADDR "192.168.255.130"

/* LMP/AXU IP address */
#define LMP_AXU_IP_ADDR "192.168.255.129"

/* WAM CTRL_MCU IP addresses */
#define WAM_10_IP_ADDR  "192.168.255.1"
#define WAM_11_IP_ADDR  "192.168.255.2"
#define WAM_20_IP_ADDR  "192.168.255.3"
#define WAM_21_IP_ADDR  "192.168.255.4"
#define WAM_30_IP_ADDR  "192.168.255.5"
#define WAM_31_IP_ADDR  "192.168.255.6"

/* WPA IP addresses */
#define WPA_10_IP_ADDR  "192.168.255.21"
#define WPA_11_IP_ADDR  "192.168.255.23"
#define WPA_20_IP_ADDR  "192.168.255.25"
#define WPA_21_IP_ADDR  "192.168.255.27"
#define WPA_30_IP_ADDR  "192.168.255.29"
#define WPA_31_IP_ADDR  "192.168.255.31"

/* WTR IP addresses */
#define WTR_10_IP_ADDR  "192.168.255.20"
#define WTR_11_IP_ADDR  "192.168.255.22"
#define WTR_20_IP_ADDR  "192.168.255.24"
#define WTR_21_IP_ADDR  "192.168.255.26"
#define WTR_30_IP_ADDR  "192.168.255.28"
#define WTR_31_IP_ADDR  "192.168.255.30"

/* WSP_MCU IP addresses */
#define WSP_10_IP_ADDR  "192.168.255.33"
#define WSP_11_IP_ADDR  "192.168.255.34"
#define WSP_12_IP_ADDR  "192.168.255.35"
#define WSP_13_IP_ADDR  "192.168.255.36"
#define WSP_14_IP_ADDR  "192.168.255.37"
#define WSP_15_IP_ADDR  "192.168.255.38"
#define WSP_20_IP_ADDR  "192.168.255.39"
#define WSP_21_IP_ADDR  "192.168.255.40"
#define WSP_22_IP_ADDR  "192.168.255.41"
#define WSP_23_IP_ADDR  "192.168.255.42"
#define WSP_24_IP_ADDR  "192.168.255.43"
#define WSP_25_IP_ADDR  "192.168.255.44"
#define WSP_30_IP_ADDR  "192.168.255.45"
#define WSP_31_IP_ADDR  "192.168.255.46"
#define WSP_32_IP_ADDR  "192.168.255.47"
#define WSP_33_IP_ADDR  "192.168.255.48"
#define WSP_34_IP_ADDR  "192.168.255.49"
#define WSP_35_IP_ADDR  "192.168.255.50"


/* WAM ATMHOST_MCU IP addresses */
#define ATMHOST_10_IP_ADDR  "192.168.255.7"
#define ATMHOST_11_IP_ADDR  "192.168.255.8"
#define ATMHOST_20_IP_ADDR  "192.168.255.9"
#define ATMHOST_21_IP_ADDR  "192.168.255.10"
#define ATMHOST_30_IP_ADDR  "192.168.255.11"
#define ATMHOST_31_IP_ADDR  "192.168.255.12"

/* O&M Master IP address */
#define OAM_MASTER_IP_ADDRESS   "192.168.255.16"
#define OAM_MASTER_IP_ADDRESS_CPRI   "13.64.1.1"  //TD-LTE BBU IP in dual mode

/* Literal for Base Station's public IP address. O&M Master's "resource */
/* manager" gets the address from the database and sets it to the variable */
#define BS_PUBLIC_IP_ADDRESS    bs_public_ip_address

/* Literal for "my own" IP address. Variable is set by INET_API_TASK */
/* after the current board is found out. Literal is ready for usage after */
/* INET_API_TASK has sent API_INET_OK_MSG to O&M autodetection */
#define MY_IP_ADDRESS my_ip_address

/* AXU IP address */
#define AXU_IP_ADDR "192.168.255.32"

/* AXC1 IP address */
#define AXC1_IP_ADDR "192.168.255.116"

/* Flexi IP addresses */
#define FSM_FCM_IP_ADDR    WAM_10_IP_ADDR    /* Flexi System Module, FCM IP address, will be removed in INC5 !!! */
#define FSM_FT_IP_ADDR     "192.168.255.129" /* Flexi Transport IP address, will be removed in INC5 !!! */
#define FSM_FSP1_IP_ADDR   WSP_10_IP_ADDR    /* Flexi Signal Processing 1 IP address, will be removed in INC5 !!! */
#define FSM_FSP2_IP_ADDR   WSP_11_IP_ADDR    /* Flexi Signal Processing 2 IP address, will be removed in INC5 !!! */
#define FSM_FSP3_IP_ADDR   WSP_12_IP_ADDR    /* Flexi Signal Processing 3 IP address, will be removed in INC5 !!! */

#define FSM1_FCM_IP_ADDR    WAM_10_IP_ADDR    /* Flexi System Module, FCM IP address */
#define FSM1_FT_IP_ADDR     "192.168.255.129" /* Flexi Transport Module 1 IP address */
#define FSM1_FSP1_IP_ADDR   WSP_10_IP_ADDR    /* Flexi System Module, Signal Processing 1 IP address */
#define FSM1_FSP2_IP_ADDR   WSP_11_IP_ADDR    /* Flexi System Module, Signal Processing 2 IP address */
#define FSM1_FSP3_IP_ADDR   WSP_12_IP_ADDR    /* Flexi System Module, Signal Processing 3 IP address */

#define FSM2_FCM_IP_ADDR    WAM_20_IP_ADDR    /* Flexi Extension Module 1, FCM IP address */
#define FSM2_FT_IP_ADDR     "192.168.255.128" /* FTM2 IP address */
#define FSM2_FSP1_IP_ADDR   WSP_20_IP_ADDR    /* Flexi Extension Module 1, Signal Processing 1 IP address */
#define FSM2_FSP2_IP_ADDR   WSP_21_IP_ADDR    /* Flexi Extension Module 1, Signal Processing 2 IP address */
#define FSM2_FSP3_IP_ADDR   WSP_22_IP_ADDR    /* Flexi Extension Module 1, Signal Processing 3 IP address */

#define FSM3_FCM_IP_ADDR    WAM_30_IP_ADDR    /* Flexi Extension Module 2, FCM IP address */
#define FSM3_FT_IP_ADDR     "192.168.255.127" /* FTM3 IP address */
#define FSM3_FSP1_IP_ADDR   WSP_30_IP_ADDR    /* Flexi Extension Module 2, Signal Processing 1 IP address */
#define FSM3_FSP2_IP_ADDR   WSP_31_IP_ADDR    /* Flexi Extension Module 2, Signal Processing 2 IP address */
#define FSM3_FSP3_IP_ADDR   WSP_32_IP_ADDR    /* Flexi Extension Module 2, Signal Processing 3 IP address */

#define FR1_IP_ADDR "192.168.255.69"         /* Flexi RF Module 1 IP address */
#define FR1_FF1_IP_ADDR "192.168.255.70"     /* Flexi RF Module 1, Flexi Filter1 (STuF) IP address */
#define FR1_FF2_IP_ADDR "192.168.255.71"     /* Flexi RF Module 1, Flexi Filter2 (STuF) IP address */
#define FR1_FF3_IP_ADDR "192.168.255.72"     /* Flexi RF Module 1, Flexi Filter3 (STuF) IP address */

#define FR2_IP_ADDR "192.168.255.73"         /* Flexi RF Module 2 IP address */
#define FR2_FF1_IP_ADDR "192.168.255.74"     /* Flexi RF Module 2, Flexi Filter1 (STuF) IP address */
#define FR2_FF2_IP_ADDR "192.168.255.75"     /* Flexi RF Module 2, Flexi Filter2 (STuF) IP address */
#define FR2_FF3_IP_ADDR "192.168.255.76"     /* Flexi RF Module 2, Flexi Filter3 (STuF) IP address */

#define FR3_IP_ADDR "192.168.255.77"         /* Flexi RF Module 3 IP address */
#define FR3_FF1_IP_ADDR "192.168.255.78"     /* Flexi RF Module 3, Flexi Filter1 (STuF) IP address */
#define FR3_FF2_IP_ADDR "192.168.255.79"     /* Flexi RF Module 3, Flexi Filter2 (STuF) IP address */
#define FR3_FF3_IP_ADDR "192.168.255.80"     /* Flexi RF Module 3, Flexi Filter3 (STuF) IP address */

/* RRU ip in dual mode*/
#define CPRI_FR1_1_1_IP_ADDR1 "13.0.12.1"  /* dual mode RF Module connected to FSM 1 optif 1 position 1 */
#define CPRI_FR1_1_1_IP_ADDR2 "13.0.13.1"  /* dual mode RF Module connected to FSM 1 optif 2 position 1 */
#define CPRI_FR1_2_1_IP_ADDR1 "13.0.18.1"  /* dual mode RF Module connected to FSM 1 optif 3 position 1 */
#define CPRI_FR1_2_1_IP_ADDR2 "13.0.25.1"  /* dual mode RF Module connected to FSM 1 optif 6 position 1 */
#define CPRI_FR1_3_1_IP_ADDR1 "13.0.19.1"  /* dual mode RF Module connected to FSM 1 optif 4 position 1 */
#define CPRI_FR1_3_1_IP_ADDR2 "13.0.24.1"  /* dual mode RF Module connected to FSM 1 optif 5 position 1 */

/* Radio module IP addresses */
#define FR1_1_1_IP_ADDR "192.168.254.129"  /* Flexi RF Module connected to FSM 1 optif 1 position 1 */
#define FR1_1_2_IP_ADDR "192.168.254.130"  /* Flexi RF Module connected to FSM 1 optif 1 position 2 */
#define FR1_1_3_IP_ADDR "192.168.254.131"  /* Flexi RF Module connected to FSM 1 optif 1 position 3 */
#define FR1_1_4_IP_ADDR "192.168.254.132"  /* Flexi RF Module connected to FSM 1 optif 1 position 4 */
#define FR1_2_1_IP_ADDR "192.168.254.133"  /* Flexi RF Module connected to FSM 1 optif 2 position 1 */
#define FR1_2_2_IP_ADDR "192.168.254.134"  /* Flexi RF Module connected to FSM 1 optif 2 position 2 */
#define FR1_2_3_IP_ADDR "192.168.254.135"  /* Flexi RF Module connected to FSM 1 optif 2 position 3 */
#define FR1_2_4_IP_ADDR "192.168.254.136"  /* Flexi RF Module connected to FSM 1 optif 2 position 4 */
#define FR1_3_1_IP_ADDR "192.168.254.137"  /* Flexi RF Module connected to FSM 1 optif 3 position 1 */
#define FR1_3_2_IP_ADDR "192.168.254.138"  /* Flexi RF Module connected to FSM 1 optif 3 position 2 */
#define FR1_3_3_IP_ADDR "192.168.254.139"  /* Flexi RF Module connected to FSM 1 optif 3 position 3 */
#define FR1_3_4_IP_ADDR "192.168.254.140"  /* Flexi RF Module connected to FSM 1 optif 3 position 4 */
#define FR1_4_1_IP_ADDR "192.168.254.141"  /* Flexi RF Module connected to FSM 1 optif 4 position 1 */
#define FR1_4_2_IP_ADDR "192.168.254.142"  /* Flexi RF Module connected to FSM 1 optif 4 position 2 */
#define FR1_4_3_IP_ADDR "192.168.254.143"  /* Flexi RF Module connected to FSM 1 optif 4 position 3 */
#define FR1_4_4_IP_ADDR "192.168.254.144"  /* Flexi RF Module connected to FSM 1 optif 4 position 4 */
#define FR1_5_1_IP_ADDR "192.168.254.145"  /* Flexi RF Module connected to FSM 1 optif 5 position 1 */
#define FR1_5_2_IP_ADDR "192.168.254.146"  /* Flexi RF Module connected to FSM 1 optif 5 position 2 */
#define FR1_5_3_IP_ADDR "192.168.254.147"  /* Flexi RF Module connected to FSM 1 optif 5 position 3 */
#define FR1_5_4_IP_ADDR "192.168.254.148"  /* Flexi RF Module connected to FSM 1 optif 5 position 4 */
#define FR1_6_1_IP_ADDR "192.168.254.149"  /* Flexi RF Module connected to FSM 1 optif 6 position 1 */
#define FR1_6_2_IP_ADDR "192.168.254.150"  /* Flexi RF Module connected to FSM 1 optif 6 position 2 */
#define FR1_6_3_IP_ADDR "192.168.254.151"  /* Flexi RF Module connected to FSM 1 optif 6 position 3 */
#define FR1_6_4_IP_ADDR "192.168.254.152"  /* Flexi RF Module connected to FSM 1 optif 6 position 4 */
#define FR2_1_1_IP_ADDR "192.168.254.177"  /* Flexi RF Module connected to FSM 2 optif 1 position 1 */
#define FR2_1_2_IP_ADDR "192.168.254.178"  /* Flexi RF Module connected to FSM 2 optif 1 position 2 */
#define FR2_1_3_IP_ADDR "192.168.254.179"  /* Flexi RF Module connected to FSM 2 optif 1 position 3 */
#define FR2_1_4_IP_ADDR "192.168.254.180"  /* Flexi RF Module connected to FSM 2 optif 1 position 4 */
#define FR2_2_1_IP_ADDR "192.168.254.181"  /* Flexi RF Module connected to FSM 2 optif 2 position 1 */
#define FR2_2_2_IP_ADDR "192.168.254.182"  /* Flexi RF Module connected to FSM 2 optif 2 position 2 */
#define FR2_2_3_IP_ADDR "192.168.254.183"  /* Flexi RF Module connected to FSM 2 optif 2 position 3 */
#define FR2_2_4_IP_ADDR "192.168.254.184"  /* Flexi RF Module connected to FSM 2 optif 2 position 4 */
#define FR2_3_1_IP_ADDR "192.168.254.185"  /* Flexi RF Module connected to FSM 2 optif 3 position 1 */
#define FR2_3_2_IP_ADDR "192.168.254.186"  /* Flexi RF Module connected to FSM 2 optif 3 position 2 */
#define FR2_3_3_IP_ADDR "192.168.254.187"  /* Flexi RF Module connected to FSM 2 optif 3 position 3 */
#define FR2_3_4_IP_ADDR "192.168.254.188"  /* Flexi RF Module connected to FSM 2 optif 3 position 4 */
#define FR2_4_1_IP_ADDR "192.168.254.189"  /* Flexi RF Module connected to FSM 2 optif 4 position 1 */
#define FR2_4_2_IP_ADDR "192.168.254.190"  /* Flexi RF Module connected to FSM 2 optif 4 position 2 */
#define FR2_4_3_IP_ADDR "192.168.254.191"  /* Flexi RF Module connected to FSM 2 optif 4 position 3 */
#define FR2_4_4_IP_ADDR "192.168.254.192"  /* Flexi RF Module connected to FSM 2 optif 4 position 4 */
#define FR2_5_1_IP_ADDR "192.168.254.193"  /* Flexi RF Module connected to FSM 2 optif 5 position 1 */
#define FR2_5_2_IP_ADDR "192.168.254.194"  /* Flexi RF Module connected to FSM 2 optif 5 position 2 */
#define FR2_5_3_IP_ADDR "192.168.254.195"  /* Flexi RF Module connected to FSM 2 optif 5 position 3 */
#define FR2_5_4_IP_ADDR "192.168.254.196"  /* Flexi RF Module connected to FSM 2 optif 5 position 4 */
#define FR2_6_1_IP_ADDR "192.168.254.197"  /* Flexi RF Module connected to FSM 2 optif 6 position 1 */
#define FR2_6_2_IP_ADDR "192.168.254.198"  /* Flexi RF Module connected to FSM 2 optif 6 position 2 */
#define FR2_6_3_IP_ADDR "192.168.254.199"  /* Flexi RF Module connected to FSM 2 optif 6 position 3 */
#define FR2_6_4_IP_ADDR "192.168.254.200"  /* Flexi RF Module connected to FSM 2 optif 6 position 4 */
#define FR4_IP_ADDR "192.168.255.81"  /* Flexi RF Module 4 IP address */
#define FR4_FF1_IP_ADDR "192.168.255.82"  /* Flexi RF Module 4, Flexi Filter1 (STuF) IP address */
#define FR4_FF2_IP_ADDR "192.168.255.83"  /* Flexi RF Module 4, Flexi Filter2 (STuF) IP address */
#define FR4_FF3_IP_ADDR "192.168.255.84"  /* Flexi RF Module 4, Flexi Filter3 (STuF) IP address */
#define FR5_IP_ADDR "192.168.255.85"  /* Flexi RF Module 5 IP address */
#define FR5_FF1_IP_ADDR "192.168.255.86"  /* Flexi RF Module 5, Flexi Filter1 (STuF) IP address */
#define FR5_FF2_IP_ADDR "192.168.255.87"  /* Flexi RF Module 5, Flexi Filter2 (STuF) IP address */
#define FR5_FF3_IP_ADDR "192.168.255.88"  /* Flexi RF Module 5, Flexi Filter3 (STuF) IP address */
#define FR6_IP_ADDR "192.168.255.89"  /* Flexi RF Module 6 IP address */
#define FR6_FF1_IP_ADDR "192.168.255.90"  /* Flexi RF Module 6, Flexi Filter1 (STuF) IP address */
#define FR6_FF2_IP_ADDR "192.168.255.91"  /* Flexi RF Module 6, Flexi Filter2 (STuF) IP address */
#define FR6_FF3_IP_ADDR "192.168.255.92"  /* Flexi RF Module 6, Flexi Filter3 (STuF) IP address */
#define FR1_4_1_SHARED_IP_ADDR "192.168.254.10"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_4_2_SHARED_IP_ADDR "192.168.254.11"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_4_3_SHARED_IP_ADDR "192.168.254.12"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_1_1_FF_IP_ADDR "192.168.254.153"  /* Filter of Radio Module connected to FSM 1 optif  1 position 1 */
#define FR1_1_2_FF_IP_ADDR "192.168.254.154"  /* Filter of Radio Module connected to FSM 1 optif  1 position 2 */
#define FR1_1_3_FF_IP_ADDR "192.168.254.155"  /* Filter of Radio Module connected to FSM 1 optif  1 position 3 */
#define FR1_1_4_FF_IP_ADDR "192.168.254.156"  /* Filter of Radio Module connected to FSM 1 optif  1 position 4 */
#define FR1_2_1_FF_IP_ADDR "192.168.254.157"  /* Filter of Radio Module connected to FSM 1 optif  2 position 1 */
#define FR1_2_2_FF_IP_ADDR "192.168.254.158"  /* Filter of Radio Module connected to FSM 1 optif  2 position 2 */
#define FR1_2_3_FF_IP_ADDR "192.168.254.159"  /* Filter of Radio Module connected to FSM 1 optif  2 position 3 */
#define FR1_2_4_FF_IP_ADDR "192.168.254.160"  /* Filter of Radio Module connected to FSM 1 optif  2 position 4 */
#define FR1_3_1_FF_IP_ADDR "192.168.254.161"  /* Filter of Radio Module connected to FSM 1 optif  3 position 1 */
#define FR1_3_2_FF_IP_ADDR "192.168.254.162"  /* Filter of Radio Module connected to FSM 1 optif  3 position 2 */
#define FR1_3_3_FF_IP_ADDR "192.168.254.163"  /* Filter of Radio Module connected to FSM 1 optif  3 position 3 */
#define FR1_3_4_FF_IP_ADDR "192.168.254.164"  /* Filter of Radio Module connected to FSM 1 optif  3 position 4 */
#define FR1_4_1_FF_IP_ADDR "192.168.254.165"  /* Filter of Radio Module connected to FSM 1 optif  4 position 1 */
#define FR1_4_2_FF_IP_ADDR "192.168.254.166"  /* Filter of Radio Module connected to FSM 1 optif  4 position 2 */
#define FR1_4_3_FF_IP_ADDR "192.168.254.167"  /* Filter of Radio Module connected to FSM 1 optif  4 position 3 */
#define FR1_4_4_FF_IP_ADDR "192.168.254.168"  /* Filter of Radio Module connected to FSM 1 optif  4 position 4 */
#define FR1_5_1_FF_IP_ADDR "192.168.254.169"  /* Filter of Radio Module connected to FSM 1 optif  5 position 1 */
#define FR1_5_2_FF_IP_ADDR "192.168.254.170"  /* Filter of Radio Module connected to FSM 1 optif  5 position 2 */
#define FR1_5_3_FF_IP_ADDR "192.168.254.171"  /* Filter of Radio Module connected to FSM 1 optif  5 position 3 */
#define FR1_5_4_FF_IP_ADDR "192.168.254.172"  /* Filter of Radio Module connected to FSM 1 optif  5 position 4 */
#define FR1_6_1_FF_IP_ADDR "192.168.254.173"  /* Filter of Radio Module connected to FSM 1 optif  6 position 1 */
#define FR1_6_2_FF_IP_ADDR "192.168.254.174"  /* Filter of Radio Module connected to FSM 1 optif  6 position 2 */
#define FR1_6_3_FF_IP_ADDR "192.168.254.175"  /* Filter of Radio Module connected to FSM 1 optif  6 position 3 */
#define FR1_6_4_FF_IP_ADDR "192.168.254.176"  /* Filter of Radio Module connected to FSM 1 optif  6 position 4 */
#define FR1_4_1_FF1_SHARED_IP_ADDR "192.168.254.22"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_4_1_FF2_SHARED_IP_ADDR "192.168.254.34"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_4_2_FF1_SHARED_IP_ADDR "192.168.254.23"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_4_2_FF2_SHARED_IP_ADDR "192.168.254.35"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_4_3_FF1_SHARED_IP_ADDR "192.168.254.24"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_4_3_FF2_SHARED_IP_ADDR "192.168.254.36"  /* Can be used for shared and 2G dedicated Filters */
#define FR2_1_1_FF_IP_ADDR "192.168.254.201"  /* Filter of Radio Module connected to FSM 2 optif  1 position 1 */
#define FR2_1_2_FF_IP_ADDR "192.168.254.202"  /* Filter of Radio Module connected to FSM 2 optif  1 position 2 */
#define FR2_1_3_FF_IP_ADDR "192.168.254.203"  /* Filter of Radio Module connected to FSM 2 optif  1 position 3 */
#define FR2_1_4_FF_IP_ADDR "192.168.254.204"  /* Filter of Radio Module connected to FSM 2 optif  1 position 4 */
#define FR2_2_1_FF_IP_ADDR "192.168.254.205"  /* Filter of Radio Module connected to FSM 2 optif  2 position 1 */
#define FR2_2_2_FF_IP_ADDR "192.168.254.206"  /* Filter of Radio Module connected to FSM 2 optif  2 position 2 */
#define FR2_2_3_FF_IP_ADDR "192.168.254.207"  /* Filter of Radio Module connected to FSM 2 optif  2 position 3 */
#define FR2_2_4_FF_IP_ADDR "192.168.254.208"  /* Filter of Radio Module connected to FSM 2 optif  2 position 4 */
#define FR2_3_1_FF_IP_ADDR "192.168.254.209"  /* Filter of Radio Module connected to FSM 2 optif  3 position 1 */
#define FR2_3_2_FF_IP_ADDR "192.168.254.210"  /* Filter of Radio Module connected to FSM 2 optif  3 position 2 */
#define FR2_3_3_FF_IP_ADDR "192.168.254.211"  /* Filter of Radio Module connected to FSM 2 optif  3 position 3 */
#define FR2_3_4_FF_IP_ADDR "192.168.254.212"  /* Filter of Radio Module connected to FSM 2 optif  3 position 4 */

#define FR1_1_1_SHARED_IP_ADDR "192.168.254.1" /* Can be used for shared and 2G dedicated FRs */
#define FR1_1_2_SHARED_IP_ADDR "192.168.254.2" /* Can be used for shared and 2G dedicated FRs */
#define FR1_1_3_SHARED_IP_ADDR "192.168.254.3" /* Can be used for shared and 2G dedicated FRs */

#define FR1_2_1_SHARED_IP_ADDR "192.168.254.4" /* Can be used for shared and 2G dedicated FRs */
#define FR1_2_2_SHARED_IP_ADDR "192.168.254.5" /* Can be used for shared and 2G dedicated FRs */
#define FR1_2_3_SHARED_IP_ADDR "192.168.254.6" /* Can be used for shared and 2G dedicated FRs */

#define FR1_3_1_SHARED_IP_ADDR "192.168.254.7" /* Can be used for shared and 2G dedicated FRs */
#define FR1_3_2_SHARED_IP_ADDR "192.168.254.8" /* Can be used for shared and 2G dedicated FRs */
#define FR1_3_3_SHARED_IP_ADDR "192.168.254.9" /* Can be used for shared and 2G dedicated FRs */

//LTE934-c1
#define FR1_5_1_SHARED_IP_ADDR "192.168.254.37" /* Can be used for shared and 2G dedicated FRs */
#define FR1_5_2_SHARED_IP_ADDR "192.168.254.38" /* Can be used for shared and 2G dedicated FRs */
#define FR1_5_3_SHARED_IP_ADDR "192.168.254.39" /* Can be used for shared and 2G dedicated FRs */

#define FR1_6_1_SHARED_IP_ADDR "192.168.254.40" /* Can be used for shared and 2G dedicated FRs */
#define FR1_6_2_SHARED_IP_ADDR "192.168.254.41" /* Can be used for shared and 2G dedicated FRs */
#define FR1_6_3_SHARED_IP_ADDR "192.168.254.42" /* Can be used for shared and 2G dedicated FRs */

#define FR1_1_1_FF1_SHARED_IP_ADDR "192.168.254.13" /* Can be used for shared and 2G dedicated Filters */
#define FR1_1_2_FF1_SHARED_IP_ADDR "192.168.254.14" /* Can be used for shared and 2G dedicated Filters */
#define FR1_1_3_FF1_SHARED_IP_ADDR "192.168.254.15" /* Can be used for shared and 2G dedicated Filters */

#define FR1_2_1_FF1_SHARED_IP_ADDR "192.168.254.16" /* Can be used for shared and 2G dedicated Filters */
#define FR1_2_2_FF1_SHARED_IP_ADDR "192.168.254.17" /* Can be used for shared and 2G dedicated Filters */
#define FR1_2_3_FF1_SHARED_IP_ADDR "192.168.254.18" /* Can be used for shared and 2G dedicated Filters */

#define FR1_3_1_FF1_SHARED_IP_ADDR "192.168.254.19" /* Can be used for shared and 2G dedicated Filters */
#define FR1_3_2_FF1_SHARED_IP_ADDR "192.168.254.20" /* Can be used for shared and 2G dedicated Filters */
#define FR1_3_3_FF1_SHARED_IP_ADDR "192.168.254.21" /* Can be used for shared and 2G dedicated Filters */

#define FR1_1_1_FF2_SHARED_IP_ADDR "192.168.254.25" /* Can be used for shared and 2G dedicated Filters */
#define FR1_1_2_FF2_SHARED_IP_ADDR "192.168.254.26" /* Can be used for shared and 2G dedicated Filters */
#define FR1_1_3_FF2_SHARED_IP_ADDR "192.168.254.27" /* Can be used for shared and 2G dedicated Filters */

#define FR1_2_1_FF2_SHARED_IP_ADDR "192.168.254.28" /* Can be used for shared and 2G dedicated Filters */
#define FR1_2_2_FF2_SHARED_IP_ADDR "192.168.254.29" /* Can be used for shared and 2G dedicated Filters */
#define FR1_2_3_FF2_SHARED_IP_ADDR "192.168.254.30" /* Can be used for shared and 2G dedicated Filters */

#define FR1_3_1_FF2_SHARED_IP_ADDR "192.168.254.31" /* Can be used for shared and 2G dedicated Filters */
#define FR1_3_2_FF2_SHARED_IP_ADDR "192.168.254.32" /* Can be used for shared and 2G dedicated Filters */
#define FR1_3_3_FF2_SHARED_IP_ADDR "192.168.254.33" /* Can be used for shared and 2G dedicated Filters */

//LTE934-c1
#define FR1_5_1_FF1_SHARED_IP_ADDR "192.168.254.43"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_5_2_FF1_SHARED_IP_ADDR "192.168.254.45"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_5_3_FF1_SHARED_IP_ADDR "192.168.254.47"  /* Can be used for shared and 2G dedicated Filters */

#define FR1_5_1_FF2_SHARED_IP_ADDR "192.168.254.44"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_5_2_FF2_SHARED_IP_ADDR "192.168.254.46"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_5_3_FF2_SHARED_IP_ADDR "192.168.254.48"  /* Can be used for shared and 2G dedicated Filters */

#define FR1_6_1_FF1_SHARED_IP_ADDR "192.168.254.49"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_6_2_FF1_SHARED_IP_ADDR "192.168.254.51"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_6_3_FF1_SHARED_IP_ADDR "192.168.254.53"  /* Can be used for shared and 2G dedicated Filters */

#define FR1_6_1_FF2_SHARED_IP_ADDR "192.168.254.50"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_6_2_FF2_SHARED_IP_ADDR "192.168.254.52"  /* Can be used for shared and 2G dedicated Filters */
#define FR1_6_3_FF2_SHARED_IP_ADDR "192.168.254.54"  /* Can be used for shared and 2G dedicated Filters */

/* Flexi FRs MAC Addresses*/
#define FR1_1_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x11
#define FR1_1_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x12
#define FR1_1_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x13
#define FR1_1_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x14

#define FR1_2_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x21
#define FR1_2_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x22
#define FR1_2_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x23
#define FR1_2_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x24

#define FR1_3_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x31
#define FR1_3_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x32
#define FR1_3_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x33
#define FR1_3_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x34

#define FR1_4_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x41
#define FR1_4_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x42
#define FR1_4_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x43
#define FR1_4_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x44

#define FR1_5_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x51
#define FR1_5_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x52
#define FR1_5_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x53
#define FR1_5_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x54

#define FR1_6_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x61
#define FR1_6_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x62
#define FR1_6_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x63
#define FR1_6_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x01, 0x64

#define FR2_1_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x11
#define FR2_1_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x12
#define FR2_1_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x13
#define FR2_1_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x14

#define FR2_2_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x21
#define FR2_2_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x22
#define FR2_2_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x23
#define FR2_2_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x24

#define FR2_3_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x31
#define FR2_3_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x32
#define FR2_3_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x33
#define FR2_3_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x34

#define FR2_4_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x41
#define FR2_4_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x42
#define FR2_4_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x43
#define FR2_4_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x44

#define FR2_5_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x51
#define FR2_5_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x52
#define FR2_5_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x53
#define FR2_5_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x54

#define FR2_6_1_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x61
#define FR2_6_2_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x62
#define FR2_6_3_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x63
#define FR2_6_4_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x02, 0x64

#define FR1_1_1_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x11
#define FR1_1_2_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x12
#define FR1_1_3_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x13
#define FR1_1_4_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x14

#define FR1_2_1_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x21
#define FR1_2_2_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x22
#define FR1_2_3_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x23
#define FR1_2_4_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x24

#define FR1_3_1_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x31
#define FR1_3_2_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x32
#define FR1_3_3_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x33
#define FR1_3_4_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x34

#define FR1_4_1_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x41
#define FR1_4_2_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x42
#define FR1_4_3_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x43
#define FR1_4_4_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x44

#define FR1_5_1_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x51
#define FR1_5_2_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x52
#define FR1_5_3_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x53
#define FR1_5_4_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x54

#define FR1_6_1_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x61
#define FR1_6_2_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x62
#define FR1_6_3_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x63
#define FR1_6_4_FILTER_MAC_ADDR 0x02, 0x00, 0x00, 0x04, 0x11, 0x64

/*Shared RFs* MAC addresses*/
#define FR1_1_1_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x01, 0x11 //Filter of radio module connected to FSM 1 at pos 1-1
#define FR1_2_1_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x01, 0x21 //Filter of radio module connected to FSM 1 at pos 1-2
#define FR1_3_1_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x01, 0x31 //Filter of radio module connected to FSM 1 at pos 1-3
#define FR1_4_1_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x01, 0x41 //Filter of radio module connected to FSM 1 at pos 1-4
#define FR1_5_1_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x01, 0x51 //Filter of radio module connected to FSM 1 at pos 1-5
#define FR1_6_1_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x01, 0x61 //Filter of radio module connected to FSM 1 at pos 1-6

#define FR1_1_1_FILTER_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x02, 0x11 //Radio module connected to ESM (Edge System Module) at pos 1-1: Filter 1
#define FR1_2_1_FILTER_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x02, 0x12 //Radio module connected to ESM (Edge System Module) at pos 1-2: Filter 1
#define FR1_3_1_FILTER_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x02, 0x13 //Radio module connected to ESM (Edge System Module) at pos 1-3: Filter 1
#define FR1_4_1_FILTER_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x02, 0x14 //Radio module connected to ESM (Edge System Module) at pos 1-4: Filter 1
#define FR1_5_1_FILTER_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x02, 0x15 //Radio module connected to ESM (Edge System Module) at pos 1-5: Filter 1
#define FR1_6_1_FILTER_SHARED_MAC_ADDR 0x02, 0x00, 0x00, 0x01, 0x02, 0x16 //Radio module connected to ESM (Edge System Module) at pos 1-6: Filter 1

/* Faraday IP addresses */
/* Flexi System Module, FSP1, Faraday 1 IP address */
#define FSM1_FSP1_CHIP1_CPU2_IP_ADDR "192.168.255.151"
/* Flexi System Module, FSP1, Faraday 2 IP address */
#define FSM1_FSP1_CHIP2_CPU2_IP_ADDR "192.168.255.152"
/* Flexi System Module, FSP1, Faraday 3 IP address */
#define FSM1_FSP1_CHIP3_CPU2_IP_ADDR "192.168.255.153"
/* Flexi System Module, FSP1, Faraday 4 IP address */
#define FSM1_FSP1_CHIP4_CPU2_IP_ADDR "192.168.255.154"
/* Flexi System Module, FSP1, Faraday 5 IP address */
#define FSM1_FSP1_CHIP5_CPU2_IP_ADDR "192.168.255.155"
/* Flexi System Module, FSP1, Faraday 6 IP address */
#define FSM1_FSP1_CHIP6_CPU2_IP_ADDR "192.168.255.156"
/* Flexi System Module, FSP1, Faraday 7 (TUP/FP) CPU2 IP address */
#define FSM1_FSP1_CHIP7_CPU2_IP_ADDR "192.168.255.157"
/* Flexi System Module, FSP1, Faraday 7 (TUP/FP) CPU1 IP address */
#define FSM1_FSP1_CHIP7_CPU1_IP_ADDR "192.168.255.158"
/* Flexi System Module, FSP1, Faraday 7 (TUP/FP) CPU3 IP address */
#define FSM1_FSP1_CHIP7_CPU3_IP_ADDR "192.168.255.159"

/* Flexi System Module, FSP2, Faraday 1 IP address */
#define FSM1_FSP2_CHIP1_CPU2_IP_ADDR "192.168.255.161"
/* Flexi System Module, FSP2, Faraday 2 IP address */
#define FSM1_FSP2_CHIP2_CPU2_IP_ADDR "192.168.255.162"
/* Flexi System Module, FSP2, Faraday 3 IP address */
#define FSM1_FSP2_CHIP3_CPU2_IP_ADDR "192.168.255.163"
/* Flexi System Module, FSP2, Faraday 4 IP address */
#define FSM1_FSP2_CHIP4_CPU2_IP_ADDR "192.168.255.164"
/* Flexi System Module, FSP2, Faraday 5 IP address */
#define FSM1_FSP2_CHIP5_CPU2_IP_ADDR "192.168.255.165"
/* Flexi System Module, FSP2, Faraday 6 IP address */
#define FSM1_FSP2_CHIP6_CPU2_IP_ADDR "192.168.255.166"
/* Flexi System Module, FSP2, Faraday 7 (TUP/FP) CPU2 IP address */
#define FSM1_FSP2_CHIP7_CPU2_IP_ADDR "192.168.255.167"
/* Flexi System Module, FSP2, Faraday 7 (TUP/FP) CPU1 IP address */
#define FSM1_FSP2_CHIP7_CPU1_IP_ADDR "192.168.255.168"
/* Flexi System Module, FSP2, Faraday 7 (TUP/FP) CPU3 IP address */
#define FSM1_FSP2_CHIP7_CPU3_IP_ADDR "192.168.255.169"

/* Flexi System Module, FSP3, Faraday 1 IP address */
#define FSM1_FSP3_CHIP1_CPU2_IP_ADDR "192.168.255.171"
/* Flexi System Module, FSP3, Faraday 2 IP address */
#define FSM1_FSP3_CHIP2_CPU2_IP_ADDR "192.168.255.172"
/* Flexi System Module, FSP3, Faraday 3 IP address */
#define FSM1_FSP3_CHIP3_CPU2_IP_ADDR "192.168.255.173"
/* Flexi System Module, FSP3, Faraday 4 IP address */
#define FSM1_FSP3_CHIP4_CPU2_IP_ADDR "192.168.255.174"
/* Flexi System Module, FSP3, Faraday 5 IP address */
#define FSM1_FSP3_CHIP5_CPU2_IP_ADDR "192.168.255.175"
/* Flexi System Module, FSP3, Faraday 6 IP address */
#define FSM1_FSP3_CHIP6_CPU2_IP_ADDR "192.168.255.176"
/* Flexi System Module, FSP3, Faraday 7 (TUP/FP) CPU2 IP address */
#define FSM1_FSP3_CHIP7_CPU2_IP_ADDR "192.168.255.177"
/* Flexi System Module, FSP3, Faraday 7 (TUP/FP) CPU1 IP address */
#define FSM1_FSP3_CHIP7_CPU1_IP_ADDR "192.168.255.178"
/* Flexi System Module, FSP3, Faraday 7 (TUP/FP) CPU3 IP address */
#define FSM1_FSP3_CHIP7_CPU3_IP_ADDR "192.168.255.179"

/* Flexi Extension Module, FSP1, Faraday 1 IP address */
#define FSM2_FSP1_CHIP1_CPU2_IP_ADDR "192.168.255.181"
/* Flexi Extension Module, FSP1, Faraday 2 IP address */
#define FSM2_FSP1_CHIP2_CPU2_IP_ADDR "192.168.255.182"
/* Flexi Extension Module, FSP1, Faraday 3 IP address */
#define FSM2_FSP1_CHIP3_CPU2_IP_ADDR "192.168.255.183"
/* Flexi Extension Module, FSP1, Faraday 4 IP address */
#define FSM2_FSP1_CHIP4_CPU2_IP_ADDR "192.168.255.184"
/* Flexi Extension Module, FSP1, Faraday 5 IP address */
#define FSM2_FSP1_CHIP5_CPU2_IP_ADDR "192.168.255.185"
/* Flexi Extension Module, FSP1, Faraday 6 IP address */
#define FSM2_FSP1_CHIP6_CPU2_IP_ADDR "192.168.255.186"
/* Flexi Extension Module, FSP1, Faraday 7 (TUP/FP) CPU2 IP address */
#define FSM2_FSP1_CHIP7_CPU2_IP_ADDR "192.168.255.187"
/* Flexi Extension Module, FSP1, Faraday 7 (TUP/FP) CPU1 IP address */
#define FSM2_FSP1_CHIP7_CPU1_IP_ADDR "192.168.255.188"
/* Flexi Extension Module, FSP1, Faraday 7 (TUP/FP) CPU3 IP address */
#define FSM2_FSP1_CHIP7_CPU3_IP_ADDR "192.168.255.189"

/* Flexi Extension Module, FSP2, Faraday 1 IP address */
#define FSM2_FSP2_CHIP1_CPU2_IP_ADDR "192.168.255.191"
/* Flexi Extension Module, FSP2, Faraday 2 IP address */
#define FSM2_FSP2_CHIP2_CPU2_IP_ADDR "192.168.255.192"
/* Flexi Extension Module, FSP2, Faraday 3 IP address */
#define FSM2_FSP2_CHIP3_CPU2_IP_ADDR "192.168.255.193"
/* Flexi Extension Module, FSP2, Faraday 4 IP address */
#define FSM2_FSP2_CHIP4_CPU2_IP_ADDR "192.168.255.194"
/* Flexi Extension Module, FSP2, Faraday 5 IP address */
#define FSM2_FSP2_CHIP5_CPU2_IP_ADDR "192.168.255.195"
/* Flexi Extension Module, FSP2, Faraday 6 IP address */
#define FSM2_FSP2_CHIP6_CPU2_IP_ADDR "192.168.255.196"
/* Flexi Extension Module, FSP2, Faraday 7 (TUP/FP) CPU2 IP address */
#define FSM2_FSP2_CHIP7_CPU2_IP_ADDR "192.168.255.197"
/* Flexi Extension Module, FSP2, Faraday 7 (TUP/FP) CPU1 IP address */
#define FSM2_FSP2_CHIP7_CPU1_IP_ADDR "192.168.255.198"
/* Flexi Extension Module, FSP2, Faraday 7 (TUP/FP) CPU3 IP address */
#define FSM2_FSP2_CHIP7_CPU3_IP_ADDR "192.168.255.199"

/* Flexi Extension Module, FSP3, Faraday 1 IP address */
#define FSM2_FSP3_CHIP1_CPU2_IP_ADDR "192.168.255.201"
/* Flexi Extension Module, FSP3, Faraday 2 IP address */
#define FSM2_FSP3_CHIP2_CPU2_IP_ADDR "192.168.255.202"
/* Flexi Extension Module, FSP3, Faraday 3 IP address */
#define FSM2_FSP3_CHIP3_CPU2_IP_ADDR "192.168.255.203"
/* Flexi Extension Module, FSP3, Faraday 4 IP address */
#define FSM2_FSP3_CHIP4_CPU2_IP_ADDR "192.168.255.204"
/* Flexi Extension Module, FSP3, Faraday 5 IP address */
#define FSM2_FSP3_CHIP5_CPU2_IP_ADDR "192.168.255.205"
/* Flexi Extension Module, FSP3, Faraday 6 IP address */
#define FSM2_FSP3_CHIP6_CPU2_IP_ADDR "192.168.255.206"
/* Flexi Extension Module, FSP3, Faraday 7 (TUP/FP) CPU2 IP address */
#define FSM2_FSP3_CHIP7_CPU2_IP_ADDR "192.168.255.207"
/* Flexi Extension Module, FSP3, Faraday 7 (TUP/FP) CPU1 IP address */
#define FSM2_FSP3_CHIP7_CPU1_IP_ADDR "192.168.255.208"
/* Flexi Extension Module, FSP3, Faraday 7 (TUP/FP) CPU3 IP address */
#define FSM2_FSP3_CHIP7_CPU3_IP_ADDR "192.168.255.209"

/* Flexi Second Extension Module, FSP1, Faraday 1 IP address */
#define FSM3_FSP1_CHIP1_CPU2_IP_ADDR "192.168.255.211"
/* Flexi Second extension Module, FSP1, Faraday 2 IP address */
#define FSM3_FSP1_CHIP2_CPU2_IP_ADDR "192.168.255.212"
/* Flexi Second Extension Module, FSP1, Faraday 3 IP address */
#define FSM3_FSP1_CHIP3_CPU2_IP_ADDR "192.168.255.213"
/* Flexi Second Extension Module, FSP1, Faraday 4 IP address */
#define FSM3_FSP1_CHIP4_CPU2_IP_ADDR "192.168.255.214"
/* Flexi Second Extension Module, FSP1, Faraday 5 IP address */
#define FSM3_FSP1_CHIP5_CPU2_IP_ADDR "192.168.255.215"
/* Flexi Second Extension Module, FSP1, Faraday 6 IP address */
#define FSM3_FSP1_CHIP6_CPU2_IP_ADDR "192.168.255.216"
/* Flexi Second Extension Module, FSP1, Faraday 7 (TUP/FP) CPU2 IP address */
#define FSM3_FSP1_CHIP7_CPU2_IP_ADDR "192.168.255.217"
/* Flexi Second Extension Module, FSP1, Faraday 7 (TUP/FP) CPU1 IP address */
#define FSM3_FSP1_CHIP7_CPU1_IP_ADDR "192.168.255.218"
/* Flexi Second Extension Module, FSP1, Faraday 7 (TUP/FP) CPU3 IP address */
#define FSM3_FSP1_CHIP7_CPU3_IP_ADDR "192.168.255.219"

/* Flexi Second Extension Module, FSP2, Faraday 1 IP address */
#define FSM3_FSP2_CHIP1_CPU2_IP_ADDR "192.168.255.221"
/* Flexi Second Extension Module, FSP2, Faraday 2 IP address */
#define FSM3_FSP2_CHIP2_CPU2_IP_ADDR "192.168.255.222"
/* Flexi Second Extension Module, FSP2, Faraday 3 IP address */
#define FSM3_FSP2_CHIP3_CPU2_IP_ADDR "192.168.255.223"
/* Flexi Second Extension Module, FSP2, Faraday 4 IP address */
#define FSM3_FSP2_CHIP4_CPU2_IP_ADDR "192.168.255.224"
/* Flexi Second Extension Module, FSP2, Faraday 5 IP address */
#define FSM3_FSP2_CHIP5_CPU2_IP_ADDR "192.168.255.225"
/* Flexi Second Extension Module, FSP2, Faraday 6 IP address */
#define FSM3_FSP2_CHIP6_CPU2_IP_ADDR "192.168.255.226"
/* Flexi Second Extension Module, FSP2, Faraday 7 (TUP/FP) CPU2 IP address */
#define FSM3_FSP2_CHIP7_CPU2_IP_ADDR "192.168.255.227"
/* Flexi Second Extension Module, FSP2, Faraday 7 (TUP/FP) CPU1 IP address */
#define FSM3_FSP2_CHIP7_CPU1_IP_ADDR "192.168.255.228"
/* Flexi Second Extension Module, FSP2, Faraday 7 (TUP/FP) CPU3 IP address */
#define FSM3_FSP2_CHIP7_CPU3_IP_ADDR "192.168.255.229"

/* Flexi Second Extension Module, FSP3, Faraday 1 IP address */
#define FSM3_FSP3_CHIP1_CPU2_IP_ADDR "192.168.255.231"
/* Flexi Second Extension Module, FSP3, Faraday 2 IP address */
#define FSM3_FSP3_CHIP2_CPU2_IP_ADDR "192.168.255.232"
/* Flexi Second Extension Module, FSP3, Faraday 3 IP address */
#define FSM3_FSP3_CHIP3_CPU2_IP_ADDR "192.168.255.233"
/* Flexi Second Extension Module, FSP3, Faraday 4 IP address */
#define FSM3_FSP3_CHIP4_CPU2_IP_ADDR "192.168.255.234"
/* Flexi Second Extension Module, FSP3, Faraday 5 IP address */
#define FSM3_FSP3_CHIP5_CPU2_IP_ADDR "192.168.255.235"
/* Flexi Second Extension Module, FSP3, Faraday 6 IP address */
#define FSM3_FSP3_CHIP6_CPU2_IP_ADDR "192.168.255.236"
/* Flexi Second Extension Module, FSP3, Faraday 7 (TUP/FP) CPU2 IP address */
#define FSM3_FSP3_CHIP7_CPU2_IP_ADDR "192.168.255.237"
/* Flexi Second Extension Module, FSP3, Faraday 7 (TUP/FP) CPU1 IP address */
#define FSM3_FSP3_CHIP7_CPU1_IP_ADDR "192.168.255.238"
/* Flexi Second Extension Module, FSP3, Faraday 7 (TUP/FP) CPU3 IP address */
#define FSM3_FSP3_CHIP7_CPU3_IP_ADDR "192.168.255.239"

#define FAM1_IP_ADDR        "192.168.255.120" /* LTE FAM1 IP address */
#define DCT1_IP_ADDR        "192.168.255.142" /* LTE DCT1 IP address */

#define BTS_MODULE_FSM1 0x1
#define BTS_MODULE_FSM2 0x2
#define BTS_MODULE_FSM3 0x3
#define BTS_MODULE_FSM4 0x4
#define BTS_MODULE_FSM5 0x5
#define BTS_MODULE_FSM6 0x6
#define BTS_MODULE_FSM7 0x7		/* Definition used only in 5G17A CT release */
#define BTS_MODULE_FSM8 0x8		/* Definition used only in 5G17A CT release */
#define BTS_MODULE_FSM9 0x9		/* Definition used only in 5G17A CT release */
#define BTS_MODULE_FSM10 0xA		/* Definition used only in 5G17A CT release */
#define BTS_MODULE_FSM11 0xB		/* Definition used only in 5G17A CT release */
#define BTS_MODULE_FSM12 0xC		/* Definition used only in 5G17A CT release */
#define BTS_MODULE_FSM13 0xD		/* Definition used only in 5G17A CT release */
#define BTS_MODULE_FSM14 0xE		/* Definition used only in 5G17A CT release */
#define BTS_NID_FMT_MODULE(module) ((((u16)module) << 12) & 0xF000)
#define BTS_NID_GET_MODULE(nid)    ((((u16)nid) >> 12) & 0xF)

#define BTS_BOARD_FCT   0x0
#define BTS_BOARD_FSP1  0x2
#define BTS_BOARD_FSP2  0x3
#define BTS_BOARD_FSP3  0x4
#define FSMR4_BOARD_FSIP  BTS_BOARD_FCT
#define FSMR4_BOARD_FBxx1 BTS_BOARD_FSP1
#define FSMR4_BOARD_FBxx2 BTS_BOARD_FSP2
#define FSMR4_BOARD_FBxx3 BTS_BOARD_FSP3
#define BTS_NID_FMT_BOARD(board) ((((u16)board) << 8) & 0x0F00)
#define BTS_NID_GET_BOARD(nid)   ((((u16)nid) >> 8) & 0xF)

#define BTS_SOC_AXM     0x1
#define BTS_SOC_1       0x3
#define BTS_SOC_2       0x4
#define BTS_SOC_3       0x5
#define BTS_SOC_4       0x6
#define FSMR4_SOC_AXM BTS_SOC_AXM
#define FSMR4_SOC_K2A BTS_SOC_1
#define FSMR4_SOC_K2B BTS_SOC_2
#define FSMR4_SOC_K2C BTS_SOC_3
#define FSMR4_SOC_K2D BTS_SOC_4
#define BTS_SOC_XEONA BTS_SOC_AXM   /* Obsolete - use BTS_SOC_FCT_MCU1 */
#define BTS_SOC_XEONB 0x2           /* Obsolete - use BTS_SOC_FCT_MCU2 */
#define BTS_SOC_FCT_MCU  BTS_SOC_AXM
#define BTS_SOC_FCT_MCU1 BTS_SOC_FCT_MCU
#define BTS_SOC_FCT_MCU2 0x2

#define BTS_NID_FMT_SOC(soc) ((((u16)soc) << 4) & 0x00F0)
#define BTS_NID_GET_SOC(nid) ((((u16)nid) >> 4) & 0xF)

#define BTS_CORE_1      0x1
#define BTS_CORE_2      0x2
#define BTS_CORE_3      0x3
#define BTS_CORE_4      0x4
#define BTS_CORE_5      0x5
#define BTS_CORE_6      0x6
#define BTS_CORE_7      0x7
#define BTS_CORE_8      0x8
#define BTS_CORE_9      0x9 /* SysCom EO by-pass for 2CE */
#define BTS_CORE_A      0xA /* SysCom EO routing */
#define BTS_CORE_B      0xB /* SysCom EO by-pass for FSMr4 and LRC */
#define BTS_CORE_D      0xD /* SMP */
#define BTS_CORE_E      0xE
#define BTS_NID_FMT_CORE(core) (((u16)core) & 0x000F)
#define BTS_NID_GET_CORE(nid)  (((u16)nid) & 0xF)

#define BTS_NID_FMT(module, board, soc, core) \
(                                             \
    BTS_NID_FMT_MODULE(module) |              \
    BTS_NID_FMT_BOARD(board)   |              \
    BTS_NID_FMT_SOC(soc)       |              \
    BTS_NID_FMT_CORE(core)                    \
)

/* FSMr4 K2 streaming addresses
 * WCDMA_LTE_BTS_PktFlow_ClassificationRules, version 79,97
 * https://sharenet-ims.int.net.nokia.com/livelink/livelink?func=ll&objaction=overview&objid=395347830 */

/* [FSM-r4]: subnet ID for streaming network 192.168.255.160/27, host range 192.168.255.161 - 190 (30 hosts) */
#define STREAMING_SUBNET_ID         "192.168.255.160"
/* [FSMr-4]: streaming network broadcast IP address */
#define STREAMING_BROADCAST_IP_ADDR FSM2_FSP2_CHIP1_CPU2_IP_ADDR

/* [FSM-r4]: Module 1: FCT_SEI, Internal IP address for SEI interface in streaming network */
#define FSM1_FSIP_AXM_SEI_STREAMING_IP_ADDR FSM1_FSP2_CHIP1_CPU2_IP_ADDR

/* [FSM-r4]: Module 1: FBxx1/K2A_ethc0 */
#define FSM1_FBxx1_K2A_STREAMING_IP_ADDR FSM1_FSP2_CHIP2_CPU2_IP_ADDR
/* [FSM-r4]: Module 1: FBxx1/K2B_ethn0 */
#define FSM1_FBxx1_K2B_STREAMING_IP_ADDR FSM1_FSP2_CHIP3_CPU2_IP_ADDR
/* [FSM-r4]: Module 1: FBxx1/K2C_ethn1 */
#define FSM1_FBxx1_K2C_STREAMING_IP_ADDR FSM1_FSP2_CHIP4_CPU2_IP_ADDR
/* [FSM-r4]: Module 1: FBxx1/K2D_ethc0 */
#define FSM1_FBxx1_K2D_STREAMING_IP_ADDR FSM1_FSP2_CHIP5_CPU2_IP_ADDR

/* [FSM-r4]: Module 1: FBxx2/K2A_ethc0 */
#define FSM1_FBxx2_K2A_STREAMING_IP_ADDR FSM1_FSP2_CHIP6_CPU2_IP_ADDR
/* [FSM-r4]: Module 1: FBxx2/K2A_ethn0 */
#define FSM1_FBxx2_K2B_STREAMING_IP_ADDR FSM1_FSP2_CHIP7_CPU2_IP_ADDR
/* [FSM-r4]: Module 1: FBxx2/K2A_ethn1 */
#define FSM1_FBxx2_K2C_STREAMING_IP_ADDR FSM1_FSP2_CHIP7_CPU1_IP_ADDR
/* [FSM-r4]: Module 1: FBxx2/K2A_ethc0 */
#define FSM1_FBxx2_K2D_STREAMING_IP_ADDR FSM1_FSP2_CHIP7_CPU3_IP_ADDR

/* [FSM-r4]: Module 1: FBxx3/K2A_ethc0 */
#define FSM1_FBxx3_K2A_STREAMING_IP_ADDR "192.168.255.170"
/* [FSM-r4]: Module 1: FBxx3/K2A_ethn0 */
#define FSM1_FBxx3_K2B_STREAMING_IP_ADDR FSM1_FSP3_CHIP1_CPU2_IP_ADDR
/* [FSM-r4]: Module 1: FBxx3/K2A_ethn1 */
#define FSM1_FBxx3_K2C_STREAMING_IP_ADDR FSM1_FSP3_CHIP2_CPU2_IP_ADDR
/* [FSM-r4]: Module 1: FBxx3/K2A_ethc0 */
#define FSM1_FBxx3_K2D_STREAMING_IP_ADDR FSM1_FSP3_CHIP3_CPU2_IP_ADDR

/* [FSM-r4]: Module 2: FBxx1/K2A_ethc0 */
#define FSM2_FBxx1_K2A_STREAMING_IP_ADDR FSM1_FSP3_CHIP4_CPU2_IP_ADDR
/* [FSM-r4]: Module 2: FBxx1/K2A_ethn0 */
#define FSM2_FBxx1_K2B_STREAMING_IP_ADDR FSM1_FSP3_CHIP5_CPU2_IP_ADDR
/* [FSM-r4]: Module 2: FBxx1/K2A_ethn1 */
#define FSM2_FBxx1_K2C_STREAMING_IP_ADDR FSM1_FSP3_CHIP6_CPU2_IP_ADDR
/* [FSM-r4]: Module 2: FBxx1/K2A_ethc0 */
#define FSM2_FBxx1_K2D_STREAMING_IP_ADDR FSM1_FSP3_CHIP7_CPU2_IP_ADDR

/* [FSM-r4]: Module 2: FBxx2/K2A_ethc0 */
#define FSM2_FBxx2_K2A_STREAMING_IP_ADDR FSM1_FSP3_CHIP7_CPU1_IP_ADDR
/* [FSM-r4]: Module 2: FBxx2/K2A_ethn0 */
#define FSM2_FBxx2_K2B_STREAMING_IP_ADDR FSM1_FSP3_CHIP7_CPU3_IP_ADDR
/* [FSM-r4]: Module 2: FBxx2/K2A_ethn1 */
#define FSM2_FBxx2_K2C_STREAMING_IP_ADDR "192.168.255.180"
/* [FSM-r4]: Module 2: FBxx2/K2A_ethc0 */
#define FSM2_FBxx2_K2D_STREAMING_IP_ADDR FSM2_FSP1_CHIP1_CPU2_IP_ADDR

/* [FSM-r4]: Module 2: FBxx3/K2A_ethc0 */
#define FSM2_FBxx3_K2A_STREAMING_IP_ADDR FSM2_FSP1_CHIP2_CPU2_IP_ADDR
/* [FSM-r4]: Module 2: FBxx3/K2A_ethn0 */
#define FSM2_FBxx3_K2B_STREAMING_IP_ADDR FSM2_FSP1_CHIP3_CPU2_IP_ADDR
/* [FSM-r4]: Module 2: FBxx3/K2A_ethn1 */
#define FSM2_FBxx3_K2C_STREAMING_IP_ADDR FSM2_FSP1_CHIP4_CPU2_IP_ADDR
/* [FSM-r4]: Module 2: FBxx3/K2A_ethc0 */
#define FSM2_FBxx3_K2D_STREAMING_IP_ADDR FSM2_FSP1_CHIP5_CPU2_IP_ADDR

/* [FSM-r4]: Test PC IP address connected to streaming network */
#define TESTER_PC_1_STREAMING_IP_ADDR FSM2_FSP1_CHIP7_CPU1_IP_ADDR
/* [FSM-r4]: Test PC IP address connected to streaming network */
#define TESTER_PC_2_STREAMING_IP_ADDR FSM2_FSP1_CHIP7_CPU3_IP_ADDR
/* [FSM-r4]: Test PC IP address connected to streaming network */
#define TESTER_PC_3_STREAMING_IP_ADDR "192.168.255.190"

/* VLAN tags */
#define VLAN_TAG_RM_ROM       0x101 /* RM:     For boot ROM traffic (RFSW), FRM-rel5.1 onwards            */
#define VLAN_TAG_RM_DFE       0x102 /* RM:     For intra-DFE (RFSW internal), traffic FRM-rel5.1 onwards  */
#define VLAN_TAG_VLAN1        0x010 /* FSM-r3: Security for Ethernet ports, See WBTS_SEC_49908            */
#define VLAN_TAG_VLAN2        0x020 /* FSM-r3: Security for Ethernet ports, See WBTS_SEC_49908            */
#define VLAN_TAG_VLAN3        0x030 /* FSM-r3: Security for Ethernet ports, See WBTS_SEC_49908            */
#define VLAN_TAG_LOCAL         200U /* FSM-r4: Local VLAN                                                 */
#define VLAN_TAG_GLOBAL        201U /* FSM-r4: Global VLAN                                                */
#define VLAN_TAG_RF            202U /* FSM-r4: RF VLAN                                                    */
#define VLAN_TAG_STREAM        210U /* FSM-r4: Streaming VLAN, RP000776-Q-b: dedicated VLAN for streaming */

/* WAM CTRL_MCU MAC addresses */
#define WAM_10_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x01
#define WAM_11_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x02
#define WAM_20_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x01
#define WAM_21_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x02
#define WAM_30_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x01
#define WAM_31_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x02

/* WPA MAC addresses */
#define WPA_10_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x31
#define WPA_11_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x32
#define WPA_20_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x31
#define WPA_21_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x32
#define WPA_30_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x31
#define WPA_31_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x32

/* WTR MAC addresses */
#define WTR_10_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x21
#define WTR_11_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x22
#define WTR_20_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x21
#define WTR_21_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x22
#define WTR_30_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x21
#define WTR_31_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x22

/* WSP_MCU MAC addresses */
#define WSP_10_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x41
#define WSP_11_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x42
#define WSP_12_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x43
#define WSP_13_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x44
#define WSP_14_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x45
#define WSP_15_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x01, 0x46
#define WSP_20_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x41
#define WSP_21_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x42
#define WSP_22_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x43
#define WSP_23_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x44
#define WSP_24_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x45
#define WSP_25_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x02, 0x46
#define WSP_30_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x41
#define WSP_31_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x42
#define WSP_32_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x43
#define WSP_33_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x44
#define WSP_34_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x45
#define WSP_35_MAC_ADDR     0x0e, 0x00, 0x00, 0x01, 0x03, 0x46


/* ATMHOST_MCU MAC addresses */
#define ATMHOST_10_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x01, 0x11
#define ATMHOST_11_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x01, 0x12
#define ATMHOST_20_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x02, 0x11
#define ATMHOST_21_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x02, 0x12
#define ATMHOST_30_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x03, 0x11
#define ATMHOST_31_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x03, 0x12

/* Flexi MAC addresses */
#define FSM_FCM_MAC_ADDR  WAM_10_MAC_ADDR /* Flexi System Module, FCM MAC address, will be removed in INC5 !!! */
#define FSM_FSP1_MAC_ADDR WSP_10_MAC_ADDR /* Flexi System Module, Signal Processing 1 MAC address, will be removed in INC5 !!! */
#define FSM_FSP2_MAC_ADDR WSP_11_MAC_ADDR /* Flexi System Module, Signal Processing 2 MAC address, will be removed in INC5 !!! */
#define FSM_FSP3_MAC_ADDR WSP_12_MAC_ADDR /* Flexi System Module, Signal Processing 3 MAC address, will be removed in INC5 !!! */

#define FSM1_FCM_MAC_ADDR  WAM_10_MAC_ADDR /* Flexi System Module, FCM MAC address */
#define FSM1_FSP1_MAC_ADDR WSP_10_MAC_ADDR /* Flexi System Module, Signal Processing 1 MAC address */
#define FSM1_FSP2_MAC_ADDR WSP_11_MAC_ADDR /* Flexi System Module, Signal Processing 2 MAC address */
#define FSM1_FSP3_MAC_ADDR WSP_12_MAC_ADDR /* Flexi System Module, Signal Processing 3 MAC address */
#define FSM2_FCM_MAC_ADDR  WAM_20_MAC_ADDR /* Flexi Extension Module 1, FCM MAC address */
#define FSM2_FSP1_MAC_ADDR WSP_20_MAC_ADDR /* Flexi Extension Module 1, Signal Processing 1 MAC address */
#define FSM2_FSP2_MAC_ADDR WSP_21_MAC_ADDR /* Flexi Extension Module 1, Signal Processing 2 MAC address */
#define FSM2_FSP3_MAC_ADDR WSP_22_MAC_ADDR /* Flexi Extension Module 1, Signal Processing 3 MAC address */
#define FSM3_FCM_MAC_ADDR  WAM_30_MAC_ADDR /* Flexi Extension Module 2, FCM MAC address */
#define FSM3_FSP1_MAC_ADDR WSP_30_MAC_ADDR /* Flexi Extension Module 2, Signal Processing 1 MAC address */
#define FSM3_FSP2_MAC_ADDR WSP_31_MAC_ADDR /* Flexi Extension Module 2, Signal Processing 2 MAC address */
#define FSM3_FSP3_MAC_ADDR WSP_32_MAC_ADDR /* Flexi Extension Module 2, Signal Processing 3 MAC address */

/* Faraday MAC addresses */
/* Flexi System Module, FSP1, Faraday 1 MAC address */
#define FSM1_FSP1_CHIP1_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x11
/* Flexi System Module, FSP1, Faraday 2 MAC address */
#define FSM1_FSP1_CHIP2_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x12
/* Flexi System Module, FSP1, Faraday 3 MAC address */
#define FSM1_FSP1_CHIP3_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x13
/* Flexi System Module, FSP1, Faraday 4 MAC address */
#define FSM1_FSP1_CHIP4_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x14
/* Flexi System Module, FSP1, Faraday 5 MAC address */
#define FSM1_FSP1_CHIP5_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x15
/* Flexi System Module, FSP1, Faraday 6 MAC address */
#define FSM1_FSP1_CHIP6_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x16
/* Flexi System Module, FSP1, Faraday 7 (TUP/FP) CPU2 MAC address */
#define FSM1_FSP1_CHIP7_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x17
/* Flexi System Module, FSP1, Faraday 7 (TUP/FP) CPU1 MAC address */
#define FSM1_FSP1_CHIP7_CPU1_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x18
/* Flexi System Module, FSP1, Faraday 7 (TUP/FP) CPU3 MAC address */
#define FSM1_FSP1_CHIP7_CPU3_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x19

/* Flexi System Module, FSP2, Faraday 1 MAC address */
#define FSM1_FSP2_CHIP1_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x21
/* Flexi System Module, FSP2, Faraday 2 MAC address */
#define FSM1_FSP2_CHIP2_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x22
/* Flexi System Module, FSP2, Faraday 3 MAC address */
#define FSM1_FSP2_CHIP3_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x23
/* Flexi System Module, FSP2, Faraday 4 MAC address */
#define FSM1_FSP2_CHIP4_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x24
/* Flexi System Module, FSP2, Faraday 5 MAC address */
#define FSM1_FSP2_CHIP5_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x25
/* Flexi System Module, FSP2, Faraday 6 MAC address */
#define FSM1_FSP2_CHIP6_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x26
/* Flexi System Module, FSP2, Faraday 7 (TUP/FP) CPU2 MAC address */
#define FSM1_FSP2_CHIP7_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x27
/* Flexi System Module, FSP2, Faraday 7 (TUP/FP) CPU1 MAC address */
#define FSM1_FSP2_CHIP7_CPU1_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x28
/* Flexi System Module, FSP2, Faraday 7 (TUP/FP) CPU3 MAC address */
#define FSM1_FSP2_CHIP7_CPU3_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x29

/* Flexi System Module, FSP3, Faraday 1 MAC address */
#define FSM1_FSP3_CHIP1_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x31
/* Flexi System Module, FSP3, Faraday 2 MAC address */
#define FSM1_FSP3_CHIP2_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x32
/* Flexi System Module, FSP3, Faraday 3 MAC address */
#define FSM1_FSP3_CHIP3_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x33
/* Flexi System Module, FSP3, Faraday 4 MAC address */
#define FSM1_FSP3_CHIP4_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x34
/* Flexi System Module, FSP3, Faraday 5 MAC address */
#define FSM1_FSP3_CHIP5_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x35
/* Flexi System Module, FSP3, Faraday 6 MAC address */
#define FSM1_FSP3_CHIP6_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x36
/* Flexi System Module, FSP3, Faraday 7 (TUP/FP) CPU2 MAC address */
#define FSM1_FSP3_CHIP7_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x37
/* Flexi System Module, FSP3, Faraday 7 (TUP/FP) CPU1 MAC address */
#define FSM1_FSP3_CHIP7_CPU1_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x38
/* Flexi System Module, FSP3, Faraday 7 (TUP/FP) CPU3 MAC address */
#define FSM1_FSP3_CHIP7_CPU3_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x39

/* Flexi Extension Module, FSP1, Faraday 1 MAC address */
#define FSM2_FSP1_CHIP1_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x41
/* Flexi Extension Module, FSP1, Faraday 2 MAC address */
#define FSM2_FSP1_CHIP2_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x42
/* Flexi Extension Module, FSP1, Faraday 3 MAC address */
#define FSM2_FSP1_CHIP3_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x43
/* Flexi Extension Module, FSP1, Faraday 4 MAC address */
#define FSM2_FSP1_CHIP4_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x44
/* Flexi Extension Module, FSP1, Faraday 5 MAC address */
#define FSM2_FSP1_CHIP5_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x45
/* Flexi Extension Module, FSP1, Faraday 6 MAC address */
#define FSM2_FSP1_CHIP6_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x46
/* Flexi Extension Module, FSP1, Faraday 7 (TUP/FP) CPU2 MAC address */
#define FSM2_FSP1_CHIP7_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x47
/* Flexi Extension Module, FSP1, Faraday 7 (TUP/FP) CPU1 MAC address */
#define FSM2_FSP1_CHIP7_CPU1_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x48
/* Flexi Extension Module, FSP1, Faraday 7 (TUP/FP) CPU3 MAC address */
#define FSM2_FSP1_CHIP7_CPU3_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x49

/* Flexi Extension Module, FSP2, Faraday 1 MAC address */
#define FSM2_FSP2_CHIP1_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x51
/* Flexi Extension Module, FSP2, Faraday 2 MAC address */
#define FSM2_FSP2_CHIP2_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x52
/* Flexi Extension Module, FSP2, Faraday 3 MAC address */
#define FSM2_FSP2_CHIP3_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x53
/* Flexi Extension Module, FSP2, Faraday 4 MAC address */
#define FSM2_FSP2_CHIP4_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x54
/* Flexi Extension Module, FSP2, Faraday 5 MAC address */
#define FSM2_FSP2_CHIP5_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x55
/* Flexi Extension Module, FSP2, Faraday 6 MAC address */
#define FSM2_FSP2_CHIP6_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x56
/* Flexi Extension Module, FSP2, Faraday 7 (TUP/FP) CPU2 MAC address */
#define FSM2_FSP2_CHIP7_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x57
/* Flexi Extension Module, FSP2, Faraday 7 (TUP/FP) CPU1 MAC address */
#define FSM2_FSP2_CHIP7_CPU1_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x58
/* Flexi Extension Module, FSP2, Faraday 7 (TUP/FP) CPU3 MAC address */
#define FSM2_FSP2_CHIP7_CPU3_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x59

/* Flexi Extension Module, FSP3, Faraday 1 MAC address */
#define FSM2_FSP3_CHIP1_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x61
/* Flexi Extension Module, FSP3, Faraday 2 MAC address */
#define FSM2_FSP3_CHIP2_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x62
/* Flexi Extension Module, FSP3, Faraday 3 MAC address */
#define FSM2_FSP3_CHIP3_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x63
/* Flexi Extension Module, FSP3, Faraday 4 MAC address */
#define FSM2_FSP3_CHIP4_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x64
/* Flexi Extension Module, FSP3, Faraday 5 MAC address */
#define FSM2_FSP3_CHIP5_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x65
/* Flexi Extension Module, FSP3, Faraday 6 MAC address */
#define FSM2_FSP3_CHIP6_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x66
/* Flexi Extension Module, FSP3, Faraday 7 (TUP/FP) CPU2 MAC address */
#define FSM2_FSP3_CHIP7_CPU2_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x67
/* Flexi Extension Module, FSP3, Faraday 7 (TUP/FP) CPU1 MAC address */
#define FSM2_FSP3_CHIP7_CPU1_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x68
/* Flexi Extension Module, FSP3, Faraday 7 (TUP/FP) CPU3 MAC address */
#define FSM2_FSP3_CHIP7_CPU3_MAC_ADDR 0x0e, 0x00, 0x00, 0x01, 0x04, 0x69

#define FR1_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x06, 0x01
#define FR1_FF1_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x06, 0x11
#define FR1_FF2_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x06, 0x21
#define FR1_FF3_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x06, 0x31

#define FR2_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x08, 0x01
#define FR2_FF1_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x08, 0x11
#define FR2_FF2_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x08, 0x21
#define FR2_FF3_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x08, 0x31

#define FR3_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x10, 0x01
#define FR3_FF1_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x10, 0x11
#define FR3_FF2_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x10, 0x21
#define FR3_FF3_MAC_ADDR 0x02, 0x00, 0x00, 0x00, 0x10, 0x31

/* Port numbers in WAM CTRL_MCU for WPA TCP connections */
#define WPA_10_TCP_PORT 10001
#define WPA_11_TCP_PORT 10002
#define WPA_20_TCP_PORT 10003
#define WPA_21_TCP_PORT 10004
#define WPA_30_TCP_PORT 10005
#define WPA_31_TCP_PORT 10006

/* Port numbers in WAM CTRL_MCU for subcontracted WPA (sWPA) TCP connections */
#define SWPA_10_TCP_PORT 10021
#define SWPA_11_TCP_PORT 10022
#define SWPA_20_TCP_PORT 10023
#define SWPA_21_TCP_PORT 10024
#define SWPA_30_TCP_PORT 10025
#define SWPA_31_TCP_PORT 10026

/* Port numbers in WAM CTRL_MCU for WTR TCP connections */
#define WTR_10_TCP_PORT 10011
#define WTR_11_TCP_PORT 10012
#define WTR_20_TCP_PORT 10013
#define WTR_21_TCP_PORT 10014
#define WTR_30_TCP_PORT 10015
#define WTR_31_TCP_PORT 10016

/* Master O&M WAM port numbers for TCP connections between WAMs */
#define WAM_10_MASTER_TCP_PORT  11001
#define WAM_11_MASTER_TCP_PORT  11002
#define WAM_20_MASTER_TCP_PORT  11003
#define WAM_21_MASTER_TCP_PORT  11004
#define WAM_30_MASTER_TCP_PORT  11005
#define WAM_31_MASTER_TCP_PORT  11006

/* Tassu Router port number for TCP connections */
#define TASSU_TCP_PORT          15001

/* DSP Browser port number for TCP connections */
#define TASSU_BROWSER_TCP_PORT  15002    /* Tassu Router if */
#define API_BROWSER_TCP_PORT    15003    /* API Browser task if */

#define API_BTS_LOG_TCP_PORT    15004    /* API BTS log task if */
#define API_TESTER_INTERFACE_TCP_PORT    15005    /* API Tester Interface task if */

/* Port numbers in WAM for RNC TCP connections */
#define RNC_TCP_PORT1
#define RNC_TCP_PORT2

/* Port numbers in WPA/SWPA/WTR for WAM CTRL_MCU UDP connections */
#define WAM_10_UDP_PORT 12001
#define WAM_11_UDP_PORT 12002
#define WAM_20_UDP_PORT 12003
#define WAM_21_UDP_PORT 12004
#define WAM_30_UDP_PORT 12005
#define WAM_31_UDP_PORT 12006

/* Reserved port numbers in WAM CTRL_MCU for WAM CTRL_MCU UDP connections */
/* These are not defined anywhere but calculated as following */
/* UDP port for WAM_10      12017 = WAM_10_UDP_PORT + WAM_10 (12001 + 16) */
/* UDP port for WAM_11      12019 = WAM_11_UDP_PORT + WAM_11 (12002 + 17) */
/* UDP port for WAM_20      12035 = WAM_20_UDP_PORT + WAM_20 (12003 + 32) */
/* UDP port for WAM_21      12037 = WAM_21_UDP_PORT + WAM_21 (12004 + 33) */
/* UDP port for WAM_30      12053 = WAM_30_UDP_PORT + WAM_30 (12005 + 48) */
/* UDP port for WAM_31      12055 = WAM_31_UDP_PORT + WAM_31 (12006 + 49) */

/* Port for ADET service */
#define SOAP_ADET_SERVER_PORT   13001
/* Port for module agent */
#define SOAP_MODULE_SERVER_PORT 13002

/* Port numbers in WAM CTRL_MCU for WPA/SWPA UDP connections */
#define WPA_10_UDP_PORT 12001
#define WPA_11_UDP_PORT 12002
#define WPA_20_UDP_PORT 12003
#define WPA_21_UDP_PORT 12004
#define WPA_30_UDP_PORT 12005
#define WPA_31_UDP_PORT 12006


/* Port numbers in WAM CTRL_MCU for WTR UDP connections */
#define WTR_10_UDP_PORT 12011
#define WTR_11_UDP_PORT 12012
#define WTR_20_UDP_PORT 12013
#define WTR_21_UDP_PORT 12014
#define WTR_30_UDP_PORT 12015
#define WTR_31_UDP_PORT 12016

/* Port numbers in WAM CTRL_MCU for AXU UDP connection */
#define AXU_UDP_PORT    60000

/* Flexi UDP port numbers */
#define FSM_FCM_UDP_PORT    WAM_10_UDP_PORT     /* Flexi System Module, FCM UDP port will be removed in INC5 !!! */
#define FSM_FSP1_UDP_PORT  12021               /* Flexi System Module, Signal Processing 1 UDP port, FCM UDP port will be removed in INC5 !!! */
#define FSM_FSP2_UDP_PORT  12022               /* Flexi System Module, Signal Processing 2 UDP port, FCM UDP port will be removed in INC5 !!! */
#define FSM_FSP3_UDP_PORT  12023               /* Flexi System Module, Signal Processing 3 UDP port, FCM UDP port will be removed in INC5 !!! */


#define FSM1_FCM_UDP_PORT   WAM_10_UDP_PORT     /* Flexi System Module, FCM UDP port */
#define FSM2_FCM_UDP_PORT   WAM_20_UDP_PORT     /* Flexi Extension Module 1, FCM UDP port */
#define FSM3_FCM_UDP_PORT   WAM_30_UDP_PORT     /* Flexi Extension Module 2, FCM UDP port */
#define FSM_FT_UDP_PORT     AXU_UDP_PORT        /* Flexi Transport UDP port */
#define FSM1_FSP1_UDP_PORT  12021               /* Flexi System Module, Signal Processing 1 UDP port */
#define FSM1_FSP2_UDP_PORT  12022               /* Flexi System Module, Signal Processing 2 UDP port */
#define FSM1_FSP3_UDP_PORT  12023               /* Flexi System Module, Signal Processing 3 UDP port */
#define FSM2_FSP1_UDP_PORT  12024               /* Flexi Extension Module 1, Signal Processing 1 UDP port */
#define FSM2_FSP2_UDP_PORT  12025               /* Flexi Extension Module 1, Signal Processing 2 UDP port */
#define FSM2_FSP3_UDP_PORT  12026               /* Flexi Extension Module 1, Signal Processing 3 UDP port */
#define FSM3_FSP1_UDP_PORT  12027               /* Flexi Extension Module 2, Signal Processing 1 UDP port */
#define FSM3_FSP2_UDP_PORT  12028               /* Flexi Extension Module 2, Signal Processing 2 UDP port */
#define FSM3_FSP3_UDP_PORT  12029               /* Flexi Extension Module 2, Signal Processing 3 UDP port */

/* Port numbers in PSPB */
/* For FSPB start-up, Faraday 1 UDP port */
#define FSM_FCM_SWDL_CHIP1_UDP_PORT    16002
/* For FSPB start-up, Faraday 2 UDP port */
#define FSM_FCM_SWDL_CHIP2_UDP_PORT    16003
/* For FSPB start-up, Faraday 3 UDP port */
#define FSM_FCM_SWDL_CHIP3_UDP_PORT    16004
/* For FSPB start-up, Faraday 4 UDP port */
#define FSM_FCM_SWDL_CHIP4_UDP_PORT    16005
/* For FSPB start-up, Faraday 5 UDP port */
#define FSM_FCM_SWDL_CHIP5_UDP_PORT    16006
/* For FSPB start-up, Faraday 6 UDP port */
#define FSM_FCM_SWDL_CHIP6_UDP_PORT    16007
/* For FSPB start-up, Faraday 7 UDP port */
#define FSM_FCM_SWDL_CHIP7_UDP_PORT    16008

/* For NMAP_GW any-route communication, Faraday 1 UDPCP port */
#define FSM_FCM_CHIP1_UDPCP_PORT       14002
/* For NMAP_GW any-route communication, Faraday 2 UDPCP port */
#define FSM_FCM_CHIP2_UDPCP_PORT       14003
/* For NMAP_GW any-route communication, Faraday 3 UDPCP port */
#define FSM_FCM_CHIP3_UDPCP_PORT       14004
/* For NMAP_GW any-route communication, Faraday 4 UDPCP port */
#define FSM_FCM_CHIP4_UDPCP_PORT       14005
/* For NMAP_GW any-route communication, Faraday 5 UDPCP port */
#define FSM_FCM_CHIP5_UDPCP_PORT       14006
/* For NMAP_GW any-route communication, Faraday 6 UDPCP port */
#define FSM_FCM_CHIP6_UDPCP_PORT       14007
/* For NMAP_GW any-route communication, Faraday 7 UDPCP port */
#define FSM_FCM_CHIP7_UDPCP_PORT       14008

/* For user plane connection between TUP/FP and DSP */
#define FSM_FSPB_U_PLANE_PORT          14001
/* For NMAP_GW any-route communication */
#define FSM_FSPB_UDPCP_PORT            12004
/* For SWDL */
#define FSM_FSPB_SWDL_PORT             12005

/* Loop mode definitions */
#define AIF_LOOP        0x7
#define SW_AIF_LOOP     0x77
#define DSC_LOOP        0x8
#define SW_DSC_LOOP     0x88
#define SW_API_LOOP     0x69
#define SW_CD_LOOP      0xcd

/* Port numbers definitions for BIST */
#define BIST_SERVER_PORT 35000
#define BIST_CLIENT_PORT 35001

/* Port number definitions for Licence Management */
#define LICM_SERVER_PORT 13060
#define LICM_CLIENT_PORT 13061

/* See WCDMA BTS SW Architecture Specification for rationale and usage of these timeouts. */
/* Telecom - TUP and Telecom - DSP (milliseconds) */
#define TIMEOUT_SIGNALING_DEFAULT               2000
/* Intra MCU BTSOM, HWAPI, TUP, Telecom common configuration etc.(milliseconds) */
#define TIMEOUT_MANAGEMENT_INTRA_CPU_DEFAULT    30000
/* Inter MCU BTSOM, HWAPI, TUP, Telecom common configuration etc. (milliseconds) */
#define TIMEOUT_MANAGEMENT_INTER_CPU_DEFAULT    60000


/* SM3: Board definitions */
#define FSM1_FCT                FSM1_FCM        //0x10
#define FSM2_FCT                FSM2_FCM        //0x20
#define FSM3_FCT                FSM3_FCM        //0x30
#define FSM4_FCT                0x40
#define FSM5_FCT                0x50
#define FSM6_FCT                0x60
#define FSM7_FCT                0x70		/* Definition used only in 5G17A CT release */
#define FSM8_FCT                0x80		/* Definition used only in 5G17A CT release */
#define FSM9_FCT                0x90		/* Definition used only in 5G17A CT release */
#define FSM10_FCT               0xA0		/* Definition used only in 5G17A CT release */
#define FSM11_FCT               0xB0		/* Definition used only in 5G17A CT release */
#define FSM12_FCT               0xC0		/* Definition used only in 5G17A CT release */
#define FSM13_FCT               0xD0		/* Definition used only in 5G17A CT release */
#define FSM14_FCT               0xE0		/* Definition used only in 5G17A CT release */

/* SM3: MCU definitions */
#define FSM1_FCT_MCU            0x1011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM1_FCT_MCU1           FSM1_FCT_MCU   /* MCU1 NRT node */
#define FSM1_FCT_MCU1_EMGRP1    0x101A         /* MCU1 RT node */
#define FSM1_FCT_MCU2           0x1021         /* MCU2 NRT node */
#define FSM1_FCT_MCU2_EMGRP1    0x102A         /* MCU2 RT node */
#define FSM2_FCT_MCU            0x2011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM2_FCT_MCU1           FSM2_FCT_MCU   /* MCU1 NRT node */
#define FSM2_FCT_MCU1_EMGRP1    0x201A         /* MCU1 RT node */
#define FSM2_FCT_MCU2           0x2021         /* MCU2 NRT node */
#define FSM2_FCT_MCU2_EMGRP1    0x202A         /* MCU2 RT node */
#define FSM3_FCT_MCU            0x3011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM3_FCT_MCU1           FSM3_FCT_MCU   /* MCU1 NRT node */
#define FSM3_FCT_MCU1_EMGRP1    0x301A         /* MCU1 RT node */
#define FSM3_FCT_MCU2           0x3021         /* MCU2 NRT node */
#define FSM3_FCT_MCU2_EMGRP1    0x302A         /* MCU2 RT node */
#define FSM4_FCT_MCU            0x4011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM4_FCT_MCU1           FSM4_FCT_MCU   /* MCU1 NRT node */
#define FSM4_FCT_MCU1_EMGRP1    0x401A         /* MCU1 RT node */
#define FSM4_FCT_MCU2           0x4021         /* MCU2 NRT node */
#define FSM4_FCT_MCU2_EMGRP1    0x402A         /* MCU2 RT node */
#define FSM5_FCT_MCU            0x5011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM5_FCT_MCU1           FSM5_FCT_MCU   /* MCU1 NRT node */
#define FSM5_FCT_MCU1_EMGRP1    0x501A         /* MCU1 RT node */
#define FSM5_FCT_MCU2           0x5021         /* MCU2 NRT node */
#define FSM5_FCT_MCU2_EMGRP1    0x502A         /* MCU2 RT node */
#define FSM6_FCT_MCU            0x6011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM6_FCT_MCU1           FSM6_FCT_MCU   /* MCU1 NRT node */
#define FSM6_FCT_MCU1_EMGRP1    0x601A         /* MCU1 RT node */
#define FSM6_FCT_MCU2           0x6021         /* MCU2 NRT node */
#define FSM6_FCT_MCU2_EMGRP1    0x602A         /* MCU2 RT node */
#define FSM7_FCT_MCU            0x7011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM7_FCT_MCU1           FSM7_FCT_MCU   /* MCU1 NRT node */
#define FSM7_FCT_MCU1_EMGRP1    0x701A         /* MCU1 RT node */
#define FSM7_FCT_MCU2           0x7021         /* MCU2 NRT node */
#define FSM7_FCT_MCU2_EMGRP1    0x702A         /* MCU2 RT node */
#define FSM8_FCT_MCU            0x8011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM8_FCT_MCU1           FSM8_FCT_MCU   /* MCU1 NRT node */
#define FSM8_FCT_MCU1_EMGRP1    0x801A         /* MCU1 RT node */
#define FSM8_FCT_MCU2           0x8021         /* MCU2 NRT node */
#define FSM8_FCT_MCU2_EMGRP1    0x802A         /* MCU2 RT node */
#define FSM9_FCT_MCU            0x9011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM9_FCT_MCU1           FSM9_FCT_MCU   /* MCU1 NRT node */
#define FSM9_FCT_MCU1_EMGRP1    0x901A         /* MCU1 RT node */
#define FSM9_FCT_MCU2           0x9021         /* MCU2 NRT node */
#define FSM9_FCT_MCU2_EMGRP1    0x902A         /* MCU2 RT node */
#define FSM10_FCT_MCU           0xA011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM10_FCT_MCU1          FSM10_FCT_MCU  /* MCU1 NRT node */
#define FSM10_FCT_MCU1_EMGRP1   0xA01A         /* MCU1 RT node */
#define FSM10_FCT_MCU2          0xA021         /* MCU2 NRT node */
#define FSM10_FCT_MCU2_EMGRP1   0xA02A         /* MCU2 RT node */
#define FSM11_FCT_MCU           0xB011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM11_FCT_MCU1          FSM11_FCT_MCU  /* MCU1 NRT node */
#define FSM11_FCT_MCU1_EMGRP1   0xB01A         /* MCU1 RT node */
#define FSM11_FCT_MCU2          0xB021         /* MCU2 NRT node */
#define FSM11_FCT_MCU2_EMGRP1   0xB02A         /* MCU2 RT node */
#define FSM12_FCT_MCU           0xC011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM12_FCT_MCU1          FSM12_FCT_MCU  /* MCU1 NRT node */
#define FSM12_FCT_MCU1_EMGRP1   0xC01A         /* MCU1 RT node */
#define FSM12_FCT_MCU2          0xC021         /* MCU2 NRT node */
#define FSM12_FCT_MCU2_EMGRP1   0xC02A         /* MCU2 RT node */
#define FSM13_FCT_MCU           0xD011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM13_FCT_MCU1          FSM13_FCT_MCU  /* MCU1 NRT node */
#define FSM13_FCT_MCU1_EMGRP1   0xD01A         /* MCU1 RT node */
#define FSM13_FCT_MCU2          0xD021         /* MCU2 NRT node */
#define FSM13_FCT_MCU2_EMGRP1   0xD02A         /* MCU2 RT node */
#define FSM14_FCT_MCU           0xE011         /* Obsolete: Use FSMx_FCT_MCU1 instead */
#define FSM14_FCT_MCU1          FSM14_FCT_MCU  /* MCU1 NRT node */
#define FSM14_FCT_MCU1_EMGRP1   0xE01A         /* MCU1 RT node */
#define FSM14_FCT_MCU2          0xE021         /* MCU2 NRT node */
#define FSM14_FCT_MCU2_EMGRP1   0xE02A         /* MCU2 RT node */

/* Node ID definitions for SM3
 * NodeID               = boardID + cpuID
 * FSM1_FSP1 + CHIP1    = 0x12    + 0x30  = 0x1230
 * etc. */
#define FSM1_FSP1_MCU           0x120D
#define FSM1_FSP1_CHIP1         0x1230
#define FSM1_FSP1_CHIP1_CPU1    0x1231
#define FSM1_FSP1_CHIP1_CPU2    0x1232
#define FSM1_FSP1_CHIP1_CPU3    0x1233
#define FSM1_FSP1_CHIP1_CPU4    0x1234
#define FSM1_FSP1_CHIP1_CPU5    0x1235
#define FSM1_FSP1_CHIP1_CPU6    0x1236
#define FSM1_FSP1_CHIP1_CPU7    0x1237
#define FSM1_FSP1_CHIP1_CPU8    0x1238
#define FSM1_FSP1_CHIP1_SMP1    0x123D /* FSM-r4 */

#define FSM1_FSP1_CHIP2         0x1240
#define FSM1_FSP1_CHIP2_CPU1    0x1241
#define FSM1_FSP1_CHIP2_CPU2    0x1242
#define FSM1_FSP1_CHIP2_CPU3    0x1243
#define FSM1_FSP1_CHIP2_CPU4    0x1244
#define FSM1_FSP1_CHIP2_CPU5    0x1245
#define FSM1_FSP1_CHIP2_CPU6    0x1246
#define FSM1_FSP1_CHIP2_CPU7    0x1247
#define FSM1_FSP1_CHIP2_CPU8    0x1248
#define FSM1_FSP1_CHIP2_SMP1    0x124D /* FSM-r4 */

#define FSM1_FSP1_CHIP3         0x1250
#define FSM1_FSP1_CHIP3_CPU1    0x1251
#define FSM1_FSP1_CHIP3_CPU2    0x1252
#define FSM1_FSP1_CHIP3_CPU3    0x1253
#define FSM1_FSP1_CHIP3_CPU4    0x1254
#define FSM1_FSP1_CHIP3_CPU5    0x1255
#define FSM1_FSP1_CHIP3_CPU6    0x1256
#define FSM1_FSP1_CHIP3_CPU7    0x1257
#define FSM1_FSP1_CHIP3_CPU8    0x1258
#define FSM1_FSP1_CHIP3_SMP1    0x125D /* FSM-r4 */

#define FSM1_FSP1_CHIP4         0x1260
#define FSM1_FSP1_CHIP4_CPU1    0x1261
#define FSM1_FSP1_CHIP4_CPU2    0x1262
#define FSM1_FSP1_CHIP4_CPU3    0x1263
#define FSM1_FSP1_CHIP4_CPU4    0x1264
#define FSM1_FSP1_CHIP4_CPU5    0x1265
#define FSM1_FSP1_CHIP4_CPU6    0x1266
#define FSM1_FSP1_CHIP4_CPU7    0x1267
#define FSM1_FSP1_CHIP4_CPU8    0x1268
#define FSM1_FSP1_CHIP4_SMP1    0x126D /* FSM-r4 */

#define FSM1_FSP1_CHIP5         0x1270
#define FSM1_FSP1_CHIP5_CPU1    0x1271
#define FSM1_FSP1_CHIP5_CPU2    0x1272
#define FSM1_FSP1_CHIP5_CPU3    0x1273
#define FSM1_FSP1_CHIP5_CPU4    0x1274
#define FSM1_FSP1_CHIP5_CPU5    0x1275
#define FSM1_FSP1_CHIP5_CPU6    0x1276
#define FSM1_FSP1_CHIP5_CPU7    0x1277
#define FSM1_FSP1_CHIP5_CPU8    0x1278

#define FSM1_FSP1_CHIP6         0x1280
#define FSM1_FSP1_CHIP6_CPU1    0x1281
#define FSM1_FSP1_CHIP6_CPU2    0x1282
#define FSM1_FSP1_CHIP6_CPU3    0x1283
#define FSM1_FSP1_CHIP6_CPU4    0x1284
#define FSM1_FSP1_CHIP6_CPU5    0x1285
#define FSM1_FSP1_CHIP6_CPU6    0x1286
#define FSM1_FSP1_CHIP6_CPU7    0x1287
#define FSM1_FSP1_CHIP6_CPU8    0x1288

#define FSM1_FSP1_CHIP7         0x1290
#define FSM1_FSP1_CHIP7_CPU1    0x1291
#define FSM1_FSP1_CHIP7_CPU2    0x1292
#define FSM1_FSP1_CHIP7_CPU3    0x1293
#define FSM1_FSP1_CHIP7_CPU4    0x1294
#define FSM1_FSP1_CHIP7_CPU5    0x1295
#define FSM1_FSP1_CHIP7_CPU6    0x1296
#define FSM1_FSP1_CHIP7_CPU7    0x1297
#define FSM1_FSP1_CHIP7_CPU8    0x1298

#define FSM1_FSP1_CHIP8         0x12A0
#define FSM1_FSP1_CHIP8_CPU1    0x12A1
#define FSM1_FSP1_CHIP8_CPU2    0x12A2
#define FSM1_FSP1_CHIP8_CPU3    0x12A3
#define FSM1_FSP1_CHIP8_CPU4    0x12A4
#define FSM1_FSP1_CHIP8_CPU5    0x12A5
#define FSM1_FSP1_CHIP8_CPU6    0x12A6
#define FSM1_FSP1_CHIP8_CPU7    0x12A7
#define FSM1_FSP1_CHIP8_CPU8    0x12A8

#define FSM1_FSP1_CHIP9         0x12B0
#define FSM1_FSP1_CHIP9_CPU1    0x12B1
#define FSM1_FSP1_CHIP9_CPU2    0x12B2
#define FSM1_FSP1_CHIP9_CPU3    0x12B3
#define FSM1_FSP1_CHIP9_CPU4    0x12B4
#define FSM1_FSP1_CHIP9_CPU5    0x12B5
#define FSM1_FSP1_CHIP9_CPU6    0x12B6
#define FSM1_FSP1_CHIP9_CPU7    0x12B7
#define FSM1_FSP1_CHIP9_CPU8    0x12B8

#define FSM1_FSP1_CHIPALL       0x12F0

/* FSM1_FSP2 */
#define FSM1_FSP2_MCU           0x130D
#define FSM1_FSP2_CHIP1         0x1330
#define FSM1_FSP2_CHIP1_CPU1    0x1331
#define FSM1_FSP2_CHIP1_CPU2    0x1332
#define FSM1_FSP2_CHIP1_CPU3    0x1333
#define FSM1_FSP2_CHIP1_CPU4    0x1334
#define FSM1_FSP2_CHIP1_CPU5    0x1335
#define FSM1_FSP2_CHIP1_CPU6    0x1336
#define FSM1_FSP2_CHIP1_CPU7    0x1337
#define FSM1_FSP2_CHIP1_CPU8    0x1338
#define FSM1_FSP2_CHIP1_SMP1    0x133D /* FSM-r4 */

#define FSM1_FSP2_CHIP2         0x1340
#define FSM1_FSP2_CHIP2_CPU1    0x1341
#define FSM1_FSP2_CHIP2_CPU2    0x1342
#define FSM1_FSP2_CHIP2_CPU3    0x1343
#define FSM1_FSP2_CHIP2_CPU4    0x1344
#define FSM1_FSP2_CHIP2_CPU5    0x1345
#define FSM1_FSP2_CHIP2_CPU6    0x1346
#define FSM1_FSP2_CHIP2_CPU7    0x1347
#define FSM1_FSP2_CHIP2_CPU8    0x1348
#define FSM1_FSP2_CHIP2_SMP1    0x134D /* FSM-r4 */

#define FSM1_FSP2_CHIP3         0x1350
#define FSM1_FSP2_CHIP3_CPU1    0x1351
#define FSM1_FSP2_CHIP3_CPU2    0x1352
#define FSM1_FSP2_CHIP3_CPU3    0x1353
#define FSM1_FSP2_CHIP3_CPU4    0x1354
#define FSM1_FSP2_CHIP3_CPU5    0x1355
#define FSM1_FSP2_CHIP3_CPU6    0x1356
#define FSM1_FSP2_CHIP3_CPU7    0x1357
#define FSM1_FSP2_CHIP3_CPU8    0x1358
#define FSM1_FSP2_CHIP3_SMP1    0x135D /* FSM-r4 */

#define FSM1_FSP2_CHIP4         0x1360
#define FSM1_FSP2_CHIP4_CPU1    0x1361
#define FSM1_FSP2_CHIP4_CPU2    0x1362
#define FSM1_FSP2_CHIP4_CPU3    0x1363
#define FSM1_FSP2_CHIP4_CPU4    0x1364
#define FSM1_FSP2_CHIP4_CPU5    0x1365
#define FSM1_FSP2_CHIP4_CPU6    0x1366
#define FSM1_FSP2_CHIP4_CPU7    0x1367
#define FSM1_FSP2_CHIP4_CPU8    0x1368
#define FSM1_FSP2_CHIP4_SMP1    0x136D /* FSM-r4 */

#define FSM1_FSP2_CHIP5         0x1370
#define FSM1_FSP2_CHIP5_CPU1    0x1371
#define FSM1_FSP2_CHIP5_CPU2    0x1372
#define FSM1_FSP2_CHIP5_CPU3    0x1373
#define FSM1_FSP2_CHIP5_CPU4    0x1374
#define FSM1_FSP2_CHIP5_CPU5    0x1375
#define FSM1_FSP2_CHIP5_CPU6    0x1376
#define FSM1_FSP2_CHIP5_CPU7    0x1377
#define FSM1_FSP2_CHIP5_CPU8    0x1378

#define FSM1_FSP2_CHIP6         0x1380
#define FSM1_FSP2_CHIP6_CPU1    0x1381
#define FSM1_FSP2_CHIP6_CPU2    0x1382
#define FSM1_FSP2_CHIP6_CPU3    0x1383
#define FSM1_FSP2_CHIP6_CPU4    0x1384
#define FSM1_FSP2_CHIP6_CPU5    0x1385
#define FSM1_FSP2_CHIP6_CPU6    0x1386
#define FSM1_FSP2_CHIP6_CPU7    0x1387
#define FSM1_FSP2_CHIP6_CPU8    0x1388

#define FSM1_FSP2_CHIP7         0x1390
#define FSM1_FSP2_CHIP7_CPU1    0x1391
#define FSM1_FSP2_CHIP7_CPU2    0x1392
#define FSM1_FSP2_CHIP7_CPU3    0x1393
#define FSM1_FSP2_CHIP7_CPU4    0x1394
#define FSM1_FSP2_CHIP7_CPU5    0x1395
#define FSM1_FSP2_CHIP7_CPU6    0x1396
#define FSM1_FSP2_CHIP7_CPU7    0x1397
#define FSM1_FSP2_CHIP7_CPU8    0x1398

#define FSM1_FSP2_CHIP8         0x13A0
#define FSM1_FSP2_CHIP8_CPU1    0x13A1
#define FSM1_FSP2_CHIP8_CPU2    0x13A2
#define FSM1_FSP2_CHIP8_CPU3    0x13A3
#define FSM1_FSP2_CHIP8_CPU4    0x13A4
#define FSM1_FSP2_CHIP8_CPU5    0x13A5
#define FSM1_FSP2_CHIP8_CPU6    0x13A6
#define FSM1_FSP2_CHIP8_CPU7    0x13A7
#define FSM1_FSP2_CHIP8_CPU8    0x13A8

#define FSM1_FSP2_CHIP9         0x13B0
#define FSM1_FSP2_CHIP9_CPU1    0x13B1
#define FSM1_FSP2_CHIP9_CPU2    0x13B2
#define FSM1_FSP2_CHIP9_CPU3    0x13B3
#define FSM1_FSP2_CHIP9_CPU4    0x13B4
#define FSM1_FSP2_CHIP9_CPU5    0x13B5
#define FSM1_FSP2_CHIP9_CPU6    0x13B6
#define FSM1_FSP2_CHIP9_CPU7    0x13B7
#define FSM1_FSP2_CHIP9_CPU8    0x13B8

#define FSM1_FSP2_CHIPALL       0x13F0

/* FSM1_FSP3 */
#define FSM1_FSP3_MCU           0x140D
#define FSM1_FSP3_CHIP1         0x1430
#define FSM1_FSP3_CHIP1_CPU1    0x1431
#define FSM1_FSP3_CHIP1_CPU2    0x1432
#define FSM1_FSP3_CHIP1_CPU3    0x1433
#define FSM1_FSP3_CHIP1_CPU4    0x1434
#define FSM1_FSP3_CHIP1_CPU5    0x1435
#define FSM1_FSP3_CHIP1_CPU6    0x1436
#define FSM1_FSP3_CHIP1_CPU7    0x1437
#define FSM1_FSP3_CHIP1_CPU8    0x1438
#define FSM1_FSP3_CHIP1_SMP1    0x143D /* FSM-r4 */

#define FSM1_FSP3_CHIP2         0x1440
#define FSM1_FSP3_CHIP2_CPU1    0x1441
#define FSM1_FSP3_CHIP2_CPU2    0x1442
#define FSM1_FSP3_CHIP2_CPU3    0x1443
#define FSM1_FSP3_CHIP2_CPU4    0x1444
#define FSM1_FSP3_CHIP2_CPU5    0x1445
#define FSM1_FSP3_CHIP2_CPU6    0x1446
#define FSM1_FSP3_CHIP2_CPU7    0x1447
#define FSM1_FSP3_CHIP2_CPU8    0x1448
#define FSM1_FSP3_CHIP2_SMP1    0x144D /* FSM-r4 */

#define FSM1_FSP3_CHIP3         0x1450
#define FSM1_FSP3_CHIP3_CPU1    0x1451
#define FSM1_FSP3_CHIP3_CPU2    0x1452
#define FSM1_FSP3_CHIP3_CPU3    0x1453
#define FSM1_FSP3_CHIP3_CPU4    0x1454
#define FSM1_FSP3_CHIP3_CPU5    0x1455
#define FSM1_FSP3_CHIP3_CPU6    0x1456
#define FSM1_FSP3_CHIP3_CPU7    0x1457
#define FSM1_FSP3_CHIP3_CPU8    0x1458
#define FSM1_FSP3_CHIP3_SMP1    0x145D /* FSM-r4 */

#define FSM1_FSP3_CHIP4         0x1460
#define FSM1_FSP3_CHIP4_CPU1    0x1461
#define FSM1_FSP3_CHIP4_CPU2    0x1462
#define FSM1_FSP3_CHIP4_CPU3    0x1463
#define FSM1_FSP3_CHIP4_CPU4    0x1464
#define FSM1_FSP3_CHIP4_CPU5    0x1465
#define FSM1_FSP3_CHIP4_CPU6    0x1466
#define FSM1_FSP3_CHIP4_CPU7    0x1467
#define FSM1_FSP3_CHIP4_CPU8    0x1468
#define FSM1_FSP3_CHIP4_SMP1    0x146D /* FSM-r4 */

#define FSM1_FSP3_CHIP5         0x1470
#define FSM1_FSP3_CHIP5_CPU1    0x1471
#define FSM1_FSP3_CHIP5_CPU2    0x1472
#define FSM1_FSP3_CHIP5_CPU3    0x1473
#define FSM1_FSP3_CHIP5_CPU4    0x1474
#define FSM1_FSP3_CHIP5_CPU5    0x1475
#define FSM1_FSP3_CHIP5_CPU6    0x1476
#define FSM1_FSP3_CHIP5_CPU7    0x1477
#define FSM1_FSP3_CHIP5_CPU8    0x1478

#define FSM1_FSP3_CHIP6         0x1480
#define FSM1_FSP3_CHIP6_CPU1    0x1481
#define FSM1_FSP3_CHIP6_CPU2    0x1482
#define FSM1_FSP3_CHIP6_CPU3    0x1483
#define FSM1_FSP3_CHIP6_CPU4    0x1484
#define FSM1_FSP3_CHIP6_CPU5    0x1485
#define FSM1_FSP3_CHIP6_CPU6    0x1486
#define FSM1_FSP3_CHIP6_CPU7    0x1487
#define FSM1_FSP3_CHIP6_CPU8    0x1488

#define FSM1_FSP3_CHIP7         0x1490
#define FSM1_FSP3_CHIP7_CPU1    0x1491
#define FSM1_FSP3_CHIP7_CPU2    0x1492
#define FSM1_FSP3_CHIP7_CPU3    0x1493
#define FSM1_FSP3_CHIP7_CPU4    0x1494
#define FSM1_FSP3_CHIP7_CPU5    0x1495
#define FSM1_FSP3_CHIP7_CPU6    0x1496
#define FSM1_FSP3_CHIP7_CPU7    0x1497
#define FSM1_FSP3_CHIP7_CPU8    0x1498

#define FSM1_FSP3_CHIP8         0x14A0
#define FSM1_FSP3_CHIP8_CPU1    0x14A1
#define FSM1_FSP3_CHIP8_CPU2    0x14A2
#define FSM1_FSP3_CHIP8_CPU3    0x14A3
#define FSM1_FSP3_CHIP8_CPU4    0x14A4
#define FSM1_FSP3_CHIP8_CPU5    0x14A5
#define FSM1_FSP3_CHIP8_CPU6    0x14A6
#define FSM1_FSP3_CHIP8_CPU7    0x14A7
#define FSM1_FSP3_CHIP8_CPU8    0x14A8

#define FSM1_FSP3_CHIP9         0x14B0
#define FSM1_FSP3_CHIP9_CPU1    0x14B1
#define FSM1_FSP3_CHIP9_CPU2    0x14B2
#define FSM1_FSP3_CHIP9_CPU3    0x14B3
#define FSM1_FSP3_CHIP9_CPU4    0x14B4
#define FSM1_FSP3_CHIP9_CPU5    0x14B5
#define FSM1_FSP3_CHIP9_CPU6    0x14B6
#define FSM1_FSP3_CHIP9_CPU7    0x14B7
#define FSM1_FSP3_CHIP9_CPU8    0x14B8

#define FSM1_FSP3_CHIPALL       0x14F0

/* FSM2_FSP1 */
#define FSM2_FSP1_MCU           0x220D
#define FSM2_FSP1_CHIP1         0x2230
#define FSM2_FSP1_CHIP1_CPU1    0x2231
#define FSM2_FSP1_CHIP1_CPU2    0x2232
#define FSM2_FSP1_CHIP1_CPU3    0x2233
#define FSM2_FSP1_CHIP1_CPU4    0x2234
#define FSM2_FSP1_CHIP1_CPU5    0x2235
#define FSM2_FSP1_CHIP1_CPU6    0x2236
#define FSM2_FSP1_CHIP1_CPU7    0x2237
#define FSM2_FSP1_CHIP1_CPU8    0x2238
#define FSM2_FSP1_CHIP1_SMP1    0x223D /* FSM-r4 */

#define FSM2_FSP1_CHIP2         0x2240
#define FSM2_FSP1_CHIP2_CPU1    0x2241
#define FSM2_FSP1_CHIP2_CPU2    0x2242
#define FSM2_FSP1_CHIP2_CPU3    0x2243
#define FSM2_FSP1_CHIP2_CPU4    0x2244
#define FSM2_FSP1_CHIP2_CPU5    0x2245
#define FSM2_FSP1_CHIP2_CPU6    0x2246
#define FSM2_FSP1_CHIP2_CPU7    0x2247
#define FSM2_FSP1_CHIP2_CPU8    0x2248
#define FSM2_FSP1_CHIP2_SMP1    0x224D /* FSM-r4 */

#define FSM2_FSP1_CHIP3         0x2250
#define FSM2_FSP1_CHIP3_CPU1    0x2251
#define FSM2_FSP1_CHIP3_CPU2    0x2252
#define FSM2_FSP1_CHIP3_CPU3    0x2253
#define FSM2_FSP1_CHIP3_CPU4    0x2254
#define FSM2_FSP1_CHIP3_CPU5    0x2255
#define FSM2_FSP1_CHIP3_CPU6    0x2256
#define FSM2_FSP1_CHIP3_CPU7    0x2257
#define FSM2_FSP1_CHIP3_CPU8    0x2258
#define FSM2_FSP1_CHIP3_SMP1    0x225D /* FSM-r4 */

#define FSM2_FSP1_CHIP4         0x2260
#define FSM2_FSP1_CHIP4_CPU1    0x2261
#define FSM2_FSP1_CHIP4_CPU2    0x2262
#define FSM2_FSP1_CHIP4_CPU3    0x2263
#define FSM2_FSP1_CHIP4_CPU4    0x2264
#define FSM2_FSP1_CHIP4_CPU5    0x2265
#define FSM2_FSP1_CHIP4_CPU6    0x2266
#define FSM2_FSP1_CHIP4_CPU7    0x2267
#define FSM2_FSP1_CHIP4_CPU8    0x2268
#define FSM2_FSP1_CHIP4_SMP1    0x226D /* FSM-r4 */

#define FSM2_FSP1_CHIP5         0x2270
#define FSM2_FSP1_CHIP5_CPU1    0x2271
#define FSM2_FSP1_CHIP5_CPU2    0x2272
#define FSM2_FSP1_CHIP5_CPU3    0x2273
#define FSM2_FSP1_CHIP5_CPU4    0x2274
#define FSM2_FSP1_CHIP5_CPU5    0x2275
#define FSM2_FSP1_CHIP5_CPU6    0x2276
#define FSM2_FSP1_CHIP5_CPU7    0x2277
#define FSM2_FSP1_CHIP5_CPU8    0x2278

#define FSM2_FSP1_CHIP6         0x2280
#define FSM2_FSP1_CHIP6_CPU1    0x2281
#define FSM2_FSP1_CHIP6_CPU2    0x2282
#define FSM2_FSP1_CHIP6_CPU3    0x2283
#define FSM2_FSP1_CHIP6_CPU4    0x2284
#define FSM2_FSP1_CHIP6_CPU5    0x2285
#define FSM2_FSP1_CHIP6_CPU6    0x2286
#define FSM2_FSP1_CHIP6_CPU7    0x2287
#define FSM2_FSP1_CHIP6_CPU8    0x2288

#define FSM2_FSP1_CHIP7         0x2290
#define FSM2_FSP1_CHIP7_CPU1    0x2291
#define FSM2_FSP1_CHIP7_CPU2    0x2292
#define FSM2_FSP1_CHIP7_CPU3    0x2293
#define FSM2_FSP1_CHIP7_CPU4    0x2294
#define FSM2_FSP1_CHIP7_CPU5    0x2295
#define FSM2_FSP1_CHIP7_CPU6    0x2296
#define FSM2_FSP1_CHIP7_CPU7    0x2297
#define FSM2_FSP1_CHIP7_CPU8    0x2298

#define FSM2_FSP1_CHIP8         0x22A0
#define FSM2_FSP1_CHIP8_CPU1    0x22A1
#define FSM2_FSP1_CHIP8_CPU2    0x22A2
#define FSM2_FSP1_CHIP8_CPU3    0x22A3
#define FSM2_FSP1_CHIP8_CPU4    0x22A4
#define FSM2_FSP1_CHIP8_CPU5    0x22A5
#define FSM2_FSP1_CHIP8_CPU6    0x22A6
#define FSM2_FSP1_CHIP8_CPU7    0x22A7
#define FSM2_FSP1_CHIP8_CPU8    0x22A8

#define FSM2_FSP1_CHIP9         0x22B0
#define FSM2_FSP1_CHIP9_CPU1    0x22B1
#define FSM2_FSP1_CHIP9_CPU2    0x22B2
#define FSM2_FSP1_CHIP9_CPU3    0x22B3
#define FSM2_FSP1_CHIP9_CPU4    0x22B4
#define FSM2_FSP1_CHIP9_CPU5    0x22B5
#define FSM2_FSP1_CHIP9_CPU6    0x22B6
#define FSM2_FSP1_CHIP9_CPU7    0x22B7
#define FSM2_FSP1_CHIP9_CPU8    0x22B8

#define FSM2_FSP1_CHIPALL       0x22F0

/* FSM2_FSP2 */
#define FSM2_FSP2_MCU           0x230D
#define FSM2_FSP2_CHIP1         0x2330
#define FSM2_FSP2_CHIP1_CPU1    0x2331
#define FSM2_FSP2_CHIP1_CPU2    0x2332
#define FSM2_FSP2_CHIP1_CPU3    0x2333
#define FSM2_FSP2_CHIP1_CPU4    0x2334
#define FSM2_FSP2_CHIP1_CPU5    0x2335
#define FSM2_FSP2_CHIP1_CPU6    0x2336
#define FSM2_FSP2_CHIP1_CPU7    0x2337
#define FSM2_FSP2_CHIP1_CPU8    0x2338
#define FSM2_FSP2_CHIP1_SMP1    0x233D /* FSM-r4 */

#define FSM2_FSP2_CHIP2         0x2340
#define FSM2_FSP2_CHIP2_CPU1    0x2341
#define FSM2_FSP2_CHIP2_CPU2    0x2342
#define FSM2_FSP2_CHIP2_CPU3    0x2343
#define FSM2_FSP2_CHIP2_CPU4    0x2344
#define FSM2_FSP2_CHIP2_CPU5    0x2345
#define FSM2_FSP2_CHIP2_CPU6    0x2346
#define FSM2_FSP2_CHIP2_CPU7    0x2347
#define FSM2_FSP2_CHIP2_CPU8    0x2348
#define FSM2_FSP2_CHIP2_SMP1    0x234D /* FSM-r4 */

#define FSM2_FSP2_CHIP3         0x2350
#define FSM2_FSP2_CHIP3_CPU1    0x2351
#define FSM2_FSP2_CHIP3_CPU2    0x2352
#define FSM2_FSP2_CHIP3_CPU3    0x2353
#define FSM2_FSP2_CHIP3_CPU4    0x2354
#define FSM2_FSP2_CHIP3_CPU5    0x2355
#define FSM2_FSP2_CHIP3_CPU6    0x2356
#define FSM2_FSP2_CHIP3_CPU7    0x2357
#define FSM2_FSP2_CHIP3_CPU8    0x2358
#define FSM2_FSP2_CHIP3_SMP1    0x235D /* FSM-r4 */

#define FSM2_FSP2_CHIP4         0x2360
#define FSM2_FSP2_CHIP4_CPU1    0x2361
#define FSM2_FSP2_CHIP4_CPU2    0x2362
#define FSM2_FSP2_CHIP4_CPU3    0x2363
#define FSM2_FSP2_CHIP4_CPU4    0x2364
#define FSM2_FSP2_CHIP4_CPU5    0x2365
#define FSM2_FSP2_CHIP4_CPU6    0x2366
#define FSM2_FSP2_CHIP4_CPU7    0x2367
#define FSM2_FSP2_CHIP4_CPU8    0x2368
#define FSM2_FSP2_CHIP4_SMP1    0x236D /* FSM-r4 */

#define FSM2_FSP2_CHIP5         0x2370
#define FSM2_FSP2_CHIP5_CPU1    0x2371
#define FSM2_FSP2_CHIP5_CPU2    0x2372
#define FSM2_FSP2_CHIP5_CPU3    0x2373
#define FSM2_FSP2_CHIP5_CPU4    0x2374
#define FSM2_FSP2_CHIP5_CPU5    0x2375
#define FSM2_FSP2_CHIP5_CPU6    0x2376
#define FSM2_FSP2_CHIP5_CPU7    0x2377
#define FSM2_FSP2_CHIP5_CPU8    0x2378

#define FSM2_FSP2_CHIP6         0x2380
#define FSM2_FSP2_CHIP6_CPU1    0x2381
#define FSM2_FSP2_CHIP6_CPU2    0x2382
#define FSM2_FSP2_CHIP6_CPU3    0x2383
#define FSM2_FSP2_CHIP6_CPU4    0x2384
#define FSM2_FSP2_CHIP6_CPU5    0x2385
#define FSM2_FSP2_CHIP6_CPU6    0x2386
#define FSM2_FSP2_CHIP6_CPU7    0x2387
#define FSM2_FSP2_CHIP6_CPU8    0x2388

#define FSM2_FSP2_CHIP7         0x2390
#define FSM2_FSP2_CHIP7_CPU1    0x2391
#define FSM2_FSP2_CHIP7_CPU2    0x2392
#define FSM2_FSP2_CHIP7_CPU3    0x2393
#define FSM2_FSP2_CHIP7_CPU4    0x2394
#define FSM2_FSP2_CHIP7_CPU5    0x2395
#define FSM2_FSP2_CHIP7_CPU6    0x2396
#define FSM2_FSP2_CHIP7_CPU7    0x2397
#define FSM2_FSP2_CHIP7_CPU8    0x2398

#define FSM2_FSP2_CHIP8         0x23A0
#define FSM2_FSP2_CHIP8_CPU1    0x23A1
#define FSM2_FSP2_CHIP8_CPU2    0x23A2
#define FSM2_FSP2_CHIP8_CPU3    0x23A3
#define FSM2_FSP2_CHIP8_CPU4    0x23A4
#define FSM2_FSP2_CHIP8_CPU5    0x23A5
#define FSM2_FSP2_CHIP8_CPU6    0x23A6
#define FSM2_FSP2_CHIP8_CPU7    0x23A7
#define FSM2_FSP2_CHIP8_CPU8    0x23A8

#define FSM2_FSP2_CHIP9         0x23B0
#define FSM2_FSP2_CHIP9_CPU1    0x23B1
#define FSM2_FSP2_CHIP9_CPU2    0x23B2
#define FSM2_FSP2_CHIP9_CPU3    0x23B3
#define FSM2_FSP2_CHIP9_CPU4    0x23B4
#define FSM2_FSP2_CHIP9_CPU5    0x23B5
#define FSM2_FSP2_CHIP9_CPU6    0x23B6
#define FSM2_FSP2_CHIP9_CPU7    0x23B7
#define FSM2_FSP2_CHIP9_CPU8    0x23B8

#define FSM2_FSP2_CHIPALL       0x23F0

/* FSM2_FSP3 */
#define FSM2_FSP3_MCU           0x240D
#define FSM2_FSP3_CHIP1         0x2430
#define FSM2_FSP3_CHIP1_CPU1    0x2431
#define FSM2_FSP3_CHIP1_CPU2    0x2432
#define FSM2_FSP3_CHIP1_CPU3    0x2433
#define FSM2_FSP3_CHIP1_CPU4    0x2434
#define FSM2_FSP3_CHIP1_CPU5    0x2435
#define FSM2_FSP3_CHIP1_CPU6    0x2436
#define FSM2_FSP3_CHIP1_CPU7    0x2437
#define FSM2_FSP3_CHIP1_CPU8    0x2438
#define FSM2_FSP3_CHIP1_SMP1    0x243D /* FSM-r4 */

#define FSM2_FSP3_CHIP2         0x2440
#define FSM2_FSP3_CHIP2_CPU1    0x2441
#define FSM2_FSP3_CHIP2_CPU2    0x2442
#define FSM2_FSP3_CHIP2_CPU3    0x2443
#define FSM2_FSP3_CHIP2_CPU4    0x2444
#define FSM2_FSP3_CHIP2_CPU5    0x2445
#define FSM2_FSP3_CHIP2_CPU6    0x2446
#define FSM2_FSP3_CHIP2_CPU7    0x2447
#define FSM2_FSP3_CHIP2_CPU8    0x2448
#define FSM2_FSP3_CHIP2_SMP1    0x244D /* FSM-r4 */

#define FSM2_FSP3_CHIP3         0x2450
#define FSM2_FSP3_CHIP3_CPU1    0x2451
#define FSM2_FSP3_CHIP3_CPU2    0x2452
#define FSM2_FSP3_CHIP3_CPU3    0x2453
#define FSM2_FSP3_CHIP3_CPU4    0x2454
#define FSM2_FSP3_CHIP3_CPU5    0x2455
#define FSM2_FSP3_CHIP3_CPU6    0x2456
#define FSM2_FSP3_CHIP3_CPU7    0x2457
#define FSM2_FSP3_CHIP3_CPU8    0x2458
#define FSM2_FSP3_CHIP3_SMP1    0x245D /* FSM-r4 */

#define FSM2_FSP3_CHIP4         0x2460
#define FSM2_FSP3_CHIP4_CPU1    0x2461
#define FSM2_FSP3_CHIP4_CPU2    0x2462
#define FSM2_FSP3_CHIP4_CPU3    0x2463
#define FSM2_FSP3_CHIP4_CPU4    0x2464
#define FSM2_FSP3_CHIP4_CPU5    0x2465
#define FSM2_FSP3_CHIP4_CPU6    0x2466
#define FSM2_FSP3_CHIP4_CPU7    0x2467
#define FSM2_FSP3_CHIP4_CPU8    0x2468
#define FSM2_FSP3_CHIP4_SMP1    0x246D /* FSM-r4 */

#define FSM2_FSP3_CHIP5         0x2470
#define FSM2_FSP3_CHIP5_CPU1    0x2471
#define FSM2_FSP3_CHIP5_CPU2    0x2472
#define FSM2_FSP3_CHIP5_CPU3    0x2473
#define FSM2_FSP3_CHIP5_CPU4    0x2474
#define FSM2_FSP3_CHIP5_CPU5    0x2475
#define FSM2_FSP3_CHIP5_CPU6    0x2476
#define FSM2_FSP3_CHIP5_CPU7    0x2477
#define FSM2_FSP3_CHIP5_CPU8    0x2478

#define FSM2_FSP3_CHIP6         0x2480
#define FSM2_FSP3_CHIP6_CPU1    0x2481
#define FSM2_FSP3_CHIP6_CPU2    0x2482
#define FSM2_FSP3_CHIP6_CPU3    0x2483
#define FSM2_FSP3_CHIP6_CPU4    0x2484
#define FSM2_FSP3_CHIP6_CPU5    0x2485
#define FSM2_FSP3_CHIP6_CPU6    0x2486
#define FSM2_FSP3_CHIP6_CPU7    0x2487
#define FSM2_FSP3_CHIP6_CPU8    0x2488

#define FSM2_FSP3_CHIP7         0x2490
#define FSM2_FSP3_CHIP7_CPU1    0x2491
#define FSM2_FSP3_CHIP7_CPU2    0x2492
#define FSM2_FSP3_CHIP7_CPU3    0x2493
#define FSM2_FSP3_CHIP7_CPU4    0x2494
#define FSM2_FSP3_CHIP7_CPU5    0x2495
#define FSM2_FSP3_CHIP7_CPU6    0x2496
#define FSM2_FSP3_CHIP7_CPU7    0x2497
#define FSM2_FSP3_CHIP7_CPU8    0x2498

#define FSM2_FSP3_CHIP8         0x24A0
#define FSM2_FSP3_CHIP8_CPU1    0x24A1
#define FSM2_FSP3_CHIP8_CPU2    0x24A2
#define FSM2_FSP3_CHIP8_CPU3    0x24A3
#define FSM2_FSP3_CHIP8_CPU4    0x24A4
#define FSM2_FSP3_CHIP8_CPU5    0x24A5
#define FSM2_FSP3_CHIP8_CPU6    0x24A6
#define FSM2_FSP3_CHIP8_CPU7    0x24A7
#define FSM2_FSP3_CHIP8_CPU8    0x24A8

#define FSM2_FSP3_CHIP9         0x24B0
#define FSM2_FSP3_CHIP9_CPU1    0x24B1
#define FSM2_FSP3_CHIP9_CPU2    0x24B2
#define FSM2_FSP3_CHIP9_CPU3    0x24B3
#define FSM2_FSP3_CHIP9_CPU4    0x24B4
#define FSM2_FSP3_CHIP9_CPU5    0x24B5
#define FSM2_FSP3_CHIP9_CPU6    0x24B6
#define FSM2_FSP3_CHIP9_CPU7    0x24B7
#define FSM2_FSP3_CHIP9_CPU8    0x24B8

#define FSM2_FSP3_CHIPALL       0x24F0

/* FSM3_FSP1 */
#define FSM3_FSP1_MCU           0x320D
#define FSM3_FSP1_CHIP1         0x3230
#define FSM3_FSP1_CHIP1_CPU1    0x3231
#define FSM3_FSP1_CHIP1_CPU2    0x3232
#define FSM3_FSP1_CHIP1_CPU3    0x3233
#define FSM3_FSP1_CHIP1_CPU4    0x3234
#define FSM3_FSP1_CHIP1_CPU5    0x3235
#define FSM3_FSP1_CHIP1_CPU6    0x3236
#define FSM3_FSP1_CHIP1_CPU7    0x3237
#define FSM3_FSP1_CHIP1_CPU8    0x3238
#define FSM3_FSP1_CHIP1_SMP1    0x323D /* FSM-r4 */

#define FSM3_FSP1_CHIP2         0x3240
#define FSM3_FSP1_CHIP2_CPU1    0x3241
#define FSM3_FSP1_CHIP2_CPU2    0x3242
#define FSM3_FSP1_CHIP2_CPU3    0x3243
#define FSM3_FSP1_CHIP2_CPU4    0x3244
#define FSM3_FSP1_CHIP2_CPU5    0x3245
#define FSM3_FSP1_CHIP2_CPU6    0x3246
#define FSM3_FSP1_CHIP2_CPU7    0x3247
#define FSM3_FSP1_CHIP2_CPU8    0x3248
#define FSM3_FSP1_CHIP2_SMP1    0x324D /* FSM-r4 */

#define FSM3_FSP1_CHIP3         0x3250
#define FSM3_FSP1_CHIP3_CPU1    0x3251
#define FSM3_FSP1_CHIP3_CPU2    0x3252
#define FSM3_FSP1_CHIP3_CPU3    0x3253
#define FSM3_FSP1_CHIP3_CPU4    0x3254
#define FSM3_FSP1_CHIP3_CPU5    0x3255
#define FSM3_FSP1_CHIP3_CPU6    0x3256
#define FSM3_FSP1_CHIP3_CPU7    0x3257
#define FSM3_FSP1_CHIP3_CPU8    0x3258
#define FSM3_FSP1_CHIP3_SMP1    0x325D /* FSM-r4 */

#define FSM3_FSP1_CHIP4         0x3260
#define FSM3_FSP1_CHIP4_CPU1    0x3261
#define FSM3_FSP1_CHIP4_CPU2    0x3262
#define FSM3_FSP1_CHIP4_CPU3    0x3263
#define FSM3_FSP1_CHIP4_CPU4    0x3264
#define FSM3_FSP1_CHIP4_CPU5    0x3265
#define FSM3_FSP1_CHIP4_CPU6    0x3266
#define FSM3_FSP1_CHIP4_CPU7    0x3267
#define FSM3_FSP1_CHIP4_CPU8    0x3268
#define FSM3_FSP1_CHIP4_SMP1    0x326D /* FSM-r4 */

#define FSM3_FSP1_CHIP5         0x3270
#define FSM3_FSP1_CHIP5_CPU1    0x3271
#define FSM3_FSP1_CHIP5_CPU2    0x3272
#define FSM3_FSP1_CHIP5_CPU3    0x3273
#define FSM3_FSP1_CHIP5_CPU4    0x3274
#define FSM3_FSP1_CHIP5_CPU5    0x3275
#define FSM3_FSP1_CHIP5_CPU6    0x3276
#define FSM3_FSP1_CHIP5_CPU7    0x3277
#define FSM3_FSP1_CHIP5_CPU8    0x3278

#define FSM3_FSP1_CHIP6         0x3280
#define FSM3_FSP1_CHIP6_CPU1    0x3281
#define FSM3_FSP1_CHIP6_CPU2    0x3282
#define FSM3_FSP1_CHIP6_CPU3    0x3283
#define FSM3_FSP1_CHIP6_CPU4    0x3284
#define FSM3_FSP1_CHIP6_CPU5    0x3285
#define FSM3_FSP1_CHIP6_CPU6    0x3286
#define FSM3_FSP1_CHIP6_CPU7    0x3287
#define FSM3_FSP1_CHIP6_CPU8    0x3288

#define FSM3_FSP1_CHIP7         0x3290
#define FSM3_FSP1_CHIP7_CPU1    0x3291
#define FSM3_FSP1_CHIP7_CPU2    0x3292
#define FSM3_FSP1_CHIP7_CPU3    0x3293
#define FSM3_FSP1_CHIP7_CPU4    0x3294
#define FSM3_FSP1_CHIP7_CPU5    0x3295
#define FSM3_FSP1_CHIP7_CPU6    0x3296
#define FSM3_FSP1_CHIP7_CPU7    0x3297
#define FSM3_FSP1_CHIP7_CPU8    0x3298

#define FSM3_FSP1_CHIP8         0x32A0
#define FSM3_FSP1_CHIP8_CPU1    0x32A1
#define FSM3_FSP1_CHIP8_CPU2    0x32A2
#define FSM3_FSP1_CHIP8_CPU3    0x32A3
#define FSM3_FSP1_CHIP8_CPU4    0x32A4
#define FSM3_FSP1_CHIP8_CPU5    0x32A5
#define FSM3_FSP1_CHIP8_CPU6    0x32A6
#define FSM3_FSP1_CHIP8_CPU7    0x32A7
#define FSM3_FSP1_CHIP8_CPU8    0x32A8

#define FSM3_FSP1_CHIP9         0x32B0
#define FSM3_FSP1_CHIP9_CPU1    0x32B1
#define FSM3_FSP1_CHIP9_CPU2    0x32B2
#define FSM3_FSP1_CHIP9_CPU3    0x32B3
#define FSM3_FSP1_CHIP9_CPU4    0x32B4
#define FSM3_FSP1_CHIP9_CPU5    0x32B5
#define FSM3_FSP1_CHIP9_CPU6    0x32B6
#define FSM3_FSP1_CHIP9_CPU7    0x32B7
#define FSM3_FSP1_CHIP9_CPU8    0x32B8

#define FSM3_FSP1_CHIPALL       0x32F0

/* FSM3_FSP2 */
#define FSM3_FSP2_MCU           0x330D
#define FSM3_FSP2_CHIP1         0x3330
#define FSM3_FSP2_CHIP1_CPU1    0x3331
#define FSM3_FSP2_CHIP1_CPU2    0x3332
#define FSM3_FSP2_CHIP1_CPU3    0x3333
#define FSM3_FSP2_CHIP1_CPU4    0x3334
#define FSM3_FSP2_CHIP1_CPU5    0x3335
#define FSM3_FSP2_CHIP1_CPU6    0x3336
#define FSM3_FSP2_CHIP1_CPU7    0x3337
#define FSM3_FSP2_CHIP1_CPU8    0x3338
#define FSM3_FSP2_CHIP1_SMP1    0x333D /* FSM-r4 */

#define FSM3_FSP2_CHIP2         0x3340
#define FSM3_FSP2_CHIP2_CPU1    0x3341
#define FSM3_FSP2_CHIP2_CPU2    0x3342
#define FSM3_FSP2_CHIP2_CPU3    0x3343
#define FSM3_FSP2_CHIP2_CPU4    0x3344
#define FSM3_FSP2_CHIP2_CPU5    0x3345
#define FSM3_FSP2_CHIP2_CPU6    0x3346
#define FSM3_FSP2_CHIP2_CPU7    0x3347
#define FSM3_FSP2_CHIP2_CPU8    0x3348
#define FSM3_FSP2_CHIP2_SMP1    0x334D /* FSM-r4 */

#define FSM3_FSP2_CHIP3         0x3350
#define FSM3_FSP2_CHIP3_CPU1    0x3351
#define FSM3_FSP2_CHIP3_CPU2    0x3352
#define FSM3_FSP2_CHIP3_CPU3    0x3353
#define FSM3_FSP2_CHIP3_CPU4    0x3354
#define FSM3_FSP2_CHIP3_CPU5    0x3355
#define FSM3_FSP2_CHIP3_CPU6    0x3356
#define FSM3_FSP2_CHIP3_CPU7    0x3357
#define FSM3_FSP2_CHIP3_CPU8    0x3358
#define FSM3_FSP2_CHIP3_SMP1    0x335D /* FSM-r4 */

#define FSM3_FSP2_CHIP4         0x3360
#define FSM3_FSP2_CHIP4_CPU1    0x3361
#define FSM3_FSP2_CHIP4_CPU2    0x3362
#define FSM3_FSP2_CHIP4_CPU3    0x3363
#define FSM3_FSP2_CHIP4_CPU4    0x3364
#define FSM3_FSP2_CHIP4_CPU5    0x3365
#define FSM3_FSP2_CHIP4_CPU6    0x3366
#define FSM3_FSP2_CHIP4_CPU7    0x3367
#define FSM3_FSP2_CHIP4_CPU8    0x3368
#define FSM3_FSP2_CHIP4_SMP1    0x336D /* FSM-r4 */

#define FSM3_FSP2_CHIP5         0x3370
#define FSM3_FSP2_CHIP5_CPU1    0x3371
#define FSM3_FSP2_CHIP5_CPU2    0x3372
#define FSM3_FSP2_CHIP5_CPU3    0x3373
#define FSM3_FSP2_CHIP5_CPU4    0x3374
#define FSM3_FSP2_CHIP5_CPU5    0x3375
#define FSM3_FSP2_CHIP5_CPU6    0x3376
#define FSM3_FSP2_CHIP5_CPU7    0x3377
#define FSM3_FSP2_CHIP5_CPU8    0x3378

#define FSM3_FSP2_CHIP6         0x3380
#define FSM3_FSP2_CHIP6_CPU1    0x3381
#define FSM3_FSP2_CHIP6_CPU2    0x3382
#define FSM3_FSP2_CHIP6_CPU3    0x3383
#define FSM3_FSP2_CHIP6_CPU4    0x3384
#define FSM3_FSP2_CHIP6_CPU5    0x3385
#define FSM3_FSP2_CHIP6_CPU6    0x3386
#define FSM3_FSP2_CHIP6_CPU7    0x3387
#define FSM3_FSP2_CHIP6_CPU8    0x3388

#define FSM3_FSP2_CHIP7         0x3390
#define FSM3_FSP2_CHIP7_CPU1    0x3391
#define FSM3_FSP2_CHIP7_CPU2    0x3392
#define FSM3_FSP2_CHIP7_CPU3    0x3393
#define FSM3_FSP2_CHIP7_CPU4    0x3394
#define FSM3_FSP2_CHIP7_CPU5    0x3395
#define FSM3_FSP2_CHIP7_CPU6    0x3396
#define FSM3_FSP2_CHIP7_CPU7    0x3397
#define FSM3_FSP2_CHIP7_CPU8    0x3398

#define FSM3_FSP2_CHIP8         0x33A0
#define FSM3_FSP2_CHIP8_CPU1    0x33A1
#define FSM3_FSP2_CHIP8_CPU2    0x33A2
#define FSM3_FSP2_CHIP8_CPU3    0x33A3
#define FSM3_FSP2_CHIP8_CPU4    0x33A4
#define FSM3_FSP2_CHIP8_CPU5    0x33A5
#define FSM3_FSP2_CHIP8_CPU6    0x33A6
#define FSM3_FSP2_CHIP8_CPU7    0x33A7
#define FSM3_FSP2_CHIP8_CPU8    0x33A8

#define FSM3_FSP2_CHIP9         0x33B0
#define FSM3_FSP2_CHIP9_CPU1    0x33B1
#define FSM3_FSP2_CHIP9_CPU2    0x33B2
#define FSM3_FSP2_CHIP9_CPU3    0x33B3
#define FSM3_FSP2_CHIP9_CPU4    0x33B4
#define FSM3_FSP2_CHIP9_CPU5    0x33B5
#define FSM3_FSP2_CHIP9_CPU6    0x33B6
#define FSM3_FSP2_CHIP9_CPU7    0x33B7
#define FSM3_FSP2_CHIP9_CPU8    0x33B8

#define FSM3_FSP2_CHIPALL       0x33F0

/* FSM3_FSP3 */
#define FSM3_FSP3_MCU           0x340D
#define FSM3_FSP3_CHIP1         0x3430
#define FSM3_FSP3_CHIP1_CPU1    0x3431
#define FSM3_FSP3_CHIP1_CPU2    0x3432
#define FSM3_FSP3_CHIP1_CPU3    0x3433
#define FSM3_FSP3_CHIP1_CPU4    0x3434
#define FSM3_FSP3_CHIP1_CPU5    0x3435
#define FSM3_FSP3_CHIP1_CPU6    0x3436
#define FSM3_FSP3_CHIP1_CPU7    0x3437
#define FSM3_FSP3_CHIP1_CPU8    0x3438
#define FSM3_FSP3_CHIP1_SMP1    0x343D /* FSM-r4 */

#define FSM3_FSP3_CHIP2         0x3440
#define FSM3_FSP3_CHIP2_CPU1    0x3441
#define FSM3_FSP3_CHIP2_CPU2    0x3442
#define FSM3_FSP3_CHIP2_CPU3    0x3443
#define FSM3_FSP3_CHIP2_CPU4    0x3444
#define FSM3_FSP3_CHIP2_CPU5    0x3445
#define FSM3_FSP3_CHIP2_CPU6    0x3446
#define FSM3_FSP3_CHIP2_CPU7    0x3447
#define FSM3_FSP3_CHIP2_CPU8    0x3448
#define FSM3_FSP3_CHIP2_SMP1    0x344D /* FSM-r4 */

#define FSM3_FSP3_CHIP3         0x3450
#define FSM3_FSP3_CHIP3_CPU1    0x3451
#define FSM3_FSP3_CHIP3_CPU2    0x3452
#define FSM3_FSP3_CHIP3_CPU3    0x3453
#define FSM3_FSP3_CHIP3_CPU4    0x3454
#define FSM3_FSP3_CHIP3_CPU5    0x3455
#define FSM3_FSP3_CHIP3_CPU6    0x3456
#define FSM3_FSP3_CHIP3_CPU7    0x3457
#define FSM3_FSP3_CHIP3_CPU8    0x3458
#define FSM3_FSP3_CHIP3_SMP1    0x345D /* FSM-r4 */

#define FSM3_FSP3_CHIP4         0x3460
#define FSM3_FSP3_CHIP4_CPU1    0x3461
#define FSM3_FSP3_CHIP4_CPU2    0x3462
#define FSM3_FSP3_CHIP4_CPU3    0x3463
#define FSM3_FSP3_CHIP4_CPU4    0x3464
#define FSM3_FSP3_CHIP4_CPU5    0x3465
#define FSM3_FSP3_CHIP4_CPU6    0x3466
#define FSM3_FSP3_CHIP4_CPU7    0x3467
#define FSM3_FSP3_CHIP4_CPU8    0x3468
#define FSM3_FSP3_CHIP4_SMP1    0x346D /* FSM-r4 */

#define FSM3_FSP3_CHIP5         0x3470
#define FSM3_FSP3_CHIP5_CPU1    0x3471
#define FSM3_FSP3_CHIP5_CPU2    0x3472
#define FSM3_FSP3_CHIP5_CPU3    0x3473
#define FSM3_FSP3_CHIP5_CPU4    0x3474
#define FSM3_FSP3_CHIP5_CPU5    0x3475
#define FSM3_FSP3_CHIP5_CPU6    0x3476
#define FSM3_FSP3_CHIP5_CPU7    0x3477
#define FSM3_FSP3_CHIP5_CPU8    0x3478

#define FSM3_FSP3_CHIP6         0x3480
#define FSM3_FSP3_CHIP6_CPU1    0x3481
#define FSM3_FSP3_CHIP6_CPU2    0x3482
#define FSM3_FSP3_CHIP6_CPU3    0x3483
#define FSM3_FSP3_CHIP6_CPU4    0x3484
#define FSM3_FSP3_CHIP6_CPU5    0x3485
#define FSM3_FSP3_CHIP6_CPU6    0x3486
#define FSM3_FSP3_CHIP6_CPU7    0x3487
#define FSM3_FSP3_CHIP6_CPU8    0x3488

#define FSM3_FSP3_CHIP7         0x3490
#define FSM3_FSP3_CHIP7_CPU1    0x3491
#define FSM3_FSP3_CHIP7_CPU2    0x3492
#define FSM3_FSP3_CHIP7_CPU3    0x3493
#define FSM3_FSP3_CHIP7_CPU4    0x3494
#define FSM3_FSP3_CHIP7_CPU5    0x3495
#define FSM3_FSP3_CHIP7_CPU6    0x3496
#define FSM3_FSP3_CHIP7_CPU7    0x3497
#define FSM3_FSP3_CHIP7_CPU8    0x3498

#define FSM3_FSP3_CHIP8         0x34A0
#define FSM3_FSP3_CHIP8_CPU1    0x34A1
#define FSM3_FSP3_CHIP8_CPU2    0x34A2
#define FSM3_FSP3_CHIP8_CPU3    0x34A3
#define FSM3_FSP3_CHIP8_CPU4    0x34A4
#define FSM3_FSP3_CHIP8_CPU5    0x34A5
#define FSM3_FSP3_CHIP8_CPU6    0x34A6
#define FSM3_FSP3_CHIP8_CPU7    0x34A7
#define FSM3_FSP3_CHIP8_CPU8    0x34A8

#define FSM3_FSP3_CHIP9         0x34B0
#define FSM3_FSP3_CHIP9_CPU1    0x34B1
#define FSM3_FSP3_CHIP9_CPU2    0x34B2
#define FSM3_FSP3_CHIP9_CPU3    0x34B3
#define FSM3_FSP3_CHIP9_CPU4    0x34B4
#define FSM3_FSP3_CHIP9_CPU5    0x34B5
#define FSM3_FSP3_CHIP9_CPU6    0x34B6
#define FSM3_FSP3_CHIP9_CPU7    0x34B7
#define FSM3_FSP3_CHIP9_CPU8    0x34B8

#define FSM3_FSP3_CHIPALL       0x34F0

/* FSM4_FSP1 */
#define FSM4_FSP1_MCU           0x420D
#define FSM4_FSP1_CHIP1         0x4230
#define FSM4_FSP1_CHIP1_CPU1    0x4231
#define FSM4_FSP1_CHIP1_CPU2    0x4232
#define FSM4_FSP1_CHIP1_CPU3    0x4233
#define FSM4_FSP1_CHIP1_CPU4    0x4234
#define FSM4_FSP1_CHIP1_CPU5    0x4235
#define FSM4_FSP1_CHIP1_CPU6    0x4236
#define FSM4_FSP1_CHIP1_CPU7    0x4237
#define FSM4_FSP1_CHIP1_CPU8    0x4238
#define FSM4_FSP1_CHIP1_SMP1    0x423D /* FSM-r4 */

#define FSM4_FSP1_CHIP2         0x4240
#define FSM4_FSP1_CHIP2_CPU1    0x4241
#define FSM4_FSP1_CHIP2_CPU2    0x4242
#define FSM4_FSP1_CHIP2_CPU3    0x4243
#define FSM4_FSP1_CHIP2_CPU4    0x4244
#define FSM4_FSP1_CHIP2_CPU5    0x4245
#define FSM4_FSP1_CHIP2_CPU6    0x4246
#define FSM4_FSP1_CHIP2_CPU7    0x4247
#define FSM4_FSP1_CHIP2_CPU8    0x4248
#define FSM4_FSP1_CHIP2_SMP1    0x424D /* FSM-r4 */

#define FSM4_FSP1_CHIP3         0x4250
#define FSM4_FSP1_CHIP3_CPU1    0x4251
#define FSM4_FSP1_CHIP3_CPU2    0x4252
#define FSM4_FSP1_CHIP3_CPU3    0x4253
#define FSM4_FSP1_CHIP3_CPU4    0x4254
#define FSM4_FSP1_CHIP3_CPU5    0x4255
#define FSM4_FSP1_CHIP3_CPU6    0x4256
#define FSM4_FSP1_CHIP3_CPU7    0x4257
#define FSM4_FSP1_CHIP3_CPU8    0x4258
#define FSM4_FSP1_CHIP3_SMP1    0x425D /* FSM-r4 */

#define FSM4_FSP1_CHIP4         0x4260
#define FSM4_FSP1_CHIP4_CPU1    0x4261
#define FSM4_FSP1_CHIP4_CPU2    0x4262
#define FSM4_FSP1_CHIP4_CPU3    0x4263
#define FSM4_FSP1_CHIP4_CPU4    0x4264
#define FSM4_FSP1_CHIP4_CPU5    0x4265
#define FSM4_FSP1_CHIP4_CPU6    0x4266
#define FSM4_FSP1_CHIP4_CPU7    0x4267
#define FSM4_FSP1_CHIP4_CPU8    0x4268
#define FSM4_FSP1_CHIP4_SMP1    0x426D /* FSM-r4 */

#define FSM4_FSP1_CHIP5         0x4270
#define FSM4_FSP1_CHIP5_CPU1    0x4271
#define FSM4_FSP1_CHIP5_CPU2    0x4272
#define FSM4_FSP1_CHIP5_CPU3    0x4273
#define FSM4_FSP1_CHIP5_CPU4    0x4274
#define FSM4_FSP1_CHIP5_CPU5    0x4275
#define FSM4_FSP1_CHIP5_CPU6    0x4276
#define FSM4_FSP1_CHIP5_CPU7    0x4277
#define FSM4_FSP1_CHIP5_CPU8    0x4278

#define FSM4_FSP1_CHIP6         0x4280
#define FSM4_FSP1_CHIP6_CPU1    0x4281
#define FSM4_FSP1_CHIP6_CPU2    0x4282
#define FSM4_FSP1_CHIP6_CPU3    0x4283
#define FSM4_FSP1_CHIP6_CPU4    0x4284
#define FSM4_FSP1_CHIP6_CPU5    0x4285
#define FSM4_FSP1_CHIP6_CPU6    0x4286
#define FSM4_FSP1_CHIP6_CPU7    0x4287
#define FSM4_FSP1_CHIP6_CPU8    0x4288

#define FSM4_FSP1_CHIP7         0x4290
#define FSM4_FSP1_CHIP7_CPU1    0x4291
#define FSM4_FSP1_CHIP7_CPU2    0x4292
#define FSM4_FSP1_CHIP7_CPU3    0x4293
#define FSM4_FSP1_CHIP7_CPU4    0x4294
#define FSM4_FSP1_CHIP7_CPU5    0x4295
#define FSM4_FSP1_CHIP7_CPU6    0x4296
#define FSM4_FSP1_CHIP7_CPU7    0x4297
#define FSM4_FSP1_CHIP7_CPU8    0x4298

#define FSM4_FSP1_CHIP8         0x42A0
#define FSM4_FSP1_CHIP8_CPU1    0x42A1
#define FSM4_FSP1_CHIP8_CPU2    0x42A2
#define FSM4_FSP1_CHIP8_CPU3    0x42A3
#define FSM4_FSP1_CHIP8_CPU4    0x42A4
#define FSM4_FSP1_CHIP8_CPU5    0x42A5
#define FSM4_FSP1_CHIP8_CPU6    0x42A6
#define FSM4_FSP1_CHIP8_CPU7    0x42A7
#define FSM4_FSP1_CHIP8_CPU8    0x42A8

#define FSM4_FSP1_CHIP9         0x42B0
#define FSM4_FSP1_CHIP9_CPU1    0x42B1
#define FSM4_FSP1_CHIP9_CPU2    0x42B2
#define FSM4_FSP1_CHIP9_CPU3    0x42B3
#define FSM4_FSP1_CHIP9_CPU4    0x42B4
#define FSM4_FSP1_CHIP9_CPU5    0x42B5
#define FSM4_FSP1_CHIP9_CPU6    0x42B6
#define FSM4_FSP1_CHIP9_CPU7    0x42B7
#define FSM4_FSP1_CHIP9_CPU8    0x42B8

#define FSM4_FSP1_CHIPALL       0x42F0

/* FSM4_FSP2 */
#define FSM4_FSP2_MCU           0x430D
#define FSM4_FSP2_CHIP1         0x4330
#define FSM4_FSP2_CHIP1_CPU1    0x4331
#define FSM4_FSP2_CHIP1_CPU2    0x4332
#define FSM4_FSP2_CHIP1_CPU3    0x4333
#define FSM4_FSP2_CHIP1_CPU4    0x4334
#define FSM4_FSP2_CHIP1_CPU5    0x4335
#define FSM4_FSP2_CHIP1_CPU6    0x4336
#define FSM4_FSP2_CHIP1_CPU7    0x4337
#define FSM4_FSP2_CHIP1_CPU8    0x4338
#define FSM4_FSP2_CHIP1_SMP1    0x433D /* FSM-r4 */

#define FSM4_FSP2_CHIP2         0x4340
#define FSM4_FSP2_CHIP2_CPU1    0x4341
#define FSM4_FSP2_CHIP2_CPU2    0x4342
#define FSM4_FSP2_CHIP2_CPU3    0x4343
#define FSM4_FSP2_CHIP2_CPU4    0x4344
#define FSM4_FSP2_CHIP2_CPU5    0x4345
#define FSM4_FSP2_CHIP2_CPU6    0x4346
#define FSM4_FSP2_CHIP2_CPU7    0x4347
#define FSM4_FSP2_CHIP2_CPU8    0x4348
#define FSM4_FSP2_CHIP2_SMP1    0x434D /* FSM-r4 */

#define FSM4_FSP2_CHIP3         0x4350
#define FSM4_FSP2_CHIP3_CPU1    0x4351
#define FSM4_FSP2_CHIP3_CPU2    0x4352
#define FSM4_FSP2_CHIP3_CPU3    0x4353
#define FSM4_FSP2_CHIP3_CPU4    0x4354
#define FSM4_FSP2_CHIP3_CPU5    0x4355
#define FSM4_FSP2_CHIP3_CPU6    0x4356
#define FSM4_FSP2_CHIP3_CPU7    0x4357
#define FSM4_FSP2_CHIP3_CPU8    0x4358
#define FSM4_FSP2_CHIP3_SMP1    0x435D /* FSM-r4 */

#define FSM4_FSP2_CHIP4         0x4360
#define FSM4_FSP2_CHIP4_CPU1    0x4361
#define FSM4_FSP2_CHIP4_CPU2    0x4362
#define FSM4_FSP2_CHIP4_CPU3    0x4363
#define FSM4_FSP2_CHIP4_CPU4    0x4364
#define FSM4_FSP2_CHIP4_CPU5    0x4365
#define FSM4_FSP2_CHIP4_CPU6    0x4366
#define FSM4_FSP2_CHIP4_CPU7    0x4367
#define FSM4_FSP2_CHIP4_CPU8    0x4368
#define FSM4_FSP2_CHIP4_SMP1    0x436D /* FSM-r4 */

#define FSM4_FSP2_CHIP5         0x4370
#define FSM4_FSP2_CHIP5_CPU1    0x4371
#define FSM4_FSP2_CHIP5_CPU2    0x4372
#define FSM4_FSP2_CHIP5_CPU3    0x4373
#define FSM4_FSP2_CHIP5_CPU4    0x4374
#define FSM4_FSP2_CHIP5_CPU5    0x4375
#define FSM4_FSP2_CHIP5_CPU6    0x4376
#define FSM4_FSP2_CHIP5_CPU7    0x4377
#define FSM4_FSP2_CHIP5_CPU8    0x4378

#define FSM4_FSP2_CHIP6         0x4380
#define FSM4_FSP2_CHIP6_CPU1    0x4381
#define FSM4_FSP2_CHIP6_CPU2    0x4382
#define FSM4_FSP2_CHIP6_CPU3    0x4383
#define FSM4_FSP2_CHIP6_CPU4    0x4384
#define FSM4_FSP2_CHIP6_CPU5    0x4385
#define FSM4_FSP2_CHIP6_CPU6    0x4386
#define FSM4_FSP2_CHIP6_CPU7    0x4387
#define FSM4_FSP2_CHIP6_CPU8    0x4388

#define FSM4_FSP2_CHIP7         0x4390
#define FSM4_FSP2_CHIP7_CPU1    0x4391
#define FSM4_FSP2_CHIP7_CPU2    0x4392
#define FSM4_FSP2_CHIP7_CPU3    0x4393
#define FSM4_FSP2_CHIP7_CPU4    0x4394
#define FSM4_FSP2_CHIP7_CPU5    0x4395
#define FSM4_FSP2_CHIP7_CPU6    0x4396
#define FSM4_FSP2_CHIP7_CPU7    0x4397
#define FSM4_FSP2_CHIP7_CPU8    0x4398

#define FSM4_FSP2_CHIP8         0x43A0
#define FSM4_FSP2_CHIP8_CPU1    0x43A1
#define FSM4_FSP2_CHIP8_CPU2    0x43A2
#define FSM4_FSP2_CHIP8_CPU3    0x43A3
#define FSM4_FSP2_CHIP8_CPU4    0x43A4
#define FSM4_FSP2_CHIP8_CPU5    0x43A5
#define FSM4_FSP2_CHIP8_CPU6    0x43A6
#define FSM4_FSP2_CHIP8_CPU7    0x43A7
#define FSM4_FSP2_CHIP8_CPU8    0x43A8

#define FSM4_FSP2_CHIP9         0x43B0
#define FSM4_FSP2_CHIP9_CPU1    0x43B1
#define FSM4_FSP2_CHIP9_CPU2    0x43B2
#define FSM4_FSP2_CHIP9_CPU3    0x43B3
#define FSM4_FSP2_CHIP9_CPU4    0x43B4
#define FSM4_FSP2_CHIP9_CPU5    0x43B5
#define FSM4_FSP2_CHIP9_CPU6    0x43B6
#define FSM4_FSP2_CHIP9_CPU7    0x43B7
#define FSM4_FSP2_CHIP9_CPU8    0x43B8

#define FSM4_FSP2_CHIPALL       0x43F0

/* FSM4_FSP3 */
#define FSM4_FSP3_MCU           0x440D
#define FSM4_FSP3_CHIP1         0x4430
#define FSM4_FSP3_CHIP1_CPU1    0x4431
#define FSM4_FSP3_CHIP1_CPU2    0x4432
#define FSM4_FSP3_CHIP1_CPU3    0x4433
#define FSM4_FSP3_CHIP1_CPU4    0x4434
#define FSM4_FSP3_CHIP1_CPU5    0x4435
#define FSM4_FSP3_CHIP1_CPU6    0x4436
#define FSM4_FSP3_CHIP1_CPU7    0x4437
#define FSM4_FSP3_CHIP1_CPU8    0x4438
#define FSM4_FSP3_CHIP1_SMP1    0x443D /* FSM-r4 */

#define FSM4_FSP3_CHIP2         0x4440
#define FSM4_FSP3_CHIP2_CPU1    0x4441
#define FSM4_FSP3_CHIP2_CPU2    0x4442
#define FSM4_FSP3_CHIP2_CPU3    0x4443
#define FSM4_FSP3_CHIP2_CPU4    0x4444
#define FSM4_FSP3_CHIP2_CPU5    0x4445
#define FSM4_FSP3_CHIP2_CPU6    0x4446
#define FSM4_FSP3_CHIP2_CPU7    0x4447
#define FSM4_FSP3_CHIP2_CPU8    0x4448
#define FSM4_FSP3_CHIP2_SMP1    0x444D /* FSM-r4 */

#define FSM4_FSP3_CHIP3         0x4450
#define FSM4_FSP3_CHIP3_CPU1    0x4451
#define FSM4_FSP3_CHIP3_CPU2    0x4452
#define FSM4_FSP3_CHIP3_CPU3    0x4453
#define FSM4_FSP3_CHIP3_CPU4    0x4454
#define FSM4_FSP3_CHIP3_CPU5    0x4455
#define FSM4_FSP3_CHIP3_CPU6    0x4456
#define FSM4_FSP3_CHIP3_CPU7    0x4457
#define FSM4_FSP3_CHIP3_CPU8    0x4458
#define FSM4_FSP3_CHIP3_SMP1    0x445D /* FSM-r4 */

#define FSM4_FSP3_CHIP4         0x4460
#define FSM4_FSP3_CHIP4_CPU1    0x4461
#define FSM4_FSP3_CHIP4_CPU2    0x4462
#define FSM4_FSP3_CHIP4_CPU3    0x4463
#define FSM4_FSP3_CHIP4_CPU4    0x4464
#define FSM4_FSP3_CHIP4_CPU5    0x4465
#define FSM4_FSP3_CHIP4_CPU6    0x4466
#define FSM4_FSP3_CHIP4_CPU7    0x4467
#define FSM4_FSP3_CHIP4_CPU8    0x4468
#define FSM4_FSP3_CHIP4_SMP1    0x446D /* FSM-r4 */

#define FSM4_FSP3_CHIP5         0x4470
#define FSM4_FSP3_CHIP5_CPU1    0x4471
#define FSM4_FSP3_CHIP5_CPU2    0x4472
#define FSM4_FSP3_CHIP5_CPU3    0x4473
#define FSM4_FSP3_CHIP5_CPU4    0x4474
#define FSM4_FSP3_CHIP5_CPU5    0x4475
#define FSM4_FSP3_CHIP5_CPU6    0x4476
#define FSM4_FSP3_CHIP5_CPU7    0x4477
#define FSM4_FSP3_CHIP5_CPU8    0x4478

#define FSM4_FSP3_CHIP6         0x4480
#define FSM4_FSP3_CHIP6_CPU1    0x4481
#define FSM4_FSP3_CHIP6_CPU2    0x4482
#define FSM4_FSP3_CHIP6_CPU3    0x4483
#define FSM4_FSP3_CHIP6_CPU4    0x4484
#define FSM4_FSP3_CHIP6_CPU5    0x4485
#define FSM4_FSP3_CHIP6_CPU6    0x4486
#define FSM4_FSP3_CHIP6_CPU7    0x4487
#define FSM4_FSP3_CHIP6_CPU8    0x4488

#define FSM4_FSP3_CHIP7         0x4490
#define FSM4_FSP3_CHIP7_CPU1    0x4491
#define FSM4_FSP3_CHIP7_CPU2    0x4492
#define FSM4_FSP3_CHIP7_CPU3    0x4493
#define FSM4_FSP3_CHIP7_CPU4    0x4494
#define FSM4_FSP3_CHIP7_CPU5    0x4495
#define FSM4_FSP3_CHIP7_CPU6    0x4496
#define FSM4_FSP3_CHIP7_CPU7    0x4497
#define FSM4_FSP3_CHIP7_CPU8    0x4498

#define FSM4_FSP3_CHIP8         0x44A0
#define FSM4_FSP3_CHIP8_CPU1    0x44A1
#define FSM4_FSP3_CHIP8_CPU2    0x44A2
#define FSM4_FSP3_CHIP8_CPU3    0x44A3
#define FSM4_FSP3_CHIP8_CPU4    0x44A4
#define FSM4_FSP3_CHIP8_CPU5    0x44A5
#define FSM4_FSP3_CHIP8_CPU6    0x44A6
#define FSM4_FSP3_CHIP8_CPU7    0x44A7
#define FSM4_FSP3_CHIP8_CPU8    0x44A8

#define FSM4_FSP3_CHIP9         0x44B0
#define FSM4_FSP3_CHIP9_CPU1    0x44B1
#define FSM4_FSP3_CHIP9_CPU2    0x44B2
#define FSM4_FSP3_CHIP9_CPU3    0x44B3
#define FSM4_FSP3_CHIP9_CPU4    0x44B4
#define FSM4_FSP3_CHIP9_CPU5    0x44B5
#define FSM4_FSP3_CHIP9_CPU6    0x44B6
#define FSM4_FSP3_CHIP9_CPU7    0x44B7
#define FSM4_FSP3_CHIP9_CPU8    0x44B8

#define FSM4_FSP3_CHIPALL       0x44F0


/* FSM5_FSP1 */
#define FSM5_FSP1_MCU           0x520D
#define FSM5_FSP1_CHIP1         0x5230
#define FSM5_FSP1_CHIP1_CPU1    0x5231
#define FSM5_FSP1_CHIP1_CPU2    0x5232
#define FSM5_FSP1_CHIP1_CPU3    0x5233
#define FSM5_FSP1_CHIP1_CPU4    0x5234
#define FSM5_FSP1_CHIP1_CPU5    0x5235
#define FSM5_FSP1_CHIP1_CPU6    0x5236
#define FSM5_FSP1_CHIP1_CPU7    0x5237
#define FSM5_FSP1_CHIP1_CPU8    0x5238
#define FSM5_FSP1_CHIP1_SMP1    0x523D /* FSM-r4 */

#define FSM5_FSP1_CHIP2         0x5240
#define FSM5_FSP1_CHIP2_CPU1    0x5241
#define FSM5_FSP1_CHIP2_CPU2    0x5242
#define FSM5_FSP1_CHIP2_CPU3    0x5243
#define FSM5_FSP1_CHIP2_CPU4    0x5244
#define FSM5_FSP1_CHIP2_CPU5    0x5245
#define FSM5_FSP1_CHIP2_CPU6    0x5246
#define FSM5_FSP1_CHIP2_CPU7    0x5247
#define FSM5_FSP1_CHIP2_CPU8    0x5248
#define FSM5_FSP1_CHIP2_SMP1    0x524D /* FSM-r4 */

#define FSM5_FSP1_CHIP3         0x5250
#define FSM5_FSP1_CHIP3_CPU1    0x5251
#define FSM5_FSP1_CHIP3_CPU2    0x5252
#define FSM5_FSP1_CHIP3_CPU3    0x5253
#define FSM5_FSP1_CHIP3_CPU4    0x5254
#define FSM5_FSP1_CHIP3_CPU5    0x5255
#define FSM5_FSP1_CHIP3_CPU6    0x5256
#define FSM5_FSP1_CHIP3_CPU7    0x5257
#define FSM5_FSP1_CHIP3_CPU8    0x5258
#define FSM5_FSP1_CHIP3_SMP1    0x525D /* FSM-r4 */

#define FSM5_FSP1_CHIP4         0x5260
#define FSM5_FSP1_CHIP4_CPU1    0x5261
#define FSM5_FSP1_CHIP4_CPU2    0x5262
#define FSM5_FSP1_CHIP4_CPU3    0x5263
#define FSM5_FSP1_CHIP4_CPU4    0x5264
#define FSM5_FSP1_CHIP4_CPU5    0x5265
#define FSM5_FSP1_CHIP4_CPU6    0x5266
#define FSM5_FSP1_CHIP4_CPU7    0x5267
#define FSM5_FSP1_CHIP4_CPU8    0x5268
#define FSM5_FSP1_CHIP4_SMP1    0x526D /* FSM-r4 */

#define FSM5_FSP1_CHIP5         0x5270
#define FSM5_FSP1_CHIP5_CPU1    0x5271
#define FSM5_FSP1_CHIP5_CPU2    0x5272
#define FSM5_FSP1_CHIP5_CPU3    0x5273
#define FSM5_FSP1_CHIP5_CPU4    0x5274
#define FSM5_FSP1_CHIP5_CPU5    0x5275
#define FSM5_FSP1_CHIP5_CPU6    0x5276
#define FSM5_FSP1_CHIP5_CPU7    0x5277
#define FSM5_FSP1_CHIP5_CPU8    0x5278

#define FSM5_FSP1_CHIP6         0x5280
#define FSM5_FSP1_CHIP6_CPU1    0x5281
#define FSM5_FSP1_CHIP6_CPU2    0x5282
#define FSM5_FSP1_CHIP6_CPU3    0x5283
#define FSM5_FSP1_CHIP6_CPU4    0x5284
#define FSM5_FSP1_CHIP6_CPU5    0x5285
#define FSM5_FSP1_CHIP6_CPU6    0x5286
#define FSM5_FSP1_CHIP6_CPU7    0x5287
#define FSM5_FSP1_CHIP6_CPU8    0x5288

#define FSM5_FSP1_CHIP7         0x5290
#define FSM5_FSP1_CHIP7_CPU1    0x5291
#define FSM5_FSP1_CHIP7_CPU2    0x5292
#define FSM5_FSP1_CHIP7_CPU3    0x5293
#define FSM5_FSP1_CHIP7_CPU4    0x5294
#define FSM5_FSP1_CHIP7_CPU5    0x5295
#define FSM5_FSP1_CHIP7_CPU6    0x5296
#define FSM5_FSP1_CHIP7_CPU7    0x5297
#define FSM5_FSP1_CHIP7_CPU8    0x5298

#define FSM5_FSP1_CHIP8         0x52A0
#define FSM5_FSP1_CHIP8_CPU1    0x52A1
#define FSM5_FSP1_CHIP8_CPU2    0x52A2
#define FSM5_FSP1_CHIP8_CPU3    0x52A3
#define FSM5_FSP1_CHIP8_CPU4    0x52A4
#define FSM5_FSP1_CHIP8_CPU5    0x52A5
#define FSM5_FSP1_CHIP8_CPU6    0x52A6
#define FSM5_FSP1_CHIP8_CPU7    0x52A7
#define FSM5_FSP1_CHIP8_CPU8    0x52A8

#define FSM5_FSP1_CHIP9         0x52B0
#define FSM5_FSP1_CHIP9_CPU1    0x52B1
#define FSM5_FSP1_CHIP9_CPU2    0x52B2
#define FSM5_FSP1_CHIP9_CPU3    0x52B3
#define FSM5_FSP1_CHIP9_CPU4    0x52B4
#define FSM5_FSP1_CHIP9_CPU5    0x52B5
#define FSM5_FSP1_CHIP9_CPU6    0x52B6
#define FSM5_FSP1_CHIP9_CPU7    0x52B7
#define FSM5_FSP1_CHIP9_CPU8    0x52B8

#define FSM5_FSP1_CHIPALL       0x52F0

/* FSM5_FSP2 */
#define FSM5_FSP2_MCU           0x530D
#define FSM5_FSP2_CHIP1         0x5330
#define FSM5_FSP2_CHIP1_CPU1    0x5331
#define FSM5_FSP2_CHIP1_CPU2    0x5332
#define FSM5_FSP2_CHIP1_CPU3    0x5333
#define FSM5_FSP2_CHIP1_CPU4    0x5334
#define FSM5_FSP2_CHIP1_CPU5    0x5335
#define FSM5_FSP2_CHIP1_CPU6    0x5336
#define FSM5_FSP2_CHIP1_CPU7    0x5337
#define FSM5_FSP2_CHIP1_CPU8    0x5338
#define FSM5_FSP2_CHIP1_SMP1    0x533D /* FSM-r4 */

#define FSM5_FSP2_CHIP2         0x5340
#define FSM5_FSP2_CHIP2_CPU1    0x5341
#define FSM5_FSP2_CHIP2_CPU2    0x5342
#define FSM5_FSP2_CHIP2_CPU3    0x5343
#define FSM5_FSP2_CHIP2_CPU4    0x5344
#define FSM5_FSP2_CHIP2_CPU5    0x5345
#define FSM5_FSP2_CHIP2_CPU6    0x5346
#define FSM5_FSP2_CHIP2_CPU7    0x5347
#define FSM5_FSP2_CHIP2_CPU8    0x5348
#define FSM5_FSP2_CHIP2_SMP1    0x534D /* FSM-r4 */

#define FSM5_FSP2_CHIP3         0x5350
#define FSM5_FSP2_CHIP3_CPU1    0x5351
#define FSM5_FSP2_CHIP3_CPU2    0x5352
#define FSM5_FSP2_CHIP3_CPU3    0x5353
#define FSM5_FSP2_CHIP3_CPU4    0x5354
#define FSM5_FSP2_CHIP3_CPU5    0x5355
#define FSM5_FSP2_CHIP3_CPU6    0x5356
#define FSM5_FSP2_CHIP3_CPU7    0x5357
#define FSM5_FSP2_CHIP3_CPU8    0x5358
#define FSM5_FSP2_CHIP3_SMP1    0x535D /* FSM-r4 */

#define FSM5_FSP2_CHIP4         0x5360
#define FSM5_FSP2_CHIP4_CPU1    0x5361
#define FSM5_FSP2_CHIP4_CPU2    0x5362
#define FSM5_FSP2_CHIP4_CPU3    0x5363
#define FSM5_FSP2_CHIP4_CPU4    0x5364
#define FSM5_FSP2_CHIP4_CPU5    0x5365
#define FSM5_FSP2_CHIP4_CPU6    0x5366
#define FSM5_FSP2_CHIP4_CPU7    0x5367
#define FSM5_FSP2_CHIP4_CPU8    0x5368
#define FSM5_FSP2_CHIP4_SMP1    0x536D /* FSM-r4 */

#define FSM5_FSP2_CHIP5         0x5370
#define FSM5_FSP2_CHIP5_CPU1    0x5371
#define FSM5_FSP2_CHIP5_CPU2    0x5372
#define FSM5_FSP2_CHIP5_CPU3    0x5373
#define FSM5_FSP2_CHIP5_CPU4    0x5374
#define FSM5_FSP2_CHIP5_CPU5    0x5375
#define FSM5_FSP2_CHIP5_CPU6    0x5376
#define FSM5_FSP2_CHIP5_CPU7    0x5377
#define FSM5_FSP2_CHIP5_CPU8    0x5378

#define FSM5_FSP2_CHIP6         0x5380
#define FSM5_FSP2_CHIP6_CPU1    0x5381
#define FSM5_FSP2_CHIP6_CPU2    0x5382
#define FSM5_FSP2_CHIP6_CPU3    0x5383
#define FSM5_FSP2_CHIP6_CPU4    0x5384
#define FSM5_FSP2_CHIP6_CPU5    0x5385
#define FSM5_FSP2_CHIP6_CPU6    0x5386
#define FSM5_FSP2_CHIP6_CPU7    0x5387
#define FSM5_FSP2_CHIP6_CPU8    0x5388

#define FSM5_FSP2_CHIP7         0x5390
#define FSM5_FSP2_CHIP7_CPU1    0x5391
#define FSM5_FSP2_CHIP7_CPU2    0x5392
#define FSM5_FSP2_CHIP7_CPU3    0x5393
#define FSM5_FSP2_CHIP7_CPU4    0x5394
#define FSM5_FSP2_CHIP7_CPU5    0x5395
#define FSM5_FSP2_CHIP7_CPU6    0x5396
#define FSM5_FSP2_CHIP7_CPU7    0x5397
#define FSM5_FSP2_CHIP7_CPU8    0x5398

#define FSM5_FSP2_CHIP8         0x53A0
#define FSM5_FSP2_CHIP8_CPU1    0x53A1
#define FSM5_FSP2_CHIP8_CPU2    0x53A2
#define FSM5_FSP2_CHIP8_CPU3    0x53A3
#define FSM5_FSP2_CHIP8_CPU4    0x53A4
#define FSM5_FSP2_CHIP8_CPU5    0x53A5
#define FSM5_FSP2_CHIP8_CPU6    0x53A6
#define FSM5_FSP2_CHIP8_CPU7    0x53A7
#define FSM5_FSP2_CHIP8_CPU8    0x53A8

#define FSM5_FSP2_CHIP9         0x53B0
#define FSM5_FSP2_CHIP9_CPU1    0x53B1
#define FSM5_FSP2_CHIP9_CPU2    0x53B2
#define FSM5_FSP2_CHIP9_CPU3    0x53B3
#define FSM5_FSP2_CHIP9_CPU4    0x53B4
#define FSM5_FSP2_CHIP9_CPU5    0x53B5
#define FSM5_FSP2_CHIP9_CPU6    0x53B6
#define FSM5_FSP2_CHIP9_CPU7    0x53B7
#define FSM5_FSP2_CHIP9_CPU8    0x53B8

#define FSM5_FSP2_CHIPALL       0x53F0

/* FSM5_FSP3 */
#define FSM5_FSP3_MCU           0x540D
#define FSM5_FSP3_CHIP1         0x5430
#define FSM5_FSP3_CHIP1_CPU1    0x5431
#define FSM5_FSP3_CHIP1_CPU2    0x5432
#define FSM5_FSP3_CHIP1_CPU3    0x5433
#define FSM5_FSP3_CHIP1_CPU4    0x5434
#define FSM5_FSP3_CHIP1_CPU5    0x5435
#define FSM5_FSP3_CHIP1_CPU6    0x5436
#define FSM5_FSP3_CHIP1_CPU7    0x5437
#define FSM5_FSP3_CHIP1_CPU8    0x5438
#define FSM5_FSP3_CHIP1_SMP1    0x543D /* FSM-r4 */

#define FSM5_FSP3_CHIP2         0x5440
#define FSM5_FSP3_CHIP2_CPU1    0x5441
#define FSM5_FSP3_CHIP2_CPU2    0x5442
#define FSM5_FSP3_CHIP2_CPU3    0x5443
#define FSM5_FSP3_CHIP2_CPU4    0x5444
#define FSM5_FSP3_CHIP2_CPU5    0x5445
#define FSM5_FSP3_CHIP2_CPU6    0x5446
#define FSM5_FSP3_CHIP2_CPU7    0x5447
#define FSM5_FSP3_CHIP2_CPU8    0x5448
#define FSM5_FSP3_CHIP2_SMP1    0x544D /* FSM-r4 */

#define FSM5_FSP3_CHIP3         0x5450
#define FSM5_FSP3_CHIP3_CPU1    0x5451
#define FSM5_FSP3_CHIP3_CPU2    0x5452
#define FSM5_FSP3_CHIP3_CPU3    0x5453
#define FSM5_FSP3_CHIP3_CPU4    0x5454
#define FSM5_FSP3_CHIP3_CPU5    0x5455
#define FSM5_FSP3_CHIP3_CPU6    0x5456
#define FSM5_FSP3_CHIP3_CPU7    0x5457
#define FSM5_FSP3_CHIP3_CPU8    0x5458
#define FSM5_FSP3_CHIP3_SMP1    0x545D /* FSM-r4 */

#define FSM5_FSP3_CHIP4         0x5460
#define FSM5_FSP3_CHIP4_CPU1    0x5461
#define FSM5_FSP3_CHIP4_CPU2    0x5462
#define FSM5_FSP3_CHIP4_CPU3    0x5463
#define FSM5_FSP3_CHIP4_CPU4    0x5464
#define FSM5_FSP3_CHIP4_CPU5    0x5465
#define FSM5_FSP3_CHIP4_CPU6    0x5466
#define FSM5_FSP3_CHIP4_CPU7    0x5467
#define FSM5_FSP3_CHIP4_CPU8    0x5468
#define FSM5_FSP3_CHIP4_SMP1    0x546D /* FSM-r4 */

#define FSM5_FSP3_CHIP5         0x5470
#define FSM5_FSP3_CHIP5_CPU1    0x5471
#define FSM5_FSP3_CHIP5_CPU2    0x5472
#define FSM5_FSP3_CHIP5_CPU3    0x5473
#define FSM5_FSP3_CHIP5_CPU4    0x5474
#define FSM5_FSP3_CHIP5_CPU5    0x5475
#define FSM5_FSP3_CHIP5_CPU6    0x5476
#define FSM5_FSP3_CHIP5_CPU7    0x5477
#define FSM5_FSP3_CHIP5_CPU8    0x5478

#define FSM5_FSP3_CHIP6         0x5480
#define FSM5_FSP3_CHIP6_CPU1    0x5481
#define FSM5_FSP3_CHIP6_CPU2    0x5482
#define FSM5_FSP3_CHIP6_CPU3    0x5483
#define FSM5_FSP3_CHIP6_CPU4    0x5484
#define FSM5_FSP3_CHIP6_CPU5    0x5485
#define FSM5_FSP3_CHIP6_CPU6    0x5486
#define FSM5_FSP3_CHIP6_CPU7    0x5487
#define FSM5_FSP3_CHIP6_CPU8    0x5488

#define FSM5_FSP3_CHIP7         0x5490
#define FSM5_FSP3_CHIP7_CPU1    0x5491
#define FSM5_FSP3_CHIP7_CPU2    0x5492
#define FSM5_FSP3_CHIP7_CPU3    0x5493
#define FSM5_FSP3_CHIP7_CPU4    0x5494
#define FSM5_FSP3_CHIP7_CPU5    0x5495
#define FSM5_FSP3_CHIP7_CPU6    0x5496
#define FSM5_FSP3_CHIP7_CPU7    0x5497
#define FSM5_FSP3_CHIP7_CPU8    0x5498

#define FSM5_FSP3_CHIP8         0x54A0
#define FSM5_FSP3_CHIP8_CPU1    0x54A1
#define FSM5_FSP3_CHIP8_CPU2    0x54A2
#define FSM5_FSP3_CHIP8_CPU3    0x54A3
#define FSM5_FSP3_CHIP8_CPU4    0x54A4
#define FSM5_FSP3_CHIP8_CPU5    0x54A5
#define FSM5_FSP3_CHIP8_CPU6    0x54A6
#define FSM5_FSP3_CHIP8_CPU7    0x54A7
#define FSM5_FSP3_CHIP8_CPU8    0x54A8

#define FSM5_FSP3_CHIP9         0x54B0
#define FSM5_FSP3_CHIP9_CPU1    0x54B1
#define FSM5_FSP3_CHIP9_CPU2    0x54B2
#define FSM5_FSP3_CHIP9_CPU3    0x54B3
#define FSM5_FSP3_CHIP9_CPU4    0x54B4
#define FSM5_FSP3_CHIP9_CPU5    0x54B5
#define FSM5_FSP3_CHIP9_CPU6    0x54B6
#define FSM5_FSP3_CHIP9_CPU7    0x54B7
#define FSM5_FSP3_CHIP9_CPU8    0x54B8

#define FSM5_FSP3_CHIPALL       0x54F0


/* FSM6_FSP1 */
#define FSM6_FSP1_MCU           0x620D
#define FSM6_FSP1_CHIP1         0x6230
#define FSM6_FSP1_CHIP1_CPU1    0x6231
#define FSM6_FSP1_CHIP1_CPU2    0x6232
#define FSM6_FSP1_CHIP1_CPU3    0x6233
#define FSM6_FSP1_CHIP1_CPU4    0x6234
#define FSM6_FSP1_CHIP1_CPU5    0x6235
#define FSM6_FSP1_CHIP1_CPU6    0x6236
#define FSM6_FSP1_CHIP1_CPU7    0x6237
#define FSM6_FSP1_CHIP1_CPU8    0x6238
#define FSM6_FSP1_CHIP1_SMP1    0x623D /* FSM-r4 */

#define FSM6_FSP1_CHIP2         0x6240
#define FSM6_FSP1_CHIP2_CPU1    0x6241
#define FSM6_FSP1_CHIP2_CPU2    0x6242
#define FSM6_FSP1_CHIP2_CPU3    0x6243
#define FSM6_FSP1_CHIP2_CPU4    0x6244
#define FSM6_FSP1_CHIP2_CPU5    0x6245
#define FSM6_FSP1_CHIP2_CPU6    0x6246
#define FSM6_FSP1_CHIP2_CPU7    0x6247
#define FSM6_FSP1_CHIP2_CPU8    0x6248
#define FSM6_FSP1_CHIP2_SMP1    0x624D /* FSM-r4 */

#define FSM6_FSP1_CHIP3         0x6250
#define FSM6_FSP1_CHIP3_CPU1    0x6251
#define FSM6_FSP1_CHIP3_CPU2    0x6252
#define FSM6_FSP1_CHIP3_CPU3    0x6253
#define FSM6_FSP1_CHIP3_CPU4    0x6254
#define FSM6_FSP1_CHIP3_CPU5    0x6255
#define FSM6_FSP1_CHIP3_CPU6    0x6256
#define FSM6_FSP1_CHIP3_CPU7    0x6257
#define FSM6_FSP1_CHIP3_CPU8    0x6258
#define FSM6_FSP1_CHIP3_SMP1    0x625D /* FSM-r4 */

#define FSM6_FSP1_CHIP4         0x6260
#define FSM6_FSP1_CHIP4_CPU1    0x6261
#define FSM6_FSP1_CHIP4_CPU2    0x6262
#define FSM6_FSP1_CHIP4_CPU3    0x6263
#define FSM6_FSP1_CHIP4_CPU4    0x6264
#define FSM6_FSP1_CHIP4_CPU5    0x6265
#define FSM6_FSP1_CHIP4_CPU6    0x6266
#define FSM6_FSP1_CHIP4_CPU7    0x6267
#define FSM6_FSP1_CHIP4_CPU8    0x6268
#define FSM6_FSP1_CHIP4_SMP1    0x626D /* FSM-r4 */

#define FSM6_FSP1_CHIP5         0x6270
#define FSM6_FSP1_CHIP5_CPU1    0x6271
#define FSM6_FSP1_CHIP5_CPU2    0x6272
#define FSM6_FSP1_CHIP5_CPU3    0x6273
#define FSM6_FSP1_CHIP5_CPU4    0x6274
#define FSM6_FSP1_CHIP5_CPU5    0x6275
#define FSM6_FSP1_CHIP5_CPU6    0x6276
#define FSM6_FSP1_CHIP5_CPU7    0x6277
#define FSM6_FSP1_CHIP5_CPU8    0x6278

#define FSM6_FSP1_CHIP6         0x6280
#define FSM6_FSP1_CHIP6_CPU1    0x6281
#define FSM6_FSP1_CHIP6_CPU2    0x6282
#define FSM6_FSP1_CHIP6_CPU3    0x6283
#define FSM6_FSP1_CHIP6_CPU4    0x6284
#define FSM6_FSP1_CHIP6_CPU5    0x6285
#define FSM6_FSP1_CHIP6_CPU6    0x6286
#define FSM6_FSP1_CHIP6_CPU7    0x6287
#define FSM6_FSP1_CHIP6_CPU8    0x6288

#define FSM6_FSP1_CHIP7         0x6290
#define FSM6_FSP1_CHIP7_CPU1    0x6291
#define FSM6_FSP1_CHIP7_CPU2    0x6292
#define FSM6_FSP1_CHIP7_CPU3    0x6293
#define FSM6_FSP1_CHIP7_CPU4    0x6294
#define FSM6_FSP1_CHIP7_CPU5    0x6295
#define FSM6_FSP1_CHIP7_CPU6    0x6296
#define FSM6_FSP1_CHIP7_CPU7    0x6297
#define FSM6_FSP1_CHIP7_CPU8    0x6298

#define FSM6_FSP1_CHIP8         0x62A0
#define FSM6_FSP1_CHIP8_CPU1    0x62A1
#define FSM6_FSP1_CHIP8_CPU2    0x62A2
#define FSM6_FSP1_CHIP8_CPU3    0x62A3
#define FSM6_FSP1_CHIP8_CPU4    0x62A4
#define FSM6_FSP1_CHIP8_CPU5    0x62A5
#define FSM6_FSP1_CHIP8_CPU6    0x62A6
#define FSM6_FSP1_CHIP8_CPU7    0x62A7
#define FSM6_FSP1_CHIP8_CPU8    0x62A8

#define FSM6_FSP1_CHIP9         0x62B0
#define FSM6_FSP1_CHIP9_CPU1    0x62B1
#define FSM6_FSP1_CHIP9_CPU2    0x62B2
#define FSM6_FSP1_CHIP9_CPU3    0x62B3
#define FSM6_FSP1_CHIP9_CPU4    0x62B4
#define FSM6_FSP1_CHIP9_CPU5    0x62B5
#define FSM6_FSP1_CHIP9_CPU6    0x62B6
#define FSM6_FSP1_CHIP9_CPU7    0x62B7
#define FSM6_FSP1_CHIP9_CPU8    0x62B8

#define FSM6_FSP1_CHIPALL       0x62F0

/* FSM6_FSP2 */
#define FSM6_FSP2_MCU           0x630D
#define FSM6_FSP2_CHIP1         0x6330
#define FSM6_FSP2_CHIP1_CPU1    0x6331
#define FSM6_FSP2_CHIP1_CPU2    0x6332
#define FSM6_FSP2_CHIP1_CPU3    0x6333
#define FSM6_FSP2_CHIP1_CPU4    0x6334
#define FSM6_FSP2_CHIP1_CPU5    0x6335
#define FSM6_FSP2_CHIP1_CPU6    0x6336
#define FSM6_FSP2_CHIP1_CPU7    0x6337
#define FSM6_FSP2_CHIP1_CPU8    0x6338
#define FSM6_FSP2_CHIP1_SMP1    0x633D /* FSM-r4 */

#define FSM6_FSP2_CHIP2         0x6340
#define FSM6_FSP2_CHIP2_CPU1    0x6341
#define FSM6_FSP2_CHIP2_CPU2    0x6342
#define FSM6_FSP2_CHIP2_CPU3    0x6343
#define FSM6_FSP2_CHIP2_CPU4    0x6344
#define FSM6_FSP2_CHIP2_CPU5    0x6345
#define FSM6_FSP2_CHIP2_CPU6    0x6346
#define FSM6_FSP2_CHIP2_CPU7    0x6347
#define FSM6_FSP2_CHIP2_CPU8    0x6348
#define FSM6_FSP2_CHIP2_SMP1    0x634D /* FSM-r4 */

#define FSM6_FSP2_CHIP3         0x6350
#define FSM6_FSP2_CHIP3_CPU1    0x6351
#define FSM6_FSP2_CHIP3_CPU2    0x6352
#define FSM6_FSP2_CHIP3_CPU3    0x6353
#define FSM6_FSP2_CHIP3_CPU4    0x6354
#define FSM6_FSP2_CHIP3_CPU5    0x6355
#define FSM6_FSP2_CHIP3_CPU6    0x6356
#define FSM6_FSP2_CHIP3_CPU7    0x6357
#define FSM6_FSP2_CHIP3_CPU8    0x6358
#define FSM6_FSP2_CHIP3_SMP1    0x635D /* FSM-r4 */

#define FSM6_FSP2_CHIP4         0x6360
#define FSM6_FSP2_CHIP4_CPU1    0x6361
#define FSM6_FSP2_CHIP4_CPU2    0x6362
#define FSM6_FSP2_CHIP4_CPU3    0x6363
#define FSM6_FSP2_CHIP4_CPU4    0x6364
#define FSM6_FSP2_CHIP4_CPU5    0x6365
#define FSM6_FSP2_CHIP4_CPU6    0x6366
#define FSM6_FSP2_CHIP4_CPU7    0x6367
#define FSM6_FSP2_CHIP4_CPU8    0x6368
#define FSM6_FSP2_CHIP4_SMP1    0x636D /* FSM-r4 */

#define FSM6_FSP2_CHIP5         0x6370
#define FSM6_FSP2_CHIP5_CPU1    0x6371
#define FSM6_FSP2_CHIP5_CPU2    0x6372
#define FSM6_FSP2_CHIP5_CPU3    0x6373
#define FSM6_FSP2_CHIP5_CPU4    0x6374
#define FSM6_FSP2_CHIP5_CPU5    0x6375
#define FSM6_FSP2_CHIP5_CPU6    0x6376
#define FSM6_FSP2_CHIP5_CPU7    0x6377
#define FSM6_FSP2_CHIP5_CPU8    0x6378

#define FSM6_FSP2_CHIP6         0x6380
#define FSM6_FSP2_CHIP6_CPU1    0x6381
#define FSM6_FSP2_CHIP6_CPU2    0x6382
#define FSM6_FSP2_CHIP6_CPU3    0x6383
#define FSM6_FSP2_CHIP6_CPU4    0x6384
#define FSM6_FSP2_CHIP6_CPU5    0x6385
#define FSM6_FSP2_CHIP6_CPU6    0x6386
#define FSM6_FSP2_CHIP6_CPU7    0x6387
#define FSM6_FSP2_CHIP6_CPU8    0x6388

#define FSM6_FSP2_CHIP7         0x6390
#define FSM6_FSP2_CHIP7_CPU1    0x6391
#define FSM6_FSP2_CHIP7_CPU2    0x6392
#define FSM6_FSP2_CHIP7_CPU3    0x6393
#define FSM6_FSP2_CHIP7_CPU4    0x6394
#define FSM6_FSP2_CHIP7_CPU5    0x6395
#define FSM6_FSP2_CHIP7_CPU6    0x6396
#define FSM6_FSP2_CHIP7_CPU7    0x6397
#define FSM6_FSP2_CHIP7_CPU8    0x6398

#define FSM6_FSP2_CHIP8         0x63A0
#define FSM6_FSP2_CHIP8_CPU1    0x63A1
#define FSM6_FSP2_CHIP8_CPU2    0x63A2
#define FSM6_FSP2_CHIP8_CPU3    0x63A3
#define FSM6_FSP2_CHIP8_CPU4    0x63A4
#define FSM6_FSP2_CHIP8_CPU5    0x63A5
#define FSM6_FSP2_CHIP8_CPU6    0x63A6
#define FSM6_FSP2_CHIP8_CPU7    0x63A7
#define FSM6_FSP2_CHIP8_CPU8    0x63A8

#define FSM6_FSP2_CHIP9         0x63B0
#define FSM6_FSP2_CHIP9_CPU1    0x63B1
#define FSM6_FSP2_CHIP9_CPU2    0x63B2
#define FSM6_FSP2_CHIP9_CPU3    0x63B3
#define FSM6_FSP2_CHIP9_CPU4    0x63B4
#define FSM6_FSP2_CHIP9_CPU5    0x63B5
#define FSM6_FSP2_CHIP9_CPU6    0x63B6
#define FSM6_FSP2_CHIP9_CPU7    0x63B7
#define FSM6_FSP2_CHIP9_CPU8    0x63B8

#define FSM6_FSP2_CHIPALL       0x63F0

/* FSM6_FSP3 */
#define FSM6_FSP3_MCU           0x640D
#define FSM6_FSP3_CHIP1         0x6430
#define FSM6_FSP3_CHIP1_CPU1    0x6431
#define FSM6_FSP3_CHIP1_CPU2    0x6432
#define FSM6_FSP3_CHIP1_CPU3    0x6433
#define FSM6_FSP3_CHIP1_CPU4    0x6434
#define FSM6_FSP3_CHIP1_CPU5    0x6435
#define FSM6_FSP3_CHIP1_CPU6    0x6436
#define FSM6_FSP3_CHIP1_CPU7    0x6437
#define FSM6_FSP3_CHIP1_CPU8    0x6438
#define FSM6_FSP3_CHIP1_SMP1    0x643D /* FSM-r4 */

#define FSM6_FSP3_CHIP2         0x6440
#define FSM6_FSP3_CHIP2_CPU1    0x6441
#define FSM6_FSP3_CHIP2_CPU2    0x6442
#define FSM6_FSP3_CHIP2_CPU3    0x6443
#define FSM6_FSP3_CHIP2_CPU4    0x6444
#define FSM6_FSP3_CHIP2_CPU5    0x6445
#define FSM6_FSP3_CHIP2_CPU6    0x6446
#define FSM6_FSP3_CHIP2_CPU7    0x6447
#define FSM6_FSP3_CHIP2_CPU8    0x6448
#define FSM6_FSP3_CHIP2_SMP1    0x644D /* FSM-r4 */

#define FSM6_FSP3_CHIP3         0x6450
#define FSM6_FSP3_CHIP3_CPU1    0x6451
#define FSM6_FSP3_CHIP3_CPU2    0x6452
#define FSM6_FSP3_CHIP3_CPU3    0x6453
#define FSM6_FSP3_CHIP3_CPU4    0x6454
#define FSM6_FSP3_CHIP3_CPU5    0x6455
#define FSM6_FSP3_CHIP3_CPU6    0x6456
#define FSM6_FSP3_CHIP3_CPU7    0x6457
#define FSM6_FSP3_CHIP3_CPU8    0x6458
#define FSM6_FSP3_CHIP3_SMP1    0x645D /* FSM-r4 */

#define FSM6_FSP3_CHIP4         0x6460
#define FSM6_FSP3_CHIP4_CPU1    0x6461
#define FSM6_FSP3_CHIP4_CPU2    0x6462
#define FSM6_FSP3_CHIP4_CPU3    0x6463
#define FSM6_FSP3_CHIP4_CPU4    0x6464
#define FSM6_FSP3_CHIP4_CPU5    0x6465
#define FSM6_FSP3_CHIP4_CPU6    0x6466
#define FSM6_FSP3_CHIP4_CPU7    0x6467
#define FSM6_FSP3_CHIP4_CPU8    0x6468
#define FSM6_FSP3_CHIP4_SMP1    0x646D /* FSM-r4 */

#define FSM6_FSP3_CHIP5         0x6470
#define FSM6_FSP3_CHIP5_CPU1    0x6471
#define FSM6_FSP3_CHIP5_CPU2    0x6472
#define FSM6_FSP3_CHIP5_CPU3    0x6473
#define FSM6_FSP3_CHIP5_CPU4    0x6474
#define FSM6_FSP3_CHIP5_CPU5    0x6475
#define FSM6_FSP3_CHIP5_CPU6    0x6476
#define FSM6_FSP3_CHIP5_CPU7    0x6477
#define FSM6_FSP3_CHIP5_CPU8    0x6478

#define FSM6_FSP3_CHIP6         0x6480
#define FSM6_FSP3_CHIP6_CPU1    0x6481
#define FSM6_FSP3_CHIP6_CPU2    0x6482
#define FSM6_FSP3_CHIP6_CPU3    0x6483
#define FSM6_FSP3_CHIP6_CPU4    0x6484
#define FSM6_FSP3_CHIP6_CPU5    0x6485
#define FSM6_FSP3_CHIP6_CPU6    0x6486
#define FSM6_FSP3_CHIP6_CPU7    0x6487
#define FSM6_FSP3_CHIP6_CPU8    0x6488

#define FSM6_FSP3_CHIP7         0x6490
#define FSM6_FSP3_CHIP7_CPU1    0x6491
#define FSM6_FSP3_CHIP7_CPU2    0x6492
#define FSM6_FSP3_CHIP7_CPU3    0x6493
#define FSM6_FSP3_CHIP7_CPU4    0x6494
#define FSM6_FSP3_CHIP7_CPU5    0x6495
#define FSM6_FSP3_CHIP7_CPU6    0x6496
#define FSM6_FSP3_CHIP7_CPU7    0x6497
#define FSM6_FSP3_CHIP7_CPU8    0x6498

#define FSM6_FSP3_CHIP8         0x64A0
#define FSM6_FSP3_CHIP8_CPU1    0x64A1
#define FSM6_FSP3_CHIP8_CPU2    0x64A2
#define FSM6_FSP3_CHIP8_CPU3    0x64A3
#define FSM6_FSP3_CHIP8_CPU4    0x64A4
#define FSM6_FSP3_CHIP8_CPU5    0x64A5
#define FSM6_FSP3_CHIP8_CPU6    0x64A6
#define FSM6_FSP3_CHIP8_CPU7    0x64A7
#define FSM6_FSP3_CHIP8_CPU8    0x64A8

#define FSM6_FSP3_CHIP9         0x64B0
#define FSM6_FSP3_CHIP9_CPU1    0x64B1
#define FSM6_FSP3_CHIP9_CPU2    0x64B2
#define FSM6_FSP3_CHIP9_CPU3    0x64B3
#define FSM6_FSP3_CHIP9_CPU4    0x64B4
#define FSM6_FSP3_CHIP9_CPU5    0x64B5
#define FSM6_FSP3_CHIP9_CPU6    0x64B6
#define FSM6_FSP3_CHIP9_CPU7    0x64B7
#define FSM6_FSP3_CHIP9_CPU8    0x64B8

#define FSM6_FSP3_CHIPALL       0x64F0


/* FSM7_FSP1 */
#define FSM7_FSP1_MCU           0x720D
#define FSM7_FSP1_CHIP1         0x7230
#define FSM7_FSP1_CHIP1_CPU1    0x7231
#define FSM7_FSP1_CHIP1_CPU2    0x7232
#define FSM7_FSP1_CHIP1_CPU3    0x7233
#define FSM7_FSP1_CHIP1_CPU4    0x7234
#define FSM7_FSP1_CHIP1_CPU5    0x7235
#define FSM7_FSP1_CHIP1_CPU6    0x7236
#define FSM7_FSP1_CHIP1_CPU7    0x7237
#define FSM7_FSP1_CHIP1_CPU8    0x7238
#define FSM7_FSP1_CHIP1_SMP1    0x723D /* FSM-r4 */

#define FSM7_FSP1_CHIP2         0x7240
#define FSM7_FSP1_CHIP2_CPU1    0x7241
#define FSM7_FSP1_CHIP2_CPU2    0x7242
#define FSM7_FSP1_CHIP2_CPU3    0x7243
#define FSM7_FSP1_CHIP2_CPU4    0x7244
#define FSM7_FSP1_CHIP2_CPU5    0x7245
#define FSM7_FSP1_CHIP2_CPU6    0x7246
#define FSM7_FSP1_CHIP2_CPU7    0x7247
#define FSM7_FSP1_CHIP2_CPU8    0x7248
#define FSM7_FSP1_CHIP2_SMP1    0x724D /* FSM-r4 */

#define FSM7_FSP1_CHIP3         0x7250
#define FSM7_FSP1_CHIP3_CPU1    0x7251
#define FSM7_FSP1_CHIP3_CPU2    0x7252
#define FSM7_FSP1_CHIP3_CPU3    0x7253
#define FSM7_FSP1_CHIP3_CPU4    0x7254
#define FSM7_FSP1_CHIP3_CPU5    0x7255
#define FSM7_FSP1_CHIP3_CPU6    0x7256
#define FSM7_FSP1_CHIP3_CPU7    0x7257
#define FSM7_FSP1_CHIP3_CPU8    0x7258
#define FSM7_FSP1_CHIP3_SMP1    0x725D /* FSM-r4 */

#define FSM7_FSP1_CHIP4         0x7260
#define FSM7_FSP1_CHIP4_CPU1    0x7261
#define FSM7_FSP1_CHIP4_CPU2    0x7262
#define FSM7_FSP1_CHIP4_CPU3    0x7263
#define FSM7_FSP1_CHIP4_CPU4    0x7264
#define FSM7_FSP1_CHIP4_CPU5    0x7265
#define FSM7_FSP1_CHIP4_CPU6    0x7266
#define FSM7_FSP1_CHIP4_CPU7    0x7267
#define FSM7_FSP1_CHIP4_CPU8    0x7268
#define FSM7_FSP1_CHIP4_SMP1    0x726D /* FSM-r4 */

#define FSM7_FSP1_CHIP5         0x7270
#define FSM7_FSP1_CHIP5_CPU1    0x7271
#define FSM7_FSP1_CHIP5_CPU2    0x7272
#define FSM7_FSP1_CHIP5_CPU3    0x7273
#define FSM7_FSP1_CHIP5_CPU4    0x7274
#define FSM7_FSP1_CHIP5_CPU5    0x7275
#define FSM7_FSP1_CHIP5_CPU6    0x7276
#define FSM7_FSP1_CHIP5_CPU7    0x7277
#define FSM7_FSP1_CHIP5_CPU8    0x7278

#define FSM7_FSP1_CHIP6         0x7280
#define FSM7_FSP1_CHIP6_CPU1    0x7281
#define FSM7_FSP1_CHIP6_CPU2    0x7282
#define FSM7_FSP1_CHIP6_CPU3    0x7283
#define FSM7_FSP1_CHIP6_CPU4    0x7284
#define FSM7_FSP1_CHIP6_CPU5    0x7285
#define FSM7_FSP1_CHIP6_CPU6    0x7286
#define FSM7_FSP1_CHIP6_CPU7    0x7287
#define FSM7_FSP1_CHIP6_CPU8    0x7288

#define FSM7_FSP1_CHIPALL       0x72F0

/* FSM7_FSP2 */
#define FSM7_FSP2_MCU           0x730D
#define FSM7_FSP2_CHIP1         0x7330
#define FSM7_FSP2_CHIP1_CPU1    0x7331
#define FSM7_FSP2_CHIP1_CPU2    0x7332
#define FSM7_FSP2_CHIP1_CPU3    0x7333
#define FSM7_FSP2_CHIP1_CPU4    0x7334
#define FSM7_FSP2_CHIP1_CPU5    0x7335
#define FSM7_FSP2_CHIP1_CPU6    0x7336
#define FSM7_FSP2_CHIP1_CPU7    0x7337
#define FSM7_FSP2_CHIP1_CPU8    0x7338
#define FSM7_FSP2_CHIP1_SMP1    0x733D /* FSM-r4 */

#define FSM7_FSP2_CHIP2         0x7340
#define FSM7_FSP2_CHIP2_CPU1    0x7341
#define FSM7_FSP2_CHIP2_CPU2    0x7342
#define FSM7_FSP2_CHIP2_CPU3    0x7343
#define FSM7_FSP2_CHIP2_CPU4    0x7344
#define FSM7_FSP2_CHIP2_CPU5    0x7345
#define FSM7_FSP2_CHIP2_CPU6    0x7346
#define FSM7_FSP2_CHIP2_CPU7    0x7347
#define FSM7_FSP2_CHIP2_CPU8    0x7348
#define FSM7_FSP2_CHIP2_SMP1    0x734D /* FSM-r4 */

#define FSM7_FSP2_CHIP3         0x7350
#define FSM7_FSP2_CHIP3_CPU1    0x7351
#define FSM7_FSP2_CHIP3_CPU2    0x7352
#define FSM7_FSP2_CHIP3_CPU3    0x7353
#define FSM7_FSP2_CHIP3_CPU4    0x7354
#define FSM7_FSP2_CHIP3_CPU5    0x7355
#define FSM7_FSP2_CHIP3_CPU6    0x7356
#define FSM7_FSP2_CHIP3_CPU7    0x7357
#define FSM7_FSP2_CHIP3_CPU8    0x7358
#define FSM7_FSP2_CHIP3_SMP1    0x735D /* FSM-r4 */

#define FSM7_FSP2_CHIP4         0x7360
#define FSM7_FSP2_CHIP4_CPU1    0x7361
#define FSM7_FSP2_CHIP4_CPU2    0x7362
#define FSM7_FSP2_CHIP4_CPU3    0x7363
#define FSM7_FSP2_CHIP4_CPU4    0x7364
#define FSM7_FSP2_CHIP4_CPU5    0x7365
#define FSM7_FSP2_CHIP4_CPU6    0x7366
#define FSM7_FSP2_CHIP4_CPU7    0x7367
#define FSM7_FSP2_CHIP4_CPU8    0x7368
#define FSM7_FSP2_CHIP4_SMP1    0x736D /* FSM-r4 */

#define FSM7_FSP2_CHIP5         0x7370
#define FSM7_FSP2_CHIP5_CPU1    0x7371
#define FSM7_FSP2_CHIP5_CPU2    0x7372
#define FSM7_FSP2_CHIP5_CPU3    0x7373
#define FSM7_FSP2_CHIP5_CPU4    0x7374
#define FSM7_FSP2_CHIP5_CPU5    0x7375
#define FSM7_FSP2_CHIP5_CPU6    0x7376
#define FSM7_FSP2_CHIP5_CPU7    0x7377
#define FSM7_FSP2_CHIP5_CPU8    0x7378

#define FSM7_FSP2_CHIP6         0x7380
#define FSM7_FSP2_CHIP6_CPU1    0x7381
#define FSM7_FSP2_CHIP6_CPU2    0x7382
#define FSM7_FSP2_CHIP6_CPU3    0x7383
#define FSM7_FSP2_CHIP6_CPU4    0x7384
#define FSM7_FSP2_CHIP6_CPU5    0x7385
#define FSM7_FSP2_CHIP6_CPU6    0x7386
#define FSM7_FSP2_CHIP6_CPU7    0x7387
#define FSM7_FSP2_CHIP6_CPU8    0x7388

#define FSM7_FSP2_CHIPALL       0x73F0

/* FSM7_FSP3 */
#define FSM7_FSP3_MCU           0x740D
#define FSM7_FSP3_CHIP1         0x7430
#define FSM7_FSP3_CHIP1_CPU1    0x7431
#define FSM7_FSP3_CHIP1_CPU2    0x7432
#define FSM7_FSP3_CHIP1_CPU3    0x7433
#define FSM7_FSP3_CHIP1_CPU4    0x7434
#define FSM7_FSP3_CHIP1_CPU5    0x7435
#define FSM7_FSP3_CHIP1_CPU6    0x7436
#define FSM7_FSP3_CHIP1_CPU7    0x7437
#define FSM7_FSP3_CHIP1_CPU8    0x7438
#define FSM7_FSP3_CHIP1_SMP1    0x743D /* FSM-r4 */

#define FSM7_FSP3_CHIP2         0x7440
#define FSM7_FSP3_CHIP2_CPU1    0x7441
#define FSM7_FSP3_CHIP2_CPU2    0x7442
#define FSM7_FSP3_CHIP2_CPU3    0x7443
#define FSM7_FSP3_CHIP2_CPU4    0x7444
#define FSM7_FSP3_CHIP2_CPU5    0x7445
#define FSM7_FSP3_CHIP2_CPU6    0x7446
#define FSM7_FSP3_CHIP2_CPU7    0x7447
#define FSM7_FSP3_CHIP2_CPU8    0x7448
#define FSM7_FSP3_CHIP2_SMP1    0x744D /* FSM-r4 */

#define FSM7_FSP3_CHIP3         0x7450
#define FSM7_FSP3_CHIP3_CPU1    0x7451
#define FSM7_FSP3_CHIP3_CPU2    0x7452
#define FSM7_FSP3_CHIP3_CPU3    0x7453
#define FSM7_FSP3_CHIP3_CPU4    0x7454
#define FSM7_FSP3_CHIP3_CPU5    0x7455
#define FSM7_FSP3_CHIP3_CPU6    0x7456
#define FSM7_FSP3_CHIP3_CPU7    0x7457
#define FSM7_FSP3_CHIP3_CPU8    0x7458
#define FSM7_FSP3_CHIP3_SMP1    0x745D /* FSM-r4 */

#define FSM7_FSP3_CHIP4         0x7460
#define FSM7_FSP3_CHIP4_CPU1    0x7461
#define FSM7_FSP3_CHIP4_CPU2    0x7462
#define FSM7_FSP3_CHIP4_CPU3    0x7463
#define FSM7_FSP3_CHIP4_CPU4    0x7464
#define FSM7_FSP3_CHIP4_CPU5    0x7465
#define FSM7_FSP3_CHIP4_CPU6    0x7466
#define FSM7_FSP3_CHIP4_CPU7    0x7467
#define FSM7_FSP3_CHIP4_CPU8    0x7468
#define FSM7_FSP3_CHIP4_SMP1    0x746D /* FSM-r4 */

#define FSM7_FSP3_CHIP5         0x7470
#define FSM7_FSP3_CHIP5_CPU1    0x7471
#define FSM7_FSP3_CHIP5_CPU2    0x7472
#define FSM7_FSP3_CHIP5_CPU3    0x7473
#define FSM7_FSP3_CHIP5_CPU4    0x7474
#define FSM7_FSP3_CHIP5_CPU5    0x7475
#define FSM7_FSP3_CHIP5_CPU6    0x7476
#define FSM7_FSP3_CHIP5_CPU7    0x7477
#define FSM7_FSP3_CHIP5_CPU8    0x7478

#define FSM7_FSP3_CHIP6         0x7480
#define FSM7_FSP3_CHIP6_CPU1    0x7481
#define FSM7_FSP3_CHIP6_CPU2    0x7482
#define FSM7_FSP3_CHIP6_CPU3    0x7483
#define FSM7_FSP3_CHIP6_CPU4    0x7484
#define FSM7_FSP3_CHIP6_CPU5    0x7485
#define FSM7_FSP3_CHIP6_CPU6    0x7486
#define FSM7_FSP3_CHIP6_CPU7    0x7487
#define FSM7_FSP3_CHIP6_CPU8    0x7488

#define FSM7_FSP3_CHIPALL       0x74F0


/* FSM8_FSP1 */
#define FSM8_FSP1_MCU           0x820D
#define FSM8_FSP1_CHIP1         0x8230
#define FSM8_FSP1_CHIP1_CPU1    0x8231
#define FSM8_FSP1_CHIP1_CPU2    0x8232
#define FSM8_FSP1_CHIP1_CPU3    0x8233
#define FSM8_FSP1_CHIP1_CPU4    0x8234
#define FSM8_FSP1_CHIP1_CPU5    0x8235
#define FSM8_FSP1_CHIP1_CPU6    0x8236
#define FSM8_FSP1_CHIP1_CPU7    0x8237
#define FSM8_FSP1_CHIP1_CPU8    0x8238
#define FSM8_FSP1_CHIP1_SMP1    0x823D /* FSM-r4 */

#define FSM8_FSP1_CHIP2         0x8240
#define FSM8_FSP1_CHIP2_CPU1    0x8241
#define FSM8_FSP1_CHIP2_CPU2    0x8242
#define FSM8_FSP1_CHIP2_CPU3    0x8243
#define FSM8_FSP1_CHIP2_CPU4    0x8244
#define FSM8_FSP1_CHIP2_CPU5    0x8245
#define FSM8_FSP1_CHIP2_CPU6    0x8246
#define FSM8_FSP1_CHIP2_CPU7    0x8247
#define FSM8_FSP1_CHIP2_CPU8    0x8248
#define FSM8_FSP1_CHIP2_SMP1    0x824D /* FSM-r4 */

#define FSM8_FSP1_CHIP3         0x8250
#define FSM8_FSP1_CHIP3_CPU1    0x8251
#define FSM8_FSP1_CHIP3_CPU2    0x8252
#define FSM8_FSP1_CHIP3_CPU3    0x8253
#define FSM8_FSP1_CHIP3_CPU4    0x8254
#define FSM8_FSP1_CHIP3_CPU5    0x8255
#define FSM8_FSP1_CHIP3_CPU6    0x8256
#define FSM8_FSP1_CHIP3_CPU7    0x8257
#define FSM8_FSP1_CHIP3_CPU8    0x8258
#define FSM8_FSP1_CHIP3_SMP1    0x825D /* FSM-r4 */

#define FSM8_FSP1_CHIP4         0x8260
#define FSM8_FSP1_CHIP4_CPU1    0x8261
#define FSM8_FSP1_CHIP4_CPU2    0x8262
#define FSM8_FSP1_CHIP4_CPU3    0x8263
#define FSM8_FSP1_CHIP4_CPU4    0x8264
#define FSM8_FSP1_CHIP4_CPU5    0x8265
#define FSM8_FSP1_CHIP4_CPU6    0x8266
#define FSM8_FSP1_CHIP4_CPU7    0x8267
#define FSM8_FSP1_CHIP4_CPU8    0x8268
#define FSM8_FSP1_CHIP4_SMP1    0x826D /* FSM-r4 */

#define FSM8_FSP1_CHIP5         0x8270
#define FSM8_FSP1_CHIP5_CPU1    0x8271
#define FSM8_FSP1_CHIP5_CPU2    0x8272
#define FSM8_FSP1_CHIP5_CPU3    0x8273
#define FSM8_FSP1_CHIP5_CPU4    0x8274
#define FSM8_FSP1_CHIP5_CPU5    0x8275
#define FSM8_FSP1_CHIP5_CPU6    0x8276
#define FSM8_FSP1_CHIP5_CPU7    0x8277
#define FSM8_FSP1_CHIP5_CPU8    0x8278

#define FSM8_FSP1_CHIP6         0x8280
#define FSM8_FSP1_CHIP6_CPU1    0x8281
#define FSM8_FSP1_CHIP6_CPU2    0x8282
#define FSM8_FSP1_CHIP6_CPU3    0x8283
#define FSM8_FSP1_CHIP6_CPU4    0x8284
#define FSM8_FSP1_CHIP6_CPU5    0x8285
#define FSM8_FSP1_CHIP6_CPU6    0x8286
#define FSM8_FSP1_CHIP6_CPU7    0x8287
#define FSM8_FSP1_CHIP6_CPU8    0x8288

#define FSM8_FSP1_CHIPALL       0x82F0

/* FSM8_FSP2 */
#define FSM8_FSP2_MCU           0x830D
#define FSM8_FSP2_CHIP1         0x8330
#define FSM8_FSP2_CHIP1_CPU1    0x8331
#define FSM8_FSP2_CHIP1_CPU2    0x8332
#define FSM8_FSP2_CHIP1_CPU3    0x8333
#define FSM8_FSP2_CHIP1_CPU4    0x8334
#define FSM8_FSP2_CHIP1_CPU5    0x8335
#define FSM8_FSP2_CHIP1_CPU6    0x8336
#define FSM8_FSP2_CHIP1_CPU7    0x8337
#define FSM8_FSP2_CHIP1_CPU8    0x8338
#define FSM8_FSP2_CHIP1_SMP1    0x833D /* FSM-r4 */

#define FSM8_FSP2_CHIP2         0x8340
#define FSM8_FSP2_CHIP2_CPU1    0x8341
#define FSM8_FSP2_CHIP2_CPU2    0x8342
#define FSM8_FSP2_CHIP2_CPU3    0x8343
#define FSM8_FSP2_CHIP2_CPU4    0x8344
#define FSM8_FSP2_CHIP2_CPU5    0x8345
#define FSM8_FSP2_CHIP2_CPU6    0x8346
#define FSM8_FSP2_CHIP2_CPU7    0x8347
#define FSM8_FSP2_CHIP2_CPU8    0x8348
#define FSM8_FSP2_CHIP2_SMP1    0x834D /* FSM-r4 */

#define FSM8_FSP2_CHIP3         0x8350
#define FSM8_FSP2_CHIP3_CPU1    0x8351
#define FSM8_FSP2_CHIP3_CPU2    0x8352
#define FSM8_FSP2_CHIP3_CPU3    0x8353
#define FSM8_FSP2_CHIP3_CPU4    0x8354
#define FSM8_FSP2_CHIP3_CPU5    0x8355
#define FSM8_FSP2_CHIP3_CPU6    0x8356
#define FSM8_FSP2_CHIP3_CPU7    0x8357
#define FSM8_FSP2_CHIP3_CPU8    0x8358
#define FSM8_FSP2_CHIP3_SMP1    0x835D /* FSM-r4 */

#define FSM8_FSP2_CHIP4         0x8360
#define FSM8_FSP2_CHIP4_CPU1    0x8361
#define FSM8_FSP2_CHIP4_CPU2    0x8362
#define FSM8_FSP2_CHIP4_CPU3    0x8363
#define FSM8_FSP2_CHIP4_CPU4    0x8364
#define FSM8_FSP2_CHIP4_CPU5    0x8365
#define FSM8_FSP2_CHIP4_CPU6    0x8366
#define FSM8_FSP2_CHIP4_CPU7    0x8367
#define FSM8_FSP2_CHIP4_CPU8    0x8368
#define FSM8_FSP2_CHIP4_SMP1    0x836D /* FSM-r4 */

#define FSM8_FSP2_CHIP5         0x8370
#define FSM8_FSP2_CHIP5_CPU1    0x8371
#define FSM8_FSP2_CHIP5_CPU2    0x8372
#define FSM8_FSP2_CHIP5_CPU3    0x8373
#define FSM8_FSP2_CHIP5_CPU4    0x8374
#define FSM8_FSP2_CHIP5_CPU5    0x8375
#define FSM8_FSP2_CHIP5_CPU6    0x8376
#define FSM8_FSP2_CHIP5_CPU7    0x8377
#define FSM8_FSP2_CHIP5_CPU8    0x8378

#define FSM8_FSP2_CHIP6         0x8380
#define FSM8_FSP2_CHIP6_CPU1    0x8381
#define FSM8_FSP2_CHIP6_CPU2    0x8382
#define FSM8_FSP2_CHIP6_CPU3    0x8383
#define FSM8_FSP2_CHIP6_CPU4    0x8384
#define FSM8_FSP2_CHIP6_CPU5    0x8385
#define FSM8_FSP2_CHIP6_CPU6    0x8386
#define FSM8_FSP2_CHIP6_CPU7    0x8387
#define FSM8_FSP2_CHIP6_CPU8    0x8388

#define FSM8_FSP2_CHIPALL       0x83F0

/* FSM8_FSP3 */
#define FSM8_FSP3_MCU           0x840D
#define FSM8_FSP3_CHIP1         0x8430
#define FSM8_FSP3_CHIP1_CPU1    0x8431
#define FSM8_FSP3_CHIP1_CPU2    0x8432
#define FSM8_FSP3_CHIP1_CPU3    0x8433
#define FSM8_FSP3_CHIP1_CPU4    0x8434
#define FSM8_FSP3_CHIP1_CPU5    0x8435
#define FSM8_FSP3_CHIP1_CPU6    0x8436
#define FSM8_FSP3_CHIP1_CPU7    0x8437
#define FSM8_FSP3_CHIP1_CPU8    0x8438
#define FSM8_FSP3_CHIP1_SMP1    0x843D /* FSM-r4 */

#define FSM8_FSP3_CHIP2         0x8440
#define FSM8_FSP3_CHIP2_CPU1    0x8441
#define FSM8_FSP3_CHIP2_CPU2    0x8442
#define FSM8_FSP3_CHIP2_CPU3    0x8443
#define FSM8_FSP3_CHIP2_CPU4    0x8444
#define FSM8_FSP3_CHIP2_CPU5    0x8445
#define FSM8_FSP3_CHIP2_CPU6    0x8446
#define FSM8_FSP3_CHIP2_CPU7    0x8447
#define FSM8_FSP3_CHIP2_CPU8    0x8448
#define FSM8_FSP3_CHIP2_SMP1    0x844D /* FSM-r4 */

#define FSM8_FSP3_CHIP3         0x8450
#define FSM8_FSP3_CHIP3_CPU1    0x8451
#define FSM8_FSP3_CHIP3_CPU2    0x8452
#define FSM8_FSP3_CHIP3_CPU3    0x8453
#define FSM8_FSP3_CHIP3_CPU4    0x8454
#define FSM8_FSP3_CHIP3_CPU5    0x8455
#define FSM8_FSP3_CHIP3_CPU6    0x8456
#define FSM8_FSP3_CHIP3_CPU7    0x8457
#define FSM8_FSP3_CHIP3_CPU8    0x8458
#define FSM8_FSP3_CHIP3_SMP1    0x845D /* FSM-r4 */

#define FSM8_FSP3_CHIP4         0x8460
#define FSM8_FSP3_CHIP4_CPU1    0x8461
#define FSM8_FSP3_CHIP4_CPU2    0x8462
#define FSM8_FSP3_CHIP4_CPU3    0x8463
#define FSM8_FSP3_CHIP4_CPU4    0x8464
#define FSM8_FSP3_CHIP4_CPU5    0x8465
#define FSM8_FSP3_CHIP4_CPU6    0x8466
#define FSM8_FSP3_CHIP4_CPU7    0x8467
#define FSM8_FSP3_CHIP4_CPU8    0x8468
#define FSM8_FSP3_CHIP4_SMP1    0x846D /* FSM-r4 */

#define FSM8_FSP3_CHIP5         0x8470
#define FSM8_FSP3_CHIP5_CPU1    0x8471
#define FSM8_FSP3_CHIP5_CPU2    0x8472
#define FSM8_FSP3_CHIP5_CPU3    0x8473
#define FSM8_FSP3_CHIP5_CPU4    0x8474
#define FSM8_FSP3_CHIP5_CPU5    0x8475
#define FSM8_FSP3_CHIP5_CPU6    0x8476
#define FSM8_FSP3_CHIP5_CPU7    0x8477
#define FSM8_FSP3_CHIP5_CPU8    0x8478

#define FSM8_FSP3_CHIP6         0x8480
#define FSM8_FSP3_CHIP6_CPU1    0x8481
#define FSM8_FSP3_CHIP6_CPU2    0x8482
#define FSM8_FSP3_CHIP6_CPU3    0x8483
#define FSM8_FSP3_CHIP6_CPU4    0x8484
#define FSM8_FSP3_CHIP6_CPU5    0x8485
#define FSM8_FSP3_CHIP6_CPU6    0x8486
#define FSM8_FSP3_CHIP6_CPU7    0x8487
#define FSM8_FSP3_CHIP6_CPU8    0x8488

#define FSM8_FSP3_CHIPALL       0x84F0


/* FSM9_FSP1 */
#define FSM9_FSP1_MCU           0x920D
#define FSM9_FSP1_CHIP1         0x9230
#define FSM9_FSP1_CHIP1_CPU1    0x9231
#define FSM9_FSP1_CHIP1_CPU2    0x9232
#define FSM9_FSP1_CHIP1_CPU3    0x9233
#define FSM9_FSP1_CHIP1_CPU4    0x9234
#define FSM9_FSP1_CHIP1_CPU5    0x9235
#define FSM9_FSP1_CHIP1_CPU6    0x9236
#define FSM9_FSP1_CHIP1_CPU7    0x9237
#define FSM9_FSP1_CHIP1_CPU8    0x9238
#define FSM9_FSP1_CHIP1_SMP1    0x923D /* FSM-r4 */

#define FSM9_FSP1_CHIP2         0x9240
#define FSM9_FSP1_CHIP2_CPU1    0x9241
#define FSM9_FSP1_CHIP2_CPU2    0x9242
#define FSM9_FSP1_CHIP2_CPU3    0x9243
#define FSM9_FSP1_CHIP2_CPU4    0x9244
#define FSM9_FSP1_CHIP2_CPU5    0x9245
#define FSM9_FSP1_CHIP2_CPU6    0x9246
#define FSM9_FSP1_CHIP2_CPU7    0x9247
#define FSM9_FSP1_CHIP2_CPU8    0x9248
#define FSM9_FSP1_CHIP2_SMP1    0x924D /* FSM-r4 */

#define FSM9_FSP1_CHIP3         0x9250
#define FSM9_FSP1_CHIP3_CPU1    0x9251
#define FSM9_FSP1_CHIP3_CPU2    0x9252
#define FSM9_FSP1_CHIP3_CPU3    0x9253
#define FSM9_FSP1_CHIP3_CPU4    0x9254
#define FSM9_FSP1_CHIP3_CPU5    0x9255
#define FSM9_FSP1_CHIP3_CPU6    0x9256
#define FSM9_FSP1_CHIP3_CPU7    0x9257
#define FSM9_FSP1_CHIP3_CPU8    0x9258
#define FSM9_FSP1_CHIP3_SMP1    0x925D /* FSM-r4 */

#define FSM9_FSP1_CHIP4         0x9260
#define FSM9_FSP1_CHIP4_CPU1    0x9261
#define FSM9_FSP1_CHIP4_CPU2    0x9262
#define FSM9_FSP1_CHIP4_CPU3    0x9263
#define FSM9_FSP1_CHIP4_CPU4    0x9264
#define FSM9_FSP1_CHIP4_CPU5    0x9265
#define FSM9_FSP1_CHIP4_CPU6    0x9266
#define FSM9_FSP1_CHIP4_CPU7    0x9267
#define FSM9_FSP1_CHIP4_CPU8    0x9268
#define FSM9_FSP1_CHIP4_SMP1    0x926D /* FSM-r4 */

#define FSM9_FSP1_CHIP5         0x9270
#define FSM9_FSP1_CHIP5_CPU1    0x9271
#define FSM9_FSP1_CHIP5_CPU2    0x9272
#define FSM9_FSP1_CHIP5_CPU3    0x9273
#define FSM9_FSP1_CHIP5_CPU4    0x9274
#define FSM9_FSP1_CHIP5_CPU5    0x9275
#define FSM9_FSP1_CHIP5_CPU6    0x9276
#define FSM9_FSP1_CHIP5_CPU7    0x9277
#define FSM9_FSP1_CHIP5_CPU8    0x9278

#define FSM9_FSP1_CHIP6         0x9280
#define FSM9_FSP1_CHIP6_CPU1    0x9281
#define FSM9_FSP1_CHIP6_CPU2    0x9282
#define FSM9_FSP1_CHIP6_CPU3    0x9283
#define FSM9_FSP1_CHIP6_CPU4    0x9284
#define FSM9_FSP1_CHIP6_CPU5    0x9285
#define FSM9_FSP1_CHIP6_CPU6    0x9286
#define FSM9_FSP1_CHIP6_CPU7    0x9287
#define FSM9_FSP1_CHIP6_CPU8    0x9288

#define FSM9_FSP1_CHIPALL       0x92F0

/* FSM9_FSP2 */
#define FSM9_FSP2_MCU           0x930D
#define FSM9_FSP2_CHIP1         0x9330
#define FSM9_FSP2_CHIP1_CPU1    0x9331
#define FSM9_FSP2_CHIP1_CPU2    0x9332
#define FSM9_FSP2_CHIP1_CPU3    0x9333
#define FSM9_FSP2_CHIP1_CPU4    0x9334
#define FSM9_FSP2_CHIP1_CPU5    0x9335
#define FSM9_FSP2_CHIP1_CPU6    0x9336
#define FSM9_FSP2_CHIP1_CPU7    0x9337
#define FSM9_FSP2_CHIP1_CPU8    0x9338
#define FSM9_FSP2_CHIP1_SMP1    0x933D /* FSM-r4 */

#define FSM9_FSP2_CHIP2         0x9340
#define FSM9_FSP2_CHIP2_CPU1    0x9341
#define FSM9_FSP2_CHIP2_CPU2    0x9342
#define FSM9_FSP2_CHIP2_CPU3    0x9343
#define FSM9_FSP2_CHIP2_CPU4    0x9344
#define FSM9_FSP2_CHIP2_CPU5    0x9345
#define FSM9_FSP2_CHIP2_CPU6    0x9346
#define FSM9_FSP2_CHIP2_CPU7    0x9347
#define FSM9_FSP2_CHIP2_CPU8    0x9348
#define FSM9_FSP2_CHIP2_SMP1    0x934D /* FSM-r4 */

#define FSM9_FSP2_CHIP3         0x9350
#define FSM9_FSP2_CHIP3_CPU1    0x9351
#define FSM9_FSP2_CHIP3_CPU2    0x9352
#define FSM9_FSP2_CHIP3_CPU3    0x9353
#define FSM9_FSP2_CHIP3_CPU4    0x9354
#define FSM9_FSP2_CHIP3_CPU5    0x9355
#define FSM9_FSP2_CHIP3_CPU6    0x9356
#define FSM9_FSP2_CHIP3_CPU7    0x9357
#define FSM9_FSP2_CHIP3_CPU8    0x9358
#define FSM9_FSP2_CHIP3_SMP1    0x935D /* FSM-r4 */

#define FSM9_FSP2_CHIP4         0x9360
#define FSM9_FSP2_CHIP4_CPU1    0x9361
#define FSM9_FSP2_CHIP4_CPU2    0x9362
#define FSM9_FSP2_CHIP4_CPU3    0x9363
#define FSM9_FSP2_CHIP4_CPU4    0x9364
#define FSM9_FSP2_CHIP4_CPU5    0x9365
#define FSM9_FSP2_CHIP4_CPU6    0x9366
#define FSM9_FSP2_CHIP4_CPU7    0x9367
#define FSM9_FSP2_CHIP4_CPU8    0x9368
#define FSM9_FSP2_CHIP4_SMP1    0x936D /* FSM-r4 */

#define FSM9_FSP2_CHIP5         0x9370
#define FSM9_FSP2_CHIP5_CPU1    0x9371
#define FSM9_FSP2_CHIP5_CPU2    0x9372
#define FSM9_FSP2_CHIP5_CPU3    0x9373
#define FSM9_FSP2_CHIP5_CPU4    0x9374
#define FSM9_FSP2_CHIP5_CPU5    0x9375
#define FSM9_FSP2_CHIP5_CPU6    0x9376
#define FSM9_FSP2_CHIP5_CPU7    0x9377
#define FSM9_FSP2_CHIP5_CPU8    0x9378

#define FSM9_FSP2_CHIP6         0x9380
#define FSM9_FSP2_CHIP6_CPU1    0x9381
#define FSM9_FSP2_CHIP6_CPU2    0x9382
#define FSM9_FSP2_CHIP6_CPU3    0x9383
#define FSM9_FSP2_CHIP6_CPU4    0x9384
#define FSM9_FSP2_CHIP6_CPU5    0x9385
#define FSM9_FSP2_CHIP6_CPU6    0x9386
#define FSM9_FSP2_CHIP6_CPU7    0x9387
#define FSM9_FSP2_CHIP6_CPU8    0x9388

#define FSM9_FSP2_CHIPALL       0x93F0

/* FSM9_FSP3 */
#define FSM9_FSP3_MCU           0x940D
#define FSM9_FSP3_CHIP1         0x9430
#define FSM9_FSP3_CHIP1_CPU1    0x9431
#define FSM9_FSP3_CHIP1_CPU2    0x9432
#define FSM9_FSP3_CHIP1_CPU3    0x9433
#define FSM9_FSP3_CHIP1_CPU4    0x9434
#define FSM9_FSP3_CHIP1_CPU5    0x9435
#define FSM9_FSP3_CHIP1_CPU6    0x9436
#define FSM9_FSP3_CHIP1_CPU7    0x9437
#define FSM9_FSP3_CHIP1_CPU8    0x9438
#define FSM9_FSP3_CHIP1_SMP1    0x943D /* FSM-r4 */

#define FSM9_FSP3_CHIP2         0x9440
#define FSM9_FSP3_CHIP2_CPU1    0x9441
#define FSM9_FSP3_CHIP2_CPU2    0x9442
#define FSM9_FSP3_CHIP2_CPU3    0x9443
#define FSM9_FSP3_CHIP2_CPU4    0x9444
#define FSM9_FSP3_CHIP2_CPU5    0x9445
#define FSM9_FSP3_CHIP2_CPU6    0x9446
#define FSM9_FSP3_CHIP2_CPU7    0x9447
#define FSM9_FSP3_CHIP2_CPU8    0x9448
#define FSM9_FSP3_CHIP2_SMP1    0x944D /* FSM-r4 */

#define FSM9_FSP3_CHIP3         0x9450
#define FSM9_FSP3_CHIP3_CPU1    0x9451
#define FSM9_FSP3_CHIP3_CPU2    0x9452
#define FSM9_FSP3_CHIP3_CPU3    0x9453
#define FSM9_FSP3_CHIP3_CPU4    0x9454
#define FSM9_FSP3_CHIP3_CPU5    0x9455
#define FSM9_FSP3_CHIP3_CPU6    0x9456
#define FSM9_FSP3_CHIP3_CPU7    0x9457
#define FSM9_FSP3_CHIP3_CPU8    0x9458
#define FSM9_FSP3_CHIP3_SMP1    0x945D /* FSM-r4 */

#define FSM9_FSP3_CHIP4         0x9460
#define FSM9_FSP3_CHIP4_CPU1    0x9461
#define FSM9_FSP3_CHIP4_CPU2    0x9462
#define FSM9_FSP3_CHIP4_CPU3    0x9463
#define FSM9_FSP3_CHIP4_CPU4    0x9464
#define FSM9_FSP3_CHIP4_CPU5    0x9465
#define FSM9_FSP3_CHIP4_CPU6    0x9466
#define FSM9_FSP3_CHIP4_CPU7    0x9467
#define FSM9_FSP3_CHIP4_CPU8    0x9468
#define FSM9_FSP3_CHIP4_SMP1    0x946D /* FSM-r4 */

#define FSM9_FSP3_CHIP5         0x9470
#define FSM9_FSP3_CHIP5_CPU1    0x9471
#define FSM9_FSP3_CHIP5_CPU2    0x9472
#define FSM9_FSP3_CHIP5_CPU3    0x9473
#define FSM9_FSP3_CHIP5_CPU4    0x9474
#define FSM9_FSP3_CHIP5_CPU5    0x9475
#define FSM9_FSP3_CHIP5_CPU6    0x9476
#define FSM9_FSP3_CHIP5_CPU7    0x9477
#define FSM9_FSP3_CHIP5_CPU8    0x9478

#define FSM9_FSP3_CHIP6         0x9480
#define FSM9_FSP3_CHIP6_CPU1    0x9481
#define FSM9_FSP3_CHIP6_CPU2    0x9482
#define FSM9_FSP3_CHIP6_CPU3    0x9483
#define FSM9_FSP3_CHIP6_CPU4    0x9484
#define FSM9_FSP3_CHIP6_CPU5    0x9485
#define FSM9_FSP3_CHIP6_CPU6    0x9486
#define FSM9_FSP3_CHIP6_CPU7    0x9487
#define FSM9_FSP3_CHIP6_CPU8    0x9488

#define FSM9_FSP3_CHIPALL       0x94F0


/* FSM10_FSP1 */
#define FSM10_FSP1_MCU           0xA20D
#define FSM10_FSP1_CHIP1         0xA230
#define FSM10_FSP1_CHIP1_CPU1    0xA231
#define FSM10_FSP1_CHIP1_CPU2    0xA232
#define FSM10_FSP1_CHIP1_CPU3    0xA233
#define FSM10_FSP1_CHIP1_CPU4    0xA234
#define FSM10_FSP1_CHIP1_CPU5    0xA235
#define FSM10_FSP1_CHIP1_CPU6    0xA236
#define FSM10_FSP1_CHIP1_CPU7    0xA237
#define FSM10_FSP1_CHIP1_CPU8    0xA238
#define FSM10_FSP1_CHIP1_SMP1    0xA23D /* FSM-r4 */

#define FSM10_FSP1_CHIP2         0xA240
#define FSM10_FSP1_CHIP2_CPU1    0xA241
#define FSM10_FSP1_CHIP2_CPU2    0xA242
#define FSM10_FSP1_CHIP2_CPU3    0xA243
#define FSM10_FSP1_CHIP2_CPU4    0xA244
#define FSM10_FSP1_CHIP2_CPU5    0xA245
#define FSM10_FSP1_CHIP2_CPU6    0xA246
#define FSM10_FSP1_CHIP2_CPU7    0xA247
#define FSM10_FSP1_CHIP2_CPU8    0xA248
#define FSM10_FSP1_CHIP2_SMP1    0xA24D /* FSM-r4 */

#define FSM10_FSP1_CHIP3         0xA250
#define FSM10_FSP1_CHIP3_CPU1    0xA251
#define FSM10_FSP1_CHIP3_CPU2    0xA252
#define FSM10_FSP1_CHIP3_CPU3    0xA253
#define FSM10_FSP1_CHIP3_CPU4    0xA254
#define FSM10_FSP1_CHIP3_CPU5    0xA255
#define FSM10_FSP1_CHIP3_CPU6    0xA256
#define FSM10_FSP1_CHIP3_CPU7    0xA257
#define FSM10_FSP1_CHIP3_CPU8    0xA258
#define FSM10_FSP1_CHIP3_SMP1    0xA25D /* FSM-r4 */

#define FSM10_FSP1_CHIP4         0xA260
#define FSM10_FSP1_CHIP4_CPU1    0xA261
#define FSM10_FSP1_CHIP4_CPU2    0xA262
#define FSM10_FSP1_CHIP4_CPU3    0xA263
#define FSM10_FSP1_CHIP4_CPU4    0xA264
#define FSM10_FSP1_CHIP4_CPU5    0xA265
#define FSM10_FSP1_CHIP4_CPU6    0xA266
#define FSM10_FSP1_CHIP4_CPU7    0xA267
#define FSM10_FSP1_CHIP4_CPU8    0xA268
#define FSM10_FSP1_CHIP4_SMP1    0xA26D /* FSM-r4 */

#define FSM10_FSP1_CHIP5         0xA270
#define FSM10_FSP1_CHIP5_CPU1    0xA271
#define FSM10_FSP1_CHIP5_CPU2    0xA272
#define FSM10_FSP1_CHIP5_CPU3    0xA273
#define FSM10_FSP1_CHIP5_CPU4    0xA274
#define FSM10_FSP1_CHIP5_CPU5    0xA275
#define FSM10_FSP1_CHIP5_CPU6    0xA276
#define FSM10_FSP1_CHIP5_CPU7    0xA277
#define FSM10_FSP1_CHIP5_CPU8    0xA278

#define FSM10_FSP1_CHIP6         0xA280
#define FSM10_FSP1_CHIP6_CPU1    0xA281
#define FSM10_FSP1_CHIP6_CPU2    0xA282
#define FSM10_FSP1_CHIP6_CPU3    0xA283
#define FSM10_FSP1_CHIP6_CPU4    0xA284
#define FSM10_FSP1_CHIP6_CPU5    0xA285
#define FSM10_FSP1_CHIP6_CPU6    0xA286
#define FSM10_FSP1_CHIP6_CPU7    0xA287
#define FSM10_FSP1_CHIP6_CPU8    0xA288

#define FSM10_FSP1_CHIPALL       0xA2F0

/* FSM10_FSP2 */
#define FSM10_FSP2_MCU           0xA30D
#define FSM10_FSP2_CHIP1         0xA330
#define FSM10_FSP2_CHIP1_CPU1    0xA331
#define FSM10_FSP2_CHIP1_CPU2    0xA332
#define FSM10_FSP2_CHIP1_CPU3    0xA333
#define FSM10_FSP2_CHIP1_CPU4    0xA334
#define FSM10_FSP2_CHIP1_CPU5    0xA335
#define FSM10_FSP2_CHIP1_CPU6    0xA336
#define FSM10_FSP2_CHIP1_CPU7    0xA337
#define FSM10_FSP2_CHIP1_CPU8    0xA338
#define FSM10_FSP2_CHIP1_SMP1    0xA33D /* FSM-r4 */

#define FSM10_FSP2_CHIP2         0xA340
#define FSM10_FSP2_CHIP2_CPU1    0xA341
#define FSM10_FSP2_CHIP2_CPU2    0xA342
#define FSM10_FSP2_CHIP2_CPU3    0xA343
#define FSM10_FSP2_CHIP2_CPU4    0xA344
#define FSM10_FSP2_CHIP2_CPU5    0xA345
#define FSM10_FSP2_CHIP2_CPU6    0xA346
#define FSM10_FSP2_CHIP2_CPU7    0xA347
#define FSM10_FSP2_CHIP2_CPU8    0xA348
#define FSM10_FSP2_CHIP2_SMP1    0xA34D /* FSM-r4 */

#define FSM10_FSP2_CHIP3         0xA350
#define FSM10_FSP2_CHIP3_CPU1    0xA351
#define FSM10_FSP2_CHIP3_CPU2    0xA352
#define FSM10_FSP2_CHIP3_CPU3    0xA353
#define FSM10_FSP2_CHIP3_CPU4    0xA354
#define FSM10_FSP2_CHIP3_CPU5    0xA355
#define FSM10_FSP2_CHIP3_CPU6    0xA356
#define FSM10_FSP2_CHIP3_CPU7    0xA357
#define FSM10_FSP2_CHIP3_CPU8    0xA358
#define FSM10_FSP2_CHIP3_SMP1    0xA35D /* FSM-r4 */

#define FSM10_FSP2_CHIP4         0xA360
#define FSM10_FSP2_CHIP4_CPU1    0xA361
#define FSM10_FSP2_CHIP4_CPU2    0xA362
#define FSM10_FSP2_CHIP4_CPU3    0xA363
#define FSM10_FSP2_CHIP4_CPU4    0xA364
#define FSM10_FSP2_CHIP4_CPU5    0xA365
#define FSM10_FSP2_CHIP4_CPU6    0xA366
#define FSM10_FSP2_CHIP4_CPU7    0xA367
#define FSM10_FSP2_CHIP4_CPU8    0xA368
#define FSM10_FSP2_CHIP4_SMP1    0xA36D /* FSM-r4 */

#define FSM10_FSP2_CHIP5         0xA370
#define FSM10_FSP2_CHIP5_CPU1    0xA371
#define FSM10_FSP2_CHIP5_CPU2    0xA372
#define FSM10_FSP2_CHIP5_CPU3    0xA373
#define FSM10_FSP2_CHIP5_CPU4    0xA374
#define FSM10_FSP2_CHIP5_CPU5    0xA375
#define FSM10_FSP2_CHIP5_CPU6    0xA376
#define FSM10_FSP2_CHIP5_CPU7    0xA377
#define FSM10_FSP2_CHIP5_CPU8    0xA378

#define FSM10_FSP2_CHIP6         0xA380
#define FSM10_FSP2_CHIP6_CPU1    0xA381
#define FSM10_FSP2_CHIP6_CPU2    0xA382
#define FSM10_FSP2_CHIP6_CPU3    0xA383
#define FSM10_FSP2_CHIP6_CPU4    0xA384
#define FSM10_FSP2_CHIP6_CPU5    0xA385
#define FSM10_FSP2_CHIP6_CPU6    0xA386
#define FSM10_FSP2_CHIP6_CPU7    0xA387
#define FSM10_FSP2_CHIP6_CPU8    0xA388

#define FSM10_FSP2_CHIPALL       0xA3F0

/* FSM10_FSP3 */
#define FSM10_FSP3_MCU           0xA40D
#define FSM10_FSP3_CHIP1         0xA430
#define FSM10_FSP3_CHIP1_CPU1    0xA431
#define FSM10_FSP3_CHIP1_CPU2    0xA432
#define FSM10_FSP3_CHIP1_CPU3    0xA433
#define FSM10_FSP3_CHIP1_CPU4    0xA434
#define FSM10_FSP3_CHIP1_CPU5    0xA435
#define FSM10_FSP3_CHIP1_CPU6    0xA436
#define FSM10_FSP3_CHIP1_CPU7    0xA437
#define FSM10_FSP3_CHIP1_CPU8    0xA438
#define FSM10_FSP3_CHIP1_SMP1    0xA43D /* FSM-r4 */

#define FSM10_FSP3_CHIP2         0xA440
#define FSM10_FSP3_CHIP2_CPU1    0xA441
#define FSM10_FSP3_CHIP2_CPU2    0xA442
#define FSM10_FSP3_CHIP2_CPU3    0xA443
#define FSM10_FSP3_CHIP2_CPU4    0xA444
#define FSM10_FSP3_CHIP2_CPU5    0xA445
#define FSM10_FSP3_CHIP2_CPU6    0xA446
#define FSM10_FSP3_CHIP2_CPU7    0xA447
#define FSM10_FSP3_CHIP2_CPU8    0xA448
#define FSM10_FSP3_CHIP2_SMP1    0xA44D /* FSM-r4 */

#define FSM10_FSP3_CHIP3         0xA450
#define FSM10_FSP3_CHIP3_CPU1    0xA451
#define FSM10_FSP3_CHIP3_CPU2    0xA452
#define FSM10_FSP3_CHIP3_CPU3    0xA453
#define FSM10_FSP3_CHIP3_CPU4    0xA454
#define FSM10_FSP3_CHIP3_CPU5    0xA455
#define FSM10_FSP3_CHIP3_CPU6    0xA456
#define FSM10_FSP3_CHIP3_CPU7    0xA457
#define FSM10_FSP3_CHIP3_CPU8    0xA458
#define FSM10_FSP3_CHIP3_SMP1    0xA45D /* FSM-r4 */

#define FSM10_FSP3_CHIP4         0xA460
#define FSM10_FSP3_CHIP4_CPU1    0xA461
#define FSM10_FSP3_CHIP4_CPU2    0xA462
#define FSM10_FSP3_CHIP4_CPU3    0xA463
#define FSM10_FSP3_CHIP4_CPU4    0xA464
#define FSM10_FSP3_CHIP4_CPU5    0xA465
#define FSM10_FSP3_CHIP4_CPU6    0xA466
#define FSM10_FSP3_CHIP4_CPU7    0xA467
#define FSM10_FSP3_CHIP4_CPU8    0xA468
#define FSM10_FSP3_CHIP4_SMP1    0xA46D /* FSM-r4 */

#define FSM10_FSP3_CHIP5         0xA470
#define FSM10_FSP3_CHIP5_CPU1    0xA471
#define FSM10_FSP3_CHIP5_CPU2    0xA472
#define FSM10_FSP3_CHIP5_CPU3    0xA473
#define FSM10_FSP3_CHIP5_CPU4    0xA474
#define FSM10_FSP3_CHIP5_CPU5    0xA475
#define FSM10_FSP3_CHIP5_CPU6    0xA476
#define FSM10_FSP3_CHIP5_CPU7    0xA477
#define FSM10_FSP3_CHIP5_CPU8    0xA478

#define FSM10_FSP3_CHIP6         0xA480
#define FSM10_FSP3_CHIP6_CPU1    0xA481
#define FSM10_FSP3_CHIP6_CPU2    0xA482
#define FSM10_FSP3_CHIP6_CPU3    0xA483
#define FSM10_FSP3_CHIP6_CPU4    0xA484
#define FSM10_FSP3_CHIP6_CPU5    0xA485
#define FSM10_FSP3_CHIP6_CPU6    0xA486
#define FSM10_FSP3_CHIP6_CPU7    0xA487
#define FSM10_FSP3_CHIP6_CPU8    0xA488

#define FSM10_FSP3_CHIPALL       0xA4F0


/* FSM11_FSP1 */
#define FSM11_FSP1_MCU           0xB20D
#define FSM11_FSP1_CHIP1         0xB230
#define FSM11_FSP1_CHIP1_CPU1    0xB231
#define FSM11_FSP1_CHIP1_CPU2    0xB232
#define FSM11_FSP1_CHIP1_CPU3    0xB233
#define FSM11_FSP1_CHIP1_CPU4    0xB234
#define FSM11_FSP1_CHIP1_CPU5    0xB235
#define FSM11_FSP1_CHIP1_CPU6    0xB236
#define FSM11_FSP1_CHIP1_CPU7    0xB237
#define FSM11_FSP1_CHIP1_CPU8    0xB238
#define FSM11_FSP1_CHIP1_SMP1    0xB23D /* FSM-r4 */

#define FSM11_FSP1_CHIP2         0xB240
#define FSM11_FSP1_CHIP2_CPU1    0xB241
#define FSM11_FSP1_CHIP2_CPU2    0xB242
#define FSM11_FSP1_CHIP2_CPU3    0xB243
#define FSM11_FSP1_CHIP2_CPU4    0xB244
#define FSM11_FSP1_CHIP2_CPU5    0xB245
#define FSM11_FSP1_CHIP2_CPU6    0xB246
#define FSM11_FSP1_CHIP2_CPU7    0xB247
#define FSM11_FSP1_CHIP2_CPU8    0xB248
#define FSM11_FSP1_CHIP2_SMP1    0xB24D /* FSM-r4 */

#define FSM11_FSP1_CHIP3         0xB250
#define FSM11_FSP1_CHIP3_CPU1    0xB251
#define FSM11_FSP1_CHIP3_CPU2    0xB252
#define FSM11_FSP1_CHIP3_CPU3    0xB253
#define FSM11_FSP1_CHIP3_CPU4    0xB254
#define FSM11_FSP1_CHIP3_CPU5    0xB255
#define FSM11_FSP1_CHIP3_CPU6    0xB256
#define FSM11_FSP1_CHIP3_CPU7    0xB257
#define FSM11_FSP1_CHIP3_CPU8    0xB258
#define FSM11_FSP1_CHIP3_SMP1    0xB25D /* FSM-r4 */

#define FSM11_FSP1_CHIP4         0xB260
#define FSM11_FSP1_CHIP4_CPU1    0xB261
#define FSM11_FSP1_CHIP4_CPU2    0xB262
#define FSM11_FSP1_CHIP4_CPU3    0xB263
#define FSM11_FSP1_CHIP4_CPU4    0xB264
#define FSM11_FSP1_CHIP4_CPU5    0xB265
#define FSM11_FSP1_CHIP4_CPU6    0xB266
#define FSM11_FSP1_CHIP4_CPU7    0xB267
#define FSM11_FSP1_CHIP4_CPU8    0xB268
#define FSM11_FSP1_CHIP4_SMP1    0xB26D /* FSM-r4 */

#define FSM11_FSP1_CHIP5         0xB270
#define FSM11_FSP1_CHIP5_CPU1    0xB271
#define FSM11_FSP1_CHIP5_CPU2    0xB272
#define FSM11_FSP1_CHIP5_CPU3    0xB273
#define FSM11_FSP1_CHIP5_CPU4    0xB274
#define FSM11_FSP1_CHIP5_CPU5    0xB275
#define FSM11_FSP1_CHIP5_CPU6    0xB276
#define FSM11_FSP1_CHIP5_CPU7    0xB277
#define FSM11_FSP1_CHIP5_CPU8    0xB278

#define FSM11_FSP1_CHIP6         0xB280
#define FSM11_FSP1_CHIP6_CPU1    0xB281
#define FSM11_FSP1_CHIP6_CPU2    0xB282
#define FSM11_FSP1_CHIP6_CPU3    0xB283
#define FSM11_FSP1_CHIP6_CPU4    0xB284
#define FSM11_FSP1_CHIP6_CPU5    0xB285
#define FSM11_FSP1_CHIP6_CPU6    0xB286
#define FSM11_FSP1_CHIP6_CPU7    0xB287
#define FSM11_FSP1_CHIP6_CPU8    0xB288

#define FSM11_FSP1_CHIPALL       0xB2F0

/* FSM11_FSP2 */
#define FSM11_FSP2_MCU           0xB30D
#define FSM11_FSP2_CHIP1         0xB330
#define FSM11_FSP2_CHIP1_CPU1    0xB331
#define FSM11_FSP2_CHIP1_CPU2    0xB332
#define FSM11_FSP2_CHIP1_CPU3    0xB333
#define FSM11_FSP2_CHIP1_CPU4    0xB334
#define FSM11_FSP2_CHIP1_CPU5    0xB335
#define FSM11_FSP2_CHIP1_CPU6    0xB336
#define FSM11_FSP2_CHIP1_CPU7    0xB337
#define FSM11_FSP2_CHIP1_CPU8    0xB338
#define FSM11_FSP2_CHIP1_SMP1    0xB33D /* FSM-r4 */

#define FSM11_FSP2_CHIP2         0xB340
#define FSM11_FSP2_CHIP2_CPU1    0xB341
#define FSM11_FSP2_CHIP2_CPU2    0xB342
#define FSM11_FSP2_CHIP2_CPU3    0xB343
#define FSM11_FSP2_CHIP2_CPU4    0xB344
#define FSM11_FSP2_CHIP2_CPU5    0xB345
#define FSM11_FSP2_CHIP2_CPU6    0xB346
#define FSM11_FSP2_CHIP2_CPU7    0xB347
#define FSM11_FSP2_CHIP2_CPU8    0xB348
#define FSM11_FSP2_CHIP2_SMP1    0xB34D /* FSM-r4 */

#define FSM11_FSP2_CHIP3         0xB350
#define FSM11_FSP2_CHIP3_CPU1    0xB351
#define FSM11_FSP2_CHIP3_CPU2    0xB352
#define FSM11_FSP2_CHIP3_CPU3    0xB353
#define FSM11_FSP2_CHIP3_CPU4    0xB354
#define FSM11_FSP2_CHIP3_CPU5    0xB355
#define FSM11_FSP2_CHIP3_CPU6    0xB356
#define FSM11_FSP2_CHIP3_CPU7    0xB357
#define FSM11_FSP2_CHIP3_CPU8    0xB358
#define FSM11_FSP2_CHIP3_SMP1    0xB35D /* FSM-r4 */

#define FSM11_FSP2_CHIP4         0xB360
#define FSM11_FSP2_CHIP4_CPU1    0xB361
#define FSM11_FSP2_CHIP4_CPU2    0xB362
#define FSM11_FSP2_CHIP4_CPU3    0xB363
#define FSM11_FSP2_CHIP4_CPU4    0xB364
#define FSM11_FSP2_CHIP4_CPU5    0xB365
#define FSM11_FSP2_CHIP4_CPU6    0xB366
#define FSM11_FSP2_CHIP4_CPU7    0xB367
#define FSM11_FSP2_CHIP4_CPU8    0xB368
#define FSM11_FSP2_CHIP4_SMP1    0xB36D /* FSM-r4 */

#define FSM11_FSP2_CHIP5         0xB370
#define FSM11_FSP2_CHIP5_CPU1    0xB371
#define FSM11_FSP2_CHIP5_CPU2    0xB372
#define FSM11_FSP2_CHIP5_CPU3    0xB373
#define FSM11_FSP2_CHIP5_CPU4    0xB374
#define FSM11_FSP2_CHIP5_CPU5    0xB375
#define FSM11_FSP2_CHIP5_CPU6    0xB376
#define FSM11_FSP2_CHIP5_CPU7    0xB377
#define FSM11_FSP2_CHIP5_CPU8    0xB378

#define FSM11_FSP2_CHIP6         0xB380
#define FSM11_FSP2_CHIP6_CPU1    0xB381
#define FSM11_FSP2_CHIP6_CPU2    0xB382
#define FSM11_FSP2_CHIP6_CPU3    0xB383
#define FSM11_FSP2_CHIP6_CPU4    0xB384
#define FSM11_FSP2_CHIP6_CPU5    0xB385
#define FSM11_FSP2_CHIP6_CPU6    0xB386
#define FSM11_FSP2_CHIP6_CPU7    0xB387
#define FSM11_FSP2_CHIP6_CPU8    0xB388

#define FSM11_FSP2_CHIPALL       0xB3F0

/* FSM11_FSP3 */
#define FSM11_FSP3_MCU           0xB40D
#define FSM11_FSP3_CHIP1         0xB430
#define FSM11_FSP3_CHIP1_CPU1    0xB431
#define FSM11_FSP3_CHIP1_CPU2    0xB432
#define FSM11_FSP3_CHIP1_CPU3    0xB433
#define FSM11_FSP3_CHIP1_CPU4    0xB434
#define FSM11_FSP3_CHIP1_CPU5    0xB435
#define FSM11_FSP3_CHIP1_CPU6    0xB436
#define FSM11_FSP3_CHIP1_CPU7    0xB437
#define FSM11_FSP3_CHIP1_CPU8    0xB438
#define FSM11_FSP3_CHIP1_SMP1    0xB43D /* FSM-r4 */

#define FSM11_FSP3_CHIP2         0xB440
#define FSM11_FSP3_CHIP2_CPU1    0xB441
#define FSM11_FSP3_CHIP2_CPU2    0xB442
#define FSM11_FSP3_CHIP2_CPU3    0xB443
#define FSM11_FSP3_CHIP2_CPU4    0xB444
#define FSM11_FSP3_CHIP2_CPU5    0xB445
#define FSM11_FSP3_CHIP2_CPU6    0xB446
#define FSM11_FSP3_CHIP2_CPU7    0xB447
#define FSM11_FSP3_CHIP2_CPU8    0xB448
#define FSM11_FSP3_CHIP2_SMP1    0xB44D /* FSM-r4 */

#define FSM11_FSP3_CHIP3         0xB450
#define FSM11_FSP3_CHIP3_CPU1    0xB451
#define FSM11_FSP3_CHIP3_CPU2    0xB452
#define FSM11_FSP3_CHIP3_CPU3    0xB453
#define FSM11_FSP3_CHIP3_CPU4    0xB454
#define FSM11_FSP3_CHIP3_CPU5    0xB455
#define FSM11_FSP3_CHIP3_CPU6    0xB456
#define FSM11_FSP3_CHIP3_CPU7    0xB457
#define FSM11_FSP3_CHIP3_CPU8    0xB458
#define FSM11_FSP3_CHIP3_SMP1    0xB45D /* FSM-r4 */

#define FSM11_FSP3_CHIP4         0xB460
#define FSM11_FSP3_CHIP4_CPU1    0xB461
#define FSM11_FSP3_CHIP4_CPU2    0xB462
#define FSM11_FSP3_CHIP4_CPU3    0xB463
#define FSM11_FSP3_CHIP4_CPU4    0xB464
#define FSM11_FSP3_CHIP4_CPU5    0xB465
#define FSM11_FSP3_CHIP4_CPU6    0xB466
#define FSM11_FSP3_CHIP4_CPU7    0xB467
#define FSM11_FSP3_CHIP4_CPU8    0xB468
#define FSM11_FSP3_CHIP4_SMP1    0xB46D /* FSM-r4 */

#define FSM11_FSP3_CHIP5         0xB470
#define FSM11_FSP3_CHIP5_CPU1    0xB471
#define FSM11_FSP3_CHIP5_CPU2    0xB472
#define FSM11_FSP3_CHIP5_CPU3    0xB473
#define FSM11_FSP3_CHIP5_CPU4    0xB474
#define FSM11_FSP3_CHIP5_CPU5    0xB475
#define FSM11_FSP3_CHIP5_CPU6    0xB476
#define FSM11_FSP3_CHIP5_CPU7    0xB477
#define FSM11_FSP3_CHIP5_CPU8    0xB478

#define FSM11_FSP3_CHIP6         0xB480
#define FSM11_FSP3_CHIP6_CPU1    0xB481
#define FSM11_FSP3_CHIP6_CPU2    0xB482
#define FSM11_FSP3_CHIP6_CPU3    0xB483
#define FSM11_FSP3_CHIP6_CPU4    0xB484
#define FSM11_FSP3_CHIP6_CPU5    0xB485
#define FSM11_FSP3_CHIP6_CPU6    0xB486
#define FSM11_FSP3_CHIP6_CPU7    0xB487
#define FSM11_FSP3_CHIP6_CPU8    0xB488

#define FSM11_FSP3_CHIPALL       0xB4F0


/* FSM12_FSP1 */
#define FSM12_FSP1_MCU           0xC20D
#define FSM12_FSP1_CHIP1         0xC230
#define FSM12_FSP1_CHIP1_CPU1    0xC231
#define FSM12_FSP1_CHIP1_CPU2    0xC232
#define FSM12_FSP1_CHIP1_CPU3    0xC233
#define FSM12_FSP1_CHIP1_CPU4    0xC234
#define FSM12_FSP1_CHIP1_CPU5    0xC235
#define FSM12_FSP1_CHIP1_CPU6    0xC236
#define FSM12_FSP1_CHIP1_CPU7    0xC237
#define FSM12_FSP1_CHIP1_CPU8    0xC238
#define FSM12_FSP1_CHIP1_SMP1    0xC23D /* FSM-r4 */

#define FSM12_FSP1_CHIP2         0xC240
#define FSM12_FSP1_CHIP2_CPU1    0xC241
#define FSM12_FSP1_CHIP2_CPU2    0xC242
#define FSM12_FSP1_CHIP2_CPU3    0xC243
#define FSM12_FSP1_CHIP2_CPU4    0xC244
#define FSM12_FSP1_CHIP2_CPU5    0xC245
#define FSM12_FSP1_CHIP2_CPU6    0xC246
#define FSM12_FSP1_CHIP2_CPU7    0xC247
#define FSM12_FSP1_CHIP2_CPU8    0xC248
#define FSM12_FSP1_CHIP2_SMP1    0xC24D /* FSM-r4 */

#define FSM12_FSP1_CHIP3         0xC250
#define FSM12_FSP1_CHIP3_CPU1    0xC251
#define FSM12_FSP1_CHIP3_CPU2    0xC252
#define FSM12_FSP1_CHIP3_CPU3    0xC253
#define FSM12_FSP1_CHIP3_CPU4    0xC254
#define FSM12_FSP1_CHIP3_CPU5    0xC255
#define FSM12_FSP1_CHIP3_CPU6    0xC256
#define FSM12_FSP1_CHIP3_CPU7    0xC257
#define FSM12_FSP1_CHIP3_CPU8    0xC258
#define FSM12_FSP1_CHIP3_SMP1    0xC25D /* FSM-r4 */

#define FSM12_FSP1_CHIP4         0xC260
#define FSM12_FSP1_CHIP4_CPU1    0xC261
#define FSM12_FSP1_CHIP4_CPU2    0xC262
#define FSM12_FSP1_CHIP4_CPU3    0xC263
#define FSM12_FSP1_CHIP4_CPU4    0xC264
#define FSM12_FSP1_CHIP4_CPU5    0xC265
#define FSM12_FSP1_CHIP4_CPU6    0xC266
#define FSM12_FSP1_CHIP4_CPU7    0xC267
#define FSM12_FSP1_CHIP4_CPU8    0xC268
#define FSM12_FSP1_CHIP4_SMP1    0xC26D /* FSM-r4 */

#define FSM12_FSP1_CHIP5         0xC270
#define FSM12_FSP1_CHIP5_CPU1    0xC271
#define FSM12_FSP1_CHIP5_CPU2    0xC272
#define FSM12_FSP1_CHIP5_CPU3    0xC273
#define FSM12_FSP1_CHIP5_CPU4    0xC274
#define FSM12_FSP1_CHIP5_CPU5    0xC275
#define FSM12_FSP1_CHIP5_CPU6    0xC276
#define FSM12_FSP1_CHIP5_CPU7    0xC277
#define FSM12_FSP1_CHIP5_CPU8    0xC278

#define FSM12_FSP1_CHIP6         0xC280
#define FSM12_FSP1_CHIP6_CPU1    0xC281
#define FSM12_FSP1_CHIP6_CPU2    0xC282
#define FSM12_FSP1_CHIP6_CPU3    0xC283
#define FSM12_FSP1_CHIP6_CPU4    0xC284
#define FSM12_FSP1_CHIP6_CPU5    0xC285
#define FSM12_FSP1_CHIP6_CPU6    0xC286
#define FSM12_FSP1_CHIP6_CPU7    0xC287
#define FSM12_FSP1_CHIP6_CPU8    0xC288

#define FSM12_FSP1_CHIPALL       0xC2F0

/* FSM12_FSP2 */
#define FSM12_FSP2_MCU           0xC30D
#define FSM12_FSP2_CHIP1         0xC330
#define FSM12_FSP2_CHIP1_CPU1    0xC331
#define FSM12_FSP2_CHIP1_CPU2    0xC332
#define FSM12_FSP2_CHIP1_CPU3    0xC333
#define FSM12_FSP2_CHIP1_CPU4    0xC334
#define FSM12_FSP2_CHIP1_CPU5    0xC335
#define FSM12_FSP2_CHIP1_CPU6    0xC336
#define FSM12_FSP2_CHIP1_CPU7    0xC337
#define FSM12_FSP2_CHIP1_CPU8    0xC338
#define FSM12_FSP2_CHIP1_SMP1    0xC33D /* FSM-r4 */

#define FSM12_FSP2_CHIP2         0xC340
#define FSM12_FSP2_CHIP2_CPU1    0xC341
#define FSM12_FSP2_CHIP2_CPU2    0xC342
#define FSM12_FSP2_CHIP2_CPU3    0xC343
#define FSM12_FSP2_CHIP2_CPU4    0xC344
#define FSM12_FSP2_CHIP2_CPU5    0xC345
#define FSM12_FSP2_CHIP2_CPU6    0xC346
#define FSM12_FSP2_CHIP2_CPU7    0xC347
#define FSM12_FSP2_CHIP2_CPU8    0xC348
#define FSM12_FSP2_CHIP2_SMP1    0xC34D /* FSM-r4 */

#define FSM12_FSP2_CHIP3         0xC350
#define FSM12_FSP2_CHIP3_CPU1    0xC351
#define FSM12_FSP2_CHIP3_CPU2    0xC352
#define FSM12_FSP2_CHIP3_CPU3    0xC353
#define FSM12_FSP2_CHIP3_CPU4    0xC354
#define FSM12_FSP2_CHIP3_CPU5    0xC355
#define FSM12_FSP2_CHIP3_CPU6    0xC356
#define FSM12_FSP2_CHIP3_CPU7    0xC357
#define FSM12_FSP2_CHIP3_CPU8    0xC358
#define FSM12_FSP2_CHIP3_SMP1    0xC35D /* FSM-r4 */

#define FSM12_FSP2_CHIP4         0xC360
#define FSM12_FSP2_CHIP4_CPU1    0xC361
#define FSM12_FSP2_CHIP4_CPU2    0xC362
#define FSM12_FSP2_CHIP4_CPU3    0xC363
#define FSM12_FSP2_CHIP4_CPU4    0xC364
#define FSM12_FSP2_CHIP4_CPU5    0xC365
#define FSM12_FSP2_CHIP4_CPU6    0xC366
#define FSM12_FSP2_CHIP4_CPU7    0xC367
#define FSM12_FSP2_CHIP4_CPU8    0xC368
#define FSM12_FSP2_CHIP4_SMP1    0xC36D /* FSM-r4 */

#define FSM12_FSP2_CHIP5         0xC370
#define FSM12_FSP2_CHIP5_CPU1    0xC371
#define FSM12_FSP2_CHIP5_CPU2    0xC372
#define FSM12_FSP2_CHIP5_CPU3    0xC373
#define FSM12_FSP2_CHIP5_CPU4    0xC374
#define FSM12_FSP2_CHIP5_CPU5    0xC375
#define FSM12_FSP2_CHIP5_CPU6    0xC376
#define FSM12_FSP2_CHIP5_CPU7    0xC377
#define FSM12_FSP2_CHIP5_CPU8    0xC378

#define FSM12_FSP2_CHIP6         0xC380
#define FSM12_FSP2_CHIP6_CPU1    0xC381
#define FSM12_FSP2_CHIP6_CPU2    0xC382
#define FSM12_FSP2_CHIP6_CPU3    0xC383
#define FSM12_FSP2_CHIP6_CPU4    0xC384
#define FSM12_FSP2_CHIP6_CPU5    0xC385
#define FSM12_FSP2_CHIP6_CPU6    0xC386
#define FSM12_FSP2_CHIP6_CPU7    0xC387
#define FSM12_FSP2_CHIP6_CPU8    0xC388

#define FSM12_FSP2_CHIPALL       0xC3F0

/* FSM12_FSP3 */
#define FSM12_FSP3_MCU           0xC40D
#define FSM12_FSP3_CHIP1         0xC430
#define FSM12_FSP3_CHIP1_CPU1    0xC431
#define FSM12_FSP3_CHIP1_CPU2    0xC432
#define FSM12_FSP3_CHIP1_CPU3    0xC433
#define FSM12_FSP3_CHIP1_CPU4    0xC434
#define FSM12_FSP3_CHIP1_CPU5    0xC435
#define FSM12_FSP3_CHIP1_CPU6    0xC436
#define FSM12_FSP3_CHIP1_CPU7    0xC437
#define FSM12_FSP3_CHIP1_CPU8    0xC438
#define FSM12_FSP3_CHIP1_SMP1    0xC43D /* FSM-r4 */

#define FSM12_FSP3_CHIP2         0xC440
#define FSM12_FSP3_CHIP2_CPU1    0xC441
#define FSM12_FSP3_CHIP2_CPU2    0xC442
#define FSM12_FSP3_CHIP2_CPU3    0xC443
#define FSM12_FSP3_CHIP2_CPU4    0xC444
#define FSM12_FSP3_CHIP2_CPU5    0xC445
#define FSM12_FSP3_CHIP2_CPU6    0xC446
#define FSM12_FSP3_CHIP2_CPU7    0xC447
#define FSM12_FSP3_CHIP2_CPU8    0xC448
#define FSM12_FSP3_CHIP2_SMP1    0xC44D /* FSM-r4 */

#define FSM12_FSP3_CHIP3         0xC450
#define FSM12_FSP3_CHIP3_CPU1    0xC451
#define FSM12_FSP3_CHIP3_CPU2    0xC452
#define FSM12_FSP3_CHIP3_CPU3    0xC453
#define FSM12_FSP3_CHIP3_CPU4    0xC454
#define FSM12_FSP3_CHIP3_CPU5    0xC455
#define FSM12_FSP3_CHIP3_CPU6    0xC456
#define FSM12_FSP3_CHIP3_CPU7    0xC457
#define FSM12_FSP3_CHIP3_CPU8    0xC458
#define FSM12_FSP3_CHIP3_SMP1    0xC45D /* FSM-r4 */

#define FSM12_FSP3_CHIP4         0xC460
#define FSM12_FSP3_CHIP4_CPU1    0xC461
#define FSM12_FSP3_CHIP4_CPU2    0xC462
#define FSM12_FSP3_CHIP4_CPU3    0xC463
#define FSM12_FSP3_CHIP4_CPU4    0xC464
#define FSM12_FSP3_CHIP4_CPU5    0xC465
#define FSM12_FSP3_CHIP4_CPU6    0xC466
#define FSM12_FSP3_CHIP4_CPU7    0xC467
#define FSM12_FSP3_CHIP4_CPU8    0xC468
#define FSM12_FSP3_CHIP4_SMP1    0xC46D /* FSM-r4 */

#define FSM12_FSP3_CHIP5         0xC470
#define FSM12_FSP3_CHIP5_CPU1    0xC471
#define FSM12_FSP3_CHIP5_CPU2    0xC472
#define FSM12_FSP3_CHIP5_CPU3    0xC473
#define FSM12_FSP3_CHIP5_CPU4    0xC474
#define FSM12_FSP3_CHIP5_CPU5    0xC475
#define FSM12_FSP3_CHIP5_CPU6    0xC476
#define FSM12_FSP3_CHIP5_CPU7    0xC477
#define FSM12_FSP3_CHIP5_CPU8    0xC478

#define FSM12_FSP3_CHIP6         0xC480
#define FSM12_FSP3_CHIP6_CPU1    0xC481
#define FSM12_FSP3_CHIP6_CPU2    0xC482
#define FSM12_FSP3_CHIP6_CPU3    0xC483
#define FSM12_FSP3_CHIP6_CPU4    0xC484
#define FSM12_FSP3_CHIP6_CPU5    0xC485
#define FSM12_FSP3_CHIP6_CPU6    0xC486
#define FSM12_FSP3_CHIP6_CPU7    0xC487
#define FSM12_FSP3_CHIP6_CPU8    0xC488

#define FSM12_FSP3_CHIPALL       0xC4F0


/* FSM13_FSP1 */
#define FSM13_FSP1_MCU           0xD20D
#define FSM13_FSP1_CHIP1         0xD230
#define FSM13_FSP1_CHIP1_CPU1    0xD231
#define FSM13_FSP1_CHIP1_CPU2    0xD232
#define FSM13_FSP1_CHIP1_CPU3    0xD233
#define FSM13_FSP1_CHIP1_CPU4    0xD234
#define FSM13_FSP1_CHIP1_CPU5    0xD235
#define FSM13_FSP1_CHIP1_CPU6    0xD236
#define FSM13_FSP1_CHIP1_CPU7    0xD237
#define FSM13_FSP1_CHIP1_CPU8    0xD238
#define FSM13_FSP1_CHIP1_SMP1    0xD23D /* FSM-r4 */

#define FSM13_FSP1_CHIP2         0xD240
#define FSM13_FSP1_CHIP2_CPU1    0xD241
#define FSM13_FSP1_CHIP2_CPU2    0xD242
#define FSM13_FSP1_CHIP2_CPU3    0xD243
#define FSM13_FSP1_CHIP2_CPU4    0xD244
#define FSM13_FSP1_CHIP2_CPU5    0xD245
#define FSM13_FSP1_CHIP2_CPU6    0xD246
#define FSM13_FSP1_CHIP2_CPU7    0xD247
#define FSM13_FSP1_CHIP2_CPU8    0xD248
#define FSM13_FSP1_CHIP2_SMP1    0xD24D /* FSM-r4 */

#define FSM13_FSP1_CHIP3         0xD250
#define FSM13_FSP1_CHIP3_CPU1    0xD251
#define FSM13_FSP1_CHIP3_CPU2    0xD252
#define FSM13_FSP1_CHIP3_CPU3    0xD253
#define FSM13_FSP1_CHIP3_CPU4    0xD254
#define FSM13_FSP1_CHIP3_CPU5    0xD255
#define FSM13_FSP1_CHIP3_CPU6    0xD256
#define FSM13_FSP1_CHIP3_CPU7    0xD257
#define FSM13_FSP1_CHIP3_CPU8    0xD258
#define FSM13_FSP1_CHIP3_SMP1    0xD25D /* FSM-r4 */

#define FSM13_FSP1_CHIP4         0xD260
#define FSM13_FSP1_CHIP4_CPU1    0xD261
#define FSM13_FSP1_CHIP4_CPU2    0xD262
#define FSM13_FSP1_CHIP4_CPU3    0xD263
#define FSM13_FSP1_CHIP4_CPU4    0xD264
#define FSM13_FSP1_CHIP4_CPU5    0xD265
#define FSM13_FSP1_CHIP4_CPU6    0xD266
#define FSM13_FSP1_CHIP4_CPU7    0xD267
#define FSM13_FSP1_CHIP4_CPU8    0xD268
#define FSM13_FSP1_CHIP4_SMP1    0xD26D /* FSM-r4 */

#define FSM13_FSP1_CHIP5         0xD270
#define FSM13_FSP1_CHIP5_CPU1    0xD271
#define FSM13_FSP1_CHIP5_CPU2    0xD272
#define FSM13_FSP1_CHIP5_CPU3    0xD273
#define FSM13_FSP1_CHIP5_CPU4    0xD274
#define FSM13_FSP1_CHIP5_CPU5    0xD275
#define FSM13_FSP1_CHIP5_CPU6    0xD276
#define FSM13_FSP1_CHIP5_CPU7    0xD277
#define FSM13_FSP1_CHIP5_CPU8    0xD278

#define FSM13_FSP1_CHIP6         0xD280
#define FSM13_FSP1_CHIP6_CPU1    0xD281
#define FSM13_FSP1_CHIP6_CPU2    0xD282
#define FSM13_FSP1_CHIP6_CPU3    0xD283
#define FSM13_FSP1_CHIP6_CPU4    0xD284
#define FSM13_FSP1_CHIP6_CPU5    0xD285
#define FSM13_FSP1_CHIP6_CPU6    0xD286
#define FSM13_FSP1_CHIP6_CPU7    0xD287
#define FSM13_FSP1_CHIP6_CPU8    0xD288

#define FSM13_FSP1_CHIPALL       0xD2F0

/* FSM13_FSP2 */
#define FSM13_FSP2_MCU           0xD30D
#define FSM13_FSP2_CHIP1         0xD330
#define FSM13_FSP2_CHIP1_CPU1    0xD331
#define FSM13_FSP2_CHIP1_CPU2    0xD332
#define FSM13_FSP2_CHIP1_CPU3    0xD333
#define FSM13_FSP2_CHIP1_CPU4    0xD334
#define FSM13_FSP2_CHIP1_CPU5    0xD335
#define FSM13_FSP2_CHIP1_CPU6    0xD336
#define FSM13_FSP2_CHIP1_CPU7    0xD337
#define FSM13_FSP2_CHIP1_CPU8    0xD338
#define FSM13_FSP2_CHIP1_SMP1    0xD33D /* FSM-r4 */

#define FSM13_FSP2_CHIP2         0xD340
#define FSM13_FSP2_CHIP2_CPU1    0xD341
#define FSM13_FSP2_CHIP2_CPU2    0xD342
#define FSM13_FSP2_CHIP2_CPU3    0xD343
#define FSM13_FSP2_CHIP2_CPU4    0xD344
#define FSM13_FSP2_CHIP2_CPU5    0xD345
#define FSM13_FSP2_CHIP2_CPU6    0xD346
#define FSM13_FSP2_CHIP2_CPU7    0xD347
#define FSM13_FSP2_CHIP2_CPU8    0xD348
#define FSM13_FSP2_CHIP2_SMP1    0xD34D /* FSM-r4 */

#define FSM13_FSP2_CHIP3         0xD350
#define FSM13_FSP2_CHIP3_CPU1    0xD351
#define FSM13_FSP2_CHIP3_CPU2    0xD352
#define FSM13_FSP2_CHIP3_CPU3    0xD353
#define FSM13_FSP2_CHIP3_CPU4    0xD354
#define FSM13_FSP2_CHIP3_CPU5    0xD355
#define FSM13_FSP2_CHIP3_CPU6    0xD356
#define FSM13_FSP2_CHIP3_CPU7    0xD357
#define FSM13_FSP2_CHIP3_CPU8    0xD358
#define FSM13_FSP2_CHIP3_SMP1    0xD35D /* FSM-r4 */

#define FSM13_FSP2_CHIP4         0xD360
#define FSM13_FSP2_CHIP4_CPU1    0xD361
#define FSM13_FSP2_CHIP4_CPU2    0xD362
#define FSM13_FSP2_CHIP4_CPU3    0xD363
#define FSM13_FSP2_CHIP4_CPU4    0xD364
#define FSM13_FSP2_CHIP4_CPU5    0xD365
#define FSM13_FSP2_CHIP4_CPU6    0xD366
#define FSM13_FSP2_CHIP4_CPU7    0xD367
#define FSM13_FSP2_CHIP4_CPU8    0xD368
#define FSM13_FSP2_CHIP4_SMP1    0xD36D /* FSM-r4 */

#define FSM13_FSP2_CHIP5         0xD370
#define FSM13_FSP2_CHIP5_CPU1    0xD371
#define FSM13_FSP2_CHIP5_CPU2    0xD372
#define FSM13_FSP2_CHIP5_CPU3    0xD373
#define FSM13_FSP2_CHIP5_CPU4    0xD374
#define FSM13_FSP2_CHIP5_CPU5    0xD375
#define FSM13_FSP2_CHIP5_CPU6    0xD376
#define FSM13_FSP2_CHIP5_CPU7    0xD377
#define FSM13_FSP2_CHIP5_CPU8    0xD378

#define FSM13_FSP2_CHIP6         0xD380
#define FSM13_FSP2_CHIP6_CPU1    0xD381
#define FSM13_FSP2_CHIP6_CPU2    0xD382
#define FSM13_FSP2_CHIP6_CPU3    0xD383
#define FSM13_FSP2_CHIP6_CPU4    0xD384
#define FSM13_FSP2_CHIP6_CPU5    0xD385
#define FSM13_FSP2_CHIP6_CPU6    0xD386
#define FSM13_FSP2_CHIP6_CPU7    0xD387
#define FSM13_FSP2_CHIP6_CPU8    0xD388

#define FSM13_FSP2_CHIPALL       0xD3F0

/* FSM13_FSP3 */
#define FSM13_FSP3_MCU           0xD40D
#define FSM13_FSP3_CHIP1         0xD430
#define FSM13_FSP3_CHIP1_CPU1    0xD431
#define FSM13_FSP3_CHIP1_CPU2    0xD432
#define FSM13_FSP3_CHIP1_CPU3    0xD433
#define FSM13_FSP3_CHIP1_CPU4    0xD434
#define FSM13_FSP3_CHIP1_CPU5    0xD435
#define FSM13_FSP3_CHIP1_CPU6    0xD436
#define FSM13_FSP3_CHIP1_CPU7    0xD437
#define FSM13_FSP3_CHIP1_CPU8    0xD438
#define FSM13_FSP3_CHIP1_SMP1    0xD43D /* FSM-r4 */

#define FSM13_FSP3_CHIP2         0xD440
#define FSM13_FSP3_CHIP2_CPU1    0xD441
#define FSM13_FSP3_CHIP2_CPU2    0xD442
#define FSM13_FSP3_CHIP2_CPU3    0xD443
#define FSM13_FSP3_CHIP2_CPU4    0xD444
#define FSM13_FSP3_CHIP2_CPU5    0xD445
#define FSM13_FSP3_CHIP2_CPU6    0xD446
#define FSM13_FSP3_CHIP2_CPU7    0xD447
#define FSM13_FSP3_CHIP2_CPU8    0xD448
#define FSM13_FSP3_CHIP2_SMP1    0xD44D /* FSM-r4 */

#define FSM13_FSP3_CHIP3         0xD450
#define FSM13_FSP3_CHIP3_CPU1    0xD451
#define FSM13_FSP3_CHIP3_CPU2    0xD452
#define FSM13_FSP3_CHIP3_CPU3    0xD453
#define FSM13_FSP3_CHIP3_CPU4    0xD454
#define FSM13_FSP3_CHIP3_CPU5    0xD455
#define FSM13_FSP3_CHIP3_CPU6    0xD456
#define FSM13_FSP3_CHIP3_CPU7    0xD457
#define FSM13_FSP3_CHIP3_CPU8    0xD458
#define FSM13_FSP3_CHIP3_SMP1    0xD45D /* FSM-r4 */

#define FSM13_FSP3_CHIP4         0xD460
#define FSM13_FSP3_CHIP4_CPU1    0xD461
#define FSM13_FSP3_CHIP4_CPU2    0xD462
#define FSM13_FSP3_CHIP4_CPU3    0xD463
#define FSM13_FSP3_CHIP4_CPU4    0xD464
#define FSM13_FSP3_CHIP4_CPU5    0xD465
#define FSM13_FSP3_CHIP4_CPU6    0xD466
#define FSM13_FSP3_CHIP4_CPU7    0xD467
#define FSM13_FSP3_CHIP4_CPU8    0xD468
#define FSM13_FSP3_CHIP4_SMP1    0xD46D /* FSM-r4 */

#define FSM13_FSP3_CHIP5         0xD470
#define FSM13_FSP3_CHIP5_CPU1    0xD471
#define FSM13_FSP3_CHIP5_CPU2    0xD472
#define FSM13_FSP3_CHIP5_CPU3    0xD473
#define FSM13_FSP3_CHIP5_CPU4    0xD474
#define FSM13_FSP3_CHIP5_CPU5    0xD475
#define FSM13_FSP3_CHIP5_CPU6    0xD476
#define FSM13_FSP3_CHIP5_CPU7    0xD477
#define FSM13_FSP3_CHIP5_CPU8    0xD478

#define FSM13_FSP3_CHIP6         0xD480
#define FSM13_FSP3_CHIP6_CPU1    0xD481
#define FSM13_FSP3_CHIP6_CPU2    0xD482
#define FSM13_FSP3_CHIP6_CPU3    0xD483
#define FSM13_FSP3_CHIP6_CPU4    0xD484
#define FSM13_FSP3_CHIP6_CPU5    0xD485
#define FSM13_FSP3_CHIP6_CPU6    0xD486
#define FSM13_FSP3_CHIP6_CPU7    0xD487
#define FSM13_FSP3_CHIP6_CPU8    0xD488

#define FSM13_FSP3_CHIPALL       0xD4F0


/* FSM14_FSP1 */
#define FSM14_FSP1_MCU           0xE20D
#define FSM14_FSP1_CHIP1         0xE230
#define FSM14_FSP1_CHIP1_CPU1    0xE231
#define FSM14_FSP1_CHIP1_CPU2    0xE232
#define FSM14_FSP1_CHIP1_CPU3    0xE233
#define FSM14_FSP1_CHIP1_CPU4    0xE234
#define FSM14_FSP1_CHIP1_CPU5    0xE235
#define FSM14_FSP1_CHIP1_CPU6    0xE236
#define FSM14_FSP1_CHIP1_CPU7    0xE237
#define FSM14_FSP1_CHIP1_CPU8    0xE238
#define FSM14_FSP1_CHIP1_SMP1    0xE23D /* FSM-r4 */

#define FSM14_FSP1_CHIP2         0xE240
#define FSM14_FSP1_CHIP2_CPU1    0xE241
#define FSM14_FSP1_CHIP2_CPU2    0xE242
#define FSM14_FSP1_CHIP2_CPU3    0xE243
#define FSM14_FSP1_CHIP2_CPU4    0xE244
#define FSM14_FSP1_CHIP2_CPU5    0xE245
#define FSM14_FSP1_CHIP2_CPU6    0xE246
#define FSM14_FSP1_CHIP2_CPU7    0xE247
#define FSM14_FSP1_CHIP2_CPU8    0xE248
#define FSM14_FSP1_CHIP2_SMP1    0xE24D /* FSM-r4 */

#define FSM14_FSP1_CHIP3         0xE250
#define FSM14_FSP1_CHIP3_CPU1    0xE251
#define FSM14_FSP1_CHIP3_CPU2    0xE252
#define FSM14_FSP1_CHIP3_CPU3    0xE253
#define FSM14_FSP1_CHIP3_CPU4    0xE254
#define FSM14_FSP1_CHIP3_CPU5    0xE255
#define FSM14_FSP1_CHIP3_CPU6    0xE256
#define FSM14_FSP1_CHIP3_CPU7    0xE257
#define FSM14_FSP1_CHIP3_CPU8    0xE258
#define FSM14_FSP1_CHIP3_SMP1    0xE25D /* FSM-r4 */

#define FSM14_FSP1_CHIP4         0xE260
#define FSM14_FSP1_CHIP4_CPU1    0xE261
#define FSM14_FSP1_CHIP4_CPU2    0xE262
#define FSM14_FSP1_CHIP4_CPU3    0xE263
#define FSM14_FSP1_CHIP4_CPU4    0xE264
#define FSM14_FSP1_CHIP4_CPU5    0xE265
#define FSM14_FSP1_CHIP4_CPU6    0xE266
#define FSM14_FSP1_CHIP4_CPU7    0xE267
#define FSM14_FSP1_CHIP4_CPU8    0xE268
#define FSM14_FSP1_CHIP4_SMP1    0xE26D /* FSM-r4 */

#define FSM14_FSP1_CHIP5         0xE270
#define FSM14_FSP1_CHIP5_CPU1    0xE271
#define FSM14_FSP1_CHIP5_CPU2    0xE272
#define FSM14_FSP1_CHIP5_CPU3    0xE273
#define FSM14_FSP1_CHIP5_CPU4    0xE274
#define FSM14_FSP1_CHIP5_CPU5    0xE275
#define FSM14_FSP1_CHIP5_CPU6    0xE276
#define FSM14_FSP1_CHIP5_CPU7    0xE277
#define FSM14_FSP1_CHIP5_CPU8    0xE278

#define FSM14_FSP1_CHIP6         0xE280
#define FSM14_FSP1_CHIP6_CPU1    0xE281
#define FSM14_FSP1_CHIP6_CPU2    0xE282
#define FSM14_FSP1_CHIP6_CPU3    0xE283
#define FSM14_FSP1_CHIP6_CPU4    0xE284
#define FSM14_FSP1_CHIP6_CPU5    0xE285
#define FSM14_FSP1_CHIP6_CPU6    0xE286
#define FSM14_FSP1_CHIP6_CPU7    0xE287
#define FSM14_FSP1_CHIP6_CPU8    0xE288

#define FSM14_FSP1_CHIPALL       0xE2F0

/* FSM14_FSP2 */
#define FSM14_FSP2_MCU           0xE30D
#define FSM14_FSP2_CHIP1         0xE330
#define FSM14_FSP2_CHIP1_CPU1    0xE331
#define FSM14_FSP2_CHIP1_CPU2    0xE332
#define FSM14_FSP2_CHIP1_CPU3    0xE333
#define FSM14_FSP2_CHIP1_CPU4    0xE334
#define FSM14_FSP2_CHIP1_CPU5    0xE335
#define FSM14_FSP2_CHIP1_CPU6    0xE336
#define FSM14_FSP2_CHIP1_CPU7    0xE337
#define FSM14_FSP2_CHIP1_CPU8    0xE338
#define FSM14_FSP2_CHIP1_SMP1    0xE33D /* FSM-r4 */

#define FSM14_FSP2_CHIP2         0xE340
#define FSM14_FSP2_CHIP2_CPU1    0xE341
#define FSM14_FSP2_CHIP2_CPU2    0xE342
#define FSM14_FSP2_CHIP2_CPU3    0xE343
#define FSM14_FSP2_CHIP2_CPU4    0xE344
#define FSM14_FSP2_CHIP2_CPU5    0xE345
#define FSM14_FSP2_CHIP2_CPU6    0xE346
#define FSM14_FSP2_CHIP2_CPU7    0xE347
#define FSM14_FSP2_CHIP2_CPU8    0xE348
#define FSM14_FSP2_CHIP2_SMP1    0xE34D /* FSM-r4 */

#define FSM14_FSP2_CHIP3         0xE350
#define FSM14_FSP2_CHIP3_CPU1    0xE351
#define FSM14_FSP2_CHIP3_CPU2    0xE352
#define FSM14_FSP2_CHIP3_CPU3    0xE353
#define FSM14_FSP2_CHIP3_CPU4    0xE354
#define FSM14_FSP2_CHIP3_CPU5    0xE355
#define FSM14_FSP2_CHIP3_CPU6    0xE356
#define FSM14_FSP2_CHIP3_CPU7    0xE357
#define FSM14_FSP2_CHIP3_CPU8    0xE358
#define FSM14_FSP2_CHIP3_SMP1    0xE35D /* FSM-r4 */

#define FSM14_FSP2_CHIP4         0xE360
#define FSM14_FSP2_CHIP4_CPU1    0xE361
#define FSM14_FSP2_CHIP4_CPU2    0xE362
#define FSM14_FSP2_CHIP4_CPU3    0xE363
#define FSM14_FSP2_CHIP4_CPU4    0xE364
#define FSM14_FSP2_CHIP4_CPU5    0xE365
#define FSM14_FSP2_CHIP4_CPU6    0xE366
#define FSM14_FSP2_CHIP4_CPU7    0xE367
#define FSM14_FSP2_CHIP4_CPU8    0xE368
#define FSM14_FSP2_CHIP4_SMP1    0xE36D /* FSM-r4 */

#define FSM14_FSP2_CHIP5         0xE370
#define FSM14_FSP2_CHIP5_CPU1    0xE371
#define FSM14_FSP2_CHIP5_CPU2    0xE372
#define FSM14_FSP2_CHIP5_CPU3    0xE373
#define FSM14_FSP2_CHIP5_CPU4    0xE374
#define FSM14_FSP2_CHIP5_CPU5    0xE375
#define FSM14_FSP2_CHIP5_CPU6    0xE376
#define FSM14_FSP2_CHIP5_CPU7    0xE377
#define FSM14_FSP2_CHIP5_CPU8    0xE378

#define FSM14_FSP2_CHIP6         0xE380
#define FSM14_FSP2_CHIP6_CPU1    0xE381
#define FSM14_FSP2_CHIP6_CPU2    0xE382
#define FSM14_FSP2_CHIP6_CPU3    0xE383
#define FSM14_FSP2_CHIP6_CPU4    0xE384
#define FSM14_FSP2_CHIP6_CPU5    0xE385
#define FSM14_FSP2_CHIP6_CPU6    0xE386
#define FSM14_FSP2_CHIP6_CPU7    0xE387
#define FSM14_FSP2_CHIP6_CPU8    0xE388

#define FSM14_FSP2_CHIPALL       0xE3F0

/* FSM14_FSP3 */
#define FSM14_FSP3_MCU           0xE40D
#define FSM14_FSP3_CHIP1         0xE430
#define FSM14_FSP3_CHIP1_CPU1    0xE431
#define FSM14_FSP3_CHIP1_CPU2    0xE432
#define FSM14_FSP3_CHIP1_CPU3    0xE433
#define FSM14_FSP3_CHIP1_CPU4    0xE434
#define FSM14_FSP3_CHIP1_CPU5    0xE435
#define FSM14_FSP3_CHIP1_CPU6    0xE436
#define FSM14_FSP3_CHIP1_CPU7    0xE437
#define FSM14_FSP3_CHIP1_CPU8    0xE438
#define FSM14_FSP3_CHIP1_SMP1    0xE43D /* FSM-r4 */

#define FSM14_FSP3_CHIP2         0xE440
#define FSM14_FSP3_CHIP2_CPU1    0xE441
#define FSM14_FSP3_CHIP2_CPU2    0xE442
#define FSM14_FSP3_CHIP2_CPU3    0xE443
#define FSM14_FSP3_CHIP2_CPU4    0xE444
#define FSM14_FSP3_CHIP2_CPU5    0xE445
#define FSM14_FSP3_CHIP2_CPU6    0xE446
#define FSM14_FSP3_CHIP2_CPU7    0xE447
#define FSM14_FSP3_CHIP2_CPU8    0xE448
#define FSM14_FSP3_CHIP2_SMP1    0xE44D /* FSM-r4 */

#define FSM14_FSP3_CHIP3         0xE450
#define FSM14_FSP3_CHIP3_CPU1    0xE451
#define FSM14_FSP3_CHIP3_CPU2    0xE452
#define FSM14_FSP3_CHIP3_CPU3    0xE453
#define FSM14_FSP3_CHIP3_CPU4    0xE454
#define FSM14_FSP3_CHIP3_CPU5    0xE455
#define FSM14_FSP3_CHIP3_CPU6    0xE456
#define FSM14_FSP3_CHIP3_CPU7    0xE457
#define FSM14_FSP3_CHIP3_CPU8    0xE458
#define FSM14_FSP3_CHIP3_SMP1    0xE45D /* FSM-r4 */

#define FSM14_FSP3_CHIP4         0xE460
#define FSM14_FSP3_CHIP4_CPU1    0xE461
#define FSM14_FSP3_CHIP4_CPU2    0xE462
#define FSM14_FSP3_CHIP4_CPU3    0xE463
#define FSM14_FSP3_CHIP4_CPU4    0xE464
#define FSM14_FSP3_CHIP4_CPU5    0xE465
#define FSM14_FSP3_CHIP4_CPU6    0xE466
#define FSM14_FSP3_CHIP4_CPU7    0xE467
#define FSM14_FSP3_CHIP4_CPU8    0xE468
#define FSM14_FSP3_CHIP4_SMP1    0xE46D /* FSM-r4 */

#define FSM14_FSP3_CHIP5         0xE470
#define FSM14_FSP3_CHIP5_CPU1    0xE471
#define FSM14_FSP3_CHIP5_CPU2    0xE472
#define FSM14_FSP3_CHIP5_CPU3    0xE473
#define FSM14_FSP3_CHIP5_CPU4    0xE474
#define FSM14_FSP3_CHIP5_CPU5    0xE475
#define FSM14_FSP3_CHIP5_CPU6    0xE476
#define FSM14_FSP3_CHIP5_CPU7    0xE477
#define FSM14_FSP3_CHIP5_CPU8    0xE478

#define FSM14_FSP3_CHIP6         0xE480
#define FSM14_FSP3_CHIP6_CPU1    0xE481
#define FSM14_FSP3_CHIP6_CPU2    0xE482
#define FSM14_FSP3_CHIP6_CPU3    0xE483
#define FSM14_FSP3_CHIP6_CPU4    0xE484
#define FSM14_FSP3_CHIP6_CPU5    0xE485
#define FSM14_FSP3_CHIP6_CPU6    0xE486
#define FSM14_FSP3_CHIP6_CPU7    0xE487
#define FSM14_FSP3_CHIP6_CPU8    0xE488

#define FSM14_FSP3_CHIPALL       0xE4F0


// Node Ids for Sic communication with HDLC modems
#define RU_MCU_NID              0xFEE0
#define RU_HDLC1_MCU_NID        0xFEE1
#define RU_HDLC2_MCU_NID        0xFEE2
#define RU_HDLC3_MCU_NID        0xFEE3
#define RU_HDLC4_MCU_NID        0xFEE4
#define RU_HDLC5_MCU_NID        0xFEE5
#define RU_HDLC6_MCU_NID        0xFEE6
#define RU_HDLC7_MCU_NID        0xFEE7
#define RU_HDLC8_MCU_NID        0xFEE8
#define RU_HDLC9_MCU_NID        0xFEE9
#define RU_HDLC10_MCU_NID       0xFEEA
#define RU_HDLC11_MCU_NID       0xFEEB
#define RU_HDLC12_MCU_NID       0xFEEC
#define RU_HDLC13_MCU_NID       0xFEED
#define RU_HDLC14_MCU_NID       0xFEEE
#define RU_HDLC15_MCU_NID       0xFEEF
#define RU_HDLC16_MCU_NID       0xFEF0
#define RU_HDLC17_MCU_NID       0xFEF1
#define RU_HDLC18_MCU_NID       0xFEF2
#define RU_HDLC19_MCU_NID       0xFEF3
#define RU_HDLC20_MCU_NID       0xFEF4
#define RU_HDLC21_MCU_NID       0xFEF5
#define RU_HDLC22_MCU_NID       0xFEF6
#define RU_HDLC23_MCU_NID       0xFEF7
#define RU_HDLC24_MCU_NID       0xFEF8
#define RU_HDLC25_MCU_NID       0xFEF9
#define RU_HDLC26_MCU_NID       0xFEFA
#define RU_HDLC27_MCU_NID       0xFEFB
#define RU_HDLC28_MCU_NID       0xFEFC
#define RU_HDLC29_MCU_NID       0xFEFD
#define RU_HDLC30_MCU_NID       0xFEFE
#define RU_HDLC31_MCU_NID       0xFEFF

/* HD-BDE */

/* SoC ID */
#define LHP 0x00
#define SHP 0x10
#define AHP 0x20
#define K2A CHIP1
#define K2B CHIP2
#define K2C CHIP3

/* Core ID */
#define CORE1  CPU1
#define CORE2  CPU2
#define CORE3  CPU3
#define CORE4  CPU4
#define CORE5  CPU5
#define CORE6  CPU6
#define CORE7  CPU7
#define CORE8  CPU8
#define EMGRP1 0x0A
#define MCU1   0x01

/* LCP MCU IDs */
#define SHP_MCU1 0x11
#define AHP_MCU1 0x21

#define FCT_MCU1         0x11
#define FCT_MCU2         0x21
#define FCT_MCU1_EMGRP1  0x1A
#define FCT_MCU2_EMGRP1  0x2A

/* FSMK MCU IDs */
#define XEONA_MCU1   0x11  /* Obsolete - use FCT_MCU1 */
#define XEONB_MCU1   0x21  /* Obsolete - use FCT_MCU2 */
#define XEONA_EMGRP1 0x1A  /* Obsolete - use FCT_MCU1_EMGRP1 */
#define XEONB_EMGRP1 0x2A  /* Obsolete - use FCT_MCU2_EMGRP1 */
#define CTRL_MCU_SLAVE  XEONB_MCU1  /* Obsolete - use FCT_MCU2 */

/* Node ID */
#define LCP1_SHP         0x1010
#define LCP1_SHP_MCU1    0x1011
#define LCP1_AHP         0x1020
#define LCP1_AHP_MCU1    0x1021
#define LCP2_SHP         0x1110
#define LCP2_SHP_MCU1    0x1111
#define LCP2_AHP         0x1120
#define LCP2_AHP_MCU1    0x1121
#define LCP_ACT_SHP      0xFE10
#define LCP_ACT_SHP_MCU1 0xFE11
#define LCP_ACT_AHP      0xFE20
#define LCP_ACT_AHP_MCU1 0xFE21

#define LSP1_LHP        0x1200
#define LSP1_LHP_SMP1   0x120D
#define LSP1_LHP_EMGRP1 0x120A
#define LSP1_K2A        0x1230
#define LSP1_K2A_SMP1   0x123D
#define LSP1_K2A_EMGRP1 0x123A
#define LSP1_K2A_CORE1  0x1231
#define LSP1_K2A_CORE2  0x1232
#define LSP1_K2A_CORE3  0x1233
#define LSP1_K2A_CORE4  0x1234
#define LSP1_K2A_CORE5  0x1235
#define LSP1_K2A_CORE6  0x1236
#define LSP1_K2A_CORE7  0x1237
#define LSP1_K2A_CORE8  0x1238
#define LSP1_K2B        0x1240
#define LSP1_K2B_SMP1   0x124D
#define LSP1_K2B_EMGRP1 0x124A
#define LSP1_K2B_CORE1  0x1241
#define LSP1_K2B_CORE2  0x1242
#define LSP1_K2B_CORE3  0x1243
#define LSP1_K2B_CORE4  0x1244
#define LSP1_K2B_CORE5  0x1245
#define LSP1_K2B_CORE6  0x1246
#define LSP1_K2B_CORE7  0x1247
#define LSP1_K2B_CORE8  0x1248
#define LSP1_K2C        0x1250
#define LSP1_K2C_SMP1   0x125D
#define LSP1_K2C_EMGRP1 0x125A
#define LSP1_K2C_CORE1  0x1251
#define LSP1_K2C_CORE2  0x1252
#define LSP1_K2C_CORE3  0x1253
#define LSP1_K2C_CORE4  0x1254
#define LSP1_K2C_CORE5  0x1255
#define LSP1_K2C_CORE6  0x1256
#define LSP1_K2C_CORE7  0x1257
#define LSP1_K2C_CORE8  0x1258

#define LSP2_LHP        0x1300
#define LSP2_LHP_SMP1   0x130D
#define LSP2_LHP_EMGRP1 0x130A
#define LSP2_K2A        0x1330
#define LSP2_K2A_SMP1   0x133D
#define LSP2_K2A_EMGRP1 0x133A
#define LSP2_K2A_CORE1  0x1331
#define LSP2_K2A_CORE2  0x1332
#define LSP2_K2A_CORE3  0x1333
#define LSP2_K2A_CORE4  0x1334
#define LSP2_K2A_CORE5  0x1335
#define LSP2_K2A_CORE6  0x1336
#define LSP2_K2A_CORE7  0x1337
#define LSP2_K2A_CORE8  0x1338
#define LSP2_K2B        0x1340
#define LSP2_K2B_SMP1   0x134D
#define LSP2_K2B_EMGRP1 0x134A
#define LSP2_K2B_CORE1  0x1341
#define LSP2_K2B_CORE2  0x1342
#define LSP2_K2B_CORE3  0x1343
#define LSP2_K2B_CORE4  0x1344
#define LSP2_K2B_CORE5  0x1345
#define LSP2_K2B_CORE6  0x1346
#define LSP2_K2B_CORE7  0x1347
#define LSP2_K2B_CORE8  0x1348
#define LSP2_K2C        0x1350
#define LSP2_K2C_SMP1   0x135D
#define LSP2_K2C_EMGRP1 0x135A
#define LSP2_K2C_CORE1  0x1351
#define LSP2_K2C_CORE2  0x1352
#define LSP2_K2C_CORE3  0x1353
#define LSP2_K2C_CORE4  0x1354
#define LSP2_K2C_CORE5  0x1355
#define LSP2_K2C_CORE6  0x1356
#define LSP2_K2C_CORE7  0x1357
#define LSP2_K2C_CORE8  0x1358

#define LSP3_LHP        0x1400
#define LSP3_LHP_SMP1   0x140D
#define LSP3_LHP_EMGRP1 0x140A
#define LSP3_K2A        0x1430
#define LSP3_K2A_SMP1   0x143D
#define LSP3_K2A_EMGRP1 0x143A
#define LSP3_K2A_CORE1  0x1431
#define LSP3_K2A_CORE2  0x1432
#define LSP3_K2A_CORE3  0x1433
#define LSP3_K2A_CORE4  0x1434
#define LSP3_K2A_CORE5  0x1435
#define LSP3_K2A_CORE6  0x1436
#define LSP3_K2A_CORE7  0x1437
#define LSP3_K2A_CORE8  0x1438
#define LSP3_K2B        0x1440
#define LSP3_K2B_SMP1   0x144D
#define LSP3_K2B_EMGRP1 0x144A
#define LSP3_K2B_CORE1  0x1441
#define LSP3_K2B_CORE2  0x1442
#define LSP3_K2B_CORE3  0x1443
#define LSP3_K2B_CORE4  0x1444
#define LSP3_K2B_CORE5  0x1445
#define LSP3_K2B_CORE6  0x1446
#define LSP3_K2B_CORE7  0x1447
#define LSP3_K2B_CORE8  0x1448
#define LSP3_K2C        0x1450
#define LSP3_K2C_SMP1   0x145D
#define LSP3_K2C_EMGRP1 0x145A
#define LSP3_K2C_CORE1  0x1451
#define LSP3_K2C_CORE2  0x1452
#define LSP3_K2C_CORE3  0x1453
#define LSP3_K2C_CORE4  0x1454
#define LSP3_K2C_CORE5  0x1455
#define LSP3_K2C_CORE6  0x1456
#define LSP3_K2C_CORE7  0x1457
#define LSP3_K2C_CORE8  0x1458

#define LSP4_LHP        0x1500
#define LSP4_LHP_SMP1   0x150D
#define LSP4_LHP_EMGRP1 0x150A
#define LSP4_K2A        0x1530
#define LSP4_K2A_SMP1   0x153D
#define LSP4_K2A_EMGRP1 0x153A
#define LSP4_K2A_CORE1  0x1531
#define LSP4_K2A_CORE2  0x1532
#define LSP4_K2A_CORE3  0x1533
#define LSP4_K2A_CORE4  0x1534
#define LSP4_K2A_CORE5  0x1535
#define LSP4_K2A_CORE6  0x1536
#define LSP4_K2A_CORE7  0x1537
#define LSP4_K2A_CORE8  0x1538
#define LSP4_K2B        0x1540
#define LSP4_K2B_SMP1   0x154D
#define LSP4_K2B_EMGRP1 0x154A
#define LSP4_K2B_CORE1  0x1541
#define LSP4_K2B_CORE2  0x1542
#define LSP4_K2B_CORE3  0x1543
#define LSP4_K2B_CORE4  0x1544
#define LSP4_K2B_CORE5  0x1545
#define LSP4_K2B_CORE6  0x1546
#define LSP4_K2B_CORE7  0x1547
#define LSP4_K2B_CORE8  0x1548
#define LSP4_K2C        0x1550
#define LSP4_K2C_SMP1   0x155D
#define LSP4_K2C_EMGRP1 0x155A
#define LSP4_K2C_CORE1  0x1551
#define LSP4_K2C_CORE2  0x1552
#define LSP4_K2C_CORE3  0x1553
#define LSP4_K2C_CORE4  0x1554
#define LSP4_K2C_CORE5  0x1555
#define LSP4_K2C_CORE6  0x1556
#define LSP4_K2C_CORE7  0x1557
#define LSP4_K2C_CORE8  0x1558

#define LSP5_LHP        0x1600
#define LSP5_LHP_SMP1   0x160D
#define LSP5_LHP_EMGRP1 0x160A
#define LSP5_K2A        0x1630
#define LSP5_K2A_SMP1   0x163D
#define LSP5_K2A_EMGRP1 0x163A
#define LSP5_K2A_CORE1  0x1631
#define LSP5_K2A_CORE2  0x1632
#define LSP5_K2A_CORE3  0x1633
#define LSP5_K2A_CORE4  0x1634
#define LSP5_K2A_CORE5  0x1635
#define LSP5_K2A_CORE6  0x1636
#define LSP5_K2A_CORE7  0x1637
#define LSP5_K2A_CORE8  0x1638
#define LSP5_K2B        0x1640
#define LSP5_K2B_SMP1   0x164D
#define LSP5_K2B_EMGRP1 0x164A
#define LSP5_K2B_CORE1  0x1641
#define LSP5_K2B_CORE2  0x1642
#define LSP5_K2B_CORE3  0x1643
#define LSP5_K2B_CORE4  0x1644
#define LSP5_K2B_CORE5  0x1645
#define LSP5_K2B_CORE6  0x1646
#define LSP5_K2B_CORE7  0x1647
#define LSP5_K2B_CORE8  0x1648
#define LSP5_K2C        0x1650
#define LSP5_K2C_SMP1   0x165D
#define LSP5_K2C_EMGRP1 0x165A
#define LSP5_K2C_CORE1  0x1651
#define LSP5_K2C_CORE2  0x1652
#define LSP5_K2C_CORE3  0x1653
#define LSP5_K2C_CORE4  0x1654
#define LSP5_K2C_CORE5  0x1655
#define LSP5_K2C_CORE6  0x1656
#define LSP5_K2C_CORE7  0x1657
#define LSP5_K2C_CORE8  0x1658

#define LSP6_LHP        0x1700
#define LSP6_LHP_SMP1   0x170D
#define LSP6_LHP_EMGRP1 0x170A
#define LSP6_K2A        0x1730
#define LSP6_K2A_SMP1   0x173D
#define LSP6_K2A_EMGRP1 0x173A
#define LSP6_K2A_CORE1  0x1731
#define LSP6_K2A_CORE2  0x1732
#define LSP6_K2A_CORE3  0x1733
#define LSP6_K2A_CORE4  0x1734
#define LSP6_K2A_CORE5  0x1735
#define LSP6_K2A_CORE6  0x1736
#define LSP6_K2A_CORE7  0x1737
#define LSP6_K2A_CORE8  0x1738
#define LSP6_K2B        0x1740
#define LSP6_K2B_SMP1   0x174D
#define LSP6_K2B_EMGRP1 0x174A
#define LSP6_K2B_CORE1  0x1741
#define LSP6_K2B_CORE2  0x1742
#define LSP6_K2B_CORE3  0x1743
#define LSP6_K2B_CORE4  0x1744
#define LSP6_K2B_CORE5  0x1745
#define LSP6_K2B_CORE6  0x1746
#define LSP6_K2B_CORE7  0x1747
#define LSP6_K2B_CORE8  0x1748
#define LSP6_K2C        0x1750
#define LSP6_K2C_SMP1   0x175D
#define LSP6_K2C_EMGRP1 0x175A
#define LSP6_K2C_CORE1  0x1751
#define LSP6_K2C_CORE2  0x1752
#define LSP6_K2C_CORE3  0x1753
#define LSP6_K2C_CORE4  0x1754
#define LSP6_K2C_CORE5  0x1755
#define LSP6_K2C_CORE6  0x1756
#define LSP6_K2C_CORE7  0x1757
#define LSP6_K2C_CORE8  0x1758

#define LSP7_LHP        0x1800
#define LSP7_LHP_SMP1   0x180D
#define LSP7_LHP_EMGRP1 0x180A
#define LSP7_K2A        0x1830
#define LSP7_K2A_SMP1   0x183D
#define LSP7_K2A_EMGRP1 0x183A
#define LSP7_K2A_CORE1  0x1831
#define LSP7_K2A_CORE2  0x1832
#define LSP7_K2A_CORE3  0x1833
#define LSP7_K2A_CORE4  0x1834
#define LSP7_K2A_CORE5  0x1835
#define LSP7_K2A_CORE6  0x1836
#define LSP7_K2A_CORE7  0x1837
#define LSP7_K2A_CORE8  0x1838
#define LSP7_K2B        0x1840
#define LSP7_K2B_SMP1   0x184D
#define LSP7_K2B_EMGRP1 0x184A
#define LSP7_K2B_CORE1  0x1841
#define LSP7_K2B_CORE2  0x1842
#define LSP7_K2B_CORE3  0x1843
#define LSP7_K2B_CORE4  0x1844
#define LSP7_K2B_CORE5  0x1845
#define LSP7_K2B_CORE6  0x1846
#define LSP7_K2B_CORE7  0x1847
#define LSP7_K2B_CORE8  0x1848
#define LSP7_K2C        0x1850
#define LSP7_K2C_SMP1   0x185D
#define LSP7_K2C_EMGRP1 0x185A
#define LSP7_K2C_CORE1  0x1851
#define LSP7_K2C_CORE2  0x1852
#define LSP7_K2C_CORE3  0x1853
#define LSP7_K2C_CORE4  0x1854
#define LSP7_K2C_CORE5  0x1855
#define LSP7_K2C_CORE6  0x1856
#define LSP7_K2C_CORE7  0x1857
#define LSP7_K2C_CORE8  0x1858

#define LSP8_LHP        0x1900
#define LSP8_LHP_SMP1   0x190D
#define LSP8_LHP_EMGRP1 0x190A
#define LSP8_K2A        0x1930
#define LSP8_K2A_SMP1   0x193D
#define LSP8_K2A_EMGRP1 0x193A
#define LSP8_K2A_CORE1  0x1931
#define LSP8_K2A_CORE2  0x1932
#define LSP8_K2A_CORE3  0x1933
#define LSP8_K2A_CORE4  0x1934
#define LSP8_K2A_CORE5  0x1935
#define LSP8_K2A_CORE6  0x1936
#define LSP8_K2A_CORE7  0x1937
#define LSP8_K2A_CORE8  0x1938
#define LSP8_K2B        0x1940
#define LSP8_K2B_SMP1   0x194D
#define LSP8_K2B_EMGRP1 0x194A
#define LSP8_K2B_CORE1  0x1941
#define LSP8_K2B_CORE2  0x1942
#define LSP8_K2B_CORE3  0x1943
#define LSP8_K2B_CORE4  0x1944
#define LSP8_K2B_CORE5  0x1945
#define LSP8_K2B_CORE6  0x1946
#define LSP8_K2B_CORE7  0x1947
#define LSP8_K2B_CORE8  0x1948
#define LSP8_K2C        0x1950
#define LSP8_K2C_SMP1   0x195D
#define LSP8_K2C_EMGRP1 0x195A
#define LSP8_K2C_CORE1  0x1951
#define LSP8_K2C_CORE2  0x1952
#define LSP8_K2C_CORE3  0x1953
#define LSP8_K2C_CORE4  0x1954
#define LSP8_K2C_CORE5  0x1955
#define LSP8_K2C_CORE6  0x1956
#define LSP8_K2C_CORE7  0x1957
#define LSP8_K2C_CORE8  0x1958

#define LSP9_LHP        0x1A00
#define LSP9_LHP_SMP1   0x1A0D
#define LSP9_LHP_EMGRP1 0x1A0A
#define LSP9_K2A        0x1A30
#define LSP9_K2A_SMP1   0x1A3D
#define LSP9_K2A_EMGRP1 0x1A3A
#define LSP9_K2A_CORE1  0x1A31
#define LSP9_K2A_CORE2  0x1A32
#define LSP9_K2A_CORE3  0x1A33
#define LSP9_K2A_CORE4  0x1A34
#define LSP9_K2A_CORE5  0x1A35
#define LSP9_K2A_CORE6  0x1A36
#define LSP9_K2A_CORE7  0x1A37
#define LSP9_K2A_CORE8  0x1A38
#define LSP9_K2B        0x1A40
#define LSP9_K2B_SMP1   0x1A4D
#define LSP9_K2B_EMGRP1 0x1A4A
#define LSP9_K2B_CORE1  0x1A41
#define LSP9_K2B_CORE2  0x1A42
#define LSP9_K2B_CORE3  0x1A43
#define LSP9_K2B_CORE4  0x1A44
#define LSP9_K2B_CORE5  0x1A45
#define LSP9_K2B_CORE6  0x1A46
#define LSP9_K2B_CORE7  0x1A47
#define LSP9_K2B_CORE8  0x1A48
#define LSP9_K2C        0x1A50
#define LSP9_K2C_SMP1   0x1A5D
#define LSP9_K2C_EMGRP1 0x1A5A
#define LSP9_K2C_CORE1  0x1A51
#define LSP9_K2C_CORE2  0x1A52
#define LSP9_K2C_CORE3  0x1A53
#define LSP9_K2C_CORE4  0x1A54
#define LSP9_K2C_CORE5  0x1A55
#define LSP9_K2C_CORE6  0x1A56
#define LSP9_K2C_CORE7  0x1A57
#define LSP9_K2C_CORE8  0x1A58

#define LSP10_LHP        0x1B00
#define LSP10_LHP_SMP1   0x1B0D
#define LSP10_LHP_EMGRP1 0x1B0A
#define LSP10_K2A        0x1B30
#define LSP10_K2A_SMP1   0x1B3D
#define LSP10_K2A_EMGRP1 0x1B3A
#define LSP10_K2A_CORE1  0x1B31
#define LSP10_K2A_CORE2  0x1B32
#define LSP10_K2A_CORE3  0x1B33
#define LSP10_K2A_CORE4  0x1B34
#define LSP10_K2A_CORE5  0x1B35
#define LSP10_K2A_CORE6  0x1B36
#define LSP10_K2A_CORE7  0x1B37
#define LSP10_K2A_CORE8  0x1B38
#define LSP10_K2B        0x1B40
#define LSP10_K2B_SMP1   0x1B4D
#define LSP10_K2B_EMGRP1 0x1B4A
#define LSP10_K2B_CORE1  0x1B41
#define LSP10_K2B_CORE2  0x1B42
#define LSP10_K2B_CORE3  0x1B43
#define LSP10_K2B_CORE4  0x1B44
#define LSP10_K2B_CORE5  0x1B45
#define LSP10_K2B_CORE6  0x1B46
#define LSP10_K2B_CORE7  0x1B47
#define LSP10_K2B_CORE8  0x1B48
#define LSP10_K2C        0x1B50
#define LSP10_K2C_SMP1   0x1B5D
#define LSP10_K2C_EMGRP1 0x1B5A
#define LSP10_K2C_CORE1  0x1B51
#define LSP10_K2C_CORE2  0x1B52
#define LSP10_K2C_CORE3  0x1B53
#define LSP10_K2C_CORE4  0x1B54
#define LSP10_K2C_CORE5  0x1B55
#define LSP10_K2C_CORE6  0x1B56
#define LSP10_K2C_CORE7  0x1B57
#define LSP10_K2C_CORE8  0x1B58

#define LSP11_LHP        0x1C00
#define LSP11_LHP_SMP1   0x1C0D
#define LSP11_LHP_EMGRP1 0x1C0A
#define LSP11_K2A        0x1C30
#define LSP11_K2A_SMP1   0x1C3D
#define LSP11_K2A_EMGRP1 0x1C3A
#define LSP11_K2A_CORE1  0x1C31
#define LSP11_K2A_CORE2  0x1C32
#define LSP11_K2A_CORE3  0x1C33
#define LSP11_K2A_CORE4  0x1C34
#define LSP11_K2A_CORE5  0x1C35
#define LSP11_K2A_CORE6  0x1C36
#define LSP11_K2A_CORE7  0x1C37
#define LSP11_K2A_CORE8  0x1C38
#define LSP11_K2B        0x1C40
#define LSP11_K2B_SMP1   0x1C4D
#define LSP11_K2B_EMGRP1 0x1C4A
#define LSP11_K2B_CORE1  0x1C41
#define LSP11_K2B_CORE2  0x1C42
#define LSP11_K2B_CORE3  0x1C43
#define LSP11_K2B_CORE4  0x1C44
#define LSP11_K2B_CORE5  0x1C45
#define LSP11_K2B_CORE6  0x1C46
#define LSP11_K2B_CORE7  0x1C47
#define LSP11_K2B_CORE8  0x1C48
#define LSP11_K2C        0x1C50
#define LSP11_K2C_SMP1   0x1C5d
#define LSP11_K2C_EMGRP1 0x1C5a
#define LSP11_K2C_CORE1  0x1C51
#define LSP11_K2C_CORE2  0x1C52
#define LSP11_K2C_CORE3  0x1C53
#define LSP11_K2C_CORE4  0x1C54
#define LSP11_K2C_CORE5  0x1C55
#define LSP11_K2C_CORE6  0x1C56
#define LSP11_K2C_CORE7  0x1C57
#define LSP11_K2C_CORE8  0x1C58

#define LSP12_LHP        0x1D00
#define LSP12_LHP_SMP1   0x1D0D
#define LSP12_LHP_EMGRP1 0x1D0A
#define LSP12_K2A        0x1D30
#define LSP12_K2A_SMP1   0x1D3D
#define LSP12_K2A_EMGRP1 0x1D3A
#define LSP12_K2A_CORE1  0x1D31
#define LSP12_K2A_CORE2  0x1D32
#define LSP12_K2A_CORE3  0x1D33
#define LSP12_K2A_CORE4  0x1D34
#define LSP12_K2A_CORE5  0x1D35
#define LSP12_K2A_CORE6  0x1D36
#define LSP12_K2A_CORE7  0x1D37
#define LSP12_K2A_CORE8  0x1D38
#define LSP12_K2B        0x1D40
#define LSP12_K2B_SMP1   0x1D4D
#define LSP12_K2B_EMGRP1 0x1D4A
#define LSP12_K2B_CORE1  0x1D41
#define LSP12_K2B_CORE2  0x1D42
#define LSP12_K2B_CORE3  0x1D43
#define LSP12_K2B_CORE4  0x1D44
#define LSP12_K2B_CORE5  0x1D45
#define LSP12_K2B_CORE6  0x1D46
#define LSP12_K2B_CORE7  0x1D47
#define LSP12_K2B_CORE8  0x1D48
#define LSP12_K2C        0x1D50
#define LSP12_K2C_SMP1   0x1D5D
#define LSP12_K2C_EMGRP1 0x1D5A
#define LSP12_K2C_CORE1  0x1D51
#define LSP12_K2C_CORE2  0x1D52
#define LSP12_K2C_CORE3  0x1D53
#define LSP12_K2C_CORE4  0x1D54
#define LSP12_K2C_CORE5  0x1D55
#define LSP12_K2C_CORE6  0x1D56
#define LSP12_K2C_CORE7  0x1D57
#define LSP12_K2C_CORE8  0x1D58

#define LSP13_LHP        0x1E00
#define LSP13_LHP_SMP1   0x1E0D
#define LSP13_LHP_EMGRP1 0x1E0A
#define LSP13_K2A        0x1E30
#define LSP13_K2A_SMP1   0x1E3D
#define LSP13_K2A_EMGRP1 0x1E3A
#define LSP13_K2A_CORE1  0x1E31
#define LSP13_K2A_CORE2  0x1E32
#define LSP13_K2A_CORE3  0x1E33
#define LSP13_K2A_CORE4  0x1E34
#define LSP13_K2A_CORE5  0x1E35
#define LSP13_K2A_CORE6  0x1E36
#define LSP13_K2A_CORE7  0x1E37
#define LSP13_K2A_CORE8  0x1E38
#define LSP13_K2B        0x1E40
#define LSP13_K2B_SMP1   0x1E4D
#define LSP13_K2B_EMGRP1 0x1E4A
#define LSP13_K2B_CORE1  0x1E41
#define LSP13_K2B_CORE2  0x1E42
#define LSP13_K2B_CORE3  0x1E43
#define LSP13_K2B_CORE4  0x1E44
#define LSP13_K2B_CORE5  0x1E45
#define LSP13_K2B_CORE6  0x1E46
#define LSP13_K2B_CORE7  0x1E47
#define LSP13_K2B_CORE8  0x1E48
#define LSP13_K2C        0x1E50
#define LSP13_K2C_SMP1   0x1E5D
#define LSP13_K2C_EMGRP1 0x1E5A
#define LSP13_K2C_CORE1  0x1E51
#define LSP13_K2C_CORE2  0x1E52
#define LSP13_K2C_CORE3  0x1E53
#define LSP13_K2C_CORE4  0x1E54
#define LSP13_K2C_CORE5  0x1E55
#define LSP13_K2C_CORE6  0x1E56
#define LSP13_K2C_CORE7  0x1E57
#define LSP13_K2C_CORE8  0x1E58

#define LSP14_LHP        0x1F00
#define LSP14_LHP_SMP1   0x1F0D
#define LSP14_LHP_EMGRP1 0x1F0A
#define LSP14_K2A        0x1F30
#define LSP14_K2A_SMP1   0x1F3D
#define LSP14_K2A_EMGRP1 0x1F3A
#define LSP14_K2A_CORE1  0x1F31
#define LSP14_K2A_CORE2  0x1F32
#define LSP14_K2A_CORE3  0x1F33
#define LSP14_K2A_CORE4  0x1F34
#define LSP14_K2A_CORE5  0x1F35
#define LSP14_K2A_CORE6  0x1F36
#define LSP14_K2A_CORE7  0x1F37
#define LSP14_K2A_CORE8  0x1F38
#define LSP14_K2B        0x1F40
#define LSP14_K2B_SMP1   0x1F4D
#define LSP14_K2B_EMGRP1 0x1F4A
#define LSP14_K2B_CORE1  0x1F41
#define LSP14_K2B_CORE2  0x1F42
#define LSP14_K2B_CORE3  0x1F43
#define LSP14_K2B_CORE4  0x1F44
#define LSP14_K2B_CORE5  0x1F45
#define LSP14_K2B_CORE6  0x1F46
#define LSP14_K2B_CORE7  0x1F47
#define LSP14_K2B_CORE8  0x1F48
#define LSP14_K2C        0x1F50
#define LSP14_K2C_SMP1   0x1F5D
#define LSP14_K2C_EMGRP1 0x1F5A
#define LSP14_K2C_CORE1  0x1F51
#define LSP14_K2C_CORE2  0x1F52
#define LSP14_K2C_CORE3  0x1F53
#define LSP14_K2C_CORE4  0x1F54
#define LSP14_K2C_CORE5  0x1F55
#define LSP14_K2C_CORE6  0x1F56
#define LSP14_K2C_CORE7  0x1F57
#define LSP14_K2C_CORE8  0x1F58

#define LSP15_LHP        0x2000
#define LSP15_LHP_SMP1   0x200D
#define LSP15_LHP_EMGRP1 0x200A
#define LSP15_K2A        0x2030
#define LSP15_K2A_SMP1   0x203D
#define LSP15_K2A_EMGRP1 0x203A
#define LSP15_K2A_CORE1  0x2031
#define LSP15_K2A_CORE2  0x2032
#define LSP15_K2A_CORE3  0x2033
#define LSP15_K2A_CORE4  0x2034
#define LSP15_K2A_CORE5  0x2035
#define LSP15_K2A_CORE6  0x2036
#define LSP15_K2A_CORE7  0x2037
#define LSP15_K2A_CORE8  0x2038
#define LSP15_K2B        0x2040
#define LSP15_K2B_SMP1   0x204D
#define LSP15_K2B_EMGRP1 0x204A
#define LSP15_K2B_CORE1  0x2041
#define LSP15_K2B_CORE2  0x2042
#define LSP15_K2B_CORE3  0x2043
#define LSP15_K2B_CORE4  0x2044
#define LSP15_K2B_CORE5  0x2045
#define LSP15_K2B_CORE6  0x2046
#define LSP15_K2B_CORE7  0x2047
#define LSP15_K2B_CORE8  0x2048
#define LSP15_K2C        0x2050
#define LSP15_K2C_SMP1   0x205D
#define LSP15_K2C_EMGRP1 0x205A
#define LSP15_K2C_CORE1  0x2051
#define LSP15_K2C_CORE2  0x2052
#define LSP15_K2C_CORE3  0x2053
#define LSP15_K2C_CORE4  0x2054
#define LSP15_K2C_CORE5  0x2055
#define LSP15_K2C_CORE6  0x2056
#define LSP15_K2C_CORE7  0x2057
#define LSP15_K2C_CORE8  0x2058

#define LSP16_LHP        0x2100
#define LSP16_LHP_SMP1   0x210D
#define LSP16_LHP_EMGRP1 0x210A
#define LSP16_K2A        0x2130
#define LSP16_K2A_SMP1   0x213D
#define LSP16_K2A_EMGRP1 0x213A
#define LSP16_K2A_CORE1  0x2131
#define LSP16_K2A_CORE2  0x2132
#define LSP16_K2A_CORE3  0x2133
#define LSP16_K2A_CORE4  0x2134
#define LSP16_K2A_CORE5  0x2135
#define LSP16_K2A_CORE6  0x2136
#define LSP16_K2A_CORE7  0x2137
#define LSP16_K2A_CORE8  0x2138
#define LSP16_K2B        0x2140
#define LSP16_K2B_SMP1   0x214D
#define LSP16_K2B_EMGRP1 0x214A
#define LSP16_K2B_CORE1  0x2141
#define LSP16_K2B_CORE2  0x2142
#define LSP16_K2B_CORE3  0x2143
#define LSP16_K2B_CORE4  0x2144
#define LSP16_K2B_CORE5  0x2145
#define LSP16_K2B_CORE6  0x2146
#define LSP16_K2B_CORE7  0x2147
#define LSP16_K2B_CORE8  0x2148
#define LSP16_K2C        0x2150
#define LSP16_K2C_SMP1   0x215D
#define LSP16_K2C_EMGRP1 0x215A
#define LSP16_K2C_CORE1  0x2151
#define LSP16_K2C_CORE2  0x2152
#define LSP16_K2C_CORE3  0x2153
#define LSP16_K2C_CORE4  0x2154
#define LSP16_K2C_CORE5  0x2155
#define LSP16_K2C_CORE6  0x2156
#define LSP16_K2C_CORE7  0x2157
#define LSP16_K2C_CORE8  0x2158

/* The following defines and macros apply to the Liquid Radio Cloud and FZM platforms */
/* ****** Approval pending EFS specification in WBTS_ICOM ********* */
/**
*  Set the board portion of a NID. First 8 bits are used to store
*  the slot/logical id
*/
#define LRC_NID_FMT_BOARD(nid_board) ((((uint16_t)nid_board) << 8) & 0xFF00)

/**
* Set the SOC/Class portion of a NID. 4 bits are used to store the
* SOC/Logical Class id
*
*/
#define LRC_NID_FMT_SOC(nid_soc) ((((uint16_t)nid_soc << 4)) & 0x00F0)

/**
* Set the Core/Logical Entity portion of a NID. 4 bits are used
* to store the Core/Logical Entity id.
* 0 is reserved for SysCom.
*/
#define LRC_NID_FMT_CORE(nid_core) (((uint16_t)nid_core) & 0x000F)

/**
* Format a NID address using slot/SOC/Core info
*
*/
#define LRC_NID_FMT_NID(nid_slot, nid_soc, nid_core) (LRC_NID_FMT_BOARD(nid_slot)|LRC_NID_FMT_SOC(nid_soc)|LRC_NID_FMT_CORE(nid_core))

/**
* Get the Board Id from a NID.
*/
#define LRC_NID_GET_BOARD(nid_nid) ((((uint16_t)nid_nid) >> 8) & 0x00FF)

/**
* Get the SOC Id from a NID.
*/
#define LRC_NID_GET_SOC(nid_nid) ((((uint16_t)nid_nid) >> 4) & 0x000F)

/**
* Get the Core Id from a NID.
*/
#define LRC_NID_GET_CORE(nid_nid) (((uint16_t)nid_nid) & 0x000F)

/*UDPCP port used by the LSP SysCom GW */
#define LRC_LSP_DEF_UDPCP_PORT       14009
/*UDP port used by the LSP SysCom GW */
#define LRC_LSP_DEF_UDP_PORT         16009

/*Board Identifier */
/*LCP01-2 same as WAM_10, WAM_11 */
#define LRC_NID_LCP01       LCP1
#define LRC_NID_LCP02       LCP2
/*LSP01-08 same as WSP_10..WSP_15 */
/* Note that LSP IDs are 0-based in the architecture document. */
#define LRC_NIDKEPLER2_LSP01       LSP1
#define LRC_NIDKEPLER2_LSP02       LSP2
#define LRC_NIDKEPLER2_LSP03       LSP3
#define LRC_NIDKEPLER2_LSP04       LSP4
#define LRC_NIDKEPLER2_LSP05       LSP5
#define LRC_NIDKEPLER2_LSP06       LSP6
#define LRC_NIDKEPLER2_LSP07       LSP7
#define LRC_NIDKEPLER2_LSP08       LSP8
#define LRC_NIDKEPLER2_LSP09       LSP9
#define LRC_NIDKEPLER2_LSP10       LSP10
#define LRC_NIDKEPLER2_LSP11       LSP11
#define LRC_NIDKEPLER2_LSP12       LSP12
#define LRC_NIDKEPLER2_LSP13       LSP13
#define LRC_NIDKEPLER2_LSP14       LSP14
/* LSP15-16 as WAM_20,WAM-21 */
#define LRC_NIDKEPLER2_LSP15       LSP15
#define LRC_NIDKEPLER2_LSP16       LSP16

/* Min and max board id for LSP */
#define LRC_NID_LSP_BOARD_MIN LRC_NIDKEPLER2_LSP01
#define LRC_NID_LSP_BOARD_MAX LRC_NIDKEPLER2_LSP16

/*Kepler-2 SOC 1 */
#define LRC_NIDKEPLER2_SOC1   0x03
/*Kepler-2 SOC 2 */
#define LRC_NIDKEPLER2_SOC2   0x04
/*Kepler-2 SOC 3 */
#define LRC_NIDKEPLER2_SOC3   0x05
/*Kepler-2 SOC 4 */
/* Note: Currently not used. For future extension. */
#define LRC_NIDKEPLER2_SOC4   0x06

/*LSI AXM5516 */
#define LRC_NIDAXM5516_SOC1   0x00
/* Note: AXM containers */
#define LRC_NIDAXM5516_SOC2   0x01
#define LRC_NIDAXM5516_SOC3   0x02

/* Min and max SOC id for LSP */
#define LRC_NID_LSP_SOC_MIN LRC_NIDAXM5516_SOC1
#define LRC_NID_LSP_SOC_MAX LRC_NIDKEPLER2_SOC4

/*Kepler 2 ARM Event Machine Group 1 */
#define LRC_NIDK2ARM_EMGRP1     0x0A
/*Kepler 2 ARM Event Machine Group 2 (specifically for CPU1 in FZM) */
#define LRC_NIDK2ARM_EMGRP2     0x09
/*Kepler 2 ARM Event Machine Group 3 (specifically for CPU2 in FZM) */
#define LRC_NIDK2ARM_EMGRP3     0x0B
/*Kepler 2 ARM Event Machine Group 4 (specifically for CPU3 in FZM) */
#define LRC_NIDK2ARM_EMGRP4     0x0C

/*Kepler 2 Process SMP-1 for ARM*/
#define LRC_NIDK2ARM_SMP1       0x0D

/* Note that DSP core IDs are 0-based on the architecture document */
/*Kepler 2 DSP Core 1 */
#define LRC_NIDK2DSPCORE1       0x01
/*Kepler 2 DSP Core 2 */
#define LRC_NIDK2DSPCORE2       0x02
/*Kepler 2 DSP Core 3 */
#define LRC_NIDK2DSPCORE3       0x03
/*Kepler 2 DSP Core 4 */
#define LRC_NIDK2DSPCORE4       0x04
/*Kepler 2 DSP Core 5 */
#define LRC_NIDK2DSPCORE5       0x05
/*Kepler 2 DSP Core 6 */
#define LRC_NIDK2DSPCORE6       0x06
/*Kepler 2 DSP Core 7 */
#define LRC_NIDK2DSPCORE7       0x07
/*Kepler 2 DSP Core 8 */
#define LRC_NIDK2DSPCORE8       0x08

#define LRC_NIDK2DSPMAX         LRC_NIDK2DSPCORE8

/*LSI - Reserved */
#define LRC_NIDLSIRESERVED    0x00

/*LSI ARM Event Machine Group 1 */
#define LRC_NIDAXM5516_EMGRP1 0x0A

/*LSI Process SMP-1 */
#define LRC_NIDAXM5516_SMP1   0x0D

/*FZM: one board and one K2.
Note that there are no slots in the FZM product.  It has a single motherboard with a fixed enclosure.
The board is not field-replaceable or hot-swappable. With only a single motherboard and no slots,
the physical slot definition used for LRC is not meaningful in this context and only as a simplification
the same LRC_NIDs used for LSP00 are used. */

#define FZM_K2_LINUX      LRC_NID_FMT_NID(0x00, LRC_NIDKEPLER2_SOC1, LRC_NIDK2ARM_SMP1)

#define FZM_K2_LINUX_NID  LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC1, LRC_NIDK2ARM_SMP1)

#define FZM_K2_D01_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC1, LRC_NIDK2DSPCORE1)
#define FZM_K2_D02_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC1, LRC_NIDK2DSPCORE2)
#define FZM_K2_D03_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC1, LRC_NIDK2DSPCORE3)
#define FZM_K2_D04_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC1, LRC_NIDK2DSPCORE4)
#define FZM_K2_D05_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC1, LRC_NIDK2DSPCORE5)
#define FZM_K2_D06_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC1, LRC_NIDK2DSPCORE6)
#define FZM_K2_D07_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC1, LRC_NIDK2DSPCORE7)
#define FZM_K2_D08_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC1, LRC_NIDK2DSPCORE8)


#define FZM_K2_D01       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC1)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE1))
#define FZM_K2_D02       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC1)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE2))
#define FZM_K2_D03       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC1)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE3))
#define FZM_K2_D04       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC1)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE4))
#define FZM_K2_D05       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC1)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE5))
#define FZM_K2_D06       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC1)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE6))
#define FZM_K2_D07       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC1)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE7))
#define FZM_K2_D08       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC1)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE8))

/* DSP NIDs on the slave board of the Sprint 3 Carrier hardware */
#define FZM_K2S_D01_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC2, LRC_NIDK2DSPCORE1)
#define FZM_K2S_D02_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC2, LRC_NIDK2DSPCORE2)
#define FZM_K2S_D03_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC2, LRC_NIDK2DSPCORE3)
#define FZM_K2S_D04_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC2, LRC_NIDK2DSPCORE4)
#define FZM_K2S_D05_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC2, LRC_NIDK2DSPCORE5)
#define FZM_K2S_D06_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC2, LRC_NIDK2DSPCORE6)
#define FZM_K2S_D07_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC2, LRC_NIDK2DSPCORE7)
#define FZM_K2S_D08_NID    LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC2, LRC_NIDK2DSPCORE8)

#define FZM_K2S_D01       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE1))
#define FZM_K2S_D02       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE2))
#define FZM_K2S_D03       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE3))
#define FZM_K2S_D04       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE4))
#define FZM_K2S_D05       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE5))
#define FZM_K2S_D06       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE6))
#define FZM_K2S_D07       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE7))
#define FZM_K2S_D08       (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2DSPCORE8))

#define FZM_BOARD_1      LRC_NIDKEPLER2_LSP01

#define FZM_NIDK2ARM_VTC    0x0E
#define FZM_K2_VTC_NID      LRC_NID_FMT_NID(LRC_NID_GET_BOARD(FZM_K2_LINUX_NID), LRC_NID_GET_SOC(FZM_K2_LINUX_NID), FZM_NIDK2ARM_VTC)

/* CC&S Lite/Scheduler NIDs on the slave board of the Sprint 3 carrier hardware */
#define FZM_K2_LINUX_EM_CPU1  LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC2, LRC_NIDK2ARM_EMGRP2)
#define FZM_K2_LINUX_EM_CPU2  LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC2, LRC_NIDK2ARM_EMGRP3)
#define FZM_K2_LINUX_EM_CPU3  LRC_NID_FMT_NID(LRC_NIDKEPLER2_LSP01, LRC_NIDKEPLER2_SOC2, LRC_NIDK2ARM_EMGRP4)

/* FZM K2 Slave */
#define FZM_K2S_A01  (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2ARM_EMGRP1))
#define FZM_K2S_A02  (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2ARM_EMGRP2))
#define FZM_K2S_A03  (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2ARM_EMGRP3))
#define FZM_K2S_A04  (LRC_NID_FMT_BOARD(0x00)|LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2)|LRC_NID_FMT_CORE(LRC_NIDK2ARM_EMGRP4))

/* CHIPs on master and slave boards for dual-board FZM */
#define FZM_K2_CHIP   LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC1) //0x30
#define FZM_K2S_CHIP  LRC_NID_FMT_SOC(LRC_NIDKEPLER2_SOC2) //0x40

/*LCP Definitions */
/*LCP Process SMP-1 for ARM*/
#define LRC_LCP_SMP1        0x01

/*LCP SHP, AHP */
#define LRC_LCP_SHP         0x01
#define LRC_LCP_AHP         0x02

/*Active LCP*/
#define LRC_LCP_ACTIVE_BOARDID_NID   0xFE
/*0xFD reserved for potential future Standby-LCP */

/*AXM 3G*/
/*Active AXM LSP*/
#define LRC_AXM_ACTIVE_BOARDID_NID   0xFC
/*0xFC reserved for future use */

#define LRC_NID_LBR01   0x22    /*It represents ID of LBR card on LRC. */
#define LRC_NID_LBR02   0x23    /*It represents ID of LBR card on LRC. */
#define LRC_NID_LBR03   0x24    /*It represents ID of LBR card on LRC. */
#define LRC_NID_LBR04   0x25    /*It represents ID of LBR card on LRC. */
#define LRC_NID_LCA      0x26    /*It represents ID of LCA card on LRC. */
#define LRC_NID_LBI       0x27    /*It represents ID of LBI card on LRC. */
#define LRC_NID_LNI01   0x28    /*It represents ID of LNI card on LRC. */
#define LRC_NID_LNI02   0x29    /*It represents ID of LNI card on LRC. */
#define LRC_NID_LPS01   0x2A    /*It represents ID of LPS card on LRC. */
#define LRC_NID_LPS02   0x2B    /*It represents ID of LPS card on LRC. */
#define LRC_NID_LPS03   0x2C    /*It represents ID of LPS card on LRC. */
#define LRC_NID_LPS04   0x2D    /*It represents ID of LPS card on LRC. */
#define LRC_NID_LPS05   0x2E    /*It represents ID of LPS card on LRC. */
#define LRC_NID_LPS06   0x2F    /*It represents ID of LPS card on LRC. */
#define LRC_NID_FAN01   0x30    /*It represents ID of FAN card on LRC. */
#define LRC_NID_FAN02   0x31    /*It represents ID of FAN card on LRC. */
#define LRC_NID_FAN03   0x32    /*It represents ID of FAN card on LRC. */
#define LRC_NID_FAN04   0x33    /*It represents ID of FAN card on LRC. */

#define LRC_SYNC_LCP01 0xE5 /*It represents SYNC on LRC card LCP #1 */
#define LRC_SYNC_LCP02 0xE6 /*It represents SYNC on LRC card LCP #2 */
#define LRC_CLK_LCP01   0xE7 /*It represents clock on LRC card LCP #1 */
#define LRC_CLK_LCP02   0xE8 /*It represents clock on LRC card LCP #2 */
#define LRC_PTP_LCP01   0xEC /*It represents function of Preceision Time Procotol: IEEE 1588v2 on LRC card LCP #1 */
#define LRC_PTP_LCP02   0xED /*It represents function of Preceision Time Procotol: IEEE 1588v2 on LRC card LCP #2 */
#define LRC_WCDMADB     0xE9 /*It represents several functions (eg. Memory dump)on LRC. */

#define LRC_BBRESOURCE_01 0x50 /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_02 0x51 /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_03 0x52 /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_04 0x53 /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_05 0x54 /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_06 0x55 /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_07 0x56 /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_08 0x57 /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_09 0x58 /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_10 0x59 /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_11 0x5A /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_12 0x5B /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_13 0x5C /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_14 0x5D /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_15 0x5E /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_BBRESOURCE_16 0x5F /*It represents the Baseband resource (3G or LTE) on LRC*/
#define LRC_CPRIMUX_01 0x60 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_02 0x61 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_03 0x62 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_04 0x63 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_05 0x64 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_06 0x65 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_07 0x66 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_08 0x67 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_09 0x68 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_10 0x69 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_11 0x6A /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_12 0x6B /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_13 0x6C /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_14 0x6D /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_15 0x6E /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_16 0x6F /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_17 0x70 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_18 0x71 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_19 0x72 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_20 0x73 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_21 0x74 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_22 0x75 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_23 0x76 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_24 0x77 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_25 0x78 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_26 0x79 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_27 0x7A /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_28 0x7B /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_29 0x7C /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_30 0x7D /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_31 0x7E /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_32 0x7F /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_33 0x80 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_34 0x81 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_35 0x82 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_36 0x83 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_37 0x84 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_38 0x85 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_39 0x86 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_40 0x87 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_41 0x88 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_42 0x89 /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_43 0x8A /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_44 0x8B /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_45 0x8C /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_46 0x8D /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_47 0x8E /*It represents CPRI link connected to RE on LRC*/
#define LRC_CPRIMUX_48 0x8F /*It represents CPRI link connected to RE on LRC*/
#define LRC_MDECPRI_01 0x90 /*It represents CPRI link to 3G-MDE on LRC*/
#define LRC_MDECPRI_02 0x91 /*It represents CPRI link to 3G-MDE on LRC*/
#define LRC_MDECPRI_03 0x92 /*It represents CPRI link to 3G-MDE on LRC*/
#define LRC_MDECPRI_04 0x93 /*It represents CPRI link to 3G-MDE on LRC*/
#define LRC_MDECPRI_05 0x94 /*It represents CPRI link to 3G-MDE on LRC*/
#define LRC_MDECPRI_06 0x95 /*It represents CPRI link to 3G-MDE on LRC*/
#define LRC_MDECPRI_07 0x96 /*It represents CPRI link to 3G-MDE on LRC*/
#define LRC_MDECPRI_08 0x97 /*It represents CPRI link to 3G-MDE on LRC*/
#define LRC_MDECPRI_09 0x98 /*It represents CPRI link to 3G-MDE on LRC*/
#define LRC_MDECPRI_10 0x99 /*It represents CPRI link to 3G-MDE on LRC*/
#define LRC_MDECPRI_11 0x9A /*It represents CPRI link to 3G-MDE on LRC*/

/* The above defines and macros apply to the Liquid Radio Cloud and FZM platforms */

#define FSM_FAN4  0x9B /* HD-BDE Module Fan4 */
#define FSM_FAN5  0x9C /* HD-BDE Module Fan5 */
#define FSM_FAN6  0x9D /* HD-BDE Module Fan6 */
#define FSM_FAN7  0x9E /* HD-BDE Module Fan7 */
#define FSM_FAN8  0x9F /* HD-BDE Module Fan8 */

#define LRC_MDECPRI_12 0xA0 /*It represents CPRI link to 3G-MDE on LRC*/

/* 3DAAS / Beamer-related Node IDs. These are 3DAAS internal NIDs (not sent on wire to SM)
and therefore reservation for 3DAAS does not exclude SM using the same NIDs */
#define AAS_MODULE 0xE

#define BEAMER_BOARD 0x0

#define KID0 0x0
#define KID0_SMP1 0x0D
#define KID0_EMGRP1 0x0D

#define KID1 0x10
#define KID1_SMP1 0x1D
#define KID1_EMGRP1 0x1D

#define KID2 0x20
#define KID2_SMP1 0x2D
#define KID2_EMGRP1 0x2D

#define KID3 0x30
#define KID3_SMP1 0x3D
#define KID3_EMGRP1 0x3D

#define SKID 0x90
#define SKID_SMP1 0x9D
#define SKID_EMGRP1 0x9D

#define BUILD_BEAMER_NID(cpu) ((AAS_MODULE << 12) | (BEAMER_BOARD << 8) | ((cpu) & 0xFF))

#define BEAMER_KID0        BUILD_BEAMER_NID(KID0)
#define BEAMER_KID0_SMP1   BUILD_BEAMER_NID(KID0_SMP1)
#define BEAMER_KID0_EMGRP1 BUILD_BEAMER_NID(KID0_EMGRP1)

#define BEAMER_KID1        BUILD_BEAMER_NID(KID1)
#define BEAMER_KID1_SMP1   BUILD_BEAMER_NID(KID1_SMP1)
#define BEAMER_KID1_EMGRP1 BUILD_BEAMER_NID(KID1_EMGRP1)

#define BEAMER_KID2        BUILD_BEAMER_NID(KID2)
#define BEAMER_KID2_SMP1   BUILD_BEAMER_NID(KID2_SMP1)
#define BEAMER_KID2_EMGRP1 BUILD_BEAMER_NID(KID2_EMGRP1)

#define BEAMER_KID3        BUILD_BEAMER_NID(KID3)
#define BEAMER_KID3_SMP1   BUILD_BEAMER_NID(KID3_SMP1)
#define BEAMER_KID3_EMGRP1 BUILD_BEAMER_NID(KID3_EMGRP1)

#define BEAMER_SKID        BUILD_BEAMER_NID(SKID)
#define BEAMER_SKID_SMP1   BUILD_BEAMER_NID(SKID_SMP1)
#define BEAMER_SKID_EMGRP1 BUILD_BEAMER_NID(SKID_EMGRP1)

/* 3DAAS / Active Element -related Node IDs. These are 3DAAS internal NIDs (not sent on wire to SM)
and therefore reservation for 3DAAS does not exclude SM using the same NIDs */

#define AE0_BOARD 0x1
#define AE1_BOARD 0x2
#define AE2_BOARD 0x3
#define AE3_BOARD 0x4

#define ARF0_SMP 0x0D
#define ARF1_SMP 0x1D
#define ARF2_SMP 0x2D
#define ARF3_SMP 0x3D

#define BUILD_AE_NID(board, cpu) ((AAS_MODULE << 12) | ((board & 0xF) << 8) | ((cpu) & 0xFF))

#define AE0_ARF0_SMP BUILD_AE_NID(AE0_BOARD, ARF0_SMP)
#define AE0_ARF1_SMP BUILD_AE_NID(AE0_BOARD, ARF1_SMP)
#define AE0_ARF2_SMP BUILD_AE_NID(AE0_BOARD, ARF2_SMP)
#define AE0_ARF3_SMP BUILD_AE_NID(AE0_BOARD, ARF3_SMP)

#define AE1_ARF0_SMP BUILD_AE_NID(AE1_BOARD, ARF0_SMP)
#define AE1_ARF1_SMP BUILD_AE_NID(AE1_BOARD, ARF1_SMP)
#define AE1_ARF2_SMP BUILD_AE_NID(AE1_BOARD, ARF2_SMP)
#define AE1_ARF3_SMP BUILD_AE_NID(AE1_BOARD, ARF3_SMP)

#define AE2_ARF0_SMP BUILD_AE_NID(AE2_BOARD, ARF0_SMP)
#define AE2_ARF1_SMP BUILD_AE_NID(AE2_BOARD, ARF1_SMP)
#define AE2_ARF2_SMP BUILD_AE_NID(AE2_BOARD, ARF2_SMP)
#define AE2_ARF3_SMP BUILD_AE_NID(AE2_BOARD, ARF3_SMP)

#define AE3_ARF0_SMP BUILD_AE_NID(AE3_BOARD, ARF0_SMP)
#define AE3_ARF1_SMP BUILD_AE_NID(AE3_BOARD, ARF1_SMP)
#define AE3_ARF2_SMP BUILD_AE_NID(AE3_BOARD, ARF2_SMP)
#define AE3_ARF3_SMP BUILD_AE_NID(AE3_BOARD, ARF3_SMP)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GLO_BS_H */


/**
*********************************************************************
*
* SW Block            : Nora BTS / BS Env
*
* Description : GLOBAL BASE STATION DEFINITIONS
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************/

