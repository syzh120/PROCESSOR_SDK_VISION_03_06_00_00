/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 * \file system_bsp_init.c
 *
 * \brief  APIs for initializing BIOS Drivers.
 *
 *         BIOS Support Package inits, which includes BIOS video drivers inits
 *
 * \version 0.0 (Jun 2013) : [CM] First version
 * \version 0.1 (Jul 2013) : [CM] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *                           Include Files                                     *
 ******************************************************************************/

#include "system_bsp_init.h"
#include <ti/drv/stw_lld/platform/chip_config.h>

#ifdef ROBUST_RVC_INCLUDE
#ifdef TDA2EX_BUILD
#include <ti/csl/soc/tda2ex/hw_ctrl_core_pad_io.h>
#endif
#ifdef TDA2XX_BUILD
#include <ti/csl/soc/tda2xx/hw_ctrl_core_pad_io.h>
#endif
#ifdef TDA2PX_BUILD
#include <ti/csl/soc/tda2px/hw_ctrl_core_pad_io.h>
#endif
#endif

/**
 *******************************************************************************
 * \brief Align BSS memory with that of BIOS heap library requirement
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Link Stack
 *
 *        Align descriptor memory with that of VPDMA requirement.
 *        Place the descriptor in non-cached heap section.
 *
 *******************************************************************************
 */

#ifdef VPE_INCLUDE
/**
 *  BspUtils_appSetVpeLazyLoad
 *  \brief Sets the VPE lazy loading parameters through the VPS control driver.
 */
static Int32 System_bspSetVpeLazyLoad(UInt32 vpeInstId,
                                 UInt32 scalerId,
                                 Bool   lazyLoadingEnable);
#endif

 /*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Initialize the required modules of BIOS video drivers
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 System_bspInit(void)
{
    Int32 nStatus = SYSTEM_LINK_STATUS_SOK;
    Bsp_CommonInitParams commonInitPrms; /* Initialized using BSP APIs */
    Bsp_PlatformInitParams platInitPrms; /* Initialized using BSP APIs */
    Vps_InitParams vpsInitPrms; /* Initialized using BSP APIs */

    BspCommonInitParams_init(&commonInitPrms);

    Vps_printf(" SYSTEM: BSP Common Init in progress !!!\n");
    nStatus = Bsp_commonInit(&commonInitPrms);
    if (SYSTEM_LINK_STATUS_SOK != nStatus)
    {
        Vps_printf(" SYSTEM: BSP Common Init Failed !!!\n");
    }
    else
    {
        Vps_printf(" SYSTEM: BSP Common Init Done !!!\n");
    }

    if (SYSTEM_LINK_STATUS_SOK == nStatus)
    {
        BspPlatformInitParams_init(&platInitPrms);
        Vps_printf(" SYSTEM: BSP Platform Init in progress !!!\n");
#ifdef A15_TARGET_OS_LINUX
        platInitPrms.isPinMuxSettingReq  = FALSE;
        platInitPrms.isAllMcASPInitReq   = FALSE;
        platInitPrms.isAllMcSPIInitReq   = FALSE;
        platInitPrms.isDmaXBarSettingReq = FALSE;
        platInitPrms.isIrqXBarSettingReq = FALSE;
#else
        platInitPrms.isPinMuxSettingReq = TRUE;
#endif

        nStatus = Bsp_platformInit(&platInitPrms);

#ifdef A15_TARGET_OS_LINUX
        if (SYSTEM_LINK_STATUS_SOK == nStatus)
        {
            /* Unlock MMR_LOCK_2  */
            nStatus = Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_2);
            if (SYSTEM_LINK_STATUS_SOK == nStatus)
            {

                /* XBAR VIP1_IRQ1 (=351) to IPU1_27 */
                BspOsal_irqXbarConnect(XBAR_INST_IPU1_IRQ_27, 351);
                #if !defined (TDA2EX_BUILD)
                /* XBAR VIP2_IRQ1 (=352) to IPU1_28 */
                BspOsal_irqXbarConnect(XBAR_INST_IPU1_IRQ_28, 352);
                #if !defined (TDA2PX_BUILD)
                /* XBAR VIP3_IRQ1 (=353) to IPU1_29 */
                BspOsal_irqXbarConnect(XBAR_INST_IPU1_IRQ_29, 353);
                #endif
                #endif
                /* XBAR VPE1_IRQ1 (=354) to IPU1_30 */
                BspOsal_irqXbarConnect(XBAR_INST_IPU1_IRQ_30, 354);
                #ifdef ROBUST_RVC_INCLUDE
                /* I2C4 PinMux setting
                 * CTRL_CORE_PAD_MCASP4_ACLKX - I2C4_SDA (4)
                 * CTRL_CORE_PAD_MCASP4_FSX - I2C4_SCL (4)
                 */
                Bsp_platformSetPinmuxRegs((UInt32) 4, (UInt32) CTRL_CORE_PAD_MCASP4_ACLKX,
                    BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                Bsp_platformSetPinmuxRegs((UInt32) 4, (UInt32) CTRL_CORE_PAD_MCASP4_FSX,
                    BSP_PLATFORM_IOPAD_CFG_DEFAULT);
                #ifdef TDA2EX_BUILD
                /* XBAR I2C1_IRQ to IPU1_41 - I2C1_IRQ (51 or 0x33)
                 * XBAR I2C5_IRQ to IPU1_42 - I2C5_IRQ (55 or 0x37)
                 */
                BspOsal_irqXbarConnect(XBAR_INST_IPU1_IRQ_41, 51);
                BspOsal_irqXbarConnect(XBAR_INST_IPU1_IRQ_42, 55);
                #endif
                /* XBAR I2C4_IRQ (57) to IPU1_48 */
                BspOsal_irqXbarConnect(XBAR_INST_IPU1_IRQ_48, 57);
                #endif
                #ifdef TDA2EX_BUILD
                /* i2c camera is controlled by bios */
                /* I2C5 mux */
                /* XBAR I2C5_IRQ to IPU1_42 */
                BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_42, CSL_XBAR_I2C5_IRQ);
                /* XBAR CAL_IRQ to IPU1_71 */
                BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_71, CSL_XBAR_CAL_IRQ);
                #endif

                #ifdef TDA2PX_BUILD
                /* i2c camera is controlled by bios */
                /* I2C5 mux */
                /* XBAR I2C5_IRQ to IPU1_49 */
                BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_49, CSL_XBAR_I2C5_IRQ);
                /* XBAR CAL_IRQ to IPU1_71 */
                BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_71, CSL_XBAR_CAL_IRQ);
                /* XBAR ISS_IRQ to IPU1_32 */
                BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_32, CSL_XBAR_EVE3_IRQ_OUT0);
                #endif

                #ifdef BOARD_TYPE_TDA2XX_RVP
                #ifndef BSP_DISABLE_I2C0
                BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_41, CSL_XBAR_I2C1_IRQ);
                #endif  /* !BSP_DISABLE_I2C0 */
                #ifndef BSP_DISABLE_I2C1
                BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_42, CSL_XBAR_I2C2_IRQ);
                #endif  /* !BSP_DISABLE_I2C1 */
                #ifndef BSP_DISABLE_I2C2
                /* XBAR I2C3_IRQ to IPU1_43 */
                BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_43, CSL_XBAR_I2C3_IRQ);
                #endif  /* !BSP_DISABLE_I2C2 */
                #ifndef BSP_DISABLE_I2C3
                #ifdef USE_LINUX_INTC_NUMBERS
                /* XBAR I2C4_IRQ to IPU1_44 */
                BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_44, CSL_XBAR_I2C4_IRQ);
                #else
                /* XBAR I2C4_IRQ to IPU1_48 */
                BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_48, CSL_XBAR_I2C4_IRQ);
                #endif  /* USE_LINUX_INTC_NUMBERS */
                #endif  /* !BSP_DISABLE_I2C3 */
                #ifndef BSP_DISABLE_I2C4
                /* XBAR I2C5_IRQ to IPU1_49 */
                BspOsal_irqXbarConnect(CSL_XBAR_INST_IPU1_IRQ_49, CSL_XBAR_I2C5_IRQ);
                #endif  /* !BSP_DISABLE_I2C4 */
                #endif  /* BOARD_TYPE_TDA2XX_RVP */
            }
        }
#endif

        if (SYSTEM_LINK_STATUS_SOK != nStatus)
        {
            Vps_printf(" SYSTEM: BSP Platform Init Failed !!!\n");
        }
        else
        {
            Vps_printf(" SYSTEM: BSP Platform Init Done !!!\n");
        }
    }

    if (SYSTEM_LINK_STATUS_SOK == nStatus)
    {
        Vps_printf(" SYSTEM: FVID2 Init in progress !!!\n");
        nStatus = Fvid2_init(NULL);
        if (SYSTEM_LINK_STATUS_SOK != nStatus)
        {
            Vps_printf(" SYSTEM: FVID2 Init Failed !!!\n");
        }
        else
        {
            Vps_printf(" SYSTEM: FVID2 Init Done !!!\n");
        }
    }

    if (SYSTEM_LINK_STATUS_SOK == nStatus)
    {
        Vps_printf(" SYSTEM: VPS Init in progress !!!\n");

        VpsInitParams_init(&vpsInitPrms);

#ifdef DDR_MEM_1024M
       /* This one to one mapping is required for the 1GB builds */
        vpsInitPrms.virtBaseAddr = 0x80000000U;
        vpsInitPrms.physBaseAddr = 0x80000000U;
        vpsInitPrms.isAddrTransReq = FALSE;
#else
        vpsInitPrms.virtBaseAddr = 0xA0000000U;
        vpsInitPrms.physBaseAddr = 0x80000000U;
        /* if Virtual address != Physical address then enable translation */
        vpsInitPrms.isAddrTransReq = TRUE;
#endif
        Vps_printf(" SYSTEM: VPDMA Descriptor Memory Address translation"
                    " ENABLED [0x%08x -> 0x%08x]\n",
                    vpsInitPrms.virtBaseAddr,
                    vpsInitPrms.physBaseAddr);

    }

    if (SYSTEM_LINK_STATUS_SOK == nStatus)
    {
        nStatus = Vps_init(&vpsInitPrms);
        if (SYSTEM_LINK_STATUS_SOK != nStatus)
        {
            Vps_printf(" SYSTEM: VPS Init Failed !!!\n");
        }
        else
        {
            Vps_printf(" SYSTEM: VPS Init Done !!!\n");
        }
    }

#ifdef VPE_INCLUDE
    System_bspSetVpeLazyLoad(VPS_M2M_INST_VPE1, 0, (Bool)TRUE);
#endif

    return nStatus;
}

/**
 *******************************************************************************
 *
 * \brief De-initialize the previously initialized modules
 *  of BIOS video drivers
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 System_bspDeInit(void)
{
    Int32 nStatus = SYSTEM_LINK_STATUS_EFAIL;

    nStatus = Vps_deInit(NULL);
    if (SYSTEM_LINK_STATUS_SOK != nStatus)
    {
        Vps_printf(" SYSTEM: VPS De-Init Failed !!!\n");
    }

    if(SYSTEM_LINK_STATUS_SOK == nStatus)
    {
        nStatus = Fvid2_deInit(NULL);
        if (SYSTEM_LINK_STATUS_SOK != nStatus)
        {
            Vps_printf(" SYSTEM: FVID2 De-Init Failed !!!\n");
        }
    }

    if(SYSTEM_LINK_STATUS_SOK == nStatus)
    {
           nStatus = Bsp_platformDeInit(NULL);
           if (SYSTEM_LINK_STATUS_SOK != nStatus)
           {
               Vps_printf(" SYSTEM: BSP Platform De-Init Failed !!!\n");
           }
    }

    if(SYSTEM_LINK_STATUS_SOK == nStatus)
    {
           nStatus = Bsp_commonDeInit(NULL);
           if (SYSTEM_LINK_STATUS_SOK != nStatus)
           {
               Vps_printf(" SYSTEM: BSP Common De-Init Failed !!!\n");
           }
    }

    return nStatus;
}

#ifdef VPE_INCLUDE
/**
 *  BspUtils_appSetVpeLazyLoad
 *  \brief Sets the VPE lazy loading parameters through the VPS control driver.
 */
static Int32 System_bspSetVpeLazyLoad(UInt32 vpeInstId,
                                 UInt32 scalerId,
                                 Bool   lazyLoadingEnable)
{
    Int32        retVal     = FVID2_SOK;
    Fvid2_Handle fvidHandle = NULL;
    Vps_ScLazyLoadingParams lazyPrms;

    fvidHandle = Fvid2_create(
        (UInt32) FVID2_VPS_CTRL_DRV,
        VPS_CTRL_INST_0,
        NULL,
        NULL,
        NULL);
    if (NULL == fvidHandle)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  "%s: Error @ line %d\n", __FUNCTION__, __LINE__);
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        VpsScLazyLoadingParams_init(&lazyPrms);
        lazyPrms.vpeInstId         = vpeInstId;
        lazyPrms.scalerId          = scalerId;
        lazyPrms.lazyLoadingEnable = (UInt32) lazyLoadingEnable;

        /* Set the lazy load params */
        retVal = Fvid2_control(
            fvidHandle,
            IOCTL_VPS_CTRL_SET_VPE_LAZY_LOADING,
            &lazyPrms,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_2trace(BspAppTrace, GT_ERR,
                      "%s: Error @ line %d\n", __FUNCTION__, __LINE__);
        }
    }

    if (NULL != fvidHandle)
    {
        retVal = Fvid2_delete(fvidHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_2trace(BspAppTrace, GT_ERR,
                      "%s: Error @ line %d\n", __FUNCTION__, __LINE__);
        }
    }

    return (retVal);
}
#endif
