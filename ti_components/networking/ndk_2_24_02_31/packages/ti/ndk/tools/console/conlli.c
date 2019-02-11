/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 * ======== conlli.c ========
 *
 * Console command processing which allows easy configuration of Static
 * ARP (LLI) entries.
 *
 */

#include <netmain.h>
#include <_stack.h>
#include <_oskern.h>
#include "console.h"

static char *LLIErr = "\nError in command line. Type 'lli' for help\n";

/**
 *  @b Description
 *  @n  
 *      Function to print, add, and remove static LLI/Host route entries. 
 *
 *  @param[in]  ntok
 *      Number of tokens to process.
 *
 *  @param[in]  tok1
 *      Token 1. Must contain a valid command to process like print / add /
 *      delete.
 *
 *  @param[in]  tok2
 *      Token 2. Only required for "add" / "delete" commands. This token 
 *      must contain a valid IPv4 address.
 *
 *  @param[in]  tok3
 *      Token 3. Only required for "add" command. This token must contain a 
 *      valid 6 byte MAC Address.
 *
 *  @retval
 *      Not Applicable
 */
void ConCmdLLI( int ntok, char *tok1, char *tok2, char *tok3 )
{
    UINT8           mac_address[6];
    char*           ptr_mac_address;
    UINT16          index = 0, i;
    struct in_addr  in1;
    LLI_INFO*       pStaticArpTable = NULL;
    LLI_INFO*       pStaticArpEntry = NULL;
	UINT32			NumStaticEntries;
    char   			str[40];

    /* Check for 'lli print' */
    if( ntok == 1 && !stricmp( tok1, "print" ) )
    {
        LLIGetStaticARPTable( &NumStaticEntries, &pStaticArpTable );

        ConPrintf("\nNumber of Static ARP Entries: %d \n", NumStaticEntries);

        if( NumStaticEntries != 0 && pStaticArpTable )
        {
           	ConPrintf("\nSNo.      IP Address         MAC Address  \n");
            ConPrintf("------    -------------      --------------- \n");

            pStaticArpEntry = (LLI_INFO *) list_get_head( (LIST_NODE **)&pStaticArpTable );

            i = 0;

            while( pStaticArpEntry )
            {
                i ++;

                ConPrintf( "%d ", i);
            
                NtIPN2Str( pStaticArpEntry->IPAddr, str );
                ConPrintf( "        %-15s  ",str);

                ConPrintf( "  %02X:%02X:%02X:%02X:%02X:%02X",
                           pStaticArpEntry->MacAddr[0], pStaticArpEntry->MacAddr[1], pStaticArpEntry->MacAddr[2],
                           pStaticArpEntry->MacAddr[3], pStaticArpEntry->MacAddr[4], pStaticArpEntry->MacAddr[5] );

                ConPrintf("\n");

                pStaticArpEntry = (LLI_INFO *) list_get_next( (LIST_NODE *)pStaticArpEntry );
            }

            LLIFreeStaticARPTable( pStaticArpTable );   
        }
    }
    /* Check for 'lli add x.x.x.x xx-xx-xx-xx-xx-xx' */
    else if( ntok == 3 && !stricmp( tok1, "add" ) )
    {
        /* Extract the MAC Address: We accept the MAC Address in either of the following 
        * formats:-
        *  a) 00-01-02-03-04-05
        *  b) 00:01:02:03:04:05 */
        ptr_mac_address = strtok (tok3, "-:");
        while (1)
        {
            /* Break out of the loop; when there are no more tokens. */
            if (ptr_mac_address == NULL)
                break;

            /* Convert to number. */
            mac_address[index] = (UINT8)strtol (ptr_mac_address, NULL, 16);

            /* Get the next token */
            ptr_mac_address = strtok (NULL, "-:");
            index = index + 1;
        }

        /* When we get out of the loop; make sure we have the entire MAC Address */
        if (index != 6)
        {
            ConPrintf ("Invalid Format for MAC Address\n");
            ConPrintf(LLIErr);
            return;
        }

        if( inet_aton(tok2,&in1)  )
        {
            if( !LLIAddStaticEntry( in1.s_addr, mac_address ) )
			{
                ConPrintf("\nLLI Entry created\n\n");
			}
            else
			{
                ConPrintf("\nLLI Entry not created\n\n");
			}
        }
        else
            ConPrintf(LLIErr);
    }
    /* Check for 'lli delete x.x.x.x' */
    else if( ntok == 2 && !stricmp( tok1, "delete" ) )
    {
        if( inet_aton(tok2,&in1) )
        {
            if( !LLIRemoveStaticEntry( in1.s_addr ) )
			{
                ConPrintf("\nLLI Entry removed\n\n");
			}
            else
			{
                ConPrintf("\nLLI Entry not found\n\n");
			}
        }
        else
            ConPrintf(LLIErr);
    }
    else if( ntok == 0 )
    {
        ConPrintf("\n[lli Command]\n");
        ConPrintf("\nCalled to print, add, or delete static LLI (ARP) entries. ");
        ConPrintf("\nIP Addresses must be used in the traditional x.x.x.x format.\n\n");
        ConPrintf("\nMAC Addresses can be used in either of xx-xx-xx-xx-xx-xx / xx:xx:xx:xx:xx:xx formats.\n\n");
        ConPrintf("lli print                    - Print out all the static LLI entries configured in the system. \n");
        ConPrintf("lli add IpAddr MacAddr       - Create new static LLI entry \n");
        ConPrintf("lli delete IpAddr            - Delete static LLI entry\n\n");
    }
    else
        ConPrintf(LLIErr);
}
