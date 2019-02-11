/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 *  ======== Ip.xdc ========
 *  Ip module definition file and initial values.
 */

/*!
 *  ======== Ip ======== 
 *  NDK Internet Protocol (IP) settings and configuration.
 *  
 *  The Ip module is used to configure settings for IP, as well as other stack
 *  properties which are closely related to IP.  The Ip module encompasses
 *  stack settings and configuration for the following catergories:
 *  
 *  @p(blist)
 *      - IP settings - Internet Protocol
 *      - DHCP Client settings - Dynamic Host Configuration Protocol
 *      - ICMP settings - Internet Control Message Protocol
 *      - Route settings
 *      - IP Socket settings
 *      - Data Pipe settings
 *  @p
 *  
 *  To configure the settings of the Ip module, the module must be used in a
 *  RTSC configuration script, as follows:
 *
 *  @p(code)
 *  var Ip = xdc.useModule('ti.ndk.config.Ip);
 *  @p
 *  
 *  To change settings, simply set the values of the Ip module's members, which
 *  correspond to what needs to be configured.  For example, the following
 *  code  set a static IP address, increase the time to live value for ICMP
 *  packets to 100 hops, and decrease the maximum number of connections on
 *  a given IP socket down to 4:
 *  
 *  @p(code)
 *  Ip.address = "192.168.1.2";
 *  
 *  Ip.icmpTimeToLive = 100;
 *  
 *  Ip.socketMaxConnections = 4;
 *  @p
 *  
 *  To configure the target to run as a DHCP client, configure the IP address
 *  to be the empty string:
 *
 *  @p(code)
 *  Ip.address = "";
 *  @p
 *
 *  To configure the target to run without any IPv4 address (i.e. not as a DHCP
 *  client nor using a static IP), configure the IP address as "none":
 *
 *  @p(code)
 *  Ip.address = "none";
 *  @p
 *
 */

@Template("./Ip.xdt")

metaonly module Ip {

    /*
     * Default values
     *  @_nodoc
     */
    const Int  defaultStartIndex      = 1;
    const Bool defaultPortForwarding  = false;
    const Bool defaultPortFiltering   = false;
    const Int  defaultMaxReasmTime    = 10;
    const Int  defaultMaxReasmSize    = 3020;
    const Bool defaultIcmpDoRedir     = true;
    const Int  defaultIcmpTTL         = 64;
    const Int  defaultIcmpTTLecho     = 255;
    const Bool defaultIcmpBcastReply  = false;
    const Bool defaultIcmpMcastReply  = false;
    const Bool defaultDirBcast        = true;
    const Int  defaultRteDownTime     = 20;
    const Int  defaultRteKpAliveTime  = 1200;
    const Int  defaultRteCloneTimeout = 120;
    const Int  defaultRteMtu          = 64;
    const Bool defaultRteCtrlDbg      = false;
    const Int  defaultRteAdverPer     = 0;
    const Int  defaultRteAdverLife    = 120;
    const Int  defaultRteAdverLvl     = 0;
    const Int  defaultSockTTL         = 64;
    const Int  defaultSockTos         = 0;
    const Int  defaultSockMaxConn     = 8;
    const Int  defaultSockConnTimeout = 80;
    const Int  defaultSockIoTimeout   = 0;
    const Int  defaultSockBufTxSz     = 2048;
    const Int  defaultSockBufRxSz     = 1;
    const Int  defaultPipIoTimeout    = 0;
    const Int  defaultPipMaxBufSz     = 1024;
    const Int  defaultPipBufTxSz      = 256;
    const Int  defaultPipBufRxSz      = 1;

    /*
     *  Define set of DHCP options that a client may request to be returned
     *  by the DHCP server.  Note that these options correspond to the options
     *  defined in dhcpopts.h (which in turn in come from RFC2132).  Set any of
     *  these options to 'true' in order to request that the DHCP server return
     *  the value for that option.
     *  
     *  E.g. Ip.DHCPOPT_TCP_DEFUALT_TTL = true;
     *  
     */ 
    config Bool DHCPOPT_TIME_OFFSET                           = false; 
    config Bool DHCPOPT_TIME_SERVER                           = false; 
    config Bool DHCPOPT_NAME_SERVERS                          = false;
    config Bool DHCPOPT_LOG_SERVER                            = false;
    config Bool DHCPOPT_COOKIE_SERVER                         = false;
    config Bool DHCPOPT_LPR_SERVER                            = false;
    config Bool DHCPOPT_IMPRESS_SERVER                        = false;
    config Bool DHCPOPT_RESOURCE_LOCATION_SERVER              = false;
    config Bool DHCPOPT_BOOT_FILE_SIZE                        = false;
    config Bool DHCPOPT_MERIT_DUMP_FILE                       = false; 
    config Bool DHCPOPT_SWAP_SERVER                           = false; 
    config Bool DHCPOPT_ROOT_PATH                             = false; 
    config Bool DHCPOPT_EXTENTIONS_PATH                       = false; 
    config Bool DHCPOPT_IP_FORWARDING                         = false; 
    config Bool DHCPOPT_NONLOCAL_SOURCE_ROUTING               = false; 
    config Bool DHCPOPT_POLICTY_FILTER                        = false; 
    config Bool DHCPOPT_MAXIMUM_DATAGRAM_REASSEMBLY_SIZE      = false; 
    config Bool DHCPOPT_DEFAULT_IP_TTL                        = false; 
    config Bool DHCPOPT_PATH_MTU_AGING_TIMEOUT                = false; 
    config Bool DHCPOPT_PATH_MTU_PLATEAU_TIMEOUT              = false; 
    config Bool DHCPOPT_INTERFACE_MTU                         = false; 
    config Bool DHCPOPT_ALL_SUBNETS_LOCAL                     = false; 
    config Bool DHCPOPT_BROADCAST_ADDRESS                     = false; 
    config Bool DHCPOPT_PERFORM_MASK_DISCOVERY                = false; 
    config Bool DHCPOPT_MASK_SUPPLIER                         = false; 
    config Bool DHCPOPT_PERFORM_ROUTER_DISCOVERY              = false; 
    config Bool DHCPOPT_ROUTER_SOLICITATION_ADDRESS           = false; 
    config Bool DHCPOPT_STATIC_ROUTE                          = false; 
    config Bool DHCPOPT_TRAILER_ENCAPSULATION                 = false; 
    config Bool DHCPOPT_ARP_CACHE_TIMEOUT                     = false; 
    config Bool DHCPOPT_ETHERNET_ENCAPSULATION                = false; 
    config Bool DHCPOPT_TCP_DEFUALT_TTL                       = false; 
    config Bool DHCPOPT_TCP_KEEPALIVE_INTERVAL                = false; 
    config Bool DHCPOPT_TCP_KEEPALIVE_GARBAGE                 = false; 
    config Bool DHCPOPT_NIS_DOMAIN                            = false; 
    config Bool DHCPOPT_NIS_SERVERS                           = false; 
    config Bool DHCPOPT_NIS_TIME_PROTOCOL_SERVERS             = false; 
    config Bool DHCPOPT_VENDOR_SPECIFIC_INFORMATION           = false; 
    config Bool DHCPOPT_NETBIOS_DATAGRAM_DISTRIBUTION_SERVER  = false; 
    config Bool DHCPOPT_XWINDOWS_FONT_SERVER                  = false; 
    config Bool DHCPOPT_XWINDOWS_DISPLAY_MANAGER              = false; 
    config Bool DHCPOPT_REQUESTED_IP_ADDRESS                  = false; 
    config Bool DHCPOPT_IP_ADDRESS_LEASE_TIME                 = false; 
    config Bool DHCPOPT_OPTION_OVERLOAD                       = false; 
    config Bool DHCPOPT_DHCP_MESSAGE_TYPE                     = false; 
    config Bool DHCPOPT_SERVER_IDENTIFIER                     = false; 
    config Bool DHCPOPT_PARAMETER_REQUEST_LIST                = false; 
    config Bool DHCPOPT_MESSAGE                               = false; 
    config Bool DHCPOPT_MAXIMUM_DHCP_MESSAGE_SIZE             = false; 
    config Bool DHCPOPT_RENEWAL_T1_TIME_VALUE                 = false; 
    config Bool DHCPOPT_RENEWAL_T2_TIME_VALUE                 = false; 
    config Bool DHCPOPT_VENDOR_CLASS_IDENTIFIER               = false; 
    config Bool DHCPOPT_CLIENT_IDENTIFIER                     = false; 
    config Bool DHCPOPT_NISPLUS_DOMAIN                        = false; 
    config Bool DHCPOPT_NISPLUS_SERVERS                       = false; 
    config Bool DHCPOPT_TFTP_SERVER_NAME                      = false; 
    config Bool DHCPOPT_BOOTFILE_NAME                         = false; 
    config Bool DHCPOPT_MOBILE_IP_HOME_AGENT                  = false; 
    config Bool DHCPOPT_SMTP_SERVER                           = false; 
    config Bool DHCPOPT_POP3_SERVER                           = false; 
    config Bool DHCPOPT_NNTP_SERVER                           = false; 
    config Bool DHCPOPT_DEFAULT_WWW_SERVER                    = false; 
    config Bool DHCPOPT_DEFAULT_FINGER_SERVER                 = false; 
    config Bool DHCPOPT_DEFAULT_IRC_SERVER                    = false; 
    config Bool DHCPOPT_STREETTALK_SERVER                     = false; 
    config Bool DHCPOPT_STREETALK_DISCOVERY_ASSISTANCE_SERVER = false; 

    /*! Type used to specify bits in dhcpClientMode */
    typedef Bits16 CisFlags;

    /*! Specifies if the IfIdx field is valid. */
    const CisFlags CIS_FLG_IFIDXVALID        = 0x0001;

    /*!
     *  Requests that IfIdx be resolved to an IP address before service
     *  execution is initiated.
     */
    const CisFlags CIS_FLG_RESOLVEIP         = 0x0002;

    /*! Specifies that the service should be invoked by IP address */
    const CisFlags CIS_FLG_CALLBYIP          = 0x0004;

    /*!
     *  A service that is dependent on a valid IP address (as determined by the
     *  RESOLVEIP flag) is shut down if the IP address becomes invalid.
     *
     *  When this flag is set, the service will be restarted when a new address
     *  becomes available. Otherwise; the service will not be restarted.
     */
    const CisFlags CIS_FLG_RESTARTIPTERM     = 0x0008;

    /*! Use to specify the client host name. */ 
    config String hostName = "tisoc";

    /*!
     *  Enter a valid address for static IP configuration.
     *
     *  The default address is null, and signifies that this Ip instance (on
     *  this interface) will run as a DHCP Client, and will obtain the IP
     *  address automatically from a DHCP Server on the network.
     *
     *  The user may also set 'address' to a valid IP address, in which
     *  case the program will not run as a DHCP Client, and instead will use
     *  the static IP address provided to connect to the internet.  When a
     *  static IP address is specified for 'address', the following
     *  instance parameters must be set:
     *  <IP mask, gateway IP address, domain name>
     *
     *  To configure neither of these options, set the value to "none".
     */
    config String address = null;
      
    /*!
     *  The physical device index for which the application's IP address should
     *  be associated with
     */ 
    config Int ifIdx = 1;

    /*!
     *  Set of flags which represent the desired behavior of DHCP Client.
     *  
     *  The following flag values may be set either individually, or by or-ing
     *  flags together:
     *
     *    - CIS_FLG_IFIDXVALID - specifies if the IfIdx field is valid.
     *  
     *    - CIS_FLG_RESOLVEIP - Requests that IfIdx be resolved to an IP
     *      address before service execution is initiated.
     *  
     *    - CIS_FLG_CALLBYIP - Specifies that the service should be invoked by
     *      IP address
     *  
     *    - CIS_FLG_RESTARTIPTERM - A service that is dependent on a valid IP
     *      address.
     *  
     */      
    config CisFlags dhcpClientMode = 1;

    /*! Handle to the service report function used by DHCP. */ 
    config void *dhcpClientPcbServer = "&ti_ndk_config_Global_serviceReport";

    /*!
     *  The IP mask must be specified when using a static IP address. 
     *  
     *  Used for manual/static IP configuration.  If configuring a static IP,
     *  this must be set to a valid mask value.
     */
    config String mask = "255.255.254.0";

    /*!
     *  The IP address of the gateway must be specified when using a static IP
     *  address.
     *  
     *  Used for manual/static IP configuration.  If configuring a static IP,
     *  this must be set to the IP address of the gateway.  
     */ 
    config String gatewayIpAddr = "0.0.0.0";

    /*!
     *  Use to specify the domain name of the network; this must be specified
     *  when using a static IP address.
     *  
     *  Used for manual/static IP configuration.  If configuring a static IP,
     *  this should be a full domain.  For example, use "home1.net", not just
     *  "home1".
     */ 
    config String domainName = "demo.net";

    /*!
     *  Initial value placed in the IP Id field for IP packets generated by the
     *  system.
     */ 
    config Int indexStart = defaultStartIndex;

    /*! Enable or disable IP forwarding. */ 
    config Bool enableForwarding = defaultPortForwarding;

    /*! Enable or disable IP filtering. */ 
    config Bool enableFiltering = defaultPortFiltering;

    /*! Set the maximum reassembly time for IP packets (seconds). */ 
    config Int maxReassemblyTime = defaultMaxReasmTime;

    /*! Set the maximum reassembly size for IP packets. */ 
    config Int maxReassemblySize = defaultMaxReasmSize;

    /*!
     *  Enable route table update on ICMP redirect.
     *  
     *  When true, causes ICMP to automatically create a route to perform
     *  redirects on an IP host to the gateway supplied in the redirect
     *  message. If false, ICMP will also generate a route control message,
     *  and user may take any action they feel is necessary.
     */
    config Bool icmpDoRedirect = defaultIcmpDoRedir;

    /*! Set the time to live value for ICMP packets. */ 
    config Int icmpTimeToLive = defaultIcmpTTL;

    /*! Set the time to live value for ICMP echo packets. */ 
    config Int icmpTimeToLiveEcho = defaultIcmpTTLecho;

    /*!
     *  Enable or disable replies to broadcast.
     *  
     *  When enabled, the stack *does not* reply to ICMP echo request packets
     *  sent to broadcast/directed broadcast addresses.
     */ 
    config Bool icmpDontReplyToBcast = defaultIcmpBcastReply;

    /*!
     *  Enable or disable replies to multicast.
     *  
     *  When enabled, the stack *does not* reply to ICMP echo request packets
     *  sent to multicast addresses.
     */ 
    config Bool icmpDontReplyToMcast = defaultIcmpMcastReply;

    /*!
     *  Enable directed broadcast.
     *  
     *  When enabled, the stack will look for directed broadcast IP packets.
     */ 
    config Bool enableDirectedBroadcast = defaultDirBcast;

    /*! Time in Seconds a Route is "Down" Due to Failed ARP. */ 
    config Int routeDownTime = defaultRteDownTime;

    /*! Time in Seconds a Validated Route is Held. */ 
    config Int routeKeepAliveTime = defaultRteKpAliveTime;

    /*! Default Timeout in Seconds of a Cloned Route. */ 
    config Int routeCloneTimeout = defaultRteCloneTimeout;

    /*! Default MTU for Local Routes. */ 
    config Int routeDefaultMtu = defaultRteMtu;

    /*! Enables Route Control messages. */ 
    config Bool routeCtrlEnableDebug = defaultRteCtrlDbg;

    /*! Time in seconds to periodically send a router advertisement. */
    config Int routeAdvertisePeriod = defaultRteAdverPer;

    /*!
     *  If sending router advertisements, this value will be used for the ICMP
     *  message lifetime.
     */  
    config Int routeAdvertiseLifetime = defaultRteAdverLife;

    /*!
     *  If sending router advertisements, this value will be used for the ICMP
     *  message route preference level.  
     */ 
    config Int routeAdvertisePrefLvl = defaultRteAdverLvl;

    /*! Default TTL for packets sent via IP socket. */ 
    config Int socketTimeToLive = defaultSockTTL;

    /*! Default TOS (Type of Service) for packets sent via a socket. */ 
    config Int socketTos = defaultSockTos;

    /*! Maximum number of connections on a listening socket. */ 
    config Int socketMaxConnections = defaultSockMaxConn;

    /*! Maximum Time in Seconds to Wait on a Connect. */ 
    config Int socketConnectTimeout = defaultSockConnTimeout;

    /*! Maximum Time in Seconds to Wait on Socket Read/Write. */ 
    config Int socketIoTimeout = defaultSockIoTimeout;

    /*! Min Size in Bytes for Socket "Able to Write." */ 
    config Int socketBufMinTxSize = defaultSockBufTxSz;

    /*! Min Size in Bytes for Socket "Able to Read." */ 
    config Int socketBufMinRxSize = defaultSockBufRxSz;

    /*! Maximum Time in Seconds to Wait on Pipe Read/Write. */ 
    config Int pipeIoTimeout = defaultPipIoTimeout;

    /*! Size in Bytes of Each End of a Pipe Buffer. */ 
    config Int pipeMaxBufSize = defaultPipMaxBufSz;

    /*! Min Size in Bytes for Pipe Able to Write. */ 
    config Int pipeBufMinTxSize = defaultPipBufTxSz;

    /*! Min Size in Bytes for Pipe Able to Write. */ 
    config Int pipeBufMinRxSize = defaultPipBufRxSz;

    /*! @_nodoc
     *
     * internal use only.  Intermediate variables mapped to Grace checkboxes,
     * used to update 'mode' dhcpClientMode variable.
     */
    config Bool IfIdXValid = true;

    /*! @_nodoc
     *
     * internal use only.  Intermediate variables mapped to Grace checkboxes,
     * used to update 'mode' dhcpClientMode variable.
     */
    config Bool ResolveIP = false;

    /*! @_nodoc
     *
     * internal use only.  Intermediate variables mapped to Grace checkboxes,
     * used to update 'mode' dhcpClientMode variable.
     */
    config Bool CallByIP = false;

    /*! @_nodoc
     *
     * internal use only.  Intermediate variables mapped to Grace checkboxes,
     * used to update 'mode' dhcpClientMode variable.
     */
    config Bool RestartIPTerm = false;

    /*! @_nodoc
     *
     * internal use only.  Intermediate variables mapped to Grace checkboxes,
     * used to update 'mode' dhcpClientMode variable.
     */
    config Bool autoIp = true;

    /*! @_nodoc
     *
     * internal use only.  Used to set network types - DHCP server, VLAN
     */
    config UInt NetType = 0;
}

