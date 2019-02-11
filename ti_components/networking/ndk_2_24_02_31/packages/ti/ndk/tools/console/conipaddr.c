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
 * ======== conipaddr.c ========
 *
 * Console command processing which allows easy configuration of NIMU 
 * interfaces. This also indicates how the NIMU IOCTL's can be used
 * by various application developers.
 *
 */

#include <netmain.h>
#include <_stack.h>
#include <_oskern.h>
#include "console.h"

_extern HANDLE  IFIndexGetHandle( uint Index );

/*********************************************************************
 * FUNCTION NAME : ConDisplayNIMUObject
 *********************************************************************
 * DESCRIPTION   :
 *  The function is used to display a NIMU Object.
 *********************************************************************/
static void ConDisplayNIMUObject (char* objId)
{
    char        IPString[16];
    UINT16      dev_index;
    UINT8       mac_address[6];
    UINT16      mtu;
    int         ret_code;
    NIMU_IF_REQ if_req;
    UINT8       dev_name[MAX_INTERFACE_NAME_LEN];
    CI_IPNET    NA;

    /* Initialize the IP Address block. */
    bzero (&NA, sizeof(CI_IPNET));

    /* Get the device index; by first trying it to be an identifier. */
    dev_index = atoi (objId);
    if (dev_index == 0)
    {
        if (strlen(objId) < MAX_INTERFACE_NAME_LEN) {
            /*
             * Error: Unable to convert to integer; maybe we were given a name
             */
            strcpy (if_req.name, objId);
        }
        else {
            ConPrintf("ConDisplayNIMUObject: error object ID name too long\n");
        }

        if_req.index = 0;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            ConPrintf (
            "ConDisplayNIMUObject: Error: Incorrect device index specified\n");
            return;
        }
    }

    /* Control comes here implies that we have a valid device index. 
     *  - At this point in time we start collecting the various properties of
     *    the NIMU Network Interface object 
     * Configure the NIMU Network Interface Identifier. */
    if_req.name[0] = 0;
    if_req.index   = dev_index;

    /* Get the device MTU */
    ret_code = NIMUIoctl (NIMU_GET_DEVICE_MTU, &if_req, &mtu, sizeof(UINT16));
    if (ret_code < 0)
    {
        ConPrintf (
                "ConDisplayNIMUObject: NIMUIOCTL (NIMU_GET_DEVICE_MTU) Failed with error code: %d\n",
                ret_code);
        return;
    }

    /* Get the device MAC Address */
    ret_code = NIMUIoctl (NIMU_GET_DEVICE_MAC, &if_req, &mac_address, sizeof(mac_address));
    if (ret_code < 0)
    {
        ConPrintf (
                "ConDisplayNIMUObject: NIMUIOCTL (NIMU_GET_DEVICE_MAC) Failed with error code: %d\n",
                ret_code);
        return;
    }

    /* Get the device NAME. */
    ret_code = NIMUIoctl (NIMU_GET_DEVICE_NAME, &if_req, &dev_name[0], sizeof(dev_name));
    if (ret_code < 0)
    {
        ConPrintf (
                "ConDisplayNIMUObject: NIMUIOCTL (NIMU_GET_DEVICE_NAME) Failed with error code: %d\n",
                ret_code);
        return;
    }

    /* Now we have all the information; display it on the console. */
    ConPrintf ("Interface Name: %s\n", dev_name);
    ConPrintf ("Interface Id  : %d\n", dev_index);
 
    /* Print the IP address information only if one is present. */
    if (CfgGetImmediate( 0, CFGTAG_IPNET, if_req.index, 1, sizeof(NA), (UINT8 *)&NA) == sizeof(NA))
    {
        /* Yes the device was configured and we got the IP address/Mask */
        NtIPN2Str (NA.IPAddr, IPString);
        ConPrintf ("IP Address    : %s\n", IPString);
        NtIPN2Str (NA.IPMask, IPString);
        ConPrintf ("IP Mask       : %s\n", IPString);
    }
    
    ConPrintf ("MTU           : %d bytes\n", mtu);
    ConPrintf ("MAC Address   : 0x%x-0x%x-0x%x-0x%x-0x%x-0x%x\n\n\n", 
                    mac_address[0], mac_address[1], mac_address[2],
                    mac_address[3], mac_address[4], mac_address[5]);
    return;
}

/*********************************************************************
 * FUNCTION NAME : ConConfigureNIMUObject
 *********************************************************************
 * DESCRIPTION   :
 *  The function is used to configure the NIMU object with the 
 *  information specified. 
 *********************************************************************/
/* ARGSUSED */
static void ConConfigureNIMUObject 
(
    int   ntok, /* Number of Tokens                 */
    char* tok1, /* NIMU Interface Identification    */
    char* tok2, /* IP Address                       */
    char* tok3  /* NET Mask                         */
)
{
    UINT16      dev_index;    
    int         ret_code;
    NIMU_IF_REQ if_req;
    CI_IPNET    NA;
    HANDLE      hNet;

    /* Get the device index; by first trying it to be an identifier. */
    dev_index = atoi (tok1);
    if (dev_index == 0)
    {
        if (strlen(tok1) < MAX_INTERFACE_NAME_LEN) {
            /* Error: Unable to convert to integer; maybe we were given a name. */
            strcpy (if_req.name, tok1);
        }
        else {
            ConPrintf(
                    "ConConfigureNIMUObject: Error: object ID name too long\n");
        }

        if_req.index = 0;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            ConPrintf (
                    "ConConfigureNIMUObject: Error: Device does not exist.\n");
            return;
        }
    }

    /* Initialize the memory. */
    bzero (&NA, sizeof(CI_IPNET));

    /* Token2 is always the IP Address and Token3 is the Netmask. */
    NA.NetType = CFG_NETTYPE_DYNAMIC;
    NA.IPAddr  = inet_addr(tok2);
    NA.IPMask  = inet_addr(tok3);

    /* Add the IP Address to the configuration. */
    ret_code = CfgAddEntry( 0, CFGTAG_IPNET, dev_index, CFG_ADDMODE_NOSAVE | CFG_ADDMODE_UNIQUE,
                           sizeof(CI_IPNET), (UINT8 *)&NA, &hNet );
    if (ret_code < 0)
    {
        ConPrintf (
            "ConConfigureNIMUObject: Error: Unable to configure the device.\n");
        return;
    }
    return;
}

/*********************************************************************
 * FUNCTION NAME : ConConfigureMTU
 *********************************************************************
 * DESCRIPTION   :
 *  The function is used to configure the MTU of the NIMU Network 
 *  Interface Object.
 *********************************************************************/
/* ARGSUSED */
static void ConConfigureMTU
(
    int   ntok, /* Number of Tokens                 */
    char* tok1, /* NIMU Interface Identification    */
    char* tok3  /* MTU                              */
)
{
    UINT16      mtu;
    UINT16      dev_index;    
    int         ret_code;
    NIMU_IF_REQ if_req;

    /* Get the device index; by first trying it to be an identifier. */
    dev_index = atoi (tok1);
    if (dev_index == 0)
    {
        if (strlen(tok1) < MAX_INTERFACE_NAME_LEN) {
            /* Error: Unable to convert to integer; maybe we were given a name. */
            strcpy (if_req.name, tok1);
        }
        else {
            ConPrintf("ConConfigureMTU: error object ID name too long\n");
        }

        if_req.index = 0;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            ConPrintf ("ConConfigureMTU: Error: Device does not exist.\n");
            return;
        }
    }
    
    /* Extract the device MTU. */
    mtu = atoi (tok3);
    if (mtu != 0)
    {
        /* Populate the NIMU Interface Identification structure. */
        if_req.name[0] = 0;
        if_req.index   = dev_index;

        /* Set the device MTU */
        ret_code = NIMUIoctl (NIMU_SET_DEVICE_MTU, &if_req, &mtu, sizeof(UINT16));
        if (ret_code < 0)
        {
            ConPrintf (
            "ConConfigureMTU: NIMUIOCTL (NIMU_SET_DEVICE_MTU) Failed with error code: %d\n",
            ret_code);
            return;
        }
    }
    else
    {
        /* MTU specified was not correct. */
        ConPrintf ("ConConfigureMTU: Error: Invalid MTU specified.\n");
        return;
    }

    /* Device has been configured successfully. */
    return;
}

/*********************************************************************
 * FUNCTION NAME : ConConfigureMAC
 *********************************************************************
 * DESCRIPTION   :
 *  The function is used to configure the MAC address of the NIMU Network 
 *  Interface Object.
 *********************************************************************/
/* ARGSUSED */
static void ConConfigureMAC
(
    int   ntok, /* Number of Tokens                 */
    char* tok1, /* NIMU Interface Identification    */
    char* tok3  /* MAC Address                      */
)
{
    UINT16      dev_index;    
    int         ret_code;
    NIMU_IF_REQ if_req;
    UINT8       mac_address[6];
    char*       ptr_mac_address;
    UINT16      index = 0;

    /* Get the device index; by first trying it to be an identifier. */
    dev_index = atoi (tok1);
    if (dev_index == 0)
    {
        if (strlen(tok1) < MAX_INTERFACE_NAME_LEN) {
            /* Error: Unable to convert to integer; maybe we were given a name. */
            strcpy (if_req.name, tok1);
        }
        else {
            ConPrintf("ConConfigureMAC: Error object ID name too long\n");
        }

        if_req.index = 0;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            ConPrintf ("ConConfigureMAC: Error: Device does not exist.\n");
            return;
        }
    }

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
        ConPrintf ("ConConfigureMAC: Invalid Format for MAC Address\n");
        return;
    }
    
    /* Populate the NIMU Interface Identification structure. */
    if_req.name[0] = 0;
    if_req.index   = dev_index;

    /* Set the device MAC Address */
    ret_code = NIMUIoctl (NIMU_SET_DEVICE_MAC, &if_req, &mac_address, sizeof(mac_address));
    if (ret_code < 0)
    {
        ConPrintf (
        "ConConfigureMAC: NIMUIOCTL (NIMU_SET_DEVICE_MAC) Failed with error code: %d\n",
        ret_code);
        return;
    }

    /* Device has been configured successfully. */
    return;
}

/*********************************************************************
* FUNCTION NAME : ConRemoveIPAddress
*********************************************************************
* DESCRIPTION   :
* This function removes the IP address(BIND object) associated with a
* NIMU object using the information passed.
*********************************************************************/
/* ARGSUSED */
static void ConRemoveIPAddress 
(
    int   ntok, /* Number of Tokens                 */
    char* tok1, /* NIMU Interface Identification    */
    char* tok3  /* IP Address                         */
)
{
    UINT16      dev_index;    
    int         ret_code;
    NIMU_IF_REQ if_req;
    CI_IPNET    NA;
    HANDLE      hIF;
    HANDLE      hCfgIpAddr;

    /* Get the device index; by first trying it to be an identifier. */
    dev_index = atoi (tok1);
    if (dev_index == 0)
    {
        if (strlen(tok1) < MAX_INTERFACE_NAME_LEN) {
            /* Error: Unable to convert to integer; maybe we were given a name. */
            strcpy (if_req.name, tok1);
        }
        else {
            ConPrintf("ConRemoveIPAddress: Error object ID name too long\n");
        }

        if_req.index = 0;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            ConPrintf ("ConRemoveIPAddress: Error: Device does not exist.\n");
            return;
        }
    }

    {
        NIMU_IF_REQ ifreq;

        /* Initialize the NIMU Interface Object. */
        mmZeroInit (&ifreq, sizeof(NIMU_IF_REQ));

        /*
         *  We are interested in receiving the handle associated with 'index'
         *  Item
         */
        ifreq.index = dev_index;
        if (NIMUIoctl(NIMU_GET_DEVICE_HANDLE, &ifreq, &hIF, sizeof(HANDLE)) < 0)
                return;
    }

    /* Initialize the memory. */
    bzero (&NA, sizeof(CI_IPNET));

    /* Token3 is the IP Address. */
    NA.NetType = CFG_NETTYPE_DYNAMIC;
    NA.IPAddr  = inet_addr(tok3);
                                          
    if (!BindFindByHost(hIF,  NA.IPAddr)) {
        ConPrintf(
            "ConRemoveIPAddress: Error: Unable to find the given IP address binding for device.\n");
        return;
    }

    ret_code = CfgGetEntry(0, CFGTAG_IPNET, dev_index, 1, &hCfgIpAddr);
    if(ret_code <= 0)
    {
        ConPrintf ("ConRemoveIPAddress: Error: Unable to retrieve IP address configuration.\n");
        return;
    }

    /* Remove the IP Address from the configuration. */
    ret_code = CfgRemoveEntry( 0, hCfgIpAddr );
    if (ret_code < 0)
    {
        ConPrintf ("ConRemoveIPAddress: Error: Unable to remove the IP Address configuration.\n");
        return;
    }

    return;
} 

/*********************************************************************
 * FUNCTION NAME : ConCmdIPAddr
 *********************************************************************
 * DESCRIPTION   :
 *  The function is the command handler for the IPAddr command. 
 *********************************************************************/
/* ARGSUSED */
void ConCmdIPAddr(int ntok, char *tok1, char *tok2, char *tok3, char* tok4)
{
    int     ret_code;
    UINT16* dev_table;
    UINT16  num_device;
    int     index = 0;

    /* Do we need to display information for all devices. */
    if (ntok == 1 && !strcmp(tok1, "all"))
    {
        /* YES. Get a number of all devices present in the system.*/
        ret_code = NIMUIoctl (NIMU_GET_NUM_NIMU_OBJ, NULL, &num_device, sizeof(num_device));
        if (ret_code < 0)
        {
            ConPrintf ("ConCmdIPAddr: NIMUIOCTL (NIMU_GET_NUM_NIMU_OBJ) Failed with error code: %d\n",ret_code);
            return;
        }

        /* Allocate memory for the device table*/
        dev_table = mmAlloc(num_device * sizeof(UINT16)); 
        if (dev_table == NULL)
        {
            ConPrintf ("ConCmdIPAddr: OOM Error\n");
            return;
        }

        /* Get a list of all device index. */
        ret_code = NIMUIoctl (NIMU_GET_ALL_INDEX, NULL, dev_table, num_device*sizeof(UINT16));
        if (ret_code < 0)
        {
            ConPrintf ("ConCmdIPAddr: NIMUIOCTL (NIMU_GET_ALL_INDEX) Failed with error code: %d\n",ret_code);
            mmFree (dev_table);
            return;
        }

        /* Cycle through all the Device Index and print them out. */
        while (index < num_device)
        {
            char InterfaceId[3];

            /* Convert the interface handle to string and display the object. */
            NDK_sprintf (InterfaceId, "%d", dev_table[index]);
            ConDisplayNIMUObject (InterfaceId);

            /* Goto the next entry. */
            index++;
        }

        /* Cleanup the allocated memory. */
        mmFree (dev_table);
        return;            
    } 
    else if (ntok == 1)
    {
        /* Display the information <tok1> should be the Interface ID */ 
        ConDisplayNIMUObject (tok1);
    }
    else if ((ntok == 3) && !strcmp(tok2, "mac"))
    {
        /* This is the case where
         *  Tok1 -> Interface Identifier. 
         *  Tok2 -> "mac"
         *  Tok3 -> MAC Address seperated by '-'. 
         * Use this to configure the MAC address of the NIMU network object. */
        ConConfigureMAC(ntok, tok1, tok3);
    }
    else if ((ntok == 3) && !strcmp(tok2, "mtu"))
    {
        /* This is the case where
         *  Tok1 -> Interface Identifier. 
         *  Tok2 -> "mtu"
         *  Tok3 -> MTU value 
         * Use this to change the MTU of the NIMU Network object. */
        ConConfigureMTU(ntok, tok1, tok3);
    }
    else if ((ntok == 3) && !strcmp(tok2, "del"))
    {
        /* This is the case where
         *  Tok1 -> Interface Identifier. 
         *  Tok2 -> "del"
         *  Tok3 -> IP Address
         * Use this to delete the IP address of the NIMU Network object. */
        ConRemoveIPAddress(ntok, tok1, tok3);
    }
    else if (ntok == 3) 
    {
        /* This is the case where
         *  Tok1 -> Interface Identifier. 
         *  Tok2 -> IP Address.
         *  Tok3 -> Netmask. */
        ConConfigureNIMUObject(ntok, tok1, tok2, tok3);
    }
    else
    {
        /* Print the usage. */
        ConPrintf("\n[ipaddr Command]\n");
        ConPrintf("\nUse this to configure NIMU Objects\n\n");
        ConPrintf("ipaddr all                       - Display configuration for all NIMU object\n");
        ConPrintf("ipaddr <if>                      - Display configuration for the specified NIMU object\n");
        ConPrintf("ipaddr <if> mac <MAC-ADDR>       - Configure the MAC Address of the NIMU Object\n");
        ConPrintf("ipaddr <if> mtu <MTU>            - Configure the MTU of the NIMU Object\n");
        ConPrintf("ipaddr <if> <ip_addr> <netmask>  - Configure the IP Address/Netmask\n");
        ConPrintf("ipaddr <if> del <ip_addr>        - Delete the IP Address from specified interface\n");
    }
    return;
}

