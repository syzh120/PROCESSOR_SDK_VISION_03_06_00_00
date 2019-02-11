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

int IDH_freeImage(Image *ptr)
{
#if 0
    if(ptr->bpp == 0)
    {
        return 1;
    }
    else if(ptr->bpp == 8)
    {
        ptr->bpp  = 0;
        ptr->rows = 0;
        ptr->cols = 0;
        ptr->res  = 0;

        free(ptr->adata);
        return 1;
    }
    else if(ptr->bpp == 24)
    {
        ptr->bpp  = 0;
        ptr->rows = 0;
        ptr->cols = 0;
        ptr->res  = 0;

        if(NULL != ptr->bdata)
            free(ptr->bdata);
        if(NULL != ptr->gdata)
            free(ptr->gdata);
        if(NULL != ptr->rdata)
            free(ptr->rdata);

        return 1;
    }
    else if(ptr->bpp == 32)
    {
        ptr->bpp  = 0;
        ptr->rows = 0;
        ptr->cols = 0;
        ptr->res  = 0;

        free(ptr->bdata);
        free(ptr->gdata);
        free(ptr->rdata);
        free(ptr->adata);

        return 1;
    }
    else
    {
        ptr->bpp = 0;
        return 1;
    }
#endif
    if (NULL != ptr->rdata)
    {
        BspUtils_memFree(ptr->rdata, sizeof(int)*(ptr->rows*ptr->cols));
        ptr->rdata = NULL;
    }
    if (NULL != ptr->gdata)
    {
        BspUtils_memFree(ptr->gdata, sizeof(int)*(ptr->rows*ptr->cols));
        ptr->gdata = NULL;
    }
    if (NULL != ptr->bdata)
    {
        BspUtils_memFree(ptr->bdata, sizeof(int)*(ptr->rows*ptr->cols));
        ptr->bdata = NULL;
    }
    if (NULL != ptr->adata)
    {
        BspUtils_memFree(ptr->adata, sizeof(int)*(ptr->rows*ptr->cols));
        ptr->adata = NULL;
    }

    return 1;
}

