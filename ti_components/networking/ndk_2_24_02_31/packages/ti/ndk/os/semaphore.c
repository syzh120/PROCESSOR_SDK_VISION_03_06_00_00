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
 * */
/*
 * ======== semaphore.c ========
 *
 * Semaphore management using BIOS6
 *
 */

#include <netmain.h>
#include <_stack.h>
#include <_oskern.h>

/* XDC/BIOS6 Includes */
#include <xdc/std.h>

#include <xdc/runtime/Error.h>

#include <ti/sysbios/knl/Semaphore.h>

/*
 *  ======== SemCreate ========
 *  Create a semaphore.
 */
HANDLE SemCreate(int Count)
{
    Error_Block eb;
    HANDLE sem;

    Error_init(&eb);

    /* create the new semaphore */
    sem = (HANDLE)Semaphore_create((Int)Count, NULL, &eb);

    if (Error_check(&eb)) {
        /* Should not get here */
        DbgPrintf(DBG_ERROR,"SemCreate(): could not create semaphore");
    }

    return (sem);
}

/*
 *  ======== SemCreateBinary ========
 *  Create a binary semaphore.
 */
HANDLE SemCreateBinary(int Count)
{
    Error_Block eb;
    Semaphore_Params semParams;
    HANDLE sem;

    Error_init(&eb);

    /* create the new semaphore */
    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_BINARY;
    sem = (HANDLE)Semaphore_create((Int)Count, &semParams, &eb);

    if (Error_check(&eb)) {
        /* Should not get here */
        DbgPrintf(DBG_ERROR,"SemCreateBinary(): could not create semaphore");
    }

    return (sem);
}

/*
 *  ======== SemDelete ========
 *  Delete a semaphore.
 */
void SemDelete(HANDLE hSem)
{
    Semaphore_delete((Semaphore_Handle *)&hSem);
}

/*
 *  ======== SemCount ========
 *  Get the current semaphore count.
 */
int SemCount(HANDLE hSem)
{
    return ((int)Semaphore_getCount((Semaphore_Handle)hSem));
}

/*
 *  ======== SemPend ========
 *  Wait for a semaphore.
 */
int SemPend(HANDLE hSem, UINT32 Timeout)
{
    return ((int)Semaphore_pend((Semaphore_Handle)hSem, (UInt)Timeout));
}

/*
 *  ======== SemPost ========
 *  Signal a semaphore.
 */
void SemPost(HANDLE hSem)
{
    Semaphore_post((Semaphore_Handle)hSem);
}

/*
 *  ======== SemReset ========
 *  Reset a semaphore's count.
 */
void SemReset(HANDLE hSem, int Count)
{
    Semaphore_reset((Semaphore_Handle)hSem, (Int)Count);
}
