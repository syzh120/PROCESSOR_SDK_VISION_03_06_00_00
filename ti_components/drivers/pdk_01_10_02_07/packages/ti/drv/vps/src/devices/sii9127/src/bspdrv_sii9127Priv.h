/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file bspdrv_sii9127Priv.h
 *
 *  \brief SII9127 decoder internal header file.
 */

#ifndef BSPDRV_SII9127_PRIV_H_
#define BSPDRV_SII9127_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/devices/bsp_videoDecoder.h>
#include <sii9127/bspdrv_sii9127.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* #define BSP_SII9127_USE_REG_CACHE */
/* #define BSP_SII9127_USE_AVI_FRAME_INFO */

/** \brief Driver object state - NOT IN USE. */
#define BSP_SII9127_OBJ_STATE_UNUSED        (UInt32) (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_SII9127_OBJ_STATE_IDLE          (UInt32) (1U)

/** \brief SII9127 I2C Port1 offset from Port0  */
#define BSP_SII9127_I2C_PORT1_OFFSET        (UInt32) (4U)

/** \brief SII9127 Default TMDS Core ID to use  */
#define BSP_SII9127_CORE_ID_DEFAULT         (UInt32) (1U)

/** \brief SII9127 Color Gamut I2C address */
#define BSP_SII9127_COLOR_GAMUT_I2C_ADDR    (UInt32) (0x32U)

/*
 * SII9127 Registers - I2C Port 0
 */
#define BSP_SII9127_REG_VND_IDL         (UInt32) (0x00U)
#define BSP_SII9127_REG_VND_IDH         (UInt32) (0x01U)
#define BSP_SII9127_REG_DEV_IDL         (UInt32) (0x02U)
#define BSP_SII9127_REG_DEV_IDH         (UInt32) (0x03U)
#define BSP_SII9127_REG_DEV_REV         (UInt32) (0x04U)
#define BSP_SII9127_REG_SRST0           (UInt32) (0x05U)
#define BSP_SII9127_REG_STATE           (UInt32) (0x06U)
#define BSP_SII9127_REG_SRST2           (UInt32) (0x07U)
#define BSP_SII9127_REG_SYS_CTRL1       (UInt32) (0x08U)
#define BSP_SII9127_REG_SYS_SWTCHC      (UInt32) (0x09U)
#define BSP_SII9127_REG_SYS_SWTCHC2     (UInt32) (0x0AU)
#define BSP_SII9127_REG_SRST3           (UInt32) (0x0BU)
#define BSP_SII9127_REG_CHIP_SEL        (UInt32) (0x0CU)
#define BSP_SII9127_REG_PCLK_CNT_MAX    (UInt32) (0x0FU)
#define BSP_SII9127_REG_HP_CTRL         (UInt32) (0x10U)
#define BSP_SII9127_REG_SLAVE_ADDR5     (UInt32) (0x14U)
#define BSP_SII9127_REG_SLAVE_ADDR4     (UInt32) (0x15U)
#define BSP_SII9127_REG_SLAVE_ADDR2     (UInt32) (0x18U)
#define BSP_SII9127_REG_SLAVE_ADDR3     (UInt32) (0x19U)
#define BSP_SII9127_REG_H_RESL          (UInt32) (0x3AU)
#define BSP_SII9127_REG_H_RESH          (UInt32) (0x3BU)
#define BSP_SII9127_REG_V_RESL          (UInt32) (0x3CU)
#define BSP_SII9127_REG_V_RESH          (UInt32) (0x3DU)
#define BSP_SII9127_REG_VID_DITHER      (UInt32) (0x47U)
#define BSP_SII9127_REG_VID_CTRL        (UInt32) (0x48U)
#define BSP_SII9127_REG_VID_MODE2       (UInt32) (0x49U)
#define BSP_SII9127_REG_VID_MODE        (UInt32) (0x4AU)
#define BSP_SII9127_REG_VID_BLANK1      (UInt32) (0x4BU)
#define BSP_SII9127_REG_VID_BLANK2      (UInt32) (0x4CU)
#define BSP_SII9127_REG_VID_BLANK3      (UInt32) (0x4DU)
#define BSP_SII9127_REG_DE_PIXL         (UInt32) (0x4EU)
#define BSP_SII9127_REG_DE_PIXH         (UInt32) (0x4FU)
#define BSP_SII9127_REG_DE_LINL         (UInt32) (0x50U)
#define BSP_SII9127_REG_DE_LINH         (UInt32) (0x51U)
#define BSP_SII9127_REG_VID_VTAVL       (UInt32) (0x52U)
#define BSP_SII9127_REG_VID_VFP         (UInt32) (0x53U)
#define BSP_SII9127_REG_VID_STAT        (UInt32) (0x55U)
#define BSP_SII9127_REG_VID_CH_MAP      (UInt32) (0x56U)
#define BSP_SII9127_REG_VID_CTRL1       (UInt32) (0x57U)
#define BSP_SII9127_REG_VID_HFP1        (UInt32) (0x59U)
#define BSP_SII9127_REG_VID_HFP2        (UInt32) (0x5AU)
#define BSP_SII9127_REG_VID_HSWID1      (UInt32) (0x5BU)
#define BSP_SII9127_REG_VID_HSWID2      (UInt32) (0x5CU)
#define BSP_SII9127_REG_VID_AOF         (UInt32) (0x5FU)
#define BSP_SII9127_REG_DC_STAT         (UInt32) (0x61U)
#define BSP_SII9127_REG_VID_XPM_MODE    (UInt32) (0x68U)
#define BSP_SII9127_REG_VID_XPM_BASE    (UInt32) (0x69U)
#define BSP_SII9127_REG_VID_XPM_EN      (UInt32) (0x6AU)
#define BSP_SII9127_REG_VID_XPM_BASE1   (UInt32) (0x6BU)
#define BSP_SII9127_REG_VID_XPM_BASE2   (UInt32) (0x6CU)
#define BSP_SII9127_REG_VID_XPM_THRESH  (UInt32) (0x6DU)
#define BSP_SII9127_REG_VID_XPCNT1      (UInt32) (0x6EU)
#define BSP_SII9127_REG_VID_XPCNT2      (UInt32) (0x6FU)
#define BSP_SII9127_REG_INTR_STATE      (UInt32) (0x70U)
#define BSP_SII9127_REG_INTR1           (UInt32) (0x71U)
#define BSP_SII9127_REG_INTR2           (UInt32) (0x72U)
#define BSP_SII9127_REG_INTR3           (UInt32) (0x73U)
#define BSP_SII9127_REG_INTR4           (UInt32) (0x74U)
#define BSP_SII9127_REG_INTR1_UNMASK    (UInt32) (0x75U)
#define BSP_SII9127_REG_INTR2_UNMASK    (UInt32) (0x76U)
#define BSP_SII9127_REG_INTR3_UNMASK    (UInt32) (0x77U)
#define BSP_SII9127_REG_INTR4_UNMASK    (UInt32) (0x78U)
#define BSP_SII9127_REG_INTR_CTRL       (UInt32) (0x79U)
#define BSP_SII9127_REG_IP_CTRL         (UInt32) (0x7AU)
#define BSP_SII9127_REG_INTR5           (UInt32) (0x7BU)
#define BSP_SII9127_REG_INTR6           (UInt32) (0x7CU)
#define BSP_SII9127_REG_INTR5_UNMASK    (UInt32) (0x7DU)
#define BSP_SII9127_REG_INTR6_UNMASK    (UInt32) (0x7EU)
#define BSP_SII9127_REG_INTR7           (UInt32) (0x90U)
#define BSP_SII9127_REG_INTR8           (UInt32) (0x91U)
#define BSP_SII9127_REG_INTR7_UNMASK    (UInt32) (0x92U)
#define BSP_SII9127_REG_INTR8_UNMASK    (UInt32) (0x93U)

/*
 * SII9127 Registers - I2C Port 1
 */
#define BSP_SII9127_REG_SYS_PWR_DWN_2   (UInt8) (0x3EU)
#define BSP_SII9127_REG_SYS_PWR_DWN     (UInt8) (0x3FU)
#define BSP_SII9127_REG_AVI_TYPE        (UInt8) (0x40U)
#define BSP_SII9127_REG_AVI_DBYTE15     (UInt8) (0x52U)

/*
 * SII9127 Registers - Color Gamut Port
 */
#define BSP_SII9127_REG_FACTORY_00E     (UInt32) (0x0EU)
#define BSP_SII9127_REG_FACTORY_9E5     (UInt32) (0xE5U)
#define BSP_SII9127_REG_FACTORY_A81     (UInt32) (0x81U)
#define BSP_SII9127_REG_FACTORY_A87     (UInt32) (0x87U)
#define BSP_SII9127_REG_FACTORY_A88     (UInt32) (0x88U)
#define BSP_SII9127_REG_FACTORY_A89     (UInt32) (0x89U)
#define BSP_SII9127_REG_FACTORY_A92     (UInt32) (0x92U)
#define BSP_SII9127_REG_FACTORY_A93     (UInt32) (0x93U)
#define BSP_SII9127_REG_FACTORY_A94     (UInt32) (0x94U)
#define BSP_SII9127_REG_FACTORY_A95     (UInt32) (0x95U)
#define BSP_SII9127_REG_FACTORY_AB5     (UInt32) (0xB5U)
#define BSP_SII9127_REG_FACTORY_ABB     (UInt32) (0xBBU)

/*
 * SII9127 Registers values
 */
/* PCLK stable, Clock detect, Sync Detect */
#define BSP_SII9127_VID_DETECT          (((UInt32) 1U << \
                                          0U) |          \
                                         ((UInt32) 1U << \
                                          1U) | ((UInt32) 1U << 4U))

/* Video interlace status */
#define BSP_SII9127_VID_INTERLACE       ((UInt32) 1U << 2U)

/* color format */
#define BSP_SII9127_COLOR_FORMAT_RGB    (UInt32) (0U)
#define BSP_SII9127_COLOR_FORMAT_YUV    (UInt32) (1U)

/* Select TMDS core */
#define BSP_SII9127_SEL_TMDS_CORE_0     (UInt8) (0U | \
                                                 ((UInt32) 1U << (UInt32) 3U))
#define BSP_SII9127_SEL_TMDS_CORE_1     (UInt8) (1U | \
                                                 ((UInt32) 1U << (UInt32) 3U))
#define BSP_SII9127_SEL_TMDS_CORE_2     (UInt8) (2U | \
                                                 ((UInt32) 1U << (UInt32) 3U))
#define BSP_SII9127_SEL_TMDS_CORE_3     (UInt8) (3U | \
                                                 ((UInt32) 1U << (UInt32) 3U))

/* Select DDC Port */
#define BSP_SII9127_SEL_DDC_PORT_0      (UInt8) ((UInt32) 1U << 4U)
#define BSP_SII9127_SEL_DDC_PORT_1      (UInt8) ((UInt32) 1U << 5U)
#define BSP_SII9127_SEL_DDC_PORT_2      (UInt8) ((UInt32) 1U << 6U)
#define BSP_SII9127_SEL_DDC_PORT_3      (UInt8) ((UInt32) 1U << 7U)

/* F_xtal frequency in Khz  */
#define BSP_SII9127_FXTAL_KHZ           (UInt32) (27000U)

/* HDMI AVI InfoFrame Packet info  */

/* color space */
#define BSP_SII9127_AVI_INFO_COLOR_RGB444       (UInt32) (0U)
#define BSP_SII9127_AVI_INFO_COLOR_YUV444       (UInt32) (1U)
#define BSP_SII9127_AVI_INFO_COLOR_YUV422       (UInt32) (2U)

/* color imetric */
#define BSP_SII9127_AVI_INFO_CMETRIC_NO_DATA    (UInt32) (0U)
#define BSP_SII9127_AVI_INFO_CMETRIC_ITU601     (UInt32) (1U)
#define BSP_SII9127_AVI_INFO_CMETRIC_ITU709     (UInt32) (2U)

/* pixel repition */
#define BSP_SII9127_AVI_INFO_PIXREP_NONE        (UInt32) (0U)
#define BSP_SII9127_AVI_INFO_PIXREP_2X          (UInt32) (1U)
#define BSP_SII9127_AVI_INFO_PIXREP_4X          (UInt32) (3U)

/* AVI packet info values */
#define BSP_SII9127_AVI_INFO_PACKET_CODE        (UInt8) (0x82U)
#define BSP_SII9127_AVI_INFO_VERSION_CODE       (UInt8) (0x02U)
#define BSP_SII9127_AVI_INFO_PACKET_LENGTH      (UInt8) (0x0DU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief SII9127 driver handle object.
 */
typedef struct
{
    UInt32                    state;
    /**< Handle state - used or free. */
    UInt32                    handleId;
    /**< Handle ID, 0..BSP_DEVICE_MAX_HANDLES-1. */
    BspOsal_SemHandle         lock;
    /**< Driver lock. */
    Bsp_VidDecCreateParams    createPrms;
    /**< Create time arguments. */
    Bsp_VidDecVideoModeParams modePrms;
    /**< Video decoder mode parameters. */
#ifdef BSP_SII9127_USE_REG_CACHE
    UInt8                     regCache[2U][256U];
    /**< Register read cache - two ports and 256 address range per I2C port. */
#endif
} Bsp_Sii9127HandleObj;

/**
 *  \brief SII9127 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle    lock;
    /**< Global driver lock. */
    Bsp_Sii9127HandleObj handlePool[BSP_DEVICE_MAX_HANDLES];
    /**< Handle objects. */
} Bsp_Sii9127Obj;

/**
 *  \brief Information that is parsed from HDMI AVIInfoFrame packet.
 */
typedef struct
{
    UInt32 colorSpace;
    /**< RGB444 ot YUV422 or YUV422. */
    UInt32 colorImetric;
    /**< BT709 or BT601. */
    UInt32 pixelRepeat;
    /**< 1x, 2x, 4x. */
} Bsp_Sii9127AviInfoFrame;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 Bsp_sii9127Reset(Bsp_Sii9127HandleObj *pObj);
Int32 Bsp_sii9127GetChipId(Bsp_Sii9127HandleObj         *pObj,
                           const Bsp_VidDecChipIdParams *pPrm,
                           Bsp_VidDecChipIdStatus       *pStatus);

Int32 Bsp_sii9127SetVideoMode(Bsp_Sii9127HandleObj            *pObj,
                              const Bsp_VidDecVideoModeParams *pPrm);
Int32 Bsp_sii9127GetVideoStatus(Bsp_Sii9127HandleObj              *pObj,
                                const Bsp_VidDecVideoStatusParams *pPrm,
                                Bsp_VidDecVideoStatus             *pStatus);

Int32 Bsp_sii9127Start(Bsp_Sii9127HandleObj *pObj);
Int32 Bsp_sii9127Stop(Bsp_Sii9127HandleObj *pObj);

Int32 Bsp_sii9127RegWrite(Bsp_Sii9127HandleObj          *pObj,
                          const Bsp_VidDecRegRdWrParams *pPrm);
Int32 Bsp_sii9127RegRead(Bsp_Sii9127HandleObj    *pObj,
                         Bsp_VidDecRegRdWrParams *pPrm);

Int32 Bsp_sii9127ResetRegCache(Bsp_Sii9127HandleObj *pObj);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSPDRV_SII9127_PRIV_H_ */
