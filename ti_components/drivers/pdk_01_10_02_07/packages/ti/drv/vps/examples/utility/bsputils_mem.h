/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_MEM_API Frame buffer memory allocator API
 *
 *  APIs to allocate frame buffer memory from a predefined memory pool
 *  @{
 */

/**
 *  \file bsputils_mem.h
 *
 *  \brief Frame buffer memory allocator API.
 */

#ifndef BSPUTILS_MEM_H_
#define BSPUTILS_MEM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#if defined(BARE_METAL)
/** \brief Typedef for Heap memory handle */
typedef void* HeapMem_Handle;
#endif

#if !defined (BARE_METAL)
#include <ti/sysbios/BIOS.h>
#endif

#include <ti/drv/vps/include/fvid2/fvid2.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Utility define for Kilobyte, i.e 1024 bytes */
#ifndef KB
#define KB ((UInt32) 1024U)
#endif

/** \brief Utility define for Megabyte, i.e 1024*1024 bytes */
#ifndef MB
#define MB (KB * KB)
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct BspUtils_MemHeapStatus
 *  \brief He.
 */
typedef struct
{
    UInt32 freeSysHeapSize;
    /**< Current system heap free space. */
    UInt32 freeBufHeapSize;
    /**< Current buffer heap free space. */
} BspUtils_MemHeapStatus;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief One time system init of memory allocator
 *
 *  Should be called by application before using allocate APIs
 *
 *  \return 0 on sucess, else failure
 */
Int32 BspUtils_memInit(void);

/**
 *  \brief One time system init of memory allocator
 *
 *  Should be called by application before using allocate APIs.
 *  This is same as BspUtils_memInit(), except that a larger heap size is used.
 *  Right now only chains app will used this large heap.
 *  When using large heap a different config.bld needs to be used.
 *  For chains app this is setup via Makefile's in HDVPSS driver build system.
 *
 *  Only ONE of BspUtils_memInit() or
 *  BspUtils_memInit_largeHeap() should be called during system init.
 *
 *  \return 0 on sucess, else failure
 */
Int32 BspUtils_memInit_largeHeap(void);

/**
 *  \brief One time system de-init of memory allocator
 *
 *  Should be called by application at system de-init
 *
 *  \return 0 on sucess, else failure
 */
Int32 BspUtils_memDeInit(void);

/**
 *  \brief Allocate a frame
 *
 *  Use Fvid2_Format to allocate a frame.
 *  Fill Fvid2_Frame fields like chNum based on Fvid2_Format
 *
 *  \param  pFormat   [IN] Data format information
 *  \param  pFrame    [OUT] Initialzed Fvid2_Frame structure
 *  \param  numFrames [IN] Number of frames to allocate
 *
 *  \return 0 on sucess, else failure
 */
Int32 BspUtils_memFrameAlloc(Fvid2_Format *pFormat,
                             Fvid2_Frame  *pFrame,
                             UInt32        numFrames);

/**
 *  \brief Free's previously allocate Fvid2_Frame's
 *
 *  \param  pFormat   [IN] Data format information
 *  \param  pFrame    [IN] Fvid2_Frame structure
 *  \param  numFrames [IN] Number of frames to free
 *
 *  \return 0 on sucess, else failure
 */
Int32 BspUtils_memFrameFree(const Fvid2_Format *pFormat,
                            Fvid2_Frame        *pFrame,
                            UInt32              numFrames);

/**
 *  \brief Returns the memory required to allocate a single
 *  buffer as per provided format.
 *
 *  This will be used by the BspUtils_memFrameAlloc() function
 *  and application could use this function to find out the memory
 *  allocated for a frame.
 *
 *  \param  pFormat   [IN]  Data format information
 *  \param  size      [OUT] Size in bytes needed per frame.
 *                          This parameter can't be NULL.
 *  \param  cOffset   [OUT] Returns the chroma buffer offset
 *                          in case of YUV planar/semi-planar formats.
 *                          If this parameter is NULL, the value is not
 *                          returned.
 *
 *  \return 0 on sucess, else failure
 */
Int32 BspUtils_memFrameGetSize(const Fvid2_Format *pFormat,
                               UInt32             *size,
                               UInt32             *cOffset);

/**
 *  \brief Allocate memory from memory pool
 *
 *  \param size   [IN] size in bytes
 *  \param align  [IN] alignment in bytes
 *
 *  \return NULL or error, else memory pointer
 */
Ptr BspUtils_memAlloc(UInt32 size, UInt32 align);

/**
 *  \brief Free previously allocate memory pointer
 *
 *  \param addr [IN] memory pointer to free
 *  \param size [IN] size of memory pointed to by the memory pointer
 *
 *  \return 0 on sucess, else failure
 */
Int32 BspUtils_memFree(Ptr addr, UInt32 size);

/**
 *  \brief Control if allocated buffer needs to be cleared to 0
 *
 *  By default allocated buffer will not be cleared to 0
 *
 *  \param enable   [IN] TRUE: clear allocated buffer,
 *                       FALSE: do not clear allocated buffer
 *
 *  \return 0 on sucess, else failure
 */
Int32 BspUtils_memClearOnAlloc(Bool enable);

/**
 *  BspUtils_memGetHeapStat
 *  \brief Returns the current status (free size) of the various heaps used.
 *
 *  This function could be called before calling the module init function or
 *  after module deinit function.
 *
 *  \param heapStat [OUT]   Status filled by the function.
 *
 */
void BspUtils_memGetHeapStat(BspUtils_MemHeapStatus *heapStat);

/**
 *  BspUtils_memCheckHeapStat
 *  \brief Checks the current status of each heap with the value passed.
 *
 *  This returns an error if the values of each of the heap doesn't match.
 *  This function could be called before calling the module init function or
 *  after module deinit function.
 *
 *  \param heapStat [IN]    Older status to be compared with the current status.
 *
 *  \return                 Returns 0 if the heap sizes match else return
 *                          BSP_EFAIL.
 */
Int32 BspUtils_memCheckHeapStat(const BspUtils_MemHeapStatus *heapStat);

/**
 *  \brief Returns the system heap free memory (in bytes)
 */
UInt32 BspUtils_memGetSystemHeapFreeSpace(void);

/**
 *  \brief Returns the buffer heap free memory (in bytes)
 */
UInt32 BspUtils_memGetBufferHeapFreeSpace(void);

/**
 *  \brief Init heap with user specified memory area
 *
 *  This API is used internally by BspUtils_memInit() and
 *  BspUtils_memInit_largeHeap()
 *  so typically user's will NOT use this API directly
 */
Int32 BspUtils_memInit_internal(UInt32 *pMemAddr, UInt32 memSize);

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_MEM_H_ */

/* @} */
