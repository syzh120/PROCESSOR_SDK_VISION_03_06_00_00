/*
 *  @file   Nameserver_devctl.c
 *
 *  @brief      OS-specific implementation of NameServer driver for Qnx
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2015, Texas Instruments Incorporated
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
#include <ti/ipc/NameServer.h>
#include <ti/syslink/inc/NameServerDrvDefs.h>

/* Function prototypes */
int ipc_nameserver_add(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_nameserver_get(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_nameserver_adduint32(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_nameserver_getuint32(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_nameserver_remove(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_nameserver_removeentry(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_nameserver_params_init(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_nameserver_create(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_nameserver_delete(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_nameserver_setup(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_nameserver_destroy(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);

/**
 * Handler for devctl() messages for MultiProc module.
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
int ipc_nameserver_devctl(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{

    switch (msg->i.dcmd)
    {
      case DCMD_NAMESERVER_ADD:
      {
          return ipc_nameserver_add( ctp, msg, ocb);
      }
      break;

      case DCMD_NAMESERVER_GET:
      {
          return ipc_nameserver_get( ctp, msg, ocb);
      }
      break;
      case DCMD_NAMESERVER_ADDUINT32:
      {
          return ipc_nameserver_adduint32( ctp, msg, ocb);
      }
      break;

      case DCMD_NAMESERVER_GETUINT32:
      {
          return ipc_nameserver_getuint32( ctp, msg, ocb);
      }
      break;

      case DCMD_NAMESERVER_REMOVE:
      {
          return ipc_nameserver_remove( ctp, msg, ocb);
      }
      break;

      case DCMD_NAMESERVER_REMOVEENTRY:
      {
          return ipc_nameserver_removeentry( ctp, msg, ocb);
      }
      break;

      case DCMD_NAMESERVER_PARAMS_INIT:
      {
          return ipc_nameserver_params_init( ctp, msg, ocb);
      }
      break;

      case DCMD_NAMESERVER_CREATE:
      {
          return ipc_nameserver_create( ctp, msg, ocb);
      }
      break;

      case DCMD_NAMESERVER_DELETE:
      {
          return ipc_nameserver_delete( ctp, msg, ocb);
      }
      break;

      case DCMD_NAMESERVER_SETUP:
      {
          return ipc_nameserver_setup( ctp, msg, ocb);
      }
      break;

      case DCMD_NAMESERVER_DESTROY:
      {
          return ipc_nameserver_destroy( ctp, msg, ocb);
      }
      break;

      default:
          fprintf( stderr, "Invalid DEVCTL for nameserver 0x%x\n", msg->i.dcmd);
          break;

    }

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs)));
}

/**
 * Handler for nameserver add API.
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
int ipc_nameserver_add(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    NameServerDrv_CmdArgs *     cargs = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    NameServerDrv_CmdArgs *     out  = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));
    String name = (String)(cargs+1);
    Ptr buf = (Ptr)((sizeof(char) * cargs->args.add.nameLen) + (char *)(name));
    Ptr entry;

    GT_assert (curTrace, (name != NULL));

    entry = NameServer_add(cargs->args.add.handle,
                           name,
                           buf,
                           cargs->args.add.len);
    GT_assert (curTrace, (entry != NULL));

    out->args.add.entry = entry;
    if (entry) {
        out->apiStatus = NameServer_S_SUCCESS;
    }
    else {
        out->apiStatus = NameServer_E_FAIL;
    }

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs)));
}

/**
 * Handler for nameserver get  API.
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
int ipc_nameserver_get(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    NameServerDrv_CmdArgs *     cargs = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    NameServerDrv_CmdArgs *     out  = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    char * buf = (char *)(cargs + 1);
    char * name  = (char *)(buf + (sizeof(char) * cargs->args.get.len));
    UInt16 * procId = NULL;

    if (cargs->args.get.procLen > 0) {
        procId = (UInt16 *)(name + (sizeof(char) * cargs->args.get.nameLen));
    }

    out->apiStatus = NameServer_get(cargs->args.get.handle,
                             (String)name,
                             (Ptr)buf,
                             &cargs->args.get.len,
                             procId);

    SETIOV(&ctp->iov[0], &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs));
    SETIOV(&ctp->iov[1], (Ptr)buf, cargs->args.get.len);

    return _RESMGR_NPARTS(2);
}

/**
 * Handler for nameserver addunit32 API.
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
int ipc_nameserver_adduint32(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    NameServerDrv_CmdArgs *     cargs = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    NameServerDrv_CmdArgs *     out  = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));
    String name = (String)(cargs+1);

    Ptr    entry;

    GT_assert (curTrace, (name != NULL));

    entry = NameServer_addUInt32 (cargs->args.addUInt32.handle,
                                  name,
                                  cargs->args.addUInt32.value);
    GT_assert (curTrace, (entry != NULL));

    out->args.addUInt32.entry = entry;
    if (entry) {
        out->apiStatus = NameServer_S_SUCCESS;
    }
    else {
        out->apiStatus = NameServer_E_FAIL;
    }

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs)));
}

/**
 * Handler for nameserver get  API.
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
int ipc_nameserver_getuint32(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    UInt32                      value;
    NameServerDrv_CmdArgs *     cargs = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    NameServerDrv_CmdArgs *     out  = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    char * name  = (char *)(cargs + 1);
    UInt16 * procId = NULL;


    if (cargs->args.getUInt32.procId[0] != (UInt16)-1) {
        procId = (UInt16 *)(name + (sizeof(char) * strlen(name)));
    }

    out->apiStatus = NameServer_getUInt32 (cargs->args.getUInt32.handle,
                             (String)name,
                             (Ptr)&value,
                             procId);

    out->args.getUInt32.value = value;

    /* Do not assert. This can return NameServer_E_NOTFOUND
     * as a valid runtime failure.
     */

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs)));
}

/**
 * Handler for nameserver remove API.
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
int ipc_nameserver_remove(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    NameServerDrv_CmdArgs * cargs = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    NameServerDrv_CmdArgs *     out  = (NameServerDrv_CmdArgs *) (_DEVCTL_DATA (msg->o));
    String name = (String)(cargs+1);

    out->apiStatus = NameServer_remove (cargs->args.remove.handle, name);

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs)));
}

/**
 * Handler for nameserver remove entry API.
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
int ipc_nameserver_removeentry(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    NameServerDrv_CmdArgs *     cargs = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    NameServerDrv_CmdArgs *     out  = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    out->apiStatus = NameServer_removeEntry (cargs->args.removeEntry.handle,
                                    cargs->args.removeEntry.entry);

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs)));
}

/**
 * Handler for nameserver params init API.
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
int ipc_nameserver_params_init(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    NameServerDrv_CmdArgs *     cargs = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    NameServerDrv_CmdArgs *     out  = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    NameServer_Params *params = (NameServer_Params *)(cargs+1);

    NameServer_Params_init (params);

    SETIOV(&ctp->iov[0], &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs));
    SETIOV(&ctp->iov[1], params, sizeof(NameServer_Params));

    out->apiStatus = NameServer_S_SUCCESS;

    return _RESMGR_NPARTS(2);
}

/**
 * Handler for nameserver create API.
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
int ipc_nameserver_create(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    NameServerDrv_CmdArgs *     cargs = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    NameServerDrv_CmdArgs *     out  = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));
    NameServer_Params *         params = (NameServer_Params *)(cargs+1);
    String name = (String)(params+1);

    out->args.create.handle = NameServer_create (name, params);
    if (out->args.create.handle) {
        out->apiStatus = NameServer_S_SUCCESS;
    }
    else {
        out->apiStatus = NameServer_E_FAIL;
    }

    GT_assert (curTrace, (out->args.create.handle != NULL));

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs)));
}

/**
 * Handler for nameserver delete API.
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
int ipc_nameserver_delete(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    NameServerDrv_CmdArgs * cargs = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    NameServerDrv_CmdArgs * out  = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    out->apiStatus = NameServer_delete (&(cargs->args.delete.handle));
    GT_assert (curTrace, (out->apiStatus >= 0));

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs)));
}

/**
 * Handler for nameserver setup  API.
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
int ipc_nameserver_setup(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    NameServerDrv_CmdArgs * out  = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    out->apiStatus = NameServer_setup ();
    GT_assert (curTrace, (out->apiStatus >= 0));

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs)));
}

/**
 * Handler for nameserver destroy API.
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
int ipc_nameserver_destroy(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    NameServerDrv_CmdArgs * out  = (NameServerDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    out->apiStatus = NameServer_destroy ();
    GT_assert (curTrace, (out->apiStatus >= 0));

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(NameServerDrv_CmdArgs)));

}
