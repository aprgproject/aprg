/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Simple Balanced B/R Tree API header file
* @module                AaGpu
* @owner                 Marcela Nemet
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAAGPUSIMPLETREEMAP_H
#define _IFAAGPUSIMPLETREEMAP_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
*@addtogroup dgAaGpuSimpleTreeMapApi Simple Tree Map
*@ingroup dgContainersApi
*
* Red-back tree -based implementation of binary search tree providing best worst
* case performance in various operations when compared to other binary search trees.
* Every node is a pair of key and data. The key can be arbitrary format since user
* can define comparator call-back function for key comparison.
*
* However if a string is used as a key type, @ref dgAaGpuSimpleTreeRadixApi may be
* more efficient than tree map with string comparator.
*
* @code
*
*                                    Key-ordered:
*              a
*        /-----5-----\                 iteration
*        b           c                 (c,9)
*    /---3---\   /---8---\             (c,8)
*    c       f   c       c             (c,6)
*    2       4   6       9             (a,5)
*                                      (f,4)
*                                      (b,3)
*                                      (c,2)
*  ------------KEY------------>
*
* @endcode
*
* This implementation uses sentinel element for the end of the subtree management.
* Data structure implementation is very fast and simple. No EE/EU synchronization
* is done thus user must do it if necessary.
*
* @note NULL elements and duplicated keys are not supported.
* @note Memory management is in user's responsibility.
*
* @warning NULL pointer checks are not done!
*
*@{*/

/**
*@defgroup dgAaGpuSimpleTreeMapApiExamples Application usage
*@ingroup dgAaGpuSimpleTreeMapApi
*
* Here are some application usage examples.
*
* <b>Data and key combined into same data structure:</b>
*
* @code
*
* struct SOwnData {
*    int   value1;
*    int   value2;
*    char  key[LENGTH];
* }
*
* SAaGpuSimpleTreeMapHandler tree;
* SAaGpuSimpleTreeMapElement e1;
* SOwnData                   d1;
* ...
*
* AaGpuSimpleTreeMapElementInit(&e1, &d1.key[0], &d1);
* AaGpuSimpleTreeMapAdd(&tree, &e1);
*
*
*    ---------
*   |    e1   |
*   | ------- |
*   |  DATA --+-----------> ---------
*   |  KEY  --+----\       |    d1   |
*    ---------     |       | ------- |
*                  |       |  value1 |
*                  |       |  value2 |
*                  \-------+->key    |
*                           ---------
*
* @endcode
*
* <b>Data, key and element combined into same data structure:</b>
*
* @code
*
* struct SOwnDataWithElement {
*    int                        value1;
*    SAaGpuSimpleTreeMapElement element;   // Element location in the hosting struct is not an issue
*    int                        value2;
*    char                       key[LENGTH];
* }
*
* SAaGpuSimpleTreeMapHandler tree;
* SOwnDataWithElement        d1;
* ...
*
* AaGpuSimpleTreeMapElementInit(&d1.element, &d1.key[0], &d1);
* AaGpuSimpleTreeMapAdd(&tree, &d1.element);
*
*
*          -----------------
*         |        d1       |<---\
*         | --------------- |    |
*         |     value1      |    |
*         |   -----------   |    |
*         |  |  element  |  |    |
*         |  | --------- |  |    |
*         |  |   DATA ---+--+----/
*         |  |   KEY  ---+--+----\
*         |   -----------   |    |
*         |     value2      |    |
*         |     key <-------+----/
*          -----------------
*
* @endcode
*
*/

/*----------------------- INCLUDED FILES -------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif



/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @brief Bi-state comparator definition for key comparsion
* @param[in] key1  Pointer to a key to compare
* @param[in] key2  Pointer to another key to compare key1 with
*
* @return If key1 is smaller that key2, #AAGPUSIMPLETREEMAP_COMPARATOR_LESS
* @return If key1 is equal or greater than key2, #AAGPUSIMPLETREEMAP_COMPARATOR_NONLESS
*/
typedef int TAaGpuSimpleTreeMapComparator(const void* const key1, const void* const key2);

/** @brief Returned by comparator when key1 is smaller than key2
* @see TAaGpuSimpleTreeMapComparator
*/
#define AAGPUSIMPLETREEMAP_COMPARATOR_LESS    1
/** @brief Returned by comparator when key1 is equal or greater than key2
* @see TAaGpuSimpleTreeMapComparator
*/
#define AAGPUSIMPLETREEMAP_COMPARATOR_NONLESS 0

/** @brief Tree element color definition */
typedef enum EAaGpuSimpleTreeMapColor
{
    EAaGpuSimpleTreeMapColor_Black = 1, /**< Set first value to something else than 0 for debugging purposes */
    EAaGpuSimpleTreeMapColor_Red = 2,
    EAaGpuSimpleTreeMapColor_Invalid /**< Used for marking element invalid */

} EAaGpuSimpleTreeMapColor;

/** @brief Tree element with map support */
typedef struct SAaGpuSimpleTreeMapElement
{
    /* Tree related members */
    struct SAaGpuSimpleTreeMapElement* left;   /**< Pointer to leftmost child element of current element (real element or sentinel; never GLO_NULL) */
    struct SAaGpuSimpleTreeMapElement* right;  /**< Pointer to rightmost child element of current element (real element or sentinel; never GLO_NULL) */
    struct SAaGpuSimpleTreeMapElement* parent; /**< Pointer to parent element of current element (real element or GLO_NULL if current is root) */

    EAaGpuSimpleTreeMapColor           color;  /**< Color of the element */


    /* Map related members */
    void*                              key;    /**< Pointer to user-specific key (may NOT be GLO_NULL) */
    void*                              data;   /**< Pointer to user-specific data (may be GLO_NULL) */

} SAaGpuSimpleTreeMapElement;

/** @brief Handler for tree map */
typedef struct SAaGpuSimpleTreeMapHandler
{
    TAaGpuSimpleTreeMapComparator* comparator;/**< Comparator for tree map element key comparison */

    SAaGpuSimpleTreeMapElement*    root;      /**< The first element of the map (not necessary smallest/greatest) */
    SAaGpuSimpleTreeMapElement     sentinel;  /**< For helping to manage the end of the subtree and conserves memory */
    unsigned int                   elements;  /**< Number of elements currently in the map */

} SAaGpuSimpleTreeMapHandler;

/** @brief Iterator definition for fast tree passing */
typedef struct SAaGpuSimpleTreeMapIterator
{
    SAaGpuSimpleTreeMapHandler* handler; /**< Pointer to the handler of the tree to being iterated */

    SAaGpuSimpleTreeMapElement* current; /**< Pointer to element where iteration is currently ongoing */
    SAaGpuSimpleTreeMapElement* first;   /**< Pointer to element where iteration started */

    int                         level;   /**< Iteration depth for debugging purpose. Might be negative. */

} SAaGpuSimpleTreeMapIterator;


/*----------------------- PUBLIC INTERFACES --------------------------------*/

/**
 * @defgroup dgAaGpuSimpleTreeMapApi Simple Tree Map COMMON API
 * @ingroup  dgContainersApiCommon
 */

/* @{ */


/**
*******************************************************************************
*
*   @brief      Initializes tree map handler.
*
*   @param[in]  handler    Pointer to an handler to initialize
*   @param[in]  comparator Comparator function pointer to be used for this tree map
*
*   @return     none
*
*   @par Description:
*   Initializes given tree map handler.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   None
*
*   @par Example:
*   None
*
*   @code
*
*     #include <IfAaGpuSimpleTreeMap.h>
*
*     SAaGpuSimpleTreeMapHandler tree;
*
*     // Init the tree for string-type keys
*     AaGpuSimpleTreeMapInit(&tree, AaGpuSimpleTreeMapComparatorString);
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
*   @see AaGpuSimpleTreeMapAdd
*   @see AaGpuSimpleTreeMapRemove
*   @see AaGpuSimpleTreeMapPrune
*   @see AaGpuSimpleTreeMapComparatorU32
*   @see AaGpuSimpleTreeMapComparatorI32
*   @see AaGpuSimpleTreeMapComparatorAddress
*   @see AaGpuSimpleTreeMapComparatorString
*
******************************************************************************/
void
AaGpuSimpleTreeMapInit(SAaGpuSimpleTreeMapHandler* const handler,
                       TAaGpuSimpleTreeMapComparator* const comparator);


/** @} */

/**
*******************************************************************************
*
*   @brief      Sets a key to map element.
*
*   @def AaGpuSimpleTreeMapKeySet
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
*   // See AaGpuSimpleTreeMapFind
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
*   @see AaGpuSimpleTreeMapElementInit
*   @see AaGpuSimpleTreeMapAdd
*   @see AaGpuSimpleTreeMapFind
*
******************************************************************************/
#define AaGpuSimpleTreeMapKeySet(___element, ___key) (___element)->key = ___key


/**
*******************************************************************************
*
*   @brief      Sets a data to map element.
*
*   @def AaGpuSimpleTreeMapDataSet
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
*   // See AaGpuSimpleTreeMapFind
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
*   @see AaGpuSimpleTreeMapElementInit
*   @see AaGpuSimpleTreeMapAdd
*   @see AaGpuSimpleTreeMapFind
*
******************************************************************************/
#define AaGpuSimpleTreeMapDataSet(___element, ___data) (___element)->data = ___data


/**
*******************************************************************************
*
*   @brief      Initializes tree map element prior adding
*
*   @def AaGpuSimpleTreeMapElementInit
*
*   @param[in]  ___element Pointer to the element to initialize
*   @param[in]  ___key     Pointer to the key to set
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
*   // See AaGpuSimpleTreeMapFind
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
*   @see AaGpuSimpleTreeMapAdd
*   @see AaGpuSimpleTreeMapKeySet
*   @see AaGpuSimpleTreeMapDataSet
*
******************************************************************************/
#define AaGpuSimpleTreeMapElementInit(___element, ___key, ___data) \
    AaGpuSimpleTreeMapKeySet(___element, ___key); \
    AaGpuSimpleTreeMapDataSet(___element, ___data);


/**
*******************************************************************************
*
*   @brief      Gets a key from map element.
*
*   @def AaGpuSimpleTreeMapKeyGet
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
*   // See AaGpuSimpleTreeMapFind
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
*   @see AaGpuSimpleTreeMapFind
*
******************************************************************************/
#define AaGpuSimpleTreeMapKeyGet(___element) ((___element)->key)

/**
*******************************************************************************
*
*   @brief      Gets a data from map element.
*
*   @def AaGpuSimpleTreeMapDataGet
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
*   // See AaGpuSimpleTreeMapFind
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
*   @see AaGpuSimpleTreeMapFind
*
******************************************************************************/
#define AaGpuSimpleTreeMapDataGet(___element) ((___element)->data)

/**
*******************************************************************************
*
*   @brief      Gets count of element currently in the tree
*
*   @def AaGpuSimpleTreeMapSize
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
*   // See AaGpuSimpleTreeMapAdd
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
*   @see AaGpuSimpleTreeMapInit
*   @see AaGpuSimpleTreeMapAdd
*   @see AaGpuSimpleTreeMapRemove
*   @see AaGpuSimpleTreeMapRemoveE
*   @see AaGpuSimpleTreeMapEmpty
*
******************************************************************************/
#define AaGpuSimpleTreeMapSize(___handler) ((___handler)->elements)

/**
*******************************************************************************
*
*   @brief      Returns GLO_TRUE if tree is empty
*
*   @def AaGpuSimpleTreeMapEmpty
*
*   @param[in]  ___handler Pointer to the handler of the tree
*
*   @return     If tree is empty (0 elemets) GLO_NULL, otherwice GLO_FALSE
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
*     #include <IfAaGpuSimpleTreeMap.h>
*
*     SAaGpuSimpleTreeMapHandler tree;
*     SAaGpuSimpleTreeMapElement* e;
*
*     ...
*
*     while (!AaGpuSimpleTreeMapEmpty(&tree))
*     {
*       e = AaGpuSimpleTreeMapRemoveE(&tree, AaGpuSimpleTreeMapGetFirst(&tree));
*
*       // Free data and element memory allocations
*       ...
*     }
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
*   @see AaGpuSimpleTreeMapInit
*   @see AaGpuSimpleTreeMapAdd
*   @see AaGpuSimpleTreeMapRemove
*   @see AaGpuSimpleTreeMapRemoveE
*   @see AaGpuSimpleTreeMapSize
*
******************************************************************************/
#define AaGpuSimpleTreeMapEmpty(___handler) ((___handler)->elements == 0 ? GLO_TRUE : GLO_FALSE)


/**
*******************************************************************************
*
*   @brief   Adds an element to a tree map
*
*   @param[in]  handler  Pointer to the handler of the tree map
*   @param[in]  element  Pointer to the element
*
*   @return     Colliding element or GLO_NULL.
*
*   @par Description:
*   If the element to be added collides with existing element it the tree, the
*   existing element shall be returned and the new element is added to the tree.
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
*     #include <IfAaGpuSimpleTreeMap.h>
*
*     SAaGpuSimpleTreeMapHandler tree;
*     char* key1 = "Key 1";
*     char* key2 = "Key 2";
*     char* data1 = "Data 1";
*     char* data2 = "Data 2";
*     SAaGpuSimpleTreeMapElement e1; // Elemets cannot be reused
*     SAaGpuSimpleTreeMapElement e2;
*     SAaGpuSimpleTreeMapElement* colliding;
*     size_t count;
*
*     // Init the tree
*     AaGpuSimpleTreeMapInit(&tree, AaGpuSimpleTreeMapComparatorString);
*
*     // Add elements to the tree
*     AaGpuSimpleTreeMapKeySet(&e1, key1);
*     AaGpuSimpleTreeMapDataSet(&e1, data1);
*     colliding = AaGpuSimpleTreeMapAdd(&tree, &e1);
*
*     if (colliding != GLO_NULL) {
*       // Handle the previous element in the tree; now replaced by
*       // the new one
*     }
*
*     AaGpuSimpleTreeMapKeySet(&e2, key2);
*     AaGpuSimpleTreeMapDataSet(&e2, data2);
*     colliding = AaGpuSimpleTreeMapAdd(&tree, &e2);
*
*     if (colliding != GLO_NULL) {
*       // Handle the previous element in the tree; now replaced by
*       // the new one
*     }
*
*     count = AaGpuSimpleTreeMapSize(&tree); // Count should be 2
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
*   Actually colliding element is not currently returned in contrast to the
*   documentation. So if someone implements that, please remove these remarks too.
*
*   @see AaGpuSimpleTreeMapInit
*   @see AaGpuSimpleTreeMapRemoveE
*
******************************************************************************/
SAaGpuSimpleTreeMapElement*
AaGpuSimpleTreeMapAdd(SAaGpuSimpleTreeMapHandler* const handler,
                      SAaGpuSimpleTreeMapElement* const element);


/**
*******************************************************************************
*
*   @brief   Tries to find an element corresponding given key
*
*   @param[in]  handler  Pointer to the handler of the tree map
*   @param[in]  key      Pointer to the key
*
*   @return     Tree map element corresponding the key or GLO_NULL if not found
*
*   @par Description:
*   Searches the given tree map using comparator given during tree initilization.
*   Time for find operation is O(log n).
*
*   @par Errors:
*
*   @par Restrictions:
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuSimpleTreeMap.h>
*
*   SAaGpuSimpleTreeMapHandler tree;
*   char* key1 = "Key 1";
*   char* key2 = "Key 2";
*   char* data1 = "Data 1";
*   char* data2 = "Data 2";
*   SAaGpuSimpleTreeMapElement e1; // Elemets cannot be reused
*   SAaGpuSimpleTreeMapElement e2;
*   SAaGpuSimpleTreeMapElement* found;
*
*   // Init the tree (string comparator is used since keys are string)
*   AaGpuSimpleTreeMapInit(&tree, AaGpuSimpleTreeMapComparatorString);
*
*   // Add elements to the tree
*   AaGpuSimpleTreeMapKeySet(&e1, key1);
*   AaGpuSimpleTreeMapDataSet(&e1, data1);
*   AaGpuSimpleTreeMapAdd(&tree, &e1);
*
*   AaGpuSimpleTreeMapKeySet(&e2, key2);
*   AaGpuSimpleTreeMapDataSet(&e2, data2);
*   AaGpuSimpleTreeMapAdd(&tree, &e2);
*
*   // Find from the tree
*   found = AaGpuSimpleTreeMapFind(&tree, key2);
*
*   // Key and data (addresses) of the found element should match to the ones added earlier
*   if ((AaGpuSimpleTreeMapKeyGet(found) == key2) &&
        (AaGpuSimpleTreeMapDataGet(found) == data2))
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
*   @see AaGpuSimpleTreeMapAdd
*   @see AaGpuSimpleTreeMapIteratorGet
*
******************************************************************************/
SAaGpuSimpleTreeMapElement*
AaGpuSimpleTreeMapFind(const SAaGpuSimpleTreeMapHandler* const handler, const void* const key);

/**
*******************************************************************************
*
*   @brief   Returns the first element in the tree map
*
*   @param[in]  handler  Pointer to the handler of the tree map
*
*   @return     Tree map element or GLO_NULL if tree map is empty
*
*   @par Description:
*   Returns the first element i.e. element in the far left i.e. the element with
*   smallest key according to comparator.
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
*     #include <IfAaGpuSimpleTreeMap.h>
*
*     SAaGpuSimpleTreeMapHandler tree;
*     SAaGpuSimpleTreeMapElement* e;
*
*     ...
*
*     // Clean up tree map
*     while ((e = AaGpuSimpleTreeMapGetFirst(&tree)) != GLO_NULL)
*     {
*       AaGpuSimpleTreeMapRemoveE(&tree, e);
*       // Free data and element memory allocations of e
*       ...
*     }
*
*   @endcode
*
*   @par Usage:
*   Especially useful for cleaning up the tree map.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaGpuSimpleTreeMapIteratorGet
*
******************************************************************************/
SAaGpuSimpleTreeMapElement*
AaGpuSimpleTreeMapGetFirst(const SAaGpuSimpleTreeMapHandler* const handler);


/**
*******************************************************************************
*
*   @brief  Returns new iterator to a given tree
*
*   @param[in]  handler  Pointer to the handler of the tree map
*   @param[out] iterator Pointer to a placeholder for the iterator
*
*   @return     none
*
*   @par Description:
*   Iterator points to the far left (i.e. smalles element according to a key).
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The behavior of the iterator is undefined, if the backing tree has been
*   structurally modified after this function call. Structural modifications
*   are those changes which affect to the size of the tree or the tree layout.
*
*   @par Example:
*
*   @code
*
*     #include <IfAaGpuSimpleTreeMap.h>
*
*     SAaGpuSimpleTreeMapHandler tree;
*     SAaGpuSimpleTreeMapIterator i;
*     SAaGpuSimpleTreeMapElement* e;
*     void* data;
*
*     // Init the tree and add elements to it
*     ...
*
*     // Get iterator to the map
*     AaGpuSimpleTreeMapIteratorGet(&tree, &i);
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
*   @see AaGpuSimpleTreeMapIteratorNext
*
******************************************************************************/
void
AaGpuSimpleTreeMapIteratorGet(SAaGpuSimpleTreeMapHandler* const handler,
                              SAaGpuSimpleTreeMapIterator* const iterator);

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
*   This function travels a tree using given iterator from left to right (i.e. from
*   the smallest element to the greatest according to key). When far right is reached and
*   no more elements are left to iterate, GLO_NULL is returned.
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   The behavior of the iterator is undefined, if the backing tree has been
*   structurally modified after this function call. Structural modifications
*   are those changes which affect to the size of the tree or the tree layout.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuSimpleTreeMap.h>
*
*   SAaGpuSimpleTreeMapHandler tree;
*   SAaGpuSimpleTreeMapIterator i;
*   SAaGpuSimpleTreeMapElement* e;
*   void* data;
*
*   // Init the tree and add elements to it
*   ...
*
*   // Get iterator to the map
*   AaGpuSimpleTreeMapIteratorGet(&tree, &i);
*
*   // Iterate through the tree
*   while ((e = AaGpuSimpleTreeMapIteratorNext(&i)) != GLO_NULL)
*   {
*       data = AaGpuSimpleTreeMapDataGet(e);
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
*   @see AaGpuSimpleTreeMapIteratorGet
*
******************************************************************************/
SAaGpuSimpleTreeMapElement*
AaGpuSimpleTreeMapIteratorNext(SAaGpuSimpleTreeMapIterator* const iterator);

/**
*******************************************************************************
*
*   @brief   Return GLO_TRUE if there is elements to iterate
*
*   @deprecated
*   Current implementation is quite slow, so it is not recommend to use this function
*   instead use #AaGpuSimpleTreeMapIteratorNext as described in the example of
*   #AaGpuSimpleTreeMapIteratorNext.
*
*   @param[in]  iterator  Pointer to iterator
*
*   @return     GLO_TRUE if there are element to iterate in the iterator or GLO_NULL
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
*   #include <IfAaGpuSimpleTreeMap.h>
*
*   SAaGpuSimpleTreeMapHandler tree;
*   SAaGpuSimpleTreeMapIterator i;
*   SAaGpuSimpleTreeMapElement* e;
*   void* data;
*
*   // Init the tree and add elements to it
*   ...
*
*   // Get iterator to the map
*   AaGpuSimpleTreeMapIteratorGet(&tree, &i);
*
*   // Iterate through the tree
*   while (AaGpuSimpleTreeMapIteratorHasNext(&i) == GLO_TRUE)
*   {
*       e = AaGpuSimpleTreeMapIteratorNext(&i);
*       data = AaGpuSimpleTreeMapDataGet(e);
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
*   @see AaGpuSimpleTreeMapIteratorGet
*   @see AaGpuSimpleTreeMapIteratorNext
*
******************************************************************************/
unsigned int
AaGpuSimpleTreeMapIteratorHasNext(SAaGpuSimpleTreeMapIterator* const iterator);

/**
*******************************************************************************
*
*   @brief  Removes element corresponding given key from the tree
*
*   @param[in]  handler  Pointer to the handler of the tree map
*   @param[in]  key      Pointer to the key
*
*   @return     Pointer to removed element or GLO_NULL if not exist
*
*   @par Description:
*   Time for remove operation is O(log n).
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   There is no more restrictions what comes to given and returned element. They
*   are now the same so no need to store returned element anymore.
*   After removing all iterators pointing to the tree must be considered invalid
*   thus needs re-querying.
*
*   @par Example:
*
*   @code
*
*     #include <IfAaGpuSimpleTreeMap.h>
*
*     SAaGpuSimpleTreeMapHandler tree;
*     SAaGpuSimpleTreeMapElement* e;
*     void* key = ...;
*
*     ...
*
*     if ((e = AaGpuSimpleTreeMapRemove(&tree, key)) != GLO_NULL) {
*       // Free data and element memory allocations of e
*     } else {
*       // Element corresponding the key not found from the tree
*     }
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
*   @see AaGpuSimpleTreeMapRemoveE
*
******************************************************************************/
SAaGpuSimpleTreeMapElement*
AaGpuSimpleTreeMapRemove(SAaGpuSimpleTreeMapHandler* const handler, const void* const key);

/**
*******************************************************************************
*
*   @brief  Removes given element from the tree
*
*   @param[in]  handler  Pointer to the handler of the tree map
*   @param[in]  element  Pointer to the element
*
*   @return     Pointer to removed element (always same as #element or GLO_NULL)
*
*   @par Description:
*   Time for remove operation is O(log n).
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   There is no more restrictions what comes to given and returned element. They
*   are now the same so no need to store returned element anymore.
*   After removing all iterators pointing to the tree must be considered invalid
*   thus needs re-querying.
*
*   @par Example:
*
*   @code
*
*     #include <IfAaGpuSimpleTreeMap.h>
*
*     SAaGpuSimpleTreeMapHandler tree;
*     SAaGpuSimpleTreeMapElement* e;
*
*     ...
*
*     while ((e = AaGpuSimpleTreeMapGetFirst(&tree)) != GLO_NULL)
*     {
*       if (e == AaGpuSimpleTreeMapRemoveE(&tree, e)) {
*         // Free data and element memory allocations
*       } else {
*         // Should not happen
*       }
*       ...
*     }
*
*   @endcode
*
*   @par Usage:
*   It might be beneficial from performance point of view to use AaGpuSimpleTreeMapPrune()
*   when whole tree needs to be cleared and caller can access to the elements
*   in the tree by some other means than using the tree API.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaGpuSimpleTreeMapRemove
*   @see AaGpuSimpleTreeMapPrune
*
******************************************************************************/
SAaGpuSimpleTreeMapElement*
AaGpuSimpleTreeMapRemoveE(SAaGpuSimpleTreeMapHandler* const handler,
                          SAaGpuSimpleTreeMapElement* const element);


/**
*******************************************************************************
*
*   @brief   Prunes internal data structure of the tree map
*
*   @param[in]  handler  Pointer to the handler of the tree map
*
*   @return     none
*
*   @par Description:
*   Internal data structure of the tree map is deleted by removing all elements
*   from the tree. It is callers responsibility to take care of releasing the
*   memory of every element after prune, which were existing in the tree prior
*   to the prune process.
*   Since nothing is returned by this function, it is also callers responsibility
*   to ensure that the dynamically allocated elements are still reachable by the
*   caller for releasing, otherwise memory leaks will occur. This of course applies
*   also to data and keys of the elements.
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
*   #include <IfAaGpuSimpleTreeMap.h>
*   #include <IfAaMem.h>
*
*   SAaGpuSimpleTreeMapHandler tree;
*   SAaGpuSimpleTreeMapElement* e;
*
*   // Init tree, allocate elements, data and keys and add them to the tree
*   e = (SAaGpuSimpleTreeMapElement*)AaMemMalloc(sizeof(SAaGpuSimpleTreeMapElement));
*   AaGpuSimpleTreeMapKeySet(&e1, ...);
*   AaGpuSimpleTreeMapDataSet(&e1, ...);
*   ...
*
*   // Prune the tree
*   AaGpuSimpleTreeMapPrune(&tree);
*
*   // Release the memory allocated for the elements (and data, keys)
*   AaMemUnRef((void const ** const)&e);
*   ...
*
*   @endcode
*
*   @par Usage:
*   When fast cleanup of all element of a tree is needed e.g. for tree reuse or
*   part of SW termination procedure, this function is faster than using
*   paradigm introduced in AaGpuSimpleTreeMapRemoveE() example, if elements are
*   accessible by the user by some other means.
*
*   @par Rationale:
*   Since memory allocations for element are done by user, prune of the tree
*   does not do any memory releasing instead user must do it since user also
*   knows how the memory is allocated.
*
*   @par Future directions:
*   None
*
*   @see AaGpuSimpleTreeMapRemoveE
*
******************************************************************************/
void
AaGpuSimpleTreeMapPrune(SAaGpuSimpleTreeMapHandler* const handler);


/**
*******************************************************************************
*
*   @brief  Moves given element from a tree and to another tree
*
*   @param[in]  from     Pointer to the handler of the source tree map
*   @param[in]  to       Pointer to the handler of the destination tree map
*   @param[in]  key      Pointer to the key
*
*   @return     Pointer to moved element or GLO_NULL.
*
*   @par Description:
*   Moves an element from a tree map to another tree map identified by given key.
*   Moved element is returned, if found from source tree or GLO_NULL if not found.
*   If the destination tree already contains colliding element, the element is
*   silently replaced, thus user must always ensure that the destination tree
*   does not have an element with matching key.
*
*   @par Errors:
*   If an element corresponding to the given key is not found, GLO_NULL is returned
*   and no moving takes place.
*
*   @par Restrictions:
*   After moving all iterators pointing to both trees must be considered invalid
*   thus needs re-querying.
*
*   Both tree maps must have same type of key.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuSimpleTreeMap.h>
*
*   SAaGpuSimpleTreeMapHandler tree1;
*   SAaGpuSimpleTreeMapHandler tree2;
*   char* key1 = "Key 1";
*   char* key2 = "Key 2";
*   char* data1 = "Data 1";
*   char* data2 = "Data 2";
*   SAaGpuSimpleTreeMapElement e1; // Elemets cannot be reused
*   SAaGpuSimpleTreeMapElement e2;
*   SAaGpuSimpleTreeMapElement* moved;
*   SAaGpuSimpleTreeMapElement* found;
*
*   // Init the tree (string comparator is used since keys are string)
*   AaGpuSimpleTreeMapInit(&tree1, AaGpuSimpleTreeMapComparatorString);
*   AaGpuSimpleTreeMapInit(&tree2, AaGpuSimpleTreeMapComparatorString);
*
*   // Add elements to the tree1
*   AaGpuSimpleTreeMapKeySet(&e1, key1);
*   AaGpuSimpleTreeMapDataSet(&e1, data1);
*   AaGpuSimpleTreeMapAdd(&tree1, &e1);
*
*   AaGpuSimpleTreeMapKeySet(&e2, key2);
*   AaGpuSimpleTreeMapDataSet(&e2, data2);
*   AaGpuSimpleTreeMapAdd(&tree1, &e2);
*
*   // Move from the tree1 to tree2
*   moved = AaGpuSimpleTreeMapMove(&tree1, &tree2, key2);
*
*   // Find for the tree2
*   found = AaGpuSimpleTreeMapFind(&tree2, key2);
*
*   // Found element should match to the one moved earlier
*   if (found == moved)
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
*   @see AaGpuSimpleTreeMapAdd
*   @see AaGpuSimpleTreeMapRemoveE
*
******************************************************************************/
SAaGpuSimpleTreeMapElement*
AaGpuSimpleTreeMapMove(SAaGpuSimpleTreeMapHandler* const from,
                       SAaGpuSimpleTreeMapHandler* const to,
                       const void* const key);

/**
*******************************************************************************
*
*   @brief      Comparator implementation for unsigned 32bit keys (u32)
*
*   @param[in]  key1  Key 1
*   @param[in]  key2  Key 2
*
*   @return     See TAaGpuSimpleTreeMapComparator
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
*   // See AaGpuSimpleTreeMapInit
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
*   @see AaGpuSimpleTreeMapInit
*
******************************************************************************/
int
AaGpuSimpleTreeMapComparatorU32(const void* const key1, const void* const key2);

/**
*******************************************************************************
*
*   @brief      Comparator implementation for signed 32bit keys (i32)
*
*   @param[in]  key1  Key 1
*   @param[in]  key2  Key 2
*
*   @return     See TAaGpuSimpleTreeMapComparator
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
*   // See AaGpuSimpleTreeMapInit
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
*   @see AaGpuSimpleTreeMapInit
*
******************************************************************************/
int
AaGpuSimpleTreeMapComparatorI32(const void* const key1, const void* const key2);


/**
*******************************************************************************
*
*   @brief      Comparator implementation for NULL-terminated string keys
*
*   @param[in]  key1  Key 1
*   @param[in]  key2  Key 2
*
*   @return     See TAaGpuSimpleTreeMapComparator
*
*   @par Description:
*   If planning to use strings as keys, refer to Radix Tree
*   AaGpuSimpleTreeRadix (see @ref dgAaGpuSimpleTreeRadixApi).
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
*   // See AaGpuSimpleTreeMapInit
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
*   @see AaGpuSimpleTreeMapInit
*
******************************************************************************/
int
AaGpuSimpleTreeMapComparatorString(const void* const key1, const void* const key2);

/**
*******************************************************************************
*
*   @brief      Comparator implementation for address keys
*
*   @param[in]  key1  Key 1
*   @param[in]  key2  Key 2
*
*   @return     See TAaGpuSimpleTreeMapComparator
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
*   // See AaGpuSimpleTreeMapInit
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
*   @see AaGpuSimpleTreeMapInit
*
******************************************************************************/
int
AaGpuSimpleTreeMapComparatorAddress(const void* const key1, const void* const key2);



#ifdef __cplusplus
}
#endif

/*@}*/


#endif /* _IFAAGPUSIMPLETREEMAP_H */

