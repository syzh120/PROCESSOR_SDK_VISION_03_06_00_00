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
*  File: pinhole.h
*
*  \brief: a struct for describing a pinhole camera parameters
*
=======================================================================*/

#ifndef PINHOLE_H_INCLUDED
#define PINHOLE_H_INCLUDED



#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*Pinhole camera parameter, also known by the K matrix:
 *
 *K =  [ fx   skew   px
 *       0     fy    py
 *       0      0     1 ]
 */
typedef struct {
    float fx; /*focal length in x (horizontal) in pixels*/
    float fy; /*focal length in y (vertical)*/
    float px; /*principal point x-coordinate in pixels*/
    float py; /*principal point y-coordinate in pixels*/
    float alpha; /*skew*/
} Pinhole;


/*set pinhole model parameters to provided values*/
void Pinhole_set(Pinhole *ph, float fx, float fy, float px, float py, float alpha);

/*set pinhole model to identity K-matrix (fx=fy=1, px=py=0, skew=0)*/
void Pinhole_identity(Pinhole *ph);

/*compute inverse pinhole model (corresponding to inverse of K matrix).
 *Input and output pointers may be the same. */
void Pinhole_inverse(Pinhole *ph, Pinhole *phInv);

#ifdef __cplusplus
}
#endif /* __cplusplus */
						
#endif


