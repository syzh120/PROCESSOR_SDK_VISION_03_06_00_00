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
/*     vcop_bin_image_to_list_kernel                                        */
/*                                                                          */
/* USAGE:                                                                   */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_bin_image_to_list                                          */
/*     (                                                                    */
/*         __vptr_uint8   im_A,                                             */
/*         __vptr_uint32  upperLeftXY,                                      */
/*         __vptr_uint16  outXY_B,                                          */
/*         __vptr_uint32  listSize,                                         */
/*         unsigned short width,                                            */
/*         unsigned short height,                                           */
/*         unsigned short inputStride,                                      */
/*         __vptr_uint8   xSequence_C                                       */
/*     )                                                                    */
/*                                                                          */
/*     im_A          :  8-bit binary input image. This buffer should        */
/*                      contain height*stride/8 bytes. The exact format of  */
/*                      the binary bit mask in image is as shown below:     */
/*                      Pix7  Pix6  Pix5  ... Pix0  Pix15 Pix14 ... Pix8    */
/*                      Pix23 Pix22 Pix21 ... Pix16 ...                     */
/*     upperLeftXY   :  (X, Y) co-ordinate of the top-left pixel.           */
/*                      X co-ordinate is expected in the upper 16-bits and  */
/*                      the Y co-ordinate is expected in the lower 16-bits. */
/*     outXY_B       :  32-bit (X, Y) co-ordinate list of locations of      */
/*                      non-zero entries in im_A. Here lower 16-bits        */
/*                      contain Y co-ordinate and upper 16-bits contain     */
/*                      the X co-oridinate. The buffer should be of size    */
/*                      equal to 'width*height' words to accomodate worst   */
/*                      case scenario where all pixels are 1's.             */
/*     width         :  Width of the input image. Good to be a multiple of  */
/*                      8. In case width is not a multiple of 8 the stride  */
/*                      should be atleast aligned to next mutiple of 8 and  */
/*                      the image should be all zeros in the padded region. */
/*     height        :  Height of the input image.                          */
/*     inputStride   :  Input image stride. Should be a multiple of 8.      */
/*     xSequence_C   :  Point to the following pre-generated sequence of    */
/*                      numbers: 0, 1, 2, ..., width-1.                     */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*             This routine accepts an 8-bit input image and outputs a      */
/*     list of (X, Y) locations of non-zeros pixels in the image.           */
/*     The recomended memory bank for each of the buffers is captured as    */
/*     A/B/C as part of the buffer pointer. A/B/C can either be IMBUF High, */
/*     IMBUF low or WMEM.                                                   */
/*                                                                          */
/* PERFORMANCE MEASUREMENT:                                                 */
/*     0.377 cycles/pix + 93 cycle VCOP overhead                            */
/*                                                                          */
/* VERSION:                                                                 */
/*            1.0 (Nov 2013) : Base version.                                */
/*                                                                          */
/*==========================================================================*/
#if VCOP_HOST_EMULATION

#include <vcop.h>
#endif

#define IMG_ELEMSZ     (sizeof(*im_A))
#define LIST_ELEMSZ    (sizeof(*listSize))
#define IMG_VECTORSZ   (1)
#define SEQ_VECTORSZ   (VCOP_SIMD_WIDTH*sizeof(*xSequence_C))

void vcop_bin_image_to_list
(
    __vptr_uint8   im_A,
    __vptr_uint32  upperLeftXY,   /* AL: point to the (X, Y) coordinate of the upper left pixel in the block being processed, these are updated by ARP32 */
    __vptr_uint32  outXY_B,
    __vptr_uint32  listSize,
    unsigned short width,
    unsigned short height,
    unsigned short inputStride,
    unsigned char  outputQformat,
    __vptr_uint32  xSequence_C    /* WMEM: point to the following pre-generated sequence of numbers: 0, 1, 2, ..., width-1 */
)
{
    __vector upLeftXY, numEntries, XYIncr;
    __vector VoutQformat;
    __vector xyOffset, XYIncrQFormat;
    __agen Addr0;
    Addr0 = 0;
    numEntries = 0;

    /* Read the (X, Y) coordinate of the upper left pixel in the block being processed, these are updated by ARP32 */
    upLeftXY = upperLeftXY[Addr0].onept();
    XYIncr = height;
    VoutQformat = outputQformat;

    /* This loop produces the list of coordinates (X, Y) corresponding to non-zeros pixels in the input binary image.
     * Iterates height*ceil(width/8) times.
     * */

    for(int k = 0; k < 1; k++)
    {
        __vector K0, K1;
        K0 = 0;
        K1 = 1;

        for (int i = 0; i < height; i++)                                        /* This loop iterates height*ceil(width/8) times */
        {
            for (int j = 0; j < (width+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; j++)     /* This loop iterates ceil(width/8) times */
            {
                __agen Addr1, Addr2;
                __vector xseq, I, mask, y, xy;

                Addr1 = j*SEQ_VECTORSZ;
                Addr2 = i*(inputStride/8)*IMG_ELEMSZ + j*IMG_VECTORSZ;

                /* Initialize y to the current row counter 'i' */
                y = i;

                /* Read the X coordinate of sequence 0, 1, 2, 3, ..., width -1 */
                xseq = xSequence_C[Addr1];

                /* Read the input image mask of 0 or 1 */
                I = im_A[Addr2].onept();

                /* Unpack the input binary image */
                mask = unpack(I, K1);                    /* 1 cycle to execute + 1 delay slot */
                xy = y << VoutQformat;

                /* Calculate (X, Y) coordinates */
                xy += xseq + upLeftXY;

                numEntries += mask;                      /* 1 cycle to execute */

                outXY_B[collate(mask)] = xy;
            }
        }
        listSize[Addr0] = numEntries;
    }

    for(int i = 0; i < 1; i++)
    {
        __vector updatedXY;

        for(int j = 0; j < 7; j++)
        {
            __agen Addr1;
            __vector sz;

            Addr1 = j*LIST_ELEMSZ;

            sz = (listSize + LIST_ELEMSZ)[Addr1].onept();

            XYIncrQFormat  = XYIncr << VoutQformat;

            numEntries += sz;
            xyOffset = upLeftXY + XYIncrQFormat ;
        }
        listSize[Addr0].onept() = numEntries;
        upperLeftXY[Addr0].onept() = xyOffset;
    }
}

