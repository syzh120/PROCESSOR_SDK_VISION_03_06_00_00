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
 *  ======== dskt2_seg.c ========
 *  Keep _DSKT2_spaceToSeg() in a separate file, so tests can replace this
 *  function with there own. This way we can test different DSKT2
 *  configurations without having to keep a separate cfg file for each test.
 */


#include <xdc/std.h>
#include <xdc/runtime/IHeap.h>

#include <ti/xdais/ialg.h>

#include "_dskt2.h"
#include <ti/sdo/fc/dskt2/dskt2.h>


/*
 *  ======== _DSKT2_spaceToSeg ========
 */
xdc_runtime_IHeap_Handle _DSKT2_spaceToSeg(UInt space)
{
    xdc_runtime_IHeap_Handle heap;

    switch (space) {
        case IALG_DARAM0:
            heap = DSKT2_daram0Heap;
            break;
        case IALG_DARAM1:
            heap = DSKT2_daram1Heap;
            break;
        case IALG_DARAM2:
            heap = DSKT2_daram2Heap;
            break;
        case IALG_SARAM0:
            heap = DSKT2_saram0Heap;
            break;
        case IALG_SARAM1:
            heap = DSKT2_saram1Heap;
            break;
        case IALG_SARAM2:
            heap = DSKT2_saram2Heap;
            break;
        case IALG_IPROG:
            heap = DSKT2_iprogHeap;
            break;
        case IALG_EPROG:
            heap = DSKT2_eprogHeap;
            break;
        case IALG_ESDATA:
            heap = DSKT2_esdataHeap;
            break;
        default:
            heap = DSKT2_esdataHeap;
    }

    return (heap);
}
