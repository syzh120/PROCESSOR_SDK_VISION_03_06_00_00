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
 * \file icrc_algo.h
 *
 * \brief Interface file for CRC algorithm on IPU1_0
 *
 *        This CRC algorithm runs on CRC HW of TDA3x SOC,
 *        So this is supported only on TDA3x
 *
 * \version 0.0 (May 2015) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef _ICRC_ALGO_H_
#define _ICRC_ALGO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <ti/csl/csl_crc.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include "src/rtos/utils_common/include/utils_dma.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

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
 *   \brief Structure containing the CRC create time parameters
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                startX;
    /**< X-Coordinate position of the frame */
    UInt32                startY;
    /**< Y-Coordinate position of the frame  */
    UInt32                roiHeight;
    /**< ROI height of the frame */
    UInt32                roiWidth;
    /**< ROI width of the frame */
    UInt32                dataFormat;
    /**< ROI width of the frame */

} Alg_CrcCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure for CRC algoirthm object
 *
 *******************************************************************************
*/
typedef struct
{
    Alg_CrcCreateParams   crcPrms;
    UInt32                baseAddr;
    UInt32                watchdogPreloadVal;
    UInt32                blockPreloadVal;
    UInt32                sectCnt;
    UInt32                patternSize;
    crcChannel_t          chNumber;
    crcOperationMode_t    mode;
    crcSignature_t        sectSignVal;
    crcSignatureRegAddr_t psaSignRegAddr;

} Alg_Crc_Obj;

/**
 *******************************************************************************
 *
 *   \brief Structure for CRC & EDMA algoirthm object
 *
 *******************************************************************************
*/
typedef struct
{
    Alg_Crc_Obj crcObj;
    /**< Base CRC object */
    unsigned int edmaChId;
    /**< EDMA CH ID that is used for this EDMA */
    unsigned int tccId;
    /**< EDMA TCC ID that is used for this EDMA */
    EDMA3_DRV_Handle hEdma;
    /**< Handle to EDMA controller associated with this logical DMA channel */
    EDMA3_DRV_PaRAMRegs *pParamSet;
    /**< Pointer to physical area of PaRAM for this channel */

} Alg_CrcDma_Obj;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the CRC control parameters
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                xxx;
    /**< Any parameters which can be used to alter the algorithm behavior */

} Alg_CrcControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Int32 Alg_CrcCreate (Alg_CrcDma_Obj *algHandle,
                     Alg_CrcCreateParams *pCreateParams);

Int32 Alg_CrcProcess (Alg_CrcDma_Obj *algHandle,
                          UInt32 *inPtr[],
                          UInt32  inWidth,
                          UInt32  inHeight,
                          UInt32  inPitch[],
                          UInt32  dataFormat
                         );

Int32 Alg_CrcControl (Alg_CrcDma_Obj *algHandle,
                      Alg_CrcControlParams *pControlParams);

Int32 Alg_CrcStop (Alg_CrcDma_Obj *algHandle);

Int32 Alg_CrcDelete (Alg_CrcDma_Obj *algHandle);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
