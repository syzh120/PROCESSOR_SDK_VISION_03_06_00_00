/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef VLIB_TRIANGULATEPOINT_TYPES_H_
#define VLIB_TRIANGULATEPOINT_TYPES_H_ 1

#define VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE (12)
#define VLIB_TRIANG_CAMERA_INTRINSIC_PARAM_SIZE (9)

/*
* To make double word alignment and also to take account of last row
* which is 0 0 0 1
*/
#define  VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_ASIZE (VLIB_TRIANG_CAMERA_EXTRENSIC_PARAM_SIZE + 8)

/* To make double word aligned.
*/
#define VLIB_TRIANG_CAMERA_INTRINSIC_PARAM_ASIZE (VLIB_TRIANG_CAMERA_INTRINSIC_PARAM_SIZE + 1)
/*
* Maximum number track length which is considered for triangulation
*/
#define VLIB_TRIANG_MAX_POINTS_IN_TRACK (6)
/*
* Maximum number of tracks worked together, called as vector.
*/
#define VLIB_TRIANG_NUM_TRACKS_IN_ONE_VECTOR (2)

/*
* Total number of unique element in matrix At*A used in triangulation
*/
#define VLIB_TRIANG_NUM_UNIQUE_ELEMENTS_IN_ATA (6)

/* Number of rows in triangulation matrix
*/
#define VLIB_TRIANG_MAT_ROW (3)

/* Number of columns in triangulation matrix
*/
#define VLIB_TRIANG_MAT_COL (VLIB_TRIANG_MAX_POINTS_IN_TRACK * 2)

/* Aligned number of rows for triangulation matrix, to have data double word aligned.
*/
#define VLIB_TRIANG_MAT_AROW ((VLIB_TRIANG_MAT_ROW + 1) & 0xFFFFFFFE)

#endif
/* ======================================================================== */
/*  End of file:  VLIB_triangulatePoints_types.h                            */
/* ======================================================================== */

