/*
 *   Copyright (c) Texas Instruments Incorporated 2015
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
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_ESM ESM
 *
 *  @{
 */
/**
 *  \file     esm.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of ESM.
 *            This also contains some related macros.
 */

#ifndef ESM_H_
#define ESM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/soc.h>
#include <ti/csl/cslr_esm.h>


#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum to select the ESM Operation Mode.
 */
typedef enum esmOperationMode
{
    ESM_OPERATION_MODE_NORMAL = ESM_ESMEKR_EKEY_NORMAL_MODE,
    /**< Configure ESM operation mode to normal mode */
    ESM_OPERATION_MODE_ERROR_FORCE = ESM_ESMEKR_EKEY_ERROR_FORCE_MODE
    /**< Configure ESM operation mode to error force mode */
}esmOperationMode_t;

/**
 * \brief  Enum to select level for interrupt.
 */
typedef enum esmIntrPriorityLvl
{
    ESM_INTR_PRIORITY_LEVEL_LOW = 0x0U,
    /**< Configure interrupt to high level interrupt */
    ESM_INTR_PRIORITY_LEVEL_HIGH = 0x1U
                                   /**< Configure interrupt to low level
                                    * interrupt */
}esmIntrPriorityLvl_t;

/**
 * \brief  Structure to access the status of interrupts belonging to a group.
 */
typedef struct esmGroupIntrStatus
{
    uint32_t grpIntrStatus[ESM_NUM_INTR_PER_GROUP / 32U];
    /**< Contains status for interrupts from a group */
}esmGroupIntrStatus_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API is used to configure operation mode of ESM module.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \param   mode            Channel number for which reset is to be done.
 *                          Refer enum #esmOperationMode_t.
 *
 * \return  None
 */
void ESMSetMode(uint32_t baseAddr, uint32_t mode);

/**
 * \brief   This API is used to set the influence of interrupt on nERROR pin.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt source which will influence nERROR pin.
 *                          Refer enum #esmGroup1IntrSrc_t.
 *
 * \param   influence       Enables influence on nERROR pin if it is TRUE.
 *                          Disables influence on nERROR pin if it is FALSE.
 *
 * \return  None
 */
void ESMSetInfluenceOnErrPin(uint32_t baseAddr, uint32_t intrSrc,
                             uint32_t influence);

/**
 * \brief   This API is used to configure the low time counter pre-load value.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \param   lowTime         Time to be configured as LTCP.
 *
 * \return  status          Configuration status.
 */
int32_t ESMSetErrPinLowTimePreload(uint32_t baseAddr, uint32_t lowTime);

/**
 * \brief   This API is used to get the current value of low time counter.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \return  Counter value   Current low time count.
 */
uint32_t ESMGetCurrErrPinLowTimeCnt(uint32_t baseAddr);

/**
 * \brief   This API is used to get the current status of nERROR pin.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \return  status          Current nERROR pin status.
 */
uint32_t ESMGetErrPinStatus(uint32_t baseAddr);

/**
 * \brief   This API is used to reset the nERROR pin.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \return  None
 *
 * \note    This will set the nERROR pin to high.
 */
void ESMResetErrPin(uint32_t baseAddr);

/**
 * \brief   This API is used to enable interrupt.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt to enable.
 *                          Refer enum #esmGroup1IntrSrc_t.
 *
 * \return  None
 */
void ESMEnableIntr(uint32_t baseAddr, uint32_t intrSrc);

/**
 * \brief   This API is used to disable interrupt.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt to disable.
 *                          Refer enum #esmGroup1IntrSrc_t.
 *
 * \return  None
 */
void ESMDisableIntr(uint32_t baseAddr, uint32_t intrSrc);

/**
 * \brief   This API is used to set interrupt level.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt to set the level.
 *                          Refer enum #esmGroup1IntrSrc_t.
 *
 * \param   intrPriorityLvl Interrupt level to set.
 *                          Refer enum #esmIntrPriorityLvl_t.
 *
 * \return  None
 */
void ESMSetIntrPriorityLvl(uint32_t baseAddr, uint32_t intrSrc,
                           uint32_t intrPriorityLvl);

/**
 * \brief   This API is used to get the interrupt status.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt for which status to return.
 *                          Refer enum #esmGroup1IntrSrc_t.
 *
 *
 * \return  status          Interrupt status.
 */
uint32_t ESMGetIntrStatus(uint32_t baseAddr, uint32_t intrSrc);

/**
 * \brief   This API is used to get the interrupt/error status for a group.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \param   grpNum          Group for which status to return.
 *                          It Starts from 1 and should not be more than
 *                          ESM_NUM_GROUP_MAX.
 *
 * \param   intrstatus      Interrupt status.
 *                          Refer struct #esmGroupIntrStatus_t.
 *
 * \return  status          Success/failure.
 */
int32_t ESMGetGroupIntrStatus(uint32_t baseAddr, uint32_t grpNum,
                              esmGroupIntrStatus_t *intrstatus);

/**
 * \brief   This API is used to clear the interrupt status.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \param   intrSrc         Interrupt to clear status.
 *                          Refer enum #esmGroup1IntrSrc_t.
 *
 * \return  None
 */
void ESMClearIntrStatus(uint32_t baseAddr, uint32_t intrSrc);

/**
 * \brief   This API is used to get the highest level pending interrupt in
 *          high level interrupts.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \return  Interrupt Source
 *                          Highest level pending interrupt
 */
uint32_t ESMGetHighPriorityLvlIntrStatus(uint32_t baseAddr);

/**
 * \brief   This API is used to get the highest level pending interrupt in
 *          low level interrupts.
 *
 * \param   baseAddr        Base Address of the ESM Registers.
 *
 * \return  Interrupt Source
 *                          Lowest level pending interrupt
 */
uint32_t ESMGetLowPriorityLvlIntrStatus(uint32_t baseAddr);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
 /** @} */
