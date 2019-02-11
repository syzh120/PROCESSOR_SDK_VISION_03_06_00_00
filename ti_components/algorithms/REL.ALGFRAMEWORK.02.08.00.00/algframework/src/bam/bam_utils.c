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



#pragma CHECK_MISRA ("none")
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>  
#ifndef HOST_EMULATION
#include <_lock.h>
#endif
#include "cpu.h"
#include "bam_utils.h"

#pragma RESET_MISRA ("required")

#pragma CHECK_MISRA ("none")
#include "starterware.h"
#if PRINTF_TYPE == PRINTF_TYPE_UART
#include "zebu_uart/inc/uartlib.h"
#endif
#pragma RESET_MISRA ("required")

/*
 A sample allocator defined
*/
char gBAM_memPrintfArr[BAM_PRINTF_MEM_SIZE] = {0};

/* CHECK_MISRA("-16.1")  -> Disable rule 16.1  */
/* Function with variable number of arguments */
/* Deviation allowed since these functions are wrapper around printf() function, which accept variable number of arguments  */

/* CHECK_MISRA("-20.9")  -> Disable rule 20.9  */
/* Use of input/output library stdio.h in production code */
/* Deviation allowed since these functions are only enabled if PRINTF_TYPE == PRINTF_TYPE_STANDARD, which should be unset in production code  */

/* CHECK_MISRA("-20.1 - 20.5 - 20.6 - 20.7 - 20.8")  -> Disable rules  */
/* Unsafe macro stdout is used */
/* Deviation allowed since stdout is only used if PRINTF_TYPE == PRINTF_TYPE_STANDARD, which should be unset in production code  */

void BAM_printf(const char * text, ...)
{
#if PRINTF_TYPE == PRINTF_TYPE_STANDARD
    va_list argptr;
    va_start(argptr, text);
    vfprintf(stdout, text, argptr);
    va_end(argptr);
    fflush(stdout);
#elif PRINTF_TYPE == PRINTF_TYPE_UART
    va_list argptr;
    va_start(argptr, text);
    vuart1_write_formated(text, argptr);
    va_end(argptr);
#else
    va_list argptr;
    va_start(argptr, text);
    memset(gBAM_memPrintfArr, 0, sizeof(gBAM_memPrintfArr));
    vsprintf(gBAM_memPrintfArr, text, argptr);
    va_end(argptr);
#endif
}

/* RESET_MISRA("16.1")  -> Reset rule 16.1*/
/* RESET_MISRA("20.9")  -> Reset rule 20.9*/
/* RESET_MISRA("-20.1 - 20.5 - 20.6 - 20.7 - 20.8")  -> Reset rules */
