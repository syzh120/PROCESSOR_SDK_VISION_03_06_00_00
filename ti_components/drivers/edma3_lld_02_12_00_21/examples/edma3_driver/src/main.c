/*
* main.c
*
* This file contains the test / demo code to demonstrate the EDMA3 driver
* functionality on DSP/BIOS 6.
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

#include <xdc/std.h>
#include <stdio.h>
#include <string.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>

#include "sample.h"
#if defined(_TMS320C6X)
extern far const uint32_t numEdma3Instances;
#else
extern const uint32_t numEdma3Instances;
#endif

#ifdef SOC_AM335x
#define WR_MEM_32(addr, data) *(unsigned int*)(addr) = (unsigned int)(data)

#define PRCM_BASE_ADDR       (0x44E00000)
#define CM_PER_TPTC0_CLKCTRL (PRCM_BASE_ADDR +0x0024)
#define CM_PER_TPCC_CLKCTRL  (PRCM_BASE_ADDR +0x00BC)
#define CM_PER_TPTC1_CLKCTRL (PRCM_BASE_ADDR +0x00FC)
#define CM_PER_TPTC2_CLKCTRL (PRCM_BASE_ADDR +0x0100)

/*To enable EDMA3 Clock Module */
static void edma3PRCMEnable();
#endif

/**
* DSP instance number on which the executable is running. Its value is
* determined by reading the processor specific register DNUM.
*/
uint32_t dsp_num_tmp;
/* To find out the DSP# */
extern unsigned short determineProcId();
extern EDMA3_DRV_InstanceInitConfig sampleInstInitConfig[][EDMA3_MAX_REGIONS];
extern EDMA3_RM_InstanceInitConfig defInstInitConfig [][EDMA3_MAX_REGIONS];
/* External Global Configuration Structure */
extern EDMA3_DRV_GblConfigParams sampleEdma3GblCfgParams[];

EDMA3_DRV_Result edma3MemToMemCpytest (EDMA3_DRV_Handle hEdma);
extern void *AppSemHandle1;
extern void *AppSemHandle2;

/*
* Local References
*/
static void tskHeartBit(void);
void echo(void);

int main()
{
    Task_create((Task_FuncPtr)echo, NULL, NULL);

    BIOS_start();

    return 0;
}

static void printWelcomeBanner(void)
{
    /* Welcome Message */
    printf("***************************************************************\n\r");
    printf("*                                                             *\n\r");
    printf("*                            ****                             *\n\r");
    printf("*                            ****                             *\n\r");
    printf("*                            ******o***                       *\n\r");
    printf("*                      ********_///_****                      *\n\r");
    printf("*                      ***** /_//_/ ****                      *\n\r");
    printf("*                       ** ** (__/ ****                       *\n\r");
    printf("*                           *********                         *\n\r");
    printf("*                            ****                             *\n\r");
    printf("*                            ***                              *\n\r");
    printf("*                                                             *\n\r");
    printf("*                     TI EDMA3 LOW LEVEL DRIVER               *\n\r");
    printf("*                     Version: 0x%x                      *\n\r",(unsigned int)EDMA3_DRV_getVersion());
    printf("*    %s     *\n\r",EDMA3_DRV_getVersionStr());
    printf("*                                                             *\n\r");
    printf("*                                                             *\n\r");
    printf("*       For issues on TI EDMA3 LLD, contact TII PSP Team      *\n\r");
    printf("*                                                             *\n\r");
    printf("*                                                             *\n\r");
    printf("*                                                             *\n\r");
    printf("***************************************************************\n\r");
    printf("\r\n\r\n");
}

/**
*  \brief   This function determines if testing on a EDMA3 instance will be bypassed.
*           When there are no EDMA channels allocated for the core from the given EDMA3 
*           instance, testing shall be bypassed.
*
*  \return  TRUE if bypass; FALSE if testing will done.
*/
uint32_t bypassCore(uint32_t edmaInstNum)
{
    uint32_t i, bypassFlag = 1;

#ifndef EDMA3_DRV_USE_DEF_RM_CFG
    EDMA3_DRV_InstanceInitConfig *instanceConfig = NULL;
#else
    EDMA3_RM_InstanceInitConfig  *rmInstInitCfg = NULL;
#endif

    /* DSP instance number */
    dsp_num_tmp = determineProcId();

#ifndef EDMA3_DRV_USE_DEF_RM_CFG
    /* configuration structure for the Driver */
    instanceConfig = &sampleInstInitConfig[edmaInstNum][dsp_num_tmp];
    for (i = 0; i < EDMA3_MAX_DMA_CHAN_DWRDS; i++)
    {
        if(instanceConfig->ownDmaChannels[i])
            bypassFlag = 0;
    }
#else
    /* configuration structure for the Driver */
    rmInstInitCfg = &defInstInitConfig[edmaInstNum][dsp_num_tmp];
    for (i = 0; i < EDMA3_MAX_DMA_CHAN_DWRDS; i++)
    {
        if(rmInstInitCfg->ownDmaChannels[i])
            bypassFlag = 0;
    }
#endif

    return (bypassFlag);
}


void echo()
{
    EDMA3_DRV_Result edmaResult = EDMA3_DRV_SOK;
    uint32_t i, bypass;
    uint32_t count=0;
    uint32_t edmaInstance = 0;
    EDMA3_DRV_Handle hEdma[MAX_NUM_EDMA_INSTANCES];
    EDMA3_DRV_Handle hndEdma = NULL;
    Semaphore_Params semParams;

    memset(hEdma,0,sizeof(hEdma));

#ifdef SOC_AM335x
    edma3PRCMEnable();
#endif

    /* Print the Welcome Message */
    printWelcomeBanner();

    Semaphore_Params_init(&semParams);
    edmaResult = edma3OsSemCreate(0, &semParams, &AppSemHandle1);
    if((edmaResult != EDMA3_DRV_SOK) || (AppSemHandle1 == NULL))
    {
        printf("Error initializing the Application Semaphore handle\n");
        return;
    }
    edmaResult = edma3OsSemCreate(0, &semParams, &AppSemHandle2);
    if((edmaResult != EDMA3_DRV_SOK) || (AppSemHandle2 == NULL))
    {
        printf("Error initializing the Application Semaphore handle\n");
        return;
    }

    if(numEdma3Instances > MAX_NUM_EDMA_INSTANCES)
    {
        printf("Error numEdma3Instances:%d > MAX_NUM_EDMA_INSTANCES: %d\n", (int)numEdma3Instances, MAX_NUM_EDMA_INSTANCES);
        return;
    }

    for (i = 0; i < numEdma3Instances; i++)
    {
        bypass = bypassCore(i);
        if(sampleEdma3GblCfgParams[i].numRegions > 1)
        {
            /* For multi core test init and de-init only once per test 
            * for a core. 
            */
            if(bypass)
            {
                printf("Bypassing init for Core %d on EDMA3 instance %d\n", (int)dsp_num_tmp, (int)i);
                continue;
            }

            hEdma[i] = edma3init(i, &edmaResult);
            if (hEdma[i])
            {
                printf("edma3init() Passed\n");
            }
            else
            {
                printf("edma3init() Failed, error code: %d\n", (int)edmaResult);
            }
        }
    }


    for (count=0; count<10; count++)
    {
        printf ("\nCount = %d\n",(int)count);

        for (i = 0; i < numEdma3Instances; i++)
        {
            bypass = bypassCore(i);
            if(bypass)
            {
                printf("Bypass Core %d on EDMA3 instance %d\n", (int)dsp_num_tmp, (int)i);
            }
            else
            {
                if(sampleEdma3GblCfgParams[i].numRegions == 1)
                {
                    /* Single Region Config Do Init and Deinit test for each iteration */
                    hEdma[i] = edma3init(i, &edmaResult);
                    if (hEdma[i])
                    {
                        printf("edma3init() Passed\n");
                    }
                    else
                    {
                        printf("edma3init() Failed, error code: %d\n", (int)edmaResult);
                    }
                }


                if (edmaResult == EDMA3_DRV_SOK)
                {
                    printf("\nStart -> EDMA3 Test memory to memory copy on Instance %d\n",(int)i);

                    edmaResult = edma3MemToMemCpytest(hEdma[i]);

                    if (EDMA3_DRV_SOK != edmaResult)
                    {
                        /* Report EDMA Error */
                        printf("edma3MemToMemCpytest() FAILED!!!!!!!!!!!!!!!!\n");
                        return;
                    }
                    else
                    {
                        printf("edma3MemToMemCpytest() Passed\n");
                    }

                    printf("\nEnd -> EDMA3 Test memory to memory copy\n\n");
                }

                if(sampleEdma3GblCfgParams[i].numRegions == 1)
                {
                    /* Single Region Config Do deinit */
                    /* De-init EDMA3 */
                    if (hEdma[i])
                    {
                        edmaResult = edma3deinit(i, hEdma[i]);
                        if (edmaResult != EDMA3_DRV_SOK)
                        {
                            printf("edma3deinit() Failed, error code: %d\n", (int)edmaResult);
                        }
                        else
                        {
                            printf("edma3deinit() Passed\n");
                        }
                    }
                }
            }
        }
    }

    for (i = 0; i < numEdma3Instances; i++)
    {
        if(sampleEdma3GblCfgParams[i].numRegions > 1)
        {
            /* Multi core Do deinit */
            /* De-init EDMA3 */
            if (hEdma[i])
            {
                edmaResult = edma3deinit(i, hEdma[i]);
                if (edmaResult != EDMA3_DRV_SOK)
                {
                    printf("edma3deinit() Failed, error code: %d\n", (int)edmaResult);
                }
                else
                {
                    printf("edma3deinit() Passed\n");
                }
            }
        }
    }

    /* Mapping DMA channels to corresponding paRAM Id. The user can request for 
     * any DAM channel to map with the paRAM Id as same as the channel number
     */
    for (count = 0u; count < EDMA3_MAX_DMA_CH; count++)
    {
        sampleEdma3GblCfgParams[edmaInstance].dmaChannelPaRAMMap[count] = count;
    }

    /*EDMA3 Initialization*/
    hndEdma = edma3init(edmaInstance, &edmaResult);
    if (hndEdma)
    {
        printf("edma3init() Passed\n");

        /* User request PaRAMId test */
        if (edmaResult == EDMA3_DRV_SOK)
        {
            edmaResult = edma3_test_user_req_paRAMId(hndEdma, edmaInstance,
                      MAX_ACOUNT, MAX_BCOUNT, MAX_CCOUNT, EDMA3_DRV_SYNC_A);
        }

        if (edmaResult == EDMA3_DRV_SOK)
        {
            printf ("edma3_test_user_req_paRAMId Passed\r\n");
        }
        else
        {
            printf ("edma3_test_user_req_paRAMId Failed\r\n");
        }

        /*EDMA3 deinitialization */
        edmaResult = edma3deinit(edmaInstance, hndEdma);
        if (edmaResult != EDMA3_DRV_SOK)
        {
            printf("edma3deinit() Failed, error code: %d\n", (int)edmaResult);
        }
        else
        {
            printf("edma3deinit() Passed\n");
        }
    }
    else
    {
        printf("edma3init() Failed, error code: %d\n", (int)edmaResult);
    }

    /* Start the Heart Beat Print */
    tskHeartBit();

    return;
}


/**
*  \brief   Main sample test case which will call other EDMA3 test cases.
*              If one wants to call Edma3 test cases, include this main
*              test case only.
*
*  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
*/
EDMA3_DRV_Result edma3MemToMemCpytest (EDMA3_DRV_Handle hEdma)
{
    EDMA3_DRV_Result result = EDMA3_DRV_SOK;

    if (hEdma == NULL)
    {
        //result = EDMA3_DRV_E_INVALID_PARAM;
        return result;
    }

    /* Edma test without linking, async, incr mode */
    if (result == EDMA3_DRV_SOK)
    {
        result = edma3_test(hEdma, MAX_ACOUNT, MAX_BCOUNT, MAX_CCOUNT, EDMA3_DRV_SYNC_A);

        if (result == EDMA3_DRV_SOK)
        {
            printf ("edma3_test (without linking) Passed\r\n");
        }
        else
        {
            printf ("edma3_test (without linking) Failed\r\n");
        }
    }

    /* Edma test with linking, async, incr mode */
    if (result == EDMA3_DRV_SOK)
    {
        result = edma3_test_with_link(hEdma, MAX_ACOUNT, MAX_BCOUNT, MAX_CCOUNT, EDMA3_DRV_SYNC_A);

        if (result == EDMA3_DRV_SOK)
        {
            printf ("edma3_test_with_link Passed\r\n");
        }
        else
        {
            printf ("edma3_test_with_link Failed\r\n");
        }
    }

    /* Qdma test, async, incr mode */
    if (result == EDMA3_DRV_SOK)
    {
        result = qdma_test(hEdma, MAX_ACOUNT, MAX_BCOUNT, MAX_CCOUNT, EDMA3_DRV_SYNC_A);

        if (result == EDMA3_DRV_SOK)
        {
            printf ("qdma_test Passed\r\n");
        }
        else
        {
            printf ("qdma_test Failed\r\n");
        }
    }

    /* Qdma test with linking, async, incr mode */
    if (result == EDMA3_DRV_SOK)
    {
        result = qdma_test_with_link (hEdma, MAX_ACOUNT, MAX_BCOUNT, MAX_CCOUNT, EDMA3_DRV_SYNC_A);

        if (result == EDMA3_DRV_SOK)
        {
            printf ("qdma_test_with_link Passed\r\n");
        }
        else
        {
            printf ("qdma_test_with_link Failed\r\n");
        }
    }

    /* DMA channels with chaining test. */
    if (result == EDMA3_DRV_SOK)
    {
        result = edma3_test_with_chaining(hEdma, MAX_ACOUNT, MAX_BCOUNT, MAX_CCOUNT, EDMA3_DRV_SYNC_A);

        if (result == EDMA3_DRV_SOK)
        {
            printf ("edma3_test_with_chaining Passed\r\n");
        }
        else
        {
            printf ("edma3_test_with_chaining Failed\r\n");
        }
    }

    /* DMA channels using Polling mode test. */
    if (result == EDMA3_DRV_SOK)
    {
        result = edma3_test_poll_mode(hEdma, MAX_ACOUNT, MAX_BCOUNT, MAX_CCOUNT, EDMA3_DRV_SYNC_A);

        if (result == EDMA3_DRV_SOK)
        {
            printf ("edma3_test_poll_mode Passed\r\n");
        }
        else
        {
            printf ("edma3_test_poll_mode Failed\r\n");
        }
    }

    /* DMA channels in using ping-pong buffers test. */
    if (result == EDMA3_DRV_SOK)
    {
        result = edma3_test_ping_pong_mode(hEdma);

        if (result == EDMA3_DRV_SOK)
        {
            printf ("edma3_test_ping_pong_mode Passed\r\n");
        }
        else
        {
            printf ("edma3_test_ping_pong_mode Failed\r\n");
        }
    }

    /* Misc tests. */
    if (result == EDMA3_DRV_SOK)
    {
        result = edma3_misc_test(hEdma);

        if (result == EDMA3_DRV_SOK)
        {
            printf ("edma3_misc_test Passed\r\n");
        }
        else
        {
            printf ("edma3_misc_test Failed\r\n");
        }
    }

    return result;
}


void tskHeartBit()
{
    static uint32_t counter = 0u;

    while (counter < 0x1000000u)
    {
        printf("\r\n\r\n!!! EDMA3 LLD HrtBt %x", (unsigned int)counter);
        counter++;
    }
}

#ifdef SOC_AM335x
/*To enable EDMA3 Clock Module of AM335x*/
static void edma3PRCMEnable()
{
    WR_MEM_32(CM_PER_TPCC_CLKCTRL, 2);
    WR_MEM_32(CM_PER_TPTC0_CLKCTRL ,   2);
    WR_MEM_32(CM_PER_TPTC1_CLKCTRL ,   2);
    WR_MEM_32(CM_PER_TPTC2_CLKCTRL ,   2);
}
#endif
