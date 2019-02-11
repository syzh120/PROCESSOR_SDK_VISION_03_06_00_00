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

/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_vertical_non_max_suppression_config.h"
#include "../inc/vcop_vertical_non_max_suppression_cn.h"

#if VCOP_HOST_EMULATION
    #include "../src_kernelC/vcop_vertical_non_max_suppression_kernel.k"    // kernel source
#else
      #include "vcop_vertical_non_max_suppression_kernel.h"

#endif

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")
#define COMPARE_REFERENCE (1)
//#define __DEBUG

#define NUM_CORNERS  (256)
#define NUM_ITER (1)
#define MAX_CORNERS  (2048)

#pragma DATA_SECTION (corners, "Adata");
unsigned int corners[MAX_CORNERS];

#pragma DATA_SECTION (sad_scores, "Bdata");
unsigned short sad_scores[MAX_CORNERS];

#pragma DATA_SECTION (nms_corners, "Cdata");
unsigned int nms_corners[MAX_CORNERS];

#pragma DATA_SECTION (nms_y_corners, "Cdata");
unsigned int nms_y_corners[MAX_CORNERS+8];

#pragma DATA_SECTION (nms_id, "Adata");
unsigned short nms_id[MAX_CORNERS];

#pragma DATA_SECTION (nms_sad_scores, "Cdata");
unsigned int nms_sad_scores[MAX_CORNERS];

#pragma DATA_SECTION (nms_y_score, "Cdata");
unsigned short nms_y_score[MAX_CORNERS];

#pragma DATA_SECTION (nms_score, "Bdata");
unsigned int nms_score[MAX_CORNERS+8];

#pragma DATA_SECTION (Id, "Cdata");
unsigned char Id[8] = {1, 2, 3, 4, 5, 6, 7, 8};

#pragma DATA_SECTION (Ref_Out_XY, "Eoutdata");
unsigned int Ref_Out_XY[NUM_CORNERS] = {0x0};

#pragma DATA_SECTION (Ref_Out_Scores, "Eoutdata");
unsigned int Ref_Out_Scores[NUM_CORNERS] = {0x0};

static void CreateRandPattern16(unsigned short *p, unsigned short w, unsigned short h)
{
    int i;
    for (i = 0; i < w*h; i++)
    {
        p[i] = rand()&0xFFFF;
    }
}

static void CreateRandPattern32(unsigned int *p, unsigned short w, unsigned short h)
{
    int i;
    short id;
    int xy;
    for (i = 0; i < w*h; i++)
    {
        /* Create random pattern for X,Y 10-bit each */
        xy = rand()&0xFFFFF000;
        /* Create randmom patter for ID - 12 bit */
        id = rand() % MAX_CORNERS;
        p[i] = xy | id;
    }
}


void sort(unsigned int m, unsigned int x[])
{
    unsigned int i, j, t;

    for(i = 1; i <= m-1; i++)
        for(j = 1; j <= m-i; j++)
            if(x[j-1] >= x[j])
            {
                t = x[j-1];
                x[j-1] = x[j];
                x[j] = t;
            }
}

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '    '))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(svertical_nms_Config * params)
{
    strcpy(params->inputSrc, "RND_PTRN");
    params->num_corners  = NUM_CORNERS;
    params->numIter        = NUM_ITER;
    params->writeOutput = 0;
    params->seedForRND    = 0;
}

int writeOutputFile(unsigned int * output1, char * filename1, int num)
{
    FILE * fp1;
    int i;

    fp1 = fopen(filename1, "w+");

    if(fp1== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for(i=0;i<num;i++)
    {
        fprintf(fp1, "%d ", output1[i]);
    }
    fclose(fp1);

    return (0);
}


int readInputFile(void * input, unsigned short n, unsigned short w, unsigned short h, unsigned short stride, char * filename, int dataType)
{
    int i, j, k;
    FILE * fp;
    char * LinePtr;
    int status;
    int value;
    char inputLine[MAX_INPUT_LINE_SIZE];
    char inputValue[MAX_INPUT_VALUE_SIZE];

    fp = fopen(filename, "r");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }
    for(k = 0; k < n; k++)
    {
        for(i = 0; i < h; i++)
        {
            memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
            status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
            if ((status == EOF) || (status == 0))
            {
                printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
                return(-1);
            }
            LinePtr = inputLine;
            for(j = 0; j < w; j++)
            {
                sscanf(LinePtr, "%d",&value);
                sscanf(LinePtr, "%s",inputValue);
                if(dataType == 5)
                {
                  int * ptr = (int * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 4)
                {
                  unsigned int * ptr = (unsigned int * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 3)
                {
                  short * ptr = (short * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 2)
                {
                  unsigned short * ptr = (unsigned short * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 1)
                {
                  char * ptr = (char * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType ==0)
                {
                  unsigned char * ptr = (unsigned char * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                LinePtr = moveToNextElement(inputValue,LinePtr);
            }
        }
    }
  fclose(fp);
  return(0);
}

void test_vertical_nms_c_reference()
{
    int k;

    char refFile1[MAX_FILE_NAME_SIZE] = "../testvecs/reference/ref_out_xy.txt";
    char refFile2[MAX_FILE_NAME_SIZE] = "../testvecs/reference/ref_out_scores.txt";
    char inFile1[MAX_FILE_NAME_SIZE] = "../testvecs/input/input_image_xy.txt";
    char inFile2[MAX_FILE_NAME_SIZE] = "../testvecs/input/input_image_scores.txt";

    memset(corners, 0, sizeof(corners));
    memset(sad_scores, 0, sizeof(sad_scores));

    readInputFile(corners, 1, NUM_CORNERS, 1, NUM_CORNERS, inFile1, 4);
    readInputFile(sad_scores, 1, NUM_CORNERS, 1, NUM_CORNERS, inFile2, 2);

    /* C function call for vertical NMS */
    vertical_nms(&corners[0],
                NUM_CORNERS,
                &sad_scores[0],
                &nms_id[0],
                &nms_y_score[0],
                (unsigned short*)&nms_y_corners[0],
                &nms_corners[0],
                &nms_sad_scores[0]);



    readInputFile(Ref_Out_XY, 1, NUM_CORNERS, 1, NUM_CORNERS, refFile1, 4);
    readInputFile(Ref_Out_Scores, 1, NUM_CORNERS, 1, NUM_CORNERS, refFile2, 2);

    for(k=0; k<NUM_CORNERS; k++)
    {
        if((Ref_Out_XY[k] != nms_corners[k]) || (Ref_Out_Scores[k] != nms_sad_scores[k]))
        {
            printf("Mismatch in corners detected or Score: RefXY: %d, Ref Score: %d, C XY: %d, C Score: %d\n", Ref_Out_XY[k], nms_corners[k], Ref_Out_Scores[k], nms_sad_scores[k]);
            break;
           }
    }

}

int test_vcop_vertical_nms(svertical_nms_Config * params)
{
    unsigned int k, iter;
    int fail = 0;

    profiler_init();

    printf("\n Vertical NMS (16-bit) block level testing: \n");

    if(strcmp(params->inputSrc, "RND_PTRN") == 0)
    {
        printf("Pattern genereation Seed = %d\n", params->seedForRND);
        srand(params->seedForRND);
        CreateRandPattern32(corners, 1, params->num_corners);
        CreateRandPattern16(sad_scores, 1, params->num_corners);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE") == 0)
    {
         readInputFile(corners, 1, params->num_corners, 1, params->num_corners, params->inFile1Name, 4);
         readInputFile(sad_scores, 1, params->num_corners, 1, params->num_corners, params->inFile2Name, 2);
    }



    printf("Number of corners to apply NMS-Y on = %d \n", params->num_corners);

    sort(params->num_corners, corners);

#ifdef __DEBUG
    printf("Corners and their scores after NMS - before sort: \n");

    for(k=0;k<params->num_corners;k++)
     {
         printf("x: %d, y: %d, sad score: %d \n", (corners[k] >> 22), ((corners[k] & 0x003FF000) >> 12), sad_scores[k]);
     }
#endif

    for(iter = 0; iter<params->numIter; iter++)
    {
        if(params->max_corners == params->num_corners)
        {
            params->num_corners -= 8;;
        }

        profiler_start();

        vcop_vertical_non_max_suppression_kernel
                    (&corners[0],
                     params->num_corners,
                     params->max_corners,
                     &sad_scores[0],
                     nms_id,
                     nms_y_score,
                     (unsigned short*)nms_y_corners,
                     nms_y_corners,
                     nms_score,
                     &Id[0]);

        profiler_end();

#ifdef __DEBUG
        printf("Corners and their scores after kernel NMS: \n");

        for(k=0;k<params->num_corners;k++)
        {
            printf("x: %d, y: %d, sad score: %d \n", nms_y_corners[k] >> 16, nms_y_corners[k] & 0xFFFF, nms_score[k] >> 16);
        }
#endif

#ifdef COMPARE_REFERENCE
        
                /* C function call for vertical NMS */
                vertical_nms(&corners[0],
                            params->num_corners,
                            &sad_scores[0],
                            &nms_id[0],
                            &nms_y_score[0],
                            (unsigned short*)&nms_y_corners[0],
                            &nms_corners[0],
                            &nms_sad_scores[0]);
        
#ifdef __DEBUG
                printf("Corners and their scores after C function NMS: \n");
                for(k=0; k<params->num_corners; k++)
                {
                    printf("x: %d, y: %d, sad score: %d\n", nms_corners[k] >> 16, nms_corners[k] & 0xFFFF, nms_sad_scores[k] >> 16);
                }
#endif

        for(k=0; k<params->num_corners; k++)
        {
            if((nms_score[k]>>16) != (nms_sad_scores[k]>>16)) // Out is packed with Score and ID
            {
                printf("\n Mismatch in NMS corners: %d, %d \n", nms_score[k], nms_sad_scores[k]);
                fail = 1;
                break;
            }
        }

        printf(fail ? "FAIL\n" : "PASS\n");

#endif

    }

    profiler_deinit();

    if(params->writeOutput)
     {
        writeOutputFile(nms_y_corners, params->outFile1Name, params->num_corners);
        writeOutputFile(nms_score, params->outFile2Name, params->num_corners);
     }

    return 0;
}

int main()
{
    FILE * fp;
    char * LinePtr;
    int status;
    int lineNum = -1;
    svertical_nms_Config * params;
    int config_cmd;
    char configFileName[MAX_FILE_NAME_SIZE];

    params = (svertical_nms_Config *)(&gConfig_vertical_nms);

    fp = fopen(CONFIG_LIST_FILE_NAME, "r");
    if(fp== NULL)
    {
        printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
        fillDefaultConfig(params);
        test_vcop_vertical_nms(params);
        return(0);
    }

    while(1)
    {
        memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
        status = (int)fgets(params->configLine,MAX_CONFIG_LINE_SIZE,fp);
        LinePtr = params->configLine;
        if ((status == EOF) || (status == 0))
            break;
        lineNum++;
        sscanf(LinePtr, "%d",&config_cmd);
        sscanf(LinePtr, "%s",params->configParam);
        if(config_cmd == 0)
        {
            printf("End of config list found !\n");
            break;
        }
        else if(config_cmd == 2)
        {
            continue;
        }
        else if(config_cmd == 1)
        {
            LinePtr = moveToNextElement(params->configParam,LinePtr);
            status  = sscanf(LinePtr, "%s",configFileName);
            printf("Processing config file %s !\n", configFileName);
            fillDefaultConfig(params);
            status = readparamfile(configFileName, &gsTokenMap_vertical_nms[0]) ;
            if(status == -1)
            {
                printf("Parser Failed");
                return -1 ;
            }
            test_vcop_vertical_nms(params);
        }
        else
        {
            printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
        }
    }
    fclose(fp);
    return (0);


}


/*----------------------------------------------------------------------------*/
/* End of file: vcop_vertical_non_max_suppression_tb.c                        */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/


