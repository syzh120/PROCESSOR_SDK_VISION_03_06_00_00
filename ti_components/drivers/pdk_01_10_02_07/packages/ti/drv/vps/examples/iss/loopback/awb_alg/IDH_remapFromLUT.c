/*
 *  Copyright (c) Texas Instruments Incorporated 2014-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 */

/************************************************************************************//**
* TI ISP Library Reference Code
* This library is a software module developed for simulation of vision and ISP
* algorithms ported on TI's embedded platforms
* @author       Hrushikesh Garud (A0393878)
* @version      1.0
*
****************************************************************************************/

#include <stdio.h>
#include <math.h>
//#include <memory.h>
#include <stdlib.h>

#include <inc/Image_Data_Handling.h>
#include <inc/spatial_domain.h>

int IDH_remapFromLUT(Image *ptr, char channel, lookUpTable *LUT) {
    int  i, j, temp;
    int *dummyPtr;

    if((ptr->bpp != 8 && ptr->bpp != 24 &&
        ptr->bpp != 32) ||
       (ptr->bpp == 8 && channel != 'a') || (ptr->bpp == 24 && channel == 'a'))
    {
        return (-1);
    }

    if(ptr->bpp == 24 || ptr->bpp == 32)
    {
        switch(channel) {
            case 'b': dummyPtr = ptr->bdata; break;
            case 'g': dummyPtr = ptr->gdata; break;
            case 'r': dummyPtr = ptr->rdata; break;
            case 'a':   if(ptr->bpp != 32)
                {
                    return -1;
                }
                else
                {
                    dummyPtr = ptr->adata; break;
                }
            default: return 0;
        }
    }

    if(ptr->bpp == 8)
    {
        if(channel != 'a')
        {
            return 0;
        }
        else
        {
            dummyPtr = ptr->adata;
        }
    }

    for(i = 0; i <= ptr->rows - 1; i++) {
        for(j = 0; j <= ptr->cols - 1; j++) {
            temp = *(dummyPtr + (i * ptr->cols) + j);
            *(dummyPtr + (i * ptr->cols) + j) = LUT->table[temp];
        }
    }

    return(1);
}

