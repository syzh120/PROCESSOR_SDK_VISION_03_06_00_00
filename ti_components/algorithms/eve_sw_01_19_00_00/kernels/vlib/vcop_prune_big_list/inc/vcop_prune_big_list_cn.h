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

/*                                                                          */
/*     @file : vcop_prune_big_list_cn.h                                     */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*         function for pruning an input list based on sorted index array.  */
/*                                                                          */
/*     vcop_prune_big_list_cn                                               */
/*         This is the C-reference for the vcop_prune_big_list kernel.      */
/*         This routine accepts an input list and a sorted array of         */
/*         indices. The outputs is a pruned list of 'bestN' elements from   */
/*         input based on the ordering in the index list provided.          */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_prune_big_list_cn                                          */
/*     (                                                                    */
/*         uint32_t *inList,                                                */
/*         uint16_t *inSortedIndexList,                                     */
/*         uint32_t *outList,                                               */
/*         uint16_t  bestN                                                  */
/*     )                                                                    */
/*                                                                          */
/*     inList            : Input list to be pruned                          */
/*     inSortedIndexList : List of sorted indexes. The index list is        */
/*                         expected to be a of 32-bit with the lower 16-bit */
/*                         representing the index.                          */
/*     outList           : Pruned and packed output list                    */
/*     bestN             : Number of elements expected to be available in   */
/*                         the output list.                                 */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @version 1.0 (Nov 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_PRUNE_BIG_LIST_CN
#define _VCOP_PRUNE_BIG_LIST_CN

void vcop_prune_big_list_cn
(
    uint32_t *inList,
    uint16_t *inSortedIndexList,
    uint32_t *inSortedIndexList32,
    uint32_t *outList,
    uint32_t *nonBestNSize,
    uint16_t  threshold,
    uint16_t  bestN
);

#endif /* _VCOP_PRUNE_BIG_LIST_CN */
