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
 *  \file vps_cfgcal.h
 *
 *  \brief  Defines the structures / control operations that could be used to
 *              configure / control CAL module
 */

/**
 *  \ingroup BSP_DRV_VPS_COMMON_API
 *  \addtogroup BSP_DRV_VPS_COMMON_CAPTURE_CAL_ISS - CAL Config API
 *
 *  @{
 */

#ifndef VPS_CFG_CAL_H_
#define VPS_CFG_CAL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>

/* ========================================================================== */
/*                                   Macros                                   */
/* ========================================================================== */

/** \brief Defines the total number of complex IO available per CAL (1) */
#if defined (SOC_TDA3XX)
#define VPS_ISS_CAL_MAX_CMPLXIO_INST    (1U)
#endif
/** \brief Defines the total number of complex IO available per CAL (2) */
#if defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_TDA2PX)
#define VPS_ISS_CAL_MAX_CMPLXIO_INST    (2U)
#endif

/** \brief Defines total number of pixel processing context available */
#define VPS_ISS_CAL_MAX_PIX_PROC_CONTEXT    (4U)

/** \brief Defines the total number of DMA writes that are possible per CAL
**/
#define VPS_ISS_CAL_MAX_STREAMS             (8U)

/** \brief Defines the total number error interrupts
**/
#define VPS_ISS_CAL_MAX_ERROR_INTERRUPTS    (20U)

/** \brief Defines the total number of VC, for which a callback can be issued
 *          on reception of X lines.
**/
#define VPS_ISS_CAL_MAX_X_LINE_MONITOR_CNT  (1U)

/* ========================================================================== */
/*                                 Function Types                             */
/* ========================================================================== */
/**
 *  \brief Defines expected function type that could be called by drivers on
 *          error conditions. Please refer driver specific header files on
 *          methods to attach callbacks on errors.
 *
 *  \param  event       Pointer to an array that holds event (s) that have
 *                          occurred. The numEvents determine the number of
 *                          elements that could accessed.
 *  \param  numEvents   Number of events (error conditions) that were detected.
 *  \param  arg         Argument provided while configuring the error parameters
 */
typedef void (*vpsissErrorCallBack)(const UInt32 *event,
                                    UInt32        numEvents,
                                    Ptr           arg);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct vpsissCaptInstId
 *  \brief Different instances of capture. As name suggests, each instance is
 *          associated with a particular method of capture. Multiple instances
 *          can co-exist, provided co-existence is supported in the h/w.
 *
 *  \warning Deviation from naming convention: To enable backward compatibility
 *
 */
typedef enum vpsissCaptInstId
{
    VPS_ISS_CAPT_CAL_A_ID = 0U,
    /**< Capture CSI2 streams via CAL. Requires to be first enum.
     *      This is requires to start with 0x0. Used an index internally in
     *      core */
    VPS_ISS_CAPT_CAL_A_CPI = 1U,
    /**< Capture From CPI - Via VPORT of IPIPEIF. Essentially via Parallel OR
     *      LVDS input which are interfaced to CPI port. */
    VPS_ISS_CAPT_CAL_A_OTF0_ID = 2U,
    /**< Capture CSI2 streams via CAL. Requires to be first enum. */
    VPS_ISS_CAPT_INST_MAX_ID = 3U,
    /**< Enum end marker */
    VPS_ISS_CAPT_INST_FORCE_INT = 0x7FFFFFFF
                        /**< This will ensure enum is not packed,
                         *      will always be contained in int */
} vpsissCaptInstId_t;   /**< vpsissCaptInstId_t */


/**
 *  enum vpsissCaptureSubModuleId
 *  \brief Different sub-modules with in the CAL block.
 *
 *  \warning Deviation from naming convention: To enable backward compatibility
 *
 */
typedef enum vpsissCaptureSubModuleId
{
    VPS_ISS_CAPT_CAL_SUB_MIN_ID = 0x000,
    /**< Begin marker */
    VPS_ISS_CAPT_CAL_SUB_PPI_ID_0 = 0x001,
    /**< PPI Interface, one per instance  */
    VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID = 0x002,
    /**< Pixel extract */
    VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID = 0x004,
    /**< DPCM Decode */
    VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID = 0x008,
    /**< DPCM Encode */
    VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID = 0x010,
    /**< Pixel packing */
    VPS_ISS_CAPT_CAL_SUB_BYS_OUT_ID = 0x020,
    /**< BYS Out */
    VPS_ISS_CAPT_CAL_SUB_BYS_IN_ID = 0x040,
    /**< BYS IN */
    VPS_ISS_CAPT_CAL_SUB_VPORT_ID = 0x080,
    /**< BYS IN */
    VPS_ISS_CAPT_CAL_SUB_DMA_RD_ID = 0x100,
    /**< DMA Read */
    VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID = 0x200,
    /**< DMA Write */
    VPS_ISS_CAPT_CAL_SUB_CSI2_ID = 0x400,
    /**< cport ID */
    VPS_ISS_CAPT_CAL_SUB_CPORT_ID = 0x800,
    /**< cport ID */
    VPS_ISS_CAPT_LVDS_ID = 0x1000,
    /**< LVDS Port ID */
    VPS_ISS_CAPT_CPI_ID = 0x2000,
    /**< CPI / Parallel interface */
    VPS_ISS_CAPT_CAL_SUB_PPI_ID_1 = 0x3000,
    /**< PPI Interface, one per instance  */
    VPS_ISS_CAPT_MOD_MAX_ID = 0x3001,
    /**< Enum end marker */
    VPS_ISS_CAPT_MOD_FORCE_INT = 0x7FFFFFFF
                                /**< This will ensure enum is not packed,
                                 *      will always be contained in int */
} vpsissCaptureSubModuleId_t;   /**< vpsissCaptureSubModuleId_t */


/**
 *  \brief Resources allocated instances. 0xFFFFFFFF in case not allocated.
 *          Otherwise valid instance number
 *
 *  \warning Deviation from naming convention: To enable backward compatibility
 *
 */
typedef struct vpsissCaptureBlocks
{
    UInt32 ppi0Inst;
    /**< PPI interface instance,  0xFFFFFFFF in case not allocated. Otherwise
     *      valid instance number */
    UInt32 ppi1Inst;
    /**< PPI Instace 1 */
    UInt32 pixExtract;
    /**< Pixel Extract instance */
    UInt32 dpmDecode;
    /**< DPM Decode instance */
    UInt32 dpmEncode;
    /**< DPM Encode instance */
    UInt32 pixPack;
    /**< Pixel Pack instance */
    UInt32 bysOut;
    /**< BYS Out instance */
    UInt32 bysIn;
    /**< BYS IN instance */
    UInt32 vPort;
    /**< VPORT IN instance */
    UInt32 rdDma;
    /**< RD Dma instance */
    UInt32 wrDma;
    /**< WR Dma instance */
    UInt32 csi2Ctx;
    /**< CSI2 processing context */
    UInt32 cport;
    /**< CPort ID */
    UInt32 lvds;
    /**< LVDS port */
    UInt32 cpi;
    /**< Parallel / CPI port */
} vpsissCaptureBlocks_t;


/**
 *  enum vpsissCalCsi2DataFormat
 *  \brief CSI2 Data types.
 *
 */
typedef enum
{
    VPS_ISS_CAL_CSI2_YUV420_8B = 0x18,
    /**< YUV 4:2:0 with 8bit for each Y/U/V */
    VPS_ISS_CAL_CSI2_YUV420_10B = 0x19,
    /**< YUV 4:2:0 with 10bit for each Y/U/V */
    VPS_ISS_CAL_CSI2_YUV420_8B_LEGACY = 0x1A,
    /**< YUV 4:2:0 with 8bit for each Y/U/V */
    VPS_ISS_CAL_CSI2_YUV420_8B_CHROMA_SHIFT = 0x1C,
    /**< YUV 4:2:0 with 8bit for each Y/U/V with
     *   with phase shifted chroma */
    VPS_ISS_CAL_CSI2_YUV420_10B_CHROMA_SHIFT = 0x1D,
    /**< YUV 4:2:0 with 10bit for each Y/U/V with
     *   with phase shifted chroma */
    VPS_ISS_CAL_CSI2_YUV422_8B = 0x1E,
    /**< YUV 4:2:2 with 8bit for each Y/U/V */
    VPS_ISS_CAL_CSI2_YUV422_10B = 0x1F,
    /**< YUV 4:2:2 with 10bit for each Y/U/V */
    VPS_ISS_CAL_CSI2_RGB444 = 0x20,
    /**< RGB888 - 4-bits B, 4-bits G, 4-bits R */
    VPS_ISS_CAL_CSI2_RGB555 = 0x21,
    /**< RGB888 - 5-bits B, 5-bits G, 5-bits R */
    VPS_ISS_CAL_CSI2_RGB565 = 0x22,
    /**< RGB888 - 5-bits B, 6-bits G, 5-bits R */
    VPS_ISS_CAL_CSI2_RGB666 = 0x23,
    /**< RGB888 - 6-bits B, 6-bits G, 6-bits R */
    VPS_ISS_CAL_CSI2_RGB888 = 0x24,
    /**< RGB888 - 8-bits B, 8-bits G, 8-bits R */
    VPS_ISS_CAL_CSI2_RAW6 = 0x28,
    /**< 6 bit raw-data. */
    VPS_ISS_CAL_CSI2_RAW7 = 0x29,
    /**< 7 bit raw-data. */
    VPS_ISS_CAL_CSI2_RAW8 = 0x2A,
    /**< 8 bit raw-data. */
    VPS_ISS_CAL_CSI2_RAW10 = 0x2B,
    /**< 10 bit raw-data. */
    VPS_ISS_CAL_CSI2_RAW12 = 0x2C,
    /**< 12 bit raw-data. */
    VPS_ISS_CAL_CSI2_RAW14 = 0x2D,
    /**< 14 bit raw-data. */
    VPS_ISS_CAL_CSI2_ANY = 0x01,
    /**< Allow any data type for capture */
    VPS_ISS_CAL_CSI2_DISABLE_CONTEXT = 0x00
                                       /**< Disable capture. */
} vpsissCalCsi2DataFormat;

/**
 *  struct vpsissCalCmplxIoLaneCfg
 *  \brief Configure the position and order of lane for the complex IO.
 *
 */
typedef struct vpsissCalCmplxIoLaneCfg
{
    uint32_t pol;
    /**< TRUE configures for - / + order of differential signal.
     + / - order otherwise */
    uint32_t position;
    /**< Specify if this lane is to be used, if so, on which position.
     *  0x0 - Not used / disabled lane
     *  0x1 - Position 1
     *  0x2 - Position 2
     *  0x3 - Position 3
     *  0x4 - Position 4
     *  0x5 - Position 5 */
} vpsissCalCmplxIoLaneCfg_t;

/**
 *  struct vpsissCalCmplxIoCfg
 *  \brief Configure complex IO.
 *
 */
typedef struct vpsissCalCmplxIoCfg
{
    uint32_t                  enable;
    /**< FALSE disables, otherwise indicates the instance to be used. Valid
     *  values are 1 and 2 */
    vpsissCalCmplxIoLaneCfg_t clockLane;
    /**< Configure position and order of differential signal */
    vpsissCalCmplxIoLaneCfg_t data1Lane;
    /**< Configure position and order of differential signal */
    vpsissCalCmplxIoLaneCfg_t data2Lane;
    /**< Configure position and order of differential signal */
    vpsissCalCmplxIoLaneCfg_t data3Lane;
    /**< Configure position and order of differential signal */
    vpsissCalCmplxIoLaneCfg_t data4Lane;
    /**< Configure position and order of differential signal */
    uint32_t                  pwrAuto;
    /**< Auto power control mode of complex IO. TRUE configures it to enable
     *  auto power mode (in which power switches to ON / OFF based on ULP / ULPM
     *  commands from the sensor.
     *  Always powered on otherwise */
} vpsissCalCmplxIoCfg_t;

/**
 *  enum vpsissCalPixExtract
 *  \brief Valid pixel extraction supported, control extraction of "word" from
 *          byte stream.
 *
 */
typedef enum vpsissCalPixExtract
{
    VPS_ISS_CAL_PIX_EXRCT_MIN = 0,
    /**< Begin Marker */
    VPS_ISS_CAL_PIX_EXRCT_B6,
    /**< 6 bits represent a word */
    VPS_ISS_CAL_PIX_EXRCT_B7,
    /**< 7 bits represent a word */
    VPS_ISS_CAL_PIX_EXRCT_B8,
    /**< 8 bits represent a word */
    VPS_ISS_CAL_PIX_EXRCT_B10_LINEAR,
    /**< 10 bits represent a word */
    VPS_ISS_CAL_PIX_EXRCT_B10_MIPI,
    /**< 10 bits represent a word */
    VPS_ISS_CAL_PIX_EXRCT_B12_LINEAR,
    /**< 12 bits represent a word */
    VPS_ISS_CAL_PIX_EXRCT_B12_MIPI,
    /**< 12 bits represent a word */
    VPS_ISS_CAL_PIX_EXRCT_B14_LINEAR,
    /**< 14 bits represent a word */
    VPS_ISS_CAL_PIX_EXRCT_B14_MIPI,
    /**< 14 bits represent a word */
    VPS_ISS_CAL_PIX_EXRCT_B16_BE,
    /**< 16 bits represent a word, big endian */
    VPS_ISS_CAL_PIX_EXRCT_B16_LE,
    /**< BYPASS - Extraction / 16 bits represent a word, little endian */
    VPS_ISS_CAL_PIX_EXRCT_MAX
    /**< End Marker */
} vpsissCalPixExtract_t; /**< vpsissCalPixExtract_t */

/**
 *  enum vpsissCalPixDpcmDecoder
 *  \brief Valid de-compression methods supported.
 *
 */
typedef enum vpsissCalPixDpcmDecoder
{
    VPS_ISS_CAL_DPCM_DEC_BYPASS = 0x0U,
    /**< BY PASS mode */
    VPS_ISS_CAL_DPCM_DEC_10_8_10_1 = 0x2U,
    /**< 10_8_10_1 decode */
    VPS_ISS_CAL_DPCM_DEC_10_7_10_1 = 0x4U,
    /**< 10_7_10_1 */
    VPS_ISS_CAL_DPCM_DEC_10_7_10_2 = 0x5U,
    /**< 10_7_10_1 decode */
    VPS_ISS_CAL_DPCM_DEC_10_6_10_1 = 0x6U,
    /**< 10_6_10_1 decode */
    VPS_ISS_CAL_DPCM_DEC_10_6_10_2 = 0x7U,
    /**< 10_6_10_2 decode */
    VPS_ISS_CAL_DPCM_DEC_12_8_12_1 = 0x8U,
    /**< 12_8_12_1, decode */
    VPS_ISS_CAL_DPCM_DEC_12_7_12_1 = 0xAU,
    /**< 12_7_12_1, decode */
    VPS_ISS_CAL_DPCM_DEC_12_6_12_1 = 0xCU,
    /**< 12_6_12_1 decode */
    VPS_ISS_CAL_DPCM_DEC_14_10_14 = 0xEU,
    /**< 14_10_14 decode */
    VPS_ISS_CAL_DPCM_DEC_14_8_14_1 = 0x10U,
    /**< 14_8_14_1 decode */
    VPS_ISS_CAL_DPCM_DEC_16_12_16_1 = 0x12U,
    /**< 16_12_16_1 decode */
    VPS_ISS_CAL_DPCM_DEC_16_10_16_1 = 0x14U,
    /**< 16_10_16_1 decode */
    VPS_ISS_CAL_DPCM_DEC_16_8_16_1 = 0x16U,
    /**< 16_8_16_1 decode */
    VPS_ISS_CAL_DPCM_DEC_MAX = 0x17U
    /**< End marker */
} vpsissCalPixDpcmDecoder_t;    /**< vpsissCalPixDpcmDecoder_t */

/**
 *  enum vpsissCalPixDpcmEncoder
 *  \brief Valid compression methods supported.
 *
 */
typedef enum vpsissCalPixDpcmEncoder
{
    VPS_ISS_CAL_DPCM_ENC_BYPASS = 0,
    /**< Encoder bypassed */
    VPS_ISS_CAL_DPCM_ENC_10_8_10_1 = 0x02U,
    /**< 10-8-10 Predictor 1 */
    VPS_ISS_CAL_DPCM_ENC_12_8_12_1 = 0x08U,
    /**< 12-8-12 Predictor 1 */
    VPS_ISS_CAL_DPCM_ENC_14_10_14 = 0x0EU,
    /**< 14-10-14 Predictor 1 */
    VPS_ISS_CAL_DPCM_ENC_14_8_14_1 = 0x10U,
    /**< 14-8-14 Predictor 1 */
    VPS_ISS_CAL_DPCM_ENC_16_12_16_1 = 0x12U,
    /**< 16-12-16 Predictor 1 */
    VPS_ISS_CAL_DPCM_ENC_16_10_16_1 = 0x14U,
    /**< 16-10-16 Predictor 1 */
    VPS_ISS_CAL_DPCM_ENC_16_8_16_1 = 0x16U,
    /**< 16-8-16 Predictor 1 */
    VPS_ISS_CAL_DPCM_ENC_MAX = 0x17U
    /**< End marker */
} vpsissCalPixDpcmEncoder_t;    /**< vpsissCalPixDpcmEncoder_t */

/**
 *  enum vpsissCalPixPack
 *  \brief Valid pixel packing supported.
 *
 */
typedef enum vpsissCalPixPack
{
    VPS_ISS_CAL_PIX_PACK_B8 = 0,
    /**< 8 bit packing */
    VPS_ISS_CAL_PIX_PACK_B10_MIPI = 0x2U,
    /**< 10 bit mipi packing */
    VPS_ISS_CAL_PIX_PACK_B12 = 0x3U,
    /**< 12 bit packing */
    VPS_ISS_CAL_PIX_PACK_B12_MIPI = 0x4U,
    /**< 12 bit mipi packing */
    VPS_ISS_CAL_PIX_PACK_B16 = 0x5U,
    /**< 16 bit packing */
    VPS_ISS_CAL_PIX_PACK_ARGB = 0x6U,
    /**< ARGB packing, 8 x 3 packing, followed by 8 bit padding */
    VPS_ISS_CAL_PIX_PACK_MAX = 0x7U
    /**< End Marker */
} vpsissCalPixPack_t;   /**< vpsissCalPixPack_t */

/**
 *  enum vpsissCalStreamType
 *  \brief Identifies different types streams.
 *
 */
typedef enum vpsissCalStreamType
{
    VPS_ISS_CAL_TAG_ATT_HDR = 0,
    /**< Attribute packet headers */
    VPS_ISS_CAL_TAG_ATT_DATA,
    /**< Attribute data */
    VPS_ISS_CAL_TAG_CTRL,
    /**< Control packets */
    VPS_ISS_CAL_TAG_PIX_HDR,
    /**< Pixel packet data headers */
    VPS_ISS_CAL_TAG_PIX_DATA,
    /**< Pixel Data */
    VPS_ISS_CAL_TAG_MAX
    /**< End marker */
} vpsissCalStreamType_t; /**< vpsissCalStreamType_t */

/**
 *  \brief Lists the possible error source in CAL reception. Applications
 *          could enable any of these and attach a function to be called on
 *          error (s)
 *          When enabled, the frame would marked with appropriate error code
 *          to indicate an issue.
 *
 *  \warning If any elements are added/deleted from this structure, ensure to
 *              update VPS_ISS_CAL_MAX_ERROR_INTERRUPTS
 */
typedef enum vpsissCalErrorSource
{
    /* Following events correspond to IEM_CAL_EVENT_PPIO */
    VPS_CAL_CSI2_PPI_CMPLXIO_ERRSOTHS1 = 0,
    /**< Not supported for now ! */
    VPS_CAL_CSI2_PPI_CMPLXIO_FIFO_OVR = 27,
    /**< Event triggered when CAL un able to process the received data.
            Typically down stream modules (including write DMA) is unable to
            keep up with the speed of reception of data. */
    VPS_CAL_CSI2_PPI_CMPLXIO_ECC_NO_CORRECTION = 30,
    /**< ECC module was unable to correct, as there were more than 1 bit errors.
            Applicable for all virtual channels */
    VPS_CAL_CSI2_PPI_CMPLXIO_RSERVED_31 = 31,
    /**< Reserved event, will be used for boundary checks */

    /* Following events correspond to IEM_CAL_EVENT_PPIO_VC */
    VPS_CAL_CSI2_PPI_VC_SOF1 = 128 + 0,
    /**< Not an error, Will be used for boundary checks / debug. */
    VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC1 = 128 + 4,
    /**< CRC did not match, the frame could be BAD */
    VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC1 = 128 + 5,
    /**< ECC module was able to correct 1 bit error */
    VPS_CAL_CSI2_PPI_VC_SOF2 = 128 + 8,
    /**< Not an error, Will be used for boundary checks / debug. */
    VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC2 = 128 + 12,
    /**< CRC did not match, the frame could be BAD */
    VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC2 = 128 + 13,
    /**< ECC module was able to correct 1 bit error */
    VPS_CAL_CSI2_PPI_VC_SOF3 = 128 + 16,
    /**< Not an error, Will be used for boundary checks / debug. */
    VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC3 = 128 + 20,
    /**< CRC did not match, the frame could be BAD */
    VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC3 = 128 + 21,
    /**< ECC module was able to correct 1 bit error */
    VPS_CAL_CSI2_PPI_VC_SOF4 = 128 + 24,
    /**< Not an error, Will be used for boundary checks / debug. */
    VPS_CAL_CSI2_PPI_VC_CRC_MISMATCH_VC4 = 128 + 28,
    /**< CRC did not match, the frame could be BAD */
    VPS_CAL_CSI2_PPI_VC_ECC_CORRECTION_VC4 = 128 + 29,
    /**< ECC module was able to correct 1 bit error */
    VPS_CAL_CSI2_PPI_VC_RESERVED_31 = 128 + 31,
    /**< Reserved event, will be used for boundary checks */

    VPS_CAL_BYSIN_OVR = VPS_CAL_CSI2_PPI_VC_RESERVED_31 + 1,
    /**< When CAL is used to receive via BYS IN (Parallel input) and the down
            stream modules could not keep up with the incoming data rate, the
            BYS IN port could overflow. */
    VPS_CAL_CSI2_FORCE_INT = 0x7FFFFFFF
    /**< This will ensure enum is not packed,
     *      will always be contained in int
     */
}vpsissCalErrorSource_t; /**< vpsissCalErrorSource_t */

/**
 *  struct vpsissCalPixProc
 *  \brief CAL Pixel Processing configuration control.
 */
typedef struct vpsissCalPixProc
{
    vpsissCalPixExtract_t     extract;
    /**< Configure bit extraction */
    vpsissCalPixDpcmDecoder_t decCodec;
    /**< Decoder required */
    uint32_t                  enableDpcmInitContext;
    /**< TRUE configure DPCM Decode to loaded from a specific memory location*/
    uint32_t                  addr;
    /**< Address of word describing DPCM init context. Should be 16 bytes
     *      aligned */
    uint32_t                  offSet;
    /**< Address offset for UV data, when data type if YUV420 */

    vpsissCalPixDpcmEncoder_t encCodec;
    /**< Encoder required */
    vpsissCalPixPack_t        pack;
    /**< Packing required */

    uint32_t                  contextToBeUsed;
    /**< RESERVED - Internal to driver. Value specified here is ignored.
     *      Context of pixel processing to be used. */
} vpsissCalPixProc_t;

/**
 *  struct vpsissCalBysOut
 *  \brief CAL BYS Out configuration control.
 */
typedef struct vpsissCalBysOut
{
    uint32_t enable;
    /**< TRUE, enables stream on BYS Out */
    uint32_t pixClock;
    /**< Configure the pixel clock required. A non zero value will ensure that
     *      BYS ports pixel clock will be gated when idle. */
    uint32_t yBlk;
    /**< Configure the Y Blank to be inserted at end of frame */
    uint32_t xBlk;
    /**< Configures the X blank to be inserted at end of line */
    uint32_t copyStreamToEncode;
    /**< TRUE configures, streams sent out on BYS out to be copied into encode*/
    uint32_t freeRun;
    /**< TRUE configures Bys out in Free running mode, False gated in idle */
} vpsissCalBysOut_t;

/**
 *  struct vpsissCalVPort
 *  \brief CAL Video Port configuration control.
 */
typedef struct vpsissCalVPort
{
    uint32_t enable;
    /**< TRUE, enables stream on Video Port input */
    uint32_t pixClock;
    /**< Configure the pixel clock required.
     *      When disabled pixlClock will be 0x0. */
    uint32_t width;
    /**< 0, indicates 1 pixel / clock cycle. Else 2 pixels / clock cycle */
    uint32_t yBlk;
    /**< Configure the Y Blank to be inserted at end of frame */
    uint32_t xBlk;
    /**< Configures the X blank to be inserted at end of line */
    uint32_t rdyThr;
    /**< Configure the initial threashold value, before the first pixel is
     *  recevied and passed for furthure proessing */
    uint32_t fsReset;
    /**< TRUE ReSet the timing generator FSM on every end of frame received,
     *      otherwise data processed normally */
    uint32_t freeRun;
    /**< TRUE enables the pixel clock during idle period. FALSE gates the same.
     */
} vpsissCalVPort_t;

/**
 *  struct vpsissCalCfg
 *  \brief CAL config, used to control all the sub-modules of CAL.
 *
 *  \attention  Ensure to allocate before trying to configure.
 *              There is only one instance of BYSOUT, BYSIN and VPORT and hence
 *                  can support only 1 channel. When these are used for
 *                  multiple channels, the last config is valid
 *
 *  \attention When non-CSI2 streams are being captured, following members
 *              are not applicable, stream, csi2VirtualChanNo, pixProcCfg &
 *              bysOutCfg.
 */
typedef struct vpsissCalCfg
{
    uint32_t numStream;
    /**< Specify the number of streams that requires to be configured. Minimum
     *      should be 1 and maximum could be VPS_ISS_CAL_MAX_STREAMS */
    uint32_t streamId[VPS_ISS_CAL_MAX_STREAMS];
    /**< Specify the stream ID, that requires to be configured.
     *      e.g. If first stream requires to be configured
     *      \code numStream = 1U;
     *            streamId[0] = 0U;
     *            inFmt[0].width = 1280U;
     *            inFmt[0].width = 800U;
     *      etc...
     *      e.g. if there are 3 streams and require to configure 2 of them, say
     *              stream 2 and 0
     *            numStream = 2U;
     *            streamId[0] = 0U;
     *            inFmt[0].width = 1280U;
     *            inFmt[0].width = 800U;
     *            streamId[1] = 2U;
     *            inFmt[1].width = 1280U;
     *            inFmt[1].width = 720U; \endcode */
    Fvid2_Format inFmt[VPS_ISS_CAL_MAX_STREAMS];
    /**< Specify the characteristics of streams that has to be received.
     *      Valid member of this structure are
     *      .width  - specify the width if known, else 0x0.
     *                  WARNING - Sufficient buffer should be allocated to
     *                      accommodate max line length.
     *      .height - expected number of lines, 0x0 for unknown
     *                  WARNING - Sufficient buffer should be allocated to
     *                      accommodate max lines.
     *      .pitch  - pitch
     *      .bpp    - Bits per pixel #Fvid2_BitsPerPixel
     *      .dataFormat - dataformat as per #Fvid2_DataFormat
     *                      \attention In case of CSI2 streams, this is not
     *                      valid. Please use #csi2DataFormat */
    vpsissCalStreamType_t   streamType[VPS_ISS_CAL_MAX_STREAMS];
    /**< Applicable when capturing via CSI2 interface only.
     *      Specify the streams that required to be captured */
    vpsissCalCsi2DataFormat csi2DataFormat[VPS_ISS_CAL_MAX_STREAMS];
    /**< Applicable when capturing via CSI2 interface only.
     *      Specify the streams data format */
    uint32_t                csi2VirtualChanNo[VPS_ISS_CAL_MAX_STREAMS];
    /**< Applicable when capturing via CSI2 interface only.
     *      Specify the virtual channel number to be used. Valid rage 0 - 3 */
    uint32_t                isPixProcCfgValid[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates valid pixel processing config, otherwise invalid config
     *      not used. */
    vpsissCalPixProc_t      pixProcCfg[VPS_ISS_CAL_MAX_STREAMS];
    /**< Configure pixel processing contexts. There are 4 pixel processing
     *      contexts available. */

    /* NOTE there is one instance of BYS Out, BYS In and Video Port.
     *  At any point only one configuration should be valid, otherwise, the last
     *  config would be active. */
    uint32_t                isBysOutCfgValid[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates valid BYS Out config, otherwise invalid config
     *        not used. */
    vpsissCalBysOut_t       bysOutCfg[VPS_ISS_CAL_MAX_STREAMS];
    /**< Configure BYS Out */

    uint32_t                bysInEnable[VPS_ISS_CAL_MAX_STREAMS];
    /**< Configure BYS In. */

    uint32_t                isVportCfgValid[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates valid Video Port In config, otherwise invalid config
     *        not used. */
    vpsissCalVPort_t        vportCfg[VPS_ISS_CAL_MAX_STREAMS];
    /**< Configure Video Port */

    uint32_t                writeToMem[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates that the captured stream should be written to memory.
     *      \attention Note that a stream could not be duplicated, e.g. if
     *          you require to send out a stream via VPORT and also to write
     *          into memory, its not possible. */

    uint32_t                cmplxIoId[VPS_ISS_CAL_MAX_STREAMS];
    /**< PPI Instance to be used for this stream,
         Must be less than VPS_ISS_CAL_MAX_CMPLXIO_INST */
    Ptr                     pIspArgs;
    /**< ISP Arguments, please refer the ISP specific header if any. */

    Ptr                     pAdditionalArgs;
    /**< Not used for now - should be set to NULL */
} vpsissCalCfg_t;

/**
 *  struct vpsissCalErrorCfg
 *  \brief
 *
 */
typedef struct vpsissCalErrorCfg
{
    uint32_t cmplxIoId;
    /**< Complex IO index,
         must be less than VPS_ISS_CAL_MAX_CMPLXIO_INST */
    uint32_t numErrorsToMonitor;
    /**< Specify the number of errors that driver should monitor/enable */
    vpsissCalErrorSource_t errSrc[VPS_ISS_CAL_MAX_ERROR_INTERRUPTS];
    /**< Identify the error that have to be enabled */
    vpsissErrorCallBack appCb;
    /**< A function pointer, that would be called on error conditions with
            following arguments
            const UInt32 *event     : Will point to array that hold actual error
                                        of type vpsissCalErrorSource_t and will
                                        have minimum 'numEvents' entries
            UInt32        numEvents : A positive value that indicate number of
                                        errors detected
            Ptr           arg       : A pointer provided by application while
                                        enabling the interrupt 'pAppCbArgs'

            \attention The appCb could be NULL. In which case the frame status
                        would be updated. When appCb is not NULL, the provided
                        function would be called and frame status would be
                        updated.
        */
    Ptr     pAppCbArgs;
    /**< Argument that would be passed when appCb is called. */
    Ptr     pAdditionalArgs;
    /**< Not used for now - should be set to NULL */
} vpsissCalErrorCfg_t;

/**
 *  struct vpsissCalFrameEventNotifyCfg
 *
 *  \brief CAL could be configured to notify application on end of frame or on
 *          reception of first X lines.
 *
 *  Limitation on first x lines callback : Currently this can be enabled for
 *      one stream and stream should be of type VPS_ISS_CAL_TAG_PIX_DATA
 *
 */
typedef struct vpsissCalFrameEventNotifyCfg
{
    uint32_t numStream;
    /**< Number of streams, which requires to be monitored for end of frame,
            and or first X lines */
    uint32_t streamId[VPS_ISS_CAL_MAX_STREAMS];
    /**< Specify the stream ID, which requires to be monitored */
    uint32_t notifyAfterFirstXLines[VPS_ISS_CAL_MAX_STREAMS];
    /**< Will call the application provided callback, after reception of
        number of lines specified here.
        Restriction :
            This can be supported for only VPS_ISS_CAL_MAX_X_LINE_MONITOR_CNT
            virtual channel */
    uint32_t notifyAfterEndOfFrame[VPS_ISS_CAL_MAX_STREAMS];
    /**< Will call the application provided callback, after reception of
        End Of Frame short packet */
    Fvid2_SubFrameCbFxn appCb;
    /**< Application callback */
    void *pAdditionalArgs;
    /**< Not used for now - should be set to NULL */
} vpsissCalFrameEventNotifyCfg_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  vpsissCalCfg_t_init
 *  \brief This function should be used to initialize variable of type
 *          #vpsissCalCfg_t.
 *
 *  \param cfg   A pointer of type vpsissCalCfg_t
 *  \return      None
 */
static inline void vpsissCalCfg_t_init(vpsissCalCfg_t *cfg);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static inline void vpsissCalCfg_t_init(vpsissCalCfg_t *cfg)
{
    if (NULL != cfg)
    {
        BspUtils_memset(cfg, 0x0, sizeof (vpsissCalCfg_t));
    }
}

#ifdef __cplusplus
}
#endif

#endif /* _VPS_CFG_CAL_H_ */

/* @} */
