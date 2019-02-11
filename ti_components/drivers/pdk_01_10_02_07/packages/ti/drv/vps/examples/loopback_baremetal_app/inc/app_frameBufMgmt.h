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
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/trace.h>

#include <ti/drv/vps/src/vpslib/common/vpscore.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/*
 * Setting as per closest VPDMA max-width/max-height setting.
 * VPDMA supports max-width/max-height setting based on pixels.
 * In raw mode, pixel size is assumed to be two bytes.
 * Therefore, buffer size must be twice the setting.
 * This should be in sync with maxOutWidth/maxOutHeight setting done in
 * App_configureVIP()
 */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2EX)
#define BUF_STRIDE   (720 * 2)                               /* Should be
                                                              *multiple of 16 */
#define BUF_HEIGHT    (480)
#elif defined (SOC_TDA3XX) || defined (SOC_TDA2PX)
#define BUF_STRIDE   (1280 * 2)                               /* Should be
                                                              ** multiple of 16
                                                              **/
#define BUF_HEIGHT    (720)

#endif
#define MAX_NUM_PORTS           2                         /* Example: PORTA and
                                                           *PORTB capture*/
#define MAX_NUM_BUFS_PER_PORT   1

#define MAX_BUF_SIZE            (BUF_STRIDE * BUF_HEIGHT) /* Size of one buffer
                                                          **/

/* These are used in callback function to identify which port has called the
 * callback function.
 * These are given as input to VPSLIB in VpsDrv_captOpen() as
 * #VpsCore_OpenPrms.drvData
 */
#define BUF_ARRAY_IDX_PORTA     0
#define BUF_ARRAY_IDX_PORTB     1

void App_FrameBufInit();

void App_FrameBufDeInit();

VpsCore_Frame *App_GetFrameBuf(UInt32 streamId);

void App_ReleaseFrameBuf(VpsCore_Frame *frm, UInt32 streamId);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

