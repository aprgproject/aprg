/**
*******************************************************************************
* Copyright 2015,2019 Nokia. All rights reserved.
*******************************************************************************/
#ifndef IF_COMMON_AASYSCOMGW_DEFS_H
#define IF_COMMON_AASYSCOMGW_DEFS_H

#include <glo_def.h>
#include <CcsCommon.h>
#include <EStatus.h>

 #ifdef __cplusplus
 extern "C" {
 #endif

/**
 * @addtogroup dgAaSysComGwCommon AaSysComGw Common
 * @ingroup dgAaSysCom
 * @{
 */

/** @name interface types
 * @{
 */
/** @brief lenght of the TIpv4AddressStr string (including null-terminator).*/
#define AASYSCOM_GW_IPV4_ADDRESS_STR_LEN 16

/** @brief Maximal length of the IPv4 or IPv6 address string (including null-terminator).
*   @par Restrictions: No restrictions.
*/
#define AASYSCOM_GW_IP_ADDRESS_MAX_STR_LEN 48

/** @brief IPv4 address in dotted decimal format, zero terminated (and, if
 *        necessary, zero padded on the right). */
typedef u8 TAaSysComGwIpv4AddressStr_deprecated[AASYSCOM_GW_IPV4_ADDRESS_STR_LEN];
typedef TAaSysComGwIpv4AddressStr_deprecated TAaSysComGwIpv4AddressStr CCS_DEPRECATED("Use TAaSysComGwIpAddressStr instead.");

/** @brief IPv4 or IPv6 address string, zero terminated (and, if
 *        necessary, zero padded on the right). */
typedef u8 TAaSysComGwIpAddressStr[AASYSCOM_GW_IP_ADDRESS_MAX_STR_LEN];

/** @brief Port number UDP/UDPCP */
typedef u32 TAaSysComGwPortNum;

/** @brief IP address and port information type used in AaSysCom Gw */
typedef struct SAaSysComGwIpAddress_deprecated
{
  TAaSysComGwIpv4AddressStr_deprecated address; /**< Ipv4 address string in dotted decimal format */
  TAaSysComGwPortNum port;           /**< port number */
} SAaSysComGwIpAddress_deprecated;
typedef SAaSysComGwIpAddress_deprecated SAaSysComGwIpAddress CCS_DEPRECATED("Use SAaSysComGwIpAddressExt instead.");

/** @brief Version of IP protocol used in AaSysCom Gw
 *  @par Restrictions: CC&S-DSP does not support IPv6.
 */
typedef enum EAaSysComGwIpVer{
    EAaSysComGwIpVer_Unknown    =  0, /**< unknown version */
    EAaSysComGwIpVer_4          =  1, /**< IP version 4  */
    EAaSysComGwIpVer_6          =  2, /**< IP version 6  */
    EAaSysComGwIpVer_NotValid   =  3  /**< Not valid version */
} EAaSysComGwIpVer;

/** @brief Extended IP address and port information type used in AaSysCom Gw */
typedef struct SAaSysComGwIpAddressExt
{
  TAaSysComGwIpAddressStr   address;    /**< IP address string */
  TAaSysComGwPortNum        port;       /**< port number */
  EAaSysComGwIpVer          ipVersion;  /**< IP Version */
} SAaSysComGwIpAddressExt;

/** @} */

/** @} end: dgAaSysComGwCommon AaSysComGw Common*/

 #ifdef __cplusplus
 }
 #endif

#endif /* IF_COMMON_AASYSCOMGW_DEFS_H */
