/** @file
*   @brief This file contains AaTrace interface
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2018 Nokia. All rights reserved.$
*/
#ifndef _IFAATRACE_H
#define _IFAATRACE_H

#include <IfAaTrace_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup dgAaTrace General API Information
 *  @ingroup dgBasicComputingSw
 *
 *  AaTrace service is available if the message handling operations
 *  are done using AaSysCom functions AaSysComMsgReceive(),
 *  AaSysComMsgSend and their modifications.
 *
 *  User should have in mind, that tracing during interrupt service
 *  routine on DSP is not possible! This is because of time limitations
 *  during ISRs and is implemented by using the following code:
 *  @code
 *       if (RTOS_INT_PROC == RTOS_getProcessType(RTOS_currentProcess()))
 *       {
 *           return; // do not trace the message
 *       }
 *  @endcode
 */


/** @defgroup dgAaTraceServiceInterface AaTrace Service Interface
 *  @ingroup dgAaTrace
 *  This chapter describe functions used in AaTrace API.
 */
///@{

/**
********************************************************************************
*
* @brief        Initializes AaTrace.
*
* @return       EAaTraceRet_Ok or EAaTraceRet_Nok.
*
* @par Description:
* The AaTraceInit() creates and starts AaTrace processes.
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
* @see
* None.
*
* @par Example:
*   @code
*       if(AaTraceInit() != EAaTraceRet_Ok)
*       {
*           //start up error
*       }
*   @endcode
*
*******************************************************************************/
EAaTraceRetVal AaTraceInit(void);

///@}

#ifdef __cplusplus
}
#endif

#endif /* _IFAATRACE_H */
