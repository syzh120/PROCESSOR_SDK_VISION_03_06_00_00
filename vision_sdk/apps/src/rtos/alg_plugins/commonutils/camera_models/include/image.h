/*=======================================================================
*
*            Texas Instruments Internal Reference Software
*
*
*                    Perception & Analytics Lab R&D
*
*         Copyright (c) 2016 Texas Instruments, Incorporated.
*                        All Rights Reserved.
*
*
*          FOR TI INTERNAL USE ONLY. NOT TO BE REDISTRIBUTED.
*
*                 TI Confidential - Maximum Restrictions
*
*
*
*=======================================================================
*
*  File: image.h
*
*  \brief Structs for describing an image
*
=======================================================================*/

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*Pixel Coordinate*/
typedef struct {
    float x;
    float y;
} Pixel;


#ifdef __cplusplus
}
#endif /* __cplusplus */
						
#endif


