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


#ifndef BUCKET_H
#define BUCKET_H

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <inttypes.h>
#include <cstdlib>

#define BUCKET_MAX_PLANES       (4)

#define BUCKET_BUFF_IDX_TAG   ( (uint16_t)( (('i')<<0) | (('d')<<8) ) )

#define BUCKET_INFO_TAG  ( (uint32_t)( (('b')<<0) | (('c')<<8) | (('k')<<16) | (('t')<<24) ) )

#define BUCKET_MAX_NUM_FILES    (4)

class Bucket
{
public:
    struct Info
    {
        uint32_t tag;
        uint32_t version;
        uint32_t flags;
        uint32_t numIdx;
        uint64_t dataFileSize;
    };

    struct BuffIdx
    {
        uint16_t tag;
        uint16_t version; /*same as Info.version*/
        uint32_t flags;
        uint16_t width;
        uint16_t height;
        uint32_t pitchOrMetaSize[BUCKET_MAX_PLANES]; /*For image data, this is pitch.
                                                       For raw data, this is size in bytes per metadata plane.*/
        uint32_t size; /*total size in bytes of the data in the buffer (sum of all planes)*/
        uint64_t timestamp;
        uint64_t offset;
    };

    enum OpenMode
    {
        OPEN_MODE_READ,
        OPEN_MODE_APPEND,
        OPEN_MODE_CREATE,
        OPEN_MODE_MAX
    };

    enum DataFormat
    {
        DATA_FORMAT_YUV420SP,
        DATA_FORMAT_YUV422I,
        DATA_FORMAT_Y8,
        DATA_FORMAT_RAW8,
        DATA_FORMAT_BITSTREAM,
        DATA_FORMAT_MAX
    };

    struct BufInfo
    {
        DataFormat dataFormat;
        uint16_t width;
        uint16_t height;
        uint64_t timestamp;
        uint16_t numPlanes;
        uint16_t chId;
        uint32_t pitchOrMetaSize[BUCKET_MAX_PLANES];
        void *addr[BUCKET_MAX_PLANES];
        size_t size[BUCKET_MAX_PLANES];
    };

    struct FileBufInfo
    {
        void *addr;
        size_t size;
    };

    struct ConfigFileInfo
    {
        FileBufInfo configFile[BUCKET_MAX_NUM_FILES];
        uint32_t numFiles;
    };

public:
    virtual ~Bucket();
    virtual int bucketOpen(const char *path, ConfigFileInfo *cfgFiles,
                           uint32_t bucketNum, OpenMode mode,
                           uint64_t maxFileSize) = 0;
    virtual int bucketWrite(BufInfo *bufInfo) = 0;
    virtual int bucketClose() = 0;
};


#endif
