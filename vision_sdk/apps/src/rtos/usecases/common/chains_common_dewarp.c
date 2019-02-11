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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
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
#include <src/include/chains_common.h>
#include <src/include/chains_common_dewarp.h>



Ptr ChainsCommon_DeWarp_memAlloc(UInt32 size, UInt32 align)
{
    Ptr addr;
    addr = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                          size,
                          align);
    UTILS_assert(addr != NULL);
    return addr;
}

Void ChainsCommon_DeWarp_memFree(Ptr addr, UInt32 size)
{
    if(addr != NULL)
    {
        Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                      addr,
                      size);
    }
}

Int32 ChainsCommon_DeWarp_fileWrite(
            Int32 fileHndl,
            UInt8 *addr,
            UInt32 size)
{
    Int32 retVal = 0;

    if(fileHndl < 0)
    {
        retVal = -1;
        Vps_printf(" FILE: ERROR: Could not open FILE !!! \n");
    }
    else
    {
        /* write in units of chunkSize */
        Int32 chunkSize = DEWARP_FILEWRITE_CHUNKSIZE;
        UInt8  *curAddr;
        UInt32 numChunks, partChunk, cnt;

        curAddr  = addr;

        numChunks = size/chunkSize;
        partChunk = size % chunkSize;

        for(cnt = 0;cnt < numChunks;cnt ++)
        {
            /*
             *  write back the buffer
             */
            Cache_wb(curAddr,
                     chunkSize,
                     Cache_Type_ALLD,
                     TRUE);

            retVal = File_write(fileHndl, curAddr, (UInt32)chunkSize);
            if(retVal!=0)
            {
                /* error in writing, abort */
                break;
            }

            curAddr += chunkSize;
        }

        if(partChunk != 0)
        {
            retVal = File_write(fileHndl, curAddr, (UInt32)partChunk);
        }
    }

    return retVal;
}


Int32 ChainsCommon_DeWarp_fileRead(
            Int32 fileHndl,
            UInt8 *addr,
            UInt32 readSize,
            UInt32 *actualReadSize)
{
    Int32 retVal = 0;
    UInt8  *curAddr;

    UInt32 readDataSize, chunkSize = DEWARP_FILEREAD_CHUNKSIZE;
    UInt32 cnt, numChunks, partChunk;

    if(fileHndl < 0)
    {
        retVal = -1;
        *actualReadSize = 0;
        Vps_printf(" FILE: ERROR: Could not open FILE !!! \n");
    }
    else
    {
        curAddr = addr;

        numChunks = readSize/chunkSize;
        partChunk = readSize % chunkSize;

        *actualReadSize = 0;

        for(cnt = 0;cnt < numChunks;cnt ++)
        {
            File_read(fileHndl, curAddr, chunkSize, &readDataSize);

            /*
             *  Invalidate the buffer
             */
            Cache_inv(curAddr,
                      readDataSize,
                      Cache_Type_ALLD,
                      TRUE);

            curAddr += chunkSize;
            *actualReadSize += readDataSize;
        }

        if(partChunk != 0)
        {
            File_read(fileHndl, curAddr, partChunk, &readDataSize);
            *actualReadSize += readDataSize;
        }
    }

    return retVal;
}




/*
 *  DeWarp Media Init
 *  Based on ChainsCommon_SurroundView_mediaInit()
 *  But assume that there is no index file
 *
 */
Int32 ChainsCommon_DeWarp_mediaInit(
            ChainsCommon_DeWarp_mediaObj *pMediaObj,
            UInt32 *pLutFilePresent,
            UInt32 *pNumViewPoints,
            DEWARP_MEDIA_FILE fileType)
{
    *pLutFilePresent = FALSE;
    *pNumViewPoints = 0;

    pMediaObj->filePtr = 0;
    pMediaObj->idxBufPtr = 0;
    pMediaObj->idxBuf = NULL;

    pMediaObj->fp = -1;

    // read LUT from SD card if nw is NOT enabled
    // only limitation if Eth port0 is used
#ifndef BOARD_TYPE_TDA3XX_RVP
    if (!Utils_netIsNetworkEnabled())
#endif
    {
        if (DEWARP_MEDIA_FILE_LUT == fileType)
        {
            pMediaObj->fp = File_open(STEREO_FILENAME_LUT, "rb");

            if (0 > pMediaObj->fp)
            {
                Vps_printf("STEREO_MEDIA: Cannot open file (%s)\n",
                            STEREO_FILENAME_LUT);
                return SYSTEM_LINK_STATUS_EFAIL;
            }
        }
        else if (RSVP_MEDIA_FILE_LUT == fileType)
        {
            pMediaObj->fp = File_open(RSVP_FILENAME_LUT, "rb");

            if (0 > pMediaObj->fp)
            {
                Vps_printf("STEREO_MEDIA: Cannot open file (%s)\n",
                            RSVP_FILENAME_LUT);
                return SYSTEM_LINK_STATUS_EFAIL;
            }
        }
    }



    *pNumViewPoints = 1; // STEREO_MAX_NUM_VIEW_POINTS
    *pLutFilePresent = TRUE;


    return SYSTEM_LINK_STATUS_SOK;
}

Int32 ChainsCommon_DeWarp_mediaReadBlock(
        ChainsCommon_DeWarp_mediaObj *pMediaObj,
        AlgorithmLink_SrvCommonViewPointParams *pViewPointParams,
        UInt32 viewPointIdx,
        UInt32 chunkSize,
        DEWARP_MEDIA_FILE fileType)
{
    Int32 retVal;
    UInt32 readSize;
    UInt32 chunkOffset = 0;
    Int32 fp;


    if( (fileType == DEWARP_MEDIA_FILE_LUT) || (fileType == RSVP_MEDIA_FILE_LUT) )
    {
        fp = pMediaObj->fp;
    }

    retVal = File_seek(fp, chunkOffset);

    retVal = ChainsCommon_DeWarp_fileRead(
                        fp,
                        (UInt8*)pViewPointParams->baseBufAddr,
                        chunkSize,
                        &readSize);

    return retVal;
}


/*
 *    DeWarp Media DeInit
 */
Int32 ChainsCommon_DeWarp_mediaDeinit(
                ChainsCommon_DeWarp_mediaObj *pMediaObj)
{
    /*
     *    Close all the open files
     */
    // read LUT from SD card if nw is NOT enabled
    //  only limitation if Eth port0 is used
#ifndef BOARD_TYPE_TDA3XX_RVP
    if (!Utils_netIsNetworkEnabled())
#endif
    {
        if(pMediaObj->fp >= 0)
            File_close(pMediaObj->fp);
    }

    if(pMediaObj->idxBuf != NULL)
    {
        ChainsCommon_DeWarp_memFree(
                        pMediaObj->idxBuf,
                        DEWARP_MEDIA_SIZE_MAXIDX);
    }

    pMediaObj->filePtr = 0;
    pMediaObj->idxBufPtr = 0;

    return 0;
}

