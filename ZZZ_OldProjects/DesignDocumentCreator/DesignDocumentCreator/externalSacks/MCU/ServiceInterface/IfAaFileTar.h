/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/
#ifndef _MCU_IF_AAFILETAR_H_
#define _MCU_IF_AAFILETAR_H_

#include "CcsCommon.h"

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../MCU/Definitions/IfAaFile_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------- PUBLIC INTERFACES (MCU API) --------------------------*/



/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup    dgAaFile
 */

/** @{ */

/**
*******************************************************************************
*
*   @brief AaFileTarItemArray() creates a tar archive from several items given
*                               in an array with item pathes (an item either
*                               can be a file or a directory)
*
*   @param[in]  archivePath       archive path
*   @param[in]  itemPathArray     array with pathes of items to be added to archive
*   @param[in]  itemPathArraySize size of array with item pathes
*   @param[in]  relativeDirPath   path to which the item pathes in the archive
*                                 will be stored relative to. If set to GLO_NULL
*                                 then the item pathes will be set relative to
*                                 root directory.
*
*   @return #EAaFileRet_Ok in case of success, otherwise #EAaFileRet_Error.
*
*   @par Description:
*
*   The function corresponds to command:
*   @code
*          tar -cf -C <reldir> <archive> <item1> <item2> ...
*   @endcode
*
*   The tar archive always will be newly created. (If archive exists already it
*   will be overwritten without warning.)
*
*   When no relative directory path is given (relativeDirPath set to GLO_NULL),
*   then the item pathes in the archive will be stored relatively to root directory
*   (this means that leading '/' from absolute Linux path of item will be removed).
*
*   When a relative directory path is set to a valid path, then the item pathes
*   in the archive are stored relatively to this directory when possible. More
*   detailed we have following behavior if relativeDirPath is set:
*      - if given relative path is an initial part of the item path, then item
*        path relative to given path is stored in the tar archive
*      - if given relative path is not an initial part of the item path, then
*        the item path will be stored relative to the root directory (this means
*        that leading '/' from absolut Linux path of item will be removed).
*
*   If an item path in the item array is related to a file, then simply the file is
*   added to the archive.
*
*   If an item path in the item array is related to a directory, then directory with
*   its complete recursive content (all contained directories and files) is added.
*
*   For the detailed behavior of the function see also examples below.
*
*   @note
*   All pathes in the interface (archive path, pathes of items in array and relative
*   path) have to be conform to AaFile path notation.
*   Internally a path is resolved into its real Linux path and finally the tar
*   archive will contain the resolved Linux pathes (at least if path storage relative
*   to root directory was chosen for archiving by setting relativeDirPath to GLO_NULL).
*
*   @par Errors:
*
*   Additionally to returned error codes, the function raises exeptions analogous to
*   AaFileOpen() - since it is internally reused or similarly implemented.
*
*   @par Restrictions:
*      - Length of the archive, item and relative directory pathes cannot exceed
*        #AAFILE_FILENAME_MAX
*      - The pathes only are allowed to have portable characters, as defined in the
*        AaFile API specification.
*
*   @par Example:
*
*   @code
*
*    // Precondition:
*    //   1) AaFile volume /logs/ corresponds to Linux path /var/log
*    //   2) AaFile volume /ram/ corresponds to Linux path /tmp
*    //   3) Linux directory structure of volume /logs/ is:
*    //           /var/log/tardir/
*    //           /var/log/tardir/subdir/
*    //           /var/log/tardir/subdir/file1.txt
*    //           /var/log/tardir/subdir/file2.txt
*    //   4) Linux directory structure in volume /ram/ is:
*    //           /tmp/file3.txt
*
*    char* baseDir = "/logs/tardir";
*    char* subDir = "/logs/tardir/subdir";
*    char* archName  = "/logs/tardir/myarch.tar";
*    char* filePathArray[3] = { "/logs/tardir/subdir/file1.txt", // file item
*                               "/logs/tardir/subdir/file2.txt", // file item
*                               "/ram/file3.txt" };              // file item
*    char* itemPathArray[2] = { "/logs/tardir/subdir",           // directory item
*                               "/ram/file3.txt" };              // file item
*
*    // *** Adding only files with pathes relative to archive base directory /logs/tardir ***
*
*    if ( EAaFileRet_Ok != AaFileTarItemArray(archName, filePathArray, 3, baseDir) ) { handleError(); }
*
*    // if tar file content is now listed with command 'tar -tf myarch.tar' it would show:
*    //     subdir/file1.txt
*    //     subdir/file2.txt
*    //     tmp/file3.txt
*    //
*    // Note:
*    // Since /ram/file3.txt (or Linux path /tmp/file3.txt) is not relative to /logs/tardir it only
*    // can be added relative to root directory. (Such a mixture anyway is untypical, normally you
*    // would use items only relative to your base directory; this example only is for clarification.)
*
*    // *** Adding only files with pathes relative to directory /logs/tardir/subdir ***
*
*    if ( EAaFileRet_Ok != AaFileTarItemArray(archName, filePathArray, 3, subDir) ) { handleError(); }
*
*    // if tar file content is now listed with command 'tar -tf myarch.tar' it would show:
*    //     file1.txt
*    //     file2.txt
*    //     tmp/file3.txt
*    //
*    // Note:
*    // Same situation for /ram/file3.txt as before: it is not relative to /logs/tardir/subdir and
*    // therefore only can be added relative to root directory.
*
*    // *** Adding only files with pathes relative to root directory / ***
*
*    if ( EAaFileRet_Ok != AaFileTarItemArray(archName, filePathArray, 3, GLO_NULL) ) { handleError(); }
*
*    // if tar file content is now listed with command 'tar -tf myarch.tar' it would show:
*    //     var/log/tardir/subdir/file1.txt
*    //     var/log/tardir/subdir/file2.txt
*    //     tmp/file3.txt
*
*    // *** Adding a file and a directory with pathes relative to root directory / ***
*
*    if ( EAaFileRet_Ok != AaFileTarItemArray(archName, itemPathArray, 2, GLO_NULL) ) { handleError(); }
*
*    // if tar file content is now listed with command 'tar -tf myarch.tar' it would show:
*    //     var/log/tardir/subdir/
*    //     var/log/tardir/subdir/file1.txt
*    //     var/log/tardir/subdir/file2.txt
*    //     tmp/file3.txt
*    //
*    // Note:
*    // Now that directory /logs/tardir/subdir was in the item list, also the subdir path itself is
*    // contained.
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
EAaFileRet AaFileTarItemArray(char* archivePath,
                              char** itemPathArray,
                              u32 itemPathArraySize,
                              char* relativeDirPath);

/**
*******************************************************************************
*
*   @brief AaFileTarGzipItemArray() creates a gzip compressed tar archive from
*                                   several items given in an array with item
*                                   pathes (an item either can be a file or a
*                                   directory)
*
*   @param[in]  archivePath       archive path
*   @param[in]  itemPathArray     array with pathes of items to be added to archive
*   @param[in]  itemPathArraySize size of array with item pathes
*   @param[in]  relativeDirPath   path to which the item pathes in the archive
*                                 will be stored relative to. If set to GLO_NULL
*                                 then the item pathes will be set relative to
*                                 root directory.
*
*   @return #EAaFileRet_Ok in case of success, otherwise #EAaFileRet_Error.
*
*   @par Description:
*
*   The function corresponds to command:
*   @code
*          tar -czf -C <reldir> <archive> <item1> <item2> ...
*   @endcode
*
*   The compressed tar archive always will be newly created. (If archive exists
*   already it will be overwritten without warning.)
*
*   When no relative directory path is given (relativeDirPath set to GLO_NULL),
*   then the item pathes in the archive will be stored relatively to root directory
*   (this means that leading '/' from absolute Linux path of item will be removed).
*
*   When a relative directory path is set to a valid path, then the item pathes
*   in the archive are stored relatively to this directory when possible. More
*   detailed we have following behavior if relativeDirPath is set:
*      - if given relative path is an initial part of the item path, then item
*        path relative to given path is stored in the tar archive
*      - if given relative path is not an initial part of the item path, then
*        the item path will be stored relative to the root directory (this means
*        that leading '/' from absolut Linux path of item will be removed).
*
*   If an item path in the item array is related to a file, then simply the file is
*   added to the archive.
*
*   If an item path in the item array is related to a directory, then directory with
*   its complete recursive content (all contained directories and files) is added.
*
*   For the detailed behavior of the function see also examples of function
*   AaFileTarItemArray() (it looks quite similar, only that the archive is compressed
*   when AaFileTarGzipItemArray() is used).
*
*   @note
*   All pathes in the interface (compressed archive path, pathes of items in array and
*   relative path) have to be conform to AaFile path notation.
*   Internally a path is resolved into its real Linux path and finally the tar
*   archive will contain the resolved Linux pathes (at least if path storage relative
*   to root directory was chosen for archiving by setting relativeDirPath to GLO_NULL).
*
*   @par Errors:
*
*   Additionally to returned error codes, the function raises exeptions analogous to
*   AaFileOpen() - since it is internally reused or similarly implemented.
*
*   @par Restrictions:
*      - Length of the archive, item and relative directory pathes cannot exceed
*        #AAFILE_FILENAME_MAX
*      - The pathes only are allowed to have portable characters, as defined in the
*        AaFile API specification.
*
*   @par Example:
*
*   See example section of AaFileTarItemArray(), which is similar, only that with
*   AaFileTarGzipItemArray() a compressed archive is created.
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
EAaFileRet AaFileTarGzipItemArray(char* archivePath,
                                  char** itemPathArray,
                                  u32 itemPathArraySize,
                                  char* relativeDirPath);

/**
*******************************************************************************
*
*   @brief AaFileTarItem() creates a tar archive from a single item path (the
*                          item either can be a file or a directory, but
*                          typically this interface is thought for archiving
*                          single directories)
*
*   @param[in]  archivePath     archive path
*   @param[in]  itemPath        path of item to be added to archive
*   @param[in]  relativeDirPath path to which the item pathes in the archive
*                               will be stored relative to. If set to GLO_NULL
*                               then the item pathes will be stored
*
*   @return #EAaFileRet_Ok in case of success, otherwise #EAaFileRet_Error.
*
*   @par Description:
*
*   The function corresponds to command:
*   @code
*          tar -cf -C <reldir> <archive> <item>
*   @endcode
*
*   The function only is a specialized form of AaFileTarItemArray() where only
*   one item would be given in the list.
*   Therefore the function only is for convenience to avoid assembling of a
*   path array when only one directory item has to be archived.
*
*   By this behavior is analogous to AaFileTarItemArray(): for detailed behavior
*   see description of AaFileTarItemArray() or examples below.
*
*   @note
*   All pathes in the interface (archive, item and relative path) have to be conform
*   to AaFile path notation.
*   Internally a path is resolved into its real Linux path and finally the tar
*   archive will contain the resolved Linux pathes (at least if path storage relative
*   to root directory was chosen for archiving by setting relativeDirPath to GLO_NULL).
*
*   @par Errors:
*
*   Additionally to returned error codes, the function raises exeptions analogous to
*   AaFileOpen() - since it is internally reused or similarly implemented.
*
*   @par Restrictions:
*      - Length of archive, item and relative directory pathes cannot exceed
*        #AAFILE_FILENAME_MAX
*      - The pathes only are allowed to have portable characters, as defined in the
*        AaFile API specification.
*
*   @par Example:
*
*   @code
*
*    // Precondition:
*    //   1) AaFile volume /logs/ corresponds to Linux path /var/log
*    //   2) Linux directory structure of volume /logs/ is:
*    //           /var/log/tardir/
*    //           /var/log/tardir/subdir/
*    //           /var/log/tardir/subdir/file1.txt
*    //           /var/log/tardir/subdir/file2.txt
*
*    char* fileName1 = "/logs/tardir/subdir/file1.txt";
*    char* baseDir   = "/logs/tardir";
*    char* subDir    = "/logs/tardir/subdir";
*    char* archName  = "/logs/tardir/myarch.tar";
*
*    // *** Adding directory content with pathes relative to archive base directory /logs/tardir ***
*
*    if ( EAaFileRet_Ok != AaFileTarItem(archName, subDir, baseDir) ) { handleError(); }
*
*    // if tar file content is now listed with command 'tar -tf myarch.tar' it would show:
*    //     subdir/
*    //     subdir/file1.txt
*    //     subdir/file2.txt
*
*    // *** Adding directory content with pathes relative to directory /logs/tardir/subdir ***
*
*    if ( EAaFileRet_Ok != AaFileTarItem(archName, subDir, subDir) ) { handleError(); }
*
*    // if tar file content is now listed with command 'tar -tf myarch.tar' it would show:
*    //     ./
*    //     ./file1.txt
*    //     ./file2.txt
*
*    // *** Adding directory content with pathes relative to root directory / ***
*
*    if ( EAaFileRet_Ok != AaFileTarItem(archName, subDir, GLO_NULL) ) { handleError(); }
*
*    // if tar file content is now listed with command 'tar -tf myarch.tar' it would show:
*    //     var/log/tardir/subdir/
*    //     var/log/tardir/subdir/file1.txt
*    //     var/log/tardir/subdir/file2.txt
*
*    // *** Adding a file with path relative to root directory / ***
*
*    if ( EAaFileRet_Ok != AaFileTarItem(archName, fileName1, GLO_NULL) ) { handleError(); }
*
*    // if tar file content is now listed with command 'tar -tf myarch.tar' it would show:
*    //     var/log/tardir/subdir/file1.txt
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
EAaFileRet AaFileTarItem(char* archivePath, char* itemPath, char* relativeDirPath);

/**
*******************************************************************************
*
*   @brief AaFileTarGzipItem() creates a gzip compressed tar archive from a
*                              single item path (the item either can be a file
*                              or a directory, but typically this interface is
*                              thought for archiving single directories)
*
*   @param[in]  archivePath     archive path
*   @param[in]  itemPath        path of item to be added to archive
*   @param[in]  relativeDirPath path to which the item pathes in the archive
*                               will be stored relative to. If set to GLO_NULL
*                               then the item pathes will be stored
*
*   @return #EAaFileRet_Ok in case of success, otherwise #EAaFileRet_Error.
*
*   @par Description:
*
*   The function corresponds to command:
*   @code
*          tar -czf -C <reldir> <archive> <item>
*   @endcode
*
*   The function only is a specialized form of AaFileTarGzipItemArray() where
*   only one item would be given in the list.
*   Therefore the function only is for convenience to avoid assembling of a
*   path array when only one directory item has to be archived.
*
*   By this behavior is analogous to AaFileTarGzipItemArray(): for detailed
*   behaviour see description of AaFileTarGzipItemArray() or examples of function
*   AaFileTarItem() (it looks quite similar, only that the archive is compressed
*   when AaFileTarGzipItem() is used).
*
*   @note
*   All pathes in the interface (compressed archive, item and relative path) have to
*   be conform to AaFile path notation.
*   Internally a path is resolved into its real Linux path and finally the tar
*   archive will contain the resolved Linux pathes (at least if path storage relative
*   to root directory was chosen for archiving by setting relativeDirPath to GLO_NULL).
*
*   @par Errors:
*
*   Additionally to returned error codes, the function raises exeptions analogous to
*   AaFileOpen() - since it is internally reused or similarly implemented.
*
*   @par Restrictions:
*      - Length of archive, item and relative directory pathes cannot exceed
*        #AAFILE_FILENAME_MAX
*      - The pathes only are allowed to have portable characters, as defined in the
*        AaFile API specification.
*
*   @par Example:
*
*   See example section of AaFileTarItem(), which is similar, only that with
*   AaFileTarGzipItem() a compressed archive is created.
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
EAaFileRet AaFileTarGzipItem(char* archivePath, char* itemPath, char* relativeDirPath);

/**
*******************************************************************************
*
*   @brief AaFileTarExtract() extract tar archive to specified destination
*                             directory or to root directory
*
*   @param[in]  archivePath archive path
*   @param[in]  destDirPath path of destination directory. If set to GLO_NULL
*                           then the root directory will be the destination.
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error.
*
*   @par Description:
*
*   The function corresponds to command:
*   @code
*          tar -xf <archive> -C <destdir>
*   @endcode
*
*   The destination directory for extracted items is determined as follows:
*      - if parameter destDirPath holds a valid and existing
*        directory it will be used as base directory for extracted items
*      - if parameter destDirPath is set to GLO_NULL, then the root directory
*        will be taken as destination for extracted items
*
*   For the detailed behavior of the function see also examples below.
*
*   @note
*   All pathes in the interface (archive path and destination path) have to be
*   conform to AaFile path notation.
*   Internally the tar archive always contains Linux path names (at least when
*   names relative to root were added to the archive before).
*   Depending on the source of the tar file it might contain items that have
*   non-portable names in AaFile context. All items, no matter if conform to
*   AaFile or not, are extracted, but the user should be aware that some of the
*   files might not be accessible through AaFile means afterwards.
*
*   @par Errors:
*
*   Additionally to returned error codes, the function raises exceptions analogous to
*   AaFileOpen() - since it is internally reused or similarly implemented.
*
*   @par Restrictions:
*      - Length of the archive and destination directory path cannot exceed
*        #AAFILE_FILENAME_MAX
*      - The pathes only are allowed to have portable characters, as defined in the
*        AaFile API documentation.
*
*   None
*
*   @par Example:
*
*   @code
*
*    // Precondition:
*    //   1) AaFile volume /logs/ corresponds to Linux path /var/log
*    //   2) Linux directory structure of volume /logs/ is:
*    //           /var/log/destdir/
*    //           /var/log/tardir/
*    //           /var/log/tardir/myarch1.tar
*    //           /var/log/tardir/myarch2.tar
*    //   3) Content of myarch1.tar listed with 'tar -tf myarch1.tar':
*    //           subdir/
*    //           subdir/file1.txt
*    //           subdir/file2.txt
*    //   4) Content of myarch2.tar listed with 'tar -tf myarch2.tar':
*    //           var/log/tardir/subdir/
*    //           var/log/tardir/subdir/file1.txt
*    //           var/log/tardir/subdir/file2.txt
*
*    char* archName1 = "/logs/tardir/myarch1.tar";
*    char* archName2 = "/logs/tardir/myarch2.tar";
*    char* baseDir   = "/logs/tardir";
*    char* subDir    = "/logs/tardir/subdir";
*    char* destDir   = "/logs/destdir";
*
*    // *** Extracting archive 1 to archive base directory /logs/tardir ***
*
*    if ( EAaFileRet_Ok != AaFileTarExtract(archName1, baseDir) ) { handleError(); }
*
*    // Linux directory structure of volume /logs/ is now:
*    //     /var/log/destdir/
*    //     /var/log/tardir/
*    //     /var/log/tardir/myarch1.tar
*    //     /var/log/tardir/myarch2.tar
*    //     /var/log/tardir/subdir/
*    //     /var/log/tardir/subdir/file1.txt
*    //     /var/log/tardir/subdir/file2.txt
*
*    // *** Extracting archive 2 to explicite destination directory /logs/tardir/destdir ***
*
*    if ( EAaFileRet_Ok != AaFileTarExtract(archName2, destDir) ) { handleError(); }
*
*    // Linux directory structure of volume /logs/ is now:
*    //     /var/log/destdir/
*    //     /var/log/destdir/var/
*    //     /var/log/destdir/var/log/
*    //     /var/log/destdir/var/log/tardir/
*    //     /var/log/destdir/var/log/tardir/subdir/
*    //     /var/log/destdir/var/log/tardir/subdir/file1.txt
*    //     /var/log/destdir/var/log/tardir/subdir/file2.txt
*    //     /var/log/tardir/
*    //     /var/log/tardir/myarch1.tar
*    //     /var/log/tardir/myarch2.tar
*    //     /var/log/tardir/subdir/
*    //     /var/log/tardir/subdir/file1.txt
*    //     /var/log/tardir/subdir/file2.txt
*
*    // Remove destination directory and sub directory
*    AaFileRemoveDir(destDir);
*    AaFileRemoveDir(subDir);
*
*    // Linux directory structure of volume /logs/ is now:
*    //     /var/log/tardir/
*    //     /var/log/tardir/myarch1.tar
*    //     /var/log/tardir/myarch2.tar
*
*    // *** Extracting archive 2 to root directory / ***
*
*    if ( EAaFileRet_Ok != AaFileTarExtract(archName2, GLO_NULL) ) { handleError(); }
*
*    // Linux directory structure of volume /logs/ is now:
*    //     /var/log/tardir/
*    //     /var/log/tardir/myarch1.tar
*    //     /var/log/tardir/myarch2.tar
*    //     /var/log/tardir/subdir/
*    //     /var/log/tardir/subdir/file1.txt
*    //     /var/log/tardir/subdir/file2.txt
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
EAaFileRet AaFileTarExtract(char* archivePath, char* destDirPath);

/**
*******************************************************************************
*
*   @brief AaFileTarGzipExtract() extract gzip compressed tar archive to
*                                 specified destination directory or to root
*                                 directory
*
*   @param[in]  archivePath archive path
*   @param[in]  destDirPath path of destination directory. If set to GLO_NULL
*                           then the root directory will be the destination.
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error.
*
*   @par Description:
*
*   The function corresponds to command:
*   @code
*          tar -xzf <archive> -C <destdir>
*   @endcode
*
*   The destination directory for extracted items is determined as follows:
*      - if parameter destDirPath holds a valid and existing directory it will
*        be used as base directory for extracted items
*      - if parameter destDirPath is set to GLO_NULL, then the root directory
*        will be taken as destination for extracted items
*
*   By this behavior is analogous to AaFileTarExtract(): for detailed behavior
*   see also examples of function AaFileTarExtract() (it looks quite similar, only
*   that the archive has to be gzip compressed when AaFileTarGzipExtract() is used).
*
*   @note
*   All pathes in the interface (compressed archive path and destination path) have
*   to be conform to AaFile path notation.
*   Internally the tar archive always contains Linux path names (at least when
*   names relative to root were added to the archive before).
*   Depending on the source of the tar file it might contain items that
*   have non-portable names in AaFile context. All items, no matter if conform
*   to AaFile or not, are extracted, but the user should be aware that some of the
*   files might not be accessible through AaFile means afterwards.
*
*   @par Errors:
*
*   Additionally to returned error codes, the function raises exceptions analogous to
*   AaFileOpen() - since it is internally reused or similarly implemented.
*
*   @par Restrictions:
*      - Length of the archive and destination directory path cannot exceed
*        #AAFILE_FILENAME_MAX
*      - The pathes only are allowed to have portable characters, as defined in the
*        AaFile API documentation.
*
*
*
*   @par Example:
*
*   See example section of AaFileTarExtract(), which is similar, only that with
*   AaFileTarGzipExtract() the archive to be extracted has to be gzip compressed.
*
*
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
EAaFileRet AaFileTarGzipExtract(char* archivePath, char* destDirPath);

/**
*******************************************************************************
*
*   @brief AaFileTarExtractOffset() extract tar archive, which is embedded in
*                                   an input file behind a defined offset
*
*   @param[in]  inFilePath  path of input file, which contains a tar archive
*   @param[in]  destDirPath path of destination directory. If set to GLO_NULL
*                           then the root directory will be the destination.
*   @param[in]  offset      offset in bytes from start of input file to embedded
*                           tar archive.
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error.
*
*   @par Description:
*
*   The function corresponds to command:
*   @code
*          tail <input file> -c <filesize - offset> | tar -x -C <destdir>
*   @endcode
*
*   The destination directory for extracted items is determined as follows:
*      - if parameter destDirPath holds a valid and existing
*        directory it will be used as base directory for extracted items
*      - if parameter destDirPath is set to GLO_NULL, then the root directory
*        will be taken as destination for extracted items
*
*   By this behavior is analogous to AaFileTarExtract(): for detailed behavior
*   see also examples of function AaFileTarExtract() (it looks quite similar, only
*   that the input file has to have an embedded tar archive behind a given offset).
*
*   @note
*   All pathes in the interface (input file path and destination path) have to be
*   conform to AaFile path notation.
*   Internally the embedded tar archive always contains Linux path names (at least
*   when names relative to root were added to the archive before).
*   Depending on the source of the embedded tar archive it might contain items that
*   have non-portable names in AaFile context. All items, no matter if conform to
*   AaFile or not, are extracted, but the user should be aware that some of the files
*   might not be accessible through AaFile means afterwards.
*
*   @par Errors:
*
*   Additionally to returned error codes, the function raises exceptions analogous to
*   AaFileOpen() - since it is internally reused or similarly implemented.
*
*   @par Restrictions:
*      - Length of the input file and destination directory path cannot exceed
*        #AAFILE_FILENAME_MAX
*      - The pathes only are allowed to have portable characters, as defined in the
*        AaFile API documentation.
*
*   None
*
*   @par Example:
*
*   See example section of AaFileTarExtract(), which is similar, only that with
*   AaFileTarExtractOffset() the input file has to contain a tar archive behind a
*   given offset.
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
EAaFileRet AaFileTarExtractOffset(char* inFilePath, char* destDirPath, u32 offset);

/**
*******************************************************************************
*
*   @brief AaFileTarGzipExtractOffset() extract gzip compressed tar archive,
*                                       which is embedded in an input file
*                                       behind a defined offset
*
*   @param[in]  inFilePath  path of input file, which contains a gzip compressed
*                           tar archive
*   @param[in]  destDirPath path of destination directory. If set to GLO_NULL
*                           then the root directory will be the destination.
*   @param[in]  offset      offset in bytes from start of input file to embedded
*                           gzip compressed tar archive
*
*   @return     #EAaFileRet_Ok on success, otherwise #EAaFileRet_Error.
*
*   @par Description:
*
*   The function corresponds to command:
*   @code
*          tail <input file> -c <filesize - offset>  | tar -xz -C <destdir>
*   @endcode
*
*   The destination directory for extracted items is determined as follows:
*      - if parameter destDirPath holds a valid and existing
*        directory it will be used as base directory for extracted items
*      - if parameter destDirPath is set to GLO_NULL, then the root directory
*        will be taken as destination for extracted items
*
*   By this behavior is analogous to AaFileTarExtractOffset() and therefore also
*   to AaFileTarExtract(): for detailed behavior see also examples of function
*   AaFileTarExtract() (it looks quite similar, only that the input file has to
*   have an embedded gzip compressed archive behind a given offset).
*
*   @note
*   All pathes in the interface (input file path and destination path) have to be
*   conform to AaFile path notation.
*   Internally the embedded gzip compressed tar archive always contains Linux path
*   names (at least when names relative to root were added to the archive before).
*   Depending on the source of the embedded tar archive it might contain items that
*   have non-portable names in AaFile context. All items, no matter if conform to
*   AaFile or not, are extracted, but the user should be aware that some of the files
*   might not be accessible through AaFile means afterwards.
*
*   @par Errors:
*
*   Additionally to returned error codes, the function raises exceptions analogous to
*   AaFileOpen() - since it is internally reused or similarly implemented.
*
*   @par Restrictions:
*      - Length of the input file and destination directory path cannot exceed
*        #AAFILE_FILENAME_MAX
*      - The pathes only are allowed to have portable characters, as defined in the
*        AaFile API documentation.
*
*   None
*
*   @par Example:
*
*   See example section of AaFileTarExtract(), which is similar, only that with
*   AaFileTarGzipExtractOffset() the input file has to contain a gzip compressed tar
*   archive behind a given offset.
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
EAaFileRet AaFileTarGzipExtractOffset(char* inFilePath, char* destDirPath, u32 offset);

/** @} */


#ifdef __cplusplus
}
#endif

#endif  /* _MCU_IF_AAFILETAR_H_ */
