#ifndef GEOMETRY_GRID_H
#define GEOMETRY_GRID_H
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
 * @file grid.h
 * @brief This defines the common grid functionality which is then used to construct occupancy grids
 *        that store a variety of data types
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//! Used for any computed cell that doesn't fit on the map
#define INVALID_GRID_CELL ((uint32_t)-1)

//! Possible type configurations for a grid structure
typedef enum grid_type_e
{
    GRID_TYPE_UINT32,           //!< The grid is used to store unsigned 32 bit integer data
    GRID_TYPE_FLOAT,            //!< The grid is used to store floating point data
    GRID_TYPE_BITS              //!< The grid is used to store flags packed in a 32 bit integer
} GridType;

//! A configuration structure which stores information that is required in order to compute how
//  much memory must be allocated to store this grid. This must be initialized before calling
//  getMemorySize() or init()
typedef struct grid_config_t
{
    GridType        type;               //!< What type of data will be stored in this grid
    uint32_t        xCells;             //!< Number of cells along x axis
    uint32_t        yCells;             //!< Number of cells along y axis
    uint32_t        zCells;             //!< Number of cells along z axis
    float           xCellSize;          //!< Length of cell along x
    float           yCellSize;          //!< Length of cell along y
    float           zCellSize;          //!< Length of cell along z
    float           xMin;               //!< Real x coordinate matching cell 0
    float           yMin;               //!< Real y coordinate matching cell 0
    float           zMin;               //!< Real z coordinate matching cell 0
} GridConfig;

//! A generic structure that stores pointers to different types of data and a flag indicating which
//  is actually used
typedef struct grid_t
{
    GridConfig      config;         //!< Configuration information describing the grid organization
    float           xInvCellSize;   //!< 1/xCellSize from config data
    float           yInvCellSize;   //!< 1/yCellSize from config data
    float           zInvCellSize;   //!< 1/zCellSize from config data
    uint32_t        dataCellCount;  //!< Number of cells in the data array
    uint32_t        dataOffset;     //!< Offset of the data field in bytes, relative to the struct
    union
    {
        uint32_t    *   ui32;       //!< Unsigned integer or flag data
        float       *   f32;        //!< Floating point data
    } data;
} Grid;

/**
 * Get the amount of memory required to create an occupancy grid structure
 * @param[in] config Pointer to configuration information describing the OG structure
 * @return Amount of memory to allocate in bytes, 0 if the configuration is invalid
 */
uint32_t Grid_getMemorySize(GridConfig *config);

/**
 * Given a chunk of memory, initialize it as an occupancy grid structure by assigning internal
 * pointers
 * @param[inout] mem Pointer to memory to use as the occupancy grid
 * @param[in] config The configuration data needed for configuration
 * @return Type-correct pointer to occupancy grid structure on the given memory
 */
Grid *Grid_init(uint8_t *mem, GridConfig *config);

/**
 * Clear an occupancy grid, resetting all values to zero
 * @param[in] og The occupancy grid to clear
 */
void Grid_clear(Grid *og);

/**
 * Update the internal pointers based on the base address given; this is needed when a pointer to
 * an occupancy grid is passed between cores that have different address spaces (i.e. going from
 * physical to virtual addresses or between distinct virtual addressing spaces).
 * @param[in] og The occupancy grid to update
 */
void Grid_updatePointers(Grid *og);

/**
 * Get the cell coordinate matching this x coordinate
 * @param[in] og The occupancy grid we're calculating a cell index for
 * @param[in] x The x coordinate to convert
 * @return The integer cell coordinate (not a linear index)
 */
uint32_t Grid_getXCell(Grid *og, float x);

/**
 * Get the cell coordinate matching this y coordinate
 * @param[in] og The occupancy grid we're calculating a cell index for
 * @param[in] y The y coordinate to convert
 * @return The integer cell coordinate (not a linear index)
 */
uint32_t Grid_getYCell(Grid *og, float y);

/**
 * Get the cell coordinate matching this z coordinate
 * @param[in] og The occupancy grid we're calculating a cell index for
 * @param[in] z The z coordinate to convert
 * @return The integer cell coordinate (not a linear index)
 */
uint32_t Grid_getZCell(Grid *og, float z);

/**
 * Compute the linear index assuming we are only using 2 of the 3 possible coordinates
 * @param[in] og The occupancy grid with dimension info
 * @param[in] x The x cell coordinate (0 indexed)
 * @param[in] y The y cell coordinate (0 indexed)
 * @return Linear index of the cell requested, not bounds checked
 */
uint32_t Grid_getLinearIndex2d(Grid *og, uint32_t x, uint32_t y);

/**
 * Compute the linear index using all three coordinates
 * @param[in] og The occupancy grid with dimension info
 * @param[in] x The x cell coordinate
 * @param[in] y The y cell coordinate
 * @param[in] z The z cell coordinate
 * @return Linear index of the cell requested, not bounds checked
 */
uint32_t Grid_getLinearIndex3d(Grid *og, uint32_t x, uint32_t y, uint32_t z);

/**
 * Set or retrieve the value stored in a given occupancy grid using 2 or 3d indexing commands. The
 * naming scheme is {set|get|ref}{f|u|b}{2d|3d} where f|u|b indicates data type and means float,
 * unsigned int, and bitfield respectively; and set sets a value, get gets a value, and ref returns
 * a mutable pointer to the value. Additionally the bitfield type has any, all, and clear as options
 * in place of set/get/ref to support the additional options of testing if any bits match, testing
 * if all bits match, or clearing the given bits
 * @param[in] og Grid structure to read/write
 * @param[in] x The x cell coordinate
 * @param[in] y The y cell coordinate
 * @param[in] z The z cell coordinate
 * @param[in] value/bits Value to write, test, or clear as appropriate
 */
void Grid_setf2d(Grid *og, uint32_t x, uint32_t y, float value);
void Grid_setf3d(Grid *og, uint32_t x, uint32_t y, uint32_t z, float value);
float Grid_getf2d(Grid *og, uint32_t x, uint32_t y);
float Grid_getf3d(Grid *og, uint32_t x, uint32_t y, uint32_t z);

void Grid_setu2d(Grid *og, uint32_t x, uint32_t y, uint32_t value);
void Grid_setu3d(Grid *og, uint32_t x, uint32_t y, uint32_t z, uint32_t value);
uint32_t Grid_getu2d(Grid *og, uint32_t x, uint32_t y);
uint32_t Grid_getu3d(Grid *og, uint32_t x, uint32_t y, uint32_t z);

void Grid_setb2d(Grid *og, uint32_t x, uint32_t y, uint32_t bits);
void Grid_setb3d(Grid *og, uint32_t x, uint32_t y, uint32_t z, uint32_t bits);
uint32_t Grid_getb2d(Grid *og, uint32_t x, uint32_t y);
uint32_t Grid_getb3d(Grid *og, uint32_t x, uint32_t y, uint32_t z);

uint32_t Grid_anyb2d(Grid *og, uint32_t x, uint32_t y, uint32_t bits);
uint32_t Grid_anyb3d(Grid *og, uint32_t x, uint32_t y, uint32_t z, uint32_t bits);
uint32_t Grid_allb2d(Grid *og, uint32_t x, uint32_t y, uint32_t bits);
uint32_t Grid_allb3d(Grid *og, uint32_t x, uint32_t y, uint32_t z, uint32_t bits);

void Grid_clearb2d(Grid *og, uint32_t x, uint32_t y, uint32_t bits);
void Grid_clearb3d(Grid *og, uint32_t x, uint32_t y, uint32_t z, uint32_t bits);

float *Grid_reff2d(Grid *og, uint32_t x, uint32_t y);
float *Grid_reff3d(Grid *og, uint32_t x, uint32_t y, uint32_t z);
uint32_t *Grid_refu2d(Grid *og, uint32_t x, uint32_t y);
uint32_t *Grid_refu3d(Grid *og, uint32_t x, uint32_t y, uint32_t z);
uint32_t *Grid_refb2d(Grid *og, uint32_t x, uint32_t y);
uint32_t *Grid_refb3d(Grid *og, uint32_t x, uint32_t y, uint32_t z);

#ifdef __cplusplus
}
#endif

#endif
