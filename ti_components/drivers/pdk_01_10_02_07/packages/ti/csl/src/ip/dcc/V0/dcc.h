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
 *  \defgroup CSL_DCC DCC
 *
 *  @{
 */
/**
 *  \file     dcc.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of DCC.
 *            This also contains some related macros.
 */

#ifndef DCC_H_
#define DCC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_dcc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  Macro defines maximum value of count for clock source 0.
 */
#define DCC_SRC0_COUNT_MAX      (0xFFFFFU)
/**
 * \brief  Macro defines maximum value of valid count for clock source 0.
 */
#define DCC_SRC0_VALID_MAX      (0x0FFFFU)
/**
 * \brief  Macro defines maximum value of count for clock source 1.
 */
#define DCC_SRC1_COUNT_MAX      (0xFFFFFU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum to select the DCC Operation Mode.
 *
 *         DCC can either operate in single shot or continuous mode.
 */
typedef enum dccOperationMode
{
    DCC_OPERATION_MODE_SINGLE_SHOT1 = DCC_DCCGCTRL_SINGLESHOT_MODE1,
    /**< Stop counting when counter0 and valid0 both reach zero */
    DCC_OPERATION_MODE_SINGLE_SHOT2 = DCC_DCCGCTRL_SINGLESHOT_MODE2,
    /**< Stop counting when counter1 reaches zero */
    DCC_OPERATION_MODE_CONTINUOUS = DCC_DCCGCTRL_SINGLESHOT_DISABLE
                                    /**< Continuously repeat (until error) */
}dccOperationMode_t;

/**
 * \brief  Enum to select the COUNT0 clock source.
 */
typedef enum dccClkSrc0
{
    DCC_CLK_SRC0_SYS_CLK1 = DCC_DCCCLKSRC0_CLKSRC0_0,
    /**< SYS_CLK1 is selected as source for COUNT0 */
    DCC_CLK_SRC0_SYS_CLK2 = DCC_DCCCLKSRC0_CLKSRC0_1,
    /**< SYS_CLK2 is selected as source for COUNT0 */
    DCC_CLK_SRC0_XREF_CLK = DCC_DCCCLKSRC0_CLKSRC0_2
                            /**< XREF_CLK is selected as source for COUNT0 */
}dccClkSrc0_t;

/**
 * \brief  Enum for DCC interrupts.
 */
typedef enum dccIntrType
{
    DCC_INTERRUPTS_ERROR = 0x0,
    /**< The error signal */
    DCC_INTERRUPTS_DONE = 0x1
                          /**< Done interrupt signal */
}dccIntrType_t;

/**
 * \brief  Structure containing parameters for DCC module configuration.
 */
typedef struct dccConfigParams
{
    uint32_t mode;
    /**< Mode of operation for DCC module.
     *  Refer enum #dccOperationMode_t.
     */
    uint32_t clkSrc0;
    /**< Clock source for COUNT0 i.e. reference clock.
     *  Refer enum #dccClkSrc0_t.
     */
    uint32_t clkSrc1;
    /**< Clock source for COUNT1 i.e. clock signal to be tested.
     *  Refer enum #dccClkSrc1_t.
     *  NOTE: This will parameter will be ignored if 'alternateClkSrc1' is set
     *        TRUE.
     */
    uint32_t alternateClkSrc1;
    /**< Select alternate clock source.
     *   TRUE: Alternate clock source is selected and 'clkSrc1' will be ignored.
     *   FALSE: Clock source is selected as per 'clkSrc1'.
     */
    uint32_t seedSrc0;
    /**< Preload value/seed value for COUNT0 */
    uint32_t seedValid0;
    /**< Preload value/seed value for VALID0 */
    uint32_t seedSrc1;
    /**< Preload value/seed value for COUNT1 */
}dccConfigParams_t;

/**
 * \brief  Structure for accessing Revision ID of DCC module.
 */
typedef struct dccRevisionId
{
    uint32_t scheme;
    /**< HL scheme */
    uint32_t func;
    /**< functional number */
    uint32_t rtlReleaseNum;
    /**< RTL release number */
    uint32_t major;
    /**< Major revision */
    uint32_t custom;
    /**< Custom revision */
    uint32_t minor;
    /**< Minor revision */
}dccRevisionId_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API is used to configure DCC module.
 *
 * \param   baseAddr        Base Address of the DCC Registers.
 *
 * \param   configParams    DCC configuration parameters.
 *                          Refer enum #dccConfigParams_t.
 *
 * \return  status          Configuration status.
 * NOTE:    If the value of 'seedValid0' is less then 4 then it will programmed
 *          as 4. Since minimum programmable value of the 'seedValid0' is 4.
 */
int32_t DCCSetConfig(uint32_t baseAddr, const dccConfigParams_t *configParams);

/**
 * \brief   This API is used to configure DCC module.
 *
 * \param   baseAddr        Base Address of the DCC Registers.
 *
 * \param   enable          DCC is enabled  if it is TRUE.
 *                          DCC is disabled  if it is FALSE.
 *
 * \return  None
 */
void DCCEnable(uint32_t baseAddr, uint32_t enable);

/**
 * \brief   This API is used to enable interrupts.
 *
 * \param   baseAddr        Base Address of the DCC Registers.
 *
 * \param   intrType        Interrupts to enable.
 *                          Refer enum #dccIntrType_t.
 *
 * \return  status          Configuration status;
 */
int32_t DCCEnableIntr(uint32_t baseAddr, uint32_t intrType);

/**
 * \brief   This API is used to disable interrupts.
 *
 * \param   baseAddr        Base Address of the DCC Registers.
 *
 * \param   intrType        Interrupts to disable.
 *                          Refer enum dccInterrupts_t.
 *
 * \return  status          Configuration status.
 */
int32_t DCCDisableIntr(uint32_t baseAddr, uint32_t intrType);

/**
 * \brief   This API is used to get occurred interrupts.
 *
 * \param   baseAddr        Base Address of the DCC Registers.
 *
 * \return  status          Occurred interrupts.
 */
uint32_t DCCGetIntrStatus(uint32_t baseAddr);

/**
 * \brief   This API is used to clear interrupt status.
 *
 * \param   baseAddr        Base Address of the DCC Registers.
 *
 * \param   intrMask        Interrupts to clear status.
 *                          Refer enum #dccIntrType_t.
 *
 * \return  None
 */
void DCCClearIntrStatus(uint32_t baseAddr, uint32_t intrMask);

/**
 * \brief   This API is used to get the configured DCC parameters.
 *
 * \param   baseAddr        Base Address of the DCC Registers.
 *
 * \param   configParams    DCC configured parameters for operation.
 *                          Refer enum #dccConfigParams_t.
 *
 * \return  None
 */
void DCCGetConfig(uint32_t baseAddr, dccConfigParams_t *configParams);

/**
 * \brief   This API is used get the DCC revision ID.
 *
 * \param   baseAddr        Base Address of the DCC Registers.
 *
 * \param   revId           Contains Revision ID of DCC module.
 *                          Refer struct #dccRevisionId_t.
 *
 * \return  None.
 */
void DCCGetRevisionId(uint32_t baseAddr, dccRevisionId_t *revId);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
 /** @} */
