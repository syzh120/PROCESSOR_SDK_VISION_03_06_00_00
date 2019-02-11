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

#ifndef VLIB_MEMORY_H_
#define VLIB_MEMORY_H_ 1

#include <stdio.h>
#include <string.h>
#include "VLIB_types.h"
#include "VLIB_profile.h"

/* Handle COFF/ELF for linker cmd file symbols */
#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#define data_size _data_size
#endif

/* Defines for types of test sequence data */
#define CONSTANT             0
#define SEQUENTIAL           1
#define SEQUENTIAL_NEGATIVE  2
#define RANDOM               3
#define STATIC               4
#define CUSTOM               5
#define FILEIO               6
#define CHECKERBOARD         7
#define STRIPES              8
#define DOTS                 9

/* Used in linker CMD file to determine code/data size */
extern uint32_t    kernel_size;
extern uint32_t    data_size;

/* Memory handling utilities in VLIB_memory.c */
extern void VLIB_copy_S32_to_S08  (int8_t *restrict dst, int32_t *restrict src, int32_t elements);
extern void VLIB_copy_S32_to_S16  (int16_t *restrict dst, int32_t *restrict src, int32_t elements);
extern int32_t  VLIB_compare_mem      (VLIB_PTR a, VLIB_PTR b, int32_t n);

/* 2D Memory handling utilities in VLIB_memory.c */
void fillConst(uint32_t val, void *array, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize);
void fillSeq(void *array, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize);
void fillSeqNeg(void *array, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize);
void fillRand(void *array, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize);
void copyRoi(void *arrayDst, void *arraySrc, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize);
void VLIB_fillBuffer(uint8_t testPattern, uint8_t constFill, void *dest, void *src,
                     uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize, char *testPatternType);

uint32_t compare(uint8_t *dsp_output, uint8_t *natc_output, uint16_t width, uint16_t height, uint16_t stride);


/* Memory clear (to zero) utility */
static inline void VLIB_clear_memory (VLIB_PTR ptr, int32_t size)
{
    memset(ptr, 0, size);
}

/* int32_t to int32_t memory copy utility */
static inline void VLIB_copy_S32_to_S32 (int32_t *restrict dst, int32_t *restrict src, int32_t elements)
{
    memcpy(dst, src, elements * sizeof(int32_t));
}

/* int32_t to uint8_t memory copy utility */
static inline void VLIB_copy_S32_to_U08 (uint8_t *restrict dst, int32_t *restrict src, int32_t elements)
{
    VLIB_copy_S32_to_S08((int8_t *) dst, src, elements);
}

/* int32_t to uint16_t memory copy utility */
static inline void VLIB_copy_S32_to_U16 (uint16_t *restrict dst, int32_t *restrict src, int32_t elements)
{
    VLIB_copy_S32_to_S16((int16_t *) dst, src, elements);
}

/* int32_t to uint32_t memory copy utility */
static inline void VLIB_copy_S32_to_U32 (uint32_t *restrict dst, int32_t *restrict src, int32_t elements)
{
    VLIB_copy_S32_to_S32((int32_t *) dst, src, elements);
}

/* Display memory reqirements */
static inline void VLIB_kernel_memory (void)
{
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
#if !defined(__ONESHOTTEST) && !defined(_HOST_BUILD)
    /* Provide memory information */
    printf("Memory Usage:\n");
    printf("  Code size:  %9d bytes\n", &kernel_size);
    printf("  Data size:  %9d bytes\n", &data_size);
#endif /* __ONESHOTTEST */
    VLIB_stack_memory();
}

/* Run-time initialation of the fast heap for VLIB
 * Called only if heap is linked into L2SRAM */
uint32_t VLIB_meminit(uint32_t size);

/* Following should be called to allocate buffers passed to VLIB functions
 * for each test vector */
void *VLIB_memalign(size_t alignment, size_t size);
void *VLIB_malloc(size_t size);

/* Following should be called to de-allocate buffers passed to VLIB functions
 * for each test vector */
void  VLIB_align_free(void *ptr);
void  VLIB_free(void *ptr);
int32_t VLIB_get_heap_size (void);
void  VLIB_memError(char *fn);

#endif  /* VLIB_MEMORY_H_ */

/* =========================================================================*/
/*  End of file:  VLIB_memory.h                                             */
/* =========================================================================*/

