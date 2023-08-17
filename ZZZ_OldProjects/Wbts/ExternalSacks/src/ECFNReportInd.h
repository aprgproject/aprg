/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Original author        <nn>
*
* Copyright 2012 Nokia Siemens Networks. All rights reserved.
*******************************************************************************/

#ifndef _ECFNREPORTIND_H
#define _ECFNREPORTIND_H

typedef enum ECFNReportInd {
    ECFNReportInd_FNReportingRequired=0,
    ECFNReportInd_FNReportingNotRequired=1
} ECFNReportInd;

#endif /* ECFNREPORTIND_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : 9.2.1.29B FN reporting indicator.
*
* Reference   : 3GPP TS 25.433 v4.3.0
*
*               "Frame Number reporting indicator.
*                Indicates if the SFN or CFN shall be included together
*                with the reported measurement value."
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/



