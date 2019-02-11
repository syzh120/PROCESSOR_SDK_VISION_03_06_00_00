/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \ingroup BSP_DRV_PLATFORM_API Platform Specific API
 *  \addtogroup BSP_DRV_PLATFORM_TDA3XX_API TDA3XX Platform Specific API
 *  @{
 */

/**
 *  \file bsp_platformTda3xx.h
 *
 *  \brief Interface file to the TDA3XX platform specific functions.
 *
 */

#ifndef BSP_PLATFORM_TDA3XX_H_
#define BSP_PLATFORM_TDA3XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Init the underlying platform */
Int32 Bsp_platformTda3xxInit(const Bsp_PlatformInitParams *initParams);

/* De-Init platform related sub-systems */
Int32 Bsp_platformTda3xxDeInit(void);

/* Get the CPU revision */
Bsp_PlatformCpuRev Bsp_platformTda3xxGetCpuRev(void);
Bsp_PlatformPackageType Bsp_platformTda3xxGetPackageType(void);

Int32 Bsp_platformTda3xxSetVencClkSrc(const Bsp_PlatformVencSrc *vencPrms);

Int32 Bsp_platformTda3xxSetPllFreq(const Bsp_PlatformSetPllFreq *pllFreq);

Int32 Bsp_platformTda3xxSetDispcFuncClkSrc(UInt32 fClkSrc);

Int32 Bsp_platformTda3xxSimVideoInputSelect(UInt32 vipInstId,
                                            UInt32 fileId,
                                            UInt32 pixelClk);

/*
 * To set the polarity of the LCD with the polarity value.
 * Refer #Fvid2_Polarity for valid values of polarity and
 */
Int32 Bsp_platformTda3xxSetLCDinputPolarity(UInt32 vencId, UInt32 polarity);
Int32 Bsp_platformTda3xxSetLcdSyncPolarity(UInt32 vencId,
                                           UInt32 ctrlEnable,
                                           UInt32 edgePolarity);
Int32 Bsp_platformTda3xxSetVipClkInversion(UInt32 instId, UInt32 invEnable);

Int32 Bsp_platformTda3xxSetPinmuxRegs(UInt32 mode_index,
                                      UInt32 offset,
                                      UInt32 pupd_info);
Int32 Bsp_platformTda3xxLockRegion(Bsp_PlatformMmrRegion region);
Int32 Bsp_platformTda3xxUnLockRegion(Bsp_PlatformMmrRegion region);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_PLATFORM_TDA3XX_H_ */

/* @} */
