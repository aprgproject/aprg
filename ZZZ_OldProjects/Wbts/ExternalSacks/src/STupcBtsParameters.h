/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/STupcBtsParameters.h $
* @version               $LastChangedRevision: 2456 $
* @date                  $LastChangedDate: 2015-08-05 14:06:01 +0800 (Wed, 05 Aug 2015) $
* @author                $Author: ancha $
*
* Original author        <nn>
*
* Copyright 2013 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_TUPC_BTS_PARAMETERS_H
#define _S_TUPC_BTS_PARAMETERS_H

#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct STupcBtsParameters
{
    u8                    assocMaxRetrans;
    u8                    pathMaxRetrans;
    u8                    pad1;
    u8                    pad2;
    u32                   validCookieLife;
    u32                   cPlaneDscp;
};
typedef struct STupcBtsParameters STupcBtsParameters;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _S_TUPC_BTS_PARAMETERS_H */

/**
*******************************************************************************
* @struct STupcBtsParameters
*
* Description         : BTS Commissioning parameters
*
* Reference           : BTSOM CPLANE IFS, version 9.0, ShareNet-IMS
*
* @param assocMaxRetrans        : Defines association maximum retransmissions
* @param pathMaxRetrans         : Defines path maximum retransmissions
* @param pad1                   : padding
* @param pad2                   : padding
* @param validCookieLife        : Defines the maximum lifespan of the Cookie
*                                 sent in an INIT/INIT ACK chunk (SCTP).
* @param cPlaneDscp             : Defines the Differentiated Services Code Point (DSCP).
*                                 Valid value for DSCP ranges from 0 to 63 (0-63)
*                                 In case legacy WBTS OAM is in use, cPlaneDscp should be set to NO_VALUE: 0x80000000
*
* Additional Information : RAN1110, RAN1262, RAN1004, CN4271 & CN4216,
*                          RAN1821-m, CN4913
*
* Definition Provided by : WCDMA Control Plane
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

