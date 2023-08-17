/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2016 Nokia Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IF_AACONFIG_TAG_H_
#define _MCU_RT_IF_AACONFIG_TAG_H_

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaConfigTagApiMcuRt AaConfigTag MCU-RT shared functions
 * @ingroup dgAaConfigTagApi
 */
/*@{*/


/**
********************************************************************************
*
* @brief        AaConfigTagReadFile reads XML file containing attribute tags.
*
* @param[in]    fileName   path and name of XML file
*
* @par Description:
* Read and parse XML file containing attribute tags.
* Attribute tags are set using AaConfigTagSet function call.
*
* @par Errors:
* No errors are defined.
*
* @par Restrictions:
* File services are not yet mapped, so physical path name has to be used.
* Only types 'u16', 'u32' and 'string' are supported.
*
* @par Usage:
* Example for attribute tag file:
* @code
* <config>
*     <tag name="ccs.service.aasyslog.startuplogsize" type="u32">1048576</tag>
*     <tag name="ccs.service.aasyslog.priority" type="u16">11</tag>
*     <tag name="ccs.service.aaconfig.rad.file.location" type="string">/rom/swconfig.txt</tag>
* </config>
* @endcode
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
*     AaConfigTagReadFile("rom/aaconfig.xml");
* @endcode
*
*******************************************************************************/
void AaConfigTagReadFile(const char *const fileName);

/**
********************************************************************************
*
* @brief        AaConfigTagPersistentSetU16 writes unsigned 16bit value for given
*               attribute tag to file.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @param[in]    value   Unsigned 16bit attribute tag value which shall be copied.
*
* @return       Function returns success of operation.
*
* @par Description:
* Attribute tag, value and type are written to the file which name is given in attribute tag
* "ccs.service.aaconfig.pcf.file.location".
* The file can be read with function AaConfigTagReadFile() during next startup.
* The value is also set via AaConfigTagPublicSetU16() function.
*
* @par Errors:
* - EAaConfigRet_NoMem
* - EAaConfigRet_Error
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
* @see AaConfigTagReadFile
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE2 "app.example.ex2"
*
*   void exampleFunc(void)
*   {
*     u32 value = 0x0666;
*     ret = AaConfigTagPersistentSetU16(AACONFIG_TAG_NAME_EXAMPLE2, value);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagPersistentSetU16(const char* const name, const u16 value);

/**
********************************************************************************
*
* @brief        AaConfigTagPersistentSetU32 writes unsigned 32bit value for given
*               attribute tag to file.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @param[in]    value   Unsigned 32bit attribute tag value which shall be copied.
*
* @return       Function returns success of operation.
*
* @par Description:
* Attribute tag, value and type are written to the file which name is given in attribute tag
* "ccs.service.aaconfig.pcf.file.location".
* The file can be read with function AaConfigTagReadFile() during next startup.
* The value is also set via AaConfigTagPublicSetU32() function.
*
* @par Errors:
* - EAaConfigRet_NoMem
* - EAaConfigRet_Error
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
* @see AaConfigTagReadFile
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_EXAMPLE1 "app.example.ex1"
*
*   void exampleFunc(void)
*   {
*     u32 value = 0x06660666;
*     ret = AaConfigTagPersistentSetU32(AACONFIG_TAG_NAME_EXAMPLE1, value);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagPersistentSetU32(const char* const name, const u32 value);

/**
********************************************************************************
*
* @brief        AaConfigTagPersistentSetString writes string value for given
*               attribute tag to file.
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
* Attribute tag, value and type are written to the file which name is given in attribute tag
* "ccs.service.aaconfig.pcf.file.location". The value must be NULL-terminated string.
* The file can be read with function AaConfigTagReadFile() during next startup.
* The value is also set via AaConfigTagPublicSetString() function.
*
* @par Errors:
* - EAaConfigRet_NoMem
* - EAaConfigRet_Error
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
* @see AaConfigTagPublicSetString
* @see AaConfigTagReadFile
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_ETH0_IP "sys.net.eth0.ip"
*
*   void exampleFunc(void)
*   {
*     void* value = "127.0.0.1";
*     ret = AaConfigTagPersistentSetString(AACONFIG_TAG_NAME_ETH0_IP, &value);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagPersistentSetString(const char* const name, const void* const value);

/**
********************************************************************************
*
* @brief        AaConfigTagPersistentDelete deletes given attribute tag from file.
*
* @param[in]    name    Pointer to NULL-terminated string containing the
*                       attribute tag name.
*
* @return       Function returns success of operation.
*
* @par Description:
* Attribute tag is deleted from the file which name is given in attribute tag
* "ccs.service.aaconfig.pcf.file.location". The value must be NULL-terminated string.
* The attribute tag is deleted via AaConfigTagPublicDelete().
* If this was the last attribute tag in the file it will be deleted from file system.
*
* @par Errors:
* - EAaConfigRet_Error
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
* @see AaConfigTagPublicDelete
*
* @par Example:
* @code
*   #define AACONFIG_TAG_NAME_ETH0_IP "sys.net.eth0.ip"
*
*   void exampleFunc(void)
*   {
*     ret = AaConfigTagPersistentDelete(AACONFIG_TAG_NAME_ETH0_IP);
*   }
* @endcode
*
*******************************************************************************/
EAaConfigRet AaConfigTagPersistentDelete(const char* const name);


/**
********************************************************************************
*
* @brief        AaConfigTagDump dumps current attribute tags to AaSysLog.
*
* @par Description:
* Function AaConfigTagDump() is intended mainly for debugging purpose.
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
*
* @par Example:
* @code
*     ret = AaConfigTagDump();
* @endcode
*
*******************************************************************************/
void AaConfigTagDump(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif  //_MCU_RT_IF_AACONFIG_TAG_H_
