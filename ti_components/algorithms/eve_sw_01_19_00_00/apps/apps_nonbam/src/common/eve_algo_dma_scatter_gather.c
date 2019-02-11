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


/*-----------------------------------------------------------------------*/
/*  NAME : algo_dma_scatter_gather.c                                     */
/*                                                                       */
/*  DESCRIPTION:                                                         */
/*                                                                       */
/*  This file demonstrates double buffering of data from external ->     */
/*  internal memory, and internal -> external memory on an image frame.  */
/*  Data from the image frame is transferred to internal memory on a     */
/*  block by block basis.                                                */
/*                                                                       */
/*  2D -> 1D transfers are used for incoming data and 1D -> 2D transfers */
/*  are used for outgoing data. Two parameter registers are used, 1 for  */
/*  the incoming ping/pong buffers and 1 for the outgoing ping/pong      */
/*  buffers.                                                             */
/*                                                                       */
/*  Autoincrementing at each DMA block transfer completion is used to    */
/*  to reduce the number of times entries in the parameter ram need to   */
/*  be updated. At the end of each block-row, the src and dst pointers   */
/*  are updated in the parameter ram to reflect the starting addresses   */
/*  of the next row of blocks.                                           */
/*=======================================================================*/
/*  Texas Instruments incorporated 2012.                                 */
/*-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <vcop/vcop.h>
#include <arp32.h>

/*-----------------------------------------------------------------------*/
/*  These are the include files that are needed for edma/qdma.           */
/*-----------------------------------------------------------------------*/
#include "evestarterware.h"
#include "dma_funcs.h"
#include "dma_resource_allocator.h"
#include "edma_utils.h"

#include "eve_algo_dma_scatter_gather.h"
#include "eve_edma_scatter_gather.h"


#define AETCTL_OFFSET (0x0700)
#define SCATTER_GATHER_NUM_CHANNEL  0x2u
/* --------------------------------------------------------------------- */
/*  Start of the main test_harness code.                                 */
/* --------------------------------------------------------------------- */
int EVELIB_algoDMAScatterGatherInit(
    DMA_resourceStruct  *edmaResources,
    CSL_EdmaccRegsOvly  edmaCc,
    int                 numTransfersIn,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    int                 numTransfersOut,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    int                 srcBlkPitch,
    unsigned int        dstBlkWidth,
    unsigned int        dstBlkHeight,
    int                 dstBlkPitch,
    unsigned int        srcBlkPadX,
    unsigned int        srcBlkPadY)
{
    unsigned int        indexIn     = 0;
    unsigned int        indexOut    = 1;
    DMA_chanAttr        dmaAttr = (DMA_chanAttr)0;
    uint32_t            numChannels = 0;
    int                 status = 0;


    VCOP_SET_MEM_VIEW (ALIAS_128K_VIEW);
    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);
    vcop_setview(VCOP_MEMALIASED);

    memset(edmaResources, 0 , sizeof (DMA_resourceStruct));

    /* ------------------------------------------------------------------ */
    /* Configure channel for EDMA transfer. We will use two channels, one */
    /* for the input transfer and one for the output transfer.            */
    /* ------------------------------------------------------------------ */
    dmaAttr       =       DMA_CHAN_ATTR_EDMA;
    numChannels   =       SCATTER_GATHER_NUM_CHANNEL;

    /* ------------------------------------------------------------- */
    /* Number of PaRAMs per channel                                  */
    /* ------------------------------------------------------------- */

    edmaResources->numChannels           = numChannels;
    edmaResources->numParam[indexIn]     = numTransfersIn;
    edmaResources->dmaAttr[indexIn]      = dmaAttr;
    edmaResources->queNo[indexIn]        = 0;

    edmaResources->numParam[indexOut]     = numTransfersOut;
    edmaResources->dmaAttr[indexOut]      = dmaAttr;
    edmaResources->queNo[indexOut]        = 0;


    DMA_resourceAllocator_initResources();
    EDMA_UTILS_globalReset();

    status = DMA_resourceAllocator_allocateResources(edmaCc, edmaResources);

    if ( status == 0 )
    {

        /*---------------------------------------------------------------*/
        /*  Re-program hardware registers to accomplish the transfer       */
        /*  settings user has asked for.                                 */
        /*---------------------------------------------------------------*/
        status = DMA_funcs_hardwareRegSetup(edmaCc, edmaResources);
        if ( status == 0 )
        {
            EVELIB_EDMAScatterGatherInit(numTransfersIn,      /**< Number of Transfers required */
                                    indexIn,      /**< HW ID of EDMA channels to be used*/
                                    srcBlkWidth+srcBlkPadX,          /**< Width of the Block in int. memory (in bytes)*/
                                    srcBlkHeight+srcBlkPadY,     /**< Height of the Block in int. memory */
                                    srcImagePitch,     /**< Stride of Source buffer (in bytes)*/
                                    srcBlkPitch,     /**< Stride of Destination buffer (in bytes)*/
                                    edmaResources,       /**< EDMA resource structure */
                                    edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                    );

            EVELIB_EDMAScatterGatherInit(numTransfersOut,      /**< Number of Transfers required */
                                        indexOut,      /**< HW ID of EDMA channels to be used*/
                                        dstBlkWidth,          /**< Width of the Block in int. memory (in bytes)*/
                                        dstBlkHeight,     /**< Height of the Block in int. memory */
                                        dstBlkPitch,     /**< Stride of Destination buffer (in bytes)*/
                                        dstImagePitch,     /**< Stride of Source buffer (in bytes)*/
                                        edmaResources,       /**< EDMA resource structure */
                                        edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                        );
        }

    }

    return status;
}


void EVELIB_algoDMAScatterGatherDeInit(
    DMA_resourceStruct  * edmaResources,
    CSL_EdmaccRegsOvly  edmaCc
    )
{
    DMA_resourceAllocator_deallocateResources(edmaCc,edmaResources);
}



void EVELIB_algoDMAScatterGatherProcessConcurrent
(
    DMA_resourceStruct *edmaResources,
    CSL_EdmaccRegsOvly  edmaCc,
    unsigned char       **srcPtrList,
    int                 numTransfersIn,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    unsigned char       **dstPtrList,
    int                 numTransfersOut,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    unsigned char       **srcBlkPtrList,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    int                 srcBlkPitch,
    unsigned char       **dstBlkPtrList,
    unsigned int        dstBlkWidth,
    unsigned int        dstBlkHeight,
    int                 dstBlkPitch,
    unsigned int        srcBlkPadX,
    unsigned int        srcBlkPadY,
    unsigned int        numBlocks,
    EVELIB_KernelFuncType execFunc[],
    EVELIB_KernelContextType context[],
    unsigned int        numKernels
)
{
    volatile unsigned int   *AETCTL  = ((volatile unsigned int *) ((unsigned int)edmaCc + AETCTL_OFFSET));
    unsigned int indexIn  = 0;
    unsigned int indexOut = 1;

    /* ----------------------------------------------------- */
    /* Loop Variables                                        */
    /* Where y_offset is the vertical offset to the next     */
    /* image block.                                          */
    /* ----------------------------------------------------- */
    int                     x, k;

    /* ----------------------------------------------------- */
    /* Transfer complete codes for input and output          */
    /* ping/pong channels                                    */
    /* ----------------------------------------------------- */
    unsigned int            tcc_in;
    unsigned int            tcc_out;


    /* ----------------------------------------------------- */
    /* ESR values for each event                             */
    /* ----------------------------------------------------- */
    unsigned int            evt_no_set_in;
    unsigned int            evt_no_set_out;


    /* ----------------------------------------------------- */
    /* Words used to set register values for DMA submission  */
    /* and completion. These will be passed as arguments to  */
    /* the DMA_SUBMIT() and DMA_WAIT macros to trigger       */
    /* transfers and wait for completion.                    */
    /* ----------------------------------------------------- */

    unsigned int            wait_word;
    unsigned int            submit_word;
    unsigned int            wait_word_in_out;
    unsigned int            submit_word_in, submit_word_out;
    unsigned int            submit_out;
    unsigned int            wait_out;
    unsigned int            submit_in;
    unsigned int            wait_in;

    /* -------------------------------------------------------------------- */
    /* Used to check if we are processing the first or last block in the    */
    /* row.                                                                 */
    /* -------------------------------------------------------------------- */

    unsigned int first_hrz_block  = 0;
    unsigned int last_hrz_block   = (numBlocks) - 1;

    unsigned int flag;

    /* -------------------------------------------------------------------- */
    /* Precompute the transfer complete codes and event set register values */
    /* that will be passed into the DMA_WAIT and DMA_SUBMIT macros. These   */
    /* macros are used to start transfers and check for completion.         */
    /* -------------------------------------------------------------------- */
    tcc_in          =    0x1 << edmaResources->tccVal[indexIn];
    tcc_out         =    0x1 << edmaResources->tccVal[indexOut];

    evt_no_set_in   =    (CSL_EDMACC_ESR_E0_SET << edmaResources->logicalChannelNo[indexIn]);
    evt_no_set_out  =    (CSL_EDMACC_ESR_E0_SET << edmaResources->logicalChannelNo[indexOut]);

    if (evt_no_set_out > evt_no_set_in)
    AETCTL[0]       =    0x80000000 + evt_no_set_in  + (edmaResources->tccVal[indexOut] << 8);//:TODO:
    else
    AETCTL[0]       =    0x80000000 + evt_no_set_out + (edmaResources->tccVal[indexIn] << 8);


    wait_word_in_out       =    tcc_in | tcc_out;

    submit_out      =    evt_no_set_out;
    wait_out        =    tcc_out;

    submit_in       =    evt_no_set_in;
    wait_in         =    tcc_in;

    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /* ----------------------------------------------------------------- */
    /* Processing loop begins here                                       */
    /* ----------------------------------------------------------------- */

    /* ------------------------------------------------------------- */
    /* Prologue:                                                     */
    /* Transfer the first block in row, reset image pointers and     */
    /* block count for autoincrementing                              */
    /* ------------------------------------------------------------- */
    EVELIB_EDMAScatterGatherConfigure(srcPtrList,
                                        srcBlkPtrList,
                                        numTransfersIn,      /**< Number of Transfers required */
                                        indexIn,
                                        edmaResources,         /**< EDMA state structure */
                                        edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                        );

    /* -------------------------------------------------------------- */
    /* Assign ping/pong buffer to first block transfer in row         */
    /* -------------------------------------------------------------- */

    submit_word    =    submit_in;
    wait_word      =    wait_in;


    /*---------------------------------------------------------------*/
    /*  Set transfer pending status flag, to indicate that transfer  */
    /*  is in progress.                                              */
    /*---------------------------------------------------------------*/

/*    *trf_pend  =  TRUE;*///:TODO:

    /*---------------------------------------------------------------*/
    /*  Return WBUF to VCOP, ans assign all A buffers to system.     */
    /*---------------------------------------------------------------*/

    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);

    /* ------------------------------------------------------------- */
    /* Kick off first block transfer                                 */
    /* ------------------------------------------------------------- */
    DMA_SUBMIT(edmaCc, submit_word);


    /* ------------------------------------------------------------- */
    /*  Check for completion of first horizontal block before        */
    /*  before entering inner loop.                                  */
    /* ------------------------------------------------------------- */
    DMA_WAIT(edmaCc, wait_word);


    /*---------------------------------------------------------------*/
    /*  Clear trf_pend status, as we have finished waiting on trans. */
    /*---------------------------------------------------------------*/

    /**trf_pend   = FALSE;*///:TODO:

    /*---------------------------------------------------------------*/
    /* Set flag to BUF_PING, so that A buffers are handed to VCOP.   */
    /*---------------------------------------------------------------*/

    flag       =  BUF_PING;

    /* --------------------------------------------------------------*/
    /* Inner loop, used to process a horizontal row of image blocks  */
    /* ------------------------------------------------------------- */

    for(x = 0; x < (numBlocks); x++)
    {

        /* --------------------------------------------------------- */
        /* Case A: Ping                                              */
        /*                                                           */
        /* We will transfer a new ping buffer to internal memory and */
        /* transfer the previously processed ping buffer to external */
        /* mem. While this transfer is occuring, we will process     */
        /* data in the pong buffer.                                  */
        /*                                                           */
        /* Case B: Pong                                              */
        /*                                                           */
        /* We will transfer a new pong buffer to internal memory and */
        /* transfer the previously processed pong buffer to external */
        /* mem. While this transfer is occuring, we will process     */
        /* data in the ping buffer.                                  */
        /* --------------------------------------------------------- */

        flag = VCOP_BUF_SWITCH_TOGGLE (flag);

        submit_word_in = submit_in;
        submit_word_out = submit_out;
        wait_word = wait_word_in_out;

        /* ------------------------------------------------------------ */
        /* If we are at first or last iteration in inner loop, set the  */
        /* enable words to be single direction "in" or "out" channels.  */
        /* ------------------------------------------------------------ */

        if(x == last_hrz_block)
        {
            submit_word_in = 0u;
            wait_word   = wait_out;
        }

        if(x == first_hrz_block)
        {
            submit_word_out = 0u;
            wait_word   = wait_in;

        }

        /**trf_pend  =  TRUE;*///:TODO:

        EVELIB_EDMAScatterGatherConfigure(&srcPtrList[(x+1)*numTransfersIn],
                                        srcBlkPtrList,
                                        numTransfersIn,      /**< Number of Transfers required */
                                        indexIn,
                                        edmaResources,         /**< EDMA state structure */
                                        edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                        );
        DMA_SUBMIT(edmaCc, submit_word_in);

        EVELIB_EDMAScatterGatherConfigure(dstBlkPtrList,
                                        (x>1)?&dstPtrList[(x-1)*numTransfersOut]:&dstPtrList[0],
                                        numTransfersOut,      /**< Number of Transfers required */
                                        indexOut,
                                        edmaResources,         /**< EDMA state structure */
                                        edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                        );

        /* ------------------------------------------------------------- */
        /* Kick off transfers of next block to process before processing */
        /* the current block.                                            */
        /* ------------------------------------------------------------- */

        DMA_SUBMIT(edmaCc, submit_word_out);

        /* ------------------------------------------------------------- */
        /* Use VCOP to copy data from IBUFL to IBUFH while DMA transfers */
        /* are occuring.                                                 */
        /* ------------------------------------------------------------- */

        /* ------------------------ */
        /* Wait for VCOP to be done */
        /* ------------------------ */
        for(k=0; k<numKernels; k++)
        {
            (execFunc[k])(context[k]);
        }

        _vcop_vloop_done();
        /* ------------------------------------------------------------- */
        /* Check for transfer completion after processing data           */
        /* ------------------------------------------------------------- */

        DMA_WAIT(edmaCc, wait_word);

        /**trf_pend   = FALSE;*///:TODO:
    }

    /* ----------------------------------------------------------------- */
    /*  Epilogue:                                                        */
    /*  Transfer the last processed block in the row                     */
    /* ----------------------------------------------------------------- */

    flag = VCOP_BUF_SWITCH_TOGGLE (flag);

    EVELIB_EDMAScatterGatherConfigure(dstBlkPtrList,
                            &dstPtrList[(x-1)*numTransfersOut],
                            numTransfersOut,      /**< Number of Transfers required */
                            indexOut,
                            edmaResources,         /**< EDMA state structure */
                            edmaCc                   /**< Pointer to the start of EDMA CC0 */
                            );

    wait_word        =  wait_out;
    submit_word      =  submit_out;

    /* *trf_pend  =  TRUE; *///:TODO:

    DMA_SUBMIT(edmaCc, submit_word);
    DMA_WAIT(edmaCc, wait_word);

    /* *trf_pend   = FALSE;*///:TODO:

    /*---------------------------------------------------------------*/
    /*  Return  all buffers to system before returning.              */
    /*---------------------------------------------------------------*/

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /* ------------------------------------------------------------- */
    /* Check to make sure there are no more pending transfers        */
    /* ------------------------------------------------------------- */
    assert(edmaCc->IPR == 0);
}

void EVELIB_algoDMAScatterGatherProcessSequential
(
    DMA_resourceStruct  *edmaResources,
    CSL_EdmaccRegsOvly  edmaCc,
    unsigned char       **srcPtrList,
    int                 numTransfersIn,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    unsigned char       **dstPtrList,
    int                 numTransfersOut,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    unsigned char       **srcBlkPtrList,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    int                 srcBlkPitch,
    unsigned char       **dstBlkPtrList,
    unsigned int        dstBlkWidth,
    unsigned int        dstBlkHeight,
    int                 dstBlkPitch,
    unsigned int        srcBlkPadX,
    unsigned int        srcBlkPadY,
    unsigned int        numBlocks,
    EVELIB_KernelFuncType execFunc[],
    EVELIB_KernelContextType context[],
    unsigned int        numKernels
)
{
    unsigned int chan_in = edmaResources->logicalChannelNo[0];
    unsigned int indexOut = edmaResources->logicalChannelNo[1];

    /* ----------------------------------------------------- */
    /* Loop Variables                                        */
    /* Where y_offset is the vertical offset to the next     */
    /* image block.                                          */
    /* ----------------------------------------------------- */
    int                     x, k;

    /* ----------------------------------------------------- */
    /* Transfer complete codes for input and output          */
    /* ping/pong channels                                    */
    /* ----------------------------------------------------- */
    unsigned int            tcc_in;
    unsigned int            tcc_out;

    /* ----------------------------------------------------- */
    /* ESR values for each event                             */
    /* ----------------------------------------------------- */
    unsigned int            evt_no_set_in;
    unsigned int            evt_no_set_out;

    /* ----------------------------------------------------- */
    /* Words used to set register values for DMA submission  */
    /* and completion. These will be passed as arguments to  */
    /* the DMA_SUBMIT() and DMA_WAIT macros to trigger       */
    /* transfers and wait for completion.                    */
    /* ----------------------------------------------------- */

    unsigned int            wait_word;
    unsigned int            submit_word;
    unsigned int            submit_out;
    unsigned int            wait_out;
    unsigned int            submit_in;
    unsigned int            wait_in;

    uint8_t             *trf_pend;//:TODO:

    /* -------------------------------------------------------------------- */
    /* Precompute the transfer complete codes and event set register values */
    /* that will be passed into the DMA_WAIT and DMA_SUBMIT macros. These   */
    /* macros are used to start transfers and check for completion.         */
    /* -------------------------------------------------------------------- */
    tcc_in          =    0x1 << edmaResources->tccVal[chan_in];
    tcc_out         =    0x1 << edmaResources->tccVal[indexOut];

    evt_no_set_in   =    (CSL_EDMACC_ESR_E0_SET << edmaResources->logicalChannelNo[chan_in]);
    evt_no_set_out  =    (CSL_EDMACC_ESR_E0_SET << edmaResources->logicalChannelNo[indexOut]);

    submit_out      =    evt_no_set_out;
    wait_out        =    tcc_out;

    submit_in       =    evt_no_set_in;
    wait_in         =    tcc_in;

    /*---------------------------------------------------------------*/
    /*  Return WBUF to VCOP, ans assign all A buffers to system.     */
    /*---------------------------------------------------------------*/

    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);

    /* *trf_pend   = FALSE;*///:TODO:

    /* --------------------------------------------------------------*/
    /* Inner loop, used to process a horizontal row of image blocks  */
    /* ------------------------------------------------------------- */

    for(x = 0; x < (numBlocks); x++)
    {

        /* --------------------------------------------------------- */
        /* Case A: Ping                                              */
        /*                                                           */
        /* We will transfer a new ping buffer to internal memory and */
        /* transfer the previously processed ping buffer to external */
        /* mem. While this transfer is occuring, we will process     */
        /* data in the pong buffer.                                  */
        /*                                                           */
        /* Case B: Pong                                              */
        /*                                                           */
        /* We will transfer a new pong buffer to internal memory and */
        /* transfer the previously processed pong buffer to external */
        /* mem. While this transfer is occuring, we will process     */
        /* data in the ping buffer.                                  */
        /* --------------------------------------------------------- */

        VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

        EVELIB_EDMAScatterGatherConfigure(&srcPtrList[(x)*numTransfersIn],
                                        srcBlkPtrList,
                                        numTransfersIn,      /**< Number of Transfers required */
                                        chan_in,
                                        edmaResources,         /**< EDMA state structure */
                                        edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                        );

        /* -------------------------------------------------------------- */
        /* Assign ping buffer to block transfer in row         */
        /* -------------------------------------------------------------- */

        submit_word    =    submit_in;
        wait_word      =    wait_in;

        /*---------------------------------------------------------------*/
        /*  Set transfer pending status flag, to indicate that transfer  */
        /*  is in progress.                                              */
        /*---------------------------------------------------------------*/

        *trf_pend  =  TRUE;

        DMA_SUBMIT(edmaCc, submit_word);

        DMA_WAIT(edmaCc, wait_word);

        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_VCOP, IBUFLA_VCOP);

        /* ------------------------ */
        /* Wait for VCOP to be done */
        /* ------------------------ */
        for(k=0; k<numKernels; k++)
        {
            (execFunc[k])(context[k]);
        }

        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

        EVELIB_EDMAScatterGatherConfigure(dstBlkPtrList,
                                        &dstPtrList[(x)*numTransfersOut],
                                        numTransfersOut,      /**< Number of Transfers required */
                                        indexOut,
                                        edmaResources,         /**< EDMA state structure */
                                        edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                        );

        /* ------------------------------------------------------------- */
        /* Kick off transfers of next block to process before processing */
        /* the current block.                                            */
        /* ------------------------------------------------------------- */
        submit_word    =    submit_out;
        wait_word      =    wait_out;

        DMA_SUBMIT(edmaCc, submit_word);

        *trf_pend  =  TRUE;

        /* ------------------------------------------------------------- */
        /* Use VCOP to copy data from IBUFL to IBUFH while DMA transfers */
        /* are occuring.                                                 */
        /* ------------------------------------------------------------- */
        /* ------------------------------------------------------------- */
        /* Check for transfer completion after processing data           */
        /* ------------------------------------------------------------- */

        DMA_WAIT(edmaCc, wait_word);

        *trf_pend   = FALSE;
    }
    /*---------------------------------------------------------------*/
    /*  Return  all buffers to system before returning.              */
    /*---------------------------------------------------------------*/

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /* ------------------------------------------------------------- */
    /* Check to make sure there are no more pending transfers        */
    /* ------------------------------------------------------------- */
    assert(edmaCc->IPR == 0);
}

void EVELIB_algoDMAScatterGatherProcess
(
    DMA_resourceStruct  *edmaResources,
    CSL_EdmaccRegsOvly  edmaCc,
    unsigned char       **srcPtrList,
    int                 numTransfersIn,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    unsigned char       **dstPtrList,
    int                 numTransfersOut,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    unsigned char       **srcBlkPtrList,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    int                 srcBlkPitch,
    unsigned char       **dstBlkPtrList,
    unsigned int        dstBlkWidth,
    unsigned int        dstBlkHeight,
    int                 dstBlkPitch,
    unsigned int        srcBlkPadX,
    unsigned int        srcBlkPadY,
    unsigned int        numBlocks,
    EVELIB_KernelFuncType execFunc[],
    EVELIB_KernelContextType context[],
    unsigned int        numKernels,
    int32_t             sequential
)
{
    if(sequential)
    {
        EVELIB_algoDMAScatterGatherProcessSequential
        (
            edmaResources,
            edmaCc,
            srcPtrList,
            numTransfersIn,
            srcImageWidth,
            srcImageHeight,
            srcImagePitch,
            dstPtrList,
            numTransfersOut,
            dstImageWidth,
            dstImageHeight,
            dstImagePitch,
            srcBlkPtrList,
            srcBlkWidth,
            srcBlkHeight,
            srcBlkPitch,
            dstBlkPtrList,
            dstBlkWidth,
            dstBlkHeight,
            dstBlkPitch,
            srcBlkPadX,
            srcBlkPadY,
            numBlocks,
            execFunc,
            context,
            numKernels
        );
    }
    else
    {
        EVELIB_algoDMAScatterGatherProcessConcurrent
        (
            edmaResources,
            edmaCc,
            srcPtrList,
            numTransfersIn,
            srcImageWidth,
            srcImageHeight,
            srcImagePitch,
            dstPtrList,
            numTransfersOut,
            dstImageWidth,
            dstImageHeight,
            dstImagePitch,
            srcBlkPtrList,
            srcBlkWidth,
            srcBlkHeight,
            srcBlkPitch,
            dstBlkPtrList,
            dstBlkWidth,
            dstBlkHeight,
            dstBlkPitch,
            srcBlkPadX,
            srcBlkPadY,
            numBlocks,
            execFunc,
            context,
            numKernels
        );
    }
}

/*-----------------------------------------------------------------------*/
/*  End of file algo_scatter_gather_incr.c                                     */
/*=======================================================================*/
/*  Texas Instruments incorporated 2013.                                 */
/*-----------------------------------------------------------------------*/
