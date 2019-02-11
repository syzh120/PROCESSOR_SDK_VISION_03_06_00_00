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
 *  ======== prototypes.h ========
 *  Declare module functions called from Ndk module generated code.
 */

#ifndef ti_ndk_config_NdkPrototypes_
#define ti_ndk_config_NdkPrototypes_

#include <xdc/std.h>

#include <ti/ndk/inc/usertype.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== ti_ndk_config_tcp_init ========
 *  function for TCP configuration.
 */
Void ti_ndk_config_tcp_init(HANDLE hCfg);

/*
 *  ======== ti_ndk_config_ip_init ========
 *  function for IP configuration.
 */
Void ti_ndk_config_ip_init(HANDLE hCfg);

/*
 *  ======== ti_ndk_config_udp_init ========
 *  function for UDP configuration.
 */
Void ti_ndk_config_udp_init(HANDLE hCfg);

/*
 *  ======== ti_ndk_config_telnet_init ========
 *  function for Telnet service configuration.
 */
Void ti_ndk_config_telnet_init(HANDLE hCfg);

/*
 *  ======== ti_ndk_config_http_init ========
 *  function for HTTP service configuration.
 */
Void ti_ndk_config_http_init(HANDLE hCfg);

/*
 *  ======== ti_ndk_config_dhcpserver_init ========
 *  function for DHCP Server configuration.
 */
Void ti_ndk_config_dhcpserver_init(HANDLE hCfg);

/*
 *  ======== ti_ndk_config_external_dns_init ========
 *  function for specifying an external DNS server.
 */
Void ti_ndk_config_external_dns_init(HANDLE hCfg);

/*
 *  ======== ti_ndk_dns_init ========
 *  function for DNS configuration.
 */
Void ti_ndk_config_dns_init(HANDLE hCfg);

/*
 *  ======== ti_ndk_config_nat_init ========
 *  function for NAT configurtion.
 */
Void ti_ndk_config_nat_init(HANDLE hCfg);

/*
 *  ======== ti_ndk_config_Global_serviceReport ========
 *  Service reporting function.
 */
Void ti_ndk_config_Global_serviceReport(uint Item, uint Status,
        uint Report, HANDLE hCfgEntry);

/*
 *  ======== ti_ndk_config_global_addUserAcct ========
 *  Add all user accounts to the configuration.
 */
Void ti_ndk_config_global_addUserAccts(HANDLE hCfg);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* ti_ndk_config_NdkPrototypes_ */

