/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016, 2018 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AACONFIG_RAD_H_
#define _COMMON_IF_AACONFIG_RAD_H_

#include <CcsCommon.h>
#include <TAaSysComSicad.h>
#include <ERadSwDomain.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../Definitions/IfAaConfigRad_Defs.h>
#include <../Definitions/IfAaConfig_Defs.h> // for EAaConfigRet
#include <../Definitions/IfAaSysCom_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaConfigRad AaConfigRad API
*
* Common Computer and Support SW Configuration AaConfigRad service API.
*
*/

/**
 * @defgroup dgAaConfigRadApi AaConfigRad functions
 * @ingroup dgAaConfigRad
 */

/**
 * @defgroup dgAaConfigRadApiCommon AaConfigRad common functions
 * @ingroup dgAaConfigRadApi
 */
/*@{*/

/**
*******************************************************************************
*
*   @brief      Function initializing R&D SW Domain with given number of R&D tags.
*
*   @param[in]  domain              SW domain
*   @param[in]  count               Number of R&D tags in SW Domain
*
*   @par Description:
*   Initializes given R&D SW Domain with given number of R&D tags.
*
*   @return     Function returns status of operation.
*
*   @par Errors:
*   - EAaConfigRet_NotAllowed
*   - EAaConfigRet_InvalidParameter
*
*   @par Restrictions:
*   - The number of R&D tags in SW Domain shall not exceed the number
*     defined by @ref AACONFIG_RAD_DOMAIN_MAX_TAG_COUNT or otherwise
*     initialization of SW Domain will fail with @ref EAaConfigRet_InvalidParameter error code.
*   - R&D SW domain shall be initialized only once in EE. Multiple attempts to initialize same R&D SW Domain
*     will fail with @ref EAaConfigRet_NotAllowed error code.
*
*   @par Example:
*   @code
*   static void initializeCcsRadParameters(void)
*   {
*     if (EAaConfigRet_Ok == AaConfigRadSetMaxTagCount(ERadSwDomain_Ccs, ERadCcs_Last)
*     {
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysCom, "AaSysCom", 0);
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysLog, "AaSysLog", 0);
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysTime, "AaSysTime", 0);
*     }
*   }
*
*   void exampleFunc()
*   {
*     AaConfigRadRegisterDomain(ERadSwDomain_Ccs,
*                               "CCS",
*                               initializeCcsRadParameters);
*   }
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

EAaConfigRet AaConfigRadSetMaxTagCount(u32 domain, u32 count);


/**
*******************************************************************************
*
*   @brief      Function for initialize R&D tag to default.
*
*   @param[in]  tag                 Identifier of R&D tag.
*   @param[in]  stringPtr           name of R&D tag.
*   @param[in]  initialValue        Initial value of R&D tag.
*
*   @return     Function returns success of operation.
*
*   @par Description:
*   None
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter
*
*   @par Restrictions:
*   - A shallow copy of R&D tag name is stored by CC&S
*     and later returned from @ref AaConfigRadGetTagString API function.
*     The lifetime of the actual R&D tag name is expected
*     to be the same as lifetime of registering application EE.
*   - This function should be called only inside user callback function
*     where initial values are set for domain R&D parameters.
*
*   @par Example:
*   @code
*   static void initializeCcsRadParameters(void)
*   {
*     if (EAaConfigRet_Ok == AaConfigRadSetMaxTagCount(ERadSwDomain_Ccs, ERadCcs_Last)
*     {
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysCom, "AaSysCom", 0);
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysLog, "AaSysLog", 0);
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysTime, "AaSysTime", 0);
*     }
*   }
*
*   void exampleFunc()
*   {
*     AaConfigRadRegisterDomain(ERadSwDomain_Ccs,
*                               "CCS",
*                               initializeCcsRadParameters);
*   }
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
*******************************************************************************/

EAaConfigRet AaConfigRadSetDefault(u32         tag,
                                   const char* stringPtr,
                                   u32         initialValue);

/**
*******************************************************************************
*
*   @brief      Function for set maximum count of R&D SW Domains.
*
*   @param[in]  count               Maximum count of domains
*
*   @par Description:
*   Set maximum number of SW domains
*
*   @return     Function returns success of operation.
*
*   @par Errors:
*   - EAaConfigRet_NotAllowed
*   - EAaConfigRet_InvalidParameter
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*   ...;
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
EAaConfigRet AaConfigRadSetMaxDomainCount(u32 count);


/**
*******************************************************************************
*
*   @brief      Function for registering R&D SW Domain.
*
*   @param[in]  domain               Identifier of R&D SW Domain
*   @param[in]  nameStringPtr        name of R&D SW Domain
*   @param[in]  initializeParameters Function which handles factory default
*                                    parameters setting.
*
*   @return     Function returns success of operation.
*
*   @par Description:
*   None
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter
*   - EAaConfigRet_NotAllowed
*   - EAaConfigRet_NoMem
*
*   @par Restrictions:
*   A shallow copy of R&D SW Domain name is stored by CC&S
*   and later returned from @ref AaConfigRadGetDomainString API function.
*   The lifetime of the actual R&D SW Domain name is expected
*   to be the same as lifetime of registering application EE.
*
*   @par Example:
*   @code
*   static void initializeCcsRadParameters(void)
*   {
*     if (EAaConfigRet_Ok == AaConfigRadSetMaxTagCount(ERadSwDomain_Ccs, ERadCcs_Last)
*     {
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysCom, "AaSysCom", 0);
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysLog, "AaSysLog", 0);
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysTime, "AaSysTime", 0);
*     }
*   }
*
*   void exampleFunc()
*   {
*     AaConfigRadRegisterDomain(ERadSwDomain_Ccs,
*                               "CCS",
*                               initializeCcsRadParameters);
*   }
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
EAaConfigRet AaConfigRadRegisterDomain(u32 domain,
                                       const char* nameStringPtr,
                                       void (*initializeParameters)(void));

/**
*******************************************************************************
*
*   @brief      Function for registering R&D SW Domain.
*
*               After registration, the attribute tag "ccs.service.aaconfig.rad.domain.<domain>.synched"
*               is set to value 1 to indicate that the domain registration completed.
*
*   @param[in]  domain               Identifier of R&D SW Domain
*   @param[in]  nameStringPtr        name of R&D SW Domain
*   @param[in]  initializeParameters Function which handles factory default
*                                    parameters setting.
*
*   @return     Function returns success of operation.
*
*   @par Description:
*   None
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter
*   - EAaConfigRet_NotAllowed
*   - EAaConfigRet_NoMem
*
*   @par Restrictions:
*   A shallow copy of R&D SW Domain name is stored by CC&S
*   and later returned from @ref AaConfigRadGetDomainString API function.
*   The lifetime of the actual R&D SW Domain name is expected
*   to be the same as lifetime of registering application EE.
*   The function does not implement a synchronous domain registration.
*   When returning, the domain is "under" registration but registration may not be completed.
*   When the mentioned Attribute Tag is set, registration is complete, but not before.
*
*   @par Example:
*   @code
*   static void initializeCcsRadParameters(void)
*   {
*     if (EAaConfigRet_Ok == AaConfigRadSetMaxTagCount(ERadSwDomain_Ccs, ERadCcs_Last)
*     {
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysCom, "AaSysCom", 0);
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysLog, "AaSysLog", 0);
*       AaConfigRadSetDefault(ERadCcs_PrintAaSysTime, "AaSysTime", 0);
*     }
*   }
*
*   void exampleFunc()
*   {
*     AaConfigRadRegisterDomainSynch(ERadSwDomain_Ccs,
*                                    "CCS",
*                                    initializeCcsRadParameters);
*   }
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
EAaConfigRet AaConfigRadRegisterDomainSynch(u32 domain, const char* nameStringPtr, void (*initializeParameters)(void));

/**
*******************************************************************************
*
*   @brief      Function for setting SW domain.
*
*   @param[in]  domain              Identifier of R&D SW Domain
*   @param[in]  nameStringPtr       name of R&D SW Domain
*   @param[in]  confTblPtr          Pointer to existing sw configuration table.
*   @param[in]  tagCount            Count of tags in table.
*   @param[in]  tagNameTbl          Pointer to a table containing tag names.
*
*   @return     Function returns success of operation.
*
*   @par Description:
*   None
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter
*   - EAaConfigRet_NotAllowed
*   - EAaConfigRet_NoMem
*
*   @par Restrictions:
*   CC&S stores shallow copies of all input parameters.
*   Shallow copies are also returned from @ref AaConfigRadGetDomainString
*   and @ref AaConfigRadGetTagString API functions.
*   The lifetime of parameters passed to this API function by pointers
*   is expected to be the same as lifetime of registering application EE.
*
*   @par Example:
*   @code
*   void exampleFunc()
*   {
*     AaConfigRadSetDomain(ERadSwDomain_Legacy,
*                          "LGC",
*                          &sw_conf_table[0],
*                          FEAT_DBG_MaxNumOfFeat,
*                          feature_string_tbl);
*   }
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
EAaConfigRet AaConfigRadSetDomain(u32 domain,
                                  const char* nameStringPtr,
                                  const void* confTblPtr,
                                  const u32 tagCount,
                                  const char** tagNameTbl);

/**
*******************************************************************************
*
*   @brief      Set all R&D tags of a domain to its default values.
*
*   @param[in]  domain        Domain ID
*
*   @return     Function returns success of operation.
*
*   @par Description:
*   None
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter
*   - EAaConfigRet_NotRegistered
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*     u32 ret = AaConfigRadSetDefaultValues(ERadSwDomain_Ccs);
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
EAaConfigRet AaConfigRadSetDefaultValues(ERadSwDomain domain);

/**
*******************************************************************************
*
*   @brief      Function for update R&D tag default value.
*
*   @param[in]  tag           Identifier of R&D tag.
*   @param[in]  value         New value for R&D tag.
*
*   @return     Function returns success of operation.
*
*   @par Description:
*   None
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter
*   - EAaConfigRet_NotRegistered
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*     u32 value = 1;
*     u32 ret = AaConfigRadUpdateDefaultValue(ERadCcs_PrintAaSysCom, value);
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
EAaConfigRet AaConfigRadUpdateDefaultValue(u32 tag, u32 value);

/**
*******************************************************************************
*
*   @brief      Function for set R&D tag value.
*
*   @param[in]  tag           Identifier of R&D tag.
*   @param[in]  value         New value for R&D tag.
*
*   @return     Function returns success of operation.
*
*   @par Description:
*   None
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter
*   - EAaConfigRet_NoMem
*   - EAaConfigRet_Error
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*     u32 value = 1;
*     u32 ret = AaConfigRadSetValue(ERadCcs_PrintAaSysCom, value);
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
EAaConfigRet AaConfigRadSetValue(u32 tag, u32 value);

/**
*******************************************************************************
*
*   @brief      Function for set R&D tag value on RadMaster.
*
*   @param[in]  tag           Identifier of R&D tag.
*   @param[in]  value         New value for R&D tag.
*
*   @return     Function returns success of operation.
*
*   @par Description:
*   None
*
*   @par Errors:
*   - EAaConfigRet_Error
*   - EAaConfigRet_NoMem
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*     u32 value = 1;
*     u32 ret = AaConfigRadSetMasterValue(ERadCcs_PrintAaSysCom, value);
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
EAaConfigRet AaConfigRadSetMasterValue(u32 tag, u32 value);

/**
*******************************************************************************
*
*   @brief      Function for get R&D Tag SW Domain name.
*
*   @param[in]  tag           Identifier of R&D tag
*
*   @return     pointer to R&D SW Domain name.
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*     char *str = AaConfigRadGetDomainString(ERadCcs_PrintAaSysCom);
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
const char* AaConfigRadGetDomainString(u32 tag);


/**
*******************************************************************************
*
*   @brief      Function for get R&D tag name.
*
*   @param[in]  tag           Identifier of R&D tag.
*
*   @return     Pointer to name of R&D tag.
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*     char *str = AaConfigRadGetTagString(ERadCcs_PrintAaSysCom);
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
const char* AaConfigRadGetTagString(u32 tag);


/**
*******************************************************************************
*
*   @brief      Function for select which part have access to flash.
*
*   @param[in]  selector      Identifier of Master or Slave.
*
*   @return     Function returns nothing.
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*   ...;
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
void AaConfigRadPersistentMemory(EAaConfigRadOperatingMode selector);


/**
*******************************************************************************
*
*   @brief      Function for subscribe notifications from parameter's value change.
*
*   @param[in]  tag           Identifier of R&D tag.
*   @param[in]  sicAddress    Subscriber's sic address
*
*   @return     Function returns nothing.
*
*   @par Description:
*   Application can subscribe notification of changed R&D parameter.
*   Message AaConfigRadChangeNotif is sent to applications which are
*   subscribed i.e. change notifications.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*     TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                                 AaProEuCurrent());
*     TAaSysComSicad mySicad = AaSysComSicadGet(myCpid, AaSysComGetOwnNid());
*     void *msg;
*
*     AaConfigRadSubscribeNotifs(ERadCcs_PrintAaSysCom, mySicad);
*     msg = AaSysComMsgReceive(15000);
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
void AaConfigRadSubscribeNotifs(u32 tag, TAaSysComSicad sicAddress);


/**
*******************************************************************************
*
*   @brief      Function for unsubscribe notifications from parameter's value change
*
*   @param[in]  tag           Identifier of R&D tag.
*   @param[in]  sicAddress    Subscriber's sic address.
*
*   @return     Function returns nothing.
*
*   @par Description:
*   Function cancels subscription of parameter change notifications.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*     TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                                 AaProEuCurrent());
*     TAaSysComSicad mySicad = AaSysComSicadGet(myCpid, AaSysComGetOwnNid());
*     void *msg;
*
*     AaConfigRadSubscribeNotifs(ERadCcs_PrintAaSysCom, mySicad);
*     msg = AaSysComMsgReceive(15000);
*
*     AaConfigRadUnSubscribeNotifs(ERadCcs_PrintAaSysCom, mySicad);
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
void AaConfigRadUnSubscribeNotifs(u32 tag, TAaSysComSicad sicAddress);


/**
*******************************************************************************
*
*   @brief      Function for subscribing notify message of updated multiple R&D tags in one domain.
*
*   @param[in]  domain        Domain ID
*   @param[in]  sicAddress    Subscriber's sic address
*
*   @return     Function returns success of operation.
*
*   @par Description:
*   Application can subscribe notification of updated R&D parameter in one domain.
*   Message AaConfigRadUpdateNotif is sent to applications which are subscribed
*   after all tags contained in one SET_PARAMS message have been updated.
*
*   @par Errors:
*   - EAaConfigRet_NoMem
*
*   @par Restrictions:
*   Parameter updates by function interface are not affected by this method.
*
*   @par Example:
*   @code
*     TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                                 AaProEuCurrent());
*     TAaSysComSicad mySicad = AaSysComSicadGet(myCpid, AaSysComGetOwnNid());
*     void *msg;
*
*     ret = AaConfigRadSubscribeDomainUpdate(ERadDomain_Ccs, mySicad);
*     msg = AaSysComMsgReceive(15000);
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
EAaConfigRet AaConfigRadSubscribeDomainUpdate(u32 domain, TAaSysComSicad sicAddress);


/**
*******************************************************************************
*
*   @brief      Function for unsubscribing notify message of updated R&D tags in one domain.
*
*   @param[in]  domain        Domain ID
*   @param[in]  sicAddress    Subscriber's sic address.
*
*   @return     Function returns nothing.
*
*   @par Description:
*   Function cancels subscription of domain update notifications.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*     TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                                 AaProEuCurrent());
*     TAaSysComSicad mySicad = AaSysComSicadGet(myCpid, AaSysComGetOwnNid());
*     void *msg;
*
*     AaConfigRadSubscribeDomainUpdate(ERadDomain_Ccs, mySicad);
*     msg = AaSysComMsgReceive(15000);
*
*     AaConfigRadUnSubscribeDomainUpdate(ERadDomain_Ccs, mySicad);
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
void AaConfigRadUnSubscribeDomainUpdate(u32 domain, TAaSysComSicad sicAddress);


/**
********************************************************************************
*
* @brief        Registers an observer callback to given R&D tag.
*
* @param[in]    flag      R&D tag id.
*
* @param[in]    callback  Pointer to an observer callback function.
*
* @return       Function returns status of operation.
*
* @par Description:
* Registers an observer callback to given R&D tag. The observer callback
* shall be called every time R&D tag's value is changed. There can be multiple
* observers per R&D tag. If R&D tag does not exist - i.e. flag has not been
* registered in current RAD slave, callback is registered. In case R&D tag
* is from domain that is out of range, error is reported.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NoMem
* - EAaConfigRet_Error
* - EAaConfigRet_NotInitialized
*
* @par Restrictions:
* Observers should be careful not to use any API calls which might lead to
* AaConfig R&D related API calls since during observer call, R&D tag database
* is locked by AaConfig internally thus calls to AaConfig R&D tag API would
* lead to deadlocks.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* TAaConfigRadObserver and AaConfigRadFlagUnregister
*
* @par Example:
* @code
*   AaConfigRadObserverExampleFunc(const u32 flag,
*                                  const u32 value)
*   {
*     // Some code here
*   }
*
*   void exampleFunc(void)
*   {
*     ret = AaConfigRadFlagRegister(ERadCcs_PrintAaSysCom,
*                                   &AaConfigRadObserverExampleFunc);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigRadFlagRegister(u32 flag,
                                     TAaConfigRadObserver* const callback);

/**
********************************************************************************
*
* @brief        Unregisters an observer callback to given R&D tag.
*
* @param[in]    flag      R&D tag id.
*
* @param[in]    callback  Pointer to an observer callback function.
*
* @return       Function returns status of operation.
*
* @par Description:
* Unregisters previously registered observer callback for given R&D tag.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NotRegistered
* - EAaConfigRet_TagNotFound
* - EAaConfigRet_NotInitialized
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* TAaConfigRadObserver and AaConfigRadFlagRegister
*
* @par Example:
* @code
*   AaConfigRadObserverExampleFunc(const u32 flag,
*                                  const u32 value)
*   {
*     // Some code here
*   }
*
*   void exampleFunc(void)
*   {
*     ret = AaConfigRadFlagRegister(ERadCcs_PrintAaSysCom,
*                                   &AaConfigRadObserverExampleFunc);
*     ret = AaConfigRadFlagUnregister(ERadCcs_PrintAaSysCom,
*                                     &AaConfigRadObserverExampleFunc);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigRadFlagUnregister(u32 flag,
                                       TAaConfigRadObserver* const callback);

/**
********************************************************************************
*
* @brief        Registers an observer callback to given R&D domain.
*
* @param[in]    domainId  R&D domain id.
*
* @param[in]    callback  Pointer to an observer callback function.
*
* @return       Function returns status of operation.
*
* @par Description:
* Registers an observer callback to given R&D domain. The observer callback
* shall be called every time any R&D tag's from given domain is changed. There
* can be multiple observers per R&D domain. If R&D domain is out of range, error
* is reported. It is possible to register callback in current RAD slave for domain
* id from valid range which is not yet registered.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NoMem
* - EAaConfigRet_Error
* - EAaConfigRet_NotInitialized
*
* @par Restrictions:
* Observers should be careful not to use any API calls which might lead to
* AaConfig R&D related API calls since during observer call, R&D tag database
* is locked by AaConfig internally thus calls to AaConfig R&D tag API would
* lead to deadlocks.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* TAaConfigRadObserver and AaConfigRadDomainUnregister
*
* @par Example:
* @code
*   AaConfigRadDomainObserverExampleFunc(const u32 flag,
*                                        const u32 value)
*   {
*     // Some code here
*   }
*
*   void exampleFunc(void)
*   {
*     ret = AaConfigRadDomainRegister(ERadSwDomain_Ccs,
*                                     &AaConfigRadDomainObserverExampleFunc);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigRadDomainRegister(ERadSwDomain domainId,
                                       TAaConfigRadObserver* const callback);

/**
********************************************************************************
*
* @brief        Unregisters an observer callback to given R&D domain.
*
* @param[in]    domainId  R&D domain id.
*
* @param[in]    callback  Pointer to an observer callback function.
*
* @return       Function returns status of operation.
*
* @par Description:
* Unregisters previously registered observer callback for given R&D tag.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NotRegistered
* - EAaConfigRet_TagNotFound
* - EAaConfigRet_NotInitialized
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* None.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* TAaConfigRadObserver and AaConfigRadDomainRegister
*
* @par Example:
* @code
*   AaConfigRadDomainObserverExampleFunc(const u32 flag,
*                                        const u32 value)
*   {
*     // Some code here
*   }
*
*   void exampleFunc(void)
*   {
*     ret = AaConfigRadDomainRegister(ERadSwDomain_Ccs,
*                                     &AaConfigRadDomainObserverExampleFunc);
*     ret = AaConfigRadDomainUnregister(ERadSwDomain_Ccs,
*                                       &AaConfigRadDomainObserverExampleFunc);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigRadDomainUnregister(ERadSwDomain domainId,
                                         TAaConfigRadObserver* const callback);

/**
*******************************************************************************
*
*   @brief      Function to compose Attribute Tag String that indicates, when
*               set to 1, that the registration negotiation with the RadMaster
*               is complete.
*
*   @param[in]  str      Buffer pointer where Attribute Tag String is written
*   @param[in]  size     Buffer size
*   @param[in]  domain   Domain ID
*
*   @return     Same as return value of snprintf()
*
*   @par Description:
*   Function to compose Attribute Tag String
*
*   @par Errors: see snprintf()
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   @code
*   size = AaConfigRadGetDomainSynchedTagString(domainSynchedTagName,
*          AACONFIG_TAG_MAX_NAME_LENGTH, regRspMsg->domain);
*   if(size < 0 || size == AACONFIG_TAG_MAX_NAME_LENGTH ||
*      EAaConfigRet_Ok != AaConfigTagSetU32(domainSynchedTagName, 1))
*   {
*     AaSysLogPrintE(EAaSysLogSeverityLevel_Error, AACONFIG_RAD_SLAVE_PRINT_FEAT,
*                    "handleDomainRegisterRsp: Could not set registration tag for Domain %d",
*                    regRspMsg->domain);
*   }
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
int AaConfigRadGetDomainSynchedTagString(char *str, int size, u32 domain);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_COMMON_IF_AACONFIG_RAD_H_
