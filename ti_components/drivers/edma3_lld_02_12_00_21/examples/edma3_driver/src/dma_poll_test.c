/*
* dma_poll_test.c
*
* Test case demonstrating the poll mode scenario. User has requested a data 
* transfer without giving any callback function. After programming and 
* enabling the channel, he uses different APIs (meant to be used in poll mode)
* to check the status of ongoing transfer. Interrupt will NOT occur in this 
* case.
*
* Copyright (C) 2009-2018 Texas Instruments Incorporated - http://www.ti.com/
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

#define EDMA3_DRV_DMA_CHANNEL_USR_REQ     (10)
/**
*  \brief   EDMA3 mem-to-mem data copy test case, using a DMA channel.
*              This test case doesnot rely on the callback mechanism.
*              Instead, it Polls the IPR register to check the transfer
*              completion status.
*
*  \param  acnt        [IN]      Number of bytes in an array
*  \param  bcnt        [IN]      Number of arrays in a frame
*  \param  ccnt        [IN]      Number of frames in a block
*  \param  syncType    [IN]      Synchronization type (A/AB Sync)
*
*  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
*/
EDMA3_DRV_Result edma3_test_poll_mode(
                                      EDMA3_DRV_Handle hEdma,
                                      uint32_t acnt,
                                      uint32_t bcnt,
                                      uint32_t ccnt,
                                      EDMA3_DRV_SyncType syncType)
{
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;
    uint32_t chId = 0;
    uint32_t tcc = 0;
    int i;
    uint32_t count;
    uint32_t Istestpassed = 0u;
    uint32_t numenabled = 0;
    uint32_t BRCnt = 0;
    int srcbidx = 0, desbidx = 0;
    int srccidx = 0, descidx = 0;
#ifdef EDMA3_RES_USER_REQ
    uint32_t paRAMId = 0;
#endif


    srcBuff1 = (signed char*) GLOBAL_ADDR(_srcBuff1);
    dstBuff1 = (signed char*) GLOBAL_ADDR(_dstBuff1);

    /* Initalize source and destination buffers */
    for (count = 0u; count < (acnt*bcnt*ccnt); count++)
    {
        srcBuff1[count] = (int)count+5;
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
    tcc = EDMA3_DRV_TCC_ANY;
    chId = EDMA3_DRV_DMA_CHANNEL_ANY;

    /* Request any DMA channel and any TCC */
    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_requestChannel (hEdma, &chId, &tcc,
            (EDMA3_RM_EventQueue)0,
            NULL, NULL);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setSrcParams (hEdma, chId, (uint32_t)(srcBuff1),
            EDMA3_DRV_ADDR_MODE_INCR,
            EDMA3_DRV_W8BIT);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setDestParams (hEdma, chId, (uint32_t)(dstBuff1),
            EDMA3_DRV_ADDR_MODE_INCR,
            EDMA3_DRV_W8BIT);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setSrcIndex (hEdma, chId, srcbidx, srccidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result =  EDMA3_DRV_setDestIndex (hEdma, chId, desbidx, descidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
        if (syncType == EDMA3_DRV_SYNC_A)
        {
            result = EDMA3_DRV_setTransferParams (hEdma, chId, acnt, bcnt, ccnt,
                BRCnt, EDMA3_DRV_SYNC_A);
        }
        else
        {
            result = EDMA3_DRV_setTransferParams (hEdma, chId, acnt, bcnt, ccnt,
                BRCnt, EDMA3_DRV_SYNC_AB);
        }
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setOptField (hEdma, chId,
            EDMA3_DRV_OPT_FIELD_TCINTEN, 1u);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setOptField (hEdma, chId,
            EDMA3_DRV_OPT_FIELD_ITCINTEN, 1u);
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
            /*
            * Now enable the transfer as many times as calculated above.
            */
            result = EDMA3_DRV_enableTransfer (hEdma, chId,
                EDMA3_DRV_TRIG_MODE_MANUAL);
            if (result != EDMA3_DRV_SOK)
            {
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("edma3_test_poll_mode: EDMA3_DRV_enableTransfer " \
                    "Failed, error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }


            /* Wait for the Completion Bit to be SET in the IPR/IPRH register. */
            result = EDMA3_DRV_waitAndClearTcc (hEdma, tcc);
            if (result != EDMA3_DRV_SOK)
            {
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("edma3_test_poll_mode: EDMA3_DRV_waitAndClearTcc " \
                    "Failed, error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
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
                Istestpassed = 0u;
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF("edma3_test_poll_mode: Data write-read matching" \
                    "FAILED at i = %d\r\n", i);
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }
        }
        if (i == (acnt*bcnt*ccnt))
        {
            Istestpassed = 1u;
        }


        /* Free the previously allocated channel. */
        result = EDMA3_DRV_freeChannel (hEdma, chId);
        if (result != EDMA3_DRV_SOK)
        {
#ifdef EDMA3_DRV_DEBUG
            EDMA3_DRV_PRINTF("edma3_test_poll_mode: EDMA3_DRV_freeChannel() FAILED, " \
                "error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
        }
    }


    if(Istestpassed == 1u)
    {
#ifdef EDMA3_DRV_DEBUG
        EDMA3_DRV_PRINTF("edma3_test_poll_mode PASSED\r\n");
#endif  /* EDMA3_DRV_DEBUG */
    }
    else
    {
#ifdef EDMA3_DRV_DEBUG
        EDMA3_DRV_PRINTF("edma3_test_poll_mode FAILED\r\n");
#endif  /* EDMA3_DRV_DEBUG */
        result = ((EDMA3_DRV_SOK == result) ?
                    EDMA3_DATA_MISMATCH_ERROR : result);
    }
    return result;
}


/**
*  \brief   EDMA3 mem-to-mem data copy test case with user requested paRAMId
*           using a DMA channel.
*           This test case doesnot rely on the callback mechanism.
*           Instead, it Polls the IPR register to check the transfer
*           completion status.
*
*  \param  edmaInstance [IN]    EDMA3 Instance number
*  \param  acnt        [IN]      Number of bytes in an array
*  \param  bcnt        [IN]      Number of arrays in a frame
*  \param  ccnt        [IN]      Number of frames in a block
*  \param  syncType    [IN]      Synchronization type (A/AB Sync)
*
*  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
*/
EDMA3_DRV_Result edma3_test_user_req_paRAMId(
                                      EDMA3_DRV_Handle hEdma,
                                      uint32_t edmaInstance,
                                      uint32_t acnt,
                                      uint32_t bcnt,
                                      uint32_t ccnt,
                                      EDMA3_DRV_SyncType syncType)
{
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;
    uint32_t chId = 0;
    uint32_t tcc = 0;
    int i;
    uint32_t count;
    uint32_t Istestpassed = 0u;
    uint32_t numenabled = 0;
    uint32_t BRCnt = 0;
    int srcbidx = 0, desbidx = 0;
    int srccidx = 0, descidx = 0;
    uint32_t paRAMId = 0;


    srcBuff1 = (signed char*) GLOBAL_ADDR(_srcBuff1);
    dstBuff1 = (signed char*) GLOBAL_ADDR(_dstBuff1);

    /* Initalize source and destination buffers */
    for (count = 0u; count < (acnt*bcnt*ccnt); count++)
    {
        srcBuff1[count] = (int)count+5;
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
    tcc = EDMA3_DRV_TCC_ANY;

    chId = EDMA3_DRV_DMA_CHANNEL_USR_REQ;

    /* Request any DMA channel and any TCC */
    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_requestChannel (hEdma, &chId, &tcc,
            (EDMA3_RM_EventQueue)0,
            NULL, NULL);

        result = EDMA3_DRV_getAllocatedPARAMId(hEdma, chId, &paRAMId);
        if(result == EDMA3_DRV_SOK)
        {
            printf("\nReserved Channel ID Test\n");
            printf ("The Requested Channel ID: %ld \nThe allocated PARAM Id:%ld\n",chId,paRAMId);

            if (chId == paRAMId)
            {
                printf("The Requested Param ID is allocated for the given Channel\n");
            }
            else
            {
                printf("The Requested Param ID is not allocated as same as the DMA channel\n");
                result = EDMA3_DATA_MISMATCH_ERROR;
            }
            printf("\n");
        }
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setSrcParams (hEdma, chId, (uint32_t)(srcBuff1),
            EDMA3_DRV_ADDR_MODE_INCR,
            EDMA3_DRV_W8BIT);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setDestParams (hEdma, chId, (uint32_t)(dstBuff1),
            EDMA3_DRV_ADDR_MODE_INCR,
            EDMA3_DRV_W8BIT);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setSrcIndex (hEdma, chId, srcbidx, srccidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result =  EDMA3_DRV_setDestIndex (hEdma, chId, desbidx, descidx);
    }

    if (result == EDMA3_DRV_SOK)
    {
        if (syncType == EDMA3_DRV_SYNC_A)
        {
            result = EDMA3_DRV_setTransferParams (hEdma, chId, acnt, bcnt, ccnt,
                BRCnt, EDMA3_DRV_SYNC_A);
        }
        else
        {
            result = EDMA3_DRV_setTransferParams (hEdma, chId, acnt, bcnt, ccnt,
                BRCnt, EDMA3_DRV_SYNC_AB);
        }
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setOptField (hEdma, chId,
            EDMA3_DRV_OPT_FIELD_TCINTEN, 1u);
    }

    if (result == EDMA3_DRV_SOK)
    {
        result = EDMA3_DRV_setOptField (hEdma, chId,
            EDMA3_DRV_OPT_FIELD_ITCINTEN, 1u);
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
            /*
            * Now enable the transfer as many times as calculated above.
            */
            result = EDMA3_DRV_enableTransfer (hEdma, chId,
                EDMA3_DRV_TRIG_MODE_MANUAL);
            if (result != EDMA3_DRV_SOK)
            {
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("edma3_test_user_req_paRAMId: EDMA3_DRV_enableTransfer " \
                    "Failed, error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }


            /* Wait for the Completion Bit to be SET in the IPR/IPRH register. */
            result = EDMA3_DRV_waitAndClearTcc (hEdma, tcc);
            if (result != EDMA3_DRV_SOK)
            {
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF ("edma3_test_user_req_paRAMId: EDMA3_DRV_waitAndClearTcc " \
                    "Failed, error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
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
                Istestpassed = 0u;
#ifdef EDMA3_DRV_DEBUG
                EDMA3_DRV_PRINTF("edma3_test_user_req_paRAMId: Data write-read matching" \
                    "FAILED at i = %d\r\n", i);
#endif  /* EDMA3_DRV_DEBUG */
                break;
            }
        }
        if (i == (acnt*bcnt*ccnt))
        {
            Istestpassed = 1u;
        }


        /* Free the previously allocated channel. */
        result = EDMA3_DRV_freeChannel (hEdma, chId);
        if (result != EDMA3_DRV_SOK)
        {
#ifdef EDMA3_DRV_DEBUG
            EDMA3_DRV_PRINTF("edma3_test_user_req_paRAMId: EDMA3_DRV_freeChannel() FAILED, " \
                "error code: %d\r\n", result);
#endif  /* EDMA3_DRV_DEBUG */
        }
    }


    if(Istestpassed == 1u)
    {
#ifdef EDMA3_DRV_DEBUG
        EDMA3_DRV_PRINTF("edma3_test_user_req_paRAMId PASSED\r\n");
#endif  /* EDMA3_DRV_DEBUG */
    }
    else
    {
#ifdef EDMA3_DRV_DEBUG
        EDMA3_DRV_PRINTF("edma3_test_user_req_paRAMId FAILED\r\n");
#endif  /* EDMA3_DRV_DEBUG */
        result = ((EDMA3_DRV_SOK == result) ?
                    EDMA3_DATA_MISMATCH_ERROR : result);
    }
    return result;
}
