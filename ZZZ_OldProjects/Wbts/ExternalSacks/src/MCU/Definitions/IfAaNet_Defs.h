/** @file
*   @brief AaNet MCU definitions.
*   @copyright 2018, 2019 Nokia. All rights reserved.
*/

#ifndef _MCU_IF_AANET_DEFS_H_
#define _MCU_IF_AANET_DEFS_H_

#include <glo_def.h>
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaNetMcuDefs     AaNet MCU definitions
 * @ingroup  dgAaNet
 */

/** @{ */

/**
* Configuration tag for setting service group name.
*/
#define AANET_CONFIG_TAG_GROUP_ID_NAME           "ccs.service.aanet.group"

/**
* Configuration tag for disabling SSH MAC algorithms.
*
* The type of tag is string. Value of the tag should be comma-separated list of SSH MAC
* algorithms which needs to be disabled. The tag should be set in \c rat\_psconfig.xml as
* it will be read only during startup phase. For details about the list of currently
* allowed SSH MAC algorithms please refer to OM_GEN_SFS_NetSec.1810
*
* Example of tag value: \c "hmac-sha1,hmac-sha1-etm@openssh.com,umac-64@openssh.com"
*/
#define AANET_CONFIG_TAG_SSHD_DISABLE_MACS  "ccs.service.aanet.sshd.disable_macs"

/**
 * The type of tag is string. Value of the tag should be comma-separated list of
 * SSH Key Exchange (KEX) algorithms which should be disabled. The tag should be
 * set in \c rat\_psconfig.xml file, as it will be read during AaNet service CE startup.
 *
 * Example of tag value: \c "diffie-hellman-group14-sha1"
 */
#define AANET_CONFIG_TAG_SSHD_DISABLE_KEX   "ccs.service.aanet.sshd.disable_kex"

/**
* Minimum username length.
*/
#define AANET_MIN_USERNAME_LENGTH              4

/**
* Maximum username length.
*/
#define AANET_MAX_USERNAME_LENGTH              32

/**
* Minimum password length.
*/
#define AANET_MIN_PASSWORD_LENGTH              8

/**
* Maximum password length.
*/
#define AANET_MAX_PASSWORD_LENGTH              128

/**
* Name of privileged (root) BTS service account.
*/
#define AANET_BTS_SERVICE_ACCOUNT_NAME         "toor4nsn"

/**
* Name of unprivileged (non-root) BTS service account.
*/
#define AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME     "serviceuser"

/**
* Maximum amount of passwords stored in history
*/
#define AANET_MAX_PASS_HISTORY_LENGTH          400

/**
* Maximum bytes of ssh login banner text including terminator.
*/
#define AANET_MAX_SSH_BANNER_TEXT_LENGTH       CCS_STATIC_CAST(u32,1025)

/**
* @brief Special timeout value for disabling the shell inactivity timeout mechanism.
*
* @par Rationale
* RP002015_1_F1
*
* @see AaNetShellSetTimeout()
*/
#define AANET_SHELL_NO_TIMEOUT      CCS_STATIC_CAST(u32,0)

/**
* @brief Maximum value for the shell inactivity timeout, in seconds.
*
* @par Rationale
* RP002015_1_F1
*
* @see AaNetShellSetTimeout()
*/
#define AANET_SHELL_MAX_TIMEOUT     CCS_STATIC_CAST(u32,86400)

/**
 *  @brief AaNet public return codes.
 *  @note This list is not maintained anymore.
 */
typedef enum EAaNETStatus {
  AaNetRetOk = 0,                               /**< operation was successful */
  AaNetRetParmError,                            /**< invalid parameter (e.g. NULL pointer) was passed as argument */
  AaNetRetIPSNotSupported,                     //deprecated
  AaNetRetIPSFwSetupFailed,                    //deprecated
  AaNetRetIPSStartFailed,                      //deprecated
  AaNetRetIPSWriteError,                       //deprecated
  AaNetRetAddTNameDup,                         //deprecated
  AaNetRetIPSAddTWriteFailed,                  //deprecated
  AaNetRetError,                                /**< underlying operating system error */
  AaNetRetWrongUser,                            /**< user does not exist in the system */
  AaNetIpsecStatusTunnelEstablished,           //deprecated
  AaNetIpsecStatusTunnelNotEstablished,        //deprecated
  AaNetIpsecStatusTunnelUnknown,               //deprecated
  AaNetRetWrongPassword,                        /**< user password is invalid */
  AaNetRetPasswdValidationErr,                 /**< returned if new password will not follow password policy rules LTE2486-B */
  EAaNETStatus_NbrOf
} EAaNETStatus;

/**
 *  @brief AaNet return codes.
 */
typedef enum EAaNetRet {
    EAaNetRet_Ok = 0,                       /**< operation was successful */
    EAaNetRet_ParmError,                    /**< invalid parameter (e.g. NULL pointer) was passed as argument */
    EAaNetRet_Error,                        /**< underlying operating system error */
    EAaNetRet_WrongUser,                    /**< operation cannot be executed for specified user account */
    EAaNetRet_WrongPassword,                /**< user password is invalid */
    EAaNetRet_PasswdValidationErr,          /**< PAM module reported problem with changing password */
    EAaNetRet_NotStarted,                   /**< http server is not started yet */
    EAaNetRet_AlreadyStarted,               /**< http server is already started */
    EAaNetRet_UserExists,                   /**< specified user account already exists in the system */
    EAaNetRet_NoSuchUser,                   /**< specified user account does not exist in the system */

    EAaNetRet_Last
} EAaNetRet;

/**
 * @brief Security mode of http server:
 */
typedef enum EAaNetHttpSecurityMode {
    EAaNetHttpSecurityMode_PlainText = 0,   /**< no encryption, use port 80 by default */
    EAaNetHttpSecurityMode_Tls,             /**< Transport Layer Security, use port 443 by default */

    EAaNetHttpSecurityMode_Last
} EAaNetHttpSecurityMode;

/**
*   @brief Detailed status codes of operations related to setting SSHD and
*   authentication options.
*/
typedef enum EAaNetSshStatus {
    EAaNetSshStatus_Ok = 0,                         /**< operation was successful */
    EAaNetSshStatus_RestrictedRootFail = 1,         /**< failed to change the state of Restricted Root Access mode */
    EAaNetSshStatus_ClientAliveTimeFail = 1<<1,     /**< failed to set SSH client alive time */
    EAaNetSshStatus_LoginDelayFail = 1<<2,          /**< failed to set SSH login delay time */
    EAaNetSshStatus_MaxAuthTriesFail = 1<<3,        /**< failed to set SSH maximum authentication tries */
    EAaNetSshStatus_PasswordHistoryFail = 1<<4,     /**< failed to set length of password history */
    EAaNetSshStatus_LoginBannerFail = 1<<5          /**< failed to set SSH login banner */
} EAaNetSshStatus;

/**
 *  @brief Type for the ssh keys.
 */
typedef struct  SAaNetUserSshKey {
    const char* key;
    const char* description;
} SAaNetUserSshKey;

/**
 *  @brief Container type for additional options that can be set for
 *  vsftpd user accounts. Field names follow names of vsftpd options.
 *  Refer to http://vsftpd.beasts.org/vsftpd_conf.html for description.
 */
typedef struct SAaNetVsftpdOptions {
    TBoolean    connect_from_port_20;   /**< Use PORT-style data connections. Default: NO */
    i32         ftp_data_port;          /**< TCP port from which PORT-style connections originate. Default: 20 */
    i32         local_max_rate;         /**< Maximum transfer rate in bytes per second. Default: 0 (unlimited) */
    i32         trans_chunk_size;       /**< Chunk size in bytes. Default: 0 (autodetect) */
    i32         pasv_min_port;          /**< Start of range of TCP ports used for PASV data connections. Default: 0 (use any port) */
    i32         pasv_max_port;          /**< End of range of TCP ports used for PASV data connections. Default: 0 (use any port) */
} SAaNetVsftpdOptions;

/**
*   @brief Container type for options related to SSH daemon and authentication.
*   \p bannerText points to a memory area that holds a null-terminated string
*   used for SSH banner. This memory is managed by the caller, and is not written
*   to by AaNet. Once AaNetSshConfigureOptionsApply() returns CC&S no longer refers
*   to the memory pointed by \p bannerText. Caller still owns the memory and is
*   responsible for freeing it.
*/
typedef struct SAaNetSshConfigureOptions {
    TBoolean    restrictedRootEnabled;  /**< state of Restricted Root Access mode */
    u32         clientAliveTime;        /**< client alive time in minutes */
    u32         loginDelayTime;         /**< login delay time in seconds */
    u32         maxAuthTries;           /**< maximum authentication attempts per SSH connection */
    u32         passwordHistoryLength;  /**< password history length */
    const char* bannerText;             /**< null-terminated login banner text */
} SAaNetSshConfigureOptions;

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _MCU_IF_AANET_DEFS_H_ */
