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
 * \ingroup SAMPLE_LINUX_MODULE_API
 * \defgroup SGXFRMCPY_LINK_API SgxFrmcpy Link API
 *
 * \brief  This module has the interface for using SgxFrmcpy Link
 *
 *         SgxFrmcpy Link is used to feed video frames to SGX for
 *         rendering.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file sgxFrmcpyLink.h
 *
 * \brief SgxFrmcpy Link API
 *
 * \version 0.0 (Jun 2014) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef SGXFRMCPY_LINK_H_
#define SGXFRMCPY_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */
/**
 *******************************************************************************
 *
 * \brief Macro defining SGX Link egl context sharing command.
 *
 *
 *******************************************************************************
 */
#define SGXLINK_CMD_ACQUIRE_EGL_INFO                       (0x8000U)

/* @} */


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

typedef enum {

    SGXFRMCPY_RENDER_TYPE_1x1 = 0,
    /**< Display video rendered full-screen on the display */

    SGXFRMCPY_RENDER_TYPE_2x2 = 1,
    /**< Display video rendered full-screen as 2x2 mosiac on the display */

    SGXFRMCPY_RENDER_TYPE_3D_CUBE = 2,
    /**< Display video rendered as a rotating 3D cube */

    SGXFRMCPY_RENDER_TYPE_2x4 = 3,
    /**< Display video rendered full-screen as 2x4 mosiac on the display */

    SGXFRMCPY_RENDER_TYPE_3x3 = 4,
    /**< Display video rendered full-screen as 3x3 mosiac on the display */

    SGXFRMCPY_RENDER_TYPE_MAX = 5,
    /**< Max value for this enum */

    SGXFRMCPY_RENDER_TYPE_FORCE_32BITS = 0x7FFFFFFF
    /**< value to force enum to be 32-bit */

} SgxFrmcpy_RenderType;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing the SgxFrmcpy link create time parameters
 *
 *          This structure is used to create and configure a SgxFrmcpy link
 *          instance.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 displayWidth;
    /**< Display width */

    UInt32 displayHeight;
    /**< Display height */

    SgxFrmcpy_RenderType renderType;
    /**< type of rendering to do using OpenGL */

    System_BufferType inBufType;
    /**< Input buffer type can be
     *   SYSTEM_BUFFER_TYPE_VIDEO_FRAME
     *   or
     *   SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER
     */

    System_LinkInQueParams inQueParams;
    /**< SgxFrmcpy link input queue information */

    System_LinkOutQueParams outQueParams;
    /**< SgxFrmcpy link Output queue information */

    Bool bEglInfoInCreate;
    /**< Flag to determine whether eglInfo is passed in Create */
    Void *EglInfo;
    /**< if bEglInfoInCreate == TRUE, the eglInfo is passed in this struct */

} SgxFrmcpyLink_CreateParams;

/*******************************************************************************
 *  Functions Prototypes
 *******************************************************************************
 */
static inline Void SgxFrmcpyLink_CreateParams_Init(
                                 SgxFrmcpyLink_CreateParams *prm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief SgxFrmcpy link register and init function
 *
 *          For each sgxFrmcpy instance (VID1, VID2, VID3 or GRPX1)
 *          - Creates link task
 *          - Registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SgxFrmcpyLink_init(void);

/**
 *******************************************************************************
 *
 *   \brief SgxFrmcpy link de-register and de-init function
 *
 *          For each sgxFrmcpy instance (VID1, VID2, VID3 or GRPX1)
 *          - Deletes link task
 *          - De-registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 SgxFrmcpyLink_deInit(void);

/**
 *******************************************************************************
 *
 *   \brief Function to initialize the SgxFrmcpy Link Create Params
 *
 *          Sets default values for SgxFrmcpy link create time parameters
 *          User/App can override these default values later.
 *
 *   \param prm [IN] SgxFrmcpy Link create parameters
 *
 *   \return void
 *
 *******************************************************************************
*/
static inline Void SgxFrmcpyLink_CreateParams_Init(
                                 SgxFrmcpyLink_CreateParams *prm)
{
    memset(prm, 0, sizeof(SgxFrmcpyLink_CreateParams));

    prm->renderType = SGXFRMCPY_RENDER_TYPE_1x1;
    prm->inBufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
