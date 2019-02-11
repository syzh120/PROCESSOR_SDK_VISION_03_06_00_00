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
 *  \addtogroup BSP_DRV_PLATFORM_TDA2XX_API TDA2XX Platform Specific API
 *  @{
 */

/**
 *  \file bsp_platformTda2xx.h
 *
 *  \brief Interface file to the TDA2XX platform specific functions.
 *
 */

#ifndef BSP_PLATFORM_TDA2XX_H_
#define BSP_PLATFORM_TDA2XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*DSS PLL Registers*/
#define PLL_CONTROL                                   (0x00000000U)
#define PLL_STATUS                                    (0x00000004U)
#define PLL_GO                                        (0x00000008U)
#define PLL_CONFIGURATION1                            (0x0000000CU)
#define PLL_CONFIGURATION2                            (0x00000010U)
#define PLL_CONFIGURATION3                            (0x00000014U)

/*DSI1 Registers */
#define DSI_CLK_CTRL_OFFSET                           (0x00000054U)
#define DSI_PLL_STATUS_OFFSET                         (0x00000304U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

struct Bsp_PlatformDpllConfig
{
    UInt32 frequency;
    UInt32 multiplier;
    UInt32 divider;
    UInt32 hsDivider;
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Init the underlying platform */
Int32 Bsp_platformTda2xxInit(const Bsp_PlatformInitParams *initParams);

/* De-Init platform related sub-systems */
Int32 Bsp_platformTda2xxDeInit(void);

/* Get the CPU revision */
Bsp_PlatformCpuRev Bsp_platformTda2xxGetCpuRev(void);
Bsp_PlatformPackageType Bsp_platformTda2xxGetPackageType(void);

Int32 Bsp_platformTda2xxSetVencClkSrc(const Bsp_PlatformVencSrc *vencPrms);

Int32 Bsp_platformTda2xxSetPllFreq(const Bsp_PlatformSetPllFreq *pllFreq);

Int32 Bsp_platformTda2xxSetDispcFuncClkSrc(UInt32 fClkSrc);

Int32 Bsp_platformTda2xxSimVideoInputSelect(UInt32 vipInstId,
                                            UInt32 fileId,
                                            UInt32 pixelClk);

Int32 Bsp_platformTda2xxEnableHdmiPll(UInt32 enable);

UInt32 Bsp_platformTda2xxGetFtRev(void);

/*
 * To set the polarity of the LCD with the polarity value.
 * Refer #Fvid2_Polarity for valid values of polarity and
 */
Int32 Bsp_platformTda2xxSetLCDinputPolarity(UInt32 vencId, UInt32 polarity);
Int32 Bsp_platformTda2xxSetLcdSyncPolarity(UInt32 vencId,
                                           UInt32 ctrlEnable,
                                           UInt32 edgePolarity);
Int32 Bsp_platformTda2xxSetVipClkInversion(UInt32 instId, UInt32 invEnable);

Int32 Bsp_platformTda2xxSetPinmuxRegs(UInt32 mode_index,
                                      UInt32 offset,
                                      UInt32 pupd_info);
Int32 Bsp_platformTda2xxLockRegion(Bsp_PlatformMmrRegion region);
Int32 Bsp_platformTda2xxUnLockRegion(Bsp_PlatformMmrRegion region);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_PLATFORM_TDA2XX_H_ */

/* @} */
