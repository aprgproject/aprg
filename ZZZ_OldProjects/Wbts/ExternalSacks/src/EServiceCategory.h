/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1910_003_00/I_Interface/Application_Env/Definitions/EServiceCategory.h $
* @version               $LastChangedRevision: 2029 $
* @date                  $LastChangedDate: 2014-06-23 16:25:46 +0800 (Mon, 23 Jun 2014) $
* @author                $Author: autobuild_sack_wro $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef ESERVICECATEGORY_H
#define ESERVICECATEGORY_H

typedef enum
{
  EServiceCategory_CBR      = 1,
  EServiceCategory_UBR      = 2,
  EServiceCategory_VBR      = 3,       /*FFS*/
  EServiceCategory_ABR      = 4        /* FFS*/
} EServiceCategory;

#endif /* ESERVICECATEGORY_H */

/**
*******************************************************************************
* @enum EServiceCategory
*
* Description  : Service category in ATM - O&M configuration message
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
*
* @param EServiceCategory_CBR :
* @param EServiceCategory_UBR :
* @param EServiceCategory_VBR :
* @param EServiceCategory_ABR :
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by :
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/



