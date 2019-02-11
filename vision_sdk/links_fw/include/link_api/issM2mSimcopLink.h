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
 *******************************************************************************
 *
 *   \ingroup FRAMEWORK_MODULE_API
 *   \defgroup ISSM2MSIMCOP_LINK_API ISS M2M SIMCOP (LDC+VTNF) Link API
 *
 *   ISS M2M SIMCOP Link is used for SIMCOP operations available in ISS
 *   This link operates in M2M mode (Input Data read from memory, operation by
 *   SIMCOP (LDC and VTNF) and Output Data written back to memory)
 *
 *   This link can be operated in three primary modes
 *   - LDC only: Lens Distortion correction
 *   - VTNF only: Temporal noise filter
 *   - LDC + VTNF only: Both LDC and VTNF are active
 *
 *   This link can operate on multiple channels.
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file issM2mIspLink.h
 *
 * \brief ISS M2M Isp link API public header file.
 *
 * \version 0.0 (Jun 2014) : [PS] First version
 * \version 0.1 (Aug 2014) : [PS] Addressed review comments given by team
 *
 *******************************************************************************
 */

#ifndef ISSM2MSIMCOP_LINK_H_
#define ISSM2MSIMCOP_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/systemLink_ipu1_0_params.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 * \brief Max Channels of operation
 *******************************************************************************
*/
#define ISSM2MSIMCOP_LINK_MAX_CH     (4U)

/**
 *******************************************************************************
 * \brief Max Channels number of input queues
 *        Input queue 0 is used for the frame data
 *        Input queue 1 is used for LDC Lut
 *******************************************************************************
*/
#define ISSM2MSIMCOP_LINK_MAX_IN_QUE    (2U)

/**
 *******************************************************************************
 * \brief Indicates number of output buffers to be set to default
 *         value by the iss M2m isp link
 *******************************************************************************
*/
#define ISSM2MSIMCOP_LINK_NUM_BUFS_PER_CH_DEFAULT (3U)

/* @} */

/* Control Command's    */

/**
    \ingroup LINK_API_CMD
    \addtogroup ISSM2MSIMCOP_LINK_API_CMD  ISS M2M SIMCOP Link Control Commands

    @{
*/

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To set configuration for LDC, VNTF
 *
 *          Needs be set by user. If not set then default values will be used.
 *          Use IssM2mSimcopLink_ConfigParams_Init() to set default params
 *
 *   \param IssM2mSimcopLink_ConfigParams *pConfig
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG           (0x5001U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To save/dump simcop frame into extra frame
 *                    Dumps the frame allocated at CreateTime
 *                    If extra frame buffer is not allocated at create time
 *                      returns Error
 *
 *      Can be used to save frame only when capture is running
 *
 *   \param None
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSM2MSIMCOP_LINK_CMD_SAVE_FRAME             (0x5002U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Return's pointer to saved frame
 *
 *   \param IssM2mSimcopLink_GetSaveFrameStatus   [OUT]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSM2MSIMCOP_LINK_CMD_GET_SAVE_FRAME_STATUS      (0x5003U)

/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *  \brief  Enumerations for operating modes of ISS M2M Simcop Link
 *******************************************************************************
*/
typedef enum
{
    ISSM2MSIMCOP_LINK_OPMODE_LDC = 0,
    /**< LDC operation only */

    ISSM2MSIMCOP_LINK_OPMODE_VTNF = 1,
    /**< VTNF operation only */

    ISSM2MSIMCOP_LINK_OPMODE_LDC_VTNF = 2,
    /**< Both LDC and VTNF operations are required */

    ISSM2MSIMCOP_LINK_OPMODE_MAXNUM = 3,
    /**< Maximum number of operating modes for this link */

    ISSM2MSIMCOP_LINK_OPMODE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} IssM2mSimcopLink_OperatingMode;


/*******************************************************************************
 *  Data structures
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \brief ISS M2m Simcop link channel parameters
 *
 *        Note, for M2M SIMCOP link output data format, width, height
 *        is same as input data format, width, height
 *
 *        For LDC+VNTF mode  , input MUST be YUV420SP data format
 *        For VNTF ONLY mode , input MUST be YUV420SP data format
 *        For LDC ONLY mode  , input MUST be YUV420SP data format
 *
 *******************************************************************************
 */
typedef struct
{
    IssM2mSimcopLink_OperatingMode     operatingMode;
    /**< Refer IssM2mSimcopLink_OperatingMode for details */

    UInt32                             numBuffersPerCh;
    /**< Number of image buffers per output channel */

    UInt32                             overrideInFrmSize;
    /**< 1, Overrides the input frame size with the given frame size,
            Ignores frame size receive from the previous link
            Used only in LDC alone mode, where LDC outputs bigger
            frame size than input frame
         0, Use the frame size received from previous link */
    UInt32                             inputFrameWidth;
    /**< Input frame width,
         Used only when #overrideInFrmSize set to TRUE,
         Used for setting LDC input frame size */
    UInt32                             inputFrameHeight;
    /**< Input frame height,
         Used only when #overrideInFrmSize set to TRUE,
         Used for setting LDC input frame size */

    UInt32                             useOutputFrameSize;
    /**< 1, Use output frame size paramters #outputFrameWidth and
            #outputFrameHeight
         0, Output frame size is same as input frame size
         Used only when LDC outputs different frame size than input
         Used in LDC alone mode */
    UInt32                             outputFrameWidth;
    /**< Output Frame width */
    UInt32                             outputFrameHeight;
    /**< Output Frame height */

} IssM2mSimcopLink_ChannelParams;

/**
 *******************************************************************************
 *  \brief Information of saved data frame
 *******************************************************************************
 */
typedef struct
{
    UInt32  chId;
    /**< Channel id for which buffer information is requested */

    UInt32 isSaveFrameComplete;
    /**< TRUE: Frame is saved at address mentioned in 'bufAddr'
     *   FALSE: Frame is not yet saved, try after some time
     */

    UInt32 bufAddr;
    /**< Address where frame is saved */

    UInt32 bufSize;
    /**< Size of buffer where frame is saved */

} IssM2mSimcopLink_GetSaveFrameStatus;

/**
 *******************************************************************************
 * \brief ISS M2m Simcop link create time parameters
 *******************************************************************************
 */
typedef struct
{
    System_LinkInQueParams       inQueParams[ISSM2MSIMCOP_LINK_MAX_IN_QUE];
    /**< Input queue information */

    UInt32                       numInQue;
    /**< Flag to enable second input queue for the LDC Lut */

    System_LinkOutQueParams      outQueParams;
    /**< Output queue information */

    IssM2mSimcopLink_ChannelParams  channelParams[ISSM2MSIMCOP_LINK_MAX_CH];
    /**< Parameters for each channel */

    UInt32                  allocBufferForDump;
    /**< [IN] Flag to allocate extra frame buffer for RAW dump
              1, extra frame buffer is allocated
              0, extra frame buffer is not allocated, so RAW frames
                 cannot be dumped */

    System_LinkMemAllocInfo memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */

    UInt32                       ldcRdMaxTagCnt;
    /**< LDC Read Max Tag Count */

} IssM2mSimcopLink_CreateParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void IssM2mSimcopLink_CreateParams_Init(
    IssM2mSimcopLink_CreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Iss M2m Isp Link register and init
 *
 * Creates the tasks for the link. Registers Link within System with
 * unique link ID and callback functions.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_init(void);

/**
 *******************************************************************************
 *
 * \brief Iss M2m Isp Link de-register and de-init
 *
 * Delete the tasks and de-registers itself from the system.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mSimcopLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Set defaults for creation time parameters
 *
 *  Currently defaults are set for 12 bit linear processing with output format of
 *  SYSTEM_DF_YUV420SP_UV.
 *  For any other use case, this function needs to be called
 *  and then change the required parameter accordingly.
 *
 * \param  pPrm [OUT] Create parameters for this link.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void IssM2mSimcopLink_CreateParams_Init(IssM2mSimcopLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    UInt32 chId;

    memset(pPrm, 0, sizeof(IssM2mSimcopLink_CreateParams));

    pPrm->allocBufferForDump = 1U;
    pPrm->numInQue = 1U;

    for(chId = 0; chId < ISSM2MSIMCOP_LINK_MAX_CH; chId++)
    {
        pPrm->channelParams[chId].operatingMode   =
            ISSM2MSIMCOP_LINK_OPMODE_LDC_VTNF;
        pPrm->channelParams[chId].numBuffersPerCh =
            ISSM2MSIMCOP_LINK_NUM_BUFS_PER_CH_DEFAULT;
        pPrm->channelParams[chId].overrideInFrmSize = 0U;
        pPrm->channelParams[chId].useOutputFrameSize = 0U;
        pPrm->channelParams[chId].inputFrameWidth = 0U;
        pPrm->channelParams[chId].inputFrameHeight = 0U;
        pPrm->channelParams[chId].outputFrameWidth = 0U;
        pPrm->channelParams[chId].outputFrameHeight = 0U;
    }

    pPrm->ldcRdMaxTagCnt = 15U;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
