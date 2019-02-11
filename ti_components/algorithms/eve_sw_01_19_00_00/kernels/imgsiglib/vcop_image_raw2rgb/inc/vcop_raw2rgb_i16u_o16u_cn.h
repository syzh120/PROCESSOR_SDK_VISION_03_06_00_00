/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_reference_bayerCFA_interpolate.h                                    */

/*   @brief  : This file contains all functions related to bayer to RGB conversion   */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (September 2012) : Base version.                               */

/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void vcop_raw2rgb_CGGC_i16u_o16u_cn
(
        uint16_t *pInBuff,
        uint16_t *pRbuff,
        uint16_t *pGbuff,
        uint16_t *pBbuff,
        unsigned short blkWidth,
        unsigned short blkHeight,
        unsigned short input_stride,
        unsigned short outputG_stride,
        unsigned short outputRB_stride
);

void vcop_raw2rgb_GCCG_i16u_o16u_cn
(
        uint16_t *pInBuff,
        uint16_t *pRbuff,
        uint16_t *pGbuff,
        uint16_t *pBbuff,
        unsigned short blkWidth,
        unsigned short blkHeight,
        unsigned short input_stride,
        unsigned short outputG_stride,
        unsigned short outputRB_stride
);


