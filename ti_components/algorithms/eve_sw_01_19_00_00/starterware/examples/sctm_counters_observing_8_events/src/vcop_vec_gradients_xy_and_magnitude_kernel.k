/*
*
* Copyright (c) 2010-2017 Texas Instruments Incorporated
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

/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */ 
/*                      All Rights Reserved                                 */ 
/*==========================================================================*/ 

#define ELEMSZ          sizeof(*pIn)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_vec_gradients_xy_and_magnitude
(                                                                    
    __vptr_uint8   pIn,                                               
    __vptr_int16   pGradX,
    __vptr_int16   pGradY,
    __vptr_int16   pMag,  
    unsigned short width,                                                       
    unsigned short height                                                       
)
{
    __vector VinT1,VinT2;               //Top pixel 
    __vector VinL1,VinL2;               //Left pixel
    __vector VinR1,VinR2;               //Right pixel 
    __vector VinB1,VinB2;               //Bottom pixel 
    __vector VgX_1,VgX_2;               //Gx 
    __vector VgY_1,VgY_2;               //Gy 
    __vector Vabs_gX_1,Vabs_gX_2;       //abs of Gx
    __vector Vabs_gY_1,Vabs_gY_2;       //abs of Gy
    __vector Vmag1,Vmag2, Z;               //Mag
    
    Z = 0;
   
    for (int I1 = 0; I1 < width*height/(2*VCOP_SIMD_WIDTH); I1++)
    {
        __agen Addr1,Addr2;
        
        Addr1 = I1*VECTORSZ*2;
        Addr2 = I1*VECTORSZ*4;
                                        
        (VinT1,VinT2) = (pIn+1)        [Addr1].deinterleave();                  
        (VinL1,VinL2) = (pIn+width)    [Addr1].deinterleave();                
        (VinR1,VinR2) = (pIn+width+2)  [Addr1].deinterleave();        
        (VinB1,VinB2) = (pIn+2*width+1)[Addr1].deinterleave();     
        
        VgX_1 = VinR1 - VinL1; 
        VgY_1 = VinB1 - VinT1; 
        
        VgX_2 = VinR2 - VinL2; 
        VgY_2 = VinB2 - VinT2; 
        
        Vmag1 = abs(VgX_1);
        Vmag2 = abs(VgX_2);
        
        Vmag1 += abs(VgY_1 - Z);
        Vmag2 += abs(VgY_2 - Z);
        
        pGradX[Addr2].interleave() = (VgX_1,VgX_2);
        pGradY[Addr2].interleave() = (VgY_1,VgY_2);
        pMag[Addr2].interleave()   = (Vmag1,Vmag2);
    }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_gradients_xy_and_magnitude_kernel.k              */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


