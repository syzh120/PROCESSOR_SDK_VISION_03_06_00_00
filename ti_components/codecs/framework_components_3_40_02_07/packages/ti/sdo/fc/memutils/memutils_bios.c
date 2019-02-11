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
 *  ======== MEMUTILS_BIOS.c ========
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_memutils_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <ti/sdo/fc/global/FCSettings.h>
#include <ti/sdo/fc/global/Settings.h>

#include <string.h>

#include <ti/sysbios/hal/Cache.h>

#include "memutils.h"

#ifdef xdc_target__isaCompatible_64P
extern __cregister volatile Uns DNUM;
static inline Uns MC_ADDR_LOC_TO_GLOB(Uns loc_addr);
#else
#define MC_ADDR_LOC_TO_GLOB(addr) (addr)
#endif

__FAR__ static Int regInit = 0;  /* Registry_addModule() called */

__FAR__ Registry_Desc ti_sdo_fc_memutils_desc;

static Void addModule();

/*
 *  ======== MEMUTILS_cacheInv ========
 */
Void MEMUTILS_cacheInv(Ptr addr, Int sizeInBytes)
{
    if (!regInit) {
        addModule();
    }

    Log_print2(Diags_ENTRY, "[+E] MEMUTILS_cacheInv> "
            "Enter(addr=0x%x, sizeInBytes=%d)", (IArg)addr, (IArg)sizeInBytes);

    Cache_inv(addr, sizeInBytes, Cache_Type_ALL, TRUE);

    Log_print0(Diags_ENTRY, "[+E] MEMUTILS_cacheInv> return");
}


/*
 *  ======== MEMUTILS_cacheWb ========
 */
Void MEMUTILS_cacheWb(Ptr addr, Int sizeInBytes)
{
    if (!regInit) {
        addModule();
    }

    Log_print2(Diags_ENTRY, "[+E] MEMUTILS_cacheWb> "
            "Enter(addr=0x%x, sizeInBytes=%d)", (IArg)addr, (IArg)sizeInBytes);

    Cache_wb(addr, sizeInBytes, Cache_Type_ALL, TRUE);

    Log_print0(Diags_ENTRY, "[+E] MEMUTILS_cacheWb> return");
}


/*
 *  ======== MEMUTILS_cacheWbInv ========
 */
Void MEMUTILS_cacheWbInv(Ptr addr, Int sizeInBytes)
{
    if (!regInit) {
        addModule();
    }

    Log_print2(Diags_ENTRY, "[+E] MEMUTILS_cacheWbInv> "
            "Enter(addr=0x%x, sizeInBytes=%d)", (IArg)addr, (IArg)sizeInBytes);

    Cache_wbInv(addr, sizeInBytes, Cache_Type_ALL, TRUE);

    Log_print0(Diags_ENTRY, "[+E] MEMUTILS_cacheWbInv> return");
}


/*
 *  ======== MEMUTILS_getPhysicalAddr ========
 */
Void * MEMUTILS_getPhysicalAddr(Ptr addr)
{
    if (!regInit) {
        addModule();
    }

    Log_print1(Diags_ENTRY, "[+E] MEMUTILS_getPhysicalAddr 0x%x",
            (IArg)addr);

    if (ti_sdo_fc_useL3MemoryMap) {
        /* Check if passed address is an internal memory address and if so
           offset it appropriate */
        if ((((Uns)addr & 0xfff00000) == 0x10f00000) ||
                (((Uns)addr & 0xfff00000) == 0x10800000) ||
                (((Uns)addr & 0xfff00000) == 0x00f00000) ||
                (((Uns)addr & 0xfff00000) == 0x00800000)) {
            return ((Void *)(((Uns)addr & 0x0fffffff) | 0x40000000));
        }
    }

    if (ti_sdo_fc_useDNUM) {
        return (Void *)MC_ADDR_LOC_TO_GLOB((Uns)addr);
    }
    return ((Void *)addr);
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

#ifdef xdc_target__isaCompatible_64P
static inline Uns MC_ADDR_LOC_TO_GLOB(Uns loc_addr)
{

    Uns tmp = loc_addr;

    if ((tmp & 0xFF000000) == 0) {
        return ((1 << 28) | (DNUM << 24) | tmp);
    }
    else {
        return loc_addr;
    }
}
#endif
