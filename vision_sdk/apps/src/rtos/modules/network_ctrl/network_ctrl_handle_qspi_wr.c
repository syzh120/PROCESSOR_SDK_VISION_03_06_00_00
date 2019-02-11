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


#include "network_ctrl_priv.h"
#include <src/rtos/utils_common/include/utils_qspi.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#define NETWORKCTRL_APP_IMAGE_FILE_SIZE     (32*1024*1024U)


Void NetworkCtrl_cmdHandlerQspiWrite(char *cmd, UInt32 prmSize)
{
    Int32 status = FVID2_SOK;
    UInt32 qSpiOffset;
    UInt8 *gDataBuf = NULL;

    gDataBuf = Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            NETWORKCTRL_APP_IMAGE_FILE_SIZE,
            8);
    UTILS_assert(gDataBuf != NULL);

    Vps_printf(" NETWORK_CTRL: Max file size that can be flashed to QSPI is %d B\n",NETWORKCTRL_APP_IMAGE_FILE_SIZE);
    Vps_printf(" NETWORK_CTRL: Received file size is %d B\n",prmSize);

    if (prmSize > NETWORKCTRL_APP_IMAGE_FILE_SIZE)
    {
        Vps_printf(" NETWORK_CTRL ERROR : Max file size that can be flashed to QSPI is %d B \
                     but received file size is %d B \n",NETWORKCTRL_APP_IMAGE_FILE_SIZE,prmSize);
        /* send response */
        NetworkCtrl_writeParams(NULL, 0, 0);
    }
    else
    {
        /* read parameters */
        NetworkCtrl_readParams(gDataBuf, prmSize);

        qSpiOffset = *((UInt32 *)gDataBuf);

        Vps_printf(" NETWORK_CTRL: Flashing %d B of file to QSPI at offset 0x%08x ...\n",(prmSize - 4U),qSpiOffset);

         /* QSPI Init is needed here otherwise erase/write will not happen even though we initialized during start  */
        System_qspiInit();
        Task_sleep(1);
        System_qspiWriteSector(qSpiOffset,
                               (UInt32)(((UInt32 *)gDataBuf) + 1U),
                               SystemUtils_align((prmSize - 4U),SYSTEM_QSPI_FLASH_BLOCK_SIZE));
        Vps_printf(" QSPI Flash Complete !!!\n");

        /* send response */
        NetworkCtrl_writeParams(NULL, 0, 0);
    }

    status = Utils_memFree( UTILS_HEAPID_DDR_CACHED_SR, gDataBuf, prmSize);
    UTILS_assert(status==0);

}
