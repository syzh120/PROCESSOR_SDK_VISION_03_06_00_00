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

#include "VXLIB_fastCornersNMS_i8u_cn.h"

CODE_SECTION(VXLIB_fastCornersNMS_i8u_cn,              ".text:ansi")
CODE_SECTION(VXLIB_fastCornersNMS_i8u_checkParams_cn,  ".text:ansi")

static uint8_t VXLIB_GetFastCornerStrengthList(int32_t curRow, int32_t x, int32_t y, const uint16_t corners[],
                                                 const uint8_t strengths[], uint32_t num_corners)
{
    static int32_t start = 0;
    static int32_t curRow_d = 0xFFFF;
    int32_t i;

    if(curRow < curRow_d) {
        start = 0;
    }
    curRow_d = curRow;

    for(i=start; i < num_corners; i++) {
        uint16_t yi = corners[i*2+1];
        uint16_t xi = corners[i*2];

        if(yi < (curRow-1))
            start = i;
        
        if(yi < y)
            continue;

        if((xi == x) && (yi == y)) {
            return strengths[i];
        }

        if(yi > y)
            break;
    }
    return 0;
}

VXLIB_STATUS VXLIB_fastCornersNMS_i8u_cn(const uint16_t corners_in[],
                                      const uint8_t strengths_in[],
                                      uint32_t num_corners_in,
                                      uint16_t corners_out[],
                                      uint8_t strengths_out[],
                                      uint32_t *num_corners_out)
{
    uint32_t        x, y, i;
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_fastCornersNMS_i8u_checkParams_cn(corners_in, strengths_in, num_corners_in, corners_out, strengths_out, num_corners_out);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t outNum = 0;
        for( i = 0; i < num_corners_in; i++ ) {
            x = corners_in[i*2+0];
            y = corners_in[i*2+1];
            if( (strengths_in[i] >= VXLIB_GetFastCornerStrengthList(y, x - 1, y - 1, corners_in, strengths_in, num_corners_in)) &&
                (strengths_in[i] >= VXLIB_GetFastCornerStrengthList(y, x, y - 1, corners_in, strengths_in, num_corners_in)) &&
                (strengths_in[i] >= VXLIB_GetFastCornerStrengthList(y, x + 1, y - 1, corners_in, strengths_in, num_corners_in)) &&
                (strengths_in[i] >= VXLIB_GetFastCornerStrengthList(y, x - 1, y, corners_in, strengths_in, num_corners_in)) &&
                (strengths_in[i] > VXLIB_GetFastCornerStrengthList(y, x + 1, y, corners_in, strengths_in, num_corners_in)) &&
                (strengths_in[i] > VXLIB_GetFastCornerStrengthList(y, x - 1, y + 1, corners_in, strengths_in, num_corners_in)) &&
                (strengths_in[i] > VXLIB_GetFastCornerStrengthList(y, x, y + 1, corners_in, strengths_in, num_corners_in)) &&
                (strengths_in[i] > VXLIB_GetFastCornerStrengthList(y, x + 1, y + 1, corners_in, strengths_in, num_corners_in)))
            {
                corners_out[outNum*2+0] = x;
                corners_out[outNum*2+1] = y;
                strengths_out[outNum] = strengths_in[i];
                outNum++;
            }
        }
        *num_corners_out = outNum;
    }
    return (status);
}

VXLIB_STATUS VXLIB_fastCornersNMS_i8u_checkParams_cn(const uint16_t corners_in[],
                                                  const uint8_t strengths_in[],
                                                  uint32_t num_corners_in,
                                                  uint16_t corners_out[],
                                                  uint8_t strengths_out[],
                                                  uint32_t *num_corners_out)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((corners_in == NULL) || (strengths_in == NULL) || (corners_out == NULL) || (strengths_out == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    }
    return (status);
}

