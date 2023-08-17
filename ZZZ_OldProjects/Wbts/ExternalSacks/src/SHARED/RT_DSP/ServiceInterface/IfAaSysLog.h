/**
********************************************************************************
* @file
*
* @brief                 AaSysLog API
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_IFAASYSLOG_H
#define _RT_DSP_IFAASYSLOG_H

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaSysLog AaSysLog API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaSysLog AaSysLog API for RT and OSECK DSP nodes
* @{
*/

#ifdef __cplusplus
extern "C" {
#endif


/**
*******************************************************************************
*
*   @brief    Offers 'printf'-style log printing with adjustable priority.
*
*   @param[in]  severityLevel           Severity level of print.
*   @param[in]  printPriority           Priority of the print
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  ...                     Variable amount of parameters.
*
*   @par Description:
*   Normally, when the buffer load increases then the low importance prints
*   are discarded. The priority parameter allows to artifically change the
*   behaviour and keep the low-severity-level prints in the buffer even if
*   the buffer load increases and the print would be discarded otherwise.
*   It is also possible to decrease the default priority.
*
*   @par Lowest priority level to buffer load mapping:
*   EAaSysLogBufferLoadLevel_01        All priority levels are accepted.
*   EAaSysLogBufferLoadLevel_02        At least EAaSysLogPriority_02 needed.
*   EAaSysLogBufferLoadLevel_03        Only EAaSysLogPriority_03 accepted.
*   EAaSysLogBufferLoadLevel_Full      no prints accepted
*
*   @par Default priority for severity level mapping:
*   EAaSysLogSeverityLevel_Debug       EAaSysLogPriority_01
*   EAaSysLogSeverityLevel_Info        EAaSysLogPriority_02
*   EAaSysLogSeverityLevel_Warning     EAaSysLogPriority_02
*   EAaSysLogSeverityLevel_Error       EAaSysLogPriority_03
*   EAaSysLogSeverityLevel_Vip         EAaSysLogPriority_03
*
*   @par Restrictions:
*   User print string should not contain newline (CR or LF) characters.
*   RT: Print can't be called from interrupt process or kernel error situation.
*   DSP: Print can't be called from kernel error situation.
*
*   @par Example:
*   Following example shows basic usage of print function.
*
*   @code
*   AaSysLogPrintPrio(EAaSysLogSeverityLevel_Info,
*                     EAaSysLogPriority_03,
*                     "RingBufferAddress: 0x%08x",
*                     ringBufferPtr);
*   @endcode
*
*   @see AaSysLogVPrintPrio
*
******************************************************************************/
void AaSysLogPrintPrio(const EAaSysLogSeverityLevel severityLevel,
                       const EAaSysLogPriority      printPriority,
                       const char*                  unformattedStringPtr,
                       ... );


/**
*******************************************************************************
*
*   @brief    Offers 'printf'-style log printing with adjustable priority.
*
*   @param[in]  severityLevel           Severity level of print.
*   @param[in]  printPriority           Priority of the print
*   @param[in]  unformattedStringPtr    Print string in ANSI-C printf format.
*   @param[in]  args                    Variable argument list.
*
*   @par Description:
*   The same as AaSysLogPrintPrio, but with variable argument list "var_args"
*   in place of variable amount of parameters.
*   @see AaSysLogPrintPrio
*
*   @par Restrictions:
*   User print string should not contain newline (CR or LF) characters.
*   RT: Print can't be called from interrupt process or kernel error situation.
*   DSP: Print can't be called from kernel error situation.
*
*   @see AaSysLogPrintPrio
*
******************************************************************************/
void AaSysLogVPrintPrio(const EAaSysLogSeverityLevel severityLevel,
                        const EAaSysLogPriority      printPriority,
                        const char*                  unformattedStringPtr,
                        va_list                      args);


#ifdef __cplusplus
}
#endif

/** @} */   /* dgUpCcsRtDspAaSysLog */
/** @} */   /* dgUpCcsAaSysLog */
/** @} */   /* dgUpCcs */

#endif  /* _RT_DSP_IFAASYSLOG_H */

