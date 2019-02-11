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


#include <osa_msgq.h>

int OSA_msgqCreate(OSA_MsgqHndl *hndl)
{
  pthread_mutexattr_t mutex_attr;
  pthread_condattr_t cond_attr;
  int status=OSA_SOK;
 
  status |= pthread_mutexattr_init(&mutex_attr);
  status |= pthread_condattr_init(&cond_attr);  
  
  status |= pthread_mutex_init(&hndl->lock, &mutex_attr);
  status |= pthread_cond_init(&hndl->condRd, &cond_attr);    
  status |= pthread_cond_init(&hndl->condWr, &cond_attr);  

  hndl->curRd = hndl->curWr = 0;
  hndl->count = 0;
  hndl->len   = OSA_MSGQ_LEN_MAX;

  if(status!=OSA_SOK)
    OSA_ERROR("OSA_msgqCreate() = %d \r\n", status);
    
  pthread_condattr_destroy(&cond_attr);
  pthread_mutexattr_destroy(&mutex_attr);
    
  return status;
}

int OSA_msgqDelete(OSA_MsgqHndl *hndl)
{
  pthread_cond_destroy(&hndl->condRd);
  pthread_cond_destroy(&hndl->condWr);
  pthread_mutex_destroy(&hndl->lock);  
  
  return OSA_SOK;
}

OSA_MsgHndl *OSA_msgqAllocMsgHndl(OSA_MsgqHndl *to, OSA_MsgqHndl *from, Uint32 cmd, void *prm, Uint16 msgFlags)
{
  OSA_MsgHndl *msg;
  
  msg = OSA_memAlloc( sizeof(OSA_MsgHndl) );
  
  if(msg!=NULL) {
    msg->pTo = to;
    msg->pFrom = from;
    msg->pPrm = prm;
    msg->status = OSA_SOK;
    msg->cmd = cmd;
    msg->flags = msgFlags;
  }

  return msg;    
}

int OSA_msgqSend(OSA_MsgqHndl *hndl, OSA_MsgHndl *msg, Uint32 timeout)
{
  int status = OSA_EFAIL;

  pthread_mutex_lock(&hndl->lock);

  while(1) {
    if( hndl->count < hndl->len ) {
      hndl->queue[hndl->curWr] = msg;
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


int OSA_msgqSendMsg(OSA_MsgqHndl *to, OSA_MsgqHndl *from, Uint32 cmd, void *prm, Uint16 msgFlags, OSA_MsgHndl **msg)
{
  int status;
  OSA_MsgHndl *data;

  data = OSA_msgqAllocMsgHndl(to, from, cmd, prm, msgFlags);
  if(data==NULL)
    return OSA_EFAIL;
  
  status = OSA_msgqSend(to, data, OSA_TIMEOUT_FOREVER);
  
  if(status==OSA_SOK) {
    if(msg!=NULL)
      *msg = data;
  }

  return status;
}

int OSA_msgqRecvMsg(OSA_MsgqHndl *hndl, OSA_MsgHndl **msg, Uint32 timeout)
{
  int status = OSA_EFAIL;
  
  pthread_mutex_lock(&hndl->lock);
  
  while(1) {
    if(hndl->count > 0 ) {

      if(msg!=NULL) {
        *msg = hndl->queue[hndl->curRd];
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

int OSA_msgqSendAck(OSA_MsgHndl *msg, int ackRetVal)
{
  int status;

  msg->status = ackRetVal;
  
  status = OSA_msgqSend(msg->pFrom, msg, OSA_TIMEOUT_FOREVER);

  return status;
}

int OSA_msgqFreeMsgHndl(OSA_MsgHndl *msg)
{
  OSA_memFree(msg);
  return OSA_SOK;
}



