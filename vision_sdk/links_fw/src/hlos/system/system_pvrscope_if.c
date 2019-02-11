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


/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <links_fw/src/hlos/osa/include/osa_mem.h>
#include <stdio.h>
#include <stdlib.h>
#include "system_pvrscope_if.h"

#ifdef BUILD_INFOADAS
#define PVRSCOPE_FIFO_DIR "/opt/infoadas"
#else
#define PVRSCOPE_FIFO_DIR "/opt/vision_sdk"
#endif

/**
 *******************************************************************************
 *
 * \brief To support SGX profiling. Create the Linux stack FIFO to read
 *        the GPU load dumped by pvr scope utility
 *
 *******************************************************************************
 */
void system_create_pvrscope_profile_data(System_PvrScope_Obj *pvrscope_obj)
{
   pvrscope_obj->fd = 0;
   pvrscope_obj->gpufifo = (char *) PVRSCOPE_FIFO_DIR "/gpufifo";
   mkfifo(pvrscope_obj->gpufifo, 0666);
   Vps_printf(" SYSTEM_PVRSCOPE: FIFO %s opened successfully \n",
                pvrscope_obj->gpufifo);

   pvrscope_obj->fd = open(pvrscope_obj->gpufifo, O_RDONLY|O_NONBLOCK);
   if (pvrscope_obj->fd==-1)
   {
       Vps_printf (" SYSTEM_PVRSCOPE: FIFO open failed \n");
       exit(-1);
   }
}

/**
 *******************************************************************************
 *
 * \brief To support SGX profiling. Close the Linux stack FIFO
 *
 *******************************************************************************
 */
void system_delete_pvrscope_profile_data(System_PvrScope_Obj *pvrscope_obj)
{
   close(pvrscope_obj->fd);
}

/**
 *******************************************************************************
 *
 * \brief To support SGX profiling. Get the SGX load from the Linux stack FIFO,
 *        in to which the the GPU load is dumped by pvr scope utility
 *
 *******************************************************************************
 */
void system_get_pvrscope_profile_data(System_PvrScope_Obj *pvrscope_obj)
{
   char buf[MAX_BUF];
   int bytes;

   bytes = read(pvrscope_obj->fd, buf, MAX_BUF);
   if (bytes>0)
   {
       char str[100];
       sscanf(buf, "%s %f %f", str, &pvrscope_obj->fragShLoad, &pvrscope_obj->vertShLoad);
       if(strcmp(str, "PVR:") == 0)
       {
           if (pvrscope_obj->fragShLoad >= pvrscope_obj->vertShLoad)
           {
               pvrscope_obj->maxShLoad = pvrscope_obj->fragShLoad;
           }
           else
           {
               pvrscope_obj->maxShLoad = pvrscope_obj->vertShLoad;
           }
           
           pvrscope_obj->loadStats.totalLoadParams.integerValue =
               (uint32_t) pvrscope_obj->maxShLoad;
           pvrscope_obj->loadStats.totalLoadParams.fractionalValue =
               (uint32_t) ((pvrscope_obj->maxShLoad -
                    pvrscope_obj->loadStats.totalLoadParams.integerValue) * 10);
#if 1  /* Enable to print on the console */
           Vps_printf(" SYSTEM_PVRSCOPE: Load of Fragment shader %f\n",
               pvrscope_obj->fragShLoad);
           Vps_printf(" SYSTEM_PVRSCOPE: Load of Vertex shader %f\n",
               pvrscope_obj->vertShLoad);
#endif
       }
       else
       {
           Vps_printf(" SYSTEM_PVRSCOPE: Received unexpected data from FIFO - \" %s \" \n", buf);
       }
       memset(buf, 0x0, sizeof(buf));
   }
   else
   {
      /* Do nothing */
   }
}

/* Nothing beyond this point */

