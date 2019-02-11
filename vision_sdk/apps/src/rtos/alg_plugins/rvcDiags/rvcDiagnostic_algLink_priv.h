/******************************************************************************
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
******************************************************************************/

/**
 *******************************************************************************
 *
 * \ingroup ALGORITHM_LINK_API
 * \defgroup ALGORITHM_LINK_IMPL Algorithm Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file rvcDiagnosticLink_algLink_priv.h RVC software diagnostic private
 * API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 *******************************************************************************
 */

#ifndef _RVCDIAGNOSTICLINK_ALGLINK_PRIV_H_
#define _RVCDIAGNOSTICLINK_ALGLINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_vip.h>
#include <ti/csl/cslr_vpe.h>
#include <ti/csl/cslr_vip_parser.h>
#include <ti/csl/cslr_dss.h>
#include <ti/csl/cslr_vpdma.h>


#include <include/link_api/system.h>
#include <include/alglink_api/algorithmLink_rvcDiagnostics.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_link_stats_if.h>
#include <include/link_api/system_common.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define DUMP_REGISTERS 1
#define COMPARE_REGISTERS 2
#define COMPARE_SOME_REGISTERS 3
#define FIX_REGISTERS 4

#define MAX_S_DIAG_REGFIELDS 4

#define MAX_PF_DIAG_REGFIELDS 24

#define RVC_DIAG_DISPLAY_DURATION_MS   (24*60*60*1000)
#define RVC_DIAG_DISPLAY_FONTID        (5)

#define GPIO_IN_INTERRUPT

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/*
 *******************************************************************************
 *
 *  \brief Structure containing register base, offset, mask, shift and reference.
 *
 *******************************************************************************
 */

typedef struct
{
    unsigned int base;
    unsigned int offset;
    unsigned int mask;
    unsigned int shift;
    unsigned int reference;
} RegField_t;

/*
 *******************************************************************************
 *
 *  \brief Array of ReqField_t containing the startup diagnostic register.
 *
 *******************************************************************************
 */

static RegField_t  startupDiagnosticsRegField[MAX_S_DIAG_REGFIELDS] =
{
    // Checking sanity of IPU surroundings componets.
    // PRCM, IPU_CONFIG, IPU_MMU, memory checks, required peripherals, uboot inherited settings.
    // 0: CM_CLKSEL_SYSCLK1 - Select the SYS CLK for SYSCLK1_32K_CLK
    {SOC_CKGEN_PRM_BASE, CM_CLKSEL_SYSCLK1, CM_CLKSEL_SYSCLK1_CLKSEL_MASK,CM_CLKSEL_SYSCLK1_CLKSEL_SHIFT, 0x0},
    // 1: CM_CLKSEL_CORE - CORE module clock selection - CLKSEL_L3
    {SOC_CKGEN_CM_CORE_AON_BASE, CM_CLKSEL_CORE, CM_CLKSEL_CORE_CLKSEL_L3_MASK,CM_CLKSEL_CORE_CLKSEL_L3_SHIFT, 0x1},
    // 2: VIP_CLKC_RST - VIP1_DP_RST
    {SOC_VIP1_VIP_REGS_BASE, VIP_CLKC_RST, VIP_CLKC_RST_S0_DP_RST_MASK, VIP_CLKC_RST_S0_DP_RST_SHIFT, 0x0},
    // 3: VIP_CLKC_RST - VPDMA_RST
    {SOC_VIP1_VIP_REGS_BASE, VIP_CLKC_RST, VIP_CLKC_RST_VPDMA_RST_MASK, VIP_CLKC_RST_VPDMA_RST_SHIFT, 0x0}
};

/*
 *******************************************************************************
 *
 *  \brief Array of ReqField_t containing per Frame diagnostic register.
 *
 *******************************************************************************
 */

static RegField_t perFrameDiagnosticsRegField[MAX_PF_DIAG_REGFIELDS] =
{
    // VIP Module
#ifdef TDA2EX_BUILD
    // 0: VIP_MAIN - DATA_INTERFACE_MODE
    {SOC_VIP1_VIP_PARSER_SLICE1_REGS_BASE, VIP_MAIN, VIP_MAIN_DATA_INTERFACE_MODE_MASK, VIP_MAIN_DATA_INTERFACE_MODE_SHIFT, 0x2},
    // 1: VIP_MAIN - CLIP_BLNK
    {SOC_VIP1_VIP_PARSER_SLICE1_REGS_BASE, VIP_MAIN, VIP_MAIN_CLIP_BLNK_MASK, VIP_MAIN_CLIP_BLNK_SHIFT, 0x0},
    // 2: VIP_MAIN - CLIP_ACTIVE
    {SOC_VIP1_VIP_PARSER_SLICE1_REGS_BASE, VIP_MAIN, VIP_MAIN_CLIP_ACTIVE_MASK, VIP_MAIN_CLIP_ACTIVE_SHIFT, 0x0},
#else
    // 0: VIP_MAIN - DATA_INTERFACE_MODE
    {SOC_VIP1_VIP_PARSER_SLICE0_REGS_BASE, VIP_MAIN, VIP_MAIN_DATA_INTERFACE_MODE_MASK, VIP_MAIN_DATA_INTERFACE_MODE_SHIFT, 0x2},
    // 1: VIP_MAIN - CLIP_BLNK
    {SOC_VIP1_VIP_PARSER_SLICE0_REGS_BASE, VIP_MAIN, VIP_MAIN_CLIP_BLNK_MASK, VIP_MAIN_CLIP_BLNK_SHIFT, 0x0},
    // 2: VIP_MAIN - CLIP_ACTIVE
    {SOC_VIP1_VIP_PARSER_SLICE0_REGS_BASE, VIP_MAIN, VIP_MAIN_CLIP_ACTIVE_MASK, VIP_MAIN_CLIP_ACTIVE_SHIFT, 0x0},
#endif

    // 3: VIP_VPDMA_SETUP - 0x4897D030
    {SOC_VIP1_VIP_VPDMA_REGS_BASE, VPDMA_SETUP, VPDMA_SETUP_SEC_BASE_CH_MASK, VPDMA_SETUP_SEC_BASE_CH_SHIFT, 0x0},

    // DISPC Module
#ifdef TDA2EX_BUILD
    // 4: SOC_DISPC_BASE, DSS_DISPC_TIMING_H3 - HBP, HFP, HSW
    {SOC_DISPC_BASE, DSS_DISPC_TIMING_H3, 0xFFFFFFFF, 0, 0x02F02F1F},
#else
    // 4: SOC_DISPC_BASE, DSS_DISPC_TIMING_H1 - HBP, HFP, HSW
    {SOC_DISPC_BASE, DSS_DISPC_TIMING_H1, 0xFFFFFFFF, 0, 0x02B02F1F},
#endif
    // 5: SOC_DISPC_BASE, DSS_DISPC_POL_FREQ1 - IEO
    {SOC_DISPC_BASE, DSS_DISPC_POL_FREQ1, DSS_DISPC_POL_FREQ1_IEO_MASK, DSS_DISPC_POL_FREQ1_IEO_SHIFT, 0x0},
    // 6: SOC_DISPC_BASE, DSS_DISPC_GLOBAL_ALPHA - VID3/VID2/VID1/GFX; 0=fullytransparent, 0xFF=fully opaque.
    {SOC_DISPC_BASE, DSS_DISPC_GLOBAL_ALPHA, 0xFFFFFFFF, 0, 0xFFFFFFFF},
#ifdef TDA2EX_BUILD
    // 7: SOC_DISPC_BASE, DSS_DISPC_SIZE_LCD3 - LPP (lines per panel), PPL (pixels per line)
    {SOC_DISPC_BASE, DSS_DISPC_SIZE_LCD3, 0xFFFFFFFF, 0, 0x031F04FF},
#else
    // 7: SOC_DISPC_BASE, DSS_DISPC_SIZE_LCD1 - LPP (lines per panel), PPL (pixels per line)
    {SOC_DISPC_BASE, DSS_DISPC_SIZE_LCD1, 0xFFFFFFFF, 0, 0x031F04FF},
#endif
    // 8: DSS_DISPC_VID2_POSITION (POSX = 280; POSY = 45)
    {SOC_DISPC_BASE, DSS_DISPC_VID2_POSITION, 0xFFFFFFFF, 0, 0x002D0118},
    // 9: DSS_DISPC_VID2_SIZE (SIZEY = 479; SIZEX = 719; 720x480 VID2 size)
    {SOC_DISPC_BASE, DSS_DISPC_VID2_SIZE, 0xFFFFFFFF, 0, 0x01DF02CF},
#ifdef TDA2EX_BUILD
    // 10: DSS_DISPC_VID2_ATTRIBUTES
    {SOC_DISPC_BASE, DSS_DISPC_VID2_ATTRIBUTES, 0xFFFFFFFF, 0, 0x8628886B},
#else
    // 10: DSS_DISPC_VID2_ATTRIBUTES
    {SOC_DISPC_BASE, DSS_DISPC_VID2_ATTRIBUTES, 0xFFFFFFFF, 0, 0x0628886B},
#endif
    // 11: DSS_DISPC_VID2_BUF_THRESHOLD
    {SOC_DISPC_BASE, DSS_DISPC_VID2_BUF_THRESHOLD, 0xFFFFFFFF, 0, 0x07FF07F8},
    // 12: DSS_DISPC_VID2_ROW_INC
    {SOC_DISPC_BASE, DSS_DISPC_VID2_ROW_INC, 0xFFFFFFFF, 0, 0x1},
    // 13: Resize factors for horizontal and vertical up/down sampling
    {SOC_DISPC_BASE, DSS_DISPC_VID2_FIR, 0xFFFFFFFF, 0, 0x06AA071C},
    // 14: picture size before up/down scaling MEMSIZEY, MEMSIZEX
    {SOC_DISPC_BASE, DSS_DISPC_VID2_PICTURE_SIZE, 0xFFFFFFFF, 0, 0x031F04FF},
    // 15: DSS_DISPC_VID3_POSITION
    {SOC_DISPC_BASE, DSS_DISPC_VID3_POSITION, 0xFFFFFFFF, 0, 0x000A0118},
    // 16: DSS_DISPC_VID3_SIZE
    {SOC_DISPC_BASE, DSS_DISPC_VID3_SIZE, 0x0FFF0FFF, 0, 0x01DF02CF},
#ifdef TDA2EX_BUILD
    // 17: DSS_DISPC_VID3_ATTRIBUTES
    {SOC_DISPC_BASE, DSS_DISPC_VID3_ATTRIBUTES, 0xFFFFFFFF, 0, 0x8A288A35},
#else
    // 17: DSS_DISPC_VID3_ATTRIBUTES
    {SOC_DISPC_BASE, DSS_DISPC_VID3_ATTRIBUTES, 0xFFFFFFFF, 0, 0x0A288A35},
#endif
    // 18: DSS_DISPC_VID3_ATTRIBUTES2
    {SOC_DISPC_BASE, DSS_DISPC_VID3_ATTRIBUTES2, 0xFFFFFFFF, 0, 0x0},
    // 19: DSS_DISPC_VID3_ROW_INC
    {SOC_DISPC_BASE, DSS_DISPC_VID3_ROW_INC, 0xFFFFFFFF, 0, 0x1},
    // 20: DSS_DISPC_VID3_PIXEL_INC
    {SOC_DISPC_BASE, DSS_DISPC_VID3_PIXEL_INC, DSS_DISPC_VID1_PIXEL_INC_PIXELINC_MASK, DSS_DISPC_VID1_PIXEL_INC_PIXELINC_SHIFT, 0x1},
    // 21: picture size before up/down scaling MEMSIZEY, MEMSIZEX
    {SOC_DISPC_BASE, DSS_DISPC_VID3_PICTURE_SIZE, 0xFFFFFFFF, 0, 0x01DF02CF},
#ifdef GPIO_IN_INTERRUPT
#ifdef TDA2EX_BUILD
    // 22: GPIO 6 Pin 28 - reverse gear detection; SOC_CORE_PAD_IO_REGISTERS_BASE - set MUXMODE to gpio6_28 CTRL_CORE_PAD_MMC1_SDWP
    {SOC_CORE_PAD_IO_REGISTERS_BASE, CTRL_CORE_PAD_MMC1_SDWP, CTRL_CORE_PAD_MMC1_SDWP_MMC1_SDWP_MUXMODE_MASK, CTRL_CORE_PAD_MMC1_SDWP_MMC1_SDWP_MUXMODE_SHIFT, CTRL_CORE_PAD_MMC1_SDWP_MMC1_SDWP_MUXMODE_GPIO6_28_14},
    // 23: GPIO 6 Pin 28 - reverse gear detection; CTRL_CORE_IPU2_IRQ_49_50 - set IPU2_IRQ_49 to point to IRQ_CROSSBAR_347 (0x15B)
    {SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CTRL_CORE_IPU2_IRQ_49_50, CTRL_CORE_IPU2_IRQ_49_50_IPU2_IRQ_49_MASK, CTRL_CORE_IPU2_IRQ_49_50_IPU2_IRQ_49_SHIFT, 0x8F}
#else
    // 22: GPIO 7 Pin 18 - reverse gear detection; SOC_CORE_PAD_IO_REGISTERS_BASE - set MUXMODE to gpio7_18
    {SOC_CORE_PAD_IO_REGISTERS_BASE, CTRL_CORE_PAD_GPMC_AD8, CTRL_CORE_PAD_GPMC_AD8_GPMC_AD8_MUXMODE_MASK, CTRL_CORE_PAD_GPMC_AD8_GPMC_AD8_MUXMODE_SHIFT, CTRL_CORE_PAD_GPMC_AD8_GPMC_AD8_MUXMODE_GPIO7_18_14},
    // 23: GPIO 7 Pin 18 - reverse gear detection; CTRL_CORE_IPU2_IRQ_49_50 - set IPU2_IRQ_49 to point to IRQ_CROSSBAR_347 (0x15B)
    {SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CTRL_CORE_IPU2_IRQ_49_50, CTRL_CORE_IPU2_IRQ_49_50_IPU2_IRQ_49_MASK, CTRL_CORE_IPU2_IRQ_49_50_IPU2_IRQ_49_SHIFT, 0x15B}
#endif
#endif
};

/**
 *******************************************************************************
 *
 *   \brief Structure containing RVC diagnostic algorithm link specific parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef  struct
{
    System_LinkOutQueParams outQueParams;
    /**< Output queue information */
    System_LinkInQueParams inQueParams;
    /**< Input queue information */
    UInt32 numInputChannels;
    /**< Number of input channels on input Q (Prev link output Q) */
    System_LinkChInfo inputChInfo[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< channel info of input */
    AlgorithmLink_RvcDiagnosticCreateParams algLinkCreateParams;
    /**< Create params of the CRC algorithm */
    AlgorithmLink_OutputQueueInfo outputQInfo;
    /**< All the information about output Q */
    AlgorithmLink_InputQueueInfo inputQInfo;
    /**< All the information about input Q */
    System_LinkStatistics *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */
    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */
} AlgorithmLink_RvcDiagnosticObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_rvcDiagnosticCreate(void * pObj, void * pCreateParams);
Int32 AlgorithmLink_rvcDiagnosticProcess(void * pObj);
Int32 AlgorithmLink_rvcDiagnosticControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_rvcDiagnosticStop(void * pObj);
Int32 AlgorithmLink_rvcDiagnosticDelete(void * pObj);
Int32 AlgorithmLink_rvcDiagnosticPrintStatistics(void *pObj, AlgorithmLink_RvcDiagnosticObj *pRvcDiagnosticObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* _RVCDIAGNOSTICLINK_ALGLINK_PRIV_H_ */
