#ifndef POINT_CLOUD_H
#define POINT_CLOUD_H
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
 * @file pointCloud.h
 * @brief Declaration of structures and functions used to manipulate point clouds
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "point.h"
#include "rigidTransform.h"

//! ID of a point guaranteed to be invalid
#define INVALID_POINT_OFFSET ((uint32_t)-1)

// Possible tag bits for points
#define POINTCLOUD_TAG_VALID                0x00000001
#define POINTCLOUD_TAG_VERTICAL_NORMAL      0x00000002
#define POINTCLOUD_TAG_MAYBE_GROUND         0x00000004
#define POINTCLOUD_TAG_DRIVEABLE            0x00000008

/****************************************************
* TYPES
****************************************************/

//! An aggregation of points to form a cloud
typedef struct point_cloud_t
{
    uint32_t    maxPoints;          //!< Maximum number of points this has space for
    uint32_t    numPoints;          //!< Number of points used
    uint32_t    numValidPoints;     //!< Number of currently valid points
    uint32_t    byteOffsetPoints;   //!< How many bytes is points pointer offset from point cloud's base pointer
    uint32_t    byteOffsetTags;     //!< How many bytes is tags pointer offset from point cloud's base pointer
    RigidTransform Mref;        //!< transform that takes the 3D points to the "reference" coordinate system
                                    //!< "reference" is to be defined/interpreted by the user of the library
    Point       *points;            //!< Array of points in memory
    uint32_t    *tags;              //!< Tag data for points, including all status
} PointCloud;



/****************************************************
* FUNCTIONS
****************************************************/
/**
 * Get the required number of bytes to pass to a separate allocator (e.g. Utils_memAlloc) to create
 * memory for a point cloud able to contain the given number of points
 * @param[in] numPoints The number of points the cloud must be able to hold
 * @return The size of the memory required, in bytes
 */
uint32_t PointCloud_getRequiredMemorySizeInBytes(uint32_t numPoints);

/**
 * In multi-core environment it may possible that point cloud'ss base address is converted to a different
 * address space. Depending on how this happens, the internal pointers of PointCloud struct may or may not
 * be updated. By calling this function, it is insured that the internal pointers point to the correct
 * address. Internally, this functions applies offsets to the PointCloud's base pointer to arrive at the
 * correct address. These offset were computed at initialization time.
 * @param[inout] cloud Pointer to point cloud
 */
void PointCloud_updateInternalPointers(PointCloud *cloud);

/**
 * Initialize a point cloud structure using the given chunk of memory
 * @param[in] A pointer to a memory region to use for backing the point cloud
 * @return Pointer to the point cloud structure created within the given buffer
 */
PointCloud *PointCloud_init(uint8_t *memPtr, uint32_t numPoints);

/**
 * Clean up the point cloud given. Does not de-allocate memory, as that must be done by the caller
 * who knows where and how it was allocated
 * @param[inout] cloud Pointer to the cloud to clean up
 */
void PointCloud_deinit(PointCloud *cloud);

/**
 * Clears all of the points in the point cloud and resets used sizes to zero. The memory, however,
 * remains allocated exactly as it was before
 * @param[inout] cloud Pointer to point cloud
 */
void PointCloud_clear(PointCloud *cloud);

/**
 * Copy the given point into the point cloud at the end and mark it valid.
 * If point cloud is full, point is not added.
 * @param[inout] pc Point cloud to add to
 * @param[in] xyzw Point to copy from, the original is left unmodified
 * @return The id/offset of this point after adding it to the cloud.
 *         INVALID_POINT_OFFSET if point cloud is full.
 */
uint32_t PointCloud_addPoint(PointCloud *pc, Point *xyzw);

/**
 * Copy points from the given array to the end of the cloud and mark all valid
 * @param[inout] pc The point cloud to copy to
 * @param[in] xyzw Pointer to a dense array of points in memory
 * @param[in] numPoints Number of points in the array to copy
 * @return The number of points copied, in case not all could fit in the destination cloud
 */
uint32_t PointCloud_addPoints(PointCloud *pc, Point *xyzw, uint32_t numPoints);

/**
 * Accessor for the numPoints field to provide an abstraction
 * @param[in] pc Pointer to point cloud
 * @return Number of total points in the cloud (valid+invalid)
 */
uint32_t PointCloud_getTotalPointCount(PointCloud *pc);

/**
 * Accessor for the numValidPoints field to provide an abstraction
 * @param[in] pc Pointer to point cloud
 * @return Number of valid points only
 */
uint32_t PointCloud_getValidPointCount(PointCloud *pc);

/**
 * Copy the point at the given index into the supplied memory region, leaving the original untouched
 * The offsets identify a point within the cloud without regards to valid/invalid status. If an
 * invalid id/offset is given, the destination point is not modified
 * @param[in] pc Pointer to point cloud
 * @param[in] id Offset of point within the cloud
 * @param[inout] dst Pointer to destination point to copy to
 * @return 1 if successfully copied, 0 otherwise
 */
uint8_t PointCloud_getPoint(PointCloud *pc, uint32_t id, Point *dst);

/**
 * Copy coordinate reference transform into RigidTransform pointer
 * @param[in] pc Pointer to point cloud
 * @param[out] M Pointer to RigidTransform
 */
void PointCloud_getMref(PointCloud *pc, RigidTransform *M);

/**
 * Set coordinate reference transform to supplied RigidTransform
 * @param[inout] pc Pointer to point cloud
 * @param[in] M Pointer to RigidTransform
 */
void PointCloud_setMref(PointCloud *pc, RigidTransform *M);

/**
 * Get a writeable reference to a point at the given offset within the given cloud. This does not
 * check valid/invalid status
 * @param[in] pc Pointer to point cloud
 * @param[in] id ID/offset of point within cloud, ignoring valid status
 * @return Pointer to the identified point, or null if the ID was outside the bounds of the cloud
 */
Point *PointCloud_refPoint(PointCloud *pc, uint32_t id);

/**
 * Test if the point at the supplied offset is valid
 * @param[in] pc Pointer to point cloud
 * @param[in] id ID/offset of point to check
 * @return 1 if valid, 0 if invalid or the ID is outside the point cloud's bounds
 */
uint8_t PointCloud_isPointValid(PointCloud *pc, uint32_t id);

/**
 * Mark the point at the given id/offset as invalid. Bad offsets are ignored silently
 * @param[in] pc Pointer to point cloud
 * @param[in] id ID/offset of point to update
 */
void PointCloud_invalidatePoint(PointCloud *pc, uint32_t id);

/**
 * Add a tag bit to a given point. This is a low level function. When setting the valid tag, this
 * function should not be used. Points are only marked valid when they are added.
 * @param[in] pc Pointer to point cloud
 * @param[in] id ID/offset of point to update
 * @param[in] tag Tag bit to apply
 */
void PointCloud_tag(PointCloud *pc, uint32_t id, uint32_t tag);

/**
 * Remove a tag bit from a given point. This is a low level function. When removing the valid tag,
 * this function should not be used (externally). Use Pointcloud_invalidatePoint() instead!
 * @param[in] pc Pointer to point cloud
 * @param[in] id ID/offset of point to update
 * @param[in] tag Tag bit to remove
 */
void PointCloud_untag(PointCloud *pc, uint32_t id, uint32_t tag);

/**
 * Test if an exact match for the given set tag bits exist at the specific point. Does not compare
 * unset tag bits (i.e. it does not require they also be unset)
 * @param[in] pc Pointer to point cloud
 * @param[in] id ID/offset of point to test
 * @param[in] tag Tag bit(s) to match. All must be present in the tags for that point
 * @return 1 if all bits are present, 0 otherwise
 */
uint32_t PointCloud_isTagged(PointCloud *pc, uint32_t id, uint32_t tag);

/**
 * Retrieve the raw tag bits for a particular point. Used mostly if you want to do something that
 * isn't covered by isTagged (i.e. checking that specifics bits are not set)
 * @param[in] pc Pointer to point cloud
 * @param[in] id ID/offset ot point to read tag bits for
 * @return tag bits from the matching point
 */
uint32_t PointCloud_readTag(PointCloud *pc, uint32_t id);

/**
 * Append the points from the source cloud to the destination cloud, so long as it has room. The
 * source cloud is not modified. Only valid points are copied. Optionally provides the new IDs of
 * all of the points in the source cloud, within the destination cloud, including invalid points,
 * whose ID will be listed as INVALID_POINT_OFFSET. Tags and Mref are copied verbatim to the
 * destination cloud.
 * @param[in] src Pointer to source cloud
 * @param[in] dst Pointer to destination cloud
 * @param[inout] ids If given (not NULL), then the new IDs of all points are written here
 * @return The number of points actually copied to the destination cloud
 */
uint32_t PointCloud_append(PointCloud *src, PointCloud *dst, uint32_t *ids);

/**
 * Transform the valid points in the source cloud to the destination cloud by using the given
 * rigid transformation. The source and destination may be the same. The rigid transform in the
 * destination is updated to account for the cascade required to return to the same reference
 * @param[in] src The source cloud, which remains unmodified
 * @param[inout] dst The destination cloud which will receive the transformed points
 * @param[in] M_dst_src The rigid transformation to use to compute the destination cloud
 */
void PointCloud_applyRigidTransform(PointCloud *src, PointCloud *dst, RigidTransform *M_dst_src);

/**
 * Scale all valid points in the source cloud and write them to the destination cloud. The two
 * may overlap if desired. The rigid transform in the destination cloud is updated for scale
 * @param[in] src The source cloud, unchanged unless it is also the destination
 * @param[in] dst The destination cloud to write to
 * @param[in] scale The scaling factor to use for each point
 */
void PointCloud_applyScale(PointCloud *src, PointCloud *dst, float scale);

/**
 * Find minimum and maximum of quantity Q among all valid points in the cloud where
 * Q is the dot product between a point (x,y,z,w) and 4-vector 'basis'. For example, if
 * basis = [1, 0, 0, 0], the function finds the minimum and maximum x-value.
 * @param[in] pc The source cloud, unchanged
 * @param[in] basis Pointer to basis vector for computing objective quantity Q
 * @param[out] minVal, maxVal Minimum/maximum value are written here
 * @param[out] minId, maxId   Point index for which Q is minimum/maximum is written here
 */
void PointCloud_getMinMax(PointCloud *pc, Point *basis,
                          float *minVal, float *maxVal,
                          uint32_t *minId, uint32_t *maxId);

#ifdef __cplusplus
}
#endif

#endif
