/*
 *  Copyright (c) Texas Instruments Incorporated 2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 *  \file CascadeFlashFpga_main.h
 *
 *  \brief Cascade Radar sample application private header file.
 *
 */

#ifndef CASCADE_RADAR_MAIN_H_
#define CASCADE_RADAR_MAIN_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/utils/Load.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/csl/soc.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <ti/csl/csl_gpio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Size of the Cascade Task stack */
#define CASCADE_APP_TSK_STACK_MAIN   (10U * 1024U)

/* Test application task priority */
#define RADAR_APP_TSK_PRI_MAIN           (10U)

#define APP_NAME                        "CASCADE_RADAR_APP"

#undef PULLUDENABLE_ENABLE
#undef PULLUDENABLE_DISABLE
#undef PULLTYPESELECT_PULL_UP
#undef PULLTYPESELECT_PULL_DOWN
#undef INPUTENABLE_ENABLE
#undef INPUTENABLE_DISABLE
#undef SLEWCONTROL_FAST_SLEW
#undef SLEWCONTROL_SLOW_SLEW
#undef WAKEUPENABLE_ENABLE
#undef WAKEUPENABLE_DISABLE

#define PULLUDENABLE_ENABLE         (1U)
#define PULLUDENABLE_DISABLE        (0U)
#define PULLTYPESELECT_PULL_UP      (1U)
#define PULLTYPESELECT_PULL_DOWN    (0U)
#define INPUTENABLE_ENABLE          (1U)
#define INPUTENABLE_DISABLE         (0U)
#define SLEWCONTROL_FAST_SLEW       (1U)
#define SLEWCONTROL_SLOW_SLEW       (0U)
#define WAKEUPENABLE_ENABLE         (1U)
#define WAKEUPENABLE_DISABLE        (0U)

extern EDMA3_DRV_Handle gEdmaHandle;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void configure_pad(const pad_config_t *pad_array, uint32_t elements);
void Utils_fgpaPowerUp(void);
Int32 Utils_fpgaStart(UInt32 fpgaNum);
Void Utils_mcspiInit(UInt32 mcSpiInstNum);
Void Utils_mcspiDeinit(UInt32 mcSpiInstNum);
void CascadeFlashFpga_InitPadMuxSPIFlash (void);

void * Bsp_FPGASpiOpenCb(UInt32 mcSpiIdx);
Int32 Bsp_FPGASpiCloseCb(void* fd);
Int32 Bsp_FPGASpiReadCb(void * fd, UInt8 *pBuff, UInt16 len);
Int32 Bsp_FPGASpiWriteCb(void * fd, UInt8 *pBuff, UInt16 len);


#ifdef __cplusplus
}
#endif

#endif  /* #ifndef CASCADE_RADAR_MAIN_H_ */
