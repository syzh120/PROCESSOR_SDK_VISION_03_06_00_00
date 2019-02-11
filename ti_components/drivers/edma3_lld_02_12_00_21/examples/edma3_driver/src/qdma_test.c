/*
* qdma_test.c
*
* EDMA3 mem-to-mem data copy test case, using a QDMA channel.
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
extern signed char   _dstBuff1[MAX_BUFFER_SIZE];

extern signed char *srcBuff1;
extern signed char *dstBuff1;
extern void *AppSemHandle1;

/**
*  \brief   EDMA3 mem-to-mem data copy test case, using a QDMA channel.
*
*
*  \param  acnt        [IN]      Number of bytes in an array
*  \param  bcnt        [IN]      Number of arrays in a frame
*  \param  ccnt        [IN]      Number of frames in a block
*  \param  syncType    [IN]      Synchronization type (A/AB Sync)
*
*  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
*/
EDMA3_DRV_Result qdma_test(
                           EDMA3_DRV_Handle hEdma,
                           uint32_t acnt,
                           uint32_t bcnt,
                           uint32_t ccnt,
                           EDMA3_DRV_SyncType syncType)
{
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;
    uint32_t i;
    uint32_t count;
    uint32_t Istestpassed = 0u;
    uint32_t numenabled = 0;
    uint32_t qCh1Id=0;
    uint32_t qTcc1 = 0;
    uint32_t BRCnt = 0;
    int srcbidx = 0, desbidx = 0;
    int srccidx = 0, descidx = 0;
    static signed char* tmpSrcBuff1 = NULL;
    static signed char* tmpDstBuff1 = NULL;

    srcBuff1 = (signed char*) GLOBAL_ADDR(_srcBuff1);
    dstBuff1 = (signed char*) GLOBAL_ADDR(_dstBuff1);

    tmpSrcBuff1 = srcBuff1;
    tmpDstBuff1 = dstBuff1;

    /* Initalize source and destination buffers */
    for (count = 0u; count < (acnt*bcnt*ccnt); count++)
    {
        srcBuff1[count] = (int)count+2;
        /**
        * No need to initialize the destination buffer as it is being invalidated.
        dstBuff1[count] = initval;
        */
    }

#ifdef EDMA3_ENABLE_DCACHE
    /*
    * Note: These functions are required if the buffer is in DDR.
    * For other cases, where buffer is NOT in DDR, user
    * may or may not require the below functions.
    */
    /* Flush the Source Buffer */
    if (result == EDMA3_DRV_SOK)
    {
        result = Edma3_CacheFlush((uint32_t)srcBuff1, (acnt*bcnt*ccnt));
    }

    /* Invalidate the Destination Buffer */
    if (result == EDMA3_DRV_SOK)
    {
        result = Edma3_CacheInvalidate((uint32_t)dstBuff1, (acnt*bcnt*ccnt));
    }
#endif  /* EDMA3_ENABLE_DCACHE */


    irqRaised1 = 0;

    /* Set B count reload as B count. */
    BRCnt = bcnt;
    /* Setting up the SRC/DES Index */
    srcbidx = (int)acnt;
    desbidx = (int)acnt;

    if (syncType == EDMA3_DRV_SYNC_A)
    {
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
            (EDMA3_RM_EventQueue)0, &callback1,
            NULL);
    }

    if (result == EDMA3_DRV_SOK)
    {
        /* Set QDMA Trigger Word as Destination Address */
        result =  EDMA3_DRV_setQdmaTrigWord (hEdma, qCh1Id,
            EDMA3_RM_QDMA_TRIG_DST);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setSrcIndex (hEdma, qCh1Id, srcbidx, srccidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result =  EDMA3_DRV_setDestIndex (hEdma, qCh1Id, desbidx, descidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
        if (syncType == EDMA3_DRV_SYNC_A)
        {
            result = EDMA3_DRV_setTransferParams (hEdma, qCh1Id, acnt, bcnt,
                ccnt, BRCnt, EDMA3_DRV_SYNC_A);
        }
        else
        {
            /* AB Sync Transfer Mode */
            result = EDMA3_DRV_setTransferParams (hEdma, qCh1Id, acnt, bcnt,
                ccnt, BRCnt, EDMA3_DRV_SYNC_AB);
        }
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


    /*
    * Since the transfer is going to happen in QDMA mode of EDMA3
    * operation, we have to "Trigger" the transfer multiple times.
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

        for (i = 0u; i < numenabled; i++)
        {
            irqRaised1 = 0u;

            if (i == (numenabled-1u))
            {
                /**
                * Since OPT.STATIC field should be SET for isolated QDMA
                * transfers or for the final transfer in a linked list of QDMA
                * transfers, do the needful for the last request.
                */
                result = EDMA3_DRV_setOptField (hEdma, qCh1Id,
                    EDMA3_DRV_OPT_FIELD_STATIC, 1u);
            }

            /* Write to the Source Address */
            result = EDMA3_DRV_setSrcParams (hEdma, qCh1Id,
                (uint32_t)(srcBuff1),
                EDMA3_DRV_ADDR_MODE_INCR,
                EDMA3_DRV_W8BIT);
            /*
            * Now trigger the QDMA channel by writing to the Trigger
            * Word which is set as Destination Address.
            */
            if (result == EDMA3_DRV_SOK)
            {
                result = EDMA3_DRV_setPaRAMEntry (hEdma, qCh1Id,
                    EDMA3_DRV_PARAM_ENTRY_DST,
                    (uint32_t)(dstBuff1));
                if (result != EDMA3_DRV_SOK)
                {
                    printf ("error from qdma_test\n\r\n");
                    break;
                }
            }

            /* Wait for the Completion ISR. */
            edma3OsSemTake(AppSemHandle1, EDMA3_OSSEM_NO_TIMEOUT);
            while (irqRaised1 == 0)
            {
                /* Wait for the Completion ISR. */
                printf ("waiting for interrupt...\n");
            }

            /* Check the status of the completed transfer */
            if (irqRaised1 < 0)
            {
                /* Some error occured, break from the FOR loop. */
                printf ("\r\nqdma_test: Event Miss Occured!!!\r\n");

                /* Clear the error bits first */
                result = EDMA3_DRV_clearErrorBits (hEdma, qCh1Id);

                break;
            }

            /**
            * Now, update the source and destination addresses for next
            * "Trigger".
            */
            srcBuff1 += srccidx;
            dstBuff1 += descidx;
        }
    }

    if (result == EDMA3_DRV_SOK)
    {
        /* Restore the src and dest buffers */
        srcBuff1 = tmpSrcBuff1;
        dstBuff1 = tmpDstBuff1;

        /* Match the Source and Destination Buffers. */
        for (i = 0u; i < (acnt*bcnt*ccnt); i++)
        {
            if (srcBuff1[i] != dstBuff1[i])
            {
                Istestpassed = 0u;
                printf("qdma_test: Data write-read matching FAILED" \
                    " at i = %d\r\n", (int)i);
                break;
            }
        }
        if (i == (acnt*bcnt*ccnt))
        {
            Istestpassed = 1u;
        }

        /* Free the previously allocated channel. */
        result = EDMA3_DRV_freeChannel (hEdma, qCh1Id);
        if (result != EDMA3_DRV_SOK)
        {
            printf("qdma_test: EDMA3_DRV_freeChannel() FAILED, error code: %d\r\n", (int)result);
        }
    }

    if(Istestpassed == 1u)
    {
        printf("qdma_test PASSED\r\n");
    }
    else
    {
        printf("qdma_test FAILED\r\n");
        result = ((EDMA3_DRV_SOK == result) ?
                    EDMA3_DATA_MISMATCH_ERROR : result);
    }

    return result;
}
