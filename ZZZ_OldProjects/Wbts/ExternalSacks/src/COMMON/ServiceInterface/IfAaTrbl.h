/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AATRBL_H_
#define _COMMON_IF_AATRBL_H_

#include <CcsCommon.h>
#include <glo_def.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaTrbl_Defs.h>
#endif

/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
* @defgroup dgAaTrbl Trouble shooting data collection service (AaTrbl)
* @ingroup dgBasicComputingSw
*
* Common Computer and Support SW Trouble shooting data collection (AaTrbl) Service.
*
* Trouble shooting data collection service (AaTrbl) offers a means to collect
* technical logs and postmortems. API can be divided into two parts:
* - Function API provides interface for application to register technical log
* files for Technical log master usage.
* - Message API provides interface for client to freeze files and to command
* them to be stored to filesystem.
* Application uses Function API to register files and handling callback
* functions to AaTrbl service. Technical log master uses message API to
* request freezing files, storing them into filesystem and deleting needless
* files from filesystem.
*
* API specification (current):
* https://pi.inside.nokiasiemensnetworks.com/urn.htm?id=09006c37810e01ca&DMW_DOCBASE=espoo11&auth=T&version=current&document_id=13-528660
*
* CC&S Wiki for AaTrbl:
* http://wikis.inside.nokiasiemensnetworks.com/bin/view/CSSWiki/AaTrbl
*/

/**
*@defgroup dgAaTrblConfigurationTags Configuration tags
*@ingroup dgAaTrbl
*
* Runtime configuration can be divided into pre- and post-configuration phases.
* Pre-configuration takes place before CE startup has been done for a service.
* Post-configuration takes place after CE, EE and EU startup. Configuration is
* handled using so called configuration tags. Data and keys are variable
* width in size so they are quite flexible to use.
* \n\n
* Usually configuration tags are used for input direction i.e. feeding
* configuration to CC&S service. However some tags can also be used for output
* direction i.e. for advertising CC&S service state or capabilities.
* Configuration tag description should state wether the tag is inteded for
* feeding information (input) to the service or the service uses the tag for
* capability and state advertisement (output).
*
* @verbatim
*  Tag name:        ccs.service.aatrbl.techlogmastersicad
*
*  Direction:       input
*
*  Context:         EE. 
*
*  Description:     Technical log master SIC address. This tag should be set in 
*                   case message broker service is not used for registering. 
*                   AaTrbl sends the registration message to this SIC address.
*  
*  Effect analysis: N/A
*  
*  Restriction:     None.
*  
*  Value:           IE Type:     Size:                      Range:
*                   u32          32 bit                     0...0xFFFFFFFF
*  
*  Define:          AATRBL_CONFIG_TAG_TECHLOGMASTERSICAD
*
*  Example:         -
*  
*  See:             -
* @endverbatim
*
*/

/**
* @defgroup dgAaTrblRdParams R&D parameters
* @ingroup dgAaTrbl
*
* R&D parameters are used for fast runtime variability when execution performance
* is critical and the data must be able to accessed fast. As described in
* Configuration tags, R&D parameters can be used for capability and state advertisement
* too. R&D parameters has fixed size key and data which may limit their usage.
* Memory addresses cannot be transferred portable way using R&D parameters.
*
*
* @ref dsVariation "[CCSAPI_VARIABILITY]"
*
* @verbatim
*  Tag name:        ERadCcs_PrintAaTrbl
*
*  Direction:       input
*
*  Description:     Controls debug prints of AaTrbl service.
*
*  Effect analysis: N/A
*
*  Restriction:     None. 
*
*  Value:           Range:        Description:
*                   1             Debug prints are enabled.
*                   0             Debug prints are disabled. 
*
*  Text:            -
*
*  See:             -
* @endverbatim
*
*/

/**
* @defgroup dgAaTrblApi API
* @ingroup dgAaTrbl
*
* Application Programming Interface.
* https://pi.inside.nokiasiemensnetworks.com/urn.htm?id=09006c37810e01ca&DMW_DOCBASE=espoo11&auth=T&version=current&document_id=13-528660
*
*/
/*@{*/



/**
 * @defgroup dgAaTrblApiCommon AaTrbl COMMON API
 * @ingroup  dgAaTrbl
 */

/* @{ */

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC INTERFACES ----------------------------------*/

/**
********************************************************************************
*
* @brief          Registers a file to AaTrbl service.
*
* @param[in]      logicalFileName    Logical (unique) name of a file to be
*                                    registered.
*
* @param[in]      physicalFileName   Physical name of file to be registered.
*                                    Includes path to file.
*
* @param[in]      priority    Priority of the file. This parameter defines
*                             whether the file is fetched in case Technical log
*                             master requests full or minor coverage of logs.
*
* @param[in]      compressed  Tells whether the file is is compressed by
*                             application when it is stored to filesystem.
*
* @param[in]      prepareCb   Pointer to a callback function that handles
*                             preparing/freezing the file.
*
* @param[in]      storeCb     Pointer to a callback function that handles
*                             storing the file to AaFile service.
*
* @param[in]      deleteCb    Pointer to a callback function that handles
*                             deleting the file from AaFile service.
*
* @param[in,out]  opaque      A pointer to user specified data which is passed
*                             to callback function as argument.
*
* @return         Function returns success of operation.
*
* @par Description:
* Function registers client to AaTrbl service. The prepareCb shall be called
* when Technical log master requests AaTrbl service to freeze a file. The
* storeCb is called when file is requested to be stored to AaFile service. The
* deleteCb shall be called when Technical log master has fetched the file
* and wants to free it.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* - Function should not be used for register file for one shot operation of adding to shapshot.
* - It is forbidden to call AaTrblFileRegister, AaTrblFileRegisterOneShot, AaTrblFileUnregister
*  in prepareCb, storeCb, deleteCb.
*
* @par Usage:
* None
*
* @par Rationale:
* None
*
* @par Future directions:
* None
*
* @see
*  AaTrblFileRegisterOneShot\n
*  AaTrblFileUnregister
*
* @par Example:
* @code
*   #include <IfAaTrbl.h>
*
*   typedef struct CbParams{
*     u32 data;
*     u16 someData;
*   } CbParams;
*
*   EAaTrblCbStatus myPrepareCb(char const * const filename, const void * opaque)
*   {
*     CbParams *params = (CbParams *)opaque;
*     // Freeze and prepare the file
*     ...
*     return EAaTrblCbStatus_Ok;          // if everything is OK
*     //return EAaTrblCbStatus_Nok;       // if error occured
*                                         // (it will cancel entire snapshot)
*     //return EAaTrblCbStatus_NotReady;  // if file is not created
*                                         // (skipp that fille from snapshot)
*   }
*
*   EAaTrblCbStatus myStoreCb(char const * const filename, const void * opaque)
*   {
*     // Handle storing a file to AaFile service
*     ...
*     return EAaTrblCbStatus_Ok;          // if everything is OK
*     //return EAaTrblCbStatus_Nok;       // if error occured
*                                         // (skip that file from snapshot)
*     //return EAaTrblCbStatus_NotReady;  // not use in store callback
*                                         // (not evaluated by AaTrbl)
*   }
*
*   void myDeleteCb(char const * const filename, const void * opaque)
*   {
*     // Handle deleting a file from AaFile service
*   }
*
*   void registerFile(const char *logfilename, const char *physfilename)
*   {
*     EAaTrblRet ret;
*     CbParams *cbParams = malloc(sizeof(CbParams));
*
*     cbParams->data = 0;
*     cbParams->someData = 0x1111;
*
*     ret = AaTrblFileRegister(logfilename,
*                              physfilename,
*                              EAaTrblFilePriority_Normal,
*                              GLO_FALSE,
*                              &myPrepareCb,
*                              &myStoreCb,
*                              &myDeleteCb,
*                              cbParams);
*
*     if (ret != EAaTrblRet_Ok)
*     {
*       // perform error handling
*     }
*   }
* @endcode
*
*******************************************************************************/
EAaTrblRet AaTrblFileRegister(char const * const logicalFileName,
                              char const * const physicalFileName,
                              EAaTrblFilePriority priority,
                              TBoolean compressed,
                              TAaTrblPrepareFileCb * const prepareCb,
                              TAaTrblStoreFileCb * const storeCb,
                              TAaTrblDeleteFileCb * const deleteCb,
                              const void * opaque);

/**
********************************************************************************
*
* @brief          Registers a file to AaTrbl service for one shot operation
*
* @param[in]      logicalFileName    Logical (unique) name of a file to be
*                                    registered.
*
* @param[in]      physicalFileName   Physical name of file to be registered
*                                    Includes path to file.
*
* @param[in]      priority    Priority of the file. This parameter defines
*                             whether the file is fetched in case Technical log
*                             master requests full or minor coverage of logs.
*
* @param[in]      compressed  Tells whether the file is is compressed by
*                             application when it is stored to filesystem.
*
* @param[in]      prepareCb   Pointer to a callback function that handles
*                             preparing/freezing the file.
*
* @param[in]      storeCb     Pointer to a callback function that handles
*                             storing the file to AaFile service.
*
* @param[in]      deleteCb    Pointer to a callback function that handles
*                             deleting the file from AaFile service.
*
* @param[in,out]  opaque      A pointer to user specified data which is passed
*                             to callback function as argument.
*
* @return         Function returns result of the operation: success or error code.
*
* @par Description:
* Function registers client to AaTrbl service. The prepareCb shall be called
* when Technical log master requests AaTrbl service to freeze a file. The
* storeCb is called when file is requested to be stored to AaFile service. The
* deleteCb shall be called when Technical log master has fetched the file
* and wants to free it. After the first usage (called all callbacks and store file in snapshot),
* client is unregistered automatically from AaTrbl service.
*
* @par Errors:
* EAaTrblRet_NotInitialized -> AaTrbl service is not initialized,
* EAaTrblRet_InvalidParameter -> input parameter is incorrect or null,
* EAaTrblRet_MemAllocFailure -> allocating memory failed,
*
* @par Restrictions:
* - Function is usefull only for one shot clients, after calling all callbacks,
*  client is autamatically unregistered. Function is supported only in CCS MCU until further notice.
* - It is forbidden to call AaTrblFileRegister, AaTrblFileRegisterOneShot, AaTrblFileUnregister
*  in prepareCb, storeCb, deleteCb.
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
*  AaTrblFileUnregister\n
*  AaTrblFileRegister
*
* @par Example:
* @code
*   #include <IfAaTrbl.h>
*
*   typedef struct CbParams{
*     u32 data;
*     u16 someData;
*   } CbParams;
*
*   EAaTrblCbStatus myPrepareCb(char const * const filename, const void * opaque)
*   {
*     CbParams *params = (CbParams *)opaque;
*     // Freeze and prepare the file
*     ...
*     return EAaTrblCbStatus_Ok;          // if everything is OK
*     //return EAaTrblCbStatus_Nok;       // if error occured
*                                         // (it will cancel entire snapshot)
*     //return EAaTrblCbStatus_NotReady;  // if file is not created
*                                         // (skipp that fille from snapshot)
*   }
*
*   EAaTrblCbStatus myStoreCb(char const * const filename, const void * opaque)
*   {
*     // Handle storing a file to AaFile service
*     ...
*     return EAaTrblCbStatus_Ok;          // if everything is OK
*     //return EAaTrblCbStatus_Nok;       // if error occured
*                                         // (skip that file from snapshot)
*     //return EAaTrblCbStatus_NotReady;  // not use in store callback
*                                         // (not evaluated by AaTrbl)
*   }
*
*   void myDeleteCb(char const * const filename, const void * opaque)
*   {
*     // Handle deleting a file from AaFile service
*   }
*
*   void registerOneShotFile(const char *logfilename, const char *physfilename)
*   {
*     EAaTrblRet ret;
*     CbParams *cbParams = malloc(sizeof(CbParams));
*
*     cbParams->data = 0;
*     cbParams->someData = 0x1111;
*
*     ret = AaTrblFileRegisterOneShot( logfilename,
*                                      physfilename,
*                                      EAaTrblFilePriority_Normal,
*                                      GLO_FALSE,
*                                      &myPrepareCb,
*                                      &myStoreCb,
*                                      &myDeleteCb,
*                                      cbParams );
*
*     if ( EAaTrblRet_Ok != ret )
*     {
*       // perform error handling
*     }
*   }
* @endcode
*
*******************************************************************************/
EAaTrblRet AaTrblFileRegisterOneShot( char const * const logicalFileName,
                                      char const * const physicalFileName,
                                      EAaTrblFilePriority priority,
                                      TBoolean compressed,
                                      TAaTrblPrepareFileCb * const prepareCb,
                                      TAaTrblStoreFileCb * const storeCb,
                                      TAaTrblDeleteFileCb * const deleteCb,
                                      const void * opaque );
/**
********************************************************************************
*
* @brief        Unregisters a file from AaTrbl service. 
*
* @param[in]    logicalFileName   Logical name of a file to be unregistered. 
*
* @return       Function returns success of operation. 
*
* @par Description:
* Function unregisters a file registered to AaTrbl service.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* File can't be removed	in case it has been locked for transfer (it has been
* requested to be prepared).
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
*  AaTrblFileRegister\n
*  AaTrblFileRegisterOneShot
*
* @par Example:
* @code
*   #include <IfAaTrbl.h>
*
*   void exampleUnreg(const char *logfilename)
*   {
*     EAaTrblRet ret = AaTrblFileUnregister(logfilename); 
* 
*     if(ret == EAaTrblRet_Locked)
*     {
*       AaSysTimeSleep(2, EAaSysTimeScale_Sec);
*       ret = AaTrblFileUnregister(logfilename);
*     }
*   }
* @endcode
*
*******************************************************************************/
EAaTrblRet AaTrblFileUnregister(char const * const logicalFileName);       

/** 
 * @}
 */
   
/*----------------------- INTERNAL INTERFACES --------------------------------*/

/**
********************************************************************************
*
* @brief        AaTrblCeStartup executes CE level startup for AaTrbl service.
*
* @return       Function returns success of operation.
*
* @par Description:
* Function executes executes CE level startup for AaTrbl service.
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
* @see AaTrblCeShutdown
* @see AaTrblEeStartup
* @see AaTrblEeShutdown
*
* @par Example:
*
* @code
*   EAaTrblRet ret = AaTrblCeStartup();
* @endcode
*
*******************************************************************************/
EAaTrblRet AaTrblCeStartup(void);
 
/**
********************************************************************************
*
* @brief        AaTrblCeShutdown executes CE level shutdown.
*
* @return       Function returns success of operation.
*
* @par Description:
* Function executes CE level shutdown for AaTrbl service.
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
* @see AaTrblCeStartup
* @see AaTrblEeStartup
* @see AaTrblEeShutdown
*
* @par Example:
* @code
*   EAaTrblRet ret = AaTrblCeShutdown();
* @endcode
*
*******************************************************************************/
EAaTrblRet AaTrblCeShutdown(void);

/**
********************************************************************************
*
* @brief        AaTrblEeStartup executes EE level startup.
*
* @return       Function returns success of operation.
*
* @par Description:
* Function executes executes EE level startup for AaTrbl service.
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
* @see AaTrblCeStartup
* @see AaTrblCeShutdown
* @see AaTrblEeShutdown
*
* @par Example:
*
* @code
*   EAaTrblRet ret = AaTrblEeStartup();
* @endcode
* 
*******************************************************************************/
EAaTrblRet AaTrblEeStartup(void);

 
/**
********************************************************************************
*
* @brief        AaTrblEeShutdown executes EE level shutdown. 
*
* @return       Function returns success of operation. 
*
* @par Description:
* Function executes EE level shutdown for AaTrbl service. 
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
* @see AaTrblCeStartup
* @see AaTrblCeShutdown
* @see AaTrblEeStartup
*
* @par Example:
* @code
*   EAaTrblRet ret = AaTrblEeShutdown();
* @endcode
*
*******************************************************************************/
EAaTrblRet AaTrblEeShutdown(void);

/**@}*/

#ifdef __cplusplus
}
#endif


#endif /* _COMMON_IF_AATRBL_H_ */
