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


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vcop.h"

#include "test_profile.h"

#define WIDTH   (64*4)
#define PITCH   (64*4)
#define HEIGHT  (30)

#pragma DATA_SECTION(Erode_bin_single_pixel_IN, "Adata");
unsigned int Erode_bin_single_pixel_IN[32*2*4]={
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x007e001f, 0xc00ff000, 0x007e001f, 0xc00ff000,
    0x007e001f, 0xc00ff000, 0x007e001f, 0xc00ff000,
    0x207c001f, 0x8007f000, 0x207c001f, 0x8007f000,
    0x207c001f, 0x8007f000, 0x207c001f, 0x8007f000,
    0x003f003f, 0xe00fe000, 0x003f003f, 0xe00fe000,
    0x003f003f, 0xe00fe000, 0x003f003f, 0xe00fe000,
    0x000fe0ff, 0xfc3fe000, 0x000fe0ff, 0xfc3fe000,
    0x000fe0ff, 0xfc3fe000, 0x000fe0ff, 0xfc3fe000,
    0x0003f9fc, 0xff7fc004, 0x0003f9fc, 0xff7fc004,
    0x0003f9fc, 0xff7fc004, 0x0003f9fc, 0xff7fc004,
    0x0000fff0, 0x1fff0000, 0x0000fff0, 0x1fff0000,
    0x0000fff0, 0x1fff0000, 0x0000fff0, 0x1fff0000,
    0x00003fc0, 0x07f80000, 0x00003fc0, 0x07f80000,
    0x00003fc0, 0x07f80000, 0x00003fc0, 0x07f80000,
    0x02000f00, 0x01f00000, 0x02000f00, 0x01f00000,
    0x02000f00, 0x01f00000, 0x02000f00, 0x01f00000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x20000000, 0x00000000, 0x20000000, 0x00000000,
    0x20000000, 0x00000000, 0x20000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x0000007c, 0x00000010, 0x0000007c, 0x00000010,
    0x0000007c, 0x00000010, 0x0000007c, 0x00000010,
    0x00007fff, 0xff000000, 0x00007fff, 0xff000000,
    0x00007fff, 0xff000000, 0x00007fff, 0xff000000,
    0x003fffff, 0xfff00000, 0x003fffff, 0xfff00000,
    0x003fffff, 0xfff00000, 0x003fffff, 0xfff00000,
    0x07fff000, 0xfffe0000, 0x07fff000, 0xfffe0000,
    0x07fff000, 0xfffe0000, 0x07fff000, 0xfffe0000,
    0x0ff80000, 0x01ffc000, 0x0ff80000, 0x01ffc000,
    0x0ff80000, 0x01ffc000, 0x0ff80000, 0x01ffc000,
    0x0fe00c03, 0x00ffe000, 0x0fe00c03, 0x00ffe000,
    0x0fe00c03, 0x00ffe000, 0x0fe00c03, 0x00ffe000,
    0x0fe0070e, 0x007fe000, 0x0fe0070e, 0x007fe000,
    0x0fe0070e, 0x007fe000, 0x0fe0070e, 0x007fe000,
    0x0fe00000, 0x007fe000, 0x0fe00000, 0x007fe000,
    0x0fe00000, 0x007fe000, 0x0fe00000, 0x007fe000,
    0x0fe00000, 0x007fe002, 0x0fe00000, 0x007fe002,
    0x0fe00000, 0x007fe002, 0x0fe00000, 0x007fe002,
    0x0ff83803, 0x80ffe000, 0x0ff83803, 0x80ffe000,
    0x0ff83803, 0x80ffe000, 0x0ff83803, 0x80ffe000,
    0x0ffe0e0e, 0x01fff000, 0x0ffe0e0e, 0x01fff000,
    0x0ffe0e0e, 0x01fff000, 0x0ffe0e0e, 0x01fff000,
    0x07ff83fc, 0x0fff8000, 0x07ff83fc, 0x0fff8000,
    0x07ff83fc, 0x0fff8000, 0x07ff83fc, 0x0fff8000,
    0x01fff800, 0x7ff80000, 0x01fff800, 0x7ff80000,
    0x01fff800, 0x7ff80000, 0x01fff800, 0x7ff80000,
    0x003fffff, 0xff000000, 0x003fffff, 0xff000000,
    0x003fffff, 0xff000000, 0x003fffff, 0xff000000,
    0x00001fff, 0xf8000010, 0x00001fff, 0xf8000010,
    0x00001fff, 0xf8000010, 0x00001fff, 0xf8000010,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000
};

#pragma DATA_SECTION(Erode_bin_single_pixel_OUT, "Bdata");
unsigned int Erode_bin_single_pixel_OUT[30*2*4]={
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00fc003f, 0x801fe000, 0x00fc003f, 0x801fe000,
    0x00fc003f, 0x801fe000, 0x00fc003f, 0x801fe000,
    0x00f8003f, 0x000fe000, 0x00f8003f, 0x000fe000,
    0x00f8003f, 0x000fe000, 0x00f8003f, 0x000fe000,
    0x007e007f, 0xc01fc000, 0x007e007f, 0xc01fc000,
    0x007e007f, 0xc01fc000, 0x007e007f, 0xc01fc000,
    0x001fc1ff, 0xf87fc000, 0x001fc1ff, 0xf87fc000,
    0x001fc1ff, 0xf87fc000, 0x001fc1ff, 0xf87fc000,
    0x0007f3f9, 0xfeff8000, 0x0007f3f9, 0xfeff8000,
    0x0007f3f9, 0xfeff8000, 0x0007f3f9, 0xfeff8000,
    0x0001ffe0, 0x3ffe0000, 0x0001ffe0, 0x3ffe0000,
    0x0001ffe0, 0x3ffe0000, 0x0001ffe0, 0x3ffe0000,
    0x00007f80, 0x0ff00000, 0x00007f80, 0x0ff00000,
    0x00007f80, 0x0ff00000, 0x00007f80, 0x0ff00000,
    0x00001e00, 0x03e00000, 0x00001e00, 0x03e00000,
    0x00001e00, 0x03e00000, 0x00001e00, 0x03e00000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x000000f8, 0x00000000, 0x000000f8, 0x00000000,
    0x000000f8, 0x00000000, 0x000000f8, 0x00000000,
    0x0000ffff, 0xfe000000, 0x0000ffff, 0xfe000000,
    0x0000ffff, 0xfe000000, 0x0000ffff, 0xfe000000,
    0x007fffff, 0xffe00000, 0x007fffff, 0xffe00000,
    0x007fffff, 0xffe00000, 0x007fffff, 0xffe00000,
    0x0fffe001, 0xfffc0000, 0x0fffe001, 0xfffc0000,
    0x0fffe001, 0xfffc0000, 0x0fffe001, 0xfffc0000,
    0x1ff00000, 0x03ff8000, 0x1ff00000, 0x03ff8000,
    0x1ff00000, 0x03ff8000, 0x1ff00000, 0x03ff8000,
    0x1fc01806, 0x01ffc000, 0x1fc01806, 0x01ffc000,
    0x1fc01806, 0x01ffc000, 0x1fc01806, 0x01ffc000,
    0x1fc00e1c, 0x00ffc000, 0x1fc00e1c, 0x00ffc000,
    0x1fc00e1c, 0x00ffc000, 0x1fc00e1c, 0x00ffc000,
    0x1fc00000, 0x00ffc000, 0x1fc00000, 0x00ffc000,
    0x1fc00000, 0x00ffc000, 0x1fc00000, 0x00ffc000,
    0x1fc00000, 0x00ffc000, 0x1fc00000, 0x00ffc000,
    0x1fc00000, 0x00ffc000, 0x1fc00000, 0x00ffc000,
    0x1ff07007, 0x01ffc000, 0x1ff07007, 0x01ffc000,
    0x1ff07007, 0x01ffc000, 0x1ff07007, 0x01ffc000,
    0x1ffc1c1c, 0x03ffe000, 0x1ffc1c1c, 0x03ffe000,
    0x1ffc1c1c, 0x03ffe000, 0x1ffc1c1c, 0x03ffe000,
    0x0fff07f8, 0x1fff0000, 0x0fff07f8, 0x1fff0000,
    0x0fff07f8, 0x1fff0000, 0x0fff07f8, 0x1fff0000,
    0x03fff000, 0xfff00000, 0x03fff000, 0xfff00000,
    0x03fff000, 0xfff00000, 0x03fff000, 0xfff00000,
    0x007fffff, 0xfe000000, 0x007fffff, 0xfe000000,
    0x007fffff, 0xfe000000, 0x007fffff, 0xfe000000,
    0x00003fff, 0xf0000000, 0x00003fff, 0xf0000000,
    0x00003fff, 0xf0000000, 0x00003fff, 0xf0000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000
};

#pragma DATA_SECTION(Erode_bin_single_pixel_output, "Cdata");
unsigned int Erode_bin_single_pixel_output[30*2*4];

#pragma DATA_SECTION(profile_array, "Cdata");
unsigned int profile_array[2];

#if VCOP_HOST_EMULATION
  #include "vcop_vec_bin_image_erode_single_pixel_kernel.k"
                                                      // kernel source
#else
void vcop_vec_bin_image_erode_single_pixel
(
    __vptr_uint32 pIn,
    __vptr_uint32 out,
    int           cols,
    int           pitch,
    int           height
);
#endif


int main()
{
    int fail;
    int i;

#ifdef REPORT
#ifdef SCTM
    unsigned int sctm_t1, sctm_t2, exec_diff;
    unsigned int overflow;
#endif
    FILE* fpReport = fopen("../../../report.csv","a+");
#endif

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/

#if VCOP_HOST_EMULATION
#else
    unsigned int t0, t1;
    _tsc_start();
#endif


    for(i = 0; i < 2; i++)
    {
#if VCOP_HOST_EMULATION
#else
        t0 = _tsc_gettime();
#endif

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
#ifdef REPORT
#ifdef SCTM
        EVE_SCTM_Enable(CTM);
        EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
        EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
        sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif

        vcop_vec_bin_image_erode_single_pixel (Erode_bin_single_pixel_IN,
                     Erode_bin_single_pixel_output, WIDTH, PITCH, HEIGHT);

#ifdef REPORT
#ifdef SCTM
        sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
        overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
        assert(overflow!=1);

        exec_diff = sctm_t2 - sctm_t1;
        EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
#endif
#endif

#if VCOP_HOST_EMULATION
#else
        t1 = _tsc_gettime();
        profile_array[i]  = (t1 - t0);
#endif
    }

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail = memcmp(Erode_bin_single_pixel_output,
                  Erode_bin_single_pixel_OUT, (HEIGHT-2)*WIDTH/32*4);

    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/
#ifdef REPORT
    fprintf(fpReport,"vcop_vec_bin_image_erode_single_pixel,");
    fprintf(fpReport,"%d,",WIDTH);
    fprintf(fpReport,"%d,",HEIGHT);
    fprintf(fpReport,"%d,",WIDTH);
    fprintf(fpReport,"%d,",HEIGHT);
    fprintf(fpReport,"%d,",1);
#endif
    if(fail)
    {
#ifdef CONSOLE
        for (i = 0; i < (HEIGHT-2)*WIDTH/32; i++)
        {
            printf("i:%d, out:%u, EOut:%u, %c \n",
                    i, Erode_bin_single_pixel_output[i],
                    Erode_bin_single_pixel_OUT[i],
                    (Erode_bin_single_pixel_output[i]
                    !=Erode_bin_single_pixel_OUT[i]) ? '*':' '
                  );
        }
#endif
#ifdef REPORT
        fprintf(fpReport,"FAIL,");
#endif
    }
    else {
#ifdef CONSOLE
        printf ("Pass \n");
#endif
#ifdef REPORT
        fprintf(fpReport,"PASS,");
#endif
    }

#if VCOP_HOST_EMULATION
#else
    for(i = 0; i < 2; i++)
        printf ("Time taken: %d cycles \n", profile_array[i]);
#endif

#ifdef REPORT
#ifdef SCTM
    fprintf(fpReport,"%d\n",exec_diff);
#endif
    if(fpReport){
        fclose(fpReport);
    }
#endif
}

/* ======================================================================== */
/*  End of file:  vcop_vec_bin_image_erode_single_pixel.c                   */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
