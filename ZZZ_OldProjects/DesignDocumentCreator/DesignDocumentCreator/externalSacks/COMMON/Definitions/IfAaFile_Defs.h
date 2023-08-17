/** @file
*   @brief AaFile common definitions.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2017, 2018 Nokia. All rights reserved.$
*/

#ifndef _COMMON_IF_AAFILE_DEFS_H_
#define _COMMON_IF_AAFILE_DEFS_H_

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiCommon
 * @ingroup    dgAaFile
 */

/** @{ */

/** @brief AaFile return codes */
#define AAFILE_RETURN_VALUE_BEGIN 10

/** @brief AaFile return item types */
typedef enum EAaFileRet {
    EAaFileRet_Ok                = 0,    /**< The operation was successful */
    EAaFileRet_Error             = -1,   /**< An error occurred */

    EAaFileRet_EACCES            = -(AAFILE_RETURN_VALUE_BEGIN + 1),     /**< Permission denied */
    EAaFileRet_EBUSY             = -(AAFILE_RETURN_VALUE_BEGIN + 2),     /**< Device or resource busy */
    EAaFileRet_EINVAL            = -(AAFILE_RETURN_VALUE_BEGIN + 3),     /**< Invalid argument */
    EAaFileRet_EIO               = -(AAFILE_RETURN_VALUE_BEGIN + 4),     /**< I/O error */
    EAaFileRet_EISDIR            = -(AAFILE_RETURN_VALUE_BEGIN + 5),     /**< Is a directory */
    EAaFileRet_ELOOP             = -(AAFILE_RETURN_VALUE_BEGIN + 6),     /**< Too many levels of symbolic links */
    EAaFileRet_EMLINK            = -(AAFILE_RETURN_VALUE_BEGIN + 7),     /**< Too many links */
    EAaFileRet_ENAMETOOLONG      = -(AAFILE_RETURN_VALUE_BEGIN + 8),     /**< Filename too long */
    EAaFileRet_ENOENT            = -(AAFILE_RETURN_VALUE_BEGIN + 9),     /**< No such file or directory */
    EAaFileRet_ENOSPC            = -(AAFILE_RETURN_VALUE_BEGIN + 10),    /**< No space left on device */
    EAaFileRet_ENOTDIR           = -(AAFILE_RETURN_VALUE_BEGIN + 11),    /**< Not a directory */
    EAaFileRet_EXDEV             = -(AAFILE_RETURN_VALUE_BEGIN + 12),    /**< Cross-device link */
    EAaFileRet_ENOMEM            = -(AAFILE_RETURN_VALUE_BEGIN + 13),    /**< Not enough space */

    EAaFileRet_EEXIST            = -(AAFILE_RETURN_VALUE_BEGIN + 17),    /**< File exists */

    /* OSE-specific values */
    EAaFileRet_EAGAIN            = -(AAFILE_RETURN_VALUE_BEGIN + 20),    /**< Resource unavailable, try again */
    EAaFileRet_EOPNOTSUPP        = -(AAFILE_RETURN_VALUE_BEGIN + 21),    /**< Operation not supported on socket */
    EAaFileRet_ENOTMOUNTED       = -(AAFILE_RETURN_VALUE_BEGIN + 22),    /**< Device not mounted */
    EAaFileRet_EPERM             = -(AAFILE_RETURN_VALUE_BEGIN + 23),    /**< Operation not permitted */
    EAaFileRet_EROFS             = -(AAFILE_RETURN_VALUE_BEGIN + 24),    /**< Read-only file system */
    EAaFileRet_ESTALE            = -(AAFILE_RETURN_VALUE_BEGIN + 25),    /**< Reserved */

    /* OS independent values */
    EAaFileRet_NONPORTABLEFILE   = -(AAFILE_RETURN_VALUE_BEGIN + 26),    /**< Not portable file */
    EAaFileRet_OWNERNOTPRESERVED = -(AAFILE_RETURN_VALUE_BEGIN + 27),    /**< Copy operation was successful, but ownership was not preserved */

    EAaFileRet_End               = -(AAFILE_RETURN_VALUE_BEGIN + 28)     /**< Last element */
} EAaFileRet;


/** @brief Parameter for AaFileSeek(): seek relative to current position. */
#define AAFILE_SEEK_CUR        0

/** @brief Parameter for AaFileSeek(): seek relative to the end of file. */
#define AAFILE_SEEK_END        1

/** @brief Parameter for AaFileSeek(): seek relative to the beginning of file. */
#define AAFILE_SEEK_SET        2


/**
 * @brief Support for portability on all OSes
 *
 * One should use the values below, if the code is intended to be portable
 * on various platforms (thus, operating systems).
 *
 * @note As tests show the maximum file length running OSE/OSECK is not the
 * expected 240 but only 48. But this is only valid for the bare filename and
 * will be checked separately.
 */
#define AAFILE_FILENAME_MAX         240

/**
 * @brief Maximum bare filename length on OSE/OSECK.
 */
#define AAFILE_BARE_FILENAME_MAX    48

/**
 * @name AaFile volume name definitions
 * @brief Volume names that are used as a prefix of the file name when calling
 * AaFileOpen() or AaFileRemove().
 * If none of these is used, then the default one will be selected.
 */

/** @{ */

/**
 * @brief Volume that uses ram-based filesystem.
 * This volume is guaranteed to exist in all environments. Any data stored in this
 * volume is not guaranteed to survive system restart.
 */
#define AAFILE_VOLUME_RAM "/ram/"

/**
 * @brief Volume that uses persistent filesystem.
 * This volume does not exist in all environments.
 */
#define AAFILE_VOLUME_ROM "/rom/"

/**
 * @brief Reset proof volume.
 */
#define AAFILE_VOLUME_RPRAM "/rpram/"

/**
 * @brief
 * This is the default mount-point of the secure-storage volume.
 * Under this name the secure-storage volume will be mounted.
 * (see @@AACONFIG_TAG_NAME_SECURE_MOUNT_POINT
 *
 * @note
 * In this very early implementation the mapping of mount-point and real volume
 * is simply made be assuming that there is a directory '/safe' already available
 * in the directory-tree.
 * In a later phase the default device should be a more advanced information
 * what really should be mounted under @@AAFILE_VOLUME_SECURE.
 * So, at moment the user could access any file with prefix '/safe' and
 * will see the file under the real path '/safe'
 */
#define AAFILE_VOLUME_SECURE_MOUNT_POINT_DEFAULT   "/safe"

/**
 * @brief
 * This is the default volume name of the secure-storage volume.
 * This volume will be used to be mounted under the secure-storage
 * mount-point (see @@AACONFIG_TAG_NAME_SECURE_VOLUME)
 *
 * @see @@AAFILE_VOLUME_SECURE_MOUNT_POINT_DEFAULT
 * @see @@AAFILE_VOLUME_SECURE_MOUNT_POINT
 * @see @@AAFILE_VOLUME_SECURE_VOLUME
 */
#define AAFILE_VOLUME_SECURE_VOLUME_DEFAULT   "/safe"

#define AAFILE_VOLUME_SECURE "/safe/"

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * no default volumes are allowed
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_DISABLE 0

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /ram/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_RAM 1

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /rom/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_ROM 2

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /safe/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_SECURE 3

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /ffs/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_FFS 4

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /ffs1/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_FFS1 5

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /ffs2/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_FFS2 6

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /ffs3/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_FFS3 7

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /ffs4/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_FFS4 8

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /rpram/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_RPRAM 9

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /logs/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_LOGS 10

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /stb/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_STB 11

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /pns/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_PNS 12

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /raml/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_RAML 13

/**
 * If value of R&D Tag ERadCcs_AaFileDefaultVolume ("AaFileDefaultVolume") is set to this value,
 * the default volume is set to /data/
 */
#define AAFILE_DEFAULT_VOLUME_RAD_VALUE_DATA 14

/** @} */


/**
 * @defgroup dgAaFileApiCommon AaFile COMMON API
 * @ingroup  dgAaFile
 */

/** @{ */

/** @brief Type for AaFile stream. */
typedef struct TAaFile TAaFile;

/**
 * @brief Abstract substitute for POSIX struct stat. It contains only the fields
 * which are actually used either externally by applications, or internally by CCS.
 */
typedef struct SAaFileStat {
    u32 st_mode;    /**< access permissions */
    u64 st_nlink;   /**< number of hard links */
    u32 st_uid;     /**< user ID of owner */
    u32 st_gid;     /**< group ID of owner */
    i64 st_size;    /**< total size, in bytes */
    i64 st_modtime; /**< time of last modification */
} SAaFileStat;

/**
 * @brief Defines the result nodes for items that are listed through
 * function AaFileListDir()
 */
typedef struct SAaFileDnode {
    char* filename;             /**< name of the item (it can be a file or a directory */
    char* fullname;             /**< full path of the item */
    struct SAaFileStat astat;   /**< abstract stat result of the item */
    struct SAaFileDnode* next;  /**< pointer to next item (if available) */
} SAaFileDnode;

/**
 *  @brief  Enum type for the error status codes of hash verification functions.
 */
typedef enum EAaFileVerifyError {
    EAaFileVerifyError_Success = 0,                /**< The operation was successful */
    EAaFileVerifyError_NoContext,                  /**< Context object is NULL */
    EAaFileVerifyError_ContainerNotFound,          /**< Hash container file was not found */
    EAaFileVerifyError_ContainerSigNotFound,       /**< Hash container signature file was not found */
    EAaFileVerifyError_NoFileToValidate,           /**< File to be validated was not found */
    EAaFileVerifyError_PathExpansionFailed,        /**< Could not expand AaFile Path Notation to OS path */
    EAaFileVerifyError_ReadingContainerFailed,     /**< Error when reading hash container file */
    EAaFileVerifyError_ReadingContainerSigFailed,  /**< Error when reading hash container signature file */
    EAaFileVerifyError_BadContainerSig,            /**< Bad hash container signature */
    EAaFileVerifyError_BadHashValue,               /**< Bad hash value */
    EAaFileVerifyError_BadTargetPath,              /**< Invalid target path */
    EAaFileVerifyError_BadHwUnit                   /**< Invalid hardware unit */
} EAaFileVerifyError;

/** @} */

/** @} */


#ifdef __cplusplus
}
#endif

#endif /* _COMMON_IF_AAFILE_DEFS_H_ */
