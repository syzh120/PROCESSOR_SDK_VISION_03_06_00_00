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
 * \ingroup  ALGORITHM_LINK_PLUGIN
 * \defgroup ALGORITHM_LINK_SYNTHESIS_API  Synthesis API
 *
 * \brief  This module has the interface for using synthesis algorithm
 *
 *         Synthesis algorithm link -
 *           1. Will perform stitching of multiple views to generate surround
 *              view
 *               - Number of views can be 4 or 6
 *               - Synthesis mode can be simple (Using single view pixels) or
 *                 blending based (Using blend of pixels from two views)
 *           2. Generates certain Photometric statistics which will be used
 *              by Photometric alignment link
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_synthesis.h
 *
 * \brief Algorithm Link API specific to synthesis algorithm
 *
 * \version 0.0 (Oct 2013) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_SYNTHESIS_H_
#define ALGORITHM_LINK_SYNTHESIS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_srvCommon.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Maximum number of views/camera supported by synthesis layer.
 *          This is specifically used for specifying number of LDC input frames.
 *          Caution: Any change in this macro requires change in the algorithm.
 */
#define ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS          (4U)

/**
 *******************************************************************************
 * \brief Link CMD: Command to complete the late creation.
 *
 *   \param AlgorithmLink_IssAewbAeDynamicParams *pPrm [IN] AE Dynamic Parameters.
 *
 *   Supported only on TDA3xx Iss UseCase
 *
 *******************************************************************************
*/
#define ALGORITHM_LINK_SRV_SYNTHESIS_LATE_CREATE        (0x1000)

/**
 *******************************************************************************
 * \brief Link CMD: Command to Generate the Blend Table.
 *
 *   \param AlgorithmLink_IssAewbAeDynamicParams *pPrm [IN] AE Dynamic Parameters.
 *
 *   Supported only on TDA3xx Iss UseCase
 *
 *******************************************************************************
*/
#define TDA3X_SV_3D_GEN_BLENDTABLE                      (0x1001)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for the algorithms supported on DSP.
 *
 *          Method of copying frame
 *
 *******************************************************************************
*/
typedef enum
{
    ALGORITHM_LINK_ALG_SIMPLESYNTHESIS = 0,
    /**< Simple synthesis using pixels from single view */
    ALGORITHM_LINK_ALG_BLENDINGSYNTHESIS = 1,
    /**< Synthesis by blending pixels from two views */
    ALGORITHM_LINK_ALG_SYNTHESIS_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} AlgorithmLink_SynthesisMode;

/**
 *******************************************************************************
 * \brief Enum for the input Q IDs
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    ALGLINK_SYNTHESIS_IPQID_MULTIVIEW = 0,
    /**< QueueId for multiview images */

    ALGLINK_SYNTHESIS_IPQID_GALUT = 1,
    /**< QueueId for GA LUTs */

    ALGLINK_SYNTHESIS_IPQID_PALUT = 2,
    /**< 2D - QueueId for PA statistics */
    /**< 3D - Not used */

    ALGLINK_SYNTHESIS_IPQID_MAXIPQ = 3,
    /**< Maximum number of input queues */

    ALGLINK_SYNTHESIS_IPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

}AlgorithmLink_SynthesisInputQueId;

/**
 *******************************************************************************
 * \brief Enum for the output Q IDs
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    ALGLINK_SYNTHESIS_OPQID_OPFRAME = 0,
    /**< 2D - QueueId for output frame (Stiched frame) */
    /**< 3D - Not used */

    ALGLINK_SYNTHESIS_OPQID_PASTATS = 1,
    /**< QueueId for PA statistics */

    ALGLINK_SYNTHESIS_OPQID_SGXLUT = 2,
    /**< 2D - Not used */
    /**< 3D - QueueId for SGX mesh LUT */

    ALGLINK_SYNTHESIS_OPQID_MAXOPQ = 3,
    /**< Maximum number of output queues */

    ALGLINK_SYNTHESIS_OPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

}AlgorithmLink_SynthesisOutputQueId;

/**
 *******************************************************************************
 * \brief Enum for handling Synthesis LUT
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
typedef enum
{
    ALGLINK_SYNTHESIS_SYNTH_LUT_CALC = 0,
    /**< Calculate LUT based on parameters provided */

    ALGLINK_SYNTHESIS_SYNTH_LUT_INBUILT = 1,
    /**< Use the inbuilt LUT array */

    ALGLINK_SYNTHESIS_SYNTH_LUT_SUPPLIED = 2
    /**< Use LUT from the array supplied in create arguments */

}AlgorithmLink_SynthesisLutMode;

/**
 *******************************************************************************
 * \brief Enum for Output resolution mode
 *
 *******************************************************************************
*/
typedef enum
{
    ALGLINK_SYNTHESIS_OUTPUTRES_1MP = 0x0,
    /**< Output resolution is 1 MP */

    ALGLINK_SYNTHESIS_OUTPUTRES_2MP = 0x1,
    /**< Output resolution is 2 MP */

    ALGLINK_SYNTHESIS_OUTPUTRES_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

}AlgorithmLink_SynthesisOutputRes;

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Synthesis algorithm
 *
 *          This structure is a replica of create time parameters of synthesis
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params. This structure should be first element */
    UInt32                   maxOutputHeight;
    /**< Max height of the output (stitched) frame */
    UInt32                   maxOutputWidth;
    /**< max width of the output (stitched) frame */
    UInt32                   maxInputHeight;
    /**< Max height of the input (captured) frame */
    UInt32                   maxInputWidth;
    /**< Max width of the input (captured) frame */
    UInt32                   numViews;
    /**< number of input views from which output will be synthesized */
    UInt32                   subsampleratio;
    /**< Sub Sample Ratio */
    UInt32                   numOutputFrames;
    /**< Number of output frames (Stitched frames)to be created
     *   for this link per channel */
    UInt32                   carBoxWidth;
    /**< Width of the car box > */
    UInt32                   carBoxHeight;
    /**< Height of the car box > */
    UInt32                   numPhotometricStatisticsTables;
    /**< Number of output Photometric statistics tables */
    UInt32                   numSgxBlendLUTables;
    /**< Number of output Blend LUT tables, this is used only in 3D */
    System_LinkOutQueParams  outQueParams[ALGLINK_SYNTHESIS_OPQID_MAXOPQ];
    /**< Output queue information. Refer AlgorithmLink_SynthesisOutputQueId
     *   for indexing order.
     */
    System_LinkInQueParams   inQueParams[ALGLINK_SYNTHESIS_IPQID_MAXIPQ];
    /**< Input queue information. Refer AlgorithmLink_SynthesisInputQueId
     *   for indexing order.
     */
    AlgorithmLink_SynthesisMode  synthesisMode;
    /**< Simple or Blending based */
    AlgorithmLink_SrvOutputModes  svOutputMode;
    /**< Surround view Alg can support either 2D or 3D ouput modes */
    UInt32                   enableCarOverlayInAlg;
    /**< Set to 1, if DSP need to create the car image, apply only for 2D SRV */
    UInt32                   useSuppliedLUT;
    /**< Set to 1, if Synthesis LUT has been pre-calculated.*/
    UInt8                    *synthLUTPtr;
    /**< Size of allocated LUT */
    UInt32                   synthLUTSize;
    /**< Set to 1, if the LUT calculated on DSP needs to be saved */
    UInt32                   saveCalculatedLUT;

    /* Used to define the size of input buffers. From all cameras */
    UInt32 ldcFrmWidth[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Width on input buffer, for all cameras */
    UInt32 ldcFrmHeight[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Height on input buffer, for all cameras */
    /* Used to define the size of input buffers. From all cameras */
    UInt32 carPosX;
    /**< Car Position Co ordinates */
    UInt32 carPosY;
    /**< Car Position Co ordinates */
    AlgorithmLink_SynthesisOutputRes outputRes;
    /**< Input resolution can be
         ALGLINK_SYNTHESIS_OUTPUTRES_1MP
         OR
         ALGLINK_SYNTHESIS_OUTPUTRES_2MP
     */
    Bool earlyCreate;
    /**< The create function will exit soon after populating the link info
         to be used by the next link the other create sequence will continue
         in the background after getting a message */

    Bool useUserBlendTable3DLDC;
    /**< Flag for using the user provided Synthesis Blend table */
    Bool useStaticGALut;
    /**< Flag to use the static GA-LUT*/
} AlgorithmLink_SynthesisCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for Synthesis algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
    AlgorithmLink_SynthesisMode    synthesisMode;
    /**< Simple or Blending based */
} AlgorithmLink_SynthesisControlParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing parameters to generate the Blend Table
 *
 *          This structure is a replica of create time parameters of synthesis
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 numCameras;
    /**< Blend Length */
    UInt32 SVOutDisplayWidth;
    /**< SV Output Width */
    UInt32 SVOutDisplayHeight;
    /**< SV Output Height */
    UInt32 carBoxX;
    /**< Car Box X */
    UInt32 carBoxY;
    /**< Car Box Y */
    Int8 *blendTableAddr;
    /**< Blend Table Address */
    UInt32 blendTableSize;
    /**< Blend Table Size */
    Void *persistentBaseAddr;
    /**< Persistent Buffer Address */
    Void *scratchBaseAddr;
    /**< Scratch Buffer Address */
    UInt32 persistentMemSize;
    /**< Persistent Buffer Size */
    UInt32 srcatchMemSize;
    /**< Scratch Buffer Size */
    Int32 viewRotationAngleRad;
    /**< Rotation Slope of the view */
    UInt32 chMap[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Synthesis Channel Mapping */
    AlgorithmLink_ldcSlicePrm ldcSlicePrm[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< LDC Slice parameters */
    UInt32 inWidth;
    /**< LDC Input Width */
    UInt32 inHeight;
    /**< LDC Input Height */
    UInt32 subSampleExp;
    /**< LDC sub sample exponent */
    UInt32 pixelPad;
    /**< LDC pixel padding */
    UInt32 ldcLut[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< LDC LUTs */
    UInt32 ldcLutSize[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< LDC LUT Size */
    UInt32 ldcLutPitchBytes;
    /**< LDC LUT Pitch in bytes */
    UInt32 ldcMaxInBlkSize;
    /**< LDC Maximum Input Block Size */
    UInt32 ldcBlkWidth[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< LDC Output Block Width */
    UInt32 ldcBlkHeight[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< LDC Output Block Height */
    UInt32 ldcMaxNumSlices;
    /**< LDC Maximum number of slices */

    /* Corners defined in following order:
     * 0: Front Right
     * 1: Rear Right
     * 2: Rear Left
     * 3: Front Left
     */
    UInt32 carCornerX[4];
    /* X coordinate of car corners */
    UInt32 carCornerY[4];
    /* Y coordinate of car corners */
    UInt32 boxCornerX[4];
    /* X coordinate of box corners */
    UInt32 boxCornerY[4];
    /* Y coordinate of box corners */


    UInt32 quadrantStartX[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Synthesis Quadrant StartX */
    UInt32 quadrantEndX[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Synthesis Quadrant EndX */
    UInt32 quadrantStartY[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Synthesis Quadrant StartY */
    UInt32 quadrantEndY[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    /**< Synthesis Quadrant EndY */

}AlgorithmLink_blenTableGenPrm;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of synthesis algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_Synthesis_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
