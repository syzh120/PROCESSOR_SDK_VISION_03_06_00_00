/*
********************************************************************************
* HDVICP2.0 Based JPEG Encoder
*
* "HDVICP2.0 Based JPEG Encoder" is software module developed for
* TI's HDVICP2 based SoCs. This module is capable of encoding a raw image
* by compressing it into a JPEG bitstream compliant with ISO/IEC IS 10918-1.
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
********************************************************************************
*/
/**
********************************************************************************
* @file      jpegenc_ti_rman_config.c
*
* @brief     IRES RMAN related functions
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
*
* @version 0.1 (Feb 2010) : Review & Clean up [vasudev]
*
* @version 0.2 (July 2010): DataSync feature added [pavan]
*
* @version 0.3 (Aug 2010) : Debug Trace Feature Added[Vasudev]
*
* @version 0.4 (Sep 2010) : Modified to support M3 part changes to align with
*                           MPEG4 Decoder[Vasudev]
*
* @version 0.5 (Dec 2010) : Changes related to HDVICP_Reset() and 
*                           ivahd_standby_power_on_uboot() [Naidu]
*
* @version 0.5 (Dec 2010) : Added RMAN_FreeResources function [Naidu]
*              
********************************************************************************
*/
/* -------------------- compilation control switches -------------------------*/


/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <xdc/std.h>
#include <hdvicp20_ti_datatypedefs.h>
#include <stdlib.h>
#include <stdio.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/ires.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/sdo/fc/utils/api/_alg.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>
#include <ti/sdo/fc/ires/tiledmemory/ires_tiledmemory.h>

/*--------------------- program files ----------------------------------------*/
#include "jpegenc_ti_api.h"
#include "jpegenc_ti_rman_config.h"

/**
*  SL2 Base Address, Register's Base Address & PRCM Base Address Set 
*  Based on Host Type Used   
*/

/*----------------------------------------------------------------------------*/
/*  These Macros for NetraEmulator  ResetFunction                             */
/*----------------------------------------------------------------------------*/
#if ( (HOSTCORTEXM3_NETRA) && (!HOSTCORTEXM3_NETRASIMULATOR) )
#define WR_MEM_32(addr, data)      \
 *(volatile unsigned int*)(addr)= (unsigned int)(data);
                                               
#define RD_MEM_32(addr)          *(volatile unsigned int*)(addr) ;
#endif

#if (HOSTCORTEXM3_OMAP4) || (HOSTCORTEXM3_OMAP4SIMULATOR)
#define IVAHD_HOST_REG_BASE    0x5A000000
#define IVAHD_HOST_SL2_BASE    0x5B000000
#define IVAHD_PRCM_BASE        0x4A306F10
#elif (HOSTCORTEXM3_NETRA) || (HOSTCORTEXM3_NETRASIMULATOR)
#define IVAHD_HOST_REG_BASE    0x58000000
#define IVAHD_HOST_SL2_BASE    0x59000000
#define IVAHD_PRCM_BASE        0x48180C10
#else
#define IVAHD_HOST_REG_BASE    0x50080000
#define IVAHD_HOST_SL2_BASE    0x00800000
#define IVAHD_PRCM_BASE        0x00000000
#endif
#define NUM_TILEDMEM_OBJECTS 1

/*----------------------------------------------------------------------------*/
/*  These Macros for OMAP4Emulator  ResetFunction                             */
/*----------------------------------------------------------------------------*/
#if ( (HOSTCORTEXM3_OMAP4) && (!HOSTCORTEXM3_OMAP4SIMULATOR) )

#define RM_IVAHD_RSTCTRL (0xAA306F10)
#define RM_IVAHD_RST_STATUS_ADDR (0xAA306F14)
#define CM_IVAHD_CLKSTCTRL (0xAA008F00)
#define CM_IVAHD_CLKCTRL (0xAA008F20)
#define CM_SL2_CLKCTRL (0xAA008F28)

#endif
/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/
/*----------------------------------------------------------------------------*/
/*  Global flag for non-blocking call.                                        */
/*----------------------------------------------------------------------------*/
extern volatile XDAS_Int32 unServMesgCount;
extern volatile XDAS_Int32 ServMesgCount;
extern XDAS_UInt32 configCount;
static Uint32 initialFrame = 0;
static Uint32 prevConfig = 0;

/*---------------------------------------------------------------------------*/
/*  Global Flag which will be intially be zero.                              */
/*  If acquire is made once, then this flag will be set and stay set.        */
/*---------------------------------------------------------------------------*/
Uint32 isAcquireCallMade;

/*----------------------------------------------------------------------------*/
/*  Global Algorithm handle which will be initialized with the argument to    */
/*  the algorithm's MB processing function.The following array is being       */
/*  declared to use the host with multiple IVAHD resources                    */
/*----------------------------------------------------------------------------*/
IALG_Handle gHandle[NUM_IVAHD_RESOURCES];

/*----------------------------------------------------------------------------*/
/*  Global Arguments which will be initialized with the argument to           */
/*  the algorithm's MB processing function.The following array is being       */
/*  declared to use the host with multiple IVAHD resources                    */
/*----------------------------------------------------------------------------*/
Uint32 gCbArgs[NUM_IVAHD_RESOURCES];

/*----------------------------------------------------------------------------*/
/*  Global function pointer which will be initialized to the algorithm's MB   */
/*  processing function and will be called by the gem interrupt handler       */
/*  function.The following array is being                                     */
/*  declared to use the host with multiple IVAHD resources                    */
/*----------------------------------------------------------------------------*/
void (* gFnPtr[NUM_IVAHD_RESOURCES])(IALG_Handle handle, void *cbArgs);
IRES_TILEDMEMORY_Obj    iresTiledMemoryObjects[NUM_TILEDMEM_OBJECTS];

typedef void (*ISR_VECTOR_TABLE)();
extern ISR_VECTOR_TABLE vectorTable[];

XDAS_Int32 IVAHD_Standby_power_on_uboot(UInt32 IVAHD_CONFIG_REG_BASE , 
                                        UInt32 PRCM_IVAHD_ICONT_RST_CNTL_ADDR
                                      );

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/

/**
*******************************************************************************
*  @fn     ISR_Function
*
*  @brief  This function is a call back function tied to IVA-HD
*  @return none
*
*******************************************************************************
*/
void ISR_Function()
{
  /*--------------------------------------------------------------------------*/
  /* Only one IVAHD resource is currently being used,This function needs to   */
  /* be modified for multiple resources                                       */
  /* Call-Back function tied to IVA-HD - 0.                                   */
  /* As with Ducati a single IVA-HD resource is tied                          */
  /* this id shall be zero.                                                   */
  /*--------------------------------------------------------------------------*/
  (*gFnPtr[0])(gHandle[0], (void *)gCbArgs[0]);
}

/** 
*******************************************************************************
*  @fn     HDVICP_reacquireIfOwner(
*                                  IALG_Handle handle, 
*                                  struct IRES_HDVICP2_Obj * iresHandle
*                                  )
*
*  @brief  This function re-acquires the resources
*          
*  @param[in] handle                        : Alg handle 
*
*  @param[out] iresHandle                   : Ires handle
*           
*  @return 1 - if acquire call is done before calling re-acquire 
*          0 - if acquire call is not done
*******************************************************************************
*/
XDAS_UInt32 HDVICP_reacquireIfOwner(IALG_Handle handle, 
struct IRES_HDVICP2_Obj * iresHandle)
{
  Uint32  regBaseAddr, memBaseAddr, prcmBaseAddr;

  /*--------------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                      */
  /*--------------------------------------------------------------------------*/
  if(NULL == handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                         */
  /*--------------------------------------------------------------------------*/
  if(NULL == iresHandle)
  {
    fprintf(stdout,"HDVICP handle not valid..\n");  
  }

  /*-------------------------------------------------------------------------*/
  /* Address space notification                                              */
  /* Notification of SL2 memory and configuration as seen by the Host ARM.   */
  /* Host ARM can be M3 or 968 or whatever. Suitable address is picked by    */
  /* macros defined in cslr_ivahd.h                                          */
  /*-------------------------------------------------------------------------*/  
  regBaseAddr = (Uint32)IVAHD_HOST_REG_BASE; 
  memBaseAddr = (Uint32)IVAHD_HOST_SL2_BASE;     

  /*-------------------------------------------------------------------------*/
  /* IVAHD_PRCM Base address as understood by Cortex-M3                      */
  /*-------------------------------------------------------------------------*/
  prcmBaseAddr = (Uint32)IVAHD_PRCM_BASE;/* Length: 0x0 bytes */

  iresHandle->registerBaseAddress = (void *)regBaseAddr;
  iresHandle->memoryBaseAddress = (void *)memBaseAddr;
  iresHandle->resetControlAddress = (void *)prcmBaseAddr;

  if(isAcquireCallMade)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/**
********************************************************************************
*  @fn     HDVICP_Acquire( IALG_Handle          handle,
*                          IRES_HDVICP2_Handle iresHandle,
*                          IRES_YieldContext   *yieldCtxt,
*                          XDAS_UInt32         *hdvicp2Status,
*                          UInt                * modeId,
*                          Int                 lateAcquireArg)
*
*  @brief  This function acquires the resources required by the process call
*          It Populates the hdvicp2Status to indicate the
*          status of the particular HDVICP2 unit that is returned.
*          The modeId  argument is both an input and output paramter which
*          specifies the  mode in which this particular HDVICP2 was used
*          last time, and the mode in which it will be used this time.
*          This API takes a yieldContext as argument, as it may yield the
*          processor to higher priority codecs in the system.
*
*  @param[in]  handle         : Pointer to the IALG_Handle structure
*
*  @param[in]  iresHandle     : Pointer to the IRES_HDVICP2_Handle structure
*
*  @param[in]  yieldCtxt      : Pointer to the IRES_YieldContext structure
*
*  @param[in]  hdvicp2Status  : Pointer to the IRES_HDVICP2_Status structure
*
*  @param[in,out] modeId      : The mode in which this particular HDVICP2 was
*                               used last time, and the mode in which it will
*                               be used this time
*  @param[in] lateAcquireArg  : This is the channel id which codec returns
*                               while acquiring the HDVICP2
*  @return     None
*
*  @return none
********************************************************************************
*/
void HDVICP_Acquire(IALG_Handle handle,IRES_HDVICP2_Handle iresHandle,
IRES_YieldContext *yieldCtxt,XDAS_UInt32       * hdvicp2Status,UInt * modeId,
Int lateAcquireArg)
{
  Int32   ID = 0;
  Uint32  regBaseAddr, memBaseAddr, prcmBaseAddr;

  if( (NULL == handle)  || (iresHandle == NULL))
  return;

  /*--------------------------------------------------------------------------*/
  /* After the resource allocation the new resource ID is communicated        */
  /*--------------------------------------------------------------------------*/
  iresHandle->id = ID;

  /*--------------------------------------------------------------------------*/
  /* Address space notification                                               */
  /* Notification of SL2 memory and configuration as seen by                  */
  /* the Host ARM. Host ARM can be M3 or 968 or whatever. Suitable            */
  /* address is picked by macros defined in cslr_ivahd.h                      */
  /*--------------------------------------------------------------------------*/

  /*--------------------------------------------------------------------------*/
  /* IVAHD_CONFIG Base address as understood by Cortex-M3                     */
  /*--------------------------------------------------------------------------*/
  regBaseAddr = (Uint32)IVAHD_HOST_REG_BASE;

  /*--------------------------------------------------------------------------*/
  /* IVAHD_SL2 Base address as understood by Cortex-M3                        */
  /*--------------------------------------------------------------------------*/
  memBaseAddr = (Uint32)IVAHD_HOST_SL2_BASE;

  /*--------------------------------------------------------------------------*/
  /* IVAHD_PRCM Base address as understood by Cortex-M3                       */
  /*--------------------------------------------------------------------------*/
  prcmBaseAddr = (Uint32)IVAHD_PRCM_BASE; /* Length: 0x0 bytes */

  iresHandle->registerBaseAddress = (void *)regBaseAddr;
  iresHandle->memoryBaseAddress   = (void *)memBaseAddr;
  iresHandle->resetControlAddress = (void *)prcmBaseAddr;

  /*--------------------------------------------------------------------------*/
  /* Reset indicates that the codec-process call need not reload the code     */
  /* Set indicates that the codec-process call needs to reload the code       */
  /*--------------------------------------------------------------------------*/
  if(initialFrame == 0 || (prevConfig != configCount))
  {
    *hdvicp2Status = DIFFERENTCODEC;
    prevConfig = configCount;
  }
  else
  {
    *hdvicp2Status = SAMECODECTYPE;
  }

#if defined (_ENABLE_BOOTING_)
  if(initialFrame == 0)
  {
    IVAHD_Standby_power_on_uboot(IVAHD_CONFIG_REG_BASE_IVAHD0, 
                                       PRCM_IVAHD_ICONT_RST_CNTL_ADDR_IVAHD0);
  }
#endif
  
  initialFrame++;

  /*-------------------------------------------------------------------------*/
  /* Set that acquire call already made                                      */
  /*-------------------------------------------------------------------------*/
  isAcquireCallMade = 0;   
}

/**
********************************************************************************
*  @fn     HDVICP_Configure(
*                         IALG_Handle handle, IRES_HDVICP2_Handle iresHandle,
*                           void (*IRES_HDVICP2_CallbackFxn)(IALG_Handle handle,
*                            void *cbArgs),void *cbArgs)
*
*  @brief  This function configures global variables
*
*  @param[in]  handle                       : Alg handle
*
*  @param[out] iresHandle                   : Ires handle
*
*  @param[out] IRES_HDVICP2_CallbackFxn     : Global function pointer to the
*                                             MB processing function
*  @param[out] cbArgs                       : Arguments to the MB processing
*                                             function
*
*  @return none
********************************************************************************
*/
void HDVICP_Configure(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle,
void (*IRES_HDVICP2_CallbackFxn)(IALG_Handle handle,void *cbArgs),void *cbArgs)
{
  Int32 ivahdID = iresHandle->id;

  /*--------------------------------------------------------------------------*/
  /*  Initialize the globalIVAHD flag upon which the HDVICP_Wait              */
  /*  shall poll.                                                             */
  /*--------------------------------------------------------------------------*/
  unServMesgCount = 0;
  ServMesgCount = -1;

  /*--------------------------------------------------------------------------*/
  /*  Initialize the Handle to the MB processing function that is             */
  /*  required to be called by the ISR.                                       */
  /*--------------------------------------------------------------------------*/
  gHandle[ivahdID] = handle;

  /*--------------------------------------------------------------------------*/
  /*  Initialize the global function ptr to the MB processing function        */
  /*  which will be called from the ISR.                                      */
  /*--------------------------------------------------------------------------*/
  gFnPtr[ivahdID]  = IRES_HDVICP2_CallbackFxn;

  /*--------------------------------------------------------------------------*/
  /*  Initialize the Argument to the MB processing function that is           */
  /*  required to be called by the ISR.                                       */
  /*--------------------------------------------------------------------------*/
  gCbArgs[ivahdID] = (Uint32)cbArgs;

  /*--------------------------------------------------------------------------*/
  /* Enable the interrupt for Host M3                                         */
  /*--------------------------------------------------------------------------*/
  *((int *) 0xE000E100)  = 0x00400000;

  /*--------------------------------------------------------------------------*/
  /* Registering the Interrupt.                                               */
  /*--------------------------------------------------------------------------*/
  vectorTable[38] = ISR_Function; /*ISR Address*/
}

/**
********************************************************************************
*  @fn     HDVICP_Release(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
*
*  @brief  Release.
*          Not implemented in the current version.
*
*  @param[in]  handle        : Handle to the Algorithm
*
*  @param[in]  iresHandle    : Handle to IRES
*
*  @return     none
********************************************************************************
*/
void HDVICP_Release(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
{
  JPEGVENC_TI_IRES.deactivateResource((IALG_Handle)handle,
                                          (IRES_Handle) iresHandle);
}

/**
********************************************************************************
*  @fn     HDVICP_Wait(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle,
*                        IRES_YieldContext * yieldCtxt)
*
*  @brief  Wait for the Completion of MB level tasks
*
*  @param[in]  handle        : Handle to the Algorithm
*
*  @param[in]  iresHandle    : Handle to IRES
*
*  @param[in]  yieldCtxt     : Pointer to Context switch structure
*
*  @return     none
********************************************************************************
*/
XDAS_UInt32 HDVICP_Wait(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle,
IRES_YieldContext * yieldCtxt)
{
  ServMesgCount++;
  while(1)
  {
    if(unServMesgCount > ServMesgCount)
    break;
  }
  return 1;
}

/** 
*******************************************************************************
*  @fn     HDVICP_Reset(
*                       IALG_Handle algHandle, 
*                       struct IRES_HDVICP2_Obj * iresHandle)
*
*  @brief  Function to reset HDVICP resouce before using it
*          This function will be called by algorithm when needed
*
*  @param[in] algHandle  : Pointer to algorithm handle
*  
*  @param[in] iresHandle : Pointer to the HDVICP resource handle
*
*  @return     0: Success, non-zero : Failure 
*
*******************************************************************************
*/
XDAS_UInt32 HDVICP_Reset(IALG_Handle algHandle, 
struct IRES_HDVICP2_Obj * iresHandle)
{   
#if ( (HOSTCORTEXM3_NETRA) && (!HOSTCORTEXM3_NETRASIMULATOR) )

   unsigned int RM_IVAHD0_RSTCTRL =  
       (unsigned int)iresHandle->resetControlAddress; /*(PRM_IVAHD0 + 0x10) */
   unsigned int RM_IVAHD0_RSTST =  
       (RM_IVAHD0_RSTCTRL + 4); /* (PRM_IVAHD0 + 0x14) */
   unsigned int CM_IVAHD0_IVAHD_CLKCTRL = 
       ((RM_IVAHD0_RSTCTRL - 0x610 ) + 0x20); /* (PRCM_BASE_ADDR + 0x0620) */
   unsigned int CM_IVAHD0_SL2_CLKCTRL =  
       (CM_IVAHD0_IVAHD_CLKCTRL + 4); /* (PRCM_BASE_ADDR + 0x0624) */

    volatile unsigned int temp;
    /* CM_IVAHD0_IVAHD_CLKCTRL. MODULEMODE = 0x0;
    while(CM_IVAHD0_IVAHD_CLKCTRL.IDLEST != 0x3); */
    WR_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL , 0);
    do{
    temp = RD_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL);
    temp = ((temp >> 16) & 3);
    }while(temp != 3);

    /* CM_IVAHD0_SL2_CLKCTRL. MODULEMODE = 0x0;
    while(CM_IVAHD0_SL2_CLKCTRL.IDLEST != 0x3); */
    WR_MEM_32(CM_IVAHD0_SL2_CLKCTRL , 0);
    do{
    temp = RD_MEM_32(CM_IVAHD0_SL2_CLKCTRL);
    temp = ((temp >> 16) & 3);
    }while(temp != 3);
    /* RM_IVAHD0_RSTST     = IVA_RST3 | IVA_RST2 | IVA_RST1; : 0x7 :
    RM_IVAHD0_RSTCTRL = IVA_RST3 | IVA_RST2 | IVA_RST1; : 0x7 */
    WR_MEM_32(RM_IVAHD0_RSTST , 7);
    WR_MEM_32(RM_IVAHD0_RSTCTRL , 7);

    /* CM_IVAHD0_SL2_CLKCTRL. MODULEMODE = 0x2;
    CM_IVAHD0_IVAHD_CLKCTRL. MODULEMODE = 0x2; */

    WR_MEM_32(CM_IVAHD0_SL2_CLKCTRL , 2);
    WR_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL , 2);

    /* RM_IVAHD0_RSTCTRL = !IVA_RST3 | IVA_RST2 | IVA_RST1; : 0x3 */
    WR_MEM_32(RM_IVAHD0_RSTCTRL , 3);

    /* Wait for !IDLE
    while(CM_IVAHD0_IVAHD_CLKCTRL.IDLEST != 0x0);
    while(CM_IVAHD0_SL2_CLKCTRL.IDLEST != 0x0); */ 
    do{
    temp = RD_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL);
    temp = ((temp >> 16) & 3);
    }while(temp != 0);
    do{
    temp = RD_MEM_32(CM_IVAHD0_SL2_CLKCTRL);
    temp = ((temp >> 16) & 3);
    }while(temp != 0);

    /* while(RM_IVAHD0_RSTST.IVA_RST3 != 0x1); */
    do{
    temp = RD_MEM_32(RM_IVAHD0_RSTST);
    temp = ((temp >> 2) & 1);
    }while(temp != 1);
    
    return (XDAS_TRUE);

#elif ( (HOSTCORTEXM3_OMAP4) && (!HOSTCORTEXM3_OMAP4SIMULATOR) )

    volatile unsigned int * resetControlRegister = NULL;
    volatile unsigned int * resetControlStatusRegister = NULL;
    volatile unsigned int * ivahdClockControlRegister = NULL;
    volatile unsigned int * ivahdClockControlStatusRegister = NULL;
    volatile unsigned int * sl2ClockControlRegister = NULL;
    volatile int debugCounter1=0,debugCounter2=0;
    
    /*Reset IVA HD,SL2 and ICONTs */
    resetControlRegister             = 
      (volatile unsigned int *)(iresHandle->resetControlAddress);
    resetControlStatusRegister       = 
      (volatile unsigned int *)(((unsigned int)resetControlRegister) + 4);
    ivahdClockControlStatusRegister  = 
     (volatile unsigned int *)(((unsigned int)resetControlRegister) - 0x2FE010);
    ivahdClockControlRegister        = 
      (volatile unsigned int *)(((unsigned int)ivahdClockControlStatusRegister)
                                                                       + 0x20);
    sl2ClockControlRegister          = 
     (volatile unsigned int *)(((unsigned int)ivahdClockControlStatusRegister) 
                                                                       + 0x28);
    
    /* First put IVA into HW Auto mode */
    *ivahdClockControlStatusRegister |= 0x3;
    
    /* Wait for IVA HD to  standby */
    while (!((*ivahdClockControlRegister) & 0x40000));
    
    /*Disable IVAHD and SL2 modules*/
    *ivahdClockControlRegister = 0;
    *sl2ClockControlRegister = 0;
    
    /*Ensure that IVAHD and SL2 are disabled*/
    do {
        if((*ivahdClockControlRegister) & 0x00030000) {
            break;
        }
    } while (1);
    
    do {
        if((*sl2ClockControlRegister) & 0x00030000) {
            break;
        }
    } while (1);
    
   /*Reset IVAHD sequencers and SL2*/
    *resetControlRegister |= 7;
    
    /*Check if modules are reset*/
    
    /*First clear the status bits*/
    *resetControlStatusRegister |= 7;
    
    /*Wait for confirmation that the systems have been reset.                 */
    /*THIS CHECK MAY NOT BE NECESSARY, AND MOST OF ALL GIVEN OUR STATE,       */
    /*MAY NOT BE POSSIBLE                                                     */
    
    /* Ensure that the wake up mode is set to SW_WAKEUP */
    *ivahdClockControlStatusRegister &= 0x2;
    
    /*Enable IVAHD and SL2 modules*/
    *ivahdClockControlRegister = 1;
    *sl2ClockControlRegister = 1;
    
    /*Deassert the SL2 reset*/
    *resetControlRegister &= 0xFFFFFFFB;
    
    /*Ensure that IVAHD and SL2 are enabled*/
    do {
        if(!((*ivahdClockControlRegister) & 0x00030000)) {
            break;
        }
        /* Just to check the number of iterations taken for the modules to get*/
        /* enabled                                                            */
        debugCounter1++;
    } while (1);
    
    do {
        if(!((*sl2ClockControlRegister) & 0x00030000)) {
            break;
        }
        /* Just to check the number of iterations taken for the modules to get*/
        /* enabled                                                            */
        debugCounter2++;
    } while (1);
    return (XDAS_TRUE);
#elif ( (HOSTCORTEXM3_NETRASIMULATOR) && (!HOSTCORTEXM3_NETRA) )
   return (XDAS_TRUE);
#elif ( (HOSTCORTEXM3_OMAP4SIMULATOR) && (!HOSTCORTEXM3_OMAP4) )
     return (XDAS_TRUE);
#else
    return (XDAS_TRUE);
#endif   
}

/**
********************************************************************************
*  @fn     HDVICP_Done(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
*
*  @brief  This function will be called by the interrupt handler
*          function when it detects an end-of-frame processing.
*
*  @param[in]  handle        : Handle to the Algorithm
*
*  @param[in]  iresHandle    : Handle to IRES
*
*  @return     none
********************************************************************************
*/
void HDVICP_Done(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
{
  unServMesgCount++;
}


IRES_HDVICP2_Obj IRES_HDVICP2_handle = {
  0,                            /* IRES_Obj.persistent                        */
  0,                            /* getStaticProperties                        */
  0,                            /* info (reserved)                            */
  0,                            /* ID of the HDVICP2 being granted,           */
  /*   could be 0,1,2, or LATE_ACQUIRE          */
  0,                            /* Reg. space base addr                       */
  0,                            /* Mem. Space base addr                       */
  0,                            /* PRCM register address                      */

  (Void (*)(IALG_Handle, struct IRES_HDVICP2_Obj *, IRES_YieldContext *,
  XDAS_UInt32 *, UInt *,Int))
  HDVICP_Acquire,               /* This call acquires the HDVICP resource     */
  /*   which the alg may (or maynot) have       */
  /*   specifically requested                   */
  
  HDVICP_Release,               /* Call to release the HDVICP resource being  */
  /*   used, to make it available for use by    */
  /*   other algs                               */
  
  HDVICP_reacquireIfOwner,      /* reacquireIfOwner- Call to reacquire an     */
  /*   HDVICP resource                          */
  
  HDVICP_Configure,             /* Call to configure the HDVICP2 instance,    */
  /*   to process data.                         */
  
  HDVICP_Wait,                  /* Waits for the HDVICP2 to return after      */
  /*   processing data                          */
  
  HDVICP_Done,                  /* Call to get out of the wait after end of   */
  /*   processing data                          */
  
  HDVICP_Reset                  /* reset- Framework supplied function to be   */
  /*   called by the codec when it acquired     */
  /*   HDVICP2 when the resource is full dirty  */ 
  /*   mode                                     */
};

/**
********************************************************************************
*  @fn     allignMalloc(size_t alignment, size_t size)
*
*  @brief  Allign memory
*
*
*  @param  alignment : Alligment parameter
*
*  @param  size      : Size of memory
*
*  @return             void *
********************************************************************************
*/
void *allignMalloc(size_t alignment, size_t size)
{
  void **mallocPtr;
  void **retPtr;
  /*--------------------------------------------------------------------------*/
  /* return if invalid size value                                             */
  /*--------------------------------------------------------------------------*/

  if (size <= 0)
  {
    return (0);
  }

  /*--------------------------------------------------------------------------*/
  /* If alignment is not a power of two, return what malloc returns. This is  */
  /* how memalign behaves on the c6x.                                         */
  /*--------------------------------------------------------------------------*/
  if ((alignment & (alignment - 1)) || (alignment <= 1))
  {
    if ((mallocPtr = malloc(size + sizeof(mallocPtr))) != NULL)
    {
      *mallocPtr = mallocPtr;
      mallocPtr++;
    }
    return ((void *)mallocPtr);
  }

  /*--------------------------------------------------------------------------*/
  /* allocate block of memory                                                 */
  /*--------------------------------------------------------------------------*/

  if (!(mallocPtr = malloc(alignment + size)))
  {
    return (0);
  }

  /*--------------------------------------------------------------------------*/
  /* Calculate aligned memory address                                         */
  /*--------------------------------------------------------------------------*/
  retPtr = (void *)(((Uns) mallocPtr + alignment) & ~(alignment - 1));

  /*--------------------------------------------------------------------------*/
  /* Set pointer to be used in the mem_free() fxn                             */
  /*--------------------------------------------------------------------------*/
  retPtr[-1] = mallocPtr;

  /*--------------------------------------------------------------------------*/
  /* return aligned memory                                                    */
  /*--------------------------------------------------------------------------*/
  return ((void *)retPtr);
}

/**
********************************************************************************
*  @fn     allignFree(void *ptr)
*
*  @brief  Free memory
*
*  @param  ptr  : Pointer to memory
*
*  @return none
********************************************************************************
*/
void allignFree(void *ptr)
{
  free((void *)((void **)ptr)[-1]);
}

/**
********************************************************************************
*  @fn     RMAN_AssignResources(IALG_Handle handle)
*
*  @brief  Implementation of RMAN_AssignResources API
*
*  @param[in]  handle  : Handle to Algorithm
*
*  @return none
********************************************************************************
*/
void RMAN_AssignResources(IALG_Handle handle)
{
  IRES_ResourceDescriptor *resourceDescriptor;
  Int32             numResources;
  IRES_YieldFxn     yieldFxn = NULL;      /* acquired from RMAN during init   */
  IRES_YieldArgs    yieldArgs = NULL;     /* acquired from RMAN during init   */
  IRES_TILEDMEMORY_ProtocolArgs *tiledmemProtocolArgs;
  numResources = JPEGVENC_TI_IRES.numResourceDescriptors(handle);
  resourceDescriptor = (IRES_ResourceDescriptor *)malloc(numResources *
  sizeof(IRES_ResourceDescriptor));

  if((numResources - 1) > NUM_TILEDMEM_OBJECTS)
  {
    printf(" Exceeding Availeble resource\n", numResources);
  }

  /*-------------------------------------------------------------------------*/
  /* Reset the isAcquireCallMade                                             */
  /*-------------------------------------------------------------------------*/
  isAcquireCallMade = 0;

  JPEGVENC_TI_IRES.getResourceDescriptors(handle, resourceDescriptor);

  /*--------------------------------------------------------------------------*/
  /* Create the HDVICP2 handle and pass it through the Resource Descriptor.   */
  /*--------------------------------------------------------------------------*/
  resourceDescriptor[0].handle = (IRES_Obj *)&IRES_HDVICP2_handle;

  if( numResources > 1)
  {
    /*------------------------------------------------------------------------*/
    /*  Create the TILED memory handles and pass it through                   */
    /*  the Resource Descriptor.                                              */
    /*------------------------------------------------------------------------*/
    resourceDescriptor[1].handle =
    (IRES_Obj *)&iresTiledMemoryObjects[0];

    /*------------------------------------------------------------------------*/
    /*        Obtain attributes of the memory request                         */
    /*------------------------------------------------------------------------*/
    tiledmemProtocolArgs =
    (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor[1].protocolArgs;

    /*------------------------------------------------------------------------*/
    /* Allocate memory and assign it to the object                            */
    /* Only 1D objects assumed                                                */
    /*------------------------------------------------------------------------*/
    iresTiledMemoryObjects[0].memoryBaseAddress =
    (Void *)malloc((tiledmemProtocolArgs->sizeDim0 * 
    sizeof(XDAS_UInt8)));
    
    iresTiledMemoryObjects[0].accessUnit    = IRES_TILEDMEMORY_RAW;
    iresTiledMemoryObjects[0].isTiledMemory = 0;
  }

  /*-------------------------------------------------------------------------*/
  /* Init all the assigned resources here                                    */
  /*-------------------------------------------------------------------------*/
  JPEGVENC_TI_IRES.initResources(handle, resourceDescriptor, yieldFxn,
  yieldArgs);

}

/**
********************************************************************************
*  @fn     RMAN_FreeResources(IALG_Handle handle)
*
*  @brief  Implementation of RMAN_FreeResources API
*
*  @param[in]  handle  : Handle to Algorithm
*
*  @return none
********************************************************************************
*/
void RMAN_FreeResources(IALG_Handle handle)
{
  Int32    numResources, idx;
  IRES_ResourceDescriptor *resourceDescriptor;
  IRES_TILEDMEMORY_Obj    *TiledMemoryObject;

  /*-------------------------------------------------------------------------*/
  /* Get the number of memory resources allocated                            */
  /*-------------------------------------------------------------------------*/
  numResources = JPEGVENC_TI_IRES.numResourceDescriptors(handle);
  printf("In RMAN_FreeResources :numResources=%d\n",numResources);
  
  resourceDescriptor = (IRES_ResourceDescriptor *)malloc(numResources *
  sizeof(IRES_ResourceDescriptor));
  
  JPEGVENC_TI_IRES.getResourceDescriptors(handle, resourceDescriptor);
  
  /*-------------------------------------------------------------------------*/
  /* Free the allocated memory resources                                     */
  /*-------------------------------------------------------------------------*/
  for(idx = 1 ; idx<(numResources) ; idx++)
  {
    TiledMemoryObject = (IRES_TILEDMEMORY_Obj *) resourceDescriptor[idx].handle;
    MemoryFree(TiledMemoryObject->memoryBaseAddress);
  }
}


/**
*******************************************************************************
*  @fn     MemoryFree(void * address)
*
*  @brief  frees a chunk of memory
*
*  @param[in]  address : Memory pointer to be freed
*
*  @return None
*******************************************************************************
*/
static Void MemoryFree(void * address)
{
  IALG_MemRec memTab;
  memTab.base = address;
  memTab.alignment = 0;
  memTab.space = IALG_EXTERNAL;
  memTab.attrs = IALG_PERSIST;
  _ALG_freeMemory(&memTab, 1);
}
