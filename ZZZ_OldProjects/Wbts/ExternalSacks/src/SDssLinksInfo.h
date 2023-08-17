/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SDssLinksInfo.h $
* @version               $LastChangedRevision: 2748 $
* @date                  $LastChangedDate: 2018-07-03 17:47:13 +0800 (Tue, 03 Jul 2018) $
* @author                $Author: malba $
*
* Original author        Mark Alba
*
* Copyright 2017 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SDSS_LINKS_INFO_H
#define _SDSS_LINKS_INFO_H

#include <TAaSysComSicad.h>
#include <TNumberOfItems.h>

struct SDssLinksInfo
{
    TAaSysComSicad           subrackAddress;
    TNumberOfItems           numberOfDssLinkIndices;
};
typedef struct SDssLinksInfo SDssLinksInfo;

#endif /* _SDSS_LINKS_INFO_H */

/**
*******************************************************************************
* @struct SDssLinksInfo
*
* Parameters :
*
* @param subrackAddress         : The address of the subrack for the corresponding DSS link indices.
*                                 This will contain the NID of AXM and the CPID is empty. Example possible values: 0x10110000 and 0x20110000.
*                                 Telecom will use the board for mapping DSS link indices.
*
* @param numberOfDssLinkIndices : The number of DSS link indices.
*                                 The possible values are: 0, 1, 2, ... 32.
*
* Description                   : Structure for DSS links information
*
* Additional Information : SR002014
*
* Reference :
*
* Definition Provided by : Mark Alba
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/

