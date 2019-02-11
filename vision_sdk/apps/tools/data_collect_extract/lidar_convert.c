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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>

#include "../../algorithms/commonutils/lidar/include/lidar.h"
#include "../../algorithms/commonutils/geometry/include/pointCloud.h"

// The normal definition uses size_t on a 32-bit architecture, but we are on a 64-bit host
// so we have to redeclare the memory layout of this structure
typedef struct
{
    uint32_t slicesFound;
    uint32_t startTime;
    uint32_t stopTime;
    LidarSlice slices[LIDAR_SLICES_PER_ROTATION];
} LidarMeta32;

// The header used in dump link is not publicly visible but has the same structure:
typedef struct
{
    uint32_t    bufferType;     // System_BufferType
    struct
    {
        uint32_t    numCh;
        struct
        {
            uint32_t    flags;
            uint32_t    pitch[3];
            uint32_t    startX;
            uint32_t    startY;
            uint32_t    width;
            uint32_t    height;
        } chInfo[8];
    } queueInfo;        // Deep copy from System_LinkQueInfo, has to be updated whenever that changes
    uint32_t    size;
    uint32_t    curPlane;
    uint32_t    numPlanes;
} dump_header_t;

// Copied from system_const.h, as we're avoid VSDK dependencies here
#define SYSTEM_BUFFER_TYPE_METADATA 2

void usage(const char *name)
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "    %s <source>\n", name);
    fprintf(stderr, "    %s dc\n", name);
    fprintf(stderr, "\n");
    fprintf(stderr, "  where <source> is the name of the lidar data to convert to MATLAB format.\n");
    fprintf(stderr, "  where dc is a literal string, reads data from stdin:\n");
    fprintf(stderr, "  A PointCloud struct followed by a LidarCloudMeta struct.\n");

    exit(1);
}

int main(int argc, char **argv)
{
    uint8_t             *   input;
    FILE                *   fp;
    PointCloud          *   cloud;
    Point               *   point;
    struct stat             st;
    dump_header_t           header;
    LidarMeta32             meta;
    int                     result;
    uint32_t                slice, laser;

    if (argc != 2)
    {
        usage(argv[0]);
    }

    // Create a point cloud of our expected size
    cloud = PointCloud_init(
        malloc(PointCloud_getRequiredMemorySizeInBytes(LIDAR_POINTS_PER_ROTATION)),
        LIDAR_POINTS_PER_ROTATION
    );

    if (argv[1][0] == 'd' && argv[1][1] == 'c')
    {
        uint32_t dummy;

        // Read PointCloud structure header information
        fread(&cloud->maxPoints, sizeof(uint32_t), 1, stdin);
        fread(&cloud->numPoints, sizeof(uint32_t), 1, stdin);
        fread(&cloud->numValidPoints, sizeof(uint32_t), 1, stdin);
        fread(&cloud->byteOffsetPoints, sizeof(uint32_t), 1, stdin);
        fread(&cloud->byteOffsetTags, sizeof(uint32_t), 1, stdin);
        fread(&cloud->Mref, sizeof(RigidTransform), 1, stdin);

        // The pointer values are dummy reads but the data is stored after the
        // PointCloud structure itself
        fread(&dummy, sizeof(uint32_t), 1, stdin);
        fread(&dummy, sizeof(uint32_t), 1, stdin);

        // Read point cloud data
        fread(cloud->points, sizeof(Point), LIDAR_POINTS_PER_ROTATION, stdin);

        // Read valid data
        fread(cloud->tags, sizeof(uint32_t), LIDAR_POINTS_PER_ROTATION, stdin);

        // The meta structure follows exactly
        fread(&meta, sizeof(LidarMeta32), 1, stdin);
    }
    else
    {
        size_t pcHeaderSize;

        result = stat(argv[1], &st);
        if (0 != result)
        {
            perror("Unable to stat file");
            return 1;
        }

        input = malloc(st.st_size);
        fp = fopen(argv[1], "r");
        (void) fread(input, st.st_size, 1, fp);

        // Now read the header for the first record
        memcpy(&header, input, sizeof(header));
        if (header.bufferType != SYSTEM_BUFFER_TYPE_METADATA)
        {
            fprintf(stderr, "Invalid buffer type discovered, this file isn't what you expectd!\n");
            return 1;
        }

        // Adjust the input pointer to the start of the point cloud
        input += sizeof(header);

        // Now, sizeof(PointCloud) is unfortunately different as we have pointers inside the struct
        // (32 bit on A15, 64 bit on linux), so we compute it ourselves as:
        //  - 5 32-bit fields
        //  - 1 rigid transform (same size on both--12 floats)
        //  - 2 32-bit pointers
        // = 76 bytes, which is 4 byte aligned by not 8 byte aligned
        pcHeaderSize = 76;

        if (header.size != (pcHeaderSize + LIDAR_POINTS_PER_ROTATION*(sizeof(Point) + sizeof(uint32_t))))
        {
            fprintf(stderr,
                    "Header size was %d bytes, but we expected %lu bytes.\n",
                    header.size,
                    pcHeaderSize + LIDAR_POINTS_PER_ROTATION*(sizeof(Point) + sizeof(uint32_t)));
            return 1;
        }

        // We care about the information fields at the start
        memcpy(cloud, input, 5*sizeof(uint32_t));

        // Then we care about the point data itself, which is directly packed and has the same size
        input += pcHeaderSize;
        memcpy(cloud->points, input, LIDAR_POINTS_PER_ROTATION*sizeof(Point));

        // Finally, grab the valid data although we don't really need it yet
        input += LIDAR_POINTS_PER_ROTATION*sizeof(Point);
        memcpy(cloud->tags, input, LIDAR_POINTS_PER_ROTATION*sizeof(uint32_t));

        // Up next, there is another header
        input += LIDAR_POINTS_PER_ROTATION*sizeof(uint32_t);
        memcpy(&header, input, sizeof(header));

        // This header will have describe a structure the same size as the lidar cloud meta
        if (header.size != sizeof(LidarMeta32))
        {
            fprintf(stderr,
                    "Second header size was %d bytes, but we expected %lu bytes.\n",
                    header.size,
                    sizeof(LidarMeta32));
            return 1;
        }

        // Copy over the metadata so we can iterate through it
        input += sizeof(header);
        memcpy(&meta, input, sizeof(LidarMeta32));
    }

    // The output format is the same for both input sources
    for (slice = 0; slice < meta.slicesFound; ++slice)
    {
        for (laser = 0; laser < LIDAR_LASERS; ++laser)
        {
            uint32_t ptIdx = meta.slices[slice].points[laser];
            if (ptIdx != INVALID_POINT_OFFSET)
            {
                point = PointCloud_refPoint(cloud, ptIdx);
                printf("%d,%.6e,%.6e,%.6e\n", laser, point->x, point->y, point->z);
            }
        }
    }

    return 0;
}
