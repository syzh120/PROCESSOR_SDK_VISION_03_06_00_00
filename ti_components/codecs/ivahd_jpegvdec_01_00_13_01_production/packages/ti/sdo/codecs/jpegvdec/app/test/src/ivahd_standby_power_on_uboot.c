/**
********************************************************************************
* IVAHD Standby Sequence
*
*  This file contains sequence to to put of given IVAHD in given SoC
*  in standby mode. This is required for booting during powering ON of 
*  given SoC. As this is an example code, there is no support provided on this.
*  Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
*  ALL RIGHTS RESERVED
********************************************************************************
*/
/**
********************************************************************************
* @file      ivahd_standby_power_on_uboot.c
*
* @brief  This File contains function to put IVAHD in standby during power ON
*
* @author  Mihir Mody  (mihir@ti.com)
*
* @version 0.0 (Apr 2010) : Base version created [Mihir Mody]
* @version 0.1 (Apr 2010) : Minor fix and more documentation [Mihir Mody]
*
********************************************************************************
*/

/* -------------------- compilation control switches -------------------------*/

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <xdc/std.h>
#include <ti/xdais/xdas.h>

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
/*******************************************************************************
*   Address of ICONT1 TCM Imemory Base address in given IVAHD
*   This NEVER chagnes across SoC, IVAHD# and MMU seeting. 
*******************************************************************************/
#define ICONT1_ITCM_OFFSET (0x08000)
#define ICONT1_ITCM_BASE  (IVAHD_CONFIG_REG_BASE  + ICONT1_ITCM_OFFSET)
/*******************************************************************************
*   Address of ICONT1 TCM Imemory Base address in given IVAHD
*   This NEVER chagnes across SoC, IVAHD# and MMU seeting. 
*******************************************************************************/
#define ICONT2_ITCM_OFFSET (0x18000)
#define ICONT2_ITCM_BASE  (IVAHD_CONFIG_REG_BASE   + ICONT2_ITCM_OFFSET)

/*******************************************************************************
*  Success or Failure
*******************************************************************************/
#define SUCCESS  0
#define FAILURE  1

/*******************************************************************************
*   Lenth of Boot code
*******************************************************************************/
#define LENGTH_BOOT_CODE  14

/*******************************************************************************
*   Hex code to set for Stack setting, Interrupt vector setting
*   and instruction to put ICONT in WFI mode.
*   This shall be placed at TCM_BASE_ADDRESS of given IVAHD, which is
*   0x0000 locally after reset.
*******************************************************************************/

const unsigned int IVAHD_memory_wfi[LENGTH_BOOT_CODE] = {
0xEA000006,
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
/* --------------------- function prototypes ---------------------------------*/

/**
********************************************************************************
*  @fn         IVAHD_Standby_power_on_uboot(
*                                        UInt32 IVAHD_CONFIG_REG_BASE,
*                                        UInt32 PRCM_IVAHD_ICONT_RST_CNTL_ADDR
*                                      )
*
*  @brief      This function puts given IVAHD in standby after power on during  
*              booting process of given SoC
*
*  @param [in] IVAHD_CONFIG_REG_BASE: Register base address (M3 view) of the 
*              given IVAHD
* 
*  @param [in] PRCM_IVAHD_ICONT_RST_CNTL_ADDR: PRCM base address (M3 view) of
*              the given IVAHD 
*
*  @return     TRUE/FALSE
*
*  @note       Please make to define address as per given SoC, IVAHD# and MMU
*              Setting
********************************************************************************
*/

XDAS_Int32 IVAHD_Standby_power_on_uboot(
                                        UInt32 IVAHD_CONFIG_REG_BASE,
                                        UInt32 PRCM_IVAHD_ICONT_RST_CNTL_ADDR
                                       )
{
  unsigned int length =0;
  
  /*--------------------------------------------------------------------------*/
  /* Assigment of pointers                                                    */
  /* A generic code shall take all address as input parameters                */
  /*--------------------------------------------------------------------------*/
  volatile unsigned int *prcm_ivahd_icont_rst_cntl_addr = 
      (unsigned int *)PRCM_IVAHD_ICONT_RST_CNTL_ADDR;
  volatile unsigned int *icont1_itcm_base_addr =
      (unsigned int *)(IVAHD_CONFIG_REG_BASE + ICONT1_ITCM_OFFSET) ; 
  volatile unsigned int *icont2_itcm_base_addr =
      (unsigned int *)(IVAHD_CONFIG_REG_BASE + ICONT2_ITCM_OFFSET); 
      
  /*--------------------------------------------------------------------------*/
  /* Set IVAHD in reset mode to enable downloading of boot code               */
  /* Please note that this state can be SKIPPED if IVAHD is alredy in reset   */
  /* state during uboot and reset is not de-asserted                          */   
  /* Set bit0 to 1 to put ICONT1 in reset state                               */
  /* Set bit1 to 1 to put ICONT2 in reset state                               */
  /*--------------------------------------------------------------------------*/
  *prcm_ivahd_icont_rst_cntl_addr |=  0x00000003;

  /*--------------------------------------------------------------------------*/
  /* Copy boot code to ICONT1 & INCOT2 memory                                 */
  /*--------------------------------------------------------------------------*/
  for (length=0; length<LENGTH_BOOT_CODE; length++) {
    *icont1_itcm_base_addr++ = IVAHD_memory_wfi[length];
    *icont2_itcm_base_addr++ = IVAHD_memory_wfi[length];
  } 
  /*--------------------------------------------------------------------------*/
  /* Take IVAHD out of reset mode.                                            */
  /* Set bit0 to 0 to take ICONT1 out of reset state                          */
  /* Set bit1 to 0 to take ICONT1 out of reset state                          */
  /* This implies ICONT inside IVAHD will exectute WFI                        */
  /*--------------------------------------------------------------------------*/
  *prcm_ivahd_icont_rst_cntl_addr &=  0xFFFFFFFC;

  /*--------------------------------------------------------------------------*/
  /* As ICONT goes in WFI and there are no pending VDMA transction            */
  /* entire IVAHD will be go in standby mode and PRCM will fully control      */
  /* further managment of IVAHD power state                                   */ 
  /*--------------------------------------------------------------------------*/

  return SUCCESS;
}
