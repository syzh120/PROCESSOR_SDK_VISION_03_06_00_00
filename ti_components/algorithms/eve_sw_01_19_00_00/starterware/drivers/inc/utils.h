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


#ifndef UTILS_H
#define UTILS_H
/**
* @brief   RD_MEM_8, WR_MEM_8
*
* @brief        8 bit memory access macros
*
*
*/
#define RD_MEM_8(addr)	((UWORD8)(*((UWORD8 *)(addr))))                      /**< 8 bit read memory */
#define WR_MEM_8(addr, data)	(*((UWORD8 *)(addr)) = (UWORD8)(data))       /**< 8 bit write memory */

/**
* @brief   RD_MEM_16, WR_MEM_16
*
* @brief        16 bit memory access macros
*
*
*/
#define RD_MEM_16(addr)	((UWORD16)(*((UWORD16 *)(addr))))                        /**< 16 bit read memory */
#define WR_MEM_16(addr, data)	(*((UWORD16 *)(addr)) = (UWORD16)(data))         /**< 16 bit write memory */

/**
* @brief   RD_MEM_32, WR_MEM_32
*
* @brief        32 bit memory access macros
*
*
*/
#define RD_MEM_32(addr)	((UWORD32)(*((UWORD32 *)(addr))))                        /**< 32 bit read memory */
#define WR_MEM_32(addr, data)	(*((UWORD32 *)(addr)) = (UWORD32)(data))         /**< 32 bit write memory */

/**
* @brief   RD_MEM_64, WR_MEM_64
*
* @brief        64 bit memory access macros
*
*
*/
#define RD_MEM_64(addr)	((UWORD64)(*((UWORD64 *)(addr))))                          /**< 64 bit read memory */
#define WR_MEM_64(addr, data)	(*((UWORD64 *)(addr)) = (UWORD64)(data))           /**< 64 bit write memory */

#endif /*UTILS_H*/

