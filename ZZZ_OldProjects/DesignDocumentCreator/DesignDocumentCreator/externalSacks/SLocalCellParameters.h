/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SLocalCellParameters.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef SLOCALCELLPARAMETERS_H
#define SLOCALCELLPARAMETERS_H

#include <TLocalCellResId.h>
#include <TCellRadius.h>
#include <TRachThroughput.h>
#include <TShutdownWindow.h>
#include <TShutdownStepAmount.h>
#include <TExprTimeFactor.h>
#include <TPrxAlpha.h>
#include <TPtxAlpha.h>
#include <TPrxAveMeasWindow.h>
#include <TPtxAveMeasWindow.h>
#include <EBoolean.h>

struct SLocalCellParameters
{
    TLocalCellResId     lcrId;
    TCellRadius         cellRadius;
    TRachThroughput     rachThroughput;
    TShutdownWindow     shutdownWindow;
    TShutdownStepAmount shutdownStepAmount;
    EBoolean            exprTimeFactorIePresent;
    TExprTimeFactor     exprTimeFactor;
    EBoolean            prxAlphaIePresent;
    TPrxAlpha           prxAlpha;
    EBoolean            ptxAlphaIePresent;
    TPtxAlpha           ptxAlpha;
    TPrxAveMeasWindow   prxAveMeasWindow;
    TPtxAveMeasWindow   ptxAveMeasWindow;
};
typedef struct SLocalCellParameters SLocalCellParameters;

#endif /* SLOCALCELLPARAMETERS_H */

/**
*******************************************************************************
* @struct SLocalCellParameters
*
* Description : Structure used in message SLocalCellParametersIndMsg
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param lcrId                   : Local cell resource ID identifies cell.
* @param cellRadius              : Cell radius, range is from 1 to 5000.
* @param rachThroughput          : Rach capacity, range is 1 to 120.
* @param shutdownWindow          : Time how long shutdown procedure takes. NOTE! This parameter is
*                                  present only when shutdownStepAmount has a valid value.
* @param shutdownStepAmount      : Number of steps. Range 1 to 16.
* @param exprTimeFactorIePresent : If 'True' exprTimeFactor contains valid value
* @param exprTimeFactor          : Expiration time factor in SIB7. Range 0 to 8 (This is optional parameter in SIB7 so '0' means 'Not Present')
* @param prxAlphaIePresent       : If 'True' then prxAlpha contains valid value.
* @param prxAlpha                : Range from 0 to 10
* @param ptxAlphaIePresent       : If 'True' then ptxAlpha contains valid value.
* @param ptxAlpha                : Range from 0 to 10
* @param prxAveMeasWindow        : Range from 10 to 200
* @param ptxAveMeasWindow        : Range from 10 to 200
*
* Additional Information :
*  If paramters value is zero then it means that parameter value is not present. Note that with prxAlpha and
*  ptx ptxAlpha zero is valid value so prxAlphaIePresent and ptxAlphaIePresent fields are used to indicate
*  presence of parameter.
*
* Definition Provided by : Petri Nasi
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

