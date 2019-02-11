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
 * \file osa_timer.c
 *
 * \brief  This file implements the clock timer.
 *
 * \version 0.1 (Aug 2016) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <osa_timer.h>

Int32 OSA_timerCreate(OSA_TimerHndl *hndl,OSA_TimerCb cbf,union sigval value)
{
    Int32 retVal = -1;
    pthread_mutexattr_t mutex_attr;
    struct sigevent sev;

    retVal = pthread_mutexattr_init(&mutex_attr);
    retVal += pthread_mutex_init(&hndl->lock, &mutex_attr);

    memset(&sev, 0, sizeof(sev));

    sev.sigev_notify = SIGEV_THREAD;            /* Notify via thread */
    sev.sigev_value.sival_int = value.sival_int; /*Callback function params */
    sev.sigev_value.sival_ptr = value.sival_ptr; /*Callback function params */
    sev.sigev_notify_function = cbf;     /* callback start function */
    sev.sigev_notify_attributes = NULL;

    /* Create Real Time Timer */
    retVal = timer_create(CLOCK_REALTIME, &sev, &hndl->timerid);
    if (retVal < 0)
    {
        Vps_printf(" OSA_TIMER: Could not create Timer\n");
        OSA_assert(FALSE);
    }

    pthread_mutexattr_destroy(&mutex_attr);

    return retVal;
}

Int32 OSA_timerDelete(OSA_TimerHndl *hndl)
{
    Int32 retVal = -1;
    struct itimerspec value = {{0, 0}, {0, 0}};

    pthread_mutex_lock(&hndl->lock);

    /* Disarm Timer */
    retVal = timer_settime(hndl->timerid, 0, &value, NULL);
    retVal += timer_delete(hndl->timerid);
    pthread_mutex_unlock(&hndl->lock);

    pthread_mutex_destroy(&hndl->lock);

    return retVal;
}

Int32 OSA_timerStart(OSA_TimerHndl *hndl)
{
    Int32 retVal = -1;
    struct itimerspec value = {{0, 0}, {0, 0}};
    value.it_value.tv_nsec = hndl->period * 1000000;
    value.it_interval.tv_nsec = hndl->period * 1000000;

    pthread_mutex_lock(&hndl->lock);
    /* Arm Timer */
    retVal = timer_settime(hndl->timerid, 0, &value, NULL);
    pthread_mutex_unlock(&hndl->lock);

    return retVal;
}

Int32 OSA_timerStop(OSA_TimerHndl *hndl)
{
    Int32 retVal = -1;
    struct itimerspec value = {{0, 0}, {0, 0}};
    pthread_mutex_lock(&hndl->lock);
    /* Disarm Timer */
    retVal = timer_settime(hndl->timerid, 0, &value, NULL);

    pthread_mutex_unlock(&hndl->lock);

    return retVal;
}
