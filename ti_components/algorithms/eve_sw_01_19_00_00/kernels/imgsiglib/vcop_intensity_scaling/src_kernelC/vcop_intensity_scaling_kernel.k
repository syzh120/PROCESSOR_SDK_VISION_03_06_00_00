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

/*                                                                          */
/* NAME:                                                                    */
/*    vcop_intensity_scaling                                                */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*             The routine accepts a gray-scale input image (inImg) and     */
/*     bins the input gray-scale pixels into bins as specified by           */
/*     'scalingLUT'. The output at 'outImg' is of size blockHeight by       */
/*     blockWidth.                                                          */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF Low, IMBUF  */
/*     High or WMEM.                                                        */
/*                                                                          */
/* USAGE:                                                                   */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_intensity_scaling                                           */
/*    (                                                                     */
/*        __vptr_uint8       inImg_A,                                       */
/*        __vptr_uint8       scalingLUT_C,                                  */
/*        __vptr_uint8       outImg_B,                                      */
/*        unsigned short     blockWidth,                                    */
/*        unsigned short     blockHeight,                                   */
/*        unsigned short     blockStride                                    */
/*    )                                                                     */
/*                                                                          */
/*    inImg_A         : 8-bit grayscale image block. This buffer should     */
/*                      contain atleast blockHeight*blockStride bytes.      */
/*    scalingLUT_C    : Pointer to look-up table for performing intensity   */
/*                      scaling.                                            */
/*    outImg_B        : Pointer to intensity scaled output image.           */
/*    blockWidth      : Width of the input image block.                     */
/*    blockHeight     : Height of the input image block.                    */
/*    blockStride     : Stride of the input image block.                    */
/*                                                                          */
/*    Returns    :  None or void.                                           */
/*                                                                          */
/* PERFORMANCE MEASUREMENT:                                                 */
/*    0.125 cycles/pix + 54 VCOP cycles overhead.                           */
/*                                                                          */
/* VERSION:                                                                 */
/*    1.0 (Jan 2014) : Base version.                                        */
/*                                                                          */
/*==========================================================================*/

#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define NUM_TBLS        (8)
#define NUM_PTS_TLU     (1)

#define IND_ELEMSZ (sizeof(*inImg_A))
#define IND_VECTORSZ (IND_ELEMSZ * NUM_TBLS)
#define IND_ROWSZ (blockStride*IND_ELEMSZ)

#define OUT_ELEMSZ (sizeof(*outImg_B))
#define OUT_VECTORSZ (OUT_ELEMSZ * NUM_TBLS)
#define OUT_ROWSZ (blockWidth *OUT_ELEMSZ)

void vcop_intensity_scaling
(
    __vptr_uint8       inImg_A,
    __vptr_uint8       scalingLUT_C,
    __vptr_uint8       outImg_B,
    unsigned short     blockWidth,
    unsigned short     blockHeight,
    unsigned short     blockStride
)
{
  __vector Vin, Vscaledpix;

  _LOOKUP(NUM_TBLS, NUM_PTS_TLU);

  for (int I1 = 0; I1 < blockHeight; I1++)
  {
    for (int I2 = 0; I2 < (blockWidth + NUM_TBLS - 1)/NUM_TBLS; I2++)
    {
      __agen table_addr = 0;
      __agen index_addr = I2 * IND_VECTORSZ + I1 * IND_ROWSZ;
      __agen out_addr = I2 * OUT_VECTORSZ + I1 * OUT_ROWSZ;

      Vin = inImg_A[index_addr];

      Vscaledpix = scalingLUT_C[table_addr].lookup(Vin);

      outImg_B[out_addr].table_npt() = Vscaledpix;
    }
  }
}

