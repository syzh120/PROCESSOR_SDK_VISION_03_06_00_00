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
**|        Copyright (c) 2007 - 2013 Texas Instruments Incorporated          |**
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

#ifndef VLIB_TYPES_H_
#define VLIB_TYPES_H_

/* Define C66x CG compiler */
#define VLIB_CGT6X_COMPILER

#include <stdint.h>

/* C66 types */
typedef double VLIB_D64;          /*!< Double precision floating point */
typedef float VLIB_F32;           /*!< Single precision floating point */
typedef void           *VLIB_PTR; /*!< Void pointer */
typedef unsigned long VLIB_VAL;  /*!< Unsigned long cast value */

/* Fixed point defines */
#define VLIB_MAX_0p16    1
#define VLIB_MAX_4p12    16
#define VLIB_MAX_8p8     256
#define VLIB_MAX_10p5    1024
#define VLIB_MAX_12p4    4096
#define VLIB_MAX_13p2    8192
#define VLIB_MAX_16p16   65536

typedef struct {
    int32_t area;
    int32_t xsum;
    int32_t ysum;

    int32_t xmin;
    int32_t ymin;
    int32_t xmax;
    int32_t ymax;

    int32_t seedx;
    int32_t seedy;

} VLIB_CC;

typedef int32_t VLIB_CCHandle;

typedef enum {
    VLIB_NO_ERROR = 0,
    VLIB_ERR_INPUT_INVALID = 1,
    VLIB_ERR_INPUT_NEGATIVE = 2,
    VLIB_ERR_INPUT_EXCEEDED_RANGE = 3,
    VLIB_ERR_MEMORY_EXCEEDED_BOUNDARY = 4,
    VLIB_ERR_MEMORY_ALLOCATION_FAILURE = 5,
    VLIB_ERR_MEMORY_POINTER_NULL = 6,
    VLIB_ERR_DMA_FAILURE = 7,
    VLIB_ERR_FILE_OPEN_FAILURE = 8,
    VLIB_ERR_FILE_READ_FAILURE = 9,
    VLIB_ERR_FILE_WRITE_FAILURE = 10,
    VLIB_ERR_FILE_CLOSE_FAILURE = 11,
    VLIB_ERR_FILE_FORMAT_FAILURE = 12,
    VLIB_WARNING_LOW_MEMORY = 13,
    VLIB_ERR_NOT_IMPLEMENTED = 14,
    VLIB_ERROR_MAX = 15
} VLIB_STATUS;

#endif

