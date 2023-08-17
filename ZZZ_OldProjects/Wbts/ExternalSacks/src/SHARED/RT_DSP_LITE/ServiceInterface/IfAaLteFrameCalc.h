/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaLteFrameCalc service API header file
* @module                AaLteFrameCalc
* @owner                 Vladimir Cundekovic 
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _RT_DSP_IFAALTEFRAMECALC_H
#define _RT_DSP_IFAALTEFRAMECALC_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
*@defgroup dgAaLteFrameCalc LTE Frame Calculation service (AaLteFrameCalc)
*@ingroup dgCommonApplicationUtilitiesSw
*
* Common Computer and Support SW LTE Frame Calculation service.
*
* SW LTE Frame Calculation service offers functionalities for:
* timing addition; timing subtraction; timing distance calculation; 
* timing update; timing conversion; timing comparison; timing normalization; 
* timing base changing; timing check; timing offset calculation; 
* absolute time addition; absolute time subtraction and absolute time 
* conversion. 
* 
*/

/**
*@defgroup dgAaLteFrameCalcApi API
*@ingroup dgAaLteFrameCalc
*
* Application Programming Interface.
* 
* API specification (current): <TBD>
*
* CC&S Wiki: <TBD>
* 
*@{*/

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <glo_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PRIVATE DECLARATIONS -------------------------------*/

/**
 *  @brief LTE Frame Calc specific private constants
 *
 *  Used in macro AALTEFRAMECALC_TOTAL_OFFSET_BTUS_GET. This definition must be 
 *  changed if the Tcell resolution is changed (1024 => 10 bits)
 */
#define AALTEFRAMECALC_TCELL_UNIT_BITS    10 

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @brief Type definition for frame */
typedef i32 TAaLteFrameCalcFrame;

/** @brief Type definition for slot */
typedef i32 TAaLteFrameCalcSlot;

/** @brief Type definition for BTU */
typedef i32 TAaLteFrameCalcBtu;

/** @brief Type definition for absolute time (unit: ms or us) */
typedef i32 TAaLteFrameCalcAbsTime;

/** @brief Type definition for Tcell */
typedef u32 TAaLteFrameCalcTcell;

/** @brief Enumerations for counter mode 
 *
 * Indicate the mode of the used frame counter (BFN or CFN)
 */
typedef enum _EAaLteFrameCalcCounterMode  
{
    EAaLteFrameCalcCounterMode_Bfn = 0,/**< Counter mode BFN */
    EAaLteFrameCalcCounterMode_Cfn,    /**< Counter mode CFN */
    EAaLteFrameCalcCounterMode_NbrOf   /**< Number of available counter modes */
} EAaLteFrameCalcCounterMode;

/** @brief Enumerations for the function return values */
typedef enum _EAaLteFrameCalcRetVal
{
    EAaLteFrameCalcRetVal_NoError = 0,      /**< Enum. for the function return 
                                             *   value, when no error. */ 
    EAaLteFrameCalcRetVal_Error,            /**< Enum. for the function return 
                                             *   value, when an error exists. */         
    EAaLteFrameCalcRetVal_InvalidParameter, /**< Enum. for the function return 
                                             *   value  when invalid input 
                                             *   parameter */
    EAaLteFrameCalcRetVal_NbrOf             /**< The number of available return 
                                             *   values */
} EAaLteFrameCalcRetVal;

/** @brief Enumerations for time unit
 *
 * Indicate which time unit to use (ms or us)
 */
typedef enum _EAaLteFrameCalcTimeUnit
{
    EAaLteFrameCalcTimeUnit_Ms = 0, /**< Enum. for ms */
    EAaLteFrameCalcTimeUnit_Us,     /**< Enum. for us */
    EAaLteFrameCalcTimeUnit_NbrOf   /**< Number of available units */
} EAaLteFrameCalcTimeUnit;

/** @brief Type definition for offset */
typedef struct SAaLteFrameCalcOffset 
{
    TAaLteFrameCalcFrame   frame; /**< Offset frame */  
    TAaLteFrameCalcTcell   tcell; /**< Offset Tcell */ 
    TAaLteFrameCalcBtu     btu;   /**< Offset BTU */ 
} TAaLteFrameCalcOffset;

/** @brief Type definition for time */
typedef struct SAaLteFrameCalcTime 
{
    TAaLteFrameCalcFrame   frame; /**< Frame */
    TAaLteFrameCalcSlot    slot;  /**< Slot */
    TAaLteFrameCalcBtu     btu;   /**< BTU */
} TAaLteFrameCalcTime;

/**
 *  @brief LTE Frame Calc specific constants
 */
#define AALTEFRAMECALC_MAX_BFN           4095   /**< BFN max value */
#define AALTEFRAMECALC_BFN_MASK          0xFFF  /**< BFN mask */
#define AALTEFRAMECALC_MAX_CFN           255    /**< CFN max value */
#define AALTEFRAMECALC_CFN_MASK          0xFF   /**< CFN mask */
#define AALTEFRAMECALC_BTUS_PER_SLOT     15360  /**< Number of BTUs per slot */
#define AALTEFRAMECALC_SLOTS_PER_FRAME   20     /**< Number of slots per frame*/
#define AALTEFRAMECALC_BTUS_PER_FRAME    307200 /**< Number of BTUs per frame */
#define AALTEFRAMECALC_TCELL_UNIT_BTUS   1024   /**< Tcell resolution in BTUs */
#define AALTEFRAMECALC_FRAME_DURATION_US 10000  /**< Frame duration in 
                                                 *   microseconds */
#define AALTEFRAMECALC_FRAME_DURATION_MS 10     /**< Frame duration in 
                                                 *   milliseconds */
#define AALTEFRAMECALC_SLOT_DURATION_US  500    /**< Slot duration in 
                                                 *   microseconds */

/*----------------------- PUBLIC INTERFACES ----------------------------------*/


/**
 * @defgroup dgAaLteFrameCalcApiCommon AaLteFrameCalc COMMON API
 * @ingroup  AaLteFrameCalc
 */

/* @{ */

/**
********************************************************************************
*
*   @brief    Generic macro to check if the input frame number is valid.
*
*
*   @param[in]     frame      The frame number to be checked.
*   @param[in]     maxValue   Maximum allowed value for the frame number.
* 
*   @return        Truth value if the frame number is within the desired range.
*
*   @par Description:
*   This macro check if the input frame number is within the desired value
*   range. The max value is given as a parameter and the min value is zero.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The maxValue must have a positive value.
*
*   @par Example:
*
*   @code
* 
*   TBoolean retval;
*   TAaLteFrameCalcFrame frame;   
*
*   retval = AALTEFRAMECALC_FRAME_CHECK(frame, 4095);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/

#define AALTEFRAMECALC_FRAME_CHECK(frame, maxValue) \
    (!(((frame) < 0) || ((frame) > (maxValue))))

/**
********************************************************************************
*
*   @brief    Function to check if the input frame number is valid.
*
*
*   @param[in]     ref        Reference frame number.
*   @param[in]     inputMode  Parameter to indicate the mode of the used frame 
*                             counter (BFN or CFN).
* 
*   @return        Truth value if the frame number is OK.
*
*   @par Description:
*   This function check if the input frame number is within the allowed value
*   range. For BFN the allowed value range is 0-4095. For CFN the allowed
*   value range is 0-255.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
* 
*   TBoolean result;
*   TAaLteFrameCalcFrame ref;   
*   retval = AaLteFrameCalcFrameCheck(ref, EAaLteFrameCalcCounterMode_Bfn);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern TBoolean AaLteFrameCalcFrameCheck(
    const TAaLteFrameCalcFrame ref,
    const EAaLteFrameCalcCounterMode inputMode);

/**
********************************************************************************
*
*   @brief    Generic macro to calculate distance between frame numbers.
*
*
*   @param[in]   ref    Reference frame number.
*   @param[in]   frame  Current frame number.
*   @param[in]   mask   Mask for the counters.

* 
*   @return      Distance between the two input frame numbers.
*
*   @par Description:
*   This macro calculates the distance between two input frame numbers.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The macro assumes that the reference frame number is earlier than the 
*   current frame number. The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, frame, frameDist;      
*
*   frameDist = AALTEFRAMECALC_FRAME_DIST_GET (ref, frame, 4095);
*
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
#define AALTEFRAMECALC_FRAME_DIST_GET(ref, frame, mask) \
    ((((mask) + 1) + (frame) - (ref)) & (mask))
  
/**
********************************************************************************
*
*   @brief    Function to calculate the distance between frame numbers.
*
*
*   @param[in]   ref        Reference frame number.
*   @param[in]   frame      Current frame number.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
* 
*   @return      Distance between the frame numbers.
*
*   @par Description:
*   None
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The function assumes that the reference frame number is earlier than the 
*   current frame number. The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, frame, result;      
*
*   result = AaLteFrameCalcFrameDistGet(ref, frame, 
*                                       EAaLteFrameCalcCounterMode_Bfn);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern TAaLteFrameCalcFrame AaLteFrameCalcFrameDistGet(
    const TAaLteFrameCalcFrame ref,
    const TAaLteFrameCalcFrame frame, 
    const EAaLteFrameCalcCounterMode inputMode);

/**
********************************************************************************
*
*   @brief    Generic macro to sum frame numbers.
*
*
*   @param[in]   ref      Reference frame number.
*   @param[in]   frame    Number of frames to be summed.
*   @param[in]   mask     Mask for the counters..
* 
*   @return      The sum of the two input frame numbers.
*
*   @par Description:
*   This function sums the two input frame numbers. It takes care of possible 
*   wrap-around of the frame counter. 
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.  
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, frame, result;  
*
*   result = AALTEFRAMECALC_FRAME_ADD(ref, frame, 4095);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
#define AALTEFRAMECALC_FRAME_ADD(ref, frame, mask) \
    (((ref) + (frame)) & (mask))

/**
********************************************************************************
*
*   @brief    Function to add frames to reference timing.
*
*
*   @param[in]   refPtr     Pointer for the reference timing values.
*   @param[in]   frame      Number of frames to be summed.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
*   @param[out]  resultPtr  Pointer for the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function accumulates frames to the reference timing including counters
*   for BTUs, slots and frames. It takes care of possible wrap-around of frame 
*   counter.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The value range for the given slot reference timing is 0?9.
*   The value range for the given BTU reference timing is 0?5359.
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   EAaLteFrameCalcRetVal retVal;
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcFrame frame;  
*
*   retVal = AaLteFrameCalcFrameAdd(&ref, frame, EAaLteFrameCalcCounterMode_Bfn,
*                                   &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcFrameAdd(
    const TAaLteFrameCalcTime *refPtr, 
    const TAaLteFrameCalcFrame frame, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Generic macro to subtract frame numbers.
*
*
*   @param[in]   ref      Reference frame number.
*   @param[in]   frame    Number of frames to be subtracted.
*   @param[in]   mask     Mask for the counters..
* 
*   @return      Subtraction of the two input frame numbers.
*
*   @par Description:
*   This function subtract the two input frame numbers. It takes care of 
*   possible wrap-around of the frame counter. 
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.  
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, frame, result;  
*
*   result = AALTEFRAMECALC_FRAME_SUBTRACT(ref, frame, 4095);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
#define AALTEFRAMECALC_FRAME_SUBTRACT(ref, frame, mask) \
    (((ref) - (frame)) & (mask))

/**
********************************************************************************
*
*   @brief    Function to subtract frames from reference timing.
*
*
*   @param[in]   refPtr     Pointer for the reference timing values.
*   @param[in]   frame      Number of frames to be subtracted.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
*   @param[out]  resultPtr  Pointer for the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function subtracts frames from the reference timing including counters
*   for BTUs, slots and frames. It takes care of wrap-around of the frame
*   counter.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The value range for the given slot reference timing is 0?9.
*   The value range for the given BTU reference timing is 0?5359.
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   EAaLteFrameCalcRetVal retVal;
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcFrame frame;  
*
*   retVal = AaLteFrameCalcFrameSubtract(&ref, frame, 
*                EAaLteFrameCalcCounterMode_Bfn, &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcFrameSubtract(
    const TAaLteFrameCalcTime *refPtr,
    const TAaLteFrameCalcFrame frame, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Macro to calculate the next frame number.
*
*
*   @param[in]   ref    Reference frame number.
*   @param[in]   mask   Mask for the counter.
* 
*   @return      Next frame number.
*
*   @par Description:
*   This macro adds one unit to the frame counter and takes care of possible 
*   wrap-around of the frame counter.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, result;  
*
*   result = AALTEFRAMECALC_FRAME_NEXT_GET(ref, 4095);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
#define AALTEFRAMECALC_FRAME_NEXT_GET(ref, mask) \
    (AALTEFRAMECALC_FRAME_ADD((ref),1,(mask)))

/**
********************************************************************************
*
*   @brief    Function to calculate the next frame number.
*
*
*   @param[in]   ref        Reference frame number.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
* 
*   @return      Next frame number.
*
*   @par Description:
*   This function adds one unit to the frame counter and takes care of possible 
*   wrap-around of the frame counter.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, result;  
*
*   result = AaLteFrameCalcFrameNextGet(ref, EAaLteFrameCalcCounterMode_Bfn);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern TAaLteFrameCalcFrame AaLteFrameCalcFrameNextGet(
    const TAaLteFrameCalcFrame ref,
    const EAaLteFrameCalcCounterMode inputMode);

/**
********************************************************************************
*
*   @brief    Macro to calculate the previous frame number. 
*
*
*   @param[in]   ref   Reference frame number.
*   @param[in]   mask  Mask for the counters..
* 
*   @return      Previous frame number.
*
*   @par Description:
*   This macro subtracts one unit to the frame counter and takes care of 
*   possible wrap-around of the frame counter.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, result;  
*
*   result = AALTEFRAMECALC_FRAME_PREV_GET(ref, 4095);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
#define AALTEFRAMECALC_FRAME_PREV_GET(ref, mask) \
    (AALTEFRAMECALC_FRAME_SUBTRACT((ref),1,(mask)))

/**
********************************************************************************
*
*   @brief    Function to calculate the previous frame number.
*
*
*   @param[in]   ref        Reference frame number.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
* 
*   @return      Previous frame number.
*
*   @par Description:
*   This function subtracts one unit from the frame counter and takes care of 
*   possible wrap-around of the frame counter.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, result;  
*
*   result = AaLteFrameCalcFramePrevGet(ref, EAaLteFrameCalcCounterMode_Bfn);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/

extern TAaLteFrameCalcFrame AaLteFrameCalcFramePrevGet(
    const TAaLteFrameCalcFrame ref,
    const EAaLteFrameCalcCounterMode inputMode);

/**
********************************************************************************
*
*   @brief    Macro to calculates total number of BTUs from frame timing. 
*
*
*   @param[in]   frame  Number of frames.
*   @param[in]   slot   Number of slots.
*   @param[in]   btu    Number of BTUs.
* 
*   @return      Number of BTUs during the input timing.
*
*   @par Description:
*   This macro calculates total number of BTUs from frame timing (frames, slots
*   and BTUs).
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcBtu result;  
*
*   result = AALTEFRAMECALC_TOTAL_BTUS_GET(712, 9, 1280);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
#define AALTEFRAMECALC_TOTAL_BTUS_GET(frame, slot, btu) \
    ((btu) + AALTEFRAMECALC_BTUS_PER_SLOT *             \
    ((slot) + AALTEFRAMECALC_SLOTS_PER_FRAME * (frame)))

/**
********************************************************************************
*
*   @brief    Function to calculates total number of BTUs from frame timing. 
*
*
*   @param[in]   refPtr     Pointer for the reference timing.
*   @param[out]  resultPtr  Pointer for the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function calculates total number of BTUs from frame timing (frames, 
*   slots and BTUs).
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref;
*   TAaLteFrameCalcBtu result;
*   EAaLteFrameCalcRetVal retVal;  
*
*   retVal = AaLteFrameCalcTotalBTUsGet(&ref, &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcTotalBTUsGet(
    const TAaLteFrameCalcTime *refPtr,
    TAaLteFrameCalcBtu *resultPtr);
    
/**
********************************************************************************
*
*   @brief    Macro to calculate the number of slots from frame timing.
*
*
*   @param[in]   frame  Number of frames.
*   @param[out]  slot   Number of slots.
* 
*   @return      Number of slots during the input timing.
*
*   @par Description:
*   This macro calculates total number of slots from frame timing (frames 
*   and slots). 
*   
*   @par Errors:
*   [None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcSlot result;
*
*   result = AALTEFRAMECALC_TOTAL_SLOTS_GET(712, 9);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
#define AALTEFRAMECALC_TOTAL_SLOTS_GET(frame, slot) \
    ((slot) + AALTEFRAMECALC_SLOTS_PER_FRAME * (frame))

/**
********************************************************************************
*
*   @brief    Function to calculates the number of slots from frame timing.
*
*
*   @param[in]   refPtr     Pointer for the reference timing.
*   @param[out]  resultPtr  Pointer for the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function calculates total number of slots from frame timing (frames 
*   and slots). Note that BTUs in the reference timing is not taken into 
*   account. 
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref;
*   TAaLteFrameCalcSlot result;
*   EAaLteFrameCalcRetVal retVal;    
*
*   retVal = AaLteFrameCalcTotalSlotsGet(&ref, &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcTotalSlotsGet(
    const TAaLteFrameCalcTime *refPtr,
    TAaLteFrameCalcSlot *resultPtr);

/**
********************************************************************************
*
*   @brief    Macro to check if frame number is inside window.
*
*
*   @param[in]   ref        Reference frame number.
*   @param[in]   frame      Current frame number.
*   @param[in]   maxEarly   Early limit for the current frame number.
*   @param[in]   maxLate    Late limit for the current frame number.
*   @param[in]   mask       Mask for the frame counters.
* 
*   @return      Truth value if the frame number is inside window.
*
*   @par Description:
*   This macro checks if the frame number is inside the window around
*   the reference frame number.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, frame, maxEarly, maxLate;
*   TBoolean result;    
*
*   result = AALTEFRAMECALC_FRAME_INSIDE_WINDOW_CHECK(ref, frame, maxEarly, 
*                                                     maxLate, 4095);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
#define AALTEFRAMECALC_FRAME_INSIDE_WINDOW_CHECK(      \
     ref, frame, maxEarly, maxLate, mask)          \
    (((maxEarly) + (maxLate)) >= (((maxLate) +  \
    AALTEFRAMECALC_FRAME_DIST_GET((frame),(ref),(mask))) & (mask)))

/**
********************************************************************************
*
*   @brief    Function to check if frame number is inside window.
*
*
*   @param[in]   ref        Reference frame number.
*   @param[in]   frame      Current frame number.
*   @param[in]   maxEarly   Early limit for the current frame number.
*   @param[in]   maxLate    Late limit for the current frame number.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
* 
*   @return      Truth value if the frame number is inside window.
*
*   @par Description:
*   This function checks if the frame number is inside the window around
*   the reference frame number.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, frame, maxEarly, maxLate;
*   TBoolean result;    
*
*   result = AaLteFrameCalcFrameInsideWindowCheck(ref, frame, maxEarly, maxLate,
*                EAaLteFrameCalcCounterMode_Bfn);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern TBoolean AaLteFrameCalcFrameInsideWindowCheck(
    const TAaLteFrameCalcFrame ref,
    const TAaLteFrameCalcFrame frame, 
    const TAaLteFrameCalcFrame maxEarly,
    const TAaLteFrameCalcFrame maxLate, 
    const EAaLteFrameCalcCounterMode inputMode);

/**
********************************************************************************
*
*   @brief    Macro to check if frame number is close enough to reference.
*
*
*   @param[in]   ref        Reference frame number.
*   @param[in]   frame      Current frame number
*   @param[in]   max        Maximum deviation from the reference.
*   @param[in]   mask       Mask for the frame counters.
* 
*   @return      Truth value if the current frame number is close enough to the
*                reference frame number.
*
*   @par Description:
*   This macro checks if the current frame number is close enough to the 
*   reference frame number.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, frame, max;
*   TBoolean result;    
*
*   result = AALTEFRAMECALC_FRAME_CLOSE_ENOUGH_CHECK (ref, frame, max, 4095);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/

#define AALTEFRAMECALC_FRAME_CLOSE_ENOUGH_CHECK(ref, frame, max, mask)         \
    ((2 * (max)) >=                                                          \
    (((max) + AALTEFRAMECALC_FRAME_DIST_GET((frame),(ref),(mask))) & (mask)))

/**
********************************************************************************
*
*   @brief    Function to check if frame number is close enough to reference.
*
*
*   @param[in]   ref        Reference frame number.
*   @param[in]   frame      Current frame number
*   @param[in]   max        Maximum deviation from the reference.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
* 
*   @return      Truth value if the current frame number is close enough to the
*                reference frame number.
*
*   @par Description:
*   This function checks if the current frame number is close enough to the 
*   reference frame number.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame ref, frame, max;
*   TBoolean result;    
*
*   result = AaLteFrameCalcFrameCloseEnoughCheck (ref, frame, max, 
*                EAaLteFrameCalcCounterMode_Bfn);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern TBoolean AaLteFrameCalcFrameCloseEnoughCheck(
    const TAaLteFrameCalcFrame ref,
    const TAaLteFrameCalcFrame frame, 
    const TAaLteFrameCalcFrame max,
    const EAaLteFrameCalcCounterMode inputMode);

/**
********************************************************************************
*
*   @brief    Macro to convert timing offset to BTUs.
*
*
*   @param[in]   frame      Frame offset
*   @param[in]   tcell      Tcell offset.
*   @param[in]   btu        BTU offset.
* 
*   @return      Total offset represented as BTUs.
*
*   @par Description:
*   This macro converts timing offset (represented as frame, Tcell and BTU
*   offsets) to BTUs and round the result to the closest 1024 BTU boundary.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame frame;
*   TAaLteFrameCalcTcell tcell;
*   TAaLteFrameCalcBtu btu, result;
*
*   result = AALTEFRAMECALC_TOTAL_OFFSET_BTUS_GET(frame, tcell, btu);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
#define AALTEFRAMECALC_TOTAL_OFFSET_BTUS_GET(frame, tcell, btu)               \
    ((((AALTEFRAMECALC_BTUS_PER_SLOT * AALTEFRAMECALC_SLOTS_PER_FRAME        \
    * (frame)) + ((tcell) * AALTEFRAMECALC_TCELL_UNIT_BTUS) + (btu) +         \
    (AALTEFRAMECALC_TCELL_UNIT_BTUS >> 1)) >> AALTEFRAMECALC_TCELL_UNIT_BITS) \
    << AALTEFRAMECALC_TCELL_UNIT_BITS) 

/**
********************************************************************************
*
*   @brief    Function to convert timing offset to BTUs.
*
*
*   @param[in]   frame      Frame offset
*   @param[in]   tcell      Tcell offset.
*   @param[in]   btu        BTU offset.
* 
*   @return      Total offset represented as BTUs.
*
*   @par Description:
*   This function converts timing offset (represented as frame, Tcell and BTU
*   offsets) to BTUs and round the result to the closest 1024 BTU boundary.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame frame;
*   TAaLteFrameCalcTcell tcell;
*   TAaLteFrameCalcBtu btu, result;
*
*   result = AaLteFrameCalcTotalOffsetBtusGet(frame, tcell, btu);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern TAaLteFrameCalcBtu AaLteFrameCalcTotalOffsetBtusGet(
    const TAaLteFrameCalcFrame frame,
    const TAaLteFrameCalcTcell tcell, 
    const TAaLteFrameCalcBtu btu);

/**
********************************************************************************
*
*   @brief    Macro to check if the frame number is the first.
*
*
*   @param[in]   first      The first frame number.
*   @param[in]   second     The second frame number.
*   @param[in]   current    Current frame number.
*   @param[in]   mask       Mask for the frame counter to be used.
* 
*   @return      Truth value if the first input frame number is the first.
*
*   @par Description:
*   This macro checks if the first input frame number is earlier than the 
*   second when keeping current frame number as a reference.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame first, second, current;
*   TBoolean result;
*
*   result = AALTEFRAMECALC_FRAME_IS_FIRST_CHECK(first, second, current, 4095);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
#define AALTEFRAMECALC_FRAME_IS_FIRST_CHECK(first, second, current, mask) \
    ((AALTEFRAMECALC_FRAME_DIST_GET((current),(second),(mask))) >        \
    (AALTEFRAMECALC_FRAME_DIST_GET((current),(first),(mask))))

/**
********************************************************************************
*
*   @brief    Function to check if the frame number is the first.
*
*
*   @param[in]   first      The first frame number.
*   @param[in]   second     The second frame number.
*   @param[in]   current    Current frame number.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
* 
*   @return      Truth value if the first input frame number is the first.
*
*   @par Description:
*   This function checks if the first input frame number is earlier than the 
*   second when keeping current frame number as a reference.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcFrame first, second, current;
*   TBoolean result;
*
*   result = AaLteFrameCalcFrameIsFirstCheck(first, second, current, 
*                EAaLteFrameCalcCounterMode_Bfn);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern TBoolean AaLteFrameCalcFrameIsFirstCheck(
    const TAaLteFrameCalcFrame first,
    const TAaLteFrameCalcFrame second, 
    const TAaLteFrameCalcFrame current,
    const EAaLteFrameCalcCounterMode inputMode);

/**
********************************************************************************
*
*   @brief    Macro to convert BTUs and slots to absolute time.
*
*
*   @param[in]   slot  Number of timeslots.
*   @param[in]   btu   Number of BTUs.
* 
*   @return      Duration of input timing in microseconds.
*
*   @par Description:
*   This macro converts the input BTUs and slots to absolute time and 
*   returns it as microseconds (rounded to the nearest integer).
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcSlot slot;
*   TAaLteFrameCalcBtu btu;
*   TBoolean result;
*
*   result = AALTEFRAMECALC_TIMING_CONVERT(slot, btu);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
#define AALTEFRAMECALC_TIMING_CONVERT(slot, btu)                              \
    ((((slot) * AALTEFRAMECALC_BTUS_PER_SLOT + (btu)) *                       \
     AALTEFRAMECALC_SLOT_DURATION_US + (AALTEFRAMECALC_BTUS_PER_SLOT >> 1)) / \
     AALTEFRAMECALC_BTUS_PER_SLOT)

/**
********************************************************************************
*
*   @brief    Function to convert BTUs and slots to absolute time.
*
*
*   @param[in]   refSlot    Number of timeslots.
*   @param[in]   refBtu     Number of BTUs.
* 
*   @return      Duration of input timing in [us].
*
*   @par Description:
*   This function converts the input BTUs and slots to absolute time and 
*   returns it as microseconds (rounded to the nearest integer).
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcSlot slot;
*   TAaLteFrameCalcBtu btu;
*   TAaLteFrameCalcAbsTime result;
*
*   result = AaLteFrameCalcTimingConvert(slot, btu);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern TAaLteFrameCalcAbsTime AaLteFrameCalcTimingConvert(
    const TAaLteFrameCalcSlot refSlot,
    const TAaLteFrameCalcBtu refBtu);

/**
********************************************************************************
*
*   @brief    Function to add slots to reference timing.
*
*
*   @param[in]   refPtr     Pointer to the reference timing.
*   @param[in]   slot       Number of slots to be added.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
*   @param[out]  resultPtr  Pointer to the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function adds slots to the reference timing including counters for 
*   BTUs, slots and frames. It takes care of the wrap-around of frame and slot 
*   counters.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcSlot slot;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcSlotAdd(&ref, slot, EAaLteFrameCalcCounterMode_Bfn, 
*                                  &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcSlotAdd(
    const TAaLteFrameCalcTime *refPtr, 
    const TAaLteFrameCalcSlot slot, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Function to add BTUs to reference timing.
*
*
*   @param[in]   refPtr     Pointer to the reference timing.
*   @param[in]   btu        Number of BTUs to be added.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
*   @param[out]  resultPtr  Pointer for the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function adds BTUs to the reference timing including counters for BTUs,
*   slots and frames. It takes care of the wrap-around of frame, slot and BTU 
*   counters.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcBtu btu;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcBtuAdd(&ref, btu, EAaLteFrameCalcCounterMode_Bfn, 
                                  &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcBtuAdd(
    const TAaLteFrameCalcTime *refPtr, 
    const TAaLteFrameCalcBtu btu, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Function to add BTUs and slots to reference timing.
*
*
*   @param[in]   refPtr     Pointer to the reference timing.
*   @param[in]   btu        Number of BTUs to be added.
*   @param[in]   slot       Number of slots to be added.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
*   @param[out]  resultPtr  Pointer to the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function adds BTUs and slots to the reference timing including 
*   counters for BTUs, slots and frames. It takes care of the wrap-around of 
*   frame, slot and BTU counters.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcBtu btu;
*   TAaLteFrameCalcSlot slot
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcBtuAdd(&ref, btu, slot, 
*                                 EAaLteFrameCalcCounterMode_Bfn, &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcBtuSlotAdd(
    const TAaLteFrameCalcTime *refPtr, 
    const TAaLteFrameCalcBtu btu, 
    const TAaLteFrameCalcSlot slot, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Function to accumulate two timings with frames, slots and BTUs.
*
*
*   @param[in]   firstPtr   Pointer to the first timing value to be summed.
*   @param[in]   secondPtr  Pointer to the second timing value to be summed.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
*   @param[out]  resultPtr  Pointer to the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function accumulates two separate timing values including counters for 
*   BTUs, slots and frames. It takes care of the wrap-around of all frame, slot
*   and BTU counters.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime first, second, result;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcTimingAdd(&first, &second, 
*                EAaLteFrameCalcCounterMode_Bfn, &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcTimingAdd(
    const TAaLteFrameCalcTime *firstPtr, 
    const TAaLteFrameCalcTime *secondPtr, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Function to subtract slots from reference timing.
*
*
*   @param[in]   refPtr     Pointer to the reference timing.
*   @param[in]   slot       Number of slots to be subtracted.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
*   @param[out]  resultPtr  Pointer to the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function subtracted slots to the reference timing including counters 
*   for BTUs, slots and frames. It takes care of the wrap-around of frame and 
*   slot counters.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcSlot slot;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcSlotSubtract(&ref, slot, 
*                                       EAaLteFrameCalcCounterMode_Bfn, 
*                                       &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcSlotSubtract(
    const TAaLteFrameCalcTime *refPtr,
    const TAaLteFrameCalcSlot slot, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Function to subtract BTUs from reference timing.
*
*
*   @param[in]   refPtr     Pointer to the reference timing.
*   @param[in]   btu        Number of BTUs to be subtracted.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
*   @param[out]  resultPtr  Pointer for the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function subtracts BTUs to the reference timing including counters for
*   BTUs, slots and frames. It takes care of the wrap-around of frame, slot and 
*   BTU counters.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcBtu btu;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcBtuSubtract(&ref, btu, 
*                                      EAaLteFrameCalcCounterMode_Bfn, 
                                       &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/

extern EAaLteFrameCalcRetVal AaLteFrameCalcBtuSubtract(
    const TAaLteFrameCalcTime *refPtr,
    const TAaLteFrameCalcBtu btu, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Function to subtract one timing from another.
*
*
*   @param[in]   firstPtr   Pointer to the reference timing.
*   @param[in]   secondPtr  Pointer to the timing values to be subtracted..
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
*   @param[out]  resultPtr  Pointer to the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function subtracts two separate timing values including counters for 
*   BTUs, slots and frames. It takes care of the wrap-around of all frame, 
*   slot and BTU counters.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime first, second, result;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcTimingSubtract(&first, &second, 
*                EAaLteFrameCalcCounterMode_Bfn, &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/

extern EAaLteFrameCalcRetVal AaLteFrameCalcTimingSubtract(
    const TAaLteFrameCalcTime *firstPtr,
    const TAaLteFrameCalcTime *secondPtr, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Function to calculate distance between input timings (as BTUs).
*
*
*   @param[in]   fromPtr    Pointer to the reference timing values.
*   @param[in]   toPtr      Pointer to the timing values to be compared.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
*   @param[out]  resultPtr  Pointer to the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function calculates the absolute distance between two timing values 
*   including counters for BTUs, slots and frames. Result is output as BTUs.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime from, to;
*   TAaLteFrameCalcBtu result;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcDistBtusGet(&from, &to, 
*                                      EAaLteFrameCalcCounterMode_Bfn, &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcDistBtusGet(
    const TAaLteFrameCalcTime *fromPtr, 
    const TAaLteFrameCalcTime *toPtr, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcBtu *resultPtr);

/**
********************************************************************************
*
*   @brief    Function to calculate distance between input timings.
*
*
*   @param[in]   fromPtr    Pointer to the reference timing.
*   @param[in]   toPtr      Pointer to the timing to be compared.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function calculates the absolute distance between two timing values 
*   including counters for BTUs, slots and frames. Result is output as BTUs, 
*   slots and frames.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime from, to, result;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcDistBtusGet(&from, &to, 
*                                      EAaLteFrameCalcCounterMode_Bfn, &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcDistGet(
    const TAaLteFrameCalcTime *fromPtr, 
    const TAaLteFrameCalcTime *toPtr, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Check whether the timings are close enough.
*
*
*   @param[in]   firstPtr   Pointer to the first timing.
*   @param[in]   secondPtr  Pointer to the second timing.
*   @param[in]   currentPtr Pointer to the current timing.
*   @param[in]   closeLimit Limit value (as BTUs).
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
* 
*   @return      Truth value if inputs are close enough.
*
*   @par Description:
*   This function checks whether the two input timings are close enough to each
*   other.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime first, second, current;
*   TAaLteFrameCalcBtu closeLimit
*   TBoolean result;
*
*   result = AaLteFrameCalcCloseEnoughCheck(&first, &second, &current, 
*                closeLimit, EAaLteFrameCalcCounterMode_Bfn);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern TBoolean AaLteFrameCalcCloseEnoughCheck(
    const TAaLteFrameCalcTime *firstPtr,
    const TAaLteFrameCalcTime *secondPtr, 
    const TAaLteFrameCalcTime *currentPtr,
    const TAaLteFrameCalcBtu closeLimit, 
    const EAaLteFrameCalcCounterMode inputMode);

/**
********************************************************************************
*
*   @brief    Function to convert BFN/SFN->CFN or BFN->SFN.
*
*
*   @param[in]   refPtr     Pointer to the reference timing.
*   @param[in]   offsetPtr  Pointer to the offsets to be subtracted from
*                           the reference timing.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
*   @param[out]  resultPtr  Pointer to the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function converts BFN or SFN to CFN. It can be also used for the
*   conversion BFN->SFN.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcOffset offset;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcConvert(&ref, &offset, 
*                                  EAaLteFrameCalcCounterMode_Bfn, &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcConvert(
    const TAaLteFrameCalcTime *refPtr, 
    const TAaLteFrameCalcOffset *offsetPtr, 
    const EAaLteFrameCalcCounterMode outputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Function to convert CFN->BFN/SFN or SFN->BFN.
*
*
*   @param[in]   refPtr       Pointer to the reference timing.
*   @param[in]   offsetPtr    Pointer to the offset to be added to the
*                             reference timing.
*   @param[in]   currentFrame Current BFN/SFN.
*   @param[in]   inputMode    Parameter to indicate the mode of the used frame 
*                             counter (BFN or CFN).
*   @param[out]  resultPtr    Pointer to the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function converts CFN to BFN or SFN . It can be also used for the
*   conversion SFN->BFN. This can be used when making Frame Protocol operations.
*   Result can point also to past time with this functionality.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcOffset offset;
*   TAaLteFrameCalcFrame currentFrame;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcInvConvert(&ref, &offset, currentFrame, 
*                                     EAaLteFrameCalcCounterMode_Bfn, &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcInvConvert(
    const TAaLteFrameCalcTime *refPtr, 
    const TAaLteFrameCalcOffset *offsetPtr, 
    TAaLteFrameCalcFrame currentFrame, 
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Function to convert CFN->BFN/SFN or SFN->BFN.
*
*
*   @param[in]   refPtr       Pointer to the reference timing.
*   @param[in]   offsetPtr    Pointer for the offset to be added to the
*                             reference timing.
*   @param[in]   currentFrame Current BFN/SFN.
*   @param[in]   inputMode    Parameter to indicate the mode of the used frame 
*                             counter (BFN or CFN).
*   @param[out]  resultPtr    Pointer to the result.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function converts CFN to BFN or SFN . It can be also used for the
*   conversion SFN->BFN. This can be used when making Commit operations. With 
*   Commit it is always assumed that the result is later than the current time.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcOffset offset;
*   TAaLteFrameCalcFrame currentFrame;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcCommitInvConvert(&ref, &offset, currentFrame, 
*                EAaLteFrameCalcCounterMode_Bfn, &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcCommitInvConvert(
    const TAaLteFrameCalcTime *refPtr,
    const TAaLteFrameCalcOffset *offsetPtr, 
    const TAaLteFrameCalcFrame currentFrame,
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Check if the first input timing is first.
*
*
*   @param[in]   firstPtr   Pointer to the first timing.
*   @param[in]   secondPtr  Pointer to the second timing.
*   @param[in]   currentPtr Pointer for the current timing.
*   @param[in]   inputMode  Parameter to indicate the mode of the used frame 
*                           counter (BFN or CFN).
* 
*   @return      Truth value if the first timing is first.
*
*   @par Description:
*   This function checks if the first timing is first when keeping the current
*   timing as a reference.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime first, second, current;
*   TBoolean result;
*
*   result = AaLteFrameCalcIsFirstCheck(&first, &second, &current, 
*                EAaLteFrameCalcCounterMode_Bfn);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern TBoolean AaLteFrameCalcIsFirstCheck(
    const TAaLteFrameCalcTime *firstPtr,
    const TAaLteFrameCalcTime *secondPtr, 
    const TAaLteFrameCalcTime *currentPtr,
    const EAaLteFrameCalcCounterMode inputMode);

/**
********************************************************************************
*
*   @brief    Function to correct invalid timing.
*
*
*   @param[in]      inputMode  Parameter to indicate the mode of the used frame 
*                              counter (BFN or CFN).
*   @param[in/out]  refPtr     Pointer to the timing to be normalized.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function normalizes the input timing value to the allowed limits.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcNormalize(EAaLteFrameCalcCounterMode_Bfn, &ref);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcNormalize(
    const EAaLteFrameCalcCounterMode inputMode, 
    TAaLteFrameCalcTime *refPtr);

/**
********************************************************************************
*
*   @brief    Function to add absolute time to the reference timing.
*
*
*   @param[in]   refPtr     Pointer to the reference timing.
*   @param[in]   time       Absolute time to be summed.
*   @param[in]   inputMode  Parameter to indicate unit of input time (ms/us).
*   @param[out]  resultPtr  Pointer to the result timing.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function adds absolute time (represented as micro or milliseconds) to 
*   the reference timing. Function outputs the timing indexes (frame, slot 
*   and BTU) to represent the timing after the addition.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcAbsTime time;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcTimeAdd(&ref, time, EAaLteFrameCalcTimeUnit_Ms,
*                                  &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcTimeAdd(
    const TAaLteFrameCalcTime *refPtr, 
    const TAaLteFrameCalcAbsTime time, 
    const EAaLteFrameCalcTimeUnit inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/**
********************************************************************************
*
*   @brief    Function to subtract absolute time from the reference timing.
*
*
*   @param[in]   refPtr     Pointer to the reference timing.
*   @param[in]   time       Absolute time to be subtracted.
*   @param[in]   inputMode  Parameter to indicate unit of input time (ms/us).
*   @param[out]  resultPtr  Pointer to the result timing.
* 
*   @return      EAaLteFrameCalcRetVal_NoError or
*                EAaLteFrameCalcRetVal_InvalidParameter
*
*   @par Description:
*   This function subtracts absolute time (represented as micro or milliseconds) 
*   from the reference timing. Function outputs the timing indexes (frame, slot 
*   and BTU) to represent the timing after the subtraction.
*   
*   @par Errors:
*   [EAaLteFrameCalcRetVal_InvalidParamValue] Invalid input parameter(s) given.
*
*   @par Restrictions:
*   The input parameters must have positive values.
*
*   @par Example:
*
*   @code
* 
*   TAaLteFrameCalcTime ref, result;
*   TAaLteFrameCalcAbsTime time;
*   EAaLteFrameCalcRetVal retVal;
*
*   retVal = AaLteFrameCalcTimeSubtract(&ref, time, EAaLteFrameCalcTimeUnit_Ms,
*                                       &result);
*
*   @endcode
*
*   @par Usage:
*
*   @par Rationale:
*
*   @par Future directions:
*
*   @see 
*
*******************************************************************************/
extern EAaLteFrameCalcRetVal AaLteFrameCalcTimeSubtract(
    const TAaLteFrameCalcTime *refPtr, 
    const TAaLteFrameCalcAbsTime time, 
    const EAaLteFrameCalcTimeUnit inputMode, 
    TAaLteFrameCalcTime *resultPtr);

/*----------------------- INTERNAL INTERFACES --------------------------------*/

/** @} */


#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _RT_DSP_IFAALTEFRAMECALC_H */

