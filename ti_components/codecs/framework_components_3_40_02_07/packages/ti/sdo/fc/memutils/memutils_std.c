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
 *  ======== MEMUTILS_std.c ========
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_memutils_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/fc/global/FCSettings.h>

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "memutils.h"


__FAR__ static Int regInit = 0;  /* Registry_addModule() called */

__FAR__ Registry_Desc ti_sdo_fc_memutils_desc;

__FAR__ static Void addModule();

/*
 *  ======== MEMUTILS_cacheInv ========
 */
/* ARGSUSED - this line tells TI compilers not to warn about unused args. */
Void MEMUTILS_cacheInv(Ptr addr, Int sizeInBytes)
{
}


/*
 *  ======== MEMUTILS_cacheWb ========
 */
/* ARGSUSED - this line tells TI compilers not to warn about unused args. */
Void MEMUTILS_cacheWb(Ptr addr, Int sizeInBytes)
{
}


/*
 *  ======== MEMUTILS_cacheWbInv ========
 */
/* ARGSUSED - this line tells TI compilers not to warn about unused args. */
Void MEMUTILS_cacheWbInv(Ptr addr, Int sizeInBytes)
{
}



/*
 *  ======== MEMUTILS_getPhysicalAddress ========
 */
Void * MEMUTILS_getPhysicalAddr(Ptr physicalAddress)
{
    if (!regInit) {
        addModule();
    }

    Log_print1(Diags_ENTRY, "[+E] MEMUTILS_getBufferVirtualAddress(0x%lx)",
            (IArg)physicalAddress);

    return ((Void *)physicalAddress);
}

/*
 *  ======== addModule ========
 */
static Void addModule()
{
    Registry_Result result;

    result = Registry_addModule(&ti_sdo_fc_memutils_desc,
            MEMUTILS_MODNAME);
    Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

    if (result == Registry_SUCCESS) {
        /* Set the diags mask to the FC default */
        FCSettings_init();
        FCSettings_setDiags(MEMUTILS_MODNAME);
    }
    regInit = 1;
}
