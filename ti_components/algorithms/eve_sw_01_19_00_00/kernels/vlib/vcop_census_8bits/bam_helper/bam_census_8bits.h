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
 *  @file       bam_census_8bits.h
 *
 *  @brief      This header defines interfaces for integrating census transform kernel
 *              into BAM.
 */

#ifndef BAM_CENSUS_8BITS_H_
#define BAM_CENSUS_8BITS_H_

/* CHECK_MISRA("-20.2")  -> Disable rule 20.2 */
/* Usage of a reserved name for naming a language entity */
/* Deviation allowed because _bam_census_8bits_args is not reserved */
typedef struct _bam_census_8bits_args
{
  uint16_t in_w; /* Must be multiple fo 16 */
  uint16_t in_h; /* for best performance should be multiple of 8 */
  uint8_t winWidth; /* width of the support window, that defines the neighborhood in which census transform is applied around each pixel. */
  uint8_t winHeight; /* height of the support window, that defines the neighborhood in which census transform is applied around each pixel. */
  uint8_t winHorzStep; /* horizontal step between each orientation in the support window. Typically 1 or 2. */
  uint8_t winVertStep; /* vertical step between each orientation in the support window. Typically 1 or 2. */
  uint16_t in_pitch; /* Must be >= in_w + winWidth - 1 and must be even */
  uint16_t out_pitch; /* stride of the output in bytes, must be >= (in_w * codeWordLenBytes) and must be multiple of 4 but not multiple of 32*/
} BAM_Census_8bits_Args;
/*RESET_MISRA("20.2")  -> Reset rule 20.2 */

extern BAM_KernelHelperFuncDef gBAM_TI_census_8bits_HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_census_8bits_ExecFunc;

extern BAM_KernelInfo gBAM_TI_census_8bits_Kernel;

#define BAM_CENSUS_8BITS_INPUT_PORT     0

#define BAM_CENSUS_8BITS_OUTPUT_PORT    0


#endif /* BAM_CENSUS_8BITS_H_ */

