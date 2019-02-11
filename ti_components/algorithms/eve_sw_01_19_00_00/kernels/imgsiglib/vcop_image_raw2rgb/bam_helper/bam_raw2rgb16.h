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
 * @file bam_raw2rgb.h
 *
 * @brief
 *
 *
 * @version 0.0 (March 2017) : Base version.
 */

#ifndef BAM_RAW2RGB16_H_
#define BAM_RAW2RGB16_H_

typedef struct bam_raw2rgb16_args_s
{
    uint16_t blk_width;
    uint16_t blk_height;
    uint16_t input_stride;
    uint16_t outputG_stride;
    uint16_t outputRB_stride;
    uint16_t bayer_pattern; /* 0: gbrg, 1: grbg, 2: bggr, 3: rggb */
} BAM_Raw2rgb16_Args;

/*
 * Public kernel control structure interface exposed to the kernel consumer/integrator
 */
typedef struct
{
    uint8_t ctlCmdId;
} BAM_Raw2rgb16_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_raw2rgb16HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_raw2rgb16ExecFunc;

extern BAM_KernelInfo gBAM_TI_raw2rgb16Kernel;

typedef enum {
  BAM_RAW2RGB_CMD_SET_ARGS,
  BAM_RAW2RGB_CMD_GET_ARGS
} BAM_RAW2RGB_CTL_CMD;


#define BAM_RAW2RGB_INPUT_PORT  0

#define BAM_RAW2RGB_OUTPUT_PORT_R 0
#define BAM_RAW2RGB_OUTPUT_PORT_G 1
#define BAM_RAW2RGB_OUTPUT_PORT_B 2

#endif /* ISP_BAM_RAW2RGB_H_ */

