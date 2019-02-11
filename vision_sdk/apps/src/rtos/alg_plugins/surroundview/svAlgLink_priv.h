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
 * \ingroup ALGORITHM_LINK_API
 * \defgroup ALGORITHM_LINK_IMPL Algorithm Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file svAlgLink_priv.h Geometric Alignment Algorithm Link private
 *                            API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 *           Definitions common to all algorithm stages of surround view
 *
 * \version 0.0 (Oct 2013) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef _SVALG_LINK_PRIV_H_
#define _SVALG_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#ifndef PC_VERSION
	#include <include/link_api/system.h>
	#include <include/link_api/algorithmLink_algPluginSupport.h>
    #include "./include/svCommonDefs.h"
#else
	#include "../include/svCommonDefs.h"
#endif



/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief SV Algorithm Input Width for 2 MP
 *
 *******************************************************************************
 */
#define SV_ALGLINK_INPUT_FRAME_WIDTH_2MP     (1920)

/**
 *******************************************************************************
 *
 *   \brief SV Algorithm Input Width for 2 MP
 *
 *******************************************************************************
 */
#define SV_ALGLINK_OUTPUT_FRAME_WIDTH_2MP     (1920)

/**
 *******************************************************************************
 *
 *   \brief SV Algorithm Input Width
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_INPUT_FRAME_WIDTH (1280)

/**
 *******************************************************************************
 *
 *   \brief SV Algorithm Input Height
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_INPUT_FRAME_HEIGHT (1088)

/**
 *******************************************************************************
 *
 *   \brief SV Algorithm Output Height
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_OUTPUT_FRAME_WIDTH (1280)

/**
 *******************************************************************************
 *
 *   \brief SV Algorithm Output Height
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_OUTPUT_FRAME_HEIGHT (1088)

/**
 *******************************************************************************
 *
 *   \brief SV Algorithm pixel point width for 3D
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_3D_PIXEL_POINTS_WIDTH (220*2)

/**
 *******************************************************************************
 *
 *   \brief SV Algorithm pixel point height for 3D
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_3D_PIXEL_POINTS_HEIGHT (270*2)

/**
 *******************************************************************************
 *
 *   \brief 2MP SV Algorithm pixel point width for 3D
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_3D_PIXEL_POINTS_WIDTH_2MP (240*2)

/**
 *******************************************************************************
 *
 *   \brief 2MP SV Algorithm pixel point height for 3D
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_3D_PIXEL_POINTS_HEIGHT_2MP (270*2)

/**
 *******************************************************************************
 *
 *   \brief SV Algorithm Maximum number of views
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_MAX_NUM_VIEWS (4)

/**
 *******************************************************************************
 *
 *   \brief Size of Geometric Alignment LUT
 *
 *          Buffer allocation done considering following factors -
 *              - Output height
 *              - Output width
 *              - Based on the color format (1.25 for 420SP)-U and V use
 *                same table
 *              - 3 tables - Simple synthesis LUT, Blend LUT1, Blend LUT2
 *                TBD - Make 3 when blending / PA Stats is enabled
 *              - Per entry size of GAlignLUT_BitPerEntry
 *              - An additional 256 bytes for any round off etc during
 *                division etc..
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_GALUT_SIZE ((SV_ALGLINK_OUTPUT_FRAME_HEIGHT) * \
                               (SV_ALGLINK_OUTPUT_FRAME_WIDTH) *  \
                               (1.25) *                           \
                               2 *                                \
                               GAlignLUT_BitPerEntry              \
                               + 256)

#define SV_ALGLINK_GALUT_SIZE_2MP ((SV_ALGLINK_OUTPUT_FRAME_HEIGHT) * \
                                   (SV_ALGLINK_OUTPUT_FRAME_WIDTH_2MP) *  \
                                   (1.25) *                           \
                                   2 *                                \
                                   GAlignLUT_BitPerEntry              \
                                   + 256)

//size of PixelsPerCm buffer in bytes
//1 float (4 bytes) for each view
#define SV_ALGLINK_GA_PIXELSPERCM_SIZE (SV_ALGLINK_MAX_NUM_VIEWS)*4

/********************************************************************************
Ultrasonic Extension
********************************************************************************/
//maximum number of ultrasonic sensors supported
#define SV_ALGLINK_INPUT_MAX_ULTRASONICS (16)

//size of ultrasonic overlay image in Bytes
#define SV_ALGLINK_UF_OVERLAYDATA_SIZE ((SV_ALGLINK_OUTPUT_FRAME_HEIGHT)/(SV_UF_OVERLAYDATA_SCALE) * \
        								(SV_ALGLINK_OUTPUT_FRAME_WIDTH)/(SV_UF_OVERLAYDATA_SCALE) * 2)

/**
 *******************************************************************************
 *
 *   \brief Size of Photometric Alignment LUT
 *
 *          Buffer allocation done considering following factors -
 *              - Number of views
 *              - Number of different pixel values (256 for 8-bit pixels)
 *              - Number of color planes - 3 (YUV or RGB)
 *              - An additional 256 bytes for any round off etc during
 *                division etc..
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_PALUT_SIZE ((SV_ALGLINK_MAX_NUM_VIEWS * 256 * 3) + 256)

/**
 *******************************************************************************
 *
 *   \brief Size of Synthesis blend LUT size. This is used only in 3D case.
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_SYNT_BLENDLUT_SIZE (SV_ALGLINK_OUTPUT_FRAME_HEIGHT * \
                                       SV_ALGLINK_OUTPUT_FRAME_WIDTH * 2)

/**
 *******************************************************************************
 *
 *   \brief Threshold size beyond which memory gets allocated in Shared area
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_ALGLINK_SRMEM_THRESHOLD (ALGORITHMLINK_SRMEM_THRESHOLD)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
