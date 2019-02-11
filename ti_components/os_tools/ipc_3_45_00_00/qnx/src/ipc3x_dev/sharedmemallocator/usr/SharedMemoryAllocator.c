/*
 *  @file       SharedMemoryAllocator.c
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

#include "ti/shmemallocator/SharedMemoryAllocator.h"
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/slog.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define SHAREDMEMALLOCATOR_DRIVER_NAME         "/dev/shmemallocator"

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int shmHandler = -1;
static int ref_cnt = 0;

int initSHMHandler(int *SHMAllocatorDrv_handle)
{
    int status = 0;

    pthread_mutex_lock(&mutex);
    if (ref_cnt++ == 0) {
        *SHMAllocatorDrv_handle = open (SHAREDMEMALLOCATOR_DRIVER_NAME,
                                        O_SYNC | O_RDWR);
        if (*SHMAllocatorDrv_handle < 0) {
            slogf (42, _SLOG_DEBUG1, "\ninitSHMHandler: couldn't open shmemallocator device\n");
            ref_cnt--;
            status = -errno;
        } else {
            status = fcntl (*SHMAllocatorDrv_handle, F_SETFD, FD_CLOEXEC);
            if (status != 0) {
                slogf (42, _SLOG_DEBUG1, "\ninitSHMHandler: Failed to set file descriptor flags\n");
                status = -errno;
            }
        }
    }

    pthread_mutex_unlock(&mutex);
    return status;
}

void deinitSHMHandler(int SHMAllocatorDrv_handle)
{
    if(SHMAllocatorDrv_handle < 0){
        slogf (42, _SLOG_DEBUG1, "invalid SHMAllocatorDrv_handle value %d",SHMAllocatorDrv_handle);
        return;
    }

    pthread_mutex_lock(&mutex);

    if (--ref_cnt == 0) {
        close (SHMAllocatorDrv_handle);
    }
    pthread_mutex_unlock(&mutex);
}

int SHM_alloc(int size, shm_buf *buf)
{
    int status = 0;
    SHMAllocatorDrv_CmdArgs     cmdArgs;

    if(buf == NULL || size <= 0){
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc: Invalid arguments\n");
        return -1;
    }
    buf->phy_addr = NULL;
    buf->vir_addr = NULL;
    buf->blockID =  -1;
    buf->size = 0;

    status = initSHMHandler(&shmHandler);

    if (status < 0) {
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc: initSHMHandler Failed\n");
        return status;
    }

    cmdArgs.size = size;
    cmdArgs.blockID = 0;
    cmdArgs.alignment = 0;
    cmdArgs.result.phy_addr = 0;
    cmdArgs.result.vir_addr = 0;

    ioctl (shmHandler, CMD_SHMALLOCATOR_ALLOC, &cmdArgs);
    status = cmdArgs.apiStatus;
    if (status < 0) {
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc: IOCTL Failed \n");
        deinitSHMHandler(shmHandler);
        return status;
    }
    else {
        buf->phy_addr = cmdArgs.result.phy_addr;
        buf->vir_addr = cmdArgs.result.vir_addr;
        buf->blockID =  cmdArgs.result.blockID;
        buf->size = cmdArgs.result.size;
    }

    return (status);
}

int SHM_alloc_aligned(int size, uint alignment, shm_buf *buf)
{
    int status = 0;
    SHMAllocatorDrv_CmdArgs     cmdArgs;

    if(buf == NULL || size <= 0 || alignment == 0){
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc: Invalid arguments\n");
        return -1;
    }
    buf->phy_addr = NULL;
    buf->vir_addr = NULL;
    buf->blockID =  -1;
    buf->size = 0;

    status = initSHMHandler(&shmHandler);

    if (status < 0) {
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc_aligned: initSHMHandler Failed\n");
        return status;
    }

    cmdArgs.size = size;
    cmdArgs.blockID = 0;
    cmdArgs.alignment = alignment;
    cmdArgs.result.phy_addr = 0;
    cmdArgs.result.vir_addr = 0;

    ioctl (shmHandler, CMD_SHMALLOCATOR_ALLOC, &cmdArgs);
    status = cmdArgs.apiStatus;
    if (status < 0) {
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc_aligned: IOCTL Failed \n");
        deinitSHMHandler(shmHandler);
        return status;
    }
    else {
        buf->phy_addr = cmdArgs.result.phy_addr;
        buf->vir_addr = cmdArgs.result.vir_addr;
        buf->blockID =  cmdArgs.result.blockID;
        buf->size = cmdArgs.result.size;
    }

    return (status);
}

int SHM_alloc_fromBlock(int size, int blockID, shm_buf *buf)
{
    int status = 0;
    SHMAllocatorDrv_CmdArgs     cmdArgs;

    buf->phy_addr = NULL;
    buf->vir_addr = NULL;
    buf->blockID =  -1;
    buf->size = 0;

    if(buf == NULL || size <= 0 || blockID < MIN_BLOCKS_IDX || blockID > MAX_BLOCKS_IDX){
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc: Invalid arguments\n");
        return -1;
    }

    status = initSHMHandler(&shmHandler);

    if (status < 0) {
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc_fromBlock: initSHMHandler Failed\n");
        return status;
    }

    cmdArgs.size = size;
    cmdArgs.blockID = blockID;
    cmdArgs.alignment = 0;
    cmdArgs.result.phy_addr = 0;
    cmdArgs.result.vir_addr = 0;

    ioctl (shmHandler, CMD_SHMALLOCATOR_ALLOC, &cmdArgs);
    status = cmdArgs.apiStatus;
    if (status < 0) {
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc_fromBlock: IOCTL Failed \n");
        deinitSHMHandler(shmHandler);
        return status;
    }
    else {
        buf->phy_addr = cmdArgs.result.phy_addr;
        buf->vir_addr = cmdArgs.result.vir_addr;
        buf->blockID =  cmdArgs.result.blockID;
        buf->size = cmdArgs.result.size;
    }

    return (status);
}

int SHM_alloc_aligned_fromBlock(int size, uint alignment, int blockID,
                                shm_buf *buf)
{
    int status = 0;
    SHMAllocatorDrv_CmdArgs     cmdArgs;

    buf->phy_addr = NULL;
    buf->vir_addr = NULL;
    buf->blockID =  -1;
    buf->size = 0;

    if(buf == NULL || size <= 0 || alignment == 0 || blockID < MIN_BLOCKS_IDX || blockID > MAX_BLOCKS_IDX){
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc: Invalid arguments\n");
        return -1;
    }

    status = initSHMHandler(&shmHandler);

    if (status < 0) {
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc_aligned_fromBlock: initSHMHandler Failed\n");
        return status;
    }

    cmdArgs.size = size;
    cmdArgs.blockID = blockID;
    cmdArgs.alignment = alignment;
    cmdArgs.result.phy_addr = 0;
    cmdArgs.result.vir_addr = 0;

    ioctl (shmHandler, CMD_SHMALLOCATOR_ALLOC, &cmdArgs);
    status = cmdArgs.apiStatus;
    if (status < 0) {
        slogf (42, _SLOG_DEBUG1, "\nSHM_alloc: IOCTL Failed \n");
        deinitSHMHandler(shmHandler);
        return status;
    }
    buf->phy_addr = cmdArgs.result.phy_addr;
    buf->vir_addr = cmdArgs.result.vir_addr;
    buf->blockID =  cmdArgs.result.blockID;
    buf->size = cmdArgs.result.size;

    return (status);
}

/*!
 *  @brief      This function triggers the buffer release  in the kernel.
 *
 *  @param    buf   Pointer to the buffer address information
 *
 *  @return     0       Success.
 *                 -1     Failure in ioctl call.
 *
 */
int SHM_release(shm_buf *buf)

{
    int                       status      = 0;
    SHMAllocatorDrv_CmdArgs     cmdArgs;

    if(buf == NULL){
        slogf (42, _SLOG_DEBUG1, "\nSHM_release: Invalid arguments\n");
        return -1;
    }
    if(buf->blockID < MIN_BLOCKS_IDX || buf->blockID > MAX_BLOCKS_IDX || buf->vir_addr == NULL){
        slogf (42, _SLOG_DEBUG1, "\nSHM_release: Invalid arguments\n");
        return -1;
    }
    cmdArgs.result.phy_addr = buf->phy_addr;
    cmdArgs.result.vir_addr = buf->vir_addr;
    cmdArgs.blockID = buf->blockID;

    ioctl (shmHandler, CMD_SHMALLOCATOR_RELEASE, &cmdArgs);
    status = cmdArgs.apiStatus;

    if (status < 0) {
        slogf (42, _SLOG_DEBUG1, "\nRELEASE IOCTL failed\n");
    }

    deinitSHMHandler (shmHandler);

    return (status);
}

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
