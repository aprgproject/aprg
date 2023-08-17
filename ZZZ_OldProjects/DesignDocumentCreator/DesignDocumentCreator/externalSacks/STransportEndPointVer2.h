/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/STransportEndPointVer2.h $
* @version               $LastChangedRevision: 2561 $
* @date                  $LastChangedDate: 2016-02-29 10:41:45 +0800 (Mon, 29 Feb 2016) $
* @author                $Author: sazon $
*
* Original author        Mikhail Sazon
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _STRANSPORT_END_POINT_VER2_H
#define _STRANSPORT_END_POINT_VER2_H

#include <TTransportIdentifier.h>
#include <TTransportLayerAddress.h>

struct STransportEndPointVer2
{
    TTransportLayerAddress    ipAddress;
    TTransportIdentifier      port;
};
typedef struct STransportEndPointVer2 STransportEndPointVer2;

#endif /* _STRANSPORT_END_POINT_VER2_H */

/**
*******************************************************************************
* @struct STransportEndPointVer2
*
* Description : Type definition for transport identifier. Transport
*               identifier is in Nora Connection Idendifier (CID).
*               In Flexi it is UDP-port.
*
* Reference   : http://omcpservices.wroclaw.nsn-rdnet.net/DokuWiki/WikiCP/doku.php?id=ran3313
*
* Parameters :
*
* @param ipAddress   :   IP address in NSAP format (Refer to RFC-RFC-4548)
*
* @param port   :  UDP port (Flexi) or AAL2 CID (Nora)
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TUP
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

