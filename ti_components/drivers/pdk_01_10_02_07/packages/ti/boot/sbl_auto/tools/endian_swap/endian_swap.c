/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
*   Component:   Security Add-on Tools
*
*   Filename:    endian_swap.c
*
*   Description: Convert little-endian input to big-endian output
*/

/****************************************************************
*  INCLUDE FILES
****************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ============================================================================
* GLOBAL VARIABLES DECLARATIONS
* =============================================================================
*/

/* ============================================================================
* LOCAL VARIABLES DECLARATIONS
* =============================================================================
*/

/* ============================================================================
* FUNCTIONS
* =============================================================================
*/
static uint32_t tiimage_swap32(uint32_t data)
{
    uint32_t result = 0;

    result  = (data & 0xFF000000) >> 24;
    result |= (data & 0x00FF0000) >> 8;
    result |= (data & 0x0000FF00) << 8;
    result |= (data & 0x000000FF) << 24;

    return result;
}

int32_t main (int32_t argc, char *argv[])
{
    FILE *in_fp, *out_fp;
    int32_t image_size = 0;
    int32_t i = 0, len;
    char *boot;

    if (argc < 3)
    {
        /* expect : tiimage <input_LE> <output_BE> */
        printf("Usage : \n");
        printf("endian_swap.exe takes the LE input image and converts to BE output image \n");
        printf("Syntax: ./<executable file name> <input_LE> <output_BE>\n");
        return (-(int32_t)1);
    }

    in_fp = fopen(argv[1], "rb");
    if(!in_fp) {
        printf("Error opening input image file!\n");
        return (-(int32_t)1);
    }

    out_fp = fopen(argv[2], "wb");
    if(!out_fp) {
        printf("Error opening/creating out image file!\n");
        return (-(int32_t)1);
    }

    /* Calcualte the size of the input image and rewind to the begin of file */
    fseek(in_fp, 0, SEEK_END);
    image_size = ftell(in_fp);
    rewind(in_fp);

    /* Insert the actual image */
    for (i = 0; i < (image_size / 4); i++) {
        uint32_t temp;
        fread(&temp, sizeof(temp), 1, in_fp);

        temp = tiimage_swap32(temp);

        fwrite(&temp, sizeof(temp), 1, out_fp);
    }

    if (image_size != ((image_size/4)*4))
    {
        uint8_t temp[4], byte_count;
        byte_count = (image_size - ((image_size/4)*4));
        for (i = 0; i < byte_count; i++)
        {
            temp[i] = 0;
        }
        fread(temp, sizeof(temp), 1, in_fp);
        for (i = 0; i < byte_count; i++)
        {
            fwrite(&temp[i], 1, 1, out_fp);
        }
    }
    fclose(in_fp);
    fclose(out_fp);
    printf("\n");
    return 0;
}
