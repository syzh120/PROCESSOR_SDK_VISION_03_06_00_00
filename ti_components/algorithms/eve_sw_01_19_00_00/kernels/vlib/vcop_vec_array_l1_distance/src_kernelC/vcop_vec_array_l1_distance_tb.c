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


#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#include "vcop.h"

#include "test_profile.h"


#if VCOP_HOST_EMULATION
  #include "vcop_vec_array_l1_distance_kernel.k"    // kernel source
#else
  void vcop_vec_array_l1_distance
  (
      __vptr_int16    a,
      __vptr_int16    b,
      __vptr_uint32   c,
        int           array_len
  );
  #endif

#define array_len  (64)

#pragma DATA_SECTION(A, "Adata");
short A[64] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,  
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,  
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,  
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F 
};

#pragma DATA_SECTION(B, "Bdata");
short B[64] =
{
          0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,  
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,  
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,  
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 
    0x40 
};

#pragma DATA_SECTION(C, "Cdata");
unsigned int C[16];

#pragma DATA_SECTION(Cout, "EOutdata");
unsigned int Cout[16]={4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};

#pragma DATA_SECTION(profile_array, "Cdata");
unsigned int profile_array[2]; 

int main()
{
    int fail,i;
#ifdef REPORT
#ifdef SCTM
unsigned int sctm_t1, sctm_t2, exec_diff;
unsigned int overflow;
#endif
FILE* fpReport = fopen("../../../report.csv","a+");
#endif

    memset(C,0,16*4);
    
    #if VCOP_HOST_EMULATION
    #else
    unsigned int t0, t1;
    _tsc_start();
    #endif
    
    
   for (i = 0; i < 2; i++)
   {    
    #if VCOP_HOST_EMULATION
    #else
    t0 = _tsc_gettime();
    #endif     
    
    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/
#ifdef REPORT
#ifdef SCTM
EVE_SCTM_Enable(CTM);
EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif
    
    vcop_vec_array_l1_distance(A, B , C, array_len);
	
#ifdef REPORT	
#ifdef SCTM
sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
assert(overflow!=1);

exec_diff = sctm_t2 - sctm_t1;	
EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);	
#endif			
#endif

    #if VCOP_HOST_EMULATION
    #else
    t1 = _tsc_gettime();
    profile_array[i]  = (t1 - t0);
    #endif  

       
   }      

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/

    fail = memcmp (C, Cout, 16*4);

    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/
#ifdef REPORT
fprintf(fpReport,"vcop_vcop_vec_array_l1_distance,");
fprintf(fpReport,"%d,",array_len);
fprintf(fpReport,"%d,",1);
fprintf(fpReport,"%d,",array_len);
fprintf(fpReport,"%d,",1);
fprintf(fpReport,"%d,",1);
#endif
    if (fail) 
    {
#ifdef CONSOLE
        for(i=0;i<16;i++)
           printf ("C:%d, Cout:%d\n", 
                     C[i], Cout[i]
                  );
#endif
#ifdef REPORT
fprintf(fpReport,"FAIL,");
#endif
    }
    else{
#ifdef CONSOLE
	printf ("Pass \n");
#endif
#ifdef REPORT
fprintf(fpReport,"PASS,");
#endif
	}
    
   #if VCOP_HOST_EMULATION
   #else
 #ifdef CONSOLE
    for (i = 0; i < 2; i++)
   printf ("Time taken: %d cycles \n", profile_array[i]);
 #endif
   #endif 
   
#ifdef REPORT		
#ifdef SCTM
fprintf(fpReport,"%d\n",exec_diff);
#endif
if(fpReport){
fclose(fpReport);
}
#endif		
   
}

/* ======================================================================== */
/*  End of file:  vcop_vec_array_l1_distance.c                              */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
