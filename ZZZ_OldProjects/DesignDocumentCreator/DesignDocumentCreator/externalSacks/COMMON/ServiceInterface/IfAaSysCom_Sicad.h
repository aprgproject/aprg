/* ***************************************************************************
 * @brief  Utility functions for SIC address, Node ID (NID), CP ID (CPID)
 *         handling.
 * @module AaSysCom
 * @owner  Kai Tetzlaff
 *
 * Copyright 2014 Nokia Solutions and Networks. All rights reserved.
 * ***************************************************************************/
#ifndef IF_COMMON_AASYSCOM_SICAD_H
#define IF_COMMON_AASYSCOM_SICAD_H

#include <CcsCommon.h>
#include <TAaSysComSicad.h>

//this file is used by CCS_LITE
#ifdef CCS_NEW_IF_STRUCTURE
#include "../Definitions/IfAaSysCom_Defs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup dgAaSysComCommon AaSysCom Common
 * @ingroup dgAaSysCom
 * @{
 */

/**
 * @brief      Extract node ID from SIC address.
 *
 * @param[in]  sicAddress    Specifies the SIC address from which the node
 *                           ID is derived from.
 *
 * @return     The function returns the node ID.
 *
 * @par Description:
 * The AaSysComSicadGetNid() function derives corresponding node identifier from
 * the user-specified SIC address.
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
 * @see AaSysComSicadGet, AaSysComSicadGetCpid
 *
 * @par Example:
 *   @code
 *       TAaSysComNid nid = 0;
 *       TAaSysComSicad sicad = AaSysComSicadGet(TEST_CPID, TEST_NID);
 *       ...
 *       nid = AaSysComSicadGetNid(sicad);
 *   @endcode
 */
TAaSysComNid AaSysComSicadGetNid(const TAaSysComSicad sicAddress);

/**
 * @brief      Extract communication point ID from SIC address.
 *
 * @param[in]  sicAddress    Specifies the SIC address from which the
 *                           communication point ID is derived from.
 *
 * @return     The function returns the communication point ID.
 *
 * @par Description:
 * The AaSysComSicadGetCpid() function derives corresponding communication point
 * identifier from the user-specified SIC address.
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
 * @see AaSysComSicadGet, AaSysComSicadGetNid
 *
 * @par Example:
 *   @code
 *       TAaSysComCpid cpid = 0;
 *       TAaSysComSicad sicad = AaSysComSicadGet(TEST_CPID, TEST_NID);
 *       ...
 *       cpid = AaSysComSicadGetCpid(sicad);
 *   @endcode
 */
TAaSysComCpid AaSysComSicadGetCpid(const TAaSysComSicad sicAddress);

/**
 * @brief      Compose SIC address from communication point and node identifiers.
 *
 * @param[in]  userCpid  Communication point ID.
 *
 * @param[in]  userNid   Node ID.
 *
 * @return     The function returns the SIC address.
 *
 * @par Description:
 * The AaSysComSicadGet() function composes the SIC address from the
 * user-specified communication point and node identifiers.
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
 * @see AaSysComSicadGetNid, AaSysComSicadGetCpid
 *
 * @par Example:
 *   @code
 *       TAaSysComCpid cpid = OWN_CPID;
 *       TAaSysComNid nid = OWN_NID;
 *       TAaSysComSicad sicad = 0;
 *       ...
 *       sicad = AaSysComSicadGet(cpid, nid);
 *   @endcode
 */
TAaSysComSicad AaSysComSicadGet(const TAaSysComCpid userCpid,
                                const TAaSysComNid userNid);


/** @} end: @addtogroup dgAaSysComCommon AaSysCom Common*/

#ifdef __cplusplus
}
#endif

#endif /* IF_COMMON_AASYSCOM_SICAD_H */
