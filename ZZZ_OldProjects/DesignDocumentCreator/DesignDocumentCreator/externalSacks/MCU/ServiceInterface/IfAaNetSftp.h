/** @file
*   @brief Functions for managing temporary SFTP user accounts.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright 2018, 2019 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AANET_SFTP_H_
#define _MCU_IF_AANET_SFTP_H_

#include <CcsCommon.h>
#include <../Definitions/IfAaNet_Defs.h>

/** @addtogroup dgAaNetMcu */

/** @{ */

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Add a temporary SFTP user account to the system.
*
* @param[in] username   name of the new user account
* @param[in] password   password for the new user account
*
* @return #EAaNetRet_Ok on success, appropriate #EAaNetRet values on error.
*
* @par Description:
* This function adds a new account dedicated for use with SFTP to the System
* Module. The home directory of the user account is set to
* <tt>/data/<username>/upload/</tt>. Necessary path components are created
* if they don't exist. Access rights are set so that user \c btssw in group
* \c btssw has read and write access to the home directory. The user of this
* API is responsible for deleting the created user account when it is no longer
* needed.
*
* @par Errors:
*  - #EAaNetRet_ParmError   Any of the parameters are \c NULL pointers or empty strings,
*                           or \p username does not meet length requirements.
*  - #EAaNetRet_UserExists  User account with requested name already exists.
*  - #EAaNetRet_Error       Failed to create requested SFTP user account.
*
* @par Restrictions:
*  - \p username must be between #AANET_MIN_USERNAME_LENGTH and
*    AANET_MAX_USERNAME_LENGTH bytes long.
*  - \p username must begin with "sftp". Otherwise the account will be denied
*    login to the System Module when Restricted Root Access is enabled.
*  - User account is restricted to ("jailed" inside) <tt>/data/<username>/</tt>
*    directory and is unable to access the remaining parts of filesystem on
*    the System Module.
*  - Created account will not survive the reboot of System Module.
*
* @par Example:
* @code
* #include <IfAaNetSftp.h>
*
* const char* username = "sftpaccount";
* const char* password = "y83Qc3NqX0lrM2j7";
*
* EAaNetRet result = AaNetSftpAddUser(username, password);
* if( EAaNetRet_Ok != result ) {
*     // handle errors
* }
* @endcode
*
* @par Rationale:
* 5GC001231-B-e
*
* @see AANET_MIN_USERNAME_LENGTH
* @see AANET_MAX_USERNAME_LENGTH
* @see AaNetSftpDeleteUser()
*/
EAaNetRet AaNetSftpAddUser(const char* username, const char* password);

/**
* @brief Delete a temporary SFTP user account from the system.
*
* @param[in] username   name of the account to be removed
*
* @return #EAaNetRet_Ok on success, appropriate #EAaNetRet values on error.
*
* @par Description:
* This function removes a temporary SFTP user account from the System Module.
* The "jail" directory <tt>/data/<username>/</tt> is removed recursively.
*
* @par Errors:
*  - #EAaNetRet_ParmError   \p username is a \c NULL pointer or an empty string.
*  - #EAaNetRet_NoSuchUser  Requested user account does not exist in the system.
*  - #EAaNetRet_WrongUser   Requested user account was not created with AaNetSftpAddUser().
*  - #EAaNetRet_Error       Failed to remove requested SFTP user account.
*
* @par Restrictions:
*  - \p username must be previously added using AaNetSftpAddUser().
*  - Removal of user directories is guaranteed only when account is removed
*    using this API.
*
* @par Example:
* @code
* #include <IfAaNetSftp.h>
*
* const char* username = "sftpaccount";
*
* // create temporary SFTP account, perform SFTP file transfers
*
* EAaNetRet result = AaNetSftpDeleteUser(username);
* if( EAaNetRet_Ok != result ) {
*     // handle errors
* }
* @endcode
*
* @par Rationale:
* 5GC001231-B-e
*
* @see AaNetSftpAddUser()
*/
EAaNetRet AaNetSftpDeleteUser(const char* username);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* _MCU_IF_AANET_SFTP_H_ */
