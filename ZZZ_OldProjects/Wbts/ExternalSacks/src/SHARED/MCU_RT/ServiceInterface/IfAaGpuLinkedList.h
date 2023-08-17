/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 Linked list interface header file
* @module                AaGpu
* @owner                 Marcela Nemet
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAGPULINKEDLIST_H
#define _MCU_RT_IFAAGPULINKEDLIST_H

#include <CcsCommon.h>


#ifdef __cplusplus
extern "C" {
#endif


#include <glo_def.h>

#include "IfAaMem.h"
#include "IfAaGpuLinked.h"



/**
*******************************************************************************
*
*   @brief      Create a linked list
*
*
*   @param[in, out]  handler  Pointer to a pointer in which the address of
*                             linked list handler will be saved
*
*   @return     Nothing
*
*   @par Description:
*   Create a linked list
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void AaGpuLinkedListCreate(SAaGpuLinkedHandler **handler);


/**
*******************************************************************************
*
*   @brief      Get elements from linked list
*
*
*   @param[in]  handler   Pointer to linked list handler
*
*   @param[in, out] index .....
*
*   @return     Pointer to linked list elements.
*
*   @par Description:
*   Get element(s) from linked list.
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void* AaGpuLinkedListGet(SAaGpuLinkedHandler *handler, u32 index);


/**
*******************************************************************************
*
*   @brief      Remove an element from linked list
*
*
*   @param[in]  handler   Pointer to linked list handler
*
*   @param[in]  index     ...
*
*   @return     Nothing.
*
*   @par Description:
*   Remove an element from linked list.
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void AaGpuLinkedListRemove(SAaGpuLinkedHandler *handler, u32 index);


/**
*******************************************************************************
*
*   @brief      Add an element to linked list
*
*
*   @param[in]  handler   Pointer to linked list handler
*
*   @param[in]  data      Pointer to the element to be added
*
*   @return     Nothing.
*
*   @par Description:
*   Add an element to the end of a linked list.
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void AaGpuLinkedListAdd(SAaGpuLinkedHandler *handler, void *data);


/**
*******************************************************************************
*
*   @brief      Put an element to specified index of the linked list
*
*
*   @param[in]  handler   Pointer to linked list handler
*
*   @param[in]  index     Place (index) in which element will be put
*
*   @param[in]  data      Pointer to the element to be added
*
*   @return     Nothing.
*
*   @par Description:
*   Put an element to specified index of the linked list.
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void AaGpuLinkedListPut(SAaGpuLinkedHandler *handler, u32 index, void *data);


/**
*******************************************************************************
*
*   @brief      Get size of linked list
*
*
*   @param[in]  handler   Pointer to linked list handler
*
*   @return     Function returns number of linked list elements.
*
*   @par Description:
*   Get size (number of elements) of linked list.
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
u32 AaGpuLinkedListSize(SAaGpuLinkedHandler *handler);


/**
*******************************************************************************
*
*   @brief      Clear (delete) a linked list
*
*
*   @param[in]  handler   Pointer to linked list handler
*
*   @return     Nothing.
*
*   @par Description:
*   Function clears the linked list and frees the list handler ptr.
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void AaGpuLinkedListClear(SAaGpuLinkedHandler *handler);


/**
*******************************************************************************
*
*   @brief      Get all elements from linked list
*
*
*   @param[in]        handler   Pointer to linked list handler
*
*   @param[in, out]   count     Pointer to integer variable in which the number
*                               of found elements will be saved
*
*   @return     Pointer to linked list elements.
*
*   @par Description:
*   Get all elements from linked list.
*
*   @par Errors:
*   No errors are defined.
*
******************************************************************************/
void* AaGpuLinkedListGetAll(SAaGpuLinkedHandler *handler, u32 *count);



#ifdef __cplusplus
}
#endif


#endif /* _MCU_RT_IFAAGPULINKEDLIST_H */

