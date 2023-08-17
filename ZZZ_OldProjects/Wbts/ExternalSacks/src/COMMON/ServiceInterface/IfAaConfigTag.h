/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _COMMON_IF_AACONFIG_TAG_H_
#define _COMMON_IF_AACONFIG_TAG_H_

#include <CcsCommon.h>
#ifdef CCS_NEW_IF_STRUCTURE
#include <../Definitions/IfAaConfig_Defs.h>
#include <../Definitions/IfAaConfigTag_Defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup dgAaConfigTag AaConfigTag API
*
* Common Computer and Support SW Configuration AaConfigTag service API.
*
*/

/**
 * @defgroup dgAaConfigTagApi AaConfigTag functions
 * @ingroup dgAaConfigTag
 */

/**
 * @defgroup dgAaConfigTagApiCommon AaConfigTag common functions
 * @ingroup dgAaConfigTagApi
 */
/*@{*/

/**
********************************************************************************
*
* @brief        AaConfigTagSet sets value for given attribute tag.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @param[in]    value   Pointer to attribute tag value which shall be copied.
*
* @param[in]    length  The length of the attribute tag value in bytes.
*
* @return       Function returns success of operation.
*
* @par Description:
* The AaConfigTagSet() function sets value for given attribute tag. If tag has
* registered observers, they will be notified. The given value shall be copied.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_Error
* - EAaConfigRet_NoMem
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* <b>This function should only be used for special purposes because no type check is executed with AaConfigTagGetxxx functions.
* Type specific Set functions should be used together with type specific Get functions whenever possible.</b>
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see AaConfigTagSetU16
* @see AaConfigTagSetU32
* @see AaConfigTagSetString
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_ETH0_IP "sys.net.eth0.ip"
*
*   void exampleFunc(void)
*   {
*     void* value = "127.0.0.1";
*     ret = AaConfigTagSet(AACONFIG_TAG_NAME_ETH0_IP, &value, sizeof(value));
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagSet(const char* const name,
                            const void* const value,
                            const u32 length);


/**
********************************************************************************
*
* @brief        AaConfigTagSetString sets string value for given attribute tag.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @param[in]    value   Pointer to NULL-terminated attribute tag value which
*                       shall be copied.
*
* @return       Function returns success of operation.
*
* @par Description:
* The AaConfigTagSetString() sets value for given attribute tag. If tag has
* registered observers, they will be notified. The given value shall be copied.
* The value must be NULL-terminated string.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_Error
* - EAaConfigRet_NoMem
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
* @see AaConfigTagPersistentSetString
* @see AaConfigTagGetString
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_ETH0_IP "sys.net.eth0.ip"
*
*   void exampleFunc(void)
*   {
*     char* value = "127.0.0.1";
*     ret = AaConfigTagSetString(AACONFIG_TAG_NAME_ETH0_IP, &value);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagSetString(const char* const name,
                                  const char* const value);


/**
********************************************************************************
*
* @brief        AaConfigTagSetU32 sets unsigned 32bit value for given tag.
*
* @param[in]    name  Pointer to NULL-terminated string containing the
*                     attribute tag name.
*
* @param[in]    value Unsigned 32bit attribute tag value which shall be copied.
*
* @return       Function returns success of operation.
*
* @par Description:
* The AaConfigTagSetU32() function sets value for given attribute tag. If tag
* has registered observers, they will be notified. The given value shall be
* copied. The value must be unsigned 32bit number.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_Error
* - EAaConfigRet_NoMem
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
* @see AaConfigTagPersistentSetU32
* @see AaConfigTagGetU32
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE1 "app.example.ex1"
*
*   void exampleFunc(void)
*   {
*     u32 value = 0x06660666;
*     ret = AaConfigTagSetU32(AACONFIG_TAG_NAME_EXAMPLE1, value);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagSetU32(const char* const name,
                               const u32 value);


/**
********************************************************************************
*
* @brief        AaConfigTagSetU16 sets unsigned 16bit value for given attribute tag.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @param[in]    value   Unsigned 16bit attribute tag value which shall be copied.
*
* @return       Function returns success of operation.
*
* @par Description:
* The AaConfigTagSet() function sets value for given attribute tag. If tag has
* registered observers, they will be notified. The given value shall be copied.
* The value must be unsigned 16bit number.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_Error
* - EAaConfigRet_NoMem
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
* @see AaConfigTagPersistentSetU16
* @see AaConfigTagGetU16
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE2 "app.example.ex2"
*
*   void exampleFunc(void)
*   {
*     u32 value = 0x0666;
*     ret = AaConfigTagSetU16(AACONFIG_TAG_NAME_EXAMPLE2, value);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagSetU16(const char* const name,
                                const u16 value);


/**
********************************************************************************
*
* @brief        AaConfigTagSetPointer sets pointer value for given attribute tag.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @param[in]    value   Pointer attribute tag value which shall be copied.
*
* @return       Function returns success of operation.
*
* @par Description:
* The AaConfigTagSet() function sets value for given attribute tag. If tag has
* registered observers, they will be notified. The given value shall be copied.
* The value must be a pointer.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_Error
* - EAaConfigRet_NoMem
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
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE3 "app.example.ex3"
*
*   void exampleFunc(void)
*   {
*     u32 *value = 0x06660666;
*     ret = AaConfigTagSetPointer(AACONFIG_TAG_NAME_EXAMPLE3, &value);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagSetPointer(const char* const name,
                                   const void* value);

/**
********************************************************************************
*
* @brief          Check if a given attribute tag is set.
*
* @param[in]      name    Pointer to NULL-terminated string containing the
*                         attribute tag name.
*
* @return         GLO_TRUE if tag is set, GLO_FALSE if it is not set.
*
* @par Description:
* The AaConfigTagIsSet() function can be used to check if a tag has been set.
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
* @see AaConfigTagSet
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE1 "app.example.ex1"
*
*   void exampleFunc(void)
*   {
*     if(AaConfigTagIsSet(AACONFIG_TAG_NAME_EXAMPLE1) == GLO_FALSE)
*     {
*       // Tag is not set, perhaps set it here.
*               ....
*     }
*   }
* @endcode
*
*******************************************************************************/
TBoolean AaConfigTagIsSet(const char* const name);


/**
********************************************************************************
*
* @brief          Get value of given attribute tag.
*
* @param[in]      name    Pointer to NULL-terminated string containing the
*                         attribute tag name.
*
* @param[in,out]  value   Pointer to a pointer attribute tag value where the
*                         value is stored.
*
* @param[in,out]  length  Pointer to a placeholder where the length of the
*                         attribute tag value is set in bytes.
*                         In case of type string it is length of string +
*                         terminating NULL.
*
* @return         Function returns success of operation.
*
* @par Description:
* The AaConfigTagGet() function gets value of given attribute tag. Pointer to
* a copy of value of the attribute tag shall be returned. The copy shall be
* allocated via AaMem from BDM pool.
* Note! Function returns EAaConfigRet_Ok also in case tag is found, but its
* value is not set. In that case value parameter is set to NULL and length
* parameter is set to 0. So, it is important to check also retuned parameters
* instead of only checking function return value.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_TagNotFound
* - EAaConfigRet_NoMem
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* <b>It is user's responsibility to free the memory allocated for returned copy of  tag value.</b>
*
* <b>This function should only be used for special purposes because no type check is executed.
* Type specific Get functions should be used together with type specific Set functions whenever possible.</b>
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see AaConfigTagSet
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE1 "app.example.ex1"
*
*   void exampleFunc(void)
*   {
*     u32 *value;
*     u32 valueLength = 0;
*     ret = AaConfigTagGet(AACONFIG_TAG_NAME_EXAMPLE1, &value, &valueLength);
*
*     if(ret == EAaConfigRet_Ok && value != GLO_NULL)
*     {
*       // Tag value get successful
*       ....
*       // Returned copy needs to be freed.
*       AaMemUnRef(&value);
*     }
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagGet(const char* const name,
                            void** const value,
                            u32* const length);

/**
********************************************************************************
*
* @brief          Get value of given attribute tag of type string.
*
* @param[in]      name    Pointer to NULL-terminated string containing the
*                         attribute tag name.
*
* @param[in,out]  value   Pointer to a pointer attribute tag value where the
*                         value is stored.
*
* @param[in,out]  length  Pointer to a placeholder where the length of the
*                         attribute tag value is set in bytes.
*                         In case of type string it is length of string +
*                         terminating NULL.
*
* @return         Function returns success of operation.
*
* @par Description:
* The AaConfigTagGet() function gets value of given attribute tag. Pointer to
* a copy of value of the attribute tag shall be returned. The copy shall be
* allocated via AaMem from BDM pool.
* Note! Function returns EAaConfigRet_Ok also in case tag is found, but its
* value is not set. In that case value parameter is set to NULL and length
* parameter is set to 0. So, it is important to check also retuned parameters
* instead of only checking function return value.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_TagNotFound
* - EAaConfigRet_NoMem
* - EAaConfigRet_TagTypeMismatch
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* <b>It is user's responsibility to free the memory allocated for returned copy of  tag value.</b>
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see AaConfigTagSetString
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE1 "app.example.ex1"
*
*   void exampleFunc(void)
*   {
*     u32 *value;
*     u32 valueLength = 0;
*     ret = AaConfigTagGetString(AACONFIG_TAG_NAME_EXAMPLE1, &value, &valueLength);
*
*     if(ret == EAaConfigRet_Ok && value != GLO_NULL)
*     {
*       // Tag value get successful
*       ....
*       // Returned copy needs to be freed.
*       AaMemUnRef(&value);
*     }
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagGetString(const char* const name,
                                  void** const value,
                                  u32* const length);

/**
********************************************************************************
*
* @brief          Get value of given attribute tag of type U16.
*
* @param[in]      name    Pointer to NULL-terminated string containing the
*                         attribute tag name.
*
* @param[out]     value   Pointer to a placeholder of size U16 where the
*                         value is stored.
*
* @return         Function returns success of operation.
*
* @par Description:
* The AaConfigTagGetU16() function gets value of given attribute tag, which
* shall be type of U16. The copy of the value shall be stored to given
* placeholder.
* Note! Function returns EAaConfigRet_TagNotSet in case tag is found,
* but its value is not set. In that case value parameter is left untouched.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_TagNotSet
* - EAaConfigRet_TagSizeMismatch
* - EAaConfigRet_TagTypeMismatch
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
* @see AaConfigTagSetU16
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE1 "app.example.ex1"
*
*   void exampleFunc(void)
*   {
*     u16 value = 0x10; // If tag is not found, this value stays untouched
*                       // which allows use of default value
*     ret = AaConfigTagGetU16(AACONFIG_TAG_NAME_EXAMPLE1, &value);
*
*     if(ret == EAaConfigRet_Ok)
*     {
*       // Tag value get successful
*     }
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagGetU16(const char* const name, u16* const value);


/**
********************************************************************************
*
* @brief          Get value of given attribute tag of type U32.
*
* @param[in]      name    Pointer to NULL-terminated string containing the
*                         attribute tag name.
*
* @param[out]     value   Pointer to a placeholder of size U32 where the
*                         value is stored.
*
* @return         Function returns success of operation.
*
* @par Description:
* The AaConfigTagGetU32() function gets value of given attribute tag, which
* shall be type of U32. The copy of the value shall be stored to given
* placeholder.
* Note! Function returns EAaConfigRet_TagNotSet in case tag is found,
* but its value is not set. In that case value parameter is left untouched.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_TagNotSet
* - EAaConfigRet_TagSizeMismatch
* - EAaConfigRet_TagTypeMismatch
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
* @see AaConfigTagSetU32
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE1 "app.example.ex1"
*
*   void exampleFunc(void)
*   {
*     u32 value = 0x10000; // If tag is not found, this value stays untouched
*                          // which allows use of default value
*     ret = AaConfigTagGetU32(AACONFIG_TAG_NAME_EXAMPLE1, &value);
*
*     if(ret == EAaConfigRet_Ok)
*     {
*       // Tag value get successful
*     }
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagGetU32(const char* const name, u32* const value);


/**
********************************************************************************
*
* @brief        Get value for given attribute tag or default value.
*
* @param[in]     name   Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @param[in,out] value  Pointer to a pointer attribute tag value where the
*                       value is stored.
*
* @param[in,out] length Pointer to a placeholder where the length of the
*                       attribute tag value is set in bytes.
*
* @param[in]     def    Pointer to an attribute tag value used as default value.
*
* @param[in]     dlength Length of the default value.
*
* @return         Function returns success of operation.
*
* @par Description:
* The AaConfigTagGetDefault() function gets value for given attribute tag.
* Pointer to a copy of value of the attribute tag shall be returned if attribute
* tag exists. If there is no value assigned to the tag or the tag does not exist,
* copy of pointer to given default value and it's length are returned and the
* attribute tag shall be created as explained in AaConfigTagSet.
* NOTE! Memory for the returned copy shall be allocated from pool
* EAaMemSysPoolId_Private.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NoMem
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* <b>It is user's responsibility to free the memory allocated for returned copy of tag value.</b>
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see AaConfigTagGet
* @see AaConfigTagSet
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE1 "app.example.ex1"
*
*   void exampleFunc(void)
*   {
*     u32 *value;
*     u32 valueLength = 0;
*     u32 default = 666;
*     ret = AaConfigTagGetDefault(AACONFIG_TAG_NAME_EXAMPLE1,
*                                 &value, &valueLength,
*                                 &default, sizeof(default));
*     if(ret == EAaConfigRet_Ok && value != GLO_NULL)
*     {
*       // Tag value get successful
*       ....
*       // Returned copy needs to be freed.
*       AaMemUnRef(&value);
*     }
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagGetDefault(const char* const name,
                                   void** const value,
                                   u32* const length,
                                   void* const def,
                                   const u32 dlength);


/**
********************************************************************************
*
* @brief        Registers an observer callback to given attribute tag.
*
* @param[in]    name      Pointer to NULL-terminated string containing the
*                         attribute tag name.
*
* @param[in]    callback  Pointer to an observer callback function.
*
* @return       Function returns success of operation.
*
* @par Description:
* Registers an observer callback to given attribute tag. The observer callback
* shall be called every time tag's attribute value is changed. There can be
* multiple observers per tag. If tag does not exist, a new one shall be created
* without any value.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NoMem
* - EAaConfigRet_Error
*
* @par Restrictions:
* Observers should be careful not to use any API calls which might lead to
* AaConfig tag related API calls since during observer call, tag database
* is locked by AaConfig internally thus calls to AaConfig tag API would
* lead to deadlocks.
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
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE1 "app.example.ex1"
*
*   AaConfigTagObserverExampleFunc(const char* const name,
*                                  const void* const value,
*                                  const u32 length)
*   {
*     // Some code here
*   }
*
*   void exampleFunc(void)
*   {
*     ret = AaConfigTagRegister(AACONFIG_TAG_NAME_EXAMPLE1,
*                               &AaConfigTagObserverExampleFunc);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagRegister(const char* const name,
                                 TAaConfigTagObserver* const callback);



/**
********************************************************************************
*
* @brief        Unregisters observer callback for given attribute tag.
*
* @param[in]    name      Pointer to NULL-terminated string containing the
*                         attribute tag name.
*
* @param[in]    callback  Pointer to an observer callback function.
*
* @return       Function returns success of operation.
*
* @par Description:
* Unregisters previously registered observer callback for given attribute tag.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_NotRegistered
* - EAaConfigRet_TagNotFound
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
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE1 "app.example.ex1"
*
*   AaConfigTagObserverExampleFunc(const char* const name,
*                                  const void* const value,
*                                  const u32 length)
*   {
*     // Some code here
*   }
*
*   void exampleFunc(void)
*   {
*     ret = AaConfigTagRegister(AACONFIG_TAG_NAME_EXAMPLE1,
*                               &AaConfigTagObserverExampleFunc);
*     ret = AaConfigTagUnregister(AACONFIG_TAG_NAME_EXAMPLE1,
*                               &AaConfigTagObserverExampleFunc);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagUnregister(const char* const name,
                                   TAaConfigTagObserver* const callback);


/**
********************************************************************************
*
* @brief        Deletes an existing attribute tag.
*
* @param[in]    name      Pointer to NULL-terminated string containing the
*                         attribute tag name.
*
* @return       Function returns success of operation.
*
* @par Description:
* Function deletes an existing attribute tag. Allocated memory for tag name and
* data is freed and a reference to the tag is removed from radix tree.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_TagNotFound
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
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE1 "app.example.ex1"
*
*   void exampleFunc(void)
*   {
*     ret = AaConfigTagDelete(AACONFIG_TAG_NAME_EXAMPLE1);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagDelete(const char* const name);


/**
********************************************************************************
*
* @brief        AaConfigTagPublicSet sets value (in every EE) for given attribute tag.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @param[in]    value   Pointer to attribute tag value which shall be copied.
*
* @param[in]    length  The length of the attribute tag value in bytes.
*
* @return       Function returns success of operation.
*
* @par Description:
* The AaConfigTagPublicSet() function sets value for given attribute tag.
* Tag value will be changed in every EE in own CE. If tag has
* registered observers, they will be notified. The given value shall be copied.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_PublicFailure
* - EAaConfigRet_Error
* - EAaConfigRet_NoMem
*
* @par Restrictions:
* No known restrictions.
*
* @par Usage:
* <b>This function should only be used for special purposes because no type check is executed with AaConfigTagGetxxx functions.
* Type specific PublicSet functions should be used together with type specific Get functions whenever possible.</b>
*
* @par Rationale:
* None.
*
* @par Future directions:
* None.
*
* @see AaConfigTagPublicSetU16
* @see AaConfigTagPublicSetU32
* @see AaConfigTagPublicSetString
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_ETH0_IP "sys.net.eth0.ip"
*
*   void exampleFunc(void)
*   {
*     void* value = "127.0.0.1";
*     ret = AaConfigTagPublicSet(AACONFIG_TAG_NAME_ETH0_IP, &value, sizeof(value));
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagPublicSet(const char* const name,
                                  const void* const value,
                                  const u32 length);

/**
********************************************************************************
*
* @brief        AaConfigTagPublicSetU16 sets value (in every EE) for given attribute tag of type U16.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @param[in]    value   Pointer to attribute tag value which shall be copied.
*
* @return       Function returns success of operation.
*
* @par Description:
* The AaConfigTagPublicSet() function sets value for given attribute tag.
* Tag value will be changed in every EE in own CE. If tag has
* registered observers, they will be notified. The given value shall be copied.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_PublicFailure
* - EAaConfigRet_Error
* - EAaConfigRet_NoMem
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
* @see AaConfigTagPublicSetU32
* @see AaConfigTagPublicSetString
* @see AaConfigTagGetU16
*
* @par Example:
* @code
*   #define AACONFIG_U16_TAG "aaconfig.u16.tag"
*
*   void exampleFunc(void)
*   {
*     u16 value =1;
*     ret = AaConfigTagPublicSetU16(AACONFIG_U16_TAG, value);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagPublicSetU16(const char* const name,
                                     const u16 value);

/**
********************************************************************************
*
* @brief        AaConfigTagPublicSetU32 sets value (in every EE) for given attribute tag of type U32.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @param[in]    value   Pointer to attribute tag value which shall be copied.
*
* @return       Function returns success of operation.
*
* @par Description:
* The AaConfigTagPublicSet() function sets value for given attribute tag.
* Tag value will be changed in every EE in own CE. If tag has
* registered observers, they will be notified. The given value shall be copied.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_PublicFailure
* - EAaConfigRet_Error
* - EAaConfigRet_NoMem
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
* @see AaConfigTagPublicSetU16
* @see AaConfigTagPublicSetString
* @see AaConfigTagGetU32
*
* @par Example:
* @code
*   #define AACONFIG_U32_TAG "aaconfig.u32.tag"
*
*   void exampleFunc(void)
*   {
*     u32 value =0xFFFF0001;
*     ret = AaConfigTagPublicSetU32(AACONFIG_U32_TAG, value);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagPublicSetU32(const char* const name,
                                     const u32 value);

/**
********************************************************************************
*
* @brief        AaConfigTagPublicSetString sets value (in every EE) for given attribute tag of type String.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @param[in]    value   Pointer to attribute tag value which shall be copied.
*
* @param[in]    length  The length of the attribute tag value in bytes.
*
* @return       Function returns success of operation.
*
* @par Description:
* The AaConfigTagPublicSet() function sets value for given attribute tag.
* Tag value will be changed in every EE in own CE. If tag has
* registered observers, they will be notified. The given value shall be copied.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_PublicFailure
* - EAaConfigRet_Error
* - EAaConfigRet_NoMem
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
* @see AaConfigTagPublicSetU16
* @see AaConfigTagPublicSetU32
* @see AaConfigTagGetString
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_ETH0_IP "sys.net.eth0.ip"
*
*   void exampleFunc(void)
*   {
*     void* value = "127.0.0.1";
*     ret = AaConfigTagPublicSetString(AACONFIG_TAG_NAME_ETH0_IP, &value, sizeof(value));
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagPublicSetString(const char* const name,
                                        const void* const value,
                                        const u32 length);

/**
********************************************************************************
*
* @brief        AaConfigTagPublicDelete deletes value (in every EE) for given attribute tag.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @return       Function returns success of operation.
*
* @par Description:
* The AaConfigTagPublicDelete() function deletes value for given attribute tag.
* Tag value will be deleted in every EE in own CE.
*
* @par Errors:
* - EAaConfigRet_InvalidParameter
* - EAaConfigRet_PublicFailure
* - EAaConfigRet_TagNotFound
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
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_ETH0_IP "sys.net.eth0.ip"
*
*   void exampleFunc(void)
*   {
*     ret = AaConfigTagPublicDelete(AACONFIG_TAG_NAME_ETH0_IP);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagPublicDelete(const char* const name);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_COMMON_IF_AACONFIG_TAG_H_
