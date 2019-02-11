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

/*
 *   @Component    MBOX - Mailbox library component
 *
 *   @Filename     mbox.h
 *
 *   @Description  The mailbox library component offers basic mailbox
 *                 functionality that can be used to transmit 32-bit messages
 *                 between CPUs using the OMAP4.0 Mailbox
 *
 *   Available Functions:
 *             EVE_MBOX_Read - Read a value for specificed mailbox
 *             EVE_MBOX_Write - Write value to specified mailbox
 *             EVE_MBOX_Reset - Soft Reset Mailbox
 *             EVE_MBOX_IsFull - Check if mailbox Full
 *             EVE_MBOX_GetNumMsg - Get Number of Messages in a mailbox
 *             EVE_MBOX_IrqEnable - Enable Interrupt for user/mailbox
 *             EVE_MBOX_IrqDisable - Clear Enable Interrupt for user/mailbox
 *             EVE_MBOX_IrqGetStatus - Get Interrupt Status for user/mailbox
 *             EVE_MBOX_IrqGetStatusAll - Get Interrupt Status for all mailboxes /1 user
 *             EVE_MBOX_IrqGetValue - calculates one mailbox irq status from all
 *             EVE_MBOX_IrqClearStatus - Clears Interrupt Status for user/mailbox
 *
 *  Domain:                 common
 *//*======================================================================== */
/**
*  @file       mbox.h
*
*  @brief      The mailbox library component offers basic mailbox
*              functionality that can be used to transmit 32-bit messages
*              between CPUs using the OMAP4.0 Mailbox
*
*  This header provides all mailbox APIs supported by EVE
*
*/
#ifndef MBOX_H
#define MBOX_H

/* ============================================================================
 * INCLUDE FILES (only if necessary)
 * =============================================================================
 */
#ifdef __cplusplus
extern "C"
{
#endif

/* ============================================================================
 * EXPORTED DEFINITIONS
 * ============================================================================
 */

/* -----------------------------------------------------------------------*//**
 * @def          MBOX_MAX_NUM_MESSAGES
 *
 * @brief        Maximum number of messages
 *
 * @details      Maximum number of messages that mailbox can hold at a time.
 *
 *//*----------------------------------------------------------------------- */

#define MBOX_MAX_NUM_MESSAGES       4

/* ============================================================================
 * EXPORTED TYPES
 * ============================================================================
 */

/* -----------------------------------------------------------------------*//**
 * @brief         MBOX_Id_t
 *
 * @brief        Mail Box Id Number
 *
 * @details      Enumerated Type used to specify Mail Box Sub Module Id Number
 *
 *//*----------------------------------------------------------------------- */

typedef enum MBOX_Id_label
{
    MBOX_ID_0 = 0,           /**< Mailbox ID 0 */
    MBOX_ID_1 = 1,               /**< Mailbox ID 1 */
    MBOX_ID_2 = 2,               /**< Mailbox ID 2 */
    MBOX_ID_3 = 3,               /**< Mailbox ID 3 */
    MBOX_ID_4 = 4,               /**< Mailbox ID 4 */
    MBOX_ID_5 = 5,               /**< Mailbox ID 5 */
    MBOX_ID_6 = 6,               /**< Mailbox ID 6 */
    MBOX_ID_7 = 7,               /**< Mailbox ID 7 */
    MBOX_ID_MAX = MBOX_ID_7 /**< Maximum Mailbox ID */
} MBOX_Id_t, *pMBOX_Id_t;   /**< MBOX_Id_t, *pMBOX_Id_t */

/* -----------------------------------------------------------------------*//**
 * @brief         MBOX_UserId_t
 *
 * @brief        Mail box User Id
 *
 * @details      Enumerated Type used to specify Mail box User Id
 *
 *//*----------------------------------------------------------------------- */

typedef enum MBOX_UserId_label
{
    MBOX_USER_0 = 0,            /**< mailbox user id 0 */
    MBOX_USER_1 = 1,                /**< mailbox user id 1 */
    MBOX_USER_2 = 2,                /**< mailbox user id 2 */
    MBOX_USER_3 = 3,                /**< mailbox user id 3 */
    MBOX_USER_MAX = MBOX_USER_3 /**< max mailbox user id  */
} MBOX_UserId_t, *pMBOX_UserId_t; /**< MBOX_UserId_t, *pMBOX_UserId_t */

/* -----------------------------------------------------------------------*//**
 * @brief         MBOX_Int_t
 *
 * @brief        Interrupt status of User
 *
 * @details      Enumerated Type used to specify Interrupt status of User for
 *                a particular mail box submodule
 *
 *//*----------------------------------------------------------------------- */

typedef enum MBOXInt_label
{
    MBOX_INT_NONE          = 0,              /**< NONE          */
    MBOX_INT_NEW_MSG_ONLY  = 1,              /**< NEW_MSG_ONLY  */
    MBOX_INT_NOT_FULL_ONLY = 2,              /**< NOT_FULL_ONLY */
    MBOX_INT_BOTH          = 3,              /**< BOTH          */
    MBOX_INT_MAX = MBOX_INT_BOTH             /**< MAX interrupt label */
} MBOX_Int_t, *pMBOX_Int_t;                  /**< MBOX_Int_t, *pMBOX_Int_t */

/* ============================================================================
 * EXPORTED VARIABLES
 * ============================================================================
 */

/* ============================================================================
 * EXPORTED FUNCTIONS
 * ============================================================================
 */

/* -----------------------------------------------------------------------*//**
 * @brief          EVE_MBOX_Read
 *
 * @brief       Reads a UWORD32 from the mbox
 *
 * @param[in]   component    Name of the component
 * @param[in]   mailBoxId    Mail Box Sub module Id to read
 *
 * @return      UWORD32                    message reads from MBox
 *
 * @details     This function reads a UWORD32 from the sub module message
 *              box Specified.
 *              It is the responsibility of the user to check if there is a
 *              message available, otherwise result is undefined
 *
 *//*----------------------------------------------------------------------- */
extern UWORD32 EVE_MBOX_Read( CRED_index_t  component,
                          MBOX_Id_t     mailBoxId );

/* -----------------------------------------------------------------------*//**
 * @brief          EVE_MBOX_Write
 *
 * @brief       Writes a UWORD32 to mbox
 *
 * @param[in]   component    Name of the component
 * @param[in]   mailBoxId    Mail Box Sub module Id to read
 * @param[in]   writeValue   Value to write to MailBox
 *
 * @return       void
 *
 * @details     This function writes a UWORD32 from the sub module message
 *              box Specified.
 *
 *//*----------------------------------------------------------------------- */
extern void EVE_MBOX_Write( CRED_index_t component,
                        MBOX_Id_t    mailBoxId,
                        UWORD32      writeValue );

/* -----------------------------------------------------------------------*//**
 * @brief          EVE_MBOX_Reset
 *
 * @brief       Soft reset of the mbox
 *
 * @param[in]   component    Name of the component
 *
 * @return      ReturnCode_t    RET_OK                   No errors occured
 *                              RET_BAD_NULL_PARAM       Address paramater set to 0
 *                              RET_TIMEOUT              Timeout occurs while
 *                                                       waiting for reset
 *
 * @details     This function does a soft reset of the Mailbox module
 *              and waits reset to complete
 *
 *//*----------------------------------------------------------------------- */
extern ReturnCode_t EVE_MBOX_Reset( CRED_index_t component );

/* -----------------------------------------------------------------------*//**
 * @brief          EVE_MBOX_IsFull
 *
 * @brief       Reads full status of mbox
 *
 * @param[in]   component    Name of the component
 * @param[in]   mailBoxId    Mail Box Sub module Id to read
 *
 * @return      BOOL          False means mail box is not Full
 *                            True means mailbox full.
 *
 * @details     This function reads the full status register for mailbox.
 *
 *//*----------------------------------------------------------------------- */
extern BOOL EVE_MBOX_IsFull( CRED_index_t  component,
                         MBOX_Id_t     mailBoxId );

/* -----------------------------------------------------------------------*//**
 * @brief          EVE_MBOX_GetNumMsg
 *
 * @brief       Gets number of messages in mbox
 *
 * @param[in]   component    Name of the component
 * @param[in]   mailBoxId    Mail Box Sub module Id to read
 *
 * @return       UWORD32       Number of messages in mailbox
 *
 * @details     This function gets number of messages in a specified mailbox.
 *
 *//*----------------------------------------------------------------------- */
extern UWORD32 EVE_MBOX_GetNumMsg( CRED_index_t  component,
                               MBOX_Id_t     mailBoxId );

/* -----------------------------------------------------------------------*//**
 * @brief          EVE_MBOX_IrqEnable
 *
 * @brief       Enables irq
 *
 * @param[in]   component    Name of the component
 * @param[in]   mailBoxId    Mail Box Sub module Id to read
 * @param[in]   userId       Mail box User Id to enable
 * @param[in]   enableIrq    Irq value to enable
 *
 * @return      void
 *
 * @details     This function enables the specified IRQ.
 *
 *//*----------------------------------------------------------------------- */
extern void EVE_MBOX_IrqEnable( CRED_index_t    component,
                            MBOX_Id_t       mailBoxId,
                            MBOX_UserId_t   userId,
                            MBOX_Int_t      enableIrq );

/* -----------------------------------------------------------------------*//**
 * @brief          EVE_MBOX_IrqDisable
 *
 * @brief       Clear the enable irq bit fields
 *
 * @param[in]   component    Name of the component
 * @param[in]   mailBoxId    Mail Box Sub module Id to read
 * @param[in]   userId       Mail box User Id to enable
 * @param[in]   disableIrq   Irq value to disable
 *
 * @return      void
 *
 * @details     This function clear the enable irq bit fields for specified IRQ.
 *
 *//*----------------------------------------------------------------------- */
extern void EVE_MBOX_IrqDisable( CRED_index_t    component,
                             MBOX_Id_t       mailBoxId,
                             MBOX_UserId_t   userId,
                             MBOX_Int_t      disableIrq );

/* -----------------------------------------------------------------------*//**
 * @brief          EVE_MBOX_IrqGetStatus
 *
 * @brief       Gets the status of irqs of userId
 *
 * @param[in]   component    Name of the component
 * @param[in]   mailBoxId    Mail Box Sub module Id to read
 * @param[in]   userId       Mail box User Id to enable
 *
 * @return      UWORD32      irqstatus values
 *
 * @details     This function gets the status of IRQs for specified userID.
 *
 *//*----------------------------------------------------------------------- */
extern UWORD32 EVE_MBOX_IrqGetStatus( CRED_index_t    component,
                                 MBOX_Id_t       mailBoxId,
                                 MBOX_UserId_t   userId );

/* -----------------------------------------------------------------------*//**
 * @brief          EVE_MBOX_IrqGetStatusMboxId
 *
 * @brief       Gets the irq status of MailBoxId
 *
 * @param[in]   mailBoxId       Mail Box Sub module Id to read
 * @param[in]   irqStatus        irqstatus register values
 *
 * @return      UWORD32    value in IRQ status register of mailBoxId
 *
 * @details        This function gets the irq status of MailBoxId from
 *                 irqStatus register values of one userId
 *
 *//*----------------------------------------------------------------------- */
extern UWORD32 EVE_MBOX_IrqGetStatusMboxId( MBOX_Id_t       mailBoxId,
                                        UWORD32         irqStatus );

/* -----------------------------------------------------------------------*//**
 * @brief          EVE_MBOX_IrqClearStatus
 *
 * @brief       Clears the irq status
 *
 * @param[in]   component    Name of the component
 * @param[in]   userId       Mail box User Id to enable
 * @param[in]   irqStatus        irqstatus register values
 *
 * @return      void
 *
 * @details     This function clears the status of the specified IRQ.
 *
 *//*----------------------------------------------------------------------- */
extern void EVE_MBOX_IrqClearStatus( CRED_index_t     component,
                                 MBOX_UserId_t    userId,
                                 UWORD32         irqStatus );

#ifdef __cplusplus
}
#endif
#endif    /* MBOX_H */
