/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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
#include <diskBucket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

DiskBucket::DiskBucket()
    : data_fd(-1),
        curWrIdx(0),
        maxIndex(DISK_BUCKET_MAX_INDEX),
        curFileSize(0),
        maxFileSize(1024*1024*1024)
{
}

DiskBucket::~DiskBucket()
{
}

int DiskBucket::bucketOpen(const char *path, ConfigFileInfo *cfgFiles,
                           uint32_t bucketNum, OpenMode mode,
                           uint64_t maxFileSize)
{
    int status = 0;

    #ifdef DISK_BUCKET_DEBUG
    printf(" DiskBucket: Open ... \n");
    #endif

    if(data_fd>=0)
    {
        #ifdef DISK_BUCKET_DEBUG
        printf(" DiskBucket: Open ... Closing Old File !!!\n");
        #endif
        /* bucketClose previous file before going to next file */
        bucketClose();
    }

    DiskBucket::makeFileName(bucketNum, path, data_filename, idx_filename, sizeof(data_filename));

    curWrIdx = 0;
    curFileSize = 0;
    this->maxFileSize = maxFileSize;

    if (0 == status)
    {
        if (Bucket::OPEN_MODE_CREATE == mode)
        {
            data_fd = open(data_filename, O_RDWR | O_CREAT | O_LARGEFILE);

            if(data_fd<0)
            {
                #ifdef DISK_BUCKET_DEBUG
                printf(" DiskBucket: Open ... ERROR (%s open failed) !!!\n", data_filename);
                #endif
                /* file could not be opened */
                status = -1;
            }
            else
            {
                status = fallocate(data_fd, 0, 0, maxFileSize);

                if(status<0)
                {
                    #ifdef DISK_BUCKET_DEBUG
                    printf(" DiskBucket: WARNING: fallocate() failed (%d) !!!\n", status);
                    #endif

                    status = 0;
                    /* ignore this error */
                }

                #ifdef DISK_BUCKET_DEBUG
                printf(" DiskBucket: Open ... SUCCESS (%s opened) !!!\n", data_filename);
                #endif
            }
        }
        else
        {
            /* other modes not supported as of now */
            status = -1;
        }
    }

    #ifdef DISK_BUCKET_DEBUG
    printf(" DiskBucket: Open ... Done !!!\n");
    #endif

    return status;
}


void DiskBucket::fillBufferIdx(BufInfo *bufInfo)
{
    BuffIdx *idx;
    uint32_t totalWriteSize = 0;

    if(curWrIdx < maxIndex)
    {
        /* find total write size */
        for(int i=0; i<bufInfo->numPlanes; i++)
        {
            totalWriteSize += bufInfo->size[i];
        }

        idx =  &indexBuf[curWrIdx];

        idx->tag = BUCKET_BUFF_IDX_TAG;
        idx->version = 1;
        idx->flags = ( ((uint8_t)bufInfo->dataFormat & 0xFF) << 0 )
                    |( ((uint8_t)bufInfo->chId & 0xFF) << 8 )
                    ;
        idx->width = bufInfo->width;
        idx->height = bufInfo->height;
        idx->timestamp = bufInfo->timestamp;
        for(int i=0; i<BUCKET_MAX_PLANES; i++)
        {
            idx->pitchOrMetaSize[i]=bufInfo->pitchOrMetaSize[i];
        }
        idx->offset = curFileSize;
        idx->size   = totalWriteSize;

        curFileSize += totalWriteSize;
        curWrIdx++;
    }
}

int DiskBucket::bucketWrite(BufInfo *bufInfo)
{
    int status = -1;
    int i;
    uint64_t totalWriteSize = 0;
    size_t size;

    if(data_fd>=0)
    {
        /* check if writing this buffer exceeds maxFileSize, if yes
           then do not write and return error
        */

        /* find total write size */
        for(i=0; i<bufInfo->numPlanes; i++)
        {
            totalWriteSize += bufInfo->size[i];
        }

        if(   ((curFileSize+totalWriteSize) < maxFileSize)
             && curWrIdx < maxIndex)
        {
            status = 0;

            /* file is opened and is valid and data can fit within max file size */
            for(i=0; i<bufInfo->numPlanes; i++)
            {
                size = write(data_fd, bufInfo->addr[i], bufInfo->size[i]);
                if (size != bufInfo->size[i])
                {
                    /* error writing file */
                    status = -1;
                }
            }

            if (0 == status)
            {
                /* file write sucessful, update local idx buffer */
                fillBufferIdx(bufInfo);
            }
        }
        if(status<0)
        {
            /* file size limit exceeded or max number of buffer put in file or some error in wirting to file */
            bucketClose();
        }
    }

    return status;
}

void DiskBucket::fillBucketInfo(Info *info)
{
    if (info)
    {
        info->tag = BUCKET_INFO_TAG;
        info->version = 1;
        info->flags = 0;
        info->numIdx = curWrIdx;
        info->dataFileSize = curFileSize;
    }
}

int DiskBucket::writeBuffIdxFile()
{
    int closeStatus;
    size_t expected;
    uint32_t size;
    int idx_fd;
    Info info;

    fillBucketInfo(&info);

    idx_fd = open(idx_filename, O_WRONLY | O_CREAT | O_TRUNC);
    if (idx_fd < 0)
    {
        return -1;
    }

    expected = sizeof(Info);
    size = write(idx_fd, &info, expected);
    if (expected != size)
    {
        close(idx_fd);
        return -1;
    }

    expected = curWrIdx * sizeof(BuffIdx);
    size = write(idx_fd, indexBuf, expected);
    if (expected != size)
    {
        close(idx_fd);
        return -1;
    }

    closeStatus = close(idx_fd);
    if (closeStatus < 0)
    {
        return -1;
    }

    return 0;
}

int DiskBucket::bucketClose()
{
    int status = 0;

    #ifdef DISK_BUCKET_DEBUG
    printf(" DiskBucket: Close ... \n");
    #endif

    /* if file is not previously open'ed then close will return success */
    if(data_fd>=0)
    {
        /* if data file close or index file write or
           info file write gives error then this will return error */
        /* if data file cannot be closed, index  file
           and info file will not be written */
        /* if index file cannot be written, info file will not be written */

        status = close(data_fd);

        if (0 == status)
        {
            #ifdef DISK_BUCKET_DEBUG
            printf(" DiskBucket: Close ... Data file closed (%s) !!!\n", data_filename);
            #endif
            status = writeBuffIdxFile();
            if (0 == status)
            {
                #ifdef DISK_BUCKET_DEBUG
                printf(" DiskBucket: Close ... Index file closed (%s) !!!\n", idx_filename);
                #endif
            }
            else
            {
                #ifdef DISK_BUCKET_DEBUG
                printf(" DiskBucket: Close ... ERROR in Index file close (%s) !!!\n", idx_filename);
                #endif
            }
        }
        else
        {
            #ifdef DISK_BUCKET_DEBUG
            printf(" DiskBucket: Close ... ERROR in Data file close (%s) !!!\n", data_filename);
            #endif
        }
        /* make data_fd as -1 to indicate no valid file is open */
        data_fd = -1;
    }

    #ifdef DISK_BUCKET_DEBUG
    printf(" DiskBucket: Close ... Done !!!\n");
    #endif

    return status;
}

void DiskBucket::makeFileName(uint32_t bucketNum, const char *path, char *dataFileName, char *idxFileName, uint32_t maxFileNameLen)
{
    snprintf(dataFileName, maxFileNameLen, "%s/b%04d_data.bin", path, bucketNum);
    snprintf(idxFileName, maxFileNameLen, "%s/b%04d_idx.bin", path, bucketNum);
    dataFileName[maxFileNameLen-1] = '\0';
    idxFileName[maxFileNameLen-1] = '\0';
}

void DiskBucket::makeCfgFileName(uint32_t bucketNum, uint32_t fileNum, const char *path,
                              char *cfgFileName, uint32_t maxFileNameLen)
{
    snprintf(cfgFileName, maxFileNameLen, "%s/b%04d_cfg_%02d.txt", path, bucketNum, fileNum);
    cfgFileName[maxFileNameLen-1] = '\0';
}

int DiskBucket::writeCfgFile(FileBufInfo *srcFileBuf, const char *dstFile)
{
    int dstFd;
    int status = 0;
    int32_t writtenBytes;
    char *ptr;
    uint32_t writeBytes;

    dstFd = open(dstFile, O_WRONLY | O_CREAT | O_TRUNC);
    if ((srcFileBuf->addr == NULL) || (dstFd < 0))
    {
        status = -1;
        #ifdef DISK_BUCKET_DEBUG
        printf(" DiskBucket: Configuration file open failed !!!\n");
        #endif
    }
    else
    {
        if (srcFileBuf->size >= 0)
        {
            writeBytes = srcFileBuf->size;
            ptr = (char *) srcFileBuf->addr;
            while ((writeBytes > 0) && (status != -1))
            {
                writtenBytes = write(dstFd, ptr, writeBytes);
                if (writtenBytes != -1)
                {
                    writeBytes -= writtenBytes;
                    ptr += writtenBytes;
                }
                else
                {
                    status = -1;
                    #ifdef DISK_BUCKET_DEBUG
                    printf(" DiskBucket: Configuration file write failed !!!\n");
                    #endif
                }
            }
        }
        else
        {
            status = -1;
            #ifdef DISK_BUCKET_DEBUG
            printf(" DiskBucket: Configuration file read failed !!!\n");
            #endif
        }
    }

    if (dstFd >= 0)
    {
        close(dstFd);
    }

    return status;
}

bool DiskBucket::isValidDataFileName(char *inFileName, uint32_t *fileNum)
{
    char fileName[DISK_BUCKET_MAX_FILENAME];
    char ref_file_name[32] = "b0000_data.bin";
    char fileNumStr[8];

    strncpy(fileName, inFileName, DISK_BUCKET_MAX_FILENAME);
    fileName[DISK_BUCKET_MAX_FILENAME-1] = '\0';

    *fileNum = 0;

    if(strlen(fileName) == strlen(ref_file_name) )
    {
        fileNumStr[0] = fileName[1];
        fileNumStr[1] = fileName[2];
        fileNumStr[2] = fileName[3];
        fileNumStr[3] = fileName[4];
        fileNumStr[4] = 0;

        fileName[1] = fileName[2] = fileName[3] = fileName[4] = '0';
        if(strcmp(fileName, ref_file_name)==0)
        {
                *fileNum = atoi(fileNumStr);
                return true;
        }
    }
    return false;
}

bool DiskBucket::isValidIndexFileName(char *inFileName, uint32_t *fileNum)
{
    char fileName[DISK_BUCKET_MAX_FILENAME];
    char ref_file_name[32] = "b0000_idx.bin";
    char fileNumStr[8];

    strncpy(fileName, inFileName, DISK_BUCKET_MAX_FILENAME);

    *fileNum = 0;

    if(strlen(fileName) == strlen(ref_file_name) )
    {
        fileNumStr[0] = fileName[1];
        fileNumStr[1] = fileName[2];
        fileNumStr[2] = fileName[3];
        fileNumStr[3] = fileName[4];
        fileNumStr[4] = 0;

        fileName[1] = fileName[2] = fileName[3] = fileName[4] = '0';
        if(strcmp(fileName, ref_file_name)==0)
        {
                *fileNum = atoi(fileNumStr);
                return true;
        }
    }
    return false;
}
