/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 *   \file  private/gmacsw_.h
 *
 *   \brief
 *      Private header file for GMACSW hardware driver.
 *
 */


#ifndef GMACSW__H_
#define GMACSW__H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>

/* Project dependency headers */
#include "gmacsw.h"


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/*! Maximum number of supported registered tick functions */
#define GMACSW_MAX_TICK_FXN_CNT             ((uint32_t)0x8U)

#define GMACSW_DEVMAGIC                       ((uint32_t)0x0ACEFACEU)
/*!< Device Magic number                                                    */




/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 *  \brief  GMACSW_NetworkStack
 *
 *  This structure contains the necessary identifying information for a registered
 *  network stack.
 *
 */
typedef struct GMACSW_TICK_FXN_
{
    /*!
     * \brief   The assigned stack number for this stack
     */
    uint32_t                tickFxnNum;

    /*!
     * \brief   Polling function that this stack will register with the driver
     */
    GMACSW_TickFxnCallback  pTickFxnCallback;

    /*!
     * \brief   Argument to be used for the Tx callback routines
     */
    void                    *hTickFxnCallbackArg;
}
GMACSW_RegisteredTickFxn;

/*!
 *  \brief  GMACSW Main Device Instance Structure
 *
 */
typedef struct GMACSW_DEVICE_
{
    /*!
     * \brief       Magic ID for this instance
     */
    uint32_t                devMagic;
    /*!
     * \brief       Max physical packet size
     */
    uint32_t                PktMTU;
    /*!
     * \brief      Active receive filter settings
     */
    uint32_t                rxFilter;
    /*!
     * \brief       Link is up flag.
     */
    uint32_t                linkIsUp[MAC_NUM_PORTS];
    /*!
     * \brief       Number of the interface that most recently had link up
     */
    uint32_t                currLinkedInterface;
    /*!
     * \brief       Bit vector to keep track of registered, active stacks
     */
    uint32_t                tickFxnBitVector;
    /*!
     * \brief       Array of stack objects, one per registered stack
     */
    GMACSW_RegisteredTickFxn   registeredTickFxns[GMACSW_MAX_TICK_FXN_CNT];

    /*!
     * \brief       Copy of original Driver Configuration
     */
    GMACSW_Config           config;
    /*!
     * \brief       CPDMA book keeping structure
     */
    CPDMA_Handle            cpdma;
    /*!
     * \brief       CPGMAC MAC book keeping structures
     */
    MAC_Handle              mac[MAC_NUM_PORTS];
    /*!
     * \brief       PORT module book keeping structure
     */
    PORT_Handle             port;
    /*!
     * \brief       CPTS module book keeping structure
     */
    CPTS_Handle             cpts;
    /*!
     * \brief       Address lookup engine book keeping structure
     */
    ALE_Handle              ale;
    /*!
     * \brief       GMACSW statistics book keeping structure
     */
    STATS_Handle            stats;
    /*!
     * \brief       MDIO module book keeping structure
     */
    MDIO_Handle             mdio;
    /*!
     * \brief       Debug print function callback
     */
    GMACSW_PrintFxnCallback printFxnCb;
}
GMACSW_Device;

/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

void GMACSW_printFxn(GMACSW_DeviceHandle hGMACSW, char *prnStr,...);

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* GMACSW__H_ */

