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
#include <stdlib.h>
#include <math.h>
#include <inc/Image_Data_Handling.h>

#include <ti/drv/vps/examples/utility/bsputils_mem.h>

int IDH_createImage(Image *ptr, int rows, int columns, int bpp, int overwrite)
{
    int test;
    if(overwrite == 0 && (ptr->bpp == 8 || ptr->bpp == 24 || ptr->bpp == 32))
    {
        return (0);
    }
    else
    {
        test = IDH_freeImage(ptr);
        if(test == 0)
        {
            return -1;
        }
        ptr->bpp  = bpp;
        ptr->rows = rows;
        ptr->cols = columns;
        ptr->res  = 11808;

#if 0
        if(bpp == 32)
        {
            ptr->bdata = (int *)calloc(sizeof(int), (rows*columns));
            ptr->gdata = (int *)calloc(sizeof(int), (rows*columns));
            ptr->rdata = (int *)calloc(sizeof(int), (rows*columns));
            ptr->adata = (int *)calloc(sizeof(int), (rows*columns));
        }
        else if(bpp == 24)
        {
            ptr->bdata = (int *)calloc(sizeof(int), (rows*columns));
            ptr->gdata = (int *)calloc(sizeof(int), (rows*columns));
            ptr->rdata = (int *)calloc(sizeof(int), (rows*columns));
        }
        else if(bpp == 8)
        {
            ptr->adata = (int *)calloc(sizeof(int), (rows*columns));
        }
#endif
        ptr->rdata = (int *)BspUtils_memAlloc(sizeof(int)*(rows*columns), 16);
        ptr->gdata = (int *)BspUtils_memAlloc(sizeof(int)*(rows*columns), 16);
        ptr->bdata = (int *)BspUtils_memAlloc(sizeof(int)*(rows*columns), 16);
        ptr->adata = (int *)BspUtils_memAlloc(sizeof(int)*(rows*columns), 16);
    }
    return 1;
}

