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
 * \defgroup ALGORITHM_LINK_SWCRC_API Algorithm Plugin: SWCRC API
 *
 * \brief  This module has the interface for using software CRC algorithm
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_swCrc.h
 *
 * \brief Algorithm Link API specific to software CRC algorithm
 *
 * \version 0.0 (Mar 2016) : [BL] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHMLINK_SWCRC_H_
#define ALGORITHMLINK_SWCRC_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */
/**
 * The type of the SW CRC values.
 *
 * This type must be big enough to contain at least 64 bits.
 *****************************************************************************/
typedef uint_fast64_t swCrc_t;

/**
 *******************************************************************************
 *
 *   \brief Structure to hold the CRC Signature object
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32   swCrcVal_L;
    /**< CRC signature - lower 32 bit value */
    UInt32   swCrcVal_H;
    /**< CRC signature - upper 32 bit value */
} AlgorithmLink_SwCrcSig_Obj;

/*******************************************************************************
 *  \brief SWCRC Algorithm Callback function to get the CRC signature
 *
 *         Use this function to add the logic for Frame freeze decision making.
 *         CRC Alg only return the CRC signature for each frame.
 *         The implementation in SDK example detect "frame freeze" scenario
 *         if the CRC signature of 5 consecutive frames are the same.
 *         Also sends the frame freeze detect notification to GRPX link Once
 *         it detect the frame Freeze
 *
 *******************************************************************************
 */
typedef Void (*AlgorithmLink_SwCrcSigCallback) (
                             AlgorithmLink_SwCrcSig_Obj *swCrcSig,
                             Void *appData);

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Sw CRC algorithm
 *
 *          This structure contains the create time parameters of SW CRC
 *          algorithm.
 *          Please note: roiWidth should be a multiple of 8, this is required
 *          because SW CRC can hold only 8 bytes at a time.
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params */
    UInt32                    startX;
    /**< X-Coordinate position of the frame */
    UInt32                    startY;
    /**< Y-Coordinate position of the frame  */
    UInt32                    roiHeight;
    /**< Height of the frame on which CRC to be performed */
    UInt32                    roiWidth;
    /**< Width of the frame on which CRC to be performed,
         Should be a multiple of 8 */
    Void                      *appData;
    /**< Private Application data */
    System_LinkInQueParams    inQueParams;
    /**< Input queue information */
    System_LinkMemAllocInfo   memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */
} AlgorithmLink_SwCrcCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for SW CRC algorithm
 *
 *          This structure is a replica of control parameters of SW CRC
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_swCrcControlParams;

/*******************************************************************************
 *  Function Prototypes
 *******************************************************************************
 */
static inline void AlgorithmLink_SwCrc_Init (AlgorithmLink_SwCrcCreateParams *pPrm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_SwCrc_Init (AlgorithmLink_SwCrcCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AlgorithmLink_SwCrcCreateParams));

    pPrm->baseClassCreate.size  = (UInt32)
                                        sizeof(AlgorithmLink_SwCrcCreateParams);
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_SW_CRC;

    pPrm->startX    = 0U;
    pPrm->startY    = 0U;
    pPrm->roiHeight = 800U;
    pPrm->roiWidth  = 480U;
    pPrm->appData   = NULL;
    pPrm->inQueParams.prevLinkId    = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of CRC algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_SwCrc_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
