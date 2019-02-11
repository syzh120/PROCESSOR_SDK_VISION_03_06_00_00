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
#include <include/alglink_api/algorithmLink_remapMerge.h>
#include <src/rtos/utils_common/include/utils_qspi.h>

Void NetworkCtrl_cmdHandlerStereoCalibImageSave
                                                    (char *cmd, UInt32 prmSize)
{
    AlgorithmLink_RemapMergeSaveFrameStatus saveFrameStatus;
    UInt32 linkId, retry;
    Int32 status;

    /* alloc tmp buffer for parameters */
    if(prmSize == 0)
    {
        /* NO parameters to read */
        linkId = EVE2_LINK (SYSTEM_LINK_ID_ALG_0);

        saveFrameStatus.baseClassControl.controlCmd =
            REMAP_LINK_CMD_SAVE_FRAME;
        saveFrameStatus.baseClassControl.size = sizeof(saveFrameStatus);

        /* get results */
        status = System_linkControl(
            linkId,
            ALGORITHM_LINK_CMD_CONFIG,
            &saveFrameStatus,
            sizeof(saveFrameStatus),
            TRUE);
        UTILS_assert(0 == status);

        retry = 5;
        status = SYSTEM_LINK_STATUS_EFAIL;
        while(retry--)
        {
            Task_sleep(40);

            memset(&saveFrameStatus, 0, sizeof(saveFrameStatus));

            saveFrameStatus.baseClassControl.controlCmd =
                REMAP_LINK_CMD_GET_SAVE_FRAME_STATUS;
            saveFrameStatus.baseClassControl.size = sizeof(saveFrameStatus);

            /* get results */
            status = System_linkControl(
                linkId,
                ALGORITHM_LINK_CMD_CONFIG,
                &saveFrameStatus,
                sizeof(saveFrameStatus),
                TRUE);
            UTILS_assert(0 == status);

            if(status!=SYSTEM_LINK_STATUS_SOK)
            {
                /* raw data saving not enabled or use-case not running*/
                break;
            }
            if(saveFrameStatus.isSaveFrameComplete)
            {
                break;
            }
        }

        if(status!=SYSTEM_LINK_STATUS_SOK)
        {
            /* some error, could not save raw data */
            saveFrameStatus.bufAddr = 0;
            saveFrameStatus.bufSize = 0;
        }
        else
        {
            Cache_inv(
                (xdc_Ptr)SystemUtils_floor(saveFrameStatus.bufAddr, 128),
                SystemUtils_align(saveFrameStatus.bufSize+128, 128),
                Cache_Type_ALLD, TRUE
                );
        }

        /* send response */
        NetworkCtrl_writeParams
            ((UInt8*)saveFrameStatus.bufAddr, saveFrameStatus.bufSize, status);
    }
    else
    {
        Vps_printf(" NETWORK_CTRL: %s: Insufficient parameters (%d bytes) specified !!!\n", cmd, prmSize);
    }
}

Void NetworkCtrl_cmdHandlerStereoWriteCalibLUTToQSPI
                                                    (char *cmd, UInt32 prmSize)
{
    UInt32 qSpiOffset, size;
    UInt8 *pCalibLUTBuf;

    /* alloc tmp buffer for parameters */
    if(prmSize)
    {
        
        pCalibLUTBuf = Utils_memAlloc(
                            UTILS_HEAPID_DDR_CACHED_SR,
                            prmSize,
                            32);
        if (NULL == pCalibLUTBuf)
        {
            Vps_printf(" NETWORK_CTRL: Calib LUT Buffer is NULL");

            /* send response */
            NetworkCtrl_writeParams(NULL, 0, 0);
            return ;
        }

        /* read parameters */
        NetworkCtrl_readParams(pCalibLUTBuf, prmSize);

        /* Third word contains the QSPI offset */
        qSpiOffset = *(((UInt32 *)pCalibLUTBuf) + 2U);
        size = *(((UInt32 *)pCalibLUTBuf) + 1U);
        Vps_printf(" NETWORK_CTRL: qSpiOffset = %u, size = %u", qSpiOffset, size);
        /* QSPI Init is needed here otherwise erase/write will not happen even though we initialized during start  */
        System_qspiInit();
        /* Write complete bin file */
        System_qspiWriteSector(qSpiOffset,
                               (UInt32)pCalibLUTBuf,
                               SystemUtils_align(size, SYSTEM_QSPI_FLASH_BLOCK_SIZE));
    }

    /* send response */
    NetworkCtrl_writeParams(NULL, 0, 0);
    Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pCalibLUTBuf,
                prmSize);
}


