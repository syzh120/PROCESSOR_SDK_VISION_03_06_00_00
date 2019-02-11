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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_vipSingleRvcCamCrc_Display_priv.h"
#include <src/include/chains_common.h>
#include <src/rtos/alg_plugins/rvcDiags/rvcDiagnostic_algLink_priv.h>
#include <src/rtos/alg_plugins/swcrc/swCrc_algLink_priv.h>

#ifdef GPIO_IN_INTERRUPT
#include <ti/csl/csl_gpio.h>
#include <ti/csl/cslr_dss.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>
#endif

#define VID2_POSX        (280)
#define VID2_POSY        (45)
#define VID3_POSX        (280)
#define VID3_POSY        (10)

#define CAPTURE_SENSOR_INPUT_WIDTH      (720)
#define CAPTURE_SENSOR_INPUT_HEIGHT     (480)

#define CAPTURE_SENSOR_OUTPUT_WIDTH      (720)
#define CAPTURE_SENSOR_OUTPUT_HEIGHT     (480)

#define CAPTURE_DISPLAY_WIDTH      (720)
#define CAPTURE_DISPLAY_HEIGHT     (480)

#define AUTOMATIC_UPDATE_COUNTER (5)

//#define PRINT_STATISTICS

/* Display writes two pixels extra for the interlaced modes, so
 * DSS write back should allocate memory for extra two pixels.
 * This macro is used for providing extra pixels to the display write back path
 * And also for configuring CRC modules ROI correctly.
 */
#define DISPLAY_WB_EXTRA_PIXELS             (2U)

#ifdef GPIO_IN_INTERRUPT
#ifdef TDA2EX_BUILD
/* GPIO INPUT INTERRUPT by default is configured using GPIO 6 pin 28
 * which is connected to CTRL_CORE_PAD_MMC1_SDWP
 * MUXMODE 14 (0xE) - gpio6_28
 * The Interrupt is GPIO6_IRQ_2 with IRQ_CROSSBAR_143.
 * The Control Module used CTRL_CORE_IPU2_IRQ_49_50.
 * IPU2_IRQ_49 is set to IRQ_CROSSBAR_143 (0x8F)
 */
#define GPIO_PIN_MASK_ALL (0xFFFFFFFFU)
#define PINMUX_MODE_14 ((UInt32) 14U)
#define SOC_CTRL_CORE_IPU2_IRQ_49_50 (0x4A002888)
#define IRQ_CROSSBAR_143 (0x8F)
#define SOC_CTRL_CORE_IPU2_IRQ_49_50_MASK_LSB (0xFFFF0000)
#define SOC_CTRL_CORE_IPU2_IRQ_49_50_MASK_MSB (0x0000FFFF)

uint32_t gpio_in_base_address = SOC_GPIO6_BASE;
uint32_t gpio_in_pin          = 28;
uint32_t rvc_int_num          = 49;

/* In TDA2EX schematic GPMC_D08 is connected to GPMC_AD8
 * which is on SW4 pin#1.
 * At boot, SW4 pin#1 DIP SWITCH is set to 1 means RVC run
 *
 * In TDA2EX schematic TP29 is connected to MMC1_SDWP (gpio6_28)
 * At boot, TP29 needs to be set to 1 for RVC run
 */
static uint32_t gpio_value = 1;

#else
/* GPIO INPUT INTERRUPT by default is configured using GPIO 7 pin 18
  * which is connected to CTRL_CORE_PAD_GPMC_AD8
  * MUXMODE 14 (0xE) - gpio7_18
  * The Interrupt is GPIO7_IRQ_2 with IRQ_CROSSBAR_347.
  * The Control Module used CTRL_CORE_IPU2_IRQ_49_50.
  * IPU2_IRQ_49 is set to IRQ_CROSSBAR_347 (0x15B)
  */
#define GPIO_PIN_MASK_ALL (0xFFFFFFFFU)
#define PINMUX_MODE_14 ((UInt32) 14U)
#define SOC_CTRL_CORE_IPU2_IRQ_49_50 (0x4A002888)
#define IRQ_CROSSBAR_347 (0x15B)
#define SOC_CTRL_CORE_IPU2_IRQ_49_50_MASK_LSB (0xFFFF0000)
#define SOC_CTRL_CORE_IPU2_IRQ_49_50_MASK_MSB (0x0000FFFF)

uint32_t gpio_in_base_address = SOC_GPIO7_BASE;
uint32_t gpio_in_pin          = 18;
uint32_t rvc_int_num          = 49;

/* In TDA2XX schematic GPMC_D08 is connected to GPMC_AD8
 * which is on SW3 pin#1
 * At boot, SW3 pin#1 DIP SWITCH is set to 1 means RVC run
 */
static uint32_t gpio_value = 1;
#endif
#endif

/**
 *******************************************************************************
 *
 *  \brief  Use-case object
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_vipSingleRvcCamCrc_DisplayObj ucObj;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;

    AlgorithmLink_SwCrcSig_Obj prevSig[SWCRC_PREV_OBJ_MAX];
    UInt32  prevSigIndex;
    UInt32  isFrameFreezeDetected;

    Bool rvc_run;

} Chains_vipSingleRvcCamCrcCameraViewAppObj;

/**
 *******************************************************************************
 *
 * \brief   Set Vpe Create Parameters
 *
 * \param   pPrm         [IN]  CaptureLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_vipSingleRvcCamCrc_Display_SetVpePrms(
                                                VpeLink_CreateParams *pPrm,
                                                UInt32 displayWidth,
                                                UInt32 displayHeight)
{
    UInt32 outId, chId;
    VpeLink_ChannelParams *chPrms;

    memset(pPrm, 0, sizeof(*pPrm));

    pPrm->enableOut[VPE_LINK_OUT_QUE_ID_0] = TRUE;
    pPrm->enableOut[VPE_LINK_OUT_QUE_ID_1] = FALSE;

    for(outId=0; outId<VPE_LINK_OUT_QUE_ID_MAX; outId++)
    {
        for (chId = 0; chId < VPE_LINK_MAX_CH; chId++)
        {
            chPrms = &pPrm->chParams[chId];
            chPrms->outParams[outId].numBufsPerCh =
                                     10;//VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;
            chPrms->outParams[outId].inputFrameRate = 60;
            chPrms->outParams[outId].outputFrameRate = 60;

            chPrms->outParams[outId].width  = CAPTURE_SENSOR_OUTPUT_WIDTH;
            chPrms->outParams[outId].height = CAPTURE_SENSOR_OUTPUT_HEIGHT;
            chPrms->outParams[outId].dataFormat = SYSTEM_DF_YUV422P;

            chPrms->deiCfg.bypass = FALSE;

            chPrms->deiCfg.inpMode = VPE_DEI_EDIMODE_LUMA_CHROMA;
            chPrms->deiCfg.tempInpEnable = TRUE;
            chPrms->deiCfg.tempInpChromaEnable = TRUE;
            chPrms->deiCfg.spatMaxBypass = TRUE;
            chPrms->deiCfg.tempMaxBypass = TRUE;

            chPrms->scCfg.bypass       = TRUE;
            chPrms->scCfg.nonLinear    = FALSE;
            chPrms->scCfg.stripSize    = 0;

            chPrms->scCropCfg.cropStartX = 0;
            chPrms->scCropCfg.cropStartY = 0;
            chPrms->scCropCfg.cropWidth  = 0;
            chPrms->scCropCfg.cropHeight = 0;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set link Parameters of ALG CRC link
 *
 *******************************************************************************
*/
static Void chains_vipSingleRvcCamCrc_Display_SetcrcAlgPrms(
                                Chains_vipSingleRvcCamCrcCameraViewAppObj *pObj,
                                AlgorithmLink_SwCrcCreateParams *pPrm,
                                UInt32 displayWidth,
                                UInt32 displayHeight,
                                Chains_DisplayType displayType)
{
    Int32 i;

    pPrm->startX    = 0;
    pPrm->startY    = 0;
    pPrm->roiWidth  = displayWidth;
    pPrm->roiHeight = displayHeight;

    pObj->prevSigIndex          = 0;
    pObj->isFrameFreezeDetected = FALSE;
    for (i=0; i<SWCRC_PREV_OBJ_MAX; i++)
    {
        pObj->prevSig[i].swCrcVal_L = i;
        pObj->prevSig[i].swCrcVal_H = i;
    }

    pPrm->appData = pObj;
}


/**
 *******************************************************************************
 *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_vipSingleRvcCamCrc_Display_SetAppPrms(chains_vipSingleRvcCamCrc_DisplayObj *pUcObj, Void *appObj)
{
    Chains_vipSingleRvcCamCrcCameraViewAppObj *pObj
        = (Chains_vipSingleRvcCamCrcCameraViewAppObj*)appObj;

    pObj->captureOutWidth  = CAPTURE_SENSOR_OUTPUT_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_OUTPUT_HEIGHT;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    ChainsCommon_SingleCam_SetCapturePrms(&pUcObj->CapturePrm,
            CAPTURE_SENSOR_INPUT_WIDTH,
            CAPTURE_SENSOR_INPUT_HEIGHT,
            pObj->captureOutWidth,
            pObj->captureOutHeight,
            pObj->chainsCfg->captureSrc
            );

    pUcObj->CapturePrm.vipInst[0].numBufs = 5;

    /*
     * This code snippet shows an example of allocating memory for
     * a link from within the use-case instead of from within the link
     *
     * This allows user's to potentially allocate memory statically outside of
     * link implementation and then pass the memory to the link during use-case
     * create.
     *
     * If user wants the link to allocate memory then dont set below parameters
     * <link create params>.memAllocInfo.memSize,
     * <link create params>.memAllocInfo.memAddr
     */
    /* memory for YUV420SP buffer's */
    pUcObj->CapturePrm.memAllocInfo.memSize =
       (   CAPTURE_SENSOR_OUTPUT_WIDTH
        * CAPTURE_SENSOR_OUTPUT_HEIGHT
        * pUcObj->CapturePrm.vipInst[0].numBufs
        * 3 ) / 2 ;

    pUcObj->CapturePrm.memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pUcObj->CapturePrm.memAllocInfo.memSize,
                128
            );
    UTILS_assert(pUcObj->CapturePrm.memAllocInfo.memAddr!=NULL);

    chains_vipSingleRvcCamCrc_Display_SetVpePrms(&pUcObj->VPE_deiPrm,
                                           pObj->displayWidth,
                                           pObj->displayHeight
                                          );

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                               pObj->displayWidth,
                                               pObj->displayHeight
                                              );

    pUcObj->GrpxSrcPrm.logoDisplayEnable = FALSE;
    pUcObj->GrpxSrcPrm.logoParams.startX = 200;
    pUcObj->GrpxSrcPrm.logoParams.startY = 335;
    pUcObj->GrpxSrcPrm.statsDisplayEnable = FALSE;
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGRA16_4444;

    ChainsCommon_SetDisplayPrms(&pUcObj->Display_VideoPrm,
                                &pUcObj->Display_GrpxPrm,
                                pObj->chainsCfg->displayType,
                                CAPTURE_DISPLAY_WIDTH,
                                CAPTURE_DISPLAY_HEIGHT
                               );

    pUcObj->Display_VideoPrm.rtParams.posX = VID3_POSX;
    pUcObj->Display_VideoPrm.rtParams.posY = VID3_POSY;
    pUcObj->Display_VideoPrm.displayId     = DISPLAY_LINK_INST_DSS_VID3;
    pUcObj->Display_GrpxPrm.rtParams.tarWidth  = CAPTURE_DISPLAY_WIDTH;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = CAPTURE_DISPLAY_HEIGHT;
    pUcObj->Display_GrpxPrm.rtParams.posX      = VID2_POSX;
    pUcObj->Display_GrpxPrm.rtParams.posY      = VID2_POSY;
    pUcObj->Display_GrpxPrm.displayId          = DISPLAY_LINK_INST_DSS_VID2;

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight
        );

    chains_vipSingleRvcCamCrc_Display_SetcrcAlgPrms(
        pObj,
        &pUcObj->Alg_SwCrcPrm,
        CAPTURE_DISPLAY_WIDTH,
        CAPTURE_DISPLAY_HEIGHT,
        pObj->chainsCfg->displayType);

    // Create parameter for RVC Diagnostics Alg Plugin
    pUcObj->Alg_RvcDiagnosticPrm.appData = pObj;
    pUcObj->Alg_RvcDiagnosticPrm.autoCorrectFlag = TRUE;
    pUcObj->Alg_RvcDiagnosticPrm.autoCorrectCount = AUTOMATIC_UPDATE_COUNTER;
}

/**
 *******************************************************************************
 *
 * \brief   Start the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_vipSingleRvcCamCrcCameraViewAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_vipSingleRvcCamCrc_Display_StartApp(Chains_vipSingleRvcCamCrcCameraViewAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_StartCaptureDevice(
        pObj->chainsCfg->captureSrc,
        pObj->captureOutWidth,
        pObj->captureOutHeight
        );

    /* For Robust RVC UC, since GrpxSrcLink_initAndDrawStaticBmp() is not
       calling Draw2D_clearBuf() saving about 760ms. ChainsCommon_StartDisplayDevice()
       needs to be called after ChainsCommon_StartCaptureDevice to allow some time
       for BSP to be ready. Or else Lcd_turnOn() will fail.
     */
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_vipSingleRvcCamCrc_Display_Start(&pObj->ucObj);
#ifdef PRINT_STATISTICS
    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
#else
    Chains_prfLoadCalcEnable(FALSE, FALSE, FALSE);
#endif
}


/**
 *******************************************************************************
 *
 * \brief   Delete the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   Chains_vipSingleRvcCamCrcCameraViewAppObj
 *
 *******************************************************************************
*/
Void chains_vipSingleRvcCamCrc_Display_StopAndDeleteApp(Chains_vipSingleRvcCamCrcCameraViewAppObj *pObj)
{
    chains_vipSingleRvcCamCrc_Display_Stop(&pObj->ucObj);
    chains_vipSingleRvcCamCrc_Display_Delete(&pObj->ucObj);

    if(pObj->ucObj.CapturePrm.memAllocInfo.memAddr)
    {
        Int32 status;

        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pObj->ucObj.CapturePrm.memAllocInfo.memAddr,
                    pObj->ucObj.CapturePrm.memAllocInfo.memSize);
        UTILS_assert(status==0);
    }

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopCaptureDevice(pObj->chainsCfg->captureSrc);
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, FALSE, FALSE);
}


Int32 RvcGPIO_setPinmuxRegs (UInt32 mode_index, UInt32 offset)
{
    UInt32 muxVal;

    if (offset != (UInt32) 0xffff)
    {
        muxVal  = HW_RD_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset);
        muxVal &= ~(0x0FU);
        muxVal |= (mode_index & 0x0000000FU);

        HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE + offset, muxVal);
    }

    return (0);
}

void RvcCtrlModule_Config(UInt32 base, UInt32 irq_crossbar, UInt32 mask)
{
    UInt32 muxVal = HW_RD_REG32(base);
    muxVal &= mask;
    muxVal |= irq_crossbar;
    HW_WR_REG32(base, muxVal);
}

void chains_vipSingleRvcCamCrc_Resume(Chains_vipSingleRvcCamCrcCameraViewAppObj *pObj)
{
    unsigned int reg_value;

    System_linkStart(pObj->ucObj.Dup_captureLinkID);
    System_linkStart(pObj->ucObj.CaptureLinkID);

    // Enable VID2 (enable DISPC_VID2_ATTRIBUTES bit 0)
    reg_value = HW_RD_FIELD32_RAW(SOC_DISPC_BASE + DSS_DISPC_VID2_ATTRIBUTES, DSS_DISPC_VID2_ATTRIBUTES_ENABLE_MASK,
        DSS_DISPC_VID2_ATTRIBUTES_ENABLE_SHIFT);
    if (reg_value == DSS_DISPC_VID2_ATTRIBUTES_ENABLE_VIDEODIS)
    {
        HW_WR_FIELD32_RAW(SOC_DISPC_BASE + DSS_DISPC_VID2_ATTRIBUTES, DSS_DISPC_VID2_ATTRIBUTES_ENABLE_MASK,
            DSS_DISPC_VID2_ATTRIBUTES_ENABLE_SHIFT, DSS_DISPC_VID2_ATTRIBUTES_ENABLE_VIDEOENB);
    }
    // Enable VID3 (enable DISPC_VID3_ATTRIBUTES bit 0)
    reg_value = HW_RD_FIELD32_RAW(SOC_DISPC_BASE + DSS_DISPC_VID3_ATTRIBUTES, DSS_DISPC_VID3_ATTRIBUTES_ENABLE_MASK,
        DSS_DISPC_VID3_ATTRIBUTES_ENABLE_SHIFT);
    if (reg_value == DSS_DISPC_VID3_ATTRIBUTES_ENABLE_VIDEODIS)
    {
        HW_WR_FIELD32_RAW(SOC_DISPC_BASE + DSS_DISPC_VID3_ATTRIBUTES, DSS_DISPC_VID3_ATTRIBUTES_ENABLE_MASK,
            DSS_DISPC_VID3_ATTRIBUTES_ENABLE_SHIFT, DSS_DISPC_VID3_ATTRIBUTES_ENABLE_VIDEOENB);
    }

    // Set DISPC_CONTROL1 (GOLCD bit 5)
    HW_WR_FIELD32_RAW(SOC_DISPC_BASE + DSS_DISPC_CONTROL1, DSS_DISPC_CONTROL1_GOLCD_MASK,
        DSS_DISPC_CONTROL1_GOLCD_SHIFT, DSS_DISPC_CONTROL1_GOLCD_UFPSR);
}

void chains_vipSingleRvcCamCrc_Stop(Chains_vipSingleRvcCamCrcCameraViewAppObj *pObj)
{
    unsigned int reg_value;

    System_linkStop(pObj->ucObj.CaptureLinkID);
    System_linkStop(pObj->ucObj.Dup_captureLinkID);

    // Disable VID2 (disable DISPC_VID2_ATTRIBUTES bit 0)
    reg_value = HW_RD_FIELD32_RAW(SOC_DISPC_BASE + DSS_DISPC_VID2_ATTRIBUTES, DSS_DISPC_VID2_ATTRIBUTES_ENABLE_MASK,
        DSS_DISPC_VID2_ATTRIBUTES_ENABLE_SHIFT);
    if (reg_value == DSS_DISPC_VID2_ATTRIBUTES_ENABLE_VIDEOENB)
    {
        HW_WR_FIELD32_RAW(SOC_DISPC_BASE + DSS_DISPC_VID2_ATTRIBUTES, DSS_DISPC_VID2_ATTRIBUTES_ENABLE_MASK,
            DSS_DISPC_VID2_ATTRIBUTES_ENABLE_SHIFT, DSS_DISPC_VID2_ATTRIBUTES_ENABLE_VIDEODIS);
    }
    // Disable VID3 (disable DISPC_VID3_ATTRIBUTES bit 0)
    reg_value = HW_RD_FIELD32_RAW(SOC_DISPC_BASE + DSS_DISPC_VID3_ATTRIBUTES, DSS_DISPC_VID3_ATTRIBUTES_ENABLE_MASK,
        DSS_DISPC_VID3_ATTRIBUTES_ENABLE_SHIFT);
    if (reg_value == DSS_DISPC_VID3_ATTRIBUTES_ENABLE_VIDEOENB)
    {
        HW_WR_FIELD32_RAW(SOC_DISPC_BASE + DSS_DISPC_VID3_ATTRIBUTES, DSS_DISPC_VID3_ATTRIBUTES_ENABLE_MASK,
            DSS_DISPC_VID3_ATTRIBUTES_ENABLE_SHIFT, DSS_DISPC_VID3_ATTRIBUTES_ENABLE_VIDEODIS);
    }
}

#ifdef GPIO_IN_INTERRUPT
void gpioInIsr(void *arg)
{
    uint32_t key;
    volatile uint32_t gpio_pin_status = 0;
    //Chains_vipSingleRvcCamCrcCameraViewAppObj* pObj = arg;

    key = Hwi_disable();

    /* GPIO_IRQSTATUS_x  */
    gpio_pin_status = GPIOPinIntStatus(gpio_in_base_address, GPIO_INT_LINE_2, gpio_in_pin);

    /* Set global gpio_value with the information from GPIO_DATAIN on the configured GPIO and pin */
    gpio_value = (GPIOPinRead(gpio_in_base_address, gpio_in_pin)) >> gpio_in_pin;

    Hwi_restore(key);

    /* Clear the bit on the configured GPIO and pin ONLY. */
    GPIOPinIntClear(gpio_in_base_address, GPIO_INT_LINE_2, gpio_in_pin);
}

void ConfigureGPIOInterrupt(Chains_vipSingleRvcCamCrcCameraViewAppObj *pObj)
{
    Hwi_Params hwiAttrs;
    uint32_t key;

    key = Hwi_disable();

    Hwi_Params_init(&hwiAttrs);
    hwiAttrs.maskSetting = Hwi_MaskingOption_LOWER;
    hwiAttrs.arg = (UArg) pObj;

    Hwi_create(rvc_int_num, (Hwi_FuncPtr) gpioInIsr, &hwiAttrs, NULL);
    Hwi_enableInterrupt(rvc_int_num);

    Hwi_restore(key);
}


/**
 *******************************************************************************
 *
 * \brief   Function to handle input value on GPIO pin when interrupt is triggered.
 *            The GPIO input will toggle the RVC to be displayed or hidden.
 *
 *******************************************************************************
*/
void Utils_gpioInEnable(uint32_t baseAdd, uint32_t pinNumber)
{
    /* Configure the pinmux for the particular GPIO7 pin18.
     *   CTRL_CORE_PAD_GPMC_AD8 (0x4A003420 - bit 3:0 should be mux to
     *   0xE: gpio7_18
     *   PAD=gpmc_ad8, PIN=gpio7_18 (pinmux_mode value of 0xE)
     *   PINMUX_MODE_14 is 0xE (14 to point to gpio7_18)
     */
    RvcGPIO_setPinmuxRegs(PINMUX_MODE_14, (UInt32) CTRL_CORE_PAD_GPMC_AD8);

    /*
     * GPIO Table 27-4 GPIO Hardware Request shows module GPIO7
     * source signal name "GPIO7_IRQ_2"
     * destination IRQ_CROSSBAR_Input of IRQ_CROSSBAR_347 (0x15B)
     * Since no default mapping interrupt to IPU.
     * In Table 17-9 Connection of Device IRQs to IRQ_CROSSBAR Inputs, we find
     *     IRQ_CROSSBAR Input: IRQ_CROSSBAR_347
     *     Interrupt Name: GPIO7_IRQ_2
     *     Interrupt Source: GPIO7
     * Description: GPIO7 Interrupt 2
     * Next is finding Table 18-28 CTRL_MODULE_CORE Registers Mapping Summary
     * or Table 17-6 IPU2_Cx_INTC Default interrupt Mapping.
     * for available IPU2_IRQ_x that points to IRQ_CROSSBAR_x which is Reserved
     * (available).
     * IPU2_IRQ_49 (27) - CTRL_CORE_IPU2_IRQ_49_50 can be remapped.
     *
     * CTRL_CORE_IPU2_IRQ_49_50 (0x4A002888) - bit 8:0 by default pointed to
     *     0x42 (66).
     * Set the IPU2_IRQ_49 Input Line of CTRL_CORE_IPU2_IRQ_49_50 (0x4A002888)
     * bit 8:0 to IRQ_CROSSBAR_347 (0x15B) for GPIO7_IRQ_2
     */
#ifdef TDA2EX_BUILD
    RvcCtrlModule_Config(SOC_CTRL_CORE_IPU2_IRQ_49_50, IRQ_CROSSBAR_143, SOC_CTRL_CORE_IPU2_IRQ_49_50_MASK_LSB);
#else
    RvcCtrlModule_Config(SOC_CTRL_CORE_IPU2_IRQ_49_50, IRQ_CROSSBAR_347, SOC_CTRL_CORE_IPU2_IRQ_49_50_MASK_LSB);
#endif

    /* Reset GPIO Module
     */
    GPIOModuleReset(baseAdd);

    /* Enable GPIO Module
     */
    GPIOModuleEnable(baseAdd);

    /* Set GPIO_INT_TYPE_BOTH_EDGE on  GPIO7 pin 18 */
    GPIOIntTypeSet(baseAdd, pinNumber, GPIO_INT_TYPE_BOTH_EDGE);;

    /* Set direction GPIO Module - INPUT DIRECTION
     */
    GPIODirModeSet(baseAdd, pinNumber, GPIO_DIR_INPUT);

    /*Clear interrupt*/
    GPIOPinIntDisable(baseAdd, GPIO_INT_LINE_2, pinNumber);
    GPIOPinIntClear(baseAdd, GPIO_INT_LINE_2, pinNumber);

    /*Enable interrupt*/
    GPIOPinIntEnable(baseAdd, GPIO_INT_LINE_2, pinNumber);

}
#endif

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase function
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
void chains_vipSingleRvcCamCrc_Display(Chains_Ctrl *chainsCfg)
{
    Chains_vipSingleRvcCamCrcCameraViewAppObj chainsObj;
    volatile Int32 loop = 1;
#ifdef PRINT_STATISTICS
    volatile unsigned long counter = 0;
#endif

    chainsObj.chainsCfg = chainsCfg;
    chains_vipSingleRvcCamCrc_Display_Create(&chainsObj.ucObj, &chainsObj);
    chains_vipSingleRvcCamCrc_Display_StartApp(&chainsObj);

    Vps_printf("CALLING Board_deInit\n");
    Board_deInit();

#ifdef GPIO_IN_INTERRUPT
    chainsObj.rvc_run = TRUE;

    /* Configure GPIO Interrupt */
    ConfigureGPIOInterrupt(&chainsObj);

    /* Enabling GPIO */
    Utils_gpioInEnable(gpio_in_base_address, gpio_in_pin);
#endif

    while (loop) {
#ifdef GPIO_IN_INTERRUPT
        if (gpio_value && !chainsObj.rvc_run)
        {
            Vps_printf("chains_vipSingleRvcCamCrc_Display Resume gpio %d rvc_run %d\n", gpio_value, chainsObj.rvc_run);
            chains_vipSingleRvcCamCrc_Resume(&chainsObj);
            chainsObj.rvc_run = TRUE;
        } else {
            if (!gpio_value && chainsObj.rvc_run )
            {
                Vps_printf("chains_vipSingleRvcCamCrc_Display Stop gpio %d rvc_run %d\n", gpio_value, chainsObj.rvc_run);
                chains_vipSingleRvcCamCrc_Stop(&chainsObj);
                chainsObj.rvc_run = FALSE;
            }
        }
#endif
        Task_sleep(500); // 500 of system clock ticks to sleep

#ifdef PRINT_STATISTICS
               if(!(counter%10)){
                      ChainsCommon_PrintStatistics();
                      chains_vipSingleRvcCamCrc_Display_printStatistics(&chainsObj.ucObj);
                      counter = 0;
                }
                counter++;
#endif
    }
}
