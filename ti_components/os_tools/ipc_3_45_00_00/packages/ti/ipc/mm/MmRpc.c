/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 *  ======== MmRpc.c ========
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <stdint.h> /* should be in linux/rpmsg_rpc.h */
#include <stddef.h> /* should be in linux/rpmsg_rpc.h */



#if defined(KERNEL_INSTALL_DIR)

#ifdef linux
#define _linux_ linux
#undef linux
#endif

#define linux_version_include(kd) <kd/include/generated/uapi/linux/version.h>
#include linux_version_include(KERNEL_INSTALL_DIR)

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,14,0)
#define linux_include(kd,m) <kd/include/linux/m.h>
#else
#define linux_include(kd,m) <kd/include/uapi/linux/m.h>
#endif

#include linux_include(KERNEL_INSTALL_DIR,rpmsg_rpc)

#ifdef _linux_
#define linux _linux
#undef _linux_
#endif

#elif defined(IPC_BUILDOS_QNX)

#include <ti/ipc/rpmsg_rpc.h>

#elif defined(IPC_BUILDOS_ANDROID)
#include <uapi/linux/rpmsg_rpc.h>

#else
#error Unsupported Operating System
#endif

#include "MmRpc.h"

#if defined(KERNEL_INSTALL_DIR) || defined(IPC_BUILDOS_ANDROID)
static int MmRpc_bufHandle(MmRpc_Handle handle, int cmd, int num,
        MmRpc_BufDesc *desc);
#endif


/*
 *  ======== MmRpc_Object ========
 */
typedef struct {
    int                         fd;         /* device file descriptor */
    struct rppc_create_instance connect;    /* connection object */
} MmRpc_Object;

/*
 *  ======== MmRpc_Params_init ========
 */
void MmRpc_Params_init(MmRpc_Params *params)
{
    params->reserved = 0;
}

/*
 *  ======== MmRpc_create ========
 */
int MmRpc_create(const char *service, const MmRpc_Params *params,
        MmRpc_Handle *handlePtr)
{
    int             status = MmRpc_S_SUCCESS;
    MmRpc_Object *  obj;
    char            cbuf[RPPC_MAX_INST_NAMELEN+16];

    /* allocate the instance object */
    obj = (MmRpc_Object *)calloc(1, sizeof(MmRpc_Object));

    if (obj == NULL) {
        status = MmRpc_E_FAIL;
        goto leave;
    }

    /* open the driver */
    sprintf(cbuf, "/dev/%s", service);
    obj->fd = open(cbuf, O_RDWR);

    if (obj->fd < 0) {
        printf("MmRpc_create: Error: open failed, name=%s\n", cbuf);
        status = MmRpc_E_FAIL;
        goto leave;
    }

    strncpy(obj->connect.name, service, (RPPC_MAX_INST_NAMELEN - 1));
    obj->connect.name[RPPC_MAX_INST_NAMELEN - 1] = '\0';

    /* create a server instance, rebind its address to this file descriptor */
    status = ioctl(obj->fd, RPPC_IOC_CREATE, &obj->connect);

    if (status < 0) {
        printf("MmRpc_create: Error: connect failed\n");
        status = MmRpc_E_FAIL;
        goto leave;
    }

leave:
    if (status < 0) {
        if ((obj != NULL) && (obj->fd >= 0)) {
            close(obj->fd);
        }
        if (obj != NULL) {
            free(obj);
        }
        *handlePtr = NULL;
    }
    else {
        *handlePtr = (MmRpc_Handle)obj;
    }

    return(status);
}

/*
 *  ======== MmRpc_delete ========
 */
int MmRpc_delete(MmRpc_Handle *handlePtr)
{
    int status = MmRpc_S_SUCCESS;
    MmRpc_Object *obj;

    obj = (MmRpc_Object *)(*handlePtr);

    /* close the device */
    if ((obj != NULL) && (obj->fd >= 0)) {
        close(obj->fd);
    }

    /* free the instance object */
    free((void *)(*handlePtr));
    *handlePtr = NULL;

    return(status);
}

/*
 *  ======== MmRpc_call ========
 */
int MmRpc_call(MmRpc_Handle handle, MmRpc_FxnCtx *ctx, int32_t *ret)
{
    int status = MmRpc_S_SUCCESS;
    MmRpc_Object *obj = (MmRpc_Object *)handle;
    struct rppc_function *rpfxn;
    struct rppc_function_return reply_msg;
    MmRpc_Param *param;
    void *msg;
    int len;
    int i;

    /* combine params and translation array into one contiguous message */
    len = sizeof(struct rppc_function) +
                (ctx->num_xlts * sizeof(struct rppc_param_translation));
    msg = (void *)calloc(len, sizeof(char));

    if (msg == NULL) {
        printf("MmRpc_call: Error: msg alloc failed\n");
        status = MmRpc_E_FAIL;
        goto leave;
    }

    /* copy function parameters into message */
    rpfxn = (struct rppc_function *)msg;
    rpfxn->fxn_id = ctx->fxn_id;
    rpfxn->num_params = ctx->num_params;

    for (i = 0; i < ctx->num_params; i++) {
        param = &ctx->params[i];

        switch (param->type) {
            case MmRpc_ParamType_Scalar:
                rpfxn->params[i].type = RPPC_PARAM_TYPE_ATOMIC;
                rpfxn->params[i].size = param->param.scalar.size;
                rpfxn->params[i].data = param->param.scalar.data;
                rpfxn->params[i].base = 0;
                rpfxn->params[i].fd = 0;
                break;

            case MmRpc_ParamType_Ptr:
                rpfxn->params[i].type = RPPC_PARAM_TYPE_PTR;
                rpfxn->params[i].size = param->param.ptr.size;
                rpfxn->params[i].data = param->param.ptr.addr;
                rpfxn->params[i].base = param->param.ptr.addr;
                rpfxn->params[i].fd = param->param.ptr.handle;
                break;

            case MmRpc_ParamType_OffPtr:
                rpfxn->params[i].type = RPPC_PARAM_TYPE_PTR;
                rpfxn->params[i].size = param->param.offPtr.size;
                rpfxn->params[i].data = param->param.offPtr.base +
                        param->param.offPtr.offset;
                rpfxn->params[i].base = param->param.offPtr.base;
                rpfxn->params[i].fd = param->param.offPtr.handle;
                break;

            default:
                printf("MmRpc_call: Error: invalid parameter type\n");
                status = MmRpc_E_INVALIDPARAM;
                goto leave;
                break;
        }
    }

    /* copy offset array into message */
    rpfxn->num_translations = ctx->num_xlts;

    for (i = 0; i < ctx->num_xlts; i++) {
        /* pack the pointer translation entry */
        rpfxn->translations[i].index = ctx->xltAry[i].index;
        rpfxn->translations[i].offset = ctx->xltAry[i].offset;
        rpfxn->translations[i].base = ctx->xltAry[i].base;
        rpfxn->translations[i].fd = (int32_t)ctx->xltAry[i].handle;
    }

    /* send message for remote execution */
    status = write(obj->fd, msg, len);

    if (status < 0) {
        printf("MmRpc_call: Error: write failed\n");
        status = MmRpc_E_FAIL;
        goto leave;
    }

    /* wait for return status from remote service */
    status = read(obj->fd, &reply_msg, sizeof(struct rppc_function_return));

    if (status < 0) {
        printf("MmRpc_call: Error: read failed\n");
        status = MmRpc_E_FAIL;
        goto leave;
    }
    else if (status != sizeof(struct rppc_function_return)) {
        printf("MmRpc_call: Error: reply bytes=%d, expected %d\n",
                status, sizeof(struct rppc_function_return));
        status = MmRpc_E_FAIL;
        goto leave;
    }
    else {
        status = MmRpc_S_SUCCESS;
    }

    *ret = (int32_t)reply_msg.status;

leave:
    if (msg != NULL) {
        free(msg);
    }

    return(status);
}

/*
 *  ======== MmRcp_release ========
 */
int MmRpc_release(MmRpc_Handle handle, MmRpc_BufType type, int num,
        MmRpc_BufDesc *desc)
{
    int stat = MmRpc_S_SUCCESS;

    switch (type) {

#if defined(KERNEL_INSTALL_DIR) || defined(IPC_BUILDOS_ANDROID)
        case MmRpc_BufType_Handle:
            stat = MmRpc_bufHandle(handle, RPPC_IOC_BUFUNREGISTER, num, desc);
            break;

#elif defined(IPC_BUILDOS_QNX)
        case MmRpc_BufType_Ptr:
            break;
#endif
        default:
            printf("MmRpc_release: Error: unsupported type value: %d\n", type);
            stat = MmRpc_E_INVALIDPARAM;
            break;
    }

    if (stat < 0) {
        printf("MmRpc_release: Error: unable to release buffer\n");
    }

    return(stat);
}

/*
 *  ======== MmRcp_use ========
 */
int MmRpc_use(MmRpc_Handle handle, MmRpc_BufType type, int num,
        MmRpc_BufDesc *desc)
{
    int stat = MmRpc_S_SUCCESS;

    switch (type) {

#if defined(KERNEL_INSTALL_DIR) || defined(IPC_BUILDOS_ANDROID)
        case MmRpc_BufType_Handle:
            stat = MmRpc_bufHandle(handle, RPPC_IOC_BUFREGISTER, num, desc);
            break;

#elif defined(IPC_BUILDOS_QNX)
        case MmRpc_BufType_Ptr:
            break;
#endif
        default:
            printf("MmRpc_use: Error: unsupported type value: %d\n", type);
            stat = MmRpc_E_INVALIDPARAM;
            break;
    }

    if (stat < 0) {
        printf("MmRpc_use: Error: unable to declare buffer use\n");
    }

    return(stat);
}

#if defined(KERNEL_INSTALL_DIR) || defined(IPC_BUILDOS_ANDROID)
/*
 *  ======== MmRpc_bufHandle ========
 */
int MmRpc_bufHandle(MmRpc_Handle handle, int cmd, int num, MmRpc_BufDesc *desc)
{
    int stat = MmRpc_S_SUCCESS;
    MmRpc_Object *obj = (MmRpc_Object *)handle;
    int i;
    struct rppc_buf_fds reg = { num, NULL };

    reg.fds = (int32_t *)malloc(num * sizeof(int32_t));

    if (reg.fds == NULL) {
        stat = MmRpc_E_NOMEM;
        goto leave;
    }

    for (i = 0; i < num; i++) {
        reg.fds[i] = desc[i].handle;
    }

    stat = ioctl(obj->fd, cmd, &reg);

    if (stat < 0) {
        stat = MmRpc_E_SYS;
    }

leave:
    if (reg.fds != NULL) {
        free(reg.fds);
    }

    return(stat);
}
#endif
