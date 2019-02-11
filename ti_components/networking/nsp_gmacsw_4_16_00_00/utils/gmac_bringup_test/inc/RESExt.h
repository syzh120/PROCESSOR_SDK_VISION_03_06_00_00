/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

/**
 *  @Component   RES - Results via SPY for cosimulation of OMAP proj
 *
 *  @Filename    res_v2.h
 *
 *  @Description Contains functions to write amd dump cosimulation results
 *               using spy block.
 *
 *                  This file provides an interface for functions which are
 *                  used by the OMAP4 library and which MUST be implemented
 *                  by each project that uses the OMAP4 library.
 *
 *    Available Functions:
 *           Common
 *                  RES_Init - Initializes RESExt lib
 *                  RES_Set - Sets a value in results table
 *                  RES_Set_Uniq - Sets a value in results table uniquified with unique code
 *                  RES_GetCurrentStatus - Get current error status
 *                  RES_SetArray - Writes array that will not be parsed at end.
 *                  RES_GetErrorCount - Return number of errors in spy area
 *                  RES_End - End spy simulation by writing 'illegal' value.
 *           MPU only
 *                  RES_SetLocation - Sets the location in memory
 *                  RES_GetExternalLocation - retrieve external spy location
 *                  RES_GetDspSpy - Copy DSP local Spy to the System Spy Area
 *                  RES_GetDspSpyPoll - Copy DSP local Spy to the System Spy Area
 *                  RES_GetIvaSpy - Copy IVA local Spy to the System Spy Area
 *                  RES_GetFinalStatus - Gets final error status
 *
 *   Domain:     MPU/IVA/DSP
 *
 *   Board:      Simulation only
 *
 *   Fucntional Specifcation Version: N/A
 *
 *   Validating Test Cases: spy_gpmc spy_sdrc spy_ext
 *
 *//*======================================================================== */


#ifndef __RESEXT_H
#define __RESEXT_H

/* ============================================================================
 * INCLUDE FILES (only if necessary)
 * ============================================================================
 */
#ifdef __cplusplus
extern "C"
{
#endif


/* ============================================================================
 * EXPORTED DEFINITIONS
 * ============================================================================
 */

/* THE BASE IDs or MODULE IDs have been moved to /cdb/libComapXXXX/inc/common
   so that each project can give it's own list of module IDs
 */

/* ----------------------------------------------------------------------------
 * Definition: RES_MIN_*_VAL,RES_MAX_*_VAL
 *
 * DESCRIPTION: The ranges of PASS and FAIL values of lower byte that can written
 *              to results table spy
 *
 * ----------------------------------------------------------------------------
 */
/* range of good / OK result values */
#define RES_MIN_OK_VAL          0x0000u
#define RES_MAX_OK_VAL          0x000Fu

/* range of bad / fail result values */
#define RES_MIN_BAD_VAL         0x0010u
#define RES_MAX_BAD_VAL         0x00FEu


#define RES_POSTPROCESS_ID   (0xf)

/* ----------------------------------------------------------------------------
 * Definition: RES_*_*
 *
 * DESCRIPTION: List of Good/Pass results values
 *
 * ----------------------------------------------------------------------------
 */
/* list of good / OK result values */
#define RES_TEST_PASSED                 (0x0000 + RES_MIN_OK_VAL)
#define RES_SPY_INIT_OK                 (0x0001 + RES_MIN_OK_VAL)
#define RES_INIT_OK                     (0x0002 + RES_MIN_OK_VAL)
#define RES_FINISHED_OK                 (0x0003 + RES_MIN_OK_VAL)
#define RES_OK                          (0x0004 + RES_MIN_OK_VAL)
#define RES_SEPERATOR                   (0x0005 + RES_MIN_OK_VAL)
#define RES_RESET_VALUE_SEPARATOR       (0x0006 + RES_MIN_OK_VAL)
#define RES_MODULE_SEPARATOR            (0x0007 + RES_MIN_OK_VAL)
#define RES_GLOBAL_TEST_SEPARATOR       (0x0008 + RES_MIN_OK_VAL)
#define RES_ARM9_READY                  (0x0009 + RES_MIN_OK_VAL)
#define RES_ARM9_TEST_DONE              (0x000A + RES_MIN_OK_VAL)
#define RES_C55_READY                   (0x000B + RES_MIN_OK_VAL)
#define RES_C55_TEST_DONE               (0x000C + RES_MIN_OK_VAL)

#define RES_START_ARRAY                 (0x000E + RES_MIN_OK_VAL)

#define RES_NOP_VALUE                   (0x000F + RES_MIN_OK_VAL)

/* ----------------------------------------------------------------------------
 * Definition: RES_*_*
 *
 * DESCRIPTION: List of Bad/Fail results values
 *
 * ----------------------------------------------------------------------------
 */
/* list of bad / fail result values */
#define RES_TEST_FAILED                 (0x0000 + RES_MIN_BAD_VAL)
#define RES_NOT_FINISHED                (0x0001 + RES_MIN_BAD_VAL)
#define RES_FINISHED_BAD                (0x0002 + RES_MIN_BAD_VAL)
#define RES_INIT_BAD                    (0x0003 + RES_MIN_BAD_VAL)
#define RES_DEINIT_BAD                  (0x0004 + RES_MIN_BAD_VAL)
#define RES_BAD                         (0x0005 + RES_MIN_BAD_VAL)
#define RES_TIMEOUT_ERR                 (0x0006 + RES_MIN_BAD_VAL)
#define RES_BUSY                        (0x0007 + RES_MIN_BAD_VAL)

#define RES_LIB_FAIL                    (0x0010 + RES_MIN_BAD_VAL)
#define RES_READ_FAIL                   (0x0011 + RES_MIN_BAD_VAL)
#define RES_WRITE_FAIL                  (0x0012 + RES_MIN_BAD_VAL)
#define RES_RESET_FAIL                  (0x0013 + RES_MIN_BAD_VAL)
#define RES_CLEAR_FAIL                  (0x0014 + RES_MIN_BAD_VAL)
#define RES_SET_FAIL                    (0x0015 + RES_MIN_BAD_VAL)
#define RES_GET_FAIL                    (0x0016 + RES_MIN_BAD_VAL)
#define RES_ENABLE_FAIL                 (0x0017 + RES_MIN_BAD_VAL)
#define RES_DISABLE_FAIL                (0x0018 + RES_MIN_BAD_VAL)
#define RES_OPEN_FAIL                   (0x0019 + RES_MIN_BAD_VAL)
#define RES_CLOSE_FAIL                  (0x001A + RES_MIN_BAD_VAL)
#define RES_START_FAIL                  (0x001B + RES_MIN_BAD_VAL)
#define RES_STOP_FAIL                   (0x001C + RES_MIN_BAD_VAL)

#define RES_INVALID_INPUT_PARAM         (0x0020 + RES_MIN_BAD_VAL)
#define RES_DATA_MISMATCH               (0x0021 + RES_MIN_BAD_VAL)
#define RES_INPUT_CHECK_FAIL            (0x0022 + RES_MIN_BAD_VAL)
#define RES_TABLE_FULL_FAIL             (0x0023 + RES_MIN_BAD_VAL)

#define RES_EXCPT_UNDEFINED             (0x0030 + RES_MIN_BAD_VAL)
#define RES_EXCPT_PREFETCH_ABORT        (0x0031 + RES_MIN_BAD_VAL)
#define RES_EXCPT_DATA_ABORT            (0x0032 + RES_MIN_BAD_VAL)
#define RES_UNEXPECTED_INTERRUPT        (0x0033 + RES_MIN_BAD_VAL)

/* user specific range which users can define on a case by case
    basis in individual source files.  */
#define RES_USER_ERR_MIN                (0x00C0 + RES_MIN_BAD_VAL)
#define RES_USER_ERR_MAX                (0x00DF + RES_MIN_BAD_VAL)

/* beach failures */
#define RES_POR_FAIL                    (0x00E0 + RES_MIN_BAD_VAL)
#define RES_RI_FAIL_ONES                (0x00E1 + RES_MIN_BAD_VAL)
#define RES_RI_FAIL_FIVES               (0x00E2 + RES_MIN_BAD_VAL)
#define RES_RI_FAIL_AAAAS               (0x00E3 + RES_MIN_BAD_VAL)
#define RES_RI_FAIL_ZEROS               (0x00E4 + RES_MIN_BAD_VAL)
#define RES_RO_FAIL                     (0x00E5 + RES_MIN_BAD_VAL)
#define RES_WO_FAIL                     (0x00E6 + RES_MIN_BAD_VAL)
#define RES_RE_UP_POWER_ON_FAIL         (0x00E7 + RES_MIN_BAD_VAL)
#define RES_RE_UP_ONES_FAIL             (0x00E8 + RES_MIN_BAD_VAL)
#define RES_RE_UP_ZEROS_FAIL            (0x00E9 + RES_MIN_BAD_VAL)
#define RES_RE_DOWN_POWER_ON_FAIL       (0x00EA + RES_MIN_BAD_VAL)
#define RES_RE_DOWN_ONES_FAIL           (0x00EB + RES_MIN_BAD_VAL)
#define RES_RE_DOWN_ZEROS_FAIL          (0x00EC + RES_MIN_BAD_VAL)

/* writing this value will cause simulation to exit */
#define RES_INVALID_VAL                 0x00FFu

/* New addition: Refer to outside of reference the effective range outside and the size range. */
#define RES_OUTOF_OFFSET                0xFFFFu

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   RES_*_BASE
 *
 * @DESCRIPTION  Base Value (Upper Byte) for library components
 *
 *//*------------------------------------------------------------------------ */
#define RES_TESTCASE_BASE       0x0000u
#define RES_MAIN_BASE           0x0100u
#define RES_SOC_BASE            0x0200u
#define RES_CPU_BASE            0x0300u
#define RES_RES_BASE            0x0400u
#define RES_INTH_BASE           0x0500u
#define RES_MSG_BASE            0x0600u
#define RES_MBOX_BASE           0x0700u
#define RES_GPMCTL_BASE         0x0800u
#define RES_INTCTL_BASE         0x0900u
#define RES_LCDCTL_BASE         0x0a00u
#define RES_MMU_BASE            0x0b00u
#define RES_RFBIF_BASE          0x0c00u
#define RES_SDRCTL_BASE         0x0d00u
#define RES_MCASP_BASE          0x0e00u
#define RES_SSM_BASE            0x0f00u
#define RES_SYSDMA_BASE         0x1000u
#define RES_WT_BASE             0x1100u
#define RES_GPTMR_BASE          0x1200u
#define RES_WDTMR_BASE          0x1300u
#define RES_MMCSD_BASE          0x1400u
#define RES_EXCPTH_BASE         0x1500u
#define RES_SYSCFG_BASE         0x1600u
#define RES_PRCM_BASE           0x1700u
#define RES_IMTMC_BASE          0x1800u
#define RES_TMGEN_BASE          0x1900u
#define RES_TML4_BASE           0x1a00u
#define RES_IMGEN_BASE          0x1b00u
#define RES_IMARM_BASE          0x1c00u
#define RES_XBEXM_BASE          0x1d00u
#define RES_XBOCM_BASE          0x1e00u
#define RES_FWGPM_BASE          0x1f00u
#define RES_FWDSP_BASE          0x2000u
#define RES_DIGRF3G_BASE        0x2100u
#define RES_FWC2C_BASE          0x2200u
#define RES_FWRAM_BASE          0x2300u
#define RES_FWROM_BASE          0x2400u
#define RES_L4_BASE             0x2500u
#define RES_SPGPIO_BASE         0x2600u
#define RES_IPGPIO_BASE         0x2600u
#define RES_MSI2C_BASE          0x2700u
#define RES_MCBSP_BASE          0x2800u
#define RES_UART_BASE           0x2900u
#define RES_CAMCOR_BASE         0x2a00u
#define RES_CAMTOP_BASE         0x2b00u
#define RES_HDQ1W_BASE          0x2c00u
#define RES_SPI_BASE            0x2d00u
#define RES_CAMDMA_BASE         0x2e00u
#define RES_CAMMMU_BASE         0x2f00u
#define RES_VLYNQ_BASE          0x3000u
#define RES_VLYNQ2OCP_BASE      0x3100u
#define RES_ROMCODE_BASE        0x3200u
#define RES_STMR_BASE           0x3300u
#define RES_MG1_BASE            0x3400u
#define RES_MSPRO_BASE          0x3500u
#define RES_SSI_BASE            0x3600u
#define RES_ICPUSYNC_BASE       0x3700u
#define RES_UTMI2SERIAL_BASE    0x3800u
#define RES_FAC_BASE            0x3900u
#define RES_USB_BASE            0x3a00u
#define RES_DMA4_BASE           0x3b00u
#define RES_DAPCTL_BASE         0x3c00u
#define RES_L3_BASE             0x3d00u
#define RES_AESS_BASE           0x3e00u
#define RES_VIDEOCONF_BASE      0x3f00u
#define RES_DSS_BASE            0x4000u
#define RES_SYSMEM_BASE         0x4100u
#define RES_GPTTC_BASE          0x4200u
#define RES_WDTTC_BASE          0x4300u
#define RES_EMU_BASE            0x4400u
#define RES_ICONTINTC_BASE      0x4500u
#define RES_MCSIOCP_BASE        0x4600u
#define RES_SATA_IFC_BASE       0x4700u
#define RES_SATA_BASE           0x4800u
#define RES_KBDOCP_BASE         0x4900u

/* Cartier Targets Ports */
#define RES_L3TMSB2SMS_BASE     0x5000u
#define RES_L3TMSB2GPMC_BASE    0x5100u
#define RES_L3TML4_BASE         0x5200u
#define RES_L3TMSB2OCM_BASE     0x5300u
#define RES_L3TMDSPMEM_BASE     0x5400u
#define RES_L3TMGFXT_BASE       0x5500u
#define RES_L3TMC2C_BASE        0x5600u
#define RES_L3TMSPARET_BASE     0x5700u
#define RES_L3TMIVAT_BASE       0x5800u
#define RES_L3TMARM2SB_BASE     0x5900u

/* Cartier Initiators Ports */
#define RES_L3IMARM2SB_BASE     0x6000u
#define RES_L3IMPDMAR_BASE      0x6100u
#define RES_L3IMPDMAW_BASE      0x6200u
#define RES_L3IMLCD_BASE        0x6300u
#define RES_L3IMCAM_BASE        0x6400u
#define RES_L3IMIVAI_BASE       0x6500u
#define RES_L3IMC2CI_BASE       0x6600u
#define RES_L3IMUSB_BASE        0x6700u
#define RES_L3IMDSP2SB_BASE     0x6800u
#define RES_L3IMSSI_BASE        0x6900u

/* Cartier CrossBar Ports */
#define RES_L3XBSMS_BASE        0x7000u
#define RES_L3XBGPMC_BASE       0x7100u
#define RES_L3XBOCMCRAM_BASE    0x7200u
#define RES_L3XBOCMCROM_BASE    0x7300u

#define RES_DSM2G_BASE          0x8100u
#define RES_DSM3G_BASE          0x8200u
#define RES_DIGRFOCP_BASE       0x8300u
#define RES_A5OCP_BASE          0x8400u
#define RES_GEAOCP_BASE         0x8500u
#define RES_GSMTIMEOCP_BASE     0x8600u
#define RES_SDI2_BASE           0x8700u
#define RES_CSI2_BASE           0x8800u
#define RES_CPI_BASE            0x8900u
#define RES_UTILSDMA_BASE       0x8A00u
#define RES_MCPDM_BASE          0x8B00u
#define RES_MAD2D_BASE          0x8C00u
#define RES_SLIMBUS_BASE        0x8D00u

/* Monica specific IPs */
#define RES_XHPI2_BASE          0x9000u

/* writing this value to make arrays more visible */
#define RES_START_ARRAY_BASE    0xEE00u

/* Processors TC */
#define RES_IVA_TC_BASE         0xFA00u
#define RES_ICONT_TC_BASE       0xFB00u
#define RES_VDMA_TC_BASE        0xFC00u
#define RES_SIM_TC_BASE         0xFD00u
#define RES_SYS_TC_BASE         0xFE00u

/* writing this value will cause simulation to exit */
#define RES_INVALID_BASE        0xFF00u


/* ----------------------------------------------------------------------------
 * Definition: RES_BADD_VALUE
 *
 * DESCRIPTION: Value that gets written to resutls table when a value that would
 *              end simulation is written to SPY by RES_SetVar();
 *
  -----------------------------------------------------------------------------
 */
#define RES_BADD_VALUE                  0xBADDu

/* ----------------------------------------------------------------------------
 * Definition: RES_PHONY_VALUE
 *
 * DESCRIPTION: Value that gets written into resutls table inside area
 *              when Simulation end pattern is recognized.
 *
 * ----------------------------------------------------------------------------
 */
#define RES_PHONY_VALUE                 0x00ABBA00ul

/* ----------------------------------------------------------------------------
 * Definition: RES_WRAP_ID
 *
 * DESCRIPTION: Value that gets written into resutls table when wrap occures
 *
 * ----------------------------------------------------------------------------*/

#define RES_WRAP_ID                     0xF0000000ul


/* ----------------------------------------------------------------------------
 * Definition: RES_ERROR_MASK
 *
 * DESCRIPTION: Used to extract pass/fail information from Spy status
 *
 * ----------------------------------------------------------------------------
 */
#define RES_ERROR_MASK                  0x000000F0l


/*-------------------------------------------------------------------------*//**
 * @DEFINITION   RES_UNIQUIFICATION_POS
 *
 * @DESCRIPTION  UNIQUIFICATION FIELD position in the SPY message
 *
 *//*------------------------------------------------------------------------ */
#define RES_UNIQUIFICATION_POS          (16)


/* ============================================================================
 * EXPORTED TYPES
 * ============================================================================
 */


/* -----------------------------------------------------------------------*//**
 * @TYPE        spy_size_t
 *
 * @BRIEF       spy message size
 *
 * @DESCRIPTION size of the spy message, 64 or 32 depending on SPY_SIZE define
 *
 *//*----------------------------------------------------------------------- */
typedef uint32_t spy_size_t;

/* ============================================================================
 * EXPORTED VARIABLES
 * ============================================================================
 */


/* ============================================================================
 * EXPORTED FUNCTIONS/MACROS
 * ============================================================================
 */


/* -----------------------------------------------------------------------*//**
 * @FUNCTION    RES_Set
 *
 * @BRIEF       Set status to next available space in results table
 *
 * @param[in]   status        status result to be written
 *
 * @RETURNS     uint32_t  Return code
 *              RET_OK        No errors occured
 *
 * @DESCRIPTION Check if enough space
 *              Set status in table at specified index
 *
 *//*----------------------------------------------------------------------- */
uint32_t RES_Set( spy_size_t status );
uint16_t RES_Set_( uint32_t status );
#endif
