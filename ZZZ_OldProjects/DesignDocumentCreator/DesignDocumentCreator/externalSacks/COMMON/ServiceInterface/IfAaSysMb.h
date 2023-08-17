/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaSysMb interface header file.
* @module                AaSysMb
*
* Copyright 2015 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef COMMON_IFAASYSMB_H
#define COMMON_IFAASYSMB_H

/**
* @defgroup dgAaSysMb System Message Broker service (AaSysMb)
* @ingroup dgBasicSystemSw
*
* Common Computer and Support SW System Message Broker (AaSysMb) Service.
*
* SysMb API provides simple methods for publishing and subscribing messages
* based on the SIC message type number (message ID).
*
*/

/**
* @defgroup dgAaSysMbApi API Service Reference
* @ingroup dgAaSysMb
*
* Application Programming Interface.
*
* API specification (current):
*
*   https://sharenet-ims.inside.nokiasiemensnetworks.com/Open/D-171124
*
* CC&S Wiki for AaSysMb:
*
*   http://wikis.inside.nokiasiemensnetworks.com/bin/view/CSSWiki/AaSysMb
*
*/
/*@{*/

/**
*@defgroup dgAaSysMbConfigurationTags Configuration tags
*@ingroup dgAaSysMb
*
* Runtime configuration can be divided into pre- and post-configuration phases.
* Pre-configuration takes place before CE startup has been done for a service.
* Post-configuration takes place after CE, EE and EU startup. Configuration is
* handled using so called configuration tags. Data and keys are variable
* width in size so they are quite flexible to use.
* \n\n
* Usually configuration tags are used for input direction i.e. feeding
* configuration to CC&S service. However some tags can also be used for output
* direction i.e. for advertising CC&S service state or capabilities. Configuration
* tag description should state wether the tag is inteded for feeding information
* (input) to the service or the service uses the tag for capability and state
* advertisement (output).
*
*
* @ref dsVariation "[CCSAPI_VARIABILITY]"
*
*
* @verbatim
*  Tag name:        ccs.service.aasysmb.connecttime
*
*  Direction:       input
*
*  Context:         CE
*
*  Description:     Sets the time which SysMb tries to configure itself to
*                   handle global zone. By default the value is 8 seconds.
*
*  Effect analysis: N/A
*
*  Restriction:     None
*
*  Value:           IE Type:     Size:     Range:
*                   number       u32       0...0xFFFFFFFF
*
*  Define:          AASYSMB_CONFIG_TAG_CONNECTTIME
*
*  See:             None
* @endverbatim
*
*
* @verbatim
*  Tag name:        sys.mw.broker.local.online
*
*  Direction:       output
*
*  Context:         CE
*
*  Description:     Message broker availability on local zone.
*
*  Effect analysis: N/A
*
*  Restriction:     None
*
*  Value:           IE Type:  Size:   Range:
*                   TBoolean  u32     "1" - AaSysMb service available on local zone
*                                     "0" / not set - AaSysMb service not available
*
*  Define:          AASYSMB_CONFIG_TAG_LOCAL_ONLINE
*
*  See:             None
* @endverbatim
*
*
* @verbatim
*  Tag name:        sys.mw.broker.server.online
*
*  Direction:       output
*
*  Context:         CE
*
*  Description:     Message broker full availability, including global zone.
*
*  Effect analysis: N/A
*
*  Restriction:     None
*
*  Value:           IE Type:  Size:   Range:
*                   TBoolean  u32     "1" - AaSysMb service fully available
*                                     "0" / not set - AaSysMb service on global zone not available
*
*  Define:          AASYSMB_CONFIG_TAG_SERVER_ONLINE
*
*  See:             None
* @endverbatim
*/


/**
* @defgroup dpAaSysMbRadParams R&D parameters
* @ingroup dgAaSysMb
*
* @ref dsVariation "[CCSAPI_VARIABILITY]"
*
* @verbatim
*  Parameter name:  ERadCcs_PrintAaSysMb
*
*  Direction:       input
*
*  Context:         EE
*
*  Description:     Controls debug prints of AaSysMb service.
*
*  Effect analysis: Depending parameter value, debug level prints are enabled
*                   or disabled.
*
*  Restrictions:    None
*
*  Value:           Range:     Description:
*                   0          Debug level prints are disabled.
*                   1          Debug level prints are enabled.
*
*  See:             None
* @endverbatim
*
* @verbatim
*  Parameter name:  ERadCcs_AaSysMbStoragePrinterEnable
*
*  Direction:       input
*
*  Context:         EE
*
*  Description:     Controls SysMb storage printer.
*
*  Effect analysis: Depending parameter value, SysMb storage printer which
*                   prints the amount of effective publications and subscriptions
*                   in storage is enabled or disabled.
*
*  Restrictions:    None
*
*  Value:           Range:     Description:
*                   0          Storage printer is disabled.
*                   1          Storage printer is enabled.
*
*  See:             None
* @endverbatim
*/


/*----------------------- INCLUDED FILES -------------------------------------*/

#include <IfAaSysCom.h>

#include <CcsCommon.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include <../Definitions/IfAaSysMb_Defs.h>
#include <../Messages/IfAaSysMb_Msg.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/*----------------------- PUBLIC INTERFACES ----------------------------------*/

/**
* @defgroup dgAaSysMbApiCommon AaSysMb Common API
* @ingroup dgAaSysMb
*
*/
/*@{*/

/**
********************************************************************************
*
* @brief        Delete existing subscriptions and/or publications.
*
* @param[in]    address   Specifies the SIC address, publications and/or
*                         subscriptions from which are deleted. Sic address with
*                         CpId AASYSCOM_CP_ANY can be used to flush every Cp
*                         publications/subscriptions.
*
* @param[in]    mode      Specifies whether only publications, subscriptions,
*                         or both are deleted.
*
* @param[in]    zone      Specifies the zone in which the subscriptions or/and
*                         publications are flushed. All zones can be flushed at
*                         once with zone parameter AASYSMB_ZONE_ANY.
*
* @return       The function returns success of operation.
*
* @par Description:
* The AaSysMbFlush() function deletes the existing subcriptions and/or
* publications of the user-specified SIC address.
* Note: AaSysMbFlush() function does not delete prepared messages which has not
* been published yet! AaSysMbRecall() function should be used to free prepared
* messages.
*
* @par Errors:
* #EAaSysMbRetVal_InvalidParam In case invalid parameter was passed to
* function.\n
* #EAaSysMbRetVal_Error In case SysCom message could not be created.
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
* AaSysMbPublish, AaSysMbSubscribe, AaSysMbRecall
*
* @par Example:
*   @code
*     #include <IfAaSysCom.h>
*     #include <IfAaSysMb.h>
*
*     void ExampleFunction(void)
*     {
*       EAaSysMbRetVal ret;
*       TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                                   AaProEuCurrent());
*
*       ret = AaSysMbFlush(AaSysComSicadGet(AASYSCOM_CP_ANY, AaSysComGetOwnNid()),
*                          EAaSysMbFlushMode_Both,
*                          AASYSMB_ZONE_GLOBAL);
*
*       if(ret == EAaSysMbRetVal_Ok)
*       {
*         // Flush succeeded
*       }
*       else
*       {
*         // Flush failed
*       }
*     }
*   @endcode
*
*******************************************************************************/
EAaSysMbRetVal AaSysMbFlush(const TAaSysComSicad address,
                            const EAaSysMbFlushMode mode,
                            const TAaSysMbZoneId zone);



/**
********************************************************************************
*
* @brief        Reserve and prepare resources for a message to be published.
*
* @param[in]    messagePayloadSize  Specifies the size of the message body
*                                   (user payload area) in bytes.
*
* @param[in]    messageId   Specifies the message id (SIC message type number)
*                           of the published message.
*
* @param[in]    publisher   Specifies the SIC address of the publisher. This
*                           address is shown as the sender of the message to
*                           the subscribers. Publisher SIC address can be any
*                           valid, registered SIC address on node in which
*                           function caller is running.
*
* @param[in]    mode        Specifies the mode in which the message is
*                           published.
*
* @param[in]    zone        Specifies the zone in which the message is
*                           published. A message can't be published on all
*                           zones simultaneously (AASYSMB_ZONE_ANY).
*
* @return       The function returns a pointer to the application payload of
*               the new message. In case of errors GLO_NULL is returned.
*
* @par Description:
* The AaSysMbPrepare() function reserves and prepares appropriate resources
* for the message.
*
* @par Errors:
* In case of errors GLO_NULL is returned.
*
* @par Restrictions:
* Maximum size of message to be published is defined by SysCom API.
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
* AaSysMbPublish, AaSysMbRecall
*
* @par Example:
* see AaSysMbPublish Example paragraph.
*
*******************************************************************************/
void *AaSysMbPrepare( const TAaSysComMsgSize messagePayloadSize,
                      const TAaSysComMsgId messageId,
                      const TAaSysComSicad publisher,
                      const EAaSysMbPublMode mode,
                      const TAaSysMbZoneId zone );



/**
********************************************************************************
*
* @brief        Function sends the user-specified message to its subscribers.
*
* @param[in]    payload     Points to a pointer to the application payload of
*                           the message to be published. It is nulled by return
*                           in case of successful publication.
*
* @return       The function returns success of operation. In case of error
*               message pointer is NOT nulled.
*
* @par Description:
* The AaSysMbPublish() function sends the user-specified message to the
* subscribers of the very message.
* NOTE: It is application's responsibility to unpublish/flush out of date
* publications.
*
* @par Errors:
* #EAaSysMbRetVal_InvalidParam In case invalid parameter was passed to
* function.
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
* AaSysMbPrepare, AaSysMbUnpublish, AaSysMbRecall, AaSysMbSubscribe
*
* @par Example:
*   @code
*     #include <IfAaSysCom.h>
*     #include <IfAaSysMb.h>
*
*     void ExampleFunction(void)
*     {
*       EAaSysMbRetVal ret;
*       void *msg;
*       char testData[] = "Something";
*       TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                                   AaProEuCurrent());
*
*       msg = AaSysMbPrepare(sizeof(testData), EXAMPLE_MSGID,
*                         AaSysComSicadGet(myCpid, AaSysComGetOwnNid()),
*                         EAaSysMbPublMode_KeepOne,
*                         AASYSMB_ZONE_LOCAL_NODE);
*
*       memcpy(msg, testData, sizeof(testData));
*
*       ret = AaSysMbPublish(&msg);
*
*       if(ret == EAaSysMbRetVal_Ok)
*       {
*         // Publishing message succeeded
*       }
*       else
*       {
*         // Publishing failed. Message pointer is not nulled.
*       }
*     }
*   @endcode
*
*******************************************************************************/
EAaSysMbRetVal AaSysMbPublish(void **payload);



/**
********************************************************************************
*
* @brief        Function registers new subscription to the message broker.
*
* @param[in]    messageId   Specifies the message id (SIC message type number)
*                           of the subscribed message.
*
* @param[in]    subscriber  Specifies the SIC address of the subscriber.
*                           Subscribed message is sent to this address.
*                           Subscriber SIC address can be any valid, registered
*                           SIC address on node in which function caller is
*                           running.
*
* @param[in]    mode        Specifies the mode in which the message is
*                           subscribed. All possible subscription modes are
*                           defined in enumeration EAaSysMbSubsMode.
*
* @param[in]    zone        Specifies the zone in which the message is
*                           subscribed. A subscription can't be done on all
*                           zones simultaneously (AASYSMB_ZONE_ANY).
*
* @return       The function returns success of operation.
*
* @par Description:
* The AaSysMbSubscribe() function registers the user-specified subscription to
* the message broker. Subscriber of a message must be registered to SysCom to
* be able to receive published messages.
* NOTE: It is application's responsibility to unsubscribe/flush out of date
* subscriptions.
*
* @par Errors:
* #EAaSysMbRetVal_InvalidParam In case invalid parameter was passed to
* function.\n
* #EAaSysMbRetVal_Error In case SysCom message could not be created.
*
* No errors are defined.
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* Subscriber of a message must be registered to SysCom to be able to receive
* published messages.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysMbPublish, AaSysMbUnsubscribe
*
* @par Example:
*   @code
*     void ExampleFunction()
*     {
*       EAaSysMbRetVal ret;
*       void *recMsg = GLO_NULL;
*       TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                                   AaProEuCurrent());
*
*       ret = AaSysMbSubscribe(EXAMPLE_MSGID,
*                              AaSysComSicadGet(myCpid, AaSysComGetOwnNid()),
*                              EAaSysMbSubsMode_All,
*                              AASYSMB_ZONE_LOCAL_NODE);
*
*       if(ret == EAaSysMbRetVal_Ok)
*       {
*         recMsg = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*       }
*       else
*       {
*         // Subscribing failed.
*       }
*     }
*   @endcode
*
*******************************************************************************/
EAaSysMbRetVal AaSysMbSubscribe(const TAaSysComMsgId messageId,
                                const TAaSysComSicad subscriber,
                                const EAaSysMbSubsMode mode,
                                const TAaSysMbZoneId zone);



/**
********************************************************************************
*
* @brief        Free the resources reserved for a prepared message.
*
* @param[in]    payload   Points to a pointer to the application payload of the
*                         message to be recalled. Resources reserved in function
*                         AaSysMbPrepare() are freed and pointer to the message
*                         is nulled.
*
* @return       The function returns success of operation.
*
* @par Description:
* The AaSysMbRecall() function frees the resources reserved for the prepared
* but not yet published message.
*
* @par Errors:
* #EAaSysMbRetVal_InvalidParam In case invalid parameter was passed to
* function.\n
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* This function can be used only for messages prepared with function
* AaSysMbPrepare(). Message should not be published with function
* AaSysMbPublish() before recalling it.
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see
* AaSysMbPrepare, AaSysMbPublish
*
* @par Example:
*   @code
*     void ExampleFunction()
*     {
*       EAaSysMbRetVal ret;
*       void *msg;
*       char testData[] = "Something";
*       TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                                   AaProEuCurrent());
*
*       msg = AaSysMbPrepare(sizeof(testData), EXAMPLE_MSGID,
*                             AaSysComSicadGet(myCpid, AaSysComGetOwnNid()),
*                             EAaSysMbPublMode_KeepOne,
*                             AASYSMB_ZONE_LOCAL_NODE);
*
*       memcpy(msg, testData, sizeof(testData));
*
*       ret = AaSysMbRecall(&msg);
*
*       if(ret == EAaSysMbRetVal_Ok)
*       {
*         // Recalling message succeeded
*       }
*       else
*       {
*         // Recalling failed.
*       }
*     }
*   @endcode
*
*******************************************************************************/
EAaSysMbRetVal AaSysMbRecall(void **payload);



/**
********************************************************************************
*
* @brief        Unpublish a message published in keep mode.
*
* @param[in]    messageId  Specifies the message id (SIC message type number)
*                          of the unpublished message.
*
* @param[in]    publisher  Specifies the SIC address of the publisher. Publisher
*                          SIC address can be any valid, registered SIC address
*                          on node in which function caller is running.
*
* @param[in]    zone       Specifies the zone in which the message is
*                          unpublished.
*
* @return       The function returns success of operation.
*
* @par Description:
* The AaSysMbUnpublish() function unpublishes a message that has been published
* in keep mode.
*
* @par Errors:
* #EAaSysMbRetVal_InvalidParam In case invalid parameter was passed to
* function.\n
* #EAaSysMbRetVal_Error In case SysCom message could not be created.
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
* AaSysMbPublish
*
* @par Example:
*   @code
*     #include <IfAaSysCom.h>
*     #include <IfAaSysMb.h>
*
*     void ExampleFunction()
*     {
*       EAaSysMbRetVal ret;
*       void *msg;
*       char testData[] = "Something";
*       TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                                   AaProEuCurrent());

*       msg = AaSysMbPrepare(sizeof(testData), EXAMPLE_MSGID,
*                           AaSysComSicadGet(myCpid, AaSysComGetOwnNid()),
*                           EAaSysMbPublMode_KeepOne,
*                           AASYSMB_ZONE_LOCAL_NODE);
*
*       memcpy(msg, testData, sizeof(testData));
*
*       AaSysMbPublish(&msg);
*
*       ret = AaSysMbUnpublish(EXAMPLE_MSGID,
*                         AaSysComSicadGet(myCpid, AaSysComGetOwnNid()),
*                         AASYSMB_ZONE_LOCAL_NODE);
*
*       if(ret == EAaSysMbRetVal_Ok)
*       {
*         // Unpublishing a publication succeeded
*       }
*       else
*       {
*         // Unpublishing failed.
*       }
*     }
*   @endcode
*
*******************************************************************************/
EAaSysMbRetVal AaSysMbUnpublish(const TAaSysComMsgId messageId,
                                const TAaSysComSicad publisher,
                                const TAaSysMbZoneId zone);



/**
********************************************************************************
*
* @brief        Unsubscribe a message.
*
* @param[in]    messageId   Specifies the message id (SIC message type number)
*                           of the message to be unsubscribed.
*
* @param[in]    subscriber  Specifies the SIC address of the subscriber.
*                           Subscriber SIC address can be any valid, registered
*                           SIC address on node in which function caller is
*                           running.
*
* @param[in]    zone        Specifies the zone in which the message is
*                           unsubscribed.
*
* @return       The function returns success of operation.
*
* @par Description:
* The AaSysMbUnsubscribe() function unsubscribes an earlier subscribed message.
*
* @par Errors:
* #EAaSysMbRetVal_InvalidParam In case invalid parameter was passed to
* function.\n
* #EAaSysMbRetVal_Error In case SysCom message could not be created.
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
* AaSysMbSubscribe
*
* @par Example:
*   @code
*     #include <IfAaSysCom.h>
      #include <IfAaSysMb.h>
*
*     void ExampleFunction()
*     {
*       EAaSysMbRetVal ret;
*       void *recMsg = GLO_NULL;
*       TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                                   AaProEuCurrent());
*
*       AaSysMbSubscribe(EXAMPLE_MSGID,
*                       AaSysComSicadGet(myCpid, AaSysComGetOwnNid()),
*                       EAaSysMbSubsMode_All,
*                       AASYSMB_ZONE_LOCAL_NODE);
*
*       recMsg = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
*
*       ret = AaSysMbUnsubscribe(EXAMPLE_MSGID,
*                         AaSysComSicadGet(myCpid, AaSysComGetOwnNid()),
*                         AASYSMB_ZONE_LOCAL_NODE);
*
*       if(ret == EAaSysMbRetVal_Ok)
*       {
*         // Unsubscribing succeeded
*       }
*       else
*       {
*         // Unsubscribing failed.
*       }
*     }
*   @endcode
*
*******************************************************************************/
EAaSysMbRetVal AaSysMbUnsubscribe(const TAaSysComMsgId messageId,
                                  const TAaSysComSicad subscriber,
                                  const TAaSysMbZoneId zone);



/**
********************************************************************************
*
* @brief        Set application payload format of prepared message.
*
* @param[in]    payload     Points to a pointer to the application payload of
*                           the message to be published.
*
* @param[in]    apf         Specifies message application payload format (MAPF)
*                           for the message.
*
* @return       The function returns success of operation.
*
* @par Description:
* Function AaSysMbSetApf() sets application payload format of message prepared
* via AaSysMbPrepare() function.
*
* @par Errors:
* #EAaSysMbRetVal_InvalidParam In case invalid parameter was passed to
* function.\n
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
* AaSysMbPrepare, AaSysMbPublish
*
* @par Example:
*   @code
*     #include <IfAaSysCom.h>
      #include <IfAaSysMb.h>
*
*     void ExampleFunction(void)
*     {
*         EAaSysMbRetVal ret;
*         void *msg;
*         u32 testData = 0x1234;
*         TAaSysComCpid myCpid = AaSysComUserRegister(AASYSCOM_CP_INVALID,
*                                                     AaProEuCurrent());
*
*         msg = AaSysMbPrepare(sizeof(testData),
*                              EXAMPLE_MSGID,
*                              AaSysComSicadGet(myCpid, AaSysComGetOwnNid()),
*                              EAaSysMbPublMode_OneShot,
*                              AASYSMB_ZONE_GLOBAL);
*
*         memcpy(msg, &testData, sizeof(testData));
*
*         ret = AaSysMbSetApf((void*)&msg, EAaSysComMsgApf_8Big);
*
*         if(ret == EAaSysMbRetVal_Ok)
*         {
*             // Setting message APF succeeded.
*         }
*         else
*         {
*             // Setting message APF failed.
*         }
*     }
*   @endcode
*
*******************************************************************************/
EAaSysMbRetVal AaSysMbSetApf(void **payload, EAaSysComMsgApf apf);


/*@}*/


#ifdef __cplusplus
}
#endif


#endif /* COMMON_IFAASYSMB_H */

