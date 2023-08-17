/**
*******************************************************************************
* @file                  $HeadURL: http://svne1.access.nokiasiemensnetworks.com/isource/svnroot/BTS_SC_CPLANE_W/dev/echano_mci/tcom/RAN3463SctKnifePhase2_V1/I_Interface/Private/SC_TCOM/Definitions/SHsdpaCellInfo.h $
* @version               $LastChangedRevision: 37397 $
* @date                  $LastChangedDate: 2012-02-22 20:48:10 +0800 (Wed, 22 Feb 2012) $
* @author                $Author: wro01810 $
*
* Original author        Ivan Todorovic
*
* Copyright 2012 Nokia Siemens Networks. All rights reserved.
*******************************************************************************/

#ifndef _S_PIC_CONFIGURATION_H
#define _S_PIC_CONFIGURATION_H

#include <TNumberOfItems.h>
#include <SPicPoolInfo.h>
#include <DOpenIUBCommonDefs.h>


struct SPicConfiguration {

    TNumberOfItems                  nbrOfPicPoolInfo;
    SPicPoolInfo                    picPoolInfo[MAX_NUM_OF_PIC_POOLS];
}; 
typedef struct SPicConfiguration SPicConfiguration;

#endif  /* _S_PIC_CONFIGURATION_H */



/**
*******************************************************************************
* @struct     SPicConfiguration
*
* Description : WCDMA BTS SW Releases Telecom Resource Management Interface Specification
*
* @param nbrOfPicPoolInfo         :    number of PIC pools in configuration
* @param picPoolInfo              :    PIC pool data
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom 
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/
