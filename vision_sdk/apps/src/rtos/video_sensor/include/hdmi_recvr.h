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
 * \defgroup EXAMPLES_HDMI_RECVR_API APIs for controlling hdmi receiver
 *
 *         hdmi receiver APIs can be used to control hdmi receiver.
 *         Drivers for hdmi receiver can be part of BSP or any other package.
 *
 * @{
 *
 *******************************************************************************
 */
 /**
 *******************************************************************************
 *
 * \file hdmi_recvr.h
 *
 * \brief APIs for controlling hdmi receiver.
 *
 * \version 0.0 (Nov 2013) : [CM] First version *
 *
 *******************************************************************************
 */

#ifndef _HDMI_RECVR_H_
#define _HDMI_RECVR_H_

#ifdef __cplusplus
extern "C" {
#endif

 /*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>

 /*******************************************************************************
 *  Defines
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \brief Base command number
 *
 *******************************************************************************
*/
#define HDMI_RECVR_CMD_BASE     (0x0)
/**
 *******************************************************************************
 *
 *   \brief CMD: To start the hdmi receiver
 *
 *           hdmi receiver will start giving data to
 *           VIP or ISS
 *
 *******************************************************************************
 */
 #define HDMI_RECVR_CMD_START    (HDMI_RECVR_CMD_BASE + 0x1)

/*******************************************************************************
 *
 *   \brief CMD: To stop the hdmi receiver
 *
 *           hdmi receiver will stop giving data to
 *           VIP or ISS
 *
 *
 *******************************************************************************
 */
#define HDMI_RECVR_CMD_STOP     (HDMI_RECVR_CMD_BASE + 0x2)

/*******************************************************************************
 *
 *   \brief CMD: To reset the  hdmi receiver
 *
 *            hdmi receiver is put to reset
 *
 *
 *******************************************************************************
 */
#define HDMI_RECVR_CMD_RESET    (HDMI_RECVR_CMD_BASE + 0x3)

/*******************************************************************************
 *
 *   \brief CMD: Command max
 *
 *           There cannont be any sensor command after this.
 *
 *   \param None
 *
 *******************************************************************************
 */
#define HDMI_RECVR_CMD_MAX      (HDMI_RECVR_CMD_BASE + 0x4)

/*******************************************************************************
 *
 *   \brief HDMI_RECVR_WAIT_FOREVER
 *
 *           Wait for ever time out value.
 *
 *   \param None
 *
 *******************************************************************************
 */
#define HDMI_RECVR_WAIT_FOREVER      (~(0))
 /**
 *******************************************************************************
 *
 *  \brief FVID2 driver handle returned by individual drivers
 *
 *******************************************************************************
*/
typedef Ptr HdmiRecvr_Handle;
 /**
 *******************************************************************************
 *
 *  \brief  Enum for receiver ID for hdmi receivers.
 *
 *  These are set of hdmi receivers currently supported on the EVM
 *
 *******************************************************************************
*/
typedef enum {
    HDMI_RECVR_SII_9127,
    /**< HDMI receiver SiI 9127 */
    HDMI_RECVR_ADV_7611,
    /**< HDMI receiver ADV_7611 */
    HDMI_RECVR_MAX = 0xFFFFu,
    /**<Max */
    HDMI_RECVR_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
}HdmiRecvr_Id;
 /*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */
 /**
 *******************************************************************************
 *
 *  \brief  HDMI Receiver Create params.
 *
 *        This structure is used to set input parameters to create hdmi receiver.
 *        This structure is used as an argument to make certain BSP function
 *        calls like Bsp_boardGetVideoDeviceInstId to get the sensor device id.
 *        Bsp_boardGetVideoDeviceI2cInstId to get the i2c instance id.
 *        Bsp_boardGetVideoDeviceI2cAddr to get the i2c address.
 *
 *******************************************************************************
*/

typedef struct
{
    HdmiRecvr_Id                hdmiRecvrId;
    /**< ID of the hdmi receiver for which create is getting called. */
    UInt32                      vipInstId;
    /**< VIP port to which this hdmi receiver is connected */
    System_Standard             standard;
    /**< camer sensor standard.
     * _xx field indicated by System_Standard which indicates FPS should be
     * ignored while using this structure.
     * OV1063x supports following:
     * SYSTEM_STD_CIF -  352,  288,
     * SYSTEM_STD_720P_xx, 1280, 720},
     * SYSTEM_STD_VGA_xx,  640,  480},
     * SYSTEM_STD_WXGA_xx, 1280, 800},
     */
     System_VideoDataFormat      dataformat;
    /**< RGB or YUV data format. valid values are given below \n
     * OV1063x supports following:
     *   SYSTEM_DF_YUV422I_UYVY, \n
     *   SYSTEM_DF_YUV422I_YUYV,  \n
     *   SYSTEM_DF_YUV422I_YVYU,  \n
     *   SYSTEM_DF_YUV422I_VYUY,  \n
     *
     *   For valid values see System_DataFormat. */
     System_VideoIfWidth         videoIfWidth;
    /**< 8 or 12 or 14 capture interface mode.
     * OV1063x supports following:
     * SYSTEM_VIFW_8BIT
     * SYSTEM_VIFW_10BIT
     *
     *   For valid values see #System_VideoIfWidth. */
     System_VideoIfMode            videoIfMode;
    /**< Video capture mode. */
     Int32                          numChan;
    /**< number of channel required */
    HdmiRecvr_Handle            hdmiRecvrHandle;
    /**< Hdmi receiver handle  */
}HdmiRecvr_CreateParams;

 /**
 *******************************************************************************
 *
 *  \brief  Hdmi receiver Create return parameters.
 *
 *        This structure is used to set output status of hdmi create
 *          create function.
 *
 *******************************************************************************
*/
typedef struct
{
    Int32 retVal;
    /**< Return value of CreateApi */
}HdmiRecvr_CreateStatus;
 /*******************************************************************************
 *  Functions
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \brief Set the default Create Params for HDMI receiver .
 *
 * \param  createParams   [IN] Create parameters for Hdmi receiver
 *
 *******************************************************************************
*/
Void HdmiRecvr_CreateParams_Init(HdmiRecvr_CreateParams *createParams);

/**
 *******************************************************************************
 *
 * \brief Create function to create hdmi receiver.
 *
 *        Creates the hdmi receiver handle using bsp function calls.
 *
 * \param  createParams   [IN] Create parameters for hdmi receiver
 *
 * \param  createStatus   [OUT] Status
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 HdmiRecvr_create(HdmiRecvr_CreateParams *createParams,
                      HdmiRecvr_CreateStatus *createStatus);



/*******************************************************************************
 *
 * \brief Delete function to delete hdmi receiver.
 *
 *        Deletes the hdmi receiver handle using Fvid2_delete function calls.
 *
 * \param  createParams    [IN] Create parameters for hdmi receiver
 *
 * \param  deleteArgs      Not used.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 HdmiRecvr_delete(HdmiRecvr_CreateParams *createParams, Ptr deleteArgs);




/*******************************************************************************
 *
 * \brief Control function to start stop and reset hdmi receiver.
 *
 *        Control the receiver operation like start and stop of the receiver using
 *        Fvid2 calls.
 *        receiver reset is performed using IOCTL call IOCTL_BSP_VID_DEC_RESET
 *
 * \param  handle        [IN] Handle to control hdmi receiver.
 *
 * \param  cmd           [IN] Control command for hdmi receiver.
 *
 * \param  cmdArgs       [IN] Arguments for command if any.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 HdmiRecvr_control(HdmiRecvr_CreateParams *createParams,
                        UInt32 cmd,
                        Ptr    cmdArgs,
                        UInt32 cmdStatusArgs);


#ifdef __cplusplus
}
#endif

#endif /* HDMI_RCVR_H*/
