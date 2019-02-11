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


#ifndef _IMAGE_CONVERT_H_
#define _IMAGE_CONVERT_H_

#include <osa.h>


#define IMAGE_CONVERT_VERSION_STRING  "0.90"

#define IMAGE_CONVERT_BUFFER_SIZE_MAX   (12*MB)


typedef enum {

  IMAGE_FORMAT_YUYV422,
  IMAGE_FORMAT_YVYU422,
  IMAGE_FORMAT_UYVY422, // DM355/DM365 YUV422 format
  IMAGE_FORMAT_VYUY422,
  IMAGE_FORMAT_YYUV422, // DM6467 YUV422 format
  IMAGE_FORMAT_YYVU422,
  IMAGE_FORMAT_YUV422p,
  IMAGE_FORMAT_YYUV420, // DM365 YUV420 format
  IMAGE_FORMAT_YYVU420,
  IMAGE_FORMAT_YUV420p,
  IMAGE_FORMAT_YUV444i,
  IMAGE_FORMAT_YUV444p,
  IMAGE_FORMAT_RGB565,  // graphics format
  IMAGE_FORMAT_RGB888i, // graphics format
  IMAGE_FORMAT_RGB888p, // graphics format
  IMAGE_FORMAT_ARGB888i,// graphics format
  IMAGE_FORMAT_BMP,     // NOT SUPPORTED as of NOW

  IMAGE_FORMAT_MAX

} IMAGE_Format;

typedef struct {

  char inFileName[256];

  Uint32 inWidth;
  Uint32 inHeight;
  Uint32 inLineOffset;

  IMAGE_Format inFormat;

  char outFileName[256];

  Uint32 outLineOffset;
  IMAGE_Format outFormat;

  Uint8 *inBuffer;
  Uint8 *outBuffer;

} IMAGE_CONVERT_Ctrl;

extern IMAGE_CONVERT_Ctrl gIMAGE_CONVERT_ctrl;

void showUsage(void);

int IMAGE_CONVERT_rgb2yuv(Uint32 r, Uint32 g, Uint32 b, Uint32 *yInt, Uint32 *uInt, Uint32 *vInt);
int IMAGE_CONVERT_yuv2rgb(Int32 y, Int32 u, Int32 v, Uint32 *rInt, Uint32 *gInt, Uint32 *bInt);
int IMAGE_CONVERT_rgb565yuv444(Uint16 rgb, Uint32 *yInt, Uint32 *uInt, Uint32 *vInt);
int IMAGE_CONVERT_yuv444rgb565(Int32 y, Int32 u, Int32 v, Uint16 *rgb565);

Uint32       IMAGE_CONVERT_GetImageSizeInBytes(IMAGE_Format format, Uint16 lineOffset, Uint16 height);
Uint16       IMAGE_CONVERT_GetBytesPerPixelInLine(IMAGE_Format format);
IMAGE_Format IMAGE_CONVERT_GetFormat(char *formatStr);

int IMAGE_CONVERT_init(void);
int IMAGE_CONVERT_run(void);
int IMAGE_CONVERT_exit(void);

int parseCmdLineArgs(int argc, char **argv);

#endif /* _IMAGE_CONVERT_H_ */


