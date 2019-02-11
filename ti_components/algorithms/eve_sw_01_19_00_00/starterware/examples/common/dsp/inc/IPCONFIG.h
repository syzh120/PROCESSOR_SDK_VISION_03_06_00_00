/*
*
* Copyright (c) 2006-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/**
 *  @Component   ATTILA
 *  @Filename    IPCONFIG.h
 *  @Description This header defines versions of the HW IP in order to handle
 *               the sharig of the same driver library code by multiple versions
 *               of the same IP.
 *               More details here: 
 * http://www.tif.ti.com/omap_validation/projects/sw_common/TechnicalMemo/TechnicalMemo_ProjectIfdefsInSharedLibs.html  
 *
 *//*======================================================================== */

#ifndef __IPCONFIG_H
#define __IPCONFIG_H

/* =============================================================================
 * INCLUDE FILES (only if necessary)
 * =============================================================================
 */

#ifdef __cplusplus
extern 
{
#endif

/* =============================================================================
 * EXPORTED DEFINITIONS
 * =============================================================================
 */

/* Define the versions here, keep following rules
 *  - use IPCONFIG prefix
 *  - use IP abbreviation for easy identification (match to the driver library)
 *  - use hexadecimal representation (not mandatory - gives only higher range)
 *  - keep 8digits
 * Example:
 * #define IPCONFIG_GPMC 0x0000123  -- GPMC version 1.2.3 
 * #define IPCONFIG_GPMC 0x000012A  -- GPMC version 1.2.10 
 */
#ifdef CORTEXA8
 #define ICONT1_MMR__IRQ IVAHD0__ICONT1_MMR__IRQ  /* have defined this variable inside IPCONFIG.h */
#endif 

#define IPCONFIG_DMA4 0x00000500 /* DMA4 version 5.00 */
#define IPCONFIG_GPMC 0x00000500 /* GPMC version 5.00 */
#define IPCONFIG_SDRC 0x00000400 /* SDRC version 4.00 */
#define IPCONFIG_LCD  0x00000500 /* LCD  arch v5 */
#define IPCONFIG_PDMA	0x20070614 /* Generation time: Jun 14 2007 21:01:36 */

/* 
 * define other common constants 
 */

/* Number of IRQ lines in interrupt controller - ARM9 & C55 */
#define IPCONFIG_INTCTL_IRQ_LINES   96

/* Using INTCPS for interrupt controller for ARM9 & C55 */
#define IPCONFIG_INTCPS

/* Number of Mailboxes */
#define IPCONFIG_MBOX_NUMBER        8


/* New PRCM API */
#define IPCONFIG_PRCM_API           2 /* 2nd version of the PRCM API */

/* Define various Power Management Companion chips
 * Triton (EC, ULC, 2)
 * TEJAS
 */
#define IPCONFIG_TRITON_EC    0x00000110
#define IPCONFIG_TRITON_ULC   0x00000120
#define IPCONFIG_TRITON_2     0x00000200
#define IPCONFIG_TEJAS        0x00000300
/* Define Usage of PRCM HAL library for cores */
#ifdef CORTEXA8
    #define IPCONFIG_USE_PRCM_HAL   2
#endif

/* Define PMC chip used with this project */
#define IPCONFIG_PMC          IPCONFIG_TEJAS

/* Define SPI Revision ID */
#define IPCONFIG_SPI	0x21
/* Define GPIO */
#define IPCONFIG_GPIO  

/* Define VLYNQ */
#define IPCONFIG_VLYNQ  0x10

/* Define MCASP */
#define IPCONFIG_MCASP  0x11

/* Define WDT */
#define IPCONFIG_WDT  0x12

#define IPCONFIG_MSI2C  0x000003d0

/* Define DMTIMER ID */
#define IPCONFIG_DMTIMER 0x7
/* Define SYNCTIMER32K */
#define IPCONFIG_SYNCTIMER32K
/* Specman synchronization GPIO port and lines */
#define IPCONFIG_ESYNC_USE_GPIO
#define IPCONFIG_ESYNC_SYNC_PORT         GPIO0
#define IPCONFIG_ESYNC_SYNC_PORT_PRCM    prcm_gpio0
#define IPCONFIG_ESYNC_READY_PORT        GPIO0
#define IPCONFIG_ESYNC_READY_PORT_PRCM   prcm_gpio0

#define IPCONFIG_ESYNC_SYNC_LINE        6 
#define IPCONFIG_ESYNC_READY_LINE       7

#define IPCONFIG_RESEXT_SWVER           0   
#ifdef __cplusplus
}
#endif
#endif	/* __IPCONFIG_H */
/* EOF */

