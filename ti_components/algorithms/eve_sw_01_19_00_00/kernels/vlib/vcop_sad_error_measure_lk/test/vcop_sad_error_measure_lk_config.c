/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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
#include "configparser.h"
#include "vcop_sad_error_measure_lk_config.h"

ssad_error_measure_lk_Config gConfig_sad_error_measure_lk;
sTokenMapping gsTokenMap_sad_error_measure_lk[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_sad_error_measure_lk.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName1",             &gConfig_sad_error_measure_lk.inFileName1              , STRING, SINGLE},
  {(char* )"inFileName2",             &gConfig_sad_error_measure_lk.inFileName2              , STRING, SINGLE},
  {(char* )"inFileName3",             &gConfig_sad_error_measure_lk.inFileName3              , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_sad_error_measure_lk.outFileName              , STRING, SINGLE},
  {(char* )"inputStride",             &gConfig_sad_error_measure_lk.inputStride              , INT_16, SINGLE},
  {(char* )"frmWidth",                &gConfig_sad_error_measure_lk.frmWidth                 , INT_16, SINGLE},
  {(char* )"frmHeight",               &gConfig_sad_error_measure_lk.frmHeight                , INT_16, SINGLE},
  {(char* )"blkWidth",                &gConfig_sad_error_measure_lk.blkWidth                 , INT_16, SINGLE},
  {(char* )"blkHeight",               &gConfig_sad_error_measure_lk.blkHeight                , INT_16, SINGLE},
  {(char* )"numKeyPoints",            &gConfig_sad_error_measure_lk.numKeyPoints             , INT_16, SINGLE},
  {(char* )"shiftValue",              &gConfig_sad_error_measure_lk.shiftValue               , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_sad_error_measure_lk.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_sad_error_measure_lk.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_sad_error_measure_lk.seedForRND               , INT_32, SINGLE},
} ;
