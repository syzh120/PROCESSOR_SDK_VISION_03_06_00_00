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
 * ======== netctrl.c ========
 *
 *
 * Shell functions for simplified net startup and shutdown
 *
 * The idea behind this API is to hide the user callable HAL/STACK functions
 *
 */

#include <netmain.h>
#include <_stack.h>
#include <_oskern.h>

/* Static Event Object */
STKEVENT  stkEvent;

/* Network Halt Flag and Return Code */
static int  NetHaltFlag;
static int  NetReturnCode;

/* System Info */
static int  SystemOpen = 0;
static int  SchedulerPriority = 0;

/* Stack Event Scheduler */
static void NetScheduler( uint const SerialCnt, uint const EtherCnt );

/* User's Network start and stop functions */
static uint flagSysTasks     = 0;       /* Set if we've called user functions */
static void (*NetStartFun)() = 0;       /* User start function ptr */
static void (*NetStopFun)()  = 0;       /* User stop function ptr */
static void (*NetIPFun)(IPN,uint,uint) = 0;  /* User IP addr function ptr */

static void (*NetLinkHook)(int) = 0; /* Called when link status event received */

/*
 * NC_SystemOpen()
 * Initialize the OS to run NET applications
 */
int NC_SystemOpen( int Priority, int OpMode )
{
    HANDLE  hSem = 0;

    /* Open the low-level enironment */

    /* Set the network scheduler priority */
    if( Priority != NC_PRIORITY_LOW &&  Priority != NC_PRIORITY_HIGH )
        return(NC_OPEN_ILLEGAL_PRIORITY);
    SchedulerPriority = Priority;

    /* Check the operating mode */
    if( OpMode != NC_OPMODE_POLLING && OpMode != NC_OPMODE_INTERRUPT )
        return(NC_OPEN_ILLEGAL_OPMODE);

    /* Polling at high priority is illegal */
    if( Priority==NC_PRIORITY_HIGH && OpMode==NC_OPMODE_POLLING )
        return(NC_OPEN_ILLEGAL_OPMODE);

    /* Intialize the task environment */
    _TaskInit();

    /* Initialize memory */
    if( !_mmInit() )
        return(NC_OPEN_MEMINIT_FAILED);

#ifdef  _INCLUDE_JUMBOFRAME_SUPPORT
    /* Initialize jumbo frame memory manager */
    if( !_jumbo_mmInit() )
        return(NC_OPEN_MEMINIT_FAILED);    
#endif

    /* Create the event semaphore */
    if( OpMode==NC_OPMODE_INTERRUPT && !(hSem = SemCreateBinary(0)) )
        return(NC_OPEN_EVENTINIT_FAILED);

    /* Initialize our Event object */
    STKEVENT_init( &stkEvent, hSem );

    /* Open the packet buffer manager */
    PBM_open();

    /* Initialize our part of the configuration system */
    NS_PreBoot();

    SystemOpen = 1;

    return(NC_OPEN_SUCCESS);
}

/*
 * NC_SystemClose()
 * Complete closing down the NET environment
 */
void NC_SystemClose()
{
    SystemOpen = 0;

    /* Delete the event semaphore */
    if( stkEvent.hSemEvent )
    {
        SemDelete( stkEvent.hSemEvent );
        stkEvent.hSemEvent = 0;
    }

    /* Close the packet buffer manager */
    PBM_close();

    /* Close the task environment */
    _TaskShutdown();
}

/* 
 * NC_NetStart()
 * Initialize stack environment
 */
int NC_NetStart( HANDLE hCfg, void (*NetStart)(),
                 void (*NetStop)(), void (*NetIP)(IPN,uint,uint) )
{
    uint   EtherDeviceCount = 0;
    uint   SerialDeviceCount = 0;

    /* Make sure we're ready to run */
    if( !SystemOpen )
        return(0);

    /* Initialize our state to be "not halted" */
    NetHaltFlag = 0;

    /* Initialize the timer */
    /* If we wanted, we could initialize the timer value with the */
    /* seconds elapsed from some standard time (1-1-70, 1-1-80, etc.). */
    _llTimerInit( &stkEvent, 0 );

    /* Initialize the User LED driver */
    _llUserLedInit();

    /* Initialize the serial port */
    SerialDeviceCount = _llSerialInit( &stkEvent );
    if( SerialDeviceCount > 1 )
        SerialDeviceCount = 1;

    /* Initialize the Network Interface Management Unit */
    NIMUInit (&stkEvent);

    /* Initialize the VLAN Module. */
    VLANInit();

#ifdef _INCLUDE_IPv6_CODE
    /* Initialize the IPv6 Stack. */
    IPv6Init ();
#endif

    /* Set the deault config handle */
    CfgSetDefault( hCfg );

    /* Record the function pointers */
    NetStartFun = NetStart;
    NetStopFun  = NetStop;
    NetIPFun    = NetIP;

    /* Initialize the stack executive */
    ExecOpen();

    /* Boot the configuration */
    TaskCreate( NS_BootTask, "ConfigBoot", OS_TASKPRINORM, 2048,
               (UINT32)hCfg, 0, 0 );

    /* Start running the stack */
    NetScheduler(SerialDeviceCount,EtherDeviceCount);

    /*
     *  Fix for SDOCM00115318 - must tear down serial/PPP config before
     *  disabling it! Otherwise config tear down code in PPP deinit fails
     */
    _llSerialShutdown();

    /* Disable the configuration */
    CfgExecute( hCfg, 0 );

    /* Call the Net stop function */
    if( !flagSysTasks ) {
        DbgPrintf(DBG_INFO,
                "\n\nNC_NetStart: WARNING: Boot thread has not completed!\n\n");
    }
    else
    {
        flagSysTasks = 0;
        if( NetStopFun )
            (*NetStopFun)();
    }

    /* In order for the system to settle out properly, we must */
    /* be "OS_SCHEDULER_LOWPRI" at this point. */
    TaskSetPri( TaskSelf(), OS_SCHEDULER_LOWPRI );

    /* Shutdown the stack */
    ExecClose();

    /* Clear function callbacks */
    NetStartFun = 0;
    NetStopFun  = 0;
    NetIPFun    = 0;

    /* Clear the default config handle */
    CfgSetDefault( 0 );

    /* Close the VLAN Module. */
    VLANDeinit();

    /* Shutdown the low-level environment */
    NIMUShutdown();

    _llUserLedShutdown();
    _llTimerShutdown();

    return( NetReturnCode );
}

/*
 * NC_NetStop()
 * Initiate system shutdown
 */
void NC_NetStop( int rc )
{
    NetReturnCode = rc;
    NetHaltFlag   = 1;
}

/*
 * NC_BootComplete()
 * Boot thread has completed
 */
void NC_BootComplete()
{
    if( !flagSysTasks )
    {
        flagSysTasks = 1;
        if( NetStartFun )
            (*NetStartFun)();
    }
}

/*
 * NC_IPUpdate( IPN IPAddr, uint fAdd )
 * Boot thread has completed
 */
void NC_IPUpdate( IPN IPAddr, uint IfIdx, uint fAdd )
{
    if( NetIPFun )
        (*NetIPFun)( IPAddr, IfIdx, fAdd );
}

/*
 * NC_setLinkHook()
 * Used to register a hook function that's called when link status changes.
 * The user defined hook function should have an int status parameter. Once
 * a link status even is received in the net scheduler, the hook will be
 * called, passing one of the following status values as its argument,
 * depending on the event type (link up or down):
 * 
 *     0: link is down (e.g. cable disconnected) 
 *     1: link is up   (e.g. cable connected)
 */
void NC_setLinkHook( void (*LinkHook)(int) )
{
    NetLinkHook = LinkHook;
}

/*
 *  NetScheduler()
 *  Check for stack related events for Timer, Ethernet, Serial and link status
 *  Returns: Stack exit code
 */
#define FLAG_EVENT_TIMER     1
#define FLAG_EVENT_ETHERNET  2
#define FLAG_EVENT_SERIAL    4
#define FLAG_EVENT_LINKUP    8
#define FLAG_EVENT_LINKDOWN  16

/* ARGSUSED */
static void NetScheduler( uint const SerialCnt, uint const EtherCnt )
{
    register int fEvents;

    /* Set the scheduler priority */
    TaskSetPri( TaskSelf(), SchedulerPriority );

    /* Enter scheduling loop */
    while( !NetHaltFlag )
    {
        if( stkEvent.hSemEvent )
        {
            SemPend( stkEvent.hSemEvent, SEM_FOREVER );
        }

        /* Clear our event flags */
        fEvents = 0;

        /* First we do driver polling. This is done from outside */
        /* kernel mode since pure "polling" drivers can not spend */
        /* 100% of their time in kernel mode. */

        /*
         * Check for a timer event and flag it. EventCodes[STKEVENT_TIMER]
         * is set as a result of llTimerTick() (NDK heartbeat)
         */
        if( stkEvent.EventCodes[STKEVENT_TIMER] )
        {
            stkEvent.EventCodes[STKEVENT_TIMER] = 0;
            fEvents |= FLAG_EVENT_TIMER;
        }

        /* Poll only once every timer event for ISR based drivers, */
        /* and continuously for polling drivers. Note that "fEvents" */
        /* can only be set to FLAG_EVENT_TIMER at this point. */
        if( fEvents || !stkEvent.hSemEvent )
        {
            NIMUPacketServiceCheck (fEvents);

            /* Poll Serial Port Devices */
            if( SerialCnt )
                _llSerialServiceCheck( fEvents );
        }

        /* Note we check for Ethernet and Serial events after */
        /* polling since the ServiceCheck() functions may */
        /* have passively set them. */

        /* Was an Ethernet event signaled? */
        if(stkEvent.EventCodes[STKEVENT_ETHERNET])
        {
            /* We call service check on an event to allow the */
            /* driver to do any processing outside of kernel */
            /* mode that it requires, but don't call it if we */
            /* already called it due to a timer event or by polling */
            if (!(fEvents & FLAG_EVENT_TIMER) && stkEvent.hSemEvent)
                NIMUPacketServiceCheck (0);

            /* Clear the event and record it in our flags */
            stkEvent.EventCodes[STKEVENT_ETHERNET] = 0;
            fEvents |= FLAG_EVENT_ETHERNET;
        }
        
        /* Check for a Serial event and flag it */
        if(SerialCnt && stkEvent.EventCodes[STKEVENT_SERIAL] )
        {
            /* We call service check on an event to allow the */
            /* driver to do any processing outside of kernel */
            /* mode that it requires, but don't call it if we */
            /* already called it due to a timer event or by polling */
            if( !(fEvents & FLAG_EVENT_TIMER) && stkEvent.hSemEvent )
                _llSerialServiceCheck( 0 );

            /* Clear the event and record it in our flags */
            stkEvent.EventCodes[STKEVENT_SERIAL] = 0;
            fEvents |= FLAG_EVENT_SERIAL;
        }

        /* Check if link went up */
        if(stkEvent.EventCodes[STKEVENT_LINKUP])
        {
            /* Clear the event and record it in our flags */
            stkEvent.EventCodes[STKEVENT_LINKUP] = 0;
            fEvents |= FLAG_EVENT_LINKUP;
        }
       
        /* Check if link went down */
        if(stkEvent.EventCodes[STKEVENT_LINKDOWN])
        {
            /* Clear the event and record it in our flags */
            stkEvent.EventCodes[STKEVENT_LINKDOWN] = 0;
            fEvents |= FLAG_EVENT_LINKDOWN;
        }

        /* Process current events in Kernel Mode */
        if( fEvents )
        {
            /* Enter Kernel Mode */
            llEnter();

            /*
             * Check for timer event. Timer event flag is set as a result of
             * llTimerTick() (NDK heartbeat)
             */
            if( fEvents & FLAG_EVENT_TIMER )
                ExecTimer();

            /* Check for packet event */
            if( fEvents & FLAG_EVENT_ETHERNET )
                NIMUPacketService();

            /* Check for serial port event */
            if( fEvents & FLAG_EVENT_SERIAL )
                llSerialService();

            /* Exit Kernel Mode */
            llExit();

            /*
             * Check for a change in link status.  Do this outside of above
             * llEnter/llExit pair as to avoid illegal reentrant calls to
             * kernel mode by user's callback.
             */
            /* Check for link up status */
            if( fEvents & FLAG_EVENT_LINKUP )
            {
                /* call the link status callback, if user registered one */
                if (NetLinkHook) {
                    /* pass callback function a link status of "up" */
                    (*NetLinkHook)(1);
                }
            }

            /* Check for link down status */
            if( fEvents & FLAG_EVENT_LINKDOWN )
            {
                /* call the link status callback, if user registered one */
                if (NetLinkHook) {
                    /* pass callback function a link status of "down" */
                    (*NetLinkHook)(0);
                }
            }
        }
    }
}
