/**
*******************************************************************************
* @file
*
* @brief
*
* @copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_STIME_H
#define _RT_DSP_STIME_H

#include "TFrame.h"
#include "TSlot.h"
#include "TChip.h"

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaSysTime AaSysTime API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaSysTime AaSysTime API for RT and OSECK DSP nodes
* @{
*/

/**
*******************************************************************************
* @struct STime
*
* Time structure for representing time in frames, slots, and chips.
* @param frame  Frame number
* @param slot   Slot number
* @param chip   Chip number
********************************************************************************/
struct STime
{
  TFrame    frame;
  TSlot     slot;
  TChip     chip;
};

typedef struct STime STime;

/** @} */   /* dgUpCcsRtDspAaSysTime*/
/** @} */   /* dgUpCcsAaSysTime */
/** @} */   /* dgUpCcs */

#endif  /* _RT_DSP_STIME_H */
