/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/



/**
    \file exif.c
    \brief EXIF 2.2 Creator/Parser APIs
*/

#include <util.h>

#define MAX_BUFFER_SIZE (1*KB*KB)

Uint8 buffer[MAX_BUFFER_SIZE];

STATUS bin2c( Uint8 *inName) {
  STATUS status=E_PASS;
	Uint32 bytes=1, size, i, csize;
	FILE* fin;
  Uint32  chunkSize = MAX_BUFFER_SIZE;

  fprintf(stderr, "\r\n Converting binary file [%s] to C array ", inName );

	fin = fopen( inName, "rb");
	if(fin==NULL) {
    fprintf(stderr, "\r\n ERROR: Input file [%s] not found", inName);
    status = E_DEVICE;
    goto error_stop;
  }

	size=0;
  csize=0;
	while(bytes) {
		bytes = fread(buffer, 1, chunkSize, fin );
    fprintf(stderr, ".");
    for(i=0;i<bytes;i++) {
      if(i%(3*30)==0)
        printf("\n");
        printf("0x%02x,", buffer[i]);
        csize++;
    }
		size +=bytes;
	}
  printf("\n // %ld bytes", csize );
  printf("\n");
  fprintf(stderr, " Done. (%ld bytes)", size);

  if(csize!=size) {
    fprintf(stderr, "\n ERROR: Check output file (byte diff %ld)", size-csize);
  }
error_stop:
	fclose(fin);

	return status;
}

void main(int argc, char **argv) {

  if(argc!=2) {
    printf("\r\n USAGE: bin2c <binary file name> \n" );
    exit(0);
  }

  bin2c(argv[1]);
}