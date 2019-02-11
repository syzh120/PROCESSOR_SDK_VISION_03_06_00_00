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

#include <include/common/chains_radar.h>
#include <include/common/chains_radar_file_io.h>

#define FILEIO_MAX_FRAMES (256000U)
#define MAXFILESIZE (107374182400) /* Max file size to write is 100 MB */

typedef struct {
    Bool fileReadOpen;
    /**< Bool to specify Read file open done or not */
    Bool fileWriteOpen;
    /**< Bool to specify Write file open done or not */
    Int32 fpReadDataStream;
    /**< Binary File containing the Read stream data.*/
    Int32 fpWriteDataStream;
    /**< Binary File containing the Write stream data.*/
    Int32 fpWriteIndexFile;
    /**< File used to index into fpWriteDataStream.
    * It will contain frame sizes in bytes.
    */
    UInt32 dataSizeWritten;
    /**< Total number of bytes written to file */
    UInt32 curRdFrameId;
    /**< Current Read frame being parsed from file */
    UInt32 curWrFrameId;
    /**< Current Write frame being parsed from file */
    UInt32 numFrames;
    /**< number of frames in input file */
    UInt32 frameSize;
    /**< size of input read frame size */
}channelObj;

typedef struct {
    UInt32 numReadCh;
    /**< Number of Read Channel opened  */
    UInt32 numWriteCh;
    /**< Number of Write Channel opened  */
    FileIO_CfgOptions fOpt;
    /**< File configuration options  */
    channelObj chObj[FILE_IO_MAX_CH];
    /**< Channel configuration options  */
} Chains_fileIOStatus;

typedef struct {
    Bool    read;
    /**< File Read Status */
    Bool    writeStart;
    /**< File Write start status */
    Bool    writePause;
    /**< File Write pause status */
    Bool    writeStop;
    /**< File Write stop status */
    Bool    writeOneFrame;
    /**< File Write One frame status */
}fileIOStatus;

fileIOStatus gfileIOStatus[FILE_IO_MAX_CH];

Chains_fileIOStatus *gpFileIOObj;

static Int32 readData(Chains_fileIOStatus *pfileIOObj,UInt32 channelId,
                                const System_Buffer *pBuffer);

static Int32 writeData(Chains_fileIOStatus *pfileIOObj,UInt32 channelId,
                                const System_Buffer *pBuffer);

static Int32 getFileName(char *fileName,UInt32 chId);
static Chains_fileIOState getReadStatus(UInt32 ChId);
static Chains_fileIOState getWriteStatus(UInt32 ChId);

static Int32 fileWriteClose(Chains_fileIOStatus *pfileIOObj,UInt32 chId);
static Int32 fileReadClose(Chains_fileIOStatus *pfileIOObj,UInt32 chId);

char gChains_fileIORunTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n FILE IO Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n a: Write Start "
    "\r\n b: Write Pause "
    "\r\n c: Write Resume "
    "\r\n d: Write Stop "
    "\r\n e: Write One Frame "
    "\r\n "
    "\r\n x: Exit from FileIOMenu "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};
char Chains_fileIORunTimeMenu()
{
    Vps_printf(gChains_fileIORunTimeMenu);
    return Chains_readChar();
}

Void Chains_fileIOMenu()
{
    UInt32 done = FALSE;
    char ch;
    while(!done)
    {
        ch = Chains_fileIORunTimeMenu();
        switch(ch)
        {
            case 'x':
                done = TRUE;
            break;

            case 'a':
                Chains_setAllChannelState(CHAINS_WRITE_START);
            break;

            case 'b':
                Chains_setAllChannelState(CHAINS_WRITE_PAUSE);
            break;

            case 'c':
                Chains_setAllChannelState(CHAINS_WRITE_RESUME);
            break;

            case 'd':
                Chains_setAllChannelState(CHAINS_WRITE_STOP);
            break;

            case 'e':
                Chains_setAllChannelState(CHAINS_WRITE_ONEFRAME);
            break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
            break;
        }
    }
}

Void Chains_setAllChannelState(Chains_fileIOState state)
{
    UInt32 i;
    for(i = 0; i < FILE_IO_MAX_CH; i++)
    {
        Chains_setChannelState(state,i);
    }
}

Void Chains_setChannelState(Chains_fileIOState state,UInt32 i)
{
    switch(state)
    {
        case CHAINS_READ_START :
                gfileIOStatus[i].read = TRUE;
        break;
        case CHAINS_READ_STOP:
                Vps_printf("FILE_IO: File Read Pause/Stop \n");
                gfileIOStatus[i].read = FALSE;
        break;
        case CHAINS_WRITE_START:
                Vps_printf("FILE_IO: File Write Start \n");
                gfileIOStatus[i].writeStart = TRUE;
                gfileIOStatus[i].writePause = FALSE;
                gfileIOStatus[i].writeStop = FALSE;
        break;
        case CHAINS_WRITE_PAUSE:
                Vps_printf("FILE_IO: File Write Pause \n");
                gfileIOStatus[i].writePause = TRUE;
                gfileIOStatus[i].writeStop = FALSE;
        break;
        case CHAINS_WRITE_RESUME:
                Vps_printf("FILE_IO: File Write Resume \n");
                gfileIOStatus[i].writePause = FALSE;
                gfileIOStatus[i].writeStop = FALSE;
        break;
        case CHAINS_WRITE_STOP:
                Vps_printf("FILE_IO: File Write Stop \n");
                gfileIOStatus[i].writeOneFrame = FALSE;
                gfileIOStatus[i].writeStart = FALSE;
                gfileIOStatus[i].writePause = FALSE;
                gfileIOStatus[i].writeStop = TRUE;
        break;
        case CHAINS_WRITE_ONEFRAME:
                Vps_printf("FILE_IO: Write One frame \n");
                gfileIOStatus[i].writeOneFrame = TRUE;
        break;
        case CHAINS_WRITE_IDLE:
                gfileIOStatus[i].writeStart = FALSE;
                gfileIOStatus[i].writePause = FALSE;
                gfileIOStatus[i].writeStop = FALSE;
                gfileIOStatus[i].writeOneFrame = FALSE;
        break;
        default:
            Vps_printf("FILE_IO: Invalid input \n");
        break;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Read Frame CallBack
 *
 *          Call back function registered with NullSrc .
 *
 * \param pChInfo    [IN] System Link Channel Obj
 * \param pBuf       [IN] System buffer to fill data
 * \param arg        [IN] Call Back Args
 *
 *******************************************************************************
*/
Void Chains_readFrameCb(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg)
{
    Int32 status;
    FileIO_CreateParams *pFileObj = (FileIO_CreateParams *)arg;
    Chains_fileIOStatus *pfileIOObj = pFileObj->fileIOHandle;
    System_Buffer *pBuffer = (System_Buffer*)pBuf;

    if(getReadStatus(pBuffer->chNum) != CHAINS_READ_STOP)
    {
        if(pfileIOObj->chObj[pBuffer->chNum].fileReadOpen != TRUE)
        {
            status = Chains_fileOpen(pFileObj,pBuffer->chNum,
                        CHAINS_FILEMODE_READ);
            if(status == SYSTEM_LINK_STATUS_SOK)
            {
                pfileIOObj->chObj[pBuffer->chNum].fileReadOpen = TRUE;
            }
            else
            {
                Vps_printf("FILE_IO: File Read Open Failed \n");
            }
        }
        if(pfileIOObj->chObj[pBuffer->chNum].fileReadOpen == TRUE)
        {
            status = readData(pfileIOObj,pBuffer->chNum, pBuffer);
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Write Frame CallBack
 *
 *          Call back function registered with Null  .
 *
 * \param pChInfo    [IN] System Link Channel Obj
 * \param pBuf       [IN] System buffer to fill data
 * \param arg        [IN] Call Back Args
 *
 *******************************************************************************
*/
Void Chains_writeFrameCb(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg)
{
    Int32 status;
    FileIO_CreateParams *pFileObj = (FileIO_CreateParams *)arg;
    Chains_fileIOStatus *pfileIOObj = pFileObj->fileIOHandle;
    System_Buffer *pBuffer = (System_Buffer*)pBuf;
    Chains_fileIOState state;

    state = getWriteStatus(pBuffer->chNum);
    if((state == CHAINS_WRITE_START) || (state == CHAINS_WRITE_ONEFRAME))
    {
        if(pfileIOObj->chObj[pBuffer->chNum].fileWriteOpen != TRUE)
        {
            status = Chains_fileOpen(pFileObj,pBuffer->chNum,
                                        CHAINS_FILEMODE_WRITE_BIN);
            if(status == SYSTEM_LINK_STATUS_SOK)
            {
                pfileIOObj->chObj[pBuffer->chNum].fileWriteOpen = TRUE;
                Vps_printf("FILE_IO: File Write started for Ch no %d \n ",pBuffer->chNum);
            }

        }
        if(pfileIOObj->chObj[pBuffer->chNum].fileWriteOpen == TRUE)
        {
            status = writeData(pfileIOObj,pBuffer->chNum, pBuffer);

            if(state == CHAINS_WRITE_ONEFRAME)
            {
                fileWriteClose(pfileIOObj,pBuffer->chNum);
                Chains_setChannelState(CHAINS_WRITE_STOP,pBuffer->chNum);
                Chains_setChannelState(CHAINS_WRITE_IDLE,pBuffer->chNum);
                Vps_printf("FILE_IO: Snapshot saved for Ch no %d \n ",pBuffer->chNum);
            }
        }
        else
        {
                Chains_setChannelState(CHAINS_WRITE_IDLE,pBuffer->chNum);
        }
    }
    else if(state == CHAINS_WRITE_STOP)
    {
        fileWriteClose(pfileIOObj,pBuffer->chNum);
        Chains_setChannelState(CHAINS_WRITE_IDLE,pBuffer->chNum);
        Vps_printf("FILE_IO: File Write stopped and file saved for Ch no %d \n ",pBuffer->chNum);
    }
}

/**
 *******************************************************************************
 *
 * \brief   File IO Init
 *
 *          Init Function to reset the file IO Paramenters  .
 *
 * \param pFileIOPrm    [IN] File IO Params
 *
 *******************************************************************************
*/
Int32 Chains_fileInit(FileIO_CreateParams *pFileIOPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i;

    Chains_fileIOStatus *pfileIOObj = (Chains_fileIOStatus *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(Chains_fileIOStatus),
                        128);

    if(pfileIOObj != NULL )
    {
        pFileIOPrm->fileIOHandle = pfileIOObj;
        memset(&gfileIOStatus,0x00,sizeof(gfileIOStatus));
        for( i = 0; i < FILE_IO_MAX_CH; i++)
        {
            gfileIOStatus[i].read = TRUE;
        }

        status = SYSTEM_LINK_STATUS_SOK;
        gpFileIOObj = pfileIOObj;
    }
    else
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if(pFileIOPrm->readFromCfg == FALSE)
    {
        pfileIOObj->fOpt.startFrameNum = pFileIOPrm->cfgOptions.startFrameNum;
        pfileIOObj->fOpt.stopFrameNum = pFileIOPrm->cfgOptions.stopFrameNum;
        pfileIOObj->fOpt.repeatMode = pFileIOPrm->cfgOptions.repeatMode;
    }
    else
    {
        /* open cfg file and parse data here */
    }
    return status;
}

static Int32 fileReadClose(Chains_fileIOStatus *pfileIOObj,UInt32 chId)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    if(pfileIOObj->chObj[chId].fileReadOpen == TRUE)
    {
       if(pfileIOObj->chObj[chId].fpReadDataStream >= 0)
       {
           status = File_close(pfileIOObj->chObj[chId].fpReadDataStream);

            if(status == SYSTEM_LINK_STATUS_SOK)
            {
                pfileIOObj->chObj[chId].fileReadOpen = FALSE;
            }
       }
    }
    return status;
}

static Int32 fileWriteClose(Chains_fileIOStatus *pfileIOObj,UInt32 chId)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    if(pfileIOObj->chObj[chId].fileWriteOpen == TRUE)
    {
        if(pfileIOObj->chObj[chId].fpWriteDataStream > 0)
        {
            status = File_close(pfileIOObj->chObj[chId].fpWriteDataStream);
            if(status == SYSTEM_LINK_STATUS_SOK)
            {
                pfileIOObj->chObj[chId].fileWriteOpen = FALSE;
            }
       }
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief   File Open functions to open the desired file
 *
 *
 * \param pFileIOPrm    [IN] File IO Params
 *
 * \param chId          [IN] Channel Id
 *
 * \param fileOpenMode  [IN] File Mode which is to be opened
 *
 *******************************************************************************
*/
Int32 Chains_fileOpen(FileIO_CreateParams *pFileIOPrm,UInt32 chId,
                        Chains_fileMode fileOpenMode )
{
    UInt32 fileSize,numFrameToRead = 0;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char fileName[128U];
    Chains_fileIOStatus *pfileIOObj = pFileIOPrm->fileIOHandle;

    if(fileOpenMode  == CHAINS_FILEMODE_READ )
    {
        /* Verify if the file names are valid */
        UTILS_assert(pFileIOPrm->channelParams[chId].nameDataFile[0]  != (char)'\0');

        /* Open the file, fd is assigned to fpReadDataStream of channel id */
        pfileIOObj->chObj[chId].fpReadDataStream =
                File_open((Char *)pFileIOPrm->channelParams[chId].nameDataFile, "r");
        if(pfileIOObj->chObj[chId].fpReadDataStream == -1)
        {
            Vps_printf("FILE_IO: Verify if desired file is present in sd card \n");
            UTILS_assert(pfileIOObj->chObj[chId].fpReadDataStream != -1);
        }
        fileSize = File_size(pfileIOObj->chObj[chId].fpReadDataStream);

        pfileIOObj->numReadCh = pfileIOObj->numReadCh + 1;

        pfileIOObj->chObj[chId].numFrames = (fileSize/
                                pFileIOPrm->channelParams[chId].frameSize);
        pfileIOObj->chObj[chId].frameSize =
                                pFileIOPrm->channelParams[chId].frameSize;
        if(pfileIOObj->chObj[chId].numFrames)
        {
            numFrameToRead = (pfileIOObj->fOpt.stopFrameNum - pfileIOObj->fOpt.startFrameNum);
            if((numFrameToRead < pfileIOObj->chObj[chId].numFrames) && (numFrameToRead != 0))
            {
                pfileIOObj->chObj[chId].numFrames = pfileIOObj->fOpt.stopFrameNum;
            }
            if(pfileIOObj->fOpt.startFrameNum > 0)
            {
                pfileIOObj->chObj[chId].curRdFrameId = pfileIOObj->fOpt.startFrameNum;
            }
        }
    }
    else if(fileOpenMode  == CHAINS_FILEMODE_WRITE_BIN)
    {
        /* To write get the file name and create a file  */
        status = getFileName(fileName,chId);
        if(status == SYSTEM_LINK_STATUS_SOK)
        {
            pfileIOObj->chObj[chId].fpWriteDataStream = File_open(fileName, "wb");
            if(pfileIOObj->chObj[chId].fpWriteDataStream > 0)
            {
                pfileIOObj->numWriteCh = pfileIOObj->numWriteCh + 1;
                status = SYSTEM_LINK_STATUS_SOK;
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
            }
        }
    }
    return status;
}

Int32 Chains_fileDeInit(FileIO_CreateParams *pFileIOPrm)
{
    Int32 status;

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                                pFileIOPrm->fileIOHandle,
                               sizeof(Chains_fileIOStatus));

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    pFileIOPrm->fileIOHandle = NULL;
    return status;
}

/**
 *******************************************************************************
 *
 * \brief   Get file name
 *          Api to get the file name. In case a file with the given name
 *          is already present the number is incremented and set.
 *
 * \param fileName      [OUT] File name which is not present in SD card
 *
 *******************************************************************************
*/
static Int32 getFileName(char *fileName,UInt32 chId)
{
    static UInt32 count = 0;
    Int32 retVal = SYSTEM_LINK_STATUS_EFAIL;
    if(fileName != NULL)
    {
        snprintf(&fileName[0], 128, "Channel_%d_fileNo%u.bin", chId,count);

        retVal = File_stat(&fileName[0]);
        if(retVal != SYSTEM_LINK_STATUS_EFILE_NO_FILE)
        {
            do{
                count++;
                snprintf(&fileName[0], 128, "Channel_%d_fileNo%u.bin", chId,count);
                retVal = File_stat(&fileName[0]);
            }
            while(retVal == SYSTEM_LINK_STATUS_SOK);
        }
        if(retVal == SYSTEM_LINK_STATUS_EFAIL)
        {
            Vps_printf("FILE_IO: File create failed due to sd card issue Stop and retry \n");
        }
        else
        {
            retVal = SYSTEM_LINK_STATUS_SOK;
        }
    }
    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief   File Close Api to close all the opened filed
 *
 *
 *******************************************************************************
*/
Void Chains_fileClose()
{
    Chains_fileIOStatus *pfileIOObj = gpFileIOObj;
    UInt32 i;

    for ( i = 0 ; i < pfileIOObj->numReadCh; i++)
    {
        fileReadClose(pfileIOObj,i);
    }
    for ( i = 0 ; i < pfileIOObj->numWriteCh; i++)
    {
        fileWriteClose(pfileIOObj,i);
    }

}

static Chains_fileIOState getReadStatus(UInt32 ChId)
{
    Chains_fileIOState retVal;
    if(gfileIOStatus[ChId].read == TRUE)
    {
        retVal = CHAINS_READ_START;
    }
    else
    {
        retVal = CHAINS_READ_STOP;
    }
    return retVal;
}

static Chains_fileIOState getWriteStatus(UInt32 ChId)
{
    Chains_fileIOState retVal;
    if(gfileIOStatus[ChId].writeStart == TRUE)
    {
        if(gfileIOStatus[ChId].writePause == TRUE)
        {
        /* If write is enabled you can pause the write */
            retVal = CHAINS_WRITE_PAUSE;
        }
        else
        {
        /* If write is enabled and not paused continue in write state*/
            retVal = CHAINS_WRITE_START;
        }

        if(gfileIOStatus[ChId].writeStop == TRUE)
        {
        /* If write is enabled you can stop the write
         * This is close the file
         */
            retVal = CHAINS_WRITE_STOP;
        }
    }
    else if(gfileIOStatus[ChId].writeOneFrame == TRUE)
    {
        retVal = CHAINS_WRITE_ONEFRAME;
    }
    else
    {
        if(gfileIOStatus[ChId].writeStop == TRUE)
        {
            retVal = CHAINS_WRITE_STOP;
        }
        else
        {
            retVal = CHAINS_WRITE_IDLE;
        }
    }
    return retVal;
}

/**
 ******************************************************************************
 * \brief This function is called to fill data from file into System Buffer
 * It is used when file read option is enabled for debugging with CCS.
 *
 * \param  pObj [IN] NullSrcLink_Obj
 * \param  channelId [IN] Channel ID for which Fill data is called
 * \param  pBuffer [IN] System Buffer in which data has to be filled
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
*/
static Int32 readData(Chains_fileIOStatus *pfileIOObj,UInt32 channelId,
                                const System_Buffer *pBuffer)
{
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 bufSize=0, i;
    UInt32 frameLength = 0U;
    System_VideoDataFormat dataFormat;
    System_VideoFrameBuffer *videoFrame;
    System_BitstreamBuffer *bitstreamBuf;
    UInt8 *bufPtr = NULL;
    UInt32 bytesRead;
    Int32 startFrameNum = 0U;

    if(pBuffer)
    {
        if(pfileIOObj->fOpt.repeatMode == TRUE)
        {
            /* Rewind if all frames are done */
            if(pfileIOObj->chObj[channelId].curRdFrameId >=
                    pfileIOObj->chObj[channelId].numFrames)
            {
                if(pfileIOObj->fOpt.startFrameNum != 0)
                {
                    startFrameNum = (pfileIOObj->fOpt.startFrameNum *
                                    pfileIOObj->chObj[channelId].frameSize);
                }

                pfileIOObj->chObj[channelId].curRdFrameId = pfileIOObj->fOpt.startFrameNum;
                File_seek(pfileIOObj->chObj[channelId].fpReadDataStream, startFrameNum);
            }
        }
    }

    switch(pBuffer->bufType)
    {
        case SYSTEM_BUFFER_TYPE_BITSTREAM:
            bitstreamBuf = (System_BitstreamBuffer *)pBuffer->payload;

            frameLength = pfileIOObj->chObj[channelId].frameSize;
            /*If buffer is of bitstream type then fillLength contains sizeof
            * valid data inside the buffer.
            */
            UTILS_assert(frameLength < bitstreamBuf->bufSize);
            File_read(pfileIOObj->chObj[channelId].fpReadDataStream,
                bitstreamBuf->bufAddr, frameLength, &(bitstreamBuf->fillLength));
            pfileIOObj->chObj[channelId].curRdFrameId++;
            break;

        case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:

            frameLength = pfileIOObj->chObj[channelId].frameSize;

            /*If end of file is reached return error*/
            if((Int32)TRUE == File_eof(pfileIOObj->chObj[channelId].fpReadDataStream))
            {
                status = SYSTEM_LINK_STATUS_ENO_MORE_BUFFERS;
                Vps_printf("FILE_IO: File End Occured No more buffers to read \n");
            }
            else
            {
                videoFrame = (System_VideoFrameBuffer*)pBuffer->payload;
                dataFormat = (System_VideoDataFormat)
                System_Link_Ch_Info_Get_Flag_Data_Format(videoFrame->chInfo.flags);

                if(dataFormat == SYSTEM_DF_YUV420SP_UV)
                {
                    bufSize =
                    (videoFrame->chInfo.pitch[0] * videoFrame->chInfo.height) +
                    (videoFrame->chInfo.pitch[1] * (videoFrame->chInfo.height/2U));
                    UTILS_assert(frameLength <= bufSize);

                    /*For YUV420sp data filedata needs to be read into 2 buffers
                    *corresponding to Y plane and UV plane.
                    */
                    bufPtr = videoFrame->bufAddr[0];
                    for(i = 0; i < videoFrame->chInfo.height; i++)
                    {
                        File_read(pfileIOObj->chObj[channelId].fpReadDataStream,
                        bufPtr, videoFrame->chInfo.width, &bytesRead);
                        bufPtr += videoFrame->chInfo.pitch[0];
                    }

                    bufPtr = videoFrame->bufAddr[1];
                    for(i = 0; i < (videoFrame->chInfo.height/2U); i++)
                    {

                        File_read(pfileIOObj->chObj[channelId].fpReadDataStream,
                                    bufPtr, videoFrame->chInfo.width, &bytesRead);
                        bufPtr += videoFrame->chInfo.pitch[1];
                    }
                    pfileIOObj->chObj[channelId].curRdFrameId++;
                }
                else if((dataFormat == SYSTEM_DF_YUV422I_YUYV) || (dataFormat == SYSTEM_DF_BAYER_BGGR))
                {
                    bufSize =
                        videoFrame->chInfo.pitch[0] *
                        videoFrame->chInfo.height;

                    UTILS_assert(frameLength <= bufSize);

                    bufPtr = videoFrame->bufAddr[0];
                    for(i = 0; i < videoFrame->chInfo.height; i++)
                    {

                        File_read(pfileIOObj->chObj[channelId].fpReadDataStream,
                                bufPtr, videoFrame->chInfo.width * 2U, &bytesRead);
                        bufPtr += videoFrame->chInfo.pitch[0];
                    }
                    pfileIOObj->chObj[channelId].curRdFrameId++;
                }
                else
                {
                    status = SYSTEM_LINK_STATUS_EFAIL;
                    break; /* Break from switch case */
                }

            }
            break;

        default:
            /*return error for unsupported format*/
            status = SYSTEM_LINK_STATUS_EFAIL;
            break; /* Break from switch case */
    }

    return status;
}

/**
 ******************************************************************************
 * \brief This function is called to fill data from file into System Buffer
 * It is used when file read option is enabled for debugging with CCS.
 *
 * \param  pObj [IN] NullSrcLink_Obj
 * \param  channelId [IN] Channel ID for which Fill data is called
 * \param  pBuffer [IN] System Buffer in which data has to be filled
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
*/
static Int32 writeData(Chains_fileIOStatus *pfileIOObj,UInt32 channelId,
        const System_Buffer *pBuffer)
{
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i;
    System_VideoDataFormat dataFormat;
    System_VideoFrameBuffer *videoFrame;
    System_BitstreamBuffer *bitstreamBuf;
    System_MetaDataBuffer *metaDataBuf;
    UInt8 *bufPtr = NULL;
    UInt32 buffSize = 0;

    switch(pBuffer->bufType)
    {
        case SYSTEM_BUFFER_TYPE_BITSTREAM:
            bitstreamBuf = (System_BitstreamBuffer *)pBuffer->payload;
            /*If buffer is of bitstream type then fillLength contains sizeof
            * valid data inside the buffer.
            */
            buffSize = bitstreamBuf->fillLength;
            File_write(pfileIOObj->chObj[channelId].fpWriteDataStream,
                            bitstreamBuf->bufAddr,
                            buffSize);

            pfileIOObj->chObj[channelId].dataSizeWritten +=  buffSize;
            pfileIOObj->chObj[channelId].curWrFrameId++;

            break;
        case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:

            /* Rewind if all frames are done */

            videoFrame = (System_VideoFrameBuffer*)pBuffer->payload;
            dataFormat = (System_VideoDataFormat)
            System_Link_Ch_Info_Get_Flag_Data_Format(videoFrame->chInfo.flags);

            if(dataFormat == SYSTEM_DF_YUV420SP_UV)
            {
                /*For YUV420sp data filedata needs to be read into 2 buffers
                *corresponding to Y plane and UV plane.
                */
                bufPtr = videoFrame->bufAddr[0];
                for(i = 0; i < videoFrame->chInfo.height; i++)
                {
                    buffSize = videoFrame->chInfo.width;
                    File_write(pfileIOObj->chObj[channelId].fpWriteDataStream,
                                bufPtr,
                                buffSize);
                    pfileIOObj->chObj[channelId].dataSizeWritten +=  buffSize;
                    bufPtr += videoFrame->chInfo.pitch[0];
                }

                bufPtr = videoFrame->bufAddr[1];
                for(i = 0; i < (videoFrame->chInfo.height/2U); i++)
                {
                    buffSize = videoFrame->chInfo.width;
                    File_write(pfileIOObj->chObj[channelId].fpWriteDataStream,
                                bufPtr,
                                buffSize);

                    pfileIOObj->chObj[channelId].dataSizeWritten +=  buffSize;
                    bufPtr += videoFrame->chInfo.pitch[1];
                }
                pfileIOObj->chObj[channelId].curWrFrameId++;
                status = SYSTEM_LINK_STATUS_SOK;
            }
            else if((dataFormat == SYSTEM_DF_YUV422I_YUYV) || (dataFormat == SYSTEM_DF_BAYER_BGGR))
            {

                bufPtr = videoFrame->bufAddr[0];
                for(i = 0; i < videoFrame->chInfo.height; i++)
                {
                    buffSize = videoFrame->chInfo.width * 2U;
                    File_write(pfileIOObj->chObj[channelId].fpWriteDataStream,
                                bufPtr,
                                buffSize);

                    pfileIOObj->chObj[channelId].dataSizeWritten +=  buffSize;
                    bufPtr += videoFrame->chInfo.pitch[0];
                }
                pfileIOObj->chObj[channelId].curWrFrameId++;
                status = SYSTEM_LINK_STATUS_SOK;
            }
            else
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
            }
            break;
        case SYSTEM_BUFFER_TYPE_METADATA:
            metaDataBuf = (System_MetaDataBuffer *)pBuffer->payload;

            /*If buffer is of bitstream type then fillLength contains sizeof
            * valid data inside the buffer.
            */
            bufPtr = metaDataBuf->bufAddr[0];
            buffSize = metaDataBuf->metaFillLength[0];

            File_write(pfileIOObj->chObj[channelId].fpWriteDataStream,
                        bufPtr,
                        buffSize);
            pfileIOObj->chObj[channelId].dataSizeWritten +=  buffSize;
            pfileIOObj->chObj[channelId].curWrFrameId++;
            break;
        default:
            /*return error for unsupported format*/
            status = SYSTEM_LINK_STATUS_EFAIL;
            break; /* Break from switch case */
    }

    if(pfileIOObj->chObj[channelId].dataSizeWritten > MAXFILESIZE)
    {
        Chains_setChannelState(CHAINS_WRITE_STOP,channelId);
    }
    return status;
}
