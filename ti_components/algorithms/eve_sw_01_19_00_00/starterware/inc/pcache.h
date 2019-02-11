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
*  @file       pcache.h
*
*  @brief      The program cache library component offers basic interface apis
*              to the cache
*
*  This header provides basic apis to invalidate or prefetch program cache
*
*/
#ifndef PCACHE_H
#define PCACHE_H

#include "GlobalTypes.h"

#ifdef __cplusplus
extern  "C"
{
#endif

/* ------------------------------------------------------------------------*//**
 * @brief          EVE_PROGCACHE_BlockInvalidate
 *
 * @brief       Invalidate the block of data in program cache
 *
 * @brief   CRED_index_t - cred module Identifier
 * @brief   UWORD32 * - address
 * @brief   UWORD32   - size
 *
 * @return      Void
 *
 * @details     Invalidates the block as specified by address and size
 *              in program cache
 *
 * @remarks      -
 *
 *//*------------------------------------------------------------------------ */
void EVE_PROGCACHE_BlockInvalidate (CRED_index_t component, const UWORD32 *address, UWORD32 num_bytes);
/* ------------------------------------------------------------------------*//**
 * @brief          EVE_PROGCACHE_GlobalInvalidate
 *
 * @brief       Invalidate the program cache globally
 *
 * @brief   CRED_index_t - cred module Identifier
 *
 * @return      Void
 *
 * @details     Invalidates the program cache globally
 *
 * @remarks      -
 *
 *//*------------------------------------------------------------------------ */
void EVE_PROGCACHE_GlobalInvalidate(CRED_index_t component);
/* ------------------------------------------------------------------------*//**
 * @brief          EVE_PROGCACHE_Prefetch
 *
 * @brief       Prefetch the block of data into program cache
 *
 * @brief   CRED_index_t - cred module Identifier
 * @brief   UWORD32 * - address
 * @brief   UWORD32   - size
 *
 * @return      Void
 *
 * @details     Prefetch the block as specified by address and size in
 *              to program cache
 *
 * @remarks      -
 *
 *//*------------------------------------------------------------------------ */
void EVE_PROGCACHE_Prefetch (CRED_index_t component, const UWORD32 *addr, UWORD32 sizePrefetch);

#ifdef __cplusplus
}
#endif
#endif	/* PCACHE_H */
/* EOF */




