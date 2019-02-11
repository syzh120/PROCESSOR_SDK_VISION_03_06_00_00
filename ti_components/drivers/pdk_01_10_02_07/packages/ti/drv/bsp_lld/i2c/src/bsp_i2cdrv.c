/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2016
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
 */

/**
 *  \file bsp_i2cdrv.c
 *
 *  \brief I2C driver
 *  This file implements I2C driver functionality.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Log.h>
#include <string.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/System.h>
#include <bsp_i2cdrv.h>
#include <ti/drv/bsp_lld/i2c/bsp_i2c.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/DEV.h>

#if defined (_TMS320C6X)
#include <ti/sysbios/family/c64p/EventCombiner.h>
#include <ti/sysbios/hal/Hwi.h>
#endif

/* ========================================================================== */
/*                       GLOBAL MODULE STATE                                  */
/* ========================================================================== */
static BspOsal_IntrHandle hwiHandle[HSI2C_INST_MAX];
static lld_hsi2c_opMode   instOpMode[HSI2C_INST_MAX];
static BspOsal_SemHandle  hsi2csem[HSI2C_INST_MAX];
static BspOsal_SemHandle  hsi2cTransfersem[HSI2C_INST_MAX];
static Semaphore_Struct   hsi2cTransfersemObj[HSI2C_INST_MAX];
static DEV_Handle         gI2cDevHandle[HSI2C_INST_MAX];
static DEV_Struct         gI2cDevStruct[HSI2C_INST_MAX];
static Int32 transferStatus[HSI2C_INST_MAX];

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/*                        LOCAL FUNCTION PROTOTYPES                           */
/* ========================================================================== */
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static Int i2cMdBindDev(Ptr *devp, Int devId, Ptr devParams);
static Int i2cMdUnBindDev(Ptr devp);
static Int i2cMdCreateChan(Ptr             *chanp,
                           Ptr              devp,
                           String           name,
                           Int              mode,
                           Ptr              chanParams,
                           IOM_TiomCallback cbFxn,
                           Ptr              cbArg);
static Int i2cMdDeleteChan(Ptr chanp);
static Int i2cMdSubmitChan(Ptr chanp, const IOM_Packet *ioPacket);
static Int i2cMdControlChan(Ptr chanp, Uns cmd, Ptr cmdArg);
Void i2cdrvCallback(hsI2cHandle appHandle, LLD_hsi2cErrorCode_t status,
                    void *appData);
Void i2c_init(Void);
#ifdef __cplusplus
}
#endif

const IOM_Fxns I2c_IOMFXNS =
{
    &i2cMdBindDev,
    &i2cMdUnBindDev,
    &i2cMdControlChan,
    &i2cMdCreateChan,
    &i2cMdDeleteChan,
    (IOM_TmdSubmitChan) & i2cMdSubmitChan, /* Misra CAST.FUNC.POINTER : Need a
                                            *waiver*/
};

/* ========================================================================== */
/*                          FUNCTION DEFINTIONS                               */
/* ========================================================================== */

/* ========================================================================== */
/*                            MODULE FUNCTIONS                                */
/* ========================================================================== */

/*
 *  \brief  Function called by BIOS during instance initialisation
 *
 */
Void i2c_init(Void)
{
    return;
}

static Int i2cMdBindDev(Ptr *devp, Int devId, Ptr devParams)
{
    Int32                  status = IOM_COMPLETED;
    lld_hsi2c_initParam_t *initParams;
    I2c_DevInitParams     *DevInitParams;
    hsI2cObjHandle         i2cObjHandle;
    LLD_Hsi2cInstId_t      i2cInstId;
    Semaphore_Params       semParams;

    /* check if the current instance is within the limit supported by the H/W */
    if ((NULL == devParams) || (HSI2C_INST_MAX <= devId) || (0 > devId))
    {
        status = IOM_EBADARGS;
        System_printf("\r\ni2cMdUnBindDev: invalid devParams or the device ID \r\n");
    }
    else
    {
        i2cInstId     = (LLD_Hsi2cInstId_t) devId;
        DevInitParams = (I2c_DevInitParams *) devParams;
        initParams    = DevInitParams->initParams;

        if (NULL == DevInitParams->hsi2c_sem)
        {
            status = IOM_EBADARGS;
            System_printf("\r\n i2cMdBindDev: Invalid DevInitParams \r\n");
        }

        if (NULL == initParams)
        {
            status = IOM_EBADARGS;
            System_printf("\r\n i2cMdBindDev: invalid initParams\r\n");
        }
        else
        {
            if ((HSI2C_MAX_BUS_FREQ < initParams->i2cBusFreq) ||
                (HSI2C_MIN_BUS_FREQ > initParams->i2cBusFreq))
            {
                status = IOM_EBADARGS;
                System_printf("\r\n i2cMdBindDev: invalid i2cBusFreq \r\n");
            }

            if (HSI2C_OPMODE_DMA == initParams->opMode)
            {
                System_printf(
                    "\r\n i2cMdBindDev: DMA Mode is defaulted to INTERRUPT Mode \r\n");
                initParams->opMode = HSI2C_OPMODE_INTERRUPT;
            }
        }
    }
    if (IOM_COMPLETED == status)
    {
        /*
         * Here Devices in Dev Table Loading will be one by one and
         * and we dont need any second initialization for the same device.
         * hence we do not need any synchronization
         */
        Semaphore_Params_init(&semParams);
        Semaphore_construct(&hsi2cTransfersemObj[i2cInstId], (Int32) 0U,
                            &semParams);
        hsi2cTransfersem[i2cInstId] =
            Semaphore_handle(&hsi2cTransfersemObj[i2cInstId]);
        if (NULL == hsi2cTransfersem[i2cInstId])
        {
            status = IOM_EALLOC;
            System_printf("\r\n i2cMdBindDev: Semaphore Creation Failure \r\n");
        }
    }
    if (IOM_COMPLETED == status)
    {
        hsi2csem[i2cInstId] = DevInitParams->hsi2c_sem;

        /*
         * Here Devices in Dev Table Loading will be one by one and
         * and we dont need any second initialization for the same device.
         * hence we do not need any synchronization
         */
        status = lld_i2c_init(&i2cObjHandle, i2cInstId, initParams);
        if (IOM_COMPLETED == status)
        {
            *devp = i2cObjHandle;
            instOpMode[i2cInstId] = initParams->opMode;
        }
        else
        {
            *devp = NULL;
        }
    }
    return (Int) status;
}

static Int i2cMdCreateChan(Ptr             *chanp,
                           Ptr              devp,
                           String           name,
                           Int              mode,
                           Ptr              chanParams,
                           IOM_TiomCallback cbFxn,
                           Ptr              cbArg)
{
    Int32                 status = IOM_COMPLETED;
    hsI2cHandle           i2cHandle;
    Int32                 i2cInstId;
    lld_hsi2c_initParam_t initParams;
    Int8 devId;
    UInt8                 numOpens;

    if (TRUE == I2c_paramCheckEnable)
    {
        /*validate the input parameters                                       */

        /* MISRA.BITS.NOT.UNSIGNED BIOS LAYER ISSUE */

        if ((NULL == chanp) || (NULL == devp) || (NULL == cbFxn) ||
            (NULL == cbArg) || ((IOM_INPUT != mode) && (IOM_OUTPUT != mode) &&
                                (IOM_INOUT != mode)) || (NULL == chanParams))
        {
            status = IOM_EBADARGS;
            System_printf("\r\n i2cMdCreateChan: invalid input params\r\n");
        }
    }
    if (IOM_COMPLETED == status)
    {
        /*Getting the instance ID from name */
        devId     = (Int8) (*name);
        i2cInstId = (Int32) devId - (Int32) '0';
        if ((HSI2C_INST_MAX <= i2cInstId) || (0 > i2cInstId))
        {
            status = IOM_EBADARGS;
            System_printf("\r\n i2cMdCreateChan: invalid instance ID \r\n");
        }
    }
    if (IOM_COMPLETED == status)
    {
        Semaphore_pend((Semaphore_Handle) hsi2csem[i2cInstId],
                       (UInt32) BIOS_WAIT_FOREVER);

        i2cHandle = lld_i2c_open((LLD_Hsi2cInstId_t) i2cInstId,
                                 i2cdrvCallback,
                                 NULL);
        if (NULL == i2cHandle)
        {
            status = LLD_HSI2C_FAIL;
            System_printf("\r\ni2cMdCreateChan: LLD_HSI2C_FAIL\r\n");
        }
        else
        {
            *chanp = i2cHandle;
            lld_i2c_getInitParams(i2cHandle, &initParams);
            lld_i2c_getOpenCount(i2cHandle, &numOpens);
            if ((numOpens == (UInt8) 1) &&
                (initParams.opMode == HSI2C_OPMODE_INTERRUPT))
            {
                #if defined (_TMS320C6X)
                /* Mapping the event id to the
                 * ECM Dispatch of the SYS/BIOS */

                EventCombiner_dispatchPlug(
                    (UInt32) initParams.i2cIntNum,
                    (EventCombiner_FuncPtr) initParams.
                    i2cIsr,
                    (UArg) i2cHandle,
                    (Bool) TRUE);

                #else
                UInt32 tempCastFuncPtr;
                tempCastFuncPtr      = (UInt32) initParams.i2cIsr;
                hwiHandle[i2cInstId] = BspOsal_registerIntr(
                    initParams.i2cIntNum,
                    (BspOsal_IntrFuncPtr) tempCastFuncPtr, i2cHandle);
                /* MISRA.CAST.FUNC.PTR */
                #endif
            }
        }

        Semaphore_post((Semaphore_Handle) hsi2csem[i2cInstId]);
    }
    return (Int) status;
}

/**
 *  \brief    Submit a I/O packet to a channel for processing
 *
 *   The GIO layer calls this function to cause the mini-driver
 *   to process the IOM_Packet for read/write operations.
 *
 *  \param   chanp      [IN]  Handle to the channel
 *  \param   ioPacket   [IN]  Pointer to packet to be submitted
 *
 *  \return  IOM_COMPLETED, if packet is fully processed
 *           IOM_PENDING,   if packet is not fully processed
 *           negative error in case of error
 *
 *  \enter   chanp      must be a valid pointer and should not be null.
 *           ioPacket   must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
static Int i2cMdSubmitChan(Ptr chanp, const IOM_Packet *ioPacket)
{
    Int32                 status = IOM_COMPLETED;
    hsI2cHandle           i2cHandle;
    lld_hsi2c_datatfr_params_t      *i2cXferParams = NULL;
    LLD_Hsi2cInstId_t     instNum;
    UInt8                 slaveAddr;

    lld_hsi2c_initParam_t initParams;
    lld_hsi2c_transreceive_params_t *i2cTxRxXferParams = NULL;

    if (TRUE == I2c_paramCheckEnable)
    {
        if ((NULL == chanp) || (NULL == ioPacket))
        {
            status = IOM_EBADARGS;
            System_printf("\r\n i2cMdSubmitChan: invalid input params\r\n");
        }
    }

    if (IOM_COMPLETED == status)
    {
        i2cHandle = chanp;
        lld_i2c_getInitParams(i2cHandle, &initParams);
        if (initParams.isMasterMode != LLD_HSI2C_MODE_SLAVE_TRANSRECEIVE)
        {
            i2cXferParams = (lld_hsi2c_datatfr_params_t *) ioPacket->addr;
            if (NULL == i2cXferParams)
            {
                status = IOM_EBADARGS;
                System_printf("\r\n i2cMdSubmitChan: invalid i2cXferParams \r\n");
            }
        }
        else
        {
            i2cTxRxXferParams =
                (lld_hsi2c_transreceive_params_t *) ioPacket->addr;
            if (NULL == i2cTxRxXferParams)
            {
                status = IOM_EBADARGS;
                System_printf(
                    "\r\n i2cMdSubmitChan: invalid i2cTxRxXferParams \r\n");
            }
        }
    }

    if (IOM_COMPLETED == status)
    {
        lld_i2c_getInstNum(i2cHandle, &instNum);
        Semaphore_pend((Semaphore_Handle) hsi2csem[instNum],
                       (UInt32) BIOS_WAIT_FOREVER);
        if (i2cXferParams != NULL)
        {
            if (i2cXferParams->timeout > I2C_IRQ_TIME_OUT)
            {
                i2cXferParams->timeout = I2C_IRQ_TIME_OUT;
            }

            status = lld_i2c_transfer(i2cHandle, i2cXferParams);

            slaveAddr = i2cXferParams->slaveAddr;
            if (IOM_COMPLETED != status)
            {
                System_printf("\r\n i2cMdSubmitChan: i2c%d transfer to slave "
                              "address 0x%0.2x failed\r\n", instNum, slaveAddr);
            }
            if ((instOpMode[instNum] == HSI2C_OPMODE_INTERRUPT) &&
                (IOM_COMPLETED == status))
            {
                status =
                    (Int32) Semaphore_pend((Semaphore_Handle) hsi2cTransfersem[
                                               instNum],
                                           (UInt32) I2C_IRQ_TIME_OUT);
                if (status != (Int32) TRUE)
                {
                    System_printf(
                        "\r\n i2cMdSubmitChan: i2c transfer Timeout IRQ not received\r\n");
                    status = IOM_ETIMEOUT;
                    lld_i2c_abort_transfer(i2cHandle);
                }
                else
                {
                    status = transferStatus[instNum];

                    if (IOM_COMPLETED != status)
                    {
                        System_printf(
                            "\r\n i2cMdSubmitChan: i2c%d transfer to slave address 0x%0.2x failed\r\n",
                            instNum, slaveAddr);
                    }
                }
            }
        }
        else if (i2cTxRxXferParams != NULL)
        {
            status = lld_i2c_transReceive(i2cHandle, i2cTxRxXferParams);

            if (IOM_COMPLETED != status)
            {
                System_printf("\r\n i2cMdSubmitChan: i2c%d Slave Transfer "
                              "failed\r\n", instNum);
            }
            if ((IOM_COMPLETED == status) &&
                (instOpMode[instNum] == HSI2C_OPMODE_INTERRUPT))
            {
                /* In case of I2C Slave, transfer starts after external master
                 * initiates it */
                Semaphore_pend((Semaphore_Handle) hsi2cTransfersem[instNum],
                               (UInt32) BIOS_WAIT_FOREVER);
                status = transferStatus[instNum];

                if (status < IOM_COMPLETED)
                {
                    System_printf("\r\n i2cMdSubmitChan: i2c%d Slave Transfer "
                                  "failed\r\n", instNum);
                    lld_i2c_abort_transfer(i2cHandle);
                }
            }
        }
        else
        {
            status = IOM_EBADARGS;
            System_printf("\r\n i2cMdSubmitChan: invalid input params\r\n");
        }
        Semaphore_post((Semaphore_Handle) hsi2csem[instNum]);
    }
    return (Int) status;
}

/**
 *  \fn     static Int i2cMdUnBindDev
 *
 *  \brief  Function called by Bios during closing of the instance
 *
 *  \param  devp       [IN]  pointer to Uart driver object
 *
 *  \return success code
 *
 *  \enter  devp       must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
static Int i2cMdUnBindDev(Ptr devp)
{
    Int32             status = IOM_COMPLETED;
    hsI2cObjHandle    i2cObjHandle;
    hsI2cHandle       i2cHandle;
    LLD_Hsi2cInstId_t instNum;
    Semaphore_Struct *i2cSemStruct;

    if (TRUE == I2c_paramCheckEnable)
    {
        /* Check if this is a valid handle
         *                                       */
        if (NULL == devp)
        {
            status = IOM_EBADARGS;
            System_printf("\r\n i2cMdUnBindDev: invalid input params\r\n");
        }
    }

    i2cObjHandle = devp;
    i2cHandle    = &i2cObjHandle;
    lld_i2c_getInstNum(i2cHandle, &instNum);
    if (instNum >= HSI2C_INST_MAX)
    {
        status = LLD_HSI2C_FAIL;
        System_printf("\r\n i2cMdUnBindDev: invalid NumInstances\r\n");
    }
    else
    {
        status = lld_i2c_deinit(instNum);
        if (IOM_COMPLETED != status)
        {
            System_printf("\r\n i2cMdUnBindDev: i2c transfer FAILURE \r\n");
        }

        i2cSemStruct =
            Semaphore_struct((Semaphore_Handle) hsi2cTransfersem[instNum]);
        Semaphore_destruct(i2cSemStruct);
    }

    return (Int) status;
}

/**
 *  \brief    This function is called by the application to close a previously
 *            opened channel.it deletes the channel so that it is not available
 *            for further transactions. All the allocated reqources are freed &
 *            the channel will be ready for the "open" operation once again.
 *
 *  \param    chanp      [IN]   Handle to the channel.
 *
 *  \return   status
 *
 *            chanp      must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
static Int i2cMdDeleteChan(Ptr chanp)
{
    Int32             status = IOM_COMPLETED;
    hsI2cHandle       i2cHandle;
    UInt8             numOpens;
    LLD_Hsi2cInstId_t instNum;
    if (TRUE == I2c_paramCheckEnable)
    {
        if (NULL == chanp)
        {
            System_printf("\r\n i2cMdDeleteChan: Invalid input parameter\n");
            status = IOM_EBADARGS;
        }
    }
    if (IOM_COMPLETED == status)
    {
        i2cHandle = (hsI2cHandle) chanp;
        lld_i2c_getInstNum(i2cHandle, &instNum);
        Semaphore_pend((Semaphore_Handle) hsi2csem[instNum],
                       (UInt32) BIOS_WAIT_FOREVER);
        lld_i2c_getOpenCount(i2cHandle, &numOpens);
        status = lld_i2c_close(&i2cHandle);
        if (IOM_COMPLETED != status)
        {
            System_printf("\r\n i2cMdDeleteChan: i2c close FAILURE \r\n");
        }
        if ((numOpens == (UInt8) 1) &&
            (instNum < HSI2C_INST_MAX) &&
            (instOpMode[instNum] == HSI2C_OPMODE_INTERRUPT) &&
            (IOM_COMPLETED == status))
        {
            BspOsal_unRegisterIntr(&hwiHandle[instNum]);
        }
        if(instNum < HSI2C_INST_MAX)
        {
            Semaphore_post((Semaphore_Handle) hsi2csem[instNum]);
        }
    }
    return (Int) status;
}

static Int i2cMdControlChan(Ptr chanp, Uns cmd, Ptr cmdArg)
{
    Int32             status = IOM_COMPLETED;
    hsI2cHandle       i2cHandle;
    UInt8             slaveAddr;
    LLD_Hsi2cInstId_t i2cInstNum;
    lld_i2c_busspeed  i2cBusFreq;
    UInt32            i2cDelay;
    if (TRUE == I2c_paramCheckEnable)
    {
        if (NULL == chanp)
        {
            System_printf("\r\n i2cMdControlChan: Invalid input parameter\n");
            status = IOM_EBADARGS;
        }
    }

    if (status != IOM_EBADARGS)
    {
        i2cHandle = (hsI2cHandle *) chanp;
        switch (cmd)
        {
            case IOCTL_I2C_PROBE:
                slaveAddr = *((UInt8 *) cmdArg);
                status    = lld_i2c_probe(i2cHandle, slaveAddr);
                break;
            case IOCTL_I2C_GET_BUS_FREQUENCY:
                lld_i2c_getInstNum(i2cHandle, &i2cInstNum);
                status = lld_i2c_getBusFreq(i2cInstNum, &i2cBusFreq);
                if (LLD_HSI2C_SUCCESS == status)
                {
                    *((lld_i2c_busspeed *) cmdArg) = i2cBusFreq;
                }
                break;
            case IOCTL_I2C_SET_BUS_FREQUENCY:
                /* bus Frequency to set in KHz */
                i2cBusFreq = *((lld_i2c_busspeed *) cmdArg);
                /* Take Instance semaphore
                 * as i2c controller would be disabled and re enabled */
                lld_i2c_getInstNum(i2cHandle, &i2cInstNum);
                Semaphore_pend((Semaphore_Handle) hsi2csem[i2cInstNum],
                               (UInt32) BIOS_WAIT_FOREVER);
                status = lld_i2c_setBusFreq(i2cInstNum, i2cBusFreq);
                Semaphore_post((Semaphore_Handle) hsi2csem[i2cInstNum]);
                break;
            case IOCTL_I2C_RESET_CONTROLLER:
                /* Take Instance semaphore
                 * as i2c controller would be disabled and re enabled */
                lld_i2c_getInstNum(i2cHandle, &i2cInstNum);
                Semaphore_pend((Semaphore_Handle) hsi2csem[i2cInstNum],
                               (UInt32) BIOS_WAIT_FOREVER);
                status = lld_i2c_resetCtrl(i2cHandle);
                Semaphore_post((Semaphore_Handle) hsi2csem[i2cInstNum]);
                break;
            case IOCTL_I2C_RECOVER_BUS:
                /* Take Instance semaphore */
                lld_i2c_getInstNum(i2cHandle, &i2cInstNum);
                Semaphore_pend((Semaphore_Handle) hsi2csem[i2cInstNum],
                               (UInt32) BIOS_WAIT_FOREVER);
                i2cDelay = *((UInt32 *) cmdArg);
                status   = lld_i2c_recoverBus(i2cHandle, i2cDelay);
                Semaphore_post((Semaphore_Handle) hsi2csem[i2cInstNum]);
                break;
            default:
                status = IOM_EBADARGS;
                System_printf("\r\ni2cMdControlChan: Unsupported IOCTL Command\r\n");
                break;
        }
    }
    return (Int) status;
}

Int32 I2c_GlobalInit(UInt32 numInst, I2c_DevInitParams *devInitPrms)
{
    Int32           status = IOM_COMPLETED;
    DEV_Params      devPrms;
    UInt32          instCnt;
    IOM_Fxns *iomFxns;
    Int devid;
    static Char     devName[] = "i2c";

    if ((NULL == devInitPrms) || (HSI2C_INST_MAX < numInst))
    {
        status = IOM_EBADARGS;
        System_printf("\r\n i2cGlobal_Init: invalid devInitPrms or numInst \r\n");
    }

    if (IOM_COMPLETED == status)
    {
        for (instCnt = 0U; instCnt < HSI2C_INST_MAX; instCnt++)
        {
            gI2cDevHandle[instCnt] = NULL;
        }

        iomFxns = (IOM_Fxns *) &I2c_IOMFXNS;
        for (instCnt = 0U; instCnt < numInst; instCnt++)
        {
            devid = devInitPrms->instId;

            DEV_Params_init(&devPrms);
            devPrms.devid        = devid;
            devPrms.deviceParams = (Ptr) devInitPrms;
            DEV_construct(&gI2cDevStruct[instCnt], devName, iomFxns,
                          &devPrms,
                          NULL);
            gI2cDevHandle[instCnt] = DEV_handle(&gI2cDevStruct[instCnt]);
            if (NULL == gI2cDevHandle[instCnt])
            {
                status = IOM_EBADARGS;
                System_printf("\r\n i2cGlobal_Init: Create device Failed \r\n");
            }
            devInitPrms++;
            /* MISRA PTR.ARITH devInitPrms increments till max numInst */
        }
    }
    return status;
}

Int32 I2c_GlobalDeInit(Ptr args)
{
    UInt32      instCnt;
    DEV_Struct *i2cDevStruct;

    for (instCnt = 0U; instCnt < HSI2C_INST_MAX; instCnt++)
    {
        if (gI2cDevHandle[instCnt] != NULL)
        {
            i2cDevStruct = DEV_struct(gI2cDevHandle[instCnt]);
            DEV_destruct(i2cDevStruct);
            gI2cDevHandle[instCnt] = NULL;
        }
    }

    return (0);
}

Void i2cdrvCallback(hsI2cHandle appHandle, LLD_hsi2cErrorCode_t status,
                    void *appData)
{
    LLD_Hsi2cInstId_t instNum;
    lld_i2c_getInstNum(appHandle, &instNum);
    transferStatus[instNum] = status;

    Semaphore_post((Semaphore_Handle) hsi2cTransfersem[instNum]);

    return;
}

