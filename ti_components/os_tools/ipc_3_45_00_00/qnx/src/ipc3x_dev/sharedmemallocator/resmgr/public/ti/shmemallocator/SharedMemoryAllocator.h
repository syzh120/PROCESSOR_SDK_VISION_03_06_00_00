/*
 *  @file   SharedMemoryAllocator.h
 *
 *  @brief      User side Shared Memory Allocator
 *
 *  ============================================================================
 *
 */
/*
 *  Copyright (c) 2012, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */

#include <sys/ioctl.h>

struct shm_req_params {
    int size;
    int blockID;
    struct {
        int req;
        int alignment;
    }alignReq;
};

typedef struct {
    unsigned long phy_addr;
    unsigned long vir_addr;
    int size;
    int blockID;
}shm_buf;

typedef enum {
    SHMALLOCATOR_CMD_ALLOC = 1,
    SHMALLOCATOR_CMD_RELEASE = 2,
} SHMAllocator_cmd_types;

typedef struct SHMAllocatorDrv_CmdArgs_Tag {
    struct {
        unsigned long phy_addr;
        unsigned long vir_addr;
        int blockID;
        int size;
    } result;
    int size;
    unsigned int alignment;
    int blockID;
    int apiStatus;

} SHMAllocatorDrv_CmdArgs;

/*!
 *  @brief  Command for SHM_alloc
 */
#define SHMALLOCATORDRV_BASE_CMD                 (0x1C)

#define CMD_SHMALLOCATOR_ALLOC            _IOWR(SHMALLOCATORDRV_BASE_CMD,\
                                            SHMALLOCATOR_CMD_ALLOC,\
                                            SHMAllocatorDrv_CmdArgs)
/*!
 *  @brief  Command for SHM_release
 */
#define CMD_SHMALLOCATOR_RELEASE            _IOWR(SHMALLOCATORDRV_BASE_CMD,\
                                            SHMALLOCATOR_CMD_RELEASE,\
                                            SHMAllocatorDrv_CmdArgs)

enum {
    MIN_BLOCKS_IDX=0,
    MAX_BLOCKS_IDX,
};

/*  ----------------------------------------------------------------------------
 *  Command arguments for SharedMemAllocator
 *  ----------------------------------------------------------------------------
 */
/*!
 *  @brief  Command arguments for SharedMemAllocator
 */
