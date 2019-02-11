/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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


/** @file file_image_file_io.c
 *
 *  @brief  This file contains code for reading, writing Y, YUV, PGM files
 *
 *
 *  @date   April 2015
 *
 *  Description
 *
 */
#pragma CHECK_MISRA ("none")

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ti_image_file_io.h"
#include "ti_file_io.h"

int32_t readFileY(const int8_t *infilename,
        uint8_t **image,
        uint16_t height,
        uint16_t width)
{
    TI_FILE *fp;
    int chr;
    int32_t status= 0;

    /***************************************************************************
     * Open the input image file for reading if a filename was given. If no
     * filename was provided, set fp to read from standard input.
     ***************************************************************************/
    //printf("\n\tStarting ReadFilePGM() routine.\n");fflush(stdout);

    if ((fp = FOPEN((const char*)infilename, "rb")) == NULL) {
        printf("\nError reading the file %s in ReadFileY().", infilename);fflush(stdout);
        status= -1;
        goto Exit;
    }

    /***************************************************************************
     * Allocate memory to store the image then read the image from the file.
     ***************************************************************************/
    if(((*image) = (uint8_t *) malloc(width*height)) == NULL) {
        printf("\nMemory allocation failure in ReadFileY().\n");fflush(stdout);
        FCLOSE(fp);
        status=1;
        goto Exit;
    }
    //   printf("\n\t\tAllocated %d bytes in ReadFilePGM().\n", width*height*(*bytesPerPixel));fflush(stdout);

    // TODO: check endianess to see if we need to switch the order later
    //chr = (width*height);
    chr = FREAD((*image), 1, width*height, fp);   /////CCS FILE LOAD: Comment this block until line 57 and set breakpoint here. Upload data of size width*height bytes to address *image.
    if (chr != (width*height)){
        printf("\nError reading the image data in ReadFileY().");fflush(stdout);
        FCLOSE(fp);
        free((*image));
        status= -1;
        goto Exit;
    }

    FCLOSE(fp);

    // printf("\n\tClosed file in ReadFilePGM().\n");fflush(stdout);
    Exit:
    return status;
}

int32_t readFile_YUV420SP(const int8_t *infilename,
        uint8_t **imageY,
        uint8_t **imageUV,
        uint16_t height,
        uint16_t width)
{
    TI_FILE *fp;
    int chr;
    int32_t status= 0;

    /***************************************************************************
     * Open the input image file for reading if a filename was given. If no
     * filename was provided, set fp to read from standard input.
     ***************************************************************************/
    //printf("\n\tStarting ReadFilePGM() routine.\n");fflush(stdout);

    if ((fp = FOPEN((const char*)infilename, "rb")) == NULL) {
        printf("\nError reading the file %s in readFile_YUV420SP().", infilename);fflush(stdout);
        status= -1;
        goto Exit;
    }

    /***************************************************************************
     * Allocate memory to store the image then read the image from the file.
     ***************************************************************************/
    if(((*imageY) = (uint8_t *) malloc(width*height)) == NULL) {
        printf("\nMemory allocation failure in readFile_YUV420SP().\n");fflush(stdout);
        FCLOSE(fp);
        status=1;
        goto Exit;
    }
    //   printf("\n\t\tAllocated %d bytes in ReadFilePGM().\n", width*height*(*bytesPerPixel));fflush(stdout);

    // TODO: check endianess to see if we need to switch the order later
    //chr = (width*height);
    chr = FREAD((*imageY), 1, width*height, fp);   /////CCS FILE LOAD: Comment this block until line 57 and set breakpoint here. Upload data of size width*height bytes to address *image.
    if (chr != (width*height)){
        printf("\nError reading the image data in readFile_YUV420SP().");fflush(stdout);
        FCLOSE(fp);
        free((*imageY));
        status= -1;
        goto Exit;
    }

    /***************************************************************************
     * Allocate memory to store the image then read the image from the file.
     ***************************************************************************/
    if(((*imageUV) = (uint8_t *) malloc((width*height)/2)) == NULL) {
        printf("\nMemory allocation failure in readFile_YUV420SP().\n");fflush(stdout);
        FCLOSE(fp);
        status=1;
        goto Exit;
    }

    // TODO: check endianess to see if we need to switch the order later
    //chr = (width*height);
    chr = FREAD((*imageUV), 1, (width*height)/2, fp);   /////CCS FILE LOAD: Comment this block until line 57 and set breakpoint here. Upload data of size width*height bytes to address *image.
    if (chr != (width*height)/2){
        printf("\nError reading the image data in ReadFileY().");fflush(stdout);
        FCLOSE(fp);
        free((*imageY));
        status= -1;
        goto Exit;
    }

    FCLOSE(fp);

    // printf("\n\tClosed file in ReadFilePGM().\n");fflush(stdout);
    Exit:
    return status;
}

int32_t readFileYUV_ILE_IBE(const int8_t *infilename,
        uint8_t **image,
        uint16_t height,
        uint16_t width)
{
    TI_FILE *fp;
    int chr;
    int32_t status= 0;

    /***************************************************************************
     * Open the input image file for reading if a filename was given. If no
     * filename was provided, set fp to read from standard input.
     ***************************************************************************/
    //printf("\n\tStarting ReadFilePGM() routine.\n");fflush(stdout);

    if ((fp = FOPEN((const char*)infilename, "rb")) == NULL) {
        printf("\nError reading the file %s in ReadFile_YUV_ILE_IBE().", infilename);fflush(stdout);
        status= -1;
        goto Exit;
    }

    /***************************************************************************
     * Allocate memory to store the image then read the image from the file.
     ***************************************************************************/
    if(((*image) = (uint8_t *) malloc(2*width*(height+10))) == NULL) { /* We allocate a bit more because due to color subsampling and the magnitude of the distorsion, the bounding box may overlap with undefined regions */
        printf("\nMemory allocation failure in ReadFile_YUV_ILE_IBE().\n");fflush(stdout);
        printf("Memory allocation failure in ReadFile_YUV_ILE_IBE().\n");fflush(stdout);
        FCLOSE(fp);
        status=1;
        goto Exit;
    }
    //   printf("\n\t\tAllocated %d bytes in ReadFilePGM().\n", width*height*(*bytesPerPixel));fflush(stdout);

    // TODO: check endianess to see if we need to switch the order later
    //chr = (width*height);
    chr = FREAD((*image), 1, 2*width*height, fp); /////CCS FILE LOAD: Comment this block until line 116 and set breakpoint here. Upload data of size 2*width*height bytes to address *image.
    if (chr != (2*width*height)){
        printf("\nError reading the image data in ReadFile_YUV_ILE_IBE().");fflush(stdout);
        FCLOSE(fp);
        free((*image));
        status= -1;
        goto Exit;
    }

    FCLOSE(fp);

    // printf("\n\tClosed file in ReadFilePGM().\n");fflush(stdout);
    Exit:
    return status;
}

int32_t readFilePGM(const int8_t *infilename,
        uint8_t **image,
        uint16_t *n_rows,
        uint16_t *n_cols,
        uint16_t *bytesPerPixel,
        uint16_t *maxBitPerPixel,
        int32_t *n_maxValue)
{
    TI_FILE *fp;
    char c;
    int chr;
    int8_t buf[71];
    int32_t width, height, maxValue;
    int32_t status= 0;

    /***************************************************************************
     * Open the input image file for reading if a filename was given. If no
     * filename was provided, set fp to read from standard input.
     ***************************************************************************/
    //printf("\n\tStarting ReadFilePGM() routine.\n");fflush(stdout);

    if ((fp = FOPEN((const char*)infilename, "rb")) == NULL) {
        printf("\nError reading the file %s in ReadFile_PGM().", infilename);fflush(stdout);
        status= -1;
        goto Exit;
    }

    // printf("\n\t\tOpened file successfully in ReadFilePGM().");fflush(stdout);
    /***************************************************************************
     * Verify that the image is in PGM format, read in the number of columns
     * and rows in the image and scan past all of the header information.
     ***************************************************************************/
    FGETS((char *)buf, 70, fp);
    if(strncmp((const char*)buf,"P5",2) != 0){
        printf("\nThe file %s is not in PGM format!", infilename);fflush(stdout);
        FCLOSE(fp);
        status= -1;
        goto Exit;
    }
    do{
        FGETS((char*)buf, 70, fp);
    } while(buf[0] == '#');  /* skip all comment lines */
    sscanf((const char*)buf, "%d %d", &width, &height);
    // printf("\n\t\tRead format and image dimensions in ReadFilePGM().");fflush(stdout);
    {
        int n;

        /* Loop until we can read an integer. */

        while (FSCANF(fp, "%d", &n) == 0)
        {
            /* Skip comments. */
            FSCANF(fp, "#%n", &n);

            /* If we found a comment, skip all characters until EOL is reached. */
            if (n > 0) {
                do {
                    FREAD(&c, 1, 1, fp);
                } while(c != '\n');
            }

            /* Skip newline. */
            FSCANF(fp, "\n");
        }

        maxValue = n;
    }


    //fgets(buf, 70, fp);
    //sscanf(buf, "%d", &maxValue);

    *n_cols = (uint16_t)width;
    *n_rows = (uint16_t)height;
    if (maxValue < 256)
        *bytesPerPixel = 1;
    else
        *bytesPerPixel = 2;

    {
        int bpp = 0;
        int val = 1;
        while (val < maxValue)
        {
            val *= 2;
            bpp++;
        }
        *maxBitPerPixel = bpp;
    }
    *n_maxValue = maxValue;

    // printf("\n\t\tRead maxValue=%d in ReadFilePGM().\n", maxValue);fflush(stdout);
    do{
        FREAD(&c, 1, 1, fp);
    } while(c != 10);  // search for NL(0x0A), e.g., 'new line'

    /***************************************************************************
     * Allocate memory to store the image then read the image from the file.
     ***************************************************************************/
    if(((*image) = (uint8_t *) malloc(width*height*(*bytesPerPixel))) == NULL) {
        printf("\nMemory allocation failure in ReadFilePGM().\n");fflush(stdout);
        FCLOSE(fp);
        status=1;
        goto Exit;
    }
    //   printf("\n\t\tAllocated %d bytes in ReadFilePGM().\n", width*height*(*bytesPerPixel));fflush(stdout);

    // TODO: check endianess to see if we need to switch the order later
    //chr = (width*height);
    chr = FREAD((*image), (*bytesPerPixel), (*n_cols)*(*n_rows), fp); /////CCS FILE LOAD: Comment this block until line 246 and set breakpoint here. Upload data of size (*n_cols)*(*n_rows) bytes to address *image.
    if (chr != (width*height)){
        printf("\nError reading the image data in ReadFilePGM().");fflush(stdout);
        FCLOSE(fp);
        free((*image));
        status= -1;
        goto Exit;
    }

    //  printf("\n\t\tRead %d pixels in ReadFilePGM().", chr);fflush(stdout);
    FCLOSE(fp);

    // printf("\n\tClosed file in ReadFilePGM().\n");fflush(stdout);
    Exit:
    return status;
}

int32_t writeFileYUV_ILE_IBE(const int8_t *outfilename,
        const uint8_t *image,
        uint16_t height,
        uint16_t width
)
{
    TI_FILE *fp;
    int32_t status= 0;

    /***************************************************************************
     * Open the output image file for writing if a filename was given. If no
     * filename was provided, set fp to write to standard output.
     ***************************************************************************/

    if((fp = FOPEN((const char*)outfilename, "wb")) == NULL){ 
        printf("Error writing the file %s in writeFileYUV_ILE_IBE().\n", outfilename);fflush(stdout);
        status= -1;
        goto Exit;
    }



    /***************************************************************************
     * Write the image data to the file.
     ***************************************************************************/
    if(height != FWRITE((void*)image, 2*width, height, fp)){ /////CCS FILE LOAD: Comment this block until line 288 and set breakpoint here. Download data of size 2*width*height bytes from address image.
        printf("Error writing the image data in writeFileYUV_ILE_IBE().\n");fflush(stdout);
        FCLOSE(fp);
        status= -1;
        goto Exit;
    }
    Exit:
    FCLOSE(fp);
    return status;
}

int32_t writeFileY(const int8_t *outfilename,
        const uint8_t *image,
        uint16_t height,
        uint16_t width
)
{
    TI_FILE *fp;
    int32_t status= 0;

    /***************************************************************************
     * Open the output image file for writing if a filename was given. If no
     * filename was provided, set fp to write to standard output.
     ***************************************************************************/

    if((fp = FOPEN((const char*)outfilename, "wb")) == NULL){
        printf("Error writing the file %s in writeFileY().\n", outfilename);fflush(stdout);
        status= -1;
        goto Exit;
    }


    /***************************************************************************
     * Write the image data to the file.
     ***************************************************************************/
    if(height != FWRITE((void*)image, width, height, fp)){ /////CCS FILE LOAD: Comment this block until line 325 and set breakpoint here. Download data of size width*height bytes from address image.
        printf("Error writing the image data in writeFileY().\n");fflush(stdout);
        FCLOSE(fp);
        status= -1;
        goto Exit;
    }
    Exit:
    FCLOSE(fp);
    return status;
}

int32_t writeFile_PGM(const int8_t *outfilename,
        const uint8_t *image,
        uint16_t n_rows,
        uint16_t n_cols,
        const int8_t *comment,
        int32_t maxval)
{
    TI_FILE *fp;
    int32_t status= 0;

    /***************************************************************************
     * Open the output image file for writing if a filename was given. If no
     * filename was provided, set fp to write to standard output.
     ***************************************************************************/

    if((fp = FOPEN((const char*)outfilename, "wb")) == NULL){
        printf("Error writing the file %s in WriteFile_PGM().\n", outfilename);fflush(stdout);
        status= -1;
        goto Exit;
    }


    /***************************************************************************
     * Write the header information to the PGM file.
     ***************************************************************************/
    FPRINTF(fp, "P5\n%d %d\n", n_cols, n_rows);
    if(comment != NULL)
        if(strlen((const char*)comment) <= 70) FPRINTF(fp, "# %s\n", comment);
    FPRINTF(fp, "%d\n", maxval);

    /***************************************************************************
     * Write the image data to the file.
     ***************************************************************************/
    if(n_rows != FWRITE((void*)image, n_cols, n_rows, fp)){ /////CCS FILE LOAD: Comment this block until line 370 and set breakpoint here. Download data of size n_cols *n_rows bytes from address image.
        printf("Error writing the image data in WriteFile_PGM().\n");fflush(stdout);
        FCLOSE(fp);
        status= -1;
        goto Exit;
    }
    Exit:
    FCLOSE(fp);
    return status;
}

int32_t writeFile_PPM(const int8_t *outfilename,
        const uint8_t *image_red,
        const uint8_t *image_grn,
        const uint8_t *image_blu,
        uint16_t n_rows,
        uint16_t n_cols,
        const int8_t *comment,
        int32_t maxval)
{
    TI_FILE *fp;
    uint32_t size, p;
    int32_t status= 0;

    /***************************************************************************
     * Open the output image file for writing if a filename was given. If no
     * filename was provided, set fp to write to standard output.
     ***************************************************************************/

    if((fp = FOPEN((const char*)outfilename, "wb")) == NULL){
        printf("Error writing the file %s in PPM_RESULT_writeFilePPM().\n", outfilename);fflush(stdout);
        status= -1;
        goto Exit;
    }

    /***************************************************************************
     * Write the header information to the PPM file.
     ***************************************************************************/
    FPRINTF(fp, "P6\n%d %d\n", n_cols, n_rows);
    if (comment != NULL)
        if(strlen((const char*)comment) <= 70) FPRINTF(fp, "# %s\n", comment);
    FPRINTF(fp, "%d\n", maxval);

    /***************************************************************************
     * Write the image data to the file.
     ***************************************************************************/
    size = n_rows * n_cols;

    for(p=0;p<size;p++){ /* Write the image in pixel interleaved format. */
        FWRITE((void*)&image_red[p], 1, 1, fp);
        FWRITE((void*)&image_grn[p], 1, 1, fp);
        FWRITE((void*)&image_blu[p], 1, 1, fp);
    }

    FCLOSE(fp);
    Exit:
    return status;
}

int32_t writeFile_YUV444(const int8_t *outfilename,
        const uint8_t *image_y,
        const uint8_t *image_u,
        const uint8_t *image_v,
        uint16_t n_rows,
        uint16_t n_cols,
        const int8_t *comment,
        int32_t maxval)
{
    TI_FILE *fp;
    uint32_t size;
    int32_t status= 0;

    /***************************************************************************
     * Open the output image file for writing if a filename was given. If no
     * filename was provided, set fp to write to standard output.
     ***************************************************************************/

    if((fp = FOPEN((const char*)outfilename, "wb")) == NULL){
        printf("Error writing the file %s in writeFileYUV444().\n", outfilename);fflush(stdout);
        status= -1;
        goto Exit;
    }

    /***************************************************************************
     * Write the image data to the file.
     ***************************************************************************/
    size = n_rows * n_cols;

    FWRITE((void*)image_y, 1, size, fp);
    FWRITE((void*)image_u, 1, size, fp);
    FWRITE((void*)image_v, 1, size, fp);

    FCLOSE(fp);
    Exit:
    return status;
}

int32_t writeFile_YUV420SP(const int8_t *outfilename,
        const uint8_t *image_y,
        const uint8_t *image_uv,
        uint16_t n_rows,
        uint16_t n_cols,
        const int8_t *comment,
        int32_t maxval)
{
    TI_FILE *fp;
    uint32_t size;
    int32_t status= 0;

    /***************************************************************************
     * Open the output image file for writing if a filename was given. If no
     * filename was provided, set fp to write to standard output.
     ***************************************************************************/

    if((fp = FOPEN((const char*)outfilename, "wb")) == NULL){
        printf("Error writing the file %s in writeFileYUV420SP().\n", outfilename);fflush(stdout);
        status= -1;
        goto Exit;
    }

    /***************************************************************************
     * Write the image data to the file.
     ***************************************************************************/
    size = n_rows * n_cols;

    FWRITE((void*)image_y, 1, size, fp);
    FWRITE((void*)image_uv, 1, size/2, fp);

    FCLOSE(fp);
    Exit:
    return status;
}

