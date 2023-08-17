/** @file
*   @brief Event Duration Measurement Utility API header file
*   @copyright 2014 Nokia Solutions and Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef _MCU_RT_IFAAGPUDUR_H
#define _MCU_RT_IFAAGPUDUR_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
*@addtogroup dgStatistics
*
* @par Event Duration Measurement Utility
* TBD
*
*/

/**
* @addtogroup dpAaStatisticsErrors Error codes
* @ingroup dgStatistics
*
* @verbatim
*  Error code:       EAaErrorCcs_AaGpuDur_InvalidParameter
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
*  Error code:       EAaErrorCcs_AaGpuDur_AllocationFailed
*
*  Severity:         Non-fatal
*
*  Description:      Memory allocation failed which lead to operation failure.
*
*  Extra code:       None
*
*  Recovery actions: None
*
*  See:              None
* @endverbatim
*
* @verbatim
*  Error code:       EAaErrorCcs_AaGpuDur_ReadOnly
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
*@addtogroup dgAaGpuDurApi Event Duration
*@ingroup dgStatisticsApi
*
*
*@{*/

/*----------------------- INCLUDED FILES --------------------------------------*/

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

/* Defines for supporting old API */
#define AaGpuDurGetHandleCopy AaGpuDurGetCopy
#define AaGpuDurGetSetOfChildNames AaGpuDurGetChildNameSet
#define AaGpuDurGetNextNameFromSet AaGpuDurGetNextName
#define AaGpuDurGetLastMicrosU64 AaGpuDurGetLastMicros
#define AaGpuDurGetMinMicrosU64 AaGpuDurGetMinMicros
#define AaGpuDurGetMaxMicrosU64 AaGpuDurGetMaxMicros
#define AaGpuDurGetAvgMicrosU64 AaGpuDurGetAvgMicros
#define AaGpuDurGetLastMicrosU32(__arg) CCS_STATIC_CAST(u32,AaGpuDurGetLastMicros(__arg))
#define AaGpuDurGetMinMicrosU32(__arg) CCS_STATIC_CAST(u32,AaGpuDurGetMinMicros(__arg))
#define AaGpuDurGetMaxMicrosU32(__arg) CCS_STATIC_CAST(u32,AaGpuDurGetMaxMicros(__arg))
#define AaGpuDurGetAvgMicrosU32(__arg) CCS_STATIC_CAST(u32,AaGpuDurGetAvgMicros(__arg))
/** @endcond */

/** @name Public API
*@{
*/

/** @brief Type definition for Duration Measurement Handler */
typedef void TAaGpuDurHandle;
/** @brief Type definition for Duration Measurement Handler set */
typedef void TAaGpuDurSet;

/** @brief Return codes */
typedef enum EAaGpuDurRet
{
    EAaGpuDurRet_Ok = 0,   /**< No errors detected */
    EAaGpuDurRet_Nok,      /**< Invalid parameter given */
    EAaGpuDurRet_ReadOnly, /**< Operation not supported for read-only counters */

    EAaGpuDurRet_NbrOf     /**< Always the last member */
} EAaGpuDurRet;

/*----------------------- PUBLIC INTERFACES --------------------------------*/



/**
 * @defgroup dgAaGpuDurApi Event Duration COMMON API
 * @ingroup  dgStatisticsApiCommon
 */

/* @{ */
/**
*******************************************************************************
*
*   @brief  Allocates a new duration measurement counter
*
*   @param[in] name Namespaced name for the counter or GLO_NULL
*
*   @return Handle to the allocated counter
*
*   @par Description:
*   If name is GLO_NULL, counter is dealt as private and the
*   handle ptr is then the only access to the counter. Otherwise the
*   counter is public and will be stored EE wide and it can be accessed by
*   the name also. If there is already existing counter with same name in
*   current EE, a reference to the existing counter is created instead
*   of new unique one.
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
*   #include <IfAaGpuDur.h>
*
*   TAaGpuDurHandle *counter;
*
*   counter = AaGpuDurAlloc("app.myapp.mycounter"); // Create public counter
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
*   @see AaGpuDurFree
*
******************************************************************************/
TAaGpuDurHandle*
AaGpuDurAlloc(char const * const name);

/**
*******************************************************************************
*
*   @brief  Frees a duration measurement counter
*
*   @param[in] handle  Pointer to the handler of the counter
*
*   @return None
*
*   @par Description:
*   Handler is freed and if the counter the handler refers to is private
*   also the counter is freed.
*
*   @par Errors:
*   If invalid (NULL or otherwice invalid) parameter is given, non-fatal
*   exception #EAaErrorCcs_AaGpuDur_InvalidParameter is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuDur.h>
*
*   TAaGpuDurHandle *counter, *counter2;
*
*   counter = AaGpuDurAlloc("app.myapp.mycounter"); // Create public counter
*   counter2 = AaGpuDurAlloc("app.myapp.mycounter"); // Create new instance to the same counter
*
*   // Use the counter (both instances can be used)
*
*   AaGpuDurFree(counter);
*   AaGpuDurFree(counter2);
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
*   @see AaGpuDurAlloc
*
******************************************************************************/
void
AaGpuDurFree(TAaGpuDurHandle *handle);

/**
*******************************************************************************
*
*   @brief  Returns a read-only copy of a counter corresponding to a name
*
*   @param[in] name Name of the counter
*
*   @return Handle to the counter, GLO_NULL if not found
*
*   @par Description:
*   Returns a read-only copy from a counter which statistics are a snapshot
*   of a certain moment of the requested counter. User is responsible of
*   freeing the handle after usage with AaMemUnRef(). Notice that the copy
*   cannot be used to make new measurements it can be only used to obtain
*   the results.
*   \n\n
*   If the counter needs to be updated, then AaGpuDurAlloc() should be used
*   instead of AaGpuDurGetCopy() for creating new reference to the counter.
*
*   @par Errors:
*   In case of invalid parameter (NULL pointer) non-fatal exception
*   #EAaErrorCcs_AaGpuDur_InvalidParameter is raised and GLO_NULL is returned.
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
*   #include <IfAaGpuDur.h>
*
*   TAaGpuDurHandle *counter, *copy;
*   u64 currentValue, copyValue;
*
*   counter = AaGpuDurAlloc("app.myapp.mycounter"); // Create public counter
*
*   copy = AaGpuDurGetCopy("app.myapp.mycounter"); // Creates a read-only snapshot of the counter
*
*   if (strcmp(AaGpuDurGetName(counter), AaGpuDurGetName(copy)) == 0)
*   {
*       // Both counter handlers have same name since they refer to same counter
*   }
*
*   // Use counter...
*   AaGpuDurStart(counter); // Copy of the counter cannot be used since it is read-only
*
*   AaGpuDurStop(counter); // Copy of the counter cannot be used since it is read-only
*
*   // Get values of both instances
*   currentValue = AaGpuDurGetLastMicros(counter);
*   copyValue = AaGpuDurGetLastMicros(copy);
*
*   if (currentValue != copyValue)
*   {
*       // Values of currentValue and copyValue are not the same since
*       // copyValue has the value of the counter at a certain moment but
*       // currentValue has the latest value
*   }
*
*   // We don't need the copy any longer
*   AaGpuDurCopyFree(copy);
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
*   @see AaGpuDurAlloc
*
******************************************************************************/
TAaGpuDurHandle*
AaGpuDurGetCopy(char const * const name);

/**
*******************************************************************************
*
*   @brief  Frees copy duration measurement counter
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
*   #EAaErrorCcs_AaGpuDur_InvalidParameter is raised. In case of counter is
*   not read-only non-fatal exception #EAaErrorCcs_AaGpuDur_InvalidParameter
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
*   @see AaGpuDurGetCopy
*
******************************************************************************/
void
AaGpuDurCopyFree(TAaGpuDurHandle *handle);

/**
*******************************************************************************
*
*   @brief  Adds alias name for existing counter
*
*   @param[in] handle Handler of the counter
*   @param[in] alias  Name for the alias
*
*   @return EAaGpuDurRet_Ok
*   @return EAaGpuDurRet_InvalidParam
*   @return EAaGpuDurRet_ReadOnly
*
*   @par Description:
*   The counter can be used via both original and alias names. Adding alias name
*   for existing alias name effectively adds the alias for the original name.
*
*   @par Errors:
*   In case the handle is read-only, return code #EAaGpuDurRet_ReadOnly is
*   returned and exception #EAaErrorCcs_AaGpuDur_ReadOnly is raised.
*   If one or both of the parameters are invalid (GLO_NULL or otherwice invalid),
*   return code #EAaGpuDurRet_InvalidParam  is returned and exception
*   #EAaErrorCcs_AaGpuDur_InvalidParameter is raised.
*
*   @par Restrictions:
*   It is not possible to add alias via read-only handler.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuDur.h>
*
*   EAaGpuDurRet rc;
*   TAaGpuDurHandle *counter, *copy1, *copy2, *counter2;
*
*   counter = AaGpuDurAlloc("app.myapp.mycounter"); // Create public counter
*
*   rc = AaGpuDurAddAlias(counter, "app.myapp.aliases.mycounter.alias1");
*   rc = AaGpuDurAddAlias(counter, "app.myapp.aliases.mycounter.alias2");
*
*   // Get copies of the same counter
*   copy1 = AaGpuDurGetCopy("app.myapp.mycounter");
*   copy2 = AaGpuDurGetCopy("app.myapp.aliases.mycounter.alias2");
*
*   // copy1 and copy2 are snapshots of the same counter however since they are
*   // read-only counters, they cannot be used for adding new aliases. Instead
*   // new counter must be allocated using original or alias name.
*
*   counter2 = AaGpuDurAlloc("app.myapp.aliases.mycounter.alias1");
*   rc = AaGpuDurAddAlias(counter2, "app.myapp.aliases.mycounter.alias3");
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
*   @see AaGpuDurAlloc
*
******************************************************************************/
EAaGpuDurRet
AaGpuDurAddAlias(const TAaGpuDurHandle* handle,  char const * const alias);

/**
*******************************************************************************
*
*   @brief  Returns the name of the counter where the handle refers to
*
*   @param[in] handle  Pointer to the handler of the counter
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
*   #include <IfAaGpuDur.h>
*
*   TAaGpuDurHandle *counter;
*   const char *name;
*
*   counter = AaGpuDurAlloc("app.myapp.mycounter"); // Create public counter
*
*   name = AaGpuDurGetName(counter);
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
*   @see AaGpuDurAlloc
*
******************************************************************************/
const char*
AaGpuDurGetName(TAaGpuDurHandle const * const handle);

/**
*******************************************************************************
*
*   @brief  Starts the duration measurement
*
*   @param[in] handle Handle to the counter
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
******************************************************************************/
void AaGpuDurStart(TAaGpuDurHandle *handle);

/**
*******************************************************************************
*
*   @brief  Stops the duration measurement
*
*   @param[in] handle Handle to the counter
*
*   @return none
*       Stops the measurement and counts & stores the current, min, max and average
*       values.
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*        Stop should not be called multiple times as it will mess up the max and
*        average values. Stop should be called only after start.
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
******************************************************************************/
void AaGpuDurStop(TAaGpuDurHandle *handle);

/**
*******************************************************************************
*
*   @brief  Pauses the duration measurement
*
*   @param[in] handle Handle to the counter
*
*   @return none
*       Pausess the measurement.
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*        Pause should not be called multiple times as it will mess up the
*        measurement. Pause should be called only after start or resume,
*        there may be multiple pause-resume sequences during a measurement.
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
******************************************************************************/
void AaGpuDurPause(TAaGpuDurHandle *handle);

/**
*******************************************************************************
*
*   @brief  Resumes the duration measurement
*
*   @param[in] handle Handle to the counter
*
*   @return none
*       Resumes the measurement.
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*        Resume should not be called multiple times as it will mess up the
*        measurement. Resume should be called only after pause. There may be
*        multiple pause-resume sequences during a measurement.
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
******************************************************************************/
void AaGpuDurResume(TAaGpuDurHandle *handle);

/**
*******************************************************************************
*
*   @brief  Resets all measurements
*
*   @param[in] handle Handle to the counter
*
*   @return EAaGpuDurRet_Ok
*   @return EAaGpuDurRet_ReadOnly
*   @return EAaGpuDurRet_InvalidParam
*
*   @par Description:
*   None
*
*   @par Errors:
*   If invalid parameter is given return code #EAaGpuDurRet_InvalidParam is
*   returned and exception #EAaErrorCcs_AaGpuDur_InvalidParameter is raised.
*   \n
*   If given handle is read-only, #EAaGpuDurRet_ReadOnly is returned and
*   exception #EAaErrorCcs_AaGpuDur_ReadOnly is raised.
*
*   @par Restrictions:
*   Counter cannot be reset via read-only handle.
*
*   @par Example:
*
*   @code
*
*
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
*   @see AaGpuDurAlloc
*   @see AaGpuDurStart
*   @see AaGpuDurStop
*   @see AaGpuDurGetLastMicros
*   @see AaGpuDurGetMinMicros
*   @see AaGpuDurGetMaxMicros
*   @see AaGpuDurGetAvgMicros
*
******************************************************************************/
EAaGpuDurRet
AaGpuDurReset(TAaGpuDurHandle *handle);

/**
*******************************************************************************
*
*   @brief  Resets the duration measurement by name
*
*   @param[in] name Name of the duration measurement
*
*   @return EAaGpuDurRet_Nok
*   @return EAaGpuDurRet_Ok
*
*   @par Description:
*   None
*
*   @par Errors:
*   If measurement name is NULL, return code #EAaGpuDurRet_Nok is returned.
*
*   @par Restrictions:
*   None.
*
*   @par Example:
*   None.
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
EAaGpuDurRet
AaGpuDurResetByName(const char * const name);

/**
*******************************************************************************
*
*   @brief Returns last result of the measured duration
*
*   @param[in] handle Handle to the counter
*
*   @return Last duration
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*        Should be used only when measurement is in stopped state
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
******************************************************************************/
u64
AaGpuDurGetLastMicros(TAaGpuDurHandle *handle);

/**
*******************************************************************************
*
*   @brief Returns minimum result of the measured duration
*
*   @param[in] handle Handle to the counter
*
*   @return Minumum duration
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
******************************************************************************/
u64
AaGpuDurGetMinMicros(TAaGpuDurHandle *handle);

/**
*******************************************************************************
*
*   @brief Returns maximum result of the measured duration
*
*   @param[in] handle Handle to the counter
*
*   @return Maximum duration
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
******************************************************************************/
u64
AaGpuDurGetMaxMicros(TAaGpuDurHandle *handle);

/**
*******************************************************************************
*
*   @brief  Returns average result of the measured duration
*
*   @param[in] handle Handle to the counter
*
*   @return Average duration
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
******************************************************************************/
u64
AaGpuDurGetAvgMicros(TAaGpuDurHandle *handle);

/**
*******************************************************************************
*
*   @brief  gets counter names under certain namespace
*
*   @param[in]  parent Parent counter namespace
*   @param[out] child  Pointer to placeholder for set of child counter names
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
*   Child name set can be iterated using AaGpuDurGetNextChildName(). User is
*   responsible of freeing the set after usage with AaMemUnRef(). If no matches
*   occurs for given parent name, 0 is returned and #child is left untouched.
*
*   @par Errors:
*   If invalid parameters are given, 0 is returned, #child is left untouched and
*   exception #EAaErrorCcs_AaGpuDur_InvalidParameter is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   See AaGpuDurGetNextChildName
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
*   @see AaGpuDurGetNextChildName
*
******************************************************************************/
size_t
AaGpuDurGetChildNameSet(char const * const parent, TAaGpuDurSet** child);

/**
*******************************************************************************
*
*   @brief  Returns next name from the given set
*
*   @param[in] child Set of child
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
*   #EAaErrorCcs_AaGpuDur_InvalidParameter is raised.
*
*   @par Restrictions:
*   Once iterated, the set is fully consumed thus containing no elements.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuDur.h>
*
*   EAaGpuDurRet rc;
*   TAaGpuDurHandle *counter;
*   size_t childCount;
*   TAaGpuDurSet* childSet;
*   char *childName;
*
*   counter = AaGpuDurAlloc("app.myapp.mycounter"); // Create public counter
*
*   rc = AaGpuDurAddAlias(counter, "app.myapp.aliases.mycounter.alias1");
*   rc = AaGpuDurAddAlias(counter, "app.myapp.aliases.mycounter.alias2");
*   rc = AaGpuDurAddAlias(counter, "app.myapp.mycounter.alias3");
*
*   // Get aliases under namespace "app.myapp.aliases.mycounter" i.e.
*   // "app.myapp.aliases.mycounter.alias1" and "app.myapp.aliases.mycounter.alias2"
*   childCount = AaGpuDurGetChildNameSet("app.myapp.aliases.mycounter", &childSet);
*
*   // Iterate child set (2 child)
*   while ((childName = AaGpuDurGetNextChildName(childSet)) != GLO_NULL)
*   {
*      // Child can be accessed using its name
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
*   @see AaGpuDurGetChildNameSet
*
******************************************************************************/
const char*
AaGpuDurGetNextName(TAaGpuDurSet* child);

/**
*******************************************************************************
*
*   @brief  frees a set of child counter names
*
*   @param[in] childs Set of child counter names
*
*   @return None
*
*   @par Description:
*   destroys a a set of child counter names.
*
*   @par Errors:
*
*   @par Restrictions:
*   None
*
*   @par Example:
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
*
******************************************************************************/
void
AaGpuDurFreeChildNameSet(TAaGpuDurSet** childs);



/** @} */



/**@}*/

/** @name Internal API
*@{
*/

void AaGpuDurCeInit(void);
void AaGpuDurCeUnInit(void);
void AaGpuDurEeInit(void);
void AaGpuDurEeUnInit(void);

/**@}*/


#ifdef __cplusplus
}
#endif

/*@}*/


#endif /*  _MCU_RT_IFAAGPUDUR_H */
