/** @file
*   @brief Contains AaSysLog Definitions interface
*
*   $Copyright: Copyright 2017,2019 Nokia. All rights reserved.$
*/

#ifndef _IFAASYSLOG_DEFS_H_
#define _IFAASYSLOG_DEFS_H_

#include <CcsCommon.h>
#include <glo_def.h>
#include <IfAaFile_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/*@cond AASYSLOG_NO_DOXYGEN */
#if defined(CCS_LINUX) && !defined(printf)
#define PRINTATTR23 __attribute__((format (printf,2,3))) /**< Force compiler to check arguments acording to printf style */
#define PRINTATTR34 __attribute__((format (printf,3,4))) /**< Force compiler to check arguments acording to printf style */
#define PRINTATTR45 __attribute__((format (printf,4,5))) /**< Force compiler to check arguments acording to printf style */
#define PRINTATTR20 __attribute__((format (printf,2,0))) /**< Force compiler to check arguments acording to printf style */
#define PRINTATTR30 __attribute__((format (printf,3,0))) /**< Force compiler to check arguments acording to printf style */
#define PRINTATTR40 __attribute__((format (printf,4,0))) /**< Force compiler to check arguments acording to printf style */
#else
#define PRINTATTR23
#define PRINTATTR34
#define PRINTATTR45
#define PRINTATTR20
#define PRINTATTR30
#define PRINTATTR40
#endif
/*@endcond */

/**
 *  @brief AaSysLog Communication Point ID.
 */
#define AASYSLOG_CPID                       0x0601
/**
 *  @brief AaSysLog Server Communication Point ID.
 */
#define AASYSLOG_ROUTER_CPID                0x0619

/**
 *  @brief Definitions for IP address size.
 */
#define AASYSLOG_IP_ADDR_SIZE (4)

/*!
 *  @brief  Maximum length of runtime log message file.
 */
#ifdef CCS_OSE
    #define AASYSLOG_MAX_FILE_NAME_LENGTH (48)
#else
    #define AASYSLOG_MAX_FILE_NAME_LENGTH (AAFILE_FILENAME_MAX)
#endif

/*!
 *  @name Configuration IDs.
 */
/*@{*/

/*!
 *  @brief DEFAULT startup.log size
 */
#define AASYSLOG_CONFIG_TAG_STARTUP_LOG_SIZE       "ccs.service.aasyslog.startuplogsize"

/*!
 *  @brief DEFAULT runtime.log size
 */
#define AASYSLOG_CONFIG_TAG_RUNTIME_LOG_SIZE       "ccs.service.aasyslog.runtimelogsize"

/*!
 *  @brief TRSW startup.log size
 */
#define AASYSLOG_CONFIG_TAG_TRSW_STARTUP_LOG_SIZE       "ccs.service.aasyslog.trsw.startuplog.size"

/*!
 *  @brief TRSW runtime.log size
 */
#define AASYSLOG_CONFIG_TAG_TRSW_RUNTIME_LOG_SIZE       "ccs.service.aasyslog.trsw.runtimelog.size"

/*!
 *  @brief DEFAULT pm_1 and pm_2 log size
 */
#define AASYSLOG_CONFIG_TAG_POSTMORTEM_LOG_SIZE    "ccs.service.aasyslog.postmortemlogsize"

/*!
 *  @brief Global quota for SC runtime.log
 */
#define AASYSLOG_CONFIG_TAG_BUFFER_SIZE            "ccs.service.aasyslog.buffersize"

/*!
 *  @brief Percentage of the SC runtime log which is copied to pm_1, pm_2 log
 */
#define AASYSLOG_CONFIG_TAG_SC_POSTMORTEM_LOG_SIZE "ccs.service.aasyslog.scpostmortemlogsize"

#define AASYSLOG_CONFIG_TAG_BUFFER_ADDRESS         "ccs.service.aasyslog.bufferaddress"
#define AASYSLOG_CONFIG_TAG_PRINT_LENGTH           "ccs.service.aasyslog.printlength"
#define AASYSLOG_CONFIG_TAG_PRIORITY               "ccs.service.aasyslog.priority"
#define AASYSLOG_CONFIG_TAG_OUTPUT_MODE            "ccs.service.aasyslog.outputmode"
#define AASYSLOG_CONFIG_TAG_INPUT_LEVEL            "ccs.service.aasyslog.inputlevel"
#define AASYSLOG_CONFIG_TAG_OUTPUT_LEVEL           "ccs.service.aasyslog.outputlevel"
#define AASYSLOG_CONFIG_TAG_UDP_ADDRESS            "ccs.service.aasyslog.udpaddress"
#define AASYSLOG_CONFIG_TAG_UDP_PORT               "ccs.service.aasyslog.udpport"

/*!
 *  @brief SIC address for SIC (3) output mode
 */
#define AASYSLOG_CONFIG_TAG_SIC_ADDRESS            "ccs.service.aasyslog.sicaddress"
#define AASYSLOG_CONFIG_TAG_READY                  "ccs.service.aasyslog.ready"

/*!
 *  @brief SIC address for Local (5) output mode
 */
#define AASYSLOG_CONFIG_TAG_SIC_ADDRESS_LOCAL      "ccs.service.aasyslog.sicaddress.local"

/*!
 *  @brief SIC address for Remote (6) output mode
 */
#define AASYSLOG_CONFIG_TAG_SIC_ADDRESS_REMOTE     "ccs.service.aasyslog.sicaddress.remote"

/*!
 *  @brief Tag which enables LZ4 compression of runtime buffer.
 */
#define AASYSLOG_CONFIG_TAG_COMPRESSION_ENABLED "ccs.service.aasyslog.compression.enabled"

/*!
 *  @brief Percentage of system component runtime budget which is stored in uncompressed format
 *  as runtime cycle buffer. Remaining space of the budget is utilized for storing compressed chunks.
 */
#define AASYSLOG_CONFIG_TAG_COMPRESSION_BUFFER_SIZE "ccs.service.aasyslog.compression.buffersize"

/*!
 *  @brief Size of the runtime chunk to be compressed with LZ4.
 */
#define AASYSLOG_CONFIG_TAG_COMPRESSION_CHUNKSIZE "ccs.service.aasyslog.compression.chunksize"

/*@}*/

/*!
 *  @brief Maximum length of unit in log print
 */
#define AASYSLOG_MAX_UNIT_STRING_LENGTH 16

/*!
 *  @brief      Type for Syslog operation modes.
 *
 *  @note       THIS API IS NOT SUPPORTED BY CC&S RT AND CC&S MCU ANYMORE.\n
 *              PLEASE, REMOVE IT FROM YOUR SOURCE CODE.
 */
typedef enum EAaSysLogOperationMode
{
    /*!
     *  Syslog normal operation mode, Operating System is active and
     *  system is stable. Syslog print interface functions are safe to
     *  be used, Syslog handles single access to shared data.
     */
    EAaSysLogOperationMode_Normal = 0,
    /*!
     *  Syslog limited operation mode, Operating System functions are not
     *  used inside syslog. Single access to print interface functions is
     *  user responsibility to handle.
     *
     *  This mode can also be used if Operating System is not started.
     */
    EAaSysLogOperationMode_Limited = 1,

    /*!
     *  Syslog limited operation mode used during process shutdown,
     *  Operating System functions are not used inside syslog.
     *  Single access to print interface functions is
     *  user responsibility to handle.
     */
    EAaSysLogOperationMode_Shutdown = 2
}EAaSysLogOperationMode;

/**
 *  @brief Type for the syslog print severity levels
 */
typedef enum EAaSysLogSeverityLevel
{
    /**
     *  @brief  Not usable value at anywhere.
     */
    EAaSysLogSeverityLevel_NotValid = 0,
    /**
     *  @brief  Debug severity is used in prints when information is useful
     *          for debugging the application.
     */
    EAaSysLogSeverityLevel_Debug    = 1,
    /**
     *  @brief  Info severity is used in prints for normal operations:
     *          reporting measuring, one time initialization, etc.
     */
    EAaSysLogSeverityLevel_Info     = 2,
    /**
     *  @brief  Warning severity is used to inform minor operation faults that
     *          are recoverable: e.g retransmission required/timeout.
     */
    EAaSysLogSeverityLevel_Warning  = 3,
    /**
     *  @brief  Error severity is used to inform application errors: internal
     *          violations.
     */
    EAaSysLogSeverityLevel_Error    = 4,
    /**
     *  @brief  VIP severity is used Very Import prints. These prints are vital
     *          information: kernel level errors, SW/HW version information, etc.
     */
    EAaSysLogSeverityLevel_Vip      = 5,
    /**
     *  @brief  No Print severity can not be used in print functions. This is
     *          severity to control SysLog functionality.
     */
    EAaSysLogSeverityLevel_NoPrints = 6
}EAaSysLogSeverityLevel;

/**
 *  @brief Type for the syslog print priority levels
 */
typedef enum EAaSysLogPriority
{
    EAaSysLogPriority_01 = 1,
    EAaSysLogPriority_02 = 2,
    EAaSysLogPriority_03 = 3    /**< Highest priority level */
}EAaSysLogPriority;

/*!
 *  @brief      Type for Syslog configuration parameters.
 *
 *  @note       THIS API IS NOT SUPPORTED BY CC&S RT AND CC&S MCU ANYMORE.\n
 *              PLEASE, REMOVE IT FROM YOUR SOURCE CODE.
 */
typedef struct SAaSysLogConfigParams
{
    /*!
     *  Log buffer address, log buffer is used to store prints.
     */
    void* logBufferAddress;
    /*!
     *  Log buffer size in bytes.
     */
    u32   logBufferSize;
    /*!
     *  OS pool number, pool is used for allocations of SysLog
     *  internal work buffers.
     */
    i32   logPoolId;
    /*!
     *  Maximum length of the stored user print, includes print prefix.
     */
    u32   logMaxPrintLen;
    /*!
     *  Unit idenfication string, added to each print prefix.
     */
    char  unitString[AASYSLOG_MAX_UNIT_STRING_LENGTH];
}SAaSysLogConfigParams;

/*!
 *  @brief      A type of device open callback function.
 *
 *  @note       THIS API IS NOT SUPPORTED BY CC&S RT AND CC&S MCU ANYMORE.\n
 *              PLEASE, REMOVE IT FROM YOUR SOURCE CODE.
 *
 *  @param[in]  opaque          Pointer to device instance.
 *
 *  @return     Zero in success, otherwise error.
 */
typedef i32 TAaSysLogDeviceOpenCb(const void* opaque);

/*!
 *  @brief      A type of device close callback function.
 *
 *  @note       THIS API IS NOT SUPPORTED BY CC&S RT AND CC&S MCU ANYMORE.\n
 *              PLEASE, REMOVE IT FROM YOUR SOURCE CODE.
 *
 *  @param[in]  opaque          Pointer to device instance.
 *
 *  @return     Zero in success, otherwise error.
 */
typedef i32 TAaSysLogDeviceCloseCb(const void* opaque);

/*!
 *  @brief      A type of device write callback function.
 *
 *  @note       THIS API IS NOT SUPPORTED BY CC&S RT AND CC&S MCU ANYMORE.\n
 *              PLEASE, REMOVE IT FROM YOUR SOURCE CODE.
 *
 *  @param[in]  opaque          Pointer to device instance.
 *
 *  @return     Written bytes to device or -1 is reserved for device itself
 *              turned off the device.
 */
typedef i32 TAaSysLogDeviceWriteCb(const void* opaque, u32 size, void* ptr);

/**
 *  @brief Type for Syslog output modes
 */
typedef enum EAaSysLogOutputMode
{
    EAaSysLogOutputMode_None             = 0,   /**< Prints are stored only in buffer,
                                                     not forwarded separetely */
    EAaSysLogOutputMode_All              = 1,   /**< Prints are put into the all output
                                                     that has been set */
    EAaSysLogOutputMode_Udp              = 2,   /**< Prints are put into UDP: Broadcast
                                                     or Unicast address */
    EAaSysLogOutputMode_Msg              = 3,   /**< Prints are put into SIC message and
                                                     forwarded to SIC address */
    EAaSysLogOutputMode_Simu             = 4,   /**< Prints are put into c standard io
                                                     output (printf) */
    EAaSysLogOutputMode_Local            = 5,   /**< Prints are sent in local mode,
                                                     interpretation is hardware dependant */
    EAaSysLogOutputMode_Remote           = 6,   /**< Prints are sent in remote mode,
                                                     interpretation is hardware dependant */
    EAaSysLogOutputMode_CompressedLocal  = 7,   /**< Prints are compressed with LZ4 algorithm and then sent in local mode,
                                                     mode available only for Flexi Rel3 */
    EAaSysLogOutputMode_CompressedRemote = 8,   /**< Prints are compressed with LZ4 algorithm and then sent in remote mode,
                                                     mode available only for Flexi Rel3 */
    EAaSysLogOutputMode_NotValid         = 9    /**< Not valid parameter */

}EAaSysLogOutputMode;

/**
 *  @brief Type for Syslog control parameters
 */
typedef struct SAaSysLogCtrlParams
{
    EAaSysLogSeverityLevel inputLevel;       /**< Level of prints that are
                                                  stored to log buffer */
    EAaSysLogSeverityLevel outputLevel;      /**< Level of prints that are
                                                  forwarded to output */
    EAaSysLogOutputMode    outputMode;       /**< Selection of print output */
    u8  targetIpAddr[AASYSLOG_IP_ADDR_SIZE]; /**< IP address where UDP prints
                                                  are sent */
    u32 targetPortNumber;                    /**< UDP port number */
    u32 targetSicAddress;                    /**< SIC address who is handling
                                                  print messages */
}SAaSysLogCtrlParams;

/**
 *  @brief  Type for the syslog configuring status value.
 */
typedef enum EAaSysLogConfigureRetVal
{
    EAaSysLogConfigureRetVal_NoError              = 0,
    EAaSysLogConfigureRetVal_Error                = 1,
    EAaSysLogConfigureRetVal_InvalidParameter     = 2,
    EAaSysLogConfigureRetVal_ResourceNotAvailable = 3,
    EAaSysLogConfigureRetVal_ProcedureOngoing     = 4   // runtime log can't be created in parallel, other procedure is already ongoing
}EAaSysLogConfigureRetVal;

/**
 *  @brief  Type for the syslog buffer load level value.
 */
typedef enum EAaSysLogBufferLoadLevel
{
    EAaSysLogBufferLoadLevel_01 = 1,
    EAaSysLogBufferLoadLevel_02 = 2,
    EAaSysLogBufferLoadLevel_03 = 3,
    EAaSysLogBufferLoadLevel_Full = 4,
    EAaSysLogBufferLoadLevel_NotValid
}EAaSysLogBufferLoadLevel;

/**
 *  @brief  Type for the syslog CPU load level value.
 */
typedef enum EAaSysLogCPULoadLevel
{
    EAaSysLogCPULoadLevel_Normal = 0,
    EAaSysLogCPULoadLevel_High   = 1
}EAaSysLogCPULoadLevel;

/**
 *  @brief Type for the syslog format
 */
typedef enum EAaSysLogLogFormat
{
    /**
     *  @brief NSN proprietary log format
     */
    EAaSysLogLogFormat_Proprietary = 1,
    /**
     *  @brief RFC5424/RFC5425 log format
     */
    EAaSysLogLogFormat_Standard    = 2,
    /**
     *  @brief Last enum
     */
    EAaSysLogLogFormat_Last        = 3

} EAaSysLogLogFormat;

/*@}*/

typedef enum EAaSysLogSystemSeverityLevel
{
    /**
     *  @brief Info severity is used in prints for normal operations: SW Download, Cell Block/Unblock, etc.
     */
    EAaSysLogSystemSeverityLevel_Info = 0,
    /**
     *  @brief  Error severity is used to inform about system errors: Application crash, Lost HW, etc.
     */
    EAaSysLogSystemSeverityLevel_Error = 1,
    /**
     *  @brief  Not a valid value.
     */
    EAaSysLogSystemSeverityLevel_NotValid = 2
}EAaSysLogSystemSeverityLevel;

/*!
 *  @brief SAaSysLogConfigurationInd change indication enum.
 */
typedef enum EAaSysLogConfigurationChangeInd
{
    EAaSysLogConfigurationChangeInd_NoChanges = 0,                      /**< no changes */
    EAaSysLogConfigurationChangeInd_DirectUdpOutputConfiguration = 1    /**< SAaSysLogDirectUdpOutputConfiguration changed */
}EAaSysLogConfigurationChangeInd;

/*!
 *  @brief structure containing direct udp output configuration
 */
typedef struct SAaSysLogDirectUdpOutputConfiguration
{
    /*!
     *  @brief ip address version 6 of destination interface
     */
    u16 ipAddress[8];
    /*!
     *  @brief destination port
     */
    u32 port;
    /*!
     *  @brief dscp
     */
    u32 dscp;
    /*!
     *  @brief ethernet mac address of destination interface
     */
    u8 macAddress[6];
    /*!
     *  @brief explicit message alignment
     */
    u8 empty[2];
}SAaSysLogDirectUdpOutputConfiguration;

#ifdef __cplusplus
}
#endif

#endif /* _IFAASYSLOG_DEFS_H_*/
