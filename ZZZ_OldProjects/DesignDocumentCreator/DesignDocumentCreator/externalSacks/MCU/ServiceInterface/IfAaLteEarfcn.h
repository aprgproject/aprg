/** @file
*   @brief AaLteEarfcn MCU API
*
*   $HeadURL$
*   $LastChangedRevision$
*   $LastChangedDate$
*   $Author$
*   $Owner: grzegorz.tobis@nokia.com $
*   $Copyright: Copyright 2016 Nokia. All rights reserved. $
*/

#ifndef _MCU_IF_AALTEEARFCN_H_
#define _MCU_IF_AALTEEARFCN_H_

#include "CcsCommon.h"
#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup dgAaLteEarfcn AaLteEarfcn API
 */


/**
 * @defgroup dgAaLteEarfcnMcu AaLteEarfcn MCU API
 * @ingroup  dgAaLteEarfcn
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief   Get uplink frequency for given EARFCN.
*
*   @param[in]  earfcn EARFCN to be converted
*
*   @return
*      - Uplink frequency in kHz
*      - 0 if given EARFCN is invalid
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
*
*   u32 earfcn;
*   u32 freqUl;
*
*   earfcn = 23100;
*
*   if ( 0 == (freqUl = AaLteEarfcnUplinkFrequencyGet(earfcn)) ) {
*       // ERROR
*   }
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
*******************************************************************************/
u32 AaLteEarfcnUplinkFrequencyGet(const u32 earfcn);


/**
*******************************************************************************
*
*   @brief   Get downlink frequency for given EARFCN.
*
*   @param[in]  earfcn EARFCN to be converted
*
*   @return
*      - Downlink frequency in kHz
*      - 0 if given EARFCN is invalid
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
*
*   u32 earfcn;
*   u32 freqDl;
*
*   earfcn = 6149;
*
*   if ( 0 == (freqDl = AaLteEarfcnDownlinkFrequencyGet(earfcn)) ) {
*       // ERROR
*   }
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
*******************************************************************************/
u32 AaLteEarfcnDownlinkFrequencyGet(const u32 earfcn);


/**
*******************************************************************************
*
*   @brief    Get uplink EARFCN for given E-UTRA band and frequency.
*
*   @param[in]  band       Used E-UTRA Band
*   @param[in]  frequency  Frequency to be converted
*
*   @return
*      - Uplink EARFCN
*      - -1 if given E-UTRA band is invalid, frequency is invalid or if
*        combination of E-UTRA band and frequency is invalid
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
*
*   u32 band;
*   u32 freqUl;
*   i32 earfcn;
*
*   band = 43;
*   freqUl = 3690000;
*
*   if ( -1 == (earfcn = AaLteEarfcnUplinkChannelGet(band, freqUl)) ) {
*       // ERROR
*   }
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
*******************************************************************************/
i32 AaLteEarfcnUplinkChannelGet(u32 band, const u32 frequency);


/**
*******************************************************************************
*
*   @brief   Get downlink EARFCN for given E-UTRA band and frequency.
*
*   @param[in]  band       Used E-UTRA Band
*   @param[in]  frequency  Frequency to be converted
*
*
*   @return
*      - Downlink EARFCN
*      - -1 if given E-UTRA band is invalid, frequency is invalid or if
*        combination of E-UTRA band and frequency is invalid
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
*
*   u32 band;
*   u32 freqDl;
*   i32 earfcn;
*
*   band = 18;
*   freqDl = 870300;
*
*   if ( -1 == (earfcn = AaLteEarfcnDownlinkChannelGet(band, freqDl)) ) {
*       // ERROR
*   }
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
*******************************************************************************/
i32 AaLteEarfcnDownlinkChannelGet(u32 band, const u32 frequency);


/**
*******************************************************************************
*
*   @brief   Get uplink EARFCN that corresponds with given downlink EARFCN.
*
*   @param[in]  earfcn   Downlink EARFCN
*
*   @return
*      - Uplink EARFCN
*      - -1 if given downlink EARFCN is invalid
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
*
*   i32 earfcnUl;
*   u32 earfcnDl;
*
*   earfcnDl = 6077;
*
*   if ( -1 == (earfcnUl = AaLteEarfcnUplinkDuplexChannelGet(earfcnDl)) ) {
*       // ERROR
*   }
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
*******************************************************************************/
i32 AaLteEarfcnUplinkDuplexChannelGet(const u32 earfcn);


/**
*******************************************************************************
*
*   @brief   Get downlink EARFCN that corresponds with given uplink EARFCN.
*
*   @param[in]  earfcn   Uplink EARFCN
*
*   @return
*      - Downlink EARFCN
*      - -1 if given downlink EARFCN is invalid
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
*
*   u32 earfcnUl;
*   i32 earfcnDl;
*
*   earfcnUl = 45700;
*
*   if ( -1 == (earfcnDl = AaLteEarfcnDownlinkDuplexChannelGet(earfcnUl)) ) {
*       // ERROR
*   }
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
*******************************************************************************/
i32 AaLteEarfcnDownlinkDuplexChannelGet(const u32 earfcn);


/**
*******************************************************************************
*
*   @brief   Get Band for Uplink EARFCN
*
*   @param[in]  earfcn   Uplink EARFCN
*
*   @return
*      - No. of E-UTRA Band
*      - 0 if given uplink EARFCN is invalid
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
*
*   u32 earfcn;
*   i32 band;
*
*   earfcn = 23730;
*
*   if ( -1 == (band = AaLteEarfcnGetBandUplink(earfcn)) ) {
*       // ERROR
*   }
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
*******************************************************************************/
i32 AaLteEarfcnGetBandUplink(const u32 earfcn);


/**
*******************************************************************************
*
*   @brief   Get Band for Downlink EARFCN
*
*   @param[in]  earfcn   Downlink EARFCN
*
*   @return
*      - No. of E-UTRA Band
*      - 0 if given downlink EARFCN is invalid
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
*
*   u32 earfcn;
*   i32 band;
*
*   earfcn = 2399;
*
*   if ( -1 == (band = AaLteEarfcnGetBandDownlink(earfcn)) ) {
*       // ERROR
*   }
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
*******************************************************************************/
i32 AaLteEarfcnGetBandDownlink(const u32 earfcn);


/* @} */


/*----------------------- INTERNAL INTERFACES --------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*  _MCU_IF_AALTEEARFCN_H_ */

