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


#include <osa_que.h>

int OSA_queCreate(OSA_QueHndl *hndl, Uint32 maxLen)
{
  pthread_mutexattr_t mutex_attr;
  pthread_condattr_t cond_attr;
  int status=OSA_SOK;

  hndl->curRd = hndl->curWr = 0;
  hndl->count = 0;
  hndl->len   = maxLen;
  hndl->queue = OSA_memAlloc(sizeof(Int32)*hndl->len);
  
  if(hndl->queue==NULL) {
    OSA_ERROR("OSA_queCreate() = %d \r\n", status);
    return OSA_EFAIL;
  }
 
  status |= pthread_mutexattr_init(&mutex_attr);
  status |= pthread_condattr_init(&cond_attr);  
  
  status |= pthread_mutex_init(&hndl->lock, &mutex_attr);
  status |= pthread_cond_init(&hndl->condRd, &cond_attr);    
  status |= pthread_cond_init(&hndl->condWr, &cond_attr);  

  if(status!=OSA_SOK)
    OSA_ERROR("OSA_queCreate() = %d \r\n", status);
    
  pthread_condattr_destroy(&cond_attr);
  pthread_mutexattr_destroy(&mutex_attr);
    
  return status;
}

int OSA_queDelete(OSA_QueHndl *hndl)
{
  if(hndl->queue!=NULL)
    OSA_memFree(hndl->queue);
    
  pthread_cond_destroy(&hndl->condRd);
  pthread_cond_destroy(&hndl->condWr);
  pthread_mutex_destroy(&hndl->lock);  
  
  return OSA_SOK;
}



int OSA_quePut(OSA_QueHndl *hndl, Int32 value, Uint32 timeout)
{
  int status = OSA_EFAIL;

  pthread_mutex_lock(&hndl->lock);

  while(1) {
    if( hndl->count < hndl->len ) {
      hndl->queue[hndl->curWr] = value;
      hndl->curWr = (hndl->curWr+1)%hndl->len;
      hndl->count++;
      status = OSA_SOK;
      pthread_cond_signal(&hndl->condRd);
      break;
    } else {
      if(timeout == OSA_TIMEOUT_NONE)
        break;

      status = pthread_cond_wait(&hndl->condWr, &hndl->lock);
    }
  }

  pthread_mutex_unlock(&hndl->lock);

  return status;
}


int OSA_queGet(OSA_QueHndl *hndl, Int32 *value, Uint32 timeout)
{
  int status = OSA_EFAIL;
  
  pthread_mutex_lock(&hndl->lock);
  
  while(1) {
    if(hndl->count > 0 ) {

      if(value!=NULL) {
        *value = hndl->queue[hndl->curRd];
      }
      
      hndl->curRd = (hndl->curRd+1)%hndl->len;
      hndl->count--;
      status = OSA_SOK;
      pthread_cond_signal(&hndl->condWr);
      break;
    } else {
      if(timeout == OSA_TIMEOUT_NONE)
        break;

      status = pthread_cond_wait(&hndl->condRd, &hndl->lock);
    }
  }

  pthread_mutex_unlock(&hndl->lock);

  return status;
}


Uint32 OSA_queGetQueuedCount(OSA_QueHndl *hndl)
{
  Uint32 queuedCount = 0;

  pthread_mutex_lock(&hndl->lock);
  queuedCount = hndl->count;
  pthread_mutex_unlock(&hndl->lock);
  return queuedCount;
}

int OSA_quePeek(OSA_QueHndl *hndl, Int32 *value)
{
  int status = OSA_EFAIL;
  *value = 0x00;
  pthread_mutex_lock(&hndl->lock);
  if(hndl->count > 0 ) {
      if(value!=NULL) {
        *value = hndl->queue[hndl->curRd];
        status = OSA_SOK;
      }
  }
  pthread_mutex_unlock(&hndl->lock);

  return status;
}

Bool OSA_queIsEmpty(OSA_QueHndl *hndl)
{
  Bool isEmpty;

  pthread_mutex_lock(&hndl->lock);
  if (hndl->count == 0)
  {
      isEmpty = TRUE;
  }
  else
  {
      isEmpty = FALSE;
  }
  pthread_mutex_unlock(&hndl->lock);

  return isEmpty;
}



