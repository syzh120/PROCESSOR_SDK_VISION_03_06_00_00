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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <system_cfg.h>
#include <src/include/chains.h>
#include <src/include/chains_common.h>

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Uncommented below line to disable user input
 *******************************************************************************
 */
//#define CHAINS_DISABLE_GET_CHAR

/**
 *******************************************************************************
 * \brief Max Size of the input string in characters.
 *******************************************************************************
 */
#define MAX_INPUT_STR_SIZE  (80)

/**
 *******************************************************************************
 * \brief Menu setting display string.
 *******************************************************************************
 */
extern char gChains_menuUseCases[];

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
extern char gChains_runTimeMenu[];

/**
 *******************************************************************************
 * \brief Run Time Menu string for Network mode
 *******************************************************************************
 */
#if defined(NSP_TFDTP_INCLUDE)
static char gChains_networkModeMenu[] = {
    "\r\n "
    "\r\n Select Network Mode, "
    "\r\n --------------------"
    "\r\n 1: TFDTP "
    "\r\n 2: TCP/IP "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};
#endif

/**
 *******************************************************************************
 *
 * \brief   Read a charater from UART or CCS console
 *
 * \return character that is read
 *
 *******************************************************************************
*/
char Chains_readChar()
{
    #if (defined(ENABLE_UART_LOG) || defined(ENABLE_NETWORK_LOG)) || (defined(ENABLE_CCS_LOG))
    Int8 ch[80];
    #endif

    #ifdef ENABLE_UART_LOG
    uartRead(ch);
    #endif
    #ifdef ENABLE_NETWORK_LOG
    {
        Int32 NetworkCons_rxReadChar(UInt8 *data);

        NetworkCons_rxReadChar((UInt8*)ch);
    }
    #endif
    #ifdef ENABLE_CCS_LOG
    fgets((char*)ch, MAX_INPUT_STR_SIZE, stdin);
    if(ch[1] != '\n' || ch[0] == '\n')
    ch[0] = '\n';
    #endif

    #if (defined(ENABLE_UART_LOG) || defined(ENABLE_NETWORK_LOG)) || (defined(ENABLE_CCS_LOG))
    return ch[0];
    #endif
}

/**
 *******************************************************************************
 *
 * \brief   Run time Menu selection
 *
 *          This functions displays the run time options available
 *          And receives user input and calls corrosponding functions run time
 *          Instrumentation logs are printing routine is called in same function
 *
 *******************************************************************************
*/
char Chains_menuRunTime()
{
    Vps_printf(gChains_runTimeMenu);

    return Chains_readChar();
}


/**
 ******************************************************************************
 *
 * \brief Set Network Rx mode for Null Source link
 *
 * \param  pPrm  [IN]  NullSourceLink Create time Params
 *
 ******************************************************************************
 */
void ChainsCommon_networkRxSetMode(NetworkRxLink_CreateParams *pPrm)
{

#if !defined(NSP_TFDTP_INCLUDE)
    Vps_printf("Chains: Using TCP/IP\n");
    pPrm->dataRxMode = NETWORK_RX_LINK_DATA_RX_MODE_TCPIP;
#else
    char ch;
    UInt32 done = FALSE;

    while(!done)
    {
        Vps_printf("Chains: Null Source Link\n");
        Vps_printf(gChains_networkModeMenu);

        ch = Chains_readChar();
        switch(ch)
        {
            case '1':
                Vps_printf("Chains: Using TFDTP. Ensure using â€“-usetfdtp with network tools..\n");
                pPrm->dataRxMode = NETWORK_RX_LINK_DATA_RX_MODE_TFDTP;
                done = TRUE;
                break;
            case '2':
                Vps_printf("Chains: Using TCP/IP\n");
                pPrm->dataRxMode = NETWORK_RX_LINK_DATA_RX_MODE_TCPIP;
                done = TRUE;
                break;
            default:
                Vps_printf("Chains: Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
#endif
}

/**
 ******************************************************************************
 *
 * \brief Set Network Tx mode for Null link
 *
 * \param  pPrm  [IN]  NullLink Create time Params
 *
 * \return  None
 ******************************************************************************
 */
void ChainsCommon_networkTxSetMode(NetworkTxLink_CreateParams *pPrm)
{
#if !defined(NSP_TFDTP_INCLUDE)
    Vps_printf("Chains: Using TCP/IP\n");
    pPrm->transmitDataType = NETWORK_TX_LINK_TRANSMIT_TYPE_TCPIP;
#else
    char ch;
    UInt32 done = FALSE;

    while(!done)
    {
        Vps_printf("Chains: NetworkTx Link\n");
        Vps_printf(gChains_networkModeMenu);

        ch = Chains_readChar();
        switch(ch)
        {
            case '1':
                Vps_printf("Chains: Using TFDTP. Ensure using â€“-usetfdtp with network tools..\n");
                pPrm->transmitDataType = NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP;
                /* no. of retry count */
                pPrm->retryCount = NETWORK_TFDTP_RETRANSMIT_COUNT;
                done = TRUE;
                break;
            case '2':
                Vps_printf("Chains: Using TCP/IP\n");
                pPrm->transmitDataType = NETWORK_TX_LINK_TRANSMIT_TYPE_TCPIP;
                done = TRUE;
                break;
            default:
                Vps_printf("Chains: Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
#endif
}

