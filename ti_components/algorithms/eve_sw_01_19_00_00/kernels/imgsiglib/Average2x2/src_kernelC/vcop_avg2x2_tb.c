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



#include <stdio.h>
#include <math.h>
#include <vcop.h>

#include "test_profile.h"

typedef unsigned char  Uint8;
typedef unsigned short Uint16;
typedef unsigned int   Uint32;

typedef char    Int8;
typedef short   Int16;
typedef int     Int32;

#define   IN_W        20
#define   IN_H        20

#define   BLK_W       16
#define   BLK_H       16
#define   OUT_W       16        // OUT_W >= 2 AND a multiple of 8
#define   OUT_H       16

#define   COMP_OFFSET  (2)      // offset where compute block starts

#define   N0           (IN_W  * IN_H )
#define   N1           (OUT_W * OUT_H )

#define   INPUT_TYPE        0   // 0 - uchar, 1 - char, 2 - ushort, 3 - short 
#define   OUTPUT_TYPE       0   // 0 - char, 1 - short, 2 - word


#pragma DATA_SECTION(in_data, "Adata");
Uint8 in_data[N0] =
{ 
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
    0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01
};

#pragma DATA_SECTION(ref, "EOutdata");
Uint8 ref[N1] = 
{ 
  0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
  1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
};
  
#pragma DATA_SECTION(out, "Bdata");
Int16 out[BLK_W * BLK_H] = {0};

#if VCOP_HOST_EMULATION
  #include "vcop_avg2x2_kernel.k"    // kernel source
#else
  #include "../inc/vcop_avg2x2_kernel.h"    // translated kernel
#endif


int main()
{
    int  i, j;
    int  col_ofst, row_ofst;    
    int  SHIFT;
    unsigned char *in_ptr;
    int ok;
#ifdef REPORT
FILE* fpReport = fopen("../../../report.csv","a+");
#ifdef SCTM
unsigned int sctm_t1, sctm_t2, exec_diff;
unsigned int overflow;
EVE_SCTM_Enable(CTM);
EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
#endif
#endif   
      
    
    SHIFT = (log10(2 * 2)/log10(2));

    /*-------------------------------------------------------------------*/
    /* Here we add the columns incrementally and write out data in a 1-D */
    /* fashion.                                                          */
    /*-------------------------------------------------------------------*/

    col_ofst = (COMP_OFFSET) % IN_W;
    row_ofst = (COMP_OFFSET) / IN_W;    
#ifdef CONSOLE
    printf("Row offset = %d, Col offset = %d\n", row_ofst, col_ofst);
#endif
	

    /*-------------------------------------------------------------------*/
    /* Actual filtering operation happens here as part of the test bench */
    /* and the results are written out so as to be compared with EVE     */
    /* results.                                                          */
    /*-------------------------------------------------------------------*/

    in_ptr =  &in_data[ col_ofst + (row_ofst * IN_W)];
#ifdef REPORT
#ifdef SCTM
sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif   
    if ( INPUT_TYPE == 0)
    {
        vcop_avg2x2_uchar
        ( 
            (Uint8 *)&in_data[ col_ofst + (row_ofst * IN_W)],  
            out,
            IN_W, 
            OUT_W,
            BLK_W,
            BLK_H,
            SHIFT,
            INPUT_TYPE,
            OUTPUT_TYPE
        ); 
    }

    if ( INPUT_TYPE == 1)
    {
        vcop_avg2x2_char
        ( 
            (Int8 *) &in_data[ col_ofst + (row_ofst * IN_W)],  
            out,
            IN_W, 
            OUT_W,
            BLK_W,
            BLK_H,
            SHIFT,
            INPUT_TYPE,
            OUTPUT_TYPE
        ); 
    }

    if ( INPUT_TYPE == 2)
    {
        vcop_avg2x2_ushort
        ( 
            (Uint16 *) &in_data[ col_ofst + (row_ofst * IN_W)],  
            out,
            IN_W, 
            OUT_W,
            BLK_W,
            BLK_H,
            SHIFT,
            INPUT_TYPE,
            OUTPUT_TYPE
        ); 
    }

    if ( INPUT_TYPE == 3)
    {
        vcop_avg2x2_short
        ( 
            (Int16 *) &in_data[ col_ofst + (row_ofst * IN_W)],  
            out,
            IN_W, 
            OUT_W,
            BLK_W,
            BLK_H,
            SHIFT,
            INPUT_TYPE,
            OUTPUT_TYPE
        ); 
    }
#ifdef REPORT	
#ifdef SCTM
sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
		overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
		assert(overflow!=1);

exec_diff = sctm_t2 - sctm_t1;		
EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
#endif			
#endif
#ifdef REPORT
fprintf(fpReport,"vcop_avg2x2,");
fprintf(fpReport,"%d,",IN_W);
fprintf(fpReport,"%d,",IN_H);
fprintf(fpReport,"%d,",BLK_W);
fprintf(fpReport,"%d,",BLK_H);
fprintf(fpReport,"1,");
#endif	   
    /*-------------------------------------------------------------------*/
    /* Print out the results here.                                       */
    /*-------------------------------------------------------------------*/

#ifdef CONSOLE	
    printf("\n INPUT BLOCK \n\n");
   for ( j = 0; j < BLK_H; j++)
   {
       for ( i = 0; i < BLK_W; i++)
       {
           printf("%3d", (in_ptr[ j * IN_W + i ] ));
       }  
       printf("\n");
   }

   printf("\n  OUTPUT DATA \n\n");
   for ( j = 0; j < BLK_H; j++)
   {
       for ( i = 0; i < BLK_W; i++)
       {
           printf("%3d, ", (out[ (j * BLK_W) + i ] ));
       }  
       printf("\n");
   }

   printf("\n");
   printf("\n");
#endif
   ok = 1;
   
   for ( j = 0; j < BLK_H; j++)
   {
       for ( i = 0; i < BLK_W; i++)
       {        
           if ( out[(j * BLK_W) + i] != ref[(j * BLK_W) + i] )
           {
#ifdef CONSOLE		   
               printf("ERROR out = %d, ref = %d,  *\n", out[(j * BLK_W) + i], ref[(j * BLK_W) + i]);
#endif			   
               ok = 0;
           }      
       } 
   }

#ifdef CONSOLE   
   if (ok)
       printf(" \n\n ***** AVERAGE 2x2-- Kernel-C -code: PASSED! *****\n\n");
   else
       printf(" \n\n ***** AVERAGE 2x2-- FAIL! ****\n\n");
#endif	   
   
#ifdef REPORT   
if(ok){
fprintf(fpReport,"PASS,");
}
else{
fprintf(fpReport,"FAIL,");
}
#ifdef SCTM
fprintf(fpReport,"%d\n",exec_diff);
#endif
if(fpReport){
fclose(fpReport);
}
#endif

return 0;
}



