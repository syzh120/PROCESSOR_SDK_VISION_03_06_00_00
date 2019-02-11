/*=======================================================================
*
*            Texas Instruments Internal Reference Software
*
*                           EP Systems Lab
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
*  File: fisheyeCamera.h
*
*  \brief: a fisheye camera modeled as pinhole camera plus LDC LUT
*
=======================================================================*/

#ifndef FISHEYE_CAMERA_H_INCLUDED
#define FISHEYE_CAMERA_H_INCLUDED



#include <stdint.h>
#include "pinholeCamera.h"
#include "../../lens_distortion_correction/lens_distortion_correction.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Fisheye camera comprised of pinhole camera model with lens distortion described by
 * LensDistortionCorrection LUT model.
 * NOTE: LensDistortionCorrection LUT model requires pinhole camera to have
 *       fx=fy (isotropic) and alpha=0 (no skew). This needs to be ensured by the caller
 */
typedef struct {
    PinholeCamera pinholeCamera;
    LensDistortionCorrection ldc;
} FisheyeCamera;


/*set up FisheyeCamera struct given pointer to a Pinhole struct and the
 * LensDistortionCorrection parameters.
 * Output uint32_t status is 0 on success*/
uint32_t FisheyeCamera_set(FisheyeCamera *fc,
                        Pinhole *pinholePrms,
                        dtype *d2u_table, uint32_t d2u_length, dtype d2u_step,
                        dtype *u2d_table, uint32_t u2d_length, dtype u2d_step);


/*Convert from distorted (xyd) to undistorted (xyu) coordinates via LDC LUTs
 * LDC_status indicates if LDC LUT look-up was successful
 * Output uint32_t status is 0 on success*/
uint32_t FisheyeCamera_undistortPoint(FisheyeCamera *fc, Pixel *xyd, Pixel *xyu, float *rdSq);

/*Convert from undistorted (xyu) to distorted (xyd) coordinates via LDC LUTs
 * LDC_status indicates if LDC LUT look-up was successful
 * Output uint32_t status is 0 on success*/
uint32_t FisheyeCamera_distortPoint(FisheyeCamera *fc, Pixel *xyu, Pixel *xyd);

/* apply Kinv matrix to a point to convert from undistorted image (xyu) to normalized (xyn) coordinates
* xyn and xyu may be the same array*/
void FisheyeCamera_normalizePoint(FisheyeCamera *fc, Pixel *xyu, Pixel *xyn);

/* apply K matrix to a point to convert from normalized (xyn) to undistorted image (xyu)  pixel coordinates
* xyn and xyu may be the same array*/
void FisheyeCamera_unnormalizePoint(FisheyeCamera *fc, Pixel *xyn, Pixel *xyu);

/* project 3d point given in 3d camera coordinates (xyz) to camera (image) coordinates (xy).*/
/* If bOnlyInFront is true, the projection happens only if xyz.z>0, i.e. if the point
 * is in front of the camera; otherwise, the projection is applied in any case.
 * Output uint32_t status is 0 on success*/
uint32_t FisheyeCamera_project(FisheyeCamera *fc,
                             Point *xyz, Pixel *xy, uint8_t bOnlyInFront);


#ifdef __cplusplus
}
#endif /* __cplusplus */
						
#endif


