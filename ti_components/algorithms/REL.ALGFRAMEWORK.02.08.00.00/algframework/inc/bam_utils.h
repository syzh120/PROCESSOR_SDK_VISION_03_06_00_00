/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
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



#ifndef BAM_UTILS_H
#define BAM_UTILS_H

#pragma CHECK_MISRA ("none")
#include <stdlib.h>
#include "cpu.h"
#include <stdint.h>
#pragma RESET_MISRA ("required")

#ifndef HOST_EMULATION
#ifdef CORE_DSP
#if defined (__C7100__)
    #include <c7x.h>
#else
    #include <c6x.h>
#endif
#endif
#endif

#define BAM_PRINTF_MEM_SIZE 1024U
#define PRINTF_TYPE_STANDARD 0U
#define PRINTF_TYPE_UART     1U
#define PRINTF_TYPE_SPRINTF  2U
#define PRINTF_TYPE_DUMMY  3U

#define PRINTF               BAM_printf

/*
 Set the actual printf to use.
 Setting to PRINTF_TYPE_SPRINTF will allow a common .lib to be used for virtio and fpga.
*/
#define PRINTF_TYPE          (PRINTF_TYPE_DUMMY) /* In production code this should be set to PRINTF_TYPE_SPRINTF */

/* CHECK_MISRA("-16.1")  -> Disable rule 16.1  */
/* Function with variable number of arguments */
/* Deviation allowed since these functions are wrapper around printf() function, which accept variable number of arguments  */
void BAM_printf(const char * text, ...);

/* Used only for printfs in standalone test files */
/* RESET_MISRA("16.1")  -> Reset rule 16.1*/

extern char gBAM_memPrintfArr[BAM_PRINTF_MEM_SIZE];

/* Profiling macros */
#ifdef HOST_EMULATION
    #define BAM_PROFILE_INIT
    #define BAM_PROFILE_READ   0
#else
    #ifdef CORE_DSP
        #if defined (__C7100__)
            #define BAM_PROFILE_INIT   __TSC = 0
            #define BAM_PROFILE_READ   __TSC
        #else
            #define BAM_PROFILE_INIT   TSCL= 0, TSCH=0
            #define BAM_PROFILE_READ   _itoll(TSCH, TSCL)
        #endif
    #else
        #define BAM_PROFILE_INIT   _tsc_start()
        #define BAM_PROFILE_READ   _tsc_gettime()
    #endif
#endif

#endif

