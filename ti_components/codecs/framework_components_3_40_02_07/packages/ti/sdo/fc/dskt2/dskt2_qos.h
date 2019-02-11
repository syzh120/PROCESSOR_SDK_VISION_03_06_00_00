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
 *  ======== dskt2_qos.h ========
 *  DSKT2 QOS support library definitions.
 *
 */

#ifndef DSKT2_QOS_H
#define DSKT2_QOS_H

#include <xdc/std.h>
#include <xdc/runtime/Memory.h>

typedef enum DSKT2_QOS_TI_MsgArg1Types {
    DSKT2_QOS_SHARED_SCRATCH_ALLHEAPS = 0x200,
    DSKT2_QOS_SHARED_SCRATCH_DARAM = 0x201,
    DSKT2_QOS_SHARED_SCRATCH_SARAM = 0x202
} DSKT2_QOS_TI_MsgArg1Types;

typedef enum DSKT2_QOS_TI_GetSharedScratchMsgArg2   {
    /*
     * If Arg2 is NOT ALL_SCRATCHGROUPS then  the assigned value
     * is Scratch Group/Mutex Id
     */
    DSKT2_QOS_ALL_SCRATCHGROUPS = 0x100
} DSKT2_QOS_TI_GetSharedScratchMsgArg2;

extern Void  DSKT2_QOS_getStat(UInt heapType, UInt mutexId,
        UInt *sizeSharedScratch, xdc_runtime_IHeap_Handle *inHeap);

#endif
