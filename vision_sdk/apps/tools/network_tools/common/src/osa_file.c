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


#include <osa_file.h>

#define OSA_DEBUG_FILE

int OSA_fileReadFile(char *fileName, Uint8 *addr, Uint32 readSize, Uint32 *actualReadSize)
{
  int retVal = OSA_SOK;
  Uint8  *curAddr;

  Uint32 readDataSize, fileSize, chunkSize=1024*100;
	Uint32 userReadSize;

  FILE *hndlFile;

  #ifdef OSA_DEBUG_FILE
  printf("# FILE: Reading file [%s] ... ", fileName);
  #endif

  hndlFile = fopen(fileName, "rb");

  if(hndlFile == NULL) {
  	retVal = OSA_EFAIL;
    goto exit;
	}

  curAddr = addr;
  fileSize = 0;

	userReadSize = readSize;

  while(1) {
		if(userReadSize != 0) {
			if(chunkSize > userReadSize)
				chunkSize = userReadSize;
			readDataSize = fread(curAddr, 1, chunkSize, hndlFile);
			fileSize += readDataSize;
			if(chunkSize != readDataSize)
				break;
			if(userReadSize==fileSize)
				break;
			curAddr += chunkSize;
		}
		else {
			readDataSize = fread(curAddr, 1, chunkSize, hndlFile);
      fileSize+=readDataSize;
      if(chunkSize!=readDataSize)
        break;
      curAddr+=chunkSize;
    }
	}
  #ifdef OSA_DEBUG_FILE
  printf("Done. [%d bytes] \r\n", fileSize);
  #endif
  fclose(hndlFile);

exit:
  if(retVal!=OSA_SOK) {
    #ifdef OSA_DEBUG_FILE
    printf("# FILE: ERROR \r\n");
    #endif
    fileSize=0;
  }
	if(actualReadSize != NULL)
    *actualReadSize = fileSize;

  return retVal;
}

int OSA_fileWriteFile(char *fileName, Uint8 *addr, Uint32 size)
{
  int retVal = OSA_SOK;
  Uint32 writeDataSize;
  FILE *hndlFile;

	if(size==0)
		return OSA_SOK;

  #ifdef OSA_DEBUG_FILE
  printf("# FILE: Writing to file [%s] (%d bytes) ... ", fileName, size);
  #endif
  hndlFile = fopen(fileName, "wb");

  if(hndlFile == NULL) {
  	retVal = OSA_EFAIL;
    goto exit;
	}

  {
    // write in units of chunkSize
    Int32 fileSize, chunkSize = 96*1024;
    Int8  *curAddr;


    fileSize = size;
    curAddr  = (Int8*)addr;
    while(fileSize>0) {
      if(fileSize<chunkSize) {
        chunkSize = fileSize;
      }
      writeDataSize=0;
      writeDataSize = fwrite(curAddr, 1, chunkSize, hndlFile);
      if(writeDataSize!=chunkSize) {
        // error in writing, abort
        retVal = OSA_EFAIL;
        break;
      }
      curAddr += chunkSize;
      fileSize -= chunkSize;
    }
    writeDataSize = size - fileSize;
  }

  #ifdef OSA_DEBUG_FILE
  printf("Done. [%d bytes] \r\n", writeDataSize);
  #endif
  fflush(hndlFile);

  fclose(hndlFile);

exit:
  if(retVal!=OSA_SOK) {
    #ifdef OSA_DEBUG_FILE
    printf("# FILE: ERROR \r\n");
    #endif
  }
  return retVal;

}

