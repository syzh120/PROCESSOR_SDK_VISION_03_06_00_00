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
**|         Copyright (c) 2007-2014 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#include "../common/VLIB_test.h"
#include "../common/VLIB_memory.h"
#include "../common/VLIB_profile.h"

#include "VLIB_Connected_Components_Labeling.h"
#include "VLIB_Connected_Components_Labeling_cn.h"
#include "VLIB_Connected_Components_Labeling_idat.h"

#include "AVMClasses.h"

static void printHeader(uint32_t width)
{
    uint32_t    i;

    for( i=0; i < width; i++ ) {
        printf("%d", (i / 10) % 10);
    }

    printf("\n  ");

    for( i=0; i < width; i++ ) {
        printf("%d", i % 10);
    }

    printf("\n +");

    for( i=0; i < width; i++ ) {
        printf("-");
    }
}

/*  P L E A S E    N O T E

The primary function for grouping and labeling blobs in a binary image is
VLIB_createConnectedComponentsList. The input to this function is a 32-bit
packed binary image, e.g. foreground mask, and the output is a pointer to a
"list" of 4- or 8-connected components (the list is actually a private
structure). This pointer can be supplied to support functions, e.g.
VLIB_getCCFeatures, VLIB_createCCMap8Bit, etc., so that meaningful
information about the connected components can be extracted.

For best performance, VLIB_createConnectedComponentsList should use internal
and external memory buffers for processing the 32-bit packed binary
foreground image (mask) and for storing the list of connected components.
The amount of memory actually required is scene dependent.

VLIB_createConnectedComponentsList is designed to use pPrimaryBuf1 and
pPrimaryBuf2 memory buffers by internal, cache-enhanced double buffering.
We recommend that pPrimaryBuf1 and pPrimaryBuf2 point to buffers in
L1 Data and/or L2 Data memory for the best performance. During processing,
the generated connected components are influenced by the image size and
content. VLIB_createConnectedComponentsList uses pPrimaryBuf1 and
pPrimaryBuf2 but will also consume memory in pOverflowBuf1 and
pOverflowBuf2, as needed, after the primary buffers become exhausted.

To be clear, all memory buffer assignments can use external DDR2 memory
exclusively, but performance will be slower. It is illegal to supply null
pointers as arguments to pPrimaryBuf1 or pPrimaryBuf2. Using the largest
possible size for pPrimaryBuf1 and pPrimaryBuf2 is also recommended. It is
appropriate to place pOverflowBuf1 and pOverflowBuf2 in external memory.
Note: Make sure that the cache is enabled. Also be aware that overlapping
memory buffers produces unknown results and is not recommended.

In any case, the initialization function VLIB_initConnectedComponentsList
must be called to identify the available memory buffers each time the addre
changes, e.g. if persistent memory locations are available, only call the
initialization function once in the beginning. These functions are not
re-entrant.
*/

/* VLIB_Connected_Components_Labeling_d:  Test Driver Routine */
void VLIB_Connected_Components_Labeling_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    ccl_testParams_t   *prm;

    ccl_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_Connected_Components_Labeling");

    /* Run each test case */
    for( tpi = 0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_numCCs = vlib_KERNEL_PASS;  /* Test status : Number of CCs compare to reference */
        int32_t    status_stats  = vlib_KERNEL_PASS;  /* Test status : Stats compare to reference */
        int32_t    status_mask   = vlib_KERNEL_PASS;  /* Test status : Mask compare to reference */

        /* Compute buffer sizes */
        uint32_t    inp_size =     prm[tpi].width * prm[tpi].height;
        uint32_t    packed_width = (prm[tpi].width + 31) / 32;
        uint32_t    mod_width    = packed_width * 32;                   /* Width must be a multiple of 32 */
        uint32_t    packed_size  = packed_width * prm[tpi].height;
        uint32_t    out_size =     mod_width * prm[tpi].height;
        int32_t     maxBytesRequired;
        int32_t     sizeOfCCHandle;

        /* Allocate buffers for each test vector */
        uint8_t         *input_image      =  (uint8_t *) malloc(inp_size * sizeof(uint8_t));
        uint32_t        *pIn32BitPacked   =  (uint32_t *) malloc(packed_size * sizeof(uint32_t));
        uint8_t         *pOutMap          =  (uint8_t *) malloc(out_size * sizeof(uint8_t));
        void            *pBuf;
        VLIB_CCHandle   *handle;

        /*
         * This function returns the bytes required to process the worst-case,
         * binary image, which is nearly impossible to occur in practice.
         * considers image dimensions as well the number and configuration of binary
         */
        VLIB_calcConnectedComponentsMaxBufferSize(prm[tpi].width, prm[tpi].height,
                                                  prm[tpi].minBlobArea,
                                                  &maxBytesRequired);
        pBuf    = (void *) malloc(maxBytesRequired);

        /*
         * The amount of memory required is content dependent.Since the pathological
         * condition is unlikely, especially if morphological functions are used to
         * remove or group small pixels, it is a good idea to shrink max bytes by
         * some factor, e.g. an order of magnitude.
         * maxBytesRequired = maxBytesRequired / 5;
         */
        sizeOfCCHandle =  VLIB_GetSizeOfCCHandle();
        handle = (VLIB_CCHandle *) malloc(sizeOfCCHandle);

        if( input_image && pIn32BitPacked && pOutMap && pBuf && handle ) {

            int32_t    fail, i, j;
            int32_t    status;
            int32_t    numCCs;
            VLIB_CC    vlibBlob;

            /* INITIALIZE FOREGROUND MASK AND MEMORY BUFFERS*/
            status  = VLIB_initConnectedComponentsList(handle, pBuf, maxBytesRequired);

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            input_image, prm[tpi].staticIn,
                            prm[tpi].width, prm[tpi].height, prm[tpi].width,
                            sizeof(uint8_t), testPatternString);

            /* In case input is not binary (rg. random input), mask out all bits except bit 0 */
            for( i=0; i < inp_size; i++ ) {
                input_image[i] = (prm[tpi].testPattern == RANDOM) ? (input_image[i] & 1) : (input_image[i] > 0);
            }

            if( LevelOfFeedback > 0 ) {
                printf("Input: %dx%d binary foreground mask:\n\n  ", prm[tpi].width, prm[tpi].height);
                printHeader(prm[tpi].width);
            }

            /* Convert foreground symbols to a binary representation. */
            /* Binary foreground mask is packed into 32-bit word */
            memset(pIn32BitPacked, 0, packed_size * sizeof(int32_t));
            memset(pOutMap, 0, out_size);

            {
                int32_t    j;
                int32_t    fgMaskPixel;
                int32_t    word, shift, pos;
                int32_t    extra = (mod_width > prm[tpi].width);

                for( j=0; j < prm[tpi].height; j++ ) {
                    shift = 31;
                    word  = 0;
                    pos   = 0;
                    if( LevelOfFeedback > 0 ) {
                        printf("\n%d|", j);
                    }

                    for( i=0; i < prm[tpi].width; i++ ) {
                        /* is this "pixel" location a member of the foreground? */
                        if( input_image[j * prm[tpi].width + i] > 0 ) {
                            if( LevelOfFeedback > 0 ) {
                                printf("*");
                            }
                            fgMaskPixel = 1;
                        } else {
                            if( LevelOfFeedback > 0 ) {
                                printf(" ");
                            }
                            fgMaskPixel = 0;
                        }

                        word |= (fgMaskPixel << shift);

                        if( shift == 0 ) {
                            pIn32BitPacked[j * packed_width + pos] = word;
                            pos++;
                            word                 = 0;
                            shift                = 31;
                        } else {
                            shift--;
                        }
                    }

                    if( extra ) {
                        pIn32BitPacked[j * packed_width + pos] = word;
                    }
                }
            }

            fflush(stdout);

            if( LevelOfFeedback > 0 ) {
                printf("\n\n ==== %d-connected component labeling ====",
                       (prm[tpi].connected8Flag + 1) * 4);
            }

            /* CONVERT FOREGROUND MASK INTO CONNECTED COMPONENTS*/
            VLIB_profile_start(vlib_KERNEL_OPT);
            status = VLIB_createConnectedComponentsList(handle,
                                                        mod_width,
                                                        prm[tpi].height,
                                                        pIn32BitPacked,
                                                        prm[tpi].minBlobArea,
                                                        prm[tpi].connected8Flag);
            VLIB_profile_stop();

            if( status == VLIB_WARNING_LOW_MEMORY ) {
                printf("\nConnected Components low memory warning!!!!!\n");
            } else if( status != 0 ) {
                VLIB_printErrCode(status);
                printf("\nCreation of Connected Components failed!!!\n");
                goto clean_exit;
            }

            /* REPORT FEATURES FROM CONNECTED COMPONENTS LIST*/
            VLIB_getNumCCs(handle, &numCCs);

            /* Report Items from List */
            if( LevelOfFeedback > 0 ) {
                printf("\n\nIdentified %d connected-components with at least %d pixels:\n", numCCs, prm[tpi].minBlobArea);
            }

            if( prm[tpi].numCCs ) {
                if( numCCs != prm[tpi].numCCs ) {
                    status_numCCs = vlib_KERNEL_FAIL;
                }
            }

            /* Report CC Features */
            for( i=0; i < numCCs; i++ ) {
                int32_t    left;
                int32_t    right;
                int32_t    top;
                int32_t    bottom;
                int32_t    xsum;
                int32_t    ysum;
                int32_t    area;

                VLIB_getCCFeatures(handle, &vlibBlob, i);

                left    = vlibBlob.xmin;
                right   = vlibBlob.xmax;
                top     = vlibBlob.ymin;
                bottom  = vlibBlob.ymax;
                xsum    = vlibBlob.xsum;
                ysum    = vlibBlob.ysum;
                area    = vlibBlob.area;

                if( prm[tpi].staticOutStats && status_numCCs == vlib_KERNEL_PASS ) {
                    if( vlibBlob.xmin != prm[tpi].staticOutStats[i].xmin ||
                        vlibBlob.xmax != prm[tpi].staticOutStats[i].xmax ||
                        vlibBlob.ymin != prm[tpi].staticOutStats[i].ymin ||
                        vlibBlob.ymax != prm[tpi].staticOutStats[i].ymax ||
                        vlibBlob.xsum != prm[tpi].staticOutStats[i].xsum ||
                        vlibBlob.ysum != prm[tpi].staticOutStats[i].ysum ||
                        vlibBlob.area != prm[tpi].staticOutStats[i].area ) {
                        status_stats = vlib_KERNEL_FAIL;
                    }
                }

                if( LevelOfFeedback > 0 ) {
                    printf("Connected component #%d:\n", i + 1);
                    printf("  Pixel Area  : %d\n", area);
                    printf("  Bounding Box: left = %2d, right = %2d, top = %2d,bottom = %2d\n", left, right, top, bottom);
                    printf("  Horz. Sum   : %d\n", xsum);
                    printf("  Vert. Sum   : %d\n", ysum);
                    printf("  Centroid    : (%4.1f,%4.1f)\n\n", (VLIB_F32)xsum / area,
                           (VLIB_F32)ysum / area);
                }
            }

            fflush(stdout);

            /* CREATE CONNECTED COMPONENTS MAP*/
            status = VLIB_createCCMap8Bit(handle,
                                          pOutMap,
                                          mod_width,
                                          prm[tpi].height);

            if( status != 0 ) {
                VLIB_printErrCode(status);
                printf("Creation of %d-bit Connected Components Map failed!!!\n",
                       (prm[tpi].connected8Flag + 1) * 4);
                status_mask = vlib_KERNEL_FAIL;
            }

            /* DISPLAY CONNECTED COMPONENTS MAP*/
            if( LevelOfFeedback > 0 ) {
                printf("Output: %dx%d binary foreground mask:\n\n  ", mod_width, prm[tpi].height);
                printHeader(mod_width);
            }

            for( j=0; j < prm[tpi].height; j++ ) {
                if( LevelOfFeedback > 0 ) {
                    printf("\n%d|", j);
                }

                for( i=0; i < mod_width; i++ ) {
                    if( prm[tpi].staticOut && pOutMap[j * mod_width + i] != prm[tpi].staticOut[j * prm[tpi].width + i] ) {
                        status_mask = vlib_KERNEL_FAIL;
                        if( LevelOfFeedback > 0 ) {
                            printf("X");
                        }
                    } else if( LevelOfFeedback > 0 ) {
                        printf("%d", pOutMap[j * mod_width + i]);
                    }
                }
            }

            if( LevelOfFeedback > 0 ) {
                printf("\n");
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_numCCs == vlib_KERNEL_FAIL) ||
                    (status_stats == vlib_KERNEL_FAIL) ||
                    (status_mask == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to static results | width=%d, height=%d, minBlobArea=%d, connected8Flag=%d, numCCs=%d",
                    testPatternString, prm[tpi].width, prm[tpi].height, prm[tpi].minBlobArea, prm[tpi].connected8Flag, numCCs);
            VLIB_formula_add_test(out_size, NULL, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "width=%d, height=%d, minBlobArea=%d, connected8Flag=%d",
                    prm[tpi].width, prm[tpi].height, prm[tpi].minBlobArea, prm[tpi].connected8Flag);
            VLIB_skip_test(desc);
        }

clean_exit:
        /* Free buffers for each test vector */
        free(handle);
        free(pBuf);
        free(pOutMap);
        free(pIn32BitPacked);
        free(input_image);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_RANGE,
                              NULL,
                              "CELING(width,32) * height");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_Connected_Components_Labeling");
    } else {
        VLIB_Connected_Components_Labeling_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_Connected_Components_Labeling_d.c                    */
/* ======================================================================== */

