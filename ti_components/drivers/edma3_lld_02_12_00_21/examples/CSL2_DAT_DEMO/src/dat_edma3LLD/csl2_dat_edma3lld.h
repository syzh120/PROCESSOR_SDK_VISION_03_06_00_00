/*
 * csl2_dat_edma3lld.h
 *
 * Header for the EDMA3 LLD setup and clean up functions
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
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

/*
 * Includes to access the EDMA3 driver libraries
 */

#include <ti/sdo/edma3/drv/edma3_drv.h>

#include <csl2_dat_edma3lld_config.h>
#include <tistdtypes.h>

/**
 * If EDMA3 LLD is already setup by some other application, the user
 * passes a handle to this structure for use by the DAT APIs
 */
typedef struct DAT_EDMA3LLD_Param {

    /* Edma3 drv handle */
    EDMA3_DRV_Handle hEdma;

    /*
     * Number of channels to be allocated to the DAT API
     * Simulates the EDMA2.0 qdma hardware queue of same depth
     */
    Uint32 numChannels;

} DAT_EDMA3LLD_Param;


/**
 * ======== DAT_EDMA3llD_init ========
 *    @brief        Initializes DAT reference implementation module using EDMA3
 *                Low level driver. Creates and opens an EDMA3 Driver instance
 *                if passed a NULL handle. Optionally an existing driver instance
 *                 handle that is used to setup the DAT module internal state.
 */
int DAT_EDMA3LLD_init(DAT_EDMA3LLD_Param * config);

/**
 * ======== DAT_EDMA3llD_exit ========
 *    @brief         Deletes the EDMA3 Low level driver if it was created by the DAT
 *                 reference implementation module. If not, it simply resets the
 *                 DAT module internal state.
 */
void DAT_EDMA3LLD_exit();
