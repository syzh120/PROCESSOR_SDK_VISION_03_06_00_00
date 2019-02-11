/*
 * Copyright (c) 2013-2015, Texas Instruments Incorporated
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
 *  ======== GateMutex.c ========
 */


/* Standard headers */
#include <ti/ipc/Std.h>

/* QNX headers */
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>

#include <ti/syslink/utils/IGateProvider.h>

/*
 * TODO: does this belong in ti/ipc/Std.h? We should consider getting rid of
 *       error blocks from the GateMutex.h interface.
 */
typedef UInt32            Error_Block;
#include <ti/syslink/utils/GateMutex.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* -----------------------------------------------------------------------------
 *  Structs & Enums
 * -----------------------------------------------------------------------------
 */
struct GateMutex_Object {
    IGateProvider_SuperObject;   /* For inheritance from IGateProvider */
    pthread_mutex_t mutex;       /* Mutex lock */
};


/* -----------------------------------------------------------------------------
 *  Forward declarations
 * -----------------------------------------------------------------------------
 */
IArg GateMutex_enter(GateMutex_Handle gmhandle);
Void GateMutex_leave(GateMutex_Handle gmhandle, IArg key);


/* -----------------------------------------------------------------------------
 *  APIs
 * -----------------------------------------------------------------------------
 */
GateMutex_Handle GateMutex_create(const GateMutex_Params * params,
    Error_Block *eb)
{
    pthread_mutexattr_t attr;

    GateMutex_Object * obj = (GateMutex_Object *)calloc(1,
        sizeof(GateMutex_Object));
    if (obj == NULL) {
        return NULL;
    }

    memset(obj, 0, sizeof(GateMutex_Object));
    IGateProvider_ObjectInitializer(obj, GateMutex);
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setrecursive(&attr, PTHREAD_RECURSIVE_ENABLE);
    pthread_mutex_init(&(obj->mutex), &attr);

    return (GateMutex_Handle)obj;
}

Int GateMutex_delete(GateMutex_Handle * handle)
{
    GateMutex_Object * obj = (GateMutex_Object *)*handle;

    if (handle == NULL) {
        return GateMutex_E_INVALIDARG;
    }
    if (*handle == NULL) {
        return GateMutex_E_INVALIDARG;
    }
    pthread_mutex_destroy(&(obj->mutex));
    free(*handle);
    *handle = NULL;

    return GateMutex_S_SUCCESS;
}

IArg GateMutex_enter (GateMutex_Handle gmHandle)
{
    GateMutex_Object * obj = (GateMutex_Object *)gmHandle;
    int ret;

    ret = pthread_mutex_lock(&(obj->mutex));
    assert(ret == 0);

    return (IArg)ret;
}

Void GateMutex_leave (GateMutex_Handle gmHandle, IArg key)
{
    GateMutex_Object * obj = (GateMutex_Object *)gmHandle;
#if defined(IPC_BUILD_DEBUG)
    int ret;

    ret = pthread_mutex_unlock(&(obj->mutex));
    assert(ret == 0);
#else
    pthread_mutex_unlock(&(obj->mutex));
#endif
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
