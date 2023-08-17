/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/ 
#ifndef _MCU_IFAAGPUHISTOGRAM_H
#define _MCU_IFAAGPUHISTOGRAM_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/**
*@addtogroup dgStatistics 
*
* @par Histogram Measurement Utility
* This utility collects data and stores them to one of the
* pre-defined categories or bins. The categories may have different widths
* and the width is important purpose since the area of the category, calculated
* using the category width and the number of cases in the category, denotes the
* value of the histogram.
*
*/

/**
*@addtogroup dgAaGpuHistogramApi Event Histogram
*@ingroup dgStatisticsApi
*
*
*@{*/

/*----------------------- INCLUDED FILES --------------------------------------*/

#include <glo_def.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
    
/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

typedef void TAaGpuHistogramHandle;
typedef void TAaGpuHistogramSet;
typedef u32 TAaGpuHistogramSize;
typedef u32 TAaGpuHistogramValue;


typedef enum EAaGpuHistogramRet
{
    EAaGpuHistogramRet_Ok = 0,
    EAaGpuHistogramRet_InvalidParam, /**< Invalid parameter given */
    EAaGpuHistogramRet_ReadOnly,     /**< read-only histogram */
    EAaGpuHistogramRet_Error,        /**< some other error */
    EAaGpuHistogramRet_NbrOf /**< Always the last member */
} EAaGpuHistogramRet;

/*----------------------- PUBLIC INTERFACES --------------------------------*/


/**
 * @defgroup dgAaGpuHistogramApi Event Histogram COMMON API
 * @ingroup  dgStatisticsApiCommon
 */

/* @{ */
/**
*******************************************************************************
*
*   @brief  Allocates a new histogram
*
*   @param name[in] Namespaced name for the histogram
*   @param size[in] number of histogram bins
*   
*   @return Handle to the allocated histogram, GLO_NULL if allocation failed
*
*   @par Description:
*   If name is given GLO_NULL, histogram is dealed as private and the
*   handle ptr is then the only access to the histogram. Otherwise the
*   histogram will be stored EE wide and it can be accessed by the name also.
*   Single handle instance should not be shared between several EUs.
*
*   Named histograms can not be freed. Once created they will stay in memory.
*
*   Returns GLO_NULL if histogram allocation fails or size of histogram
*   is zero.
*
*   @par Errors:
*   The call may fail if memory allocation for histogram fails.
*
*   @par Restrictions:
*   Named histogram can not be freed.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuHistogram.h>
*
*   TAaGpuHistogramHandle *histogramHandle;
*
*   //Create a private histogram with 10 bins
*
*   histogramHandle = AaGpuHistogramAlloc(GLO_NULL, 10); 
*
*   //or named histogram with 10 bins
*
*   histogramHandle = AaGpuHistogramAlloc("foo.bar", 10);
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
******************************************************************************/
TAaGpuHistogramHandle*
AaGpuHistogramAlloc(const char* const name, TAaGpuHistogramSize size);

/**
*******************************************************************************
*
*   @brief  Frees a histogram
*
*   @param handle[in] Handle to the histogram
*
*   @return none
*
*   @par Description:
*   Frees histogram. Only private histograms are actually freed. If
*   histogram is named, only reference to histogram is freed.
*
*   @par Errors:
*
*   @par Restrictions:
*   Named histogram can not be freed entirely. 
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuHistogram.h>
*
*   TAaGpuHistogramHandle *histogramHandle = AaGpuHistogramAlloc(GLO_NULL, 10); 
*
*   ...
*   //Set ranges and use histogram 
*   ...
*
*   AaGpuHistogramFree(histogramHandle);
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
******************************************************************************/
void
AaGpuHistogramFree(TAaGpuHistogramHandle *handle);

/**
*******************************************************************************
*
*   @brief  Sets ranges for existing histogram 
*
*   @param handle[in] Handler of the histogram
*   @param ranges[in] table of ranges
*   @param size[in] number of elements in ranges table
*
*   @return Status of the API call
*
*   @par Description:
*   Sets user specified ranges to histogram.
*
*   Ranges table is used to set ranges for histogram. Ranges table 
*   must have one element more than there is bins in histogram.
*   Data in histogram is zeroed.
*
*   @par Errors:
*   The call may fail if given size does not match with histogram size or
*   histogram is read only.
*
*   @par Restrictions:
*   It is not possible to set ranges via read-only handle.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuHistogram.h>
*
*   #define HISTOGRAM_SIZE 10
*
*   TAaGpuHistogramSize size = HISTOGRAM_SIZE;
*   TAaGpuHistogramValue range_table[HISTOGRAM_SIZE+1];
*   TAaGpuHistogramHandle *histogramHandle;
*
*   histogramHandle = AaGpuHistogramAlloc(GLO_NULL, HISTOGRAM_SIZE); 
*
*   //Fill range_table. Here we create histogram with ranges 0,5,10...50
*   for(i=0; i<=HISTOGRAM_SIZE; i++)
*   {
*        range_table[i] = i*5;
*   }
*
*   AaGpuHistogramSetRange(histogramHandle, range_table, HISTOGRAM_SIZE+1);
*
*   //Histogram is now ready for use
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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramSetRanges(const TAaGpuHistogramHandle* handle,
                        const TAaGpuHistogramValue ranges[],
                        const TAaGpuHistogramSize size);

/**
*******************************************************************************
*
*   @brief  Sets linear ranges for existing histogram
*
*   @param handle[in] Handle of the histogram
*   @param min[in] minimum lower range
*   @param max[in] maximum upper range
*
*   @return Status of the API call
*
*   @par Description:
*   Sets linear ranges to the histogram. Data in the histogram is zeroed.
*
*   @par Errors:
*   The call fails if maximum upper range is smaller or equal than minimum
*   lower range. The call also fails if the histogram is read only. The
*   call also fails if (max-min)%(number_of_histogram_bins)!=0.   
*
*   @par Restrictions:
*   - It is not possible to set ranges via read-only handle.
*   - (max - min) % (number_of_histogram_bins) must be zero.
*
*
*   @par Example:
*
*   @code
*   #include <IfAaGpuHistogram.h>
*
*   #define HISTOGRAM_SIZE 10
*
*   TAaGpuHistogramSize size = HISTOGRAM_SIZE;
*   TAaGpuHistogramValue range_min, range_max;
*   TAaGpuHistogramHandle *histogramHandle;
*
*   histogramHandle = AaGpuHistogramAlloc(GLO_NULL, HISTOGRAM_SIZE); 
*
*   range_min = 0;
*   range_max = 50;
*
*   //Set ranges 0,5,10...50   
*   AaGpuHistogramSetRangesLinear(histogramHandle, range_min, range_max);
*
*   //Histogram is ready for use.
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
*   Condition max-min%(number_of_bins)=0 should be removed.
*
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramSetRangesLinear(const TAaGpuHistogramHandle* handle,
                              const TAaGpuHistogramValue min,
                              const TAaGpuHistogramValue max);

/**
*******************************************************************************
*
*   @brief  Increments histogram 
*
*   @param handle[in] Handler of the histogram
*   @param min[in] value
*
*   @return Status of API call
*
*   @par Description:
*   Updates histogram. Increments bin whose range contains given value.
*
*   @par Errors:
*   The call fails if given value is out of histogram range.
*
*   @par Restrictions:
*   The ranges must be set to histogram before incrementing.
*
*   @par Example:
*
*   @code
*   #include <IfAaGpuHistogram.h>
*
*   TAaGpuHistogramHandle *histogramHandle = AaGpuHistogramAlloc(GLO_NULL, 10);
*
*   AaGpuHistogramSetRangesLinear(histogramHandle, 0, 50);
*
*   ...
*   //Set some_value to histogram
*   AaGpuHistogramIncrement(histogramHandle, some_value);
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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramIncrement(const TAaGpuHistogramHandle* handle,
                        const TAaGpuHistogramValue value);

/**
*******************************************************************************
*
*   @brief  Get size of histogram
*
*   @param handle[in] Handler of the histogram
*   @param size[out] pointer to size 
*
*   @return Status of API call
*
*   @par Description:
*   Get size of histogram to user the specified pointer.
*
*   @par Errors:
*   The call fails if given handle is not valid.
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuHistogram.h>
*
*   TAaGpuHistogramSize histogram_size;
*
*   TAaGpuHistogramHandle *histogramHandle = AaGpuHistogramAlloc(GLO_NULL, 10);
*
*   AaGpuHistogramGetSize(histogramHandle, &histogram_size);
*
*   //histogram_size is now 10
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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramGetSize(const TAaGpuHistogramHandle* handle,
                      TAaGpuHistogramSize* size);

/**
*******************************************************************************
*
*   @brief  Returns bin of histogram
*
*   @param handle[in] Handler of the histogram
*   @param bin[in] bin number of histogram 
*   @param value[out] pointer to store bin value
*
*   @return Status of API call
*
*   @par Description:
*   Returns number of samples in histogram bin to pointer value
*
*   @par Errors:
*   The call fails if given histogram handle is not valid or given bin
*   is bigger than histogram size.
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramGetBin(const TAaGpuHistogramHandle* handle,
                     const TAaGpuHistogramSize bin,
                     TAaGpuHistogramValue* value);

/**
*******************************************************************************
*
*   @brief Get maximum value of histogram
*
*   @param handle[in] Handler of the histogram
*   @param value[out] pointer to store bin value
*
*   @return Status of API call
*
*   @par Description:
*   Returns maximum bin value of the histogram to given pointer value.
*
*   @par Errors:
*   The call fails if given histogram handle is invalid.
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   TAaGpuHistogramHandle* handle;
*   TAaGpuHistogramValue maxval;
*   ...
*   AaGpuHistogramGetMaxVal(handle, &maxval);
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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramGetMaxVal(const TAaGpuHistogramHandle* handle,
                        TAaGpuHistogramValue* value);

/**
*******************************************************************************
*
*   @brief Get minimum value of the histogram
*
*   @param handle[in] Handler of the histogram
*   @param value[out] pointer to store bin value
*
*   @return Status of API call
*
*   @par Description:
*   Returns minimum bin value of the histogram to given pointer value.
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*   TAaGpuHistogramHandle* handle;
*   TAaGpuHistogramValue minval;
*   ...
*   AaGpuHistogramGetMaxVal(handle, &minval);
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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramGetMinVal(const TAaGpuHistogramHandle* handle,
                        TAaGpuHistogramValue* value);


/**
*******************************************************************************
*
*   @brief Get index of bin containing maximum value
*
*   @param handle[in] Handler of the histogram
*   @param value[out] pointer to store bin number
*
*   @return Status of API call
*
*   @par Description:
*   Returns bin containing maximum value. If there are several bins 
*   containing maximum value only bin with smallest index is returned.
*
*   @par Errors:
*   The call fails if given histogram handle is invalid.
*
*   @par Restrictions:
*
*   @par Example:
*   TAaGpuHistogramHandle* handle;
*   TAaGpuHistogramSize maxbin;
*   ...
*   AaGpuHistogramGetMaxBin(handle, &maxbin);
*
*   @code
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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramGetMaxBin(const TAaGpuHistogramHandle* handle,
                        TAaGpuHistogramSize* bin);

/**
*******************************************************************************
*
*   @brief Get index of bin containing minimum value
*
*   @param handle[in] Handler of the histogram
*   @param value[out] pointer to store bin number
*
*   @return Status of API call
*
*   @par Description:
*   Returns bin containing minimum value. If there are several bins
*   containing minimum value only bin with smallest index is returned.
*
*   @par Errors:
*   The call fails if given handle to histogram is invalid.
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*   TAaGpuHistogramHandle* handle;
*   TAaGpuHistogramSize minbin;
*   ...
*   AaGpuHistogramGetMinBin(handle, &minbin);

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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramGetMinBin(const TAaGpuHistogramHandle* handle,
                        TAaGpuHistogramSize* bin);

/**
*******************************************************************************
*
*   @brief  Returns sum of histogram bins
*
*   @param handle[in] Handler of the histogram
*   @param value[out] pointer to store histogram sum value
*
*   @return Status of API call
*
*   @par Description:
*   Returns sum of histogram bins to pointer value.
*
*   @par Errors:
*   The call fails if histogram handle is invalid.
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*   TAaGpuHistogramHandle* handle;
*   TAaGpuHistogramValue sum;
*   ...
*   AaGpuHistogramGetSum(handle, &sum);

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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramGetSum(const TAaGpuHistogramHandle* handle, 
                     TAaGpuHistogramValue* value);

/*******************************************************************************
*
*   @brief  Get range of bin
*
*   @param handle[in] Handler of the histogram
*
*   @param bin[in] bin number of histogram
*   @param lower[out] pointer to lower limit of range
*   @param upper[out] pointer to upper limit of range
*
*   @return Status of API call
*
*   @par Description:
*   Gets upper and lower range of bin.
*
*   @par Errors:
*   The call fails if bin number is bigger than histogram size or given
*   histogram handle is invalid.
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*   TAaGpuHistogramHandle* handle;
*   TAaGpuHistogramValue lower_range;
*   TAaGpuHistogramValue upper_range;
*   ...
*   //Get upper and lower ranges of bin 0    
*   AaGpuHistogramGetRange(handle, 0, &lower_range, &upper_range);
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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramGetRange(const TAaGpuHistogramHandle* handle,
                       const TAaGpuHistogramSize bin,
                       TAaGpuHistogramValue* lower,
                       TAaGpuHistogramValue* upper);

/*******************************************************************************
*
*   @brief  Dumps histogram
*
*   @param handle[in] Handler of the histogram
*   @param filename[in] dump filename with full path or GLO_NULL
*
*   @return 
*
*   @par Description:
*   Dumps histogram to a file or to the syslog. If the filename is GLO_NULL,
*   dump is directed to syslog. A line in dump is in following format 
*   (space is used as a separator): 
*   [min range of bin] [max range of bin] [bin value]
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*   TAaGpuHistogramHandle* handle;
*   ...
*   AaGpuHistogramDump(handle, 0, "/ram/hist_dump.txt");
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
******************************************************************************/
void
AaGpuHistogramDump(const TAaGpuHistogramHandle* handle, const char* filename);

/**
*******************************************************************************
*
*   @brief  Returns a read-only copy of a histogram corresponding to a name
*
*   @param name[in] Name of the histogram
*
*   @return Handle to the read-only copy of histogram, GLO_NULL if histogram
*   with specified name not found
*
*   @par Description:
*   Returns a read-only copy of histogram handle. User is responsible of 
*   freeing the handle after usage with AaGpuHistogramFree(). Notice that the
*   copy cannot be used to increment bins. It can be only used to obtain the
*   histogram data.
*
*   @par Errors:
*
*   @par Restrictions:
*   It is not recommended to lookup the handle by name all the time, instead
*   in histogram update procedure the direct handle ptr should be stored locally
*   which makes the update procedure fast. The lookup by name can be 
*   potentially expensive operation. Wildcards cannot be used in the name.
*
*   @par Example:
*
*   @code
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
******************************************************************************/
TAaGpuHistogramHandle*
AaGpuHistogramGetCopy(const char* const name);

/**
*******************************************************************************
*
*   @brief  Adds alias name for existing histogram
*
*   @param handle[in] Handler of the histogram
*   @param name[in] Name for the alias
*
*   @return Status of API call
*
*   @par Description:
*   The histogram can be used via both original and alias names. Adding alias name
*   for existing alias name effectively adds the alias for the original name.
*
*   @par Errors:
*   The call fails if the handle is read-only, return code
*   #EAaGpuHistogramRet_ReadOnly is returned.
*   If one or both of the parameters are invalid (GLO_NULL or otherwise invalid),
*   return code #EAaGpuDurHistogram_InvalidParam is returned.
*
*   @par Restrictions:
*   It is not possible to add alias via read-only handler.
*
*   @par Example:
*
*   @code
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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramAddAlias(const TAaGpuHistogramHandle* handle,
                       const char* const alias);

/**
*******************************************************************************
*
*   @brief  Finds the histogram name with handle
*
*   @param handle[in] Counter handle
*
*   @return Pointer to string of histogram name or GLO_NULL
*
*   @par Description:
*
*   @par Errors:
*   If histogram is private(no name was given in allocation), GLO_NULL is returned.
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
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
******************************************************************************/
const char*
AaGpuHistogramGetName(TAaGpuHistogramHandle *handle);

/**
*******************************************************************************
*
*   @brief  Resets histogram
*
*   @param handle[in] Handle to the histogram
*
*   @return Status of API call
*
*   @par Description:
*   Sets all histogram bin values to zero.
*
*   @par Errors:
*   The call fails if histogram is read only or given histogram handle is
*   invalid
*
*   @par Restrictions:
*   It is not possible to reset the histogram via read-only handler.
*
*   @par Example:
*
*   @code
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
******************************************************************************/
EAaGpuHistogramRet
AaGpuHistogramReset(TAaGpuHistogramHandle *handle);


/**
*******************************************************************************
*
*   @brief  gets histogram names under certain namespace
*
*   @param parent[in] Parent histogram namespace
*   @param child[out] Pointer to placeholder for set of child histogram names
*
*   @return number of items in the childs name set
*
*   @par Description:
*   returns the names of the histograms that are childs for the parent name.
*   You can use wildcards in the parent as follows:
*   Let's assume that following histograms exist:
*       "ccs.aasyscom.msg.receive.size"
*       "ccs.aasyscom.msg.receive.latency"
*       "ccs.aamem.latency.alloc"
*   By setting parent name to "ccs." the return value will be 3 and the 
*   childs array will contain three items (all histogram names given above).
*   By setting parent name to "ccs.aasyscom." the return value will be 2 
*   and the childs array will contain two items
*       "ccs.aasyscom.msg.receive.size"
*       "ccs.aasyscom.msg.receive.latency"
*
*   User is responsible of freeing the set after usage with AaMemUnRef.
*
*   If no matches occurs for given parent name, 0 is returned and #child
*   is left untouched.
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
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
******************************************************************************/
size_t
AaGpuHistogramGetChildNameSet(const char* const parent,
                              TAaGpuHistogramSet** child);
/**
*******************************************************************************
*
*   @brief  Returns next name from the given set
*
*   @param child[in] Set of child
*
*   @return Pointer to the null-terminated name string or GLO_NULL
*
*   @par Description:
*   Pointer to a name is returned until all names are iterated and then
*   GLO_NULL is returned. Iterated set cannot be rewind instead new set must
*   be queried.
*
*   @par Errors:
*   If invalid parameters are given, GLO_NULL is returned.
*
*   @par Restrictions:
*   Once iterated, the set is fully consumed thus containing no elements.
*
*   @par Example:
*
*   @code
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
******************************************************************************/
char*
AaGpuHistogramGetNextChildName(TAaGpuHistogramSet* child);

/** @} */

/*----------------------- PRIVATE INTERFACES --------------------------------*/

/** @name Internal API
*@{
*/

/** @brief Executes CE level initialization */
EAaGpuHistogramRet AaGpuHistogramCeInit(void);
/** @brief Executes CE level uninitialization */
EAaGpuHistogramRet AaGpuHistogramCeUnInit(void);
/** @brief Executes EE level initialization */
EAaGpuHistogramRet AaGpuHistogramEeInit(void);
/** @brief Executes EE level uninitialization */
EAaGpuHistogramRet AaGpuHistogramEeUnInit(void);

/**@}*/

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /*  _MCU_IFAAGPUHISTOGRAM_H */
