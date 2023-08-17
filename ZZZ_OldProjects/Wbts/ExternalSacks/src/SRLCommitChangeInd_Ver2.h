/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Original author        JARZMIK
*
* Copyright 2012 Nokia Siemens Networks. All rights reserved.
*******************************************************************************/

#ifndef _S_RL_COMMIT_CHANGE_IND_VER2_H
#define _S_RL_COMMIT_CHANGE_IND_VER2_H

#include <DOpenIUBCommonDefs.h>
#include <SMessageHeader.h>
#include <TUserId.h>
#include <TCRNCCommunicationContextId.h>
#include <TNodeBCommunicationContextId.h>
#include <SMessageAddress.h>
#include <TFrameOffset.h>
#include <TRLSetID.h>
#include <TNumberOfItems.h>
#include <SRLSetupIndRlInfo.h>
#include <TSfn.h>

struct SRLCommitChangeInd_Ver2
{
    MESSAGEHEADER(msgHeader)
    TUserId                         userId;
    TNodeBCommunicationContextId    nBCCId;
    TCRNCCommunicationContextId     crncCommContextId;
    SMessageAddress                 dspLtcomAddr;
    TFrameOffset                    firstFrameOffset;
    TRLSetID                        rlSETId;
    TNumberOfItems                  nbrOfRLs;
    SRLSetupIndRlInfo               rlInfo[ MAX_NR_OF_RLS ];
    TSfn                            sfn;
};

typedef struct SRLCommitChangeInd_Ver2 SRLCommitChangeInd_Ver2;

#endif /* _S_RL_COMMIT_CHANGE_IND_VER2_H */

/**
*******************************************************************************
* @struct     SRLCommitChangeInd_Ver2 
*
*                      
*
* Reference           : 
*
* @param userId               : Identifies the user who has new radiolinks
* @param nBCCId               : Node B-Communication ContextID
* @param crncCommContextId    : Controlling RNC Communication Context Identifier
* @param dspRakeAddr          : Rake address of for these radio links
* @param dspCodeAddr          : Code address of for these radio links
* @param firstFrameOffset     : Frame offset for the first radio link
* @param rlSETId              : Radiolink set ID assigned to users radiolinks
* @param nbrOfRLs             : Number of entries in rlID-table
* @param rlInfo               : Array of new radiolink radio link informations
* @param sfn                  : sfn value
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom 
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/
