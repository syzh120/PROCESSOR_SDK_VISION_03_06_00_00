/*
 *  Copyright (C) 2017 Texas Instruments Incorporated
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

#include <stdio.h>
#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <app_framebufmgnt.h>

/*
 * \brief Maximum number of buffers to be allocated
 */
#define MAX_NUM_BUFS            (CAL_APP_NUM_FRAMES)

/*
 * \brief Maximum Buffer Size, assuming input size is always greater
 */
#define MAX_BUF_SIZE            (1280U * 800U * 2U)

#pragma DATA_ALIGN(gFrameBufArray, 32)
UInt8 gFrameBufArray[MAX_NUM_BUFS][MAX_BUF_SIZE];

typedef struct
{
    UInt32      inpIdx;
    /* This is a counter which will provide MAX_NUM_BUFS_PER_PORT buffers
     * addresses to CAL in a cyclical manner */

    VpsCore_Frame frm[MAX_NUM_BUFS];
    /* This stores frame addresses in a format understood by CAL driver */
} App_FrameBufObj;

App_FrameBufObj gFrameBufObj;

void CalAppUtils_FrameBufInit(void)
{
    UInt32       index;
    VpsCore_Frame *frm;

    gFrameBufObj.inpIdx = 0U;
    for (index = 0U; index < MAX_NUM_BUFS; index++)
    {
        frm             = &(gFrameBufObj.frm[index]);
        frm->drvData    = NULL;
        frm->streamId   = 0;      /* Ignore for current use-case */
        frm->chId       = 0;      /* Ignore for current use-case */
        frm->dropFrm    = 0;      /* Ignore for current use-case */
        frm->coreStats  = 0;      /* Ignore for current use-case */
        frm->addr[0U][0U] = &gFrameBufArray[index][0U]; /*Frame address */
    }
}

void CalAppUtils_FrameBufDeInit(void)
{
    /* No book-keeping required since buffers are statically allocated */
}

VpsCore_Frame *CalAppUtils_GetFrameBuf(void)
{
    VpsCore_Frame *frm;

    frm = &(gFrameBufObj.frm[gFrameBufObj.inpIdx]);

    /* This is to keep cycling between buffer allocated for the specified port*/
    gFrameBufObj.inpIdx++;
    if (gFrameBufObj.inpIdx >= MAX_NUM_BUFS)
    {
        gFrameBufObj.inpIdx = 0U;
    }

    return frm;
}

void CalAppUtils_ReleaseFrameBuf(VpsCore_Frame *frm)
{
    /* No book-keeping required since buffers are statically allocated */
}
