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
 *  ======== Nat.xdc ========
 *  Nat module definition and inital values
 */

/*!
 *  ======== Nat ======== 
 *  NDK Network Address Translation (NAT) settings and configuration.
 *  
 */  

@Template("./Nat.xdt")

metaonly module Nat {

    /*! Function signature for CISARGS struct service reporting function */
    typedef Void (*natServiceFxn)(Int, Int, Int, Void *);

    /*! Type used to specify bits in mode */
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

    /*!
     *  ======== create ========
     *  Creates an Nat instance.
     */
    create();

instance:

    /*! Specifies the NAT group virtual network IP address. */
    config String virtualIpAddr = null;

    /*! Specifies the subnet mask of the NAT group virtual network. */
    config String virtualMask = "255.255.254.0";

    /*! Specifies the IP MTU limit (1500 for ethernet, 1492 for PPPoE, ...) */
    config Int mtu = 1500;

    /*!
     *  Set of flags which represent the desired behavior of the telnet Server.
     *  
     *  The following flag values may be set either individually, or by or-ing
     *  flags together:
     * @p(blist)
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
     * @p
     */
    config Int mode = 0;

    /*!
     *  The physical device index on which the NAT server shall be
     *  executed.  Must be greater than zero.
     */
    config Int ifIdx = 1;

    /*! Nat service reporting function. */
    config natServiceFxn pCbSrv = "&ti_ndk_config_Global_serviceReport";

    /*! @_nodoc
     *
     * internal use only.  Intermediate variables mapped to Grace checkboxes,
     * used to update 'mode' flags variable.
     */
    config Bool IfIdXValid = false;

    /*! @_nodoc
     *
     * internal use only.  Intermediate variables mapped to Grace checkboxes,
     * used to update 'mode' flags variable.
     */
    config Bool ResolveIP = false;

    /*! @_nodoc
     *
     * internal use only.  Intermediate variables mapped to Grace checkboxes,
     * used to update 'mode' flags variable.
     */
    config Bool CallByIP = false;

    /*! @_nodoc
     *
     * internal use only.  Intermediate variables mapped to Grace checkboxes,
     * used to update 'mode' flags variable.
     */
    config Bool RestartIPTerm = false;
}
