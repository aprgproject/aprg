/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Checksum Service API header file
* @module                AaGpu
* @owner                 Marcela Nemet
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAGPUCHECKSUMS_H
#define _MCU_RT_IFAAGPUCHECKSUMS_H

/*----------------------- INCLUDED FILES --------------------------------------*/

#include "CcsCommon.h"
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
*@defgroup dgChecksums Checksoms API
*
* Implementation is double linked list utilising offsets instead of pointers in
* internal house-keeping. Since some arithmetic is required during list handing
* this is not as efficient as original AaGpuSimpleLinkedList but this implementation
* should be suitable for Linux shared memory.
*
* @warning NULL pointer checks are not done!
*
*@{*/


/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @brief AaGpuChecksums return codes */
typedef enum EAaGpuChecksumsRet
{
    EAaGpuChecksumsRet_Ok = 0,           /**< No errors */
    EAaGpuChecksumsRet_InvalidParameter, /**< Invalid parameter defined */
    EAaGpuChecksumsRet_InvalidState,     /**< Handler is in invalid state */
    EAaGpuChecksumsRet_InternalError,    /**< Algorithm internal error */

    EAaGpuChecksumsRet_NbrOf             /**< The last one and keep it that way! */

} EAaGpuChecksumsRet;

/** @brief AaGpuChecksums return codes in convenience textual representation */
#define EAAGPUCHECKSUMSRET_VALUES \
   { \
       "EAaGpuChecksumsRet_Ok", \
       "EAaGpuChecksumsRet_InvalidParameter" \
       "EAaGpuChecksumsRet_InvalidState" \
       "EAaGpuChecksumsRet_InternalError" \
       "EAaGpuChecksumsRet_NbrOf" \
   }

typedef struct SAaGpuChecksumsParams
{
    void*  opaque;     /**< Algorithm specific data */

} SAaGpuChecksumsParams;

typedef EAaGpuChecksumsRet TAaGpuChecksumsUninit(SAaGpuChecksumsParams* const params);
typedef EAaGpuChecksumsRet TAaGpuChecksumsUpdate(SAaGpuChecksumsParams* const params,
                                                 const void* const data, const u32 length);
typedef u32                TAaGpuChecksumsValueGet(SAaGpuChecksumsParams* const params);


/** @brief AaGpuChecksums function pointers for operations */
typedef struct SAaGpuChecksumsOps
{
    TAaGpuChecksumsUninit*   uninit;    /**< Algorithm uninitialization operation */
    TAaGpuChecksumsUpdate*   update;    /**< Algorithm checksum update operation */
    TAaGpuChecksumsValueGet* valueGet;  /**< Algorithm checksum value get operation */

} SAaGpuChecksumsOps;


/** @brief Handler for checksum algorithm implementation */
typedef struct SAaGpuChecksumHandler
{

    SAaGpuChecksumsOps     operations; /**< Algorithm specific operations */
    SAaGpuChecksumsParams  parameters; /**< Parameters of the handler */

} SAaGpuChecksumHandler;


/*----------------------- PUBLIC INTERFACES (MCU API)-------------------------*/


/**
 * @defgroup dgChecksumsApiMcu Checksums MCU API
 * @ingroup  dgChecksums
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief  AaGpuChecksumsUninit uninitializes checksum handler to be reused for checksumming
*
*
*   @param[in]  handler  Pointer to checksum handler.
*
*   @return EAaGpuChecksumsRet_Ok
*   @return EAaGpuChecksumsRet_InvalidParameter
*
*   @par Description:
*   Uninitialization must be done for every initialized handlers which are not needed any longer.
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   EAaGpuChecksumsRet ret;
*   SAaGpuChecksumHandler handler;
*
*   // Initilize the handler before use
*   ret = AaGpuAdler32Init(&handler);
*   // ... Use the handler ...
*   ret = AaGpuChecksumsUninit(&handler);
*
*   // Since handler in uninit, it can be re-used
*   ret = AaGpuCrc2Init(&handler);
*   // ... Use the handler ...
*   ret = AaGpuChecksumsUninit(&handler);
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/
EAaGpuChecksumsRet
AaGpuChecksumsUninit(SAaGpuChecksumHandler* const handler);

/**
*******************************************************************************
*
*   @brief  AaGpuChecksumsUpdate updates handler with checksum over given data.
*
*
*   @param[in]      handler  Pointer to checksum handler.
*   @param[in]      data     Pointer to data to calculate.
*   @param[in]      length   Length of the data to calculate in bytes.
*
*   @return EAaGpuChecksumsRet_Ok
*   @return EAaGpuChecksumsRet_InvalidParameter
*
*   @par Description:
*   Checksum is calculated over given data and stored in the handler.
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   char* data = "Data to calculate";
*   char* data2 = "and more data";
*   EAaGpuChecksumsRet ret;
*   SAaGpuChecksumHandler handler;
*
*   ret = AaGpuAdler32Init(&handler);
*   ret = AaGpuChecksumsUpdate(&handler, data, strlen(data));
*   ret = AaGpuChecksumsUpdate(&handler, data2, strlen(data2));
*   ret = AaGpuChecksumsUninit(&handler);
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/
EAaGpuChecksumsRet
AaGpuChecksumsUpdate(SAaGpuChecksumHandler* const handler, const void* const data, const u32 length);

/**
*******************************************************************************
*
*   @brief  AaGpuChecksumsValueGet returns current checksum value.
*
*
*   @param[in]  handler  Pointer to checksum handler.
*
*   @return Current checksum value or in case of error 0.
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   char* data = "Data to calculate";
*   char* data2 = "Data 2 to calculate";
*   char* data3 = " and more data to calculate";
*   EAaGpuChecksumsRet ret;
*   SAaGpuChecksumHandler handler;
*   u32 checksum;
*
*   // This example uses Adler32 algorithm
*   ret = AaGpuAdler32Init(&handler);
*   ret = AaGpuChecksumsUpdate(&handler, data, strlen(data));
*   checksum = AaGpuChecksumsValueGet(&handler);
*
*   // Uninit after use
*   ret = AaGpuChecksumsUninit(&handler);
*
*   AaSysLogPrint(EAaSysLogSeverityLevel_Debug, "Checksum of data '%s' is %lu", data, checksum);
*
*   // Init before reuse
*   ret = AaGpuAdler32Init(&handler);
*   ret = AaGpuChecksumsUpdate(&handler, data2, strlen(data2));
*   ret = AaGpuChecksumsUpdate(&handler, data3, strlen(data3));
*   checksum = AaGpuChecksumsValueGet(&handler);
*
*   // Uninit after use
*   ret = AaGpuChecksumsUninit(&handler);
*
*   AaSysLogPrint(EAaSysLogSeverityLevel_Debug, "Checksum of data2 and data3 '%s%s' is %lu", data2, data3, checksum);
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/
u32
AaGpuChecksumsValueGet(SAaGpuChecksumHandler* const handler);


/**
 * @}
 */


/*@}*/

#ifdef __cplusplus
}
#endif

#endif /*  _MCU_RT_IFAAGPUCHECKSUMS_H */
