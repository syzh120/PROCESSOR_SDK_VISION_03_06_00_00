/*
********************************************************************************  
 * HDVICP2.0 Based H.264 HP Encoder
 * 
 * "HDVICP2.0 Based H.264 HP Encoder" is software module developed on TI's 
 *  HDVICP2 based SOCs. This module is capable of compressing a 4:2:0 Raw 
 *  video into a high/main/baseline profile bit-stream. Based on ISO/IEC      
 *  14496-10." 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
********************************************************************************
*/
  

/** 
********************************************************************************
 * @file H264EncRmanConfig.c                          
 *                                       
 * @brief This file contains RMAN API functions
 *  
 *        This file contains functions to emulate actual RMAN in system
 *
 * @author: Pramod Swami (pramods@ti.com)
 *
 * @version 0.0 (Jan 2008) : Base version created
 *                           [Pramod]
 * @version 0.1 (Oct 2009) : Review and more commenting along with cleanup
 *                           [Rama Mohan]
 * @version 0.2 (Mar 2010) : Modified function arguments to make compatable with
 *                           FC 59 release
 * @version 0.3 (April 2010) : Modified HDVICP wait and done function to mimic
 *                           Counting semaphore implimentation.
 * @version 0.4 (April 2010) : Support of tiler buffer control [Pramod]
 * @version 0.5 (April 2010) : Added pointer check in alignfree function[Nirmal]
 * @version 0.6 (April 2010) : Added handle valid check, verification of
 *                             protocolArgs at RMAN_FreeResources which is
 *                             same as at create time and flag to check whether
 *                             Aquire call is made or not[Nirmal]
 * @version 0.7 (May 2010)   : Added review comments, added functions to check 
 *                             error robust ness of codec.
 * @version 0.8 (May 2010)   : Support of IVAHD sub system selection[Nirmal]
 * @version 0.9 (July 2010)  : Changes related to getBuf support for multiple 
 *                             blocks. PutDataFxn implementaion is also added
 * @version 1.0 (Sep 2010) :  Added support for long term reference frame
 * @version 1.1 (Sep 2010) : Support of setting value to numBlocks for
 *                           DataSyncGetData from user
 * @version 1.2 (Dec 2010) : Adding  HDVICP_Reset function for Netra
 * @version 1.3 (Dec 2010) : Cleanup related to platform specific macros
 * @version 1.4 (June 2011) : NALStream testing case added
 * @version 1.5(Apr 2012) :  Added code to request Ires Buffers for RoiInfo.
 *                           [Santoshkumar S K]
 *
********************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/ires.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/sdo/fc/utils/api/_alg.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>
#include <ti/sdo/fc/ires/tiledmemory/ires_tiledmemory.h>
#include <ti/sdo/fc/memutils/memutils.h>
#include <h264enc.h>
#include "H264BPEnc_rman_config.h"
#include "tilerBuf.h"

/* #define PROVIDE_ONE_BUFFER                                                 */

extern XDAS_Int32 gDataSyncUnitGap;
extern XDAS_Int32 currProcessCallNumChannel;
extern XDAS_Int32    inschan;
XDAS_UInt32   ivaCodeLoadDone;
/*----------------------------------------------------------------------------*/
/*  Global Algorithm handle which will be initialized with the argument to    */
/*  the algorithm's MB processing function.                                   */
/*----------------------------------------------------------------------------*/
IALG_Handle g_handle[MAX_ITEMS_TO_RUN][NUM_IVAHD_RESOURCES];
IALG_Handle g_handle_last;
IALG_Handle g_handle_last_prevAcuire;
XDAS_Int32 prevProcessCallNumChannel;

IRES_HDVICP2_Handle gHDVICP2Handle ;
/*----------------------------------------------------------------------------*/
/*  Global Arguments which will be initialized with the argument to           */
/*  the algorithm's MB processing function.                                   */
/*----------------------------------------------------------------------------*/
Uint32 g_cbArgs[NUM_IVAHD_RESOURCES];

/*----------------------------------------------------------------------------*/
/* Input data handles, we define 2 just to check some robust ness             */
/*----------------------------------------------------------------------------*/
XDM_DataSyncHandle fGetInpDHandle1;
XDM_DataSyncHandle fGetInpDHandle2;
XDM_DataSyncDesc   ip_datasyncDesc1;
XDM_DataSyncDesc   ip_datasyncDesc2;

/*----------------------------------------------------------------------------*/
/*  Global variables which will hold IVAHD Config, SL2 PRCM base address      */
/*----------------------------------------------------------------------------*/
Uint32 MEM_BASE;
Uint32 REG_BASE;
Uint32 RST_CNTL_BASE;

/*----------------------------------------------------------------------------*/
/*  Global function pointer which will be initialized to the algorithm's MB   */
/*  processing function and will be called by the gem interrupt handler       */
/*  function.                                                                 */
/*----------------------------------------------------------------------------*/
void (* g_fnPtr[NUM_IVAHD_RESOURCES])(IALG_Handle handle, void *cbArgs);

XDAS_Int32 blockSizeArray[NUM_BLOCKS] = {DATA_SYNCH_UNIT};

XDAS_Int32 blockAddrArray[NUM_BLOCKS];

/*--------------------------------------------------------------------------*/
/* Here we have given MAX_NUM_INPUT_BLOCKS blocks and also they are always  */
/* variable in size                                                         */
/*--------------------------------------------------------------------------*/
const XDAS_Int32 Input_BlockSizeArray[MAX_NUM_INPUT_BLOCKS] = 
                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  
                    /*{1,1,2,0,0,4,0,2,5,0,0,0,0,1,2};*/ 

/*--------------------------------------------------------------------------*/
/* Variables to back up the protocol Args & numResourcesBackUp              */
/* requested by the codec.                                                  */
/*--------------------------------------------------------------------------*/
XDAS_UInt32  numResourcesBackUp;
IRES_TILEDMEMORY_ProtocolArgs protocolArgsBackUp
                                      [MAX_ITEMS_TO_RUN][IRES_TOTAL_RESOURCES];
/*----------------------------------------------------------------------------*/
/* Flag to check whetehr Aquire call made or not                              */
/* NOTE: need to check with Uday why it is needed                             */
/*----------------------------------------------------------------------------*/
Uint32 isAcquireCallMade;

extern XDAS_UInt8 gOutputData[OUTPUT_BUFFER_SIZE];

extern XDAS_UInt32   insChanid;
extern XDAS_UInt32 gOutputDataProvided;
extern XDAS_Int32 gBlockSizes[];
extern XDAS_Int32 gBlockAddr[];
extern XDAS_Int32 gOutputBlocksRecieved;
/*----------------------------------------------------------------------------*/
/* Global config parameters                                                   */
/*----------------------------------------------------------------------------*/
extern h264BPEncConfig            gConfigOrg;
extern sTilerParams TilerParams;

extern ISR_VECTOR_TABLE vector_table[];


/*---------------------------------------------------------------------------*/
/*  Global flag for non-blocking call.                                       */
/*---------------------------------------------------------------------------*/
volatile XDAS_Int32 gSemCount;
extern IRES_Fxns H264ENC_TI_IRES;
extern XDAS_UInt32   insChanid;

/*---------------------------------------------------------------------------*/
/* Counter for setting Codec Type                                            */
/*---------------------------------------------------------------------------*/
Uint32 FrameNum  = 0 ;

/** 
********************************************************************************
 *  @fn     Init_IVAHDAddrSpace
 *  @brief  Function to get the IVAHD Config, SL2, PRCM base address based
 *          on IVAHD ID
 *          
 *  @param[in]  None
 *
 *  @return     None
********************************************************************************
*/
void Init_IVAHDAddrSpace()
{
  /* set ivahdid to 0 if it is other than 0, 1, 2       */
  if(gConfigOrg.ivahdid > 2)
  {
    gConfigOrg.ivahdid = 0 ;
  }
#if defined NETRA
  /*  If IVAHD1 subsystem     */
  if(gConfigOrg.ivahdid == 1)
  {
    /* IVAHD1 CONFIG Base address as understood by Cortex-M3 */
    MEM_BASE = MEM_BASE_IVAHD1;
    /* IVAHD1 SL2 Base address as understood by Cortex-M3 */
    REG_BASE = REG_BASE_IVAHD1;
    /* IVAHD1 PRCM Base address as understood by Cortex-M3 */
    RST_CNTL_BASE = RST_CNTL_BASE_IVAHD1;
  }
  /*  If IVAHD2 subsystem     */
  if(gConfigOrg.ivahdid == 2)
  {
    /* IVAHD2 CONFIG Base address as understood by Cortex-M3 */
    MEM_BASE = MEM_BASE_IVAHD2;
    /* IVAHD2 SL2 Base address as understood by Cortex-M3 */
    REG_BASE = REG_BASE_IVAHD2;
    /* IVAHD2 PRCM Base address as understood by Cortex-M3 */
    RST_CNTL_BASE = RST_CNTL_BASE_IVAHD2;
  }
#else
  gConfigOrg.ivahdid = 0 ;
#endif

  /*  If IVAHD0 subsystem     */
  if(gConfigOrg.ivahdid == 0)
  {
    /* IVAHD0 CONFIG Base address as understood by Cortex-M3 */
    MEM_BASE = MEM_BASE_IVAHD0;
    /* IVAHD0 SL2 Base address as understood by Cortex-M3 */
    REG_BASE = REG_BASE_IVAHD0;
    /* IVAHD0 PRCM Base address as understood by Cortex-M3 */
    RST_CNTL_BASE = RST_CNTL_BASE_IVAHD0;
  }
}

/** 
********************************************************************************
 *  @fn     ISR_Function
 *  @brief  ISR function for Mail box interrupts
 *          
 *          ISR function for all the IVAHD Mail box interrupts which intern 
 *          calls callback api function 
 *
 *  @param[in]  None
 *
 *  @return     None
********************************************************************************
*/
void ISR_Function()
{
  /*--------------------------------------------------------------------------*/
  /* Call-Back function tied to IVA-HD - 0. As with Ducati a single IVA-HD    */
  /* resource is tied this id shall be zero.                                  */
  /*--------------------------------------------------------------------------*/
  (*g_fnPtr[0])(g_handle_last, (void *)g_cbArgs[0]);

}

/** 
********************************************************************************
 *  @fn     HDVICP_Acquire
 *  @brief  Function to acquire HDVICP resource
 *          
 *
 *  @param[in] handle : pointer to algorithm handle
 *  
 *  @param[in] iresHandle : Pointer to the HDVICP resource handle
 * 
 *  @param[in] yieldCtxt : pointer to the context switch handle
 *
 *  @param[out] status : Pointer to the HDVICP status structure in which 
 *                       status of the aquired resource is returned
 *  @param[in/out] modeId : The mode in which this particular HDVICP2 was
 *                          used last time, and the mode in which it will be 
 *                          used this time 
 *  @param[in] lateAcquireArg : This is the channel id which codec returns
 *                              while acquiring the HDVICP2
 *  @return     None
********************************************************************************
*/
XDAS_Void HDVICP_Acquire(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle, 
          IRES_YieldContext *yieldCtxt, XDAS_UInt32 *status, 
          Uint32* modeId, Int lateAcquireArg )
{
  /*--------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                */
  /*--------------------------------------------------------------------*/
  if((IALG_Handle)g_handle_last != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                   */
  /*--------------------------------------------------------------------*/
  if(iresHandle != gHDVICP2Handle)
  {
    fprintf(stdout,"HDVICP handle not valid during acquire..\n");
  }
  /*--------------------------------------------------------------------------*/
  /* IVAHD_CONFIG Base address as understood by Cortex-M3                     */
  /*--------------------------------------------------------------------------*/
   iresHandle->registerBaseAddress = (void *)REG_BASE;
  /*--------------------------------------------------------------------------*/
  /* IVAHD_SL2 Base address as understood by Cortex-M3                        */
  /*--------------------------------------------------------------------------*/
   iresHandle->memoryBaseAddress = (void *)MEM_BASE;
  /*--------------------------------------------------------------------------*/
  /* IVAHD_PRCM Base address as understood by Cortex-M3                       */
  /*--------------------------------------------------------------------------*/
  iresHandle->resetControlAddress = (void *)RST_CNTL_BASE;
  /*--------------------------------------------------------------------------*/
  /* Mode of the resource used last time and this time                        */
  /* depending on this flag Resource memorys are initialised                  */
  /* When it is SAMECODEC only scratch memory is initialized                  */
  /* When it is SAMECODECTYPE only scratch and persistant memory is           */
  /* initialized                                                              */
  /* When it is DIFFERENTCODEC all scratch and persistant memorys are         */
  /* initialized including program memory                                     */
  /*--------------------------------------------------------------------------*/

  if(FrameNum)
  {
    if((IALG_Handle)g_handle_last_prevAcuire == handle)
    {
      *modeId = (Uint32)HDVICP_STATUS;
    }
    else
    {
      *modeId = (Uint32)SAMECODECTYPE;
    }
    ivaCodeLoadDone = XDAS_TRUE;
  }
  else
  {
    *modeId = (Uint32)DIFFERENTCODEC;
    FrameNum = 1;
    ivaCodeLoadDone = XDAS_FALSE;
  }
  g_handle_last_prevAcuire  = handle;
  prevProcessCallNumChannel = currProcessCallNumChannel;
 /*------------------------------------------------------------------------*/
 /*ncomment below two lines to force DIFFERENTFCODEC for very process call */
 /*------------------------------------------------------------------------*/

 /*
  *modeId = (Uint32)DIFFERENTCODEC;
   ivaCodeLoadDone = XDAS_FALSE; */

  /*------------------------------------------------------------------------*/
  /* Do the scratch area contamination                                      */
  /*------------------------------------------------------------------------*/
  H264ENC_TI_Scratch_Contaminate(*modeId);
  
  if(*modeId != SAMECODEC)
  {
    RMAN_activateHDVICP2Resource(handle, (IRES_Handle)iresHandle) ;
  }
  
  /*--------------------------------------------------------------------------*/
  /* Return the status of the resurce with mode it is going to be used        */
  /*--------------------------------------------------------------------------*/
  *status = (IRES_HDVICP2_Status)(*modeId);
  /*--------------------------------------------------------------------*/
  /* Check if acquire call is made earlier                              */
  /*--------------------------------------------------------------------*/
  if(isAcquireCallMade != 0)
  {
    fprintf(stdout,"HDVICP is being acquired without releasing..\n");
  }
  isAcquireCallMade = 1;
  H264ENC_TI_Capture_time(HDVICP_ACQUIRE);
  
  /*--------------------------------------------------------------------------*/
  /* lateAcquireArg is not used in this implementation                        */
  /*--------------------------------------------------------------------------*/
  /* printf("lateAcquireArg = %d\n", lateAcquireArg);                         */
}
/* Below function need to check with Uday*/
/** 
********************************************************************************
 *  @fn     HDVICP_reacquireIfOwner
 *  @brief  Function to acquire HDVICP resource
 *          
 *
 *  @param[in] handle : pointer to algorithm handle
 *  
 *  @param[in] iresHandle : Pointer to the HDVICP resource handle
 * 
 *  @param[in] yieldCtxt : pointer to the context switch handle
 *
 *  @param[out] status : Pointer to the HDVICP status structure in which 
 *                       status of the aquired resource is returned
 *  @param[in/out] modeId : The mode in which this particular HDVICP2 was
 *                          used last time, and the mode in which it will be 
 *                          used this time 
 *  @return     None
********************************************************************************
*/
XDAS_UInt32 HDVICP_reacquireIfOwner(IALG_Handle handle, 
                                    IRES_HDVICP2_Handle iresHandle)
          
{
  Uint32  regBaseAddr, memBaseAddr, resetControlAddress;

  /*--------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                */
  /*--------------------------------------------------------------------*/
  if((IALG_Handle)g_handle[insChanid][0] != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                   */
  /*--------------------------------------------------------------------*/
  if(iresHandle != gHDVICP2Handle)
  {
    fprintf(stdout,"HDVICP handle not valid during reacquire..\n");
  }
  /* After the resource allocation the new resource ID is communicated */
  /* iresHandle->id = ID;                                                     */
  /* Address space notification */
  /* Notification of SL2 memory as seen by the Host ARM. */
  /* IVAHD_CONFIG Base address as understood by Cortex-M3 */
  regBaseAddr = (Uint32)REG_BASE; /* Length: 0x00080000 bytes */
  
  /* IVAHD_SL2 Base address as understood by Cortex-M3 */
  memBaseAddr = (Uint32)MEM_BASE; /* Length: 0x00080000 bytes */

  /* IVAHD_PRCM Base address as understood by Cortex-M3 */
  resetControlAddress = (Uint32)RST_CNTL_BASE; /* Length: 0x0 bytes */

  iresHandle->registerBaseAddress = (void *)regBaseAddr;
  iresHandle->memoryBaseAddress = (void *)memBaseAddr;
  iresHandle->resetControlAddress = (void *)resetControlAddress;
  if(isAcquireCallMade)
    return TRUE;  
  else 
  {
    RMAN_deactivateHDVICP2Resource(handle, (IRES_Handle)iresHandle) ;
    return FALSE;  
}
}

/* 
  HDVICP_Configure API
*/
void dummy_isr()
{
  asm(" NOP ");
}

/** 
********************************************************************************
 *  @fn     HDVICP_Configure
 *  @brief  Function to configure HDVICP resource
 *          
 *
 *  @param[in] handle : Pointer to algorithm handle
 *  
 *  @param[in] iresHandle : Pointer to the HDVICP resource handle
 * 
 *  @param[in] IRES_HDVICP2_CallbackFxn : Pointer to the call back function, 
 *                                        This will be tied to ISR function
 *
 *  @param[out] cbArgs : Argument to be passed to the callback function 
 *
 *  @return     None
********************************************************************************
*/
void HDVICP_Configure(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle, 
             void (*IRES_HDVICP2_CallbackFxn)(IALG_Handle handle, void *cbArgs),
         void *cbArgs)
{
  Int32 resourceId = 0;

  /*--------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                */
  /*--------------------------------------------------------------------*/
  if((IALG_Handle)g_handle_last!= handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                   */
  /*--------------------------------------------------------------------*/
  if(iresHandle != gHDVICP2Handle)
  {
    fprintf(stdout,"HDVICP handle not valid during configure..\n");
  }
  /*--------------------------------------------------------------------------*/
  /*  Initialize the gSemCount flag upon which the HDVICP_Wait                */
  /*  shall poll.                                                             */
  /*--------------------------------------------------------------------------*/
  gSemCount = 0;
  /*--------------------------------------------------------------------------*/
  /*  Initialize the global function ptr to the MB processing function        */
  /*  which will be called from the ISR.                                      */ 
  /*--------------------------------------------------------------------------*/
  g_fnPtr[resourceId]  = IRES_HDVICP2_CallbackFxn;
  /*--------------------------------------------------------------------------*/
  /*  Initialize the Argument to the MB processing function that is           */
  /*  required to be called by the ISR.                                       */
  /*--------------------------------------------------------------------------*/
  g_cbArgs[resourceId] = (Uint32)cbArgs;
  /*--------------------------------------------------------------------------*/
  /* Register the interrupt function to the vector table in case of M3 host   */
  /*--------------------------------------------------------------------------*/

  if(gConfigOrg.ivahdid == 0)
  {
    *((volatile int *)0xE000E100) = 0x00400000; /* Interrupt enable on Ducati */
  vector_table[38] = ISR_Function;                 
  }                                                
  else if(gConfigOrg.ivahdid == 1)                    
  {                                                
    *((volatile int *)0xE000E100) = 0x00080000; /* Interrupt enable on Ducati */
    vector_table[35] = ISR_Function;               
  }                                                
  else if(gConfigOrg.ivahdid == 2)                    
  {                                                
    *((volatile int *)0xE000E100) = 0x00010000; /* Interrupt enable on Ducati */
    vector_table[32] = ISR_Function;
  } 
}

/** 
********************************************************************************
 *  @fn     HDVICP_Release
 *  @brief  Function to release HDVICP resource
 *
 *  @param[in] handle : Pointer to algorithm handle
 *  
 *  @param[in] iresHandle : Pointer to the HDVICP resource handle
 *
 *  @return     None
********************************************************************************
*/
void HDVICP_Release(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
{
  /*--------------------------------------------------------------------------*/
  /* As of now this is dummy function                                         */
  /* In this function we can put IVAHD in idle mode                           */
  /*--------------------------------------------------------------------------*/
  /*  U32 * IVAHD_CNTL_REG = (U32*)0x30082000;  From TB spec                
      U32 cntl_reg_val = *(IVAHD_CNTL_REG);
      cntl_reg_val |=  0x000000010;
      *(IVAHD_CNTL_REG) = cntl_reg_val; */
  H264ENC_TI_Capture_time(HDVICP_RELEASE);    

  /*--------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                */
  /*--------------------------------------------------------------------*/
  if((IALG_Handle)g_handle_last != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                   */
  /*--------------------------------------------------------------------*/
  if(gHDVICP2Handle != iresHandle)
  {
    fprintf(stdout,"HDVICP handle not valid..\n");
  }

  /*--------------------------------------------------------------------*/
  /* Check if acquire call is made earlier                              */
  /*--------------------------------------------------------------------*/
  if(isAcquireCallMade ==0)
  {
    fprintf(stdout,"HDVICP is being released without acquire..\n");
  }
  isAcquireCallMade = 0 ;
}

/** 
********************************************************************************
 *  @fn     HDVICP_Wait
 *  @brief  Function to wait for Interrupt from IVAHD mail box 
 *
 *  @param[in] handle : Pointer to algorithm handle
 *  
 *  @param[in] iresHandle : Pointer to the HDVICP resource handle
 *
 *  @param[in] yieldCtxt : Pointer to the context switch handle
 *
 *  @return     None
********************************************************************************
*/
XDAS_UInt32 HDVICP_Wait(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle,
                                                  IRES_YieldContext * yieldCtxt)
{
  H264ENC_TI_Capture_time(HDVICP_WAIT);

  /*--------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                */
  /*--------------------------------------------------------------------*/
  if((IALG_Handle)g_handle_last != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                   */
  /*--------------------------------------------------------------------*/
  if(iresHandle != gHDVICP2Handle)
  {
    fprintf(stdout,"HDVICP handle not valid during wait..\n");
  }
  /*--------------------------------------------------------------------------*/
  /* Set the global flag to ON and wait on the same flag, This flag will be   */
  /* reset HDVICP_Done function i.e after the frame process                   */
  /*--------------------------------------------------------------------------*/
  while(gSemCount == 0) ;
  gSemCount-- ;

  return 1 ;
}

/** 
********************************************************************************
 *  @fn     HDVICP_Done
 *  @brief  Function to send HDVICP resouce finished processing
 *          This function will be called by the inerrrupt handler function when
 *          it detects end of frame processing
 *
 *  @param[in] handle : Pointer to algorithm handle
 *  
 *  @param[in] iresHandle : Pointer to the HDVICP resource handle
 *
 *  @return     None
********************************************************************************
*/
void HDVICP_Done(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
{
  /*--------------------------------------------------------------------------*/
  /* Set the poll flag to zero so that host will come out of wait state       */
  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                */
  /*--------------------------------------------------------------------*/
  if((IALG_Handle)g_handle_last != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                   */
  /*--------------------------------------------------------------------*/
  if(iresHandle != gHDVICP2Handle)
  {
    fprintf(stdout,"HDVICP handle not valid during wait..\n");
  }
  gSemCount++ ;
  H264ENC_TI_Capture_time(HDVICP_DONE);
}

#define WR_MEM_32(addr, data) *(volatile unsigned int*)(addr) \
                                   = (unsigned int)(data)
#define RD_MEM_32(addr)    *(volatile unsigned int*)(addr) 
/** 
********************************************************************************
 *  @fn     HDVICP_Reset
 *  @brief  Function to reset HDVICP resouce before using it
 *          This function will be called by algorithm when needed
 *
 *  @param[in] handle : Pointer to algorithm handle
 *  
 *  @param[in] iresHandle : Pointer to the HDVICP resource handle
 *
 *  @return     0: Success, non-zero : Failure 
********************************************************************************
*/
XDAS_UInt32 HDVICP_Reset(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
{
#if ((defined(NETRA)) && !(defined(_SIMULATOR_)))
  unsigned int RM_IVAHD0_RSTCTRL =  
    (unsigned int)iresHandle->resetControlAddress; /* (PRM_IVAHD0 + 0x10)     */
  unsigned int RM_IVAHD0_RSTST =  
    (RM_IVAHD0_RSTCTRL + 4); /* (PRM_IVAHD0 + 0x14)                           */
  unsigned int CM_IVAHD0_IVAHD_CLKCTRL = 
    ((RM_IVAHD0_RSTCTRL - 0x610 ) + 0x20); /* (PRCM_BASE_ADDR + 0x0620)       */
  unsigned int CM_IVAHD0_SL2_CLKCTRL =  
    (CM_IVAHD0_IVAHD_CLKCTRL + 4); /* (PRCM_BASE_ADDR + 0x0624)               */

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

#elif ((defined(OMAP4)) && !(defined(_SIMULATOR_)))

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
  ivahdClockControlRegister        = (volatile unsigned int *)
           (((unsigned int)ivahdClockControlStatusRegister) + 0x20);
  sl2ClockControlRegister          = (volatile unsigned int *)
           (((unsigned int)ivahdClockControlStatusRegister) + 0x28);
  
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
  
  /*Wait for confirmation that the systems have been reset*/
  /*THIS CHECK MAY NOT BE NECESSARY, AND MOST OF ALL GIVEN OUR STATE, 
  MAY NOT BE POSSIBLE*/    
  
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
      /*----------------------------------------------------------------------*/
      /* Just to check the number of iterations taken for the                 */
    /* modules to get enabled                                               */
      /*----------------------------------------------------------------------*/
      debugCounter1++;
  } while (1);
  
  do {
      if(!((*sl2ClockControlRegister) & 0x00030000)) {
          break;
      }
      /*----------------------------------------------------------------------*/
      /* Just to check the number of iterations taken for the                 */
      /* modules to get enabled                                               */
      /*----------------------------------------------------------------------*/
      debugCounter2++;
  } while (1);
#endif
  return (XDAS_TRUE);
}

/*----------------------------------------------------------------------------*/
/* Initialise the HDVICP handle with default values                           */
/*----------------------------------------------------------------------------*/

IRES_HDVICP2_Obj IRES_HDVICP2_handle = {
  0,  /* IRES_Obj.persistent */
  0,  /* getStaticProperties */
  0,   /* info (reserved)        */
  0,  /* ID of the HDVICP2 being granted, could be 0,1,2, or LATE_ACQUIRE */
  (Void*)REG_BASE_IVAHD0,       /* Reg. space base addr  */
  (Void*)MEM_BASE_IVAHD0,       /* Mem. Space base addr  */
  (Void*)RST_CNTL_BASE_IVAHD0,  /* PRCM register address */  
  HDVICP_Acquire,          /* Pointer to the HDVICP_Acquire API function */
  HDVICP_Release,          /* Pointer to the HDVICP_Release API function */
  HDVICP_reacquireIfOwner, /* Pointer to the HDVICP_reacquireIfOwner 
                            API function */
  HDVICP_Configure,        /* Pointer to the HDVICP_Configure API function */
  HDVICP_Wait,             /* Pointer to the HDVICP_Wait API function */
  HDVICP_Done,              /* Pointer to the HDVICP_Done API function */
  HDVICP_Reset              /* Pointer to the HDVICP_Reset API function */
  
};
/*----------------------------------------------------------------------------*/
/* Initialize tiled memory resource handles with default values               */
/*----------------------------------------------------------------------------*/
IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_luma1[MAX_ITEMS_TO_RUN] =
{
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/  
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/  
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/  
  IRES_TILEDMEMORY_8BIT,
  
  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS, 

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL 
 },

{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/  
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/  
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/  
  IRES_TILEDMEMORY_8BIT,
  
  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS, 

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL 
 },

{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/  
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/  
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/  
  IRES_TILEDMEMORY_8BIT,
  
  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS, 

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL 
 },

{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/  
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/  
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/  
  IRES_TILEDMEMORY_8BIT,
  
  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS, 

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL 
 }
};

IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_luma2[MAX_ITEMS_TO_RUN] =
{
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/  
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/  
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/  
  IRES_TILEDMEMORY_8BIT,
  
  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS, 

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL 
 },

{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/  
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/  
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/  
  IRES_TILEDMEMORY_8BIT,
  
  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS, 

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL 
 },

{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/  
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/  
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/  
  IRES_TILEDMEMORY_8BIT,
  
  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS, 

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL 
 },

{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/  
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/  
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/  
  IRES_TILEDMEMORY_8BIT,
  
  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS, 

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL 
 }
};

IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_luma3[MAX_ITEMS_TO_RUN] =
{
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/  
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },
  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 }
};
IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_luma4[MAX_ITEMS_TO_RUN] =
{
 {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
}
};
IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_luma5[MAX_ITEMS_TO_RUN] =
{
 {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_8BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
}
};

IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_chroma1[MAX_ITEMS_TO_RUN] =
{
 {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },
  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 }
};

IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_chroma2[MAX_ITEMS_TO_RUN] =
{
 {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 }
};

IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_chroma3[MAX_ITEMS_TO_RUN] =
{
 {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 }
};
IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_chroma4[MAX_ITEMS_TO_RUN] =
{
 {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
}
};

IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_chroma5[MAX_ITEMS_TO_RUN] =
{
 {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
},
{
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_16BIT,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
}
};

IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_coloMBInfo[MAX_ITEMS_TO_RUN] =
{
 {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 }
};

IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_roiInfo[MAX_ITEMS_TO_RUN] =
{
 {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 }
};
IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_persistentMemory[MAX_ITEMS_TO_RUN] =
{
 {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 }
};
IRES_TILEDMEMORY_Obj IRES_TILEDMEMORY_debugTraceMemory[MAX_ITEMS_TO_RUN] =
{
 {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 },

  {
  {
    /*------------------------------------------------------------------------*/
    /*  Indicates if the resource has been allocated as persistent.           */
    /*------------------------------------------------------------------------*/
    1,
    /*------------------------------------------------------------------------*/
    /*  Obtain the static properties associated with this resource            */
    /*  This could include information like the register layer of the         */
    /*  device etc.                                                           */
    /*------------------------------------------------------------------------*/
    NULL
  },
  /*--------------------------------------------------------------------------*/
  /*   Void * info RSVD for future use                                        */
  /*--------------------------------------------------------------------------*/
  0,
  /*--------------------------------------------------------------------------*/
  /*  Void * memoryBaseAddress,            Allocated Memory base addr         */
  /*--------------------------------------------------------------------------*/
  NULL,

  /*--------------------------------------------------------------------------*/
  /*  Int  isTiledMemory                                                      */
  /*--------------------------------------------------------------------------*/
  0,

  /*--------------------------------------------------------------------------*/
  /* IRES_TILEDMEMORY_AccessUnit accessUnit                                   */
  /*--------------------------------------------------------------------------*/
  IRES_TILEDMEMORY_PAGE,

  /*--------------------------------------------------------------------------*/
  /*  Void * tilerBaseAddress              Static TILER MEMORY base addr      */
  /*--------------------------------------------------------------------------*/
  TILERBASEADDRESS,

  /*--------------------------------------------------------------------------*/
  /*  Void * systemSpaceBaseAddress        Static physical addr               */
  /* Kept NULL as codec is not using it, ideally it should be physical address*/
  /* of the tiled buffer to avoid MEMUTILS_getPhysicalAddr API                */
  /*--------------------------------------------------------------------------*/
  NULL
 }
};

/** 
********************************************************************************
 *  @fn     allignMalloc
 *  @brief  Memory allocate function with alignment
 *
 *  @param[in] alignment : alignment value
 *  
 *  @param[in] size : size of the buffer to be allocated in bytes
 *
 *  @return     Pointer to the allocated buffer
 *              Error in case allocation fails
********************************************************************************
*/
void *allignMalloc(size_t alignment, size_t size)
{
  void **mallocPtr;
  void **retPtr;
  /*--------------------------------------------------------------------------*/
  /* return if invalid size value                                             */
  /*--------------------------------------------------------------------------*/
  if (size <= 0) {
    return (0);
  }
  /*--------------------------------------------------------------------------*/
  /* If alignment is not a power of two, return what malloc returns. This is  */
  /* how memalign behaves on the c6x.                                         */
  /*--------------------------------------------------------------------------*/
  if((alignment & (alignment - 1)) || (alignment <= 1))
  {
    if((mallocPtr = malloc(size + sizeof(mallocPtr))) != NULL)
    {
      /*----------------------------------------------------------------------*/
      /* Very first pointer will hold the base address of the allocated memory*/
      /* This address will be use full for the freeing the buffer             */
      /*----------------------------------------------------------------------*/
      *mallocPtr = mallocPtr;
      mallocPtr++;
    }
    return((void *)mallocPtr);
  }
  /*--------------------------------------------------------------------------*/
  /* allocated block of memroy including alignment when the alignment is not  */
  /* power of 2                                                               */
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
 *  @fn     allignFree
 *  @brief  Funtion to free the memory allocated with "allignMalloc" fucntion
 *
 *  @param[in] ptr : pointer to the buffer free
 *  
 *  @return     None
********************************************************************************
*/
void allignFree(void *ptr)
{
  /*--------------------------------------------------------------------------*/
  /* Go to the previous pointer to check exact address of the buffer allocated*/
  /*--------------------------------------------------------------------------*/
  if(ptr != NULL)
  {
    free((void *)((void **)ptr)[-1]);
  }
}

/** 
********************************************************************************
 *  @fn     RMAN_AssignResources
 *  @brief  Funtion to assigne the HDVICP and Memory resources, This is dummy 
 *          implimentation to emulate exact RMAN module API
 *
 *  @param[in] handle : Pointer to the algorithm handle
 *  
 *  @return     IRES_Status : status of the resource assigment
 *
********************************************************************************
*/
IRES_Status RMAN_AssignResources(IALG_Handle handle, XDAS_Int8 lumaTilerSpace, 
                                 XDAS_Int8 chromaTilerSpace)
{
  /*--------------------------------------------------------------------------*/
  /* Pointers to the resource discriptor, protocal arguments of the HDVICP and*/
  /* tiledmemory resoures                                                     */
  /*--------------------------------------------------------------------------*/
  IRES_ResourceDescriptor       *resourceDescriptor;
   IRES_TILEDMEMORY_ProtocolArgs *tiledmemProtocolArgs;
   IRES_HDVICP2_ProtocolArgs     *hdvicp2ProtocolArgs;

  Int32          numResources;
  IRES_Status retVal;
   IRES_YieldFxn     yieldFxn   = 0;      /* acquired from RMAN during init */
  IRES_YieldArgs    yieldArgs  = 0;     /* acquired from RMAN during init */
  Int32 index;
  /*--------------------------------------------------------------------------*/
  /* reset global flag to zero which tells assigment status                   */
  /*--------------------------------------------------------------------------*/
  isAcquireCallMade = 0;
  /*--------------------------------------------------------------------------*/
  /* Call codec api function to get number of resources required for algorithm*/
  /*--------------------------------------------------------------------------*/
  numResources = H264ENC_TI_IRES.numResourceDescriptors(handle);

  numResourcesBackUp = numResources;  
  /*--------------------------------------------------------------------------*/
  /* Allogate memory for the resource instances                               */
  /*--------------------------------------------------------------------------*/
   resourceDescriptor = 
           (IRES_ResourceDescriptor *)malloc(IRES_TOTAL_RESOURCES * 
                                               sizeof(IRES_ResourceDescriptor));

  printf("Number of Resources required = %d\n", numResources);
  /*--------------------------------------------------------------------------*/
  /* Get properties of the resource with help codec API function              */
  /*--------------------------------------------------------------------------*/
  retVal = H264ENC_TI_IRES.getResourceDescriptors(handle, resourceDescriptor);
  if (retVal != IRES_OK)
  {
    printf("Error in Get Resource Descriptor \n");
    return retVal;
  }
  /*--------------------------------------------------------------------------*/
  /* assign default HDVICP resource handle pointer to the resource discriptor */
  /* hadle                                                                    */
  /*--------------------------------------------------------------------------*/
   resourceDescriptor[IRES_HDVICP_RESOURCE_IVAHD_0].handle = 
                                               (IRES_Obj *)&IRES_HDVICP2_handle;
  gHDVICP2Handle =  (IRES_HDVICP2_Handle)&IRES_HDVICP2_handle ;                                            
  /*--------------------------------------------------------------------------*/
  /* Assigne default memory resource handles all memory resource discriptors  */
  /*--------------------------------------------------------------------------*/
  resourceDescriptor[IRES_TILED_MEMORY_2D_RESOURCE_LUMA_0].handle =
                                (IRES_Obj *)&IRES_TILEDMEMORY_luma1[insChanid];
  resourceDescriptor[IRES_TILED_MEMORY_2D_RESOURCE_LUMA_1 ].handle =
                                (IRES_Obj *)&IRES_TILEDMEMORY_luma2[insChanid];
  resourceDescriptor[IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_0].handle =
                              (IRES_Obj *)&IRES_TILEDMEMORY_chroma1[insChanid];
  resourceDescriptor[IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_1].handle =
                              (IRES_Obj *)&IRES_TILEDMEMORY_chroma2[insChanid];
  if(numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_2)

  {
    resourceDescriptor[IRES_TILED_MEMORY_2D_RESOURCE_LUMA_2 ].handle =
                                (IRES_Obj *)&IRES_TILEDMEMORY_luma3[insChanid];
    resourceDescriptor[IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_2].handle =
                              (IRES_Obj *)&IRES_TILEDMEMORY_chroma3[insChanid];
  }
  if(numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_3)
  {
    resourceDescriptor[IRES_TILED_MEMORY_2D_RESOURCE_LUMA_3 ].handle = 
                                 (IRES_Obj *)&IRES_TILEDMEMORY_luma4[insChanid];
    resourceDescriptor[IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_3].handle = 
                               (IRES_Obj *)&IRES_TILEDMEMORY_chroma4[insChanid];
  } 
  if(numResources == IRES_TOTAL_RESOURCES)
  {
    resourceDescriptor[IRES_TILED_MEMORY_2D_RESOURCE_LUMA_4 ].handle = 
                                 (IRES_Obj *)&IRES_TILEDMEMORY_luma5[insChanid];
    resourceDescriptor[IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_4].handle = 
                               (IRES_Obj *)&IRES_TILEDMEMORY_chroma5[insChanid];
  }
  
  resourceDescriptor[IRES_TILED_MEMORY_1D_RESOURCE_COL_MBINFO].handle =
                           (IRES_Obj *)&IRES_TILEDMEMORY_coloMBInfo[insChanid];
  resourceDescriptor[IRES_TILED_MEMORY_1D_RESOURCE_ROI_INFO].handle =
                           (IRES_Obj *)&IRES_TILEDMEMORY_roiInfo[insChanid];
  resourceDescriptor[IRES_TILED_MEMORY_1D_RESOURCE_PERSISTENT_MEM].handle =
                     (IRES_Obj *)&IRES_TILEDMEMORY_persistentMemory[insChanid];
  resourceDescriptor[IRES_TILED_MEMORY_1D_RESOURCE_DEBUGTRACE_MEM].handle =
                     (IRES_Obj *)&IRES_TILEDMEMORY_debugTraceMemory[insChanid];
  /*--------------------------------------------------------------------------*/
  /* Update HDVICP resource handle                                            */
  /*--------------------------------------------------------------------------*/
  hdvicp2ProtocolArgs  =
             (IRES_HDVICP2_ProtocolArgs*)resourceDescriptor
                                    [IRES_HDVICP_RESOURCE_IVAHD_0].protocolArgs;
  IRES_HDVICP2_handle.id = hdvicp2ProtocolArgs->id;
  /*--------------------------------------------------------------------------*/
  /* Allocate memory in tiler space.                                          */
  /*--------------------------------------------------------------------------*/
  if(numResources > IRES_TILED_MEMORY_1D_RESOURCE_MAX)
  {
    /*------------------------------------------------------------------------*/
    /* 'B' frames supported with tiler enabled cases are less than or equal   */
    /* to 4. Tiler Buffers 0,2,4,6 are used to store captured data(YUV) and   */
    /* hence buffer numbered with 8,10,12 etc are used to store reference     */
    /* (recon) data. Same logic applies for chroma buffers too.               */
    /*------------------------------------------------------------------------*/
    /* In Multi-Channel sceanrio only 4 channels are supported with tiled     */
    /* enabled cases. Luma buffers 0,2,4... 14 are used to store captured(YUV)*/
    /* data and hence buffers numbered 16,18... are used to reference data.   */
    /* same logic applies to chroma buffers also. And note that 'B' frames    */
    /* are not supported in multi-channel scenario.                           */
    /*------------------------------------------------------------------------*/
    if(lumaTilerSpace)
    {
      IRES_TILEDMEMORY_luma1[insChanid].memoryBaseAddress =
                     (Void *)TilerParams.tiledBufferAddr[(inschan > 1) ? 
                                                  (16 + (4*insChanid)) :  8 ] ;
      IRES_TILEDMEMORY_luma2[insChanid].memoryBaseAddress =
                     (Void *)TilerParams.tiledBufferAddr[(inschan > 1) ? 
                                                  (18 + (4*insChanid)) : 10 ] ;
      IRES_TILEDMEMORY_luma1[insChanid].isTiledMemory = 1;
      IRES_TILEDMEMORY_luma2[insChanid].isTiledMemory = 1;
       if(numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_2)

      {
        IRES_TILEDMEMORY_luma3[insChanid].memoryBaseAddress =
                     (Void *)TilerParams.tiledBufferAddr[(inschan > 1) ? 
                                                  (20 + (4*insChanid)) : 12 ] ;
        IRES_TILEDMEMORY_luma3[insChanid].isTiledMemory = 1;
      }
      if(numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_3)
      {
        IRES_TILEDMEMORY_luma4[insChanid].memoryBaseAddress = 
                     (Void *)TilerParams.tiledBufferAddr[(inschan > 1) ? 
                                                  (22 + (4*insChanid)) : 14 ] ;
        IRES_TILEDMEMORY_luma4[insChanid].isTiledMemory = 1;
      }
      if(numResources == IRES_TOTAL_RESOURCES)
      {
        IRES_TILEDMEMORY_luma5[insChanid].memoryBaseAddress =
                     (Void *)TilerParams.tiledBufferAddr[(inschan > 1) ?
                                                 (24 + (4*insChanid)) : 16 ] ;
        IRES_TILEDMEMORY_luma5[insChanid].isTiledMemory = 1;
      }
    

    }
    else
    {
    tiledmemProtocolArgs =
             (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                            [IRES_TILED_MEMORY_2D_RESOURCE_LUMA_0].protocolArgs;
    IRES_TILEDMEMORY_luma1[insChanid].memoryBaseAddress =
             (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
             (tiledmemProtocolArgs->sizeDim0 * tiledmemProtocolArgs->sizeDim1 *
              sizeof(XDAS_UInt8)));
    IRES_TILEDMEMORY_luma1[insChanid].isTiledMemory = 0;


    tiledmemProtocolArgs =
             (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                            [IRES_TILED_MEMORY_2D_RESOURCE_LUMA_1].protocolArgs;
    IRES_TILEDMEMORY_luma2[insChanid].memoryBaseAddress =
             (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
             (tiledmemProtocolArgs->sizeDim0 * tiledmemProtocolArgs->sizeDim1 *
             sizeof(XDAS_UInt8)));
    IRES_TILEDMEMORY_luma2[insChanid].isTiledMemory = 0;

      if(numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_2)
    {
      tiledmemProtocolArgs =
               (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                            [IRES_TILED_MEMORY_2D_RESOURCE_LUMA_2].protocolArgs;
      IRES_TILEDMEMORY_luma3[insChanid].memoryBaseAddress =
              (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
              (tiledmemProtocolArgs->sizeDim0 * tiledmemProtocolArgs->sizeDim1 *
                sizeof(XDAS_UInt8)));
      IRES_TILEDMEMORY_luma3[insChanid].isTiledMemory = 0;
    }
      if(numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_3)
      {
        tiledmemProtocolArgs = 
                 (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                            [IRES_TILED_MEMORY_2D_RESOURCE_LUMA_3].protocolArgs;
        IRES_TILEDMEMORY_luma4[insChanid].memoryBaseAddress = 
             (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
             (tiledmemProtocolArgs->sizeDim0 * tiledmemProtocolArgs->sizeDim1 *
                  sizeof(XDAS_UInt8)));
        IRES_TILEDMEMORY_luma4[insChanid].isTiledMemory = 0;
      }
      if(numResources == IRES_TOTAL_RESOURCES)
      {
        tiledmemProtocolArgs = 
                 (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                            [IRES_TILED_MEMORY_2D_RESOURCE_LUMA_4].protocolArgs;
        IRES_TILEDMEMORY_luma5[insChanid].memoryBaseAddress = 
             (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
             (tiledmemProtocolArgs->sizeDim0 * tiledmemProtocolArgs->sizeDim1 *
                  sizeof(XDAS_UInt8)));
        IRES_TILEDMEMORY_luma5[insChanid].isTiledMemory = 0;
      }
    }
    if(chromaTilerSpace)
    {
      IRES_TILEDMEMORY_chroma1[insChanid].memoryBaseAddress =
                     (Void *)TilerParams.tiledBufferAddr[(inschan > 1) ? 
                                                  (17 + (4*insChanid)) :  9 ] ;
      IRES_TILEDMEMORY_chroma2[insChanid].memoryBaseAddress =
                     (Void *)TilerParams.tiledBufferAddr[(inschan > 1) ? 
                                                  (19 + (4*insChanid)) : 11 ] ;
      IRES_TILEDMEMORY_chroma1[insChanid].isTiledMemory = 1;
      IRES_TILEDMEMORY_chroma2[insChanid].isTiledMemory = 1;

      if(chromaTilerSpace == XDM_MEMTYPE_TILED8)
      {
        IRES_TILEDMEMORY_chroma1[insChanid].accessUnit = IRES_TILEDMEMORY_8BIT ;
        IRES_TILEDMEMORY_chroma2[insChanid].accessUnit = IRES_TILEDMEMORY_8BIT ;

      }
      else if(chromaTilerSpace == XDM_MEMTYPE_TILED16)
      {
        IRES_TILEDMEMORY_chroma1[insChanid].accessUnit = IRES_TILEDMEMORY_16BIT;
        IRES_TILEDMEMORY_chroma2[insChanid].accessUnit = IRES_TILEDMEMORY_16BIT;
      }
      if(numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_2)
      {
        IRES_TILEDMEMORY_chroma3[insChanid].memoryBaseAddress =
                     (Void *)TilerParams.tiledBufferAddr[(inschan > 1) ? 
                                                   (21 + (4*insChanid)) : 13 ] ;
        IRES_TILEDMEMORY_chroma3[insChanid].isTiledMemory = 1;
        if(chromaTilerSpace == XDM_MEMTYPE_TILED8)
        {
          IRES_TILEDMEMORY_chroma3[insChanid].accessUnit = 
                                                         IRES_TILEDMEMORY_8BIT ;
        }
        else if(chromaTilerSpace == XDM_MEMTYPE_TILED16)
        {
          IRES_TILEDMEMORY_chroma3[insChanid].accessUnit = 
                                                        IRES_TILEDMEMORY_16BIT ;
        }
      }
      if(numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_3)
      {
        IRES_TILEDMEMORY_chroma4[insChanid].memoryBaseAddress =
                     (Void *)TilerParams.tiledBufferAddr[(inschan > 1) ?
                                                   (23 + (4*insChanid)) : 15 ] ;
        IRES_TILEDMEMORY_chroma4[insChanid].isTiledMemory = 1;

        if(chromaTilerSpace == XDM_MEMTYPE_TILED8)
        {
          IRES_TILEDMEMORY_chroma4[insChanid].accessUnit =
                                                        IRES_TILEDMEMORY_8BIT ;
        }
        else if(chromaTilerSpace == XDM_MEMTYPE_TILED16)
        {
          IRES_TILEDMEMORY_chroma4[insChanid].accessUnit =
                                                        IRES_TILEDMEMORY_16BIT ;
        }
      }
      if(numResources == IRES_TOTAL_RESOURCES)
      {
        IRES_TILEDMEMORY_chroma5[insChanid].memoryBaseAddress =
                     (Void *)TilerParams.tiledBufferAddr[(inschan > 1) ? 
                                                  (25 + (4*insChanid)) : 17 ] ;
        IRES_TILEDMEMORY_chroma5[insChanid].isTiledMemory = 1;

        if(chromaTilerSpace == XDM_MEMTYPE_TILED8)
        {
          IRES_TILEDMEMORY_chroma5[insChanid].accessUnit =
                                                        IRES_TILEDMEMORY_8BIT ;
        }
        else if(chromaTilerSpace == XDM_MEMTYPE_TILED16)
        {
          IRES_TILEDMEMORY_chroma5[insChanid].accessUnit =
                                                       IRES_TILEDMEMORY_16BIT ;
        }
      }
    }
    else
    {

      tiledmemProtocolArgs =
               (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                         [IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_0].protocolArgs;
      IRES_TILEDMEMORY_chroma1[insChanid].memoryBaseAddress =
              (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
              (tiledmemProtocolArgs->sizeDim0 * tiledmemProtocolArgs->sizeDim1 *
               sizeof(XDAS_UInt8)));
      IRES_TILEDMEMORY_chroma1[insChanid].isTiledMemory = 0;
      tiledmemProtocolArgs =
               (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                          [IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_1].protocolArgs;
      IRES_TILEDMEMORY_chroma2[insChanid].memoryBaseAddress =
              (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
              (tiledmemProtocolArgs->sizeDim0 * tiledmemProtocolArgs->sizeDim1 *
               sizeof(XDAS_UInt8)));
      IRES_TILEDMEMORY_chroma2[insChanid].isTiledMemory = 0;

      if(numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_2)

      {
        tiledmemProtocolArgs =
                 (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                          [IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_2].protocolArgs;
        IRES_TILEDMEMORY_chroma3[insChanid].memoryBaseAddress =
              (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
              (tiledmemProtocolArgs->sizeDim0 * tiledmemProtocolArgs->sizeDim1 *
              sizeof(XDAS_UInt8)));
        IRES_TILEDMEMORY_chroma3[insChanid].isTiledMemory = 0;
      }
      if(numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_3)
      {
        tiledmemProtocolArgs = 
                 (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                          [IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_3].protocolArgs;
        IRES_TILEDMEMORY_chroma4[insChanid].memoryBaseAddress = 
              (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
              (tiledmemProtocolArgs->sizeDim0 * tiledmemProtocolArgs->sizeDim1 *
                 sizeof(XDAS_UInt8)));
        IRES_TILEDMEMORY_chroma4[insChanid].isTiledMemory = 0;
      }      
      if(numResources == IRES_TOTAL_RESOURCES)
      {
        tiledmemProtocolArgs = 
                 (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                          [IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_4].protocolArgs;
        IRES_TILEDMEMORY_chroma5[insChanid].memoryBaseAddress = 
              (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
              (tiledmemProtocolArgs->sizeDim0 * tiledmemProtocolArgs->sizeDim1 *
                 sizeof(XDAS_UInt8)));
        IRES_TILEDMEMORY_chroma5[insChanid].isTiledMemory = 0;
      }
     }
   }
   
   tiledmemProtocolArgs = 
             (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                        [IRES_TILED_MEMORY_1D_RESOURCE_COL_MBINFO].protocolArgs;
   IRES_TILEDMEMORY_coloMBInfo[insChanid].memoryBaseAddress =
             (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
                         (tiledmemProtocolArgs->sizeDim0 * sizeof(XDAS_UInt8)));
   tiledmemProtocolArgs =
             (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                    [IRES_TILED_MEMORY_1D_RESOURCE_ROI_INFO].protocolArgs;
   IRES_TILEDMEMORY_roiInfo[insChanid].memoryBaseAddress =
             (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
                         (tiledmemProtocolArgs->sizeDim0 * sizeof(XDAS_UInt8)));
   tiledmemProtocolArgs =
             (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                    [IRES_TILED_MEMORY_1D_RESOURCE_PERSISTENT_MEM].protocolArgs;
   IRES_TILEDMEMORY_persistentMemory[insChanid].memoryBaseAddress =
             (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
                         (tiledmemProtocolArgs->sizeDim0 * sizeof(XDAS_UInt8)));
   tiledmemProtocolArgs =
             (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                    [IRES_TILED_MEMORY_1D_RESOURCE_DEBUGTRACE_MEM].protocolArgs;
   IRES_TILEDMEMORY_debugTraceMemory[insChanid].memoryBaseAddress =
             (Void *)allignMalloc(tiledmemProtocolArgs->alignment,
                         (tiledmemProtocolArgs->sizeDim0 * sizeof(XDAS_UInt8)));

  /*--------------------------------------------------------------------------*/
  /* Back up the protocol Args requested by the codec.                        */
  /* Later use this to check that same is requested during during             */
  /* RMAN_FreeResources()                                                     */
  /*--------------------------------------------------------------------------*/
  for(index = 1; index < numResources; index++)
  {
    memcpy(&protocolArgsBackUp[insChanid][index],
                                       resourceDescriptor[index].protocolArgs, 
                                       sizeof (IRES_TILEDMEMORY_ProtocolArgs));
  }
  /*--------------------------------------------------------------------------*/
  /* Codec API function init resources                                        */
  /*--------------------------------------------------------------------------*/
  retVal = H264ENC_TI_IRES.initResources(handle, resourceDescriptor,
                                                           yieldFxn, yieldArgs);
  if (retVal != IRES_OK)
  {
    printf("Error in Init Resources \n");
    return retVal;
  }
  /*--------------------------------------------------------------------------*/
  /* Free the memory allocated for the discriptor instances                   */
  /*--------------------------------------------------------------------------*/
  free(resourceDescriptor);
  return  IRES_OK;
}

/** 
********************************************************************************
 *  @fn     RMAN_activateAllResources
 *  @brief  Funtion to activate all the resources
 *          This fucntion intern calls algorithm call back function to activate
 *          all the resources
 *
 *  @param[in] handle : Pointer to the algorithm handle
 *  
 *  @return     Status of the activation
 *
********************************************************************************
*/
XDAS_UInt32 RMAN_activateAllResources (IALG_Handle handle)
{
  /*--------------------------------------------------------------------------*/
  /* call to the codec activate function                                      */
  /*--------------------------------------------------------------------------*/
  return (H264ENC_TI_IRES.activateAllResources(handle));

}


/** 
********************************************************************************
 *  @fn     RMAN_deactivateAllResources
 *  @brief  Funtion to deactivate all the resources
 *          This fucntion intern calls algorithm call back function to 
 *          deactivate all the resources
 *
 *  @param[in] handle : Pointer to the algorithm handle
 *  
 *  @return     Status of the activation
 *
********************************************************************************
*/
XDAS_UInt32 RMAN_deactivateAllResources (IALG_Handle handle)
{
  /*--------------------------------------------------------------------------*/
  /* call to the codec deactivate function                                    */
  /*--------------------------------------------------------------------------*/
  return (H264ENC_TI_IRES.deactivateAllResources(handle));
} 

/** 
********************************************************************************
 *  @fn     RMAN_activateHDVICP2Resource
 *  @brief  Funtion to activate HDVICP2 resource
 *          This fucntion intern calls algorithm call back function to activate
 *          HDVICP2 resource
 *
 *  @param[in] handle : Pointer to the algorithm handle
 *  
 *  @param[in] resourceHandle : Pointer to the HDVICP2 handle
 * 
 *  @return     Status of the activation
 *
********************************************************************************
*/
XDAS_UInt32 RMAN_activateHDVICP2Resource (IALG_Handle handle,
  IRES_Handle resourceHandle)
 {
    return (H264ENC_TI_IRES.activateResource(handle, resourceHandle));
 }

/** 
********************************************************************************
 *  @fn     RMAN_deactivateHDVICP2Resource
 *  @brief  Funtion to deactivate HDVICP2 resource
 *          This fucntion intern calls algorithm call back function to 
 *          deactivate HDVICP2 resource
 *
 *  @param[in] handle : Pointer to the algorithm handle
 *  
 *  @param[in] resourceHandle : Pointer to the HDVICP2 handle
 *  
 *  @return     Status of the deactivation
 *
********************************************************************************
*/
XDAS_UInt32 RMAN_deactivateHDVICP2Resource (IALG_Handle handle, 
  IRES_Handle resourceHandle)
{
  return (H264ENC_TI_IRES.deactivateResource(handle, resourceHandle));
}

/** 
********************************************************************************
 *  @fn     RMAN_FreeResources
 *  @brief  Funtion to free the resources allocated
 *          This fucntion basically frees all the memory allocated for memory
 *          resources
 *
 *  @param[in] handle : Pointer to the algorithm handle
 *  
 *  @return     None
 *
********************************************************************************
*/
void RMAN_FreeResources(IALG_Handle handle)
{
  Int32 numResources;
  Int32 index;
  IRES_ResourceDescriptor       *resourceDescriptor;
  IRES_Status retVal;  
  /*--------------------------------------------------------------------------*/
  /* Find out number of resources allocated by calling codec api function     */
  /*--------------------------------------------------------------------------*/
  numResources = H264ENC_TI_IRES.numResourceDescriptors(handle);

  if(numResources != numResourcesBackUp)
  {
    fprintf(stdout, "Err: Number of Resources requsted changed during Free\n",
           numResources); 
  }

  /*--------------------------------------------------------------------------*/
  /* Allogate memory for the resource instances                               */
  /*--------------------------------------------------------------------------*/
   resourceDescriptor = 
           (IRES_ResourceDescriptor *)malloc(IRES_TOTAL_RESOURCES * 
                                               sizeof(IRES_ResourceDescriptor));

  /*--------------------------------------------------------------------------*/
  /* Get properties of the resource with help codec API function              */
  /*--------------------------------------------------------------------------*/
  retVal = H264ENC_TI_IRES.getResourceDescriptors(handle, resourceDescriptor);
  if (retVal != IRES_OK)
  {
    printf("Error in Get Reosource Descriptor \n");
  }

  /*--------------------------------------------------------------------------*/
  /* Free the allocated memory resources                                      */
  /*--------------------------------------------------------------------------*/
  if(numResources > IRES_TILED_MEMORY_1D_RESOURCE_MAX)
  {
    if(IRES_TILEDMEMORY_luma1[insChanid].isTiledMemory == 0)
    {
    allignFree(IRES_TILEDMEMORY_luma1[insChanid].memoryBaseAddress);
    }
    if(IRES_TILEDMEMORY_luma2[insChanid].isTiledMemory == 0)
    {
    allignFree(IRES_TILEDMEMORY_luma2[insChanid].memoryBaseAddress);
    }
    if(IRES_TILEDMEMORY_chroma1[insChanid].isTiledMemory == 0)
    {
    allignFree(IRES_TILEDMEMORY_chroma1[insChanid].memoryBaseAddress);
    }
    if(IRES_TILEDMEMORY_chroma2[insChanid].isTiledMemory == 0)
    {
    allignFree(IRES_TILEDMEMORY_chroma2[insChanid].memoryBaseAddress);
  }
  }
  if(IRES_TILEDMEMORY_coloMBInfo[insChanid].isTiledMemory == 0)
  {
    allignFree(IRES_TILEDMEMORY_coloMBInfo[insChanid].memoryBaseAddress);
  }
  if(IRES_TILEDMEMORY_roiInfo[insChanid].isTiledMemory == 0)
  {
    allignFree(IRES_TILEDMEMORY_roiInfo[insChanid].memoryBaseAddress);
  }
  if(IRES_TILEDMEMORY_persistentMemory[insChanid].isTiledMemory == 0)
  {
    allignFree(IRES_TILEDMEMORY_persistentMemory[insChanid].memoryBaseAddress);
  }
  if(IRES_TILEDMEMORY_debugTraceMemory[insChanid].isTiledMemory == 0)
  {
    allignFree(IRES_TILEDMEMORY_debugTraceMemory[insChanid].memoryBaseAddress);
  }
  /*--------------------------------------------------------------------------*/
  /* Check for the extra allocated memory resource                            */
  /*--------------------------------------------------------------------------*/
   if (numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_2)

   {
    if(IRES_TILEDMEMORY_luma3[insChanid].isTiledMemory == 0)
    {
      allignFree(IRES_TILEDMEMORY_luma3[insChanid].memoryBaseAddress);
    }
    if(IRES_TILEDMEMORY_chroma3[insChanid].isTiledMemory == 0)
    {
      allignFree(IRES_TILEDMEMORY_chroma3[insChanid].memoryBaseAddress);
    }
   }
  if (numResources > IRES_TILED_MEMORY_2D_RESOURCE_LUMA_3)
   {
    if(IRES_TILEDMEMORY_luma4[insChanid].isTiledMemory == 0)
    {
      allignFree(IRES_TILEDMEMORY_luma4[insChanid].memoryBaseAddress);
    }
    if(IRES_TILEDMEMORY_chroma4[insChanid].isTiledMemory == 0)
    {
      allignFree(IRES_TILEDMEMORY_chroma4[insChanid].memoryBaseAddress);
    }
   }
  if (numResources == IRES_TOTAL_RESOURCES)
   {
    if(IRES_TILEDMEMORY_luma5[insChanid].isTiledMemory == 0)
    {
      allignFree(IRES_TILEDMEMORY_luma5[insChanid].memoryBaseAddress);
    }
    if(IRES_TILEDMEMORY_chroma5[insChanid].isTiledMemory == 0)
    {
      allignFree(IRES_TILEDMEMORY_chroma5[insChanid].memoryBaseAddress);
    }
   }


  for(index = 1; index < numResources; index++)
  {

    /*------------------------------------------------------------------------*/
    /* Chk that same protocol Args are reported again. Otherwise flag an      */
    /* error.                                                                 */
    /*------------------------------------------------------------------------*/
    if(memcmp(&protocolArgsBackUp[insChanid][index], 
            resourceDescriptor[index].protocolArgs,
              sizeof (IRES_TILEDMEMORY_ProtocolArgs)))
    {
       fprintf(stdout, "Err: Protocol Args requested changed for idx = %d \n",
                        (index+1));
    }
  }
  /*--------------------------------------------------------------------------*/
  /* Free the memory allocated for the discriptor instances                   */
  /*--------------------------------------------------------------------------*/
  free(resourceDescriptor);

}
/*---------------------------------------------------------------------*/
/* This rotuien is a call back implementation on behalf of application */
/* to provide bit-stream in chunk of DATA_SYNCH_UNIT bytes unit        */
/*---------------------------------------------------------------------*/
/** 
********************************************************************************
 *  @fn     H264ETest_DataSyncPutDataFxn
 *  @brief  Funtion to initialize the Bitsream and size information of every 
 *          chunk of bitstream from put data synch descriptor
 *
 *  @param[in] dataSyncHandle : pointer to the datasync handle
 *  
 *  @param[in] dataSyncDesc : pointer to the datasync discriptors
 *
 *  @return     0 : when no error
 *             -1 : in case of errors
 *
********************************************************************************
*/

Void H264ETest_DataSyncPutDataFxn(XDM_DataSyncHandle dataSyncHandle, 
                                  XDM_DataSyncDesc *dataSyncDesc)
{
  XDAS_Int32 i;
  XDAS_Int32 j;  
  for(i=0, j = 0; i<dataSyncDesc->numBlocks; i++)
  {
    gBlockSizes[gOutputBlocksRecieved]    =  dataSyncDesc->blockSizes[j];
    if(dataSyncDesc->scatteredBlocksFlag != 0)
    {
      gBlockAddr[gOutputBlocksRecieved]   = dataSyncDesc->baseAddr[i]   ;
    }
    else
    {
      if(i == 0)
      {  
        gBlockAddr[gOutputBlocksRecieved] = (XDAS_Int32)dataSyncDesc->baseAddr;
      }
      else
      {
        gBlockAddr[gOutputBlocksRecieved] = 
                                    gBlockAddr[gOutputBlocksRecieved - 1] +
                                            gBlockSizes[gOutputBlocksRecieved];
      }
    }
    gOutputBlocksRecieved++;

    /*------------------------------------------------------------------------*/
    /* Debug code to catch if memory is not available to write the            */
    /* block address and block sizes                                          */
    /*------------------------------------------------------------------------*/
    if(gOutputBlocksRecieved == TOT_BLOCKS_IN_PROCESS)
    {    
      while(1);
    }

    if(dataSyncDesc->varBlockSizesFlag != 0)
    {
     j++;
    }
  }
  gBlockSizes[gOutputBlocksRecieved]    =  
                              dataSyncDesc->blockSizes[dataSyncDesc->numBlocks];
}

/** 
********************************************************************************
 *  @fn     H264ETest_DataSyncGetBufFxn
 *  @brief  Funtion to initialize the data sync module
 *
 *  @param[in] dataSyncHandle : pointer to the datasync handle
 *  
 *  @param[in] dataSyncDesc : pointer to the datasync discriptors
 *
 *  @return     0 : when no error
 *             -1 : in case of errors
 *
********************************************************************************
*/
XDAS_Int32 H264ETest_DataSyncGetBufFxn(XDM_DataSyncHandle dataSyncHandle, 
        XDM_DataSyncDesc *dataSyncDesc)
{
  XDAS_Int32 i;  
  static XDAS_Int32 block_count = 0;
  XDAS_Int32 dataSyncUnitSize   = gDataSynchUnit + gDataSyncUnitGap;
  
  /*--------------------------------------------------------------------------*/
  /* TODO : need to add comments                                              */
  /*--------------------------------------------------------------------------*/
#ifdef PROVIDE_ONE_BUFFER
  dataSyncDesc->numBlocks           = 1;
  dataSyncDesc->scatteredBlocksFlag = 0;
  dataSyncDesc->varBlockSizesFlag   = 0;
#else  
  dataSyncDesc->numBlocks           = block_count;
  dataSyncDesc->scatteredBlocksFlag = (dataSyncDesc->numBlocks & 0x1) || 
                                      (gDataSyncUnitGap != 0);
  dataSyncDesc->varBlockSizesFlag   = dataSyncDesc->numBlocks & 0x1;
#endif

  for(i = 0; i < dataSyncDesc->numBlocks; i++)
  { 
   blockSizeArray[i] = gDataSynchUnit;
  }

  if(dataSyncDesc->scatteredBlocksFlag == 0)
  {
    dataSyncDesc->baseAddr          = 
                              (XDAS_Int32 *)(gOutputData + gOutputDataProvided);
  }
  else
  {

    dataSyncDesc->baseAddr            = (XDAS_Int32*) blockAddrArray;
    for(i = 0; i < dataSyncDesc->numBlocks; i++)
    {
      blockAddrArray[i]               = (XDAS_Int32)(gOutputData         + 
                                                   gOutputDataProvided + 
                                                   i*dataSyncUnitSize
                                                  );
    }
  }
  dataSyncDesc->blockSizes       = (XDAS_Int32*) blockSizeArray;
  gOutputDataProvided           += (dataSyncDesc->numBlocks * dataSyncUnitSize);
  if(block_count == NUM_BLOCKS)
  {
    block_count = 0;
  }
  else  
  {
    block_count++;
  }
  if(gOutputDataProvided > OUTPUT_BUFFER_SIZE)
  {
    return (-1);   
  }
  else
  {
    return (0);   
  }
}

/** 
********************************************************************************
 *  @fn     H264ETest_DataSyncGetDataFxn1
 *  @brief  Funtion to Give fill buffer pointer details to the input YUV buufer
 *
 *
 *  @param[in] dataSyncHandle : pointer to the datasync handle
 *  
 *  @param[in] dataSyncDesc : pointer to the datasync discriptors
 *
 *  @return     0 : when no error
 *             -1 : in case of errors
 *
********************************************************************************
*/
XDAS_Int32 H264ETest_DataSyncGetDataFxn1(XDM_DataSyncHandle dataSyncHandle, 
        XDM_DataSyncDesc *dataSyncDesc)
{
  static XDAS_Int32 block_count = 0; 
  
  /*--------------------------------------------------------------------------*/
  /* Check whether the handle provided is proper or not, even though we are   */
  /* not using just to check codec make sure it provides proper handle        */
  /*--------------------------------------------------------------------------*/
  if(dataSyncHandle != fGetInpDHandle1)
  {
    printf("Error wrong Data sync handle \n");
    exit(-1);
  }
  /*--------------------------------------------------------------------------*/
  /* It is assumed that base address for each block is continues and codec    */
  /* will not work if it is changed due to some other restrictions            */
  /*--------------------------------------------------------------------------*/
  dataSyncDesc->baseAddr          = NULL;
  dataSyncDesc->numBlocks         = gConfigOrg.numBlocks[block_count];
  dataSyncDesc->varBlockSizesFlag = 1;
  dataSyncDesc->blockSizes        = (XDAS_Int32*)Input_BlockSizeArray;
  /*--------------------------------------------------------------------------*/
  /* When number of blocks reaches 10 just give NULL pointer to check error   */
  /* robust ness                                                              */
  /*--------------------------------------------------------------------------*/
  if(block_count == 5)
  {
    dataSyncDesc->blockSizes        = (XDAS_Int32*)NULL;
  }
  /*--------------------------------------------------------------------------*/
  /* Incriment the num of block count to test variable number of blocks and   */
  /* sizes                                                                    */
  /*--------------------------------------------------------------------------*/
  block_count++;
  block_count &= 0x7;
  return (0);  
}

/** 
********************************************************************************
 *  @fn     H264ETest_DataSyncGetDataFxn2
 *  @brief  Funtion to Give fill buffer pointer details to the input YUV buufer
 *          
 *
 *  @param[in] dataSyncHandle : pointer to the datasync handle
 *  
 *  @param[in] dataSyncDesc : pointer to the datasync discriptors
 *
 *  @return     0 : when no error
 *             -1 : in case of errors
 *
********************************************************************************
*/
XDAS_Int32 H264ETest_DataSyncGetDataFxn2(XDM_DataSyncHandle dataSyncHandle, 
        XDM_DataSyncDesc *dataSyncDesc)
{
  static XDAS_Int32 block_count = 0; 
  
  /*--------------------------------------------------------------------------*/
  /* Check whether the handle provided is proper or not, even though we are   */
  /* not using just to check codec make sure it provides proper handle        */
  /*--------------------------------------------------------------------------*/
  if(dataSyncHandle != fGetInpDHandle2)
  {
    return -1;
  }
  /*--------------------------------------------------------------------------*/
  /* It is assumed that base address for each block is continues and codec    */
  /* will not work if it is changed due to some other restrictions            */
  /*--------------------------------------------------------------------------*/
  dataSyncDesc->baseAddr          = NULL;
  dataSyncDesc->numBlocks         = gConfigOrg.numBlocks[block_count];
  dataSyncDesc->varBlockSizesFlag = 0;
  dataSyncDesc->blockSizes        = (XDAS_Int32*)Input_BlockSizeArray;
  /*--------------------------------------------------------------------------*/
  /* When number of blocks reaches 10 just give NULL pointer to check error   */
  /* robust ness                                                              */
  /*--------------------------------------------------------------------------*/
  if(block_count == 5)
  {
    dataSyncDesc->blockSizes        = (XDAS_Int32*)NULL;
  }
  /*--------------------------------------------------------------------------*/
  /* Incriment the num of block count to test variable number of blocks and   */
  /* sizes                                                                    */
  /*--------------------------------------------------------------------------*/
  block_count++;
  block_count &= 0x7;
  return (0);  
}
/** 
********************************************************************************
 *  @fn     MEMUTILS_getPhysicalAddr
 *  @brief  Funtion to get physical address of DDR memory
 *
 *  @param[in] addr : pointer to the address to get corresponding physical mem
 *  
 *  @return     Pointer to the physical memory
 *
********************************************************************************
*/
Void *MEMUTILS_getPhysicalAddr(Ptr Addr)
{
#if defined(A9_HOST_FILE_IO) && defined(OMAP4)
  Uint32 temp1;

  if(((Uint32)Addr<(0x0+0x4000))){
   temp1= ((Uint32)Addr+0x9d000000);                       
  }else if(((Uint32)Addr>=0x4000)&&((Uint32)Addr<(0x4000+0x1fc000))){
   temp1= ((Uint32)Addr - 0x4000 + 0x9d004000);
  }else if(((Uint32)Addr>=0x200000)&&((Uint32)Addr<(0x200000+0x600000))){
   temp1= ((Uint32)Addr - 0x200000 + 0x9d200000);
  }else if(((Uint32)Addr>=0x800000)&&((Uint32)Addr<(0x800000+0x200000))){
   temp1= ((Uint32)Addr - 0x800000 + 0x9d800000);
  }else if(((Uint32)Addr>=0xa00000)&&((Uint32)Addr<(0xa00000+0x600000))){
   temp1= ((Uint32)Addr - 0xa00000 + 0x9da00000);

  }else if(((Uint32)Addr>=0x80000000)&&((Uint32)Addr<(0x80000000+0x100000))){
   temp1= ((Uint32)Addr - 0x80000000 +0x9e000000);
  }else if(((Uint32)Addr>=0x80100000)&&((Uint32)Addr<(0x80100000+0x100000))){
   temp1= ((Uint32)Addr - 0x80100000 + 0x9e100000);

  }else if(((Uint32)Addr>=0x80200000)&&((Uint32)Addr<(0x80200000+0x100000))){
   temp1= ((Uint32)Addr - 0x80200000 +0x9e200000);

  }else if(((Uint32)Addr>=0x80300000)&&((Uint32)Addr<(0x80300000+0x1000000))){
   temp1= ((Uint32)Addr - 0x80300000 +0x9e300000);

  }else if(((Uint32)Addr>=0x81300000)&&((Uint32)Addr<(0x81300000+0xc00000))){
   temp1= ((Uint32)Addr - 0x81300000 +0x9f300000);

  }else if(((Uint32)Addr>=0x81f00000)&&((Uint32)Addr<(0x81f00000+0x100000))){
   temp1= ((Uint32)Addr - 0x81f00000 +0x9ff00000);

  }else if(((Uint32)Addr>=0xa0000000)&&((Uint32)Addr<(0xa0000000+0x55000))){
   temp1= ((Uint32)Addr - 0xa0000000 +0x9cf00000);

  }else if(((Uint32)Addr>=0xa0055000)&&((Uint32)Addr<(0xa0055000+0x55000))){
   temp1= ((Uint32)Addr - 0xa0055000 +0x9cf55000);

  }else{
   temp1= ((Uint32)Addr & 0xFFFFFFFF);
  }
  return (Void *)temp1;
#else
  return ((void *)((unsigned int)Addr)); 
#endif
}
