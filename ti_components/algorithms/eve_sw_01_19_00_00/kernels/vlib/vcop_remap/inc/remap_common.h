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


#ifndef REMAP_COMMON_H
#define REMAP_COMMON_H

#ifdef __cplusplus
    extern "C" {
#endif

#include <stdint.h>


#define HORZ_TILE_PADDING (2U)
#define VERT_TILE_PADDING (2U)

/**
 *  @enum       eFormat
 *  @brief      Format of the Image (Chroma Format) - it is 8 bit field
 *
 *  @remarks    lower 7-bits reserved for format and upper bit is
 *              for alpha infomration
*/
typedef enum {
    U8BIT      = 0,
    S8BIT      = 1,
    U16BIT     = 2,
    S16BIT     = 3,
    YUV_422IBE = 4,
    YUV_422ILE = 5,
    YUV_420SP  = 6
} eFormat;

typedef uint8_t Format;



/*!
 Funtion to return the bytes per pixel for a given format
*/
static inline uint16_t sizeofFormat(Format format)
{
    /* LUT To compute the bytes per pixel for a given format */
    const uint16_t sizeOfFormat[] = { 1, 1, 2, 2, 2, 2, 1 };
    eFormat inpFormat = (eFormat)format;

    return (sizeOfFormat[inpFormat]);
}

/*!

  @struct convertMapBlockInfo

  @brief  This structure contains the parameters which assist Remap module to
          perform block level Pixel Remap. It is produced by convert map module
          and consumed by Remap.

  @param  inputBlockWidth: Block width of Input required to perform Remap
  @param  inputBlockWidthDiv2: Block width/2 of Input required to perform Remap. It
          is required for chroma Remap
  @param  inputBlockWidthQ16: : 1/(Block width) of Input required to perform Remap. It
          is required for on the fly computation of LUT for chroma Remap
  @param  inputBlockHeight : Block height of Input required to perform Remap
  @param  inBlock_x : X co-ordinate of start position of input block from top left corner
          of image
  @param  inBlock_y : Y co-ordinate of start position of input block from top left corner
          of image
  @param  padding[10]: Padd so the structure is 32 bytes aligned for TLU requirement

*/

typedef struct
{
  uint16_t inputBlockWidth;
  uint16_t inputBlockWidthDiv2;
  uint16_t inputBlockWidthQ16;
  uint16_t inputBlockHeight;
  uint16_t inBlock_x;
  uint16_t inBlock_y;
  uint16_t padding[10];
} convertMapBlockInfo;

/*!

  @struct Size

  @brief  This structure contains the parameters which helps defining size of
          a 2d BLOCK

  @param  width  : width of the block in pixels
  @param  height : height of the block in pixels

*/
typedef struct {
    uint32_t width;
    uint32_t height;
} Size;



/*!

  @struct sTileInfo

  @brief  This structure contains the information of an Input Tile mapped to
          an Output Block

  @param  inBlock_x  : Horizontal offset of the tile (in pixels)
  @param  inBlock_y  : Vertical offset of the tile (in pixels)
  @param  numPixels : Number of pixels backmapped from output block to input tile
*/
typedef struct
{
  uint16_t inBlock_x;
  uint16_t inBlock_y;
  uint16_t numPixels;
} sTileInfo;


/*!

  @struct sTileLutHeader

  @brief  This structure contains the header information of an Input Tile mapped to
          an Output Block

  @param  numPixels : Number of pixels backmapped from output block to input tile
  @param  numEvenPixels : Number of even pixels backmapped from output block to input tile
                if format is YUV 420 SP, then even pixels correspond to the backmapped output block pixels
                              at even locations along x and y directions.
               if format is YUV 422, then even pixels correspond to the backmapped output block pixels
                             at even locations along x direction.
  @param  numOddPixels  : Number of odd pixels (total - even) backmapped from output block to input tile

*/
typedef struct
{
  uint16_t numPixels;
  uint16_t numEvenPixels;
  uint16_t numOddPixels;
} sTileLutHeader;




/*!

  @struct RemapMaps

  @brief  This structure defines the parameters to do LUT conversion from
        frame based LUT to block based LUT

  @param  srcMap [In]: srcMap points to an input array of (x,y) coordinates in
        float or uint32 - this is frame level LUT

  @param mapDim [In] : width and height of the coordinate map pointed by the above
        srcMap, which are also the destination ROI's width and height

  @param  srcImageDim [In]; Dimensions of the source image, doesn't need to be
         same as mapDim and usually are larger

  @param  isSrcMapFloat [In]: Is srcMap floating point ? Floating point vs Uint32
          will result in slower execution of however advantage is that the qShift
          doesn’t need to be fixed beforehand

  @param  srcFormat [In]: source format: Refer enumeration Format

  @param  outputBlockDim [In]: output block dimensions
          which must divide mapDim.width and mapDim.height .
          Width must be multiple of 16 bytes
  @param  blockMap [In/Out]
          pointer to block-partitioned map of indexes in Q format. The convertMap
          routine shall populate this buffer in below format
          RemapBlockInfo of Block0 followed by Linear LUT for Block0 followed by
          RemapBlockInfo of Block1 followed by Linear LUT for Block1
          ... and so on
          This buffer is allocated by the user of covert_map routine and expected size is
          (sizeof(RemapBlockInfo) + 2*outputBlockDim.width*outputBlockDim.height) *
          ( 2  + (mapDim.width * mapDim.height) / (outputBlockDim.width * outputBlockDim.height))

  @param  qShift [In]
          Number of fractional bits used to represent Q-numbers pointed by srcMap

  @param  maxInputBlockDim [Out]: worst case input block dimensions
          It helps for remap routine to do a worst case memory allocation

  @param  maxInputBlockSize [Out]: worst case input block size
          It helps for remap routine to do a worst case memory allocation
*/
/* This structure needs to be obliterated into:
     1. a structure which inputs data into */

/* In this sructure, srcMap, srcImageDim, isSrcMapFloat are not used in Remap Applet/Kernel. They can be moved out of this structure. */
/* This structure can be split between what is needed by Remap, what is needed by ConvertMap and what is generated by COnvertMap. */
typedef struct
{
  const void *srcMap;
  Size        mapDim;
  Size        srcImageDim;
  uint8_t     isSrcMapFloat;
  Format      srcFormat;
  Size        outputBlockDim;
  Size        inputTileDim;
  uint8_t    *outputBlkInfo;
  sTileInfo  *tileInfo;
  uint16_t    maxNumPixelsinTile;
  uint16_t    maxNumEvenPixelsinTile;
  uint16_t    maxNumOddPixelsinTile;
  uint32_t    tileInfoSize;
  Size        maxInputBlockDim;
  uint32_t    maxInputBlockSize;
  void       *blockMap;
  uint8_t     qShift;
} sConvertMap;



/**
 *  @enum       eInterpolation
 *  @brief      Interpolation type - Nearest Neighbor or Bi-linear interpolation
 *
*/

typedef enum {
    NN,
    BILINEAR
} eInterpolation;

typedef uint8_t Interpolation;

/* Structure used as input parameter to CPIS_remap()
 */


/*!

  @struct RemapParms

  @brief  This structure contains the parameters which assist Remap module to
          perform block level Pixel Remap. It is produced by user

  @param  interpolationLuma
          interpolation method for luma: bilinear or NN  @sa eInterpolation
  @param  interpolationChroma
          interpolation method for chroma: bilinear or NN @sa eInterpolation
  @param  rightShift
          optional right shift to convert from 16-bit to 8-bit for instance
  @param  sat_high
          upper bound saturation limit applied after shift amount of 'rightShift
  @param  sat_high_set
          upper bound saturation value applied after shift amount of 'rightShift
  @param  sat_low
          lower bound saturation limit applied after shift amount of 'rightShift
  @param  sat_low_set
          lower bound saturation value applied after shift amount of 'rightShift
  @param  maps - Structure to hold infomration for convert map (frame to Block )
          @sa sConvertMap

*/
typedef struct {
    Interpolation interpolationLuma;
    Interpolation interpolationChroma;
    uint8_t       rightShift;
    int32_t       sat_high;
    int32_t       sat_high_set;
    int32_t       sat_low;
    int32_t       sat_low_set;
    sConvertMap   maps;
    uint32_t      reserved[3];
} RemapParms;


#ifdef __cplusplus
 }
#endif

#endif
