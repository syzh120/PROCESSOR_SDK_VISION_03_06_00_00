/*
 *  Copyright (c) Texas Instruments Incorporated 2014-2015
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

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/stw_types.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <app_framebufmgnt.h>

/** \brief Maximum number of buffers to be allocated
 */
#define MAX_NUM_BUFS            (6U)

/** \brief Maximum Buffer Size, Assuming input size is always greater
 */
#define MAX_BUF_SIZE            (1920u * 1080u * 2U)

/* Frame buffers must be aligned */
#pragma DATA_ALIGN(FrameBufArray, 32)
uint8_t         FrameBufArray[MAX_NUM_BUFS][MAX_BUF_SIZE];

typedef struct
{
    uint32_t      inpIdx;
    /* This is a counter which will provide MAX_NUM_BUFS_PER_PORT buffers
     * addresses to VIP in a cyclical manner */

    VpsCore_Frame frm[MAX_NUM_BUFS];
    /* This stores frame addresses in a format understood by VIP driver */
} App_FrameBufObj;

App_FrameBufObj gFrameBufObj;

void App_FrameBufInit()
{
    uint32_t       i;
    VpsCore_Frame *frm;

    gFrameBufObj.inpIdx = 0;
    for(i = 0; i < MAX_NUM_BUFS; i++)
    {
        frm = &(gFrameBufObj.frm[i]);
        frm->drvData   = NULL;
        frm->streamId  = 0;                        /* Ignore for current
                                                    *use-case */
        frm->chId      = 0;                        /* Ignore for current
                                                    *use-case */
        frm->dropFrm   = 0;                        /* Ignore for current
                                                    *use-case */
        frm->coreStats = 0;                        /* Ignore for current
                                                    * use-case
                                                    * Used to provide error
                                                    * information
                                                    */

        frm->addr[0][0] = &FrameBufArray[i][0];    /*Important. Frame addr */
    }
}

void App_FrameBufDeInit()
{
    // No book-keeping required since buffers are statically allocated
}

VpsCore_Frame *App_GetFrameBuf()
{
    VpsCore_Frame *frm;

    frm = &(gFrameBufObj.frm[gFrameBufObj.inpIdx]);

    /* This is to keep cycling between buffer allocated for the specified port*/
    gFrameBufObj.inpIdx++;
    if(gFrameBufObj.inpIdx >= MAX_NUM_BUFS)
    {
        gFrameBufObj.inpIdx = 0;
    }

    return frm;
}

void App_ReleaseFrameBuf(VpsCore_Frame *frm)
{
    // No book-keeping required since buffers are statically allocated
}

