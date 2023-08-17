/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/ 
#ifndef _MCU_IFAAGPUSIMPLEOFFLINKEDLIST_H
#define _MCU_IFAAGPUSIMPLEOFFLINKEDLIST_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
*@addtogroup dgAaGpuSimpleOffLinkedListApi Simple Offset Linked List
*@ingroup dgContainersApi
*
* Implementation is double linked list utilising offsets instea of pointers in 
* internal house-keeping. Since some arithmetic is required during list handing
* this is not as efficient as original AaGpuSimpleLinkedList but this implementation
* sould be suitable for Linux shared memory.
* 
* @warning NULL pointer checks are not done!
* 
*@{*/

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <stddef.h>
#include <glo_def.h> /* TBoolean */

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

#define AAGPUSIMPLEOFFLINKEDLIST_UNDETERMINED_1 0x0 /**< For polluting deleted elements */
#define AAGPUSIMPLEOFFLINKEDLIST_UNDETERMINED_2 0x0 /**< For polluting deleted elements */

/* There are differences between compilers inlining */
#ifndef __CCS_INLINE__
# define __CCS_INLINE__ __inline__
#endif


/** @brief Offset Linked list head element */
struct SAaGpuSimpleOffLinkedListElement
{
    unsigned long next; /**< Offset to next in the list */
    unsigned long prev; /**< Offset to previous in the list */

};

typedef struct SAaGpuSimpleOffLinkedListElement SAaGpuSimpleOffLinkedListElement;


/*----------------------- PUBLIC INTERFACES --------------------------------*/
 


/**
 * @defgroup dgAaGpuSimpleOffLinkedListApi Simple Offset Linked List COMMON API
 * @ingroup  dgContainersApiCommon
 */

/* @{ */    

/**
*******************************************************************************
*
*   @brief      Initialize list element.
*
*   @param[in]  element Pointer to an element to initialize
*
*   @par Description:
*       Initilizes given element to be used as a list head.
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
*   @see 
*
******************************************************************************/
static __CCS_INLINE__ void 
AaGpuSimpleOffLinkedListInit(SAaGpuSimpleOffLinkedListElement* element)
{
    element->next = element->prev = 0;

} /* AaGpuSimpleOffLinkedListInit */


/**
*******************************************************************************
*
*   @brief      Insert new element between two known element.
*
*   @param[in]  base     Pointer to list base address
*   @param[in]  element  Pointer to an element to be inserted
*   @param[in]  prev     Pointer to an element which next shall be the new
*   @param[in]  next     Pointer to an element which prev shall be the new 
*
*   @par Description:
*       Mainly used by AaGpuSimpleOffLinkedList internally.
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
*   @see 
* 
******************************************************************************/
static __CCS_INLINE__ void 
AaGpuSimpleOffLinkedListInsert(const void* const                 base,
                               SAaGpuSimpleOffLinkedListElement* element, 
                               SAaGpuSimpleOffLinkedListElement* prev, 
                               SAaGpuSimpleOffLinkedListElement* next)
{
    
    
    next->prev = (unsigned long)element - (unsigned long)base;
    
    prev->next = (unsigned long)element - (unsigned long)base;

    element->next = (unsigned long)next - (unsigned long)base;
    element->prev = (unsigned long)prev - (unsigned long)base;

} /* AaGpuSimpleOffLinkedListInsert */


/**
*******************************************************************************
*
*   @brief      Add new element after given element.
*
*   @param[in]  base     Pointer to list base address
*   @param[in]  element  Pointer to a new element to add to a list
*   @param[in]  head     Pointer to a a list where the new element shall be added
*
*   @par Description:
*       Useful for implementing stacks.
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
*   @see 
*
******************************************************************************/
static __CCS_INLINE__ void 
AaGpuSimpleOffLinkedListAddAfter(const void* const                 base,
                                 SAaGpuSimpleOffLinkedListElement* element, 
                                 SAaGpuSimpleOffLinkedListElement* head)
{
    AaGpuSimpleOffLinkedListInsert(base, element, head, 
        (SAaGpuSimpleOffLinkedListElement*)((unsigned long)base + head->next));
    
} /* AaGpuSimpleOffLinkedListAddAfter */

/**
*******************************************************************************
*
*   @brief      Add new element before given element.
*
*   @param[in]  base     Pointer to list base address
*   @param[in]  element  Pointer to a new element to add to a list
*   @param[in]  head     Pointer to a a list where the new element shall be added
*
*   @par Description:
*       Useful for implementing queues.
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
*   @see 
* 
******************************************************************************/
static __CCS_INLINE__ void 
AaGpuSimpleOffLinkedListAddBefore(const void* const                 base,
                                  SAaGpuSimpleOffLinkedListElement* element, 
                                  SAaGpuSimpleOffLinkedListElement* head)
{
    AaGpuSimpleOffLinkedListInsert(base, element, 
        (SAaGpuSimpleOffLinkedListElement*)((unsigned long)base + head->prev), head);
    
} /* AaGpuSimpleOffLinkedListAddBefore */

/**
*******************************************************************************
*
*   @brief      Delete given element from list.
*
*   @param[in]  base    Pointer to list base address
*   @param[in]  element Pointer to a element in a list to to be removed
*
*   @par Description:
*       Element is removed from the list. However element itself is not freed.
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
*   @see 
*
******************************************************************************/
static __CCS_INLINE__ void 
AaGpuSimpleOffLinkedListDel(const void* const                 base,
                            SAaGpuSimpleOffLinkedListElement* element)
{
    unsigned long next = element->next;
    unsigned long prev = element->prev;

    ((SAaGpuSimpleOffLinkedListElement*)((unsigned long)base + next))->prev = prev;
    ((SAaGpuSimpleOffLinkedListElement*)((unsigned long)base + prev))->next = next;

    element->next = AAGPUSIMPLEOFFLINKEDLIST_UNDETERMINED_1;
    element->prev = AAGPUSIMPLEOFFLINKEDLIST_UNDETERMINED_2;
    
} /* AaGpuSimpleOffLinkedListDel */

/**
*******************************************************************************
*
*   @brief      Checks if the list is empty.
*
*   @param[in]  head  Pointer to list head element
*
*   @par Description:
*       List is considered to be empty if head element does not point to another
*       element thus meaning that there may be data in the head but nowhere else.
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
*   @see 
*
******************************************************************************/
static __CCS_INLINE__ TBoolean 
AaGpuSimpleOffLinkedListEmpty(SAaGpuSimpleOffLinkedListElement* head)
{
    return head->next == 0;
    
} /* AaGpuSimpleOffLinkedListEmpty */


/**
*******************************************************************************
*
*   @brief      Moves given element to before another element.
*
*   @param[in]  base      Pointer to list base address
*   @param[in]  element   Pointer to an element to move to another list
*   @param[in]  head      Pointer to a list where the new element shall be moved
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
static __CCS_INLINE__ void 
AaGpuSimpleOffLinkedListMoveBefore(const void* const                 base,
                                   SAaGpuSimpleOffLinkedListElement* element, 
                                   SAaGpuSimpleOffLinkedListElement* head)
{
    unsigned long next = element->next;
    unsigned long prev = element->prev;

    ((SAaGpuSimpleOffLinkedListElement*)((unsigned long)base + next))->prev = prev;
    ((SAaGpuSimpleOffLinkedListElement*)((unsigned long)base + prev))->next = next;
    
    AaGpuSimpleOffLinkedListAddBefore(base, element, head);
    
} /* AaGpuSimpleOffLinkedListMoveBefore */

/**
*******************************************************************************
*
*   @brief      Moves given element to after another element.
*
*   @param[in]  base      Pointer to list base address
*   @param[in]  element   Pointer to an element to move to another list
*   @param[in]  head      Pointer to a list where the new element shall be moved
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
static __CCS_INLINE__ void 
AaGpuSimpleOffLinkedListMoveAfter(const void* const                 base,
                                  SAaGpuSimpleOffLinkedListElement* element, 
                                  SAaGpuSimpleOffLinkedListElement* head)
{
    unsigned long next = element->next;
    unsigned long prev = element->prev;

    ((SAaGpuSimpleOffLinkedListElement*)((unsigned long)base + next))->prev = prev;
    ((SAaGpuSimpleOffLinkedListElement*)((unsigned long)base + prev))->next = next;
    
    AaGpuSimpleOffLinkedListAddAfter(base, element, head);
    
} /* AaGpuSimpleOffLinkedListMoveAfter */

/** @} */


#ifdef __cplusplus
}
#endif

/*@}*/


#endif /* _MCU_IFAAGPUSIMPLEOFFLINKEDLIST_H */

