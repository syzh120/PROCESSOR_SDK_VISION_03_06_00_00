/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file m2mIssCal_main.h
 *
 *  \brief ISS CAL M2M driver sample application private header file.
 *
 */

#ifndef M2M_ISSCAL_MAIN_H_
#define M2M_ISSCAL_MAIN_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/utils/Load.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/vps.h>

#if defined (VPS_ISS_CALM2M_BUILD)
#include <ti/drv/vps/include/vps_m2mIntf.h>
#include <ti/drv/vps/include/iss/vps_m2mIss.h>
#endif

#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_NAME                 "M2MISSCAL_APP"

/* Test application stack size. */
#define APP_TSK_STACK_SIZE       (10U * 1024U)

/* Input Frame Format, SIMCOP LDC flow uses 1920x1080 input image with 8bit
 * FVID2_DF_YUV422I_YUYV input data*/
#define IN_WIDTH                 (1280U)
#define IN_HEIGHT                (720U)
#define IN_PITCH                 ((IN_WIDTH * 3) / 2)
#define IN_FORMAT                (FVID2_DF_BAYER_RAW)
#define IN_BPP                   (FVID2_BPP_BITS12_PACKED_MIPI)
#define IN_PIX_EXTRACT           (VPS_ISS_CAL_PIX_EXRCT_B12_MIPI)


#define OUT_WIDTH                (IN_WIDTH)
#define OUT_HEIGHT               (IN_HEIGHT)
#define OUT_PITCH                (IN_WIDTH * 2)
#define OUT_FORMAT               (FVID2_DF_BAYER_RAW)
#define OUT_BPP                  (FVID2_BPP_BITS16)
#define OUT_PIX_PACK             (VPS_ISS_CAL_PIX_PACK_B16)

/* VPS_ISS_LDC_LUMA_INTRP_BILINEAR */

#define APP_NUM_FRAMES           (4U)
#define APP_INP_FRM_IDX          (0U)
#define APP_OUT_FRM_IDX          (APP_INP_FRM_IDX + APP_NUM_FRAMES)
#define APP_MAX_FRAMES_ALLOCATED (APP_OUT_FRM_IDX + APP_NUM_FRAMES)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef M2M_ISSCAL_MAIN_H_ */
