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

#include <app_frameBufMgmt.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

/* Frame buffers must be aligned */
#ifdef __cplusplus
#pragma DATA_ALIGN(32)
#else
#pragma DATA_ALIGN(FrameBufArray, 32)
#endif  /* #ifdef __cplusplus */
UInt8 FrameBufArray[MAX_NUM_PORTS][MAX_NUM_BUFS_PER_PORT][MAX_BUF_SIZE];

typedef struct
{
    UInt32        inpIdx[MAX_NUM_PORTS];
    /* This is a counter which will provide MAX_NUM_BUFS_PER_PORT buffers
     * addresses to VIP in a cyclical manner */

    VpsCore_Frame frm[MAX_NUM_PORTS][MAX_NUM_BUFS_PER_PORT];
    /* This stores frame addresses in a format understood by VIP driver */
} App_FrameBufObj;

App_FrameBufObj gFrameBufObj;

void App_FrameBufInit()
{
    /* This function initilizes a pool of
     * VpsCore_Frame[MAX_NUM_PORTS][MAX_NUM_BUFS_PER_PORT]
     * with static addresses from
     * FrameBufArray[MAX_NUM_PORTS][MAX_NUM_BUFS_PER_PORT][MAX_BUF_SIZE]
     */
    UInt32         i, j;
    VpsCore_Frame *frm;

    for (i = 0; i < MAX_NUM_PORTS; i++)
    {
        gFrameBufObj.inpIdx[i] = 0;
        for (j = 0; j < MAX_NUM_BUFS_PER_PORT; j++)
        {
            frm            = &(gFrameBufObj.frm[i][j]);
            frm->drvData   = NULL;
            frm->streamId  = 0;    /* Ignore for current use-case */
            frm->chId      = 0;    /* Ignore for current use-case */
            frm->dropFrm   = 0;    /* Ignore for current use-case */
            frm->coreStats = 0;
            frm->rtParams  = NULL; /* No Runtime params for this use-case */
            /* Ignore for current use-case Used to provide error information */
            frm->addr[0][0] = &FrameBufArray[i][j][0];
            /* Important. Frame addr */
        }
    }
}

void App_FrameBufDeInit()
{
    // No book-keeping required since buffers are statically allocated
}

VpsCore_Frame *App_GetFrameBuf(UInt32 portId)
{
    VpsCore_Frame *frm;

    frm = &(gFrameBufObj.frm[portId]
            [gFrameBufObj.inpIdx[portId]]
            );

    /* This is to keep cycling between buffer allocated for the specified port*/
    gFrameBufObj.inpIdx[portId]++;
    if (gFrameBufObj.inpIdx[portId] >= MAX_NUM_BUFS_PER_PORT)
    {
        gFrameBufObj.inpIdx[portId] = 0;
    }

    return frm;
}

void App_ReleaseFrameBuf(VpsCore_Frame *frm)
{
    // No book-keeping required since buffers are statically allocated
}

