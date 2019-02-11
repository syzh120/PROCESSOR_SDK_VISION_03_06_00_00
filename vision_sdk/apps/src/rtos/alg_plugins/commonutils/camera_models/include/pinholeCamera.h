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
*  File: pinholeCamera.h
*
*  \brief: an ideal pinhole camera
*
=======================================================================*/

#ifndef PINHOLE_CAMERA_H_INCLUDED
#define PINHOLE_CAMERA_H_INCLUDED

#include "pinhole.h"
#include "image.h"
#include "../../geometry/include/point.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Ideal pinhole camera defined by K matrix.
 * Inverse of K-matrix (Kinv) is included for efficiency.
 */
typedef struct {
    Pinhole K;
    Pinhole Kinv;
} PinholeCamera;

/* set up PinholeCamera object given pointer to a Pinhole struct*/
void PinholeCamera_set(PinholeCamera *phc,
                       Pinhole *prms);

/* apply Kinv matrix to a point to convert from image (xyu) to normalized (xyn) pixel coordinates
 * xyn and xyu may be the same array*/
void PinholeCamera_normalizePoint(PinholeCamera *phc, Pixel *xyu, Pixel *xyn);

/* apply K matrix to a point to convert from normalized (xyn) to image (xyu)  pixel coordinates
* xyn and xyu may be the same array*/
void PinholeCamera_unnormalizePoint(PinholeCamera *phc, Pixel *xyn, Pixel *xyu);

/* project 3d point given in 3d camera coordinates (xyz) to camera (image) coordinates (xy).*/
/* If bOnlyInFront is true, the projection happens only if xyz.z>0, i.e. if the point
 * is in front of the camera; otherwise, the projection is applied in any case.*/
void PinholeCamera_project(PinholeCamera *phc,
                           Point *xyz, Pixel *xy, uint8_t bOnlyInFront);

#ifdef __cplusplus
}
#endif /* __cplusplus */
						
#endif


