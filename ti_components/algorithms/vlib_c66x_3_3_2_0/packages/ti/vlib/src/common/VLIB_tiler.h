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
**|        Copyright (c) 2007 - 2015 Texas Instruments Incorporated          |**
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

#ifndef VLIB_TILER_H_
#define VLIB_TILER_H_ 1

#include "VLIB_types.h"

/**
 *  @enum eTileTypes_t
 *  @brief  This enum defines the data type of the flags parameter in the sBuffer_t
 *
 *  @param TILE_TYPE_8U   Unsigned 8 bit
 *  @param TILE_TYPE_8S   Signed 8 bit
 *  @param TILE_TYPE_16U  Unsigned 16 bit
 *  @param TILE_TYPE_16S  Signed 16 bit
 *  @param TILE_TYPE_32U  Unsigned 32 bit
 *  @param TILE_TYPE_32S  Signed 32 bit
 *  @param TILE_TYPE_32F  Floating point 32 bit
 *  @param TILE_TYPE_64F  Floating point 64 bit
 *  @param TILE_TYPE_MAX  Max enumeration
 */
typedef enum {
    TILE_TYPE_8U  = 0,      /*!< Unsigned 8 bit */
    TILE_TYPE_8S  = 1,      /*!< Signed 8 bit */
    TILE_TYPE_16U = 2,      /*!< Unsigned 16 bit */
    TILE_TYPE_16S = 3,      /*!< Signed 16 bit */
    TILE_TYPE_32U = 4,      /*!< Unsigned 32 bit */
    TILE_TYPE_32S = 5,      /*!< Signed 32 bit */
    TILE_TYPE_32F = 6,      /*!< Floating point 32 bit */
    TILE_TYPE_64F = 7,      /*!< Floating point 64 bit */
    TILE_TYPE_MAX = 8       /*!< Max enumeration */

}eTileTypes_t;

#define TILE_TYPE_BIT_POS    (uint32_t)(0)
#define TILE_TYPE_BIT_LENGTH (uint32_t)(4)
#define TILE_TYPE_BIT_MASK   (uint32_t)(0x000F)

#define TILE_CH_BIT_POS      (TILE_TYPE_BIT_POS + TILE_TYPE_BIT_LENGTH)
#define TILE_CH_BIT_LENGTH   (9)
#define TILE_CH_BIT_MASK     (uint32_t)(0x01FF)

#define TILE_CONTIGUOUS_BIT_POS (TILE_CH_BIT_POS + TILE_CH_BIT_LENGTH)
#define TILE_CONTIGUOUS_BIT_LENGTH (1)
#define TILE_CONTIGUOUS_BIT_MASK   (0x0001)

#define SET_TILE_TYPE(flag, type) \
    {\
        uint32_t    bits = (1 << TILE_TYPE_BIT_LENGTH) - 1;\
        uint32_t    mask  = ~(bits << TILE_TYPE_BIT_POS);\
        flag = flag & mask;\
        flag = flag | (type << TILE_TYPE_BIT_POS);\
    }

#define SET_TILE_CH(flag, ch) \
    {\
        uint32_t    bits = (1 << TILE_CH_BIT_LENGTH) - 1;\
        uint32_t    mask  = ~(bits << TILE_CH_BIT_POS);\
        flag = flag & mask;\
        flag = flag | (ch << TILE_CH_BIT_POS);\
    }

#define SET_TILE_CONTIGUOUS(flag, contiguous) \
    {\
        uint32_t    bits = (1 << TILE_CONTIGUOUS_BIT_LENGTH) - 1;\
        uint32_t    mask  = ~(bits << TILE_CONTIGUOUS_BIT_POS);\
        flag = flag & mask;\
        flag = flag | (contiguous << TILE_CONTIGUOUS_BIT_POS);\
    }

#define GET_TILE_TYPE(flag, type) \
    {\
        type = (flag >> TILE_TYPE_BIT_POS) & TILE_TYPE_BIT_MASK;\
    }

#define GET_TILE_CH(flag, ch) \
    {\
        ch = (flag >> TILE_CH_BIT_POS) & TILE_CH_BIT_MASK;\
    }

#define GET_TILE_CONTIGUOUS(flag, contiguous) \
    {\
        contiguous = (flag >> TILE_CONTIGUOUS_BIT_POS) & TILE_CONTIGUOUS_BIT_MASK;\
    }

/**
 *  @struct sBuffer_t
 *  @brief  Container which holds a buffer pointer and its associated memory layout information
 *          for each buffer used in functions which end in "_tile"
 *
 *  @param data   Pointer to the data buffer
 *  @param rows   Number of rows in the buffer
 *  @param cols   Number of columns in the buffer
 *  @param pitch  Number of elements between the start of each row in the buffer
 *  @param flags  Contains information about tile type, channel number, and continous flag (can be
                  independently set and retreived using macros)
*/
typedef struct {
    void    *data;      /*!< Pointer to the data buffer */
    int32_t  rows;      /*!< Number of rows in the buffer */
    int32_t  cols;      /*!< Number of columns in the buffer */
    int32_t  pitch;     /*!< Number of elements between the start of each row in the buffer */
    uint32_t flags;     /*!< Contains information about tile type, channel number, and continous flag */

}sBuffer_t;

#endif  /* VLIB_TILER_H_ */

/* =========================================================================*/
/*  End of file:  VLIB_tiler.h                                              */
/* =========================================================================*/

