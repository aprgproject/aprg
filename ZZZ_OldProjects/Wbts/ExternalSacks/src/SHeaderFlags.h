/**
*******************************************************************************
* @file                  $HeadURL: https://wrscmi.inside.nsn.com/isource/svnroot/BTS_I_GLOBAL/tags/GLOBAL_ENV_13_168/I_Interface/Global_Env/Definitions/SHeaderFlags.h $
* @version               $LastChangedRevision: 3080 $
* @date                  $LastChangedDate: 2014-05-23 20:32:51 +0800 (Fri, 23 May 2014) $
* @author                $Author: plaskonk $
*
* Original author        Tomi Kahila
*
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _SHEADERFLAGS_H
#define _SHEADERFLAGS_H

#include <glo_def.h>
#ifdef __TCC__ /* For texas compiler environment - ref glo_def.h */

struct SHeaderFlags
{
    u8 user;       /* reserved for application layer, transported "as is".       */
    u8 system;     /* reserved for transportation/platform layer (checksum etc)  */
};
typedef struct SHeaderFlags SHeaderFlags;

#else /* for PPC and PC MSC compilers */

struct SHeaderFlags
{
    u8 system;     /* reserved for transportation/platform layer (checksum etc)  */
    u8 user;       /* reserved for application layer, transported "as is".       */
};
typedef struct SHeaderFlags SHeaderFlags;

#endif /* __TCC__ */


#endif /* _SHEADERFLAGS_H */

/**
*******************************************************************************
* @struct SHeaderFlags
* Description         : type definition used in message header
*
* Reference   : <Interface Specification, version, location>
*
* Parameters  :
* @param system : reserved for transportation/platform layer (checksum etc)
* @param user   : reserved for application layer, transported "as is".
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : BTS-RAN1 SACK / Tomi Kahila
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
************************************************************************/



