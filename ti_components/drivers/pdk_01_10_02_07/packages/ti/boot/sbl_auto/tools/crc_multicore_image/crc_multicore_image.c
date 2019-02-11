/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     crc_mutlicore_image.c
 *
 *  \brief    This file contains the code that will generate CRC on RPRC images
 *            and add it to Multicore App Image Header. It also generates CRC
 *            for Multicore App Image Header.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MAX_INPUT_FILES     5

#define MAX_FILE_PATH_SIZE  (500)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct _meta_header_start_
{
    char     magic_string_str[4];
    uint32_t num_files;
    uint32_t dev_id;
    uint32_t multicore_hdr_crc_h;
    uint32_t multicore_hdr_crc_l;
    uint32_t multicore_image_size;
    uint32_t rsvd;
}meta_header_start;

typedef struct _meta_header_core_
{
    uint32_t is_core_image_valid;
    uint32_t core_id;
    uint32_t image_offset;
    uint32_t core_image_crc_h;
    uint32_t core_image_crc_l;
    uint32_t image_size;
}meta_header_core;

typedef struct _meta_header_end_
{
    uint32_t rsvd;
    char     magic_string_end[4];
}meta_header_end;

typedef struct _pad_data_
{
    uint32_t data;
}pad_data;

typedef struct _crc_data_
{
    uint32_t crc_h;
    uint32_t crc_l;
} crc_data;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t tiimage_swap32(uint32_t data)
{
    uint32_t result = 0;

    result  = (data & 0xFF000000) >> 24;
    result |= (data & 0x00FF0000) >> 8;
    result |= (data & 0x0000FF00) << 8;
    result |= (data & 0x000000FF) << 24;

    return result;
}

uint64_t calculate_crc(uint64_t crc, uint64_t data)
{
    int32_t  i, j;
    uint64_t nextCrc = 0;

    for (i = 63; i >= 0; i--)
    {
        nextCrc =
            (nextCrc &
             (uint64_t) 0xfffffffffffffffe) | ((crc >> 63) ^ (data >> i));

        for (j = 1; j < 64; j++)
        {
            if (j == 1 || j == 3 || j == 4)
            {
                nextCrc =
                    (nextCrc & ~((uint64_t) 1 << j)) |
                    ((((crc >> (j - 1)) ^ (crc >> 63) ^ (data >> i)) & 1) << j);
            }
            else
            {
                nextCrc =
                    (nextCrc &
                     ~((uint64_t) 1 << j)) | (((crc >> (j - 1)) & 1) << j);
            }
        }
        crc = nextCrc;
    }

    return crc;
}

void calculate_file_crc(FILE *fp, crc_data *crcD)
{
    uint64_t crcV = 0, fileData = 0;
    uint32_t fileSize, i;

    /* Calculate file size */
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    for (i = 0; i < fileSize / 8; i++)
    {
        fread(&fileData, 8, 1, fp);
        crcV = calculate_crc(crcV, fileData);
    }

    crcD->crc_l = crcV & 0xFFFFFFFFU;
    crcD->crc_h = (crcV >> 32U) & 0xFFFFFFFFU;
}

int32_t main(int32_t argc, char *argv[])
{
    FILE             *inFp, *outFp;
    char              inputFileName[MAX_FILE_PATH_SIZE+1], outputFile[MAX_FILE_PATH_SIZE+4];
    int32_t           inputFileSize = 0, i = 0, j = 0, k = 0;
    uint32_t          temp;

    meta_header_start hdr_start;
    meta_header_core  hdr_core[MAX_INPUT_FILES];
    meta_header_end   hdr_end;
    pad_data          pdata;
    uint32_t          header_size, is_header_appended = 0;

    FILE             *crcFp;
    char              crcTempFile[] = {"crcFile"};
    crc_data          crcVal;
    uint32_t          cur_crc_read_addr;
    FILE             *in_outFp;
    uint32_t          status = 0;

    char              appImageBEName[MAX_FILE_PATH_SIZE+1];

    if (argc < 3)
    {
        /* Expected usage */
        printf("Usage: \n");
        printf("CRC generator takes Multicore Images as input \n");
        printf("The output is placed in the same Multicore Images \n");
        printf(
            "Syntax: ./<executable file name> <Multicore_image_name_LE> <Multicore_image_name_BE>\n");
    }
    else
    {
        inFp = fopen(argv[1], "rb");
        if (!inFp)
        {
            printf("Error opening Multicore file!\n");
        }

        strncpy(inputFileName, argv[1], MAX_FILE_PATH_SIZE);
        strncpy(appImageBEName, argv[2], MAX_FILE_PATH_SIZE);
        strncpy(outputFile, argv[1], MAX_FILE_PATH_SIZE);
        strcat(outputFile, "_op");

        outFp = fopen(outputFile, "wb+");
        if (!outFp)
        {
            printf("Error opening/creating Outfile1!\n");
        }

        /* Calculate the size of the Input file and rewind to the begin of file
        **/
        fseek(inFp, 0, SEEK_END);
        inputFileSize = ftell(inFp);
        rewind(inFp);
        printf("size of App Image is %d bytes\n", inputFileSize);

        /* Read meta header start */
        fseek(inFp, 0, SEEK_SET);
        fread(&hdr_start, sizeof (hdr_start), 1, inFp);
        if ((0 != hdr_start.multicore_hdr_crc_h) ||
            (0 != hdr_start.multicore_hdr_crc_l))
        {
            printf("CRC is already present, exiting");
            fclose(outFp);
            remove(outputFile);
        }
        else
        {
            header_size = sizeof (hdr_start) +
                          (hdr_start.num_files) * sizeof (hdr_core[0]) +
                          sizeof (hdr_end);

            /* Read core headers */
            for (i = 0; i < hdr_start.num_files; i++)
            {
                fread(&hdr_core[i], sizeof (hdr_core[i]), 1, inFp);
            }

            /* Read header end */
            fread(&hdr_end, sizeof (hdr_end), 1, inFp);

            if (0 == (header_size % 8))
            {
                /* No padding is needed */
                is_header_appended = 0;
            }
            else
            {
                printf("Padding header with zeroes as header size is %d\n",
                       header_size);
                for (i = 0; i < hdr_start.num_files; i++)
                {
                    hdr_core[i].image_offset += 0x4;
                }
            }

            /* Insert Meta Header Start */
            fwrite(&hdr_start, sizeof (hdr_start), 1, outFp);

            /* Insert all core info in Meta Header */
            for (i = 0; i < hdr_start.num_files; i++)
            {
                fwrite(&hdr_core[i], sizeof (meta_header_core), 1, outFp);
            }

            /* Insert Meta Header End */
            fwrite(&hdr_end, sizeof (hdr_end), 1, outFp);

            if (0 != (header_size % 8))
            {
                pdata.data = 0;
                fwrite(&pdata.data, sizeof (pdata.data), 1, outFp);
                header_size += sizeof (pdata.data);
                hdr_start.multicore_image_size += sizeof (pdata.data);
                is_header_appended = 1;
            }

            /* Insert RPRC Images */
            for (i = 0; i < hdr_start.num_files; i++)
            {
                for (j = 0; j < hdr_core[i].image_size / 4; j++)
                {
                    fread(&temp, sizeof (temp), 1, inFp);
                    fwrite(&temp, sizeof (temp), 1, outFp);
                }

                if (0 != (hdr_core[i].image_size % 8))
                {
                    printf("Padded RPRC Image for Core ID:%d\n",
                           hdr_core[i].core_id);
                    pdata.data = 0;
                    fwrite(&pdata.data, sizeof (pdata.data), 1, outFp);
                    hdr_core[i].image_size         += 0x4;
                    hdr_start.multicore_image_size += sizeof (pdata.data);
                    for (k = i + 1; k < hdr_start.num_files; k++)
                    {
                        hdr_core[k].image_offset += 0x4;
                    }
                }
            }

            /* Write Updated Header */
            fseek(outFp, 0, SEEK_SET);
            /* Insert Meta Header Start */
            fwrite(&hdr_start, sizeof (hdr_start), 1, outFp);

            /* Insert all core info in Meta Header */
            for (i = 0; i < hdr_start.num_files; i++)
            {
                fwrite(&hdr_core[i], sizeof (meta_header_core), 1, outFp);
            }

            /* Insert Meta Header End */
            fwrite(&hdr_end, sizeof (hdr_end), 1, outFp);

            /* Open Temp CRC file */
            crcFp = fopen(crcTempFile, "wb+");
            if (!crcFp)
            {
                printf("Error opening/creating CRC Temp File\n");
            }
            else
            {
                /* Write Contents to Temp CRC file */
                /* Insert Meta Header Start */
                fwrite(&hdr_start, sizeof (hdr_start), 1, crcFp);

                /* Insert all core info in Meta Header */
                for (i = 0; i < hdr_start.num_files; i++)
                {
                    fwrite(&hdr_core[i], sizeof (meta_header_core), 1, crcFp);
                }

                /* Insert Meta Header End */
                fwrite(&hdr_end, sizeof (hdr_end), 1, crcFp);

                if (1 == is_header_appended)
                {
                    pdata.data = 0;
                    fwrite(&pdata.data, sizeof (pdata.data), 1, crcFp);
                }
                cur_crc_read_addr = ftell(crcFp);
                crcVal.crc_h      = 0;
                crcVal.crc_l      = 0;
                calculate_file_crc(crcFp, &crcVal);
                fclose(crcFp);

                hdr_start.multicore_hdr_crc_h = crcVal.crc_h;
                hdr_start.multicore_hdr_crc_l = crcVal.crc_l;

                /* Open output file for reading */
                in_outFp = fopen(outputFile, "rb");

                /* Calculate CRC for RPRC Images */
                for (i = 0; i < hdr_start.num_files; i++)
                {
                    /* Open Temp CRC file again, this will clear contents */
                    crcFp = fopen(crcTempFile, "wb+");
                    if (!crcFp)
                    {
                        printf(
                            "Error opening/creating CRC Temp File for RPRC File%d\n",
                            i);
                    }
                    fseek(in_outFp, cur_crc_read_addr, SEEK_SET);
                    for (j = 0; j < hdr_core[i].image_size / 4; j++)
                    {
                        fread(&temp, sizeof (temp), 1, in_outFp);
                        fwrite(&temp, sizeof (temp), 1, crcFp);
                    }
                    cur_crc_read_addr += ftell(crcFp);
                    crcVal.crc_h       = 0;
                    crcVal.crc_l       = 0;
                    calculate_file_crc(crcFp, &crcVal);

                    hdr_core[i].core_image_crc_h = crcVal.crc_h;
                    hdr_core[i].core_image_crc_l = crcVal.crc_l;
                    fclose(crcFp);
                }

                /* Write Updated Header */
                fseek(outFp, 0, SEEK_SET);
                /* Insert Meta Header Start */
                fwrite(&hdr_start, sizeof (hdr_start), 1, outFp);

                /* Insert all core info in Meta Header */
                for (i = 0; i < hdr_start.num_files; i++)
                {
                    fwrite(&hdr_core[i], sizeof (meta_header_core), 1, outFp);
                }

                /* Insert Meta Header End */
                fwrite(&hdr_end, sizeof (hdr_end), 1, outFp);

                /* Remove files that are not needed */
                fclose(inFp);
                fclose(outFp);
                fclose(in_outFp);
                status = remove(argv[1]);
                if (0 != status)
                {
                    printf("Failed to modify original input file\n");
                }
                status = rename(outputFile, inputFileName);
                if (0 != status)
                {
                    printf("Failed to rename output file\n");
                }
                status = remove(crcTempFile);
                if (0 != status)
                {
                    printf("Failed to remove CRC temp file\n");
                }

                /* Now the new AppImage_LE is input and AppImage_BE will be
                 * output
                 */
                inFp = fopen(inputFileName, "rb");
                if (!inFp)
                {
                    printf("Error opening AppImage_LE!\n");
                }
                outFp = fopen(appImageBEName, "wb+");
                if (!outFp)
                {
                    printf("Error opening/creating AppImage_BE!\n");
                }

                /* Calculate the size of the Input file and rewind to the begin
                 * of file
                 **/
                fseek(inFp, 0, SEEK_END);
                inputFileSize = ftell(inFp);
                rewind(inFp);
                for (i = 0; i < inputFileSize / 4; i++)
                {
                    fread(&temp, sizeof (temp), 1, inFp);
                    temp = tiimage_swap32(temp);
                    fwrite(&temp, sizeof (temp), 1, outFp);
                }

                fclose(inFp);
                fclose(outFp);
            }
        }
    }

    printf("\n");
    return (0);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

