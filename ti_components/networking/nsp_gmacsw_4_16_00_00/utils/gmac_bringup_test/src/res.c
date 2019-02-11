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
 *  @Component    RES - Results via SPY for cosimulation of Attila proj
 *
 *  @Filename     res.c
 *
 *  @Description  Contains functions to dump cosimulation results
 *
 *//*======================================================================== */

/* ============================================================================
* STANDARD INCLUDE FILES
* =============================================================================
*/

/* ============================================================================
* PROJECT SPECIFIC INCLUDE FILES
* =============================================================================
*/

#include "soc.h"
#include "stdint.h"
#include "stdio.h"
#include "hw_types.h"
#include "RESExt.h"
/* ============================================================================
* GLOBAL VARIABLES DECLARATIONS
* =============================================================================
*/


/* ============================================================================
* LOCAL TYPES AND DEFINITIONS
* =============================================================================
*/


/*-------------------------------------------------------------------------*//**
 * @DEFINITION   RES_THE_END
 *
 * @DESCRIPTION  this is correct value to write to cause test to end
 *
 *//*------------------------------------------------------------------------ */
#define RES_THE_END                  0x0000FFFFl



/* ============================================================================
* LOCAL VARIABLES DECLARATIONS
* =============================================================================
*/
    /* Spy Table location and size is defined in Linker Command File */
//===>#pragma DATA_SECTION(spyStart, ".OCMC_RESULT")
void *spyStart;

    /* Spy table */
    /* Spy table */
    uint32_t *res_spy;
    uint32_t res_spySize;
    /* Initialization Flag */
    uint32_t res_initialized = 0;
    /* Empty location to write result */
    uint32_t res_spyFree;
    /* Loged errors counter */
    uint32_t res_errorCount;
    /* Wrapper Control */
    uint32_t res_wrapCount;



/* ============================================================================
* LOCAL FUNCTIONS PROTOTYPES
* =============================================================================
*/

/* ============================================================================
* FUNCTIONS
* =============================================================================
*/



/*==================== Function Separator =============================*/
void RES_Init( void )
{

    /* Setup Spy Address */
    res_spy = (uint32_t *)&spyStart;
    res_spySize = 0x100;

    /* Set Free spy to first location  */
    res_spyFree = 0;
    res_wrapCount = 0;

    /* Set no Errors at the begining */
    res_errorCount = 0;

    /* Spy is initialized */
    res_initialized = 1;

} /* RES_Init() */



/*==================== Function Separator =============================*/
uint32_t RES_Set( uint32_t status )
{


    uint32_t lVal;

    if (res_initialized )
    {

        /*Add CPU Signature*/
        lVal  = status;
        //==>lVal |= RES_CPU;

        /* Write into SPY */
        res_spy[res_spyFree] = lVal;


        /* Check For Errors */
        if ( status & RES_ERROR_MASK )
        {
             #if ( defined(__STDIO_DEVICE__) )
             INFO(fprintf(UARTW, "<%s-SPY ERROR>\r\n",SOC_cpuNames[CPU] );)
             #endif
            res_errorCount ++;
        }

        /* update pointers */
        res_spyFree ++;

        if ( res_spyFree > res_spySize )
        {
            res_spyFree = 1;
            res_wrapCount ++;
            /* Set First location in buffer to Wrap mode */
            res_spy[0] = RES_WRAP_ID | res_wrapCount;
        }

    }

    return 0;

} /* RES_Set() */



/* EOF */
