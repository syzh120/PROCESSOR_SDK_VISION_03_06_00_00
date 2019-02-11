/*
* dma_link_test.c
*
* EDMA3 mem-to-mem data copy test case, using two DMA channels, linked to each
* other.
*
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include "sample.h"

extern signed char   _srcBuff1[MAX_BUFFER_SIZE];
extern signed char   _srcBuff2[MAX_BUFFER_SIZE];
extern signed char   _dstBuff1[MAX_BUFFER_SIZE];
extern signed char   _dstBuff2[MAX_BUFFER_SIZE];

extern signed char *srcBuff1;
extern signed char *srcBuff2;
extern signed char *dstBuff1;
extern signed char *dstBuff2;

extern void *AppSemHandle1;
/**
*  \brief   EDMA3 mem-to-mem data copy test case, using two DMA
*              channels, linked to each other.
*
*  \param  acnt        [IN]      Number of bytes in an array
*  \param  bcnt        [IN]      Number of arrays in a frame
*  \param  ccnt        [IN]      Number of frames in a block
*  \param  syncType    [IN]      Synchronization type (A/AB Sync)
*
*  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
*/
EDMA3_DRV_Result edma3_test_with_link(
                                      EDMA3_DRV_Handle hEdma,
                                      uint32_t acnt,
                                      uint32_t bcnt,
                                      uint32_t ccnt,
                                      EDMA3_DRV_SyncType syncType)
{
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;
    EDMA3_DRV_PaRAMRegs paramSet = {0,0,0,0,0,0,0,0,0,0,0,0};
    uint32_t ch1Id = 0;
    uint32_t ch2Id = 0;
    uint32_t tcc1 = 0;
    uint32_t tcc2 = 0;
    int i;
    uint32_t count;
    uint32_t Istestpassed1 = 0u;
    uint32_t Istestpassed2 = 0u;
    uint32_t numenabled = 0;
    uint32_t BRCnt = 0;
    int srcbidx = 0, desbidx = 0;
    int srccidx = 0, descidx = 0;


    srcBuff1 = (signed char*) GLOBAL_ADDR(_srcBuff1);
    dstBuff1 = (signed char*) GLOBAL_ADDR(_dstBuff1);
    srcBuff2 = (signed char*) GLOBAL_ADDR(_srcBuff2);
    dstBuff2 = (signed char*) GLOBAL_ADDR(_dstBuff2);


    /* Initalize source and destination buffers */
    for (count = 0u; count < (acnt*bcnt*ccnt); count++)
    {
        srcBuff1[count] = (int)count+1;
        srcBuff2[count] = (int)count+1;
        /**
        * No need to initialize the destination buffer as it is being invalidated.
        dstBuff1[count] = initval;
        dstBuff2[count] = initval;
        */
    }


#ifdef EDMA3_ENABLE_DCACHE
    /*
    * Note: These functions are required if the buffer is in DDR.
    * For other cases, where buffer is NOT in DDR, user
    * may or may not require the below functions.
    */
    /* Flush the Source Buffers */
    if (result == EDMA3_DRV_SOK)
    {
        result = Edma3_CacheFlush((uint32_t)srcBuff1, (acnt*bcnt*ccnt));
    }
    if (result == EDMA3_DRV_SOK)
    {
        result = Edma3_CacheFlush((uint32_t)srcBuff2, (acnt*bcnt*ccnt));
    }

    /* Invalidate the Destination Buffers */
    if (result == EDMA3_DRV_SOK)
    {
        result = Edma3_CacheInvalidate((uint32_t)dstBuff1, (acnt*bcnt*ccnt));
    }
    if (result == EDMA3_DRV_SOK)
    {
        result = Edma3_CacheInvalidate((uint32_t)dstBuff2, (acnt*bcnt*ccnt));
    }
#endif  /* EDMA3_ENABLE_DCACHE */


    irqRaised1 = 0;
    irqRaised2 = 0;

    /* Set B count reload as B count. */
    BRCnt = bcnt;

    /* Setting up the SRC/DES Index */
    srcbidx = (int)acnt;
    desbidx = (int)acnt;
    if (syncType == EDMA3_DRV_SYNC_A)
    {
        /* A Sync Transfer Mode */
        srccidx = (int)acnt;
        descidx = (int)acnt;
    }
    else
    {
        /* AB Sync Transfer Mode */
        srccidx = ((int)acnt * (int)bcnt);
        descidx = ((int)acnt * (int)bcnt);
    }


    /* Setup for Channel 1*/
    tcc1 = EDMA3_DRV_TCC_ANY;
    ch1Id = EDMA3_DRV_DMA_CHANNEL_ANY;

    /* Request any DMA channel and any TCC */
    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_requestChannel (hEdma, &ch1Id, &tcc1,
            (EDMA3_RM_EventQueue)0,
            &callback1, NULL);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /* Fill the PaRAM Set with transfer specific information */
        paramSet.srcAddr    = (uint32_t)(srcBuff1);
        paramSet.destAddr   = (uint32_t)(dstBuff1);

        /**
        * Be Careful !!!
        * Valid values for SRCBIDX/DSTBIDX are between –32768 and 32767
        * Valid values for SRCCIDX/DSTCIDX are between –32768 and 32767
        */
        paramSet.srcBIdx    = srcbidx;
        paramSet.destBIdx   = desbidx;
        paramSet.srcCIdx    = srccidx;
        paramSet.destCIdx   = descidx;

        /**
        * Be Careful !!!
        * Valid values for ACNT/BCNT/CCNT are between 0 and 65535.
        * ACNT/BCNT/CCNT must be greater than or equal to 1.
        * Maximum number of bytes in an array (ACNT) is 65535 bytes
        * Maximum number of arrays in a frame (BCNT) is 65535
        * Maximum number of frames in a block (CCNT) is 65535
        */
        paramSet.aCnt       = acnt;
        paramSet.bCnt       = bcnt;
        paramSet.cCnt       = ccnt;

        /* For AB-synchronized transfers, BCNTRLD is not used. */
        paramSet.bCntReload = BRCnt;

        paramSet.linkAddr   = 0xFFFFu;

        /* Src & Dest are in INCR modes */
        paramSet.opt &= 0xFFFFFFFCu;
        /* Program the TCC */
        paramSet.opt |= ((tcc1 << OPT_TCC_SHIFT) & OPT_TCC_MASK);

        /* Enable Intermediate & Final transfer completion interrupt */
        paramSet.opt |= (1 << OPT_ITCINTEN_SHIFT);
        paramSet.opt |= (1 << OPT_TCINTEN_SHIFT);

        if (syncType == EDMA3_DRV_SYNC_A)
        {
            paramSet.opt &= 0xFFFFFFFBu;
        }
        else
        {
            /* AB Sync Transfer Mode */
            paramSet.opt |= (1 << OPT_SYNCDIM_SHIFT);
        }

        /* Now, write the PaRAM Set. */
        result = EDMA3_DRV_setPaRAM (hEdma, ch1Id, &paramSet);
    }


    /*
    * There is another way to program the PaRAM Set using specific APIs
    * for different PaRAM set entries. It gives user more control and easier
    * to use interface. User can use any of the methods.
    * Below is the alternative way to program the PaRAM Set.
    */

    /*

    if (result == EDMA3_DRV_SOK)
    {
    result = EDMA3_DRV_setSrcParams (hEdma, ch1Id, (uint32_t)(srcBuff1),
    EDMA3_DRV_ADDR_MODE_INCR,
    EDMA3_DRV_W8BIT);
    }

    if (result == EDMA3_DRV_SOK)
    {
    result = EDMA3_DRV_setDestParams (hEdma, ch1Id,
    (uint32_t)(dstBuff1),
    EDMA3_DRV_ADDR_MODE_INCR,
    EDMA3_DRV_W8BIT);
    }

    if (result == EDMA3_DRV_SOK)
    {
    result = EDMA3_DRV_setSrcIndex (hEdma, ch1Id, srcbidx, srccidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
    result =  EDMA3_DRV_setDestIndex (hEdma, ch1Id, desbidx, descidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
    if (syncType == EDMA3_DRV_SYNC_A)
    {
    result = EDMA3_DRV_setTransferParams (hEdma, ch1Id, acnt, bcnt,
    ccnt, BRCnt,
    EDMA3_DRV_SYNC_A);
    }
    else
    {
    result = EDMA3_DRV_setTransferParams (hEdma, ch1Id, acnt, bcnt,
    ccnt, BRCnt,
    EDMA3_DRV_SYNC_AB);
    }
    }

    if (result == EDMA3_DRV_SOK)
    {
    result = EDMA3_DRV_setOptField (hEdma, ch1Id,
    EDMA3_DRV_OPT_FIELD_TCINTEN, 1u);
    }

    if (result == EDMA3_DRV_SOK)
    {
    result = EDMA3_DRV_setOptField (hEdma, ch1Id,
    EDMA3_DRV_OPT_FIELD_ITCINTEN, 1u);
    }

    */


    /* Request any LINK channel and any TCC */
    if (result == EDMA3_DRV_SOK)
    {
        /* Setup for Channel 2 */
        ch2Id   = EDMA3_DRV_LINK_CHANNEL;
        tcc2    = EDMA3_DRV_TCC_ANY;

        result = EDMA3_DRV_requestChannel (hEdma, &ch2Id, &tcc2,
            (EDMA3_RM_EventQueue)0,
            &callback1, NULL);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /*
        * Fill the PaRAM Set for the LINK channel
        * with transfer specific information.
        */
        paramSet.srcAddr    = (uint32_t)(srcBuff2);
        paramSet.destAddr   = (uint32_t)(dstBuff2);

        /**
        * Be Careful !!!
        * Valid values for SRCBIDX/DSTBIDX are between –32768 and 32767
        * Valid values for SRCCIDX/DSTCIDX are between –32768 and 32767
        */
        paramSet.srcBIdx    = srcbidx;
        paramSet.destBIdx   = desbidx;
        paramSet.srcCIdx    = srccidx;
        paramSet.destCIdx   = descidx;

        /**
        * Be Careful !!!
        * Valid values for ACNT/BCNT/CCNT are between 0 and 65535.
        * ACNT/BCNT/CCNT must be greater than or equal to 1.
        * Maximum number of bytes in an array (ACNT) is 65535 bytes
        * Maximum number of arrays in a frame (BCNT) is 65535
        * Maximum number of frames in a block (CCNT) is 65535
        */
        paramSet.aCnt       = acnt;
        paramSet.bCnt       = bcnt;
        paramSet.cCnt       = ccnt;

        /* For AB-synchronized transfers, BCNTRLD is not used. */
        paramSet.bCntReload = BRCnt;

        paramSet.linkAddr   = 0xFFFFu;

        /* Reset opt field first */
        paramSet.opt = 0x0u;
        /* Src & Dest are in INCR modes */
        paramSet.opt &= 0xFFFFFFFCu;

        /* Enable Intermediate & Final transfer completion interrupt */
        paramSet.opt |= (1 << OPT_ITCINTEN_SHIFT);
        paramSet.opt |= (1 << OPT_TCINTEN_SHIFT);

        if (syncType == EDMA3_DRV_SYNC_A)
        {
            paramSet.opt &= 0xFFFFFFFBu;
        }
        else
        {
            /* AB Sync Transfer Mode */
            paramSet.opt |= (1 << OPT_SYNCDIM_SHIFT);
        }

        /* Now, write the PaRAM Set. */
        result = EDMA3_DRV_setPaRAM(hEdma, ch2Id, &paramSet);
    }


    /*
    * There is another way to program the PaRAM Set using specific APIs
    * for different PaRAM set entries. It gives user more control and easier
    * to use interface. User can use any of the methods.
    * Below is the alternative way to program the PaRAM Set.
    */

    /*

    if (result == EDMA3_DRV_SOK)
    {
    result = EDMA3_DRV_setSrcParams (hEdma, ch2Id, (uint32_t)(srcBuff2),
    EDMA3_DRV_ADDR_MODE_INCR,
    EDMA3_DRV_W8BIT);
    }

    if (result == EDMA3_DRV_SOK)
    {
    result = EDMA3_DRV_setDestParams (hEdma, ch2Id,
    (uint32_t)(dstBuff2),
    EDMA3_DRV_ADDR_MODE_INCR,
    EDMA3_DRV_W8BIT);
    }

    if (result == EDMA3_DRV_SOK)
    {
    result = EDMA3_DRV_setSrcIndex (hEdma, ch2Id, srcbidx, srccidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
    result =  EDMA3_DRV_setDestIndex (hEdma, ch2Id, desbidx, descidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
    if (syncType == EDMA3_DRV_SYNC_A)
    {
    result = EDMA3_DRV_setTransferParams (hEdma, ch2Id, acnt, bcnt,
    ccnt,
    BRCnt,EDMA3_DRV_SYNC_A);
    }
    else
    {
    result = EDMA3_DRV_setTransferParams (hEdma, ch2Id, acnt, bcnt,
    ccnt,
    BRCnt,EDMA3_DRV_SYNC_AB);
    }
    }

    if (result == EDMA3_DRV_SOK)
    {
    result = EDMA3_DRV_setOptField (hEdma, ch2Id,
    EDMA3_DRV_OPT_FIELD_TCINTEN, 1u);
    }

    if (result == EDMA3_DRV_SOK)
    {
    result = EDMA3_DRV_setOptField (hEdma, ch2Id,
    EDMA3_DRV_OPT_FIELD_ITCINTEN, 1u);
    }

    */


    /* Link both the channels. */
    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_linkChannel (hEdma, ch1Id, ch2Id);
    }


    /*
    * Since the transfer is going to happen in Manual mode of EDMA3
    * operation, we have to 'Enable the Transfer' multiple times.
    * Number of times depends upon the Mode (A/AB Sync)
    * and the different counts.
    */
    if (result == EDMA3_DRV_SOK)
    {
        /*Need to activate next param*/
        if (syncType == EDMA3_DRV_SYNC_A)
        {
            numenabled = bcnt * ccnt;
        }
        else
        {
            /* AB Sync Transfer Mode */
            numenabled = ccnt;
        }

        for (i = 0; i < numenabled; i++)
        {
            irqRaised1 = 0;

            /*
            * Now enable the transfer for Master channel as many times
            * as calculated above.
            */
            result = EDMA3_DRV_enableTransfer (hEdma, ch1Id,
                EDMA3_DRV_TRIG_MODE_MANUAL);
            if (result != EDMA3_DRV_SOK)
            {
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("error from edma3_test_with_link\n\r\n");
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }

            edma3OsSemTake(AppSemHandle1, EDMA3_OSSEM_NO_TIMEOUT);
            while (irqRaised1 == 0)
            {
                /* Wait for the Completion ISR on Master Channel. */
                printf ("waiting for interrupt...\n");
            }

            /* Check the status of the completed transfer */
            if (irqRaised1 < 0)
            {
                /* Some error occured, break from the FOR loop. */
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("\r\nedma3_test_with_link: Event Miss Occured!!!\r\n");
#endif  /* EDMA3_DRV_DEBUG */

                /* Clear the error bits first */
                result = EDMA3_DRV_clearErrorBits (hEdma, ch1Id);

                break;
            }
        }
    }


    /**
    * Now the transfer on Master channel is finished.
    * Trigger next (LINK) param.
    */
    if (EDMA3_DRV_SOK == result)
    {
        for (i = 0; i < numenabled; i++)
        {
            irqRaised1 = 0;

            /*
            * Enable the transfer for LINK channel as many times
            * as calculated above.
            */
            result = EDMA3_DRV_enableTransfer (hEdma, ch1Id,
                EDMA3_DRV_TRIG_MODE_MANUAL);
            if (result != EDMA3_DRV_SOK)
            {
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("error from edma3_test_with_link\n\r\n");
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }

            edma3OsSemTake(AppSemHandle1, EDMA3_OSSEM_NO_TIMEOUT);
            while (irqRaised1 == 0)
            {
                /* Wait for the Completion ISR on the Link Channel. */
                printf ("waiting for interrupt...\n");	
            }

            /* Check the status of the completed transfer */
            if (irqRaised1 < 0)
            {
                /* Some error occured, break from the FOR loop. */
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("\r\nedma3_test_with_link: Event Miss Occured!!!\r\n");
#endif  /* EDMA3_DRV_DEBUG */

                /* Clear the error bits first */
                result = EDMA3_DRV_clearErrorBits (hEdma, ch2Id);

                break;
            }
        }
    }



    /* Match the Source and Destination Buffers. */
    if (EDMA3_DRV_SOK == result)
    {
        for (i = 0; i < (acnt*bcnt*ccnt); i++)
        {
            if (srcBuff1[i] != dstBuff1[i])
            {
                Istestpassed1 = 0u;
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF("edma3_test_with_link: Data write-read " \
                    "matching FAILED at i = %d " \
                    "(srcBuff1 -> dstBuff1)\r\n", i);
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }
        }
        if (i == (acnt*bcnt*ccnt))
        {
            Istestpassed1 = 1u;
        }


        for (i = 0; i < (acnt*bcnt*ccnt); i++)
        {
            if (srcBuff2[i] != dstBuff2[i])
            {
                Istestpassed2 = 0;
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF("edma3_test_with_link: Data write-read " \
                    "matching FAILED at i = %d " \
                    "(srcBuff2 -> dstBuff2)\r\n", i);
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }
        }
        if (i == (acnt*bcnt*ccnt))
        {
            Istestpassed2 = 1u;
        }


        /* Free the previously allocated channels. */
        result = EDMA3_DRV_freeChannel (hEdma, ch1Id);
        if (result != EDMA3_DRV_SOK)
        {
#ifdef EDMA3_DRV_DEBUG
            EDMA3_DRV_PRINTF("edma3_test_with_link: EDMA3_DRV_freeChannel() " \
                "for ch1 FAILED, error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
        }
        else
        {
            result = EDMA3_DRV_freeChannel (hEdma, ch2Id);
            if (result != EDMA3_DRV_SOK)
            {
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF("edma3_test_with_link: " \
                    "EDMA3_DRV_freeChannel() for ch 2 FAILED, " \
                    "error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
            }
        }
    }


    if((Istestpassed1 == 1u) && (Istestpassed2 == 1u))
    {
#ifdef EDMA3_DRV_DEBUG
        EDMA3_DRV_PRINTF("edma3_test_with_link PASSED\r\n");
#endif  /* EDMA3_DRV_DEBUG */
    }
    else
    {
#ifdef EDMA3_DRV_DEBUG
        EDMA3_DRV_PRINTF("edma3_test_with_link FAILED\r\n");
#endif  /* EDMA3_DRV_DEBUG */
        result = ((EDMA3_DRV_SOK == result) ?
                    EDMA3_DATA_MISMATCH_ERROR : result);
    }
    return result;
}
