/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|        Copyright (c) 2017 Texas Instruments Incorporated                 |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef BAM_VXLIB_MINMAXLOC_I8U_H_
#define BAM_VXLIB_MINMAXLOC_I8U_H_

#include "bam_common.h"

typedef struct
{
    uint32_t minLocCapacity; /* Capacity of minLoc array */
    uint32_t maxLocCapacity; /* Capacity of maxLoc array */

} BAM_VXLIB_minMaxLoc_i8u_params;

typedef struct
{
    VXLIB_bufParams2D_t bufParams[1];
    BAM_VXLIB_minMaxLoc_i8u_params params;

} BAM_VXLIB_minMaxLoc_i8u_Args;

/* Commands used in the BAM_controlNode() function */
#define VXLIB_MINMAXLOC_I8U_CMD_SET_MIN_LOC_PTR 0U /* set the min location output pointer */
#define VXLIB_MINMAXLOC_I8U_CMD_SET_MAX_LOC_PTR 1U /* set the max location output pointer */
#define VXLIB_MINMAXLOC_I8U_CMD_SET_MIN_CNT_PTR 2U /* set the min count output pointer */
#define VXLIB_MINMAXLOC_I8U_CMD_SET_MAX_CNT_PTR 3U /* set the max count output pointer */
#define VXLIB_MINMAXLOC_I8U_CMD_GET_MIN_VAL 4U /* get the output min value */
#define VXLIB_MINMAXLOC_I8U_CMD_GET_MAX_VAL 5U /* get the output max value */

extern BAM_KernelInfo gBAM_VXLIB_minMaxLoc_i8u_kernel;
extern BAM_KernelHelperFuncDef gBAM_VXLIB_minMaxLoc_i8u_helperFunc;
extern BAM_KernelExecFuncDef gBAM_VXLIB_minMaxLoc_i8u_execFunc;

typedef enum
{
    BAM_VXLIB_MINMAXLOC_I8U_INPUT_IMAGE_PORT= 0,
    BAM_VXLIB_MINMAXLOC_I8U_NUM_INPUT_BLOCKS
} eBAM_VXLIB_MINMAXLOC_I8U_INPUT_PORTS;

typedef enum
{
    BAM_VXLIB_MINMAXLOC_I8U_NUM_OUTPUT_BLOCKS = 0
} eBAM_VXLIB_MINMAXLOC_I8U_OUTPUT_PORTS;

void BAM_VXLIB_minMaxLoc_i8u_getKernelInfo(BAM_VXLIB_minMaxLoc_i8u_params *kernelArgs,
                                                     BAM_KernelInfo *kernelInfo);

#endif /* BAM_VXLIB_MINMAXLOC_I8U_H_ */
