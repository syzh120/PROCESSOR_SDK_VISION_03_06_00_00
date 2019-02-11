/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 */

/*
 *  ======== MxServer.c ========
 *
 *  Example implementation of the Mx module which runs on the host.
 *  The Mx module will invoke these function here using MmRpc.
 */

#include <stddef.h>
#include <stdint.h>

#include "MxServer.h"

/*
 *  ======== MxServer_triple ========
 */
int32_t MxServer_triple(uint32_t a)
{
    int32_t result;

    result = a * 3;

    return(result);
}

/*
 *  ======== MxServer_add ========
 */
int32_t MxServer_add(int32_t a, int32_t b)
{
    int32_t result;

    result = a + b;

    return(result);
}

/*
 *  ======== MxServer_compute ========
 */
int32_t MxServer_compute(MxServer_Compute *compute)
{
    int i;

    /* process inBuf into outBuf */
    for (i = 0; i < compute->size; i++) {
        compute->outBuf[i] = compute->coef | compute->inBuf[i];
    }

    /* write a cookie into the key */
    compute->key = 0xA0A0;

    return(0);
}
