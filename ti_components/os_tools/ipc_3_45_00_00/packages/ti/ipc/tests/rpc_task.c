/*
 * Copyright (c) 2013-2014, Texas Instruments Incorporated
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
 *  ======== rpc_task.c ========
 *
 *  Example of how to integrate the MxServer module with the
 *  MmService manager.
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/grcm/RcmServer.h>
#include <ti/ipc/mm/MmType.h>
#include <ti/ipc/mm/MmServiceMgr.h>
#include <ti/sysbios/hal/Cache.h>
#include <ti/ipc/MultiProc.h>

#include "MxServer.h"

/* turn on/off printf's */
#define CHATTER 1

typedef struct {
    Int a;
    Int b;
    Int c;
} FxnAdd3Args;

typedef struct {
    Int num;
    Int *array;
} FxnAddXArgs;


#define SERVICE_NAME "rpc_example"

/* MxServer skel function declarations */
static Int32 RPC_SKEL_Init2(UInt32 size, UInt32 *data);
static Int32 MxServer_skel_triple(UInt32 size, UInt32 *data);
static Int32 MxServer_skel_add(UInt32 size, UInt32 *data);
static Int32 fxnAdd3(UInt32 size, UInt32 *data);
static Int32 fxnAddX(UInt32 size, UInt32 *data);
static Int32 MxServer_skel_compute(UInt32 size, UInt32 *data);
static Int32 fxnFault(UInt32 size, UInt32 *data);

/* MxServer skel function array */
static RcmServer_FxnDesc mxSkelAry[] = {
    { "RPC_SKEL_Init2",         RPC_SKEL_Init2          },
    { "MxServer_triple",        MxServer_skel_triple    },
    { "MxServer_add",           MxServer_skel_add       },
    { "fxnAdd3",                fxnAdd3                 },
    { "fxnAddX",                fxnAddX                 },
    { "MxServer_compute",       MxServer_skel_compute   },
    { "fxnFault",               fxnFault                }
};

/* MxServer skel function table */
static const RcmServer_FxnDescAry rpc_fxnTab = {
    (sizeof(mxSkelAry) / sizeof(mxSkelAry[0])),
    mxSkelAry
};

static MmType_FxnSig rpc_sigAry[] = {
    { "RPC_SKEL_Init2", 3,
        {
            { MmType_Dir_Out, MmType_Param_S32, 1 }, /* return */
            { MmType_Dir_In,  MmType_Param_U32, 1 },
            { MmType_Dir_In,  MmType_PtrType(MmType_Param_U32), 1 }
        }
    },
    { "MxServer_triple", 2,
        {
            { MmType_Dir_Out, MmType_Param_S32, 1 }, /* return */
            { MmType_Dir_In,  MmType_Param_U32, 1 }
        }
    },
    { "MxServer_add", 3,
        {
            { MmType_Dir_Out, MmType_Param_S32, 1 }, /* return */
            { MmType_Dir_In,  MmType_Param_S32, 1 },
            { MmType_Dir_In,  MmType_Param_S32, 1 }
        }
    },
    { "fxnAdd3", 2,
        {
            { MmType_Dir_Out, MmType_Param_S32, 1 }, /* return */
            { MmType_Dir_In,  MmType_PtrType(MmType_Param_U32), 1 }
        }
    },
    { "fxnAddX", 2,
        {
            { MmType_Dir_Out, MmType_Param_S32, 1 }, /* return */
            { MmType_Dir_In,  MmType_PtrType(MmType_Param_U32), 1 }
        }
    },
    { "MxServer_compute", 2,
        {
            { MmType_Dir_Out, MmType_Param_S32, 1 }, /* return */
            { MmType_Dir_In,  MmType_PtrType(MmType_Param_VOID), 1 }
        }
    },
    { "fxnFault", 2,
        {
            { MmType_Dir_Out, MmType_Param_S32, 1 }, /* return */
            { MmType_Dir_In,  MmType_PtrType(MmType_Param_U32), 1 }
        }
    }
};

static MmType_FxnSigTab rpc_fxnSigTab = {
    MmType_NumElem(rpc_sigAry), rpc_sigAry
};

/* the server create parameters, must be in persistent memory */
static RcmServer_Params rpc_Params;


Void RPC_SKEL_SrvDelNotification(Void)
{
    System_printf("RPC_SKEL_SrvDelNotification: Nothing to cleanup for "
        "MmRpc instance id=%d\n", MmServiceMgr_getId());
}

static Int32 RPC_SKEL_Init2(UInt32 size, UInt32 *data)
{
    System_printf("RPC_SKEL_Init2: size=0x%x data=0x%x\n", size, data);
    return(0);
}

/*
 *  ======== MxServer_skel_triple ========
 */
Int32 MxServer_skel_triple(UInt32 size, UInt32 *data)
{
    MmType_Param *payload = (MmType_Param *)data;
    UInt32 a;
    Int32 result;

    a = (UInt32)payload[0].data;
    result = MxServer_triple(a);

#if CHATTER
    System_printf("fxnTriple: a=%d, result=%d\n", a, result);
#endif

    return(result);
}

/*
 *  ======== MxServer_skel_add ========
 */
Int32 MxServer_skel_add(UInt32 size, UInt32 *data)
{
    MmType_Param *payload = (MmType_Param *)data;
    Int32 a, b;
    Int32 result;

    a = (Int32)payload[0].data;
    b = (Int32)payload[1].data;

    result = MxServer_add(a, b);

#if CHATTER
    System_printf("fxnAdd: a=%d, b=%d, result=%d\n", a, b, result);
#endif

    return(result);
}

/*
 *  ======== fxnAdd3 ========
 */
Int32 fxnAdd3(UInt32 size, UInt32 *data)
{
    MmType_Param *payload = (MmType_Param *)data;
    FxnAdd3Args *args;
    Int a, b, c;

    args = (FxnAdd3Args *)payload[0].data;

    Cache_inv (args, sizeof(FxnAdd3Args), Cache_Type_ALL, TRUE);

    a = args->a;
    b = args->b;
    c = args->c;

#if CHATTER
    System_printf("fxnAdd3: a=%d, b=%d, c=%d\n", a, b, c);
#endif

    return(a + b + c);
}

/*
 *  ======== fxnAddX ========
 */
Int32 fxnAddX(UInt32 size, UInt32 *data)
{
    MmType_Param *payload = (MmType_Param *)data;
    FxnAddXArgs *args;
    Int num, i, sum = 0;
    Int *array;

    args = (FxnAddXArgs *)payload[0].data;

    Cache_inv (args, sizeof(FxnAddXArgs), Cache_Type_ALL, TRUE);

    num = args->num;
    array = args->array;

    Cache_inv (array, sizeof(Int) * num, Cache_Type_ALL, TRUE);

#if CHATTER
    System_printf("fxnAddX: ");
#endif
    for (i = 0; i < num; i++) {
#if CHATTER
        System_printf(" a[%d]=%d,", i, array[i]);
#endif
        sum += array[i];
    }

#if CHATTER
    System_printf(" sum=%d\n", sum);
#endif

    return(sum);
}

/*
 *  ======== MxServer_skel_compute ========
 */
Int32 MxServer_skel_compute(UInt32 size, UInt32 *data)
{
    MmType_Param *payload;
    MxServer_Compute *compute;
    Int32 result = 0;

    payload = (MmType_Param *)data;
    compute = (MxServer_Compute *)payload[0].data;

    Cache_inv(compute, sizeof(MxServer_Compute), Cache_Type_ALL, TRUE);

#if CHATTER
    System_printf("skel_compute: compute=0x%x\n", compute);
    System_printf("skel_compute: compute size=%d\n", (Int)payload[0].size);
    System_printf("skel_compute: coef=0x%x\n", compute->coef);
    System_printf("skel_compute: key=0x%x\n", compute->key);
    System_printf("skel_compute: size=0x%x\n", compute->size);
    System_printf("skel_compute: inBuf=0x%x\n", compute->inBuf);
    System_printf("skel_compute: outBuf=0x%x\n", compute->outBuf);
#endif

    Cache_inv(compute->inBuf, compute->size * sizeof(uint32_t),
            Cache_Type_ALL, TRUE);
    Cache_inv(compute->outBuf, compute->size * sizeof(uint32_t),
            Cache_Type_ALL, TRUE);

#if CHATTER
    System_printf("skel_compute: outBuf[0]=0x%x\n", compute->outBuf[0]);
    System_printf("skel_compute: inBuf[0]=0x%x\n", compute->inBuf[0]);
#endif

    /* invoke the implementation function */
    result = MxServer_compute(compute);

    Cache_wbInv(compute->outBuf, compute->size * sizeof(uint32_t),
            Cache_Type_ALL, TRUE);

    return(result);
}

/*
 *  ======== fxnAddX ========
 */
Int32 fxnFault(UInt32 size, UInt32 *data)
{
    MmType_Param *payload = (MmType_Param *)data;
    Int a;
    typedef Int (*MyCode)();
    MyCode fxn = (MyCode)0x96000000;
    volatile Int dummy = 0;

    a = (UInt32)payload[0].data;

    switch (a) {
        case 1:
            System_printf("Generating read MMU Fault...\n");
            a = *(volatile int *)(0x96000000);
            break;
        case 2:
            System_printf("Generating write MMU Fault...\n");
            *(volatile int *)(0x96000000) = 0x1;
            break;
        case 3:
            System_printf("Generating program MMU Fault...\n");
            fxn();
            break;
        case 4:
            System_printf("Generating exception...\n");
            dummy = dummy / dummy;
            break;
        case 5:
            System_printf("Generating Watchdog interrupt...\n");
            dummy = 1;
            while(dummy);
            break;
        default:
            System_printf("Invalid fxnFault test\n");
            break;
    }

    return(0);
}

/*
 *  ======== register_MxServer ========
 *
 *  Bootstrap function, must be configured in BIOS.addUserStartupFunctions.
 */
void register_MxServer(void)
{
    Int status = MmServiceMgr_S_SUCCESS;
    Char mMServerName[20];

    System_printf("register_MxServer: -->\n");

    /* must initialize these modules before using them */
    RcmServer_init();
    MmServiceMgr_init();

    /* setup the server create params */
    RcmServer_Params_init(&rpc_Params);
    rpc_Params.priority = Thread_Priority_ABOVE_NORMAL;
    rpc_Params.stackSize = 0x1000;
    rpc_Params.fxns.length = rpc_fxnTab.length;
    rpc_Params.fxns.elem = rpc_fxnTab.elem;

    /* Construct an MMServiceMgr name adorned with core name: */
    System_sprintf(mMServerName, "%s_%d", SERVICE_NAME,
                   MultiProc_self());

    /* register an example service */
    status = MmServiceMgr_register(mMServerName, &rpc_Params, &rpc_fxnSigTab,
            RPC_SKEL_SrvDelNotification);

    if (status < 0) {
        System_printf("register_MxServer: MmServiceMgr_register failed, "
                "status=%d\n", status);
        status = -1;
        goto leave;
    }

leave:
    System_printf("register_MxServer: <--, status=%d\n", status);
}
