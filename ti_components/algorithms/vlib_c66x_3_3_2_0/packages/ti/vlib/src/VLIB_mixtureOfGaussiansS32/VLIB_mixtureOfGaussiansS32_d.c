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
**|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
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

#include "VLIB_mixtureOfGaussiansS32.h"
#include "VLIB_mixtureOfGaussiansS32_cn.h"
#include "VLIB_mixtureOfGaussiansS32_idat.h"

/* VLIB_mixtureOfGaussiansS32_d:  Test Driver Routine */
void VLIB_mixtureOfGaussiansS32_d (uint8_t LevelOfFeedback)
{
    int32_t    tpi;  /* test parameter index */

    /* Test Parameters */
    mixtureOfGaussiansS32_testParams_t   *prm;

    mixtureOfGaussiansS32_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(3, "VLIB_mixtureOfGaussiansS32");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
        int32_t    status_nat_vs_ref = vlib_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */

        /* Compute buffer sizes */
        uint32_t    inp_size     =   prm[tpi].im_size * prm[tpi].num_images; // Allocate all frames into a single buffer for this test

        /* Allocate buffers for each test vector */
        uint8_t    *Im          =  (uint8_t *) VLIB_malloc(inp_size * sizeof(uint8_t));
        int16_t    *wt          =  (int16_t *) VLIB_malloc(prm[tpi].im_size * 3 * sizeof(int16_t));
        int32_t    *mu          =  (int32_t *) VLIB_malloc(prm[tpi].im_size * 3 * sizeof(int32_t));
        int32_t    *var         =  (int32_t *) VLIB_malloc(prm[tpi].im_size * 3 * sizeof(int32_t));
        uint8_t    *compNum     =  (uint8_t *) VLIB_malloc(prm[tpi].im_size * sizeof(uint8_t));
        uint8_t    *updateMask8 =  (uint8_t *) VLIB_malloc(prm[tpi].im_size * sizeof(uint8_t));
        uint32_t   *Im_mask     =  (uint32_t *) VLIB_malloc(prm[tpi].im_size / 32 * sizeof(uint32_t));
        uint32_t   *Im_mask_cn  =  (uint32_t *) malloc(prm[tpi].im_size / 32 * sizeof(uint32_t));

        /* Only run the test if the buffer allocations fit in the heap */
        if( Im && wt && mu && var && compNum && updateMask8 && Im_mask && Im_mask_cn ) {

            int32_t    fail, i, k, counter;
            int8_t     mode[3];

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            Im, prm[tpi].staticIn,
                            prm[tpi].im_size, prm[tpi].num_images, prm[tpi].im_size * sizeof(uint8_t),
                            sizeof(uint8_t), testPatternString);

            /* ****************** */
            /* TEST _OPT KERNEL   */
            /* ****************** */

            /* Set the moments and the polynomial to 0 */
            memset(wt, 0, prm[tpi].im_size * 3 * sizeof(int16_t));
            memset(mu, 0, prm[tpi].im_size * 3 * sizeof(int32_t));
            memset(var, 0, prm[tpi].im_size * 3 * sizeof(int32_t));
            counter = 0;

            if( LevelOfFeedback > 0 ) {
                /* Format diagnostic output */
                printf("Luma  FG    Mean-1   Varn-1   Wght-1        Mean-2   Varn-2   Wght-2       Mean-3   Varn-3   Wght-3\n");
                printf("-----------------------------------------------------------------------------------------------------\n");
            }

            /* PROCESS IMAGES */
            for( i=0; i < prm[tpi].num_images; i++ ) {

                /* Test optimized kernel */
                VLIB_profile_start(vlib_KERNEL_OPT);
                VLIB_mixtureOfGaussiansS32(&Im[i * prm[tpi].im_size],
                                           wt, mu, var, compNum, updateMask8, Im_mask,
                                           prm[tpi].im_size,
                                           prm[tpi].alpha,  prm[tpi].rho,
                                           prm[tpi].delta,  prm[tpi].T,
                                           prm[tpi].ini_wt, prm[tpi].ini_var);
                VLIB_profile_stop();

                /* Display state of the MOG model */
                mode[0] = ' ';
                mode[1] = ' ';
                mode[2] = ' ';
                mode[compNum[0]] = '*';

                if( LevelOfFeedback > 0 ) {
                    printf("%4d  %d  %c %8.4f %8.4f %8.6f   %c %8.4f %8.4f %8.6f   %c %8.4f %8.4f %8.6f\n", Im[i * prm[tpi].im_size], (Im_mask[0] & 0x80000000) >> 31,
                           mode[0], VLIB_getFractional32(mu[0], 15, 1), VLIB_getFractional16(var[0], 3, 1), VLIB_getFractional16(wt[0], 15, 1),
                           mode[1], VLIB_getFractional32(mu[0 + (prm[tpi].im_size)], 23, 1), VLIB_getFractional32(var[0 + (prm[tpi].im_size)], 15, 1), VLIB_getFractional16(wt[0 + (prm[tpi].im_size)], 15, 1),
                           mode[2], VLIB_getFractional32(mu[0 + 2 * (prm[tpi].im_size)], 23, 1), VLIB_getFractional16(var[0 + 2 * (prm[tpi].im_size)], 15, 1), VLIB_getFractional16(wt[0 + 2 * (prm[tpi].im_size)], 15, 1));
                }

                /* If static output is available, then additionally compares output with static reference output data */
                if( prm[tpi].staticOut != NULL ) {

                    /* CHECK ACCURACY OF RESULTS */
                    for( k=0; k < 3 * prm[tpi].im_size; k++ ) {
                        if( mu[k] != prm[tpi].staticOut[counter++] ) {
                            printf("\tError in Mean: Image %d, Pixel %d, Mode %d\n", i, k % 32, k / 32);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                        if( var[k] != prm[tpi].staticOut[counter++] ) {
                            printf("\tError in Variance: Image %d, Pixel %d, Mode %d\n", i, k % 32, k / 32);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                        if( wt[k] != prm[tpi].staticOut[counter++] ) {
                            printf("\tError in Weight: Image %d, Pixel %d, Mode %d\n", i, k % 32, k / 32);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                    }

                    for( k=0; k < prm[tpi].im_size; k++ ) {
                        if( compNum[k] != prm[tpi].staticOut[counter++] ) {
                            printf("\tError in Component index: Image %d, Pixel %d\n", i, k % 32);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                    }

                    for( k=0; k < prm[tpi].im_size; k++ ) {
                        if(((Im_mask[0] >> k) & 0x00000001) != ((prm[tpi].staticOut[counter] >> k) & 0x00000001)) {
                            printf("\tError in Foreground Mask: Image %d, Pixel %d\n", i, k);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                    }

                    counter++;
                }
            }

            /* ***************** */
            /* TEST _CN KERNEL   */
            /* ***************** */

            /* Set the moments and the polynomial to 0 */
            memset(wt, 0, prm[tpi].im_size * 3 * sizeof(int16_t));
            memset(mu, 0, prm[tpi].im_size * 3 * sizeof(int32_t));
            memset(var, 0, prm[tpi].im_size * 3 * sizeof(int32_t));
            counter = 0;

            if( LevelOfFeedback > 0 ) {
                /* Format diagnostic output */
                printf("Luma  FG    Mean-1   Varn-1   Wght-1        Mean-2   Varn-2   Wght-2       Mean-3   Varn-3   Wght-3\n");
                printf("-----------------------------------------------------------------------------------------------------\n");
            }

            /* PROCESS IMAGES */
            for( i=0; i < prm[tpi].num_images; i++ ) {

                /* Test _cn kernel */
                VLIB_profile_start(vlib_KERNEL_CN);
                VLIB_mixtureOfGaussiansS32_cn(&Im[i * prm[tpi].im_size],
                                              wt, mu, var, compNum, updateMask8, Im_mask_cn,
                                              prm[tpi].im_size,
                                              prm[tpi].alpha,  prm[tpi].rho,
                                              prm[tpi].delta,  prm[tpi].T,
                                              prm[tpi].ini_wt, prm[tpi].ini_var);
                VLIB_profile_stop();

                /* Display state of the MOG model */
                mode[0] = ' ';
                mode[1] = ' ';
                mode[2] = ' ';
                mode[compNum[0]] = '*';

                if( LevelOfFeedback > 0 ) {
                    printf("%4d  %d  %c %8.4f %8.4f %8.6f   %c %8.4f %8.4f %8.6f   %c %8.4f %8.4f %8.6f\n", Im[i * prm[tpi].im_size], (Im_mask[0] & 0x80000000) >> 31,
                           mode[0], VLIB_getFractional32(mu[0], 15, 1), VLIB_getFractional16(var[0], 3, 1), VLIB_getFractional16(wt[0], 15, 1),
                           mode[1], VLIB_getFractional32(mu[0 + (prm[tpi].im_size)], 23, 1), VLIB_getFractional32(var[0 + (prm[tpi].im_size)], 15, 1), VLIB_getFractional16(wt[0 + (prm[tpi].im_size)], 15, 1),
                           mode[2], VLIB_getFractional32(mu[0 + 2 * (prm[tpi].im_size)], 23, 1), VLIB_getFractional16(var[0 + 2 * (prm[tpi].im_size)], 15, 1), VLIB_getFractional16(wt[0 + 2 * (prm[tpi].im_size)], 15, 1));
                }

                /* If static output is available, then additionally compares output with static reference output data */
                if( prm[tpi].staticOut != NULL ) {

                    /* CHECK ACCURACY OF RESULTS */
                    for( k=0; k < 3 * prm[tpi].im_size; k++ ) {
                        if( mu[k] != prm[tpi].staticOut[counter++] ) {
                            printf("\tError in Mean: Image %d, Pixel %d, Mode %d\n", i, k % 32, k / 32);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                        if( var[k] != prm[tpi].staticOut[counter++] ) {
                            printf("\tError in Variance: Image %d, Pixel %d, Mode %d\n", i, k % 32, k / 32);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                        if( wt[k] != prm[tpi].staticOut[counter++] ) {
                            printf("\tError in Weight: Image %d, Pixel %d, Mode %d\n", i, k % 32, k / 32);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                    }

                    for( k=0; k < prm[tpi].im_size; k++ ) {
                        if( compNum[k] != prm[tpi].staticOut[counter++] ) {
                            printf("\tError in Component index: Image %d, Pixel %d\n", i, k % 32);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                    }

                    for( k=0; k < prm[tpi].im_size; k++ ) {
                        if(((Im_mask_cn[0] >> k) & 0x00000001) != ((prm[tpi].staticOut[counter] >> k) & 0x00000001)) {
                            printf("\tError in Foreground Mask: Image %d, Pixel %d\n", i, k);
                            status_nat_vs_ref = vlib_KERNEL_FAIL;
                        }
                    }

                    counter++;
                }
            }

            /* Compare natural C Output and Optimized Output */
            status_nat_vs_int = VLIB_compare_mem((void *) Im_mask, (void *)Im_mask_cn, prm[tpi].im_size / 32 * sizeof(uint32_t));

            /* Set the 'fail' flag based on test vector comparison results */
            fail = ((status_nat_vs_int == vlib_KERNEL_FAIL) || (status_nat_vs_ref == vlib_KERNEL_FAIL)) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | im_size=%d, num_images=%d",
                    testPatternString, prm[tpi].im_size, prm[tpi].num_images);
            VLIB_formula_add_test(prm[tpi].im_size * prm[tpi].num_images, prm[tpi].num_images, NULL, fail, desc, NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "im_size=%d, num_images=%d",
                    prm[tpi].im_size, prm[tpi].num_images);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(Im_mask_cn);
        VLIB_free(Im_mask);
        VLIB_free(updateMask8);
        VLIB_free(compNum);
        VLIB_free(var);
        VLIB_free(mu);
        VLIB_free(wt);
        VLIB_free(Im);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = im_size*num_images; M = num_images",
                              "im_size*num_images");

    /* Provide memory requirements */
    VLIB_kernel_memory();
}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

main() {
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_mixtureOfGaussiansS32");
    } else {
        VLIB_mixtureOfGaussiansS32_d(0);
    }
}
#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_mixtureOfGaussiansS32_d.c                            */
/* ======================================================================== */

