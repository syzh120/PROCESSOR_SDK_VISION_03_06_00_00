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
 * \defgroup NETWORK_RX_LINK_API Network Rx Link API
 *
 * network Rx Link is a source link which provides input to the next links
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
 * \file networkRxLink.h
 *
 * \brief Network Rx link API public header file.
 *
 * \version 0.0 (Dec 2013) : [VT] First version
 *
 ******************************************************************************
 */

#ifndef NETWORK_RX_LINK_H_
#define NETWORK_RX_LINK_H_

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
 * \brief Maximum number of network rx link objects
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NETWORK_RX_LINK_OBJ_MAX                       (1U)

/**
 ******************************************************************************
 *
 * \brief Maximum number of output queues that network rx link supports.
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NETWORK_RX_LINK_MAX_OUT_QUE                   (1U)

/******************************************************************************
 *
 * \brief Max channels per output queues supported by network Rx Link
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
#define NETWORK_RX_LINK_MAX_CH                        (6U)

/**
 ******************************************************************************
 *
 * \brief Default number of channels in network rx link
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NETWORK_RX_LINK_NUM_CHANNELS_DEFAULT          (1U)

/**
 ******************************************************************************
 *
 * \brief Maximum number of output buffers per channel in network rx link
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NETWORK_RX_LINK_MAX_OUT_BUFS_PER_CH       (SYSTEM_LINK_MAX_FRAMES_PER_CH)

/**
 ******************************************************************************
 *
 * \brief Default number of output buffers per channel in network rx link
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NETWORK_RX_LINK_NUM_BUFS_PER_CH_DEFAULT       (4U)

/**
 ******************************************************************************
 *
 * \brief Default time interval between buffers sent by network Rx Link
 * 16 is set considering a throughput rate of 60fps.
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NETWORK_RX_LINK_BUF_TIME_INTERVAL_DEFAULT     (16U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Get the Buffer Information of the Network Rx Link
 *
 *******************************************************************************
 */
#define NETWORK_RX_LINK_CMD_GET_BUF_INFO              (0x5001U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Pause Network Rx Link
 *
 *******************************************************************************
 */
#define NETWORK_RX_LINK_CMD_PAUSE                     (0x5002U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Resume Network Rx Link
 *
 *******************************************************************************
 */
#define NETWORK_RX_LINK_CMD_RESUME                    (0x5003U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Update the input files
 *
 *******************************************************************************
 */
#define NETWORK_RX_LINK_CMD_RESTARTFILES               (0x5004U)

/**
 *******************************************************************************
 * \brief  Data receive mode
 *******************************************************************************
*/
typedef enum
{
    NETWORK_RX_LINK_DATA_RX_MODE_TCPIP = 0U,
    /**< Data is received over network,
     *   NetworkRxLink_CreateParams.serverPort needs to be set
     */

    NETWORK_RX_LINK_DATA_RX_MODE_TFDTP = 1U,
    /**< Data is received over network using TFDTP,
     *   NetworkRxLink_CreateParams.serverPort + 100 will be used by TFDTP Rx
     */

    NETWORK_RX_LINK_DATA_RX_MODE_FORCE32BITS = 0x7FFFFFFFU
    /**< To make sure enum is 32 bits */

} NetworkRxLink_DataRxMode;


/******************************************************************************
 *
 * Data structures
 *
*******************************************************************************
*/

/******************************************************************************
 *
 * brief Network Rx link Channel specific create parameters
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

} NetworkRxLink_ChannelSpecificParams;

/******************************************************************************
 *
 * brief Network Rx Output buffers information
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

    System_Buffer buffer[NETWORK_RX_LINK_NUM_BUFS_PER_CH_DEFAULT];
    /**< Buffer Information */

}NetworkRxLink_GetBufInfoParams;


/******************************************************************************
 *
 * brief Network Rx link create parameters
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

    NetworkRxLink_ChannelSpecificParams
                                channelParams[NETWORK_RX_LINK_MAX_CH];
    /**< Channel Specific Parameters contain num buffers etc.*/

    UInt32 networkServerPort;
    /**< Server port ot use when dataRxMode is
     *   NETWORK_RX_LINK_DATA_RX_MODE_TCPIP
     */

    NetworkRxLink_DataRxMode dataRxMode;
    /**< Received data via network */

    Bool pauseLink;
    /**< Pause the Link */

    Int32 retryCount;
    /**< Number of times to retry transmission. */

} NetworkRxLink_CreateParams;

/******************************************************************************
*  Functions Prototypes
*******************************************************************************
*/
static inline void NetworkRxLink_CreateParams_Init
                                            (NetworkRxLink_CreateParams *pPrm);

/******************************************************************************
*
*  Functions
*
*******************************************************************************
*/

/**
*******************************************************************************
 *
 * \brief Network Rx link register and init
 *
 *  - Creates link task
 *  - Registers as a link with the system API
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 ******************************************************************************
 */
Int32 NetworkRxLink_init(void);

/**
*******************************************************************************
 *
 * \brief Network Rx link de-register and de-init
 *
 *  - Deletes link task
 *  - De-registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 ******************************************************************************
 */
Int32 NetworkRxLink_deInit(void);

/**
 ******************************************************************************
 *
 * \brief Network Rx link set default parameters for create time params
 *
 * \param  pPrm  [IN]  NetworkRxLink Create time Params
 *
 ******************************************************************************
 */
static inline void NetworkRxLink_CreateParams_Init
                                            (NetworkRxLink_CreateParams *pPrm)
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
    memset(pPrm, 0, sizeof(NetworkRxLink_CreateParams));

    pPrm->timerPeriodMilliSecs = NETWORK_RX_LINK_BUF_TIME_INTERVAL_DEFAULT;
    pPrm->outQueInfo.numCh = NETWORK_RX_LINK_NUM_CHANNELS_DEFAULT;
    pPrm->dataRxMode = NETWORK_RX_LINK_DATA_RX_MODE_TCPIP;

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
                                        = NETWORK_RX_LINK_NUM_BUFS_PER_CH_DEFAULT;
    }

    return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
