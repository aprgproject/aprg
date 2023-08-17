/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_GLOBAL/tags/GLOBAL_ENV_13_168/I_Interface/Global_Env/Definitions/EStatus.h $
* @version               $LastChangedRevision: 4650 $
* @date                  $LastChangedDate: 2018-02-22 11:27:34 +0800 (Thu, 22 Feb 2018) $
* @author                $Author: rancastr $
*
* Original author        Haverinen Lasse
*
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _E_STATUS_H
#define _E_STATUS_H

typedef enum EStatus
{
    /* Generic status codes: */
    EStatus_NoError                        = 0,
    EStatus_UndefinedError                 = 1,
    EStatus_UserInSync                     = 2,
    EStatus_UserOutOfSync                  = 3,
    EStatus_InvalidParam                   = 4,
    EStatus_Timeout                        = 5,
    EStatus_Initialized                    = 6,
    EStatus_NotInitialized                 = 7,
    EStatus_Active                         = 8,
    EStatus_InActive                       = 9,
    EStatus_ParallelOperationOngoing       = 10,
    EStatus_DummyUserConfError             = 11, /*RAN 1913*/
    EStatus_CommonEdchResourceConfError    = 12,
    EStatus_CommonEdchFpError              = 13,
    EStatus_CommonEdchResUpdateError       = 14,
    EStatus_NotPresent                     = 15,
    EStatus_CannotRetrieveDeviceParameters = 16, /* LBT2410 */
    EStatus_InvalidDomainId                = 17,
    EStatus_UserDowngradeNotPossible       = 18,

    /* Domain specific status codes: */

    /* ATM specific status codes: */

    /* TCOM specific status codes: */
    EStatus_ErroneusValueInMessage         = 300,
    EStatus_CellIdAlreadyInUse             = 301,
    EStatus_NoSpaceForCell                 = 302,
    EStatus_UnknownCellID                  = 303,
    EStatus_LinkOutOfService               = 304,
    EStatus_ErroneusCellState              = 305,
    EStatus_CellNotConfigured              = 306,
    EStatus_NoWspResources                 = 307,
    EStatus_NoResponseFromCoPro            = 308,
    EStatus_FeatureAlreadyActivated        = 309,
    EStatus_WspcPpcLoadLimitAdjusted       = 310,
    EStatus_PseudoLoadAdjusted             = 311,
    EStatus_UnknownAtmMcu                  = 312,
    EStatus_UnknownWspId                   = 313,
    EStatus_UnknownAal2Id                  = 314,
    EStatus_UserRemovalFailure             = 315,
    EStatus_CellRemovalFailure             = 316,

    /* O&M specific status codes: */
    EStatus_RbusSynchronizationFailure     = 400,
    EStatus_ResourceUnavailable            = 401,
    EStatus_HibernationFailure             = 402,

    /* Baseband specific status codes: */
    EStatus_BB_AlreadyActivated            = 0x8001,
    EStatus_BB_NotActivated                = 0x8002,
    EStatus_BB_MeasurementFailure          = 0x8003,

    /* WTR specific status codes: */
    EStatus_WTR_NotInitialised             = 0x9001,
    EStatus_WTR_InvalidFrequencyBand       = 0x9002,
    EStatus_WTR_ChannelIsBarred            = 0x9003,

    /* RFSW specific status codes: */
    EStatus_RFSW_MeasurementFailure        = 0xA001

    /* WPA specific status codes: */

    /* any more??? */
} EStatus;

#endif /* _E_STATUS_H */

/**
*******************************************************************************
* @enum EStatus
*
* Description         : Status codes used in WTR initialization/configuration procedures
*
* Reference           : WTR_WAM_IF_SPEC, 0.0.25, PVCS: HELENA_XENA_COMMON_WS
*
* Parameters:
*
* @param EStatus_NoError :
* @param EStatus_UndefinedError :
* @param EStatus_UserInSync :
* @param EStatus_UserOutOfSync :
* @param EStatus_InvalidParam :
* @param EStatus_Timeout :
* @param EStatus_Initialized :
* @param EStatus_NotInitialized :
* @param EStatus_Active :
* @param EStatus_InActive :
* @param EStatus_ParallelOperationOngoing :
* @param EStatus_DummyUserConfError :
* @param EStatus_CommonEdchResourceConfError :
* @param EStatus_CommonEdchFpError :
* @param EStatus_CommonEdchResUpdateError :
* @param EStatus_NotPresent :
* @param EStatus_InvalidDomainId :
* @param EStatus_UserDowngradeNotPossible:
* @param EStatus_ErroneusValueInMessage :
* @param EStatus_CellIdAlreadyInUse :
* @param EStatus_NoSpaceForCell :
* @param EStatus_UnknownCellID :
* @param EStatus_LinkOutOfService :
* @param EStatus_ErroneusCellState :
* @param EStatus_CellNotConfigured :
* @param EStatus_NoWspResources :
* @param EStatus_NoResponseFromCoPro :
* @param EStatus_FeatureAlreadyActivated :
* @param EStatus_WspcPpcLoadLimitAdjusted :
* @param EStatus_PseudoLoadAdjusted :
* @param EStatus_UnknownAtmMcu :
* @param EStatus_UnknownWspId :
* @param EStatus_UnknownAal2Id :
* @param EStatus_UserRemovalFailure :
* @param EStatus_CellRemovalFailure :
* @param EStatus_RbusSynchronizationFailure :
* @param EStatus_ResourceUnavailable :
* @param EStatus_HibernationFailure :
* @param EStatus_BB_AlreadyActivated :
* @param EStatus_BB_NotActivated :
* @param EStatus_BB_MeasurementFailure :
* @param EStatus_WTR_NotInitialised :
* @param EStatus_WTR_InvalidFrequencyBand :
* @param EStatus_WTR_ChannelIsBarred :
* @param EStatus_RFSW_MeasurementFailure :
*
* Additional Information    : -
*
* Definition Provided by    : WTR
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

