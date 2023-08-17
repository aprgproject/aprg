/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2018 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AACONFIG_SVC_REG_H_
#define _COMMON_IF_AACONFIG_SVC_REG_H_

#include <CcsCommon.h>
#include <IfAaSysTime_Defs.h>
#ifdef CCS_NEW_IF_STRUCTURE
#include <../Definitions/IfAaConfig_Defs.h>
#include <../Definitions/IfAaConfigSvcReg_Defs.h>
#include <../Messages/IfAaConfigSvcReg_Msg.h>
#include <../Definitions/IfAaSysTime_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaConfigSvcReg AaConfigSvcReg API
*
* Common Computer and Support SW Configuration AaConfigSvcReg service API.
*
*/

/**
 * @defgroup dgAaConfigSvcRegApi AaConfigSvcReg functions
 * @ingroup dgAaConfigSvcReg
 */

/**
 * @defgroup dgAaConfigSvcRegApiCommon AaConfigSvcReg common functions
 * @ingroup dgAaConfigSvcRegApi
 */
/*@{*/

/**
********************************************************************************
*
* @brief        AaConfigSubscribeService subscribes an application to a registered service.
*
* @param[in]    namePtr          Pointer to NULL-terminated string containing the service name.
*
* @param[in]    major_version    Major version number of the service.
*
* @param[in]    minor_version    Minor version number of the service.
*
* @param[in]    scope            Enumeration value which defines the scope of service subscription.
*
* @param[in]    sicad            SIC address of subscribing application.
*
* @return       Function returns status of operation.
*
* @par Description:
* Function \ref AaConfigSubscribeService is used by applications to subscribe to SW services.
* The application receives a notification message (AACONFIG_SVC_REG_NOTIF_MSG) every time a service with matching name
* and version is registered or unregistered by a server in the requested scope.
* The scope argument relates to the location of subscribing application and subscribed service.
* A EE/CE scope subscriber gets notifications about all services with matching name and version registered
* by a server in the same EE/CE.
* A Global scope subscriber gets notifications about all services with matching name and version.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NoMem
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
* @see AaConfigUnSubscribeService
* @see AaConfigRegisterService
* @see AaConfigUnRegisterService
* @see AaConfigGetService
* @see AaConfigGetServiceWithTimeout
* @see AaConfigReverseLookupOfService
*
* @par Example:
* @code
*   #define AACONFIG_SERVICE_FAULT_HANDLING "faultHandling"
*   static TAaSysComSicad mySicad;
*
*   void exampleFunc(void)
*   {
*     u32 major_version = 1;
*     u32 minor_version = 2;
*
*     ret = AaConfigSubscribeService(AACONFIG_SERVICE_FAULT_HANDLING,
*                                    major_version,
*                                    minor_version,
*                                    EAaConfigSvcRegScope_CE,
*                                    mySicad);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigSubscribeService(const char* const namePtr, const u32 major_version,
                                      const u32 minor_version, EAaConfigSvcRegScope scope, TAaSysComSicad sicad);

/**
********************************************************************************
*
* @brief        AaConfigUnSubscribeService removes subscription of an application for registered services.
*
* @param[in]    namePtr          Pointer to NULL-terminated string containing the service name.
*
* @param[in]    major_version    Major version number of the service.
*
* @param[in]    minor_version    Minor version number of the service.
*
* @param[in]    sicad            SIC address of unsubscribing application.
*
* @return       Function returns status of operation.
*
* @par Description:
* Function \ref AaConfigUnSubscribeService is used by applications to unsubscribe from SW services.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NotRegistered
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
* @see AaConfigSubscribeService
* @see AaConfigRegisterService
* @see AaConfigUnRegisterService
* @see AaConfigGetService
* @see AaConfigGetServiceWithTimeout
* @see AaConfigReverseLookupOfService
*
* @par Example:
* @code
*   #define AACONFIG_SERVICE_FAULT "faultHandling"
*   TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                               AaProEuCurrent());
*
*   void exampleFunc(void)
*   {
*     u32 major_version = 1;
*     u32 minor_version = 2;
*     TAaSysComSicad mySicad = AaSysComSicadGet(myCpid, AaSysComGetOwnNid());
*     ret = AaConfigUnSubscribeService(AACONFIG_SERVICE_FAULT_HANDLING,
*                                      major_version,
*                                      minor_version,
*                                      mySicad);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigUnSubscribeService(const char* const namePtr, const u32 major_version,
                                        const u32 minor_version, TAaSysComSicad sicad);

/**
********************************************************************************
*
* @brief        AaConfigRegisterService registers a service to be used by subscribed applications.
*
* @param[in]    namePtr    Pointer to NULL-terminated string containing the service name.
*
* @param[in]    major_version    Major version number of the service.
*
* @param[in]    minor_version    Minor version number of the service.
*
* @param[in]    scope      Enumeration value which defines the visibility of the service.
*
* @param[in]    sicad      SIC address of the service.
*
* @return       Function returns status of operation.
*
* @par Description:
* Function \ref AaConfigRegisterService is used by sw servers to register services.
* Applications can subscribe to these SW services.
*
* @par Errors:
* - EAaConfigRet_PublicFailure
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NoMem
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
* @see AaConfigUnRegisterService
* @see AaConfigSubscribeService
* @see AaConfigUnSubscribeService
* @see AaConfigGetService
* @see AaConfigGetServiceWithTimeout
* @see AaConfigReverseLookupOfService
*
* @par Example:
* @code
*   #define AACONFIG_SERVICE_FAULT "faultHandling"
*   TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                               AaProEuCurrent());
*
*   void exampleFunc(void)
*   {
*     u32 major_version = 1;
*     u32 minor_version = 2;
*     TAaSysComSicad mySicad = AaSysComSicadGet(myCpid, AaSysComGetOwnNid();
*     ret = AaConfigRegisterService(AACONFIG_SERVICE_FAULT_HANDLING,
*                                   major_version,
*                                   minor_version,
*                                   EAaConfigSvcRegScope_CE,
*                                   mySicad);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigRegisterService(const char* const namePtr, const u32 major_version,
                                     const u32 minor_version, EAaConfigSvcRegScope scope, TAaSysComSicad sicad);

/**
********************************************************************************
*
* @brief        AaConfigUnRegisterService unregisters a previously registered service.
*
* @param[in]    namePtr          Pointer to NULL-terminated string containing the service name.
*
* @param[in]    major_version    Major version number of the service.
*
* @param[in]    minor_version    Minor version number of the service.
*
* @return       Function returns status of operation.
*
* @par Description:
* Function \ref AaConfigUnRegisterService is used by sw servers to unregister services.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_PublicFailure
* - EAaConfigRet_NotRegistered
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
* @see AaConfigRegisterService
* @see AaConfigSubscribeService
* @see AaConfigUnSubscribeService
* @see AaConfigGetService
* @see AaConfigGetServiceWithTimeout
* @see AaConfigReverseLookupOfService
*
* @par Example:
* @code
*   #define AACONFIG_SERVICE_FAULT "faultHandling"
*
*   void exampleFunc(void)
*   {
*     u32 major_version = 1;
*     u32 minor_version = 2;
*     ret = AaConfigUnRegisterService(AACONFIG_SERVICE_FAULT_HANDLING,
*                                     major_version,
*                                     minor_version);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigUnRegisterService(const char* const namePtr, const u32 major_version, const u32 minor_version);

/**
********************************************************************************
*
* @brief        AaConfigGetService requests directly the Sicad of a registered service.
*
* @param[in]    namePtr           Pointer to NULL-terminated string containing the service name.
*
* @param[in]    major_version     Major version number of the service.
*
* @param[in]    minor_version     Minor version number of the service or wildcard.
*
* @param[in]    scope             Enumeration value which defines the scope of service get operation.
*
* @param[out]   svcRegGetRsp_ptr  Address of pointer to store list of minor versions and SIC address of services,
*                                 only valid if EAaConfigRet_Ok is returned, otherwise undefined.
*
* @return       Function returns status of operation.
*
* @par Description:
* Function \ref AaConfigGetService is used by applications to get minor version and Sicad of a registered SW services.
* The result is similar to \ref AaConfigSubscribeService but without notification message.
* If 'minor_version' parameter is given as explicit number (not wildcard) only one entry is returned if found.
* The scope argument relates to the location of application calling the API function and registered services.
* If EE/CE scope is selected, application will get all services with matching name and version,
* registered from the same EE/CE as the application making the API call.
* If Global scope is selected, application will get all services with matching name and version.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NoMem
* - EAaConfigRet_NotRegistered: requested service was not found.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* <b>It is user's responsibility to free the memory allocated for returned structure pointer.</b>
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see AaConfigSubscribeService
* @see AaConfigUnSubscribeService
* @see AaConfigRegisterService
* @see AaConfigUnRegisterService
* @see AaConfigGetServiceWithTimeout
* @see AaConfigReverseLookupOfService
*
* @par Example:
* @code
*   #define AACONFIG_SERVICE_FAULT_HANDLING "faultHandling"
*
*   void exampleFunc(void)
*   {
*     u32 major_version = 1;
*     u32 minor_version = AACONFIG_SVC_REG_MINOR_VERSION_WILDCARD;
*     SAaConfigSvcRegGetRes *svcRegGetRsp_ptr;
*     EAaConfigRet ret;
*
*     ret = AaConfigGetService(AACONFIG_SERVICE_FAULT_HANDLING,
*                              major_version,
*                              minor_version,
*                              EAaConfigSvcRegScope_CE,
*                              &svcRegGetRsp_ptr);
*
*     if ((EAaConfigRet_Ok == ret) && (0 != svcRegGetRsp_ptr->num_services))
*     {
*       for (i=0; i<svcRegGetRsp_ptr->num_services; i++)
*       {
*         //svcRegGetRsp_ptr->service[i].minor_version,
*         //svcRegGetRsp_ptr->service[i].sicad);
*       }
*       AaMemUnRef((void const **)&svcRegGetRsp_ptr);
*     }
*     else
*     {
*     //error
*     }
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigGetService(const char* const namePtr, const u32 major_version,
                                const u32 minor_version, EAaConfigSvcRegScope scope,
                                SAaConfigSvcRegGetRes **svcRegGetRsp_ptr);

/**
********************************************************************************
*
* @brief        AaConfigGetServiceWithTimeout requests the Sicad of a registered service.
*
* @param[in]    namePtr           Pointer to NULL-terminated string containing the service name.
*
* @param[in]    major_version     Major version number of the service.
*
* @param[in]    minor_version     Minor version number of the service or wildcard.
*
* @param[in]    scope             Enumeration value which defines the visibility of the service.
*
* @param[in]    timeout           Timeout value [msec] which defines the maximum wait time (0 = infinite).
*
* @param[out]   svcRegGetRsp_ptr  Address of pointer to store list of minor versions and SIC address of services,
*                                 only valid if EAaConfigRet_Ok is returned, otherwise undefined.
*
* @return       Function returns status of operation.
*
* @par Description:
* Function \ref AaConfigGetServiceWithTimeout is used by applications to get minor version and Sicad of a registered services.
* The result is similar to \ref AaConfigSubscribeService but without notification message.
* If 'minor_version' parameter is given as explicit number (not wildcard) only one entry is returned if found.
* If there are no services with matching name, major version and minor version (can be the wildcard) in given scope
* the return from the API call is delayed until timeout expires or there is a matching service available.
* The scope argument relates to the location of application calling the API function and registered services.
* If EE/CE scope is selected, application will get all services with matching name and version,
* registered from the same EE/CE as the application making the API call.
* If Global scope is selected, application will get all services with matching name and version.
* The unit of timeout value is msec and the range is 1..4294967295, 0 means infinite wait.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NoMem
* - EAaConfigRet_NotRegistered: requested service was not found.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* <b>It is user's responsibility to free the memory allocated for returned structure pointer.</b>
* Timeout value AACONFIG_SVC_REG_TIMER_INFINITE means infinite wait for response.
*
* This is a blocking function call!
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see AaConfigSubscribeService
* @see AaConfigUnSubscribeService
* @see AaConfigRegisterService
* @see AaConfigUnRegisterService
* @see AaConfigGetService
* @see AaConfigReverseLookupOfService
*
* @par Example:
* @code
*   #define AACONFIG_SERVICE_FAULT_HANDLING "faultHandling"
*
*   void exampleFunc(void)
*   {
*     u32 major_version = 1;
*     u32 minor_version = AACONFIG_SVC_REG_MINOR_VERSION_WILDCARD;
*     SAaConfigSvcRegGetRes *svcRegGetRsp_ptr;
*     EAaConfigRet ret;
*     TAaSysTime timeout = 1000;
*
*     ret = AaConfigGetServiceWithTimeout(AACONFIG_SERVICE_FAULT_HANDLING,
*                                         major_version,
*                                         minor_version,
*                                         EAaConfigSvcRegScope_CE,
*                                         timeout,
*                                         &svcRegGetRsp_ptr);
*
*     if ((EAaConfigRet_Ok == ret) && (0 != svcRegGetRsp_ptr->num_services))
*     {
*       for (i=0; i<svcRegGetRsp_ptr->num_services; i++)
*       {
*         //svcRegGetRsp_ptr->service[i].minor_version,
*         //svcRegGetRsp_ptr->service[i].sicad);
*       }
*       AaMemUnRef((void const **)&svcRegGetRsp_ptr);
*     }
*     else
*     {
*     //error handling
*     }
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigGetServiceWithTimeout(const char* const namePtr, const u32 major_version,
                                           const u32 minor_version, const EAaConfigSvcRegScope scope,
                                           const TAaSysTime timeout, SAaConfigSvcRegGetRes **svcRegGetRsp_ptr);

/**
********************************************************************************
*
* @brief        AaConfigReverseLookupOfService requests a list of services which have been registered by certain SIC address.
*
* @param[in]    sicad             SIC address of the service.
*
* @param[out]   revLookupRsp_ptr  Address of pointer to store list of service name, minor version, major version scope of services,
*                                 only valid if EAaConfigRet_Ok is returned, otherwise undefined.
*
* @return       Function returns status of operation.
*
* @par Description:
* Function \ref AaConfigReverseLookupOfService is used by applications to get a list of registered SW services.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NoMem
* - EAaConfigRet_NotRegistered: no service was found.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* <b>It is user's responsibility to free the memory allocated for returned structure pointer.</b>
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see AaConfigSubscribeService
* @see AaConfigUnSubscribeService
* @see AaConfigRegisterService
* @see AaConfigUnRegisterService
* @see AaConfigGetService
* @see AaConfigGetServiceWithTimeout
*
* @par Example:
* @code
*
*   void exampleFunc(void)
*   {
*     TAaSysComSicad sicad = 0x1011140A;
*     SAaConfigReverseLookupRes *revLookupRsp_ptr;
*     EAaConfigRet ret;
*
*     ret = AaConfigReverseLookupOfService(sicad, &revLookupRsp_ptr);
*
*     if ((EAaConfigRet_Ok == ret) && (0 != revLookupRsp_ptr->num_services))
*     {
*       for (i=0; i<revLookupRsp_ptr->num_services; i++)
*       {
*         //revLookupRsp_ptr->service[i].name,
*         //revLookupRsp_ptr->service[i].major_version,
*         //revLookupRsp_ptr->service[i].minor_version,
*         //revLookupRsp_ptr->service[i].scope);
*       }
*       AaMemUnRef((void const **)&revLookupRsp_ptr);
*     }
*     else
*     {
*     //error handling
*     }
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigReverseLookupOfService(TAaSysComSicad sicad, SAaConfigReverseLookupRes **revLookupRsp_ptr);

/**
********************************************************************************
*
* @brief        AaConfigSvcRegIsReady tells if service registry is ready.
*
* @return       GLO_TRUE if service is ready.
*
* @par Description:
* Applications which intend to register or subscribe in a very early phase can use this function to get the
* information if service registry is ready.
*
* @par Errors:
* No errors are defined.
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
* @par Example:
* @code
*
*   while(!AaConfigSvcRegIsReady())
*   {
*     AaSysTimeSleep(200, EAaSysTimeScale_Millisec);
*   }
* @endcode
*
*******************************************************************************/
TBoolean AaConfigSvcRegIsReady(void);

/**
********************************************************************************
*
* @brief        AaConfigSvcRegIsLocalReady tells if service registry is ready (EE and CE scope at least).
*
* @return       GLO_TRUE if service is ready.
*
* @par Description:
* Applications which intend to register or subscribe in a very early phase can use this function to get the
* information if service registry is ready for EE and CE scope at least.
*
* @par Errors:
* No errors are defined.
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
* @par Example:
* @code
*
*   while(!AaConfigSvcRegIsLocalReady())
*   {
*     AaSysTimeSleep(200, EAaSysTimeScale_Millisec);
*   }
* @endcode
*
*******************************************************************************/
TBoolean AaConfigSvcRegIsLocalReady(void);

/**
********************************************************************************
*
* @brief        AaConfigSvcEeStartup performs AaConfigSvcReg startup.
*
* @return
*
* @par Description:
* Function performs AaConfigSvcReg startup when all of the needed
* preconditions are fulfilled. The function needs to be called in
* DSP environment before any usage of AaConfigSvcReg interface
* functions on the given core. On MCU there is no need to call
* this function, because AaConfigSvc is started by default.
* The required preconditions:
* - AaConfig startup is done and MASTERNID is set for the given core.
* - AaSysMb is running on the given core.
*
* @par Errors:
* No errors are defined.
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
* @par Example:
* @code
*
* @endcode
*
*******************************************************************************/
void AaConfigSvcEeStartup(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_COMMON_IF_AACONFIG_SVC_REG_H_
