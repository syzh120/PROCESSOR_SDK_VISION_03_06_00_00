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
 *  \ingroup PM_HAL PM HAL API
 *  \defgroup PM_HAL_VM Voltage Configuration
 *  The Voltage Manager (VM) is an important component of the Power Management
 *  (PM) software which helps set and read back the voltage on the voltage rails
 *  of the System on Chip (SoC).
 *  The VM works closely with Power Management IC (PMIC) software
 *  Hardware Abstraction Layer (HAL).
 *  The VM provides support for the PMIC
 *  - One Time Programmed (OTP) boot voltage,
 *  - Automatic Voltage Scaling (AVS)/ Smart Reflex Class 0 and
 *    Adaptive Body Bias (ABB).
 *
 * @{
 */

/**
 *  \file  pmhal_vm.h
 *
 *  \brief This file contains the Voltage Manager API.
 *         This API supports OPP Voltage changes for all the voltage
 *         domains.
 */

#ifndef PMHAL_VM_H_
#define PMHAL_VM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/pm/include/prcm/pmhal_prcm.h>

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

/* None */

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief           Change the device OPP to the given OPP for a given voltage
 *                  domain.
 *
 * \note            It is the caller's responsibility to ensure that
 *                  the frequency of the modules in the given voltage domain
 *                  are valid for the OPP before calling this function.
 *
 * \param voltDomId     Voltage domain ID of the targetted voltage domain.
 *                      Refer Enum #pmhalPrcmVdId_t
 * \param oppId         Operating point ID to which the given Voltage domain
 *                      should change to.
 *                      Refer Enum #pmhalVmOppId_t
 * \param   timeout     Timeout iterations to wait for setting the right
 *                      regulator voltage value. Possible values can be:
 *                     - #PM_TIMEOUT_NOWAIT   Do not wait for voltage setting.
 *                     - #PM_TIMEOUT_INFINITE Wait infinitely till the voltage
 *                                          is set.
 *                      Non Zero Value      Wait for the time provided by the
 *                                          user.
 *
 * \return          Status of the OPP change.
 *                 - #PM_SUCCESS       Indicates the operation is success.
 *                 - #PM_TIMEOUT       Indicates PmVoltageDisableABB has
 *                                   timed out.
 *                 - #PM_BADARGS       Invalid voltage id or opp id.
 *
 **/
pmErrCode_t PMHALVMSetOpp(pmhalPrcmVdId_t voltDomId,
                          pmhalVmOppId_t  oppId,
                          uint32_t        timeout);

/**
 * \brief           Wrapper function to get the current voltage setting of
 *                  voltage rail for the given voltage domain. This is
 *                  NOT necessarily the VD voltage as this doesn't account
 *                  for ABB LDO and the PMIC variations.
 *
 * \param voltDomId Voltage domain ID of the voltage domain requested.
 *                  Refer Enum #pmhalPrcmVdId_t
 * \param voltage   Voltage in mV is populated to this argument.
 *                  Populated with 0 in case of any error condition.
 *
 * \return           Status of the API call.
 *                  Can be any of the following:
 *                 - #PM_SUCCESS  Indicates the operation is success.
 *                 - #PM_BADARGS  Invalid voltage id or pointer to
 *                              voltage is NULL.
 **/
pmErrCode_t PMHALVMGetCurrentVoltage(pmhalPrcmVdId_t voltDomId,
                                     uint32_t       *voltage);

/**
 * \brief  Get the current OPP for the given voltage domain.
 *
 * \note This function is good at finding the OPP if the VM API is used
 *       to set the OPP. Otherwise, it will make a best effort to find
 *       the OPP.
 *
 * \param   voltDomId   Voltage domain ID of the voltage domain requested.
 *                      Refer Enum #pmhalPrcmVdId_t
 * \param   oppId       OPP ID is populated in this argument with the current
 *                      OPP ID. Refer Enum #pmhalVmOppId_t
 *
 * \return  retVal  Status of the API call.
 *                         Can be any of the following,
 *                 - #PM_SUCCESS      Indicates the operation is success.
 *                 - #PM_BADARGS      Invalid voltage id or pointer to
 *                                  voltage is NULL.
 **/
pmErrCode_t PMHALVMGetCurrentOpp(pmhalPrcmVdId_t voltDomId,
                                 pmhalVmOppId_t *oppId);

/**
 * \brief  Initialize ABB
 *
 *     The following ABB initialization steps are required to use ABB:
 *     1. Set up the WTCNT value (see PmhalVmGetWtCnt() for details)
 *     2. Set PRM_ABBLDO_<VD>_SETUP.SR2EN to 1
 *     3. Initialize PRM_ABBLDO_<VD>_SETUP.ACTIVE_FBB_SEL to 0. This will
 *        be programmed as needed by the OPP change.
 *     4. Ensure PRM_ABBLDO_<VD>_SETUP.NOCAP is unchanged from reset value.
 *        This value is automatically loaded.
 *     5. Ensure all other bits are zero.
 *
 * \param voltDomId Voltage domain ID of the targetted voltage domain.
 *                  Refer Enum #pmhalPrcmVdId_t
 *
 * \param  oppId     OPP Voltage structure
 *
 * \return None
 */
void PMHALVMInitABB(pmhalPrcmVdId_t voltDomId,
                    pmhalVmOppId_t  oppId);

/**
 * \brief  Enable ABB for the given (VD, OPP) pair.
 *
 * \param voltDomId Voltage domain ID of the targetted voltage domain.
 *                  Refer Enum #pmhalPrcmVdId_t
 * \param oppId     Operating point ID to which the given Voltage domain
 *                  should change to.
 *                  Refer Enum #pmhalVmOppId_t
 *
 * \return          Indicates if the ABB has been enabled
 *                - #PM_TIMEOUT - If the setting of ABB times out
 *                - #PM_BADARGS - If the opp given is NULL
 *                - #PM_SUCCESS - If the ABB is enabled successfully
 */
pmErrCode_t PMHALVMEnableABB(pmhalPrcmVdId_t voltDomId,
                             pmhalVmOppId_t  oppId);

/**
 * \brief  Disable ABB for the given OPP
 *
 * \param voltDomId Voltage domain ID of the targetted voltage domain.
 *                  Refer Enum #pmhalPrcmVdId_t
 * \param oppId     Operating point ID to which the given Voltage domain
 *                  should change to.
 *                  Refer Enum #pmhalVmOppId_t
 *
 * \return         Indicates if the ABB has been disabled
 *               - #PM_TIMEOUT - If the setting of ABB times out
 *               - #PM_BADARGS - If the opp given is NULL
 *               - #PM_SUCCESS - If the ABB is disabled successfully
 */
pmErrCode_t PMHALVMDisableABB(pmhalPrcmVdId_t voltDomId,
                              pmhalVmOppId_t  oppId);

/**
 * \brief  Get the AVS Class-0 voltage in micro Volts.
 *
 * \param voltDomId Voltage domain ID of the targetted voltage domain.
 *                  Refer Enum #pmhalPrcmVdId_t
 * \param oppId     Operating point ID to which the given Voltage domain
 *                  should change to.
 *                  Refer Enum #pmhalVmOppId_t
 *
 * \return  voltage         Voltage is returned in mV.
 *                          Zero is returned if AVS is not supported for the
 *                          given OPP.
 */
uint32_t PMHALVMGetAVS0EfuseVoltage(pmhalPrcmVdId_t voltDomId,
                                    pmhalVmOppId_t  oppId);

/**
 * \brief  Check if the ABB is enabled for a given OPP.
 *
 * \param voltDomId Voltage domain ID of the targetted voltage domain.
 *                  Refer Enum #pmhalPrcmVdId_t
 * \param oppId     Operating point ID to which the given Voltage domain
 *                  should change to.
 *                  Refer Enum #pmhalVmOppId_t
 *
 * \return               Check for whether ABB is enabled
 *                      1         if ABB is enabled
 *                      0        otherwise.
 */
uint32_t PMHALVMIsABBEnabled(pmhalPrcmVdId_t voltDomId,
                             pmhalVmOppId_t  oppId);

/**
 * \brief  Set the desired SRAM LDO retention state for a given voltage domain.
 *
 * \param voltDomId Voltage domain ID of the targeted voltage domain.
 *                  Refer Enum #pmhalPrcmVdId_t
 * \param retState  Desired retention state for SRAM LDO.
 *                  Refer Enum #pmhalPrcmSramLdoRetState_t
 *
 * \return           Indicates if the Ret state has been set correctly.
 *                 - #PM_BADARGS - If the voltage domain does not support the
 *                               retention state.
 *                 - #PM_SUCCESS - If the retention state is set successfully.
 */
uint32_t PMHALVMSetSramLdoRetState(pmhalPrcmVdId_t            voltDomId,
                                   pmhalPrcmSramLdoRetState_t retState);

/**
 * \brief  Get the SRAM LDO transition state for a given voltage domain.
 *
 * \param voltDomId   Voltage domain ID of the targeted voltage domain.
 *                    Refer Enum #pmhalPrcmVdId_t
 * \param transState  Read transition state for SRAM LDO.
 *                    Refer Enum #pmhalPrcmSramLdoTransState_t
 *
 * \return           Indicates if the Transition state has been read correctly.
 *                 - #PM_SUCCESS - If the transition state is read correctly.
 *                 - #PM_BADARGS - Otherwise
 */
uint32_t PMHALVMGetSramLdoTransState(pmhalPrcmVdId_t               voltDomId,
                                     pmhalPrcmSramLdoTransState_t *transState);

/**
 * \brief  Get the desired SRAM LDO power state for a given voltage domain.
 *
 * \param voltDomId  Voltage domain ID of the targeted voltage domain.
 *                   Refer Enum #pmhalPrcmVdId_t
 * \param ldoStatus  Read status for SRAM LDO.
 *                   Refer Enum #pmhalPrcmSramLdoStatus_t
 *
 * \return           Indicates if the SRAM LDO status is read correctly.
 *                 - #PM_SUCCESS - If the SRAM LDO status is read correctly.
 *                 - #PM_BADARGS - Otherwise
 */
uint32_t PMHALVMGetSramLdoStatus(pmhalPrcmVdId_t           voltDomId,
                                 pmhalPrcmSramLdoStatus_t *ldoStatus);

/**
 * \brief  Set the desired SRAM LDO Setup register for a given voltage domain.
 *         This API performs a write and not a read modify write to the register
 *         Use this in combination with PMHALVMGetSramLdoSetup for a read
 *         modify write operation.
 *
 * \param voltDomId  Voltage domain ID of the targeted voltage domain.
 *                   Refer Enum #pmhalPrcmVdId_t
 * \param setupVal   Value to be written into SRAM LDO Setup register.
 *                   Refer Enum #pmhalPrcmSramSetupBitFields_t for valid bit
 *                   fields.
 *
 * \return           Indicates if the SRAM LDO setup register is written
 *                  correctly. Valid values are:
 *                 - #PM_SUCCESS - If the setup register is written correctly.
 *                 - #PM_BADARGS - Otherwise
 */
uint32_t PMHALVMSetSramLdoSetup(pmhalPrcmVdId_t voltDomId,
                                uint32_t        setupVal);

/**
 * \brief  Get the desired SRAM LDO Setup register for a given voltage domain.
 *
 * \param voltDomId  Voltage domain ID of the targeted voltage domain.
 *                   Refer Enum #pmhalPrcmVdId_t
 * \param setupVal   Value to be read from SRAM LDO Setup register.
 *                   Refer Enum #pmhalPrcmSramSetupBitFields_t for valid bit
 *                   fields.
 *
 * \return           Indicates if the SRAM LDO setup register is read correctly.
 *                 - #PM_SUCCESS - If the setup register is read correctly.
 *                 - #PM_BADARGS - Otherwise
 */
uint32_t PMHALVMGetSramLdoSetup(pmhalPrcmVdId_t voltDomId,
                                uint32_t       *setupVal);

/**
 * \brief  Get the dependent CPU for the given CPUID.A CPU is said to be
 *         dependent on another CPU if they are present in the same
 *         Voltage Domain
 *
 * \param  cpuId        ID which identifies a module as a CPU.
 *                      Refer #pmhalPrcmCpuId_t enum for valid values.
 *
 * \param  depCpuId     ID which identifies a module as a CPU,
 *                      which is dependent on cpuId.
 *                      Refer #pmhalPrcmCpuId_t enum for valid values.
 *
 * \return status       CPUID of the dependent CPU. Refer #pmhalPrcmCpuId_t
 *                      enum for valid values.
 *                      Fails if cpuID is not valid.
 */
pmErrCode_t PMHALVMGetDepCpuId(pmhalPrcmCpuId_t  cpuId,
                               pmhalPrcmCpuId_t *depCpuId);

/**
 * \brief  Get the voltage value that should be programmed for a given voltage
 *         rail for a given OPP.
 *
 * \param  voltDomId   Voltage Domain ID for which the OPP voltage value needs
 *                     to be found. Refer #pmhalPrcmVdId_t enum for valid
 *                     values.
 * \param  oppId       Opp ID for which the voltage needs to be found. Refer
 *                     #pmhalVmOppId_t enum for valid values.
 * \param  voltage     Voltage values is returned in this variable.
 *
 * \return status     - #PM_SUCCESS When the voltage value is returned
 *                      correctly.
 *                    - #PM_BADARGS When the voltage and OPP are not valid.
 */
pmErrCode_t PMHALVMGetVoltageForOpp(pmhalPrcmVdId_t voltDomId,
                                    pmhalVmOppId_t  oppId,
                                    uint32_t       *voltage);

/**
 * \brief  Get the list of CPUs which belong to the given voltage domain.
 *
 * \param  voltDomId   Voltage Domain ID for which the OPP voltage value needs
 *                     to be found. Refer #pmhalPrcmVdId_t enum for valid
 *                     values.
 * \param  cpuIdArray  Pointer to the CPU ID array is returned.
 * \param  numCpus     Number of CPUs in the voltage domain is returned.
 *
 * \return status    - #PM_SUCCESS When the voltage value is returned correctly.
 *                   - #PM_BADARGS When the voltage ID is not valid.
 */
pmErrCode_t PMHALVMGetCpuInVoltageDomain(pmhalPrcmVdId_t    voltDomId,
                                         pmhalPrcmCpuId_t **cpuIdArray,
                                         uint32_t          *numCpus);

#ifdef __cplusplus
}
#endif

#endif

/* @} */

