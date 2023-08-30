/**
*******************************************************************************
* @file                  $HeadURL:
*http://svne1.access.nsn.com/isource/svnroot/BTS_I_GLOBAL/tags/GLOBAL_ENV_11_71/I_Interface/Global_Env/Definitions/glo_def.h
*$
* @version               $LastChangedRevision: 3536 $
* @date                  $LastChangedDate: 2015-01-28 16:59:03 +0800 (Wed, 28 Jan 2015) $
* @author                $Author: penaflor $
*
* Original author        <nn>
*
* Copyright 2010 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _GLO_DEF_H
#define _GLO_DEF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Global defition */
#define GLO_TRUE 1
#define GLO_FALSE 0
#define GLO_NULL 0
#define MAX_NUM_OF_FAULT_INFO 14
#define ENUM_32BIT_ENFORCER 0x7FFFFFFF

/* Global type defintions */
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int; /* int == long */
using i8 = signed char;
using i16 = short;
using i32 = int;          /* int == long */
using r32 = float;        /* Do not use this in DSP */
using r64 = double;       /* Do not use this in DSP */
using r128 = long double; /* Do not use this in DSP */
using pu8 = unsigned char *;
using pu8h = u8 *;
using pu16 = unsigned short *;
using pu32 = unsigned int *;
using pi8 = signed char *;
using pi16 = short *;
using pi32 = int *;

using GLO_BOOLEAN = unsigned char;

using TBoolean = u32;
using MESSAGEID = unsigned long;
using TMsgId = MESSAGEID;

/* For AGERE SC100 C complier */
/* For compilation only, X. Song 14.06.2001*/
using sc100_u64 = struct {
    long first;
    long second;
};

#ifdef __DCC__ /* For diab compiler environment */

typedef unsigned long long u64;
typedef signed long long i64;

#endif

#ifdef __GNUC__ /* For GNU C compiler environment */
#if (0 < __GNUC__)

using u64 = unsigned long long;
using i64 = long long;

#endif
#endif

#ifdef __MSC__ /* For microsoft compiler environment */

typedef unsigned __int64 u64;
typedef __int64 i64;

#endif

#ifdef __TCC__ /* For texas compiler environment */

typedef unsigned long long u64;
typedef signed long long i64;

#endif

#ifdef __SC100__ /* For AGERE SC100 C complier */
/* For compilation only, X. Song 14.06.2001*/
typedef sc100_u64 u64;
typedef sc100_u64 i64; /* WARNING Note: Starpro2000 DSP does not support U64 or i64 data type */

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GLO_DEF_H */

/**
*******************************************************************************
* @typedef glo_def
* Description         : GLOBAL BS DEFINITIONS
*
* Reference           : <type interface spec., version, location here>
*                       <type 3GPP or other spec. notation here>
*
*
* Additional Information : <type additional information if needed>
*
* Definition Provided by : BTS-RAN1 SACK / Lomu Mika
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
************************************************************************/
