/*
 * main.c
 *
 * Demonstrates how to use DAT APIs, implemented using CSL DAT adapter, with
 * EDMA3 hardware.
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

#include <xdc/std.h>
#include <stdio.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/System.h>

/* Include the legacy csl 2.0 dat header */
#include <csl_dat.h>

/* Include EDMA3 low level driver specific implementation APIs for dat */
#include <csl2_dat_edma3lld.h>

#define SIZE 			(0x4000)
#define NUM_TRANSFERS 	(0x100)

/**
 * EDMA3 Driver Handle, which is used to call all the Driver APIs.
 * It gets initialized during EDMA3 Initialization.
 */
extern EDMA3_DRV_Handle hEdma;

extern EDMA3_DRV_Handle DAT_EDMA3LLD_hEdma;

/*
 * Patterns to fill up in the source buffers
 */
unsigned long long fill1d =   0x1111111111111111;
unsigned long long fill1d2d = 0x1212121212121212;
unsigned long long fill2d1d = 0x8C0FFEE821212121;
unsigned long long fill2d2d = 0x2222222222222222;
unsigned long long fillzero = 0x0;

/*
 * Destination buffer
 */
unsigned int dstBuff[SIZE];
/*
 * Source buffers
 */
unsigned int srcBuff1[SIZE];
unsigned int srcBuff2[SIZE];
unsigned int srcBuff3[SIZE];
unsigned int srcBuff4[SIZE];

/*
 * Local References
 */
void DAT_main(void);
static void tskHeartBit(void);

void main()
	{
	Task_Params datParams;

	Task_Params_init (&datParams);
	datParams.stackSize = 8192;

	Task_create((Task_FuncPtr)DAT_main, &datParams, NULL);

    BIOS_start();
	}


/*
 *  DAT_main task that will perform the dat transfers
 */
void DAT_main()
	{
    int waitId[NUM_TRANSFERS];

    /*
     * Initialize Dat reference implementation module using EDMA3 Low level
     * driver.
     *   - Creates and opens an EDMA3 Driver instance if passed a NULL handle
     *   - Optionally, can pass an existing EDMA3 driver instance handle
     */
    if (!DAT_EDMA3LLD_init(NULL))
	{
		printf("Error initializing EDMA3 low level driver\n");
		System_exit(0);
	}
	else
	{
		DAT_EDMA3LLD_hEdma = hEdma;
	}

    /*
     * Holds the waitId(s) returned from the various transfers
     */
    if (0 != DAT_open(0,0,0))
    {
		printf ("DAT_open Successful\n");

	    waitId[1] = DAT_fill(srcBuff1, SIZE, (Uint32 *)&fill1d);
        waitId[1] = DAT_fill(srcBuff1, SIZE, (Uint32 *)&fill1d);
        waitId[2] = DAT_fill(srcBuff2, SIZE, (Uint32 *)&fill1d2d);
        waitId[3] = DAT_fill(srcBuff3, SIZE, (Uint32 *)&fill2d1d);
        waitId[4] = DAT_fill(srcBuff4, SIZE, (Uint32 *)&fill2d2d);
        waitId[5] = DAT_fill(dstBuff, SIZE, (Uint32 *)&fillzero);

        DAT_wait(waitId[1]);

        if (DAT_busy(waitId[2]))    {
            /* srcBuff2 is busy, so copy Buff 1 first */
            DAT_copy(srcBuff1, dstBuff, 16 * 4 * 8);
            DAT_wait(waitId[1]);
            DAT_copy2d(DAT_1D2D,srcBuff2, dstBuff + 16 * 8, 4 * 4, 16, 16 * 4);
        }
        else {
            /*
             * Copy out two rows of 64 bytes
             */
            DAT_copy2d(DAT_1D2D,srcBuff2, dstBuff + 16 * 8, 4 * 4, 16, 16 * 4);
            /*
             * Copy out a row of data from srcBuff2 into a 2-d patter in dstBuff
             */
            DAT_copy(srcBuff1, dstBuff, 16 * 4 * 8);
        }

        /*
         * Wait for all transfers to finish
         */
        DAT_wait(DAT_XFRID_WAITALL);

        /*
         * Demonstrate 2D copy mode
         */
        waitId[6] = DAT_copy2d(DAT_2D1D, srcBuff3, dstBuff + 16 * 22 + 4 , 4, 12, 16 * 4);
        waitId[7] = DAT_copy2d(DAT_2D1D, srcBuff3, dstBuff + 16 * 23 + 4 , 4, 12, 16 * 4);
        waitId[8] = DAT_copy2d(DAT_2D2D, srcBuff4, dstBuff +16 * 8 + 4 , 4 * 12, 14, 16 * 4);

        /*
         * Wait for all transfers to complete
         */
        DAT_wait(DAT_XFRID_WAITALL);

        /*
          * Clear up fill buffers
         */
        waitId[0] = DAT_fill(srcBuff1, SIZE, (Uint32 *)&fillzero);
        waitId[1] = DAT_fill(srcBuff2, SIZE, (Uint32 *)&fillzero);
        waitId[2] = DAT_fill(srcBuff3, SIZE, (Uint32 *)&fillzero);
        waitId[3] = DAT_fill(srcBuff4, SIZE, (Uint32 *)&fillzero);

        /*
         * Wait for all transfers to complete
         */
        DAT_wait(DAT_XFRID_WAITALL);

        /*
         * Close DAT module
         */
        DAT_close();

        printf("DAT Transfers Done\n");
    }
    else
    {
        printf("Failed to open DAT\n");
    }

    /*
     * Clean up and exit Dat reference implementation module using EDMA3 Low level
     */
    DAT_EDMA3LLD_exit();

    /* Start the Heart Beat Print */
    tskHeartBit();

    return;
	}

void tskHeartBit()
    {
    static unsigned int counter = 0u;

    while (counter < 0x1000000u)
        {
        Task_sleep (1000u);
        printf("\r\n\r\n!!! DAT HrtBt %x", counter);
        counter++;
        }
    }
