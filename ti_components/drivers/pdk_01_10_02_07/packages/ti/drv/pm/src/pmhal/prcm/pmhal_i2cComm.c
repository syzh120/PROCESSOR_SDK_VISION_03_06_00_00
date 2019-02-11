/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
 * \file    pmhal_i2cComm.c
 *
 * \brief   This file contains the API to register I2C communication using
 *          PMHAL.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include "pm_types.h"
#include "pm_utils.h"
#include "pmhal_i2cComm.h"
#include <ti/csl/hw_types.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None  */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*
 * Pointer to the I2C functions. This should be populated with pointers to
 * the I2C driver being used.
 */
const pmhalI2cCommOperations_t *gPmhalI2cFunc = NULL;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMHALI2CCommRegister(const pmhalI2cCommOperations_t *i2cfunc)
{
    pmErrCode_t     status = PM_FAIL;
    static uint32_t i2cRegistrationDone = 0U;
    /*
     * The API checks if all the function pointers are properly populated.
     */
    if ((i2cfunc != NULL) && (0U == i2cRegistrationDone))
    {
        if (i2cfunc->pmhalI2cCommInit != NULL)
        {
            /* Check if any either the Read8 and Write8 are populated
             * or Read16 and Write16 are populated. Only in that case register
             * the functions. If only one in the pair of read/write is
             * populated do not register the functions.
             */
            if ((i2cfunc->pmhalI2cCommRead8 == NULL) &&
                (i2cfunc->pmhalI2cCommWrite8 == NULL))
            {
                if ((i2cfunc->pmhalI2cCommRead16 != NULL) &&
                    (i2cfunc->pmhalI2cCommWrite16 != NULL))
                {
                    gPmhalI2cFunc = i2cfunc;
                    status        = PM_SUCCESS;
                    /* Once the registration is done do not re-do the
                     * registration
                     */
                    i2cRegistrationDone = 1U;
                }
            }
            else if ((i2cfunc->pmhalI2cCommRead8 != NULL) &&
                     (i2cfunc->pmhalI2cCommWrite8 != NULL))
            {
                gPmhalI2cFunc = i2cfunc;
                status        = PM_SUCCESS;
                /* Once the registration is done do not re-do the
                 * registration
                 */
                i2cRegistrationDone = 1U;
            }
            else
            {
                status = PM_BADARGS;
            }
        }
    }
    return status;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
