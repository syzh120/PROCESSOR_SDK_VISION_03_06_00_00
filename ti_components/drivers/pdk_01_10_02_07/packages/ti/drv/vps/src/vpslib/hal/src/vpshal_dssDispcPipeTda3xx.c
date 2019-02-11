/* =============================================================================
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
 *  \file vpshal_dssDispcPipeTda3xx.c
 *
 *  \brief VPS DSS Dispc video/gfx/WB pipeline HAL file.
 *  This file implements the HAL APIs of the DSS DISPC Pipelines
 *  (Video/Graphics/WriteBack).
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/csl/soc.h>

#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_dss.h>

#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/include/dss/vps_cfgDss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_dssDispcVid.h>

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_VidRegOffset
 *  \brief structure to store register offsets of each pipeline.
 */
typedef struct
{
    UInt32 vidBaseAdd;
    /**< offset of Base Address register for this instance */
    UInt32 vidPos;
    /**< offset of Position register for this instance */
    UInt32 vidSize;
    /**< offset of Video Window Size register for this instance */
    UInt32 vidAttrib;
    /**< offset of attributes register for this instance */
    UInt32 bufThresh;
    /**< offset of buffer threshold register for this instance */
    UInt32 bufSizeStat;
    /**< offset of Buffer Size status register for this instance */
    UInt32 rowInc;
    /**< offset of Row Increment register for this instance */
    UInt32 pixelInc;
    /**< offset of Pixel Increment register for this instance */
    UInt32 firH;
    /**< offset of Horizontal FIR(resize factor of scaling) register
     *   for this instance */
    UInt32 firV;
    /**< offset of Vertical FIR(resize factor of scaling) register
     *   for this instance */
    UInt32 pictSize;
    /**< offset of Picture Size register for this instance */
    UInt32 accumuH;
    /**< offset of Horizontal resize accumulator Size register for this instance
     *  [0] for Ping and [1] for pong with external trigger , based on field
     *  polarity */
    UInt32 accumuV;
    /**< offset of Vertical resize accumulator Size register for this instance
     *  [0] for Ping and [1] for pong with external trigger , based on field
     *  polarity */
    UInt32 firCoefH;
    /**< offset of resizer filter coefficient register for this instance */
    UInt32 firCoefHV;
    /**< offset of resizer filter coefficient register for this instance */
    UInt32 convCoef[7];
    /**< offset of array of color conversion coeff registers for this
     *   instance, coeff0 - coeff6 */
    UInt32 firCoefV;
    /**< offset of resizer filter coefficient register for this instance */
    UInt32 preload;
    /**< offset of preload register for this instance */
    UInt32 vidBaseAddUv;
    /**< offset of Base Address of UV bufferregister for this instance */
    UInt32 vidAttrib2;
    /**< offset of attributes2 register for this instance */
    UInt32 firH2;
    /**< offset of Horizontal FIR(resize factor of scaling) fir cb and cr
     *   register for this instance */
    UInt32 firV2;
    /**< offset of Vertical FIR(resize factor of scaling) fir cb and cr
     *   register for this instance */
    UInt32 accumuH2;
    /**< offset of Horizontal resize accumulator Size register for this instance
     *   it is used for cb and cr settings [0] for Ping and [1] for pong
     *   with external trigger , based on field
     *   polarity */
    UInt32 accumuV2;
    /**< offset of Vertical resize accumulator Size register for this instance
     *   it is used for cb and cr settings [0] for Ping and [1] for pong
     *   with external trigger , based on field
     *   polarity */
    UInt32 firCoefH0;
    /**< offset of Horizontal resizer filter coefficient base register for this
     *   instance, used for ARGB and Y setting.*/
    UInt32 firCoefH0_C;
    /**< offset of Horizontal resizer filter coefficient register for this
     *   instance it is used for Cb and Cr settings in case of YUV formats*/
    UInt32 firCoefH12;
    /**< offset of Horizontal resizer filter coefficient register for this
     *  instance,used for ARGB and Y setting.*/
    UInt32 firCoefV0;
    /**< offset of Vertical resizer filter coefficient base register for this
     *  instance, used for ARGB and Y setting.*/
    UInt32 firCoefV12;
    /**< offset of Vertical resizer filter coefficient base register for this
     *  instance,used for ARGB and Y setting.*/
    UInt32 firCoefH12_C;
    /**< offset of Horizontal resizer filter coefficient register for this
     *  instance, it is used for Cb and Cr settings in case of YUV formats*/
    UInt32 firCoefV0_C;
    /**< offset of Vertical resizer filter coefficient register for this
     *  instance,it is used for Cb and Cr settings in case of YUV formats*/
    UInt32 firCoefV12_C;
    /**< offset of Vertical resizer filter coefficient register for this
     *  instance,it is used for Cb and Cr settings in case of YUV formats*/
    UInt32 mflagThre;
    /**< offset of Mflag Threshold register for this instance */
    UInt32 clutTable;
    /**< offset for the clut table */
} VpsHal_VidRegOffset;

/**
 *  struct VpsHal_dssDispcVidObj
 *  \brief Per instance information about each Video Pipeline module.
 */
typedef struct
{
    UInt32              halId;
    /**< Instance number/ID */
    UInt32              openCnt;
    /**< Counter to keep track of number of open calls for an instance */
    VpsHal_VidRegOffset regOffset;
    /**< Structure to store offsets of all the registers related to Overlay */
    Vps_DssCscCoeff     cscCoeff;
    /**< Structure to store store the csc coefficients for the pipeline */
} VpsHal_DssDispcVidObj;

/* Scalar Coeff */
typedef struct {
    Int32 firhc2;
    Int32 firhc1;
    Int32 firhc0;
} VpsHal_DssScCoeff;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 halDssVidInitInstance(VpsHal_DssDispcVidObj *dispcVidObj);

static void halDssVidSetFormat(VpsHal_Handle handle, UInt32 dataFmt);

static void halDssVidConfCscFullRange(VpsHal_Handle handle,
                                      UInt32        cscFullRngEnable);

static void halDssVidConfCscCoeff(VpsHal_Handle          handle,
                                  const Vps_DssCscCoeff *coeff);

static void halDssVidConfCscEnable(VpsHal_Handle handle,
                                   UInt32        cscEnable);

const VpsHal_DssScCoeff *halDssVidGetScalarCoeff(UInt32 inSize,
                                                 UInt32 outSize,
                                                 UInt32 verticalTaps);

static void halDssVidSetScalerCoeff(VpsHal_Handle            handle,
                                    const VpsHal_DssScCoeff *vCoef,
                                    const VpsHal_DssScCoeff *hCoef,
                                    const VpsHal_DssScCoeff *vChromaCoef,
                                    const VpsHal_DssScCoeff *hChromaCoef);

static void halDssVidConfFir(VpsHal_Handle handle,
                             UInt32        inSizeX,
                             UInt32        inSizeY,
                             UInt32        outSizeX,
                             UInt32        outSizeY);

static void halDssVidConfFir2(VpsHal_Handle handle,
                              UInt32        inSizeX,
                              UInt32        inSizeY,
                              UInt32        outSizeX,
                              UInt32        outSizeY);

static void halDssVidConfVerticalTapsEnable(VpsHal_Handle handle,
                                            UInt32        verticalTaps);

static void halDssVidConfScalerEnable(VpsHal_Handle handle,
                                      UInt32        scalerEnable);

static void halDssVidSetVc1Coeff(VpsHal_Handle handle,
                                 UInt32        rangeY,
                                 UInt32        rangeUV);

static void halDssVidVc1Enable(VpsHal_Handle handle,
                               UInt32        vc1Enable);

static void halDssVidSetOutRes(VpsHal_Handle handle,
                               UInt32        outHeight,
                               UInt32        outWidth);

static void halDssVidSetPos(VpsHal_Handle handle,
                            UInt32        posY,
                            UInt32        posX);

static void halDssVidSetInRes(VpsHal_Handle handle,
                              UInt32        inSizeY,
                              UInt32        inSizeX);

static void halDssVidDmaBufThreConf(VpsHal_Handle handle,
                                    UInt32        bufLowThreshold,
                                    UInt32        bufHighThreshold,
                                    UInt32        bufPreloadType);

static void halDssVidDmaPixelRowIncConf(VpsHal_Handle handle,
                                        UInt32        rowInc,
                                        UInt32        pixelInc);

static void halDssVidDmaConfArbitration(VpsHal_Handle handle,
                                        UInt32        arbitration);

static void halDssVidDmaConfSelfRefresh(VpsHal_Handle handle,
                                        UInt32        selfRefreshEnable);

static void halDssVidConfRepliEnable(VpsHal_Handle handle,
                                     UInt32        repliEnable);

static void halDssVidConfAntiFlickerEnable(VpsHal_Handle handle,
                                           UInt32        antiFlickerEnable);

static void halDssVidConfNibbleMode(VpsHal_Handle handle,
                                    UInt32        nibblemode);

static void halDssVidConfClutTable(VpsHal_Handle handle,
                                   const UInt32 *clutdata);

static void halDssWbIdleConfig(VpsHal_Handle handle,
                               UInt32  idleNumber,
                               UInt32  idleSize);

static void halDssWbSetMode(VpsHal_Handle handle,
                            UInt32        wbMode);

static void halDssWbSetPosition(VpsHal_Handle handle,
                                UInt32        inPosX,
                                UInt32        inPosY);

static void halDssWbSetInNode(VpsHal_Handle handle,
                              UInt32        inNode);

static void halDssWbSetRegionBased(VpsHal_Handle handle,
                                   UInt32        enable);

static void halDssGetChromaRes(UInt32 dataFmt, UInt32 width, UInt32 height,
                               UInt32 *chromaWidth, UInt32 *chromaHeight);

Int32 halDssConvFvid2DataFmt(UInt32 handleId, UInt32 fvid2Fmt);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  DISP PIPE  objects - Module variable to store information about each video
 *  piepline instance .Note: If the number of Video pipeline instance increase,
 *  then VPSHAL_DSS_DISPC_PIPE_MAX_INST macro should be changed accordingly.
 */
static VpsHal_DssDispcVidObj   gDispcVidHalObj[VPSHAL_DSS_DISPC_PIPE_MAX_INST];

/* Coefficients for BT601-5 YUV to RGB conversion */
/* Uncomment below csc coefficients to set the limited range coeff
 * by default, or pass these parameters from application using the ioctl
 * IOCTL_VPS_DISP_SET_CSC_COEFF.

static const Vps_DssCscCoeff   gVidCscCoeff =
{298,            409,             0,
 298,            -((Int16) 208),  -((Int16) 100),
 298,            0,               517,
 -((Int16) 256), -((Int16) 2048), -((Int16) 2048)};
 */

/* Below is the full range csc conversion parameters. */
static const Vps_DssCscCoeff   gVidCscCoeff =
{256,            359,             0,
 256,            -((Int16) 183),  -((Int16) 87),
 256,            0,               454,
   0,           -((Int16) 2048), -((Int16) 2048)};

/**
 * Coefficients for RGB to BT601-5 YUV conversion.
 *
 */
/* Uncomment below csc coefficients to set the limited range coeff
 * by default, or pass these parameters from application using the ioctl
 * IOCTL_VPS_DISP_SET_CSC_COEFF.

static const Vps_DssCscCoeff   gWbCscCoeff =
{66,            129,           25,
 112,           -((Int16) 94), -((Int16) 18),
 -((Int16) 38), -((Int16) 74), 112,
 0,             2048,          2048};
 */

/* Below is the full range csc conversion parameters. */
static const Vps_DssCscCoeff   gWbCscCoeff =
{76,            150,           29,
 128,           -((Int16) 107), -((Int16) 20),
 -((Int16) 43), -((Int16) 84), 128,
 0,             2048,          2048};

/**
 * Scalar coefficient for different scaling ratios.
 *
 */
static const VpsHal_DssScCoeff gDispcCoefUpScale[16] =
{
    {0, 0,   512},
    {0, 0,   512},
    {0, 64,  448},
    {0, 64,  448},
    {0, 128, 384},
    {0, 128, 384},
    {0, 192, 320},
    {0, 192, 320},
    {0, 0,   256},
    {0, 0,   0  },
    {0, 0,   0  },
    {0, 0,   0  },
    {0, 0,   0  },
    {0, 0,   0  },
    {0, 0,   0  },
    {0, 0,   0  },
};

static const VpsHal_DssScCoeff gDispcCoefDownScaleM10[16] =
{
    {-((Int16) 16), 72,             400},
    {-((Int16) 20), 96,             398},
    {-((Int16) 24), 120,            396},
    {-((Int16) 28), 148,            384},
    {-((Int16) 32), 176,            372},
    {-((Int16) 34), 204,            354},
    {-((Int16) 36), 232,            336},
    {-((Int16) 34), 260,            312},
    {0,             -((Int16) 32),  288},
    {0,             -((Int16) 26),  312},
    {0,             -((Int16) 20),  336},
    {-((Int16) 2),  -((Int16) 10),  354},
    {-((Int16) 4),  0,              372},
    {-((Int16) 8),  16,             384},
    {-((Int16) 12), 32,             396},
    {-((Int16) 14), 52,             398},
};

static const VpsHal_DssScCoeff gDispcCoefDownScaleM14[16] =
{
    {-((Int16) 8), 120, 288},
    {-((Int16) 6), 134, 286},
    {-((Int16) 4), 148, 284},
    {-((Int16) 2), 164, 280},
    {0,            180, 276},
    {6,            194, 266},
    {12,           208, 256},
    {18,           220, 244},
    {0,            24,  232},
    {-((Int16) 2), 32,  244},
    {-((Int16) 4), 40,  256},
    {-((Int16) 6), 52,  266},
    {-((Int16) 8), 64,  276},
    {-((Int16) 8), 78,  280},
    {-((Int16) 8), 92,  284},
    {-((Int16) 8), 106, 286},
};

static const VpsHal_DssScCoeff gDispcCoefDownScaleM19[16] =
{
    {12, 128, 232},
    {14, 140, 232},
    {16, 152, 232},
    {22, 160, 226},
    {28, 168, 220},
    {34, 176, 218},
    {40, 184, 216},
    {48, 192, 208},
    {0,  56,  200},
    {0,  64,  208},
    {0,  72,  216},
    {2,  82,  218},
    {4,  92,  220},
    {4,  100, 226},
    {4,  108, 232},
    {8,  118, 232},
};

static const VpsHal_DssScCoeff gDispcCoefDownScaleM22[16] =
{
    {16, 132, 216},
    {20, 140, 216},
    {24, 148, 216},
    {30, 156, 214},
    {36, 164, 212},
    {42, 172, 208},
    {48, 180, 204},
    {56, 186, 198},
    {0,  64,  192},
    {0,  72,  198},
    {0,  80,  204},
    {2,  88,  208},
    {4,  96,  212},
    {8,  104, 214},
    {12, 112, 216},
    {14, 122, 216},
};

static const VpsHal_DssScCoeff gDispcCoefDownScaleM26[16] =
{
    {24, 132, 200},
    {28, 138, 202},
    {32, 144, 204},
    {38, 152, 202},
    {44, 160, 200},
    {50, 166, 196},
    {56, 172, 192},
    {64, 178, 188},
    {0,  72,  184},
    {2,  80,  188},
    {4,  88,  192},
    {6,  94,  196},
    {8,  100, 200},
    {12, 108, 202},
    {16, 116, 204},
    {20, 124, 202},
};

static const VpsHal_DssScCoeff gDispcCoefDownScale3TapM10[16] =
{
    {0, 40,            432},
    {0, 62,            424},
    {0, 84,            416},
    {0, 110,           396},
    {0, 136,           376},
    {0, 166,           348},
    {0, 196,           320},
    {0, 226,           288},
    {0, 0,             256},
    {0, -((Int16) 2),  0  },
    {0, -((Int16) 4),  0  },
    {0, -((Int16) 2),  0  },
    {0, 0,             0  },
    {0, 6,             0  },
    {0, 12,            0  },
    {0, 26,            0  },
};

static const VpsHal_DssScCoeff gDispcCoefDownScale3TapM14[16] =
{
    {0, 80,  352},
    {0, 100, 348},
    {0, 120, 344},
    {0, 142, 334},
    {0, 164, 324},
    {0, 186, 310},
    {0, 208, 296},
    {0, 232, 276},
    {0, 0,   256},
    {0, 4,   0  },
    {0, 8,   0  },
    {0, 16,  0  },
    {0, 24,  0  },
    {0, 36,  0  },
    {0, 48,  0  },
    {0, 64,  0  },
};

static const VpsHal_DssScCoeff gDispcCoefDownScale3TapM19[16] =
{
    {0, 96,  320},
    {0, 114, 318},
    {0, 132, 316},
    {0, 152, 310},
    {0, 172, 304},
    {0, 194, 292},
    {0, 216, 280},
    {0, 236, 268},
    {0, 0,   256},
    {0, 8,   0  },
    {0, 16,  0  },
    {0, 26,  0  },
    {0, 36,  0  },
    {0, 50,  0  },
    {0, 64,  0  },
    {0, 80,  0  },
};

static const VpsHal_DssScCoeff gDispcCoefDownScale3TapM22[16] =
{
    {0, 100, 312},
    {0, 118, 310},
    {0, 136, 308},
    {0, 156, 302},
    {0, 176, 296},
    {0, 196, 286},
    {0, 216, 276},
    {0, 236, 266},
    {0, 0,   256},
    {0, 10,  0  },
    {0, 20,  0  },
    {0, 30,  0  },
    {0, 40,  0  },
    {0, 54,  0  },
    {0, 68,  0  },
    {0, 84,  0  },
};

static const VpsHal_DssScCoeff gDispcCoefDownScale3TapM26[16] =
{
    {0, 104, 304},
    {0, 122, 300},
    {0, 140, 296},
    {0, 160, 292},
    {0, 180, 288},
    {0, 198, 282},
    {0, 216, 276},
    {0, 236, 266},
    {0, 0,   256},
    {0, 10,  0  },
    {0, 20,  0  },
    {0, 32,  0  },
    {0, 44,  0  },
    {0, 60,  0  },
    {0, 76,  0  },
    {0, 90,  0  },
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsHal_dssVidInit
 *  \brief DISPC VID HAL init function.
 *
 *  Initializes VID objects, gets the register overlay offsets for DISPC VID
 *  registers.
 *  This function should be called before calling any of DISPC VID HAL API's.
 *
 *  \param numInst          Number of instance objects to be initialized
 *  \param instPrms         Pointer to the instance parameter containing
 *                          instance specific information. If the number of
 *                          instance is greater than 1, then this pointer
 *                          should point to an array of init parameter
 *                          structure of size numInst.
 *                          This parameter should not be NULL.
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssVidInit(UInt32                           numInst,
                        const VpsHal_DispcVidInstParams *instPrms,
                        Ptr                              arg)
{
    Int32  retVal = BSP_SOK;
    UInt32 instCnt;
    VpsHal_DssDispcVidObj *dispcVidObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= VPSHAL_DSS_DISPC_PIPE_MAX_INST));
    GT_assert(VpsHalTrace, (instPrms != NULL));

    /* Initialize DISPC VID Objects to zero */
    BspUtils_memset(gDispcVidHalObj, 0, sizeof (gDispcVidHalObj));

    for (instCnt = 0; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  (instPrms[instCnt].halId < VPSHAL_DSS_DISPC_VID_INST_ID_MAX));

        dispcVidObj        = &gDispcVidHalObj[instCnt];
        dispcVidObj->halId = instPrms[instCnt].halId;

        /* Initialize the instance */
        retVal += halDssVidInitInstance(dispcVidObj);
    }

    return (retVal);
}

/**
 *  VpsHal_dssVidDeInit
 *  \brief DSS DISPC VID HAL exit function.
 *
 *  Currently this function does not do anything.
 *
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssVidDeInit(Ptr arg)
{
    UInt32 instCnt;

    for (instCnt = 0; instCnt < VPSHAL_DSS_DISPC_PIPE_MAX_INST; instCnt++)
    {
        gDispcVidHalObj[instCnt].halId   = 0;
        gDispcVidHalObj[instCnt].openCnt = 0;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_dssVidOpen
 *  \brief Returns the handle to the requested DISPC VID instance.
 *
 *  This function should be called prior to calling any of the DISPC VID HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param halId            Requested DISPC VID instance.
 *
 *  \return                 Returns DISPC VID instance handle on success else
 *                          returns NULL.
 */
VpsHal_Handle VpsHal_dssVidOpen(const VpsHal_DispcVidOpenParams *openPrms)
{
    UInt32        cnt;
    VpsHal_Handle handle = NULL;

    /* Check if instance number is valid */
    GT_assert(VpsHalTrace, (NULL != openPrms));
    GT_assert(VpsHalTrace, (openPrms->halId < VPSHAL_DSS_DISPC_VID_INST_ID_MAX));

    for (cnt = 0; cnt < VPSHAL_DSS_DISPC_PIPE_MAX_INST; cnt++)
    {
        /* Return the matching instance handle */
        if (openPrms->halId == gDispcVidHalObj[cnt].halId)
        {
            /* Check whether some one has already opened this instance */
            if (0U == gDispcVidHalObj[cnt].openCnt)
            {
                handle = (VpsHal_Handle) & gDispcVidHalObj[cnt];
                gDispcVidHalObj[cnt].openCnt++;
            }
            break;
        }
    }

    return (handle);
}

/**
 *  VpsHal_dssVidClose
 *  \brief Closes the DISPC VID HAL instance.
 *
 *  Currently this function does not do anything. It is provided in case
 *  in the future resource management is done by individual HAL - using
 *  counters.
 *
 *  \param handle           Valid handle returned by VpsHal_dssVidOpen
 *                          function
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssVidClose(VpsHal_Handle handle)
{
    Int32 retVal = BSP_EFAIL;
    VpsHal_DssDispcVidObj *dispcVidObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    /* Decrement the open count */
    if (dispcVidObj->openCnt > 0U)
    {
        dispcVidObj->openCnt--;
        retVal = BSP_SOK;
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_004)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-855) DOX_REQ_TAG(PDK-856) DOX_REQ_TAG(PDK-857)
 *          DOX_REQ_TAG(PDK-858)
 */
/**
 *  halDssVidInitInstance
 *  Initialize the DISPC VID instance by updating the register offsets
 */
static Int32 halDssVidInitInstance(VpsHal_DssDispcVidObj *dispcVidObj)
{
    Int32  retVal = BSP_SOK;
    UInt32 baseAddr;

    switch (dispcVidObj->halId)
    {
        case VPSHAL_DSS_DISPC_VID1:
            baseAddr = SOC_DISPC_VID1_BASE;
            break;
        case VPSHAL_DSS_DISPC_VID2:
            baseAddr = SOC_DISPC_VID2_BASE;
            break;
        case VPSHAL_DSS_DISPC_GFX:
            baseAddr = SOC_DISPC_GFX1_BASE;
            break;
        case VPSHAL_DSS_DISPC_WB1:
            baseAddr = SOC_DISPC_WB_BASE;
            break;
        default:
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
            break;
    }
    switch (dispcVidObj->halId)
    {
        case VPSHAL_DSS_DISPC_VID1:
        case VPSHAL_DSS_DISPC_VID2:
            dispcVidObj->regOffset.vidBaseAdd = baseAddr + DSS_VID_BA(0);
            dispcVidObj->regOffset.vidPos     = baseAddr + DSS_VID_POSITION;
            dispcVidObj->regOffset.vidSize    = baseAddr + DSS_VID_SIZE;
            dispcVidObj->regOffset.vidAttrib  = baseAddr + DSS_VID_ATTRIBUTES;
            dispcVidObj->regOffset.bufThresh  = baseAddr +
                                                DSS_VID_BUF_THRESHOLD;
            dispcVidObj->regOffset.bufSizeStat = baseAddr +
                                                 DSS_VID_BUF_SIZE_STATUS;
            dispcVidObj->regOffset.rowInc   = baseAddr + DSS_VID_ROW_INC;
            dispcVidObj->regOffset.pixelInc = baseAddr + DSS_VID_PIXEL_INC;
            dispcVidObj->regOffset.firH     = baseAddr + DSS_VID_FIRH;
            dispcVidObj->regOffset.firV     = baseAddr + DSS_VID_FIRV;
            dispcVidObj->regOffset.pictSize = baseAddr +
                                              DSS_VID_PICTURE_SIZE;
            dispcVidObj->regOffset.accumuH      = baseAddr + DSS_VID_ACCUH(0);
            dispcVidObj->regOffset.accumuV      = baseAddr + DSS_VID_ACCUV(0);
            dispcVidObj->regOffset.convCoef[0]  = baseAddr + DSS_VID_CONV_COEF0;
            dispcVidObj->regOffset.convCoef[1]  = baseAddr + DSS_VID_CONV_COEF1;
            dispcVidObj->regOffset.convCoef[2]  = baseAddr + DSS_VID_CONV_COEF2;
            dispcVidObj->regOffset.convCoef[3]  = baseAddr + DSS_VID_CONV_COEF3;
            dispcVidObj->regOffset.convCoef[4]  = baseAddr + DSS_VID_CONV_COEF4;
            dispcVidObj->regOffset.convCoef[5]  = baseAddr + DSS_VID_CONV_COEF5;
            dispcVidObj->regOffset.convCoef[6]  = baseAddr + DSS_VID_CONV_COEF6;
            dispcVidObj->regOffset.preload      = baseAddr + DSS_VID_PRELOAD;
            dispcVidObj->regOffset.vidBaseAddUv = baseAddr + DSS_VID_BA_UV(0);
            dispcVidObj->regOffset.vidAttrib2   = baseAddr +
                                                  DSS_VID_ATTRIBUTES2;
            dispcVidObj->regOffset.firH2     = baseAddr + DSS_VID_FIRH2;
            dispcVidObj->regOffset.firV2     = baseAddr + DSS_VID_FIRV2;
            dispcVidObj->regOffset.accumuH2  = baseAddr + DSS_VID_ACCUH2(0);
            dispcVidObj->regOffset.accumuV2  = baseAddr + DSS_VID_ACCUV2(0);
            dispcVidObj->regOffset.mflagThre = baseAddr +
                                               DSS_VID_MFLAG_THRESHOLD;
            dispcVidObj->regOffset.clutTable = baseAddr + DSS_VID_CLUT;
            dispcVidObj->regOffset.firCoefH0 = baseAddr +
                                               DSS_VID_FIR_COEF_H0(0);
            dispcVidObj->regOffset.firCoefH0_C = baseAddr +
                                                 DSS_VID_FIR_COEF_H0_C(0);
            dispcVidObj->regOffset.firCoefH12 = baseAddr +
                                                DSS_VID_FIR_COEF_H12(0);
            dispcVidObj->regOffset.firCoefV0 = baseAddr +
                                               DSS_VID_FIR_COEF_V0(0);
            dispcVidObj->regOffset.firCoefV12 = baseAddr +
                                                DSS_VID_FIR_COEF_V12(0);
            dispcVidObj->regOffset.firCoefH12_C = baseAddr +
                                                  DSS_VID_FIR_COEF_H12_C(0);
            dispcVidObj->regOffset.firCoefV0_C = baseAddr +
                                                 DSS_VID_FIR_COEF_V0_C(0);
            dispcVidObj->regOffset.firCoefV12_C = baseAddr +
                                                  DSS_VID_FIR_COEF_V12_C(0);
            break;

        case VPSHAL_DSS_DISPC_GFX:
            dispcVidObj->regOffset.vidBaseAdd = baseAddr + DSS_GFX_BA(0);
            dispcVidObj->regOffset.vidPos     = baseAddr + DSS_GFX_POSITION;
            dispcVidObj->regOffset.vidSize    = baseAddr + DSS_GFX_SIZE;
            dispcVidObj->regOffset.vidAttrib  = baseAddr + DSS_GFX_ATTRIBUTES;
            dispcVidObj->regOffset.bufThresh  = baseAddr +
                                                DSS_GFX_BUF_THRESHOLD;
            dispcVidObj->regOffset.bufSizeStat = baseAddr +
                                                 DSS_GFX_BUF_SIZE_STATUS;
            dispcVidObj->regOffset.rowInc    = baseAddr + DSS_GFX_ROW_INC;
            dispcVidObj->regOffset.pixelInc  = baseAddr + DSS_GFX_PIXEL_INC;
            dispcVidObj->regOffset.preload   = baseAddr + DSS_GFX_PRELOAD;
            dispcVidObj->regOffset.mflagThre = baseAddr +
                                               DSS_GFX_MFLAG_THRESHOLD;
            dispcVidObj->regOffset.clutTable = baseAddr + DSS_GFX_CLUT;
            break;

        case VPSHAL_DSS_DISPC_WB1:
            dispcVidObj->regOffset.vidBaseAdd = baseAddr + DSS_WB_BA(0);
            dispcVidObj->regOffset.vidPos     = baseAddr + DSS_WB_POSITION;
            dispcVidObj->regOffset.vidSize    = baseAddr + DSS_WB_SIZE;
            dispcVidObj->regOffset.vidAttrib  = baseAddr + DSS_WB_ATTRIBUTES;
            dispcVidObj->regOffset.bufThresh  = baseAddr +
                                                DSS_WB_BUF_THRESHOLD;
            dispcVidObj->regOffset.bufSizeStat = baseAddr +
                                                 DSS_WB_BUF_SIZE_STATUS;
            dispcVidObj->regOffset.firH     = baseAddr + DSS_WB_FIRH;
            dispcVidObj->regOffset.firV     = baseAddr + DSS_WB_FIRV;
            dispcVidObj->regOffset.pictSize = baseAddr +
                                              DSS_WB_PICTURE_SIZE;
            dispcVidObj->regOffset.accumuH      = baseAddr + DSS_WB_ACCUH(0);
            dispcVidObj->regOffset.accumuV      = baseAddr + DSS_WB_ACCUV(0);
            dispcVidObj->regOffset.convCoef[0]  = baseAddr + DSS_WB_CONV_COEF0;
            dispcVidObj->regOffset.convCoef[1]  = baseAddr + DSS_WB_CONV_COEF1;
            dispcVidObj->regOffset.convCoef[2]  = baseAddr + DSS_WB_CONV_COEF2;
            dispcVidObj->regOffset.convCoef[3]  = baseAddr + DSS_WB_CONV_COEF3;
            dispcVidObj->regOffset.convCoef[4]  = baseAddr + DSS_WB_CONV_COEF4;
            dispcVidObj->regOffset.convCoef[5]  = baseAddr + DSS_WB_CONV_COEF5;
            dispcVidObj->regOffset.convCoef[6]  = baseAddr + DSS_WB_CONV_COEF6;
            dispcVidObj->regOffset.vidBaseAddUv = baseAddr + DSS_WB_BA_UV(0);
            dispcVidObj->regOffset.vidAttrib2   = baseAddr + DSS_WB_ATTRIBUTES2;
            dispcVidObj->regOffset.firH2        = baseAddr + DSS_WB_FIRH2;
            dispcVidObj->regOffset.firV2        = baseAddr + DSS_WB_FIRV2;
            dispcVidObj->regOffset.accumuH2     = baseAddr + DSS_WB_ACCUH2(0);
            dispcVidObj->regOffset.accumuV2     = baseAddr + DSS_WB_ACCUV2(0);
            dispcVidObj->regOffset.mflagThre    = baseAddr +
                                                  DSS_WB_MFLAG_THRESHOLD;
            dispcVidObj->regOffset.firCoefH0 = baseAddr + DSS_WB_FIR_COEF_H0(
                0);
            dispcVidObj->regOffset.firCoefH0_C = baseAddr +
                                                 DSS_WB_FIR_COEF_H0_C(0);
            dispcVidObj->regOffset.firCoefH12 = baseAddr +
                                                DSS_WB_FIR_COEF_H12(0);
            dispcVidObj->regOffset.firCoefV0 = baseAddr + DSS_WB_FIR_COEF_V0(
                0);
            dispcVidObj->regOffset.firCoefV12 = baseAddr +
                                                DSS_WB_FIR_COEF_V12(0);
            dispcVidObj->regOffset.firCoefH12_C = baseAddr +
                                                  DSS_WB_FIR_COEF_H12_C(0);
            dispcVidObj->regOffset.firCoefV0_C = baseAddr +
                                                 DSS_WB_FIR_COEF_V0_C(0);
            dispcVidObj->regOffset.firCoefV12_C = baseAddr +
                                                  DSS_WB_FIR_COEF_V12_C(0);
            break;

        default:
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
            retVal = BSP_EBADARGS;
            break;
    }
    switch (dispcVidObj->halId)
    {
        case VPSHAL_DSS_DISPC_VID1:
        case VPSHAL_DSS_DISPC_VID2:
            BspUtils_memcpy(&dispcVidObj->cscCoeff, &gVidCscCoeff,
                            sizeof (Vps_DssCscCoeff));
            break;

        case VPSHAL_DSS_DISPC_WB1:
            BspUtils_memcpy(&dispcVidObj->cscCoeff, &gWbCscCoeff,
                            sizeof (Vps_DssCscCoeff));
            break;

        default:
            /* It could be Gfx pipe nothing to be done for that */
            break;
    }

    return retVal;
}

/**
 *  halDssGetChromaRes
 *  Return effective width and height for chroma plane based on the dataFormat.
 */
static void halDssGetChromaRes(UInt32 dataFmt, UInt32 width, UInt32 height,
                               UInt32 *chromaWidth, UInt32 *chromaHeight)
{
    Int32 retVal = BSP_SOK;

    if (Fvid2_isDataFmtRgb(dataFmt) == (Int32) TRUE)
    {
        *chromaWidth  = width;
        *chromaHeight = height;
    }
    else if (Fvid2_isDataFmtYuv(dataFmt) == (Int32) TRUE)
    {
        if (Fvid2_isDataFmtYuv422(dataFmt) == (Int32) TRUE)
        {
            *chromaWidth  = width;
            *chromaHeight = height / 2U;
        }
        if (Fvid2_isDataFmtYuv420(dataFmt) == (Int32) TRUE)
        {
            *chromaWidth  = width / 2U;
            *chromaHeight = height / 2U;
        }
        else
        {
            *chromaWidth  = width;
            *chromaHeight = height;
        }
    }
    else
    {
        retVal = BSP_EBADARGS;
    }
    GT_assert(VpsHalTrace, (BSP_SOK == retVal));

    return;
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_018)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-995) DOX_REQ_TAG(PDK-996) DOX_REQ_TAG(PDK-998)
 *          DOX_REQ_TAG(PDK-999) DOX_REQ_TAG(PDK-1000)
 */
/**
 *  VpsHal_dssConfWbPipe
 *  \brief DISPC Write Back Pipeline Conf function.
 *
 *  Initializes WB objects, gets the Pointers to Writeback pipeline config.
 *  Configures all the components present in the Writeback pipeline
 *  like input and out Format and resolution, out position, VC1 config.
 *
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Hanlde to the Writeback pipeline hal object
 *  \param wbConf          Pointer to the DispcwbConf structure.
 *                                  This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssConfWbPipe(VpsHal_Handle                   handle,
                           const VpsHal_DssDispcWbPipeCfg *wbConf)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 scEnable = 0;
    UInt32 verticalTaps;
    Int32  fmt;
    Int32  isInDataFmtRgb = 0, isOutDataFmtRgb = 0;
    Int32  isInDataFmtYuv = 0, isOutDataFmtYuv = 0;
    UInt32 chromaInWidth, chromaInHeight;
    UInt32 chromaOutWidth, chromaOutHeight;
    const VpsHal_DssScCoeff *hCoeff, *vCoeff;
    const VpsHal_DssScCoeff *hChromaCoeff, *vChromaCoeff;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId >= VPSHAL_DSS_DISPC_VID_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        fmt = halDssConvFvid2DataFmt(dispcVidObj->halId,
                                     wbConf->outFmt.dataFormat);

        if (fmt == BSP_EFAIL)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid Data format\r\n");
            retVal += BSP_EBADARGS;
        }

        halDssVidSetFormat(handle, (UInt32) fmt);

        halDssVidSetInRes(handle, wbConf->inHeight,
                          wbConf->inWidth);

        halDssVidSetOutRes(handle, wbConf->outFmt.height,
                           wbConf->outFmt.width);

        halDssWbSetMode(handle, wbConf->wbMode);

        halDssWbSetPosition(handle, wbConf->inPosX, wbConf->inPosY);

        halDssWbSetInNode(handle, wbConf->inNode);

        halDssWbSetRegionBased(handle, wbConf->cropEnable);

        isInDataFmtRgb  = Fvid2_isDataFmtRgb(wbConf->inDataFormat);
        isOutDataFmtYuv = Fvid2_isDataFmtYuv(wbConf->outFmt.dataFormat);
        isInDataFmtYuv  = Fvid2_isDataFmtYuv(wbConf->inDataFormat);
        isOutDataFmtRgb = Fvid2_isDataFmtRgb(wbConf->outFmt.dataFormat);

        if ((isInDataFmtRgb == (Int32) TRUE) &&
            (isOutDataFmtYuv == (Int32) TRUE))
        {
            halDssVidConfCscEnable(handle, (UInt32) 1);
        }
        else if ((isInDataFmtYuv == (Int32) TRUE) &&
                 (isOutDataFmtRgb == (Int32) TRUE))
        {
            halDssVidConfCscEnable(handle, (UInt32) 1);
        }
        else
        {
            halDssVidConfCscEnable(handle, (UInt32) 0);
        }

        /* TODO check if this is correct scaling in WB path*/
        if ((wbConf->inSourceHeight != wbConf->inHeight) ||
            (wbConf->inSourceWidth  != wbConf->inWidth))
        {
            /* In case of region based writeback enable scaling */
            scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_HRESIZE;
            scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_VRESIZE;
        }
        else if (wbConf->scEnable != 0)
        {
            if (wbConf->inWidth != wbConf->outFmt.width)
            {
                scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_HRESIZE;
            }
            if (wbConf->inHeight != wbConf->outFmt.height)
            {
                scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_VRESIZE;
            }
            if ((wbConf->outFmt.dataFormat == FVID2_DF_YUV422I_YUYV) ||
                (wbConf->outFmt.dataFormat == FVID2_DF_YUV422I_UYVY))
            {
                scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_HRESIZE;
            }
            if (wbConf->outFmt.dataFormat == FVID2_DF_YUV420SP_UV)
            {
                scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_HRESIZE;
                scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_VRESIZE;
            }
        }
        else if (wbConf->outFmt.dataFormat == FVID2_DF_YUV420SP_UV)
        {
            /* wbConf->scEnable == 0 */
            scEnable = DSS_VID_ATTRIBUTES_RESIZEENABLE_VRESIZE |
                            DSS_VID_ATTRIBUTES_RESIZEENABLE_HRESIZE;
        }
        else if ((wbConf->outFmt.dataFormat == FVID2_DF_YUV422I_YUYV) ||
                  (wbConf->outFmt.dataFormat == FVID2_DF_YUV422I_UYVY))
        {
            /* wbConf->scEnable == 0 */
            scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_HRESIZE;
        }
        else
        {
            /* Nothing to be done here */
        }

        if (scEnable != 0U)
        {
            /* For scaling in writeback pipeline there is a limitation,
             * maximum input width of 1280 pixels using 32-bit pixels and 5-tap,
             * and 2560 pixels using 32-bit pixels and 3-tap.
             * No limitation on the input height. */
            if (wbConf->inWidth > 1280)
            {
                verticalTaps = DSS_VID_ATTRIBUTES_VERTICALTAPS_TAPS3;
            }
            else
            {
                verticalTaps = DSS_VID_ATTRIBUTES_VERTICALTAPS_TAPS5;
            }
            halDssGetChromaRes(wbConf->inDataFormat, wbConf->inWidth,
                               wbConf->inHeight, &chromaInWidth,
                               &chromaInHeight);
            halDssGetChromaRes(wbConf->outFmt.dataFormat, wbConf->outFmt.width,
                               wbConf->outFmt.height, &chromaOutWidth,
                               &chromaOutHeight);

            hCoeff = halDssVidGetScalarCoeff(wbConf->inWidth,
                                             wbConf->outFmt.width,
                                             verticalTaps);
            vCoeff = halDssVidGetScalarCoeff(wbConf->inHeight,
                                             wbConf->outFmt.height,
                                             verticalTaps);

            hChromaCoeff = halDssVidGetScalarCoeff(chromaInWidth,
                                                   chromaOutWidth,
                                                   verticalTaps);

            vChromaCoeff = halDssVidGetScalarCoeff(chromaInHeight,
                                                   chromaOutHeight,
                                                   verticalTaps);

            halDssVidSetScalerCoeff(handle, vCoeff, hCoeff, vChromaCoeff,
                                    hChromaCoeff);

            halDssVidConfFir(handle, wbConf->inWidth,
                             wbConf->inHeight,
                             wbConf->outFmt.width,
                             wbConf->outFmt.height);

            halDssVidConfVerticalTapsEnable(handle, verticalTaps);

            if ((wbConf->outFmt.dataFormat == FVID2_DF_YUV422I_YUYV) ||
                (wbConf->outFmt.dataFormat == FVID2_DF_YUV422I_UYVY))
            {
                halDssVidConfFir2(handle, wbConf->inWidth,
                                  wbConf->inHeight,
                                  wbConf->outFmt.width / (UInt32) 2,
                                  wbConf->outFmt.height);
            }
            if (wbConf->outFmt.dataFormat == FVID2_DF_YUV420SP_UV)
            {
                halDssVidConfFir2(handle, wbConf->inWidth,
                                  wbConf->inHeight,
                                  wbConf->outFmt.width / (UInt32) 2,
                                  wbConf->outFmt.height / (UInt32) 2);
            }

            halDssVidConfScalerEnable(handle, scEnable);
        }
        else
        {
            /* Disable scalar */
            halDssVidConfScalerEnable(handle, scEnable);
        }

        halDssVidConfCscFullRange(handle, wbConf->cscFullRngEnable);
    }

    return retVal;
}

/**
 *  VpsHal_dssConfGfxPipe
 *  \brief DISPC GFX Pipeline Conf function.
 *
 *  Initializes GFX objects, gets the Pointers to pipeline config
 *  structure .Configures all the components present in the graphics pipeline
 *  like input Format, output resolution, out position.
 *
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Hanlde to the Graphics pipeline hal object
 *  \param gfxConf          Pointer to the DispcGfxConf structure.
 *                                    This parameter should not be NULL..
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssConfGfxPipe(VpsHal_Handle                    handle,
                            const VpsHal_DssDispcGfxPipeCfg *gfxConf)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcVidObj *dispcVidObj;
    Int32 fmt;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != gfxConf));

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId != VPSHAL_DSS_DISPC_GFX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        fmt = halDssConvFvid2DataFmt(dispcVidObj->halId,
                                     gfxConf->inFmt.dataFormat);

        if (fmt == BSP_EFAIL)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid Data format\r\n");
            retVal += BSP_EBADARGS;
        }

        halDssVidSetFormat(handle, (UInt32) fmt);

        /* As there is no scaler in GFX pipeline input res is same as
         * output resolution*/
        halDssVidSetOutRes(handle, gfxConf->inFmt.height,
                           gfxConf->inFmt.width);

        halDssVidSetPos(handle, gfxConf->posY,
                        gfxConf->posX);

        halDssVidConfRepliEnable(handle, gfxConf->repliEnable);

        halDssVidConfAntiFlickerEnable(handle, gfxConf->antiFlickerEnable);

        if ((gfxConf->inFmt.dataFormat == DSS_VID_ATTRIBUTES_FORMAT_BITMAP1) ||
            (gfxConf->inFmt.dataFormat == DSS_VID_ATTRIBUTES_FORMAT_BITMAP2) ||
            (gfxConf->inFmt.dataFormat == DSS_VID_ATTRIBUTES_FORMAT_BITMAP4) ||
            (gfxConf->inFmt.dataFormat == FVID2_DF_BITMAP8))
        {
            halDssVidConfClutTable(handle, gfxConf->clutdata);

            halDssVidConfNibbleMode(handle, gfxConf->nibblemode);
        }
    }

    return retVal;
}

/**
 *  VpsHal_dssConfVidPipe
 *  \brief DISPC VID Pipeline Conf function.
 *
 *  Initializes VID objects, gets the Pointers to pipeline config and vc1 config
 *  structures .Configures all the components present in the video pipeline
 *  like input Format, output resolution, out position, VC1 config.
 *
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Hanlde to the Video pipeline hal object
 *  \param vidConf          Pointer to the DispcVidConf structure.
 *                          This parameter should not be NULL.
 *  \param vc1Cfg           Pointer to the Vps_DssDispcVidVC1Config structure.
 *                          This parameter can be NULL, VC1 module will not be.
 *                          Enabled.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssConfVidPipe(VpsHal_Handle                    handle,
                            const VpsHal_DssDispcVidPipeCfg *vidConf,
                            const Vps_DssDispcVidVC1Config  *vc1Cfg)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 scEnable = 0;
    Int32  fmt;
    const VpsHal_DssScCoeff *hCoeff, *vCoeff;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != vidConf));

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId >= VPSHAL_DSS_DISPC_VID_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        fmt = halDssConvFvid2DataFmt(dispcVidObj->halId,
                                     vidConf->inFmt.dataFormat);

        if (fmt == BSP_EFAIL)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid Data format\r\n");
            retVal += BSP_EBADARGS;
        }

        halDssVidSetFormat(handle, (UInt32) fmt);

        halDssVidSetInRes(handle, vidConf->inFmt.height,
                          vidConf->inFmt.width);

        halDssVidSetOutRes(handle, vidConf->outHeight,
                           vidConf->outWidth);

        halDssVidSetPos(handle, vidConf->posY,
                        vidConf->posX);

        if ((vidConf->inFmt.dataFormat == FVID2_DF_BITMAP1) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_BITMAP2) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_BITMAP4) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_BITMAP8))
        {
            halDssVidConfClutTable(handle, vidConf->clutdata);

            halDssVidConfNibbleMode(handle, vidConf->nibblemode);
        }

        if ((vidConf->inFmt.dataFormat == FVID2_DF_YUV420SP_UV) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_YUYV) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_UYVY))
        {
            halDssVidConfCscEnable(handle, (UInt32) 1);
        }
        else
        {
            halDssVidConfCscEnable(handle, 0);
        }

        halDssVidConfRepliEnable(handle, vidConf->repliEnable);

        if ((vidConf->scEnable != 0) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_YUV420SP_UV) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_YUYV) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_UYVY))
        {
            if ((vidConf->scEnable != 0) &&
                (vidConf->inFmt.width != vidConf->outWidth))
            {
                scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_HRESIZE;
            }
            if ((vidConf->scEnable != 0) &&
                (vidConf->inFmt.height != vidConf->outHeight))
            {
                scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_VRESIZE;
            }

            hCoeff = halDssVidGetScalarCoeff(
                vidConf->inFmt.width,
                vidConf->outWidth,
                DSS_VID_ATTRIBUTES_VERTICALTAPS_TAPS5);
            vCoeff = halDssVidGetScalarCoeff(
                vidConf->inFmt.height,
                vidConf->outHeight,
                DSS_VID_ATTRIBUTES_VERTICALTAPS_TAPS5);
            halDssVidSetScalerCoeff(handle, vCoeff, hCoeff, vCoeff, hCoeff);

            halDssVidConfFir(handle, vidConf->inFmt.width,
                             vidConf->inFmt.height,
                             vidConf->outWidth,
                             vidConf->outHeight);
            halDssVidConfVerticalTapsEnable(
                handle, DSS_VID_ATTRIBUTES_VERTICALTAPS_TAPS5);

            if ((vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_YUYV) ||
                (vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_UYVY))
            {
                scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_HRESIZE;
                halDssVidConfFir2(handle, vidConf->inFmt.width / (UInt32) 2,
                                  vidConf->inFmt.height,
                                  vidConf->outWidth,
                                  vidConf->outHeight);
            }
            if (vidConf->inFmt.dataFormat == FVID2_DF_YUV420SP_UV)
            {
                scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_HRESIZE;
                scEnable |= DSS_VID_ATTRIBUTES_RESIZEENABLE_VRESIZE;
                halDssVidConfFir2(handle, vidConf->inFmt.width / (UInt32) 2,
                                  vidConf->inFmt.height / (UInt32) 2,
                                  vidConf->outWidth,
                                  vidConf->outHeight);
            }

            halDssVidConfScalerEnable(handle, scEnable);
        }
        else
        {
            /* Disable scalar */
            halDssVidConfScalerEnable(handle, 0U);
        }

        halDssVidConfCscFullRange(handle, vidConf->cscFullRngEnable);

        if (vc1Cfg != NULL)
        {
            halDssVidSetVc1Coeff(handle, vc1Cfg->rangeY,
                                 vc1Cfg->rangeUV);

            halDssVidVc1Enable(handle, vc1Cfg->enable);
        }
        else
        {
            halDssVidVc1Enable(handle, (UInt32) FALSE);
        }
    }

    return retVal;
}

Int32 VpsHal_dssPipeOvlyConfig(VpsHal_Handle                     handle,
                               const Vps_DssDispcOvlyPipeConfig *pipeCfg,
                               UInt32                            channelOut,
                               UInt32                            channelOut2)
{
    Int32                   retVal = BSP_SOK;
    UInt32                  regVal;
    VpsHal_DssDispcVidObj  *dispcVidObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != pipeCfg);

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (pipeCfg->pipeLine >= VPS_DSS_DISPC_PIPE_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Pipeline\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
        HW_SET_FIELD32(regVal, DSS_VID_ATTRIBUTES_ZORDER, pipeCfg->zorder);
        HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);

        if (dispcVidObj->halId == VPSHAL_DSS_DISPC_GFX)
        {
            regVal = HW_RD_REG32(
                ((dispcVidObj->regOffset.vidAttrib - DSS_GFX_ATTRIBUTES)
                    + DSS_GFX_GLOBAL_ALPHA));
            HW_SET_FIELD32(
                regVal, DSS_GFX_GLOBAL_ALPHA_GLOBALALPHA, pipeCfg->globalAlpha);
            HW_WR_REG32(
                ((dispcVidObj->regOffset.vidAttrib - DSS_GFX_ATTRIBUTES) +
                    DSS_GFX_GLOBAL_ALPHA), regVal);
        }
        else if ((dispcVidObj->halId == VPSHAL_DSS_DISPC_VID1) ||
                 (dispcVidObj->halId == VPSHAL_DSS_DISPC_VID2))
        {
            regVal = HW_RD_REG32(
                ((dispcVidObj->regOffset.vidAttrib - DSS_VID_ATTRIBUTES)
                    + DSS_VID_GLOBAL_ALPHA));
            HW_SET_FIELD32(
                regVal, DSS_VID_GLOBAL_ALPHA_GLOBALALPHA, pipeCfg->globalAlpha);
            HW_WR_REG32(
                (dispcVidObj->regOffset.vidAttrib - DSS_VID_ATTRIBUTES) +
                    DSS_VID_GLOBAL_ALPHA, regVal);
        }
        else
        {
            /* Not applicable for WB Pipeline */
            retVal = BSP_EINVALID_PARAMS;
        }

        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
        HW_SET_FIELD32(
            regVal,
            DSS_VID_ATTRIBUTES_PREMULTIPLYALPHA,
            pipeCfg->preMultiplyAlpha);
        HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);

        if (dispcVidObj->halId == VPSHAL_DSS_DISPC_GFX)
        {
            regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
            HW_SET_FIELD32(regVal, DSS_GFX_ATTRIBUTES_CHANNELOUT, channelOut);
            HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
        }
        else
        {
            regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
            HW_SET_FIELD32(regVal, DSS_VID_ATTRIBUTES_CHANNELOUT, channelOut);
            HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
        }
    }

    return (retVal);
}

/**
 *  VpsHal_dssConfAdvDma
 *  \brief DISPC Advance DMA Config Function.
 *
 *  This function will configure all the advance DMA parameters,
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Hanlde to the Video pipeline hal object
 *  \param advDmaCfg        Pointer to advance DMA configuration structure.
 *                          This parameter should not be NULL.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssConfAdvDma(VpsHal_Handle                      handle,
                           const VpsHal_DssDispcAdvDmaConfig *advDmaCfg)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcVidObj *dispcVidObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != advDmaCfg));

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId >= VPSHAL_DSS_DISPC_VID_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        halDssVidDmaBufThreConf(handle,
                                advDmaCfg->bufLowThreshold,
                                advDmaCfg->bufHighThreshold,
                                advDmaCfg->bufPreloadType);

        if (dispcVidObj->halId != VPSHAL_DSS_DISPC_WB1)
        {
            /* WB pipe doesnot support Row/Pixel Inc. */
            halDssVidDmaPixelRowIncConf(handle,
                                        advDmaCfg->rowInc,
                                        advDmaCfg->pixelInc);
        }

        halDssVidDmaConfArbitration(handle,
                                    advDmaCfg->arbitration);

        halDssVidDmaConfSelfRefresh(handle,
                                    advDmaCfg->selfRefreshEnable);

        if (dispcVidObj->halId == VPSHAL_DSS_DISPC_WB1)
        {
            halDssWbIdleConfig(handle,
                               advDmaCfg->idleNumber,
                               advDmaCfg->idleSize);
        }
    }
    return retVal;
}

/**
 *  VpsHal_dssVidPipeEnable
 *  \brief Enables/Disables the Video pipeline
 *
 *  This function will Enable a particular video pipeline,
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Hanlde to the Video pipeline hal object
 *  \param enable           enable or disable the pipeline.1-enable,0-disable.
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssVidPipeEnable(VpsHal_Handle handle,
                              UInt32        enable)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId >= VPSHAL_DSS_DISPC_VID_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);

        regVal &= ~((UInt32) DSS_VID_ATTRIBUTES_ENABLE_MASK);
        regVal |= (((UInt32) enable) << DSS_VID_ATTRIBUTES_ENABLE_SHIFT) &
                  DSS_VID_ATTRIBUTES_ENABLE_MASK;

        HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
    }
    return retVal;
}

/**
 *  VpsHal_dssVidPipeSetBufAddr
 *  \brief Sets the buffer address for a particular pipeline
 *
 *  This function will program the buffer address for a pipeline,
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Handle to the Video pipeline hal object
 *  \param field            Top or bottom field.0-top field, 1-bottom field
 *                          For progressive buffers always use 0.
 *  \param baseAddRGBY      Base address of RGB or Y plane depending on format.
 *  \param baseAddCbCr      Valid only for YUV420-NV12 format.
 *
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssVidPipeSetBufAddr(VpsHal_Handle handle,
                                  UInt32        field,
                                  UInt32        baseAddRGBY,
                                  UInt32        baseAddCbCr)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcVidObj *dispcVidObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId >= VPSHAL_DSS_DISPC_VID_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        if ((field == 0U) || (field == 1U))
        {
            /* TODO - 4 should be passed as macro*/
            HW_WR_REG32(dispcVidObj->regOffset.vidBaseAdd +
                        (field * (0x4U)), baseAddRGBY);

            if (dispcVidObj->halId != VPSHAL_DSS_DISPC_GFX)
            {
                HW_WR_REG32(dispcVidObj->regOffset.vidBaseAddUv +
                            (field * (0x4U)), baseAddCbCr);
            }
        }
        else
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid field ID \r\n");
            retVal = BSP_EBADARGS;
        }
    }
    return retVal;
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_018)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-997)
 */
Int32 VpsHal_dssWbPipeSetRegionBased(VpsHal_Handle handle,
                                     UInt32        enable)
{
    halDssWbSetRegionBased(handle, enable);
    return BSP_SOK;
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_005)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-835) DOX_REQ_TAG(PDK-836) DOX_REQ_TAG(PDK-837)
 *          DOX_REQ_TAG(PDK-838) DOX_REQ_TAG(PDK-839) DOX_REQ_TAG(PDK-840)
 *          DOX_REQ_TAG(PDK-841) DOX_REQ_TAG(PDK-843) DOX_REQ_TAG(PDK-844)
 *          DOX_REQ_TAG(PDK-845) DOX_REQ_TAG(PDK-846) DOX_REQ_TAG(PDK-847)
 *          DOX_REQ_TAG(PDK-848) DOX_REQ_TAG(PDK-849) DOX_REQ_TAG(PDK-850)
 *          DOX_REQ_TAG(PDK-851) DOX_REQ_TAG(PDK-852) DOX_REQ_TAG(PDK-853)
 *          DOX_REQ_TAG(PDK-854) DOX_REQ_TAG(PDK-825)
 */
/**
 *  halDssConvFvid2DataFmt
 *  Converts the FVID2 Dataformat into DSS data format
 */
Int32 halDssConvFvid2DataFmt(UInt32 handleId, UInt32 fvid2Fmt)
{
    Int32 fmt = BSP_EFAIL;

    if (handleId <= VPS_DSS_DISPC_PIPE_WB)
    {
        switch (fvid2Fmt)
        {
            case FVID2_DF_YUV422I_UYVY:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_UYVY;
                break;
            case FVID2_DF_YUV422I_YUYV:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_YUV2;
                break;
            case FVID2_DF_YUV420SP_UV:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_NV12;
                break;
            case FVID2_DF_BGR24_888:   /*RGB24-888*/ /* TODO - Check this*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_RGB24P_888;
                break;
            case FVID2_DF_BGRA16_4444: /* ARGB16_4444*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_ARGB16_4444;
                break;
            case FVID2_DF_BGRA32_8888: /* ARGB32_8888*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_ARGB32_8888;
                break;
            case FVID2_DF_BGRX32_8888: /* XBGR32_8888*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_XBGR32_8888;
                break;
            case FVID2_DF_BGRA16_1555: /* ARGB16_1555*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_ABGR16_1555;
                break;
            case FVID2_DF_BGRX16_1555: /* XRGB16_1555*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_XBGR16_1555;
                break;
            case FVID2_DF_BGR16_565_A8: /* RGB16_565_A8*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_RGB565A8;
                break;
            case FVID2_DF_RGB16_565_A8: /* BGR16_565_A8*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_BGR565A8;
                break;
            case FVID2_DF_BGRX_4444: /* XRGB16_4444*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_XRGB16_4444;
                break;
            case FVID2_DF_XBGR_4444: /* RGBX16_4444*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_RGBX16_4444;
                break;
            case FVID2_DF_ABGR16_4444: /* RGBA16_4444*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_RGBA16_4444;
                break;
            case FVID2_DF_RGBA16_4444: /* ABGR16_4444*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_ABGR16_4444;
                break;
            case FVID2_DF_RGBX16_4444: /* XBGR16_4444 */
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_XBGR16_4444;
                break;
            case FVID2_DF_RGBA32_8888: /* ABGR32_8888*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_ABGR32_8888;
                break;
            case FVID2_DF_BGRX16_5551: /*xRGB16-1555*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_XRGB16_1555;
                break;
            case FVID2_DF_BGRA16_5551: /*ARGB16-1555*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_ARGB16_1555;
                break;
            case FVID2_DF_BGR16_565:   /* RGB16- 565*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_RGB16_565;
                break;
            case FVID2_DF_RGB16_565:   /* BGR16- 565*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_BGR16_565;
                break;
            case FVID2_DF_BGRX24_8888: /*xRGB24-8888*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_XRGB32_8888;
                break;
            case FVID2_DF_XBGR24_8888: /*RGBx24-8888*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_RGBX32_8888;
                break;
            case FVID2_DF_ABGR32_8888: /*RGBA32-8888*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_RGBA32_8888;
                break;
            case FVID2_DF_ARGB32_8888: /*BGRA32-8888*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_BGRA32_8888;
                break;
            case FVID2_DF_XRGB32_8888: /*BGRX32-8888*/
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_BGRX32_8888;
                break;
            case FVID2_DF_BGRA32_1010102:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_ARGB32_2101010;
                break;
            case FVID2_DF_BGRX32_1010102:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_XRGB32_2101010;
                break;
            case FVID2_DF_RGBA32_1010102:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_ABGR32_2101010;
                break;
            case FVID2_DF_RGBX32_1010102:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_XBGR32_2101010;
                break;
            case FVID2_DF_BGRA64_16161616:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_ARGB64_16161616;
                break;
            case FVID2_DF_BGRX64_16161616:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_XRGB64_16161616;
                break;
            case FVID2_DF_ABGR64_16161616:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_RGBA64_16161616;
                break;
            case FVID2_DF_XBGR64_16161616:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_RGBX64_16161616;
                break;
            case FVID2_DF_BITMAP1:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_BITMAP1;
                break;
            case FVID2_DF_BITMAP2:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_BITMAP2;
                break;
            case FVID2_DF_BITMAP4:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_BITMAP4;
                break;
            case FVID2_DF_BITMAP8:
                fmt = (Int32) DSS_VID_ATTRIBUTES_FORMAT_BITMAP8;
                break;
            default:
                fmt = BSP_EFAIL;
                break;
        }

        if (handleId == VPS_DSS_DISPC_PIPE_WB)
        {
            if ((fvid2Fmt == FVID2_DF_BGRA32_1010102) ||
                (fvid2Fmt == FVID2_DF_RGBA32_1010102) ||
                (fvid2Fmt == FVID2_DF_BITMAP1) ||
                (fvid2Fmt == FVID2_DF_BITMAP2) ||
                (fvid2Fmt == FVID2_DF_BITMAP4) ||
                (fvid2Fmt == FVID2_DF_BITMAP8) ||
                (fvid2Fmt == FVID2_DF_BGRX32_1010102) ||
                (fvid2Fmt == FVID2_DF_RGBX32_1010102))
            {
                fmt = BSP_EFAIL;
                GT_0trace(
                    VpsHalTrace, GT_ERR,
                    "Format not supported for \
                 WB pipeline \r\n");
            }
        }

        if (handleId == VPS_DSS_DISPC_PIPE_GFX1)
        {
            if ((fvid2Fmt == FVID2_DF_YUV422I_UYVY) ||
                (fvid2Fmt == FVID2_DF_YUV422I_YUYV) ||
                (fvid2Fmt == FVID2_DF_YUV420SP_UV) ||
                (fvid2Fmt == FVID2_DF_BGR16_565_A8) ||
                (fvid2Fmt == FVID2_DF_RGB16_565_A8))
            {
                fmt = BSP_EFAIL;
                GT_0trace(
                    VpsHalTrace, GT_ERR,
                    "Format not supported for \
                 GFX pipeline \r\n");
            }
        }
    }

    return fmt;
}

/**
 *  halDssVidDmaBufThreConf
 *  Sets the Buffer Threshold(Low and High) of DMA for the pipeline
 */
static void halDssVidDmaBufThreConf(VpsHal_Handle handle,
                                    UInt32        bufLowThreshold,
                                    UInt32        bufHighThreshold,
                                    UInt32        bufPreloadType)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;
    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal  = HW_RD_REG32(dispcVidObj->regOffset.bufThresh);
    regVal &=
        ~(DSS_VID_BUF_THRESHOLD_BUFLOWTHRESHOLD_MASK |
          DSS_VID_BUF_THRESHOLD_BUFHIGHTHRESHOLD_MASK);

    regVal |=
        (((UInt32) bufLowThreshold) <<
         DSS_VID_BUF_THRESHOLD_BUFLOWTHRESHOLD_SHIFT) &
        DSS_VID_BUF_THRESHOLD_BUFLOWTHRESHOLD_MASK;

    regVal |=
        (((UInt32) bufHighThreshold) <<
         DSS_VID_BUF_THRESHOLD_BUFHIGHTHRESHOLD_SHIFT) &
        DSS_VID_BUF_THRESHOLD_BUFHIGHTHRESHOLD_MASK;

    HW_WR_REG32(dispcVidObj->regOffset.bufThresh, regVal);

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
    if ((Int32) TRUE == (VpsHal_dssIsGfxPipe(dispcVidObj->halId)))
    {
        HW_SET_FIELD32(regVal, DSS_GFX_ATTRIBUTES_BUFPRELOAD, bufPreloadType);
    }
    else if ((Int32) TRUE == (VpsHal_dssIsVidPipe(dispcVidObj->halId)))
    {
        HW_SET_FIELD32(regVal, DSS_VID_ATTRIBUTES_BUFPRELOAD, bufPreloadType);
    }
    else
    {
        /* MISRA-C */
    }
    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_005)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-828)
 */
/**
 *  halDssVidDmaPixelRowIncConf
 *  Sets the Pixel Inc and Row Inc of DMA for the video pipeline
 */
static void halDssVidDmaPixelRowIncConf(VpsHal_Handle handle,
                                        UInt32        rowInc,
                                        UInt32        pixelInc)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;
    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    /* Not applicable for writeback pipeline */
    if (dispcVidObj->halId != VPSHAL_DSS_DISPC_WB1)
    {
        regVal  = HW_RD_REG32(dispcVidObj->regOffset.rowInc);
        regVal &= ~(DSS_VID_ROW_INC_ROWINC_MASK);
        regVal |= (((UInt32) rowInc) << DSS_VID_ROW_INC_ROWINC_SHIFT) &
                  DSS_VID_ROW_INC_ROWINC_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.rowInc, regVal);

        regVal  = HW_RD_REG32(dispcVidObj->regOffset.pixelInc);
        regVal &= ~((UInt32) DSS_VID_PIXEL_INC_PIXELINC_MASK);
        regVal |= (((UInt32) pixelInc) << DSS_VID_PIXEL_INC_PIXELINC_SHIFT) &
                  DSS_VID_PIXEL_INC_PIXELINC_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.pixelInc, regVal);
    }
}

/**
 *  halDssVidDmaConfArbitration
 *  Sets the Priority of the video pipeline wrt DMA
 */
static void halDssVidDmaConfArbitration(VpsHal_Handle handle,
                                        UInt32        arbitration)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);

    if (dispcVidObj->halId == VPSHAL_DSS_DISPC_GFX)
    {
        regVal &= ~((UInt32) DSS_GFX_ATTRIBUTES_ARBITRATION_MASK);
        regVal |=
            (((UInt32) arbitration) << DSS_GFX_ATTRIBUTES_ARBITRATION_SHIFT) &
            DSS_GFX_ATTRIBUTES_ARBITRATION_MASK;
    }
    else
    {
        regVal &= ~((UInt32) DSS_VID_ATTRIBUTES_ARBITRATION_MASK);
        regVal |=
            (((UInt32) arbitration) << DSS_VID_ATTRIBUTES_ARBITRATION_SHIFT) &
            DSS_VID_ATTRIBUTES_ARBITRATION_MASK;
    }

    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
}

/**
 *  halDssVidDmaConfSelfRefresh
 *  Sets the SelfRefresh mode of the video pipeline wrt DMA
 *  Enables the self refresh of the video window from its own
 *  DMA buffer only
 */
static void halDssVidDmaConfSelfRefresh(VpsHal_Handle handle,
                                        UInt32        selfRefreshEnable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);

    if (dispcVidObj->halId == VPSHAL_DSS_DISPC_GFX)
    {
        regVal &= ~((UInt32) DSS_GFX_ATTRIBUTES_SELFREFRESH_MASK);
        regVal |=
            (((UInt32) selfRefreshEnable) <<
             DSS_GFX_ATTRIBUTES_SELFREFRESH_SHIFT) &
            DSS_GFX_ATTRIBUTES_SELFREFRESH_MASK;
    }
    else if ((dispcVidObj->halId == VPSHAL_DSS_DISPC_VID1) ||
             (dispcVidObj->halId == VPSHAL_DSS_DISPC_VID2))
    {
        regVal &= ~((UInt32) DSS_VID_ATTRIBUTES_SELFREFRESH_MASK);
        regVal |=
            (((UInt32) selfRefreshEnable) <<
             DSS_VID_ATTRIBUTES_SELFREFRESH_SHIFT) &
            DSS_VID_ATTRIBUTES_SELFREFRESH_MASK;
    }
    else
    {
        /* Not applicable for WB Pipeline */
    }

    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_005)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-834) DOX_REQ_TAG(PDK-842)
 */
/**
 *  halDssVidSetFormat
 *  Sets the data format for the video pipeline
 */
static void halDssVidSetFormat(VpsHal_Handle handle,
                               UInt32        dataFmt)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);

    regVal &= ~((UInt32) DSS_VID_ATTRIBUTES_FORMAT_MASK);
    regVal |= (((UInt32) dataFmt) << DSS_VID_ATTRIBUTES_FORMAT_SHIFT) &
              DSS_VID_ATTRIBUTES_FORMAT_MASK;

    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
}

/**
 *  halDssVidConfCscFullRange
 *  Configures the CSC Mode of Operation
 */
static void halDssVidConfCscFullRange(VpsHal_Handle handle,
                                      UInt32        cscFullRngEnable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);

    if ((dispcVidObj->halId == VPSHAL_DSS_DISPC_VID1) ||
        (dispcVidObj->halId == VPSHAL_DSS_DISPC_VID2))
    {
        regVal &= ~((UInt32) DSS_VID_ATTRIBUTES_FULLRANGE_MASK);
        regVal |=
            (((UInt32) cscFullRngEnable) <<
             DSS_VID_ATTRIBUTES_FULLRANGE_SHIFT) &
            DSS_VID_ATTRIBUTES_FULLRANGE_MASK;
    }
    else if (dispcVidObj->halId == VPSHAL_DSS_DISPC_WB1)
    {
        regVal &= ~((UInt32) DSS_WB_ATTRIBUTES_FULLRANGE_MASK);
        regVal |=
            (((UInt32) cscFullRngEnable) <<
             DSS_WB_ATTRIBUTES_FULLRANGE_SHIFT) &
            DSS_WB_ATTRIBUTES_FULLRANGE_MASK;
    }
    else
    {
        /* Not applicable for graphics */
    }

    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
}

/**
 *  halDssVidConfCscCoeff
 *  Configures the coefficients for color space conversion
 */
static void halDssVidConfCscCoeff(VpsHal_Handle          handle,
                                  const Vps_DssCscCoeff *coeff)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((dispcVidObj->halId == VPSHAL_DSS_DISPC_VID1) ||
        (dispcVidObj->halId == VPSHAL_DSS_DISPC_VID2) ||
        (dispcVidObj->halId == VPSHAL_DSS_DISPC_WB1))
    {
        regVal  = HW_RD_REG32(dispcVidObj->regOffset.convCoef[0]);
        regVal &= ~(DSS_VID_CONV_COEF0_RCR_MASK | DSS_VID_CONV_COEF0_RY_MASK);

        regVal |= (((UInt32) coeff->rcr) << DSS_VID_CONV_COEF0_RCR_SHIFT) &
                  DSS_VID_CONV_COEF0_RCR_MASK;

        regVal |= (((UInt32) coeff->ry) << DSS_VID_CONV_COEF0_RY_SHIFT) &
                  DSS_VID_CONV_COEF0_RY_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.convCoef[0], regVal);

        regVal  = HW_RD_REG32(dispcVidObj->regOffset.convCoef[1]);
        regVal &= ~(DSS_VID_CONV_COEF1_GY_MASK | DSS_VID_CONV_COEF1_RCB_MASK);

        regVal |= (((UInt32) coeff->gy) << DSS_VID_CONV_COEF1_GY_SHIFT) &
                  DSS_VID_CONV_COEF1_GY_MASK;

        regVal |= (((UInt32) coeff->rcb) << DSS_VID_CONV_COEF1_RCB_SHIFT) &
                  DSS_VID_CONV_COEF1_RCB_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.convCoef[1], regVal);

        regVal  = HW_RD_REG32(dispcVidObj->regOffset.convCoef[2]);
        regVal &= ~(DSS_VID_CONV_COEF2_GCB_MASK | DSS_VID_CONV_COEF2_GCR_MASK);

        regVal |= (((UInt32) coeff->gcb) << DSS_VID_CONV_COEF2_GCB_SHIFT) &
                  DSS_VID_CONV_COEF2_GCB_MASK;

        regVal |= (((UInt32) coeff->gcr) << DSS_VID_CONV_COEF2_GCR_SHIFT) &
                  DSS_VID_CONV_COEF2_GCR_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.convCoef[2], regVal);

        regVal  = HW_RD_REG32(dispcVidObj->regOffset.convCoef[3]);
        regVal &= ~(DSS_VID_CONV_COEF3_BCR_MASK | DSS_VID_CONV_COEF3_BY_MASK);

        regVal |= (((UInt32) coeff->bcr) << DSS_VID_CONV_COEF3_BCR_SHIFT) &
                  DSS_VID_CONV_COEF3_BCR_MASK;

        regVal |= (((UInt32) coeff->by) << DSS_VID_CONV_COEF3_BY_SHIFT) &
                  DSS_VID_CONV_COEF3_BY_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.convCoef[3], regVal);

        regVal  = HW_RD_REG32(dispcVidObj->regOffset.convCoef[4]);
        regVal &= ~((UInt32) DSS_VID_CONV_COEF4_BCB_MASK);

        regVal |= (((UInt32) coeff->bcb) << DSS_VID_CONV_COEF4_BCB_SHIFT) &
                  DSS_VID_CONV_COEF4_BCB_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.convCoef[4], regVal);

        regVal  = HW_RD_REG32(dispcVidObj->regOffset.convCoef[5]);
        regVal &=
            ~(DSS_VID_CONV_COEF5_ROFFSET_MASK | DSS_VID_CONV_COEF5_GOFFSET_MASK);

        regVal |=
            (((UInt32) coeff->roff) << DSS_VID_CONV_COEF5_ROFFSET_SHIFT) &
            DSS_VID_CONV_COEF5_ROFFSET_MASK;

        regVal |=
            (((UInt32) coeff->goff) << DSS_VID_CONV_COEF5_GOFFSET_SHIFT) &
            DSS_VID_CONV_COEF5_GOFFSET_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.convCoef[5], regVal);

        regVal  = HW_RD_REG32(dispcVidObj->regOffset.convCoef[6]);
        regVal &= ~((UInt32) DSS_VID_CONV_COEF6_BOFFSET_MASK);

        regVal |=
            (((UInt32) coeff->boff) << DSS_VID_CONV_COEF6_BOFFSET_SHIFT) &
            DSS_VID_CONV_COEF6_BOFFSET_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.convCoef[6], regVal);
    }
    else
    {
        /* Error */
    }
}

/**
 *  halDssVidConfCscCoeff
 *  Configures the coefficients for color space conversion
 */
static void halDssVidConfCscEnable(VpsHal_Handle handle,
                                   UInt32        cscEnable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;
    if (TRUE == cscEnable)
    {
        if ((dispcVidObj->halId == VPSHAL_DSS_DISPC_VID1) ||
            (dispcVidObj->halId == VPSHAL_DSS_DISPC_VID2) ||
            (dispcVidObj->halId == VPSHAL_DSS_DISPC_WB1))
        {
            halDssVidConfCscCoeff(handle, &dispcVidObj->cscCoeff);
        }
        else
        {
            /* Not applicable for GFX */
        }
    }

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);

    if ((dispcVidObj->halId == VPSHAL_DSS_DISPC_VID1) ||
        (dispcVidObj->halId == VPSHAL_DSS_DISPC_VID2))
    {
        regVal &= ~((UInt32) DSS_VID_ATTRIBUTES_COLORCONVENABLE_MASK);
        regVal |=
            (((UInt32) cscEnable) <<
             DSS_VID_ATTRIBUTES_COLORCONVENABLE_SHIFT) &
            DSS_VID_ATTRIBUTES_COLORCONVENABLE_MASK;
    }

    if (dispcVidObj->halId == VPSHAL_DSS_DISPC_WB1)
    {
        regVal &= ~((UInt32) DSS_WB_ATTRIBUTES_COLORCONVENABLE_MASK);
        regVal |=
            (((UInt32) cscEnable) << DSS_WB_ATTRIBUTES_COLORCONVENABLE_SHIFT) &
            DSS_WB_ATTRIBUTES_COLORCONVENABLE_MASK;
    }

    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_005)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-823) DOX_REQ_TAG(PDK-824) DOX_REQ_TAG(PDK-825)
 */
/**
 *  halDssVidConfScalerCoeff
 *  Configures the coefficients of  Scaler module
 */
static void halDssVidSetScalerCoeff(VpsHal_Handle            handle,
                                    const VpsHal_DssScCoeff *vCoef,
                                    const VpsHal_DssScCoeff *hCoef,
                                    const VpsHal_DssScCoeff *vChromaCoef,
                                    const VpsHal_DssScCoeff *hChromaCoef)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 i = 0, regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId != VPSHAL_DSS_DISPC_GFX)
    {
        for (i = 0U; i < 9U; i++)
        {
            regVal  = HW_RD_REG32(dispcVidObj->regOffset.firCoefH0 + (i * 0x4U));
            regVal &= ~((UInt32) DSS_VID_FIR_COEF_H0_FIRHC0_MASK);
            regVal |=
                (((UInt32) hCoef[i].firhc0) <<
                 DSS_VID_FIR_COEF_H0_FIRHC0_SHIFT) &
                DSS_VID_FIR_COEF_H0_FIRHC0_MASK;
            HW_WR_REG32(dispcVidObj->regOffset.firCoefH0 + (i * 0x4U), regVal);

            regVal =
                HW_RD_REG32(dispcVidObj->regOffset.firCoefH0_C + (i * 0x4U));
            regVal &= ~((UInt32) DSS_VID_FIR_COEF_H0_C_FIRHC0_MASK);
            regVal |=
                (((UInt32) hChromaCoef[i].firhc0) <<
                 DSS_VID_FIR_COEF_H0_C_FIRHC0_SHIFT) &
                DSS_VID_FIR_COEF_H0_C_FIRHC0_MASK;
            HW_WR_REG32(dispcVidObj->regOffset.firCoefH0_C + (i * 0x4U), regVal);

            regVal  = HW_RD_REG32(dispcVidObj->regOffset.firCoefV0 + (i * 0x4U));
            regVal &= ~((UInt32) DSS_VID_FIR_COEF_V0_FIRVC0_MASK);
            regVal |=
                (((UInt32) vCoef[i].firhc0) <<
                 DSS_VID_FIR_COEF_V0_FIRVC0_SHIFT) &
                DSS_VID_FIR_COEF_V0_FIRVC0_MASK;
            HW_WR_REG32(dispcVidObj->regOffset.firCoefV0 + (i * 0x4U), regVal);

            regVal =
                HW_RD_REG32(dispcVidObj->regOffset.firCoefV0_C + (i * 0x4U));
            regVal &= ~((UInt32) DSS_VID_FIR_COEF_V0_C_FIRVC0_MASK);
            regVal |=
                (((UInt32) vChromaCoef[i].firhc0) <<
                 DSS_VID_FIR_COEF_V0_C_FIRVC0_SHIFT) &
                DSS_VID_FIR_COEF_V0_C_FIRVC0_MASK;
            HW_WR_REG32(dispcVidObj->regOffset.firCoefV0_C + (i * 0x4U), regVal);
        }

        for (i = 0U; i < 16U; i++)
        {
            regVal  = HW_RD_REG32(dispcVidObj->regOffset.firCoefH12 + (i * 0x4U));
            regVal &=
                ~(DSS_VID_FIR_COEF_H12_FIRHC2_MASK |
                  DSS_VID_FIR_COEF_H12_FIRHC1_MASK);
            regVal |=
                (((UInt32) hCoef[i].firhc2) <<
                 DSS_VID_FIR_COEF_H12_FIRHC2_SHIFT) &
                DSS_VID_FIR_COEF_H12_FIRHC2_MASK;
            regVal |=
                (((UInt32) hCoef[i].firhc1) <<
                 DSS_VID_FIR_COEF_H12_FIRHC1_SHIFT) &
                DSS_VID_FIR_COEF_H12_FIRHC1_MASK;
            HW_WR_REG32(dispcVidObj->regOffset.firCoefH12 + (i * 0x4U), regVal);

            regVal =
                HW_RD_REG32(dispcVidObj->regOffset.firCoefH12_C + (i * 0x4U));
            regVal &=
                ~(DSS_VID_FIR_COEF_H12_C_FIRHC2_MASK |
                  DSS_VID_FIR_COEF_H12_C_FIRHC1_MASK);
            regVal |=
                (((UInt32) hChromaCoef[i].firhc2) <<
                 DSS_VID_FIR_COEF_H12_C_FIRHC2_SHIFT) &
                DSS_VID_FIR_COEF_H12_C_FIRHC2_MASK;
            regVal |=
                (((UInt32) hChromaCoef[i].firhc1) <<
                 DSS_VID_FIR_COEF_H12_C_FIRHC1_SHIFT) &
                DSS_VID_FIR_COEF_H12_C_FIRHC1_MASK;
            HW_WR_REG32(dispcVidObj->regOffset.firCoefH12_C + (i * 0x4U),
                        regVal);

            regVal  = HW_RD_REG32(dispcVidObj->regOffset.firCoefV12 + (i * 0x4U));
            regVal &=
                ~(DSS_VID_FIR_COEF_V12_FIRVC2_MASK |
                  DSS_VID_FIR_COEF_V12_FIRVC1_MASK);
            regVal |=
                (((UInt32) vCoef[i].firhc2) <<
                 DSS_VID_FIR_COEF_V12_FIRVC2_SHIFT) &
                DSS_VID_FIR_COEF_V12_FIRVC2_MASK;
            regVal |=
                (((UInt32) vCoef[i].firhc1) <<
                 DSS_VID_FIR_COEF_V12_FIRVC1_SHIFT) &
                DSS_VID_FIR_COEF_V12_FIRVC1_MASK;
            HW_WR_REG32(dispcVidObj->regOffset.firCoefV12 + (i * 0x4U), regVal);

            regVal =
                HW_RD_REG32(dispcVidObj->regOffset.firCoefV12_C + (i * 0x4U));
            regVal &=
                ~(DSS_VID_FIR_COEF_V12_C_FIRVC2_MASK |
                  DSS_VID_FIR_COEF_V12_C_FIRVC1_MASK);
            regVal |=
                (((UInt32) vChromaCoef[i].firhc2) <<
                 DSS_VID_FIR_COEF_V12_C_FIRVC2_SHIFT) &
                DSS_VID_FIR_COEF_V12_C_FIRVC2_MASK;
            regVal |=
                (((UInt32) vChromaCoef[i].firhc1) <<
                 DSS_VID_FIR_COEF_V12_C_FIRVC1_SHIFT) &
                DSS_VID_FIR_COEF_V12_C_FIRVC1_MASK;
            HW_WR_REG32(dispcVidObj->regOffset.firCoefV12_C + (i * 0x4U),
                        regVal);
        }
    }
    else
    {
        /* Error */
    }
}

const VpsHal_DssScCoeff *halDssVidGetScalarCoeff(UInt32 inSize,
                                                 UInt32 outSize,
                                                 UInt32 verticalTaps)
{
    const VpsHal_DssScCoeff *scCoef = NULL;

    if (inSize <= outSize)
    {
        /* Upscaling coefficient. Common for all ratios. */
        scCoef = gDispcCoefUpScale;
    }
    else
    {
        /* DownScaling coefficient. Pick based on scaling ratio. */
        if ((inSize > outSize) && (inSize <= ((outSize * 3U) / 2U)))
        {
            /* For scaling ratio of 1 to 1.5 pick M10 coeff */
            if (verticalTaps == DSS_VID_ATTRIBUTES_VERTICALTAPS_TAPS3)
            {
                scCoef = gDispcCoefDownScale3TapM10;
            }
            else
            {
                scCoef = gDispcCoefDownScaleM10;
            }
        }
        else if ((inSize > ((outSize * 3U) / 2U)) && (inSize <= (outSize * 2U)))
        {
            /* For scaling ratio of 1.5 to 2 pick M14 coeff */
            if (verticalTaps == DSS_VID_ATTRIBUTES_VERTICALTAPS_TAPS3)
            {
                scCoef = gDispcCoefDownScale3TapM14;
            }
            else
            {
                scCoef = gDispcCoefDownScaleM14;
            }
        }
        else if ((inSize > (outSize * 2U)) && (inSize <= ((outSize * 5U) / 2U)))
        {
            /* For scaling ratio of 2 to 2.5 pick M19 coeff */
            if (verticalTaps == DSS_VID_ATTRIBUTES_VERTICALTAPS_TAPS3)
            {
                scCoef = gDispcCoefDownScale3TapM19;
            }
            else
            {
                scCoef = gDispcCoefDownScaleM19;
            }
        }
        else if ((inSize > ((outSize * 5U) / 2U)) && (inSize <= (outSize * 3U)))
        {
            /* For scaling ratio of 2.5 to 3 pick M22 coeff */
            if (verticalTaps == DSS_VID_ATTRIBUTES_VERTICALTAPS_TAPS3)
            {
                scCoef = gDispcCoefDownScale3TapM22;
            }
            else
            {
                scCoef = gDispcCoefDownScaleM22;
            }
        }
        else if ((inSize > (outSize * 3U)) && (inSize <= (outSize * 4U)))
        {
            /* For scaling ratio of 3 to 4 pick M26 coeff */
            if (verticalTaps == DSS_VID_ATTRIBUTES_VERTICALTAPS_TAPS3)
            {
                scCoef = gDispcCoefDownScale3TapM26;
            }
            else
            {
                scCoef = gDispcCoefDownScaleM26;
            }
        }
        else
        {
            /* Use M22 coeff as default scaling coeff */
            if (verticalTaps == DSS_VID_ATTRIBUTES_VERTICALTAPS_TAPS3)
            {
                scCoef = gDispcCoefDownScale3TapM22;
            }
            else
            {
                scCoef = gDispcCoefDownScaleM22;
            }
        }
    }
    return scCoef;
}

/**
 *  halDssVidConfVerticalTapsEnable
 *  Enables or disables the VerticalTaps
 */
static void halDssVidConfVerticalTapsEnable(VpsHal_Handle handle,
                                            UInt32        verticalTaps)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId != VPSHAL_DSS_DISPC_GFX)
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);

        regVal &= ~DSS_VID_ATTRIBUTES_VERTICALTAPS_MASK;
        regVal |=
            (((UInt32) verticalTaps) <<
             DSS_VID_ATTRIBUTES_VERTICALTAPS_SHIFT) &
            DSS_VID_ATTRIBUTES_VERTICALTAPS_MASK;

        HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
    }
}

/**
 *  halDispcVidConfFir
 *  Configures the Fir for RGB/Y component
 */
static void halDssVidConfFir(VpsHal_Handle handle,
                             UInt32        inSizeX,
                             UInt32        inSizeY,
                             UInt32        outSizeX,
                             UInt32        outSizeY)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 firHinc, firVinc, regVal;

    firHinc = (2097152U * (inSizeX)) / (outSizeX);
    firVinc = (2097152U * (inSizeY)) / (outSizeY);

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId != VPSHAL_DSS_DISPC_GFX)
    {
        regVal  = HW_RD_REG32(dispcVidObj->regOffset.firH);
        regVal &= ~DSS_VID_FIRH_FIRHINC_MASK;
        regVal |= (((UInt32) firHinc) << DSS_VID_FIRH_FIRHINC_SHIFT) &
                  DSS_VID_FIRH_FIRHINC_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.firH, regVal);

        regVal  = HW_RD_REG32(dispcVidObj->regOffset.firV);
        regVal &= ~DSS_VID_FIRV_FIRVINC_MASK;
        regVal |= (((UInt32) firVinc) << DSS_VID_FIRV_FIRVINC_SHIFT) &
                  DSS_VID_FIRV_FIRVINC_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.firV, regVal);
    }
    else
    {
        /* ERROR */
    }
}

/**
 *  halDispcVidConfScalarEnable
 *  Configures the mode of Scalar module
 */
static void halDssVidConfFir2(VpsHal_Handle handle,
                              UInt32        inSizeX,
                              UInt32        inSizeY,
                              UInt32        outSizeX,
                              UInt32        outSizeY)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 firHinc, firVinc, regVal;

    firHinc     = (2097152U * (inSizeX)) / (outSizeX);
    firVinc     = (2097152U * (inSizeY)) / (outSizeY);
    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId != VPSHAL_DSS_DISPC_GFX)
    {
        regVal  = HW_RD_REG32(dispcVidObj->regOffset.firH2);
        regVal &= ~DSS_VID_FIRH2_FIRHINC_MASK;
        regVal |= (((UInt32) firHinc) << DSS_VID_FIRH2_FIRHINC_SHIFT) &
                  DSS_VID_FIRH2_FIRHINC_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.firH2, regVal);

        regVal  = HW_RD_REG32(dispcVidObj->regOffset.firV2);
        regVal &= ~DSS_VID_FIRV2_FIRVINC_MASK;
        regVal |= (((UInt32) firVinc) << DSS_VID_FIRV2_FIRVINC_SHIFT) &
                  DSS_VID_FIRV2_FIRVINC_MASK;
        HW_WR_REG32(dispcVidObj->regOffset.firV2, regVal);
    }
    else
    {
        /* ERROR */
    }
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_005)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-823) DOX_REQ_TAG(PDK-824) DOX_REQ_TAG(PDK-825)
 */
/**
 *  halDispcVidConfScalerEnable
 *  Configures the mode of Scaler module
 */
static void halDssVidConfScalerEnable(VpsHal_Handle handle,
                                      UInt32        scalerEnable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);

    regVal &= ~((UInt32) DSS_VID_ATTRIBUTES_RESIZEENABLE_MASK);
    regVal |=
        (((UInt32) scalerEnable) << DSS_VID_ATTRIBUTES_RESIZEENABLE_SHIFT) &
        DSS_VID_ATTRIBUTES_RESIZEENABLE_MASK;

    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
}

/**
 *  halDssVidSetVc1Coeff
 *  Sets the coefficients of VC1 Rnage mapping module
 */
static void halDssVidSetVc1Coeff(VpsHal_Handle handle,
                                 UInt32        rangeY,
                                 UInt32        rangeUV)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((dispcVidObj->halId == VPSHAL_DSS_DISPC_VID1) ||
        (dispcVidObj->halId == VPSHAL_DSS_DISPC_VID2))
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib2);

        regVal &=
            ~((UInt32) DSS_VID_ATTRIBUTES2_VC1_RANGE_Y_MASK |
                        DSS_VID_ATTRIBUTES2_VC1_RANGE_CBCR_MASK);

        regVal |=
            (((UInt32) rangeY) << DSS_VID_ATTRIBUTES2_VC1_RANGE_Y_SHIFT) &
            DSS_VID_ATTRIBUTES2_VC1_RANGE_Y_MASK;

        regVal |=
            (((UInt32) rangeUV) << DSS_VID_ATTRIBUTES2_VC1_RANGE_CBCR_SHIFT) &
            DSS_VID_ATTRIBUTES2_VC1_RANGE_CBCR_MASK;

        HW_WR_REG32(dispcVidObj->regOffset.vidAttrib2, regVal);
    }
    else
    {
        /* Error */
    }
}

/**
 *  halDssVidVc1Enable
 *  Enable VC1 Range Mapping
 */
static void halDssVidVc1Enable(VpsHal_Handle handle,
                               UInt32        vc1Enable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((dispcVidObj->halId == VPSHAL_DSS_DISPC_VID1) ||
        (dispcVidObj->halId == VPSHAL_DSS_DISPC_VID2))
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib2);

        regVal &= ~((UInt32) DSS_VID_ATTRIBUTES2_VC1ENABLE_MASK);

        regVal |=
            (((UInt32) vc1Enable) << DSS_VID_ATTRIBUTES2_VC1ENABLE_SHIFT) &
            DSS_VID_ATTRIBUTES2_VC1ENABLE_MASK;

        HW_WR_REG32(dispcVidObj->regOffset.vidAttrib2, regVal);
    }
    else
    {
        /* Error */
    }
}

/**
 *  halDssWbSetRegionBased
 *  Set/Clear Region based bit
 */
static void halDssWbSetRegionBased(VpsHal_Handle handle,
                                   UInt32        enable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId == VPSHAL_DSS_DISPC_WB1)
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib2);
        HW_SET_FIELD32(regVal, DSS_WB_ATTRIBUTES2_REGION_BASED,
                       enable);
        HW_WR_REG32(dispcVidObj->regOffset.vidAttrib2, regVal);
    }
}

/**
 *  halDssWbSetInNode
 *  Sets the connection to writeback pipeline.
 */
static void halDssWbSetInNode(VpsHal_Handle handle,
                              UInt32        inNode)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal, nodeSel;
    Int32  retVal = BSP_SOK;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId == VPSHAL_DSS_DISPC_WB1)
    {
        switch (inNode)
        {
            case VPS_DSS_DISPC_WB_IN_NODE_VID1:
                nodeSel = DSS_WB_ATTRIBUTES_CHANNELIN_VID1SEL;
                break;

            case VPS_DSS_DISPC_WB_IN_NODE_VID2:
                nodeSel = DSS_WB_ATTRIBUTES_CHANNELIN_VID2SEL;
                break;

            case VPS_DSS_DISPC_WB_IN_NODE_GFX:
                nodeSel = DSS_WB_ATTRIBUTES_CHANNELIN_GFX1SEL;
                break;

            case VPS_DSS_DISPC_WB_IN_NODE_LCD1:
                nodeSel = DSS_WB_ATTRIBUTES_CHANNELIN_VP1SEL;
                break;

            case VPS_DSS_DISPC_WB_IN_NODE_LCD2:
                nodeSel = DSS_WB_ATTRIBUTES_CHANNELIN_OVR2SEL;
                break;

            default:
                GT_0trace(VpsHalTrace, GT_ERR,
                          "Invalid Node Connection to WB \r\n");
                retVal = BSP_EBADARGS;
                break;
        }

        if (retVal == BSP_SOK)
        {
            regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
            HW_SET_FIELD32(regVal, DSS_WB_ATTRIBUTES_CHANNELIN,
                           nodeSel);
            HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
        }
    }
    else
    {
        GT_0trace(
            VpsHalTrace, GT_ERR,
            "Not supported for this \
                     instance of HAL \r\n");
    }
}

/**
 *  halDssWbSetPosition
 *  Sets the Position of buffer in overlay for writeback pipeline.
 */
static void halDssWbSetPosition(VpsHal_Handle handle,
                                UInt32        inPosX,
                                UInt32        inPosY)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId == VPSHAL_DSS_DISPC_WB1)
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidPos);
        HW_SET_FIELD32(regVal, DSS_WB_POSITION_POSY,
                       inPosY);
        HW_SET_FIELD32(regVal, DSS_WB_POSITION_POSX,
                       inPosX);
        HW_WR_REG32(dispcVidObj->regOffset.vidPos, regVal);
    }
    else
    {
        GT_0trace(VpsHalTrace, GT_ERR,
                  "Not supported for this \
            instance of HAL \r\n");
    }
}

/**
 *  halDssWbSetMode
 *  Sets the Writeback mode for writeback pipeline.
 */
static void halDssWbSetMode(VpsHal_Handle handle,
                            UInt32        wbMode)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId == VPSHAL_DSS_DISPC_WB1)
    {
        if ((wbMode == DSS_WB_ATTRIBUTES_WRITEBACKMODE_CAPTURE) ||
            (wbMode == DSS_WB_ATTRIBUTES_WRITEBACKMODE_MEM2MEM))
        {
            regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
            HW_SET_FIELD32(regVal, DSS_WB_ATTRIBUTES_WRITEBACKMODE,
                           wbMode);
            HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
        }
        else
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid WbMode \r\n");
        }
    }
    else
    {
        GT_0trace(VpsHalTrace, GT_ERR,
                  "Not supported for this \
            instance of HAL \r\n");
    }
}

/**
 *  halDssVidSetOutRes
 *  Sets the Output Resolution for the video pipeline
 */
static void halDssVidSetOutRes(VpsHal_Handle handle,
                               UInt32        outHeight,
                               UInt32        outWidth)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId != VPSHAL_DSS_DISPC_WB1)
    {
        regVal  = HW_RD_REG32(dispcVidObj->regOffset.vidSize);
        regVal &= ~((UInt32) DSS_VID_SIZE_SIZEX_MASK);
        regVal |= (((UInt32) outWidth - 1U) << DSS_VID_SIZE_SIZEX_SHIFT) &
                  DSS_VID_SIZE_SIZEX_MASK;

        regVal &= ~((UInt32) DSS_VID_SIZE_SIZEY_MASK);
        regVal |= (((UInt32) outHeight - 1U) << DSS_VID_SIZE_SIZEY_SHIFT) &
                  DSS_VID_SIZE_SIZEY_MASK;

        HW_WR_REG32(dispcVidObj->regOffset.vidSize, regVal);
    }
    else
    {
        regVal  = HW_RD_REG32(dispcVidObj->regOffset.pictSize);
        regVal &= ~((UInt32) DSS_WB_PICTURE_SIZE_MEMSIZEX_MASK);
        regVal |=
            (((UInt32) outWidth - 1U) << DSS_WB_PICTURE_SIZE_MEMSIZEX_SHIFT) &
            DSS_WB_PICTURE_SIZE_MEMSIZEX_MASK;

        regVal &= ~((UInt32) DSS_WB_PICTURE_SIZE_MEMSIZEY_MASK);
        regVal |=
            (((UInt32) outHeight - 1U) << DSS_WB_PICTURE_SIZE_MEMSIZEY_SHIFT) &
            DSS_WB_PICTURE_SIZE_MEMSIZEY_MASK;

        HW_WR_REG32(dispcVidObj->regOffset.pictSize, regVal);

        regVal = HW_RD_REG32(
            SOC_DISPC_WB_BASE + DSS_WB_REGION_BASED_TOTAL_PICTURE_SIZEY);
        regVal &= ~((UInt32) DSS_WB_REGION_BASED_TOTAL_PICTURE_SIZEY_MASK);

        regVal |=
            (((UInt32) outHeight -
              1U) << DSS_WB_REGION_BASED_TOTAL_PICTURE_SIZEY_SHIFT) &
            DSS_WB_REGION_BASED_TOTAL_PICTURE_SIZEY_MASK;
        HW_WR_REG32(SOC_DISPC_WB_BASE +
                    DSS_WB_REGION_BASED_TOTAL_PICTURE_SIZEY, regVal);
    }
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_005)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-827)
 */
/**
 *  halDssVidSetInRes
 *  Sets the Input Resolution for the video pipeline
 */
static void halDssVidSetInRes(VpsHal_Handle handle,
                              UInt32        inSizeY,
                              UInt32        inSizeX)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId != VPSHAL_DSS_DISPC_WB1)
    {
        regVal  = HW_RD_REG32(dispcVidObj->regOffset.pictSize);
        regVal &= ~((UInt32) DSS_VID_PICTURE_SIZE_MEMSIZEX_MASK);
        regVal |=
            (((UInt32) (inSizeX -
                        1U)) << DSS_VID_PICTURE_SIZE_MEMSIZEX_SHIFT) &
            DSS_VID_PICTURE_SIZE_MEMSIZEX_MASK;

        regVal &= ~((UInt32) DSS_VID_PICTURE_SIZE_MEMSIZEY_MASK);
        regVal |=
            (((UInt32) (inSizeY -
                        1U)) << DSS_VID_PICTURE_SIZE_MEMSIZEY_SHIFT) &
            DSS_VID_PICTURE_SIZE_MEMSIZEY_MASK;

        HW_WR_REG32(dispcVidObj->regOffset.pictSize, regVal);
    }
    else
    {
        regVal  = HW_RD_REG32(dispcVidObj->regOffset.vidSize);
        regVal &= ~((UInt32) DSS_WB_SIZE_SIZEX_MASK);
        regVal |= (((UInt32) inSizeX - 1U) << DSS_WB_SIZE_SIZEX_SHIFT) &
                  DSS_WB_SIZE_SIZEX_MASK;

        regVal &= ~((UInt32) DSS_WB_SIZE_SIZEY_MASK);
        regVal |= (((UInt32) inSizeY - 1U) << DSS_WB_SIZE_SIZEY_SHIFT) &
                  DSS_WB_SIZE_SIZEY_MASK;

        HW_WR_REG32(dispcVidObj->regOffset.vidSize, regVal);
    }
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_005)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-826)
 */
/**
 *  halDssVidSetPos
 *  Sets the position of the window for video pipeline
 */
static void halDssVidSetPos(VpsHal_Handle handle,
                            UInt32        posY,
                            UInt32        posX)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal  = HW_RD_REG32(dispcVidObj->regOffset.vidPos);
    regVal &= ~((UInt32) DSS_VID_POSITION_POSX_MASK);
    regVal |= (((UInt32) posX) << DSS_VID_POSITION_POSX_SHIFT) &
              DSS_VID_POSITION_POSX_MASK;

    regVal &= ~((UInt32) DSS_VID_POSITION_POSY_MASK);
    regVal |= (((UInt32) posY) << DSS_VID_POSITION_POSY_SHIFT) &
              DSS_VID_POSITION_POSY_MASK;

    HW_WR_REG32(dispcVidObj->regOffset.vidPos, regVal);
}

/**
 *  halDssVidConfRepliEnable
 *  Enables or disables the replication logic
 */
static void halDssVidConfRepliEnable(VpsHal_Handle handle,
                                     UInt32        repliEnable)
{
    /* Not supported in DSS-Lite */
}

/**
 *  halDssVidConfAntiFlickerEnable
 *  Enables or disables the antiflicker logic
 */
static void halDssVidConfAntiFlickerEnable(VpsHal_Handle handle,
                                           UInt32        antiFlickerEnable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId == VPSHAL_DSS_DISPC_GFX)
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);

        regVal &= ~((UInt32) DSS_GFX_ATTRIBUTES_ANTIFLICKER_MASK);
        regVal |=
            (((UInt32) antiFlickerEnable) <<
             DSS_GFX_ATTRIBUTES_ANTIFLICKER_SHIFT) &
            DSS_GFX_ATTRIBUTES_ANTIFLICKER_MASK;

        HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
    }
}

/**
 *  halDssVidConfNibbleMode
 *  Configures the nibble mode
 */
static void halDssVidConfNibbleMode(VpsHal_Handle handle,
                                    UInt32        nibblemode)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);

    regVal &= ~((UInt32) DSS_VID_ATTRIBUTES_NIBBLEMODE_MASK);
    regVal |= (((UInt32) nibblemode) << DSS_VID_ATTRIBUTES_NIBBLEMODE_SHIFT) &
              DSS_VID_ATTRIBUTES_NIBBLEMODE_MASK;

    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
}

/**
 *  halDssVidConfClutTable
 *  Programs the clut table
 */
static void halDssVidConfClutTable(VpsHal_Handle handle,
                                   const UInt32 *clutdata)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    UInt32 index;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    for (index = 0U; index < 256U; index++)
    {
        HW_WR_REG32(dispcVidObj->regOffset.clutTable, clutdata[index]);
    }
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_021)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-2095)
 */
/**
 *  halDssWbIdleConfig
 *  Sets the idle Size and idle number for WB pipe used only in m2m wb mode.
 */
static void halDssWbIdleConfig(VpsHal_Handle handle,
                               UInt32  idleNumber,
                               UInt32  idleSize)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32                 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId == VPSHAL_DSS_DISPC_WB1)
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
        HW_SET_FIELD32(regVal, DSS_WB_ATTRIBUTES_IDLESIZE, idleSize);
        HW_SET_FIELD32(regVal, DSS_WB_ATTRIBUTES_IDLENUMBER, idleNumber);
        HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
    }
}

Int32 VpsHal_dssSetCscCoeff(VpsHal_Handle          handle,
                            const Vps_DssCscCoeff *coeff)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcVidObj *dispcVidObj;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (((Int32) TRUE == (VpsHal_dssIsVidPipe(dispcVidObj->halId))) ||
        ((Int32) TRUE == (VpsHal_dssIsWbPipe(dispcVidObj->halId))))
    {
        /* Save the passed Csc Coeff to pipe object */
        BspUtils_memcpy(&dispcVidObj->cscCoeff, coeff, sizeof (Vps_DssCscCoeff));
        /* Set the Csc Coeff for the pipeline */
        halDssVidConfCscCoeff(handle, &dispcVidObj->cscCoeff);
    }
    else
    {
        /* Not applicable for GFX */
    }

    return (retVal);
}

Int32 VpsHal_dssEnablePipeIntr(UInt32       pipeHalId,
                               UInt32       enable)
{
    Int32  retVal = BSP_SOK;
    UInt32 regVal;
    UInt32 irqEnableSetClearOffset = 0;

    if (pipeHalId >= VPSHAL_DSS_DISPC_VID_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }
    if ((enable != 0U) && (enable != 1U))
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid argument \r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        if(enable == 0)
        {
            irqEnableSetClearOffset = 4U;
        }
        switch (pipeHalId)
        {
            case VPSHAL_DSS_DISPC_VID1:
                HW_WR_REG32((SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQENABLE_SET +
                                    irqEnableSetClearOffset),
                    ((UInt32) 1U << DSS_DISPC_IRQENABLE_SET_VID1_IRQ_SHIFT));
                HW_WR_FIELD32((SOC_DISPC_VID1_BASE + DSS_VID_IRQENABLE),
                              DSS_VID_IRQENABLE_VIDBUFFERUNDERFLOW_EN,
                              enable);
                break;
            case VPSHAL_DSS_DISPC_VID2:
                HW_WR_REG32((SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQENABLE_SET +
                                    irqEnableSetClearOffset),
                    ((UInt32) 1U << DSS_DISPC_IRQENABLE_SET_VID2_IRQ_SHIFT));
                HW_WR_FIELD32((SOC_DISPC_VID2_BASE + DSS_VID_IRQENABLE),
                               DSS_VID_IRQENABLE_VIDBUFFERUNDERFLOW_EN,
                               enable);
                break;
            case VPSHAL_DSS_DISPC_GFX:
                HW_WR_REG32((SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQENABLE_SET +
                                    irqEnableSetClearOffset),
                    ((UInt32) 1U << DSS_DISPC_IRQENABLE_SET_GFX1_IRQ_SHIFT));
                HW_WR_FIELD32((SOC_DISPC_GFX1_BASE + DSS_GFX_IRQENABLE),
                              DSS_GFX_IRQENABLE_GFXBUFFERUNDERFLOW_EN,
                              enable);
                break;
            case VPSHAL_DSS_DISPC_WB1:
                HW_WR_REG32((SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQENABLE_SET +
                                    irqEnableSetClearOffset),
                    ((UInt32) 1U << DSS_DISPC_IRQENABLE_SET_WB_IRQ_SHIFT));
                regVal = HW_RD_REG32(SOC_DISPC_WB_BASE + DSS_WB_IRQENABLE);
                HW_SET_FIELD32(regVal, DSS_WB_IRQENABLE_WBBUFFEROVERFLOW_EN,
                               enable);
                HW_SET_FIELD32(regVal, DSS_WB_IRQENABLE_WBUNCOMPLETEERROR_EN,
                               enable);
                HW_SET_FIELD32(regVal, DSS_WB_IRQENABLE_WBFRAMEDONE_EN,
                               enable);
                HW_SET_FIELD32(regVal, DSS_WB_IRQSTATUS_WBREGIONBASEDEVENT_IRQ,
                               enable);
                HW_SET_FIELD32(regVal, DSS_WB_IRQSTATUS_WBFRAMESYNC_IRQ,
                               enable);
                HW_WR_REG32((SOC_DISPC_WB_BASE + DSS_WB_IRQENABLE), regVal);
                break;
            default:
                retVal = BSP_EBADARGS;
                break;
        }
    }
    return retVal;
}

