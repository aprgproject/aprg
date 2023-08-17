/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
*
* Copyright (c) Nokia 2007. All rights reserved.
*******************************************************************************/

#ifndef _SFSPINFORMATION_H
#define _SFSPINFORMATION_H

#include <TTransportPathIdentifier.h>
#include <SMessageAddress.h>
#include <TTransportIdentifier.h>
#include <EWspType.h>
#include <EBoolean.h>

typedef struct SFspInformation
{
     TTransportPathIdentifier   ipAddress;
     SMessageAddress            messageAddress;
     TTransportIdentifier       udpPortMinimum;
     TTransportIdentifier       udpPortMaximum;
     EWspType                   fspType;
     EBoolean                   isReady;
} SFspInformation;

#endif /* _SFSPINFORMATION_H */

/**
*******************************************************************************
* @struct SFspInformation
* Development Workset : WCDMA:BS_ENV_WS
*
* Design Part         : <type design part name here>
*
* Description         : Flexi FSP information for TUP configuration.
*
* Reference           : ATM CTRL MCUS IF SPEC, 13.0, PI
*
* @param ipAddress : The IP address of the FSP.
* @param messageAddress : NMAP address of the FSP
* @param udpPortMinimum : First of the available (user plane) UDP port numbers that are not reserved for something else.
* @param udpPortMaximum : Last of the available UDP port numbers.
* @param fspType : Type of the board.
* @param isReady : Status: Is it allowed to send messages to the board?
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : TUP / KVAKEVA
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/


