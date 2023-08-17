/** @file
*   @brief Prototypes of AaFile Signature Verification and Hash Container Verification functions.
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright 2018 Nokia. All rights reserved.$
*/

#ifndef _MCU_RT_IF_AAFILEVERIFICATION_H_
#define _MCU_RT_IF_AAFILEVERIFICATION_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include <../../COMMON/Definitions/IfAaFile_Defs.h>

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
*   @brief      AaFileSign signs a file. Name of signature file which is created
*               is specified by the caller.
*
*   @param[in]  filePath       path of file to be signed, in AaFile path notation
*
*   @param[in]  signaturePath  path of signature file to be created, in AaFile
*                              path notation
*
*   @param[in]  digestTypeStr  digest type as string.
*                              (If GLO_NULL is passed, then default digest type
*                               "sha256" is used.)
*
*   @return     GLO_TRUE on success, GLO_FALSE otherwise
*
*   @par Description:
*   Allowed digest type strings are:
*        "md5",
*        "sha1",
*        "sha224",
*        "sha256",
*        "sha384",
*        "sha512",
*        and "ripemd160".
*
*   @par Errors:
*
*   @par Restrictions:
*   This function is fully available only on FSMr3, AirScale family and on FZM, where LFS
*   cryptographic services are available. For remaining targets a dummy implementation is
*   provided. The dummy implementation doesn't require the LFS cryptographic services,
*   always returns GLO_TRUE and doesn't create a signature file.
*
*   @par Example:
*   @code
*   if ( GLO_TRUE != AaFileSign("/ram/abc.txt", "/ram/abc.sig", GLO_NULL) ) {
*      // Error handling
*   }
*   ...
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/
TBoolean AaFileSign(const char* filePath, const char* signaturePath, const char* digestTypeStr);

/**
******************************************************************************
*
*   @brief      AaFileSignP7 signs a file.
*               For the name of signature file which is created, the given file
*               path is extended with suffix ".p7".
*
*   @param[in]  filePath       path of file to be signed in AaFile path notation
*
*   @param[in]  digestTypeStr  digest type as string.
*                              (If GLO_NULL is passed, then default digest type
*                               "sha256" is used.)
*
*   @return     GLO_TRUE on success, GLO_FALSE otherwise
*
*   @par Description:
*   Allowed digest type strings are:
*        "md5",
*        "sha1",
*        "sha224",
*        "sha256",
*        "sha384",
*        "sha512",
*        and "ripemd160".
*
*   @par Errors:
*
*   @par Restrictions:
*   This function is fully available only on FSMr3, AirScale family and on FZM, where LFS
*   cryptographic services are available. For remaining targets a dummy implementation is
*   provided. The dummy implementation doesn't require the LFS cryptographic services,
*   always returns GLO_TRUE and doesn't create a signature file.
*
*   @par Example:
*   @code
*    if ( GLO_TRUE != AaFileSignP7("/ram/abc.txt", GLO_NULL) ) {
*       // Error handling
*    } else {
*       // A signature file with file path "/ram/abc.txt.p7" was created
*    }
*    ...
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/
TBoolean AaFileSignP7(const char* filePath, const char* digestTypeStr);

/**
******************************************************************************
*
*   @brief      AaFileVerify verifies the signature of a file.
*               Name of signature file is specified by the caller.
*
*   @param[in]  filePath       path of file to be verified, in AaFile path notation
*
*   @param[in]  signaturePath  path of signature file used for verification,
*                              in AaFile path notation
*
*   @return     GLO_TRUE on success, GLO_FALSE otherwise
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*   - This function is fully available only on FSMr3, AirScale family and on FZM, where LFS
*     cryptographic services are available. For remaining targets a dummy implementation is
*     provided. This dummy implementation doesn't require the LFS cryptographic services,
*     doesn't perform any verification and always returns GLO_TRUE.
*   - This function only verifies locally signed files.
*
*   @par Example:
*   @code
*    if ( GLO_TRUE != AaFileVerify("/ram/abc.txt", "/ram/abc.sig") ) {
*       // Verification failed
*    }
*    ...
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/
TBoolean AaFileVerify(const char* filePath, const char* signaturePath);

/**
******************************************************************************
*
*   @brief      AaFileVerifyExternalSign verifies the signature of a file.
*               Name of signature file is specified by the caller.
*
*   @param[in]  filePath       path of file to be verified, in AaFile path notation
*
*   @param[in]  signaturePath  path of signature file used for verification,
*                              in AaFile path notation
*
*   @return     GLO_TRUE on if signature is correct, GLO_FALSE in case of
*               errors or when signature is not correct.
*
*   @par Description:
*
*   @par Errors:
*        GLO_FALSE will be returned in following cases:
*        - Any of argument is NULL pointer of empty string.
*        - Path to file or signature is invalid.
*        - There are no permissions for reading file or its signature.
*        - Signature is invalid for a file.
*
*   @par Restrictions:
*   - This function is fully available only on FSMr3, AirScale family and on FZM, where LFS
*     cryptographic services are available. For remaining targets a dummy implementation is
*     provided. This dummy implementation doesn't require the LFS cryptographic services,
*     doesn't perform any verification and always returns GLO_TRUE.
*   - This function only verifies files signed by a remote authority.
*
*   @par Example:
*   @code
    if ( GLO_TRUE != AaFileVerifyExternalSign("/ram/abc.txt", "/ram/abc.sig") ) {
       // Verification failed
    }
    ...
    @endcode
*
*   @par Rationale:
*   FDT10-0003
*
*   @par Future directions:
*   None
*
******************************************************************************/
TBoolean AaFileVerifyExternalSign(const char* filePath, const char* signaturePath);

/**
******************************************************************************
*
*   @brief      AaFileVerifyP7 verifies the signature of a file.
*               For name of signature file, which has to exist, the given file
*               path is extended with suffix ".p7".
*
*   @param[in]  filePath       path of file to be verified, in AaFile path notation
*
*   @return     GLO_TRUE on success, GLO_FALSE otherwise
*
*   @par Description:
*
*   @par Errors:
*
*   @par Restrictions:
*   - This function is fully available only on FSMr3, AirScale family and on FZM, where LFS
*     cryptographic services are available. For remaining targets a dummy implementation is
*     provided. This dummy implementation doesn't require the LFS cryptographic services,
*     doesn't perform any verification and always returns GLO_TRUE.
*   - This function only verifies locally signed files.
*
*   @par Example:
*   @code
*    // Note: a signature file with path "/ram/abc.txt.p7" should already exist here
*
*    if ( GLO_TRUE != AaFileVerifyP7("/ram/abc.txt") ) {
*       // Verification failed
*    }
*    ...
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/
TBoolean AaFileVerifyP7(const char* filePath);

/**
******************************************************************************
*
*   @brief    AaFileIsSecureEnvironment returns security status of the board.
*
*   @return   GLO_TRUE if environment is secure, GLO_FALSE otherwise
*
*   @par Description:
*   AaFileIsSecureEnvironment() reflects the is_secure reference parameter of DDAL
*   function ddal_security_is_secure_env().
*
*   Since based on ddal_security_is_secure_env() the return value is set in
*   case of internal errors to worst case, which is GLO_FALSE (non-secure environment).
*   Read more about this in header of ddal_security_is_secure_env().
*
*   @par Errors:
*
*   @par Restrictions:
*   This function is fully available only on FSMr3, AirScale family and on FZM. For remaining
*   targets a dummy implementation is provided. The dummy implementation always returns GLO_FALSE.
*
*   @par Example:
*   @code
*   if ( GLO_TRUE != AaFileIsSecureEnvironment() ) {
*       if ( GLO_TRUE != AaFileVerify("/ram/abc.txt", "/ram/abc.sig") ) {
*           // Verification failed
*       }
*   }
*   ...
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see ddal_security_is_secure_env()
*
******************************************************************************/
TBoolean AaFileIsSecureEnvironment(void);

/**
******************************************************************************
*
*   @brief Load the Hash Container file and verify its signature.
*
*   Performs the initial validation for Hash Container Signature file and
*   Hash Container file. On success a context object is returned.
*
*   @param[in]  hashContainerPath     path of Hash Container file
*   @param[in]  hashContainerSigPath  path of Hash Container Signature file
*   @param[out] error                 error reference pointer
*
*   @return Pointer to context object for current validation processing.
*           A valid pointer reflects a successful validation.
*           Otherwise, if pointer is GLO_NULL, validation failed.
*
*   @note Ownership of returned context object is passed to the user.
*         The user has to clean up the context with help of function
*         AaFileVerifyHashCleanup()
*
*   @par Restrictions:
*   This function is fully available only on FSMr3, AirScale family and on FZM, where LFS
*   cryptographic services are available. For remaining targets a dummy implementation is
*   provided. The dummy implementation performs sanity checks of input parameters,
*   allocates a dummy context object, and sets error reference pointer accordingly.
*
*   @par Example:
*   @code
*   if ( GLO_NULL == (hashContext = AaFileVerifyHashInit("hcFile.txt", "hcFile.txt.sig", &error)) ) {
*   // Check the value of error for specific reason of failure
*   }
*   ...
*   @endcode
*
*   @see AaFileVerifyHashCleanup()
*   @see AaFileVerifyHash()
*   @see AaFileVerifyHashFlat()
*
******************************************************************************/
void* AaFileVerifyHashInit(const char* hashContainerPath, const char* hashContainerSigPath, EAaFileVerifyError* error);

/**
******************************************************************************
*
*   @brief Frees a Hash Container verification context object.
*
*   @param[in]  hashContext  pointer to a pointer to context object for current
*                            validation process.
*
*   @par Restrictions:
*   This function is fully available only on FSMr3, AirScale family and on FZM, where LFS
*   cryptographic services are available. For remaining targets a dummy implementation is
*   provided. The dummy implementation performs sanity checks of input parameter,
*   and frees the dummy context object.
*
*   @par Example:
*   @code
*   if ( GLO_NULL == (hashContext = AaFileVerifyHashInit("hcFile.txt", "hcFile.sig", &error)) ) {
*       // Check the value of error for specific reason of failure
*   }
*
*   // call AaFileVerifyHash() as required
*
*   AaFileVerifyHashCleanup(&hashContext);
*   @endcode
*
*   @see AaFileVerifyHashInit()
*   @see AaFileVerifyHash()
*   @see AaFileVerifyHashFlat()
*
******************************************************************************/
void AaFileVerifyHashCleanup(void** hashContext);

/**
******************************************************************************
*
*   @brief Validate the hash of given file against a related entry in the
*          Hash Container file.
*
*   With given file path, a lookup in the Hash Container file for a related
*   entry is performed. If no entry for that file path is found in the Hash
*   Container file, then the function returns GLO_FALSE, and a specific error
*   is referenced.
*
*   If an entry for that file path exists, then the hash of the file is
*   calculated with the hash algorithm, which is determined by the entry.
*   The locally calculated hash is compared with the hash that is stored
*   in the Hash Container entry, and its result is returned.
*
*   @param[in]  hashContext  pointer to context object of current validation process
*   @param[in]  filePath     path of file to be validated
*   @param[out] error        error reference
*
*   @par Restrictions:
*   This function is fully available only on FSMr3, AirScale family and on FZM, where LFS
*   cryptographic services are available. For remaining targets a dummy implementation is
*   provided. The dummy implementation performs sanity checks of input parameters,
*   and returns GLO_TRUE if the input parameters are valid. If they are not, GLO_FALSE
*   is returned. In both cases error reference pointer is set accordingly.
*
*   @par Example:
*   @code
*   if ( GLO_FALSE == AaFileVerifyHash(hashContext, "fileToVerify.txt", &error) ) {
*       // Check the value of error for specific reason of failure
*   }
*   ...
*   @endcode
*
*   @see AaFileVerifyHashInit()
*   @see AaFileVerifyHashCleanup()
*   @see AaFileVerifyHashFlat()
*
******************************************************************************/
TBoolean AaFileVerifyHash(void* hashContext, const char* filePath, EAaFileVerifyError* error);

/**
******************************************************************************
*
*   @brief Validate the hash of file stored in a temporary location against a related
*          entry in the Hash Container file. Target path and hardware unit can be specified
*          as function arguments.
*
*   This function searches the Hash Container file for appropriate entry with a specified
*   hardware unit. The entry is constructed by concatenating \p targetPath argument with
*   file name from \p filePath argument.
*
*   If an entry for specified hardware unit exists, then the hash of the file stored
*   in a temporary location (specified by \p filePath argument) is calculated with hashing
*   algorithm determined by the entry. Locally calculated hash is compared with the hash
*   stored in the Hash Container entry. The result is returned, and error pointer is set
*   appropriately.
*
*   Unlike AaFileVerifyHash(), it is not required that the file to be validated is
*   stored with the same directory structure as specified in the Hash Container file.
*
*   @param[in]  hashContext  pointer to context object of current validation process
*   @param[in]  filePath     path to where the file to be validated is stored
*   @param[in]  targetPath   target path of the file to be validated
*   @param[in]  hwUnit       hardware unit specification
*   @param[out] error        error reference pointer
*
*   @par Restrictions:
*   This function is fully available only on FSMr3, AirScale family and on FZM, where LFS
*   cryptographic services are available and provide an alternative method for file verification
*   using Hash Container (in which target path and hardware unit can be provided as arguments).
*   For remaining targets a dummy implementation is provided. The dummy implementation
*   performs sanity checks of input parameters, and returns GLO_TRUE if the input
*   parameters are valid. If they are not, GLO_FALSE is returned. In all cases error
*   reference pointer is set accordingly.
*
*   @par Example:
*   @code
    // create hash verification context object

    if( GLO_FALSE == AaFileVerifyHashFlat(hashContext, "/ram/BTSOMexe", "swpool/OAM/", "FCTJ", &error)) {
        // check error value, handle the error
    }

    // free verification context object
    @endcode
*
*   @par Rationale:
*   LTE3340-D-d
*
*   @see AaFileVerifyHashInit()
*   @see AaFileVerifyHash()
*   @see AaFileVerifyHashCleanup()
*
******************************************************************************/
TBoolean AaFileVerifyHashFlat( void *hashContext,
                               const char *filePath,
                               const char *targetPath,
                               const char *hwUnit,
                               EAaFileVerifyError *error );

/** @} */


#ifdef __cplusplus
}
#endif

#endif /* _MCU_RT_IF_AAFILEVERIFICATION_H_ */
