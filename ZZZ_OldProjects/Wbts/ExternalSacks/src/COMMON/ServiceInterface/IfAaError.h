/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Generic error reporting and handling service interface
* @module                AaError
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAAERROR_H
#define _IFAAERROR_H

/**
*@defgroup dgAaError Error Reporting Service (AaError)
*@ingroup dgBasicComputingSw
*
* This is part of AaError defines Software Domains for Application Runtime
* Error reporting.
*/

/**
*@defgroup dgAaErrorApi API
*@ingroup dgAaError
*
* @{
*/

#include "CcsCommon.h"
#include <glo_def.h>
#include <IfAaConfig_Defs.h>

#include <AaErrorCodeDefinitions.h>

#ifdef __cplusplus
extern "C" {
#endif

/** following AaConfig tags are supported by the AaError */
/** Sets path for storing core file, value will be read by AaError at Startup,
    if not set a default value will be used. */
#define AAERROR_CONFIG_TAG_CORE_PATH "ccs.service.aaerror.core_path"

/**@brief Default path for saving core file
 * This path is not valid in all environments.
 */
#define AAERROR_DEFALUT_CONFIG_VOLUME "/rpram"

/** @brief definition for reset call back function */
typedef void TAaErrorResetCallback(void);

/** @brief definitions for watchdog call back functions*/
typedef void TAaErrorWdCallback(void);

/** @brief AaError exception fatality levels. */
typedef enum EAaErrorFatality
{
    EAaErrorFatality_NonFatal = 0, /**< Non-fatal exception. */
    EAaErrorFatality_Fatal,        /**< Fatal exception. */
    EAaErrorFatality_System,       /**< Fatal exception at system level. (DO NOT use directly!) */
    EAaErrorFatality_Supervision,  /**< Exception reported by a supervising application */

    EAaErrorFatality_NbrOf         /**< Last one. And keep it that way! */

} EAaErrorFatality;

/** @brief AaError exception fatality levels in convenience textual representation */
#define EAAERRORFATALITY_VALUES \
   { \
       "EAaErrorFatality_NonFatal", \
       "EAaErrorFatality_Fatal", \
       "EAaErrorFatality_System", \
       "EAaErrorFatality_Supervision", \
       "EAaErrorFatality_NbrOf", \
   }

/** @brief AaError error detectors. */
typedef enum EAaErrorDetector
{
    EAaErrorDetector_Application = 0, /**< Application detected the error. */
    EAaErrorDetector_Os,              /**< OS detected the error. */
    EAaErrorDetector_Ccs,             /**< CC&S SW detected the error. */

    EAaErrorDetector_NbrOf            /**< Last one. And keep it that way! */

} EAaErrorDetector;

/** @brief AaError error detector in convenience textual representation */
#define EAAERRORDETECTOR_VALUES \
   { \
       "EAaErrorDetector_Application", \
       "EAaErrorDetector_Os", \
       "EAaErrorDetector_Ccs", \
       "EAaErrorDetector_NbrOf", \
   }

/** @brief AaError return codes. */
typedef enum EAaErrorRet
{
    EAaErrorRet_Ok = 0,  /**< No errors occurred. */
    EAaErrorRet_Nok = 1, /**< Some error occurred. */

    EAaErrorRet_NbrOf    /**< Last one. And keep it that way! */

} EAaErrorRet;

/** @brief Type definition for error handler callback
*
* @param[in] detector  Detector of the reported error.
* @param[in] fatality  Fatality of the reported error.
* @param[in] exception Exception code of the reported error.
* @param[in] extra     Pointer to a extra error information of the reported error.
* @param[in] extraLen  Length of the user specified extra parameter.
*
* @return GLO_TRUE if the error is handled, GLO_FALSE if not
*/
typedef TBoolean TAaErrorHandler(const EAaErrorDetector detector, const EAaErrorFatality fatality,
                                 const i32 exception, const void* extra, u32 extraLen);

/** @brief AaErrorAssert(Pre/Post) evaluates given expression and if false (0) assertion is generated
*
* @param[in] __expression  Expression to be validated.
*
* @par Description:
* Conveniences macros for AaErrorAssertion function call. Assertions should be used to check
* logically impossible situations. If the "impossible" occurs, then something fundamental
* is clearly wrong in the system. The difference to error handling is that most error conditions
* are possible thus assertion should not to use for common error  handling since assertions
* does not allow gracefully recovery from errors. Execution never returns to the calling EE/EU.
*
* Pre- and postcondition checks can be distinguished using #AaErrorAssertPre and #AaErrorAssertPost
* macros.
*
* All assertions can be disabled at compiling time by defining #AAERROR_ASSERTION_DISABLED.
* Pre-assertions can be disabled at compiling time by defining #AAERROR_PRE_ASSERTION_DISABLED.
* Post-assertions can be disabled at compiling time by defining #AAERROR_POST_ASSERTION_DISABLED.
*
* @def AaErrorAssert
* @def AaErrorAssertPre
* @def AaErrorAssertPost
*
* @{
*/
#if !defined(AAERROR_ASSERTION_DISABLED)

#ifdef __KLOCWORK__
#define AaErrorAssert(__expression) do{if(!(__expression)) abort();}while(0)
#else
#define AaErrorAssert(__expression) \
   ((__expression) ? ((void)0) : AaErrorAssertion(#__expression, __FILE__, __LINE__))
#endif

# if !defined(AAERROR_PRE_ASSERTION_DISABLED)
#  define AaErrorAssertPre(__expression) \
    ((__expression) ? ((void)0) : AaErrorAssertion(#__expression, __FILE__, __LINE__))
# else
#  define AaErrorAssertPre(__expression) ((void)0)
# endif

# if !defined(AAERROR_POST_ASSERTION_DISABLED)
#  define AaErrorAssertPost(__expression) \
    ((__expression) ? ((void)0) : AaErrorAssertion(#__expression, __FILE__, __LINE__))
# else
#  define AaErrorAssertPost(__expression) ((void)0)
# endif

#else

# define AaErrorAssert(__expression) ((void)0)
# define AaErrorAssertPre(__expression) ((void)0)
# define AaErrorAssertPost(__expression) ((void)0)

#endif

/** @} */

/** @brief AaErrorRaise helpful macro to use AaErrorExeptionRaise function
*
* @param[in] __fatality     Fatality of the exception.
* @param[in] __code         Exception code.
* @param[in] __description  Description about the error in NULL-terminated string (optional).
* @param[in] __extra        Pointer to a extra information about the exception (optional).
* @param[in] __extraLen     Length of the extra information in bytes (optional).
*
* @par Description:
* Conveniences macros for AaErrorExceptionRaise function call.
*/
#define AaErrorRaise(__fatality, __code, __description) \
    AaErrorExceptionRaise(__fatality, __code,  GLO_NULL, 0, \
                          __description, __FILE__, __LINE__)



/** @brief AaErrorRaiseE helpful macro to use AaErrorExeptionRaise function
*
* @param[in] __fatality     Fatality of the exception.
* @param[in] __code         Exception code.
* @param[in] __description  Description about the error in NULL-terminated string (optional).
* @param[in] __extra        Pointer to a extra information about the exception (optional).
* @param[in] __extraLen     Length of the extra information in bytes (optional).
*
* @par Description:
* Conveniences macros for AaErrorExceptionRaise function call.
*/
#define AaErrorRaiseE(__fatality, __code, __description, __extra, __extraLen) \
    AaErrorExceptionRaise(__fatality, __code,  __extra, __extraLen, \
                          __description, __FILE__, __LINE__)

/*----------------------- PUBLIC INTERFACES (COMMON API) --------------------------------*/


/**
 * @defgroup dgAaErrorApiCommon AaError COMMON API
 * @ingroup  dgAaError
 */

/* @{ */

/**
*******************************************************************************
*   @brief  Raises an exception for handling.
*
*   @param[in] fatality     Fatality of the exception.
*   @param[in] code         Exception code.
*   @param[in] extra        Pointer to a extra information about the exception (optional).
*   @param[in] extraLen     Length of the extra information in bytes (optional).
*   @param[in] description  Description about the error in NULL-terminated string (optional).
*   @param[in] file         Pointer to a NULL-terminated string containing filename (optional).
*   @param[in] line         Line number in the file (optional).
*
*   @return GLO_TRUE if the error is handled, GLO_FALSE if not
*
*   @par Description:
*   This function raises an exception and if the exception fatality is
*   #EAaErrorFatality_Fatal, this function never returns. In case of
*   #EAaErrorFatality_NonFatal, error, function returns with return value
*   defining if the error has been handled (GLO_TRUE) or not (GLO_FALSE).
*   Optional parameters can be 0 or GLO_NULL.
*
*   @par Errors:
*   If invalid parameters are given to this call, #EAaErrorInternal_Recurse
*   exception is raised.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaError.h>
*   #include <AaErrorCodeDefinitions.h>
*
*   TCounterType* counter = ...
*
*   AaErrorExceptionRaise(EAaErrorFatality_NonFatal, EAaErrorCcs_AaGpuHistogram_ReadOnly,
*                         counter, sizeof(*counter), "tried to use read-only counter",
*                         __FILE__, __LINE__);
*
*   // Same can be achieved using helper macros
*   AaErrorRaise(EAaErrorFatality_NonFatal, EAaErrorCcs_AaGpuHistogram_ReadOnly,
*                "tried to use read-only counter");
*
*   // or if extra is needed
*   AaErrorRaiseE(EAaErrorFatality_NonFatal, EAaErrorCcs_AaGpuHistogram_ReadOnly,
*                "tried to use read-only counter", counter, sizeof(*counter));
*
*   @endcode
*
*   @par Usage:
*   There are helper macros #AaErrorRaise and #AaErrorRaiseE which sets some
*   parameters to default values if they are not needed.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaErrorRaise
*   @see AaErrorRaiseE
*
******************************************************************************/
TBoolean
AaErrorExceptionRaise(const EAaErrorFatality fatality, const i32 code,
                      const void* const extra, const u32 extraLen,
                      const char* const description, const char* const file,
                      const u32 line);

/**
*******************************************************************************
*   @brief  Raises assertion error.
*
*   @param[in] expression  Expression of the assertion error as NULL-terminated string
*   @param[in] file        Filename as NULL-terminated string
*   @param[in] line        Line number
*
*   @return None
*
*   @par Description:
*   Execution never returns to the calling EE/EU. NOTE! This function always
*   raises assertion error thus if checking for the expression is needed,
*   macros #AaErrorAssert, AaErrorAssertPre or AaErrorAssertPost must be used.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaError.h>
*
*   int value = 0;
*
*   AaErrorAssert(value == 0); // If value is not 0, assertion is generated
*
*   @endcode
*
*   @par Usage:
*   Macros #AaErrorAssert, #AaErrorAssertPre and #AaErrorAssertPost
*   are ment for wrapper to this call.
*
*   @par Rationale:
*   Assertions should be used to check logically impossible situations.
*   If the "impossible" occurs, then something fundamental is clearly wrong
*   in the system. Assertion should not be used for common error handling,
*   since assertions do not allow gracefully recovery from errors.
*
*   @par Future directions:
*   None
*
*   @see AaErrorAssert
*   @see AaErrorAssertPre
*   @see AaErrorAssertPost
*
******************************************************************************/
CCS_NORETURN void
AaErrorAssertion(const char* const expression, const char* const file, const u32 line);

/**
*******************************************************************************
*   @brief  Registers error handler callback for current EU.
*
*   @param[in] handlerImpl  Pointer to handler implementation
*
*   @return Pointer to previously registered handler or GLO_NULL.
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
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
TAaErrorHandler*
AaErrorEuHandlerRegister(TAaErrorHandler* handlerImpl);

/**
*******************************************************************************
*   @brief  Registers error handler callback for another EU.
*
*   @param[in] handlerImpl  Pointer to handler implementation
*   @param[in] euId         Id of the EU for the handler is registered
*
*   @return Pointer to previously registered handler or GLO_NULL.
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
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
TAaErrorHandler*
AaErrorEuHandlerRegisterFor(TAaErrorHandler* handlerImpl, const u32 euId);

/**
*******************************************************************************
*   @brief  Registers error handler callback for current EE.
*
*   @param[in] handlerImpl  Pointer to handler implementation
*
*   @return Pointer to previously registered handler or GLO_NULL.
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
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
TAaErrorHandler*
AaErrorEeHandlerRegister(TAaErrorHandler* handlerImpl);

/**
*******************************************************************************
*   @brief  Registers error handler callback for CE.
*
*   @param[in] handlerImpl  Pointer to handler implementation
*
*   @return Pointer to previously registered handler or GLO_NULL.
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
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
TAaErrorHandler*
AaErrorCeHandlerRegister(TAaErrorHandler* handlerImpl);

/**
*******************************************************************************
*
*   @brief  Executes startup at EE level.
*
*   @param None
*
*   @return EAaErrorRet_Ok
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
EAaErrorRet
AaErrorEeStartup(void);

/**
*******************************************************************************
*
*   @brief  Executes shutdown at EE level.
*
*   @param None
*
*   @return EAaErrorRet_Ok
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
EAaErrorRet
AaErrorEeShutdown(void);

/**
*******************************************************************************
*
*   @brief  Executes startup at CE level.
*
*   @param None
*
*   @return EAaErrorRet_Ok
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
EAaErrorRet
AaErrorCeStartup(void);

/*******************************************************************************
*
*   @brief  Executes shutdown at CE level.
*
*   @param None
*
*   @return EAaErrorRet_Ok
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
EAaErrorRet
AaErrorCeShutdown(void);

/**
*******************************************************************************
*
*   @brief  Registers WatchdogCallback 'feed' function for AaError.
*
*   @param[in] feedWatchdog       Pointer to WatchDog feeding callBack function
*
*   @return None
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
void AaErrorRegisterWatchdogCallBack(TAaErrorWdCallback * feedWatchdog);

/**
*******************************************************************************
*
*   @brief  Registers Reset Callback function for AaError.
*
*   @param[in] resetPtr       Pointer to Reset Callback function
*
*   @return None
*
*   @par Description:
*   Used for pool exhaust analyzator.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
void AaErrorRegisterResetCallBack(TAaErrorResetCallback * resetPtr);

/**
*******************************************************************************
*
*   @brief  Calls registered Reset callback function
*
*
*   @return GLO_FALSE
*   @return GLO_TRUE
*
*   @par Description:
*         Function to call Reset callback function
*
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
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
TBoolean AaErrorResetCallBack(void);

/**
*******************************************************************************
*
*   @brief  Starts thread, that handles a possible timeout if Signalhandler
*           gets stuck.
*
*   @param None
*
*   @return EAaErrorRet_Ok
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
EAaErrorRet
AaErrorInitSignalHandling(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /*  _IFAAERROR_H */
