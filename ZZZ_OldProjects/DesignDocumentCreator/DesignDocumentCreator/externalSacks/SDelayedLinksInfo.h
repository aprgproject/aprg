/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SDelayedLinksInfo.h $
* @version               $LastChangedRevision: 2748 $
* @date                  $LastChangedDate: 2018-07-03 17:47:13 +0800 (Tue, 03 Jul 2018) $
* @author                $Author: malba $
*
* Original author        Mark Alba
*
* Copyright 2017 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SDELAYED_LINKS_INFO_H
#define _SDELAYED_LINKS_INFO_H

#include <TAaSysComSicad.h>
#include <TNumberOfItems.h>

struct SDelayedLinksInfo
{
    TAaSysComSicad           subrackAddress;
    TNumberOfItems           numberOfDelayedLinkIndices;
};
typedef struct SDelayedLinksInfo SDelayedLinksInfo;

#endif /* _SDELAYED_LINKS_INFO_H */

/**
*******************************************************************************
* @struct SDelayedLinksInfo
*
* Parameters :
*
* @param subrackAddress             : The address of the subrack for the corresponding delayed link indices.
*                                     This will contain the NID of AXM and the CPID is empty. Example possible values: 0x10110000 and 0x20110000.
*                                     Telecom will use the board for mapping delayed link indices.
*
* @param numberOfDelayedLinkIndices : The number of delayed link indices.
*                                     The possible values are: 0, 1, 2, ... 48.
*
* Description                       : Structure for delayed links information
*
* Additional Information : RP001621
*
* Reference :
*
* Definition Provided by : Mark Alba
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

