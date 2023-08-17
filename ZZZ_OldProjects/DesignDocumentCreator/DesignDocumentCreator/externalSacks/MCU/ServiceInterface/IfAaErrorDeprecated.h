/**
*******************************************************************************
* @file                  $HeadURL:$
* @version               $LastChangedRevision:$
* @date                  $LastChangedDate:$
* @author                $Author:$
*
* Copyright 2019 Nokia. All rights reserved.
*
*******************************************************************************/
#ifndef _MCU_IFAAERROR_DEPRECATED_H
#define _MCU_IFAAERROR_DEPRECATED_H

#include "CcsCommon.h"
#include <../../COMMON/ServiceInterface/IfAaError.h>
#include <../../SHARED/MCU_RT/ServiceInterface/IfAaError.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaErrorApiMcuLinux AaError LINUX MCU API
* @ingroup dgAaError
*/

/** @{ */
#ifndef CCS_SKIP_AaErrorRaiseFatalE_loc
#ifndef CCS_DISABLE_DEPRECATED_WARNING
    #warning "AaErrorRaiseFatalE_loc is deprecated, please use AaErrorExceptionRaise instead."
#endif
static __CCS_INLINE__
void AaErrorRaiseFatalE_loc(const i32 code, const char* const description, const void* const extra, const u32 extraLen, const char *file, const u32 line)
{
   AaErrorExceptionRaise(EAaErrorFatality_Fatal, code, extra, extraLen,
                         description, file, line);
}

#define AaErrorRaiseFatalE(__code, __description, __extra, __extraLen) \
   AaErrorRaiseFatalE_loc(__code, __description, __extra, __extraLen, __FILE__, __LINE__)

#define AaErrorRaiseFatal(__code, __description) \
   AaErrorRaiseFatalE(__code, __description, GLO_NULL, 0)

#endif
/** @} */

#ifdef __cplusplus
}
#endif

#endif /*  _MCU_IFAAERROR_DEPRECATED_H */
