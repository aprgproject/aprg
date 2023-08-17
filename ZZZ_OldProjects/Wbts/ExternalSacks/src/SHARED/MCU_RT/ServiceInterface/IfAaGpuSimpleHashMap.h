/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Simple Hash Map API header file
* @module                AaGpu
* @owner                 Marcela Nemet
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAGPUSIMPLEHASHMAP_H
#define _MCU_RT_IFAAGPUSIMPLEHASHMAP_H
#include "CcsCommon.h"

/*----------------------- DOXYGEN GROUPS -------------------------------------*/

/**
*@addtogroup dgAaGpuSimpleHashMapApi Simple Hash Map
*@ingroup dgContainersApi
*
* Hash map uses keys to calculate an index (using hasher and modulo) to a location 
* in an array of buckets. Every bucket is a pointer to a element in the map thus 
* the bucket has valid pointer in case the bucket is in use and non-valid in case
* the bucket is not in use. There may be several elements under same bucket (collision) 
* if the element keys causes hasher to generate suitable value to cause collision. 
* However every element in the hash map must have unique key.
*
* Collisions in hash map are possible and they are resolved using 
* <i>direct chaining</i> i.e. elements are not stored to hash table itself and colliding
* elements are linked to gether using linked list. Due to this, worst case time 
* is <i>O(n)</i>. AaGpuSimpleLinkedList is used to handle the colliding element 
* list inside a bucket. Since it is doubly-linked list, it allows faster element 
* removal (worst case <i>O(1)</i>) than single-linked (worst case <i>O(n)</i>) 
* but takes extra space of one word per bucket and element.
*
*
* @code
*
*      [0]   [1]   [2]   [3]   [4]   [5]   [6]   [7]    (index)
*    |xxxxx|xxxxx|nnnnn|xxxxx|xxxxx|nnnnn|xxxxx|nnnnn|  (buckets)
*       |     |           |     |           |
*     [0,0] [2,0]       [3,0] [4,0]       [6,0]         (elements)
*       |                 |     |           |
*     [0,1]             [3,1] [4,1]       [6,1]
*                         |
*                       [3,2]
*
* Iteration order: [0,0];[0,1];[2,0];[3,0];[3,1];[3,2];[4,0]; ...etc...
*
* Empty buckets are marked with <i>nnnnn</i> and buckets pointing to at least 
* one element are marked with <i>xxxxx</i>.
* 
* @endcode
*
* @par Hash function
*
* Selection of hash function is critical from performance point of view.
* In Wikipedia there is an article covering the issue at http://en.wikipedia.org/wiki/Hash_function.
* Basically user-defined hasher function should generate index from given key
* to a hash table.
*
* @code
*
*  input:     hasher      output:
*    A --------f(x)-------> 1
*    C --------f(x)-------> 5
*    K --------f(x)-------> 3
*    W --------f(x)-------> 1
*
* @endcode 
* 
*
* @par Resizing
*
* If element count in the hash map exceeds #AAGPUSIMPLEHASHMAP_MAX_USAGE_FACTOR
* of the total hash table size (count of buckets), the hash table is enlarged 
* and the elements are relocated according to the new size. If element count goes
* below #AAGPUSIMPLEHASHMAP_MIN_USAGE_FACTOR of the total has table size, the
* hash table size is decreased and the elements are relocated according to 
* the new size. By selecting initial size for the hash map, need for resize
* is postponed or totally avoided since resize operation may be potentially
* expensive. Hashing is done every time when resize takes place per element. 
* Pre-defined sizes for hash table is based on prime numbers and user defined
* size is rounded up to the nearest value.
*
* @warning NULL pointer checks are not done!
*
* @todo Study of using power-of-2 table sizes and bit masking in index generation.
* 
*@{*/

/*----------------------- INCLUDED FILES -------------------------------------*/

#include <IfAaGpuSimpleLinkedList.h>

#include <glo_def.h> /* For u32 and i32 */
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/


/**@brief Default max usage factor in percents
*
* Value derived form Wikipedia: http://en.wikipedia.org/wiki/Hash_table 
*/
#ifndef AAGPUSIMPLEHASHMAP_MAX_USAGE_FACTOR
# define AAGPUSIMPLEHASHMAP_MAX_USAGE_FACTOR 70
#endif

/**@brief Default min usage factor in percents */
#ifndef AAGPUSIMPLEHASHMAP_MIN_USAGE_FACTOR
# define AAGPUSIMPLEHASHMAP_MIN_USAGE_FACTOR 5
#endif

/** @brief Comparator definition for key comparsion 
* 
* @param[in] key1  Pointer to a key to compare
* @param[in] key2  Pointer to a key to compare with
* 
* @return If key1 is equal to key2, #AAGPUSIMPLEHASHMAP_COMPARATOR_EQUAL
* @return If key1 is NOT equal to key2, #AAGPUSIMPLEHASHMAP_COMPARATOR_NON_EQUAL
*/
typedef int TAaGpuSimpleHashMapComparator(const void* const key1, const void* const key2);

#define AAGPUSIMPLEHASHMAP_COMPARATOR_EQUAL      0 /**< key1 is equal to key2 */
#define AAGPUSIMPLEHASHMAP_COMPARATOR_NON_EQUAL -1 /**< key1 is NOT equal to key2 */

/** @brief Type definition for hash value */
typedef size_t TAaGpuSimpleHashMapHash;

/** @brief Generates hash value from given key
* 
* @param[in] key  Pointer to a key to hash
* @param[in] max  Maximum value for the hash (minimum is 0)
* 
* @return Generated hash value (index)
*/
typedef TAaGpuSimpleHashMapHash TAaGpuSimpleHashMapHasher(const void* const key, const size_t max );

/** @brief Hash map allocator callback typedef
*  
* @param[in] opaque  Pointer to implementation specific data or GLO_NULL
* @param[in] size    Size of the requested allocation in bytes
* @param[in] ptr     Pointer to a memory block to unallocate
* 
*/
typedef void* TAaGpuSimpleHashMapAllocator  (void* const opaque, const size_t size);

/** @brief Hash map unallocator callback typedef
*  
*
* @param[in] opaque  Pointer to implementation specific data or GLO_NULL
* @param[in] ptr     Pointer to a memory block to unallocate
* 
*/
typedef void  TAaGpuSimpleHashMapUnallocator(void* const opaque, void* const ptr);

/** @brief Hash map element */
typedef struct SAaGpuSimpleHashMapElement
{
    struct SAaGpuSimpleLinkedListElement  list; /**< Linked list of element having same hash code */
    
    void*                                 key;  /**< Pointer to user provided key */
    void*                                 data; /**< Pointer to user provided data */
    
} SAaGpuSimpleHashMapElement;

/** @brief Handler for hash map */
typedef struct SAaGpuSimpleHashMapHandler
{
    SAaGpuSimpleLinkedListElement*  table;      /**< Pointer to array of linked list elements of buckets */
    size_t                          size;       /**< Size of the hash map element pointer array */
    size_t                          elements;   /**< Number of elements currently in the map */

    TAaGpuSimpleHashMapHasher*      hasher;     /**< Hasher for hash map key */
    TAaGpuSimpleHashMapComparator*  comparator; /**< Comparator for hash map keys */
    TAaGpuSimpleHashMapAllocator*   allocator;  /**< Memory block allocator */
    TAaGpuSimpleHashMapUnallocator* unallocator;/**< Memory block unallocator */
    void*                           opaque;     /**< Opaque for memory block allocator and unallocator */
    
    int                             usageFactorMax; /**< Maximum usage size in percents when enlargement takes place */
    int                             usageFactorMin; /**< Minimum usage size in percents when downsizing takes place */ 

} SAaGpuSimpleHashMapHandler;

/** @brief Iterator definition for fast hash map passing */
typedef struct SAaGpuSimpleHashMapIterator
{
    SAaGpuSimpleHashMapHandler* handler; /**< Handler of the hash map under iteration */

    SAaGpuSimpleHashMapElement* current; /**< Current element to be iterated */
    size_t                      index;   /**< Index of the bucket currently under iteration */

    int                         level;   /**< Iteration depth inside a bucket for debugging purpose. */

} SAaGpuSimpleHashMapIterator;


/*----------------------- PUBLIC INTERFACES --------------------------------*/


/**
 * @defgroup dgAaGpuSimpleHashMapApi Simple Hash Map COMMON API
 * @ingroup  dgContainersApiCommon
 */

/* @{ */

/**
*******************************************************************************
*
*   @brief    Initializes hash map handler
*
*   @param[in]  handler      Pointer to an handler to initialize
*   @param[in]  hasher       Key hasher function
*   @param[in]  comparator   Key comparator function
*   @param[in]  allocator    Allocator function
*   @param[in]  unallocator  Unallocator function
*   @param[in]  opaque       Pointer to allocator and unallocator implementation 
*                             related opaque data
*   @param[in]  size         Estimated initial size for the table
*
*   @return     none
*
*   @par Description:
*   Initializes given handler. Also hash table is allocated and the size of
*   the table is based on given #size. However actual allocated size may
*   be larger that the requested one (rounded up). 
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
*   #include <IfAaGpuSimpleHashMap.h>
*   #include <IfAaMem.h>
*
*   // Allocator example (opaque not in use)
*   static void* HashAllocator(void* const opaque, const size_t size)
*   {
*       return AaMemMalloc((u32)size);
*   }
* 
*   // Unallocator example (opaque not in use)
*   static void HashUnallocator(void* const opaque, void* const ptr)
*   {
*       AaMemUnRef(&ptr);
*   }
*
*
*   SAaGpuSimpleHashMapHandler map;
*
*   // Init the map
*   AaGpuSimpleHashMapInit(&map, 
*                          AaGpuSimpleHashMapHasherU32, 
*                          AaGpuSimpleHashMapComparatorU32, 
*                          HashAllocator, 
*                          HashUnallocator, 
*                          100); // Start with 100 elements (may be rounded up)
*
*   @endcode
*
*   @par Usage:
*   Initial size for the table should be <i>1.25 or 1.45</i> times the expected 
*   data count. E.g. if there is assumed to be 150 elements in the hash map, then 
*   initial size should be between <i>188 (1.25*150) and 218 (1.45*150)</i> 
*   depending how accurate the estimation is expected to be.
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
AaGpuSimpleHashMapInit(SAaGpuSimpleHashMapHandler* const handler,
                       TAaGpuSimpleHashMapHasher* hasher,
                       TAaGpuSimpleHashMapComparator* comparator,
                       TAaGpuSimpleHashMapAllocator* allocator,
                       TAaGpuSimpleHashMapUnallocator* unallocator,
                       void* const opaque,
                       const size_t size);


/**
*******************************************************************************
*
*   @brief  Returns new iterator to a given map     
*
*   @param[in]  handler  Pointer to the handler of the map
*   @param[out] iterator Pointer to a placeholder for the iterator
*
*   @return     none
*
*   @par Description:
*   Iterator points to the far left (i.e. smalles element according to index).   
*
*   @par Errors:
*   None   
*
*   @par Restrictions:
*   The behaviour of the iterator is undefined, if the backing hash map has been 
*   structurally modified after this function call. Structural modifications
*   are those changes which affect to the size or element count of the hash map.
*
*   @par Example:
*
*   @code
*
*   // See AaGpuSimpleHashMapIteratorNext
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
*   @see AaGpuSimpleHashMapIteratorNext
*
******************************************************************************/
void 
AaGpuSimpleHashMapIteratorGet(SAaGpuSimpleHashMapHandler* const handler, 
                              SAaGpuSimpleHashMapIterator* const iterator);

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
*   This function travels a hash map using given iterator from left to right 
*   (i.e. from smalles index to the greatest). When far right is reached and
*   no more elements are left to iterate, GLO_NULL is returned. Order of the
*   iteration is not quaranteed since element order is heavily dependent on
*   hasher, the size of the hash table and order which the elements were added.
*
*   @par Errors:   
*   None
*
*   @par Restrictions:
*   The behaviour of the iterator is undefined, if the backing hash map has been 
*   structurally modified after this function call. Structural modifications
*   are those changes which affect to the size or element count of the hash map.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuSimpleHashMap.h>
*
*   SAaGpuSimpleTreeHashHandler map;
*   SAaGpuSimpleTreeHashIterator i;
*   SAaGpuSimpleTreeHashElement* e;
*   void* data;
*
*   // Init the hash map and add elements to it
*   ...
*
*   // Get iterator to the map
*   AaGpuSimpleHashMapIteratorGet(&map, &i);
*
*   // Iterate through the map
*   while ((e = AaGpuSimpleHashMapIteratorNext(&i)) != GLO_NULL)
*   {
*       data = AaGpuSimpleHashMapDataGet(e);
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
*   @see AaGpuSimpleHashMapIteratorGet
*
******************************************************************************/
SAaGpuSimpleHashMapElement*
AaGpuSimpleHashMapIteratorNext(SAaGpuSimpleHashMapIterator* const iterator);



/**
*******************************************************************************
*
*   @brief      Gets count of element currently in the map
*
*   @def AaGpuSimpleHashMapSize
*
*   @param[in]  ___handler Pointer to the handler of the map
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
*   // See AaGpuSimpleHashMapAdd
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
*   @see AaGpuSimpleHashMapInit
*   @see AaGpuSimpleHashMapAdd
*   @see AaGpuSimpleHashMapRemove
*   @see AaGpuSimpleHashMapRemoveE
*   @see AaGpuSimpleHashMapEmpty
*
******************************************************************************/
#define AaGpuSimpleHashMapSize(___handler) ((___handler)->elements)


/**
*******************************************************************************
*
*   @brief      Sets a key to map element.
*
*   @def AaGpuSimpleHashMapKeySet
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
*   // See AaGpuSimpleHashMapAdd
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
*   @see AaGpuSimpleHashMapElementInit
*   @see AaGpuSimpleHashMapAdd
*   @see AaGpuSimpleHashMapFind
*
******************************************************************************/
#define AaGpuSimpleHashMapKeySet(___element, ___key) ((___element)->key = (___key))


/**
*******************************************************************************
*
*   @brief      Sets a data to map element.
*
*   @def AaGpuSimpleHashMapDataSet
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
*   // See AaGpuSimpleHashMapAdd
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
*   @see AaGpuSimpleHashMapElementInit
*   @see AaGpuSimpleHashMapAdd
*   @see AaGpuSimpleHashMapFind
*
******************************************************************************/
#define AaGpuSimpleHashMapDataSet(___element, ___data) ((___element)->data = (___data))


/**
*******************************************************************************
*
*   @brief      Initializes hash map element prior adding
*
*   @def AaGpuSimpleHashMapElementInit
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
*   // See AaGpuSimpleHashMapAdd
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
*   @see AaGpuSimpleHashMapAdd
*   @see AaGpuSimpleHashMapKeySet
*   @see AaGpuSimpleHashMapDataSet
*
******************************************************************************/
#define AaGpuSimpleHashMapElementInit(___element, ___key, ___data) \
    AaGpuSimpleHashMapKeySet(___element, ___key); \
    AaGpuSimpleHashMapDataSet(___element, ___data);


/**
*******************************************************************************
*
*   @brief      Gets a key from map element.
*
*   @def AaGpuSimpleHashMapKeyGet
*
*   @param[in]  ___element Pointer to the element where key shall be get
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
*   // See AaGpuSimpleHashMapAdd
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
*   @see AaGpuSimpleHashMapFind
*   @see AaGpuSimpleHashMapAdd
*
******************************************************************************/
#define AaGpuSimpleHashMapKeyGet(___element) ((___element)->key)


/**
*******************************************************************************
*
*   @brief      Gets a data from map element.
*
*   @def AaGpuSimpleHashMapDataGet
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
*   // See AaGpuSimpleHashMapAdd
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
*   @see AaGpuSimpleHashMapFind
*   @see AaGpuSimpleHashMapAdd
*
******************************************************************************/
#define AaGpuSimpleHashMapDataGet(___element) ((___element)->data)


/**
*******************************************************************************
*
*   @brief   Adds an element to a hash map   
*
*   @param[in]  handler  Pointer to map handler
*
*   @return     GLO_NULL or colliding element
*
*   @par Description:
*   If the element to be added collides with existing element it the map, 
*   the existing element shall be returned and the new element is added to 
*   the map. If no collision occurred, GLO_NULL is returned.
*   
*   @par Errors:
*   None
*
*   @par Restrictions:
*   All keys must be unique thus adding of colliding element causes 
*   original element in the map to be replaced and returned.
*
*   @par Example:
*
*   @code
*
*   #include <IfAaGpuSimpleHashMap.h>
*
*   SAaGpuSimpleHashMapHandler map;
*   char* key1 = "Key 1";
*   char* key2 = "Key 2";
*   char* data1 = "Data 1";
*   char* data2 = "Data 2";
*   SAaGpuSimpleHashMapElement e1;
*   SAaGpuSimpleHashMapElement e2;
*   SAaGpuSimpleHashMapElement* colliding;
*   size_t count;
*
*   // ... init the tree, see AaGpuSimpleHashMapInit...
*
*   // Add elements to the tree
*   AaGpuSimpleHashMapKeySet(&e1, key1);
*   AaGpuSimpleHashMapDataSet(&e1, data1);
*   colliding = AaGpuSimpleHashMapAdd(&map, &e1);
*
*   if (colliding != GLO_NULL) {
*       // Handle the previous element in the tree; now replaced by 
*       // the new one
*   }
*
*   // Alternative way to init element
*   AaGpuSimpleHashMapElementInit(&e2, key2, data2);
*   colliding = AaGpuSimpleHashMapAdd(&map, &e2);
*
*   if (colliding != GLO_NULL) {
*       // Handle the previous element in the tree; now replaced by 
*       // the new one
*   }
*
*   count = AaGpuSimpleHashMapSize(&map); // Count should be 2
*
*   // Find from the hash map
*   found = AaGpuSimpleHashMapFind(&map, key2);
*
*   // Key and data (addresses) of the found element should match to the ones added earlier
*   if ((AaGpuSimpleHashMapKeyGet(found) == key2) &&
*       (AaGpuSimpleHashMapDataGet(found) == data2))
*   {
*      // ...
*   }
*
*   // Remove element
*   if (AaGpuSimpleHashMapRemove(&map, key2) == found)
*   {
*      // ... removed element should match the element corresponding the given key...
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
*   @see AaGpuSimpleHashMapInit
*   @see AaGpuSimpleHashMapElementInit
*   @see AaGpuSimpleHashMapKeySet
*   @see AaGpuSimpleHashMapDataSet
*   @see AaGpuSimpleHashMapFind
*
******************************************************************************/
SAaGpuSimpleHashMapElement* 
AaGpuSimpleHashMapAdd(SAaGpuSimpleHashMapHandler* const handler,
                      SAaGpuSimpleHashMapElement* const element);                      

/**
*******************************************************************************
*
*   @brief    Tries to find an element matching to given key from hash map  
*
*   @param[in]  handler      Pointer to map handler
*   @param[in]  key          Pointer to a key to look for
*
*   @return     Pointer to corresponding element or GLO_NULL if not found.
*
*   @par Description:
*   Searches the given tree map using comparator given during hash map initilization.
*   Time for find operation is in the best case O(1) and in the worst case O(n).
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
*   // See AaGpuSimpleHashMapAdd
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
*   @see AaGpuSimpleHashMapInit
*   @see AaGpuSimpleHashMapAdd
*
******************************************************************************/
SAaGpuSimpleHashMapElement* 
AaGpuSimpleHashMapFind(SAaGpuSimpleHashMapHandler* const handler,
                       const void* const key);


/**
*******************************************************************************
*
*   @brief  Removes element corresponding given key from the hash map
*
*   @param[in]  handler  Pointer to the handler of the hash map
*   @param[in]  key      Pointer to the key
*
*   @return     Pointer to removed element
*
*   @par Description:
*   Time for remove operation is in average O(1) and in worst case O(n).
*
*   @par Errors:
*   None   
*
*   @par Restrictions:
*   After removing all iterators pointing to the tree must be considered invalid 
*   thus needs re-querying.
*
*   @par Example:
*
*   @code
*   
*   // See AaGpuSimpleHashMapAdd
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
*   @see AaGpuSimpleHashMapRemoveE
*   @see AaGpuSimpleHashMapAdd
*
******************************************************************************/
SAaGpuSimpleHashMapElement*
AaGpuSimpleHashMapRemove(SAaGpuSimpleHashMapHandler* const handler, const void* const key);

/**
*******************************************************************************
*
*   @brief  Removes given element from the hash map    
*
*   @param[in]  handler  Pointer to the handler of the map
*   @param[in]  element  Pointer to the element
*
*   @return     Pointer to removed element or GLO_NULL
*
*   @par Description:
*   Time for remove operation is O(1).
*
*   @par Errors:
*   If given element is not part of the hash map, GLO_NULL is returned.   
*
*   @par Restrictions:
*   After removing all iterators pointing to the tree must be considered invalid 
*   thus needs re-querying.
*
*   @par Usage:
*   It might be beneficial from performance point of view to use AaGpuSimpleHashMapPrune()
*   when whole tree needs to be cleared and caller can access to the elements
*   in the tree by some other means than using the tree API.
*
*   @par Rationale:
*   None
*
*   @par Future directions:
*   None
*
*   @see AaGpuSimpleHashMapRemove
*   @see AaGpuSimpleHashMapPrune
*
******************************************************************************/
SAaGpuSimpleHashMapElement*
AaGpuSimpleHashMapRemoveE(SAaGpuSimpleHashMapHandler* const handler, 
                          SAaGpuSimpleHashMapElement* const element);


/**
*******************************************************************************
*
*   @brief   Prunes internal data structure of the hash map
*
*   @param[in]  handler  Pointer to the handler of the hash map
*
*   @return     none
*
*   @par Description:
*   Internal data structure of the hash map is deleted by removing all elements
*   from the map. It is callers responsibility to take care of releasing the
*   memory of every element after prune, which were existing in the map prior 
*   to the prune process.
*   Since nothing is returned by this function, it is also callers responsibility
*   to ensure that the dynamically allocated elements are still reachable by the
*   caller for releasing, othervice memory leaks will occur. This of course applies 
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
*   #include <IfAaGpuSimpleHashMap.h>
*   #include <IfAaMem.h>
*
*   SAaGpuSimpleHashMapHandler map;
*   SAaGpuSimpleHashMapElement* e;
*
*   // Init the map
*   AaGpuSimpleHashMapInit(&map, 
*                          AaGpuSimpleHashMapHasherU32, 
*                          AaGpuSimpleHashMapComparatorU32, 
*                          HashAllocator, 
*                          HashUnallocator, 
*                          100); // Start with 100 elements (may be rounded up)
*
*
*   // Init map, allocate elements, data and keys and add them to the tree
*   e = (SAaGpuSimpleHashMapElement*)AaMemMalloc(sizeof(SAaGpuSimpleHashMapElement));
*   AaGpuSimpleHashMapKeySet(&e1, ...);
*   AaGpuSimpleHashMapDataSet(&e1, ...);
*   ...
*
*   // Prune the tree
*   AaGpuSimpleHashMapPrune(&map);
*
*   // Release the memory allocated for the elements (and data, keys)
*   AaMemUnRef((void const ** const)&e);
*   ...
*
*   // Reinit the map
*   AaGpuSimpleHashMapInit(&map, 
*                          AaGpuSimpleHashMapHasherU32, 
*                          AaGpuSimpleHashMapComparatorU32, 
*                          HashAllocator, 
*                          HashUnallocator, 
*                          10000); // Start with 10000 elements (may be rounded up)
*   
*   // ... handler can now be used ...
*
*   @endcode
*
*   @par Usage:
*   When fast cleanup of all element of a map is needed e.g. for map reuse or
*   part of SW termination procedure, this function is faster than using 
*   paradigm introduced in AaGpuSimpleHashMapRemoveE() example, if elements are
*   accessible by the user by some other means. Intialization must be done
*   after prune if the handler is going to be used again.
*
*   @par Rationale:
*   Since memory allocations for element are done by user, prune of the tree 
*   does not do any memory releasing instead user must do it since user also 
*   knows how the memory is allocated.
*
*   @par Future directions:
*   None
*
*   @see AaGpuSimpleHashMapRemoveE
*   @see AaGpuSimpleHashMapInit
*
******************************************************************************/
void
AaGpuSimpleHashMapPrune(SAaGpuSimpleHashMapHandler* const handler);



/**
*******************************************************************************
*
*   @brief    Comparator implementation for U32 keys  
* 
*   @param[in]  key1   Pointer to a unsigned 32 key to compare
*   @param[in]  key2   Pointer to a unsigned 32 key to compare with
*
*   @return See TAaGpuSimpleHashMapComparator    
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
*   None
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
*   @see TAaGpuSimpleHashMapComparator
*
******************************************************************************/
int 
AaGpuSimpleHashMapComparatorU32(const void* const key1, const void* const key2);


/**
*******************************************************************************
*
*   @brief   A hasher implementation for U32 keys   
* 
*   @param[in]  key   Pointer to a unsigned 32 key to hash
*
*   @return See TAaGpuSimpleHashMapHasher    
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
*   None
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
*   @see TAaGpuSimpleHashMapHasher
*
******************************************************************************/
TAaGpuSimpleHashMapHash 
AaGpuSimpleHashMapHasherU32(const void* const key, const size_t max);


/**
*******************************************************************************
*
*   @brief    Comparator implementation for NULL-terminated string keys  
* 
*   @param[in]  key1   Pointer to a NULL-terminated string key to compare
*   @param[in]  key2   Pointer to a NULL-terminated string key to compare with
*
*   @return See TAaGpuSimpleHashMapComparator    
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
*   None
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
*   @see TAaGpuSimpleHashMapComparator
*
******************************************************************************/
int 
AaGpuSimpleHashMapComparatorString(const void* const key1, const void* const key2);


/**
*******************************************************************************
*
*   @brief   A hasher implementation for NULL-terminated string keys   
* 
*   @param[in]  key   Pointer to a NULL-terminated string key to hash
*
*   @return See TAaGpuSimpleHashMapHasher    
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
*   None
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
*   @see TAaGpuSimpleHashMapHasher
*
******************************************************************************/
TAaGpuSimpleHashMapHash 
AaGpuSimpleHashMapHasherString(const void* const key, const size_t max);

/** @} */

#ifdef __cplusplus
}
#endif


/*@}*/

#endif /* _MCU_RT_IFAAGPUSIMPLEHASHMAP_H */
