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
 *  ======== Http.xdc ========
 *  Http module definition and inital values
 */

/*!
 *  ======== Http ======== 
 *  NDK HTTP server settings and configuration.
 *  
 *  The Http module is used to create an HTTP server on the target processor.
 *  Using the Http module, the user is able easily set up and add an HTTP
 *  server to their application.
 *  
 *  Summary of Steps:
 *  
 *  The following is a summary of required steps to add a HTTP server to an NDK
 *  application:
 *  
 *  1. Use the Http module
 *  
 *  2. Create a Http parameter structure and configure its properties.
 *  
 *  3. Create an Http module instance based on the properties set in the
 *     configuration structure.
 *  
 *  Detailed Steps:
 *  
 *  1. To add an HTTP server using the Http module, it's first necessary to use
 *     the Http module in the application RTSC configuration file:
 *  @p(code)
 *  var Http = xdc.useModule('ti.ndk.config.Http');
 *  @p
 *  2. After the Http module is used, it can then be referenced to create a 
 *     Http parameter structure, through which the properties of the HTTP
 *     server being added can be configured:
 *  @p(code)
 *  var httpParams = new Http.Params();
 *  httpParams.port = 1003;
 *  httpParams.maxCon = 11;
 *  @p
 *  3. Once the properties of the HTTP server have been set (via the parameter
 *     structure), an Http instance may be created based on those parameters:
 *  @p(code)
 *  var httpInst = Http.create(httpParams);
 *  @p
 *  
 *  As the above steps indicate, the Http module is configured on a per
 *  instance basis.  The steps above detail how to configure a single Http
 *  instance, but, it is also possible to create several Http servers, all
 *  running on the same target processor, which accept connections on
 *  different ports.
 *  
 *  For example, the above steps illustrate how to add a HTTP server which
 *  accepts connections on port 1003.  To add a second HTTP server, which
 *  accepts connections on the port 1004, the following code could be
 *  added:
 *  @p(code)
 *  var http2Params = new Http.Params();
 *  http2Params.port = 1004;
 *  var http2Inst = Http.create(http2Params);
 *  @p
 */  

@Template("./Http.xdt")

metaonly module Http {

    /*! Function signature for CISARGS struct service reporting function */
    typedef Void (*httpServiceFxn)(Int, Int, Int, Void *);

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
     *  Creates an Http instance.
     */
    create();

instance:

    /*!
     *  Specifies the maximum number of hosts that may connect to the HTTP
     *  server running on this port (1 - 24).
     */
    config Int maxCon = 8;

    /*!
     *  Specifies the port number which this HTTP server will accept
     *  connections.
     */ 
    config Int port = 80;

    /*!
     *  Set of flags which represent the desired behavior of the HTTP Server.
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
    config CisFlags mode = CIS_FLG_IFIDXVALID;

    /*!
     *  The physical device index on which the HTTP server shall be
     *  executed.  Must be greater than zero.
     */
    config Int ifIdx = 1;

    /*! 
     *  The IP address on which to initiate this service.
     *  
     *  To accept a connection from any IP, specify INADDR_ANY.
     */ 
    config String ipAddr = "INADDR_ANY";

    /*! HTTP service reporting function. */
    config httpServiceFxn pCbSrv = "&ti_ndk_config_Global_serviceReport";

    /*! CGI functions and names */
    config string cgiFunctions[string];

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
