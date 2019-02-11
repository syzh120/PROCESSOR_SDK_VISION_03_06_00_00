/********************************************************************
 * Copyright (C) 2013-2014 Texas Instruments Incorporated.
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
#ifndef CSLR_SYNCTIMER_H
#define CSLR_SYNCTIMER_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for __ALL__
**************************************************************************/
typedef struct {
    volatile Uint32 REVISION;
    volatile Uint8  RSVD0[12];
    volatile Uint32 SYSCONFIG;
    volatile Uint8  RSVD1[28];
    volatile Uint32 CR;
} CSL_SynctimerRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

/* IP Revision Identifier (X.Y.R) Used by software to track features, bugs,
 * and compatibility */
#define CSL_SYNCTIMER_REVISION                                  (0x0U)

/* This register contains the System Configuration settings */
#define CSL_SYNCTIMER_SYSCONFIG                                 (0x10U)

/* This register holds the counter value */
#define CSL_SYNCTIMER_CR                                        (0x30U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* REVISION */

#define CSL_SYNCTIMER_REVISION_Y_MINOR_MASK                     (0x0000003FU)
#define CSL_SYNCTIMER_REVISION_Y_MINOR_SHIFT                    (0U)
#define CSL_SYNCTIMER_REVISION_Y_MINOR_RESETVAL                 (0x00000000U)
#define CSL_SYNCTIMER_REVISION_Y_MINOR_MAX                      (0x0000003fU)

#define CSL_SYNCTIMER_REVISION_X_MAJOR_MASK                     (0x00000700U)
#define CSL_SYNCTIMER_REVISION_X_MAJOR_SHIFT                    (8U)
#define CSL_SYNCTIMER_REVISION_X_MAJOR_RESETVAL                 (0x00000007U)
#define CSL_SYNCTIMER_REVISION_X_MAJOR_MAX                      (0x00000007U)

#define CSL_SYNCTIMER_REVISION_CUSTOM_MASK                      (0x000000C0U)
#define CSL_SYNCTIMER_REVISION_CUSTOM_SHIFT                     (6U)
#define CSL_SYNCTIMER_REVISION_CUSTOM_RESETVAL                  (0x00000000U)
#define CSL_SYNCTIMER_REVISION_CUSTOM_MAX                       (0x00000003U)

#define CSL_SYNCTIMER_REVISION_R_RTL_MASK                       (0x0000F800U)
#define CSL_SYNCTIMER_REVISION_R_RTL_SHIFT                      (11U)
#define CSL_SYNCTIMER_REVISION_R_RTL_RESETVAL                   (0x00000000U)
#define CSL_SYNCTIMER_REVISION_R_RTL_MAX                        (0x0000001fU)

#define CSL_SYNCTIMER_REVISION_FUNC_MASK                        (0x0FFF0000U)
#define CSL_SYNCTIMER_REVISION_FUNC_SHIFT                       (16U)
#define CSL_SYNCTIMER_REVISION_FUNC_RESETVAL                    (0x00000000U)
#define CSL_SYNCTIMER_REVISION_FUNC_MAX                         (0x00000fffU)

#define CSL_SYNCTIMER_REVISION_SCHEME_MASK                      (0xC0000000U)
#define CSL_SYNCTIMER_REVISION_SCHEME_SHIFT                     (30U)
#define CSL_SYNCTIMER_REVISION_SCHEME_RESETVAL                  (0x00000001U)
#define CSL_SYNCTIMER_REVISION_SCHEME_HL08                      (0x00000001U)
#define CSL_SYNCTIMER_REVISION_SCHEME_LEGACY                    (0x00000000U)

#define CSL_SYNCTIMER_REVISION_RESETVAL                         (0x50000700U)

/* SYSCONFIG */

#define CSL_SYNCTIMER_SYSCONFIG_IDLEMODE_MASK                   (0x00000018U)
#define CSL_SYNCTIMER_SYSCONFIG_IDLEMODE_SHIFT                  (3U)
#define CSL_SYNCTIMER_SYSCONFIG_IDLEMODE_RESETVAL               (0x00000000U)
#define CSL_SYNCTIMER_SYSCONFIG_IDLEMODE_FORCEIDLE              (0x00000000U)
#define CSL_SYNCTIMER_SYSCONFIG_IDLEMODE_NOIDLE                 (0x00000001U)
#define CSL_SYNCTIMER_SYSCONFIG_IDLEMODE_SMARTIDLE              (0x00000002U)
#define CSL_SYNCTIMER_SYSCONFIG_IDLEMODE_RESERVED1              (0x00000003U)

#define CSL_SYNCTIMER_SYSCONFIG_SYNCMODE_MASK                   (0x00000001U)
#define CSL_SYNCTIMER_SYSCONFIG_SYNCMODE_SHIFT                  (0U)
#define CSL_SYNCTIMER_SYSCONFIG_SYNCMODE_RESETVAL               (0x00000000U)
#define CSL_SYNCTIMER_SYSCONFIG_SYNCMODE_MAX                    (0x00000001U)

#define CSL_SYNCTIMER_SYSCONFIG_RESETVAL                        (0x00000000U)

/* CR */

#define CSL_SYNCTIMER_CR_COUNTER_VALUE_MASK                     (0xFFFFFFFFU)
#define CSL_SYNCTIMER_CR_COUNTER_VALUE_SHIFT                    (0U)
#define CSL_SYNCTIMER_CR_COUNTER_VALUE_RESETVAL                 (0x00000003U)
#define CSL_SYNCTIMER_CR_COUNTER_VALUE_MAX                      (0xffffffffU)

#define CSL_SYNCTIMER_CR_RESETVAL                               (0x00000003U)

#ifdef __cplusplus
}
#endif
#endif
