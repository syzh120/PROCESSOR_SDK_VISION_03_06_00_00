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
 *  ======== dskt2ctrl.c ========
 *  Function to simplify call to algorithm's algControl() function.
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

extern Registry_Desc ti_sdo_fc_dskt2_desc;


/*
 *  ======== DSKT2_controlAlg ========
 */
Int DSKT2_controlAlg(IALG_Handle alg, IALG_Cmd cmd, IALG_Status *status)
{
    Int retVal = IALG_EFAIL;
    Log_print2(Diags_ENTRY, "[+E] DSKT2_controlAlg> Enter (alg=0x%x, cmd=%d)",
            (IArg)alg, (IArg)cmd);

    if ((alg != NULL) && (status != NULL) && (alg->fxns->algControl != NULL)) {

        Log_print1(Diags_USER4, "[+4] DSKT2_controlAlg> Command %d", (IArg)cmd);

        retVal = alg->fxns->algControl(alg, cmd, status);
    }

    Log_print1(Diags_EXIT, "[+X] DSKT2_controlAlg> Exit (status=%d)",
            (IArg)retVal);

    return (retVal);
}
