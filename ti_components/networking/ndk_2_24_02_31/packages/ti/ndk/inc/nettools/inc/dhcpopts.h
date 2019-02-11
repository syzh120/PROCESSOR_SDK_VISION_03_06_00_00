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
 * ======== dhcpopts.h ========
 *
 */

#ifndef _DHCPOPTIONS_H_
#define _DHCPOPTIONS_H_

/* DHCP Options */
/* This is used to specify which options the DHCP client should request. */
/* The name of the constant is the option name, the value is the code. */
/* See RFC 2132. */
#define DHCPOPT_PAD                                    0
#define DHCPOPT_SUBNET_MASK                            1
#define DHCPOPT_TIME_OFFSET                            2
#define DHCPOPT_ROUTER                                 3
#define DHCPOPT_TIME_SERVER                            4
#define DHCPOPT_NAME_SERVERS                           5
#define DHCPOPT_DOMAIN_NAME_SERVERS                    6
#define DHCPOPT_LOG_SERVER                             7
#define DHCPOPT_COOKIE_SERVER                          8
#define DHCPOPT_LPR_SERVER                             9
#define DHCPOPT_IMPRESS_SERVER                         10
#define DHCPOPT_RESOURCE_LOCATION_SERVER               11
#define DHCPOPT_HOSTNAME                               12
#define DHCPOPT_BOOT_FILE_SIZE                         13
#define DHCPOPT_MERIT_DUMP_FILE                        14
#define DHCPOPT_DOMAIN_NAME                            15
#define DHCPOPT_SWAP_SERVER                            16
#define DHCPOPT_ROOT_PATH                              17
#define DHCPOPT_EXTENTIONS_PATH                        18
#define DHCPOPT_IP_FORWARDING                          19
#define DHCPOPT_NONLOCAL_SOURCE_ROUTING                20
#define DHCPOPT_POLICTY_FILTER                         21
#define DHCPOPT_MAXIMUM_DATAGRAM_REASSEMBLY_SIZE       22
#define DHCPOPT_DEFAULT_IP_TTL                         23
#define DHCPOPT_PATH_MTU_AGING_TIMEOUT                 24
#define DHCPOPT_PATH_MTU_PLATEAU_TIMEOUT               25
#define DHCPOPT_INTERFACE_MTU                          26
#define DHCPOPT_ALL_SUBNETS_LOCAL                      27
#define DHCPOPT_BROADCAST_ADDRESS                      28
#define DHCPOPT_PERFORM_MASK_DISCOVERY                 29
#define DHCPOPT_MASK_SUPPLIER                          30
#define DHCPOPT_PERFORM_ROUTER_DISCOVERY               31
#define DHCPOPT_ROUTER_SOLICITATION_ADDRESS            32
#define DHCPOPT_STATIC_ROUTE                           33
#define DHCPOPT_TRAILER_ENCAPSULATION                  34
#define DHCPOPT_ARP_CACHE_TIMEOUT                      35
#define DHCPOPT_ETHERNET_ENCAPSULATION                 36
#define DHCPOPT_TCP_DEFUALT_TTL                        37
#define DHCPOPT_TCP_KEEPALIVE_INTERVAL                 38
#define DHCPOPT_TCP_KEEPALIVE_GARBAGE                  39
#define DHCPOPT_NIS_DOMAIN                             40
#define DHCPOPT_NIS_SERVERS                            41
#define DHCPOPT_NIS_TIME_PROTOCOL_SERVERS              42
#define DHCPOPT_VENDOR_SPECIFIC_INFORMATION            43
#define DHCPOPT_NETBIOS_NAME_SERVER                    44
#define DHCPOPT_NETBIOS_DATAGRAM_DISTRIBUTION_SERVER   45
#define DHCPOPT_NETBIOS_NODE_TYPE                      46
#define DHCPOPT_NETBIOS_SCOPE                          47
#define DHCPOPT_XWINDOWS_FONT_SERVER                   48
#define DHCPOPT_XWINDOWS_DISPLAY_MANAGER               49
#define DHCPOPT_REQUESTED_IP_ADDRESS                   50
#define DHCPOPT_IP_ADDRESS_LEASE_TIME                  51
#define DHCPOPT_OPTION_OVERLOAD                        52
#define DHCPOPT_DHCP_MESSAGE_TYPE                      53
#define DHCPOPT_SERVER_IDENTIFIER                      54
#define DHCPOPT_PARAMETER_REQUEST_LIST                 55
#define DHCPOPT_MESSAGE                                56
#define DHCPOPT_MAXIMUM_DHCP_MESSAGE_SIZE              57
#define DHCPOPT_RENEWAL_T1_TIME_VALUE                  58
#define DHCPOPT_RENEWAL_T2_TIME_VALUE                  59
#define DHCPOPT_VENDOR_CLASS_IDENTIFIER                60
#define DHCPOPT_CLIENT_IDENTIFIER                      61
#define DHCPOPT_NISPLUS_DOMAIN                         64
#define DHCPOPT_NISPLUS_SERVERS                        65
#define DHCPOPT_TFTP_SERVER_NAME                       66
#define DHCPOPT_BOOTFILE_NAME                          67
#define DHCPOPT_MOBILE_IP_HOME_AGENT                   68
#define DHCPOPT_SMTP_SERVER                            69
#define DHCPOPT_POP3_SERVER                            70
#define DHCPOPT_NNTP_SERVER                            71
#define DHCPOPT_DEFAULT_WWW_SERVER                     72
#define DHCPOPT_DEFAULT_FINGER_SERVER                  73
#define DHCPOPT_DEFAULT_IRC_SERVER                     74
#define DHCPOPT_STREETTALK_SERVER                      75
#define DHCPOPT_STREETALK_DISCOVERY_ASSISTANCE_SERVER  76
#define DHCPOPT_END                                    255

#endif
