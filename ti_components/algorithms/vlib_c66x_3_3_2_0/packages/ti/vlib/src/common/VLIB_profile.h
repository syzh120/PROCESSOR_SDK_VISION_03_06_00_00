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
**|        Copyright (c) 2007 - 2015 Texas Instruments Incorporated          |**
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
**|  with devices manufactured by or for TI ('TI Devices').  No hardware     |**
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

#ifndef VLIB_PROFILE_H_
#define VLIB_PROFILE_H_ 1

/* Memory utility includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "VLIB_test.h"

/* Kernel routine type enumeration (must not use explicit numbering) */
#define  vlib_KERNEL_OPT 0             /* Kernel type optimized (C-intrinsics, assembly) */
#define  vlib_KERNEL_CN  1              /* Kernel type natural C */
#define  vlib_KERNEL_CNT 2

/* Global test case index */
extern int    test_index;       /* Index of current active test */
extern int    act_kernel;       /* Active kernel type for test and profile */

/* Profiling defines */
#define vlib_PROFILE_MAX_TESTS     32
#define vlib_PROFILE_MAX_ORDER      4
#define vlib_PROFILE_MAX_MODES      5
#define vlib_PROFILE_FORMULA        0
#define vlib_PROFILE_RANGE          1
#define vlib_PROFILE_FORMULA_RANGE  2

/* Profiling macros */
#ifdef _HOST_BUILD
    #define PROFILE_INIT
    #define PROFILE_READ   0
#else
    #define PROFILE_INIT   TSCL= 0, TSCH=0
    #define PROFILE_READ   _itoll(TSCH, TSCL)
#endif

/* Profiling globals */
extern int         est_test;   /* Use current test in formula estimation */
extern uint64_t    beg_count; /* Begin cycle count for profiling */
extern uint64_t    end_count; /* End cycle count for profiling */
extern uint64_t    overhead;  /* Cycle profiling overhead */
extern uint64_t    cycles[vlib_KERNEL_CNT]; /* Cycle counts for C-natural & optimized */

void VLIB_profile_init (int order, char *kernel_name);
void VLIB_profile_setMode(int mode, int mode_order, char *mode_desc, int finalMode);
void VLIB_formula_add_test (int Ax0, int Ax1, int Ax2, int errorFlag, char *desc, int mode);
void VLIB_skip_test (char *desc);
void VLIB_profile_cycle_report (int reportType, char *formulaInfo, char *rangeInfo);
void initStack(uint32_t SP);
void setStackDepth(void);
uint32_t getSP(void);
void VLIB_stack_memory(void);

/* Profiling start routine */
static inline void VLIB_profile_start (int kernel)
{
    /* Set the active kernel for subsequent calls */
    act_kernel = kernel;

    /* Invalidate the cache */
    VLIB_cache_inval();

    /* Initialize the stack for stack depth profiling */
    initStack(getSP());

    /* Register starting timestamp */
    beg_count = PROFILE_READ;
}

/* Profiling stop (and calculate) routine */
static inline void VLIB_profile_stop (void)
{
    /* Register ending timestamp */
    end_count = PROFILE_READ;

    /* Calculate and store cycles */
    cycles[act_kernel] += end_count - beg_count - overhead;

    /* Analize the stack and register stack depth used */
    setStackDepth();
}

#endif

/* =========================================================================*/
/*  End of file:  VLIB_profile.h                                             */
/* =========================================================================*/

