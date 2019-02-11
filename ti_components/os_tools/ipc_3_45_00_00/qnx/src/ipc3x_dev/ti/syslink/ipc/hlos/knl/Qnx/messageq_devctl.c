/*
 *  @file   messageq_devctl.c
 *
 *  @brief      OS-specific implementation of Messageq driver for Qnx
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2013-2015, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */


/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/List.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/Memory.h>

/* QNX specific header include */
#include <ti/syslink/build/Qnx/resmgr/proto.h>
#include <ti/syslink/build/Qnx/resmgr/dcmd_syslink.h>

/* Module specific header files */
#include <ti/ipc/MessageQ.h>
#include <ti/syslink/inc/MessageQDrvDefs.h>

/* Function prototypes */
int ipc_messageq_getconfig(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_messageq_setup(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_messageq_destroy(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_messageq_create(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_messageq_delete(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);

/**
 * Handler for devctl() messages for messageQ module.
 *
 * Handles special devctl() messages that we export for control.
 *
 * \param ctp   Thread's associated context information.
 * \param msg   The actual devctl() message.
 * \param ocb   OCB associated with client's session.
 *
 * \return POSIX errno value.
 *
 * \retval EOK      Success.
 * \retval ENOTSUP  Unsupported devctl().
 */
int ipc_messageq_devctl(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    switch (msg->i.dcmd)
    {
          case DCMD_MESSAGEQ_CREATE:
          {
                return ipc_messageq_create( ctp, msg, ocb);
          }
          break;

          case DCMD_MESSAGEQ_DELETE:
          {
                return ipc_messageq_delete( ctp, msg, ocb);
          }
          break;

          case DCMD_MESSAGEQ_GETCONFIG:
          {
                return ipc_messageq_getconfig( ctp, msg, ocb);
          }
          break;

          case DCMD_MESSAGEQ_SETUP:
          {
                return ipc_messageq_setup( ctp, msg, ocb);
          }
          break;

          case DCMD_MESSAGEQ_DESTROY:
          {
                return ipc_messageq_destroy( ctp, msg, ocb);
          }
          break;

     default:
        fprintf( stderr, "Invalid DEVCTL for messageQ 0x%x \n", msg->i.dcmd);
        break;

    }

    return (_RESMGR_PTR(ctp, &msg->o, sizeof(msg->o) +
        sizeof(MessageQDrv_CmdArgs)));
}

/**
 * Handler for messageq create API.
 *
 * \param ctp   Thread's associated context information.
 * \param msg   The actual devctl() message.
 * \param ocb   OCB associated with client's session.
 *
 * \return POSIX errno value.
 *
 * \retval EOK      Success.
 * \retval ENOTSUP  Unsupported devctl().
 */
int ipc_messageq_create(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    MessageQDrv_CmdArgs *       cargs = (MessageQDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    MessageQDrv_CmdArgs *       out   = (MessageQDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));
    MessageQ_Params *local_createparams = NULL;
    String local_createname = NULL;

    out->apiStatus = MessageQ_S_SUCCESS;

    if (cargs->args.create.params) {
        local_createparams = (MessageQ_Params *)(cargs+1);
        if (cargs->args.create.name)
            local_createname = (String)(local_createparams+1);
    }
    else {
        if (cargs->args.create.name)
            local_createname = (String)(cargs+1);
    }

    out->args.create.handle = MessageQ_create(local_createname,
        local_createparams);
    GT_assert (curTrace, (out->args.create.handle != NULL));

    /* Set failure status if create has failed. */
    if (out->args.create.handle == NULL) {
        out->apiStatus = MessageQ_E_FAIL;
    }
    else {
        out->apiStatus = MessageQ_S_SUCCESS;
    }

    if (out->args.create.handle != NULL) {
        out->args.create.queueId = MessageQ_getQueueId(out->args.create.handle);
        /*
         * TODO: Need to implement cleanup of queues for processes that departed
         */
        /* MessageQ_setQueueOwner(out->args.create.handle,clientPID[clientId])*/
    }

    SETIOV(&ctp->iov[0], &msg->o, sizeof(msg->o) +
        sizeof(MessageQDrv_CmdArgs));
    return _RESMGR_NPARTS(1);
}

/**
 * Handler for messageq delete API.
 *
 * \param ctp   Thread's associated context information.
 * \param msg   The actual devctl() message.
 * \param ocb   OCB associated with client's session.
 *
 * \return POSIX errno value.
 *
 * \retval EOK      Success.
 * \retval ENOTSUP  Unsupported devctl().
 */
int ipc_messageq_delete(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    MessageQDrv_CmdArgs * cargs = (MessageQDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    MessageQDrv_CmdArgs * out  = (MessageQDrv_CmdArgs *)(_DEVCTL_DATA (msg->o));

    out->apiStatus = MessageQ_delete ((MessageQ_Handle *)
        &(cargs->args.deleteMessageQ.handle));
    GT_assert (curTrace, (out->apiStatus >= 0));

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(MessageQDrv_CmdArgs)));
}

/**
 * Handler for messageq getconfig API.
 *
 * \param ctp   Thread's associated context information.
 * \param msg   The actual devctl() message.
 * \param ocb   OCB associated with client's session.
 *
 * \return POSIX errno value.
 *
 * \retval EOK      Success.
 * \retval ENOTSUP  Unsupported devctl().
 */
int ipc_messageq_getconfig(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    MessageQDrv_CmdArgs * cargs = (MessageQDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    MessageQ_Config local_config;
    MessageQ_getConfig (&local_config);

    cargs->apiStatus = MessageQ_S_SUCCESS;
    SETIOV(&ctp->iov[0], &msg->o, sizeof(msg->o) +
        sizeof(MessageQDrv_CmdArgs));
    SETIOV(&ctp->iov[1], &local_config, sizeof(MessageQ_Config));

    return _RESMGR_NPARTS(2);

}

/**
 * Handler for messageq setup API.
 *
 * \param ctp   Thread's associated context information.
 * \param msg   The actual devctl() message.
 * \param ocb   OCB associated with client's session.
 *
 * \return POSIX errno value.
 *
 * \retval EOK      Success.
 * \retval ENOTSUP  Unsupported devctl().
 */
int ipc_messageq_setup(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    MessageQDrv_CmdArgs * cargs = (MessageQDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    MessageQDrv_CmdArgs * out  = (MessageQDrv_CmdArgs *)(_DEVCTL_DATA (msg->o));

    MessageQ_Config *     local_setupconfig;
    local_setupconfig = (MessageQ_Config *)(cargs+1);

    out->apiStatus = MessageQ_setup (local_setupconfig);
    out->args.setup.nameServerHandle  = MessageQ_getNameServerHandle();

    GT_assert (curTrace, (out->apiStatus  >= 0));
    GT_assert (curTrace, (out->args.setup.nameServerHandle  != NULL));

    SETIOV(&ctp->iov[0], &msg->o, sizeof(msg->o) +
        sizeof(MessageQDrv_CmdArgs));

    return _RESMGR_NPARTS(1);
}


/**
 * Handler for messageq destroy API.
 *
 * \param ctp   Thread's associated context information.
 * \param msg   The actual devctl() message.
 * \param ocb   OCB associated with client's session.
 *
 * \return POSIX errno value.
 *
 * \retval EOK      Success.
 * \retval ENOTSUP  Unsupported devctl().
 */
int ipc_messageq_destroy(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    MessageQDrv_CmdArgs * out = (MessageQDrv_CmdArgs *)(_DEVCTL_DATA (msg->o));

    out->apiStatus = MessageQ_destroy();
    GT_assert(curTrace, (out->apiStatus  >= 0));

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(MessageQDrv_CmdArgs)));
}
