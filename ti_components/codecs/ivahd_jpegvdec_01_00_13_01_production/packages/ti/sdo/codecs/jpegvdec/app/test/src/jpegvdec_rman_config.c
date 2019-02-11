/*
********************************************************************************  
* HDVICP2.0 Based JPEG Decoder
*
* "HDVICP2.0 Based JPEG Decoder" is software module developed on
* TI's HDVICP2 based SOCs. This module is capable of generating a raw image 
* by de-compressing/decoding a jpeg bit-stream based on ISO/IEC IS 10918-1. 
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
* ALL RIGHTS RESERVED 
********************************************************************************
*/

/**  
********************************************************************************
* @file      jpegvdec_rman_config.c                           
*
* @brief     This File contains functions for IRES IMPLEMENTATION 
*
* @author    Chetan
*
* @version 0.0 (Dec 2008) : Created the initial version.[Odanaka]
*
* @version 0.1 (Feb 2010) : Cleaned code to adhere for the coding guidelines
*                           [Chetan]  
*
* @version 0.2 (Sept 2010) : M3 Part Aligned with all other codecs
*                           [Chetan]  
*
*******************************************************************************
*/

/*----------------------compilation control switches -------------------------*/

/*******************************************************************************
*   INCLUDE FILES
*******************************************************************************/
/*--------------------- system and platform files ----------------------------*/
#include <xdc/std.h>
#include <stdio.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/ires.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/sdo/fc/utils/api/_alg.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>
#include <ti/sdo/fc/ires/tiledmemory/ires_tiledmemory.h>


#include <stdlib.h>     /* malloc/free declarations */

/*----------------------program files ----------------------------------------*/
#include "jpegvdec_rman_config.h"
#include "ijpegvdec.h"
#include "jpegvdec_ti.h"

/**
*  SL2 Base Address, Register's Base Address & PRCM Base Address Set 
*  Based on Host Type Used   
*/
#if defined(MY)
#define IVAHD_HOST_REG_BASE    0xBA000000
#define IVAHD_HOST_SL2_BASE    0xBB000000
#define IVAHD_PRCM_BASE        0xAA306F10

#elif (HOSTCORTEXM3_OMAP4 || HOSTCORTEXM3_OMAP4SIMULATOR)
#define IVAHD_HOST_REG_BASE    0x5A000000
#define IVAHD_HOST_SL2_BASE    0x5B000000
#define IVAHD_PRCM_BASE        0x4A306F10

#elif (HOSTCORTEXM3_NETRA_IVAHD0 || HOSTCORTEXM3_NETRASIMULATOR)
#define IVAHD_HOST_REG_BASE    0x58000000
#define IVAHD_HOST_SL2_BASE    0x59000000
#define IVAHD_PRCM_BASE        0x48180C10

#elif defined(HOSTCORTEXM3_NETRA_IVAHD1)
#define IVAHD_HOST_REG_BASE    0x5A000000
#define IVAHD_HOST_SL2_BASE    0x5B000000
#define IVAHD_PRCM_BASE        0x48180D10

#elif defined(HOSTCORTEXM3_NETRA_IVAHD2)
#define IVAHD_HOST_REG_BASE    0x53000000
#define IVAHD_HOST_SL2_BASE    0x54000000
#define IVAHD_PRCM_BASE        0x48180E10

#else
#define IVAHD_HOST_REG_BASE    0x50080000
#define IVAHD_HOST_SL2_BASE    0x00800000
#define IVAHD_PRCM_BASE        0x00000000
#endif

/*******************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/
extern Uint32 initialFrame;

/*---------------------------------------------------------------------------*/
/*  Global Flag which will be intially be zero.                              */
/*  If acquire is made once, then this flag will be set and stay set.        */
/*---------------------------------------------------------------------------*/
Uint32 isAcquireCallMade;
/*----------------------------------------------------------------------------*/
/*  Global flag for non-blocking call.                                        */
/*----------------------------------------------------------------------------*/

extern volatile XDAS_Int32 unServMesgCount;
extern volatile XDAS_Int32 ServMesgCount;

typedef void (*ISR_VECTOR_TABLE)();
extern ISR_VECTOR_TABLE vector_table[];
/*******************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/* ------------------------------ macros ------------------------------------ */
#define NUM_TILEDMEM_OBJECTS 1
/**
* Global Algorithm handle which will be initialized with the argument to   
*  the algorithm's MB processing function.                                 
*/
IALG_Handle gHandle[NUM_IVAHD_RESOURCES];

/**
*  Global Arguments which will be initialized with the argument to          
*  the algorithm's MB processing function.                                  
*/
Uint32 gCbArgs[NUM_IVAHD_RESOURCES];

/**
*  Global function pointer which will be initialized to the algorithm's MB  
*  processing function and will be called by the gem interrupt handler      
*  function. The following array is being declared to use the host with multiple
*  IVAHD resources                                                               
*/
void (* gFnPtr[NUM_IVAHD_RESOURCES])(IALG_Handle handle, void *cbArgs);
IRES_TILEDMEMORY_Obj    iresTiledMemoryObjects[NUM_TILEDMEM_OBJECTS];
/*----------function prototypes ----------------------------------------------*/

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
  /* As with Ducati a single IVA-HD resource is tied                          */
  /* this id shall be zero.                                                   */
  /*--------------------------------------------------------------------------*/
  (*gFnPtr[0])(gHandle[0], (void *)gCbArgs[0]);
}
/** 
*******************************************************************************
*  @fn     HDVICP_Acquire(IALG_Handle handle, 
*                         IRES_HDVICP2_Handle iresHandle, 
*                         IRES_YieldContext * pYieldCtxt, 
*                         XDAS_UInt32 * hdvicp2Status, 
*                         XDAS_UInt32 * modeId, XDAS_Int32 lateAcquireArg)
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
*  @param[in]  handle        : Pointer to the IALG_Handle structure
* 
*  @param[in]  iresHandle    : Pointer to the IRES_HDVICP2_Handle structure
*
*  @param[in]  pYieldCtxt     : Pointer to the IRES_YieldContext structure
*
*  @param[in]  hdvicp2Status  : Pointer to the IRES_HDVICP2_Status structure
*
*  @param[in,out] modeId     : The mode in which this particular HDVICP2 was
*                              used last time, and the mode in which it will  
*                              be used this time 
*  @param[in] lateAcquireArg : This is the channel id which codec returns
*                              while acquiring the HDVICP2
*  @return     None
*
********************************************************************************
*/
void HDVICP_Acquire(IALG_Handle handle, 
IRES_HDVICP2_Handle iresHandle, 
IRES_YieldContext * pYieldCtxt, 
XDAS_UInt32 * hdvicp2Status, 
XDAS_UInt32 * modeId, XDAS_Int32 lateAcquireArg)
{
  Int32 ID = 0;
  Uint32    regBaseAddr, memBaseAddr, prcmBaseAddr;

  if( (NULL == handle)  || (iresHandle == NULL))
  return;

  /*--------------------------------------------------------------------------*/
  /* After the resource allocation the new resource ID is communicated        */
  /*--------------------------------------------------------------------------*/
  iresHandle->id = ID;                                                        
  
  /*--------------------------------------------------------------------------*/
  /* Address space notification                                               */
  /* Notification of SL2 memory as seen by the Host ARM.                      */
  /* IVAHD_CONFIG Base address as understood by Cortex-M3                     */
  /*--------------------------------------------------------------------------*/
  regBaseAddr = (Uint32)IVAHD_HOST_REG_BASE; /* Length: 0x00080000 bytes */   
  
  /*--------------------------------------------------------------------------*/
  /* IVAHD_SL2 Base address as understood by Cortex-M3                        */
  /*--------------------------------------------------------------------------*/
  memBaseAddr = (Uint32)IVAHD_HOST_SL2_BASE; /* Length: 0x00080000 bytes */   
  
  /*--------------------------------------------------------------------------*/
  /* IVAHD_PRCM Base address as understood by Cortex-M3                       */
  /*--------------------------------------------------------------------------*/
  prcmBaseAddr = (Uint32)IVAHD_PRCM_BASE; /* Length: 0x0 bytes */             
  
  iresHandle->registerBaseAddress = (void *)regBaseAddr;                      
  iresHandle->memoryBaseAddress = (void *)memBaseAddr;                        
  iresHandle->resetControlAddress = (void *)prcmBaseAddr;                     
  
  /*--------------------------------------------------------------------------*/
  /* Reset indicates that the codec-process call need not reload the code     */
  /* Set indicates that the codec-process call needs to reload the code       */
  /*--------------------------------------------------------------------------*/

  
  if(initialFrame == 0)
  {
  *hdvicp2Status = DIFFERENTCODEC;
  
  }
  else
  {
    
  *hdvicp2Status = SAMECODECTYPE;
  
  }
    

#if defined (_ENABLE_BOOTING_)
  if(initialFrame == 0)
  {
#if (HOSTCORTEXM3_NETRA_IVAHD0 || HOSTCORTEXM3_NETRASIMULATOR)      
    IVAHD_Standby_power_on_uboot(IVAHD_CONFIG_REG_BASE_IVAHD0, 
                                       PRCM_IVAHD_ICONT_RST_CNTL_ADDR_IVAHD0);
#endif

#ifdef HOSTCORTEXM3_NETRA_IVAHD1    
    IVAHD_Standby_power_on_uboot(IVAHD_CONFIG_REG_BASE_IVAHD1, 
                                       PRCM_IVAHD_ICONT_RST_CNTL_ADDR_IVAHD1);
#endif

#ifdef HOSTCORTEXM3_NETRA_IVAHD2    
    IVAHD_Standby_power_on_uboot(IVAHD_CONFIG_REG_BASE_IVAHD2, 
                                       PRCM_IVAHD_ICONT_RST_CNTL_ADDR_IVAHD2);
#endif                                     

#if (HOSTCORTEXM3_OMAP4 || HOSTCORTEXM3_OMAP4SIMULATOR)     
    IVAHD_Standby_power_on_uboot(IVAHD_CONFIG_REG_BASE_IVAHD0, 
                                       PRCM_IVAHD_ICONT_RST_CNTL_ADDR_IVAHD0);
#endif
  }
#endif
  
  initialFrame++; 
  /*-------------------------------------------------------------------------*/
  /* Set that acquire call already made                                      */
  /*-------------------------------------------------------------------------*/
  isAcquireCallMade = 1;   

}
/** 
*******************************************************************************
*  @fn     HDVICP_Configure(IALG_Handle handle, 
*                          IRES_HDVICP2_Handle iresHandle, 
*                          void (*IRES_HDVICP2_CallbackFxn)
*                          (IALG_Handle handle, void *cbArgs),
*                          void *cbArgs)
*
*  @brief  This function configures global variables 
*          
*  @param[in] handle                        : Alg handle 
*
*  @param[out] iresHandle                   : Ires handle
*
*  @param[out] IRES_HDVICP2_CallbackFxn     : Global function pointer to the 
*                                             MB processing function 
*  @param[out] cbArgs                       : Arguments to the MB processing 
*                                             function
*          
*  @return none
*
*******************************************************************************
*/
void HDVICP_Configure(IALG_Handle handle,
IRES_HDVICP2_Handle iresHandle, 
void (*IRES_HDVICP2_CallbackFxn)
(IALG_Handle handle, void *cbArgs),
void *cbArgs)
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
#if (HOSTCORTEXM3_OMAP4 || HOSTCORTEXM3_OMAP4SIMULATOR)
  *((int *) 0xE000E100)  = 0x00400000;
  
  vector_table[38] = ISR_Function; /*ISR Address*/
#endif  /* HOSTCORTEXM3_OMAP4 */
  
#if (HOSTCORTEXM3_NETRA_IVAHD0 || HOSTCORTEXM3_NETRASIMULATOR)
  *((int *) 0xE000E100)  = 0x00400000;
  
  vector_table[38] = ISR_Function; /*ISR Address*/
#endif  /* HOSTCORTEXM3_NETRA_IVAHD0 */ 
  
#ifdef HOSTCORTEXM3_NETRA_IVAHD1
  *((int *)0xE000E100) = 0x00080000;  /*Interrupt enable on Cortex-M3*/
  vector_table[35]     = ISR_Function; /*ISR Address*/
#endif /* HOSTCORTEXM3_NETRA_IVAHD1 */

#ifdef HOSTCORTEXM3_NETRA_IVAHD2
  *((int *)0xE000E100) = 0x00010000;  /*Interrupt enable on Cortex-M3*/
  vector_table[32]     = ISR_Function; /*ISR Address*/
#endif /* HOSTCORTEXM3_NETRA_IVAHD2 */  

}

/** 
*******************************************************************************
*  @fn     HDVICP_Release(IALG_Handle handle, 
*                         IRES_HDVICP2_Handle iresHandle)
*
*  @brief  Release
*
*  @param[in] handle                        : Alg handle 
*
*  @param[out] iresHandle                   : Ires handle
*
*  @return none
*******************************************************************************
*/
void HDVICP_Release(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
{
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

  JPEGVDEC_TI_IRES.deactivateResource(
      (IALG_Handle) handle,
      (IRES_Handle) iresHandle);
}

/** 
*******************************************************************************
*  @fn     HDVICP_Wait(IALG_Handle handle,
*                      IRES_HDVICP2_Handle iresHandle, 
*                      IRES_YieldContext * yieldCtxt)
*
*  @brief  This function waits for IVAHD done
*          
*  @param[in] handle                        : Alg handle 
*
*  @param[out] iresHandle                   : Ires handle
*
*  @param[in] yieldCtxt                     : IRES yieldContext
*
*  @return TRUE/FAIL
*******************************************************************************
*/
XDAS_UInt32 HDVICP_Wait(IALG_Handle handle,
IRES_HDVICP2_Handle iresHandle, 
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
XDAS_UInt32 HDVICP_Reset(
IALG_Handle algHandle, 
struct IRES_HDVICP2_Obj * iresHandle)
{   
#if ( (HOSTCORTEXM3_NETRA_IVAHD0 || HOSTCORTEXM3_NETRA_IVAHD1 || \
               HOSTCORTEXM3_NETRA_IVAHD2 ) && (!HOSTCORTEXM3_NETRASIMULATOR) )

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
#else
    return (XDAS_TRUE);
#endif
}

/** 
*******************************************************************************
*  @fn     HDVICP_Done(IALG_Handle handle, 
*                      IRES_HDVICP2_Handle iresHandle)
*
*  @brief   This function will be called by the interrupt handler function 
*           when it detects an end-of-frame processing
*          
*  @param[in] handle                        : Alg handle 
*
*  @param[out] iresHandle                   : Ires handle
*           
*  @return none
*
*******************************************************************************
*/
void HDVICP_Done(IALG_Handle handle, 
IRES_HDVICP2_Handle iresHandle)
{
  /*--------------------------------------------------------------------------*/
  /*  This function will be called by the interrupt handler function when     */
  /*  it detects Message from IVAHD        .                                  */
  /*--------------------------------------------------------------------------*/

  unServMesgCount++;

}

/**
* Define IRES_HDVICP2_Obj handle here                           
*/
IRES_HDVICP2_Obj IRES_HDVICP2_handle = {
  0,  /* IRES_Obj.persistent */
  0,  /* getStaticProperties */
  0,  /* info (reserved)     */         
  0,  /* ID of the HDVICP2 being granted, could be 0,1,2, or LATE_ACQUIRE */
  0,  /* Reg. space base addr */
  0,  /* Mem. Space base addr */
  0,  /* PRCM register address */  

  HDVICP_Acquire,
  HDVICP_Release,
  HDVICP_reacquireIfOwner, /* reacquireIfOwner */
  HDVICP_Configure,
  (XDAS_UInt32 (*)(IALG_Handle algHandle, struct IRES_HDVICP2_Obj * this,
  IRES_YieldContext * pYieldCtxt))HDVICP_Wait,
  HDVICP_Done,
  HDVICP_Reset /* reset */
};

/**
********************************************************************************
*  @fn      RMAN_AssignResources(IALG_Handle handle)
*
*  @brief     Funtion to assigne the HDVICP and Memory resources, This is  
*             dummy implimentation to emulate exact RMAN module API
*
*  @param[in]  handle : Pointer to the Algorithm Handle structure
*
*  @return     None.
*******************************************************************************
*/
void RMAN_AssignResources(IALG_Handle handle)
{
  IRES_ResourceDescriptor *resourceDescriptor;
  Int32                 retVal, numResources;
  
  IRES_TILEDMEMORY_ProtocolArgs *tiledmemProtocolArgs;

  /*--------------------------------------------------------------------------*/
  /* ALG_activate function to be called before each control call to copy      */
  /* image of handle structure data in the external persistant memory to      */
  /* scarcth memory                                                           */
  /*--------------------------------------------------------------------------*/
  ALG_activate((IALG_Handle)handle);

  numResources = JPEGVDEC_TI_IRES.numResourceDescriptors(handle);

  fprintf(stdout, "Number of Resources required = %d\n", numResources);
  
  resourceDescriptor = (IRES_ResourceDescriptor *)malloc(numResources *
  sizeof(IRES_ResourceDescriptor));
  
  /*-------------------------------------------------------------------------*/
  /* Reset the isAcquireCallMade                                             */
  /*-------------------------------------------------------------------------*/
  isAcquireCallMade = 0;

  retVal = JPEGVDEC_TI_IRES.getResourceDescriptors(handle, resourceDescriptor);
  
  /* To remove warning */
  retVal = retVal;

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

  retVal = JPEGVDEC_TI_IRES.initResources(handle, resourceDescriptor, 
  NULL, NULL);

  /*--------------------------------------------------------------------------*/
  /* ALG_deactivate function to be called before each control call to store   */
  /* image of handle structure data in the scarcth  memory to                 */
  /* external persistant memory                                               */
  /*--------------------------------------------------------------------------*/
  ALG_deactivate((IALG_Handle)handle);

}

/**
*******************************************************************************
*  @fn     RMAN_FreeResources(IALG_Handle handle)
*
*  @brief  This function frees the resources
*
*  @param[in]  handle : Pointer to the IALG_Handle structure
*
*  @return     None
*******************************************************************************
*/
void RMAN_FreeResources(IALG_Handle handle)
{
  Int32    numResources, idx;
  IRES_ResourceDescriptor *resourceDescriptor;
  IRES_TILEDMEMORY_Obj    *TiledMemoryObject;

  /*-------------------------------------------------------------------------*/
  /* Get the nimber of memory resources allocated                            */
  /*-------------------------------------------------------------------------*/
  numResources = JPEGVDEC_TI_IRES.numResourceDescriptors(handle);
  
  resourceDescriptor = (IRES_ResourceDescriptor *)malloc(numResources *
  sizeof(IRES_ResourceDescriptor));
  
  JPEGVDEC_TI_IRES.getResourceDescriptors(handle, resourceDescriptor);
  
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
XDAS_UInt32 HDVICP_reacquireIfOwner(
IALG_Handle handle, 
struct IRES_HDVICP2_Obj * iresHandle
)

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
    return FALSE;
  }
  else
  {
    return FALSE;
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


