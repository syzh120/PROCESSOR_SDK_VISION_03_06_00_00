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

/**
  ******************************************************************************
 * \file ultrasonicCaptureLink_PGA460_tsk.c
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "ultrasonicCaptureLink_priv.h"
#include <ti/drv/vps/include/boards/bsp_board.h>

/* polling interval in units of msecs */
#define ULTRASONIC_CAPTURE_POLLING_INTERVAL     (1)

/**
 *******************************************************************************
 * \brief Creates link related information, including buffer allocation
 *
 * \param  pObj     [IN]  link instance handle
 * \param  pPrm     [IN]  Create params for link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 UltrasonicCaptureLink_PGA460_drvCreate(UltrasonicCaptureLink_Obj * pObj, UltrasonicCaptureLink_CreateParams * pPrm)
{
    UInt32 bufId;
    Int32 status;
    System_Buffer *pSysBuf;
    System_MetaDataBuffer *pMetaBuf;
    UInt32 deviceId;
    Bool   isDetected;

    UInt8 ultrasonicSensorDetected;
    Vps_printf(" ULTRASONIC: Create in progress !!!");

    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    /* set output info */
    memset(&pObj->info, 0, sizeof(pObj->info));
    pObj->info.numQue = 1;
    pObj->info.queInfo[0].numCh = 1;

    pObj->info.queInfo[0].chInfo[0].flags = System_Link_Ch_Info_Set_Flag_Buf_Type(
            pObj->info.queInfo[0].chInfo[0].flags,
            SYSTEM_BUFFER_TYPE_METADATA
            );

    status = Utils_bufCreate(&pObj->outFrameQue, FALSE, FALSE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    ultrasonicSensorDetected = 0;

    for (bufId = 0; bufId < ULTRASONIC_CAPTURE_LINK_MAX_OUT_BUFFERS; bufId++)
    {
        pSysBuf = &pObj->sysBufs[bufId];
        pMetaBuf = &pObj->metaBufs[bufId];

        memset(pSysBuf, 0, sizeof(*pSysBuf));
        memset(pMetaBuf, 0, sizeof(*pMetaBuf));

        pSysBuf->bufType = SYSTEM_BUFFER_TYPE_METADATA;
        pSysBuf->payloadSize = sizeof(*pMetaBuf);
        pSysBuf->payload = pMetaBuf;

        pMetaBuf->numMetaDataPlanes = 1;
        pMetaBuf->metaBufSize[0] = sizeof(UltrasonicCapture_MeasurementInfo);
        pMetaBuf->bufAddr[0] =
                    Utils_memAlloc( UTILS_HEAPID_DDR_CACHED_SR,
                                    pMetaBuf->metaBufSize[0],
                                    32
                                    );

        pMetaBuf->metaFillLength[0] = pMetaBuf->metaBufSize[0];

        status = Utils_bufPutEmptyBuffer(&pObj->outFrameQue,
                                         pSysBuf);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    if(pObj->createArgs.uartInstId!=BSP_DEVICE_UART_INST_ID_2)
    {
        Vps_printf(
                " ULTRASONIC: WARNING: UART instance used for communication MUST be UART%d !!!\n",
                        BSP_DEVICE_UART_INST_ID_2);
        pObj->createArgs.uartInstId = BSP_DEVICE_UART_INST_ID_2;
    }

    for (deviceId = 0U; deviceId < pPrm->numSensorsConnected; deviceId++)
    {
        pObj->deviceIsDetected[deviceId] = FALSE;

        isDetected = Bsp_pga460ProbeDevice(pObj->createArgs.uartInstId, deviceId);
        if (TRUE == isDetected)
        {
            pObj->deviceIsDetected[deviceId] = TRUE;
            Vps_printf(" ULTRASONIC: UART%d: DEVICE%d detected !\n",
                pObj->createArgs.uartInstId, deviceId);
            ultrasonicSensorDetected++;
        }
        else
        {
            Vps_printf(
                " ULTRASONIC: UART%d: DEVICE%d NOT FOUND !!!\n",
                pObj->createArgs.uartInstId, deviceId);
        }
    }

    Vps_printf(" ULTRASONIC: %d ultrasonic sensors have been detected\n", ultrasonicSensorDetected);
    Vps_printf(" ULTRASONIC: Create DONE !!!");

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Stop link
 *
 * \param  pObj     [IN]  link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 UltrasonicCaptureLink_PGA460_drvStart(UltrasonicCaptureLink_Obj * pObj)
{

    Vps_printf(" ULTRASONIC: Start DONE !!!");

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Start link
 *
 * \param  pObj     [IN]  link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 UltrasonicCaptureLink_PGA460_drvStop(UltrasonicCaptureLink_Obj * pObj)
{

    Vps_printf(" ULTRASONIC: Stop DONE !!!");

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Get measurement data from ultrasonic sensor
 *
 * \param  pObj     [IN]  link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 UltrasonicCaptureLink_PGA460_tskRun(UltrasonicCaptureLink_Obj * pObj,
                         Utils_TskHndl * pTsk,
                         Utils_MsgHndl ** pMsg, Bool * done, Bool * ackMsg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool runDone, runAckMsg;
    Utils_MsgHndl *pRunMsg;
    UInt32 cmd, deviceId;
    UltrasonicCaptureLink_CreateParams *pCreateArgs;
    System_Buffer *pBuf;
    System_MetaDataBuffer *pMetaBuf;
    UltrasonicCapture_MeasurementInfo *pMesurementInfo;
    UltrasonicCapture_DeviceMeasurementInfo *pDeviceInfo;
    Int32 distMeasuredShort, distMeasuredShort_front, distMeasuredShort_back, distMeasuredShort_right, distMeasuredShort_left, measurementInit;
    UInt32 curTime;
    UInt8 firstBroadcast = 1;

    distMeasuredShort_front = 0x7FFFFFFF;
    distMeasuredShort_right = 0x7FFFFFFF;
    distMeasuredShort_back = 0x7FFFFFFF;
    distMeasuredShort_left = 0x7FFFFFFF;
    /* READY loop done and ackMsg status */
    *done = FALSE;
    *ackMsg = FALSE;
    *pMsg = NULL;

    pCreateArgs = &pObj->createArgs;

    /* RUN loop done and ackMsg status */
    runDone = FALSE;
    runAckMsg = FALSE;

    measurementInit = Bsp_pga460InitMeasurement(pObj->createArgs.uartInstId);

    /* RUN state loop */
    while (!runDone)
    {
        curTime = Utils_getCurTimeInMsec();

        pBuf = NULL;
        Utils_bufGetEmptyBuffer(&pObj->outFrameQue,
                                &pBuf, BSP_OSAL_NO_WAIT);

        if(pBuf)
        {
            pBuf->srcTimestamp  = Utils_getCurGlobalTimeInUsec();
            pBuf->frameId  = 0;

            pMetaBuf = (System_MetaDataBuffer*)pBuf->payload;

            pMesurementInfo = (UltrasonicCapture_MeasurementInfo*)
                                    pMetaBuf->bufAddr[0];

            pMesurementInfo->numSensors = 0;

                Bsp_pga460SendBroadcast(
                                   pCreateArgs->uartInstId,
                                   deviceId,
                                   firstBroadcast);

                firstBroadcast = 0;
                for (deviceId = 0U; deviceId < pCreateArgs->numSensorsConnected; deviceId++)
                {
                    if(pObj->deviceIsDetected[deviceId] && (measurementInit==0))
                    {
                        distMeasuredShort = Bsp_pga460GetMeasurement(
                                   pCreateArgs->uartInstId,
                                   deviceId);

                        /* If there was a timeout, use previous values */
                        if (0 == distMeasuredShort)
                        {
                            if (deviceId == 0)
                            {
                                Vps_printf("Front timeout!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                distMeasuredShort = distMeasuredShort_front;
                            }
                            if (deviceId == 1)
                            {
                                Vps_printf("Right timeout!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                distMeasuredShort = distMeasuredShort_right;
                            }
                            if (deviceId == 2)
                            {
                                Vps_printf("Back timeout!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                distMeasuredShort = distMeasuredShort_back;
                            }
                            if (deviceId == 3)
                            {
                                Vps_printf("Left timeout!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                distMeasuredShort = distMeasuredShort_left;
                            }
                        }

                        pDeviceInfo =
                            &pMesurementInfo->deviceInfo
                                        [pMesurementInfo->numSensors];

                        pDeviceInfo->deviceId = deviceId;
                        pDeviceInfo->distanceShort = distMeasuredShort;

                        pMesurementInfo->numSensors++;

                        if (deviceId == 0)
                        {
                            distMeasuredShort_front = distMeasuredShort;
                        }
                        if (deviceId == 1)
                        {
                            distMeasuredShort_right = distMeasuredShort;
                        }
                        if (deviceId == 2)
                        {
                            distMeasuredShort_back = distMeasuredShort;
                        }
                        if (deviceId == 3)
                        {
                            distMeasuredShort_left = distMeasuredShort;
                        }
                    }
                }

            Cache_wb(
                pMetaBuf->bufAddr[0],
                pMetaBuf->metaBufSize[0],
                Cache_Type_ALLD,
                TRUE
              );

            if(pMesurementInfo->numSensors > 0)
            {
                /* sensor data available, send data to next link */
                status = Utils_bufPutFullBuffer(&pObj->outFrameQue,
                                                pBuf);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                System_sendLinkCmd(pCreateArgs->outQueParams.nextLink,
                                  SYSTEM_CMD_NEW_DATA, NULL);
            }
            else
            {
                /* No sensor detected, dont send buffer to next link */
                status = Utils_bufPutEmptyBuffer(&pObj->outFrameQue,
                                                pBuf);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
        }

        curTime = Utils_getCurTimeInMsec() - curTime;

        /* sleep such that task gets invoked once every 33 msec */
        if(curTime<ULTRASONIC_CAPTURE_POLLING_INTERVAL)
            Task_sleep(ULTRASONIC_CAPTURE_POLLING_INTERVAL-curTime);

        /* wait for message */
        status = Utils_tskRecvMsg(pTsk, &pRunMsg, BSP_OSAL_NO_WAIT);
        if (status == SYSTEM_LINK_STATUS_SOK)
        {
            /* extract message command from message */
            cmd = Utils_msgGetCmd(pRunMsg);

            switch (cmd)
            {
                case SYSTEM_CMD_STOP:
                    /* stop RUN loop and goto READY state */
                    runDone = TRUE;

                    /* ACK message after actually stopping the driver outside the
                     * RUN loop */
                    runAckMsg = TRUE;
                    break;

                case SYSTEM_CMD_DELETE:

                    /* stop RUN loop and goto IDLE state */

                    /* exit RUN loop */
                    runDone = TRUE;

                    /* exit READY loop */
                    *done = TRUE;

                    /* ACK message after exiting READY loop */
                    *ackMsg = TRUE;

                    /* Pass the received message to the READY loop */
                    *pMsg = pRunMsg;

                    break;
                default:

                    /* invalid command for this state ACK it and continue RUN
                     * loop */
                    Utils_tskAckOrFreeMsg(pRunMsg, status);
                    break;
            }
        }
    }

    /* RUN loop exited, stop driver */
    UltrasonicCaptureLink_PGA460_drvStop(pObj);

    /* ACK message if not ACKed earlier */
    if (runAckMsg)
        Utils_tskAckOrFreeMsg(pRunMsg, status);

    return status;
}

/**
 *******************************************************************************
 * \brief Function to delete ULTRASONIC_CAPTURE link. This will simply delete all output
 *    queues and the semaphore
 *
 * \param  pObj     [IN]  ULTRASONIC_CAPTURE link instance handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 UltrasonicCaptureLink_PGA460_drvDelete(UltrasonicCaptureLink_Obj * pObj)
{
    Int32 status;
    UInt32 bufId;
    System_MetaDataBuffer *pMetaBuf;

    Vps_printf(" ULTRASONIC: Delete in progress !!!");

    for (bufId = 0; bufId < ULTRASONIC_CAPTURE_LINK_MAX_OUT_BUFFERS; bufId++)
    {
        pMetaBuf = &pObj->metaBufs[bufId];

        status = Utils_memFree( UTILS_HEAPID_DDR_CACHED_SR,
                        pMetaBuf->bufAddr[0],
                        pMetaBuf->metaBufSize[0]
                    );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    status = Utils_bufDelete(&pObj->outFrameQue);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Vps_printf(" ULTRASONIC: Delete DONE !!!");

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Creating ULTRASONIC_CAPTURE link
 *     - Arrival of new data
 *     - Deleting ULTRASONIC_CAPTURE link
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */
Void UltrasonicCaptureLink_PGA460_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool ackMsg, done;

    UltrasonicCaptureLink_Obj *pObj = (UltrasonicCaptureLink_Obj*) pTsk->appData;

    if(cmd!=SYSTEM_CMD_CREATE)
    {
        /* invalid command recived in IDLE status, be in IDLE state and ACK
         * with error status */
        Utils_tskAckOrFreeMsg(pMsg, SYSTEM_LINK_STATUS_EFAIL);
        return;
    }

    /* Create command received, create the driver */
    status = UltrasonicCaptureLink_PGA460_drvCreate(pObj, Utils_msgGetPrm(pMsg));

    /* ACK based on create status */
    Utils_tskAckOrFreeMsg(pMsg, status);

    /* if create status is error then remain in IDLE state */
    if (status != SYSTEM_LINK_STATUS_SOK)
        return;

    done = FALSE;
    ackMsg = FALSE;

    /* READY state loop */
    while (!done)
    {
        /* wait for message */
        status = Utils_tskRecvMsg(pTsk, &pMsg, BSP_OSAL_WAIT_FOREVER);
        if (status != SYSTEM_LINK_STATUS_SOK)
            break;

        /* extract message command from message */
        cmd = Utils_msgGetCmd(pMsg);

        switch (cmd)
        {
            case SYSTEM_CMD_START:
                /* Start capture driver */
                status = UltrasonicCaptureLink_PGA460_drvStart(pObj);

                /* ACK based on create status */
                Utils_tskAckOrFreeMsg(pMsg, status);

                /* if start status is error then remain in READY state */

                if (status == SYSTEM_LINK_STATUS_SOK)
                {
                    /* start success, entering RUN state */
                    status =
                        UltrasonicCaptureLink_PGA460_tskRun(pObj, pTsk, &pMsg, &done, &ackMsg);

                    /** done = FALSE, exit RUN state
                      done = TRUE, exit RUN and READY state
                     */
                }
                break;
            case SYSTEM_CMD_DELETE:

                /* exit READY state */
                done = TRUE;
                ackMsg = TRUE;
                break;

            default:
                /* invalid command for this state ACK it and continue READY
                 * loop */
                Utils_tskAckOrFreeMsg(pMsg, status);
                break;
        }
    }

    /* exiting READY state, delete driver */
    UltrasonicCaptureLink_PGA460_drvDelete(pObj);

    /* ACK message if not previously ACK'ed */
    if (ackMsg && pMsg != NULL)
        Utils_tskAckOrFreeMsg(pMsg, status);

    /* entering IDLE state */
    return;
}

