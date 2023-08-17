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

#ifndef _SRLSETUPINDRLINFO_H
#define _SRLSETUPINDRLINFO_H

#include <TRadioLinkId.h>
#include <TCellId.h>

struct SRLSetupIndRlInfo
{
    TRadioLinkId                    rlId;
    TCellId                         cellId;
};

typedef struct SRLSetupIndRlInfo SRLSetupIndRlInfo;

#endif /* _SRLSETUPINDRLINFO_H */

/******************************************************************
*
* SW Block            : Nora BTS / BS Env
*
* Description : RLH uses this to inform that a new UserID is established.
*
* Reference   :
*
* Parameters  :
*
*   rlId                RadioLink Id.
*
*   cellId              Cell in which this radio link is located.
*
*
* Provider : Telecom/Mika Jarvi
*
************************************************************************/

