/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AACONFIG_RAD_H_
#define _MCU_IF_AACONFIG_RAD_H_

#include <CcsCommon.h>

#include <IfAaSysCom_Defs.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../../COMMON/ServiceInterface/IfAaConfigRad.h>
#include <../../SHARED/MCU_LITE_RT/ServiceInterface/IfAaConfigRad.h>
#endif



#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigRadApiMcu AaConfigRad MCU functions
 * @ingroup dgAaConfigRadApi
 */
/*@{*/

/**
*******************************************************************************
*
*   @brief    Gets requested R&D parameters values for given domain set globally
*
*   @param[in]        domain       The requested R&D parameters domain identifier
*   @param[in,out]    numOfParams  Number of parameters
*   @param[in,out]    params       Parameters with values
*
*   @return  Status of get operation
*
*   @par Description:
*   The function returns requested R&D parameters with values set globally.\n
*   Globally in this context means common values set at BTS level on all nodes.\n
*   - If numOfParams is set to @ref AACONFIG_RAD_PARAMS_ALL, all R&D parameters from given domain are requested
*   and params argument shall point to GLO_NULL.\n
*   In this case, function implementation allocates memory to store R&D parameters data.\n
*   The owneship of allocated memory is transfered to application and it is application resposibility to release the memory.\n
*   - If numOfParams is != @ref AACONFIG_RAD_PARAMS_ALL, params argument must point to a valid table of SAaConfigRadParamData elements
*   and function fills in requested R&D parameters data based on indexes set in SAaConfigRadParamData elements table.
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one of input parameters is invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - getting of R&D parameters has failed
*
*   @par Restrictions:
*   The function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   The function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, getting of R&D parameters will fail.\n
*
*   @par Examples:
*   Requesting all R&D parameters inside domain.
*
*   @code
*   u32 numberOfParams = AACONFIG_RAD_PARAMS_ALL;
*   SAaConfigRadParamData* params = GLO_NULL;
*   EAaConfigRet result = AaConfigRadGetGlobalValues(
*                           ERadSwDomain_Ccs, &numberOfParams, &params);
*   if (EAaConfigRet_Ok == result && GLO_NULL != params)
*   {
*      u32 paramIndex = 0;
*      for (; paramIndex < numberOfParams; paramIndex++)
*      {
*         //Do the parameter handling ...
*         //...
*      }
*      AaMemUnref((const void**)&params);
*   }
*   @endcode
*
*   Requesting specific R&D parameters
*
*   @code
*   #define NUMBER_OF_PARAMS 2
*   u32 numberOfParams = NUMBER_OF_PARAMS;
*   SAaConfigRadParamData params[NUMBER_OF_PARAMS];
*   memset(&params, 0, sizeof(params));
*   params[0].index = GET_RAD_INDEX(ERadCcs_AaSysLogInputLevel);
*   params[1].index = GET_RAD_INDEX(ERadCcs_AaSysLogOutputLevel);
*
*   EAaConfigRet result = AaConfigRadGetGlobalValues(
*                           ERadSwDomain_Ccs, &numberOfParams, &params);
*   if (EAaConfigRet_Ok == result)
*   {
*      u32 paramIndex = 0;
*      for (; paramIndex < numberOfParams; paramIndex++)
*      {
*         //Do the parameter handling ...
*         //...
*      }
*   }
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalNonDefaults
*   @see AaConfigRadGetLocalValues
*   @see AaConfigRadGetLocalNonDefaults
*   @see AaConfigRadSetGlobalValues
*   @see AaConfigRadSetLocalValues
*   @see AaConfigRadRestoreGlobalDefaults
*   @see AaConfigRadRestoreLocalDefaults
*   @see AaConfigRadRestoreDomainGlobalDefaults
*   @see AaConfigRadRestoreDomainLocalDefaults
*   @see AaConfigRadRestoreAllDomainsGlobalDefaults
*   @see AaConfigRadRestoreAllDomainsLocalDefaults
*
******************************************************************************/
EAaConfigRet AaConfigRadGetGlobalValues(ERadSwDomain domain, u32 *numOfParams, SAaConfigRadParamData **params);

/**
*******************************************************************************
*
*   @brief    Gets requested R&D parameters for given domain, with values set locally on given node
*
*   @param[in]        domain       The requested R&D parameters domain identifier
*   @param[in]        node         The node from which local parameters values are get
*   @param[in,out]    numOfParams  Number of parameters
*   @param[in,out]    params       Parameters with values
*
*   @return  Status of get operation
*
*   @par Description:
*   The function returns requested R&D parameters with values set locally on given node.\n
*   - If numOfParams is set to @ref AACONFIG_RAD_PARAMS_ALL, all R&D parameters from given domain are requested
*   and params argument shall point to GLO_NULL.\n
*   In this case, function implementation allocates memory to store R&D parameters data.\n
*   The owneship of allocated memory is transfered to application and it is application resposibility to release the memory.\n
*   - If numOfParams is != @ref AACONFIG_RAD_PARAMS_ALL, params argument must point to a valid table of SAaConfigRadParamData elements
*   and function fills in requested R&D parameters data based on indexes set in SAaConfigRadParamData elements table.
*
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one of input parameters is invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - getting of R&D parameters has failed
*
*
*   @par Restrictions:
*   If function is called for remote node, the function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   In such case the function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, getting of R&D parameters will fail.\n
*   If the funciton is called for local node, data from local RadSlave instance is read and returned to calling application.\n
*
*   @par Examples:
*   Requesting all R&D parameters inside domain.
*
*   @code
*   u32 numberOfParams = AACONFIG_RAD_PARAMS_ALL;
*   SAaConfigRadParamData* params = GLO_NULL;
*   EAaConfigRet result = AaConfigRadGetLocalValues(
*                           ERadSwDomain_Ccs, AaSysComGetOwnNid(),
*                           &numberOfParams, &params);
*   if (EAaConfigRet_Ok == result && GLO_NULL != params)
*   {
*      u32 paramIndex = 0;
*      for (; paramIndex < numberOfParams; paramIndex++)
*      {
*         //Do the parameter handling ...
*         //...
*      }
*      AaMemUnref((const void**)&params);
*   }
*   @endcode
*
*   Requesting specific R&D parameters
*
*   @code
*   #define NUMBER_OF_PARAMS 2
*   u32 numberOfParams = NUMBER_OF_PARAMS;
*   SAaConfigRadParamData params[NUMBER_OF_PARAMS];
*   memset(&params, 0, sizeof(params));
*   params[0].index = GET_RAD_INDEX(ERadCcs_AaSysLogInputLevel);
*   params[1].index = GET_RAD_INDEX(ERadCcs_AaSysLogOutputLevel);
*
*   EAaConfigRet result = AaConfigRadGetLocalValues(
*                           ERadSwDomain_Ccs, AaSysComGetOwnNid(),
*                           &numberOfParams, &params);
*   if (EAaConfigRet_Ok == result)
*   {
*      u32 paramIndex = 0;
*      for (; paramIndex < numberOfParams; paramIndex++)
*      {
*         //Do the parameter handling ...
*         //...
*      }
*   }
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalValues
*   @see AaConfigRadGetGlobalNonDefaults
*   @see AaConfigRadGetLocalNonDefaults
*   @see AaConfigRadSetGlobalValues
*   @see AaConfigRadSetLocalValues
*   @see AaConfigRadRestoreGlobalDefaults
*   @see AaConfigRadRestoreLocalDefaults
*   @see AaConfigRadRestoreDomainGlobalDefaults
*   @see AaConfigRadRestoreDomainLocalDefaults
*   @see AaConfigRadRestoreAllDomainsGlobalDefaults
*   @see AaConfigRadRestoreAllDomainsLocalDefaults
*
******************************************************************************/
EAaConfigRet AaConfigRadGetLocalValues(ERadSwDomain domain, TAaSysComNid node,
                                       u32 *numOfParams, SAaConfigRadParamData **params);


/**
*******************************************************************************
*
*   @brief    Gets R&D parameters for given domain with non-default values set globally
*
*   @param[in]     domain       The requested R&D parameters domain identifier
*   @param[out]    numOfParams  Number of parameters with non-default value
*   @param[out]    params       Parameters with non-default values
*
*   @return  Status of get operation
*
*   @par Description:
*   The function returns R&D parameters with non-deafult values set globally.\n
*   Globally in this context means common values set at BTS level on all nodes.\n
*   Each node may also have local non-default settings which can be get using
*   @ref AaConfigRadGetLocalNonDefaults function.\n
*   The function implementation allocates memory to store R&D parameters value.\n
*   The owneship of allocated memory is transfered to application and it is application resposibility to release the memory.\n
*
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one of input parameters is invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - getting of R&D parameters has failed
*
*
*   @par Restrictions:
*   The function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   The function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, getting of R&D parameters will fail.\n
*
*   @par Example:
*
*   @code
*
*   u32 numberOfParams;
*   SAaConfigRadParamData* params = GLO_NULL;
*   EAaConfigRet result = AaConfigRadGetGlobalNonDefaults(
*                           ERadSwDomain_Ccs, &numberOfParams, &params);
*   if (EAaConfigRet_Ok == result && GLO_NULL != params)
*   {
*      u32 paramIndex = 0;
*      for (; paramIndex < numberOfParams; paramIndex++)
*      {
*         //Do the parameter handling ...
*         //...
*      }
*      AaMemUnref((const void**)&params);
*   }
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalValues
*   @see AaConfigRadGetLocalValues
*   @see AaConfigRadGetLocalNonDefaults
*   @see AaConfigRadSetGlobalValues
*   @see AaConfigRadSetLocalValues
*   @see AaConfigRadRestoreGlobalDefaults
*   @see AaConfigRadRestoreLocalDefaults
*   @see AaConfigRadRestoreDomainGlobalDefaults
*   @see AaConfigRadRestoreDomainLocalDefaults
*   @see AaConfigRadRestoreAllDomainsGlobalDefaults
*   @see AaConfigRadRestoreAllDomainsLocalDefaults
*
******************************************************************************/
EAaConfigRet AaConfigRadGetGlobalNonDefaults(ERadSwDomain domain, u32 *numOfParams, SAaConfigRadParamData **params);

/**
*******************************************************************************
*
*   @brief    Gets R&D parameters for given domain, with non-default values set locally on given node
*
*   @param[in]     domain       The requested R&D parameters domain identifier
*   @param[in]     node         The node from which local, non-default parameters are get
*   @param[out]    numOfParams  Number of parameters with non-default value
*   @param[out]    params       Parameters with non-default values
*
*   @return  Status of get operation
*
*   @par Description:
*   The function returns R&D parameters with non-deafult values set locally on given node.\n
*   The function implementation allocates memory to store R&D parameters values.\n
*   The owneship of allocated memory is transfered to application and it is application resposibility to release the memory.\n
*
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one of input parameters is invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - getting of R&D parameters has failed
*
*
*   @par Restrictions:
*   If function is called for remote node, the function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   The function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, getting of R&D parameters will fail.\n
*   If the funciton is called for local node, data from local RadSlave instance is read and returned to calling application.\n

*   @par Example:
*
*   @code
*
*   u32 numberOfParams;
*   SAaConfigRadParamData* params = GLO_NULL;
*   EAaConfigRet result = AaConfigRadGetLocalNonDefaults(
*                           ERadSwDomain_Ccs, AaSysComGetOwnNid(),
*                           &numberOfParams, &params);
*   if (EAaConfigRet_Ok == result && GLO_NULL != params)
*   {
*      u32 paramIndex = 0;
*      for (; paramIndex < numberOfParams; paramIndex++)
*      {
*         //Do the parameter handling ...
*         //...
*      }
*      AaMemUnref((const void**)&params);
*   }
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalValues
*   @see AaConfigRadGetGlobalNonDefaults
*   @see AaConfigRadGetLocalValues
*   @see AaConfigRadSetGlobalValues
*   @see AaConfigRadSetLocalValues
*   @see AaConfigRadRestoreGlobalDefaults
*   @see AaConfigRadRestoreLocalDefaults
*   @see AaConfigRadRestoreDomainGlobalDefaults
*   @see AaConfigRadRestoreDomainLocalDefaults
*   @see AaConfigRadRestoreAllDomainsGlobalDefaults
*   @see AaConfigRadRestoreAllDomainsLocalDefaults
*
******************************************************************************/
EAaConfigRet AaConfigRadGetLocalNonDefaults(ERadSwDomain domain, TAaSysComNid node,
                                            u32 *numOfParams, SAaConfigRadParamData **params);

/**
*******************************************************************************
*
*   @brief    Sets given R&D parameters for given domain globally
*
*   @param[in]     persistence     The setting persistence mask.
*   @param[in]     domain          The R&D parameters domain identifier
*   @param[in]     numberOfParams  Number of set R&D parameters
*   @param[in]     params          The set R&D parameters
*
*   @return  Status of set operation
*
*   @par Description:
*   The function sets given R&D parameters for given domain globally.\n
*   Globally in this context means at BTS level, on all available nodes.\n
*   The persistence argument defines how given R&D parameters settings are stored.\n
*   Please note that not all nodes supports persistent and persistent over one reset type of storage.\n
*
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one or more of input parameters are invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - setting of R&D parameters has failed
*
*
*   @par Restrictions:
*   The function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   The function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, setting of R&D parameters will fail.\n
*
*   @par Example:
*
*   @code
*
*     #define NUMBER_OF_PARAMS 2
*     u32 logLevel = 1;
*     SAaConfigRadParams params[NUMBER_OF_PARAMS];
*     params[0].index = GET_RAD_INDEX(ERadCcs_AaSysLogInputLevel);
*     params[0].size = sizeof(logLevel);
*     params[0].value = logLevel;
*     params[1].index = GET_RAD_INDEX(ERadCcs_AaSysLogOutputLevel);
*     params[1].size = sizeof(logLevel);
*     params[1].value = logLevel;
*     EAaConfigRet status = AaConfigRadSetGlobalValues(
*                             EAaConfigRadParamSetMask_Current,
*                             ERadSwDomain_Ccs, NUMBER_OF_PARAMS, params);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalValues
*   @see AaConfigRadGetGlobalNonDefaults
*   @see AaConfigRadGetLocalValues
*   @see AaConfigRadGetLocalNonDefaults
*   @see AaConfigRadSetLocalValues
*   @see AaConfigRadRestoreGlobalDefaults
*   @see AaConfigRadRestoreLocalDefaults
*   @see AaConfigRadRestoreDomainGlobalDefaults
*   @see AaConfigRadRestoreDomainLocalDefaults
*   @see AaConfigRadRestoreAllDomainsGlobalDefaults
*   @see AaConfigRadRestoreAllDomainsLocalDefaults
*
******************************************************************************/
EAaConfigRet AaConfigRadSetGlobalValues(EAaConfigRadParamSetMask persistence, ERadSwDomain domain,
                                        u32 numberOfParams, const SAaConfigRadParams *params);

/**
*******************************************************************************
*
*   @brief    Sets given R&D parameters for given domain locally, on given nodes
*
*   @param[in]     persistence    The setting persistence mask
*   @param[in]     numberOfNodes  The number of setting target nodes
*   @param[in]     nodes          The setting target nodes
*   @param[in]     domain         The set R&D parameters domain identifier
*   @param[in]     numberOfParams The number of set R&D parameters
*   @param[in]     params         The set R&D parameters
*
*   @return  Status of get operation
*
*   @par Description:
*   The function sets given R&D parameters for given domain locally, on given nodes.\n
*   The persistence argument defines how given R&D parameters settings are stored locally.\n
*   Please note that not all nodes supports persistent and persistent over one reset type of storage.\n
*
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one or more of input parameters are invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - setting of R&D parameters has failed
*
*
*   @par Restrictions:
*   The function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   The function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, setting of R&D parameters will fail.\n
*
*   @par Example:
*
*   @code
*
*     #define NUMBER_OF_NODES 1
*     #define NUMBER_OF_PARAMS 2
*     u32 logLevel = 1;
*     TAaSysComNid nodes[NUMBER_OF_NODES];
*     nodes[0] = AaSysComGetOwnNid();
*     SAaConfigRadParams params[NUMBER_OF_PARAMS];
*     params[0].index = GET_RAD_INDEX(ERadCcs_AaSysLogInputLevel);
*     params[0].size = sizeof(logLevel);
*     params[0].value = logLevel;
*     params[1].index = GET_RAD_INDEX(ERadCcs_AaSysLogOutputLevel);
*     params[1].size = sizeof(logLevel);
*     params[1].value = logLevel;
*     EAaConfigRet status = AaConfigRadSetLocalValues(
*                             EAaConfigRadParamSetMask_Current,
*                             NUMBER_OF_NODES, nodes, ERadSwDomain_Ccs,
*                             NUMBER_OF_PARAMS, params);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalValues
*   @see AaConfigRadGetGlobalNonDefaults
*   @see AaConfigRadGetLocalValues
*   @see AaConfigRadGetLocalNonDefaults
*   @see AaConfigRadSetGlobalValues
*   @see AaConfigRadRestoreGlobalDefaults
*   @see AaConfigRadRestoreLocalDefaults
*   @see AaConfigRadRestoreDomainGlobalDefaults
*   @see AaConfigRadRestoreDomainLocalDefaults
*   @see AaConfigRadRestoreAllDomainsGlobalDefaults
*   @see AaConfigRadRestoreAllDomainsLocalDefaults
*
******************************************************************************/
EAaConfigRet AaConfigRadSetLocalValues(EAaConfigRadParamSetMask persistence, u32 numberOfNodes, const TAaSysComNid *nodes,
                                       ERadSwDomain domain, u32 numberOfParams, const SAaConfigRadParams *params);

/**
*******************************************************************************
*
*   @brief    Restores given R&D parameters settings for given domain to factory defaults, globally.
*
*   @param[in]     persistence    The restore persistence mask
*   @param[in]     domain         The restored R&D parameters domain identifier
*   @param[in]     numberOfParams The number of restored R&D parameters
*   @param[in]     params         Indexes of restored R&D parameters
*
*   @return  Status of restore operation
*
*   @par Description:
*   The function restores given R&D parameters settings for given domain to factory defaults, globally.\n
*   Globally in this context means at BTS level, on all available nodes.\n
*   The persistence argument defines which R&D parameters storage is cleared.\n
*   Please note that not all nodes supports persistent and persistent over one reset type of storage.\n
*
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one or more of input parameters are invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - setting of R&D parameters has failed
*
*
*   @par Restrictions:
*   The function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   The function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, restoring of R&D parameters will fail.\n
*
*   @par Example:
*
*   @code
*
*     #define NUMBER_OF_PARAMS 2
*     u32 params[NUMBER_OF_PARAMS];
*     params[0] = GET_RAD_INDEX(ERadCcs_AaSysLogInputLevel);
*     params[1] = GET_RAD_INDEX(ERadCcs_AaSysLogOutputLevel);
*     EAaConfigRet status = AaConfigRadRestoreGlobalDefaults(
*                             EAaConfigRadParamSetMask_Current,
*                             ERadSwDomain_Ccs, NUMBER_OF_PARAMS, params);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalValues
*   @see AaConfigRadGetGlobalNonDefaults
*   @see AaConfigRadGetLocalValues
*   @see AaConfigRadGetLocalNonDefaults
*   @see AaConfigRadSetGlobalValues
*   @see AaConfigRadSetLocalValues
*   @see AaConfigRadRestoreLocalDefaults
*   @see AaConfigRadRestoreDomainGlobalDefaults
*   @see AaConfigRadRestoreDomainLocalDefaults
*   @see AaConfigRadRestoreAllDomainsGlobalDefaults
*   @see AaConfigRadRestoreAllDomainsLocalDefaults
*
******************************************************************************/
EAaConfigRet AaConfigRadRestoreGlobalDefaults(EAaConfigRadParamSetMask persistence, ERadSwDomain domain,
                                              u32 numberOfParams, const u32 *params);

/**
*******************************************************************************
*
*   @brief    Restores given R&D parameters settings for given domain to factory defaults, locally on given nodes
*
*   @param[in]     persistence    The restore persistence mask
*   @param[in]     numberOfNodes  The number of restore target nodes
*   @param[in]     nodes          The restore target nodes
*   @param[in]     domain         The restore R&D parameters domain identifier
*   @param[in]     numberOfParams The number of restored R&D parameters
*   @param[in]     params         The indexes of restored R&D parameters
*
*   @return  Status of restore operation
*
*   @par Description:
*   The function restores given R&D parameters for given domain, locally on given nodes.\n
*   The persistence argument defines which R&D parameters storage is cleared.\n
*   Please note that not all nodes supports persistent and persistent over one reset type of storage.\n
*
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one or more of input parameters are invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - setting of R&D parameters has failed
*
*
*   @par Restrictions:
*   The function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   The function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, restoring of R&D parameters will fail.\n
*
*   @par Example:
*
*   @code
*
*     #define NUMBER_OF_PARAMS 2
*     #define NUMBER_OF_NODES 1
*     TAaSysComNid nodes[NUMBER_OF_NODES];
*     nodes[0] = AaSysComGetOwnNid();
*     u32 params[NUMBER_OF_PARAMS];
*     params[0] = GET_RAD_INDEX(ERadCcs_AaSysLogInputLevel);
*     params[1] = GET_RAD_INDEX(ERadCcs_AaSysLogOutputLevel);
*     EAaConfigRet status = AaConfigRadRestoreLocalDefaults(
*                             EAaConfigRadParamSetMask_Current,
*                             NUMBER_OF_NODES, nodes, ERadSwDomain_Ccs,
*                             NUMBER_OF_PARAMS, params);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalValues
*   @see AaConfigRadGetGlobalNonDefaults
*   @see AaConfigRadGetLocalValues
*   @see AaConfigRadGetLocalNonDefaults
*   @see AaConfigRadSetGlobalValues
*   @see AaConfigRadSetLocalValues
*   @see AaConfigRadRestoreGlobalDefaults
*   @see AaConfigRadRestoreDomainGlobalDefaults
*   @see AaConfigRadRestoreDomainLocalDefaults
*   @see AaConfigRadRestoreAllDomainsGlobalDefaults
*   @see AaConfigRadRestoreAllDomainsLocalDefaults

*
******************************************************************************/
EAaConfigRet AaConfigRadRestoreLocalDefaults(EAaConfigRadParamSetMask persistence, u32 numberOfNodes, const TAaSysComNid *nodes,
                                             ERadSwDomain domain, u32 numberOfParams, const u32 *params);

/**
*******************************************************************************
*
*   @brief    Restores all R&D parameters settings for given domain to factory deafults globally.
*
*   @param[in]     persistence    The restore persistence mask
*   @param[in]     domain         The restored R&D parameters domain identifier
*
*   @return  Status of restore operation
*
*   @par Description:
*   The function restores all R&D parameters setting for given domain to factory defaults, globally.\n
*   Globally in this context means at BTS level, on all available nodes.\n
*   The persistence argument defines which R&D parameters storage is reset.\n
*   Please note that not all nodes supports persistent and persistent over one reset type of storage.\n
*
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one or more of input parameters are invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - setting of R&D parameters has failed
*
*
*   @par Restrictions:
*   The function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   The function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, restoring of R&D parameters will fail.\n
*
*   @par Example:
*
*   @code
*
*     EAaConfigRet status = AaConfigRadRestoreGlobalDefaults(
*                             EAaConfigRadParamSetMask_Current,
*                             ERadSwDomain_Ccs);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalValues
*   @see AaConfigRadGetGlobalNonDefaults
*   @see AaConfigRadGetLocalValues
*   @see AaConfigRadGetLocalNonDefaults
*   @see AaConfigRadSetGlobalValues
*   @see AaConfigRadSetLocalValues
*   @see AaConfigRadRestoreGlobalDefaults
*   @see AaConfigRadRestoreLocalDefaults
*   @see AaConfigRadRestoreDomainLocalDefaults
*   @see AaConfigRadRestoreAllDomainsGlobalDefaults
*   @see AaConfigRadRestoreAllDomainsLocalDefaults
*
******************************************************************************/
EAaConfigRet AaConfigRadRestoreDomainGlobalDefaults(EAaConfigRadParamSetMask persistence, ERadSwDomain domain);

/**
*******************************************************************************
*
*   @brief    Restores all R&D parameters settings for given domain to factory defaults, locally on given nodes
*
*   @param[in]     persistence    The restore persistence mask
*   @param[in]     numberOfNodes  The number of restore target nodes
*   @param[in]     nodes          The restore target nodes
*   @param[in]     domain         The restore R&D parameters domain identifier
*
*   @return  Status of restore operation
*
*   @par Description:
*   The function restores all R&D parameters for given domain locally on given nodes.\n
*   The persistence argument defines which R&D parameters storage is cleared.\n
*   Please note that not all nodes supports persistent and persistent over one reset type of storage.\n
*
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one or more of input parameters are invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - setting of R&D parameters has failed
*
*
*   @par Restrictions:
*   The function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   The function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, restoring of R&D parameters will fail.\n
*
*   @par Example:
*
*   @code
*
*     #define NUMBER_OF_NODES 1
*     TAaSysComNid nodes[NUMBER_OF_NODES];
*     nodes[0] = AaSysComGetOwnNid();
*     EAaConfigRet status = AaConfigRadRestoreDomainLocalDefaults(
*                             EAaConfigRadParamSetMask_Current,
*                             NUMBER_OF_NODES, nodes, ERadSwDomain_Ccs);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalValues
*   @see AaConfigRadGetGlobalNonDefaults
*   @see AaConfigRadGetLocalValues
*   @see AaConfigRadGetLocalNonDefaults
*   @see AaConfigRadSetGlobalValues
*   @see AaConfigRadSetLocalValues
*   @see AaConfigRadRestoreGlobalDefaults
*   @see AaConfigRadRestoreLocalDefaults
*   @see AaConfigRadRestoreDomainGlobalDefaults
*   @see AaConfigRadRestoreAllDomainsGlobalDefaults
*   @see AaConfigRadRestoreAllDomainsLocalDefaults
*
******************************************************************************/
EAaConfigRet AaConfigRadRestoreDomainLocalDefaults(EAaConfigRadParamSetMask persistence, ERadSwDomain domain,
                                                    u32 numberOfNodes, const TAaSysComNid *nodes);

/**
*******************************************************************************
*
*   @brief    Restores all R&D parameters settings to factory deafults, globally.
*
*   @param[in]     persistence    The restore persistence mask
*
*   @return  Status of restore operation
*
*   @par Description:
*   The function restores all R&D parameters settings to factory defaults, globally.
*   Globally in this context means at BTS level, on all available nodes.
*   The persistence argument defines which R&D parameters storage is reset.
*   Please note that not all nodes supports persistent and persistent over one reset type of storage.
*
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one or more of input parameters are invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - setting of R&D parameters has failed
*
*
*   @par Restrictions:
*   The function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   The function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, restoring of R&D parameters will fail.\n
*
*   @par Example:
*
*   @code
*
*     EAaConfigRet status = AaConfigRadRestoreAllDomainsGlobalDefaults(
*                             EAaConfigRadParamSetMask_Current);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalValues
*   @see AaConfigRadGetGlobalNonDefaults
*   @see AaConfigRadGetLocalValues
*   @see AaConfigRadGetLocalNonDefaults
*   @see AaConfigRadSetGlobalValues
*   @see AaConfigRadSetLocalValues
*   @see AaConfigRadRestoreGlobalDefaults
*   @see AaConfigRadRestoreLocalDefaults
*   @see AaConfigRadRestoreDomainGlobalDefaults
*   @see AaConfigRadRestoreDomainLocalDefaults
*   @see AaConfigRadRestoreAllDomainsLocalDefaults

*
******************************************************************************/
EAaConfigRet AaConfigRadRestoreAllDomainsGlobalDefaults(EAaConfigRadParamSetMask persistence);

/**
*******************************************************************************
*
*   @brief    Restores all R&D parameters settings to factory defaults, locally on given nodes
*
*   @param[in]     persistence    The restore persistence mask
*   @param[in]     numberOfNodes  The number of restore target nodes
*   @param[in]     nodes          The restore target nodes
*
*   @return  Status of restore operation
*
*   @par Description:
*   The function restores all R&D parameters to factory defauls locally, on given nodes.\n
*   The persistence argument defines which R&D parameters storage is reset.\n
*   Please note that not all nodes supports persistent and persistent over one reset type of storage.\n
*
*
*   @par Errors:
*   - EAaConfigRet_InvalidParameter - one or more of input parameters are invalid
*   - EAaConfigRet_NotRegistered - given R&D domain is not registered
*   - EAaConfigRet_NoMem - memory buffer/message allocation has failed
*   - EAaConfigRet_Error - setting of R&D parameters has failed
*
*
*   @par Restrictions:
*   The function implementation communicates with RadMaster located on CCS master node using SIC messages.\n
*   The function should be called only from EU having SysCom message queue.\n
*   The calling EU is blocked until the communication with RadMaster is completed.\n
*   If location of RadMaster is not known, i.e. CCS master node is not configured, restoring of R&D parameters will fail.\n
*
*   @par Example:
*
*   @code
*
*     #define NUMBER_OF_NODES 1
*     TAaSysComNid nodes[NUMBER_OF_NODES];
*     nodes[0] = AaSysComGetOwnNid();
*     EAaConfigRet status = AaConfigRadRestoreAllDomainsLocalDefaults(
*                             EAaConfigRadParamSetMask_Current,
*                             NUMBER_OF_NODES, nodes);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see AaConfigRadGetGlobalValues
*   @see AaConfigRadGetGlobalNonDefaults
*   @see AaConfigRadGetLocalValues
*   @see AaConfigRadGetLocalNonDefaults
*   @see AaConfigRadSetGlobalValues
*   @see AaConfigRadSetLocalValues
*   @see AaConfigRadRestoreGlobalDefaults
*   @see AaConfigRadRestoreLocalDefaults
*   @see AaConfigRadRestoreDomainGlobalDefaults
*   @see AaConfigRadRestoreDomainLocalDefaults
*   @see AaConfigRadRestoreAllDomainsGlobalDefaults
*
******************************************************************************/
EAaConfigRet AaConfigRadRestoreAllDomainsLocalDefaults(EAaConfigRadParamSetMask persistence, u32 numberOfNodes, const TAaSysComNid* nodes);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_MCU_IF_AACONFIG_RAD_H_
