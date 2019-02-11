/*
*
* Copyright (c) 2007-2017 Texas Instruments Incorporated
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


/*                                                                            */
/* NAME: vcop_census_8bits                                                    */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/* The function "vcop_census_8bits" takes an input image block and apply      */
/* a "census filter" on every pixel                                           */
/* Performance is:                                							  */
/* 1/32 + 3 * ((winHeight+winVertStep-1)/winVertStep) * ((winWidth+winHorzStep-1)/winHorzStep) / 32  + 2*2*ALIGN_8(winWidth * winHeight) / 128  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2014.                                  */
/*============================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define VCOP_SIMD_WIDTH2 (2*VCOP_SIMD_WIDTH)
#define VCOP_SIMD_WIDTH4 (4*VCOP_SIMD_WIDTH)
#define ELEMSZ          sizeof(*pIn8)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

#define ALIGN_2(a)   (((a) + 1) & ~(1))
#define ALIGN_8(a)   (((a) + 7) & ~(7))
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD2(a)   (((a) + (2*VCOP_SIMD_WIDTH)-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD4(a)   (((a) + (4*VCOP_SIMD_WIDTH)-1) & ~(4*VCOP_SIMD_WIDTH-1))

#define MIN(a,b) ((a)<(b)?(a):(b))

void vcop_census_8bits
(
        __vptr_uint8 pIn8,  /* in ILA */
        __vptr_uint16 pIn16,  /* points to same location as pIn8 in ILA, used for the copy, faster processing if elements are viewed as 16-bits */
        __vptr_uint8 pOut,
        __vptr_uint8 pScratchBitmask, /* IAH of size (2*NUM_WIN_W_ITER*NUM_WIN_H_ITER + 16)*((computeWidth+15)/16)*computeHeight bytes*/
        __vptr_uint8 pScratch8, /* 32 bytes aligned and WBUF size is MAX(computeWidth*scratchStride*(NUM_WIN_W_ITER*NUM_WIN_H_ITER+7)/8, inStride * (computeHeight + winHeight -1 ) + 15) bytes */
        __vptr_uint16 pScratch16, /* points to same location as pScratch8 in WBUF, size is MAX((computeHeight)2*(ALIGN_SIMD2(computeWidth)/VCOP_SIMD_WIDTH2)*scratchStride*(NUM_WIN_W_ITER*NUM_WIN_H_ITER+7)/8, inStride * (computeHeight + winHeight -1 ) + 15) bytes */
        __vptr_uint16 pOffset, /* Point to an array of 32 bytes. Call init_census_8bits_params() to initialize content pointed by pOffset*/
        __vptr_uint8 pCodeWordMask, /* Point to an array of (NUM_WIN_W_ITER*NUM_WIN_H_ITER+7)/8 bytes. Call init_census_8bits_params() to initialize content pointed by pCodeWordMask */
        __vptr_uint8 pRowMask,/* Point to an array of (computeHeight+7)/8 bytes. Call init_census_8bits_params() to initialize content pointed by pRowMask */
        unsigned char winWidth, /* width of the support window, that defines the neighborhood in which census transform is applied around each pixel. */
        unsigned char winHeight, /* height of the support window, that defines the neighborhood in which census transform is applied around each pixel. */
        unsigned char winHorzStep, /* horizontal step between each orientation in the support window. Typically 1 or 2. */
        unsigned char winVertStep, /* vertical step between each orientation in the support window. Typically 1 or 2. */
        unsigned short computeWidth, /* Must be multiple of 16 */
        unsigned short computeHeight, /* For best performance, should be multiple of 8 */
        unsigned short inStride, /* Must be >= computeWidth + winWidth - 1 */
        unsigned short outStride, /* in bytes and must be multiple of 4, but not multiple of 32 */
        unsigned short scratchStride /* scratchStride is returned by init_census_8bits_params() and is equal to (ALIGN_32(computeHeight) + 4) bytes */
)
{

    /* Make a copy in WMEM for faster processing later on 
     * We use the pointer to 16-bits in order to speed up the copy as we can copy 16x16=256 bits= 32 bytes per cycle
     * 1/32 cyc/pixel
     * */
    for(int i=0;i<ALIGN_SIMD2((inStride*(computeHeight + winHeight - 1)+1)/2)/VCOP_SIMD_WIDTH2;i++){
        __agen Addr= i*VCOP_SIMD_WIDTH2*2;
        __vector vIn1, vIn2;

        (vIn1, vIn2)= pIn16[Addr].deinterleave(); /* ILA */
        pScratch16[Addr].interleave()= (vIn1, vIn2);  /* WMEM */

    }

    /* This loop generates the bitmask that correspond to positions where the center pixel is greater 
     * 
     * To illustrate the implementation, we consider a 3x3 census transform as example:
     * 
     * A   B   C
     * D   E   F
     * G   H   I
     * 
     * 
     * First we will prepare all pixels for orientation A, using Bank 0 and storing down one column, so Bank 0, at end of innermost loop will look like:
            Bank0                                         
            WBUF                                          
Row 0:      {B15..B0} {A15…A0}            
Row 1:                    

Basically 2 bytes per orientation is stored at a time in the innermost loop. These 2 bytes correspond to 16 pixels.  
The outer loop will fill orientation B in byte #2 of bank 0, orientation C in byte #0 of Bank 1, orientation D in byte #2 of bank 1. So, for 8 orientations we will exhaust 2 banks
bank 0 to bank 3, which is 16 bytes.  We can work on next 16 pixels and use Banks 4, 5, 6 and 7 for next 8 orientations. 
Effectively, this means each set of 16 pixels is separated by 2*N bytes where N is the number of orientations.
However since we are using interleave store, 16 bytes
are actually written out every cycle, not 2 bytes. Ideally the last 14 bytes of every interelaved store should be thrown away but since there is no predicate interleave store,
they are written to the memory anyway. We use an offset of 2 bytes so the scheme still works except that the spacing between each set of 16 pixels should be 2*N + 14 bytes, 
not 2*N bytes in order to prevent any side effect.
To align to a multiple of 16 bytes, let's set the spacing to 2*N + 16 bytes.

    If we had more orientations, we can store up to 32 orientations within one line across all banks, 1 byte at a time.

So, at the end of the loop:

WBUF:
    Bank0   Bank1   Bank2   Bank 3  Bank4   Bank5   Bank6   Bank7   Bank8   Bank9       Bank10      Bank11      Bank12
    AB_0…15 CD_0…15 EF_0…15 GH_0…15 IX_0…15 XXXXX   XXXXX   XXXXX   XXXXX   AB_16…31    CD_16…31    EF_16…31    GH_16…31 IX_16…31
    Each bank is 4 bytes
     * 
     * 2 * winHeight * winWidth / 16 cycles per pixel (one delay slot for bitpack)
     * */
#define NUM_ITER_W (ALIGN_SIMD2(computeWidth)/VCOP_SIMD_WIDTH2)
#define NUM_WIN_H_ITER ((winHeight + winVertStep - 1)/winVertStep)
#define NUM_WIN_W_ITER ((winWidth + winHorzStep - 1)/winHorzStep)

    for(int wh= 0; wh<NUM_WIN_H_ITER; wh++) {
        for(int ww= 0; ww<NUM_WIN_W_ITER; ww++) {
            for(int h=0; h< computeHeight/2; h++) {
                for (int w=0; w< NUM_ITER_W; w++) {

                    __agen AddrCenter= 2*h*ELEMSZ*inStride + w*ELEMSZ*VCOP_SIMD_WIDTH2;
                    __agen AddrNeighbour= wh*winVertStep*ELEMSZ*inStride + ww*winHorzStep*ELEMSZ + 2*h*ELEMSZ*inStride + w*ELEMSZ*VCOP_SIMD_WIDTH2;
                    __agen AddrBitmask= wh*2*NUM_WIN_W_ITER + ww*2 + 2*h*NUM_ITER_W*(2*NUM_WIN_W_ITER*NUM_WIN_H_ITER+VCOP_SIMD_WIDTH2) + w*(2*NUM_WIN_W_ITER*NUM_WIN_H_ITER+VCOP_SIMD_WIDTH2);

                    __vector vCenter1, vCenter2, vCenter3, vCenter4, vNeighbour1, vNeighbour2, vNeighbour3, vNeighbour4, vBitMask1, vBitMask2, vBitMask3, vBitMask4;

                    (vCenter1, vCenter2)= (pIn8+ELEMSZ*(winWidth/2+(winHeight/2)*inStride))[AddrCenter].deinterleave(); /* load 16x8= 128 bits from ILA, vCenter1= pixels 0,2,..14 and vCenter2= pixels 1,3,..15 */
                    (vNeighbour1, vNeighbour2)= pScratch8[AddrNeighbour].deinterleave(); /* load 16x8= 128 bits from WBUF */
                    (vCenter3, vCenter4)= (pIn8+ELEMSZ*(winWidth/2+(winHeight/2 + 1)*inStride))[AddrCenter].deinterleave(); /* load 16x8= 128 bits from ILA, vCenter1= pixels 0,2,..14 and vCenter2= pixels 1,3,..15 */
                    (vNeighbour3, vNeighbour4)= (pScratch8 + ELEMSZ*inStride)[AddrNeighbour].deinterleave(); /* load 16x8= 128 bits from WBUF */

                    vBitMask1= pack(vCenter1 >= vNeighbour1); /* vBitmask contains resulting comparison for pixels 0,2,..14 of the current orientation */
                    vBitMask2= pack(vCenter2 >= vNeighbour2); /* vBitmask contains resulting comparison for pixels 1,3,..15 of the current orientation */
                    vBitMask3= pack(vCenter3 >= vNeighbour3); /* vBitmask contains resulting comparison for pixels 0,2,..14 of the current orientation */
                    vBitMask4= pack(vCenter4 >= vNeighbour4); /* vBitmask contains resulting comparison for pixels 1,3,..15 of the current orientation */

                    pScratchBitmask[AddrBitmask].interleave()= (vBitMask1, vBitMask2); /* store 2 bytes in IAH, pixels 0,2,..,14 followed by pixels 1,3,..,15 */
                    (pScratchBitmask+NUM_ITER_W*(2*NUM_WIN_W_ITER*NUM_WIN_H_ITER+VCOP_SIMD_WIDTH2))[AddrBitmask].interleave()= (vBitMask3, vBitMask4);
                }
            }
        }
    }

    /* 
     * 2 *ALIGN_8(winWidth * winHeight) / (8*16) cycles per pixel
     * 
     * Bit transpose so that:
    Bank0   Bank1   Bank2   Bank 3  Bank4   Bank5   Bank6   Bank7   Bank8   Bank9       Bank10      Bank11      Bank12
    AB_0…15 CD_0…15 EF_0…15 GH_0…15 IX_0…15 XXXXX   XXXXX   XXXXX   XXXXX   AB_16…31    CD_16…31    EF_16…31    GH_16…31

     * becomes (X,Y)_HGFEDCBA:
     *  (0,0)_HGFEDCBA (1,0)_HGFEDCBA ... (15,0)_HGFEDCBA (0,0)_XXXXXXXI (1,0)_XXXXXXXI ... (15,0)_XXXXXXXI (16,0)_HGFEDCBA (17,0)_HGFEDCBA ... (31,0)_HGFEDCBA (16,0)_XXXXXXXI (17,0)_XXXXXXXI ... (31,0)_XXXXXXXI
     *  (0,1)_HGFEDCBA (1,1)_HGFEDCBA ... (15,1)_HGFEDCBA (0,1)_XXXXXXXI (1,1)_XXXXXXXI ... (15,1)_XXXXXXXI (16,1)_HGFEDCBA (17,1)_HGFEDCBA ... (31,1)_HGFEDCBA (16,1)_XXXXXXXI (17,1)_XXXXXXXI ... (31,1)_XXXXXXXI
     * 
     * etc
     * 
     * Except that we store in transpose format (X,Y)_HGFEDCBA, where the stride between each row is 9 bytes in order to use parallel scatter.
     * Transpose store is used as a first step to concatenate (X,Y)_HGFEDCBA with (X,Y)_XXXXXXXI. In next vloop we transpose again to produce the final output
     * 
     * (0,0)_HGFEDCBA       (0,1)_HGFEDCBA      (0,2)_HGFEDCBA      (0,3)_HGFEDCBA      (0,4)_HGFEDCBA      (0,5)_HGFEDCBA      (0,6)_HGFEDCBA      ...     (0,COMPUTE_HEIGHT-1)_HGFEDCBA  0
     * (2,0)_HGFEDCBA       (2,1)_HGFEDCBA      (2,2)_HGFEDCBA      (2,3)_HGFEDCBA      (2,4)_HGFEDCBA      (2,5)_HGFEDCBA      (2,6)_HGFEDCBA      ...     (2,COMPUTE_HEIGHT-1)_HGFEDCBA  0
     * ...
     * (COMPUTE_WIDTH-2,0)_HGFEDCBA       (COMPUTE_WIDTH-2,1)_HGFEDCBA      (COMPUTE_WIDTH-2,2)_HGFEDCBA      (COMPUTE_WIDTH-2,3)_HGFEDCBA      (COMPUTE_WIDTH-2,4)_HGFEDCBA      (COMPUTE_WIDTH-2,5)_HGFEDCBA      (COMPUTE_WIDTH-2,6)_HGFEDCBA      ... (COMPUTE_WIDTH-2, COMPUTE_HEIGHT-1)_HGFEDCBA  0
     *
     * (1,0)_HGFEDCBA       (1,1)_HGFEDCBA      (1,2)_HGFEDCBA      (1,3)_HGFEDCBA      (1,4)_HGFEDCBA      (1,5)_HGFEDCBA      (1,6)_HGFEDCBA      ...     (1,COMPUTE_HEIGHT-1)_HGFEDCBA  0
     * (3,0)_HGFEDCBA       (3,1)_HGFEDCBA      (3,2)_HGFEDCBA      (3,3)_HGFEDCBA      (3,4)_HGFEDCBA      (3,5)_HGFEDCBA      (3,6)_HGFEDCBA      ...     (3,COMPUTE_HEIGHT-1)_HGFEDCBA  0
     * ...
     * (COMPUTE_WIDTH-1,0)_HGFEDCBA       (COMPUTE_WIDTH-1,1)_HGFEDCBA      (COMPUTE_WIDTH-1,2)_HGFEDCBA      (COMPUTE_WIDTH-1,3)_HGFEDCBA      (COMPUTE_WIDTH-1,4)_HGFEDCBA      (COMPUTE_WIDTH-1,5)_HGFEDCBA      (COMPUTE_WIDTH-1,6)_HGFEDCBA      ...   (COMPUTE_WIDTH-1,COMPUTE_HEIGHT-1)_HGFEDCBA  0
     *
     * (0,0)_XXXXXXXI       (0,1)_XXXXXXXI      (0,2)_XXXXXXXI      (0,3)_XXXXXXXI      (0,4)_XXXXXXXI      (0,5)_XXXXXXXI      (0,6)_XXXXXXXI      ... (0,COMPUTE_HEIGHT-1)_XXXXXXXI  0
     * (2,0)_XXXXXXXI       (2,1)_XXXXXXXI      (2,2)_XXXXXXXI      (2,3)_XXXXXXXI      (2,4)_XXXXXXXI      (2,5)_XXXXXXXI      (2,6)_XXXXXXXI      ... (2,COMPUTE_HEIGHT-1)_XXXXXXXI  0
     * ...
     * (COMPUTE_WIDTH-2,0)_XXXXXXXI       (COMPUTE_WIDTH-2,1)_XXXXXXXI      (COMPUTE_WIDTH-2,2)_XXXXXXXI      (COMPUTE_WIDTH-2,3)_XXXXXXXI      (COMPUTE_WIDTH-2,4)_XXXXXXXI      (COMPUTE_WIDTH-2,5)_XXXXXXXI      (COMPUTE_WIDTH-2,6)_XXXXXXXI      (COMPUTE_WIDTH-2,7)_XXXXXXXI  0 
     *
     * (1,0)_XXXXXXXI       (1,1)_XXXXXXXI      (1,2)_XXXXXXXI      (1,3)_XXXXXXXI      (1,4)_XXXXXXXI      (1,5)_XXXXXXXI      (1,6)_XXXXXXXI      ... (1,COMPUTE_HEIGHT-1)_XXXXXXXI  0
     * (3,0)_XXXXXXXI       (3,1)_XXXXXXXI      (3,2)_XXXXXXXI      (3,3)_XXXXXXXI      (3,4)_XXXXXXXI      (3,5)_XXXXXXXI      (3,6)_XXXXXXXI      ... (3,COMPUTE_HEIGHT-1)_XXXXXXXI  0
     * ...
     * (COMPUTE_WIDTH-1,0)_XXXXXXXI       (COMPUTE_WIDTH-1,1)_XXXXXXXI      (COMPUTE_WIDTH-1,2)_XXXXXXXI      (COMPUTE_WIDTH-1,3)_XXXXXXXI      (COMPUTE_WIDTH-1,4)_XXXXXXXI      (COMPUTE_WIDTH-1,5)_XXXXXXXI      (COMPUTE_WIDTH-1,6)_XXXXXXXI      (COMPUTE_WIDTH-1,7)_XXXXXXXI  0 
     *
     * 
     */
    
    __vector  vOfst;

    __agen AddrOffset= 0;
    vOfst= pOffset[AddrOffset].npt();
    
#define NUM_ITER_WW (ALIGN_8(NUM_WIN_H_ITER*NUM_WIN_W_ITER)/8)

    for(int h=0; h< computeHeight; h++) {
            for (int w=0; w< NUM_ITER_W; w++) {
                for(int ww= 0; ww<NUM_ITER_WW; ww++) { /* Process 8 orientation HGFEDCBA per inner loop for 16 pixels */

                    __agen AddrBitMask= h*NUM_ITER_W*(2*NUM_WIN_W_ITER*NUM_WIN_H_ITER+VCOP_SIMD_WIDTH2)  +  w*(2*NUM_WIN_W_ITER*NUM_WIN_H_ITER+VCOP_SIMD_WIDTH2) + ww*VCOP_SIMD_WIDTH2;
                    __agen AddrOut= h +  w*scratchStride*VCOP_SIMD_WIDTH + ww*computeWidth*scratchStride;

                    __vector v_A_H_0_14, v_A_H_1_15, v_0_14_A_H, v_1_15_A_H;

                    (v_A_H_0_14, v_A_H_1_15)= pScratchBitmask[AddrBitMask].deinterleave(); /* Load 8 orientations for 16 pixels 0..14 and 1..15 in IAH */

                    v_0_14_A_H= transpose_bits(v_A_H_0_14);
                    v_1_15_A_H= transpose_bits(v_A_H_1_15);

                    pScratch8[AddrOut].p_scatter(vOfst)= v_0_14_A_H; /* Store in WMEM */
                    (pScratch8 + (ALIGN_SIMD2(computeWidth)/2)*scratchStride)[AddrOut].p_scatter(vOfst)= v_1_15_A_H; /* Store in WMEM */
                }
            }
    }

    /* Transpose previous output:
     * 
     * (0,0)_HGFEDCBA       (0,1)_HGFEDCBA      (0,2)_HGFEDCBA      (0,3)_HGFEDCBA      (0,4)_HGFEDCBA      (0,5)_HGFEDCBA      (0,6)_HGFEDCBA      ...     (0,COMPUTE_HEIGHT-1)_HGFEDCBA  0
     * (2,0)_HGFEDCBA       (2,1)_HGFEDCBA      (2,2)_HGFEDCBA      (2,3)_HGFEDCBA      (2,4)_HGFEDCBA      (2,5)_HGFEDCBA      (2,6)_HGFEDCBA      ...     (2,COMPUTE_HEIGHT-1)_HGFEDCBA  0
     * ...
     * (COMPUTE_WIDTH-2,0)_HGFEDCBA       (COMPUTE_WIDTH-2,1)_HGFEDCBA      (COMPUTE_WIDTH-2,2)_HGFEDCBA      (COMPUTE_WIDTH-2,3)_HGFEDCBA      (COMPUTE_WIDTH-2,4)_HGFEDCBA      (COMPUTE_WIDTH-2,5)_HGFEDCBA      (COMPUTE_WIDTH-2,6)_HGFEDCBA      ... (COMPUTE_WIDTH-2, COMPUTE_HEIGHT-1)_HGFEDCBA  0
     *
     * (1,0)_HGFEDCBA       (1,1)_HGFEDCBA      (1,2)_HGFEDCBA      (1,3)_HGFEDCBA      (1,4)_HGFEDCBA      (1,5)_HGFEDCBA      (1,6)_HGFEDCBA      ...     (1,COMPUTE_HEIGHT-1)_HGFEDCBA  0
     * (3,0)_HGFEDCBA       (3,1)_HGFEDCBA      (3,2)_HGFEDCBA      (3,3)_HGFEDCBA      (3,4)_HGFEDCBA      (3,5)_HGFEDCBA      (3,6)_HGFEDCBA      ...     (3,COMPUTE_HEIGHT-1)_HGFEDCBA  0
     * ...
     * (COMPUTE_WIDTH-1,0)_HGFEDCBA       (COMPUTE_WIDTH-1,1)_HGFEDCBA      (COMPUTE_WIDTH-1,2)_HGFEDCBA      (COMPUTE_WIDTH-1,3)_HGFEDCBA      (COMPUTE_WIDTH-1,4)_HGFEDCBA      (COMPUTE_WIDTH-1,5)_HGFEDCBA      (COMPUTE_WIDTH-1,6)_HGFEDCBA      ...   (COMPUTE_WIDTH-1,COMPUTE_HEIGHT-1)_HGFEDCBA  0
     *
     * (0,0)_XXXXXXXI       (0,1)_XXXXXXXI      (0,2)_XXXXXXXI      (0,3)_XXXXXXXI      (0,4)_XXXXXXXI      (0,5)_XXXXXXXI      (0,6)_XXXXXXXI      ... (0,COMPUTE_HEIGHT-1)_XXXXXXXI  0
     * (2,0)_XXXXXXXI       (2,1)_XXXXXXXI      (2,2)_XXXXXXXI      (2,3)_XXXXXXXI      (2,4)_XXXXXXXI      (2,5)_XXXXXXXI      (2,6)_XXXXXXXI      ... (2,COMPUTE_HEIGHT-1)_XXXXXXXI  0
     * ...
     * (COMPUTE_WIDTH-2,0)_XXXXXXXI       (COMPUTE_WIDTH-2,1)_XXXXXXXI      (COMPUTE_WIDTH-2,2)_XXXXXXXI      (COMPUTE_WIDTH-2,3)_XXXXXXXI      (COMPUTE_WIDTH-2,4)_XXXXXXXI      (COMPUTE_WIDTH-2,5)_XXXXXXXI      (COMPUTE_WIDTH-2,6)_XXXXXXXI      (COMPUTE_WIDTH-2,7)_XXXXXXXI  0 
     *
     * (1,0)_XXXXXXXI       (1,1)_XXXXXXXI      (1,2)_XXXXXXXI      (1,3)_XXXXXXXI      (1,4)_XXXXXXXI      (1,5)_XXXXXXXI      (1,6)_XXXXXXXI      ... (1,COMPUTE_HEIGHT-1)_XXXXXXXI  0
     * (3,0)_XXXXXXXI       (3,1)_XXXXXXXI      (3,2)_XXXXXXXI      (3,3)_XXXXXXXI      (3,4)_XXXXXXXI      (3,5)_XXXXXXXI      (3,6)_XXXXXXXI      ... (3,COMPUTE_HEIGHT-1)_XXXXXXXI  0
     * ...
     * (COMPUTE_WIDTH-1,0)_XXXXXXXI       (COMPUTE_WIDTH-1,1)_XXXXXXXI      (COMPUTE_WIDTH-1,2)_XXXXXXXI      (COMPUTE_WIDTH-1,3)_XXXXXXXI      (COMPUTE_WIDTH-1,4)_XXXXXXXI      (COMPUTE_WIDTH-1,5)_XXXXXXXI      (COMPUTE_WIDTH-1,6)_XXXXXXXI      (COMPUTE_WIDTH-1,7)_XXXXXXXI  0 
     *
     * to:
     * (0,0)_HGFEDCBA       (0,0)_XXXXXXXI      (1,0)_HGFEDCBA      (1,0)_XXXXXXXI      (2,0)_HGFEDCBA      (2,0)_XXXXXXXI      ...                 COMPUTE_WIDTH-1,0)_HGFEDCBA     (COMPUTE_WIDTH-1,0)_XXXXXXXI
     * (0,1)_HGFEDCBA       (0,1)_XXXXXXXI      (1,1)_HGFEDCBA      (1,1)_XXXXXXXI      (2,1)_HGFEDCBA      (2,1)_XXXXXXXI      ...                 COMPUTE_WIDTH-1,1)_HGFEDCBA     (COMPUTE_WIDTH-1,1)_XXXXXXXI
     * (0,2)_HGFEDCBA       (0,2)_XXXXXXXI      (1,2)_HGFEDCBA      (1,2)_XXXXXXXI      (2,2)_HGFEDCBA      (2,2)_XXXXXXXI      ...                 COMPUTE_WIDTH-1,2)_HGFEDCBA     (COMPUTE_WIDTH-1,2)_XXXXXXXI
     * ...
     * (0,COMPUTE_HEIGHT-1)_HGFEDCBA       (0,COMPUTE_HEIGHT-1)_XXXXXXXI      (1,COMPUTE_HEIGHT-1)_HGFEDCBA      (1,COMPUTE_HEIGHT-1)_XXXXXXXI      (2,COMPUTE_HEIGHT-1)_HGFEDCBA      (2,COMPUTE_HEIGHT-1)_XXXXXXXI      ...                 COMPUTE_WIDTH-1,COMPUTE_HEIGHT-1)_HGFEDCBA     (COMPUTE_WIDTH-1,COMPUTE_HEIGHT-1)_XXXXXXXI
     * 
     * and apply mask such that (X,Y)_XXXXXXXI becomes (X,Y)_0000000I
     * 
     *  2*ALIGN_8(NUM_WIN_W_ITER * winHeight) / (8*16) cycles per pixel
     */
    vOfst= (pOffset+16)[AddrOffset].npt();

    for(int h=0; h< ALIGN_SIMD(computeHeight)/VCOP_SIMD_WIDTH; h++) {
        
        __vector vRowMask;
        __agen AddrRowMask= h;
        vRowMask= pRowMask[AddrRowMask].nbits();
        
        for (int w=0; w< ALIGN_2(computeWidth)/2; w++) {
            for(int ww= 0; ww<NUM_ITER_WW; ww++) { /* Process 8 orientation HGFEDCBA per inner loop for 16 pixels */

                __agen AddrIn= h*VCOP_SIMD_WIDTH +  w*scratchStride +  ww*computeWidth*scratchStride;
                __agen AddrOut= h*VCOP_SIMD_WIDTH*outStride*sizeof(*pOut) +  w*2*NUM_ITER_WW + ww;
                __agen AddrMask= ww;

                __vector v_0_0_7_A_H, v_1_0_7_A_H, vMask_0_7_A_H;

                v_0_0_7_A_H= pScratch8[AddrIn].npt(); /* Load 8 codewords in WMEM, 64 bits */
                v_1_0_7_A_H= (pScratch8+(ALIGN_SIMD2(computeWidth)/2)*scratchStride)[AddrIn].npt(); /* Load 8 codewords from next row in WMEM, 64 bits */
                vMask_0_7_A_H= pCodeWordMask[AddrMask].onept(); /* Load mask from WMEM */

                v_0_0_7_A_H= v_0_0_7_A_H & vMask_0_7_A_H;
                v_1_0_7_A_H= v_1_0_7_A_H & vMask_0_7_A_H;

                pOut[AddrOut].p_scatter(vOfst)= v_0_0_7_A_H.predicate(vRowMask); /* Store in IAL */
                (pOut + NUM_ITER_WW)[AddrOut].p_scatter(vOfst)= v_1_0_7_A_H.predicate(vRowMask); /* Store in IAL */
            }
        }
    }

}
