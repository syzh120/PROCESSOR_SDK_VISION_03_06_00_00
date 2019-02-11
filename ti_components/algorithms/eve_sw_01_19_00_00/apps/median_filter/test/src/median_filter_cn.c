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


/* ===========================================================================*/
/*   @file : median_filter_cn.c                                               */
/*                                                                            */
/*   @brief  : This file contains all functions calls for median filtering    */
/*             reference                                                      */
/*                                                                            */
/*   @version 0.1 (Sept 2013) : Base version.                                 */
/*                                                                            */
/*============================================================================*/

#include "median_filter_cn.h"

/* Function prototypes */
void vcop_select_kth_smallest_from_hist_cn(short *hist_ptr, unsigned char *optr,
    unsigned short k);

void vcop_compute_block_histogram_8c_cn(unsigned char *inp_data, short *histo, 
    unsigned int blk_wdth, unsigned int blk_hght, unsigned int blk_stride);

void medianFilter_cn
(
    MEDIAN_FILTER_TI_CreateParams *createParams,
    uint16_t  imagePitch,
    uint8_t  *pInput,
    uint8_t  *pMedian,
    int16_t  *histo
)
{
    int i, j;
    unsigned short out_width, out_height;

    out_width = ((createParams->imageWidth - createParams->blockWidth)/createParams->stepSizeHorz) + 1;
    out_height = ((createParams->imageHeight - createParams->blockHeight)/createParams->stepSizeVert) + 1;

    for(i = 0; i < out_height; i++) {
        for(j = 0; j < out_width; j++) {
            vcop_compute_block_histogram_8c_cn(&(pInput[i*createParams->stepSizeVert*imagePitch + j*createParams->stepSizeHorz]),
                                              histo, createParams->blockWidth, createParams->blockHeight, imagePitch);
            vcop_select_kth_smallest_from_hist_cn(histo, &pMedian[i*out_width+j],
                                              (createParams->blockWidth*createParams->blockHeight+1)/2);
        }
    }

    return;
}


void vcop_select_kth_smallest_from_hist_cn
(
    short           *hist_ptr,         /* Transposed histogram: 16 bins of 16-bit values in each row */
    unsigned char   *optr,             /* Output data pointer: 1 8-bit value */
    unsigned short   k                 /* Order statistic required */
)
{
    int i, hist_sum;

    hist_sum = 0;
    for(i = 0; i < 256; i++) {
        hist_sum += hist_ptr[i];
        if(hist_sum >= k) {
            *optr = i;
            break;
        }
    }

    return;
}


void vcop_compute_block_histogram_8c_cn
(
    unsigned char   *inp_data,    /* Block input */
    short           *histo,       /* Block histogram array output: 256 bins of 16-bit values */
    unsigned int     blk_wdth,
    unsigned int     blk_hght,
    unsigned int     blk_stride
)
{
    int i, j;

    memset(histo, 0, 8*2*256);

    for(i = 0; i < blk_hght; i++) {
        for(j = 0; j < blk_wdth; j++) {
            histo[inp_data[i*blk_stride+j]]++;
        }
    }
}

