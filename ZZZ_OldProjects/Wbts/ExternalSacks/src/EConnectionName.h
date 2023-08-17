/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EConnectionName.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef ECONNECTIONNAME_H
#define ECONNECTIONNAME_H

typedef enum
{
                  /* per each WAM unit*/
  EConnectionName_CNBAP =  1,         /* SAAL connections towards RNC*/
  EConnectionName_DNBAP =  2,
  EConnectionName_AAL2S =  3,
  EConnectionName_WamP1 =  4,         /* WAM protocol (API) connections between WAMs*/
  EConnectionName_WamP2 =  5,         /*    -- (RULE: "ascending WAM number"!!) --*/
  EConnectionName_WamP3 =  6,
  EConnectionName_WamP4 =  7,
  EConnectionName_WamP5 =  8,
  EConnectionName_AxuIP =  9,         /* IP over ATM connection to "AXU SAR VCC"*/
  EConnectionName_IPoA1 = 10,         /* IP over ATM connections between WAMs*/
  EConnectionName_IPoA2 = 11,         /*    -- (RULE: "ascending WAM number"!!) --*/
  EConnectionName_IPoA3 = 12,
  EConnectionName_IPoA4 = 13,
  EConnectionName_IPoA5 = 14,
  EConnectionName_TLoop = 15,         /* "AXU Loop VCC", test loop connection*/
  EConnectionName_AAL2a = 16,         /* User Plane AAL2 connections*/
  EConnectionName_AAL2b = 17,         /*    -- (RULE: "ascending MCU number"!!) --*/
  EConnectionName_AAL2c = 18,         /* (reservation)*/
  EConnectionName_AAL2d = 19,         /* (reservation)*/
  EConnectionName_Wsmf1 = 20,         /* EUBB - WSMF 1 (Ultra) */
  EConnectionName_Wsmf2 = 21          /* EUBB - WSMF 2 (Ultra) */
} EConnectionName;

#endif /* ECONNECTIONNAME_H */

/**
*******************************************************************************
* @enum EConnectionName
*
* Description  : ATM connections
*
* Reference   : TUP IFS 15.0
*
* Parameters  :
*
* @param EConnectionName_CNBAP :
* @param EConnectionName_DNBAP :
* @param EConnectionName_AAL2S :
* @param EConnectionName_WamP1 :
* @param EConnectionName_WamP2 :
* @param EConnectionName_WamP3 :
* @param EConnectionName_WamP4 :
* @param EConnectionName_WamP5 :
* @param EConnectionName_AxuIP :
* @param EConnectionName_IPoA1 :
* @param EConnectionName_IPoA2 :
* @param EConnectionName_IPoA3 :
* @param EConnectionName_IPoA4 :
* @param EConnectionName_IPoA5 :
* @param EConnectionName_TLoop :
* @param EConnectionName_AAL2a :
* @param EConnectionName_AAL2b :
* @param EConnectionName_AAL2c :
* @param EConnectionName_AAL2d :
* @param EConnectionName_Wsmf1 :
* @param EConnectionName_Wsmf2 :
*
* Additional Information :
*
*  WN6.0: names EConnectionName_Wsmf1 and EConnectionName_Wsmf2 added for
*         Eubb support in Ultra. The connection names "Wsmf1" and "Wsmf2"
*         use the same WAM-WAM protocol (at WAM side of the connection) as
*         the WamP1...WamP5. They have their own p2p ATM VCCs (with the
*         shown names) which are statically always present in the HW
*         configuration message even in the case there is no EUBB boards
*         HW installed in the BTS (see WAM AXU IFS).
*
* Definition Provided by : TUP / KVAKEVA
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/


