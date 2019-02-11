/*
 *  Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file   mflash_uart.c
 *
 * \brief  This file contains the program for the Mflash PC side.
           These APIs are used for configuration
 *         of instance, transmission and reception of data.
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <linux/serial.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#endif

/* ========================================================================== */
/*                             Defines                                        */
/* ========================================================================== */

/**
 * \brief  These macros define the commands used to communicate with the RBL
 */
#define PERI_REQ 0xF0030002
#define ASIC_REQ 0xF0030003

/**
 * \brief  These macros define some parameters passed to the UART configuration
 */
#ifdef _WIN32
#define BAUD_RATE_115200    (115200U)
#define BAUD_RATE_921600    (921600U)
#else
#define BAUD_RATE_115200    B115200
#define BAUD_RATE_921600    B921600
#endif
#define BAUD_RATE_3686400   (3686400U)
#define BAUD_RATE_12000000  (12000000U)

#ifndef EVENPARITY
#define EVENPARITY  0
#define ODDPARITY   1
#define NOPARITY    3
#endif

/**
 * \brief  These macros define the prefix of the COM port id on the PC
 */
#ifdef _WIN32
#define MFLASH_PORT_PREFIX "\\\\.\\COM"
#define MFlash_startPort2 MFlash_startPort
#else
#define MFLASH_PORT_PREFIX "/dev/ttyUSB"
#endif

/**
 * \brief  This macro defines the buffer size of the chunk that is sent
 */
#define MFLASH_BUFFER (64U * 1024U)

/**
 * \brief  This macro tells the UART Rx FIFO Trigger Level on board. All the
 *         file data is sent in multiples of UART_FIFO_TRIGGER. To do this some extra
 *         bytes are appended at the end.
 */
#define UART_FIFO_TRIGGER (16U)


#define TDA3XXevm              (1U)
#define TDA2PXevm              (2U)
#define TDA2EXevm              (3U)
#define TDA3XXrvp              (4U)
#define TDA2XXevm              (5U)

#define SBL_MFLASH_CMD_HNDSKE_STEP1     "Mflash Begins!!\r\n"
/* ========================================================================== */
/*                             Typedefs                                       */
/* ========================================================================== */

/**
 * \brief  These typedef combine the different data_types used in WIN and LINUX
 *         into one single type for abstraction.
 */
#ifdef _WIN32
typedef HANDLE MFlash_Descriptor;
typedef DWORD  MFlash_Word;
#else
typedef int32_t MFlash_Descriptor;
typedef uint32_t MFlash_Word;
#endif
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * \brief  Used to calculate the filesize of a given file
 */
uint32_t MFlash_getFileSize(char *fileName)
{
    struct stat st;
    if(stat(fileName, &st) < 0)
    {
        printf("\n[PC][error] File Not Found: %s\n", fileName);
        exit(-1);
    }
    uint32_t size = st.st_size;
    return size;
}

/**
 * \brief  Put a delay of mseconds milliseconds
 */
void MFlash_putDelay(uint32_t mseconds)
{
    clock_t goal = mseconds + clock();
    while(goal > clock()){};
}

/**
 * \brief  Used to find the smaller unsigned integer
 */
uint32_t MFlash_getMinInt(uint32_t a, uint32_t b)
{
    if(a > b)
    {
        return b;
    }
    return a;
}

#ifdef _WIN32
/**
 * \brief  Writes lpBuffer to the hComm port
 */
uint32_t MFlash_puts(MFlash_Descriptor hComm, uint8_t *lpBuffer,
                     uint32_t bytestoWrite)
{
    // No of bytes written to the port
    MFlash_Word dNoOfBytesWritten = 0U;
    WriteFile(hComm,                // Handle to the Serial port
            lpBuffer,               // Data to be written to the port
            bytestoWrite,           //No of bytes to write
            &dNoOfBytesWritten,     //Bytes written
            NULL);
    return dNoOfBytesWritten;
}

/**
 * \brief  Start a serial communication port with given parity and baud
 */
MFlash_Descriptor MFlash_startPort(char *port, uint8_t parity, uint32_t baud)
{
    char read;
    MFlash_Descriptor hComm;
    hComm = CreateFile(port,
                      GENERIC_READ | GENERIC_WRITE,  //Read/Write
                      0U,                             // No Sharing
                      NULL,                          // No Security
                      OPEN_EXISTING,                 // Open existing port only
                      0U,                             // Non Overlapped I/O
                      NULL);

    // Initializing DCB structure
    DCB dcbSerialParams;
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    GetCommState(hComm, &dcbSerialParams);

    dcbSerialParams.BaudRate = baud;        // Setting BaudRate = baud
    dcbSerialParams.ByteSize = 8U;           // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;  // Setting StopBits = 1
    dcbSerialParams.Parity   = parity;      // Setting Parity = parity

    SetCommState(hComm, &dcbSerialParams);

    GetCommState(hComm, &dcbSerialParams);
    printf("\n     Baud     = %d", dcbSerialParams.BaudRate);
    printf("\n     Parity   = %d", dcbSerialParams.Parity);
    printf("\n     StopBits = %d", dcbSerialParams.StopBits);
    printf("\n     ByteSize = %d", dcbSerialParams.ByteSize);

    PurgeComm(hComm, PURGE_RXABORT);

    return hComm;
}

/**
 * \brief  Used to get a string of given lenght from the COM Port
 */
MFlash_Word MFlash_gets(MFlash_Descriptor hComm, uint8_t *buffer,
                        uint32_t noOfBytestoRead)
{
    MFlash_Word noOfBytesRead;
    ReadFile(hComm,            //Handle of the Serial port
              buffer,           //temporary character
              noOfBytestoRead,  //Size of tempChar
              &noOfBytesRead,   //Number of bytes read
              NULL);
    return noOfBytesRead;
}

/**
 * \brief  Used to free the port handle
 */
void MFlash_stopPort(MFlash_Descriptor hComm)
{
    CloseHandle(hComm);
}

#else
/**
 * \brief  Writes lpBuffer to the hComm port
 */
uint32_t MFlash_puts(int32_t hComm, uint8_t *lpBuffer,
                     uint32_t noOfBytesToWrite)
{
    // No of bytes written to the port
    uint32_t dNoOfBytesWritten = 0U;
    dNoOfBytesWritten = write(hComm, lpBuffer, noOfBytesToWrite);
    return dNoOfBytesWritten;
}

/**
 * \brief  Start a serial communication port with given parity and baud
 */
int32_t MFlash_startPort(char *port, uint8_t parity, uint32_t baud)
{
    struct termios tty;
    struct serial_struct serinfo;
    int32_t fd;

    fd = open(port, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        printf("error opening %s", port);
        return fd;
    }

    if(tcgetattr(fd, &tty) != 0)
    {
        printf("Error getting the attributes of the port\n");
        return -1;
    }

    if(baud == B115200)
    {
        cfsetospeed(&tty, baud);
        cfsetispeed(&tty, baud);
    }
    else
    {
        printf("Not supported by this API\n");
        return -1;
    }
    fcntl(fd, F_SETFL, 0);

    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

    tty.c_oflag &= ~OPOST;

    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

	if(parity == EVENPARITY)
    {
	    tty.c_cflag |= (CLOCAL | CREAD);
        tty.c_cflag |= PARENB;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8;
	    tty.c_cflag &= ~CRTSCTS;
    }
    else
    {
        printf("Invalid parity type\n");
    }

    if (tcsetattr(fd, TCSANOW, &tty) != 0U)
    {
        printf("error from tcsetattr");
        return -1;
    }

    sleep(2U);
    //tcflush(fd, TCIOFLUSH);
    return fd;
}

int32_t MFlash_startPort2(char *port, uint8_t parity, uint32_t baud)
{
    struct termios tty;
    struct serial_struct serinfo;
    int32_t fd;

    fd = open(port, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        printf("error opening %s", port);
        return fd;
    }

    if(tcgetattr(fd, &tty) != 0)
    {
        printf("Error getting the attributes of the port\n");
        return -1;
    }

    if(baud == B115200 || baud == B921600)
    {
        cfsetospeed(&tty, baud);
        cfsetispeed(&tty, baud);
    }
    else if(baud == BAUD_RATE_3686400 || baud == BAUD_RATE_12000000)
    {
        serinfo.reserved_char[0] = 0U;
        ioctl(fd, TIOCGSERIAL, &serinfo);
        serinfo.flags = (serinfo.flags & ~ASYNC_SPD_MASK) | ASYNC_SPD_CUST;
        serinfo.custom_divisor = (serinfo.baud_base + (baud / 2U)) / baud;
        uint32_t closestSpeed = serinfo.baud_base/serinfo.custom_divisor;

        ioctl(fd, TIOCSSERIAL, &serinfo);
        ioctl(fd, TIOCGSERIAL, &serinfo);
        cfsetospeed(&tty, B38400);
        cfsetispeed(&tty, B38400);
        cfmakeraw(&tty);
    }

    fcntl(fd, F_SETFL, 0);

    //Enable the receiver and set local mode
    tty.c_cflag |= (CLOCAL | CREAD);

    //setting up parity
    if (parity == NOPARITY)
    {
        tty.c_cflag &= ~PARENB;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8;
    }
    else
    {
        printf("Invalid parity type\n");
    }

    //shut off software control flow
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    //disable hardware flow control
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0U)
    {
        printf("error from tcsetattr");
        return -1;
    }

    sleep(4U);
    tcflush(fd, TCIOFLUSH);
    return fd;
}

/**
 * \brief  Used to get a string of given lenght from the COM Port
 */
uint32_t MFlash_gets(MFlash_Descriptor  hComm, uint8_t *buffer,
                    uint32_t dNoOFBytestoRead)
{
    uint32_t dNoOFBytesRead = read(hComm, buffer, dNoOFBytestoRead);
    return dNoOFBytesRead;
}

/**
 * \brief  Used to free the port handle
 */
void MFlash_stopPort(MFlash_Descriptor  hComm)
{
	close(hComm);
}
#endif

/**
 * \brief  Used to send the file to UART in chunks
 */
uint8_t MFlash_putFileInPatches(MFlash_Descriptor hComm, char *fileName,
                                uint32_t size)
{
    uint8_t buffer[MFLASH_BUFFER];
    FILE *ptr;
    uint8_t byteRead;
    uint32_t  noBytesRead;
    uint32_t countSize = size;
    uint32_t sizeToSend;
    uint8_t extraBytesReq;
    uint8_t appendExtra[16];
    uint32_t percount = 0;
    printf("[PC] File Size  = %d\n", size );

    // r for read, b for binary
    ptr = fopen(fileName, "rb");
    if(ptr == NULL)
    {
       printf("Invalid File Name\n");
    }

    MFlash_puts(hComm, (uint8_t *)"1", 1);
    printf("[PC] ");

    byteRead = 0U;
    while(byteRead != 4)
    {
        noBytesRead = MFlash_gets(hComm, &byteRead, 1U);
        if(byteRead == 6 && noBytesRead != 0U)
        {
            sizeToSend = MFlash_getMinInt(MFLASH_BUFFER, countSize);
            fread(buffer, 1, sizeToSend, ptr);
            if(sizeToSend % UART_FIFO_TRIGGER != 0U)
            {
                extraBytesReq = 16U - (sizeToSend % UART_FIFO_TRIGGER);
                while(extraBytesReq--)
                {
                    *(buffer + sizeToSend + extraBytesReq) = '0';
                }
            sizeToSend = (sizeToSend / 16U + 1U ) * 16U;
            }
            MFlash_puts(hComm, buffer, (uint32_t)sizeToSend);
            countSize = countSize - sizeToSend;

            uint8_t PerTransferred = ((size - countSize) * 100.0 / size);
            if( PerTransferred > percount)
            {
                printf("#");
                fflush(stdout);
                percount += 5;
            }
            byteRead = 0U;
        }
        else if(noBytesRead != 0U)
        {
            printf("%c ", byteRead);
        }
    }
    printf("\n[PC] Write File Completed.\n");
}

/**
 * \brief  Used to send a character to the sbl when it demands
 */
void MFlash_putChar(MFlash_Descriptor hComm, uint8_t count)
{
    uint8_t choice[2];

    if(count == 0U)
    {
    	choice[0] = '1';
    	choice[1] = '\r';
    	MFlash_puts(hComm, choice, 2U);
    }
    else if(count == 10U)
    {
    	choice[0] = '3';
    	choice[1] = '\r';
    	MFlash_puts(hComm, choice, 2U);
    }
    else
    {
    	choice[0] = '2';
    	choice[1] = '\r';
    	MFlash_puts(hComm, choice, 2U);
    }
}

/**
 * \brief  Used to send a Hex value to the sbl when it demands
 */
void MFlash_putHex(MFlash_Descriptor hComm, char hex[10])
{
    uint8_t size = strlen(hex);
    hex[size] = '\r';
    size = size + 1;
    MFlash_puts(hComm, (uint8_t *)hex, size);
}

/**
 * \brief  Used to send the filesize to the sbl when it demands
 */
void MFlash_putFileSize(MFlash_Descriptor hComm, char file[100])
{
    uint32_t filesize = MFlash_getFileSize(file);
    char fileSizeString[100];
    snprintf (fileSizeString, 100U, "%d\r", filesize);
    MFlash_puts(hComm, (uint8_t *)fileSizeString, strlen(fileSizeString));
}

/**
 * \brief  Used to send a file to the sbl when it demands
 */
void MFlash_putFile(MFlash_Descriptor hComm, char file[100])
{
    printf("\n[PC] Download started");
    time_t begin = time(NULL);
    MFlash_putFileInPatches(hComm, file, MFlash_getFileSize(file));
    time_t end = time(NULL);
    printf("\n[PC] Time taken to download file  = %.2f", (double)(end - begin));
}

/**
 * \brief  Read the 70 character ASCI ID from the RBL
 */
void MFlash_getASICId(MFlash_Descriptor hComm)
{
    uint8_t temp=0;
    uint32_t  noBytesRead;
    int32_t i;

    i = 69U;

    do
    {
        noBytesRead = MFlash_gets(hComm, &temp, 1);
    }while(temp != 4 || noBytesRead == 0);
    printf("[RBL]%x\t", temp);

    while(i)
    {
        noBytesRead = MFlash_gets(hComm, &temp, 1);
        if(noBytesRead != 0)
	{
		printf("[RBL]%x\t", temp);
        	i--;
	}
    }
}

/**
 * \brief  Write sbl_mflash to the UART Port
 */
uint8_t MFlash_putSblMflash(MFlash_Descriptor hComm, char *fileName,
                            uint32_t size)
{
    uint8_t buffer[MFLASH_BUFFER];
    int32_t countSize;
    uint32_t sizeToSend;
    FILE *ptr;

    ptr = fopen(fileName, "rb");
    printf("\n[PC] File Size  = %d\n", size );
    printf("[PC] ");

    countSize = size;
    while(countSize > 0U)
    {
        sizeToSend = MFlash_getMinInt(MFLASH_BUFFER, countSize);
        fread(buffer, 1U, sizeToSend, ptr);
        MFlash_puts(hComm, buffer, sizeToSend);
        countSize = countSize - sizeToSend;

        uint32_t PerTransferred = ((size - countSize) * 100.0 / size);
        if( PerTransferred > 10U)
        {
            printf("#");
            PerTransferred = 0U;
        }
    }
    return 1;
}


void MFlash_getString(MFlash_Descriptor hComm, char *str)
{
    uint8_t byteRead;
    do
    {
    	MFlash_gets(hComm, &byteRead, 1U);
    }while(byteRead != 'M');

    *str = byteRead;
    str++;
    do
    {
        MFlash_gets(hComm, &byteRead, 1U);
        *str = byteRead;
        str++;
    }while(byteRead != '\n');
        *str = 0;
}

/**
 * \brief  Print Uasge in case of an error
 */
void MFlash_writeUsage()
{
	printf("Usage: mflash -M <sbl_mflash> -P <Port Number> ");
	printf("-C [optional: to clean the QSPI Flash]");
	printf("-F <fileName> <offset> ");
	printf("-F <fileName> <offset> ... ");
}

int main(int argc, char **argv)
{
    uint8_t i;
    uint8_t numFiles = 0U;
    uint8_t cleanQspiFlag = 0U;
    uint8_t count;
    uint8_t byteRead;
    uint8_t StopByte = 4;
    uint8_t stopByteFlag;

    /*Default BOARD is TDA3XXevm*/
    uint8_t BOARD = TDA3XXevm;

    uint32_t asicRequest = ASIC_REQ;
    uint32_t peripherialBootRequest = PERI_REQ;
    uint32_t sblMflashSize;

    char sblMflashFile[100];
    char sblMflashHndShk[100];
    char file[3][100];
    char offset[3][15];
    char com[50] = MFLASH_PORT_PREFIX;
    char wait;

    MFlash_Descriptor hComm;

    MFlash_Word noBytesRead;

    time_t begin;
    time_t end;

    i = 0U;
    while(i < argc)
    {
    	if(strcmp(argv[i], "-M") == 0U)
    	{
            i++;
    		strcpy(sblMflashFile, argv[i]);
    	}
    	else if(strcmp(argv[i], "-P") == 0U)
    	{
            i++;
    		strcat(com, argv[i]);
    	}
        else if(strcmp(argv[i], "-S") == 0U)
        {
            i++;
            if (strcmp(argv[i], "tda3xxevm") == 0U)
            {
                BOARD = TDA3XXevm;
            }
            else if (strcmp(argv[i], "tda2pxevm") == 0U)
            {
                BOARD = TDA2PXevm;
            }
            else if (strcmp(argv[i], "tda2xxevm") == 0U)
            {
                BOARD = TDA2XXevm;
            }
            else if (strcmp(argv[i], "tda3xxrvp") == 0U)
            {
                BOARD = TDA3XXrvp;
            }
            else if (strcmp(argv[i], "tda2exevm") == 0U)
            {
                BOARD = TDA2EXevm;
            }
            else
            {
                printf("Invalid BOARD type. Exiting\n");
                exit(0);
            }
        }
    	else if(strcmp(argv[i], "-F") == 0U)
    	{
            i++;
    		strcpy(file[numFiles], argv[i]);
            i++;
    		strcpy(offset[numFiles], argv[i]);
            numFiles++;
    	}
    	else if(strcmp(argv[i], "-C") == 0U)
    	{
    		cleanQspiFlag = 1U;
    	}
    	else
    	{
            MFlash_writeUsage();
    		;
    	}
    	i++;
    }

    if(numFiles == 0U)
    {
    	printf("[PC] ERROR: Insufficient Parameters. No file specified\n");
    	MFlash_writeUsage();
    	return 0U;
    }

    printf("[PC] sbl_mflash %s\n", sblMflashFile);

    for(i = 0U; i < numFiles; i++)
    {
        printf("[PC] File\t%d\t%s\n", i, file[i]);
        printf("[PC] Offset\t%d\t%s\n", i, offset[i]);
    }
    printf("[PC] com %s\n", com);

    printf("[PC] ##########Starting USB/UART Flasing Utility##############\n");
    if(BOARD != TDA3XXrvp)
    {
        printf("[PC] Put UART Boot Mode, make fresh UART connection & restart\n");
    }
    else
    {
        printf("[PC] Make fresh UART connection & power off the board\n\n");
        fflush(stdout);
    }
    printf("[PC] Press Enter when done...");

    scanf("%c", &wait);

    hComm = MFlash_startPort(com, EVENPARITY, BAUD_RATE_115200);
    if (hComm < 0)
    {
        printf("[PC] Error in opening serial port\n");
        return 0;
    }
    else
    {
        printf("[PC] Opening serial port successful.\n");
        if(BOARD == TDA3XXrvp)
        {
            printf("[PC] Switch ON the board now.\n");
        }
    	fflush(stdout);
    }

    MFlash_getASICId(hComm);
    printf("\n[PC] Requesting the ASIC ID\n");
    MFlash_puts(hComm, (uint8_t *)(&asicRequest), 4U);
    MFlash_getASICId(hComm);

    printf("\n[PC] Requesting PERI_REQ mode");
    MFlash_puts(hComm, (uint8_t *)(&peripherialBootRequest), 4U);

    printf("\n[PC] Sending SBL_MFLASH filesize.");
    sblMflashSize = MFlash_getFileSize(sblMflashFile);
    printf("\n[PC] Size of sbl_mflash = %d", sblMflashSize );
    MFlash_puts(hComm, (uint8_t *)(&sblMflashSize), 4U);

    printf("\n[PC] Sending SBL_MFLASH... Please wait");
    begin = time(NULL);
    MFlash_putSblMflash(hComm, sblMflashFile, sblMflashSize);
    end = time(NULL);

    printf("\n[PC] Transfer Complete. Time = %.3f", (double)(end - begin));

    MFlash_putDelay(2000U);
    MFlash_stopPort(hComm);

    ////////////////////////////SBL' Execution Starts //////////////////////
    printf("\n[PC] Opening port for sbl_mflash.");
    if (BOARD == TDA3XXevm)
    {
        hComm = MFlash_startPort2(com, NOPARITY, BAUD_RATE_12000000);
    }
    else if( BOARD == TDA2PXevm || BOARD == TDA2EXevm || BOARD == TDA3XXrvp || BOARD == TDA2XXevm)
    {
        hComm = MFlash_startPort2(com, NOPARITY, BAUD_RATE_921600);
    }
    else
    {
        ;
    }

    if(hComm < 0)
    {
        printf("\n[PC] Error in opening serial port.");
        return 0U;
    }
    else
    {
        printf("\n[PC] Opening serial port successful.");
    }

    count = 1U;
    stopByteFlag = 1U;
    do
    {
        MFlash_getString(hComm, sblMflashHndShk);
    	if(strcmp(sblMflashHndShk, SBL_MFLASH_CMD_HNDSKE_STEP1) == 0)
    	{
                uint8_t choice[2];
                choice[0] = '1';
                MFlash_puts(hComm, choice, 1U);
                stopByteFlag = 0U;
    	}
    }while(stopByteFlag != 0U);

    stopByteFlag = 1U;
    do
    {
        noBytesRead = MFlash_gets(hComm, &byteRead, 1U);
        if(byteRead == 'r')
        {
                stopByteFlag = 0U;
        }
    }while(stopByteFlag != 0U);

    printf("\n[PC] sbl_mflash switch On Request Sent.");
    fflush(stdout);

    stopByteFlag = 1U;
    while(stopByteFlag != 0U)
    {
        noBytesRead = MFlash_gets(hComm, &byteRead, 1U);
        if(noBytesRead != 0U)
        {
            switch(byteRead)
            {
                case '\v':
                    //UART is expecting a single character byte
                    if(cleanQspiFlag == 1U)
                    {
                        MFlash_putChar(hComm, 0U);
                        cleanQspiFlag = 0U;
                    }
                    else if(numFiles <= 0U)
                    {
                        MFlash_putChar(hComm, 10U);
                    }
                    else
                    {
                        MFlash_putChar(hComm, count);
                        count++;
                    }
                    break;
                case '\t':
                    /*UART is expecting a filesize in Decimal*/
                    MFlash_putFileSize(hComm, file[numFiles - 1U]);
                    break;
                case '\'':
                    /*UART is expecting a binary file*/
                    MFlash_putFile(hComm, file[numFiles - 1U]);
                    numFiles--;
                    break;
                case '\?':
                    /*UART is expecting some hex value*/
                    MFlash_putHex(hComm, offset[numFiles - 1U]);
                    break;
                case 4:
                    /*UART tell the code to stop the execution*/
                    stopByteFlag = 0U;
                    break;
                default:
                    /*Display the character recieved just as it is*/
                    printf("%c", byteRead);
                    fflush(stdout);
            }
        }
    }
    MFlash_stopPort(hComm);
    printf("\n[PC] ##############!!!!mflash shutting down!!!!#############");
    return 0;
}
