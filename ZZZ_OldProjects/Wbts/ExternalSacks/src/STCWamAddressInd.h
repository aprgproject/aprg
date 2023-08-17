/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Original author        Mika Hiltunen
*
* Copyright 2012 Nokia Siemens Networks. All rights reserved.
*******************************************************************************/

#ifndef _S_TC_WAM_ADDRESS_IND_H
#define _S_TC_WAM_ADDRESS_IND_H

#include <DOpenIUBCommonDefs.h>
#include <EBoolean.h>
#include <SMessageHeader.h>
#include <STcomInstance.h>
#include <TAaSysComSicad.h>
#include <TNumberOfItems.h>

struct STCWamAddressInd
{
    MESSAGEHEADER(msgHeader)
    EBoolean        isSbts;
    TAaSysComSicad  oamSubscriberSicad;
    TAaSysComSicad  lmsSicad;
    TAaSysComSicad  tupConmanSicad;
    TAaSysComSicad  cnbapTupAalmanSicad;
    TAaSysComSicad  dnbapTupAalmanSicad;
    TNumberOfItems  numOfTcomInstances;
    STcomInstance   tcomInstances[MAX_NUM_OF_CONTROL_UNITS];
    EBoolean        isEndiannessConversionNeeded;
};
typedef struct STCWamAddressInd STCWamAddressInd;

#endif /* _S_TC_WAM_ADDRESS_IND_H */

/**
*******************************************************************************
* @struct STCWamAddressInd
*
* Description : Used to pass WAM address information from a process to another
*               at the TelecomSW.
*
* Reference   : https://confluence.int.net.nokia.com/display/CpPta/Explicit+addresses+in+TC_WAM_ADDRESS_IND_MSG
*
* @param msgHeader                    : Message header.
* @param isSbts                       : Indicates If BTS configuration is SBTS.
* @param oamSubscriberSicad           : The SICAD of OAM Subscriber that is used
*                                       as recipient for TCOM-originated messages.
* @param lmsSicad                     : The SICAD of License Management Service in OAM
* @param tupConmanSicad               : The SICAD of TUP Conman that is used as
*                                       recipient for TCOM-originated messages.
* @param cnbapTupAalmanSicad          : The SICAD of CNBAP TUP Aalman that is used
*                                       as recipient for TCOM-originated messages.
* @param dnbapTupAalmanSicad          : The SICAD of DNBAP TUP Aalman that is used
*                                       as recipient for TCOM-originated messages.
* @param numOfTcomInstances           : Number of active TCOM instances.
* @param tcomInstances                : Array of active TCOM instances.
* @param isEndiannessConversionNeeded : Indicates if endianness change is needed for OAM messages.
*
* Additional Information :
*
* Definition Provided by : Telecom
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/
