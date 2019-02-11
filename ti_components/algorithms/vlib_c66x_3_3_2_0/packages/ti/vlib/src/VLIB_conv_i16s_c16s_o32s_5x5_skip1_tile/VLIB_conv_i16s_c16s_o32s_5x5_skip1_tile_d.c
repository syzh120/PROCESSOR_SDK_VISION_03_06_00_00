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

#include "VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile.h"
#include "VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_cn.h"
#include "VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_idat.h"

/* VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_d:  Test Driver Routine */
void VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_d(uint8_t LevelOfFeedback)
{
    int32_t      tpi; /* test parameter index */
    uint32_t     shiftQ, coeffQ;
    sBuffer_t    sInChannel, sWeights, sBias;
    sBuffer_t    sOutChannel, sOutChannel_cn;

    /* Test Parameters */
    VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_testParams_t   *prm;

    VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_getTestParams(&prm, &test_cases);

    /* Initialize profiling */
    VLIB_profile_init(2, "VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile");

    /* Run each test case */
    for( tpi=0; tpi < test_cases; tpi++ ) {

        /* Initialize status flags */
        int32_t    status_nat_vs_int = vlib_KERNEL_PASS; /* Test status : Natural c vs. Optimized */

        /* Compute buffer sizes */
        uint32_t    inp_size  =   (prm[tpi].inPitch  * prm[tpi].inRows * prm[tpi].numInChannels);
        uint32_t    wgt_size  =   (prm[tpi].wgtPitch * prm[tpi].wgtRows * prm[tpi].numInChannels * prm[tpi].numOutChannels);
        uint32_t    bias_size =   (prm[tpi].biasPitch * prm[tpi].biasRows);
        uint32_t    out_size  =   (prm[tpi].outPitch * prm[tpi].outRows * prm[tpi].numOutChannels);
        uint32_t    flags;

        /* Allocate buffers for each test vector */
        sInChannel.data       = (uint8_t *) VLIB_memalign(8, inp_size * sizeof(int16_t));
        sInChannel.rows       = prm[tpi].inRows;
        sInChannel.cols       = prm[tpi].inCols;
        sInChannel.pitch      = prm[tpi].inPitch;

        flags = 0;
        SET_TILE_TYPE(flags, TILE_TYPE_16S);
        SET_TILE_CH(flags, prm[tpi].numInChannels);
        SET_TILE_CONTIGUOUS(flags, 1);
        sInChannel.flags       = flags;

        sWeights.data    = (uint8_t *) VLIB_memalign(8, wgt_size * sizeof(int16_t));
        sWeights.rows    = prm[tpi].wgtRows;
        sWeights.cols    = prm[tpi].wgtCols;
        sWeights.pitch   = prm[tpi].wgtPitch;

        flags = 0;
        SET_TILE_TYPE(flags, TILE_TYPE_16S);
        SET_TILE_CH(flags, prm[tpi].numInChannels * prm[tpi].numOutChannels);
        SET_TILE_CONTIGUOUS(flags, 1);
        sWeights.flags   = flags;

        sBias.data    = (uint8_t *) VLIB_memalign(8, bias_size * sizeof(int16_t));
        sBias.rows    = prm[tpi].biasRows;
        sBias.cols    = prm[tpi].biasCols;
        sBias.pitch   = prm[tpi].biasPitch;

        flags = 0;
        SET_TILE_TYPE(flags, TILE_TYPE_16S);
        SET_TILE_CH(flags, prm[tpi].numOutChannels);
        SET_TILE_CONTIGUOUS(flags, 1);
        sBias.flags      = flags;

        sOutChannel.data       = (uint8_t *) VLIB_memalign(8, out_size * sizeof(int32_t));
        sOutChannel.rows       = prm[tpi].outRows;
        sOutChannel.cols       = prm[tpi].outCols;
        sOutChannel.pitch      = prm[tpi].outPitch;

        flags = 0;
        SET_TILE_TYPE(flags, TILE_TYPE_32S);
        SET_TILE_CH(flags, prm[tpi].numOutChannels);
        SET_TILE_CONTIGUOUS(flags, 1);
        sOutChannel.flags      = flags;

        sOutChannel_cn.data    = (uint8_t *) malloc(out_size * sizeof(int32_t));
        sOutChannel_cn.rows    = prm[tpi].outRows;
        sOutChannel_cn.cols    = prm[tpi].outCols;
        sOutChannel_cn.pitch   = prm[tpi].outPitch;

        flags = 0;
        SET_TILE_TYPE(flags, TILE_TYPE_32S);
        SET_TILE_CH(flags, prm[tpi].numOutChannels);
        SET_TILE_CONTIGUOUS(flags, 1);
        sOutChannel_cn.flags   = flags;

        shiftQ = 2;
        coeffQ = 4;

        /* Only run the test if the buffer allocations fit in the heap */
        if( sInChannel.data && sWeights.data && sBias.data && sOutChannel.data && sOutChannel_cn.data ) {

            int32_t    fail, i, j, outChIdx;

            /* Fill input arrays according to desired test pattern */
            VLIB_fillBuffer(prm[tpi].testPattern,
                            (uint8_t)255,
                            sInChannel.data, prm[tpi].staticInChannel,
                            prm[tpi].inCols, prm[tpi].inRows * prm[tpi].numInChannels, prm[tpi].inPitch * sizeof(int16_t),
                            sizeof(int16_t), testPatternString);

            /* Fill weight arrays according to desired test pattern */
            VLIB_fillBuffer(STATIC,
                            (uint8_t)255,
                            sWeights.data, prm[tpi].staticWeights,
                            prm[tpi].wgtPitch, prm[tpi].wgtRows * prm[tpi].numInChannels * prm[tpi].numOutChannels, prm[tpi].wgtPitch * sizeof(int16_t),
                            sizeof(int16_t), testPatternString);

            /* Fill bias arrays according to desired test pattern */
            VLIB_fillBuffer(STATIC,
                            (uint8_t)255,
                            sBias.data, prm[tpi].staticBias,
                            prm[tpi].biasCols, prm[tpi].biasRows, prm[tpi].biasPitch * sizeof(int16_t),
                            sizeof(int16_t), testPatternString);

            /* Test optimized kernel */
            VLIB_profile_start(vlib_KERNEL_OPT);
            VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile(&sInChannel, &sWeights, &sBias, &sOutChannel, shiftQ, coeffQ);
            VLIB_profile_stop();


            /* Test _cn kernel */
            VLIB_profile_start(vlib_KERNEL_CN);
            VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_cn(&sInChannel, &sWeights, &sBias, &sOutChannel_cn, shiftQ, coeffQ);
            VLIB_profile_stop();

            /* Compare natural C Output and Optimized Output */
            for( outChIdx = 0; outChIdx < prm[tpi].numOutChannels; outChIdx++ ) {
                for( j=0; j < (prm[tpi].outRows); j++ ) {
                    int32_t   *optData = (int32_t *)sOutChannel.data + (outChIdx * prm[tpi].outPitch * prm[tpi].outRows);
                    int32_t   *cnData  = (int32_t *)sOutChannel_cn.data + (outChIdx * prm[tpi].outPitch * prm[tpi].outRows);

                    for( i=0; i < (prm[tpi].outCols); i++ ) {
                        int32_t    offset = j * prm[tpi].outPitch + i;
                        int32_t    optVal = (int32_t)optData[offset];
                        int32_t    cnVal  = (int32_t)cnData[offset];

                        if( optVal != cnVal ) {
                            status_nat_vs_int = vlib_KERNEL_FAIL;
                            break;
                        }
                    }
                }
            }

            /* Set the 'fail' flag based on test vector comparison results */
            fail = (status_nat_vs_int == vlib_KERNEL_FAIL) ? 1 : 0;

            est_test=1;

            /* Profile display and preparation for cycle estimation */
            sprintf(desc, "%s generated input | Opt results compared to NatC results | inCols=%d, inRows=%d, outCols=%d, outRows=%d",
                    testPatternString, prm[tpi].inCols, prm[tpi].inRows, prm[tpi].outCols, prm[tpi].outRows);
            VLIB_formula_add_test(out_size, (int) NULL, (int) NULL, fail, desc, (int)NULL);

        } else {
            /* Display the error printout for this test vector before moving on to the next test vector */
            sprintf(desc, "inCols=%d, inRows=%d, outCols=%d, outRows=%d",
                    prm[tpi].inCols, prm[tpi].inRows, prm[tpi].outCols, prm[tpi].outRows);
            VLIB_skip_test(desc);
        }

        /* Free buffers for each test vector */
        free(sOutChannel_cn.data);
        VLIB_align_free(sOutChannel.data);
        VLIB_align_free(sBias.data);
        VLIB_align_free(sWeights.data);
        VLIB_align_free(sInChannel.data);
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
        VLIB_memError("VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile");
    } else {
        VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_d(0);
    }
    return (0);
}

#endif /* __ONESHOTTEST */

/* ======================================================================== */
/*  End of file:  VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_d.c               */
/* ======================================================================== */

