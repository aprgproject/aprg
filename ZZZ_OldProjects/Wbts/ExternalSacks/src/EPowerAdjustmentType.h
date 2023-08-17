/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_WN/tags/WBTS00_ENV_1910_001_00/I_Interface/Application_Env/Wn_Env/Bs_Env/Definitions/EPowerAdjustmentType.h $
* @version               $LastChangedRevision: 4180 $
* @date                  $LastChangedDate: 2014-06-25 21:50:07 +0800 (Wed, 25 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
*
* Original author        <nn>
*
* Copyright 2011 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _EPOWERADJUSTMENTTYPE_H
#define _EPOWERADJUSTMENTTYPE_H

typedef enum EPowerAdjustmentType {
    EPowerAdjustmentType_None       =0,
    EPowerAdjustmentType_Common     =1,
    EPowerAdjustmentType_Individual =2
} EPowerAdjustmentType;

#endif /* _EPOWERADJUSTMENTTYPE_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : 9.2.2.27 Power Adjustment Type.
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
* IE Type and Reference:  ENUMERATED (None, Common, Individual)
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/



