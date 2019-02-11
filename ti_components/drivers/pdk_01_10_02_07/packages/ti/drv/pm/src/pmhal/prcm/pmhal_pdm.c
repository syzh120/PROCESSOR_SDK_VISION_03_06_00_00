/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
 * \file    pmhal_pdm.c
 *
 * \brief   Power Domain Manager (PDM) interface implementation.
 *
 *          The Power Domain Manager (PDM) implements the following:
 *          - Interface to set the power state of the power domain (PD).
 *          - Interface to set the logic retention state when the PD is in
 *            retention.
 *          - Interface to request low power state change for the power domain.
 *          - Interface to set the memory retention state for the memory in the
 *            power domain.
 *          - Interface to read the power state of the power domain.
 *          - Interface to read the state of the logic in the power domain.
 *          - Interface to check if the power domain transition is complete.
 *          - Interface to read the last power state of the power domain.
 *          - Interface to read the memory bank status of a given memory in the
 *            power domain.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include "pm_types.h"
#include "pmhal_prcm.h"
#include "pmhal_pdm.h"
#include "hw_pmhal_data.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief This API verifies if the power domain Id is valid or not.
 *
 * \param   pdId             Unique ID of the power domain to be checked.
 *
 * \retval  errorStatus      Status of the API call. Can be any of the following
 *          PM_SUCCESS                           Indicates the operation is
 *                                               success
 *          PM_INPUT_PARAM_BAD_POWER_DOMAIN_ID   Indicates the power domain ID
 *                                               is invalid.
 */
static pmErrCode_t PmhalPdmIsPDIdValid(pmhalPrcmPdId_t pdId);

/**
 * \brief   This API verifies if the power domain state provided is valid or not
 *          for a given power domain.
 *
 * \param   pdId            Unique ID of the power domain to be checked.
 * \param   pdState         Power Domain state provided.
 *
 * \retval  retVal          Status of the API call. Can be any of the following
 *          PM_SUCCESS      Indicates the power domain state is correct.
 *          PM_BADARGS      Indicates the power domain state is not supported
 *                          for the given power domain.
 */
static pmErrCode_t PmhalPdmIsPowerStateValid(pmhalPrcmPdId_t    pdId,
                                             pmhalPrcmPdState_t pdState);

/**
 * \brief   This API verifies if the Logic retention state provided is valid or
 *          not for a given power domain.
 *
 * \param   pdId            Unique ID of the power domain to be checked.
 * \param   logicState      Logic Retention State provided.
 *
 * \retval  retVal          Status of the API call. Can be any of the following
 *          PM_SUCCESS      Indicates the Logic Retention state is correct.
 *          PM_BADARGS      Indicates the Logic Retention state is not supported
 *                          for the given power domain.
 */
static pmErrCode_t PmhalPdmIsLogicRetStateValid(
    pmhalPrcmPdId_t            pdId,
    pmhalPrcmPdLogicRetState_t logicState);

/**
 * \brief   This API verifies if the Low Power Request provided is valid or
 *          not for a given power domain.
 *
 * \param   pdId            Unique ID of the power domain to be checked.
 * \param   lowPwrReq       Low Power Request provided.
 *
 * \retval  retVal          Status of the API call. Can be any of the following
 *          PM_SUCCESS      Indicates the lowPwrReq is correct.
 *          PM_BADARGS      Indicates the lowPwrReq is not supported
 *                          for the given power domain.
 */
static pmErrCode_t PmhalPdmIsLowPwrReqValid(
    pmhalPrcmPdId_t pdId,
    pmhalPrcmPdLowPwrStateChangeType_t
    lowPwrReq);

/**
 * \brief   This API verifies if the memory bank Id provided is valid and
 *          belongs to a given power domain.
 *
 * \param   pdId            Unique ID of the power domain to be checked.
 * \param   memBankId       Unique ID of the memory bank.
 *
 * \retval  retVal          Status of the API call. Can be any of the following
 *          PM_SUCCESS      Indicates the memory bank ID is correct.
 *          PM_BADARGS      Indicates the memory bank ID is not supported
 *                          for the given power domain or memory bank ID is
 *                          invalid.
 */
static pmErrCode_t PmhalPdmIsMemBankIdValid(pmhalPrcmPdId_t         pdId,
                                            pmhalPrcmPhyMemBankId_t memBankId);

/**
 * \brief   This API verifies if the memory bank retention status to be
 *          programmed if valid or not for the given memory bank.
 *
 * \param   memBankId       Unique ID of the memory bank.
 * \param   memoryRetState     Memory Retention Status given as an input.
 *
 * \retval  retVal          Status of the API call. Can be any of the following
 *          PM_SUCCESS      Indicates the memory retention request is valid.
 *          PM_BADARGS      Indicates the memory retention request is not
 *                          supported for the given memory bank ID.
 */
pmErrCode_t PmhalPdmIsMemRetStateValid(pmhalPrcmPhyMemBankId_t memBankId,
                                       uint32_t                memoryRetState);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PMHALPdmSetPDState(pmhalPrcmPdId_t pdId, pmhalPrcmPdState_t pdState,
                           uint32_t timeout)
{
    pmErrCode_t        retVal = PM_SUCCESS;
    pmhalPrcmPdState_t pdStateCurr;
    uint32_t           timeToWait;

    /* First check if the power domain is valid. If valid check whether the
     * power state is valid or not for the given power domain.
     */
    retVal = PmhalPdmIsPDIdValid(pdId);

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalPdmIsPowerStateValid(pdId, pdState);
    }

    if (PM_SUCCESS == retVal)
    {
        /* Always on power domains do not have a valid power state control
         * register. Make sure the power domain has a valid power state control
         * register.
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateCtrlRegAddr;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            HW_WR_FIELD32(addr, PMHAL_PWRSTCTRL_POWERSTATE, pdState);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID;
        }
    }
    /* Once the power state is programmed based on the time out provided check
     * if the power domain is able to reach the desired power state by reading
     * the power state status register.
     */
    if (timeout == PM_TIMEOUT_NOWAIT)
    {
        /* Will not wait for for the desired power domain mode */
        ;
    }
    else if (timeout == PM_TIMEOUT_INFINITE)
    {
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateStatusRegAddr;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            /* Wait infinitely for the power state to be set to the
             * desired mode.
             */
            do
            {
                pdStateCurr = (pmhalPrcmPdState_t) HW_RD_FIELD32(
                    addr,
                    PMHAL_PWRSTST_POWERSTATEST);
            } while (pdStateCurr != pdState);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID;
        }
    }
    else
    {
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateStatusRegAddr;
        timeToWait = timeout;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            /* Wait till timeout till the power domain is in the desired state.
             */
            do
            {
                pdStateCurr = (pmhalPrcmPdState_t) HW_RD_FIELD32(
                    addr,
                    PMHAL_PWRSTST_POWERSTATEST);

                timeToWait--;
            } while ((pdStateCurr != pdState) && (timeToWait != 0U));

            if (timeToWait == 0U)
            {
                retVal = PM_FAIL;
            }
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmGetConfiguredPDState(pmhalPrcmPdId_t     pdId,
                                     pmhalPrcmPdState_t *pdState)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (NULL != pdState)
    {
        retVal = PmhalPdmIsPDIdValid(pdId);
        /* Assigned here in case the power domain is not valid */
        *pdState = PMHAL_PRCM_PD_STATUS_COUNT;
    }
    else
    {
        retVal = PM_BADARGS;
    }

    if (PM_SUCCESS == retVal)
    {
        /* Read the configured power state PWRSTCTRL: POWERSTATE*/
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateCtrlRegAddr;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            *pdState = (pmhalPrcmPdState_t) HW_RD_FIELD32(
                addr,
                PMHAL_PWRSTCTRL_POWERSTATE);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmSetLogicRetState(pmhalPrcmPdId_t            pdId,
                                 pmhalPrcmPdLogicRetState_t logicState)
{
    pmErrCode_t retVal = PM_SUCCESS;

    retVal = PmhalPdmIsPDIdValid(pdId);

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalPdmIsLogicRetStateValid(pdId, logicState);
    }

    if (PM_SUCCESS == retVal)
    {
        /* Set the Logic state when power domain is RETENTION
         * 0x0: Only retention registers are retained and remaining
         *      logic is off when the domain is in RETENTION state.
         * 0x1: Whole logic is retained when domain is in RETENTION state.
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateCtrlRegAddr;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            HW_WR_FIELD32(addr, PMHAL_PWRSTCTRL_LOGICRETSTATE, logicState);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmGetConfiguredLogicRetState(
    pmhalPrcmPdId_t pdId,
    pmhalPrcmPdLogicRetState_t *
    logicState)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (NULL != logicState)
    {
        retVal = PmhalPdmIsPDIdValid(pdId);
        /* Assigned here in case the power domain is not valid */
        *logicState = PMHAL_PRCM_PD_RET_STATUS_COUNT;
    }
    else
    {
        retVal = PM_BADARGS;
    }

    if (PM_SUCCESS == retVal)
    {
        /* Get the configured Logic state when power domain is RETENTION
         * 0x0: Only retention registers are retained and remaining
         *      logic is off when the domain is in RETENTION state.
         * 0x1: Whole logic is retained when domain is in RETENTION state.
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateCtrlRegAddr;

        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            *logicState = (pmhalPrcmPdLogicRetState_t) HW_RD_FIELD32(
                addr,
                PMHAL_PWRSTCTRL_LOGICRETSTATE);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmSetLowPwrStateChange(
    pmhalPrcmPdId_t pdId,
    pmhalPrcmPdLowPwrStateChangeType_t
    lowPwrReq)
{
    pmErrCode_t retVal = PM_SUCCESS;

    retVal = PmhalPdmIsPDIdValid(pdId);

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalPdmIsLowPwrReqValid(pdId, lowPwrReq);
    }

    if (PM_SUCCESS == retVal)
    {
        /* Set the Power state change request when domain has already
         * performed a sleep transition. Allows going into deeper
         * low power state without waking up the power domain.
         * 0x0: Do not request a low power state change.
         * 0x1: Request a low power state change. This bit is
         *      automatically cleared when the power state is effectively
         *      changed or when power state is ON.
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateCtrlRegAddr;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            HW_WR_FIELD32(addr, PMHAL_PWRSTCTRL_LOWPOWERSTATECHANGE, lowPwrReq);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmGetConfiguredLowPwrStateChange(
    pmhalPrcmPdId_t pdId,
    pmhalPrcmPdLowPwrStateChangeType_t
                   *lowPwrReq)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (NULL != lowPwrReq)
    {
        retVal = PmhalPdmIsPDIdValid(pdId);
        /* Assigned here in case the power domain is not valid */
        *lowPwrReq = PMHAL_PRCM_PD_LOW_PWR_REQUEST_COUNT;
    }
    else
    {
        retVal = PM_BADARGS;
    }

    if (PM_SUCCESS == retVal)
    {
        /* Get the configured Power state change request when domain has already
         * performed a sleep transition.
         * 0x0: Do not request a low power state change.
         * 0x1: Request a low power state change.
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateCtrlRegAddr;

        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            *lowPwrReq = (pmhalPrcmPdLowPwrStateChangeType_t) HW_RD_FIELD32(
                addr,
                PMHAL_PWRSTCTRL_LOWPOWERSTATECHANGE);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmSetMemRetState(pmhalPrcmPdId_t         pdId,
                               pmhalPrcmPhyMemBankId_t memBankId,
                               pmhalPhyBankRetStates_t memoryRetState)
{
    pmErrCode_t retVal = PM_SUCCESS;

    retVal = PmhalPdmIsPDIdValid(pdId);

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalPdmIsMemBankIdValid(pdId, memBankId);
    }

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalPdmIsMemRetStateValid(memBankId, memoryRetState);
    }

    if (PM_SUCCESS == retVal)
    {
        /* Set the memory state when domain is RETENTION.
         * Should always be same as or higher than LogicRETState bit-field.
         * 0x0: Memory bank is off when the domain is in the
         *      RETENTION state.
         * 0x1: Memory bank is retained when domain is in RETENTION state.
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateCtrlRegAddr;
        uint32_t value;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            value = HW_RD_REG32(addr);

            value = value &
                    (~((uint32_t) 1U <<
                       pmhalPhysicalMemoryElems[memBankId].pwrRetStateCtrlShift));

            value = value |
                    (memoryRetState <<
                     pmhalPhysicalMemoryElems[memBankId].pwrRetStateCtrlShift);

            HW_WR_REG32(addr, value);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmGetConfiguredMemRetState(
    pmhalPrcmPdId_t          pdId,
    pmhalPrcmPhyMemBankId_t  memBankId,
    pmhalPhyBankRetStates_t *memoryRetState)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (NULL != memoryRetState)
    {
        retVal = PmhalPdmIsPDIdValid(pdId);
        /* Assigning a value in case the API fails */
        *memoryRetState = PMHAL_BANK_RET_UNDEF;
    }
    else
    {
        retVal = PM_BADARGS;
    }

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalPdmIsMemBankIdValid(pdId, memBankId);
    }

    if (PM_SUCCESS == retVal)
    {
        /* Get the configured   memory state when domain is RETENTION.
         * Should always be same as or higher than LogicRETState bit-field.
         * 0x0: Memory bank is off when the domain is in the
         *      RETENTION state.
         * 0x1: Memory bank is retained when domain is in RETENTION state.
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateCtrlRegAddr;
        uint32_t value;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            value           = HW_RD_REG32(addr);
            *memoryRetState = (pmhalPhyBankRetStates_t) ((value >>
                                                          pmhalPhysicalMemoryElems
                                                          [memBankId].
                                                          pwrRetStateCtrlShift)
                                                         &
                                                         (uint32_t) 1U);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmGetMemOnState(pmhalPrcmPdId_t         pdId,
                              pmhalPrcmPhyMemBankId_t memBankId,
                              uint32_t               *memOnState)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (NULL != memOnState)
    {
        retVal = PmhalPdmIsPDIdValid(pdId);
        /* Assigning a value in case the API fails */
        *memOnState = 0U;
    }
    else
    {
        retVal = PM_BADARGS;
    }

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalPdmIsMemBankIdValid(pdId, memBankId);
    }

    if (PM_SUCCESS == retVal)
    {
        /* Read the memory state when domain is ON.
         * 0x3: Memory bank is on when the domain is ON.
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateCtrlRegAddr;
        uint32_t value;

        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            value       = HW_RD_REG32(addr);
            *memOnState = (value >>
                           pmhalPhysicalMemoryElems[memBankId].
                           pwrOnStateCtrlShift) &
                          (uint32_t) 3U;
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_CTRL_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmGetCurrPDStatus(pmhalPrcmPdId_t     pdId,
                                pmhalPrcmPdState_t *pdState)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (NULL != pdState)
    {
        *pdState = PMHAL_PRCM_PD_STATUS_COUNT;
        retVal   = PmhalPdmIsPDIdValid(pdId);
    }
    else
    {
        retVal = PM_BADARGS;
    }

    if (PM_SUCCESS == retVal)
    {
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateStatusRegAddr;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            /* Read the Current power state status.
             * 0x0: Power domain is OFF
             * 0x1: Power domain is in RETENTION
             * 0x3: Power domain is ON-ACTIVE
             * 0x2: Power domain is ON-INACTIVE
             */
            *pdState = (pmhalPrcmPdState_t) HW_RD_FIELD32(
                addr,
                PMHAL_PWRSTST_POWERSTATEST);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmGetCurrLogicStatus(pmhalPrcmPdId_t pdId, uint32_t *logicOn)
{
    pmErrCode_t retVal = PM_SUCCESS;

    *logicOn = 0;

    retVal = PmhalPdmIsPDIdValid(pdId);

    if (PM_SUCCESS == retVal)
    {
        /* Read the Logic state status
         * 0x0: Logic in domain is OFF
         * 0x1: Logic in domain is ON
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateStatusRegAddr;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            *logicOn = HW_RD_FIELD32(addr, PMHAL_PWRSTST_LOGICSTATEST);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmGetCurrMemBankStatus(pmhalPrcmPdId_t         pdId,
                                     pmhalPrcmPhyMemBankId_t memBankId,
                                     pmhalPrcmPdState_t     *memBankState)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (NULL != memBankState)
    {
        retVal = PmhalPdmIsPDIdValid(pdId);
        /* Assigning a value in case the API fails */
        *memBankState = PMHAL_PRCM_PD_STATUS_COUNT;
    }
    else
    {
        retVal = PM_BADARGS;
    }

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalPdmIsMemBankIdValid(pdId, memBankId);
    }

    if (PM_SUCCESS == retVal)
    {
        /* Read the memory status in the power domain:
         * 0x0: Memory is OFF
         * 0x1: Memory is RETENTION
         * 0x3: Memory is ON
         * 0x2: Reserved
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateStatusRegAddr;
        uint32_t value;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            value         = HW_RD_REG32(addr);
            *memBankState = (pmhalPrcmPdState_t) ((value >>
                                                   pmhalPhysicalMemoryElems[
                                                       memBankId].
                                                   pwrStateStatusShift) &
                                                  (uint32_t) 3U);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmGetPDTransState(pmhalPrcmPdId_t pdId,
                                uint32_t       *pdInTransition)
{
    pmErrCode_t retVal = PM_SUCCESS;

    *pdInTransition = 0U;

    retVal = PmhalPdmIsPDIdValid(pdId);

    if (PM_SUCCESS == retVal)
    {
        /* Get the Domain transition status
         * 0x0: No on-going transition on power domain
         * 0x1: Power domain transition is in progress.
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateStatusRegAddr;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            *pdInTransition = HW_RD_FIELD32(addr, PMHAL_PWRSTST_INTRANSITION);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID;
        }
    }
    return retVal;
}

int32_t PMHALPdmSetLastPDStatus(pmhalPrcmPdId_t    pdId,
                                pmhalPrcmPdState_t pdState)
{
    pmErrCode_t retVal = PM_SUCCESS;

    retVal = PmhalPdmIsPDIdValid(pdId);

    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalPdmIsPowerStateValid(pdId, pdState);
    }

    if (PM_SUCCESS == retVal)
    {
        /* Configure the Last low power state entered. Set to 0x3 upon write of
         * the same only. This register is intended for debug
         * purpose only.
         * 0x0: Power domain was previously OFF
         * 0x1: Power domain was previously in RETENTION
         * 0x3: Power domain was previously ON-ACTIVE
         * 0x2: Power domain was previously ON-INACTIVE
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateStatusRegAddr;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            HW_WR_FIELD32(addr, PMHAL_PWRSTST_LASTPOWERSTATEENTERED, pdState);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

int32_t PMHALPdmGetLastPDStatus(pmhalPrcmPdId_t     pdId,
                                pmhalPrcmPdState_t *pdState)
{
    pmErrCode_t retVal = PM_SUCCESS;

    if (NULL != pdState)
    {
        *pdState = PMHAL_PRCM_PD_STATUS_COUNT;
        retVal   = PmhalPdmIsPDIdValid(pdId);
    }
    else
    {
        retVal = PM_BADARGS;
    }

    if (PM_SUCCESS == retVal)
    {
        /* Read the Last low power state entered.
         * 0x0: Power domain was previously OFF
         * 0x1: Power domain was previously in RETENTION
         * 0x3: Power domain was previously ON-ACTIVE
         * 0x2: Power domain was previously ON-INACTIVE
         */
        uint32_t addr = pmhalPowerDomainElems[pdId].pwrStateStatusRegAddr;
        if (addr != PMHAL_REG_NOTAPPLICABLE)
        {
            *pdState = (pmhalPrcmPdState_t) HW_RD_FIELD32(
                addr,
                PMHAL_PWRSTST_LASTPOWERSTATEENTERED);
        }
        else
        {
            retVal = PM_PDM_POWER_STATE_STATUS_REGISTER_NOT_VALID;
        }
    }

    return retVal;
}

pmhalPrcmResetGroupId_t PMHALPdmGetModuleResetId(pmhalPrcmPdId_t     pdId,
                                                 pmhalPrcmModuleId_t modIdx)
{
    pmErrCode_t retVal = PM_SUCCESS;
    pmhalPrcmResetGroupId_t resetId = PMHAL_PRCM_RG_COUNT;
    pmhalPrcmResetGroupId_t *resetIdList;
    pmhalPrcmResetGroupId_t currResetId;
    uint32_t    numResetDomain;
    uint32_t    count;
    retVal = PmhalPdmIsPDIdValid(pdId);
    if (PM_SUCCESS == retVal)
    {
        /* For the given module first find the power domain it belongs to.
         * Once the power domain is found then check if the reset ID has the
         * desired module listed as its subsystem reset.
         * We go from reset ID to module as the number of reset domains are
         * smaller than the number of modules.
         */
        resetIdList = pmhalPowerDomainElems[pdId].resetId;
        if (NULL != resetIdList)
        {
            numResetDomain =
                (uint32_t) pmhalPowerDomainElems[pdId].numResetDomain;
            for (count = 0U; count < numResetDomain; count++)
            {
                currResetId = resetIdList[count];
                /* Check if reset ID is programmable */
                if ((currResetId > PMHAL_PRCM_RG_LOWER_BOUND) &&
                    (currResetId < PMHAL_PRCM_RG_PROGRAMMABLE_RST_COUNT))
                {
                    if (modIdx ==
                        pmhalResetDomainElems[currResetId].toSubsystem)
                    {
                        resetId = resetIdList[count];
                        break;
                    }
                }
            }
        }
        else
        {
            resetId = PMHAL_PRCM_RG_COUNT;
        }
    }
    return resetId;
}

pmErrCode_t PMHALPdmGetCpuResetId(
    pmhalPrcmPdId_t         pdId,
    pmhalPrcmModuleId_t     modIdx,
    pmhalPrcmResetGroupId_t cpuResetId[PMHAL_PRCM_NUM_CPU_RESETS_FOR_SUBSYSTEM],
    uint32_t               *numResetsReturned)
{
    pmErrCode_t status = PM_SUCCESS;
    pmErrCode_t retVal = PM_SUCCESS;
    pmhalPrcmResetGroupId_t *resetIdList;
    pmhalPrcmResetGroupId_t currResetId;
    uint32_t    numResetDomain = 0U;
    uint32_t    count          = 0U;
    uint32_t    numResetFound  = 0U;
    retVal = PmhalPdmIsPDIdValid(pdId);

    if ((NULL == cpuResetId) || (NULL == numResetsReturned))
    {
        /* cpuResetId should not be NULL and must point to a valid array
         * Number of resets returned is filled in the numResetsReturned
         * parameter and hence cannot be NULL.
         */
        retVal = PM_BADARGS;
    }

    if (PM_SUCCESS == retVal)
    {
        /* Loop through all the resets belonging to a power domain and match
         * which reset goes to the desired module.
         */
        resetIdList = pmhalPowerDomainElems[pdId].resetId;
        if (NULL != resetIdList)
        {
            numResetDomain =
                (uint32_t) pmhalPowerDomainElems[pdId].numResetDomain;
            for (count = 0U; count < numResetDomain; count++)
            {
                currResetId = resetIdList[count];
                /* Check if reset ID is programmable */
                if ((currResetId > PMHAL_PRCM_RG_LOWER_BOUND) &&
                    (currResetId < PMHAL_PRCM_RG_PROGRAMMABLE_RST_COUNT))
                {
                    /* Here check if the reset which goes to a particular
                     * module is indeed the desired module.
                     */
                    if (modIdx == pmhalResetDomainElems[currResetId].toCpu)
                    {
                        if (PMHAL_PRCM_NUM_CPU_RESETS_FOR_SUBSYSTEM >
                            numResetFound)
                        {
                            cpuResetId[numResetFound] = resetIdList[count];
                            numResetFound++;
                        }
                        if (PMHAL_PRCM_NUM_CPU_RESETS_FOR_SUBSYSTEM ==
                            numResetFound)
                        {
                            /* If all the resets to a CPU subsystem is found
                             * break out of the search loop.
                             */
                            break;
                        }
                    }
                }
            }
        }
        /* If no CPU resets are found the returned array is properly filled
         * with an invalid reset group ID.
         */
        if (PMHAL_PRCM_NUM_CPU_RESETS_FOR_SUBSYSTEM > numResetFound)
        {
            /* If only few resets are found out of the max possible, fill the
             * rest with an invalid Reset ID.
             */
            for (count = numResetFound;
                 count < PMHAL_PRCM_NUM_CPU_RESETS_FOR_SUBSYSTEM;
                 count++)
            {
                cpuResetId[count] = PMHAL_PRCM_RG_COUNT;
            }
        }
        /* Capture the number of resets found to be used by the application
         * to reset the given CPU subsystem.
         */
        *numResetsReturned = numResetFound;
    }
    return status;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static pmErrCode_t PmhalPdmIsPDIdValid(pmhalPrcmPdId_t pdId)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    if ((pdId <= PMHAL_PRCM_PD_LOWER_BOUND) || (pdId >= PMHAL_PRCM_PD_COUNT))
    {
        retVal = PM_INPUT_PARAM_BAD_POWER_DOMAIN_ID;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
#else
    return PM_SUCCESS;
#endif
}

static pmErrCode_t PmhalPdmIsPowerStateValid(pmhalPrcmPdId_t    pdId,
                                             pmhalPrcmPdState_t pdState)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    /* Power state which are valid for a given PD are encoded
     * as a one hot encoding. Based on the given power state the bit
     * position is checked to see if the power state is supported.
     */
    uint32_t    compareVal = (uint32_t) ((uint32_t) 1U << (uint32_t) pdState);
    uint32_t    validVal   = pmhalPowerDomainElems[pdId].validPwrStates;

    if ((compareVal & validVal) != 0U)
    {
        retVal = PM_SUCCESS;
    }
    else
    {
        retVal = PM_PDM_PDSTATE_NOT_SUPPORTED;
    }
    return retVal;
#else
    return PM_SUCCESS;
#endif
}

static pmErrCode_t PmhalPdmIsLogicRetStateValid(
    pmhalPrcmPdId_t            pdId,
    pmhalPrcmPdLogicRetState_t logicState)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    /* Logic state which are valid for a given PD are encoded
     * as a one hot encoding. Based on the given Logic state the bit
     * position is checked to see if the Logic state is supported.
     */
    uint32_t    compareVal = (uint32_t) ((uint32_t) 1U << (uint32_t) logicState);
    uint32_t    validVal   = pmhalPowerDomainElems[pdId].validLogicRetState;

    if ((compareVal & validVal) != 0U)
    {
        retVal = PM_SUCCESS;
    }
    else
    {
        retVal = PM_PDM_LOGIC_RET_STATE_NOT_SUPPORTED;
    }
    return retVal;
#else
    return PM_SUCCESS;
#endif
}

static pmErrCode_t PmhalPdmIsLowPwrReqValid(
    pmhalPrcmPdId_t pdId,
    pmhalPrcmPdLowPwrStateChangeType_t
    lowPwrReq)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    /* Low power request state which are valid for a given PD are encoded
     * as a one hot encoding. Based on the given Low power request state the bit
     * position is checked to see if the Low power request state is supported.
     */
    uint32_t    compareVal = (uint32_t) ((uint32_t) 1U << (uint32_t) lowPwrReq);
    uint32_t    validVal   = pmhalPowerDomainElems[pdId].validLowPwrRequest;

    if ((compareVal & validVal) != 0U)
    {
        retVal = PM_SUCCESS;
    }
    else
    {
        retVal = PM_PDM_LOW_POWER_REQUEST_NOT_SUPPORTED;
    }
    return retVal;
#else
    return PM_SUCCESS;
#endif
}

static pmErrCode_t PmhalPdmIsMemBankIdValid(pmhalPrcmPdId_t         pdId,
                                            pmhalPrcmPhyMemBankId_t memBankId)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal = PM_SUCCESS;
    const pmhalPowerDomain_t *pwrDomPtr = &pmhalPowerDomainElems[pdId];
    uint32_t    memCount         = pwrDomPtr->numMemoryModules;
    pmhalPrcmPhyMemBankId_t *ptr = pwrDomPtr->phyMemoryBankId;
    uint32_t    i;

    if (memBankId > PMHAL_PRCM_PHY_BANK_MAX)
    {
        retVal = PM_INPUT_PARAM_BAD_PHYSICAL_MEMORY_ID;
    }

    if (PM_SUCCESS == retVal)
    {
        /* Check if the memory bank belongs to the given power domain */
        for (i = 0U; i < memCount; i++)
        {
            if (memBankId == *(ptr + i))
            {
                break;
            }
        }

        if (i == memCount)
        {
            retVal = PM_INPUT_PARAM_BAD_PHYSICAL_MEMORY_ID;
        }
    }

    return retVal;
#else
    return PM_SUCCESS;
#endif
}

pmErrCode_t PmhalPdmIsMemRetStateValid(pmhalPrcmPhyMemBankId_t memBankId,
                                       uint32_t                memoryRetState)
{
#if !defined (PM_OPTIMIZE)
    /* Assume Inputs are correct when optimization enabled */
    pmErrCode_t retVal;
    /* Memory Retention state which are valid for a given PD are encoded
     * as a one hot encoding. Based on the given Memory Retention state the bit
     * position is checked to see if the Memory Retention state is supported.
     */
    uint32_t    value        = ((uint32_t) 1U << memoryRetState);
    int32_t     compareValue =
        pmhalPhysicalMemoryElems[memBankId].pwrRetStateModes;

    if (PMHAL_BANK_RET_UNDEF != compareValue)
    {
        if ((value & pmhalPhysicalMemoryElems[memBankId].pwrRetStateModes) !=
            0U)
        {
            retVal = PM_SUCCESS;
        }
        else
        {
            retVal = PM_PDM_MEM_RET_STATE_NOT_SUPPORTED;
        }
    }
    else
    {
        retVal = PM_PDM_MEM_RET_STATE_NOT_SUPPORTED;
    }

    return retVal;
#else
    return PM_SUCCESS;
#endif
}

