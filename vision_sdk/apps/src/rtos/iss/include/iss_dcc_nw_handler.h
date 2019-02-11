/******************************************************************************
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
******************************************************************************/

/*
 *******************************************************************************
 *
 * \file iss_DCC_NW_HANDLER.h
 *
 * \brief Interface file for DCC network command handler.
 *
 *******************************************************************************
 */


#ifndef ISS_DCC_NW_HANDLER_H_
#define ISS_DCC_NW_HANDLER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*  \brief Command to save DCC file
 *         This command is used to DCC file in the QSPI. This command is sent
 *         by the network tool and processed by the chains common layer
 */
#define SYSTEM_LINK_CMD_SAVE_DCC_FILE           (0x8000)

/*  \brief Command to clear DCC QSPI mem for the give sensor
 *         This command is used to clear QSPI memory for the given sensor .
 *         This command is sent by the network tool and processed by
 *         the chains common layer
 */
#define SYSTEM_LINK_CMD_CLEAR_DCC_QSPI_MEM      (0x8001)

/*  \brief Command to read a sensor Register, used by the network utility
 *         for reading sensor register using video sensor layer
 */
#define SYSTEM_LINK_CMD_READ_SENSOR_REG         (0x8002)

/*  \brief Command to write to sensor register, used by network utility
 *         writes given value to given sensor register using video
 *         sensor layer
 */
#define SYSTEM_LINK_CMD_WRITE_SENSOR_REG        (0x8003)

/* Size of the header in DCC bin file */
#define CHAINS_COMMON_ISS_DCC_BIN_HEADER_SIZE           (16U)

/* offset of the qSPI address in dcc bin header */
#define CHAINS_COMMON_ISS_DCC_BIN_DCC_ID_OFFSET         (2U)

/* DCC Bin file Tag/magic number */
#define CHAINS_COMMON_ISS_DCC_BIN_FILE_TAG_ID           (0x00DCCBEEU)



/*******************************************************************************
 *  Structure declaration
 *******************************************************************************
 */


/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

Void Iss_DccCmdHandler_Init(void);

Void Iss_DccCmdHandler_DeInit(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* end of ISS_DCC_NW_HANDLER_H_ */

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */
