/*
 * Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
 * */
/*
 *  ======== MultiProc.c ========
 *  Implementation of functions specified in MultiProc.xdc.
 */

#include <xdc/std.h>
#include <string.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Startup.h>

#include <ti/sdo/utils/_MultiProc.h>

#include "package/internal/MultiProc.xdc.h"

#ifdef __ti__
    #pragma FUNC_EXT_CALLED(MultiProc_getBaseIdOfCluster);
    #pragma FUNC_EXT_CALLED(MultiProc_getClusterProcList);
    #pragma FUNC_EXT_CALLED(MultiProc_getId);
    #pragma FUNC_EXT_CALLED(MultiProc_getName);
    #pragma FUNC_EXT_CALLED(MultiProc_getNumProcessors);
    #pragma FUNC_EXT_CALLED(MultiProc_getNumProcsInCluster);
    #pragma FUNC_EXT_CALLED(MultiProc_self);
    #pragma FUNC_EXT_CALLED(MultiProc_setLocalId);
    #pragma FUNC_EXT_CALLED(MultiProc_setBaseIdOfCluster);
#endif

/*
 *************************************************************************
 *                       Common Header Functions
 *************************************************************************
 */

/*
 *  ======== MultiProc_getBaseIdOfCluster ========
 */
UInt16 MultiProc_getBaseIdOfCluster()
{
    return (MultiProc_module->baseIdOfCluster);
}

/*
 *  ======== MultiProc_getClusterProcList ========
 */
UInt16 *MultiProc_getClusterProcList()
{
    return (MultiProc_module->clusterProcList);
}

/*
 *  ======== MultiProc_getId ========
 */
UInt16 MultiProc_getId(String name)
{
    Int    i;
    UInt16 id;

    Assert_isTrue(name != NULL, ti_sdo_utils_MultiProc_A_invalidProcName);

    id = MultiProc_INVALIDID;
    for (i = 0; i < ti_sdo_utils_MultiProc_numProcsInCluster; i++) {
        if ((ti_sdo_utils_MultiProc_nameList[i] != NULL) &&
            (strcmp(name, ti_sdo_utils_MultiProc_nameList[i]) == 0)) {
            id = i + MultiProc_module->baseIdOfCluster;
        }
    }
    return (id);
}

/*
 *  ======== MultiProc_getClusterId ========
 */
UInt16 ti_sdo_utils_MultiProc_getClusterId(UInt16 procId)
{
    return (procId - MultiProc_module->baseIdOfCluster);
}

/*
 *  ======== MultiProc_getName ========
 */
String MultiProc_getName(UInt16 id)
{
    Assert_isTrue((id < ti_sdo_utils_MultiProc_numProcessors),
            ti_sdo_utils_MultiProc_A_invalidMultiProcId);

    return (ti_sdo_utils_MultiProc_nameList[id -
            MultiProc_module->baseIdOfCluster]);
}

/*
 *  ======== MultiProc_getNumProcessors ========
 */
UInt16 MultiProc_getNumProcessors()
{
    return (ti_sdo_utils_MultiProc_numProcessors);
}

/*
 *  ======== MultiProc_getNumProcsInCluster ========
 */
UInt16 MultiProc_getNumProcsInCluster()
{
    return (ti_sdo_utils_MultiProc_numProcsInCluster);
}

/*
 *  ======== MultiProc_self ========
 */
UInt16 MultiProc_self()
{
    return (MultiProc_module->id);
}

/*
 *  ======== MultiProc_setLocalId ========
 */
Int MultiProc_setLocalId(UInt16 id)
{
    /* id must be less than the number of processors */
    Assert_isTrue((id < ti_sdo_utils_MultiProc_numProcessors),
            ti_sdo_utils_MultiProc_A_invalidMultiProcId);

    /*
     *  Check the following
     *  1. Make sure the statically configured constant was invalid.
     *     To call setLocalId, the id must have been set to invalid.
     *  2. Make sure the call is made before module startup
     */
    if ((MultiProc_self() == MultiProc_INVALIDID) &&
        (Startup_rtsDone() == FALSE)) {

        /* It is ok to set the id */
        MultiProc_module->id = id;
        return (MultiProc_S_SUCCESS);
    }

    return (MultiProc_E_FAIL);
}

/*
 *  ======== MultiProc_setBaseIdOfCluster ========
 */
Int MultiProc_setBaseIdOfCluster(UInt16 id)
{
    /*
     *  Check the following
     *  1. Make sure the statically configured constant was invalid.
     *     To call setBaseIdOfCluster, the id must have been set to invalid.
     *  2. Make sure the call is made before module startup
     */
    if ((MultiProc_getBaseIdOfCluster() == MultiProc_INVALIDID) &&
        (Startup_rtsDone() == FALSE)) {
        /* It is ok to set the id */
        MultiProc_module->baseIdOfCluster = id;
        return (MultiProc_S_SUCCESS);
    }

    return (MultiProc_E_FAIL);
}

/*
 *  ======== ti_sdo_utils_MultiProc_dummy ========
 */
Void ti_sdo_utils_MultiProc_dummy()
{
}
