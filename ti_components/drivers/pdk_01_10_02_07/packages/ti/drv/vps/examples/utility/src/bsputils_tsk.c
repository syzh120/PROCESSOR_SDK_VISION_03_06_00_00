/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file bsputils_buf.c
 *
 *  \brief This file implements application level buffer handling functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#if defined (BARE_METAL)
#include <ti/csl/tistdtypes.h>
#else
#include <xdc/std.h>
#endif

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/examples/utility/bsputils_tsk.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSPUTILS_TSK_CMD_EXIT   (0xFFFFFFFFU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void BspUtils_tskMain(UArg arg0, UArg arg1);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void BspUtils_tskMain(UArg arg0, UArg arg1)
{
    BspUtils_TskHndl *pHndl = (BspUtils_TskHndl *) arg0;
    BspUtils_MsgHndl *pMsg;
    Int32 status = FVID2_SOK;
    UInt32 cmd;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);

    while (FVID2_SOK == status)
    {
        status = BspUtils_mbxRecvMsg(&pHndl->mbx, &pMsg, BSP_OSAL_WAIT_FOREVER);
        if (FVID2_SOK == status)
        {
            cmd = BspUtils_msgGetCmd(pMsg);
            if (cmd == BSPUTILS_TSK_CMD_EXIT)
            {
                BspUtils_tskAckOrFreeMsg(pMsg, FVID2_SOK);
                break;
            }

            if (pHndl->funcMain)
            {
                pHndl->funcMain(pHndl, pMsg);
            }
        }
    }

    return;
}

Int32 BspUtils_tskCreate(BspUtils_TskHndl    *pHndl,
                         BspUtils_TskFuncMain funcMain,
                         UInt32               tskPri,
                         UInt8               *stackAddr,
                         UInt32               stackSize,
                         Ptr                  appData,
                         char                 *tskName)
{
    Int32 status;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);
    GT_assert(GT_DEFAULT_MASK, funcMain != NULL);

    pHndl->funcMain  = funcMain;
    pHndl->stackSize = stackSize;
    pHndl->stackAddr = stackAddr;
    pHndl->tskPri    = tskPri;
    pHndl->appData   = appData;
    pHndl->tskAffinity = 0; /* set to 0 as BSP testApp run only on core 0 */

    status = BspUtils_mbxCreate(&pHndl->mbx);
    GT_assert(GT_DEFAULT_MASK, FVID2_SOK == status);

    pHndl->tsk = BspOsal_taskCreate(
        (BspOsal_TaskFuncPtr) & BspUtils_tskMain,
        tskName,
        (Int32) tskPri,
        stackAddr,
        stackSize,
        pHndl,
        pHndl->tskAffinity);
    GT_assert(GT_DEFAULT_MASK, pHndl->tsk != NULL);

    BspUtils_prfLoadRegister((Task_Handle) pHndl->tsk, tskName);

    return (status);
}

Int32 BspUtils_tskDelete(BspUtils_TskHndl *pHndl)
{
    BspUtils_prfLoadUnRegister((Task_Handle) pHndl->tsk);

    BspUtils_tskSendCmd(pHndl, BSPUTILS_TSK_CMD_EXIT);
    /* wait for command to be received
     * and task to be exited - BspOsal_taskDelete() internally waits for task
     * to exit */
    BspOsal_sleep((UInt32) 1U);
    BspOsal_taskDelete(&pHndl->tsk);
    BspUtils_mbxDelete(&pHndl->mbx);

    return (FVID2_SOK);
}

