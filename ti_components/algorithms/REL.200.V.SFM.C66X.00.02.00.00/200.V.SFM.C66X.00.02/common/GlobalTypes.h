/*
*
* Copyright (c) 2003-2017 Texas Instruments Incorporated
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
*  @file       globaltypes.h
*
*  @brief      Error types and some data types needed by starterware
*
*
*/
#ifndef GLOBALTYPES_H
#define GLOBALTYPES_H

/* ============================================================================
* INCLUDE FILES (only if necessary)
* =============================================================================
*/
/*#pragma CHECK_MISRA ("none")*/
#include <stddef.h>
#include <stdint.h>

#ifndef HOST_EMULATION
#include <stdbool.h>
#endif

#include <string.h>
/*#pragma RESET_MISRA ("required")*/
#ifdef __cplusplus
extern "C"
{
#endif


/**
*
* @brief        ReturnCode_t, *pReturnCode_t : Return codes to be returned by all library functions
*
*
*/
typedef enum ReturnCode_label {
    RET_OK = 0,                 /**< pass */
    RET_FAIL,                   /**< fail */
    RET_BAD_NULL_PARAM,         /**< bad null parameter */
    RET_PARAM_OUT_OF_RANGE,     /**< parameter is out of range */
    RET_INVALID_ID,             /**< invalid id */
    RET_EMPTY,                  /**< empty */
    RET_FULL,                   /**< full */
    RET_TIMEOUT,                /**< timed out */
    RET_INVALID_OPERATION,      /**< invalid operation */

    /* Beach register tests return codes */
    RET_POR_FAIL,               /* Power on reset fail */
    RET_READ_INTEG_FAIL,        /* Read Integrity fail  */
    RET_READ_ONLY_FAIL,         /* Read only fail */
    RET_WRTIE_ONLY_FAIL,        /* Write only fail */
    RET_RE_UP_FAIL,             /* Read exclusivity Up fail */
    RET_RE_DOWN_FAIL,           /* Read exclusivity Down fail */
    RET_BUSY,

    /* Add new error codes at end of above list */

    RET_NUM_RET_CODES     /* this should ALWAYS be LAST entry */
} ReturnCode_t, *pReturnCode_t;                    /**< ReturnCode_t, *pReturnCode_t */


/* Boolean  Definition */
/**
*
* @brief        Boolean Type True, False
*
*
*/
#ifndef BOOL_FLAG
    #define BOOL_FLAG
#ifndef HOST_EMULATION
    typedef  _Bool BOOL;
#else
    typedef  unsigned char BOOL;
#endif
#endif

/*-------------------------------------------------------------------------*//**
 * @TYPE  UWORD8
 *
 * @BRIEF unsigned byte type
 *//*------------------------------------------------------------------------ */
#ifndef UWORD8_FLAG
  #define UWORD8_FLAG
  typedef     uint8_t   UWORD8;
  #endif

#ifndef WORD8_FLAG
  #define WORD8_FLAG
typedef     int8_t    WORD8;
#endif

#ifndef UWORD16_FLAG
  #define UWORD16_FLAG
typedef    uint16_t  UWORD16 ;
#endif

#ifndef WORD16_FLAG
  #define WORD16_FLAG
typedef    int16_t    WORD16;
#endif

#ifndef UWORD32_FLAG
  #define UWORD32_FLAG
typedef   uint32_t  UWORD32;
#endif

#ifndef WORD32_FLAG
  #define WORD32_FLAG
typedef   int32_t    WORD32;
#endif

#ifndef UCHAR_FLAG
  #define UCHAR_FLAG
typedef   uint8_t    UCHAR;
#endif

/**
  * @brief REG_UWORD8, REG_WORD8
  *
  * @brief       8 bit register types.
  *
  *
  */
#ifndef REG_UWORD8_FLAG
  #define REG_UWORD8_FLAG                             /**< REG_UWORD8 flag */
  typedef volatile uint8_t REG_UWORD8;          /**< REG_UWORD8 */
#endif

  typedef volatile int8_t  REG_WORD8;          /**< REG_WORD8 */

  /**
  * @brief REG_UWORD16, REG_WORD16
  *
  * @brief       16 bit register types.
  *
  *
  */
#ifndef REG_UWORD16_FLAG
  #define REG_UWORD16_FLAG                             /**< REG_UWORD16 flag */
  typedef volatile uint16_t REG_UWORD16;         /**< REG_UWORD16 */
#endif

  typedef volatile    uint16_t REG_WORD16;          /**< REG_WORD16 */

  /**
  * @brief REG_UWORD32, REG_WORD32
  *
  * @brief       32 bit register types.
  *
  *
  */
#ifndef REG_UWORD32_FLAG
  #define REG_UWORD32_FLAG                             /**< REG_UWORD32 flag */
  typedef volatile uint32_t  REG_UWORD32;          /**< REG_UWORD32 */
#endif

#ifndef REG_WORD32_FLAG
  #define REG_WORD32_FLAG                               /**< REG_WORD32 flag*/
  typedef volatile          int32_t  REG_WORD32;            /**< REG_WORD32 */
#endif



#ifdef __cplusplus
}
#endif
#endif  /* GLOBALTYPES_H */
