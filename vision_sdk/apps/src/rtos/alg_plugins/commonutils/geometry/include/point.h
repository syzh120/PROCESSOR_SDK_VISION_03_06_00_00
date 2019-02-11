#ifndef POINT_H
#define POINT_H
/**
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
 * All Rights Reserved.
 * The recipient shall have no right to copy or distribute or make any
 * use of this code, except as expressly provided in a separate written
 * license, executed between recipient and Texas Instruments.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file point.h
 * @brief Declaration of structures and functions for a point
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "rigidTransform.h"

/****************************************************
* TYPES
****************************************************/

//! A single point within a point cloud
typedef struct point_t
{
    float   x;      //!< Real 3D coordinate
    float   y;      //!< Real 3D coordinate
    float   z;      //!< Real 3D coordinate
    float   w;      //!< Metadata coordinate, free to use as desired
} Point;

/****************************************************
* FUNCTIONS
****************************************************/

/**
 * Set all four values for a point as a convenience function
 * @param[inout] dst Pointer to Point to be modified
 * @param[in] x New x value
 * @param[in] y New y value
 * @param[in] z New z value
 * @param[in] w New w value
 */
void Point_set(Point *dst, float x, float y, float z, float w);

/**
 * Scale the given point by the scale factor given, only affecting x, y, and z coordinates. The
 * w coordinate is unchanged.
 * @param[in] src The source point
 * @param[inout] dst The destination point, which may be the same as the source point
 * @param[in] scale The scale factor to multiply by
 */
void Point_applyScale(Point *src, Point *dst, float scale);

/**
 * Apply the given rigid transformation to a single point. dst = M_dst_src.R * src + M_dst_src.t.
 * w coordinate is unchanged.
 * @param[in] src Pointer to source point
 * @param[inout] dst Pointer to destination point, which may be the same as the source point
 * @param[in] M_dst_src The rigid transformation to be applied
 */
void Point_applyRigidTransform(Point *src, Point *dst, RigidTransform *M_dst_src);

/**
 * Dot product using x, y coordinates between two points
 * @param[in] p1 Pointer to point 1
 * @param[in] p2 Pointer to point 2
 * @param[out] float dot product
 */
float Point_dot2(Point *p1, Point *p2);

/**
 * Dot product using x, y, z coordinates between two points
 * @param[in] p1 Pointer to point 1
 * @param[in] p2 Pointer to point 2
 * @param[out] float dot product
 */
float Point_dot3(Point *p1, Point *p2);

/**
 * Dot product using x, y, z, w coordinates between two points
 * @param[in] p1 Pointer to point 1
 * @param[in] p2 Pointer to point 2
 * @param[out] float dot product
 */
float Point_dot4(Point *p1, Point *p2);


#ifdef __cplusplus
}
#endif

#endif
