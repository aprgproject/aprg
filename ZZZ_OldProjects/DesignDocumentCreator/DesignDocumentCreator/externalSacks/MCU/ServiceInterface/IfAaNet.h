/** @file
*   @brief AaNet MCU function prototypes.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AANET_H_
#define _MCU_IF_AANET_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include <../Definitions/IfAaNet_Defs.h>

/**
 * @defgroup dgAaNet        CC&S AaNet Service
 * @defgroup dgAaNetMcu     AaNet MCU API
 * @ingroup  dgAaNet
 */

/** @{ */

#ifdef __cplusplus
extern "C" {
#endif

/**
*********************************************************************************
* @brief    AaNetFTPVsftpdOptionsInit() initializes the vsftpd options structure.
*
* @param[in] options    pointer to structure holding vsftpd configuration parameters
*
* @return   #EAaNetRet_Ok on success, specific error value otherwise.
*
* @par Description
* This function performs initialization of the vsftpd options structure. This is done
* by storing the value interpreted as "do not change this option" in every field of the
* structure. If vsftpd configuration parameters need to be changed, then the user must
* store appropriate values in the structure after initialization.
*
* @par Errors:
*  - #EAaNetRet_ParmError   Invalid parameter: NULL pointer to option structure.
*
* @par Restrictions:
*  - Only a subset of vsftpd options is allowed to be modified. Refer to the description
*  of SAaNetVsftpdOptions for the complete list.
*
* @par Example:
* @code
*   SAaNetVsftpdOptions options;
*   AaNetFTPVsftpdOptionsInit(&options);
*
*   options.local_max_rate = 2048;
*   options.trans_chunk_size = 512;
*
*   if( EAaNetRet_Ok != AaNetFTPConfigureAddUserExt("username", "password", "/tmp", &options) )
*   {
*       // error handling
*   }
* @endcode
*
* @see SAaNetVsftpdOptions
* @see AaNetFTPConfigureAddUserExt()
*
******************************************************************************/
EAaNetRet AaNetFTPVsftpdOptionsInit(SAaNetVsftpdOptions* options);

/**
********************************************************************************
* @brief        AaNetFTPConfigureAddUser(const char* username,const char* password,const char* rootdir);
*
* @param[in] username              User name for ftp user to be created
* @param[in] password              Password in clear text of ftp to be created
* @param[in] rootdir               root directory for this ftp user, specified as Linux path
*
* @return        #AaNetRetOk on success, specific error value otherwise
*
* @par Description:
* The function adds to the system an new ftp user with working directory.
* Path to working directory must be specified as system (Linux) path and it is used as jail directory.
* Also if ccs.service.aanet.group tag is set, ftp user will be created with group id of this tag.
* This user cannot login with anything else then ftp.
*
* @par
* It is possible to create anonymous ftp user. This user will have for now only read rights.
* Also anonymous user with write acces can be created but in this case root directory must be "/raml"
* We use this "/raml" directory as OS pathname and it is passed directly to LFS.
* User will be chrooted into this directory and will have right to upload files to this directory.
* It is allowed to set an empty password for the anonymous user.
*
* @par Errors:
* @return #AaNetRetParmError   Parameters are empty or not in expected format
* @return #AaNetRetError       Adduser failed because of underlaying OS error.
*
* @par Restrictions:
*  - This user is only a temporary ftp user. After reset or power cycle it is gone.
*  - The username must not already exist in the system.
*  - The username has to be between #AANET_MIN_USERNAME_LENGTH and #AANET_MAX_USERNAME_LENGTH characters.
*  - The password has to be between #AANET_MIN_PASSWORD_LENGTH and #AANET_MAX_PASSWORD_LENGTH characters.
*  - Home directory for this user is not created.
*
* @par Example:
* @code
* EAaNETStatus rc;
* rc = AaNetFTPConfigureAddUser("TestUser", "mypassword", "/tmp");
* if ( AaNetRetOk != rc )   {
*     switch(rc){
*        AaNetRetParmError: printf("Parameter error. Please check username password and Rootdirectory");
*                           break;
*        AaNetRetError:     printf("Underlaying OS could not perform requested action.");
*                           break;
*     }
* }
* @endcode
*
* @see AaNetFTPConfigureAddUserInRaml()
* @see AaNetFTPConfigureAddUserExt()
* @see AaNetFTPConfigureDeleteUser()
*
*******************************************************************************/
EAaNETStatus AaNetFTPConfigureAddUser(const char* username, const char* password, const char* rootdir);

/**
********************************************************************************
* @brief        AaNetFTPConfigureAddUserInRaml(const char* username, const char* password)
*
* @param[in] username  User name for ftp user
* @param[in] password  Ftp user password
*
* @return        #AaNetRetOk on success, specific error value otherwise.
*
* @par Description:
* The function adds to the system a new ftp user with ftp root directory set to "/raml".
* User will have read/write access rights to "/raml" and will be chrooted into this directory.
*
* @par Errors:
*  - AaNetRetParmError   Parameters are empty or not in expected format
*  - AaNetRetError       Add user failed because of underlaying OS error.
*
* @par Restrictions:
*  - This user is only a temporary ftp user. After reset or power cycle it is gone.
*  - The username must not already exist in the system.
*  - The username has to be between #AANET_MIN_USERNAME_LENGTH and #AANET_MAX_USERNAME_LENGTH characters.
*  - The password has to be between #AANET_MIN_PASSWORD_LENGTH and #AANET_MAX_PASSWORD_LENGTH characters.
*
* @par Example:
* @code
* EAaNETStatus rc = AaNetRetOk;
* rc=AaNetFTPConfigureAddUserInRaml("TestUser","mypassword");
* if ( AaNetRetOk != rc )   {
*     switch(rc){
*        AaNetRetParmError: printf("Parameter error. Please check username and password");
*                           break;
*        AaNetRetError:     printf("Underlaying OS could not perform requested action.");
*                           break;
*     }
* }
* @endcode
*
* @see AaNetFTPConfigureAddUser()
* @see AaNetFTPConfigureAddUserExt()
* @see AaNetFTPConfigureDeleteUser()
*
*******************************************************************************/
EAaNETStatus AaNetFTPConfigureAddUserInRaml(const char* username, const char* password);

/**
********************************************************************************
* @brief        AaNetFTPConfigureAddUserInRamlExt(const char* username, const char* password, SAaNetVsftpdOptions* options)
*
* @param[in] username  User name for ftp user
* @param[in] password  Ftp user password
* @param[in] options   Structure containing additional vsftpd options to be set for the user
*
* @return        #EAaNetRet_Ok on success, specific error value otherwise.
*
* @par Description:
* The function adds to the system a new ftp user with ftp root directory set to "/raml".
* User will have read/write access rights to "/raml" and will be chrooted into this directory.
* Additional vsftpd configuration options can be enabled for this user.
*
* @par Errors:
*  - #EAaNetRet_ParmError   Parameters are empty or not in expected format
*  - #EAaNetRet_Error       Add user failed because of underlaying OS error.
*
* @par Restrictions:
*  - This user is only a temporary ftp user. After reset or power cycle it is gone.
*  - The username must not already exist in the system.
*  - The username has to be between #AANET_MIN_USERNAME_LENGTH and #AANET_MAX_USERNAME_LENGTH characters.
*  - The password has to be between #AANET_MIN_PASSWORD_LENGTH and #AANET_MAX_PASSWORD_LENGTH characters.
*
* @par Example:
* @code
* SAaNetVsftpdOptions options;
* AaNetFTPVsftpdOptionsInit(&options);
* options.local_max_rate = 2048;
* options.trans_chunk_size = 512;
*
* EAaNetRet rc = EAaNetRet_Ok;
* rc=AaNetFTPConfigureAddUserInRamlExt("TestUser","mypassword", &options);
* if ( EAaNetRet_Ok != rc ){
*       //error handling;
*     }
* }
* @endcode
*
* @see AaNetFTPConfigureAddUserInRaml()
* @see AaNetFTPConfigureAddUser()
* @see AaNetFTPConfigureAddUserExt()
* @see AaNetFTPConfigureDeleteUser()
* @see AaNetFTPVsftpdOptionsInit()
* @see SAaNetVsftpdOptions
*
*******************************************************************************/
EAaNetRet AaNetFTPConfigureAddUserInRamlExt(const char* username, const char* password, SAaNetVsftpdOptions* options);

/**
*********************************************************************************
* @brief    AaNetFTPConfigureAddUserExt() adds a temporary FTP user account to the system.
* Additional vsftpd configuration options can be enabled for this user.
*
* @param[in] username   name of temporary FTP user
* @param[in] password   password of temporary FTP user
* @param[in] rootdir    root directory of FTP user, specified as system (Linux) path
* @param[in] options    structure containing additional vsftpd options to be set for the user
*
* @return   #EAaNetRet_Ok on success, specific error value otherwise.
*
* @par Description
* This function adds temporary FTP user to the system, with given username, password and working directory.
* Path to working directory must be specified as system (Linux) path and it is used as jail directory.
* The last parameter is the pointer to a structure containing additional vsftpd configuration options.
* It has to be initialized first, and appropriate parameters have to be stored in it (see example).
* Upon creation of the user, options specified in the options structure are written to /etc/vsftpd.d/<username>.
*
* @par
* This function acts similar to AaNetFTPConfigureAddUser(). If the username is "anonymous" and the working
* directory is "/raml", then anonymous user with empty password and with write access to /raml is created.
*
* @par Errors:
*  - #EAaNetRet_ParmError   Invalid parameters (NULL pointers or username/password do not meet requirements)
*  - #EAaNetRet_Error       Adding user failed because of underlaying OS error.
*
* @par Restrictions:
*  - Working directory must be specified as a system (Linux) path. AaFile path notation is not used.
*  - This user account is only temporary: after reset or power cycle it is gone.
*  - The username must not already exist in the system.
*  - The username has to be between #AANET_MIN_USERNAME_LENGTH and #AANET_MAX_USERNAME_LENGTH characters.
*  - The password has to be between #AANET_MIN_PASSWORD_LENGTH and #AANET_MAX_PASSWORD_LENGTH characters.
*
* @par Example:
* @code
*   SAaNetVsftpdOptions options;
*   AaNetFTPVsftpdOptionsInit(&options);
*
*   options.local_max_rate = 2048;
*   options.trans_chunk_size = 512;
*
*   if( EAaNetRet_Ok != AaNetFtpConfigureAddUserExt("username", "password", "/tmp", &options) )
*   {
*       // error handling
*   }
* @endcode
*
* @see AaNetFTPConfigureAddUser()
* @see AaNetFTPConfigureAddUserInRaml()
* @see AaNetFTPConfigureDeleteUser()
* @see AaNetFTPVsftpdOptionsInit()
* @see SAaNetVsftpdOptions
*
******************************************************************************/
EAaNetRet AaNetFTPConfigureAddUserExt( const char* username,
                                       const char* password,
                                       const char* rootdir,
                                       SAaNetVsftpdOptions* options );

/**
********************************************************************************
* @brief        AaNetFTPConfigureDeleteUser(const char* username);
*
* @param[in] username              Username for ftp user to be removed
*
* @return        #AaNetRetOk on success, specific error value otherwise
*
* @par Description:
* The function removes from the system an ftp user earlier created with AaNetFTPConfigureAddUser().
* or related APIs. Active FTP sessions of that user will remain until the session is terminated.
*
* @par Errors:
* @return #AaNetRetParmError   Parameters are empty or not in expected format
* @return #AaNetRetError       Adduser failed because of underlaying OS error.

* @par Restrictions:
* This is for LTE 150. Only customer is BTSOM.
* Only users created wiht AaNetFTPConfigureAddUser() and related APIs can be removed
* The \p username has to be at least 4 characters long.
*
* @par Example:
* @code
* EAaNETStatus rc;
* rc=AaNetFTPConfigureDeleteUser("TestUser");
* if ( rc!=AaNetRetOk)   {
*     switch(rc){
*         AaNetRetParmError: printf("Parameter error. Please check username");
*                            break;
*         AaNetRetError:     printf("Underlaying OS could not perform requested action.");
*                            break;
*     }
* }
* @endcode
*
* @see AaNetFTPConfigureAddUser()
* @see AaNetFTPConfigureAddUserInRaml()
* @see AaNetFTPConfigureAddUserExt()
*
*******************************************************************************/
EAaNETStatus AaNetFTPConfigureDeleteUser(const char* username);

/**
********************************************************************************
* @brief        AaNetUserChangePassword(const char *username, const char *oldPassword, const char *newPassword);
*
* @param[in] username              Pointer to name of user whose password will be changed
* @param[in] oldPassword           Pointer to old user password in clear text
* @param[in] newPassword           Pointer to new user password in clear text
*
* @return        #AaNetRetOk on success, specific error value otherwise
*
* @par Description:
* The function changes user password.
* Parameter oldPassword can be NULL and then oldPassword will not be checked with existing user password.
*
* @par Errors:
* @return #AaNetRetParmError       Parameters are empty or not in expected format.
* @return #AaNetRetWrongUser       User not exists in system.
* @return #AaNetRetWrongPassword   Old user password does not match.
* @return #AaNetRetError           Change user password failed because of underlaying OS error.
*
* @par Restrictions:
*  - This is for LTE1030.
*  - \p password has to be between #AANET_MIN_PASSWORD_LENGTH and #AANET_MAX_PASSWORD_LENGTH characters.
*  - Password change is allowed only for user accounts #AANET_BTS_SERVICE_ACCOUNT_NAME and
*    #AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME.
*
* @par Example:
* @code
* EAaNETStatus rc;
* rc = AaNetUserChangePassword(AANET_BTS_SERVICE_ACCOUNT_NAME, "OldPassword", "NewPassword");
* if ( AaNetRetOk != rc )   {
*     switch(rc){
*         AaNetRetParmError:      AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Parameter error. Please check username");
*                                 break;
*         AaNetRetWrongUser:      AaSysLogPrint(EAaSysLogSeverityLevel_Error, "No such user in system. Please check username");
*                                 break;
*         AaNetRetWrongPassword:  AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Old password not match. Please check oldPassword");
*                                 break;
*         AaNetRetError:          AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Underlaying OS could not perform requested action.");
*                                 break;
*     }
* }
* @endcode
*
* @see AANET_BTS_SERVICE_ACCOUNT_NAME
* @see AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME
* @see AaNetUserChangePasswordVerbose()
* @see AaNetUserResetPassword()
*
*******************************************************************************/
EAaNETStatus AaNetUserChangePassword(const char *username, const char *oldPassword, const char *newPassword);

/**
********************************************************************************
* @brief        AaNetUserChangePasswordVerbose(const char *username, const char *oldPassword, const char *newPassword, char **err_msg);
*
* @param[in]  username              Pointer to name of user whose password will be changed.
* @param[in]  oldPassword           Pointer to old user password in plain text.
* @param[in]  newPassword           Pointer to new user password in plain text.
* @param[out] err_msg               Pointer to PAM error message buffer - needs to be freed after usage.
*
* @return
*  - AaNetRetOk on success, specific error value otherwise.
*
* @par Description:
* The function changes user password.
* Parameter oldPassword can be NULL and then oldPassword will not be checked with existing user password.
*
* @par Errors:
*  - AaNetRetParmError            Parameters are empty or not in expected format.
*  - AaNetRetWrongUser            User not exists in system.
*  - AaNetRetWrongPassword        Old user password does not match.
*  - AaNetRetError                Change user password failed because of underlaying OS error.
*  - AaNetRetPasswdValidationlErr PAM module return general problem with changing password.
*
* @par Restrictions:
*  - \p password has to be between #AANET_MIN_PASSWORD_LENGTH and #AANET_MAX_PASSWORD_LENGTH characters.
*  - Password change is allowed only for user accounts #AANET_BTS_SERVICE_ACCOUNT_NAME and
*    #AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME.
*
* @par Example:
* @code
* EAaNETStatus rc;
* char *err_msg = GLO_NULL;
* rc = AaNetUserChangePasswordVerbose(AANET_BTS_SERVICE_ACCOUNT_NAME, "OldPassword", "NewPassword", &err_msg);
* if ( AaNetRetOk != rc ) {
*     switch(rc){
*         AaNetRetParmError:
*             AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Parameter error. Please check username");
*             break;
*         AaNetRetWrongUser:
*             AaSysLogPrint(EAaSysLogSeverityLevel_Error, "No such user in system. Please check username");
*             break;
*         AaNetRetWrongPassword:
*             AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Old password not match. Please check oldPassword");
*             break;
*         AaNetRetError:
*             AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Underlaying OS could not perform requested action.");
*             break;
*         AaNetRetPasswdValidationErr:
*             AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Cannot change password because of password policy problem.");
*             break;
*     }
* }
* if ( GLO_NULL != err_msg)
* {
*    AaMemUnRef((void const **)&err_msg);
* }
* @endcode
*
* @par Rationale:
* LTE2486-B
*
* @see AANET_BTS_SERVICE_ACCOUNT_NAME
* @see AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME
* @see AaNetUserChangePassword()
* @see AaNetUserResetPassword()
*
*******************************************************************************/
EAaNETStatus AaNetUserChangePasswordVerbose(const char *username, const char *oldPassword, const char *newPassword, char **err_msg);

/**
*********************************************************************************
* @brief    AaNetUserResetPassword(const char* username) resets user password to the default value.
*
* @param[in]    username    reset the password of this user
*
* @return   #EAaNetRet_Ok on success, specific error value otherwise.
*
* @par Description:
* This function resets the password of a given user to its default,
* which is the password shipped with the rootfs.
*
* @par Errors:
*  - #EAaNetRet_ParmError   Invalid parameter (e.g. NULL pointer) was passed as an argument.
*  - #EAaNetRet_WrongUser   Password reset for unsupported user was requested.
*  - #EAaNetRet_Error       Failed to reset password.
*
* @par Restrictions:
* This function supports resetting passwords only for accounts
* #AANET_BTS_SERVICE_ACCOUNT_NAME and #AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME.
*
* @par Example:
* @code
  EAaNetRet result = AaNetUserResetPassword(AANET_BTS_SERVICE_ACCOUNT_NAME);
  if( EAaNetRet_Ok != result ) {
      // handle error
  }
  @endcode
*
* @par Rationale:
* LTE2647-A-f1
*
* @see AaNetUserChangePassword()
* @see AaNetUserChangePasswordVerbose()
* @see AaNetUserResetSshKeys()
* @see #AANET_BTS_SERVICE_ACCOUNT_NAME
* @see #AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME
*
******************************************************************************/
EAaNetRet AaNetUserResetPassword(const char* username);

/**
********************************************************************************
* @brief AaNetUserChangePasswordHistory(u32 historyLen);
*
* @param[in] historyLen     number of passwords to be stored in the history.
*
* @return
* #AaNetRetOk on success, specific error value otherwise.
*
* @par Description:
* The function changes amount of passwords stored in history.
* If historyLen is set to 0, password history policy check will be deactivated.
*
* @par Errors:
* - #AaNetRetError                Change amount of stored passwords in history failed.
*
* @par Restrictions:
* The historyLen could be at maximum AANET_MAX_PASS_HISTORY_LENGTH.
* If it will be greater, then it is internally set to AANET_MAX_PASS_HISTORY_LENGTH.
*
* @par Example:
* @code
* EAaNETStatus rc;
* rc = AaNetUserChangePasswordHistory(10);
*
* if ( AaNetRetOk != rc ){
*     switch(rc){
*         AaNetRetError:
*             AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Change amount of stored passwords in history failed");
*             break;
*     }
* }
* @endcode
*
* @par Rationale:
* LTE2486-B
*
* @see AANET_MAX_PASS_HISTORY_LENGTH
*
*******************************************************************************/
EAaNETStatus AaNetUserChangePasswordHistory(u32 historyLen);

/**
********************************************************************************
* @brief        AaNetUserStoreSshKeys(const char* username, const u32 numberOfKeys, const SAaNetUserSshKey keys[]);
*
* @param[in]   username        Pointer to username for which keys will be stored
* @param[in]   numberOfKeys    Number of keys to be stored
* @param[in]   keys[]          Array of ssh keys
*
* @return        #AaNetRetOk on success, specific error value otherwise
*
* @par Description:
* The function stores SSH keys to user's authorized keys file <tt>$HOME/.ssh/authorized_keys</tt>.
* If parameter \p username is NULL then keys are stored for #AANET_BTS_SERVICE_ACCOUNT_NAME.
* If parameter \p numberOfKeys is 0 then \c authorized_keys file of specified user is removed.
*
* @par Errors:
* @return #AaNetRetParmError   Parameters are empty or not in expected format.
* @return #AaNetRetWrongUser   User not exists in system.
* @return #AaNetRetError       Store keys failed because of underlaying OS error.
*
* @par Restrictions:
* This is for LTE1030.
* If \p username is not NULL it has to be between #AANET_MIN_USERNAME_LENGTH
* and #AANET_MAX_USERNAME_LENGTH characters.
*
* @par Example:
* @code
* EAaNETStatus rc;
* u32 numberOfKeys = 2;
* SAaNetUserSshKey keys[numberOfKeys];
* keys[0].key = "Ssh key 1 in plain text";
* keys[0].description = "Descryption of Ssh key 1";
* keys[1].key = "Ssh key 2 in plain text";
* keys[1].description = "Descryption of Ssh key 2";
*
* rc=AaNetUserStoreSshKeys("TestUser", numberOfKeys, keys);
* if ( AaNetRetOk != rc ) {
*     switch(rc) {
*        AaNetRetParmError: AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Parameter error. Please check username");
*                           break;
*        AaNetRetWrongUser: AaSysLogPrint(EAaSysLogSeverityLevel_Error, "No such user in system. Please check username");
*                           break;
*        AaNetRetError:     AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Underlaying OS could not perform requested action.");
*                           break;
*       }
* }
* @endcode
*
* @see AaNetUserResetSshKeys()
*
*******************************************************************************/
EAaNETStatus AaNetUserStoreSshKeys(const char* username, const u32 numberOfKeys, const SAaNetUserSshKey keys[]);

/**
*********************************************************************************
* @brief    AaNetUserResetSshKeys(const char* username) resets user SSH keys to the default value.
*
* @param[in]    username    reset the SSH keys of this user
*
* @return   #EAaNetRet_Ok on success, specific error value otherwise.
*
* @par Description:
* This function resets the SSH keys of a given user to the default key,
* which is the key shipped with the rootfs.
*
* @par Errors:
*  - #EAaNetRet_ParmError   Invalid parameter (e.g. NULL pointer) was passed as an argument.
*  - #EAaNetRet_WrongUser   SSH keys reset of unsupported user was requested.
*  - #EAaNetRet_Error       Failed to reset SSH keys.
*
* @par Restrictions:
* This function supports resetting SSH keys only for accounts
* #AANET_BTS_SERVICE_ACCOUNT_NAME and #AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME.
*
* @par Example:
* @code
  EAaNetRet result = AaNetUserResetSshKeys(AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME);
  if( EAaNetRet_Ok != result ) {
      // handle error
  }
  @endcode
*
* @par Rationale:
* LTE2647-A-f1
*
* @see AaNetUserStoreSshKeys()
* @see AaNetUserResetPassword()
* @see #AANET_BTS_SERVICE_ACCOUNT_NAME
* @see #AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME
*
******************************************************************************/
EAaNetRet AaNetUserResetSshKeys(const char* username);

/**
*********************************************************************************
* @brief    Checks if default password for specified user is set
*
* @param[in]    username           user for which password will be checked
* @param[out]   isPasswordDefault  password information: GLO_TRUE if password is default,
*                                                        GLO_FALSE otherwise
*
* @return   #EAaNetRet_Ok on success, specific error value otherwise.
*
* @par Description:
* This function checks if user given by \p username has default password. This function will
* modify \p isPasswordDefault value only if #EAaNetRet_Ok is returned. In case of any error
* the value will remain unchanged.
*
* @par Errors:
*  - #EAaNetRet_ParmError   Invalid parameter (e.g. NULL pointer) was passed as an argument.
*  - #EAaNetRet_WrongUser   Password checking of unsupported user was requested.
*  - #EAaNetRet_Error       Failed to check if password is default.
*
* @par Restrictions:
* This function supports password checking only for accounts
* #AANET_BTS_SERVICE_ACCOUNT_NAME and #AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME.
*
* @par Example:
* @code
* TBoolean isPasswordDefault;
* EAaNetRet result = AaNetUserCheckDefaultPassword(AANET_BTS_SERVICE_ACCOUNT_NAME, &isPasswordDefault);
* if( EAaNetRet_Ok == result ) {
*     if( GLO_TRUE == isPasswordDefault ) {
*     // password is default
*     }
* } else {
*     // handle error
* }
* @endcode
*
* @par Rationale:
* RP001543_1_FC1
*
* @see AaNetUserChangePassword()
* @see AaNetUserResetPassword()
* @see #AANET_BTS_SERVICE_ACCOUNT_NAME
* @see #AANET_BTS_UNPRIVILEGED_SERVICE_ACCOUNT_NAME
*
******************************************************************************/
EAaNetRet AaNetUserCheckDefaultPassword(const char* username, TBoolean* isPasswordDefault);

/**
********************************************************************************
* @brief       AaNetSshConfigureClientAliveTime(const u32 clientAliveTime);
*
* @param[in]   clientAliveTime       SSH session inactivity time in minutes.
*
* @return      #AaNetRetOk on success, specific error value otherwise
*
* @par Description:
* The function changes client alive timer in ssh daemon.
* After successful change ssh daemon is restarted.
*
* @par Errors:
* @return #AaNetRetParmError   Parameters are empty or not in expected format.
* @return #AaNetRetError       Configure sshd failed because of underlaying OS error.
*
* @par Restrictions:
* This is for LTE1030.
*
* @par Example:
* @code
* EAaNETStatus rc;
* rc=AaNetSshConfigureClientAliveTime(5);
* if ( AaNetRetOk != rc )   {
      switch(rc){
        AaNetRetParmError: AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Parameter error.");
                           break;
        AaNetRetError:     AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Underlaying OS could not perform requested action.");
                           break;
       }
   }
* @endcode
*
* @see AaNetSshConfigureDelayTime()
*
*******************************************************************************/
EAaNETStatus  AaNetSshConfigureClientAliveTime(const u32 clientAliveTime);

/**
********************************************************************************
* @brief       AaNetSshConfigureDelayTime(const u32 delayTime);
*
* @param[in]   delayTime       SSH session login delay time in seconds.
*
* @return      #AaNetRetOk on success, specific error value otherwise
*
* @par Description:
* The function changes delay timer in a pluggable authentication module (PAM).
*
* @par Errors:
* @return #AaNetRetParmError   Parameters are empty or not in expected format.
* @return #AaNetRetError       Configure PAM failed because of underlaying OS error.
*
* @par Restrictions:
* This is for LTE1030.
*
* @par Example:
* @code
* EAaNETStatus rc;
* rc=AaNetSshConfigureDelayTime(30);
* if ( AaNetRetOk != rc )   {
      switch(rc){
        AaNetRetParmError: AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Parameter error.");
                           break;
        AaNetRetError:     AaSysLogPrint(EAaSysLogSeverityLevel_Error, "Underlaying OS could not perform requested action.");
                           break;
       }
   }
* @endcode
*
* @see AaNetSshConfigureClientAliveTime()
*
*******************************************************************************/
EAaNETStatus  AaNetSshConfigureDelayTime(const u32 delayTime);

/**
********************************************************************************
* @brief       AaNetSshSetBanner(const char* text);
*
* @param[in]   text         SSH login banner text.
*
* @return      #AaNetRetOk on success, specific error value otherwise.
*
* @par Description:
* The function sets ssh login banner text. The login banner text is displayed
* to the user along with the login prompt.
*
* @par Errors:
* @return #AaNetRetParmError   Parameter is empty or exceeds AANET_MAX_SSH_BANNER_TEXT_LENGTH bytes.
* @return #AaNetRetError       Internal underlying OS error.

* @par Restrictions:
* Banner text length should not exceed AANET_MAX_SSH_BANNER_TEXT_LENGTH bytes.
*
* @par Example:
* @code
* EAaNETStatus rc  = EAaNETStatus_Ok;
* const char* newText = "This is test ssh banner text";
* rc=AaNetSshSetBanner(newText);
* if ( AaNetRetOk != rc )   {
      AaSysLogPrintE(EAaSysLogSeverityLevel_Error, ERadCcs_PrintAaNet,
                    ("%s, AaNetSshSetBanner failed, rc=%d", __FUNCTION__, rc);
   }
* @endcode
*
*******************************************************************************/
EAaNETStatus  AaNetSshSetBanner(const char* text);

/**
*********************************************************************************
* @brief    AaNetRestrictedRootAccessEnable(void) enables Restricted Root Access.
*
* @return   #EAaNetRet_Ok on success, #EAaNetRet_Error otherwise.
*
* @par Description:
* This function enables the Restricted Root Access (also known as two-step login)
* in the platform.
*
* @par Errors:
*  - #EAaNetRet_Error   Failed to enable Restricted Root Access.
*
* @par Example:
* @code
  EAaNetRet result = AaNetRestrictedRootAccessEnable();
  if( EAaNetRet_Ok != result ) {
      // handle error
  }
  @endcode
*
* @par Rationale:
* LTE2647-A-c1
*
* @see AaNetRestrictedRootAccessDisable()
*
******************************************************************************/
EAaNetRet AaNetRestrictedRootAccessEnable(void);

/**
*********************************************************************************
* @brief    AaNetRestrictedRootAccessDisable(void) disables Restricted Root Access.
*
* @return   #EAaNetRet_Ok on success, #EAaNetRet_Error otherwise.
*
* @par Description:
* This function disables the Restricted Root Access (also known as two-step login)
* in the platform.
*
* @par Errors:
*  - #EAaNetRet_Error   Failed to disable Restricted Root Access.
*
* @par Example:
* @code
  EAaNetRet result = AaNetRestrictedRootAccessDisable();
  if( EAaNetRet_Ok != result ) {
      // handle error
  }
  @endcode
*
* @par Rationale:
* LTE2647-A-c1
*
* @see AaNetRestrictedRootAccessEnable()
*
******************************************************************************/
EAaNetRet AaNetRestrictedRootAccessDisable(void);

/**
 ********************************************************************************
 * @brief Starts the http server.
 *
 * @param[in]   serverRootDir   root directory of the http server, specified as system (Linux) path
 * @param[in]   serverPort      listen port of the http server
 * @param[in]   securityMode    security mode (plain text or TLS enabled)
 *
 * @returns #EAaNetRet_Ok when server is successfully started, appropriate error otherwise.
 *
 * @par Description
 * This function starts the http server. Files are served from serverRootDir. The path to server
 * root directory must be specified as system (Linux) path (AaFile path notation is not used).
 * If port number is 0, the server listens on a default port: 80 in plain text mode, 443 in TLS mode.
 *
 * @par Errors:
 *  - #EAaNetRet_ParmError          Invalid parameters (NULL pointers, etc.) were passed to the function.
 *  - #EAaNetRet_AlreadyStarted     Http server is already running.
 *  - #EAaNetRet_Error              Failed to start the http server.
 *
 * @par Restrictions:
 *  - Http server must not be already running.
 *  - Path to server root directory is specified as system (Linux) path.
 *  - Server root directory must have read and write access for user btssw in group btssw.
 *  - Maximum port number is 65535. Applications without root priviliges cannot bind to ports 0-1023.
 *
 * @par Example
 * @code
   EAaNetRet result = AaNetHttpEnableServer("/tmp/srv/http/", 50443, EAaNetHttpSecurityMode_Tls);

   if( EAaNetRet_Ok != result ) {
       // handle error
   }
   @endcode
 *
 * @see EAaNetHttpSecurityMode
 * @see AaNetHttpDisableServer()
 * @see AaNetHttpAddUser()
 * @see AaNetHttpDeleteUser()
 *
 *******************************************************************************/
EAaNetRet AaNetHttpEnableServer( const char *serverRootDir,
                                 u32 serverPort,
                                 EAaNetHttpSecurityMode securityMode );

/**
 ********************************************************************************
 * @brief Stops the http server.
 *
 * @returns #EAaNetRet_Ok when server is successfully stopped, appropriate error otherwise.
 *
 * @par Description
 * This function stops the http server.
 *
 * @par Errors:
 *  - #EAaNetRet_NotStarted     Http server is not started.
 *  - #EAaNetRet_Error          Failed to stop the http server.
 *
 * @par Restrictions:
 * Http server must be already started.
 *
 * @par Example
 * @code
   EAaNetRet result = AaNetHttpDisableServer();

   if( EAaNetRet_Ok != result ) {
       // handle error
   }
   @endcode
 *
 * @see AaNetHttpEnableServer()
 * @see AaNetHttpAddUser()
 * @see AaNetHttpDeleteUser()
 *
 *******************************************************************************/
EAaNetRet AaNetHttpDisableServer( void );

/**
 ********************************************************************************
 * @brief Adds user of http server.
 *
 * @param[in]   username    user login
 * @param[in]   password    user password
 *
 * @returns #EAaNetRet_Ok on successful user creation, appropriate error otherwise.
 *
 * @par Description
 * This function adds user of http server, with given username and password.
 *
 * @par Errors:
 *  - #EAaNetRet_ParmError      Invalid parameters (NULL pointers, etc.) were given to the function.
 *  - #EAaNetRet_AlreadyStarted It is not allowed to add users when server is already running.
 *  - #EAaNetRet_WrongUser      Username already exists, or doesn't meet length requirements.
 *  - #EAaNetRet_WrongPassword  Password doesn't meet length requirements.
 *  - #EAaNetRet_Error          Failed to add user.
 *
 * @Par Restrictions:
 *  - The http server must not be started.
 *  - The username must not already exist in the system.
 *  - The username has to be between #AANET_MIN_USERNAME_LENGTH and #AANET_MAX_USERNAME_LENGTH characters.
 *  - The password has to be between #AANET_MIN_PASSWORD_LENGTH and #AANET_MAX_PASSWORD_LENGTH characters.
 *
 * @par Example
 * @code
   EAaNetRet result = AaNetHttpAddUser("httpUser", "httpPassword");

   if( EAaNetRet_Ok != result ) {
       // handle error
   }
   @endcode
 *
 * @see AaNetHttpEnableServer()
 * @see AaNetHttpDisableServer()
 * @see AaNetHttpDeleteUser()
 *
 *******************************************************************************/
EAaNetRet AaNetHttpAddUser( const char *username,
                            const char *password );

/**
 ********************************************************************************
 * @brief Deletes user of http server.
 *
 * @param[in]   username    user login
 *
 * @returns #EAaNetRet_Ok on successful user deletion, appropriate error otherwise.
 *
 * @par Description
 * This function deletes given user of http server.
 *
 * @par Errors:
 *  - #EAaNetRet_ParmError      Invalid parameter (NULL pointer, etc.) was given to the function.
 *  - #EAaNetRet_AlreadyStarted It is not allowed to remove users when server is already running.
 *  - #EAaNetRet_WrongUser      User with that name doesn't exist, or is "root" or #AANET_BTS_SERVICE_ACCOUNT_NAME.
 *  - #EAaNetRet_Error          Failed to delete user.
 *
 * @par Restrictions:
 *  - The http server must not be started.
 *  - The http user account must already exist.
 *  - The username cannot be "root" or #AANET_BTS_SERVICE_ACCOUNT_NAME.
 *
 * @par Example
   EAaNetRet result = AaNetHttpDeleteUser("httpUser");

   if( EAaNetRet_Ok != result ) {
       // handle error
   }
 *
 * @see AaNetHttpEnableServer()
 * @see AaNetHttpDisableServer()
 * @see AaNetHttpAddUser()
 *
 *******************************************************************************/
EAaNetRet AaNetHttpDeleteUser( const char *username );

/** @} */


#ifdef __cplusplus
}
#endif

#endif /* _MCU_IF_AANET_H_ */
