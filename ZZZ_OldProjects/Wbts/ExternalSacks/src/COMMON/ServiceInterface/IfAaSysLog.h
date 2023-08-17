/** @file
*   @brief Contains AaSysLog API printing interface
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2017, 2019 Nokia. All rights reserved.$
*/

#ifndef _IFAASYSLOG_H
#define _IFAASYSLOG_H

/************************** DOXYGEN GROUPS ************************************/

/**
 *  @defgroup dgAaSysLog AaSysLog API
 *  @ingroup  dgBasicSystemSw
 *
 *  Common Computer and Support SW System Logging Service.
 *
 *  Service provides uniform API for tracing system actions. Service
 *  helps to create system log.
 *
 *  @cond AASYSLOG_NO_DOXYGEN
 *
 *  Application Programming Interface.
 *
 *  For more information see API specification on IMS:
 *  https://sharenet-ims.inside.nokiasiemensnetworks.com/livelink/livelink?func=ll&objId=396832787&objAction=Browse
 *
 *  @endcond
 */

/*@{*/
/*@}*/

/************************** INCLUDED FILES ************************************/

#include "CcsCommon.h"
#include <glo_def.h>
#include <stdarg.h>
#include <IfAaSysLog_Defs.h>

#ifdef __cplusplus
extern "C"{
#endif

/************************** PUBLIC DECLARATIONS *******************************/
/**
* @defgroup dgAaSysLogApiCommon AaSysLog COMMON API
* @ingroup dgAaSysLog
*
*/
/*@{*/


/************************** PUBLIC INTERFACES (CCS_COMMON_API)*********************************/

/**
*******************************************************************************
*
*   @brief    Offers 'printf'-style log printing
*
*   @param[in]  severityLevel           Severity level of print.
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  ...                     Variable amount of parameters.
*
*   @par Description:
*   This function offers the ansi-C 'printf'-style log printing.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters.
*   MCU: Print can not be called from interrupt process or kernel error
*   situation.
*   DSP: Print can not be called from kernel error situation.
*
*   @par Example:
*   Following example shows basic usage of print function.
*/
/**
*   @code
*   u32 channel = 34;
*
*   AaSysLogPrint(EAaSysLogSeverityLevel_Debug, "Channel:%d", channel);
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
*
******************************************************************************/
void AaSysLogPrint(const EAaSysLogSeverityLevel severityLevel,
                   const char*                  unformattedStringPtr,
                   ... )PRINTATTR23;

/**
*******************************************************************************
*
*   @brief    Offers 'printf'-style log printing
*
*   @param[in]  severityLevel           Severity level of print.
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  args                    Variable argument list.
*
*   @par Description:
*   This function offers the ansi-C 'printf'-style log printing.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters.
*   MCU: Print can not be called from interrupt process or kernel error
*   situation.
*   DSP: Print can not be called from kernel error situation.
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
void AaSysLogVPrint(const EAaSysLogSeverityLevel severityLevel,
                    const char*                  unformattedStringPtr,
                    va_list                      args)PRINTATTR20;

/**
*******************************************************************************
*
*   @brief      Offers 'printf'-style log printing with the line number and
*               file name.
*
*   @param[in]  severityLevel           Severity level of print.
*   @param[in]  lineNumber              Line number.
*   @param[in]  fileName                String for the file name.
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  ...                     Variable amount of parameters.
*
*   @par Description:
*   This function offers the ansi-C 'printf'-style log printing adding to
*   output the line number and the file name where print function call was.
*   Note that function accepts various number of parameters.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters.
*   MCU: Print can not be called from interrupt process or kernel error
*   situation.
*   DSP: Print can not be called from kernel error situation.
*
*   @par Example:
*   Following example shows basic usage of print function. __LINE__ and
*   __FILE__ macros comes from ANSI-C.
*/
/**
*   @code
*   u32 channel = 34;
*
*   AaSysLogPrintD(EAaSysLogSeverityLevel_Debug,
*                  __LINE__,
*                  __FILE__,
*                  "Channel:%d",
*                  channel);
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
*
******************************************************************************/
void AaSysLogPrintD(const EAaSysLogSeverityLevel severityLevel,
                    const u32                    lineNumber,
                    const char*                  fileName,
                    const char*                  unformattedStringPtr,
                    ... )PRINTATTR45;

/**
*******************************************************************************
*
*   @brief      Offers reduced 'printf'-style log printing
*
*   @param[in]  severityLevel        Severity level of print.
*   @param[in]  plainCharString      Print string without format characters.
*   @param[in]  numberOfValidParams  Number of parameters that are
*                                    printed to log.
*   @param[in]  parameter1           First numerical argument.
*   @param[in]  parameter2           Second numerical argument.
*
*   @par Description:
*   This function offers the reduced 'printf'-style log printing. Function uses
*   less clock cycles than non-reduced print functions. Function accepts
*   a string and only two unsigned integer number as parameters.
*   Use of numberOfValidParams parameter:
*   0 = None of the parameters is included into the print.
*   1 = First parameter is included.
*   2 = Both parameters are included.
*   3,4,... Illegal value, prints nothing.
*   -1 = First parameter is excluded from the print, second parameter is
*        printed.
*   -2 = Both parameters are excluded from the print, same as 0.
*   -3,-4,... Illegal value, prints nothing.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters.
*   MCU: Print can not be called from interrupt process or kernel error
*   situation.
*   DSP: Print can not be called from kernel error situation.
*
*   @par Example:
*   Following example shows how to print one value parameter.
*/
/**
*   @code
*   u32 channel = 34;
*
*   AaSysLogPrintPmax2(EAaSysLogSeverityLevel_Info,
*                      "Channel:",
*                      1,
*                      channel,
*                      0);
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
*
******************************************************************************/
void AaSysLogPrintPmax2(const EAaSysLogSeverityLevel severityLevel,
                        const char*                  plainCharString,
                        const i32                    numberOfValidParams,
                        const u32                    parameter1,
                        const u32                    parameter2);

/**
*******************************************************************************
*
*   @brief      Offers the memory dump to log.
*
*   @param[in]  severityLevel           Severity level of the print.
*   @param[in]  dataBuffer              Pointer to data buffer.
*   @param[in]  dataBufferSizeInBytes   Buffer size in bytes.
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  ...                     Variable amount of parameters.
*
*   @par Description:
*   This function offers the memory dump to log.
*   The first print is information about print area: name, address and size.
*   After that data is printed in 8 bit wide hexadecimal format.
*   Memory print format is: {SysLog header} {Address} {16 bytes of data}
*   Format example:
*   {SysLog header}: 0x00912728 12345678 12345678 12345678 12345678
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters.
*   MCU: Print can not be called from interrupt process or kernel error
*   situation.
*   DSP: Print can not be called from kernel error situation.
*
*   @par Example:
*   Following example prints buffer data to system log.
*/
/**
*   @code
*   u8  buffer[80] = "This is my buffer which data is dumped to system log";
*   u32 bufferNumber = 23;
*
*   AaSysLogPrintHD(EAaSysLogSeverityLevel_Debug,
*                   buffer,
*                   sizeof(buffer),
*                   "test buffer %d",
*                   bufferNumber);
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
*
*******************************************************************************/
void AaSysLogPrintHD(const EAaSysLogSeverityLevel severityLevel,
                     const void*                  dataBuffer,
                     const u32                    dataBufferSizeInBytes,
                     const char*                  unformattedStringPtr,
                     ...)PRINTATTR45;

/**
*******************************************************************************
*
*   @brief      Offers feature based print.
*
*   @param[in]  severityLevel           Severity level of the print.
*   @param[in]  feature                 feature identifier
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  ...                     Variable amount of parameters
*
*   @par Description:
*   Function for print feature print. Prints the user-specified string into
*   system log.
*
*   Logging Service gets feature name from feature Id.
*
*   Note! Feature id based enable/disable is only working when print severity
*   level is debug. If severity level is some other, feature id value check is
*   not done. Print is always printed based on general print filters.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters.
*   MCU: Print can not be called from interrupt process or kernel error
*   situation.
*   DSP: Print can not be called from kernel error situation.
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
void AaSysLogPrintE(const EAaSysLogSeverityLevel severityLevel,
                    const u32                    feature,
                    const char*                  unformattedStringPtr,
                    ...)PRINTATTR34;

/**
*******************************************************************************
*
*   @brief      Offers feature based print.
*
*   @param[in]  severityLevel           Severity level of the print.
*   @param[in]  featureId                 feature identifier
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  args                    Variable argument list
*
*   @par Description:
*   Function for print feature print. Prints the user-specified string into
*   system log.
*
*   Logging Service gets feature name from feature Id.
*
*   Note! Feature id based enable/disable is only working when print severity
*   level is debug. If severity level is some other, feature id value check is
*   not done. Print is always printed based on general print filters.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters.
*   MCU: Print can not be called from interrupt process or kernel error
*   situation.
*   DSP: Print can not be called from kernel error situation.
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
void AaSysLogVPrintE(const EAaSysLogSeverityLevel severityLevel,
                     const u32                    featureId,
                     const char*                  unformattedStringPtr,
                     va_list                      args)PRINTATTR30;
/**
*******************************************************************************
*
*   @brief      Offers feature based print with priority.
*
*   @param[in]  severityLevel           Severity level of the print.
*   @param[in]  feature                 feature identifier
*   @param[in]  priority                Priority of the print
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  ...                     Variable amount of parameters
*
*   @par Description:
*   Function for print feature print feature level and log priority check.
*   Prints the user-specified string into system log.
*
*   Logging Service gets feature name from feature Id.
*
*   Note! Feature ID R&D tag can control input level filtering (lower 16 bits
*   of R&D value) and output level filtering (higher 16 bits of R&D value).
*   Logs with severity level lower than the Feature ID R&D tag input level
*   value are disabled on input and logs with severity level lower than the
*   Feature ID R&D tag output level value are disabled on output (meaning
*   they are written to the runtime log but not sent to output device).
*   Log priority provides means to filter logs, based on their priority and
*   current AaSysLog load level.
*   Severity levels and priorities are mapped accordingly:
*       - EAaSysLogSeverityLevel_Debug by default to EAaSysLogPriority_01
*       - EAaSysLogSeverityLevel_Info by default to EAaSysLogPriority_02
*       - EAaSysLogSeverityLevel_Error and EAaSysLogSeverityLevel_Warning
*         by default to EAaSysLogPriority_03
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters.
*   MCU: Print can not be called from interrupt process or kernel error
*   situation.
*   DSP: Print can not be called from kernel error situation.
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
void AaSysLogPrintL(const EAaSysLogSeverityLevel severityLevel,
                    const u32                    feature,
                    const EAaSysLogPriority      priority,
                    const char*                  unformattedStringPtr,
                    ...)PRINTATTR45;

/**
*******************************************************************************
*
*   @brief      Offers feature based print with priority.
*
*   @param[in]  severityLevel           Severity level of the print.
*   @param[in]  featureId               Feature identifier
*   @param[in]  priority                Priority of the print
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  args                    Variable argument list
*
*   @par Description:
*   Function for print feature print feature level and log priority check.
*   Prints the user-specified string into system log.
*
*   Logging Service gets feature name from feature Id.
*
*   Note! Feature ID R&D tag can control input level filtering (lower 16 bits
*   of R&D value) and output level filtering (higher 16 bits of R&D value).
*   Logs with severity level lower than the Feature ID R&D tag input level
*   value are disabled on input and logs with severity level lower than the
*   Feature ID R&D tag output level value are disabled on output (meaning
*   they are written to the runtime log but not sent to output device).
*   Log priority provides means to filter logs, based on their priority and
*   current AaSysLog load level.
*   Severity levels and priorities are mapped accordingly:
*       - EAaSysLogSeverityLevel_Debug by default to EAaSysLogPriority_01
*       - EAaSysLogSeverityLevel_Info by default to EAaSysLogPriority_02
*       - EAaSysLogSeverityLevel_Error and EAaSysLogSeverityLevel_Warning
*         by default to EAaSysLogPriority_03
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters.
*   MCU: Print can not be called from interrupt process or kernel error
*   situation.
*   DSP: Print can not be called from kernel error situation.
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
void AaSysLogVPrintL(const EAaSysLogSeverityLevel severityLevel,
                     const u32                    featureId,
                     const EAaSysLogPriority      priority,
                     const char*                  unformattedStringPtr,
                     va_list                      args)PRINTATTR40;


/**
*******************************************************************************
*
*   @brief      Offers system feature based print with severity.
*
*   @param[in]  severityLevel           System severity level of the print.
*   @param[in]  featureId               Feature identifier
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  ...                     Variable amount of parameters
*
*   @par Description:
*   Function for storing the EFS specified prints used for logging events important from BTS state pov.
*   Prints are added to dedicated system feature log if registered otherwise print will be added to generic system buffer.
*
*   Info print example:
*   00 FCT-1011-B-CCS <2015-10-06T09:24:01.883257Z> 2C8D-HWR SYSTEM_INF/CCS/AaStartup, AaStartup_Linux - AaStartupCeStartup() : CC&S CE startup successful
*
*   Error print example:
*   00 FCT-1011-B-CCS <2015-10-06T09:24:01.890790Z> 2CE2-CcsDaemonCeStar SYSTEM_ERR/CCS/CCSDaemon, openAppExeDefFile(): Failed to open application definition file '/rom/AppDef.txt'
*
*   Note: Existence of EU name in the logs depends on if feature LBT2678 is enabled.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   Prints are sent to CCSDaemon on masternode only if master node Id is set, before that prints are being sent to local CCSDaemon and processed as normal prints.
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters.
*   MCU/RT: Print can not be called from interrupt process or kernel error
*   situation.
*   DSP: Print can not be called from kernel error situation.
*
*   @par Example:
*   @code
*   #include <IfAaSysLog.h>
*
*   AaSysLogSystemPrint(EAaSysLogSystemSeverityLevel_Info, ERadCcs_PrintAaSysTime, "SYSTEM PRINT 1");
*
*   const u32 logSize = 1024 * 256;
*   const u32 logCount = 4;
*   EAaSysLogSystemFeatureBufferRegister retval = AaSysLogRegisterSystemFeatureBuffer( ERadCcs_PrintAaSysTime,
*                                                                                      "AaSysTime",
*                                                                                      logSize,
*                                                                                      logCount );
*   if( EAaSysLogSystemFeatureBufferRegister_Ok != retval && EAaSysLogSystemFeatureBufferRegister_Exists == retval )
*   {
*        AaSysLogPrint( EAaSysLogSeverityLevel_Error, "Domain buffer not registered, reason %d", retval );
*        return;
*   }
*   AaSysLogSystemPrint(EAaSysLogSystemSeverityLevel_Info, ERadCcs_PrintAaSysTime, "SYSTEM PRINT 1");
*
*   Output:
*   systemlog_1.log:
*   00 FCT-1011-B-CCS <2015-10-06T09:24:01.883257Z> 2C8D-SysTIme SYSTEM_INF/CCS/AaSysTime, SYSTEM PRINT 1
*
*   systemlog_AaSysTime_1.log
*   00 FCT-1011-B-CCS <2015-10-06T09:24:01.983257Z> 2C8D-SysTIme SYSTEM_INF/CCS/AaSysTime, SYSTEM PRINT 2
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
void AaSysLogSystemPrint(const EAaSysLogSystemSeverityLevel severityLevel,
                         const u32                  featureId,
                         const char*                unformattedStringPtr,
                         ...)PRINTATTR34;

/*@}*/

/*----------------------- PUBLIC INTERFACES (MCU API)-------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*  _IFAASYSLOG_H */
