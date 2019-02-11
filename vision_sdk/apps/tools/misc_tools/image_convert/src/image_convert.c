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

IMAGE_CONVERT_Ctrl gIMAGE_CONVERT_ctrl;

int IMAGE_CONVERT_run(void)
{
  Uint32 outSize;
  Uint32 i, j;
  Uint32 y, u, v, r, g, b;
  Uint8 *curInLine, *curOutLine, *curInLineC, *curOutLineC;
  Uint32 inBytesPerPixelInLine, outBytesPerPixelInLine, inOffsetV, outOffsetV;
  Uint16 rgb565;

  inBytesPerPixelInLine  = IMAGE_CONVERT_GetBytesPerPixelInLine(gIMAGE_CONVERT_ctrl.inFormat);
  outBytesPerPixelInLine = IMAGE_CONVERT_GetBytesPerPixelInLine(gIMAGE_CONVERT_ctrl.outFormat);

  inOffsetV = gIMAGE_CONVERT_ctrl.inLineOffset*gIMAGE_CONVERT_ctrl.inHeight;
  outOffsetV = gIMAGE_CONVERT_ctrl.outLineOffset*gIMAGE_CONVERT_ctrl.inHeight;

  curInLineC = gIMAGE_CONVERT_ctrl.inBuffer + inOffsetV;
  curOutLineC = gIMAGE_CONVERT_ctrl.outBuffer + outOffsetV;

  for(j=0; j<gIMAGE_CONVERT_ctrl.inHeight; j++) {

    curInLine  = gIMAGE_CONVERT_ctrl.inBuffer  + j*gIMAGE_CONVERT_ctrl.inLineOffset*inBytesPerPixelInLine;
    curOutLine = gIMAGE_CONVERT_ctrl.outBuffer + j*gIMAGE_CONVERT_ctrl.outLineOffset*outBytesPerPixelInLine;

    for(i=0; i<gIMAGE_CONVERT_ctrl.inWidth; i++) {

      // get y, u, v for pixel i, j dpeending on input format

      switch(gIMAGE_CONVERT_ctrl.inFormat) {

        case IMAGE_FORMAT_YUYV422:
          y = curInLine[2*i];
          if(i%2==0) {
            u = curInLine[2*i+1];
            v = curInLine[2*i+1+2];
          } else {
            v = curInLine[2*i+1];
            u = curInLine[2*i+1-2];
          }
          break;

        case IMAGE_FORMAT_YVYU422:
          y = curInLine[2*i];
          if(i%2==0) {
            v = curInLine[2*i+1];
            u = curInLine[2*i+1+2];
          } else {
            u = curInLine[2*i+1];
            v = curInLine[2*i+1-2];
          }
          break;

        case IMAGE_FORMAT_UYVY422:
          y = curInLine[2*i+1];
          if(i%2==0) {
            u = curInLine[2*i];
            v = curInLine[2*i+2];
          } else {
            v = curInLine[2*i];
            u = curInLine[2*i-2];
          }
          break;

        case IMAGE_FORMAT_VYUY422:
          y = curInLine[2*i+1];
          if(i%2==0) {
            v = curInLine[2*i];
            u = curInLine[2*i+2];
          } else {
            u = curInLine[2*i];
            v = curInLine[2*i-2];
          }
          break;

        case IMAGE_FORMAT_YYUV422:
          y = curInLine[i];

          if(i%2==0) {
            u = curInLine[inOffsetV+i];
            v = curInLine[inOffsetV+i+1];
          } else {
            v = curInLine[inOffsetV+i];
            u = curInLine[inOffsetV+i-1];
          }
          break;

        case IMAGE_FORMAT_YYVU422:
          y = curInLine[i];

          if(i%2==0) {
            v = curInLine[inOffsetV+i];
            u = curInLine[inOffsetV+i+1];
          } else {
            u = curInLine[inOffsetV+i];
            v = curInLine[inOffsetV+i-1];
          }
          break;

        case IMAGE_FORMAT_YUV422p:
          y = curInLine[i];
          u = curInLineC[i/2 ];
          v = curInLineC[i/2 +inOffsetV/2];
          break;

        case IMAGE_FORMAT_YYUV420:
          y = curInLine[i];

          if(i%2==0) {
            u = curInLineC[i];
            v = curInLineC[i+1];
          } else {
            v = curInLineC[i];
            u = curInLineC[i-1];
          }

          break;

        case IMAGE_FORMAT_YYVU420:
          y = curInLine[i];

          if(i%2==0) {
            v = curInLineC[i];
            u = curInLineC[i+1];
          } else {
            u = curInLineC[i];
            v = curInLineC[i-1];
          }
          break;

        case IMAGE_FORMAT_YUV420p:
          y = curInLine[i];
          u = curInLineC[i/2];
          v = curInLineC[i/2+inOffsetV/4];

          break;
        case IMAGE_FORMAT_YUV444i:
          y = curInLine[3*i];
          u = curInLine[3*i+1];
          v = curInLine[3*i+2];
          break;
        case IMAGE_FORMAT_YUV444p:
          y = curInLine[i];
          u = curInLine[i+inOffsetV];
          v = curInLine[i+inOffsetV*2];
          break;

        case IMAGE_FORMAT_RGB888i:
          r = curInLine[3*i];
          g = curInLine[3*i+1];
          b = curInLine[3*i+2];

          IMAGE_CONVERT_rgb2yuv(r, g, b, &y, &u, &v);
          break;

        case IMAGE_FORMAT_ARGB888i:
          b = curInLine[4*i];
          g = curInLine[4*i+1];
          r = curInLine[4*i+2];

          IMAGE_CONVERT_rgb2yuv(r, g, b, &y, &u, &v);
          break;

        case IMAGE_FORMAT_RGB888p:
          b = curInLine[i];
          g = curInLine[i+inOffsetV];
          r = curInLine[i+inOffsetV*2];

          IMAGE_CONVERT_rgb2yuv(r, g, b, &y, &u, &v);
          break;

        case IMAGE_FORMAT_RGB565:
          rgb565 = *((Uint16*)curInLine+i);

          IMAGE_CONVERT_rgb565yuv444(rgb565, &y, &u, &v);
          break;
      }

      #if 0
      if(i==0 && j==0) {
        printf(" %x %x %x\n", y, u, v);
      }
      #endif


      // put y, u, v for pixel i, j depending on output format

      switch(gIMAGE_CONVERT_ctrl.outFormat) {

        case IMAGE_FORMAT_YUYV422:
          curOutLine[2*i] = y;

          if(i%2==0) {
            curOutLine[2*i+1] = u;
          } else {
            curOutLine[2*i+1] = v;
          }
          break;

        case IMAGE_FORMAT_YVYU422:
          curOutLine[2*i] = y;
          if(i%2==0) {
            curOutLine[2*i+1] = v;
          } else {
            curOutLine[2*i+1] = u;
          }
          break;

        case IMAGE_FORMAT_UYVY422:
          curOutLine[2*i+1] = y;
          if(i%2==0) {
            curOutLine[2*i] = u;
          } else {
            curOutLine[2*i] = v;
          }
          break;

        case IMAGE_FORMAT_VYUY422:
          curOutLine[2*i+1] = y;
          if(i%2==0) {
            curOutLine[2*i] = v;
          } else {
            curOutLine[2*i] = u;
          }
          break;

        case IMAGE_FORMAT_YYUV422:
          curOutLine[i] = y;

          if(i%2==0) {
            curOutLine[outOffsetV+i]=u;
          } else {
            curOutLine[outOffsetV+i]=v;
          }
          break;

        case IMAGE_FORMAT_YYVU422:
          curOutLine[i] = y;

          if(i%2==0) {
            curOutLine[outOffsetV+i]=v;
          } else {
            curOutLine[outOffsetV+i]=u;
          }
          break;

        case IMAGE_FORMAT_YUV422p:
          curOutLine[i] = y;

          if(i%2==0) {
            curOutLineC[i/2 ]=u;
            curOutLineC[i/2 + outOffsetV/2] = v;
          }
          break;

        case IMAGE_FORMAT_YYUV420:
          curOutLine[i] = y;

          if(i%2==0) {
            curOutLineC[i] = u;
          } else {
            curOutLineC[i] = v;
          }
          break;

        case IMAGE_FORMAT_YYVU420:
          curOutLine[i] = y;

          if(i%2==0) {
            curOutLineC[i] = v;
          } else {
            curOutLineC[i] = u;
          }
          break;

        case IMAGE_FORMAT_YUV420p:
          curOutLine[i] = y;

          if(i%2==0) {
            curOutLineC[i/2] = u;
            curOutLineC[i/2+inOffsetV/4]=v;
          }
          break;

        case IMAGE_FORMAT_YUV444i:
          curOutLine[3*i] = y;
          curOutLine[3*i+1] = u;
          curOutLine[3*i+2] = v;
          break;

        case IMAGE_FORMAT_YUV444p:
          curOutLine[i] = y;
          curOutLine[i+outOffsetV] = u;
          curOutLine[i+outOffsetV*2] = v;
          break;

        case IMAGE_FORMAT_RGB888i:

          IMAGE_CONVERT_yuv2rgb(y, u, v, &r, &g, &b);

          curOutLine[3*i] = b;
          curOutLine[3*i+1] = g;
          curOutLine[3*i+2] = r;

          break;

        case IMAGE_FORMAT_ARGB888i:

          IMAGE_CONVERT_yuv2rgb(y, u, v, &r, &g, &b);

          curOutLine[4*i] = b;
          curOutLine[4*i+1] = g;
          curOutLine[4*i+2] = r;
          curOutLine[4*i+3] = 0;

          break;

        case IMAGE_FORMAT_RGB888p:

          IMAGE_CONVERT_yuv2rgb(y, u, v, &r, &g, &b);

          curOutLine[i] = b;
          curOutLine[i+outOffsetV] = g;
          curOutLine[i+outOffsetV*2] = r;
          break;

        case IMAGE_FORMAT_RGB565:

          IMAGE_CONVERT_yuv444rgb565(y, u, v, &rgb565);
          *( (Uint16*)curOutLine + i ) = rgb565;
          break;
      }
    }

    if(   gIMAGE_CONVERT_ctrl.inFormat == IMAGE_FORMAT_YYVU420
       || gIMAGE_CONVERT_ctrl.inFormat == IMAGE_FORMAT_YYUV420
      ) {
      if(j%2!=0) {
        curInLineC += gIMAGE_CONVERT_ctrl.inLineOffset;
      }
    }

    if( gIMAGE_CONVERT_ctrl.inFormat == IMAGE_FORMAT_YUV422p )
    {
      curInLineC += gIMAGE_CONVERT_ctrl.inLineOffset/2;
    }

    if( gIMAGE_CONVERT_ctrl.inFormat == IMAGE_FORMAT_YUV420p )
    {
      if(j%2!=0) {
        curInLineC += gIMAGE_CONVERT_ctrl.inLineOffset/2;
      }
    }

    if(   gIMAGE_CONVERT_ctrl.outFormat == IMAGE_FORMAT_YYVU420
       || gIMAGE_CONVERT_ctrl.outFormat == IMAGE_FORMAT_YYUV420
      ) {
      if(j%2!=0) {
        curOutLineC += gIMAGE_CONVERT_ctrl.outLineOffset;
      }
    }

    if( gIMAGE_CONVERT_ctrl.outFormat == IMAGE_FORMAT_YUV422p )
    {
      curOutLineC += gIMAGE_CONVERT_ctrl.outLineOffset/2;
    }

    if( gIMAGE_CONVERT_ctrl.outFormat == IMAGE_FORMAT_YUV420p )
    {
      if(j%2!=0) {
        curOutLineC += gIMAGE_CONVERT_ctrl.outLineOffset/2;
      }
    }

  }

  outSize = IMAGE_CONVERT_GetImageSizeInBytes(gIMAGE_CONVERT_ctrl.outFormat, gIMAGE_CONVERT_ctrl.outLineOffset, gIMAGE_CONVERT_ctrl.inHeight);

  OSA_fileWriteFile(gIMAGE_CONVERT_ctrl.outFileName, gIMAGE_CONVERT_ctrl.outBuffer, outSize);

  return OSA_SOK;
}

int main(int argc, char **argv)
{
  int status;

  if(argc < 2 ) {
    showUsage();
    return 0;
  }

  status = IMAGE_CONVERT_init();
  if(status != OSA_SOK) {
    return status;
  }

  status = parseCmdLineArgs(argc, argv );
  if(status != OSA_SOK) {
    goto error_exit;
  }

  IMAGE_CONVERT_run();

error_exit:
  IMAGE_CONVERT_exit();

  return 0;
}

int IMAGE_CONVERT_init(void)
{
  memset(&gIMAGE_CONVERT_ctrl, 0, sizeof(gIMAGE_CONVERT_ctrl));

  gIMAGE_CONVERT_ctrl.inFormat = IMAGE_FORMAT_MAX;
  gIMAGE_CONVERT_ctrl.outFormat = IMAGE_FORMAT_MAX;


  gIMAGE_CONVERT_ctrl.inBuffer = malloc(IMAGE_CONVERT_BUFFER_SIZE_MAX);
  gIMAGE_CONVERT_ctrl.outBuffer = malloc(IMAGE_CONVERT_BUFFER_SIZE_MAX);

  if(  gIMAGE_CONVERT_ctrl.inBuffer == NULL
    || gIMAGE_CONVERT_ctrl.outBuffer == NULL
    ) {
    printf(" ERROR: Insufficient memory in system");
    return OSA_EFAIL;
  }

  return OSA_SOK;
}

int IMAGE_CONVERT_exit(void)
{
  free(gIMAGE_CONVERT_ctrl.inBuffer);
  free(gIMAGE_CONVERT_ctrl.outBuffer);

  return OSA_SOK;
}

void showUsage(void)
{
  printf( "\n"
          " Image Format Convertor -- (c) Texas Instruments 2008 \n"
          "\n"
          " Build Version  : %s \n"
          " Build Date/Time: " __DATE__ " " __TIME__ "\n"
          "\n"
          " image_convert \n"
          "   -i <in file>  <in format>  <in width> <in height> <in line offset> \n"
          "   -o <out file> <out format> <out line offset> \n"
          "\n"
          " Supported input/output formats,\n"
          " YUV422 formats : yuyv422 yvyu422 uyvy422 vyuy422 yyuv422 yyvu422 yuv422p \n"
          " YUV420 formats : yyuv420 yyvu420 yuv420p \n"
          " YUV444 formats : yuv444i yuv444p \n"
          " RGB    formats : rgb565 rgb888i rgb888p\n"
          "\n"
          " Note, \n"
          " - uyvy422 is DM355/DM365 YUV422 format used for capture/display \n"
          " - yyuv420 is DM365 YUV420 format used for capture/display \n"
          " - yyuv422 is DM6467 format used for capture/display \n"
          "\n",
          IMAGE_CONVERT_VERSION_STRING
        );

}

int parseCmdLineArgs(int argc, char **argv)
{
  int i, status = OSA_SOK;
  Uint32 readSize;

  for(i=0; i<argc; i++) {

    if(strcmp(argv[i], "-h")==0) {
      showUsage();
      exit(0);
    }

    if(strcmp(argv[i], "-i")==0) {
      i++;
      if(i>=argc)
        break;

      strcpy(gIMAGE_CONVERT_ctrl.inFileName, argv[i]);
      i++;
      if(i>=argc)
        break;

      gIMAGE_CONVERT_ctrl.inFormat = IMAGE_CONVERT_GetFormat(argv[i]);
      i++;
      if(i>=argc)
        break;

      gIMAGE_CONVERT_ctrl.inWidth = atoi(argv[i]);
      i++;
      if(i>=argc)
        break;

      gIMAGE_CONVERT_ctrl.inHeight = atoi(argv[i]);
      i++;
      if(i>=argc)
        break;

      gIMAGE_CONVERT_ctrl.inLineOffset = atoi(argv[i]);
      i++;
      if(i>=argc)
        break;

    }
    if(strcmp(argv[i], "-o")==0) {
      i++;
      if(i>=argc)
        break;

      strcpy(gIMAGE_CONVERT_ctrl.outFileName, argv[i]);
      i++;
      if(i>=argc)
        break;

      gIMAGE_CONVERT_ctrl.outFormat = IMAGE_CONVERT_GetFormat(argv[i]);
      i++;
      if(i>=argc)
        break;

      gIMAGE_CONVERT_ctrl.outLineOffset = atoi(argv[i]);
      i++;
      if(i>=argc)
        break;

    }
  }

  if(gIMAGE_CONVERT_ctrl.inFileName[0]==0) {
    status = OSA_EFAIL;
    printf(" ERROR: Input file not specified \n");
  }

  if(gIMAGE_CONVERT_ctrl.inFormat >= IMAGE_FORMAT_MAX ) {
    status = OSA_EFAIL;
    printf(" ERROR: Input format is invalid \n");
  }

  if(gIMAGE_CONVERT_ctrl.inFormat != IMAGE_FORMAT_BMP) {
    if(  gIMAGE_CONVERT_ctrl.inWidth == 0
      || gIMAGE_CONVERT_ctrl.inHeight == 0
      || gIMAGE_CONVERT_ctrl.inLineOffset == 0
      ) {

      status = OSA_EFAIL;
      printf(" ERROR: Invalid input resolution \n");
    }
  }

  if(gIMAGE_CONVERT_ctrl.outFileName[0]==0) {
    status = OSA_EFAIL;
    printf(" ERROR: Output file not specified \n");
  }

  if(gIMAGE_CONVERT_ctrl.outFormat >= IMAGE_FORMAT_MAX ) {
    status = OSA_EFAIL;
    printf(" ERROR: Output format is invalid \n");
  }

  if(gIMAGE_CONVERT_ctrl.outFormat != IMAGE_FORMAT_BMP) {
    if( gIMAGE_CONVERT_ctrl.outLineOffset == 0
      ) {

      status = OSA_EFAIL;
      printf(" ERROR: Invalid output line offset \n");
    }
  }

  if(gIMAGE_CONVERT_ctrl.inLineOffset*gIMAGE_CONVERT_ctrl.inHeight*3 > IMAGE_CONVERT_BUFFER_SIZE_MAX )
  {
    status = OSA_EFAIL;
    printf(" ERROR: Too big input size \n");
  }

  if(gIMAGE_CONVERT_ctrl.outLineOffset*gIMAGE_CONVERT_ctrl.inHeight*3 > IMAGE_CONVERT_BUFFER_SIZE_MAX )
  {
    status = OSA_EFAIL;
    printf(" ERROR: Too big output size \n");
  }

  if(status != OSA_SOK) {
    showUsage();
  }

  if(status==OSA_SOK) {
    status = OSA_fileReadFile(gIMAGE_CONVERT_ctrl.inFileName, gIMAGE_CONVERT_ctrl.inBuffer, gIMAGE_CONVERT_ctrl.inLineOffset*gIMAGE_CONVERT_ctrl.inHeight*3, &readSize);

    if(status != OSA_SOK ) {
      printf(" ERROR: File [%s] not found or read error \n", gIMAGE_CONVERT_ctrl.inFileName);
    }
  }

  return status;
}


