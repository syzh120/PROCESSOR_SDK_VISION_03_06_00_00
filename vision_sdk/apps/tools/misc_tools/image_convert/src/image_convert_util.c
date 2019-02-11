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


#include <image_convert.h>

int IMAGE_CONVERT_rgb2yuv(Uint32 r, Uint32 g, Uint32 b, Uint32 *yInt, Uint32 *uInt, Uint32 *vInt)
{
  float y, u, v;

  y = 0.299*r + 0.587*g + 0.114*b;
  u = 0.492*(b-y) + 128;
  v = 0.877*(r-y) + 128;

  if(v>255)
    v = 255;
  if(v<0)
    v = 0;

  if(u>255)
    u = 255;
  if(u<0)
    u = 0;

  if(y>255)
    y = 255;
  if(y<0)
    y = 0;

  *yInt = y;
  *uInt = u;
  *vInt = v;

  return OSA_SOK;
}

int IMAGE_CONVERT_yuv2rgb(Int32 y, Int32 u, Int32 v, Uint32 *rInt, Uint32 *gInt, Uint32 *bInt)
{
  float r, g, b;

  r = 1.164*(y - 16) + 1.596 * (v - 128);
  g = 1.164*(y - 16) - 0.813 * (v - 128) - 0.391*(u - 128);
  b = 1.164*(y - 16) + 2.018 * (u - 128);

  if(r>255)
    r=255;
  if(r<0)
    r=0;

  if(g>255)
    g=255;
  if(g<0)
    g=0;

  if(b>255)
    b=255;
  if(b<0)
    b=0;

  *rInt = (Uint32)r;
  *gInt = (Uint32)g;
  *bInt = (Uint32)b;

  return OSA_SOK;
}

int IMAGE_CONVERT_rgb565yuv444(Uint16 rgb, Uint32 *yInt, Uint32 *uInt, Uint32 *vInt)
{
  Uint32 r, g, b;

  r  = (rgb & 0xF800) >> (11-3);
  g  = (rgb & 0x07E0) >> (5-2);
  b  = (rgb & 0x001F) << (3);

  return IMAGE_CONVERT_rgb2yuv(r, g, b, yInt, uInt, vInt);
}

int IMAGE_CONVERT_yuv444rgb565(Int32 y, Int32 u, Int32 v, Uint16 *rgb565)
{
  Uint32 r, g, b;

  IMAGE_CONVERT_yuv2rgb(y, u, v, &r, &g, &b);

  r = r >> 3;
  g = g >> 2;
  b = b >> 3;

  *rgb565 = ( r << 11) + (g << 5) + b;

  return OSA_SOK;
}

Uint32 IMAGE_CONVERT_GetImageSizeInBytes(IMAGE_Format format, Uint16 lineOffset, Uint16 height)
{
  switch(format) {
    case IMAGE_FORMAT_YUYV422:
    case IMAGE_FORMAT_YVYU422:
    case IMAGE_FORMAT_UYVY422:
    case IMAGE_FORMAT_VYUY422:
    case IMAGE_FORMAT_YYUV422:
    case IMAGE_FORMAT_YYVU422:
    case IMAGE_FORMAT_YUV422p:
    case IMAGE_FORMAT_RGB565:
      return lineOffset*height*2;

    case IMAGE_FORMAT_YYUV420:
    case IMAGE_FORMAT_YYVU420:
    case IMAGE_FORMAT_YUV420p:
      return (lineOffset*height*3)/2;

    case IMAGE_FORMAT_RGB888i:
    case IMAGE_FORMAT_RGB888p:
    case IMAGE_FORMAT_YUV444i:
    case IMAGE_FORMAT_YUV444p:
    case IMAGE_FORMAT_BMP:
      return (lineOffset*height*3);

    case IMAGE_FORMAT_ARGB888i:
        return (lineOffset*height*4);
  }

  return 0;
}


Uint16 IMAGE_CONVERT_GetBytesPerPixelInLine(IMAGE_Format format)
{
  switch(format) {
    case IMAGE_FORMAT_YUYV422:
    case IMAGE_FORMAT_YVYU422:
    case IMAGE_FORMAT_UYVY422:
    case IMAGE_FORMAT_VYUY422:
    case IMAGE_FORMAT_RGB565:
      return 2;

    case IMAGE_FORMAT_YYUV422:
    case IMAGE_FORMAT_YYVU422:
    case IMAGE_FORMAT_YUV422p:
    case IMAGE_FORMAT_YYUV420:
    case IMAGE_FORMAT_YYVU420:
    case IMAGE_FORMAT_YUV420p:
    case IMAGE_FORMAT_YUV444p:
    case IMAGE_FORMAT_RGB888p:
      return 1;

    case IMAGE_FORMAT_RGB888i:
    case IMAGE_FORMAT_YUV444i:
    case IMAGE_FORMAT_BMP:
      return 3;

    case IMAGE_FORMAT_ARGB888i:
      return 4;
  }

  return 0;
}

IMAGE_Format IMAGE_CONVERT_GetFormat(char *formatStr)
{
  if(strcmp(formatStr, "yuyv422")==0)
    return IMAGE_FORMAT_YUYV422;

  if(strcmp(formatStr, "yvyu422")==0)
    return IMAGE_FORMAT_YVYU422;

  if(strcmp(formatStr, "uyvy422")==0)
    return IMAGE_FORMAT_UYVY422;

  if(strcmp(formatStr, "vyuy422")==0)
    return IMAGE_FORMAT_VYUY422;

  if(strcmp(formatStr, "yyuv422")==0)
    return IMAGE_FORMAT_YYUV422;

  if(strcmp(formatStr, "yyvu422")==0)
    return IMAGE_FORMAT_YYVU422;

  if(strcmp(formatStr, "yuv422p")==0)
    return IMAGE_FORMAT_YUV422p;

  if(strcmp(formatStr, "yyuv420")==0)
    return IMAGE_FORMAT_YYUV420;

  if(strcmp(formatStr, "yyvu420")==0)
    return IMAGE_FORMAT_YYVU420;

  if(strcmp(formatStr, "yuv420p")==0)
    return IMAGE_FORMAT_YUV420p;

  if(strcmp(formatStr, "yuv444i")==0)
    return IMAGE_FORMAT_YUV444i;

  if(strcmp(formatStr, "yuv444p")==0)
    return IMAGE_FORMAT_YUV444p;

  if(strcmp(formatStr, "rgb565")==0)
    return IMAGE_FORMAT_RGB565;

  if(strcmp(formatStr, "rgb888i")==0)
    return IMAGE_FORMAT_RGB888i;

  if(strcmp(formatStr, "argb888i")==0)
    return IMAGE_FORMAT_ARGB888i;

  if(strcmp(formatStr, "rgb888p")==0)
    return IMAGE_FORMAT_RGB888p;

  #if 0
  if(strcmp(formatStr, "bmp")==0)
    return IMAGE_FORMAT_BMP;
  #endif

  return IMAGE_FORMAT_MAX;
}

