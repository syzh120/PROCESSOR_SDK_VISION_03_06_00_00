#ifndef GEOMETRY_OCCUPANCYGRID_H
#define GEOMETRY_OCCUPANCYGRID_H
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
 * @file occupancyGrid.h
 * @brief Manipulate a grid structure as an "occupancy grid" which stores cell information in the
 *        bits field of the backing data
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// Flag bits for the occupancy grid
#define OG_FLAG_OCCUPIED        0x00000001  //!< Contains at least one non-ground point
#define OG_FLAG_GROUND          0x00000002  //!< Contains a mixture of ground and drivable points
#define OG_FLAG_DRIVEABLE       0x00000004  //!< Contains only drivable points

// Forward declarations of these allow us to skip headers and additional dependencies
struct grid_t;
struct point_cloud_t;

/**
 * Populate the flags based on the tags in any points contained within the associated point cloud.
 * Currently this assigns flags for occupied, potential ground point, and drivable points. A cell
 * is classified conservatively based on the safest types of points observed: all cells containing
 * any untagged points are marked as occupied, containing only ground and driveable points are
 * marked as ground, and only driveable points are marked as driveable.
 * @param[inout] og The occupancy grid to update with additional point cloud measurements
 * @param[in] cloud The point cloud to read point data and tags from
 */
void OccupancyGrid_populateFrom(struct grid_t *og, struct point_cloud_t *cloud);

#ifdef __cplusplus
}
#endif

#endif
