/** @file
* @brief AaFileSicFtp common definitions.
* @copyright 2017, 2019 Nokia. All rights reserved.
*/

#ifndef _COMMON_IF_AAFILESICFTP_DEFS_H_
#define _COMMON_IF_AAFILESICFTP_DEFS_H_

#include <CcsCommon.h>
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiCommon
 * @ingroup    dgAaFile
 */

/** @{ */

/**
******************************************************************************
*
* @verbatim
*  Tag name:        ccs.service.aafile.sicftp.client.timeout
*
*  Direction:       input
*
*  Description:     Maximum number of seconds SICFTP client waits for a SIC-message
*                   during a file transfer.
*
*  Effect analysis: If this tag is not set, a default value for client timeout is used.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 1
*
*  Define:          AAFILE_SICFTP_CONFIG_TAG_CLIENT_TIMEOUT
*
*  See:             None
* @endverbatim
*/
#define AAFILE_SICFTP_CONFIG_TAG_CLIENT_TIMEOUT "ccs.service.aafile.sicftp.client.timeout"

/**
* @verbatim
*  Tag name:        ccs.service.aafile.sicftp.client.get.delay
*
*  Direction:       input
*
*  Description:     The tag specifies delay in milliseconds between received GET response message and
*                   sent GET request message.
*
*  Effect analysis: If the tag is not set or set to 0, GET request message is sent without any
*                   delay, just after received GET response message.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u16       [0,1000]
*
*  Define:          AAFILE_SICFTP_CONFIG_TAG_CLIENT_GET_DELAY
*
*  See:             AaFileSicFtpGet, AaFileSicFtpGetXz, AaFileSicFtpGetXzExt
* @endverbatim
*/
#define AAFILE_SICFTP_CONFIG_TAG_CLIENT_GET_DELAY "ccs.service.aafile.sicftp.client.get.delay"

/**
* @verbatim
*  Tag name:        ccs.service.aafile.sicftp.client.put.delay
*
*  Direction:       input
*
*  Description:     The tag specifies delay in milliseconds between received PUT response message and
*                   sent PUT request message.
*
*  Effect analysis: If the tag is not set or set to 0, PUT request message is sent without any
*                   delay, just after received PUT response message.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u16       [0,1000]
*
*  Define:          AAFILE_SICFTP_CONFIG_TAG_CLIENT_PUT_DELAY
*
*  See:             AaFileSicFtpPut
* @endverbatim
*/
#define AAFILE_SICFTP_CONFIG_TAG_CLIENT_PUT_DELAY "ccs.service.aafile.sicftp.client.put.delay"

/**
* @verbatim
*  Tag name:        ccs.service.aafile.sicftp.server.timeout
*
*  Direction:       input
*
*  Description:     Maximum number of seconds SICFTP server waits for a SIC-message
*                   during a file transfer.
*
*  Effect analysis: If this tag is not set, a default value for server timeout is used.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 1
*
*  Define:          AAFILE_SICFTP_CONFIG_TAG_SERVER_TIMEOUT
*
*  See:             None
* @endverbatim
******************************************************************************/
#define AAFILE_SICFTP_CONFIG_TAG_SERVER_TIMEOUT "ccs.service.aafile.sicftp.server.timeout"

/**
* @verbatim
*  Tag name:        ccs.service.aafile.sicftp.server.priority
*
*  Direction:       input
*
*  Description:     The server priority is the runtime priority of the SicFtp-server-process
*
*  Effect analysis: If this tag is not set, the default priority for SicFtp is used
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 1
*
*  Define:          AAFILE_SICFTP_CONFIG_TAG_SERVER_PRIORITY
*
*  See:             None
* @endverbatim
******************************************************************************/
#define AAFILE_SICFTP_CONFIG_TAG_SERVER_PRIORITY "ccs.service.aafile.sicftp.server.priority"

/**
* @verbatim
*  Tag name:        ccs.service.aafile.sicftp.chunksize
*
*  Direction:       input
*
*  Description:     The chunk-size is the amount of data that the #AaFileSicFtpPut() function will read, and
*                   #AaFileSicFtpGet() function will write, in one go to the file. Files with bigger sizes
*                   will be divided in these chunk sizes.
*
*  Effect analysis: If this tag is not set, a default value for chunksize is used.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 1
*
*  Define:          AAFILE_SICFTP_CONFIG_TAG_CHUNKSIZE
*
*  See:             None
* @endverbatim
******************************************************************************/
#define AAFILE_SICFTP_CONFIG_TAG_CHUNKSIZE "ccs.service.aafile.sicftp.chunksize"

/**
* @verbatim
*  Tag name:        ccs.service.aafile.sicftp.blocksize
*
*  Direction:       input
*
*  Description:     The block-size is the payload-size the internal SICFTP-messages will
*                   transfer at maximum in one go.
*
*                   For using the SICFTP-message-API directly this define will be essential
*                   for the buffers you have to provide. Especially using the GET-transfer the
*                   SICFTP server will return a SIC-message with a maximum of
*                   #AAFILE_SICFTP_CONFIG_TAG_BLOCKSIZE bytes in its payload data.
*
*  Effect analysis: If this tag is not set, a default value for blocksize is used.
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       >= 1
*
*  Define:          AAFILE_SICFTP_CONFIG_TAG_BLOCKSIZE
*
*  See:             None
* @endverbatim
******************************************************************************/
#define AAFILE_SICFTP_CONFIG_TAG_BLOCKSIZE "ccs.service.aafile.sicftp.blocksize"

/**
 * @brief These defines should be not part of this interface-file but be placed
 * in the appropriate place.
 */
#define AAFILE_SICFTP_SERVER_CPID  0x0614

/**
 * @brief 2*10 kiB chunk size
 * @see AAFILE_SICFTP_CONFIG_TAG_CHUNKSIZE config-tag
 */
#define AAFILE_SICFTP_CHUNKSIZE_DEFAULT 20480

/**
 * @brief 10 kiB block size for SIC-messaging
 * @see AAFILE_SICFTP_CONFIG_TAG_BLOCKSIZE config-tag
 */
#define AAFILE_SICFTP_BLOCKSIZE_DEFAULT 10240

/**
 * @brief TAaFileSicFtp: Type for AaFileListing container
 */
typedef struct SAaFileListing TAaFileListing;

/**
 * @brief Structure containing a volume's directory
 * @warning The caller of any API-function returning this struct is responsible
 * for free'ing the allocated 'files'-pointer.
 *
 */
struct SAaFileListing {
    /** @brief Number of entries in this file listing */
    u32 entries;

    /** @brief Pointer to a string containing the file-paths.
     * Each path's end is marked with a '\n' character.
     * There must be exactly 'entries' path-elements be available.
     * Please use strtok_r() to separate the entries.
     *
     * The compression of the filenames is made to save memory. The other
     * way round could be to use a dynamic array with fixed-length entries. But
     * then we'll waste a big amount of unused memory with each call.
     *
     * @note The API-function will allocate adequate memory-size for all 'entries'.
     * But the requester will become the owner of this buffer and therefore must
     * take care for free'ing it in time.
     **/
    char *files;
};

/** @brief AaFileSicFtp return values */
typedef enum EAaFileSicFtpRet {
    EAaFileSicFtpRet_Ok                             =   0,  /**< No error */
    EAaFileSicFtpRet_Timeout                        =  -1,  /**< Timeout occured */
    EAaFileSicFtpRet_AccessViolation                =  -2,  /**< Wrong permission either on remote or local node */
    EAaFileSicFtpRet_FileAlreadyExists              =  -3,  /**< Destination file exists and must first be removed */
    EAaFileSicFtpRet_FileNotFound                   =  -4,  /**< File could not be found */
    EAaFileSicFtpRet_FileNotReadable                =  -5,  /**< File could not be read, because it is already opened for writing */
    EAaFileSicFtpRet_FileNotWritable                =  -6,  /**< File could not be written, because it is already opened for reading */
    EAaFileSicFtpRet_FileCopyError                  =  -7,  /**< Error during file copying */
    EAaFileSicFtpRet_DirNotFound                    =  -8,  /**< Directory could not be found */
    EAaFileSicFtpRet_DirNotReadable                 =  -9,  /**< Directory could not be read, because it is already in use for another conflicting action */
    EAaFileSicFtpRet_DirNotWritable                 = -10,  /**< Directory could not be written, because it is already in use for another conflicting action */
    EAaFileSicFtpRet_DirCopyError                   = -11,  /**< Error during directory copying */
    EAaFileSicFtpRet_NoMemory                       = -12,  /**< Memory allocation failed */
    EAaFileSicFtpRet_ReadError                      = -13,  /**< Read error */
    EAaFileSicFtpRet_WriteError                     = -14,  /**< Write error */
    EAaFileSicFtpRet_SeekError                      = -15,  /**< Seek error */
    EAaFileSicFtpRet_RenameError                    = -16,  /**< File could not be renamed */
    EAaFileSicFtpRet_StatError                      = -17,  /**< Failure in calling stat-function */
    EAaFileSicFtpRet_AddressFailure                 = -18,  /**< SIC-address failure */
    EAaFileSicFtpRet_MessageFailure                 = -19,  /**< SIC-messaging failure */
    EAaFileSicFtpRet_NoTransferInProgress           = -20,  /**< Instantiation of new transfer necessary, no ongoing transfer found */
    EAaFileSicFtpRet_OutOfRange                     = -21,  /**< Value is out of range, used in context of #AaFileSicFtpList function */
    EAaFileSicFtpRet_UndefinedError                 = -22,  /**< Undefined error, should not happen. Regularly a meaningful return-code should be available. */
    EAaFileSicFtpRet_CopyError_NonPortableFile      = -23,  /**< Non portable file(s) detected during file or directory copy */
    EAaFileSicFtpRet_WrongInputParameter            = -24,  /**< One or more input parameters are incorrect */
    EaFileSicFtpRet_End                             = -25
} EAaFileSicFtpRet;

/** @brief Begin number scheme of SICFTP item type codes */
#define AAFILE_SIC_FTP_ITEM_TYPE_VALUE_BEGIN 0

/** @brief AaFileSicFtp item types */
typedef enum EAaFileSicFtpItemType {
    EAaFileSicFtpItemType_Undefined = AAFILE_SIC_FTP_ITEM_TYPE_VALUE_BEGIN,         /**< undefined item type, set in case of failing existence checks */
    EAaFileSicFtpItemType_File      = AAFILE_SIC_FTP_ITEM_TYPE_VALUE_BEGIN + 1,     /**< file item type */
    EAaFileSicFtpItemType_Dir       = AAFILE_SIC_FTP_ITEM_TYPE_VALUE_BEGIN + 2,     /**< directory item type */
    EAaFileSicFtpItemType_End       = AAFILE_SIC_FTP_ITEM_TYPE_VALUE_BEGIN + 3
} EAaFileSicFtpItemType;

/** @see ccs.service.aafile.sicftp.client.timeout config-tag */
#define AAFILE_SICFTP_CLIENT_TIMEOUT_DEFAULT 30   /* 30 seconds latency */

/* TODO: introduce config-tag for copy timeout */
/** @brief 30 min latency for copying */
#define AAFILE_SICFTP_CLIENT_COPY_TIMEOUT_DEFAULT 1800

/* TODO: introduce config-tag for copy dir timout */
/** @brief 1 hour 11 min latency for copying directories
 *  @note This is currently the maximum possible value according to current implementation:
 *  value is multipied by 1000000 and in order not to overflow 32 bit integers, 4294 is the limit
 */
#define AAFILE_SICFTP_CLIENT_COPY_DIR_TIMEOUT_DEFAULT 4294

/** @see ccs.service.aafile.sicftp.server.timeout config-tag */
#define AAFILE_SICFTP_SERVER_TIMEOUT_DEFAULT 30   /* 30 seconds latency */

/**
 * @brief Garbage collectors interval time in seconds.
 * In this interval the garbage collector will be awakened and look for
 * outdated transfers.
 */
#define AAFILE_SICFTP_GARBAGE_COLLECTOR_INTERVAL 2

/** @} */


#ifdef __cplusplus
}
#endif

#endif /* _COMMON_IF_AAFILESICFTP_DEFS_H_ */
