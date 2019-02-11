/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2017
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
 */

/**
 *  \file bsputils_app.c
 *
 *  \brief This file implements application level generic helper functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>

#ifndef BARE_METAL
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#endif

#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/vps/include/vps_control.h>
#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/vps_displayCtrlDataTypes.h>
#include <ti/drv/vps/include/vps_displayCtrl.h>
#endif /* #ifdef VPS_DSS_BUILD */
#include <ti/drv/vps/include/boards/bsp_board.h>
#if defined (VPS_TI_RTOS_I2C)
#include <ti/drv/i2c/I2C.h>
#else
#include <ti/drv/bsp_lld/i2c/bsp_i2c.h>
#endif
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/vps/examples/utility/bsputils_mem.h>
#include <ti/drv/vps/examples/utility/bsputils_prf.h>
#include <ti/drv/vps/examples/utility/bsputils_fileio.h>
#include <ti/drv/vps/examples/utility/bsputils_uart.h>
#include <ti/csl/soc.h>
#if defined (VPS_TI_RTOS_MMCSD)
#include <ti/drv/mmcsd/MMCSD.h>
#include <ti/drv/mmcsd/src/MMCSD_osal.h>
#include <ti/drv/mmcsd/soc/MMCSD_soc.h>
/* No EDMA support for baremetal */
#if !defined(BARE_METAL)
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>
#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>
#endif
#else
#include <ti/drv/stw_lld/fatlib/hsmmcsd_API.h>
#include <ti/sdo/edma3/drv/src/edma3.h>
#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>
#endif
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
#include <ti/csl/csl_wd_timer.h>
#elif defined (SOC_TDA3XX)
#include <ti/csl/csl_rti.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSPUTILS_MAX_FILENAMESIZE (100U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure to store app objects.
 */
typedef struct BspUtils_AppObj_t
{
    Bool               initDone;
    /**< Initialization done flag. */
    BspOsal_SemHandle  lockSem;
    /**< Semaphore used to protect globals. */

    Bsp_PlatformId     platformId;
    /**< Platform identifier. */
    Bsp_PlatformCpuRev cpuRev;
    /**< CPU version identifier. */
#if !defined (BARE_METAL)
    EDMA3_DRV_Handle   hEdma;
    /**< System edma handle. */
#endif
} BspUtils_AppObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  BspUtils_print
 *  \brief BSP utility print function.
 */
#if !defined(SOC_AM574x) && !defined(SOC_AM572x) && !defined(SOC_AM571x)
static void BspUtils_print(char *pBuffer);
#endif
static inline UInt32 BspUtils_appCalcCrc32(UInt8 byte, UInt32 prevCrc32);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief BSP Utils app object used for storing semaphore handle, flags etc. */
static BspUtils_AppObj   gBspUtilsAppObj;

#if !defined (VPS_TI_RTOS_I2C)
/**
 *  \brief I2C Device Init Params used for storing init Params handle,
 *  Semaphore handle, etc.
 */
static I2c_DevInitParams gI2cDevInitParams[BSP_DEVICE_I2C_INST_ID_MAX];
#endif

/** \brief CRC table. */
static const UInt32      gCrc32Table[256U] =
{
    0x00000000U, 0x77073096U, 0xEE0E612CU, 0x990951BAU,
    0x076DC419U, 0x706AF48FU, 0xE963A535U, 0x9E6495A3U,
    0x0EDB8832U, 0x79DCB8A4U, 0xE0D5E91EU, 0x97D2D988U,
    0x09B64C2BU, 0x7EB17CBDU, 0xE7B82D07U, 0x90BF1D91U,
    0x1DB71064U, 0x6AB020F2U, 0xF3B97148U, 0x84BE41DEU,
    0x1ADAD47DU, 0x6DDDE4EBU, 0xF4D4B551U, 0x83D385C7U,
    0x136C9856U, 0x646BA8C0U, 0xFD62F97AU, 0x8A65C9ECU,
    0x14015C4FU, 0x63066CD9U, 0xFA0F3D63U, 0x8D080DF5U,
    0x3B6E20C8U, 0x4C69105EU, 0xD56041E4U, 0xA2677172U,
    0x3C03E4D1U, 0x4B04D447U, 0xD20D85FDU, 0xA50AB56BU,
    0x35B5A8FAU, 0x42B2986CU, 0xDBBBC9D6U, 0xACBCF940U,
    0x32D86CE3U, 0x45DF5C75U, 0xDCD60DCFU, 0xABD13D59U,
    0x26D930ACU, 0x51DE003AU, 0xC8D75180U, 0xBFD06116U,
    0x21B4F4B5U, 0x56B3C423U, 0xCFBA9599U, 0xB8BDA50FU,
    0x2802B89EU, 0x5F058808U, 0xC60CD9B2U, 0xB10BE924U,
    0x2F6F7C87U, 0x58684C11U, 0xC1611DABU, 0xB6662D3DU,

    0x76DC4190U, 0x01DB7106U, 0x98D220BCU, 0xEFD5102AU,
    0x71B18589U, 0x06B6B51FU, 0x9FBFE4A5U, 0xE8B8D433U,
    0x7807C9A2U, 0x0F00F934U, 0x9609A88EU, 0xE10E9818U,
    0x7F6A0DBBU, 0x086D3D2DU, 0x91646C97U, 0xE6635C01U,
    0x6B6B51F4U, 0x1C6C6162U, 0x856530D8U, 0xF262004EU,
    0x6C0695EDU, 0x1B01A57BU, 0x8208F4C1U, 0xF50FC457U,
    0x65B0D9C6U, 0x12B7E950U, 0x8BBEB8EAU, 0xFCB9887CU,
    0x62DD1DDFU, 0x15DA2D49U, 0x8CD37CF3U, 0xFBD44C65U,
    0x4DB26158U, 0x3AB551CEU, 0xA3BC0074U, 0xD4BB30E2U,
    0x4ADFA541U, 0x3DD895D7U, 0xA4D1C46DU, 0xD3D6F4FBU,
    0x4369E96AU, 0x346ED9FCU, 0xAD678846U, 0xDA60B8D0U,
    0x44042D73U, 0x33031DE5U, 0xAA0A4C5FU, 0xDD0D7CC9U,
    0x5005713CU, 0x270241AAU, 0xBE0B1010U, 0xC90C2086U,
    0x5768B525U, 0x206F85B3U, 0xB966D409U, 0xCE61E49FU,
    0x5EDEF90EU, 0x29D9C998U, 0xB0D09822U, 0xC7D7A8B4U,
    0x59B33D17U, 0x2EB40D81U, 0xB7BD5C3BU, 0xC0BA6CADU,

    0xEDB88320U, 0x9ABFB3B6U, 0x03B6E20CU, 0x74B1D29AU,
    0xEAD54739U, 0x9DD277AFU, 0x04DB2615U, 0x73DC1683U,
    0xE3630B12U, 0x94643B84U, 0x0D6D6A3EU, 0x7A6A5AA8U,
    0xE40ECF0BU, 0x9309FF9DU, 0x0A00AE27U, 0x7D079EB1U,
    0xF00F9344U, 0x8708A3D2U, 0x1E01F268U, 0x6906C2FEU,
    0xF762575DU, 0x806567CBU, 0x196C3671U, 0x6E6B06E7U,
    0xFED41B76U, 0x89D32BE0U, 0x10DA7A5AU, 0x67DD4ACCU,
    0xF9B9DF6FU, 0x8EBEEFF9U, 0x17B7BE43U, 0x60B08ED5U,
    0xD6D6A3E8U, 0xA1D1937EU, 0x38D8C2C4U, 0x4FDFF252U,
    0xD1BB67F1U, 0xA6BC5767U, 0x3FB506DDU, 0x48B2364BU,
    0xD80D2BDAU, 0xAF0A1B4CU, 0x36034AF6U, 0x41047A60U,
    0xDF60EFC3U, 0xA867DF55U, 0x316E8EEFU, 0x4669BE79U,
    0xCB61B38CU, 0xBC66831AU, 0x256FD2A0U, 0x5268E236U,
    0xCC0C7795U, 0xBB0B4703U, 0x220216B9U, 0x5505262FU,
    0xC5BA3BBEU, 0xB2BD0B28U, 0x2BB45A92U, 0x5CB36A04U,
    0xC2D7FFA7U, 0xB5D0CF31U, 0x2CD99E8BU, 0x5BDEAE1DU,

    0x9B64C2B0U, 0xEC63F226U, 0x756AA39CU, 0x026D930AU,
    0x9C0906A9U, 0xEB0E363FU, 0x72076785U, 0x05005713U,
    0x95BF4A82U, 0xE2B87A14U, 0x7BB12BAEU, 0x0CB61B38U,
    0x92D28E9BU, 0xE5D5BE0DU, 0x7CDCEFB7U, 0x0BDBDF21U,
    0x86D3D2D4U, 0xF1D4E242U, 0x68DDB3F8U, 0x1FDA836EU,
    0x81BE16CDU, 0xF6B9265BU, 0x6FB077E1U, 0x18B74777U,
    0x88085AE6U, 0xFF0F6A70U, 0x66063BCAU, 0x11010B5CU,
    0x8F659EFFU, 0xF862AE69U, 0x616BFFD3U, 0x166CCF45U,
    0xA00AE278U, 0xD70DD2EEU, 0x4E048354U, 0x3903B3C2U,
    0xA7672661U, 0xD06016F7U, 0x4969474DU, 0x3E6E77DBU,
    0xAED16A4AU, 0xD9D65ADCU, 0x40DF0B66U, 0x37D83BF0U,
    0xA9BCAE53U, 0xDEBB9EC5U, 0x47B2CF7FU, 0x30B5FFE9U,
    0xBDBDF21CU, 0xCABAC28AU, 0x53B39330U, 0x24B4A3A6U,
    0xBAD03605U, 0xCDD70693U, 0x54DE5729U, 0x23D967BFU,
    0xB3667A2EU, 0xC4614AB8U, 0x5D681B02U, 0x2A6F2B94U,
    0xB40BBE37U, 0xC30C8EA1U, 0x5A05DF1BU, 0x2D02EF8DU,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  BspUtils_appInit
 *  \brief BSP application utils init function.
 */
Int32 BspUtils_appInit(void)
{
    Int32 retVal = BSP_SOK;
    BspUtils_AppObj *appObj = &gBspUtilsAppObj;

    BspUtils_memset(appObj, 0U, sizeof (*appObj));

    /* Get platform type, board and CPU revisions */
    appObj->platformId = Bsp_platformGetId();
    if ((appObj->platformId == BSP_PLATFORM_ID_UNKNOWN) ||
        (appObj->platformId >= BSP_PLATFORM_ID_MAX))
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Unrecognized platform!!\r\n");
        retVal = BSP_EFAIL;
    }
    appObj->cpuRev = Bsp_platformGetCpuRev();
    if (appObj->cpuRev >= BSP_PLATFORM_CPU_REV_MAX)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Unrecognized CPU version!!\r\n");
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK == retVal)
    {
        appObj->lockSem = BspOsal_semCreate((Int32) 1, FALSE);
        if (NULL == appObj->lockSem)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Error: Semaphore create failed!!\r\n");
            retVal = BSP_EALLOC;
        }
    }

    if (BSP_SOK == retVal)
    {
        appObj->initDone = (Bool) TRUE;
    }

    return (retVal);
}

/**
 *  BspUtils_appDeInit
 *  \brief BSP application utils deinit function.
 */
Int32 BspUtils_appDeInit(void)
{
    Int32 retVal = BSP_SOK;
    BspUtils_AppObj *appObj = &gBspUtilsAppObj;

    if (NULL != appObj->lockSem)
    {
        BspOsal_semDelete(&appObj->lockSem);
        appObj->lockSem = NULL;
    }

    appObj->initDone = (Bool) FALSE;

    return (retVal);
}

/**
 *  BspUtils_appDefaultInit
 *  \brief BSP application utils function to call all the default init
 *  functions.
 */
Int32 BspUtils_appDefaultInit(UInt32 isI2cInitReq)
{
    Int32                   retVal = BSP_SOK;
    Vps_InitParams          vpsInitPrms;
    Bsp_CommonInitParams    commonInitPrms;
    Bsp_BoardInitParams     boardInitPrms;
    Bsp_PlatformInitParams  platInitPrms;
    Bsp_DeviceInitParams    deviceInitPrms;
#if !defined (VPS_TI_RTOS_I2C)
    UInt32                  instCnt;
    lld_hsi2c_initParam_t   i2cInitParams[BSP_DEVICE_I2C_INST_ID_MAX];
    Bsp_BoardI2cInstData   *i2cInstData;
#endif
    const Bsp_BoardI2cData *i2cData;
#if !defined (BARE_METAL)
    EDMA3_DRV_Result        edmaResult      = 0;
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    /* Catalog devices have already initialized the OSAL printf */
#else
    BspOsal_InitParams_t    bspOsalInitPrms = {0};
    UInt32                  tempFuncPtr;
#endif

    BspCommonInitParams_init(&commonInitPrms);
    retVal += Bsp_commonInit(&commonInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Common Init failed!!\r\n");
    }

    BspBoardInitParams_init(&boardInitPrms);
    /* Override board detection if I2C is disabled */
    if (((Bool) TRUE) != ((Bool) isI2cInitReq))
    {
        boardInitPrms.boardId      = BSP_BOARD_UNKNOWN;
        boardInitPrms.baseBoardRev = BSP_BOARD_REV_UNKNOWN;
        boardInitPrms.dcBoardRev   = BSP_BOARD_REV_UNKNOWN;
    }
    retVal += Bsp_boardInit(&boardInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Board Init failed!!\r\n");
    }

    BspPlatformInitParams_init(&platInitPrms);
    retVal += Bsp_platformInit(&platInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Platform Init failed!!\r\n");
    }

    retVal += Fvid2_init(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: FVID2 Init failed!!\r\n");
    }

    VpsInitParams_init(&vpsInitPrms);
    /* Need to use address translation becasue of limited memory of 512MB */
#if defined (SOC_TDA3XX) || defined (TDA3XX_INTERPOSER_BUILD) || \
    defined (SOC_TDA2EX) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    vpsInitPrms.isAddrTransReq = TRUE;
    vpsInitPrms.virtBaseAddr   = 0xA0000000U;
    vpsInitPrms.physBaseAddr   = 0x80000000U;
#endif
    /* Pass the interrupt numbers from application for VPS instances.
     * setting same interrupt numbers as in default setting for referance.
     * Specifying for all instances, only applicable instances are used by lib.
     * Driver will only register for the specified interrupt numbers.
     * The corresponding crossbar mapping for the device interrupt should be
     * done by the application. In the Vps examples the crossar mapping is
     * done from function Bsp_platformTda2xxInit/Bsp_platformTda3xxInit.
     * Application may pass the Bsp_PlatformInitParams->isIrqXBarSettingReq as
     * false to Bsp_platformInit function and do all the crossbar mapping
     * required or update the crossbar configuration done in
     * Bsp_platformTda2xxInit/Bsp_platformTda3xxInit.
     */
    #if defined (VPS_VIP1_BUILD)
        vpsInitPrms.irqParams.vipIrqNum[0U] = CSL_INTC_EVENTID_VIP1INT0;
    #endif
    #if defined (VPS_VIP2_BUILD)
        vpsInitPrms.irqParams.vipIrqNum[1U] = CSL_INTC_EVENTID_VIP2INT0;
    #endif
    #if defined (VPS_VIP3_BUILD)
        vpsInitPrms.irqParams.vipIrqNum[2U] = CSL_INTC_EVENTID_VIP3INT0;
    #endif
    #if defined (VPS_VPE_BUILD)
        vpsInitPrms.irqParams.vpeIrqNum    = CSL_INTC_EVENTID_VPEINT0;
    #endif
    #if defined (VPS_DSS_BUILD)
        vpsInitPrms.irqParams.dssIrqNum    = CSL_INTC_EVENTID_DSS_DISPC;
    #endif
    #if defined (VPS_CAL_BUILD)
        vpsInitPrms.irqParams.calIrqNum    = CSL_CAL_IRQ_NUM;
    #endif
    #if defined (VPS_ISS_BUILD)
        vpsInitPrms.irqParams.issIrqNum    = CSL_ISS_IRQ0_NUM;
    #endif
    retVal += Vps_init(&vpsInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: VPS Init failed!!\r\n");
    }

    /* Override I2C init for non-EVM builds */
    if (BSP_PLATFORM_ID_EVM != Bsp_platformGetId())
    {
        isI2cInitReq = FALSE;
    }

    if (((Bool) TRUE) == ((Bool) isI2cInitReq))
    {
        i2cData = Bsp_boardGetI2cData();
        GT_assert(BspAppTrace, (NULL != i2cData));
        GT_assert(BspAppTrace,
                  (i2cData->numInst <= BSP_DEVICE_I2C_INST_ID_MAX));
        GT_assert(BspAppTrace, (NULL != i2cData->instData));
#if defined (VPS_TI_RTOS_I2C)
        I2C_init();
#else
        for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
        {
            i2cInstData = &i2cData->instData[instCnt];
            GT_assert(BspAppTrace,
                      (i2cInstData->instId < BSP_DEVICE_I2C_INST_ID_MAX));
            i2cInitParams[instCnt].opMode       = HSI2C_OPMODE_INTERRUPT;
            i2cInitParams[instCnt].isMasterMode = TRUE;
            i2cInitParams[instCnt].is10BitAddr  = FALSE;
            i2cInitParams[instCnt].i2cBusFreq   =
                (lld_i2c_busspeed) i2cInstData->busClkKHz;
            i2cInitParams[instCnt].i2cIntNum      = i2cInstData->intNum;
            i2cInitParams[instCnt].i2cOwnAddr     = 0xCC;
            gI2cDevInitParams[instCnt].initParams = &i2cInitParams[instCnt];
            gI2cDevInitParams[instCnt].hsi2c_sem  =
                BspOsal_semCreate((Int32) 1, (Bool) TRUE);
            gI2cDevInitParams[instCnt].instId = i2cInstData->instId;
        }

        if (i2cData->numInst > 0)
        {
            retVal = I2c_GlobalInit(i2cData->numInst, &gI2cDevInitParams[0U]);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Error: I2C Init failed!!\r\n");
            }
        }
#endif

        BspDeviceInitParams_init(&deviceInitPrms);
#if defined (SOC_TDA3XX)
        deviceInitPrms.isI2cProbingReq = TRUE;
#else
        /* For J6 Eco 23X23 and 17X17 Evms the I2C3 SDA line is connected to
         * daughter card connector EXP_P1 pin 12. This is used for JMAR App
         * board. But on Vision App board the corresponding pin is connected to
         * GPIO_USER_RESET connected to CPLD. The probe causes the CPLD to reset.
         * So disabling probe for TDA2Ex build
         */
        deviceInitPrms.isI2cProbingReq = FALSE;
#endif
        retVal += Bsp_deviceInit(&deviceInitPrms);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Error: Device Init failed!!\r\n");
        }
    }

    retVal += Bsp_boardLateInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Board Late Init failed!!\r\n");
    }

    retVal += BspUtils_memInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App MEM Utils Init failed!!\r\n");
    }

    retVal += BspUtils_prfInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App PRF Utils Init failed!!\r\n");
    }

    retVal += BspUtils_appInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App Utils Init failed!!\r\n");
    }

#if defined (VPS_TI_RTOS_MMCSD)
#if defined (SOC_AM572x) || defined (SOC_AM571x) || defined (SOC_AM574x)
    MMCSD_init();
#if defined(BARE_METAL)
    retVal += BspUtils_initFileio(NULL);
    GT_0trace(BspAppTrace, GT_ERR, "Error: init File IO complete for Bare Metal cases!!\r\n");
#else
    gBspUtilsAppObj.hEdma = edma3init(0, &edmaResult);
    retVal += BspUtils_initFileio(gBspUtilsAppObj.hEdma);
    GT_0trace(BspAppTrace, GT_ERR, "Error: init File IO complete for Sys Bios cases!!\r\n");
#endif
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: File io init failed!!\r\n");
    }
#endif
#else
    /* Initialize system edma and initialize file io */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    Bsp_boardPowerOnDevice(BSP_DRV_ID_MMC, BSP_DEVICE_MMC_INST_ID_1,
                           (UInt32) TRUE);
    Bsp_boardSetPinMux(BSP_DRV_ID_MMC, BSP_DEVICE_MMC_INST_ID_1,
                       BSP_BOARD_MODE_DEFAULT);
    Bsp_boardSelectDevice(BSP_DRV_ID_MMC, BSP_DEVICE_MMC_INST_ID_1);
    HSMMCSDInit(MMC1_INST);
#endif
#if defined (SOC_TDA3XX)
    Bsp_boardPowerOnDevice(BSP_DRV_ID_MMC, BSP_DEVICE_MMC_INST_ID_4,
                           (UInt32) TRUE);
    Bsp_boardSetPinMux(BSP_DRV_ID_MMC, BSP_DEVICE_MMC_INST_ID_4,
                       BSP_BOARD_MODE_DEFAULT);
    Bsp_boardSelectDevice(BSP_DRV_ID_MMC, BSP_DEVICE_MMC_INST_ID_4);
    HSMMCSDInit(MMC4_INST);
#endif
    gBspUtilsAppObj.hEdma = edma3init(0, &edmaResult);
    retVal += BspUtils_initFileio(gBspUtilsAppObj.hEdma);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: File io init failed!!\r\n");
    }
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    /* UART initialization printf is already done, and hence not needed here again */
#else
    BspUtils_uartInit();
    tempFuncPtr = (UInt32) & BspUtils_print;
    bspOsalInitPrms.printFxn = (BspOsal_PrintFxn) (tempFuncPtr);
    BspOsal_Init(&bspOsalInitPrms);
#endif
    /* All trace prints after this will go to UART console insted of CCS. */

    /* Print FVID2 and BSP version string and platform info*/
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_2trace(BspAppTrace, GT_INFO,
              " Build time            : [%s %s]\r\n", __TIME__, __DATE__);
    GT_1trace(BspAppTrace, GT_INFO,
              " FVID2 Version         : [%s]\r\n", Fvid2_getVersionString());
    GT_1trace(BspAppTrace, GT_INFO,
              " BSP Version           : [%s]\r\n", Bsp_getVersionString());
    Bsp_platformPrintInfo();
    Bsp_boardPrintInfo();
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    return (retVal);
}

#if defined(SOC_AM574x) || defined(SOC_AM572x) || defined(SOC_AM571x)
/* For AM parts, we don't need this utility
 * as the UART print is already initialized
 * to only Uart print and no System_printf
 */
#else
static void BspUtils_print(char *pBuffer)
{
    /* Print on the uart console */
    BspUtils_uartPrint(pBuffer);

    /* Print on CCS console */
    System_printf(pBuffer);
    System_flush();
}
#endif

/**
 *  BspUtils_appDefaultDeInit
 *  \brief BSP application utils function to call all the default de-init
 *  functions.
 */
Int32 BspUtils_appDefaultDeInit(UInt32 isI2cDeInitReq)
{
    Int32  retVal = BSP_SOK;
    const Bsp_BoardI2cData *i2cData;
#if !defined (VPS_TI_RTOS_I2C)
    UInt32 instCnt;
#endif

    retVal += BspUtils_appDeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App Utils De-Init failed!!\r\n");
    }

    retVal += BspUtils_prfDeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: App PRF Utils De-Init failed!!\r\n");
    }

    retVal += BspUtils_memDeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: App MEM Utils De-Init failed!!\r\n");
    }

    /* Override I2C de-init for non-EVM builds */
    if (BSP_PLATFORM_ID_EVM != Bsp_platformGetId())
    {
        isI2cDeInitReq = FALSE;
    }

    if (((Bool) TRUE) == ((Bool) isI2cDeInitReq))
    {
        i2cData = Bsp_boardGetI2cData();
        GT_assert(BspAppTrace, (NULL != i2cData));
        GT_assert(BspAppTrace,
                  (i2cData->numInst <= BSP_DEVICE_I2C_INST_ID_MAX));

        retVal += Bsp_deviceDeInit(NULL);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Error: Device De-Init failed!!\r\n");
        }
#if !defined (VPS_TI_RTOS_I2C)
        if (i2cData->numInst > 0)
        {
            for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
            {
                BspOsal_semDelete(&(gI2cDevInitParams[instCnt].hsi2c_sem));
            }
            retVal += I2c_GlobalDeInit(NULL);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Error: I2C De-Init failed!!\r\n");
            }
        }
#endif
    }

    retVal += Vps_deInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: VPS De-Init failed!!\r\n");
    }

    retVal += Fvid2_deInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: FVID2 De-Init failed!!\r\n");
    }

    retVal += Bsp_platformDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: BSP Platform De-Init failed!!\r\n");
    }

    retVal += Bsp_boardDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Board De-Init failed!!\r\n");
    }

    retVal += Bsp_commonDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Common De-Init failed!!\r\n");
    }

#if !defined (VPS_TI_RTOS_MMCSD)
    /* De-Init system edma and file io */
    retVal += BspUtils_deinitFileio();
    retVal += edma3deinit(0, gBspUtilsAppObj.hEdma);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: File io De-Init failed!!\r\n");
    }
#endif

    BspOsal_Deinit();
    BspUtils_uartDeinit();

    return (retVal);
}

/**
 *  BspUtils_appDefaultSerialInit
 *  \brief BSP application utils function to call all the default init
 *  functions related to serial drivers.
 */
Int32 BspUtils_appDefaultSerialInit(UInt32 isI2cInitReq)
{
    Int32  retVal = BSP_SOK;
    Bsp_CommonInitParams    commonInitPrms;
    Bsp_BoardInitParams     boardInitPrms;
    Bsp_PlatformInitParams  platInitPrms;
    Bsp_DeviceInitParams    deviceInitPrms;
    const Bsp_BoardI2cData *i2cData;
#if !defined (VPS_TI_RTOS_I2C)
    UInt32 instCnt;
    lld_hsi2c_initParam_t   i2cInitParams[BSP_DEVICE_I2C_INST_ID_MAX];
    Bsp_BoardI2cInstData   *i2cInstData;
#endif

    BspCommonInitParams_init(&commonInitPrms);
    retVal += Bsp_commonInit(&commonInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Common Init failed!!\r\n");
    }

    BspBoardInitParams_init(&boardInitPrms);
    /* Override board detection if I2C is disabled */
    if (((Bool) TRUE) != ((Bool) isI2cInitReq))
    {
        boardInitPrms.boardId      = BSP_BOARD_UNKNOWN;
        boardInitPrms.baseBoardRev = BSP_BOARD_REV_UNKNOWN;
        boardInitPrms.dcBoardRev   = BSP_BOARD_REV_UNKNOWN;
    }
    retVal += Bsp_boardInit(&boardInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Board Init failed!!\r\n");
    }

    BspPlatformInitParams_init(&platInitPrms);
    retVal += Bsp_platformInit(&platInitPrms);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Platform Init failed!!\r\n");
    }

    retVal += Fvid2_init(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: FVID2 Init failed!!\r\n");
    }

    /* Override I2C init for non-EVM builds */
    if (BSP_PLATFORM_ID_EVM != Bsp_platformGetId())
    {
        isI2cInitReq = FALSE;
    }

    if (((Bool) TRUE) == ((Bool) isI2cInitReq))
    {
        i2cData = Bsp_boardGetI2cData();
        GT_assert(BspAppTrace, (NULL != i2cData));
        GT_assert(BspAppTrace,
                  (i2cData->numInst <= BSP_DEVICE_I2C_INST_ID_MAX));
        GT_assert(BspAppTrace, (NULL != i2cData->instData));
#if defined (VPS_TI_RTOS_I2C)
        I2C_init();
#else
        for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
        {
            i2cInstData = &i2cData->instData[instCnt];
            GT_assert(BspAppTrace,
                      (i2cInstData->instId < BSP_DEVICE_I2C_INST_ID_MAX));
            i2cInitParams[instCnt].opMode       = HSI2C_OPMODE_INTERRUPT;
            i2cInitParams[instCnt].isMasterMode = TRUE;
            i2cInitParams[instCnt].is10BitAddr  = FALSE;
            i2cInitParams[instCnt].i2cBusFreq   =
                (lld_i2c_busspeed) i2cInstData->busClkKHz;
            i2cInitParams[instCnt].i2cIntNum      = i2cInstData->intNum;
            i2cInitParams[instCnt].i2cOwnAddr     = 0xCC;
            gI2cDevInitParams[instCnt].initParams = &i2cInitParams[instCnt];
            gI2cDevInitParams[instCnt].hsi2c_sem  =
                BspOsal_semCreate((Int32) 1, (Bool) TRUE);
            gI2cDevInitParams[instCnt].instId = i2cInstData->instId;
        }

        if (i2cData->numInst > 0)
        {
            retVal = I2c_GlobalInit(i2cData->numInst, &gI2cDevInitParams[0U]);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR, "Error: I2C Init failed!!\r\n");
            }
        }
#endif

        BspDeviceInitParams_init(&deviceInitPrms);
#if defined (SOC_TDA3XX) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
        deviceInitPrms.isI2cProbingReq = TRUE;
#else
        deviceInitPrms.isI2cProbingReq = FALSE;
#endif
        retVal += Bsp_deviceInit(&deviceInitPrms);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Error: Device Init failed!!\r\n");
        }
    }

    retVal += BspUtils_prfInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App PRF Utils Init failed!!\r\n");
    }

    retVal += BspUtils_appInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App Utils Init failed!!\r\n");
    }

    /* Print FVID2 and BSP version string and platform info*/
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_2trace(BspAppTrace, GT_INFO,
              " Build time            : [%s %s]\r\n", __TIME__, __DATE__);
    GT_1trace(BspAppTrace, GT_INFO,
              " FVID2 Version         : [%s]\r\n", Fvid2_getVersionString());
    GT_1trace(BspAppTrace, GT_INFO,
              " BSP Version           : [%s]\r\n", Bsp_getVersionString());
    Bsp_platformPrintInfo();
    Bsp_boardPrintInfo();
    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    return (retVal);
}

/**
 *  BspUtils_appDefaultSerialDeInit
 *  \brief BSP application utils function to call all the default de-init
 *  functions related to serial drivers.
 */
Int32 BspUtils_appDefaultSerialDeInit(UInt32 isI2cDeInitReq)
{
    Int32  retVal = BSP_SOK;
    const Bsp_BoardI2cData *i2cData;
#if !defined (VPS_TI_RTOS_I2C)
    UInt32 instCnt;
#endif

    retVal += BspUtils_appDeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: App Utils De-Init failed!!\r\n");
    }

    retVal += BspUtils_prfDeInit();
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: App PRF Utils De-Init failed!!\r\n");
    }

    /* Override I2C de-init for non-EVM builds */
    if (BSP_PLATFORM_ID_EVM != Bsp_platformGetId())
    {
        isI2cDeInitReq = FALSE;
    }

    if (((Bool) TRUE) == ((Bool) isI2cDeInitReq))
    {
        i2cData = Bsp_boardGetI2cData();
        GT_assert(BspAppTrace, (NULL != i2cData));
        GT_assert(BspAppTrace,
                  (i2cData->numInst <= BSP_DEVICE_I2C_INST_ID_MAX));

        retVal += Bsp_deviceDeInit(NULL);
        if (BSP_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR, "Error: Device De-Init failed!!\r\n");
        }

#if !defined (VPS_TI_RTOS_I2C)
        if (i2cData->numInst > 0)
        {
            for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
            {
                BspOsal_semDelete(&(gI2cDevInitParams[instCnt].hsi2c_sem));
            }
            retVal += I2c_GlobalDeInit(NULL);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Error: I2C De-Init failed!!\r\n");
            }
        }
#endif
    }

    retVal += Fvid2_deInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: FVID2 De-Init failed!!\r\n");
    }

    retVal += Bsp_platformDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Error: BSP Platform De-Init failed!!\r\n");
    }

    retVal += Bsp_boardDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Board De-Init failed!!\r\n");
    }

    retVal += Bsp_commonDeInit(NULL);
    if (BSP_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: BSP Common De-Init failed!!\r\n");
    }

    return (retVal);
}

void BspUtils_appPrintMemStatus(void)
{
    BspOsal_StaticMemStatus memStat;

    /* Eliminate KW critical error, initialize all elements */
    memset((void *) &memStat, 0, sizeof (BspOsal_StaticMemStatus));

    BspOsal_getStaticMemStatus(&memStat);

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    GT_0trace(BspAppTrace, GT_INFO, "BSP OSAL Memory Usage\r\n");
    GT_0trace(BspAppTrace, GT_INFO, "---------------------\r\n");

    GT_1trace(BspAppTrace, GT_INFO,
              "Peak OSAL Semaphore Objects : %d\r\n", memStat.peakSemObjs);
    GT_1trace(BspAppTrace, GT_INFO,
              "Max  OSAL Semaphore Objects : %d\r\n", memStat.numMaxSemObjs);
    GT_1trace(BspAppTrace, GT_INFO,
              "Free OSAL Semaphore Objects : %d\r\n", memStat.numFreeSemObjs);

    GT_1trace(BspAppTrace, GT_INFO,
              "Peak OSAL Task      Objects : %d\r\n", memStat.peakTaskObjs);
    GT_1trace(BspAppTrace, GT_INFO,
              "Max  OSAL Task      Objects : %d\r\n", memStat.numMaxTaskObjs);
    GT_1trace(BspAppTrace, GT_INFO,
              "Free OSAL Task      Objects : %d\r\n", memStat.numFreeTaskObjs);

    GT_1trace(BspAppTrace, GT_INFO,
              "Peak OSAL Clock     Objects : %d\r\n", memStat.peakClockObjs);
    GT_1trace(BspAppTrace, GT_INFO,
              "Max  OSAL Clock     Objects : %d\r\n", memStat.numMaxClockObjs);
    GT_1trace(BspAppTrace, GT_INFO,
              "Free OSAL Clock     Objects : %d\r\n", memStat.numFreeClockObjs);

    GT_1trace(BspAppTrace, GT_INFO,
              "Peak OSAL HWI       Objects : %d\r\n", memStat.peakHwiObjs);
    GT_1trace(BspAppTrace, GT_INFO,
              "Max  OSAL HWI       Objects : %d\r\n", memStat.numMaxHwiObjs);
    GT_1trace(BspAppTrace, GT_INFO,
              "Free OSAL HWI       Objects : %d\r\n", memStat.numFreeHwiObjs);

    /* Check for memory leaks */
    if (memStat.numFreeSemObjs != memStat.numMaxSemObjs)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  "Warning: Not all SEM Objects are freed!!\r\n");
    }
    if (memStat.numFreeTaskObjs != memStat.numMaxTaskObjs)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  "Warning: Not all TSK Objects are freed!!\r\n");
    }
    if (memStat.numFreeClockObjs != memStat.numMaxClockObjs)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  "Warning: Not all CLK Objects are freed!!\r\n");
    }
    if (memStat.numFreeHwiObjs != memStat.numMaxHwiObjs)
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  "Warning: Not all HWI Objects are freed!!\r\n");
    }

    GT_0trace(BspAppTrace, GT_INFO, " \r\n");

    return;
}

void BspUtils_appGetFileName(Char       *fileNameString,
                             UInt32      fileNameSize,
                             const Char *fileStr,
                             UInt32      dataFormat,
                             UInt32      width,
                             UInt32      height)
{
    Char *fmtName;

    if (FVID2_DF_YUV422I_YUYV == dataFormat)
    {
        fmtName = "yuyv422";
    }
    else if (FVID2_DF_YUV422I_YVYU == dataFormat)
    {
        fmtName = "yvyu422";
    }
    else if (FVID2_DF_YUV422I_UYVY == dataFormat)
    {
        fmtName = "uyvy422";
    }
    else if (FVID2_DF_YUV422I_VYUY == dataFormat)
    {
        fmtName = "vyuy422";
    }
    else if (FVID2_DF_YUV420SP_UV == dataFormat)
    {
        fmtName = "nv12";
    }
    else if (FVID2_DF_YUV420SP_VU == dataFormat)
    {
        fmtName = "nv21";
    }
    else if (FVID2_DF_YUV422SP_UV == dataFormat)
    {
        fmtName = "nv16";
    }
    else if (FVID2_DF_YUV422SP_VU == dataFormat)
    {
        fmtName = "yuv422spvu";
    }
    else if (FVID2_DF_YUV444I == dataFormat)
    {
        fmtName = "yuv444";
    }
    else if (FVID2_DF_RGB24_888 == dataFormat)
    {
        fmtName = "rgb888";
    }
    else if (FVID2_DF_BGR24_888 == dataFormat)
    {
        fmtName = "bgr888";
    }
    else if (FVID2_DF_RAW16 == dataFormat)
    {
        fmtName = "raw16";
    }
    else if (FVID2_DF_RAW08 == dataFormat)
    {
        fmtName = "raw8";
    }
    else if (FVID2_DF_ARGB32_8888 == dataFormat)
    {
        fmtName = "argb8888";
    }
    else if (FVID2_DF_ABGR32_8888 == dataFormat)
    {
        fmtName = "abgr8888";
    }
    else if (FVID2_DF_BGRA32_8888 == dataFormat)
    {
        fmtName = "bgra8888";
    }
    else if (FVID2_DF_XBGR24_8888 == dataFormat)
    {
        fmtName = "xbgr8888";
    }
    else if (FVID2_DF_BGRX24_8888 == dataFormat)
    {
        fmtName = "bgrx8888";
    }
    else if (FVID2_DF_BGR16_565_A8 == dataFormat)
    {
        fmtName = "bgr565a8";
    }
    else if (FVID2_DF_BGR16_565 == dataFormat)
    {
        fmtName = "bgr565";
    }
    else if (FVID2_DF_RGB16_565 == dataFormat)
    {
        fmtName = "rgb565";
    }
    else
    {
        fmtName = "unknownformat";
    }
    snprintf(fileNameString, fileNameSize,
             "%s_%s_prog_packed_%u_%u.tigf", fileStr, fmtName,
             (unsigned int) width, (unsigned int) height);
}

/*
 *  \brief Function to print the loadRaw command used to load buffers from file
 *  through CCS scripting console.
 *
 *  \param fileStr          [IN]    File name string.
 *  \param bufAddr          [IN]    Buffer address.
 *  \param dataFormat       [IN]    FVID2 Data format.
 *  \param width            [IN]    Width of buffer in pixels.
 *  \param height           [IN]    Height of buffer in lines.
 */
void BspUtils_appPrintLoadRawCmd(const Char *fileStr,
                                 const void *bufAddr,
                                 UInt32      dataFormat,
                                 UInt32      width,
                                 UInt32      height)
{
    char fileNameString[BSPUTILS_MAX_FILENAMESIZE];

    BspUtils_appGetFileName(fileNameString, BSPUTILS_MAX_FILENAMESIZE, fileStr,
                            dataFormat, width,
                            height);

    GT_2trace(
        BspAppTrace, GT_INFO,
        "loadRaw(0x%.8x, 0, \"C:\\\\%s\", 32, false);\r\n",
        bufAddr, fileNameString);

    return;
}

/**
 *  \brief Function to print the saveRaw command used to save buffers to file
 *  through CCS scripting console.
 */
void BspUtils_appPrintSaveRawCmd(const Char *fileStr,
                                 const void *bufAddr,
                                 UInt32      dataFormat,
                                 UInt32      width,
                                 UInt32      height,
                                 UInt32      bufSize)
{
    char fileNameString[BSPUTILS_MAX_FILENAMESIZE];
    BspUtils_appGetFileName(fileNameString, BSPUTILS_MAX_FILENAMESIZE, fileStr,
                            dataFormat, width,
                            height);

    GT_3trace(
        BspAppTrace, GT_INFO,
        "saveRaw(0, 0x%.8x, \"D:\\\\%s\", %d, "
        "32, false);\r\n",
        bufAddr, fileNameString, (bufSize / 4U));

    return;
}

void BspUtils_appLogTestResult(UInt32 testResult)
{
    HW_WR_REG32(BSPUTILS_APP_TST_ADDR, testResult);

    return;
}

UInt32 BspUtils_appGetCrc(const UInt8 *bufPtr, UInt32 numBytes)
{
    UInt32 crc32, bCnt;

    GT_assert(BspAppTrace, (NULL != bufPtr));

    crc32 = 0xFFFFFFFFU;
    for (bCnt = 0u; bCnt < numBytes; bCnt++)
    {
        crc32 = BspUtils_appCalcCrc32(*bufPtr, crc32);
        bufPtr++;
    }

    crc32 = ~crc32;

    return (crc32);
}

static inline UInt32 BspUtils_appCalcCrc32(UInt8 byte, UInt32 prevCrc32)
{
    UInt32 newCrc32, offset;

    offset   = byte ^ (prevCrc32 & 0x000000FFU);
    newCrc32 = (prevCrc32 >> 8U) ^ gCrc32Table[offset];

    return (newCrc32);
}

#if defined (VPS_VIP_BUILD) || defined (VPS_CAL_BUILD)

/**
 *  \brief Prints the capture instance status information by calling the
 *  driver get status IOCTL.
 */
void BspUtils_appPrintCaptStatus(Fvid2_Handle fvidHandle,
                                 UInt32       instId,
                                 UInt32       numStream,
                                 UInt32       numCh,
                                 UInt32       execTime)
{
    Int32                retVal;
    UInt32               streamId, chId;
    Vps_CaptStatus       captStat;
    Vps_CaptChStatusArgs chStatArgs;
    Vps_CaptChStatus     chStat;
    static Char          buf[300];

    retVal = Fvid2_control(
        fvidHandle,
        IOCTL_VPS_CAPT_GET_STATUS,
        &captStat,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Capture Inst Status: Error: Get capture status failed!!\r\n");
    }
    else
    {
        GT_1trace(BspAppTrace, GT_INFO,
                  " Capture Instance %d Statistics\r\n", instId);
        GT_0trace(BspAppTrace, GT_INFO,
                  " ==============================\r\n");
        GT_2trace(BspAppTrace, GT_INFO,
                  " Capture Inst %d Status: Number of request queued  : %d\r\n",
                  instId,
                  captStat.queueCount);
        GT_2trace(BspAppTrace, GT_INFO,
                  " Capture Inst %d Status: Number of request dequeued: %d\r\n",
                  instId,
                  captStat.dequeueCount);
        GT_2trace(BspAppTrace, GT_INFO,
                  " Capture Inst %d Status: Overflow Count            : %d\r\n",
                  instId,
                  captStat.overflowCount);
        GT_0trace(BspAppTrace, GT_INFO, " \r\n");

        GT_0trace(
            BspAppTrace, GT_INFO,
            "    CH    |     Q      DQ     Total   Top     Bot    Total  Top    "
            "Bot   Min/Max     Min/Max   Dropped  Repeat   Fid   Desc \r\n");
        GT_0trace(
            BspAppTrace, GT_INFO,
            " (I/S/CH) |   Count   Count  Fields  Fields  Fields   FPS   FPS    "
            "FPS    Width       Height   Frames   Frames  Repeat Error\r\n");
        GT_0trace(
            BspAppTrace, GT_INFO,
            " ------------------------------------------------------------------"
            "---------------------------------------------------------\r\n");

        VpsCaptChStatusArgs_init(&chStatArgs);
        for (streamId = 0U; streamId < numStream; streamId++)
        {
            for (chId = 0U; chId < numCh; chId++)
            {
                chStatArgs.chNum =
                    Vps_captMakeChNum(instId, streamId, chId);
                chStatArgs.frameInterval = 33;

                retVal = Fvid2_control(
                    fvidHandle,
                    IOCTL_VPS_CAPT_GET_CH_STATUS,
                    &chStatArgs,
                    &chStat);
                if (FVID2_SOK != retVal)
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Get channel status failed!!\r\n");
                    break;
                }
                else
                {
                    snprintf(buf, sizeof (buf),
                             " %02u.%u.%02u | %7u %7u %7u %7u %7u %6u %5u "
                             "%5u %5u/%-5u %5u/%-5u %7u %7u %7u %5u\r\n",
                             (unsigned int)instId,
                             (unsigned int)streamId,
                             (unsigned int)chId,
                             (unsigned int)chStat.queueCount,
                             (unsigned int)chStat.dequeueCount,
                             (unsigned int)chStat.captFrmCount,
                             (unsigned int)chStat.fldCount[FVID2_FID_TOP],
                             (unsigned int)chStat.fldCount[FVID2_FID_BOTTOM],
                             (unsigned int)(chStat.captFrmCount /
                                            (execTime / 1000U)),
                             (unsigned int)(chStat.fldCount[FVID2_FID_TOP] /
                                            (execTime / 1000U)),
                             (unsigned int)(chStat.fldCount[FVID2_FID_BOTTOM] /
                                            (execTime / 1000U)),
                             (unsigned int)chStat.minRecvFrmWidth,
                             (unsigned int)chStat.maxRecvFrmWidth,
                             (unsigned int)chStat.minRecvFrmHeight,
                             (unsigned int)chStat.maxRecvFrmHeight,
                             (unsigned int)chStat.droppedFrmCount,
                             (unsigned int)chStat.repeatFrmCount,
                             (unsigned int)chStat.fidRepeatCount,
                             (unsigned int)chStat.descErrCount);

                    GT_1trace(BspAppTrace, GT_INFO, " %s\r\n", buf);
                }
            }
            if (FVID2_SOK != retVal)
            {
                break;
            }
        }
    }
}

#endif

#ifdef VPS_VPE_BUILD
/**
 *  BspUtils_appAllocDeiCtxBuffer
 *  \brief Allocate context buffer according to the VPE driver need and
 *  provide it to the driver.
 */
Int32 BspUtils_appAllocDeiCtxBuffer(Fvid2_Handle fvidHandle, UInt32 numCh)
{
    Int32          retVal = FVID2_SOK;
    Vps_DeiCtxInfo deiCtxInfo;
    Vps_DeiCtxBuf  deiCtxBuf;
    UInt32         chCnt, bCnt;

    for (chCnt = 0U; chCnt < numCh; chCnt++)
    {
        /* Get the number of buffers to allocate */
        deiCtxInfo.chNum = chCnt;
        retVal           = Fvid2_control(
            fvidHandle,
            IOCTL_VPS_GET_DEI_CTX_INFO,
            &deiCtxInfo,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Error: Get DEI Context Info IOCTL failed!!\r\n");
        }
        /* Allocate the buffers as requested by the driver */
        if (FVID2_SOK == retVal)
        {
            for (bCnt = 0U; bCnt < deiCtxInfo.numFld; bCnt++)
            {
                deiCtxBuf.fldBuf[bCnt] = (void *) BspUtils_memAlloc(
                    deiCtxInfo.fldBufSize,
                    (UInt32) VPS_BUFFER_ALIGNMENT_RECOMMENDED);
                if (NULL == deiCtxBuf.fldBuf[bCnt])
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Error: Mem alloc failed!!\r\n");
                    retVal = FVID2_EALLOC;
                }
            }
        }
        if (FVID2_SOK == retVal)
        {
            for (bCnt = 0U; bCnt < deiCtxInfo.numMv; bCnt++)
            {
                deiCtxBuf.mvBuf[bCnt] = (void *) BspUtils_memAlloc(
                    deiCtxInfo.mvBufSize,
                    (UInt32) VPS_BUFFER_ALIGNMENT_RECOMMENDED);
                if (NULL == deiCtxBuf.mvBuf[bCnt])
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Error: Mem alloc failed!!\r\n");
                    retVal = FVID2_EALLOC;
                }
            }
        }
        if (FVID2_SOK == retVal)
        {
            for (bCnt = 0U; bCnt < deiCtxInfo.numMvstm; bCnt++)
            {
                deiCtxBuf.mvstmBuf[bCnt] = (void *) BspUtils_memAlloc(
                    deiCtxInfo.mvstmBufSize,
                    (UInt32) VPS_BUFFER_ALIGNMENT_RECOMMENDED);
                if (NULL == deiCtxBuf.mvstmBuf[bCnt])
                {
                    GT_0trace(BspAppTrace, GT_ERR,
                              "Error: Mem alloc failed!!\r\n");
                    retVal = FVID2_EALLOC;
                }
            }
        }
        if (FVID2_SOK == retVal)
        {
            /* Provided the allocated buffer to driver */
            deiCtxBuf.chNum = chCnt;
            retVal          = Fvid2_control(
                fvidHandle,
                IOCTL_VPS_SET_DEI_CTX_BUF,
                &deiCtxBuf,
                NULL);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Error: Set DEI Context Buffer IOCTL failed!!\r\n");
            }
        }
        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    return (retVal);
}

/**
 *  BspUtils_appFreeDeiCtxBuffer
 *  \brief Get the context buffers back from the VPE driver and free them.
 */
Int32 BspUtils_appFreeDeiCtxBuffer(Fvid2_Handle fvidHandle, UInt32 numCh)
{
    Int32          retVal = FVID2_SOK;
    Vps_DeiCtxInfo deiCtxInfo;
    Vps_DeiCtxBuf  deiCtxBuf;
    UInt32         chCnt, bCnt;

    for (chCnt = 0U; chCnt < numCh; chCnt++)
    {
        /* Get the number of buffers to allocate */
        deiCtxInfo.chNum = chCnt;
        retVal           = Fvid2_control(
            fvidHandle,
            IOCTL_VPS_GET_DEI_CTX_INFO,
            &deiCtxInfo,
            NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Error: Get DEI Context Info IOCTL failed!!\r\n");
        }
        else
        {
            /* Get the allocated buffer back from the driver */
            deiCtxBuf.chNum = chCnt;
            retVal          = Fvid2_control(
                fvidHandle,
                IOCTL_VPS_GET_DEI_CTX_BUF,
                &deiCtxBuf,
                NULL);

            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Error: Get DEI Context Buffer IOCTL failed!!\r\n");
            }
            else
            {
                /* Free the buffers */
                for (bCnt = 0U; bCnt < deiCtxInfo.numFld; bCnt++)
                {
                    BspUtils_memFree(deiCtxBuf.fldBuf[bCnt],
                                     deiCtxInfo.fldBufSize);
                }
                for (bCnt = 0U; bCnt < deiCtxInfo.numMv; bCnt++)
                {
                    BspUtils_memFree(deiCtxBuf.mvBuf[bCnt],
                                     deiCtxInfo.mvBufSize);
                }
                for (bCnt = 0U; bCnt < deiCtxInfo.numMvstm; bCnt++)
                {
                    BspUtils_memFree(deiCtxBuf.mvstmBuf[bCnt],
                                     deiCtxInfo.mvstmBufSize);
                }
            }
        }
        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    return (retVal);
}

/**
 *  BspUtils_appPrintM2mVpeCreateStatus
 *  \brief Prints the M2M VPE driver create status information.
 */
void BspUtils_appPrintM2mVpeCreateStatus(
    const Vps_M2mCreateStatus *createStatus)
{
    GT_1trace(
        BspAppTrace, GT_INFO,
        "M2M VPE Create Status: Maximum Handles                  : %d\r\n",
        createStatus->maxHandles);
    GT_1trace(
        BspAppTrace, GT_INFO,
        "M2M VPE Create Status: Maximum Channels per Handle      : %d\r\n",
        createStatus->maxChPerHandle);
    GT_1trace(
        BspAppTrace, GT_INFO,
        "M2M VPE Create Status: Maximum same Channels per Request: %d\r\n",
        createStatus->maxSameChPerRequest);

    return;
}

/**
 *  BspUtils_appSetVpeLazyLoad
 *  \brief Sets the VPE lazy loading parameters through the VPS control driver.
 */
Int32 BspUtils_appSetVpeLazyLoad(UInt32 vpeInstId,
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
                  "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
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
                      "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        }
    }

    if (NULL != fvidHandle)
    {
        retVal = Fvid2_delete(fvidHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_2trace(BspAppTrace, GT_ERR,
                      "%s: Error @ line %d\r\n", __FUNCTION__, __LINE__);
        }
    }

    return (retVal);
}

#endif

#ifdef VPS_DSS_BUILD

/**
 *  \brief Prints the display instance status information by calling the
 *  driver get status IOCTL.
 *
 *  \param fvidHandle   [IN] Valid display driver handle.
 *  \param instId       [IN] Instance ID used for print.
 *  \param execTime     [IN] Execution time from display start to display
 *                           stop in msec.
 *
 */
void BspUtils_appPrintDispStatus(Fvid2_Handle fvidHandle,
                                 UInt32       instId,
                                 UInt32       execTime)
{
    Int32          retVal;
    Vps_DispStatus dispStat;

    retVal = Fvid2_control(
        fvidHandle,
        IOCTL_VPS_DISP_GET_STATUS,
        &dispStat,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspAppTrace, GT_ERR,
                  "Display Inst Status: Error: Get display status failed!!\r\n");
    }
    else
    {
        GT_1trace(BspAppTrace, GT_INFO,
                  " Display Instance %d Statistics\r\n", instId);
        GT_0trace(BspAppTrace, GT_INFO,
                  " ==============================\r\n");
        GT_2trace(BspAppTrace, GT_INFO,
                  " Display Inst %d Status: Number of request queued  : %d\r\n",
                  instId,
                  dispStat.queueCount);
        GT_2trace(BspAppTrace, GT_INFO,
                  " Display Inst %d Status: Number of request dequeued: %d\r\n",
                  instId,
                  dispStat.dequeueCount);
        GT_2trace(BspAppTrace, GT_INFO,
                  " Display Inst %d Status: Displayed frame count     : %d\r\n",
                  instId,
                  dispStat.dispFrmCount);
        GT_2trace(BspAppTrace, GT_INFO,
                  " Display Inst %d Status: Frame repeat count        : %d\r\n",
                  instId,
                  dispStat.repeatFrmCount);
        GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    }
    return;
}

void BspUtils_appPrintDctrlStatus(Fvid2_Handle fvidHandle)
{
    Int32 retVal;
    Vps_DctrlErrorSyncLostStats dctrlStat;

    retVal = Fvid2_control(
        fvidHandle,
        IOCTL_VPS_DCTRL_GET_ERROR_STATS,
        &dctrlStat,
        NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(
            BspAppTrace, GT_ERR,
            "Display Ctrl Error Status: Error: Get display control status failed!!\r\n");
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO,
                  " Dispaly Controller Error Status \r\n");
        GT_0trace(BspAppTrace, GT_INFO,
                  " ==============================\r\n");
        GT_1trace(BspAppTrace, GT_INFO,
                  " LCD1 SyncLost count          : %d\r\n",
                  dctrlStat.syncLost1);
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
        GT_1trace(BspAppTrace, GT_INFO,
                  " LCD2 SyncLost2 count         : %d\r\n",
                  dctrlStat.syncLost2);
        GT_1trace(BspAppTrace, GT_INFO,
                  " LCD3 SyncLost3 count         : %d\r\n",
                  dctrlStat.syncLost3);
        GT_1trace(BspAppTrace, GT_INFO,
                  " TV SyncLost count            : %d\r\n",
                  dctrlStat.syncLostTV);
#endif
        GT_1trace(BspAppTrace, GT_INFO,
                  " OCP Error count              : %d\r\n",
                  dctrlStat.ocpError);
        GT_0trace(BspAppTrace, GT_INFO, " \r\n");
    }
}

/**
 *  \brief Prints the display driver create status information.
 *
 *  \param createStatus [IN] Pointer to display driver create status.
 */
void BspUtils_appPrintDispCreateStatus(const Vps_DispCreateStatus *createStatus)
{
    GT_3trace(
        BspAppTrace, GT_INFO,
        "Display Create Status: VENC Standard: %s, Width: %d, Height: %d\r\n",
        Fvid2_getStandardString(createStatus->standard),
        createStatus->dispWidth, createStatus->dispHeight);
    GT_1trace(
        BspAppTrace, GT_INFO,
        "Display Create Status: Minimum Number of Buffers to Prime: %d\r\n",
        createStatus->minNumPrimeBuf);

    return;
}

#endif

void BspUtils_appServiceWatchdog(void)
{
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    /*trigger reload*/
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x1010);
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x0101);
#elif defined (SOC_TDA3XX)
    if (TRUE == RTIDwwdIsCounterEnabled(SOC_RTI4_BASE))
    {
        /* wait for RTI to be in open window. When running from SBL automation,
         * This returns immediately as we are configuring for 100% window. */
        while (RTIDwwdIsClosedWindow(SOC_RTI4_BASE))
        {}
        RTIDwwdService(SOC_RTI4_BASE);
    }
#endif
    return;
}

void * BspUtils_appGetEdmaHandle(void)
{
#if !defined (VPS_TI_RTOS_MMCSD)
    return (void *) gBspUtilsAppObj.hEdma;
#else
    return NULL;
#endif
}
