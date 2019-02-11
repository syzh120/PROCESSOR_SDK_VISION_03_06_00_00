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
/*!
 * ======== NdkProductView.xdc ========
 * @_nodoc
 */

metaonly module NdkProductView inherits xdc.tools.product.IProductView {

    /*
     *  homeModule
     *
     *  Specify the home module for the MCU SDK
     */
    override config String homeModule = "ti.ndk.config.Global";

    /*
     *  linksToArray
     *
     *  Specify other products that are "linked to" from the NDK
     */
    override config String linksToArray[] = [
    ];

    /* modules */
    config ProductElemDesc ti_ndk_config_DhcpClient;
    config ProductElemDesc ti_ndk_config_DhcpServer;
    config ProductElemDesc ti_ndk_config_Dns;
    config ProductElemDesc ti_ndk_config_Emac;
    config ProductElemDesc ti_ndk_config_Global;
    config ProductElemDesc ti_ndk_config_Http;
    config ProductElemDesc ti_ndk_config_Icmp;
    config ProductElemDesc ti_ndk_config_Ip;
    config ProductElemDesc ti_ndk_config_Nat;
    config ProductElemDesc ti_ndk_config_Ppp;
    config ProductElemDesc ti_ndk_config_Pppoe;
    config ProductElemDesc ti_ndk_config_Route;
    config ProductElemDesc ti_ndk_config_Tcp;
    config ProductElemDesc ti_ndk_config_Telnet;
    config ProductElemDesc ti_ndk_config_Udp;

    /* groups */
    config ProductElemDesc applicationLayerGroup;
    config ProductElemDesc transportLayerGroup;
    config ProductElemDesc networkLayerGroup;
    config ProductElemDesc datalinkLayerGroup;


    /* product */
    config ProductElemDesc ndkProduct;
};
