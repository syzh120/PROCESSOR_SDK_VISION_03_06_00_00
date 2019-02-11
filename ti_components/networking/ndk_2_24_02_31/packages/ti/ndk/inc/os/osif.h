/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 * ======== osif.h ========
 *
 * OS Interface Functions
 *
 */

#ifndef _C_OSIF_H
#define _C_OSIF_H

/*--------------------------------------------- */
/*--------------------------------------------- */
/* OS Environment Globals */
/*--------------------------------------------- */
/*--------------------------------------------- */

/* Printf Buffer Size */
/* Change requires a recompile of the OS library */
#define OS_PRINTFBUFFER         512

/* Configuration Structure */
typedef struct _osenvcfg {
    uint     DbgPrintLevel;     /* Debug msg print threshhold */
    uint     DbgAbortLevel;     /* Debug msg sys abort theshhold */
    int      TaskPriLow;        /* Lowest priority for stack task */
    int      TaskPriNorm;       /* Normal priority for stack task */
    int      TaskPriHigh;       /* High priority for stack task */
    int      TaskPriKern;       /* Kernel-level priority (highest) */
    int      TaskStkLow;        /* Minimum stack size */
    int      TaskStkNorm;       /* Normal stack size */
    int      TaskStkHigh;       /* Stack size for high volume tasks */
    } OSENVCFG;

/* Configuration */
extern OSENVCFG _oscfg;

/* Equates used in code */
#define DBG_PRINT_LEVEL         (_oscfg.DbgPrintLevel)
#define DBG_ABORT_LEVEL         (_oscfg.DbgAbortLevel)
#define OS_TASKPRILOW           (_oscfg.TaskPriLow)
#define OS_TASKPRINORM          (_oscfg.TaskPriNorm)
#define OS_TASKPRIHIGH          (_oscfg.TaskPriHigh)
#define OS_TASKPRIKERN          (_oscfg.TaskPriKern)
#define OS_TASKSTKLOW           (_oscfg.TaskStkLow)
#define OS_TASKSTKNORM          (_oscfg.TaskStkNorm)
#define OS_TASKSTKHIGH          (_oscfg.TaskStkHigh)

/* Default values */
#define DEF_DBG_PRINT_LEVEL     DBG_INFO
#define DEF_DBG_ABORT_LEVEL     DBG_ERROR
#define OS_TASKPRILOW_DEF       3
#define OS_TASKPRINORM_DEF      5
#define OS_TASKPRIHIGH_DEF      7
#define OS_TASKPRIKERN_DEF      9   /* Leave room to run scheduler at 8 */
#define OS_TASKSTKLOW_DEF       3072
#define OS_TASKSTKNORM_DEF      4096
#define OS_TASKSTKHIGH_DEF      5120

#define OS_SCHEDULER_HIGHPRI    (_oscfg.TaskPriKern-1)
#define OS_SCHEDULER_LOWPRI     (_oscfg.TaskPriLow-1)

extern int stricmp(const char *s1, const char *s2);

/*----------------------------------------------------------------------- */
/*----[ PACKET BUFFER MANAGER ]------------------------------------------ */
/*----------------------------------------------------------------------- */

/* Packet Buffer Object */
typedef struct _PBM_Pkt {
    UINT32          Type;         /* Identifier (Read Only) */
    struct _PBM_Pkt *pPrev;       /* Previous record */
    struct _PBM_Pkt *pNext;       /* Next record */
    UINT8           *pDataBuffer; /* Pointer to Data Buffer (Read Only) */
    uint            BufferLen;    /* Physical Length of buffer (Read Only) */
    uint            Flags;        /* Packet Flags */
    uint            ValidLen;     /* Length of valid data in buffer */
    uint            DataOffset;   /* Byte offset to valid data */
    uint            EtherType;    /* Ether Type Code */
    uint            L2HdrLen;     /* Length of L2 Hdr (on 'L3' Rx pkts) */
    uint            IpHdrLen;     /* Length of Ip Hdr */
    HANDLE          hIFRx;        /* Rx Interface */
    HANDLE          hIFTx;        /* Tx Interface */
    HANDLE          hRoute;       /* Handle to Route */
    UINT16          PktPriority;  /* Priority of the packet. */
    UINT32          Aux1;         /* Aux1 Data */
    UINT32          Aux2;         /* Aux2 Data */
    TimestampFxn    pTimestampFxn;/* Callout function pointer to */
                                  /* timestamp TX */
    UINT8           *pIpHdr;      /* Pointer to IP Header  */

#ifdef _INCLUDE_IPv6_CODE    
    HANDLE          hRoute6;      /* Handle to Route6 object. */
    IP6N            SrcAddress;   /* IPv6 Source Address of the packet  */
    UINT32          SrcPort;      
#endif
    } PBM_Pkt;

/* PBM Handle */
typedef void * PBM_Handle;

/* Packet Buffer Manager Initialization Functions */
_extern uint        PBM_open();
_extern void        PBM_close();

/* Packet Buffer Functions (re-entrant and "kernel mode" agnostic) */
_extern PBM_Handle  PBM_alloc( uint MaxSize );
_extern PBM_Handle  PBM_copy( PBM_Handle hPkt );
_extern void        PBM_free( PBM_Handle hPkt );

/* The following field Functions can be used by device drivers */
/* All other PBM_Pkt fields are reserved */
#define PBM_getBufferLen(hPkt)      (((PBM_Pkt*)hPkt)->BufferLen)
#define PBM_getDataBuffer(hPkt)     (((PBM_Pkt*)hPkt)->pDataBuffer)
#define PBM_getValidLen(hPkt)       (((PBM_Pkt*)hPkt)->ValidLen)
#define PBM_getDataOffset(hPkt)     (((PBM_Pkt*)hPkt)->DataOffset)
#define PBM_getIFRx(hPkt)           (((PBM_Pkt*)hPkt)->hIFRx)

#define PBM_setValidLen(hPkt,x)     (((PBM_Pkt*)hPkt)->ValidLen=(x))
#define PBM_setDataOffset(hPkt,x)   (((PBM_Pkt*)hPkt)->DataOffset=(x))
#define PBM_setIFRx(hPkt,x)         (((PBM_Pkt*)hPkt)->hIFRx=(x))

/*----------------------------------------------------------------------- */
/*----[ PACKET BUFFER QUEUE ]-------------------------------------------- */
/*----------------------------------------------------------------------- */

/* Packet Buffer Queue Object */
typedef struct _PBMQ {
  uint              Count;      /* Number of packets in queue */
  PBM_Pkt           *pHead;     /* Pointer to first packet */
  PBM_Pkt           *pTail;     /* Pointer to last packet */
} PBMQ;

/* Packet Queue Functions (re-entrant and "kernel mode" agnostic) */
#define            PBMQ_init(pQ)   mmZeroInit( (pQ), sizeof(PBMQ) )
#define            PBMQ_count(pQ) ((pQ)->Count)
_extern void       PBMQ_enq( PBMQ *pQ, PBM_Handle hPkt );
_extern PBM_Handle PBMQ_deq( PBMQ *pQ );

/*----------------------------------------------------------------------- */
/*----[ STACK EVENT OBJECT ]--------------------------------------------- */
/*----------------------------------------------------------------------- */

#define STKEVENT_NUMEVENTS    5

#define STKEVENT_TIMER        0
#define STKEVENT_ETHERNET     1
#define STKEVENT_SERIAL       2
#define STKEVENT_LINKUP       3
#define STKEVENT_LINKDOWN     4

/* Stack Event Object */
typedef struct _stkevent {
    HANDLE      hSemEvent;
    uint        EventCodes[STKEVENT_NUMEVENTS];
} STKEVENT;


/* STKEVENT Handle */
typedef void * STKEVENT_Handle;


/* Packet Queue Functions (kernel mode agnostic */

/* void STKEVENT_signal( STKEVENT_Handle hEventRec, uint Event, uint Ext ); */
/*          hEventRec       Handle to Event Record */
/*          Event           Event Code to Signal */
/*          Ext             Set to 1 if triggered by an external event (isr) */
/*                          Set to 0 if detected by polling function */
#define STKEVENT_signal(h,event,ext) { \
                                ((STKEVENT *)(h))->EventCodes[(event)]=1; \
                                if( (ext) && ((STKEVENT *)(h))->hSemEvent ) \
                                SemPost( ((STKEVENT *)(h))->hSemEvent ); }

#define STKEVENT_init(h,hSem) { \
                                mmZeroInit( (h), sizeof(STKEVENT) ); \
                                ((STKEVENT *)(h))->hSemEvent = (hSem); }


/*--------------------------------------------- */
/*--------------------------------------------- */
/* TASK */
/*--------------------------------------------- */
/*--------------------------------------------- */

/* These functions may need to be hooked or ported */
_extern void   TaskBlock(HANDLE h);
_extern HANDLE TaskCreate( void(*pFun)(), char *Name,
                          int Priority, uint StackSize,
                          UINT32 Arg1, UINT32 Arg2, UINT32 Arg3 );
_extern void   TaskDestroy( HANDLE h );
_extern void   TaskExit();
_extern HANDLE TaskGetEnv( HANDLE h, int Slot );
_extern int    TaskGetPri(HANDLE h);
_extern HANDLE TaskSelf();
_extern void   TaskSetEnv( HANDLE h, int Slot, HANDLE hEnv );
_extern int    TaskSetPri(HANDLE h, int priority);
_extern void   TaskSleep(UINT32 delay);
_extern void   TaskYield();

/* Kernel Level Gateway Functions */
_extern void  llEnter();
_extern void  llExit();

/* signal that system resources are low */ 
_extern void NotifyLowResource(void);

/*--------------------------------------------- */
/*--------------------------------------------- */
/* SEM */
/*--------------------------------------------- */
/*--------------------------------------------- */
/*#define SEM_FOREVER SYS_FOREVER */
#define SEM_FOREVER     ~(0)

/* SEM fxn mappings */
_extern HANDLE SemCreate(int Count);
_extern HANDLE SemCreateBinary(int Count);
_extern void SemDelete(HANDLE hSem);
_extern int SemCount(HANDLE hSem); 
_extern int SemPend(HANDLE hSem, UINT32 Timeout);
_extern void SemPost(HANDLE hSem);
_extern void SemReset(HANDLE hSem, int Count); 

/*--------------------------------------------- */
/*--------------------------------------------- */
/* MEMORY */
/*--------------------------------------------- */
/*--------------------------------------------- */

_extern void   *mmAlloc( uint Size );
_extern void   mmFree( void* pv );
_extern void   mmCopy( void* pDst, void* pSrc, uint Size );
_extern void   mmZeroInit( void* pDst, uint Size );
_extern void   *mmBulkAlloc( INT32 Size );
_extern void   mmBulkFree( void *pMemory );

#ifdef _INCLUDE_JUMBOFRAME_SUPPORT
/*--------------------------------------------- */
/*--------------------------------------------- */
/* JUMBO MEMORY ( >3K ) */
/*--------------------------------------------- */
/*--------------------------------------------- */

_extern void   *jumbo_mmAlloc( uint Size );
_extern void   jumbo_mmFree( void* pv );
#endif

/*--------------------------------------------- */
/*--------------------------------------------- */
/* DEBUG */
/*--------------------------------------------- */
/*--------------------------------------------- */
/* Debug Log */
extern int   DebugCritError;                /* Set on critical error */

_extern void    DbgPrintf(uint Level, char *fmt, ... );
#define DBG_INFO        1
#define DBG_WARN        2
#define DBG_ERROR       3
#define DBG_NONE        4

/*--------------------------------------------- */
/*--------------------------------------------- */
/* Fast Crit Sections */
/*--------------------------------------------- */
/*--------------------------------------------- */
_extern uint OEMSysCritOn();
_extern void OEMSysCritOff( uint enable );

/*--------------------------------------------- */
/*--------------------------------------------- */
/* Cache */
/*--------------------------------------------- */
/*--------------------------------------------- */
_extern void OEMCacheClean( void *pAddr, uint Length );
_extern void OEMCacheCleanSynch();

/*--------------------------------------------- */
/*--------------------------------------------- */
/* PRINTF */
/*--------------------------------------------- */
/*--------------------------------------------- */

_extern int  NDK_sprintf(char *s, const char *format, ...);
_extern int  NDK_vsprintf(char *s, const char *format, va_list arg);

/*--------------------------------------------- */
/*--------------------------------------------- */
/* Embedded File System */
/*--------------------------------------------- */
/*--------------------------------------------- */

/* File system equates */
#define EFS_FILENAME_MAX    80

/* File type equates */
#define EFS_SEEK_SET        0
#define EFS_SEEK_CUR        1
#define EFS_SEEK_END        2
#define EFS_FILE            void

/* Executable function */
typedef void (*EFSFUN)();

/* Functions */
_extern void      efs_createfile( char *name, INT32 length, UINT8 *pData );
_extern void      efs_createfilecb( char *name, INT32 length, UINT8 *pData,
                                    EFSFUN pllDestroyFun, UINT32 MemMgrArg );

_extern void      efs_destroyfile( char *name );
_extern EFSFUN    efs_loadfunction( char *name );

_extern EFS_FILE *efs_fopen( char *name, char *mode );
_extern int       efs_fclose( EFS_FILE *stream );
_extern int       efs_feof( EFS_FILE *stream );
_extern size_t    efs_fread( void *ptr, size_t size, size_t nobj,
                            EFS_FILE *stream );
_extern size_t    efs_fwrite( void *ptr, size_t size, size_t nobj,
                             EFS_FILE *stream );
_extern INT32     efs_fseek( EFS_FILE *stream, INT32 offset, int origin );
_extern INT32     efs_ftell( EFS_FILE *stream );
_extern void      efs_rewind( EFS_FILE *stream );
_extern INT32     efs_getfilesize( EFS_FILE *f );

_extern size_t    efs_filesend( EFS_FILE *stream, size_t size, SOCKET s );

_extern int  efs_filecheck(char *name, char *user, char *pass, int *prealm);

/* Possible return flags for efs_filecheck() */
#define EFS_FC_NOTFOUND         0x01        /* File not found */
#define EFS_FC_NOTALLOWED       0x02        /* File can not be accessed */
#define EFS_FC_EXECUTE          0x04        /* Filename is a function call (CGI) */
#define EFS_FC_AUTHFAILED       0x08        /* File autentication failed */
                                            /* (realm index suppied in realm) */

/*--------------------------------------------- */
/*--------------------------------------------- */
/* Interrupt Management Wrapper APIs and  */
/* Data structure. */
/*--------------------------------------------- */
/*--------------------------------------------- */

/* This is the maximum number of system events defined by
 * C64x+ DSP. Can be customized according to the platform
 * limitations.
 */
#define     MAX_NUM_SYSEVENTS   128

/** 
 * @brief 
 *  The structure describes the interrupt setup object defined by
 *  the interrupt management wrapper in OS Abstraction Layer.
 *
 * @details
 *  This structure can be used by a driver/such in setting up 
 *  interrupts using the underlying OS (BIOS) constructs without
 *  having to know the details of the OS specific calls. All calls
 *  to the interrupt management wrapper require a handle to
 *  the structure described below.
 */
typedef struct _IntSetup
{
    /**
     * @brief   HWI Object number to use for setting up this 
     *          system event. The valid values for this range
     *          between 4 - 15 (both inclusive).
     */
    UINT8       intVectId;                      

    /**
     * @brief   System Event number(s) for which the 
     *          interrupts need to be setup. The valid values
     *          for this range between 4 - 127 (both inclusive).
     */
    UINT8       sysEvtId[MAX_NUM_SYSEVENTS];   

    /**
     * @brief   Number of system events that need to be mapped 
     *          to a given DSP interrupt number and be serviced by
     *          a specified Interrupt Service Routine (ISR).
     *          Valid values for this range between 1 - 128.
     */
    UINT8       sysEvtCount;

    /**
     * @brief   The callback function to be triggered when the 
     *          interrupt occurs, i.e. the ISR. This should not be
     *          set to NULL for a successful interrupt setup.
     */
    void        (*pCallbackFxn)(void* pCallbackArg);

    /**
     * @brief   The arguments that need to be passed to the ISR.
     *          Can be NULL.
     */
    void*       pCallbackArg;

    /**
     * @brief   Flag to indicate whether to enable/disable the
     *          interrupt by default. This flag is valid only
     *          when setting up combined interrupts, i.e., 
     *          multiple system events mapped to a single
     *          DSP interrupt number.
     *          
     */    
    UINT8       bEnable;

} IntSetup;

UINT32  Interrupt_add(IntSetup* myIntSetup);
UINT32  Interrupt_delete(IntSetup* myIntSetup);
UINT32  Interrupt_enable(IntSetup* myIntSetup);
UINT32  Interrupt_disable(IntSetup* myIntSetup);

#endif
