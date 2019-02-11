/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/** ===========================================================================
* @file   edma_utils_autoincrement_int.h
*
* @path   $(STARTERWAREPATH)/drivers/inc
*
* @desc   This header is an internal header for decleration autoincrement internal
*             context
*
* =====================================================================
*
* Use of this software is controlled by the terms and conditions found
* ===========================================================================*/

#ifndef EDMA_UTILS_AUTOINCREMENT_INT_H
#define EDMA_UTILS_AUTOINCREMENT_INT_H

/*#pragma CHECK_MISRA ("none")*/
#include "stdint.h"
/*#pragma RESET_MISRA ("required")*/
#include "edma_utils_autoincrement.h"

/** ========================================================
 *  @name   EDMA_UTILS_autoIncrement_context
 *
 *  @desc   This structure contains the context for autoincrement usecase. It contains
 *               variables which are internally needed by auto increment usecase
 *
 *  @field  numInTransfers
 *             Total number of input transfers
 *
 *  @field numOutTransfers
 *             Total number of output transfers
 *
 *  @field startChannelIdIn
 *               This field stores the channelId from which the allocation of all input channels
 *               is done. Actual channel number in the dmaStateStructure can be retreived by adding
 *               this field of the channelNum in this context
 *
 *  @field startChannelIdOut
 *               This field stores the channelId from which the allocation of all output channels
 *               is done. Actual channel number in the dmaStateStructure can be retreived by adding
 *               this field of the channelNum in this context
 *
 *  @field submitWordIn
 *             Submit word to be written in ESR register for all the input transfers
 *
 *  @field submitWordOut
 *             Submit word to be written in ESR register for all the output transfers
 *
 *  @field waitWordIn
 *             Wait word to be written in ESR register for all the input transfers=
 *
 *  @field waitWordOut
 *             Wait to be written in ESR register for all the output transfers
 *
 *  @field blkHorzIdxIn
 *              Horizontal index of the block during autoincrement for input transfers
 *
 *  @field  blkVertIdxIn
 *              Vertical index of the block during autoincrement for input transfers
 *
 *  @field blkHorzIdxOut
 *              Horizontal index of the block during autoincrement for output transfers
 *
 *  @field blkVertIdxOut
 *              Vertical index of the block during autoincrement for output transfers
 *
 *  @field numBlkHorz
 *              Total number of times we should run in horizontal direction before updating
 *              param set. It is calculated as follows:
 *              numBlkHorz = ( roiWidth[i] - blkWidth[i])/(extBlkIncrementX[i])
 *
 *  @field numBlkVert
 *              Total number of times we should increment in vertical direction
  *              numBlkVert = ( roiHeight[i] - blkHeight[i])/(extBlkIncrementY[i])
 *
 * @field numTotalBlk
 *              Total number of blocks in auto increment. It is calculated as follows:
 *              numTotalBlk = numBlkHorz * numBlkVert

 *
 * @field transferProp
 *              Array storing transfer properties for each transfer
 *  ===============================================================
 */
typedef struct
{
    uint8_t                      numInTransfers;
    uint8_t                      numOutTransfers;
    uint8_t                      startChannelIdIn;
    uint8_t                      startChannelIdOut;
    uint32_t                     submitWordIn;
    uint32_t                     submitWordOut;
    uint32_t                     waitWordIn;
    uint32_t                     waitWordOut;

    int16_t                      blkHorzIdxIn;
    int16_t                      blkVertIdxIn;
    int16_t                      blkHorzIdxOut;
    int16_t                      blkVertIdxOut;

    uint16_t                      numBlkHorz;
    uint16_t                      numBlkVert;
    uint16_t                      numTotalBlk;
    uint16_t                      blkWidthLast[NUM_MAX_TRANSFER_AUTOINCREMENT];
    uint16_t                      blkHeightLast[NUM_MAX_TRANSFER_AUTOINCREMENT];
    EDMA_UTILS_autoIncrement_transferProperties transferProp[NUM_MAX_TRANSFER_AUTOINCREMENT];

} EDMA_UTILS_autoIncrement_context;


#endif /*EDMA_UTILS_AUTOINCREMENT_INT_H*/
/*!
*! Revision History
*! ================
*! 21-Mar-2017   Anshu: Initial Draft
*/



