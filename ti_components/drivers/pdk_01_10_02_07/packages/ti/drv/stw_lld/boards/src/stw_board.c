/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 *
 */

/**
 * \file   stw_board.c
 *
 * \brief  This file contains the implementation of the APIs that abstract the
 *         board-specific details for StarterWare.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/platform/stw_platform.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/stw_lld/boards/src/stw_boardPriv.h>
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Enables the MMR region lock  */
/**<  Note : Only if required Enable the macro to lock the MMR region
 *    In the code if unlock MMR and lock MMR is not taken care properly ,
 *    by enabling this macro will result in hang while configuring pinmux ,
 *    PRCM etc.,
 */
/* #define BOARD_MMR_REG_LOCK_ENABLE*/

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
extern boardPinmuxBoardCfg_t gBoardTda2xxPinMuxData[
    NUM_OF_TDA2XXBOARD_PINMUX_CONFIGUARATIONS];
#endif
#if defined (SOC_TDA3XX)
extern boardPinmuxBoardCfg_t gBoardTda3xxPinMuxData[
    NUM_OF_TDA3XXBOARD_PINMUX_CONFIGUARATIONS];
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct boardIdString_t
 *  \brief Structure to store board ID and string pair.
 */
typedef struct boardIdString
{
    boardId_t   boardId;
    /**< Board ID. */
    const char *pBoardIdStr;
    /**< Pointer to board ID string. */
} boardIdString_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* None */
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Board module object. */
static boardCommonObj_t      gBoardCommonObj;

/** \brief Table containing all board ID strings */
static const boardIdString_t gBoardIdStrTable[] =
{
    {BOARD_UNKNOWN,       "UNKNOWN"       },
    {BOARD_VS,            "VS"            },
    {BOARD_VC,            "VC"            },
    {BOARD_VISION,        "Vision"        },
    {BOARD_VISION_TI81XX, "Vision(TI81XX)"},
    {BOARD_CATALOG,       "Catalog"       },
    {BOARD_CUSTOM,        "Custom"        },
    {BOARD_JAMR3,         "JAMR3"         },
    {BOARD_MULTIDES,      "MULTIDES"      },
    {BOARD_BASE_TDA2XX,   "TDA2XX BASE"   },
    {BOARD_BASE_TDA3XX,   "TDA3XX BASE"   },
    {BOARD_BASE_TI81XX,   "TI81XX BASE"   },
    {BOARD_BASE_TDA2EX,   "TDA2EX BASE"   },
};

static const char           *gBoardRevStr[] =
{
    "UNKNOWN",
    "REV A",
    "REV B",
    "REV C",
};

/** \brief Number of entries in board ID string table. */
#define BOARD_NUM_ID_STR_ENTRIES        (sizeof (gBoardIdStrTable) / \
                                         sizeof (boardIdString_t))

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t BOARDInit(const boardInitParams_t *pInitPrms)
{
    int32_t           status = STW_SOK;
    boardInitParams_t localInitPrms;

    /* If NULL is passed the parameters will be initialized by default */
    if (NULL == pInitPrms)
    {
        pInitPrms = &localInitPrms;
        BoardInitParams_init(&localInitPrms);
    }
    memset(&gBoardCommonObj, 0, sizeof (gBoardCommonObj));

    gBoardCommonObj.boardId      = pInitPrms->boardId;
    gBoardCommonObj.baseBoardRev = pInitPrms->baseBoardRev;
    gBoardCommonObj.dcBoardRev   = pInitPrms->dcBoardRev;
    if (NULL != gBoardCommonObj.customData)
    {
        /* Below parameters can't be NULL */
        if ((gBoardCommonObj.customData->brdIdString == NULL) ||
            (gBoardCommonObj.customData->brdRevString == NULL) ||
            (gBoardCommonObj.customData->i2cData == NULL) ||
            (gBoardCommonObj.customData->brdData == NULL))
        {
            status = STW_EFAIL;
        }
    }

    /* Macro is used insted of checking for SoC. Any SoC API
     * cannot be called in board init as SoC init happens after board
     * init */
    if (status == STW_SOK)
    {
        if (NULL != gBoardCommonObj.customData)
        {
            if (NULL != gBoardCommonObj.customData->initFxn)
            {
                status = gBoardCommonObj.customData->initFxn();
            }
        }
        else
        {
            /* Use default built-in board functions */
#if defined (SOC_TDA2EX)
            status = BOARDTda2exInit(pInitPrms);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
            status = BOARDTda2xxInit(pInitPrms);
#endif
#if defined (SOC_TDA3XX)
            status = BOARDTda3xxInit(pInitPrms);
#endif      /* ifdef SOC_TDA3XX */
        }
    }
    return (status);
}

int32_t BOARDDeInit(void *args)
{
    int32_t status = STW_SOK;

    return (status);
}

boardId_t BOARDGetId(void)
{
    if (BOARD_MAX == gBoardCommonObj.boardId)
    {
        if (PLATFORMGetId() != PLATFORM_ID_EVM)
        {
            gBoardCommonObj.boardId = BOARD_UNKNOWN;
        }
        else
        {
#if defined (SOC_TDA2EX)
            gBoardCommonObj.boardId = BOARDGetIdTda2ex();
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
            gBoardCommonObj.boardId = BOARDGetIdTda2xx();
#endif
#if defined (SOC_TDA3XX)
            gBoardCommonObj.boardId = BOARDGetIdTda3xx();
#endif
#if defined (TI814X_BUILD)
            gBoardCommonObj.boardId = BOARDGetIdTI814x();
#endif
        }
    }
    return (gBoardCommonObj.boardId);
}

const char *BOARDGetBoardName(void)
{
    const char *pBoardIdStr = NULL;
    uint32_t    entryCnt;
    boardId_t   boardId;

    if (NULL != gBoardCommonObj.customData)
    {
        pBoardIdStr = gBoardCommonObj.customData->brdIdString;
    }
    else
    {
        boardId = BOARDGetId();
        if (boardId > BOARD_MAX)
        {
            boardId = BOARD_UNKNOWN;
        }

        for (entryCnt = 0U; entryCnt < BOARD_NUM_ID_STR_ENTRIES; entryCnt++)
        {
            if (gBoardIdStrTable[entryCnt].boardId == boardId)
            {
                pBoardIdStr = gBoardIdStrTable[entryCnt].pBoardIdStr;
                break;
            }
        }
    }

    return (pBoardIdStr);
}

boardRev_t BOARDGetBaseBoardRev(void)
{
    if (BOARD_REV_MAX == gBoardCommonObj.baseBoardRev)
    {
        if (PLATFORMGetId() != PLATFORM_ID_EVM)
        {
            /*
             * Set to first permitted revision, since it is irrelevant for
             * non-EVM platforms.
             */
            gBoardCommonObj.baseBoardRev = BOARD_REV_A;
        }
        else
        {
#if defined (SOC_TDA2EX)
            gBoardCommonObj.baseBoardRev = BOARDGetBaseBoardRevTda2ex();
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
            gBoardCommonObj.baseBoardRev = BOARDGetBaseBoardRevTda2xx();
#endif
#if defined (SOC_TDA3XX)
            gBoardCommonObj.baseBoardRev = BOARDGetBaseBoardRevTda3xx();
#endif
#if defined (TI814X_BUILD)
            gBoardCommonObj.baseBoardRev = BOARDGetBaseBoardRevTI814x();
#endif
        }
    }
    return (gBoardCommonObj.baseBoardRev);
}

const char *BOARDGetBaseBoardRevName(void)
{
    boardRev_t  boardRev = BOARD_REV_UNKNOWN;
    const char *retPtr   = NULL;

    /* Check for out of bound access */
    if (BOARD_REV_MAX == ((sizeof (gBoardRevStr)) / (sizeof (char *))))
    {
        boardRev = BOARDGetBaseBoardRev();
        if (boardRev >= BOARD_REV_MAX)
        {
            boardRev = BOARD_REV_UNKNOWN;
        }
        retPtr = gBoardRevStr[boardRev];
    }

    return (retPtr);
}

boardRev_t BOARDGetDcRev(void)
{
    if (BOARD_REV_MAX == gBoardCommonObj.dcBoardRev)
    {
        if (PLATFORMGetId() != PLATFORM_ID_EVM)
        {
            /*
             * Set to first permitted revision, since it is irrelevant for
             * non-EVM platforms.
             */
            gBoardCommonObj.dcBoardRev = BOARD_REV_A;
        }
        else
        {
#if defined (SOC_TDA2EX)
            gBoardCommonObj.dcBoardRev = BOARDGetDcRevTda2ex();
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
            gBoardCommonObj.dcBoardRev = BOARDGetDcRevTda2xx();
#endif
#if defined (SOC_TDA3XX)
            gBoardCommonObj.dcBoardRev = BOARDGetDcRevTda3xx();
#endif
#if defined (TI814X_BUILD)
            gBoardCommonObj.dcBoardRev = BOARDGetDcRevTI814x();
#endif
        }
    }
    return (gBoardCommonObj.dcBoardRev);
}

const char *BOARDGetDcRevName(void)
{
    boardRev_t  boardRev = BOARD_REV_UNKNOWN;
    const char *retPtr   = NULL;

    /* Check for out of bound access */
    if (BOARD_REV_MAX == ((sizeof (gBoardRevStr)) / (sizeof (char *))))
    {
        boardRev = BOARDGetDcRev();
        if (boardRev >= BOARD_REV_MAX)
        {
            boardRev = BOARD_REV_UNKNOWN;
        }
        retPtr = gBoardRevStr[boardRev];
    }

    return (retPtr);
}

const boardI2cData_t *BOARDGetI2cData(void)
{
    const boardI2cData_t *i2cData = NULL;
#if defined (SOC_TDA2EX)
    i2cData = BOARDGetI2cDataTda2ex();
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    i2cData = BOARDGetI2cDataTda2xx();
#endif
#if defined (SOC_TDA3XX)
    i2cData = BOARDGetI2cDataTda3xx();
#endif
#if defined (TI814X_BUILD)
    i2cData = BOARDGetI2cDataTI814x();
#endif

    return (i2cData);
}

const boardData_t *BOARDGetData(void)
{
    const boardData_t *pBoardData = NULL;

    if (NULL != gBoardCommonObj.customData)
    {
        pBoardData = gBoardCommonObj.customData->brdData;
    }
    else
    {
#if defined (SOC_TDA2EX)
        pBoardData = BOARDGetDataTda2ex();
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
        pBoardData = BOARDGetDataTda2xx();
#endif
#if defined (SOC_TDA3XX)
        pBoardData = BOARDGetDataTda3xx();
#endif
#if defined (TI814X_BUILD)
        pBoardData = BOARDGetDataTI814x();
#endif
    }
    return (pBoardData);
}

uint32_t BOARDGetDeviceCtrlModId(uint32_t devId, uint32_t devInstNum)
{
    uint32_t ctrlModId = BOARD_INVALID_ID;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum))
                {
                    ctrlModId = pDevData->ctrlModId;
                    break;
                }
            }
        }

        if (BOARD_INVALID_ID == ctrlModId)
        {
            UARTPuts("\r\nInvalid device ID!!", (-((int32_t) 1)));
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (ctrlModId);
}

uint32_t BOARDGetDeviceCtrlModInstNum(uint32_t devId, uint32_t devInstNum)
{
    uint32_t ctrlModInstNum = BOARD_INVALID_INST_NUM;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum))
                {
                    ctrlModInstNum = pDevData->ctrlModInstNum;
                    break;
                }
            }
        }
        if (BOARD_INVALID_INST_NUM == ctrlModInstNum)
        {
            UARTPuts("\r\nInvalid device ID!!", (-((int32_t) 1)));
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (ctrlModInstNum);
}

uint32_t BOARDGetDeviceCtrlInfo(uint32_t devId, uint32_t devInstNum)
{
    uint32_t ctrlInfo = BOARD_INVALID_INFO;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum))
                {
                    ctrlInfo = pDevData->ctrlInfo;
                    break;
                }
            }
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (ctrlInfo);
}

uint32_t BOARDGetDeviceDataModId(uint32_t devId, uint32_t devInstNum)
{
    uint32_t dataModId = BOARD_INVALID_ID;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum))
                {
                    dataModId = pDevData->dataModId;
                    break;
                }
            }
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (dataModId);
}

uint32_t BOARDGetDeviceDataModInstNum(uint32_t devId, uint32_t devInstNum)
{
    uint32_t dataModInstNum = BOARD_INVALID_INST_NUM;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum))
                {
                    dataModInstNum = pDevData->dataModInstNum;
                    break;
                }
            }
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (dataModInstNum);
}

int32_t BOARDPowerOnDevice(uint32_t devId,
                           uint32_t devInstNum,
                           uint32_t powerOn)
{
    int32_t  status = STW_SOK;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum) &&
                    (pDevData->pFnPowerOnDev != NULL))
                {
                    status = pDevData->pFnPowerOnDev(devId, devInstNum, powerOn);
                    if (STW_SOK != status)
                    {
                        UARTPuts("\r\nDevice power-on failed!!", (-((int32_t) 1)));
                    }
                    break;
                }
            }
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (status);
}

int32_t BOARDSelectDevice(uint32_t devId, uint32_t devInstNum)
{
    int32_t  status = STW_SOK;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum) &&
                    (pDevData->pFnSelectDev != NULL))
                {
                    status = pDevData->pFnSelectDev(devId, devInstNum);
                    if (STW_SOK != status)
                    {
                        UARTPuts("\r\nDevice select failed!!", (-((int32_t) 1)));
                    }
                    break;
                }
            }
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (status);
}

int32_t BOARDResetDevice(uint32_t devId, uint32_t devInstNum)
{
    int32_t  status = STW_SOK;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum) &&
                    (pDevData->pFnResetDev != NULL))
                {
                    status = pDevData->pFnResetDev(devId, devInstNum);
                    if (STW_SOK != status)
                    {
                        UARTPuts("\r\nDevice reset failed!!", (-((int32_t) 1)));
                    }
                    break;
                }
            }
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (status);
}

int32_t BOARDSelectMode(uint32_t    devId,
                        uint32_t    instId,
                        boardMode_t boardMod)
{
    int32_t retVal = STW_SOK;

    if (NULL != gBoardCommonObj.customData)
    {
        if (NULL != gBoardCommonObj.customData->selectModeFxn)
        {
            retVal = gBoardCommonObj.customData->selectModeFxn(devId,
                                                               instId,
                                                               boardMod);
        }
    }
    else
    {
#if defined (SOC_TDA3XX)
        retVal = BOARDSelectModeTda3xx(devId, instId, boardMod);
#endif
    }
    return (retVal);
}

void BOARDPrintInfo(void)
{
    const char *baseBoardrevision = NULL;
    const char *boardIdStr        = NULL;
    const char *boardRevStr       = NULL;

    boardIdStr = BOARDGetBoardName();
    if (boardIdStr != NULL)
    {
        UARTPuts(" \r\nBoard Detected               : ", (-((int32_t) 1)));
        UARTPuts(boardIdStr, (-((int32_t) 1)));
    }
    else
    {
        UARTPuts(" \r\nNULL Pointer Detected boardIdStr  : ", (-((int32_t) 1)));
    }

    baseBoardrevision = BOARDGetBaseBoardRevName();
    if (baseBoardrevision != NULL)
    {
        UARTPuts(" \r\nBase Board Revision          : ", (-((int32_t) 1)));
        UARTPuts(baseBoardrevision, (-((int32_t) 1)));
    }
    else
    {
        UARTPuts(
            " \r\n baseBoardrevision out of bound error : ", (-((int32_t) 1)));
    }

    boardRevStr = BOARDGetDcRevName();
    if (boardRevStr != NULL)
    {
        UARTPuts(" \r\nDaughter Card Revision       : ", (-((int32_t) 1)));
        UARTPuts(boardRevStr, (-((int32_t) 1)));
    }
    else
    {
        UARTPuts(
            " \r\n Daughter Card Revision out of bound error  : ", (-((int32_t) 1)));
    }
}

void BOARDConfigModulePinMux(uint32_t moduleId,
                             uint32_t instNum,
                             uint32_t boardMod)
{
    const boardPinmuxBoardCfg_t *pPinmuxData = NULL;
    uint32_t i = 0;
    const boardData_t           *pBoardData = NULL;

    /* Get board Data */
    pBoardData = BOARDGetData();

    /* Get module Data */
    if (NULL != pBoardData)
    {
        pPinmuxData = pBoardData->pPinmuxData;
        if (pPinmuxData != NULL)
        {
            for (i = 0; (DEVICE_ID_INVALID != pPinmuxData[i].moduleId); i++)
            {
                if ((pPinmuxData[i].moduleId == moduleId) &&
                    (pPinmuxData[i].instNum == instNum) &&
                    ((pPinmuxData[i].boardMode & boardMod) == boardMod))
                {
                    PLATFORMSetPinmuxRegs(pPinmuxData[i].regOffset,
                                          pPinmuxData[i].regVal);
                }
            }
        }
        else
        {
            UARTPuts(" \r\nNULL Pointer Detected pPinmuxData  : ", (-((int32_t) 1)));
        }
    }
    return;
}

uint32_t BOARDIsDevicePresent(uint32_t devId)
{
    uint32_t found = FALSE;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if (pDevData->devId == devId)
                {
                    /* Found at least one instance of the specified device. */
                    found = (uint32_t) TRUE;
                    break;
                }
            }
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (found);
}

uint32_t BOARDGetNumDevices(uint32_t devId)
{
    uint32_t                 numDevFound = 0U;
    uint32_t                 devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if (pDevData->devId == devId)
                {
                    numDevFound++;
                }
            }
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (numDevFound);
}

uint32_t BOARDGetVideoDeviceInstId(uint32_t devDrvId,
                                   uint32_t drvId,
                                   uint32_t drvInstId)
{
    uint32_t instId = BOARD_INVALID_INST_ID;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devDrvId) &&
                    (pDevData->dataModId == drvId) &&
                    (pDevData->dataModInstNum == drvInstId))
                {
                    instId = pDevData->devInstNum;
                    break;
                }
            }
        }
        if (BOARD_INVALID_INST_ID == instId)
        {
            UARTPuts("\r\nInvalid device driver ID!!", (-((int32_t) 1)));
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (instId);
}

uint32_t BOARDGetVideoDeviceI2cInstId(uint32_t devDrvId,
                                      uint32_t drvId,
                                      uint32_t drvInstId)
{
    uint32_t i2cInstId = HSI2C_INST_MAX;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devDrvId) &&
                    (pDevData->dataModId == drvId) &&
                    (pDevData->dataModInstNum == drvInstId))
                {
                    i2cInstId = pDevData->ctrlModInstNum;
                    break;
                }
            }
        }

        if (HSI2C_INST_MAX == i2cInstId)
        {
            UARTPuts("\r\nInvalid device driver ID!!", (-((int32_t) 1)));
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (i2cInstId);
}

uint32_t BOARDGetVideoDeviceI2cAddr(uint32_t devDrvId,
                                    uint32_t drvId,
                                    uint32_t drvInstId)
{
    uint32_t i2cAddr = 0U;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                UARTPuts(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ", (-((int32_t) 1)));
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devDrvId) &&
                    (pDevData->dataModId == drvId) &&
                    (pDevData->dataModInstNum == drvInstId))
                {
                    i2cAddr = pDevData->ctrlInfo;
                    break;
                }
            }
        }
        if (0U == i2cAddr)
        {
            UARTPuts("\r\nInvalid device driver ID!!", (-((int32_t) 1)));
        }
    }
    else
    {
        UARTPuts(
            " \r\nNULL Pointer Detected pBoardData : ", (-((int32_t) 1)));
    }
    return (i2cAddr);
}

/**
 *  \brief Returns the console Instance ID of the connected Board
 *
 *
 *  \return console Instance ID
 */
uint32_t BOARDGetConsoleInstID(void)
{
    uint32_t uartInstId = DEVICE_UART_INST_ID_1;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    uartInstId = DEVICE_UART_INST_ID_1;
#elif defined (SOC_TDA3XX)
    uartInstId = DEVICE_UART_INST_ID_3;
#else
    /* Nothing to be done here */
#endif
    return uartInstId;
}

/**
 * \brief   Configures IO pins needed by UART console. This API uses the pin mux
 *          data and configures the pinmux of UART console for default mode
 *
 * \param   uartInstId     Instance number of the UART console
 *
 **/
void BOARDConfigConsolePinMux(uint32_t uartInstId)
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    BOARDTda2xxConfigConsolePinMux(uartInstId);
#elif defined (SOC_TDA2EX)
    BOARDTda2exConfigConsolePinMux(uartInstId);
#elif defined (SOC_TDA3XX)
    BOARDTda3xxConfigConsolePinMux(uartInstId);
#else
    /* Nothing to be done here */
#endif

    return;
}

