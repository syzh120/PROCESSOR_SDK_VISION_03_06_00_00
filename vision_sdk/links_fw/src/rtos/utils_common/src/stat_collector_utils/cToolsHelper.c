/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Note this file to be updated for the specific implementation */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "cToolsHelper.h"
#include <src/rtos/utils_common/include/sci.h>

#ifdef __linux__
    #include <fcntl.h>
    #include <sys/mman.h>

    /*  Mapping paramters */
    typedef struct _MapObject {
        void * vAddr;            /*  Virtural Address */
        uint32_t mapSize;    /*  Map size in Bytes */
        struct _MapObject * pPrevMapObj;
        struct _MapObject * pNextMapObj;
    }MapObject;

    MapObject * pMapObjLL = 0; /*  Map Object Link List Pointer */

    static int32_t fd = 0;
    static const uint32_t pageSize = 4096U;
    static const uint32_t pageMask = 4096U -1U ;
#endif

#ifdef __sysbios__

#include <xdc/runtime/Memory.h>

/* structure for storing pointer and size of the memory block allocated */
typedef struct MemAllocObject_s {
    void * mem_block_pointer; /* Pointer to the allocated Memory block */
    uint32_t mem_block_size; /* Size of the allocated Memory block */
    struct MemAllocObject_s * pPrevMemAllocObj;
    struct MemAllocObject_s * pNextMemAllocObj;
    }MemAllocObject;

MemAllocObject * pMemAllocObjLL = 0; /*  MemAlloc Object Link List Pointer */

#endif

/*  Memory allocation */
void * cTools_memAlloc(size_t sizeInBytes)
{
#ifdef __sysbios__
    uint32_t *ptr;
    sci_err_t retVal = SCI_SUCCESS;
    MemAllocObject *pMemAllocObj;

    /* Allocate memory */
    ptr = (uint32_t*)Memory_alloc(NULL,sizeInBytes,(size_t)16, NULL);

    if (ptr == NULL)
    {
        retVal = SCI_ERR_MEM_ALLOC;
    }
    if (retVal == SCI_SUCCESS)
    {
        /*  Allocate space for the Mem Alloc object */
        pMemAllocObj = (MemAllocObject *)Memory_alloc(NULL, sizeof(MemAllocObject), (size_t)16, NULL);
        if ( pMemAllocObj == NULL )
        {
            retVal = SCI_ERR_MEM_ALLOC;
        }
    }

    if(retVal == SCI_SUCCESS)
    {
        /* Update the memory block ptr and size */
        pMemAllocObj->mem_block_pointer =  (void*)ptr;
        pMemAllocObj->mem_block_size = sizeInBytes;

        /*  Add map object to end of link list */
        pMemAllocObj->pNextMemAllocObj = NULL;
        if ( NULL == pMemAllocObjLL )
        {
            pMemAllocObjLL = pMemAllocObj;
            pMemAllocObj->pPrevMemAllocObj = NULL;
        }
        else
        {
            /* search the link list for the current last element */
            MemAllocObject *pThisMemAllocObj = pMemAllocObjLL;
            while ( NULL != pThisMemAllocObj->pNextMemAllocObj) {
                pThisMemAllocObj = pThisMemAllocObj->pNextMemAllocObj;
            }

            pThisMemAllocObj->pNextMemAllocObj = pMemAllocObj;
            pMemAllocObj->pPrevMemAllocObj = pThisMemAllocObj;
        }
    }
    if(retVal != SCI_SUCCESS)
    {
        ptr = NULL;
    }
    /* Return the allocated memory block. */
    return ptr;
#else

    return((void *)malloc (sizeInBytes));

#endif

}

/*  Memory free */
void cTools_memFree(void *ptr)
{
#ifdef __sysbios__

    uint32_t size;
    sci_err_t retVal = SCI_SUCCESS;

    /* Using the memory block pointer, try to look up the size from the linked list */
    MemAllocObject * pThisMemAllocObj = pMemAllocObjLL;

    if ( NULL == pThisMemAllocObj )
    {

  #ifdef _DEBUG
        printf("cTools_memFree:: Failed to find memory block pointer 0x%X in the lookup table\n", (uint32_t)p);
  #endif
        retVal = SCI_ERR_INVALID_PARM;
    }
    else
    {
        while (ptr != pThisMemAllocObj->mem_block_pointer)
        {
            pThisMemAllocObj = pThisMemAllocObj->pNextMemAllocObj;
            if (  NULL == pThisMemAllocObj )
            {
  #ifdef _DEBUG
                printf("cTools_memFree:: Failed to find memory block pointer 0x%X in the lookup table\n", (uint32_t)p);
  #endif
                retVal = SCI_ERR_INVALID_PARM;
                break;
            }
        }
    }

    if(retVal == SCI_SUCCESS)
    {
        /* get the size of the memory block to be freed */
        size = pThisMemAllocObj->mem_block_size;

        /* Fix MemAlloc object link */
        /*  If this is the only object in the list */
        if ( ( NULL == pThisMemAllocObj->pNextMemAllocObj ) &&  ( NULL == pThisMemAllocObj->pPrevMemAllocObj ) )
        {
            pMemAllocObjLL = NULL;
        }

        /*  If first in list need to update list pointer to next element */
        if ( ( NULL != pThisMemAllocObj->pNextMemAllocObj ) &&  ( NULL == pThisMemAllocObj->pPrevMemAllocObj ) )
        {
            pMemAllocObjLL = pThisMemAllocObj->pNextMemAllocObj;
            pThisMemAllocObj->pNextMemAllocObj->pPrevMemAllocObj = NULL;

        }

        /*  If last object then just need to make the prev MemAlloc object the last */
        if ( ( NULL == pThisMemAllocObj->pNextMemAllocObj ) &&  ( NULL != pThisMemAllocObj->pPrevMemAllocObj ) )
        {
        pThisMemAllocObj->pPrevMemAllocObj->pNextMemAllocObj = NULL;
        }

        /*  If in the middle of list then need to remove */
        if ( ( NULL != pThisMemAllocObj->pNextMemAllocObj ) &&  ( NULL != pThisMemAllocObj->pPrevMemAllocObj ) )
        {
            /*  - The previous MemAlloc object's next pointer is updated with this object's next pointer */
            pThisMemAllocObj->pPrevMemAllocObj->pNextMemAllocObj = pThisMemAllocObj->pNextMemAllocObj;
            /*  - The next MemAlloc object's previous pointer is updated with this objects previous pointer */
            pThisMemAllocObj->pNextMemAllocObj->pPrevMemAllocObj = pThisMemAllocObj->pPrevMemAllocObj;
        }

        /*  - Free this object */
        Memory_free(NULL, pThisMemAllocObj, sizeof(MemAllocObject));

        /*  Free the required memory block */
        Memory_free(NULL, ptr, size);
    }
#else

    free(p);

#endif
}

/* Returns virtual address to region requested */
void * cTools_memMap(uint32_t phyAddr, uint32_t mapSizeInBytes)
{
#ifdef __linux__

    void * pVirtualAddress = NULL;
    uint32_t mapSize = 0;
    MapObject *pMapObj;

    /*  Only open the /dev/mem device once */
    if(0 == fd)
    {
        if((fd = open("/dev/mem", O_RDWR | O_SYNC | O_RSYNC)) == -1)
        {
  #ifdef _DEBUG
            printf("cTools_memMap:: Device '/dev/mem' could not be opened with O_RDWR | O_SYNC attributes.\n");
  #endif
            return NULL;
        }
    }

    /*  Allocate space for the map object */
    if ( ( pMapObj = (MapObject *)cTools_memAlloc(sizeof(MapObject))) == NULL )
    {
        printf("cTools_memMap:: Unable to create map object, malloc failed\n");
        return NULL;
    }

    /* Note: phyAddr may need to be aligned to a PAGE_SIZE and mapSizeInBytes may need to be */
    /*       a multiple of PAGE_SIZE. Since the STM physical size is either 256KB or 1MB */
    /*       this should not be an issue. It is assumed that the Virtual Address returned will */
    /*       map to the first location of physical STM space. */

    /*  Adjust mapSizeInBytes to a whole number of pages */
    if ((mapSizeInBytes % pageSize) != 0 )
    {
        mapSize = ((mapSizeInBytes/pageSize) + 1 ) * pageSize;
    }
    else
    {
        mapSize = mapSizeInBytes;
    }

    pVirtualAddress = mmap(0, mapSize,  (PROT_READ|PROT_WRITE), MAP_SHARED, fd, phyAddr & ~pageMask);

    if (pVirtualAddress == (void *) -1)
    {
        cTools_memFree(pMapObj);
  #ifdef _DEBUG
        printf("cTools_memMap:: Unable to map physical address 0x%X for %d bytes\n", phyAddr, mapSizeInBytes);
  #endif
        return NULL;
    }

    /*  Add map object to end of link list */
    pMapObj->vAddr = pVirtualAddress;
    pMapObj->mapSize = mapSize;
    pMapObj->pNextMapObj = NULL;
    if ( NULL == pMapObjLL )
    {
        pMapObjLL = pMapObj;
        pMapObj->pPrevMapObj = NULL;
    }
    else
    {
        /* search the link list for the current last element */
        MapObject *pThisMapObj = pMapObjLL;
        while ( NULL != pThisMapObj->pNextMapObj) {
             pThisMapObj = pThisMapObj->pNextMapObj;
        }

        pThisMapObj->pNextMapObj = pMapObj;
        pMapObj->pPrevMapObj = pThisMapObj;
    }

    /*  Virtual addres must be adjusted with LS 12 bits of the phyAddr */
    pVirtualAddress += phyAddr & pageMask;

    return pVirtualAddress;

#else  /*  __linux__  not defined */

  #ifdef _DEBUG
        printf("cTools_memMap:: Mapping physical address 0x%X for %d bytes\n", phyAddr, mapSizeInBytes);
  #endif
    return (void *)phyAddr;

#endif
}

/* Unmap virtual address space of region requested */
void cTools_memUnMap(void * vAddr, uint32_t mapSizeInBytes)
{
#ifdef __linux__
    if( munmap(vAddr,  mapSizeInBytes) ==  -1 )
    {
  #ifdef _DEBUG
        printf("cTools_memUnMap:: Unable to unmap address 0x%X for %d bytes\n", (unsigned)vAddr, mapSizeInBytes);
  #endif
        return;
    }

    uint32_t realSize;

    /* Mask address and look it up */
    MapObject * pThisMapObj = pMapObjLL;

    while (( (uint32_t)vAddr & ~pageMask ) != (uint32_t)pThisMapObj->vAddr )
    {
        pThisMapObj = pThisMapObj->pNextMapObj;
        if (  NULL == pThisMapObj )
        {
  #ifdef _DEBUG
           printf("cTools_memUnMap:: Failed to find vitural address 0x%X in lookup table\n", (unsigned)vAddr & ~pageMask);
  #endif
           return;
        }
    }

    if( munmap(pThisMapObj->vAddr,  pThisMapObj->mapSize) ==  -1 )
    {
  #ifdef _DEBUG
        printf("cTools_memUnMap:: Unmap failed for address 0x%X for %d bytes\n", (unsigned)pThisMapObj->vAddr, pThisMapObj->mapSize);
  #endif
        return;
    }

    /* Fix map object link */
    /*  If this is the only object in the list */
    if ( ( NULL == pThisMapObj->pNextMapObj ) &&  ( NULL == pThisMapObj->pPrevMapObj ) )
    {
        pMapObjLL = NULL;
        close(fd); /*  close memory device handle */
        fd = 0;
    }

    /*  If first in list need to update list pointer to next element */
    if ( ( NULL != pThisMapObj->pNextMapObj ) &&  ( NULL == pThisMapObj->pPrevMapObj ) )
    {
        pMapObjLL = pThisMapObj->pNextMapObj;
        pThisMapObj->pNextMapObj->pPrevMapObj = NULL;

    }

    /*  If last object then just need to make the prev map object the last */
    if ( ( NULL == pThisMapObj->pNextMapObj ) &&  ( NULL != pThisMapObj->pPrevMapObj ) )
    {
       pThisMapObj->pPrevMapObj->pNextMapObj = NULL;
    }

    /*  If in the middle of list then need to remove */
    if ( ( NULL != pThisMapObj->pNextMapObj ) &&  ( NULL != pThisMapObj->pPrevMapObj ) )
    {
        /*  - The previous map object's next pointer is updated with this object's next pointer */
        pThisMapObj->pPrevMapObj->pNextMapObj = pThisMapObj->pNextMapObj;
        /*  - The next map object's previous pointer is updated with this objects previous pointer */
        pThisMapObj->pNextMapObj->pPrevMapObj = pThisMapObj->pPrevMapObj;
    }

    /*  - Free this object */
    cTools_memFree(pThisMapObj);

#endif
#ifdef _DEBUG
    printf("cTools_memUnMap:: unmap request for address 0x%X for %d bytes\n", (unsigned)vAddr, mapSizeInBytes);
#endif
}
int32_t cTools_mutexInit(uint32_t mutexId)
{
    return 0;
}

int32_t cTools_mutexTrylock(uint32_t mutexId)
{
    return 0;
}

int32_t cTools_mutexUnlock(uint32_t mutexId)
{
    return 0;
}
