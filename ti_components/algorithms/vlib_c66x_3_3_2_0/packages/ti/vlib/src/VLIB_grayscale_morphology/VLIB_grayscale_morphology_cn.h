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
**|         Copyright (c) 2007-2013 Texas Instruments Incorporated           |**
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

#ifndef VLIB_GRAYSCALE_MORPHOLOGY_CN_H_

#define VLIB_GRAYSCALE_MORPHOLOGY_CN_H_

#include "../common/VLIB_types.h"
#include "VLIB_grayscale_morphology_types.h"

void    VLIB_grayscale_morphology_cn
(
    uint16_t blk_w,                /* width of input block, in elements */
    uint16_t line_ofst,            /* offset between input lines, in elements */
    uint16_t blk_h,                /* height of input block */
    const uint8_t data_ptr[],      /* input data pointer */
    uint16_t se_w,                 /* width of structuring element block, in elements */
    uint16_t se_h,                 /* height of structuring element block */
    const uint8_t se_ptr[],        /* structuring element data pointer */
    const uint8_t refl_se_ptr[],   /* Reflected structuring element data pointer */
    uint8_t scratch1_ptr[],         /* scratch 1 pointer */
    uint8_t scratch2_ptr[],         /* scratch 2 pointer */
    uint8_t output_ptr[],           /* output data pointer */
    GrayscaleMorphologyOperation operation  /* Grayscale Morphology Operation */
);

void    VLIB_grayscale_dilate_mask_cn
(
    uint16_t blk_w,                /* width of input block, in elements */
    uint16_t line_ofst,            /* offset between input lines, in elements */
    uint16_t blk_h,                /* height of input block */
    const uint8_t data_ptr[],      /* input data pointer */
    uint16_t se_w,                 /* width of structuring element block, in elements */
    uint16_t se_h,                 /* height of structuring element block */
    const uint8_t se_ptr[],        /* structuring element data pointer */
    uint8_t output_ptr[]            /* output data pointer */
);

void    VLIB_grayscale_erode_mask_cn
(
    uint16_t blk_w,                /* width of input block, in elements */
    uint16_t line_ofst,            /* offset between input lines, in elements */
    uint16_t blk_h,                /* height of input block */
    const uint8_t data_ptr[],    /* input data pointer */
    uint16_t se_w,                 /* width of structuring element block, in elements */
    uint16_t se_h,                 /* height of structuring element block */
    const uint8_t se_ptr[],      /* structuring element data pointer */
    uint8_t output_ptr[]           /* output data pointer */
);

void    VLIB_grayscale_morp_diff_cn
(
    uint16_t blk_w,                /* width of input block, in elements */
    uint16_t line_ofst,            /* offset between input lines, in elements */
    uint16_t blk_h,                /* height of input block */
    const uint8_t data_ptr[],       /* input 1 data pointer (data >= data2)*/
    const uint8_t data2_ptr[],      /* input 2 data pointer */
    uint8_t output_ptr[]            /* output data poS32er */
);

#endif /* VLIB_GRAYSCALE_MORP_DIFF_CN_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_grayscale_morphology_cn.h                            */
/* ======================================================================== */

