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
**|         Copyright (c) 2015 Texas Instruments Incorporated                |**
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

#ifndef VLIB_MATCHTEMPLATE_H_
#define VLIB_MATCHTEMPLATE_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_matchTemplate */
/** @ingroup  VLIB_matchTemplate */
/* @{ */
/**
 * @par Description:
 *   This routine accepts an 8-bit grayscale input image of size orgImgWidth by
 *   orgImgHeight with a stride of orgImgPitch along with template image of size
 *   tempImgWidth by tempImgHeight with a stride tempImgPitch and calculates
 *   normalized cross correlation of template image with original image at all
 *   possible locations.
 *
 * @par
 *   @param [in]  img[]            original input image data pointer                          (UQ8.0 )
 *   @param [in]  imgWidth         original input image width                                 (SQ31.0)
 *   @param [in]  imgHeight        original input image height                                (SQ31.0)
 *   @param [in]  imgPitch         original input image pitch                                 (SQ31.0)
 *   @param [in]  tempImg          template image pointer                                     (SQ13.2)
 *   @param [in]  tempImgWidth     template image width                                       (SQ31.0)
 *   @param [in]  tempImgHeight    template image height                                      (SQ31.0)
 *   @param [in]  tempImgPitch     template image pitch                                       (SQ31.0)
 *   @param [in]  scaledTempImgVar template image variance                                    (FLOAT)
 *   @param [in]  xDirJump         jump in x direction while template search in \c img        (UQ8.0 )
 *   @param [in]  yDirJump         jump in y direction while template search in \c img        (UQ8.0 )
 *   @param [in]  method           method use in template matching, must be 0 for now         (SQ31.0)
 *   @param [in]  outScorePitch    pitch of \c outScore buffer (elements, not bytes)          (SQ31.0)
 *   @param [out] outScore         data pointer for variance value for each block             (FLOAT)
 *   @param [in]  scratch[]        data pointer for scratch buffer                            (UQ8.0 )
 *
 * @par Assumptions:
 *    - Input image data is of 8 bits.
 *    - All buffers should not overlap (should be non-aliased)
 *    - Scaled template image variance, 1.0f/sqrt(Sum((tempImg[i]-tempImgMean)^2)))
 *    - \c outScore buffer size should be at least \c outScorePitch * outScoreHeight * 4 bytes, where:
 *      - outScoreWidth is(\c imgWidth - (\c tempImgWidth - 1))
 *      - outScoreHeight is (\c imgHeight - (\c tempImgHeight - 1))
 *      - \c outScorePitch parameter should be greater than or equal to outScoreWidth
 *    - \c scratch buffer size should be at least  20*(outScoreWidth * outScoreHeight) +  40 bytes. Where outScoreWidth and outScoreHeight are given above.
 *    - Supported range of \c tempImgWidth is [4 .. 128]
 *    - Supported range of \c tempImgHeight is [4 .. 128]
 *    - When \c xDirJump is 'n' then every 'n' th output is valid in \c outScore, similarly for \c yDirJump
 *
 * @par Implementation Notes:
 *    - Specific optimimzation is done when \c tempImgWidth is equal to \c tempImgPitch
 *    - Specific optimimzation is done \c tempImgWidth * \c tempImgHeight is less than 2048
 *    - Specific optimimzation is done when \c tempImgWidth is 24 and 32
 *    - Specific optimimzation is done if \c img base address is word aligned and \c tempImg is double word aligned.
 *    - Specific optimimzation is done if \c tempImgPitch and \c orgImgPitch is multiple of 4
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
int32_t    VLIB_matchTemplate(uint8_t img[restrict],
                              int32_t imgWidth,
                              int32_t imgHeight,
                              int32_t imgPitch,
                              int16_t tempImg[restrict],
                              int32_t tempImgWidth,
                              int32_t tempImgHeight,
                              int32_t tempImgPitch,
                              VLIB_F32 scaledTempImgVar,
                              uint8_t xDirJump,
                              uint8_t yDirJump,
                              int32_t method,
                              int32_t outScorePitch,
                              VLIB_F32 outScore[restrict],
                              uint8_t scratch[restrict]);

#endif
/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_MATCHTEMPLATEsSparse.h                    */
/* ======================================================================== */

