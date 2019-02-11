#ifndef RIGID_TRANSFORM_H
#define RIGID_TRANSFORM_H
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
 * @file rigidTransform.h
 * @brief Declaration of structures and functions for rigid transforms
 * @todo Add restrict keyword where appropriate--investigate how it is handled across compilers
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "rigidTransform_d.h"

/****************************************************
* TYPES
****************************************************/

//! rigid transformation
typedef struct rigid_transform_t
{
    float       R[9];     //!< 3x3 rotation matrix, in row-major order: [0], [1], [2] are the first row
    float       t[3];     //!< 3x1 translation vector
} RigidTransform;

/**
 * Set rigid transform to identity Euclidean transform (zero rotation & translation)
 * @param[in/out] M_in Pointer to RigidTransform
 */
void RigidTransform_identity(RigidTransform *M);

/**
 * set translation vector to
 * @param[inout] M      RigidTransform pointer
 * @param[in] x, y, z   float x, y and z coordinates of translation t
 */
void RigidTransform_setTranslation(RigidTransform *M, float x, float y, float z);

/**
 * Compose a transformation out of two given transformations, s.t. M31 = M32 * M21, the output must
 * be distinct from the inputs
 * @param[in] M32_in Left matrix in multiplication
 * @param[in] M21_in Right matrix in multiplication
 * @param[out] M31_out Destination transformation to be written to
 */
void RigidTransform_compose(RigidTransform *M32_in,
                            RigidTransform *M21_in,
                            RigidTransform *M31_out);

/**
 * Compute the inverse of a rigid transformation, these must be different objects
 * @param[in] M12_in Transformation to invert
 * @param[out] M21_out Inversion written here
 */
void RigidTransform_inverse(RigidTransform *M12_in,
                            RigidTransform *M21_out);

/**
 * Scale a rigid transform by the given factor. This only affects the translation component as
 * rotations are unaffected by scaling. The input and output may be the same transformation
 * @param[in] M_in Transformation to scale
 * @param[in] f The scaling factor
 * @param[out] M_out The scaled transformation will be written here
 */
void RigidTransform_scale(RigidTransform *M_in, float f, RigidTransform *M_out);

/** @TODO MM: Should this be Point_rotate(p1, p2, RigidTransform)
 * Rotate a vector of 3 floats by the R matrix in the rigid transform only. The in and out vectors
 * may point to the same memory location, as this is done using temporary storage
 * @param[in] M The rotation to apply
 * @param[in] in The 3-vector to rotate
 * @param[out] out Where to write the resulting vector
 */
void RigidTransform_rotate(RigidTransform *M, float *in, float *out);

/**
 * Print out the information in a rigid transformation for debugging purposes
 * @param[in] M Pointer to transformation to print
 */
void RigidTransform_print(RigidTransform *M);

/**
 * Convert double to float precision
 * @param[in]  M_d pointer to double precision transformation
 * @param[out] M_f pointer to float precision transformation
 */
void RigidTransform_doubleToFloat(RigidTransform_d *M_d,
                                  RigidTransform *M_f);

/**
 * Convert float to double precision
 * @param[in]  M_f pointer to float precision transformation
 * @param[out] M_d pointer to double precision transformation
 */
void RigidTransform_floatToDouble(RigidTransform *M_f,
                                  RigidTransform_d *M_d);

#ifdef __cplusplus
}
#endif

#endif
