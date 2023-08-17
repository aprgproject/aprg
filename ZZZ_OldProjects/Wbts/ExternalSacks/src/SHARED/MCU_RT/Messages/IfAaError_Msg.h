/** @file
*   @brief Generic error reporting and handling service interface
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Copyright: 2015 Nokia Solutions and Networks. All rights reserved.$
*/

#ifndef _MCU_RT_IFAAERROR_MSG_H_
#define _MCU_RT_IFAAERROR_MSG_H_

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
 * @defgroup dgAaErrorApiLinux AaError LINUX API
* @ingroup dgAaError
*/
/* @{
*/

#include <CcsCommon.h>
#include "../../../COMMON/Definitions/IfAaSysTime_Defs.h"
#ifdef CCS_NEW_IF_STRUCTURE
#include "../Definitions/IfAaError_Defs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
*******************************************************************************
* @brief AaError core dump started indication message
*
* @par Description
* This message is used to inform that the core dumping has started.
*
* @par Message Id
* AAERROR_CORE_DUMP_STARTED_IND_MSG
*
* @par Restrictions:
* Message has to be byte-mode oriented. Endianness has to be specified by Apf flag.
*
*******************************************************************************/
#define AAERROR_CORE_DUMP_STARTED_IND_MSG 0x1197 /**< !- SIGNO(struct SAaErrorCoreDumpMsg) -!  */

/**
*******************************************************************************
* @brief AaError core dump completed indication message
*
* @par Description
* This message is used to inform that core dumping has finished.
*
* @par Message Id
* AAERROR_CORE_DUMP_COMPLETED_IND_MSG
*
* @par Restrictions:
* Message has to be mode-mode oriented. Endianness has to be specified by Apf flag.
*
*******************************************************************************/
#define AAERROR_CORE_DUMP_COMPLETED_IND_MSG 0x1198 /**< !- SIGNO(struct SAaErrorCoreDumpMsg) -!  */

/**
*******************************************************************************
* @brief AaError diagnostic files detected indication message
*
* @par Description
* This message is used to inform that diagnostic files (K2 memdumps or
* Linux crashdumps) have been found.
*
* @par Message Id
* AAERROR_DIAGN_LOG_DETECTED_IND_MSG
*
* @par Restrictions:
* Message has to be byte-mode oriented. Endianness has to be specified by Apf flag.
*
*******************************************************************************/
#define AAERROR_DIAGN_LOG_DETECTED_IND_MSG 0x1255 /**< !- SIGNO(struct SAaErrorCoreDumpMsg) -!  */

/**
*******************************************************************************
* @brief AaError diagnostic files cleared indication message
*
* @par Description
* This message is used to inform that diagnostic files (K2 memdumps or
* Linux crashdumps) have been cleared.
*
* @par Message Id
* AAERROR_DIAGN_LOG_CLEARED_IND_MSG
*
* @par Restrictions:
* Message has to be byte-mode oriented. Endianness has to be specified by Apf flag.
*
*******************************************************************************/
#define AAERROR_DIAGN_LOG_CLEARED_IND_MSG 0x1256 /**< !- SIGNO(struct SAaErrorCoreDumpMsg) -!  */


/**
*******************************************************************************
* @brief AaError core dump indication message struct
* This message is used for storing information about crash.
* It is byte-mode oriented.
*
*******************************************************************************/
typedef struct SAaErrorCoreDumpMsg
{
  u32           nodeID;                                   /**< NodeID where the crash took place */
  char          name[AAERROR_MAX_APPLICATION_NAME];       /**< Name of the crashed application */
  u32           pId;                                      /**< Possix PID of the crashed application */
  u32           signal;                                   /**< Signal number which crashed the application */
  TAaSysTime    time;                                     /**< Time, in seconds since Epoch, when signal was handled */
  char          path[AAERROR_MAX_CORE_PATH_LENGTH];       /**< Absolute path to the diagnostic files container */
  u32           coreDumpEnabled;                          /**< True if a core file will be generated,
                                                               false if only bt-coreinfo.txt is generated/appended */
} SAaErrorCoreDumpMsg;

typedef SAaErrorCoreDumpMsg SAaErrorDiagnMsg;

#ifdef __cplusplus
}
#endif

/*@}*/
#endif /* _MCU_RT_IFAAERROR_MSG_H_ */
