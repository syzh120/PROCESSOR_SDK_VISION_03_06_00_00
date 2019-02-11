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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/include/chains_common_osal.h>

/*******************************************************************************
 *  FUNCTIONS
 *******************************************************************************
 */
#if defined(LINUX_BUILD) || defined(QNX_BUILD)

/* File Open */
Int32 ChainsCommon_Osal_fileOpen(
                    char *fileName,
                    ChainsCommon_Osal_FileMode fileMode)
{
    FILE *fp = NULL;
    char mmcsdFileName[128U];

    snprintf(mmcsdFileName, sizeof(mmcsdFileName), "/%s/%s/%s",\
                                MMCSD_MOUNT_PT, SRV_DIR_2X, fileName);

    switch (fileMode)
    {
        case CHAINSCOMMON_OSAL_FILEMODE_READ:
            fp = fopen(mmcsdFileName, "r");
            break;

        case CHAINSCOMMON_OSAL_FILEMODE_WRITE:
            fp = fopen(mmcsdFileName, "w");
            break;

        case CHAINSCOMMON_OSAL_FILEMODE_READ_BIN:
            fp = fopen(mmcsdFileName, "rb");
            break;

        case CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN:
            fp = fopen(mmcsdFileName, "wb");
            break;
    }

    if (NULL == fp)
    {
        return (-1);
    }
    else
    {
        return ((Int32)fp);
    }
}

/* File Close */
Void ChainsCommon_Osal_fileClose(Int32 fp)
{
    if (-1 != fp)
    {
        fclose((FILE*)fp);
    }
}

/* File Seek */
Void ChainsCommon_Osal_fileSeek(Int32 fp, UInt32 seekOffset)
{
    if (-1 != fp)
    {
        fseek((FILE*)fp, seekOffset, SEEK_SET);
    }
}

/* File Seek */
Int32 ChainsCommon_Osal_fileChDir(char *dirName)
{
    return (0);
}

/* File Read */
Int32 ChainsCommon_Osal_fileRead(
                            Int32 fp,
                            UInt8 *addr,
                            UInt32 readSize,
                            UInt32 *actualReadSize)
{
    Int32 retVal = 0;
    UInt8  *curAddr;

    UInt32 readDataSize, chunkSize = CHAINSCOMMON_OSAL_FILEREAD_CHUNKSIZE;
    UInt32 cnt, numChunks, partChunk;

    if (-1 == fp)
    {
        retVal = -1;
        *actualReadSize = 0;
    }
    else
    {
        curAddr = addr;

        numChunks = readSize/chunkSize;
        partChunk = readSize % chunkSize;

        *actualReadSize = 0;

        for(cnt = 0;cnt < numChunks;cnt ++)
        {
            readDataSize = fread(curAddr, 1U, chunkSize, (FILE*)fp);

            curAddr += chunkSize;
            *actualReadSize += readDataSize;
        }

        if(partChunk != 0)
        {
            readDataSize = fread(curAddr, 1U, partChunk, (FILE*)fp);
            *actualReadSize += readDataSize;
        }

        /*
         *  Invalidate the buffer
         */
        OSA_memCacheInv((UInt32)addr, readSize);
    }

    return retVal;
}

/* File Write */
Int32 ChainsCommon_Osal_fileWrite(
                                Int32 fp,
                                UInt8 *addr,
                                UInt32 size)
{
    Int32 retVal = 0;

    if (-1 == fp)
    {
        retVal = -1;
    }
    else
    {
        /* write in units of chunkSize */
        Int32 chunkSize = CHAINSCOMMON_OSAL_FILEWRITE_CHUNKSIZE;
        UInt8  *curAddr;
        UInt32 numChunks, partChunk, cnt;

        /*
         *  write back the buffer
         */
        OSA_memCacheWb((UInt32)addr, ((UInt32)addr + size));

        curAddr  = addr;

        numChunks = size/chunkSize;
        partChunk = size % chunkSize;

        for(cnt = 0;cnt < numChunks;cnt ++)
        {
            retVal = fwrite(curAddr, 1U, chunkSize, (FILE*)fp);
            if(retVal != chunkSize)
            {
                /* error in writing, abort */
                break;
            }

            curAddr += chunkSize;
        }

        if(partChunk != 0)
        {
            retVal = fwrite(curAddr, 1U, partChunk, (FILE*)fp);
        }
    }

    return retVal;
}

Ptr ChainsCommon_Osal_memAlloc(UInt32 size, UInt32 align)
{
    Ptr addr;
    addr = OSA_memAllocSR(OSA_HEAPID_DDR_CACHED_SR1, size, align);
    UTILS_assert(addr != NULL);

    addr = (Void*) ChainsCommon_Osal_getPhysAddr((UInt32)addr);
    return addr;
}

Void ChainsCommon_Osal_memFree(Ptr addr, UInt32 size)
{
    if(addr != NULL)
    {
        OSA_memFreeSR(OSA_HEAPID_DDR_CACHED_SR1,
            (Ptr)ChainsCommon_Osal_getVirtAddr((UInt32)addr), size);
    }
}

Void ChainsCommon_Osal_cacheInv(UInt32 addr, UInt32 size)
{
    OSA_memCacheInv(addr, size);
}

Void ChainsCommon_Osal_cacheWb(UInt32 addr, UInt32 size)
{
    OSA_memCacheWb(addr, (addr + size));
}

/* 2D memory copy */
Ptr ChainsCommon_Osal_dmaCreate()
{
    return (NULL);
}

Void ChainsCommon_Osal_dmaDelete(Ptr dmaChObj)
{
    return;
}

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
                        UInt32 srcStartY)
{
    UInt32 ht;
    UInt32 bytesPerPixel = 1U;

    if ((SYSTEM_DF_YUV422I_YUYV == dataFormat)   ||
        (SYSTEM_DF_YUV422I_UYVY == dataFormat))
    {
        bytesPerPixel = 2U;
    }
    else
    {
        ChainsCommon_Osal_cacheInv(srcAddr1,
                                (bytesPerPixel * srcPitch1 * height/2));

        for (ht = 0U;ht < height/2;ht++)
        {
            memcpy(
                (Ptr)(destAddr1 + (ht * destPitch)),
                (Ptr)(srcAddr1 + (ht * srcPitch1)),
                width * bytesPerPixel);
        }

        ChainsCommon_Osal_cacheWb(destAddr1,
                                (bytesPerPixel * destPitch * height/2));
    }

    ChainsCommon_Osal_cacheInv(srcAddr0, (bytesPerPixel * srcPitch0 * height));

    for (ht = 0U;ht < height;ht++)
    {
        memcpy(
            (Ptr)(destAddr0 + (ht * destPitch)),
            (Ptr)(srcAddr0 + (ht * srcPitch0)),
            width * bytesPerPixel);
    }

    ChainsCommon_Osal_cacheWb(destAddr0,
                            (bytesPerPixel * destPitch * height));

    return 0;
}

Ptr ChainsCommon_Osal_mutexCreate()
{
    OSA_MutexHndl *mutexHndl;

    mutexHndl = ChainsCommon_Osal_memAlloc(sizeof(OSA_MutexHndl), 32U);

    OSA_mutexCreate(
            (OSA_MutexHndl*)ChainsCommon_Osal_getVirtAddr((UInt32)mutexHndl));
    ChainsCommon_Osal_mutexWait((Ptr)mutexHndl);

    return ((Ptr)mutexHndl);
}

Void ChainsCommon_Osal_mutexDelete(Ptr mutexHndl)
{
    if (NULL != mutexHndl)
    {
        OSA_mutexDelete(
            (OSA_MutexHndl*)ChainsCommon_Osal_getVirtAddr((UInt32)mutexHndl));
        ChainsCommon_Osal_memFree(mutexHndl, sizeof(OSA_MutexHndl));
    }
}

Void ChainsCommon_Osal_mutexPost(Ptr mutexHndl)
{
    if (NULL != mutexHndl)
    {
        OSA_mutexUnlock(
            (OSA_MutexHndl*)ChainsCommon_Osal_getVirtAddr((UInt32)mutexHndl));
    }
}

Void ChainsCommon_Osal_mutexWait(Ptr mutexHndl)
{
    if (NULL != mutexHndl)
    {
        OSA_mutexLock(
            (OSA_MutexHndl*)ChainsCommon_Osal_getVirtAddr((UInt32)mutexHndl));
    }
}

UInt32 ChainsCommon_Osal_getCurTimeMsec()
{
    return (0U);
}

UInt32 ChainsCommon_Osal_getVirtAddr(UInt32 phyAddr)
{
    UInt32 virtAddr;

    virtAddr = OSA_memPhys2Virt(
                            (unsigned int)phyAddr,
                            OSA_MEM_REGION_TYPE_AUTO);

    return (virtAddr);
}

UInt32 ChainsCommon_Osal_getPhysAddr(UInt32 virtAddr)
{
    UInt32 physAddr;

    physAddr = OSA_memVirt2Phys(
                            (unsigned int)virtAddr,
                            OSA_MEM_REGION_TYPE_AUTO);

    return (physAddr);
}

Void ChainsCommon_Osal_eraseSrvCalibTable(UInt32 offset, UInt32 size)
{
    OSA_fileCreateFile(
                CALIBDATA_FILENAME,
                (offset + size),
                TRUE);
}


UInt32 ChainsCommon_Osal_map(UInt32 addr, UInt32 size)
{
    return OSA_memMap(addr, size);
}
void ChainsCommon_Osal_unmap(UInt32 addr, UInt32 size)
{
    int status;

    status = OSA_memUnMap(addr, size);

    UTILS_assert(OSA_SOK == status);
}

Int32 ChainsCommon_Osal_fileSize(Int32 fp)
{
    return (0);
}

/* file delete*/
/* Untested with Linux build */
Int32 ChainsCommon_Osal_fileDelete(char *fileName)
{
    return remove(fileName);
}

#else

/* File Open */
Int32 ChainsCommon_Osal_fileOpen(
                    char *fileName,
                    ChainsCommon_Osal_FileMode fileMode)
{
    Int32 fp = -1;

    switch (fileMode)
    {
        case CHAINSCOMMON_OSAL_FILEMODE_READ:
            fp = File_open(fileName, "r");
            break;

        case CHAINSCOMMON_OSAL_FILEMODE_WRITE:
            fp = File_open(fileName, "w");
            break;

        case CHAINSCOMMON_OSAL_FILEMODE_READ_BIN:
            fp = File_open(fileName, "rb");
            break;

        case CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN:
            fp = File_open(fileName, "wb");
            break;
    }

    if (0 > fp)
    {
        return (-1);
    }
    else
    {
        return fp;
    }
}

/* File Close */
Void ChainsCommon_Osal_fileClose(Int32 fp)
{
    if (-1 != fp)
    {
        File_close(fp);
    }
}

/* File Seek */
Void ChainsCommon_Osal_fileSeek(Int32 fp, UInt32 seekOffset)
{
    if (-1 != fp)
    {
        File_seek(fp, seekOffset);
    }
}

/* File Change Directory */
Int32 ChainsCommon_Osal_fileChDir(char *dirName)
{
    Int32 retVal = 0;
    char fatDirName[128U];

    sprintf(fatDirName,"/%s",dirName);
    retVal = File_chDir(fatDirName);

    return retVal;
}

/* Get file size*/
Int32 ChainsCommon_Osal_fileSize(Int32 fp)
{
    if (-1 != fp)
    {
        return File_size(fp);
    }
    return -1;
}

/* file delete*/
Int32 ChainsCommon_Osal_fileDelete(char *fileName)
{
    return File_delete(fileName);
}

/* File Read */
Int32 ChainsCommon_Osal_fileRead(
                            Int32 fp,
                            UInt8 *addr,
                            UInt32 readSize,
                            UInt32 *actualReadSize)
{
    Int32 retVal = 0;
    UInt8  *curAddr;

    UInt32 readDataSize, chunkSize = CHAINSCOMMON_OSAL_FILEREAD_CHUNKSIZE;
    UInt32 cnt, numChunks, partChunk;

    if (-1 == fp)
    {
        retVal = -1;
        *actualReadSize = 0;
    }
    else
    {
        Cache_wb(
                addr,
                readSize,
                Cache_Type_ALLD,
                TRUE);

        curAddr = addr;

        numChunks = readSize/chunkSize;
        partChunk = readSize % chunkSize;

        *actualReadSize = 0;

        for(cnt = 0;cnt < numChunks;cnt ++)
        {
            File_read(fp, curAddr, chunkSize, &readDataSize);

            curAddr += chunkSize;
            *actualReadSize += readDataSize;
        }

        if(partChunk != 0)
        {
            File_read(fp, curAddr, partChunk, &readDataSize);
            *actualReadSize += readDataSize;
        }

        /*
         *  Invalidate the buffer
         */
        Cache_inv(addr,
                  readSize,
                  Cache_Type_ALLD,
                  TRUE);
    }

    return retVal;
}

/* File Write */
Int32 ChainsCommon_Osal_fileWrite(
                                Int32 fp,
                                UInt8 *addr,
                                UInt32 size)
{
    Int32 retVal = 0;

    if (-1 == fp)
    {
        retVal = -1;
        Vps_printf(" FILE: ERROR: Could not open FILE !!! \n");
    }
    else
    {
        /* write in units of chunkSize */
        Int32 chunkSize = CHAINSCOMMON_OSAL_FILEWRITE_CHUNKSIZE;
        UInt8  *curAddr;
        UInt32 numChunks, partChunk, cnt;

        /*
         *  write back the buffer
         */
        Cache_wb(addr,
                 size,
                 Cache_Type_ALLD,
                 TRUE);

        curAddr  = addr;

        numChunks = size/chunkSize;
        partChunk = size % chunkSize;

        for(cnt = 0;cnt < numChunks;cnt ++)
        {
            retVal = File_write(fp, curAddr, (UInt32)chunkSize);
            if(retVal != 0)
            {
                /* error in writing, abort */
                break;
            }

            curAddr += chunkSize;
        }

        if(partChunk != 0)
        {
            retVal = File_write(fp, curAddr, (UInt32)partChunk);
        }
    }

    return retVal;
}

/* Memory Alloc */
Ptr ChainsCommon_Osal_memAlloc(UInt32 size, UInt32 align)
{
    Ptr addr;
    addr = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                          size,
                          align);
    UTILS_assert(addr != NULL);
    return addr;
}

/* Memory Free */
Void ChainsCommon_Osal_memFree(Ptr addr, UInt32 size)
{
    if(addr != NULL)
    {
        Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                      addr,
                      size);
    }
}

Void ChainsCommon_Osal_cacheInv(UInt32 addr, UInt32 size)
{
    Cache_inv(
            (Ptr)addr,
            size,
            Cache_Type_ALLD,
            TRUE);
}

Void ChainsCommon_Osal_cacheWb(UInt32 addr, UInt32 size)
{
    Cache_wb(
            (Ptr)addr,
            size,
            Cache_Type_ALLD,
            TRUE);
}

/* 2D memory copy */
Ptr ChainsCommon_Osal_dmaCreate()
{
    Int32 retVal;
    Utils_DmaChCreateParams dmaParams;
    Ptr dmaChObj = ChainsCommon_Osal_memAlloc(sizeof(Utils_DmaChObj), 32U);

    Utils_DmaChCreateParams_Init(&dmaParams);
    retVal = Utils_dmaCreateCh(
                        (Utils_DmaChObj*)dmaChObj,
                        &dmaParams);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

    return (dmaChObj);
}

Void ChainsCommon_Osal_dmaDelete(Ptr dmaChObj)
{
    if (NULL != dmaChObj)
    {
        Utils_dmaDeleteCh((Utils_DmaChObj*)dmaChObj);
        ChainsCommon_Osal_memFree(dmaChObj, sizeof(Utils_DmaChObj));
    }
}

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
                        UInt32 srcStartY)
{
    Int32 status;
    Utils_DmaCopyFill2D dmaPrm;

    dmaPrm.dataFormat   = dataFormat;
    dmaPrm.destAddr[0]  = (Ptr)destAddr0;
    dmaPrm.destAddr[1]  = (Ptr)destAddr1;
    dmaPrm.destPitch[0] = destPitch;
    dmaPrm.destPitch[1] = destPitch;
    dmaPrm.destStartX   = destStartX;
    dmaPrm.destStartY   = destStartY;
    dmaPrm.width        = width;
    dmaPrm.height       = height;
    dmaPrm.srcAddr[0]   = (Ptr)srcAddr0;
    dmaPrm.srcAddr[1]   = (Ptr)srcAddr1;
    dmaPrm.srcPitch[0]  = srcPitch0;
    dmaPrm.srcPitch[1]  = srcPitch1;
    dmaPrm.srcStartX    = srcStartX;
    dmaPrm.srcStartY    = srcStartY;

    status = Utils_dmaCopy2D(
                    (Utils_DmaChObj*)pDmaChObj,
                    &dmaPrm,
                    1U);
    UTILS_assert (SYSTEM_LINK_STATUS_SOK == status);

    return (status);
}

Ptr ChainsCommon_Osal_mutexCreate()
{
    BspOsal_SemHandle *mutexHndl;

    mutexHndl = ChainsCommon_Osal_memAlloc(sizeof(BspOsal_SemHandle), 32U);

    *mutexHndl = BspOsal_semCreate(0, (Bool)TRUE);
    UTILS_assert(NULL != *mutexHndl);

    return (mutexHndl);
}

Void ChainsCommon_Osal_mutexDelete(Ptr mutexHndl)
{
    if (NULL != mutexHndl)
    {
        BspOsal_semDelete((BspOsal_SemHandle*)mutexHndl);
        ChainsCommon_Osal_memFree(mutexHndl, sizeof(BspOsal_SemHandle));
    }
}

Void ChainsCommon_Osal_mutexPost(Ptr mutexHndl)
{
    if (NULL != mutexHndl)
    {
        BspOsal_semPost(*((BspOsal_SemHandle*)mutexHndl));
    }
}

Void ChainsCommon_Osal_mutexWait(Ptr mutexHndl)
{
    if (NULL != mutexHndl)
    {
        BspOsal_semWait(*((BspOsal_SemHandle*)mutexHndl),\
                                                        BSP_OSAL_WAIT_FOREVER);
    }
}

UInt32 ChainsCommon_Osal_getCurTimeMsec()
{
    return (Utils_getCurTimeInMsec());
}

UInt32 ChainsCommon_Osal_getVirtAddr(UInt32 phyAddr)
{
    return (phyAddr);
}

UInt32 ChainsCommon_Osal_getPhysAddr(UInt32 virtAddr)
{
    return (virtAddr);
}

Void ChainsCommon_Osal_eraseSrvCalibTable(UInt32 offset, UInt32 size)
{
    System_qspiEraseSector(offset, size);
}

UInt32 ChainsCommon_Osal_map(UInt32 addr, UInt32 size)
{
    return addr;
}
void ChainsCommon_Osal_unmap(UInt32 addr, UInt32 size)
{
}

#endif
