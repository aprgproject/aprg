/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/SDchInfo_Ver2.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        Jukka Sakkinen
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_DCH_INFO_VER2_H
#define _S_DCH_INFO_VER2_H

#include <EFpPayloadCrc.h>
#include <EUlFpMode.h>
#include <TFpToaw.h>
#include <ETransportBearReqInd.h>
#include <TNumberOfItems.h>
#include <TDynamicData.h>

struct SDchInfo_Ver2
{
    EFpPayloadCrc               payloadCrcPresenceInd;
    EUlFpMode                   ulFpMode;
    TFpToaw                     toAws;
    TFpToaw                     toAwe;
    ETransportBearReqInd        transportBearerRequestInd;
    TNumberOfItems              numOfDchSpecificInfo;
    TDynamicData                dynamicData[1];
};
typedef struct SDchInfo_Ver2 SDchInfo_Ver2;

#endif /* _S_DCH_INFO_VER2_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env
*
* Description : DCH info provides information for DCHs existing after
*               BB_2_RlSetupReq.
*
* Reference   : WCDMA BTS RELEASES BTS RELEASE PROGRAMS
*               DSP SW - MCU SW INTERFACE SPECIFICATION
*
* Parameters  :
*
********************************************************
*    Static part                                       *
********************************************************
*
*   payloadCrcPresenceInd           Indicates whether FP payload 16 bit CRC is
*                                   used or not.
*
*   ulFpMode                        The DCH Frame Protocol mode that shall be
*                                   used on the transport bearer.
*
*   toAws                           TOAWS (Time of Arrival Window Startpoint)
*                                   is the window startpoint.
*
*   toAwe                           TOAWE (Time of Arrival Window Endpoint)
*                                   is the window endpoint.
*
*   transportBearerRequestInd       Indicates whether a new transport bearer needs
*                                   to be established for carrying the concerned
*                                   transport channel.
*
*   numOfDchSpecificInfo            Defines number of Dch specific info structs
*                                   in dynamicData.
*
*******************************************
*    Dynamic part
*******************************************
*
*   Content of the dynamic part:
*   SDchSpecificInfo                Provides DCH specific information. Must be
*                                   present as many times as set to the
*                                   numOfDchSpecificInfo in the static part of
*                                   this struct.
*
* Provider : DSP
*
* Remember to put an empty line in the end of each definition
* file. Otherwise the compiler will generate a warning.
************************************************************************/


