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
 *  @file       bam_ncc.h
 *
 *  @brief      This header defines interfaces for integrating normalized cross correlation
 *              into BAM.
 */

#ifndef BAM_NCC_H_
#define BAM_NCC_H_

/* CHECK_MISRA("-20.2")  -> Disable rule 20.2 */
/* Usage of a reserved name for naming a language entity */
/* Deviation allowed because _bam_ncc_args is not reserved */
typedef struct bam_ncc_args
{
    int16_t *pExtTemplate; /* pointer to template image residing in external memory */
    uint16_t templateExtPitch; /* Pitch in external memory of template */
    uint16_t inPitch; /* Must be >= outputWidth + templateWidth - 1 and must be even */
    uint8_t templateWidth; /* width of the 16-bits template */
    uint8_t templateHeight; /* height of the 16-bits template */
    uint16_t outputWidth;
    uint16_t outputHeight;
    uint16_t outPitch; /* stride of the output in number of 32-bits elements*/
    uint8_t qShift; /* Number of bits allocated for the fractional part */
    uint8_t sizeQshift;
} BAM_Ncc_Args;
/*RESET_MISRA("20.2")  -> Reset rule 20.2 */

typedef struct
{
    uint8_t ctlCmdId;
    int16_t *pExtTemplate; /* pointer to template image residing in external memory */
    uint16_t templateExtPitch; /* Pitch in external memory of template */
} BAM_Ncc_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_ncc_HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_ncc_ExecFunc;

extern BAM_KernelInfo gBAM_TI_ncc_Kernel;

#define BAM_NCC_INPUT_PORT     0

#define BAM_NCC_NUMCC_OUTPUT_PORT       0
#define BAM_NCC_DENOMVAR_OUTPUT_PORT    1

/* Macro symbols to initialize member ctlCmdId in BAM_Ncc_CtlArgs */
#define BAM_NCC_CMD_SET_TEMPLATE_PTR 0

#endif /* BAM_NCC_H_ */

