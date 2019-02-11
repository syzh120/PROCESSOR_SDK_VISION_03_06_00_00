/*
 *   Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file bspdrv_ar12xxInternal.c
 *
 *  \brief This file defines the internal test functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <bspdrv_ar12xxPriv.h>
#include <rl_driver.h>
#include <rl_controller.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static inline void  RL_SENSOR_OPCODE (rlDriverOpcode_t * opcode);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static inline void  RL_SENSOR_OPCODE (rlDriverOpcode_t * opcode)
{
    opcode->dir = RL_API_DIR_HOST_TO_BSS;
    opcode->msgType = RL_API_CLASS_CMD;
    opcode->nsbc = 1U;
}

/**
*   \brief Reads Internal Configuration Memory
*   \param profileId [in] Profile Id
*   \param memAddr   [in] Memory address
*   \param value     [out] Value at the memory address
*
*   \return int32_t Success - 0, Failure - Error Code
*
*   This function reads Internal Configuration Memory
*/
int32_t Bsp_ar12xxGetInternalConfig(uint8_t deviceMap, uint16_t profileId, uint32_t memAddr,
                                    uint32_t* data)
{
    int32_t retVal = RL_RET_CODE_OK;
    Bsp_ar12xxInternalCfg_t intCfg = {0};

    /* check if deviceIndex is out of defined value */
    if((rlDriverIsDeviceMapValid(deviceMap) != RL_RET_CODE_OK) || (RL_NULL_PTR == data) \
            || (RL_NULL_PTR == (uint32_t*)memAddr))
    {
        retVal = RL_RET_CODE_INVALID_INPUT;
    }
    else
    {
        /* Initialize Command and Response Sub Blocks */
        rlDriverMsg_t inMsg = {0};
        rlDriverMsg_t outMsg = {0};

        rlPayloadSb_t inPayloadSb = {0};
        rlPayloadSb_t* pInPayloadSb = &inPayloadSb;
        rlPayloadSb_t outPayloadSb = {0};
        rlPayloadSb_t* pOutPayloadSb = &outPayloadSb;

        inMsg.subblocks = pInPayloadSb;
        inMsg.remChunks = 0U;
        outMsg.subblocks = pOutPayloadSb;

        /* Expected Response Sub Blocks */
        outMsg.opcode.nsbc = 1U;

        /* Set Command Header Opcode */
        RL_SENSOR_OPCODE(&inMsg.opcode);
        inMsg.opcode.msgId = RL_RF_MISC_CONF_GET_MSG;

        inMsg.opcode.dir = rlDeviceIdentifyCmdDir(inMsg.opcode.msgId, rlDriverGetPlatformId());

        intCfg.profileId = profileId;
        intCfg.memAddr = memAddr;

        if((RL_NULL_PTR != pInPayloadSb) && (RL_NULL_PTR != pOutPayloadSb))
        {
            /* Set Command Sub Block*/
            pInPayloadSb->sbid = RL_GET_UNIQUE_SBID(RL_RF_MISC_CONF_GET_MSG,
                                                  RL_RF_REG_CONFIG_GET_SB);
            pInPayloadSb->len = (uint16_t)(sizeof(Bsp_ar12xxInternalCfg_t) - sizeof(uint32_t));
            pInPayloadSb->pSblkData = (uint8_t* )&intCfg;

            /* Pass Application buffer to receive response */
            outPayloadSb.pSblkData = (uint8_t* )&intCfg;

            /* Send Command to AR1XXX Device */
            retVal =  rlDriverCmdInvoke(deviceMap, inMsg, &outMsg);
            *data = intCfg.value;
        }
        else
        {
            retVal = RL_RET_CODE_FATAL_ERROR;
        }
    }

    return retVal;
}

/**
*   \brief Reads Internal Configuration Memory
*   \param profileId [in] Profile Id
*   \param memAddr   [in] Memory address
*   \param value     [out] Value at the memory address
*
*   \return int32_t Success - 0, Failure - Error Code
*
*   This function reads Internal Configuration Memory
*/
int32_t Bsp_ar12xxSetInternalConfig(uint8_t deviceMap,
                              uint16_t profileId,
                              uint32_t memAddr,
                              uint32_t data)
{
    int32_t retVal = RL_RET_CODE_OK;
    Bsp_ar12xxInternalCfg_t intCfg = {0};

    /* Initialize Command and Response Sub Blocks */
    rlDriverMsg_t inMsg = {0};
    rlDriverMsg_t outMsg = {0};

    rlPayloadSb_t inPayloadSb = {0};
    rlPayloadSb_t* pInPayloadSb = &inPayloadSb;
    rlPayloadSb_t outPayloadSb = {0};
    rlPayloadSb_t* pOutPayloadSb = &outPayloadSb;

    /* check if deviceIndex is out of defined value */
    if((rlDriverIsDeviceMapValid(deviceMap) != RL_RET_CODE_OK) \
            || (RL_NULL_PTR == (uint32_t*)memAddr))
    {
        retVal = RL_RET_CODE_INVALID_INPUT;
    }
    else
    {
        inMsg.subblocks = pInPayloadSb;
        inMsg.remChunks = 0U;
        outMsg.subblocks = pOutPayloadSb;

        /* Expected Response Sub Blocks */
        outMsg.opcode.nsbc = 0U;

        /* Set Command Header Opcode */
        RL_SENSOR_OPCODE(&inMsg.opcode);
        inMsg.opcode.msgId = RL_RF_MISC_CONF_SET_MSG;

        inMsg.opcode.dir = rlDeviceIdentifyCmdDir(inMsg.opcode.msgId, rlDriverGetPlatformId());

        intCfg.profileId = profileId;
        intCfg.memAddr = memAddr;
        intCfg.value = data;

        if((RL_NULL_PTR != pInPayloadSb) && (RL_NULL_PTR != pOutPayloadSb))
        {
            /* Set Command Sub Block*/
            pInPayloadSb->sbid = RL_GET_UNIQUE_SBID(RL_RF_MISC_CONF_SET_MSG,
                                              RL_RF_REG_CONFIG_SET_SB);
            pInPayloadSb->len = (uint16_t)(sizeof(Bsp_ar12xxInternalCfg_t));
            pInPayloadSb->pSblkData = (uint8_t* )&intCfg;

            /* Pass Application buffer to receive response */
            outPayloadSb.pSblkData = RL_NULL_PTR;

            /* Send Command to AR1XXX Device */
            retVal =  rlDriverCmdInvoke(deviceMap, inMsg, &outMsg);
        }
        else
        {
            retVal = RL_RET_CODE_FATAL_ERROR;
        }
    }
    return retVal;
}
/**
*   \brief Writes Internal Configuration Memory
*   \param memAddr   [in]  - Memory address
*   \param value     [in]  - Value to write at memory address
*   \param deviceMap [in]  - Connected device Index
*
*   \return int32_t Success - 0, Failure - Error Code
*
*   \brief Writes Internal Configuration Memory
*/
int32_t Bsp_ar12xxDeviceSetInternalConf(uint8_t deviceMap, uint32_t memAddr, uint32_t value)
{
    int32_t retVal = RL_RET_CODE_OK;
    Bsp_ar12xxDevInternalCfg_t intCfg = {0};

    /* check if deviceIndex is out of defined value */
    if((rlDriverIsDeviceMapValid(deviceMap) != RL_RET_CODE_OK) ||
            (RL_NULL_PTR == (uint32_t*)memAddr))
    {
        retVal = RL_RET_CODE_INVALID_INPUT;
    }
    else
    {
        /* Initialize Command and Response Sub Blocks */
        rlDriverMsg_t inMsg = {0};
        rlDriverMsg_t outMsg = {0};

        /* Initialize Command and Response Sub Blocks */
        rlPayloadSb_t inPayloadSb = {0};
        rlPayloadSb_t* pInPayloadSb = &inPayloadSb;

        inMsg.subblocks = pInPayloadSb;
        inMsg.remChunks = 0U;

        /* Set Command Header Opcode */
        inMsg.opcode.msgType = RL_API_CLASS_CMD;
        inMsg.opcode.nsbc = 1U;
        inMsg.opcode.msgId = RL_DEV_INTERNAL_CONF_SET_MSG;
        inMsg.opcode.dir = rlDeviceIdentifyCmdDir(inMsg.opcode.msgId, rlDriverGetPlatformId());

        /* Fill SubBlock Data */
        intCfg.memAddr = memAddr;
        intCfg.value = value;

        inPayloadSb.sbid = RL_GET_UNIQUE_SBID(RL_DEV_INTERNAL_CONF_SET_MSG, RL_DEV_MEM_REGISTER_SB);
        inPayloadSb.len = (uint16_t)(sizeof(intCfg));
        inPayloadSb.pSblkData = (uint8_t*)&intCfg;

        /* Send Command to AR1XXX Device */
        retVal = rlDriverCmdInvoke(deviceMap, inMsg, &outMsg);
    }

    return retVal;

}

/**
*   \brief Reads Internal Configuration Memory
*   \param memAddr    [in]   - Memory address
*   \param value     [out]   - Value at memory address
*   \param deviceMap  [in]   - Connected device Index
*
*   \return int32_t Success - 0, Failure - Error Code
*
*/
int32_t Bsp_ar12xxDeviceGetInternalConf(uint8_t deviceMap, uint32_t memAddr, uint32_t* value)
{
    int32_t retVal = RL_RET_CODE_OK;
    Bsp_ar12xxDevInternalCfg_t intCfg = {0};

    /* check if deviceIndex is out of defined value */
    if((rlDriverIsDeviceMapValid(deviceMap) != RL_RET_CODE_OK) ||
            (RL_NULL_PTR == (uint32_t*)memAddr))
    {
        retVal = RL_RET_CODE_INVALID_INPUT;
    }
    else
    {
        /* Initialize Command and Response Sub Blocks */
        rlDriverMsg_t inMsg = {0};
        rlDriverMsg_t outMsg = {0};

        /* Initialize Command and Response Sub Blocks */
        rlPayloadSb_t inPayloadSb = {0};
        rlPayloadSb_t* pInPayloadSb = &inPayloadSb;
        rlPayloadSb_t outPayloadSb = {0};
        rlPayloadSb_t* pOutPayloadSb = &outPayloadSb;

        inMsg.subblocks = pInPayloadSb;
        inMsg.remChunks = 0U;

        outMsg.subblocks = pOutPayloadSb;

        /* Expected Response Sub Blocks */
        outMsg.opcode.nsbc = 1U;

        /* Set Command Header Opcode */
        inMsg.opcode.msgType = RL_API_CLASS_CMD;
        inMsg.opcode.nsbc = 1U;
        inMsg.opcode.msgId = RL_DEV_INTERNAL_CONF_GET_MSG;
        inMsg.opcode.dir = rlDeviceIdentifyCmdDir(inMsg.opcode.msgId, rlDriverGetPlatformId());

        inPayloadSb.sbid = RL_GET_UNIQUE_SBID(RL_DEV_INTERNAL_CONF_GET_MSG, RL_DEV_MEM_REGISTER_SB);
        inPayloadSb.len = (uint16_t)(sizeof(uint32_t));
        inPayloadSb.pSblkData = (uint8_t*)&memAddr;

        outPayloadSb.pSblkData = (uint8_t*)&intCfg;

        /* Send Command to AR1XXX Device */
        retVal =  rlDriverCmdInvoke(deviceMap, inMsg, &outMsg);

        *value = intCfg.value;
    }

    return retVal;

}

