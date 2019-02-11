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
  ******************************************************************************
 * \file lz4CompDecomp_tsk.c
*******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "lz4.h"
#include <rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/lz4CompDecomp.h>
#include <include/link_api/rtiLink.h>
#include <src/rtos/utils_common/include/utils_prf.h>/**
 *******************************************************************************
 *
 * \brief This function accepts the lz4CompDecomp_inp buffer for
 *     - DeCompression of the input buffer
 * \param  pMsg [IN] lz4CompDecomp_inp
 *
 *******************************************************************************
 */
uint32_t lz4CompDecomp_compress(lz4CompDecomp_inp *pMsg)
{
    uint32_t start = 0;
    uint32_t end = 0;
    const int32_t max_dst_size = LZ4_compressBound(pMsg->inputBufferSize);

    start = Utils_getCurTimeInMsec();
    pMsg->outputBufferSize = LZ4_compress_default((char *)(pMsg->inputBuffer), (char *)(pMsg->outputBuffer), pMsg->inputBufferSize, max_dst_size);
    end = Utils_getCurTimeInMsec();

    /* Check return_value to determine what happened. */
    if (pMsg->outputBufferSize < 0)
    Vps_printf("A negative result from LZ4_compress_default indicates a failure trying to compress the data.  See exit code (echo $?) for value returned.");
    if (pMsg->outputBufferSize == 0)
    Vps_printf("A result of 0 means compression worked, but was stopped because the destination buffer couldn't hold all the information.");
    if (pMsg->outputBufferSize > 0)
    Vps_printf("We successfully compressed some data from %d to %d in %dms\n", pMsg->inputBufferSize, pMsg->outputBufferSize, (end - start));

    Cache_wb(
            (Ptr)(pMsg->outputBuffer),
            pMsg->outputBufferSize,
            Cache_Type_ALLD,
            TRUE);
    pMsg->operationDone = 1;

    Cache_wb(
            (Ptr)(pMsg),
            sizeof(lz4CompDecomp_inp),
            Cache_Type_ALLD,
            TRUE);

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief This function accepts the lz4CompDecomp_inp buffer for
 *         - Compression of the input buffer
 * \param  pMsg [IN] lz4CompDecomp_inp
 *
 *******************************************************************************
 */
uint32_t lz4CompDecomp_decompress(lz4CompDecomp_inp *pMsg)
{
    Int32 start, end;
    start = Utils_getCurTimeInMsec();
    pMsg->outputBufferSize = LZ4_decompress_safe((char *)(pMsg->inputBuffer), (char *)(pMsg->outputBuffer), pMsg->inputBufferSize, pMsg->outputBufferSize);
    end = Utils_getCurTimeInMsec();

    if (pMsg->outputBufferSize < 0)
    Vps_printf("A negative result from LZ4_decompress_safe indicates a failure trying to decompress the data.  See exit code (echo $?) for value returned.");
    if (pMsg->outputBufferSize == 0)
    Vps_printf("I'm not sure this function can ever return 0.  Documentation in lz4.h doesn't indicate so.");
    if (pMsg->outputBufferSize > 0)
    Vps_printf("We successfully decompressed data from %d to %d in %dms\n", pMsg->inputBufferSize, pMsg->outputBufferSize, (end - start));

    Cache_wb(
            (Ptr)(pMsg->outputBuffer),
            pMsg->outputBufferSize,
            Cache_Type_ALLD,
            TRUE);

    pMsg->operationDone = 1;

    Cache_wb(
            (Ptr)(pMsg),
            sizeof(lz4CompDecomp_inp),
            Cache_Type_ALLD,
            TRUE);

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Compression of the input buffer
 *     - Decompression of Input Buffer
 * \param  cmd  [IN] The command for compression/decompression
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */
static Void lz4CompDecomp_tskMain(uint32_t cmd, Void *pMsg)
{

    switch (cmd)
    {
        case LZ4_COMPRESS_CMD:
            lz4CompDecomp_compress((lz4CompDecomp_inp *)pMsg);
            break;

        case LZ4_DECOMPRESS_CMD:
            lz4CompDecomp_decompress((lz4CompDecomp_inp *)pMsg);
            break;

        default:
            break;
    }
    return;
}

/**
 *******************************************************************************
 *
 * \brief Init function for lz4CompDecomp module. This function registers this
 *  module from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 lz4CompDecomp_init()
{
    Vps_printf("lz4CompDecomp Init");
    SystemLink_registerHandler(lz4CompDecomp_tskMain);
    return 0;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for lz4CompDecomp module. This function de-registers this
 *  module from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 lz4CompDecomp_deInit()
{
    SystemLink_unregisterHandler(lz4CompDecomp_tskMain);
    return 0;
}
