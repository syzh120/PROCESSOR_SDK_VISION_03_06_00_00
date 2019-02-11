/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef HDVICP2_H
#define HDVICP2_H

#include "ires_hdvicp2.h"

#define _HDVICP2_MAXRESOURCES 10

typedef XDAS_Void (*ConfigFxn)(IALG_Handle algHandle,
        IRES_HDVICP2_Obj * hdvicpHandle,
        IRES_HDVICP2_CallbackFxn cbFunctionPtr, XDAS_Void *cbArgs);
typedef XDAS_UInt32 (*WaitFxn)(IALG_Handle algHandle,
        IRES_HDVICP2_Obj *hdvicpHandle, IRES_YieldContext * yieldCtxt);
typedef XDAS_Void (*DoneFxn)(IALG_Handle algHandle,
        IRES_HDVICP2_Obj *hdvicpHandle);
typedef XDAS_UInt32 (*ResetFxn)(IALG_Handle algHandle,
        IRES_HDVICP2_Obj *hdvicpHandle);

typedef struct HDVICP2_Params {
    ConfigFxn configFxn;
    WaitFxn waitFxn;
    DoneFxn doneFxn;
    UInt32 memoryBaseAddress[_HDVICP2_MAXRESOURCES];
    UInt32 resetControlAddress[_HDVICP2_MAXRESOURCES];
    UInt32 registerBaseAddress[_HDVICP2_MAXRESOURCES];
    ResetFxn resetFxn;
} HDVICP2_Params;

extern __FAR__ HDVICP2_Params HDVICP2_PARAMS;

extern __FAR__ unsigned int _HDVICP2_NUMRESOURCES;

extern XDAS_UInt32 ti_sdo_fc_ires_hdvicp_HDVICP2_reset_Omap(
        IALG_Handle algHandle, IRES_HDVICP2_Handle iresHandle);

extern XDAS_UInt32 ti_sdo_fc_ires_hdvicp_HDVICP2_reset_Netra(
        IALG_Handle algHandle, IRES_HDVICP2_Handle iresHandle);

extern UInt ti_sdo_fc_ires_hdvicp_HDVICP2_interrupts[];

#endif /* HDVICP2_H */
