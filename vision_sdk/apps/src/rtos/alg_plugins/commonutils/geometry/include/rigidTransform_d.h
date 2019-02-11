#ifndef RIGID_TRANSFORM_D_H
#define RIGID_TRANSFORM_D_H
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
 * @file rigidTransform_d.h
 * @brief basic double support for rigidTransform.h
 */

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************
* TYPES
****************************************************/

//! rigid transformation
typedef struct rigid_transform_d_t
{
    double       R[9];     //!< 3x3 rotation matrix, in row-major order: [0], [1], [2] are the first row
    double       t[3];     //!< 3x1 translation vector
} RigidTransform_d;

/**
 * Set rigid transform to identity Euclidean transform (zero rotation & translation)
 * @param[in/out] M_in Pointer to RigidTransform_d
 */
void RigidTransform_d_identity(RigidTransform_d *M);

/**
 * set translation vector
 * @param[inout] M         RigidTransform_d pointer
 * @param[in]    x, y, z   double x, y and z coordinates of translation t
 */
void RigidTransform_d_setTranslation(RigidTransform_d *M, double x, double y, double z);

/**
 * Compose a transformation out of two given transformations, s.t. M31 = M32 * M21
 * @param[in] M32_in Left matrix in multiplication
 * @param[in] M21_in Right matrix in multiplication
 * @param[out] M31_out Destination transformation to be written to
 */
void RigidTransform_d_compose(RigidTransform_d *M32_in,
                            RigidTransform_d *M21_in,
                            RigidTransform_d *M31_out);

/**
 * Compute the inverse of a rigid transformation
 * @param[in] M12_in Transformation to invert
 * @param[out] M21_out Inversion written here
 */
void RigidTransform_d_inverse(RigidTransform_d *M12_in,
                            RigidTransform_d *M21_out);
/**
 * Print out the information in a rigid transformation for debugging purposes
 * @param[in] M Pointer to transformation to print
 */
void RigidTransform_d_print(RigidTransform_d *M);



#ifdef __cplusplus
}
#endif

#endif
