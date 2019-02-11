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

/**
 *******************************************************************************
 *
 * \ingroup EXAMPLES_API
 * \defgroup EXAMPLES_UTILS FILE IO APIs for Radar Usecase.
 *
 * \brief  APIs for selecting  File IO for Radar Usecase
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file chains_radar.h
 *
 * \brief APIs for File IO .
 *
 * \version 0.0 (Sept 2016) : [CM] First version
 *
 *******************************************************************************
 */

#ifndef CHAINS_RADAR_FILE_IO_H_
#define CHAINS_RADAR_FILE_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

#include <include/link_api/nullSrcLink.h>
#include <include/link_api/nullLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define FILE_IO_MAX_CH (6)


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

typedef enum
{
    CHAINS_FILEMODE_READ,
    /** File Mode Read */
    CHAINS_FILEMODE_WRITE,
    /** File Mode Write */
    CHAINS_FILEMODE_READ_BIN,
    /** File Mode Read Binary */
    CHAINS_FILEMODE_WRITE_BIN
    /** File Mode Write Binary */
} Chains_fileMode;

typedef enum
{
    CHAINS_READ_START = 0,
    /** File read Start */
    CHAINS_READ_STOP = 1,
    /** File read Stop */
    CHAINS_WRITE_START = 2,
    /** File Write Start */
    CHAINS_WRITE_PAUSE = 3,
    /** File Write Pause */
    CHAINS_WRITE_RESUME = 4,
    /** File Write Resume */
    CHAINS_WRITE_IDLE = 5,
    /** File Write Idle - File Write is not enabled */
    CHAINS_WRITE_STOP = 6,
    /** File Write Stop */
    CHAINS_WRITE_ONEFRAME = 7
    /** File write in Snapshot mode */
} Chains_fileIOState;
/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */
typedef struct
{

    char                    nameDataFile[260U];
    /**< File containing the stream data. This is a binary file.
     * 260 is filename size limit set by WIndows 7
     * This file resides on local machine and used only for the purpose of
     * debugging with CCS
     *
     *   ONLY needs to be set when dataRxMode is
     *     NULLSRC_LINK_DATA_RX_MODE_CUSTOM
     */

     UInt32                 frameSize;
     /** Frame size of input file */
} FileIO_ChannelSpecificParams;


typedef struct {
    UInt32    startFrameNum;
    /** Start frame number from which file read should start */
    UInt32    stopFrameNum;
    /** Stop frame number till which file should be read */
    Bool      repeatMode;
    /** If file repeat mode is to be enabled or not */
} FileIO_CfgOptions;


typedef struct
{
    Void*       fileIOHandle;
    /** FileIO Params handle */
    Bool        readFromCfg;
    /** Read the configurations from CFG file */
    FileIO_CfgOptions cfgOptions;
    /** File configuration options */
    FileIO_ChannelSpecificParams channelParams[FILE_IO_MAX_CH];
    /** File Channel specific params options */
}FileIO_CreateParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Int32 Chains_fileInit(FileIO_CreateParams *pFileIOPrm);

Int32 Chains_fileOpen(FileIO_CreateParams *pFileIOPrm,UInt32 chId,
                        Chains_fileMode fileOpenMode );

Void Chains_fileClose();

Void Chains_readFrameCb(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg);
Void Chains_writeFrameCb(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg);

Int32 Chains_fileDeInit(FileIO_CreateParams *pFileIOPrm);

Void Chains_setAllChannelState(Chains_fileIOState state);
Void Chains_setChannelState(Chains_fileIOState state,UInt32 i);

Void Chains_fileIOMenu();

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
