/*
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
*/

#include <osa.h>
#include <osa_dma.h>
#include <dev_memcache.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>


typedef struct {

  int fd;
  Bool isInitDone;

} OSA_DmaCtrl;

OSA_DmaCtrl gOSA_dmaCtrl = { -1, FALSE };

int OSA_dmaInit(void)
{
  char deviceName[20];

  if(!gOSA_dmaCtrl.isInitDone) {

    snprintf(deviceName, sizeof(deviceName), "/dev/%s", DMA_DRV_NAME);

    gOSA_dmaCtrl.fd = open(deviceName, O_RDWR);
    if(gOSA_dmaCtrl.fd<0)
      return OSA_EFAIL;

    gOSA_dmaCtrl.isInitDone = TRUE;
  }

  return OSA_SOK;
}

int OSA_dmaExit(void)
{
  gOSA_dmaCtrl.isInitDone = FALSE;
  return close(gOSA_dmaCtrl.fd);
}

Uint8 *OSA_dmaMapMem(Uint8 *physAddr, Uint32 size, Uint32 mapType)
{
    DMA_MmapPrm prm;
    Uint32 cmd;

    prm.physAddr = (unsigned int)physAddr;
    prm.size     = size;
    prm.mapType  = mapType;
    prm.virtAddr = 0;

    cmd = DMA_IOCTL_CMD_MAKE(DMA_CMD_MMAP);
    ioctl(gOSA_dmaCtrl.fd, cmd, &prm);

    if (prm.virtAddr==0)
    {
        OSA_ERROR(" OSA_dmaMapMem() failed !!!\n");
        return NULL;
    }

#ifdef ANDROID
    prm.virtAddr = (UInt32)mmap64(
#else
    prm.virtAddr = (UInt32)mmap(
#endif
                (void *)physAddr,
                size,
                PROT_READ|PROT_WRITE|PROT_EXEC,MAP_SHARED,
                gOSA_dmaCtrl.fd,
                (unsigned int)physAddr
            );

    return (Uint8*)prm.virtAddr;
}

int OSA_dmaUnmapMem(Uint8 *virtAddr, Uint32 size)
{
  if(virtAddr)
    munmap((void*)virtAddr, size);

  return 0;
}

