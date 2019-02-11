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


#include <osa_thr.h>

int OSA_thrCreate(OSA_ThrHndl *hndl, OSA_ThrEntryFunc entryFunc, Uint32 pri, Uint32 stackSize, void *prm)
{
  int status=OSA_SOK;
  pthread_attr_t thread_attr;
  struct sched_param schedprm;

  // initialize thread attributes structure
  status = pthread_attr_init(&thread_attr);

  if(status!=OSA_SOK) {
    OSA_ERROR("OSA_thrCreate() - Could not initialize thread attributes\n");
    return status;
  }

  if(stackSize!=OSA_THR_STACK_SIZE_DEFAULT)
    pthread_attr_setstacksize(&thread_attr, stackSize);

#ifndef ANDROID
  status |= pthread_attr_setinheritsched(&thread_attr, PTHREAD_EXPLICIT_SCHED);
#endif
  status |= pthread_attr_setschedpolicy(&thread_attr, SCHED_RR);

  if(pri>OSA_THR_PRI_MAX)
    pri=OSA_THR_PRI_MAX;
  else
  if(pri<OSA_THR_PRI_MIN)
    pri=OSA_THR_PRI_MIN;

  schedprm.sched_priority = pri;
  status |= pthread_attr_setschedparam(&thread_attr, &schedprm);

  if(status!=OSA_SOK) {
    OSA_ERROR("OSA_thrCreate() - Could not initialize thread attributes\n");
    goto error_exit;
  }

  status = pthread_create(&hndl->hndl, &thread_attr, entryFunc, prm);

  if(status != OSA_SOK) {
    OSA_ERROR("OSA_thrCreate() - Could not create thread [%d]\n", status);
    OSA_assert(status == OSA_SOK);
  }

error_exit:
  pthread_attr_destroy(&thread_attr);

  return status;
}

int OSA_thrJoin(OSA_ThrHndl *hndl)
{
  int status=OSA_SOK;
  void *returnVal;

  status = pthread_join(hndl->hndl, &returnVal);

  return status;
}

int OSA_thrDelete(OSA_ThrHndl *hndl)
{
  int status = OSA_SOK;

  if(&hndl->hndl != NULL)
  {
#ifdef ANDROID
      status = pthread_kill(hndl->hndl, 0);
#else
      status = pthread_cancel(hndl->hndl); 
#endif
      status = OSA_thrJoin(hndl);
  }

  return status;
}

int OSA_thrChangePri(OSA_ThrHndl *hndl, Uint32 pri)
{
  int status = OSA_SOK;
  struct sched_param schedprm;

  if(pri>OSA_THR_PRI_MAX)
    pri=OSA_THR_PRI_MAX;
  else
  if(pri<OSA_THR_PRI_MIN)
    pri=OSA_THR_PRI_MIN;

  schedprm.sched_priority = pri;
  status |= pthread_setschedparam(hndl->hndl, SCHED_FIFO, &schedprm);

  return status;
}

int OSA_thrExit(void *returnVal)
{
  pthread_exit(returnVal);
  return OSA_SOK;
}

