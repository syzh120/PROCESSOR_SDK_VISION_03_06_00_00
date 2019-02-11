/*
* Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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

/**
*  \file tfdtp_host_app.c
*
*  \brief TFDTP Host Application source file.
*/


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

/* This module's header */
#include "sockets.h"
#include "tfdtp_api.h"
#include "../common/test_common.h"
#include "tfdtp_test_client.h"
#include "tfdtp_utils.h"

/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define STRESS_TEST         (0)

/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

void ShowUsage();
void ParseCmdLineArgs(int argc, char *argv[]);

/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

App_Obj gApp_obj;

/*---------------------------------------------------------------------------*\
|                          Function Definitions                        |
\*---------------------------------------------------------------------------*/

/*
*  ======== main ========
*/
int main(int argc, char *argv[])
{
    char * name = argv[0];
    uint32_t i, j, cnt, loop;
    int status = EXIT_SUCCESS;
    FILE * input_fp = NULL;
    FILE * output_fp = NULL;
    long file_size;
    char * frame_buffer = NULL;
    uint32_t frame_size;
    uint32_t buf_id, frame_id;
    bool done = false;
    uint32_t *dataPtr;
    uint32_t rxVal, bufState;

    memset(&gApp_obj, 0, sizeof(App_Obj));

    ParseCmdLineArgs(argc, argv);

    if (gApp_obj.tfdtpParam.frameSize == 0)
    {
        fprintf(stderr, "%s: invalid frame size (%d)\n", name, gApp_obj.tfdtpParam.frameSize);
        status = -1;
    }
    if (gApp_obj.tfdtpParam.direction == DIR_TX)
    {
        /* Open & copy input file into ram */
        input_fp = fopen(gApp_obj.filename, "rb");
        if (NULL == input_fp) {
            fprintf(stderr, "%s: File open failed\n", name);
            status = -1;
            goto QUIT;
        }
        fseek(input_fp, 0, SEEK_END);
        file_size = ftell(input_fp);
        rewind(input_fp);
        if (gApp_obj.tfdtpParam.frameSize > file_size)
        {
            fprintf(stderr, "%s: invalid frame size (%d)\n", name, gApp_obj.tfdtpParam.frameSize);
            status = -1;
        }
    }
    else if (gApp_obj.tfdtpParam.direction == DIR_RX)
    {
        if (gApp_obj.filename != NULL)
        {
            /* Open output file for writing */
            output_fp = fopen(gApp_obj.filename, "wb");
            if (NULL == output_fp)
            {
                fprintf(stderr, "%s: File open failed\n", name);
                status = -1;
                goto QUIT;
            }
        }
    }
    else
    {
        fprintf(stderr, "%s: No valid direction specified\n", name);
        status = -1;
        goto QUIT;
    }

    gApp_obj.tfdtpObj = TFDTP_open(&gApp_obj.tfdtpParam);

    if (gApp_obj.tfdtpObj == NULL)
    {
        fprintf(stderr, "%s: TFDTP_open failed\n", name);
        goto QUIT;
    }

    printf("\nEntering Test Client \n");
    /* Send host MAC and IP address and start TFDTP on target */
    status = tfdtp_testClient_start(gApp_obj.tfdtpObj, gApp_obj.srcIpAddr);
    if (status < 0)
    {
        fprintf(stderr, "%s: tfdtp_testClient_start failed\n", name);
        goto QUIT;
    }
    //getchar();

    while (!done)
    {
        printf("\nTransfer Starts.\n");
        for (loop = 0; loop < gApp_obj.numLoop; loop++)
        {
            if (gApp_obj.tfdtpParam.direction == DIR_TX)
            {
                rewind(input_fp);
                frame_buffer = gApp_obj.tfdtpObj->bufDes[gApp_obj.tfdtpObj->curBufIndex].bufAddr;
                frame_size = gApp_obj.tfdtpObj->bufDes[gApp_obj.tfdtpObj->curBufIndex].frameSize;
                uint32_t frameCnt = 0;
                for (i = 0; i <= (file_size - frame_size); i += frame_size)
                {
                    cnt = fread(frame_buffer, 1, frame_size, input_fp);
                    if (cnt != frame_size)
                    {
                        status = getError();
                        fprintf(stderr, "%s: failed to read %s (%d)\n", name, gApp_obj.filename, status);
                        goto QUIT;
                    }
                    /* Send one frame to target via TFDTP */
                    status = TFDTP_send(gApp_obj.tfdtpObj);
                    if (status != 0)
                    {
                        fprintf(stderr, "%s: failed to send packet.\n", name);
                        goto QUIT;
                    }
                    frameCnt++;
                }
                printf("\nSent [%d] frames.\n", frameCnt);
                print_stats(&gApp_obj);
            }
            else
            {
                if (output_fp)
                {
                    rewind(output_fp);
                }
                printf("Starting TFDTP Transmit test on Target\n");
                /* Send START command */
                status = TFDTP_TestClient_sendCmd(gApp_obj.tfdtpObj, TEST_CMD_START_TFDTP_TX, NULL);

                for (i = 0; i < gApp_obj.numRxFrame; i++)
                {
                    buf_id = gApp_obj.tfdtpObj->curBufIndex;

                    /* Receive one frame from target via TFDTP */
                    status = TFDTP_recv(gApp_obj.tfdtpObj);

                    bufState     = gApp_obj.tfdtpObj->bufDes[buf_id].bufState;
                    frame_buffer = gApp_obj.tfdtpObj->bufDes[buf_id].bufAddr;
                    frame_id     = gApp_obj.tfdtpObj->bufDes[buf_id].frameId;
                    frame_size   = gApp_obj.tfdtpObj->bufDes[buf_id].frameSize;
                    if (status != 0)
                    {
                        if(BUFF_PARTIAL == bufState)
                        {
                            gApp_obj.tfdtpObj->stats.partialFrameCnt++;
                            if (output_fp)
                            {
                                /* Write data back to output file */
                                cnt = fwrite(frame_buffer, 1, frame_size, output_fp);
                                if (cnt != frame_size)
                                {
                                    status = getError();
                                    fprintf(stderr, "%s: failed to write %s (%d)\n", name, gApp_obj.filename, status);
                                    goto QUIT;
                                }
                            }
                        }
                        else
                        {
                            gApp_obj.tfdtpObj->stats.errorCnt++;
                        }
                    }
                    else
                    {
                        if (output_fp)
                        {
                            /* Write data back to output file */
                            cnt = fwrite(frame_buffer, 1, frame_size, output_fp);
                            if (cnt != frame_size)
                            {
                                status = getError();
                                fprintf(stderr, "%s: failed to write %s (%d)\n", name, gApp_obj.filename, status);
                                goto QUIT;
                            }
                        }
                        else
                        {
                            /* Validate test data on receive */
                            /* Get frame id of this the loop */
                            uint32_t currFrameId = (frame_id%gApp_obj.numRxFrame);
                            dataPtr = (uint32_t *)(frame_buffer);
                            /* Do data validation check only at lower data rate */
                            for (j = 0; j < TEST_DATA_SIZE; j += 4)
                            {
                                rxVal = (currFrameId + (TEST_DATA_PATTERN * j));
                                if (*dataPtr != rxVal)
                                {
                                    gApp_obj.tfdtpObj->stats.dataMatchFailCnt++;
                                    break;
                                }
                                dataPtr++;
                            }

                            if (j == TEST_DATA_SIZE)
                            {
                                dataPtr = (uint32_t *)(frame_buffer + frame_size);
                                for (j = 0; j <TEST_DATA_SIZE; j += 4)
                                {
                                    dataPtr--;
                                    rxVal = (currFrameId + (TEST_DATA_PATTERN * j));
                                    if (*dataPtr != rxVal)
                                    {
                                        gApp_obj.tfdtpObj->stats.dataMatchFailCnt++;
                                        break;
                                    }
                                }
                            }


                        }
                    }
                }
                print_stats(&gApp_obj);
                /* Print statistics */
                print_appStats(&gApp_obj);
                {
                    printf("Stopping TFDTP Transmit test on Target\n");
                    /* Send STOP command */
                    status = TFDTP_TestClient_sendCmd(gApp_obj.tfdtpObj, TEST_CMD_STOP_TFDTP_TX, NULL);
                }
            }
            printf("Iteration %d Complete.\n", loop);
        }
#if (0 == STRESS_TEST)
        printf("\nTransfer Complete. Press 'x' to exit and any other key to repeat.\n");
        int key = getchar();
        if (key == 'x')
        {
            done = true;
        }
        else
        {
            while ((key = getchar()) != '\n' && key != EOF);
        }
#endif
    }
    status = gApp_obj.tfdtpObj->stats.errorCnt;

QUIT:
    printf("\nTest Status [%d]\n", status);
    printf("Stopping TFDTP stack on server\n");
    /* Send STOP command */
    status = TFDTP_TestClient_sendCmd(gApp_obj.tfdtpObj, TEST_CMD_STOP_TFDTP, NULL);

    /* Close TFDTP */
    TFDTP_close(gApp_obj.tfdtpObj);

    if (input_fp)
    {
        fclose(input_fp);
    }

    if (output_fp)
    {
        fclose(output_fp);
    }

    if (status != 0)
    {
        return EXIT_FAILURE;
    }
    else
    {
        return EXIT_SUCCESS;
    }
}


void ShowUsage()
{
    printf(" \n");
    printf("# \n");
    printf("# tfdtp_test --host_ip <ipaddr> --target_ip <ipaddr> [--ch <ch id>] --dir <tx:0|rx:1>\n");
    printf("#            --file <filename> --num_frame <# of RX frames> --frame_size <# of bytes>\n");
    printf("#            [--num_loop <# of iterations>]\n");
    printf("#            [--data-rate <throughput(TX) in Mbps>] [--validate-data<yes:1>]\n");
    printf("# \n");
    printf("# (c) Texas Instruments 2016\n");
    printf("# \n");
    printf("# \n");
    exit(0);
}

void ParseCmdLineArgs(int argc, char *argv[])
{
    int i;
    uint32_t numFrameFlag = 0, channelFlag = 0, inputFileFlag = 0;

    gApp_obj.tfdtpParam.cmdPort = TEST_CMD_PORT;
    gApp_obj.tfdtpParam.udpPort = TEST_UDP_PORT;
    gApp_obj.tfdtpParam.chId = 0;
    gApp_obj.tfdtpParam.thruput = TEST_DEFAULT_RX_THRUPUT;
    gApp_obj.numLoop = 1;

    for (i = 0; i<argc; i++)
    {
        if (strcmp(argv[i], "--host_ip") == 0)
        {
            i++;
            if (i >= argc)
            {
                ShowUsage();
            }
            strcpy(gApp_obj.srcIpAddr, argv[i]);
        }
        else if (strcmp(argv[i], "--target_ip") == 0)
        {
            i++;
            if (i >= argc)
            {
                ShowUsage();
            }
            strcpy(gApp_obj.tfdtpParam.destIpAddr, argv[i]);
        }
        else if (strcmp(argv[i], "--ch") == 0)
        {
            i++;
            if (i >= argc)
            {
                ShowUsage();
            }

            gApp_obj.tfdtpParam.chId = atoi(argv[i]);
            channelFlag = 1;
        }
        else if (strcmp(argv[i], "--dir") == 0)
        {
            i++;
            if (i >= argc)
            {
                ShowUsage();
            }
            gApp_obj.tfdtpParam.direction = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "--file") == 0)
        {
            i++;
            if (i >= argc)
            {
                ShowUsage();
            }
            gApp_obj.filename = argv[i];
            inputFileFlag = 1;
        }
        else if (strcmp(argv[i], "--num_frame") == 0)
        {
            i++;
            if (i >= argc)
            {
                ShowUsage();
            }
            gApp_obj.numRxFrame = atoi(argv[i]);
            gApp_obj.tfdtpParam.numRxFrame = atoi(argv[i]);
            numFrameFlag = 1;
        }
        else if (strcmp(argv[i], "--frame_size") == 0)
        {
            i++;
            if (i >= argc)
            {
                ShowUsage();
            }
            gApp_obj.tfdtpParam.frameSize = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "--num_loop") == 0)
        {
            i++;
            if (i >= argc)
            {
                ShowUsage();
            }
            gApp_obj.numLoop = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "--data-rate") == 0)
        {
            i++;
            if (i >= argc)
            {
                ShowUsage();
            }
            gApp_obj.tfdtpParam.thruput = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "--validate-data") == 0)
        {
            i++;
            if (i >= argc)
            {
                ShowUsage();
            }
            if(atoi(argv[i]) == 1)
                gApp_obj.tfdtpParam.enableDataValFlag = true;
        }
    }
    if (channelFlag != 1)
    {
        gApp_obj.tfdtpParam.chId = TEST_CHANNEL_ID;
        printf(" Channel Id not given, using default chId 56 \n");
    }

    if (gApp_obj.tfdtpParam.direction == 1)
    {
        if (1 != numFrameFlag)
            printf(" For receive --num_frame should be given, remaining frames will be dropped \n");
        if (1 != inputFileFlag)
            printf(" Output file not given, dropping all received frames \n");
    }

    if (gApp_obj.srcIpAddr[0] == 0
        ||
        gApp_obj.tfdtpParam.destIpAddr[0] == 0
        ||
        ((gApp_obj.filename == NULL) && (gApp_obj.tfdtpParam.direction == DIR_TX))
        )
    {
        if (gApp_obj.srcIpAddr[0] == 0)
        {
            printf("# ERROR: Source IP Address of server MUST be specified\n");
        }
        else if (gApp_obj.tfdtpParam.destIpAddr[0] == 0)
        {
            printf("# ERROR: Destination IP Address of server MUST be specified\n");
        }
        else if (gApp_obj.filename[0] == 0)
        {
            printf("# ERROR: Filename MUST be specified\n");
        }

        ShowUsage();
        exit(0);
    }
}

