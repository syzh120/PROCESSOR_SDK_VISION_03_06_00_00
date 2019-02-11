/*
 *  Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \ingroup CSL_ARCH_C66X
 *  \defgroup CSL_ARCH_C66X_ECC ECC
 *
 *  @{
 */
/**
 *  \file   dsp_ecc.h
 *
 *  \brief  ECC API declarations for DSP Internal memory (L1P and L2) ECC
 *
 *   This file contains the API prototypes for DSP Internal memory (L1P and L2)
 *   ECC.
 */

#ifndef DSP_ECC_H_
#define DSP_ECC_H_

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/

/** \brief Macro to Enable ECC */
#define ECC_ENABLE                 (0x1U)
/** \brief Macro to DISABLE ECC */
#define ECC_DISABLE                (0x0U)

/**
 *  \brief    Enumerates the values used to represent DSP ECC Memory types
 */
typedef enum eccDspMemType
{
    ECC_DSP_MEM_TYPE_L2 = 0x1U,
    /**<  DSP L2 RAM/Cache ECC Memory Type*/
    ECC_DSP_MEM_TYPE_L1P = 0x2U,
    /**<  DSP L1P RAM/Cache ECC Memory Type*/
    ECC_DSP_MEM_TYPE_L1D = 0x3U
                           /**<  DSP L1D RAM/Cache ECC Memory Type*/

} eccDspMemType_t;

/*****************************************************************************
**                     STRUCTURE DEFINITIONS
*****************************************************************************/

/** \brief Structure holding ECC configuration parameters of DSP L2 EDC
 */
typedef struct eccDspL2CfgPrm
{
    uint32_t l1DCacheReadEccEn;
    /**< 1: Enables EDC on L1D memory controller reads from an external
     *      address (Hits L2 cache) if L2EDCMD.EN = 1.
     *   0: Disables EDC on L1D memory controller reads from an external
     *      address (Hits L2 cache)
     */
    uint32_t l1PCacheReadEccEn;
    /**< 0: Disables EDC on L1P memory controller reads from an external
     *      address (Hits L2 cache)
     *   1: Enables EDC on L1P memory controller reads from an external
     *      address (Hits L2 cache) if L2EDCMD.EN = 1
     */
    uint32_t l1DRamReadEccEn;
    /**< 0: Disables EDC on L1D memory controller read from L2 RAM
     *   1: Enables EDC on L1D memory controller read from L2 RAM
     *      (if L2EDCMD.EN = 1)
     */
    uint32_t l1PRamReadEccEn;
    /**< 0: Disables EDC on L1P memory controller read from L2 RAM
     *   1: Enables EDC on L1P memory controller read from L2 RAM (
     *      if L2EDCMD.EN = 1)
     */
    uint32_t sdmaReadEccEn;
    /**< 0: Disables EDC on SDMA read from L2 RAM
     *   1: Enables EDC on SDMA read from L2 RAM (if L2EDCMD.EN = 1).
     *   This includes RAM under cache.
     */
} eccDspL2CfgPrm_t;

/** \brief Structure holding DSP ECC Error status.
 */
typedef struct eccDspErrStatus
{
    uint32_t l1PProgramFetchErr;
    /**< L1P Mem: A program fetch resulted in a parity check error */
    uint32_t l1PDmaAccessErr;
    /**< L1P Mem: A DMA/IDMA access to L1P memory resulted in a parity
     *            check error.
     */
    uint32_t l2L1DAccessErr;
    /**< L2 Mem: Parity error occurred during L1D data access */
    uint32_t l2L1PAccessErr;
    /**< L2 Mem: Parity error occurred during L1P access */
    uint32_t l2DmaAccessErr;
    /**< L2 Mem: Parity error occurred during DMA access */
    uint32_t l2VictimsErr;
    /**< L2 Mem: Parity error occurred on L2 victims */
    uint32_t l1DDataCorrectableError;
    /**< L1D Mem: correctable error occurred on L1D data memory */
    uint32_t l1DDataNonCorrectableError;
    /**< L1D Mem: non correctable error occurred on L1D data memory */
    uint32_t l1DTagCorrectableError;
    /**< L1D Mem: correctable error occurred on L1D tag memory */
    uint32_t l1DTagNonCorrectableError;
    /**< L1D Mem: non correctable error occurred on L1D tag memory */
    uint32_t l2TagCorrectableError;
    /**< L2T Mem: correctable error occurred on L2 tag memory */
    uint32_t l2TagNonCorrectableError;
    /**< L2T Mem: non correctable error occurred on L2 tag memory */
    uint32_t l1PTagNonCorrectableError;
    /**< L1P Mem: non correctable error occurred on L1P tag memory */
} eccDspErrStatus_t;

/** \brief Structure holding the DSP ECC Error Information.
 */
typedef struct eccDspErrInfo
{
    uint32_t errAddress;
    /**< L1P and L2: Contains the upper 27 bit of error location. */
    uint32_t errRamOrCache;
    /**< L1P and L2: 0: Error detected in L1P/L2 cache
     *               1: Error detected in L1P/L2 RAM
     */
    uint32_t errL2BitPosition;
    /**< L2 only:   0: Bit Position = 0
     *              1: Bit Position = 1
     *              ...
     *              255: Bit Position = 255
     *   L1P : Value returned is always 0
     */
    uint32_t errL2Type;
    /**< L2 Only :   0: Single Bit Error
     *               1: Double Bit Error
     *               3: Error in parity value, data is correct
     *               2: Reserved
     *   L1P : Value returned is always 0
     */
    uint32_t errL2way;
    /**< L2 Only :
     *               00: Error detected in Way 0 of L2 cache
     *               01: Error detected in Way 1 of L2 cache
     *               10: Error detected in Way 2 of L2 cache
     *               11: Error detected in Way 3 of L2 cache
     *               (Note: L2WAY = 00 when RAM = 1)
     *   L1P : Value returned is always 0
     */
    uint32_t errL2CorrectableCount;
    /**< Correctable Parity Error Count */
    uint32_t errL2NonCorrectableCount;
    /**< Non-Correctable Parity Error count */
} eccDspErrInfo_t;

/** \brief Structure holding the L1D DSP ECC Error Information.
 */
typedef struct eccDspL1DErrInfo
{
    uint32_t dataCErrStat;
    /**< L1D: Correctable Data error status.
     *        1: Single correctable data ecc error occured.
     *        2: multiple correctable data ecc error occured.
     */
    uint32_t dataCErrAddr;
    /**< L1D: Address of correctable data ecc error. */
    uint32_t dataCErrBitPos;
    /**< L1D: bit position of correctable data ecc error. */
    uint32_t dataCErrByte;
    /**< L1D: byte of correctable data ecc error. */
    uint32_t dataCErrBank;
    /**< L1D: bank of correctable data ecc error. */

    uint32_t dataNCErrStat;
    /**< L1D: Non Correctable Data error status.
     *        1: Single non correctable data ecc error occured.
     *        2: multiple non correctable data ecc error occured.
     */
    uint32_t dataNCErrAddr;
        /**< L1D: Address of non correctable data ecc error. */
    uint32_t dataNCErrByte;
    /**< L1D: byte of non correctable data ecc error. */
    uint32_t dataNCErrBank;
    /**< L1D: bank of non correctable data ecc error. */

    uint32_t tagCErrStat;
    /**< L1D: Correctable Tag error status.
     *        1: Single correctable tag ecc error occured.
     *        2: multiple correctable tag ecc error occured.
     */
    uint32_t tagCErrAddr;
    /**< L1D: Address of correctable tag ecc error. */
    uint32_t tagCErrBitPos;
    /**< L1D: bit position of correctable tag ecc error. */
    uint32_t tagCErrChan;
    /**< L1D: channel of correctable tag ecc error. */
    uint32_t tagCErrBank;
    /**< L1D: bank of correctable tag ecc error. */

    uint32_t tagNCErrStat;
    /**< L1D: non Correctable Tag error status.
     *        1: Single non correctable tag ecc error occured.
     *        2: multiple non correctable tag ecc error occured.
     */
    uint32_t tagNCErrAddr;
    /**< L1D: Address of non correctable tag ecc error. */
    uint32_t tagNCErrChan;
    /**< L1D: channel of non correctable tag ecc error. */
    uint32_t tagNCErrBank;
    /**< L1D: bank of non correctable tag ecc error. */
} eccDspL1DErrInfo_t;

/** \brief Structure holding the L2 Tag DSP ECC Error Information.
 */
typedef struct eccDspL2TagErrInfo
{
    uint32_t tagCErrStat;
    /**< L2T: Correctable Tag error status.
     *        1: Single correctable tag ecc error occured.
     *        2: multiple correctable tag ecc error occured.
     */
    uint32_t tagCErrAddr;
    /**< L2T: Address of correctable tag ecc error. */
    uint32_t tagCErrBitPos;
    /**< L2T: bit position of correctable tag ecc error. */
    uint32_t tagCErrChan;
    /**< L2T: channel of correctable tag ecc error. */
    uint32_t tagCErrBank;
    /**< L2T: bank of correctable tag ecc error. */

    uint32_t tagNCErrStat;
    /**< L2T: non Correctable Tag error status.
     *        1: Single non correctable tag ecc error occured.
     *        2: multiple non correctable tag ecc error occured.
     */
    uint32_t tagNCErrAddr;
    /**< L2T: Address of non correctable tag ecc error. */
    uint32_t tagNCErrBank;
    /**< L2T: bank of non correctable tag ecc error. */
} eccDspL2TagErrInfo_t;

/** \brief Structure holding the L1D DSP ECC Error Information.
 */
typedef struct eccDspL1PTagErrInfo
{
    uint32_t tagNCErrStat;
    /**< L1P: non Correctable Tag error status.
     *        1: Single non correctable tag ecc error occured.
     *        2: multiple non correctable tag ecc error occured.
     */
    uint32_t tagNCErrAddr;
    /**< L1P: Address of non correctable tag ecc error. */
} eccDspL1PTagErrInfo_t;

/*****************************************************************************
**                     API FUNCTION PROTOTYPES
*****************************************************************************/

/**
 * \brief   This function initializes the software structure to configure the
 *          DSP L2 ECC L2EDCEN register.
 *
 * \param   eccDspL2Param   Pointer to the structure to hold the L2 EDC/ECC
 *                          configuration. Refer #eccDspL2CfgPrm_t for details
 *                          on the structure fields.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspL2CfgPrm_init(eccDspL2CfgPrm_t *eccDspL2Param);

/**
 * \brief   This function configures the DSP L2 ECC L2EDCEN register. The
 *          function to initialize the structure is #ECCDspL2CfgPrm_init.
 *
 * \param   eccDspL2Param   Pointer to the structure to hold the L2 ECC/EDC
 *                          configuration. Refer #eccDspL2CfgPrm_t for details
 *                          on the structure.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspL2Configure(const eccDspL2CfgPrm_t *eccDspL2Param);

/**
 * \brief   This function enables or disables EDC/ECC for L1P or L2 DSP
 *          memories.
 *
 * \param   memType         DSP ECC memory type. This parameter can take any of
 *                          following values:
 *                          ECC_DSP_MEM_TYPE_L2  - DSP L2 ECC/EDC
 *                          ECC_DSP_MEM_TYPE_L1P - DSP L1P ECC/EDC
 * \param   eccEnable       Flag to indicate whether to enable or disable
 *                          EDC/ECC. It can take any of the two values:
 *                          ECC_ENABLE - To enable EDC/ECC
 *                          ECC_DISABLE - To disable EDC/ECC
 * \param   timeout         Time to wait for the ECC/EDC to get ENABLED/DISABLED
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspEnable(uint32_t memType, uint32_t eccEnable, uint32_t timeout);
/**
 * \brief   This function suspends the EDC/ECC for L1P or L2 DSP
 *          memories.
 *
 * \param   memType         DSP ECC memory type. This parameter can take any of
 *                          following values:
 *                          ECC_DSP_MEM_TYPE_L2  - DSP L2 ECC/EDC
 *                          ECC_DSP_MEM_TYPE_L1P - DSP L1P ECC/EDC
 * \param   timeout         Time to wait for the ECC/EDC to get SUSPENDED
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspSuspend(uint32_t memType, uint32_t timeout);

/**
 * \brief   This function reads the error status of both L1P and L2 EDC/ECC.
 *
 * \param   errStatus       Holds the values of which error got set. Refer
 *                          #eccDspErrStatus_t for more details. If the value
 *                          of any field is read as 1 the corresponding ECC
 *                          error has occurred.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspIntrGetErrStatus(eccDspErrStatus_t *errStatus);

/**
 * \brief   This function clears the error status of both L1P and L2 EDC/ECC.
 *
 * \param   errClr          Holds the values of which error need to be cleared.
 *                          Refer #eccDspErrStatus_t for more details.
 *                          A value of 1 is written to fields that need to be
 *                          cleared and 0 for those that need not be cleared.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspIntrClrErrStatus(const eccDspErrStatus_t *errClr);

/**
 * \brief   This function reads the details of the ECC errors for a particular
 *          DSP memory.
 *
 * \param   memType         DSP ECC memory type. This parameter can take any of
 *                          following values:
 *                          ECC_DSP_MEM_TYPE_L2  - DSP L2 ECC/EDC
 *                          ECC_DSP_MEM_TYPE_L1P - DSP L1P ECC/EDC
 * \param   eccDspInfo      Structure to hold the details of the ECC/EDC error
 *                          generated at L1P or L2. Refer #eccDspErrInfo_t for
 *                          which fields apply to L1P and which to L2 and their
 *                          meaning.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspGetErrInfo(uint32_t memType, eccDspErrInfo_t *eccDspInfo);

/**
 * \brief   This function reads the details of the L1D ECC errors.
 *
 * \param   eccDspInfo      Structure to hold the details of the ECC/EDC error
 *                          generated at L1D. Refer #eccDspL1DErrInfo_t for
 *                          the field details.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspGetL1DErrInfo(eccDspL1DErrInfo_t *eccDspInfo);

/**
 * \brief   This function reads the details of the L2 Tag ECC errors.
 *
 * \param   eccDspInfo      Structure to hold the details of the ECC/EDC error
 *                          generated at L2 Tag. Refer #eccDspL2TagErrInfo_t
 *                          for the field details.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspGetL2TagErrInfo(eccDspL2TagErrInfo_t *eccDspInfo);

/**
 * \brief   This function reads the details of the L1P ECC errors.
 *
 * \param   eccDspInfo      Structure to hold the details of the ECC/EDC error
 *                          generated at L1P Tag. Refer #eccDspL1PTagErrInfo_t
 *                          for the field details.
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCDspGetL1PTagErrInfo(eccDspL1PTagErrInfo_t *eccDspInfo);

#ifdef __cplusplus
}
#endif
#endif /* #ifndef DSP_ECC_H_ */
 /** @} */
