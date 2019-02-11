/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 * ======== lliif.h ========
 *
 */

#ifndef _C_LLIIF_INC
#define _C_LLIIF_INC  /* #defined if this .h file has been included */

/*----------------------------------------------------------------------- */
/* Global Task Information */

/* Defined Messages */
#define MSG_LLI_TIMER                   (ID_LLI*MSG_BLOCK + 0)

/** 
 * @brief 
 *  This structure describes the LLI/ARP Information Object.
 *
 * @details
 *  This data structure is used by the LLI module to populate
 *  LLI/ARP Entry information contained in the NDK Kernel
 *  in a simple, user-friendly way to the application.
 *
 */
typedef struct _lli_info 
{
    /**
     * @brief       Links to other LLI_INFO Objects
     */
    LIST_NODE       Links;           

    /**
     * @brief       Boolean Flag to indicate whether this LLI
     *              entry is a static / dynamic entry.
     */
    UINT8           IsStatic;

    /**
     * @brief       The 4 byte IPv4 address associated with this
     *              LLI/ARP Entry.
     */
    IPN             IPAddr;

    /**
     * @brief       The 6 byte Ethernet MAC address associated with this
     *              LLI/ARP Entry.
     */
    UINT8           MacAddr[6];          
} LLI_INFO;

/* Hook function to give access to received ARP packets */
typedef void(*LLI_ReportARP)(void * data);
extern void LLI_setARPHook(LLI_ReportARP fxn);

/* LLI Access Functions */
_extern HANDLE LLINew( HANDLE hRt, UINT8 *pMacAddr );
_extern void   LLIFree( HANDLE hLLI );
_extern void   LLITxIpPacket( PBM_Pkt *pPkt, IPN IPDst );
_extern HANDLE LLIValidateRoute( HANDLE hIF, IPN IPAddr, UINT8 *pMacAddr );
_extern uint   LLIGetMacAddr( HANDLE hLLI, UINT8 *pMacAddr, uint MaxLen );
_extern void   LLIRxPacket( PBM_Pkt *pPkt );
_extern void   LLIGenArpPacket( HANDLE hIF, IPN IPDst );
_extern UINT32 LLIGetValidTime( HANDLE hLLI );

/* APIs to add/modify/remove/print Static LLI Entries 
 * configured in the system.
 */
_extern int LLIRemoveStaticEntry( IPN IPAddr );
_extern int LLIAddStaticEntry( IPN IPAddr, UINT8 *pMacAddr );
_extern void LLIGetStaticARPTable( UINT32* pNumEntries, LLI_INFO** pStaticArpTable );
_extern void LLIFreeStaticARPTable (LLI_INFO* pStaticArpTable);

#endif
