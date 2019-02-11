/*
 * Copyright (c) 2014, Texas Instruments Incorporated
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
 * ======== convlan.c ========
 *
 *  EXAMPLE Usage of the VLAN API for creation and deletion of VLAN Devices
 *  The VLAN Support is available only if the NIMU architecture is built in
 *
 */

#include <netmain.h>
#include <_stack.h>
#include <_oskern.h>
#include "console.h"

/* VLAN support is available only if NIMU is available. */

/*********************************************************************
 * FUNCTION NAME : CmdVLANAdd
 *********************************************************************
 * DESCRIPTION   :
 *  The function creates a VLAN device.
 *********************************************************************/
static void CmdVLANAdd(char *tok1, char *tok2, char *tok3)
{
    int         vlan_dev_index;
    UINT8       prio_mapping[8];
    UINT16      src_index;
    UINT16      vlan_id;
    UINT8       def_priority;
    UINT8       index;
    NIMU_IF_REQ nimu_ifreq;

    /* First Token: This is the source interface on which the VLAN device is
     * being created */
    src_index = atoi (tok1);
    if (src_index == 0)
    {
        if (strlen(tok1) < MAX_INTERFACE_NAME_LEN) {
            /* Error: Unable to convert to integer; maybe we were given a name. */
            strcpy (nimu_ifreq.name, tok1);
        }
        else {
            ConPrintf("CmdVLANAdd: error VLAN device name too long\n");
        }

        nimu_ifreq.index = 0;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &nimu_ifreq, &src_index, sizeof(src_index)) < 0)
        {
            ConPrintf ("Error: Source Interface specified does not exist.\n");
            return;
        }
    }

    /* Second Token: This is the VLAN Identifier */
    vlan_id = atoi (tok2);
    if (vlan_id == 0)
    {
        ConPrintf ("Incorrect VLAN Id specified.\n");
        return;
    }

    /* Third Token: This is the VLAN Identifier */
    def_priority = atoi (tok3);

    /* By default: We configure the priority mapping to be as follows:-
     *  Priority  | VLAN User Priority 
     *  -----------------------------------
     *      0     | 0
     *      1     | 1
     *      2     | 2
     *      3     | 3
     *      4     | 4
     *      5     | 5
     *      6     | 6
     *      7     | 7   */
    for (index = 0; index < 8; index++)
        prio_mapping[index] = index;

    /* Use the VLAN API to create a new VLAN device. */    
    vlan_dev_index = VLANAddDevice (src_index, vlan_id, def_priority, prio_mapping);
    if (vlan_dev_index < 0)
    {
        ConPrintf ("Error: Unable to create a VLAN Device errcode=%d\n", vlan_dev_index);
        return;
    }
    ConPrintf ("Successfully created new VLAN Device %d\n", vlan_dev_index);
    return;
}

/*********************************************************************
 * FUNCTION NAME : CmdVLANDel
 *********************************************************************
 * DESCRIPTION   :
 *  The function deletes a previously created VLAN device.
 *********************************************************************/
static void CmdVLANDel(char *tok1)
{
    UINT16      dev_index;
    int         ret_code;
    NIMU_IF_REQ nimu_ifreq;

    /* Get the device index which needs to be deleted. */
    dev_index = atoi (tok1);
    if (dev_index == 0)
    {
        if (strlen(tok1) < MAX_INTERFACE_NAME_LEN) {
            /* Error: Unable to convert to integer; maybe we were given a name. */
            strcpy (nimu_ifreq.name, tok1);
        }
        else {
            ConPrintf("CmdVLANDel: error VLAN device name too long\n");
        }

        nimu_ifreq.index = 0;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &nimu_ifreq, &dev_index, sizeof(dev_index)) < 0)
        {
            ConPrintf ("Error: Device does not exist.\n");
            return;
        }
    }

    /* Delete the VLAN Device */
    ret_code = VLANDelDevice (dev_index);
    if (ret_code < 0)
    {
        ConPrintf ("Error: Unable to delete the VLAN Device Error:%d\n", ret_code);
        return;            
    }
    ConPrintf ("VLAN Device %d has been deleted from the system.\n", dev_index);
    return;
}

/*********************************************************************
 * FUNCTION NAME : CmdVLANSend
 *********************************************************************
 * DESCRIPTION   :
 *  The function is used to send a packet. The IPAddress to which the 
 *  packet is transmitted is passed as a token. 
 *
 * NOTES         :
 *  The function should has been provided in the VLAN module to 
 *  indicate to users on how priority and mappings exist. If the result
 *  of 'routing' the 'IPAddress' is a non VLAN interface the markings
 *  are not used at all. Thus users should ensure that a VLAN device
 *  has been created and the routing table is correct to ensure that 
 *  the result of routing the 'IPAddress' is a VLAN interface
 *********************************************************************/
static void CmdVLANSend (char* IPAddress)
{
    SOCKET              s;
    struct sockaddr_in  sin1;
	struct sockaddr_in  to;
    char                data_payload[50];
    UINT16              payload_len;
    UINT16              priority;

    /* Create the socket */
    s = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET)
    {
        ConPrintf ("Error: Unable to open the socket.\n");
        return;
    }

    /* Bind the socket. */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family = AF_INET;
    sin1.sin_port   = htons(10000);
    if (bind (s, (PSA)&sin1, sizeof(sin1)) < 0 )
    {
        ConPrintf ("Error: Unable to bind the socket.\n");
        fdClose (s);
        return;
    }
   
    /* Once the socket has been bound; initialize the structure to whom we 
     * are sending the packet. */ 
    bzero( &to, sizeof(struct sockaddr_in) );
    to.sin_family      = AF_INET;
    to.sin_port        = htons(10000);
	to.sin_addr.s_addr = inet_addr (IPAddress);

    /* Create a data payload. */
    strcpy (data_payload, "Testing Socket Priority");
    payload_len = strlen (data_payload);

    /* Send out the packet; this should go out with default priority. */
    if (sendto (s, &data_payload[0], payload_len, 0,(struct sockaddr *)&to, sizeof(to)) < 0)
    {
        ConPrintf ("Error: Unable to send data payload for DEFAULT Priority\n");
        fdClose (s);
        return;
    }

    /* Wait for some time before proceeding to the next test cases. */
    TaskSleep (1000);

    /* TEST Case: 
     * Configure an incorrect priority level. The setsockopt should FAIL. Valid Priority 
     * levels are only from 0 - 7. The value 0xFFFF is a special case to 'reset' the 
     * socket back to 'default' priority mode. */
    priority = 0x8;
    if (setsockopt(s, SOL_SOCKET, SO_PRIORITY, &priority, sizeof(priority)) < 0)
    {
        ConPrintf ("TEST Case Passed: Priority 0x%x is incorrect and was detected\n", priority);
    }
    else
    {
        ConPrintf ("TEST Case Failed: Priority 0x%x is incorrect and was NOT detected\n", priority);
        fdClose (s);
        return;
    }

    /* TEST Case:
     *  Set the socket priority to all valid levels and send out a packet. Sniff the packets on 
     *  Ethereal to ensure the markings are correct. */
    priority = 0;
    while (priority < 8)
    {
        /* Set the socket priority */
        if (setsockopt(s, SOL_SOCKET, SO_PRIORITY, &priority, sizeof(priority)) < 0)
        {
            ConPrintf ("TEST Case Failed: Priority 0x%x could not be set error=%d\n", priority, fdError());
            fdClose (s);
            return;
        }

        /* Create an appropriate data payload */
        NDK_sprintf(data_payload, "Testing Socket Priority %d", priority);
        payload_len = strlen (data_payload);

        /* Send the packet out. */
        if (sendto (s, &data_payload[0], payload_len, 0,(struct sockaddr *)&to, sizeof(to)) < 0)
        {
            ConPrintf ("Error: Unable to send data payload for Priority %d\n", priority);
            fdClose (s);
            return;
        }

        /* Goto the next priority. */
        ConPrintf ("Packet with priority %d has been sent\n", priority);
        priority = priority + 1;
    }

    /* Once we have tested all the priorities and sent packets out. We move back to default priority 
     * and send out another packet. */
    priority = PRIORITY_UNDEFINED;
    if (setsockopt(s, SOL_SOCKET, SO_PRIORITY, &priority, sizeof(priority)) < 0)
    {
        ConPrintf ("TEST Case Failed: Priority 0x%x could not be set error=%d\n", priority, fdError());
        fdClose (s);
        return;
    }

    /* Create an appropriate data payload */
    NDK_sprintf(data_payload, "Testing Socket Priority %d", priority);
    payload_len = strlen (data_payload);    
    if (sendto (s, &data_payload[0], payload_len, 0,(struct sockaddr *)&to, sizeof(to)) < 0)
    {
        ConPrintf ("Error: Unable to send data payload for DEFAULT Priority\n");
        fdClose (s);
        return;
    }

    /* Close the socket. */
    ConPrintf ("Packet with default priority has been sent\n");
    fdClose (s);
    return;
}

/*********************************************************************
 * FUNCTION NAME : ConCmdVLAN
 *********************************************************************
 * DESCRIPTION   :
 *  The function is the command handler for the VLAN command. 
 *********************************************************************/
void ConCmdVLAN( int ntok, char *tok1, char *tok2, char *tok3, char* tok4 )
{
    /* Check for the VLAN Add command */ 
    if ((ntok == 4) && !strcmp( tok1, "add"))
    {
        CmdVLANAdd (tok2, tok3, tok4);
    }
    /* Check for the VLAN Del command */ 
    else if ((ntok == 2) && !strcmp( tok1, "del"))
    {
        CmdVLANDel (tok2);
    }
    /* Check for the VLAN Send command. */
    else if ((ntok == 2) && !strcmp( tok1, "send"))
    {
        CmdVLANSend (tok2);
    }
    else
    {
        /* Print the usage. */
        ConPrintf("\n[vlan Command]\n");
        ConPrintf("\nUse this to add/del & configure VLAN Devices\n\n");
        ConPrintf("vlan add  <srcif> <vlan_id> <default prio>   - Adds a VLAN Device \n");
        ConPrintf("vlan del  <vlan_id_index>                    - Deletes a VLAN Device \n");
        ConPrintf("vlan send <dst_ip>                           - Tests SO_PRIORITY option by sending packets  \n");
    }

    return;
}

