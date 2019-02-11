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

/*==========================================================================*/
/*==========================================================================*/


/**
 *  @file       dma_functions.c
 *
 *  @brief      This header defines functions to use EDMA
 */

/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/*  These are the include files that are needed for edma/qdma.           */
/*-----------------------------------------------------------------------*/
#include "dma_funcs.h"
#include "edmacc_config.h"

#define CSL_QUE_PRI0     0x00000000U
#define CSL_QUE_PRI3     0x00000003U

/* ==================================================
 *  @func     DMA_funcs_hardwareRegSetup
 *
 *  @desc   This function updates the actual hardware register based on
 *          DMA_resourceStruct. For QDMA we will be setting up QCHMAP,
 *          QDMAQNUM, QEESR. Similarly for EDMA we will be setting
 *          up, DCHMAP, DMAQNUM. Independent of QDMA and EDMA we configure
 *          QUEWTHRA, QUEPRI and QUETCMAP registers.
 *          In current implementation there is a one to one mapping
 *          between transfer controllers and hardware queues. TC0 is
 *          mapped to Q0 and TC1 is mapped to Q1, this means Q0 submits
 *          on TC0 and Q1 submits on TC1.
 *          More over Q0 is given a higher priority compare to Q1.
 *          Currently Trigger word for QDMA channel is set to 7.
 *
 *
 *  @modif    This function modifies edmaCc
 *
 *  @inputs   This function takes following Inputs
 *                  edmaCc :
 *                      Pointer to the address space of EDMA module
 *                  edmaResources :
 *                      Pointer to the resource Structure as defined in dma_resource.h
 *
 *  @outputs NONE
 *
 *   @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
int32_t DMA_funcs_hardwareRegSetup(CSL_EdmaccRegsOvly edmaCc,
                                const DMA_resourceStruct * edmaResources)
{
    uint32_t            evtNo;
    uint32_t            queNo;
    uint32_t            trigWord;
    uint32_t            queRem;
    uint32_t            queShift;
    uint32_t            prmNo;
    uint32_t            dmaAttr;
    int32_t             channelCnt;
    uint32_t             queRegNo;
    volatile uint32_t   *baseParam;
    int32_t             status = 0;
    uint32_t            maxNumDmaQue;

    if ( edmaResources == NULL )
    {
        status = -1;
    }

    if ( status == 0 )
    {
        /*-------------------------------------------------------------------*/
        /*  First setup the quee to TC mapping, we setup 1 to 1 mapping and  */
        /*  this needs to be verified based on FIFO properties. For now Q0   */
        /*  submits on TC0, and similarly Q1 submits on TC1.                 */
        /*-------------------------------------------------------------------*/

        /* The uint8_t casts below are to satisfy MISRA-C rule 10.5 ... however,
        if the underlying shift values change this cast needs to change to be able
        to contain the larger register size */
        edmaCc->QUETCMAP = ((uint32_t)CSL_EDMACC_CCCFG_NUM_TC_1 <<
                                CSL_EDMACC_QUETCMAP_TCNUMQ0_SHIFT) |
                                ((uint32_t)CSL_EDMACC_CCCFG_NUM_TC_2 <<
                                CSL_EDMACC_QUETCMAP_TCNUMQ1_SHIFT);

        /*-------------------------------------------------------------------*/
        /*  We need to verify priority values, but for now, DDR traffic is   */
        /*  given higher priority, and co-processor commands are given le    */
        /*  sser priority. We program these without accepting user inputs    */
        /*  as this could impact performance, so we calibrate this on QT     */
        /*  and set it here.                                                 */
        /*-------------------------------------------------------------------*/

        edmaCc->QUEPRI =
            ((uint32_t)CSL_QUE_PRI3 << CSL_EDMACC_QUEPRI_PRIQ0_SHIFT) |
                    ((uint32_t)CSL_QUE_PRI0 << CSL_EDMACC_QUEPRI_PRIQ1_SHIFT);

        /*-------------------------------------------------------------------*/
        /* Also set up the threshold register though this is strictly not    */
        /* needed.                                                           */
        /*-------------------------------------------------------------------*/

        edmaCc->QWMTHRA = CSL_EDMACC_QWMTHRA_RESETVAL & 0xFFFFU;

        maxNumDmaQue = ( (uint32_t)(edmaCc->CCCFG >> 0x16U ) & (uint32_t)0x7U ) + 1U;

        /*-------------------------------------------------------------------*/
        /*  Now iterate for each of the channels and setup the other regs.   */
        /*  based on channel attribute.                                      */
        /*-------------------------------------------------------------------*/
        for (channelCnt = 0 ; channelCnt < edmaResources->numChannels ; channelCnt++)
        {
            /*---------------------------------------------------------------*/
            /*  Read specific event num, tcc, region, trigger param, base    */
            /*  param, number of paramns, trfPend locn, dma attrib, of      */
            /*  channel, queNo for request.                                 */
            /*---------------------------------------------------------------*/


            evtNo = edmaResources->logicalChannelNo[channelCnt];
            queNo = ((uint32_t)edmaResources->queNo[channelCnt] & 0x01U) % maxNumDmaQue;
            baseParam = edmaResources->baseParam[channelCnt];
            dmaAttr = edmaResources->dmaAttr[channelCnt];

            if ( dmaAttr == DMA_CHAN_ATTR_EDMA )
            {

                /*---------------------------------------------------------------*/
                /*  If it is EDMA channel, we setup DCHMAP, DMAQNUM, DRAE. This  */
                /*  will tie down specific PARAM to event, queue for event, and  */
                /*  region where completion interrupt must go.                   */
                /*---------------------------------------------------------------*/

                /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
                /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
                /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
                   The address space is 32 bit and type casting to integer will not result into any loss because of TI's
                 compiler teratment to integer.   */

                prmNo = ((uint32_t) baseParam - (uint32_t)edmaCc->PARAMENTRY)
                            >> CSL_EDMACC_DCHMAP_PAENTRY_SHIFT;
                /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

#ifdef DMA_ASSERT
                    assert (evtNo >= 0U);
                    assert (evtNo <= NUM_EDMA_CHANNELS);
                    assert (queNo >= 0U);
                    assert (queNo <= 1U);
                    assert (prmNo >= 0U);
                    assert (prmNo <= EDMA_NUM_PARAMS);
                    assert (edmaResources->numChannels <= NUM_MAX_CHANNELS);
#endif

                    /*-----------------------------------------------------------*/
                    /*  Write the corresponding param for evt no evtNo, each    */
                    /*  of the 64 events has an associated register. This is     */
                    /*  the difference between the current param address and     */
                    /*  base PARAM address. This gives offset in bytes, 32       */
                    /*  bytes makes a PARAM, so to get PARAM no, we divide       */
                    /*  by 32, note DCHMAP finally ends up taking this offset    */
                    /*  so we can avoid right shifting and left shifting by 5    */
                    /*  as we optimize cycles.                                   */
                    /*-----------------------------------------------------------*/
                    edmaCc->DCHMAP[evtNo] = (uint32_t) prmNo << CSL_EDMACC_DCHMAP_PAENTRY_SHIFT;

                    /*-----------------------------------------------------------*/
                    /*  Queue to use for the 64 event is present in 8 regs. So   */
                    /*  we determine regNo, and offset within that register.    */
                    /*  Offset within reg, is used to decide shift.              */
                    /*-----------------------------------------------------------*/

                    queRegNo = evtNo >> 3U;
                    queRem = evtNo - (8U * queRegNo);

#ifdef DMA_ASSERT
                    assert (queRem >= 0U);
                    assert (queRem <= 7U);
#endif

                    queShift = CSL_EDMACC_DMAQNUM_E0_SHIFT;

                    if (queRem == 0U)
                    {
                        queShift = CSL_EDMACC_DMAQNUM_E0_SHIFT;
                    }
                    if (queRem == 1U)
                    {
                        queShift = CSL_EDMACC_DMAQNUM_E1_SHIFT;
                    }
                    if (queRem == 2U)
                    {
                        queShift = CSL_EDMACC_DMAQNUM_E2_SHIFT;
                    }
                    if (queRem == 3U)
                    {
                        queShift = CSL_EDMACC_DMAQNUM_E3_SHIFT;
                    }
                    if (queRem == 4U)
                    {
                        queShift = CSL_EDMACC_DMAQNUM_E4_SHIFT;
                    }
                    if (queRem == 5U)
                    {
                        queShift = CSL_EDMACC_DMAQNUM_E5_SHIFT;
                    }
                    if (queRem == 6U)
                    {
                        queShift = CSL_EDMACC_DMAQNUM_E6_SHIFT;
                    }
                    if (queRem == 7U)
                    {
                        queShift = CSL_EDMACC_DMAQNUM_E7_SHIFT;
                    }

                    /*-----------------------------------------------------------*/
                    /*  Now we can write in DMAQNUM, the queue number, at the    */
                    /*  correct location.                                        */
                    /*-----------------------------------------------------------*/

                     edmaCc->DMAQNUM[queRegNo] = (edmaCc->DMAQNUM[queRegNo]  & ~((uint32_t)1U<<queShift) ) |
                                              (queNo << queShift);
            }
            else
            {
#ifdef DMA_ASSERT
                assert (evtNo >= 0U);
                assert (evtNo <= NUM_QDMA_CHANNELS);
                assert (queNo >= 0U);
                assert (queNo <= 1U);
                assert (edmaResources->numChannels <= NUM_QDMA_CHANNELS);
#endif

                /*-----------------------------------------------------------*/
                /* For QDMA we have an associated QDMA enable register.      */
                /*-----------------------------------------------------------*/
                queShift = CSL_EDMACC_QEESR_E0_SHIFT;

                if (evtNo == 0U)
                {
                    queShift = CSL_EDMACC_QEESR_E0_SHIFT;
                }
                if (evtNo == 1U)
                {
                    queShift = CSL_EDMACC_QEESR_E1_SHIFT;
                }
                if (evtNo == 2U)
                {
                    queShift = CSL_EDMACC_QEESR_E2_SHIFT;
                }
                if (evtNo == 3U)
                {
                    queShift = CSL_EDMACC_QEESR_E3_SHIFT;
                }
                if (evtNo == 4U)
                {
                    queShift = CSL_EDMACC_QEESR_E4_SHIFT;
                }
                if (evtNo == 5U)
                {
                    queShift = CSL_EDMACC_QEESR_E5_SHIFT;
                }
                if (evtNo == 6U)
                {
                    queShift = CSL_EDMACC_QEESR_E6_SHIFT;
                }
                if (evtNo == 7U)
                {
                    queShift = CSL_EDMACC_QEESR_E7_SHIFT;
                }

                edmaCc->QEESR = ((uint32_t)0x1U << queShift);

                /*-----------------------------------------------------------*/
                /*  For QDMA channel we write both param amd trigger word.   */
                /*-----------------------------------------------------------*/
                trigWord = edmaResources->trigWordIndex[channelCnt];

                /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
                /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
                /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
                   The address space is 32 bit and type casting to integer will not result into any loss because of TI's
                 compiler teratment to integer.   */
                prmNo = ((uint32_t) baseParam - (uint32_t) &edmaCc->PARAMENTRY[0])
                        >> CSL_EDMACC_QCHMAP_PAENTRY_SHIFT;
                /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

                edmaCc->QCHMAP[evtNo] = ((uint32_t) prmNo << CSL_EDMACC_QCHMAP_PAENTRY_SHIFT )
                                         | (trigWord << CSL_EDMACC_QCHMAP_TRWORD_SHIFT);

                /*-----------------------------------------------------------*/
                /*  In QDMAQNUM, we write the queue number specified by the  */
                /*  user, as evtNo has to be one of 8 QDMA channels. We     */
                /*  also write a 1, into the region requested by user.       */
                /*-----------------------------------------------------------*/

                queRem = evtNo;
                if (queRem == 0U)
                {
                    queShift = CSL_EDMACC_QDMAQNUM_E0_SHIFT;
                }
                if (queRem == 1U)
                {
                    queShift = CSL_EDMACC_QDMAQNUM_E1_SHIFT;
                }
                if (queRem == 2U)
                {
                    queShift = CSL_EDMACC_QDMAQNUM_E2_SHIFT;
                }
                if (queRem == 3U)
                {
                    queShift = CSL_EDMACC_QDMAQNUM_E3_SHIFT;
                }
                if (queRem == 4U)
                {
                    queShift = CSL_EDMACC_QDMAQNUM_E4_SHIFT;
                }
                if (queRem == 5U)
                {
                    queShift = CSL_EDMACC_QDMAQNUM_E5_SHIFT;
                }
                if (queRem == 6U)
                {
                    queShift = CSL_EDMACC_QDMAQNUM_E6_SHIFT;
                }
                if (queRem == 7U)
                {
                    queShift = CSL_EDMACC_QDMAQNUM_E7_SHIFT;
                }

                edmaCc->QDMAQNUM =  (edmaCc->QDMAQNUM & ~((uint32_t)1U<<queShift) ) |
                                              (queNo << queShift) ;
            }
        }
    }
    return status;
}

/* ==================================================
 *  @func     DMA_funcs_writeTransferParams
 *
 *  @desc     This function populates the param set based on the inputs.
 *            It is to be noted that this API will automatically trigger
 *            QDMA channel transfer because it writes to all the param
 *            set entries
 *
 *  @modif    This function modifies param set
 *
 *  @inputs   This function takes following Inputs
 *                  tparam :
 *                      Trigger param where you want to write
 *                  optWord :
 *                      Opt word for the param set corresponding to the
 *                      channel number given
 *                  srcPtr :
 *                      Pointer to the source
 *                  dstPtr :
 *                      Pointer to the destination
 *                  noBytes :
 *                      Number of bytes to be transfered (Acnt)
 *                  noLines :
 *                      Number of lines of noBytes (Bcnt)
 *                  srcLinePitch :
 *                      Pitch for the source pointer
 *                  dstLinePitch :
 *                      Pitch for the destination pointer
 *                  srcNextBlkOffset :
 *                      Offset for the next block in for source
 *                  dstNextBlkOffset :
 *                      Offset for the next block for destination
 *                  numAutoIncr :
 *                      Number of times autoincrement to be executed (Ccnt)
 *                  linkAddr :
 *                      Link address for the cases when you want to link
 *                      one param set to another
 *                      Default value = 0, in this case it will write 0xFFFF
 *
 *  @outputs NONE
 *
 *
 *  =======================================================
 */
  /* This decleration violates MISRA-C Rule 16.7 : MISRA.PPARAM.NEEDS.CONST.
 This cannot be avoided because dstPtr is actually modified by the EDMA hardware
 but from the code compiler cannot detect this and hence returns a warning */
void DMA_funcs_writeTransferParams(volatile uint32_t tparam[8], uint32_t optWord,
                    const uint8_t *srcPtr, uint8_t *dstPtr, uint16_t noBytes, uint16_t noLines,
                    int16_t srcLinePitch, int16_t dstLinePitch, int16_t srcNextBlkOffset,
                    int16_t dstNextBlkOffset, uint16_t numAutoIncr, uint16_t linkAddr)
{
    tparam[0] = (uint32_t) optWord;

    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
       The address space is 32 bit and type casting to integer will not result into any loss because of TI's
     compiler teratment to integer.   */
    tparam[1] = (uint32_t) srcPtr;
    tparam[2] = pack2(noLines, noBytes);
    tparam[3] = (uint32_t) dstPtr;
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    tparam[4] = (uint32_t)pack2((uint16_t)dstLinePitch, (uint16_t)srcLinePitch);
    if ( linkAddr == 0)
    {
        tparam[5] = pack2(noLines, 0xFFFFU);
    }
    else
    {
        tparam[5] = pack2(noLines, linkAddr);
    }
    tparam[6] = (uint32_t)pack2((uint16_t)dstNextBlkOffset, (uint16_t)srcNextBlkOffset);
    tparam[7] = numAutoIncr;
}

