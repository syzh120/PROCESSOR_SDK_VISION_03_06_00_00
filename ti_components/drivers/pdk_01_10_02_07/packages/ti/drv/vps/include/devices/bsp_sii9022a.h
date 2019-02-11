/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2015
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
 * \ingroup BSP_DRV_DEVICE_VID_ENC_API
 * \defgroup BSP_DRV_DEVICE_VID_ENC_SII9022A_API SII9022A Video Encoder API
 *
 *  This modules define API specific to SII9022A video encoder device.
 *
 * @{
 */

/**
 *  \file bsp_sii9022a.h
 *
 *  \brief SII9022A Video Encoder API
 */

#ifndef BSP_SII9022A_H_
#define BSP_SII9022A_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/devices/bsp_videoEncoder.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \addtogroup BSP_DRV_IOCTL_SII9022A
 *  @{
 */

/**
 *  \brief Query hot plug detect (HPD) for HDMI cable connect or disconnect.
 *
 *
 *  \param cmdArgs       [OUT]  Bsp_Sii9022aHdmiChipId *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID_SOK on success, else failure. Status= TRUE means cable
 *  connected else not connected
 */
#define IOCTL_BSP_SII9022A_GET_DETAILED_CHIP_ID \
    (BSP_VID_ENC_IOCTL_BASE + 0x1000U)

/**
 *  \brief Query Hot Plug Detect status
 *
 *  \param cmdArgs       [OUT]  Bsp_Sii9022aHpdParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID_SOK on success, else failure.
 */
#define IOCTL_BSP_SII9022A_QUERY_HPD \
    (BSP_VID_ENC_IOCTL_BASE + 0x1001U)

/**
 *  \brief Set Configuration in HDMI 9022A
 *
 *  \param cmdArgs       [IN]   const Bsp_Sii9022aParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID_SOK on success, else failure.
 */
#define IOCTL_BSP_SII9022A_SET_PARAMS \
    (BSP_VID_ENC_IOCTL_BASE + 0x1002U)

/**
 *  \brief Get Configuration in HDMI 9022A
 *
 *  \param cmdArgs       [IN]   Bsp_Sii9022aParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID_SOK on success, else failure.
 */
#define IOCTL_BSP_SII9022A_GET_PARAMS \
    (BSP_VID_ENC_IOCTL_BASE + 0x1003U)

/**
 * \brief Enum defining output type
 */
typedef enum
{
    BSP_SII9022A_HDMI_RGB = 0,
    /**< Output format is RGB over HDMI interface */
    BSP_SII9022A_HDMI_YUV444,
    /**< Output format is YUV444 over HDMI interface */
    BSP_SII9022A_HDMI_YUV422,
    /**< Output format is YUV422 over HDMI interface */
    BSP_SII9022A_DVI_RGB,
    /**< Output format is RGB over DVI interface */
    BSP_SII9022A_MAX_FORMAT
    /**< Max output format */
} Bsp_Sii9022AOutputFormat;

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure for getting detailed HDMI chip Id.
 */
typedef struct
{
    UInt32 deviceId;
    /**< Device Id TPI. */
    UInt32 deviceProdRevId;
    /**< Device Production Revision Id TPI. */
    UInt32 tpiRevId;
    /**< TPI Revision Id TPI. */
    UInt32 hdcpRevTpi;
    /**< HDCP revision TPI. */
} Bsp_Sii9022aHdmiChipId;

/**
 *  \brief Structure for hot plug detection parameters.
 *
 *  It is used to get the hpd parameters using
 *  IOCTL_BSP_SII9022A_QUERY_HPD ioctl.
 */
typedef struct
{
    UInt32 hpdEvtPending;
    /**< Hot Plug Connection Event Pending. */
    UInt32 busError;
    /**< Receiver Sense Event Pending or CTRL Bus Error. */
    UInt32 hpdStatus;
    /**< Hot Plug Pin Current Status. */
} Bsp_Sii9022aHpdParams;

typedef struct
{
    UInt32 outputFormat;
    /**< Type of the OUTPUT i.e. HDMI of DVI #Bsp_Sii9022AOutputFormat. */
} Bsp_Sii9022aParams;

/* ========================================================================== */
/*                         Functions                                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif  /* #ifndef BSP_SII9022A_H_ */

#endif

/* @} */
