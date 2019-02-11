/*
 *  Copyright (C) 2017 Texas Instruments Incorporated
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

#ifndef APP_FRAMEBUFMGNT_H_
#define APP_FRAMEBUFMGNT_H_

#include <stdio.h>
#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

#define CAL_APP_NUM_FRAMES      (0x40U)
/**< Number of frames to capture */
#define CAL_APP_NUM_SUB_FRAMES  (0x1U)
/**< Number of sub frames per frame, right now only 1 */
#define CAL_APP_TOTAL_NUM_SUB_FRAMES \
                                (CAL_APP_NUM_FRAMES * CAL_APP_NUM_SUB_FRAMES)

/**< Designator for Sub Frame callback, used in sequence checks */
#define CAL_APP_SUB_F_CB        (const VpsCore_Frame *) (0xFFFF)
/**< Designator for EOF callback, used in sequence checks */
#define CAL_APP_EOF_CB          (const VpsCore_Frame *) (0xAAAA)
/**< Designator for callback which returns frame, used in sequence checks */
#define CAL_APP_CAPT_F_CB       (const VpsCore_Frame *) (0x5555)
/**< Number of callback expected (Eof, Sof & X line) */
#define CAL_APP_NUM_CB          (CAL_APP_NUM_FRAMES * 3U)
void CalAppUtils_BoardInit(void);
void CalAppUtils_FrameBufInit(void);
void CalAppUtils_FrameBufDeInit(void);
VpsCore_Frame *CalAppUtils_GetFrameBuf(void);
void CalAppUtils_ReleaseFrameBuf(VpsCore_Frame *frm);
void CalAppUtils_appInitUb954_Ub953(void);
void CalAppUtils_appDeInitUb954_Ub953(void);
void CalAppUtils_IntrInit(void);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* APP_FRAMEBUFMGNT_H_ */

