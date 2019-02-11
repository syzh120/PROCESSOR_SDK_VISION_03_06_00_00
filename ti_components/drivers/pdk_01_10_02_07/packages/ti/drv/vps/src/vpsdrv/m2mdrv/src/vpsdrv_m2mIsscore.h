/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014-2015
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
 */

/**
 *  \file vpsdrv_m2mIntfCore.h
 *
 *  \brief VPS M2M driver internal header file.
 */

#ifndef VPSDRV_M2MISSCORE_H_
#define VPSDRV_M2MISSCORE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef VPS_ISS_BUILD
Int32 vpsMdrvIssSubmitReq(
    VpsMDrv_IntfHandleObj *hObj,
    VpsMDrv_IntfQueueObj  *qObj);

Int32 vpsMdrvIssControl(
    VpsMDrv_IntfHandleObj *hObj,
    UInt32                 cmd,
    Ptr                    cmdArgs,
    Ptr                    cmdStatArgs);
#endif /* VPS_ISS_BUILD */

#ifdef VPS_SIMCOP_BUILD
Int32 vpsMdrvSimcopSubmitReq(
    VpsMDrv_IntfHandleObj *hObj,
    VpsMDrv_IntfQueueObj  *qObj);

Int32 vpsMdrvSimcopControl(
    VpsMDrv_IntfHandleObj *hObj,
    UInt32                 cmd,
    Ptr                    cmdArgs,
    Ptr                    cmdStatArgs);
#endif

#ifdef VPS_ISS_BUILD
Int32 vpsMdrvCalm2mSubmitReq(
    VpsMDrv_IntfHandleObj *hObj,
    VpsMDrv_IntfQueueObj  *qObj);

Int32 vpsMdrvCalm2mControl(
    VpsMDrv_IntfHandleObj *hObj,
    UInt32                 cmd,
    Ptr                    cmdArgs,
    Ptr                    cmdStatArgs);
#endif

#ifdef __cplusplus
}
#endif

#endif /*  VPSDRV_M2MISSCORE_H_ */

