/**
*******************************************************************************
* @file
*
* @brief                 AaSysCom inline functions implementation.
*
* Copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_IFAASYSCOM_INLINE_H
#define _RT_DSP_IFAASYSCOM_INLINE_H


/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaSysCom AaSysCom API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaSysCom AaSysCom API for RT and OSECK DSP nodes
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaSysComInlineApi AaSysCom Inline API
* @{
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

#include "CcsCommon.h"
#include <glo_def.h>
#include <string.h>
#include <IfAaCpu.h>
#include <IfAaError.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PRIVATE DECLARATIONS -------------------------------*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

#if defined(CCS_OSECK)
extern TAaSysComNid g_sysComCurrentNid;
#endif /*defined(CCS_OSECK)*/

#define AASYSCOM_SFMON_CLEAR        0xEFFF

/** @} end: @name Structure definitions */

/*----------------------- PUBLIC INTERFACES ----------------------------------*/

/**
* @name Definitions for inline implementation functions
* @{
*/
#define AaSysComMsgGetPayload AaSysComMsgGetPayload_inlineImpl
#define AaSysComMsgSetSender AaSysComMsgSetSender_inlineImpl
#define AaSysComMsgGetId AaSysComMsgGetId_inlineImpl

#define AaSysComMsgGetMef AaSysComMsgGetMef_inlineImpl

#define AaSysComMsgGetPayloadSize AaSysComMsgGetPayloadSize_inlineImpl
#define AaSysComMsgGetReceiver AaSysComMsgGetReceiver_inlineImpl
#define AaSysComMsgGetSender AaSysComMsgGetSender_inlineImpl
#define AaSysComMsgSetId AaSysComMsgSetId_inlineImpl
#define AaSysComMsgSetReceiver AaSysComMsgSetReceiver_inlineImpl
#define AaSysComSicadGetNid AaSysComSicadGetNid_inlineImpl
#define AaSysComSicadGetCpid AaSysComSicadGetCpid_inlineImpl
#define AaSysComSicadGet AaSysComSicadGet_inlineImpl

#define AaSysComMsgGetApf AaSysComMsgGetApf_inlineImpl
#define AaSysComMsgGetMtm AaSysComMsgGetMtm_inlineImpl
#define AaSysComMsgGetTrailer AaSysComMsgGetTrailer_inlineImpl
#define AaSysComSicMsgGetLength AaSysComSicMsgGetLength_inlineImp
#define AaSysComIsHostAndMsgEndianSame AaSysComIsHostAndMsgEndianSame_inlineImp
#define AaSysComMsgSetApf2B AaSysComMsgSetApf2B_inlineImp
#define AaSysComMsgSetApf AaSysComMsgSetApf_inlineImp
#define AaSysComMsgSetMtm AaSysComMsgSetMtm_inlineImp
#if defined(CCS_OSECK)
#define AaSysComGetOwnNid AaSysComGetOwnNid_inlineImp
#endif /*defined(CCS_OSECK)*/
#define AaSysComEnd16Swap AaSysComEnd16Swap_inlineImp
#define AaSysComEnd32Swap AaSysComEnd32Swap_inlineImp
#define AaSysComEnd64Swap AaSysComEnd64Swap_inlineImp
#define AaSysComMsgEcho AaSysComMsgEcho_inlineImp
#define AaSysComMsgForward AaSysComMsgForward_inlineImp
#define AaSysComMsgRelay AaSysComMsgRelay_inlineImp
#define AaSysComMsgSend AaSysComMsgSend_inlineImp
#define AaSysComMsgSendS AaSysComMsgSendS_inlineImp
#define AaSysComMsgGetBulkMsg AaSysComMsgGetBulkMsg_inlineImp
#define AaSysComMsgGetBulkMsgLength AaSysComMsgGetBulkMsgLength_inlineImp
#define AaSysComMsgReveal AaSysComMsgReveal_inlineImp
#define AaSysComMsgCreateCopy AaSysComMsgCreateCopy_inlineImpl
#define AaSysComMsgCreateCopyTo AaSysComMsgCreateCopyTo_inlineImpl
#define AaSysComMsgCreateCopyRe AaSysComMsgCreateCopyRe_inlineImpl
#define AaSysComMsgCreateReply AaSysComMsgCreateReply_inlineImpl
/** @} */

/**
********************************************************************************
*
*   @brief    Get the handle of message.
*             NOTE the function is not supported by the MCU implementation with
*             the exception of the RT-CC&S version.
*             Null pointer handling MUST be provided by user!
*
*******************************************************************************/
static __CCS_INLINE__ void *AaSysComMsgReveal_inlineImp(const void *messagePayload)
{
    u8 *ptr = (u8 *) messagePayload;
    return (void *) (ptr - sizeof(SInternalMsgHeader));
}


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
* @brief      Reveal the Message Envelope Format (MEF) of the (received)
*             message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ EAaSysComMsgMef AaSysComMsgGetMef_inlineImpl(
    const void *message)
{
  SMsgData const * const msg = (SMsgData*)message;
  /* HF2.MEF */
  return ((EAaSysComMsgMef)(msg->header.flags & AASYSCOM_MEF_READ_MASK));
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
  return (TAaSysComNid)((0xFFFF0000 & sicAddress) >> 16);
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
  return (TAaSysComNid)((0xFFFF & sicAddress));
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
  return (TAaSysComSicad)((userNid << 16) | userCpid);
}

/**
********************************************************************************
*
* @brief      Reveal the application payload format of the (received) message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ EAaSysComMsgApf AaSysComMsgGetApf_inlineImpl(
    const void *message)
{
  SMsgData const * const msg = (SMsgData*)message;
  /* HF2.MAPF */
  return (EAaSysComMsgApf) ((msg->header.flags & AASYSCOM_APF_READ_MASK) >> 2);
}

/**
********************************************************************************
*
* @brief      Get the message transfer mode of a message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ EAaSysComMtm AaSysComMsgGetMtm_inlineImpl(
    const void *message)
{
    SMsgData const * const msg = (SMsgData*)message;
    SSicHeaderFlags *flags = (SSicHeaderFlags *)&msg->header.flags;
    return ((flags->user & UF_BEST_EFFORT_TRANSPORT) != 0 ? \
        EAaSysComMtm_Basic : EAaSysComMtm_Reliable);
}

/**
********************************************************************************
*
* @brief      Get the trailer of the message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void* AaSysComMsgGetTrailer_inlineImpl(
    const void *message)
{
  SMsgData const * const msg = (SMsgData*)message;
  return ((void *)((u8*)msg + msg->header.msgSize
    - sizeof(SInternalMsgTrailer)));
}

/**
********************************************************************************
*
* @brief      Get the length of the SIC message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ u32 AaSysComSicMsgGetLength_inlineImp(
    const void *message)
{
  SMsgData *msg = (SMsgData*)message;
  return (u32)msg->header.msgSize;
}

/**
********************************************************************************
*
* @brief      Checks if endianness of host cpu and message payload is same.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ TBoolean AaSysComIsHostAndMsgEndianSame_inlineImp(
    const void *message)
{
  EAaSysComMsgApf apf;
  apf = AaSysComMsgGetApf(message);
  if ((EAaSysComMsgApf_32Little == apf) || (EAaSysComMsgApf_8Little  == apf))
  {
    return GLO_TRUE;
  }
  return GLO_FALSE;
}

/**
********************************************************************************
*
* @brief      Set Message Application Part Format (MAPF) to Byte (flags in
*             header set).
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComMsgSetApf2B_inlineImp(const void *message)
{
  SMsgData * const msg = (SMsgData*)message;
  msg->header.flags = (u16)((msg->header.flags & AASYSCOM_CLEAR_APF) | \
                        AASYSCOM_SET_APF_LITTLE8);
}

/**
********************************************************************************
*
* @brief      Set Message Application Part Format (MAPF) - flags in header set.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComMsgSetApf_inlineImp(const void *message,
    EAaSysComMsgApf apf)
{
  SMsgData * const msg = (SMsgData*)message;
  /* set HF2.MAPF */
  msg->header.flags = (u16)((msg->header.flags & AASYSCOM_CLEAR_APF) | \
                        AASYSCOM_SET_APF(apf));
}

/**
********************************************************************************
*
*  @brief     Set the message transfer mode of a message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComMsgSetMtm_inlineImp(const void *message,
    const EAaSysComMtm requestedTransferMode)
{
  SMsgData * const msg = (SMsgData*)message;
  SSicHeaderFlags *flags = (SSicHeaderFlags *)&msg->header.flags;
  if(requestedTransferMode == EAaSysComMtm_Reliable)
  {
    flags->user &= (u8)~UF_BEST_EFFORT_TRANSPORT;
  }
  else if(requestedTransferMode == EAaSysComMtm_Basic)
  {
    flags->user |= (u8)UF_BEST_EFFORT_TRANSPORT;
  }
}

#if defined(CCS_OSECK)
/**
********************************************************************************
*
*  @brief     Get own node id of the requesting user.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ TAaSysComNid AaSysComGetOwnNid_inlineImp(void)
{
  return g_sysComCurrentNid;
}
#endif /*defined(CCS_OSECK)*/

/**
********************************************************************************
*
*  @brief     Reverses the order of bytes of each 16-bit long field.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComEnd16Swap_inlineImp(const void *firstField,
    const u32 numberOfFields)
{
  AaCpuBitSwapMultiByteOrder16((u16*) firstField, (size_t) numberOfFields);
}

/**
********************************************************************************
*
*  @brief     Reverses the order of bytes of each 32-bit long field.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComEnd32Swap_inlineImp(const void *firstField,
    const u32 numberOfFields)
{
  AaCpuBitSwapMultiByteOrder32((u32*) firstField, (size_t) numberOfFields);
}

/**
********************************************************************************
*
*  @brief     Reverses the order of bytes of each 64-bit long field.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComEnd64Swap_inlineImp(const void *firstField,
    const u32 numberOfFields)
{
  AaCpuBitSwapMultiByteOrder64((u64*) firstField, (size_t) numberOfFields);
}

/**
********************************************************************************
*
*  @brief     Echo a message.
*
*             This function implements the AASYSCOM_ECHO_CPID service for other
*             message IDs.
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComMsgEcho_inlineImp(void **message)
{
  SMsgData * const msg = (SMsgData*)(*message);
  TAaSysComSicad const target = msg->header.target;

  msg->header.target = msg->header.sender;
  msg->header.sender = target;

  AaSysComMsgSendWithPriority(message,EAaSysComSendPriority_Unspecified);
}

/**
********************************************************************************
*
*  @brief     Forward a message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComMsgForward_inlineImp(void **message,
    const TAaSysComSicad messageTarget)
{
  SMsgData * const msg = (SMsgData*)(*message);
  /* change the sender to be the receiver of the orig msg */
  msg->header.sender = AaSysComMsgGetReceiver(*message);

  msg->header.target = messageTarget;

  AaSysComMsgSendWithPriority(message,EAaSysComSendPriority_Unspecified);
}

/**
********************************************************************************
*
*  @brief     Relay a message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComMsgRelay_inlineImp(void **message,
    const TAaSysComSicad messageTarget)
{
  SMsgData * const msg = (SMsgData*)(*message);
  msg->header.target = messageTarget;

  AaSysComMsgSendWithPriority(message,EAaSysComSendPriority_Unspecified);
}

/**
********************************************************************************
*
*  @brief     Function is used to send the message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComMsgSend_inlineImp(void **message)
{
  AaSysComMsgSendWithPriority(message, EAaSysComSendPriority_Unspecified);
}

/**
********************************************************************************
*
*  @brief     Function is used to send the message with setting sender
*             parameter.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void AaSysComMsgSendS_inlineImp(void **message,
    const TAaSysComSicad messageSender)
{
  SMsgData *msgPtr = (SMsgData*)(*message);
  msgPtr->header.sender = messageSender;
  AaSysComMsgSendWithPriority(message, EAaSysComSendPriority_Unspecified);
}


/**
********************************************************************************
*
*   @brief  Returns pointer to header of sysCom message.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void *AaSysComMsgGetBulkMsg_inlineImp(const void *sicMessage)
{
    return (void*)sicMessage;
}


/**
********************************************************************************
*
* @brief        Get the length of of a message (including the length of msg
*               header).
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ TAaSysComMsgSize AaSysComMsgGetBulkMsgLength_inlineImp(const void *sicMessage)
{
    SMsgData const * const msg = (SMsgData*)(sicMessage);
    return msg->header.msgSize;
}

#if defined(CCS_OSECK)
/** @brief Public version of SysComSelectPool
*
*  Needed in some inlined code.
**/
extern i32 SysComSelectPool_Public(const TAaSysComSicad messageTarget);
#endif
extern TBoolean AaMemCheckTag(void const *ptr);

/**
********************************************************************************
*
*  @brief    Reserve and prepare resources for a message pre-filled with a
*            copy of a user-specified message.
*
*  @param    originalMessage: Input; Pointer to the original message.
*
*  @return   Pointer to the create message is returned if operation was
*            successful. Otherwise, NULL is returned.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void *AaSysComMsgCreateCopy_inlineImpl(const void *originalMessage)
{
    SMsgData const * const orig = (SMsgData*)(originalMessage);
    SMsgData *msgPtr = GLO_NULL;
    i32 messagePoolId;

    if(originalMessage!=GLO_NULL)
    {
      if(GLO_TRUE != AaMemCheckTag(originalMessage))
      {
        AaErrorExceptionRaise(EAaErrorFatality_Fatal, EAaErrorCcs_AaSysCom_MemAllocFailure, GLO_NULL, 0,
                "AaMemCheckTag detected non-AaMem buffer", __FILE__, __LINE__);
      }
#if defined(CCS_OSECK)
      messagePoolId = SysComSelectPool_Public(orig->header.target);
#else /* CCS-RT */
      messagePoolId = AaSysComMsgGetPoolId(originalMessage);
#endif
      /* Allocate memory for the message and fill in message header. */
      msgPtr = (SMsgData*)AaSysComMsgCreateP(orig->header.msgId,
                                  (TAaSysComMsgSize)(orig->header.msgSize - \
                                  sizeof(SInternalMsgHeader)),
                                  (TAaSysComSicad) orig->header.target, messagePoolId);
      if(msgPtr!=GLO_NULL)
      {
        /*Copy header and userdata from orig to msgPtr*/
        /*Possible trailer is copied with user data*/
        (void)memcpy(&(msgPtr->header),
                     &(orig->header),
                      orig->header.msgSize);
        // For new message copy SF_MONITORED flag should not be set.
        msgPtr->header.flags &= AASYSCOM_SFMON_CLEAR;
        return msgPtr;
      }
    }
    return GLO_NULL;
}


/**
********************************************************************************
*
*  @brief    Reserve and prepare resources for a message pre-filled with a
*            copy of a user-specified message.
*
*  @param    originalMessage: Input; Pointer to the original message.
*  @param    messageTarget: Input; SICAD of the receiver.
*
*  @return   Pointer to the create message is returned if operation was
*            successful. Otherwise, NULL is returned.
*
* @see
* respective function documentation in IfAaSysCom.h
*
*******************************************************************************/
static __CCS_INLINE__ void *AaSysComMsgCreateCopyTo_inlineImpl(const void *originalMessage,
                              const TAaSysComSicad messageTarget)
{
    SMsgData const * const orig = (SMsgData*)(originalMessage);
    SMsgData *msgPtr = GLO_NULL;
    i32 messagePoolId;

    if(originalMessage != GLO_NULL)
    {
        if(GLO_TRUE != AaMemCheckTag(originalMessage))
        {
            AaErrorExceptionRaise(EAaErrorFatality_Fatal, EAaErrorCcs_AaSysCom_MemAllocFailure, GLO_NULL, 0,
                    "AaMemCheckTag detected non-AaMem buffer", __FILE__, __LINE__);
        }
#if defined(CCS_OSECK)
        messagePoolId = SysComSelectPool_Public(messageTarget);
#else /* CCS-RT */
        messagePoolId = AaSysComMsgGetPoolId(originalMessage);
#endif
        /* Allocate memory for the message and fill in message header. */
        msgPtr = (SMsgData*)AaSysComMsgCreateP(orig->header.msgId,
                (TAaSysComMsgSize)(orig->header.msgSize - \
                        sizeof(SInternalMsgHeader)),
                        (TAaSysComSicad) orig->header.target, messagePoolId);
        if(msgPtr!=GLO_NULL)
        {
            /*Copy the message*/
            (void)memcpy(msgPtr, orig, orig->header.msgSize);
            msgPtr->header.target = messageTarget;
            // For new message copy SF_MONITORED flag should not be set.
            msgPtr->header.flags &= AASYSCOM_SFMON_CLEAR;
        }
        return msgPtr;
    }
    return GLO_NULL;
}


/**
*******************************************************************************
*
*  @brief    Reserve and prepare resources for a message pre-filled with a
*            copy of a user-specified message.
*
*  @param    originalMessage: Input; Pointer to the original message.
*  @param    repliedMessage: Input; Pointer to the replied message.
*
*  @return   Pointer to the create message is returned if operation was
*            successful. Otherwise, NULL is returned.
*
******************************************************************************/
static __CCS_INLINE__ void *AaSysComMsgCreateCopyRe_inlineImpl(const void *originalMessage,
                              const void *repliedMessage)
{
    SMsgData const * const orig = (SMsgData*)(originalMessage);
    SMsgData *msgPtr = GLO_NULL;
    i32 messagePoolId;

    if(originalMessage != GLO_NULL && repliedMessage != GLO_NULL)
    {
        if(GLO_TRUE != AaMemCheckTag(originalMessage))
        {
            AaErrorExceptionRaise(EAaErrorFatality_Fatal, EAaErrorCcs_AaSysCom_MemAllocFailure, GLO_NULL, 0,
                    "AaMemCheckTag detected non-AaMem buffer", __FILE__, __LINE__);
        }
#if defined(CCS_OSECK)
        /*Memory allocation*/
        messagePoolId = SysComSelectPool_Public(((SMsgData*)repliedMessage)->header.sender);
#else /* CCS-RT */
        messagePoolId = AaSysComMsgGetPoolId(originalMessage);
#endif
        /* Allocate memory for the message and fill in message header. */
        msgPtr = (SMsgData*)AaSysComMsgCreateP(orig->header.msgId,
                (TAaSysComMsgSize)(orig->header.msgSize - \
                        sizeof(SInternalMsgHeader)),
                        (TAaSysComSicad) orig->header.target, messagePoolId);
        if(msgPtr != GLO_NULL)
        {
            /*Copy the message*/
            (void)memcpy(msgPtr, orig, orig->header.msgSize);
            msgPtr->header.target = ((SMsgData*)repliedMessage)->header.sender;
            // For new message copy SF_MONITORED flag should not be set.
            msgPtr->header.flags &= AASYSCOM_SFMON_CLEAR;
        }
        return msgPtr;
    }
    return GLO_NULL;
}


/**
********************************************************************************
*
*  @brief    Function is used to reserve and prepare resources for a reply
*            message.
*
*  @param    messageId: Input; Id of the message.
*  @param    messagePayloadSize: Input; Size of the application part of the
*            message.
*  @param    repliedMessage: Input; Message that reply should be for.
*
*  @return   Pointer to the created message is returned. NULL is returned, if
*            memory allocation failed.
*
*    Pseudocode
*    (0100)  Allocate memory for the message and fill in message header.
*    (0200)  Fill in message header sender as same as header target.
*
*******************************************************************************/
static __CCS_INLINE__ void *AaSysComMsgCreateReply_inlineImpl(const TAaSysComMsgId messageId,
    const TAaSysComMsgSize messagePayloadSize,
    const void *repliedMessage)
{
    SMsgData *msgPtr = GLO_NULL;
    i32 messagePoolId;

    SMsgData const * const replied = (SMsgData*)repliedMessage;

    if(repliedMessage!=GLO_NULL)
    {
#if defined(CCS_OSECK)
      messagePoolId = SysComSelectPool_Public(replied->header.sender);
#else /* CCS-RT */
      messagePoolId = AaSysComMsgGetPoolId(repliedMessage);
#endif
     /*0100*/
     /* Allocate memory for the message and fill in message header. */
     msgPtr = (SMsgData*)AaSysComMsgCreateP(messageId, messagePayloadSize,
                     (TAaSysComSicad) replied->header.sender, messagePoolId);
     if(msgPtr!=GLO_NULL)
     {
       /*0200*/
       /* Fill in message header sender as same as header target. */
       msgPtr->header.sender   = replied->header.target;
     }
     return (void*)msgPtr;
   }
   return GLO_NULL;
}


/** @} */    /* dgUpCcsRtDspAaSysComInlineApi */

#ifdef __cplusplus
}
#endif

/** @} */   /* dgUpCcsRtDspAaSysCom */
/** @} */   /* dgUpCcsAaSysCom */
/** @} */   /* dgUpCcs */

#endif /* _RT_DSP_IFAASYSCOM_INLINE_H */
