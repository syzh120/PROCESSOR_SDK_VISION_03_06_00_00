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
 * ======== ipv6.c ========
 *
 * The file has functions which handle the IPv6 Protocol.
 *
 */

#include <stkmain.h>
#include "ipv6.h"

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 *************************** Global Variables *************************
 **********************************************************************/

/* These are the well-defined IPv6 Global Addresses */
IP6N  IPV6_LINKLOCALMASK;
IP6N  IPV6_MULTICASTMASK;
IP6N  IPV6_UNSPECIFIED_ADDRESS;
IP6N  IPV6_LOOPBACK_ADDRESS;
IP6N  IPV6_HOST_MASK;
IP6N  IPV6_ALL_NODES_ADDRESS;
IP6N  IPV6_ALL_ROUTER_ADDRESS;

/* IPv6 Protocol Constants. */
const UINT32 IPV6_MAX_MULTICAST_SOLICIT      = 3;
const UINT32 IPV6_MAX_UNICAST_SOLICIT        = 3;
const UINT32 IPV6_RETRANS_TIME               = 1;
const UINT32 IPV6_DELAY_FIRST_PROBE_TIME     = 5;
const UINT32 IPV6_REACHABLE_TIME             = 30;
const UINT32 IPV6_MAX_RTR_SOLICITATION_DELAY = 1;
const UINT32 IPV6_RTR_SOLICITATION_INTERVAL  = 4;
const UINT32 IPV6_MAX_RTR_SOLICITATIONS      = 3;

/* Lifetime values for which the BINDING will remain valid. This defines INFINITE! */
const UINT32 INFINITE_LT = 0xFFFFFFFF;

/* Statistics block used for recording the IPv6 counters. */
IPV6_MCB ipv6mcb;

/**********************************************************************
 *************************** IPv6 Functions ***************************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      The function does the Layer4 Checksum computation.
 *
 *  @param[in]  ptr_l4Hdr
 *      Pointer to the Layer4 Header. This could be TCP, UDP
 *      or ICMPv6.
 *  @param[in]  ptr_pseudoHdr
 *      Pointer to the Pseudo Header.
 *
 *  @retval
 *      Returns the computed checksum.
 *
 *  @pre
 *      Ensure that the Checksum field in the layer4 header is set to 0
 *      before calling this function.
 */
UINT16 IPv6Layer4ComputeChecksum (UINT8* ptr_l4Hdr, PSEUDOV6* ptr_pseudoHdr)
{
    int     tmp1;
    UINT16  *pw;
    UINT32  TSum;

    /* Get header size in bytes */
    tmp1 = (int)ntohs(ptr_pseudoHdr->PktLen);

    /* Checksum the header */
    pw = (UINT16 *)ptr_l4Hdr;
    TSum = 0;
    for( ; tmp1 > 1; tmp1 -= 2 )
        TSum += (UINT32)*pw++;

#ifdef BIGENDIAN
    if( tmp1 )
        TSum += (UINT32)(*pw & 0xFF00);
#else
    if( tmp1 )
        TSum += (UINT32)(*pw & 0x00FF);
#endif

    /* Checksum the pseudo header */
    pw = (UINT16 *)ptr_pseudoHdr;
    for( tmp1=0; tmp1 < sizeof(PSEUDOV6)/2; tmp1++ )
        TSum += (UINT32)*pw++;

    /* Must continue to perform this op as long as upper bits exist! */
    while (TSum >> 16)
        TSum = (TSum&0xFFFF) + (TSum>>16);

    TSum = ~TSum;

    /* Note checksum is Net/Host byte order independent */
    return (UINT16)TSum;        
}

/** 
 *  @b Description
 *  @n  
 *      Utility Function which converts the IPv6 address to string format.
 *
 *  @param[in]   address
 *      The IPv6 Address in IP6N format.
 *  @param[out]  strIPAddress
 *      The IPv6 Address in String Format.
 *
 *  @retval
 *   Not Applicable.
 */
void IPv6IPAddressToString (IP6N address, char* strIPAddress)
{
    int     index              = 0;
    int     num_leading_zeroes = 0;
    int     zc                 = 0;
    char    tmpStr[6];
    char*   ptr_tmpStr;

    if (ipv6mcb.IsZeroCompressionEnabled)
    {
    /* Special Cases: Check for UNSPECIFIED Address and LOOPBACK Address */
    if((address.u.addr16[0] == 0) && (address.u.addr16[1] == 0) && (address.u.addr16[2] == 0) && 
       (address.u.addr16[3] == 0) && (address.u.addr16[4] == 0) && (address.u.addr16[5] == 0) &&
       (address.u.addr16[6] == 0))
    {
        if (address.u.addr16[7] == 0)
            NDK_sprintf (strIPAddress, "::");
        else
            NDK_sprintf (strIPAddress, "::%x",ntohs(address.u.addr16[7])); 
        return;
    }

    /* Initialize the memory. */
    *strIPAddress = 0;

    /* Cycle through the entire address. */
    while (index < 8)
    {
        /* Initialize the temp string at the beginning of each loop iteration. */
        ptr_tmpStr  = &tmpStr[0];
        *ptr_tmpStr = 0;

        /* Check if the address is 0. */
        if (address.u.addr16[index] == 0)
        {
            /* YES. This is 0. Now check if we have done zero-compression or not? Remember
             * the RFC states that we are allowed only once to do zero-compression. */
            if (zc == 0)
            {
                /* Zero compression has not been done. Count the number of leading zeroes. */
                num_leading_zeroes++;
            }
            else
            {
                /* Zero compression has been done. Simply print the address on the console now */
                if (index == 7)
                    NDK_sprintf (tmpStr, "%x", ntohs(address.u.addr16[index]));
                else
                    NDK_sprintf (tmpStr, "%x:", ntohs(address.u.addr16[index]));
            }
        }
        else
        {
            /* NO. This is NON ZERO. Check if we got enough zeroes for compression and that we
             * have not already done the zero compression. */
            if ((num_leading_zeroes >= 2) && (zc == 0))
            {
                /* OK; we can do zero compression at this stage. We print only 
                 * one ':' here because we have already done one while printing the initial
                 * non-zero down. */
                ptr_tmpStr += NDK_sprintf (ptr_tmpStr, ":");

                /* We are allowed only one zero compression. */
                zc = 1;
            }

            /* This is not a candidate for zero compression; so print out the contents. 
             * For the last address index we dont want an additional ':' at the end. */
            if (index == 7)
                ptr_tmpStr += NDK_sprintf (ptr_tmpStr, "%x", ntohs(address.u.addr16[index]));
            else
                ptr_tmpStr += NDK_sprintf (ptr_tmpStr, "%x:", ntohs(address.u.addr16[index]));

            /* Reset the number of leading zeroes. */
            num_leading_zeroes = 0;
        }

        /* Get the next address. */
        index = index + 1;

        /* Concatenate to the final output. */
        strcat (strIPAddress, tmpStr);
    }

    /* This handles the trailing zeroes. */
    if ((num_leading_zeroes >= 4) && (zc == 0))
        strcat (strIPAddress, ":");

    }
    else
    {
    NDK_sprintf (strIPAddress, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
             ntohs(address.u.addr16[0]), ntohs(address.u.addr16[1]), ntohs(address.u.addr16[2]), 
             ntohs(address.u.addr16[3]), ntohs(address.u.addr16[4]), ntohs(address.u.addr16[5]), 
             ntohs(address.u.addr16[6]), ntohs(address.u.addr16[7]));
    }

    /* Work has been completed. */
    return;
}

/** 
 *  @b Description
 *  @n  
 *      Utility Function which prints the IPv6 address. The IP address passed
 *      has to be specified in network order (IP6N).
 *
 *  @param[in]   address
 *      IPv6 Address to be displayed.
 *  @retval
 *   Not Applicable.
 */
void IPv6DisplayIPAddress (IP6N address)
{
    char    strIPAddress[40];

    if (ipv6mcb.IsZeroCompressionEnabled)
    {
    /* Convert to string format. */
    IPv6IPAddressToString (address, &strIPAddress[0]);

    /* Print out the address on the console. */
    DbgPrintf(DBG_INFO, "%s\n", strIPAddress);
    }
    else
    {
    DbgPrintf(DBG_INFO, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
            ntohs(address.u.addr16[0]), ntohs(address.u.addr16[1]), ntohs(address.u.addr16[2]), 
            ntohs(address.u.addr16[3]), ntohs(address.u.addr16[4]), ntohs(address.u.addr16[5]), 
            ntohs(address.u.addr16[6]), ntohs(address.u.addr16[7]));
    }

    return;
}

/** 
 *  @b Description
 *  @n  
 *      Utility Function that validates whether a given ASCII 
 *      character is a valid hexadecimal digit.
 *
 *  @param[in]   ch
 *      The character that needs to be validated 
 *
 *  @retval
 *      1   - Success, the character is a hexadecimal digit
 *
 *  @retval
 *      0   - Error, the character is not a valid hexadecimal digit.
 */
int isValidHexDigit (int ch)
{
  /* Valid Hexadecimal char. return 1. RFC 2396. */
  if ((ch >= '0' && ch <= '9') ||
      (ch >= 'A' && ch <= 'F') ||
      (ch >= 'a' && ch <= 'f'))
    return 1;
  /* Invalid Hexadecimal char. return 0. */
  else
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      Utility function that converts a given ASCII character
 *      to its hexadecimal value.
 *
 *  @param[in]   ch
 *      The character that needs to be converted to hex.
 *
 *  @retval
 *      Hex equivalent - Success
 *
 *  @retval
 *      -1  - Error, the character is not a valid hexadecimal digit.
 */
int GetHexValue (int ch)
{
    if (ch >= '0' && ch <= '9') 
    {
        return (ch -'0');
    } 
    else if (ch >= 'A' && ch <= 'F') 
    {
        return (ch - 'A' + 10);
    } 
    else if (ch >= 'a' && ch <= 'f')
    {
        return (ch - 'a' + 10);
    } 
    else 
    {
        /* Not a valid hexadecimal char, so return error */
        return -1;
    }
}

/** 
 *  @b Description
 *  @n  
 *      Utility Function which converts an IPv6 Address from CHAR Format to IP6N
 *
 *  @param[in]   StringIP
 *      The IPv6 Address in String Format 
 *  @param[out]  address
 *      The IPv6 Address in IP6N format.
 *
 *  @retval
 *      0   -   Success
 *  @retval
 *      -1  -   Error
 */
int IPv6StringToIPAddress (char* StringIP, IP6N* address)
{
    int     num_colon_sep = 0;
    int     num_dcolon_sep = 0;
    int     index = 0, exp_index = 0;

    /* Basic Validations: */
    if ((StringIP == NULL) || (address == NULL))
        return -1;

    /* Initialize the IPv6 Address */
    mmZeroInit(address, sizeof(IP6N));

    /* Cycle through and verify if the address had zero compression or not? 
     * We run through the Entire string and check the number of ':' and '::' separators. 
     */
    while (StringIP[index] != 0)
    {
        /* Parse through the string, and when we encounter
         * a ':' increment the number of colons by 1 and
         * if we encounter another ':' following a ':', i.e.,
         * a '::', increment both number of colons and 
         * number of double colons.
         * These numbers are used for validation purposes 
         * once we step out of the loop.
         */
        if (StringIP[index] == ':')
        {
            num_colon_sep++;

            if (StringIP[index + 1] == ':')
                num_dcolon_sep++;
        }
        else if (!isValidHexDigit(StringIP[index]))
        {
            /* ASCII char not a valid hexadecimal int. return 
             * error.
             */
            return -1;
        }

        index = index + 1;
    }

    /* A Valid IPv6 Address cannot have more than 8 16-bit hexadecimal peices
     * separated by ":" separator or more than one "::". Also, if it doesnt have
     * any "::" separated pieces, then it must exactly have 7 ":". Otherwise,
     * its an invalid IPv6 address.
     */
    if (num_colon_sep > 7 || num_dcolon_sep > 1 || (!num_dcolon_sep && num_colon_sep != 7))
        return -1;

    /* Iterate through the string and convert the characters to their hexadecimal value
     * to insert into IPv6 address.
     */
    index = 0;
    while (StringIP[index] != 0)
    {
        if (StringIP[index] == ':')
        {
            if (StringIP[index + 1] == ':')
                exp_index += (8 - num_colon_sep);
            else
                exp_index ++;
        }
        else
        {
            address->u.addr16[exp_index] = htons((ntohs(address->u.addr16[exp_index]) << 4) + GetHexValue(StringIP[index]));
        }

		index ++;
    }

    /* Address has been converted. */
    return 0;
}


/** 
 *  @b Description
 *  @n  
 *      Utility Function used to compare the 2 IPv6 Addresses.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]   addr1
 *      The first IPv6 Address which is to be compared.
 *
 *  @param[in]   addr2
 *      The second IPv6 Address which is to be compared.
 *      
 *  @retval
 *   1  -   The IP Addresses match
 *  @retval
 *   0  -   The IP Addresses do not match
 */
UINT16 IPv6CompareAddress (IP6N addr1, IP6N addr2)
{
    /* Compare the IPv6 Addresses. */
    if ((addr1.u.addr32[0] == addr2.u.addr32[0]) &&
        (addr1.u.addr32[1] == addr2.u.addr32[1]) &&
        (addr1.u.addr32[2] == addr2.u.addr32[2]) &&
        (addr1.u.addr32[3] == addr2.u.addr32[3]))
    {
        /* Perfect Match. */
        return 1;
    }
    /* No Match. */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      Utility Function which determines if the IPv6 Address specified is a 
 *      Multicast address or not?
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]   address
 *      IPv6 Address which needs to be verfied.
 *      
 *  @retval
 *   1  -   The address passed is MULTICAST
 *  @retval
 *   0  -   The address passed is NOT Multicast
 */
UINT16 IPv6IsMulticast (IP6N address)
{
    /* Multicast IPv6 address have their most significant order bits set. */
    if (address.u.addr8[0] == 0xFF)
        return 1;
    return 0; 
}

/** 
 *  @b Description
 *  @n  
 *      Utility Function which determines if the IPv6 Address specified is a 
 *      Link Local address or not?
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]   address
 *      IPv6 Address which needs to be verfied.
 *      
 *  @retval
 *   1  -   The address passed is Link Local
 *  @retval
 *   0  -   The address passed is NOT Link Local
 */
UINT16 IPv6IsLinkLocal (IP6N address)
{
    if (address.u.addr16[0] == htons(0xFE80))
        return 1;
    return 0; 
}

/** 
 *  @b Description
 *  @n  
 *      Utility Function which gets the subnet mask given the number
 *      of bits.
 *
 *      For example: Subnet Mask = 0xFFFF:: if the bits is 16
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[out]   SubnetMask
 *      Pointer to the computed subnet mask in network order.
 *  @param[in]    bits
 *      Number of bits in the subnet mask
 *      
 *  @retval
 *      Not Applicable.
 */
void IPv6GetSubnetMaskFromBits (IP6N* SubnetMask, UINT16 bits)
{
    UINT16  index;
    UINT32  Seed;
    UINT32* ptr_subnetMask;

    /* Basic Validations: Make sure bits is in the range? */
    if ((SubnetMask == NULL) || (bits > 128))
        return;

    /* Initialize the Subnet Mask. */
    SubnetMask->u.addr32[0] = 0;
    SubnetMask->u.addr32[1] = 0;
    SubnetMask->u.addr32[2] = 0;
    SubnetMask->u.addr32[3] = 0;

    /* Start with the Highest Order address word. */
    ptr_subnetMask = &SubnetMask->u.addr32[0];

    /* Loop off */
    while (1)
    {
        /* Initialize the Seed. */
        Seed = 0x80000000;

        /* Determine the number of bits we need to set in the first 4 bytes. */
        if (bits < 32)
            index = bits;
        else
            index = 32;

        /* Set out all the bits */
        while (index-- != 0)
        {
            *ptr_subnetMask = *ptr_subnetMask | Seed;
            Seed  = Seed >> 1;
        }
        *ptr_subnetMask = htonl(*ptr_subnetMask);

        /* We have taken care of the 32 bits; do we need to proceed? */
        if (bits <= 32)
            return;

        /* YES. Take out the bits that we took care off and goto the next address. */
        bits = bits - 32;
        ptr_subnetMask++;
    }
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to generate a 64 bit IPv6 Identifier 
 *      from the MAC Address.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @param[in]  ptr_device
 *      The pointer to the NIMU Network Interface object for which the
 *      IPv6 identifier is being generated.
 *
 *  @param[out]  InterfaceID
 *      The IPv6 64 bit Interface Identifier generated
 *
 *  @sa RFC 2373 IPv6 Addressing Architecture (Section 5.1)
 *
 *  @retval
 *   Not Applicable
 */
static void IPv6GenerateEUI64 (NETIF_DEVICE* ptr_device, UINT32* InterfaceID)
{
    UINT8*  ptr = (UINT8 *)InterfaceID;

    /* Copy the first 3 bytes i.e. the IEEE assigned value 
     * RFC 2373 Section 5.1 and Appendix A indicates we set the 
     * 'u' bit to be 0 when we create the EUI64 bit Identifier. 
     * This value is then complemented to get the IPv6 Interface 
     * Identifier. */
    *ptr       = ptr_device->mac_address[0] | 0x2;
    *(ptr + 1) = ptr_device->mac_address[1];
    *(ptr + 2) = ptr_device->mac_address[2];

    /* Now insert the fixed fields. */
    *(ptr + 3) = 0xFF;
    *(ptr + 4) = 0xFE;

    /* Now copy the next 3 bytes i.e. the Vendor assigned value. */
    *(ptr + 5) = ptr_device->mac_address[3];
    *(ptr + 6) = ptr_device->mac_address[4];
    *(ptr + 7) = ptr_device->mac_address[5];

    return;
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to add an IPv6 address to an interface.
 *      This function should not be used to add Link Local Addresses to
 *      the interface. Link Local Addresses are automatically added to
 *      the interface when the IPv6 stack is initialized on it. 
 *  @sa
 *      IPv6AddAddress
 *
 *      The function is exported to system developers and should only
 *      be called from outside kernel mode.
 *
 *  @param[in]  dev_index
 *      The device index on which the IPv6 address needs to be added.
 *  @param[in]  Address
 *      The IPv6 Address which needs to be added.
 *  @param[in]  NetBits
 *      The number of bits which make the Subnet-Mask.
 *  @param[in]  ValidLifetime
 *      The Valid Lifetime of the address. Set to INFINITE_LT if the address is 
 *      permanent
 *  @param[in]  PrefLifetime
 *      The Preferred Lifetime of the address. Set to INFINITE_LT if the address
 *      is permanent.
 *  @param[in]  IsAnycast
 *      Flag which indicates if the address to be added is ANYCAST or UNICAST.
 *      Set to 1 for ANYCAST.
 *
 *  @retval
 *   0  -   Success
 *  @retval
 *   <0 -   Error
 */
int IPv6AddAddress 
(
    UINT16  dev_index, 
    IP6N    Address, 
    UINT16  NetBits, 
    UINT32  ValidLifetime, 
    UINT32  PrefLifetime,
    UINT8   IsAnycast
)
{
    NETIF_DEVICE*       ptr_device;
    IP6N                SubnetMask;

    /* Move into kernel mode. */
    llEnter();

    /* Validate the arguments: Ensure that the NET device exists in the System? */
    ptr_device = NIMUFindByIndex (dev_index);
    if (ptr_device == NULL)
    {
        /* Device does not exist. */
        llExit ();
        return -EINVAL;
    }

    /* Validate the arguments: Make sure that the bits is in the range? */
    if (NetBits > 128)
    {
        /* Invalid Range. */
        llExit ();
        return -EINVAL;            
    }

    /* Make sure the IPv6 stack has already been initialized on this interface. */
    if (ptr_device->ptr_ipv6device == NULL)
    {
        /* IPv6 has not been initialized on this interface. */
        llExit ();
        return -1;
    }

    /* We do not let the user add Unspecified address (::) or 
     * loopback address (::1).
     */
    if ((IPv6CompareAddress(Address, IPV6_UNSPECIFIED_ADDRESS) == 1) ||
        (IPv6CompareAddress(Address, IPV6_LOOPBACK_ADDRESS) == 1))
    {
        llExit ();
        return -1;
    }

    /* Generate a V6 Subnet Mask from the NetBits provided. */
    IPv6GetSubnetMaskFromBits (&SubnetMask, NetBits);

    /* Check for Duplicate Address Bindings? */
    if (Bind6FindByHost (ptr_device, Address) == 0)
    {
        /* Address does not exist: Create the binding for the address. */
        if (Bind6New (ptr_device, Address, SubnetMask, ValidLifetime, PrefLifetime, IsAnycast) == 0)
        {
            /* Error: Failed to create the BINDING */
            llExit ();
            return -1;
        }
    }
 
    /* Exit out of kernel mode. */
    llExit ();
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to delete an IPv6 address from an interface
 *      This function should not be used to delete Link Local Addresses from
 *      the interface. Link Local Addresses are automatically deleted from 
 *      the interface when the IPv6 stack is de-initialized on it. 
 *  @sa
 *      IPv6InterfaceDeInit
 *
 *      The function is exported to system developers and should only
 *      be called from outside kernel mode.
 *
 *  @param[in]  dev_index
 *      The device index on which the IPv6 address needs to be deleted.
 *  @param[in]  Address
 *      The IPv6 Address which needs to be deleted.
 *
 *  @retval
 *   0  -   Success
 *  @retval
 *   <0 -   Error
 */
int IPv6DelAddress (UINT16 dev_index, IP6N Address)
{
    NETIF_DEVICE*   ptr_device;
    HANDLE          hBind6Obj;

    /* Move into kernel mode. */
    llEnter();

    /* Validate the arguments: Ensure that the NET device exists in the System? */
    ptr_device = NIMUFindByIndex (dev_index);
    if (ptr_device == NULL)
    {
        /* Device does not exist. */
        llExit ();
        return -EINVAL;
    }

    /* Make sure the IPv6 stack has already been initialized on this interface. */
    if (ptr_device->ptr_ipv6device == NULL)
    {
        /* IPv6 has not been initialized on this interface. */
        llExit ();
        return -1;
    }

    /* We dont allow leaving of LINK Local Address through this API. */
    if (Address.u.addr16[0] == htons(0xFE80))
    {
        /* Trying to delete a Link Local Address through this API. This is not supported
         * Use the Deinitialize API Instead. */
        llExit ();
        return -1;
    }

    /* Make sure that the address exists on the interface? */
    hBind6Obj = Bind6FindByHost (ptr_device, Address);
    if (hBind6Obj == 0)
    {
        /* Address does not exist; lets return an error and indicate so. */
        llExit ();
        return -EINVAL;
    }

    /* Cleanout the Binding */
    Bind6Free (hBind6Obj);
    
    /* Move out of kernel mode. */
    llExit ();
    return 0;    
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to initialize the IPv6  stack on the the 
 *      specific device name. This is available to System Developers 
 *      and should be invoked for the IPv6 stack to be operational on the
 *      specified interface. This can be called only from kernel mode thus
 *      System Developers should ensure that is called within the llEnter
 *      and llExit sections.
 *
 *  @param[in]  dev_index
 *      The device index on which the IPv6 stack is to be initialized.
 *  @param[in]  DADStatus
 *      This is the call back function which is invoked by the IPv6 state
 *      machine once the DAD process has been completed on an address. The 
 *      Status argument indicates the result of the DAD operation. 1 indicates
 *      that the address was permanent and 0 indicates that the address is a 
 *      duplicate. This is an optional parameter and can be passed as NULL.
 *
 *  @retval
 *   0  -   Success
 *  @retval
 *   <0 -   Error
 */
int IPv6InterfaceInit (UINT16 dev_index, void (*DADStatus)(IP6N Address, UINT16 dev_index, UINT8 Status))
{
    IPV6_DEV_RECORD*    ptr_ipv6dev;
    IP6N                address;
    NETIF_DEVICE*       ptr_device;

    /* Get the NIMU Device; by searching with the name */
    ptr_device = NIMUFindByIndex (dev_index);
    if (ptr_device == NULL)
        return -1;

    /* Check if the IPv6 stack has been initialized on this interface? 
     * This should never be the case. */
    if (ptr_device->ptr_ipv6device != NULL)
        return -1;

    /* The IPv6 stack can execute only if the interface is capable of handling at
     * least 1280 bytes MTU. If we fall below this then IPv6 will not operate. 
     * Though this is an error; we still return SUCCESS here */
    if (ptr_device->mtu < MIN_IPV6_MTU)
        return 0;
    
    /* Allocate memory for the IPv6 Record. */
    ptr_ipv6dev = mmAlloc(sizeof(IPV6_DEV_RECORD));
    if (ptr_ipv6dev == NULL)
    {
        /* Error: Out of memory. */
        NotifyLowResource();
        return -1;
    }

    /* Initialize the allocated block of memory. */
    mmZeroInit ((void *)ptr_ipv6dev, sizeof(IPV6_DEV_RECORD));

    /* Initialize the fields. */
    ptr_ipv6dev->CurHopLimit        = IPV6_UCAST_DEF_HOP_LIMIT;
    ptr_ipv6dev->BaseReachableTime  = IPV6_REACHABLE_TIME;
    ptr_ipv6dev->ReachableTime      = IPV6_REACHABLE_TIME;
    ptr_ipv6dev->RetransTimer       = IPV6_RETRANS_TIME;
    ptr_ipv6dev->ManagedFlag        = 0;
    ptr_ipv6dev->OtherConfigFlag    = 0;
    ptr_ipv6dev->DADStatus          = DADStatus;

    /* Link MTU has a different story; we inherit this from the NIMU Network Interface Object but
     * the MTU can be modified from the RA received; we dont want to change the MTU of the NIMU
     * Network Interface object because of this; since it will affect IPv4 traffic too. Hence we keep
     * a seperate copy in the IPv6 domain. */
    ptr_ipv6dev->LinkMTU            =  ptr_device->mtu;

    /* Hook the IPv6 Device Record with NIMU and vice-versa. */
    ptr_device->ptr_ipv6device      = ptr_ipv6dev;
    ptr_ipv6dev->hIF                = (HANDLE)ptr_device;

    /* Create the EUI-64 for this interface. */
    IPv6GenerateEUI64 (ptr_device, &ptr_ipv6dev->EUI64[0]);

    /* Create the LINK-LOCAL Address for the interface. */ 
    address.u.addr32[0] = htonl (0xFE800000);
    address.u.addr32[1] = 0x0;
    address.u.addr32[2] = ptr_ipv6dev->EUI64[0];
    address.u.addr32[3] = ptr_ipv6dev->EUI64[1];

    /* Now we create a BINDING for the Link Local Address. All Link Local Bindings remain valid
     * for INFINITE Time. This is most definately not an ANYCAST Address. */
    ptr_ipv6dev->hLinkLocalBind = Bind6New (ptr_device, address, IPV6_LINKLOCALMASK, INFINITE_LT, INFINITE_LT, 0);
    if (ptr_ipv6dev->hLinkLocalBind == 0)
    {
        /* Error: Unable to create the Local Bindings. */
        mmFree (ptr_ipv6dev);
        return -1;
    }

    /* Here we create the Loopback Route; which is to be used for this interface. */
    ptr_ipv6dev->hLinkLoopbackRoute = Rt6Create (FLG_RTE_HOST|FLG_RTE_IFLOCAL,
                                                 IPV6_LOOPBACK_ADDRESS, IPV6_HOST_MASK,
                                                 IPV6_UNSPECIFIED_ADDRESS, NULL, ptr_device, INFINITE_LT);

    /* Once the Bindings have been created; we now need to join the 
     * following multicast groups:- 
     *  a) All Nodes Group
     *  b) Solicited Link Local Node Multicast Address 
     *
     * Starting with the All Nodes Group i.e. 0xFF02::1 */
    if (MLDJoinGroup (ptr_device, IPV6_ALL_NODES_ADDRESS) < 0)
    {
        /* Error: Unable to join the multicast all nodes group. */
        mmFree (ptr_ipv6dev);
        return -1;
    }

    /* Increment the reference counter for the NIMU Network Interface object. This 
     * informs the NIMU layer that the network interface object is currently being used
     * and should not be deleted. */
    ptr_device->RefCount++;

    /* Send out the Router Solicitation */
    ICMPv6SendRS (ptr_device, IPV6_UNSPECIFIED_ADDRESS);

    /* Work has been completed successfully. */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to deinitialize the IPv6 stack on the the 
 *      specific device name. The function is available to System Developers 
 *      and should only be called from within kernel mode.
 *
 *  @param[in]  dev_index
 *      The device index on which the IPv6 stack is to be deinitialized.
 *
 *  @retval
 *   0  -   Success
 *  @retval
 *   <0 -   Error
 */
int IPv6InterfaceDeInit (UINT16 dev_index)
{
    NETIF_DEVICE* ptr_device;
    HANDLE        hBind6Obj;

    /* Get the NIMU Device; by searching with the name */
    ptr_device = NIMUFindByIndex (dev_index);
    if (ptr_device == NULL)
        return -1;

    /* Check if the IPv6 stack has been initialized on this interface? */
    if (ptr_device->ptr_ipv6device == NULL)
        return 0;

    /* Find all Bindings for this Interface and remove them */
    hBind6Obj = Bind6FindByIF (ptr_device);
    while (hBind6Obj != 0)
    {
        /* Cleanout the Binding */
        Bind6Free (hBind6Obj);

        /* Get the next binding. */
        hBind6Obj = Bind6FindByIF (ptr_device);
    }

    /* Remove the Link Loopback route. */
    Rt6Free(ptr_device->ptr_ipv6device->hLinkLoopbackRoute);

    /* Leave the ALL Node Multicast Address group. */
    MLDLeaveGroup (ptr_device, IPV6_ALL_NODES_ADDRESS);

    /* Decrement the reference counter for the NIMU Network Interface object. This 
     * informs the NIMU layer that the network interface object is no longer 
     * being used by the IPv6 stack. */
    ptr_device->RefCount--;

    /* Cleanout the IPv6 Device Record. */
    mmFree (ptr_device->ptr_ipv6device);
    ptr_device->ptr_ipv6device = NULL;

    /* IPv6 stack has been deinitialized. */
    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      This function is used to initialize the IPv6 Module.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *   Not Applicable.
 */
void IPv6Init (void)
{
    /* Initialize the IPv6 statistics. */
    mmZeroInit (&ipv6mcb, sizeof(IPV6_MCB));

    /* Initialize the IPv6 Master Control Block. 
     *  NDK currently supports only Host Mode. */
    ipv6mcb.IsRouter = 0;

    /* Zero compression of IPv6 addresses is enabled
     * by default.
     */
    ipv6mcb.IsZeroCompressionEnabled = 1;

    /* Configure some well known IPv6 Constants. 
     *  LINK Local Mask */
    IPV6_LINKLOCALMASK.u.addr32[0] = htonl(0xFFC00000);
    IPV6_LINKLOCALMASK.u.addr32[1] = 0;
    IPV6_LINKLOCALMASK.u.addr32[2] = 0;
    IPV6_LINKLOCALMASK.u.addr32[3] = 0;

    /* All Nodes Address */
    IPV6_ALL_NODES_ADDRESS.u.addr32[0] = htonl (0xFF020000);
    IPV6_ALL_NODES_ADDRESS.u.addr32[1] = 0;
    IPV6_ALL_NODES_ADDRESS.u.addr32[2] = 0;
    IPV6_ALL_NODES_ADDRESS.u.addr32[3] = htonl(0x1);

    /* All Router Address */
    IPV6_ALL_ROUTER_ADDRESS.u.addr32[0] = htonl (0xFF020000);
    IPV6_ALL_ROUTER_ADDRESS.u.addr32[1] = 0;
    IPV6_ALL_ROUTER_ADDRESS.u.addr32[2] = 0;
    IPV6_ALL_ROUTER_ADDRESS.u.addr32[3] = htonl(0x2);
 
    /* Multicast Mask. */
    IPV6_MULTICASTMASK.u.addr32[0] = htonl(0xFF000000);
    IPV6_MULTICASTMASK.u.addr32[1] = 0;
    IPV6_MULTICASTMASK.u.addr32[2] = 0;
    IPV6_MULTICASTMASK.u.addr32[3] = 0;

    /* The Unspecified Address is all :: */
    IPV6_UNSPECIFIED_ADDRESS.u.addr32[0] = 0;
    IPV6_UNSPECIFIED_ADDRESS.u.addr32[1] = 0;
    IPV6_UNSPECIFIED_ADDRESS.u.addr32[2] = 0;
    IPV6_UNSPECIFIED_ADDRESS.u.addr32[3] = 0;

    /* The Loopback Address is all ::1 */
    IPV6_LOOPBACK_ADDRESS.u.addr32[0] = 0;
    IPV6_LOOPBACK_ADDRESS.u.addr32[1] = 0;
    IPV6_LOOPBACK_ADDRESS.u.addr32[2] = 0;
    IPV6_LOOPBACK_ADDRESS.u.addr32[3] = htonl(1);

    /* The IPv6 Host Mask. */
    IPV6_HOST_MASK.u.addr32[0] = htonl(0xFFFFFFFF);
    IPV6_HOST_MASK.u.addr32[1] = htonl(0xFFFFFFFF);
    IPV6_HOST_MASK.u.addr32[2] = htonl(0xFFFFFFFF);
    IPV6_HOST_MASK.u.addr32[3] = htonl(0xFFFFFFFF);

    /* IPv6 Stack is operational. */
    return;
}

#endif /* _INCLUDE_IPv6_CODE */

