#ifndef GEOMETRY_POINTCLOUDLIB_H
#define GEOMETRY_POINTCLOUDLIB_H
/**
 * Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
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
 * @file pointCloudLib.h
 * @brief PointCloudLib contains library routines that use point cloud data, as opposed to routines
 *        in pointCloud.h which modify or access point clouds. This includes RANSAC estimators,
 *        segmentation, clustering, etc. that operate strictly on unordered point clouds without
 *        side information specific to another source (such as sensor information).
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <geometry/include/pointCloud.h>

// Maximum number of inliers that can be selected in point cloud ransac algorithms
#define POINTCLOUD_MAX_RANSAC_INLIERS       5000

/**
 * Fit a plane to the selected indices of points in the given point cloud using a RANSAC approach
 * with the given inlier tolerance and expected inlier fraction. The IDs of the inliers for the
 * are written to the output array (which must be the same size as the input array at least) and
 * the total number of inliers found is returned
 * @param[in] pc The point cloud storing point information
 * @param[in] ids Array of IDs to use for plane fitting
 * @param[in] N Number of IDs given in ID array
 * @param[in] tol Plane inlier tolerance, magnitude of distance from the plane must be smaller
 * @param[in] iter Number of ransac iterations, if 0 this will be selected assuming 60% inliers and
 *                 acceptable probability of error of 0.1%
 * @param[out] nd Array of 4 floats written to this address, defining the plane in Hessian normal
 *                form: n*p = d for all points p on the plane, as [n.x, n.y, n.z, d], with n being
 *                a unit length vector as well
 * @param[out] inliers Array of detected inliers for the plane in nd, must be given as the same size
 *                     as ids was initially
 * @return the total number of inliers found
 */
uint32_t PointCloud_ransacPlane(PointCloud *pc,
                                uint32_t *ids,
                                uint32_t N,
                                float tol,
                                uint32_t iters,
                                float *nd,
                                uint32_t *inliers);

#ifdef __cplusplus
}
#endif

#endif
