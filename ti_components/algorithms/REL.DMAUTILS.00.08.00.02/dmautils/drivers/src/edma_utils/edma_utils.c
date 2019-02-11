/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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

/*
*******************************************************************************
*
* EDMA utility functions
*
*******************************************************************************
*/

/**
*****************************************************************************
* @file
*  edma_utils.c
*
* @brief    This function implements functions which can be used accross all usecases
*
* @author: Anshu Jain (anshu_jain@ti.com)
*
* @version 0.1 (Aug 2013) : First version of edma utils
*
*****************************************************************************
*/

#include "edma_utils.h"

/*#pragma CHECK_MISRA ("none")*/
#include "csl_edma.h"
#include "cslr_edmacc.h"
/*#pragma RESET_MISRA ("required")*/


#include "dma_funcs.h"
#include "dma_resource_allocator.h"
#include "edma_utils_state.h"

#ifdef HOST_EMULATION

CSL_EdmaccRegs dummyEDMAreg;
uint32_t edmaBase[1] = {(uint32_t)(&dummyEDMAreg)};

#else

/**< Pointer to the start of EDMA CC0 */
/* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
/* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
/* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
   The address space is 32 bit and type casting to integer will not result into any loss because of TI's
 compiler teratment to integer.   */
const volatile  uint32_t edmaBase[1] = {(uint32_t)CSL_EDMACC_0_REGS};
/*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

#endif

/* ==================================================
*  @func     EDMA_UTILS_setEdma3RmHandle
*
*  @desc   This is first function which should be called before calling any
*               utility function ane even before EDMA_UTILS_globalReset function is called.
*               This function sets the EDMA3 LLD handle which will be used for resource
*               allocation. User can pass the handle as NULL also for the cases he/she doesnt
*               want to use EDMA3 LLD.
*
*  @modif    NONE
*
*  @inputs   edma3RmHandle : Handle to the EDMA3 LLD resoruce manager instance
*                 This can take value as NULL for the cases where user doesnt want to use
*                 EDMA3 LLD
*
*  @outputs NONE
*
*  @return    NONE
*
*  =======================================================
*/
void  EDMA_UTILS_setEdma3RmHandle(EDMA3_RM_Handle edma3RmHandle)
{
    DMA_resourceAllocator_setEdma3RmHandle(edma3RmHandle);
}


/* ==================================================
*  @func     EDMA_UTILS_globalReset
*
*  @desc   This function resets the global utils state structure which contains
*          all resources allocatred for different utility usecases also it
*          releases all the resources allocated by resources mangaer so far.
*          This function should be called once before using EDMA utilities
*
*  @modif    NONE
*
*  @inputs   NONE
*
*  @outputs NONE
*
*  @return    NONE
*
*  =======================================================
*/
void  EDMA_UTILS_globalReset(void)
{
  /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
  /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
  /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
     The address space is 32 bit and type casting to integer will not result into any loss because of TI's
   compiler teratment to integer.   */
    const CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)edmaBase[0];
  /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */

  /* If we are not using EDMA3LLD then just set the EDMA3 RM handle to NULL */
#ifndef USE_EDMA3LLD
    DMA_resourceAllocator_setEdma3RmHandle(NULL);
#endif

    /* Reset global Utility State Structure */
    DMA_utils_resetStateStruct();

    /* Initalize all the resources in resource allocator */
    DMA_resourceAllocator_initResources();

    /* Clear All pending interrupts so as to start with clear state */
    if ( gEdmaCc->IPR != 0 )
    {
#ifdef DEBUG
        printf ("Warning : EDMA_UTILS_globalReset - Previous IPR registers are not cleared \n");
#endif
        gEdmaCc->ICR= gEdmaCc->IPR;
        gEdmaCc->ICRH= gEdmaCc->IPRH;
    }
    gEdmaCc->QEECR = 0xFFU;

}

