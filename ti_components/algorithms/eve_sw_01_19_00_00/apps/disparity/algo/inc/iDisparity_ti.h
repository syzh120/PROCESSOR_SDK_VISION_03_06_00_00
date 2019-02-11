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


/**
 *  @file       iDisparity_ti.h
 *
 *  @brief      This file defines the ivision interface for disparity calculation Applet
 *  @version 0.0 (July 2014) : Base version.
 */

/** @ingroup    iDISPARITY */
/*@{*/
#ifndef IDISPARITY_TI_H
#define IDISPARITY_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>

/**
 * @brief Macro symbols used as command passed to the control API
 */
#define DISPARITY_TI_GET_OUTPUT_BLOCK_DIM 0x0 /* Get output block's dimensions (width & height) derived during applet creation */

/**
 * @brief Macro symbols used as error code returned by the alloc init, process, control or deinit APIs. 
 */
typedef enum 
{
    DISPARITY_TI_ERROR_INVALID_ROI_WIDTH = IALG_CUSTOMFAILBASE ,
    DISPARITY_TI_ERROR_INVALID_ROI_HEIGHT,
    DISPARITY_TI_ERROR_INVALID_INPUT_BITDEPTH,
    DISPARITY_TI_PARAMETER_VALUE_NOT_SUPPORTED
} DISPARITY_TI_ErrorCodes ;

/**
 * @brief The unique const funtion table for the DISPARITY_HAMDIST_TI.
 */
extern const IVISION_Fxns DISPARITY_TI_VISION_FXNS;

/**
 * @brief IRES interface of the DISPARITY_TI_ algorithm
 */
extern const IRES_Fxns DISPARITY_TI_IRES;

/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of buffer
            There are 2 input buffers descriptor

            DISPARITY_TI_BUFDESC_IN_LEFT: This buffer descriptor provides the
            actual left image data required by algorithm. The data is composed of 4 bytes or 8 bytes census codewords

            DISPARITY_TI_BUFDESC_IN_RIGHT: This buffer descriptor provides the
            actual right image data required by algorithm. The data is composed of 4 bytes or 8 bytes census codewords
 */
typedef enum 
{
    DISPARITY_TI_BUFDESC_IN_LEFT_IMAGE = 0,
    DISPARITY_TI_BUFDESC_IN_RIGHT_IMAGE = 1,
    DISPARITY_TI_BUFDESC_IN_TOTAL = 2
} DISPARITY_TI_InBufOrder ;

/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of out buffer
            There are 2 output buffers descriptor

            DISPARITY_TI_BUFDESC_DISPARITY_OUT: This buffer is filled up by the algorithm and will contain 
            the per pixel 8-bit disparity values from left-right disparity calculation if searchDir= DISPARITY_TI_LEFT_TO_RIGHT.

            DISPARITY_TI_BUFDESC_COST_OUT: This buffer is filled up by the algorithm and will contain 
            the per pixel 16-bits cost values from left-right disparity calculation if searchDir= DISPARITY_TI_LEFT_TO_RIGHT. Different type of costs can be output and they are specified by the parameter
            outputCostType of type DISPARITY_TI_OutputCostType in the creation parameters.

            DISPARITY_TI_BUFDESC_RL_DISPARITY_OUT: This buffer is filled up by the algorithm and will contain 
            the per pixel 8-bit disparity values corresponding to the right to left search if searchDir= DISPARITY_TI_BOTH_DIR.
            If searchDir= DISPARITY_TI_LEFT_TO_RIGHT, the buffer is not written.
 */
typedef enum 
{
    DISPARITY_TI_BUFDESC_DISPARITY_OUT = 0,
    DISPARITY_TI_BUFDESC_COST_OUT = 1,
    DISPARITY_TI_BUFDESC_PREV_ADJ_COST_OUT = 2,
    DISPARITY_TI_BUFDESC_NEXT_ADJ_COST_OUT = 3,
    DISPARITY_TI_BUFDESC_RL_DISPARITY_OUT = 4,
    DISPARITY_TI_BUFDESC_OUT_TOTAL = 5
} DISPARITY_TI_OutBufOrder ;

/**
    @brief  This enum type defines the method used to caculate the cost of each disparity.

            DISPARITY_TI_SAD: Sum of absolute difference. The left and right images are assumed to contain intensity pixel values of 8 or 16-bits.

            DISPARITY_TI_HAM_DIST: Hamming distance. The left and right frames are assumed to hold codeword values of every pixel. Generally, census transform has been previously executed to produce the codewords.

 */
typedef enum {
    DISPARITY_TI_SAD= 0,
    DISPARITY_TI_HAM_DIST= 1
} DISPARITY_TI_CostMethod;

/**
    @brief  This enum type defines the direction of the disparity search

            DISPARITY_TI_LEFT_TO_RIGHT: Disparity search is done by fixing a pixel in left image and then searching for the minimum cost pixel in the right image, along the same epipolar line.

            DISPARITY_TI_RIGHT_TO_LEFT: Disparity search is done by fixing a pixel in right image and then searching for the minimum cost pixel in left right image, along the same epipolar line.

            DISPARITY_TI_BOTH_DIR: In addition to left-right search, right-left search is also performned by fixing a pixel in right image and then searching for the minimum cost pixel in the left image, along the same epipolar line.
                                        Disparities values corresponding to right-left search are written out in buffer ID DISPARITY_TI_BUFDESC_RL_DISPARITY_OUT.
                                        This is used in LR consistency check.

 */
typedef enum {
    DISPARITY_TI_LEFT_TO_RIGHT=0,
    DISPARITY_TI_RIGHT_TO_LEFT,
    DISPARITY_TI_BOTH_DIR
} DISPARITY_TI_SearchDir;


/**
    @brief  Below DISPARITY_TI_OutputCostType enums define the type of cost values written by the function into the output buffer with identifier DISPARITY_TI_BUFDESC_COST_OUT
            Internally for each pixel P(i,j) with i=[0.., width-1] & j=[0.., height-1] up to numDisparities cost values are computed, thus producing an array COST(d,i,j) with d=[0,...,numDisparities-1] and i=[0,...,width-1], j=[0.., height-1].
            The function offers choices on what cost values can be written out to DISPARITY_TI_BUFDESC_COST_OUT. Each cost value is a 16-bit integer.

            Here are the output cost type supported:

            DISPARITY_TI_NOCOST: no output cost value is written into the buffer DISPARITY_TI_BUFDESC_COST_OUT.

            DISPARITY_TI_MINCOST: for each pixel, the cost value corresponding to the best disparity found is output. 
                                        The cost value can be characterized as the minimum cost value accross all disparities searched.
                                        So for every pixel P(i,j) what is produced is MINCOST(i,j)= COST(dmin,i,j)= min(COST(d,i,j)) with d varying from 0,.. to numDisparities-1 and for which minimum is attained at d= dmin.
                                        Note that dmin is different for every pixel and in reality is a function of i & j .

                                        The format of the output frame is:

                                        row 0:        MINCOST(0,0),        MINCOST(1,0), ....        MINCOST(width-1,0)
                                        row 1:        MINCOST(0,1),        MINCOST(1,1), ....        MINCOST(width-1,1)
                                        ...
                                        row height-1: MINCOST(0,height-1), MINCOST(1,height-1), .... MINCOST(width-1,height-1)

                                        In total width x height x 2 bytes are produced . 

            DISPARITY_TI_MIN_ADJACENT_COSTS: in addition to the minimum cost, adjacent costs are written out. 
                                                   Adjacent costs are defined as follow: if for a pixel P(i,j), COST(dmin,i,j) is the minimum cost corresponding to the best disparity then COST(dmin-1, i,j) and COST(dmin+1, i,j) are the 
                                                   defined as adjacent costs. Note that dmin is different for every pixel and in reality is a function of i & j .

                                                   The format of the output frame  is: 

                                                   row 0: COST(dmin-1, 0, 0),   COST(dmin-1, 1, 0), ... COST(dmin-1, width-1, 0)
                                                   row 0: COST(dmin, 0, 0),     COST(dmin, 1, 0), ...   COST(dmin, width-1, 0)
                                                   row 0: COST(dmin+1, 0, 0),   COST(dmin+1, 1, 0), ... COST(dmin+1, width-1, 0)
                                                   row 1: COST(dmin-1, 0, 1),   COST(dmin-1, 1, 1), ... COST(dmin-1, width-1, 1)
                                                   row 1: COST(dmin, 0, 1),     COST(dmin, 1, 1), ...   COST(dmin, width-1, 1)
                                                   row 1: COST(dmin+1, 0, 1),   COST(dmin+1, 1, 1), ... COST(dmin+1, width-1, 1)
                                                   ...
                                                   row height-1: COST(dmin-1, 0, height-1),   COST(dmin-1, 1, height-1), ... COST(dmin-1, width-1, height-1)
                                                   row height-1: COST(dmin, 0, height-1),     COST(dmin, 1, height-1), ...   COST(dmin, width-1, height-1)
                                                   row height-1: COST(dmin+1, 0, height-1),   COST(dmin+1, 1, height-1), ... COST(dmin+1, width-1, height-1)

                                                   In total 3 x width x height x 2 bytes are produced . This format is used for interpolating the disparity values in some post-processing stage.

          DISPARITY_TI_ALL_COSTS: all costs for every disparity values are written out. 

                                                   The format of the output frame  is:

                                                   row 0: COST(0, 0, 0),                   COST(0, 1, 0), ...                COST(0, width-1, 0)
                                                   row 0: COST(1, 0, 0),                   COST(1, 1, 0), ...                COST(1, width-1, 0)
                                                   row 0: COST(2, 0, 0),                   COST(2, 1, 0), ...                COST(2, width-1, 0)
                                                   row 0: ...
                                                   row 0: COST(numDisparities-1 , 0, 0),   COST(numDisparities-1, 1, 0), ... COST(numDisparities-1, width-1, 0)

                                                   row 1: COST(0, 0, 1),                   COST(0, 1, 1), ...                COST(0, width-1, 1)
                                                   row 1: COST(1, 0, 1),                   COST(1, 1, 1), ...                COST(1, width-1, 1)
                                                   row 1: COST(2, 0, 1),                   COST(2, 1, 1), ...                COST(2, width-1, 1)
                                                   row 1: ...
                                                   row 1: COST(numDisparities-1 , 0, 1),   COST(numDisparities-1, 1, 1), ... COST(numDisparities-1, width-1, 1)
                                                   ...

                                                   row height-1: COST(0, 0, height-1),                   COST(0, 1, height-1), ...                COST(0, width-1, height-1)
                                                   row height-1: COST(1, 0, height-1),                   COST(1, 1, height-1), ...                COST(1, width-1, height-1)
                                                   row height-1: COST(2, 0, height-1),                   COST(2, 1, height-1), ...                COST(2, width-1, height-1)
                                                   row height-1: ...
                                                   row height-1: COST(numDisparities-1 , 0, height-1),   COST(numDisparities-1, 1, height-1), ... COST(numDisparities-1, width-1, height-1)

                                                   In total numDisparities x width x height x 2 bytes are produced. 

 */
typedef enum
{
    DISPARITY_TI_NOCOST= 0,
    DISPARITY_TI_MINCOST,
    DISPARITY_TI_MIN_ADJACENT_COSTS,
    DISPARITY_TI_ALL_COSTS
} DISPARITY_TI_OutputCostType;


/**

  @struct DISPARITY_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          census transform applet at create time

  @param  visionParams
          Common parameters for all ivison based modules

  @param  imgFrameWidth
          Width in number of census codewords of the ROI image for which the disparity between left and right image will be produced.

  @param  imgFrameHeight
          Height in number of lines of the ROI image for which the disparity between left and right image will be produced.

  @param  inputBitDepth
          Number of bits in each left and right image's pixel or codewords (depending whether costMethod= DISPARITY_TI_SAD or DISPARITY_TI_HAMMING_DIST). Currently 32-bits is supported.

  @param  winWidth
          Width of the support window, that defines the neighbourhood in which SAD or hamming-distance based cost calculations are performed.

  @param  winHeight
          Height of the support window, that defines the neighbourhood in which SAD or hamming-distance based cost calculations are performed.

  @param  numDisparities
          Number of disparities for which the cost are calculated. For each pixel, the disparity corresponding to the minimumn cost is returned. 
          When earchDir= DISPARITY_TI_LEFT_TO_RIGHT, disparity search is done by fixing a pixel in left image and then searching for the minimum cost pixel in the right image, along the same epilpolar line.
          Setting searchDir= DISPARITY_TI_BOTH will also do the search "from" right image "to" left image.

  @param  disparityStep
          Disparity step allows to down-sample the number of disparities for which the cost is calculated, resulting in faster computation in detriment to precision.

  @param costMethod
          See description of enum type DISPARITY_TI_CostMethod, which defines the method employed to calculate each disparity's cost.
          Currently only DISPARITY_TI_HAM_DIST is supported.
  
  @param  searchDir
          See description of enum type DISPARITY_TI_SearchDir, which defines the direction(s) of the disparity search.  
          Currently only DISPARITY_TI_LEFT_TO_RIGHT is supported.

  @param  outputCostType
          See description of enum type DISPARITY_TI_OutputCostType, which defines what type of cost values are written out.
          Currently only DISPARITY_TI_MINCOST is supported.

 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t imgFrameWidth;
    uint16_t imgFrameHeight;
    uint8_t inputBitDepth;
    uint8_t winWidth;
    uint8_t winHeight;
    uint8_t numDisparities; 
    uint8_t disparityStep;
    uint8_t costMethod;
    uint8_t searchDir;
    uint8_t outputCostType;
} DISPARITY_TI_CreateParams;


/**

  @struct DISPARITY_TI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  visionParams
          Common outArgs for all ivison based modules

  @param  activeImgWidthLeft
          Width in bytes of the area that will be accessed by the EDMA when reading the left image frame.
          For this function, it should always be equal to (imgFrameWidth + winWidth - 1)*inputBitDepth/8 bytes

  @param  activeImgWidthRight
          Width in bytes of the area that will be accessed by the EDMA when reading the right image frame.
          For this function, it should always be equal to (imgFrameWidth + winWidth - 1 + numDisparities - 1)*inputBitDepth/8 bytes

  @param  activeImgHeight
          Height in number of rows of the area that will be accessed by the EDMA when reading the right and left frame.
          For this function, it should always be equal to (imgFrameHeight + winHeight - 1)

  @param  outputBlockWidth
          Output block width in number of pixels returned by BAM_createGraph(). That's useful information to understand performance.

  @param  outputBlockHeight
          Output block height in number of rows returned by BAM_createGraph(). Should always be 1 as the processing is row-wise.

 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
    uint16_t activeImgWidthLeft;
    uint16_t activeImgWidthRight;
    uint16_t activeImgHeight;
    uint16_t outputBlockWidth;
    uint16_t outputBlockHeight;

} DISPARITY_TI_outArgs;

/**

  @struct DISPARITY_TI_ControlInParams
  @brief  This structure contains all the input parameters which controls
          the applet after creation. 
          In the case of disparity calculation, it does not have any additional parameters
          than the default algParams from which it inherits the content.

  @param  algParams
          Common params for all IALG based modules

 */
typedef struct
{
    IALG_Params algParams;
} DISPARITY_TI_ControlInParams;

/**

  @struct DISPARITY_TI_ControlOutputParams
  @brief  This structure contains all the output parameters written by the control function
          the applet after creation. Mainly it contains output block dimensions which can be queried
          after graph creation. The application should use these values to make sure that any ROI's width and height
          are multiple of the output block's width and height.

  @param  algParams
          Common params for all IALG based modules

  @param  outputBlockWidth
          output block width

  @param  outputBlockHeight
          output block height

 */
typedef struct
{
    IALG_Params algParams;
    uint16_t outputBlockWidth;
    uint16_t outputBlockHeight;

} DISPARITY_TI_ControlOutParams;

/*@}*/
/* iDISPARITY */

#endif /*IDISPARITY_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


