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
* @file      jpegvdec_rman_config.h                      
*
* @brief     This File contains the implementation of RMAN interfaces used by
*            the codec.
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
********************************************************************************
*/

/* ---------------------compilation control switches -------------------------*/

/*******************************************************************************
*   INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/

/*----------------------program files ----------------------------------------*/

/*******************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/*******************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/* ------------------------------ macros ------------------------------------ */
#ifndef _JPEGVDEC_RMAN_CONFIG_H__
#define _JPEGVDEC_RMAN_CONFIG_H__


#define NUM_IVAHD_RESOURCES 2

#define MAILBOX_CFG_START   (0x5A05A800)

#if (HOSTCORTEXM3_NETRA_IVAHD0 || HOSTCORTEXM3_NETRA_IVAHD1 || \
                  HOSTCORTEXM3_NETRA_IVAHD2 || HOSTCORTEXM3_NETRASIMULATOR)
                                                   
/*******************************************************************************
*   Address of IVAHD Base address in configuration space
*   This is based on IVAHD# as well as MMU Setting. 
*   Please refer to Memory map of SoC and MMU seeting to get this
*******************************************************************************/
#define IVAHD_CONFIG_REG_BASE_IVAHD0      (0x58000000)
#define IVAHD_CONFIG_REG_BASE_IVAHD1      (0x5A000000)
#define IVAHD_CONFIG_REG_BASE_IVAHD2      (0x53000000)
/*******************************************************************************
*   Address of Reset control address for ICONT in PRCM module of SoC
*   This is based on MMU Setting as well as given SoC.
*   Please refer to Memory map of SoC and MMU seeting to get this
*******************************************************************************/
#define PRCM_IVAHD_ICONT_RST_CNTL_ADDR_IVAHD0 (0x48180C10)
#define PRCM_IVAHD_ICONT_RST_CNTL_ADDR_IVAHD1 (0x48180D10)
#define PRCM_IVAHD_ICONT_RST_CNTL_ADDR_IVAHD2 (0x48180E10)

#elif (HOSTCORTEXM3_OMAP4 || HOSTCORTEXM3_OMAP4SIMULATOR)

#define IVAHD_CONFIG_REG_BASE_IVAHD0          (0x5A000000)
#define PRCM_IVAHD_ICONT_RST_CNTL_ADDR_IVAHD0 (0x4A306F10)

#endif

/*----------------------------------------------------------------------------*/
/*  These Macros for Netra Emulator Reset Function                            */
/*----------------------------------------------------------------------------*/
#if ( (HOSTCORTEXM3_NETRA_IVAHD0 || HOSTCORTEXM3_NETRA_IVAHD1 || \
               HOSTCORTEXM3_NETRA_IVAHD2 ) && (!HOSTCORTEXM3_NETRASIMULATOR) )
#define WR_MEM_32(addr, data)      \
 *(volatile unsigned int*)(addr)= (unsigned int)(data);
                                               
#define RD_MEM_32(addr)          *(volatile unsigned int*)(addr) ;
#endif

/** 
*******************************************************************************
*  @fn     ISR_Function
*
*  @brief  This function is a call back function tied to IVA-HD
*  @return none
*
*******************************************************************************
*/
void ISR_Function();
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
XDAS_UInt32 * modeId, XDAS_Int32 lateAcquireArg);

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
void *cbArgs);
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
void HDVICP_Release(IALG_Handle handle, 
IRES_HDVICP2_Handle iresHandle);
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
IRES_YieldContext * yieldCtxt);
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
IRES_HDVICP2_Handle iresHandle);

/**
********************************************************************************
*  @fn      RMAN_AssignResources(IALG_Handle handle)
*
*  @brief     Funtion to assigne the HDVICP and Memory resources, This is  
*             dummy implimentation to emulate exact RMAN module API
*
*  @param[in]  handle : Pointer to the Algorithm Handle structure
*
*  @return     IRES_Status : status of the resource assigment
*******************************************************************************
*/
void RMAN_AssignResources(IALG_Handle handle);

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
void RMAN_FreeResources(IALG_Handle handle);

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
);

/**
********************************************************************************
*  @fn     IVAHD_Standby_power_on_uboot
*
*  @brief  This function puts given IVAHD in standby after power on during  
*          booting process of given SoC
*
*  @return TRUE/FALSE
*
*  @note   Please make to define address as per given SoC, IVAHD# and MMU
*          Setting
********************************************************************************
*/

XDAS_Int32 IVAHD_Standby_power_on_uboot();


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
static Void MemoryFree(void * address);

#endif /* _JPEGVDEC_RMAN_CONFIG_H__ */

