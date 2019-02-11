/*
*
* Copyright (c) 2007-2017 Texas Instruments Incorporated
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
 *  @Component		MBOX - Mailbox library component
 *  @Filename		mbox.c
 *  @Description    The mailbox library component offers basic mailbox
 *                  functionality that can be used to transmit 32-bit messages
 *                  between CPUs using the OMAP4.0 Mailbox
 *
 *//*======================================================================== */

/* =============================================================================
 * STANDARD INCLUDE FILES
 * =============================================================================
 */

/* =============================================================================
 * PROJECT SPECIFIC INCLUDE FILES
 * =============================================================================
 */
#include "GlobalTypes.h"
#include "baseaddress.h"
#include "mbox.h"

/* =============================================================================
 * GLOBAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* =============================================================================
 * LOCAL TYPES AND DEFINITIONS
 * =============================================================================
 */
/* width/mask in bits of MBOX Id */
#define MBOX_ID_WIDTH           2
#define MBOX_ID_MASK            0x3

/****************************************************************/

/* =============================================================================
 * LOCAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* =============================================================================
 * LOCAL FUNCTIONS PROTOTYPES
 * =============================================================================
 */

/* =============================================================================
 * FUNCTIONS
 * =============================================================================
 */

UWORD32 EVE_MBOX_Read( CRED_index_t  component,
	               MBOX_Id_t     mailBoxId)
{
    UWORD32 message = 0;
    return message;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_Write( CRED_index_t  component,
                 MBOX_Id_t     mailBoxId,
                 UWORD32       writeValue )
{
    return;
}

/* ======================== Function Separator ============================= */
ReturnCode_t EVE_MBOX_Reset( CRED_index_t  component )
{    
    ReturnCode_t returnCode = RET_OK;

    return returnCode;
}

/* ======================== Function Separator ============================= */

BOOL EVE_MBOX_IsFull( CRED_index_t  component,
                  MBOX_Id_t     mailBoxId )
{
    BOOL returnValue = true;

    return returnValue;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_GetNumMsg(
                       CRED_index_t  component,
    	               MBOX_Id_t     mailBoxId
                      )
{
    UWORD32       NumMsg = 0;
    return NumMsg;
} /* MBOX_GetNumMsg() */

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqEnable( CRED_index_t    component,
	                 MBOX_Id_t       mailBoxId,
                     MBOX_UserId_t   userId,
                     MBOX_Int_t      enableIrq )
{

    return;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqDisable( CRED_index_t    component,
                      MBOX_Id_t       mailBoxId,
                      MBOX_UserId_t   userId,
                      MBOX_Int_t      disableIrq )
{

    return;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_IrqGetStatus( CRED_index_t    component,
			   MBOX_Id_t       mailBoxId,
                           MBOX_UserId_t   userId )
{
    UWORD32      irqStatusReg = 0;

    return irqStatusReg;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_IrqGetStatusMboxId( MBOX_Id_t       mailBoxId,
                                 UWORD32         irqStatus )
{
    UWORD32 mbox_irqStatus = 0;

    return mbox_irqStatus;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqClearStatus( CRED_index_t     component,
                          MBOX_UserId_t    userId,
                          UWORD32          irqStatus )
{
    return;
}
