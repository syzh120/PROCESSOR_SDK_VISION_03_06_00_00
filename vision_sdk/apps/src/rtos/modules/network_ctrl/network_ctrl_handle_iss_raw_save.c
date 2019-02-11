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
#include <include/link_api/issCaptureLink.h>
#include <include/link_api/issM2mIspLink.h>
#include <include/link_api/issM2mSimcopLink.h>
#include <src/rtos/iss/include/algorithmLink_issAewb.h>
#include <src/rtos/utils_common/include/utils_qspi.h>
#include <src/rtos/iss/include/iss_dcc_nw_handler.h>

#define NETWORKCTRL_ISS_DCC_FILE_SIZE   (ALGORITHM_AEWB1_DCC_IN_BUF_SIZE)

/* Define for Task Sleep */
#if defined(LINUX_BUILD)

#ifdef Task_sleep
#undef Task_sleep
#endif

#define Task_sleep(x) OSA_waitMsecs(x)

#endif

UInt32 gAewbLinkId = SYSTEM_LINK_ID_INVALID;
UInt32 NetworkCtrl_getAewbLinkId();

Void NetworkCtrl_cmdHandlerIssRawSave(char *cmd, UInt32 prmSize)
{
    IssCaptureLink_GetSaveFrameStatus saveFrameStatus;
    UInt32 linkId, retry, virtAddr = 0, chId = 0;
    Int32 status;

    /* alloc tmp buffer for parameters */
    if(prmSize == 0)
    {
        /* NO parameters to read */
        linkId = SYSTEM_LINK_ID_ISSCAPTURE_0;

        System_linkControl(
            linkId,
            ISSCAPTURE_LINK_CMD_SAVE_FRAME,
            &chId,
            sizeof(chId),
            TRUE
            );

        retry = 5;
        status = SYSTEM_LINK_STATUS_EFAIL;
        while(retry--)
        {
            Task_sleep(40);

            memset(&saveFrameStatus, 0, sizeof(saveFrameStatus));

            status = System_linkControl(
                linkId,
                ISSCAPTURE_LINK_CMD_GET_SAVE_FRAME_STATUS,
                &saveFrameStatus,
                sizeof(saveFrameStatus),
                TRUE
                );

            if(status!=SYSTEM_LINK_STATUS_SOK)
            {
                /* raw data saving not enabled or use-case not running
                 */
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
            virtAddr = 0;
        }
        else
        {
            virtAddr = ChainsCommon_Osal_getVirtAddr((UInt32)
                SystemUtils_floor(saveFrameStatus.bufAddr, 128));

            ChainsCommon_Osal_cacheInv(
                virtAddr,
                SystemUtils_align(saveFrameStatus.bufSize+128, 128));
        }

        /* send response */
        NetworkCtrl_writeParams((UInt8*)virtAddr, saveFrameStatus.bufSize,
            status);
    }
    else
    {
        Vps_printf(" NETWORK_CTRL: %s: Insufficient parameters (%d bytes) specified !!!\n", cmd, prmSize);
    }
}

Void NetworkCtrl_cmdHandlerIssYuvSave(char *cmd, UInt32 prmSize)
{
    IssM2mSimcopLink_GetSaveFrameStatus saveFrameStatus;
    UInt32 linkId, retry, virtAddr = 0, chId = 0;
    Int32 status;

    /* alloc tmp buffer for parameters */
    if(prmSize == 0)
    {
        /* NO parameters to read */
        linkId = SYSTEM_LINK_ID_ISSM2MSIMCOP_0;

        System_linkControl(
            linkId,
            ISSM2MSIMCOP_LINK_CMD_SAVE_FRAME,
            &chId,
            sizeof(chId),
            TRUE
            );

        retry = 5;
        status = SYSTEM_LINK_STATUS_EFAIL;
        while(retry--)
        {
            Task_sleep(40);

            memset(&saveFrameStatus, 0, sizeof(saveFrameStatus));

            status = System_linkControl(
                linkId,
                ISSM2MSIMCOP_LINK_CMD_GET_SAVE_FRAME_STATUS,
                &saveFrameStatus,
                sizeof(saveFrameStatus),
                TRUE
                );

            if(status!=SYSTEM_LINK_STATUS_SOK)
            {
                /* raw data saving not enabled or use-case not running
                 */
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
            virtAddr = 0;
        }
        else
        {
            virtAddr = ChainsCommon_Osal_getVirtAddr((UInt32)
                SystemUtils_floor(saveFrameStatus.bufAddr, 128));

            ChainsCommon_Osal_cacheInv(
                virtAddr,
                SystemUtils_align(saveFrameStatus.bufSize+128, 128));
        }

        /* send response */
        NetworkCtrl_writeParams((UInt8*)virtAddr, saveFrameStatus.bufSize,
            status);
    }
    else
    {
        Vps_printf(" NETWORK_CTRL: %s: Insufficient parameters (%d bytes) specified !!!\n", cmd, prmSize);
    }
}

Void NetworkCtrl_cmdHandlerIssIspSave(char *cmd, UInt32 prmSize)
{
    IssM2mIspLink_GetSaveFrameStatus saveFrameStatus;
    UInt32 linkId, retry, virtAddr, chId = 0;
    Int32 status;

    /* alloc tmp buffer for parameters */
    if(prmSize == 0)
    {
        /* NO parameters to read */
        linkId = SYSTEM_LINK_ID_ISSM2MISP_0;

        System_linkControl(
            linkId,
            ISSM2MISP_LINK_CMD_SAVE_FRAME,
            &chId,
            sizeof(chId),
            TRUE
            );

        retry = 5;
        status = SYSTEM_LINK_STATUS_EFAIL;
        while(retry--)
        {
            Task_sleep(40);

            memset(&saveFrameStatus, 0, sizeof(saveFrameStatus));

            status = System_linkControl(
                linkId,
                ISSM2MISP_LINK_CMD_GET_SAVE_FRAME_STATUS,
                &saveFrameStatus,
                sizeof(saveFrameStatus),
                TRUE
                );

            if(status!=SYSTEM_LINK_STATUS_SOK)
            {
                /* raw data saving not enabled or use-case not running
                 */
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
            virtAddr = 0;
        }
        else
        {
            virtAddr = ChainsCommon_Osal_getVirtAddr((UInt32)
                SystemUtils_floor(saveFrameStatus.bufAddr, 128));

            ChainsCommon_Osal_cacheInv(
                virtAddr,
                SystemUtils_align(saveFrameStatus.bufSize+128, 128));
        }

        /* send response */
        NetworkCtrl_writeParams((UInt8*)virtAddr, saveFrameStatus.bufSize,
            status);
    }
    else
    {
        Vps_printf(" NETWORK_CTRL: %s: Insufficient parameters (%d bytes) specified !!!\n", cmd, prmSize);
    }
}

Void NetworkCtrl_cmdHandlerIssDccSendFile(char *cmd, UInt32 prmSize)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 linkId;
    AlgorithmLink_IssAewbDccControlParams dccCtrlPrms;

    if (prmSize > NETWORKCTRL_ISS_DCC_FILE_SIZE)
    {
        Vps_printf(" NETWORK_CTRL: Insufficient DCC Buffer\n");
        Vps_printf(" NETWORK_CTRL: Increase DCC buffer size in NETWORKCTRL_ISS_DCC_FILE_SIZE\n");

        /* send response */
        NetworkCtrl_writeParams(NULL, 0, 0);

        return ;
    }

    if(prmSize)
    {
        dccCtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_AEWB_LINK_CMD_GET_DCC_BUF_PARAMS;
        dccCtrlPrms.baseClassControl.size = sizeof(dccCtrlPrms);

        dccCtrlPrms.dccBuf = NULL;

        linkId = NetworkCtrl_getAewbLinkId();

        if (SYSTEM_LINK_ID_INVALID != linkId)
        {
            /* get results */
            status = System_linkControl(
                linkId,
                ALGORITHM_LINK_CMD_CONFIG,
                &dccCtrlPrms,
                sizeof(dccCtrlPrms),
                TRUE);
            UTILS_assert(0 == status);
        }

        if (NULL == dccCtrlPrms.dccBuf)
        {
            Vps_printf(" NETWORK_CTRL: DCC Buffer is NULL");

            /* send response */
            NetworkCtrl_writeParams(NULL, 0, 0);

            return ;
        }

        /* read parameters */
        NetworkCtrl_readParams(dccCtrlPrms.dccBuf, prmSize);

        Vps_printf(" NETWORK_CTRL: %s:", cmd);

        dccCtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_AEWB_LINK_CMD_PARSE_AND_SET_DCC_PARAMS;
        dccCtrlPrms.baseClassControl.size = sizeof(dccCtrlPrms);
        dccCtrlPrms.dccBufSize = prmSize;

        /* get results */
        status = System_linkControl(
            linkId,
            ALGORITHM_LINK_CMD_CONFIG,
            &dccCtrlPrms,
            sizeof(dccCtrlPrms),
            TRUE);
    }

    /* send response */
    NetworkCtrl_writeParams(NULL, 0, status);
}

Void NetworkCtrl_cmdHandlerIssSaveDccFile(char *cmd, UInt32 prmSize)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 linkId;
    AlgorithmLink_IssAewbDccControlParams dccCtrlPrms;

    if (prmSize > NETWORKCTRL_ISS_DCC_FILE_SIZE)
    {
        Vps_printf(" NETWORK_CTRL: Insufficient DCC Buffer\n");
        Vps_printf(" NETWORK_CTRL: Increase DCC buffer size in NETWORKCTRL_ISS_DCC_FILE_SIZE\n");

        /* send response */
        NetworkCtrl_writeParams(NULL, 0, 0);

        return ;
    }

    /* alloc tmp buffer for parameters */
    if(prmSize)
    {
        dccCtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_AEWB_LINK_CMD_GET_DCC_BUF_PARAMS;
        dccCtrlPrms.baseClassControl.size = sizeof(dccCtrlPrms);

        dccCtrlPrms.dccBuf = NULL;

        linkId = NetworkCtrl_getAewbLinkId();

        if (SYSTEM_LINK_ID_INVALID != linkId)
        {
            /* get results */
            status = System_linkControl(
                linkId,
                ALGORITHM_LINK_CMD_CONFIG,
                &dccCtrlPrms,
                sizeof(dccCtrlPrms),
                TRUE);
            UTILS_assert(0 == status);
        }

        if (NULL == dccCtrlPrms.dccBuf)
        {
            Vps_printf(" NETWORK_CTRL: DCC Buffer is NULL");

            /* send response */
            NetworkCtrl_writeParams(NULL, 0, 0);

            return ;
        }

        /* read parameters */
        NetworkCtrl_readParams(dccCtrlPrms.dccBuf, prmSize);

        dccCtrlPrms.dccBufSize = prmSize;
        linkId = SYSTEM_LINK_ID_IPU1_0;
        System_linkControl(
            linkId,
            SYSTEM_LINK_CMD_SAVE_DCC_FILE,
            &dccCtrlPrms,
            sizeof(dccCtrlPrms),
            TRUE
        );
    }

    /* send response */
    NetworkCtrl_writeParams(NULL, 0, 0);
}

Void NetworkCtrl_cmdHandlerIssClearDccQspiMem(char *cmd, UInt32 prmSize)
{
    UInt32 linkId;
    UInt32 dccCameraId;

    memset((void*) &dccCameraId, 0U, sizeof(dccCameraId));

    /* alloc tmp buffer for parameters */
    if(prmSize == sizeof(dccCameraId))
    {
        /* read parameters */
        NetworkCtrl_readParams((UInt8*)&dccCameraId, sizeof(dccCameraId));

        linkId = SYSTEM_LINK_ID_IPU1_0;
        System_linkControl(
            linkId,
            SYSTEM_LINK_CMD_CLEAR_DCC_QSPI_MEM,
            &dccCameraId,
            sizeof(dccCameraId),
            TRUE);

        /* send response */
        NetworkCtrl_writeParams(NULL, 0, 0);
    }
    else
    {
        Vps_printf(" NETWORK_CTRL: %s: Insufficient parameters (%d bytes) specified !!!\n", cmd, prmSize);
    }
}

Void NetworkCtrl_cmdHandleIssWriteSensorReg(char *cmd, UInt32 prmSize)
{
    UInt32 linkId;
    UInt32 sensorRegRdWr[3] = {0};

    memset(sensorRegRdWr, 0U, sizeof(sensorRegRdWr));

    /* alloc tmp buffer for parameters */
    if(prmSize == sizeof(sensorRegRdWr))
    {
        /* read parameters */
        NetworkCtrl_readParams((UInt8 *)sensorRegRdWr, sizeof(sensorRegRdWr));

        linkId = SYSTEM_LINK_ID_IPU1_0;
        System_linkControl(
            linkId,
            SYSTEM_LINK_CMD_WRITE_SENSOR_REG,
            &sensorRegRdWr,
            sizeof(sensorRegRdWr),
            TRUE);

        /* send response */
        NetworkCtrl_writeParams(NULL, 0, 0);
    }
    else
    {
        Vps_printf(" NETWORK_CTRL: %s: Insufficient parameters (%d bytes) specified !!!\n", cmd, prmSize);
    }
}

Void NetworkCtrl_cmdHandleIssReadSensorReg(char *cmd, UInt32 prmSize)
{
    UInt32 linkId;
    UInt32 sensorRegRdWr[3] = {0};

    memset(sensorRegRdWr, 0U, sizeof(sensorRegRdWr));

    /* alloc tmp buffer for parameters */
    if (prmSize <= sizeof(sensorRegRdWr))
    {
        /* read parameters */
        NetworkCtrl_readParams((UInt8 *)sensorRegRdWr, prmSize);

        linkId = SYSTEM_LINK_ID_IPU1_0;
        System_linkControl(
            linkId,
            SYSTEM_LINK_CMD_READ_SENSOR_REG,
            &sensorRegRdWr,
            sizeof(sensorRegRdWr),
            TRUE);

        /* send response */
        NetworkCtrl_writeParams((UInt8 *)&sensorRegRdWr[2],
            sizeof(sensorRegRdWr[2]), 0);
    }
    else
    {
        Vps_printf(" NETWORK_CTRL: %s: Insufficient parameters (%d bytes) specified !!!\n", cmd, prmSize);
    }
}

Void NetworkCtrl_cmdHandleIssRead2AParams(char *cmd, UInt32 prmSize)
{
    Int32 status;
    UInt32 linkId;
    AlgorithmLink_IssAewb2AControlParams aewb2ACtrlPrms;

    memset(&aewb2ACtrlPrms, 0U, sizeof(AlgorithmLink_IssAewb2AControlParams));

    if (prmSize == sizeof(AlgorithmLink_IssAewb2AParams))
    {
        /* read parameters */
        NetworkCtrl_readParams((UInt8 *)(&aewb2ACtrlPrms.aewb2APrms), prmSize);

        aewb2ACtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_AEWB_LINK_CMD_GET_2A_PARAMS;
        aewb2ACtrlPrms.baseClassControl.size = sizeof(aewb2ACtrlPrms);

        linkId = NetworkCtrl_getAewbLinkId();

        if (SYSTEM_LINK_ID_INVALID != linkId)
        {
            /* get results */
            status = System_linkControl(
                linkId,
                ALGORITHM_LINK_CMD_CONFIG,
                &aewb2ACtrlPrms,
                sizeof(aewb2ACtrlPrms),
                TRUE);
            UTILS_assert(0 == status);
        }

        /* send response */
        NetworkCtrl_writeParams((UInt8 *)&aewb2ACtrlPrms.aewb2APrms,
            sizeof(AlgorithmLink_IssAewb2AParams), 0);
    }
    else
    {
        Vps_printf(" NETWORK_CTRL: %s: Insufficient parameters (%d bytes) specified !!!\n", cmd, prmSize);
    }
}

Void NetworkCtrl_cmdHandleIssWrite2AParams(char *cmd, UInt32 prmSize)
{
    Int32 status;
    UInt32 linkId;
    AlgorithmLink_IssAewb2AControlParams aewb2ACtrlPrms;

    memset(&aewb2ACtrlPrms, 0U, sizeof(AlgorithmLink_IssAewb2AControlParams));

    if (prmSize == sizeof(AlgorithmLink_IssAewb2AParams))
    {
        /* read parameters */
        NetworkCtrl_readParams((UInt8 *)(&aewb2ACtrlPrms.aewb2APrms), prmSize);

        aewb2ACtrlPrms.baseClassControl.controlCmd =
            ALGORITHM_AEWB_LINK_CMD_SET_2A_PARAMS;
        aewb2ACtrlPrms.baseClassControl.size = sizeof(aewb2ACtrlPrms);

        linkId = NetworkCtrl_getAewbLinkId();

        if (SYSTEM_LINK_ID_INVALID != linkId)
        {
            /* get results */
            status = System_linkControl(
                linkId,
                ALGORITHM_LINK_CMD_CONFIG,
                &aewb2ACtrlPrms,
                sizeof(aewb2ACtrlPrms),
                TRUE);
            UTILS_assert(0 == status);
        }

        /* send response */
        NetworkCtrl_writeParams(NULL, 0, 0);
    }
    else
    {
        Vps_printf(" NETWORK_CTRL: %s: Insufficient parameters (%d bytes) specified !!!\n", cmd, prmSize);
    }
}

UInt32 NetworkCtrl_getAewbLinkId()
{
    Int32 status;
    UInt32 cnt, algId, linkId;

    if (SYSTEM_LINK_ID_INVALID == gAewbLinkId)
    {
        /* Get the linkId of the AEWB algorithm */
        for (cnt = 0U;cnt < ALGORITHM_LINK_IPU_ALG_MAXNUM;cnt ++)
        {
            linkId = IPU1_0_LINK (SYSTEM_LINK_ID_ALG_0 + cnt);

            status = System_linkControl(
                            linkId,
                            ALGORITHM_LINK_CMD_GET_ALGID,
                            &algId,
                            sizeof(algId),
                            TRUE);
            UTILS_assert(0 == status);

            if (ALGORITHM_LINK_IPU_ALG_ISS_AEWB1 == algId)
            {
                gAewbLinkId = linkId;
                break;
            }
        }
    }

    return (gAewbLinkId);
}
