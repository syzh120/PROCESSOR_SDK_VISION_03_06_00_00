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


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vcop_soft_isp_cn.h"

int32_t soft_isp_ref_cn(uint16_t *pInput,
                        uint8_t  *pOutput,
                        uint8_t  *pOutputR,
                        uint8_t  *pStatsBuf,
                        uint16_t  imageWidth,
                        uint16_t  imageHeight,
                        uint16_t  imagePitch,
                        uint8_t   rPosition,
                        uint8_t   sensorBitDepth,
                        uint8_t   enableDecompand,
                        uint16_t  pout1,
                        uint16_t  pout2,
                        uint8_t   slope1,
                        uint16_t  slope2,
                        uint16_t *blackClamp,
                        uint16_t *cBalanceGain,
                        uint8_t   cBalanceShift,
                        uint8_t   enableExtractR,
                        uint8_t   enableStats,
                        uint16_t  statBlkWidth,
                        uint16_t  statBlkHeight,
                        uint16_t  saturationLimit,
                        uint8_t   gbceMethod,
                        uint8_t  *pGbceToneCurve)
{
  int32_t status = 0;
  uint32_t i, outStride, bufStride;
  uint8_t bitShift, start_x;
  uint16_t *pInput_rc, *pInput_cc;
  uint16_t *pOut_rc, *pOut_cc;
  uint8_t  *pOutput_rc, *pOutput_cc;
  uint32_t p2;

  uint16_t *pDecompandOut_rc, *pDecompandOut_cc;
  uint16_t *pBlackClampOut_rc, *pBlackClampOut_cc;

  outStride = 16*((imageWidth + 15)/16);

  /* Allocate Input buffers */
  bufStride = (outStride > imagePitch)? outStride : imagePitch;
  pInput_rc = (uint16_t *)malloc((imageHeight/2)*bufStride*sizeof(uint16_t));
  pInput_cc = (uint16_t *)malloc((imageHeight/2)*bufStride*sizeof(uint16_t));

  /* Allocate intermediate output buffers */
  pOut_rc = (uint16_t *)malloc((imageHeight/2)*outStride*sizeof(uint16_t));
  pOut_cc = (uint16_t *)malloc((imageHeight/2)*outStride*sizeof(uint16_t));

  /* Allocate output buffers */
  pOutput_rc = (uint8_t *)malloc((imageHeight/2)*imageWidth);
  pOutput_cc = (uint8_t *)malloc((imageHeight/2)*imageWidth);

  /* Deinterleave RC and CC pixels */
  for(i = 0; i < imageHeight/2; i++) {
    if(rPosition == 1 || rPosition == 2) {
      memcpy(pInput_rc + i*imagePitch, pInput + 2*i*imagePitch, imageWidth*sizeof(uint16_t));
      memcpy(pInput_cc + i*imagePitch, pInput + (2*i + 1)*imagePitch, imageWidth*sizeof(uint16_t));
    }
    else {
      memcpy(pInput_cc + i*imagePitch, pInput + 2*i*imagePitch, imageWidth*sizeof(uint16_t));
      memcpy(pInput_rc + i*imagePitch, pInput + (2*i + 1)*imagePitch, imageWidth*sizeof(uint16_t));
    }
  }

  /* Optional piece-wise linear decompanding for HDR sensor input */
  if(enableDecompand == 1) {
    pDecompandOut_rc  = pOut_rc;
    pDecompandOut_cc  = pOut_cc;
    pBlackClampOut_rc = pInput_rc;
    pBlackClampOut_cc = pInput_cc;
    bufStride         = outStride;

    p2 = pout1 + (pout2 - pout1)*slope1;

    status = vcop_decompand_piecewise_linear_cn(pInput_rc, pInput_cc, pDecompandOut_rc,
        pDecompandOut_cc, imageWidth, imageHeight, imagePitch, outStride, pout1, p2,
        pout2, slope1, slope2, sensorBitDepth - 16);

    if(status != 0) {
      printf("SOFT ISP C reference: Decompanding failed.\n");
      goto EXIT;
    }
  }
  else {
    pDecompandOut_rc  = pInput_rc;
    pDecompandOut_cc  = pInput_cc;
    pBlackClampOut_rc = pOut_rc;
    pBlackClampOut_cc = pOut_cc;
    bufStride         = imagePitch;
  }

  /* Black clamp and C imbalance correction */
  status = vcop_black_clamp_c_balance_cn(pDecompandOut_rc, pDecompandOut_cc, pBlackClampOut_rc,
               pBlackClampOut_cc, imageWidth, imageHeight, bufStride, outStride,
               blackClamp, cBalanceGain, cBalanceShift);

  if(status != 0) {
    printf("SOFT ISP C reference: Black Clamp and C Balance failed.\n");
    goto EXIT;
  }

  /* Extract R pixels */
  if(enableExtractR == 1) {
    if((rPosition == 1) || (rPosition == 3)) {
      start_x = 2;
    }
    else {
      start_x = 3;
    }
    if(enableDecompand == 1) {
      bitShift = 8;
    }
    else {
      bitShift = sensorBitDepth - 8;
    }
    vcop_soft_isp_extract_r_cn(pBlackClampOut_rc + outStride + start_x,
      pOutputR, imageWidth - 4, imageHeight - 4, outStride, bitShift);
  }

  /* Statistics Collection */
  if(enableStats == 1) {
    status = vcop_stats_collector_dense_cn(pBlackClampOut_rc + outStride + 2,
        pBlackClampOut_cc + outStride + 2, pStatsBuf, imageWidth - 4,
        imageHeight - 4, outStride, 1, statBlkWidth, statBlkHeight,
        saturationLimit);

    if(status != 0) {
      printf("SOFT ISP C reference: Statistics Collector failed.\n");
      goto EXIT;
    }
  }

  /* RCCC to CCCC CFA interpolation */
  status = vcop_rccc_to_cccc_cn(pBlackClampOut_rc, pBlackClampOut_cc, imageWidth, imageHeight,
               outStride, rPosition);

  if(status != 0) {
    printf("SOFT ISP C reference: CFA Interpolation failed.\n");
    goto EXIT;
  }

  /* Global Brightness and Contrast Enhancement (GBCE) */
  if(enableDecompand == 1) {
    bitShift = 4;
  }
  else {
    bitShift = (sensorBitDepth > 12) ? (sensorBitDepth - 12): 0;
  }

  if(gbceMethod == 0) {
    status = vcop_gbce_simple_cn(pBlackClampOut_rc + outStride + 2, pBlackClampOut_cc + outStride + 2,
                 pOutput_rc, pOutput_cc, imageWidth - 4, imageHeight - 4,
                 outStride, bitShift, pGbceToneCurve);
  }
  else {
    status = vcop_gbce_interp_cn(pBlackClampOut_rc + outStride + 2, pBlackClampOut_cc + outStride + 2,
                 pOutput_rc, pOutput_cc, imageWidth - 4, imageHeight - 4,
                 outStride, bitShift, ((1 << bitShift) - 1), pGbceToneCurve);
  }

  if(status != 0) {
    printf("SOFT ISP C reference: GBCE failed.\n");
    goto EXIT;
  }

  /* Interleave back RC and CC pixels */
  for(i = 0; i < (imageHeight - 4)/2; i++) {
    if(rPosition == 0 || rPosition == 1) {
      memcpy(pOutput + 2*i*(imageWidth - 4), pOutput_rc + i*(imageWidth - 4), imageWidth - 4);
      memcpy(pOutput + (2*i + 1)*(imageWidth - 4), pOutput_cc + i*(imageWidth - 4), imageWidth - 4);
    }
    else {
      memcpy(pOutput + 2*i*(imageWidth - 4), pOutput_cc + i*(imageWidth - 4), imageWidth - 4);
      memcpy(pOutput + (2*i + 1)*(imageWidth - 4), pOutput_rc + i*(imageWidth - 4), imageWidth - 4);
    }
  }

EXIT:
  free(pInput_rc);
  free(pInput_cc);
  free(pOut_rc);
  free(pOut_cc);
  free(pOutput_rc);
  free(pOutput_cc);

  return (status);
}

