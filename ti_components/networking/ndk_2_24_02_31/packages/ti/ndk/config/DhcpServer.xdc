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
 *  ======== DhcpServer.xdc ========
 *
 *  DhcpServer module definition and initial values
 */

/*!
 *  ======== DhcpServer ========
 *  NDK module for creating and configuring a DHCP server. 
 *  
 *  The DhcpServer module can be used to configure and create a DHCP server in
 *  an NDK application.
 *  
 *  In order to configure a DHCP server, users must create a DhcpServer module
 *  parameters structure, which contains all of the instance properties of a
 *  DhcpServer instance.  Once the parameter structure is created, it may
 *  be used to change the properties of the DHCP server that's being created.
 *  
 *  Users are able to create multiple DHCP servers by creating multiple
 *  DhcpServer instances, and configuring each one.  However, if multiple
 *  DhcpServer instances are created, one must be careful to ensure that
 *  they all have been configured to have unique and free port numbers.
 */  

@Template("./DhcpServer.xdt")

metaonly module DhcpServer {

    /*! Function signature for CISARGS struct service reporting function */
    typedef Void (*dhcpServerServiceFxn)(Int, Int, Int, Void *);

    /*! Type used to specify bits in flags config parameter */
    typedef Bits16 DhcpServerFlag;

    /*!
     *  Causes DHCP Server to report its own IP address as the local DNS server
     *  to clients
     *
     *  If this flag is not set, the DHCP server reports the DNS servers as
     *  contained in the SYSINFO portion of the configuration.
     */
    const DhcpServerFlag DHCPS_FLG_LOCALDNS    = 0x0001;

    /*!
     *  Causes DHCP Server to report the local domain name assigned to the
     *  virtual network to clients.
     *
     *  If this flag is not set, the DHCP Server reports the public domain
     *  name to its clients.
     */
    const DhcpServerFlag DHCPS_FLG_LOCALDOMAIN = 0x0002;

    /*
     *  NOTE: DHCPS can only be run on an interface so no CIS mode options
     */

    /*!
     *  ======== create ========
     *  Creates an DhcpServer instance.
     */
    create();

instance:
    /*! The first IP address of the DHCP server address pool */
    config String ipAddrPoolBase = "192.168.1.2";

    /*! The number of IP addresses in the DHCP server address pool */
    config Int ipAddrPoolCount = 253;

    /*!
     *  The physical device index on which the DHCP server shall be
     *  executed.  Must be greater than zero.
     */
    config Int ifIdx = 1;

    /*! DhcpServer service reporting function. */
    config dhcpServerServiceFxn pCbSrv = '&ti_ndk_config_Global_serviceReport';

    /*!
     *  Causes DHCP Server to report its own IP address as the local DNS server
     *  to clients
     */
    config Bool localDNS = false;

    /*!
     *  Causes DHCP Server to report the local domain name assigned to the
     *  virtual network to clients.
     */
    config Bool localDomain = false;
}
