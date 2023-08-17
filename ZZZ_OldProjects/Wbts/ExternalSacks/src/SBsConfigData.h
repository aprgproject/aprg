/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SBsConfigData.h $
* @version               $LastChangedRevision: 2770 $
* @date                  $LastChangedDate: 2018-07-24 18:10:00 +0800 (Tue, 24 Jul 2018) $
* @author                $Author: echano $
*
* Original author        Bartosz Ciesla
*
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_BS_CONFIG_DATA_H
#define _S_BS_CONFIG_DATA_H

#include <DOpenIUBCommonDefs.h>
#include <EMaximumNbrOfHsdpaUsers.h>
#include <ENumOfHsdpaSchedulers.h>
#include <glo_def.h>
#include <IfAaSysComGw.h>
#include <SDelayedLinksInfo.h>
#include <SDssLinksInfo.h>
#include <SHibernationConfiguration.h>
#include <SHsdpaSchedulerInfo.h>
#include <SLcgInfo.h>
#include <SOptimizedHsdpaSchedulingConfiguration.h>
#include <SPicConfiguration.h>
#include <SSpiSchedulingWeightList.h>
#include <SUeTracingConfiguration.h>
#include <TAdditionalFlags.h>
#include <TNodeBId.h>
#include <TNumberOfItems.h>
#include <TSbtsId.h>
#include <TTransportLayerAddress.h>

struct SBsConfigData
{
    ENumOfHsdpaSchedulers                  nbrOfHsdpaSchedulerInfo;
    SHsdpaSchedulerInfo                    hsdpaSchedulerInfo[ENumOfHsdpaSchedulers_12];
    TTransportLayerAddress                 transportLayerAddress;
    TSbtsId                                sbtsId;
    TNumberOfItems                         nbrOfLcg;
    SLcgInfo                               lcgInfo[MAX_LOCAL_CELL_GROUP_IN_NODEB];
    SSpiSchedulingWeightList               spiSchedulingWeightList;
    TNumberOfItems                         hsdpaUsers;
    TNumberOfItems                         hsupaUsers;
    SUeTracingConfiguration                ueTracingConfiguration;
    TNodeBId                               nodeBID;
    EAaSysComGwIpVer                       btsIpAddressVersion;
    char                                   mPlaneIpAddress[AASYSCOM_GW_IP_ADDRESS_MAX_STR_LEN];
    SHibernationConfiguration              hibernationConfiguration;
    SPicConfiguration                      picConfiguration;
    TNumberOfItems                         numberOfDelayedLinksInfo;
    SDelayedLinksInfo                      delayedLinksInfo[MAX_NUM_OF_DELAYED_LINKS_INFO];
    TNumberOfItems                         numberOfDssLinksInfo;
    SDssLinksInfo                          dssLinksInfo[MAX_NUM_OF_DSS_LINKS_INFO];
    TAdditionalFlags                       btsCommissioningFlags;
    SOptimizedHsdpaSchedulingConfiguration optimizedHsdpaSchedulingConfiguration;
};
typedef struct SBsConfigData SBsConfigData;

#endif /* _S_BS_CONFIG_DATA_H */

/**
*******************************************************************************
* @struct SBsConfigData
*
* Description : BsConfigData section in TC_HW_CONFIGURATION_MSG
*
* Reference   : OAM CPlane Interface specification
*
* Parameters  :
*
* @param nbrOfHsdpaSchedulerInfo               : The number of valid hsdpaSchedulerInfo instances in the message.
*
* @param hsdpaSchedulerInfo                    : A list containing hsdpaSchedulerInfo instances.
*
* @param transportLayerAddress                 : The transport layer address for BTS.
*
* @param sbtsId                                : The Single Ran BTS Identifier. NO_VALUE should be used for WCDMA BTS.
*
* @param nbrOfLcg                              : The number of valid lcgInfo instances in the message.
*
* @param lcgInfo                               : A list containing lcgInfo instances.
*
* @param spiSchedulingWeightList               : A list of all SPI scheduling weight class values defined in commissioning.
*
* @param hsdpaUsers                            : The maximum number of HSDPA users allowed by TCOM
*                                                Possible values: 0, 1, 2, ... 516779, and NO_VALUE
*                                                If value is NO_VALUE, TCOM should consider users from HSDPA Processing Sets
*
* @param hsupaUsers                            : The maximum number of HSUPA users allowed by TCOM
*                                                Possible values: 0, 1, 2, ... 2375, and NO_VALUE
*                                                If value is NO_VALUE, TCOM should consider users from HSUPA Processing Sets
*
* @param ueTracingConfiguration                : The configuration for UE tracing.
*
* @param nodeBID                               : The BTS Id.
*
* @param btsIpAddressVersion                   : The IP version of the M-Plane IP Address.
*
* @param mPlaneIpAddress                       : The M-Plane IP Address. This field must always end with a null terminating character.
*
* @param hibernationConfiguration              : The hibernation configuration.
*
* @param picConfiguration                      : The PIC configuration.
*
* @param numberOfDelayedLinksInfo              : The number of SDelayedLinksInfo instances in the message.
*
* @param delayedLinksInfo                      : A list containing SDelayedLinksInfo instances.
*
* @param numberOfDssLinksInfo                  : The number of SDssLinksInfo instances in the message.
*
* @param dssLinksInfo                          : A list containing SDssLinksInfo instances.
*
* @param btsCommissioningFlags                 : Bit container for additional flags for BTS commissioning.
*                                                The enum EBtsCommissioningFlagsBitPosition indicates the mapping for each bit in the bit container.
*
* @param optimizedHsdpaSchedulingConfiguration : The configuration for optimized hsdpa scheduling.
*
* Additional Information :
*
* Definition Provided by : TCOM / Bartosz Ciesla
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

