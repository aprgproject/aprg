/** @file
*   @brief AaFile common function prototypes.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2017-2019 Nokia. All rights reserved.$
*/

#ifndef _COMMON_IF_AAFILE_H_
#define _COMMON_IF_AAFILE_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include <stddef.h>

#include <../../COMMON/Definitions/IfAaFile_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* Runtime configuration can be divided into pre- and post-configuration phases.
* Pre-configuration takes place before CE startup has been done for a service.
* Post-configuration takes place after CE, EE and EU startup. Configuration is
* handled using so called attribute/configuration tags. Data and keys are variable
* width in size so they are quite flexible to use.
* \n\n
* Usually configuration tags are used for input direction i.e. feeding
* configuration to CC&S service. However some tags can also be used for output
* direction i.e. for advertising CC&S service state or capabilities. Configuration
* tag description should state wether the tag is inteded for feeding information
* (input) to the service or the service uses the tag for capability and state
* advertisement (output).
*
*
* See also [CCSAPI_VARIABILITY] for more details about environments.
*<a href="doors://XESDOORSP01.EXT.NOKIA.COM:36655/?version=1,prodID=0,dbid=4017b9fe29051a61,container=00002def,object=77">
*[BTSC_CCS_220]
*</a>
*
*
* @verbatim
*  Tag name:        sys.fs.temp.path
*
*  Direction:       input
*
*  Description:     Temporary file storage path, used by AaFile as physical path
*                   for ram-volume. See [BTSC_CCS_220]
*                   (Note: path should contain a trailing slash)
*
*  Effect analysis: If this tag is not set, a default directory is used for ram-volume,
*                   and there will be no indication when temporary filesystem has
*                   been initialized. This means the user must have another way to ensure
*                   that the file system is fully initialized before using it.
*
*  Restriction:     Not in use on some environments.
*                   See [CCSAPI_VARIABILITY] for more details.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_TEMP_PATH
*
*  See:             AACONFIG_TAG_NAME_TEMP_ONLINE
* @endverbatim
*
*
* @verbatim
*  Tag name:        sys.fs.persistent.path
*
*  Direction:       input
*
*  Description:     Persistent file storage path, used by AaFile as physical path
*                   for rom-volume. See [BTSC_CCS_220].
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, a default directory is used for rom-volume,
*                   and there will be no indication when persistent filesystem has
*                   been initialized. This means the user must have another way to ensure
*                   that the file system is fully initialized before using it.
*
*  Restriction:     Not in use on some environments.
*                   See [CCSAPI_VARIABILITY] for more details.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_PERSISTENT_PATH
*
*  See:             AACONFIG_TAG_NAME_PERSISTENT_ONLINE
* @endverbatim
*
*
* @verbatim
*  Tag name:        sys.fs.temp.online
*
*  Direction:       output
*
*  Description:     This tag indicates that temporary filesystem, including AaFile
*                   ram-volume, is up and running.
*                   AaFile sets this tag after tag AACONFIG_TAG_NAME_TEMP_PATH
*                   is set and AaFile ram-volume has been initialized successfully.
*
*  Effect analysis: N/A
*
*  Restriction:     Not in use on some environments.
*                   See [CCSAPI_VARIABILITY] for more details.
*
*  Value:           IE Type:     Size:     Range:
*                   number       i32       1           - Temporary filesystem is
*                                                        configured and online.
*                                          0 / not set - Default configuration for temporary
*                                                        filesystem is being used.
*
*  Define:          AACONFIG_TAG_NAME_TEMP_ONLINE
*
*  See:             AACONFIG_TAG_NAME_TEMP_PATH
* @endverbatim
*
*
* @verbatim
*  Tag name:        sys.fs.persistent.online
*
*  Direction:       output
*
*  Description:     This tag indicates that persistent filesystem, including AaFile
*                   rom-volume, is up and running.
*                   AaFile sets this tag after tag AACONFIG_TAG_NAME_PERSISTENT_PATH
*                   is set and AaFile rom-volume has been initialized successfully.
*
*  Effect analysis: N/A
*
*  Restriction:     Not in use on some environments.
*                   See [CCSAPI_VARIABILITY] for more details.
*
*  Value:           IE Type:     Size:     Range:
*                   number       i32       1           - Persistent filesystem is
*                                                        configured and online.
*                                          0 / not set - Default configuration for persistent
*                                                        filesystem is being used.
*
*  Define:          AACONFIG_TAG_NAME_PERSISTENT_ONLINE
*
*  See:             AACONFIG_TAG_NAME_PERSISTENT_PATH
* @endverbatim
*
*
* @verbatim
*  Tag name:        sys.fs.secure.mountpoint
*
*  Direction:       input
*
*  Description:     Mount-point of the secure-storage volume
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, a default mount-point is used for
*                   mounting the SecureStorage-volume.
*
*  Restriction:     None
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_SECURE_MOUNT_POINT
*
*  See:             None
* @endverbatim
*
* @verbatim
*  Tag name:        sys.fs.secure.volume
*
*  Direction:       input
*
*  Description:     Name of the secure-storage volume
*
*  Effect analysis: If this tag is not set, a default volume name is used
*                   for the SecureStorage-volume.
*
*  Restriction:     None
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_SECURE_VOLUME
*
*  See:             None
*
* @endverbatim
*
* @verbatim
*  Tag name:        sys.fs.ffs.path
*
*  Direction:       input
*
*  Description:     mount point path for Flash File System (FFS), used by SW Management.
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, the ffs-volume can't be used.
*
*  Restriction:     Not in use on some environments.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_FFS_PATH
*
*  See:             None
* @endverbatim
*
* @verbatim
*  Tag name:        sys.fs.ffs1.path
*
*  Direction:       input
*
*  Description:     mount point path for Flash File System 1 (FFS1), used by SW Management.
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, the ffs1-volume can't be used.
*
*  Restriction:     Not in use on some environments.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_FFS1_PATH
*
*  See:             None
* @endverbatim
*
* @verbatim
*  Tag name:        sys.fs.ffs2.path
*
*  Direction:       input
*
*  Description:     mount point path for Flash File System 2 (FFS2), used by SW Management.
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, the ffs2-volume can't be used.
*
*  Restriction:     Not in use on some environments.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_FFS2_PATH
*
*  See:             None
* @endverbatim
*
* @verbatim
*  Tag name:        sys.fs.ffs3.path
*
*  Direction:       input
*
*  Description:     mount point path for Flash File System 3 (FFS3), used by SW Management.
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, the ffs3-volume can't be used.
*
*  Restriction:     Not in use on some environments.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_FFS3_PATH
*
*  See:             None
* @endverbatim
*
* @verbatim
*  Tag name:        sys.fs.ffs4.path
*
*  Direction:       input
*
*  Description:     mount point path for Flash File System 4 (FFS4), used by SW Management.
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, the ffs4-volume can't be used.
*
*  Restriction:     Not in use on some environments.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_FFS4_PATH
*
*  See:             None
* @endverbatim
*
* @verbatim
*  Tag name:        sys.fs.rpram.path
*
*  Direction:       input
*
*  Description:     mount point path for reset proof ram (RPRAM).
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, the rpram-volume can't be used.
*
*  Restriction:     Not in use on some environments.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_RPRAM_PATH
*
*  See:             None
* @endverbatim
*
*
* @verbatim
*  Tag name:        sys.fs.logs.path
*
*  Direction:       input
*
*  Description:     mount point path for logs volume (LOGS).
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, the logs-volume can't be used.
*
*  Restriction:     Not in use on some environments.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_LOGS_PATH
*
*  See:             None
* @endverbatim
*
*
* @verbatim
*  Tag name:        sys.fs.raml.path
*
*  Direction:       input
*
*  Description:     mount point path for ram logs volume (RAML).
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, the ram-logs-volume can't be used.
*
*  Restriction:     Not in use on some environments.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_RAML_PATH
*
*  See:             None
*
*
* @endverbatim
*
* @verbatim
*  Tag name:        sys.fs.stb.path
*
*  Direction:       input
*
*  Description:     mount point path for stb volume (STB).
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, the stb-volume can't be used.
*
*  Restriction:     Not in use on some environments.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_STB_PATH
*
*  See:             None
* @endverbatim
*
* @verbatim
*  Tag name:        sys.fs.data.path
*
*  Direction:       input
*
*  Description:     mount point path for data volume.
*                   (Note: path should contain a trailing slash.)
*
*  Effect analysis: If this tag is not set, the data volume can't be used.
*
*  Restriction:     Only available on AirScale family and newer products.
*
*  Value:           IE Type:                   Size:             Range:
*                   zero-terminated string     N/A               N/A
*
*  Define:          AACONFIG_TAG_NAME_DATA_PATH
*
*  See:             None
* @endverbatim
*/

/**
* Exception codes are used with Error Management Service (AaError) and they describe
* various error situations a service may have and report. Important part of exception
* is the severity. Usually it is non-fatal thus execution of application continues
* after the exception reporting but in some special case execution is prohibited and
* the application is eventually terminated.
*
*
* See [CCSAPI_VARIABILITY] for more details about environments.
*
* @verbatim
*  Error code:       EAaErrorCcs_AaFile_MemAllocFailure
*
*  Severity:         Non-fatal
*
*  Description:      Internal memory allocation failed.
*                    This is a serious error that usually causes AaFile to
*                    abort whatever it was trying to do.
*
*  Extra code:       None
*
*  Recovery actions: None
*
*  See:              None
* @endverbatim
*
*
* @verbatim
*  Error code:       EAaErrorCcs_AaFile_InvalidVolume
*
*  Severity:         Non-fatal
*
*  Description:      Requested volume is not found.
*                    Either the volume name is invalid or the volume is
*                    not implemented in the system.
*
*  Extra code:       None
*
*  Recovery actions: None
*
*  See:              None
* @endverbatim
*
*
* @verbatim
*  Error code:       EAaErrorCcs_AaFile_Exception
*
*  Severity:         Non-fatal
*
*  Description:      AaFile generic exception code.
*
*  Extra code:       None
*
*  Recovery actions: None
*
*  See:              None
* @endverbatim
*/

/**
 * @defgroup dgAaFile AaFile API
 */

/**
 * @defgroup dgAaFileApiCommon AaFile COMMON API
 * @ingroup  dgAaFile
 */

/** @{ */

/************************** PUBLIC INTERFACES *********************************/

/**@name AaFile common operations
 * @brief File and stream handling functions available in all environments
 */

/** @{ */

/**
*******************************************************************************
*
*   @brief    AaFileOpen() opens a file and returns an associated stream.
*
*   @param[in]  fileName   File path for file to be opened.
*                          (given in AaFile notation: [ volume ] + path)
*   @param[in]  mode       Pattern for opening mode.
*
*   @return                Stream object pointer.
*                          \c GLO_NULL is returned if an error occured.
*
*   @par Description:
*
*   AaFileOpen() opens a file from underlaying filesystem, allocates and
*   returns a stream object which has to be used for further file access. (The
*   stream may be buffered or unbuffered, depending on the implementation.)
*
*   Only the following modes are supported:
*
*   @code
*         r     Open file for reading.
*         w     Truncate to zero length or create file for writing.
*         a     Append; open or create file for writing at end-of-file.
*         r+    Open file for update (reading and writing).
*         w+    Truncate to zero length or create file for update.
*         a+    Append; open or create file for update, writing at end-of-file.
*   @endcode
*
*   @note Legacy mode 'b' is allowed as well, even if not used internally. So in principle
*         also mode strings like 'rb' and 'wb' would be accepted.
*         For files on the secure storage (volume '/safe/') only the modes 'r' and 'w'
*         are allowed, where 'r+', 'w+', 'a' and 'a+' are forbidden.
*
*   @par Errors:
*
*   Function returns \c GLO_NULL in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*      - Length of the file name cannot exceed #AAFILE_FILENAME_MAX.
*      - The file path can only include portable characters, defined in AaFile
*        API documentation.
*      - For secure file storage only mode 'w' or 'r' is allowed
*
*   @par Example:
*
*   @code
*
*    TAaFile *stream;
*    char *fileName = "/ram/testfile.txt";
*    if ( GLO_NULL == (stream = AaFileOpen(fileName, "r")) ) {
*        // Error. Maybe file not found?
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
TAaFile *AaFileOpen(const char *fileName, const char *mode);

/**
*******************************************************************************
*
*   @brief    AaFileOpenErrno() opens a file and returns an associated stream,
*             along with the errno (in case of failures).
*
*   @param[in]  filename   File path for file to be opened.
*                          (given in AaFile notation: [ volume ] + path)
*   @param[in]  mode       Pattern for opening mode.
*   @param[in]  eno        Container to return the errno to the caller. It
*                          will be used internally only if provided.
*                          If it is not provided, the function will behave exactly
*                          like AaFileOpen() API.
*
*   @return                Stream object pointer.
*                          \c GLO_NULL is returned if an error occured.
*
*   @par Description:
*
*   AaFileOpenErrno() behaves like the AaFileOpen() but in addition it
*   provides support for returning to the caller the OS-provided errno
*   (for erroneous cases).
*   Behavior:
*     - if a non-null stream is returned then open worked and eno is not defined
*     - if a null stream is returned and eno is 0, then the error was not based
*       on any problem with fopen.
*       These errors would be anything AaFile related (e.g. illegal file name,
*       memory allocation failure, etc.). Such errors still would be printed as
*       in AaFileOpen().
*     - if a null stream is returned and eno is not 0, then the error is based
*       on a errno problem after fopen. These errors would be not be printed
*       and the user can decide in his context if it is a problem or not.
*
*   @note Same modes as in AaFileOpen() case are supported.
*
*   @par Errors:
*
*   Function returns \c GLO_NULL in case of error and prints error message in logs.
*   In case an internal error occurs, as a result of a system call, the related
*   errno will be returned to the caller in the eno param.
*
*   @par Restrictions:
*
*      - Same restrictions as in AaFileOpen() case apply
*
*   @par Example:
*
*   @code
*
*    TAaFile *stream;
*    int eno = 0;
*    char *fileName = "/ram/testfile.txt";
*    if ( GLO_NULL == (stream = AaFileOpenErrno(fileName, "r", &eno)) ) {
*        // Error. Maybe file not found?
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
TAaFile* AaFileOpenErrno(const char* filename, const char* mode, int* eno);

/**
******************************************************************************
*   @brief    AaFileOpenWithLock() opens a file in locked mode, and returns an
*             associated stream. (Locked mode means: during file is opened,
*             implicitly a lock file is existing. When closing the file, the
*             related lock file will be removed. A file cannot be openend with
*             this function if a related lock file exists already!)
*
*   @param[in]  fileName  File path for file to be opened in locked mode.
*                         (Given in AaFile notation: [ volume ] + path)
*   @param[in]  mode      Pattern for opening mode.
*   @param[out] locked    Flag that indicates (in case of failed opening) if
*                         failing was caused by file locking or by another
*                         reason. If function returns \c GLO_NULL and locked
*                         is \c GLO_TRUE, then a lock file exists.
*
*   @return               Stream object pointer.
*                         \c GLO_NULL is returned if file is currently locked or
*                         if an error occured. (In case of locked files,
*                         reference parameter locked will be set to \c GLO_TRUE.)
*
*   @par Description:
*
*   First of all AaFileOpenWithLock() checks whether a related lock file exists.
*   (The lock file name is derived with certain rules from passed file name.)
*   If the lock file exists, the function returns \c GLO_NULL and sets reference
*   parameter locked to \c GLO_TRUE.
*   Only if no related lock file exists, the function creates a new lock file,
*   opens a file from underlaying filesystem, allocates and returns a stream
*   object which has to be used for further file access. (The stream may be
*   buffered or unbuffered, depending on the implementation.)
*   Be aware that AaFileClose() will remove related lock file again. Therefore
*   the mechanism is used to detect files, which are not yet or never closed.
*   More specifically: if a lock file exists after reset, it is a hint that previous
*   reset was caused by error and related file might be corrupt.
*
*   @note
*   It is up to the user to choose proper actions when a lock file is detected
*   during startup at very first access.
*   Lock file cleanup is supported through function AaFileForceUnlock().
*
*   @note Same modes as in AaFileOpen() case are supported.
*
*   @par Errors:
*
*   Function returns \c GLO_NULL in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*      - Same restrictions as in AaFileOpen() case apply, the only difference being that
*       length of file name cannot exceed #AAFILE_FILENAME_MAX - 5.
*
*   @par Example:
*
*   @code
*
*    TAaFile *stream = GLO_NULL;
*    TBoolean locked = GLO_FALSE;
*    char *fileName = "/ram/testfile.txt";
*    if ( GLO_NULL == (stream = AaFileOpenWithLock(fileName, "w", &locked)) ) {
*       if (locked) { // Error. File could not be opened, since locked! }
*       else { // Error. File could not be opened by other reasons. }
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
*   @see AaFileClose()
*   @see AaFileForceUnlock()
*
******************************************************************************/
TAaFile *AaFileOpenWithLock(const char *fileName, const char *mode, TBoolean* locked);

/**
*******************************************************************************
*
*   @brief    AaFileRemove removes a file from the filesystem.
*
*   @param[in]  fileName   Pointer to string that contains the file name
*                          and optional volume name.
*
*   @return     #EAaFileRet_Ok on success, appropriate error otherwise.
*
*   @par Description:
*
*   This function removes a file from underlaying filesystem.
*
*   @par Errors:
*
*   - #EAaFileRet_ENOENT:            \p fileName is \c GLO_NULL or empty, or contains invalid AaFile volume.
*   - #EAaFileRet_NONPORTABLEFILE:   \p fileName do not conform to AaFile path notation.
*   - #EAaFileRet_ENOMEM:            Failed to allocate memory for internal buffer.
*   - #EAaFileRet_Error:             For all other errors.
*
*   @par Restrictions:
*
*      - Length of the file name cannot exceed #AAFILE_FILENAME_MAX.
*      - The file path can only include portable characters, defined in AaFile
*        API documentation.
*      - Result of removing an open file is unspecified and depends on the
*        implementation. Application shall ensure that any file is not removed
*        while it is in use.
*
*   @par Example:
*
*   @code
*
*    if (AaFileRemove("testfile.txt") != EAaFileRet_Ok) {
*        // Error. File not found or removal failed.
*    }
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
EAaFileRet AaFileRemove(const char *fileName);

/**
*******************************************************************************
*
*   @brief    AaFileClose() closes a stream.
*             (If stream was opened with AaFileOpenWithLock() instead of
*              AaFileOpen(), it also removes related lock file.)
*
*   @param[in]  stream   Pointer to the stream object.
*
*   @return     #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise.
*
*   @par Description:
*
*   This function unallocates the stream and closes the associated file.
*   For buffered streams, flushing will be performed automatically.
*   If stream was opened with AaFileOpenWithLock(), additionally the
*   related lock file is removed.
*   On closing the stream, internally, the user-space buffers are flushed
*   subsequently to kernel-space then to the actual destination.
*
*   @par Errors:
*
*   Function returns #EAaFileRet_Error in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    TAaFile *stream;
*    char *fileName = "testfile.txt";
*    if ((stream = AaFileOpen(fileName, "w")) == GLO_NULL) {
*        // Error. Something weird happened.
*    }
*    ...
*
*    if (AaFileClose(stream) != EAaFileRet_Ok) {
*        // Error. Should not happen.
*    }
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
*   @see AaFileOpen()
*   @see AaFileOpenWithLock()
*
******************************************************************************/
EAaFileRet AaFileClose(TAaFile *stream);

/**
*******************************************************************************
*
*   @brief    AaFileExists() checks existence of a file.
*
*   @param[in]  fileName   Pointer to string that contains the file name
*                          and optional volume name.
*
*   @return     \c GLO_TRUE if file exists, \c GLO_FALSE in case it is missing or errors
*               where encountered during execution.
*
*   @par Description:
*
*   This function checks whether a file given as input parameter exists or not.
*
*   @par Errors:
*
*   Function returns \c GLO_FALSE in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*   char *fileName = "testfile.txt";
*   if ( GLO_TRUE == AaFileExists(fileName) ) {
*      // file is existing
*   }
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
*   @see AaFileOpen()
*
******************************************************************************/
TBoolean AaFileExists(const char* fileName);

/**
*******************************************************************************
*
*   @brief    AaFileForceUnlock() removes the lock file which is related to
*             given file name. (Lock files are created, when a file is opened
*             with AaFileOpenWithLock()).
*
*   @param[in]  filename  File path for file to be opened.
*                         (given in AaFile notation: [ volume ] + path)
*
*   @return     #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise.
*
*   @par Description:
*
*   AaFileForceUnlock() derives the name of related lock file, fitting to
*   passed file name, and removes the lock file.
*   The function mainly is used to cleanup after corrupted or failing
*   AaFileOpenWithLock()-AaFileClose() sequences.
*
*   @par Errors:
*
*   Function returns #EAaFileRet_Error in case of error and prints error message in logs.
*
*   @par Restrictions:
*     - Length of the file name or length of derived lock file name cannot
*       exceed #AAFILE_FILENAME_MAX - 5.
*     - The file path can only include portable characters, defined in AaFile
*       API documentation.
*
*   @par Example:
*
*   @code
*
*    TAaFile *stream = GLO_NULL;
*    TBoolean locked = GLO_FALSE;
*    char *fileName = "/ram/testfile.txt";
*    if ( GLO_NULL == (stream = AaFileOpenWithLock(fileName, "w", &locked)) ) {
*       if (locked) {
*           // Handle error
*           ...
*           // Cleanup
*           if ( EAaFileRet_Ok != AaFileForceUnlock(fileName) ) {
*               // Error. This is not expected!
*           }
*       } else { // Error. File could not be opened by other reasons. }
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
*   @see AaFileOpenWithLock()
*   @see AaFileClose()
*
******************************************************************************/
EAaFileRet AaFileForceUnlock(const char *filename);

/**
*******************************************************************************
*
*   @brief    AaFileRead reads data from the stream.
*
*   @param[in,out]   ptr     Pointer to the array into which the elements will
*                            be copied.
*   @param[in]       size    Size of one element in bytes.
*   @param[in]       nitems  Requested number of elements to read.
*   @param[in]       stream  Pointer to the stream object.
*
*   @return     Number of elements succesfully read.
*
*   @par Description:
*
*   The function reads given number of elements from the stream.
*   The stream position (i.e. file position indicator for the stream) shall be
*   advanced by the number of bytes successfully read. If an error occurs,
*   the resulting value of the file position indicator for the stream is
*   unspecified. If a partial element is read, its value is unspecified.
*
*   @par Errors:
*
*   Function returns 0 in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    TAaFile *stream;
*    char buf[MY_BUFSIZE];
*
*    if ((stream = AaFileOpen("testfile.txt", "r")) == GLO_NULL) {
*        // Error. Maybe file not found?
*        ...
*    }
*    if (AaFileRead(buf, 1, MY_BUFSIZE, stream) != MY_BUFSIZE) {
*        // Probably EOF.
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
size_t AaFileRead(void *ptr, size_t size, size_t nitems, TAaFile *stream);

/**
*******************************************************************************
*
*   @brief    AaFileReadLine reads data from a stream line by line.
*
*   @param[in,out]   buf     Pointer to the line buffer to which the line
*                            will be copied.
*   @param[in]       size    Size of line buffer
*   @param[in]       stream  Pointer to the stream object.
*
*   @return  Pointer to begin of line that was successfully read (which is the
*            pointer to passed user buffer), or \c GLO_NULL otherwise.
*
*   @par Description:
*
*   The function reads from the stream the next bytes until either
*      - EOL (end of line '\\n')
*      - maximal allowed number of bytes - 1 (size of line buffer with trailing '\\0')
*   or
*      - EOF (end of file)
*   is reached.
*   In any case the result is followed by a trailing '\\0'.
*
*   Note: be aware that as end of line character only '\\n' is considered!
*
*   @par Errors:
*
*   Function returns \c GLO_NULL in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*   None
*
*   @code
*
*    TAaFile *stream;
     char *line;
*    char lineBuf[MAX_LINE_LENGTH];
*
*    if ( GLO_NULL == (stream = AaFileOpen("testfile.txt", "r")) ) {
*        // Error handling
*        ...
*    }
*
*    do {
*        line = AaFileReadLine(lineBuf, MAX_LINE_LENGTH, stream);
*        ...
*    } while (line);
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
*   @see AaFileRead()
*
******************************************************************************/
char* AaFileReadLine(char *buf, size_t size, TAaFile *stream);

/**
*******************************************************************************
*
*   @brief    AaFileWrite writes data to the stream.
*
*   @param[in,out]   ptr     Pointer to the array from which the elements
*                            will be copied.
*   @param[in]       size    Size of one element in bytes.
*   @param[in]       nitems  Requested number of elements to write.
*   @param[in]       stream  Pointer to the stream object.
*
*   @return     Number of elements succesfully written.
*
*   @par Description:
*
*   The function writes given number of elements to the stream.
*   The stream position (i.e. file position indicator for the stream) shall be
*   advanced by the number of bytes successfully written. If an error occurs,
*   the resulting value of the file position indicator for the stream is
*   unspecified.
*
*   @note  If the stream is buffered, flushing may be required to actually write
*          the data to the target location. Flushing will be done automatically
*          as the stream is closed.
*
*   @par Errors:
*
*   Function returns 0 in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*   None
*
*   @par Example:
*
*   @code
*
*    extern char buf[];
*    TAaFile *stream;
*
*    if ((stream = AaFileOpen("testfile.txt", "w")) == GLO_NULL) {
*        // Something's wrong.
*        ...
*    }
*    if (AaFileWrite(buf, 1, MY_BUFSIZE, stream) != MY_BUFSIZE) {
*        // Something's wrong.
*        ...
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
size_t AaFileWrite(void *ptr, size_t size, size_t nitems, TAaFile *stream);

/**
*******************************************************************************
*
*   @brief    AaFileSeek seeks the stream position.
*
*   @param[in]   stream  Pointer to the stream object.
*   @param[in]   offset  The new stream position (signed value)
*                        measured from position indicated by parameter whence.
*   @param[in]   whence  The file position from which the new position will be
*                        measured.
*
*   @return     #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise
*
*   @par Description:
*
*   The function sets the file-position indicator for the stream.
*
*   The parameter whence must be one of the following constants:
*
*      - #AAFILE_SEEK_CUR        seek relative to current stream position.
*      - #AAFILE_SEEK_END        seek relative to the end of file.
*      - #AAFILE_SEEK_SET        seek relative to the beginning of file.
*
*   @note If the stream refers to a secure storage file, this function is not applicable.
*
*   @par Errors:
*
*   Function returns #EAaFileRet_Error in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*     - Function is not applicable on secure storage streams.
*
*   @par Example:
*
*   @code
*
*    TAaFile *stream;
*
*    if ((stream = AaFileOpen("testfile.txt", "r")) == GLO_NULL) {
*        // Error. Maybe file not found?
*        ...
*    }
*    // Set position before the last byte
*    if (AaFileSeek(stream, -1, AAFILE_SEEK_END) != EAaFileRet_Ok) {
*        // The file may be empty.
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
EAaFileRet AaFileSeek(TAaFile *stream, long offset, int whence);

/**
*******************************************************************************
*
*   @brief    AaFileTell tells the stream position.
*
*   @param[in]   stream  Pointer to the stream object.
*
*   @return   current stream position (which is always >=0), -1 otherwise
*
*   @par Description:
*
*   The function tells the file-position indicator of the stream.
*
*   @note If the stream refers to a secure storage file, this function is not applicable.
*
*   @par Errors:
*
*   Function returns -1 in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*     - Function is not applicable on secure storage streams.
*
*   @par Example:
*
*   @code
*
*    extern char buf[];
*    TAaFile *stream;
*    long spos;
*
*    if ((stream = AaFileOpen("testfile.txt", "w")) == GLO_NULL) {
*        // Error. File could not be opened. Maybe access rights?
*        ...
*    }
*    // Write data to the file
*    if (AaFileWrite(buf, 1, MY_BUFSIZE, stream) != MY_BUFSIZE) {
*        // Something's wrong.
*        ...
*    }
*    if ( 0 > (spos = AaFileTell(stream)) ) {
*        // Something's wrong.
*        ...
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
long AaFileTell(TAaFile *stream);

/**
*******************************************************************************
*
*   @brief    AaFileFlush() flushes the stream.
*
*   @param[in]   stream  Pointer to the stream object.
*
*   @return     #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise
*
*   @par Description:
*
*   If the stream is unbuffered, this function does nothing.
*   As a buffered stream is flushed, a part of the buffer, including any new
*   data written to the stream by the user, shall be flushed to kernel-space.
*
*   @par Errors:
*
*   Function returns #EAaFileRet_Error in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*     - Some implementations may choose to update the whole buffer to the final
*       location any time flushing is initiated.
*
*   @par Example:
*
*   @code
*
*    extern char buf[];
*    TAaFile *stream;
*
*    if ((stream = AaFileOpen("testfile.txt", "w")) == GLO_NULL) {
*        // Something's wrong.
*        ...
*    }
*    if (AaFileWrite(buf, 1, MY_BUFSIZE, stream) != MY_BUFSIZE) {
*        // Something's wrong.
*        ...
*    }
*    if (AaFileFlush(stream) != EAaFileRet_Ok) {
*        // Something's definitely wrong.
*        ...
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
EAaFileRet AaFileFlush(TAaFile *stream);

/**
*******************************************************************************
*
*   @brief    AaFileSync() performs flush and sync on the stream.
*
*   @param[in]   stream  Pointer to the stream object.
*
*   @return     #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise
*
*   @par Description:
*
*   If the stream is unbuffered, this function does nothing.
*   As a buffered stream is flushed, a part of the buffer, including any new
*   data written to the stream by the user, shall be updated to the final
*   location. Internally, flushing of user-space buffers to kernel-space is
*   performed, followed by flush of kernel-space buffers to destination.
*
*   @par Errors:
*
*   Function returns #EAaFileRet_Error in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*     - Some implementations may choose to update the whole buffer to the final
*       location any time flushing is initiated.
*
*   @par Example:
*
*   @code
*
*    extern char buf[];
*    TAaFile *stream;
*
*    if ((stream = AaFileOpen("testfile.txt", "w")) == GLO_NULL) {
*        // Something's wrong.
*        ...
*    }
*    if (AaFileWrite(buf, 1, MY_BUFSIZE, stream) != MY_BUFSIZE) {
*        // Something's wrong.
*        ...
*    }
*    if (AaFileSync(stream) != EAaFileRet_Ok) {
*        // Something's definitely wrong.
*        ...
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
EAaFileRet AaFileSync(TAaFile *stream);

/**
*******************************************************************************
*
*   @brief    AaFileRename renames an existing file
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
*   @note
*   Using AaFileRename for moving files between different volumes is never allowed; the
*   function will return an error if volume of source and destination path is different
*   If you try to move files within the same volume, but between different directories,
*   then it depends on the filesystem underneath if this is allowed or not.
*   (E.g. on ExtFM renaming only works within the the same directory. This is therefore
*   the case for OSE5.3 and OSE4.6.1, but also for LINUX on FSM-r2, when ExtFM is addressed.)
*
*
*   @par Return value
*
*   Upon successful completion AaFileRename shall return #EAaFileRet_Ok.
*   Otherwise, an error dependent value shall be returned.
*
*   @par Errors:
*
*   - #EAaFileRet_ENOENT:            \p oldPath or \p newPath is \c GLO_NULL or empty, or contains invalid AaFile volume.
*   - #EAaFileRet_NONPORTABLEFILE:   \p oldPath or \p newPath do not conform to AaFile path notation.
*   - #EAaFileRet_EACCES:            A component of either path prefix denies search
*                                    permission; or one of the directories containing \p oldPath or
*                                    \p newPath denies write permissions; or, write permission is
*                                    required and is denied for a directory pointed to by the
*                                    \p oldPath or \p newPath arguments.
*   - #EAaFileRet_EBUSY:             The directory named by \p oldPath or \p newPath is currently in use by
*                                    the system or another process, and the implementation
*                                    considers this an error.
*   - #EAaFileRet_EINVAL:            The \p newPath directory pathname contains a path prefix that
*                                    names the \p oldPath directory.
*   - #EAaFileRet_EIO:               A physical I/O error has occurred.
*   - #EAaFileRet_EISDIR:            The \p newPath argument points to a directory and the \p oldPath
*                                    argument points to a file that is not a directory.
*   - #EAaFileRet_ELOOP:             A loop exists in symbolic links encountered during
*                                    resolution of the path argument.
*   - #EAaFileRet_EMLINK:            The file named by \p oldPath is a directory, and the link count
*                                    of the parent directory of \p newPath would exceed {LINK_MAX}.
*   - #EAaFileRet_ENAMETOOLONG:      The length of the \p oldPath or \p newPath argument exceeds {PATH_MAX}
*                                    or a pathname component is longer than {NAME_MAX}.
*   - #EAaFileRet_ENOENT:            The link named by \p oldPath or \p newPath does not name an existing file,
*                                    or either \p oldPath or \p newPath mount points are invalid.
*   - #EAaFileRet_ENOSPC:            The directory that would contain \p newPath cannot be extended.
*   - #EAaFileRet_ENOTDIR:           A component of either path prefix is not a directory; or
*                                    the \p oldPath argument names a directory and \p newPath argument
*                                    names a non-directory file.
*   - #EAaFileRet_EXDEV:             The links named by \p newPath and \p oldPath are on different file
*                                    systems and the implementation does not support links
*                                    between file systems.
*   - #EAaFileRet_ENOMEM:            Internal failure due to lack of memory.
*   - #EAaFileRet_Error:             For all other errors.
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
*    if ((retval = AaFileRename( oldPath, newPath) != EAaFileRet_Ok) {
*        switch (retval) {
*        case EAaFileRet_ENOENT : printf("file does not exist"); break;
*        case EAaFileRet_EACCES : printf("file is not accessible"); break;
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
EAaFileRet AaFileRename(const char *oldPath, const char *newPath);

/**
******************************************************************************
*   AaFileGetAbsPath() converts a path given in AaFile Path notation to the OS
*   specific path notation.
*
*   @param[in]  path AaFile path
*
*   @return     Absolute path in related stdio filesystem if volume is mounted correctly,
*               \c GLO_NULL otherwise.
*
*   @note
*   Returned pointer to string buffer, containing the absolute path, was newly
*   allocated by the function. Ownership of returned pointer is passed to the user!
*   Therefore the RETURNED POINTER HAS TO BE FREED BY THE USER with AaMemUnRef().
*
*   @par Description
*
*   Get the absolute file path of local filesystem for given AaFile path.
*   (An AaFile path starts either with a valid volume - like /ram, /rom,
*   /safe etc. - or is relative and therefore related to the default volume.)
*   If given path doesn't contain a volume it is related the default volume.
*   If the volume is related to a stdio filesystem it is resolved to its
*   mountpoint in the system. In other words: given AaFile path is expanded.
*
*   @note
*   No checks (length, portable characters etc.) are done on the file name
*
*   @par Example:
*
*   @code
*
*     char* myPath;
*     char* absPath;
*     char stat st;
*
*     myPath = "/rom/swconfig.txt";
*
*     if ( GLO_NULL == (absPath = AaFileGetAbsPath(myPath)) ) {
*         // ERROR
*     }
*
*     // NOTE: DON'T FORGET TO FREE POINTER AGAIN!
*
*     if ( 0 > lstat(absPath, &st) ) {
*         // ERROR
*     }
*
*     if ( S_ISLNK(st.st_mode) ) {
*         // => it is a symbolic link
*     }
*
*     AaMemUnRef((const void*)&absPath); // POINTER HAS TO BE FREED!
*
*   @endcode
*
******************************************************************************/
char* AaFileGetAbsPath(const char* path);

/** @} */

/**
 * @name AaFile additional operations
 * @brief Functions that are available in most environments.
 *        See [CCSAPI_VARIABILITY] for more details.
 */

/** @{ */

/**
*******************************************************************************
*
*   @brief    AaFileGetSize returns the size of the file associated with the stream
*
*   @param[in]   stream  Pointer to the stream object.
*
*   @return     Size of the file in bytes. On error return -1.
*
*   @par Description:
*
*   Get size of the file associated with the stream. Value of the file position
*   indicator will remain the same.
*
*   @note For files on the secure storage this function will return the size of the encrypted file,
*         which is not the size of resulting plaintext, gained with function AaFileRead.
*         The size of a ciphertext file always is bigger than its decrypted plaintext. By this an
*         allocation of a maximal user buffer is possible, but the user has to take care of actually
*         read data amount.
*
*   @par Errors:
*
*   Function returns -1 in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*   None.
*
*   @par Example:
*
*   @code
*
*    TAaFile *stream;
*    long fileSize;
*
*    if ((stream = AaFileOpen("testfile.txt", "r")) == GLO_NULL) {
*        // Error. Maybe file not found?
*        ...
*    }
*    if ((fileSize = AaFileGetSize(stream)) < 0) {
*        // Error. Should not happen.
*        ...
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
long AaFileGetSize(TAaFile *stream);

/**
*******************************************************************************
*
*   @brief    AaFileGetSizeOf returns the size of the file with given path.
*
*   @param[in]  path file path
*
*   @return     Size of the file in bytes. On error return -1.
*
*   @par Description:
*
*   Get size of the file with given path.
*
*   @par Errors:
*
*   Function returns -1 in case of error and prints error message in logs.
*
*   @par Restrictions:
*
*   None.
*
*   @par Example:
*
*   @code
*
*    long fileSize;
*
*    if ( 0 > (fileSize = AaFileGetSizeOf("testfile.txt")) ) {
*        // Error. Should not happen.
*        ...
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
long AaFileGetSizeOf(const char* path);

/**
******************************************************************************
*   AaFileCopy() copies a file from source to destination path.
*
*   @param[in] srcPath AaFile source path of file
*   @param[in] destPath AaFile destination path of file
*
*   @return     #EAaFileRet_Ok on success, specific error value otherwise
*
*   @par Errors:
*
*   - #EAaFileRet_ENOENT:            \p srcPath or \p destPath is \c GLO_NULL or empty, or contains invalid AaFile volume.
*   - #EAaFileRet_NONPORTABLEFILE:   \p srcPath or \p destPath do not conform to AaFile path notation.
*   - #EAaFileRet_Error:             For all other errors.
*
*   @par Example:
*
*   @code
*
*    if ( EAaFileRet_Ok != AaFileCopy("/ram/fileA.txt", "/ram/fileB.txt") ) {
*        // error handling
*        ...
*    }
*
*   @endcode
******************************************************************************/
EAaFileRet AaFileCopy(const char* srcPath, const char* destPath);

/**
******************************************************************************
*   AaFileCreateDir() creates a directory with given path.
*
*   @param[in] path directory path (AaFile Path Notation)
*
*   @return     #EAaFileRet_Ok on success, specific error value otherwise
*
*   @par Errors:
*
*   - #EAaFileRet_ENOENT:            \p path is \c GLO_NULL or empty, or contains invalid AaFile volume.
*   - #EAaFileRet_NONPORTABLEFILE:   \p path do not conform to AaFile path notation.
*   - #EAaFileRet_ENOMEM:            Failed to allocate memory for internal buffer.
*   - #EAaFileRet_EEXIST:            Directory already exists.
*   - #EAaFileRet_Error:             For all other errors.
*
*   @note
*   If a directory with the same name exists already, #EAaFileRet_EEXIST is returned,
*   but if a file with the same name exists before then #EAaFileRet_Error is
*   returned.
*
*   @par Example:
*
*   @code
*
*     if ( EAaFileRet_Ok != AaFileCreateDir("/ram/dirB") ) {
*          // error handling
*          ...
*     }
*
*   @endcode
******************************************************************************/
EAaFileRet AaFileCreateDir(const char* path);

/**
******************************************************************************
*   AaFileCopyDir() copies a directory (with contents being portable).
*
*   @param[in] srcPath  source directory path (AaFile Path Notation)
*   @param[in] destPath destination directory path (AaFile Path Notation)
*
*   @return     #EAaFileRet_Ok on success, specific error value otherwise
*
*   @par Errors:
*
*   - #EAaFileRet_ENOENT:            \p srcPath or \p destPath is \c GLO_NULL or empty, or contains invalid AaFile volume.
*   - #EAaFileRet_NONPORTABLEFILE:   \p srcPath or \p destPath do not conform to AaFile path notation.
*   - #EAaFileRet_Error:             For all other errors.
*
*   @par Description:
*
*   Copying is done recursively and all copied items in the destination directory are portable.
*   (If the source directory contains non-portable items, e.g. with file names not complying
*   to AaFile Path Notation or symbolic links, which were created or placed there
*   without AaFile means, then these items are ignored; for those items INF prints will be
*   logged.)
*
*   @note
*    - the destination directory will be a recursive copy of the source directory.
*    - symbolic links are ignored on LINUX. (If a symbolic link is contained in the source
*      directory, it will not be copied to the destination directory.)
*    - items with non-portable paths (not comform to AaFile Path Notation) are ignored.
*      (They won't be copied to the destination directory.)
*
*   @see AaFileCopyDirExt()
*
*   @par Example:
*
*   @code
*
*    if ( EAaFileRet_Ok != AaFileCopyDir("/ram/dirA", "/ram/dirB") ) {
*        // error handling
*        ...
*    }
*
* @endcode
******************************************************************************/
EAaFileRet AaFileCopyDir(const char* srcPath, const char* destPath);

/**
*********************************************************************************
*   AaFileListDir() lists volume or directory contents being portable.
*
*   @param[out] dirArray  pointer to resulting directory array of node pointers
*   @param[out] nfilesp   number of nodes in resulting array of node pointers
*   @param[in]  path      volume or directory path (AaFile Path Notation)
*   @param[in]  recursive specifies whether recursive listing is performed
*
*   @return     #EAaFileRet_Ok on success, specific error value otherwise
*
*   @par Description:
*
*   All listed paths, which are contained in resulting directory array, are portable.
*   (If volume or directory contains non-portable items, e.g. file names not complying
*   to AaFile Path Notation or symbolic links, which were created or placed there
*   without AaFile means, then these items are ignored.)
*   By this the function is AaFile consistent: all resulting paths can be reused in further
*   operations with AaFile functions.
*
*   @par Errors:
*
*   - #EAaFileRet_ENOENT:            \p path is \c GLO_NULL or empty, or contains invalid AaFile volume.
*   - #EAaFileRet_NONPORTABLEFILE:   \p path do not conform to AaFile path notation.
*   - #EAaFileRet_EINVAL:            Parameter \p dirArray or \p nfilesp is \c GLO_NULL
*   - #EAaFileRet_Error:             For all other errors.
*
*   @note
*    - resulting directory array has to be freed again, but ownership is passed to the user.
*      For freeing AaFileFreeListDirArray() should be used.
*    - symbolic links are ignored on LINUX. (If a symbolic link is contained, it will have no
*      entry in resulting directory array.)
*    - items with non-portable paths (not conform to AaFile Path Notation) are ignored. (They
*      will have no entry in resulting directory array.)
*
*   @see AaFileFreeListDirArray()
*   @see AaFileListDirExt()
*
*   @par Example:
*
*   @code
*
*    SAaFileDnode** darray;
*    SAaFileDnode*  dp;
*    u32            n, i;
*    EAaFileRet     rc;
*
*    if ( EAaFileRet_Ok == AaFileListDir(&darray, &n, "/ram", GLO_FALSE) ) {
*        for (i = 0; i < n; i++) {
*            dp = darray[i];
*            printf(dp->filename);
*        }
*    }
*
*    :
*
*    AaFileFreeListDirArray(&darray, n);
*
*   @endcode
******************************************************************************/
EAaFileRet AaFileListDir(SAaFileDnode*** dirArray, u32* nfilesp, const char* path, TBoolean recursive);

/**
******************************************************************************
*   AaFileFreeListDirArray() frees memory of listing results
*
*   @param[in,out] dirArray   pointer to array of node pointers (will be set to
*                             \c GLO_NULL after freeing.)
*   @param[in]     nfiles     number of nodes in array of node pointers
*
*   @par Errors:
*
*   Function prints error message in logs in case of error.
*
*   @par Description
*
*   Listing results are produced through functions AaFileListDir() or
*   AaFileListDirExt(), which pass ownership of the results to their callers.
*   Given reference pointer to the array is set to \c GLO_NULL after freeing the
*   memory.
*
*   @note
*   If reference pointer already is \c GLO_NULL, nothing happens.
*
*   @see AaFileListDir()
*   @see AaFileListDirExt()
******************************************************************************/
void AaFileFreeListDirArray(SAaFileDnode*** dirArray, u32 nfiles);

/**
******************************************************************************
*   AaFileRemoveDir() deletes a directory (and its contents).
*
*   @param[in] path directory path (AaFile Path Notation)
*
*   @return     #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise
*
*   @par Errors:
*
*   Function returns #EAaFileRet_Error in case of error and prints error message in logs.
*
*   @par Description:
*
*   Removal will be done in any case and it affects also non-portable items.
*   (If the directory contains non-portable items, e.g. with file names not complying
*   to AaFile Path Notations or symbolic links, which were created or placed there
*   without AaFile means, then these items are removed as well.)
*   If \p path is a symbolic link to a directory, then the symbolic link is removed,
*   but the target directory is left intact.
*
*   @par Example:
*
*   @code
*
*     if ( EAaFileRet_Ok != AaFileRemoveDir("/ram/dirB") ) {
*         // error handling
*         ...
*     }
*
*   @endcode
******************************************************************************/
EAaFileRet AaFileRemoveDir(const char* path);

/**
******************************************************************************
*   AaFileDirExists() checks if a directory exists
*
*   @param[in] path directory path (AaFile Path notation)
*
*   @return     \c GLO_TRUE if directory exists, \c GLO_FALSE in case it is missing or errors
*               where encountered during execution.
*
*   @par Errors:
*
*   Function returns \c GLO_FALSE in case of error and prints error message in logs.
*
*   @par Example:
*
*   @code
*
*     if ( GLO_TRUE == AaFileDirExists("/ram/dirX") ) {
*         // directory exists
*         if ( EAaFileRet_Ok != AaFileRemoveDir("/ram/dirX") ) {
*           // error handling
*           ...
*         }
*     }
*
*   @endcode
******************************************************************************/
TBoolean AaFileDirExists(const char* path);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _COMMON_IF_AAFILE_H_ */
