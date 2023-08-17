/* ****************************************************************************
 * @brief  AaSysCom interface NMAP header file.
 * @module AaSysCom
 * @owner  Vedran Cundekovic
 *
 * Copyright 2014 Nokia Solutions and Networks. All rights reserved.
 * ****************************************************************************/

#ifndef IF_COMMON_AASYSCOMNMAP_H
#define IF_COMMON_AASYSCOMNMAP_H
#include <CcsCommon.h>


/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
* @addtogroup dgAaSysComNmap Legacy NMAP interworking API
* @ingroup  dgAaSysComCommon
* @{
*
* Provides services for address convertion between SICv1 and
* legacy NMAP address.
*/

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>
#include <TMsgHeaderTypes.h> /* for TBoard, TCpu and TTask types */
#include <TAaSysComSicad.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/*----------------------- PUBLIC INTERFACES ----------------------------------*/

/**
********************************************************************************
*
* @brief        Get the address based on board, cpu and task id used in NMAP.
*
* @param[in]    board   Specifies the NMAP-board identifier.
*
* @param[in]    cpu     Specifies the NMAP-cpu identifier.
*
* @param[in]    task    Specifies the NMAP-task identifier.
*
* @return     The function returns the SIC address.
*
* @par Description:
* The AaSysComNmapGetSicad() function composes the SIC address from the
* user-specified NMAP identifiers.
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
* AaSysComNmapGetBoard, AaSysComNmapGetCpu, AaSysComNmapGetTask
*
* @par Example:
*   @code
*       TAaSysComSicad myAddr = AaSysComNmapGetSicad(myBoard, myCpu, myTask);
*   @endcode
*
*******************************************************************************/
TAaSysComSicad AaSysComNmapGetSicad(const TBoard board,
                                    const TCpu cpu,
                                    const TTask task);


/**
********************************************************************************
*
* @deprecated This is an obsolete version of AaSysComNmapGetSicad. DO NOT USE!
*
* @par Restrictions:
* Do NOT use this function, this will be removed soon!
*
* @see AaSysComNmapGetSicad
*
*******************************************************************************/
TAaSysComSicad AaSysComNmapGetSicAddress(const TBoard board,
                                         const TCpu cpu,
                                         const TTask task);


/**
********************************************************************************
*
* @brief        Get the board identifier used in NMAP.
*
* @param[in]  sicAddress    Specifies the address from which the NMAP board
*                                               identifier is derived from.
*
* @return     The function returns the board identifier.
*
* @par Description:
* The AaSysComNmapGetBoard() function derives corresponding NMAP-board
* identifier from the user-specified address.
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
* AaSysComNmapGetSicAddress
*
* @par Example:
*   @code
*       TBoard board = AaSysComNmapGetBoard(sicAddr);
*   @endcode
*
*******************************************************************************/
TBoard AaSysComNmapGetBoard(const TAaSysComSicad sicAddress);


/**
********************************************************************************
*
* @brief        Get the cpu identifier used in NMAP.
*
* @param[in]  sicAddress    Specifies the address from which the NMAP cpu
*                                               identifier is derived from.
*
* @return     The function returns the cpu identifier.
*
* @par Description:
* The AaSysComNmapGetCpu() function derives corresponding NMAP-cpu identifier
* from the user-specified address.
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
* AaSysComNmapGetSicAddress
*
* @par Example:
*   @code
*       TCpu cpu = AaSysComNmapGetCpu(sicAddr);
*   @endcode
*
*******************************************************************************/
TCpu AaSysComNmapGetCpu(const TAaSysComSicad sicAddress);


/**
********************************************************************************
*
* @brief        Get the task identifier used in NMAP.
*
* @param[in]  sicAddress    Specifies the address from which the NMAP task
*                                               identifier is derived from.
*
* @return     The function returns the task identifier.
*
* @par Description:
* The AaSysComNmapGetTask() function derives corresponding NMAP-task identifier
* from the user-specified address.
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
* AaSysComNmapGetSicAddress
*
* @par Example:
*   @code
*       TTask task = AaSysComNmapGetTask(sicAddr);
*   @endcode
*
*******************************************************************************/
TTask AaSysComNmapGetTask(const TAaSysComSicad sicAddress);

/** @} end: @addtogroup dgAaSysComNmap Legacy NMAP interworking API */

#ifdef __cplusplus
}
#endif


#endif /* IF_COMMON_AASYSCOMNMAP_H */
