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


#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "alg_osal.h"
#include "convert_map.h"
#include "remap_common.h"

#define NUM_FRAC_BITS   (4)

#define ALIGN_2SIMD(a)    ((a + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define ALIGN_SHORT(a)    ((a + 2-1) & ~(2-1))

#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define MAX(a,b) ((a)>(b) ? (a) : (b))


typedef struct
{
  uint16_t *ptrIndexMap;
  uint16_t *ptrEvenIndexMap;
  uint8_t  *ptrFracMap;
  uint8_t  *ptrEvenFracMap;
  uint16_t *ptrOffsetMap;
  uint16_t *ptrEvenOffsetMap;
  uint16_t  numPixels;
  uint16_t  numEvenPixels;
} tileLutInfo;

typedef struct _ltileinfo
{
  uint16_t   columnIndex;
  uint16_t   rowIndex;
  uint16_t   numPixels;
  struct _ltileinfo *next;
} lTileInfo;


inline uint32_t convertMap_round(float float_a)
{
    uint32_t inc, int_a;

    int_a = float_a;
    inc = (float_a - (float)int_a) >= 0.5 ? 1 : 0;
    return (int_a + inc);
}


int32_t convertMap_tileApproach_getMemorysizeBlockMap(sConvertMap *maps)
{
  uint16_t outputWidth, outputHeight, inputTileWidth, inputTileHeight, outputBlockSize, numOutputBlocks;
  uint16_t numHorzOutputBlocks, numVertOutputBlocks;
  uint32_t blockMapByteLen = 0;
  uint16_t srcWidth, srcHeight, numHorzTiles, numVertTiles, r, c, block_row, block_col, out_y, out_x;
  uint16_t intile_x, intile_y, x, y, numTiles, totalNumTiles;
  tileLutInfo **tileArry;
  uint32_t *srcMapU32;
  float    *srcMapFloat;

  if (maps->isSrcMapFloat)
    srcMapFloat= (float*)maps->srcMap;
  else
    srcMapU32= (uint32_t*)maps->srcMap;

  outputWidth     = maps->outputBlockDim.width;
  outputHeight    = maps->outputBlockDim.height;
  outputBlockSize = outputWidth*outputHeight;

  inputTileWidth  = maps->inputTileDim.width;
  inputTileHeight = maps->inputTileDim.height;

  if (maps->mapDim.width % outputWidth) {
    PRINTF("convertMap() error: maps->mapDim.width must be multiple of maps->outputBlockDim.width\n");
    return -1;
  }

  if (maps->mapDim.height % outputHeight) {
    PRINTF("convertMap() error: maps->mapDim.height must be multiple of maps->outputBlockDim.height\n");
    return -1;
  }

  if (maps->srcImageDim.width % inputTileWidth) {
    PRINTF("convertMap() error: maps->srcImageDim.width must be multiple of inputTileWidth\n");
    return -1;
  }

  if (maps->srcImageDim.height % inputTileHeight) {
    PRINTF("convertMap() error: maps->srcImageDim.height must be multiple of inputTileHeight\n");
    return -1;
  }

  numHorzOutputBlocks = maps->mapDim.width / outputWidth;
  numVertOutputBlocks = maps->mapDim.height / outputHeight;
  numOutputBlocks     = numHorzOutputBlocks * numVertOutputBlocks;
  srcWidth  = maps->srcImageDim.width;
  srcHeight = maps->srcImageDim.height;

  numHorzTiles = srcWidth/inputTileWidth;
  numVertTiles = srcHeight/inputTileHeight;
  maps->tileInfoSize = 0;

    tileArry = (tileLutInfo **)malloc(numVertTiles * sizeof(tileLutInfo *));

    if(tileArry == NULL) {
      PRINTF("convertMap() error: Out of Memory\n");
      return -1;
    }

    for(r = 0; r < numVertTiles; r++) {
      tileArry[r] = (tileLutInfo *)malloc(numHorzTiles * sizeof(tileLutInfo));

      if(tileArry[r] == NULL) {
        PRINTF("convertMap() error: Out of Memory\n");
        return -1;
      }
    }

    /* Loop through the Output Blocks */
    for (block_row= 0, out_y=0; block_row < maps->mapDim.height; block_row += outputHeight, out_y++)
    {
      for (block_col= 0, out_x=0; block_col < 2*maps->mapDim.width; block_col+= 2*outputWidth, out_x++)
      {

        for(r = 0; r < numVertTiles; r++) {
          memset(tileArry[r], 0, numHorzTiles * sizeof(tileLutInfo));
        }

        /*
            * In 1st scan, we just continuously
            * update the coordinates of the input bounding box's upper left and lower right corners
            */
        if (maps->isSrcMapFloat) {
          for (r= 0; r < outputHeight; r++)
            for (c= 0; c < 2*outputWidth; c+=2){ // increment by 2 because each index corresponds to pair (x,y)
              x= (uint16_t)(srcMapFloat[(block_row + r)*2*maps->mapDim.width + block_col + c]);
              y= (uint16_t)(srcMapFloat[(block_row + r)*2*maps->mapDim.width + block_col + c + 1]);

              intile_x = x/inputTileWidth;
              intile_y = y/inputTileHeight;

              tileArry[intile_y][intile_x].numPixels++;
            }
        }
        else {
          for (r= 0; r < outputHeight; r++)
            for (c= 0; c < 2*outputWidth; c+=2){ // increment by 2 because each index corresponds to pair (x,y)
              x= (uint16_t)(srcMapU32[(block_row + r)*2*maps->mapDim.width + block_col + c]>>maps->qShift);
              y= (uint16_t)(srcMapU32[(block_row + r)*2*maps->mapDim.width + block_col + c + 1]>>maps->qShift);

              intile_x = x/inputTileWidth;
              intile_y = y/inputTileHeight;

              tileArry[intile_y][intile_x].numPixels++;
            }
        }

        numTiles = 0;

        /* Scan with tileArry and generate heuristics to partition LUT memory */
        for (r= 0; r < numVertTiles; r++)
          for (c= 0; c < numHorzTiles; c++){
            if(tileArry[r][c].numPixels) {
              numTiles++;
            }
          }
          maps->tileInfoSize    += numTiles;
    }
  }
  /* One tileInfo having numPixels = 0 needed to avoid DMAing unnecessary data in last Trigger_Source() */
  maps->tileInfoSize++;
  totalNumTiles      = maps->tileInfoSize;
  maps->tileInfoSize = maps->tileInfoSize*sizeof(sTileInfo);

  blockMapByteLen = 0;

  /* Memory for maps->outputBlkInfo */
  blockMapByteLen += numOutputBlocks;

  /* Memory for maps->tileInfo */
  blockMapByteLen += maps->tileInfoSize;

  /*********  Memory for maps->blockMap ************/
  /* For every pixel in output image, LUT is generated. */
  /* LUT is of 5 bytes = 2 bytes for Integer Index + 1 B for Frac Index + 2 B for Scatter Store Offset */
  blockMapByteLen += (5 * outputBlockSize) * numOutputBlocks;

  /* Additional memory to have 6 bytes of header data on IndexMap per tile */
  blockMapByteLen += 6*totalNumTiles;

  /* Additional memory to ensure tluScatterStore memory per tile is aligned to short */
  blockMapByteLen += 2*totalNumTiles;//32;

  for(r = 0; r < numVertTiles; r++) {
    free(tileArry[r]);
  }
  free(tileArry);


  return blockMapByteLen;
}


int32_t convertMap_tileApproach(sConvertMap *maps, RemapStat *stat, void *memLUT, uint8_t enableMerge)
{
  sTileInfo *ptrTileInfo;
  lTileInfo *lTileInfoHead, *lTileInfoPrev, *lTileInfoCurr, *lTileInfoNew, *lTileInfofirst;
  sTileLutHeader *ptrLUTHeader;
  uint8_t  *ptrOutputBlkInfo;
  uint16_t *ptrIndexMap;
  uint16_t x, y, tluIndex, width, height, block_row, block_col, out_x, out_y, r, c;
  float    float_x, float_y;
  uint16_t frac_x, frac_y;
  uint32_t *srcMapU32;
  float    *srcMapFloat;
  uint8_t  inputTileWidth, inputTileHeight;
  uint16_t intile_x, intile_y, offset_x, offset_y, srcWidth, srcHeight, numHorzTiles, numVertTiles, numOddPixelsinTile;
  uint16_t numHorzOutputBlocks, numVertOutputBlocks, numOutputBlocks;
  tileLutInfo **tileArry;
  Format   srcFormat;
#ifdef DEBUG
  float    numTiles;
  uint16_t numPixels;
#endif

  if (maps->isSrcMapFloat)
    srcMapFloat= (float*)maps->srcMap;
  else
    srcMapU32= (uint32_t*)maps->srcMap;

  width= maps->outputBlockDim.width;
  height= maps->outputBlockDim.height;

  srcWidth  = maps->srcImageDim.width;
  srcHeight = maps->srcImageDim.height;

  srcFormat = maps->srcFormat;

/* IMP: 2 considerations
    1. inputTileWidth should be a multiple of 32 for lookup of one row below.
    2. +1 padding should be given in both width and height.
*/

  inputTileWidth  = maps->inputTileDim.width;
  inputTileHeight = maps->inputTileDim.height;

  if (maps->mapDim.width % width) {
    PRINTF("convertMap() error: maps->mapDim.width must be multiple of maps->outputBlockDim.width\n");
    return -1;
  }

  if (maps->mapDim.height % height) {
    PRINTF("convertMap() error: maps->mapDim.height must be multiple of maps->outputBlockDim.height\n");
    return -1;
  }

  if (srcWidth % inputTileWidth) {
    PRINTF("convertMap() error: maps->srcImageDim.width must be multiple of inputTileWidth\n");
    return -1;
  }

  if (srcHeight % inputTileHeight) {
    PRINTF("convertMap() error: maps->srcImageDim.height must be multiple of inputTileHeight\n");
    return -1;
  }

  numHorzOutputBlocks = maps->mapDim.width / width;
  numVertOutputBlocks = maps->mapDim.height / height;
  numOutputBlocks     = numHorzOutputBlocks * numVertOutputBlocks;

  numHorzTiles = srcWidth/inputTileWidth;
  numVertTiles = srcHeight/inputTileHeight;

  tileArry = (tileLutInfo **)malloc(numVertTiles * sizeof(tileLutInfo *));

  if(tileArry == NULL) {
    PRINTF("convertMap() error: Out of Memory\n");
    return -1;
  }

  for(r = 0; r < numVertTiles; r++) {
    tileArry[r] = (tileLutInfo *)malloc(numHorzTiles * sizeof(tileLutInfo));

    if(tileArry[r] == NULL) {
      PRINTF("convertMap() error: Out of Memory\n");
      return -1;
    }
  }


  /* Scan the list of coordinates in srcMap in blockwise fashion
  * to populate dstMapStruct->srcMap[].
  * We implement a 2-pass scan
  * In 1st scan, we just continuously
  * update the coordinates of the input bounding box
  */
  maps->maxInputBlockSize      = 0;
  /* This is approximation. The correct value needs to be figured out */
  maps->maxNumPixelsinTile     = 0;
  maps->maxNumEvenPixelsinTile = 0;
  maps->maxNumOddPixelsinTile  = 0;

  maps->outputBlkInfo = (uint8_t *)ALIGN_SHORT((uint32_t)memLUT);
  maps->tileInfo      = (sTileInfo *)ALIGN_SHORT((uint32_t)((uint8_t *)memLUT + numOutputBlocks));
  maps->blockMap      = (void *)ALIGN_SHORT((uint32_t)((uint8_t *)maps->tileInfo + maps->tileInfoSize + (maps->tileInfoSize/sizeof(sTileInfo))));

  ptrOutputBlkInfo = (uint8_t *)maps->outputBlkInfo;
  ptrTileInfo    = (sTileInfo *)maps->tileInfo;
  ptrIndexMap     = (uint16_t *)maps->blockMap;

  maps->tileInfoSize = 0;

  if (stat->collectStatFlag)
  {
    /* Collect statistics on expansion/reduction factor of each block */
    stat->maxWidthRatio= 0;
    stat->minWidthRatio= 10000.0; /* some big number */
    stat->averWidthRatio= 0;

    /* Collect statistics on expansion/reduction factor of each block */
    stat->maxHeightRatio= 0;
    stat->minHeightRatio= 10000.0; /* some big number */
    stat->averHeightRatio= 0;
  }

  /* Loop through the Output Blocks */
  for (block_row= 0, out_y=0; block_row < maps->mapDim.height; block_row += height, out_y++)
  {
    for (block_col= 0, out_x=0; block_col < 2*maps->mapDim.width; block_col+= 2*width, out_x++)
    {

      for(r = 0; r < numVertTiles; r++) {
        memset(tileArry[r], 0, numHorzTiles * sizeof(tileLutInfo));
      }

      /*
          * In 1st scan, we just continuously
          * update the coordinates of the input bounding box's upper left and lower right corners
          */
      if (maps->isSrcMapFloat) {
        for (r= 0; r < height; r++)
          for (c= 0; c < 2*width; c+=2){ // increment by 2 because each index corresponds to pair (x,y)
            x= (uint16_t)(srcMapFloat[(block_row + r)*2*maps->mapDim.width + block_col + c]);
            y= (uint16_t)(srcMapFloat[(block_row + r)*2*maps->mapDim.width + block_col + c + 1]);

            intile_x = x/inputTileWidth;
            intile_y = y/inputTileHeight;

            tileArry[intile_y][intile_x].numPixels++;

            if(srcFormat == YUV_420SP) {
              if((c/2)%2 == 0 && r%2 == 0) {
                  tileArry[intile_y][intile_x].numEvenPixels++;
              }
            } else if(srcFormat == YUV_422ILE || srcFormat == YUV_422IBE) {
              if((c/2)%2 == 0) {
                  tileArry[intile_y][intile_x].numEvenPixels++;
              }
            }

          }
      }
      else {
        for (r= 0; r < height; r++)
          for (c= 0; c < 2*width; c+=2){ // increment by 2 because each index corresponds to pair (x,y)
            x= (uint16_t)(srcMapU32[(block_row + r)*2*maps->mapDim.width + block_col + c]>>maps->qShift);
            y= (uint16_t)(srcMapU32[(block_row + r)*2*maps->mapDim.width + block_col + c + 1]>>maps->qShift);

            intile_x = x/inputTileWidth;
            intile_y = y/inputTileHeight;

            tileArry[intile_y][intile_x].numPixels++;

            if(srcFormat == YUV_420SP) {
              if((c/2)%2 == 0 && r%2 == 0) {
                  tileArry[intile_y][intile_x].numEvenPixels++;
              }
            } else if(srcFormat == YUV_422ILE || srcFormat == YUV_422IBE) {
              if((c/2)%2 == 0) {
                  tileArry[intile_y][intile_x].numEvenPixels++;
              }
            }

          }
      }

      *ptrOutputBlkInfo = 0;

      lTileInfoHead              = (lTileInfo *)malloc(sizeof(lTileInfo));
      lTileInfoHead->columnIndex = 0xFFFF;
      lTileInfoHead->rowIndex    = 0xFFFF;
      lTileInfoHead->numPixels   = 0xFFFF;
      lTileInfoHead->next        = NULL;

      /* Scan with tileArry and sort the tileInfo based on numPixels in the descending order
                The sorting is an optimization process. It reduces the ARP32 overhead caused due to
                DMA'ing In/Out large blocks while VCOP processing less numMappedPixels or vise-versa */
      for (r= 0; r < numVertTiles; r++) {
        for (c= 0; c < numHorzTiles; c++) {
          if(tileArry[r][c].numPixels) {
            (*ptrOutputBlkInfo)++;

            lTileInfoPrev             = lTileInfoHead;
            lTileInfoCurr             = lTileInfoHead->next;

            lTileInfoNew              = (lTileInfo *)malloc(sizeof(lTileInfo));
            lTileInfoNew->columnIndex = c;
            lTileInfoNew->rowIndex    = r;
            lTileInfoNew->numPixels   = tileArry[r][c].numPixels;

            while(lTileInfoCurr != NULL) {
              if(lTileInfoNew->numPixels >= lTileInfoCurr->numPixels) {
                lTileInfoPrev->next = lTileInfoNew;
                lTileInfoNew->next  = lTileInfoCurr;
                break;
              }
              lTileInfoPrev = lTileInfoCurr;
              lTileInfoCurr = lTileInfoCurr->next;
            }
            if(lTileInfoCurr == NULL) {
              lTileInfoPrev->next = lTileInfoNew;
              lTileInfoNew->next  = NULL;
            }
          }
        }
      }

      /* The below code is an optimzation for scenarios where Merge is enabled
                in the Remap data flow. Such cases involve the additional DMA In of Merge
                and Alpha block along with the last tile corresponding to an output block.
                Therefore, it is better to have the last tile with the least numMappedPixels.
                Also, during the additional DMA, VCOP processes the Second last tile. Hence,
                it is better to have the second last tile with the highest numMappedPixels. The
                below code replaces the first item in the linked list with the second last item to achieve
                the above explained. */
      if(enableMerge) {
        lTileInfofirst = lTileInfoHead->next;
        lTileInfoPrev  = lTileInfoHead->next;
        lTileInfoCurr  = lTileInfoPrev->next;
        if(lTileInfoCurr != NULL) {
            while(lTileInfoCurr->next != NULL) {
              lTileInfoPrev = lTileInfoCurr;
              lTileInfoCurr = lTileInfoCurr->next;
            }
              if(lTileInfoPrev != lTileInfofirst) {
                lTileInfoHead->next = lTileInfofirst->next;
                lTileInfoPrev->next = lTileInfofirst;
                lTileInfofirst->next = lTileInfoCurr;
              }
        }
      }

      /* Scan with sorted Linked List and generate heuristics to partition LUT memory */
      lTileInfoCurr = lTileInfoHead->next;
      while(lTileInfoCurr != NULL) {

        c = lTileInfoCurr->columnIndex;
        r = lTileInfoCurr->rowIndex;

        ptrTileInfo->inBlock_x = c*inputTileWidth;
        ptrTileInfo->inBlock_y = r*inputTileHeight;
        ptrTileInfo->numPixels = tileArry[r][c].numPixels;
        ptrTileInfo++;

        ptrLUTHeader = (sTileLutHeader *)ptrIndexMap;
        ptrLUTHeader->numPixels     = tileArry[r][c].numPixels;
        ptrLUTHeader->numEvenPixels = tileArry[r][c].numEvenPixels;
        ptrLUTHeader->numOddPixels  = tileArry[r][c].numPixels - tileArry[r][c].numEvenPixels;

        tileArry[r][c].ptrEvenIndexMap  = (ptrIndexMap + 3);
        tileArry[r][c].ptrIndexMap      = tileArry[r][c].ptrEvenIndexMap + tileArry[r][c].numEvenPixels;

        tileArry[r][c].ptrEvenFracMap   = (uint8_t *)(tileArry[r][c].ptrEvenIndexMap + tileArry[r][c].numPixels);
        tileArry[r][c].ptrFracMap       = (uint8_t *)(tileArry[r][c].ptrEvenFracMap  + tileArry[r][c].numEvenPixels);

        tileArry[r][c].ptrEvenOffsetMap = (uint16_t *)(tileArry[r][c].ptrEvenFracMap   + ALIGN_SHORT(tileArry[r][c].numPixels));
        tileArry[r][c].ptrOffsetMap     = (uint16_t *)(tileArry[r][c].ptrEvenOffsetMap + tileArry[r][c].numEvenPixels);

        ptrIndexMap                     = tileArry[r][c].ptrEvenOffsetMap + tileArry[r][c].numPixels;

        numOddPixelsinTile = tileArry[r][c].numPixels - tileArry[r][c].numEvenPixels;
        maps->maxNumPixelsinTile        = MAX(maps->maxNumPixelsinTile,     tileArry[r][c].numPixels);
        maps->maxNumEvenPixelsinTile    = MAX(maps->maxNumEvenPixelsinTile, tileArry[r][c].numEvenPixels);
        maps->maxNumOddPixelsinTile     = MAX(maps->maxNumOddPixelsinTile,  numOddPixelsinTile);

        lTileInfoCurr = lTileInfoCurr->next;
      }

      maps->tileInfoSize    += *ptrOutputBlkInfo;
      ptrOutputBlkInfo++;

    /*
        * Now that we got the coordinates of the bounding box, we can generate
        * the indexes/fractional parts from the coordinates
        */
        if (maps->isSrcMapFloat) {
          for (r= 0; r < height; r++)
            for (c= 0; c < width; c++){
              float_x= srcMapFloat[(block_row + r)*2*maps->mapDim.width + block_col + 2*c];
              x= (uint16_t)float_x;
              frac_x= (uint16_t)convertMap_round((float_x - x)*(1<<maps->qShift));
              float_y= srcMapFloat[(block_row + r)*2*maps->mapDim.width + block_col + 2*c + 1];
              y= (uint16_t)float_y;
              frac_y= (uint16_t)convertMap_round((float_y - y)*(1<<maps->qShift));

              intile_x = x/inputTileWidth;
              intile_y = y/inputTileHeight;
              offset_x = x%inputTileWidth;
              offset_y = y%inputTileHeight;
              tluIndex = offset_x + offset_y*(inputTileWidth+HORZ_TILE_PADDING);

              if(srcFormat == YUV_420SP) {
                if(c%2 == 0 && r%2 == 0) {
                  *(tileArry[intile_y][intile_x].ptrEvenIndexMap++)  = (tluIndex);
                  *(tileArry[intile_y][intile_x].ptrEvenFracMap++)   = ((frac_y << NUM_FRAC_BITS) | (frac_x));
                  *(tileArry[intile_y][intile_x].ptrEvenOffsetMap++) = c + r*width;

                } else {
                  *(tileArry[intile_y][intile_x].ptrIndexMap++)  = (tluIndex);
                  *(tileArry[intile_y][intile_x].ptrFracMap++)   = ((frac_y << NUM_FRAC_BITS) | (frac_x));
                  *(tileArry[intile_y][intile_x].ptrOffsetMap++) = c + r*width;

                }
              } else if(srcFormat == YUV_422ILE || srcFormat == YUV_422IBE) {
                if(c%2 == 0) {
                  *(tileArry[intile_y][intile_x].ptrEvenIndexMap++)  = (tluIndex);
                  *(tileArry[intile_y][intile_x].ptrEvenFracMap++)   = ((frac_y << NUM_FRAC_BITS) | (frac_x));
                  *(tileArry[intile_y][intile_x].ptrEvenOffsetMap++) = c + r*width;
                } else {
                  *(tileArry[intile_y][intile_x].ptrIndexMap++)  = (tluIndex);
                  *(tileArry[intile_y][intile_x].ptrFracMap++)   = ((frac_y << NUM_FRAC_BITS) | (frac_x));
                  *(tileArry[intile_y][intile_x].ptrOffsetMap++) = c + r*width;

                }
              } else {
                *(tileArry[intile_y][intile_x].ptrIndexMap++)  = (tluIndex);
                *(tileArry[intile_y][intile_x].ptrFracMap++)   = ((frac_y << NUM_FRAC_BITS) | (frac_x));
                *(tileArry[intile_y][intile_x].ptrOffsetMap++) = c + r*width;
              }
            }

        }
        else {
          uint32_t U32_x, U32_y;

          for (r= 0; r < height; r++)
            for (c= 0; c < width; c++){
              U32_x= srcMapU32[(block_row + r)*2*maps->mapDim.width + block_col + 2*c];
              x= (uint16_t)(U32_x>>maps->qShift);
              frac_x= (uint16_t)(U32_x - (x<<maps->qShift));
              U32_y= srcMapU32[(block_row + r)*2*maps->mapDim.width + block_col + 2*c + 1];
              y= (uint16_t)(U32_y>>maps->qShift);
              frac_y= (uint16_t)(U32_y - (y<<maps->qShift));

              intile_x = x/inputTileWidth;
              intile_y = y/inputTileHeight;
              offset_x = x%inputTileWidth;
              offset_y = y%inputTileHeight;
              tluIndex = offset_x + offset_y*(inputTileWidth+HORZ_TILE_PADDING);

              if(srcFormat == YUV_420SP) {
                if(c%2 == 0 && r%2 == 0) {
                  *(tileArry[intile_y][intile_x].ptrEvenIndexMap++)  = (tluIndex);
                  *(tileArry[intile_y][intile_x].ptrEvenFracMap++)   = ((frac_y << NUM_FRAC_BITS) | (frac_x));
                  *(tileArry[intile_y][intile_x].ptrEvenOffsetMap++) = c + r*width;

                } else {
                  *(tileArry[intile_y][intile_x].ptrIndexMap++)  = (tluIndex);
                  *(tileArry[intile_y][intile_x].ptrFracMap++)   = ((frac_y << NUM_FRAC_BITS) | (frac_x));
                  *(tileArry[intile_y][intile_x].ptrOffsetMap++) = c + r*width;

                }
              } else if(srcFormat == YUV_422ILE || srcFormat == YUV_422IBE) {
                if(c%2 == 0) {
                  *(tileArry[intile_y][intile_x].ptrEvenIndexMap++)  = (tluIndex);
                  *(tileArry[intile_y][intile_x].ptrEvenFracMap++)   = ((frac_y << NUM_FRAC_BITS) | (frac_x));
                  *(tileArry[intile_y][intile_x].ptrEvenOffsetMap++) = c + r*width;
                } else {
                  *(tileArry[intile_y][intile_x].ptrIndexMap++)  = (tluIndex);
                  *(tileArry[intile_y][intile_x].ptrFracMap++)   = ((frac_y << NUM_FRAC_BITS) | (frac_x));
                  *(tileArry[intile_y][intile_x].ptrOffsetMap++) = c + r*width;

                }
              } else {
                *(tileArry[intile_y][intile_x].ptrIndexMap++)  = (tluIndex);
                *(tileArry[intile_y][intile_x].ptrFracMap++)   = ((frac_y << NUM_FRAC_BITS) | (frac_x));
                *(tileArry[intile_y][intile_x].ptrOffsetMap++) = c + r*width;
              }

            }
        }

        lTileInfoPrev = lTileInfoHead;
        while(lTileInfoPrev) {
          lTileInfoCurr = lTileInfoPrev->next;
          free(lTileInfoPrev);
          lTileInfoPrev = lTileInfoCurr;
        }

      }
    }

#ifdef DEBUG
  numTiles = (float)maps->tileInfoSize/(float)numOutputBlocks;
  numPixels = (width*height)/numTiles;

  PRINTF("convertMap() info: Tiles per OutputBlk = %f\n", numTiles);
  PRINTF("convertMap() info: Pixels mapped per Tile = %d\n", numPixels);
#endif

  /* One tileInfo having numPixels = 0 needed to avoid DMAing unnecessary data in last Trigger_Source() */
  ptrTileInfo->inBlock_x = 0;
  ptrTileInfo->inBlock_y = 0;
  ptrTileInfo->numPixels = 0;
  maps->tileInfoSize++;

  maps->tileInfoSize = maps->tileInfoSize*sizeof(sTileInfo);

  if (stat->collectStatFlag) {
    stat->averWidthRatio/=out_x*out_y;
    stat->averHeightRatio/=out_x*out_y;
  }

  for(r = 0; r < numVertTiles; r++) {
    free(tileArry[r]);
  }

  free(tileArry);

  return 0;
}



int32_t convertMap_bbApproach_getMemorysizeBlockMap(sConvertMap *maps)
{
  uint16_t width, height,outputBlockSize;
  uint16_t numHorzBlocks, numVertBlocks;
  uint32_t blockMapByteLen ;

  width= maps->outputBlockDim.width;
  height= maps->outputBlockDim.height;
  outputBlockSize= width*height;

  if (maps->mapDim.width % width) {
    PRINTF("convertMap() error: maps->mapDim.width must be multiple of maps->outputBlockDim.width\n");
    return -1;
  }

  if (maps->mapDim.height % height) {
    PRINTF("convertMap() error: maps->mapDim.height must be multiple of maps->outputBlockDim.height\n");
    return -1;
  }

  numHorzBlocks= maps->mapDim.width / width;
  numVertBlocks= maps->mapDim.height / height;

  /* Addition of 2 to help pipe down phase in VCOP */
  blockMapByteLen= (sizeof(convertMapBlockInfo) + outputBlockSize*3)* (2 + numHorzBlocks*numVertBlocks);

  return blockMapByteLen ;
}


int32_t convertMap_bbApproach(sConvertMap *maps, RemapStat *stat, void *memLUT)
{

  convertMapBlockInfo *ptrInfoMap;
  uint8_t  *ptrfracMap;
  uint16_t *ptrIndexMap;
  uint16_t x, y, tluIndex, width, height, block_row, block_col, out_x, out_y, r, c;
  float float_x, float_y;
  uint16_t frac_x, frac_y;
  uint16_t blockMapBlockSize;
  uint16_t xul, xlr, yul, ylr;
  uint16_t inputBlockWidth, inputBlockHeight;
  uint32_t blockSize;
  uint16_t outputBlockSize;
  uint32_t *srcMapU32;
  float *srcMapFloat;

  if (maps->isSrcMapFloat)
    srcMapFloat= (float*)maps->srcMap;
  else
    srcMapU32= (uint32_t*)maps->srcMap;

  width= maps->outputBlockDim.width;
  height= maps->outputBlockDim.height;
  outputBlockSize= width*height;

  if (maps->mapDim.width % width) {
    PRINTF("convertMap() error: maps->mapDim.width must be multiple of maps->outputBlockDim.width\n");
    return -1;
  }

  if (maps->mapDim.height % height) {
    PRINTF("convertMap() error: maps->mapDim.height must be multiple of maps->outputBlockDim.height\n");
    return -1;
  }

  /* Scan the list of coordinates in srcMap in blockwise fashion
  * to populate dstMapStruct->srcMap[].
  * We implement a 2-pass scan
  * In 1st scan, we just continuously
  * update the coordinates of the input bounding box
  */

  maps->maxInputBlockDim.width= 0;
  maps->maxInputBlockDim.height= 0;
  maps->maxInputBlockSize= 0;
  maps->maxNumPixelsinTile = 0;

  /* Every block's layout pointed by maps->blockMap
  * is as follow:
  * - 9 half-words of information i.e., convertMapBlockInfo:
  *                  - 1st half-word is valid flag 0 or 1: 0 means the block doesn't contain any pixel value and needs to be skipped
  *                  because it falls outside of the input ROI.
  *                  - 2nd half-word contains the inputBlockWidth
  *                  - 3rd half-word contains the inputBlockWidth/2
  *                  - 4th half-word contains the inputBlockHeight
  *                  - 5th and 6th half words contain upper left coordinates of input block
  *                  - 7th and 8th half words contain upper left coordinates of output block
  *                  - 9th half word contain deinterleave register value
  *                  - 16 half words are used as padding to make convertMapBlockInfo as multiple of 32
  * - lookup indexes made of width*height half words. These lookup indexes
  *   are derived from the integer part of the x,y coordinates.
  * - Fractional part of the x coordinates made of width*height bytes
  * - Fractional part of the y coordinates made of width*height bytes
  */
  maps->blockMap = memLUT;
  ptrInfoMap= (convertMapBlockInfo*)maps->blockMap;
  ptrIndexMap= (uint16_t*)(ptrInfoMap + 1);
  ptrfracMap = (uint8_t*)(ptrIndexMap + outputBlockSize);

  blockMapBlockSize= sizeof(convertMapBlockInfo) + 3*outputBlockSize;

  if (stat->collectStatFlag)
  {
    /* Collect statistics on expansion/reduction factor of each block */
    stat->maxWidthRatio= 0;
    stat->minWidthRatio= 10000.0; /* some big number */
    stat->averWidthRatio= 0;

    /* Collect statistics on expansion/reduction factor of each block */
    stat->maxHeightRatio= 0;
    stat->minHeightRatio= 10000.0; /* some big number */
    stat->averHeightRatio= 0;
  }

  for (block_row= 0, out_y=0; block_row < maps->mapDim.height; block_row += height, out_y++)
  {
    for (block_col= 0, out_x=0; block_col < 2*maps->mapDim.width; block_col+= 2*width, out_x++)
    {


      xul= 65535;
      xlr= 0;
      yul= 65535;
      ylr= 0;

      /*
      * In 1st scan, we just continuously
      * update the coordinates of the input bounding box's upper left and lower right corners
      */
      if (maps->isSrcMapFloat) {
        for (r= 0; r < height; r++)
          for (c= 0; c < 2*width; c+=2){ // increment by 2 because each index corresponds to pair (x,y)
            x= (uint16_t)(srcMapFloat[(block_row + r)*2*maps->mapDim.width + block_col + c]);
            y= (uint16_t)(srcMapFloat[(block_row + r)*2*maps->mapDim.width + block_col + c + 1]);
            xul= MIN(x, xul);
            xlr= MAX(x+1, xlr);
            yul= MIN(y, yul);
            ylr= MAX(y+1, ylr);
          }
      }
      else {
        for (r= 0; r < height; r++)
          for (c= 0; c < 2*width; c+=2){ // increment by 2 because each index corresponds to pair (x,y)
            x= (uint16_t)(srcMapU32[(block_row + r)*2*maps->mapDim.width + block_col + c]>>maps->qShift);
            y= (uint16_t)(srcMapU32[(block_row + r)*2*maps->mapDim.width + block_col + c + 1]>>maps->qShift);
            xul= MIN(x, xul);
            xlr= MAX(x+1, xlr);
            yul= MIN(y, yul);
            ylr= MAX(y+1, ylr);
          }
      }

      // If YUV_422ILE or YUV420SP, we want upper left corner to be aligned to even  x coordinate
      // so sequence of chrominance values starts with a u
      if (maps->srcFormat== YUV_422ILE || maps->srcFormat== YUV_422IBE || maps->srcFormat== YUV_420SP) {
        if (xul & 1)
          xul-=1;
        if (maps->srcFormat== YUV_420SP)
          if (yul & 1)
            yul-=1;
      }

      inputBlockWidth= xlr - xul + 1;
      inputBlockHeight= ylr - yul + 1;

      // In case source format has chrominance, we need to round up the input block width
      // so we can interpolate the color as well.
      if (maps->srcFormat== YUV_422ILE || maps->srcFormat== YUV_422IBE || maps->srcFormat== YUV_420SP) {
        inputBlockWidth  = (inputBlockWidth + 3 ) & 0xFFFE;
        inputBlockHeight = (inputBlockHeight + 3 ) & 0xFFFE;
      }

      blockSize= inputBlockWidth*inputBlockHeight;
      // We want maps->maxInputBlockSize to be multiple of 16 so we can easily later divide it
      // into 2 component maxInputBlockWidth multiple of 4.
      maps->maxInputBlockSize= ((MAX(maps->maxInputBlockSize, blockSize) + 15) >> 4) << 4;
      maps->maxInputBlockDim.width= MAX(maps->maxInputBlockDim.width, inputBlockWidth);
      maps->maxInputBlockDim.height= MAX(maps->maxInputBlockDim.height, inputBlockHeight);

#ifdef DEBUG
      if (maps->maxInputBlockSize > maxSupportedBlockSize) {
          PRINTF("convertMap() error: one input block has dimensions exceeding internal memory of coprocessor. Please reduce outputBlockDim.width or outputBlockDim.height\n");
          PRINTF("convertMap() error: Issue seen for block_col = %d, block_row = %d\n", block_col/(2*width), block_row/height);
          return -1;
        }
#endif
        if (stat->collectStatFlag) {
          float ratioW, ratioH;

          ratioW= (float)inputBlockWidth / width;
          if (ratioW > stat->maxWidthRatio)
            stat->maxWidthRatio= ratioW;
          else if (ratioW < stat->minWidthRatio)
            stat->minWidthRatio= ratioW;

          stat->averWidthRatio+= ratioW;

          ratioH= (float)inputBlockHeight / height;
          if (ratioH > stat->maxHeightRatio)
            stat->maxHeightRatio= ratioH;
          else if (ratioH < stat->minHeightRatio)
            stat->minHeightRatio= ratioH;

          stat->averHeightRatio+= ratioH;
          /*
          if (ratioW > 2.0 || ratioH > 2.0)
          PRINTF("Block %d,%d: inputWidth=%3.2f x %d, inputHeight= %3.2f x %d\n", out_x, out_y, ratioW, width, ratioH, height);
          */
        }

        ptrInfoMap->inputBlockWidth= (uint16_t)inputBlockWidth;
        ptrInfoMap->inputBlockWidthDiv2= ptrInfoMap->inputBlockWidth/2;
        /* ceil((1<<16)/inputBlockWidth) is done as inputBlockWidth not being a divisor of
                   2^16 leads to quantization error. It matters during TLUchroma calculation.
                   TLUluma = i + j*src_stride. In cases when i = 0, TLUchroma computation results in chroma-i = stride and
                   chroma-j = j-1. This along with the offset calculation based on i,j being odd/even creates a problem.
                   To avoid this, ceil is done. ceil has it's own limitations. For inputBlockWidth values >=56, quantization
                   issues are observed for i = inputBlockWidth - 1. But since we are padding the input block by
                   inputBlockWidth  = (inputBlockWidth + 3 ) & 0xFFFE, i will never be inputBlockWidth - 1. Hence this is not
                   a problem. */
        ptrInfoMap->inputBlockWidthQ16 = (uint16_t)(((1<<16) + inputBlockWidth-1)/inputBlockWidth);
        ptrInfoMap->inputBlockHeight= (uint16_t)inputBlockHeight;
        ptrInfoMap->inBlock_x= xul;
        ptrInfoMap->inBlock_y= yul;

        /*
        * Now that we got the coordinates of the bounding box, we can generate
        * the indexes/fractional parts from the coordinates
        */
        if (maps->isSrcMapFloat) {
          for (r= 0; r < height; r++)
            for (c= 0; c < width; c++){
              float_x= srcMapFloat[(block_row + r)*2*maps->mapDim.width + block_col + 2*c];
              x= (uint16_t)float_x;
              frac_x= (uint16_t)convertMap_round((float_x - x)*(1<<maps->qShift));
              float_y= srcMapFloat[(block_row + r)*2*maps->mapDim.width + block_col + 2*c + 1];
              y= (uint16_t)float_y;
              frac_y= (uint16_t)convertMap_round((float_y - y)*(1<<maps->qShift));

              tluIndex= ((x - xul) + (y - yul)*inputBlockWidth);

              *(ptrIndexMap++)= (tluIndex);
              *(ptrfracMap++)= ((frac_y << NUM_FRAC_BITS) | (frac_x));
            }

        }
        else {
          uint32_t U32_x, U32_y;

          for (r= 0; r < height; r++)
            for (c= 0; c < width; c++){
              U32_x= srcMapU32[(block_row + r)*2*maps->mapDim.width + block_col + 2*c];
              x= (uint16_t)(U32_x>>maps->qShift);
              frac_x= (uint16_t)(U32_x - (x<<maps->qShift));
              U32_y= srcMapU32[(block_row + r)*2*maps->mapDim.width + block_col + 2*c + 1];
              y= (uint16_t)(U32_y>>maps->qShift);
              frac_y= (uint16_t)(U32_y - (y<<maps->qShift));

              tluIndex= ((x - xul) + (y - yul)*inputBlockWidth);

              *(ptrIndexMap++)= (tluIndex);
              *(ptrfracMap++)= ((frac_y << NUM_FRAC_BITS) | (frac_x));
            }
        }

        ptrInfoMap= (convertMapBlockInfo*)((uint8_t*)ptrInfoMap + blockMapBlockSize);
        ptrIndexMap= (uint16_t*)(ptrInfoMap + 1);
        ptrfracMap = (uint8_t*)(ptrIndexMap + outputBlockSize);
      }
    }

  if (stat->collectStatFlag) {
    stat->averWidthRatio/=out_x*out_y;
    stat->averHeightRatio/=out_x*out_y;
  }

  return 0;
}

