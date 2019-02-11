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
 * \file vectorToImageLink_dma.h
 *
 * \brief  This file contains DMA APIs for use with vector to image conversion
 *
 * \version 0.0 (Nov 2013) : [KC] First version
 *
 *******************************************************************************
*/

#ifndef _VECTORTOIMAGE_LINK_DMA_H_
#define _VECTORTOIMAGE_LINK_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "vectorToImgLink_priv.h"
#include "src/rtos/utils_common/include/utils_dma.h"

/**
 * \brief Number of DMA channels used
 *
 *        0 - for input[0]
 *        1 - for input[1]
 *        2 - for output
 */
#define NUM_DMA_CH  (3)

/**
 * \brief Number of buffer used for ping/pong
 */
#define NUM_PING_PONG_BUF   (2)

/**
 * \brief number of lines in ping or pong buffer
 */
#define NUM_LINES_IN_BUF    (3)

/**
 * \brief Structure to hold information related to DMA processing for this
 *        algorithm
 */
typedef struct
{
    unsigned int edmaChId[NUM_DMA_CH];
    /**< EDMA channel ID's */

    unsigned int tccId[NUM_DMA_CH];
    /**< TCC ID of the EDMA channels */

    EDMA3_DRV_Handle hEdma;
    /**< Handle to EDMA controller */

    EDMA3_DRV_PaRAMRegs *pParamSet[NUM_DMA_CH];
    /**< Pointer to physical area of PaRAM for this channel */

    UInt8       *pLineBufVectorX[NUM_PING_PONG_BUF];
    /**< Ping/Pong line buffer address for input Vector X */

    UInt8       *pLineBufVectorY[NUM_PING_PONG_BUF];
    /**< Ping/Pong line buffer address for input Vector Y */

    UInt8       *pLineBufOutput[NUM_PING_PONG_BUF];
    /**< Ping/Pong line buffer address for output */

    UInt8       *pColorMapLut;
    /**< Pointer to LUT in internal memory */

    UInt8       *pAllocAddrL2;
    /**< Address of memory allocated from L2 */

    UInt32       allocSizeL2;
    /**< Size of memory to alloc from L2 */

    UInt32      inPitch;
    /**< Pitch of input in bytes */

    UInt32      outPitch;
    /**< Pitch of output in bytes */

    UInt32      inBytesPerLine;
    /**< Valid data size in bytes in a line */

    UInt32      outBytesPerLine;
    /**< Valid data size in bytes in a line */

    UInt32      numLines;
    /**< Number of lines in line buffer */

    UInt32      edmaOpt[NUM_DMA_CH];
    /**< Value used in EDMA CH OPT field */

    UInt32      channelEnableMaskH;
    /**< Mask to enable DMA channels */

    UInt32      channelEnableMaskL;
    /**< Mask to enable DMA channels */


} AlgorithmLink_VectorToImageDmaObj;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
