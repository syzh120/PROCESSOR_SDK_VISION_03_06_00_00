/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
/*
 *  ======== gt_dais.c ========
 */

#include <xdc/std.h>
#include <ti/xdais/ialg.h>
#include "gt_dais.h"

/*
 *  ======== gt_MemAttrs ========
 */
char * gt_MemAttrs(IALG_MemAttrs index)
{
    switch(index) {

    case IALG_SCRATCH:
        return (SCRATCH);

    case IALG_PERSIST:
        return (PERSIST);

    case IALG_WRITEONCE:
        return  (WRITEONCE);

    default:
        return (UNDEF);
    }
}


/*
 *  ======== gt_MemSpace ========
 */
char * gt_MemSpace(IALG_MemSpace index)
{
    switch(index) {

        case IALG_EPROG:
            return (EPROG);

        case IALG_IPROG:
            return (IPROG);

        case IALG_ESDATA:
            return (ESDATA);

        case IALG_EXTERNAL:
            return (EXTERNAL);

        case IALG_DARAM0:
            return (DARAM0);

        case IALG_DARAM1:
            return (DARAM1);

        case IALG_SARAM:
            return (SARAM);

        case IALG_SARAM1:
            return (SARAM1);

        case IALG_DARAM2:
            return (DARAM2);

        case IALG_SARAM2:
            return (SARAM2);

        default:
            return (UNDEF);
    }
}
