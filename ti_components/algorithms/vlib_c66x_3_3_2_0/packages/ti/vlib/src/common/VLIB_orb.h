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
**|        Copyright (c) 2007 - 2013 Texas Instruments Incorporated          |**
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

#ifndef VLIB_ORB_H
#define VLIB_ORB_H 1

#include "VLIB_types.h"

#define CORB_MAX_FEATURES 10000

#define CORB_MAX_IMAGE_WIDTH 10000
#define CORB_MIN_IMAGE_WIDTH 120
#define CORB_MIN_IMAGE_HEIGHT 120
#define CORB_IMAGE_WIDTH_MULTIPLE 8
#define CORB_IMAGE_HEIGHT_MULTIPLE 8

#define CORB_NUM_OFAST_OFFSETS (8 * CORB_HALF_PATCH_SIZE)

#define CORB_PATCH_SIZE 31
#define CORB_HALF_PATCH_SIZE (CORB_PATCH_SIZE / 2)

#define CORB_NUM_PATTERNS 256

#define CORB_NUM_ORIENTATIONS 30

#define CORB_PATCH_KERNEL_WIDTH 5
#define CORB_PATCH_KERNEL_HALF_WIDTH (CORB_PATCH_KERNEL_WIDTH / 2)

#define Compare(X, Y) ((X) >= (Y))

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

/* Round up the number to the nearest 4 (useful for pointers) */
#ifndef ALIGN4
#define ALIGN4(x) (((x) + 3) & (~3u))
#endif

#ifndef DWORD_ALIGNED
#define DWORD_ALIGNED(x) (_nassert(((int32_t)(x) & 0x7) == 0))
#endif

#ifdef _MSC_VER
#ifndef restrict
/* #define restrict __restrict */
#define restrict /* Blank, because correctness is more important than speed on the PC */
#endif

#ifndef snprintf
#define snprintf sprintf_s
#endif

#ifndef inline
#define inline __inline
#endif

#endif

#if !defined(CORB_Bool) && !defined(BOOL_FALSE) && !defined(BOOL_TRUE)
typedef enum {
    BOOL_FALSE = 0,
    BOOL_TRUE = 1
}CORB_Bool;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if 0 /* Not needed by VLIB library, required at higher level abstraction */
typedef enum {
    FAST_9,
    FAST_9_ACCELERATED,
    FAST_12,
    FAST_12_ACCELERATED
}FastKeypointVersion;
#endif

typedef enum {
    CORB_OK  = 0,
    CORB_FAIL = -1
}CORBResult;

/*!
 * \brief Structure defining various parameters required by the ORB functions.
 */
typedef struct {
    int32_t width;                       /*!< Width of the input image. Must be a multiple of 8, aligned in memory by 8, and greater than 120. */
    int32_t height;                      /*!< Height of the input image. Must be a multiple of 8, aligned in memory by 8, and greater than 120. */
    int32_t marginPixels;                /*!< (35 is safe). Due to the size of the rBRIEF features, border effects on Harris, etc, we should not
                                           extract features right by the image border. */
    uint8_t fastDifferenceThreshold;     /*!< The threshold for fast corner detection. 20 is a reasonable value for 0->255 data. */
    /*        FastKeypointVersion fastVersion; Which version of fast to use. FAST_9 is the value for the original ORB. */
    /*        CORB_Bool useFastNonMaxSupression; Should the detected FAST features be non-maxima supressed? For the original ORB, this is BOOL_TRUE. */
    /*        int16_t harrisK;  (SQ0.15) The k-parameter for Harris. A reasonable value is 1311 (which is equal to 0.04f * powf(2.0f,15.0f)) */
    int32_t n_features_desired;          /*!< Number of features to extract rBRIEF descriptors. A few hundred is a reasonable number. */
}CORBParameters;

/*!
 * \brief Structure containing automatically computed pattern information needed by \ref VLIB_ORB_computeRBrief
 */
typedef struct {
    int32_t octave;     /*!< The user can set this parameter, to keep track of which pyramid level these patterns are for */
    /* TODO: change to int8_t or S16, if possible */
    int32_t relative_patterns[CORB_NUM_ORIENTATIONS][CORB_NUM_PATTERNS * 8];
    int32_t rotated_patterns[CORB_NUM_ORIENTATIONS][CORB_NUM_PATTERNS * 4];
    int32_t integralImageWidth;
}CORBPatterns;

/*!
 * \brief Structure containing automatically computed offset information needed by \ref VLIB_ORB_computeOrientation
 */
typedef struct {
    int32_t orientation_horizontal_offsets[CORB_NUM_OFAST_OFFSETS];
    int32_t orientation_vertical_offsets[CORB_NUM_OFAST_OFFSETS];
    int32_t u_max[CORB_HALF_PATCH_SIZE + 1];
}CORBOrientationOffsets;

/*!
 * \brief Structure defining the ORB Input (input buffers containing data needed for various stages of ORB)
 */
typedef struct {
    CORBPatterns           patterns; /*!< Automatically populated by calling \ref cORB_init() */
    CORBOrientationOffsets offsets;  /*!< Automatically populated by calling \ref cORB_init() */
    uint8_t               *image;        /*!< User-populated input image */
    uint8_t               *prefimage;    /*!< Reserved: Can be NULL since it is NOT currently used in VLIB */
    int16_t               *harrisImage;  /*!< User-populated pointer to the harris score output obtained by calling \ref VLIB_harrisScore_7x7 */
    uint32_t              *integralImage; /*!< User-populated pointer to the integral image obtained by calling \ref VLIB_integralImage8 */
    char                  *scratchBuffer; /*!< User-populated pointer to scratch buffer of size returned by calling getRequiredScratchSize(). Must be 8 byte aligned */
    int8_t                *orbPattern31; /*!< User-populated pointer to precomputed orbPattern31 array (found in VLIB_orb_idat.c file) */
}CORBInput;


/*!
 * \brief Structure defining a feature (Used by FAST and ORB functions)
 */
typedef struct {
    int32_t x;                                 /*!< X-coordinate of the feature. Set by corner detector APIs: \ref VLIB_originalfast9_detectCorners,
                                                \ref VLIB_originalfast12_detectCorners, \ref VLIB_afast9_detectCorners, or \ref VLIB_afast12_detectCorners */
    int32_t y;                                 /*!< Y-coordinate of the feature. Set by corner detector APIs: \ref VLIB_originalfast9_detectCorners,
                                                \ref VLIB_originalfast12_detectCorners, \ref VLIB_afast9_detectCorners, or \ref VLIB_afast12_detectCorners  */
    int32_t octave;                            /*!< Indicates which level of the pyramid
                                                VLIB functions do not explicitly use thie parameter, but the user can set this parameter
                                                to keep track of which pyramid level this feature is for */
    VLIB_F32 angle;                             /*!< Angle of the feature in degress.  Set by \ref VLIB_ORB_computeOrientation */ /*TODO: make integer (or fixed point) */
    int32_t  fastResponse;                     /*!< Fast score of feature.  Set by \ref VLIB_originalfast9_score or \ref VLIB_originalfast12_score  */
    int16_t  harrisResponse;                   /*!< Harris score of feature.  Set by \ref VLIB_ORB_getHarrisScore, SQ5.10 */
    uint8_t  descriptor[CORB_NUM_PATTERNS / 8]; /*!< Feature descriptor. Set by \ref VLIB_ORB_computeRBrief. */
}CORBFeature;

/*!
 * \brief Structure defining the ORB (and aFast) output (number and list of features found)
 */
typedef struct {
    CORBFeature *features;     /*!< Contains arrray of features.  Size should be \ref CORB_MAX_FEATURES. */
    int32_t      n_features;       /*!< Number of features contained in the features buffer */
}CORBOutput;

#ifdef __cplusplus
}
#endif



#endif /* define VLIB_ORB_H */

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

