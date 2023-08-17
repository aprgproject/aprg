/** @file
*   @brief AaFile MCU function prototypes.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2017, 2019 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AAFILE_H_
#define _MCU_IF_AAFILE_H_

#include <CcsCommon.h>
#include <../../COMMON/ServiceInterface/IfAaFile.h>
#include <../../SHARED/MCU_RT/ServiceInterface/IfAaFile.h>
#include <../../MCU/Definitions/IfAaFile_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup    dgAaFile
 */

/** @{ */

/**
*********************************************************************************
*   AaFileListDirToFile() lists volume or directory content.
*
*   @param[in] path      volume or directory path (AaFile Path Notation) which contents is listed.
*   @param[in] fileName  file (AaFile Path Notation) to write the path content.
*   @param[in] mode      pattern for file opening mode.
*   @param[in] format    format of written content to the file.
*   @param[in] recursive \c GLO_TRUE lists content recursively.
*
*   @return    #EAaFileRet_Ok on success, #EAaFileRet_Error otherwise.
*
*   @par Errors:
*
*   Function returns #EAaFileRet_Error in case of error and prints error message in logs.
*
*   @par Description
*
*   The function lists the volume or directory content to the file according to the given
*   format (#EAaFileListDirFormat_Long or #EAaFileListDirFormat_Short).
*   Format #EAaFileListDirFormat_Long writes the contents in the following format:
*     - The file's type and file mode bits.
*     - The number of hard links to the file.
*     - The user who owns the file.
*     - The file's group.
*     - The file's size in bytes.
*     - The date the file was last modified.
*     - The file's name.
*
*     Example: drwxr-xr-x   12 root     root          4984 Sep 19 09:41 fs3
*
*     Format #EAaFileListDirFormat_Short writes just the file names to the output file.
*     Example: FileDirectory.xml
*
*   @note
*
*   @par Example:
*
*   @code
*
*    EAaFileRet rc = EAaFileRet_Ok;
*    rc = AaFileListDirToFile("/ram", "ramContent.txt", "w", EAaFileListDirFormat_Short, GLO_FALSE );
*    if ( EAaFileRet_Ok != rc )
*    {
*        AAFILE_PRINT( AAFILE_PRINT_ERROR, "%s() failed, rc = %d", __FUNCTION__, rc);
*    }
*
*   @endcode
******************************************************************************/
EAaFileRet AaFileListDirToFile(const char* path, const char* fileName, const char* mode, EAaFileListDirFormat format, TBoolean recursive);

/**
******************************************************************************
*
*   @brief    Check if given path is a mount point
*
*   @param[in]  path         Pointer to a string that contains path to be checked
*
*   @return     #EAaFileFsMounted when path is a mount point otherwise refer to error description
*
*   @par Description:
*   Function checks if given path is a mount point.
*   Specified item path must be given in AaFile notation.
*
*
*   @par Errors:
*     - #EAaFileFsInvalidPath              Given path is invalid.
*     - #EAaFileFsNotMounted               Given path isn't a mount point
*
*   @par Restrictions:
*       - Length of item path cannot exceed #AAFILE_FILENAME_MAX
*
*   @par Example:
*
*   @code
*
*       const char* path = "/ram/";
*
*       if ( EAaFileFsMounted != (rc = AaFileIsFsMounted( path )) ) {
*
*           // handle error
*           ...
*       }
*
*   @endcode
*
*   @par Usage:
*
*   None
*
*   @par Rationale:
*
*   LBT3424
*
*   @par Future directions:
*
*   None
*
******************************************************************************/
EAaFileFsMountStatus AaFileIsFsMounted( const char* path );

/**
******************************************************************************
*
* @brief Copy a file. Preserve owner and group owner information.
*
* @param[in] srcPath    AaFile path of source file
* @param[in] destPath   AaFile path of destination file
*
* @returns #EAaFileRet_Ok on successful copy operation, appropriate error otherwise.
*
* @par Description:
* This function copies a source file to specified destination file. While copying it aligns
* the access modes, the owner and group owner information of the destination file with the
* source file.
*
* @par Errors:
*  - #EAaFileRet_ENOENT:            \p srcPath or \p destPath is \c GLO_NULL or empty, or contains invalid AaFile volume.
*  - #EAaFileRet_NONPORTABLEFILE:   \p srcPath or \p destPath do not conform to AaFile path notation.
*  - #EAaFileRet_OWNERNOTPRESERVED: Failed to align ownership between destination and source.
*  - #EAaFileRet_Error:             For all other errors.
*
* @par Restrictions:
* The caller must have appropriate access rights to correctly preserve ownership information.
* If this is not the case file will be copied, but ownership information will be inherited from the
* user ID and group ID of the caller. #EAaFileRet_OWNERNOTPRESERVED will be returned in that case.
*
* @par Example:
* @code
* EAaFileRet rc = AaFileCopyPreserve("/ram/sourceFile.txt", "/ram/destinationFile.txt");
*
*  if( EAaFileRet_Ok != rc ) {
*     if( EAaFileRet_OWNERNOTPRESERVED == rc ) {
*         // handle ownership information not being preserved
*         ...
*     }
*     // handle remaining errors
*     ...
* }
* @endcode
*
* @par Rationale:
* PS-0060
*
* @see AaFileCopy()
* @see AaFileCopyDirPreserve()
*
******************************************************************************/
EAaFileRet AaFileCopyPreserve( const char* srcPath, const char* destPath );

/**
******************************************************************************
*
* @brief Recursively copy a directory. Preserve owner and group owner information
* of directory and all of its contents.
*
* @param[in] srcPath        AaFile path of source directory
* @param[in] destPath       AaFile path of destination directory
* @param[in] copyAllItems   Flag to toggle copying of non-portable items.
*
* @returns #EAaFileRet_Ok on successful copy operation, appropriate error otherwise.
*
* @par Description:
* This function recursively copies source directory to specified destination. While copying it
* aligns the access modes, the owner and group owner information of all items between source and destination.
* @par
* The argument \p copyAllItems selects the behavior when \p srcPath contains symbolic links or items with
* names which are non-portable in context of AaFile path notation. If set to \c GLO_FALSE, these non-portable
* items will not be copied, and #EAaFileRet_NONPORTABLEFILE will be returned (but portable items will be
* copied correctly). If \p copyAllItems is set to \c GLO_TRUE all items will be copied regardless of being
* portable or not.
*
* @par Errors:
*  - #EAaFileRet_ENOENT:            \p srcPath or \p destPath is \c GLO_NULL or empty, or contains invalid AaFile volume.
*  - #EAaFileRet_NONPORTABLEFILE:   \p srcPath or \p destPath do not conform to AaFile path notation, or \p srcPath
*                                   contains items with non-portable names in context of AaFile path notation when
*                                   \p copyAllItems is set to \c GLO_FALSE.
*  - #EAaFileRet_OWNERNOTPRESERVED: Failed to align ownership between destination and source.
*  - #EAaFileRet_Error:             For all other errors (contents of \p destPath are undefined).
*
* @par Restrictions:
* The caller must have appropriate access rights to correctly preserve ownership information.
* If this is not the case directory will be copied, but ownership information will be inherited from
* the user ID and group ID of the caller. #EAaFileRet_OWNERNOTPRESERVED will be returned in that case.
*
* @par Example:
* @code
* EAaFileRet rc = AaFileCopyDirPreserve("/ram/sourceDir/", "/ram/destinationDir/", GLO_TRUE);
*  if( EAaFileRet_Ok != rc ) {
*     if( EAaFileRet_OWNERNOTPRESERVED == rc ) {
*         // handle ownership information not being preserved
*         ...
*     }
*     // handle remaining errors
*     ...
* }
* @endcode
*
* @par Rationale:
* PS-0060
*
* @see AaFileCopyDir()
* @see AaFileCopyDirExt()
* @see AaFileCopyPreserve()
*
******************************************************************************/
EAaFileRet AaFileCopyDirPreserve( const char* srcPath, const char* destPath, TBoolean copyAllItems );

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IF_AAFILE_H_ */
