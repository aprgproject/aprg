/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Linked Queue API header file
* @module                AaGpu
* @owner                 Marcela Nemet
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAAGPULINKEDQUEUE_H
#define _IFAAGPULINKEDQUEUE_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
*@addtogroup dgAaGpuLinkedQueueApi Linked Queue
*@ingroup dgContainersApi
*
* LinkedQueue is a implementation of double ended queue. Add/remove from head or
* tail is O(1). Add/Remove from other than head or tail is not supported, due
* to the nature of the container.
* 
*@{*/

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @brief handle type for AaGpuLinkedQueue */
typedef void TAaGpuLinkedQueue;

/** @brief prototype for memory alloc function */
typedef void* (TAaGpuMemAlloc)(size_t size);

/** @brief protorype for memory free function */
typedef void (TAaGpuMemFree)(void **ptr);


/**
 * @defgroup dgAaGpuLinkedQueueApi Linked Queue COMMON API
 * @ingroup  dgContainersApiCommon
 */

/* @{ */
/*----------------------- PUBLIC INTERFACES --------------------------------*/

/**
*******************************************************************************
*
*   @brief  Create a container
*
*   @param[in]  allocFunc allocator function pointer
*   @param[in]  freeFunc comparator function pointer
*
*   @return pointer to created container
*
*   @par Description:
*     Create a queue. It is possible to define allocFunc and freeFunc to GLO_NULL
*     in which case the default functions will be used. Notice that the alloc and
*     the free functions should match, so that the region allocated with the alloc
*     function should be able to free with the free func. This means that both of
*     these or neither should be defined. It will be considered an error if you
*     define only one of them.
*   
*   @par Errors:   
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
******************************************************************************/
TAaGpuLinkedQueue* AaGpuLinkedQueueCreate(TAaGpuMemAlloc *allocFunc,
                                          TAaGpuMemFree  *freeFunc);


/**
*******************************************************************************
*
*   @brief  number of elements
*
*   @param[in]  container Pointer to container
*
*   @return number of elements in the container
*
*   @par Description:
*   
*   @par Errors:   
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
******************************************************************************/
size_t AaGpuLinkedQueueSize(TAaGpuLinkedQueue *container);


/**
*******************************************************************************
*
*   @brief  adds a new element to the front
*
*   @param[in]  container Pointer to container
*   @param[in]  newItem New item to be pushed into front
*
*   @return Nothing.
*
*   @par Description:
*     Pushes a new item to the front. User is responsible of allocating
*     dynamic memory for the newItem as no copying will be done in the
*     interface. Allocation should be done with the same allocator that
*     was configured in the container create.
*   
*   @par Errors:   
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
******************************************************************************/
void AaGpuLinkedQueuePushFront(TAaGpuLinkedQueue *container, void *newItem);


/**
*******************************************************************************
*
*   @brief  adds a new element to the back
*
*   @param[in]  container Pointer to container
*   @param[in]  newItem New item to be pushed into back
*
*   @return Nothing.
*
*   @par Description:
*     pushes a new item to the back. User is responsible of allocating
*     dynamic memory for the newItem as no copying will be done in the
*     interface. Allocation should be done with the same allocator that
*     was configured in the container create.
*   
*   @par Errors:   
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
******************************************************************************/
void AaGpuLinkedQueuePushBack(TAaGpuLinkedQueue *container, void *newItem);


/**
*******************************************************************************
*
*   @brief  gets element from the front
*
*   @param[in]  container Pointer to container
*
*   @return element, or NULL if empty
*
*   @par Description:
*     User should not try to free the dynamic memory pointed
*     by the returned pointer as the element still remains in the queue.
*   
*   @par Errors:   
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
******************************************************************************/
const void* AaGpuLinkedQueueFront(TAaGpuLinkedQueue *container);


/**
*******************************************************************************
*
*   @brief  gets element from the back
*
*   @param[in] container Pointer to container
*
*   @return element, or NULL if empty
*
*   @par Description:
*     User should not try to free the dynamic memory pointed
*     by the returned pointer as the element still remains in the queue.
*   
*   @par Errors:   
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
******************************************************************************/
const void* AaGpuLinkedQueueBack(TAaGpuLinkedQueue *container);


/**
*******************************************************************************
*
*   @brief  pops front element from queue
*
*   @param[in] container Pointer to container
*
*   @return  returns the popped element
*
*   @par Description:
*     User is responsible to free the dynamic memory
*     pointed by the returned pointer after it is no longer used.
*   
*   @par Errors:   
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
******************************************************************************/
void* AaGpuLinkedQueuePopFront(TAaGpuLinkedQueue *container);


/**
*******************************************************************************
*
*   @brief  pops back element from queue
*
*   @param[in] container Pointer to container
*
*   @return  returns the popped element
*
*   @par Description:
*     User is responsible to free the dynamic memory
*     pointed by the returned pointer after it is no longer used.
*   
*   @par Errors:   
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
******************************************************************************/
void* AaGpuLinkedQueuePopBack(TAaGpuLinkedQueue *container);

/**
*******************************************************************************
*
*   @brief  Clears a container by removing all existing elements
*
*   @param[in] container Pointer to container
*
*   @return  none
*
*   @par Description:
*     All elements in the container will be freed using the free function 
*     configured at the container create. Calling of AaGpuLinkedQueueSize for
*     the container shall return 0 after calling this function. Container instance
*     itself is not destroyed in contrast to AaGpuLinkedQueueDestroy.
*   
*   @par Errors:   
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
*   @see AaGpuLinkedQueueSize
*   @see AaGpuLinkedQueueDestroy
*
******************************************************************************/
void AaGpuLinkedQueueClear(TAaGpuLinkedQueue *container);

/**
*******************************************************************************
*
*   @brief  destroys a container
*
*   @param[in] container Pointer to pointer to a container
*
*   @return  none
*
*   @par Description:
*     destroys a container. If there are elements in the container those will
*     be freed using the free function configured at the container create.
*   
*   @par Errors:   
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
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
******************************************************************************/
void AaGpuLinkedQueueDestroy(TAaGpuLinkedQueue **container);


/** @} */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _IFAAGPULINKEDQUEUE_H */

