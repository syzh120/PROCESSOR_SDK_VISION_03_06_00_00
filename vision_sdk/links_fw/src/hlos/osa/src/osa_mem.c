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

#include <osa_mem_map.h>
#include <osa_mem.h>
#ifndef QNX_BUILD
#include <dev_memcache.h>
#include <sys/ioctl.h>
#ifdef BUILD_INFOADAS
#include <shmem.h>
#endif
#else
#include <sys/neutrino.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/cache.h>
#include <fcntl.h>
#if _NTO_VERSION >= 660
#define OSA_QNX_USE_CACHE
#endif
#endif
//#define OSA_DEBUG_MEM

typedef struct
{
  OSA_MemRegion memRegion[OSA_MEM_REGION_TYPE_MAX];
  unsigned int  non_cache_fd;
  unsigned int  cache_fd;
#ifdef QNX_BUILD
  struct cache_ctrl cachectl;
#endif
} OSA_Mem;

#ifdef QNX_BUILD
typedef struct
{
    unsigned int paddr;
    unsigned int vaddr;
} sr2_mem_table;

#define MAX_SR2_ENTRIES  128
sr2_mem_table g_sr2MemTable[MAX_SR2_ENTRIES];
int g_sr2MemTableNextIndex = 0;
#endif

OSA_Mem gOsaMem;

unsigned int OSA_memMapFd(int fd, unsigned int physAddr, unsigned int size)
{
    unsigned int pageSize = getpagesize ();
    unsigned int taddr;
    unsigned int tsize;
    unsigned int virtAddr;

    /* Mapping this physical address to linux user space */
    taddr = physAddr;
    tsize = size;

    /* Align the physical address to page boundary */
    tsize = OSA_align(tsize + (taddr % pageSize), pageSize);
    taddr = OSA_floor(taddr, pageSize);

#ifndef QNX_BUILD
#ifdef ANDROID
    virtAddr              = (unsigned int)mmap64(0, tsize,
#else
    virtAddr              = (unsigned int)mmap(0, tsize,
#endif
                          (PROT_READ | PROT_WRITE),
                          (MAP_SHARED), fd, taddr);
#else
#ifdef OSA_QNX_USE_CACHE
    if (fd == gOsaMem.non_cache_fd)
    {
        virtAddr           = (unsigned int)mmap(0, tsize,
                          (PROT_READ | PROT_WRITE | PROT_NOCACHE),
                          (MAP_SHARED), fd, taddr);
    }
    else
    {
        virtAddr           = (unsigned int)mmap(0, tsize,
                          (PROT_READ | PROT_WRITE),
                          (MAP_SHARED), fd, taddr);
    }
#else
    virtAddr           = (unsigned int)mmap(0, tsize,
                  (PROT_READ | PROT_WRITE | PROT_NOCACHE),
                  (MAP_SHARED), fd, taddr);
#endif
#endif

    if(virtAddr==0xFFFFFFFF)
        return 0;

    #ifdef OSA_DEBUG_MEM
    OSA_printf(" OSA: MEM: Mapped 0x%08x to 0x%08x of size 0x%08x (pagesize = 0x%04x)\n",
        taddr, virtAddr, tsize, pageSize
        );
    #endif

    return virtAddr + (physAddr % pageSize);
}

unsigned int OSA_memMap(unsigned int physAddr, unsigned int size)
{
    return OSA_memMapFd(gOsaMem.non_cache_fd, physAddr, size);
}

int OSA_memUnMap(unsigned int virtAddr, unsigned int size)
{
    int status=OSA_SOK;

    unsigned int pageSize = getpagesize ();
    unsigned int taddr;
    unsigned int tsize;

    taddr = virtAddr;
    tsize = size;

    tsize = OSA_align(tsize + (taddr % pageSize), pageSize);
    taddr = OSA_floor(taddr, pageSize);

    munmap((void *)taddr, tsize);

    #ifdef OSA_DEBUG_MEM
    OSA_printf(" OSA: MEM: Unmapped 0x%08x of size 0x%08x (pagesize = 0x%08x)\n",
        taddr, tsize, pageSize
        );
    #endif

    return status;
}

unsigned int OSA_memPhys2RegionType(unsigned int physAddr)
{
    OSA_MemRegion *pMemRegion;
    int i;

    for(i=0; i<OSA_MEM_REGION_TYPE_AUTO; i++)
    {
        pMemRegion = &gOsaMem.memRegion[i];

        if(physAddr >= pMemRegion->physAddr
                &&
            physAddr < (pMemRegion->physAddr + pMemRegion->size)
        )
        {
            return i;
        }
    }

    return OSA_MEM_REGION_TYPE_MAX;
}

unsigned int OSA_memVirt2RegionType(unsigned int virtAddr)
{
    OSA_MemRegion *pMemRegion;
    int i;

    for(i=0; i<OSA_MEM_REGION_TYPE_AUTO; i++)
    {
        pMemRegion = &gOsaMem.memRegion[i];

        if(virtAddr >= pMemRegion->virtAddr
                &&
            virtAddr < (pMemRegion->virtAddr + pMemRegion->size)
        )
        {
            return i;
        }
    }

    return OSA_MEM_REGION_TYPE_MAX;
}


unsigned int OSA_memPhys2Virt(unsigned int physAddr, OSA_MemRegionType type)
{
    OSA_MemRegion *pMemRegion;

    if(type==OSA_MEM_REGION_TYPE_AUTO)
    {
        type = OSA_memPhys2RegionType(physAddr);
    }

    if(type>=OSA_MEM_REGION_TYPE_MAX)
    {
#ifdef BUILD_INFOADAS
#ifdef QNX_BUILD
        /* This is special handling for buffer allocated in the SR2 heap by the
         * sharedMemoryAllocator
         */
        int i;
        if (physAddr >= SR2_FRAME_BUFFER_MEM_ADDR
            &&
            physAddr < (SR2_FRAME_BUFFER_MEM_ADDR + SR2_FRAME_BUFFER_MEM_SIZE))
        {
            for(i = 0; i < MAX_SR2_ENTRIES; i++)
            {
                if(g_sr2MemTable[i].paddr == physAddr)
                {
                    return g_sr2MemTable[i].vaddr;
                }
            }
        }
#else

        /* Failed to convert address in SR0/SR1. Call A15 based memory allocator API for conversion */
        unsigned int virtAddr;
        SHM_physToVirt(physAddr, &virtAddr);
        return virtAddr;
#endif
#else
        return 0;
#endif
    }

    pMemRegion = &gOsaMem.memRegion[type];

    if(physAddr < pMemRegion->physAddr
        ||
       physAddr >= (pMemRegion->physAddr + pMemRegion->size)
    )
    {
        return 0;
    }

    return pMemRegion->virtAddr + (physAddr - pMemRegion->physAddr);
}

unsigned int OSA_memVirt2Phys(unsigned int virtAddr, OSA_MemRegionType type)
{
    OSA_MemRegion *pMemRegion;

    if(type==OSA_MEM_REGION_TYPE_AUTO)
    {
        type = OSA_memVirt2RegionType(virtAddr);
    }

    if(type>=OSA_MEM_REGION_TYPE_MAX)
    {
#ifdef BUILD_INFOADAS
#ifdef QNX_BUILD
        /* This is special handling for buffer allocated in the SR2 heap by the
         * sharedMemoryAllocator
         */
        uint64_t *vaddr = (uint64_t *)virtAddr;
        int64_t  paddr = 0;
        int i, found = 0;
        mem_offset64(vaddr, NOFD, (size_t)4, &paddr, NULL);
        if (paddr >= SR2_FRAME_BUFFER_MEM_ADDR
            &&
            paddr < (SR2_FRAME_BUFFER_MEM_ADDR + SR2_FRAME_BUFFER_MEM_SIZE))
        {
            for(i = 0; i < MAX_SR2_ENTRIES; i++)
            {
                if(g_sr2MemTable[i].paddr == paddr)
                {
                    found = 1;
                    break;
                }
            }
            /* NOTE: currently using a next free index which will rollover after
             * MAX_SR2_ENTRIES. Ideally, we must implement an API in the Shmemallocator
             * so that we don't have to maintaing this table
             */
            if (!found)
            {
                g_sr2MemTable[g_sr2MemTableNextIndex].paddr = paddr;
                g_sr2MemTable[g_sr2MemTableNextIndex].vaddr = virtAddr;
                g_sr2MemTableNextIndex = (g_sr2MemTableNextIndex + 1) % MAX_SR2_ENTRIES;
            }
            return paddr;
        }
#else
        /* Failed to convert address in SR0/SR1. Call A15 based memory allocator API for conversion */
        unsigned int phyAddr;
        SHM_virtToPhys(virtAddr, &phyAddr);
        return phyAddr;
#endif
#else
        return 0;
#endif
    }

    pMemRegion = &gOsaMem.memRegion[type];

    if(virtAddr < pMemRegion->virtAddr
        ||
       virtAddr >= (pMemRegion->virtAddr + pMemRegion->size)
    )
    {
        return 0;
    }

    return pMemRegion->physAddr + (virtAddr - pMemRegion->virtAddr);
}

unsigned int OSA_memOffset2Virt(unsigned int offset, OSA_MemRegionType type)
{
    OSA_MemRegion *pMemRegion;

    if(type==OSA_MEM_REGION_TYPE_AUTO)
    {
        /* type cannot be AUTO for this API */
        OSA_assert(0);
    }

    if(type>=OSA_MEM_REGION_TYPE_MAX)
    {
        return 0;
    }

    pMemRegion = &gOsaMem.memRegion[type];

    if(offset >= pMemRegion->size)
    {
        return 0;
    }

    return pMemRegion->virtAddr + offset;
}

unsigned int OSA_memOffset2Phys(unsigned int offset, OSA_MemRegionType type)
{
    OSA_MemRegion *pMemRegion;

    if(type==OSA_MEM_REGION_TYPE_AUTO)
    {
        /* type cannot be AUTO for this API */
        OSA_assert(0);
    }

    if(type>=OSA_MEM_REGION_TYPE_MAX)
    {
        return 0;
    }

    pMemRegion = &gOsaMem.memRegion[type];

    if(offset >= pMemRegion->size)
    {
        return 0;
    }

    return pMemRegion->physAddr + offset;
}

unsigned int OSA_memVirt2Offset(unsigned int virtAddr, OSA_MemRegionType type)
{
    OSA_MemRegion *pMemRegion;

    if(type==OSA_MEM_REGION_TYPE_AUTO)
    {
        type = OSA_memVirt2RegionType(virtAddr);
    }

    if(type>=OSA_MEM_REGION_TYPE_MAX)
        return 0;

    pMemRegion = &gOsaMem.memRegion[type];

    if(virtAddr < pMemRegion->virtAddr
        ||
       virtAddr >= (pMemRegion->virtAddr + pMemRegion->size)
    )
    {
        return 0;
    }

    return (virtAddr - pMemRegion->virtAddr);
}

unsigned int OSA_memPhys2Offset(unsigned int physAddr, OSA_MemRegionType type)
{
    OSA_MemRegion *pMemRegion;

    if(type==OSA_MEM_REGION_TYPE_AUTO)
    {
        type = OSA_memPhys2RegionType(physAddr);
    }

    if(type>=OSA_MEM_REGION_TYPE_MAX)
    {
        return 0;
    }

    pMemRegion = &gOsaMem.memRegion[type];

    if(physAddr < pMemRegion->physAddr
        ||
       physAddr >= (pMemRegion->physAddr + pMemRegion->size)
    )
    {
        return 0;
    }

    return (physAddr - pMemRegion->physAddr);
}

unsigned int OSA_memMapHeapIdToRegionId(Osa_HeapId heapId)
{

    OSA_assert(heapId < OSA_HEAPID_MAXNUMHEAPS);

    if(heapId == OSA_HEAPID_DDR_NON_CACHED_SR0)
    {
        return OSA_MEM_REGION_TYPE_SR0;
    }
    else if (heapId == OSA_HEAPID_DDR_CACHED_SR1)
    {
        return OSA_MEM_REGION_TYPE_SR1;
    }
    else
    {
        OSA_printf(" OSA: MEM: WARNING: Invalid heap ID !!!\n");
        return OSA_MEM_REGION_TYPE_INVALID;
    }
}

int OSA_memCacheInv(unsigned int virtAddr, unsigned int length)
{
#ifndef QNX_BUILD
    Uint32 cmd;
    DMA_CacheInvPrm prm;
    int status;

    prm.size = length;
    prm.virtAddr = virtAddr;
    prm.physAddr = OSA_memVirt2Phys(virtAddr, OSA_MEM_REGION_TYPE_AUTO);

    cmd = DMA_IOCTL_CMD_MAKE(DMA_CMD_CACHEINV);
    status = ioctl(gOsaMem.cache_fd, cmd, &prm);

    return status;
#else
#ifdef OSA_QNX_USE_CACHE
    unsigned int paddr;

    paddr = OSA_memVirt2Phys(virtAddr, OSA_MEM_REGION_TYPE_AUTO);
    CACHE_INVAL(&gOsaMem.cachectl, (void *)virtAddr, (uint64_t) paddr, length);
#endif
    return 0;
#endif
}

int OSA_memCacheWb(unsigned int virtAddrStart, unsigned int virtAddrEnd)
{
#ifndef QNX_BUILD
    Uint32 cmd;
    DMA_CacheWbPrm prm;
    int status;

    prm.virtAddrStart = virtAddrStart;
    prm.virtAddrEnd = virtAddrEnd;
    prm.physAddrStart = OSA_memVirt2Phys(virtAddrStart, OSA_MEM_REGION_TYPE_AUTO);

    cmd = DMA_IOCTL_CMD_MAKE(DMA_CMD_CACHEWB);
    status = ioctl(gOsaMem.cache_fd, cmd, &prm);

    return status;
#else
#ifdef OSA_QNX_USE_CACHE
    unsigned int paddr;
    unsigned int length;

    length = virtAddrEnd - virtAddrStart;

    paddr = OSA_memVirt2Phys(virtAddrStart, OSA_MEM_REGION_TYPE_AUTO);
    CACHE_FLUSH(&gOsaMem.cachectl, (void *)virtAddrStart, (uint64_t) paddr, length);
#endif
    return 0;
#endif
}

int OSA_memInit(void)
{
    int status=OSA_SOK;
    int i;
    OSA_MemRegion *pMemRegion;
    char deviceName[20];

    memset(&gOsaMem, 0, sizeof(OSA_Mem));

    gOsaMem.non_cache_fd = open("/dev/mem",O_RDWR|O_SYNC);
    if(gOsaMem.non_cache_fd  < 0)
    {
        OSA_printf(" OSA: ERROR: /dev/mem open failed !!!\n");
        return -1;
    }

#ifdef QNX_BUILD
    sprintf(deviceName, "%s", "/dev/mem");
#else
    sprintf(deviceName, "%s", DMA_DRV_NAME);
#endif
    gOsaMem.cache_fd = open(deviceName, O_RDWR);
    if(gOsaMem.cache_fd<0)
    {
        OSA_printf(" OSA: ERROR: %s open failed !!!\n", deviceName);
        return OSA_EFAIL;
    }
#ifdef QNX_BUILD
#ifdef OSA_QNX_USE_CACHE
    gOsaMem.cachectl.fd = gOsaMem.cache_fd;
    if (cache_init(0, &gOsaMem.cachectl, NULL) == -1) {
        OSA_printf(" OSA: ERROR: Cache init failed !!!\n");
        return OSA_EFAIL;
    }
#else
    OSA_printf("Not using cache");
#endif
#endif

    /* Map required sections upfront */

    i = OSA_MEM_REGION_TYPE_SR0;
    pMemRegion = &gOsaMem.memRegion[i];

    pMemRegion->physAddr = SR0_ADDR;
    pMemRegion->size = SR0_SIZE;

    pMemRegion->virtAddr =
        OSA_memMap(pMemRegion->physAddr, pMemRegion->size);

    OSA_assert(pMemRegion->virtAddr != 0);

    i = OSA_MEM_REGION_TYPE_SR1;
    pMemRegion = &gOsaMem.memRegion[i];

    pMemRegion->physAddr = SR1_FRAME_BUFFER_MEM_ADDR;
    pMemRegion->size = SR1_FRAME_BUFFER_MEM_SIZE;

    pMemRegion->virtAddr =
        OSA_memMapFd(gOsaMem.cache_fd, pMemRegion->physAddr, pMemRegion->size);

    OSA_assert(pMemRegion->virtAddr != 0);

    i = OSA_MEM_REGION_TYPE_SYSTEM_IPC;
    pMemRegion = &gOsaMem.memRegion[i];

    pMemRegion->physAddr = SYSTEM_IPC_SHM_MEM_ADDR;
    pMemRegion->size = SYSTEM_IPC_SHM_MEM_SIZE;

    pMemRegion->virtAddr =
        OSA_memMap(pMemRegion->physAddr, pMemRegion->size);

    OSA_assert(pMemRegion->virtAddr != 0);

    i = OSA_MEM_REGION_TYPE_REMOTE_LOG;
    pMemRegion = &gOsaMem.memRegion[i];

    pMemRegion->physAddr = REMOTE_LOG_MEM_ADDR;
    pMemRegion->size = REMOTE_LOG_MEM_SIZE;

    pMemRegion->virtAddr =
        OSA_memMap(pMemRegion->physAddr, pMemRegion->size);

    OSA_assert(pMemRegion->virtAddr != 0);

#ifdef OPENVX_INCLUDE
    i = OSA_MEM_REGION_TYPE_OPENVX_OBJ_DESC;
    pMemRegion = &gOsaMem.memRegion[i];

    pMemRegion->physAddr = OPENVX_OBJ_DESC_MEM_ADDR;
    pMemRegion->size = OPENVX_OBJ_DESC_MEM_SIZE;

    pMemRegion->virtAddr =
        OSA_memMap(pMemRegion->physAddr, pMemRegion->size);

    OSA_assert(pMemRegion->virtAddr != 0);
#endif

#ifdef BUILD_INFOADAS
#ifndef QNX_BUILD
    /* Initlialise SHM allocator on A15*/
    SHM_init();
#endif
#endif

    #if 1 //def OSA_DEBUG_MEM
    for(i=0; i<OSA_MEM_REGION_TYPE_AUTO; i++)
    {
        pMemRegion = &gOsaMem.memRegion[i];
        OSA_printf(" OSA: MEM: %d: Mapped 0x%08x to 0x%08x of size 0x%08x \n",
            i, pMemRegion->physAddr, pMemRegion->virtAddr, pMemRegion->size
            );
    }
    #endif

    return status;
}

int OSA_memDeInit(void)
{
    int status=OSA_SOK;
    int i;

    for(i=0; i<OSA_MEM_REGION_TYPE_AUTO; i++)
    {
        OSA_memUnMap(
            gOsaMem.memRegion[i].virtAddr,
            gOsaMem.memRegion[i].size
            );
    }

#ifdef BUILD_INFOADAS
#ifndef QNX_BUILD
    SHM_exit();
#endif
#endif

    close(gOsaMem.non_cache_fd);
#ifndef QNX_BUILD
    close(gOsaMem.cache_fd);
#else
#ifdef OSA_QNX_USE_CACHE
    cache_fini(&gOsaMem.cachectl);
#endif
#endif

    return status;
}

Void* OSA_memAllocSR(UInt32 heapId, UInt32 size, UInt32 align)
{
    Void *addr = NULL;

    if(heapId>=OSA_HEAPID_MAXNUMHEAPS)
        return NULL;

    if(heapId==OSA_HEAPID_DDR_NON_CACHED_SR0)
    {
        heapId = SYSTEM_HEAPID_DDR_NON_CACHED_SR0;
    }
    else if(heapId==OSA_HEAPID_DDR_CACHED_SR1)
    {
        heapId = SYSTEM_HEAPID_DDR_CACHED_SR1;
    }
    else
    {
        OSA_assert(0);
    }
    /*
     * Allocate from heap created on IPU1-0
     */
    SystemCommon_AllocBuffer bufAlloc;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    bufAlloc.bufferPtr = (UInt32)NULL;
    bufAlloc.heapId = heapId;
    bufAlloc.size = size;
    bufAlloc.align = align;

    /*
     * Alloc by sending command to IPU1-0 core
     */
    status = System_linkControl(
                SYSTEM_LINK_ID_IPU1_0,
                SYSTEM_COMMON_CMD_ALLOC_BUFFER,
                &bufAlloc,
                sizeof(bufAlloc),
                TRUE
                );
    if(status != SYSTEM_LINK_STATUS_SOK)
    {
        return NULL;
    }
    else
    {
        addr = (Ptr)bufAlloc.bufferPtr;
    }

    #ifdef OSA_DEBUG_MEM
    Vps_printf(" OSA: MEM: ALLOC, addr = 0x%08x, size = %d bytes, heapId = %d \n",
            addr,
            size,
            heapId
           );
    #endif

    addr = (Void*) OSA_memPhys2Virt((UInt32)addr, OSA_MEM_REGION_TYPE_AUTO);

    return addr;
}

Int32 OSA_memFreeSR(UInt32 heapId, Ptr addr, UInt32 size)
{
    Int32 status = OSA_SOK;
    SystemCommon_FreeBuffer bufFree;

    if(heapId>=OSA_HEAPID_MAXNUMHEAPS)
        return OSA_EFAIL;

    if(heapId==OSA_HEAPID_DDR_NON_CACHED_SR0)
    {
        heapId = SYSTEM_HEAPID_DDR_NON_CACHED_SR0;
    }
    else if(heapId==OSA_HEAPID_DDR_CACHED_SR1)
    {
        heapId = SYSTEM_HEAPID_DDR_CACHED_SR1;
    }
    else
    {
        OSA_assert(0);
    }

    /* Invalidate is required here to ensure that we (this core) will
        not update memory, after releasing the memory */
    OSA_memCacheInv((unsigned int)addr, size);

    addr = (Void*) OSA_memVirt2Phys((UInt32)addr, OSA_MEM_REGION_TYPE_AUTO);

    #ifdef OSA_DEBUG_MEM
    Vps_printf(" OSA: MEM: FREE, addr = 0x%08x, size = %d bytes, heapId = %d \n",
            addr,
            size,
            heapId
           );
    #endif

    bufFree.bufferPtr = (UInt32)addr;
    bufFree.heapId = heapId;
    bufFree.size = size;

    status = System_linkControl(
                SYSTEM_LINK_ID_IPU1_0,
                SYSTEM_COMMON_CMD_FREE_BUFFER,
                &bufFree,
                sizeof(bufFree),
                TRUE
                );

    return status;
}

unsigned int OSA_getOpenVxShmVirtAddr()
{
    unsigned int addr = 0;
#ifdef OPENVX_INCLUDE
    addr = gOsaMem.memRegion[OSA_MEM_REGION_TYPE_OPENVX_OBJ_DESC].virtAddr;
#endif
    return (addr);
}