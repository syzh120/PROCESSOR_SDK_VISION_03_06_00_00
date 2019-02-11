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


#pragma CHECK_MISRA ("none")
#include <stdint.h>
#include <string.h>
#pragma RESET_MISRA ("required")

#include "eve_edma_scatter_gather.h"

EVELIB_EDMAScatterGatherErr  EVELIB_EDMAScatterGatherInit( int32_t            numTransfers,      /**< Number of Transfers required */
                                                        uint32_t              index,      /**< Index In resource structure, this indicates In or Out transfers*/
                                                        uint32_t              blkWidth,          /**< Width of the Block in int. memory (in bytes)*/
                                                        uint32_t              blkHeight,     /**< Height of the Block in int. memory */
                                                        int16_t               srcStride,     /**< Stride of Source buffer (in bytes)*/
                                                        int16_t               dstStride,     /**< Stride of Destination buffer (in bytes)*/
                                                        DMA_resourceStruct   *edmaResources,
                                                        CSL_EdmaccRegsOvly    edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                                        )
{
    EVELIB_EDMAScatterGatherErr status = EVELIB_EDMASCATTERGATHER_ERR_SUCCESS;

    if(numTransfers < 0 && numTransfers > MAX_SCATTERGATHER_TRANSFERS)
    {
        status = EVELIB_EDMASCATTERGATHER_ERR_CROSSED_MAX_TRANSFERS;
    }

    if(status == EVELIB_EDMASCATTERGATHER_ERR_SUCCESS)
    {
        volatile uint32_t   *trigParam = 0;
        uint32_t            paramChan = 0;
        uint32_t            linkAddr = 0;
        uint32_t            linkAddr2nd = 0;
        uint32_t            j = 0;

        uint32_t            itccEn = 0;
        uint32_t            tccEn = 0;
        uint32_t            itcintEn = 0;
        uint32_t            tcintEn = 0;
        uint32_t            tccMode = 0;
        uint32_t            fwid = 0;
        uint32_t            stat = 0;
        uint32_t            syncDim = 0;
        uint32_t            dam = 0;
        uint32_t            sam = 0;

        uint32_t            evtNo = 0;
        uint32_t            optLinkChain = 0;
        uint32_t            optNormal = 0;

        /*---------------------------------------------------------------*/
        /*  Write up the values of the PARAM in internal memory. We      */
        /*  have to prepare the options field once, upfront, to use      */
        /*  ASYNC, transfer complete chaining enable, transfer compl.    */
        /*  interrupt disable, evt_no for chaining in CER, early         */
        /*  completion, entry is updated as normal. SRC and DST are      */
        /*  set in increment mode. Read the param no, for this chan.     */
        /*  and figure out link address by adding 32 bytes or 1 PARAM.   */
        /*---------------------------------------------------------------*/

        paramChan  = (uint32_t) edmaResources->baseParam[index];

        linkAddr2nd = linkAddr   =  (numTransfers > 1)?(paramChan + 32):0xFFFF;

        itccEn     =  CSL_EDMACC_OPT_ITCCHEN_DISABLE;
        tccEn      =  CSL_EDMACC_OPT_TCCHEN_ENABLE;
        itcintEn   =  CSL_EDMACC_OPT_ITCINTEN_DISABLE;
        tcintEn    =  CSL_EDMACC_OPT_TCINTEN_DISABLE;
        evtNo      =  edmaResources->logicalChannelNo[index];
        tccMode    =  CSL_EDMACC_OPT_TCCMODE_EARLY;
        fwid       =  CSL_EDMACC_OPT_FWID_8;
        stat       =  CSL_EDMACC_OPT_STATIC_NORMAL;
        syncDim    =  CSL_EDMACC_OPT_SYNCDIM_ABSYNC;
        dam        =  CSL_EDMACC_OPT_DAM_INCR;
        sam        =  CSL_EDMACC_OPT_SAM_INCR;

        /*---------------------------------------------------------------*/
        /*  Now prepare options for 1D -> 1D with linking and chaining.  */
        /*---------------------------------------------------------------*/

        optLinkChain  = CSL_EDMA_OPT_MAKE
                        (itccEn,tccEn,itcintEn,tcintEn,evtNo,tccMode,fwid,stat,syncDim,dam,sam);

        /* modify opt word for the last transfer */
        tccEn      =  CSL_EDMACC_OPT_TCCHEN_DISABLE;
        tccMode    =  CSL_EDMACC_OPT_TCCMODE_NORMAL;
        stat       =  CSL_EDMACC_OPT_STATIC_STATIC;
        tcintEn    =  CSL_EDMACC_OPT_TCINTEN_ENABLE;

        optNormal  = CSL_EDMA_OPT_MAKE
                     (itccEn,tccEn,itcintEn,tcintEn,evtNo,tccMode,fwid,stat,syncDim,dam,sam);
        /*---------------------------------------------------------------*/
        /*  We want to do numTransfers linked transfers, we setup a loop. Keep      */
        /*  incrementing the link_address by 32 bytes. Pack src and      */
        /*  dst addresses along with num_bytes.                          */
        /*---------------------------------------------------------------*/

        trigParam       =    edmaResources->baseParam[index];

        for (j = 0; j <numTransfers*8; j+= 8)
        {
            memset((void*)&trigParam[j], 0, sizeof(uint32_t)*8);
            linkAddr &= 0xFFFF;

            trigParam[j + 0]  = (uint32_t) (optLinkChain);
            trigParam[j + 1]  = (uint32_t)0;
            trigParam[j + 2]  = pack2(blkHeight, blkWidth);
            trigParam[j + 3]  = (uint32_t)0;
            trigParam[j + 4]  = pack2(dstStride, srcStride);
            trigParam[j + 5]  = pack2(blkHeight, linkAddr);
            trigParam[j + 6]  = (0x0 << 16) | (0x0);
            trigParam[j + 7]  =  0x1;

            linkAddr  += 32;
        }

        /*---------------------------------------------------------------*/
        /*  Back up loop counter by 8. This will be used for fixing      */
        /*  last param.                                                  */
        /*---------------------------------------------------------------*/

        j -= 8;

        /*---------------------------------------------------------------*/
        /*  Set the link address for the last transfer to terminate.     */
        /*  Always set the last link to post completion. It is assumed   */
        /*  that the last link will always use the TCC allocated for     */
        /*  the channel as a whole irrespective of what the user         */
        /*  passes. Fix up options field.                                */
        /*---------------------------------------------------------------*/

        trigParam[j + 0] = optNormal;
        trigParam[j + 5] = pack2(blkHeight, 0xFFFF & linkAddr2nd);
    }
    return status;
}

EVELIB_EDMAScatterGatherErr  EVELIB_EDMAScatterGatherDeInit(DMA_resourceStruct *edmaResources,         /**< EDMA state structure */
                                                 CSL_EdmaccRegsOvly    edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                                 )
{
    EVELIB_EDMAScatterGatherErr status = EVELIB_EDMASCATTERGATHER_ERR_SUCCESS;

    return status;
}
