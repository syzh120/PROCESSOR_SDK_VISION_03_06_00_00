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

 THIS SOFTWARE IS PROVIDED BY TI AND TIS LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TIS LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
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
 * \defgroup DISP_DIST_SOURCE_LINK_API Display Distributor F/W Source Link API
 *
 * Disp Dist Src Link is a source link which provides input to the next links
 * It can be used to integrate other links while taking input from HLOS
 * applications using a display distribution user/distributor framework.
 *
 * The link has a single output queue and supports a single channel.
 *
 * @{
 ******************************************************************************
 */

/**
 ******************************************************************************
 *
 * \file dispDistSrcLink.h
 *
 * \brief Disp dist source link API public header file.
 *
 * \version 0.0 (Nov 2017) : [VT] First version
 *
 ******************************************************************************
 */

#ifndef DISP_DIST_SRC_LINK_H_
#define DISP_DIST_SRC_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Include's    */

#include <include/link_api/system.h>
#include <include/link_api/system_buffer.h>

/**
 ******************************************************************************
 *
 * \brief Maximum number of disp dist source link objects
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define DISP_DIST_SRC_LINK_OBJ_MAX                       (8U)

/**
 ******************************************************************************
 *
 * \brief Maximum number of output queues that disp dist source link supports.
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define DISP_DIST_SRC_LINK_MAX_OUT_QUE                   (1U)

/******************************************************************************
 *
 * \brief Max channels per output queues supported by disp dist Src Link
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
#define DISP_DIST_SRC_LINK_MAX_CH                        (1U)

/******************************************************************************
 *
 * \brief Length of name string supported by disp dist Src Link
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
#define DISP_DIST_SRC_LINK_VDRM_CONTROLLER_NAME_LEN      (128U)

/**
 *******************************************************************************
 * \brief  DRM object type
 *******************************************************************************
*/
typedef enum
{
    DISP_DIST_SRC_LINK_DRM_OBJECT_TYPE_PLANE = 0U,
    /**< DRM object id is plane
     */

    DISP_DIST_SRC_LINK_DRM_OBJECT_TYPE_CRTC = 1U,
    /**< DRM object id is crtc
     */

    DISP_DIST_SRC_LINK_DRM_OBJECT_TYPE_FORCE32BITS = 0x7FFFFFFFU
    /**< To make sure enum is 32 bits */

} DispDistSrcLink_DrmObjectType;


/******************************************************************************
 *
 * brief Disp dist source link create parameters
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/

typedef struct
{
    System_LinkOutQueParams   outQueParams;
    /**< output queue parameters. contains next links ID */

    UInt8 vDrmControllerName[DISP_DIST_SRC_LINK_VDRM_CONTROLLER_NAME_LEN];
    /**< /dev device node Name for this instance
    */

    UInt32 vDrmControllerObjectId;
    /**< DRM object id for this instance
    */

    DispDistSrcLink_DrmObjectType vDrmControllerObjectType;
    /**< DRM object type for this instance
    */

    UInt32 width;
    /**< Width from this Endpoint to next link
    */

    UInt32 height;
    /**< height from this Endpoint to next link
    */

    System_VideoDataFormat format;
    /**< video data format from this Endpoint to next link
    */

} DispDistSrcLink_CreateParams;

/******************************************************************************
*  Functions Prototypes
*******************************************************************************
*/
static inline void DispDistSrcLink_CreateParams_Init
                                            (DispDistSrcLink_CreateParams *pPrm);

/******************************************************************************
*
*  Functions
*
*******************************************************************************
*/

/**
*******************************************************************************
 *
 * \brief Disp Dist Source link register and init
 *
 *  - Creates link task
 *  - Registers as a link with the system API
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 ******************************************************************************
 */
Int32 DispDistSrcLink_init(void);

/**
*******************************************************************************
 *
 * \brief Disp Dist Source link de-register and de-init
 *
 *  - Deletes link task
 *  - De-registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 ******************************************************************************
 */
Int32 DispDistSrcLink_deInit(void);

/**
 ******************************************************************************
 *
 * \brief Disp Dist Source link set default parameters for create time params
 *
 * \param  pPrm  [IN]  DispDistSourceLink Create time Params
 *
 ******************************************************************************
 */
static inline void DispDistSrcLink_CreateParams_Init
                                            (DispDistSrcLink_CreateParams *pPrm)
{

    memset(pPrm, 0, sizeof(DispDistSrcLink_CreateParams));

}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
