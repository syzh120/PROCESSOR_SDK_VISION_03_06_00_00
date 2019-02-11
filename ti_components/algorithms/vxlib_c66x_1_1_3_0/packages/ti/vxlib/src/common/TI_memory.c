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
**|         Copyright (c) 2007 - 2017 Texas Instruments Incorporated         |**
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

#include "TI_memory.h"
#include "TI_test.h"
#include "TI_profile.h"

#if defined(_HOST_BUILD)
#include <malloc.h>
#endif

/* Heap global variables */
#if !defined(_HOST_BUILD)

/* Handle COFF/ELF for linker cmd file symbols */
#if defined(__TI_EABI__)
#define sram_start _sram_start
#endif

/* These extern variables are created by the linker command files */
extern uint32_t    sram_start;

static void   *fast_heap_start;
static void   *fast_heap_end;

#if defined(HEAP_L2SRAM)
static uint32_t    fast_heap_size;
static void       *fast_heap_front;
#endif

/* The linker will place this section in L2SRAM after linked section, if any
 * Therefore, the address of this variable indicates the first available
 * address in the L2SRAM for the fast heap to use */
#pragma DATA_SECTION(sram_start_placeholder, ".sram_start")
static uint8_t    sram_start_placeholder;

#endif /* !defined(_HOST_BUILD) */


uint32_t TI_meminit(uint32_t size)
{
    uint32_t    status = 0;

#if !defined(_HOST_BUILD)
    fast_heap_start =  (void *)(size_t)&sram_start_placeholder;
    fast_heap_end   = (void *)((size_t)&sram_start + size * 1024);
    if( fast_heap_start > fast_heap_end ) {
        status = 1; /* ERROR: There is no room in the L2SRAM. */
    }
#if defined(HEAP_L2SRAM)
    else {
        fast_heap_size = (size_t)fast_heap_end - (size_t)fast_heap_start;
        fast_heap_front = fast_heap_start;
    }
#endif
#endif
    return (status);
}

void *TI_memalign(size_t alignment, size_t size)
{
#if !defined(_HOST_BUILD) && defined(HEAP_L2SRAM)
    size_t    temp_start = ((size_t)fast_heap_front + (alignment - 1)) & ~(size_t)(alignment - 1);

    if((temp_start + size) > (size_t)fast_heap_end ) {
        temp_start = 0;
    } else {
        fast_heap_front = (void *)(temp_start + size);
    }
    return ((void *)temp_start);
#else
    return (memalign(alignment, size));
#endif
}

void *TI_malloc(size_t size)
{
#if !defined(_HOST_BUILD) && defined(HEAP_L2SRAM)
    size_t    temp_start = ((size_t)fast_heap_front + (sizeof(long double) - 1)) & ~(size_t)(sizeof(long double) - 1);

    if((temp_start + size) > (size_t)fast_heap_end ) {
        temp_start = 0;
    } else {
        fast_heap_front = (void *)(temp_start + size);
    }
    return ((void *)temp_start);
#else
    return (malloc(size));
#endif
}

void TI_align_free(void *ptr)
{
#if !defined(_HOST_BUILD) && defined(HEAP_L2SRAM)
    fast_heap_front = fast_heap_start;
#else
    align_free(ptr);
#endif
}

void TI_free(void *ptr)
{
#if !defined(_HOST_BUILD) && defined(HEAP_L2SRAM)
    fast_heap_front = fast_heap_start;
#else
    free(ptr);
#endif
}

int32_t TI_get_heap_size (void)
{
#if !defined(_HOST_BUILD) && defined(HEAP_L2SRAM)
    return (fast_heap_size);
#else
    return (0);
#endif
}

void  TI_memError(char *fn)
{
    printf("%s:\n    ERROR: This test can not run given the build-time configuration of L2SRAM.\n", fn);
}

/* Common Memory Utility:
 *
 *    TI_compare_mem
 *
 */
int32_t TI_compare_mem (void *a, void *b, int32_t size)
{
    int32_t    test_result = (int32_t) TI_TEST_KERNEL_PASS;

    /* Compare memory (byte-based) */
    if( memcmp(a, b, size)) {
        TI_test_assert((act_kernel == TI_PROFILE_KERNEL_OPT ||
                        act_kernel == TI_PROFILE_KERNEL_CN), "Invalid kernel type");

        /* Provide failure message */
        if( act_kernel == TI_PROFILE_KERNEL_OPT ) {
            printf("\nFailure: Output - Optimized:  Case #%d\n", test_index);
            test_result = (int32_t) TI_TEST_KERNEL_FAIL;
        } else {
            printf("\nFailure: Output - Natural C:  Case #%d\n", test_index);
            test_result = (int32_t) TI_TEST_KERNEL_FAIL;
        }
    }

    /* Return PASS/FAIL */
    return (test_result);
}

/* Common Memory Utility:
 *
 *    TI_compare_mem_2D
 *
 */
int32_t  TI_compare_mem_2D(void *a, void *b, int32_t tolerance, int32_t wrap_exception, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize)
{
    int32_t   test_result = (int32_t) TI_TEST_KERNEL_PASS;
    uint32_t  row, col;
    uint8_t   warn  = 0;

    for( row= 0; row < height; row++ ) {
        for( col=0; col < width; col++ ) {
            int32_t valA, valB;
            int32_t offset;

            offset = (row * (stride / elementSize)) + col;

            if( elementSize == 1 ) {
                uint8_t   *ptrA = (uint8_t *)a;
                uint8_t   *ptrB = (uint8_t *)b;

                valA = ptrA[offset];
                valB = ptrB[offset];
            }
            else if( elementSize == 2 ) {
                uint16_t   *ptrA = (uint16_t *)a;
                uint16_t   *ptrB = (uint16_t *)b;

                valA = ptrA[offset];
                valB = ptrB[offset];
            }
            else if( elementSize == 4 ) {
                uint32_t   *ptrA = (uint32_t *)a;
                uint32_t   *ptrB = (uint32_t *)b;

                valA = ptrA[offset];
                valB = ptrB[offset];
            }
            else if( elementSize == 8 ) {
                uint64_t   *ptrA = (uint64_t *)a;
                uint64_t   *ptrB = (uint64_t *)b;

                valA = ptrA[offset];
                valB = ptrB[offset];
            }
            else {
                printf("\nUnsupported data type in TI_compare_mem_2D.\n");
            }

            if(valA != valB)
            {
                if(tolerance) {
                    int32_t diff = abs(valA - valB);
                    if((diff > tolerance) && (diff != wrap_exception)) {
                        printf("\nFailure at: row=%d, col=%d, val1=%d, val2=%d\n", row, col, valA, valB);
                        return(TI_TEST_KERNEL_FAIL);
                    } else if(warn == 0) {
                        warn = 1;
                        printf("\nWarning at: row=%d, col=%d, val1=%d, val2=%d\n", row, col, valA, valB);
                    }
                } else {
                    printf("\nFailure at: row=%d, col=%d, val1=%d, val2=%d\n", row, col, valA, valB);
                    return(TI_TEST_KERNEL_FAIL);
                }
            }
        }
    }

    return test_result;
}

/* Common Memory Utility:
 *
 *    TI_compare_mem_3D
 *
 */
int32_t  TI_compare_mem_3D(void *a, void *b, int32_t tolerance, int32_t wrap_exception, uint16_t dim_x, uint16_t dim_y, uint16_t dim_z, uint16_t stride_y, uint16_t stride_z, uint8_t elementSize)
{
    int32_t   test_result = (int32_t) TI_TEST_KERNEL_PASS;
    uint32_t  ctrX, ctrY, ctrZ;
    uint8_t   warn  = 0;

    for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
        for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
            for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                int32_t valA, valB;
                int32_t offset;

                offset = (ctrZ * (stride_z / elementSize)) + (ctrY * (stride_y / elementSize)) + ctrX;

                if( elementSize == 1 ) {
                    uint8_t   *ptrA = (uint8_t *)a;
                    uint8_t   *ptrB = (uint8_t *)b;

                    valA = ptrA[offset];
                    valB = ptrB[offset];
                }
                else if( elementSize == 2 ) {
                    uint16_t   *ptrA = (uint16_t *)a;
                    uint16_t   *ptrB = (uint16_t *)b;

                    valA = ptrA[offset];
                    valB = ptrB[offset];
                }
                else if( elementSize == 4 ) {
                    uint32_t   *ptrA = (uint32_t *)a;
                    uint32_t   *ptrB = (uint32_t *)b;

                    valA = ptrA[offset];
                    valB = ptrB[offset];
                }
                else if( elementSize == 8 ) {
                    uint64_t   *ptrA = (uint64_t *)a;
                    uint64_t   *ptrB = (uint64_t *)b;

                    valA = ptrA[offset];
                    valB = ptrB[offset];
                }
                else {
                    printf("\nUnsupported data type in TI_compare_mem_3D.\n");
                }

                if(valA != valB)
                {
                    if(tolerance) {
                        int32_t diff = abs(valA - valB);
                        if((diff > tolerance) && (diff != wrap_exception)) {
                            printf("\nFailure at: z=%d, y=%d, x=%d, val1=%d, val2=%d\n", ctrZ, ctrY, ctrX, valA, valB);
                            return(TI_TEST_KERNEL_FAIL);
                        } else if(warn == 0) {
                            warn = 1;
                            printf("\nWarning at: z=%d, y=%d, x=%d, val1=%d, val2=%d\n", ctrZ, ctrY, ctrX, valA, valB);
                        }
                    } else {
                        printf("\nFailure at: z=%d, y=%d, x=%d, val1=%d, val2=%d\n", ctrZ, ctrY, ctrX, valA, valB);
                        return(TI_TEST_KERNEL_FAIL);
                    }
                }
            }
        }
    }

    return test_result;
}

/* Common Memory Utility:
 *
 *    TI_compare_mem_2D
 *
 */
int32_t  TI_compare_mem_2D_float(void *a, void *b, double log10tolerance, double abstolerance, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize)
{
    int32_t   test_result = (int32_t) TI_TEST_KERNEL_PASS;
    uint32_t  row, col;
    uint8_t   warn  = 0;

    for( row= 0; row < height; row++ ) {
        for( col=0; col < width; col++ ) {
            double valA, valB;
            int32_t offset;

            offset = (row * (stride / elementSize)) + col;

            if( elementSize == 4 ) {
                float   *ptrA = (float *)a;
                float   *ptrB = (float *)b;

                valA = ptrA[offset];
                valB = ptrB[offset];
            }
            else if( elementSize == 8 ) {
                double   *ptrA = (double *)a;
                double   *ptrB = (double *)b;

                valA = ptrA[offset];
                valB = ptrB[offset];
            }
            else{
                printf("\nUnsupported data type in TI_compare_mem_2D_float.\n");
            }

            if(valA != valB)
            {
                if(log10tolerance) {
                    double log10diff = fabs(log10(valB/valA));
                    double absdiff = fabs(valB-valA);
                    if((log10diff > log10tolerance) && (absdiff > abstolerance)) {
                        printf("\nFailure at: row=%d, col=%d, val1=%f, val2=%f\n", row, col, valA, valB);
                        return(TI_TEST_KERNEL_FAIL);
                    } else if(warn == 0) {
                        warn = 1;
                        printf("\nWarning at: row=%d, col=%d, val1=%f, val2=%f\n", row, col, valA, valB);
                    }
                } else if(abstolerance) {
                    double absdiff = fabs(valB-valA);
                    if(absdiff > abstolerance) {
                        printf("\nFailure at: row=%d, col=%d, val1=%f, val2=%f\n", row, col, valA, valB);
                        return(TI_TEST_KERNEL_FAIL);
                    } else if(warn == 0) {
                        warn = 1;
                        printf("\nWarning at: row=%d, col=%d, val1=%f, val2=%f\n", row, col, valA, valB);
                    }
                } else {
                    printf("\nFailure at: row=%d, col=%d, val1=%f, val2=%f\n", row, col, valA, valB);
                    return(TI_TEST_KERNEL_FAIL);
                }
            }
        }
    }

    return test_result;
}

/* Common Memory Utility:
 *
 *    TI_compare_mem_3D
 *
 */
int32_t  TI_compare_mem_3D_float(void *a, void *b, double log10tolerance, double abstolerance, uint16_t dim_x, uint16_t dim_y, uint16_t dim_z, uint16_t stride_y, uint16_t stride_z, uint8_t elementSize)
{
    int32_t   test_result = (int32_t) TI_TEST_KERNEL_PASS;
    uint32_t  ctrX, ctrY, ctrZ;
    uint8_t   warn  = 0;

    for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
        for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
            for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                double valA, valB;
                int32_t offset;

                offset = (ctrZ * (stride_z / elementSize)) + (ctrY * (stride_y / elementSize)) + ctrX;

                if( elementSize == 4 ) {
                    float   *ptrA = (float *)a;
                    float   *ptrB = (float *)b;

                    valA = ptrA[offset];
                    valB = ptrB[offset];
                }
                else if( elementSize == 8 ) {
                    double   *ptrA = (double *)a;
                    double   *ptrB = (double *)b;

                    valA = ptrA[offset];
                    valB = ptrB[offset];
                }
                else{
                    printf("\nUnsupported data type in TI_compare_mem_3D_float.\n");
                }

                if(valA != valB)
                {
                    if(log10tolerance) {
                        double log10diff = fabs(log10(valB/valA));
                        double absdiff = fabs(valB-valA);
                        if((log10diff > log10tolerance) && (absdiff > abstolerance)) {
                            printf("\nFailure at: z=%d, y=%d, x=%d, val1=%f, val2=%f\n", ctrZ, ctrY, ctrX, valA, valB);
                            return(TI_TEST_KERNEL_FAIL);
                        } else if(warn == 0) {
                            warn = 1;
                            printf("\nWarning at: z=%d, y=%d, x=%d, val1=%f, val2=%f\n", ctrZ, ctrY, ctrX, valA, valB);
                        }
                    } else if(abstolerance) {
                        double absdiff = fabs(valB-valA);
                        if(absdiff > abstolerance) {
                            printf("\nFailure at: z=%d, y=%d, x=%d, val1=%f, val2=%f\n", ctrZ, ctrY, ctrX, valA, valB);
                            return(TI_TEST_KERNEL_FAIL);
                        } else if(warn == 0) {
                            warn = 1;
                            printf("\nWarning at: z=%d, y=%d, x=%d, val1=%f, val2=%f\n", ctrZ, ctrY, ctrX, valA, valB);
                        }
                    } else {
                        printf("\nFailure at: z=%d, y=%d, x=%d, val1=%f, val2=%f\n", ctrZ, ctrY, ctrX, valA, valB);
                        return(TI_TEST_KERNEL_FAIL);
                    }
                }
            }
        }
    }

    return test_result;
}

/* 2D Memory Utility:
 *
 *    fillConst
 *
 */
void fillConst(uint32_t val, void *array, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize)
{
    uint32_t    row, col;

    if( elementSize == 1 ) {
        uint8_t   *ptr = (uint8_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride + col]= val;
            }
        }
    } else if( elementSize == 2 ) {
        uint16_t   *ptr = (uint16_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 2 + col]= val;
            }
        }
    } else if( elementSize == 4 ) {
        uint32_t   *ptr = (uint32_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 4 + col]= val;
            }
        }
    } else if( elementSize == 8 ) {
        uint64_t   *ptr = (uint64_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 8 + col]= val;
            }
        }
    } else {
        printf("\nUnsupported data type in fillConst.\n");
    }
}

/* 3D Memory Utility:
 *
 *    fillConst3D
 *
 */
void fillConst3D(uint32_t val, void *array, uint16_t dim_x, uint16_t dim_y, uint16_t dim_z, uint16_t stride_y, uint16_t stride_z, uint8_t elementSize)
{
    uint32_t  ctrX, ctrY, ctrZ;

    if( elementSize == 1 ) {
        uint8_t   *ptr = (uint8_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX]= val;
                }
            }
        }

    } else if( elementSize == 2 ) {
        uint16_t   *ptr = (uint16_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/2) + (ctrY * stride_y/2) + ctrX]= val;
                }
            }
        }

    } else if( elementSize == 4 ) {
        uint32_t   *ptr = (uint32_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/4) + (ctrY * stride_y/4) + ctrX]= val;
                }
            }
        }
    } else if( elementSize == 8 ) {
        uint64_t   *ptr = (uint64_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/8) + (ctrY * stride_y/8) + ctrX]= val;
                }
            }
        }
    } else {
        printf("\nUnsupported data type in fillConst3D.\n");
    }
}

/* 2D Memory Utility:
 *
 *    fillSeq
 *
 */
void fillSeq(void *array, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize)
{
    uint32_t    row, col;

    if( elementSize == 1 ) {
        uint8_t   *ptr = (uint8_t *)array;
        uint8_t    val= 0;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride + col]= val++;
            }
        }
    } else if( elementSize == 2 ) {
        uint16_t   *ptr = (uint16_t *)array;
        uint16_t    val= 0;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 2 + col]= val++;
            }
        }
    } else if( elementSize == 4 ) {
        uint32_t   *ptr = (uint32_t *)array;
        uint32_t    val= 0;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 4 + col]= val++;
            }
        }
    } else if( elementSize == 8 ) {
        uint64_t   *ptr = (uint64_t *)array;
        uint64_t    val= 0;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 8 + col]= val++;
            }
        }
    } else {
        printf("\nUnsupported data type in fillSeq.\n");
    }
}

/* 3D Memory Utility:
 *
 *    fillSeq3D
 *
 */
void fillSeq3D(void *array, uint16_t dim_x, uint16_t dim_y, uint16_t dim_z, uint16_t stride_y, uint16_t stride_z, uint8_t elementSize)
{
    uint32_t  ctrX, ctrY, ctrZ;

    if( elementSize == 1 ) {
        uint8_t   *ptr = (uint8_t *)array;
        uint8_t    val= 0;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX]= val++;
                }
            }
        }
    } else if( elementSize == 2 ) {
        uint16_t   *ptr = (uint16_t *)array;
        uint16_t    val= 0;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/2) + (ctrY * stride_y/2) + ctrX]= val++;
                }
            }
        }
    } else if( elementSize == 4 ) {
        uint32_t   *ptr = (uint32_t *)array;
        uint32_t    val= 0;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/4) + (ctrY * stride_y/4) + ctrX]= val++;
                }
            }
        }
    } else if( elementSize == 8 ) {
        uint64_t   *ptr = (uint64_t *)array;
        uint64_t    val= 0;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/8) + (ctrY * stride_y/8) + ctrX]= val++;
                }
            }
        }
    } else {
        printf("\nUnsupported data type in fillSeq3D.\n");
    }
}

/* 2D Memory Utility:
 *
 *    fillSeqNeg
 *
 */
void fillSeqNeg(void *array, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize)
{
    uint32_t    row, col;

    if( elementSize == 1 ) {
        int8_t   *ptr = (int8_t *)array;
        int8_t    val= 0;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride + col]= val--;
            }
        }
    } else if( elementSize == 2 ) {
        int16_t   *ptr = (int16_t *)array;
        int16_t    val= 0;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 2 + col]= val--;
            }
        }
    } else if( elementSize == 4 ) {
        int32_t   *ptr = (int32_t *)array;
        int32_t    val= 0;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 4 + col]= val--;
            }
        }
    } else if( elementSize == 8 ) {
        int64_t   *ptr = (int64_t *)array;
        int64_t    val= 0;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 8 + col]= val--;
            }
        }
    } else {
        printf("\nUnsupported data type in fillSeqNeg.\n");
    }
}

/* 3D Memory Utility:
 *
 *    fillSeqNeg3D
 *
 */
void fillSeqNeg3D(void *array, uint16_t dim_x, uint16_t dim_y, uint16_t dim_z, uint16_t stride_y, uint16_t stride_z, uint8_t elementSize)
{
    uint32_t  ctrX, ctrY, ctrZ;

    if( elementSize == 1 ) {
        uint8_t   *ptr = (uint8_t *)array;
        uint8_t    val= 0;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX]= val--;
                }
            }
        }
    } else if( elementSize == 2 ) {
        uint16_t   *ptr = (uint16_t *)array;
        uint16_t    val= 0;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/2) + (ctrY * stride_y/2) + ctrX]= val--;
                }
            }
        }
    } else if( elementSize == 4 ) {
        uint32_t   *ptr = (uint32_t *)array;
        uint32_t    val= 0;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/4) + (ctrY * stride_y/4) + ctrX]= val--;
                }
            }
        }
    } else if( elementSize == 8 ) {
        uint64_t   *ptr = (uint64_t *)array;
        uint64_t    val= 0;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/8) + (ctrY * stride_y/8) + ctrX]= val--;
                }
            }
        }
    } else {
        printf("\nUnsupported data type in fillSeqNeg3D.\n");
    }
}

/* 2D Memory Utility:
 *
 *    copyRoi
 *
 */
void copyRoi(void *arrayDst, void *arraySrc, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize)
{
    uint32_t    row, col;

    if( elementSize == 1 ) {
        uint8_t   *dst = (uint8_t *)arrayDst;
        uint8_t   *src = (uint8_t *)arraySrc;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                dst[row * stride + col]= src[row * width + col];
            }
        }
    } else if( elementSize == 2 ) {
        uint16_t   *dst = (uint16_t *)arrayDst;
        uint16_t   *src = (uint16_t *)arraySrc;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                dst[row * stride / 2 + col]= src[row * width + col];
            }
        }
    } else if( elementSize == 4 ) {
        uint32_t   *dst = (uint32_t *)arrayDst;
        uint32_t   *src = (uint32_t *)arraySrc;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                dst[row * stride / 4 + col]= src[row * width + col];
            }
        }
    } else if( elementSize == 8 ) {
        uint64_t   *dst = (uint64_t *)arrayDst;
        uint64_t   *src = (uint64_t *)arraySrc;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                dst[row * stride / 8 + col]= src[row * width + col];
            }
        }
    } else {
        printf("\nUnsupported data type in copyRoi.\n");
    }
}

/* 3D Memory Utility:
 *
 *    copyRoi3D
 *
 */
void copyRoi3D(void *arrayDst, void *arraySrc, uint16_t dim_x, uint16_t dim_y, uint16_t dim_z, uint16_t stride_y, uint16_t stride_z, uint8_t elementSize)
{
    uint32_t  ctrX, ctrY, ctrZ;

    if( elementSize == 1 ) {
        uint8_t   *dst = (uint8_t *)arrayDst;
        uint8_t   *src = (uint8_t *)arraySrc;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    dst[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX]= src[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX];
                }
            }
        }
    } else if( elementSize == 2 ) {
        uint16_t   *dst = (uint16_t *)arrayDst;
        uint16_t   *src = (uint16_t *)arraySrc;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    dst[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX]= src[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX];
                }
            }
        }
    } else if( elementSize == 4 ) {
        uint32_t   *dst = (uint32_t *)arrayDst;
        uint32_t   *src = (uint32_t *)arraySrc;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    dst[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX]= src[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX];
                }
            }
        }
    } else if( elementSize == 8 ) {
        uint64_t   *dst = (uint64_t *)arrayDst;
        uint64_t   *src = (uint64_t *)arraySrc;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    dst[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX]= src[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX];
                }
            }
        }
    } else {
        printf("\nUnsupported data type in copyRoi3D.\n");
    }
}

/* 2D Memory Utility:
 *
 *    fillRand
 *
 */

void fillRand(void *array, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize)
{
    uint32_t row, col;

    if( elementSize == 1 ) {
        uint8_t   *ptr = (uint8_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride + col]= rand();
            }
        }
    } else if( elementSize == 2 ) {
        uint16_t   *ptr = (uint16_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 2 + col]= rand();
            }
        }
    } else if( elementSize == 4 ) {
        uint32_t   *ptr = (uint32_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 4 + col]= rand();
            }
        }
    } else if( elementSize == 8 ) {
        uint32_t   *ptr = (uint32_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 8 + col]= rand();
            }
        }
    } else {
        printf("\nUnsupported data type in fillRand.\n");
    }
}

void fillRandSigned(void *array, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize)
{
   uint32_t    row, col;
   
   // RAND_MAX is assumed to be equal to 32767 == SHRT_MAX
   // rand effectively produces 15 random bits, we want elementSize*8 random bits
   
   if( elementSize == 1 ) {
      int8_t   *ptr = (int8_t *)array;
      
      for( row= 0; row < height; row++ ) {
         for( col=0; col < width; col++ ) {
            ptr[row * stride + col]= rand();
         }
      }
   } else if( elementSize == 2 ) {
      int16_t   *ptr = (int16_t *)array;
      
      for( row= 0; row < height; row++ ) {
         for( col=0; col < width; col++ ) {
            // bits                         [15:1]          [0]
            ptr[row * stride / 2 + col]= (rand() << 1) | (rand() & 0x00000001);
         }
      }
   } else if( elementSize == 4 ) {
      int32_t   *ptr = (int32_t *)array;
      
      for( row= 0; row < height; row++ ) {
         for( col=0; col < width; col++ ) {
            // bits                        [31:17]            [16:2]            [1:0]
            ptr[row * stride / 4 + col]= (rand() << 17) | (rand() << 2) | (rand() & 0x00000003);
         }
      }
   } else if( elementSize == 8 ) {
      int64_t   *ptr = (int64_t *)array;
      int64_t    temp = 0;
      
      for( row= 0; row < height; row++ ) {
         for( col=0; col < width; col++ ) {
            // bits           [63:49]            [48:34]         [33:19]       [18:4]        [3:0]
            temp = (((int64_t)rand()) <<  49) | (((int64_t)rand()) << 34) | (((int64_t)rand()) << 19) | (((int64_t)rand()) << 4) | (((int64_t)rand()) & 0x000000000000000F);
            ptr[row * stride / 8 + col]= temp;
         }
      }
   } else {
      printf("\nUnsupported data type in fillRandSigned.\n");
   }
}

/* 3D Memory Utility:
 *
 *    fillRand3D
 *
 */
void fillRand3D(void *array, uint16_t dim_x, uint16_t dim_y, uint16_t dim_z, uint16_t stride_y, uint16_t stride_z, uint8_t elementSize)
{
    uint32_t  ctrX, ctrY, ctrZ;

    if( elementSize == 1 ) {
        uint8_t   *ptr = (uint8_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z) + (ctrY * stride_y) + ctrX]= rand();
                }
            }
        }
    } else if( elementSize == 2 ) {
        uint16_t   *ptr = (uint16_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/2) + (ctrY * stride_y/2) + ctrX]= rand();
                }
            }
        }

    } else if( elementSize == 4 ) {
        uint32_t   *ptr = (uint32_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/4) + (ctrY * stride_y/4) + ctrX]= rand();
                }
            }
        }
    } else if( elementSize == 8 ) {
        uint64_t   *ptr = (uint64_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/8) + (ctrY * stride_y/8) + ctrX]= rand();
                }
            }
        }
    } else {
        printf("\nUnsupported data type in fillRand3D.\n");
    }
}

static uint64_t state01 = 0x0000000100000002;
static uint64_t state23 = 0x0000000300000004;

#define A (0x41C64E6D)          //1103515245
#define C (0x0000303900003039)  //12345
#define M (0x7FFFFFFF7FFFFFFF)  //2^31 - 1

#define UPDATE_STATE()                                               \
{                                                                    \
    uint64_t mul01 = _itoll(_loll(state01) * A, _hill(state01) * A); \
    uint64_t mul23 = _itoll(_loll(state23) * A, _hill(state23) * A); \
                                                                     \
    uint64_t add01 = _dadd(mul01, C);                                \
    uint64_t add23 = _dadd(mul23, C);                                \
                                                                     \
    state01 = add01 & M;                                             \
    state23 = add23 & M;                                             \
}

/* 2D Memory Utility:
 *
 *    fillRandFast
 *
 */

void fillRandFast(void *array, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize)
{
    uint32_t row, col;
    int32_t count = (width >> 2) << 2;
    
    if( elementSize == 1 ) {

        uint8_t   *restrict ptr = (uint8_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < count; col+=4 ) {

                UPDATE_STATE();

                ptr[(row * stride) + col + 0] = _loll(state01);
                ptr[(row * stride) + col + 1] = _hill(state01);
                ptr[(row * stride) + col + 2] = _loll(state23);
                ptr[(row * stride) + col + 3] = _hill(state23);
            }

            UPDATE_STATE();

            if(col < width)  ptr[(row * stride) + col++] = _loll(state01);
            if(col < width)  ptr[(row * stride) + col++] = _hill(state01);
            if(col < width)  ptr[(row * stride) + col++] = _loll(state23);
        }
    } else if( elementSize == 2 ) {
        uint16_t   *restrict ptr = (uint16_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < count; col+=4 ) {

                UPDATE_STATE();

                ptr[(row * stride/2) + col + 0] = _loll(state01);
                ptr[(row * stride/2) + col + 1] = _hill(state01);
                ptr[(row * stride/2) + col + 2] = _loll(state23);
                ptr[(row * stride/2) + col + 3] = _hill(state23);
            }

            UPDATE_STATE();

            if(col < width)  ptr[(row * stride/2) + col++] = _loll(state01);
            if(col < width)  ptr[(row * stride/2) + col++] = _hill(state01);
            if(col < width)  ptr[(row * stride/2) + col++] = _loll(state23);
        }
    } else if( elementSize == 4 ) {
        uint32_t   *restrict ptr = (uint32_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < count; col+=4 ) {

                UPDATE_STATE();

                ptr[(row * stride/4) + col + 0] = _loll(state01);
                ptr[(row * stride/4) + col + 1] = _hill(state01);
                ptr[(row * stride/4) + col + 2] = _loll(state23);
                ptr[(row * stride/4) + col + 3] = _hill(state23);
            }

            UPDATE_STATE();

            if(col < width)  ptr[(row * stride/4) + col++] = _loll(state01);
            if(col < width)  ptr[(row * stride/4) + col++] = _hill(state01);
            if(col < width)  ptr[(row * stride/4) + col++] = _loll(state23);
        }

    } else if( elementSize == 8 ) {
        uint32_t   *restrict ptr = (uint32_t *)array;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride / 8 + col]= rand();
            }
        }
    } else {
        printf("\nUnsupported data type in fillRand.\n");
    }
}

/* 3D Memory Utility:
 *
 *    fillRand3DFast
 *
 */
void fillRand3DFast(void *array, uint16_t dim_x, uint16_t dim_y, uint16_t dim_z, uint16_t stride_y, uint16_t stride_z, uint8_t elementSize)
{
    uint32_t  ctrX, ctrY, ctrZ;
    int32_t count = (dim_x >> 2) << 2;

    if( elementSize == 1 ) {
        uint8_t   *restrict ptr = (uint8_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {

                int32_t offset = (ctrZ * stride_z) + (ctrY * stride_y);

                for( ctrX=0; ctrX < count; ctrX+=4 ) {

                    UPDATE_STATE();

                    ptr[offset + ctrX + 0] = _loll(state01);
                    ptr[offset + ctrX + 1] = _hill(state01);
                    ptr[offset + ctrX + 2] = _loll(state23);
                    ptr[offset + ctrX + 3] = _hill(state23);
                }

                UPDATE_STATE();

                if(ctrX < dim_x)  ptr[offset + ctrX++] = _loll(state01);
                if(ctrX < dim_x)  ptr[offset + ctrX++] = _hill(state01);
                if(ctrX < dim_x)  ptr[offset + ctrX++] = _loll(state23);
            }
        }

    } else if( elementSize == 2 ) {
        uint16_t   *restrict ptr = (uint16_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                
                int32_t offset = (ctrZ * stride_z/2) + (ctrY * stride_y/2);

                for( ctrX=0; ctrX < count; ctrX+=4 ) {

                    UPDATE_STATE();

                    ptr[offset + ctrX + 0] = _loll(state01);
                    ptr[offset + ctrX + 1] = _hill(state01);
                    ptr[offset + ctrX + 2] = _loll(state23);
                    ptr[offset + ctrX + 3] = _hill(state23);
                }

                UPDATE_STATE();

                if(ctrX < dim_x)  ptr[offset + ctrX++] = _loll(state01);
                if(ctrX < dim_x)  ptr[offset + ctrX++] = _hill(state01);
                if(ctrX < dim_x)  ptr[offset + ctrX++] = _loll(state23);
            }
        }

    } else if( elementSize == 4 ) {
        uint32_t   *restrict ptr = (uint32_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                int32_t offset = (ctrZ * stride_z/4) + (ctrY * stride_y/4);

                for( ctrX=0; ctrX < count; ctrX+=4 ) {

                    UPDATE_STATE();

                    ptr[offset + ctrX + 0] = _loll(state01);
                    ptr[offset + ctrX + 1] = _hill(state01);
                    ptr[offset + ctrX + 2] = _loll(state23);
                    ptr[offset + ctrX + 3] = _hill(state23);
                }

                UPDATE_STATE();

                if(ctrX < dim_x)  ptr[offset + ctrX++] = _loll(state01);
                if(ctrX < dim_x)  ptr[offset + ctrX++] = _hill(state01);
                if(ctrX < dim_x)  ptr[offset + ctrX++] = _loll(state23);
            }
        }
    } else if( elementSize == 8 ) {
        uint64_t   *restrict ptr = (uint64_t *)array;

        for( ctrZ= 0; ctrZ < dim_z; ctrZ++ ) {
            for( ctrY= 0; ctrY < dim_y; ctrY++ ) {
                for( ctrX=0; ctrX < dim_x; ctrX++ ) {
                    ptr[(ctrZ * stride_z/8) + (ctrY * stride_y/8) + ctrX]= rand();
                }
            }
        }
    } else {
        printf("\nUnsupported data type in fillRand3D.\n");
    }
}


/* 2D Memory Utility:
 *
 *    fillBuffer
 *
 */
void TI_fillBuffer(uint8_t testPattern, uint8_t constFill, void *dest, void *src,
                   uint16_t width, uint16_t height, uint16_t stride,
                   uint8_t elementSize, char *testPatternType)
{
    if( testPattern == CONSTANT ) {
        if( dest ) {
            fillConst(constFill, dest, width, height, stride, elementSize);
        }
        sprintf(testPatternType, "Constant");
    } else if( testPattern == SEQUENTIAL ) {
        if( dest ) {
            fillSeq(dest, width, height, stride, elementSize);
        }
        sprintf(testPatternType, "Sequentially");
    } else if( testPattern == SEQUENTIAL_NEGATIVE ) {
        if( dest ) {
            fillSeqNeg(dest, width, height, stride, elementSize);
        }
        sprintf(testPatternType, "Sequentially");
    } else if( testPattern == STATIC ) {
        if( dest && src ) {
            copyRoi(dest, src, width, height, stride, elementSize);
        }
        sprintf(testPatternType, "Statically");
    } else if( testPattern == RANDOM ) {
        if( dest ) {
            fillRand(dest, width, height, stride, elementSize);
        }
        sprintf(testPatternType, "Randomly");
    } else if( testPattern == RANDOM_SIGNED ) {
        if( dest ) {
            fillRandSigned(dest, width, height, stride, elementSize);
        }
        sprintf(testPatternType, "Randomly");
    } else {
        sprintf(testPatternType, "Custom");
    }
}

/* 3D Memory Utility:
 *
 *    fillBuffer3D
 *
 */
void TI_fillBuffer3D(uint8_t testPattern, uint8_t constFill, void *dest, void *src,
                     uint16_t dim_x, uint16_t dim_y, uint16_t dim_z, uint16_t stride_y, uint16_t stride_z,
                     uint8_t elementSize, char *testPatternType)
{
    if( testPattern == CONSTANT ) {
        if( dest ) {
            fillConst3D(constFill, dest, dim_x, dim_y, dim_z, stride_y, stride_z, elementSize);
        }
        sprintf(testPatternType, "Constant");
    } else if( testPattern == SEQUENTIAL ) {
        if( dest ) {
            fillSeq3D(dest, dim_x, dim_y, dim_z, stride_y, stride_z, elementSize);
        }
        sprintf(testPatternType, "Sequentially");
    } else if( testPattern == SEQUENTIAL_NEGATIVE ) {
        if( dest ) {
            fillSeqNeg3D(dest, dim_x, dim_y, dim_z, stride_y, stride_z, elementSize);
        }
        sprintf(testPatternType, "Sequentially");
    } else if( testPattern == STATIC ) {
        if( dest && src ) {
            copyRoi3D(dest, src, dim_x, dim_y, dim_z, stride_y, stride_z, elementSize);
        }
        sprintf(testPatternType, "Statically");
    } else if( testPattern == RANDOM ) {
        if( dest ) {
            fillRand3D(dest, dim_x, dim_y, dim_z, stride_y, stride_z, elementSize);
        }
        sprintf(testPatternType, "Randomly");
    } else {
        sprintf(testPatternType, "Custom");
    }
}

/* 2D Memory Utility:
 *
 *    compare
 *
 */
uint32_t compare(uint8_t *dsp_output, uint8_t *natc_output, uint16_t width, uint16_t height, uint16_t stride)
{
    uint32_t    row, col;

    for( row= 0; row < height; row++ ) {
        for( col=0; col < width; col++ ) {
            if( dsp_output[row * stride + col] != natc_output[row * stride + col] ) {
                return (1);
            }
        }
    }

    return (0);
}

/* 2D Memory Utility:
 *
 *    copyRoi_float
 *
 */
void copyRoi_float(void *arrayDst, void *arraySrc, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize)
{
    uint32_t    row, col;

    if( elementSize == 4 ) {
        float   *dst = (float *)arrayDst;
        float   *src = (float *)arraySrc;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                dst[row * stride + col]= src[row * width + col];
            }
        }
    } else if( elementSize == 8 ) {
        double   *dst = (double *)arrayDst;
        double   *src = (double *)arraySrc;

        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                dst[row * stride / 2 + col]= src[row * width + col];
            }
        }
    } else {
        printf("\nUnsupported data type in copyRoi_float.\n");
    }
}

/* 2D Memory Utility:
 *
 *    fillRand_float
 *
 */
void fillRand_float(void *array, uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize)
{
    uint32_t    row, col;
    if( elementSize == 4 ) {
        float    *ptr = (float  *)array;
        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride + col]= ( float  ) ( ( double ) rand() / ( ( double ) RAND_MAX / 2.0 ) ) - 1.0F; \
            }
        }
    } else if (elementSize == 8){
        double    *ptr = (double  *)array;
        for( row= 0; row < height; row++ ) {
            for( col=0; col < width; col++ ) {
                ptr[row * stride + col]= ( ( double ) rand() / ( ( double ) RAND_MAX / 2.0 ) ) - 1.0F; \
            }
        }
    } else {
        printf("\nUnsupported data type in fillRand_float.\n");
    }
}

/* 2D Memory Utility:
 *
 *    fillBuffer_float
 *
 */
void TI_fillBuffer_float(uint8_t testPattern, void *constFill, void *dest, void *src,
        uint16_t width, uint16_t height, uint16_t stride, uint8_t elementSize, char *testPatternType)
{
    if( testPattern == CONSTANT ) {
        sprintf(testPatternType, "Constant");
    } else if( testPattern == SEQUENTIAL ) {

        sprintf(testPatternType, "Sequentially");
    } else if( testPattern == SEQUENTIAL_NEGATIVE ) {

        sprintf(testPatternType, "Sequentially");
    } else if( testPattern == STATIC ) {
        if( dest && src ) {
            copyRoi_float(dest, src, width, height, stride, elementSize);
        }
        sprintf(testPatternType, "Statically");
    } else if( testPattern == RANDOM ) {
        if( dest ) {
            fillRand_float(dest, width, height, stride, elementSize);
        }
        sprintf(testPatternType, "Randomly");
    } else {
        sprintf(testPatternType, "Custom");
    }
}

/* ======================================================================== */
/*  End of file:  TI_memory.c                                             */
/* ======================================================================== */

