/*
 * csl2_dat_edma3lld.c
 *
 * Implements the EDMA3 LLD Initialization and clean up functions.
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
 * Includes for accessing EDMA3 Driver Sample Init/Deinit functions
 */
#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>

#include <csl2_dat_edma3lld.h>
/*
 * global variable definitions
 */

/*
 * Flag to guard against multiple calls to DAT_EDMA3LLD_init
 */
int DAT_EDMA3LLD_initCalled = 0;


/*
 * static variable definitions
 */

/*
 * Flag to indicate that this instance is the master of the DRV instance
 */
static int _drvMaster = 0;

/*
 * extern variable declarations
 */

/*
 * The EDMA3 handle and the number of allocated channels needed by the
 * DAT module is setup here
 */
EDMA3_DRV_Handle hEdma;
extern EDMA3_DRV_Handle DAT_EDMA3LLD_hEdma;
extern int DAT_EDMA3LLD_numAllocatedChannels;



/* External Declaration */
EDMA3_DRV_Handle edma3init (unsigned int edma3Id, EDMA3_DRV_Result *errorCode);

/*
 * OS dependent functions, that must be implemented by user of CSL DAT adapter
 * These functions mark the entry and exit to critical sections of the code
 */
extern void _dat_critical_section_enter();
extern void _dat_critical_section_exit();


/*
 * global function definitions
 */

/*
 * ======== DAT_EDMA3llD_init ========
 * This function initializes the EDMA3 LLD for the DAT module
 */
int DAT_EDMA3LLD_init(DAT_EDMA3LLD_Param * param) {

    EDMA3_DRV_Result edmaResult = EDMA3_DRV_E_INVALID_PARAM;

    /*
     * Ensure DAT_EDMA3LLD_init is called only once
     */
    _dat_critical_section_enter();
    if (DAT_EDMA3LLD_initCalled)
    {
        _dat_critical_section_exit();
        return 0;
    }

    DAT_EDMA3LLD_initCalled = 1;
    _dat_critical_section_exit();

    /*
     *  If the passed parameter is NULL, then configure EDMA3 with the
     * default settings
     */
    if (NULL == param) {

    /* Initialize EDMA3 first */
    hEdma = edma3init(0, &edmaResult);
    if (edmaResult != EDMA3_DRV_SOK)
        {
        printf("edma3init() FAILED, error code: %d\r\n",
                            edmaResult);
        }
    else
        {
        printf("edma3init() PASSED\r\n");
        }

        /*
         * Allocate maximum number of channels by default
         */
        DAT_EDMA3LLD_numAllocatedChannels = DAT_QUEUEDEPTH;

        /*
         * Flag indicating DAT was responsible for creating the DRV instance
         * and opening it
         */
        _drvMaster = 1;
    }
    else
    {
        /*
         * Use the EDMA3 DRV handle passed for requesting channels etc
         */
        DAT_EDMA3LLD_hEdma = param->hEdma;

        /*
         * Save the number of allocated channels from the config information
         */
        DAT_EDMA3LLD_numAllocatedChannels = param->numChannels;
    }

    return 1;
}

/*
 * ======== DAT_EDMA3llD_exit ========
 * Function to clean-up the EDMA3 LLD after use
 */
void DAT_EDMA3LLD_exit() {

    /*
     * Ensure _initCalled was set
     */
    _dat_critical_section_enter();
    if (DAT_EDMA3LLD_initCalled == 0)
    {
        _dat_critical_section_exit();
        return;
    }

    if (_drvMaster == 0)
    {
        DAT_EDMA3LLD_hEdma = NULL;
        _dat_critical_section_exit();
        return;
    }

    DAT_EDMA3LLD_initCalled = 0;
    _dat_critical_section_exit();
}


