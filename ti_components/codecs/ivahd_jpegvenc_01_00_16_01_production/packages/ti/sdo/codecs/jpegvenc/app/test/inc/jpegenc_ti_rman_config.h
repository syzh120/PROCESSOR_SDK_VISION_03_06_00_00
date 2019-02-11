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
* @file      jpegenc_ti_rman_config.h
*
* @brief     IRES RMAN related header file
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
*
* @version 0.1 (July 2010): DataSync feature added [pavan]
*
* @version 0.2 (Aug 2010) : Debug Trace Feature Added[Vasudev]
*
* @version 0.3 (Sep 2010) : Modified to support M3 part changes to align with
*                           MPEG4 Decoder[Vasudev]
*
* @version 0.4 (Dec 2010) : Changes related to HDVICP_Reset() and 
*                           ivahd_standby_power_on_uboot() [Naidu]
*******************************************************************************
*/
/* -------------------- compilation control switches -------------------------*/
#ifndef JPEGENC_TI__RMAN_CONFIG_H__
#define   JPEGENC_TI__RMAN_CONFIG_H__

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/

/*--------------------- program files ----------------------------------------*/

/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

#define   NUM_IVAHD_RESOURCES 5

#if defined(HOSTCORTEXM3_NETRA)
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

#elif defined(HOSTCORTEXM3_OMAP4)

#define IVAHD_CONFIG_REG_BASE_IVAHD0          (0x5A000000)
#define PRCM_IVAHD_ICONT_RST_CNTL_ADDR_IVAHD0 (0x4A306F10)

#endif

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/
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
void RMAN_AssignResources(IALG_Handle handle);

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

void RMAN_FreeResources(IALG_Handle handle);

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

#endif /* JPEGVENC_RMAN_CONFIG_H__ */

