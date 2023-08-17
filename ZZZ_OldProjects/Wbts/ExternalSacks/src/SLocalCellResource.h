/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SLocalCellResource.h $
* @version               $LastChangedRevision: 2890 $
* @date                  $LastChangedDate: 2019-07-19 07:06:00 +0800 (Fri, 19 Jul 2019) $
* @author                $Author: iyee $
*
* Original author        <nn>
*
* Copyright 2013 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _S_LOCAL_CELL_RESOURCE_H
#define _S_LOCAL_CELL_RESOURCE_H

#include <EDssType.h>
#include <EExpirationTimeFactor.h>
#include <EHspaMapping.h>
#include <EState.h>
#include <glo_def.h>
#include <SDssWcdmaLteCommissioningParametersForFilter.h>
#include <SLcrEirpControlParameters.h>
#include <TAdditionalFlags.h>
#include <TCellPowerMaximum.h>
#include <TCellRadius.h>
#include <TLocalCellGroupId.h>
#include <TLocalCellResId.h>
#include <TNumberOfItems.h>
#include <TPowerLevel.h>
#include <TRachThroughput.h>
#include <TShutdownStepAmount.h>
#include <TShutdownWindow.h>
#include <TUARFCN.h>

struct SLocalCellResource
{
    TLocalCellResId                              localCellResourceId;
    TLocalCellGroupId                            localCellGroupId;
    EState                                       initialLcrState;
    TCellPowerMaximum                            upperLimitForPaMaxOutputPower;
    TCellRadius                                  cellRadius;
    TRachThroughput                              rachThroughput;
    TShutdownWindow                              shutdownWindow;
    TShutdownStepAmount                          shutdownStepAmount;
    EExpirationTimeFactor                        expirationTimeFactor;
    TUARFCN                                      defaultCarrierDlUarfcn;
    EHspaMapping                                 hspaMapping;
    TNumberOfItems                               numberOfTxResources;
    TNumberOfItems                               numberOfRxResources;
    TPowerLevel                                  maxRxPowerDifferenceThreshold;
    EDssType                                     dssType;
    SDssWcdmaLteCommissioningParametersForFilter dssWcdmaLteCommissioningParametersForFilter;
    SLcrEirpControlParameters                    eirpControlParameters;
    TAdditionalFlags                             additionalFlags;
};
typedef struct SLocalCellResource SLocalCellResource;

#endif /* _S_LOCAL_CELL_RESOURCE_H */

/**
*******************************************************************************
* @struct SLocalCellResource
*
* Description : Structure used in message SHwConfigurationMsg and SHwConfigurationChangeMsg
*
* Reference : OAM CPlane Interface Specification
*
* Parameters :
*
* @param localCellResourceId                          : LCR ID
*
* @param localCellGroupId                             : LCR group ID
*
* @param initialLcrState                              : Initial LCR state (enabled(default)/disabled)
*
* @param upperLimitForPaMaxOutputPower                : Upper limit for PA max output power
*
* @param cellRadius                                   : Cell radius
*
* @param rachThroughput                               : RACH throughput
*
* @param shutdownWindow                               : Shutdown procedure duration in seconds
*
* @param shutdownStepAmount                           : Shutdown step amount
*
* @param expirationTimeFactor                         : Expiration time factor
*
* @param defaultCarrierDlUarfcn                       : Default carrier DL UARFCN - value of the parameter comes from
*                                                       BTS commissioning (SCF parameter "LCELW/defaultCarrier")
*
* @param hspaMapping                                  : Indicates how HSPA local cells are mapped to
                                                        baseband HW resources
*
* @param numberOfTxResources                          : Number of TX carrier resources commissioned for LCR
*
* @param numberOfRxResources                          : Number of RX carrier resources commissioned for LCR
*
* @param maxRxPowerDifferenceThreshold                : Max rx power difference threshold for LCR
*
* @param dssType                                      : DSS type for the LCR
*
* @param dssWcdmaLteCommissioningParametersForFilter  : Commissioning filter parameters for WCDMA+LTE Dynamic Spectrum Sharing (DSS)
*
* @param eirpControlParameters                        : Commissioning parameters for EIRP control
*
* @param additionalFlags                              : Bit container for additional flags for LCR
*                                                       The enum ELcrInfoAdditionalFlagsBitPosition indicates the mapping for each bit in the bit container.
*
* Additional Information : WBTS_CP_13301
*
* Definition Provided by : Telecom / Mika Kauppinen / Toni Kyllonen / Margus Metsanurm
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
********************************************************************************/

