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
#include <diskBucketMgr.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <dirent.h>

#define GB ((uint64_t)1024*1024*1024)

DiskBucketMgr::DiskBucketMgr()
{
    lastFileNum = -1;
    for(int i=0; i<DISK_BUCKET_MGR_MAX_FILE_NUM; i++)
    {
        fileInfo[i].isDataFileValid = false;
        fileInfo[i].isIndexFileValid = false;
    }
    skipFileWrite = true;

    diskBucket = new DiskBucket();
}

DiskBucketMgr::~DiskBucketMgr()
{
    delete diskBucket;
}

int DiskBucketMgr::scanDisk()
{
    int status = -1;
    DIR *dir;
    struct dirent dirEnt, *dirEntResult;
    uint32_t fileNum;
    bool isValid;

    #ifdef DISK_BUCKET_MGR_DEBUG
    printf(" DiskBucketMgr: Opening dir [%s] !!!\n", basePath);
    #endif

    dir = opendir(basePath);
    if(dir!=NULL)
    {
        while(1)
        {
            status = readdir_r(dir, &dirEnt, &dirEntResult);
            if(status < 0 || dirEntResult==NULL)
            {
                break;
            }

            isValid = DiskBucket::isValidDataFileName(dirEnt.d_name, &fileNum);
            if(isValid && fileNum < DISK_BUCKET_MGR_MAX_FILE_NUM)
            {
                fileInfo[fileNum].isDataFileValid = true;

                #ifdef DISK_BUCKET_MGR_DEBUG
                printf(" DiskBucketMgr: File [%s], data file %04d !!! \n", dirEnt.d_name, fileNum);
                #endif

            }
            else
            {
                isValid = DiskBucket::isValidIndexFileName(dirEnt.d_name, &fileNum);
                if(isValid && fileNum < DISK_BUCKET_MGR_MAX_FILE_NUM)
                {
                    fileInfo[fileNum].isIndexFileValid = true;

                    #ifdef DISK_BUCKET_MGR_DEBUG
                    printf(" DiskBucketMgr: File [%s], index file %04d !!! \n", dirEnt.d_name, fileNum);
                    #endif
                }
            }

        }

        closedir(dir);

        lastFileNum = -1;
        for(int i=0; i<DISK_BUCKET_MGR_MAX_FILE_NUM; i++)
        {
            if(fileInfo[i].isIndexFileValid && fileInfo[i].isDataFileValid)
            {
                lastFileNum = i;
            }
        }
    }

    return status;
}

int DiskBucketMgr::removeInvalidFiles()
{
    char dataFileName[DISK_BUCKET_MAX_FILENAME];
    char idxFileName[DISK_BUCKET_MAX_FILENAME];

    for(int i=0; i<DISK_BUCKET_MGR_MAX_FILE_NUM; i++)
    {
        if(
             ( fileInfo[i].isDataFileValid && !fileInfo[i].isIndexFileValid)
           ||
             (!fileInfo[i].isDataFileValid &&  fileInfo[i].isIndexFileValid)
          )
        {
            /* if either index file or data file is not valid remove it */
            DiskBucket::makeFileName(i, basePath, dataFileName, idxFileName, sizeof(dataFileName));
            remove(dataFileName);
            remove(idxFileName);

            #ifdef DISK_BUCKET_MGR_DEBUG
            printf(" DiskBucketMgr: Removed invalid file %04d !!! \n", i);
            #endif

            fileInfo[i].isDataFileValid = false;
            fileInfo[i].isIndexFileValid = false;
        }
    }
    return 0;
}

int32_t DiskBucketMgr::getNextWrFileNum()
{
    uint32_t idx, i;
    int32_t nextWrFileNum = lastFileNum;

    idx = (lastFileNum+1)%DISK_BUCKET_MGR_MAX_FILE_NUM;
    for(i = 0; i<DISK_BUCKET_MGR_MAX_FILE_NUM; i++)
    {
        if(!fileInfo[idx].isDataFileValid && !fileInfo[idx].isIndexFileValid)
        {
            nextWrFileNum = lastFileNum = idx;
            break;
        }
        idx = (idx+1)%DISK_BUCKET_MGR_MAX_FILE_NUM;
    }
    if(i>=DISK_BUCKET_MGR_MAX_FILE_NUM)
    {
        nextWrFileNum = -1;
    }
    return nextWrFileNum;
}

int DiskBucketMgr::getDiskInfo(DiskInfo *info)
{
    int status;
    struct statvfs diskStat;

    status = statvfs(basePath, &diskStat);
    if(status<0)
    {
        info->totalSize = 0;
        info->freeSize = 0;
        info->blockSize = 1024; /* default to avoid divide by zero */
    }
    else
    {
        info->totalSize = (uint64_t)diskStat.f_bsize*diskStat.f_blocks;
        info->freeSize = (uint64_t)diskStat.f_bsize*diskStat.f_bfree;
        info->blockSize = diskStat.f_bsize;
    }

    #ifdef DISK_BUCKET_MGR_DEBUG
    printf(" DiskBucketMgr: Disk @ [%s], total size = %5.1f GB, free size = %5.1f GB, block size = %d B  !!! \n", basePath, (float)info->totalSize/GB, (float)info->freeSize/GB, info->blockSize);
    #endif

    return status;
}

uint64_t DiskBucketMgr::getMaxFileSize()
{
    DiskInfo diskInfo;
    uint64_t sizeMargin, fileSize;

    getDiskInfo(&diskInfo);

    sizeMargin = 512*1024*1024; /* minimum free space required to write a new file */

    if(diskInfo.freeSize < sizeMargin)
    {
         fileSize = 0;
    }
    else
    {
        if(maxFileSize > (diskInfo.freeSize-sizeMargin))
        {
            fileSize = diskInfo.freeSize-sizeMargin;
        }
        else
        {
            fileSize = maxFileSize;
        }
    }
    return fileSize;
}

int DiskBucketMgr::openNextFile()
{
    uint64_t curMaxFileSize;
    int32_t fileNum;
    int status = 0;

    curMaxFileSize = getMaxFileSize();
    if(curMaxFileSize==0)
    {
        #ifdef DISK_BUCKET_MGR_DEBUG
        printf(" DiskBucketMgr: Disk full !!! \n");
        #endif

        /* disk full */
        status = -1;
    }
    else
    {
        fileNum = getNextWrFileNum();

        if(fileNum<0)
        {
            #ifdef DISK_BUCKET_MGR_DEBUG
            printf(" DiskBucketMgr: Filename not available !!! \n");
            #endif

            /* exhausted file number skip write's */
            status = -1;
        }
        else
        {
            #ifdef DISK_BUCKET_MGR_DEBUG
            printf(" DiskBucketMgr: Opening file %04d, max size = %6.1f MB !!! \n", fileNum, (float)curMaxFileSize/(1024*1024));
            #endif

            status = diskBucket->bucketOpen(
                                            basePath,
                                            NULL,
                                            fileNum,
                                            openMode,
                                            curMaxFileSize
                                            );
        }
    }

    if(status<0)
    {
        #ifdef DISK_BUCKET_MGR_DEBUG
        printf(" DiskBucketMgr: Next file open failed, file write disabled !!! \n");
        #endif

        /* some error in opening file so skip subsequent write's */
        skipFileWrite = true;
    }

    return status;
}

int DiskBucketMgr::bucketOpen(const char *path, ConfigFileInfo *cfgFiles,
                              uint32_t bucketNum, OpenMode mode,
                              uint64_t maxFileSize)
{
    int status = 0;
    char cfgFileName[DISK_BUCKET_MAX_FILENAME];
    unsigned int i;
    FileBufInfo *pFileBuf;

    #ifdef DISK_BUCKET_MGR_DEBUG
    printf(" DiskBucketMgr: Open ... \n");
    #endif

    strncpy(basePath, path, sizeof(basePath));
    basePath[sizeof(basePath)-1] = '\0';

    openMode = mode;
    this->maxFileSize = maxFileSize;
    skipFileWrite = false;

    status = scanDisk();
    if(0==status)
    {
        status = removeInvalidFiles();
        if(0==status)
        {
            status = openNextFile();
        }
    }
    if(status<0)
    {
        #ifdef DISK_BUCKET_MGR_DEBUG
        printf(" DiskBucketMgr: Open failed, file write disabled !!! \n");
        #endif

        skipFileWrite = true;
    }
    else
    {
        #ifdef DISK_BUCKET_MGR_DEBUG
        printf(" DiskBucketMgr: Copy Configuration %d files \n", cfgFiles->numFiles);
        #endif
        for (i = 0; i < cfgFiles->numFiles; i++)
        {
            pFileBuf = &cfgFiles->configFile[i];
            DiskBucket::makeCfgFileName(lastFileNum, i, basePath, cfgFileName, sizeof(cfgFileName));
            status = DiskBucket::writeCfgFile(pFileBuf, cfgFileName);
        }
   }

    #ifdef DISK_BUCKET_MGR_DEBUG
    printf(" DiskBucketMgr: Open ... Done !!!\n");
    #endif

    return status;
}




int DiskBucketMgr::bucketWrite(BufInfo *bufInfo)
{
    int status = -1;

    if(skipFileWrite==false)
    {
        status = diskBucket->bucketWrite(bufInfo);
        if(status<0)
        {
            status = openNextFile();
            if (0 == status)
            {
                /* switched to new bucket */
                status = diskBucket->bucketWrite(bufInfo);
                if(status<0)
                {
                    #ifdef DISK_BUCKET_MGR_DEBUG
                    printf(" DiskBucketMgr: File writed failed, file write disabled !!! \n");
                    #endif

                    skipFileWrite = true;
                }
            }
        }
    }

    return status;
}

int DiskBucketMgr::bucketClose()
{
    int status = 0;

    #ifdef DISK_BUCKET_MGR_DEBUG
    printf(" DiskBucketMgr: Close ... \n");
    #endif

    diskBucket->bucketClose();

    #ifdef DISK_BUCKET_MGR_DEBUG
    printf(" DiskBucketMgr: Close ... Done !!!\n");
    #endif

    return status;
}


