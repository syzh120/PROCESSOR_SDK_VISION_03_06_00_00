/*
* TICV
*
* This module contains bam applets that can be used for accelerating OpenCV functions
*
* Copyright (C) {YEAR} Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
*
*/

/**
 *  @file      BAM_sobel.h
 *
 *  @brief     This file defines the interface for BAM applet for edge detector
 *
 *  @version 0.0 (June 2017) : Base version.
 */

#ifndef _BAM_SOBEL_H
#define _BAM_SOBEL_H 1

void BAM_sobel(uint8_t *inputDataPtr,
               int16_t *outputDataPtr,
               uint32_t imageWidth,
               uint32_t imageHeight,
               uint32_t inputPitch,
               uint32_t outputPitch,
               uint32_t count,
               uint8_t *graphMem
               );

void edgeDetector_ref(uint8_t *inputDataPtr,
                      int16_t *outputDataPtr,
                      uint32_t imageWidth,
                      uint32_t imageHeight,
                      uint32_t inputPitch,
                      uint32_t outputPitch
                      );

void delGraphMem(uint8_t *graphMem);

#endif
