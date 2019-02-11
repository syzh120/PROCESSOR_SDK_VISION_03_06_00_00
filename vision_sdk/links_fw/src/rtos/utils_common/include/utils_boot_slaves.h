/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *
 * \ingroup UTILS_API
 * \defgroup UTILS_BOOT_SLAVES_API Slave Boot APIs
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils_boot_slaves.h
 *
 * \brief  APIs to use SBL LIB to load and run slaves
 *
 * \version 0.0 (Jun 2015) : [YM] First version
 *
 *******************************************************************************
 */

#ifndef UTILS_BOOT_SLAVES_H
#define UTILS_BOOT_SLAVES_H

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 * \brief Default qspi offset for UcLate AppImages
 *
 * SUPPORTED on TDA3x
 *
 *******************************************************************************
*/
#define SBLLIB_APP_IMAGE_LATE_OFFSET_QSPI (0xA80000U)

/*******************************************************************************
 *  Structures
 *******************************************************************************
 */

typedef struct
{
    UInt32 uclateOffset;
    /**< offset of UcLate multi-core appImage in the memory */

    UInt32 ddrAddress;
    /**< DDR address where RPRC image is copied before parsing. This is the
      *  done in order to remove the limitation of QSPI read and utilize the
      *  DDR bandwidth to do CRC. First App Image is copied from QSPI to DDR,
      *  then CRC is calculated using EDMA from DDR to CRC Signature register
      *  and finally App Image is parsed and executable sections are loaded
      *  into DDR using EDMA.
      */

    UInt32 maxDdrBuffSize;
    /**< Maximum size of DDR buffer */

    Bool useEdma;
    /**< if not true uses memcpy to copy sections to DDR */

    Bool loadCode;
    /**< Flag to state if the code needs to be loaded every time the slaves
     *   are booted or not.
     *   TRUE - Load Code, FALSE - Do not load code.
     */

    Bool enableCrc;
    /**< Flag to state if the CRC needs to be enabled or not (enabled by
     *   default). To disable CRC build SBL with CRC disabled and make the
     *   required changes in multicore image generation script (bat or sh).
     *   TRUE - Enable CRC, FALSE - Disable CRC.
     */
}Utils_BootSlaves_Params;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Reads a Multi-core AppImage from given offset, parses it for entry
 *        points and sections to be loaded, loads and runs slave core
 *        using SBL LIB
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 Utils_bootSlaves(const Utils_BootSlaves_Params *params);

/**
 *******************************************************************************
 *
 * \brief Syncs up with all cores after boot up is complete and completes ipc
 *        set up
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Void Utils_syncSlaves(void);

/**
 *******************************************************************************
 *
 * \brief Initializes basic create time params
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
static inline Void Utils_bootSlaves_paramsInit(Utils_BootSlaves_Params *params);
static inline Void Utils_bootSlaves_paramsInit(Utils_BootSlaves_Params *params)
{
    params->uclateOffset  = SBLLIB_APP_IMAGE_LATE_OFFSET_QSPI;
    params->ddrAddress  = 0U;
    params->maxDdrBuffSize  = 0U;
    params->useEdma = (Bool)TRUE;
    params->loadCode = (Bool)TRUE;
    params->enableCrc = (Bool)TRUE;
}


Void Utils_bootPowerDownSlaves(Void);

#ifdef __cplusplus
}
#endif

#endif

/* @} */
