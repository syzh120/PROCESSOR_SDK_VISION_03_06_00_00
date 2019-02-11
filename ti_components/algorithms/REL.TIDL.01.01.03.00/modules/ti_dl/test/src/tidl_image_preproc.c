/*
*
* Copyright (c) {2015 - 2017} Texas Instruments Incorporated
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
* *     No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *     any redistribution and use are licensed by TI for use only with TI Devices.
*
* *     Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *     any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *     any redistribution and use of any object code compiled from the source code
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


/** @file tidl_image_preproc.c
*
*  @brief  This file contains image read related 
*       test code for TI DL test application
*
*
*  @date  Aug 2017
*
*/


#if (HOST_EMULATION)  || (VCOP_HOST_EMULATION)
#ifdef BUILD_WITH_OPENCV
#define USE_OPENCV (1)
#else
#define USE_OPENCV (0)
#endif  
#else
#define USE_OPENCV (0)
#endif
#include <stdint.h>
#include <stdio.h>

#if USE_OPENCV        
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace cv;    
using namespace std;

int32_t readImage(uint8_t *imageFile, int8_t *ptr, int16_t roi, int16_t n, 
                  int16_t width, int16_t height, int16_t pitch, 
                  int32_t chOffset, int32_t frameCount, int32_t preProcType)
{

  int32_t  i0, i1, i2, i3;
  Mat image;
  Mat spl[3];
  std::string fileName = (char*)imageFile;
  image = cv::imread(fileName, CV_LOAD_IMAGE_COLOR);  // Read the file
  int32_t enableMeanSub = 0;
  Mat tempImage; 
  int32_t meanVlaues[3];
  
  if(preProcType == 0) // Caffe-Jacinto Models
  {
   int32_t crop_width    =  width;
   int32_t crop_height    =  height;
   int32_t half_the_width  =  256/ 2;
   int32_t half_the_height =  256/ 2;

   int32_t startX  = half_the_width -crop_width/2;
   int32_t startY  = half_the_height -crop_height/2;
   
   cv::Rect myROI(startX,
   startY,
   crop_width,
   crop_height);
   cv::resize(image, tempImage, Size(256,256), 0,0,cv::INTER_AREA); 
   image = tempImage(myROI);
   enableMeanSub = 0;
  }
  else if (preProcType == 1) // Caffe Models , eg : SqueezeNet
  {
   
   int32_t crop_width    =  width;
   int32_t crop_height    =  height;
   int32_t half_the_width  =  256/ 2;
   int32_t half_the_height =  256/ 2;

   int32_t startX  = half_the_width -crop_width/2;
   int32_t startY  = half_the_height -crop_height/2;
   
   cv::Rect myROI(startX,
   startY,
   crop_width,
   crop_height);
   cv::resize(image, tempImage, Size(256,256), 0,0,cv::INTER_AREA); 
   image = tempImage(myROI);
   enableMeanSub = 1;
   meanVlaues[0] = 104;
   meanVlaues[1] = 117;
   meanVlaues[2] = 123;
   
  }
  else if (preProcType == 2)
  {
   cv::cvtColor(image, image, CV_BGR2RGB);
   float factor  = 0.875; 
   int32_t orgWidth  = image.size[1];
   int32_t orgHeight = image.size[0];

   int32_t crop_width    =  orgWidth*factor;
   int32_t crop_height    =  orgHeight*factor;
   int32_t half_the_width  = orgWidth/ 2;
   int32_t half_the_height = orgHeight / 2;

   int32_t startX  = half_the_width -crop_width/2;
   int32_t startY  = half_the_height -crop_height/2;
   
   cv::Rect myROI(startX,
   startY,
   crop_width,
   crop_height);
   tempImage = image(myROI);
   cv::resize(tempImage, image, Size(width,height), 0,0,CV_INTER_AREA); 
   enableMeanSub = 1;
   meanVlaues[0] = 128;
   meanVlaues[1] = 128;
   meanVlaues[2] = 128;
  }  
  else if (preProcType == 3)
  {
   cv::cvtColor(image, image, CV_BGR2RGB);
   int32_t crop_width    =  width;
   int32_t crop_height    =  height;
   int32_t half_the_width  =  32/ 2;
   int32_t half_the_height =  32/ 2;

   int32_t startX  = half_the_width -crop_width/2;
   int32_t startY  = half_the_height -crop_height/2;
   
   cv::Rect myROI(startX,
   startY,
   crop_width,
   crop_height);
   cv::resize(image, tempImage, Size(32,32), 0,0,cv::INTER_AREA); 
   image = tempImage(myROI);
   enableMeanSub = 0;
  }  
  else if (preProcType == 4)
  {
   //cv::cvtColor(image, image, CV_BGR2RGB);
   int32_t crop_width    =  width;
   int32_t crop_height    =  height;
   int32_t half_the_width  =  width/ 2;
   int32_t half_the_height =  height/ 2;

   int32_t startX  = half_the_width -crop_width/2;
   int32_t startY  = half_the_height -crop_height/2;
   
   cv::Rect myROI(startX,
   startY,
   crop_width,
   crop_height);
   cv::resize(image, tempImage, Size(width,height), 0,0,cv::INTER_AREA); 
   image = tempImage(myROI);
   enableMeanSub = 0;
  }
  else if (preProcType == 5)
  {
    cv::cvtColor(image, image, CV_BGR2RGB);
    float factor = 1;
    int32_t orgWidth = image.size[1];
    int32_t orgHeight = image.size[0];

    int32_t crop_width = orgWidth*factor;
    int32_t crop_height = orgHeight*factor;
    int32_t half_the_width = orgWidth / 2;
    int32_t half_the_height = orgHeight / 2;

    int32_t startX = half_the_width - crop_width / 2;
    int32_t startY = half_the_height - crop_height / 2;

    cv::Rect myROI(startX,
      startY,
      crop_width,
      crop_height);
    tempImage = image(myROI);
    cv::resize(tempImage, image, Size(width, height), 0, 0, CV_INTER_AREA);
    enableMeanSub = 1;
    meanVlaues[0] = 128;
    meanVlaues[1] = 128;
    meanVlaues[2] = 128;
  }
  else
  {
    printf("Unsupported preProcType : %d\n",preProcType);
  }
    
  
   
  
  if(image.channels() > 3)
  {
   return 0;   
  } 
  if(image.total() != height* width)
  {
   return 0;   
  } 
  int size = (int)image.total()*image.channels();
  uint8_t * data = (uint8_t*)malloc(size);

  if(data == NULL)
  {
   return 0;   
  }
  
  split(image,spl);
  for(i0 = 0; i0 < image.channels(); i0++)
  {   
   std::memcpy(&data[i0*((int)image.total())],spl[i0].data,((int)image.total()) * sizeof(uint8_t));
  }
  for(i2 = 0; i2 < roi; i2++)
  {
   for(i0 = 0; i0 < n; i0++)
   {
    for(i1 = 0; i1 < height; i1++)
    {
      for(i3 = 0; i3 < width; i3++)
      {  
       int32_t in;    

       if(enableMeanSub)
       {
        if(n != 1)
        {
          in =  data[i2*n*width*height + i0*width*height+ i1*width + i3] - meanVlaues[i0];
        }
        else
        {
          in =  data[i2*1*width*height + i1*width + i3] - meanVlaues[i0];
        }
        
        if(in > 127)  in  = 127;
        if(in < -128) in = -128;
       }
       else
       {
        
        if(n != 1)
        {
          in =  data[i2*n*width*height + i0*width*height+ i1*width + i3];
        }
        else
        {
          in =  data[i2*1*width*height + i1*width + i3];
        }
       }
       
       ptr[i2*n*chOffset + i0*chOffset + i1*pitch + i3] = in;
      }
    }
   }
  }
  return 1;
  
  
}
#else
int32_t readImage(uint8_t *imageFile, int8_t *ptr, int16_t roi, int16_t n, 
                  int16_t width, int16_t height, int16_t pitch, 
                  int32_t chOffset, int32_t frameCount, int32_t preProcType)
{
  printf("Image reading is Not Supported. OpenCV not Enabled\n");
  return (0);
}
#endif


