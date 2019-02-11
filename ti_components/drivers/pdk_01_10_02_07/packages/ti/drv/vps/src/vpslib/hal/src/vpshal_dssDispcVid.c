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
 *  \file vpshal_dssDispcVid.c
 *
 *  \brief VPS DSS Dispc video pipeline HAL file.
 *  This file implements the HAL APIs of the DSS DISPC Video pipelines.
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

#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_dss.h>
#include <ti/csl/soc.h>
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
    UInt32 fir;
    /**< offset of FIR(resize factor of scaling) register for this instance */
    UInt32 pictSize;
    /**< offset of Picture Size register for this instance */
    UInt32 accumu;
    /**< offset of resize accumulator Size register for this instance
     *  [0] for Ping and [1] for pong with external trigger , based on field
     *  polarity */
    UInt32 firCoefH;
    /**< offset of resizer filter coefficient register for this instance */
    UInt32 firCoefHV;
    /**< offset of resizer filter coefficient register for this instance */
    UInt32 convCoef[5];
    /**< offset of array of color conversion coeff registers for this
     *   instance, coeff0 - coeff4 */
    UInt32 firCoefV;
    /**< offset of resizer filter coefficient register for this instance */
    UInt32 preload;
    /**< offset of preload register for this instance */
    UInt32 vidpos2;
    /**< offset of Position2 register for this instance
     *   Used in framepacking mode */
    UInt32 vidBaseAddUv;
    /**< offset of Base Address of UV bufferregister for this instance */
    UInt32 vidAttrib2;
    /**< offset of attributes2 register for this instance */
    UInt32 fir2;
    /**< offset of FIR(resize factor of scaling) fir cb and cr
     *   register for this instance */
    UInt32 accumu2;
    /**< offset of resize accumulator Size register for this instance
     *   it is used for cb and cr settings [0] for Ping and [1] for pong
     *   with external trigger , based on field
     *   polarity */
    UInt32 firCoefH2;
    /**< offset of resizer filter coefficient register for this instance
     *   it is used for Cb and Cr settings in case of YUV formats*/
    UInt32 firCoefHV2;
    /**< offset of resizer filter coefficient register for this instance
     *   it is used for Cb and Cr settings in case of YUV formats*/
    UInt32 firCoefV2;
    /**< offset of resizer filter coefficient register for this instance */
    UInt32 mflagThre;
    /**< offset of Mflag Threshold register for this instance */
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
    UInt32              dispcBaseAddr;
    /**< DISPC Base address. */
    VpsHal_VidRegOffset regOffset;
    /**< Structure to store offsets of all the registers related to Overlay */
    Vps_DssCscCoeff     cscCoeff;
    /**< Structure to store store the csc coefficients for the pipeline */
} VpsHal_DssDispcVidObj;

/* Scalar Coeff */
typedef struct {
    Int8  hc4Vc22;
    Int8  hc3Vc2;
    UInt8 hc2Vc1;
    Int8  hc1Vc0;
    Int8  hc0Vc00;
}VpsHal_DssScCoeff;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 halDssVidInitInstance(VpsHal_DssDispcVidObj *dispcVidObj);

static void halDssVidSetFormat(VpsHal_Handle handle, UInt32 dataFmt);

static void halDssVidConfYuvChromaReSampling(VpsHal_Handle handle,
                                             UInt32        chromaSampling);

static void halDssVidConfCscFullRange(VpsHal_Handle handle,
                                      UInt32        cscFullRngEnable);

static void halDssVidConfCscCoeff(VpsHal_Handle          handle,
                                  const Vps_DssCscCoeff *coeff);

static void halDssVidConfCscEnable(VpsHal_Handle handle,
                                   UInt32        cscEnable);

static void halDssVidSetRotation(VpsHal_Handle handle,
                                 UInt32        rotation);

static void halDssVidSetDoubleStride(VpsHal_Handle handle,
                                     UInt32        doubleStride);

static Int32 halDssVidSetScalerCoeff(VpsHal_Handle            handle,
                                     const VpsHal_DssScCoeff *vCoef,
                                     const VpsHal_DssScCoeff *hCoef);

const VpsHal_DssScCoeff *halDssVidGetScalarCoeff(UInt32 inSize,
                                                 UInt32 outSize);

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

static void halDssWbSetMode(VpsHal_Handle handle,
                            UInt32        wbMode);

static void halDssWbSetInNode(VpsHal_Handle handle,
                              UInt32        inNode);

static void halDssWbSetTruncation(VpsHal_Handle handle, UInt32 dataFmt);

static void halDssVidDmaBufThreConf(VpsHal_Handle handle,
                                    UInt32        bufLowThreshold,
                                    UInt32        bufHighThreshold,
                                    UInt32        bufPreloadType);

static void halDssVidDmaSetBurstAttributes(VpsHal_Handle handle,
                                           UInt32        burstSize,
                                           UInt32        burstType);

static void halDssWbIdleConfig(VpsHal_Handle handle,
                               UInt32  idleNumber,
                               UInt32  idleSize);

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

Int32 halDssConvFvid2DataFmt(UInt32 handleId, UInt32 fvid2Fmt);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  DISP VID  objects - Module variable to store information about each video
 *  piepline instance .Note: If the number of Video pipeline instance increase,
 *  then VPSHAL_DSS_DISPC_PIPE_MAX_INST macro should be changed accordingly.
 */
static VpsHal_DssDispcVidObj   gDispcVidHalObj[VPSHAL_DSS_DISPC_PIPE_MAX_INST];

/**
 * Coefficients for BT601-5 YUV to RGB conversion.
 *
 */
/* Uncomment below csc coefficients to set the limited range coeff
 * by default, or pass these parameters from application using the ioctl
 * IOCTL_VPS_DISP_SET_CSC_COEFF.

static const Vps_DssCscCoeff   gVidCscCoeff =
{298, 409,            0,
 298, -((Int16) 208), -((Int16) 100),
 298, 0,              517,
 0,   0,              0};

 */

/* Below is the full range csc conversion parameters. */
static const Vps_DssCscCoeff   gVidCscCoeff =
{256, 359,            0,
 256, -((Int16) 183), -((Int16) 87),
 256, 0,              454,
 0,   0,              0};

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
 0,             0,             0};
 */

/* Below is the full range csc conversion parameters. */
static const Vps_DssCscCoeff   gWbCscCoeff =
{76,            150,           29,
 128,           -((Int16) 107), -((Int16) 20),
 -((Int16) 43), -((Int16) 84), 128,
 0,             0,             0};

/**
 * Scalar coefficient for different scaling ratios.
 *
 */
static const VpsHal_DssScCoeff coefM8[8] =
{
    {0,             0,              128, 0,             0            },
    {-((Int16) 2),  14,             125, -((Int16) 10), 1            },
    {-((Int16) 6),  33,             114, -((Int16) 15), 2            },
    {-((Int16) 10), 55,             98,  -((Int16) 16), 1            },
    {0,             -((Int16) 14),  78,  78,            -((Int16) 14)},
    {1,             -((Int16) 16),  98,  55,            -((Int16) 10)},
    {2,             -((Int16) 15),  114, 33,            -((Int16) 6) },
    {1,             -((Int16) 10),  125, 14,            -((Int16) 2) }
};

static const VpsHal_DssScCoeff coefM9[8] = {
    {-((Int16) 3),  10,            114, 10,            -((Int16) 3)},
    {-((Int16) 6),  24,            111, 0,             -((Int16) 1)},
    {-((Int16) 8),  40,            103, -((Int16) 7),  0},
    {-((Int16) 11), 58,            91,  -((Int16) 11), 1},
    {0,             -((Int16) 12), 76,  76,            -((Int16) 12)},
    {1,             -((Int16) 11), 91,  58,            -((Int16) 11)},
    {0,             -((Int16) 7),  103, 40,            -((Int16) 8)},
    {-((Int16) 1),  0,             111, 24,            -((Int16) 6)},
};

static const VpsHal_DssScCoeff coefM10[8] = {
    {-((Int16) 4), 18, 100, 18, -((Int16) 4)},
    {-((Int16) 6), 30, 99,  8,  -((Int16) 3)},
    {-((Int16) 8), 44, 93,  0,  -((Int16) 1)},
    {-((Int16) 9), 58, 84,  -((Int16) 5), 0 },
    {0,  -((Int16) 8), 72,  72, -((Int16) 8)},
    {0,  -((Int16) 5), 84,  58, -((Int16) 9)},
    {-((Int16) 1), 0,  93,  44, -((Int16) 8)},
    {-((Int16) 3), 8,  99,  30, -((Int16) 6)},
};

static const VpsHal_DssScCoeff coefM11[8] = {
    {-((Int16) 5), 23, 92, 23, -((Int16) 5)},
    {-((Int16) 6), 34, 90, 13, -((Int16) 3)},
    {-((Int16) 6), 45, 85, 6,  -((Int16) 2)},
    {-((Int16) 6), 57, 78, 0,  -((Int16) 1)},
    {0,  -((Int16) 4), 68, 68, -((Int16) 4)},
    {-((Int16) 1), 0,  78, 57, -((Int16) 6)},
    {-((Int16) 2), 6,  85, 45, -((Int16) 6)},
    {-((Int16) 3), 13, 90, 34, -((Int16) 6)},
};

static const VpsHal_DssScCoeff coefM12[8] = {
    {-((Int16) 4), 26, 84, 26, -((Int16) 4)},
    {-((Int16) 5), 36, 82, 18, -((Int16) 3)},
    {-((Int16) 4), 46, 78, 10, -((Int16) 2)},
    {-((Int16) 3), 55, 72, 5,  -((Int16) 1)},
    {0,  0,  64, 64, 0 },
    {-((Int16) 1), 5,  72, 55, -((Int16) 3)},
    {-((Int16) 2), 10, 78, 46, -((Int16) 4)},
    {-((Int16) 3), 18, 82, 36, -((Int16) 5)},
};

static const VpsHal_DssScCoeff coefM13[8] = {
    {-((Int16) 3), 28, 78, 28, -((Int16) 3)},
    {-((Int16) 3), 37, 76, 21, -((Int16) 3)},
    {-((Int16) 2), 45, 73, 14, -((Int16) 2)},
    {0,  53, 68, 8,  -((Int16) 1)},
    {0,  3,  61, 61, 3 },
    {-((Int16) 1), 8,  68, 53, 0 },
    {-((Int16) 2), 14, 73, 45, -((Int16) 2)},
    {-((Int16) 3), 21, 76, 37, -((Int16) 3)},
};

static const VpsHal_DssScCoeff coefM14[8] = {
    {-((Int16) 2), 30, 72, 30, -((Int16) 2)},
    {-((Int16) 1), 37, 71, 23, -((Int16) 2)},
    {0,  45, 69, 16, -((Int16) 2)},
    {3,  52, 64, 10, -((Int16) 1)},
    {0,  6,  58, 58, 6 },
    {-((Int16) 1), 10, 64, 52, 3 },
    {-((Int16) 2), 16, 69, 45, 0 },
    {-((Int16) 2), 23, 71, 37, -((Int16) 1)},
};

static const VpsHal_DssScCoeff coefM16[8] = {
    {0,  31, 66, 31, 0 },
    {1,  38, 65, 25, -((Int16) 1)},
    {3,  44, 62, 20, -((Int16) 1)},
    {6,  49, 59, 14, 0 },
    {0,  10, 54, 54, 10},
    {0,  14, 59, 49, 6 },
    {-((Int16) 1), 20, 62, 44, 3 },
    {-((Int16) 1), 25, 65, 38, 1 },
};

static const VpsHal_DssScCoeff coefM19[8] = {
    {3,  32, 58, 32, 3 },
    {4,  38, 58, 27, 1 },
    {7,  42, 55, 23, 1 },
    {10, 46, 54, 18, 0 },
    {0,  14, 50, 50, 14},
    {0,  18, 54, 46, 10},
    {1,  23, 55, 42, 7 },
    {1,  27, 58, 38, 4 },
};

static const VpsHal_DssScCoeff coefM22[8] = {
    {4,  33, 54, 33, 4 },
    {6,  37, 54, 28, 3 },
    {9,  41, 53, 24, 1 },
    {12, 45, 51, 20, 0 },
    {0,  16, 48, 48, 16},
    {0,  20, 51, 45, 12},
    {1,  24, 53, 41, 9 },
    {3,  28, 54, 37, 6 },
};

static const VpsHal_DssScCoeff coefM26[8] = {
    {6,  33, 50, 33, 6 },
    {8,  36, 51, 29, 4 },
    {11, 40, 50, 25, 2 },
    {14, 43, 48, 22, 1 },
    {0,  18, 46, 46, 18},
    {1,  22, 48, 43, 14},
    {2,  25, 50, 40, 11},
    {4,  29, 51, 36, 8 },
};

static const VpsHal_DssScCoeff coefM32[8] = {
    {7,  33, 48, 33, 7 },
    {10, 36, 48, 29, 5 },
    {13, 39, 47, 26, 3 },
    {16, 42, 46, 23, 1 },
    {0,  19, 45, 45, 19},
    {1,  23, 46, 42, 16},
    {3,  26, 47, 39, 13},
    {5,  29, 48, 36, 10},
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
    GT_assert(VpsHalTrace, numInst <= VPSHAL_DSS_DISPC_PIPE_MAX_INST);
    GT_assert(VpsHalTrace, instPrms != NULL);

    /* Initialize DISPC VID Objects to zero */
    BspUtils_memset(gDispcVidHalObj, 0, sizeof (gDispcVidHalObj));

    for (instCnt = 0; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  instPrms[instCnt].halId < VPSHAL_DSS_DISPC_VID_INST_ID_MAX);

        dispcVidObj                = &gDispcVidHalObj[instCnt];
        dispcVidObj->halId         = instPrms[instCnt].halId;
        dispcVidObj->dispcBaseAddr = SOC_DISPC_BASE;

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
    GT_assert(VpsHalTrace, NULL != openPrms);
    GT_assert(VpsHalTrace,
              openPrms->halId < VPSHAL_DSS_DISPC_VID_INST_ID_MAX);

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
    GT_assert(VpsHalTrace, NULL != handle);

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
 *          DOX_REQ_TAG(PDK-858) DOX_REQ_TAG(PDK-859) DOX_REQ_TAG(PDK-860)
 */
/**
 *  halDssVidInitInstance
 *  Initialize the DISPC VID instance by updating the register offsets
 */
static Int32 halDssVidInitInstance(VpsHal_DssDispcVidObj *dispcVidObj)
{
    Int32 retVal = BSP_SOK;

    switch (dispcVidObj->halId)
    {
        case VPSHAL_DSS_DISPC_VID1:
            dispcVidObj->regOffset.vidBaseAdd =
                dispcVidObj->dispcBaseAddr + (UInt32) DSS_DISPC_VID1_BA(0U);
            dispcVidObj->regOffset.vidPos =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_POSITION;
            dispcVidObj->regOffset.vidSize =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_SIZE;
            dispcVidObj->regOffset.vidAttrib =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_ATTRIBUTES;
            dispcVidObj->regOffset.bufThresh =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_BUF_THRESHOLD;
            dispcVidObj->regOffset.bufSizeStat =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_BUF_SIZE_STATUS;
            dispcVidObj->regOffset.rowInc =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_ROW_INC;
            dispcVidObj->regOffset.pixelInc =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_PIXEL_INC;
            dispcVidObj->regOffset.fir =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_FIR;
            dispcVidObj->regOffset.pictSize =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_PICTURE_SIZE;
            dispcVidObj->regOffset.accumu =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_ACCU(0U);
            dispcVidObj->regOffset.firCoefH =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_FIR_COEF_H(0U);
            dispcVidObj->regOffset.firCoefHV =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_FIR_COEF_HV(0U);
            dispcVidObj->regOffset.convCoef[0] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_CONV_COEF0;
            dispcVidObj->regOffset.convCoef[1] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_CONV_COEF1;
            dispcVidObj->regOffset.convCoef[2] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_CONV_COEF2;
            dispcVidObj->regOffset.convCoef[3] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_CONV_COEF3;
            dispcVidObj->regOffset.convCoef[4] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_CONV_COEF4;
            dispcVidObj->regOffset.firCoefV =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_FIR_COEF_V(0U);
            dispcVidObj->regOffset.preload =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_PRELOAD;
            dispcVidObj->regOffset.vidpos2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_POSITION2;
            dispcVidObj->regOffset.vidBaseAddUv =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_BA_UV(0U);
            dispcVidObj->regOffset.vidAttrib2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_ATTRIBUTES2;
            dispcVidObj->regOffset.fir2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_FIR2;
            dispcVidObj->regOffset.accumu2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_ACCU2(0U);
            dispcVidObj->regOffset.firCoefH2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_FIR_COEF_H2(0U);
            dispcVidObj->regOffset.firCoefHV2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_FIR_COEF_HV2(0U);
            dispcVidObj->regOffset.firCoefV2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_FIR_COEF_V2(0U);
            dispcVidObj->regOffset.mflagThre =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID1_MFLAG_THRESHOLD;
            break;

        case VPSHAL_DSS_DISPC_VID2:
            dispcVidObj->regOffset.vidBaseAdd =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_BA(0U);
            dispcVidObj->regOffset.vidPos =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_POSITION;
            dispcVidObj->regOffset.vidSize =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_SIZE;
            dispcVidObj->regOffset.vidAttrib =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_ATTRIBUTES;
            dispcVidObj->regOffset.bufThresh =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_BUF_THRESHOLD;
            dispcVidObj->regOffset.bufSizeStat =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_BUF_SIZE_STATUS;
            dispcVidObj->regOffset.rowInc =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_ROW_INC;
            dispcVidObj->regOffset.pixelInc =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_PIXEL_INC;
            dispcVidObj->regOffset.fir =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_FIR;
            dispcVidObj->regOffset.pictSize =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_PICTURE_SIZE;
            dispcVidObj->regOffset.accumu =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_ACCU(0U);
            dispcVidObj->regOffset.firCoefH =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_FIR_COEF_H(0U);
            dispcVidObj->regOffset.firCoefHV =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_FIR_COEF_HV(0U);
            dispcVidObj->regOffset.convCoef[0] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_CONV_COEF0;
            dispcVidObj->regOffset.convCoef[1] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_CONV_COEF1;
            dispcVidObj->regOffset.convCoef[2] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_CONV_COEF2;
            dispcVidObj->regOffset.convCoef[3] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_CONV_COEF3;
            dispcVidObj->regOffset.convCoef[4] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_CONV_COEF4;
            dispcVidObj->regOffset.firCoefV =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_FIR_COEF_V(0U);
            dispcVidObj->regOffset.preload =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_PRELOAD;
            dispcVidObj->regOffset.vidpos2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_POSITION2;
            dispcVidObj->regOffset.vidBaseAddUv =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_BA_UV(0U);
            dispcVidObj->regOffset.vidAttrib2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_ATTRIBUTES2;
            dispcVidObj->regOffset.fir2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_FIR2;
            dispcVidObj->regOffset.accumu2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_ACCU2(0U);
            dispcVidObj->regOffset.firCoefH2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_FIR_COEF_H2(0U);
            dispcVidObj->regOffset.firCoefHV2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_FIR_COEF_HV2(0U);
            dispcVidObj->regOffset.firCoefV2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_FIR_COEF_V2(0U);
            dispcVidObj->regOffset.mflagThre =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID2_MFLAG_THRESHOLD;
            break;

        case VPSHAL_DSS_DISPC_VID3:
            dispcVidObj->regOffset.vidBaseAdd =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_BA(0U);
            dispcVidObj->regOffset.vidPos =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_POSITION;
            dispcVidObj->regOffset.vidSize =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_SIZE;
            dispcVidObj->regOffset.vidAttrib =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_ATTRIBUTES;
            dispcVidObj->regOffset.bufThresh =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_BUF_THRESHOLD;
            dispcVidObj->regOffset.bufSizeStat =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_BUF_SIZE_STATUS;
            dispcVidObj->regOffset.rowInc =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_ROW_INC;
            dispcVidObj->regOffset.pixelInc =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_PIXEL_INC;
            dispcVidObj->regOffset.fir =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_FIR;
            dispcVidObj->regOffset.pictSize =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_PICTURE_SIZE;
            dispcVidObj->regOffset.accumu =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_ACCU(0U);
            dispcVidObj->regOffset.firCoefH =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_FIR_COEF_H(0U);
            dispcVidObj->regOffset.firCoefHV =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_FIR_COEF_HV(0U);
            dispcVidObj->regOffset.convCoef[0] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_CONV_COEF0;
            dispcVidObj->regOffset.convCoef[1] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_CONV_COEF1;
            dispcVidObj->regOffset.convCoef[2] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_CONV_COEF2;
            dispcVidObj->regOffset.convCoef[3] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_CONV_COEF3;
            dispcVidObj->regOffset.convCoef[4] =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_CONV_COEF4;
            dispcVidObj->regOffset.firCoefV =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_FIR_COEF_V(0U);
            dispcVidObj->regOffset.preload =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_PRELOAD;
            dispcVidObj->regOffset.vidpos2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_POSITION2;
            dispcVidObj->regOffset.vidBaseAddUv =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_BA_UV(0U);
            dispcVidObj->regOffset.vidAttrib2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_ATTRIBUTES2;
            dispcVidObj->regOffset.fir2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_FIR2;
            dispcVidObj->regOffset.accumu2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_ACCU2(0U);
            dispcVidObj->regOffset.firCoefH2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_FIR_COEF_H2(0U);
            dispcVidObj->regOffset.firCoefHV2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_FIR_COEF_HV2(0U);
            dispcVidObj->regOffset.firCoefV2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_FIR_COEF_V2(0U);
            dispcVidObj->regOffset.mflagThre =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_VID3_MFLAG_THRESHOLD;
            break;

        case VPSHAL_DSS_DISPC_GFX:
            dispcVidObj->regOffset.vidBaseAdd =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_GFX_BA(0U);
            dispcVidObj->regOffset.vidPos =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_GFX_POSITION;
            dispcVidObj->regOffset.vidSize =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_GFX_SIZE;
            dispcVidObj->regOffset.vidAttrib =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_GFX_ATTRIBUTES;
            dispcVidObj->regOffset.bufThresh =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_GFX_BUF_THRESHOLD;
            dispcVidObj->regOffset.bufSizeStat =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_GFX_BUF_SIZE_STATUS;
            dispcVidObj->regOffset.rowInc =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_GFX_ROW_INC;
            dispcVidObj->regOffset.pixelInc =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_GFX_PIXEL_INC;
            dispcVidObj->regOffset.preload =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_GFX_PRELOAD;
            dispcVidObj->regOffset.vidpos2 =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_GFX_POSITION2;
            dispcVidObj->regOffset.mflagThre =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_GFX_MFLAG_THRESHOLD;
            break;

        case VPSHAL_DSS_DISPC_WB1:
            dispcVidObj->regOffset.vidBaseAdd = dispcVidObj->dispcBaseAddr +
                                                DSS_DISPC_WB_BA(0);
            dispcVidObj->regOffset.vidSize = dispcVidObj->dispcBaseAddr +
                                             DSS_DISPC_WB_SIZE;
            dispcVidObj->regOffset.vidAttrib = dispcVidObj->dispcBaseAddr +
                                               DSS_DISPC_WB_ATTRIBUTES;
            dispcVidObj->regOffset.bufThresh = dispcVidObj->dispcBaseAddr +
                                               DSS_DISPC_WB_BUF_THRESHOLD;
            dispcVidObj->regOffset.bufSizeStat = dispcVidObj->dispcBaseAddr +
                                                 DSS_DISPC_WB_BUF_SIZE_STATUS;
            dispcVidObj->regOffset.fir = dispcVidObj->dispcBaseAddr +
                                         DSS_DISPC_WB_FIR;
            dispcVidObj->regOffset.pictSize = dispcVidObj->dispcBaseAddr +
                                              DSS_DISPC_WB_PICTURE_SIZE;
            dispcVidObj->regOffset.accumu = dispcVidObj->dispcBaseAddr +
                                            DSS_DISPC_WB_ACCU(0);
            dispcVidObj->regOffset.firCoefH =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_WB_FIR_COEF_H(0U);
            dispcVidObj->regOffset.firCoefHV =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_WB_FIR_COEF_HV(0U);
            dispcVidObj->regOffset.firCoefV =
                dispcVidObj->dispcBaseAddr + DSS_DISPC_WB_FIR_COEF_V(0U);
            dispcVidObj->regOffset.convCoef[0] = dispcVidObj->dispcBaseAddr +
                                                 DSS_DISPC_WB_CONV_COEF0;
            dispcVidObj->regOffset.convCoef[1] = dispcVidObj->dispcBaseAddr +
                                                 DSS_DISPC_WB_CONV_COEF1;
            dispcVidObj->regOffset.convCoef[2] = dispcVidObj->dispcBaseAddr +
                                                 DSS_DISPC_WB_CONV_COEF2;
            dispcVidObj->regOffset.convCoef[3] = dispcVidObj->dispcBaseAddr +
                                                 DSS_DISPC_WB_CONV_COEF3;
            dispcVidObj->regOffset.convCoef[4] = dispcVidObj->dispcBaseAddr +
                                                 DSS_DISPC_WB_CONV_COEF4;
            dispcVidObj->regOffset.vidBaseAddUv = dispcVidObj->dispcBaseAddr +
                                                  DSS_DISPC_WB_BA_UV(0);
            dispcVidObj->regOffset.vidAttrib2 = dispcVidObj->dispcBaseAddr +
                                                DSS_DISPC_WB_ATTRIBUTES2;
            dispcVidObj->regOffset.fir2 = dispcVidObj->dispcBaseAddr +
                                          DSS_DISPC_WB_FIR2;
            dispcVidObj->regOffset.accumu2 = dispcVidObj->dispcBaseAddr +
                                             DSS_DISPC_WB_ACCU2(0);
            dispcVidObj->regOffset.mflagThre = dispcVidObj->dispcBaseAddr +
                                               DSS_DISPC_WB_MFLAG_THRESHOLD;
            dispcVidObj->regOffset.firCoefH2 = dispcVidObj->dispcBaseAddr +
                                               DSS_DISPC_WB_FIR_COEF_H2(0);
            dispcVidObj->regOffset.firCoefV2 = dispcVidObj->dispcBaseAddr +
                                               DSS_DISPC_WB_FIR_COEF_V2(0);
            dispcVidObj->regOffset.firCoefHV2 = dispcVidObj->dispcBaseAddr +
                                                DSS_DISPC_WB_FIR_COEF_HV2(0);
            dispcVidObj->regOffset.rowInc = dispcVidObj->dispcBaseAddr +
                                                DSS_DISPC_WB_ROW_INC;
            dispcVidObj->regOffset.pixelInc = dispcVidObj->dispcBaseAddr +
                                                DSS_DISPC_WB_PIXEL_INC;
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
        case VPSHAL_DSS_DISPC_VID3:
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

    return (retVal);
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
    Int32 fmt;
    VpsHal_DssDispcVidObj *dispcVidObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != gfxConf);

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((Int32) FALSE == (VpsHal_dssIsGfxPipe(dispcVidObj->halId)))
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
        halDssVidSetOutRes(handle, gfxConf->inFmt.height, gfxConf->inFmt.width);
        halDssVidSetPos(handle, gfxConf->posY, gfxConf->posX);
        halDssVidConfRepliEnable(handle, gfxConf->repliEnable);
        halDssVidConfAntiFlickerEnable(handle, gfxConf->antiFlickerEnable);
    }

    return (retVal);
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
    Int32  fmt;
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 scEnable = 0;
    const VpsHal_DssScCoeff *vCoef, *hCoef;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != vidConf);

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
        halDssVidSetInRes(handle, vidConf->inFmt.height, vidConf->inFmt.width);
        halDssVidSetOutRes(handle, vidConf->outHeight, vidConf->outWidth);
        halDssVidSetPos(handle, vidConf->posY, vidConf->posX);

        if ((vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_YUYV) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_YUV420SP_UV) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_UYVY))
        {
            halDssVidConfCscEnable(handle, (UInt32) 1U);
        }
        else
        {
            halDssVidConfCscEnable(handle, (UInt32) 0U);
        }

        halDssVidConfRepliEnable(handle, vidConf->repliEnable);

        /* For 1D buffers double stride will be equal to 0 */
        /* Only 1D is supported for Tda2xx platform */
        if (vidConf->inFmt.dataFormat == FVID2_DF_YUV420SP_UV)
        {
            /* Errata ID: i631 - for 1D burst mode in YUV420 - doublestride
             * should be set to 0 and rotation should be either 90 or 270. */
            halDssVidSetDoubleStride(handle, 0);
            halDssVidSetRotation(
                handle,
                (UInt32)
                DSS_DISPC_VID1_ATTRIBUTES_ROTATION_ROT90);
        }
        else
        {
            halDssVidSetRotation(
                handle,
                (UInt32)
                DSS_DISPC_VID1_ATTRIBUTES_ROTATION_NOROT);
        }

        if ((0 != vidConf->scEnable) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_YUV420SP_UV) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_YUYV) ||
            (vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_UYVY))
        {
            if ((0 != vidConf->scEnable) &&
                (vidConf->inFmt.width != vidConf->outWidth))
            {
                scEnable |= DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_HRESIZE;
            }
            if ((0 != vidConf->scEnable) &&
                (vidConf->inFmt.height != vidConf->outHeight))
            {
                scEnable |= DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_VRESIZE;
            }

            vCoef = halDssVidGetScalarCoeff(vidConf->inFmt.height,
                                            vidConf->outHeight);
            hCoef = halDssVidGetScalarCoeff(vidConf->inFmt.width,
                                            vidConf->outWidth);

            retVal += halDssVidSetScalerCoeff(handle, vCoef, hCoef);

            if (retVal == BSP_SOK)
            {
                halDssVidConfFir(handle, vidConf->inFmt.width,
                                 vidConf->inFmt.height,
                                 vidConf->outWidth,
                                 vidConf->outHeight);

                halDssVidConfVerticalTapsEnable(
                    handle,
                    (UInt32) DSS_DISPC_VID1_ATTRIBUTES_VERTICALTAPS_TAPS5);

                if ((vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_YUYV) ||
                    (vidConf->inFmt.dataFormat == FVID2_DF_YUV422I_UYVY))
                {
                    scEnable |= DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_HRESIZE;
                    halDssVidConfFir2(handle,
                                      (UInt32) (vidConf->inFmt.width / 2),
                                      vidConf->inFmt.height,
                                      vidConf->outWidth,
                                      vidConf->outHeight);
                }

                if (vidConf->inFmt.dataFormat == FVID2_DF_YUV420SP_UV)
                {
                    scEnable |= DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_HRESIZE;
                    scEnable |= DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_VRESIZE;
                    halDssVidConfFir2(handle,
                                      (UInt32) (vidConf->inFmt.width / 2),
                                      (UInt32) (vidConf->inFmt.height / 2),
                                      vidConf->outWidth,
                                      vidConf->outHeight);
                }

                halDssVidConfScalerEnable(handle, scEnable);
            }
        }
        else
        {
            /* Disable scalar */
            halDssVidConfScalerEnable(handle, 0U);
        }

        halDssVidConfCscFullRange(handle, vidConf->cscFullRngEnable);

        if (vidConf->inFmt.dataFormat == FVID2_DF_YUV420SP_UV)
        {
            halDssVidConfYuvChromaReSampling(handle, (UInt32) 1U);
        }
        else
        {
            halDssVidConfYuvChromaReSampling(handle, 0);
        }

        if (vc1Cfg != NULL)
        {
            halDssVidSetVc1Coeff(handle, vc1Cfg->rangeY, vc1Cfg->rangeUV);
            halDssVidVc1Enable(handle, vc1Cfg->enable);
        }
        else
        {
            halDssVidVc1Enable(handle, (UInt32) FALSE);
        }
    }

    return (retVal);
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
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_VID1_ATTRIBUTES_ZORDER,
            pipeCfg->zorder);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_VID1_ATTRIBUTES_ZORDERENABLE,
            pipeCfg->zorderEnable);
        HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);

        /* Note: Global alpha is part of overlay - so not done here */

        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_VID1_ATTRIBUTES_PREMULTIPHYALPHA,
            pipeCfg->preMultiplyAlpha);

        if (dispcVidObj->halId == VPSHAL_DSS_DISPC_GFX)
        {
            regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
            HW_SET_FIELD32(
                regVal, DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT2, channelOut2);
            HW_SET_FIELD32(
                regVal, DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT, channelOut);
            HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
        }
        else
        {
            regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
            HW_SET_FIELD32(
                regVal, DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT2, channelOut2);
            HW_SET_FIELD32(
                regVal, DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT, channelOut);
            HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
        }
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_018)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-995) DOX_REQ_TAG(PDK-996)
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
 *  \param wbConf           Pointer to the DispcwbConf structure.
 *                                  This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssConfWbPipe(VpsHal_Handle                   handle,
                           const VpsHal_DssDispcWbPipeCfg *wbConf)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 scEnable = 0;
    Int32  fmt;
    UInt32 cscEnable = 1U;
    Bool   dataFmtYuv, dataFmtRgb;
    const VpsHal_DssScCoeff *vCoef, *hCoef;

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

        halDssWbSetInNode(handle, wbConf->inNode);
        halDssWbSetTruncation(handle, wbConf->outFmt.dataFormat);

        dataFmtRgb = (Bool) Fvid2_isDataFmtRgb(wbConf->inDataFormat);
        dataFmtYuv = (Bool) Fvid2_isDataFmtYuv(wbConf->outFmt.dataFormat);

        if ((TRUE == dataFmtRgb) && (TRUE == dataFmtYuv))
        {
            halDssVidConfCscEnable(handle, cscEnable);
        }
        else
        {
            halDssVidConfCscEnable(handle, 0);
        }

        if (wbConf->scEnable != 0)
        {
            if (wbConf->inWidth != wbConf->outFmt.width)
            {
                scEnable |= DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_HRESIZE;
            }
            if (wbConf->inHeight != wbConf->outFmt.height)
            {
                scEnable |= DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_VRESIZE;
            }

            vCoef = halDssVidGetScalarCoeff(wbConf->inHeight,
                                            wbConf->outFmt.height);
            hCoef = halDssVidGetScalarCoeff(wbConf->inWidth,
                                            wbConf->outFmt.width);

            retVal += halDssVidSetScalerCoeff(handle, vCoef, hCoef);

            if (retVal == BSP_SOK)
            {
                halDssVidConfFir(handle, wbConf->inWidth,
                                 wbConf->inHeight,
                                 wbConf->outFmt.width,
                                 wbConf->outFmt.height);
                /* For scaling in writeback pipeline there is a limitation,
                 * maximum input width of 1280 pixels using 32-bit pixels and
                 * 5-tap, and 2560 pixels using 32-bit pixels and 3-tap.
                 * No limitation on the input height. */
                if (wbConf->inWidth > 1280)
                {
                    halDssVidConfVerticalTapsEnable(
                        handle, DSS_DISPC_VID1_ATTRIBUTES_VERTICALTAPS_TAPS3);
                }
                else
                {
                    halDssVidConfVerticalTapsEnable(
                        handle, DSS_DISPC_VID1_ATTRIBUTES_VERTICALTAPS_TAPS5);
                }

                if ((wbConf->outFmt.dataFormat == FVID2_DF_YUV422I_YUYV) ||
                    (wbConf->outFmt.dataFormat == FVID2_DF_YUV422I_UYVY))
                {
                    scEnable |= DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_HRESIZE;
                    halDssVidConfFir2(handle, wbConf->inWidth,
                                      wbConf->inHeight,
                                      (UInt32) (wbConf->outFmt.width / 2),
                                      wbConf->outFmt.height);
                }
                if (wbConf->outFmt.dataFormat == FVID2_DF_YUV420SP_UV)
                {
                    scEnable |= DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_HRESIZE;
                    scEnable |= DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_VRESIZE;
                    halDssVidConfFir2(handle, wbConf->inWidth,
                                      wbConf->inHeight,
                                      (UInt32) (wbConf->outFmt.width / 2),
                                      (UInt32) (wbConf->outFmt.height / 2));
                }

                halDssVidConfScalerEnable(handle, scEnable);
            }
        }
        else
        {
            if (wbConf->outFmt.dataFormat == FVID2_DF_YUV420SP_UV)
            {
                halDssVidConfScalerEnable(
                    handle,
                    (UInt32) (DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_VRESIZE |
                              DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE_HRESIZE));

                vCoef = halDssVidGetScalarCoeff(wbConf->inHeight,
                                                wbConf->outFmt.height);
                hCoef = halDssVidGetScalarCoeff(wbConf->inWidth,
                                                wbConf->outFmt.width);

                retVal += halDssVidSetScalerCoeff(handle, vCoef, hCoef);

                if (retVal == BSP_SOK)
                {
                    halDssVidConfFir(handle, wbConf->inWidth,
                                     wbConf->inHeight,
                                     wbConf->outFmt.width,
                                     wbConf->outFmt.height);

                    halDssVidConfVerticalTapsEnable(
                        handle,
                        (UInt32) DSS_DISPC_VID1_ATTRIBUTES_VERTICALTAPS_TAPS5);

                    halDssVidConfFir2(handle, wbConf->inWidth,
                                      wbConf->inHeight,
                                      (UInt32) (wbConf->outFmt.width / 2),
                                      (UInt32) (wbConf->outFmt.height / 2));
                }
            }
            else if (((wbConf->outFmt.dataFormat == FVID2_DF_YUV422I_YUYV) ||
                 (wbConf->outFmt.dataFormat == FVID2_DF_YUV422I_UYVY)))
            {
                vCoef = halDssVidGetScalarCoeff(wbConf->inHeight,
                                                wbConf->outFmt.height);
                hCoef = halDssVidGetScalarCoeff(wbConf->inWidth,
                                                wbConf->outFmt.width);

                retVal += halDssVidSetScalerCoeff(handle, vCoef, hCoef);

                if (retVal == BSP_SOK)
                {
                    halDssVidConfFir(handle, wbConf->inWidth,
                                     wbConf->inHeight,
                                     wbConf->outFmt.width,
                                     wbConf->outFmt.height);

                    halDssVidConfVerticalTapsEnable(handle, (UInt32) 1);

                    halDssVidConfFir2(handle, wbConf->inWidth,
                                      wbConf->inHeight,
                                      (UInt32) (wbConf->outFmt.width / 2),
                                      wbConf->outFmt.height);

                    halDssVidConfScalerEnable(handle, (UInt32) 0x1);
                }
            }
            else
            {
                /* Disable scalar */
                halDssVidConfScalerEnable(handle, (UInt32) 0x0);
            }
        }

        halDssVidConfCscFullRange(handle, wbConf->cscFullRngEnable);
    }

    return retVal;
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
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != advDmaCfg);

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId >= VPSHAL_DSS_DISPC_VID_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        halDssVidDmaSetBurstAttributes(handle,
                                       advDmaCfg->burstSize,
                                       advDmaCfg->burstType);
        halDssVidDmaBufThreConf(handle,
                                advDmaCfg->bufLowThreshold,
                                advDmaCfg->bufHighThreshold,
                                advDmaCfg->bufPreloadType);
        halDssVidDmaPixelRowIncConf(handle,
                                    advDmaCfg->rowInc,
                                    advDmaCfg->pixelInc);
        halDssVidDmaConfArbitration(handle, advDmaCfg->arbitration);
        halDssVidDmaConfSelfRefresh(handle, advDmaCfg->selfRefreshEnable);
        if ((Int32) TRUE == (VpsHal_dssIsWbPipe(dispcVidObj->halId)))
        {
            halDssWbIdleConfig(handle,
                               advDmaCfg->idleNumber,
                               advDmaCfg->idleSize);
        }
    }

    return (retVal);
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
Int32 VpsHal_dssVidPipeEnable(VpsHal_Handle handle, UInt32 enable)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcVidObj *dispcVidObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId >= VPSHAL_DSS_DISPC_VID_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_VID1_ATTRIBUTES_ENABLE,
            enable);
    }

    return (retVal);
}

/**
 *  VpsHal_dssWbSetGoBit
 *  \brief Sets the WBGo bit for WB pipeline
 *   Applicable only for WB pipeline
 *
 *  This function will program the buffer address for a pipeline,
 *  This function should be called after calling Init and open.
 *
 *  \param handle           Handle to the Video pipeline hal object
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */

Int32 VpsHal_dssWbSetGoBit(VpsHal_Handle handle)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcVidObj *dispcVidObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((Int32) FALSE == (VpsHal_dssIsWbPipe(dispcVidObj->halId)))
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        HW_WR_FIELD32(
            SOC_DISPC_BASE + DSS_DISPC_CONTROL2,
            DSS_DISPC_CONTROL2_GOWB,
            1U);
    }

    return (retVal);
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
    GT_assert(VpsHalTrace, NULL != handle);

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if (dispcVidObj->halId >= VPSHAL_DSS_DISPC_VID_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        if ((field == 0) || (field == 1U))
        {
            /* TODO - 4 should be passed as macro */
            HW_WR_REG32(
                dispcVidObj->regOffset.vidBaseAdd + (field * 0x04U),
                baseAddRGBY);
            if ((Int32) FALSE == (VpsHal_dssIsGfxPipe(dispcVidObj->halId)))
            {
                HW_WR_REG32(
                    dispcVidObj->regOffset.vidBaseAddUv + (field * 0x04U),
                    baseAddCbCr);
            }
        }
        else
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid field ID \r\n");
            retVal = BSP_EBADARGS;
        }
    }

    return (retVal);
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
 *          DOX_REQ_TAG(PDK-851) DOX_REQ_TAG(PDK-852) DOX_REQ_TAG(PDK-825)
 */
/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_020)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1782) DOX_REQ_TAG(PDK-1783) DOX_REQ_TAG(PDK-1784)
 *          DOX_REQ_TAG(PDK-1785) DOX_REQ_TAG(PDK-1786) DOX_REQ_TAG(PDK-1787)
 *          DOX_REQ_TAG(PDK-1788) DOX_REQ_TAG(PDK-1789) DOX_REQ_TAG(PDK-1790)
 *          DOX_REQ_TAG(PDK-1791)
 */
Int32 halDssConvFvid2DataFmt(UInt32 handleId, UInt32 fvid2Fmt)
{
    Int32 fmt;
    Int32 dssVidPipe, dssWbPipe;

    dssVidPipe = VpsHal_dssIsVidPipe(handleId);
    dssWbPipe  = VpsHal_dssIsWbPipe(handleId);

    if (((Int32) TRUE == dssVidPipe) || ((Int32) TRUE == dssWbPipe))
    {
        switch (fvid2Fmt)
        {
            case FVID2_DF_YUV422I_UYVY:
                fmt = 0xb;
                break;
            case FVID2_DF_YUV422I_YUYV:
                fmt = 0xa;
                break;
            case FVID2_DF_YUV420SP_UV:
                fmt = 0;
                break;
            case FVID2_DF_BGR24_888:   /*RGB24-888*/
                fmt = 0x9;
                break;
            case FVID2_DF_XBGR_4444:   /*RGBX12_4444*/
                fmt = 0x1;
                break;
            case FVID2_DF_BGRX_4444:   /*XRGB12_4444*/
                fmt = 0x4;
                break;
            case FVID2_DF_BGRA16_4444: /* ARGB16_4444*/
                fmt = 0x5;
                break;
            case FVID2_DF_ABGR16_4444: /*RGBA16_4444*/
                fmt = 0x2;
                break;
            case FVID2_DF_BGRX16_5551: /*xRGB16-1555*/
                fmt = 0xF;
                break;
            case FVID2_DF_BGRA16_5551: /*ARGB16-1555*/
                fmt = 0x7;
                break;
            case FVID2_DF_BGR16_565:   /* RGB16- 565*/
                fmt = 0x6;
                break;
            case FVID2_DF_BGRX24_8888: /*xRGB24-8888*/
                fmt = 0x8;
                break;
            case FVID2_DF_XBGR24_8888: /*RGBx24-8888*/
                fmt = 0xE;
                break;
            case FVID2_DF_BGRA32_8888: /*ARGB32-8888*/
                fmt = 0xc;
                break;
            case FVID2_DF_ABGR32_8888: /*RGBA32-8888*/
                fmt = 0xd;
                break;
            case FVID2_DF_ARGB32_8888: /*BGRA32-8888*/
                fmt = 0x3;
                break;
            default:
                fmt = BSP_EFAIL;
                break;
        }
    }
    else if ((Int32) TRUE == (VpsHal_dssIsGfxPipe(handleId)))
    {
        switch (fvid2Fmt)
        {
            case FVID2_DF_ARGB32_8888:  /*BGRA32-8888*/
                fmt = 0x3;
                break;
            case FVID2_DF_BGR24_888:    /*RGB24_888*/
                fmt = 0x9;
                break;
            case FVID2_DF_XBGR_4444:    /*RGBX12_4444*/
                fmt = 0xA;
                break;
            case FVID2_DF_BGRX_4444:    /*XRGB12_4444*/
                fmt = 0x4;
                break;
            case FVID2_DF_BGRA16_4444:  /*ARGB16_4444*/
                fmt = 0x5;
                break;
            case FVID2_DF_ABGR16_4444:  /*RGBA16_4444*/
                fmt = 0xb;
                break;
            case FVID2_DF_BGRX16_5551:  /*xRGB16-1555*/
                fmt = 0xF;
                break;
            case FVID2_DF_BGRA16_5551:  /*ARGB16-1555*/
                fmt = 0x7;
                break;
            case FVID2_DF_BGR16_565:    /*RGB16- 565*/
                fmt = 0x6;
                break;
            case FVID2_DF_BGRX24_8888:  /*xRGB24-8888*/
                fmt = 0x8;
                break;
            case FVID2_DF_XBGR24_8888:  /*RGBx24-8888*/
                fmt = 0xE;
                break;
            case FVID2_DF_BGRA32_8888:  /*ARGB32-8888*/
                fmt = 0xc;
                break;
            case FVID2_DF_ABGR32_8888:  /*RGBA32-8888*/
                fmt = 0xd;
                break;
            default:
                fmt = BSP_EFAIL;
                break;
        }
    }
    else
    {
        fmt = BSP_EFAIL;
    }
    return (fmt);
}

/**
 *  halDssVidDmaSetBurstAttributes
 *  Sets the Burst Attributs(size and tye) of DMA for the video pipeline
 */
static void halDssVidDmaSetBurstAttributes(VpsHal_Handle handle,
                                           UInt32        burstSize,
                                           UInt32        burstType)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
    if ((Int32) TRUE == (VpsHal_dssIsGfxPipe(dispcVidObj->halId)))
    {
        HW_SET_FIELD32(regVal, DSS_DISPC_GFX_ATTRIBUTES_BURSTSIZE, burstSize);
        HW_SET_FIELD32(regVal, DSS_DISPC_GFX_ATTRIBUTES_BURSTTYPE, burstType);
    }
    else if ((Int32) TRUE == (VpsHal_dssIsVidPipe(dispcVidObj->halId)))
    {
        HW_SET_FIELD32(regVal, DSS_DISPC_VID1_ATTRIBUTES_BURSTSIZE, burstSize);
        HW_SET_FIELD32(regVal, DSS_DISPC_VID1_ATTRIBUTES_BURSTTYPE, burstType);
    }
    else if ((Int32) TRUE == (VpsHal_dssIsWbPipe(dispcVidObj->halId)))
    {
        HW_SET_FIELD32(regVal, DSS_DISPC_WB_ATTRIBUTES_BURSTSIZE, burstSize);
        HW_SET_FIELD32(regVal, DSS_DISPC_WB_ATTRIBUTES_BURSTTYPE, burstType);
    }
    else
    {
        /* MISRA-C */
    }

    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);

    return;
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

    if ((Int32) TRUE == (VpsHal_dssIsWbPipe(dispcVidObj->halId)))
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);

        HW_SET_FIELD32(regVal, DSS_DISPC_WB_ATTRIBUTES_IDLENUMBER, idleNumber);
        HW_SET_FIELD32(regVal, DSS_DISPC_WB_ATTRIBUTES_IDLESIZE, idleSize);

        HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);
    }

    return;
}


/**
 *  halDssVidDmaBufThreConf
 *  Sets the Buffer Threshold(Low and High) of DMA for the video pipeline
 */
static void halDssVidDmaBufThreConf(VpsHal_Handle handle,
                                    UInt32        bufLowThreshold,
                                    UInt32        bufHighThreshold,
                                    UInt32        bufPreloadType)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal = HW_RD_REG32(dispcVidObj->regOffset.bufThresh);
    HW_SET_FIELD32(
        regVal,
        DSS_DISPC_VID1_BUF_THRESHOLD_BUFLOWTHRESHOLD,
        bufLowThreshold);
    HW_SET_FIELD32(
        regVal,
        DSS_DISPC_VID1_BUF_THRESHOLD_BUFHIGHTHRESHOLD,
        bufHighThreshold);
    HW_WR_REG32(dispcVidObj->regOffset.bufThresh, regVal);

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
    if ((Int32) TRUE == (VpsHal_dssIsGfxPipe(dispcVidObj->halId)))
    {
        HW_SET_FIELD32(regVal, DSS_DISPC_GFX_ATTRIBUTES_BUFPRELOAD,
                       bufPreloadType);
    }
    else if ((Int32) TRUE == (VpsHal_dssIsVidPipe(dispcVidObj->halId)))
    {
        HW_SET_FIELD32(regVal, DSS_DISPC_VID1_ATTRIBUTES_BUFPRELOAD,
                       bufPreloadType);
    }
    else
    {
        /* MISRA-C */
    }
    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);

    return;
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

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    HW_WR_FIELD32(
        dispcVidObj->regOffset.rowInc,
        DSS_DISPC_VID1_ROW_INC_ROWINC,
        rowInc);
    HW_WR_FIELD32(
        dispcVidObj->regOffset.pixelInc,
        DSS_DISPC_VID1_PIXEL_INC_PIXELINC,
        pixelInc);

    return;
}

/**
 *  halDssVidDmaConfArbitration
 *  Sets the Priority of the video pipeline wrt DMA
 */
static void halDssVidDmaConfArbitration(VpsHal_Handle handle,
                                        UInt32        arbitration)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((Int32) TRUE == (VpsHal_dssIsGfxPipe(dispcVidObj->halId)))
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_GFX_ATTRIBUTES_ARBITRATION,
            arbitration);
    }
    else
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_VID1_ATTRIBUTES_ARBITRATION,
            arbitration);
    }

    return;
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

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((Int32) TRUE == (VpsHal_dssIsVidPipe(dispcVidObj->halId)))
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_VID1_ATTRIBUTES_SELFREFRESH,
            selfRefreshEnable);
    }
    else if ((Int32) TRUE == (VpsHal_dssIsGfxPipe(dispcVidObj->halId)))
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_GFX_ATTRIBUTES_SELFREFRESH,
            selfRefreshEnable);
    }
    else
    {
        /*Error*/
    }

    return;
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

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    HW_WR_FIELD32(
        dispcVidObj->regOffset.vidAttrib,
        DSS_DISPC_VID1_ATTRIBUTES_FORMAT,
        dataFmt);

    return;
}

/**
 *  halDssVidConfYuvChromaReSampling
 *  Configures the Chromasampling for a pipeline
 */
static void halDssVidConfYuvChromaReSampling(VpsHal_Handle handle,
                                             UInt32        chromaSampling)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    HW_WR_FIELD32(
        dispcVidObj->regOffset.vidAttrib2,
        DSS_DISPC_VID1_ATTRIBUTES2_YUVCHROMARESAMPLING,
        chromaSampling);

    return;
}

/**
 *  halDssVidConfCscFullRange
 *  Configures the CSC Mode of Operation
 */
static void halDssVidConfCscFullRange(VpsHal_Handle handle,
                                      UInt32        cscFullRngEnable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((Int32) FALSE == (VpsHal_dssIsWbPipe(dispcVidObj->halId)))
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_VID1_ATTRIBUTES_FULLRANGE,
            cscFullRngEnable);
    }
    else
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_WB_ATTRIBUTES_FULLRANGE,
            cscFullRngEnable);
    }

    return;
}

/**
 *  halDssVidConfCscCoeff
 *  Configures the coefficients for color space conversion
 */
static void halDssVidConfCscCoeff(VpsHal_Handle          handle,
                                  const Vps_DssCscCoeff *coeff)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    HW_WR_FIELD32(
        dispcVidObj->regOffset.convCoef[0],
        DSS_DISPC_VID1_CONV_COEF0_RCR,
        coeff->rcr);
    HW_WR_FIELD32(
        dispcVidObj->regOffset.convCoef[0],
        DSS_DISPC_VID1_CONV_COEF0_RY,
        coeff->ry);
    HW_WR_FIELD32(
        dispcVidObj->regOffset.convCoef[1],
        DSS_DISPC_VID1_CONV_COEF1_GY,
        coeff->gy);
    HW_WR_FIELD32(
        dispcVidObj->regOffset.convCoef[1],
        DSS_DISPC_VID1_CONV_COEF1_RCB,
        coeff->rcb);
    HW_WR_FIELD32(
        dispcVidObj->regOffset.convCoef[2],
        DSS_DISPC_VID1_CONV_COEF2_GCB,
        coeff->gcb);
    HW_WR_FIELD32(
        dispcVidObj->regOffset.convCoef[2],
        DSS_DISPC_VID1_CONV_COEF2_GCR,
        coeff->gcr);
    HW_WR_FIELD32(
        dispcVidObj->regOffset.convCoef[3],
        DSS_DISPC_VID1_CONV_COEF3_BCR,
        coeff->bcr);
    HW_WR_FIELD32(
        dispcVidObj->regOffset.convCoef[3],
        DSS_DISPC_VID1_CONV_COEF3_BY,
        coeff->by);
    HW_WR_FIELD32(
        dispcVidObj->regOffset.convCoef[4],
        DSS_DISPC_VID1_CONV_COEF4_BCB,
        coeff->bcb);

    return;
}

/**
 *  halDssVidConfCscCoeff
 *  Configures the coefficients for color space conversion
 */
static void halDssVidConfCscEnable(VpsHal_Handle handle,
                                   UInt32        cscEnable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;
    if (TRUE == cscEnable)
    {
        if (((Int32) TRUE == (VpsHal_dssIsVidPipe(dispcVidObj->halId))) ||
            ((Int32) TRUE == (VpsHal_dssIsWbPipe(dispcVidObj->halId))))
        {
            halDssVidConfCscCoeff(handle, &dispcVidObj->cscCoeff);
        }
        else
        {
            /* Not applicable for GFX */
        }
    }

    HW_WR_FIELD32(
        dispcVidObj->regOffset.vidAttrib,
        DSS_DISPC_VID1_ATTRIBUTES_COLORCONVENABLE,
        cscEnable);

    return;
}

/**
 *  halDssVidSetRotation
 *  Sets the rotation bit  for the video pipeline
 */
static void halDssVidSetRotation(VpsHal_Handle handle,
                                 UInt32        rotation)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    HW_WR_FIELD32(
        dispcVidObj->regOffset.vidAttrib2,
        DSS_DISPC_VID1_ATTRIBUTES_ROTATION,
        rotation);

    return;
}

/**
 *  halDssVidSetDoubleStride
 *  Sets the double stride for the video pipeline
 */
static void halDssVidSetDoubleStride(VpsHal_Handle handle,
                                     UInt32        doubleStride)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    HW_WR_FIELD32(
        dispcVidObj->regOffset.vidAttrib,
        DSS_DISPC_VID1_ATTRIBUTES_DOUBLESTRIDE,
        doubleStride);

    return;
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
static Int32 halDssVidSetScalerCoeff(VpsHal_Handle            handle,
                                     const VpsHal_DssScCoeff *vCoef,
                                     const VpsHal_DssScCoeff *hCoef)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 i = 0;
    UInt32 firCoefH, firCoefV, firCoefHV;
    UInt32 firCoefH2, firCoefV2, firCoefHV2;
    UInt32 regVal;
    Int32  retVal = BSP_SOK;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((NULL == vCoef) || (NULL == hCoef))
    {
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        for (i = 0; i < 8U; i++)
        {
            firCoefH   = dispcVidObj->regOffset.firCoefH + (8U * i);
            firCoefHV  = dispcVidObj->regOffset.firCoefHV + (8U * i);
            firCoefV   = dispcVidObj->regOffset.firCoefV + (4U * i);
            firCoefH2  = dispcVidObj->regOffset.firCoefH2 + (8U * i);
            firCoefHV2 = dispcVidObj->regOffset.firCoefHV2 + (8U * i);
            firCoefV2  = dispcVidObj->regOffset.firCoefV2 + (4U * i);

            GT_1trace(
                VpsHalTrace, GT_DEBUG,
                "Address of current firH register %x \r\n",
                firCoefH);
            GT_1trace(
                VpsHalTrace, GT_DEBUG,
                "Address of current firHV register %x \r\n",
                firCoefHV);
            GT_1trace(
                VpsHalTrace, GT_DEBUG,
                "Address of current firV register %x \r\n",
                firCoefV);

            regVal = HW_RD_REG32(firCoefH);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_H_FIRHC0,
                           hCoef[i].hc0Vc00);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_H_FIRHC1,
                           hCoef[i].hc1Vc0);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_H_FIRHC2,
                           hCoef[i].hc2Vc1);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_H_FIRHC3,
                           hCoef[i].hc3Vc2);
            HW_WR_REG32(firCoefH, regVal);

            regVal = HW_RD_REG32(firCoefHV);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID3_FIR_COEF_HV_FIRHC4,
                           hCoef[i].hc4Vc22);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_HV_FIRVC0,
                           vCoef[i].hc1Vc0);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_HV_FIRVC1,
                           vCoef[i].hc2Vc1);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_HV_FIRVC2,
                           vCoef[i].hc3Vc2);
            HW_WR_REG32(firCoefHV, regVal);

            regVal = HW_RD_REG32(firCoefV);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_V_FIRVC00,
                           vCoef[i].hc0Vc00);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_V_FIRVC22,
                           vCoef[i].hc4Vc22);
            HW_WR_REG32(firCoefV, regVal);

            regVal = HW_RD_REG32(firCoefH2);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_H2_FIRHC0,
                           hCoef[i].hc0Vc00);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_H2_FIRHC1,
                           hCoef[i].hc1Vc0);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_H2_FIRHC2,
                           hCoef[i].hc2Vc1);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_H2_FIRHC3,
                           hCoef[i].hc3Vc2);
            HW_WR_REG32(firCoefH2, regVal);

            regVal = HW_RD_REG32(firCoefHV2);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID3_FIR_COEF_HV2_FIRHC4,
                           hCoef[i].hc4Vc22);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC0,
                           vCoef[i].hc1Vc0);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC1,
                           vCoef[i].hc2Vc1);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC2,
                           vCoef[i].hc3Vc2);
            HW_WR_REG32(firCoefHV2, regVal);

            regVal = HW_RD_REG32(firCoefV2);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_V2_FIRVC00,
                           vCoef[i].hc0Vc00);
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_COEF_V2_FIRVC22,
                           vCoef[i].hc4Vc22);
            HW_WR_REG32(firCoefV2, regVal);
        }
    }

    return retVal;
}

const VpsHal_DssScCoeff *halDssVidGetScalarCoeff(UInt32 inSize, UInt32 outSize)
{
    const VpsHal_DssScCoeff *scCoef = NULL;
    UInt32 inc, i;

    typedef struct
    {
        UInt32                   mMin;
        UInt32                   mMax;
        const VpsHal_DssScCoeff *coef;
    } VpsHal_DssScCoefsArr;

    VpsHal_DssScCoefsArr     coefArr[] =
    {
        {27, 32, coefM32},
        {23, 26, coefM26},
        {20, 22, coefM22},
        {17, 19, coefM19},
        {15, 16, coefM16},
        {14, 14, coefM14},
        {13, 13, coefM13},
        {12, 12, coefM12},
        {11, 11, coefM11},
        {10, 10, coefM10},
        {9,  9,  coefM9 },
        {4,  8,  coefM8 },
        /*
         * When upscaling more than two times, blockiness and outlines
         * around the image are observed when M8 tables are used. M11,
         * M16 and M19 tables are used to prevent this.
         */
        {3,  3,  coefM11},
        {2,  2,  coefM16},
        {0,  1,  coefM19},
    };

    inc = (8U * inSize) / outSize;

    for (i = 0; i < (sizeof (coefArr) / sizeof (coefArr[0])); i++)
    {
        if ((inc >= coefArr[i].mMin) && (inc <= coefArr[i].mMax))
        {
            scCoef = coefArr[i].coef;
            break;
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

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((Int32) FALSE == (VpsHal_dssIsGfxPipe(dispcVidObj->halId)))
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_VID1_ATTRIBUTES_VERTICALTAPS,
            verticalTaps);
    }

    return;
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
    UInt32 firHinc, firVinc;
    UInt32 regVal;

    firHinc = (1024U * (inSizeX)) / (outSizeX);
    firVinc = (1024U * (inSizeY)) / (outSizeY);

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal = HW_RD_REG32(dispcVidObj->regOffset.fir);
    HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_FIRHINC, firHinc);
    HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR_FIRVINC, firVinc);
    HW_WR_REG32(dispcVidObj->regOffset.fir, regVal);

    return;
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
    UInt32 firHinc, firVinc;
    UInt32 regVal;

    firHinc     = ((UInt32) 1024U * (inSizeX)) / (outSizeX);
    firVinc     = ((UInt32) 1024U * (inSizeY)) / (outSizeY);
    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    regVal = HW_RD_REG32(dispcVidObj->regOffset.fir2);
    HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR2_FIRHINC, firHinc);
    HW_SET_FIELD32(regVal, DSS_DISPC_VID1_FIR2_FIRVINC, firVinc);
    HW_WR_REG32(dispcVidObj->regOffset.fir2, regVal);

    return;
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

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    HW_WR_FIELD32(
        dispcVidObj->regOffset.vidAttrib,
        DSS_DISPC_VID1_ATTRIBUTES_RESIZEENABLE,
        scalerEnable);

    return;
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

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib2);
    HW_SET_FIELD32(regVal, DSS_DISPC_VID1_ATTRIBUTES2_VC1_RANGE_Y, rangeY);
    HW_SET_FIELD32(regVal, DSS_DISPC_VID1_ATTRIBUTES2_VC1_RANGE_CBCR, rangeUV);
    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib2, regVal);

    return;
}

/**
 *  halDssVidVc1Enable
 *  Enable VC1 Range Mapping
 */
static void halDssVidVc1Enable(VpsHal_Handle handle,
                               UInt32        vc1Enable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    HW_WR_FIELD32(
        dispcVidObj->regOffset.vidAttrib2,
        DSS_DISPC_VID1_ATTRIBUTES2_VC1ENABLE,
        vc1Enable);

    return;
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

    if ((Int32) TRUE == (VpsHal_dssIsWbPipe(dispcVidObj->halId)))
    {
        switch (inNode)
        {
            case VPS_DSS_DISPC_WB_IN_NODE_VID1:
                nodeSel = DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_VID1;
                break;

            case VPS_DSS_DISPC_WB_IN_NODE_VID2:
                nodeSel = DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_VID2;
                break;

            case VPS_DSS_DISPC_WB_IN_NODE_VID3:
                nodeSel = DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_VID3;
                break;

            case VPS_DSS_DISPC_WB_IN_NODE_GFX:
                nodeSel = DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_GFX;
                break;

            case VPS_DSS_DISPC_WB_IN_NODE_LCD1:
                nodeSel = DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_LCD1;
                break;

            case VPS_DSS_DISPC_WB_IN_NODE_LCD2:
                nodeSel = DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_LCD2;
                break;

            case VPS_DSS_DISPC_WB_IN_NODE_LCD3:
                nodeSel = DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_LCD3;
                break;

            case VPS_DSS_DISPC_WB_IN_NODE_TV:
                nodeSel = DSS_DISPC_WB_ATTRIBUTES_CHANNELIN_TV;
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
            HW_SET_FIELD32(regVal, DSS_DISPC_WB_ATTRIBUTES_CHANNELIN,
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
 *  halDssWbSetTruncation
 *  Sets the truncation mode for writeback pipeline.
 */
static void halDssWbSetTruncation(VpsHal_Handle handle, UInt32 dataFmt)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    UInt32 regVal, enable;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    switch (dataFmt)
    {
        case FVID2_DF_BGRA16_4444:
        case FVID2_DF_ABGR16_4444:
        case FVID2_DF_BGRA16_5551:
        case FVID2_DF_BGR16_565:
            enable = 0x1U;
            break;
        default:
            enable = 0x0U;
            break;
    }

    regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
    HW_SET_FIELD32(regVal, DSS_DISPC_WB_ATTRIBUTES_TRUNCATIONENABLE, enable);
    HW_WR_REG32(dispcVidObj->regOffset.vidAttrib, regVal);

    return;
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

    if ((Int32) TRUE == (VpsHal_dssIsWbPipe(dispcVidObj->halId)))
    {
        if ((wbMode == DSS_DISPC_WB_ATTRIBUTES_WRITEBACKMODE_CAPTURE) ||
            (wbMode == DSS_DISPC_WB_ATTRIBUTES_WRITEBACKMODE_MEM2MEM))
        {
            regVal = HW_RD_REG32(dispcVidObj->regOffset.vidAttrib);
            HW_SET_FIELD32(regVal, DSS_DISPC_WB_ATTRIBUTES_WRITEBACKMODE,
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

    if ((Int32) TRUE == (VpsHal_dssIsWbPipe(dispcVidObj->halId)))
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.pictSize);
        HW_SET_FIELD32(regVal, DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEX,
                       (outWidth - 1U));
        HW_SET_FIELD32(regVal, DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEY,
                       (outHeight - 1U));
        HW_WR_REG32(dispcVidObj->regOffset.pictSize, regVal);
    }
    else
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidSize);
        if ((Int32) TRUE == (VpsHal_dssIsGfxPipe(dispcVidObj->halId)))
        {
            HW_SET_FIELD32(regVal, DSS_DISPC_GFX_SIZE_SIZEX, (outWidth - 1U));
            HW_SET_FIELD32(regVal, DSS_DISPC_GFX_SIZE_SIZEY, (outHeight - 1U));
        }
        else
        {
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_SIZE_SIZEX, (outWidth - 1U));
            HW_SET_FIELD32(regVal, DSS_DISPC_VID1_SIZE_SIZEY, (outHeight - 1U));
        }
        HW_WR_REG32(dispcVidObj->regOffset.vidSize, regVal);
    }

    return;
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

    if ((Int32) FALSE == (VpsHal_dssIsWbPipe(dispcVidObj->halId)))
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.pictSize);
        HW_SET_FIELD32(regVal, DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEX,
                       (inSizeX - 1U));
        HW_SET_FIELD32(regVal, DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEY,
                       (inSizeY - 1U));
        HW_WR_REG32(dispcVidObj->regOffset.pictSize, regVal);
    }
    else
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidSize);
        HW_SET_FIELD32(regVal, DSS_DISPC_WB_SIZE_SIZEX, (inSizeX - 1U));
        HW_SET_FIELD32(regVal, DSS_DISPC_WB_SIZE_SIZEY, (inSizeY - 1U));
        HW_WR_REG32(dispcVidObj->regOffset.vidSize, regVal);
    }

    return;
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

    if ((Int32) FALSE == (VpsHal_dssIsWbPipe(dispcVidObj->halId)))
    {
        regVal = HW_RD_REG32(dispcVidObj->regOffset.vidPos);
        HW_SET_FIELD32(regVal, DSS_DISPC_VID1_POSITION_POSX, posX);
        HW_SET_FIELD32(regVal, DSS_DISPC_VID1_POSITION_POSY, posY);
        HW_WR_REG32(dispcVidObj->regOffset.vidPos, regVal);
    }
    else
    {
        GT_0trace(VpsHalTrace, GT_ERR,
                  "Not supported for this \
            instance of HAL \r\n");
    }

    return;
}

/**
 *  halDssVidConfRepliEnable
 *  Enables or disables the replication logic
 */
static void halDssVidConfRepliEnable(VpsHal_Handle handle,
                                     UInt32        repliEnable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((Int32) TRUE == (VpsHal_dssIsGfxPipe(dispcVidObj->halId)))
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_GFX_ATTRIBUTES_REPLICATIONENABLE,
            repliEnable);
    }
    else
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_VID1_ATTRIBUTES_REPLICATIONENABLE,
            repliEnable);
    }

    return;
}

/**
 *  halDssVidConfAntiFlickerEnable
 *  Enables or disables the antiflicker logic
 */
static void halDssVidConfAntiFlickerEnable(VpsHal_Handle handle,
                                           UInt32        antiFlickerEnable)
{
    VpsHal_DssDispcVidObj *dispcVidObj;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((Int32) TRUE == (VpsHal_dssIsGfxPipe(dispcVidObj->halId)))
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib,
            DSS_DISPC_GFX_ATTRIBUTES_ANTIFLICKER,
            antiFlickerEnable);
    }

    return;
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
    Int32 retVal = BSP_SOK;

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
        switch (pipeHalId)
        {
            case VPSHAL_DSS_DISPC_VID1:
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_VID1BUFFERUNDERFLOW_EN,
                    enable);
                break;
            case VPSHAL_DSS_DISPC_VID2:
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_VID2BUFFERUNDERFLOW_EN,
                    enable);
                break;
            case VPSHAL_DSS_DISPC_VID3:
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_VID3BUFFERUNDERFLOW_EN,
                    enable);
                break;
            case VPSHAL_DSS_DISPC_GFX:
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_GFXBUFFERUNDERFLOW_EN,
                    enable);
                break;
            case VPSHAL_DSS_DISPC_WB1:
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_WBBUFFEROVERFLOW_EN,
                    enable);
                break;
            default:
                retVal = BSP_EBADARGS;
                break;
        }
    }
    return retVal;
}

Int32 VpsHal_dssConfWbDelayCnt(VpsHal_Handle          handle,
                               UInt32                 wbDelayCnt)
{
    VpsHal_DssDispcVidObj *dispcVidObj;
    Int32  retVal = BSP_SOK;

    dispcVidObj = (VpsHal_DssDispcVidObj *) handle;

    if ((Int32) TRUE == (VpsHal_dssIsWbPipe(dispcVidObj->halId)))
    {
        HW_WR_FIELD32(
            dispcVidObj->regOffset.vidAttrib2,
            DSS_DISPC_WB_ATTRIBUTES2_WBDELAYCOUNT,
            wbDelayCnt);
    }
    else
    {
        GT_0trace(
            VpsHalTrace, GT_ERR,
            "Not supported for this instance of HAL \r\n");
        retVal = BSP_EBADARGS;
    }
    return retVal;
}
