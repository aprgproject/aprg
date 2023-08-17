/** @file
*   @brief AaFileFtpClient shared MCU/RT function prototypes.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright 2017, 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_RT_IF_AAFILEFTPCLIENT_H_
#define _MCU_RT_IF_AAFILEFTPCLIENT_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include "../Definitions/IfAaFileFtpClient_Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaFileApiMcu
 * @ingroup    dgAaFile
 */

/** @{ */

/**
******************************************************************************
*
*   @brief      AaFileFtpClientInit  Initialize usage of FTP-client
*
*   @return     #EAaFileFtpClientRet_Ok on success, specific error value otherwise
*
*   @par Description:
*   Initialize usage of FTP-client. There are some internal values that must be
*   set and initialized. Therefore this function must be called once for every
*   process (EE) accessing FTP-client's API-functions.
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*    EAaFileFtpClientRet retval = EAaFileRet_UndefinedError;
*    if ((retval = AaFileFtpClientInit()) != EAaFileFtpClientRet_Ok) {
*        switch (retval) {
*        case EAaFileFtpClientRet_UndefinedError : printf("FTP-client initialization failed"); break;
*        ...
*        }
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
EAaFileFtpClientRet AaFileFtpClientInit(void);

/**
******************************************************************************
*   @brief Establish connection with FTP server on the default FTP port (21),
*          or on the port specified by #AAFILE_FTP_CLIENT_CONFIG_TAG_SERVER_PORT
*          configuration tag.
*
*   @param[out] sessionId Pointer to a session ID returned if connection is established.
*   @param[in]  server    Pointer to a null-terminated string containing the IP address of FTP server.
*   @param[in]  user      Pointer to a null-terminated string containing user name for FTP server.
*   @param[in]  password  Pointer to a null-terminated string containing password for FTP server.
*   @param[in]  mode      Specifies active or passive transfer mode for FTP session.
*
*   @return     #EAaFileFtpClientRet_Ok and #TAaFileFtpClientSessionId on success,
*               appropriate #EAaFileFtpClientRet values on error.
*
*   @par Description:
*   This function establishes a connection with the desired FTP server using provided
*   login credentials. \p server argument can be either IPv4 or IPv6 address. The connection
*   is established either on the default FTP port (21), or on the port specified by the
*   #AAFILE_FTP_CLIENT_CONFIG_TAG_SERVER_PORT configuration tag. The function returns
*   a session ID that must be used for all further operations on this connection.
*
*   @par Errors:
*    - #EAaFileFtpClientRet_AlreadyOpen            There is already an existing FTP connection established with this session ID
*    - #EAaFileFtpClientRet_MaxNumOfFtpSessions    Maximum number of parallel FTP sessions achieved
*    - #EAaFileFtpClientRet_CurlInitError          Error during initialization of \c curl library
*    - #EAaFileFtpClientRet_InvalidTransferMode    Specified transfer mode is invalid
*    - #EAaFileFtpClientRet_ServerNotGiven         Specified FTP server address given is invalid
*    - #EAaFileFtpClientRet_AddressTooLong         Specified URL exceeds internal buffer size
*    - #EAaFileFtpClientRet_CurlError              \c curl library error, see AaSysLog output for details
*    - #EAaFileFtpClientRet_NoAnonymousAccess      Anonymous FTP server access is prohibited
*    - #EAaFileFtpClientRet_UserPwdLenTooLong      Length of concatenated username and password exceeds internal buffer size
*
*   @par Restrictions:
*   The length of server argument must not exceed #AAFILE_FTP_CLIENT_URL_LEN bytes.
*   IPv6 addresses must not contain zone ID suffix (e.g. \%eth0). In these cases the
*   function will return #EAaFileFtpClientRet_ServerNotGiven. IPv6 is only supported
*   by MCU implementation.
*
*   @par Example:
*   @code
*   EAaFileFtpClientRet retval = EAaFileRet_UndefinedError;
*   TAaFileFtpClientSessionId sessionId;
*   char* ftpserver = "192.168.255.1";
*   char* user = "ftpuser";
*   char* password = "verysecretpassword";
*
*   retval = AaFileFtpClientOpen(&sessionId,
*                                ftpserver,
*                                user, password
*                                EAaFileFtpClientTransferModePassive);
*   if( EAaFileFtpClientRet_Ok != retval ) {
*       switch (retval) {
*           // handle errors
*       }
*   }
*   ...
*   @endcode
*
*   @par Rationale:
*   RAN3217, LTE4537-B-k5
*
*   @see AAFILE_FTP_CLIENT_URL_LEN
*   @see AAFILE_FTP_CLIENT_CONFIG_TAG_SERVER_PORT
*   @see EAaFileFtpClientTransferMode
*   @see AaFileFtpClientOpenWithPort()
*   @see AaFileFtpRemoteClientOpenWithPort()
******************************************************************************/
EAaFileFtpClientRet AaFileFtpClientOpen( TAaFileFtpClientSessionId* sessionId,
                                         const char* server,
                                         const char* user,
                                         const char* password,
                                         EAaFileFtpClientTransferMode mode );

/**
******************************************************************************
*   @brief Establish connection with FTP server listening on a specified port.
*
*   @param[out] sessionId Pointer to a session ID returned if connection is established.
*   @param[in]  server    Pointer to a null-terminated string containing the IP address of FTP server.
*   @param[in]  port      The listening port of the FTP server.
*   @param[in]  user      Pointer to a null-terminated string containing user name for FTP server.
*   @param[in]  password  Pointer to a null-terminated string containing password for FTP server.
*   @param[in]  mode      Specifies active or passive transfer mode for FTP session.
*
*   @return     #EAaFileFtpClientRet_Ok and #TAaFileFtpClientSessionId on success,
*               appropriate #EAaFileFtpClientRet values on error.
*
*   @par Description:
*   This function establishes a connection with the desired FTP server on a given \p port
*   using provided login credentials. \p server argument can be either IPv4 or IPv6 address.
*   The function returns a session ID that must be used for all further operations on this
*   connection.
*
*   @par Errors:
*    - #EAaFileFtpClientRet_AlreadyOpen            There is already an existing FTP connection established with this session ID
*    - #EAaFileFtpClientRet_MaxNumOfFtpSessions    Maximum number of parallel FTP sessions achieved
*    - #EAaFileFtpClientRet_CurlInitError          Error during initialization of \c curl library
*    - #EAaFileFtpClientRet_InvalidTransferMode    Specified transfer mode is invalid
*    - #EAaFileFtpClientRet_ServerNotGiven         Specified FTP server address given is invalid
*    - #EAaFileFtpClientRet_AddressTooLong         Specified URL exceeds internal buffer size
*    - #EAaFileFtpClientRet_CurlError              \c curl library error, see AaSysLog output for details
*    - #EAaFileFtpClientRet_NoAnonymousAccess      Anonymous FTP server access is prohibited
*    - #EAaFileFtpClientRet_UserPwdLenTooLong      Length of concatenated username and password exceeds internal buffer size
*
*   @par Restrictions:
*   The length of server argument must not exceed #AAFILE_FTP_CLIENT_URL_LEN bytes.
*   IPv6 addresses must not contain zone ID suffix (e.g. \%eth0). In these cases the
*   function will return #EAaFileFtpClientRet_ServerNotGiven. IPv6 is only supported
*   by MCU implementation.
*
*   @par Example:
*   @code
*	TAaFileFtpClientRet retval = EAaFileRet_UndefinedError;
*	TAaFileFtpClientSessionId sessionId;
*   char* ftpserver = "192.168.255.1";
*   u32 port = 15400;
*   char* user = "ftpuser";
*   char* password = "verysecretpassword";
*
*   retval = AaFileFtpClientOpenWithPort(&sessionId,
*                                        ftpserver, port,
*                                        user, password,
*                                        EAaFileFtpClientTransferModePassive);
*   if( EAaFileFtpClientRet_Ok != retval ) {
*       switch (retval) {
*           // handle errors
*       }
*   }
*   ...
*   @endcode
*
*   @par Rationale:
*   RAN3217, LTE4537-B-k5
*
*   @see AAFILE_FTP_CLIENT_URL_LEN
*   @see EAaFileFtpClientTransferMode
*   @see AaFileFtpClientOpen()
*   @see AaFileFtpRemoteClientOpenWithPort()
******************************************************************************/
EAaFileFtpClientRet AaFileFtpClientOpenWithPort( TAaFileFtpClientSessionId* sessionId,
                                                 const char* server,
                                                 u32 port,
                                                 const char* user,
                                                 const char* password,
                                                 EAaFileFtpClientTransferMode mode );

/**
******************************************************************************
*
*   @brief    AaFileFtpClientClose Close FTP-connection
*
*   @param[in]  sessionId FTP-client session id
*
*   @return     #EAaFileFtpClientRet_Ok on success, specific error value otherwise
*
*   @par Description:
*   Call this function to close an established FTP-connection.
*
*   @note
*   The function works for local and remote session types.
*
*   @par Errors:
*   #AaFileFtpClientClose will return the following values:
*   #EAaFileFtpClientRet_InvalidSession         Invalid session-Id given; perhaps session not openend
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*       EAaFileFtpClientRet retval = EAaFileRet_UndefinedError;
*       TAaFileFtpClientSessionId sessionId;
*       ...
*       if ((retval = AaFileFtpClientClose( sessionId)) != EAaFileFtpClientRet_Ok) {
*           switch (retval) {
*               ...
*           }
*       }
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
EAaFileFtpClientRet AaFileFtpClientClose( TAaFileFtpClientSessionId sessionId);

/**
******************************************************************************
*
*   @brief    AaFileFtpClientPut Store a file on the remote ftp server
*
*   @param[in]  sessionId     FTP-client session ID.
*   @param[in]  srcFilePath   Pointer to string that contains the source path
*                             (this is the local file and therefore required to be conform to AaFile Path Notation)
*                             In case of remote session srcFilePath concerns remote node path where AaFileFtpClientProxy resides.
*   @param[in]  destFilePath  Pointer to string that contains the destination path
*                             (this is the remote file and therefore only is bound to file notation of remote OS)
*   @param[in]  transferType  Specifies BINARY or ASCII form of transfer
*
*   @return     #EAaFileFtpClientRet_Ok on success, specific error value otherwise
*
*   @par Description:
*   Store local file identified by the given source-file path at the
*   FTP-server's file-path indicated by the given destination-file path.
*
*   A new file is created at the server site if the file specified in the
*   pathname does not already exist.
*
*   @note
*       - Timeout:<br>
*         A timeout value will be given per default to indicate.
*         It is set by ccs.service.aafile.ftpclient.timeout config tag.
*       - Blocking:<br>
*         This function will block until either the file was successfully sent to the
*         remote side or the timeout will be achieved. If you want to send more than
*         one file to the remote side in parallel you have to launch separate threads
*         (EU's) for this purpose.
*       - URL:<br>
*         The ftp url, which is assembled implicitly for the remote file path, requires
*         that '#' characters are replaced by string "%23". AaFileFtpClientGet() does
*         this implicitly.
*       - The function works for local and remote session types.
*
*   @par Errors:
*
*   #AaFileFtpClientPut will return the following values:
*
*   #EAaFileFtpClientRet_Ok        The demanded operation has succeeded
*
*   #EAaFileFtpClientRet_InvalidSession     Invalid session-Id given; perhaps session not openend
*
*   #EAaFileFtpClientRet_FileNotFound       The source file could not be found at the given path
*                                           on the local node.
*
*   #EAaFileFtpClientRet_FileAlreadyExists  The destination file already exists and must
*                                           be removed separately first.
*
*   #EAaFileFtpClientRet_CurlError          CURL-library error during setting FTP-options,
*                                           for details see AaSysLog-output
*
*   #EAaFileFtpClientRet_AddressTooLong     Given URL exceeds internal buffer size
*
*   #EAaFileFtpClientRet_CurlPerformError   CURL-library error during performing FTP-operation,
*                                           for details see AaSysLog-output
*
*
*   @par Restrictions:
*
*      - Length of the local file name cannot exceed #AAFILE_FILENAME_MAX.
*      - The local file path can only include portable characters, defined in AaFile
*        API documentation.
*      - The FTP-server will limit access to files relative to the given user's
*        home-directory, i.e. a file requested from the FTP-server with
*        srcFilePath "/ram/mydir/srcFilePath.txt" will really rely at the FTP-server
*        to the absolute path "/home/joe/ram/mydir/srcFilePath.txt" if the
*        FTP-connection was established using this username.
*      - In case of remote session srcFilePath concerns remote node path
*        where AaFileFtpClientProxy resides.
*
*   @par Example:
*
*   @code
*
*       TAaFileFtpClientSessionId sessionId;
*       ...
*       EAaFileFtpClientRet retval = EAaFileRet_UndefinedError;
*       char* srcFilePath = "/ram/mydir/srcFilePath.txt";
*       char* destFilePath = "/ram/mydir/destFilePath.txt";
*       if ((retval = AaFileFtpClientPut( sessionId,
*                                         srcFilePath,
*                                         destFilePath,
*                                         EAaFileFtpClientTransferTypeBinary))
*           != EAaFileFtpClientRet_Ok) {
*           switch (retval) {
*               ...
*           }
*       }
*       ...
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
EAaFileFtpClientRet AaFileFtpClientPut( TAaFileFtpClientSessionId sessionId,
                                        const char* srcFilePath,
                                        const char* destFilePath,
                                        EAaFileFtpClientTransferType transferType);

/**
******************************************************************************
*
*   @brief    AaFileFtpClientGet  Transfer remote file to local node
*
*   @param[in]  sessionId     FTP-client session ID.
*   @param[in]  srcFilePath   Pointer to string that contains the source path
*                             (this is the remote file and therefore only is bound to file notation of remote OS).
*   @param[in]  destFilePath  Pointer to string that contains the destination path
*                             (this is the local file and therefore required to be conform to AaFile Path Notation).
*                             In case of remote session destFilePath concerns remote node path where AaFileFtpClientProxy resides.
*   @param[in]  failIfExists  Indicates whether the destination path may already be used by an existing file
*                             (if set an existing destination file won't be overwritten and the function returns
*                              with error in that case).
*   @param[in]  attributes    Indicates the attributes of the local file
*   @param[in]  transferType  Specifies BINARY or ASCII form of transfer
*
*   @return     #EAaFileFtpClientRet_Ok on success, specific error value otherwise
*
*   @par Description:
*   Copy remote file identified by the given source-file path on the FTP-server
*   to the local host's file-path indicated by the given destination-file path.
*
*   @note
*       - Timeout:<br>
*         A timeout value will be given per default to indicate
*         For further details check config tag section.
*       - Blocking:<br>
*         This function will block until either the file was successfully received from
*         the remote side or the timeout will be achieved. If you want to receive more
*         than one file from the remote side in parallel you have to launch separate threads
*         (EU's) for this purpose.
*       - URL:<br>
*         The ftp url, which is assembled implicitly for the remote file path, requires
*         that '#' characters are replaced by string "%23". AaFileFtpClientGet() does
*         this implicitly.
*       - The function works for local and remote session types.
*
*   @par Errors:
*
*   #AaFileFtpClientGet will return the following values:
*
*   #EAaFileFtpClientRet_Ok         The demanded operation has succeeded
*
*   #EAaFileFtpClientRet_InvalidSession     Invalid session-Id given; perhaps session not openend
*
*   #EAaFileFtpClientRet_FileNotFound       The source file could not be found at the given path
*                                           on the local node.
*
*   #EAaFileFtpClientRet_FileAlreadyExists  The destination file already exists and must
*                                           be removed separately first.
*
*   #EAaFileFtpClientRet_FileOpenError      Given destination-file cannot be opened
*
*   #EAaFileFtpClientRet_CurlError          CURL-library error during setting FTP-options,
*                                           for details see AaSysLog-output
*
*   #EAaFileFtpClientRet_AddressTooLong     Given URL exceeds internal buffer size
*
*   #EAaFileFtpClientRet_CurlPerformError   CURL-library error during performing FTP-operation,
*                                           for details see AaSysLog-output
*
*
*   @par Restrictions:
*
*      - Length of the local file name cannot exceed #AAFILE_FILENAME_MAX.
*      - The local file path can only include portable characters, defined in AaFile
*        API documentation.
*      - The FTP-server will limit access to files relative to the given user's
*        home-directory, i.e. a file requested from the FTP-server with
*        srcFilePath "/ram/mydir/srcFilePath.txt" will really rely at the FTP-server
*        to the absolute path "/home/joe/ram/mydir/srcFilePath.txt" if the
*        FTP-connection was established using this username.
*      - The given parameter 'attributes' is currently not used, the OSE-implementation
*        does not use it all.
*      - In case of remote session destFilePath concerns remote node path
*        where AaFileFtpClientProxy resides.
*
*   @par Example:
*
*   @code
*
*       TAaFileFtpClientSessionId sessionId;
*       ...
*       EAaFileFtpClientRet retval = EAaFileRet_UndefinedError;
*       char* srcFilePath = "/ram/mydir/srcFilePath.txt";
*       char* destFilePath = "/ram/mydir/destFilePath.txt";
*       int failIfExists = GLO_TRUE;
*       int attributes = 0;
*
*       retval = AaFileFtpClientGet( sessionId,
*                                    srcFilePath,
*                                    destFilePath,
*                                    failIfExists,
*                                    attributes,
*                                    EAaFileFtpClientTransferTypeBinary);
*       if( EAaFileFtpClientRet_Ok != retval) {
*           switch (retval) {
*               ...
*           }
*       }
*       ...
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
EAaFileFtpClientRet AaFileFtpClientGet( TAaFileFtpClientSessionId sessionId,
                                        const char* srcFilePath,
                                        const char* destFilePath,
                                        int failIfExists,
                                        int attributes,
                                        EAaFileFtpClientTransferType transferType);

/**
******************************************************************************
*
*   @brief    AaFileFtpClientSetCurrentDirectory  Set current working directory
*
*   @param[in]  sessionId FTP-client session id
*
*   @param[in]  directoryName  A pointer to a string containing the name of the
*               directory to change to.
*
*   @return     #EAaFileFtpClientRet_Ok on success, specific error value otherwise
*
*   @par Description:
*   Call this function to change to a different directory on the FTP-server.
*   The given path must be absolute, thus beginning with a '/'-character. This
*   path will be used for all further relative get- and put-actions. If the get- or
*   put-action uses an absolute path either the path of the last ##AaFileFtpClientSetCurrentDirectory
*   call will be ignored.
*
*   @note
*   The function works for local and remote session types.
*
*   @par Errors:
*
*   #AaFileFtpClientSetCurrentDirectory will return the following values:
*
*   #EAaFileFtpClientRet_Ok         The demanded operation has succeeded
*
*   #EAaFileFtpClientRet_InvalidSession     Invalid session-Id given; perhaps session not openend
*
*
*   @par Restrictions:
*
*      - The file path can only include portable characters, defined in AaFile
*        API documentation.
*
*   @par Example:
*
*   @code
*
*       TAaFileFtpClientSessionId sessionId;
*       ...
*       EAaFileFtpClientRet retval = EAaFileRet_UndefinedError;
*       char* path = "/ram/mydir";
*       if ((retval = AaFileFtpClientSetCurrentDirectory( sessionId, path)) != EAaFileFtpClientRet_Ok) {
*           switch (retval) {
*               ...
*           }
*       }
*       ...
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
EAaFileFtpClientRet AaFileFtpClientSetCurrentDirectory( TAaFileFtpClientSessionId sessionId,
                                                        const char* directoryName);

/**
******************************************************************************
*
*   @brief    AaFileFtpClientGetLastFtpError  Get last error of FTP-communication
*
*   @param[in]  sessionId FTP-client session id
*
*   @param[out] lastError Curl-FTP error-code (see curl.h for details)
*
*   @return     #EAaFileFtpClientRet_Ok on success, specific error value otherwise
*
*   @par Description:
*   Get last FTP-error. This is not the last FTP-communication code-number as
*   defined in RFC959 (section "4.2.1  Reply Codes by Function Groups") but the
*   error code returned by the CURL-library-function providing the FTP-transfer.
*
*   @note
*   The function works for local and remote session types.
*
*   @par Errors:
*
*   #AaFileFtpClientGetLastFtpError will return the following values:
*
*   #EAaFileFtpClientRet_Ok         The demanded operation has succeeded
*
*   #EAaFileFtpClientRet_InvalidSession     Invalid session-Id given; perhaps session not openend
*
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*       TAaFileFtpClientSessionId sessionId;
*       ...
*       EAaFileFtpClientRet retval = EAaFileRet_UndefinedError;
*       int lastError = 0;
*       if ((retval = AaFileFtpClientGetLastFtpError( sessionId, &lastError)) != EAaFileFtpClientRet_Ok) {
*           switch (retval) {
*               ...
*           }
*       }
*       ...
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
EAaFileFtpClientRet AaFileFtpClientGetLastFtpError( TAaFileFtpClientSessionId sessionId,
                                                    int* lastError);

/**
******************************************************************************
*   @brief Set additional AaFileFtpClient connection options.
*
*   @param[in]  sessionId FTP client session ID.
*   @param[in]  options   Specifies connection options to be set.
*   @param[in]  optValues Pointer to structure containing values of options to be set.
*
*   @return     #EAaFileFtpClientRet_Ok on success, specific error value otherwise.
*
*   @par Description:
*   This function sets additional FTP connection parameters for a given session ID.
*   Before calling this function an FTP session needs to be already open using one
*   of available AaFileFtpClient APIs. To set the connection parameters a structure
*   of type #SAaFileFtpClientOpt must be created, its fields must be set to the
*   desired values, and a pointer to this structure must be passed to the function.
*   Supported FTP connection options are specified in #EAaFileFtpClientOpt.
*
*   @note
*   The function works for both local and remote session types.
*
*   @par Errors:
*   - #EAaFileFtpClientRet_InvalidSession Invalid session ID given; perhaps session not open
*   - #EAaFileFtpClientRet_InvalidPointer NULL pointer to \p optValues argument was given
*   - #EAaFileFtpClientRet_CurlError      \c curl library error, see SysLog for details
*
*   @par Restrictions:
*   IPv6 link-local addresses (fe80::/10) must not be used as source IP addresses.
*
*   @par Example:
*   @code
    const char* sourceAddress = "192.168.255.7";
    TAaFileFtpClientSessionId sessionId;
    EAaFileFtpClientRet retval = EAaFileRet_UndefinedError;

    // open FTP connection and acquire sessionId

    SAaFileFtpClientOpt options;
    strncpy(options.sourceIP, sourceAddress, AASYSCOM_GW_IP_ADDRESS_MAX_STR_LEN);

    retval = AaFileFtpClientSetOpts(sessionId, EAaFileFtpClientOpt_SourceIP, &options);
    if( EAaFileFtpClientRet_Ok != retval ) {
        // handle errors
    }
    ...
    @endcode
*
*   @par Rationale:
*   LBT3476
*
*   @see EAaFileFtpClientOpt
*   @see SAaFileFtpClientOpt
*   @see AaFileFtpClientOpen()
*   @see AaFileFtpClientOpenWithPort()
******************************************************************************/
EAaFileFtpClientRet AaFileFtpClientSetOpts( TAaFileFtpClientSessionId sessionId,
                                            EAaFileFtpClientOpt options,
                                            const SAaFileFtpClientOpt* const optValues );

/**
******************************************************************************
*   @brief AaFileFtpClientGetSessionType(): determine if FTP client session is local or remote.
*
*   @param[in]  sessionId   FTP client session ID the type of which will be determined.
*   @param[out] sesionType  FTP client session type.
*
*   @return     #EAaFileFtpClientRet_Ok and #TAaFileFtpClientSessionId on success,
*               #EAaFileFtpClientRet values in case of error.
*
*   @par Description:
*   Call this function to determine session type for a given session ID.
*
*   @par Errors:
*   AaFileFtpClientGetSessionType() can return the following values:
*   - #EAaFileFtpClientRet_Ok               Requested operation was successful.
*   - #EAaFileFtpClientRet_InvalidSession   Invalid session ID.
*   - #EAaFileFtpClientRet_InvalidPointer   Invalid pointer.
*
*   @par Example:
*   @code
    EAaFileFtpClientRet retval = EAaFileRet_UndefinedError;
    EAaFileFtpClientSessionType sessionType = EAaFileFtpClientSessionType_Local;

    retval = AaFileFtpClientGetSessionType(sessionId, &sessionType);
    if( EAaFileFtpClientRet_Ok != retval ) {
        // <handle error>
    }
    ...
    @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   LTE3266
*
*   @par Future directions:
*   None
*
*   @see
*   AaFileFtpClientOpen(), AaFileFtpRemoteClientOpenWithPort()
******************************************************************************/
EAaFileFtpClientRet AaFileFtpClientGetSessionType( TAaFileFtpClientSessionId sessionId,
                                                   EAaFileFtpClientSessionType* sessionType );

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* _MCU_RT_IF_AAFILEFTPCLIENT_H_ */
