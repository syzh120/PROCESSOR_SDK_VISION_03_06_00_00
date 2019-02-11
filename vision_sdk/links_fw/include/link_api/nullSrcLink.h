/*
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
*/

/**
 ******************************************************************************
 *
 * \ingroup FRAMEWORK_MODULE_API
 * \defgroup NULL_SOURCE_LINK_API Null Source Link API
 *
 * Null Src Link is a source link which provides input to the next links
 * It can be used to integrate other links when capture link is not available
 * or not used. It can also be used for supplying pre-defined data to the chain
 * for testing purpose.
 * The Link currently supports - YUV420sp, YUV422i and bitstream data.
 * The link has a single output queue and supports multiple channel.
 * For testing purpose in conjunction with CCS, the link can be used to
 * data from file in a chain.
 *
 * @{
 ******************************************************************************
 */

/**
 ******************************************************************************
 *
 * \file nullSrcLink.h
 *
 * \brief Null source link API public header file.
 *
 * \version 0.0 (Dec 2013) : [VT] First version
 *
 ******************************************************************************
 */

#ifndef NULL_SRC_LINK_H_
#define NULL_SRC_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Include's    */

#include <include/link_api/networkCtrl_if.h>
#include <include/link_api/system.h>
#include <include/link_api/system_buffer.h>


/**
 ******************************************************************************
 *
 * \brief Maximum number of null source link objects
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NULL_SRC_LINK_OBJ_MAX                       (1U)

/**
 ******************************************************************************
 *
 * \brief Maximum number of output queues that null source link supports.
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NULL_SRC_LINK_MAX_OUT_QUE                   (1U)

/******************************************************************************
 *
 * \brief Max channels per output queues supported by Null Src Link
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
#define NULL_SRC_LINK_MAX_CH                        (6U)

/**
 ******************************************************************************
 *
 * \brief Default number of channels in null source link
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NULL_SRC_LINK_NUM_CHANNELS_DEFAULT          (1U)

/**
 ******************************************************************************
 *
 * \brief Maximum number of output buffers per channel in null source link
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NULL_SRC_LINK_MAX_OUT_BUFS_PER_CH       (SYSTEM_LINK_MAX_FRAMES_PER_CH)

/**
 ******************************************************************************
 *
 * \brief Default number of output buffers per channel in null source link
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NULL_SRC_LINK_NUM_BUFS_PER_CH_DEFAULT       (4U)

/**
 ******************************************************************************
 *
 * \brief Default time interval between buffers sent by Null Src Link
 * 16 is set considering a throughput rate of 60fps.
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NULL_SRC_LINK_BUF_TIME_INTERVAL_DEFAULT     (16U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Get the Buffer Information of the Null Source Link
 *
 *******************************************************************************
 */
#define NULL_SRC_LINK_CMD_GET_BUF_INFO              (0x5001U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Pause Null Source Link
 *
 *******************************************************************************
 */
#define NULL_SRC_LINK_CMD_PAUSE                     (0x5002U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Resume Null Source Link
 *
 *******************************************************************************
 */
#define NULL_SRC_LINK_CMD_RESUME                    (0x5003U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Update the input files
 *
 *******************************************************************************
 */
#define NULL_SRC_LINK_CMD_RESTARTFILES               (0x5004U)

/**
 *******************************************************************************
 * \brief  Data receive mode
 *******************************************************************************
*/
typedef enum
{
    NULLSRC_LINK_DATA_RX_MODE_FILE = 0U,
    /**< Data is read from a file based on
     *   NullSrcLink_ChannelSpecificParams.NullSrcLink_ApiFileReadMode
     */
    NULLSRC_LINK_DATA_RX_MODE_CUSTOM = 1U,
    /**< Data is Filled in custom app callback,
     *   NullSrcLink_CreateParams.appCb needs to be set
     */

    NULLSRC_LINK_DATA_RX_MODE_FORCE32BITS = 0x7FFFFFFFU
    /**< To make sure enum is 32 bits */

} NullSrcLink_DataRxMode;

/**
 *******************************************************************************
 * \brief Enum for the File read mode
 *
 * This mode will indicate whether Null Src link will read data from a file.
 * And if does then whether its read at create time or run time.
 * By default file read is disabled. Only for the purpose of debugging using CCS
 * should other modes be enabled. File read option will work ONLY with CCS.
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    NULLSRC_LINK_FILEREAD_DISABLE = 0U,
    /**<File read is disabled. Dummy data is circulated. */

    NULLSRC_LINK_FILEREAD_CREATE_TIME = 1U,
    /**< Buffers are filled with data from file in create state.
    * These are then circulated till the link is deleted.
    */

    NULLSRC_LINK_FILEREAD_RUN_TIME = 2U,
    /**< Buffers are filled with data from file in run state.
    * Everytime New Data has to be processed data is read from file and buffer
    * is filled.
    */

    NULLSRC_LINK_FILEREAD_FORCE32BITS = 0x7FFFFFFFU
    /**< To make sure enum is 32 bits */

}NullSrcLink_ApiFileReadMode;

/******************************************************************************
 *
 * Data structures
 *
*******************************************************************************
*/

/******************************************************************************
 *
 * brief Null source link Channel specific create parameters
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt32                   numBuffers;
    /**< Number of buffers per channel to be allocated for the source link.
    * This can be set based on the throughput rate the chain requires.
    */

    NullSrcLink_ApiFileReadMode fileReadMode;
    /**< This mode will take values from NullSrcLink_ApiFileReadMode
     *
     *   ONLY needs to be set when dataRxMode is
     *     NULLSRC_LINK_DATA_RX_MODE_FILE
     */

    char                    nameDataFile[260U];
    /**< File containing the stream data. This is a binary file.
     * 260 is filename size limit set by WIndows 7
     * This file resides on local machine and used only for the purpose of
     * debugging with CCS
     *
     *   ONLY needs to be set when dataRxMode is
     *     NULLSRC_LINK_DATA_RX_MODE_FILE
     */

    char                    nameIndexFile[260U];
    /**< File used to index into binary Data file. This is a text file.
     * This file resides on local machine and used in tandem with nameDataFile
     * only for the purpose of debugging with CCS
     * It contains frame sizes in bytes for every frame on every line.
     * e.g. contents of index file for 3 frames of YUV420,image size 200x100
     *
     * 30000
     * 30000
     * 30000
     *
     *
     *   ONLY needs to be set when dataRxMode is
     *     NULLSRC_LINK_DATA_RX_MODE_FILE
     */
} NullSrcLink_ChannelSpecificParams;

/******************************************************************************
 *
 * brief Null source Output buffers information
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt32 chId;
    /**< Channel Id for which buffer info is provided */

    UInt32 numBuf;
    /**< Number of buffers allocated */

    System_Buffer buffer[NULL_SRC_LINK_NUM_BUFS_PER_CH_DEFAULT];
    /**< Buffer Information */

}NullSrcLink_GetBufInfoParams;

/******************************************************************************
 *
 * brief Update the input files parameters
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt32 chId;
    /**< Channel Id for which the files are updated */

    char nameDataFile[128U];
    /**< Name of data file */

    char nameIndexFile[128U];
    /**< Name of Index file */

}NullSrcLink_RestartFileParams;

/******************************************************************************
 *
 * brief Null source link create parameters
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/

typedef struct
{
    System_LinkOutQueParams   outQueParams;
    /**< output queue parameters. contains next links ID */

    System_LinkQueInfo        outQueInfo;
    /**< Output queue information : This contains channel info which further
        * details the buffer format and resolutions
        */

    UInt32                    timerPeriodMilliSecs;
    /**< Time period at which output data has to be generated
    * Note that for all CHannels - Throughput rate is common
    */

    NullSrcLink_ChannelSpecificParams
                                channelParams[NULL_SRC_LINK_MAX_CH];
    /**< Channel Specific Parameters contain file read mode, num buffers etc.*/

    UInt32 networkServerPort;
    /**< Server port ot use when dataRxMode is
     *   NULLSRC_LINK_DATA_RX_MODE_NETWORK
     */

    NullSrcLink_DataRxMode dataRxMode;
    /**< Received data via File or network */

     Void (*appCb)(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg);
    /**< Application call back function which returns the full buffer */

     Void *appCbArg;
    /**< Application call back argument */

    Void (*inEofCb)(UInt32 numFrames);
    /**< Application call back function which returns when the EOF of input file
            reached */

    Bool pauseLink;
    /**< Pause the Link */

} NullSrcLink_CreateParams;

/******************************************************************************
*  Functions Prototypes
*******************************************************************************
*/
static inline void NullSrcLink_CreateParams_Init
                                            (NullSrcLink_CreateParams *pPrm);

/******************************************************************************
*
*  Functions
*
*******************************************************************************
*/

/**
*******************************************************************************
 *
 * \brief Null Source link register and init
 *
 *  - Creates link task
 *  - Registers as a link with the system API
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 ******************************************************************************
 */
Int32 NullSrcLink_init(void);

/**
*******************************************************************************
 *
 * \brief Null Source link de-register and de-init
 *
 *  - Deletes link task
 *  - De-registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 ******************************************************************************
 */
Int32 NullSrcLink_deInit(void);

/**
 ******************************************************************************
 *
 * \brief Null Source link set default parameters for create time params
 *
 * \param  pPrm  [IN]  NullSourceLink Create time Params
 *
 ******************************************************************************
 */
static inline void NullSrcLink_CreateParams_Init
                                            (NullSrcLink_CreateParams *pPrm)
{
    UInt32 chId;
    System_LinkChInfo *pChInfo;

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(NullSrcLink_CreateParams));

    pPrm->timerPeriodMilliSecs = NULL_SRC_LINK_BUF_TIME_INTERVAL_DEFAULT;
    pPrm->outQueInfo.numCh = NULL_SRC_LINK_NUM_CHANNELS_DEFAULT;
    pPrm->dataRxMode = NULLSRC_LINK_DATA_RX_MODE_FILE;

    pPrm->networkServerPort = NETWORK_RX_SERVER_PORT;

    pPrm->pauseLink = FALSE;

    /*
    * For YUV422i parameters are Data format = SYSTEM_DF_YUV422I_YUYV,
    * Scan Format = SYSTEM_SF_PROGRESSIVE,
    * Buffer Type = SYSTEM_BUFFER_TYPE_VIDEO_FRAME
    * Width and Height need to be set.
    * Pitch should be equal to width * 2
    */

    /*
    * For Bitstream parameters are Buf Type = SYSTEM_BUFFER_TYPE_BITSTREAM,
    * BITSTREAM_FORMAT = SYSTEM_BITSTREAM_CODING_TYPE_MJPEG,
    * Width and Height need to be set. Pitch is irrelevant.
    */

    for (chId = 0; chId < pPrm->outQueInfo.numCh; chId++)
    {
        pPrm->channelParams[chId].fileReadMode = NULLSRC_LINK_FILEREAD_DISABLE;

        pChInfo = &pPrm->outQueInfo.chInfo[chId];

        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pChInfo->flags,
                                                    SYSTEM_DF_YUV420SP_UV);
        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pChInfo->flags,
                                                    SYSTEM_SF_PROGRESSIVE);
        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pChInfo->flags,
                                               SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
        pChInfo->width = 800U;
        pChInfo->height = 480U;
        pChInfo->startX = 0U;
        pChInfo->startY = 0U;
        pChInfo->pitch[0U] = SystemUtils_align(pChInfo->width, 32U);
        pChInfo->pitch[1U] = SystemUtils_align(pChInfo->width, 32U);

        pPrm->channelParams[chId].numBuffers
                                        = NULL_SRC_LINK_NUM_BUFS_PER_CH_DEFAULT;
    }

    pPrm->appCb = NULL;
    pPrm->appCbArg = NULL;
    pPrm->inEofCb = NULL;

    return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
