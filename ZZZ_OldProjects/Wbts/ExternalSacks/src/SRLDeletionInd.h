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

#ifndef SRLDELETIONIND_H
#define SRLDELETIONIND_H

#include <DOpenIUBCommonDefs.h>
#include <SMessageHeader.h>
#include <TUserId.h>
#include <EBoolean.h>
#include <TNumberOfItems.h>
#include <TRadioLinkId.h>
#include <TSfn.h>

struct SRLDeletionInd
{
    MESSAGEHEADER(msgHeader) 
    TUserId                 userId;
    EBoolean                removeUser;    
    TNumberOfItems          nbrOfRLIds;
    TRadioLinkId            rlId[ MAX_NR_OF_RLS ];
    TSfn                    sfn;
};

typedef struct SRLDeletionInd SRLDeletionInd;

#endif /* SRLDELETIONIND_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env 
*
* Description : RLH uses this to inform that radiolink is deleted.
*               NOTE: when all radiolinks of a userID are deleted, 
*                     the whole user is ought to be removed.
*
* Reference   : 
*
* Parameters  :
*
*   msgHeader           TC_RL_DELETION_IND_MSG
*
*   userId              Identifies the user whose radiolink(s) is deleted.
*
*   removeUser          Remove whole user, in this case nbrOfRLIds should be 0. 
*
*   nbrOfRLIds          Number of entries in rlID-table
*
*   rlId                Array of new radiolinks
*
*
* Provider : Telecom/Mika Jarvi
*
************************************************************************/

