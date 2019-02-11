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

#include "VLIB_neuralNet_tile.h"
#include "VLIB_neuralNet_tile_cn.h"
#include "VLIB_neuralNet_tile_idat.h"

/* VLIB_neuralNet_tile_d:  Test Driver Routine */
void VLIB_neuralNet_tile_d(uint8_t LevelOfFeedback)
{
    int32_t      tpi; /* test parameter index */
    sBuffer_t    sInNodes, sOutNodes, sOutNodes_cn;
    sBuffer_t    sBias, sWeight;
    int16_t     *pOutNodes;
    int16_t     *pOutNodes_cn;

    /* Test Parameters */
    VLIB_neuralNet_tile_testParams_t   *prm;

    VLIB_neuralNet_tile_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_neuralNet_tile");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {
       
        uint32_t flags;

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */

        /* Compute buffer sizes */
        uint32_t    inp_size    =  (prm[tpi].inPitch     * prm[tpi].inRows     * prm[tpi].inCh);
        uint32_t    weight_size =  (prm[tpi].weightPitch * prm[tpi].weightRows * prm[tpi].weightCh);
        uint32_t    bias_size   =  (prm[tpi].biasPitch   * prm[tpi].biasRows   * prm[tpi].biasCh);
        uint32_t    out_size    =  (prm[tpi].outPitch    * prm[tpi].outRows    * prm[tpi].outCh);

        /* Allocate buffers for each test vector */
        flags = 0;
        sInNodes.data        = (uint8_t *) VLIB_memalign(8, inp_size * sizeof(int16_t));
        sInNodes.rows        = prm[tpi].inRows;
        sInNodes.cols        = prm[tpi].inCols;
        sInNodes.pitch       = prm[tpi].inPitch;
        SET_TILE_CH(flags, prm[tpi].inCh);
        sInNodes.flags       = flags;

        flags = 0;
        sWeight.data         = (uint8_t *) VLIB_memalign(8, weight_size * sizeof(int16_t));
        sWeight.rows         = prm[tpi].weightRows;
        sWeight.cols         = prm[tpi].weightCols;
        sWeight.pitch        = prm[tpi].weightPitch;
        SET_TILE_CH(flags, prm[tpi].weightCh);
        sWeight.flags        = flags;

        flags = 0;
        sBias.data           = (uint8_t *) VLIB_memalign(8, bias_size * sizeof(int16_t));
        sBias.rows           = prm[tpi].biasRows;
        sBias.cols           = prm[tpi].biasCols;
        sBias.pitch          = prm[tpi].biasPitch;
        SET_TILE_CH(sBias.flags, prm[tpi].biasCh);
        sBias.flags          = flags;

        flags = 0;
        sOutNodes.data       = (uint8_t *) VLIB_memalign(8, out_size * sizeof(int16_t));
        sOutNodes.rows       = prm[tpi].outRows;
        sOutNodes.cols       = prm[tpi].outCols;
        sOutNodes.pitch      = prm[tpi].outPitch;
        SET_TILE_CH(sOutNodes.flags, prm[tpi].outCh);
        sOutNodes.flags      = flags;

        flags = 0;
        sOutNodes_cn.data    = (uint8_t *) malloc(out_size * sizeof(int16_t));
        sOutNodes_cn.rows    = prm[tpi].outRows;
        sOutNodes_cn.cols    = prm[tpi].outCols;
        sOutNodes_cn.pitch   = prm[tpi].outPitch;
        SET_TILE_CH(sOutNodes_cn.flags, prm[tpi].outCh);
        sOutNodes_cn.flags   = flags;

        pOutNodes = (int16_t *)sOutNodes.data;
        pOutNodes_cn  = (int16_t *)sOutNodes_cn.data;

        /* Only run the test if the buffer allocations fit in the heap */
        if( sInNodes.data && sOutNodes.data && sOutNodes_cn.data ) {

            int32_t    fail, i, j;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            sInNodes.data, prm[tpi].staticIn,
                            prm[tpi].inCols, prm[tpi].inCh, prm[tpi].inPitch * sizeof(int16_t),
                            sizeof(int16_t), testPatternString);

            /* Fill weight arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            sWeight.data, prm[tpi].staticWeights,
                            prm[tpi].weightPitch, prm[tpi].weightRows, prm[tpi].weightPitch * sizeof(int16_t),
                            sizeof(int16_t), testPatternString);

            /* Fill bias arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            sBias.data, prm[tpi].staticBias,
                            prm[tpi].biasCols, prm[tpi].biasRows, prm[tpi].biasPitch * sizeof(int16_t),
                            sizeof(int16_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_neuralNet_tile(&sInNodes, &sWeight, &sBias, &sOutNodes, 3, 3, 1, 1);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_neuralNet_tile_cn(&sInNodes, &sWeight, &sBias, &sOutNodes_cn, 3, 3, 1, 1);
            VLIB_profile_stop();

            for( j=0; j < (prm[tpi].outRows); j++ ) {
                for( i=0; i < (prm[tpi].outCols); i++ ) {
                    if( pOutNodes[(j * prm[tpi].outPitch) + i] != pOutNodes_cn[(j * prm[tpi].outPitch) + i] ) {
                        status_nat_vs_int = vlib_KERNEL_FAIL;
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = (status_nat_vs_int == vlib_KERNEL_FAIL) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | inCols=%d, inRows=%d, outCols=%d, outRows=%d, numCh=%d",
                    testPatternString, prm[tpi].inCols, prm[tpi].inRows, prm[tpi].outCols, prm[tpi].outRows, prm[tpi].inCh);
            VLIB_formula_add_test(prm[tpi].outCols * prm[tpi].outRows * prm[tpi].outCh, (int32_t)NULL, (int32_t)NULL, fail, desc, (int32_t)NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "inCols=%d, inRows=%d, outCols=%d, outRows=%d, numCh=%d",
                    prm[tpi].inCols, prm[tpi].inRows, prm[tpi].outCols, prm[tpi].outRows, prm[tpi].inCh);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(sOutNodes_cn.data);
        VLIB_align_free(sOutNodes.data);
        VLIB_align_free(sBias.data);
        VLIB_align_free(sWeight.data);
        VLIB_align_free(sInNodes.data);
    }

    /* Calculate and display cycle formula and/or cycle range (and testing success) */
    VLIB_profile_cycle_report(vlib_PROFILE_FORMULA_RANGE,
                              "N = outCols * outRows",
                              "outCols * outRows");

    /* Provide memory requirements */
    VLIB_kernel_memory();

}

/* Main call for individual test projects */
#ifndef __ONESHOTTEST

int main()
{
    if( VLIB_cache_init()) {
        VLIB_memError("VLIB_neuralNet_tile");
    } else {
        VLIB_neuralNet_tile_d(0);
    }
    return (0);
}

#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_neuralNet_tile_d.c                                   */
/* ======================================================================== */

