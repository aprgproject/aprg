/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* Copyright 2015 Nokia Networks. All rights reserved.
*******************************************************************************/ 
#ifndef _MCU_IFAAGPULINKEDMAP_H
#define _MCU_IFAAGPULINKEDMAP_H

#include "CcsCommon.h"

#ifdef __cplusplus
extern "C" {
#endif


#include <glo_def.h>

#include <IfAaMem.h>
#include <IfAaGpuLinked.h>




typedef struct SAaGpuLinkedMapElement{
	void *key;
	void *data;
} SAaGpuLinkedMapElement;



/**
*******************************************************************************
*
*   @brief      Create a linked map
*
*
*   @param[in, out]  handler   Pointer to a pointer in which the address of linked map
*                         handler will be saved
*
*   @return     Nothing
*
*   @par Description:
*   Create a linked map
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void AaGpuLinkedMapCreate(SAaGpuLinkedHandler **handler);


/**
*******************************************************************************
*
*   @brief      Get elements from linked map 
*
*
*   @param[in]  handler   Pointer to linked map handler
*
*   @param[in]  key       Pointer to key of wanted element
*
*   @param[in, out]  count     Pointer to integer variable in which the number of 
*                         found elements will be saved
*
*   @param[in]  (fcmp)(void*, void*)  function that will be used when comparing 
*                                     keys of elements. See IfAaGpuLinked.h to 
*                                     find already implemented functions. 
*
*   @return     Pointer to linked map elements.
*
*   @par Description:
*   Get element(s) from linked map. 
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void* AaGpuLinkedMapGet(SAaGpuLinkedHandler *handler, 
                        void *key, 
                        u32 *count, 
                        int (fcmp)(void*, void*));



/**
*******************************************************************************
*
*   @brief      Remove an element from linked map 
*
*
*   @param[in]  handler   Pointer to linked map handler
*
*   @param[in]  element   Pointer to element to be removed 
*
*   @return     Nothing.
*
*   @par Description:
*   Remove an element from linked map. AaGpuLinkedMapGet function can be used to
*   find an element with specific key.
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void AaGpuLinkedMapRemove(SAaGpuLinkedHandler *handler, SAaGpuLinkedMapElement *element);


u32 AaGpuLinkedMapContains(SAaGpuLinkedHandler *handler, void *key);


/**
*******************************************************************************
*
*   @brief      Add an element to linked map 
*
*
*   @param[in]  handler   Pointer to linked map handler
*
*   @param[in]  key       Pointer to key of the element
*
*   @param[in]  data      Pointer to data of the element 
*
*   @return     Nothing.
*
*   @par Description:
*   Add an element to linked map.
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void AaGpuLinkedMapAdd(SAaGpuLinkedHandler *handler, void *key, void *data);


u32 AaGpuLinkedMapSize(SAaGpuLinkedHandler *handler);


void AaGpuLinkedMapClear(SAaGpuLinkedHandler *handler);


/**
*******************************************************************************
*
*   @brief      Get all elements from linked map 
*
*
*   @param[in]        handler   Pointer to linked map handler
*
*   @param[in, out]   count     Pointer to integer variable in which the number 
*                               of found elements will be saved 
*
*   @return     Pointer to linked map elements.
*
*   @par Description:
*   Get all elements from linked map. 
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void* AaGpuLinkedMapGetAll(SAaGpuLinkedHandler *handler, u32 *count);


#ifdef __cplusplus
}
#endif


#endif /* _MCU_IFAAGPULINKEDMAP_H */

