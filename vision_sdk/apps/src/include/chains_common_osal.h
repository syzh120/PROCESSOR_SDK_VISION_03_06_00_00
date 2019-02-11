/******************************************************************************
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
******************************************************************************/

/*
 *******************************************************************************
 *
 * \file chains_common_osal.h
 *
 * \brief This file contains common utility functions used by SV use cases
 *
 *******************************************************************************
 */

#ifndef _CHAINS_COMMON_OSAL_H_
#define _CHAINS_COMMON_OSAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */
#if defined(LINUX_BUILD) || defined(QNX_BUILD)
    #include <apps/src/hlos/common/chains_common.h>
    #include <links_fw/src/hlos/osa/include/osa_mem.h>
    #include <links_fw/src/hlos/system/system_priv_ipc.h>
    #include <links_fw/src/hlos/osa/include/osa_file.h>
#else
    #include <src/include/chains_common.h>
#endif

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define CHAINSCOMMON_OSAL_FILEWRITE_CHUNKSIZE       (96U * 1024U)   /* Bytes */
#define CHAINSCOMMON_OSAL_FILEREAD_CHUNKSIZE        (100U * 1024U)  /* Bytes */

/* Imported from qspi_flash.h */
#define QSPIFLASH_BLOCKSIZE                         (64U * 1024U)

#ifdef BUILD_INFOADAS
#ifdef QNX_BUILD
#define MMCSD_MOUNT_PT                      "tmp"
#else
#define MMCSD_MOUNT_PT                      ""
#endif
#else
#define MMCSD_MOUNT_PT                      "mnt"
#endif
/*******************************************************************************
 *  Structures and enums
 *******************************************************************************
 */
typedef enum
{
    CHAINSCOMMON_OSAL_FILEMODE_READ,
    CHAINSCOMMON_OSAL_FILEMODE_WRITE,
    CHAINSCOMMON_OSAL_FILEMODE_READ_BIN,
    CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN

} ChainsCommon_Osal_FileMode;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
Int32 ChainsCommon_Osal_fileOpen(
                    char *fileName,
                    ChainsCommon_Osal_FileMode fileMode);
Void ChainsCommon_Osal_fileClose(Int32 fp);
Void ChainsCommon_Osal_fileSeek(Int32 fp, UInt32 seekOffset);
Int32 ChainsCommon_Osal_fileChDir(char *dirName);
Int32 ChainsCommon_Osal_fileSize(Int32 fp);
Int32 ChainsCommon_Osal_fileDelete(char *fileName);
Int32 ChainsCommon_Osal_fileRead(
                            Int32 fp,
                            UInt8 *addr,
                            UInt32 readSize,
                            UInt32 *actualReadSize);
Int32 ChainsCommon_Osal_fileWrite(
                                Int32 fp,
                                UInt8 *addr,
                                UInt32 size);
Ptr ChainsCommon_Osal_memAlloc(UInt32 size, UInt32 align);
Void ChainsCommon_Osal_memFree(Ptr addr, UInt32 size);
Void ChainsCommon_Osal_cacheInv(UInt32 addr, UInt32 size);
Void ChainsCommon_Osal_cacheWb(UInt32 addr, UInt32 size);
Ptr ChainsCommon_Osal_dmaCreate();
Void ChainsCommon_Osal_dmaDelete(Ptr dmaChObj);
Int32 ChainsCommon_Osal_dmaCopy2D(
                        Ptr pDmaChObj,
                        UInt32 dataFormat,
                        UInt32 destAddr0,
                        UInt32 destAddr1,
                        UInt32 destPitch,
                        UInt32 destStartX,
                        UInt32 destStartY,
                        UInt32 width,
                        UInt32 height,
                        UInt32 srcAddr0,
                        UInt32 srcAddr1,
                        UInt32 srcPitch0,
                        UInt32 srcPitch1,
                        UInt32 srcStartX,
                        UInt32 srcStartY);
Ptr ChainsCommon_Osal_mutexCreate();
Void ChainsCommon_Osal_mutexDelete(Ptr mutexHndl);
Void ChainsCommon_Osal_mutexPost(Ptr mutexHndl);
Void ChainsCommon_Osal_mutexWait(Ptr mutexHndl);
UInt32 ChainsCommon_Osal_getCurTimeMsec();
UInt32 ChainsCommon_Osal_getVirtAddr(UInt32 phyAddr);
UInt32 ChainsCommon_Osal_getPhysAddr(UInt32 virtAddr);
Void ChainsCommon_Osal_eraseSrvCalibTable(UInt32 offset, UInt32 size);

UInt32 ChainsCommon_Osal_map(UInt32 addr, UInt32 size);
void ChainsCommon_Osal_unmap(UInt32 addr, UInt32 size);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */


