/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @module                AaFile
*
* Copyright 2017 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _DSP_LITE_IFAAFILE_RAMFS_H
#define _DSP_LITE_IFAAFILE_RAMFS_H

/************************** INCLUDED FILES ************************************/


#include <stddef.h>
#include <CcsCommon.h>
#include <IfAaFile_Defs.h>

#ifndef __CCS_INLINE__
# define __CCS_INLINE__ __inline__
#endif

#ifdef __cplusplus
extern "C" {
#endif

/********************** PUBLIC DECLARATIONS (DSP API) **********************/


/**
 * @addtogroup dgAaFileApiDsp
 * @ingroup    dgAaFile
 */

/* @{ */


/** @brief Return values of callback functions */
typedef enum EAaFileCallbackAction {
     EAaFileCallbackAction_None,          /**< No action is taken. */
     EAaFileCallbackAction_TrashUnused    /**< Trash the file if it is left
                                               unused. No action is taken
                                               if this value is returned from
                                               lock function or if unlocking
                                               was due to truncating a file
                                               that is still in use. */
} EAaFileCallbackAction;


/** @brief Type of the callback function that is used to tell the owner of
 *         a memory mapped file that a user has the file opened.
 */
typedef EAaFileCallbackAction TAaFileCallbackFn(void *arg);


/**@name AaFileRamfs public API
 * @brief Special file handling functions, only implemented in some environments.
 * @{
 */


/**
*******************************************************************************
*
*   @brief    AaFileRamfsSetExt registers a user-managed memory buffer
*             to be used as a file
*
*   @param[in]  fileName     Pointer to string that contains the file name.
*   @param[in]  blockData    Pointer to the start of the file data.
*   @param[in]  blockSize    Length of the file data.
*   @param[in]  lockFnPtr    Pointer to the lock callback function.
*   @param[in]  unlockFnPtr  Pointer to the unlock callback function.
*   @param[in]  callbackArg  Pointer that is passed to callback functions as
*                            parameter.
*
*   @return     #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise.
*
*   @par Description:
*
*   Register a user-managed memory buffer to be used as a file in the
*   filesystem.  If a file with the same name exists, it will be truncated to
*   zero-length before attaching the external memory block to it.
*
*   User of this function guarantees the registered memory to remain valid as
*   long as there is possibility for anyone else to be using the file. For
*   making the memory unaccessible from AaFile one of the following methods is
*   recommended:
*     - Ensure that the memory block is not held locked with callback function,
*       after first calling AaFileRamfsRemove() to prevent any new users for the
*       file.
*     - Remove the file during call to function pointed by unlockFnPtr. This is
*       only supported by returning value #EAaFileCallbackAction_TrashUnused from
*       the unlock function.
*
*   The function pointed by lockFnPtr will be called whenever the file is opened
*   while being unused (not already locked with callback). It will also be
*   called before AaFileRamfsSetExt returns if the file has any users.
*
*   The function pointed by unlockFnPtr will be called whenever the last user
*   closes the file (the file is left unused).
*
*   The pointers to callback functions are optional (may be NULL). However,
*   modifying the file data while some other user has the file opened may cause
*   data corruption. To prevent data corruption by using the callback functions,
*   the user is not allowed to modify the registered memory after the function
*   pointed by lockFnPtr is called, until the function pointed by unlockFnPtr
*   is called to indicate the file is no more open.
*
*   The external memory block will be detached from the file if the file is
*   later truncated to zero-length, i.e. opened in write mode or updated with
*   another call to AaFileRamfsSetExt. The block will also be unlocked with
*   callback if in locked state.
*
*   @par Errors:
*
*   If an internal memory allocation fails, AaFileRamfsSetExt raises
*   exception #EAaErrorCcs_AaFile_MemAllocFailure.
*
*   AaFileRamfsSetExt fails, also raising exception
*   #EAaErrorCcs_AaFile_Exception, if
*      - given file name is empty or NULL
*      - parameter blockData is NULL
*      - given file path contains non-portable characters
*
*   @par Restrictions:
*
*    - AaFileRamfs must have been initialized before calling this function.
*      If AaFile uses AaFileRamfs for ram-volume, the initialization will be
*      done automatically.
*    - The file path can only include portable characters, defined in AaFile
*      API documentation.
*    - The callback functions are not allowed to access any files through AaFile
*      API or wait for any other functions that use AaFile.
*
*   @par Example:
*
*   @code
*
*     // --- One way to use an external file: ---
*
*     static EAaFileCallbackAction lockFn(void *arg) {
*          // External file locked.
*          ...
*          return EAaFileCallbackAction_None;
*     }
*
*     static EAaFileCallbackAction unlockFn(void *arg) {
*          // External file unlocked.
*          ...
*          // Action: Trash the file. The memory block is surely
*          // unaccessible from AaFile after this call returns:
*          return EAaFileCallbackAction_TrashUnused;
*     }
*
*     extern unsigned char *fileData;
*     extern size_t fileDataLen;
*     char *fileName = "testfile.txt";
*
*     ...
*
*     // Register memory block pointed to by fileData as a file.
*     // Variable fileDataLen must contain the correct size of the block.
*     if (EAaFileRet_Ok != AaFileRamfsSetExt(fileName, fileData, fileDataLen,
*                                            lockFn, unlockFn, GLO_NULL)) {
*          // Error
*          ...
*     }
*
*     ...
*
*   @endcode
*
*   @par Example:
*
*   @code
*
*     // --- Another way to use an external file: ---
*
*     static volatile TBoolean fileLocked = GLO_FALSE;
*
*     static EAaFileCallbackAction lockFn(void *arg) {
*          char *fileName = (char *) arg;
*          // External file locked.
*          ...
*          fileLocked = GLO_TRUE;
*          return EAaFileCallbackAction_None;
*     }
*
*     static EAaFileCallbackAction unlockFn(void *arg) {
*          char *fileName = (char *) arg;
*          // External file unlocked.
*          ...
*          fileLocked = GLO_FALSE;
*          return EAaFileCallbackAction_None;
*     }
*
*     extern unsigned char *fileData;
*     extern size_t fileDataLen;
*     char *fileName = "testfile.txt";
*
*     ...
*
*     // Register memory block pointed to by fileData as a file.
*     // Variable fileDataLen must contain the correct size of the block.
*     // Pass fileName as callback function parameter.
*     if (EAaFileRet_Ok != AaFileRamfsSetExt(fileName, fileData, fileDataLen,
*                                            lockFn, unlockFn, fileName)) {
*          // Error
*          ...
*     }
*
*     ...
*
*     // Remove the file from the filesystem:
*     AaFileRamfsRemove(fileName);
*     // Wait until nobody uses the file any more:
*     while (fileLocked) AaSysTimeSleep(100, EAaSysTimeScale_Millisec);
*     // Now fileData buffer is surely unaccessible from AaFile and can
*     // be freely used for other purposes.
*     ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   The restrictions with callback functions in multiple-user situation lay
*   in the fact that existence of the file needs to be guaranteed during the
*   callback calls, and also because callback functions need to be called in
*   correct order (and strictly before/after anyone uses the file). These facts
*   prevent AaFileRamfs from unlocking the file semaphore (if enabled with
*   compile-time option AAFILE_RAMFS_SAFE_FILE) during the callbacks.
*   To prevent deadlocks, this also prevents callback functions from accessing
*   the filesystem, even if the particular file wouldn't need to be touched.
*
*   @par Future directions:
*
*   None
*
*   @see AaFileRamfsRemove()
*
******************************************************************************/
EAaFileRet AaFileRamfsSetExt(const char *fileName, void *blockData, size_t blockSize,
                        TAaFileCallbackFn *lockFnPtr, TAaFileCallbackFn *unlockFnPtr,
                        void *callbackArg);

/**
*******************************************************************************
*
*   @brief    AaFileRamfsRemove removes a file from the filesystem.
*
*   @param[in]  fileName     Pointer to string that contains the file name.
*
*   @return     #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise.
*
*   @par Description:
*
*   Remove a file from the filesystem, making it unaccessible to any new users.
*   Destroy the file as soon as it is left unused (i.e. either on removal or as
*   the last user closes it). Until then, any user that has the file open can
*   continue to access it.
*
*   @par Errors:
*
*   If the file is not found, AaFileRamfsRemove fails without raising
*   exceptions.
*
*   If an internal memory allocation fails, AaFileRamfsRemove raises exception
*   #EAaErrorCcs_AaFile_MemAllocFailure.
*
*   AaFileRamfsRemove fails, also raising exception
*   #EAaErrorCcs_AaFile_Exception, if
*      - given file name is empty or NULL
*      - given file path contains non-portable characters
*
*   @par Restrictions:
*
*   - AaFileRamfs must have been initialized before calling this function.
*     If AaFile uses AaFileRamfs for ram-volume, the initialization will be
*     done automatically.
*   - The file path can only include portable characters, defined in AaFile
*     API documentation.
*
*   @par Example:
*
*   @code
*
*   if (AaFileRamfsRemove("testfile.txt") != EAaFileRet_Ok) {
*      // File not found or something unexpected happened.
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
*
*   @see AaFileRamfsSetExt()
*
******************************************************************************/
EAaFileRet AaFileRamfsRemove(const char *fileName);

/**
*******************************************************************************
*
*   @brief    AaFileRamfsRename renames an existing file
*
*   @param[in]  oldPath  Pointer to string that contains the source filepath
*
*   @param[in]  newPath  Pointer to string that contains the destination filepath
*
*   @return     #EAaFileRet_Ok on success, specific error value otherwise
*
*   @par Description:
*
*   This function renames a file using the given source-filepath to the given
*   destination name using the given destination-filepath.
*
*   @par Return value
*
*   Upon successful completion AaFileRamfsRename shall return EAaFileRet_Ok.
*   Otherwise, an error dependent value shall be returned.
*
*   @par Errors:
*
*   AaFileRamfsRename will return the following values:
*
*   EAaFileRet_EACCES   The new path exists and therefore the source cannot be
*                       renamed. AaFileRamfsRename won't remove the destination
*                       file but will abort renaming process.
*
*   EAaFileRet_EBUSY    The old path is available but in use by another instance.
*                       To assure system integrity no renaming will be made if files
*                       are in use.
*
*   EAaFileRet_ENOENT   The link named by old does not name an existing file,
*                       or either old or new points to an empty string.
*
*   @par Restrictions:
*
*      - Length of the file name cannot exceed #AAFILE_FILENAME_MAX.
*      - The file path can only include portable characters, defined in AaFile
*        API documentation.
*
*   @par Example:
*
*   @code
*
*    char* oldPath = "/ram/oldfile.txt"
*    char* newPath = "/ram/newfile.txt"
*    EAaFileRet retval = EAaFileRet_Error;
*
*    if ((retval = AaFileRamfsRename( oldPath, newPath) != EAaFileRet_Ok) {
*        switch (retval) {
*        case EAaFileRet_EBUSY : printf("file is still in use"); break;
*        case EAaFileRet_ENOENT : printf("file does not exist"); break;
*        case EAaFileRet_EACCES : printf("newPath exists"); break;
*    }
*    ...
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   None
*
*   @par Future directions:
*
*   None
*
*   @see
*
******************************************************************************/
EAaFileRet AaFileRamfsRename(const char *oldPath, const char *newPath);

/* @} */

/* @} */

/*------------------- PUBLIC DECLARATIONS (RT_LINUX_API)  -------------------------*/


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  /* _DSP_LITE_IFAAFILE_RAMFS_H */
