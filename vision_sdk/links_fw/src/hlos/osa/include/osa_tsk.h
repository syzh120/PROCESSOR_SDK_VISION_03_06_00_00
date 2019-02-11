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


#ifndef _OSA_TSK_H_
#define _OSA_TSK_H_

#include <osa_thr.h>
#include <osa_mbx.h>

struct OSA_TskHndl;

#define OSA_TSK_STACK_SIZE_DEFAULT OSA_THR_STACK_SIZE_DEFAULT

typedef int (*OSA_TskFncMain)(struct OSA_TskHndl *pTsk, OSA_MsgHndl *pMsg, Uint32 curState );


/**
  \brief Task Handle
*/
typedef struct OSA_TskHndl {

  OSA_MbxHndl mbxHndl;      ///< Mailbox handle
  OSA_ThrHndl thrHndl;      ///< OS thread handle

  Uint32 curState;          ///< Task state as defined by user
  OSA_TskFncMain fncMain;   ///< Task Main, this function is entered when a message is received by the process
  
  void *appData;
  char *fncName;
    
} OSA_TskHndl;

int OSA_tskCreate(OSA_TskHndl *pPrc, OSA_TskFncMain fncMain, Uint32 tskPri, Uint32 tskStackSize, Uint32 initState,
                  void *appData, char *fncName);
int OSA_tskDelete(OSA_TskHndl *pTsk);
int OSA_tskSendMsg(OSA_TskHndl *pTskTo, OSA_TskHndl *pTskFrom, Uint16 cmd, void *pPrm, Uint16 flags);
int OSA_tskBroadcastMsg(OSA_TskHndl *pTskToList[], OSA_TskHndl *pTskFrom, Uint16 cmd, void *pPrm, Uint16 flags);
int OSA_tskAckOrFreeMsg(OSA_MsgHndl *pMsg, int ackRetVal);
int OSA_tskWaitMsg(OSA_TskHndl *pTsk, OSA_MsgHndl **pMsg);
int OSA_tskCheckMsg(OSA_TskHndl *pTsk, OSA_MsgHndl **pMsg);
int OSA_tskWaitCmd(OSA_TskHndl *pTsk, OSA_MsgHndl **pMsg, Uint16 waitCmd);
int OSA_tskFlushMsg(OSA_TskHndl *pTsk);

int    OSA_tskSetState(OSA_TskHndl *pPrc, Uint32 curState);
Uint32 OSA_tskGetState(OSA_TskHndl *pPrc);

#endif /* _OSA_TSK_H_ */




