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


#include <stdint.h>
#include <stdio.h>

#include "vcop_intensity_scaling.h"

int32_t prepare_lut
(
    uint8_t loPixelVal,
    uint8_t hiPixelVal,
    uint8_t numLevels,
    uint8_t numTables,
    uint8_t scalingLUT[]
)
{
  int32_t status = 0;
  uint32_t i, j, k, idx, lut_idx;
  uint16_t curBin;
  uint8_t pixRange;

  if((numTables != 1U) && (numTables != 8U)) {
#ifdef __DEBUG
    printf("Unsupported number of tables.\n");
#endif
    status = GLCM_ERROR_UNSUPPORTED_NUM_LUT_TABLES;

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    goto EXIT;
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  pixRange = (hiPixelVal - loPixelVal);

  /* Prepare the LUT for intensity scaling */
  for(i = 0; i < (256U/(32U/numTables)); i++) {
    for(k = 0; k < numTables; k++) {
      for(j = 0; j < (32U/numTables); j++) {
        idx = (i*(32U/numTables)) + j;
        lut_idx = (i*32U) + (k*4U) + j;
        if(idx <= loPixelVal) {
          /* Pixels less than loPixelVal maps to first bin*/
          scalingLUT[lut_idx] = 0;
        }
        else if(idx >= hiPixelVal){
          /* Pixels greater than hiPixelVal maps to last bin*/
          scalingLUT[lut_idx] = numLevels - 1U;
        }
        else {
          /* Equi-sized bins within pixRange with loPixelVal mapping to 0 and
             hiPixelVal mapping to (numLevels-1) */
          curBin = (uint16_t)((idx - loPixelVal)*numLevels)/pixRange;
          if( curBin  > ((uint16_t)numLevels - (uint16_t)1)) {
            curBin = ((uint16_t)numLevels - (uint16_t)1);
          }
          scalingLUT[lut_idx] = (uint8_t)curBin;
        }
      }
    }
  }

EXIT:
  return status;
}
