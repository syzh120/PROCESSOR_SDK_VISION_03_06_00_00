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


/** @file   remap_merge_natc.c
 *
 *  @brief   This file contains test code for the Remap and Merge Applet
 *
 *
 *  @date   Jan, 2014
 *
 *  Description
 *    This file contains natural C code to validate the frame level applet Remap functionality.
 */

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "alg_osal.h"
#include "convert_map.h"
#include "remap_common.h"
#include "eve_profile.h"

uint16_t remapBilinearInterpolate(uint32_t p00, uint32_t p10, uint32_t p01, uint32_t p11,
        uint16_t frac_x, uint16_t frac_y, uint16_t qScale, uint16_t outputQShift, RemapParms *params)
{
    uint16_t qScale_frac_x, qScale_frac_y, m, n, o;
    uint32_t tmp;

    qScale_frac_x = qScale - frac_x;
    qScale_frac_y = qScale - frac_y;

    p00 = p00 * qScale_frac_x;
    p10 = p10 * frac_x;
    p01 = p01 * qScale_frac_x;
    p11 = p11 * frac_x;

    tmp = (p00 + p10) * qScale_frac_y;
    if (tmp >= 65535) {
        tmp = 65535;
    }
    m   = (uint16_t)tmp;

    tmp = (p01 + p11) * frac_y;
    if (tmp >= 65535) {
        tmp = 65535;
    }
    n   = (uint16_t)tmp;

    o   = m + n;

    /* output Q shift will be twice that of input because the output pixel is generated after being
            multiplied by both frac and qscale_frac, each of which are qshifted. */
    o   = (o  + (1 << (outputQShift - 1))) >> outputQShift;

    if (o >= params->sat_high)
        o = params->sat_high_set;
    else if (o < params->sat_low)
        o = params->sat_low_set;

    return o;
}


void remapNatc(uint8_t *srcY, uint8_t *srcUV, uint8_t *dstY, uint8_t *dstUV, RemapParms *params)
{
    sConvertMap *maps = &(params->maps);
    uint32_t    *srcMapU32, U32_x, U32_y, p00, p10, p01, p11;
    uint16_t     x, y, frac_x, frac_y, row, col, o, mult, lumaOffset, chromaOffset, vOffset;
    uint16_t     qScale, outputQShift, srcStride, chroma_x, chroma_y, chroma_frac_x, chroma_frac_y, offset_x, offset_y;
    Format       srcFormat;


    if(params->rightShift != 0)
    {
        TEST_PRINTF("rightShift not supported\n");
        goto EXIT;
    }

    srcFormat = params->maps.srcFormat;
    if (srcFormat != YUV_422ILE && srcFormat != YUV_422IBE && srcFormat != YUV_420SP \
            && srcFormat != U8BIT && srcFormat != S8BIT)
    {
        TEST_PRINTF("Format not supported\n");
        goto EXIT;
    }

    srcMapU32   = (uint32_t*)maps->srcMap;

    for (row = 0; row < maps->mapDim.height; row++)
    {
        for (col = 0; col < maps->mapDim.width; col++)
        {
            if (maps->isSrcMapFloat)
            {
                TEST_PRINTF("Float srcY MAP not supported\n");
            }
            else
            {
                U32_x  = srcMapU32[row*2*maps->mapDim.width + 2*col];
                U32_y  = srcMapU32[row*2*maps->mapDim.width + 2*col + 1];
                x      = (uint16_t)(U32_x >> maps->qShift);
                y      = (uint16_t)(U32_y >> maps->qShift);
                frac_x = (uint16_t)(U32_x - (x << maps->qShift));
                frac_y = (uint16_t)(U32_y - (y << maps->qShift));
            }

            /* output Q shift will be twice that of input because the output pixel is generated after being
                           multiplied by both frac and qscale_frac, each of which are qshifted. */
            outputQShift   = 2 * params->maps.qShift;
            qScale         = (1 << params->maps.qShift);
            srcStride      = params->maps.srcImageDim.width;


            if(params->interpolationLuma == BILINEAR)
            {
                if (srcFormat == YUV_420SP || srcFormat == U8BIT)
                {
                    mult = 1;
                    lumaOffset = 0;
                }
                /* Because luma and chroma are deinterleaved, mult = 2 for 422 formats. */
                else if(srcFormat == YUV_422ILE)
                {
                    mult = 2;
                    /* 422ILE is UYVY format. lumaOffset is to consider the shift by 1 for luma. Hence chromaOffset is 0. */
                    lumaOffset   = 1;
                    chromaOffset = 0;
                } else if(srcFormat == YUV_422IBE)
                {
                    mult = 2;
                    lumaOffset   = 0;
                    chromaOffset = 1;
                }


                /* Bilinear Luma Interpolation for U8/YUV420 formats from srcY and write to DST. */
                p00 = *((uint8_t*)srcY + mult*(y*srcStride + x) + lumaOffset);
                p10 = *((uint8_t*)srcY + mult*(y*srcStride + x + 1) + lumaOffset);
                p01 = *((uint8_t*)srcY + mult*((y + 1)*srcStride + x) + lumaOffset);
                p11 = *((uint8_t*)srcY + mult*((y + 1)*srcStride + x + 1) + lumaOffset);

                o = remapBilinearInterpolate(p00, p10, p01, p11, frac_x, frac_y, qScale, outputQShift, params);

                dstY[mult*(row*maps->mapDim.width + col) + lumaOffset] = (uint8_t)o;

            }else
            {
                TEST_PRINTF("NN Luma Interpolation not supported\n");
            }

            /* Chroma Interpolation for YUV 420 SP */
            if (srcFormat == YUV_420SP)
            {
                if(!(row%2) && !(col%2))
                {
                    /* There is only one U for every 2 Ys along horizontal and vertical direction. */
                    /* Therefore, luma indexes and fracs should be divided by 2 to generate chroma indexes. */
                    /* But since U and V are deinterleaved, chroma x becomes (luma x/2)*2. Also, U and V are considered as a pair. */
                    /* Chroma x should be even to point to U */
                    /* To account for the 1 lost by making x even, we consider offset_x. */
                    if(x%2)
                    {
                        chroma_x = x-1;
                        offset_x = 1 << maps->qShift;
                    }else
                    {
                        chroma_x = x;
                        offset_x = 0;
                    }
                    /* Chroma y should half of luma y */
                    /* To account for the 1 lost during dividing y, we consider offset_y. */
                    if(y%2)
                    {
                        offset_y = 1 << maps->qShift;
                    }else
                    {
                        offset_y = 0;
                    }
                    chroma_y = y/2;

                    chroma_frac_x = (frac_x + offset_x)/2;
                    chroma_frac_y = (frac_y + offset_y)/2;


                    if(params->interpolationChroma == NN)
                    {
                        /* NN Chroma U and V Interpolation for YUV 420 formats. */
                        /* Rounding the fractionals. */
                        chroma_frac_x = (chroma_frac_x + (1 << (params->maps.qShift - 1))) >> params->maps.qShift;
                        chroma_frac_y = (chroma_frac_y + (1 << (params->maps.qShift - 1))) >> params->maps.qShift;

                        p00 = *((uint8_t*)srcUV + (chroma_y + chroma_frac_y)*srcStride + (chroma_x + 2*chroma_frac_x));
                        p01 = *((uint8_t*)srcUV + (chroma_y + chroma_frac_y)*srcStride + (chroma_x + 2*chroma_frac_x) + 1);

                        dstUV[(row/2)*maps->mapDim.width + col]     = (uint8_t)p00;
                        dstUV[(row/2)*maps->mapDim.width + col + 1] = (uint8_t)p01;

                    } else
                    {
                        /* Bilinear Chroma U Interpolation for YUV 420 formats. */
                        p00 = *((uint8_t*)srcUV + chroma_y*srcStride + chroma_x);
                        p10 = *((uint8_t*)srcUV + chroma_y*srcStride + chroma_x + 2);
                        p01 = *((uint8_t*)srcUV + (chroma_y + 1)*srcStride + chroma_x);
                        p11 = *((uint8_t*)srcUV + (chroma_y + 1)*srcStride + chroma_x + 2);

                        o = remapBilinearInterpolate(p00, p10, p01, p11, chroma_frac_x, chroma_frac_y, qScale, outputQShift, params);

                        dstUV[(row/2)*maps->mapDim.width + col] = (uint8_t)o;

                        /* Bilinear Chroma V Interpolation for YUV 420 formats. */
                        p00 = *((uint8_t*)srcUV + chroma_y*srcStride + chroma_x + 1);
                        p10 = *((uint8_t*)srcUV + chroma_y*srcStride + chroma_x + 3);
                        p01 = *((uint8_t*)srcUV + (chroma_y + 1)*srcStride + chroma_x + 1);
                        p11 = *((uint8_t*)srcUV + (chroma_y + 1)*srcStride + chroma_x + 3);

                        o = remapBilinearInterpolate(p00, p10, p01, p11, chroma_frac_x, chroma_frac_y, qScale, outputQShift, params);

                        dstUV[(row/2)*maps->mapDim.width + col + 1] = (uint8_t)o;

                    }
                }
            }else if(srcFormat == YUV_422ILE || srcFormat == YUV_422IBE)
            {
                /* There is a U associated with every alternate Y along the horizontal direction. */
                /* Similarly, there is a V associated with the other alternate Y along the horizontal direction. */
                /* Therefore, luma indexes and fracs along the horizontal direction should be divided by 2 to generate chroma indexes. */
                /* To account for the 1 lost by dividing x, we consider offset_x. */
                /* We consider the luma backmapping values at even horizontal locations for U and the ones at odd horizontal locations for V. */
                if(!(col%2))
                {
                    /* vOffset is the positional difference of V from U. ie V is 2 pixels away from U. */
                    vOffset = 0;
                } else
                {
                    vOffset = 2;
#if 0
                    /* For REL.EVE.SW.01.06.00.00 or before. */
                    /* For chroma V, since the first (leftmost chroma V is associated with the second Y pixel, */
                    /* we subtract 1 from x. */
                    if(x >= 1)
                    {
                        x = x-1;
                    }
#endif
                }

                if(x%2)
                {
                    offset_x = 1 << maps->qShift;
                }else
                {
                    offset_x = 0;
                }
                chroma_x = x/2;
                chroma_y = y;

                chroma_frac_x = (frac_x + offset_x)/2;
                chroma_frac_y =  frac_y;

                if(params->interpolationChroma == NN)
                {
                    /* NN Chroma U or V Interpolation for YUV 422 formats. */
                    /* Rounding the fractionals. */
                    chroma_frac_x = (chroma_frac_x + (1 << (params->maps.qShift - 1))) >> params->maps.qShift;
                    chroma_frac_y = (chroma_frac_y + (1 << (params->maps.qShift - 1))) >> params->maps.qShift;

                    p00 = *((uint8_t*)srcY + (chroma_y + chroma_frac_y)*srcStride*mult + 4*(chroma_x + chroma_frac_x) + chromaOffset + vOffset);

                    dstY[mult*(row*maps->mapDim.width + col) + chromaOffset]     = (uint8_t)p00;

                } else
                {
                    /* Bilinear Chroma U or V Interpolation for YUV 422 formats. */
                    p00 = *((uint8_t*)srcY + chroma_y*srcStride*mult + 4*chroma_x + chromaOffset + vOffset);
                    p10 = *((uint8_t*)srcY + chroma_y*srcStride*mult + 4*(chroma_x + 1) + chromaOffset + vOffset);
                    p01 = *((uint8_t*)srcY + (chroma_y + 1)*srcStride*mult + 4*chroma_x + chromaOffset + vOffset);
                    p11 = *((uint8_t*)srcY + (chroma_y + 1)*srcStride*mult + 4*(chroma_x + 1) + chromaOffset + vOffset);

                    o = remapBilinearInterpolate(p00, p10, p01, p11, chroma_frac_x, chroma_frac_y, qScale, outputQShift, params);

                    dstY[mult*(row*maps->mapDim.width + col) + chromaOffset]     = (uint8_t)o;
                }
            }
        }
    }


    EXIT:
    return;
}

