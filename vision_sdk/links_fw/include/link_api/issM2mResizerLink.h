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
 *   \defgroup ISSRSZ_LINK_API ISS M2M ISP Link API
 *
 *
 *   ISS M2M Isp Link is used for ISP operations available in ISS
 *   This link operates in M2M mode (Input Data read from memory, operation by
 *   ISP and Output Data written back to memory)
 *
 *   This link can be operated in two main modes
 *   - ISSRSZ_LINK_OPMODE_12BITLINEAR: This
 *     mode is typically used for RAW Bayear to YUV format conversion with
 *     relevant image signal processing.
 *   - ISSRSZ_LINK_OPMODE_20BITWDR: This
 *     mode is typically used for Wide Dynamic Range operations.
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

#ifndef ISSRSZ_LINK_H_
#define ISSRSZ_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/systemLink_ipu1_0_params.h>
#include <include/link_api/issIspConfiguration.h>

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
#define ISS_RSZ_LINK_MAX_CH     (4U)

/**
 *******************************************************************************
 *
 * \brief Indicates number of output buffers to be set to default
 *         value by the link
 *******************************************************************************
*/
#define ISS_RSZ_LINK_NUM_BUFS_PER_CH_DEFAULT (3U)

/**
 *******************************************************************************
 * \brief Buffer Alignment requirement for ISP Resizer Output
 *******************************************************************************
*/
#define ISS_RSZ_LINK_RSZ_BUF_ALIGN  (128U)

/* @} */

/* Control Command's    */

/**
    \ingroup LINK_API_CMD
    \addtogroup ISSRSZ_LINK_API_CMD  ISS M2M Resizer Link Control Commands

    @{
*/

/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *  \brief  Enumerations for output queue IDs
 *******************************************************************************
*/
typedef enum
{
    ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A = 0,
    /**< Output queue for image output of re-sizer A */

    ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_B = 1,
    /**< Output queue for image output of re-sizer B */

    ISSRSZ_LINK_OUTPUTQUE_MAXNUM = 2,
    /**< Number of Output queues for this link */

    ISSRSZ_LINK_OUTPUTQUE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} IssRszLink_OutputQueId;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
*/

/**
 *******************************************************************************
 * \brief ISS M2m Isp link output image format
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                           heightRszA;
    /**< Height of the output frame for Re-sizer.
     *   Don't care if  enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] = 0
     */

    UInt32                           widthRszA;
    /**< Width of the output frame for Re-sizer.
     *   Don't care if  enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A] = 0
     */

    UInt32                           heightRszB;
    /**< Height of the output frame for Re-sizer.
     *   Don't care if  enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0
     */

    UInt32                           widthRszB;
    /**< Width of the output frame for Re-sizer.
     *   Don't care if  enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0
     */

    System_VideoDataFormat           dataFormat;
    /**< Output Frame data Format.
     *   Only following output data formats are supported
     *       SYSTEM_DF_YUV422I_YUYV
     *       SYSTEM_DF_YUV420SP_UV,
     */
} IssRszLink_OutputParams;

/**
 *******************************************************************************
 * \brief ISS M2m Isp link output image format
 *
 *******************************************************************************
*/
typedef struct
{
    System_BitsPerPixel                inBpp;
    /**< Input Bits per pixel
     *   - As output by image censor
     *   - In case of 16-bit WDR and 20-bit WDR mode
     *     - This specifies BPP after companding
     */

    UInt32                             numBuffersPerCh;
    /**< Number of image buffers per output channel */

    UInt32                             enableOut[ISSRSZ_LINK_OUTPUTQUE_MAXNUM];
    /**< enableOut[x] = 1, enable the corresponding output
     *   enableOut[x] = 0, disable the corresponding output.
     *   For possible value of x, refer enum IssRszLink_OutputQueId
     */

    UInt32                              enableCrop;
    /**< Enable/Disable input cropping */

    System_CropConfig                   inCropCfg;
    /**< Crop configuration for this channel */

    IssRszLink_OutputParams             outParams;
    /**< Parameters for output queue */
} IssRszLink_ChannelParams;

/**
 *******************************************************************************
 * \brief ISS M2m Isp link create time parameters
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    System_LinkInQueParams inQueParams;
    /**< Input queue information */

    System_LinkOutQueParams outQueParams[ISSRSZ_LINK_OUTPUTQUE_MAXNUM];
    /**< Output queue information */

    IssRszLink_ChannelParams channelParams[ISS_RSZ_LINK_MAX_CH];
    /**< Parameters for each channel */

    System_LinkMemAllocInfo memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */
} IssRszLink_CreateParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

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
Int32 IssRszLink_init(void);

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
Int32 IssRszLink_deInit(void);


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
static inline void IssRszLink_CreateParams_Init(
    IssRszLink_CreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for ISP config params
 *
 *  Currently, it resets config parameters to 0
 *
 * \param  pPrm [OUT] ISP Configuration Parameters.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void IssRszLink_ConfigParams_Init(
    IssIspConfigurationParameters *pPrm);

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
static inline void IssRszLink_CreateParams_Init(
    IssRszLink_CreateParams *pPrm)
{
    UInt32 chId, queId;
    IssRszLink_ChannelParams *pChPrm;

    memset(pPrm, 0, sizeof(IssRszLink_CreateParams));

    pPrm->inQueParams.prevLinkId = SYSTEM_LINK_ID_INVALID;

    for(queId=0; queId<ISSRSZ_LINK_OUTPUTQUE_MAXNUM; queId++)
    {
        pPrm->outQueParams[queId].nextLink = SYSTEM_LINK_ID_INVALID;
    }


    for(chId = 0U; chId < ISS_RSZ_LINK_MAX_CH; chId++)
    {
        pChPrm = &pPrm->channelParams[chId];

        pChPrm->inBpp = SYSTEM_BPP_BITS12;
        pChPrm->numBuffersPerCh = ISS_RSZ_LINK_NUM_BUFS_PER_CH_DEFAULT;
        pChPrm->enableOut[ISSRSZ_LINK_OUTPUTQUE_IMAGE_RSZ_A]  = 1U;
        pChPrm->outParams.heightRszA = 720U;
        pChPrm->outParams.widthRszA  = 1280U;
        pChPrm->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
    }
}

/**
 *******************************************************************************
 *
 * \brief Set defaults for ISP config params
 *
 *  Currently, it resets config parameters to 0
 *
 * \param  pPrm [OUT] ISP Configuration Parameters.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void IssRszLink_ConfigParams_Init(
    IssIspConfigurationParameters *pPrm)
{
    memset(pPrm, 0, sizeof(IssIspConfigurationParameters));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
