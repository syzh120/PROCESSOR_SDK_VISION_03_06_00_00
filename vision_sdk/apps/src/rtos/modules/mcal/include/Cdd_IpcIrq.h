/* ======================================================================
 *   Copyright (C) 2017 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     Cdd_IpcIrq.h
 *
 *  \brief    This file contains ISR function declaration for CDD IPC Driver
 *
 */

/**
 *  \ingroup MCAL_IPC_API IPC ISR API's
 *
 *  This file provides ISR API's that is used to receive and process events from
 *  remote cores
 *
 *  - For each remote core & for each mailbox used, an associated ISR is
 *      required.
 *
 *
 *  \version 00.00.01
 *
 *  Revision History
 *      Version     : 00.09.00
 *      Author      : Sujith S
 *      Comment     : Created, used AR1x IPC CDD as reference
 *
 *  @sa MCAL_IPC_ISR
 *  @{
 */


#ifndef CDD_IPCIRQ_H_
#define CDD_IPCIRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_Ipc.h"


#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Version identification */
/** \brief Driver ISR Implementation Major Version */
#define CDD_IPC_IRQ_MAJOR_VERSION    (1U)
/** \brief Driver ISR Implementation Minor Version */
#define CDD_IPC_IRQ_MINOR_VERSION    (9U)
/** \brief Driver ISR Implementation Patch Version */
#define CDD_IPC_IRQ_PATCH_VERSION    (0U)

/**
 *  \name CDD Driver ISR category level
 *
 *  Design : IPCCDD_DesignId_017
 *  Requirements : SWS_BSW_00043, SWS_BSW_00068
 *
 *  Defines for CDD Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define CDD_IPC_ISR_VOID            (0x00U)
/** \brief Category 1 ISR type */
#define CDD_IPC_ISR_CAT1            (0x01U)
/** \brief Category 2 ISR type */
#define CDD_IPC_ISR_CAT2            (0x02U)
/* @} */


/* ========================================================================== */
/*                           Function Prototypes                              */
/* ========================================================================== */

/** \brief A Mailbox can raise multiple interrupts. In this implementation, the
            Mailbox new message interrupt is used determine presence of data
            from the remote core. This interrupt will have to be mapped core
            IPU1_1/IPU2_0 for TDA3x/TDA2Ex & TDA2x respectively, Done by MCU
            module.
            One interrupt per mailbox (& that mailbox can only be written
            into by one remote core)
            i.e. interrupt for below

                    <---MBX_1 (FIFO 1)<------IPU1_0
                    <---MBX_1 (FIFO 2)<------DSP 1 (Yes MBX_1 is being used for
            IPU1_1       :                          IPU1_0 and DSP 1 )
                    <---MBX_N (FIFO X)<------DSP 2
            */
#if (CDD_IPC_ISR_TYPE == CDD_IPC_ISR_CAT1 || \
     CDD_IPC_ISR_TYPE == CDD_IPC_ISR_VOID)

    /* #EXTEND_SUPPORT_4_OTHERCORES When support for other cores is required
        and the mailbox used different with respect to IPU1_0.
        You will require to add a seperate ISR */
    /** \brief ISR for Mailbox, Not Empty interrupt handler */
    void Cdd_IrqMbxFromCoreIpu1_0( void );

#elif (CDD_IPC_ISR_TYPE == CDD_IPC_ISR_CAT2)

    /** \brief ISR for Mailbox, Not Empty interrupt handler */
    ISR( Cdd_IrqMbxFromCoreIpu1_0 );

#endif /* ((CDD_IPC_ISR_TYPE == CDD_IPC_ISR_CAT1).... */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef CDD_IPCIRQ_H_ */

/* @} */

