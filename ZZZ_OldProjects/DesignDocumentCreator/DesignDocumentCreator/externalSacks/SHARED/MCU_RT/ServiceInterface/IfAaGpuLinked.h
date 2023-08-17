/**
*******************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief
* @module                AaGpu
* @owner                 Marcela Nemet
*
* Copyright 2014 Nokia Solutions and Networks. All rights reserved.
*******************************************************************************/

#ifndef _MCU_RT_IFAAGPULINKED_H
#define _MCU_RT_IFAAGPULINKED_H

#include <CcsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <glo_def.h>




struct SAaGpuLinkedElement{
  void *data ;
  struct SAaGpuLinkedElement *prev;
  struct SAaGpuLinkedElement *next;
};

typedef struct SAaGpuLinkedElement SAaGpuLinkedElement;


typedef struct SAaGpuLinkedHandler{
  SAaGpuLinkedElement *head;
  SAaGpuLinkedElement *tail;
} SAaGpuLinkedHandler;




void AaGpuLinkedAdd(u32 index, SAaGpuLinkedElement* element, SAaGpuLinkedHandler *linkedHandler);

void AaGpuLinkedPut(u32 index, SAaGpuLinkedElement* element, SAaGpuLinkedHandler *linkedHandler);
void AaGpuLinkedRemove(SAaGpuLinkedHandler* linkedHandler, SAaGpuLinkedElement* element);



/* Compare functions */
i32 AaGpuMapCompareStr(void* key1, void* key2);

i32 AaGpuMapCompareInt(void* key1, void* key2);

i32 AaGpuMapCompareShort(void* key1, void* key2);


#ifdef __cplusplus
}
#endif


#endif /* _MCU_RT_IFAAGPULINKED_H */

