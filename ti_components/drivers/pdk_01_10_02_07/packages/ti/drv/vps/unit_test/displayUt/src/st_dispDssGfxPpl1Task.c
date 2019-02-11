/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2016
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 *  \file st_dispDssGfxPpl1Task.c
 *
 *  \brief
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <st_dispDss.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Semaphore_Handle gStDispDssMasterTaskSem;
extern Semaphore_Handle gStDispDssGfxPpl1TaskSem;
extern Queue_Handle     gGfxPpl1msgQueue;
UInt32 gTestVal4 = 0U;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  st_dispDssGfxPpl1TestTask
 */

void st_dispDssGfxPpl1TestTask(UArg arg0, UArg arg1)
{
    Int32  retVal = FVID2_SOK;
    st_DispDssMsgObj       *gfxPpl1TskmsgObj;
    st_DispDssAppObj       *appObj;
    st_DispDssInstObj *instObj;
    UInt32 flag    = 1;
    UInt32 msgFlag = 1;

    appObj             = (st_DispDssAppObj *) arg0;
    appObj->taskId     = VPS_DISP_INST_DSS_GFX1 + 1;
    instObj            = &appObj->instObj;
    appObj->taskResult = FVID2_SOK;

    Semaphore_pend(gStDispDssGfxPpl1TaskSem, BIOS_WAIT_FOREVER);

    while (1)
    {
        if ((!flag) | (appObj->taskResult != FVID2_SOK))
        {
            Semaphore_post(gStDispDssMasterTaskSem);
            Semaphore_pend(gStDispDssGfxPpl1TaskSem, BIOS_WAIT_FOREVER);
        }

        if (msgFlag)
        {
            gfxPpl1TskmsgObj = Queue_get(gGfxPpl1msgQueue);
            flag = 0;

            switch (gfxPpl1TskmsgObj->cmd)
            {
                case CREATE:

                    retVal = st_dispDssCreatePhase(appObj);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  "Create phase failed\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }

                    break;

                case CONTROL:
                    retVal = st_dispDssControlPhase(appObj);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  "Control phase failed\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }
                    break;

                case ALLOC_AND_QUEUE:
                    retVal = st_dispDssAllocAndQueuePhase(appObj);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  "ALLOC_AND_QUEUE phase failed\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }
                    break;

                case START:
                    retVal = Fvid2_start(instObj->drvHandle, NULL);
                    if (retVal != FVID2_SOK)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  UT_NAME ": Display Start Failed!!!\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }
                    break;

                case STOP:
                    retVal = Fvid2_stop(instObj->drvHandle, NULL);
                    if (retVal != FVID2_SOK)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  UT_NAME ": Display Stop Failed!!!\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }
                    break;

                case DELETE:
                    retVal = st_dispDssDeletePhase(appObj);
                    if (FVID2_SOK != retVal)
                    {
                        GT_0trace(appObj->traceMask, GT_ERR,
                                  "Delete phase failed\r\n");
                        appObj->taskResult = FVID2_EFAIL;
                    }
                    break;
            }
        }
    }
}

