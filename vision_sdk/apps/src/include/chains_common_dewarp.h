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
 * \file chains_common_dewarp.h
 *
 * \brief This file contains common utility functions used by stereo usecase
 *
 *******************************************************************************
 */

#ifndef _CHAINS_COMMON_DEWARP_H_
#define _CHAINS_COMMON_DEWARP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */
#include <src/include/chains.h>
#include <src/rtos/utils_common/include/utils_temperature.h>
#include "include/link_api/system_common.h"
#include <include/alglink_api/algorithmLink_srvCommon.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define STEREO_DIR_NAME                     "/RSVP"
#define STEREO_FILENAME_LUT                 "SLUT.BIN"
#define STEREO_FILENAME_PARAM               "SPARAMS.BIN"
#define STEREO_FILENAME_CAMPARAM            "SCPARAMS.BIN"
#define RSVP_DIR_NAME                       "/RSVP"
#define RSVP_FILENAME_LUT                   "RSVP_LUT.BIN"
#define STEREO_PARAM_SIZE                   (256U)
#define STEREO_CAMPARAM_SIZE                (256U)

#define DEWARP_MEDIA_SIZE_HEADER            (256U)
#define DEWARP_MEDIA_SIZE_MAXIDX            (10U * 1024U)
#define DEWARP_MEDIA_SIZE_METADATA          (128U)
#define DEWARP_FILEWRITE_CHUNKSIZE          (96U * 1024U)   /* Bytes */
#define DEWARP_FILEREAD_CHUNKSIZE           (100U * 1024U)  /* Bytes */
#define DEWARP_SRCATCH_BUF_SIZE             (1U * MB)

/*******************************************************************************
 *  Structures
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 *  \brief  ChainsCommon_DeWarp_mediaObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct
{
    Int32  fp;
    UInt32 filePtr;
    UInt32 *idxBuf;
    UInt32 idxBufPtr;
    UInt32 stereoBufSize[4];

} ChainsCommon_DeWarp_mediaObj;

/**
 *******************************************************************************
 *
 *  \brief  DEWARP_MEDIA_FILE
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef enum
{
    DEWARP_MEDIA_FILE_LUT,
    RSVP_MEDIA_FILE_LUT
} DEWARP_MEDIA_FILE;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
Int32 ChainsCommon_DeWarp_mediaInit(
            ChainsCommon_DeWarp_mediaObj *pMediaObj,
            UInt32 *pLutFilePresent,
            UInt32 *pNumViewPoints,
            DEWARP_MEDIA_FILE fileType);
Int32 ChainsCommon_DeWarp_mediaDeinit(
            ChainsCommon_DeWarp_mediaObj *pMediaObj);
Int32 ChainsCommon_DeWarp_fileRead(
            Int32 fileHndl,
            UInt8 *addr,
            UInt32 readSize,
            UInt32 *actualReadSize);
Int32 ChainsCommon_DeWarp_fileWrite(
            Int32 fileHndl,
            UInt8 *addr,
            UInt32 size);
Int32 ChainsCommon_DeWarp_mediaReadBlock(
            ChainsCommon_DeWarp_mediaObj *pMediaObj,
            AlgorithmLink_SrvCommonViewPointParams *pViewPointParams,
            UInt32 viewPointIdx,
            UInt32 chunkSize,
            DEWARP_MEDIA_FILE fileType);

Ptr  ChainsCommon_DeWarp_memAlloc(UInt32 size, UInt32 align);
Void ChainsCommon_DeWarp_memFree(Ptr addr, UInt32 size);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */


/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */
