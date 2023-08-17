/** @file
*   @brief Contains AaSysLog API printing interface
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: Copyright 2017 Nokia. All rights reserved.$
*/

#ifndef _MCU_RT_IFAASYSLOG_H
#define _MCU_RT_IFAASYSLOG_H

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @defgroup dgAaSysLogApiMcu AaSysLog MCU API
 * @ingroup dgAaSysLog
 *
 */
 /*@{*/

/**
*   @brief Constant which defines maximum timeout
*
*   @see   AaSysLogPrintETmo
*/
#define INFINITY_TIMEOUT        100000000

/**
*******************************************************************************
*
*   @brief      Offers reduced 'printf'-style log printing
*
*   @param[in]  severityLevel        Severity level of print.
*   @param[in]  featureId                 feature identifier
*   @param[in]  formattedStringPtr   Print string without format characters.
*   @param[in]  length               Size of print
*
*   @par Description:
*   This function offers the reduced 'printf'-style log printing. Function uses
*   less clock cycles than non-reduced print functions. Function accepts
*   a string and size of that string and feature Id.
*   It is reduced version of AaSysLogPrintPmax2, when number of parameters
*   is 0. It does not do any unnecessary string copying and temporary buffer
*   allocating and deallocating.  It is used for printing logs from LinuxListener
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
*   u32 length = (u32) (pptr() - pbase());
*
*   AaSysLogPrintP0LinuxListener(EAaSysLogSeverityLevel_Info,
*                                featureId,
*                                "String",
*                                length);
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
void AaSysLogPrintP0LinuxListener(const EAaSysLogSeverityLevel severityLevel,
                                  const u32   featureId,
                                  const char* formattedStringPtr,
                                  const u32 length);

/**
*******************************************************************************
*
*   @brief      Offers reduced 'printf'-style log printing
*
*   @param[in]  severityLevel        Severity level of print.
*   @param[in]  formattedStringPtr   Print string without format characters.
*   @param[in]  length               Size of print
*
*   @par Description:
*   This function offers the reduced 'printf'-style log printing. Function uses
*   less clock cycles than non-reduced print functions. Function accepts
*   a string and size of that string.
*   It is reduced version of AaSysLogPrintPmax2, when number of parameters
*   is 0. It does not do any unnecessary string copying and temporary buffer
*   allocating and deallocating.
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
*   u32 length = (u32) (pptr() - pbase());
*
*   AaSysLogPrintP0(EAaSysLogSeverityLevel_Info,
*                      "String",
*                      length);
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
void AaSysLogPrintP0(const EAaSysLogSeverityLevel severityLevel,
                     const char* formattedStringPtr,
                     const u32 length);

/**
*******************************************************************************
*
*   @brief      Offers feature based print.
*
*   @param[in]  severityLevel           Severity level of the print.
*   @param[in]  featureId               feature identifier
*   @param[in]  timeout                 timeout in miliseconds for mutex lock
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  ...                     Variable amount of parameters
*
*   @par Description:
*   Function for print feature print. Prints the user-specified string into
*   system log.
*
*   Logging Service gets feature name from feature Id.
*   This function waits for mutex for timeout time in miliseconds. If mutex
*   cannot be locked during this time, this function returns without adding
*   anything to syslog.
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
*   @see INFINITY_TIMEOUT
*
******************************************************************************/
void AaSysLogPrintETmo( const EAaSysLogSeverityLevel severityLevel,
                        const u32 featureId,
                        u32 timeout,
                        const char* unformattedStringPtr,
                        ... );

/**
*******************************************************************************
*
*   @brief      Offers feature based print.
*
*   @param[in]  severityLevel           Severity level of the print.
*   @param[in]  featureId               feature identifier
*   @param[in]  timeout                 timeout in miliseconds for mutex lock
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  args                    Variable argument list
*
*   @par Description:
*   Function for print feature print. Prints the user-specified string into
*   system log.
*
*   Logging Service gets feature name from feature Id.
*   This function waits for mutex for timeout time in miliseconds. If mutex
*   cannot be locked during this time, this function returns without adding
*   anything to syslog.
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
void AaSysLogVPrintETmo(const EAaSysLogSeverityLevel severityLevel,
                        const u32                    featureId,
                        u32                          timeout,
                        const char*                  unformattedStringPtr,
                        va_list                      args)PRINTATTR40;

/**
*******************************************************************************
*
*   @brief      Offers feature based print with feature levelling.
*
*   @param[in]  severityLevel           Severity level of the print.
*   @param[in]  feature                 Feature identifier
*   @param[in]  featureLevel            Feature level
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  ...                     Variable amount of parameters
*
*   @par Description:
*   Function for print feature print with feature level check. Prints the
*   user-specified string into system log.
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
*   characters. Print can not be called from interrupt process or kernel error
*   situation.
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
void AaSysLogPrintF(const EAaSysLogSeverityLevel severityLevel,
                    const u32                    feature,
                    const u32                    featureLevel,
                    const char*                  unformattedStringPtr,
                    ...)PRINTATTR45;

/**
*******************************************************************************
*
*   @brief      Offers feature based print with feature mask.
*
*   @param[in]  severityLevel           Severity level of the print.
*   @param[in]  featureId                 Feature identifier
*   @param[in]  featureMask             Feature mask
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  ...                     Variable amount of parameters
*
*   @par Description:
*   Function for print feature print with feature mask check. Print is allowed
*   to be printed if current feature id (R&D parameter) value passes the OR bit
*   operation with user given feature mask.
*
*   Note!   Feature id based enable/disable is only working when print severity
*           level is debug. If severity level is some other, feature id value
*           check is not done. Print is always printed based on general print
*           filters.
*
*   Note!   Function is mostly done for legacy software support. New software is
*           recommended to do so that, new feature id is reserved for different
*           parts of application prints and use AaSysLogPrintE() instead for
*           printing. This simplifies setting/controlling the prints at runtime!
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters. Print can not be called from interrupt process or kernel error
*   situation.
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
void AaSysLogPrintM(const EAaSysLogSeverityLevel severityLevel,
                    const u32                    featureId,
                    const u32                    featureMask,
                    const char*                  unformattedStringPtr,
                    ...)PRINTATTR45;

/**
*******************************************************************************
*
*   @brief      Offers print that can be called from interrupt process.
*
*   @param[in]  severityLevel           Severity level of the print.
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
    @param[in]  ...                     Variable amount of parameters.
*
*   @par Description:
*   Prints the user-specified string into the system log. Function can be
*   called from interrupt process context.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   User print string should not contain linefeed (LF) and carriage return (CR)
*   characters.
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
void AaSysLogPrintI(const EAaSysLogSeverityLevel severityLevel,
                    const char*                  unformattedStringPtr,
                    ...)PRINTATTR23;

/**
*******************************************************************************
*
*   @deprecated FUNCTION IS NOT SUPPORTED ANYMORE. PLEASE, REMOVE IT FROM YOUR SOURCE CODE.
*   @brief      Function for register output device to syslog.
*
*   @param[in]  name            Name of the device.
*   @param[in]  mode            Operation mode where device is working.
*   @param[in]  open            Device open callback function.
*   @param[in]  close           Device close callback function.
*   @param[in]  write           Device write callback function.
*   @param[in]  opaque          Pointer to device instance, this is passed to
*                               callback functions as a parameter.
*
*   @par Description:
*   Specifies the user device which will handle print output. Logging Service
*   output mode must be set to 'ALL' that device is taken to use.
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
*   @see
*
******************************************************************************/
EAaSysLogConfigureRetVal AaSysLogRegisterDevice(const char*             name,
                                                EAaSysLogOperationMode  mode,
                                                TAaSysLogDeviceOpenCb*  open,
                                                TAaSysLogDeviceCloseCb* close,
                                                TAaSysLogDeviceWriteCb* write,
                                                void*                   opaque);

/**
*******************************************************************************
*
*   @deprecated FUNCTION IS NOT SUPPORTED ANYMORE. PLEASE, REMOVE IT FROM YOUR SOURCE CODE.
*   @brief      Function for unregister output device.
*
*   @param[in]  name            Name of the device.
*
*   @par Description:
*   Remove user output device.
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
*   @see
*
******************************************************************************/
EAaSysLogConfigureRetVal AaSysLogUnregisterDevice(const char* name);

/**
*******************************************************************************
*
*   @deprecated FUNCTION IS NOT SUPPORTED ANYMORE. PLEASE, REMOVE IT FROM YOUR SOURCE CODE.
*   @brief      Function for set operation mode.
*
*   @param[in]  mode            Operation mode to be used.
*
*   @par Description:
*   Function for set Logging Service operation mode. If setting operation mode
*   to limited, all interface print functions operates as unsafely and
*   internally they do not use any Operating System or other calls that can
*   block print operation.
*
*   Warning! It is user responsibility to handle single access to print functions.
*
*   @par Errors:
*   No errors are defined.
*
*   @par Restrictions:
*   Currently normal mode setting is not supported.
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
EAaSysLogConfigureRetVal AaSysLogSetOperationMode(EAaSysLogOperationMode mode);

/**
*******************************************************************************
*
*   @brief      Function for get print filter input level.
*
*   @return     Current input level.
*
*   @par Description:
*   Query print filter input level.
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
*   @see
*
******************************************************************************/
EAaSysLogSeverityLevel AaSysLogGetInputLevel(void);

/**
*******************************************************************************
*
*   @brief Returns (current) runtime buffer utilization in percentage.
*
*   @return runtime buffer utilization in percentage
*
*   @par Errors:
*   None
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
u32 AaSysLogGetLogUtilization(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /*  _MCU_RT_IFAASYSLOG_H */
