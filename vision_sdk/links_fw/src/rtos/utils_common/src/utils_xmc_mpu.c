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
 * \file utils_xmc_mpu.c
 *
 * \brief  This file has the implementation for utility functions for using
 *         XMC(Extended Memory Controller) and MPU(Memory Protection Unit)
 *         in C66x in TDA2x and TDA3x.
 *         Currently supports only protection on:
 *          - EMIF (EMIF1 only) using XMC
 *          - L2RAM using MPU
 *         This will also define no-execute segments at OCMC/EMIF boundaries
 *         to avoid prefetch accesses going into invalid memory section.
 *
 *         Based on ECC_FFI_INCLUDE macro definition, it will add segments
 *         to demonstrate FFI.
 *         The VisionSDK example will demonstrate FFI only on following:
 *          - DSP and DSP_EDMA (using XMC)
 *          - EVE and EVE_EDMA (using Firewalls - not present in this file)
 *         FFI on DSP and DSP_EDMA
 *          VisionSDK uses a common stack for all algorithms on DSP.
 *          As a result, we cannot demonstrate FFI on DSP_DATA regions.
 *          This section will be, therefore, mapped as QM.
 *          We will demonstrate how to prevent write-access from DSP to two
 *          specific ASIL regions - UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL and
 *          UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL.
 *          VisionSDK framework on DSP will have full access to these regions.
 *          Only the "safeFrameCopyPlugin" will be denied access.
 *          VisionSDK framework will ensure firewall permission switch before
 *          executing this plugin.
 *          To demonstrate error detection, we will generate write accesses to
 *          these regions in the safeFrameCopyPlugin and demonstrate that these
 *          accesses are prevented by firewalls and detected by the VisionSDK
 *          framework.
 *          L2RAM will be given QM permissions since all algos in VisionSDK use
 *          it only as scratch - it is included here just to demonstrate
 *          example usage of HAL.
 *
 * \version 0.0 (Jan 2016) : [CSG] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <xdc/std.h>
#include <string.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include "utils_common/include/utils_xmc_mpu.h"
#include "utils_common/include/utils_mem.h"
#include <ti/csl/arch/csl_arch.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define XMC_MDMA_ERR (110U)

/* Permission summary:
 * ASIL mode permissions will restrict write-access to USR mode
 * QM mode permissions will allow all transactions.
 */
#define DSPICFG_PERMISSION_MODE_ASIL  (DSPICFG_L2MPPA_LOCAL | \
                                       DSPICFG_L2MPPA_SR    | \
                                       DSPICFG_L2MPPA_SW    | \
                                       DSPICFG_L2MPPA_SX    | \
                                       DSPICFG_L2MPPA_UR    | \
                                       DSPICFG_L2MPPA_UX)

#define DSPXMC_PERMISSION_MODE_ASIL   (DSPXMC_ALLOW_UR | \
                                       DSPXMC_ALLOW_UX | \
                                       DSPXMC_ALLOW_SR | \
                                       DSPXMC_ALLOW_SW | \
                                       DSPXMC_ALLOW_SX)

#define DSPICFG_PERMISSION_MODE_QM    (DSPICFG_PERMISSION_MODE_ASIL |\
                                       DSPICFG_L2MPPA_UW)

#define DSPXMC_PERMISSION_MODE_QM     (DSPXMC_PERMISSION_MODE_ASIL |\
                                       DSPXMC_ALLOW_UW)

/* Keys to lock/unlock MPU and XMC registers
 * Default state is unlocked. Locking is optional.
 * Keys can be changed by user.
 */
#define MPLK_KEY0   (0xABCD1234U)
#define MPLK_KEY1   (0x1234ABCDU)
#define MPLK_KEY2   (0xA1B2C3D4U)
#define MPLK_KEY3   (0x4D3C2B1AU)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */
typedef struct Utils_xmcMpuXmcSegments_t
{
    UInt32 startAddr;
    /**< Start Address XMC segment */
    UInt32 segSize;
    /**< Size of segment in bytes */
    UInt32 permission;
    /**< Permissions for XMC segment */
} Utils_xmcMpuXmcSegments;

/*******************************************************************************
 *  Global variables
 *******************************************************************************
 */

static Utils_xmcMpuXmcSegments gXmcSegments[DSPXMC_NUM_SEGMENTS] = {0};

#ifdef ECC_FFI_INCLUDE
static UInt32 LINK_STATS_ADDR = 0U;
static UInt32 LINK_STATS_SIZE = 0U;
#endif

/*******************************************************************************
 *  Function prototype's
 *******************************************************************************
 */
#ifdef ECC_FFI_INCLUDE
static Void Utils_xmcMpuAddRegions(UInt32  addr,
                                   UInt32  size,
                                   UInt32 *pSegId,
                                   UInt32  perms);
#endif
static UInt32 UTILS_xmcMpuGetSegSize(UInt32 sizeInBytes);
static Void Utils_xmcErrISR(UArg ctx);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

#ifdef ECC_FFI_INCLUDE
/*
 * XMC supports DSPXMC_NUM_SEGMENTS segments of type (addr, size)
 * where "addr" is "size" aligned and "size" is a power of 2 and > 4KB
 *
 * This function creates multiple segments for XMC for any (addr, size)
 * provided it can satisfy the above requirements
 */
static Void Utils_xmcMpuAddRegions(UInt32  addr,
                                   UInt32  size,
                                   UInt32 *pSegId,
                                   UInt32  perms)
{
    UInt32 i, tmpSegSize, temp;
    Vps_printf(" UTILS: XMC_MPU:  0x%08x - 0x%08x\n",
               addr, size);
    UTILS_assert(0U == (addr % (4U*KB)));

    i = 12U; /* start checking with (1<<12) = 4U*KB alignment */
    while((Bool)TRUE)
    {
        /* This while loop will identify the largest page size
         * which can be used for addr
         */
        temp = ((UInt32)1U << i);
        while(0U == (addr % temp))
        {
            i++;
            temp = ((UInt32)1U << i);
        }
        i--;

        temp = ((UInt32)1U << (i + (UInt32)1U));
        while((0U != (addr % temp)) &&
              (size != 0U))
        {
            /* This while loop will
             *  - allocate at least one page of size (1<<i+1)
             *  - If after this allocation, the size remaining is more than
             *    (1<<i) it will exit this inner loop
             *  - If after allocation, the size remaining is less than (1<<i)
             *    it will continue allocating smaller pages until all memory
             *    is allocated, or pSegId reaches DSPXMC_NUM_SEGMENTS.
             */
            tmpSegSize = ((UInt32)1U << i);
            while(size < tmpSegSize)
            {
                tmpSegSize = tmpSegSize/2U;
                i--;
            }
            UTILS_assert(*pSegId < DSPXMC_NUM_SEGMENTS);
            gXmcSegments[*pSegId].startAddr  = addr;
            gXmcSegments[*pSegId].segSize    = tmpSegSize;
            gXmcSegments[*pSegId].permission = perms;
            Vps_printf(" UTILS: XMC_MPU:  0x%08x - 0x%08x\n",
                       gXmcSegments[*pSegId].startAddr,
                       gXmcSegments[*pSegId].segSize);

            addr = addr + gXmcSegments[*pSegId].segSize;
            size = size - gXmcSegments[*pSegId].segSize;
            *pSegId = *pSegId + 1U;

            temp = ((UInt32)1U << (i + ((UInt32)1U)));
        }

        /* Exit if all memory is covered using XMC segments */
        if(0U == size)
        {
            break;
        }
    }
}
#endif

static UInt32 UTILS_xmcMpuGetSegSize(UInt32 sizeInBytes)
{
    UInt32 tmpSegSize = 0;
    UTILS_assert(sizeInBytes >= (4U*KB));
    while(sizeInBytes > 1U)
    {
        tmpSegSize++;
        sizeInBytes = sizeInBytes/2U;
    }
    return (tmpSegSize - 1U);
}

static Void Utils_xmcErrISR(UArg ctx)
{
    UInt32 faultAddr;
    faultAddr = DSPXMCGetFaultAddr(SOC_DSP_XMC_CTRL_BASE);
    if(0U != faultAddr)
    {
        Vps_printf(" UTILS: XMC_MPU:  XMC Fault at 0x%08x!!!\n", faultAddr);
    }
    else
    {
        Vps_printf(" UTILS: MDMA ERROR - invalid memory access in DSP!!!\n");
    }
    DSPXMCClearFaultRegs(SOC_DSP_XMC_CTRL_BASE);
    DSPICFGClearMdmaErrEvt(SOC_DSP_ICFG_BASE);
}

/*
 * \brief Setup L3FW error handlers
 *
 * \param  None
 *
 * \return None
 */
void Utils_xmcMpuInit(void)
{
    UInt32 segId;
    UInt32 numSegs;
    UInt32 segSizeEnum;

    /* MISRA.CAST.Func.Ptr
     * MISRAC_2004_Rule_11.1
     * MISRAC_WAIVER:
     * Casting it to EventCombiner_FuncPtr as required by the BIOS API
     */
    EventCombiner_dispatchPlug(
                    XMC_MDMA_ERR,
                    (EventCombiner_FuncPtr)(&Utils_xmcErrISR),
                    NULL,
                    (Bool)TRUE
                    );
    EventCombiner_enableEvent(XMC_MDMA_ERR);

    /*
     *  At reset, XMC Segment 0 and 1 provide full access to
     *  0x0000_0000 to 0xFFFF_FFFF.
     *
     *  For FFI (only created when ECC_FFI_INCLUDE is defined:
     *  Define Segment for EMIF in XMC
     *  - ASIL permissions for full EMIF by default
     *    Segment 0 and Segment 1 will be used for this.
     *  - Override DSP_DATA to provide QM permissions
     *  - Override UTILS_HEAPID_DDR_CACHED_SR_ECC_QM to provide QM
     *    permissions
     *
     *  Following Segment will be defined always
     *  Define no-access Segment
     *  -   4KB before 0x4030_0000
     *  - 512KB after  0x4038_0000
     *  -   4KB after  0x4060_0000 (in TDA2X)
     *
     *  L2RAM - QM permissions to entire L2RAM
     *
     */

    /* Region 0 - Default ASIL for everything */
    segId = 0U;
    gXmcSegments[segId].startAddr  = 0x00000000U;
    gXmcSegments[segId].segSize    = 2048U*MB;
    #ifdef ECC_FFI_INCLUDE
    gXmcSegments[segId].permission = DSPICFG_PERMISSION_MODE_ASIL;
    #else
    gXmcSegments[segId].permission = DSPICFG_PERMISSION_MODE_QM;
    #endif
    segId++;

    /* Region 1 - Default ASIL for everything */
    UTILS_assert(segId < DSPXMC_NUM_SEGMENTS);
    gXmcSegments[segId].startAddr  = 0x80000000U;
    gXmcSegments[segId].segSize    = 2048U*MB;
    #ifdef ECC_FFI_INCLUDE
    gXmcSegments[segId].permission = DSPICFG_PERMISSION_MODE_ASIL;
    #else
    gXmcSegments[segId].permission = DSPICFG_PERMISSION_MODE_QM;
    #endif
    segId++;

    /* Block accesses before start of OCMC */
    UTILS_assert(segId < DSPXMC_NUM_SEGMENTS);
    gXmcSegments[segId].startAddr  = SOC_OCMC_RAM1_BASE - (4U*KB);
    gXmcSegments[segId].segSize    = 4U*KB;
    gXmcSegments[segId].permission = 0U;
    segId++;

    /* Block accesses between OCMC1 and OCMC2 */
    UTILS_assert(segId < DSPXMC_NUM_SEGMENTS);
    gXmcSegments[segId].startAddr  = SOC_OCMC_RAM1_BASE + (512U*KB);
    gXmcSegments[segId].segSize    = 512U*KB;
    gXmcSegments[segId].permission = 0U;
    segId++;

#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
    /* OCMC2 and OCMC3 are contiguous.
     * Block accesses after end of OCMC3 */
    UTILS_assert(segId < DSPXMC_NUM_SEGMENTS);
    gXmcSegments[segId].startAddr  = SOC_OCMC_RAM3_BASE + (1U*MB);
    gXmcSegments[segId].segSize    = 4U*KB;
    gXmcSegments[segId].permission = 0U;
    segId++;
#endif

#ifdef ECC_FFI_INCLUDE
    {
        Utils_MemHeapStats heapStats;
        Int32              status;
        status = Utils_memGetHeapStats(
            UTILS_HEAPID_DDR_CACHED_SR_ECC_QM,
            &heapStats);
        UTILS_assert(0 == status);
        UTILS_assert(heapStats.heapSize > 0U);
        /* 2MB after UTILS_HEAPID_DDR_CACHED_SR_ECC_QM
         * is reserved for DSP1/DSP2 in .xs file
         */
        heapStats.heapSize += (2U*MB);
        Utils_xmcMpuAddRegions(heapStats.heapAddr,
                               heapStats.heapSize,
                               &segId,
                               DSPICFG_PERMISSION_MODE_QM);

        /* Link-Stats should be kept in QM */
        Utils_xmcMpuAddRegions(LINK_STATS_ADDR,
                               LINK_STATS_SIZE,
                               &segId,
                               DSPICFG_PERMISSION_MODE_QM);
    }
#endif
    numSegs = segId;
    Vps_printf(" UTILS: XMC_MPU:  Segments used = %d\n", numSegs);
    for(segId = 0U; segId < numSegs; segId++)
    {
        segSizeEnum = UTILS_xmcMpuGetSegSize(gXmcSegments[segId].segSize);
        DSPXMCSetMPAXSegment(
            SOC_DSP_XMC_CTRL_BASE,              /* baseAddress   */
            segId,                              /* segmentId     */
            segSizeEnum,                        /* segmentSize   */
            gXmcSegments[segId].startAddr,      /* inpBAddress   */
            gXmcSegments[segId].startAddr,      /* repAddressL   */
            0x0U,                               /* repAddressH   */
            gXmcSegments[segId].permission);    /* permsFieldVal */
    }
}

/*
 * \brief Unregister L3FW error handlers
 *
 * \param  None
 *
 * \return None
 */
void Utils_xmcMpuDeInit(void)
{
    EventCombiner_disableEvent(XMC_MDMA_ERR);
}

#ifdef ECC_FFI_INCLUDE
void Utils_xmcMpuSetLinkStatsSectInfo(UInt32 addr, UInt32 size)
{
    LINK_STATS_ADDR = addr;
    LINK_STATS_SIZE = size;
}
#endif
