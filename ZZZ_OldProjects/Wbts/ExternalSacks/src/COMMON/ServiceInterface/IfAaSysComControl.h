/* ****************************************************************************
 * @brief  AaSysComControl implementation header file.
 * @module AaSysCom
 * @owner  Vedran Cundekovic
 *
 * Copyright 2014 Nokia Solutions and Networks. All rights reserved.
 * ****************************************************************************/

#ifndef IF_COMMON_AASYSCOM_CONTROL_H
#define IF_COMMON_AASYSCOM_CONTROL_H
#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <IfAaSysComControl_Msgs.h>
#endif

#if !defined (CCS_LITTLE_ENDIAN) && !defined (CCS_BIG_ENDIAN)
#error "No endianness defined"
#endif

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
 *@addtogroup dgAaSysComCommon AaSysCom Common
 *@ingroup dgAaSysCom
 *
 * Common Computer and Support SW System Communication Control Service.
 *
 * This service provides following functionality
 * - Echo     Handles EchoRouteReq message (i.e. updates and passes further
 *            according to message contents) and echoes all other messages back
 *            to sender.
 * - Drain    Deletes all received messages (in some earlier discussion referred
 *            as 'Null_CP').
 * - Control  TBD - So far mainly for future needs.
 *            Provides amount and CPIDs of all registered users in the node.
 *
 * @{
 */

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>

#include <EStatus.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PRIVATE DECLARATIONS -------------------------------*/

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/**
 * @name Function API in AaSysComControl.
 * @{
 */

/**
********************************************************************************
*
* @brief        Init function - creates the AaSysComControl EU.
*
* @return       The function returns nothing.
*
* @par Description:
* The AaSysComControlInit() function creates and starts the AaSysComControl
* Execution Unit.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* This function is ment to be used internally by CC&S.
*
* @par Usage:
* This function should be called during SysCom startup.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComControl
*
* @par Example:
*   @code
*       // perform needed startup routines
*       AaSysComControlInit()
*       ...
*       // perform other needed startup routines
*   @endcode
*
*******************************************************************************/
void AaSysComControlInit(void);


/**
********************************************************************************
*
* @brief        Function to handle echo route request message.
*
* @param[in,out]  message   Address of pointer to the handle of message
*                           containing the request to be updated.
*
* @return       The function returns
*               GLO_TRUE if the received message has been forwarded to next
*                   receiver by this function.
*               GLO_FALSE if the message has not been forwarded (i.e. this
*                   receiver is the last in the list) and the message must be
*                   given to application even if it is not directed to
*                   AASYSCOM_ECHO_CPID.
*
* @par Description:
* The AaSysComControlHandleEchoRouteReq() function handles the received
* EchoRouteReq message i.e. updates contents of the message and passes it
* to next receiver if needed.
*
* EXCEPTION:
* If Sic v1 trailer is used, Time To Live (TTL) in header flags is updated for
* this message in every CP where it is handled. Reason for this is to ensure that
* the message ment to visit numerous nodes is not deleted by SysCom as a hobo.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* This function should be called during SysCom stratup.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComControl
*
* @par Example:
*   @code
*     SMsgData const * msg = GLO_NULL;
*     TBoolean continueWaiting = GLO_FALSE;
*     ...
*     if ((AASYSCOM_ECHO_ROUTE_REQ_MSG == AaSysComMsgGetId((const void *)msg)) &&
*         (AASYSCOM_ECHO_CPID != AaSysComSicadGetCpid(AaSysComMsgGetReceiver((const void *)msg))))
*     {
*       continueWaiting = AaSysComControlHandleEchoRouteReq((void**)&msg);
*     }
*     ...
*   @endcode
*
*******************************************************************************/
TBoolean AaSysComControlHandleEchoRouteReq(void **message);


/**
 * @deprecated
 * This function was accidentally included in this interface header.
 * It must not be used  - ment to be used internally by AaSysComControl
 */
void AaSysComControlUpdateRouteReq(void *message);


/**
********************************************************************************
*
* @brief      Print contents of Route Request message.
*
* @param[in]  message   Points to the handle of the message.
*
* @return     The function returns nothing.
*
* @par Description:
* The AaSysComControlPrintRouteReq() function prints contents of Route Request
* message (echoData is not printed).
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* This function can be used to trace contents of SAaSysComEchoRouteReq message
* in any phase of the loop of the message. AaSysComControl uses this function
* in case it has been defined to be the last receiver in the list - it does
* not know what else to do.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysComControl
*
* @par Example:
*   @code
*       void *msgPtr = GLO_NULL;
*       SAaSysComEchoRouteReq *routeReq = GLO_NULL;
*       ...
*       msgPtr = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       if (AASYSCOM_ECHO_ROUTE_REQ_MSG == AaSysComMsgGetId((const void *)msgPtr))
*       {
*         AaSysComControlPrintRouteReq((const void *)msgPtr);
*       }
*       ...
*   @endcode
*
*******************************************************************************/
void AaSysComControlPrintRouteReq(const void *message);


/**
*******************************************************************************
*
*   @brief     Calculates the size of echo route msg
*
*   @param[in] receiverCount  number of receivers of the message
*   @param[in] echoDataSize   size of the test data (echoData) filled later to the message
*
*   @return    length of the Echo Route Req message
*
*   @par Description:
*   The AaSysComControlCalculateEchoRouteMsgLen() function calculates the size of
*   echo route msg according to number of receivers and application data size. It
*   - takes size of the basic structure (1)
*   - adds dynamic part containing
*     - addresses and time stamps according to number of receivers (2)
*       Note that first receivers are included in the basic structure
*     - user data in the message and finally (3)
*     - possible padding of the data (4). The basic structure length is divisible by 4.
*       Thus user data defines the need of padding. If length of user data is divisible by 4
*       no padding is needed, otherwise required padding is 4 - (userDataLen mod 4)
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example: The example here presents using of all functions when creating
*                 the Echo Route Req message. A message having two receivers is
*                 created in the example below. Please note that the last receiver
*                 does not necessarily have to be the original sender even it is
*                 in this example.
*
*   @code
*       u32 len;
*       u32 i = 0;
*       u32 expectedEchoDataLen;
*       u8 expectedEchoData[15];
*       void *testMsg = GLO_NULL;
*       SAaSysComEchoRouteReq *testReq = GLO_NULL;
*       TAaSysComSicad sicAddr;
*       TAaSysComSicad mySicad;
*       ...
*       expectedEchoDataLen = strlen("Hello World")+1;
*       memcpy(expectedEchoData, "Hello World", expectedEchoDataLen);
*
*       len = AaSysComControlCalculateEchoRouteMsgLen(2, expectedEchoDataLen);
*       testMsg = AaSysComMsgCreate(AASYSCOM_ECHO_ROUTE_REQ_MSG,
*                                   (TAaSysComMsgSize)len,
*                                   AaSysComNmapGetSicad(WSP_12,
*                                                        CHIP1_CPU1,
*                                                        AASYSCOM_ECHO_CPID));
*       testReq = (SAaSysComEchoRouteReq *)AaSysComMsgGetPayload(testMsg);
*       memset((void *)testReq, 0x00, (size_t)len);
*
*       AaSysComControlSetSequenceNumberToEchoRouteReqMsg(testReq, 0x88);
*
*       // Add the receiver nodes.
*       AaSysComControlSetReceiverCountToEchoRouteReqMsg(testReq, 2);
*
*       sicAddr = AaSysComNmapGetSicad((const TBoard) WSP_12,
*                                      (const TCpu) CHIP1_CPU1,
*                                      (const TTask) AASYSCOM_ECHO_CPID);        // receiver[0]
*
*       AaSysComControlSetReceiverAddressToEchoRouteReqMsg(testReq, i, sicAddr);
*       AaSysComControlSetLinkForReceiverToEchoRouteReqMsg(testReq, i, AASYSCOM_LINK_UDPCP);
*       i++;
*       AaSysComControlSetReceiverAddressToEchoRouteReqMsg(testReq, i, mySicad);  // receiver[1]
*       AaSysComControlSetLinkForReceiverToEchoRouteReqMsg(testReq, i, 0);
*       //i++;
*
*       // set test data length + test data to msg
*       AaSysComControlSetEchoDataToEchoRouteReqMsg(testReq, expectedEchoData, (u16)expectedEchoDataLen);
*       AaSysComMsgSetSender(testMsg, mySicad);
*
*       // Specify the first link according to the selected route, or
*       // AASYSCOM_LINK_INVALID for the implicit default link.
*       // On DSP only, the AASYSCOM_LINK_UDPCP can also be used for the default link.
*       AaSysComControlSendEchoRouteReqMsg(&testMsg, AASYSCOM_LINK_INVALID);
*       ...
*   @endcode
*
*   @par Usage:
*   This function must be used by the original sender of EchoRouteReq message
*   before reserving memory (e.g. AaSysComMsgCreate) for the message.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg()
*
******************************************************************************/
u32 AaSysComControlCalculateEchoRouteMsgLen(u16 receiverCount, u32 echoDataSize);


/**
*******************************************************************************
*
*   @brief     Sends the Echo Route Req message (for original sender)
*
*   @param[in] msg     address of pointer to message handle
*   @param[in] link    id of first link to be used (by the original sender)
*                      if link is 0 (zero) SysCom basic AaSysComMsgSend() is
*                      used instead of AaSysComMsgSendViaLink()
*
*   @return    The function returns nothing.
*
*   @par Description:
*   The AaSysComControlSendEchoRouteReqMsg() function sends the message using defined
*   link or default SysCom routing (link) depending on value of the LINK parameter.
*   The function
*   - first sets fields 'reserved' and 'padding' to zero
*   - reads timeStamp (BTS synchronized time, BCN) and sets it to senderTimeStamp
*   - sends the message using AaSysComMsgSendViaLink() or AaSysComMsgSend().
*     The used send function depends on link Id given as parameter:
*     If link == AASYSCOM_LINK_INVALID default link i.e. AaSysComMsgSend()
*     is used otherwise given link and AaSysComMsgSendViaLink() is used.

*   @par Errors:
*   None
*
*   @par Restrictions:
*   See Usage below.
*
*   @par Example: see AaSysComControlCalculateEchoRouteMsgLen()
*
*   @code
*   @endcode
*
*   @par Usage:
*   This function may be used by the _original_sender_ of the Echo Route Req message.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg()
*
******************************************************************************/
void AaSysComControlSendEchoRouteReqMsg(void **msg, TAaSysComLinkId link);


/**
*******************************************************************************
*
*   @brief     Sets number of receivers to Echo Route Req message
*
*   @param[in] routeReq       pointer to the message (SAaSysComEchoRouteReq)
*   @param[in] receiverCount  number of receivers (1..255)
*
*   @return    The function returns nothing.
*
*   @par Description:
*   The AaSysComControlSetReceiverCountToEchoRouteReqMsg() function sets number
*   of receivers (receiverCount) and resets receiverIndex to echo route message.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   This must be the first function used after reserving memory for the message,
*   since the mesage contains dynamic tables and number of receivers must
*   be used to calculate certain offsets in other functions handlng the Echo
*   Route Req message.
*
*   @par Example: see AaSysComControlCalculateEchoRouteMsgLen()
*
*   @code
*   @endcode
*
*   @par Usage:
*   May be used by the _original_sender_ of the Echo Route Req message.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg()
*
******************************************************************************/
void AaSysComControlSetReceiverCountToEchoRouteReqMsg(
    SAaSysComEchoRouteReq *routeReq, u8 receiverCount);


/**
*******************************************************************************
*
*   @brief     Sets sequenceNumber to echo route message
*
*   @param[in] routeReq  pointer to the message (SAaSysComEchoRouteReq)
*   @param[in] seqNbr    sequence number to be set to the message
*
*   @return    The function returns nothing.
*
*   @par Description:
*   The function AaSysComControlSetSequenceNumberToEchoRouteReqMsg() sets
*   sequenceNumber to echo route message.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example: see AaSysComControlCalculateEchoRouteMsgLen()
*
*   @code
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
*   @see AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg()
*
******************************************************************************/
void AaSysComControlSetSequenceNumberToEchoRouteReqMsg(
    SAaSysComEchoRouteReq *routeReq, u8 seqNbr);


/**
*******************************************************************************
*
*   @brief    Sets receiver address to echo route message
*
*   @param[in] routeReq  pointer to the message (SAaSysComEchoRouteReq)
*   @param[in] recIndex  index of receiver (n receivers -> recIndex = 0..n-1)
*   @param[in] sicAddr   reciver address to be set to the message
*
*   @return    The function returns nothing.
*
*   @par Description:
*   The function AaSysComControlSetReceiverAddressToEchoRouteReqMsg() sets
*   receiver recIndex address to Echo Route Req message.
*   NOTE that linkId is set to AASYSCOM_LINK_INVALID -> if linkId must
*   be set it must be set separately (see Restrictions) !
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   receiverCount must have been set to the message before using this function.
*   Link used to send the message to "this receiver" must be set after using
*   this function i.e. AaSysComControlSetLinkForReceiverToEchoRouteReqMsg must
*   be used after AaSysComControlSetReceiverAddressToEchoRouteReqMsg.
*
*   @par Example: see AaSysComControlCalculateEchoRouteMsgLen()
*
*   @code
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
*   @see AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg()
*
******************************************************************************/
void AaSysComControlSetReceiverAddressToEchoRouteReqMsg(
    SAaSysComEchoRouteReq *routeReq, u8 recIndex, TAaSysComSicad sicAddr);


/**
*******************************************************************************
*
*   @brief     Sets receiver timestamp to echo route message
*
*   @param[in] routeReq  pointer to the message (SAaSysComEchoRouteReq)
*   @param[in] recIndex  index of receiver (n receivers -> recIndex = 0..n-1)
*
*   @return    The function returns nothing.
*
*   @par Description:
*   The function AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg() sets receiver
*   N timestamp to Echo Route Req message.
*   Place for the timestamp is calculated because before the receiver time
*   stamp the message contains dynamic length table of sicaddresses. The function
*   reads timestamp and places it according to receiverIndex (recIndex).
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Precondition for this function is that (in addition to message memory
*   allocation) number of receivers (receiverCount) must have been set.
*
*   @par Example:
*
*   @code
*
*     void *message;
*     SAaSysComEchoRouteReq *routeReq = GLO_NULL;
*     u8 recInd;
*     ...
*     if(message != GLO_NULL)
*     {
*       routeReq = (SAaSysComEchoRouteReq*) AaSysComMsgGetPayload(message);
*       if ((recInd = routeReq->receiverIndex) < routeReq->receiverCount)
*       {
*         AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg(routeReq, recInd)
*         ...
*       }
*       ...
*     }
*     ...
*   @endcode
*
*   @par Usage:
*   This function can be used by all the receivers defined in the Echo Route Req
*   message (not by the original sender).
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaSysComControlCalculateEchoRouteMsgLen()
*
******************************************************************************/
void AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg(
    SAaSysComEchoRouteReq *routeReq, u8 recIndex);


/**
*******************************************************************************
*
*   @brief     Sets receiver N link to echo route message.
*
*   @param[in] routeReq  pointer to the message (SAaSysComEchoRouteReq)
*   @param[in] recIndex  index of receiver (n receivers -> recIndex = 0..n-1)
*   @param[in] link      linkId to be set into the request for receiver recIndex
*
*   @return    The function returns nothing.
*
*   @par Description:
*   The function AaSysComControlSetLinkForReceiverToEchoRouteReqMsg() sets
*   link for receiver recIndex to Echo Route Req message.
*   Place for the link is calculated because before link the message contains
*   dynamic length table of receiver addresse structures.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Precondition for this function is that (in addition to message memory
*   allocation) number of receivers (receiverCount) must have been set.
*
*   @par Example: see AaSysComControlCalculateEchoRouteMsgLen()
*
*   @code
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
*   @see AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg()
*        AASYSCOM_SET_LINK_FOR_RECEIVER_TO_ECHO_ROUTE_MSG
*
******************************************************************************/
void AaSysComControlSetLinkForReceiverToEchoRouteReqMsg(
    SAaSysComEchoRouteReq *routeReq, u8 recIndex, TAaSysComLinkId link);


/**
*******************************************************************************
*
*   @brief     Sets size of echoData to echo route message
*
*   @param[in] routeReq     pointer to the request structure (SAaSysComEchoRouteReq)
*   @param[in] echoDataSize size of the data (number of bytes) to be set to the
*                           message.
*
*   @return    The function returns nothing.
*
*   @par Description:
*   The function AaSysComControlSetEchoDataSizeToEchoRouteReqMsg() sets size of
*   echoData (echoDataSize) to Echo Route Req message.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Precondition for this function is that (in addition to message memory
*   allocation) number of receivers (receiverCount) must have been set.
*
*   @par Example: see AaSysComControlCalculateEchoRouteMsgLen()
*
*   @code
*   @endcode
*
*   @par Usage:
*   This function can be used by the original sender of the message.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaSysComControlSetEchoDataToEchoRouteReqMsg(),
*        AaSysComControlGetEchoDataSizeFromEchoRouteReqMsg()
*        AASYSCOM_GET_ECHODATA_FROM_ECHO_ROUTE_MSG and
*        (AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg()).
*
******************************************************************************/
void AaSysComControlSetEchoDataSizeToEchoRouteReqMsg(
    SAaSysComEchoRouteReq *routeReq, u16 echoDataSize);

/**
*******************************************************************************
*
*   @brief     Sets echoData and size of it to echo route message.
*
*   @param[in] routeReq     pointer to the request structure (SAaSysComEchoRouteReq)
*   @param[in] echoDataPtr  pointer to data to be copied
*   @param[in] echoDataSize size of the data to be copied
*
*   @return    The function returns nothing.
*
*   @par Description:
*   The function AASYSCOM_SET_ECHODATA_TO_ECHO_ROUTE_MSG sets echoData and size
*   of it (echoDataSize) to Echo Route Req message. Data is set in BIG endian
*   format. Place for the data is calculated because before data there are two
*   dynamic length tables: time stamps and receiver addresses.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Precondition for this function is that (in addition to message memory
*   allocation) number of receivers (receiverCount) must have been set.
*
*   @par Example: see AaSysComControlCalculateEchoRouteMsgLen()
*
*   @code
*   @endcode
*
*   @par Usage:
*   This function can be ised by the original sender of the Echo Route Req message
*   to set echoData and size of it to the message.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaSysComControlGetEchoDataSizeFromEchoRouteReqMsg(),
*        AaSysComControlGetEchoDataFromEchoRouteReqMsg(),
*        (AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg()).

******************************************************************************/
void AaSysComControlSetEchoDataToEchoRouteReqMsg(
    SAaSysComEchoRouteReq *routeReq, u8 *echoDataPtr, u16 echoDataSize);

/**
*******************************************************************************
*
*   @brief     Gets size of echoData from echo route message (SAaSysComEchoRouteReq)
*
*   @param[in]     routeReq        pointer to the request structure
*                                  (SAaSysComEchoRouteReq)
*   @param         echoDataSizePtr pointer to variable where to set size of the
*                                  echo data
*
*   @return    The function returns nothing.
*
*   @par Description:
*   The function AaSysComControlGetEchoDataSizeFromEchoRouteReqMsg() gets size of
*   echoData (echoDataSize) from echo route message (SAaSysComEchoRouteReq) to
*   given variable.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example: This example shows how to get sizeof echo data and actual echo
*                 data from the message.
*
*   @code
*     SAaSysComEchoRouteReq *recRouteReq = GLO_NULL;
*     void *receivedMsg  = GLO_NULL;
*     u8   *recEchoData  = GLO_NULL;
*     u16  recEchoDataLen;
*     TAaSysComMsgId  msgId;
*
*     receivedMsg = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*     msgId = AaSysComMsgGetId((const void *)receivedMsg);
*
*     if (AASYSCOM_ECHO_ROUTE_REQ_MSG == msgId)
*     {
*       recRouteReq = (SAaSysComEchoRouteReq*)AaSysComMsgGetPayload(receivedMsg);
*       AaSysComControlGetEchoDataSizeFromEchoRouteReqMsg(recRouteReq, &recEchoDataLen);
*
*       if ((recEchoDataLen > 0) &&
*           (recEchoData = (u8*) malloc(recEchoDataLen)) != NULL)
*       {
*          AaSysComControlGetEchoDataFromEchoRouteReqMsg(recRouteReq, recEchoData, &recEchoDataLen);
*          ...
*       }
*
*       ...
*     }
*     ...
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
*   @see AASYSCOM_SET_ECHODATA_TO_ECHO_ROUTE_MSG,
*        (AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg()).
*
******************************************************************************/
void AaSysComControlGetEchoDataSizeFromEchoRouteReqMsg(
    SAaSysComEchoRouteReq *routeReq, u16 *echoDataSizePtr);

/**
*******************************************************************************
*
*   @brief      Copy echoData from echo route message to memory buffer
*
*   @param[in]     routeReq        pointer to the request structure (SAaSysComEchoRouteReq)
*   @param         echoDataPtr     pointer to area where the data is to be copied
*   @param         echoDataSizePtr pointer to max size of the data to be copied
*                                  / actual number of copied bytes
*
*   @return    The function returns nothing.
*
*   @par Description:
*   The function AaSysComControlGetEchoDataFromEchoRouteReqMsg() gets echoData from echo
*   route message (SAaSysComEchoRouteReq) to given memory area. Size of the
*   echoData in the message is checked against the given size (echoDataSizePtr)
*   to prevent exceeding of the user reserved memory area. Number of actually
*   copied bytes is set - replaces the given maximum data size (echoDataSizePtr).
*   Data location in the message is first calculated because before data there
*   are dynamic lenght tables: time stamps and receiver addresses.
*   Note that one receiverAddr and one receiverTimeStamp are included in the
*   basic structure.
*   Note that data is read using AaSysComGetRawData(), which expects the data
*   being set with AaSysComSetRawData() i.e. in BIG endian format
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
*   See AaSysComControlGetEchoDataSizeFromEchoRouteReqMsg
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
*   @see AASYSCOM_SET_ECHODATA_TO_ECHO_ROUTE_MSG,
*        (AaSysComControlSetReceiverTimeStampToEchoRouteReqMsg()).
*
******************************************************************************/
void AaSysComControlGetEchoDataFromEchoRouteReqMsg(
    SAaSysComEchoRouteReq *routeReq, u8 *echoDataPtr, u16 *echoDataSizePtr);

/**
*******************************************************************************
*
*   @brief      Changes scheduler scheduler for control, if possible,
*               and sends response to request.
*
*   @param[in]  message  pointer to the request message containing
*                        SAaSysComSchedChangeReq struct.
*
*   @return    The function returns nothing.
*
*   @par Description:
*   The function AaSysComControlHandleSchedChangeReq() is for handling
*   AASYSCOM_CONTROL_SCHED_CHANGE_REQ_MSG -message. It reads scheduling
*   change data from SAaSysComSchedChangeReq and tries to change scheduling
*   on Linux. On response message, operation status indicates whether operation
*   is successful or unsuccessful with requested parameters. Also data from
*   request struct is copied to response message. Response message is sent
*   immediately after scheduling change attempt.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   Change is supported under Linux. On OSE response message should always
*   contain operationStatus EStatus_UndefinedError.
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
void AaSysComControlHandleSchedChangeReq(void **message);

/** @} end: name Function API in AaSysComControl.*/


#ifdef __cplusplus
}
#endif

/** @} end: @addtogroup  dgAaSysComCommon AaSysCom Common */

#endif /* IF_COMMON_AASYSCOM_CONTROL_H */
