/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
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
#ifndef VIDEOLOOPBACK_CONFIGURE_H_
#define VIDEOLOOPBACK_CONFIGURE_H_

#include <stdio.h>
#include <string.h>
#include <ti/drv/vps/include/common/bsp_types.h>

#include <ti/drv/vps/include/vip/vps_vipDrv.h>
#include <ti/drv/vps/include/dss/vps_dssDrv.h>
#include <ti/drv/vps/include/dss/vps_dctrlDrv.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/*VIP Capture functions*/
extern VpsCore_Frame *App_queBufs(void *drvData, UInt32 streamId, UInt32 chId);
extern Int32 App_deQueBufs(void *drvData, VpsCore_Frame *frmBufList);

VpsDrv_CaptInstObj *App_coreOpen(UInt32 vipInstId,
                                 UInt32 sliceId,
                                 UInt32 portId);

Int32 App_coreClose(VpsDrv_CaptInstObj *pObj);

Int32 App_coreStart(VpsDrv_CaptInstObj *pObj);

Int32 App_coreStop(VpsDrv_CaptInstObj *pObj);

Int32 App_configureVIP(VpsDrv_CaptInstObj *pObj,
                       UInt32              sliceId,
                       UInt32              portId);

Int32 App_portReset(VpsDrv_CaptInstObj *pObj);

/*DSS Display functions*/

extern VpsCore_Frame *App_DssqueBufs(void *drvData);
extern Int32 App_DssdeQueBufs(void *drvData, VpsCore_Frame *frmBufList);

VpsDrv_DispInstObj *App_dsscoreOpen(UInt32 dssInstId);

Int32 App_dsscoreClose(VpsDrv_DispInstObj *pObj);

Int32 App_dsscoreStart(VpsDrv_DispInstObj *pObj);

Int32 App_dsscoreStop(VpsDrv_DispInstObj *pObj);

Int32 App_dssconfigure(VpsDrv_DispInstObj *pObj);

/*Display Controller functions*/
VpsDrv_DctrlInstObj *App_dctrlcoreOpen(void);
Int32 App_dctrlcoreClose(VpsDrv_DctrlInstObj *pObj);
Int32 App_configureDctrl(VpsDrv_DctrlInstObj *pObj);
Int32 App_configureDctrlPipe(VpsDrv_DctrlInstObj *pObj);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /*VIDEOLOOPBACK_CONFIGURE_H_*/