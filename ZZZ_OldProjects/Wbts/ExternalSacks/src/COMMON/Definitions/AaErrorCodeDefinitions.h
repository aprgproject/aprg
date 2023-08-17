/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Error code definitions for AaError
* @module                AaError
* @owner                 Ksenija Bischof
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/
 
#ifndef _AAERRORCODEDEFINITIONS_H
#define _AAERRORCODEDEFINITIONS_H

/************************** DOXYGEN GROUPS ************************************/

/**
 *  @defgroup dgErrorCodes Error codes
 *  @ingroup  dgCcs
 *
 *  Defines CC&S error codes.
 */
/*@{*/

/************************** INCLUDED FILES ************************************/
#include <CcsCommon.h>
#include <EAaErrorSwDomain.h>

/************************** PUBLIC DECLARATIONS *******************************/

/** @cond */
#define AAERROR_INTERNAL(__value) AAERROR_SW_DOMAIN(EAaErrorSwDomain_Internal, (__value))
#define AAERROR_CCS(__value) AAERROR_SW_DOMAIN(EAaErrorSwDomain_Ccs, (__value))
/** @endcond */


/************************** PUBLIC INTERFACES *********************************/

/*!
 *  @brief  Defines CC&S AaError internal error codes.
 */
enum EAaErrorInternal
{
    EAaErrorInternal_NotUsed         = AAERROR_INTERNAL(0),   /* Not in use */
    EAaErrorInternal_Assertion       = AAERROR_INTERNAL(1),   /* AaError assertion error code */
    EAaErrorInternal_InvalidAddress  = AAERROR_INTERNAL(2),   /* Invalid address error code */
    EAaErrorInternal_Recurse         = AAERROR_INTERNAL(3),   /* AaError called itself */

    EAaErrorInternal_Last                                /* Not usable value, let always be the last! */
};

/*!
 *  @brief  Defines CC&S error codes.
 */
enum EAaErrorCcs
{
    EAaErrorCcs_AaMemAdapter_Logic           = AAERROR_CCS(0),   /**< AaMemAdapter internal logic error */
    EAaErrorCcs_AaMemAdapter_Unref_Violation = AAERROR_CCS(1),   /**< AaMemAdapter detected buffer usage after unref */
    EAaErrorCcs_AaMemAdapter_Duplicate_Unref = AAERROR_CCS(2),   /**< AaMemAdapter detected dumplicated unrefing */
    EAaErrorCcs_AaMemAdapter_Invalid_Block   = AAERROR_CCS(3),   /**< AaMemAdapter detected invalid memory block */
    EAaErrorCcs_AaMemAdapter_Internal_Error  = AAERROR_CCS(4),   /**< AaMemAdapter unspecified internal error */

    EAaErrorCcs_AaMem_Exception              = AAERROR_CCS(5),   /**< AaMem generic exception code */

    EAaErrorCcs_AaSysMb_Exception            = AAERROR_CCS(8),   /**< AaSysMb generic exception code */
    EAaErrorCcs_AaSysMb_SyncFailure          = AAERROR_CCS(9),   /**< AaSysMb detected synchronization error between
                                                                      SysMb Server and Local Proxy. */
    EAaErrorCcs_AaSysMb_InvalidPublication   = AAERROR_CCS(10),  /**< AaSysMb detected invalid/overlapping publication */
    EAaErrorCcs_AaSysMb_InvalidParam         = AAERROR_CCS(11),  /**< Invalid parameter given to API function */
    EAaErrorCcs_AaSysMb_ServerNotReady       = AAERROR_CCS(12),  /**< SysMb server is not running, but it is needed to
                                                                      complete requested operation */

    EAaErrorCcs_AaPro_InvalidParam           = AAERROR_CCS(13),  /**< Invalid parameter given to AaPro API function */
    EAaErrorCcs_AaPro_MemAllocFailure        = AAERROR_CCS(14),  /**< AaPro internal memory allocation failure */
    EAaErrorCcs_AaPro_EuCreationFailed       = AAERROR_CCS(15),  /**< AaPro EU creation failure */
    EAaErrorCcs_AaPro_UnexpectedMessage      = AAERROR_CCS(16),  /**< AaPro received unexpected message */
    EAaErrorCcs_AaPro_NonCriticalExited      = AAERROR_CCS(17),  /**< AaPro Supervision report: Non critical application exited */
    EAaErrorCcs_AaPro_CriticalExited         = AAERROR_CCS(18),  /**< AaPro Supervision report: Critical application exited*/
    EAaErrorCcs_AaPro_Reserved1              = AAERROR_CCS(19),  /**< AaPro reserved error code 1 */
    EAaErrorCcs_AaPro_Reserved2              = AAERROR_CCS(20),  /**< AaPro reserved error code 2 */

    EAaErrorCcs_AaSem_InvalidParameter       = AAERROR_CCS(21),  /**< AaSem invalid parameter error */
    EAaErrorCcs_AaSem_CreationFailed         = AAERROR_CCS(22),  /**< AaSem creation failed error */
    EAaErrorCcs_AaSem_MaxRecursion           = AAERROR_CCS(23),  /**< Maximum recursion exceeded (in AaSemReMutex) */
    EAaErrorCcs_AaSem_LockNotOwned           = AAERROR_CCS(24),  /**< Tried to unlock a lock not owned by current EU */
    EAaErrorCcs_AaSem_Reserved1              = AAERROR_CCS(25),  /**< AaSem reserved error code 1 */
    EAaErrorCcs_AaSem_Reserved2              = AAERROR_CCS(26),  /**< AaSem reserved error code 2 */
    EAaErrorCcs_AaSem_Reserved3              = AAERROR_CCS(27),  /**< AaSem reserved error code 3 */
    EAaErrorCcs_AaSem_Reserved4              = AAERROR_CCS(28),  /**< AaSem reserved error code 4 */

    EAaErrorCcs_AaFile_MemAllocFailure       = AAERROR_CCS(29),  /**< AaFile internal memory allocation failure */
    EAaErrorCcs_AaFile_InvalidVolume         = AAERROR_CCS(30),  /**< Requested volume does not found */
    EAaErrorCcs_AaFile_Exception             = AAERROR_CCS(31),  /**< AaFile generic exception code */

    EAaErrorCcs_AaTrbl_Exception             = AAERROR_CCS(32),  /**< AaTrbl generic exception code */
    EAaErrorCcs_AaTrbl_CbError               = AAERROR_CCS(33),  /**< AaTrbl - callback function returned unspecified error */

    EAaErrorCcs_AaSysTime_MemAllocFailure    = AAERROR_CCS(34),  /**< AaSysTime memory alloc failed   */
    EAaErrorCcs_AaSysTime_InternalError      = AAERROR_CCS(35),  /**< AaSysTime internal error        */
    EAaErrorCcs_AaSysTime_UnexpectedMsg      = AAERROR_CCS(36),  /**< AaSysTime unexpected message    */
    EAaErrorCcs_AaSysTime_Reserved1          = AAERROR_CCS(37),  /**< AaSysTime reserved error code 1 */
    EAaErrorCcs_AaSysTime_Reserved2          = AAERROR_CCS(38),  /**< AaSysTime reserved error code 2 */
    EAaErrorCcs_AaSysTime_Reserved3          = AAERROR_CCS(39),  /**< AaSysTime reserved error code 3 */
    EAaErrorCcs_AaSysTime_Reserved4          = AAERROR_CCS(40),  /**< AaSysTime reserved error code 4 */

    EAaErrorCcs_AaWcdmaTime_MemAllocFailure  = AAERROR_CCS(41),  /**< AaWcdmaTime memory alloc failed   */
    EAaErrorCcs_AaWcdmaTime_Reserved1        = AAERROR_CCS(42),  /**< AaWcdmaTime reserved error code 1 */
    EAaErrorCcs_AaWcdmaTime_Reserved2        = AAERROR_CCS(43),  /**< AaWcdmaTime reserved error code 2 */

    EAaErrorCcs_AaLteTime_MemAllocFailure    = AAERROR_CCS(44),  /**< AaLteTime memory alloc failed   */
    EAaErrorCcs_AaLteTime_Reserved1          = AAERROR_CCS(45),  /**< AalteTime reserved error code 1 */
    EAaErrorCcs_AaLteTime_Reserved2          = AAERROR_CCS(46),  /**< AaLteTime reserved error code 2 */

    EAaErrorCcs_AaDma_InternalError          = AAERROR_CCS(47),  /**< AaDma - Internal error*/

    EAaErrorCcs_AaSysLog_MemAllocFailure     = AAERROR_CCS(48),  /**< AaSysLog memory alloc failed   */
    EAaErrorCcs_AaSysLog_InternalError       = AAERROR_CCS(49),  /**< AaSysLog internal error        */
    EAaErrorCcs_AaSysLog_UnexpectedMsg       = AAERROR_CCS(50),  /**< AaSysLog unexpected message    */
    EAaErrorCcs_AaSysLog_Reserved1           = AAERROR_CCS(51),  /**< AaSysLog reserved error code 1 */
    EAaErrorCcs_AaSysLog_Reserved2           = AAERROR_CCS(52),  /**< AaSysLog reserved error code 2 */

    EAaErrorCcs_AaMemAdapter_PoolExhaust_Error = AAERROR_CCS(53),/**< AaMemAdapter detected that a pool is almost full */

    EAaErrorCcs_AaGpuCount_InvalidParameter = AAERROR_CCS(54),   /**< AaGpuCount detected invalid parameter */
    EAaErrorCcs_AaGpuCount_AllocationFailed = AAERROR_CCS(55),   /**< AaGpuCount allocation failed */
    EAaErrorCcs_AaGpuCount_Reserved1        = AAERROR_CCS(56),   /**< AaGpuCount reserved error code 1 */
    EAaErrorCcs_AaGpuCount_ReadOnly         = AAERROR_CCS(57),   /**< AaGpuCount read-only handler is used */

    EAaErrorCcs_AaGpuDur_InvalidParameter   = AAERROR_CCS(58),   /**< AaGpuDur detected invalid parameter */
    EAaErrorCcs_AaGpuDur_AllocationFailed   = AAERROR_CCS(59),   /**< AaGpuDur allocation failed */
    EAaErrorCcs_AaGpuDur_Reserved1          = AAERROR_CCS(60),   /**< AaGpuDur reserved error code 1 */
    EAaErrorCcs_AaGpuDur_ReadOnly           = AAERROR_CCS(61),   /**< AaGpuDur read-only handler is used */

    EAaErrorCcs_AaGpuFreq_InvalidParameter  = AAERROR_CCS(62),   /**< AaGpuFreq detected invalid parameter */
    EAaErrorCcs_AaGpuFreq_AllocationFailed  = AAERROR_CCS(63),   /**< AaGpuFreq allocation failed */
    EAaErrorCcs_AaGpuFreq_Reserved1         = AAERROR_CCS(64),   /**< AaGpuFreq reserved error code 1 */
    EAaErrorCcs_AaGpuFreq_ReadOnly          = AAERROR_CCS(65),   /**< AaGpuFreq read-only handler is used */

    EAaErrorCcs_AaGpuHistogram_InvalidParameter  = AAERROR_CCS(66),   /**< AaGpuHistogram detected invalid parameter */
    EAaErrorCcs_AaGpuHistogram_AllocationFailed  = AAERROR_CCS(67),   /**< AaGpuHistogram allocation failed */
    EAaErrorCcs_AaGpuHistogram_Reserved1         = AAERROR_CCS(68),   /**< AaGpuHistogram reserved error code 1 */
    EAaErrorCcs_AaGpuHistogram_ReadOnly          = AAERROR_CCS(69),   /**< AaGpuHistogram read-only handler is used */

    EAaErrorCcs_AaSysCom_MemAllocFailure    = AAERROR_CCS(70),   /**< AaSysCom memory allocation failure */
    EAaErrorCcs_AaSysCom_InvalidParameter   = AAERROR_CCS(71),   /**< AaSysCom detected invalid parameter */
    EAaErrorCcs_AaSysCom_CPidNotRegistered  = AAERROR_CCS(72),   /**< AaSysCom couldn't find cPid */
    EAaErrorCcs_AaSysCom_Reserved3          = AAERROR_CCS(73),   /**< AaSysCom reserved error code 3 */

    EAaErrorCcs_AaTrace_MsgCreationFailure  = AAERROR_CCS(74),   /**< AaTrace message allocation failed */

    EAaErrorCcs_AaStartup_HwapiStartupFailed  = AAERROR_CCS(75),   /**< FSM-Rel3 Hwapi startup failed (sys.hwapi.online tag not set in time)  */

    EAaErrorCcs_AaSysCom_CorruptedMessage   = AAERROR_CCS(76),   /**< AaSysCom (or AaRTOSApi) detected corrupted message */
    EAaErrorCcs_AaSysCom_NotSupported       = AAERROR_CCS(77),   /**< AaSysCom (or AaRTOSApi) unsupported operation */
    EAaErrorCcs_AaSysCom_UserRegisterFailed = AAERROR_CCS(78),   /**< AaSysCom user register failure due to invalid parameter */
    EAaErrorCcs_AaSysCom_Reserved5          = AAERROR_CCS(79),   /**< AaSysCom reserved error code 5 */
    EAaErrorCcs_AaSysCom_Reserved6          = AAERROR_CCS(80),   /**< AaSysCom reserved error code 6 */
    EAaErrorCcs_AaSysCom_Reserved7          = AAERROR_CCS(81),   /**< AaSysCom reserved error code 7 */

    EAaErrorCcs_AaCpu_MutexLockFailed       = AAERROR_CCS(82),   /**< AaCpu error during mutex lock (pthread_mutex_lock) */
    EAaErrorCcs_AaCpu_MutexUnlockFailed     = AAERROR_CCS(83),   /**< AaCpu error during mutex unlock (pthread_mutex_unlock) */
    EAaErrorCcs_AaCpu_Reserved1             = AAERROR_CCS(84),   /**< AaCpu reserved errpr code 1 */
    EAaErrorCcs_AaCpu_Reserved2             = AAERROR_CCS(85),   /**< AaCpu reserved errpr code 2 */
    EAaErrorCcs_AaCpu_Reserved3             = AAERROR_CCS(86),   /**< AaCpu reserved errpr code 3 */
    EAaErrorCcs_AaCpu_Reserved4             = AAERROR_CCS(87),   /**< AaCpu reserved errpr code 4 */

    EAaErrorCcs_AaRTOSApi_EuIdAllocFailed   = AAERROR_CCS(88),   /**< AaRTOSApi allocation of EuId failed */
    EAaErrorCcs_AaStartup_Exception         = AAERROR_CCS(89),   /**< AaStartup generic exception code */
    EAaErrorCcs_AaRTOSApi_Exception         = AAERROR_CCS(90),   /**< AaRTOSApi general exception */

    EAaErrorCcs_AaRedundancy_ShmCreateFailure = AAERROR_CCS(91), /**< AaRedundancy shm creation exception */
    EAaErrorCcs_AaRedundancy_ShmOpenFailure   = AAERROR_CCS(92), /**< AaRedudnancy shm open exception */

    EAaErrorCcs_AaConfigRad_FlagSettingError  = AAERROR_CCS(93), /**< AaConfigRad R&D flag setting failed */
    EAaErrorCcs_AaSysComGw_AppStartFailed     = AAERROR_CCS(94), /**< AaSysComGw separate application start failed */

    EAaErrorCcs_Last                                   /**< Not usable value, let always be the last! */
};

/*@}*/

#endif /* _AAERRORCODEDEFINITIONS_H */
