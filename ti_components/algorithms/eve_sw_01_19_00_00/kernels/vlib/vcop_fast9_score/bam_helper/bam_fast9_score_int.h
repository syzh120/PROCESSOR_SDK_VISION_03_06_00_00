/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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


/**
 *  @file       bam_fast9_score_int.h
 *
 *  @brief      This header defines internal structures for fast9 score
 *              into BAM.
 */

#ifndef BAM_FAST9_SCORE_INT_H
#define BAM_FAST9_SCORE_INT_H

#include <stdint.h>
#include <vcop.h>

#include "algframework.h"
#include "bam_fast9_score.h"

#define NUM_IN_BLOCKS 1    /* 8x8 patch around XY */
#define NUM_OUT_BLOCKS 1   /* Fast9 Score is output */

#define NUM_FEATURES 32

/* Using max number of sad and threshold method */
/* Threshold method needs only 8 internal blocks */
/* So, for threshold, the BSCORE and DSCORE will have dummy allocation */

#define NUM_INTERNAL_BLOCKS 8


#define NUM_IND_SAD   17     /* 17 indeces to be looked up by LUT for SAD based score */
#define NUM_IND_THR   25     /* 25 indeces to be looked up by LUT for threshold based score */
#define NUM_BANKS     8     /* 8 memory banks to do 8-way look-up */

typedef struct
{
    uint8_t offset_out[NUM_FEATURES*4*17];
    uint8_t Dscore[NUM_FEATURES*16];
}SCORE_INTERNAL_MEMORY_IBUFHA;

#define IN_IDX   (BAM_FAST9_SCORE_INPUT_PORT_IN)

#define OUT_SCORE_IDX (BAM_FAST9_SCORE_OUTPUT_PORT_SCORE)

#define PARAMS_IDX                  0       /* 0 */
#define PTEMP_BUF_IDX               1       /* 1 */
#define PTEMP_IDX                   2       /* 2 */
#define SCORE_INTERNAL_IBUFHA_IDX   3       /* 3 */
#define BSCORE_IDX                  4       /* 4 */
#define SCORE_B_IDX                 5       /* 5 */
#define SCORE_D_IDX                 6       /* 6 */
#define LUT_IDX                     7       /* 7 */


extern const uint8_t LUT_EXT_IDX_SAD[NUM_IND_SAD*NUM_BANKS];
extern const uint8_t LUT_EXT_IDX_THR[NUM_IND_THR*NUM_BANKS];

typedef struct bam_fast9_score_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Fast9_Score_Args kernelArgs;
    void *pOutBlockBase_OUT_SCORE_IDX;
} BAM_Fast9_Score_Context;

#endif
