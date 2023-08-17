/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2017 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_IF_AACONFIG_TAG_MSG_H_
#define _MCU_IF_AACONFIG_TAG_MSG_H_

#include <CcsCommon.h>
#include <TAaSysComSicad.h>

#ifdef CCS_NEW_IF_STRUCTURE
#include "../../COMMON/Definitions/IfAaConfig_Defs.h"
#include "../../COMMON/Messages/IfAaConfigTag_Msg.h"
#include "../Definitions/IfAaConfigTag_Defs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigTagMsgMcu AaConfigTag MCU messages
 * @ingroup dgAaConfigTagMsg
 */
/*@{*/

/** @brief Attribute tag get request message */
#define AACONFIG_TAG_GET_REQ_MSG                  0x143C      /* !- SIGNO(struct SAaConfigTagGetReqMsg) -!  */

/** @brief Attribute tag get response message */
#define AACONFIG_TAG_GET_RESP_MSG                 0x143D      /* !- SIGNO(struct SAaConfigTagGetRespMsg) -!  */

/** @brief Attribute tag set request message */
#define AACONFIG_TAG_SET_REQ_MSG                  0x143E      /* !- SIGNO(struct SAaConfigTagSetReqMsg) -!  */

/** @brief Attribute tag set response message */
#define AACONFIG_TAG_SET_RESP_MSG                 0x143F      /* !- SIGNO(struct SAaConfigTagSetRespMsg) -!  */

/** @brief Attribute tag delete request message */
#define AACONFIG_TAG_DELETE_REQ_MSG               0x1440      /* !- SIGNO(struct SAaConfigTagDeleteReqMsg) -!  */

/** @brief Attribute tag delete response message */
#define AACONFIG_TAG_DELETE_RESP_MSG              0x1441      /* !- SIGNO(struct SAaConfigTagDeleteRespMsg) -!  */

/**
 * @brief Attribute tag get request message structure
 *
 * @par Description:
 * Application sends this message to AaConfigTag service to get attribute tag value.
 * The message contains wanted attribute tag name and type.
 * The message application payload format is byte oriented.
 * Application is expected to call @ref PrepareSend_SAaConfigTagGetReqMsg
 * for this message before sending it.
 * AaConfigTag service implementation is expected to call @ref PrepareRead_SAaConfigTagGetReqMsg
 * for this message before reading data from it.
 *
 * @par Errors:
 * See errors for AaConfigTagGet, AaConfigTagGetU16, AaConfigTagGetU32, AaConfigTagGetString API functions.
 *
 * @par Restrictions:
 * None.
 *
 * @par Examples:
 *
 * @code
 *
 * TAaSysComSicad configTagSicad = AaConfigTagEeGetSicad();
 * if (AASYSCOM_ADDRESS_INVALID != configTagSicad)
 * {
 *    TAaSysComCpid myCpId = AaSysComEuUserRegister(AASYSCOM_CP_INVALID);
 *    TAaSysComSicad mySicad = AaSysComSicadGet(myCpId, AaSysComGetOwnNid());
 *    void* msg = AaSysComMsgCreate(AACONFIG_TAG_GET_REQ_MSG,
 *                                  sizeof(SAaConfigTagGetReqMsg),
 *                                  configTagSicad);
 *
 *    SAaConfigTagGetReqMsg* getReq =
 *        (SAaConfigTagGetReqMsg*)AaSysComMsgGetPayload(msg);
 *
 *    if (GLO_NULL != getReq)
 *    {
 *       getReq->type = u32_type;
 *       strncpy(getReq->name,
 *               AACONFIG_TAG_CCS_RAT_MODE_ENABLED,
 *               sizeof(getReq->name));
 *       getReq->name[sizeof(getReq->name) - 1)] = '\0';
 *
 *       PrepareSend_SAaConfigTagGetReqMsg(msg);
 *       AaSysComMsgSendS(&msg, mySicad);
 *    }
 * }
 *
 * @endcode
 *
 * @par Usage:
 * Application sends this message to AaConfigTag service to get attribute tag value in an asynchronous way.
 *
 * @par Rationale:
 * Message allows applications to get attribute tag value in an asynchronous way.
 *
 * @par Future directions:
 * None
 *
 * @see PrepareSend_SAaConfigTagGetReqMsg
 * @see PrepareRead_SAaConfigTagGetReqMsg
 * @see SAaConfigTagGetRespMsg
 * @see AaConfigTagEeGetSicad
 *
 */
typedef struct SAaConfigTagGetReqMsg
{
  char name[AACONFIG_TAG_MAX_NAME_LENGTH];  /**< Attribute tag name */
  EAttributeType type;                      /**< Attribute tag type */
} SAaConfigTagGetReqMsg;


/**
 * @brief Prepares @ref SAaConfigTagGetReqMsg message for sending
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagGetReqMsg message for sending.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * This function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagGetReqMsg message before it is sent.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagGetReqMsg message before it is sent.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareRead_SAaConfigTagGetReqMsg
 * @see SAaConfigTagGetReqMsg
 *
 */
void PrepareSend_SAaConfigTagGetReqMsg(void *message);


/**
 * @brief Prepares @ref SAaConfigTagGetReqMsg message for data reading
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagGetReqMsg message for data reading.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * This function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagGetReqMsg message before data is read from it.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagGetReqMsg message before data is read from it.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareSend_SAaConfigTagGetReqMsg
 * @see SAaConfigTagGetReqMsg
 *
 */
void PrepareRead_SAaConfigTagGetReqMsg(void *message);


/**
 * @brief Attribute tag get response message structure
 *
 * @par Description:
 * AaConfigTag service sends this message in response to received @ref SAaConfigTagGetReqMsg.
 * The message contains get operation status and requested attribute tag name, type, size and value.
 * The message application payload format is byte oriented.
 * AaConfigTag service implementation is expected to call @ref PrepareSend_SAaConfigTagGetRespMsg
 * for this message before sending it.
 * Application is expected to call @ref PrepareRead_SAaConfigTagGetRespMsg
 * for this message before reading data from it.
 *
 * @par Errors:
 * See errors for AaConfigTagGet, AaConfigTagGetU16, AaConfigTagGetU32, AaConfigTagGetString API functions.
 *
 * @par Restrictions:
 * None.
 *
 * @par Examples:
 *
 * @code
 *
 * u32 value = 0;
 * void* msg = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
 * if (GLO_NULL != msg && AACONFIG_TAG_GET_RESP_MSG == AaSysComMsgGetId(msg))
 * {
 *    PrepareRead_SAaConfigTagGetRespMsg(msg);
 *
 *    SAaConfigTagGetRespMsg* getResp =
 *        (SAaConfigTagGetRespMsg*)AaSysComMsgGetPayload(msg);
 *    if (EAaConfigRet_Ok == getResp->status)
 *    {
 *       value = getResp->tag.value.u32Value;
 *    }
 *    else
 *    {
 *       // errors handling
 *    }
 *    AaSysComMsgDestroy(&msg);
 * }
 *
 * @endcode
 *
 * @par Usage:
 * Application gets this message in response to @ref SAaConfigTagGetReqMsg.
 *
 * @par Rationale:
 * Message allows applications to get attribute tag value in an asynchronous way.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareSend_SAaConfigTagGetRespMsg
 * @see PrepareRead_SAaConfigTagGetRespMsg
 * @see SAaConfigTagGetReqMsg
 *
 */
typedef struct SAaConfigTagGetRespMsg
{
  EAaConfigRet status;                      /**< Attribute tag get status */
  SAaConfigTagData tag;                     /**< Attribute tag data */
} SAaConfigTagGetRespMsg;


/**
 * @brief Prepares @ref SAaConfigTagGetRespMsg message for sending
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagGetRespMsg message for sending.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * Function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagGetRespMsg message before it is sent.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagGetRespMsg message before it is sent.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareRead_SAaConfigTagGetRespMsg
 * @see SAaConfigTagGetRespMsg
 *
 */
void PrepareSend_SAaConfigTagGetRespMsg(void *message);


/**
 * @brief Prepares @ref SAaConfigTagGetRespMsg message for data reading
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagGetRespMsg message for data reading.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * Function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagGetRespMsg message before data is read from it.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagGetRespMsg message before data is read from it.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareSend_SAaConfigTagGetRespMsg
 * @see SAaConfigTagGetRespMsg
 *
 */
void PrepareRead_SAaConfigTagGetRespMsg(void *message);


/**
 * @brief Attribute tag set request message structure
 *
 * @par Description:
 * Application sends this message to AaConfigTag service to set attribute tag value.
 * The message contains set operation mode and set attribute tag name, type, size and value.
 * The message application payload format is byte oriented.
 * Application is expected to call @ref PrepareSend_SAaConfigTagSetReqMsg
 * for this message before sending it.
 * AaConfigTag service implementation is expected to call @ref PrepareRead_SAaConfigTagSetReqMsg
 * for this message before reading data from it.
 *
 * @par Errors:
 * See errors for AaConfigTagSet, AaConfigTagSetU16, AaConfigTagSetU32, AaConfigTagSetString,
 * AaConfigTagPublicSet, AaConfigTagPublicSetU16, AaConfigTagPublicSetU32, AaConfigTagPublicSetString,
 * AaConfigTagPersistentSetU16, AaConfigTagPersistentSetU32, AaConfigTagPersistentSetString API functions.
 *
 * @par Restrictions:
 * Persistent setting of attribute tag of any_type is not supported.
 *
 * @par Examples:
 *
 * @code
 *
 * TAaSysComSicad configTagSicad = AaConfigTagEeGetSicad();
 * if (AASYSCOM_ADDRESS_INVALID != configTagSicad)
 * {
 *    TAaSysComCpid myCpId = AaSysComEuUserRegister(AASYSCOM_CP_INVALID);
 *    TAaSysComSicad mySicad = AaSysComSicadGet(myCpId, AaSysComGetOwnNid());
 *    void* msg = AaSysComMsgCreate(AACONFIG_TAG_SET_REQ_MSG,
 *                                  sizeof(SAaConfigTagSetReqMsg),
 *                                  configTagSicad);
 *
 *    SAaConfigTagSetReqMsg* setReq =
 *        (SAaConfigTagSetReqMsg*)AaSysComMsgGetPayload(msg);
 *
 *    if (GLO_NULL != setReq)
 *    {
 *       setReq->mode = EAaConfigTagChangeMode_Public;
 *       setReq->tag.type = u32_type;
 *       strncpy(setReq->tag.name,
 *               AACONFIG_TAG_CCS_RAT_MODE_ENABLED,
 *               sizeof(setReq->tag.name));
 *       setReq->tag.name[sizeof(setReq->tag.name) - 1)] = '\0';
 *       setReq->tag.size = sizeof(setReq->tag.value.u32Value);
 *       setReq->tag.value.u32Value = 1;
 *
 *       PrepareSend_SAaConfigTagSetReqMsg(msg);
 *       AaSysComMsgSendS(&msg, mySicad);
 *    }
 * }
 *
 * @endcode
 *
 * @par Usage:
 * Application sends this message to AaConfigTag service to set attribute tag value in an asynchronous way.
 *
 * @par Rationale:
 * Message allows applications to set attribute tag value in an asynchronous way.
 *
 * @par Future directions:
 * None
 *
 * @see PrepareSend_SAaConfigTagSetReqMsg
 * @see PrepareRead_SAaConfigTagSetReqMsg
 * @see SAaConfigTagSetRespMsg
 * @see AaConfigTagEeGetSicad
 *
 */
typedef struct SAaConfigTagSetReqMsg
{
  EAaConfigTagChangeMode mode;              /**< Attribute tag set mode */
  SAaConfigTagData tag;                     /**< Set attribute tag data */
} SAaConfigTagSetReqMsg;


/**
 * @brief Prepares @ref SAaConfigTagSetReqMsg message for sending
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagSetReqMsg message for sending.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * Function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagSetReqMsg message before it is sent.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagSetReqMsg message before it is sent.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareRead_SAaConfigTagSetReqMsg
 * @see SAaConfigTagSetReqMsg
 *
 */
void PrepareSend_SAaConfigTagSetReqMsg(void *message);


/**
 * @brief Prepares @ref SAaConfigTagSetReqMsg message for data reading
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagSetReqMsg message for data reading.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * Function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagSetReqMsg message before data is read from it.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagSetReqMsg message before data is read from it.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareSend_SAaConfigTagSetReqMsg
 * @see SAaConfigTagSetReqMsg
 *
 */
void PrepareRead_SAaConfigTagSetReqMsg(void *message);


/**
 * @brief Attribute tag set response message structure
 *
 * @par Description:
 * AaConfigTag service sends this message in response to received @ref SAaConfigTagSetReqMsg.
 * The message contains set attribute tag data as well as set operation mode and status.
 * The message application payload format is byte oriented.
 * AaConfigTag service implementation is expected to call @ref PrepareSend_SAaConfigTagSetRespMsg
 * for this message before sending it.
 * Application is expected to call @ref PrepareRead_SAaConfigTagSetRespMsg
 * for this message before reading data from it.
 *
 * @par Errors:
 * See errors for AaConfigTagSet, AaConfigTagSetU16, AaConfigTagSetU32, AaConfigTagSetString,
 * AaConfigTagPublicSet, AaConfigTagPublicSetU16, AaConfigTagPublicSetU32, AaConfigTagPublicSetString,
 * AaConfigTagPersistentSetU16, AaConfigTagPersistentSetU32, AaConfigTagPersistentSetString API functions.
 *
 * @par Restrictions:
 * Persistent setting of attribute tag of any_type is not supported.
 *
 * @par Examples:
 *
 * @code
 *
 * void* msg = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
 * if (GLO_NULL != msg && AACONFIG_TAG_SET_RESP_MSG == AaSysComMsgGetId(msg))
 * {
 *    PrepareRead_SAaConfigTagSetRespMsg(msg);
 *
 *    SAaConfigTagSetRespMsg* setResp =
 *        (SAaConfigTagSetRespMsg*)AaSysComMsgGetPayload(msg);
 *    if (EAaConfigRet_Ok != setResp->status)
 *    {
 *       // errors handling
 *    }
 *    AaSysComMsgDestroy(&msg);
 * }
 *
 * @endcode
 *
 * @par Usage:
 * Application gets this message in response to @ref SAaConfigTagSetReqMsg.
 *
 * @par Rationale:
 * Message allows applications to set attribute tag value in an asynchronous way.
 *
 * @par Future directions:
 * None
 *
 * @see PrepareSend_SAaConfigTagSetRespMsg
 * @see PrepareRead_SAaConfigTagSetRespMsg
 * @see SAaConfigTagSetReqMsg
 *
 */
typedef struct SAaConfigTagSetRespMsg
{
  EAaConfigRet status;                      /**< Attribute tag set status */
  SAaConfigTagSetReqMsg req;                /**< Attribute tag set request data */
} SAaConfigTagSetRespMsg;


/**
 * @brief Prepares @ref SAaConfigTagSetRespMsg message for sending
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagSetRespMsg message for sending.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * Function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagSetRespMsg message before it is sent.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagSetRespMsg message before it is sent.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareRead_SAaConfigTagSetRespMsg
 * @see SAaConfigTagSetRespMsg
 *
 */
void PrepareSend_SAaConfigTagSetRespMsg(void *message);


/**
 * @brief Prepares @ref SAaConfigTagSetRespMsg message for data reading
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagSetRespMsg message for data reading.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * Function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagSetRespMsg message before data is read from it.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagSetRespMsg message before data is read from it.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareSend_SAaConfigTagSetRespMsg
 * @see SAaConfigTagSetRespMsg
 *
 */
void PrepareRead_SAaConfigTagSetRespMsg(void *message);


/**
 * @brief Attribute tag delete request message structure
 *
 * @par Description:
 * Application sends this message to AaConfigTag service to delete attribute tag value.
 * The message contains delete operation mode and deleted attribute tag name.
 * The message application payload format is byte oriented.
 * Application is expected to call @ref PrepareSend_SAaConfigTagDeleteReqMsg
 * for this message before sending it.
 * AaConfigTag service implementation is expected to call @ref PrepareRead_SAaConfigTagDeleteReqMsg
 * for this message before reading data from it.
 *
 * @par Errors:
 * See errors for AaConfigTagDelete, AaConfigTagPublicDelete, AaConfigTagPersistentDelete API functions.
 *
 * @par Restrictions:
 * None.
 *
 * @par Examples:
 *
 * @code
 *
 * TAaSysComSicad configTagSicad = AaConfigTagEeGetSicad();
 * if (AASYSCOM_ADDRESS_INVALID != configTagSicad)
 * {
 *    TAaSysComCpid myCpId = AaSysComEuUserRegister(AASYSCOM_CP_INVALID);
 *    TAaSysComSicad mySicad = AaSysComSicadGet(myCpId, AaSysComGetOwnNid());
 *    void* msg = AaSysComMsgCreate(AACONFIG_TAG_DELETE_REQ_MSG,
 *                                  sizeof(SAaConfigTagDeleteReqMsg),
 *                                  configTagSicad);
 *
 *    SAaConfigTagDeleteReqMsg* delReq =
 *        (SAaConfigTagDeleteReqMsg*)AaSysComMsgGetPayload(msg);
 *
 *    if (GLO_NULL != delReq)
 *    {
 *       delReq->mode = EAaConfigTagChangeMode_Public;
 *       strncpy(delReq->name,
 *               AACONFIG_TAG_CCS_RAT_MODE_ENABLED,
 *               sizeof(delReq->name));
 *       delReq->name[sizeof(delReq->name) - 1)] = '\0';
*
 *       PrepareSend_SAaConfigTagDeleteReqMsg(msg);
 *       AaSysComMsgSendS(&msg, mySicad);
 *    }
 * }
 *
 * @endcode
 *
 * @par Usage:
 * Application sends this message to AaConfigTag service to delete attribute tag value in an asynchronous way.
 *
 * @par Rationale:
 * Message allows applications to delete attribute tag value in an asynchronous way.
 *
 * @par Future directions:
 * None
 *
 * @see PrepareSend_SAaConfigTagDeleteReqMsg
 * @see PrepareRead_SAaConfigTagDeleteReqMsg
 * @see SAaConfigTagDeleteRespMsg
 * @see AaConfigTagEeGetSicad
 *
 */
typedef struct SAaConfigTagDeleteReqMsg
{
  EAaConfigTagChangeMode mode;              /**< Attribute tag delete mode */
  char name[AACONFIG_TAG_MAX_NAME_LENGTH];  /**< Deleted attribute tag name */
} SAaConfigTagDeleteReqMsg;


/**
 * @brief Prepares @ref SAaConfigTagDeleteReqMsg message for sending
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagDeleteReqMsg message for sending.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * Function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagDeleteReqMsg message before it is sent.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagDeleteReqMsg message before it is sent.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareRead_SAaConfigTagDeleteReqMsg
 * @see SAaConfigTagDeleteReqMsg
 *
 */
void PrepareSend_SAaConfigTagDeleteReqMsg(void *message);


/**
 * @brief Prepares @ref SAaConfigTagDeleteReqMsg message for data reading
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagDeleteReqMsg message for data reading.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * Function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagDeleteReqMsg message before data is read from it.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagDeleteReqMsg message before data is read from it.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareSend_SAaConfigTagDeleteReqMsg
 * @see SAaConfigTagDeleteReqMsg
 *
 */
void PrepareRead_SAaConfigTagDeleteReqMsg(void *message);


/**
 * @brief Attribute tag delete response message structure
 *
 * @par Description:
 * AaConfigTag service sends this message in response to received @ref SAaConfigTagDeleteReqMsg.
 * The message contains deleted attribute tag name as well as delete operation mode and status.
 * The message application payload format is byte oriented.
 * AaConfigTag service implementation is expected to call @ref PrepareSend_SAaConfigTagDeleteRespMsg
 * for this message before sending it.
 * Application is expected to call @ref PrepareRead_SAaConfigTagDeleteRespMsg
 * for this message before reading data from it.
 *
 * @par Errors:
 * See errors for AaConfigTagDelete, AaConfigTagPublicDelete, AaConfigTagPersistentDelete API functions.
 *
 * @par Restrictions:
 * None.
 *
 * @par Examples:
 *
 * @code
 *
 * void* msg = AaSysComMsgReceive(AASYSCOM_INFINITE_WAITTIME);
 * if (GLO_NULL != msg && AACONFIG_TAG_DELETE_RESP_MSG == AaSysComMsgGetId(msg))
 * {
 *    PrepareRead_SAaConfigTagDeleteRespMsg(msg);
 *
 *    SAaConfigTagDeleteRespMsg* delResp =
 *        (SAaConfigTagDeleteRespMsg*)AaSysComMsgGetPayload(msg);
 *    if (EAaConfigRet_Ok != delResp->status)
 *    {
 *       // errors handling
 *    }
 *    AaSysComMsgDestroy(&msg);
 * }
 *
 * @endcode
 *
 * @par Usage:
 * Application gets this message in response to @ref SAaConfigTagDeleteReqMsg.
 *
 * @par Rationale:
 * Message allows applications to delete attribute tag value in an asynchronous way.
 *
 * @par Future directions:
 * None
 *
 * @see PrepareSend_SAaConfigTagDeleteRespMsg
 * @see PrepareRead_SAaConfigTagDeleteRespMsg
 * @see SAaConfigTagDeleteReqMsg
 *
 */
typedef struct SAaConfigTagDeleteRespMsg
{
  EAaConfigRet status;                      /**< Attribute tag delete operation status */
  SAaConfigTagDeleteReqMsg req;             /**< Attribute tag delete request data */
} SAaConfigTagDeleteRespMsg;


/**
 * @brief Prepares @ref SAaConfigTagDeleteRespMsg message for sending
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagDeleteRespMsg message for sending.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * Function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagDeleteRespMsg message before it is sent.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagDeleteRespMsg message before it is sent.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareRead_SAaConfigTagDeleteRespMsg
 * @see SAaConfigTagDeleteRespMsg
 *
 */
void PrepareSend_SAaConfigTagDeleteRespMsg(void *message);


/**
 * @brief Prepares @ref SAaConfigTagDeleteRespMsg message for data reading
 *
 * @param[in] message Prepared message handle
 *
 * @return None
 *
 * @par Description:
 * Function prepares @ref SAaConfigTagDeleteRespMsg message for data reading.
 *
 * @par Errors:
 * None.
 *
 * @par Restrictions:
 * Function does not check prepared message handle against NULL.
 * Checking of prepared message handle must be done before it is passed to this function.
 *
 * @par Examples:
 * None.
 *
 * @par Usage:
 * Function shall be called for @ref SAaConfigTagDeleteRespMsg message before data is read from it.
 *
 * @par Rationale:
 * Function shall be called for @ref SAaConfigTagDeleteRespMsg message before data is read from it.
 *
 * @par Future directions:
 * None.
 *
 * @see PrepareSend_SAaConfigTagDeleteRespMsg
 * @see SAaConfigTagDeleteRespMsg
 *
 */
void PrepareRead_SAaConfigTagDeleteRespMsg(void *message);


/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_MCU_IF_AACONFIG_TAG_MSG_H_
