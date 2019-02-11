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
 *   \ingroup SAMPLE_MODULE_API
 *   \defgroup LZ4_LINK_API Grpx Source Link API
 *
 *   lz4CompDecomp module can be used for the following purposes
 *   1. Compression of the the buffer using LZ4
 *   2. Decompression of buffer compressed using LZ4
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file lz4CompDecomp.h
 *
 * \brief lz4 Compression Decompression link API public header file.
 *
 * \version 0.0 (Nov 2017) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef LZ4_LINK_H_
#define LZ4_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <include/link_api/system.h>
#include <include/link_api/system_const.h>

/**
 *******************************************************************************
 *   \brief Link CMD: Print the passed string on display
 *
 *   Command used to print arbitrary string on display using GrpxSrc link
 *
 *   \param lz4CompDecomp_StringRunTimePrintParams * [IN] String to be printed
 *******************************************************************************
 */
#define LZ4_COMPRESS_CMD              (0x5001U)

/**
 *******************************************************************************
 *   \brief Link CMD: Print the passed string on display with out clear
 *
 *   Command used to print arbitrary string on display using GrpxSrc link
 *
 *   \param lz4CompDecomp_StringRunTimePrintParams * [IN] String to be printed
 *******************************************************************************
 */
#define LZ4_DECOMPRESS_CMD            (0x5002U)

/* @} */


/******************************************************************************
 *
 *  Data structures
 *
*******************************************************************************
*/
typedef struct
{
  Int32 inputBufferSize;
  /*Input buffer size to be compressed/decompressed*/
  UInt8 *inputBuffer;
  /*Input buffer address to be compressed/decompressed*/
  Int32 outputBufferSize;
  /*Output buffer size which is compressed/decompressed*/
  UInt8  *outputBuffer;
  /*Output buffer which is compressed/decompressed*/
  UInt32 operationDone;
  /*Flag to indicate the completion of operation*/
  UInt32 CRC[4];
  /*CRC to check the integrity of the output buffer*/
}lz4CompDecomp_inp;

/**
******************************************************************************
*
*  Functions
*
*******************************************************************************
*/

/**
*******************************************************************************
 *
 * \brief lz4 Compression Decompression link register and init
 *
 *    - Creates link task
 *    - Registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 lz4CompDecomp_init(void);

/**
*******************************************************************************
 *
 * \brief lz4 Compression Decompression link de-register and init
 *
 *    - deletes link task
 *    - De-registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 lz4CompDecomp_deInit(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
