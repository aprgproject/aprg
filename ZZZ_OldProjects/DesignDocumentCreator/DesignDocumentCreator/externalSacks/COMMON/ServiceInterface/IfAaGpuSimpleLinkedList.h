/** @file
*   @brief Simple Linked List API header file
*   @copyright 2014 Nokia Solutions and Networks. All rights reserved.
*   @copyright 2019 Nokia. All rights reserved.
*/

#ifndef _IFAAGPUSIMPLELINKEDLIST_H
#define _IFAAGPUSIMPLELINKEDLIST_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
*@addtogroup dgAaGpuSimpleLinkedListApi Simple Linked List
*@ingroup dgContainersApi
*
* Implementation is double linked list and bases partly on Linux kernel list.h. 
* Memory allocations are user's responsibility. Implementation is very fast and
* simple. No EE/EU synchronization is done thus user must do it if necessary.
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

#define AAGPUSIMPLELINKEDLIST_UNDETERMINED_1 0x00101100 /**< For polluting deleted elements */
#define AAGPUSIMPLELINKEDLIST_UNDETERMINED_2 0x00202200 /**< For polluting deleted elements */

/* There are differences between compilers inlining */
/** @cond */
#ifndef __CCS_INLINE__
# define __CCS_INLINE__ __inline__
#endif
/** @endcond */


/** @brief Linked list head element */
struct SAaGpuSimpleLinkedListElement
{
    struct SAaGpuSimpleLinkedListElement* next; /**< Pointer to next in the list */
    struct SAaGpuSimpleLinkedListElement* prev; /**< Pointer to previous in the list */

};

typedef struct SAaGpuSimpleLinkedListElement SAaGpuSimpleLinkedListElement;

/**
*******************************************************************************
*   
*   @brief Returns a pointer to the data structure stored into linked list element 
*
*   @def AAGPUSIMPLELINKEDLIST_ENTRY  
*
*   @param[in] __ptr     Pointer to list element
*   @param[in] __type    Type name of the data stored into list element
*   @param[in] __member  Name of the list element member in the data type
*
*   @return Pointer to __type data type
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuSimpleLinkedList.h>
*
*   typedef struct SOwnDataElement {
*       u32                            data;
*       SAaGpuSimpleLinkedListElement  listElement;
*   } SOwnDataElement;
* 
*   SAaGpuSimpleLinkedListElement head;
*   SOwnDataElement* newE = AaMemMalloc(sizeof(SOwnDataElement));
*   SAaGpuSimpleLinkedListElement* e;
*   SOwnDataElement* i;
* 
*   // Important to init head element
*   AaGpuSimpleLinkedListInit(&head);
* 
*   AaGpuSimpleLinkedListAddBefore(&newE->listElement, &head);
*
*   // Following operations are needed if list member is not the first member
*   // in the own data struct.
*   e = head->listElement.next;
*   i = AAGPUSIMPLELINKEDLIST_ENTRY(e, SOwnDataElement, listElement);
*   
*   if (i == newE)
*   {
*   }
*
*   @endcode
*
******************************************************************************/
#define AAGPUSIMPLELINKEDLIST_ENTRY(__ptr, __type, __member) \
    (CCS_REINTERPRET_CAST(__type*,(CCS_REINTERPRET_CAST(char*,__ptr)-offsetof(__type,__member))))


/**
*******************************************************************************
*   
* @brief Removes given element from list.
*
* Functionality is identical to AaGpuSimpleLinkedListRemove and this API
* call is provided only for backward compatibility. The API call is
* replaced by AaGpuSimpleLinkedListRemove() due to API consistency between
* other container implementations.
* 
* @deprecated Use AaGpuSimpleLinkedListRemove() instead
* @see AaGpuSimpleLinkedListRemove
******************************************************************************/
#define AaGpuSimpleLinkedListDel AaGpuSimpleLinkedListRemove



/*----------------------- PUBLIC INTERFACES --------------------------------*/

/**
 * @defgroup dgAaGpuSimpleLinkedListApi Simple Linked List COMMON API
 * @ingroup  dgContainersApiCommon
 */

/* @{ */

/** @} */
    
/**
*******************************************************************************
*
*   @brief      Initialize list element.
*
*   @param[in]  element Pointer to an element to initialize
*
*   @return     Pointer to the initialized element
*
*   @par Description:
*   Initilizes given element to be used in a list.
*   It is important to init head element before any other element is added.
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
*   #include <IfAaGpuSimpleLinkedList.h>
*
*   typedef struct SOwnDataElement {
*       SAaGpuSimpleLinkedListElement  list;
*       u32                            data;
*   } SOwnDataElement;
* 
*   SOwnDataElement* head = AaMemMalloc(sizeof(SOwnDataElement));
*   SAaGpuSimpleLinkedListElement head2;
* 
*   // In this example the head element is in the own element
*   AaGpuSimpleLinkedListInit(&head->list);
*
*   // In this example the head element is alone
*   AaGpuSimpleLinkedListInit(&head2);
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
static __CCS_INLINE__ SAaGpuSimpleLinkedListElement* 
AaGpuSimpleLinkedListInit(SAaGpuSimpleLinkedListElement* element)
{
    return element->next = element->prev = element;

} /* AaGpuSimpleLinkedListInit */


/**
*******************************************************************************
*
*   @brief      Insert new element between two known element.
*
*   @param[in]  element  Pointer to an element to be inserted
*   @param[in]  prev     Pointer to an element which next shall be the new
*   @param[in]  next     Pointer to an element which prev shall be the new 
*
*   @return     Pointer to the new element
*
*   @par Description:
*   Mainly used in other API calls of AaGpuSimpleLinkedList internally.
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
*      // See AaGpuSimpleLinkedListAddBefore
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
*   @see AaGpuSimpleLinkedListAddBefore
*   @see AaGpuSimpleLinkedListAddAfter
* 
******************************************************************************/
static __CCS_INLINE__ SAaGpuSimpleLinkedListElement* 
AaGpuSimpleLinkedListInsert(SAaGpuSimpleLinkedListElement* element, 
                            SAaGpuSimpleLinkedListElement* prev, 
                            SAaGpuSimpleLinkedListElement* next)
{
    next->prev = element;
    
    prev->next = element;

    element->next = next;
    element->prev = prev;

    return element;

} /* AaGpuSimpleLinkedListInsert */


/**
*******************************************************************************
*
*   @brief      Add new element after given element.
*
*   @param[in]  element  Pointer to a new element to add to a list
*   @param[in]  head     Pointer to a a list where the new element shall be added
*
*   @return     Pointer to the new element
*
*   @par Description:
*   Useful for implementing stacks.
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
*   #include <IfAaGpuSimpleLinkedList.h>
*
*   typedef struct SOwnDataElement {
*       SAaGpuSimpleLinkedListElement  list;
*       u32                            data;
*   } SOwnDataElement;
* 
*   SOwnDataElement* head = AaMemMalloc(sizeof(SOwnDataElement));
*   SOwnDataElement* newE = AaMemMalloc(sizeof(SOwnDataElement));
*
* 
*   AaGpuSimpleLinkedListInit(&head->list);
* 
*   // Pointer to the element to be added, is returned
*   AaGpuSimpleLinkedListAddAfter(&newE->list, &head->list) == &newE->list;
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
*   @see AaGpuSimpleLinkedListInit
*   @see AaGpuSimpleLinkedListAddBefore
*
******************************************************************************/
static __CCS_INLINE__ SAaGpuSimpleLinkedListElement* 
AaGpuSimpleLinkedListAddAfter(SAaGpuSimpleLinkedListElement* element, 
                              SAaGpuSimpleLinkedListElement* head)
{
    return AaGpuSimpleLinkedListInsert(element, head, head->next);
    
} /* AaGpuSimpleLinkedListAddAfter */

/**
*******************************************************************************
*
*   @brief      Add new element before given element.
*
*   @param[in]  element  Pointer to a new element to add to a list
*   @param[in]  head     Pointer to a a list where the new element shall be added
*
*   @return     Pointer to the new element
*
*   @par Description:
*   Useful for implementing queues.
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
*   #include <IfAaGpuSimpleLinkedList.h>
*
*   typedef struct SOwnDataElement {
*       SAaGpuSimpleLinkedListElement  list;
*       u32                            data;
*   } SOwnDataElement;
* 
*   SOwnDataElement* head = AaMemMalloc(sizeof(SOwnDataElement));
*   SOwnDataElement* newE = AaMemMalloc(sizeof(SOwnDataElement));
* 
*   // Only head element needs to be init because AddBefore operation
*   // does not use pointers from the source element
*   AaGpuSimpleLinkedListInit(&head->list);
* 
*   AaGpuSimpleLinkedListAddBefore(&newE->list, &head->list);
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
*   @see AaGpuSimpleLinkedListInit
*   @see AaGpuSimpleLinkedListAddAfter
* 
******************************************************************************/
static __CCS_INLINE__ SAaGpuSimpleLinkedListElement* 
AaGpuSimpleLinkedListAddBefore(SAaGpuSimpleLinkedListElement* element, 
                               SAaGpuSimpleLinkedListElement* head)
{
    return AaGpuSimpleLinkedListInsert(element, head->prev, head);
    
} /* AaGpuSimpleLinkedListAddBefore */

/**
*******************************************************************************
*
*   @brief      Removes given element from list.
*
*   @param[in]  element Pointer to a element in a list to to be removed
*
*   @return     Pointer to the removed element
*
*   @par Description:
*   Element is removed from the list. However element itself is not freed/deleted.
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
*   #include <IfAaGpuSimpleLinkedList.h>
*
*   typedef struct SOwnDataElement {
*       u32                            data1;
*       SAaGpuSimpleLinkedListElement  list; // List element can be anywhere in the struct
*       u32                            data2;
*       SAaGpuSimpleLinkedListElement  list2; // Own element can be member of another list too
*       u32                            data3;
*   } SOwnDataElement;
* 
*   SAaGpuSimpleLinkedListElement head;
*   SAaGpuSimpleLinkedListElement head2;
*   SAaGpuSimpleLinkedListElement* e;
*   SOwnDataElement* i = (SOwnDataElement*)AaMemMalloc(sizeof(SOwnDataElement));
*   
*   AaGpuSimpleLinkedListInit(&head);
*   AaGpuSimpleLinkedListInit(&head2);
*   
*   // Add element to both lists but use different list element of the own structure
*   AaGpuSimpleLinkedListAddBefore(&newE->list, &head);
*   AaGpuSimpleLinkedListAddBefore(&newE->list2, &head2);
* 
*   // Remove all list elements
*   while (!AaGpuSimpleLinkedListEmpty(&head))
*   {
*       e = head->list.next;
*       // Use AAGPUSIMPLELINKEDLIST_ENTRY macro since list element not the first member
*       i = AAGPUSIMPLELINKEDLIST_ENTRY(e, SOwnDataElement, list); // Get pointer to SOwnDataElement instance
*       // ... use the data of the instance
*       AaGpuSimpleLinkedListRemove(&e->list);
*   }
*
*   // Remove all list2 elements
*   while (!AaGpuSimpleLinkedListEmpty(&head->list2))
*   {
*       e = head->list2.next;
*       // Use AAGPUSIMPLELINKEDLIST_ENTRY macro since list element not the first member
*       i = AAGPUSIMPLELINKEDLIST_ENTRY(e, SOwnDataElement, list2); // Get pointer to SOwnDataElement instance
*       // ... use the data of the instance
*       AaGpuSimpleLinkedListRemove(&e->list2);
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
*   @see AaGpuSimpleLinkedListInit
*   @see AaGpuSimpleLinkedListEmpty
*
******************************************************************************/
static __CCS_INLINE__ SAaGpuSimpleLinkedListElement*
AaGpuSimpleLinkedListRemove(SAaGpuSimpleLinkedListElement* const element)
{
    SAaGpuSimpleLinkedListElement* next = element->next;
    SAaGpuSimpleLinkedListElement* prev = element->prev;

    next->prev = prev;
    prev->next = next;

    element->next = (SAaGpuSimpleLinkedListElement*)AAGPUSIMPLELINKEDLIST_UNDETERMINED_1;
    element->prev = (SAaGpuSimpleLinkedListElement*)AAGPUSIMPLELINKEDLIST_UNDETERMINED_2;

    return element;    
} /* AaGpuSimpleLinkedListRemove */

/**
*******************************************************************************
*
*   @brief      Checks if the list is empty.
*
*   @param[in]  head  Pointer to list head element
*
*   @par Description:
*   List is considered to be empty if head element does not point to another
*   element thus meaning that there may be data in the head but nowhere else.
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
*   #include <IfAaGpuSimpleLinkedList.h>
*
*   typedef struct SOwnDataElement {
*       SAaGpuSimpleLinkedListElement  list;
*       u32                            data;
*   } SOwnDataElement;
* 
*   SAaGpuSimpleLinkedListElement head;
*
*   SOwnDataElement* new = AaMemMalloc(sizeof(SOwnDataElement));
* 
*   AaGpuSimpleLinkedListInit(&head);
* 
*   AaGpuSimpleLinkedListAddBefore(&new->list, &head);
* 
*   if (!AaGpuSimpleLinkedListEmpty(&head))
*   {     
*       AaGpuSimpleLinkedListRemove(&new->list);
*       AaMemUnRef(&new);
*   }
* 
*   if (AaGpuSimpleLinkedListEmpty(&head))
*   {
*       AaSysLogPrint(EAaSysLogSeverityLevel_Debug, "List is now empty (only head left)");
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
******************************************************************************/
static __CCS_INLINE__ TBoolean 
AaGpuSimpleLinkedListEmpty(const SAaGpuSimpleLinkedListElement* const head)
{
    return head == head->next;
    
} /* AaGpuSimpleLinkedListEmpty */

/**
*******************************************************************************
*
*   @brief      Returns the number of element in the list.
*
*   @param[in]  head  Pointer to list head element
*
*   @par Description:
*   Element count does not contain the head element.
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
*   #include <IfAaGpuSimpleLinkedList.h>
*
*   typedef struct SOwnDataElement {
*       SAaGpuSimpleLinkedListElement  list;
*       u32                            data;
*   } SOwnDataElement;
* 
*   SAaGpuSimpleLinkedListElement head;
*
*   SOwnDataElement* new1 = AaMemMalloc(sizeof(SOwnDataElement));
*   SOwnDataElement* new2 = AaMemMalloc(sizeof(SOwnDataElement));
*   SOwnDataElement* new3 = AaMemMalloc(sizeof(SOwnDataElement));
*   size_t size;
* 
*   AaGpuSimpleLinkedListInit(&head);
* 
*   AaGpuSimpleLinkedListAddBefore(&new1->list, &head);
*   AaGpuSimpleLinkedListAddBefore(&new2->list, &head);
*   AaGpuSimpleLinkedListAddBefore(&new3->list, &head);
* 
*   size = AaGpuSimpleLinkedListSize(&head);
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
static __CCS_INLINE__ size_t 
AaGpuSimpleLinkedListSize(SAaGpuSimpleLinkedListElement* head)
{
    size_t size = 0;
    SAaGpuSimpleLinkedListElement* e = head->next;
    
    for (;e != head; ++size, e = e->next)
    {
    }
    
    return size;
    
} /* AaGpuSimpleLinkedListSize */

/**
*******************************************************************************
*
*   @brief      Moves given element to before another element.
*
*   @param[in]  element   Pointer to an element to move to another list
*   @param[in]  head      Pointer to a list where the new element shall be moved
*
*   @return     Pointer to the moved element
*
*   @par Description:
*   Moves given element from the list it currently is in to another list before
*   defined element. The moved element is returned.
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
*   #include <IfAaGpuSimpleLinkedList.h>
*
*   typedef struct SOwnDataElement {
*       SAaGpuSimpleLinkedListElement  list;
*       u32                            data;
*   } SOwnDataElement;
* 
*   SOwnDataElement*              head = AaMemMalloc(sizeof(SOwnDataElement));
*   SAaGpuSimpleLinkedListElement head2;
*
*   SOwnDataElement* newE = AaMemMalloc(sizeof(SOwnDataElement));
* 
*   AaGpuSimpleLinkedListInit(&head->list);
*   AaGpuSimpleLinkedListInit(&head2);
* 
*   // Note the difference bewteen usage of the different head elements
*   AaGpuSimpleLinkedListAddBefore(&newE->list, &head->list);
*   AaGpuSimpleLinkedListMoveBefore(&newE->list, &head2);
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
*   @see AaGpuSimpleLinkedListMoveAfter
* 
******************************************************************************/
static __CCS_INLINE__ SAaGpuSimpleLinkedListElement* 
AaGpuSimpleLinkedListMoveBefore(SAaGpuSimpleLinkedListElement* element, 
                                SAaGpuSimpleLinkedListElement* head)
{
    SAaGpuSimpleLinkedListElement* next = element->next;
    SAaGpuSimpleLinkedListElement* prev = element->prev;

    next->prev = prev;
    prev->next = next;
    
    return AaGpuSimpleLinkedListAddBefore(element, head);
    
} /* AaGpuSimpleLinkedListMoveBefore */

/**
*******************************************************************************
*
*   @brief      Moves given element to after another element.
*
*   @param[in]  element   Pointer to an element to move to another list
*   @param[in]  head      Pointer to a list where the new element shall be moved
*
*   @return     Pointer to the new element
*
*   @par Description:
*   Moves given element from the list it currently is in to another list after
*   defined element. The moved element is returned.
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
*   #include <IfAaGpuSimpleLinkedList.h>
*
*   typedef struct SOwnDataElement {
*       SAaGpuSimpleLinkedListElement  list;
*       u32                            data;
*   } SOwnDataElement;
* 
*   SAaGpuSimpleLinkedListElement head;
*   SAaGpuSimpleLinkedListElement head2;
*   SOwnDataElement* newE = AaMemMalloc(sizeof(SOwnDataElement));
* 
*   AaGpuSimpleLinkedListInit(&head);
*   AaGpuSimpleLinkedListInit(&head2);
* 
*   AaGpuSimpleLinkedListAddBefore(&newE->list, &head);
* 
*   // Element shall be moved to beginning of list2 from list1
*   AaGpuSimpleLinkedListMoveAfter(&newE->list, &head2) == &newE->list;
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
*   @see AaGpuSimpleLinkedListMoveBefore
* 
******************************************************************************/
static __CCS_INLINE__ SAaGpuSimpleLinkedListElement* 
AaGpuSimpleLinkedListMoveAfter(SAaGpuSimpleLinkedListElement* element, 
                               SAaGpuSimpleLinkedListElement* head)
{
    SAaGpuSimpleLinkedListElement* next = element->next;
    SAaGpuSimpleLinkedListElement* prev = element->prev;

    next->prev = prev;
    prev->next = next;
    
    return AaGpuSimpleLinkedListAddAfter(element, head);
    
} /* AaGpuSimpleLinkedListMoveAfter */



#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _IFAAGPUSIMPLELINKEDLIST_H */

