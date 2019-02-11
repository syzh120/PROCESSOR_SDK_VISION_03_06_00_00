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
 *  \file bsp_board.c
 *
 *  \brief File containing the BSP board functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <bsp_boardPriv.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    Bsp_BoardId          boardId;
    /**< Board ID. For valid values see #Bsp_BoardId. */
    Bsp_BoardRev         baseBoardRev;
    /**< Base Board revision. */
    Bsp_BoardRev         dcBoardRev;
    /**< Daughter card board revision. */
    Bsp_BoardCustomData *customData;
    /**< Pointer to custom board data structure. */
    BspOsal_SemHandle    lock;
    /**< Generic lock for task re-entrant protection. */
} Bsp_BoardCommonObj;

/**
 *  struct Bsp_BoardIdString
 *  \brief Structure to store board ID and string pair.
 */
typedef struct
{
    Bsp_BoardId boardId;
    /**< Board ID. */
    const Char *boardIdStr;
    /**< Pointer to board ID string. */
} Bsp_BoardIdString;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Bsp_boardEnableThs7353(Fvid2_Standard standard,
                                    UInt32         i2cInstId,
                                    UInt32         i2cDevAddr);
static Int32 Bsp_boardEnableThs73681(Fvid2_Standard standard,
                                     UInt32         i2cInst,
                                     UInt32         ioExpAddr);
static Int32 Bsp_boardLock(void);
static Int32 Bsp_boardUnlock(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bsp_BoardCommonObj gBoardCommonObj;

static Bsp_BoardIdString  gBoardIdStrTable[] =
{
    {BSP_BOARD_UNKNOWN,                    "UNKNOWN"                       },
    {BSP_BOARD_VS,                         "VS"                            },
    {BSP_BOARD_MONSTERCAM,                 "MONSTER_CAM"                   },
    {BSP_BOARD_VC,                         "VC"                            },
    {BSP_BOARD_VISION,                     "Vision"                        },
    {BSP_BOARD_VISION_TI81XX,              "Vision(TI81XX)"                },
    {BSP_BOARD_CATALOG,                    "Catalog"                       },
    {BSP_BOARD_CUSTOM,                     "Custom"                        },
    {BSP_BOARD_JAMR3,                      "JAMR3"                         },
    {BSP_BOARD_MULTIDES,                   "MULTIDES"                      },
    {BSP_BOARD_BASE_TDA2XX,                "TDA2XX BASE"                   },
    {BSP_BOARD_BASE_TDA3XX,                "TDA3XX BASE"                   },
    {BSP_BOARD_BASE_TI81XX,                "TI81XX BASE"                   },
    {BSP_BOARD_BASE_TDA2EX,                "TDA2EX BASE"                   },
    {BSP_BOARD_GP_AM572X,                  "AM572X GP EVM"                 },
    {BSP_BOARD_IDK_AM57XX,                 "AM57XX IDK EVM"                },
    {BSP_BOARD_TDA3XX_RVP_ALPHA,           "TDA3XX RVP ALPHA"              },
    {BSP_BOARD_TDA3XX_RVP_BETA,            "TDA3XX RVP BETA"               },
    {BSP_BOARD_TDA3XX_RVP_A,               "TDA3XX RVP A"                  },
    {BSP_BOARD_TDA3XX_AR12XX_RADAR,        "TDA3XX AR12 RADAR"             },
    {BSP_BOARD_TDA3XX_AR12XX_ALPS,         "TDA3XX AR12 ALPS RADAR"        },
    {BSP_BOARD_BASE_TDA2PX,                "TDA2PX BASE"                   },
    {BSP_BOARD_TDA2ECO_RVP_1,              "TDA2ECO RVP REV 1"             },
    {BSP_BOARD_TDA2ECO_RVP_AM571X_1,       "TDA2ECO RVP (AM571X) REV 1"    },
    {BSP_BOARD_TDA2ECO_RVP_AM572X_1,       "TDA2ECO RVP (AM572X) REV 1"    },
    {BSP_BOARD_TDA2ECO_RVP_TDA2X_1,        "TDA2ECO RVP (TDA2X) REV 1"     },
    {BSP_BOARD_TDA2XDE_RVP_X,              "TDA2XDE RVP REV X"             },
    {BSP_BOARD_TDA3XX_D3_SK,               "TDA3XX D3 Starter Kit"         },
    {BSP_BOARD_TDA2XX_CASCADE_RADAR,       "TDA2XX CASCADE RADAR"          }
};

static Char *gBoardRevStr[] =
{
    "UNKNOWN",
    "REV A",
    "REV B",
    "REV C",
    "REV D",
    "REV E",
    "REV 1.3A",
    "REV ALPHA",
    "REV BETA",
    "REV A 4G",
    "REV 1 RADAR DC",
    "REV - SK",
    "REV - SK DASH",
    "REV 1 4CH",
    "REV 1 8CH",
    "REV 2 8CH",
    "REV DASH 4G",
    "REV DASH 2G STP",
    "REV DASH 4G STP",
    "REV A 2G"
};

/** \brief Number of entries in board ID string table. */
#define BSP_BOARD_NUM_ID_STR_ENTRIES        (sizeof (gBoardIdStrTable) / \
                                             sizeof (Bsp_BoardIdString))

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_boardInit(const Bsp_BoardInitParams *initPrms)
{
    Int32 retVal = BSP_SOK;
    Int32 initValue;
    Bsp_BoardInitParams localInitPrms;

    BspUtils_memset(&gBoardCommonObj, 0, sizeof (gBoardCommonObj));

    /* If NULL is passed pinMux will be initialized by default */
    if (NULL == initPrms)
    {
        initPrms = &localInitPrms;
        BspBoardInitParams_init(&localInitPrms);
    }

    gBoardCommonObj.boardId      = initPrms->boardId;
    gBoardCommonObj.baseBoardRev = initPrms->baseBoardRev;
    gBoardCommonObj.dcBoardRev   = initPrms->dcBoardRev;
    gBoardCommonObj.customData   = initPrms->customData;
    if (NULL != gBoardCommonObj.customData)
    {
        /* Below parameters can't be NULL */
        GT_assert(BspBoardTrace,
                  (gBoardCommonObj.customData->boardIdString != NULL));
        GT_assert(BspBoardTrace,
                  (gBoardCommonObj.customData->boardRevString != NULL));
        GT_assert(BspBoardTrace,
                  (gBoardCommonObj.customData->i2cData != NULL));
        GT_assert(BspBoardTrace,
                  (gBoardCommonObj.customData->boardData != NULL));
    }

    /* Create global board lock */
    initValue = (Int32) 1;
    gBoardCommonObj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if (NULL == gBoardCommonObj.lock)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "Global semaphore create failed\r\n");
        retVal = BSP_EALLOC;
    }

    /* Macro is used instead of platform API. Any Platform API
     * cannot be called in board init as platform init happens after board
     * init */
    if (BSP_SOK == retVal)
    {
        if (NULL != gBoardCommonObj.customData)
        {
            if (NULL != gBoardCommonObj.customData->initFxn)
            {
                retVal = gBoardCommonObj.customData->initFxn();
            }
        }
        else
        {
            /* Use default built-in board functions */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
  #if defined (SOC_TDA2EX)
            retVal = Bsp_boardTda2exInit();
  #else
            retVal = Bsp_boardTda2xxInit();
  #endif
#endif

#if defined (SOC_TDA3XX)
            retVal = Bsp_boardTda3xxInit();
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
            retVal = Bsp_boardAm572xInit();
#endif
        }
    }

    return (retVal);
}

Int32 Bsp_boardLateInit(void)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA3XX)
    retVal = Bsp_boardTda3xxLateInit();
#endif

#if defined (SOC_TDA2XX)
    retVal = Bsp_boardTda2xxLateInit();
#endif

    return (retVal);
}

Int32 Bsp_boardDeInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBoardCommonObj.lock);

    return (retVal);
}

Bsp_BoardId Bsp_boardGetId(void)
{
    if (BSP_BOARD_MAX == gBoardCommonObj.boardId)
    {

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
        gBoardCommonObj.boardId = Bsp_boardGetIdTda2xx();
#endif

#if defined (SOC_TDA2EX)
        gBoardCommonObj.boardId = Bsp_boardGetIdTda2ex();
#endif

#if defined (SOC_TDA3XX)
        gBoardCommonObj.boardId = Bsp_boardGetIdTda3xx();
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
        gBoardCommonObj.boardId = Bsp_boardGetIdAm572x();
#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
        gBoardCommonObj.boardId = Bsp_boardGetIdTI814x();
#endif

#if defined (OMAP5430_BUILD)
        gBoardCommonObj.boardId = Bsp_boardGetIdOmap5430();
#endif
    }

    return (gBoardCommonObj.boardId);
}

Bsp_BoardRev Bsp_boardGetBaseBoardRev(void)
{
    if (BSP_BOARD_REV_MAX == gBoardCommonObj.baseBoardRev)
    {

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
        gBoardCommonObj.baseBoardRev = Bsp_boardGetBaseBoardRevTda2xx();
#endif

#if defined (SOC_TDA2EX)
        gBoardCommonObj.baseBoardRev = Bsp_boardGetBaseBoardRevTda2ex();
#endif

#if defined (SOC_TDA3XX)
        gBoardCommonObj.baseBoardRev = Bsp_boardGetBaseBoardRevTda3xx();
#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
        gBoardCommonObj.baseBoardRev = Bsp_boardGetBaseBoardRevTI814x();
#endif

#if defined (OMAP5430_BUILD)
        gBoardCommonObj.baseBoardRev = Bsp_boardGetBaseBoardRevOmap5430();
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
        gBoardCommonObj.baseBoardRev = Bsp_boardGetBaseBoardRevAm572x();
#endif

    }

    return (gBoardCommonObj.baseBoardRev);
}

Bsp_BoardRev Bsp_boardGetDcRev(void)
{
    if (BSP_BOARD_REV_MAX == gBoardCommonObj.dcBoardRev)
    {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
#if defined (SOC_TDA2EX)
        gBoardCommonObj.dcBoardRev = Bsp_boardGetDcRevTda2ex();
#else
        gBoardCommonObj.dcBoardRev = Bsp_boardGetDcRevTda2xx();
#endif
#endif

#if defined (SOC_TDA3XX)
        gBoardCommonObj.dcBoardRev = Bsp_boardGetDcRevTda3xx();
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
        gBoardCommonObj.dcBoardRev = Bsp_boardGetDcRevAm572x();
#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
        gBoardCommonObj.dcBoardRev = Bsp_boardGetDcRevTI814x();
#endif

#if defined (OMAP5430_BUILD)
        gBoardCommonObj.dcBoardRev = Bsp_boardGetDcRevOmap5430();
#endif
    }

    return (gBoardCommonObj.dcBoardRev);
}

void Bsp_boardClearId(void)
{
    gBoardCommonObj.boardId = BSP_BOARD_MAX;
}

void Bsp_boardClearBaseBoardRev(void)
{
    gBoardCommonObj.baseBoardRev = BSP_BOARD_REV_MAX;
}

void Bsp_boardClearDcRev(void)
{
    gBoardCommonObj.dcBoardRev = BSP_BOARD_REV_MAX;
}

const Bsp_BoardI2cData *Bsp_boardGetI2cData(void)
{
    const Bsp_BoardI2cData *i2cData = NULL;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
#if defined (SOC_TDA2EX)
    i2cData = Bsp_boardGetI2cDataTda2ex();
#else
    i2cData = Bsp_boardGetI2cDataTda2xx();
#endif
#endif

#if defined (SOC_TDA3XX)
    i2cData = Bsp_boardGetI2cDataTda3xx();
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    i2cData = Bsp_boardGetI2cDataAm572x();
#endif

#if defined (OMAP5430_BUILD)
    i2cData = Bsp_boardGetI2cDataOmap5430();
#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    i2cData = Bsp_boardGetI2cDataTI814x();
#endif

    return (i2cData);
}

const Bsp_BoardData *Bsp_boardGetData(void)
{
    const Bsp_BoardData *boardData = NULL;

    if (NULL != gBoardCommonObj.customData)
    {
        boardData = gBoardCommonObj.customData->boardData;
    }
    else
    {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
#if defined (SOC_TDA2EX)
        boardData = Bsp_boardGetDataTda2ex();
#else
        boardData = Bsp_boardGetDataTda2xx();
#endif
#endif

#if defined (SOC_TDA3XX)
        boardData = Bsp_boardGetDataTda3xx();
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
        boardData = Bsp_boardGetDataAm572x();
#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
        boardData = Bsp_boardGetDataTI814x();
#endif

#if defined (OMAP5430_BUILD)
        boardData = Bsp_boardGetDataOmap5430();
#endif
    }

    return (boardData);
}

UInt32 Bsp_boardGetVideoDeviceInstId(UInt32 devDrvId,
                                     UInt32 drvId,
                                     UInt32 drvInstId)
{
    UInt32 instId = BSP_BOARD_INVALID_INST_ID;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->drvId == drvId) &&
            (devData->drvInstId == drvInstId))
        {
            instId = devData->instId;
            break;
        }
    }

    if (BSP_BOARD_INVALID_INST_ID == instId)
    {
        GT_2trace(BspBoardTrace, GT_ERR, "Invalid device driver ID - devDrvId: %d drvInstId: %d!!\r\n",
                  devDrvId, drvInstId);
    }

    return (instId);
}

UInt32 Bsp_boardGetVideoDeviceI2cInstId(UInt32 devDrvId,
                                        UInt32 drvId,
                                        UInt32 drvInstId)
{
    UInt32 i2cInstId = BSP_DEVICE_I2C_INST_ID_MAX;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->drvId == drvId) &&
            (devData->drvInstId == drvInstId))
        {
            i2cInstId = devData->i2cInstId;
            break;
        }
    }

    if (BSP_DEVICE_I2C_INST_ID_MAX == i2cInstId)
    {
        GT_2trace(BspBoardTrace, GT_ERR, "Invalid device driver ID - devDrvId: %d drvInstId: %d!!\r\n",
                  devDrvId, drvInstId);
    }

    return (i2cInstId);
}

UInt32 Bsp_boardGetVideoDeviceI2cAddr(UInt32 devDrvId,
                                      UInt32 drvId,
                                      UInt32 drvInstId)
{
    UInt32 i2cAddr = 0U;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->drvId == drvId) &&
            (devData->drvInstId == drvInstId))
        {
            i2cAddr = devData->i2cAddr;
            break;
        }
    }

    if (0U == i2cAddr)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "Invalid device driver ID!!\r\n");
    }

    return (i2cAddr);
}

Int32 Bsp_boardPowerOnDevice(UInt32 devDrvId, UInt32 instId, UInt32 powerOn)
{
    Int32  retVal = BSP_SOK;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    Bsp_boardLock();

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->instId == instId) &&
            (devData->powerOnDev != NULL))
        {
            retVal = devData->powerOnDev(devDrvId, instId, powerOn);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "Device power-on failed!!\r\n");
            }
            break;
        }
    }

    Bsp_boardUnlock();

    return (retVal);
}

Int32 Bsp_boardSelectDevice(UInt32 devDrvId, UInt32 instId)
{
    Int32  retVal = BSP_SOK;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    Bsp_boardLock();

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->instId == instId) &&
            (devData->selectDev != NULL))
        {
            retVal = devData->selectDev(devDrvId, instId);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "Device select failed!!\r\n");
            }
            break;
        }
    }

    Bsp_boardUnlock();

    return (retVal);
}

Int32 Bsp_boardResetDevice(UInt32 devDrvId, UInt32 instId)
{
    Int32  retVal = BSP_SOK;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    Bsp_boardLock();

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->instId == instId) &&
            (devData->resetDev != NULL))
        {
            retVal = devData->resetDev(devDrvId, instId);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "Device reset failed!!\r\n");
            }
            break;
        }
    }

    Bsp_boardUnlock();

    return (retVal);
}

Int32 Bsp_boardSelectMode(UInt32        devDrvId,
                          UInt32        instId,
                          Bsp_BoardMode boardMode)
{
    Int32 retVal = BSP_SOK;

    Bsp_boardLock();

    if (BSP_BOARD_MODE_NONE != boardMode)
    {
        if (NULL != gBoardCommonObj.customData)
        {
            if (NULL != gBoardCommonObj.customData->selectModeFxn)
            {
                retVal = gBoardCommonObj.customData->selectModeFxn(devDrvId,
                                                                   instId,
                                                                   boardMode);
            }
        }
        else
        {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
#if defined (TDA3XX_INTERPOSER_BUILD)
            retVal = Bsp_boardSelectModeTda3xx(devDrvId, instId, boardMode);
#endif
#endif

#if defined (SOC_TDA3XX)
            retVal = Bsp_boardSelectModeTda3xx(devDrvId, instId, boardMode);
#endif
        }
    }

    Bsp_boardUnlock();

    return (retVal);
}

Int32 Bsp_boardReadTCA6424BoardMux(UInt32 numRegs, UInt8 regVal[])
{
    Int32 retVal = BSP_SOK;
    Bsp_boardLock();
#if defined (SOC_TDA3XX)
    retVal = Bsp_boardTda3xxReadTCA6424BoardMux(numRegs, regVal);
#endif
    Bsp_boardUnlock();
    return (retVal);
}

Int32 Bsp_boardWriteTCA6424BoardMux(UInt32 numRegs, UInt8 regVal[])
{
    Int32 retVal = BSP_SOK;

    Bsp_boardLock();
#if defined (SOC_TDA3XX)
    retVal = Bsp_boardTda3xxWriteTCA6424BoardMux(numRegs, regVal);
#endif
    Bsp_boardUnlock();

    return (retVal);
}

Int32 Bsp_boardEnableTvp7002Filter(UInt32 instId, Fvid2_Standard standard)
{
    Int32        retVal = BSP_SOK;
    Bsp_BoardId  boardId;
    Bsp_BoardRev dcBoardRev;
    const Bsp_BoardI2cData *i2cData;

    boardId    = Bsp_boardGetId();
    dcBoardRev = Bsp_boardGetDcRev();
    i2cData    = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    if (BSP_BOARD_VC == boardId)
    {
        if (BSP_BOARD_REV_A == dcBoardRev)
        {
            retVal = Bsp_boardEnableThs7353(
                standard,
                i2cData->probeInstId,
                (UInt32) BOARD_THS7353_I2C_ADDR);
        }
        else if (BSP_BOARD_REV_B == dcBoardRev)
        {
            retVal = Bsp_boardEnableThs73681(
                standard,
                i2cData->probeInstId,
                (UInt32) BOARD_IO_EXP_I2C_ADDR_1);
        }
        else
        {
            GT_0trace(BspBoardTrace, GT_ERR, "Invalid DC revision!!\r\n");
            retVal = BSP_EFAIL;
        }
    }
    else if (BSP_BOARD_CATALOG == boardId)
    {
        retVal = Bsp_boardEnableThs73681(
            standard,
            i2cData->probeInstId,
            (UInt32) BOARD_IO_EXP_I2C_ADDR_1);
    }
    else
    {
        /* Do nothing for other boards */
    }

    return (retVal);
}

const Char *Bsp_boardGetBoardString(void)
{
    UInt32      entryCnt;
    const Char *boardIdStr = NULL;
    Bsp_BoardId boardId;

    if (NULL != gBoardCommonObj.customData)
    {
        boardIdStr = gBoardCommonObj.customData->boardIdString;
    }
    else
    {
        boardId = Bsp_boardGetId();
        if (boardId >= BSP_BOARD_MAX)
        {
            boardId = BSP_BOARD_UNKNOWN;
        }

        for (entryCnt = 0U; entryCnt < BSP_BOARD_NUM_ID_STR_ENTRIES; entryCnt++)
        {
            if (gBoardIdStrTable[entryCnt].boardId == boardId)
            {
                boardIdStr = gBoardIdStrTable[entryCnt].boardIdStr;
                break;
            }
        }
    }
    GT_assert(BspBoardTrace, (boardIdStr != NULL));

    return (boardIdStr);
}

Int32 Bsp_boardSetPinMux(UInt32        drvId,
                         UInt32        instId,
                         Bsp_BoardMode boardMode)
{
    Int32 status = FVID2_SOK;

    if (BSP_BOARD_MODE_NONE != boardMode)
    {
        if (NULL != gBoardCommonObj.customData)
        {
            if (NULL != gBoardCommonObj.customData->setPinMuxFxn)
            {
                gBoardCommonObj.customData->setPinMuxFxn(drvId, instId,
                                                         boardMode);
            }
        }
        else
        {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX)
#if defined (SOC_TDA2EX)
            Bsp_boardSetPinMuxTda2ex(drvId, instId, boardMode);
#else
            Bsp_boardSetPinMuxTda2xx(drvId, instId, boardMode);
#endif
#endif

#if defined (SOC_TDA3XX)
            Bsp_boardSetPinMuxTda3xx(drvId, instId, boardMode);
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
            Bsp_boardSetPinMuxAm572x(drvId, instId, boardMode);
#endif
        }
    }

    return (status);
}

const Char *Bsp_boardGetBaseBoardRevString(void)
{
    Bsp_BoardRev boardRev;
    const Char  *boardRevStr = NULL;

    if (NULL != gBoardCommonObj.customData)
    {
        boardRevStr = gBoardCommonObj.customData->boardRevString;
    }
    else
    {
        /* Check for out of bound access */
        GT_assert(BspBoardTrace,
                  (BSP_BOARD_REV_MAX ==
                   ((sizeof (gBoardRevStr)) / (sizeof (Char *)))));

        boardRev = Bsp_boardGetBaseBoardRev();
        if (boardRev >= BSP_BOARD_REV_MAX)
        {
            boardRev = BSP_BOARD_REV_UNKNOWN;
        }
        boardRevStr = gBoardRevStr[boardRev];
    }

    return (boardRevStr);
}

const Char *Bsp_boardGetDcRevString(void)
{
    Bsp_BoardRev boardRev;

    /* Check for out of bound access */
    GT_assert(BspBoardTrace,
              (BSP_BOARD_REV_MAX ==
               ((sizeof (gBoardRevStr)) / (sizeof (Char *)))));

    boardRev = Bsp_boardGetDcRev();
    if (boardRev >= BSP_BOARD_REV_MAX)
    {
        boardRev = BSP_BOARD_REV_UNKNOWN;
    }

    return (gBoardRevStr[boardRev]);
}

void Bsp_boardPrintInfo(void)
{
    GT_1trace(BspBoardTrace, GT_INFO,
              " Board Detected        : [%s]\r\n", Bsp_boardGetBoardString());
    GT_1trace(BspBoardTrace, GT_INFO,
              " Base Board Revision   : [%s]\r\n",
              Bsp_boardGetBaseBoardRevString());
    GT_1trace(BspBoardTrace, GT_INFO,
              " Daughter Card Revision: [%s]\r\n", Bsp_boardGetDcRevString());

    return;
}

static Int32 Bsp_boardEnableThs7353(Fvid2_Standard standard,
                                    UInt32         i2cInstId,
                                    UInt32         i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt8  regAddr, regValue;
    UInt32 numRegs;

    switch (standard)
    {
        case FVID2_STD_1080P_60:
        case FVID2_STD_1080P_50:
        case FVID2_STD_SXGA_60:
        case FVID2_STD_SXGA_75:
        case FVID2_STD_SXGAP_60:
        case FVID2_STD_SXGAP_75:
        case FVID2_STD_UXGA_60:
            regValue = (UInt8) 0x9CU;
            break;

        case FVID2_STD_1080I_60:
        case FVID2_STD_1080I_50:
        case FVID2_STD_1080P_24:
        case FVID2_STD_1080P_30:
        case FVID2_STD_720P_60:
        case FVID2_STD_720P_50:
        case FVID2_STD_SVGA_60:
        case FVID2_STD_SVGA_72:
        case FVID2_STD_SVGA_75:
        case FVID2_STD_SVGA_85:
        case FVID2_STD_XGA_60:
        case FVID2_STD_XGA_DSS_TDM_60:
        case FVID2_STD_XGA_70:
        case FVID2_STD_XGA_75:
        case FVID2_STD_XGA_85:
        case FVID2_STD_WXGA_60:
        case FVID2_STD_WXGA_75:
        case FVID2_STD_WXGA_85:
            regValue = (UInt8) 0x94U;
            break;

        case FVID2_STD_480P:
        case FVID2_STD_576P:
        case FVID2_STD_VGA_60:
        case FVID2_STD_VGA_72:
        case FVID2_STD_VGA_75:
        case FVID2_STD_VGA_85:
            regValue = (UInt8) 0x4CU;
            break;

        case FVID2_STD_NTSC:
        case FVID2_STD_PAL:
        case FVID2_STD_480I:
        case FVID2_STD_576I:
        case FVID2_STD_D1:
            regValue = (UInt8) 0x04U;
            break;

        default:
            regValue = (UInt8) 0x94U;
            break;
    }

    regAddr = (UInt8) 0x01U;
    numRegs = 1U;
    retVal += Bsp_deviceWrite8(i2cInstId, i2cDevAddr, &regAddr, &regValue,
                               numRegs);
    regAddr = (UInt8) 0x02U;
    retVal += Bsp_deviceWrite8(i2cInstId, i2cDevAddr, &regAddr, &regValue,
                               numRegs);
    regAddr = (UInt8) 0x03U;
    retVal += Bsp_deviceWrite8(i2cInstId, i2cDevAddr, &regAddr, &regValue,
                               numRegs);

    return (retVal);
}

/* Used for TI814x VC REV B card only */
static Int32 Bsp_boardEnableThs73681(Fvid2_Standard standard,
                                     UInt32         i2cInst,
                                     UInt32         ioExpAddr)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regValue[2];
    UInt32 numRegs;
    UInt32 regValueTemp;

    numRegs = 2U;
    retVal  = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
    GT_assert(BspBoardTrace, (retVal == FVID2_SOK));

    /*  PCF8575 - mappings
     *  P7 - THS73861_FILTER2
     *  P6 - THS73861_FILTER1
     *  P5 - THS73861_BYPASS
     *  P4 - THS73861_DISABLE
     *  P0 - TVP7002_RSTN */
    /* Enable filter, disable bypass, clear filter select bits */
    regValueTemp =
        ((UInt32) regValue[0] & ((UInt32) ~(BOARD_PCF8575_THS73861_DISABLE_MASK
                                            |
                                            BOARD_PCF8575_THS73861_BYPASS_MASK
                                            |
                                            BOARD_PCF8575_THS73861_FILTER1_MASK
                                            |
                                            BOARD_PCF8575_THS73861_FILTER2_MASK)));
    regValue[0] = (UInt8) regValueTemp;

    switch (standard)
    {
        case FVID2_STD_1080P_60:
        case FVID2_STD_1080P_50:
        case FVID2_STD_SXGA_60:
        case FVID2_STD_SXGA_75:
        case FVID2_STD_SXGAP_60:
        case FVID2_STD_SXGAP_75:
        case FVID2_STD_UXGA_60:
            /* Filter2: 1, Filter1: 1 */
            regValueTemp = (UInt32) regValue[0] |
                           (BOARD_PCF8575_THS73861_FILTER1_MASK |
                            BOARD_PCF8575_THS73861_FILTER2_MASK);
            regValue[0] = (UInt8) regValueTemp;
            break;

        case FVID2_STD_1080I_60:
        case FVID2_STD_1080I_50:
        case FVID2_STD_1080P_24:
        case FVID2_STD_1080P_30:
        case FVID2_STD_720P_60:
        case FVID2_STD_720P_50:
        case FVID2_STD_SVGA_60:
        case FVID2_STD_SVGA_72:
        case FVID2_STD_SVGA_75:
        case FVID2_STD_SVGA_85:
        case FVID2_STD_XGA_60:
        case FVID2_STD_XGA_DSS_TDM_60:
        case FVID2_STD_XGA_70:
        case FVID2_STD_XGA_75:
        case FVID2_STD_XGA_85:
        case FVID2_STD_WXGA_60:
        case FVID2_STD_WXGA_75:
        case FVID2_STD_WXGA_85:
            /* Filter2: 0, Filter1: 1 */
            regValueTemp =
                ((UInt32) regValue[0] &
                 ((UInt32) (~BOARD_PCF8575_THS73861_FILTER2_MASK)));
            regValue[0]  = (UInt8) regValueTemp;
            regValueTemp =
                ((UInt32) regValue[0] | (BOARD_PCF8575_THS73861_FILTER1_MASK));
            regValue[0] = (UInt8) regValueTemp;
            break;

        case FVID2_STD_480P:
        case FVID2_STD_576P:
        case FVID2_STD_VGA_60:
        case FVID2_STD_VGA_72:
        case FVID2_STD_VGA_75:
        case FVID2_STD_VGA_85:
            /* Filter2: 1, Filter1: 0 */
            regValueTemp =
                ((UInt32) regValue[0] &
                 ((UInt32) (~BOARD_PCF8575_THS73861_FILTER1_MASK)));
            regValue[0]  = (UInt8) regValueTemp;
            regValueTemp =
                ((UInt32) regValue[0] | (BOARD_PCF8575_THS73861_FILTER2_MASK));
            regValue[0] = (UInt8) regValueTemp;
            break;

        case FVID2_STD_NTSC:
        case FVID2_STD_PAL:
        case FVID2_STD_480I:
        case FVID2_STD_576I:
        case FVID2_STD_D1:
            /* Filter2: 0, Filter1: 0 */
            regValueTemp =
                ((UInt32) regValue[0] &
                 ((UInt32) ~(BOARD_PCF8575_THS73861_FILTER1_MASK |
                             BOARD_PCF8575_THS73861_FILTER2_MASK)));
            regValue[0] = (UInt8) regValueTemp;
            break;

        default:
            /* Filter2: 0, Filter1: 1 */
            regValueTemp =
                ((UInt32) regValue[0] &
                 (UInt32) (~BOARD_PCF8575_THS73861_FILTER2_MASK));
            regValue[0]  = (UInt8) regValueTemp;
            regValueTemp =
                ((UInt32) regValue[0] | (BOARD_PCF8575_THS73861_FILTER1_MASK));
            regValue[0] = (UInt8) regValueTemp;
            break;
    }

    retVal = Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
    GT_assert(BspBoardTrace, (retVal == FVID2_SOK));

    return (retVal);
}

static Int32 Bsp_boardLock(void)
{
    BspOsal_semWait(gBoardCommonObj.lock, BSP_OSAL_WAIT_FOREVER);

    return (BSP_SOK);
}

static Int32 Bsp_boardUnlock(void)
{
    BspOsal_semPost(gBoardCommonObj.lock);

    return (BSP_SOK);
}

