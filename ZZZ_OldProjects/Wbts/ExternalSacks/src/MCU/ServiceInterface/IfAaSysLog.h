/** @file
*   @brief Contains AaSysLog API printing interface
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2017, 2019 Nokia. All rights reserved.$
*/

#ifndef _MCU_IFAASYSLOG_H
#define _MCU_IFAASYSLOG_H

#include "CcsCommon.h"
#include <ESysLogSwDomain.h>
#include <IfAaSysLog_Defs.h>
#include "../../COMMON/ServiceInterface/IfAaSysLog.h"
#include "../../SHARED/MCU_RT/ServiceInterface/IfAaSysLog.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 *  * @defgroup dgAaSysLogApiMcu AaSysLog MCU API
 *   * @ingroup dgAaSysLog
 *    */
/*@{*/

/**
*******************************************************************************
*   @brief      Error print severity callback function
*
*   @param[in]  featureIdBuffer Application's buffer
*   @param[in]  runtimeBuffer   Pointer to runtime buffer
*
*
*   @par Description:
*   TAaSysLogErrorPrintCb function:
*   In case that error severity is printed to application's buffer,
*   buffer is dumped to runtime buffer or file.
*
*   @par Errors:
*   If buffer cannot be dumped.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   Here is the usage example for the function:
*/
/**
*   @code
*   EAaSysLogFeatureBufferCbStatus status;
*   if(EAaSysLogSeverityLevel == EAaSysLogSeverityLevel_Error)
*   {
*       if(errorPrintCb != GLO_NULL)
*       {
*           status = errorPrintCb(featureId, featureIdBuffer, runtimeBuffer);
*       }
*       if(status != EAaSysLogFeatureBufferCbStatus_Ok)
*       {
*           / * Application specific error handling. * /
*       }
*   }
*
*   // Definition of function:
*
*   EAaSysLogFeatureBufferCbStatus TAaSysLogErrorPrintCb(CBipoBuffer* featureIdBuffer,
*                                                        CBipoBuffer* runtimeBuffer)
*   {
*       AaSysLogDumpRingBufferToLog(featureIdBuffer, runtimeBuffer);
*
*       //Or:
*
*       AaSysLogDumpRingBufferToFile(featureIdBuffer, "/tmp/debugBufferLog.log");
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
*   @see
*   AaSysLogDumpRingBufferToFile and AaSysLogDumpRingBufferToLog functions.
*
******************************************************************************/
typedef int (*TAaSysLogErrorPrintCb)(void);

/**
*******************************************************************************
*
*   @brief      Function for registering ring buffer with adding to snapshot
*
*   @param[in]  featureId                  Feature identifier (feature flag with related print level)
*   @param[in]  bufferSize                 Size of ring buffer in bytes
*   @param[in]  severityLevel              Input filter for ring buffer with inverted severity logic: feature buffer with DBG severity will only accept prints with severity <= DBG
*   @param[in]  registerIfFeatureFlagSet   if set to true - feature buffer is always registered, if is set to false - feature buffer is registered only in case AaConfigGetRadValue(featureId) == 0
*   @param[in]  dumpFeatureBufferOnErr     if set to true - logs are dumped to runtime buffer in case of Err print with the same feature identifier
*   @param[in]  fileNameInSnapshot         name of the file for dumped logs. If null provided: default name is used: runtime_<binary>_<severity>_<feature flag>.log
*
*   @par Description:
*   Application SW registers a log print ring buffer for specific
*   feature and particular severity level to CC&S AaSysLog service
*   by AaSysLogRegisterRingBufferAndAddToSnapshot API. Feature ring
*   buffer registered via this API is dumped to user file during
*   snapshot request and included in snapshot. Feature ring buffer is not
*   created if print level for Feature flag is set to debug
*   (AaConfigGetRadValue(featureId) == 1) during API
*   function execution and <<registerIfFeatureFlagSet>> is set to false.
*   This is needed to avoid duplicate DUBUG logs from the runtime log
*   and from the feature buffer log. In this situation code
*   EAaSysLogFeatureBufferRegister_NotNeeded is returned and user file is
*   not created and not registered to snapshot.
*   Otherwise ring buffer will be created. All callbacks needed
*   for registering user file to snapshot are not needed from user side.
*   File is unregister from snapshot automatically during calling
*   AaSysLogUnRegisterRingBuffer API for dedicated feature ID.
*   User file <<fileNameInSnapshot>> is register to snapshot with normal priority.
*
*   @return EAaSysLogFeatureBufferRegister
*
*   @par Errors:
*   EAaSysLogFeatureBufferRegister_Exists    -> in case that buffer already exists for given feature ID,
*   EAaSysLogFeatureBufferRegister_NOk       -> in case that buffer can not be allocated,
*   EAaSysLogFeatureBufferRegister_NotNeeded -> in case that <<registerIfFeatureFlagSet>> is set to false and AaConfigGetRadValue(featureId) != 0
*
*
*   @par Restrictions:
*   Buffers are registered on EE level, not CE level.
*
*   @par Example:
*   Example shows how this function can be used by application:
*/
/**
*   @code
*   //Register dumping ring buffer prints to log in case of error print
*   EAaSysLogFeatureBufferRegister ret = AaSysLogRegisterRingBufferAndAddToSnapshot(FEAT_DBG_BTSOM_ALMAG, 51200, EAaSysLogSeverityLevel_Debug, false, false, "userFile.log");
*
*   if( EAaSysLogFeatureBufferRegister_NotNeeded == ret )
*   {
*       dbg_print( MON_SEVERITY_DEBUG, FEAT_DBG_BTSOM_ALMAG,
*                  "DM_ALMAG_init:init() debug buffer not needed - print level for FEAT_DBG_BTSOM_ALMAG set to Debug" );
*   }
*   else if( EAaSysLogFeatureBufferRegister_Ok != ret )
*   {
*       dbg_print( MON_SEVERITY_WARNING, FEAT_DBG_BTSOM_ALMAG,
*                  "DM_ALMAG_init:init() AaSysLogRegisterRingBuffer failed to register BTSOM_ALMAG buffer, ret=%d", ret );
*   }
*   @endcode
*
*   @par Usage:
*   None
*
*   @par Rationale:
*   Functionality introduced with CNI-4693
*
*   @par Future directions:
*   None
*
*   @see
*   AaSysLogRegisterRingBuffer
*   AaSysLogUnRegisterRingBuffer
*
******************************************************************************/
EAaSysLogFeatureBufferRegister AaSysLogRegisterRingBufferAndAddToSnapshot( const u32 featureId,
                                                                           const u32 bufferSize,
                                                                           const EAaSysLogSeverityLevel severityLevel,
                                                                           const TBoolean registerIfFeatureFlagSet,
                                                                           const TBoolean dumpFeatureBufferOnErr,
                                                                           const char* fileNameInSnapshot );

/**
*******************************************************************************
*
*   @brief      Function for registering ring buffer
*
*   @param[in]  featureId               Feature identifier
*   @param[in]  bufferSize              Size of ring buffer
*   @param[in]  severityLevel           Severity level of the print
*   @param[in]  errorPrintCb            Error callback function, which is
*                                       called in case of error severity
*                                       log print.
*
*   @par Description:
*   Application SW registers a log print ring buffer for specific
*   feature and particular severity level to CC&S AaSysLog service
*   by AaSysLogRegisterRingBuffer API.
*
*   @return EAaSysLogFeatureBufferRegister
*
*   @par Errors:
*   EAaSysLogFeatureBufferRegister_Exists -> in case that buffer already exists for given feature ID,
*   EAaSysLogFeatureBufferRegister_NOk    -> in case that buffer can not be allocated.
*
*
*   @par Restrictions:
*   Buffers are registered on EE level, not CE level.
*
*   @par Example:
*   registration debug buffer only, if a corresponding RAD param is set to 0
*   so no buffers are registered if DBG prints are set up in the swconfig.txt
*/
/**
*   @code
*   if ( !AaConfigRadGetValue(FEAT_DBG_BTSOM_ALMAG) )
*   {
*        //Register dumping ring buffer prints to log in case of error print
*        EAaSysLogFeatureBufferRegister ret = AaSysLogRegisterRingBuffer(FEAT_DBG_BTSOM_ALMAG, 51200, EAaSysLogSeverityLevel_Debug, NULL);
*
*        if( EAaSysLogFeatureBufferRegister_Ok != ret )
*        {
*                dbg_print(MON_SEVERITY_WARNING, FEAT_DBG_BTSOM_ALMAG,
*                        "DM_ALMAG_init:init() AaSysLogRegisterRingBuffer failed to register BTSOM_ALMAG buffer, ret=%d", ret );
*        }
*
*        //Register adding ring buffer file to snapshot
*        string fileNameALMAG = "/ram/runtime_BTSOM_DBG_ALMAG.log";
*        dbg_print(MON_SEVERITY_INFO, FEAT_DBG_BTSOM_ALMAG, "DM_ALMAG_init:init() call AaTrblFileRegister(%s)",fileNameALMAG.c_str() );
*        EAaTrblRet fileRegisterRet = AaTrblFileRegister(
*                                                                 fileNameALMAG.c_str(),
*                                                                 fileNameALMAG.c_str(),
*                                                                 EAaTrblFilePriority_Normal,       // present at normal and full snapshot.
*                                                                 GLO_FALSE,
*                                                                 &opAaPrepareFileDefaultCbALMAG,  // callback - Prepare
*                                                                 &opAaStoreFileDefaultCbALMAG,   // callback - Store
*                                                                 &opAaDeleteFileDefaultCbALMAG,   // callback - Delete
*                                                                 NULL);
*        if( EAaTrblRet_Ok != fileRegisterRet )
*        {
*            dbg_print( MON_SEVERITY_WARNING, FEAT_DBG_BTSOM_ALMAG,
*                      "DM_ALMAG_init:init() AaTrblFileRegister failed to register BTSOM_ALMAG buffer, ret=%d", fileRegisterRet );
*        }
*    }
*    //Then all three callbacks registered above:
*
*    EAaTrblCbStatus opAaPrepareFileDefaultCbALMAG(char const * const fileName, const void* opaque)
*    {
*        ....
*    }
*
*    EAaTrblCbStatus opAaStoreFileDefaultCbALMAG(char const * const fileName, const void* opaque)
*    {
*        ....
*    }
*
*    void opAaDeleteFileDefaultCbALMAG(char const * const fileName, const void* opaque)
*    {
*        ....
*    }
*    @endcode
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
*   @see
*   AaSysLogRegisterRingBufferAndAddToSnapshot
*   AaSysLogUnRegisterRingBuffer
*
******************************************************************************/
EAaSysLogFeatureBufferRegister AaSysLogRegisterRingBuffer(const u32                    featureId,
                                                          u32                          bufferSize,
                                                          const EAaSysLogSeverityLevel severityLevel,
                                                          TAaSysLogErrorPrintCb        errorPrintCb);
/**
*******************************************************************************
*
*   @brief      Function that dumps ring buffer to file
*
*   @param[in]  featureId               Feature identifier
*   @param[in]  fileName                Name of file
*
*   @par Description:
*   By calling  AaSysLogDumpRingBufferToFile, application SW starts process
*   of dumping registered ring buffer to a defined file. If errorPrintCb is NULL ,
*   then CC&S dumps automatically feature specific ring buffer to runtime log.
*   If errorPrintCb is not null, then CC&S calls application
*   SW predefined callback function to facilitate application SW
*   predefined actions. By CC&S AaSysLog services AaSysLogDumpRingBufferToLog API
*   or AaSysLogDumpRingBufferToFile API ring buffer is dumped to runtime log or
*   file respectively. Besides, when output level is enabled log prints
*   are forwarded to output device.
*
*   @return EAaSysLogFeatureBufferDumpToFile
*
*   @par Errors:
*   In case that file name is invalid or file cannot be written.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
EAaSysLogFeatureBufferDumpToFile AaSysLogDumpRingBufferToFile(const u32   featureId,
                                                              const char* fileName);

/**
*******************************************************************************
*
*   @brief      Function that dumps ring buffer to runtime log
*
*   @param[in]  featureId               Feature identifier
*
*   @par Description:
*   By calling  AaSysLogDumpRingBufferToLog, application SW starts process
*   of dumping registered ring buffer to a runtime log.
*
*   @return EAaSysLogFeatureBufferDumpToLog
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
EAaSysLogFeatureBufferDumpToLog AaSysLogDumpRingBufferToLog(const u32 featureId);

/**
*******************************************************************************
*
*   @brief      Function for de-registering ring buffer
*
*   @param[in]  featureId               Feature identifier
*
*   @par Description:
*   By calling  AaSysLogUnRegisterRingBuffer, application SW de-registering buffer
*   and memory which was allocated by the ring buffer is freed.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
void AaSysLogUnRegisterRingBuffer(const u32 featureId);

/**
*******************************************************************************
*
*   @brief      Function for registering domain log buffer
*
*   @param[in]  domainID               Domain identifier
*   @param[in]  domainName             Name of the log buffer
*   @param[in]  startupLogSize         Startup log size
*   @param[in]  runtimeLogSize         Runtime log size
*
*   @par Description:
*   By calling AaSysLogRegisterDomainBuffer, application SW registers
*   a log print ring buffer for specific log domain.
*   Size of the startup/runtime log for each SC is defined in
*   WBTS_TEST_14819 Log size budgeting
*   PM_1 and PM_2 log size is defined globally for all SC via
*   CC&S config tag "ccs.service.aasyslog.scpostmortemlogsize"
*
*   NOTE: in case of compression mode (enabled by configuration tag
*         "ccs.service.aasyslog.compression.enabled") runtimeLogSize
*         defines runtime quota for given log domain - i.e. quota for
*         logs stored in runtime buffer and in small chunks compressed
*         with LZ4 and stored in files.
*
*   @return EAaSysLogDomainBufferRegister
*
*   @par Errors:
*   In case that buffer already exists for given domain ID, or in case
*   that buffer can not be allocated.
*
*   @par Restrictions:
*   Minimum runtime log size is 50kB
*
*   @par Example:
*   @code
*   #include <IfAaSysLog.h>
*   #include <ESysLogSwDomain.h>
*
*   ESysLogSwDomain domainID = ESysLogSwDomain_Telecom;
*   char* domainName = "Telecom";
*   u32 startupLogSize = 1024 * 1024;
*   u32 runtimeLogSize = 1024 * 1024;
*   EAaSysLogDomainBufferRegister retval = AaSysLogRegisterDomainBuffer( domainID,
*                                                                        domainName,
*                                                                        startupLogSize,
*                                                                        runtimeLogSize );
*   if( EAaSysLogDomainBufferRegister_Ok == retval ||
*        EAaSysLogDomainBufferRegister_Exists == retval )
*   {
*        AaSyslogSetLogDomain( domainID );
*   }
*   else
*   {
*        AaSysLogPrint( EAaSysLogSeverityLevel_Error, "Domain buffer not registered, reason %d", retval );
*   }
*   @endcode
*
*   @par Usage:
*   If the same log domain is used in more than one SC (EE/process),
*   AaSysLogRegisterDomainBuffer must be called in all of them to avoid race condition.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaSyslogSetLogDomain funtion and EAaSysLogDomainBufferRegister enum
*
******************************************************************************/
EAaSysLogDomainBufferRegister AaSysLogRegisterDomainBuffer(const ESysLogSwDomain domainID,
                                                           const char*           domainName,
                                                           const u32             startupLogSize,
                                                           const u32             runtimeLogSize);

/**
*******************************************************************************
*
*   @brief      Function for setting log domain buffer
*
*   @param[in]  domainID Domain identifier
*
*   @par Description:
*   By calling AaSyslogSetLogDomain, application SW defines the log
*   to which AaSysLog service will store all logs from SC (EE/process).
*   Application SW log prints before the log domain was set are stored
*   in legacy log buffer.
*
*   @return EAaSysLogDomainBufferSet
*
*   @par Errors:
*   In case the domain log buffer was not registered.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
*   @see AaSysLogRegisterDomainBuffer function and EAaSysLogDomainBufferSet enum
*
******************************************************************************/
EAaSysLogDomainBufferSet AaSysLogSetLogDomain(const ESysLogSwDomain domainID);

/**
*******************************************************************************
*
*   @brief      Returns log domain utilization in percentage.
*
*   @param[in]  domainID Domain identifier
*
*   @par Description:
*   This function returns domain log utilization in percentage.
*
*   @return domain utilization in percentage or -1 in case when domain was not registered
*
*   @par Errors:
*   In case the domain log buffer was not registered function return -1.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
*   @see
*
******************************************************************************/
i32 AaSysLogGetLogDomainUtilization(const ESysLogSwDomain domainID);

/**
*******************************************************************************
*
*   @brief Returns domain log Id.
*
*   @par Description:
*   This function returns domain log Id.
*
*   @return ESysLogSwDomain
*
*   @par Errors:
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
*   @see
*
******************************************************************************/
ESysLogSwDomain AaSysLogGetLogDomainId(void);

/**
*******************************************************************************
*
*   @brief Returns log domain name.
*
*   @param[in] domainID Domain identifier
*
*   @par Description:
*   This function returns log domain name.
*
*   @return domain name string
*
*   @par Errors:
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
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
*   @see
*
******************************************************************************/
const char* AaSysLogGetLogDomainName(const ESysLogSwDomain domainID);

/**
*******************************************************************************
*
*   @brief Function for freezing runtime log.
*
*   @par Description:
*   Application can use this function in case where irreversible error has been
*   detected and situation is wanted to be kept safe until next CPU reset. Printing is being disabled until unfreeze.
*
*   @return
*   None
*
*   @par Errors:
*
*   @par Restrictions:
*   Function won't have any effects if the runtime log is already frozen.
*   If runtime compression is enabled print about freeze may not appear.
*   If runtime compression is disabled prints from feature ring buffer dumps may appear during freeze.
*
*   @par Example:
*   None
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
*   @see
*
******************************************************************************/
void AaSysLogFreezeRuntimeLog( void );

/**
*******************************************************************************
*
*   @brief Function for unfreezing runtime log.
*
*   @par Description:
*   Unfreeze runtime log, allowing printing.
*
*   @return
*   None
*
*   @par Errors:
*
*   @par Restrictions:
*   Function won't have any effects if the runtime log isn't frozen.
*
*   @par Example:
*   None
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
*   @see
*
******************************************************************************/
void AaSysLogUnfreezeRuntimeLog( void );

/**
*******************************************************************************
*
*   @brief      Function for registering system feature log
*
*   @param[in]  featureId               Feature identifier
*   @param[in]  fileName                Name of the log buffer, file format systemlog_<fileName>_<sequenceNumber>.log
*   @param[in]  logSize                 System log single file size.
*                                       When the maximum file size is reached file is compressed and closed.
*   @param[in]  logCount                Number of stored system log files.
*                                       When the maximum number of stored files is reached last file is removed.
*                                       First file is always preserved
*   @param[in]  waitForResponse         Defines if API should wait for AaSysLog on masterNid to response.
*                                       Waiting may block the function until buffer is registered on master side.
*
*   @par Description:
*   By calling AaSysLogRegisterSystemFeatureBuffer, application SW registers
*   a system log print buffer for specific system log prints;
*   Application can add prints to system feature log by calling AaSysLogSystemPrint and specifying registered feature id.
*   NOTE: If specified system feature log buffer is not registered prints will be added to generic system log.
*
*   On system startup logs from directory: pm_2 will be removed, pm_1 will be renamed to pm_2 and from runtime moved to pm_1.
*   System log file format: systemlog_<fileName>_<sequenceNumber>.log
*   During snapshot collection all systemlog_<fileName>_<sequenceNumber>.log files are merged.
*   and all files are added to already existing registered AaSysLog files: runtime.zip, pm_1_syslog.zip and pm_2_syslog.zip
*   System logs from passive partition will be added to pm_syslog_stb.zip
*
*   NOTE: System buffer has a common configuration with generic system buffer
*         Common parameters:
*         ccs.service.aasyslog.system.log.path
*         ccs.service.aasyslog.system.log.path_stb
*         ccs.service.aasyslog.system.log.time.window
*         ccs.service.aasyslog.system.log.time.window.size
*
*   If API is called with waitForResponse=GLO_FALSE, then any errors on master AaSysLog side are NOT reported by this functions return.
*
*   @return EAaSysLogSystemFeatureBufferRegister
*
*   @par Errors:
*   In case that buffer already exists for given domain ID, or in case
*   that buffer can not be allocated.
*
*   @par Restrictions:
*   Buffer can only be registered after master node Id is set.
*   Function shouldn't be called with parameter waitForResponse set to GLO_TRUE in critical sections or interrupts, as it may cause delays.
*
*   @par Example:
*   @code
*
*   const u32 logSize = 1024 * 256;
*   const u32 logCount = 4;
*   EAaSysLogSystemFeatureBufferRegister retval = AaSysLogRegisterSystemFeatureBuffer( ERadCcs_PrintAaSysTime,
*                                                                                      "AaSysTime",
*                                                                                      logSize,
*                                                                                      logCount,
*                                                                                      GLO_TRUE );
*   if( EAaSysLogSystemFeatureBufferRegister_Ok != retval && EAaSysLogSystemFeatureBufferRegister_Exists == retval )
*   {
*        AaSysLogPrint( EAaSysLogSeverityLevel_Error, "Domain buffer not registered, reason %d", retval );
*        return;
*   }
*   AaSysLogSystemPrint(EAaSysLogSystemSeverityLevel_Info, ERadCcs_PrintAaSysTime, "Time source set");
*   Output:
*   systemlog_AaSysTime_1.log
*   00 FCT-1011-B-CCS <2015-10-06T09:24:01.983257Z> 2C8D-SysTIme SYSTEM_INF/CCS/AaSysTime, Time source set
*

*   @endcode
*
*   @par Usage:
*   If the same log domain is used in more than one SC (EE/process),
*   AaSysLogRegisterSystemFeatureBuffer must be called in all of them to avoid race condition.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
******************************************************************************/

EAaSysLogSystemFeatureBufferRegister AaSysLogRegisterSystemFeatureBuffer(const u32      featureId,
                                                                         const char*    fileName,
                                                                         const u32      logSize,
                                                                         const u32      logCount,
                                                                         const TBoolean waitForResponse);
/*@}*/

#ifdef __cplusplus
}
#endif

#endif /*  _MCU_IFAASYSLOG_H */
