/** @file
*   @brief AaWcdmaUarfcn MCU API
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Owner: grzegorz.tobis@nokia.com $
*   $Copyright: Copyright 2016 Nokia. All rights reserved.$
*/

#ifndef _MCU_IF_AAWCDMAUARFCN_H_
#define _MCU_IF_AAWCDMAUARFCN_H_

/*----------------------- INCLUDED FILES --------------------------------------*/

#include "CcsCommon.h"
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dgAaWcdmaUarfcn AaWcdmaUarfcn API
 */

/**
 * @defgroup dgAaWcdmaUarfcnMcu AaWcdmaUarfcn MCU API
 * @ingroup  dgAaWcdmaUarfcn
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief   Returns uplink frequency of given UARFCN.
*
*   @param[in]  uarfcn UARFCN to be converted
*
*   @return
*      - Uplink frequency in kHz
*      - 0 if given UARFCN is invalid
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
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
*   @see
*
*******************************************************************************/
u32 AaWcdmaUarfcnUplinkFrequencyGet(const u32 uarfcn);

/**
*******************************************************************************
*
*   @brief   Get downlink frequency of given UARFCN.
*
*   @param[in]  uarfcn UARFCN to be converted
*
*   @return
*      - Downlink frequency in kHz
*      - 0 if given UARFCN is invalid
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
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
*   @see
*
*******************************************************************************/
u32 AaWcdmaUarfcnDownlinkFrequencyGet(const u32 uarfcn);

/**
*******************************************************************************
*
*   @brief   Get uplink UARFCN for given WCDMA band and frequency.
*
*   @param[in]  band       Used WCDMA Band
*   @param[in]  frequency  Frequency to be converted
*
*   @return
*      - Uplink UARFCN
*      - 0 if give WCDMA band is invalid, frequency is invalid or if
*        combination of WCDMA band and frequency is invalid
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
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
*   @see
*
*******************************************************************************/
u32 AaWcdmaUarfcnUplinkChannelGet(u32 band, const u32 frequency);

/**
*******************************************************************************
*
*   @brief   Get downlink UARFCN for given WCDMA band and frequency.
*
*   @param[in]  band       Used WCDMA Band
*   @param[in]  frequency  Frequency to be converted
*
*   @return
*      - Downlink UARFCN
*      - 0 if given WCDMA band is invalid, frequency is invalid or if
*        combination of WCDMA band and frequency is invalid
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
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
*   @see
*
*******************************************************************************/
u32 AaWcdmaUarfcnDownlinkChannelGet(u32 band, const u32 frequency);

/**
*******************************************************************************
*
*   @brief   Get uplink UARFCN that corresponds with given downlink UARFCN.
*
*   @param[in]  uarfcn   Downlink UARFCN
*
*   @return
*      - Uplink UARFCN
*      - 0 if given downlink UARFCN is invalid
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
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
*   @see
*
*******************************************************************************/
u32 AaWcdmaUarfcnUplinkDuplexChannelGet(const u32 uarfcn);

/**
*******************************************************************************
*
*   @brief   Get downlink UARFCN that corresponds with given uplink UARFCN.
*
*   @param[in]  uarfcn   Uplink UARFCN
*
*   @return
*      - Downlink UARFCN
*      - 0 if given uplink UARFCN is invalid
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
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
*   @see
*
*******************************************************************************/
u32 AaWcdmaUarfcnDownlinkDuplexChannelGet(const u32 uarfcn);

/**
*******************************************************************************
*
*   @brief   Get Band for Uplink UARFCN
*
*   @param[in]  uarfcn   Uplink UARFCN
*
*   @return
*      - No. of WCDMA Band
*      - 0 if given uplink UARFCN is invalid
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   According to WBTS\_APPS\_4656 (PR 34505ESPE05) the function always returns
*   Band V (5) for the overlapping UARFCNs of Band V (5) and Band VI (6).
*
*   @par Example:
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
*   @see
*
*******************************************************************************/
u32 AaWcdmaUarfcnGetBandUplink(const u32 uarfcn);

/**
*******************************************************************************
*
*   @brief   Get Band for Downlink UARFCN
*
*   @param[in]  uarfcn   Downlink UARFCN
*
*   @return
*      - No. of WCDMA Band
*      - 0 if given downlink UARFCN is invalid
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   According to WBTS\_APPS\_4656 (PR 34505ESPE05) the function always returns
*   Band V (5) for the overlapping UARFCNs of Band V (5) and Band VI (6).
*
*   @par Example:
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
*   @see
*
*******************************************************************************/
u32 AaWcdmaUarfcnGetBandDownlink(const u32 uarfcn);

/* @} */


/*----------------------- INTERNAL INTERFACES --------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*  _MCU_IF_AAWCDMAUARFCN_H_ */
