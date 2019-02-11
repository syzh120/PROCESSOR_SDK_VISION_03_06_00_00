/*
*
* Copyright (c) 2008-2017 Texas Instruments Incorporated
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
 *  @Component    TESLASS_MMU
 *
 *  @Filename     mmu.c
 *
 *  @Description  TeslaSS/Ducati L3 MMU
 *
 *//*======================================================================== */


/* =============================================================================
 * STANDARD INCLUDE FILES
 * =============================================================================
 */
#include "GlobalTypes.h"

#include "baseaddress.h"
#include "mmu.h"

/* =============================================================================
 * PROJECT SPECIFIC INCLUDE FILES
 * =============================================================================
 */

/* =============================================================================
 * GLOBAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/*-------------------------------------------------------------------------*//**
 * @VARIABLE     <Identifier>
 *
 * @BRIEF        <type> <Identifier> - <Brief description of variable>
 *
 * @DESCRIPTION  <Detailed description of variable>
 *
 *//*------------------------------------------------------------------------ */

/* =============================================================================
 * LOCAL TYPES AND DEFINITIONS
 * =============================================================================
 */

/*-------------------------------------------------------------------------*//**
 * @TYPE         <Identifier>
 *
 * @BRIEF        <Brief description of type>
 *
 * @DESCRIPTION  <Detailed description of type>
 *
 *//*------------------------------------------------------------------------ */
/* =============================================================================
 * LOCAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* =============================================================================
 * LOCAL FUNCTIONS PROTOTYPES
 * =============================================================================
 */

/*-------------------------------------------------------------------------*//**
 * @FUNCTION     Function Name
 *
 * @BRIEF        Brief description of function purpose
 *
 * @DESCRIPTION  Detailed description of function purpose
 *
 * @RETURNS      Description of return value
 *
 * @NOTES        This section is optional, delete if unused. Should contain
 *               anything else important about the function, e.g correct usage
 *
 *//*------------------------------------------------------------------------ */


/* =============================================================================
 * FUNCTIONS
 * =============================================================================
 */

/* ======================== Function Separator ============================= */
void EVE_MMU_CurrentVictimSet ( CRED_index_t component, UWORD32 tlbEntry )
{


} /* EVE_MMU_CurrentVictimSet() */



/* ======================== Function Separator ============================= */
UWORD32 EVE_MMU_CurrentVictimGet ( CRED_index_t component )
{

    UWORD32 rdVal=0;


    return rdVal;

} /* EVE_MMU_CurrentVictimGet() */



/* ======================== Function Separator ============================= */
void EVE_MMU_TlbLockSet ( CRED_index_t component, UWORD32 tlbEntry )
{

 return;
} /* EVE_MMU_TlbLockSet() */



/* ======================== Function Separator ============================= */
UWORD32 EVE_MMU_TlbLockGet ( CRED_index_t component )
{

    UWORD32 rdVal=0;

    return rdVal;

} /* EVE_MMU_TlbLockGet() */



/* ======================== Function Separator ============================= */
void EVE_MMU_GlobalFlush( CRED_index_t component )
{

	return;
} /* EVE_MMU_GlobalFlush() */


/* ======================== Function Separator ============================= */
void EVE_MMU_TlbEntryFlush( CRED_index_t component, UWORD32 virtAddress )
{

	return;
} /* EVE_MMU_GlobalFlush() */



/* ======================== Function Separator ============================= */
void EVE_MMU_SoftReset( CRED_index_t component )
{

	return;
} /* EVE_MMU_SoftReset() */



/* ======================== Function Separator ============================= */
UWORD32 EVE_MMU_IrqGetStatus ( CRED_index_t component )
{

    UWORD32 rdVal=0;

    return rdVal;

} /* EVE_MMU_IrqGetStatus() */


/* ======================== Function Separator ============================= */
void EVE_MMU_IrqClearStatus ( CRED_index_t component, MMU_IntType_t intType  )
{

	return;

} /* EVE_MMU_IrqGetStatus() */



/* ======================== Function Separator ============================= */
void EVE_MMU_IrqEnable ( CRED_index_t component, MMU_IntType_t intType )
{
	return;
} /* EVE_MMU_IrqEnable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_IrqDisable ( CRED_index_t component, MMU_IntType_t intType )
{
	return;
} /* EVE_MMU_IrqDisable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_WtlEnable ( CRED_index_t component )
{
	return;
} /* EVE_MMU_WtlEnable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_WtlDisable ( CRED_index_t component )
{
	return;
} /* EVE_MMU_WtlDisable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_Enable ( CRED_index_t component )
{
	return;
} /* EVE_MMU_Enable() */



/* ======================== Function Separator ============================= */
void EVE_MMU_Disable ( CRED_index_t component )
{
	return;
} /* EVE_MMU_Enable() */


/* ======================== Function Separator ============================= */
#ifdef VAYU_PLATFORM
ReturnCode_t EVE_MMU_TlbEntrySet_Coherency ( CRED_index_t component,
                                         UWORD32      tlbEntry,
                                         const MMU_TlbEntry_t *mmuTlbEntry,
                                         UWORD32 Coherency )

{

    ReturnCode_t returnCode = RET_OK;

    return returnCode;

} /* MMU_WriteTLBEntry() */

#endif



/* ======================== Function Separator ============================= */
ReturnCode_t EVE_MMU_TlbEntrySet ( CRED_index_t component,
                               UWORD32 tlbEntry,
                               const MMU_TlbEntry_t *mmuTlbEntry )

{

    ReturnCode_t returnCode = RET_OK;

    return returnCode;

} /* MMU_WriteTLBEntry() */


/* ======================== Function Separator ============================= */
#ifdef VAYU_PLATFORM
ReturnCode_t EVE_MMU_TlbEntrySet_Extended ( CRED_index_t component,
                                        UWORD32 tlbEntry,
                                        const MMU_TlbEntry_extended_t *mmuTlbEntry_extended )

{

    ReturnCode_t returnCode = RET_OK;


    return returnCode;

} /* MMU_WriteTLBEntry_Extended() */
#endif
/* ============================================================================*/
/*              MMU_SuperSection                                               */
/* ============================================================================*/
ReturnCode_t EVE_MMU_SuperSection(
                             const UWORD32      physicalAddr,
                             const UWORD32      virtualAddr,
                             const UWORD32      TTB ,
                             MMU_Endianness_t     endianism,
                             MMU_ElementSize_t   elementSizeA,
                             MMUMixedSize_t     mixedSize,
                             MMUFault_t         faultType
                             )
{
   ReturnCode_t returnCode = RET_OK;

   return returnCode;
}

/* ============================================================================*/
/*               MMU_Section                                                   */
/* ============================================================================*/
ReturnCode_t EVE_MMU_Section(
                        const UWORD32      physicalAddr,
                        const UWORD32      virtualAddr,
                        const UWORD32      TTB ,
                        MMU_Endianness_t     endianism,
                        MMU_ElementSize_t   elementSizeB,
                        MMUMixedSize_t     mixedSize,
                        MMUFault_t         faultType
                        )
{
   ReturnCode_t returnCode = RET_OK;
   return returnCode;
}


/* ============================================================================*/
/*                MMU_CoarseLargePage                                          */
/* ============================================================================*/
ReturnCode_t EVE_MMU_CoarseLargePage(
                                const UWORD32      physicalAddr,
                                const UWORD32      virtualAddr,
                                const UWORD32      TTB,
                                const UWORD32      pageTableBase,
                                MMU_Endianness_t     endianism,
                                MMU_ElementSize_t   elementSize__,
                                MMUMixedSize_t     mixedSize,
                                MMUFault_t         faultType
                                )
{
   ReturnCode_t returnCode = RET_OK;
   return returnCode;
}


/* ============================================================================*/
/*                  MMU_CoarseSmallPage                                        */
/* ============================================================================*/
ReturnCode_t EVE_MMU_CoarseSmallPage(
                                const UWORD32      physicalAddr,
                                const UWORD32      virtualAddr,
                                const UWORD32      TTB,
                                const UWORD32      pageTableBase,
                                MMU_Endianness_t     endianism,
                                MMU_ElementSize_t   elementSize_,
                                MMUMixedSize_t     mixedSize,
                                MMUFault_t         faultType
                                )
{
   ReturnCode_t returnCode = RET_OK;

   return returnCode;
}



/* =============================================================================
 * LOCAL FUNCTIONS
 * =============================================================================
 */


/* EOF */

