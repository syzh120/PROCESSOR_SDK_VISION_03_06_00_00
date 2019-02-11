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
 */
/*
 *  ======== GateMPSupportNull.c ========
 *  Implementation of functions specified in GateMPSupportNull.xdc.
 *
 */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/IGateProvider.h>

#include <ti/sdo/ipc/interfaces/IGateMPSupport.h>

#include "package/internal/GateMPSupportNull.xdc.h"

/*
 *************************************************************************
 *                       Instance functions
 *************************************************************************
 */

/*
 *  ======== GateMPSupportNull_Instance_init ========
 */
Void GateMPSupportNull_Instance_init(GateMPSupportNull_Object *obj,
        IGateProvider_Handle localGate, const GateMPSupportNull_Params *params)
{
    obj->resourceId = params->resourceId;
}

/*
 *  ======== GateMPSupportNull_getResourceId ========
 */
Bits32 GateMPSupportNull_getResourceId(GateMPSupportNull_Object *obj)
{
    return (1);
}

/*
 *  ======== GateMPSupportNull_enter ========
 *  Returns FIRST_ENTER when it gets the gate, returns NESTED_ENTER
 *  on nested calls.
 */
IArg GateMPSupportNull_enter(GateMPSupportNull_Object *obj)
{
    if (GateMPSupportNull_action == GateMPSupportNull_Action_ASSERT) {
        Assert_isTrue(FALSE, GateMPSupportNull_A_invalidAction);
    }

    return (0);
}

/*
 *  ======== GateMPSupportNull_leave ========
 *  Only releases the gate if key == FIRST_ENTER.
 */
Void GateMPSupportNull_leave(GateMPSupportNull_Object *obj, IArg key)
{
    if (GateMPSupportNull_action == GateMPSupportNull_Action_ASSERT) {
        Assert_isTrue(FALSE, GateMPSupportNull_A_invalidAction);
    }
}

/*
 *************************************************************************
 *                       Module functions
 *************************************************************************
 */

/*
 *  ======== GateMPSupportNull_getReservedMask ========
 */
Bits32 *GateMPSupportNull_getReservedMask()
{
    /* This gate doesn't allow reserving resources */
    return (NULL);
}

/*
 *  ======== GateSupportNull_query ========
 *
 */
Bool GateMPSupportNull_query(Int qual)
{
    return (FALSE);
}


/*
 *  ======== GateMPSupportNull_sharedMemReq ========
 */
SizeT GateMPSupportNull_sharedMemReq(const IGateMPSupport_Params *params)
{
    return (0);
}
