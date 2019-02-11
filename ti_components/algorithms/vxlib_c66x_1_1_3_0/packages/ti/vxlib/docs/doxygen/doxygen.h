/* ======================================================================== *
 * VXLIB -- TI OpenVX Kernel Library                                        *
 *                                                                          *
 *   Doxygen generation header file                                         *
 *                                                                          *
 * Copyright (C) 2016 - 2017 Texas Instruments Incorporated                 *
 *                           http://www.ti.com/                             *
 *                                                                          *
 *                                                                          *
 *  Redistribution and use in source and binary forms, with or without      *
 *  modification, are permitted provided that the following conditions      *
 *  are met:                                                                *
 *                                                                          *
 *    Redistributions of source code must retain the above copyright        *
 *    notice, this list of conditions and the following disclaimer.         *
 *                                                                          *
 *    Redistributions in binary form must reproduce the above copyright     *
 *    notice, this list of conditions and the following disclaimer in the   *
 *    documentation and/or other materials provided with the                *
 *    distribution.                                                         *
 *                                                                          *
 *    Neither the name of Texas Instruments Incorporated nor the names of   *
 *    its contributors may be used to endorse or promote products derived   *
 *    from this software without specific prior written permission.         *
 *                                                                          *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    *
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        *
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     *
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
 * ======================================================================== */

/**
 * @mainpage  VXLIB Function Reference
 *
 *
 * @HLINE
 *
 *
 * @section content  Contents
 *
 *  <ol>
 *    <li> @ref intro
 *    <li> @ref conventions
 *    <li> OpenVX 1.1 Vision Functions
 *    <ol>
 *      <li> @subpage absdiff
 *      <li> @subpage accumulate
 *      <li> @subpage accumulate_squared
 *      <li> @subpage accumulate_weighted
 *      <li> @subpage arithmetic_add
 *      <li> @subpage arithmetic_sub
 *      <li> @subpage bitwise_and
 *      <li> @subpage bitwise_xor
 *      <li> @subpage bitwise_or
 *      <li> @subpage bitwise_not
 *      <li> @subpage box_filter
 *      <li> @subpage canny_edge
 *      <li> @subpage channel_combine
 *      <li> @subpage channel_extract
 *      <li> @subpage color_convert
 *      <li> @subpage convert_bit
 *      <li> @subpage convolution
 *      <li> @subpage dilate_img
 *      <li> @subpage equalize_hist
 *      <li> @subpage erode_img
 *      <li> @subpage fast_corners
 *      <li> @subpage gauss_filter
 *      <li> @subpage nonlinear_filter
 *      <li> @subpage harris_corners
 *      <li> @subpage histogram
 *      <li> @subpage gaussian_img_pyr
 *      <li> @subpage laplacian_img_pyr
 *      <li> @subpage laplacian_reconstruct
 *      <li> @subpage integral_img
 *      <li> @subpage magnitude
 *      <li> @subpage mean_std_dev
 *      <li> @subpage median_filter
 *      <li> @subpage min_max_loc
 *      <li> @subpage optical_flow_lk
 *      <li> @subpage phase
 *      <li> @subpage multiplication
 *      <li> @subpage remap
 *      <li> @subpage scale
 *      <li> @subpage sobel
 *      <li> @subpage lookup
 *      <li> @subpage thresholding
 *      <li> @subpage warp_affine
 *      <li> @subpage warp_perspective
 *    </ol>
 *  </ol>
 *
 *
 * @HLINE
 *
 *
 * @section intro  Introduction
 *
 *  VXLIB provides a collection of C-callable high-performance routines that are
 *  developed to be compatible with the kernels defined in the Khronos OpenVX specificaiton.
 *  These functions exploit the high performance capabilities of Texas Instruments
 *  DSPs.
 *
 *  All functions in VXLIB have been developed for a little-endian memory model.
 *  Some may work in a big-endian memory model as well, however, their functionality
 *  is not guaranteed.
 *
 *
 * @HLINE
 *
 *
 * @section conventions  Notational Conventions
 *
 *  All functions within VXLIB following the naming conventions described below.
 *
 *    -#  Each function begins with the prefix <tt>VXLIB_</tt>.  This serves to prevent
 *        namespace conflicts.
 *    -#  The prefix is followed by an English functional descriptor.  The functional
 *        descriptor was chosen to follow the descriptor used in OpenVX node API, where
 *        applicable.
 *    -#  Further description after the English words (i.e. variants, border modes, bit depths, numbers)
 *        are separated by underscores: '_'
 *    -#  All kernels use UNDEFINED border modes, unless specified by the following convention:\n
 *        bc=constant border mode\n
 *        br=replicate border mode
 *    -#  Filter kernel or window sizes are MxN format (e.g. 3x3).
 *    -#  Conversion of channels/bit depths are XtoY format (e.g. 4to1, 8to16).
 *    -#  Data types of buffer parameters come last in the kernel name, and use the following codes:\n
 *        i=input\n
 *        o=output\n
 *        io=inout\n
 *        c=coefficients\n
 *        s=signed\n
 *        u=unsigned\n
 *        f=float
 *    -#  Scalar inputs/outputs, lists, and scratch buffers are not part of the name.
 */


/**
 * @page absdiff  Absolute Difference
 *
 *  @section intro1 OpenVX Function Description
 *  - Computes the absolute difference between two images.
 *
 *  @section ref1 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/dc/ddf/group__group__vision__function__absdiff.html
 *
 *  @section apis1 VXLIB APIs
 *  - @ref VXLIB_absDiff_i8u_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_absDiff_i16s_i16s_o16s : Input and output images are S16 format
 */
/**
 * @page accumulate  Accumulate
 *
 *  @section intro2 OpenVX Function Description
 *  - Accumulates an input image into output image.
 *
 *  @section ref2 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d0/d77/group__group__vision__function__accumulate.html
 *
 *  @section apis2 VXLIB API
 *  - @ref VXLIB_accumulateImage_i8u_io16s : Input image is U8 format and output image is S16 format
 *    - Calls internally: @ref VXLIB_add_i8u_i16s_o16s
 */
/**
 * @page accumulate_squared  Accumulate Squared
 *
 *  @section intro3 OpenVX Function Description
 *  - Accumulates a squared value from an input image to an output image.
 *
 *  @section ref3 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d0/d2c/group__group__vision__function__accumulate__square.html
 *
 *  @section apis3 VXLIB API
 *  - @ref VXLIB_accumulateSquareImage_i8u_io16s : Input image is U8 format and output image is S16 format
 *    - Calls internally: @ref VXLIB_addSquare_i8u_i16s_o16s
 */
/**
 * @page accumulate_weighted  Accumulate Weighted
 *
 *  @section intro4 OpenVX Function Description
 *  - Accumulates a weighted value from an input image to an output image.
 *
 *  @section ref4 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d2/d2e/group__group__vision__function__accumulate__weighted.html
 *
 *  @section apis4 VXLIB API
 *  - @ref VXLIB_accumulateWeightedImage_i8u_io8u : Input and output images are U8 format
 *    - Calls internally: @ref VXLIB_addWeight_i8u_i8u_o8u
 */
/**
 * @page arithmetic_add  Arithmetic Addition
 *
 *  @section intro5 OpenVX Function Description
 *  - Performs addition between two images.
 *
 *  @section ref5 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d6/db0/group__group__vision__function__add.html
 *
 *  @section apis5 VXLIB APIs
 *  - @ref VXLIB_add_i8u_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_add_i8u_i8u_o16s : Input images are U8 format and output image is S16 format
 *  - @ref VXLIB_add_i8u_i16s_o16s : One input image is U8 format, one input image is S16 format and output image is S16 format
 *  - @ref VXLIB_add_i16s_i16s_o16s : Input and output images are S16 format
 */
/**
 * @page arithmetic_sub  Arithmetic Subtraction
 *
 *  @section intro6 OpenVX Function Description
 *  - Performs subtraction between two images.
 *
 *  @section ref6 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d6/d6d/group__group__vision__function__sub.html
 *
 *  @section apis6 VXLIB APIs
 *  - @ref VXLIB_subtract_i8u_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_subtract_i8u_i8u_o16s : Input images are U8 format and output image is S16 format
 *  - @ref VXLIB_subtract_i8u_i16s_o16s : One input image is U8 format, one input image is S16 format and output image is S16 format
 *  - @ref VXLIB_subtract_i16s_i16s_o16s : Input and output images are S16 format
 */
/**
 * @page bitwise_and  Bitwise AND
 *
 *  @section intro7 OpenVX Function Description
 *  - Performs a bitwise AND operation between two images.
 *
 *  @section ref7 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d4/d4e/group__group__vision__function__and.html
 *
 *  @section apis7 VXLIB API
 *  - @ref VXLIB_and_i8u_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page bitwise_xor  Bitwise EXCLUSIVE OR
 *
 *  @section intro8 OpenVX Function Description
 *  - Performs a bitwise EXCLUSIVE OR (XOR) operation between two images.
 *
 *  @section ref8 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d3/dd1/group__group__vision__function__xor.html
 *
 *  @section apis8 VXLIB API
 *  - @ref VXLIB_xor_i8u_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page bitwise_or  Bitwise INCLUSIVE OR
 *
 *  @section intro9 OpenVX Function Description
 *  - Performs a bitwise INCLUSIVE OR operation between two images.
 *
 *  @section ref9 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d2/d5d/group__group__vision__function__or.html
 *
 *  @section apis9 VXLIB API
 *  - @ref VXLIB_or_i8u_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page bitwise_not  Bitwise NOT
 *
 *  @section intro10 OpenVX Function Description
 *  - Performs a bitwise NOT operation on an images.
 *
 *  @section ref10 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/dc/d06/group__group__vision__function__not.html
 *
 *  @section apis10 VXLIB API
 *  - @ref VXLIB_not_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page box_filter  Box Filter
 *
 *  @section intro11 OpenVX Function Description
 *  - Computes a Box filter over a window of the input image.
 *
 *  @section ref11 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/da/d7c/group__group__vision__function__box__image.html
 *
 *  @section apis11 VXLIB API
 *  - @ref VXLIB_box_3x3_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page canny_edge  Canny Edge Detector
 *
 *  @section intro12 OpenVX Function Description
 *  - Provides a Canny edge detector kernel.
 *
 *  @section ref12 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d7/d71/group__group__vision__function__canny.html
 *
 *  @section apis12 VXLIB API
 *  - @ref VXLIB_sobel_3x3_i8u_o16s_o16s : Input image is U8 format, output gradients are S16 format
 *  - @ref VXLIB_sobel_5x5_i8u_o16s_o16s : Input image is U8 format, output gradients are S16 format
 *  - @ref VXLIB_sobel_7x7_i8u_o16s_o16s : Input image is U8 format, output gradients are S16 format
 *  - @ref VXLIB_normL1_i16s_i16s_o16u : Input gradients are S16 format, and output magnitude is U16 format
 *  - @ref VXLIB_normL2_i16s_i16s_o16u : Input gradients are S16 format, and output magnitude is U16 format
 *  - @ref VXLIB_cannyNMS_i16s_i16s_i16u_o8u : Input gradients are S16 format, input magnitude is U16 format, and output edgeMap is U8 format
 *  - @ref VXLIB_doubleThreshold_i16u_i8u : Input magnitude is U16 format, input/output edgeMap is U8 format, and output edgeList is U32 format
 *  - @ref VXLIB_edgeTracing_i8u : Input/output edgeMap is U8 format, and input edgeList is U32 format
 *  - @ref VXLIB_thresholdBinary_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page channel_combine  Channel Combine
 *
 *  @section intro13 OpenVX Function Description
 *  - Implements the Channel Combine Kernel.
 *
 *  @section ref13 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/de/df2/group__group__vision__function__channelcombine.html
 *
 *  @section apis13 VXLIB APIs
 *  - @ref VXLIB_channelCopy_1to1_i8u_o8u : Input (1) and output (1) images are U8 format
 *  - @ref VXLIB_channelCombine_2to1_i8u_o8u : Input (2) and output (1) images are U8 format
 *  - @ref VXLIB_channelCombine_3to1_i8u_o8u : Input (3) and output (1) images are U8 format
 *  - @ref VXLIB_channelCombine_4to1_i8u_o8u : Input (4) and output (1) images are U8 format
 *  - @ref VXLIB_channelCombine_yuyv_i8u_o8u : Input (3) and output (1) images are U8 format
 */
/**
 * @page channel_extract  Channel Extract
 *
 *  @section intro14 OpenVX Function Description
 *  - Implements the Channel Extraction Kernel.
 *
 *  @section ref14 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/dd/dc1/group__group__vision__function__channelextract.html
 *
 *  @section apis14 VXLIB API
 *  - @ref VXLIB_channelCopy_1to1_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_channelExtract_1of2_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_channelExtract_1of3_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_channelExtract_1of4_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page color_convert  Color Convert
 *
 *  @section intro15 OpenVX Function Description
 *  - Implementes the Color Conversion Kernel.
 *
 *  @section ref15 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d1/dc2/group__group__vision__function__colorconvert.html
 *
 *  @section apis15 VXLIB API
 *  - @ref VXLIB_colorConvert_IYUVtoNV12_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_IYUVtoRGB_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_NVXXtoRGB_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_RGBtoIYUV_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_RGBtoNV12_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_RGBtoRGBX_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_RGBtoYUV4_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_RGBXtoNV12_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_RGBXtoRGB_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_YUVXtoNV12_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_YUVXtoRGB_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u : Input and output images are U8 format
 *
 *  @section conventions15 VXLIB Color Convert API General Conventions
 *  - Some color formats contain only a single plane for the full image: (e.g. RGB, RGBX, and YUVX).  Others
 *    require 2 (NVXX, NV12) or 3 planes (YUV4, IYUV).
 *  - The way each color format interprets the dimensional information in these addressing structures follows the
 *    convention below.  In the description below, 'sizeof(dataType)' refers to the size in bytes of the pointer type for
 *    each function (e.g. sizeof(u8) = 1; sizeof(s16) = 2).
 *    - RGB (1 plane)
 *      - 'dim_x' refers to the number of RGB pixel units per line
 *      - 'dim_y' refers to the number of lines in the image
 *      - 'stride_y' should be at least ('dim_x' * 3 * sizeof(dataType)) bytes
 *    - RGBX (1 plane)
 *      - 'dim_x' refers to the number of RGBX pixel units per line
 *      - 'dim_y' refers to the number of lines in the image
 *      - 'stride_y' should be at least ('dim_x' * 4 * sizeof(dataType)) bytes
 *    - YUVX (1 plane)
 *      - 'dim_x' refers to the number of luma pixel units per line
 *      - 'dim_y' refers to the number of lines in the image
 *      - 'stride_y' should be at least ('dim_x' * 2 * sizeof(dataType)) bytes
 *    - NVXX & NV12 (2 planes)
 *      - plane0
 *        - 'dim_x' refers to the number of luma pixel units per line
 *        - 'dim_y' refers to the number of lines in the luma plane
 *        - 'stride_y' refers to the stride of the luma plane, and should be at least ('dim_x' * 1 * sizeof(dataType)) bytes
 *      - plane1
 *        - 'dim_x' refers to the number of bytes per line (should be equal to plane0.dim_x)
 *        - 'dim_y' refers to the number of lines in the interleaved chroma plane (should be equal to plane0.dim_y / 2)
 *        - 'stride_y' refers to the stride of the interleaved chroma plane, and should be at least ('dim_x' * 1 * sizeof(dataType)) bytes
 *    - YUV4 (3 planes)
 *      - plane0
 *        - 'dim_x' refers to the number of luma pixel units per line
 *        - 'dim_y' refers to the number of lines in the luma plane
 *        - 'stride_y' refers to the stride of the luma plane, and should be at least ('dim_x' * 1 * sizeof(dataType)) bytes
 *      - plane1
 *        - 'dim_x' refers to the number of chroma pixel units per line (should be equal to plane0.dim_x)
 *        - 'dim_y' refers to the number of lines in the chroma plane (should be equal to plane0.dim_y)
 *        - 'stride_y' refers to the stride of the chroma plane, and should be at least ('dim_x' * 1 * sizeof(dataType)) bytes
 *      - plane2
 *        - 'dim_x' refers to the number of chroma pixel units per line (should be equal to plane0.dim_x)
 *        - 'dim_y' refers to the number of lines in the chroma plane (should be equal to plane0.dim_y)
 *        - 'stride_y' refers to the stride of the chroma plane, and should be at least ('dim_x' * 1 * sizeof(dataType)) bytes
 *    - IYUV (3 planes)
 *      - plane0
 *        - 'dim_x' refers to the number of luma pixel units per line
 *        - 'dim_y' refers to the number of lines in the luma plane
 *        - 'stride_y' refers to the stride of the luma plane, and should be at least ('dim_x' * 1 * sizeof(dataType)) bytes
 *      - plane1
 *        - 'dim_x' refers to the number of chroma pixel units per line (should be equal to plane0.dim_x / 2)
 *        - 'dim_y' refers to the number of lines in the chroma plane (should be equal to plane0.dim_y / 2)
 *        - 'stride_y' refers to the stride of the chroma plane, and should be at least ('dim_x' * 1 * sizeof(dataType)) bytes
 *      - plane2
 *        - 'dim_x' refers to the number of chroma pixel units per line (should be equal to plane0.dim_x / 2)
 *        - 'dim_y' refers to the number of lines in the chroma plane (should be equal to plane0.dim_y / 2)
 *        - 'stride_y' refers to the stride of the chroma plane, and should be at least ('dim_x' * 1 * sizeof(dataType)) bytes
 *
 */
/**
 * @page convert_bit  Convert Bit depth
 *
 *  @section intro16 OpenVX Function Description
 *  - Converts image bit depth.
 *
 *  @section ref16 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/de/d73/group__group__vision__function__convertdepth.html
 *
 *  @section apis16 VXLIB APIs
 *  - @ref VXLIB_convertDepth_i8u_o16s : Input image is U8 format and output image is S16 format
 *  - @ref VXLIB_convertDepth_i16s_o8u : Input image is S16 format and output image is U8 format
 */
/**
 * @page convolution  Custom Convolution
 *
 *  @section intro17 OpenVX Function Description
 *  - Convolves the input with the client supplied convolution matrix.
 *
 *  @section ref17 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d3/d3b/group__group__vision__function__custom__convolution.html
 *
 *  @section apis17 VXLIB API
 *  - @ref VXLIB_convolve_i8u_c16s_o8u : Input and output images are U8 format
 *    - Calls internally: @ref VXLIB_convolve_3x3_i8u_c16s_o8u
 *    - Calls internally: @ref VXLIB_convolve_5x5_i8u_c16s_o8u
 *    - Calls internally: @ref VXLIB_convolve_7x7_i8u_c16s_o8u
 *  - @ref VXLIB_convolve_i8u_c16s_o16s : Input and output images are U8 format
 *    - Calls internally: @ref VXLIB_convolve_3x3_i8u_c16s_o16s
 *    - Calls internally: @ref VXLIB_convolve_5x5_i8u_c16s_o16s
 *    - Calls internally: @ref VXLIB_convolve_7x7_i8u_c16s_o16s
 */
/**
 * @page dilate_img  Dilate Image
 *
 *  @section intro18 OpenVX Function Description
 *  - Implements Dilation, which grows the white space in an image.
 *
 *  @section ref18 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/dc/d73/group__group__vision__function__dilate__image.html
 *
 *  @section apis18 VXLIB API
 *  - @ref VXLIB_dilate_3x3_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page equalize_hist  Equalize Histogram
 *
 *  @section intro19 OpenVX Function Description
 *  - Equalizes the histogram of a grayscale image.
 *
 *  @section ref19 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d1/d70/group__group__vision__function__equalize__hist.html
 *
 *  @section apis19 VXLIB API
 *  - @ref VXLIB_equalizeHist_i8u_o8u : Input and output images are U8 format
 *    - Calls internally: @ref VXLIB_histogramSimple_i8u_o32u
 *    - Calls internally: @ref VXLIB_histogramCdfLut_i32u_o8u
 *    - Calls internally: @ref VXLIB_tableLookup_i8u_o8u
 */
/**
 * @page erode_img  Erode Image
 *
 *  @section intro20 OpenVX Function Description
 *  - Implements Erosion, which shrinks the white space in an image.
 *
 *  @section ref20 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/dc/dff/group__group__vision__function__erode__image.html
 *
 *  @section apis20 VXLIB API
 *  - @ref VXLIB_erode_3x3_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page fast_corners  Fast Corners
 *
 *  @section intro21 OpenVX Function Description
 *  - Computes the corners in an image using a method based upon FAST9 algorithm.
 *
 *  @section ref21 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/dd/d22/group__group__vision__function__fast.html
 *
 *  @section apis21 VXLIB API
 *  - @ref VXLIB_fastCorners_i8u : Input image is U8 format
 *    - Calls internally: @ref VXLIB_fastCornersDetect_i8u
 *    - Calls internally: @ref VXLIB_fastCornersScore_i8u
 *    - Calls internally: @ref VXLIB_fastCornersNMS_i8u
 */
/**
 * @page gauss_filter  Gaussian Filter
 *
 *  @section intro22 OpenVX Function Description
 *  - Computes a Gaussian filter over a window of the input image.
 *
 *  @section ref22 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d6/d58/group__group__vision__function__gaussian__image.html
 *
 *  @section apis22 VXLIB API
 *  - @ref VXLIB_gaussian_3x3_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_gaussian_5x5_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page harris_corners  Harris Corners
 *
 *  @section intro23 OpenVX Function Description
 *  - Computes the Harris Corners of an image.
 *
 *  @section ref23 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d7/d5f/group__group__vision__function__harris.html
 *
 *  @section apis23 VXLIB API
 *  - @ref VXLIB_sobel_3x3_i8u_o16s_o16s : Input image is U8 format, output gradients are S16 format
 *  - @ref VXLIB_sobel_5x5_i8u_o16s_o16s : Input image is U8 format, output gradients are S16 format
 *  - @ref VXLIB_sobel_7x7_i8u_o32s_o32s : Input image is U8 format, output gradients are S32 format
 *  - @ref VXLIB_harrisCornersScore_i16s_i16s_o32f : Input images are S16 format
 *  - @ref VXLIB_harrisCornersScore_i32s_i32s_o32f : Input images are S32 format
 *  - @ref VXLIB_harrisCornersDetect_i32f : Input images are F32 format, output is a list of features
 *  - @ref VXLIB_harrisCornersNMS_i32f : Input and output is a list of features
 */
/**
 * @page histogram  Histogram
 *
 *  @section intro24 OpenVX Function Description
 *  - Generates a distribution from an image.
 *
 *  @section ref24 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d6/dcb/group__group__vision__function__histogram.html
 *
 *  @section apis24 VXLIB API
 *  - @ref VXLIB_histogram_i8u_o32u : Input image is U8 format
 *    - Calls internally: @ref VXLIB_histogramSimple_i8u_o32u
 */
/**
 * @page gaussian_img_pyr  Gaussian Image Pyramid
 *
 *  @section intro25 OpenVX Function Description
 *  - Computes a Gaussian Image Pyramid from an input image.
 *
 *  @section ref25 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d0/d15/group__group__vision__function__gaussian__pyramid.html
 *
 *  @section apis25 VXLIB API
 *  - @ref VXLIB_gaussian_5x5_i8u_o8u : Input image is U8 format and output image is U8 format
 *  - @ref VXLIB_scaleImageNearest_i8u_o8u : Input image is U8 format and output image is U8 format
 *  - @ref VXLIB_halfScaleGaussian_5x5_i8u_o8u : Input image is U8 format and output image is U8 format
 */
/**
 * @page integral_img  Integral Image
 *
 *  @section intro26 OpenVX Function Description
 *  - Computes the integral image of the input.
 *
 *  @section ref26 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d0/d7b/group__group__vision__function__integral__image.html
 *
 *  @section apis26 VXLIB APIs
 *  - @ref VXLIB_integralImage_i8u_o32u : Input image is U8 format and output image is U32 format
 */
/**
 * @page magnitude  Magnitude
 *
 *  @section intro27 OpenVX Function Description
 *  - Implements the Gradient Magnitude Computation Kernel.
 *
 *  @section ref27 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/dd/df2/group__group__vision__function__magnitude.html
 *
 *  @section apis27 VXLIB APIs
 *  - @ref VXLIB_magnitude_i16s_i16s_o16s : Input and output images are S16 format
 */
/**
 * @page mean_std_dev  Mean and Standard Deviation
 *
 *  @section intro28 OpenVX Function Description
 *  - Computes the mean pixel value and the standard deviation of the pixels in the input image (which has a dimension width and height).
 *
 *  @section ref28 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d8/d85/group__group__vision__function__meanstddev.html
 *
 *  @section apis28 VXLIB APIs
 *  - @ref VXLIB_meanStdDev_i8u_o32f : Input image is U8 format and output is float format
 */
/**
 * @page median_filter  Median Filter
 *
 *  @section intro29 OpenVX Function Description
 *  - Computes a median pixel value over a window of the input image.
 *
 *  @section ref29 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d3/d77/group__group__vision__function__median__image.html
 *
 *  @section apis29 VXLIB APIs
 *  - @ref VXLIB_median_3x3_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page min_max_loc  Min, Max Location
 *
 *  @section intro30 OpenVX Function Description
 *  - Finds the minimum and maximum values in an image and a location for each.
 *
 *  @section ref30 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d8/d05/group__group__vision__function__minmaxloc.html
 *
 *  @section apis30 VXLIB APIs
 *  - @ref VXLIB_minMaxLoc_i8u : Input image is U8 format
 *  - @ref VXLIB_minMaxLoc_i16s : Input image is S16 format
 */
/**
 * @page optical_flow_lk  Optical Flow Pyramid (LK)
 *
 *  @section intro31 OpenVX Function Description
 *  - Computes the optical flow using the Lucas-Kanade method between two pyramid images.
 *
 *  @section ref31 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d0/d0c/group__group__vision__function__opticalflowpyrlk.html
 *
 *  @section apis31 VXLIB API
 *  - @ref VXLIB_scharr_3x3_i8u_o16s_o16s : Input image is U8 format
 *  - @ref VXLIB_trackFeaturesLK_i8u : Input image is U8 format
 */
/**
 * @page phase  Phase
 *
 *  @section intro32 OpenVX Function Description
 *  - Implements the Gradient Phase Computation Kernel.
 *
 *  @section ref32 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/db/d4e/group__group__vision__function__phase.html
 *
 *  @section apis32 VXLIB API
 *  - @ref VXLIB_phase_i16s_i16s_o8u : Input image is S16 format and output image is U8 format
 */
/**
 * @page multiplication  Pixel-wise Multiplication
 *
 *  @section intro33 OpenVX Function Description
 *  - Performs element-wise multiplication between two images and a scalar value.
 *
 *  @section ref33 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d7/dae/group__group__vision__function__mult.html
 *
 *  @section apis33 VXLIB APIs
 *  - @ref VXLIB_multiply_i8u_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_multiply_i8u_i8u_o16s : Input images are U8 format and output image is S16 format
 *  - @ref VXLIB_multiply_i8u_i16s_o16s : One input image is U8 format, one input image is S16 format and output image is S16 format
 *  - @ref VXLIB_multiply_i16s_i16s_o16s : Input and output images are S16 format
 */
/**
 * @page remap  Remap
 *
 *  @section intro34 OpenVX Function Description
 *  - Maps output pixels in an image from input pixels in an image.
 *
 *  @section ref34 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/df/dca/group__group__vision__function__remap.html
 *
 *  @section apis34 VXLIB API
 */
/**
 * @page scale  Scale Image
 *
 *  @section intro35 OpenVX Function Description
 *  - Implements the Image Resizing Kernel.
 *
 *  @section ref35 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d1/d26/group__group__vision__function__scale__image.html
 *
 *  @section apis35 VXLIB API
 *  - @ref VXLIB_scaleImageNearest_i8u_o8u : Input image is U8 format and output image is U8 format
 *  - @ref VXLIB_scaleImageBilinear_i8u_o8u : Input image is U8 format and output image is U8 format
 *  - @ref VXLIB_scaleImageBilinear_bc_i8u_o8u : Input image is U8 format and output image is U8 format
 *  - @ref VXLIB_scaleImageBilinear_br_i8u_o8u : Input image is U8 format and output image is U8 format
 *  - @ref VXLIB_halfScaleGaussian_5x5_i8u_o8u : Input image is U8 format and output image is U8 format
 *  - @ref VXLIB_gaussian_3x3_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_gaussian_5x5_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page sobel  Sobel 3x3
 *
 *  @section intro36 OpenVX Function Description
 *  - Implements the Sobel Image Filter Kernel.
 *
 *  @section ref36 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/da/d4b/group__group__vision__function__sobel3x3.html
 *
 *  @section apis36 VXLIB API
 *  - @ref VXLIB_sobel_3x3_i8u_o16s_o16s : Input image is U8 format and output images are S16 format
 *  - @ref VXLIB_sobelX_3x3_i8u_o16s : Input image is U8 format and output image is S16 format
 *  - @ref VXLIB_sobelY_3x3_i8u_o16s : Input image is U8 format and output image is S16 format
 */
/**
 * @page lookup  TableLookup
 *
 *  @section intro37 OpenVX Function Description
 *  - Implements the Table Lookup Image Kernel.
 *
 *  @section ref37 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d5/d4e/group__group__vision__function__lut.html
 *
 *  @section apis37 VXLIB API
 *  - @ref VXLIB_tableLookup_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_tableLookup_i16s_o16s : Input and output images are S15 format
 */
/**
 * @page thresholding  Thresholding
 *
 *  @section intro38 OpenVX Function Description
 *  - Thresholds an input image and produces an output Boolean image.
 *
 *  @section ref38 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d3/d1e/group__group__vision__function__threshold.html
 *
 *  @section apis38 VXLIB APIs
 *  - @ref VXLIB_thresholdBinary_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_thresholdRange_i8u_o8u  : Input and output images are U8 format
 */
/**
 * @page warp_affine  Warp Affine
 *
 *  @section intro39 OpenVX Function Description
 *  - Performs an affine transform on an image.
 *
 *  @section ref39 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d5/d5f/group__group__vision__function__warp__affine.html
 *
 *  @section apis39 VXLIB API
 *  - @ref VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u : Input and output images are U8 format
 *  - @ref VXLIB_warpAffineBilinear_i8u_c32f_o8u : Input and output images are U8 format
 *  - @ref VXLIB_warpAffineNearest_bc_i8u_c32f_o8u : Input and output images are U8 format
 *  - @ref VXLIB_warpAffineNearest_i8u_c32f_o8u : Input and output images are U8 format
 */
/**
 * @page warp_perspective  Warp Perspective
 *
 *  @section intro40 OpenVX Function Description
 *  - Performs a perspective transform on an image.
 *
 *  @section ref40 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/da/d6a/group__group__vision__function__warp__perspective.html
 *
 *  @section apis40 VXLIB API
 *  - @ref VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u : Input and output images are U8 format
 *  - @ref VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u : Input and output images are U8 format
 *  - @ref VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u : Input and output images are U8 format
 *  - @ref VXLIB_warpPerspectiveNearest_i8u_c32f_o8u : Input and output images are U8 format
 */
/**
 * @page nonlinear_filter  Non Linear Filter
 *
 *  @section intro41 OpenVX Function Description
 *  - Computes a non-linear filter over a window of the input image.
 *
 *  @section ref41 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/d5/dc5/group__group__vision__function__nonlinear__filter.html
 *
 *  @section apis41 VXLIB API
 *  - @ref VXLIB_dilate_MxN_i8u_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_erode_MxN_i8u_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_median_MxN_i8u_i8u_o8u : Input and output images are U8 format
 */
/**
 * @page laplacian_img_pyr  Laplacian Image Pyramid
 *
 *  @section intro42 OpenVX Function Description
 *  - Computes a Laplacian Image Pyramid from an input image.
 *
 *  @section ref42 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/dc/d60/group__group__vision__function__laplacian__pyramid.html
 *
 *  @section apis42 VXLIB API
 *  - @ref VXLIB_gaussian_5x5_br_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_subtract_i8u_i8u_o16s : Input images in U8 format, and output images are S16 format
 */
/**
 * @page laplacian_reconstruct  Reconstruction from a Laplacian Image Pyramid
 *
 *  @section intro43 OpenVX Function Description
 *  - Reconstructs the original image from a Laplacian Image Pyramid.
 *
 *  @section ref43 OpenVX Function Reference Page
 *  - https://www.khronos.org/registry/vx/specs/1.1/html/dd/daa/group__group__vision__function__laplacian__reconstruct.html
 *
 *  @section apis43 VXLIB API
 *  - @ref VXLIB_channelCopy_1to1_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_gaussian_5x5_br_i8u_o8u : Input and output images are U8 format
 *  - @ref VXLIB_add_i8u_i16s_o16s : Input images in U8 and S16 format, and output images are S16 format
*/
