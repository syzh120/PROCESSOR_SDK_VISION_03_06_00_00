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
**|         Copyright (c) 2016 - 2017 Texas Instruments Incorporated         |**
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
/*
 * Copyright (c) 2012-2016 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and/or associated documentation files (the
 * "Materials"), to deal in the Materials without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Materials, and to
 * permit persons to whom the Materials are furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 *
 * MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS
 * KHRONOS STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS
 * SPECIFICATIONS AND HEADER INFORMATION ARE LOCATED AT
 *    https://www.khronos.org/registry/
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
 */

#include "VXLIB_trackFeaturesLK_i8u.h"

CODE_SECTION(VXLIB_trackFeaturesLK_i8u,              ".text:optimized")
CODE_SECTION(VXLIB_trackFeaturesLK_i8u_checkParams,  ".text:optimized")

/* Number of bits to use as fractional in fixed point math */
#define  W_BITS 14U

/* Upshift coefficients before converting to fixed point */
#define  FRACTIONAL ((uint32_t)1 << W_BITS)

#define  FLT_SCALE (1.0f/(VXLIB_F32)((uint32_t)1 << 20))

/* There is an approximations being done for the square-root operation:
 *
 * The NEWTON_RHAPSON_ITERATIONS parameter is the number of iterations
 * in the Newton-rhapson algorithm to determing the double-precision
 * square root.  In all cases, the exponent of the rsqrdp is accurate,
 * but this value affects the mantissa precision.
 *
 * NEWTON_RHAPSON_ITERATIONS =
 *   0:  8-bit mantissa precision
 *   1: 16-bit mantissa precision
 *   2: 32-bit mantissa precision
 *   3: Full 52-bit mantissa precision
 * 
 * If it is found that the current setting is inappropriate, then the
 * NEWTON_RHAPSON_ITERATIONS parameter can be changed to alter the
 * precision. (see RSQRDP instruction in the C6X instruction manual).
 */
#define NEWTON_RHAPSON_ITERATIONS 2

static inline int32_t INT_ROUND(int32_t x, uint32_t n);
static inline VXLIB_D64 sqrtdp (VXLIB_D64 a);
static inline VXLIB_D64 recipdp (VXLIB_D64 a);
static inline void getWindowsInterpolate(const uint8_t image[restrict],
                                           const int16_t gradX[restrict],
                                           const int16_t gradY[restrict],
                                           int16_t winImage[restrict],
                                           uint32_t winGrad[restrict],
                                           int32_t strideImage,
                                           int32_t strideGrad,
                                           int32_t x,
                                           int32_t y,
                                           const int64_t weights,
                                           int32_t window_size,
                                           VXLIB_F32 *XX,
                                           VXLIB_F32 *XY,
                                           VXLIB_F32 *YY);
static inline void diffNewWindowInterpolate(const uint8_t image[restrict],
                                                 const int16_t winImage[restrict],
                                                 const uint32_t winGrad[restrict],
                                                 int32_t stride,
                                                 int32_t x,
                                                 int32_t y,
                                                 const int64_t weights,
                                                 int32_t window_size,
                                                 VXLIB_F32 *zx,
                                                 VXLIB_F32 *zy);

static inline int32_t INT_ROUND(int32_t x, uint32_t n) {
    uint32_t half = (uint32_t)1 << (n-1U);
    int32_t addhalf = x + (int32_t)half;

    /* MISRA.BITS.NOT_UNSIGNED
     * MISRAC_2004 Rule_12.7
     * MISRAC_WAIVER:
     * An arithmetic right shift of the signed integer "addhalf" by n is required.
     * It can not be cast to an unsigned because that would make a logical right shift
     * instead of the arithmetic shift that I need (I need the sign bit extension) to
     * mantain negative values.  I have confirmed that the DSP compiler is doing as
     * I expect with this code.
     */
    int32_t result = (int32_t)(addhalf >> n);
    return result;
}

static inline VXLIB_D64 sqrtdp (VXLIB_D64 a)
{
    VXLIB_D64    half  =  0.5;
    VXLIB_D64    OneP5 =  1.5;
    VXLIB_D64    x, y;
    int32_t     i;

    x = _rsqrdp(a);

    for( i = 0; i < NEWTON_RHAPSON_ITERATIONS; i++ ) {
        x = x * (OneP5 - (a * x * x * half));
    }

    y = a * x;

    if( a > 1.7976931348623157E+308 ) { /* DBL_MAX */
        y = 1.7976931348623157E+308;    /* DBL_MAX */
    }

    return (y);
}


static inline VXLIB_D64 recipdp (VXLIB_D64 a)
{
    VXLIB_D64    two  =  2.0;
    VXLIB_D64    max  = 1.7976931348623157E+308;
    VXLIB_D64    x;
    int32_t     i;

    x = _rcpdp(a);

    for( i = 0; i < 3; i++ ) {
        x = x * (two - (a * x));
    }

    if( _fabs(a) > max ) {
        x = 0.0;
    }

    return (x);
}

/*
 *  getWindowsInterpolate()
 *
 *  This function fetches the window neighborhood for the old image, the old gradient X, and the old gradient Y.
 *  It then does a bilinear interpolation on each window separatly based on the fractional portion of the x and y coordinates.
 *  The interpolted results are stored in 2 local buffers: winImage and winGrad.  The gradient values are stored
 *  interleaved in order to  reduce load/store instructions and should be better for cache. Finally, the gradient values
 *  are multiply accumulated to return the XX, XY, and YY results.
 *
 * [in]      image[]        Pointer to old image array (U8.0)
 * [in]      gradX[]        Pointer old X gradient image array from Scharr filter (S15.0)
 * [in]      gradY[]        Pointer old Y gradient image array from Scharr filter (S15.0)
 * [out]     winImage[]     Pointer to interpolated image window (SQ16.0)
 * [out]     winGrad[]      Pointer to interleaved interpolated gradient window (UQ32.0)
 * [in]      strideImage    Stride of old image input
 * [in]      strideGrad     Stride of old gradient image inputs
 * [in]      x              X coordinate for center of window (truncated to int) (SQ31.0)
 * [in]      y              Y coordinate for center of window (truncated to int) (SQ31.0)
 * [in]      weights        Packed 4x16-bit weights for bilinear interpolation operation (I64)
 * [in]      window_size    Window size
 * [in,out] *XX             Sum of squares of X gradient from interpolated window
 * [in,out] *XY             Sum of (X gradient)*(Y gradient) from interpolated window
 * [in,out] *YY             Sum of squares of Y gradient from interpolated window
 */
static inline void getWindowsInterpolate(const uint8_t image[restrict],
                                           const int16_t gradX[restrict],
                                           const int16_t gradY[restrict],
                                           int16_t winImage[restrict],
                                           uint32_t winGrad[restrict],
                                           int32_t strideImage,
                                           int32_t strideGrad,
                                           int32_t x,
                                           int32_t y,
                                           const int64_t weights,
                                           int32_t window_size,
                                           VXLIB_F32 *XX,
                                           VXLIB_F32 *XY,
                                           VXLIB_F32 *YY)
{
    int32_t i, j, k;
    int32_t winDiv2 = window_size/2;

    /* Calculate offsets for each row of the images */
    int32_t offsetImage = ((y-winDiv2)*strideImage) + (x-winDiv2);
    int32_t offsetGrad1 = ((y-winDiv2)*strideGrad) + (x-winDiv2);
    int32_t offsetGrad2 = offsetGrad1+strideGrad;

    /* Pack YY and XX into a __float2_t for SIMD-2 operations */
    __float2_t yyxx = _ftof2(*YY, *XX);

    j = k = 0;

    /* Collapse 2D processing into a single loop to reduce cycles due to
     * pipe-up and pipe-down since the loop will be so small */
    for(i=0; i < (window_size*window_size); i++)
    {
        int16_t xval, yval;
        int32_t xyval;
        uint32_t xypack;

        /* Step 1: Image Fetch and Interpolation */

        /* Fetch 4 pixels of old image */
        uint8_t imtl = image[offsetImage + k];
        uint8_t imtr = image[offsetImage + k + 1];
        uint8_t imbl = image[offsetImage + strideImage + k];
        uint8_t imbr = image[offsetImage + strideImage +k + 1];

        /* Pack into 4x16bit lanes for DOTP4H instruction*/
        int64_t left  = _itoll((uint32_t)imbl, (uint32_t)imtl);
        int64_t right = _itoll((uint32_t)imbr, (uint32_t)imtr);
        int64_t pixels = _dpackl2(right, left);

        /* Perform Bilinear interpolation by multuply accumulating all 4 pixels and weights */
        /* Saturation check (fits in 32 bits): MAX Weight = 0x4000, MAX pixel = 0xFF, MAX sum = 0x3FC000 */
        int32_t sum = _dotp4h(pixels, weights);

        /* Round result while shifting off extra fractional bits that were added to the weights,
         * taking into account that scharr gradient results are 5bits more than image (x32) */
        /* Saturation check (fits in 16 bits): MAX of ROUND = 0x3FC000 + 0x100 = 0x3FC100 >> 9 = 0x1FE0  */
        int16_t imval = (int16_t)INT_ROUND(sum, W_BITS-5U);



        /* Step 2: GradX Fetch and Interpolation */

        /* Fetch 4 pixels of old gradient X */
        uint32_t top = _mem4_const(&gradX[offsetGrad1+k]);
        uint32_t bot = _mem4_const(&gradX[offsetGrad2+k]);

        /* Pack into 4x16bit lanes, and perform bilinear interpolation using DOTP4H instruction */
        /* Saturation check (fits in 32 bits): MAX Weight = 0x4000, MAX pixel = 0x1FE0 (+1 sign bit), MAX sum = 0x7F80000 (+1 sign bit)*/
        pixels = _itoll(bot, top);
        sum = _dotp4h(pixels, weights);

        /* Round result while shifting off extra fractional bits that were added to the weights */
        /* Saturation check (fits in 16 bits): MAX of ROUND = 0x7F80000 + 0x2000 = 0x7F82000 >> 14 = 0x1FE0 (+1 sign bit) */
        xval = (int16_t)INT_ROUND(sum, W_BITS);



        /* Step 3: GradY Fetch and Interpolation */

        /* Fetch 4 pixels of old gradient Y */
        top = _mem4_const(&gradY[offsetGrad1+k]);
        bot = _mem4_const(&gradY[offsetGrad2+k]);

        /* Pack into 4x16bit lanes, and perform bilinear interpolation using DOTP4H instruction */
        /* Saturation check (fits in 32 bits): MAX Weight = 0x4000, MAX pixel = 0x1FE0 (+1 sign bit), MAX sum = 0x7F80000 (+1 sign bit)*/
        pixels = _itoll(bot, top);
        sum = _dotp4h(pixels, weights);

        /* Round result while shifting off extra fractional bits that were added to the weights */
        /* Saturation check (fits in 16 bits): MAX of ROUND = 0x7F80000 + 0x2000 = 0x7F82000 >> 14 = 0x1FE0 (+1 sign bit) */
        yval = (int16_t)INT_ROUND(sum, W_BITS);



        /* Store interpolated image and interpolated gradients to their window buffers */
        xypack = _pack2((uint32_t)yval, (uint32_t)xval);
        winImage[i] = imval;
        winGrad[i] = xypack;


        /* Equivalent code rewritten for SIMD of 2 operations at a time:
         *   *XX += (VXLIB_F32)(xval*xval);
         *   *YY += (VXLIB_F32)(yval*yval);
         */
        yyxx = _daddsp(_dintspu(_mpy2ll((int32_t)xypack, (int32_t)xypack)), yyxx);

        /* Saturation check (fits in 32 bits): MAX of MPY = 0x1FE0*0x1FE0 = 0x03F80400 (+1 sign bit) 5 bits headroom */
        xyval= (int32_t)xval*(int32_t)yval;

        /* Saturation check (fits in F32): MAX of SUM will overflow 32 bits, put in F32 */
        *XY += (VXLIB_F32)xyval;

        /* The remaining code is done to manage the update of image pointers when
         * we have reached the end of processing each row of the window */
        j++;

        if(j == window_size) {
            j = 0;
            offsetImage += strideImage;
            offsetGrad1+= strideGrad;
            offsetGrad2+= strideGrad;
        }
        k = _mvd(j);
    }

    /* Update the output data from the inner loop SIMD version of the variable */ 
    *XX = _lof2(yyxx);
    *YY = _hif2(yyxx);
}


/*
 *  diffNewWindowInterpolate()
 *
 *  This function fetches the window neighborhood for the new image, performing a bilinear interpolation based on the fractional
 *  portion of the x and y coordinates. The interpolated results are compared to the old window, and the sum of the products of the
 *  intensity difference and the gradient values across the window are returned.
 *
 * [in]      image[]        Pointer to new image array (U8.0)
 * [in]      winImage[]     Pointer to interpolated image window (SQ15.0)
 * [in]      winGrad[]      Pointer to interleaved interpolated gradient window (UQ32.0)
 * [in]      stride         Stride of new image input
 * [in]      x              X coordinate for center of window (truncated to int) (SQ31.0)
 * [in]      y              Y coordinate for center of window (truncated to int) (SQ31.0)
 * [in]      weights        Packed 4x16-bit weights for bilinear interpolation operation (I64)
 * [in]      window_size    Window size
 * [in,out] *zx             Sum of products of intensity difference and x gradients across window
 * [in,out] *zy             Sum of products of intensity difference and y gradients across window
 */
static inline void diffNewWindowInterpolate(const uint8_t image[restrict],
                                                 const int16_t winImage[restrict],
                                                 const uint32_t winGrad[restrict],
                                                 int32_t stride,
                                                 int32_t x,
                                                 int32_t y,
                                                 const int64_t weights,
                                                 int32_t window_size,
                                                 VXLIB_F32 *zx,
                                                 VXLIB_F32 *zy)
{
    int32_t i, j, k;
    int32_t winDiv2 = window_size/2;

    /* Calculate offsets for each row of the image */
    int32_t offset = ((y-winDiv2)*stride) + (x-winDiv2);

    /* Pack zy and zx into a __float2_t for SIMD-2 operations */
    __float2_t z = _ftof2(*zy, *zx);

    j = k = 0;

    /* Collapse 2D processing into a single loop to reduce cycles due to
     * pipe-up and pipe-down since the loop will be so small */
    for(i=0; i < (window_size*window_size); i++)
    {
        /* Fetch 4 pixels of new image */
        uint8_t imtl = image[offset + k];
        uint8_t imtr = image[offset + k + 1];
        uint8_t imbl = image[offset + stride + k];
        uint8_t imbr = image[offset + stride + k + 1];

        /* Pack into 4x16bit lanes for DOTP4H instruction*/
        int64_t left  = _itoll((uint32_t)imbl, (uint32_t)imtl);
        int64_t right = _itoll((uint32_t)imbr, (uint32_t)imtr);
        int64_t pixels = _dpackl2(right, left);

        /* Perform Bilinear interpolation by multuply accumulating all 4 pixels and weights */
        /* Saturation check (fits in 32 bits): MAX Weight = 0x4000, MAX pixel = 0xFF, MAX sum = 0x3FC000 */
        int32_t sum = _dotp4h(pixels, weights);

        /* Round result while shifting off extra fractional bits that were added to the weights,
         * taking into account that scharr gradient results are 5bits more than image (x32) */
        /* Saturation check (fits in 16 bits): MAX of ROUND = 0x3FC000 + 0x100 = 0x3FC100 >> 9 = 0x1FE0  */
        int16_t imval = (int16_t)INT_ROUND(sum, W_BITS-5U);





        /* Subtract the old image value for the pixel from the new image value */
        /* Saturation check (fits in 16 bits): MAX of DIFF = 0x1FE0 (+1 sign bit) */
        int32_t    diff = (int32_t)imval - (int32_t)winImage[i];

        /* Multiply the difference by the old gradient values, and convert to F32 */
        /* Saturation check (fits in 32 bits): MAX of MPY = 0x1FE0*0x1FE0 = 0x03F80400 (+1 sign bit) 5 bits headroom */
        __float2_t xxyy = _dintsp(_mpy2ll((int32_t)winGrad[i], (int32_t)_pack2((uint32_t)diff, (uint32_t)diff)));

        /* Add to running sum of products */
        /* Saturation check (fits in F32): MAX of SUM will overflow 32 bits, put in F32 */
        z = _daddsp(xxyy, z); 

        /* The remaining code is done to manage the update of image pointers when
         * we have reached the end of processing each row of the window */
        j++;

        if(j == window_size) {
            j = 0;
            offset += stride;
        }
        k = j;
    }

    /* Update the output data from the inner loop SIMD version of the variable */ 
    *zx = _lof2(z);
    *zy = _hif2(z);
}


VXLIB_STATUS VXLIB_trackFeaturesLK_i8u(const uint8_t old_image[restrict],
                                       const VXLIB_bufParams2D_t *old_image_addr,
                                       const uint8_t new_image[restrict],
                                       const VXLIB_bufParams2D_t *new_image_addr,
                                       const int16_t old_gradX[restrict],
                                       const VXLIB_bufParams2D_t *old_gradX_addr,
                                       const int16_t old_gradY[restrict],
                                       const VXLIB_bufParams2D_t *old_gradY_addr,
                                       __float2_t old_points[restrict],
                                       __float2_t new_points[restrict],
                                       uint8_t tracking_status[restrict],
                                       uint32_t num_points,
                                       uint32_t max_iters,
                                       VXLIB_F32 epsilon,
                                       VXLIB_F32 scale,
                                       uint8_t window_size,
                                       uint8_t level,
                                       uint8_t termination,
                                       uint8_t scratch[restrict],
                                       uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_TRACKFEATURESLK_I8U_CHECK_PARAMS)
    status = VXLIB_trackFeaturesLK_i8u_checkParams(old_image, old_image_addr, new_image, new_image_addr,
                                                   old_gradX, old_gradX_addr, old_gradY, old_gradY_addr,
                                                   old_points, new_points, tracking_status, num_points, max_iters,
                                                   epsilon, scale, window_size, level, termination, scratch, scratch_size);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t i;
        int32_t winDiv2 = (int32_t)window_size/2;
        int32_t width = old_image_addr->dim_x;
        int32_t height = old_image_addr->dim_y;
        int32_t window_size_sqrd = (int32_t)window_size * (int32_t)window_size;
        int32_t window_size_sqrdx2 = 2*window_size_sqrd;

        /* Partition scratch memory into 2 buffers, one for interpolated old image, and another for
         * interpolated old gradient (interleaved) */
        /* MISRA.CAST.PTR
         * MISRAC_2004 Rule_11.4
         * MISRAC_WAIVER:
         * I need two local buffers which are of different types.  I don't want to expose both
         * to the API, when a single buffer would make the API simpler.  Therefore, I can partition
         * the scratch buffer internal to the function, and I take care that the alignment is correct.
         * The DSP is using the unaligned access instructions anyway.
         */
        int16_t  *winImage = (int16_t *)&scratch[0];
        uint32_t *winGrad = (uint32_t *)&scratch[(2 * window_size_sqrd) + 2];

        /* Packed min and max values for out of bounds comparison */
        int32_t maxY = height - winDiv2 - 2;
        int32_t maxX = width - winDiv2 - 2;
        int32_t minXY = winDiv2 + 1;
        int32_t maxCmp = (int32_t)_pack2((uint32_t)maxY, (uint32_t)maxX);
        int32_t minCmp = (int32_t)_pack2((uint32_t)minXY, (uint32_t)minXY);

        /* Compute 1/(2*window_size*window_size) outside the loop for use later */
        VXLIB_F32 eigDiv = (VXLIB_F32)recipdp((VXLIB_D64)window_size_sqrdx2);

        /* Pack scale into 2 lanes */
        __float2_t scale2 = _ftof2(scale, scale);

        /* Iterate through each point in the list */
        for(i = 0; i < (int32_t)num_points; i++)
        {
            /* Update points according to scale */
            old_points[i] = _dmpysp(old_points[i], scale2);
            new_points[i] = _dmpysp(new_points[i], scale2);

            /* Only operate on valid points */
            if (tracking_status[i] != 0)
            {
                uint32_t outOfBounds = 0;

                /* Get points for center of window, find truncated version of them, and pack for border compare */
                VXLIB_F32 oldXf = _lof2(old_points[i]);
                VXLIB_F32 oldYf = _hif2(old_points[i]);
                int32_t oldXi = (int32_t)oldXf;
                int32_t oldYi = (int32_t)oldYf;
                uint32_t oldPtsi = _pack2((uint32_t)oldYi, (uint32_t)oldXi);

                /* Ignore the borders (+1 accounts for gradient borders)*/
                outOfBounds = (uint32_t)_cmpgt2(minCmp, (int32_t)oldPtsi) | (uint32_t)_cmpgt2((int32_t)oldPtsi, maxCmp);

                /* Tracking is lost coordinate goes out of bounds */
                if( outOfBounds != 0) {
                    if(level == 0) {
                        tracking_status[i] = 0;
                    }
                } else {

                    VXLIB_F32 dx = oldXf - (VXLIB_F32)oldXi;
                    VXLIB_F32 dy = oldYf - (VXLIB_F32)oldYi;
                    int32_t a[4];
                    VXLIB_F32 XX = 0.0;
                    VXLIB_F32 XY = 0.0;
                    VXLIB_F32 YY = 0.0;
                    VXLIB_F32 Df;
                    VXLIB_D64 D;
                    int64_t weights;
                    VXLIB_F32 minEig;
                    VXLIB_F32 ftmp, tmp;
                    VXLIB_F32 flt_scale = FLT_SCALE;

                    /* Compute coefficients for bilinear interpolation and pack them into 4x16bits */
                    ftmp = ((1.0f - dx) * (1.0f - dy) * (VXLIB_F32)FRACTIONAL) + 0.5f; a[0] = (int32_t)ftmp;
                    ftmp = (       (dx) * (1.0f - dy) * (VXLIB_F32)FRACTIONAL) + 0.5f; a[1] = (int32_t)ftmp;
                    ftmp = ((1.0f - dx) * (dy)        * (VXLIB_F32)FRACTIONAL) + 0.5f; a[2] = (int32_t)ftmp;
                    a[3] = (int32_t)FRACTIONAL - a[0] - a[1] - a[2];

                    weights = _itoll(_pack2((uint32_t)a[3],(uint32_t)a[2]), _pack2((uint32_t)a[1],(uint32_t)a[0]));

                    /* Fetch window around each point for old image, and gradient images.  Interpolate,
                     * and put in local window buffers.  Compute XX, XY, and YY. */
                    getWindowsInterpolate(old_image, old_gradX, old_gradY, 
                                          winImage, winGrad,
                                          old_image_addr->stride_y, old_gradX_addr->stride_y/2,
                                          oldXi, oldYi, weights, (int32_t)window_size, &XX, &XY, &YY);

                    /* Remove the fractional bits that were added to the coefficients */
                    XX *= flt_scale;
                    XY *= flt_scale;
                    YY *= flt_scale;

                    /* Compute the determinate and minimum eigenvalue of the matrix */
                    Df = (XX*YY) - (XY*XY);
                    D = (VXLIB_D64)Df;
                    tmp = ((XX-YY)*(XX-YY)) + (4.0f*(XY*XY));
                    minEig = (VXLIB_F32)((YY + XX) - (VXLIB_F32)sqrtdp((VXLIB_D64)tmp))*eigDiv;

                    /* Tracking is lost if the matrix is invertible ( D < 10e-7 ) or
                     * Minimum eigenvalue of the matrix is smaller than 10e-4. */
                    if( (minEig < 1.0e-04F) || (D < 1.0e-07F) )
                    {
                        if( level == 0 )
                        {
                            tracking_status[i] = 0;
                        }
                    } else {
                        /* MISRA.ITER.ONETERM
                         * MISRAC_2004 Rule_14.6
                         * MISRAC_WAIVER:
                         * This loop has 3 break statments.
                         * I am able to remove one or both of these by adding a flag that the
                         * loop can conditionally terminate in, but the performance suffers.
                         * Therefore, we are requesting a waiver for this in the interest of
                         * performance.
                         */

                        uint32_t j = 0;
                        VXLIB_F32 newXf, newYf;

                        /* Initialize the previous delta values that will help determine when to stop iterating */
                        VXLIB_F32 prevDelta_x = 0.0f;
                        VXLIB_F32 prevDelta_y = 0.0f;

                        /* 1.0/D */
                        D = recipdp(D);

                        /* Fetch new points from list */
                        newXf = _lof2(new_points[i]);
                        newYf = _hif2(new_points[i]);

                        /* Iterate until converged based on policy */
                        while( (j < max_iters) || (termination == VXLIB_TERM_EPSILON) )
                        {
                            /* Get points for center of window, find truncated version of them, and pack for border compare */
                            int32_t newXi = (int32_t)newXf;
                            int32_t newYi = (int32_t)newYf;
                            uint32_t newPtsi = _pack2((uint32_t)newYi, (uint32_t)newXi);
                            VXLIB_F32    zxf = 0.0f;
                            VXLIB_F32    zyf = 0.0f;
                            VXLIB_D64    zx, zy;
                            VXLIB_F32    delta_x, delta_y;

                            /* Ignore the borders (+1 accounts for gradient borders)*/
                            outOfBounds = (uint32_t)_cmpgt2(minCmp, (int32_t)newPtsi) | (uint32_t)_cmpgt2((int32_t)newPtsi, maxCmp);

                            /* Tracking is lost coordinate goes out of bounds */
                            if( outOfBounds != 0) {
                                if(level == 0) {
                                    tracking_status[i] = 0;
                                }
                                break;
                            }

                            dx = newXf - (VXLIB_F32)newXi;
                            dy = newYf - (VXLIB_F32)newYi;

                            /* Compute coefficients for bilinear interpolation and pack them into 4x16bits */
                            ftmp = ((1.0f - dx) * (1.0f - dy) * (VXLIB_F32)FRACTIONAL) + 0.5f; a[0] = (int32_t)ftmp;
                            ftmp = (       (dx) * (1.0f - dy) * (VXLIB_F32)FRACTIONAL) + 0.5f; a[1] = (int32_t)ftmp;
                            ftmp = ((1.0f - dx) * (dy)        * (VXLIB_F32)FRACTIONAL) + 0.5f; a[2] = (int32_t)ftmp;
                            a[3] = (int32_t)FRACTIONAL - a[0] - a[1] - a[2];

                            weights = _itoll(_pack2((uint32_t)a[3],(uint32_t)a[2]), _pack2((uint32_t)a[1],(uint32_t)a[0]));

                            /* Fetch window around each point for new image and compute  zx and zy differences */
                            diffNewWindowInterpolate(new_image, winImage, winGrad, new_image_addr->stride_y,
                                                     newXi, newYi, weights, (int32_t)window_size, &zxf, &zyf);

                            zx = (VXLIB_D64)zxf * (VXLIB_D64)flt_scale;
                            zy = (VXLIB_D64)zyf * (VXLIB_D64)flt_scale;

                            /* Compute deltas for each coordinate */
                            delta_x = (VXLIB_F32)((((VXLIB_D64)XY*zy) - ((VXLIB_D64)YY*zx)) * D);
                            delta_y = (VXLIB_F32)((((VXLIB_D64)XY*zx) - ((VXLIB_D64)XX*zy)) * D);

                            newXf += delta_x;
                            newYf += delta_y;

                            /* Stop iterating if termination policy is "epsilon" AND the residual of the
                             * affine motion vector is < epsilon */
                            if( (((delta_x*delta_x) + (delta_y*delta_y)) <= epsilon) &&
                                ( (termination == VXLIB_TERM_EPSILON) || (termination == VXLIB_TERM_BOTH) ))
                            {
                                break;
                            } 

                            /* Stop iterating if sum of current change and previous change is < 0.01 */
                            if( (j > 0) && (_fabsf(delta_x + prevDelta_x) < 0.01f) &&
                                           (_fabsf(delta_y + prevDelta_y) < 0.01f) )
                            {
                                newXf -= delta_x*0.5f;
                                newYf -= delta_y*0.5f;
                                break;
                            }
                            prevDelta_x = delta_x;
                            prevDelta_y = delta_y;
                            j++;
                        }

                        /* Save points back to new list */
                        new_points[i] = _ftof2(newYf, newXf);
                    }
                }
            }
        }
    }

    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_TRACKFEATURESLK_I8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_TRACKFEATURESLK_I8U_CHECK_PARAMS))

VXLIB_STATUS    VXLIB_trackFeaturesLK_i8u_checkParams(const uint8_t old_image[restrict],
                                                   const VXLIB_bufParams2D_t *old_image_addr,
                                                   const uint8_t new_image[restrict],
                                                   const VXLIB_bufParams2D_t *new_image_addr,
                                                   const int16_t old_gradX[restrict],
                                                   const VXLIB_bufParams2D_t *old_gradX_addr,
                                                   const int16_t old_gradY[restrict],
                                                   const VXLIB_bufParams2D_t *old_gradY_addr,
                                                   const __float2_t old_points[restrict],
                                                   const __float2_t new_points[restrict],
                                                   const uint8_t tracking_status[restrict],
                                                   uint32_t num_points,
                                                   uint32_t max_iters,
                                                   VXLIB_F32 epsilon,
                                                   VXLIB_F32 scale,
                                                   uint8_t window_size,
                                                   uint8_t level,
                                                   uint8_t termination,
                                                   const uint8_t scratch[restrict],
                                                   uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((old_image == NULL) || (new_image == NULL) || (old_gradX == NULL) ||
       (old_gradY == NULL) || (old_points == NULL) || (new_points == NULL) ||
       (tracking_status == NULL) || (scratch == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((old_image_addr->dim_x != new_image_addr->dim_x) ||
              (old_gradX_addr->dim_x != old_gradY_addr->dim_x) ||
              (old_image_addr->dim_y != new_image_addr->dim_y) ||
              (old_gradX_addr->dim_y != old_gradY_addr->dim_y) ||
              (old_image_addr->stride_y < old_image_addr->dim_x) ||
              (new_image_addr->stride_y < new_image_addr->dim_x) ||
              (old_gradX_addr->stride_y != old_gradY_addr->stride_y) ||
              (old_gradX_addr->stride_y < (old_gradX_addr->dim_x*2))) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((old_image_addr->data_type != VXLIB_UINT8) ||
               (new_image_addr->data_type != VXLIB_UINT8) ||
               (old_gradX_addr->data_type != VXLIB_INT16) ||
               (old_gradY_addr->data_type != VXLIB_INT16)) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if((termination != VXLIB_TERM_ITERATIONS) &&
             (termination != VXLIB_TERM_EPSILON) &&
             (termination != VXLIB_TERM_BOTH)) {
        status = VXLIB_ERR_INVALID_VALUE;
    } else if((int32_t)scratch_size < (((int32_t)window_size*(int32_t)window_size*6) + 2)) {
        status = VXLIB_ERR_BUFFER_TOO_SMALL;
    } else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
