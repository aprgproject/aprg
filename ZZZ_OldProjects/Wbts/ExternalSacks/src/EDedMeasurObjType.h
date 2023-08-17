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

#ifndef _EDEDMEASUROBJTYPE_H
#define _EDEDMEASUROBJTYPE_H

typedef enum EDedMeasurObjType {
    EDedMeasurObjType_RL    =0,
    EDedMeasurObjType_RLS   =1,
    EDedMeasurObjType_ALLRL =2,
    EDedMeasurObjType_ALLRLS=3
} EDedMeasurObjType;

#endif /* EDEDMEASUROBJTYPE_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env / Definitions
*
* Description : 9.2.1.22 Dedicated Measurement Object Type.
*
* Reference   : 3GPP TS 25.433 v4.1.0
*
*               "The Dedicated Measurement Object type indicates the
*                type of object that the measurement is to be performed on."
*
* Provider : Telecom / Jesse Pasuri / Mika Hautala
*
************************************************************************/



