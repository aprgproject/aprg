/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/DFromTc_dsp.h $
* @version               $LastChangedRevision: 2589 $
* @date                  $LastChangedDate: 2016-05-30 17:11:42 +0800 (Mon, 30 May 2016) $
* @author                $Author: hxkv68 $
*
* Original author        <nn>
*
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _DFROM_TC_DSP_H
#define _DFROM_TC_DSP_H

#define NO_VALUE                                0x80000000
#define NO_VALUE_FOR_ENUMS                      0xffff
#define EXECUTE_IMMEDIATELY                     0xfff0
#define SFN_EXECUTE_IMMEDIATELY                 EXECUTE_IMMEDIATELY
#define DEACTIVATED_INITIAL_STATE               0xfff1

#define MAX_NUM_OF_UL_CHAN_CODES                8
#define MAX_NUM_OF_DL_CHAN_CODES                8
#define MAX_NUMBER_OF_CODE_CHANNELS_PER_USER    1
#define RADIO_FRAME_CYCLE                       4096
#define SLOTS_IN_FRAME                          15
#define CHIPS_IN_SLOT                           2560
#define MAX_DCH_IN_DPDCH                        8
#define MAX_NUM_OF_DCH                          8
#define MAX_NUMBER_OF_SECTORS                   6
#define MAX_NUMBER_OF_SECTORS_IN_CELL           6
#define MAX_NUMBER_OF_RADIUS_SPLIT              4
#define MAX_NUM_OF_WTR_OF_SECTOR                2
#define CHIPS_PER_SLOT                          CHIPS_IN_SLOT
#define MAX_FRAME_NUMBER                        (RADIO_FRAME_CYCLE - 1)
#define MAX_DL_TX_PWR_AVE_WINDOW_LENGTH         60
#define AVERAGE_MEASURED_UPLINK_SIR_VALUES      64
#define MAX_NUMBER_OF_USERS_TO_BTS_REPORT       20
#define MAX_NUMBER_OF_CM_SEQUENCES              4
#define MAX_CLUSTER_FRACT_IN_SPLIT_DECODING     2
#define MAX_NUM_OF_PIC_CODEC                    16
#define UE_TRACING_SYNCH_ID                     0x0A0B0C0D
#define UE_TRACING_TRACE_SESSION                0x12
#define UE_TRACING_VERSION                      0x11000000
#define UE_TRACING_TRACE_TYPE                   0x12
#define UE_TRACING_LINK_AND_ITF_NAME            0x00
#define UE_TRACING_PROT_MSG_TYPE                0xFFFF
#define UE_TRACING_VALUE_LSB                    0
#define UE_TRACING_VALUE_MSB                    0xFFFFFF
#define UE_TRACING_CORRELATION_INFO             0

#endif /* _DFROM_TC_DSP_H */

/**
*******************************************************************************
* @brief
* Development Workset : WCDMA:BS_ENV_WS
*
* Description         : Defines constants for TCOM - DSP interface.
*                       NOTE: DOpenIUBCommonDefs.h defines constants which are
*                       added in WN21!
*
* Reference           : DSP SW - MCU SW Interface Specification
*                       Link to PI:
*                       espoo11/Projects/WCDMA RAN/WCDMA BTS/WBTS3.x/
*                       2 Technical Management/Specification/Specification
*                       Documents/IFS
*
* @param MAX_NUMBER_OF_CODE_CHANNELS_PER_USER : In Nora WN 1.1 Multicode not
*                                               supported.
* @param MAX_NUMBER_OF_SECTORS                : Here the assumption is that one
*                                               cell one sector?
*                                               Comment 25.03.2002 JuM.
* @param MAX_NUMBER_OF_SECTORS_IN_CELL        : This make possible to have more
*                                               than one sector in cell e.g.
*                                               ROC mode. 25.03.2002 JuM.
* @param MAX_NUMBER_OF_RADIUS_SPLIT           : This tell how many Rach channels
*                                               is needed with same Id to cover
*                                               whole cell. 25.03.2002 JuM.
* @param MAX_NUM_OF_PIC_CODEC                 : defines maximum number of Codec
*                                               Devices PIC handles in FSMr2 SM
*
* Additional Information : N/A
*
* Definition Provided by : DSP, Kari Korvela
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

