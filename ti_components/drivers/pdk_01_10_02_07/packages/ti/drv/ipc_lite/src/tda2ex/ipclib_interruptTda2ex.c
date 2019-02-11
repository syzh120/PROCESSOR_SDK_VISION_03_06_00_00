/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  @file   ipclib_interruptTda2ex.c
 *
 *  @brief  This file contains implementation for ipclib interrupt
 *          module for Tda2ex.
 *          DO NOT EXTEND this implementation to other plaforms.
 *          For new platform please add ipclib_interrupt<PlatformName>.c
 *          under ipclib\<PlatformName> folder.
 *
 */

/*_______________________________ Include Files _____________________________*/
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ipclib_interrupt_priv.h>

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_006) */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1417)
 */
/**
 * \brief     This function is used internally by ipc interrupt module
 *            to setup interrupt connections of INTC to interrupt source.
 *
 * \return    None
 *
 * \note      This internal fucntion is valid only for Tdaxx
 */
void ipcLibInitInterrupts(void)
{
    uint32_t  i;
    for (i = 0;
         i < (sizeof (IpcLib_gXbarConfig) / sizeof (IpcLib_InterruptXbar));
         i++)
    {
        if ((IpcLib_gXbarConfig[i].xbarInst != LE) &&
            (IpcLib_gXbarConfig[i].xbarInput != LE))
        {
            BspOsal_irqXbarConnect(IpcLib_gXbarConfig[i].xbarInst,
                                   IpcLib_gXbarConfig[i].xbarInput);
        }
        else
        {
            break;
        }
    }
}

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_006) */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1418)
 */
/**
 * \brief     This function is used internally by ipc interrupt module
 *            to de-init interrupt connections of INTC to interrupt source.
 *
 * \return    None
 *
 * \note      This internal fucntion is valid only for Tdaxx
 */
void ipcLibDeInitInterrupts(void)
{
    uint32_t  i;
    for (i = 0U;
         i < (sizeof (IpcLib_gXbarConfig) / sizeof (IpcLib_InterruptXbar));
         i++)
    {
        if ((IpcLib_gXbarConfig[i].xbarInst != LE) &&
            (IpcLib_gXbarConfig[i].xbarInput != LE))
        {
            BspOsal_irqXbarDisconnect(IpcLib_gXbarConfig[i].xbarInst);
        }
        else
        {
            break;
        }
    }
}

/**
 * \brief     This function is used to update mailbox base address.
 *            In some cases, Tx and Rx address viewed by IPC cores are different
 *            this platform specific function allows you to update mbxBase.
 *
 * \return    None
 *
 * \note      This internal fucntion is valid only for Tdaxx
 */
void ipcLibUpdateMbxAddr(uint32_t selfProcId,
                         uint32_t remoteProcId,
                         uint32_t *mbxBase)
{
    /* Nothing to be done for TDA2EX */
}

