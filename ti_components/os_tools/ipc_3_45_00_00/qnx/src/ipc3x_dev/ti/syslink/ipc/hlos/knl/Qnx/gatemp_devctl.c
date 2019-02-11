/*
 * Copyright (c) 2013-2015 Texas Instruments Incorporated - http://www.ti.com
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== gatemp_devctl.c ========
 *
 */

/* Standard headers */
#include <ti/syslink/Std.h>

/* QNX specific header include */
#include <ti/syslink/build/Qnx/resmgr/proto.h>
#include <ti/syslink/build/Qnx/resmgr/dcmd_syslink.h>

/* Module specific header files */
#include <ti/ipc/GateMP.h>
#include <ti/syslink/inc/_GateMP_daemon.h>
#include <ti/syslink/inc/GateMPDrvDefs.h>

/* Function prototypes */
int ipc_gatemp_getFreeResource(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_gatemp_releaseResource(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_gatemp_getNumResources(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_gatemp_start(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_gatemp_stop(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);
int ipc_gatemp_isSetup(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb);

/**
 * Handler for devctl() messages for GateMP module.
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
int ipc_gatemp_devctl(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{

    switch (msg->i.dcmd)
    {
      case DCMD_GATEMP_GETFREERES:
      {
          return ipc_gatemp_getFreeResource(ctp, msg, ocb);
      }
      break;

      case DCMD_GATEMP_RELRES:
      {
          return ipc_gatemp_releaseResource(ctp, msg, ocb);
      }
      break;

      case DCMD_GATEMP_GETNUMRES:
      {
          return ipc_gatemp_getNumResources(ctp, msg, ocb);
      }
      break;

      case DCMD_GATEMP_START:
      {
          return ipc_gatemp_start(ctp, msg, ocb);
      }
      break;

      case DCMD_GATEMP_STOP:
      {
          return ipc_gatemp_stop(ctp, msg, ocb);
      }
      break;

      case DCMD_GATEMP_ISSETUP:
      {
          return ipc_gatemp_isSetup(ctp, msg, ocb);
      }
      break;

      default:
          fprintf(stderr, "Invalid DEVCTL for gatemp 0x%x\n", msg->i.dcmd);
          break;

    }

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(GateMPDrv_CmdArgs)));
}


/**
 * Handler for gatemp getFreeResource API.
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
int ipc_gatemp_getFreeResource(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    GateMPDrv_CmdArgs * cargs = (GateMPDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    GateMPDrv_CmdArgs * out  = (GateMPDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    out->apiStatus = GateMP_getFreeResource(cargs->args.getFreeResource.type);
    out->args.getFreeResource.id = out->apiStatus;

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(GateMPDrv_CmdArgs)));
}

/**
 * Handler for gatemp releaseResource API.
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
int ipc_gatemp_releaseResource(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    GateMPDrv_CmdArgs * cargs = (GateMPDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    GateMPDrv_CmdArgs * out  = (GateMPDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    out->apiStatus = GateMP_releaseResource(cargs->args.releaseResource.id,
        cargs->args.releaseResource.type);

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(GateMPDrv_CmdArgs)));
}

/**
 * Handler for gatemp getNumResources API.
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
int ipc_gatemp_getNumResources(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    GateMPDrv_CmdArgs * cargs = (GateMPDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    GateMPDrv_CmdArgs * out  = (GateMPDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    out->apiStatus = GateMP_getNumResources(cargs->args.getNumResources.type);
    cargs->args.getNumResources.value = out->apiStatus;

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(GateMPDrv_CmdArgs)));
}

/**
 * Handler for gatemp start API.
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
int ipc_gatemp_start(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    GateMPDrv_CmdArgs * cargs = (GateMPDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    GateMPDrv_CmdArgs * out  = (GateMPDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    cargs->args.start.nameServerHandle = GateMP_getNameServer();
    out->apiStatus = GateMP_start();

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(GateMPDrv_CmdArgs)));
}

/**
 * Handler for gatemp stop API.
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
int ipc_gatemp_stop(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    GateMPDrv_CmdArgs * out  = (GateMPDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    out->apiStatus = GateMP_stop();

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(GateMPDrv_CmdArgs)));
}

/**
 * Handler for gatemp isSetup API.
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
int ipc_gatemp_isSetup(resmgr_context_t *ctp, io_devctl_t *msg,
    ipc_ocb_t *ocb)
{
    GateMPDrv_CmdArgs * cargs = (GateMPDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->i));
    GateMPDrv_CmdArgs * out  = (GateMPDrv_CmdArgs *)
        (_DEVCTL_DATA (msg->o));

    cargs->args.isSetup.result = GateMP_isSetup();
    out->apiStatus = GateMP_S_SUCCESS;

    return (_RESMGR_PTR (ctp, &msg->o, sizeof(msg->o) +
        sizeof(GateMPDrv_CmdArgs)));
}
