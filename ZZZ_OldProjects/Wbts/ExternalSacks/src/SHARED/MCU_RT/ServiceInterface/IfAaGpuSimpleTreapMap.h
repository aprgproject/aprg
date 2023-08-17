/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 API header file for simple treap implementation
* @module                AaGpu
* @owner                 Marcela Nemet
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAGPUSIMPLETREAPMAP_H
#define _MCU_RT_IFAAGPUSIMPLETREAPMAP_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
*@addtogroup dgAaGpuSimpleTreapMapApi Simple Treap Map
*@ingroup dgContainersApi
*
* Unique key:data mapping with priority.
*
* Treap-based implementation of binary search tree. Every node is a composition 
* of key, priority and data. The key and priority can be arbitrary format since 
* user can define comparator call-back function for key and priority comparison.
* Key must always be unique. 
*
* In principle, treap nodes are ordered according to keys so that they form 
* binary search tree and according to priority so that heap properties are 
* fulfilled (in this case max-heap) i.e. minimal 2-dimensional ordering. Keys 
* are always unique but priority do not necessary be unique. However if priorities 
* are non-random, the tree may not be balanced (worst-case situation). However the 
* most important elements according to the priority are near the root.
*
* @code
*
*                                        Key-ordered:     Priority-ordered:
*  ^               a
*  |         /-----5-----\      operation: iteration        removing root
*  |         b           c                 (e,11)           (a,5)
*  |     /---3---\   /---8---\             (d,10)           (b,3)
*  P     c       f   c       c             (c,9)            (c,2)
*  R     2       4   6       9---\         (c,8)            (c,8)
*  I                             d         (c,6)            (c,6)
*  O                            10---\     (a,5)            (c,9)
*  R                                 e     (f,4)            (d,10)
*  |                                11     (b,3)            (e,11)
*  |                                       (c,2)            (f,4)
*  |                                       
*  ------------KEY-------------------->
*
* Here letters are priorities and numbers are keys. Element (a,5) is 
* the root thus having the highest priority. Removing root effectively allows 
* getting elements in priority-ordered.
*
* @endcode
*
* It should be noted that treap only quarantees that parent element has
* greater (or equal) priority than it's child. The priority of two child of 
* the parent element have no specific order between each others according to 
* the priority. This means that it is not possible to iterate according to 
* priority instead root element removing is the only way to get elements in 
* priority order.
* 
* Removing of root can be achieved using AaGpuSimpleTreapMapGetHigh() and
* AaGpuSimpleTreapMapRemoveE() paradigm.
*
* @warning NULL pointer checks are not done!
*
*@{*/


/*----------------------- INCLUDED FILES -------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @brief Bi-state comparator definition for value comparsion 
* @param[in] value1  Value to compare
* @param[in] value2  Value to compare with
* 
* @return If value1 is smaller that value2, #AAGPUSIMPLETREAPMAP_COMPARATOR_LESS
* @return If value1 is equal or greater than value2, #AAGPUSIMPLETREAPMAP_COMPARATOR_NONLESS
*/
typedef int TAaGpuSimpleTreapMapComparator(const void* const value1, const void* const value2);

/** @brief Returned by comparator when value1 is smaller than value2 
* @see TAaGpuSimpleTreapMapComparator
*/
#define AAGPUSIMPLETREAPMAP_COMPARATOR_LESS    1
/** @brief Returned by comparator when value1 is equal or greater than value2 
* @see TAaGpuSimpleTreapMapComparator
*/
#define AAGPUSIMPLETREAPMAP_COMPARATOR_NONLESS 0


/** @brief Treap element with map support */
typedef struct SAaGpuSimpleTreapMapElement
{
    /* Treap related members */
    struct SAaGpuSimpleTreapMapElement* left;     /**< Child which has bigger key and lower priority */
    struct SAaGpuSimpleTreapMapElement* right;    /**< Child which has smaller key and lower priority */
    struct SAaGpuSimpleTreapMapElement* parent;   /**< Child which has higher priority */
    void*                               priority; /**< Arbitrary but not necessarily unique between elements in a treap */

    /* Map related members */
    void*                               key;  /**< Arbitrary and unique for every element in a treap */
    void*                               data; /**< Arbitrary data */

} SAaGpuSimpleTreapMapElement;

/** @brief Handler for treap map */
typedef struct SAaGpuSimpleTreapMapHandler
{
    TAaGpuSimpleTreapMapComparator* keyComp;   /**< Comparator for element key comparsions */
    TAaGpuSimpleTreapMapComparator* priorComp; /**< Comparator for element priority comparsions */

    SAaGpuSimpleTreapMapElement*    root;      /**< The first element of the map (the highest according to priority) */
    unsigned int                    elements;  /**< Number of elements currently in the map */

} SAaGpuSimpleTreapMapHandler;

/** @brief Iterator definition for fast treap passing */
typedef struct SAaGpuSimpleTreapMapIterator
{
    SAaGpuSimpleTreapMapHandler* handler; /**< Handler of the treap this iterator iterates */

    SAaGpuSimpleTreapMapElement* current; /**< Current element in iteration */
    SAaGpuSimpleTreapMapElement* first;   /**< First element iteration started */

    int                          level;   /**< Iteration depth for debugging purpose. Might be negative. */

} SAaGpuSimpleTreapMapIterator;


/*----------------------- PUBLIC INTERFACES --------------------------------*/


/**
 * @defgroup dgAaGpuSimpleTreapMapApi Simple Treap Map COMMON API
 * @ingroup  dgContainersApiCommon
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief      Initializes treap map handler.
*
*   @param[in]  handler    Pointer to an handler to initialize
*   @param[in]  keyComp    Function to be used for key comparison
*   @param[in]  priorComp  Function to be used for priority comparison
*
*   @return     none
*
*   @par Description:
*
*   Initilizes given treap map handler to be used.
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
*   #include <IfAaGpuSimpleTreapMap.h>
*
*   SAaGpuSimpleTreapMapHandler handler;
*
*   // Init the tree
*   AaGpuSimpleTreapMapInit(&handler, 
*                           AaGpuSimpleTreapMapComparatorString,  // Key is pointer to string 
*                           AaGpuSimpleTreapMapComparatorString); // Prioroty is pointer to string
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
*   @see AaGpuSimpleTreapMapElementInit
*   @see AaGpuSimpleTreapMapAdd
*   @see AaGpuSimpleTreapMapPrune
*
******************************************************************************/
void 
AaGpuSimpleTreapMapInit(SAaGpuSimpleTreapMapHandler*    const handler, 
                        TAaGpuSimpleTreapMapComparator* const keyComp,
                        TAaGpuSimpleTreapMapComparator* const priorComp);


/** @} */

/**
*******************************************************************************
*
*   @brief      Sets a key to map element.
*
*   @def AaGpuSimpleTreapMapKeySet
*
*   @param[in]  ___element Pointer to the element where key shall be set
*   @param[in]  ___key     Pointer to the key to set
*
*   @return     none
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
*
*   @code
*
*   // See AaGpuSimpleTreapMapAdd
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
*   @see AaGpuSimpleTreapMapElementInit
*   @see AaGpuSimpleTreapMapAdd
*   @see AaGpuSimpleTreapMapFind
*
******************************************************************************/
#define AaGpuSimpleTreapMapKeySet(___element, ___key) ((___element)->key = ___key)


/**
*******************************************************************************
*
*   @brief      Sets a priority to treap map element.
*
*   @def AaGpuSimpleTreapMapPriorSet
*
*   @param[in]  ___element Pointer to the element where data shall be set
*   @param[in]  ___prior   Pointer to the priority to set
*
*   @return     none
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
*
*   @code
*
*   // See AaGpuSimpleTreapMapAdd
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
*   @see AaGpuSimpleTreapMapElementInit
*   @see AaGpuSimpleTreapMapAdd
*   @see AaGpuSimpleTreapMapFind
*
******************************************************************************/
#define AaGpuSimpleTreapMapPriorSet(___element, ___prior) ((___element)->priority = ___prior)


/**
*******************************************************************************
*
*   @brief      Sets a data to map element.
*
*   @def AaGpuSimpleTreapMapDataSet
*
*   @param[in]  ___element Pointer to the element where data shall be set
*   @param[in]  ___data    Pointer to the data to set
*
*   @return     none
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
*
*   @code
*
*   // See AaGpuSimpleTreapMapAdd
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
*   @see AaGpuSimpleTreapMapElementInit
*   @see AaGpuSimpleTreapMapAdd
*   @see AaGpuSimpleTreapMapFind
*
******************************************************************************/
#define AaGpuSimpleTreapMapDataSet(___element, ___data) ((___element)->data = ___data)

/**
*******************************************************************************
*
*   @brief      Initializes treap map element prior adding
*
*   @def AaGpuSimpleTreapMapElementInit
*
*   @param[in]  ___element Pointer to the element to initialize
*   @param[in]  ___key     Pointer to the key to set
*   @param[in]  ___prior   Pointer to the priority to set
*   @param[in]  ___data    Pointer to the data to set
*
*   @return     none
*
*   @par Description:
*
*   Elements must be initilized prior to the adding of the to initialized
*   treap. This call does all necessary initializations at once for the element.
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
*   // See AaGpuSimpleTreapMapAdd
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
*   @see AaGpuSimpleTreapMapAdd
*   @see AaGpuSimpleTreapMapKeySet
*   @see AaGpuSimpleTreapMapDataSet
*
******************************************************************************/
#define AaGpuSimpleTreapMapElementInit(___element, ___key, ___prior, ___data) \
    AaGpuSimpleTreapMapKeySet(___element, ___key); \
    AaGpuSimpleTreapMapPriorSet(___element, ___prior); \
    AaGpuSimpleTreapMapDataSet(___element, ___data);


/**
*******************************************************************************
*
*   @brief      Gets a key from map element.
*
*   @def AaGpuSimpleTreapMapKeyGet
*
*   @param[in]  ___element Pointer to the element where data shall be get
*
*   @return     Element key
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
*
*   @code
*
*   // See AaGpuSimpleTreapMapFind
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
*   @see AaGpuSimpleTreapMapFind
*
******************************************************************************/
#define AaGpuSimpleTreapMapKeyGet(___element) ((___element)->key)

/**
*******************************************************************************
*
*   @brief      Gets a priority from treap element.
*
*   @def AaGpuSimpleTreapMapPriorGet
*
*   @param[in]  ___element Pointer to the element where priority shall be get
*
*   @return     Element priority
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
*
*   @code
*
*   // See AaGpuSimpleTreapMapFind
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
*   @see AaGpuSimpleTreapMapFind
*
******************************************************************************/
#define AaGpuSimpleTreapMapPriorGet(___element) ((___element)->priority)

/**
*******************************************************************************
*
*   @brief      Gets a data from map element.
*
*   @def AaGpuSimpleTreapMapDataGet
*
*   @param[in]  ___element Pointer to the element where data shall be get
*
*   @return     Element data
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
*
*   @code
*
*   // See AaGpuSimpleTreapMapFind
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
*   @see AaGpuSimpleTreapMapFind
*
******************************************************************************/
#define AaGpuSimpleTreapMapDataGet(___element) ((___element)->data)

/**
*******************************************************************************
*
*   @brief      Gets count of element currently in the tree
*
*   @def AaGpuSimpleTreapMapSize
*
*   @param[in]  ___handler Pointer to the handler of the tree
*
*   @return     Element count (unsigned int)
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
*
*   @code
*   
*   // See AaGpuSimpleTreapMapFind
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
*   @see AaGpuSimpleTreapMapInit
*   @see AaGpuSimpleTreapMapAdd
*   @see AaGpuSimpleTreapMapRemove
*   @see AaGpuSimpleTreapMapRemoveE
*   @see AaGpuSimpleTreapMapEmpty
*
******************************************************************************/
#define AaGpuSimpleTreapMapSize(___handler) ((___handler)->elements)


/**
*******************************************************************************
*
*   @brief      Returns GLO_TRUE if treap is empty
*
*   @def AaGpuSimpleTreapMapEmpty
*
*   @param[in]  ___handler Pointer to the handler of the treap
*
*   @return     If treap is empty (0 elemets) GLO_NULL, otherwice GLO_FALSE
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
*
*   @code
*
*   #include <IfAaGpuSimpleTreapMap.h>
*
*   SAaGpuSimpleTreapMapHandler handler;
*   SAaGpuSimpleTreapMapElement* e;
*
*   ...
*
*   while (!AaGpuSimpleTreapMapEmpty(&handler))
*   {
*       e = AaGpuSimpleTreapMapRemoveE(&handler, AaGpuSimpleTreapMapGetFirst(&handler));
*
*       // Free data and element memory allocations
*       ...
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
*   @see AaGpuSimpleTreapMapInit
*   @see AaGpuSimpleTreapMapAdd
*   @see AaGpuSimpleTreapMapRemove
*   @see AaGpuSimpleTreapMapRemoveE
*   @see AaGpuSimpleTreapMapSize
*
******************************************************************************/
#define AaGpuSimpleTreapMapEmpty(___handler) ((___handler)->elements == 0 ? GLO_TRUE : GLO_FALSE)





/**
 * @defgroup dgAaGpuSimpleTreapMapApi Simple Treap Map COMMON API
 * @ingroup  dgContainersApiCommon
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief   Adds an element to a treap
*
*   @param[in]  handler  Pointer to the handler of the tree map
*   @param[in]  element  Pointer to the element
*
*   @return     Colliding element or GLO_NULL.
*
*   @par Description:
*
*   If the element to be added collides with existing element it the treap, the
*   existing element shall be returned and the new element is added to the treap.
*   If no collision occurred, GLO_NULL is returned.
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
*   #include <IfAaGpuSimpleTreapMap.h>
*
*   // In this example element, key and priority is stored to the actual
*   // data
*   typedef struct
*   {
*       SAaGpuSimpleTreapMapElement element;
*       char*                       key;
*       u32                         priority;
*       void*                       data;
*       void*                       data1;
*       void*                       data2;
*   } SMyStruct
*   
*   SAaGpuSimpleTreapMapHandler handler;
*   SMyStruct                   myStruct;
*
*   // Init the tree
*   AaGpuSimpleTreapMapInit(&handler, 
*                           AaGpuSimpleTreapMapComparatorString, // Key is string
*                           AaGpuSimpleTreapMapComparatorU32);   // Priority is u32
*
*   // Init the structure
*   myStruct.key = "app.myapp.mykey";
*   myStruct.priority = 3
*   myStruct.data = ...
*   myStruct.data1 = ...
*   myStruct.data2 = ...
*
*   // Init the element in the struct
*   AaGpuSimpleTreapMapElementInit(&myStruct.element, 
*                                  &myStruct.key, 
*                                  &myStruct.priority, 
*                                  &myStruct); // Actual data of the element is the whole struct
*
*   // The other way to do element init is:
*   AaGpuSimpleTreapMapKeySet(&myStruct.element, &myStruct.key);
*   AaGpuSimpleTreapMapPriorSet(&myStruct.element, &myStruct.priority);
*   AaGpuSimpleTreapMapDataSet(&myStruct.element, &myStruct);
*
*
*   // Add element to the treap
*   if (AaGpuSimpleTreapMapAdd(&handler, &myStruct.element) != GLO_NULL)
*   {
*       // Collsion occurred according to the key
*   }
*
*   @endcode
*
*   @par Usage:
*
*   There is also helper macro #AaGpuSimpleTreapMapElementInit for initializing
*   new element before adding it to a treap.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaGpuSimpleTreapMapInit
*   @see AaGpuSimpleTreapMapElementInit
*   @see AaGpuSimpleTreapMapKeySet
*   @see AaGpuSimpleTreapMapPriorSet
*   @see AaGpuSimpleTreapMapDataSet
*
******************************************************************************/
SAaGpuSimpleTreapMapElement* 
AaGpuSimpleTreapMapAdd(SAaGpuSimpleTreapMapHandler* const handler, 
                       SAaGpuSimpleTreapMapElement* const element);


/**
*******************************************************************************
*
*   @brief   Tries to find an element corresponding given key
*
*   @param[in]  handler  Pointer to the handler
*   @param[in]  key      Pointer to the key
*
*   @return     Treap map element corresponding the key or GLO_NULL if not found
*
*   @par Description:
*
*   Searches the given tree map using comparator given during tree initilization.
*   Time for find operation is O(TDB).
*   
*   @par Errors:   
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuSimpleTreapMap.h>
*
*   SAaGpuSimpleTreapMapHandler handler;
*   char* key1 = "Key 1";
*   char* key2 = "Key 2";
*   char* data1 = "Data 1";
*   char* data2 = "Data 2";
*   char* prior1 = "Priority 1";
*   char* prior2 = "Priority 2";
*   SAaGpuSimpleTreapMapElement e1; // Elemets cannot be reused
*   SAaGpuSimpleTreapMapElement e2;
*   SAaGpuSimpleTreapMapElement* found;
*
*   // Init the tree (string comparator is used since key and priority are string)
*   AaGpuSimpleTreapMapInit(&handler, 
*                           AaGpuSimpleTreeMapComparatorString, 
*                           AaGpuSimpleTreeMapComparatorString);
*
*   // Add elements to the tree
*   AaGpuSimpleTreapMapElementInit(&e1, key1, prior1, data1);
*   AaGpuSimpleTreapMapAdd(&handler, &e1);
*
*   AaGpuSimpleTreapMapElementInit(&e2, key2, prior2, data2);
*   AaGpuSimpleTreapMapAdd(&handler, &e2);
*
*   // Find from the tree
*   found = AaGpuSimpleTreapMapFind(&handler, key2);
*
*   // Key, priority and data (addresses) of the found element should match to the ones added earlier
*   if ((AaGpuSimpleTreapMapKeyGet(found) == key2) &&
*       (AaGpuSimpleTreapMapPriorGet(found) == prior2) &&
*       (AaGpuSimpleTreapMapDataGet(found) == data2))
*   {
*      ...
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
*   @see AaGpuSimpleTreapMapAdd
*   @see AaGpuSimpleTreapMapElementInit
*   @see AaGpuSimpleTreapMapKeyGet
*   @see AaGpuSimpleTreapMapPriorGet
*   @see AaGpuSimpleTreapMapDataGet
*
******************************************************************************/
SAaGpuSimpleTreapMapElement* 
AaGpuSimpleTreapMapFind(const SAaGpuSimpleTreapMapHandler* const handler, const void* const key);


/**
*******************************************************************************
*
*   @brief   Returns the first element in the treap map
*
*   @param[in]  handler  Pointer to the handler
*
*   @return     First treap element or GLO_NULL
*
*   @par Description:
*
*   Returns the first element i.e. element in the far right i.e. the element with
*   the biggest key according to comparator. The key may not necessary be the biggest
*   in mathematical sense since the key comparator ultimately decides how the keys 
*   are interpreted.
*   
*   @par Errors:
*   GLO_NULL is returned is the treap is empty or the element is not part of 
*   the treap.   
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuSimpleTreapMap.h>
*
*   SAaGpuSimpleTreapMapHandler handler;
*   SAaGpuSimpleTreapMapElement* e;
*
*   ...
*
*   while ((e = AaGpuSimpleTreapMapGetFirst(&handler)) != GLO_NULL)
*   {
*       if (AaGpuSimpleTreapMapRemoveE(&handler, e) != e)
*       {
*           // Error. Removed element not found from the treap.
*       }
*
*       // Free key, priority, data and element memory allocations
*       ...
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
*   @see AaGpuSimpleTreapMapIteratorGet
*
******************************************************************************/
SAaGpuSimpleTreapMapElement* 
AaGpuSimpleTreapMapGetFirst(const SAaGpuSimpleTreapMapHandler* const handler);

/**
*******************************************************************************
*
*   @brief   Returns the element with the highest-priority
*
*   @param[in]  handler  Pointer to the handler
*
*   @return     The highest-priority element or GLO_NULL if treap map is empty
*
*   @par Description:
*
*   Returns the element which has the highest-priority according to comparator. 
*   The priority may not necessary be the highest in mathematical sense since 
*   the priority comparator ultimately decides how the priorities are interpreted.
*   
*   @par Errors:
*   None   
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   In this example, element are removed from the treap on priority order.
*   Since it is not possible to iterate treap in priority order this is also
*   only way to do similar operation however in destructive way.
*
*   @code
*
*   #include <IfAaGpuSimpleTreapMap.h>
*
*   SAaGpuSimpleTreapMapHandler handler;
*   SAaGpuSimpleTreapMapElement* elementPtr;
*   
*   // ... init and fill the treap ...
*
*   while ((elementPtr = AaGpuSimpleTreapMapGetHigh(&handler)) != GLO_NULL)
*   {
        // The removed element has the highes priority

*       if (elementPtr != AaGpuSimpleTreapMapRemoveE(&handler, elementPtr))
*       {
*           // Error. Remove failed
*           break;
*       }
*
*       // Use the removed element
*
*   } // while
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
*   @see AaGpuSimpleTreapMapRemoveE
*   @see AaGpuSimpleTreapMapGetFirst
*
******************************************************************************/
#define AaGpuSimpleTreapMapGetHigh(___handler) ((___handler)->root)


/**
*******************************************************************************
*
*   @brief  Returns new iterator to a given treap     
*
*   @param[in]  handler  Pointer to the handler of the treap map
*   @param[out] iterator Pointer to a placeholder for the iterator
*
*   @return     none
*
*   @par Description:
*
*   Iterator points to the far left (i.e. the biggest element according to a key).
*   The key may not necessary be the biggest in mathematical sense since the key 
*   comparator ultimately decides how the keys are interpreted.
*
*   @par Errors:
*   None   
*
*   @par Restrictions:
*
*   The behaviour of the iterator is undefined, if the backing treap has been 
*   structurally modified or priority-ordered after this function call. 
*   Structural modifications are those changes which affect to the size of the treap.
*
*   @par Example:
*
*   @code
*
*   // See AaGpuSimpleTreapMapIteratorNext
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
*   @see AaGpuSimpleTreapMapIteratorNext
*
******************************************************************************/
void 
AaGpuSimpleTreapMapIteratorGet(SAaGpuSimpleTreapMapHandler* const  handler, 
                               SAaGpuSimpleTreapMapIterator* const iterator);

/**
*******************************************************************************
*
*   @brief  Returns next element pointer by iterator or GLO_NULL    
*
*   @param[in]  iterator  Pointer to iterator
*
*   @return     Next element in the tree or GLO_NULL if no more elements left
*
*   @par Description:
*
*   @par Errors:   
*   None
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuSimpleTreapMap.h>
*
*   SAaGpuSimpleTreapMapHandler  handler;
*   SAaGpuSimpleTreapMapIterator i;
*   SAaGpuSimpleTreapMapElement* e;
*   void* data;
*
*   // Init the tree and add elements to it
*   ...
*
*   // Get iterator to the map
*   AaGpuSimpleTreapMapIteratorGet(&handler, &i);
*
*   // Iterate through the treap
*   while ((e = AaGpuSimpleTreapMapIteratorNext(&i)) != GLO_NULL)
*   {
*       data = AaGpuSimpleTreapMapDataGet(e);
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
*   @see AaGpuSimpleTreapMapIteratorGet
*
******************************************************************************/
SAaGpuSimpleTreapMapElement*
AaGpuSimpleTreapMapIteratorNext(SAaGpuSimpleTreapMapIterator* const iterator);


/**
*******************************************************************************
*
*   @brief  Updates a priority of an element corresponding the key and 
*           re-balances the treap
*
*   @param[in]  handler  Pointer to treap handler
*   @param[in]  key      Pointer to the key whose element is updated
*   @param[in]  priority Pointer to new priority of the element
*
*   @return     Pointer to previous priority or GLO_NULL
*
*   @par Description:
*
*   This call updated priority of an element corresponding to given key and 
*   returns the previous priority. After update, the treap is re-balanced 
*   according to the new priority.
*
*   @par Errors:   
*   
*   If an element corresponding to given key is not found from the given treap, 
*   GLO_NULL is returned.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuSimpleTreapMap.h>
*
*   SAaGpuSimpleTreapMapHandler handler;
*   void* key = ...;
*   void *oldPrior, *newPrior = ...;
*
*   ... init treap and add some elements ...
*   
*   oldPrior = AaGpuSimpleTreapMapPriorUpdate(&handler, key, newPrior);
*
*   if (oldPrior == GLO_NULL)
*   {
*       // Element, corresponding to the key, not found from the treap
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
*   @see AaGpuSimpleTreapMapPriorUpdateE
*
******************************************************************************/
void* 
AaGpuSimpleTreapMapPriorUpdate(SAaGpuSimpleTreapMapHandler* const handler, 
                               void const * const                 key,
                               void* const                        priority);


/**
*******************************************************************************
*
*   @brief  Updates a priority of an element and re-balances the treap
*
*   @param[in]  handler  Pointer to treap handler
*   @param[in]  element  Pointer to element to update
*   @param[in]  priority Pointer to new priority of the element
*
*   @return     Pointer to previous priority or GLO_NULL
*
*   @par Description:
*
*   This call updated priority of given element and returns the previous
*   priority. After update, the treap is re-balanced according to the
*   new priority.
*
*   @par Errors:   
*   
*   If the given element is not belonging to the given treap, GLO_NULL
*   is returned.
*
*   @par Restrictions:
*   None
*
*   @par Example:
*
*   @code
*
*   // See AaGpuSimpleTreapMapPriorUpdate
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
*   @see AaGpuSimpleTreapMapPriorUpdate
*
******************************************************************************/
void* 
AaGpuSimpleTreapMapPriorUpdateE(SAaGpuSimpleTreapMapHandler* const handler, 
                                SAaGpuSimpleTreapMapElement* const element,
                                void* const                        priority);

/**
*******************************************************************************
*
*   @brief  Removes element corresponding given key from the treap
*
*   @param[in]  handler  Pointer to the handler of the treap map
*   @param[in]  key      Pointer to the key
*
*   @return     Pointer to removed element
*
*   @par Description:
*
*   Time for remove operation is O(TBD).    
*
*   @par Errors:
*   None   
*
*   @par Restrictions:
*
*   After removing all iterators pointing to the treap must be considered 
*   invalid thus needs re-querying.
*
*   @par Example:
*
*   @code
*   
*   SAaGpuSimpleTreapMapHandler  handler;
*   SAaGpuSimpleTreapMapElement* e;
*   void* key = ...;
*
*   ...
*
*   if ((e = AaGpuSimpleTreapMapRemove(&handler, key)) != GLO_NULL)
*   {
*       // Free data, key, priority and element memory allocations
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
*   @see AaGpuSimpleTreeMapRemoveE
*
******************************************************************************/
SAaGpuSimpleTreapMapElement*
AaGpuSimpleTreapMapRemove(SAaGpuSimpleTreapMapHandler* const handler, const void* const key);


/**
*******************************************************************************
*
*   @brief  Removes given element from the tree    
*
*   @param[in]  handler  Pointer to the handler
*   @param[in]  element  Pointer to the element to be removed
*
*   @return     Pointer to removed element
*
*   @par Description:
*
*   Time for remove operation is O(TBD).    
*
*   @par Errors:
*   None   
*
*   @par Restrictions:
*
*   After removing all iterators pointing to the tree must be considered invalid thus needs 
*   re-querying.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuSimpleTreapMap.h>
*
*   SAaGpuSimpleTreapMapHandler  handler;
*   SAaGpuSimpleTreapMapElement* e;
*
*   ...
*
*   while ((e = AaGpuSimpleTreapMapGetFirst(&handler)) != GLO_NULL)
*   {
*       e = AaGpuSimpleTreapMapRemoveE(&handler, e);
*
*       // Free data, key, priority and element memory allocations
*       ...
*   }
*
*   @endcode
*
*   @par Usage:
*
*   It might be beneficial from performance point of view to use AaGpuSimpleTreapMapPrune()
*   when whole tree needs to be cleared and caller can access to the elements
*   in the tree by some other means than using the tree API.
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
SAaGpuSimpleTreapMapElement*
AaGpuSimpleTreapMapRemoveE(SAaGpuSimpleTreapMapHandler* const handler, 
                           SAaGpuSimpleTreapMapElement* const element);


/**
*******************************************************************************
*
*   @brief   Prunes internal data structure of the map
*
*   @param[in]  handler  Pointer to the handler of the treap map
*
*   @return     none
*
*   @par Description:
*
*   Internal data structure of the treap map is deleted by removing all elements
*   from the treap. It is callers responsibility to take care of releasing the
*   memory of every element after prune, which were existing in the treap prior 
*   to the prune call.
*   Since nothing is returned by this function, it is also callers responsibility
*   to ensure that the dynamically allocated elements are still reachable by the
*   caller for releasing, othervice memory leaks will occur. This of course applies 
*   also to data, priorities and keys of the elements. 
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
*   #include <IfAaGpuSimpleTreapMap.h>
*   #include <IfAaMem.h>
*
*   SAaGpuSimpleTreapMapHandler treap;
*   SAaGpuSimpleTreapMapElement* e;
*
*   // Init treap, allocate elements, data, priorities and keys and add them to the treap
*   e = (SAaGpuSimpleTreapMapElement*)AaMemMalloc(sizeof(SAaGpuSimpleTreapMapElement));
*   AaGpuSimpleTreapMapKeySet(&e1, ...);
*   AaGpuSimpleTreapMapPriorSet(&e1, ...);
*   AaGpuSimpleTreapMapDataSet(&e1, ...);
*   ...
*
*   // Prune the treap
*   AaGpuSimpleTreapMapPrune(&treap);
*
*   // Release the memory allocated for the elements (and data, prior, keys)
*   AaMemUnRef((void const ** const)&e);
*   ...   
*
*   @endcode
*
*   @par Usage:
*
*   When fast cleanup of all element of a treap is needed e.g. for treap reuse or
*   part of SW termination procedure, this function is faster than using 
*   paradigm introduced in AaGpuSimpleTreapMapRemoveE() example, if elements are
*   accessible by the user by some other means.
*
*   @par Rationale:
*
*   Since memory allocations for element are done by user, prune of the treap 
*   does not do any memory releasing instead user must do it since user also 
*   knows how the memory is allocated.
*
*   @par Future directions:
*   None
*
*   @see AaGpuSimpleTreapMapRemoveE
*
******************************************************************************/
void
AaGpuSimpleTreapMapPrune(SAaGpuSimpleTreapMapHandler* const handler);


/**
*******************************************************************************
*
*   @brief      Comparator implementation for unsigned 32bit values (u32)
*
*   @param[in]  value1  Value 1 
*   @param[in]  value2  Value 2
*
*   @return     See TAaGpuSimpleTreapMapComparator
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
*
*   @code
*
*   // See AaGpuSimpleTreapMapInit
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
int 
AaGpuSimpleTreapMapComparatorU32(const void* const value1, const void* const value2);

/**
*******************************************************************************
*
*   @brief      Comparator implementation for signed 32bit keys (i32)
*
*   @param[in]  key1  Key 1 
*   @param[in]  key2  Key 2
*
*   @return     See TAaGpuSimpleTreapMapComparator
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
*
*   @code
*
*   // See AaGpuSimpleTreapMapInit
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
*   @see AaGpuSimpleTreapMapInit
*
******************************************************************************/
int 
AaGpuSimpleTreapMapComparatorI32(const void* const key1, const void* const key2);


/**
*******************************************************************************
*
*   @brief      Comparator implementation for NULL-terminated string keys
*
*   @param[in]  key1  Key 1 
*   @param[in]  key2  Key 2
*
*   @return     See TAaGpuSimpleTreapMapComparator
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
*
*   @code
*
*   // See AaGpuSimpleTreapMapInit
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
*   @see AaGpuSimpleTreapMapInit
*
******************************************************************************/
int 
AaGpuSimpleTreapMapComparatorString(const void* const key1, const void* const key2);

/**
*******************************************************************************
*
*   @brief      Comparator implementation for address keys
*
*   @param[in]  key1  Key 1 
*   @param[in]  key2  Key 2
*
*   @return     See TAaGpuSimpleTreapMapComparator
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
*
*   @code
*
*   // See AaGpuSimpleTreapMapInit
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
*   @see AaGpuSimpleTreapMapInit
*
******************************************************************************/
int 
AaGpuSimpleTreapMapComparatorAddress(const void* const key1, const void* const key2);


/** @} */

#ifdef __cplusplus
}
#endif

/*@}*/


#endif /* _MCU_RT_IFAAGPUSIMPLETREAPMAP_H */

