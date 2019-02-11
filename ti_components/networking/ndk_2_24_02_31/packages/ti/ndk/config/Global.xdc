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
 *  ======== Global.xdc ========
 *  Global module definition file and initial values.
 */

/*!
 *  ======== Global ========
 *  High level NDK stack configuration and settings.
 *  
 *  The Global module is required to be used by an NDK application.  At
 *  minimum, it is used to link in the default flavor of the NDK stack library,
 *  as well as the other core libraries, and generates no code.
 *
 *  However, if the user desires, it may be used to link in libraries,
 *  configure global stack settings, and generate NDK C configuration code.
 *  
 *  The following libraries are linked in by default via the Global Module:
 *  @p(blist)
 *      - stack.lib
 *      - cgi.lib
 *      - console.lib
 *      - hdlc.lib
 *      - miniPrintf.lib
 *      - netctrl.lib
 *      - nettool.lib
 *      - os.lib
 *      - servers.lib
 *  @p
 *  
 *  The user can select which version of "stack.lib" to use via the following
 *  configuration parameters:
 *  
 *  @p(code)
 *      config stackLibProtocol stackLibType
 *      config IPv6
 *  @p
 *  
 *  stackLibType may be set to the following values. If the configuration
 *  parameter 'IPv6' is set to 'true', then this will result in the
 *  following IPv6 library selections:
 *  
 *  @p(blist)
 *  - Global.MIN                : stk6.lib
 *  - Global.NONE               : stack.lib (default)
 *  - Global.NAT                : stk6_nat.lib
 *  - Global.NAT_PPP            : stk6_nat_ppp.lib
 *  - Global.NAT_PPP_PPPOE      : stk6_nat_ppp_pppoe.lib
 *  - Global.PPP                : stk6_ppp.lib
 *  - Global.PPP_PPPOE          : stk6_ppp_pppoe.lib
 *  @p
 *  
 *  If the configuration parameter 'IPv6' is set to 'false', then this will
 *  result in the following IPv4 library selections:
 *  
 *  @p(blist)
 *  - Global.MIN                : stk.lib
 *  - Global.NONE               : stk_ppp_pppoe.lib (default)
 *  - Global.NAT                : stk_nat.lib
 *  - Global.NAT_PPP            : stk_nat_ppp.lib
 *  - Global.NAT_PPP_PPPOE      : stk_nat_ppp_pppoe.lib
 *  - Global.PPP                : stk_ppp.lib
 *  - Global.PPP_PPPOE          : stk_ppp_pppoe.lib
 *  @p
 *  
 *  In addition to NDK library selection, the Global module may be used to
 *  change global configuration settings of the stack.  This includes settings
 *  for the:
 *  @p(blist)
 *       - NDK OSAL
 *       - Debug settings
 *       - Default stack task priority levels and stack sizes
 *       - Priority level and operating mode of the NDK scheduler thread.
 *       - Calling user defined hook functions
 *       - Enabling or disabling code generation.
 *  @p
 *  
 *  Note that the Global module generates NDK C configuration code in order to
 *  manipulate the settings of the above mentioned items.  In order for these
 *  settings to take effect, code generation must be enabled in the Global
 *  module.
 *
 *  If the code generation feature is enabled, then it's important to note that
 *  the C code for several functions will be created, which may cause a
 *  conflict if a program already has defined these functions, and then
 *  later enables code generation.  These functions may also be updated
 *  with C API calls that will correspond to the RTSC configuration settings
 *  that were made.
 *  
 *  The following list is a list of the C functions that are generated as a
 *  result of using the NDK RTSC configuration's code generating feature:
 *  @p(blist)
 *  - ti_ndk_config_Global_stackThread(): The NDK stack thread function.
 *  - NetworkOpen(): function that is called automatically by NC_NetStart().
 *  - NetworkClose(): function that is called automatically by NC_NetStart().
 *  - NetworkIPAddr(): function that is called automatically by NC_NetStart().
 *  - ti_ndk_config_Global_serviceReport(): Service report callback function.
 *  @p
 *  
 *  The NDK RTSC configuration and code generation feature is really intended
 *  to be used with a new NDK program, not with an existing one.  For example,
 *  if the user has an already existing NDK program, and they wish to change
 *  one of the configuration settings to that already existing program, then
 *  the NDK RTSC configuration should *not* be used.  If the user were to use
 *  the NDK RTSC configuration in this manner, then the resulting program
 *  behavior would become unpredictable, due to having multiple NDK stack
 *  threads running with different configuration settings.
 *  
 *  However, one could create a new NDK program that uses the RTSC
 *  configuration in order to easily see the C configuration code needed to
 *  change a particular stack setting.  This generated C configuration code
 *  could then be copied from the new NDK program, and then pasted into the
 *  user's existing program to add that setting.
 *  
 *  User Defined Hook Functions
 *
 *  Since the NDK stack thread function (as well as the other functions listed
 *  above) is generated when using this code generation feature, the user will
 *  not be able to directly add custom code into it.  In order to allow this,
 *  a set of hook functions are provided.  These hook functions may be called
 *  from various places from within the generated code.  The user can define
 *  these hook functions as appropriate, and then assign the function names to
 *  the Global modules ndkHookFxn configuration parameters.  For each
 *  ndkHookFxn configuration paramter that is defined, a call to that
 *  function will be added into the generated C code, as described by that
 *  ndkHookFxn parameter.  Note that for some of these hook calls will be made
 *  with useful parameters in order to pass down information into the user's
 *  code (please refer to the hook descriptions for details on arguments
 *  passed and prototype signature for these hooks).
 *  
 *  Note if the user specifies a hook function in the RTSC configuration
 *  script, but does not define this function in their C code, a linker error
 *  will result.
 */  

@Template("./Global.xdt")

metaonly module Global {

    /*!
     *  ======== NetEventSchedPri ========
     *  This defines the legal values for the priority setting for the Network
     *  event scheduler task.
     */
    enum NetEventSchedPri {
        NC_PRIORITY_LOW,  /*! Low Priority */
        NC_PRIORITY_HIGH  /*! High Priority */
    }

    /*!
     *  ======== NetEventSchedOp ========
     *  This defines the legal values for the operating mode setting for the
     *  Network event scheduler task.
     */
    enum NetEventSchedOp {
        NC_OPMODE_POLLING,  /*! Polling Mode */
        NC_OPMODE_INTERRUPT /*! Interrupt Mode */
    }

    /*!
     *  ======== DebugLevel ========
     *  This defines the legal values for the severity level of debug messages
     *  and debug aborts in the stack.
     */
    enum DebugLevel {
        DBG_INFO = 1,  /*! Information Messages (DBG_INFO)*/
        DBG_WARN,  /*! Warning Messages (DBG_WARN)*/
        DBG_ERROR, /*! Error Messages (DBG_ERROR)*/
        DBG_NONE   /*! No Messages (DBG_NONE)*/
    }

    /*!
     *  ======== StackLibProtocol ======== 
     *  Defines the set of legal stack library types.
     */
    enum StackLibProtocol {
        NONE,
        NAT,
       	NAT_PPP,
       	NAT_PPP_PPPOE,
       	PPP,
       	PPP_PPPOE,
        MIN
    };

    /*! This data structure is used to add a user account */
    struct Account {
        String username;
        String password;
    };

    /*! Array that holds all of the user accounts to be created. */
    config Account userAccounts[length] = [];

    /*! Function signature for user defined NDK hook functions */
    typedef Void (*ndkHookFxn)();

    /*!
     *  ======== StackRunModeFlags ========
     *  This defines the legal values for the flags that can be used for setting
     *  multiCoreStackRun, which determines the processors for which the stack
     *  should run on when multiple cores are present.
     */

    /*! Type used to specify bits in mode */
    typedef Bits32 StackRunModeFlags;

    const StackRunModeFlags STACKRUN_FLG_CORE_0       = 0x1;
    const StackRunModeFlags STACKRUN_FLG_CORE_1       = 0x2;
    const StackRunModeFlags STACKRUN_FLG_CORE_2       = 0x4;
    const StackRunModeFlags STACKRUN_FLG_CORE_3       = 0x8;
    const StackRunModeFlags STACKRUN_FLG_CORE_4       = 0x10;
    const StackRunModeFlags STACKRUN_FLG_CORE_5       = 0x20;
    const StackRunModeFlags STACKRUN_FLG_CORE_6       = 0x40;
    const StackRunModeFlags STACKRUN_FLG_CORE_7       = 0x80;
    const StackRunModeFlags STACKRUN_FLG_CORE_8       = 0x100;
    const StackRunModeFlags STACKRUN_FLG_CORE_9       = 0x200;
    const StackRunModeFlags STACKRUN_FLG_CORE_10      = 0x400;
    const StackRunModeFlags STACKRUN_FLG_CORE_11      = 0x800;
    const StackRunModeFlags STACKRUN_FLG_CORE_12      = 0x1000;
    const StackRunModeFlags STACKRUN_FLG_CORE_13      = 0x2000;
    const StackRunModeFlags STACKRUN_FLG_CORE_14      = 0x4000;
    const StackRunModeFlags STACKRUN_FLG_CORE_15      = 0x8000;
    const StackRunModeFlags STACKRUN_FLG_CORE_16      = 0x10000;
    const StackRunModeFlags STACKRUN_FLG_CORE_17      = 0x20000;
    const StackRunModeFlags STACKRUN_FLG_CORE_18      = 0x40000;
    const StackRunModeFlags STACKRUN_FLG_CORE_19      = 0x80000;
    const StackRunModeFlags STACKRUN_FLG_CORE_20      = 0x100000;
    const StackRunModeFlags STACKRUN_FLG_CORE_21      = 0x200000;
    const StackRunModeFlags STACKRUN_FLG_CORE_22      = 0x400000;
    const StackRunModeFlags STACKRUN_FLG_CORE_23      = 0x800000;
    const StackRunModeFlags STACKRUN_FLG_CORE_24      = 0x1000000;
    const StackRunModeFlags STACKRUN_FLG_CORE_25      = 0x2000000;
    const StackRunModeFlags STACKRUN_FLG_CORE_26      = 0x4000000;
    const StackRunModeFlags STACKRUN_FLG_CORE_27      = 0x8000000;
    const StackRunModeFlags STACKRUN_FLG_CORE_28      = 0x10000000;
    const StackRunModeFlags STACKRUN_FLG_CORE_29      = 0x20000000;
    const StackRunModeFlags STACKRUN_FLG_CORE_30      = 0x40000000;
    const StackRunModeFlags STACKRUN_FLG_CORE_31      = 0x80000000;

    /*!
     * Default values
     *  @_nodoc
     */
    const DebugLevel defaultDebugPrintLevel = DBG_INFO;
    const DebugLevel defaultDebugAbortLevel = DBG_ERROR;
    const Int defaultLowTaskPriLevel  = 3;
    const Int defaultNormTaskPriLevel = 5;
    const Int defaultHighTaskPriLevel = 7;
    const Int defaultKernTaskPriLevel = 9;
    const Int defaultLowTaskStackSize  = 3072;
    const Int defaultNormTaskStackSize = 4096;
    const Int defaultHighTaskStackSize = 5120;
    const Int defaultNdkTaskStackSize  = 8192;
    const Int defaultNdkTickPeriod     = 100;


    /*!
     *  Set of flags which used to specify which cores the NDK stack should run
     *  on for multi-core processors.  Default is to run the stack on core 0.
     *
     *  This configuration parameter is only valid for C6000 multi-core
     *  processors.
     *  
     *  The following flag values may be set either individually, or by OR-ing
     *  flags together, in order to run the stack on other cores
     *  (or combination of cores):
     *
     *  Currently supports up to 32 cores.
     *
     * @p(blist)
     *    - STACKRUN_FLG_CORE_0 - specifies that the stack should run on core 0
     *  
     *    - STACKRUN_FLG_CORE_1 - specifies that the stack should run on core 1
     *  
     *    - STACKRUN_FLG_CORE_2 - specifies that the stack should run on core 2
     *  
     *    - STACKRUN_FLG_CORE_3 - specifies that the stack should run on core 3
     *  
     *    - STACKRUN_FLG_CORE_4 - specifies that the stack should run on core 4
     *  
     *    - STACKRUN_FLG_CORE_5 - specifies that the stack should run on core 5
     *  
     * @p
     */
    config StackRunModeFlags multiCoreStackRunMode = STACKRUN_FLG_CORE_0;

    /*!
     *  When true, the IPv6 version of the NDK libraries will be used, otherwise
     *  the IPv4 versions will be linked.
     *
     *  Default is IPv6.
     */
    config Bool IPv6 = true;

    /*!
     *  Variable used for choosing the NDK library to be linked into a program.
     *  Default stack library is PPP_PPPOE
     *
     *  NONE:          Links in support for NAT, PPP, and PPPoE (default).
     *  NAT:           Links in support for NAT.
     *  NAT_PPP:       Links in support for NAT and PPP.
     *  NAT_PPP_PPPOE: Links in support for NAT, PPP, and PPPoE.
     *  PPP:           Links in support for PPP.
     *  PPP_PPPOE:     Links in support for PPP and PPPoE.
     *  MIN:           Minimal stack library.  Does not link any support NAT, PPP or PPPoE.
     */
    config StackLibProtocol stackLibType = NONE;

    /*!
     *  Variable to cause the semaphore version of the NDK libraries to be linked into a program.
     * 
     *  true: link libraries which use Semaphore for kernel mode. 
     *  false: (Default) link libraries which use Task priority for kernel mode. 
     */
    config Bool useSemLibs = false;

    /*!
     *  Sets the severity level of system debug messages that are recorded to
     *  the debug log.
     */
    config DebugLevel debugPrintLevel = defaultDebugPrintLevel;

    /*!
     *  Sets the severity level of system debug messages that that result in a
     *  system shutdown.
     */
    config DebugLevel debugAbortLevel = defaultDebugAbortLevel;

    /*! Sets the priority value for low priority NDK tasks */
    config Int lowTaskPriLevel  = defaultLowTaskPriLevel;

    /*! Sets the priority value for normal priority NDK tasks */
    config Int normTaskPriLevel = defaultNormTaskPriLevel;

    /*! Sets the priority value for high priority NDK tasks */
    config Int highTaskPriLevel = defaultHighTaskPriLevel;

    /*! Sets the priority value for kernel priority NDK tasks */
    config Int kernTaskPriLevel = defaultKernTaskPriLevel;

    /*! Sets the default stack size for low priority NDK tasks */
    config Int lowTaskStackSize = defaultLowTaskStackSize;

    /*! Sets the default stack size for normal priority NDK tasks */
    config Int normTaskStackSize = defaultNormTaskStackSize;

    /*! Sets the default stack size for high priority NDK tasks */
    config Int highTaskStackSize = defaultHighTaskStackSize;

    /*!
     *  Enables the NDK stack thread and C stack configuration code to be
     *  generated automatically for the application. When false, no C code is
     *  generated, but NDK libraries are still linked into the application
     *  automatically.
     */
    config Bool enableCodeGeneration = true;

    /*!
     *  Automatically open/close file descriptor session
     *  
     *  When true, calls to fdOpenSession and fdCloseSession will be made
     *  automatically for dynamically created Tasks.  This allows standard BSD
     *  sockets code fit more easily into an NDK application.
     *  
     *  Note that this is only supported for dynamically created tasks that are
     *  created from within Task context (i.e. from within an already running
     *  Task function).  Tasks created from the configuration or dynamically
     *  in main or a Hwi or Swi thread will not have support for this feature.  
     *
     *  Disabled by default.
     */
    config Bool autoOpenCloseFD = false;


    /*!
     *  Allows user to define their own implementation of the NDK stack thread
     *
     *  If set, the user is responsible for defining the NDK stack
     *  thread, which has no return value and has two parameters of type UArg.
     *
     *  For example (C code):
     *
     *      Void MYMODULE_stackThreadUser(UArg arg0, UArg arg1);
     *
     *  And in the configuration file:
     *
     *      Global.stackThreadUser = '&MYMODULE_stackThreadUser';
     *
     *  The user is also responsible for creating the SYS/BIOS Clock
     *  instance for the NDK 100ms heartbeat, calling appropriate NC_* APIs,
     *  and adding the appropriate C run time configuration code that matches
     *  the settings of the BIOS config file in the function. (e.g. if
     *  configuring the Ip module, the stack thread must call NC_SystemOpen(),
     *  'ti_ndk_config_ip_init(hCfg)', etc.).
     */
    config ndkHookFxn stackThreadUser = null;

    /*! Priority of the generated NDK task 'ti_ndk_config_Global_stackThread' */
    config Int ndkThreadPri = defaultNormTaskPriLevel;

    /*! Stack size of the generated NDK task 'ti_ndk_config_Global_stackThread' */
    config Int ndkThreadStackSize = defaultNdkTaskStackSize;

    /*!
     *  Tick period in Clock ticks for the NDK heartbeat
     *
     *  Default value set to 100 ticks to match the default tick rate of
     *  1 tick = 1 millisecond.  Note that if the a custom Timer is configured
     *  to drive the Clock module with a period other than 1 millisecond
     *  per tick, then you must adjust the ndkTickPeriod accordingly.
    */
    config Int ndkTickPeriod = defaultNdkTickPeriod;

    /*! The priority level at which the NDK net scheduler task runs. */
    config NetEventSchedPri netSchedulerPri = NC_PRIORITY_LOW;

    /*! The manner at which the NDK net scheduler task runs. */
    config NetEventSchedOp netSchedulerOpMode = NC_OPMODE_INTERRUPT;

    /*! The name for authorization realm 1 */
    config String realm1Name = null;

    /*! The name for authorization realm 2 */
    config String realm2Name = null;

    /*! The name for authorization realm 3 */
    config String realm3Name = null;

    /*! The name for authorization realm 4 */
    config String realm4Name = null;

    /*!
     *  Packet Buffer Manager (PBM) number of frames
     *
     *  Used to set the size of PBM 'pBufMem[]'.
     */
    config Int pktNumFrameBufs = 192;

    /*!
     *  Packet Buffer Manager (PBM) size frame buffer
     *
     *  Used to set the size of PBM 'pHdrMem[]'.
     */
    config Int pktSizeFrameBuf = 1536;

    /*!
     *  Packet Buffer Manager (PBM) buffer data section
     *
     *  Section to place PBM buffers 'pBufMem' and 'pHdrMem'.
     */
    config String pbmDataSection = ".far:NDK_PACKETMEM";

    /*!
     *  Memory Manager page size
     *
     *  Used to set the size of OSAL's 'pitBuffer[]'.
     */
    config Int memRawPageSize = 3072;

    /*!
     *  Memory Manager page count
     *
     *  Used to set the size of OSAL's 'pit[]' and 'pitBuffer[]'.
     */
    config Int memRawPageCount = 16;

    /*!
     *  Memory Manager buffer data section
     *
     *  Section to place NDK memory manager buffers 'pit[]', 'pitBuffer[]' and
     *   'Id2Size[]'.
     */
    config String memDataSection = ".far:NDK_MMBUFFER";

    /*!
     *  User defined hook function to run in the NDK stack thread
     *  ti_ndk_config_Global_stackThread().  This function will run at
     *  the very beginning of the stack thread, before the call to
     *  NC_SystemOpen() is made.  It will not be passed any arguments.
     *
     *  For example, if your configuration sets 'stackBeginHook' to a function
     *  called "myBeginFxn":
     *
     *      var Global = xdc.useModule('ti.ndk.config.Global');
     *      Global.stackBeginHook = '&myBeginFxn';
     *
     *  Then a call to "myBeginFxn" will be generated as follows:
     *
     *      myBeginFxn();
     *
     */
    config ndkHookFxn stackBeginHook = null;

    /*!
     *  User defined hook function to run in the NDK stack thread
     *  ti_ndk_config_Global_stackThread().  This function will run immediately
     *  after the function call to create a new configuration, CfgNew(), and
     *  will be passed the handle to that configuration.
     *
     *  For example, if your configuration sets 'stackInitHook' to a function
     *  called "myInitFxn":
     *
     *      var Global = xdc.useModule('ti.ndk.config.Global');
     *      Global.stackInitHook = '&myInitFxn';
     *
     *  Then a call to "myInitFxn" will be generated as follows:
     *
     *      myInitFxn(hCfg);
     *
     *  Therefore, if you wish to use the configuration handle in "myInitFxn",
     *  then you should define it so that it can accept the handle passed to it:
     *  
     *      Void myInitFxn(HANDLE hCfg)
     *      {  
     *          ...
     *      }  
     */
    config ndkHookFxn stackInitHook = null;

    /*!
     *  User defined hook function to run in the NDK stack thread
     *  ti_ndk_config_Global_stackThread().  This function will run immediately
     *  after the return from NC_NetStart() and within the while() loop which contains
     *  the NC_NetStart() call.  It will be passed a handle to the configuration
     *  as well as the valued returned from NC_NetStart.
     *
     *  For example, if your configuration sets 'stackRebootHook' to a function
     *  called "myRebootFxn":
     *
     *      var Global = xdc.useModule('ti.ndk.config.Global');
     *      Global.stackRebootHook = '&myRebootFxn';
     *
     *  Then a call to "myRebootFxn" will be generated after the call to
     *  NC_NetStart(), but within the do/while loop, which allows this hook to
     *  run for the case of the NDK stack thread rebooting.  The generated code
     *  will look similar to the following:
     *
     *      do
     *      {
     *           rc = NC_NetStart(hCfg, ti_ndk_config_Global_NetworkOpen,
     *                   ti_ndk_config_Global_NetworkClose,
     *                   ti_ndk_config_Global_NetworkIPAddr);
     *
     *           myRebootFxn(hCfg, rc);
     *
     *      } while( rc > 0 );
     *
     *
     *  Therefore, if you wish to use the configuration handle and return code
     *  in "myRebootFxn", then you should define it so that it has such
     *  parameters:
     *
     *      Void myRebootFxn(HANDLE hCfg, int rc)
     *      {
     *          ...
     *      }
     */
    config ndkHookFxn stackRebootHook = null;

    /*!
     *  User defined hook function to run in the NDK stack thread
     *  ti_ndk_config_Global_stackThread().  This function will run immediately
     *  after exiting from the while() loop which contains the call to
     *  NC_NetStart(), but before the subsequent calls to CfgFree( hCfg ) and
     *  NC_SystemClose().  It will be passed a handle to the configuration as
     *  well as the valued returned from NC_NetStart.
     *
     *  For example, if your configuration sets 'stackDeleteHook' to a function
     *  called "myDeleteFxn":
     *
     *      var Global = xdc.useModule('ti.ndk.config.Global');
     *      Global.stackDeleteHook = '&myDeleteFxn';
     *
     *  Then a call to "myDeleteFxn" will be generated after the call to
     *  NC_NetStart(), similar to the following:
     *
     *      do
     *      {
     *           rc = NC_NetStart(hCfg, ti_ndk_config_Global_NetworkOpen, 
     *                   ti_ndk_config_Global_NetworkClose, 
     *                   ti_ndk_config_Global_NetworkIPAddr);
     *      } while( rc > 0 );
     *
     *      myDeleteFxn(hCfg, rc);
     *
     *  Therefore, if you wish to use the configuration handle in "myDeleteFxn",
     *  then you should define it so that it can accept the handle passed to it:
     *  
     *      Void myDeleteFxn(HANDLE hCfg, int rc)
     *      {  
     *          ...
     *      }  
     */
    config ndkHookFxn stackDeleteHook = null;

    /*!
     *  User defined hook function to run in the NDK status report callback
     *  funtion, ti_ndk_config_Global_serviceReport().  This function will run
     *  at the beginning of the service report function and will be passed the
     *  the same arguments passed to ti_ndk_config_Global_serviceReport(),
     *  Item, Status, Report and h.
     *
     *  For example, if your configuration sets 'serviceReportHook' to a function
     *  called "myReportFxn":
     *
     *      var Global = xdc.useModule('ti.ndk.config.Global');
     *      Global.serviceReportHook = '&myReportFxn';
     *
     *  Then a call to "myReportFxn" will be generated as follows:
     *
     *      myReportFxn(Item, Status, Report, h);
     *
     *  Therefore, if you wish to use the configuration handle in "myReportFxn",
     *  then you should define it so that it can accept the handle passed to it:
     *  
     *      Void myReportFxn(uint Item, uint Status, uint Report, HANDLE h)
     *      {  
     *          ...
     *      }  
     */
    config ndkHookFxn serviceReportHook = null;

    /*!
     *  User defined hook function to run inside the NDK Network Start callback
     *  function, NetworkOpen().  The Network Start callback function is called
     *  when the stack is ready to begin the creation of application supplied
     *  network tasks.  This hook function will run immediately, upon entering
     *  the NetworkOpen() function.  Note that this function is called during
     *  the early stages of the stack startup, and must return in order for the
     *  stack to resume operations.  It will not be passed any arguments.
     *
     *  For example, if your configuration sets 'networkOpenHook' to a function
     *  called "myNetOpenFxn":
     *
     *      var Global = xdc.useModule('ti.ndk.config.Global');
     *      Global.networkOpenHook = '&myNetOpenFxn';
     *
     *  Then a call to "myNetOpenFxn" will be generated as follows:
     *
     *      myNetOpenFxn();
     *
     */
    config ndkHookFxn networkOpenHook = null;

    /*!
     *  User defined hook function to run in the NDK Network Stop callback
     *  function, NetworkClose().  The Network Close callback function is
     *  called when the stack is about to shut down.  This hook function will
     *  run immediately, upon entering the NetworkClose() function. It will not
     *  be passed any arguments.
     *
     *  For example, if your configuration sets 'networkCloseHook' to a function
     *  called "myNetCloseFxn":
     *
     *      var Global = xdc.useModule('ti.ndk.config.Global');
     *      Global.networkCloseHook = '&myNetCloseFxn';
     *
     *  Then a call to "myNetCloseFxn" will be generated as follows:
     *
     *      myNetCloseFxn();
     *
     */
    config ndkHookFxn networkCloseHook = null;

    /*!
     *  User defined hook function to run in the NDK Network IP address
     *  callback function, NetworkIPAddr().  The Network IP address callback
     *  function is called when an IP address is added or removed from the
     *  system.  This hook function will run immediately, upon entering the
     *  NetworkIPAddr() function and is passed the same arguments passed to
     *  NetworkIPAddr(), IPAddr, IfIdx, fAdd.
     *
     *  For example, if your configuration sets 'networkIPAddrHook' to a
     *  function called "myIPAddrHook":
     *
     *      var Global = xdc.useModule('ti.ndk.config.Global');
     *      Global.networkIPAddrHook = '&myIPAddrHook';
     *
     *  Then a call to "myIPAddrHook" will be generated as follows:
     *
     *      myIPAddrHook(hCfg);
     *
     *  Therefore, if you wish to use the configuration handle in "myIPAddrHook",
     *  then you should define it so that it can accept the arguments passed to
     *  it:
     *  
     *      Void myIPAddrHook(IPN IPAddr, uint IfIdx, uint fAdd)
     *      {  
     *          ...
     *      }  
     */
    config ndkHookFxn networkIPAddrHook = null;

    /*!
     *  ======== addUserAccount ========
     *  addUserAccount is used in a config file to add a new user account into
     *  the set of user accounts (and corresponding passwords) that will be
     *  added into the NDK configuration.
     *
     *  A user account is created by making a struct Account, setting that
     *  structs username and password for the account to be added, and then
     *  calling this function to add it. For example:
     *  
     *  
     *       Account acct1;
     *       acct1.username = "user1";  
     *       acct1.password = "user1pass";  
     *  
     *       addUserAccount(acct1);
     *
     *  @param(account) structure of type Account
     */
    metaonly Void addUserAccount(Account account);
}

