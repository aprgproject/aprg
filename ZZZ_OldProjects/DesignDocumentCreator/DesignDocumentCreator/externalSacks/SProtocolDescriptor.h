/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/SProtocolDescriptor.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef SPROTOCOLDESCRIPTOR_H
#define SPROTOCOLDESCRIPTOR_H

#include <EProtocolType.h>
#include <ESaalUsage.h>
#include <TMtuSize.h>
#include <EHeaderFormat.h>

typedef struct SProtocolDescriptor
{
    EProtocolType    type;
    ESaalUsage       saalUsage;
    TMtuSize         mtuSize;
    EHeaderFormat    headerFormat;
} SProtocolDescriptor;

#endif /* SPROTOCOLDESCRIPTOR_H */

/**
*******************************************************************************
* @struct SProtocolDescriptor
*
* Description  : Protocol descriptor in ATM - O&M configuration message
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param type :
* @param saalUsage :
* @param mtuSize :
* @param headerFormat :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/




