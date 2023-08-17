/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2018 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef _MCU_IFAACPU_DEFS_H
#define _MCU_IFAACPU_DEFS_H

#include <CcsCommon.h>
#include <glo_def.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
*@defgroup dgAaCpuApiMcu MCU API
*@ingroup dgAaCpu
*@{
*/

/**
* @name CPU affinity management macros
* @{
*/

/**
 * @brief affinity mask type
 */
typedef u32 TAaCpuAffinityMask;

/**
 * @brief affinity mask to set each available core
 */
#define AACPU_AFFINITY_MASK_ALL_SET ( 0xFFFFFFFF )

/**
 * @brief maximal affinity mask size
 */
#define AACPU_AFFINITY_MASK_MAX_SIZE ( sizeof(TAaCpuAffinityMask)*8 )

/**
* @brief Macro sets core given by \p __coreNumber in \p __mask.
*
* @param[out] __mask        Affinity mask to be modified.
* @param[in]  __coreNumber  Core number to be set.
*/
#define AACPU_AFFINITY_SET_CORE(__mask, __coreNumber) do {\
            u32 __cn = (__coreNumber); \
            __cn >= AACPU_AFFINITY_MASK_MAX_SIZE ? 0 : ((__mask) |= (1 << __cn));} while(0)

/**
* @brief Macro clears core given by \p __coreNumber in \p __mask.
*
* @param[out] __mask        Affinity mask to be modified.
* @param[in]  __coreNumber  Core number to be cleared.
*/
#define AACPU_AFFINITY_CLEAR_CORE(__mask, __coreNumber) do {\
            u32 __cn = (__coreNumber); \
            __cn >= AACPU_AFFINITY_MASK_MAX_SIZE ? 0 : ((__mask) &= ~(1 << __cn));} while(0)

/**
* @brief Macro tests if core given by \p __coreNumber in \p __mask is set.
*
* @param[in] __mask        Affinity mask to be tested.
* @param[in] __coreNumber  Core number to be tested.
*
* @return GLO_TRUE if core is set, GLO_FALSE otherwise
*/
#define AACPU_AFFINITY_IS_CORE_SET(__mask, __coreNumber) __extension__({\
            u32 __cn = (__coreNumber); \
            __cn >= AACPU_AFFINITY_MASK_MAX_SIZE ? GLO_FALSE : \
            ((((__mask) & (1 << __cn)) > 0) ? GLO_TRUE : GLO_FALSE);})

/* @}*/
/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IFAACPU_DEFS_H */
