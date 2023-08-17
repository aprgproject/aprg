/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Original author        A Heikkila
*
* Copyright 2012 Nokia Siemens Networks. All rights reserved.
*******************************************************************************/

#ifndef SRLPREPARECHANGEIND_H
#define SRLPREPARECHANGEIND_H

#include <SMessageHeader.h>
#include <TUserId.h>

struct SRLPrepareChangeInd
{
    MESSAGEHEADER(msgHeader)
    TUserId                 userId;
    TBoard                  board;
};

typedef struct SRLPrepareChangeInd SRLPrepareChangeInd;

#endif /* SRLPREPARECHANGEIND_H */

/**
*******************************************************************************
* @struct     SRLPrepareChangeInd 
*
* Reference           : 
*
* @param userId          : UsedId
* @param board           : Source Dmeas board
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : Telecom 
* 
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
*******************************************************************************/
