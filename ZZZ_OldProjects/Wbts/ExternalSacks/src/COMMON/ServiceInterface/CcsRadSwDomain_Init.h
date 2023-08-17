/** @file
 *  @brief Initialization of R&D flags in CCS domain with default values
 *
 *  $HeadURL$
 *  $LastChangedRevision$
 *  $LastChangedDate$
 *  $Author$
 *  $Copyright: Copyright 2018 Nokia. All right reserved.$
 */
#ifndef _CCS_RAD_SW_DOMAIN_INIT_H_
#define _CCS_RAD_SW_DOMAIN_INIT_H_

#include <CcsCommon.h>

#include <ERadCcs.h>
#include <IfAaConfig_Defs.h>
#include <IfAaConfigRad.h>

#ifdef __cplusplus
extern "C" {
#endif

/************************** DOXYGEN GROUPS ************************************/

/**
 *  @defgroup dgRadCcs            CCS R&D parameters
 *
 *  Defines CC&S R&D parameters.
 *
 *  For detailed description of service specific parameters please refer to the according API Spec: <a href="https://sharenet-ims.inside.nokiasiemensnetworks.com/Open/396832787">https://sharenet-ims.inside.nokiasiemensnetworks.com/Open/396832787</a>
 *
 */
/*@{*/



/*@}*/

#ifdef CCS_INTERNAL_API
#ifdef CCS_OSECK
#pragma CODE_SECTION(initializeCcsRadParameters, "ccs_AaStartup_slow_code")
#endif
static __CCS_INLINE__ void
initializeCcsRadParameters (void)
{
    AaConfigRadSetMaxTagCount (ERadSwDomain_Ccs, ERadCcs_Last);

    AaConfigRadSetDefault (ERadCcs_PrintAaSysCom, "AaSysCom", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysLog, "AaSysLog", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysTime, "AaSysTime", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaMem, "AaMem", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaPro, "AaPro", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSem, "AaSem", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaStartup, "AaStartup", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaFile, "AaFile", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaUdpcpGen, "AaUdpcpGen", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaUdpcpTx, "AaUdpcpTx", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaUdpcpRx, "AaUdpcpRx", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaMemAdapter, "AaMemAdapter", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysComGw, "AaSysComGw", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterMasterEnable, "AaMemAdapterMasterEnable", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterRtTrace, "AaMemAdapterRtTrace", 0xFFFFFFFF); /* transparency for config tag */
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterRtObs, "AaMemAdapterRtObs", 1);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterRtTraceTmo, "AaMemAdapterRtTraceTmo", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterRtObsTmo, "AaMemAdapterRtObsTmo", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterListenerDisable, "AaMemAdapterListenerDisable", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaProdTest, "AaProdTest", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaProdTestCBist, "AaProdTestCBist", 0);
    AaConfigRadSetDefault (ERadCcs_AaProdTestEnable, "AaProdTestEnable", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysMb, "AaSysMb", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaConfigRaDSlave, "AaConfigRadSlave",
                           0);
    AaConfigRadSetDefault (ERadCcs_PrintAaConfigRaDMaster, "AaConfigRadMaster",
                           0);
    AaConfigRadSetDefault (ERadCcs_PrintAaConfigRad, "AaConfigRad", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaConfigTag, "AaConfigTag", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaPostmortem, "AaPostmortem", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaTrbl, "AaTrbl", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaError, "AaError", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaTrblTechLogMasterEmu,
                           "TechLogMasterEmu", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterPoolLimitThold,
                           "AaMemAdapterPoolLimitThold", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterPoolLimitTmo,
                           "AaMemAdapterPoolLimitTmo", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterPoolStatsTmo,
                           "AaMemAdapterPoolStatsTmo", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterPoolTraceTmo,
                           "AaMemAdapterPoolTraceTmo", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaTrace, "AaTrace", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaTestPort, "AaTestPort", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysMbStoragePrinterEnable,
                           "AaSysMbStoragePrinterEnable", 0);
    AaConfigRadSetDefault (ERadCcs_PrintSchedulerTrace, "AaSchedTrace", 0);
    AaConfigRadSetDefault (ERadCcs_PrintProcessTrace, "AaProcTrace", 0);
    AaConfigRadSetDefault (ERadCcs_PrintMessageTrace, "AaMsgTrace", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaHTTP, "AaHTTP", 0);
    AaConfigRadSetDefault (ERadCcs_AaTraceSwConfUsed, "AaTraceSwConfUsed", 0);
    AaConfigRadSetDefault (ERadCcs_AaTraceSwConfId1, "AaTraceSwConfId1", 0);
    AaConfigRadSetDefault (ERadCcs_AaTraceSwConfId2, "AaTraceSwConfId2", 0);
    AaConfigRadSetDefault (ERadCcs_AaTraceSwConfId3, "AaTraceSwConfId3", 0);
    AaConfigRadSetDefault (ERadCcs_AaTraceSwConfId4, "AaTraceSwConfId4", 0);
    AaConfigRadSetDefault (ERadCcs_AaTraceSwConfRange1, "AaTraceSwConfRange1",
                           0);
    AaConfigRadSetDefault (ERadCcs_AaTraceSwConfRange2, "AaTraceSwConfRange2",
                           0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysComUser, "AaSysComUser", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysComLink, "AaSysComLink", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysComHop, "AaSysComHop", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysComGwRoute, "AaSysComGwRoute", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysComRtm, "AaSysComRtm", 0);
    AaConfigRadSetDefault (ERadCcs_PoolAnalyzerDisable, "PoolAnalyzerDisable",
                           0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSNTP, "AaSNTP", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaDHCP, "AaDHCP", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysComControl, "AaSysComControl", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysComEndian4Divisible,
                           "AaSysComEndian4Divisible", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysTimeBcn, "AaSysTimeBcn", 0);
    AaConfigRadSetDefault (ERadCcs_HeapAnalyzerDisable, "HeapAnalyzerDisable",
                           0);
    AaConfigRadSetDefault (ERadCcs_PrintAaNet, "AaNet", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComKernelErrorDisable,
                           "AaSysComKernelErrorDisable", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogInputLevel, "AaSysLogInputLevel",
                           0xFFFFFFFF);
    AaConfigRadSetDefault (ERadCcs_AaSysLogOutputLevel, "AaSysLogOutputLevel",
                           0xFFFFFFFF);
    AaConfigRadSetDefault (ERadCcs_AaSysLogOutputMode, "AaSysLogOutputMode",
                           0xFFFFFFFF);
    AaConfigRadSetDefault (ERadCcs_AaSysLogUdpAddress, "AaSysLogUdpAddress", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogUdpPort, "AaSysLogUdpPort", 0xFFFFFFFF);
    AaConfigRadSetDefault (ERadCcs_AaSysLogSicAddress, "AaSysLogSicAddress", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogStartupLogSize,
                           "AaSysLogStartupLogSize", 0xFFFFFFFF);
    AaConfigRadSetDefault (ERadCcs_AaSysLogSnapshotFreezeDisable,
                           "AaSysLogSnapshotFreezeDisable", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaProSched, "AaProSched", 0);
    AaConfigRadSetDefault (ERadCcs_AaProSchedControl, "AaProSchedControl", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaFileSicFtp, "AaFileSicFtp", 0);
    AaConfigRadSetDefault (ERadCcs_AaProLinuxRealtimeScheduling, "AaProLinuxRealtimeScheduling", 0);    /* SCHED_OTHER */
    AaConfigRadSetDefault (ERadCcs_PrintAaLteTime, "AaLteTime", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComRtmDisable, "AaSysComRtmDisable", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComRtmTimeout, "AaSysComRtmTimeout", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComRtmResendings, "AaSysComRtmResendings", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaRTOS, "AaRTOS", 0);
    AaConfigRadSetDefault (ERadCcs_AaProDisableSafetyMarginFeature, "AaProDisableSafetyMarginFeature", 0);  /* 0 = feature is
enabled */
    AaConfigRadSetDefault (ERadCcs_AaProVirtStacksizeOffset, "AaProVirtStacksizeOffset", 0);    /* stacksize offset */
    AaConfigRadSetDefault (ERadCcs_PrintAaShell, "AaShell", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaGpuXml, "AaGpuXml", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterValidateAllocMaxBlockCount, "AaMemAdapterValidateAllocMaxBlockCount", 5000);
    AaConfigRadSetDefault (ERadCcs_AaFileDefaultVolume, "AaFileDefaultVolume", 1);
    AaConfigRadSetDefault (ERadCcs_PrintAaFileTftp, "AaFileTftp", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComMsgRerouteEnable, "AaSysComMsgRerouteEnable", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterHeapTracingDelay, "AaMemAdapterHeapTracingDelay", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterHeapTracingEnable, "AaMemAdapterHeapTracingEnable", 0xFFFFFFFF); /* transparenc
y for config tag */
    AaConfigRadSetDefault (ERadCcs_AaTraceTracingMode, "AaTraceTracingMode", 0);
    AaConfigRadSetDefault (ERadCcs_AaUDPCPTxMessageResendTimeout,
                           "ERadCcs_AaUDPCPTxMessageResendTimeout", 0);
    AaConfigRadSetDefault (ERadCcs_AaUDPCPTxMessageResendRetries,
                           "ERadCcs_AaUDPCPTxMessageResendRetries", 0);
    AaConfigRadSetDefault (ERadCcs_AaUDPCPAckMode,
                           "ERadCcs_AaUDPCPAckMode", 0);
    AaConfigRadSetDefault (ERadCcs_AaUDPCPCrcInUse,
                           "ERadCcs_AaUDPCPCrcInUse", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterHeapTracingMode, "AaMemAdapterHeapTracingMode", 0xFFFFFFFF); /* transparency fo
r config tag */
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterQuarantineListLength, "AaMemAdapterQuarantineListLength", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysComNotifList,
                           "AaSysComNotifList", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComCommErrNotifyDisabled,
                           "AaSysComCommErrNotifyDisabled", 0);
    AaConfigRadSetDefault (ERadCcs_SwAppDefCheckDisable, "ERadCcs_SwAppDefCheckDisable", 0);
    AaConfigRadSetDefault (ERadCcs_AaFileSicFtpClientTimeout, "AaFileSicFtpClientTimeout", 0); /* disabled by default */
    AaConfigRadSetDefault (ERadCcs_AaFileSicFtpServerTimeout, "AaFileSicFtpServerTimeout", 0); /* disabled by default */
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterPermanentQuarantineListLength, "AaMemAdapterPermanentQuarantineListLength", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterQuarantineListBlockSizeMin, "AaMemAdapterQuarantineListBlockSizeMin", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterQuarantineListBlockSizeMax, "AaMemAdapterQuarantineListBlockSizeMax", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterQuarantineListStopAtCorruption, "AaMemAdapterQuarantineListStopAtCorruption", 0
);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterCallStackFrameSkipCount, "AaMemAdapterCallStackFrameSkipCount", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterCorruptedBlockDumpPreBytes, "AaMemAdapterBlockDumpPreBytes", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterCorruptedBlockDumpPostBytes, "AaMemAdapterBlockDumpPostBytes", 0);
#if defined(AASTARTUP_PLATFORM_KEPLER2)
    AaConfigRadSetDefault (ERadCcs_AaTestPortNagleDisable, "AaTestPort", 0);
#else
    AaConfigRadSetDefault (ERadCcs_AaTestPortNagleDisable, "AaTestPortNagleDisable", 0);
#endif
    AaConfigRadSetDefault (ERadCcs_AaFileTftpLookupTableSize, "AaFileTftpLookupTableSize", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaConfigSvcReg, "AaConfigSvcReg", 0);
#if defined(AASTARTUP_PLATFORM_KEPLER2)
    AaConfigRadSetDefault (ERadCcs_CCSDaemonWaitTime,"ERadCcs_CCSDaemonWaitTime", 300000);
#else
    AaConfigRadSetDefault (ERadCcs_CCSDaemonWaitTime,"ERadCcs_CCSDaemonWaitTime", 180000);
#endif
    AaConfigRadSetDefault (ERadCcs_PrintCCSDaemon,"CCSDaemon", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaFileFtpClient, "AaFileFtpClient", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComStatistics, "AaSysComStatistics", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComGwStatistics, "AaSysComGwStatistics", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysComStats, "AaSysComStats", 0);
    AaConfigRadSetDefault (ERadCcs_PrintStatistics, "Statistics", 0);
    AaConfigRadSetDefault (ERadCcs_AaProWDRebootDisable, "ERadCcs_AaProWDRebootDisable", 0);
    AaConfigRadSetDefault (ERadCcs_AaRTOSApiFatalExceptionDisable, "AaRTOSApiFatalExceptionDisable", 0);
    AaConfigRadSetDefault (ERadCcs_AaErrorCoreDump, "AaErrorCoreDump", 0);
    AaConfigRadSetDefault (ERadCcs_AaErrorCoreDumpOamEnabled , "AaErrorCoreDumpOamEnabled", 0);
    AaConfigRadSetDefault (ERadCcs_AaProMemoryOverloadCoefficient, "AaProMemoryOverloadCoefficient", 60);
    AaConfigRadSetDefault (ERadCcs_AaSysLogPrintLinuxDbgLogs, "LinuxSyslog", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogLinuxListener, "AaSysLogLinuxListener", 1);
    AaConfigRadSetDefault (ERadCcs_PrintAaRTOSApi, "AaRTOSApi", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterHeapTracingPoolSize, "AaMemAdapterHeapTracingPoolSize", 0);
    AaConfigRadSetDefault (ERadCcs_AaMemAdapterHeapTracingCallStackDepth, "AaMemAdapterHeapTracingCallstackDepth", 0);
    AaConfigRadSetDefault (ERadCcs_AaLteTimeSimDrvFrameMultiplier, "AaLteTimeSimDrvFrameMultiplier", 1);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysComGwTcp, "AaSysComGwTcp", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComGwKeepAliveDisable, "ERadCcs_AaSysComGwKeepAliveDisable", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComGwKeepCnt, "ERadCcs_AaSysComGwKeepCnt", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComGwKeepIdle, "ERadCcs_AaSysComGwKeepIdle", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComGwKeepIntvl, "ERadCcs_AaSysComGwKeepIntvl", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComGwNagleDisable, "ERadCcs_AaSysComGwNagleDisable", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComGwTcpBufferSize, "ERadCcs_AaSysComGwTcpBufferSize", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComGwUdpRxBufferSize, "ERadCcs_AaSysComGwUdpRxBufferSize", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysComGwUdpTxBufferSize, "ERadCcs_AaSysComGwUdpTxBufferSize", 0);
    AaConfigRadSetDefault (ERadCcs_AaProNumberOfCPUMeasurementsPerLogLine, "AaProNumberOfCPUMeasurementsPerLogLine", 12);
    AaConfigRadSetDefault (ERadCcs_AaSysMbNodeListDelayTimeout, "AaSysMbNodeListDelayTimeout", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogFeatureLogRingBuffer, "AaSysLogFeatureLogRingBuffer", 1);
    AaConfigRadSetDefault (ERadCcs_AaSysLogFeatureLogRingBufferOutputLevel, "AaSysLogFeatureLogRingBufferOutputLevel", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysTimeBaseDisable, "ERadCcs_AaSysTimeBaseDisable", 1);
    AaConfigRadSetDefault (ERadCcs_AaSysLogRAMDeviceFileSize, "AaSysLogRAMDeviceFileSize", 0x1400000); /* Set maximum size of
AaSysLog RAM device file to 20 MB by default*/
    AaConfigRadSetDefault (ERadCcs_AaTraceAggBufferSize, "AaTraceAggBufferSize", 0);
    AaConfigRadSetDefault (ERadCcs_AaTraceAggTimeout, "AaTraceAggTimeout", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogPrintTrswDbgLogs, "TRSWSyslog", 0);
    AaConfigRadSetDefault (ERadCcs_AaSNTPToPdSupport, "ERadCcs_AaSNTPToPdSupport", 1);
    AaConfigRadSetDefault (ERadCcs_AaSysLogQuotaCheckDisable, "AaSysLogQuotaCheckDisable", 0);
    AaConfigRadSetDefault (ERadCcs_AaLogCollectorDbgLogs, "AaLogCollect", 0);
    AaConfigRadSetDefault (ERadCcs_AaLogCollectorFileSize, "AaLogCollectorFileSize",  (10*1024*1024));
    AaConfigRadSetDefault (ERadCcs_AaLogCollectorCompressionDisable, "AaLogCollectorCompressionDisable", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogRemoteServerMode, "AaSysLogRemoteServerMode", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaRedundancy, "AaRedundancy", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogCompressionDisable, "ERadCcs_AaSysLogCompressionDisable", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaConfig, "AaConfig", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogSicAddressLocal, "AaSysLogSicAddressLocal", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogSicAddressRemote, "AaSysLogSicAddressRemote", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogConsumerRate, "AaSysLogConsumerRate", 1);
    AaConfigRadSetDefault (ERadCcs_PrintAaWcdmaTime, "AaWcdmaTime", 0);
    AaConfigRadSetDefault (ERadCcs_AaFileTraceConfig, "AaFileTraceConfig", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaSysInfo  , "AaSysInfo", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoMemoryStartupTime, "AaSysInfoMemoryStartupTime", 120);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoMemorySamplingTime, "AaSysInfoMemorySamplingTime", 900);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoMemoryMaxHistory, "AaSysInfoMemoryMaxHistory", 30);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoMemoryMinHistory, "AaSysInfoMemoryMinHistory", 3);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoMemoryFileQuota, "AaSysInfoMemoryFileQuota", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoMemoryCompressionInterval, "AaSysInfoMemoryCompressionInterval", 86400);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoCpuStartupTime, "AaSysInfoCpuStartupTime", 120);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoCpuSamplingTime, "AaSysInfoCpuSamplingTime", 5);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoCpuMaxHistory, "AaSysInfoCpuMaxHistory", 9);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoCpuMinHistory, "AaSysInfoCpuMinHistory", 2);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoCpuFileQuota, "AaSysInfoCpuFileQuota", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoCpuCompressionInterval, "AaSysInfoCpuCompressionInterval", 3600);
    AaConfigRadSetDefault (ERadCcs_PrintAaConfigRadMasterChange, "AaConfigRadMasterChange", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaConfigRadShellChange, "AaConfigRadShellChange", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogSubstringSearchEnabled, "AaSysLogSubstringSearchEnabled", 0xFFFFFFFF);
    AaConfigRadSetDefault (ERadCcs_AaSysLogSubstringSearchDelay, "AaSysLogSubstringSearchDelay", 900);
    AaConfigRadSetDefault (ERadCcs_AaSysLogSubstringSearchMaximumPatterns, "AaSysLogSubstringSearchMaximumPatterns", 1);
    AaConfigRadSetDefault (ERadCcs_AaSysLogSubstringSearchActive, "AaSysLogSubstringSearchActive", 0);
    AaConfigRadSetDefault (ERadCcs_PrintAaFileWrapper, "AaFileWrapper", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogUdpAddressLcp0, "AaSysLogUdpAddressLcp0", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysLogUdpAddressLcp1, "AaSysLogUdpAddressLcp1", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoRadControlMode, "AaSysInfoRadControlMode", 1);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoVerboseMode, "AaSysInfoVerboseMode", 0);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoProcessUssThreshold, "AaSysInfoProcessUssThreshold", 0x400000);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoProcessDiscoveryInterval, "AaSysInfoProcessDiscoveryInterval", 3600);
    AaConfigRadSetDefault (ERadCcs_AaAllocationTraceDbgLogs, "AaAllocationTrace", 0);
    AaConfigRadSetDefault (ERadCcs_AaAllocationTraceMode, "AaAllocationTraceMode", 1);
    AaConfigRadSetDefault (ERadCcs_AaAllocationTracePoolMemoryQuota, "AaAllocationTracePoolMemoryQuota", 0xA00000);
    AaConfigRadSetDefault (ERadCcs_AaAllocationTracePoolCount, "AaAllocationTracePoolCount", 29);
    AaConfigRadSetDefault (ERadCcs_AaAllocationTraceCompressedPoolMemoryQuota, "AaAllocationTraceCompressedPoolMemoryQuota", 0x100000);
    AaConfigRadSetDefault (ERadCcs_AaAllocationTraceCallStackDepth, "AaAllocationTraceCallStackDepth", 10);
    AaConfigRadSetDefault (ERadCcs_AaAllocationTraceAllocationTimestampEnabled, "AllocationTimestampEnabled", 0);
    AaConfigRadSetDefault (ERadCcs_AaTraceMaxPacketDumpSize, "AaTraceMaxPacketDumpSize", 0xFFFFFFFF);
    AaConfigRadSetDefault (ERadCcs_AaTrblServerParallelStoreRequestsPerNode, "AaTrblServerParallelStoreRequestsPerNode", 0xFFFFFFFF);
    AaConfigRadSetDefault (ERadCcs_AaTraceRestrictToOwnDomain, "AaTraceRestrictToOwnDomain", 0xFFFFFFFF);

    AaConfigRadSetDefault (ERadCcs_AaSysInfoSyscomSamplingTime,        "AaSysInfoSyscomSamplingTime",        5);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoSyscomCompressionInterval, "AaSysInfoSyscomCompressionInterval", 3600);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoSyscomMaxHistory,          "AaSysInfoSyscomMaxHistory",          9);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoSyscomMinHistory,          "AaSysInfoSyscomMinHistory",          2);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoSyscomMaxReports,          "AaSysInfoSyscomMaxReports",          200);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoSyscomEntriesInReport,     "AaSysInfoSyscomEntriesInReport",     5);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoSyscomReportThreshold,     "AaSysInfoSyscomReportThreshold",     60);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoSyscomReportInterval,      "AaSysInfoSyscomReportInterval",      600);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoSyscomFileQuota,           "AaSysInfoSyscomFileQuota",           0);
    AaConfigRadSetDefault (ERadCcs_AaSysinfoCpuThreadMonitoring,       "AaSysinfoCpuThreadMonitoring",       0);
    AaConfigRadSetDefault (ERadCcs_AaSysinfoProcessCpuThreshold,       "AaSysinfoProcessCpuThreshold",       10);
    AaConfigRadSetDefault (ERadCcs_AaSysinfoProcessCpuCount,           "AaSysinfoProcessCpuCount",           10);

    AaConfigRadSetDefault (ERadCcs_AaSysInfoUPLoadMaxHistory,          "AaSysInfoUPLoadMaxHistory",          30);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoUPLoadMinHistory,          "AaSysInfoUPLoadMinHistory",          3);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoUPLoadFileQuota,           "AaSysInfoUPLoadFileQuota",           0);
    AaConfigRadSetDefault (ERadCcs_AaSysInfoUPLoadCompressionInterval, "AaSysInfoUPLoadCompressionInterval", 3600);

    AaConfigRadSetDefault (ERadCcs_AaSysLogPrintRcpDbgLogs,            "RCPSyslog",                          0);
    AaConfigRadSetDefault (ERadCcs_PrintAaStartupTime,                 "AaStartupTime",                      0);
    AaConfigRadSetDefault (ERadCcs_AaSysMessageOperationHistoryEnable, "AaSysComMsgHistory",                 0);
}

#endif /* CCS_INTERNAL_API */

#ifdef __cplusplus
}
#endif

#endif //_CCS_RAD_SW_DOMAIN_INIT_H_
