/*
* dma_misc_test.c
*
* Miscellaneous EDMA3 test cases.
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

#include "sample.h"

/**
*  \brief   EDMA3 misc test cases.
*              This test case will read/write to some CC registers.
*
*  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
*/
EDMA3_DRV_Result edma3_misc_test(EDMA3_DRV_Handle hEdma)
{
    EDMA3_DRV_Result drvResult = EDMA3_DRV_SOK;
    uint32_t ccRegOffset = 0u;
    uint32_t ccRegVal = 0u;
    uint32_t newRegVal = 0u;
    uint32_t origRegVal = 0u;


    /**
    *1. Try fetching some CC registers value.
    * It should PASS.
    */
    /* PID Register */
    ccRegOffset = 0x0u;
    ccRegVal = 0;
    drvResult = EDMA3_DRV_getCCRegister(hEdma, ccRegOffset, &ccRegVal);

    if (drvResult != EDMA3_DRV_SOK)
    {
#ifdef EDMA3_DRV_DEBUG
        EDMA3_DRV_PRINTF ("Fetching CC Register (offset 0X%x) Failed, test FAILED\r\n", ccRegOffset);
#endif
    }
    else
    {
#ifdef EDMA3_DRV_DEBUG
        EDMA3_DRV_PRINTF ("Fetching CC Register (offset 0X%x) Passed, test PASSED\r\n", ccRegOffset);
#endif

#ifdef EDMA3_DEBUG_PRINT
        EDMA3_DEBUG_PRINTF ("Fetched CC Register at Offset 0X%x, Value = 0X%x\r\n", ccRegOffset, ccRegVal);
#endif  /* EDMA3_DEBUG_PRINT */
    }


    if (drvResult == EDMA3_DRV_SOK)
    {
        /* Fetch DRAE1 Register */
        ccRegOffset = 0x0348u;
        ccRegVal = 0;
        drvResult = EDMA3_DRV_getCCRegister(hEdma, ccRegOffset, &ccRegVal);

        if (drvResult != EDMA3_DRV_SOK)
        {
#ifdef EDMA3_DRV_DEBUG
            EDMA3_DRV_PRINTF ("Fetching CC Register (offset 0X%x) Failed, test FAILED\r\n", ccRegOffset);
#endif
        }
        else
        {
#ifdef EDMA3_DRV_DEBUG
            EDMA3_DRV_PRINTF ("Fetching CC Register (offset 0X%x) Passed, test PASSED\r\n", ccRegOffset);
#endif

#ifdef EDMA3_DEBUG_PRINT
            EDMA3_DEBUG_PRINTF ("Fetched CC Register at Offset 0X%x, Value = 0X%x\r\n", ccRegOffset, ccRegVal);
#endif  /* EDMA3_DEBUG_PRINT */
        }
    }


    if (drvResult == EDMA3_DRV_SOK)
    {
        /* Fetch QWMTHRA Register */
        ccRegOffset = 0x0620u;
        ccRegVal = 0;
        drvResult = EDMA3_DRV_getCCRegister(hEdma, ccRegOffset, &ccRegVal);

        if (drvResult != EDMA3_DRV_SOK)
        {
#ifdef EDMA3_DRV_DEBUG
            EDMA3_DRV_PRINTF ("Fetching CC Register (offset 0X%x) Failed, test FAILED\r\n", ccRegOffset);
#endif
            return drvResult;
        }
        else
        {
#ifdef EDMA3_DRV_DEBUG
            EDMA3_DRV_PRINTF ("Fetching CC Register (offset 0X%x) Passed, test PASSED\r\n", ccRegOffset);
#endif

#ifdef EDMA3_DEBUG_PRINT
            EDMA3_DEBUG_PRINTF ("Fetched CC Register at Offset 0X%x, Value = 0X%x\r\n", ccRegOffset, ccRegVal);
#endif  /* EDMA3_DEBUG_PRINT */
        }
    }



    /**
    * 2. Try fetching some CC registers value, whose offset is not 4-bytes
    * aligned. It should FAIL.
    */
    if (drvResult == EDMA3_DRV_SOK)
    {
        ccRegOffset = 0x1002u;
        ccRegVal = 0x0u;
        drvResult = EDMA3_DRV_getCCRegister(hEdma, ccRegOffset, &ccRegVal);

        if (drvResult == EDMA3_DRV_E_INVALID_PARAM)
        {
#ifdef EDMA3_DEBUG_PRINT
            EDMA3_DEBUG_PRINTF ("Fetching Invalid CC Register (offset 0X%x) Failed, test PASSED\r\n", ccRegOffset);
#endif  /* EDMA3_DEBUG_PRINT */
            drvResult = EDMA3_DRV_SOK;
        }
        else
        {
#ifdef EDMA3_DEBUG_PRINT
            EDMA3_DEBUG_PRINTF ("Fetching Invalid CC Register (offset 0X%x) Passed, test FAILED\r\n", ccRegOffset);
#endif  /* EDMA3_DEBUG_PRINT */
        }
    }



    /**
    * 3. Read CC Register QWMTHRA. Store the current value. Write a different
    * value on it. Read it back. Write the original value again. Read it back to
    * cross-check. It should PASS.
    */
    if (drvResult == EDMA3_DRV_SOK)
    {
        ccRegOffset = 0x0620u;
        origRegVal = 0x0u;
        drvResult = EDMA3_DRV_getCCRegister(hEdma, ccRegOffset, &origRegVal);

        if (drvResult != EDMA3_DRV_SOK)
        {
#ifdef EDMA3_DRV_DEBUG
            EDMA3_DRV_PRINTF ("Fetching CC Register (offset 0X%x) Failed, test FAILED\r\n", ccRegOffset);
#endif
        }
        else
        {
#ifdef EDMA3_DRV_DEBUG
            EDMA3_DRV_PRINTF ("Fetching CC Register (offset 0X%x) Passed, test PASSED\r\n", ccRegOffset);
#endif

#ifdef EDMA3_DEBUG_PRINT
            EDMA3_DEBUG_PRINTF ("Fetched CC Register at Offset 0X%x, Value = 0X%x\r\n", ccRegOffset, origRegVal);
#endif  /* EDMA3_DEBUG_PRINT */

            /* Find the new value to be written, it depends on the no of event queues */
            switch (origRegVal)
            {
                /* Write a new value on the same register */
            case 0x10:
                /* 1 TC */
                newRegVal = 0x0Fu;
                break;

            case 0x1010:
                /* 2 TC */
                newRegVal = 0x0F0Fu;
                break;

            case 0x101010:
                /* 3 TC */
                newRegVal = 0x0F0F0Fu;
                break;

            case 0x10101010:
                /* 4 TC */
                newRegVal = 0x0F0F0F0Fu;
                break;

            default:
                newRegVal = origRegVal;
                break;
            }

            drvResult = EDMA3_DRV_setCCRegister (hEdma, ccRegOffset, newRegVal);
            if (drvResult == EDMA3_DRV_SOK)
            {
                /* If write is successful, read it back to check */
                ccRegVal = 0x0u;

                drvResult = EDMA3_DRV_getCCRegister (hEdma, ccRegOffset, &ccRegVal);
                if (drvResult == EDMA3_DRV_SOK)
                {
                    /* Check with the value which we have written */
                    if (newRegVal == ccRegVal)
                    {
#ifdef EDMA3_DEBUG_PRINT
                        EDMA3_DEBUG_PRINTF ("Value written successfully \r\n");
#endif  /* EDMA3_DEBUG_PRINT */
                    }
                    else
                    {
#ifdef EDMA3_DRV_DEBUG
                        EDMA3_DRV_PRINTF ("QWMTHRA write FAILED \r\n");
#endif
                        drvResult = EDMA3_DRV_E_INVALID_PARAM;
                    }
                }

                /* Restore the original value */
                if (drvResult == EDMA3_DRV_SOK)
                {
                    drvResult = EDMA3_DRV_setCCRegister (hEdma, ccRegOffset, origRegVal);
                    if (drvResult != EDMA3_DRV_SOK)
                    {
#ifdef EDMA3_DEBUG_PRINT
                        EDMA3_DEBUG_PRINTF ("QWMTHRA Restore FAILED\r\n");
#endif  /* EDMA3_DEBUG_PRINT */
                    }
                    else
                    {
#ifdef EDMA3_DEBUG_PRINT
                        EDMA3_DEBUG_PRINTF ("QWMTHRA Restore Successful\r\n");
#endif  /* EDMA3_DEBUG_PRINT */
                    }
                }
            }
        }
    }
    return drvResult;
}
