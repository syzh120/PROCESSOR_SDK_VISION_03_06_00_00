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
 *  ======== NdkProductView.xs ========
 *
 */
function module$meta$init()
{
    this.ti_ndk_config_Global.elemName = "Networking";
    this.ti_ndk_config_Global.moduleName = "ti.ndk.config.Global";
    this.ti_ndk_config_Global.iconFileName = "icons/world.png";

    this.ti_ndk_config_Emac.elemName = "EMAC";
    this.ti_ndk_config_Emac.moduleName = "ti.ndk.config.Emac";
    this.ti_ndk_config_Emac.iconFileName = "icons/connect.png";

    this.ti_ndk_config_Ppp.elemName = "PPP";
    this.ti_ndk_config_Ppp.moduleName = "ti.ndk.config.Ppp";
    this.ti_ndk_config_Ppp.iconFileName = "icons/connect.png";

    this.ti_ndk_config_Pppoe.elemName = "PPPoE";
    this.ti_ndk_config_Pppoe.moduleName = "ti.ndk.config.Pppoe";
    this.ti_ndk_config_Pppoe.iconFileName = "icons/connect.png";

    this.ti_ndk_config_Ip.elemName = "IP";
    this.ti_ndk_config_Ip.moduleName = "ti.ndk.config.Ip";
    this.ti_ndk_config_Ip.iconFileName = "icons/connect.png";

    this.ti_ndk_config_Dns.elemName = "DNS";
    this.ti_ndk_config_Dns.moduleName = "ti.ndk.config.Dns";
    this.ti_ndk_config_Dns.iconFileName = "icons/book.png";

    this.ti_ndk_config_Icmp.elemName = "ICMP";
    this.ti_ndk_config_Icmp.moduleName = "ti.ndk.config.Icmp";
    this.ti_ndk_config_Icmp.iconFileName = "icons/connect.png";

    this.ti_ndk_config_Udp.elemName = "UDP";
    this.ti_ndk_config_Udp.moduleName = "ti.ndk.config.Udp";
    this.ti_ndk_config_Udp.iconFileName = "icons/connect.png";

    this.ti_ndk_config_Tcp.elemName = "TCP";
    this.ti_ndk_config_Tcp.moduleName = "ti.ndk.config.Tcp";
    this.ti_ndk_config_Tcp.iconFileName = "icons/connect.png";

    this.ti_ndk_config_Nat.elemName = "NAT";
    this.ti_ndk_config_Nat.moduleName = "ti.ndk.config.Nat";
    this.ti_ndk_config_Nat.iconFileName = "icons/connect.png";

    this.ti_ndk_config_DhcpClient.elemName = "DHCPClient";
    this.ti_ndk_config_DhcpClient.moduleName = "ti.ndk.config.DhcpClient";
    this.ti_ndk_config_DhcpClient.iconFileName = "icons/connect.png";

    this.ti_ndk_config_DhcpServer.elemName = "DHCPServer";
    this.ti_ndk_config_DhcpServer.moduleName = "ti.ndk.config.DhcpServer";
    this.ti_ndk_config_DhcpServer.iconFileName = "icons/connect.png";

    this.ti_ndk_config_Route.elemName = "Route";
    this.ti_ndk_config_Route.moduleName = "ti.ndk.config.Route";
    this.ti_ndk_config_Route.iconFileName = "icons/connect.png";
   
    this.ti_ndk_config_Telnet.elemName = "Telnet";
    this.ti_ndk_config_Telnet.moduleName = "ti.ndk.config.Telnet";
    this.ti_ndk_config_Telnet.iconFileName = "icons/connect.png";
    
    this.ti_ndk_config_Http.elemName = "HTTP";
    this.ti_ndk_config_Http.moduleName = "ti.ndk.config.Http";
    this.ti_ndk_config_Http.iconFileName = "icons/computer_link.png";

    /* groups */
    this.applicationLayerGroup.elemName = "Application Layer";
    this.applicationLayerGroup.moduleName = null;
    this.applicationLayerGroup.iconFileName = "icons/connect.png";
    this.applicationLayerGroup.elemArray = [
        this.ti_ndk_config_DhcpClient,
        this.ti_ndk_config_DhcpServer,
        this.ti_ndk_config_Dns,
        this.ti_ndk_config_Http,
        this.ti_ndk_config_Telnet
    ];

    this.transportLayerGroup.elemName = "Transport Layer";
    this.transportLayerGroup.moduleName = null;
    this.transportLayerGroup.iconFileName = "icons/connect.png";
    this.transportLayerGroup.elemArray = [
        this.ti_ndk_config_Tcp,
        this.ti_ndk_config_Udp,
        this.ti_ndk_config_Nat,
    ];

    this.networkLayerGroup.elemName = "Network Layer";
    this.networkLayerGroup.moduleName = null;
    this.networkLayerGroup.iconFileName = "icons/connect.png";
    this.networkLayerGroup.elemArray = [
        this.ti_ndk_config_Ip,
        this.ti_ndk_config_Icmp,
        this.ti_ndk_config_Route,
    ];

    this.datalinkLayerGroup.elemName = "Data Link Layer";
    this.datalinkLayerGroup.moduleName = null;
    this.datalinkLayerGroup.iconFileName = "icons/connect.png";
    this.datalinkLayerGroup.elemArray = [
        this.ti_ndk_config_Ppp,
        this.ti_ndk_config_Pppoe,
    ];


    /* product */
    this.ndkProduct.elemName = "NDK Core Stack";
    this.ndkProduct.moduleName = null;
    this.ndkProduct.iconFileName = "icons/bios.gif";
    this.ndkProduct.elemArray = [
        this.ti_ndk_config_Global,
        this.applicationLayerGroup,
        this.transportLayerGroup,
        this.networkLayerGroup,
        this.datalinkLayerGroup,
    ]; 
}

/*
 *  ======== getProductDescriptor ========
 */
function getProductDescriptor() 
{
    return this.ndkProduct;
}
