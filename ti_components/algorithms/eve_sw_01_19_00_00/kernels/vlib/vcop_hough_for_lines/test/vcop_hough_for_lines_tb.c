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
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_hough_for_lines_config.h"
#include <math.h>

#define ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

/* ------------------------------------------------------------------------ */
/*  Include prototypes for "C" implementation of Hough for Lines kernel  */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_hough_for_lines_cn.h"

#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_hough_for_lines_kernel.k"
#else
#include "../inc/vcop_hough_for_lines_kernel.h"
#endif

//#define __DEBUG
#define MAX_THETA_RANGE (360)
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

#define ALIGNED_WIDTH ALIGN_SIMD(MAX_WIDTH)


#define SQRTof2_Q8      (362)
#define max(x,y)         ((x) > (y) ? (x) : (y))


static int16_t sinLutQ8[360]=
{
0, 4, 8, 13, 17, 22, 26, 31,
35, 40, 44, 48, 53, 57, 61, 66,
70, 74, 79, 83, 87, 91, 95, 99,
104, 108, 112, 116, 120, 124, 127, 131,
135, 139, 143, 146, 150, 153, 157, 161,
164, 167, 171, 174, 177, 180, 184, 187,
190, 193, 196, 198, 201, 204, 207, 209,
212, 214, 217, 219, 221, 223, 225, 228,
230, 231, 233, 235, 237, 238, 240, 242,
243, 244, 246, 247, 248, 249, 250, 251,
252, 252, 253, 254, 254, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255,
254, 254, 253, 252, 252, 251, 250, 249,
248, 247, 246, 244, 243, 242, 240, 239,
237, 235, 233, 232, 230, 228, 226, 224,
221, 219, 217, 214, 212, 209, 207, 204,
201, 199, 196, 193, 190, 187, 184, 181,
178, 174, 171, 168, 164, 161, 157, 154,
150, 147, 143, 139, 135, 132, 128, 124,
120, 116, 112, 108, 104, 100, 96, 92,
87, 83, 79, 75, 70, 66, 62, 57,
53, 49, 44, 40, 36, 31, 27, 22,
18, 13, 9, 4, 0, -4, -8, -12,
-17, -21, -26, -30, -35, -39, -44, -48,
-52, -57, -61, -65, -70, -74, -78, -82,
-87, -91, -95, -99, -103, -107, -111, -115,
-119, -123, -127, -131, -135, -139, -142, -146,
-150, -153, -157, -160, -164, -167, -170, -174,
-177, -180, -183, -186, -189, -192, -195, -198,
-201, -204, -206, -209, -211, -214, -216, -219,
-221, -223, -225, -227, -229, -231, -233, -235,
-237, -238, -240, -241, -243, -244, -245, -247,
-248, -249, -250, -251, -252, -252, -253, -254,
-254, -254, -255, -255, -255, -255, -255, -255,
-255, -255, -255, -255, -254, -254, -253, -252,
-252, -251, -250, -249, -248, -247, -246, -245,
-243, -242, -240, -239, -237, -235, -234, -232,
-230, -228, -226, -224, -222, -219, -217, -215,
-212, -210, -207, -204, -202, -199, -196, -193,
-190, -187, -184, -181, -178, -175, -171, -168,
-165, -161, -158, -154, -151, -147, -143, -140,
-136, -132, -128, -124, -120, -116, -112, -108,
-104, -100, -96, -92, -88, -84, -79, -75,
-71, -67, -62, -58, -53, -49, -45, -40,
-36, -31, -27, -23, -18, -14, -9, -5};

static int16_t cosLutQ8[360] =
{256, 255, 255, 255, 255, 255, 254, 254,
253, 252, 252, 251, 250, 249, 248, 247,
246, 244, 243, 242, 240, 239, 237, 235,
233, 232, 230, 228, 226, 223, 221, 219,
217, 214, 212, 209, 207, 204, 201, 199,
196, 193, 190, 187, 184, 181, 177, 174,
171, 168, 164, 161, 157, 154, 150, 146,
143, 139, 135, 131, 128, 124, 120, 116,
112, 108, 104, 100, 96, 91, 87, 83,
79, 75, 70, 66, 62, 57, 53, 49,
44, 40, 35, 31, 26, 22, 18, 13,
9, 4, 0, -4, -8, -13, -17, -22,
-26, -30, -35, -39, -44, -48, -52, -57,
-61, -66, -70, -74, -78, -83, -87, -91,
-95, -99, -103, -107, -111, -115, -119, -123,
-127, -131, -135, -139, -142, -146, -150, -153,
-157, -160, -164, -167, -171, -174, -177, -180,
-183, -187, -190, -192, -195, -198, -201, -204,
-206, -209, -212, -214, -216, -219, -221, -223,
-225, -227, -229, -231, -233, -235, -237, -238,
-240, -241, -243, -244, -245, -247, -248, -249,
-250, -251, -252, -252, -253, -254, -254, -254,
-255, -255, -255, -255, -255, -255, -255, -255,
-255, -255, -254, -254, -253, -252, -252, -251,
-250, -249, -248, -247, -246, -244, -243, -242,
-240, -239, -237, -235, -234, -232, -230, -228,
-226, -224, -221, -219, -217, -214, -212, -209,
-207, -204, -202, -199, -196, -193, -190, -187,
-184, -181, -178, -174, -171, -168, -164, -161,
-158, -154, -150, -147, -143, -139, -136, -132,
-128, -124, -120, -116, -112, -108, -104, -100,
-96, -92, -88, -83, -79, -75, -71, -66,
-62, -58, -53, -49, -45, -40, -36, -31,
-27, -22, -18, -14, -9, -5, 0, 3,
8, 12, 17, 21, 26, 30, 35, 39,
43, 48, 52, 56, 61, 65, 69, 74,
78, 82, 86, 91, 95, 99, 103, 107,
111, 115, 119, 123, 127, 131, 135, 138,
142, 146, 149, 153, 157, 160, 164, 167,
170, 174, 177, 180, 183, 186, 189, 192,
195, 198, 201, 204, 206, 209, 211, 214,
216, 219, 221, 223, 225, 227, 229, 231,
233, 235, 237, 238, 240, 241, 243, 244,
245, 247, 248, 249, 250, 251, 251, 252,
253, 253, 254, 254, 255, 255, 255, 255};


void fillDefaultConfig(sHough_for_lines_Config * params)
{
  strcpy(params->edgeMapList  , "");
  strcpy(params->outputVotedRhoTheta , "");
  params->width             = 640;
  params->height            = 480;
  params->listSize          = 4080;
  params->thetaStart        = 0;
  params->thetaEnd          = 180;
  params->rhoMaxLength      = 800;
  params->randSeed          = 0;
  params->numIter           = 1;
  params->thetaStepSize     = 1;
}


///////////////////////////////////////
// Makes a 32x32 random
///////////////////////////////////////
static void CreatePattern(uint16_t * p, uint32_t listSize, uint16_t imgWidth, uint16_t imgHeight)
{
  int32_t i;

  for ( i = 0; i < 2 * listSize; i+=2 )
  {
    p[i]    = rand() % imgWidth;
    p[i+1]  = rand() % imgHeight;
  }

}

int32_t test_houghForLines()
{
  int32_t i,j, iter, status = 0;
  uint32_t seed;
  FILE *fp_in = NULL, *fp_out = NULL;

  uint16_t * edgeMapList;
  uint16_t * intermIndexArray;
  uint16_t * votedRhoArray8Copy;
  uint16_t * votedRhoArray;

  uint16_t * intermIndexArrayRef;
  uint16_t * votedRhoArrayRef;
  uint16_t * votedRhoArrayCurrRef;
  uint16_t * offsetPtr;
  uint16_t * interimTransposeBuf1;
  uint16_t * interimTransposeBuf2;
  int16_t * pCosSinThetaMulNormQ15;
  uint16_t interimTransposeStride;
  uint16_t numWordsInterimTransposeBuf;
  uint16_t normalizationFactorQ8;
  uint32_t diameterQ8;
  uint16_t theta;
  long tempData;
  profiler_init();
  vcop_minit();

    numWordsInterimTransposeBuf = ( ( ( ALIGN_2SIMD(gConfig_hough_for_lines.rhoMaxLength) * sizeof(uint16_t)) / 2)/ 4);
    interimTransposeStride = (numWordsInterimTransposeBuf % 2)? numWordsInterimTransposeBuf :
                                            numWordsInterimTransposeBuf + 1;

    /* get stride in terms of bytes */
    interimTransposeStride = interimTransposeStride * sizeof(uint32_t);

#if VCOP_HOST_EMULATION
  /* Multiplication by two because it stores x and y coordinate in packed format*/
  edgeMapList = (uint16_t *) malloc(gConfig_hough_for_lines.listSize *
                                  sizeof(uint16_t) * 2);


  intermIndexArray = (uint16_t *) malloc(
                  max(interimTransposeStride * 8, gConfig_hough_for_lines.listSize * sizeof(uint16_t)));

  votedRhoArray8Copy = (uint16_t *) malloc(8 * ALIGN_2SIMD(gConfig_hough_for_lines.rhoMaxLength) * sizeof(uint16_t));

  votedRhoArray = (uint16_t *) malloc(ALIGN_2SIMD(gConfig_hough_for_lines.rhoMaxLength) * sizeof(uint16_t));

  offsetPtr = (uint16_t *) malloc(8 * sizeof(uint16_t));

  pCosSinThetaMulNormQ15 = ( int16_t *) malloc (2* sizeof(int16_t));


#else
 /* vcop_malloc doesnt allow to allocate full 16k of image buffer LA. Hence using
 hard coded address for it edgeMap*/
 edgeMapList = (uint16_t *)0x40050004;
  /* Use 4 bytes for storing the multiplication of cos for current theta and normalization factor
  followed by sin for current theta and normalization factor */
 pCosSinThetaMulNormQ15 = ( int16_t *) 0x40050000 ;


 intermIndexArray = (uint16_t *) vcop_malloc(VCOP_IBUFHA ,max(interimTransposeStride * 8, gConfig_hough_for_lines.listSize * sizeof(uint16_t)));

 votedRhoArray8Copy = (uint16_t *) vcop_malloc(VCOP_WMEM ,8 * ALIGN_2SIMD(gConfig_hough_for_lines.rhoMaxLength) *
                                          sizeof(uint16_t));

 votedRhoArray = (uint16_t *) vcop_malloc(VCOP_IBUFHA, ALIGN_2SIMD(gConfig_hough_for_lines.rhoMaxLength) *
                                          sizeof(uint16_t));



 offsetPtr = (uint16_t *) vcop_malloc(VCOP_WMEM , 8 * sizeof(uint16_t));

#endif

  intermIndexArrayRef = (uint16_t *) malloc(gConfig_hough_for_lines.listSize * sizeof(uint16_t));

  votedRhoArrayRef = (uint16_t *) malloc(ALIGN_2SIMD(gConfig_hough_for_lines.rhoMaxLength) * sizeof(uint16_t));

  votedRhoArrayCurrRef = (uint16_t *) malloc(ALIGN_2SIMD(gConfig_hough_for_lines.rhoMaxLength) * sizeof(uint16_t));




  memset(votedRhoArrayCurrRef, 0, ALIGN_2SIMD(gConfig_hough_for_lines.rhoMaxLength) * sizeof(uint16_t));


  for (iter = 0; iter < gConfig_hough_for_lines.numIter; iter++)
  {
    printf("Iteration %d\n", iter);

    if(strcmp(gConfig_hough_for_lines.edgeMapList, ""))
    {
      printf("File Test\n");
      fp_in = fopen((const char *)gConfig_hough_for_lines.edgeMapList, "rb");

      if(fp_in == NULL)
      {
          printf("Failed to open input file: %s.\n", gConfig_hough_for_lines.edgeMapList);
          return -1;
      }
      fread(edgeMapList, gConfig_hough_for_lines.listSize *
                    sizeof(uint16_t) * 2, 1, fp_in);

      fclose(fp_in);
    }
    else
    {
      /* Generate input data */
      seed = (gConfig_hough_for_lines.randSeed == 0) ? _tsc_gettime() : gConfig_hough_for_lines.randSeed;
      srand(seed);
      printf("Random pattern test: Seed = %d\n", seed);
      CreatePattern(edgeMapList,
                    gConfig_hough_for_lines.listSize,
                    gConfig_hough_for_lines.width,
                    gConfig_hough_for_lines.height);
    }

    numWordsInterimTransposeBuf = ( ( ( ALIGN_2SIMD(gConfig_hough_for_lines.rhoMaxLength) * sizeof(uint16_t)) / 2)/ 4);
    interimTransposeStride = (numWordsInterimTransposeBuf % 2)? numWordsInterimTransposeBuf :
                                            numWordsInterimTransposeBuf + 1;

    /* get stride in terms of bytes */
    interimTransposeStride = interimTransposeStride * sizeof(uint32_t);

    for ( i = 0 ; i < 8 ; i++)
    {
      offsetPtr[i] = interimTransposeStride * i;
    }

    diameterQ8 = SQRTof2_Q8 * max( gConfig_hough_for_lines.width ,
                                  gConfig_hough_for_lines.height);


#if VCOP_HOST_EMULATION

    interimTransposeBuf2 = (uint16_t *) malloc ( interimTransposeStride * 8 );


#else
    interimTransposeBuf2 = (uint16_t *) vcop_malloc(VCOP_WMEM,
                          interimTransposeStride * 8);
#endif

    if(strcmp(gConfig_hough_for_lines.outputVotedRhoTheta , ""))
    {
      fp_out = fopen((const char*)gConfig_hough_for_lines.outputVotedRhoTheta, "wb+");
    }

    if(fp_out == NULL)
    {
      printf("Failed to open Output file.\n");
    }

    for ( theta = gConfig_hough_for_lines.thetaStart ;
      theta < gConfig_hough_for_lines.thetaStart + gConfig_hough_for_lines.thetaEnd;
      theta+= gConfig_hough_for_lines.thetaStepSize)
    {
        tempData = cosLutQ8[theta] * (gConfig_hough_for_lines.rhoMaxLength << 16) / (2 * diameterQ8);
        pCosSinThetaMulNormQ15[0] = (int16_t) (tempData >> 1) ;//round(tempData, 1);
            tempData = sinLutQ8[theta] * (gConfig_hough_for_lines.rhoMaxLength << 16) / (2 * diameterQ8);
        pCosSinThetaMulNormQ15[1] = (int16_t)(tempData >> 1);//round(tempData, 1);

      memset(votedRhoArrayRef, 0, gConfig_hough_for_lines.rhoMaxLength * sizeof(uint16_t));
      memset(votedRhoArray, 0, gConfig_hough_for_lines.rhoMaxLength * sizeof(uint16_t));

      profiler_start();

      vcop_hough_for_lines(edgeMapList,
                                  pCosSinThetaMulNormQ15,
                                  intermIndexArray,
                                  votedRhoArray8Copy,
                                  gConfig_hough_for_lines.listSize,
                                  gConfig_hough_for_lines.rhoMaxLength
                                  );
      profiler_end();

      /* Reuse intermIndexArray buffer */
      interimTransposeBuf1 = intermIndexArray;
      profiler_start();

      vcop_merge_voted_rho_array(votedRhoArray8Copy,
                                 votedRhoArray,
                                 interimTransposeBuf1,
                                 interimTransposeBuf2,
                                 offsetPtr,
                                 gConfig_hough_for_lines.rhoMaxLength
                                 );

      profiler_end();

      /*---------------------------------------------------------------------*/
      /*  Function call to the Natural-C API to be tested                    */
      /*  Compute Harris scores for all blocks in IMAGE_BLOCKS               */
      /*---------------------------------------------------------------------*/

      vcop_hough_for_lines_cn(edgeMapList,
                              pCosSinThetaMulNormQ15,
                              intermIndexArrayRef,
                              votedRhoArrayCurrRef,
                              gConfig_hough_for_lines.listSize,
                              gConfig_hough_for_lines.rhoMaxLength
                              );

      vcop_merge_voted_rho_array_cn(votedRhoArrayCurrRef,
                              votedRhoArrayRef,
                              gConfig_hough_for_lines.rhoMaxLength);



      /*---------------------------------------------------------------------*/
      /*  Compare the results of output arrays with expected output arrays.  */
      /*---------------------------------------------------------------------*/
      status = 0;

      for ( j = 0 ; j < gConfig_hough_for_lines.rhoMaxLength * 1 ; j++ )
      {
        if ( votedRhoArray[j] != votedRhoArrayRef[j])
        {
          status = -1;
          printf("Output Not Bit Matching at %d \n", j);
          break;
        }
      }

      if ( status != 0 )
      {
        printf("NATC and Kernel C output not matching at iteration %d for theta %d \n", iter, theta);
        break;
      }

      if(fp_out != NULL)
      {
        fwrite(votedRhoArray , gConfig_hough_for_lines.rhoMaxLength * sizeof(uint16_t),
                        1, fp_out);
      }

    }

    fclose(fp_out);

#if VCOP_HOST_EMULATION
      free(interimTransposeBuf1);
#endif

  }

  if(status != 0) {
      printf("Hough For lines mismatches:\n");
  }

  profiler_deinit();

  printf(status ? "test_houghForLines: FAIL\n" : "test_houghForLines: PASS\n");

  return (status);
}


int32_t main(int32_t argc, char *argv[])
{
    int32_t status = 0;
    char configFile[FILE_NAME_SIZE];

    if (argc > 1)
    {
        strcpy(configFile, argv[1]) ;
    }
    else
    {
        strcpy(configFile,"../testvecs/config/vcop_hough_for_lines.cfg");
    }

    fillDefaultConfig(&gConfig_hough_for_lines);
    status = readparamfile(configFile, &gsTokenMap_hough_for_lines[0]) ;
    if(status == -1)
    {
        printf("Parser Failed. Using default values.\n");
    }

    printf ("\nHough For Lines kernel Test Bench:\n");
    status = test_houghForLines();

    return status;
}

