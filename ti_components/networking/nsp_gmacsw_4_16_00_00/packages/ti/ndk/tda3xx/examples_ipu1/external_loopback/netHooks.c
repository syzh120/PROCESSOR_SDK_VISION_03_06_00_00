/*
 *  netHooks.c
 */

/*
 * Copyright (C) 2007-2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <xdc/std.h>

#include <ti/sysbios/knl/Task.h>

#include <ti/ndk/inc/netmain.h>
#include <ti/ndk/inc/tools/servers.h>
#include <ti/ndk/inc/tools/console.h>


Task_Handle recvTask;
Task_Handle sendTask;

extern void recvTaskFxn(UArg arg0, UArg arg1);
extern void sendTaskFxn(UArg arg0, UArg arg1);

void netOpenHook()
{
    {
        Task_Params taskParams;
        Task_Params_init(&taskParams);
        taskParams.instance->name = "Raw_Sender";
        taskParams.stackSize = 0x1000;
        taskParams.priority = 1;
        sendTask = Task_create((Task_FuncPtr)sendTaskFxn, &taskParams,NULL);
    }
#if (0)
    {
        Task_Params taskParams;
        Task_Params_init(&taskParams);
        taskParams.instance->name = "Raw_Receiver";
        taskParams.stackSize = 0x1000;
        taskParams.priority = 1;
        recvTask = Task_create((Task_FuncPtr)recvTaskFxn, &taskParams,NULL);
    }
#endif
}

void netCloseHook()
{
    Task_delete(&sendTask);
    Task_delete(&recvTask);
}
