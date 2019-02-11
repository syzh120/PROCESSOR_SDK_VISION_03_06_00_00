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


/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      eve_profile.h                                                      */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*  This file helps perform TSC and SCTM based profiling                    */
/*                                                                          */
/*==========================================================================*/

#ifndef EVE_PROFILE_H
#define EVE_PROFILE_H

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#include "curve_fitting.h"


#define TEST_PRINTF_TYPE_STANDARD 0U
#define TEST_PRINTF_TYPE_UART     1U
#define TEST_PRINTF_TYPE_SPRINTF  2U
#define TEST_PRINTF_TYPE_DUMMY  3U

/*
 Set the actual printf to use.
 Setting to PRINTF_TYPE_SPRINTF will allow a common .lib to be used for virtio and fpga.
*/
#define TEST_PRINTF_TYPE          (TEST_PRINTF_TYPE_STANDARD)

/* Used only for printfs in standalone test files */
void TEST_PRINTF(const char * text, ...);
/* RESET_MISRA("16.1")  -> Reset rule 16.1*/

void profiler_init(void);

void profiler_start(void);

void profiler_end(void);

void print_profile_num(void);

void report_profile_num(char* comp_name, char* statusStr, int img_width, int img_height, char* comments);

void report_memory_usage(char* comp_name, char* comments);

void profiler_deinit(void);

uint32_t profiler_getSP(void);

void profiler_initStack(uint32_t SP);

uint32_t profiler_getStackDepth(void);

void profiler_printStatus(int32_t status);

void profiler_testCaseInfo(int8_t * name, int8_t *desc, uint8_t performanceTestcase);

void profiler_end_print(uint32_t id);

void profiler_performanceParam(uint32_t param);

void report_printAppletInfo(int8_t * name);

#endif /* EVE_PROFILE_H */