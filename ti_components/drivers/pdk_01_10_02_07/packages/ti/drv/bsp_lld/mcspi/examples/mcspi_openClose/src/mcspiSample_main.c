/*
 *  Copyright (C) 2018 Texas Instruments Incorporated
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
/**
 *  \file   mcspiSample_main.c
 *
 *  \brief   McSPI sample application for testing multiple driver open/close
 *
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */

#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/bsp_lld/mcspi/bsp_mcspi.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>
/* ========================================================================== */
/*                       Macros & Typedefs                                    */
/* ========================================================================== */
#define MCSPI_APP_OPEN_CLOSE_TEST_COUNT              (1000U)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void spiSampleTask(UArg arg1, UArg arg2);
void user_mcspi_init(void);

/* ========================================================================== */
/*                             GLOBAL VARIABLES                               */
/* ========================================================================== */
Mcspi_Params mcspiPrms;
extern const IOM_Fxns Mcspi_IOMFXNS;

/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */
/**
 * \brief     Main entry function for the spi sample application. it creates
 *            the spi sample task(used to demonstrate the spi functionality).
 *
 * \param     None
 *
 * \return    None
 *
 */
Int32 main(void)
{
    Int32   inst_num = 0;

    System_printf("Running McSPI open/close test.\r\n");
    GIO_addDevice("/mcspi0", (xdc_Ptr) & Mcspi_IOMFXNS, &user_mcspi_init,
                  inst_num, (xdc_Ptr) & mcspiPrms);

    Task_create((Task_FuncPtr) spiSampleTask, NULL, NULL);
    BIOS_start();

    return (0);
}

/**
 * \brief      Entry point for the main task. This creates and deletes the SPI 
 *             driver in a loop.
 *
 * \param      arg1  [IN]   unused
 * \param      arg2  [IN]   unused
 *
 * \return     None
 */
void spiSampleTask(UArg arg1, UArg arg2)
{
    GIO_Params       ioParams;
    Mcspi_ChanParams chanParams;
    Error_Block      eb;
    UInt32           i;
    EDMA3_DRV_Result edmaResult = 0;
    EDMA3_DRV_Handle edmaHandle;
    GIO_Handle       mcspiHandle = NULL;
    Int32            retVal = BSP_SOK;

    /* call the function for the SPI application test                     */
    edmaHandle = edma3init(0, &edmaResult);

    if (edmaResult != EDMA3_DRV_SOK)
    {
        /* Report EDMA Error */
        System_printf("\r\nEDMA driver initialization FAIL\r\n");
    }

    Error_init(&eb);

    /* Initialize channel Params. */
    Mcspi_ChanParams_init(&chanParams);
    /* update the edma Handle */
    chanParams.hEdma        = edmaHandle;
    chanParams.fifoEnable   = (UInt32) TRUE;

    /* Initialize io Params. */
    GIO_Params_init(&ioParams);
    ioParams.chanParams     = (Ptr) & chanParams;
    ioParams.model          = GIO_Model_ISSUERECLAIM;
    ioParams.numPackets     = 2U;

    for (i = 0U; i < MCSPI_APP_OPEN_CLOSE_TEST_COUNT; i++)
    {
        mcspiHandle = GIO_create("/mcspi0", GIO_INOUT, &ioParams, &eb);
        if (mcspiHandle == NULL)
        {
            System_printf("\r\nMcSPI Driver create FAILED.\r\n");
            retVal = BSP_EFAIL;
            break;
        }
        else
        {
            GIO_delete(&mcspiHandle);
        }
    }

    if (retVal == BSP_SOK)
    {
        System_printf("!!!McSPI open/close test Passed.\r\n");
    }
    else
    {
        System_printf("!!!McSPI open/close test Failed.\r\n");
    }

    return;
}

/*
 * McSPI init function called when creating the driver.
 */
void user_mcspi_init(void)
{
    Mcspi_init();

    mcspiPrms = Mcspi_PARAMS;
    mcspiPrms.opMode = MCSPI_OPMODE_DMAINTERRUPT;
}

/* ========================================================================== */
/*                                END OF FILE                                 */
/* ========================================================================== */
