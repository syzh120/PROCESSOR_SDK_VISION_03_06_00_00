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


/**
 *  @file       bam_fft_npt_16ix16o.h
 *
 *  @brief      This header defines interfaces for integrating FFT kernels
 *              into BAM.
 */

#ifndef BAM_FFT_NPT_16IX16O_H_
#define BAM_FFT_NPT_16IX16O_H_

#include "bam_common.h"

#define BAM_FFT_NPT_16IX16O_MAX_NUM_STAGES (5U)
#define BAM_FFT_NPT_16IX16O_MAX_NUM_POINTS (1024U)

typedef enum
{
  BAM_FFT_NPT_16IX16O_NUM_POINTS_1024 = 1024,
  BAM_FFT_NPT_16IX16O_NUM_POINTS_512 = 512,
  BAM_FFT_NPT_16IX16O_NUM_POINTS_256 = 256,
  BAM_FFT_NPT_16IX16O_NUM_POINTS_128 = 128,
  BAM_FFT_NPT_16IX16O_NUM_POINTS_64  = 64
} eBAM_FFT_NPT_16IX16O_NUM_POINTS;

typedef enum
{
  /* cmdId is this then corresponding args should be BAM_BeamForming_InCtrlArgs */
  BAM_FFT_NPT_16IX16O_CTRL_CMD_ID_SET_PARAMS = 0,
  /* cmdId is this then corresponding args should be BAM_BeamForming_OutCtrlArgs */
  BAM_FFT_NPT_16IX16O_CTRL_CMD_ID_GET_WBUF_PTR
} eBAM_BEAM_FORMING_CTRL_CMD_ID;


typedef struct
{
  uint16_t maxNumPoints;
  uint16_t maxNumLines;
  uint8_t  enableTranspose;
} BAM_Fftnpt16ix16o_Args;

typedef struct
{
  uint16_t       cmdId;
  void          *ctrlArgs;
} BAM_Fftnpt16ix16o_CtrlArgs;

typedef struct
{
  uint16_t numPoints;/* Refer eBAM_FFT_NPT_16IX16O_NUM_POINTS enum for valid values */
  uint16_t scaleFactors[BAM_FFT_NPT_16IX16O_MAX_NUM_STAGES];
  uint16_t numLines;
  uint16_t pitch;
  uint8_t  enable32bitsIntermResults;
  int8_t * twiddleFactorBuf;
  uint8_t enableDopplerCorrection;
  uint8_t *dopplerCorrectionBuf;
  uint16_t dopplerCorrectionScaling;
  uint16_t numPointsZeroPadding;
  uint16_t numActualPoints;
  uint16_t numBlocksPerAntenna;
  uint8_t  overflowMask;
  uint8_t  enableOverflowDetection;
  uint16_t saturationLimit;
  uint8_t  numValidBits;
} BAM_Fftnpt16ix16o_InCtrlArgs;

typedef struct
{
  /* These are the pointers allocated by this node but as we need to do further processing on
  this data we are getting these pointers outside of this node so that
  we can do further processing on the same without any need for doing
  EDMA transfer for the same */
  uint8_t       *WBUFPtrScaleFactorOut;
} BAM_Fftnpt16ix16o_OutCtrlArgs;


extern BAM_KernelHelperFuncDef gBAM_TI_Fftnpt16ix16oHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_Fftnpt16ix16oExecFunc;

extern BAM_KernelInfo gBAM_TI_Fftnpt16ix16oKernel;


typedef enum
{
  BAM_FFT_NPT_16IX16O_INPUT_PORT = 0,
  BAM_FFT_NPT_16IX16O_NUM_INPUT_BLOCKS
} eBAM_FFT_NPT_16IX16O_INPUT_PORTS;

/* There is no output port for this kernel as it modifies the input itsel we are using a dummy port connected to a nul node*/
typedef enum
{
  BAM_FFT_NPT_16IX16O_OUTPUT_PORT = 0,
  BAM_FFT_NPT_16IX16O_NUM_OUTPUT_BLOCKS
} eBAM_FFT_NPT_16IX16O_OUTPUT_PORTS;

#endif /* BAM_FFT_NPT_16IX16O_H_ */

