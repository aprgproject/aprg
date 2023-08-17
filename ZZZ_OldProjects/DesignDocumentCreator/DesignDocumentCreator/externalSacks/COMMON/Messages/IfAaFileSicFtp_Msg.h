/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaFile SICFTP interface header
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AAFILESICFTP_MSG_H_
#define _COMMON_IF_AAFILESICFTP_MSG_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include <IfAaSysCom_Defs.h>     /* for TAaSysComNid */
#include <IfAaFile_Defs.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/Definitions/IfAaFileSicFtp_Defs.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiCommon
 * @ingroup    dgAaFile
 */

/** @{ */

/* SICFTP related SIC-messages */
#define AAFILE_SICFTP_GET_REQ_MSG          0x0A82      /**< !- SIGNO(struct AaFileSicFtpGetReq) -! @hideinitializer */
#define AAFILE_SICFTP_GET_RESP_MSG         0x0A83      /**< !- SIGNO(struct AaFileSicFtpGetResp) -! */
#define AAFILE_SICFTP_PUT_REQ_MSG          0x0A84      /**< !- SIGNO(struct AaFileSicFtpPutReq) -! @hideinitializer */
#define AAFILE_SICFTP_PUT_RESP_MSG         0x0A85      /**< !- SIGNO(struct AaFileSicFtpPutResp) -! @hideinitializer */
#define AAFILE_SICFTP_REMOVE_REQ_MSG       0x0A86      /**< !- SIGNO(struct AaFileSicFtpRemoveReq) -! @hideinitializer */
#define AAFILE_SICFTP_REMOVE_RESP_MSG      0x0A87      /**< !- SIGNO(struct AaFileSicFtpRemoveResp) -! @hideinitializer */
#define AAFILE_SICFTP_LIST_REQ_MSG         0x0A88      /**< !- SIGNO(struct AaFileSicFtpListReq) -! @hideinitializer */
#define AAFILE_SICFTP_LIST_RESP_MSG        0x0A89      /**< !- SIGNO(struct AaFileSicFtpListResp) -! @hideinitializer */
#define AAFILE_SICFTP_TIMEOUT_MSG          0x0A8A      /**< !- SIGNO(void) -! @hideinitializer */
#define AAFILE_SICFTP_COPY_REQ_MSG         0x0B06      /**< !- SIGNO(struct AaFileSicFtpCopyReq) -! @hideinitializer */
#define AAFILE_SICFTP_COPY_RESP_MSG        0x0B07      /**< !- SIGNO(struct AaFileSicFtpCopyResp) -! @hideinitializer */
#define AAFILE_SICFTP_COPY_DIR_REQ_MSG     0x0B08      /**< !- SIGNO(struct AaFileSicFtpCopyDirReq) -! @hideinitializer */
#define AAFILE_SICFTP_COPY_DIR_RESP_MSG    0x0B09      /**< !- SIGNO(struct AaFileSicFtpCopyDirResp) -! @hideinitializer */
#define AAFILE_SICFTP_REMOVE_DIR_REQ_MSG   0x0B0A      /**< !- SIGNO(struct AaFileSicFtpRemoveDirReq) -! @hideinitializer */
#define AAFILE_SICFTP_REMOVE_DIR_RESP_MSG  0x0B0B      /**< !- SIGNO(struct AaFileSicFtpRemoveDirResp) -! @hideinitializer */
#define AAFILE_SICFTP_LIST_REC_REQ_MSG     0x0B0C      /**< !- SIGNO(struct AaFileSicFtpListRecReq) -! @hideinitializer */
#define AAFILE_SICFTP_LIST_REC_RESP_MSG    0x0B0D      /**< !- SIGNO(struct AaFileSicFtpListRecResp) -! @hideinitializer */
#define AAFILE_SICFTP_CREATE_DIR_REQ_MSG   0x0BA5      /**< !- SIGNO(struct AaFileSicFtpCreateDirReq)  -! @hideinitializer */
#define AAFILE_SICFTP_CREATE_DIR_RESP_MSG  0x0BA6      /**< !- SIGNO(struct AaFileSicFtpCreateDirResp) -! @hideinitializer */
#define AAFILE_SICFTP_EXISTS_REQ_MSG       0x1F14      /**< !- SIGNO(struct AaFileSicFtpExistsReq) -! @hideinitializer */
#define AAFILE_SICFTP_EXISTS_RESP_MSG      0x1F15      /**< !- SIGNO(struct AaFileSicFtpExistsResp) -! @hideinitializer */
#define AAFILE_SICFTP_GET_SIZE_REQ_MSG     0x11D1      /**< !- SIGNO(struct AaFileSicFtpGetSizeReq) -! @hideinitializer */
#define AAFILE_SICFTP_GET_SIZE_RESP_MSG    0x11D2      /**< !- SIGNO(struct AaFileSicFtpGetSizeResp) -! @hideinitializer */


/**
**********************************************************************
* @brief SIC-message structure used to request a remote file.
*
* @see AaFileSicFtpGet
**********************************************************************/
struct AaFileSicFtpGetReq {
    char filename[AAFILE_FILENAME_MAX]; /**< Name of file on remote system (including AaFile volume name) */
    u32 offset; /**< offset in file at which returned fragment should start */
};

/** @brief Typedef for AaFileSicFtpGet request. */
typedef struct AaFileSicFtpGetReq SAaFileSicFtpGetReq;

/**
**********************************************************************
* @brief SIC message structure passed from SICFTP server containing data
* of the requested remote file.
*
* @see #AaFileSicFtpGet
*
* @note If this SIC-message will be used directly from external, thus not using
* the official client-API function #AaFileSicFtpGet(), the caller will get a
* maximum of AAFILE_SICFTP_CONFIG_TAG_BLOCKSIZE bytes or the size of the file (depending
* on what is less) in his response.
**********************************************************************/
struct AaFileSicFtpGetResp {
    char filename[AAFILE_FILENAME_MAX]; /**< Name of file on remote system (including AaFile volume name) */
    EAaFileSicFtpRet returnCode; /**< Indicates success or failure of the request */
    u32 filesize;   /**< Contains total size of remote-file */
    u32 offset;     /**< Offset in file at which returned fragment should start */
    u32 last;       /**< Will be set to non-zero if this is the last fragment of the remote-file been transfered. */
    u32 length;     /**< Length of data-section in this message */
    char data[1];   /**<  Contents of the remote-file beginning at offset. Variable array. */
};

/** @brief Typedef for AaFileSicFtpGet response. */
typedef struct AaFileSicFtpGetResp SAaFileSicFtpGetResp;

/**
**********************************************************************
* @brief SIC message structure used to transfer a local file
* to the SICFTP server.
*
* @see AaFileSicFtpPut
*
* @note If this SIC message will be used directly from external, thus not using
* the official client-API function #AaFileSicFtpPut(), _NO_ checking of length
* will be made. The caller is responsible for creating a valid SIC-message
* containing the complete data amount he claims with the length-value.
**********************************************************************/
struct AaFileSicFtpPutReq {
    char filename[AAFILE_FILENAME_MAX]; /**< Name of file on remote system (including AaFile volume name) */
    u32 filesize;   /**< Contains total size of local-file */
    u32 offset;     /**< Offset in file at which response data-fragment should start.\n
                        If offset is zero, any temporary file is deleted and a new temporary
                        file is created. If offset is non-zero, temporary file length
                        must be equal to offset. */
    u32 last;       /**< If zero remote-file will be named "filename.part"; if non-zero
                        'filename.part' will be renamed to 'filename' */
    u32 length;     /**< Length of data-section in this message */
    char data[1];   /**< Contents of the local-file that should be written to remote-file
                        starting at offset. Variable array. */
};

/** @brief Typedef for AaFileSicFtpPut request. */
typedef struct AaFileSicFtpPutReq SAaFileSicFtpPutReq;

/**
**********************************************************************
* @brief SIC message structure used to send data-chunks of the local file
* to the SICFTP server's remote file.
*
* @see AaFileSicFtpPut
**********************************************************************/
struct AaFileSicFtpPutResp {
    char filename[AAFILE_FILENAME_MAX]; /**< Name of file on remote system (including AaFile volume name) */
    EAaFileSicFtpRet returnCode; /**< Indicates success or failure of the request */
    u32 offset;     /**< Offset in file at which data-fragment was written to */
    u32 last;       /**< Mirrored from request-message, only for integrity check. */
    u32 length;     /**< Length of data-section written to file. */
};

/** @brief Typedef for AaFileSicFtpPut response. */
typedef struct AaFileSicFtpPutResp SAaFileSicFtpPutResp;

/**
**********************************************************************
* @brief SIC message structure used to remove a file on the
* SICFTP server
*
* @see AaFileSicFtpRemove
**********************************************************************/
struct AaFileSicFtpRemoveReq {
    char filename[AAFILE_FILENAME_MAX]; /**< Name of file on remote system (including AaFile volume name) */
};

/** @brief Type for AaFileSicFtpRemove request. */
typedef struct AaFileSicFtpRemoveReq SAaFileSicFtpRemoveReq;

/**
**********************************************************************
* @brief SIC message structure passed from SICFTP server containing
* the result of a file removal.
*
* @see AaFileSicFtpRemove
**********************************************************************/
struct AaFileSicFtpRemoveResp {
    char filename[AAFILE_FILENAME_MAX]; /**< Name of file on remote system (including AaFile volume name) */
    EAaFileSicFtpRet returnCode; /**< Indicates success or failure of the request */
};

/** @brief Type for AaFileSicFtpRemove response. */
typedef struct AaFileSicFtpRemoveResp SAaFileSicFtpRemoveResp;

/**
**********************************************************************
* @brief SIC message structure used to trigger the execution of a remote
* file copy on SICFTP server side
**********************************************************************/
struct AaFileSicFtpCopyReq {
    char srcFileName[AAFILE_FILENAME_MAX]; /**< Name of source file on remote system (including AaFile volume name) */
    char destFileName[AAFILE_FILENAME_MAX]; /**< Name of destination file on remote system (including AaFile volume name) */
};

/** @brief Type for AaFileSicFtpCopy request. */
typedef struct AaFileSicFtpCopyReq SAaFileSicFtpCopyReq;

/**
**********************************************************************
* @brief SIC message structure passed from SICFTP server containing the
* result of a server sided file copy
**********************************************************************/
struct AaFileSicFtpCopyResp {
    char srcFileName[AAFILE_FILENAME_MAX]; /**< Name of source file on remote system (including AaFile volume name) */
    char destFileName[AAFILE_FILENAME_MAX]; /**< Name of destination file on remote system (including AaFile volume name) */
    EAaFileSicFtpRet returnCode; /**< Indicates success or failure on the request */
};

/** @brief Type for AaFileSicFtpCopy response. */
typedef struct AaFileSicFtpCopyResp SAaFileSicFtpCopyResp;

/**
**********************************************************************
* @brief SIC message structure used to trigger the execution of a remote
* directory removal on SICFTP server side
**********************************************************************/
struct AaFileSicFtpRemoveDirReq {
    char dirName[AAFILE_FILENAME_MAX]; /**< Name of directory on remote system (including AaFile volume name) */
};

/** @brief Type for AaFileSicFtpRemoveDir request */
typedef struct AaFileSicFtpRemoveDirReq SAaFileSicFtpRemoveDirReq;

/**
**********************************************************************
* @brief SIC message structure passed from SICFTP server containing the
* result of a server sided directory removal
**********************************************************************/
struct AaFileSicFtpRemoveDirResp {
    char dirName[AAFILE_FILENAME_MAX]; /**< Name of directory on remote system (incuding AaFile volume name) */
    EAaFileSicFtpRet returnCode; /**< Indicates success or failure on the request */
};

/** @brief Type for AaFileSicFtpRemoveDir response */
typedef struct AaFileSicFtpRemoveDirResp SAaFileSicFtpRemoveDirResp;

/**
**********************************************************************
* @brief SIC message structure used to trigger the execution of a remote
* directory copy on SICFTP server side
**********************************************************************/
struct AaFileSicFtpCopyDirReq {
    char srcDirName[AAFILE_FILENAME_MAX]; /**< Name of source directory on remote system (including AaFile volume name) */
    char destDirName[AAFILE_FILENAME_MAX]; /**< Name of destination directory on remote system (including AaFile volume name) */
};

/** @brief Type for AaFileSicFtpCopyDir request */
typedef struct AaFileSicFtpCopyDirReq SAaFileSicFtpCopyDirReq;

/**
**********************************************************************
* @brief SIC message structure passed from SICFTP server containing the
* result of a server sided directory copy
**********************************************************************/
struct AaFileSicFtpCopyDirResp {
    char srcDirName[AAFILE_FILENAME_MAX]; /**< Name of source directory on remote system (including AaFile volume name) */
    char destDirName[AAFILE_FILENAME_MAX]; /**< Name of destination directory on remote system (including AaFile volume name) */
    EAaFileSicFtpRet returnCode; /**< Indicates success or failure on the request */
};

/** @brief Type for AaFileSicFtpCopyDir response */
typedef struct AaFileSicFtpCopyDirResp SAaFileSicFtpCopyDirResp;

/**
**********************************************************************
* @brief SIC message structure used to request a flat file listing
* (or next package of the flat file listing) from the SICFTP server.
*
* @see AaFileSicFtpList
**********************************************************************/
struct AaFileSicFtpListReq {
    char destVolumeName[AAFILE_FILENAME_MAX]; /**< Remote path name (NOTE: field name is misleading; besides volume */
                                              /*   names also directory pathes are allowed.                         */
    u32 offset;                               /**< Offset in list at which returned entries should start */
    u32 maxEntries;                           /**< Maximum of entries to be returned in response message */
};

/** @brief Type for AaFileSicFtpList request */
typedef struct AaFileSicFtpListReq SAaFileSicFtpListReq;

/**
**********************************************************************
* @brief SIC message structure used to request a recursive file listing
* (or next package of the recursive file listing) from SICFTP server.
*
* @see AaFileSicFtpListRecursive
**********************************************************************/
struct AaFileSicFtpListRecReq {
    char path[AAFILE_FILENAME_MAX]; /**< Remote path name */
    u32 offset;                     /**< Offset in list at which returned entries should start */
    u32 maxEntries;                 /**< Maximum of entries to be returned in response message */
};

/** @brief Type for AaFileSicFtpListRec request */
typedef struct AaFileSicFtpListRecReq SAaFileSicFtpListRecReq;

/**
**********************************************************************
* @brief SIC message structure passed from SICFTP server. It contains
* the file list (or at least a part of the file list).
*
* @see AaFileSicFtpList
**********************************************************************/
struct AaFileSicFtpListResp {
    char destVolumeName[AAFILE_FILENAME_MAX]; /**< Remote path name (NOTE: field name is misleading; besides volume */
                                              /*   names also directory pathes are allowed.                         */
    EAaFileSicFtpRet returnCode;              /**< Indicates success or failure of the request */
    u32 totalEntries;                         /**< Contains total number listed files */
    u32 offset;                               /**< File number offset in this listing response */
    u32 entries;                              /**< Number of entries in this listing response */
    char listing[1];                          /**< List of filenames starting at offset. (Variable array.) */
};

/** @brief Type for AaFileSicFtpList response */
typedef struct AaFileSicFtpListResp SAaFileSicFtpListResp;

/**
***********************************************************************
* @brief SIC message structure passed from SICFTP server. It contains
* the file list (or at least a part of the file list).
*
* @see AaFileSicFtpListRecursive
***********************************************************************/
struct AaFileSicFtpListRecResp {
    char path[AAFILE_FILENAME_MAX]; /**< Remote path name */
    EAaFileSicFtpRet returnCode;    /**< Indicates success or failure of the request */
    u32 totalEntries;               /**< Contains total number of listed files */
    u32 offset;                     /**< File number offset in this listing response */
    u32 entries;                    /**< Number of entries in this listing response */
    char listing[1];                /**< List of filnames starting at offset. (Variable array.) */
};

/** @brief Type for AaFileSicFtpListRec response */
typedef struct AaFileSicFtpListRecResp SAaFileSicFtpListRecResp;

/**
*************************************************************************
* @brief SIC message structure used to trigger the execution of a remote
* directory creation on SICFTP server side
*************************************************************************/
struct AaFileSicFtpCreateDirReq {
    char dirName[AAFILE_FILENAME_MAX]; /**< Name of directory on remote system (including AaFile volume name) */
};

/** @brief Type for AaFileSicFtpCreateDir request */
typedef struct AaFileSicFtpCreateDirReq SAaFileSicFtpCreateDirReq;

/**
*************************************************************************
* @brief SIC message structure passed from SICFTP server containing the
* result of a server sided directory creation
*************************************************************************/
struct AaFileSicFtpCreateDirResp {
    char dirName[AAFILE_FILENAME_MAX]; /**< Name of directory on remote system (including AaFile volume name) */
    EAaFileSicFtpRet returnCode;       /**< Indicates success or failure on the request                       */
};

/** @brief Type for AaFileSicFtpCreateDir response */
typedef struct AaFileSicFtpCreateDirResp SAaFileSicFtpCreateDirResp;

/**
*************************************************************************
* @brief SIC message structure used to request an item existence check
* from remote SICFTP server side
*************************************************************************/
struct AaFileSicFtpExistsReq {
    char path[AAFILE_FILENAME_MAX]; /**< Remote path name */
};

/** @brief Type for AaFileSicFtpExists request */
typedef struct AaFileSicFtpExistsReq SAaFileSicFtpExistsReq;

/**
*************************************************************************
* @brief SIC message structure passed from SICFTP server containing the
* result of an item existence check
*************************************************************************/
struct AaFileSicFtpExistsResp {
    char path[AAFILE_FILENAME_MAX]; /**< Remote path                                                                       */
    EAaFileSicFtpRet returnCode;    /**< Indicates success or failure on the request                                       */
    EAaFileSicFtpItemType itemType; /**< Type of remote item if exists (only defined if returnCode is EAaFileSicFtpRet_Ok) */
};

/** @brief Type for AaFileSicFtpExists response */
typedef struct AaFileSicFtpExistsResp SAaFileSicFtpExistsResp;

/**
*************************************************************************
* @brief SIC message structure used to request item size (dir or file)
* from remote SICFTP server side
*************************************************************************/
typedef struct AaFileSicFtpGetSizeReq {
    u8 path[AAFILE_FILENAME_MAX]; /**< Remote path name */
} SAaFileSicFtpGetSizeReq;

/**
*************************************************************************
* @brief SIC message structure passed from SICFTP server containing the
* result of item size (dir or file)
*************************************************************************/
typedef struct AaFileSicFtpGetSizeResp {
    u8 path[AAFILE_FILENAME_MAX]; /**< Remote path                                                                       */
    EAaFileSicFtpRet returnCode;    /**< Indicates success or failure on the request                                       */
    long itemSize;                  /**< Size of remote item (only valid if returnCode is EAaFileSicFtpRet_Ok) */
} SAaFileSicFtpGetSizeResp;


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _COMMON_IF_AAFILESICFTP_MSG_H_ */
