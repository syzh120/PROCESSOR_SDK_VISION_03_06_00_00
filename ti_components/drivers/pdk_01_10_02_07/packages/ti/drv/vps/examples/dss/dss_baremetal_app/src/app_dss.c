/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
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
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dctrl.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dss.h>
#include <app_dctrlConfigure.h>
#include <app_dssConfigure.h>
#include <ti/drv/vps/include/dss/vps_dssDrv.h>
#include <ti/drv/vps/include/dss/vps_dctrlDrv.h>

#define TEST_CASE_DURATION (3600)

#define BUFFER_ROTATION (TEST_CASE_DURATION / 4)

UInt32             gEnableInfiniteCaptLoop = 0;

#define BUF_DSS_STRIDE     (720 * 2) /* Should be multiple of 16 */
#define BUF_DSS_HEIGHT     (480)

#define MAX_NUM_BUFS_PER_PIPE   4

#define MAX_NUM_VID_PIPE        4

/* Size of one buffer */
#define MAX_DSS_BUF_SIZE        (BUF_DSS_STRIDE * BUF_DSS_HEIGHT)

extern UInt32      FrameBufArrayDss[MAX_NUM_VID_PIPE][MAX_NUM_BUFS_PER_PIPE];

volatile UInt32    gDqCount_vid = 0;
extern int32_t     gTestStatus;

typedef struct
{
    UInt32        inpIdx[MAX_NUM_VID_PIPE];
    /* This is a counter which will provide MAX_NUM_BUFS_PER_PIPE buffers
     * addresses to DSS in a cyclical manner */

    VpsCore_Frame frm[MAX_NUM_VID_PIPE][MAX_NUM_BUFS_PER_PIPE];
    /* This stores frame addresses in a format understood by DSS driver */
} App_DssFrameBufObj;

App_DssFrameBufObj gDssFrameBufObj;

void App_DssFrameBufInit()
{
    /* This function initilizes a pool of
     * VpsCore_Frame[MAX_NUM_VID_PIPE][MAX_NUM_BUFS_PER_PIPE]
     * with static addresses from
     * FrameBufArray[MAX_NUM_VID_PIPE][MAX_NUM_BUFS_PER_PIPE][MAX_BUF_SIZE]
     */
    UInt32         i, j;
    VpsCore_Frame *frm;

    for (i = 0; i < MAX_NUM_VID_PIPE; i++)
    {
        gDssFrameBufObj.inpIdx[i] = 0;
        for (j = 0; j < MAX_NUM_BUFS_PER_PIPE; j++)
        {
            frm            = &(gDssFrameBufObj.frm[i][j]);
            frm->drvData   = NULL;
            frm->streamId  = 0;    /* Ignore for current usecase */
            frm->chId      = 0;    /* Ignore for current usecase */
            frm->dropFrm   = 0;    /* Ignore for current usecase */
            frm->coreStats = 0;    /* used to provide error information */
            frm->rtParams  = NULL; /* No Runtime change */

            /* Important Frame addr*/
            frm->addr[0][0] = (Ptr *) FrameBufArrayDss[i][j];
        }
    }
}

void App_DssFrameBufDeInit()
{
    /* No book-keeping required since buffers are statically allocated */
}

VpsCore_Frame *App_DssGetFrameBuf(UInt32 pipeId)
{
    VpsCore_Frame *frm;

    frm = &(gDssFrameBufObj.frm[pipeId]
            [gDssFrameBufObj.inpIdx[pipeId]]
            );

    /* This is to keep cycling between buffer allocated for the specified port*/
    if ((gDqCount_vid % BUFFER_ROTATION == 0) && (gDqCount_vid > 0))
    {
        gDssFrameBufObj.inpIdx[pipeId]++;
    }

    if (gDssFrameBufObj.inpIdx[pipeId] >= MAX_NUM_BUFS_PER_PIPE)
    {
        gDssFrameBufObj.inpIdx[pipeId] = 0;
    }

    return frm;
}

void App_DssReleaseFrameBuf(VpsCore_Frame *frm)
{
    /* No book-keeping required since buffers are statically allocated */
}

VpsCore_Frame *App_DssqueBufs(void *drvData)
{
    VpsDrv_DispInstObj *pObj = (VpsDrv_DispInstObj *) drvData;
    return (VpsCore_Frame *) App_DssGetFrameBuf((UInt32) pObj->drvInstId);
}

Int32 App_DssdeQueBufs(void *drvData, VpsCore_Frame *frmBufList)
{
    /* The first VSYNC interrupt has NULL pointer as there is no frame to deQ */
    if (NULL != frmBufList)
    {
        gDqCount_vid++;
        App_DssReleaseFrameBuf(frmBufList);
    }
    return 0;
}

int App_DssRun()
{
    Int32 retVal = 0;

    VpsDrv_DispInstObj  *DispObj  = NULL;
    VpsDrv_DctrlInstObj *DctrlObj = NULL;

    /*** START POINT ***/
    Bsp_printf("Hello World\r\n");

    Bsp_printf("***** START :: VPS Init\r\n");
    Vps_init(NULL);
    Bsp_printf("***** STOP  :: VPS Init\r\n");

    App_DssFrameBufInit();

    /* Initialize & Open the VIP Core */
    Bsp_printf("***** START :: DSS Core Initialization\r\n");
    DctrlObj = App_dctrlcoreOpen();

    if (DctrlObj == NULL)
    {
        Bsp_printf("***** FAILED :: Dctrl Core Open  ***** \r\n");
        gTestStatus = STW_EFAIL;
        return -1;
    }

    /* Configure Dss and Dctrl module */
    Bsp_printf("***** START :: Configure Dctrl\r\n");
    retVal  = App_configureDctrl(DctrlObj);
    retVal |= App_configureDctrlPipe(DctrlObj);

    if (retVal != BSP_SOK)
    {
        Bsp_printf("***** FAIL  :: Configure Dctrl \r\n");
        gTestStatus = STW_EFAIL;
        return -1;
    }

    DispObj = App_dsscoreOpen(VPSDRV_DISP_INST_DSS_VID1);

    Bsp_printf("***** STOP  :: Dss Core Initialization\r\n");

    if (DispObj == NULL)
    {
        Bsp_printf("***** FAILED :: Dss Core Open  ***** \r\n");
        gTestStatus = STW_EFAIL;
        return -1;
    }

    retVal = App_dssconfigure(DispObj);

    if (retVal != BSP_SOK)
    {
        Bsp_printf("***** FAIL  :: Configure Dss\r\n");
        gTestStatus = STW_EFAIL;
        return -1;
    }
    Bsp_printf("***** STOP  :: Configure Dss\r\n");

    /* Start Capture */
    App_dsscoreStart(DispObj);

    while ((gDqCount_vid < TEST_CASE_DURATION))
    {
        /* Wait for TEST_CASE_DURATION number of frames to be displayed */
    }

    App_dsscoreStop(DispObj);

    Bsp_printf("Frames Displayed            : %d\r\n", gDqCount_vid);

    gDqCount_vid = 0;

    /* De-Initialize & Close the Dss and Dctrl Core*/
    App_dsscoreClose(DispObj);
    /* Add dctrl clear config */

    /* De-Initialize Frame buffer management and VPS library */
    App_DssFrameBufDeInit();
    Vps_deInit(NULL);

    return 0;
}

