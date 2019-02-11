/*
* qdma_link_test.c
*
* Test case demonstrating the usgae of QDMA channel for transferring data
* between two memory locations. QDMA channel is linked to a LINK channel.
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
*  \brief   EDMA3 mem-to-mem data copy test case, using a QDMA channel,
*              linked to another LINK channel.
*
*  \param  acnt        [IN]      Number of bytes in an array
*  \param  bcnt        [IN]      Number of arrays in a frame
*  \param  ccnt        [IN]      Number of frames in a block
*  \param  syncType    [IN]      Synchronization type (A/AB Sync)
*
*  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
*/
EDMA3_DRV_Result qdma_test_with_link(
                                     EDMA3_DRV_Handle hEdma,
                                     uint32_t acnt,
                                     uint32_t bcnt,
                                     uint32_t ccnt,
                                     EDMA3_DRV_SyncType syncType)
{
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;
    uint32_t i;
    uint32_t count;
    uint32_t Istestpassed1 = 0u;
    uint32_t Istestpassed2 = 0u;
    uint32_t qCh1Id=0;
    uint32_t qTcc1 = 0;
    uint32_t qCh2Id=0;
    uint32_t qTcc2 = 0;
    uint32_t BRCnt = 0;
    int srcbidx = 0, desbidx = 0;
    int srccidx = 0, descidx = 0;
    uint32_t numenabled = 0;
    static signed char* tmpSrcBuff1 = NULL;
    static signed char* tmpDstBuff1 = NULL;
    static signed char* tmpSrcBuff2 = NULL;
    static signed char* tmpDstBuff2 = NULL;
    uint32_t abCNT = 0;
    uint32_t bcntReloadLinkField = 0x0u;


    srcBuff1 = (signed char*) GLOBAL_ADDR(_srcBuff1);
    dstBuff1 = (signed char*) GLOBAL_ADDR(_dstBuff1);
    srcBuff2 = (signed char*) GLOBAL_ADDR(_srcBuff2);
    dstBuff2 = (signed char*) GLOBAL_ADDR(_dstBuff2);


    /* Store the original pointers for future usage. */
    tmpSrcBuff1 = srcBuff1;
    tmpDstBuff1 = dstBuff1;
    tmpSrcBuff2 = srcBuff2;
    tmpDstBuff2 = dstBuff2;


    /* Initalize source and destination buffers */
    for (count= 0u; count < (acnt*bcnt*ccnt); count++)
    {
        srcBuff1[count] = (int)count+3;
        srcBuff2[count] = (int)count+3;
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


    /* Setup for any QDMA Channel */
    qCh1Id = EDMA3_DRV_QDMA_CHANNEL_ANY;
    qTcc1 = EDMA3_DRV_TCC_ANY;

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_requestChannel (hEdma, &qCh1Id, &qTcc1,
            (EDMA3_RM_EventQueue)0,
            &callback1, NULL);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /* Setup for Channel 2 (Link Channel) */
        qCh2Id = EDMA3_DRV_LINK_CHANNEL;
        qTcc2 = EDMA3_DRV_TCC_ANY;

        result = EDMA3_DRV_requestChannel (hEdma, &qCh2Id, &qTcc2,
            (EDMA3_RM_EventQueue)0,
            &callback1, NULL);
    }

    /* Configure the Link Channel first */
    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setSrcParams (hEdma, qCh2Id,
            (uint32_t)(srcBuff2),
            EDMA3_DRV_ADDR_MODE_INCR,
            EDMA3_DRV_W8BIT);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setDestParams (hEdma, qCh2Id,
            (uint32_t)(dstBuff2),
            EDMA3_DRV_ADDR_MODE_INCR,
            EDMA3_DRV_W8BIT);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setSrcIndex (hEdma, qCh2Id, srcbidx, srccidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setDestIndex (hEdma, qCh2Id, desbidx, descidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
        if (syncType == EDMA3_DRV_SYNC_A)
        {
            result = EDMA3_DRV_setTransferParams (hEdma, qCh2Id, acnt, bcnt,
                ccnt, BRCnt,
                EDMA3_DRV_SYNC_A);
        }
        else
        {
            /* AB Sync Transfer Mode */
            result = EDMA3_DRV_setTransferParams (hEdma, qCh2Id, acnt, bcnt,
                ccnt, BRCnt,
                EDMA3_DRV_SYNC_AB);
        }
    }

    if (result == EDMA3_DRV_SOK)
    {
        /* Enable the Transfer Completion Interrupt on Link Channel */
        result = EDMA3_DRV_setOptField (hEdma, qCh2Id,
            EDMA3_DRV_OPT_FIELD_TCINTEN, 1u);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /**
        * Enable the Intermediate Transfer Completion Interrupt on Link
        * Channel.
        */
        result = EDMA3_DRV_setOptField (hEdma, qCh2Id,
            EDMA3_DRV_OPT_FIELD_ITCINTEN, 1u);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /* Link both the channels. */
        result = EDMA3_DRV_linkChannel (hEdma, qCh1Id, qCh2Id);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /**
        * Now configure the QDMA channel. Here lies the trick. Since QDMA
        * channel is linked to another DMA channel, as soon as transfer on
        * QDMA channel is finished, static field being NOT SET, the associated
        * PaRAM Set will be reloaded with the Linked PaRAM Set. Now, as the
        * reload occurs, the QDMA channel will be triggered due to the write
        * on a specific Trigger Word. We want the trigger to happen immediately
        * after the write, so the trigger word should be chosen in such a way
        * that it should trigger after the COMPLETE PaRAM Set will get copied
        * onto the QDMA Channel PaRAM Set. In that case, only ONE option is
        * there to choose the CCNT as the trigger word. All other trigger
        * words will cause the trigger happen in-between the PaRAM Set is
        * loading. So Set the trigger word as CCNT.
        */
        result = EDMA3_DRV_setQdmaTrigWord (hEdma, qCh1Id,
            EDMA3_RM_QDMA_TRIG_CCNT);
    }


    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setSrcIndex (hEdma, qCh1Id, srcbidx, srccidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setDestIndex (hEdma, qCh1Id, desbidx, descidx);
    }

    abCNT = acnt | ((bcnt & 0xFFFFu) << 16u);

    /* Write ACNT and BCNT */
    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setPaRAMEntry(hEdma, qCh1Id,
            EDMA3_DRV_PARAM_ENTRY_ACNT_BCNT,
            abCNT);
    }

    /* Set the SYNC Mode (A/AB Sync) */
    if (syncType == EDMA3_DRV_SYNC_A)
    {
        result = EDMA3_DRV_setOptField (hEdma, qCh1Id,
            EDMA3_DRV_OPT_FIELD_SYNCDIM, 0u);
    }
    else
    {
        result = EDMA3_DRV_setOptField (hEdma, qCh1Id,
            EDMA3_DRV_OPT_FIELD_SYNCDIM, 1u);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /* Enable Transfer Completion Interrupt */
        result = EDMA3_DRV_setOptField (hEdma, qCh1Id,
            EDMA3_DRV_OPT_FIELD_TCINTEN, 1u);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /* Enable Intermediate Transfer Completion Interrupt */
        result = EDMA3_DRV_setOptField (hEdma, qCh1Id,
            EDMA3_DRV_OPT_FIELD_ITCINTEN, 1u);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /* Set Source Transfer Mode as Increment Mode. */
        result = EDMA3_DRV_setOptField (hEdma, qCh1Id, EDMA3_DRV_OPT_FIELD_SAM,
            EDMA3_DRV_ADDR_MODE_INCR);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /* Set Destination Transfer Mode as Increment Mode. */
        result = EDMA3_DRV_setOptField (hEdma, qCh1Id, EDMA3_DRV_OPT_FIELD_DAM,
            EDMA3_DRV_ADDR_MODE_INCR);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /* Get Link Address. */
        result = EDMA3_DRV_getPaRAMField(hEdma, qCh1Id,
            EDMA3_DRV_PARAM_FIELD_LINKADDR,
            &bcntReloadLinkField);
    }

    bcntReloadLinkField = (bcntReloadLinkField | (BRCnt << 16));

    if (result == EDMA3_DRV_SOK)
    {
        /* Set B Count Reload & Link Address. */
        result = EDMA3_DRV_setPaRAMEntry(hEdma, qCh1Id,
            EDMA3_DRV_PARAM_ENTRY_LINK_BCNTRLD,
            bcntReloadLinkField);
    }


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


    if (numenabled == 1u)
    {
        /**
        * If only one Sync event is required, make the PaRAM Set associated
        * with the LINK channel as Static.
        */
        if (result == EDMA3_DRV_SOK)
        {
            result = EDMA3_DRV_setOptField (hEdma, qCh2Id,
                EDMA3_DRV_OPT_FIELD_STATIC, 1u);
        }

        /**
        * Be Careful!!!
        * PaRAM Set associated with the Master Channel should NOT be
        * set as Static, otherwise the reload will not occur.
        */
    }



    /*
    * Since the transfer is going to happen in QDMA mode of EDMA3
    * operation, we have to "Trigger" the transfer multiple times.
    * Number of times depends upon the Mode (A/AB Sync)
    * and the different counts.
    */
    if (result == EDMA3_DRV_SOK)
    {
        for (i = 0u; i < numenabled; i++)
        {
            irqRaised1 = 0u;

            /* Write to the Source Address */
            result = EDMA3_DRV_setSrcParams (hEdma, qCh1Id,
                (uint32_t)(srcBuff1),
                EDMA3_DRV_ADDR_MODE_INCR,
                EDMA3_DRV_W8BIT);
            if (result != EDMA3_DRV_SOK)
            {
                printf ("error from qdma_test_with_link\r\n\r\n");
                return result;
            }


            /* Write to the Destination Address */
            result = EDMA3_DRV_setDestParams(hEdma, qCh1Id,
                (uint32_t)(dstBuff1),
                EDMA3_DRV_ADDR_MODE_INCR,
                EDMA3_DRV_W8BIT);
            if (result != EDMA3_DRV_SOK)
            {
                printf ("error from qdma_test_with_link\r\n\r\n");
                return result;
            }


            /* Now write to the Trigger Word i.e. CCNT. */
            result = EDMA3_DRV_setPaRAMEntry(hEdma, qCh1Id, EDMA3_DRV_PARAM_ENTRY_CCNT, ccnt);
            if (result != EDMA3_DRV_SOK)
            {
                printf ("error from qdma_test_with_link\r\n\r\n");
                return result;
            }


            /* After this, transfer will start. */

            /**
            * Now, update the source and destination addresses for next
            * "Trigger".
            */
            srcBuff1 += srccidx;
            dstBuff1 += descidx;


            /**
            * Read the current C Count from the PaRAM Set and write it back.
            * In this way, we would write the correct CCNT every time and
            * trigger the transfer also. Since CC will decrement the CCNT
            * after every (ACNT * BCNT) bytes of data transfer, we can use
            * that decremented value to trigger the next transfer.
            * Another option is to take count of CCNT manually (in your code)
            * and write that value.
            * First option seems less error prone.
            */
            result = EDMA3_DRV_getPaRAMField(hEdma, qCh1Id, EDMA3_DRV_PARAM_FIELD_CCNT, &ccnt);
            if (result != EDMA3_DRV_SOK)
            {
                printf ("error from qdma_test_with_link\r\n\r\n");
                return result;
            }
        }
    }


    /**
    * Transfer on the QDMA channel has finished and Link
    * PaRAM Set is loaded on the QDMA channel PaRAM Set.
    * Now for the transfers on the LINK channel,
    * if only one "TRIGGER" is required,
    * that has already been provided by the PaRAM Set
    * upload.
    * For other triggers, we will take care.
    */
    if (result == EDMA3_DRV_SOK)
    {
        /**
        * One trigger has been provided already, so first wait for
        * that transfer to complete.
        */
        edma3OsSemTake(AppSemHandle1, EDMA3_OSSEM_NO_TIMEOUT);
        while (irqRaised1 == 0)
        {
            /* Wait for the Completion ISR for the Master QDMA Channel. */
            printf ("waiting for interrupt...\n");
        }

        /* Check the status of the completed transfer */
        if (irqRaised1 < 0)
        {
            /* Some error occured, clear the error bits. */
            printf ("\r\nqdma_test_with_link: Event Miss Occured!!!\r\n");

            /* Clear the error bits first */
            result = EDMA3_DRV_clearErrorBits (hEdma, qCh1Id);
        }


        if (numenabled == 1u)
        {
            /**
            * Only 1 trigger was required which has been provided
            * already. No need to do anything.
            */
        }
        else
        {
            /**
            * One trigger has been provided already, so take that into account.
            */
            numenabled -= 1u;

            for (i = 0u; i < numenabled; i++)
            {
                irqRaised1 = 0u;

                if (i == (numenabled - 1u))
                {
                    /**
                    * Before providing the last trigger,
                    * make the PaRAM Set static.
                    */
                    result = EDMA3_DRV_setOptField (hEdma, qCh1Id,
                        EDMA3_DRV_OPT_FIELD_STATIC, 1u);
                }

                /**
                * Now, update the source and destination addresses for next
                * "Trigger".
                */
                srcBuff2 += srccidx;
                dstBuff2 += descidx;


                /**
                * Read the current C Count from the PaRAM Set and write it back.
                * In this way, we would write the correct CCNT every time and
                * trigger the transfer also.
                */
                result = EDMA3_DRV_getPaRAMField(hEdma, qCh1Id, EDMA3_DRV_PARAM_FIELD_CCNT, &ccnt);
                if (result != EDMA3_DRV_SOK)
                {
                    printf ("error from qdma_test_with_link\r\n\r\n");
                    return result;
                }


                /* Write to the Source Address */
                result = EDMA3_DRV_setSrcParams (hEdma, qCh1Id,
                    (uint32_t)(srcBuff2),
                    EDMA3_DRV_ADDR_MODE_INCR,
                    EDMA3_DRV_W8BIT);
                if (result != EDMA3_DRV_SOK)
                {
                    printf ("error from qdma_test_with_link\r\n\r\n");
                    return result;
                }


                /* Write to the Destination Address */
                result = EDMA3_DRV_setDestParams(hEdma, qCh1Id,
                    (uint32_t)(dstBuff2),
                    EDMA3_DRV_ADDR_MODE_INCR,
                    EDMA3_DRV_W8BIT);
                if (result != EDMA3_DRV_SOK)
                {
                    printf ("error from qdma_test_with_link\r\n\r\n");
                    return result;
                }


                /* Now write to the Trigger Word i.e. CCNT. */
                result = EDMA3_DRV_setPaRAMEntry(hEdma, qCh1Id, EDMA3_DRV_PARAM_ENTRY_CCNT, ccnt);
                if (result != EDMA3_DRV_SOK)
                {
                    printf ("error from qdma_test_with_link\r\n\r\n");
                    return result;
                }


                /* After this, transfer will start. */
                edma3OsSemTake(AppSemHandle1, EDMA3_OSSEM_NO_TIMEOUT);
                while (irqRaised1 == 0)
                {
                    /* Wait for the Completion ISR for the Link Channel. */
                    printf ("waiting for interrupt...\n");
                }


                /* Check the status of the completed transfer */
                if (irqRaised1 < 0)
                {
                    /* Some error occured, break from the FOR loop. */
                    printf ("\r\nqdma_test_with_link: Event Miss Occured!!!\r\n");

                    /* Clear the error bits first */
                    result = EDMA3_DRV_clearErrorBits (hEdma, qCh1Id);

                    break;
                }
            }
        }
    }


    /* Restore the src and dest buffers */
    srcBuff1 = tmpSrcBuff1;
    dstBuff1 = tmpDstBuff1;
    srcBuff2 = tmpSrcBuff2;
    dstBuff2 = tmpDstBuff2;


    /* Match the Source and Destination Buffers. */
    if (EDMA3_DRV_SOK == result)
    {
        for (i = 0; i < (acnt*bcnt*ccnt); i++)
        {
            if (srcBuff1[i] != dstBuff1[i])
            {
                Istestpassed1 = 0;
                printf("qdma_test_with_link: Data write-read " \
                    "matching FAILED at i = %d " \
                    "(srcBuff1 -> dstBuff1)\r\r\n", (int)i);
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
                printf("qdma_test_with_link: Data write-read " \
                    "matching FAILED at i = %d " \
                    "(srcBuff2 -> dstBuff2)\r\n", (int)i);
                break;
            }
        }
        if (i == (acnt*bcnt*ccnt))
        {
            Istestpassed2 = 1u;
        }
    }


    if (EDMA3_DRV_SOK == result)
    {
        /* Free the previously allocated channels. */
        result = EDMA3_DRV_freeChannel (hEdma, qCh1Id);
        if (result != EDMA3_DRV_SOK)
        {
            printf("qdma_test_with_link: EDMA3_DRV_freeChannel() for qCh1Id FAILED, error code: %d\r\n", (int)result);
        }
        else
        {
            result = EDMA3_DRV_freeChannel (hEdma, qCh2Id);
            if (result != EDMA3_DRV_SOK)
            {
                printf("qdma_test_with_link: EDMA3_DRV_freeChannel() for qCh2Id FAILED, error code: %d\r\n", (int)result);
            }
        }
    }


    if((Istestpassed1 == 1u) && (Istestpassed2 == 1u))
    {
        printf("qdma_test_with_link PASSED\r\n");
    }
    else
    {
        printf("qdma_test_with_link FAILED\r\n");
        result = ((EDMA3_DRV_SOK == result) ?
                    EDMA3_DATA_MISMATCH_ERROR : result);
    }
    return result;
}
