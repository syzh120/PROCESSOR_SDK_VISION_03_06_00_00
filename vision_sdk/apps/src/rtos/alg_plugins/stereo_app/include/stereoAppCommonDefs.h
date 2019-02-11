#ifndef _STEREOAPP_COMMONDEFS_H_
#define _STEREOAPP_COMMONDEFS_H_

#ifndef PC_VERSION
#include <include/link_api/system.h>
#endif


#include <stdio.h>
#include <stdlib.h>

#define ALGORITHM_PROCESS_OK 0
#define ALGORITHM_PROCESS_FAIL -1



#ifdef PC_VERSION
typedef char           Int8;
typedef unsigned char  Bool;
typedef unsigned char  UInt8;
typedef short          Int16;
typedef int            Int32;
typedef unsigned short UInt16;
typedef unsigned int   UInt32;
#endif


typedef UInt32         uWord32;
typedef Int32          Word32;
typedef UInt16         uWord16;
typedef Int16          Word16;
typedef UInt8          Byte;


#define MAX_DISPARITY_NUM       2048
#define MAX_L2_MEMORY_SIZE      200000

#ifdef PC_VERSION
#define MATLAB_DATA_GEN         1
#endif

#define MAX_INPUT_STEREO_PAIRS  3 

// 3D occupancy grid
#define UNIFORM_GRID_INTERVAL   50
#define DEAD_ZONE               UNIFORM_GRID_INTERVAL/2

// points out of these ranges will be discarded when constructing OG map
#define X_MIN_GRID_VALUE        (-1000 - DEAD_ZONE)
#define X_MAX_GRID_VALUE        ( 1000 + DEAD_ZONE)
#define Y_MIN_GRID_VALUE        (-1000 - DEAD_ZONE)
#define Y_MAX_GRID_VALUE        ( 1000 + DEAD_ZONE)
#define Z_MIN_GRID_VALUE        (-1000 - DEAD_ZONE)
#define Z_MAX_GRID_VALUE        ( 1000 + DEAD_ZONE)


// Odd number of grid so that the center is camera location
#define UNIF_GRID_SIZE_X        ((X_MAX_GRID_VALUE - X_MIN_GRID_VALUE)/UNIFORM_GRID_INTERVAL)
#define UNIF_GRID_SIZE_Y        ((Y_MAX_GRID_VALUE - Y_MIN_GRID_VALUE)/UNIFORM_GRID_INTERVAL)
#define UNIF_GRID_SIZE_Z        ((Z_MAX_GRID_VALUE - Z_MIN_GRID_VALUE)/UNIFORM_GRID_INTERVAL)

// ROI range around center grid index
#define X_ROI_OFFSET          ((UNIF_GRID_SIZE_X/2) - 1)
#define Y_ROI_OFFSET          ((UNIF_GRID_SIZE_Y/2) - 1)
#define Z_ROI_OFFSET          ((UNIF_GRID_SIZE_Z/2) - 1)

// SB range around center grid index
#define X_SB_OFFSET           5
#define Y_SB_OFFSET           5
#define Z_SB_OFFSET           5

// offset from which actual og map start. The first index is dummy
#define OG_INDEX_OFFSET       1   // DO NOT CHANGE

// for connected component analysis
#define CONN_NUM              26

// motion search points - depending on ROI size
#define ME_SEARCH_POINT        39
#define NUM_FRAMES_SIGMA_UPDATE 3

#define SB_RADIUS 250



#endif
