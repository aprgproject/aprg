/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Event Count Measurement Utility API header file
* @module                AaGpu
* @owner                 Marcela Nemet
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAGPUCOUNT_H
#define _MCU_RT_IFAAGPUCOUNT_H
#include "CcsCommon.h"



/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
*@addtogroup dgStatistics
*
* @par Event Count Utility
* This utility calculates how many times certain event has been occurred.
* If only event count is needed, then it is reasonable to use this utility
* instead of Duration Measurement Utility.
*
*/

/**
* @defgroup dpAaStatisticsErrors Error codes
* @ingroup dgStatistics
*
* Exception codes are used with Error Management Service (AaError) and they describe
* various error situations a service may have and report. Important part of exception
* is the severity. Usually it is non-fatal thus execution of application continues
* after the exception repporting but in some special case execution is prohipited and
* the application is eventually terminated.
*
*
* @ref dsVariation "[CCSAPI_VARIABILITY]"
*
* @verbatim
*  Error code:       EAaErrorCcs_AaGpuCount_InvalidParameter
*
*  Severity:         Non-fatal
*
*  Description:      Invalid parameter given to AaGpuCount API call.
*
*  Extra code:       None
*
*  Recovery actions: None
*
*  See:              None
* @endverbatim
*
* @verbatim
*  Error code:       EAaErrorCcs_AaGpuCount_AllocationFailed
*
*  Severity:         Non-fatal
*
*  Description:      Allocation failed which lead to operation failure.
*                    There are mainly three reasons for failure:
*                       - Lack of resources (out-of-memory)
*                       - Maximum reference or alias count exceeded for existing counter
*                       - There is already existing counter for given alias name
*
*  Extra code:       Name of the counter if given
*
*  Recovery actions: None
*
*  See:              None
* @endverbatim
*
* @verbatim
*  Error code:       EAaErrorCcs_AaGpuCount_ReadOnly
*
*  Severity:         Non-fatal
*
*  Description:      Requested operation is not possible to execute for
*                    read-only handle.
*
*  Extra code:       None
*
*  Recovery actions: Use AaGpuCountAlloc to create writable handle.
*
*  See:              None
* @endverbatim
*
*/

/**
*@addtogroup dgAaGpuCountApi Event Count
*@ingroup dgStatisticsApi
*
*
*@{*/

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <stddef.h>
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/* Following defined are dropped out from Doxygen document */
/** @cond */
#ifndef __CCS_INLINE__
# define __CCS_INLINE__ __inline__
#endif

#define AaGpuCountGetSetOfChildNames AaGpuCountGetChildNameSet /**< For supporting old SW */
#define AaGpuCountGetNextNameFromSet AaGpuCountGetNextChildName /**< For supporting old SW */
#define AaGpuCountGetHandleCopy      AaGpuCountGetCopy /**< For supporting old SW */
/** @endcond */


/** @brief Return codes */
typedef enum
{
    EAaGpuCountRet_Ok = 0,       /**< No errors detected */
    EAaGpuCountRet_InvalidParam, /**< Invalid parameter given */
    EAaGpuCountRet_ReadOnly,     /**< Operation not supported for read-only counters */
    EAaGpuCountRet_Error,        /**< Some kind of error occurred */

    EAaGpuCountRet_NbrOf         /**< Keep always the last */
} EAaGpuCountRet;

/** @brief Type definition for Counter Handler */
typedef void TAaGpuCountHandle;
/** @brief Type definition for Counter Handler set */
typedef void TAaGpuCountSet;

/** @brief Count value type, makes it possible to acquire the value with the wanted size */
typedef union
{
  u32 u32val; /**< Member for 32bit counter */

// TODO: Not used because AaCpuSpinLock and AaCpuYield cause problems on OSE.
//  u64 u64val; /**< Member for 64bit counter */

}UAaGpuCountValue;

/*----------------------- PUBLIC INTERFACES ----------------------------------*/

/** @name Public API
*@{
*/

/**
 * @defgroup dgAaGpuCountApi Event Count COMMON API
 * @ingroup  dgStatisticsApiCommon
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief  Allocates a new event counter handler
*
*   @param[in] name Namespaced name for the counter or GLO_NULL
*
*   @return  Pointer to the allocated counter handler
*
*   @par Description:
*   If name is GLO_NULL, counter is dealt as private and the handle is then
*   the only access to the counter. Otherwise the counter is public and will
*   be stored EE wide and it can be accessed via the name also. If there is
*   already existing counter with same name in current EE, a reference to
*   the existing counter is created instead of new unique one. There is no
*   difference between alias counter and their original counterparts thus
*   allocating counter with existing alias name shall increase references of
*   the alias counter.
*
*   @par Errors:
*   Exception #EAaErrorCcs_AaGpuCount_AllocationFailed is raised and GLO_NULL
*   is returned due to following reasons:
*      - Lack of resources (out-of-memory)
*      - Maximum reference count exceeded for existing counter
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuCount.h>
*
*   TAaGpuCountHandle *counter;
*
*   counter = AaGpuCountAlloc("app.myapp.mycounter"); // Create public counter
*
*   // Counter can now be used
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
*   @see AaGpuCountFree
*
******************************************************************************/
TAaGpuCountHandle*
AaGpuCountAlloc(char const * const name);

/**
*******************************************************************************
*
*   @brief  Frees an event counter handler
*
*   @param[in] handle  Pointer to the handler of the counter
*
*   @return None
*
*   @par Description:
*   Handler is freed and if the counter, the handler refers to, is private,
*   also the counter is then freed.
*
*   @par Errors:
*   If invalid (NULL or otherwise invalid) parameter is given, non-fatal
*   exception #EAaErrorCcs_AaGpuCount_InvalidParameter is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuCount.h>
*
*   TAaGpuCountHandle *counter, *counter2;
*
*   counter = AaGpuCountAlloc("app.myapp.mycounter"); // Create public counter
*   counter2 = AaGpuCountAlloc("app.myapp.mycounter"); // Create new instance to the same counter
*
*   // Use the counter (both instances can be used)
*
*   AaGpuCountFree(counter);
*   AaGpuCountFree(counter2);
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
*   @see AaGpuCountAlloc
*
******************************************************************************/
void
AaGpuCountFree(TAaGpuCountHandle *handle);

/**
*******************************************************************************
*
*   @brief  Returns a read-only copy of a counter corresponding to a name
*
*   @param[in] name Name of the counter (original or alias)
*
*   @return Handle to the counter, GLO_NULL if not found
*
*   @par Description:
*   Returns a read-only copy from a counter which statistics are a snapshot
*   of a certain moment of the requested counter. User is responsible of
*   freeing the handle after usage with AaGpuCountCopyFree(). Notice that the
*   copy cannot be used to make new measurements it can be only used to obtain
*   the results. Alias name can be also used for making copy.
*   \n\n
*   If the counter needs to be updated, then AaGpuCountAlloc() should be used
*   instead of AaGpuCountGetCopy() for creating new reference to the counter.
*
*   @par Errors:
*   In case of invalid parameter (NULL pointer) non-fatal exception
*   #EAaErrorCcs_AaGpuCount_InvalidParameter is raised and GLO_NULL is returned.
*
*   @par Restrictions:
*   It is not recommended to lookup the handle by name all the time, instead
*   in counter update procedure the direct handle ptr should be stored locally
*   which makes the update procedure fast. The lookup by name can be
*   potentially expensive operation. Wildcards cannot be used in the name.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuCount.h>
*
*   TAaGpuCountHandle *counter, *copy;
*   UAaGpuCountValue currentValue, copyValue;
*
*   counter = AaGpuCountAlloc("app.myapp.mycounter"); // Create public counter
*
*   copy = AaGpuCountGetCopy("app.myapp.mycounter"); // Creates a read-only snapshot of the counter
*
*   if (strcmp(AaGpuCountGetName(counter), AaGpuCountGetName(copy)) == 0)
*   {
*       // Both counter handlers have same name since they refer to same counter
*   }
*
*   // Use counter...
*   AaGpuCountIncrease(counter); // Copy of the counter cannot be used since it is read-only
*
*   // Get values of both instances
*   currentValue = AaGpuCountGetValue(counter);
*   copyValue = AaGpuCountGetValue(copy);
*
*   if (currentValue != copyValue)
*   {
*       // Values of currentValue and copyValue are not the same since
*       // copyValue has the value of the counter at a certain moment but
*       // currentValue has the latest value
*   }
*
*   // We don't need the copy any longer
*   AaGpuCountCopyFree(copy);
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
*   @see AaGpuCountAlloc
*
******************************************************************************/
TAaGpuCountHandle*
AaGpuCountGetCopy(char const * const name);

/**
*******************************************************************************
*
*   @brief  Frees copy of an event counter handler
*
*   @param[in] handle  Pointer to the handler of the counter copy
*
*   @return None
*
*   @par Description:
*   Handler is freed and counter copy is freed.
*
*   @par Errors:
*   In case of invalid parameter (NULL pointer) non-fatal exception
*   #EAaErrorCcs_AaGpuCount_InvalidParameter is raised. In case of counter is
*   not read-only non-fatal exception #EAaErrorCcs_AaGpuCount_InvalidParameter
*   is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
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
*   @see AaGpuCountGetCopy
*
******************************************************************************/
void
AaGpuCountCopyFree(TAaGpuCountHandle *handle);

/**
*******************************************************************************
*
*   @brief  Adds alias name for existing counter
*
*   @param[in] handler Handler of the counter
*   @param[in] name    Name for the alias
*
*   @return EAaGpuCountRet_Ok
*   @return EAaGpuCountRet_InvalidParam
*   @return EAaGpuCountRet_ReadOnly
*   @return EAaGpuCountRet_Error
*
*   @par Description:
*   The counter can be used via both original and alias names. Adding alias name
*   for existing alias name effectively adds the alias for the original name thus
*   aliases may NOT have aliases.
*
*   @par Errors:
*   In case the handle is read-only, return code #EAaGpuCountRet_ReadOnly is
*   returned and exception #EAaErrorCcs_AaGpuCount_ReadOnly is raised.
*   If one or both of the parameters are invalid (GLO_NULL or otherwice invalid),
*   return code #EAaGpuCountRet_InvalidParam  is returned and exception
*   #EAaErrorCcs_AaGpuCount_InvalidParameter is raised. Exception
*   #EAaErrorCcs_AaGpuCount_AllocationFailed is raised and #EAaGpuCountRet_Error
*   is returned due to following reasons:
*      - Lack of resources (out-of-memory)
*      - Maximum alias count exceeded for existing counter
*      - There is already existing counter for given alias name
*
*   @par Restrictions:
*   It is not possible to add alias via read-only handler.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuCount.h>
*
*   EAaGpuCountRet rc;
*   TAaGpuCountHandle *counter, *copy1, *copy2, *counter2;
*
*   counter = AaGpuCountAlloc("app.myapp.mycounter"); // Create public counter
*
*   rc = AaGpuCountAddAlias(counter, "app.myapp.aliases.mycounter.alias1");
*   rc = AaGpuCountAddAlias(counter, "app.myapp.aliases.mycounter.alias2");
*
*   // Get copies of the same counter
*   copy1 = AaGpuCountGetCopy("app.myapp.mycounter");
*   copy2 = AaGpuCountGetCopy("app.myapp.aliases.mycounter.alias2");
*
*   // copy1 and copy2 are snapshots of the same counter however since they are
*   // read-only counters, they cannot be used for adding new aliases. Instead
*   // new counter must be allocated using original or alias name.
*
*   counter2 = AaGpuCountAlloc("app.myapp.aliases.mycounter.alias1");
*   rc = AaGpuCountAddAlias(counter2, "app.myapp.aliases.mycounter.alias3");
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
*   @see AaGpuCountAlloc
*
******************************************************************************/
EAaGpuCountRet
AaGpuCountAddAlias(const TAaGpuCountHandle* handler, char const * const alias);

/**
*******************************************************************************
*
*   @brief  Returns the name of the counter where the handle refers to
*
*   @param handle[in]  Pointer to the handler of the counter
*
*   @return Pointer to string of counter name or GLO_NULL
*
*   @par Description:
*   If counter is private and no name was given, GLO_NULL is returned.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuCount.h>
*
*   TAaGpuCountHandle *counter;
*   const char *name;
*
*   counter = AaGpuCountAlloc("app.myapp.mycounter"); // Create public counter
*
*   name = AaGpuCountGetName(counter);
*
*   if (strcmp("app.myapp.mycounter", name) == 0)
*   {
*       // Given name matches to the returned one
*   }
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
*   @see AaGpuCountAlloc
*
******************************************************************************/
const char*
AaGpuCountGetName(TAaGpuCountHandle const * const handle);

/**
*******************************************************************************
*
*   @brief     Increases the counter value by one
*
*   @param handle[in] Handle to the counter
*
*   @return EAaGpuCountRet_Ok
*   @return EAaGpuCountRet_ReadOnly
*   @return EAaGpuCountRet_InvalidParam
*
*   @par Description:
*   None
*
*   @par Errors:
*   If invalid parameter is given return code #EAaGpuCountRet_InvalidParam is
*   returned and exception #EAaErrorCcs_AaGpuCount_InvalidParameter is raised.
*   If given handle is read-only, #EAaGpuCountRet_ReadOnly is returned and
*   exception #EAaErrorCcs_AaGpuCount_ReadOnly is raised.
*
*   @par Restrictions:
*   Counter cannot be increased via read-only handle.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuCount.h>
*
*   TAaGpuCountHandle *counter;
*   EAaGpuCountRet rc;
*
*   counter = AaGpuCountAlloc(GLO_NULL); // Create private counter
*
*   rc = AaGpuCountIncrease(counter);
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
*   @see AaGpuCountAlloc
*   @see AaGpuCountReset
*   @see AaGpuCountGetValue
*
******************************************************************************/
EAaGpuCountRet
AaGpuCountIncrease(TAaGpuCountHandle *handle);

/**
*******************************************************************************
*
*   @brief  Resets couter
*
*   @param handle[in] Handle to the counter
*
*   @return EAaGpuCountRet_Ok
*   @return EAaGpuCountRet_ReadOnly
*   @return EAaGpuCountRet_InvalidParam
*
*   @par Description:
*   None
*
*   @par Errors:
*   If invalid parameter is given return code #EAaGpuCountRet_InvalidParam is
*   returned and exception #EAaErrorCcs_AaGpuCount_InvalidParameter is raised.
*   \n
*   If given handle is read-only, #EAaGpuCountRet_ReadOnly is returned and
*   exception #EAaErrorCcs_AaGpuCount_ReadOnly is raised.
*
*   @par Restrictions:
*   Counter cannot be reset via read-only handle.
*
*   @par Example:
*
*   @code
*
*   See AaGpuCountGetValue
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
*   @see AaGpuCountAlloc
*   @see AaGpuCountIncrease
*   @see AaGpuCountGetValue
*
******************************************************************************/
EAaGpuCountRet
AaGpuCountReset(TAaGpuCountHandle *handle);

/**
*******************************************************************************
*
*   @brief  Resets couter by name
*
*   @param[in] name Name of the counter
*
*   @return  EAaGpuCountRet_Ok
*   @return  EAaGpuCountRet_InvalidParam
*
*   @par Description:
*   Finds specified counter and resets its value.
*
*   @par Errors:
*   Exception #EAaErrorCcs_AaGpuCount_InvalidParameter is raised and
*   EAaGpuCountRet_InvalidParam due to following reason:
*      - Counter name is NULL.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuCount.h>
*
*   EAaGpuCountRet rc;
*
*   rc = AaGpuCountResetByName("app.myapp.mycounter");
*
*   if(rc != EAaGpuCountRet_Ok)
*   {
*       // Failed to reset counter.
*   }
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
*   @see
*
******************************************************************************/
EAaGpuCountRet
AaGpuCountResetByName(char const * const name);

/**
*******************************************************************************
*
*   @brief  Returns current value of the counter
*
*   @param handle[in] Handle to the counter
*
*   @return Current value
*
*   @par Description:
*   None
*
*   @par Errors:
*   If invalid parameter is given exception #EAaErrorCcs_AaGpuCount_InvalidParameter
*   is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuCount.h>
*
*   TAaGpuCountHandle *counter;
*   EAaGpuCountRet rc;
*   UAaGpuCountValue value;
*
*   counter = AaGpuCountAlloc(GLO_NULL); // Create private counter
*
*   rc = AaGpuCountIncrease(counter);
*
*   value = AaGpuCountGetValue(counter);
*
*   // value is now 1
*
*   rc = AaGpuCountReset(counter);
*
*   value = AaGpuCountGetValue(counter);
*
*   // value is now 0
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
*   @see AaGpuCountAlloc
*   @see AaGpuCountReset
*   @see AaGpuCountIncrease
*
******************************************************************************/
UAaGpuCountValue
AaGpuCountGetValue(TAaGpuCountHandle *handle);

/**
*******************************************************************************
*
*   @brief  Gets counter names under certain namespace
*
*   @param parent[in] Parent counter name in namespace
*   @param child[out] Pointer to placeholder for set of child counter names
*
*   @return Number of items in the childs name set or 0
*
*   @par Description:
*   Returns the names of the counters that are childs for the parent name.
*   For example following counters exist:\n
*   <i>"ccs.aasyscom.msg.count.send"</i>\n
*   <i>"ccs.aasyscom.msg.count.receive"</i>\n
*   <i>"ccs.aamem.count.alloc"</i>\n
*   \n
*   By setting parent name to <i>"ccs."</i> the return value will be 3 and
*   the childs array will contain three items (all counter names given above).\n
*   By setting parent name to <i>"ccs.aasyscom."</i> the return value will
*   be 2 and the childs array will contain two items:\n
*   <i>"ccs.aasyscom.msg.count.send"</i>\n
*   <i>"ccs.aasyscom.msg.count.receive"</i>\n
*   \n
*   Child name set can be iterated using AaGpuCountGetNextChildName(). User is
*   responsible of freeing the set after usage with AaMemUnRef(). If no matches
*   occurs for given parent name, 0 is returned and #child is left untouched.
*
*   @par Errors:
*   If invalid parameters are given, 0 is returned, #child is left untouched and
*   exception #EAaErrorCcs_AaGpuCount_InvalidParameter is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   See AaGpuCountGetNextChildName
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
*   @see AaGpuCountGetNextChildName
*
******************************************************************************/
size_t
AaGpuCountGetChildNameSet(char const * const parent, TAaGpuCountSet** child);

/**
*******************************************************************************
*
*   @brief  Returns next name from the given set
*
*   @param childSet[in] Set of child
*
*   @return Pointer to the null-terminated name string of GLO_NULL
*
*   @par Description:
*   Pointer to a name is returned until all names are iterated and then
*   GLO_NULL is returned. Iterated set cannot be rewind instead new set must
*   be queried.
*
*   @par Errors:
*   If invalid parameters are given, GLO_NULL is returned and exception
*   #EAaErrorCcs_AaGpuCount_InvalidParameter is raised.
*
*   @par Restrictions:
*   Once iterated, the set is fully consumed thus containing no elements.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuCount.h>
*
*   EAaGpuCountRet rc;
*   TAaGpuCountHandle *counter;
*   size_t childCount;
*   TAaGpuCountSet* childSet;
*   char *childName;
*
*   counter = AaGpuCountAlloc("app.myapp.mycounter"); // Create public counter
*
*   rc = AaGpuCountAddAlias(counter, "app.myapp.aliases.mycounter.alias1");
*   rc = AaGpuCountAddAlias(counter, "app.myapp.aliases.mycounter.alias2");
*   rc = AaGpuCountAddAlias(counter, "app.myapp.mycounter.alias3");
*
*   // Get aliases under namespace "app.myapp.aliases.mycounter" i.e.
*   // "app.myapp.aliases.mycounter.alias1" and "app.myapp.aliases.mycounter.alias2"
*   childCount = AaGpuCountGetChildNameSet("app.myapp.aliases.mycounter", &childSet);
*
*   // Iterate child set (2 child)
*   while ((childName = AaGpuCountGetNextChildName(childSet)) != GLO_NULL)
*   {
*      // Child can be accessed using its name
*
*     // Child name should be freed when no longer needed
*     AaMemUnRef((void const **)&childName);
*   }
*
*   // The set must be freed after it is iterated since it is empty
*   AaMemUnRef(&childSet);
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
*   @see AaGpuCountGetChildNameSet
*
******************************************************************************/
const char*
AaGpuCountGetNextChildName(TAaGpuCountSet* childSet);

/**
*******************************************************************************
*
*   @brief  Dumps all counters via SysLog
*
*   @param None
*
*   @return None
*
*   @par Description:
*   All public counters and their aliases are dumped via SysLog.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuCount.h>
*
*   TAaGpuCountHandle *counter;
*
*   counter = AaGpuCountAlloc("app.ccs.test.foo.1");
*   counter = AaGpuCountAlloc("app.ccs.test.foo.2");
*   counter = AaGpuCountAlloc("app.ccs.test.gpucount.first");
*   AaGpuCountAddAlias(counter, "app.ccs.test.gpucount.alias.first");
*   counter = AaGpuCountAlloc("app.ccs.test.gpucount.second");
*   AaGpuCountAddAlias(counter, "app.ccs.test.gpucount.alias.second");
*   counter = AaGpuCountAlloc("app.ccs.test.gpucount.third");
*
*   AaGpuCountDump();
*
*   // Printout via SysLog looks something like this (SysLog headers stripped):
*    Counter Dump: name [64bit-dec, 64bit-hex] (refs, aliases) {original}
*    CD: app.ccs.test.foo.2 [100000000, 5f5e100] (1, 0)
*    CD: app.ccs.test.foo.1 [100000000, 5f5e100] (1, 0)
*    CD: app.ccs.test.gpucount.first [100000000, 5f5e100] (1, 1)
*    CD: app.ccs.test.gpucount.alias.second [100000000, 5f5e100] (1, 1) {app.ccs.test.gpucount.second}
*    CD: app.ccs.test.gpucount.alias.first [100000000, 5f5e100] (1, 1) {app.ccs.test.gpucount.first}
*    CD: app.ccs.test.gpucount.second [100000000, 5f5e100] (1, 1)
*    CD: app.ccs.test.gpucount.third [100000000, 5f5e100] (1, 0)
*
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   For debugging purpose.
*
*   @par Future directions:
*   None
*
*   @see
*
******************************************************************************/
void
AaGpuCountDump(void);


/** @cond */
/**
*******************************************************************************
*
*   @brief  Frees the child set
*
*   @deprecated It is not necessary to use this function to deallocate child set.
*               Instead it is now possible to directly use AaMemUnRef for deallocation.
*
*   @param child[in] Set of child
*
*   @return none
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
*   @see
*
******************************************************************************/
void
AaGpuCountFreeChildNameSet(TAaGpuCountSet** child);
/** @endcond */

/**@}*/


/** @} */

/*----------------------- PRIVATE INTERFACES --------------------------------*/

/** @name Internal API
*@{
*/

/** @brief Executes CE level initialization */
EAaGpuCountRet AaGpuCountCeInit(void);
/** @brief Executes CE level uninitialization */
EAaGpuCountRet AaGpuCountCeUnInit(void);
/** @brief Executes EE level initialization */
EAaGpuCountRet AaGpuCountEeInit(void);
/** @brief Executes EE level uninitialization */
EAaGpuCountRet AaGpuCountEeUnInit(void);
/** @brief Executes EU level initialization */
EAaGpuCountRet AaGpuCountEuInit(void);
/** @brief Executes EU level uninitialization */
EAaGpuCountRet AaGpuCountEuUnInit(void);

/**@}*/

#ifdef __cplusplus
}
#endif


/*@}*/

#endif /*  _MCU_RT_IFAAGPUCOUNT_H */
