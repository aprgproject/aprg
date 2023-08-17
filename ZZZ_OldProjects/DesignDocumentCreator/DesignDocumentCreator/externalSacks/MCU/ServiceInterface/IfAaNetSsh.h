/** @file
*   @brief Functions for handling SSH and authentication configuration.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef _MCU_IF_AANET_SSH_H_
#define _MCU_IF_AANET_SSH_H_

#include <glo_def.h>
#include <CcsCommon.h>
#include <../Definitions/IfAaNet_Defs.h>

/** @addtogroup dgAaNetMcu */

/** @{ */

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Initialize SSHD and authentication configuration options structure.
*
* @param[in,out] options        structure of configuration parameters
*
* @retval #EAaNetRet_Ok         operation was successful
* @retval #EAaNetRet_ParmError  \c NULL pointer to options structure
*
* @par Description
* This function initializes a structure of SSHD and authentication options. To
* change the options user must assign appropriate values to structure fields
* after initialization, and call AaNetSshConfigureOptionsApply(). It is not
* required to set every field of the structure: setting a subset of fields
* is supported.
*
* @par Errors
* See Return values section.
*
* @par Restrictions
* None.
*
* @par Example
* @code
* #include <IfAaNetSsh.h>
*
* SAaNetSshConfigureOptions options;
*
* EAaNetRet result = AaNetSshConfigureOptionsInit(&options);
* if( EAaNetRet_Ok != result ) {
*   // handle initialization error
* }
*
* options.clientAliveTime = 5;
* options.loginDelayTime = 180;
* options.maxAuthTries = 4;
* options.passwordHistoryLength = 10;
*
* result = AaNetSshConfigureOptionsApply(&options);
* if( EAaNetRet_Ok != result ) {
*   // handle error of configuration
* }
* @endcode
*
* @par Rationale
* 5GC002359-B
*/
EAaNetRet AaNetSshConfigureOptionsInit(SAaNetSshConfigureOptions *options);

/**
* @brief Apply configuration changes related to SSH daemon and authentication.
*
* @param[in]  options           structure of configuration parameters
* @param[out] errors            status of every configuration change
*
* @retval #EAaNetRet_Ok         all configuration changes applied successfully
* @retval #EAaNetRet_ParmError  \c NULL pointer to options structure or invalid parameter values
* @retval #EAaNetRet_Error      failed to apply at least one configuration change
*
* @par Description
* This function applies SSHD and authentication configuration changes defined
* by the fields of #SAaNetSshConfigureOptions structure. It triggers at most
* one restart of the SSH daemon. Once this fuction returns CC&S no longer refers
* to the memory pointed by #SAaNetSshConfigureOptions.bannerText. Caller still
* owns the memory and is responsible for freeing it.
*
* @par Errors
* In addition to returning status codes described in the Return values section,
* \p errors variable is used to store the bitwise alternative of statuses
* defined in #EAaNetSshStatus.
*
* @par Restrictions
*  - Parameters structure must be initialized with AaNetSshConfigureOptionsInit()
*    prior to assigning values to its fields. Using uninitialized parameters
*    structure may result in undefined behavior.
*  - The maximum length of SSH banner text is #AANET_MAX_SSH_BANNER_TEXT_LENGTH.
*
* @par Example
* @code
* #include <IfAaNetSsh.h>
*
* u32 errors = 0;
* SAaNetSshConfigureOptions options;
*
* EAaNetRet result = AaNetSshConfigureOptionsInit(&options);
* if( EAaNetRet_Ok != result ) {
*   // handle initialization error
* }
*
* options.restrictedRootEnabled = GLO_TRUE;
* options.bannerText = "Unauthorized access prohibited.";
*
* result = AaNetSshConfigureOptionsApply(&options, &errors);
* if( EAaNetRet_Ok != result ) {
*   if( errors & EAaNetSshStatus_RestrictedRootFail ) {
*       // handle failure of setting Restricted Root Access mode
*   }
*   // check for other possible failures
* }
* @endcode
*
* @par Rationale
* 5GC002359-B
*
* @see AaNetRestrictedRootAccessEnable(), AaNetRestrictedRootAccessDisable(),
* AaNetSshConfigureClientAliveTime(), AaNetSshConfigureDelayTime(),
* AaNetUserChangePasswordHistory(), AaNetSshSetBanner()
*/
EAaNetRet AaNetSshConfigureOptionsApply(const SAaNetSshConfigureOptions *options, u32 *errors);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* _MCU_IF_AANET_SSH_H_ */
