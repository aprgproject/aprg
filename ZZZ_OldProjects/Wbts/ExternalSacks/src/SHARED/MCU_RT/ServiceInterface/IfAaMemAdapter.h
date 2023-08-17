/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Memory Management Testability Service API header
* @module                AaMem
* @owner                 Martin Mueller
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAMEMADAPTER_H
#define _MCU_RT_IFAAMEMADAPTER_H
#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief CID of invalid pool ID definition */
#define AAMEM_INVALID_CID 0xFFFF

/** @brief SID of invalid pool ID definition */
#define AAMEM_INVALID_SID 0xFFFF

/** @brief Invalid pool ID definition */
#define AAMEM_INVALID_POOL_ID ((AAMEM_INVALID_CID << 16) | AAMEM_INVALID_SID)

/**
 * @defgroup dgAaMemAdapterAttributeTags Attribute tags
 * @ingroup dgAaMemAdapter
 *
 * Runtime configuration can be divided into pre- and post-configuration phases.
 * Pre-configuration takes place before CE startup has been done for a service.
 * Post-configuration takes place after CE, EE and EU startup. Configuration is
 * handled using so called attribute/configuration tags. Data and keys are variable
 * width in size so they are quite flexible to use.
 * \n\n
 * Usually configuration tags are used for input direction i.e. feeding
 * configuration to CC&S service. However some tags can also be used for output
 * direction i.e. for advertising CC&S service state or capabilities. Configuration
 * tag description should state wether the tag is inteded for feeding information
 * (input) to the service or the service uses the tag for capability and state
 * advertisement (output).
 *
 * @ref dsVariation "[CCSAPI_VARIABILITY]"
 *
 *
 * @verbatim
 *  Tag name:        sys.mem.trace.online
 *
 *  Direction:       output
 *
 *  Context:         EE
 *
 *  Description:     Informs about state of AaMemAdapter availability in the context
 *                   of the current EE
 *
 *  Effect analysis: N/A
 *
 *  Restriction:     Not in use on some environments. See [CCSAPI_VARIABILITY] for more
 *                   details.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u32       1 - AaMemAdapter is up and running
 *                                          0 / not set - AaMemAdapter is down
 *
 *  Define:          AAMEMADAPTER_CONFIG_TAG_TRACE_ONLINE
 *
 *  See:             ccs.service.aamemadapter.enabled
 *  @endverbatim
 *
 *
 * @verbatim
 *  Tag name:        ccs.service.aamemadapter.enabled
 *
 *  Direction:       input
 *
 *  Context:         EE
 *
 *  Description:     Master enablement switch for the service in current EE context.
 *
 *  Effect analysis: If enabled, AaMemAdapter starts up in the current EE, however there
 *                   are other tags, which affect the features of AaMemAdapter.
 *                   Affects also to the state of "sys.mem.trace.online" tag.
 *
 *  Restriction:     Not in use on some systems. See [CCSAPI_VARIABILITY] for more details.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u32       1 - AaMemAdapter service enabled
 *                                          0 / not set - AaMemAdapter service disabled
 *
 *  Define:          AAMEMADAPTER_CONFIG_TAG_MASTER_ENABLE
 *
 *  See:             sys.mem.trace.online
 * @endverbatim
 *
 * @verbatim
 *  Tag name:        ccs.service.aamemadapter.trace.alloc.max.items
 *
 *  Direction:       input
 *
 *  Context:         EE
 *
 *  Description:     Maximum number of allocated memory blocks to be traced at the same time.
 *                   If defined limit is exceeded, the oldest allocation is replaced by the
 *                   new one.
 *
 *  Effect analysis: None
 *
 *  Restriction:     Not in use on some systems. See [CCSAPI_VARIABILITY] for more details.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u32       0 - allocations are not traced at all
 *                                          not set - default value is used
 *
 *  Define:          AAMEMADAPTER_CONFIG_TAG_RT_OBS_STATS_TMO
 *
 *  See:
 * @endverbatim
 *
 * @verbatim
 *  Tag name:        ccs.service.aamemadapter.rtobs.limit.tmo
 *
 *  Direction:       input
 *
 *  Context:         EE
 *
 *  Description:     Timeout for periodic pool limit checking in seconds. If an allocated
 *                   space in a pool exceeds ccs.service.aamemadapter.rtobs.limit.threshold,
 *                   non-fatal exception EAaErrorCcs_AaMemAdapter_PoolExhaust_Error is raised.
 *
 *  Effect analysis: None
 *
 *  Restriction:     Not in use on some systems. See [CCSAPI_VARIABILITY] for more details.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u32       0 / not set - default value is used
 *
 *  Define:          AAMEMADAPTER_CONFIG_TAG_RT_OBS_LIMIT_TMO
 *
 *  See:             ccs.service.aamemadapter.rtobs.limit.threshold
 *  See:             EAaErrorCcs_AaMemAdapter_PoolExhaust_Error
 * @endverbatim
 *
 * @verbatim
 *  Tag name:        ccs.service.aamemadapter.rtobs.enable
 *
 *  Direction:       input
 *
 *  Context:         EE
 *
 *  Description:     Pool statistics and limit observation master enablement switch.
 *
 *  Effect analysis: None
 *
 *  Restriction:     Not in use on some systems. See [CCSAPI_VARIABILITY] for more details.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u32       0 - observations disabled
 *                                          1 - observations enabled
 *                                          not set - default value is used
 *
 *  Define:          AAMEMADAPTER_CONFIG_TAG_RT_OBS_ENABLE
 *
 *  See:             ccs.service.aamemadapter.rtobs.statusdump.syslog.enable
 *  See:             ccs.service.aamemadapter.rtobs.statusdump.file.enable
 * @endverbatim
 *
 * @verbatim
 *  Tag name:        ccs.service.aamemadapter.rtobs.statusdump.syslog.enable
 *
 *  Direction:       input
 *
 *  Context:         EE
 *
 *  Description:     Runtime observation pool statistics dump to SysLog enablement switch.
 *
 *  Effect analysis: None
 *
 *  Restriction:     Not in use on some systems. See [CCSAPI_VARIABILITY] for more details.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u32       0 - disabled
 *                                          1 - enabled
 *                                          not set - default value is used
 *
 *  Define:          AAMEMADAPTER_CONFIG_TAG_RT_STATS_DUMP_SYSLOG
 *
 *  See:
 * @endverbatim
 *
 * @verbatim
 *  Tag name:        ccs.service.aamemadapter.rttrace.tmo
 *
 *  Direction:       input
 *
 *  Context:         EE
 *
 *  Description:     Runtime allocation and deallocation trace timeout in seconds.
 *
 *  Effect analysis: None
 *
 *  Restriction:     Not in use on some systems. See [CCSAPI_VARIABILITY] for more details.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u32       0 / not set - default value is used
 *
 *  Define:          AAMEMADAPTER_CONFIG_TAG_RT_TRACE_TMO
 *
 *  See:
 * @endverbatim
 *
 * @verbatim
 *  Tag name:        ccs.service.aamemadapter.rttrace.enable
 *
 *  Direction:       input
 *
 *  Context:         EE
 *
 *  Description:     Runtime allocation and deallocation trace master enablement switch.
 *
 *  Effect analysis: None
 *
 *  Restriction:     Not in use on some systems. See [CCSAPI_VARIABILITY] for more details.
 *
 *  Value:           IE Type:     Size:     Range:
 *                   number       u32       not set - default value is used
 *                                          0 - disabled
 *                                          1 - enabled
 *
 *  Define:          AAMEMADAPTER_CONFIG_TAG_RT_TRACE_ENABLE
 *
 *  See:
 * @endverbatim
 *
 *
 */

/**
 * @defgroup dpAaMemAdapterRdTags R&D tags
 * @ingroup dgAaMemAdapter
 *
 * R&D tags (R&D switches) are used for fast runtime variability when execution performance
 * is critical and the data must be able to accessed fast. As @ref dsVariation "configuration tags",
 * R&D tags can be used for capability and state advertisement too. R&D switches has fixed
 * size key and data which may limit their usage. Memory addresses cannot be transferred
 * portable way using R&D tags.
 *
 *
 * @ref dsVariation "[CCSAPI_VARIABILITY]"
 *
 * @verbatim
 *  Tag name:        ERadCcs_PrintAaMemAdapter
 *
 *  Direction:       input
 *
 *  Description:     Controls printouts of AaMemAdapter service.
 *
 *  Effect analysis: Depending tag value, debug level prinouts are enabled or disable.
 *
 *  Restriction:     None
 *
 *  Value:           Range:     Description:
 *                   0          Debug level prinouts are disabled.
 *                   1          Debug level prinouts are enabled.
 *
 *  Text:            AaMem
 *
 *  See:             None
 * @endverbatim
 *
 * @verbatim
 *  Tag name:        ERadCcs_AaMemAdapterPoolLimitThold
 *
 *  Direction:       input
 *
 *  Description:     Pool utilization limit threshold in percents.
 *
 *  Effect analysis: None
 *
 *  Restriction:     None
 *
 *  Value:           Range:     Description:
 *                   0-100      In percents
 *
 *  Text:            ERadCcs_AaMemAdapterPoolLimitThold
 *
 *  See:             None
 * @endverbatim
 *
 * @verbatim
 *  Tag name:        ERadCcs_AaMemAdapterPoolLimitTmo
 *
 *  Direction:       input
 *
 *  Description:
 *
 *  Effect analysis: None
 *
 *  Restriction:     None
 *
 *  Value:           Range:     Description:
 *
 *
 *  Text:            ERadCcs_AaMemAdapterPoolLimitTmo
 *
 *  See:             None
 * @endverbatim
 *
 * @verbatim
 *  Tag name:        ERadCcs_AaMemAdapterPoolStatsTmo
 *
 *  Direction:       input
 *
 *  Description:
 *
 *  Effect analysis: None
 *
 *  Restriction:     None
 *
 *  Value:           Range:     Description:
 *
 *
 *  Text:            ERadCcs_AaMemAdapterPoolStatsTmo
 *
 *  See:             None
 * @endverbatim
 *
 * @verbatim
 *  Tag name:        ERadCcs_AaMemAdapterPoolTraceTmo
 *
 *  Direction:       input
 *
 *  Description:
 *
 *  Effect analysis: None
 *
 *  Restriction:     None
 *
 *  Value:           Range:     Description:
 *
 *
 *  Text:            ERadCcs_AaMemAdapterPoolTraceTmo
 *
 *  See:             None
 * @endverbatim
 *
 */

/**
 * @defgroup dpAaMemAdapterErrors Error codes
 * @ingroup dgAaMemAdapter
 *
 * Exception codes are used with Error Management Service (AaError) and they describe
 * various error situations a service may have and report. Important part of exception
 * is the severity. Usually it is non-fatal thus execution of application continues
 * after the exception repporting but in some special case execution is prohipited and
 * the application is eventually terminated.
 *
 *
 * @ref dsVariation "[CCSAPI_VARIABILITY]"
 *
 * @verbatim
 *  Error code:       EAaErrorCcs_AaMemAdapter_Unref_Violation
 *
 *  Severity:         Non-fatal
 *
 *  Description:      Buffer usage after unref has been detected.
 *
 *  Extra code:       AaMem internal block handler SAaMemPrivBlockHandler
 *
 *  Recovery actions: None
 *
 *  See:              None
 * @endverbatim
 *
 * @verbatim
 *  Error code:       EAaErrorCcs_AaMemAdapter_Duplicate_Unref
 *
 *  Severity:         Non-fatal
 *
 *  Description:      Unref has been issued for a memory block multiple times.
 *
 *  Extra code:       None
 *
 *  Recovery actions: None
 *
 *  See:              None
 * @endverbatim
 *
 * @verbatim
 *  Error code:       EAaErrorCcs_AaMemAdapter_Invalid_Block
 *
 *  Severity:         Non-fatal
 *
 *  Description:      Invalid or corrupted memory block detected.
 *
 *  Extra code:       AaMem internal block handler SAaMemPrivBlockHandler
 *
 *  Recovery actions: None
 *
 *  See:              None
 * @endverbatim
 *
 * @verbatim
 *  Error code:       EAaErrorCcs_AaMemAdapter_Internal_Error
 *
 *  Severity:         Fatal/non-fatal
 *
 *  Description:      Internal error detected.
 *
 *  Extra code:       None
 *
 *  Recovery actions: None
 *
 *  See:              None
 * @endverbatim
 *
 * @verbatim
 *  Error code:       EAaErrorCcs_AaMemAdapter_PoolExhaust_Error
 *
 *  Severity:         Non-fatal
 *
 *  Description:      A pool is almost full.
 *
 *  Extra code:       None
 *
 *  Recovery actions: None
 *
 *  See:              ccs.service.aamemadapter.rtobs.limit.threshold
 * @endverbatim
 *
 *
 */

/*----------------------- INCLUDED FILES --------------------------------------*/

#include <glo_def.h>
#include <IfAaMem.h>
#include <IfAaFile.h>

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/


/**
 * @addtogroup dgAaMemApiMcu AaMem MCU API
 * @ingroup dgAaMem
 */

/* @{ */

/** @brief Invalid pool ID */
#define AAMEMADAPTER_INVALID_POOL_ID AAMEM_INVALID_POOL_ID
/** @brief ID for selecting all attached pools in some API calls */
#define AAMEMADAPTER_ALL_POOL_ID AAMEMADAPTER_INVALID_POOL_ID
/** @brief Maximum filename length supported */
#define AAMEMADAPTER_MAX_FILENAME_LENGTH AAFILE_FILENAME_MAX

/** @name Configuration tags
 * @{
 */

#define AAMEMADAPTER_CONFIG_TAG_TRACE_ONLINE                "sys.mem.trace.online"
#define AAMEMADAPTER_CONFIG_TAG_MASTER_ENABLE               "ccs.service.aamemadapter.enabled"
#define AAMEMADAPTER_CONFIG_TAG_POOL_EXHAUST_PM_FILE_SIZE   "ccs.service.aamemadapter.trace.pool.exhaust.pm.file.size"
#define AAMEMADAPTER_CONFIG_TAG_HEAP_EXHAUST_PM_FILE_SIZE AAMEMADAPTER_CONFIG_TAG_POOL_EXHAUST_PM_FILE_SIZE /** @deprecated Do NOT use this definition anymore */
#define AAMEMADAPTER_CONFIG_TAG_SLAB_POOL_INIT_SIZE         "ccs.service.aamemadapter.trace.slab.pool.init.size"
#define AAMEMADAPTER_CONFIG_TAG_RT_OBS_STATS_TMO            "ccs.service.aamemadapter.rtobs.stats.tmo"
#define AAMEMADAPTER_CONFIG_TAG_RT_OBS_LIMIT_TMO            "ccs.service.aamemadapter.rtobs.limit.tmo"
#define AAMEMADAPTER_CONFIG_TAG_RT_OBS_LIMIT_THOLD          "ccs.service.aamemadapter.rtobs.limit.threshold"
#define AAMEMADAPTER_CONFIG_TAG_RT_OBS_ENABLE               "ccs.service.aamemadapter.rtobs.enable"
#define AAMEMADAPTER_CONFIG_TAG_RT_STATS_DUMP_SYSLOG        "ccs.service.aamemadapter.rtobs.statusdump.syslog.enable"
#define AAMEMADAPTER_CONFIG_TAG_RT_STATS_DUMP_FILE          "ccs.service.aamemadapter.rtobs.statusdump.file.enable"
#define AAMEMADAPTER_CONFIG_TAG_RT_STATS_DUMP_FILE_SIZE     "ccs.service.aamemadapter.rtobs.statusdump.file.size"
#define AAMEMADAPTER_CONFIG_TAG_RT_TRACE_TMO                "ccs.service.aamemadapter.rttrace.tmo"
#define AAMEMADAPTER_CONFIG_TAG_RT_TRACE_ENABLE             "ccs.service.aamemadapter.rttrace.enable"
#define AAMEMADAPTER_CONFIG_TAG_LISTENER_ENABLE             "ccs.service.aamemadapter.listener.enable"
#define AAMEMADAPTER_CONFIG_TAG_HEAP_TRACING_ENABLE         "ccs.service.aamemadapter.heap.tracing.enable"
#define AAMEMADAPTER_CONFIG_TAG_HEAP_TRACING_MODE           "ccs.service.aamemadapter.heap.tracing.mode"

/** @} */

/** @brief Return code enumerations */
typedef enum EAaMemAdapterRet
{
    EAaMemAdapterRet_Ok = 0,            /**< No errors occurred. */
    EAaMemAdapterRet_InvalidParameter,  /**< Invalid parameter defined. */
    EAaMemAdapterRet_DumpError,         /**< Dumping failed. */
    EAaMemAdapterRet_UnexistentPoolId,  /**< Specified pool id doesn't exist */
    EAaMemAdapterRet_MemError,          /**< Memory error, e.g. no memory left for allocation */
    EAaMemAdapterRet_NbrOf              /**< Last one. Do not move. */
} EAaMemAdapterRet;

/** @brief Dump facility enumeration */
typedef enum EAaMemAdapterDumpFacility
{
    EAaMemAdapterDumpFacility_SysLog = 0, /**< Dump output facility is AaSysLog */
    EAaMemAdapterDumpFacility_File,       /**< Dump output facility is file system */
    EAaMemAdapterDumpFacility_User,       /**< Dump output facility is user specific */
    EAaMemAdapterDumpFacility_NbrOf       /**< Last one. Do not move. */
} EAaMemAdapterDumpFacility;

/** @brief Dump facility configuration for AaSysLog */
typedef struct SAaMemAdapterDumpFacilityConfSysLog
{
    EAaMemAdapterDumpFacility facility;
    void*                     buffer; /**< Buffer where printouts are stored */
} SAaMemAdapterDumpFacilityConfSysLog;

/** @brief Dump facility configuration for file */
typedef struct SAaMemAdapterDumpFacilityConfFile
{
    EAaMemAdapterDumpFacility facility;
    char                      filename[AAMEMADAPTER_MAX_FILENAME_LENGTH]; /**< Output filename */
    TBoolean                  append; /**< Append enablement (enabled=GLO_TRUE) */
    void*                     opaque; /**< Implementation specific data */
} SAaMemAdapterDumpFacilityConfFile;

/** @brief Dump facility configuration for user specific */
typedef struct SAaMemAdapterDumpFacilityConfUser
{
    EAaMemAdapterDumpFacility facility;
    void*                     opaque; /**< Implementation specific data */
} SAaMemAdapterDumpFacilityConfUser;

/** @brief Dump facility configuration union */
typedef union UAaMemAdapterDumpFacilityConf
{
    EAaMemAdapterDumpFacility           facility; /**< Defines which member of this union is used */
    SAaMemAdapterDumpFacilityConfFile   file;   /**< Config for filesystem dump implementation */
    SAaMemAdapterDumpFacilityConfSysLog syslog; /**< Config for syslog dump implementation */
    SAaMemAdapterDumpFacilityConfUser   user;   /**< Config for user-specific dump implementation */

} UAaMemAdapterDumpFacilityConf;

/**
 * @brief Callback for opening dump facility
 *
 * @param[in] facilityConf  Facility specific configuration
 *
 * @return EAaMemAdapterRet_Ok
 * @return EAaMemAdapterRet_InvalidParameter
 */
typedef EAaMemAdapterRet TAaMemAdapterDumpFacilityOpen(UAaMemAdapterDumpFacilityConf* const facilityConf);

/**
 * @brief Callback for closing dump facility
 *
 * @param[in] facilityConf  Facility specific configuration
 *
 * @return
 *   - EAaMemAdapterRet_Ok
 *   - EAaMemAdapterRet_InvalidParameter
 */
typedef EAaMemAdapterRet TAaMemAdapterDumpFacilityClose(UAaMemAdapterDumpFacilityConf* const facilityConf);

/**
 * @brief Callback for opening dump facility
 *
 * @param[in] facilityConf  Facility specific configuration
 * @param[in] format        Formatting string (printf compatible)
 *
 * @retval
 *   - EAaMemAdapterRet_Ok
 *   - EAaMemAdapterRet_InvalidParameter  Invalid parameter is given or config contains invalid values
 *   - EAaMemAdapterRet_DumpError
 */
typedef EAaMemAdapterRet TAaMemAdapterDumpFacilityWrite(UAaMemAdapterDumpFacilityConf* const facilityConf, const char* const format, ...);

/** @brief Dump facility handler */
typedef struct SAaMemAdapterDumpFacilityHndlr
{
    TAaMemAdapterDumpFacilityOpen*  openCb;  /**< Callback for facility open operation */
    TAaMemAdapterDumpFacilityClose* closeCb; /**< Callback for facility close operation */
    TAaMemAdapterDumpFacilityWrite* writeCb; /**< Callback for facility write operation */
} SAaMemAdapterDumpFacilityHndlr;

/** @brief Dump scope */
typedef enum EAaMemAdapterDumpScope
{
    EAaMemAdapterDumpScope_Allocs = 0, /**< Only allocation trace is dumped */
    EAaMemAdapterDumpScope_Deallocs,   /**< Only deallocation trace is dumped */
    EAaMemAdapterDumpScope_All,        /**< Both allocation and deallocation traces are dumped */
    EAaMemAdapterDumpScope_NbrOf       /**< Last one. Do not move. */
} EAaMemAdapterDumpScope;

/** @brief Dump configuration structure */
typedef struct SAaMemAdapterDumpConf
{
    UAaMemAdapterDumpFacilityConf  facilityConf;
    SAaMemAdapterDumpFacilityHndlr facilityHndlr;

} SAaMemAdapterDumpConf;

/**
 * @brief Helper macro for configuring dump facility for file mode
 *
 * @param[in] __config    Dump configuration structure
 * @param[in] __filename  NULL-terminated string for filename (the string is copied)
 * @param[in] __append    Append mode selection (if GLO_FALSE, existing file is replaced)
 */
#define AAMEMADAPTER_CONFIG_FILE_DUMP(__config, __filename, __append) \
    { (__config).facilityConf.facility = EAaMemAdapterDumpFacility_File; \
      strncpy((__config).facilityConf.file.filename, (__filename), AAMEMADAPTER_MAX_FILENAME_LENGTH-1); \
      (__config).facilityConf.file.append = (__append); }

/**
 * @brief Helper macro for configuring dump facility for AaSysLog mode
 *
 * @param[in] __config    Dump configuration structure
 */
#define AAMEMADAPTER_CONFIG_SYSLOG_DUMP(__config) \
    (__config).facilityConf.facility = EAaMemAdapterDumpFacility_SysLog

/** @brief Struct for pool status query */
typedef struct
{
    i32 poolId;             /**< ID of the pool */
    u32 size;               /**< Pool total size */
    u32 theoreticalMaxSize; /**< Total theoretical maximum pool size in bytes, fixed with OSE but flexiable with Linux */
    u32 free;               /**< Total free currently in the pool */
    u32 maxContinous;       /**< Biggest continuous block of memory */
    u32 peakAlloc;          /**< Maximum used size of the pool */
    u32 largestFreeBuffer;  /**< Largest free buffer in pool */
    u32 numberOfAllocs;     /**< Number of allocations in pool */
    u32 reqByteCount;       /**< Requested byte amount in pool */

} SAaMemAdapterPoolStatus;

/** @name Function interface
 * @{
 */

/**
 *******************************************************************************
 *
 * @brief Dump all allocations, which are currently traced
 *
 * @param[in] scope    dummy parameter, which has no meaning in the moment
 *                     (should be always filled with EAaMemAdapterDumpScope_All)
 * @param[in] poolId   pool ID of pool to be dumped (AAMEMADAPTER_ALL_POOL_ID if all
 *                     pools have to be dumped)
 * @param[in] config   pointer to dump configuration structure
 *
 * @return
 *      - EAaMemAdapterRet_Ok
 *      - EAaMemAdapterRet_InvalidParameter
 *      - EAaMemAdapterRet_DumpError
 *
 * @par Description:
 * This function dumps traced allocations, which are currently contained in the Trace Record Pool.
 * This only works if 'Allocation Tracing' is turned on and result depends on the specific tracing mode.
 * (Read more about this in the 'Testability Services (AaMemAdapter)' chapter of AaMem API Spec.)
 * There are several facilities to which the dump can be directed (see #SAaMemAdapterDumpConf).
 * \n
 * It is also possible to use a user defined dump facility. In this case
 * the application must fill the SAaMemAdapterDumpConf.facilityHndlr field as well.
 *
 * @par Errors:
 * If config argument is GLO_NULL or there is invalid parameters in the
 * config struct, #EAaMemAdapterRet_InvalidParameter is returned. If error
 * is occurred during dumping, #EAaMemAdapterRet_DumpError is returned. In case
 * of any error, dumpping is terminated when error is detected.
 * \n\n
 * Possible causes for EAaMemAdapterRet_InvalidParameter:
 *    - Invalid enumeration
 *    - Invalid pool ID (non-existent pool)
 *    - NULL parameter
 *    - Invalid filename
 *
 * @par Restrictions:
 * None
 *
 * @par Example:
 *
 * @code
 *
 *    #include <IfAaMemAdapter.h>
 *
 *    EAaMemAdapterRet rc;
 *    SAaMemAdapterDumpConf config; // Configuration structure for all kind of dump facilities
 *
 *    // Handy macro is used for configuring dumping to file mode
 *    AAMEMADAPTER_CONFIG_FILE_DUMP(config, "/ram/memtrace.log", GLO_FALSE);
 *
 *    // Dump both alloc and dealloc trace of all pools to facility configured earlier
 *    rc = AaMemAdapterDump(EAaMemAdapterDumpScope_All, AAMEMADAPTER_ALL_POOL_ID, &config);
 *
 * @endcode
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
 * @see AAMEMADAPTER_CONFIG_SYSLOG_DUMP
 * @see AAMEMADAPTER_CONFIG_FILE_DUMP
 *
 ******************************************************************************/
EAaMemAdapterRet AaMemAdapterDump(const EAaMemAdapterDumpScope scope,
                                  const i32 poolId,
                                  SAaMemAdapterDumpConf* const config);

/**
 *******************************************************************************
 *
 * @brief Queries pool related status information for all AaMem pools
 *
 * @param[in]  poolId        pool id should always be set to AAMEMADAPTER_ALL_POOL_ID
 *                           (otherwise nothing will be queried)
 * @param[out] statusArray   array with pool status information
 *                           (Ownership is passed to user and therefore has to be freed!)
 * @param[out] statusCount   number of pools for which status information is contained
 *                           in the status array
 *
 * @return
 *   - EAaMemAdapterRet_Ok:               status information was queried successfully
 *   - EAaMemAdapterRet_InvalidParameter: error in passed parameters (e.g. null pointers
 *                                        for reference values.)
 *
 * @par Description:
 * The status of every AaMem pool, which currently is registered at the
 * AaMemAdapter, will be referenced in an array.
 * With status mainly the pool statistics (total size, total free, etc.) is meant.
 *
 * @note
 *  - Ownership of referenced status is passed to the caller of the function.
 *    The caller is responsible to free the status (see example).
 *  - Implemented statistic data and status information capability of a pool depends
 *    on the pool individual implementation.
 *
 * @par Restrictions:
 *
 * @par Example:
 *
 * @code
 *
 *    #include <IfAaMemAdapter.h>
 *
 *    SAaMemAdapterPoolStatus* stPtr = GLO_NULL;
 *    size_t counter = 0;
 *
 *    if ( EAaMemAdapterRet_Ok ==
 *        AaMemAdapterQuery( AAMEMADAPTER_ALL_POOL_ID, &stPtr, &counter) ) {
 *        for (i = 0; i < counter; i++) {
 *            AaSysLog("total size for pool id %i is %i",
 *                     stPtr[i].poolId, stPtr[i].size);
 *        }
 *
 *        AaMemUnRef(&stPtr); // VERY IMPORTANT FOR AVOIDING MEMORY-LEAKS!!!
 *    }
 *
 * @endcode
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
 *
 ******************************************************************************/
EAaMemAdapterRet AaMemAdapterQuery(const i32 poolId,
                                   SAaMemAdapterPoolStatus** statusArray,
                                   size_t* statusCount);

/**
 *******************************************************************************
 *
 * @brief Queries pool related status information for a given AaMem pool
 *
 * @param[in]  poolId      pool id for pool to be queried
 * @param[out] status      pool status information
 * @param[out] poolCount   number of pools, which currently are registerd at AaMemAdapter
 *
 * @return
 *   - EAaMemAdapterRet_Ok:               status information was queried successfully
 *   - EAaMemAdapterRet_InvalidParameter: error in passed parameters (e.g. null pointers
 *                                        for reference values.)
 *
 * @par Description:
 * The status of the AaMem pool with given pool id, will be referenced (if
 * the pool with given id is registered at the AaMemAdapter).
 * With status mainly the pool statistics (total size, total free, etc.) is meant.
 *
 * @note
 * Implemented statistic data and status information capability of a pool depends
 * on the pool individual implementation.
 *
 * @par Restrictions:
 *
 * @par Example:
 *
 * @code
 *
 *    #include <IfAaMemAdapter.h>
 *
 *    SAaMemAdapterPoolStatus st;
 *    size_t counter = 0; // only to satisfy interface
 *
 *    if ( EAaMemAdapterRet_Ok ==
 *        AaMemAdapterOnePoolQuery(EAaMemSysPoolId_Private, &st, &counter) ) {
 *        AaSysLog("total size for pool is %i", st.size);
 *    }
 *
 * @endcode
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
 *
 ******************************************************************************/
EAaMemAdapterRet AaMemAdapterOnePoolQuery(const i32 poolId,
                                          SAaMemAdapterPoolStatus* status,
                                          size_t* poolCount);

/**
 *******************************************************************************
 *
 * @brief CE level initialisation of AaMemAdapter
 *
 * @param none
 *
 * @return EAaMemRet_Ok
 *
 * @par Description:
 *
 * @par Errors:
 *
 * @par Restrictions:
 *
 * @par Example:
 *
 * @code
 *
 * @endcode
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
 *
 ******************************************************************************/
EAaMemRet AaMemAdapterCeInit(void);

/**
 *******************************************************************************
 *
 * @brief EE level initialisation of AaMemAdapter
 *
 * @param none
 *
 * @return EAaMemRet_Ok
 *
 * @par Description:
 *
 * @par Errors:
 *
 * @par Restrictions:
 *
 * @par Example:
 *
 * @code
 *
 * @endcode
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
 *
 ******************************************************************************/
EAaMemRet AaMemAdapterEeInit(void);

/**
 *******************************************************************************
 *
 * @brief EE level shutdown of AaMemAdapter
 *
 * @param none
 *
 * @return EAaMemRet_Ok
 *
 * @par Description:
 *
 * @par Errors:
 *
 * @par Restrictions:
 *
 * @par Example:
 *
 * @code
 *
 * @endcode
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
 *
 ******************************************************************************/
EAaMemRet AaMemAdapterEeUninit(void);


/** @name Message interface
 * @{
 */

/** @brief CpId for the AaMemAdapter controller EU in master-EE */
#define AAMEMADAPTER_CONTROLLER_CPID 0x060F /* Only in master-EE */

/* Message IDs */
#define AAMEMADAPTER_DUMP_REQ_MSG                     0x08D6 /* !- SIGNO(struct AaMemAdapterDumpReq) -! */
#define AAMEMADAPTER_DUMP_RESP_MSG                    0x08D7 /* !- SIGNO(struct AaMemAdapterDumpResp) -! */
#define AAMEMADAPTER_QUERY_REQ_MSG                    0x0AF5 /* !- SIGNO(struct AaMemAdapterQueryReq) -! */
#define AAMEMADAPTER_QUERY_RESP_MSG                   0x0B24 /* !- SIGNO(struct AaMemAdapterQueryResp) -! */
#define AAMEMADAPTER_HEAP_TRACE_DELAY_TIMEOUT_IND_MSG 0x0B89 /* !- SIGNO(void) -! */

/**
 * @brief Message for requesting dumping of allocations and unallocations
 */
struct AaMemAdapterDumpReq
{
    SAaMemAdapterDumpConf  config;
    EAaMemAdapterDumpScope scope;
    i32                    poolId; /**< Id of the pool to dump or AAMEMADAPTER_ALL_POOL_ID */

};
typedef struct AaMemAdapterDumpReq AaMemAdapterDumpReq;

/**
 * @brief Message for responding dump request
 */
struct AaMemAdapterDumpResp
{
    EAaMemAdapterRet rc;

};
typedef struct AaMemAdapterDumpResp AaMemAdapterDumpResp;

/**
 * @brief Message for querying pool statuses
 */
struct AaMemAdapterQueryReq
{
    i32 poolId; /**< Id of the pool to query or AAMEMADAPTER_ALL_POOL_ID */

};
typedef struct AaMemAdapterQueryReq AaMemAdapterQueryReq;

/**
 * @brief Message for responding dump request
 */
struct AaMemAdapterQueryResp
{
    EAaMemAdapterRet        rc; /**< Result code for request */

    u32                     count; /**< Number of elements in #statuses member */
    SAaMemAdapterPoolStatus statuses[1]; /**< Pool statuses */

};
typedef struct AaMemAdapterQueryResp AaMemAdapterQueryResp;

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

/*@}*/


#endif /*  _MCU_RT_IFAAMEMADAPTER_H */
