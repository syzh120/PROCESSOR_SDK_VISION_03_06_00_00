/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/*                                                                          */
/*  @file : vcop_soft_isp_cn.h                                              */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for a software Image Signal Processor (ISP).                   */
/*                                                                          */
/*  vcop_decompand_piecewise_linear_cn                                      */
/*      This is the c-reference for the vcop_decompand_piecewise_linear     */
/*      kernel. This routine accepts a 16-bit companded RAW input image and */
/*      outputs a linearized RAW image after decompanding to a 16-bit       */
/*      linear data. The operation assumes piecewise decompanding with      */
/*      two knee points.                                                    */
/*                                                                          */
/*  USAGE:                                                                  */
/*  This routine is C-callable and can be called as:                        */
/*                                                                          */
/*  vcop_decompand_piecewise_linear_cn(uint16_t *pInput_rc,                 */
/*                                uint16_t *pInput_cc,                      */
/*                                uint16_t *pOutput_rc,                     */
/*                                uint16_t *pOutput_cc,                     */
/*                                uint16_t  width,                          */
/*                                uint16_t  height,                         */
/*                                uint16_t  inPitch,                        */
/*                                uint16_t  outPitch,                       */
/*                                uint16_t  p1,                             */
/*                                uint16_t  p2,                             */
/*                                uint16_t  pk,                             */
/*                                uint8_t   r1,                             */
/*                                uint16_t  r1r2,                           */
/*                                uint8_t   shift)                          */
/*                                                                          */
/*  pInput_rc     :  [in] Pointer to even rows of the RAW input image,      */
/*                   16 bit per pixel.                                      */
/*  pInput_cc     :  [in] Pointer to odd rows of the RAW input image,       */
/*                   16 bit per pixel.                                      */
/*  pOutput_rc    :  [out] Pointer to even rows of output RAW image after   */
/*                   decompanding.                                          */
/*  pOutput_cc    :  [out] Pointer to odd rows of output RAW image after    */
/*                   decompanding.                                          */
/*  width         :  Image width                                            */
/*  height        :  Image height                                           */
/*  inPitch       :  Input Image pitch/stride                               */
/*  outPitch      :  Output Image pitch/stride                              */
/*  p1            :  Output pixel value at first Knee point. This is same   */
/*                   as knee point value (input value).                     */
/*  p2            :  Output pixel value at second knee point.               */
/*  pk            :  Second knee point value (input value).                 */
/*  r1            :  Slope for second segment.                              */
/*  r1r2          :  Slope for third segment.                               */
/*  shift         :  Number of bits to right shift after decompanding to    */
/*                   fit the output pixel within 16-bits.                   */
/*                                                                          */
/*  Returns       :  Status = 0 if it runs sucessfully                      */
/*                                                                          */
/*                                                                          */
/*  vcop_black_clamp_c_balance_cn                                           */
/*      This is the c-reference for the vcop_black_clamp_c_balance kernel.  */
/*      This routine accepts a 16-bit RAW input image and outputs a RAW     */
/*      image after dark current subtraction/black clamp and C imbalance    */
/*      correction (for an RCCC image).                                     */
/*                                                                          */
/*  USAGE:                                                                  */
/*  This routine is C-callable and can be called as:                        */
/*                                                                          */
/*  vcop_black_clamp_c_balance_cn(uint16_t *pInput_rc,                      */
/*                                uint16_t *pInput_cc,                      */
/*                                uint16_t *pOutput_rc,                     */
/*                                uint16_t *pOutput_cc,                     */
/*                                uint16_t  width,                          */
/*                                uint16_t  height,                         */
/*                                uint16_t  inPitch,                        */
/*                                uint16_t  outPitch,                       */
/*                                uint16_t *blackClamp,                     */
/*                                uint16_t *cBalanceGain,                   */
/*                                uint8_t   shift)                          */
/*                                                                          */
/*  pInput_rc     :  [in] Pointer to even rows of the RAW input image,      */
/*                   16 bit per pixel. This image will be corrected for     */
/*                   sensor dark current and gain imbalance.                */
/*  pInput_cc     :  [in] Pointer to odd rows of the RAW input image,       */
/*                   16 bit per pixel. This image will be corrected for     */
/*                   sensor dark current and gain imbalance.                */
/*  pOutput_rc    :  [out] Pointer to even rows of output RAW image after   */
/*                   black clamp and imbalance correction.                  */
/*  pOutput_cc    :  [out] Pointer to odd rows of output RAW image after    */
/*                   black clamp and imbalance correction.                  */
/*  width         :  Image width                                            */
/*  height        :  Image height                                           */
/*  inPitch       :  Input Image pitch/stride                               */
/*  outPitch      :  Output Image pitch/stride                              */
/*  blackClamp    :  The dark current values to be subtracted from each     */
/*                   paxel. This is an array of 4 values. The four values   */
/*                   corresponds to the 4 locations in a paxel.             */
/*  cBalanceGain  :  Gain to be applied to each of the 4 pixels in a paxel. */
/*                   An array of 4 16-bit values are expected. The value to */
/*                   be programmed is equal to the actual gain multiplied   */
/*                   by 2^(shift).                                          */
/*  shift         :  The shift (right shift) required to scale down the     */
/*                   cBalanceGain values.                                   */
/*                                                                          */
/*  Returns       :  Status = 0 if it runs sucessfully                      */
/*                                                                          */
/*                                                                          */
/*  vcop_rccc_to_cccc_cn                                                    */
/*      This is the c-reference for the vcop_rccc_to_cccc kernel.           */
/*      This routine accepts a 16-bit RAW input image in RCCC format and    */
/*      performs CFA interpolation to fill out the missing C samples at     */
/*      R locations.                                                        */
/*                                                                          */
/*  USAGE:                                                                  */
/*  This routine is C-callable and can be called as:                        */
/*                                                                          */
/*  vcop_rccc_to_cccc_cn(uint16_t *pInput_rc,                               */
/*                       uint16_t *pInput_cc,                               */
/*                       uint16_t  width,                                   */
/*                       uint16_t  height,                                  */
/*                       uint16_t  inPitch,                                 */
/*                       uint8_t   rPosition);                              */
/*                                                                          */
/*  pInput_rc     :  [in] Pointer to even rows of the RAW input image,      */
/*                   16 bit per pixel.                                      */
/*  pInput_cc     :  [in] Pointer to odd rows of the RAW input image,       */
/*                   16 bit per pixel.                                      */
/*  width         :  Image width                                            */
/*  height        :  Image height                                           */
/*  inPitch       :  Input Image pitch/stride                               */
/*  rPosition     :  Location of the R pixel in the RCCC paxel. Possible    */
/*                   values are 1, 2, 3 and 4. 1 stands for RCCC, 2 for     */
/*                   CRCC, 3 for CCRC and 4 for CCCR.                       */
/*                                                                          */
/*  Returns       :  Status = 0 if it runs sucessfully                      */
/*                                                                          */
/*                                                                          */
/*  vcop_gbce_simple_cn                                                     */
/*      This is the c-reference for the vcop_gbce_simple kernel. This       */
/*      routine accepts a 16-bit RAW input image in RCCC format and         */
/*      performs global brightness and contrast enhancement (GBCE).  The    */
/*      expects a 12-bit GBCE tone curve to be provided at pGbceToneCurve.  */
/*      The input pixel value is shifted first to ensure that the bit       */
/*      depth is less than or equal to 12 bit before looking-up in the      */
/*      tone curve.                                                         */
/*                                                                          */
/*  USAGE:                                                                  */
/*  This routine is C-callable and can be called as:                        */
/*                                                                          */
/*  vcop_gbce_simple_cn(uint16_t *pInput_rc,                                */
/*                      uint16_t *pInput_cc,                                */
/*                      uint8_t  *pOutput_rc,                               */
/*                      uint8_t  *pOutput_cc,                               */
/*                      uint16_t  width,                                    */
/*                      uint16_t  height,                                   */
/*                      uint16_t  inPitch,                                  */
/*                      uint8_t   shift,                                    */
/*                      uint8_t  *pGbceToneCurve);                          */
/*                                                                          */
/*  pInput_rc      : [in] Pointer to even rows of the RAW input image,      */
/*                   16 bit per pixel.                                      */
/*  pInput_cc      : [in] Pointer to odd rows of the RAW input image,       */
/*                   16 bit per pixel.                                      */
/*  pOutput_rc     : 8-bit output for even rows.                            */
/*  pOutput_cc     : 8-bit output for odd rows.                             */
/*  width          : Image width.                                           */
/*  height         : Image height.                                          */
/*  inPitch        : Input Image pitch/stride.                              */
/*  shift          : Number of bits to right shift to fit within 12 bits.   */
/*                   For input image with bitdepth less than 12 bits the    */
/*                   shift value would be 0.                                */
/*  pGbceToneCurve : Tone Curve to perform Global Brightness and Contrast   */
/*                   enhancement. The tone curve is expected to be provided */
/*                   in 4-way LUT format.                                   */
/*                                                                          */
/*  Returns        :  Status = 0 if it runs sucessfully.                    */
/*                                                                          */
/*                                                                          */
/*  vcop_gbce_interp_cn                                                     */
/*      This is the c-reference for the vcop_gbce_interp kernel which       */
/*      performs global tone mapping for input images with bit depth        */
/*      between 12 and 16. This routine accepts a 16-bit RAW input image    */
/*      in RCCC format and performs global brightness and contrast          */
/*      enhancement (GBCE). A 12-bit LUT is provided for performing GBCE.   */
/*      In this method the input pixel value is used to find out the two    */
/*      nearest entries in the LUT provided and an interpolated value is    */
/*      reported as the output.                                             */
/*                                                                          */
/*  USAGE:                                                                  */
/*  This routine is C-callable and can be called as:                        */
/*                                                                          */
/*  vcop_gbce_interp_cn(uint16_t *pInput_rc,                                */
/*                      uint16_t *pInput_cc,                                */
/*                      uint8_t  *pOutput_rc,                               */
/*                      uint8_t  *pOutput_cc,                               */
/*                      uint16_t  width,                                    */
/*                      uint16_t  height,                                   */
/*                      uint16_t  inPitch,                                  */
/*                      uint8_t   sensorBitDepth,                           */
/*                      uint8_t  *pGbceToneCurve);                          */
/*                                                                          */
/*  pInput_rc      :  [in] Pointer to even rows of the RAW input image,     */
/*                    16 bit per pixel and bit depth more than 12 bits.     */
/*  pInput_cc      :  [in] Pointer to odd rows of the RAW input image,      */
/*                    16 bit per pixel and bit depth more than 12 bits.     */
/*  pOutput_rc     :  8-bit output for even rows.                           */
/*  pOutput_cc     :  8-bit output for odd rows.                            */
/*  width          :  Image width                                           */
/*  height         :  Image height                                          */
/*  inPitch        :  Input Image pitch/stride                              */
/*  sensorBitDepth :  Number of bits required to represent the pixel value. */
/*                    This function should be called only for input with    */
/*                    sensor bit depths between 12 and 16.                  */
/*  pGbceToneCurve :  Tone Curve to perform Global Brightness and Contrast  */
/*                    enhancement. The tone curve is expected to be         */
/*                    provided in 4-way LUT format.                         */
/*                                                                          */
/*  Returns       :  Status = 0 if it runs sucessfully                      */
/*                                                                          */
/*                                                                          */
/*  vcop_stats_collector_dense_cn                                           */
/*      This is the c-reference for the vcop_stats_collector_dense kernel   */
/*      which collects certain statistics for assisting Auto Exposure       */
/*      algorithm in deciding the exposure settings for the sensor. In      */
/*      this function the statistics is collected from every pixel within   */
/*      a window.                                                           */
/*                                                                          */
/*  USAGE:                                                                  */
/*  This routine is C-callable and can be called as:                        */
/*                                                                          */
/*  vcop_stats_collector_dense_cn(uint16_t *pInput_rc,                      */
/*                                uint16_t *pInput_cc,                      */
/*                                uint8_t  *pStatsBuf,                      */
/*                                uint16_t  width,                          */
/*                                uint16_t  height,                         */
/*                                uint16_t  inPitch,                        */
/*                                uint16_t  statBlkWidth,                   */
/*                                uint16_t  statBlkHeight,                  */
/*                                uint16_t  saturationLimit)                */
/*                                                                          */
/*  pInput_rc       :  [in] Pointer to even rows of the RAW input image.    */
/*  pInput_cc       :  [in] Pointer to odd rows of the RAW input image.     */
/*  pPixelSum       :  Accumulated sum of all pixels within a window.       */
/*  pUnsatPixelSum  :  Accumulated sum of non-saturated pixels within a     */
/*                     window.                                              */
/*  pUnsatPixelCnt  :  Count of non-saturated pixels per window.            */
/*  width           :  Image width                                          */
/*  height          :  Image height                                         */
/*  inPitch         :  Input Image pitch/stride                             */
/*  statBlkWidth    :  Statistics window width (in pixels).                 */
/*  statBlkHeight   :  Statistics window height (in lines).                 */
/*  saturationLimit :  Saturation limit to decide whether a paxel is        */
/*                     saturated or not.                                    */
/*                                                                          */
/*  Returns       :  Status = 0 if it runs sucessfully                      */
/*                                                                          */
/*                                                                          */
/*  @version 0.1 (Mar 2014) : Base version.                                 */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_SOFT_ISP_CN
#define _VCOP_SOFT_ISP_CN

int32_t vcop_decompand_piecewise_linear_cn(uint16_t *pInput_rc,
                                      uint16_t *pInput_cc,
                                      uint16_t *pOutput_rc,
                                      uint16_t *pOutput_cc,
                                      uint16_t  width,
                                      uint16_t  height,
                                      uint16_t  inPitch,
                                      uint16_t  outPitch,
                                      uint16_t  p1,
                                      uint32_t  p2,
                                      uint16_t  pk,
                                      uint8_t   r1,
                                      uint16_t  r1r2,
                                      uint8_t   shift);

int32_t vcop_black_clamp_c_balance_cn(uint16_t *pInput_rc,
                                      uint16_t *pInput_cc,
                                      uint16_t *pOutput_rc,
                                      uint16_t *pOutput_cc,
                                      uint16_t  width,
                                      uint16_t  height,
                                      uint16_t  inPitch,
                                      uint16_t  outPitch,
                                      uint16_t *blackClamp,
                                      uint16_t *cBalanceGain,
                                      uint8_t   shift);

int32_t vcop_soft_isp_extract_r_cn(uint16_t *pInput_rc,
                                   uint8_t  *pOut_r,
                                   uint16_t  width,
                                   uint16_t  height,
                                   uint16_t  inPitch,
                                   uint8_t   shift);

int32_t vcop_rccc_to_cccc_cn(uint16_t *pInput_rc,
                             uint16_t *pInput_cc,
                             uint16_t  width,
                             uint16_t  height,
                             uint16_t  inPitch,
                             uint8_t   rPosition);

int32_t vcop_gbce_simple_cn(uint16_t *pInput_rc,
                            uint16_t *pInput_cc,
                            uint8_t  *pOutput_rc,
                            uint8_t  *pOutput_cc,
                            uint16_t  width,
                            uint16_t  height,
                            uint16_t  inPitch,
                            uint8_t   shift,
                            uint8_t  *pGbceToneCurve);

int32_t vcop_gbce_interp_cn(uint16_t *pInput_rc,
                            uint16_t *pInput_cc,
                            uint8_t  *pOutput_rc,
                            uint8_t  *pOutput_cc,
                            uint16_t  width,
                            uint16_t  height,
                            uint16_t  inPitch,
                            uint8_t   shift,
                            uint8_t   mask,
                            uint8_t  *pGbceToneCurve);

int32_t vcop_stats_collector_dense_cn(uint16_t *pInput_rc,
                                      uint16_t *pInput_cc,
                                      uint8_t  *pStatsBuf,
                                      uint16_t  width,
                                      uint16_t  height,
                                      uint16_t  inPitch,
                                      uint8_t   rPosition,
                                      uint16_t  statBlkWidth,
                                      uint16_t  statBlkHeight,
                                      uint16_t  saturationLimit);

#endif /* _VCOP_SOFT_ISP_CN */
