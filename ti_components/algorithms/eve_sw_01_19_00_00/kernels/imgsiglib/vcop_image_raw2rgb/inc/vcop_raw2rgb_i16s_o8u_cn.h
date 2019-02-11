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

void vcop_raw2rgb_i16s_o8u_cn
(
 short *in_buff,
 short *pOffsetR,
 short *pOffsetG,
 short *pOffsetB,
 unsigned char *Rbuff,
 unsigned char *Gbuff,
 unsigned char *Bbuff,
 unsigned int  *pSumR,
 unsigned int  *pSumG,
 unsigned int  *pSumB,
 unsigned int  img_width,
 unsigned int  img_height,
 unsigned int  input_stride,
 unsigned int  output_stride
);



