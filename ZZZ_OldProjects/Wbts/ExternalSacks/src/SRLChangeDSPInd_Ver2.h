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

#ifndef SRLCHANGEDSPIND_VER2_H
#define SRLCHANGEDSPIND_VER2_H

#include <SMessageHeader.h>
#include <TUserId.h>
#include <SMessageAddress.h>
#include <TSfn.h>

struct SRLChangeDSPInd_Ver2
{
    MESSAGEHEADER(msgHeader)
    TUserId                 userId;
    SMessageAddress         destLtcomAddr;
    TSfn                    sfn;
};

typedef struct SRLChangeDSPInd_Ver2 SRLChangeDSPInd_Ver2;

#endif /* SRLCHANGEDSPIND_VER2_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env 
*
* Description : RLH uses this to inform that the dsp address of a user
*               has been changed.
*
* Reference   : 
*
* Parameters  :
*
*   msgHeader           TC_RL_CHANGE_DSP_IND_MSG
*
*   userId              Identifies the user whos radio links are changed
*
*   destRakeAddr        New ltcom address of for these radio links
*
*   sfn                 SFN which commits this change
*                 
* Provider : Telecom/Mika Jarvi
*
************************************************************************/

