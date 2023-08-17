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

#ifndef _SRLRECONFCOMMITIND_H
#define _SRLRECONFCOMMITIND_H

#include <SMessageHeader.h>
#include <TUserId.h>
#include <TSfn.h>

struct SRLReconfCommitInd
{
    MESSAGEHEADER(msgHeader) 
    TUserId                 userId;
    TSfn                    sfn;
};

typedef struct SRLReconfCommitInd SRLReconfCommitInd;

#endif /* _SRLRECONFCOMMITIND_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env 
*
* Description : RLH uses this to commit the prepared reconf state 
*               of a radio link .
*
* Reference   : 
*
* Parameters  :
*
*   msgHeader           TC_RL_RECONF_COMMIT_IND_MSG
*
*   userId              Identifies the user whos reconf is commited
*
*   sfn                 SFN from which this change takes effect.
*                 
* Provider : Telecom/Mika Jarvi
*
************************************************************************/

