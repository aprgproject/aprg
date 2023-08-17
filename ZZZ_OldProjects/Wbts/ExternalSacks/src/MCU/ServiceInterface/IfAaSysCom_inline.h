/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/ 
#ifndef IF_MCU_AASYSCOM_INLINEH
#define IF_MCU_AASYSCOM_INLINEH
#include <CcsCommon.h>


/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 * @addtogroup dgAaSysComMcuInline AaSysCom MCU INLINE
 * @ingroup dgAaSysCom

 * @{
 *
 * Common Computer and Support SW System Communication Inline Implementation.
 *
 * This service provides inline implementation of certain SysCom services.
 *
 * Users should not include this header directly. Instead include the normal
 * SysCom interface header file and indicate intention to use the inline
 * implementations with a:
 *
 * -DAASYSCOM_USE_INLINE_IMPL
 */

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>
#include <IfAaSysCom.h>
#include <IfAaSysCom_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PRIVATE DECLARATIONS -------------------------------*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/



/*----------------------- PUBLIC INTERFACES ----------------------------------*/

/**
 * @name definitions for inline implementation functions
 * @{
 */
#define AaSysComMsgGetPayload AaSysComMsgGetPayload_inlineImpl
#define AaSysComMsgSetSender AaSysComMsgSetSender_inlineImpl
#define AaSysComMsgGetId AaSysComMsgGetId_inlineImpl

#define AaSysComMsgGetPayloadSize AaSysComMsgGetPayloadSize_inlineImpl
#define AaSysComMsgGetReceiver AaSysComMsgGetReceiver_inlineImpl
#define AaSysComMsgGetSender AaSysComMsgGetSender_inlineImpl
#define AaSysComMsgSetId AaSysComMsgSetId_inlineImpl
#define AaSysComMsgSetReceiver AaSysComMsgSetReceiver_inlineImpl
#define AaSysComSicadGetNid AaSysComSicadGetNid_inlineImpl
#define AaSysComSicadGetCpid AaSysComSicadGetCpid_inlineImpl
#define AaSysComSicadGet AaSysComSicadGet_inlineImpl

/** @} */

/**
********************************************************************************
*
* @brief      Get the application part of a message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void *AaSysComMsgGetPayload_inlineImpl(
    const void *message)
{
  SMsgData const * const msg = (SMsgData*)message;
  return (void*)&(msg->userData);
}


/**
********************************************************************************
*
* @brief        Set the sender of a message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComMsgSetSender_inlineImpl(
    const void *message,
    const TAaSysComSicad messageSource)
{
  SMsgData * const msg = (SMsgData*)(message);
  msg->header.sender = messageSource;
}


/**
********************************************************************************
*
* @brief      Get the message identifier of a message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ TAaSysComMsgId AaSysComMsgGetId_inlineImpl(
    const void *message)
{
  SMsgData const * const msg = (SMsgData*)(message);
  return (TAaSysComMsgId)msg->header.msgId;

}

/**
********************************************************************************
*
* @brief      Get the length of the application part of a message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ TAaSysComMsgSize AaSysComMsgGetPayloadSize_inlineImpl(
    const void *message)
{
  SMsgData const * const msg = (SMsgData*)(message);
  TAaSysComMsgSize retVal;

  if (EAaSysComMsgMef_Sicv1WithTrailer == AaSysComMsgGetMef(message))
  {
      retVal = (TAaSysComMsgSize)(msg->header.msgSize - \
      sizeof(SInternalMsgHeader) - sizeof(SInternalMsgTrailer));
  }
  else
  {
      retVal = (TAaSysComMsgSize)(msg->header.msgSize - \
      sizeof(SInternalMsgHeader));
  }
  return retVal;
}


/**
********************************************************************************
*
* @brief      Get the receiver of a message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ TAaSysComSicad AaSysComMsgGetReceiver_inlineImpl(
    const void *message)
{
  SMsgData const * const msg = (SMsgData*)(message);
  return msg->header.target;

}


/**
********************************************************************************
*
* @brief      Get the sender of a message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ TAaSysComSicad AaSysComMsgGetSender_inlineImpl(
    const void *message)
{
  SMsgData const * const msg = (SMsgData*)(message);
  return msg->header.sender;
}


/**
********************************************************************************
*
* @brief      Set the message identifier (SIC message type number) of a
*             message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComMsgSetId_inlineImpl(
    const void *message,
    const TAaSysComMsgId messageId)
{
  SMsgData * const msg = (SMsgData*)(message);
  msg->header.msgId = messageId;
}


/**
********************************************************************************
*
* @brief      Set the receiver of a message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComMsgSetReceiver_inlineImpl(
    void **message,
    const TAaSysComSicad receiver)
{
  SMsgData * const msg = (SMsgData*)(*message);
  msg->header.target = receiver;
}


/**
********************************************************************************
*
* @brief      Get node ID.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ TAaSysComNid AaSysComSicadGetNid_inlineImpl(
    const TAaSysComSicad sicAddress)
{
  SSicAddress const * const addr = (SSicAddress *)&sicAddress;
  return addr->nId;
}


/**
********************************************************************************
*
* @brief      Get communication point ID.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ TAaSysComCpid AaSysComSicadGetCpid_inlineImpl(
    const TAaSysComSicad sicAddress)
{
  SSicAddress const * const addr = (SSicAddress *)&sicAddress;
  return addr->cpId;
}


/**
********************************************************************************
*
* @brief      Get the SIC address based on cp id and node id.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ TAaSysComSicad AaSysComSicadGet_inlineImpl(
    const TAaSysComCpid userCpid,
    const TAaSysComNid userNid)
{
  TAaSysComSicad sicAddress = 0;
  SSicAddress * const addr = (SSicAddress *)(void*)&sicAddress;
  addr->cpId = userCpid;
  addr->nId  = userNid;
  return sicAddress;
}

/** @} end: @addtogroup dgAaSysComMcuInline AaSysCom MCU INLINE */

#ifdef __cplusplus
}
#endif


#endif /* IF_MCU_AASYSCOM_INLINE_H */
