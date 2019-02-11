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


/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if (VCOP_HOST_EMULATION)
#include "vcop.h"
#endif

#define   VCOP_SIMD_WIDTH    8

#define   ELEMSZ_IN          sizeof(*in_ptr)
#define   VECTORSZ_IN        (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define   ELEMSZ_INTER       sizeof(*B0_ptr)
#define   VECTORSZ_INTER     (VCOP_SIMD_WIDTH * ELEMSZ_INTER)

#define   ELEMSZ_OUT         sizeof(*out_ptr)
#define   VECTORSZ_OUT       (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define   TRANSPOSE_WIDTH    8

#define   BYTES_IN_HALF_WD   2
#define   BYTES_IN_WORD      4

#define   TWOSIXTY           260 

// #define __PRINT__            1

void eve_integral_image_reset_accv(
        __vptr_uint32   acc_v_ptr,
        unsigned int blk_h){

    for(int i = 0; i < blk_h; i++)
    {
        __vector vZero;
        __agen Addr0=  i*sizeof(*acc_v_ptr);
        vZero= 0;

        acc_v_ptr[Addr0].onept() = vZero;
    }

}

void eve_integral_image_reset_acch(
        __vptr_uint32   acc_h_ptr,
        unsigned int blk_w){

    for(int i = 0; i < blk_w/VCOP_SIMD_WIDTH; i++)
    {
        __vector vZero;
        __agen Addr0=  i*VCOP_SIMD_WIDTH*sizeof(*acc_h_ptr);
        vZero= 0;

        acc_h_ptr[Addr0].npt() = vZero;
    }

}

/*-------------------------------------------------------------*/
/* For input type of 'char' or 'uchar', we call the function   */
/* eve_integral_image_u8_int_int().                          */
/*-------------------------------------------------------------*/

void eve_integral_image_u8_int_int
(
    unsigned int    blk_w,      // II core kernel height            
    unsigned int    blk_h,      // II core kernel width             
    unsigned int    in_width,   // Width (or pitch) of the input image.                 
    __vptr_uint32   acc_h_ptr,  // Pointer to an horz accumulator 1-D array of type int.
    __vptr_uint32   acc_v_ptr,  // Pointer to an vert accumulator 1-D array of type int.
    __vptr_uint8    in_ptr,     // Pointer to an input array of type char.              
    __vptr_uint32   B0_ptr,     // Pointer to an even intermediate array of type int.   
    __vptr_uint32   B1_ptr,     // Pointer to an odd intermediate array of type int.    
    __vptr_uint32   C0_ptr,     // Pointer to an even output array of type int.         
    __vptr_uint32   C1_ptr,     // Pointer to an odd output array of type int.          
    __vptr_uint32   out_ptr,     // Pointer to interleaved output array of type int.     
    __vptr_uint32   out_acc_h_ptr  // Pointer to an horz accumulator 1-D array of type int.
)
{

  __vector Vin_even, Vin_odd, Vin_B0, Vin_B1, V_C0, Vin_a, Vin_b;
  __vector Vacc_h_even, Vacc_h_odd, Vacc_v;

    /*-------------------------------------------------------------------*/
    /* First we add row-wise and write out the result in transposed form.*/
    /* The data is also read in 'deinterleave' format, so we have two    */
    /* separate blocks of even and odd results. Even results are stored  */
    /* in the intermediate array B0, odd results are stored in B1.       */
    /* Cycle count for this loop should be 1/16                          */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < blk_w/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        __agen accAddr;

        accAddr  = I1 * (2 * VCOP_SIMD_WIDTH) * ELEMSZ_OUT;

        Vacc_h_even = acc_h_ptr[accAddr];
        Vacc_h_odd = (acc_h_ptr + 32)[accAddr];
        
        for (int I2 = 0; I2 < blk_h/TRANSPOSE_WIDTH; I2++ )
        {
            for ( int I3 = 0; I3 < TRANSPOSE_WIDTH; I3++)
            {
                __agen dataAddr;
                __agen outAddr;
        
                
                 dataAddr = (I3 * in_width * ELEMSZ_IN) + 
                            (I2 * in_width * TRANSPOSE_WIDTH * ELEMSZ_IN) + 
                            (I1 * VECTORSZ_IN * 2);
        
                outAddr  = (I3 * ELEMSZ_INTER) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_INTER) +
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_INTER);
        
                (Vin_even, Vin_odd)  =  in_ptr[dataAddr].deinterleave();  

                Vacc_h_even = Vacc_h_even + Vin_even;   
                Vacc_h_odd = Vacc_h_odd + Vin_odd;   
                    
#ifdef __PRINT__

                Vacc_h_even.printx();
                printf("\n");
                Vacc_h_odd.printx();
#endif

                B0_ptr[outAddr].offset_np1() = Vacc_h_even;
                B1_ptr[outAddr].offset_np1() = Vacc_h_odd;               

           }
       }

       //acc_h_ptr[accAddr] = Vacc_h_even;
       //(acc_h_ptr + 32)[accAddr] = Vacc_h_odd;
       
       out_acc_h_ptr[accAddr] = Vacc_h_even;
       (out_acc_h_ptr + 32)[accAddr] = Vacc_h_odd;

       

    }

    /*-------------------------------------------------------------------*/
    /* Now, we add the transposed array in the row-wise direction again. */
    /* Here, we consider inter_w = blk_h, inter_h = blk_w, as the        */
    /* original array dimensions are switched.                           */
    /* Cycle count for this loop should be 1/8                           */
    /*-------------------------------------------------------------------*/

#ifdef __PRINT__
    printf("\n\n 2nd loop \n\n");
#endif

    for (int I1 = 0; I1 < blk_w/( 2 * VCOP_SIMD_WIDTH); I1++)
    {
        
        for (int I2 = 0; I2 < blk_h/TRANSPOSE_WIDTH; I2++ )
        { 
        
            __agen accAddr;
            
            accAddr  = I2 * TRANSPOSE_WIDTH *  ELEMSZ_INTER;

            Vacc_v   = acc_v_ptr[accAddr].npt();

            for ( int I3 = 0; I3 < TRANSPOSE_WIDTH; I3++)
            {
                __agen dataAddr;
                __agen outAddr;
          
                dataAddr = (I3 * (TRANSPOSE_WIDTH + 1) * ELEMSZ_INTER) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_INTER) + 
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_INTER) ;

                outAddr =  (I3 * ELEMSZ_OUT) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_OUT) + 
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_OUT) ;

                Vin_B0  =  B0_ptr[dataAddr].npt();  
                Vin_B1  =  B1_ptr[dataAddr].npt();  

                V_C0     = Vacc_v + Vin_B0;   
                Vacc_v  += Vin_B0 + Vin_B1;  

#ifdef __PRINT__
                V_C0.printx();
                Vacc_v.printx();
#endif

                C0_ptr[outAddr].offset_np1() = V_C0;
                C1_ptr[outAddr].offset_np1() = Vacc_v;

            } 
      
           acc_v_ptr[accAddr] = Vacc_v;

      }

    }


    /*-------------------------------------------------------------------*/
    /* This is the third VLOOP, where we 'interleave' the two output     */
    /* buffers to get back or correct output block. We also reformat the */
    /* data by removing the 9th word, inserted as part of the transpose  */
    /* store feature.                                                    */
    /* Estimated cycle count 2/16                                        */
    /*-------------------------------------------------------------------*/

#ifdef __PRINT__
     printf("\n\nThird loop\n\n");
#endif

    for (int I1 = 0; I1 <  blk_w/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        for (int I2 = 0; I2 < blk_h; I2++)
        {
            __agen dataAddr, outAddr;
                 
            dataAddr = (I1 * blk_h * (TRANSPOSE_WIDTH + 1) * ELEMSZ_OUT) + (I2 * (TRANSPOSE_WIDTH + 1) * ELEMSZ_OUT);
            outAddr  = (I2 * in_width * ELEMSZ_OUT) +  (I1 * 2 * VECTORSZ_OUT);
            
            Vin_a = C0_ptr[dataAddr];
            Vin_b = C1_ptr[dataAddr];

#ifdef __PRINT__           
            Vin_a.printx();
            Vin_b.printx();
#endif
            (Vin_a, Vin_b).interleave();
            
            out_ptr[outAddr] = Vin_a;
            (out_ptr + (8 * 4))[outAddr] = Vin_b;
            
        }
    }  
}


/*-----------------------------------------------------------------------*/
/* For input type of 'short' or 'ushort', we call the function           */
/* eve_integral_image_short_int_int().                                   */
/*-----------------------------------------------------------------------*/

void eve_integral_image_u16_int_int
(
    unsigned int    blk_w,
    unsigned int    blk_h,
    unsigned int    in_width,
    __vptr_uint32   acc_h_ptr,
    __vptr_uint32   acc_v_ptr,
    __vptr_uint16   in_ptr,
    __vptr_uint32   B0_ptr,
    __vptr_uint32   B1_ptr,
    __vptr_uint32   C0_ptr,
    __vptr_uint32   C1_ptr,
    __vptr_uint32   out_ptr
)
{

  __vector Vin_even, Vin_odd, Vin_B0, Vin_B1, V_C0, Vin_a, Vin_b;
  __vector Vacc_h_even, Vacc_h_odd, Vacc_v;


    /*-------------------------------------------------------------------*/
    /* First we add row-wise and write out the result in transposed form.*/
    /* The data is also read in 'deinterleave' format, so we have two    */
    /* separate blocks of even and odd results. Even results are stored  */
    /* in the intermediate array B0, odd results are stored in B1.       */
    /* Cycle count for this loop should be 1/16                          */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < blk_w/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        __agen accAddr;
        
        accAddr  = I1 * (2 * VCOP_SIMD_WIDTH) * ELEMSZ_OUT;
        Vacc_h_even = acc_h_ptr[accAddr];
        Vacc_h_odd = (acc_h_ptr + 32)[accAddr];
        
        for (int I2 = 0; I2 < blk_h/TRANSPOSE_WIDTH; I2++ )
        {
            for ( int I3 = 0; I3 < TRANSPOSE_WIDTH; I3++)
            {
                __agen dataAddr;
                __agen outAddr;
        
                
                 dataAddr = (I3 * in_width * ELEMSZ_IN) + 
                            (I2 * in_width * TRANSPOSE_WIDTH * ELEMSZ_IN) + 
                            (I1 * VECTORSZ_IN * 2);
        
                outAddr  = (I3 * ELEMSZ_INTER) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_INTER) +
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_INTER);
        
                (Vin_even, Vin_odd)  =  in_ptr[dataAddr].deinterleave();  

                Vacc_h_even = Vacc_h_even + Vin_even;   
                Vacc_h_odd = Vacc_h_odd + Vin_odd;   
                    
#ifdef __PRINT__

                Vacc_h_even.printx();
                printf("\n");
                Vacc_h_odd.printx();
#endif

                B0_ptr[outAddr].offset_np1() = Vacc_h_even;
                B1_ptr[outAddr].offset_np1() = Vacc_h_odd;
                 

           }
       }

       acc_h_ptr[accAddr] = Vacc_h_even;
       (acc_h_ptr + 32)[accAddr] = Vacc_h_odd;

    }

    /*-------------------------------------------------------------------*/
    /* Now, we add the transposed array in the row-wise direction again. */
    /* Here, we consider inter_w = blk_h, inter_h = blk_w, as the        */
    /* original array dimensions are switched.                           */
    /* Cycle count for this loop should be 1/8                           */
    /*-------------------------------------------------------------------*/

#ifdef __PRINT__
    printf("\n\n 2nd loop \n\n");
#endif

    for (int I1 = 0; I1 < blk_w/( 2 * VCOP_SIMD_WIDTH); I1++)
    {
        
        for (int I2 = 0; I2 < blk_h/TRANSPOSE_WIDTH; I2++ )
        { 
        
            __agen accAddr;
            
            accAddr  = I2 * TRANSPOSE_WIDTH *  ELEMSZ_INTER;

            Vacc_v   = acc_v_ptr[accAddr].npt();

            for ( int I3 = 0; I3 < TRANSPOSE_WIDTH; I3++)
            {
                __agen dataAddr;
                __agen outAddr;
          
                dataAddr = (I3 * (TRANSPOSE_WIDTH + 1) * ELEMSZ_INTER) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_INTER) + 
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_INTER) ;

                outAddr =  (I3 * ELEMSZ_OUT) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_OUT) + 
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_OUT) ;

                Vin_B0  =  B0_ptr[dataAddr].npt();  
                Vin_B1  =  B1_ptr[dataAddr].npt();  

                V_C0     = Vacc_v + Vin_B0;   
                Vacc_v  += Vin_B0 + Vin_B1;  

#ifdef __PRINT__
                V_C0.printx();
                Vacc_v.printx();
#endif

                C0_ptr[outAddr].offset_np1() = V_C0;
                C1_ptr[outAddr].offset_np1() = Vacc_v;

            } 
      
           acc_v_ptr[accAddr] = Vacc_v;

      }

    }


    /*-------------------------------------------------------------------*/
    /* This is the third VLOOP, where we 'interleave' the two output     */
    /* buffers to get back or correct output block. We also reformat the */
    /* data by removing the 9th word, inserted as part of the transpose  */
    /* store feature.                                                    */
    /* Estimated cycle count 2/16                                        */
    /*-------------------------------------------------------------------*/

#ifdef __PRINT__
     printf("\n\nThird loop\n\n");
#endif

    for (int I1 = 0; I1 <  blk_w/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        for (int I2 = 0; I2 < blk_h; I2++)
        {
            __agen dataAddr, outAddr;
                 
            dataAddr = (I1 * blk_h * (TRANSPOSE_WIDTH + 1) * ELEMSZ_OUT) + (I2 * (TRANSPOSE_WIDTH + 1) * ELEMSZ_OUT);
            outAddr  = (I2 * in_width * ELEMSZ_OUT) +  (I1 * 2 * VECTORSZ_OUT);
            
            Vin_a = C0_ptr[dataAddr];
            Vin_b = C1_ptr[dataAddr];

#ifdef __PRINT__           
            Vin_a.printx();
            Vin_b.printx();
#endif
            (Vin_a, Vin_b).interleave();
            
            out_ptr[outAddr] = Vin_a;
            (out_ptr + (8 * 4))[outAddr] = Vin_b;
            
        }
    }  
}

/* ======================================================================== */
/*  End of file:  eve_integral_image_kernel.k                               */
/*--------------------------------------------------------------------------*/
/*          Copyright (C) 2002 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
