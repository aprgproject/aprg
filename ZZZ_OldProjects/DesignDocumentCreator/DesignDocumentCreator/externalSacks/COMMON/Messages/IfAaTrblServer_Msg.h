/**
*******************************************************************************
* @brief                 AaTrblServer common messages.
* @module                AaTrblServer
*
* Copyright 2017, 2019 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AATRBLSERVER_MSG_H_
#define _COMMON_IF_AATRBLSERVER_MSG_H_

#include <CcsCommon.h>
#include <IfAaTrbl_Defs.h>
#include <TAaSysComSicad.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
************************************************************************************************
* @defgroup dgAaTrblServerApiLinux AaTrblServer
* @ingroup  dgAaTrblServer
*/
/*@{*/
/**
* @brief AaTrblServer discover message
*
* @par Description
* AaTrblServer uses this message to publish information to AaTrblServer Master about new AaTrblServer in system.
*
* @par Message Id
* AATRBL_SERVER_DISCOVER_REQ_MSG
*
* @par Restrictions:
* This message is supported only on LINUX_PC, LINUX_PC64, LINUX_FSM3, LINUX_FSM4, LINUX_OCTEON2_LRC LINUX_ARM53_LE, LINUX_ARM57_LE and CCS_RT_LINUX targets.
* Rest platforms are not supported. DSP not handle this message.
***********************************************************************************************/
#define AATRBL_SERVER_DISCOVER_REQ_MSG      0x1171   /* !- SIGNO(struct SAaTrblServerDiscoverReq) -!  */

/**
************************************************************************************************
* @brief AaTrblServer discover message structure
* @param serverSicad   Sic address of registered server.
*
* @par Description
* AaTrblServer uses this message to get registered to AaTrblServer Master (discovery).
*
* @par Message Id
* AATRBL_SERVER_DISCOVER_REQ_MSG
***********************************************************************************************/
typedef struct SAaTrblServerDiscoverReq
{
  TAaSysComSicad  serverSicad;
} SAaTrblServerDiscoverReq;

/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _COMMON_IF_AATRBLSERVER_MSG_H_*/

