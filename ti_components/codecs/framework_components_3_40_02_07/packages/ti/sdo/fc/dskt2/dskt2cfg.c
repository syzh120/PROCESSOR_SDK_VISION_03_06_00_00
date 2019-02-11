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
/*
 *  ======== dskt2cfg.c ========
 *  For non-xdc config.
 */


#include <xdc/std.h>
#include <xdc/runtime/IHeap.h>
#include "_dskt2.h"

/*
 *  ======== _DSKT2_ALLOW_EXTERNAL_SCRATCH ========
 *  Allow external memory to be used for algorithm scratch memory requests.
 *
 *  If an algorithm requests scratch memory, and insufficient scratch
 *  memory is available, scratch buffers will be allocated in external
 *  memory if _DSKT2_ALLOW_EXTERNAL_SCRATCH is non-zero.
 */
__FAR__ Uns _DSKT2_ALLOW_EXTERNAL_SCRATCH = 0;

/*
 *  ======== _DSKT2_DARAM_SCRATCH_SIZES ========
 *  Shared IALG_DARAM0 scratch group sizes. Modify as needed.
 */
__FAR__ Uns _DSKT2_DARAM_SCRATCH_SIZES[DSKT2_NUM_SCRATCH_GROUPS] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

/*
 *  ======== _DSKT2_SARAM_SCRATCH_SIZES ========
 *  Shared IALG_SARAM0 scratch group sizes. Modify as needed.
 */
__FAR__ Uns _DSKT2_SARAM_SCRATCH_SIZES[DSKT2_NUM_SCRATCH_GROUPS] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

/*
 *  Declaration of DSKT2 scratch heaps. Please do not modify.
 */
__FAR__ xdc_runtime_IHeap_Handle DSKT2_daram0Heap = NULL;
__FAR__ xdc_runtime_IHeap_Handle DSKT2_daram1Heap = NULL;
__FAR__ xdc_runtime_IHeap_Handle DSKT2_daram2Heap = NULL;
__FAR__ xdc_runtime_IHeap_Handle DSKT2_saram0Heap = NULL;
__FAR__ xdc_runtime_IHeap_Handle DSKT2_saram1Heap = NULL;
__FAR__ xdc_runtime_IHeap_Handle DSKT2_saram2Heap = NULL;
__FAR__ xdc_runtime_IHeap_Handle DSKT2_iprogHeap = NULL;
__FAR__ xdc_runtime_IHeap_Handle DSKT2_eprogHeap = NULL;
__FAR__ xdc_runtime_IHeap_Handle DSKT2_esdataHeap = NULL;
__FAR__ xdc_runtime_IHeap_Handle _DSKT2_heap = NULL;

#ifdef USEDSKT2CACHEWB
extern Void DSKT2_cacheWBInv(Ptr blockPtr, size_t byteCnt, Bool wait);

__FAR__ DSKT2_CacheWBInvFxn DSKT2_cacheWBInvFxn = (DSKT2_CacheWBInvFxn)DSKT2_cacheWBInv;
#else

__FAR__ DSKT2_CacheWBInvFxn DSKT2_cacheWBInvFxn = (DSKT2_CacheWBInvFxn)NULL;
#endif

UInt32 _DSKT2_ipcKeyBase = 0x44534B54;

__FAR__ Bool ti_sdo_fc_dskt2_DSKT2_disableLazyDeactivate = FALSE;

/*
 *  ======== DSKT2_cfgInit ========
 *  Initialize DSKT2 variables for non-RTSC configuration.
 */
Void DSKT2_cfgInit()
{
}
