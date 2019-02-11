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
 */
/*
 * ======== MultiProcCfg.c ========
 * System-wide MultiProc configuration
 */

/* Standard IPC headers */
#include <ti/ipc/Std.h>

/* For Backplane IPC startup/shutdown stuff: */
#include <_MultiProc.h>

/* This must match BIOS side MultiProc configuration for given platform!: */
MultiProc_Config _MultiProc_cfg =  {
   .numProcessors = 9,
   .nameList[0] = "HOST",
   .nameList[1] = "CORE0",
   .nameList[2] = "CORE1",
   .nameList[3] = "CORE2",
   .nameList[4] = "CORE3",
   .nameList[5] = "CORE4",
   .nameList[6] = "CORE5",
   .nameList[7] = "CORE6",
   .nameList[8] = "CORE7",
   .rprocList[0] = -1,
   .rprocList[1] = 0,
   .rprocList[2] = 1,
   .rprocList[3] = 2,
   .rprocList[4] = 3,
   .rprocList[5] = 4,
   .rprocList[6] = 5,
   .rprocList[7] = 6,
   .rprocList[8] = 7,
   .id = 0,             /* host processor must be coherent with cluster */
   .numProcsInCluster = 9,
   .baseIdOfCluster = 0
};
