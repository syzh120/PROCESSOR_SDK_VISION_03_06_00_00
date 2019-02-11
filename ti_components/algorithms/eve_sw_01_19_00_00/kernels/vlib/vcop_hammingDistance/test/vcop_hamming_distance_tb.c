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
/*  NAME                                                                    */
/*      vcop_hamming_distance_tb.c                                          */
/*                                                                          */
/*  Test bench file for testing the VCOP kernel for hamming distance        */
/*  function with C reference output                                        */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the function        */
/*      'vcop_hamming_distance' function with a random input strings        */
/*      of varying lengths.                                                 */
/*                                                                          */
/*  This test bench then compares the results with the C reference output   */
/*  "pHammingRefOut[]" and prints a pass/fail message.                      */
/*                                                                          */
/*  To build the executable type:                                           */
/*  gmake                                                                   */
/*                                                                          */
/*  @author Venkat R Peddigari (a0393744@ti.com)                            */
/*                                                                          */
/*  @version 1.0 (July 2013) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#include  <stdio.h>
#include  <stdint.h>
#include  <stdlib.h>
#include  <string.h>

#include "vcop.h"
#include "ti_file_io.h"
#include "eve_profile.h"

#if VCOP_HOST_EMULATION
    #include "../src_kernelC/vcop_feature_matching_kernel.k"
    #include "../src_kernelC/vcop_hamming_distance_kernel.k"
#else
    #include "vcop_feature_matching_kernel.h"
    #include "vcop_hamming_distance_kernel.h"
#endif

#include "vcop_hamming_distance_config.h"

/* ------------------------------------------------------------------------ */
/*  Include prototype for the "C" implementation of hamming distance        */
/*  functions.                                                              */
/* ------------------------------------------------------------------------ */
#include "vcop_hamming_distance_cn.h"

void test_hamming_distance_vcop()
{
  uint32_t fail, i, j, seed;
  uint8_t *pHammingIn1 = NULL, *pHammingIn2 = NULL;
  uint32_t *pHammingOut = NULL, *pHammingRefOut = NULL;
  uint16_t *pHammingScratch = NULL;
  uint32_t size_mod_32 = 0;

  profiler_init();

#if VCOP_HOST_EMULATION
  pHammingIn1   = (uint8_t *)malloc(gConfig_hamming_distance.descPitch*2*((gConfig_hamming_distance.numDesc1 + 1)/2));
  pHammingIn2   = (uint8_t *)malloc(gConfig_hamming_distance.descPitch*2*((gConfig_hamming_distance.numDesc1 + 1)/2));
  pHammingOut   = (uint32_t *)malloc(2*((gConfig_hamming_distance.numDesc1 + 1)/2)*16*sizeof(uint32_t));
  pHammingScratch = (uint16_t *)malloc(36*8*((gConfig_hamming_distance.numDesc1 + 1)/2));
#else
  pHammingIn1   = (uint8_t *)vcop_malloc(VCOP_IBUFLA, gConfig_hamming_distance.descPitch*2*((gConfig_hamming_distance.numDesc1 + 1)/2));
  pHammingIn2   = (uint8_t *)vcop_malloc(VCOP_IBUFHA, gConfig_hamming_distance.descPitch*2*((gConfig_hamming_distance.numDesc1 + 1)/2));
  pHammingOut   = (uint32_t *)vcop_malloc(VCOP_IBUFLA, 2*((gConfig_hamming_distance.numDesc1 + 1)/2)*16*sizeof(uint32_t));
  pHammingScratch = (uint16_t *)vcop_malloc(VCOP_WMEM, 36*8*((gConfig_hamming_distance.numDesc1 + 1)/2));
#endif

  pHammingRefOut = (uint32_t *)malloc(gConfig_hamming_distance.numDesc1*sizeof(uint32_t));

  printf("\nStart Hamming Distance Test\n");
  printf("descLen = %d, numDesc = %d, mode = %s\n",
    gConfig_hamming_distance.descLen, gConfig_hamming_distance.numDesc1,
    gConfig_hamming_distance.mode ? "One to One" : "Many to One");

  //Initialize input strings with random inputs
  memset(pHammingIn1, 0, gConfig_hamming_distance.descPitch*
         gConfig_hamming_distance.numDesc1*sizeof(unsigned char));
  memset(pHammingIn2, 0, gConfig_hamming_distance.descPitch*
         gConfig_hamming_distance.numDesc1*sizeof(unsigned char));

  seed = (gConfig_hamming_distance.randSeed1 == 0) ? _tsc_gettime() :
          gConfig_hamming_distance.randSeed1;
  srand(seed);
  printf("Pattern Generation Seed for String 1 = %d\n", seed);

  for(j = 0; j< gConfig_hamming_distance.numDesc1; j++) {
    for(i = 0; i< gConfig_hamming_distance.descLen; i++) {
      pHammingIn1[j*gConfig_hamming_distance.descPitch + i]= rand()&0xFF;
    }
  }

  seed = (gConfig_hamming_distance.randSeed2 == 0) ? _tsc_gettime() :
          gConfig_hamming_distance.randSeed2;
  srand(seed);
  printf("Pattern Generation Seed for String 2 = %d\n", seed);

  for(j = 0; j< gConfig_hamming_distance.numDesc1; j++) {
    for(i = 0; i< gConfig_hamming_distance.descLen; i++) {
      pHammingIn2[j*gConfig_hamming_distance.descPitch + i]= rand()&0xFF;
    }
  }

  profiler_start();

  size_mod_32 = (gConfig_hamming_distance.descLen % (4 * VCOP_SIMD_WIDTH));

  if(gConfig_hamming_distance.descLen >= (4 * VCOP_SIMD_WIDTH)) {
    if(size_mod_32 != 0) {
      vcop_hamming_distance((unsigned int *)pHammingIn1,
        (unsigned int *)pHammingIn2, pHammingIn1, pHammingIn2,
        gConfig_hamming_distance.descLen, gConfig_hamming_distance.numDesc1,
        gConfig_hamming_distance.mode, gConfig_hamming_distance.descPitch,
        pHammingOut, (unsigned short*)pHammingScratch);
    }
    else {
      vcop_hamming_distance_multiple_32((unsigned int *)pHammingIn1,
        (unsigned int *)pHammingIn2, gConfig_hamming_distance.descLen,
        gConfig_hamming_distance.numDesc1, gConfig_hamming_distance.mode,
        gConfig_hamming_distance.descPitch, pHammingOut,
        (unsigned short*)pHammingScratch);
    }
  }
  else {
    vcop_hamming_distance_size_lt_32(pHammingIn1, pHammingIn2,
      gConfig_hamming_distance.descLen, gConfig_hamming_distance.numDesc1,
      gConfig_hamming_distance.mode, gConfig_hamming_distance.descPitch,
      pHammingOut);
  }

  profiler_end();

  /*---------------------------------------------------------------------*/
  /*  Call the natural C implementation for hamming distance             */
  /*---------------------------------------------------------------------*/
  vcop_hamming_distance_cn(pHammingIn1, pHammingIn2,
    gConfig_hamming_distance.descLen, gConfig_hamming_distance.numDesc1,
    gConfig_hamming_distance.mode, gConfig_hamming_distance.descPitch,
    pHammingRefOut, 1, 0);

  /*---------------------------------------------------------------------*/
  /*  Compare the results of hamming distance with expected truth.       */
  /*  If there is a mismatch, print out the expected value, else print   */
  /*  pass.                                                              */
  /*---------------------------------------------------------------------*/
  fail = 0;

  for(i = 0; i< gConfig_hamming_distance.numDesc1; i++) {
    if((pHammingRefOut[i] >> 16) != pHammingOut[i]) {
      fail = 1;
      printf("(%4d): C Reference Output = %d, VCOP Computed Output = %d\n",
        i, pHammingRefOut[i] >> 16, pHammingOut[i]);
    }
  }

#if 0
  for(i = 0; i < gConfig_hamming_distance.ysize; i++)
  {
    printf("Computed Hamming Distance: (%3d): C Reference = %d, "
      "VCOP Output = %d, Size of String = %d \n", i,
      pHammingRefOut[i] >> 16, pHammingOut[i],
      gConfig_hamming_distance.descLen);
  }
#endif

  printf(fail?"FAIL\n":"PASS\n");

#if VCOP_HOST_EMULATION
  if(!pHammingIn1) free(pHammingIn1);
  if(!pHammingIn2) free(pHammingIn2);
  if(!pHammingOut) free(pHammingOut);
  if(!pHammingScratch) free(pHammingScratch);
#else
  if(!pHammingIn1) vcop_free(pHammingIn1);
  if(!pHammingIn2) vcop_free(pHammingIn2);
  if(!pHammingOut) vcop_free(pHammingOut);
  if(!pHammingScratch) vcop_free(pHammingScratch);
#endif

  if(!pHammingRefOut) free(pHammingRefOut);

}

void test_feature_matching_vcop()
{
  uint32_t fail, i, j, seed;
  uint16_t numOutCols;
  uint8_t *pHammingIn1 = NULL, *pHammingIn2 = NULL;
  uint32_t *pDescriptorMask = NULL, *pHammingOut = NULL, *pHammingRefOut = NULL;
  uint32_t *pMinDist0 = NULL, *pMinDist1 = NULL;
  uint32_t *pMinDist0_ref = NULL, *pMinDist1_ref = NULL;
  uint16_t *pHammingScratch = NULL, *pMatchIdx = NULL;
  uint16_t *pScatterOffsets = NULL, *pMatchIdx_ref = NULL;

  profiler_init();

#if VCOP_HOST_EMULATION
  pHammingIn1   = (uint8_t *)malloc(gConfig_hamming_distance.descPitch*16*((gConfig_hamming_distance.numDesc1 + 15)/16));
  pHammingIn2   = (uint8_t *)malloc(gConfig_hamming_distance.descPitch*2*((gConfig_hamming_distance.numDesc2 + 1)/2));
  pHammingOut   = (uint32_t *)malloc(2*((gConfig_hamming_distance.numDesc2 + 1)/2)*16* sizeof(uint32_t));
  pMinDist0     = (uint32_t *)malloc(16*((gConfig_hamming_distance.numDesc1 + 15)/16)* sizeof(uint32_t));
  pMinDist1     = (uint32_t *)malloc(16*((gConfig_hamming_distance.numDesc1 + 15)/16)* sizeof(uint32_t));
  pMatchIdx     = (uint16_t *)malloc(2*gConfig_hamming_distance.numDesc1);
  pDescriptorMask = (uint32_t *)malloc(32*((gConfig_hamming_distance.descLen + 31)/32));
  if(gConfig_hamming_distance.descLen <= 32) {
    pHammingScratch = (uint16_t *)malloc(36*8*((gConfig_hamming_distance.numDesc2 + 1)/2));
  }
  else {
    pHammingScratch = (uint16_t *)malloc(68*8*((gConfig_hamming_distance.numDesc2 + 1)/2));
    pScatterOffsets = (uint16_t *)malloc(8*sizeof(uint16_t));
  }
#else
  pHammingIn1   = (uint8_t *)vcop_malloc(VCOP_IBUFLA, gConfig_hamming_distance.descPitch*16*((gConfig_hamming_distance.numDesc1 + 15)/16));
  pHammingIn2   = (uint8_t *)vcop_malloc(VCOP_IBUFHA, gConfig_hamming_distance.descPitch*2*((gConfig_hamming_distance.numDesc2 + 1)/2));
  pHammingOut   = (uint32_t *)vcop_malloc(VCOP_IBUFLA, 2*((gConfig_hamming_distance.numDesc2 + 1)/2)*16* sizeof(uint32_t));
  pMinDist0     = (uint32_t *)vcop_malloc(VCOP_WMEM, 16*((gConfig_hamming_distance.numDesc1 + 15)/16)* sizeof(uint32_t));
  pMinDist1     = (uint32_t *)vcop_malloc(VCOP_WMEM, 16*((gConfig_hamming_distance.numDesc1 + 15)/16)* sizeof(uint32_t));
  pMatchIdx     = (uint16_t *)vcop_malloc(VCOP_IBUFHA, 2*gConfig_hamming_distance.numDesc1);
  pDescriptorMask = (uint32_t *)vcop_malloc(VCOP_WMEM, 32*((gConfig_hamming_distance.descLen + 31)/32));
  if(gConfig_hamming_distance.descLen <= 32) {
    pHammingScratch = (uint16_t *)vcop_malloc(VCOP_WMEM, 36*8*((gConfig_hamming_distance.numDesc2 + 1)/2));
  }
  else {
    pHammingScratch = (uint16_t *)vcop_malloc(VCOP_WMEM, 68*8*((gConfig_hamming_distance.numDesc2 + 1)/2));
    pScatterOffsets = (uint16_t *)vcop_malloc(VCOP_WMEM, 8*sizeof(uint16_t));
  }
#endif

  pHammingRefOut = (uint32_t *)malloc(gConfig_hamming_distance.numDesc2*16* sizeof(uint32_t));
  pMinDist0_ref  = (uint32_t *)malloc(16*((gConfig_hamming_distance.numDesc1 + 15)/16)* sizeof(uint32_t));
  pMinDist1_ref  = (uint32_t *)malloc(16*((gConfig_hamming_distance.numDesc1 + 15)/16)* sizeof(uint32_t));
  pMatchIdx_ref  = (uint16_t *)malloc(2*gConfig_hamming_distance.numDesc1);

  printf("\nStart Feature Matching Test\n");
  printf("descLen = %d, numDesc1 = %d, numDesc2 = %d, mode = %s\n",
    gConfig_hamming_distance.descLen, gConfig_hamming_distance.numDesc1,
    gConfig_hamming_distance.numDesc2, gConfig_hamming_distance.mode ?
    "One to One" : "Many to 16");

  //Initialize input strings with random inputs
  memset(pHammingIn1, 0, gConfig_hamming_distance.descPitch*16*
         ((gConfig_hamming_distance.numDesc1 + 15)/16)*sizeof(unsigned char));
  memset(pHammingIn2, 0, gConfig_hamming_distance.descPitch*2*
         ((gConfig_hamming_distance.numDesc2 + 1)/2)*sizeof(unsigned char));
  memset(pMinDist0_ref, 0xFF, 16*((gConfig_hamming_distance.numDesc1 + 15)/16)* sizeof(uint32_t));
  memset(pMinDist1_ref, 0xFF, 16*((gConfig_hamming_distance.numDesc1 + 15)/16)* sizeof(uint32_t));

  // Generate descriptor list 1
  seed = (gConfig_hamming_distance.randSeed1 == 0) ? _tsc_gettime() :
          gConfig_hamming_distance.randSeed1;
  srand(seed);
  printf("Pattern Generation Seed for String 1 = %d\n", seed);

  for( j = 0; j< gConfig_hamming_distance.numDesc1; j++) {
    for( i = 0; i< gConfig_hamming_distance.descLen; i++) {
      pHammingIn1[j*gConfig_hamming_distance.descPitch + i]= rand()&0xFF;
    }
  }

  // Generate descriptor list 2
  seed = (gConfig_hamming_distance.randSeed2 == 0) ? _tsc_gettime() :
          gConfig_hamming_distance.randSeed2;
  srand(seed);
  printf("Pattern Generation Seed for String 2 = %d\n", seed);

  for( j = 0; j< gConfig_hamming_distance.numDesc2; j++) {
    for( i = 0; i< gConfig_hamming_distance.descLen; i++) {
      pHammingIn2[j*gConfig_hamming_distance.descPitch + i]= rand()&0xFF;
    }
  }

  numOutCols = (gConfig_hamming_distance.mode == 0) ? 16 : 1;

  if(gConfig_hamming_distance.descLen != 32) {
    for(i = 0; i < 32*((gConfig_hamming_distance.descLen + 31)/32); i++) {
      ((uint8_t *)pDescriptorMask)[i] = (i < gConfig_hamming_distance.descLen) ? 0xFF : 0x00;
    }
  }

  if(gConfig_hamming_distance.descLen > 32) {
    for(i = 0; i < 8; i++) {
      pScatterOffsets[i] = 68*i;
    }
  }

#if !(VCOP_HOST_EMULATION)
  VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                      IBUFHA_SYST, IBUFLA_SYST);

  vcop_featureMatch_initialize_init(pMinDist0, pMinDist1,
    16*((gConfig_hamming_distance.numDesc1 + 15)/16),
    __pblock_vcop_featureMatch_initialize);

  if(gConfig_hamming_distance.descLen == 32) {
    vcop_featureMatching_32_init((unsigned int *)pHammingIn2,
      (unsigned int *)pHammingIn1, (unsigned char *)pHammingScratch,
      (unsigned short *)pHammingOut, gConfig_hamming_distance.numDesc2,
      gConfig_hamming_distance.mode, gConfig_hamming_distance.descPitch,
      0, __pblock_vcop_featureMatching_32);

    vcop_featureMatch_32_pblk_update_init(
      (unsigned int*)__pblock_vcop_featureMatching_32,
      (unsigned int*)__pblock_vcop_findTwoBestMatches,
      16*gConfig_hamming_distance.descPitch, 4*16,
      __pblock_vcop_featureMatch_32_pblk_update);

    vcop_featureMatch_32_pblk_reset_init(
      (int*)__pblock_vcop_featureMatching_32,
      (unsigned int*)__pblock_vcop_findTwoBestMatches,
      gConfig_hamming_distance.numDesc2,
      gConfig_hamming_distance.numDesc2 - 1, (unsigned int)pHammingIn1,
      (unsigned int)pMinDist0, (unsigned int)pMinDist1,
      __pblock_vcop_featureMatch_32_pblk_reset);
  }
  else if(gConfig_hamming_distance.descLen < 32) {
    vcop_featureMatching_lt_32_init((unsigned int *)pHammingIn2,
      (unsigned int *)pHammingIn1, (unsigned int *)pDescriptorMask,
      (unsigned char *)pHammingScratch, (unsigned short *)pHammingOut,
      gConfig_hamming_distance.numDesc2, gConfig_hamming_distance.mode,
      gConfig_hamming_distance.descPitch, 0,
      __pblock_vcop_featureMatching_lt_32);

    vcop_featureMatch_lt_32_pblk_update_init(
      (unsigned int*)__pblock_vcop_featureMatching_lt_32,
      (unsigned int*)__pblock_vcop_findTwoBestMatches,
      16*gConfig_hamming_distance.descPitch, 4*16,
      __pblock_vcop_featureMatch_lt_32_pblk_update);

    vcop_featureMatch_lt_32_pblk_reset_init(
      (int*)__pblock_vcop_featureMatching_lt_32,
      (unsigned int*)__pblock_vcop_findTwoBestMatches,
      gConfig_hamming_distance.numDesc2,
      gConfig_hamming_distance.numDesc2 - 1, (unsigned int)pHammingIn1,
      (unsigned int)pMinDist0, (unsigned int)pMinDist1,
      __pblock_vcop_featureMatch_lt_32_pblk_reset);
  }
  else {
    vcop_featureMatching_gt_32_init((unsigned int *)pHammingIn2,
      (unsigned int *)pHammingIn1, (unsigned int *)pDescriptorMask,
      (unsigned short *)pHammingScratch, (unsigned short *)pScatterOffsets,
      (unsigned short *)pHammingOut, gConfig_hamming_distance.descLen,
      gConfig_hamming_distance.numDesc2, gConfig_hamming_distance.mode,
      gConfig_hamming_distance.descPitch, 0,
      __pblock_vcop_featureMatching_gt_32);

    vcop_featureMatch_gt_32_pblk_update_init(
      (unsigned int*)__pblock_vcop_featureMatching_gt_32,
      (unsigned int*)__pblock_vcop_findTwoBestMatches,
      16*gConfig_hamming_distance.descPitch, 4*16,
      __pblock_vcop_featureMatch_gt_32_pblk_update);

    vcop_featureMatch_gt_32_pblk_reset_init(
      (int*)__pblock_vcop_featureMatching_gt_32,
      (unsigned int*)__pblock_vcop_findTwoBestMatches,
      gConfig_hamming_distance.numDesc2,
      gConfig_hamming_distance.numDesc2 - 1, (unsigned int)pHammingIn1,
      (unsigned int)pMinDist0, (unsigned int)pMinDist1,
      __pblock_vcop_featureMatch_gt_32_pblk_reset);
  }

  vcop_findTwoBestMatches_init((unsigned int *)pHammingOut, pMinDist0,
    pMinDist1, 16, gConfig_hamming_distance.numDesc2,
    __pblock_vcop_findTwoBestMatches);

  vcop_pickConfidentMatches_init((unsigned short*)pMinDist0,
    (unsigned short*)pMinDist1, pMatchIdx,
    16*((gConfig_hamming_distance.numDesc1 + 15)/16),
    gConfig_hamming_distance.minDistanceThres,
    gConfig_hamming_distance.matchConfidence,
    __pblock_vcop_pickConfidentMatches);

  vcop_twoBestMatches_update_n_init(
    (short*)__pblock_vcop_findTwoBestMatches, 0,
    __pblock_vcop_twoBestMatches_update_n);
#endif

  /*---------------------------------------------------------------------*/
  /*  Function call to the VCOP featureMatch_initialize API              */
  /*---------------------------------------------------------------------*/
  profiler_start();

#if VCOP_HOST_EMULATION
  vcop_featureMatch_initialize(pMinDist0, pMinDist1,
    16*((gConfig_hamming_distance.numDesc1 + 15)/16));
#else
  VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                      IBUFHA_VCOP, IBUFLA_VCOP);

  vcop_featureMatch_initialize_vloops(__pblock_vcop_featureMatch_initialize);
  _vcop_vloop_done();

  VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                      IBUFHA_SYST, IBUFLA_SYST);
#endif

  profiler_end();


  for(j = 0; j < (gConfig_hamming_distance.numDesc1 + 15)/16; j++) {

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP hamming_distance API to be tested        */
    /*---------------------------------------------------------------------*/
    profiler_start();

#if VCOP_HOST_EMULATION
    if(gConfig_hamming_distance.descLen == 32) {
      vcop_featureMatching_32((unsigned int *)pHammingIn2,
        (unsigned int *)(pHammingIn1 + j*16*gConfig_hamming_distance.descPitch),
        (unsigned char *)pHammingScratch, (unsigned short *)pHammingOut,
        gConfig_hamming_distance.numDesc2, gConfig_hamming_distance.mode,
        gConfig_hamming_distance.descPitch, 0);
    }
    else if(gConfig_hamming_distance.descLen < 32){
      vcop_featureMatching_lt_32((unsigned int *)pHammingIn2,
        (unsigned int *)(pHammingIn1 + j*16*gConfig_hamming_distance.descPitch),
        (unsigned int *)pDescriptorMask, (unsigned char *)pHammingScratch,
        (unsigned short *)pHammingOut, gConfig_hamming_distance.numDesc2,
        gConfig_hamming_distance.mode, gConfig_hamming_distance.descPitch, 0);
    }
    else {
      vcop_featureMatching_gt_32((unsigned int *)pHammingIn2,
        (unsigned int *)(pHammingIn1 + j*16*gConfig_hamming_distance.descPitch),
        (unsigned int *)pDescriptorMask, (unsigned short *)pHammingScratch,
        (unsigned short *)pScatterOffsets, (unsigned short *)pHammingOut,
        gConfig_hamming_distance.descLen, gConfig_hamming_distance.numDesc2,
        gConfig_hamming_distance.mode, gConfig_hamming_distance.descPitch, 0);
    }
#else
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                        IBUFHA_VCOP, IBUFLA_VCOP);

    if(gConfig_hamming_distance.descLen == 32) {
      vcop_featureMatching_32_vloops(__pblock_vcop_featureMatching_32);
    }
    else if(gConfig_hamming_distance.descLen < 32){
      vcop_featureMatching_lt_32_vloops(__pblock_vcop_featureMatching_lt_32);
    }
    else {
      vcop_featureMatching_gt_32_vloops(__pblock_vcop_featureMatching_gt_32);
    }
    _vcop_vloop_done();

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);
#endif

    profiler_end();

    /*---------------------------------------------------------------------*/
    /*  Call the natural C implementation for hamming distance             */
    /*---------------------------------------------------------------------*/
    for(i = 0; i < numOutCols; i++) {
      vcop_hamming_distance_cn(pHammingIn2, pHammingIn1 +
        j*16*gConfig_hamming_distance.descPitch +
        i*gConfig_hamming_distance.descPitch, gConfig_hamming_distance.descLen,
        gConfig_hamming_distance.numDesc2, gConfig_hamming_distance.mode,
        gConfig_hamming_distance.descPitch, pHammingRefOut + i, 16, 0);
    }

    /*---------------------------------------------------------------------*/
    /*  Compare the results of hamming distance kernel with expected       */
    /*  truth. If there is a mismatch, print out the values.               */
    /*---------------------------------------------------------------------*/
    fail = memcmp((void *)pHammingRefOut, (void *)pHammingOut,
             numOutCols*gConfig_hamming_distance.numDesc2*sizeof(uint32_t));
    if(fail != 0) {
      for(i = 0; i < numOutCols*gConfig_hamming_distance.numDesc2; i++) {
        if (pHammingRefOut[i] != pHammingOut[i]) {
          printf("(%d, %d): C Reference = %d, VCOP Output = %d\n",
            i/numOutCols, i % numOutCols, pHammingRefOut[i], pHammingOut[i]);
          break;
        }
      }
    }

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP findTwoBestMatches API to be tested      */
    /*---------------------------------------------------------------------*/
    profiler_start();

#if VCOP_HOST_EMULATION
    vcop_findTwoBestMatches((unsigned int *)pHammingOut, pMinDist0 + j*16,
      pMinDist1 + j*16, 16, gConfig_hamming_distance.numDesc2);
#else
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                        IBUFHA_VCOP, IBUFLA_VCOP);

    vcop_findTwoBestMatches_vloops(__pblock_vcop_findTwoBestMatches);
    if(gConfig_hamming_distance.descLen == 32) {
      vcop_featureMatch_32_pblk_update_vloops(__pblock_vcop_featureMatch_32_pblk_update);
    }
    else if(gConfig_hamming_distance.descLen < 32) {
      vcop_featureMatch_lt_32_pblk_update_vloops(__pblock_vcop_featureMatch_lt_32_pblk_update);
    }
    else {
      vcop_featureMatch_gt_32_pblk_update_vloops(__pblock_vcop_featureMatch_gt_32_pblk_update);
    }
    _vcop_vloop_done();

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);
#endif

    profiler_end();

    /*---------------------------------------------------------------------*/
    /*  Call the natural C implementation for findTwoBestMatches           */
    /*---------------------------------------------------------------------*/
    vcop_findTwoBestMatches_cn(pHammingOut, pMinDist0_ref + j*16,
      pMinDist1_ref + j*16, 16, gConfig_hamming_distance.numDesc2);
  }

  /*---------------------------------------------------------------------*/
  /*  Compare the results of findTwoBestMatches kernel with expected     */
  /*  truth. If there is a mismatch, print out the values.               */
  /*---------------------------------------------------------------------*/
  fail |= memcmp(pMinDist0, pMinDist0_ref, sizeof(uint32_t)*
                 gConfig_hamming_distance.numDesc1);
  fail |= memcmp(pMinDist1, pMinDist1_ref, sizeof(uint32_t)*
                 gConfig_hamming_distance.numDesc1);

  if(fail != 0) {
    for(i = 0; i < gConfig_hamming_distance.numDesc1; i++) {
      if(pMinDist0_ref[i] != pMinDist0[i])
        printf("MinDist0(%d): %8x  %8x\n", i, pMinDist0_ref[i], pMinDist0[i]);
    }

    for(i = 0; i < gConfig_hamming_distance.numDesc1; i++) {
      if(pMinDist1_ref[i] != pMinDist1[i])
        printf("MinDist1(%d): %8x  %8x\n", i, pMinDist1_ref[i], pMinDist1[i]);
    }
  }

  /*---------------------------------------------------------------------*/
  /*  Function call to the VCOP pickConfidentMatches API to be tested    */
  /*---------------------------------------------------------------------*/
  profiler_start();

#if VCOP_HOST_EMULATION
  vcop_pickConfidentMatches((unsigned short*)pMinDist0,
    (unsigned short*)pMinDist1, pMatchIdx,
    16*((gConfig_hamming_distance.numDesc1 + 15)/16),
    gConfig_hamming_distance.minDistanceThres,
    gConfig_hamming_distance.matchConfidence);
#else
  VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                      IBUFHA_VCOP, IBUFLA_VCOP);

  vcop_pickConfidentMatches_vloops(__pblock_vcop_pickConfidentMatches);
  if(gConfig_hamming_distance.descLen == 32) {
    vcop_featureMatch_32_pblk_reset_vloops(__pblock_vcop_featureMatch_32_pblk_reset);
  }
  else if(gConfig_hamming_distance.descLen < 32) {
    vcop_featureMatch_lt_32_pblk_reset_vloops(__pblock_vcop_featureMatch_lt_32_pblk_reset);
  }
  else {
    vcop_featureMatch_gt_32_pblk_reset_vloops(__pblock_vcop_featureMatch_gt_32_pblk_reset);
  }
  vcop_twoBestMatches_update_n_vloops(__pblock_vcop_twoBestMatches_update_n);
  _vcop_vloop_done();

  VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                      IBUFHA_SYST, IBUFLA_SYST);
#endif

  profiler_end();

  /*---------------------------------------------------------------------*/
  /*  Call the natural C implementation for pickConfidentMatches         */
  /*---------------------------------------------------------------------*/
  vcop_pickConfidentMatches_cn((uint16_t*)pMinDist0_ref,
    (uint16_t*)pMinDist1_ref, pMatchIdx_ref,
    gConfig_hamming_distance.numDesc1,
    gConfig_hamming_distance.minDistanceThres,
    gConfig_hamming_distance.matchConfidence);

  fail |= memcmp(pMatchIdx, pMatchIdx_ref, sizeof(uint16_t)*
                gConfig_hamming_distance.numDesc1);
  if(fail != 0) {
    for(i = 0; i < gConfig_hamming_distance.numDesc1; i++) {
      if(pMatchIdx_ref[i] != pMatchIdx[i])
        printf("MatchIdx (%4d): %4x  %4x\n", i, pMatchIdx_ref[i], pMatchIdx[i]);
    }
  }

#if 0
  printf("Hamming Distance:\n");
  for(i = 0; i < gConfig_hamming_distance.numDesc2; i++) {
    for(j = 0; j < numOutCols; j++) {
      printf("%8x  ", pHammingOut[i*numOutCols + j]);
    }
    printf("\n");
  }

  printf("MinDist0:\n");
  for(i = 0; i < gConfig_hamming_distance.numDesc1; i++) {
    printf("%8x  ", pMinDist0[i]);
  }
  printf("MinDist1:\n");
  for(i = 0; i < gConfig_hamming_distance.numDesc1; i++) {
    printf("%8x  ", pMinDist1[i]);
  }
#endif

  printf(fail?"FAIL\n":"PASS\n");

#if VCOP_HOST_EMULATION
  if(pHammingIn1) free(pHammingIn1);
  if(pHammingIn2) free(pHammingIn2);
  if(pHammingOut) free(pHammingOut);
  if(pMinDist0) free(pMinDist0);
  if(pMinDist1) free(pMinDist1);
  if(pMatchIdx) free(pMatchIdx);
  if(pDescriptorMask) free(pDescriptorMask);
  if(pHammingScratch) free(pHammingScratch);
  if(pScatterOffsets) free(pScatterOffsets);
#else
  if(pHammingIn1) vcop_free(pHammingIn1);
  if(pHammingIn2) vcop_free(pHammingIn2);
  if(pHammingOut) vcop_free(pHammingOut);
  if(pMinDist0) vcop_free(pMinDist0);
  if(pMinDist1) vcop_free(pMinDist1);
  if(pMatchIdx) vcop_free(pMatchIdx);
  if(pDescriptorMask) vcop_free(pDescriptorMask);
  if(pHammingScratch) vcop_free(pHammingScratch);
  if(pScatterOffsets) vcop_free(pScatterOffsets);
#endif

  if(pHammingRefOut) free(pHammingRefOut);
  if(pMinDist0_ref) free(pMinDist0_ref);
  if(pMinDist1_ref) free(pMinDist1_ref);
  if(pMatchIdx_ref) free(pMatchIdx_ref);
}


char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}


void fillDefaultConfig(sHamming_distance_Config * params)
{
  strcpy(params->inStr1, "");
  strcpy(params->inStr2, "");
  strcpy(params->outHamDist, "");

  params->descLen      = 32;
  params->descPitch    = 32;
  params->numDesc1     = 160;
  params->numDesc2     = 160;
  params->mode         = 1;

  params->minDistanceThres = 50;
  params->matchConfidence  = 3277;

  params->randSeed1    = 0;
  params->randSeed2    = 0;
}


int main(int32_t argc, char *argv[])
{
  int32_t status = 0;
  TI_FILE *fp;
  int8_t *LinePtr;
  int32_t lineNum = -1;
  int32_t config_cmd;
  int8_t  configFileName[FILE_NAME_SIZE];
  sHamming_distance_Config *params;

  params = (sHamming_distance_Config *)(&gConfig_hamming_distance);

  if (argc > 1){
    strcpy((char *)configFileName, argv[1]) ;
  }
  else {
    strcpy((char *)configFileName, CONFIG_LIST_FILE_NAME);
  }

  fp = FOPEN((char *)configFileName , "r");
  if(fp== NULL)
  {
    printf("Could not open config list file : %s, Runing in default mode \n", CONFIG_LIST_FILE_NAME);
    fillDefaultConfig(params);
    /* Validate the applet */
    test_feature_matching_vcop();
    return (status);
  }

  while(1)
  {
    memset(params->configLine, 0, CONFIG_LINE_SIZE);
    status = (int)FGETS(params->configLine, CONFIG_LINE_SIZE, fp);
    LinePtr = (int8_t *)params->configLine;
    if ((status == EOF) || (status == 0))
      break;
    status = 0;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",params->configParam);
    if(config_cmd == 0)
    {
      printf("End of config list found !\n");
      break;
    }
    else if(config_cmd == 2)
    {
      continue;
    }
    else if(config_cmd == 1)
    {
      LinePtr = (int8_t *)moveToNextElement(params->configParam,(char *)LinePtr);
      status  = sscanf((const char *)LinePtr, "%s",configFileName);
      printf("Processing config file %s !\n", configFileName);
      fillDefaultConfig(params);
      status = readparamfile((char *)configFileName, gsTokenMap_hamming_distance) ;
      if(status == -1)
      {
        printf("Parser Failed\n");
        return -1 ;
      }

      printparams(gsTokenMap_hamming_distance, (int32_t)MAX_ITEMS_TO_PARSE,
        (uint32_t)params, sizeof(sHamming_distance_Config)) ;

      /* Validate the applet */
      if(gConfig_hamming_distance.testCase == 0) {
        test_hamming_distance_vcop();
      }
      else {
        test_feature_matching_vcop();
      }
    }
    else
    {
      printf("Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }
  }
  FCLOSE(fp);

#if 0 && VCOP_HOST_EMULATION
    printf("Press any key to continue ...\n");
    scanf("%c", configFileName);
#endif

  return status;
}

