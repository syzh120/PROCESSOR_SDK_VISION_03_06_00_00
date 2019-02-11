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
#include <vcop.h>

#include "test_profile.h"

typedef unsigned char  Uint8;
typedef unsigned short Uint16;
typedef unsigned int   Uint32;

typedef char    Int8;
typedef short   Int16;
typedef int     Int32;


/*-----------------------------------------------------------------------*/
/* Complete image size for correct block placement                       */
/*-----------------------------------------------------------------------*/

#define   IN_W             (16)
#define   IN_H             (12)

/*-----------------------------------------------------------------------*/
/* Coefficients of 2D filter                                             */
/*-----------------------------------------------------------------------*/

#define   COEF_W           (5)      
#define   COEF_H           (5)

/*-----------------------------------------------------------------------*/
/* Block of interest over which we are filtering.                        */
/*-----------------------------------------------------------------------*/
#define   OUT_W            (16)
#define   OUT_H            (8)

/*-----------------------------------------------------------------------*/
/* Block of interest over which we are filtering.                        */
/*-----------------------------------------------------------------------*/
#define   COMP_W           (16)   // multiple of 8
#define   COMP_H           (8)

#define   DOWNSAMPLE_HORZ  (2)
#define   DOWNSAMPLE_VERT  (2)

#define   RND_SAT          (18)

#define   N0                (IN_W * IN_H )
#define   N1                (COEF_W * COEF_H)
#define   Nout              (OUT_W * OUT_H)
#define   N_o_inter         ((COMP_W * DOWNSAMPLE_HORZ) * COMP_H)

#define   INPUT_TYPE        2   // 0 - uchar, 1 - char, 2 - ushort, 3 - short 
#define   COEF_TYPE         2   // 0 - uchar, 1 - char, 2 - ushort, 3 - short
#define   OUTPUT_TYPE       1   // 0 - char, 1 - short, 2 - word

#pragma DATA_SECTION(in_data, "Adata");
Uint16 in_data[N0] =
 {    
    0x0ca8, 0x0e8b, 0x0b39, 0x071b, 0x0507, 0x04ec, 0x0b95, 0x064d, 0x0f32, 0x0731, 0x0b3a, 0x0332, 0x049e, 0x0ac3, 0x09f0, 0x0a2f,
    0x0d0a, 0x098a, 0x0179, 0x09ee, 0x09bb, 0x0695, 0x0481, 0x0855, 0x08ed, 0x02c1, 0x0d90, 0x00ca, 0x0e38, 0x0f53, 0x08f6, 0x02b9,
    0x0ab8, 0x0543, 0x06cc, 0x0f3a, 0x02cc, 0x0493, 0x0430, 0x0b7d, 0x003a, 0x0f80, 0x0359, 0x0911, 0x01a0, 0x0c43, 0x03e7, 0x08a2,
    0x0336, 0x07a6, 0x0602, 0x0a3d, 0x09ef, 0x064e, 0x0b55, 0x091b, 0x0989, 0x05b1, 0x0748, 0x01f3, 0x010b, 0x0aa8, 0x0d26, 0x09f9,
    0x045e, 0x098e, 0x02a8, 0x03f5, 0x03ef, 0x080c, 0x0c8a, 0x075f, 0x0d0f, 0x00c8, 0x014c, 0x085a, 0x03bf, 0x0218, 0x0436, 0x0af9,
    0x0a05, 0x0295, 0x0d54, 0x05a4, 0x0965, 0x0b8d, 0x0fc7, 0x071f, 0x0fa2, 0x0c15, 0x0d9e, 0x01df, 0x0eed, 0x0186, 0x0c0e, 0x0ad6,
    0x0896, 0x0d45, 0x0d6b, 0x0301, 0x0818, 0x04e6, 0x0792, 0x0167, 0x038c, 0x0e51, 0x08fe, 0x0c51, 0x0102, 0x003c, 0x0a8d, 0x0e07,
    0x00f3, 0x0f4c, 0x0739, 0x07d9, 0x076f, 0x01cb, 0x0e71, 0x0718, 0x0b42, 0x0494, 0x051b, 0x0600, 0x043a, 0x049c, 0x036c, 0x0034,
    0x016c, 0x0987, 0x0f4e, 0x068c, 0x08a9, 0x0717, 0x0737, 0x05dc, 0x085a, 0x0404, 0x05ff, 0x0d2c, 0x0ffe, 0x0d11, 0x09a2, 0x04f7,
    0x0457, 0x0075, 0x025a, 0x076a, 0x0f13, 0x0777, 0x0cdf, 0x04d7, 0x0eed, 0x0eec, 0x0de2, 0x00bf, 0x0364, 0x0fc4, 0x09ad, 0x0c77,
    0x068b, 0x0cfe, 0x0deb, 0x09c6, 0x0577, 0x003c, 0x0d43, 0x0da1, 0x0b69, 0x0218, 0x05f4, 0x0991, 0x07f9, 0x0047, 0x0a8d, 0x04ea,
    0x0795, 0x09c3, 0x0c4f, 0x0123, 0x066d, 0x0a9f, 0x02a9, 0x0c26, 0x03a6, 0x0f0d, 0x012d, 0x0f2f, 0x04a5, 0x0d1c, 0x02ef, 0x0ed3,
};

#pragma DATA_SECTION(fir_coefs, "Bdata");
Uint16 fir_coefs[N1] =
{
    0x0adc, 0x0842, 0x0130, 0x0505, 0x0d3f,
    0x0130, 0x0754, 0x0317, 0x0a36, 0x0eae,
    0x0121, 0x0b40, 0x0612, 0x0fc8, 0x01cf,
    0x0030, 0x0951, 0x046c, 0x080b, 0x0cfe,
    0x03a2, 0x0825, 0x0c55, 0x0f29, 0x0e88,

};

#pragma DATA_SECTION(ref, "Cdata");
Int16 ref[Nout] =
{
/*
// DOWN_SAMPLE_HORZ = 1, DOWN_SAMPLE_VERT = 1
0x0195, 0x0157, 0x0193, 0x0171, 0x01b2, 0x0160, 0x019e, 0x012b, 0x0148, 0x015e, 0x0178, 0x014e, 0x01ac, 0x0184, 0x0166, 0x0186,
0x0191, 0x016a, 0x0199, 0x01c2, 0x01c8, 0x01bf, 0x01b2, 0x017e, 0x0163, 0x0152, 0x016e, 0x016f, 0x01c6, 0x019d, 0x01bc, 0x0191,
0x017e, 0x015b, 0x018f, 0x019f, 0x0169, 0x01c9, 0x0189, 0x0181, 0x0147, 0x0148, 0x013e, 0x0180, 0x0157, 0x01c1, 0x019d, 0x0189,
0x016c, 0x016c, 0x0196, 0x01b0, 0x01ae, 0x01c4, 0x017f, 0x0198, 0x0131, 0x012e, 0x0120, 0x014b, 0x0113, 0x017e, 0x01c8, 0x0199,
0x0191, 0x0196, 0x0199, 0x017f, 0x018e, 0x0191, 0x017a, 0x018e, 0x01be, 0x015f, 0x0163, 0x0185, 0x0150, 0x0135, 0x01a3, 0x0153,
0x019d, 0x01a2, 0x01a8, 0x0190, 0x01a0, 0x0202, 0x01e6, 0x01bb, 0x01b7, 0x017c, 0x01a7, 0x01b0, 0x0168, 0x017c, 0x01ba, 0x01a1,
0x01bf, 0x018a, 0x019d, 0x018b, 0x019e, 0x01cb, 0x0182, 0x0173, 0x015f, 0x017c, 0x0192, 0x018c, 0x012f, 0x0176, 0x01bb, 0x0172,
0x016f, 0x018b, 0x0188, 0x01b4, 0x0183, 0x01ae, 0x0195, 0x01d8, 0x019b, 0x0187, 0x0192, 0x017c, 0x0183, 0x0181, 0x0181, 0x014c,
*/

/*
// DOWN_SAMPLE_HORZ = 1, DOWN_SAMPLE_VERT = 2
0x0195, 0x0157, 0x0193, 0x0171, 0x01b2, 0x0160, 0x019e, 0x012b, 0x0148, 0x015e, 0x0178, 0x014e, 0x01ac, 0x0184, 0x0166, 0x0186,
0x017e, 0x015b, 0x018f, 0x019f, 0x0169, 0x01c9, 0x0189, 0x0181, 0x0147, 0x0148, 0x013e, 0x0180, 0x0157, 0x01c1, 0x019d, 0x0189,
0x0191, 0x0196, 0x0199, 0x017f, 0x018e, 0x0191, 0x017a, 0x018e, 0x01be, 0x015f, 0x0163, 0x0185, 0x0150, 0x0135, 0x01a3, 0x0153,
0x01bf, 0x018a, 0x019d, 0x018b, 0x019e, 0x01cb, 0x0182, 0x0173, 0x015f, 0x017c, 0x0192, 0x018c, 0x012f, 0x0176, 0x01bb, 0x0172,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
*/

// DOWN_SAMPLE_HORZ = 2, DOWN_SAMPLE_VERT = 2

0x0195, 0x0193, 0x01b2, 0x019e, 0x0148, 0x0178, 0x01ac, 0x0166, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x017e, 0x018f, 0x0169, 0x0189, 0x0147, 0x013e, 0x0157, 0x019d, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0191, 0x0199, 0x018e, 0x017a, 0x01be, 0x0163, 0x0150, 0x01a3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x01bf, 0x019d, 0x019e, 0x0182, 0x015f, 0x0192, 0x012f, 0x01bb, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

};

/*-----------------------------------------------------------------------*/
/* This is our intermediate buffer before downsampling horizontally.     */
/*-----------------------------------------------------------------------*/

#pragma DATA_SECTION(out, "Bdata");
Int16 out[N_o_inter] = {0};
  
/*-----------------------------------------------------------------------*/
/* This is our intermediate buffer before downsampling horizontally.     */
/*-----------------------------------------------------------------------*/
#pragma DATA_SECTION(out_final, "Bdata");
Int16 out_final[Nout] = {0};

#if VCOP_HOST_EMULATION
  #include "vcop_filter_kernel.k"    // kernel source
#else
  #include "vcop_filter_kernel.h"    // translated kernel
#endif

int verify_output();
void print_output();

int main()
{
    int i, j, k;
    int ok;

    /*-------------------------------------------------------------------*/
    /* Actual filtering operation happens here as part of the test bench */
    /* and the results are written out so as to be compared with EVE     */
    /* results.                                                          */
    /*-------------------------------------------------------------------*/
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

#ifdef REPORT
#ifdef SCTM
sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif   

    if (( INPUT_TYPE == 2) && (COEF_TYPE == 2) && (OUTPUT_TYPE == 1) )
    {
        vcop_filter_ushort_ushort_short
        ( 
            in_data, 
            fir_coefs, 
            out,
            IN_W,         
            COEF_W,       
            COEF_H,        
            COMP_W,       
            COMP_H,       
            DOWNSAMPLE_VERT,
            DOWNSAMPLE_HORZ,  
            RND_SAT
        ); 
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
fprintf(fpReport,"vcop_filter,");
fprintf(fpReport,"%d,",IN_W);
fprintf(fpReport,"%d,",IN_H);
fprintf(fpReport,"%d,",OUT_W);
fprintf(fpReport,"%d,",OUT_H);
fprintf(fpReport,"1,");
#endif	        
   

        /*---------------------------------------------------------------*/
        /* Here we downsample horizontally                               */
        /*---------------------------------------------------------------*/

        for ( j = 0; j < OUT_H; j++)
        {
            k = 0;
            for ( i = 0; i < OUT_W * DOWNSAMPLE_HORZ; i++)
            {
                if ( !( i % DOWNSAMPLE_HORZ) ) 
                {
                    out_final[j * OUT_W + k] = out[ (j * OUT_W * DOWNSAMPLE_HORZ) + i];
                    k++;
                }
            } 
        }  
    }
#ifdef CONSOLE
    print_output();
#endif	
    ok = verify_output();

#ifdef CONSOLE	
   if (ok)
      printf(" \n\n ***** FILTER-OP Kernel-C Code-- Results verified: PASSED! *****\n\n");

   else
      printf(" \n\n ***** FILTER-OP Kernel-C Code-- FAIL *****\n\n");
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


void print_output()
{
    int i, j;

   printf("\n--- INPUT DATA ---\n");
   for ( j = 0; j < IN_H; j++)
   {
       for ( i = 0; i < IN_W; i++)
       {
           printf("0x%2.4x, ", in_data[j * OUT_W + i]);
       } 
       printf("\n");
   }

   printf("\n--- COEF DATA ---\n");
   for ( j = 0; j < COEF_H; j++)
   {
       for ( i = 0; i < COEF_W; i++)
       {
           printf("0x%2.4x, ", fir_coefs[j * COEF_W + i]);
       } 
       printf("\n");
   }



   printf("\n--- OUTPUT DATA ---\n");
   for ( j = 0; j < OUT_H; j++)
   {
       for ( i = 0; i < OUT_W; i++)
       {
           printf("0x%2.4x, ", out_final[j * OUT_W + i]);
       } 
       printf("\n");
   }

   printf("\n--- REFERENCE DATA ---\n");
   for ( j = 0; j < OUT_H; j++)
   {
       for ( i = 0; i < OUT_W; i++)
       {
           printf("0x%2.4x, ", ref[j * OUT_W + i]);
       } 
       printf("\n");
   }

}

int verify_output()
{
    int i, j, ok;

   ok = 1;
   for ( j = 0; j < OUT_H; j++)
   {
      for ( i = 0; i < OUT_W; i++)
      {
          if ( out_final[j * OUT_W + i] != ref[j * OUT_W + i] )
          {
#ifdef CONSOLE		  
              printf("ERROR out = %d, ref = %d,  *\n", out_final[j * OUT_W + i], ref[j * OUT_W + i]);
#endif			  
              ok = 0;
          }
      } 
   }

   
    return ok;

}




