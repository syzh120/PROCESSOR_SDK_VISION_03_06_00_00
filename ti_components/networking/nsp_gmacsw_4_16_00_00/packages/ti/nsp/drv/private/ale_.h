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
 *   \file  ale.h
 *
 *   \brief
 *      Private header file for ALE of GMACSW subsystem.
 *
 */


#ifndef ALE__H_
#define ALE__H_

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
#include "ale.h"


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/*! Maximum number of ALE table entries                                    */
#define ALE_TABLE_DEPTH                ((uint32_t)1024U)


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*!
 *  \brief ALE Info Instance Structure
 */
typedef struct ALE_STATE_
{
    /*! Pointer to the config structure used for module init                    */
    ALE_Config      *pALEConfig;
    /*! Active receive filter settings                                          */
    uint32_t        rxFilter;
    /*! Boolean flag to indicate if ALE timer is active                         */
    uint32_t        aleTimerActive;
    /*! Current timer count (increments when ALE timer is marked as active)     */
    uint32_t        aleTickCount;
    /*! ALE time out count                                                      */
    uint32_t        aleTickTimeOutCount;
    /*! ALE Control fields                                                      */
    uint32_t        aleModeFlags;
    /*! Unknown VLAN Force Untagged Egress (except on port 2)                   */
    uint8_t         unknownForceUntaggedEgress;
    /*! Unknown VLAN Registered Multicast Flood Mask                            */
    uint8_t         unknownRegMcastFloodMask;
    /*! Unknown VLAN Multicast Flood Mask                                       */
    uint8_t         unknownMcastFloodMask;
    /*! Unknown VLAN Member List                                                */
    uint8_t         unknownVlanMemberList;
    /*! Default Port VLAN ID                                                    */
    uint32_t        defaultPortVID;
}
ALE_State;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

extern void ALE_ageOut(ALE_Handle hAle);


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* ALE__H_ */


