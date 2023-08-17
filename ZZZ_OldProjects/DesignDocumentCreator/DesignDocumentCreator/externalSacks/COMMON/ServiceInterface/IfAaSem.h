/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAASEM_H_
#define _IFAASEM_H_


#include <glo_def.h>
#include <CcsCommon.h>
#include <IfAaFile_Defs.h>        /* Constant definitions */

#ifdef __cplusplus
extern "C" {
#endif


/**
*@defgroup dgAaSem AaSem API
*
* Common Computer and Support SW Configuration AaSem service API.
*/


/**
 * @defgroup dgAaSemApiCommon AaSem COMMON API
 * @ingroup dgAaSem
 */

/* @{ */


/** @brief Maximum semaphore name length in bytes including NUL mark */
#define AASEM_MAX_SEM_NAME_LENGTH 64

/** @brief Type definition for abstract counting semaphore */
typedef struct TAaSem  TAaSem;

/**
*******************************************************************************
*
*   @brief      Creates and initializes a counting semaphore
*
*   @param[out] semPtr        Returns the address of the created semaphore.
*   @param[in]  initialValue  Specifies the initial value for the semaphore
*                             count i.e. the value of a semaphore is the number
*                             of units of the resource which are free.
*
*   @par Description:
*   This function creates and initializes a semaphore and sets the initial
*   count. C stands for counting.
*   Counting semaphore can be used for restricting access to a certain number of
*   shared resources. Setting initial value to 1 makes a semaphore open from the
*   beginning of it's lifecycle.
*
*   @return     None
*
*   @par Errors:(Linux)
*   In case of invalid parameter, exception EAaErrorCcs_AaSem_InvalidParameter
*   is raised. If internal error occurs which leads to semaphore creation failure,
*    a fatal error EAaErrorCcs_AaSem_CreationFailed is raised.
*
*   @par Errors:(OSE)
*   OSE OS does not provide any error return codes for semaphores.
*
*   @par Restrictions:
*   Semaphores can be shared only between EUs residing in the same EE.
*
*   @par Example:
*   Following example shows how to create semaphore
*   @code
*
*   #include <IfAaSem.h>
*
*   TAaSem* semPtr;
*
*   AaSemCreateC(&semPtr, 1);
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
*   @see AaSemCreateNamedC
*   @see AaSemDestroy
*
*******************************************************************************/
void AaSemCreateC( TAaSem** semPtr, u32 initialValue );

/**
*******************************************************************************
*
*   @brief      Creates and initializes a named counting semaphore
*
*   @param[out] semPtr          Returns the address of the created semaphore.
*   @param[in]  namePtr         Pointer to a semaphore name.
*   @param[in]  initialValue    Specifies the initial value for the semaphore
*                               count.
*
*   @par Description:
*   This function creates and initializes a named semaphore and sets the initial
*   count. C stands for counting. Maximum length of the name is specified by
*   #AASEM_MAX_SEM_NAME_LENGTH.
*   \n\n
*   If a semaphore with same name already exist in the CE and it has not been
*   scheduled for termination by AaSemUnlink(), returned semaphore refers to
*   the existing one and initialValue is ignored. If existing semaphore is
*   scheduled for termination, new semaphore with given initial value is created.
*   \n\n
*   Each invocation, in a EE, with same semaphore name, results new semaphore instance
*   refering to same named semaphore.
*   \n\n
*   Semaphore naming should follow namespace definition, however it is not compulsory.
*
*   @return     None
*
*   @par Errors:
*   In case of invalid parameter, exception EAaErrorCcs_AaSem_InvalidParameter
*   is raised. If internal error occurs which leads to semaphore creation failure,
*   EAaErrorCcs_AaSem_CreationFailed is raised. Too long name is considered also
*   as invalid parameter.
*
*   @par Restrictions:
*   Semaphore name cannot exceed #AASEM_MAX_SEM_NAME_LENGTH bytes including ending NUL
*   character. \n\n
*   Semaphore name must not contain any '/' characters.
*
*   @par Example:
*   Following example shows how to create named semaphore
*   @code
*
*   #include <IfAaSem.h>
*
*   TAaSem* semPtr;
*   TAaSem* semPtr2;
*   const char name[AASEM_MAX_SEM_NAME_LENGTH] = "app.myapp.mysem";
*
*   AaSemCreateNamedC(&semPtr, name, 1);
*   AaSemCreateNamedC(&semPtr2, name, 1); // Initial value is ignored
*
*   // Altough semPtr and semPtr2 point to different semaphore instance
*   // they are refering to same named semaphore
*   // semPtr != semPtr2
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
*   @see AaSemCreateC
*   @see AaSemDestroy
*   @see AaSemUnlink
*
*******************************************************************************/
void AaSemCreateNamedC( TAaSem** semPtr,char const* const namePtr, u32 initialValue );

/**
********************************************************************************
*
*   @brief      Destroys the semaphore.
*
*   @param[in]  semPtr   Pointer to the semaphore.
*
*   @par Description:
*   This function destroys the semaphore referenced by #semPtr. Destroying takes
*   place only in current EE, if the semaphore is named and there are references to
*   the semaphore in other EEs.
*   \n\n
*   If the named semaphore, referenced by semPtr, is sheduled earlier for destruction
*   by AaSemUnlink() and this call to AaSemDestroy() is the last, compared to count of
*   AaSemCreateNamedC() calls for the semaphore, the resources reserved for the
*   semaphore shall be destructed CE wide before this call returns.
*   \n\n
*   Subsequent calls to AaSemUnlink() with same name shall be ignored. Also calls to
*   unexistent semaphores shall be silently ignored.
*
*   @return     None
*
*   @par Errors:(OSE)
*   OSE OS does not provide any error return codes for semaphores.
*
*
*    @par Errors:(Linux)
*   It's an error if semPtr is not valid or semaphore is re-destroyed. These cases
*   are reported by raising EAaErrorCcs_AaSem_InvalidParameter exception.
*
*   @par Restrictions:
*   When using this call the semaphore instance must not be locked by any EU in
*   current EE.\n\n
*   This call can only be used conjunction with AaSemCreateC() or
*   AaSemCreateNamedC().
*
*   @par Example:
*
*   @code
*
*   #include <IfAaSem.h>
*
*   const char name[AASEM_MAX_SEM_NAME_LENGTH] = "app.myapp.mysem";
*   TAaSem* semPtr;
*
*   AaSemCreateNamedC(&semPtr, name, 1);
*
*   //... use the new sem ...
*
*   AaSemDestroy(semPtr);
*
*   // Following call opens the same semaphore and initial value is ignored
*   AaSemCreateNamedC(&semPtr, name, 1);
*
*   //... use the sem again ...
*
*   AaSemDestroy(semPtr);
*
*   // This call removes the semaphore permanently from the CE
*   AaSemUnlink(name);
*
*   // Subsequent call to AaSemCreateNamedC after AaSemUnlink shall return
*   // a brand new semaphore
*   AaSemCreateNamedC(&semPtr, name, 1);
*
*   //... use the new sem ...
*
*   AaSemDestroy(semPtr);
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
*   @see AaSemCreateC
*   @see AaSemCreateNamedC
*
******************************************************************************/
void AaSemDestroy(TAaSem* semPtr);


/**
********************************************************************************
*
*   @brief      Unlinks the named semaphore.
*
*   @param[in]  name   The semaphore name.
*
*   @par Description:
*   This function unlinks the named semaphore referenced by the name at CE wide.
*   Since named semaphores may be shared between EEs, it's resources are not released
*   by call to AaSemDestroy() instead this function must be called when the semaphore
*   needs to be removed permanently from the CE.
*   \n\n
*   If there are active references to the named semaphore in other EEs (made by
*   call to AaSemCreateNamedC()), the resource termination may be postponed
*   until all EEs, using the semaphore, have called AaSemDestroy() for the
*   semaphore. Subsequent calls to AaSemUnlink() with same name and unexistent
*   semaphores shall be ignored.
*
*   @return     None
*
*   @par Errors:
*   It's an error if name is invalid i.e. NULL pointer or too long and this is
*   reported by raising EAaErrorCcs_AaSem_InvalidParameter exception.
*
*   @par Restrictions:
*   Semaphore name cannot exceed #AASEM_MAX_SEM_NAME_LENGTH bytes including ending NUL
*   character.
*
*   @par Example:
*   Following example shows how to unlink semaphore
*   @code
*
*   #include <IfAaSem.h>
*
*   const char name[AASEM_MAX_SEM_NAME_LENGTH] = "app.myapp.mysem";
*   TAaSem* semPtr;
*
*   AaSemCreateNamedC(&semPtr, name, 1);
*
*   // ... use the new sem ...
*
*   AaSemDestroy(semPtr);
*
*   // Following call opens the same semaphore and initial value is ignored
*   AaSemCreateNamedC(&semPtr, name, 1);
*
*   // ... use the sem again ...
*
*   AaSemDestroy(semPtr);
*
*   // This call removes the semaphore permanently from the CE
*   AaSemUnlink(name);
*
*   // Subsequent call to AaSemCreateNamedC after AaSemUnlink shall return a brand new semaphore
*   AaSemCreateNamedC(&semPtr, name, 1);
*
*   // ... use the new sem ...
*
*   AaSemDestroy(semPtr);
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
*   @see AaSemCreateNamedC
*
******************************************************************************/
void AaSemUnlink(char const * const name);

/**
*******************************************************************************
*
*   @brief      Decrements the semaphore value.
*
*   @param[in]  semPtr   Pointer to the semaphore.
*
*   @par Description:
*   Decrements the semaphore value referenced by semPtr. If the semaphore value
*   is 0 then the calling EU is suspended and queued in the semaphore queue
*   (NOTE: Depending on the OS and the scheduling mechanism, the queuing policy
*   of EUs waiting for the semaphore may be different. E.g. in some cases
*   higher priority EUs may be queued ahead of lower priority EUS, whereas in
*   some other cases simple FIFO queuing might be applied, etc?.
*   \n\n
*   Each time some other EU posts the semaphore (with AaSemPost()), the value
*   is incremented and the first EU queued at the semaphore is released.
*   Upon successful return, the semaphore value is decremented. If the
*   semaphore value is 0 then EU is suspended.
*
*   @return     None
*
*   @par Errors:
*   It's a fatal error if semPtr is not valid and the error
*   handler will be called.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example shows how to lock semaphore
*   @code
*
*   #include <IfAaSem.h>
*
*   extern TAaSem* semPtr;
*
*   AaSemWait(semPtr);
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
*   @see AaSemCreateC
*   @see AaSemCreateNamedC
*   @see AaSemPost
*   @see AaSemGetValue
*
******************************************************************************/
void AaSemWait(TAaSem* semPtr);

/**
*******************************************************************************
*
*   @brief      Returns the current value of the semaphore
*
*
*   @param[in]  semPtr      Pointer to the semaphore.
*   @param[out] semValuePtr Returns the value of the semaphore.
*
*   @par Description:
*   This function returns the current value of the semaphore referenced by
*   semPtr. If the semaphore is not locked, the return value in semValuePtr is
*   positive and it indicates the number of free resources. If the semaphore is
*   locked, then the value returned in semValuePtr is either 0 (semaphore locked
*   but no other EU is waiting at the semaphore) or a negative number whose
*   absolute value represents the number of EUs waiting for the semaphore.
*
*   @return     None
*
*   @par Errors:
*   If semPtr is not valid exception EAaErrorCcs_AaSem_InvalidParameter
*   is raised.
*
*   @par Restrictions:
*   The updated value in semValuePtr represents an actual semaphore value that
*   occurred at some unspecified time during the call, but it need not be the
*   actual value of the semaphore when it is returned to the calling EU.
*
*   @par Example:
*   Following example shows how to ask current value of semaphore
*   @code
*
*   #include <IfAaSem.h>
*
*   extern TAaSem* semPtr;
*   i32 semValue;
*
*   AaSemGetValue(semPtr, &semValue);
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
*   @see AaSemCreateC
*   @see AaSemCreateNamedC
*   @see AaSemWait
*   @see AaSemPost
*
******************************************************************************/
void AaSemGetValue(TAaSem*  semPtr, i32* semValuePtr);


/**
*******************************************************************************
*
*   @brief      Unlocks the semaphore.
*
*   @param[in]  semPtr  Pointer to the semaphore.
*
*   @par Description:
*   This function unlocks the semaphore referenced by semPtr.
*   If the semaphore value resulting from this operation is positive (i.e. no
*   other EUs were waiting for the semaphore to become unlocked), the semaphore
*   value is simply incremented. If the value of the semaphore resulting from
*   this operation is zero, then the first EU waiting for the semaphore is
*   allowed to return successfully from its call to AaSemWait().
*
*   @return     None
*
*   @par Errors:
*   If semPtr is not valid exception EAaErrorCcs_AaSem_InvalidParameter
*   is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example shows how to unlock semaphore
*   @code
*
*   #include <IfAaSem.h>
*
*   extern TAaSem* semPtr;
*
*   AaSemPost(semPtr);
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
*   @see AaSemCreateC
*   @see AaSemCreateNamedC
*   @see AaSemWait
*   @see AaSemGetValue
*
******************************************************************************/
void AaSemPost(TAaSem* semPtr);


/**
*******************************************************************************
*
*   @brief      Decrements the semaphore value and changes EU
*               priority before that.
*
*   @param[in]  semPtr      Pointer to the semaphore.
*   @param[in]  priority    EU priority to be changed
*
*   @par Description:
*   Decrements the semaphore value referenced by semPtr. If the semaphore value
*   is 0 then the calling EU is suspended and queued in the semaphore queue
*   (NOTE: Depending on the OS and the scheduling mechanism, the queuing policy
*   of EUs waiting for the semaphore may be different. E.g. in some cases
*   higher priority EUs may be queued ahead of lower priority EUS, whereas in
*   some other cases simple FIFO queuing might be applied, etc.).
*   Each time some other EU posts the semaphore (with AaSemPost()), the value
*   is incremented and the first EU queued at the semaphore is released.
*   Upon successful return, the semaphore value is decremented. If the
*   semaphore value is 0 then EU is suspended.
*
*   @return     None
*
*   @par Errors:
*   If semPtr is not valid exception EAaErrorCcs_AaSem_InvalidParameter
*   is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example shows how to lock semaphore
*   @code
*
*   #include <IfAaSem.h>
*
*   extern TAaSem* semPtr;
*   u32 priority = EU_PRIORITY_08;
*
*   AaSemWaitPri(semPtr, priority);
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
*   @see AaSemCreateC
*   @see AaSemCreateNamedC
*   @see AaSemPostPri
*   @see AaSemGetValue
*
******************************************************************************/
void AaSemWaitPri(TAaSem* semPtr, u32 priority);

/**
*******************************************************************************
*
*   @brief      Unlocks the semaphore and changes EU priority
*               back to original.
*
*   @param[in]  semPtr  Pointer to the semaphore.
*
*   @par Description:
*   This function unlocks the semaphore referenced by semPtr.
*   If the semaphore value resulting from this operation is positive (i.e. no
*   other EUs were waiting for the semaphore to become unlocked), the semaphore
*   value is simply incremented. If the value of the semaphore resulting from
*   this operation is zero, then the first EU waiting for the semaphore is
*   allowed to return successfully from its call to AaSemWait().
*
*   @return     None
*
*   @par Errors:
*   If semPtr is not valid exception EAaErrorCcs_AaSem_InvalidParameter
*   is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Following example shows how to unlock semaphore
*   @code
*   
*   #include <IfAaSem.h>
*
*   extern TAaSem* semPtr;
*
*   AaSemPostPri(semPtr);
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
*   @see AaSemCreateC
*   @see AaSemCreateNamedC
*   @see AaSemWaitPri
*   @see AaSemGetValue
*
******************************************************************************/
void AaSemPostPri(TAaSem* semPtr);

/* @} */


#ifdef __cplusplus
}
#endif


#endif /* _IFAASEM_H_*/
