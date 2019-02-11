/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 *  \file iem_evtmngr.h
 *
 *  \brief ISS Event Manager
 *  This file exposes the HAL APIs for ISS ISIF module
 *
 */

#ifndef VPS_ISS_EVENT_MNGR_H_
#define VPS_ISS_EVENT_MNGR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Event Manager maximum number of instances for any given platform -
 *  used for memory allocation.
 */
#define IEM_MAX_INST                    (6U)

/**
 *  \brief Event manager instance ID.
 */
typedef enum issemInstId
{
    IEM_INST_ID_IRQ0 = 0x0,
    /**< Interrupt 0 */
    IEM_INST_ID_IRQ1,
    /**< ISS Interrupt 1 */
    IEM_INST_ID_IRQ2,
    /**< ISS Interrupt 2 */
    IEM_INST_ID_IRQ3,
    /**< ISS Interrupt 3 */
    IEM_INST_ID_IRQ4,
    /**< ISS Interrupt 4 */
    IEM_INST_ID_IRQ5,
    /**< ISS Interrupt 5 */
    IEM_INST_ID_MAX,
    /**< Max - used for error check. */
    IEM_INST_ID_FORCE_INT
    /**< This will ensure enum is not packed, will
     *always be contained in int */
} issemInstId_t;

/**
 *  \brief All ISS Events are logically grouped under one of the following
 *          categories.
 */
typedef enum issemEventGroup
{
    IEM_EG_ISP0 = 0,
    /**< Event Group for ISP0 */
    IEM_EG_ISP1 = 1,
    /**< Event Group for ISP1 */
    IEM_EG_ISP2 = 2,
    /**< Event Group for ISP2 */
    IEM_EG_ISP3 = 3,
    /**< Event Group for ISP3 */
    IEM_EG_CCP0 = 6,
    /**< Event Group for CCP0 */
    IEM_EG_CCP1 = 7,
    /**< Event Group for CCP1 */
    IEM_EG_CCP2 = 8,
    /**< Event Group for CCP2 */
    IEM_EG_CCP3 = 9,
    /**< Event Group for CCP3 */
    IEM_EG_CBUFF = 10,
    /**< CBUFF Events */
    IEM_EG_BTE = 11,
    /**< BTE Events */
    IEM_EG_SIMCOP0 = 12,
    /**< Event Group for SIMCOP0 */
    IEM_EG_SIMCOP1 = 13,
    /**< Event Group for SIMCOP1 */
    IEM_EG_SIMCOP2 = 14,
    /**< Event Group for SIMCOP2 */
    IEM_EG_SIMCOP3 = 15,
    /**< Event Group for SIMCOP3 */
    IEM_EG_CCP8 = 16,
    /**< Event Group for CCP8 */
    IEM_EG_HS_VS = 17,
    /**< Event Group for HS_VS */
    IEM_EG_BYS_A = 18,
    /**< Event Group for BYS_A */
    IEM_EG_VMUX = 19,
    /**< Event Group for VMUX */
    IEM_EG_BYS_B = 20,
    /**< Event Group for BYS_B */
    IEM_EG_CAL_A = 22,
    /**< Event Group for CAL_A */
    IEM_EG_CAL_B = 23,
    /**< Event Group for CAL_B */
    IEM_EG_ICM_B = 24,
    /**< Event Group for ICM_B */
    IEM_EG_ICM_A = 25,
    /**< Event Group for ICM_A */
    IEM_EG_LVDSRX0 = 26,
    /**< Event Group for LVDSRX0 */
    IEM_EG_LVDSRX1 = 27,
    /**< Event Group for LVDSRX1 */
    IEM_EG_LVDSRX2 = 28,
    /**< Event Group for LVDSRX2 */
    IEM_EG_LVDSRX3 = 29,
    /**< Event Group for LVDSRX3 */
    IEM_EG_RESERVED_30 = 30,
    /**< Reserved */
    IEM_EG_RESERVED_31 = 31,
    /**< Reserved */

    /* Events group below do not directly map to ISS top level event source bit
        positions. ISS_HL_XXX (XXX = IRQENABLE_SET/IRQENABLE_CLR/STATUS)
        Event Manager takes care of handling these separately. */

    IEM_EG_CAL_A_CSI2 = IEM_EG_RESERVED_31 + IEM_EG_CAL_A,
    /**< CSI2 specific events refer issemCalEvents_t for events supported
            in this group */
    IEM_EG_MAX = IEM_EG_CAL_A_CSI2 + 1,
    /**< Should be the last number */
    IEM_EG_FORCE_INT = 0x7FFFFFFF
                       /**< This will ensure enum is not packed, will always be
                        *contained in int */
} issemEventGroup_t;

/**
 *  \brief List of ISP Events.
 *         ISP Provides Four interrupts to the ISP, these are defined as
 *         event groups ISP0 to ISP3 in EventGroup enum
 *         these events  can be mapped to any one of these interrupt.
 *         This enum data type defines the event groups. This enum data
 *         type is type casted to unsigned int so it must not have any negative
 *         value
 */
typedef enum issemIspEvents
{
    IEM_ISP_EVENT_ISIF_VDINT0 = 0,
    /**< VD INT 0 */
    IEM_ISP_EVENT_ISIF_VDINT1 = 1,
    /**< VD INT 1 */
    IEM_ISP_EVENT_ISIF_VDINT2 = 2,
    /**< VD INT 2 */
    IEM_ISP_EVENT_ISIF_VDINT3 = 3,
    /**< VD INT 3, typically used for LSC */
    IEM_ISP_EVENT_IPIPE_INT = 4,
    /**< IPIPE End Interrupt */
    IEM_ISP_EVENT_IPIPE_INT_LAST_PIX = 5,
    /**< IPIPE Last Pixel end interrupt */
    IEM_ISP_EVENT_IPIPE_INT_DMA = 6,
    /**< IPIPE DMA end interrupt */
    IEM_ISP_EVENT_IPIPE_INT_BSC = 7,
    /**< BSC Interrupt */
    IEM_ISP_EVENT_IPIPE_INT_HST = 8,
    /**< Histogram interrupt */
    IEM_ISP_EVENT_IPIPEIF_INT = 9,
    /**< IPIPEIF interrupt */
    IEM_ISP_EVENT_AEW_INT = 10,
    /**< AEW interrupt */
    IEM_ISP_EVENT_AF_INT = 11,
    /**< AF interrupt */
    IEM_ISP_EVENT_H3A_INT = 12,
    /*< H3A End interrupt */
    IEM_ISP_EVENT_RSZ_INT = 13,
    /**< This event is triggered when the first pixel of the valid
     *   area is received */
    IEM_ISP_EVENT_RSZ_INT_LAST_PIX = 14,
    /**< This event is triggered when the last pixel of the valid
     *   area is received */
    IEM_ISP_EVENT_RSZ_INT_DMA = 15,
    /**< This event is triggered when the last eof (of the two MTC interfaces)
     *   is sent out to the BL and that the resizer core has returned to idle.
     *   rsz_int_dma is a true indication that all processing is
     *   finished for the particular frame on both resizer engines */
    IEM_ISP_EVENT_RSZ_INT_CYC_RSZA = 16,
    /**< An event can be triggered every time that RSZ_IRQ_RZA output
     *   lines have been written out to the RZA_SDR_Y buffer */
    IEM_ISP_EVENT_RSZ_INT_CYC_RSZB = 17,
    /**< An event can be triggered every time that RSZ_IRQ_RZB output
     *   lines have been written out to the RZB_SDR_Y buffer */
    IEM_ISP_EVENT_RSZ_INT_FIFO_OVF = 18,
    /**< Resizer module overflow */
    IEM_ISP_EVENT_RSZ_INT_FIFO_IN_BLK_ERR = 19,
    IEM_ISP_EVENT_RSZ_INT_EOF0            = 22,
    IEM_ISP_EVENT_RSZ_INT_EOF1            = 23,
    IEM_ISP_EVENT_H3A_INT_EOF             = 24,
    IEM_ISP_EVENT_IPIPE_INT_EOF           = 25,
    IEM_ISP_EVENT_IPIPE_DPC_IN            = 27,
    IEM_ISP_EVENT_IPIPE_DPC_RENEW0        = 28,
    IEM_ISP_EVENT_IPIPE_DPC_RENEW1        = 29,
    IEM_ISP_EVENT_OCP_ERR = 31,
    IEM_ISP_EVENT_H3A_OVF = 32,
    /**< H3a Overflow event */
    IEM_ISP_EVENT_IPIPEIF_UDF = 33,
    /**< IPIPEIF Underflow event */
    IEM_ISP_EVENT_IPIPE_BOXCAR_OVF = 34,
    /**< IPIPE Boxcar Overflow event */
    IEM_ISP_EVENT_ISIF_OVF = 35,
    /**< ISIF Overflow Event */
    IEM_ISP_EVENT_IPIPE_HST_ERR = 36,
    /**< IPIPE Histogram Error */
    IEM_ISP_EVENT_IPIPE_BSC_ERR = 37,
    /**< IPIPE BSC Error */
    IEM_ISP_EVENT_IPIPEIF_CB = 38,
    /**< IPIPEIF CB Error */
    IEM_ISP_EVENT_ISIF_CB = 39,
    /**< ISIF CB Error */
    IEM_ISP_EVENT_NSF3V_INT_REPRGM = 40,
    /**< NSF3 Reprogram Event */
    IEM_ISP_EVENT_NSF3V_INT_INCMPL = 41,
    /**< NSF3 Input Completion Event */
    IEM_ISP_EVENT_NSF3V_INT_OUTCMPL = 42,
    /**< NSF3 output Completion Event */
    IEM_ISP_EVENT_NSF3V_INT_OVERFLOW = 43,
    /**< NSF3 overflow Event */
    IEM_ISP_EVENT_NSF3V_VERT_BLANK = 44,
    /**< NSF3 Vertical Blanking event */
    IEM_ISP_EVENT_NSF3V_INT_HORZ_BLANK = 45,
    /**< NSF3 Horizontal Blanking event */
    IEM_ISP_EVENT_GLBCE_INT_REG = 46,
    /**< GLBCE Register event */
    IEM_ISP_EVENT_GLBCE_FILTERING_START = 47,
    /**< GLBCE Filtering start event */
    IEM_ISP_EVENT_GLBCE_FILTERING_DONE = 48,
    /**< GLBCE Filtering stop event */
    IEM_ISP_EVENT_GLBCE_ERROR = 49,
    /**< GLBCE error event */
    IEM_ISP_EVENT_CNFA_INT_REPRGM = 50,
    /**< CNFA Reprogram event */
    IEM_ISP_EVENT_CNFA_INT_INCMPL = 51,
    /**< CNFA NSF3 Input Completion Event */
    IEM_ISP_EVENT_CNFA_INT_OUTCMPL = 52,
    /**< CNFA output Completion Event */
    IEM_ISP_EVENT_CNFA_INT_OVERFLOW = 53,
    /**< CNFA overflow Event */
    IEM_ISP_EVENT_CNFA_VERT_BLANK = 54,
    /**< CNFA Vertical Blanking event */
    IEM_ISP_EVENT_CNFA_INT_HORZ_BLANK = 55,
    /**< CNFA Horizontal Blanking event */
    IEM_ISP_EVENT_SWT_NSF3V_OVERFLOW = 63,
    /**< NSF3 Overflow event */
    IEM_ISP_EVENT_FORCE_INT = 0x7FFFFFFF
                              /**< This will ensure enum is not packed, will
                               *always be contained in int */
} issemIspEvents_t;

/**
 *  \brief Possible LVDS events, expected to be used when event group is
 *          IEM_EG_LVDSRX0.
 */
typedef enum issemLvdsrxEvents
{
    IEM_LVDSRX_EVENT_CAM1_SOF = 0,
    /**< Start of frame timing */
    IEM_LVDSRX_EVENT_CAM1_ERR_EOX = 1,
    /**< EOX not received */
    IEM_LVDSRX_EVENT_CAM1_ERR_SOV = 2,
    /**< Unexpected SOV */
    IEM_LVDSRX_EVENT_CAM1_ERR_EOL = 3,
    /**< unexpected EOL */
    IEM_LVDSRX_EVENT_CAM1_ERR_EOF = 4,
    /**< unexpected EOF */
    IEM_LVDSRX_EVENT_CAM1_ERR_SOL = 5,
    /**< unexpected SOL */
    IEM_LVDSRX_EVENT_CAM1_ERR_SOF = 6,
    /**< unexpected SOF */
    IEM_LVDSRX_EVENT_CAM1_ERR_CRC = 7,
    /**< CRC Error */
    IEM_LVDSRX_EVENT_CAM1_ERR_TIMEOUT = 8,
    /**< sync detected timeout reached */
    IEM_LVDSRX_EVENT_FORCE_INT = 0x7FFFFFFF
                                 /**< This will ensure enum is not packed, will
                                  *always be contained in int */
} issemLvdsrxEvents_t;

/**
 *  \brief Possible SIMCOP events, expected to be used when event group is
 *          IEM_EG_SIMCOP0, IEM_EG_SIMCOP1, IEM_EG_SIMCOP2 or IEM_EG_SIMCOP3.
 */
typedef enum issemSimcopEvents
{
    IEM_SIMCOP_EVENT_DMA0 = 0,
    /**< Event triggered by the SIMCOP DMA */
    IEM_SIMCOP_EVENT_LDC_FRAME = 1,
    /**< This event is triggered by LDC when a full frame has been processed */
    IEM_SIMCOP_EVENT_VTNF = 8,
    /**< Event triggered by the VTNF imaging accelerator
     *   when processing of a block is done */
    IEM_SIMCOP_EVENT_LDC_BLOCK = 9,
    /**< This event is triggered by LDC when a macro-block has been processed */
    IEM_SIMCOP_EVENT_STEP0 = 10,
    /**< Event triggered when STEP0 is activated by the HW sequencer */
    IEM_SIMCOP_EVENT_STEP1 = 11,
    /**< Event triggered when STEP1 is activated by the HW sequencer */
    IEM_SIMCOP_EVENT_STEP2 = 12,
    /**< Event triggered when STEP2 is activated by the HW sequencer */
    IEM_SIMCOP_EVENT_STEP3 = 13,
    /**< Event triggered when STEP3 is activated by the HW sequencer */
    IEM_SIMCOP_EVENT_HWSEQ_DONE = 14,
    /**< Event triggered when the HW sequencer finishes the sequence:
     *      - the sequence step counter has reached the limit
     *      - all accelerator and DMA events for the last sequence
     *        step have been received */
    IEM_SIMCOP_EVENT_OCP_ERR = 16,
    /**< An OCP error has been received on the OCPMB master port */
    IEM_SIMCOP_EVENT_DMA1 = 18,
    /**< Event triggered by the SIMCOP DMA */
    IEM_SIMCOP_EVENT_PROC_START = 20,
    /**< Event triggered by the HW sequencer to instruct the CPU to process
     * a macro block
     */
    IEM_SIMCOP_EVENT_FORCE_INT = 0x7FFFFFFF
                                 /**< This will ensure enum is not packed, will
                                  *always be contained in int */
} issemSimcopEvents_t;

/**
 *  \brief Possible CAL events, expected to be used when event group is
 *          IEM_EG_CAL_A or IEM_EG_CAL_B.
 */
typedef enum issemCalEvents
{
    IEM_CAL_EVENT_RDMA_END          = 0,
    /**< Event triggered when CAL read is completed */
    IEM_CAL_EVENT_BYSIN_OVR         = 1,
    /**< Event triggered when CAL BYS IN overflows */
    IEM_CAL_EVENT_VPORT_EOF         = 2,
    /**< Event triggered when CAL End Of Frame seen at VPORT port */
    IEM_CAL_EVENT_BYSOUT_EOF        = 3,
    /**< Event triggered when CAL End Of Frame seen at BYS_OUT port */
    IEM_CAL_EVENT_BYSIN_SOF         = 4,
    /**< Event triggered when CAL Start Of Frame seen at BYS_IN port */
    IEM_CAL_EVENT_BYSIN_EOF         = 5,
    /**< Event triggered when CAL End Of Frame seen at BYS_OUT port */
    IEM_CAL_EVENT_OCPO_ERR          = 6,
    /**< Internal write failure error */
    IEM_CAL_EVENT_RDMA_CIRC         = 7,
    /**< Event triggered when configured number of lines received into circular
            buffer. */
    IEM_CAL_EVENT_LINE_NUMBER       = 8,
    /**< Event triggered when configured number of lines is received by CAL */
    IEM_CAL_EVENT_BYSOUT_VBLANK_END = 9,
    /**< Event triggered when at the end of VBLANK period on BYS_OUT port */
    IEM_CAL_EVENT_PPIO              = 16,
    /**< This is aggregate event, which when set indicates that there 1 or more
            events CSI2 events. Please DO NOT USE this.
            Use event group IEM_EG_CAL_A_CSI2 and events issemCalEvents_t*/
    IEM_CAL_EVENT_PPIO_VC           = 17,
    /**< This is aggregate event, which when set indicates that there 1 or more
            events CSI2 events. Please DO NOT USE this.
            Use event group IEM_EG_CAL_A_CSI2 and events issemCalEvents_t*/
    IEM_CAL_EVENT_PPIO1             = 24,
    /**< Not applicable for now */
    IEM_CAL_EVENT_PPIO1_VC          = 25,
    /**< Not applicable for now */

    /**< Event triggered when DMA Write completes */
    IEM_CAL_EVENT_WDMA_END0  = 32 + 0,
    IEM_CAL_EVENT_WDMA_END1  = 32 + 1,
    IEM_CAL_EVENT_WDMA_END2  = 32 + 2,
    IEM_CAL_EVENT_WDMA_END3  = 32 + 3,
    IEM_CAL_EVENT_WDMA_END4  = 32 + 4,
    IEM_CAL_EVENT_WDMA_END5  = 32 + 5,
    IEM_CAL_EVENT_WDMA_END6  = 32 + 6,
    IEM_CAL_EVENT_WDMA_END7  = 32 + 7,
    IEM_CAL_EVENT_WDMA_CICR0 = 32 + 16,
    IEM_CAL_EVENT_WDMA_CICR1 = 32 + 17,
    IEM_CAL_EVENT_WDMA_CICR2 = 32 + 18,
    IEM_CAL_EVENT_WDMA_CICR3 = 32 + 19,
    IEM_CAL_EVENT_WDMA_CICR4 = 32 + 20,
    IEM_CAL_EVENT_WDMA_CICR5 = 32 + 21,
    IEM_CAL_EVENT_WDMA_CICR6 = 32 + 22,
    IEM_CAL_EVENT_WDMA_CICR7 = 32 + 23,

    /**< Event triggered when DMA read starts */
    IEM_CAL_EVENT_WDMA_START0 = 64 + 0,
    IEM_CAL_EVENT_WDMA_START1 = 64 + 1,
    IEM_CAL_EVENT_WDMA_START2 = 64 + 2,
    IEM_CAL_EVENT_WDMA_START3 = 64 + 3,
    IEM_CAL_EVENT_WDMA_START4 = 64 + 4,
    IEM_CAL_EVENT_WDMA_START5 = 64 + 5,
    IEM_CAL_EVENT_WDMA_START6 = 64 + 6,
    IEM_CAL_EVENT_WDMA_START7 = 64 + 7,

    /**< CSI3 Specific, not applicable for now !!! */
    IEM_CAL_EVENT_LL_SOF0     = 96 + 0,
    IEM_CAL_EVENT_LL_SOF1     = 96 + 1,
    IEM_CAL_EVENT_LL_SOF2     = 96 + 2,
    IEM_CAL_EVENT_LL_SOF3     = 96 + 3,
    IEM_CAL_EVENT_ATTR_CTRL0  = 96 + 4,
    IEM_CAL_EVENT_ATTR_CTRL1  = 96 + 5,
    IEM_CAL_EVENT_ATTR_CTRL2  = 96 + 6,
    IEM_CAL_EVENT_ATTR_CTRL3  = 96 + 7,
    IEM_CAL_EVENT_PIX_CTRL0   = 96 + 8,
    IEM_CAL_EVENT_PIX_CTRL1   = 96 + 9,
    IEM_CAL_EVENT_PIX_CTRL2   = 96 + 10,
    IEM_CAL_EVENT_PIX_CTRL3   = 96 + 11,
    IEM_CAL_EVENT_TX_OVR0     = 96 + 12,
    IEM_CAL_EVENT_TX_OVR1     = 96 + 13,
    IEM_CAL_EVENT_TX_OVR2     = 96 + 14,
    IEM_CAL_EVENT_TX_OVR3     = 96 + 15,
    IEM_CAL_EVENT_LL_INVALID0 = 96 + 16,
    IEM_CAL_EVENT_LL_INVALID1 = 96 + 17,
    IEM_CAL_EVENT_LL_INVALID2 = 96 + 18,
    IEM_CAL_EVENT_LL_INVALID3 = 96 + 19,
    IEM_CAL_EVENT_LL_EOF0     = 96 + 20,
    IEM_CAL_EVENT_LL_EOF1     = 96 + 21,
    IEM_CAL_EVENT_LL_EOF2     = 96 + 22,
    IEM_CAL_EVENT_LL_EOF3     = 96 + 23,
    IEM_CAL_EVENT_LL_SOF4     = 218 + 0,
    IEM_CAL_EVENT_LL_SOF5     = 218 + 1,
    IEM_CAL_EVENT_LL_SOF6     = 218 + 2,
    IEM_CAL_EVENT_LL_SOF7     = 218 + 3,
    IEM_CAL_EVENT_ATTR_CTRL4  = 218 + 4,
    IEM_CAL_EVENT_ATTR_CTRL5  = 218 + 5,
    IEM_CAL_EVENT_ATTR_CTRL6  = 218 + 6,
    IEM_CAL_EVENT_ATTR_CTRL7  = 218 + 7,
    IEM_CAL_EVENT_PIX_CTRL4   = 218 + 8,
    IEM_CAL_EVENT_PIX_CTRL5   = 218 + 9,
    IEM_CAL_EVENT_PIX_CTRL6   = 218 + 10,
    IEM_CAL_EVENT_PIX_CTRL7   = 218 + 11,
    IEM_CAL_EVENT_TX_OVR4     = 218 + 12,
    IEM_CAL_EVENT_TX_OVR5     = 218 + 13,
    IEM_CAL_EVENT_TX_OVR6     = 218 + 14,
    IEM_CAL_EVENT_TX_OVR7     = 218 + 15,
    IEM_CAL_EVENT_LL_INVALID4 = 218 + 16,
    IEM_CAL_EVENT_LL_INVALID5 = 218 + 17,
    IEM_CAL_EVENT_LL_INVALID6 = 218 + 18,
    IEM_CAL_EVENT_LL_INVALID7 = 218 + 19,
    IEM_CAL_EVENT_LL_EOF4     = 218 + 20,
    IEM_CAL_EVENT_LL_EOF5     = 218 + 21,
    IEM_CAL_EVENT_LL_EOF6     = 218 + 22,
    IEM_CAL_EVENT_LL_EOF7     = 218 + 23,

    IEM_CAL_EVENT_FORCE_INT = 0x7FFFFFFF
                              /**< This will ensure enum is not packed, will
                               *always be contained in int */
} issemCalEvents_t;

typedef enum issemModules
{
    IEM_MODULE_ISS_CAL_A     = 0,
    IEM_MODULE_ISS           = 1,
    IEM_MODULE_ISP_SYS1      = 2,
    IEM_MODULE_ISP_SYS2      = 3,
    IEM_MODULE_ISP_SYS3      = 4,
    IEM_MODULE_ISS_SIMCOP    = 5,
    IEM_MODULE_ISS_LVDSRX    = 6,
    IEM_MODULE_ISS_CAL_B     = 7,
    IEM_MODULE_ISS_MAX       = 8,
    IEM_MODULE_ISS_FORCE_INT = 0x7FFFFFFF
                               /**< This will ensure enum is not packed, will
                                *always be contained in int */
} issemModules_t;

/**
 *  \brief enum for specifying the priority of the client. Event
 *  Manager always calls the callback functions of the clients in the order of
 *  priority so that highest priority callback will get executed much earlier.
 *  When client registers itself to the event manager, it also specifies the
 *  priority of itself. Event manager puts the client in the appropriate
 *  location in the linked list as per the given priority. This enum data
 *  type defines the event groups. This enum data type is typecast to
 *  unsigned int so it must not have any negative value
 */
typedef enum issemPriority
{
    IEM_PRIORITY0 = 0U,
    /**< Highest. Typically used for error handling */
    IEM_PRIORITY1,
    IEM_PRIORITY2,
    IEM_PRIORITY3,
    IEM_PRIORITY4,
    /**< Lowest. For normal operations, frame completion, etc... */
    IEM_PRIORITY_FORCE_INT
    /**< This will ensure enum is not packed, will
     *always be contained in int */
} issemPriority_t;

/**
 *  \brief This typedef defines the VPS Event manager callback function
 *  prototype. Client registers this callback with the event manager and when
 *  event occurs, event manager calls this callback.
 *
 *  \param  event       This is an array of events occurred when interrupt came.
 *                      Event manager passes this list to the client.
 *  \param  numEvents   This tells number of events occurred.
 *  \param  arg         Client's Private Data
 */
typedef void (*issemClientCbFxn)(const UInt32 *event,
                                 UInt32        numEvents,
                                 Ptr           arg);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct issemInitParams
{
    uint32_t numIrq;
    /**< Number of valid entries in below two arrays */
    uint32_t instId[IEM_MAX_INST];
    /**< Instance Ids */
    uint32_t irqNum[IEM_MAX_INST];
    /**< irq number */
    uint32_t numBaseAddress;
    /**< number of valid entries in baseAddress */
    uint32_t baseAddress[IEM_MODULE_ISS_MAX];
    /**< Base Addresses for different modules */
} issemInitParams_t;

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  \brief This function initializes event manager. It creates the semaphore,
 *  initializes pointers and sets the memory to zero. It also register ISR
 *  for the VPS interrupt. It returns pass or fail based on initialization
 *  passed or failed.
 *
 *  \param numInst      Number of VEM Instances and number of
 *                      array elements in the second argument.
 *  \param instPrms     Instance specific parameters.
 *
 *  \return             Returns 0 on success else returns error value
 */
int32_t Vps_iemInit(const issemInitParams_t *initPrms);

/**
 *  \brief This function de-initializes the event manager.
 *
 *  \return             Returns 0 on success else returns error value
 */
int32_t Vps_iemDeInit(void);

/**
 *  \brief Function to register callback to the Event Manager. Client passes
 *  the set of events of a group with the callback and priority and
 *  this function adds a new node at the appropriate position as per
 *  the priority in the list of nodes. It also stores the list of
 *  events, registers for the events and masks in the the client info
 *  structure. It returns handle of the registered callback.
 *
 *  \param instId           Instance ID to register with.
 *  \param eventGroup       Group of the event passed in the second argument
 *  \param event            List of event for which client requested callback
 *  \param numEvents        Number of events in the second argument
 *  \param priority         Priority of this callback
 *  \param callback         Callback function of the client
 *  \param arg              Private Data of the client
 *
 *  \return                 It returns the handle of the registered callback.
 */
void *Vps_iemregister(issemInstId_t     instId,
                      issemEventGroup_t eventGroup,
                      const uint32_t   *event,
                      uint32_t          numEvents,
                      issemPriority_t   priority,
                      issemClientCbFxn  callback,
                      void             *arg);

/**
 *  \brief Function to un-register callback from the event manager. It removes
 *  node from the linked list and frees up memory allocated to the node
 *  and client info structure. It takes handle to the callback and
 *  returns status of the whether callback is removed.
 *
 *  \param handle           Handle to the callback
 *  \return                 Returns 0 on success else returns error value
 */
int32_t Vps_iemUnRegister(void *handle);

int32_t Vps_iemDisable(void *handle);

int32_t Vps_iemEnable(void *handle);

int32_t Iem_disableAll(void *handle);

#ifdef __cplusplus
}
#endif

#endif  /* _VPS_IRQ_EVENT_MNGR_H_ */
