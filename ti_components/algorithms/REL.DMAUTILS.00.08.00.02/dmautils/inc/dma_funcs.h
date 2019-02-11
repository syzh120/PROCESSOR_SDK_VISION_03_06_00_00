/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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
 *  @file       dma_functions.h
 *
 *  @brief      This header defines functions to use EDMA
 */

#ifndef DMA_FUNCS_H
#define DMA_FUNCS_H

/*-----------------------------------------------------------------------*/
/*  These are the include files that are needed for edma/qdma.           */
/*-----------------------------------------------------------------------*/
/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
/*#pragma RESET_MISRA ("required")*/


/*#pragma CHECK_MISRA ("none")*/
#include "csl_edma.h"
#include "cslr_edmacc.h"
/*#pragma RESET_MISRA ("required")*/

/*#pragma CHECK_MISRA ("none")*/
#include "stdint.h"
/*#pragma RESET_MISRA ("required")*/

#include "dma_resource.h"

#ifdef _MSC_VER /* If using MS Visual Studio C Compiler */
    #define inline            __inline
#endif

/** ======================= ============================
 *  @name   DMA_TransferStatus
 *
 *  @desc   Describes the status of DMA transfer of a particular channel
 *
 *  @field  DMA_TRANSFER_STATUS_ACTIVE
 *             Transfer is active for this particular channel
 *
 *  @field  DMA_TRANSFER_STATUS_INACTIVE
 *             Transfer is completed for this particular channel
 *  ====================================================
 */
typedef enum
{
    DMA_TRANSFER_STATUS_INACTIVE,
    DMA_TRANSFER_STATUS_ACTIVE
}DMA_TransferStatus;


/* ==================================================
*  @func     pack2
*
*  @desc   This function packs two 16 bit data into one 32 bit data. This function is
*               mainly used for populating some fields of param set
*
*  @modif    NONE
*
*  @inputs   This function takes following Inputs
*                 hi : 16 bit data that should goto upper 16 bit of 32 bit data
*                 lo : 16 bit data that should goto lower 16 bit of 32 bit data
*
*  @outputs NONE
*
*  @return    32 bit data with lower 16 bits coming from lo and upper 16 bits coming from ho
*
*  =======================================================
*/
static inline uint32_t pack2 (uint16_t hi, uint16_t lo);

/* ==================================================
*  @func     pack2
*
*  @desc   This function packs two 16 bit data into one 32 bit data. This function is
*               mainly used for populating some fields of param set
*
*  @modif    NONE
*
*  @inputs   This function takes following Inputs
*                 hi : 16 bit data that should goto upper 16 bit of 32 bit data
*                 lo : 16 bit data that should goto lower 16 bit of 32 bit data
*
*  @outputs NONE
*
*  @return    32 bit data with lower 16 bits coming from lo and upper 16 bits coming from ho
*
*  =======================================================
*/
/* CHECK_MISRA("-8.5")  -> Disable rule 8.5  */
/* MISRA.ONEDEFRULE.FUNC:   Global function definition in a header file*/
/* Coding convention, downgraded to advisory in 2012 */
static inline uint32_t pack2 (uint16_t hi, uint16_t lo)
{
    uint32_t retVal;
    uint32_t temp = ((uint32_t)hi & 0x0000FFFFU);
    retVal = ((temp << 16U) & 0xFFFF0000U) | ((uint32_t)lo & 0x0000FFFFU);
    return (retVal);
}
/* RESET_MISRA("8.5")  -> Reset rule 8.5 for  MISRA.ONEDEFRULE.FUNC  */

/* Following Declaration are needed by Misra C */
inline void DMA_SUBMIT(CSL_EdmaccRegsOvly edmaCc , uint32_t submit_word);

inline void DMA_WAIT(CSL_EdmaccRegsOvly edmaCc , uint32_t wait_word);

inline void QDMA_SUBMIT(volatile uint32_t * trigWordAddr , uint32_t value);

inline void QDMA_WAIT(CSL_EdmaccRegsOvly edmaCc , uint32_t wait_word);


/* ==================================================
*  @func     DMA_SUBMIT
*
*  @desc   This function triggers EDMA transfer for the channels described by submit word by
*               writing the submit word in ESR register
*
*  @modif    edmaCc
*
*  @inputs   This function takes following Inputs
*                 edmaCc :
*                       Pointer to the EDMA CC structure
*                 submit_word :
*                       Submit word containing the set of channels which you want to trigger. Setting bit
*                       positions in submit word triggers the event corresponding the the bit position
*
*
*  @outputs NONE
*
*  @return    NONE
*
*  =======================================================
*/
/* CHECK_MISRA("-8.5")  -> Disable rule 8.5  */
/* MISRA.ONEDEFRULE.FUNC:   Global function definition in a header file*/
/* Coding convention, downgraded to advisory in 2012 */

inline void DMA_SUBMIT(CSL_EdmaccRegsOvly edmaCc , uint32_t submit_word)
{
    edmaCc->ESR  = submit_word;
}
/* RESET_MISRA("8.5")  -> Reset rule 8.5 for  MISRA.ONEDEFRULE.FUNC  */

/* ==================================================
*  @func     DMA_WAIT
*
*  @desc   This function waits for the completion of EDMA transfers indicated by bit position in
*               wait word. It also clears the IPR register by writing to 1 to the bits position indicated
*               by wait word
*
*  @modif    edmaCc
*
*  @inputs   This function takes following Inputs
*                 edmaCc :
*                       Pointer to the EDMA CC structure
*                 wait_word :
*                       Wait containing the set of channels for which you want to wait.
*
*  @outputs NONE
*
*  @return    NONE
*
*  =======================================================
*/
/* CHECK_MISRA("-8.5")  -> Disable rule 8.5  */
/* MISRA.ONEDEFRULE.FUNC:   Global function definition in a header file*/
/* Coding convention, downgraded to advisory in 2012 */

inline void DMA_WAIT(CSL_EdmaccRegsOvly edmaCc , uint32_t wait_word)
{
    while  ((edmaCc->IPR & (wait_word)) != (wait_word)){}
    edmaCc->ICR  = wait_word;
}
/* RESET_MISRA("8.5")  -> Reset rule 8.5 for  MISRA.ONEDEFRULE.FUNC  */


/* ==================================================
*  @func     QDMA_SUBMIT
*
*  @desc   This function is used to trigger QDMA transfer. It's
*          user of this functions responsibility to provide the
*          address of the trigger word writing at which will
*          trigger the QDMA transfers. This function is only
*          aplicable for QDMA channels and should not be used
*          for EDMA channels
*
*  @modif    edmaCc
*
*  @inputs   This function takes following Inputs
*                 trigWordAddr :
*                       This is the address of the trigger word, writing
*                       here will trigger the QDMA transfer. This address
*                       can be computed using baseParam and trigWordIndex fields
*                       of DMA_resourceStruct.
*                       trigWordAddr = baseParam + trigWordIndex;
*                 value :
*                       The value to be written at triggerword for QDMA
*                       channel. It is important to note that it is user's
*                       responsibility to provide correct value for paramEntry
*                       which are 16 bits. User should pack two 16 bit data
*                       into 32 bit data if he/she wants to use those fields
*                       as triggerWord.
*
*  @outputs NONE
*
*  @return    NONE
*
*  =======================================================
*/
/* CHECK_MISRA("-8.5")  -> Disable rule 8.5  */
/* MISRA.ONEDEFRULE.FUNC:   Global function definition in a header file*/
/* Coding convention, downgraded to advisory in 2012 */

inline void QDMA_SUBMIT(volatile uint32_t * trigWordAddr , uint32_t value)
{
    *trigWordAddr = value;
}
/* RESET_MISRA("8.5")  -> Reset rule 8.5 for  MISRA.ONEDEFRULE.FUNC  */



/* ==================================================
*  @func     QDMA_WAIT
*
*  @desc   This function waits for the completion of QEDMA transfers indicated
*          by bit position in wait word. It also clears the IPR register by
*          writing to 1 to the bits position indicated by wait word
*
*  @modif    edmaCc
*
*  @inputs   This function takes following Inputs
*                 edmaCc :
*                       Pointer to the EDMA CC structure
*                 wait_word :
*                       Wait containing the set of channels for which you want to wait.
*
*  @outputs NONE
*
*  @return    NONE
*
*  =======================================================
*/
/* CHECK_MISRA("-8.5")  -> Disable rule 8.5  */
/* MISRA.ONEDEFRULE.FUNC:   Global function definition in a header file*/
/* Coding convention, downgraded to advisory in 2012 */

inline void QDMA_WAIT(CSL_EdmaccRegsOvly edmaCc , uint32_t wait_word)
{
    while  ((edmaCc->IPR & (wait_word)) != (wait_word)){}
    edmaCc->ICR  = wait_word;
}
/* RESET_MISRA("8.5")  -> Reset rule 8.5 for  MISRA.ONEDEFRULE.FUNC  */

/* ==================================================
 *  @func     DMA_funcs_hardwareRegSetup
 *
 *  @desc   This function updates the actual hardware register based on
 *          DMA_resourceStruct. For QDMA we will be setting up QCHMAP,
 *          QDMAQNUM, QEESR. Similarly for EDMA we will be setting
 *          up, DCHMAP, DMAQNUM. Independent of QDMA and EDMA we configure
 *          QUEWTHRA, QUEPRI and QUETCMAP registers.
 *          In current implementation there is a one to one mapping
 *          between transfer controllers and hardware queues. TC0 is
 *          mapped to Q0 and TC1 is mapped to Q1, this means Q0 submits
 *          on TC0 and Q1 submits on TC1.
 *          More over Q0 is given a higher priority compare to Q1.
 *
 *
 *  @modif    This function modifies edmaCc
 *
 *  @inputs   This function takes following Inputs
 *                  edmaCc :
 *                      Pointer to the address space of EDMA module
 *                  edmaResources :
 *                      Pointer to the resource Structure as defined in dma_resource.h
 *
 *  @outputs NONE
 *
 *   @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
int32_t DMA_funcs_hardwareRegSetup(CSL_EdmaccRegsOvly edmaCc,
                                const DMA_resourceStruct * edmaResources);

/* ==================================================
 *  @func     DMA_funcs_writeTransferParams
 *
 *  @desc     This function populates the param set based on the inputs
 *
 *  @modif    This function modifies param set
 *
 *  @inputs   This function takes following Inputs
 *                  tparam :
 *                      Trigger param where you want to write
 *                  optWord :
 *                      Opt word for the param set corresponding to the
 *                      channel number given
 *                  srcPtr :
 *                      Pointer to the source
 *                  dstPtr :
 *                      Pointer to the destination
 *                  noBytes :
 *                      Number of bytes to be transfered (Acnt)
 *                  noLines :
 *                      Number of lines of noBytes (Bcnt)
 *                  srcLinePitch :
 *                      Pitch for the source pointer
 *                  dstLinePitch :
 *                      Pitch for the destination pointer
 *                  srcNextBlkOffset :
 *                      Offset for the next block in for source
 *                  dstNextBlkOffset :
 *                      Offset for the next block for destination
 *                  numAutoIncr :
 *                      Number of times autoincrement to be executed (Ccnt)
 *                  linkAddr :
 *                      Link address for the cases when you want to link
 *                      one param set to another
 *                      Default value = 0, in this case it will write 0xFFFF
 *
 *  @outputs NONE
 *
 *
 *  =======================================================
 */
 /* This decleration violates MISRA-C Rule 16.7 : MISRA.PPARAM.NEEDS.CONST.
 This cannot be avoided because dstPtr is actually modified by the EDMA hardware
 but from the code compiler cannot detect this and hence returns a warning */
void DMA_funcs_writeTransferParams(volatile uint32_t tparam[8], uint32_t optWord,
                    const uint8_t *srcPtr, uint8_t *dstPtr, uint16_t noBytes, uint16_t noLines,
                    int16_t srcLinePitch, int16_t dstLinePitch, int16_t srcNextBlkOffset,
                    int16_t dstNextBlkOffset, uint16_t numAutoIncr, uint16_t linkAddr);



#endif /*DMA_FUNCS_H*/
/*!
*! Revision History
*! ================
*! 16-Oct-2013   Anshu: Initial Draft
*/

