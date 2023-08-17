/**
*******************************************************************************
* @file
*
* @brief
*
* @copyright 2016 Nokia. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_EIF_AA_SYSCOM_RET_VAL_H
#define _RT_DSP_EIF_AA_SYSCOM_RET_VAL_H

/*----------------------- DOXYGEN GROUPS --------------------------------------*/
/**
* @addtogroup dgUpCcs U-Plane specific CC&S API
* @{
*/

/**
* @addtogroup dgUpCcsAaSysCom AaSysCom API
* @{
*/

/**
* @addtogroup dgUpCcsRtDspAaSysCom AaSysCom API for RT and OSECK DSP nodes
* @{
*/

typedef enum EIfAaSysComRetVal
{
    EIfAaSysComRetVal_NoError   = 0,
    EIfAaSysComRetVal_Error     = 1
} EIfAaSysComRetVal;

#endif  /* _RT_DSP_EIF_AA_SYSCOM_RET_VAL_H */

/**
*******************************************************************************
* @enum EIfAaSysComRetVal
*
*
* Description : Enumeration for MessageRouter function return values.
*
* Reference   :
*
* @param NoError:       Function returns no error
* @param Error:         Function returns error
*
*
*
*
*******************************************************************************/

/** @} */   /* dgUpCcsRtDspAaSysCom */
/** @} */   /* dgUpCcsAaSysCom */
/** @} */   /* dgUpCcs */
