/*
*
* Copyright (c) 2010-2017 Texas Instruments Incorporated
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


#include  <stdio.h>
#include  <stdlib.h>
#include <string.h>
#include "GlobalTypes.h"
#include "baseaddress.h"
#include "sctm.h"
#include <assert.h>
#include <stdint.h>

#include "vcop/vcop.h"

void vcop_vec_gradients_xy_and_magnitude
(
    __vptr_uint8   pIn,
    __vptr_int16   pGradX,
    __vptr_int16   pGradY,
    __vptr_int16   pMag,
    unsigned short width,
    unsigned short height
);

#define WIDTH   (16)
#define HEIGHT  (8)

#pragma DATA_SECTION(pIn, "Adata");
unsigned char pIn[WIDTH*HEIGHT] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
};

#pragma DATA_SECTION(pGradX, "Bdata");
short pGradX[WIDTH*HEIGHT];

#pragma DATA_SECTION(pGradY, "Cdata");
short pGradY[WIDTH*HEIGHT];

#pragma DATA_SECTION(pMag, "Udata");
short pMag[WIDTH*HEIGHT];

#pragma DATA_SECTION(pGradX_OUT, "Eoutdata");
short pGradX_OUT[(WIDTH-2)*(HEIGHT-2)]=
{
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02
};

#pragma DATA_SECTION(pGradY_OUT, "Eoutdata");
short pGradY_OUT[(WIDTH-2)*(HEIGHT-2)]=
{
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20
};

#pragma DATA_SECTION(pMag_OUT, "Eoutdata");
short pMag_OUT[(WIDTH-2)*(HEIGHT-2)]=
{
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22
};

void Check_status (int return_value)
{
    if (return_value == RET_OK)
    {
        printf("PASS \n");
    }
    else
    {
        printf("Fail \n");
    }
}

int test_main()
{
    ReturnCode_t checkReturn = RET_OK;

    unsigned int sctm_t1, sctm_t2, exec_diff;
    unsigned int overflow;
    unsigned int i=0;


    memset(pGradX,0,sizeof(pGradX));
    memset(pGradY,0,sizeof(pGradY));
    memset(pMag  ,0,sizeof(pMag)  );

    /*------------------------------------------------------------*/
    /* Global Enable of SCTM hardware */
    /* This function actually sets Enable bit in the CT CNTL */
    /* register of SCTM. Parameter CTM is defined in */
    /* baseaddress.h, and is used by cred macros to compute */
    /* baseaddress of CTM. */
    /*------------------------------------------------------------*/
    EVE_SCTM_Enable(CTM);

    /*------------------------------------------------------------*/
    /* Configure Counter 0, to measure "vcop_busy" which is a */
    /* duration signal, and enable the counter. */
    /*------------------------------------------------------------*/
    checkReturn = EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);

    /*Enables counter for counting or for timer*/
    EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);

    for ( i = 0 ; i < 10; i++ )
    {
        /*------------------------------------------------------------*/
        /* Read the initial value of counter, prior to starting */
        /* the loop. */
        /*------------------------------------------------------------*/
        sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);

        /*------------------------------------------------------------*/
        /* Invoke VCOP kernel. */
        /*------------------------------------------------------------*/

        vcop_vec_gradients_xy_and_magnitude(pIn,pGradX+WIDTH,
                                 pGradY+WIDTH,pMag+WIDTH, WIDTH , HEIGHT-2);

        /*------------------------------------------------------------*/
        /* Read counter again, and take difference, multiplying by 2 */
        /* as SCTM counters run at CLK_2 while VCOP runs at CLK_1. */
        /*------------------------------------------------------------*/
        sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);

        /*Checks if a counter has overflowed: 1 if overflow; 0 otherwise*/
        overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
        assert(overflow!=1);

        exec_diff = (sctm_t2 - sctm_t1) << 1;
        /* Disable counter timer */

        printf ("VCOP was busy for iteration %d for %d VCOP cycles \n", i, exec_diff);
    }
    EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);

    Check_status(checkReturn);
    return checkReturn;
}

/* ======================================================================== */
/*  End of file:  vcop_vec_gradients_xy_and_magnitude.c                     */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

