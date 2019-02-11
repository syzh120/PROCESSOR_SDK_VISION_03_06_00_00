/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \addtogroup QSPI_FLASH
 *
 *  @{
 */
/**
 *  \file     qspi_cmd_init.h
 *
 *  \brief    This file contains the API to get the Flash Info and
 *            Initialize different flashes
 */

#ifndef QSPI_CMD_INIT_H_
#define QSPI_CMD_INIT_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_qspi.h>
#include <ti/boot/sbl_auto/qspiflash/qspi_flash.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   Api to get default intitialize paramters
 *
 * \param   flashType     QSPI Flash type
 * \param   flashDevInfo  Pointer to structure containing device info
 *
 * \return  STW_SOK in case of success -ve number otherwise
 */
int32_t QSPI_GetDefaultFlashDevInfo(qspi_DeviceType_e    flashType,
                                    QSPI_FlashDevInfo_t *flashDevInfo);

/**
 * \brief   Api to initialize device info parameters with default value
 *
 * \param   flashType     QSPI Flash type
 * \param   flashDevInfo  Pointer to structure containing device info
 *
 * \return  STW_SOK in case of success -ve number otherwise
 */
int32_t QSPI_SetDefaultFlashDevInfo(qspi_DeviceType_e          flashType,
                                    const QSPI_FlashDevInfo_t *flashDevInfo);

/**
 * \brief   Api to intialize Spansion flash
 *
 * \param   DeviceType    QSPI Flash type
 *
 * \return  none
 */
void QSPI_SpansionFlashInit(qspi_DeviceType_e DeviceType);

/**
 * \brief   Api to intialize Micron flash
 *
 * \param   DeviceType    QSPI Flash type
 *
 * \return  none
 */
void QSPI_MicronFlashInit(qspi_DeviceType_e DeviceType);

/**
 * \brief   Api to intialize Winbond flash
 *
 * \param   DeviceType    QSPI Flash type
 *
 * \return  none
 */
void QSPI_WinbondFlashInit(qspi_DeviceType_e DeviceType);

/**
 * \brief   Api to intialize ISSI flash
 *
 * \param   DeviceType    QSPI Flash type
 *
 * \return  none
 */
void QSPI_IssiFlashInit(qspi_DeviceType_e DeviceType);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* QSPI_CMD_INIT_H_ */
/** @} */
