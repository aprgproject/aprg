/** @file
*   @brief AaFile MCU_RT function prototypes.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2015 Nokia Solutions and Networks. All rights reserved.$
*   $Copyright: 2019 Nokia. All rights reserved.$
*/
#ifndef _MCU_RT_IF_AAFILE_H_
#define _MCU_RT_IF_AAFILE_H_

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/*------------------- PUBLIC INTERFACES (MCU API) ---------------------------*/

/**
 * @defgroup dgAaFileApiMcu AaFile MCU API
 * @ingroup  dgAaFile
 */

/** @{ */

/**
*******************************************************************************
*
*   @brief    AaFileFlushAll() flushes all open write streams.
*
*   @return     #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise
*
*   @par Description:
*
*   All open and buffered write streams are flushed.
*   This function only is a wrapper for fflush(NULL), that cannot be reflected
*   by AaFileFlush().
*
*   @par Errors:
*
*   Function only fails (ERR level type log is generated) if implicitly called
*   fflush(NULL) fails. Read in fflush() descripton of your platform
*   (OSE or LINUX), if and when this happens.
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
*    extern char buf1[];
*    extern char buf2[];
*    TAaFile *stream1;
*    TAaFile *stream2;
*
*    if ( GLO_NULL == (stream1 = AaFileOpen("testfile1.txt", "w")) ) {
*        // Something's wrong.
*        ...
*    }
*    if ( MY_BUFSIZE1 != AaFileWrite(buf1, 1, MY_BUFSIZE, stream1) ) {
*        // Something's wrong.
*        ...
*    }
*    if ( GLO_NULL == (stream2 = AaFileOpen("testfile2.txt", "w")) ) {
*        // Something's wrong.
*        ...
*    }
*    if ( MY_BUFSIZE2 != AaFileWrite(buf2, 1, MY_BUFSIZE, stream2) ) {
*        // Something's wrong.
*        ...
*    }
*
*    if ( EAaFileRet_Ok != AaFileFlushAll() ) {
*        // Something's definitely wrong.
*        ...
*    }
*
*    // both write streams (stream1 and stream2) have been flushed to the related files
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
EAaFileRet AaFileFlushAll(void);

/**
*******************************************************************************
*   AaFileCreateSymbLink() creates a symbolic link to a target with given
*   link name.
*
*   @param[in] targetPath target path (AaFile Path Notation)
*   @param[in] linkPath   link path (AaFile Path Notation)
*
*   @return    #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise
*
*   @par Errors:
*
*   Function returns #EAaFileRet_Error in case of error and prints error message in logs.
*
*   @note
*       - Target and link path have to be given in AaFile Path Notation. (The
*         function verifies plausibility of both paths.)
*       - It is allowed to create a broken link. (Existence of the target is
*         not checked.)
*
*   @par Example:
*
*   @code
*
*       char* lnkpath = "/ram/slnk";
*       char* targetpath = "/rom/swconfig.txt";
*
*       if ( EAaFileRet_Ok != AaFileCreateSymbLink(targetpath, lnkpath) ) {
*           // error handling
*           ...
*       }
*
*   @endcode
******************************************************************************/
EAaFileRet AaFileCreateSymbLink(const char* targetPath, const char* linkPath);

/**
*******************************************************************************
*   AaFileCreateSymbLinkAbsPath() creates a symbolic link to a target with given
*   link name.
*
*   @param[in] targetPath target path (LINUX path)
*   @param[in] linkPath   link path (AaFile Path Notation)
*
*   @return    #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise
*
*   @par Errors:
*
*   Function returns #EAaFileRet_Error in case of error and prints error message in logs.
*
*   @note
*       - Only the link path is given in AaFile Path Notation.
*       - The target path is a LINUX path. By this it can point in principle
*         outside the valid volume space of AaFile.
*       - It is allowed to create a broken link. (Existence of the target is
*         not checked.)
*
*   @par Example:
*
*   @code
*
*       char* lnkpath = "/ram/slnk";
*       char* targetpath = "/etc/sysconfig";
*
*       if ( EAaFileRet_Ok != AaFileCreateSymbLinkAbsPath(targetpath, lnkpath) ) {
*           // error handling
*           ...
*       }
*
*   @endcode
******************************************************************************/
EAaFileRet AaFileCreateSymbLinkAbsPath(const char* targetPath, const char* linkPath);

/**
*******************************************************************************
*   AaFileIsSymbLink() checks if an item is a symbolic link.
*
*   @param[in] linkPath AaFile path for item to be checked
*
*   @return
*      - \c GLO_TRUE if item with given path is a symbolic link
*      - \c GLO_FALSE if item with given path is not existing or no symbolic link
*
*   @par Errors:
*
*   Function returns \c GLO_FALSE in case of error and prints error message in logs.
*
*   @par Example:
*
*   @code
*
*       char* lnkpath = "/ram/slnk";
*
*       if ( GLO_TRUE == AaFileIsSymbLink(lnkpath) ) {
*           // this is a symbolic link
*           AaFileRemove(lnkpath);
*       }
*
*   @endcode
******************************************************************************/
TBoolean AaFileIsSymbLink(const char* linkPath);

/**
******************************************************************************
*   AaFileGetAbsTargetPath() retrieves the LINUX target path from a symbolic link.
*
*   @param[in]  linkPath         path of symbolic link (AaFile Path notation)
*   @param[out] targetPathBuf[]  reference buffer for target path (LINUX path)
*   @param[in]  targetPathBufLen size of reference buffer
*
*   @return    #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise
*
*   @par Errors:
*
*   Function returns #EAaFileRet_Error in case of error and prints error message in logs.
*
*   @note
*     - Only the link path is given in AaFile Path Notation
*     - The retrieved target path is a LINUX path. (In any case it cannot be
*       reused in regular AaFile interfaces, which required AaFile Path Notation.
*       Further the target path might point outside the valid volume space of AaFile.)
*
*   @par Example:
*
*   @code
*
*     #define TARGET_PATH_BUF_SIZE 256
*     char tpbuf[TARGET_PATH_BUF_SIZE];
*
*     if ( EAaFileRet_Ok == AaFileGetAbsTargetPath("/ram/slnk", tpbuf, TARGET_PATH_BUF_SIZE) ) {
*         // do something with retrieved path
*         if ( 0 == strncmp(tpbuf, "/etc/sysconfig", TARGET_PATH_BUF_SIZE) ) {
*             ...
*         }
*     }
*
*   @endcode
******************************************************************************/
EAaFileRet AaFileGetAbsTargetPath(const char* linkPath, char targetPathBuf[], u32 targetPathBufLen);

/**
*********************************************************************************
*   AaFileListDirExt() lists volume or directory contents. (Extended behavior)
*
*   @param[out] dirArray  pointer to resulting directory array of node pointers
*   @param[out] nfilesp   number of nodes in resulting array of node pointers
*   @param[in]  path      volume or directory path (AaFile Path Notation)
*   @param[in]  recursive specifies whether listing is recursive or not
*
*   @return     #EAaFileRet_Ok on success, specific error value otherwise
*
*   @par Errors:
*
*   - #EAaFileRet_ENOENT:            \p path is \c GLO_NULL or empty, or contains invalid AaFile volume.
*   - #EAaFileRet_NONPORTABLEFILE:   \p path do not conform to AaFile path notation.
*   - #EAaFileRet_EINVAL:            Parameter \p dirArray or \p nfilesp is \c GLO_NULL
*   - #EAaFileRet_Error:             For all other errors.
*
*   @par Description
*
*   Extended behavior means: symbolic links or non-portable file names are not ignored and might
*   occur in resulting directory array.
*   The function is not AaFile consistent and resulting paths might not be allowed for
*   further operations with AaFile functions.
*
*   @note
*    - resulting directory array has to be freed again, but ownership is passed to the user.
*      For freeing AaFileFreeListDirArray() should be used.
*    - symbolic link items are listed
*    - non-portable item names are listed
*
*   @see AaFileFreeListDirArray()
*   @see AaFileListDir()
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
*    if ( EAaFileRet_Ok == AaFileListDirExt(&darray, &n, "/ram", GLO_FALSE) ) {
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
EAaFileRet AaFileListDirExt(SAaFileDnode*** dirArray, u32* nfilesp, const char* path, TBoolean recursive);

/**
******************************************************************************
*   AaFileCopyDirExt() copies a directory. (Extended behavior)
*
*   @param[in] srcPath  path of source directory (AaFile Path Notation)
*   @param[in] destPath path of destination directory (AaFile Path Notation)
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
*   Copying is done recursively.
*   Extended behavior means: symbolic links or non-portable file names are not ignored and
*   copied to the destination directory as well.
*
*   @see AaFileCopyDir()
*
*   @par Example:
*
*   @code
*
*    if ( EAaFileRet_Ok != AaFileCopyDirExt("/ram/dirA", "/ram/dirB") ) {
*        // error handling
*        ...
*    }
*
*   @endcode
******************************************************************************/
EAaFileRet AaFileCopyDirExt(const char* srcPath, const char* destPath);

/**
*******************************************************************************
*
*   @brief    AaFileSyncAll() flushes and syncs all open write streams and data.
*
*   @return     #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise
*
*   @par Description:
*
*   All open and buffered write streams are flush-ed then sync-ed.
*   This function only is a wrapper over subsequent calls to fflush() and sync().
*
*   @par Errors:
*
*   Function only fails if fflush(NULL) fails. sync() does not return an error
*   code.
*   Read in fflush() descripton of your platform (LINUX), if and when this
*   happens.
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
*    extern char buf1[];
*    extern char buf2[];
*    TAaFile *stream1;
*    TAaFile *stream2;
*
*    if ( GLO_NULL == (stream1 = AaFileOpen("testfile1.txt", "w")) ) {
*        // Something's wrong.
*        ...
*    }
*    if ( MY_BUFSIZE1 != AaFileWrite(buf1, 1, MY_BUFSIZE, stream1) ) {
*        // Something's wrong.
*        ...
*    }
*    if ( GLO_NULL == (stream2 = AaFileOpen("testfile2.txt", "w")) ) {
*        // Something's wrong.
*        ...
*    }
*    if ( MY_BUFSIZE2 != AaFileWrite(buf2, 1, MY_BUFSIZE, stream2) ) {
*        // Something's wrong.
*        ...
*    }
*
*    if ( EAaFileRet_Ok != AaFileSyncAll() ) {
*        // Something's definitely wrong.
*        ...
*    }
*
*    // both write streams (stream1 and stream2) have been flushed to the
*    // related files
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
EAaFileRet AaFileSyncAll(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_RT_IF_AAFILE_H_ */
