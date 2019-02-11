/*
*******************************************************************************
 * HDVICP2.0 Based H.264 HP Decoder
 * 
 * "HDVICP2.0 Based H.264 HP Decoder" is a software module developed on TI's 
 *  HDVICP2 based SOCs. This module is capable of decoding a compressed 
 *  high/main/baseline profile H.264 bit-stream into a YUV 4:2:0 Raw video.
 *  Based on "ISO/IEC 14496-10". 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
*******************************************************************************
*/

/**  
********************************************************************************
 * @file <TestApp_rmanConfig.c>                          
 *                                       
 * @brief This file contains sample implementataion of RMAN functions 
 *
 * @author: Ramakrishna Adireddy
 *
 * @version 0.0 (Aug 2009) : Base version 
 * @version 0.1 (Apr 2010) : Code cleanup and commenting
 *                           [Ramakrishna]
 * @version 0.2 (May 2010) : Added condition checks for handle validity
 *                           [Ramakrishna]
 * @version 0.3 (Jun 2010) : Implemented activate and deactivate for the 
 *                           application
 *                           [Ramakrishna]
 * @version 0.4 (Jul 2010) : Reset implementation with uboot
 *                           [Ramakrishna]
 * @version 0.5 (Oct 2010) : Fix issue corresponds to Frame Size bit-stream mode
 *                           and parse header combination run
 *                           [Ramakrishna]
 * @version 0.6 (Dec 2010) : Modification to HDVICP_Reset funcation
 *                           [Ramakrishna]
 * @version 0.7 (July 2012): Added support for decoding only specific frame 
 *                           types as requested by application [Mahantesh]
 ******************************************************************************
*/

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/ires.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/sdo/fc/utils/api/_alg.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>
#include <ti\sdo\fc\ires\tiledmemory\ires_tiledmemory.h>
#include <h264vdec.h>
#include <TestApp_rmanConfig.h>
#include <TestApp_Constants.h>
#include <TestAppDecoder.h>

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
#ifdef MEM_CORRUPTION_TEST
extern XDAS_Int32    countConfigSet;
#endif
/*----------------------------------------------------------------------------*/
/* Functions related to memory allocation/deallocation: malloc and free       */
/*----------------------------------------------------------------------------*/
#define myMemalign(align, size)  malloc((size))
#define myFree      free

/*---------------------------------------------------------------------------*/
/*   Size of Boot code                                                       */
/*---------------------------------------------------------------------------*/
#define BOOT_CODE_SIZE  14
/*----------------------------------------------------------------------------*/
/*   Hex code to set for Stack setting, Interrupt vector setting              */
/*   and instruction to put ICONT in WFI mode.                                */
/*   This shall be placed at TCM_BASE_ADDRESS of given IVAHD, which is        */
/*   0x0000 locally after reset.                                              */
/*----------------------------------------------------------------------------*/
const XDAS_UInt32 IVAHD_memory_wfi[BOOT_CODE_SIZE] =   { 0xEA000006,
                                                         0xEAFFFFFE,
                                                         0xEAFFFFFE,
                                                         0xEAFFFFFE,
                                                         0xEAFFFFFE,
                                                         0xEAFFFFFE,
                                                         0xEAFFFFFE,
                                                         0xEAFFFFFE,
                                                         0xE3A00000,
                                                         0xEE070F9A,
                                                         0xEE070F90,
                                                         0xE3A00000,
                                                         0xEAFFFFFE,
                                                         0xEAFFFFF1
                                                        };
/*--------------------------------------------------------------------------*/
/* Variables to back up the protocol Args & numResourcesBackUp              */
/* requested by the codec.                                                  */
/*--------------------------------------------------------------------------*/
XDAS_UInt32                   numResourcesBackUp;
XDAS_UInt32                   colocBufSize;
IRES_TILEDMEMORY_ProtocolArgs protocolArgsBackUp[NUM_TILEDMEM_OBJECTS];

/*--------------------------------------------------------------------------*/
/* Flag that indicates the ivahd Code load status                           */
/*--------------------------------------------------------------------------*/
XDAS_UInt32   ivaCodeLoadDone;
extern XDAS_UInt32   streamEnded;

/*--------------------------------------------------------------------------*/
/* Counting semaphore on which HDVICP_Wait() happens                        */
/*--------------------------------------------------------------------------*/
volatile XDAS_Int32 gIvahdDoneFlag;
/*--------------------------------------------------------------------------*/
/* Extrnally referenced variabled: HDVICP Handle  and picture count to      */
/* control the IVAHD booting (code loading)                                 */
/* H264VDEC_Handle: Algorithm specific handle                               */
/*--------------------------------------------------------------------------*/
extern IRES_HDVICP2_Obj h264IresHdvicp2_handle;
extern XDAS_UInt8       appIvahdId;

/*----------------------------------------------------------------------------*/
/*  Global Algorithm handle which will be initialized with the argument to    */
/*  the algorithm's  processing function.                                     */
/*----------------------------------------------------------------------------*/
IALG_Handle g_handle[NUM_IVAHD_RESOURCES];

extern sChannelState nChannelState[NUM_DEC_CHANNELS_SUPPORTED];

/** 
 *******************************************************************************
 *
 *@fn   H264VDEC_TI_deactivateResource
 *
 *@brief  Call to deactivate a resource, identified by resourceHandle
 *        Part of IRES interface 
 *
 *@param[in] handle          : pointer to the algorithm handle
 *@param[in] resourceHandle  : pointer to HDVICP handle 
 *
 *@return IRES_Status
 *
 *******************************************************************************
*/
extern IRES_Status H264VDEC_TI_deactivateResource(IALG_Handle handle, 
                                                  IRES_Handle resourceHandle);

/** 
 *******************************************************************************
 *
 *@fn   H264VDEC_TI_activateResource
 *
 *@brief  Call to Activate a resource, identified by resourceHandle
 *        Part of IRES interface 
 *
 *@param[in] handle          : pointer to the algorithm handle
 *@param[in] resourceHandle  : pointer to HDVICP handle 
 *
 *@return IRES_Status
 *
 *******************************************************************************
*/
extern IRES_Status H264VDEC_TI_activateResource(IALG_Handle handle, 
                                                IRES_Handle resourceHandle);
/** 
 *******************************************************************************
 *
 *@fn   memcmp
 *
 *@brief  Function to compare two memory blocks
 *
 *@param[in] s1  : pointer to source memory block1
 *@param[in] s2  : pointer to source memory block2
 *@param[in] s2  : size of the memory block
 *
 *@return True/False
 *
 *******************************************************************************
*/
extern int (memcmp)(const void *s1, const void *s2, size_t n);

/*----------------------------------------------------------------------------*/
/*  Global Arguments which will be initialized with the argument to           */
/*  the algorithm's MB processing function.                                   */
/*----------------------------------------------------------------------------*/
Uint32 g_cbArgs[NUM_IVAHD_RESOURCES];

/*----------------------------------------------------------------------------*/
/*  Global function pointer which will be initialized to the algorithm's MB   */
/*  processing function and will be called by the interrupt handler function. */                                                                 
/*----------------------------------------------------------------------------*/
void (* g_fnPtr[NUM_IVAHD_RESOURCES])(IALG_Handle handle, void *cbArgs);

/*----------------------------------------------------------------------------*/
/*  Global Flag which will be intially be zero.                               */
/*  If acquire is made once, then this flag will be set and stay set.         */
/*----------------------------------------------------------------------------*/
XDAS_UInt32 isAcquireCallMade;
/*----------------------------------------------------------------------------*/
/*  Interrupt vector table definitions.                                       */
/*----------------------------------------------------------------------------*/
typedef void (*ISR_VECTOR_TABLE)();
extern ISR_VECTOR_TABLE vector_table[];
XDAS_Void TestApp_captureTime(XDAS_UInt32 capLoc);
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
#ifdef HOST_ARM9
arm_isr()
{
  (*g_fnPtr[0])(g_handle[0], (void *)g_cbArgs[0]);
}
/*----------------------------------------------------------------------------*/
/* For Cortex M3 (Case of Ducati or ASIC)                                     */
/*----------------------------------------------------------------------------*/
#else /* For Cortex M3 (Case of Ducati or ASIC) */
void ISR_Function()
{
  /*--------------------------------------------------------------------------*/
  /* Call-Back function tied to IVA-HD - 0.                                   */
  /* As with Ducati a single IVA-HD resource is tied                          */
  /* this id shall be zero.                                                   */
  /*--------------------------------------------------------------------------*/
  (*g_fnPtr[0])(g_handle[0], (void *)g_cbArgs[0]);
}
#endif

/** 
********************************************************************************
 *  @fn     HDVICP_Acquire
 *  @brief  This function acquires the resources required by the process call
 *          
 *  @param[in] handle          : Alg handle 
 *  @param[out] iresHandle     : Ires handle
 *  @param[in] yieldCtxt       : IRES Yield context
 *  @param[] reloadHDVICP      : Status of Acquire 
 *  @param[] configurationId   : Id of the codec configuration used
 *  @param[] lateAcquireArg    : Parameters related to late acquire
 *          
 *  @return none
********************************************************************************
*/
void HDVICP_Acquire(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle, 
                    IRES_YieldContext *yieldCtxt, 
                    XDAS_UInt32 *reloadHDVICP,
                    XDAS_UInt32 *configurationId, XDAS_Int32 lateAcquireArg
                   )
{
  XDAS_Int32 ID = 0;
  XDAS_UInt32 regBaseAddr, memBaseAddr, prcmBaseAddr;
#if DISABLE_FOR_PROFILING
  /*--------------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                      */
  /*--------------------------------------------------------------------------*/
  if((IALG_Handle)h264decHandle != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                         */
  /*--------------------------------------------------------------------------*/
  if(&h264IresHdvicp2_handle != iresHandle)
  {
    fprintf(stdout,"HDVICP handle not valid..\n");  
  }
#endif  
  /*--------------------------------------------------------------------------*/
  /* After the resource allocation the new resource ID is communicated        */
  /*--------------------------------------------------------------------------*/
  iresHandle->id = ID;

  /*--------------------------------------------------------------------------*/
  /* Address space notification                                               */
  /* Notification of SL2 memory and configuration as seen by                  */
  /* the Host ARM. Host ARM can be M3 or 968 . Suitable                       */
  /* address is picked by macros defined in cslr_ivahd.h                      */
  /*--------------------------------------------------------------------------*/

  regBaseAddr = (Uint32)regBaseAdderss[appIvahdId];/*Length: 0x00080000 bytes */
  memBaseAddr = (Uint32)memBaseAddress[appIvahdId];/*Length: 0x00080000 bytes */

  /*--------------------------------------------------------------------------*/
  /* IVAHD_PRCM Base address as understood by Cortex-M3                       */
  /*--------------------------------------------------------------------------*/
  prcmBaseAddr = (Uint32)resetControlAddress[appIvahdId];/* Length: 0x0 bytes */

  iresHandle->registerBaseAddress = (void *)regBaseAddr;
  iresHandle->memoryBaseAddress   = (void *)memBaseAddr;
  iresHandle->resetControlAddress = (void *)prcmBaseAddr;
  /*--------------------------------------------------------------------------*/
  /* Load the code only for the first time (i.e., for first frame of the first*/
  /* stream/test vector...                                                    */
  /*--------------------------------------------------------------------------*/
  if(ivaCodeLoadDone == XDAS_FALSE)
  {
#if defined(HOST_ASIC)
    /*------------------------------------------------------------------------*/
    /* if set to SAMECODEC, it indicates that codec-process call need not     */
    /* reload the code. DIFFERENTCODEC indicates that the codec-process call  */
    /* needs to reload the code                                               */
    /*------------------------------------------------------------------------*/
    *reloadHDVICP = DIFFERENTCODEC; 
#else
    *reloadHDVICP = DIFFERENTCODEC; 
#endif
    ivaCodeLoadDone = XDAS_TRUE;
  }
  else if(streamEnded)
  {
    *reloadHDVICP = DIFFERENTCODEC;
    streamEnded = XDAS_FALSE;
  } 
  else
  {
    *reloadHDVICP = SAMECODECTYPE;
  }

#ifdef MEM_CORRUPTION_TEST
  *reloadHDVICP = DIFFERENTCODEC;
#endif

  *configurationId = *reloadHDVICP;
  
  isAcquireCallMade = 1;
  TestApp_captureTime(HDVICP_ACQUIRE);
}

/** 
********************************************************************************
 *  @fn     HDVICP_Configure
 *  @brief  This function configures global variables 
 *          
 *  @param[in] handle                        : Alg handle 
 *  @param[out] iresHandle                   : Ires handle
 *  @param[out] IRES_HDVICP2_CallbackFxn     : Global function pointer to the 
 *                                             MB processing function 
 *  @param[out] cbArgs                       : Arguments to the MB processing 
 *                                             function
 *          
 *  @return none
********************************************************************************
*/
void HDVICP_Configure
( 
  IALG_Handle handle, IRES_HDVICP2_Handle iresHandle, 
  void (*IRES_HDVICP2_CallbackFxn)(IALG_Handle handle, void *cbArgs), 
  void *cbArgs
)
{
  XDAS_Int32 ivahdID = 0;
#if DISABLE_FOR_PROFILING
  /*--------------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                      */
  /*--------------------------------------------------------------------------*/
  if((IALG_Handle)h264decHandle != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                         */
  /*--------------------------------------------------------------------------*/
  if(&h264IresHdvicp2_handle != iresHandle)
  {
    fprintf(stdout,"HDVICP handle not valid..\n");  
  }
#endif  
  /*--------------------------------------------------------------------------*/
  /*  Initialize the globalIVAHD flag upon which the HDVICP_Wait              */
  /*  shall poll.                                                             */
  /*--------------------------------------------------------------------------*/
  gIvahdDoneFlag = 0;

  /*--------------------------------------------------------------------------*/
  /*  Initialize the Handle to the MB processing function that is             */
  /*  required to be called by the ISR.                                       */
  /*--------------------------------------------------------------------------*/
  g_handle[ivahdID] = handle;

  /*--------------------------------------------------------------------------*/
  /*  Initialize the global function ptr to the MB processing function        */
  /*  which will be called from the ISR.                                      */ 
  /*--------------------------------------------------------------------------*/
  g_fnPtr[ivahdID]  = IRES_HDVICP2_CallbackFxn;


  /*--------------------------------------------------------------------------*/
  /*  Initialize the Argument to the MB processing function that is           */
  /*  required to be called by the ISR.                                       */
  /*--------------------------------------------------------------------------*/
  g_cbArgs[ivahdID] = (Uint32)cbArgs;

#ifndef HOST_ARM9
  /*--------------------------------------------------------------------------*/
  /* Registering the Interrupt.                                               */
  /*--------------------------------------------------------------------------*/
  *((int *)MBOX_INTR_REG) = mboxIntrEnableMask[appIvahdId];
                                               /*Interrupt enable on Cortex-M3*/
  vector_table[mboxIntrIndex[appIvahdId]] = ISR_Function; /* ISR Address      */
#endif
}

/** 
********************************************************************************
 *  @fn     HDVICP_Release

 *  @brief  Release
 *
 *  @param[in] handle                        : Alg handle 
 *  @param[out] iresHandle                   : Ires handle

 *  @return none
********************************************************************************
*/
void HDVICP_Release(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
{
  TestApp_captureTime(HDVICP_RELEASE);
#if DISABLE_FOR_PROFILING
  /*--------------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                      */
  /*--------------------------------------------------------------------------*/
  if((IALG_Handle)h264decHandle != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                         */
  /*--------------------------------------------------------------------------*/
  if(&h264IresHdvicp2_handle != iresHandle)
  {
    fprintf(stdout,"HDVICP handle not valid..\n");  
  }
#endif  
  /* dummy call */
}

/** 
********************************************************************************
 *  @fn     HDVICP_reacquireIfOwner
 *  @brief  This function re-acquires the resources
 *          
 *  @param[in] handle                        : Alg handle 
 *  @param[out] iresHandle                   : Ires handle
 *           
 *  @return 1 - if acquire call is done before calling re-acquire 
 *           0 - if acquire call is not done
********************************************************************************
*/
XDAS_UInt32 HDVICP_reacquireIfOwner(IALG_Handle handle, 
                                    IRES_HDVICP2_Handle iresHandle)
{

#if DISABLE_FOR_PROFILING
  XDAS_UInt32 regBaseAddr, memBaseAddr, prcmBaseAddr;

  /*--------------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                      */
  /*--------------------------------------------------------------------------*/
  if((IALG_Handle)h264decHandle != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                         */
  /*--------------------------------------------------------------------------*/
  if(&h264IresHdvicp2_handle != iresHandle)
  {
    fprintf(stdout,"HDVICP handle not valid..\n");  
  }
  
  /*--------------------------------------------------------------------------*/
  /* Address space notification                                               */
  /* Notification of SL2 memory and configuration as seen by the Host ARM.    */
  /* Host ARM can be M3 or 968 or whatever. Suitable address is picked by     */
  /* macros defined in cslr_ivahd.h                                           */
  /*--------------------------------------------------------------------------*/  
  regBaseAddr = (Uint32)regBaseAdderss[appIvahdId];/*Length: 0x00080000 bytes */
  memBaseAddr = (Uint32)memBaseAddress[appIvahdId];/*Length: 0x00080000 bytes */

  /*--------------------------------------------------------------------------*/
  /* IVAHD_PRCM Base address as understood by Cortex-M3                       */
  /*--------------------------------------------------------------------------*/
  prcmBaseAddr = (Uint32)resetControlAddress[appIvahdId];/* Length: 0x0 bytes */

  iresHandle->registerBaseAddress = (void *)regBaseAddr;
  iresHandle->memoryBaseAddress   = (void *)memBaseAddr;
  iresHandle->resetControlAddress = (void *)prcmBaseAddr;
  
  if(isAcquireCallMade)
    return TRUE;  
  else 
    return FALSE;  
#endif

  TestApp_captureTime(IVAHD_POSTMSG);
  return TRUE;
}

/** 
********************************************************************************
 *  @fn     HDVICP_Wait
 *  @brief  This function waits for IVAHD done
 *          
 *  @param[in] handle                        : Alg handle 
 *  @param[out] iresHandle                   : Ires handle
 *  @param[] yieldCtxt                   : IRES yieldContext
 *  @return TRUE/FAIL
********************************************************************************
*/
XDAS_UInt32 HDVICP_Wait(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle, 
                 IRES_YieldContext * yieldCtxt
                )
{
  TestApp_captureTime(HDVICP_WAIT);
#if DISABLE_FOR_PROFILING
  /*--------------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                      */
  /*--------------------------------------------------------------------------*/
  if((IALG_Handle)h264decHandle != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                         */
  /*--------------------------------------------------------------------------*/
  if(&h264IresHdvicp2_handle != iresHandle)
  {
    fprintf(stdout,"HDVICP handle not valid..\n");  
  }
#endif
  /*--------------------------------------------------------------------------*/
  /* Wait untill the global counter (counting semaphore) is zero              */
  /*--------------------------------------------------------------------------*/
  while (gIvahdDoneFlag == 0);
  gIvahdDoneFlag--;

  return TRUE;
}

/** 
********************************************************************************
 *  @fn     HDVICP_Done
 *  @brief  This function will be called by the interrupt handler function 
 *          when it detects an end-of-frame processing
 *          
 *  @param[in] handle                        : Alg handle 
 *  @param[out] iresHandle                   : Ires handle
 *           
 *  @return none
********************************************************************************
*/
void HDVICP_Done(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
{
#if DISABLE_FOR_PROFILING
  /*--------------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                      */
  /*--------------------------------------------------------------------------*/
  if((IALG_Handle)h264decHandle != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                         */
  /*--------------------------------------------------------------------------*/
  if(&h264IresHdvicp2_handle != iresHandle)
  {
    fprintf(stdout,"HDVICP handle not valid..\n");  
  }
#endif
  /*--------------------------------------------------------------------------*/
  /* Increment the global counter to register the new interrput               */
  /*--------------------------------------------------------------------------*/
  gIvahdDoneFlag++;
  TestApp_captureTime(HDVICP_DONE);
}

/** 
********************************************************************************
 *  @fn     HDVICP_Reset
 *  @brief  Function to reset HDVICP resouce before using it
 *          This function will be called by algorithm when needed
 *          This is dummy on Simulator and as well on ARM9 HOST.
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
#if !defined(HOST_ARM9) && !defined(SIMULATOR_RUN)

#ifdef NETRA
  volatile unsigned int temp;
  unsigned int RM_IVAHD0_RSTCTRL =  
         (unsigned int)iresHandle->resetControlAddress; /*(PRM_IVAHD0 + 0x10) */
  unsigned int RM_IVAHD0_RSTST = 
         (RM_IVAHD0_RSTCTRL + 4);                        /*(PRM_IVAHD0 + 0x14)*/
  unsigned int CM_IVAHD0_IVAHD_CLKCTRL = 
         ((RM_IVAHD0_RSTCTRL - 0x610 ) + 0x20);    /*(PRCM_BASE_ADDR + 0x0620)*/
  unsigned int CM_IVAHD0_SL2_CLKCTRL =  
         (CM_IVAHD0_IVAHD_CLKCTRL + 4);            /*(PRCM_BASE_ADDR + 0x0624)*/

  /*---------------------------------------------------------------*/
  /* CM_IVAHD0_IVAHD_CLKCTRL. MODULEMODE = 0x0;                    */
  /* while(CM_IVAHD0_IVAHD_CLKCTRL.IDLEST != 0x3);                 */
  /*---------------------------------------------------------------*/
  WR_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL , 0);
  do
  {
    temp = RD_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL);
    temp = ((temp >> 16) & 3);
  }while(temp != 3);

  /*---------------------------------------------------------------*/
  /* CM_IVAHD0_SL2_CLKCTRL. MODULEMODE = 0x0;                      */
  /* while(CM_IVAHD0_SL2_CLKCTRL.IDLEST != 0x3);                   */
  /*---------------------------------------------------------------*/
  WR_MEM_32(CM_IVAHD0_SL2_CLKCTRL , 0);
  do
  {
    temp = RD_MEM_32(CM_IVAHD0_SL2_CLKCTRL);
    temp = ((temp >> 16) & 3);
  }while(temp != 3);
  
  /*---------------------------------------------------------------*/
  /* RM_IVAHD0_RSTST     = IVA_RST3 | IVA_RST2 | IVA_RST1; : 0x7 : */
  /* RM_IVAHD0_RSTCTRL   = IVA_RST3 | IVA_RST2 | IVA_RST1; : 0x7   */
  /*---------------------------------------------------------------*/
  WR_MEM_32(RM_IVAHD0_RSTST , 7);
  WR_MEM_32(RM_IVAHD0_RSTCTRL , 7);

  /*---------------------------------------------------------------*/
  /* CM_IVAHD0_SL2_CLKCTRL. MODULEMODE = 0x2;                      */
  /* CM_IVAHD0_IVAHD_CLKCTRL. MODULEMODE = 0x2;                    */
  /*---------------------------------------------------------------*/
  WR_MEM_32(CM_IVAHD0_SL2_CLKCTRL , 2);
  WR_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL , 2);

  /*---------------------------------------------------------------*/
  /* RM_IVAHD0_RSTCTRL = !IVA_RST3 | IVA_RST2 | IVA_RST1; : 0x3    */
  /*---------------------------------------------------------------*/
  WR_MEM_32(RM_IVAHD0_RSTCTRL , 3);

  /*---------------------------------------------------------------*/
  /* Wait for !IDLE                                                */
  /* while(CM_IVAHD0_IVAHD_CLKCTRL.IDLEST != 0x0);                 */
  /* while(CM_IVAHD0_SL2_CLKCTRL.IDLEST != 0x0);                   */
  /*---------------------------------------------------------------*/
  do
  {
    temp = RD_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL);
    temp = ((temp >> 16) & 3);
  }while(temp != 0);
  
  do
  {
    temp = RD_MEM_32(CM_IVAHD0_SL2_CLKCTRL);
    temp = ((temp >> 16) & 3);
  }while(temp != 0);
  
  /*---------------------------------------------------------------*/
  /* while(RM_IVAHD0_RSTST.IVA_RST3 != 0x1);                       */
  /*---------------------------------------------------------------*/
  do
  {
    temp = RD_MEM_32(RM_IVAHD0_RSTST);
    temp = ((temp >> 2) & 1);
  }while(temp != 1);
  
#else

  /*--------------------------------------------------------------------------*/
  /* Assigment of pointers                                                    */
  /* A generic code shall take all address as input parameters                */
  /*--------------------------------------------------------------------------*/
  volatile XDAS_UInt32 *resetControlReg = 
                        (volatile XDAS_UInt32 *)iresHandle->resetControlAddress;

  volatile XDAS_UInt32 *resetControlStatusReg = 
                (volatile XDAS_UInt32 *)((XDAS_UInt32)resetControlReg + 0x04);

  volatile unsigned int *ivaClkControlReg = 
          (volatile unsigned int *)(IVAHD_CLKREG_BASE + IVAHD_CLKCTRL_OFFSET);

  volatile unsigned int *ivaClkControlStatusReg = 
        (volatile unsigned int *)(IVAHD_CLKREG_BASE + IVAHD_CLKSTCTRL_OFFSET);

  volatile unsigned int *sl2ClkControlReg = 
            (volatile unsigned int *)(IVAHD_CLKREG_BASE + SL2_CLKCTRL_OFFSET);

  volatile int debugCounter1 = 0, debugCounter2 = 0; 
#if DISABLE_FOR_PROFILING
  /*--------------------------------------------------------------------------*/
  /* Check if algorithm handle is valid.                                      */
  /*--------------------------------------------------------------------------*/
  if((IALG_Handle)h264decHandle != handle)
  {
    fprintf(stdout,"Algorithm handle not valid..\n");
  }

  /*--------------------------------------------------------------------------*/
  /* Check if HDVICP handle is valid.                                         */
  /*--------------------------------------------------------------------------*/
  if(&h264IresHdvicp2_handle != iresHandle)
  {
    fprintf(stdout,"HDVICP handle not valid..\n");  
  }
#endif
  /*--------------------------------------------------------------------------*/
  /* First put IVA into HW Auto mode                                          */
  /* Wait for IVA HD to standby                                               */
  /*--------------------------------------------------------------------------*/
  *ivaClkControlStatusReg |= 0x3;
  while (!((*ivaClkControlReg) & 0x40000));
    
  /*--------------------------------------------------------------------------*/
  /* Disable IVAHD and SL2 modules                                            */
  /* Ensure that IVAHD and SL2 are disabled                                   */
  /*--------------------------------------------------------------------------*/
  *ivaClkControlReg = 0;
  *sl2ClkControlReg = 0;

  do{
    if((*ivaClkControlReg) & 0x00030000) 
    {
      break;
    }
  }while(1);
  
  do{
    if((*sl2ClkControlReg) & 0x00030000) 
    {
      break;
    }
  } while(1);

  /*--------------------------------------------------------------------------*/
  /* First clear the status bits                                              */
  /* Reset IVAHD sequencers and SL2                                           */
  /*--------------------------------------------------------------------------*/
  *resetControlReg       |= 7;
  *resetControlStatusReg |= 7;
    
  /*--------------------------------------------------------------------------*/
  /* Wait for confirmation that the systems have been reset                   */
  /* THIS CHECK MAY NOT BE NECESSARY, AND MOST OF ALL GIVEN OUR STATE,        */
  /* MAY NOT BE POSSIBLE                                                      */
  /*--------------------------------------------------------------------------*/
    
  /* Ensure that the wake up mode is set to SW_WAKEUP */
  *ivaClkControlStatusReg &= 0x2;
    
  /* Enable IVAHD and SL2 modules */
  *ivaClkControlReg = 1;
  *sl2ClkControlReg = 1;
    
  /* Deassert the SL2 reset */
  *resetControlReg &= 0xFFFFFFFB;

  /*Ensure that IVAHD and SL2 are enabled*/
  do{
    if(!((*ivaClkControlReg) & 0x00030000)) 
    {
      break;
    }
    /*------------------------------------------------------------------------*/
    /*Just to check the number of iterations taken for the modules to get     */
    /*enabled                                                                 */
    /*------------------------------------------------------------------------*/
    debugCounter1++;
  }while(1);
  
  do{
    if(!((*sl2ClkControlReg) & 0x00030000)) 
    {
      break;
    }
    /*------------------------------------------------------------------------*/
    /*Just to check the number of iterations taken for the modules to get     */
    /*enabled                                                                 */
    /*------------------------------------------------------------------------*/
    debugCounter2++;
  }while(1);

#endif   /* NETRA     */
#endif   /* HOST_ARM9 , SIMULATOR_RUN */

  /*--------------------------------------------------------------------------*/
  /* As ICONT goes in WFI and there are no pending VDMA transction,           */
  /* entire IVAHD will go to standby mode and PRCM will fully control         */
  /* further managment of IVAHD power state                                   */ 
  /*--------------------------------------------------------------------------*/

  return XDAS_TRUE;
}

/*----------------------------------------------------------------------------*/
/* Initialise the HDVICP handle with default values                           */
/*----------------------------------------------------------------------------*/
IRES_HDVICP2_Obj h264IresHdvicp2_handle =  {
  0,  /* IRES_Obj.persistent */
  0,  /* getStaticProperties */
  0,   /* info (reserved)        */
  0,  /* ID of the HDVICP2 being granted, could be 0,1,2, or LATE_ACQUIRE */
  (void*)IVAHD0_HOST_L2_BASE,   /* Reg. space base addr */
  (void*)IVAHD0_HOST_SL2,       /* Mem. space base addr */
  (void*)IVA0_RESET_CONTROLLER, /* PRCM register address */
  HDVICP_Acquire,            /* Pointer to the HDVICP_Acquire API function */
  HDVICP_Release,            /* Pointer to the HDVICP_Release API function */
  HDVICP_reacquireIfOwner,   /* Pointer to the HDVICP_reacquireIfOwner 
                                API function */
  HDVICP_Configure,          /* Pointer to the HDVICP_Configure API function */
  HDVICP_Wait,               /* Pointer to the HDVICP_Wait API function */
  HDVICP_Done,               /* Pointer to the HDVICP_Done API function */
  HDVICP_Reset               /* Pointer to the HDVICP_Reset API function */
  
};
/** 
********************************************************************************
 *  @fn     RMAN_AssignResources
 *  @brief  Funtion to assigne the HDVICP and Memory resources, This is dummy 
 *          implimentation to emulate the RMAN API
 *
 *  @param[in] handle : Pointer to the algorithm handle
 *  
 *  @return     IRES_Status : status of the resource assigment
 *
********************************************************************************
*/
XDAS_Int8 RMAN_AssignResources(IALG_Handle handle, XDAS_Int8 chnlNum)
{
  /*--------------------------------------------------------------------------*/
  /* Pointers to the resource discriptor, protocal arguments of the HDVICP and*/
  /* tiledmemory resoures                                                     */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32 retVal, numResources, idx;
  IRES_TILEDMEMORY_ProtocolArgs *tiledmemProtocolArgs;
  IRES_ResourceDescriptor       *resourceDescriptor;
  IRES_HDVICP2_ProtocolArgs     *hdvicp2ProtocolArgs;  

  IRES_YieldFxn     yieldFxn = NULL;        /* acquired from RMAN during init */
  IRES_YieldArgs    yieldArgs = NULL;       /* acquired from RMAN during init */
  /*--------------------------------------------------------------------------*/
  /* reset global flag to zero which tells assigment status                   */
  /*--------------------------------------------------------------------------*/
  isAcquireCallMade = 0;
  /*--------------------------------------------------------------------------*/
  /* Call codec api function to get number of resources required for algorithm*/
  /*--------------------------------------------------------------------------*/
  numResources       = H264VDEC_TI_IRES.numResourceDescriptors(handle);
  numResourcesBackUp = numResources;
  /*--------------------------------------------------------------------------*/
  /* Allocate memory for the resource instances                               */
  /*--------------------------------------------------------------------------*/
  resourceDescriptor = (IRES_ResourceDescriptor *)malloc(numResources *
                       sizeof(IRES_ResourceDescriptor));

  fprintf(stdout, "Number of Resources required = %d\n", numResources);
    
  if((numResources-1) > NUM_TILEDMEM_OBJECTS)
  {
    fprintf(stdout, "Number of Resources required exceeding available.\n",
           numResources); 
  }
  /*--------------------------------------------------------------------------*/
  /* Get properties of the resource with help codec API function              */
  /*--------------------------------------------------------------------------*/
  retVal = H264VDEC_TI_IRES.getResourceDescriptors(handle, resourceDescriptor);

  if (retVal != IRES_OK)
  {
    printf("Error in Get Reosource Descriptor \n");
    myFree(resourceDescriptor);
    return IRES_EFAIL;
  }

  /*--------------------------------------------------------------------------*/
  /* assign default HDVICP resource handle pointer to the resource discriptor */
  /* hadle                                                                    */
  /*--------------------------------------------------------------------------*/
  resourceDescriptor[0].handle = (IRES_Obj *)&h264IresHdvicp2_handle;
  
  hdvicp2ProtocolArgs  =  
             (IRES_HDVICP2_ProtocolArgs*)resourceDescriptor[0].protocolArgs;

  h264IresHdvicp2_handle.id = hdvicp2ProtocolArgs->id;
                         
  for(idx = 1 ; idx<numResources ; idx++)
  {
    /*------------------------------------------------------------------------*/
    /* Create the TILED memory handles and pass it through the Resource       */
    /* Descriptor.                                                            */
    /*------------------------------------------------------------------------*/
    resourceDescriptor[idx].handle = 
        (IRES_Obj *)&nChannelState[chnlNum].iresTiledMemoryObjects[idx-1];

    /*------------------------------------------------------------------------*/
    /* Obtain attributes of the memory request                                */
    /*------------------------------------------------------------------------*/
    tiledmemProtocolArgs = (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                            [idx].protocolArgs;

    /*------------------------------------------------------------------------*/
    /* Allocate memory and assign it to the object.                           */
    /* Note: only 1D objects assumed                                          */
    /*------------------------------------------------------------------------*/
    nChannelState[chnlNum].iresTiledMemoryObjects[idx-1].memoryBaseAddress = 
                          (Void *)myMemalign(tiledmemProtocolArgs->alignment, 
                         (tiledmemProtocolArgs->sizeDim0 * sizeof(XDAS_UInt8)));

    /*------------------------------------------------------------------------*/
    /* Capture Colocated Info ires Buffer allocation details at create time   */
    /* The value "4" is correspond to colocated IRES buffer. If codec changes */
    /* the order of requesting IRES buffer, this value needs to be updated    */
    /* accordingly.  TODO: check for any other logic                          */
    /* Buffer index of colocated MB info buffer changed to 10 after           */ 
    /* implementing support for decoding only specific frame types as         */
    /* requested by application.                                              */
    /*------------------------------------------------------------------------*/
    if(idx == 10) 
    {
      colocBufSize = tiledmemProtocolArgs->sizeDim0;
    }
    /*------------------------------------------------------------------------*/
    /* Back up the protocol Args requested by the codec.                      */
    /* Later use this to check that same is requested during during           */
    /* RMAN_FreeResources()                                                   */
    /*------------------------------------------------------------------------*/
    memcpy(&protocolArgsBackUp[idx-1], tiledmemProtocolArgs, 
           sizeof (IRES_TILEDMEMORY_ProtocolArgs));
#ifdef MEM_CORRUPTION_TEST
    {
      /*---------------------------------------------------------------------*/
      /* Fill IRES memory with some data to check that codec doesnt depend   */
      /* on the DDR content (corrupting the memory).                         */
      /*---------------------------------------------------------------------*/
      char word_pattern[4] = {0x00, 0xAA, 0x55, 0x99};
      char word = word_pattern[countConfigSet & 0x3];
      if(nChannelState[chnlNum].iresTiledMemoryObjects[idx-1].
          memoryBaseAddress != NULL)
      {
        memset ((Void*)(nChannelState[chnlNum].iresTiledMemoryObjects[idx-1].
              memoryBaseAddress), word, 
              (tiledmemProtocolArgs->sizeDim0 * sizeof(XDAS_UInt8))); 
      }          
    }
#endif  
    nChannelState[chnlNum].iresTiledMemoryObjects[idx-1].isTiledMemory = 0;
  }
  /*--------------------------------------------------------------------------*/
  /* Codec API function init resources                                        */
  /*--------------------------------------------------------------------------*/
  retVal |= H264VDEC_TI_IRES.initResources(handle, &resourceDescriptor[0],
                                           yieldFxn, yieldArgs
                                          );
  /*--------------------------------------------------------------------------*/
  /* Free the memory allocated for the discriptor instances                   */
  /*--------------------------------------------------------------------------*/ 
  myFree(resourceDescriptor);

  return (retVal);
}

/** 
********************************************************************************
 *  @fn     RMAN_FreeResources
 *  @brief   This function Frees the resources acquired
 *          
 *  @param[in] handle                        : Alg handle 
 *           
 *  @return none
********************************************************************************
*/
void RMAN_FreeResources(IALG_Handle handle, XDAS_Int8 chnlNum)
{
  XDAS_Int32  retVal, numResources, idx;
  IRES_ResourceDescriptor       *resourceDescriptor;  
#if DISABLE_FOR_PROFILING
  IRES_TILEDMEMORY_ProtocolArgs *tiledmemProtocolArgs;
#endif
  
  H264VDEC_TI_deactivateResource(handle, 
        (IRES_Handle)&h264IresHdvicp2_handle);
  /*--------------------------------------------------------------------------*/
  /* Find out number of resources allocated by calling codec api function     */
  /*--------------------------------------------------------------------------*/
  numResources  = H264VDEC_TI_IRES.numResourceDescriptors(handle);
  
  if(numResources != numResourcesBackUp)
  {
    fprintf(stdout, "Err: Number of Resources requsted changed during Free\n",
           numResources); 
  }
  /*--------------------------------------------------------------------------*/
  /* Allocate memory for the resource instances                               */
  /*--------------------------------------------------------------------------*/
  resourceDescriptor = (IRES_ResourceDescriptor *)malloc(numResources *
                       sizeof(IRES_ResourceDescriptor));
  /*--------------------------------------------------------------------------*/
  /* Get properties of the resource with help codec API function              */
  /*--------------------------------------------------------------------------*/
  retVal = H264VDEC_TI_IRES.getResourceDescriptors(handle, resourceDescriptor);

  if (retVal != IRES_OK)
  {
    printf("Error in Get Reosource Descriptor \n");
  }
  /*--------------------------------------------------------------------------*/
  /* Free the allocated memory resources                                      */
  /*--------------------------------------------------------------------------*/   
  for(idx = 0 ; idx<(numResources-1) ; idx++)
  {
#if DISABLE_FOR_PROFILING
    /*------------------------------------------------------------------------*/
    /* Obtain attributes of the memory request                                */
    /*------------------------------------------------------------------------*/
    tiledmemProtocolArgs = (IRES_TILEDMEMORY_ProtocolArgs*)resourceDescriptor
                            [idx+1].protocolArgs;

    /*------------------------------------------------------------------------*/
    /* Chk that same protocol Args are reported again. Otherwise flag an      */
    /* error.                                                                 */
    /*------------------------------------------------------------------------*/
    if(memcmp(&protocolArgsBackUp[idx], tiledmemProtocolArgs, 
              sizeof (IRES_TILEDMEMORY_ProtocolArgs)))
    {
      fprintf(stdout, "Err: Protocol Args requested changed for idx = %d \n", 
                        (idx+1));  
    }
#endif  
    if(&nChannelState[chnlNum].iresTiledMemoryObjects[idx] !=
        (IRES_TILEDMEMORY_Obj *) resourceDescriptor[idx+1].handle)
    {
      printf("Decoder not returning IRES object handle correctly \n");
    }
    myFree(nChannelState[chnlNum].iresTiledMemoryObjects[idx].
            memoryBaseAddress);
  }

  myFree(resourceDescriptor);
}

/** 
********************************************************************************
 *  @fn     RMAN_DeactivateAllResources
 *  @brief   This function deactivates all resources
 *          
 *  @param[in] handle                        : Alg handle 
 *           
 *  @return none
********************************************************************************
*/
void RMAN_DeactivateAllResources(IALG_Handle handle)
{
  H264VDEC_TI_deactivateResource(handle, 
  (IRES_Handle)&h264IresHdvicp2_handle);

}

/** 
********************************************************************************
 *  @fn     RMAN_ActivateAllResources
 *  @brief   This function deactivates all resources
 *          
 *  @param[in] handle                        : Alg handle 
 *           
 *  @return none
********************************************************************************
*/
void RMAN_ActivateAllResources(IALG_Handle handle)
{
  H264VDEC_TI_activateResource(handle, 
  (IRES_Handle)&h264IresHdvicp2_handle);

}





