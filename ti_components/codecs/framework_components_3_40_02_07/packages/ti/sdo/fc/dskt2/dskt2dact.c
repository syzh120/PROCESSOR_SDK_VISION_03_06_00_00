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
 *  ======== dskt2dact.c ========
 *  Function to simplify call to algorithm's algDeactivate() function.
 *
 */

/* This define must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_dskt2_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/xdais/ialg.h>

#include "dskt2.h"
#include "_dskt2.h"

#include "dskt2_lock.h"

extern Registry_Desc ti_sdo_fc_dskt2_desc;

/*
 * ======== DSKT2_deactivateAlg ========
 *
 * Performs 'optimistic' algorithm activation/deactivation!
 * That is: alg 'deactivation' does not happen until  some *other* algorithm
 * instance needs to be activated.
 * When activating the new algorithm, the former (i.e.'current') active
 * instance gets deactivated.
 */
Void DSKT2_deactivateAlg(Int scratchId, IALG_Handle alg)
{

#ifndef DSKT2_DISABLELAZYD
    Bool isScratch;
#endif

    Log_print2(Diags_ENTRY, "[+E] DSKT2_deactivateAlg> Enter "
            "(scratchId=%d, algHandle=0x%x)", (IArg)scratchId, (IArg)alg);

#ifndef DSKT2_DISABLELAZYD
    isScratch = (scratchId >= 0) && (scratchId < DSKT2_NUM_SCRATCH_GROUPS);

    if (isScratch) {
        _DSKT2_lastActiveAlg[scratchId] = alg;
        _DSKT2_activeAlg[scratchId] = NULL;

        Log_print1(Diags_USER4, "[+4] DSKT2_deactivateAlg> "
                "Lazy deactivate of algorithm 0x%x", (IArg)alg);
    }
    else {
#endif
        if ((alg != NULL) && (alg->fxns->algDeactivate != NULL)) {

            Log_print1(Diags_USER4,
                    "[+4] DSKT2_deactivateAlg> Real deactivate of algorithm 0x%x",
                    (IArg)alg);

            Log_print1(Diags_USER2, "[+2] DSKT2_deactivateAlg> "
                    "Release lock for scratch group %d", (IArg)scratchId);

            /* Deactivate if alg is not using scratch */
            alg->fxns->algDeactivate(alg);
        }
#ifndef DSKT2_DISABLELAZYD
    }
#endif

    /*
     * Release lock that was acquired during activate
     */
    DSKT2_releaseLock(scratchId);

    if (_DSKT2_yielded) {
        _DSKT2_yielded = 0;
        _DSKT2_NumYielded--;
    }

    Log_print0(Diags_EXIT, "[+X] DSKT2_deactivateAlg> Exit");
}

/*
 *  ======== DSKT2_deactivateAll ========
 */
Int DSKT2_deactivateAll()
{
#ifndef DSKT2_DISABLELAZYD
    IALG_Handle alg;
    Int         i;
#endif
    Int         nActive = 0;

    Log_print0(Diags_ENTRY, "[+E] DSKT2_deactivateAll Enter");

#ifndef DSKT2_DISABLELAZYD

    if (_DSKT2_lastActiveAlg == NULL) {
        /*
         *  Memory not yet allocated for _DSKT2_lastActiveAlg ( _DSKT2_init not
         *  yet called), so return "0" active algorithms
         */
        return (nActive);
    }

    /*
     *  Deactivate all algs that have been lazily deactivated.
     */
    for (i = 0; i < DSKT2_NUM_SCRATCH_GROUPS; i++) {

        if ((alg = _DSKT2_lastActiveAlg[i]) != NULL) {
            if (alg->fxns->algDeactivate != NULL) {

                Log_print2(Diags_USER4,
                        "[+4] DSKT2_deactivateAll> Real deactivate of algorithm "
                        "0x%x in scratch group %d", (IArg)alg, (IArg)i);

                alg->fxns->algDeactivate(alg);
            }
            _DSKT2_lastActiveAlg[i] = NULL;
        }

        if (_DSKT2_activeAlg[i] != NULL) {

            Log_print2(Diags_USER2, "[+2] DSKT2_deactivateAll>"
                    " Algorithm 0x%x in scratch group %d still active",
                    (IArg)alg, (IArg)i);

            nActive++;
        }
    }
#endif

    Log_print1(Diags_EXIT, "[+X] DSKT2_deactivateAll Exit (numActive=%d)",
            (IArg)(nActive + _DSKT2_NumYielded));

    return (nActive + _DSKT2_NumYielded);
}
