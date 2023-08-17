/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Simple Radix Tree Map API header file
* @module                AaGpu
* @owner                 Marcela Nemet
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _IFAAGPUSIMPLETREERADIX_H
#define _IFAAGPUSIMPLETREERADIX_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
*@addtogroup dgAaGpuSimpleTreeRadixApi Simple Radix Map
*@ingroup dgContainersApi
*
* This is a Patricia Trie implementation focused on string type keys.
* The main idea is to implement tree map -like structure optimized for
* character array -like keys.
*
* More information about Radix (Patricia) trees see:
* http://en.wikipedia.org/wiki/Radix_tree
*
* @note Correct name for the service would be AaGpuSimpleRadixMap
*       according to naming rules.
*
* @warning All iterators to certain radix map instance shall be considered
*          invalid after adding or removing an element. 
*
* @warning Since implementation uses standard type definitions e.g. size_t, allocator
*          implementation should take consideration the fact that current AaMem API
*          uses legacy u32 for allocation size parameter type. In 64bit machines
*          u32 and size_t may be incompatible. Therefore type cast is required and
*          effective size for allocation is limited atleast to size of u32 (also
*          the used pool and the system may limit the size).
*
* @warning Recusion is used in AaGpuSimpleTreeRadixSet(), AaGpuSimpleTreeRadixAdd() 
*          and AaGpuSimpleTreeRadixIteratorNext(). Be very careful when handling trees
*          from untrusted sources. <b>I MEAN IT!</b>
*
* @todo More API documentation and example codes.
*
*@{*/

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <stddef.h>
#include <IfAaGpuSimpleLinkedList.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/** @brief Radix map allocator type definition
* @param[in] opaque  Pointer to implementation specific data or GLO_NULL
*/
typedef void* TAaGpuSimpleTreeRadixAllocator  (void* const opaque, const size_t size);

/** @brief Radix map unallocator type definition
* @param[in] opaque  Pointer to implementation specific data or GLO_NULL
*/
typedef void  TAaGpuSimpleTreeRadixUnallocator(void* const opaque, void* const ptr);


/** @brief Radix map (Patricia trie) element  */
typedef struct SAaGpuSimpleTreeRadixElement
{
    char*  key;  /**< User provided key (never GLO_NULL) */
    void*  data; /**< User provided data (may be GLO_NULL) */

    /** @todo Add pointer back to node to support faster AaGpuSimpleTreeRadixRemoveE */

} SAaGpuSimpleTreeRadixElement;

/** @brief Radix map (Patricia trie) node (or in some cases pure junction node) */
typedef struct SAaGpuSimpleTreeRadixNode
{
    struct SAaGpuSimpleTreeRadixNode* parent;     /**< Parent node for iterator support */
    
    /* Patricia (radix) trie related members (for internal usage) */
    SAaGpuSimpleLinkedListElement  list;          /**< List for subnode handling (of type SAaGpuSimpleTreeRadixNode) */    
    SAaGpuSimpleLinkedListElement  subnodes;      /**< Subnode list (of type SAaGpuSimpleTreeRadixNode) */
    char                           discriminator; /**< Discriminator for fast comparison */
    char*                          prefix;        /**< Prefix of the current element or subnodes in this node */
    
    /* User provided element */
    SAaGpuSimpleTreeRadixElement*  element; /**< User provided element (is GLO_NULL if this is a pure junction node) */

} SAaGpuSimpleTreeRadixNode;


/** @brief Handler for radix map (Patricia trie) */
typedef struct SAaGpuSimpleTreeRadixHandler
{
    TAaGpuSimpleTreeRadixAllocator*   allocator;   /**< Allocator for internal map memory allocations */
    TAaGpuSimpleTreeRadixUnallocator* unallocator; /**< Unallocator for internal map memory allocations */
    void*                             opaque;      /**< Pointer to implementation specific data or GLO_NULL */

    SAaGpuSimpleTreeRadixNode         root;        /**< The first node of the map (for internal usage) */
    unsigned int                      elements;    /**< Number of _elements_ currently in the map (there may be more nodes) */

} SAaGpuSimpleTreeRadixHandler;


/** @brief Interator for convient radix map iteration */
typedef struct SAaGpuSimpleTreeRadixIterator
{

    SAaGpuSimpleTreeRadixHandler*   handler;   /**< Pointer to the radix map handler to iterate */

    SAaGpuSimpleTreeRadixNode*      rootNode;  /**< Root radix map node to support finding of child nodes */
    SAaGpuSimpleTreeRadixNode*      currNode;  /**< Current iterated radix map node */
    int                             level;     /**< Current level of the iterator depth (for debugging) */

} SAaGpuSimpleTreeRadixIterator;

/*----------------------- PUBLIC INTERFACES --------------------------------*/


/**
 * @defgroup dgAaGpuSimpleTreeRadixApi Simple Radix Map COMMON API
 * @ingroup  dgContainersApiCommon
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief      AaGpuSimpleTreeRadixInit initializes radix map handler.
*
*   @param[in]  element      Pointer to an handler to initialize
*   @param[in]  allocator    Pointer to allocator implementation
*   @param[in]  unallocator  Pointer to unallocator implementation
*   @param[in]  opaque       Pointer to implemetation specific data
*
*   @return     none
*
*   @par Description:
*   Initilizes given radix map handler. Allocation and unallocation
*   call-backs must always be given. They are called during certain map 
*   operations.
* 
*   @par
*   There are two types of allocations, which may take place during 
*   map-related operations:
*      - Radix map node allocations
*      - Prefix string allocations
* 
*   @par
*   With this information, allocator (and unallocator) call-backs can
*   be optimized for different allocations sizes. Radix map nodes
*   are always sizeof(SAaGpuSimpleTreeRadixNode) but prefix strings
*   depends purely on used keys.
*   
*   @par
*   Parameter opaque can be used to pass allocator/unallocator specific data.
*   If the implementations do not need any special data, opaque can be GLO_NULL.
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
*   // Simple allocator example (opaque not in use)
*   static void* SimpleRadixAllocator(void* const opaque, const size_t size)
*   {
*       return AaMemMalloc((u32)size);
*   }
* 
*   // More advanced allocator example (opaque not in use)
*   static void* AdvRadixAllocator(void* const opaque, const size_t size)
*   {
*       if (size == sizeof(SAaGpuSimpleTreeRadixNode)
*       {
*           // Allocation probably for radix map node so
*           // use special space optimized pool
*           return AaMemAlloc(optimizedPoolId, (u32)size);
*       }
* 
*       return AaMemMalloc((u32)size);
*   }
*
*   // This unallocator should work with simple and advanced
*   // allocator examples (opaque not in use)
*   static void RadixUnallocator(void* const opaque, void* const ptr)
*   {
*       AaMemUnRef(&ptr);
*   }
* 
*   ...
*  
*   SAaGpuSimpleTreeRadixHandler handler;
* 
*   AaGpuSimpleTreeRadixInit(&handler, SimpleRadixAllocator, RadixUnallocator, GLO_NULL);
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
void 
AaGpuSimpleTreeRadixInit(SAaGpuSimpleTreeRadixHandler* const handler,
                         TAaGpuSimpleTreeRadixAllocator* const allocator,
                         TAaGpuSimpleTreeRadixUnallocator* const unallocator,
                         void* const opaque);



/** @} */

/**
*******************************************************************************
*
*   @brief      AaGpuSimpleTreeRadixKeySet sets a key to map element.
*
*   @def  AaGpuSimpleTreeRadixKeySet    
*
*   @param[in]  ___element Pointer to the element where key shall be set
*   @param[in]  ___key     Pointer to the key to set
*
*   @return     none
*
*   @par Description:
*   Sets a pointer to a NULL-terminated string key to an element.
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
#define AaGpuSimpleTreeRadixKeySet(___element, ___key) (___element)->key = (___key)

/**
*******************************************************************************
*
*   @brief      AaGpuSimpleTreeRadixDataSet sets a data to map element.
*
*   @def AaGpuSimpleTreeRadixDataSet
*
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
#define AaGpuSimpleTreeRadixDataSet(___element, ___data) (___element)->data = (___data)
    
/**
*******************************************************************************
*
*   @brief      AaGpuSimpleTreeRadixKeyGet gets a key from map element.
*
*   @def AaGpuSimpleTreeRadixKeyGet
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
#define AaGpuSimpleTreeRadixKeyGet(___element) ((___element)->key)

/**
*******************************************************************************
*
*   @brief      AaGpuSimpleTreeRadixDataGet gets a data from map element.
*
*   @def AaGpuSimpleTreeRadixDataGet
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
#define AaGpuSimpleTreeRadixDataGet(___element) ((___element)->data)

/**
*******************************************************************************
*
*   @brief      AaGpuSimpleTreeRadixSize gets count of element currently in the map
*
*   @def AaGpuSimpleTreeRadixSize
*
*   @param[in]  ___handler Pointer to the handler of the map
*
*   @return     Element count
*
*   @par Description:
*   Returns current nunber of elements in the map. There may be more nodes
*   in the map since radix map needs pure junction nodes, which contains
*   no user-specific data.
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
#define AaGpuSimpleTreeRadixSize(___handler) ((___handler)->elements)

/**
*******************************************************************************
*
*   @brief      AaGpuSimpleTreeRadixEmpty returns GLO_TRUE if map is empty
*
*   @def AaGpuSimpleTreeRadixEmpty
*
*   @param[in]  ___handler Pointer to the handler of the map
*
*   @return     If map is empty (0 elemets) GLO_NULL, otherwice GLO_FALSE
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
#define AaGpuSimpleTreeRadixEmpty(___handler) ((___handler)->elements == 0 ? GLO_TRUE : GLO_FALSE)




/**
 * @defgroup dgAaGpuSimpleTreeRadixApi Simple Radix Map COMMON API
 * @ingroup  dgContainersApiCommon
 */

/* @{ */


/**
*******************************************************************************
*
*   @brief   AaGpuSimpleTreeRadixAdd adds an element to a radix map   
*
*   @param[in]  handler  Pointer to the handler of the radix map
*   @param[in]  element  Pointer to the element to add
*
*   @return     Colliding element or GLO_NULL.
*
*   @par Description:
*   The element must contain valid key (NULL-terminated string). According to
*   the key, the element is added into the map. Time for add operation is O(k).
*   If the element to be added collides with existing element it the map, the
*   existing element shall be returned and the new element is added to the map.
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
*   SAaGpuSimpleTreeRadixHandler handler;
*   SAaGpuSimpleTreeRadixElement e1;
*   SAaGpuSimpleTreeRadixElement e2;
*   SAaGpuSimpleTreeRadixElement* colliding;
* 
*   AaGpuSimpleTreeRadixKeySet(&e1, "key 1");
*   AaGpuSimpleTreeRadixDataSet(&e1, "data 1");
*   AaGpuSimpleTreeRadixKeySet(&e2, "key 2");
*   AaGpuSimpleTreeRadixDataSet(&e2, "data 2");
* 
*   AaGpuSimpleTreeRadixInit(&handler, SimpleRadixAllocator, RadixUnallocator, GLO_NULL);
* 
*   colliding = AaGpuSimpleTreeRadixAdd(&handler, &e1);
*   if (colliding != GLO_NULL) {
*       // Handle the previous element in the map; now replaced by 
*       // the new one
*   }
*
*   colliding = AaGpuSimpleTreeRadixAdd(&handler, &e2);
*   if (colliding != GLO_NULL) {
*       // Handle the previous element in the map; now replaced by 
*       // the new one
*   }
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
*   @see AaGpuSimpleTreeRadixInit
*
******************************************************************************/
SAaGpuSimpleTreeRadixElement* 
AaGpuSimpleTreeRadixAdd(SAaGpuSimpleTreeRadixHandler* const handler, 
                        SAaGpuSimpleTreeRadixElement* const element);


/**
*******************************************************************************
*
*   @brief   AaGpuSimpleTreeRadixFind tries to find a element corresponding given key
*
*   @param[in]  handler  Pointer to the handler of the radix map
*   @param[in]  key      Pointer to the NULL-terminated key string
*
*   @return     Radix map element corresponding the key or GLO_NULL if not found
*
*   @par Description:
*   Time for find operation is O(k).
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
*   SAaGpuSimpleTreeRadixHandler handler;
*   SAaGpuSimpleTreeRadixElement e1;
*   SAaGpuSimpleTreeRadixElement e2;
*   SAaGpuSimpleTreeRadixElement* ePtr;
* 
*   AaGpuSimpleTreeRadixKeySet(&e1, "key 1");
*   AaGpuSimpleTreeRadixDataSet(&e1, "data 1");
*   AaGpuSimpleTreeRadixKeySet(&e2, "key 2");
*   AaGpuSimpleTreeRadixDataSet(&e2, "data 2");
* 
*   AaGpuSimpleTreeRadixInit(&handler, SimpleRadixAllocator, RadixUnallocator, GLO_NULL);
* 
*   AaGpuSimpleTreeRadixAdd(&handler, &e1);
*   AaGpuSimpleTreeRadixAdd(&handler, &e2);
* 
*   ePtr = AaGpuSimpleTreeRadixFind(&handler, "key 1");
* 
*   // Returned pointer should point to earlier set element
*   if (ePtr == &e1)
*   {
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
*   @see 
*
******************************************************************************/
SAaGpuSimpleTreeRadixElement* 
AaGpuSimpleTreeRadixFind(const SAaGpuSimpleTreeRadixHandler* const handler, 
                         const char* const key);

/**
*******************************************************************************
*
*   @brief   AaGpuSimpleTreeRadixGetFirst returns the first element in the radix map
*
*   @param[in]  handler  Pointer to the handler of the radix map
*
*   @return     Radix map element or GLO_NULL if the radix map is empty
*
*   @par Description:
*   Returns arbitrary element in the map i.e. the first element for radix map
*   implementation point of view. Particular order according to key is NOT 
*   guaranteed.
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
SAaGpuSimpleTreeRadixElement* 
AaGpuSimpleTreeRadixGetFirst(const SAaGpuSimpleTreeRadixHandler* const handler);


/**
*******************************************************************************
*
*   @brief  AaGpuSimpleTreeRadixIteratorGet returns new iterator to a given map
*
*   @param[in]  handler  Pointer to the handler of the radix map
*   @param[out] iterator Pointer to a placeholder for the iterator
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
*   Iterating of radix map does not guarantee that the order of iterated
*   elements is ascend or descent. Instead the order is undefined. 
*   \n\n
*   The behaviour of the iterator is undefined, if the backing radix has been 
*   structurally modified after this function call. Structural modifications
*   are those changes which affect to the size or layout of the radix.
*   
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
*   @see AaGpuSimpleTreeRadixPrefixIteratorGet
*   @see AaGpuSimpleTreeRadixIteratorNext
*
******************************************************************************/
void 
AaGpuSimpleTreeRadixIteratorGet(SAaGpuSimpleTreeRadixHandler* const handler, 
                                SAaGpuSimpleTreeRadixIterator* const iterator);

/**
*******************************************************************************
*
*   @brief  AaGpuSimpleTreeRadixPrefixIteratorGet returns new prefix iterator to 
*           a given radix map
*
*   @param[in]  handler  Pointer to the handler of the radix map
*   @param[in]  prefix   Pointer to the NULL-terminated prefix key string
*   @param[out] iterator Pointer to a placeholder for the iterator
*
*   @return     None
*
*   @par Description:
*   This function returns an iterator which can be used for iterating all elements
*   matching to the given prefix. Perfect match is also included into iteration i.e.
*   if the map contains element with key "sys.eth0" and prefix is set to "sys.eth0", 
*   that element is included into the iteration.
* 
*   @par Errors:
*   None   
*
*   @par Restrictions:
*   Iterating of radix map does not guarantee that the order of iterated
*   elements is ascend or descent. Instead the order is undefined. 
*   \n\n
*   The behaviour of the iterator is undefined, if the backing radix has been 
*   structurally modified after this function call. Structural modifications
*   are those changes which affect to the size or layout of the radix.
* 
*   @par Example:
*
*   @code
*
*   SAaGpuSimpleTreeRadixHandler handler;
*   SAaGpuSimpleTreeRadixIterator iterator;
* 
*   // ... add element to the radix map ...
* 
*   // Initialize prefix iterator and iterate through the elements of radix map
*   // which have "sys.net.eth0." prefix.
*   AaGpuSimpleTreeRadixPrefixIteratorGet(&handler, "sys.net.eth0.", &iterator);
*    
*   while ((e = AaGpuSimpleTreeRadixIteratorNext(&iterator)) != GLO_NULL)
*   {
*       // In this example we assume that the data is string type
*       AaSysLogPrint(EAaSysLogSeverityLevel_Info, "key: (%s), data: (%s)", 
*           AaGpuSimpleTreeRadixKeyGet(e), AaGpuSimpleTreeRadixDataGet(e)); 
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
*   @see AaGpuSimpleTreeRadixIteratorGet
*   @see AaGpuSimpleTreeRadixIteratorNext
*
******************************************************************************/
void 
AaGpuSimpleTreeRadixPrefixIteratorGet(SAaGpuSimpleTreeRadixHandler* const handler,
                                      const char* const prefix,
                                      SAaGpuSimpleTreeRadixIterator* const iterator);

/**
*******************************************************************************
*
*   @brief  AaGpuSimpleTreeRadixIteratorNext returns next element pointed by iterator    
*
*   @param[in]  iterator  Pointer to iterator
*
*   @return     Next element in the map or GLO_NULL if no more elements left
*
*   @par Description:
*   None
*
*   @par Errors:
*   None
*
*   @par Restrictions:
*   If elements are added or removed from the radix map, iterator should be
*   considered as invalid and needs re-querying. See AaGpuSimpleTreeRadixIteratorGet.
*
*   @par Example:
*
*   @code
*
*   SAaGpuSimpleTreeRadixHandler handler;
*   SAaGpuSimpleTreeRadixIterator iterator;
* 
*   // ... add elements to the radix map ...
* 
*   // Initialize iterator and iterate through the radix map
*   AaGpuSimpleTreeRadixIteratorGet(&handler, &iterator);
*    
*   while ((e = AaGpuSimpleTreeRadixIteratorNext(&iterator)) != GLO_NULL)
*   {
*       // In this example we assume that the data is string type
*       AaSysLogPrint(EAaSysLogSeverityLevel_Info, "key: (%s), data: (%s)", 
*           AaGpuSimpleTreeRadixKeyGet(e), AaGpuSimpleTreeRadixDataGet(e)); 
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
*   @see AaGpuSimpleTreeRadixIteratorGet
*   @see AaGpuSimpleTreeRadixPrefixIteratorGet
*
******************************************************************************/
SAaGpuSimpleTreeRadixElement*
AaGpuSimpleTreeRadixIteratorNext(SAaGpuSimpleTreeRadixIterator* const iterator);

/**
*******************************************************************************
*
*   @brief  AaGpuSimpleTreeRadixRemove removes element corresponding given key from the map
*
*   @param[in]  handler  Pointer to the handler of the radix map
*   @param[in]  key      Pointer to the key string
*
*   @return     Pointer to removed element
*
*   @par Description:
*   Time for remove operation is O(k).
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
*   SAaGpuSimpleTreeRadixHandler  handler;
*   SAaGpuSimpleTreeRadixElement* element;
*   char* key;
*   void* data;
* 
*   // ... add elements to the radix map ...
* 
*   // Remove an element from the map, which has key "sys.net.eth0.ip"
*   element = AaGpuSimpleTreeRadixRemove(&handler, "sys.net.eth0.ip");
*
*   // Get key and data from the element
*   key = AaGpuSimpleTreeRadixKeyGet(element);
*   data = AaGpuSimpleTreeRadixDataGet(element);
*
*   // Free memory allocated for the element
*   AaMemUnRef((void const ** const)&key);
*   AaMemUnRef((void const ** const)&data);
*   AaMemUnRef((void const ** const)&element);
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
SAaGpuSimpleTreeRadixElement*
AaGpuSimpleTreeRadixRemove(SAaGpuSimpleTreeRadixHandler* const handler, 
                           const char* const key);

/**
*******************************************************************************
*
*   @brief  AaGpuSimpleTreeRadixRemoveE removes given element from the map    
*
*   @param[in]  handler  Pointer to the handler of the radix map
*   @param[in]  element  Pointer to the element to be removed
*
*   @return     Pointer to removed element
*
*   @par Description:
*   Time for remove operation is O(k).
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
*   SAaGpuSimpleTreeRadixHandler radix;
*   SAaGpuSimpleTreeRadixElement* e;
*
*   ...
*
*   // Empty radix map
*   while ((e = AaGpuSimpleTreeRadixGetFirst(&radix)) != GLO_NULL)
*   {
*       e = AaGpuSimpleTreeRadixRemoveE(&radix, e);
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
*   @see 
*
******************************************************************************/
SAaGpuSimpleTreeRadixElement*
AaGpuSimpleTreeRadixRemoveE(SAaGpuSimpleTreeRadixHandler* const handler, 
                            SAaGpuSimpleTreeRadixElement* const element);


/**
*******************************************************************************
*
*   @brief  AaGpuSimpleTreeRadixMove moves given element from a map to another map
*
*   @param[in]  from     Pointer to the handler of the source radix map
*   @param[in]  to       Pointer to the handler of the destination radix map
*   @param[in]  key      Pointer to the key string
*
*   @return     Pointer to moved element in the destination radix map or GLO_NULL
*
*   @par Description:
*   Time for move operation is O(k). GLO_NULL is returned, if matching element 
*   not found. If the destination map already contains colliding element, 
*   the element is silently replaced, thus user must always ensure that the 
*   destination map does not have an element with matching key.
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
SAaGpuSimpleTreeRadixElement*
AaGpuSimpleTreeRadixMove(SAaGpuSimpleTreeRadixHandler* const from, 
                         SAaGpuSimpleTreeRadixHandler* const to,
                         const char* const key);



/** @} */

#ifdef __cplusplus
}
#endif

/*@}*/


#endif /* _IFAAGPUSIMPLETREERADIX_H */

