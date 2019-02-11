#ifndef _AUTO_REMAP_COMMONDEFS_H_
#define _AUTO_REMAP_COMMONDEFS_H_

#ifndef PC_VERSION
#include <include/link_api/system.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#define ALGORITHM_PROCESS_OK 0
#define ALGORITHM_PROCESS_FAIL -1

#define L_PIC_IDX 1
#define R_PIC_IDX 0

typedef enum {
	FEATURE_COLLECT,
	PERSMAT_CAL,
	RUN_REMAP
} PROCESS_MODE;

typedef enum
{
	FILE_TYPE_PGM,
	FILE_TYPE_YUV_420,
	FILE_TYPE_YUV_422
} IMG_TYPE;


typedef unsigned char  Byte;
typedef float          FLOAT;


typedef UInt32         uWord32;
typedef Int32          Word32;
typedef UInt16         uWord16;
typedef Int16          Word16;
//typedef UInt8          Byte;
//typedef UInt8          Bool;

/*
typedef S08            Int8;
typedef U08            UInt8;
typedef Byte           Bool;
typedef S16            Int16;
typedef S32            Int32;
typedef U16            UInt16;
typedef U32            UInt32;
*/

// SHOULD BE 0
// Fisheye lens rectification is disabled temporarily
// LDC table should be read from SD card
#define ENABLE_FISHEYE_RECT 0

#define INPUT_SCALE_BEFORE_RECT 1

#define NUM_MAX_VIEWS       (2)
#define NUM_MAX_COLORPLANES (1)

#define MAX_INPUT_CAMERAS	NUM_MAX_VIEWS
#define MAX_COLOR_CHANNELS	NUM_MAX_COLORPLANES

/*
#define OUT_FRAME_WIDTH     640
#define OUT_FRAME_HEIGHT    360

#define REMAP_BLOCK_WIDTH   64
#define REMAP_BLOCK_HEIGHT  8
*/


#define SMALC_MAX_IMAGE_WIDTH				384
#define SMALC_MAX_BRIEF_SAMPLE_PAIRS		256
#define SMALC_MAX_HARRIS_FEATURES			2500
#define HARRIS_DEFAULT_SENSITIVITY_SQ0_15	1310	// 0.04 * 2^15 = 0.04 * 32768 = 1310.72
#define HARRIS_MAX_BLOCKSIZE				7
#define HARRIS_SCORE_THRESHOLD				1.0 // 0.75
#define SMALC_NUM_COEFFECIENTS				5
#define SMALC_MAX_TOLERABLE_FEATURE_ERROR	0.5   // 0.4

#endif
