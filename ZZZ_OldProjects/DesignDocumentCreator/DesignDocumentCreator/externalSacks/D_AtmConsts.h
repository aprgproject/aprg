/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/D_AtmConsts.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _DATMCONSTS_H
#define _DATMCONSTS_H

#include <DOpenIUBCommonDefs.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ATM End System Address  size (in octets), of any format*/
#define AESA_SIZE 20

/*AFI, value of octet[0] in SxxxAesaFormat, the "Authority and Format Identifier"*/
#define DCCAESAFORMAT_C 0x39    /* (AFI == DCC AESA)*/
#define ICDAESAFORMAT_C 0x47    /* (AFI==ICD AESA)*/
#define E164AESAFORMAT_C 0x45   /* (AFI==E.164 AESA)*/
#define LOCALAESAFORMAT_C 0x49  /* (AFI==Local ATM format)*/

/* ATM Connections Adaptation Layer Termination Point location Identifier (data type TMcuNumber)*/
#define AAL_TP_ATMHOST  0
#define AAL_TP_ATM1_MCU 1
#define AAL_TP_ATM2_MCU 2
#define AAL_TP_ATM3_MCU 3
#define AAL_TP_ATMUX    0xFF /* for type TMcuNumber (==AAL2 VCC with ATMUX AAL2 processing enabled)*/

#define AALM_ATM_ARPTBL_SIZE    12
#define AALM_ETH_ARPTBL_SIZE    24

/* Maximum number of serial ports in UX-ASIC*/
/*const u32 UX_serMax_C     = 5;*/
#define UX_SER_MAX 5

/* Test Loop Fp Setup constants*/
#define MAX_NUM_TEST_DCH 3

/*Testability constants*/
#define ALL_CELLS           (MAX_CELL_ID+1)
#define ALL_FP_INSTANCES    AAL_TP_ATMUX

/* Flexi BTS definitions*/
#define MAX_NUM_FSP 6
#define MAX_NUM_TUP_CPU_IN_FSP 3

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DATMCONSTS_H */

/**
*******************************************************************************
* Description  : Constant definitions (from ATM)
*
* Reference   : ATM CTRL MCUS IF SPEC, 5.0, PI
*
* Parameters  :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : ATM / Kari Vakeva
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

