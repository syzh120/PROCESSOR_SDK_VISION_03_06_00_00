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


#include <osa_tsk.h>
#include <osa_debug.h>

void *OSA_tskThrMain(void *pPrm)
{
  OSA_MsgHndl *pMsg;
  OSA_TskHndl *pPrc;

  pPrc = (OSA_TskHndl *)pPrm;
  OSA_assert(pPrc!=NULL);

#ifdef QNX_BUILD
  pthread_setname_np(pthread_self(), pPrc->fncName);
#endif

  while(1) {

    OSA_assertSuccess( OSA_tskWaitMsg(pPrc, &pMsg) );

    OSA_assert(pPrc->fncMain!=NULL);
    pPrc->fncMain(pPrc, pMsg, pPrc->curState);
  }

  return NULL;
}

int OSA_tskCreate(OSA_TskHndl *pPrc, OSA_TskFncMain fncMain, Uint32 tskPri, Uint32 tskStackSize, Uint32 initState,
                  void *appData, char *fncName)
{
  pPrc->curState      = initState;
  pPrc->fncMain       = fncMain;
  pPrc->appData       = appData;
  pPrc->fncName       = fncName;

  OSA_assert(pPrc->fncMain      != NULL);

  OSA_mbxCreate(&pPrc->mbxHndl);

  OSA_assertSuccess( OSA_thrCreate(&pPrc->thrHndl, OSA_tskThrMain, tskPri, tskStackSize,  pPrc) );

  return OSA_SOK;
}

int OSA_tskDelete(OSA_TskHndl *pPrc)
{
  OSA_thrDelete(&pPrc->thrHndl);
  OSA_mbxDelete(&pPrc->mbxHndl);

  pPrc->curState      = 0;
  pPrc->fncMain       = NULL;

  return OSA_SOK;
}

int OSA_tskSendMsg(OSA_TskHndl *pPrcTo, OSA_TskHndl *pPrcFrom, Uint16 cmd, void *pPrm, Uint16 flags)
{
  int retVal;
  OSA_MbxHndl *pMbxFrom;

  OSA_assert(pPrcTo!=NULL);

  if(pPrcFrom==NULL) {
    pMbxFrom = NULL;
  } else {
    pMbxFrom = &pPrcFrom->mbxHndl;
  }

  retVal = OSA_mbxSendMsg(&pPrcTo->mbxHndl, pMbxFrom, cmd, pPrm, flags);

  return retVal;
}

int OSA_tskBroadcastMsg(OSA_TskHndl *pPrcToList[], OSA_TskHndl *pPrcFrom, Uint16 cmd, void *pPrm, Uint16 flags)
{
  int retVal;

  OSA_MbxHndl *pMbxToList[OSA_MBX_BROADCAST_MAX];
  Uint32 i, numMsg;
  OSA_MbxHndl *pMbxFrom;

  OSA_assert(pPrcToList!=NULL);

  if(pPrcFrom==NULL) {
    pMbxFrom = NULL;
  } else {
    pMbxFrom = &pPrcFrom->mbxHndl;
  }

  for(i=0; i<OSA_MBX_BROADCAST_MAX; i++)
  {
    pMbxToList[i]=NULL;
  }

  numMsg = 0;
  while(pPrcToList[numMsg]!=NULL) {
    pMbxToList[numMsg] = &pPrcToList[numMsg]->mbxHndl;
    numMsg++;
    if(numMsg>=OSA_MBX_BROADCAST_MAX) {
      // cannot broadcast to more than OSA_mbx_BROADCAST_MAX mailboxes
      OSA_assert(0);
    }
  }

  if(numMsg == 0) {
     // no mailboxes in 'to' mailbox list
     return OSA_SOK;
  }

  retVal = OSA_mbxBroadcastMsg(&pMbxToList[0], pMbxFrom, cmd, pPrm, flags);

  return retVal;
}


int OSA_tskWaitMsg(OSA_TskHndl *pPrc, OSA_MsgHndl **pMsg)
{
  int retVal;

  retVal = OSA_mbxWaitMsg(&pPrc->mbxHndl, pMsg);

  return retVal;
}

int OSA_tskCheckMsg(OSA_TskHndl *pPrc, OSA_MsgHndl **pMsg)
{
  int retVal;

  retVal = OSA_mbxCheckMsg(&pPrc->mbxHndl, pMsg);

  return retVal;
}

int OSA_tskAckOrFreeMsg(OSA_MsgHndl *pMsg, int ackRetVal)
{
  int retVal;

  retVal = OSA_mbxAckOrFreeMsg(pMsg, ackRetVal);

  return retVal;
}

int OSA_tskFlushMsg(OSA_TskHndl *pPrc)
{
  int retVal;

  retVal = OSA_mbxFlush(&pPrc->mbxHndl);

  return retVal;
}

int OSA_tskWaitCmd(OSA_TskHndl *pPrc, OSA_MsgHndl **pMsg, Uint16 waitCmd)
{
  int retVal;

  retVal = OSA_mbxWaitCmd(&pPrc->mbxHndl, pMsg, waitCmd);

  return retVal;
}

int OSA_tskSetState(OSA_TskHndl *pPrc, Uint32 curState)
{
  pPrc->curState = curState;
  return OSA_SOK;
}

Uint32 OSA_tskGetState(OSA_TskHndl *pPrc)
{
  return pPrc->curState;
}

