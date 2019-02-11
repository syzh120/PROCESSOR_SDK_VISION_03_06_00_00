/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
*
*  File: sgx3DsfmDefs.h
*
*  Description: Definitions and Parameters for sgx3DsfmLink rendering layout used
*               in 3D Perception (SfM) demo
*
* *******************************************************************************/

#ifndef __SGX_3D_SFM_DEFS_H
#define __SGX_3D_SFM_DEFS_H

#include "sgxRender3DsfmUtils.h"

/*LAYOUT/VIEW PARAMETERS*/
/***********************/
/*Layout Options (turn on/off)*/
//#define ENABLE_CAR_ROI_BOX /*uncomment to enable a car ROI in map view*/
//#define ENABLE_BILLBOARDS  /*uncomment to show billboards on top of boxes*/
#define ENABLE_DISTANCE_INFO /*uncomment to show distance info on top of boxes*/

/*Render view parameters
 * refer to srv_coords_t struct for details */
#define SFM_DISP_EGOVIEW_PARAM_0 (0.0f)
#define SFM_DISP_EGOVIEW_PARAM_1 (20.0f)
#define SFM_DISP_EGOVIEW_PARAM_2 (520.0f)
#define SFM_DISP_EGOVIEW_PARAM_3 (0.0f)
#define SFM_DISP_EGOVIEW_PARAM_4 (-1232.0f)
#define SFM_DISP_EGOVIEW_PARAM_5 (-9856.0f)
#define SFM_DISP_EGOVIEW_PARAM_6 (-0.85f)
#define SFM_DISP_EGOVIEW_PARAM_7 (-0.0f)
#define SFM_DISP_EGOVIEW_PARAM_8 (1.5708f)

/*Ego (Center) View*/
#define SFM_DISP_EGOVIEW_ASPECT_RATIO_INV (0.7f) /*aspect ratio of view port*/

/*World Map View*/
#define SFM_DISP_WORLDMAP_VIEW_DISTANCE (300) /*camera distance*/
#define SFM_DISP_WORLDMAP_SCALE (0.7f) /*scale*/
/*limits of the world map */
#define SFM_DISP_WORLDMAP_LIMIT_XMIN (-900 -900 -150)
#define SFM_DISP_WORLDMAP_LIMIT_XMAX ( 900 +900 +150)
#define SFM_DISP_WORLDMAP_LIMIT_YMIN (-500 -1500 -250)
#define SFM_DISP_WORLDMAP_LIMIT_YMAX ( 2500 + 600 + 50)

/*Object Boxes*/
#define MAX_BOXES SFM_MAP_NUM_BOXES_LIMIT /*maximum number of boxes supported*/
#define BOXES_COLOR_R (1.0f) /*red channel*/
#define BOXES_COLOR_G (0.0f) /*green channel*/
#define BOXES_COLOR_B (0.0f) /*blue channel*/

/*Mesh*/
#define SFM_DISP_MESH_CELL_WIDTH_X (300) /*in mm*/
#define SFM_DISP_MESH_CELL_WIDTH_Y (300) /*in mm*/
#define MESH_COLOR_R (0.0f) /*red channel*/
#define MESH_COLOR_G (0.52f) /*green channel*/
#define MESH_COLOR_B (0.74f) /*blue channel*/

/*Free Space Tiles*/
#define FREE_SPACE_ROI_RADIUS (800) /*radius (mm) in which tiles are marked as free (if not occupied)*/
#define FREE_SPACE_COLOR_R (0.2f) /*red channel*/
#define FREE_SPACE_COLOR_G (1.0f) /*green channel*/
#define FREE_SPACE_COLOR_B (0.2f) /*blue channel*/

/*Car Model Box (for world map)*/
#define SFM_DISP_CAR_BOX_HALF_WIDTH (100) /*in mm*/
#define SFM_DISP_CAR_BOX_HALF_HEIGHT (200) /*in mm*/
#define SFM_DISP_CAR_BOX_GRAY_LEVEL (0.6f) /*gray level: 0 black, 1: white*/

/*Legend*/
#define SFM_DISP_LEGEND_SQUARE_WIDTH (40.0f) /*size of square*/
#define SFM_DISP_LEGEND_OFFSETX1 (-400.0f) /*offset in x for free space label*/
#define SFM_DISP_LEGEND_OFFSETX2 ( 60.0f)  /*offset in x for occupied space label*/
#define SFM_DISP_LEGEND_OFFSETY (-30.0f)   /*offset in y for both*/

/*Billboard/Infos on top of boxes*/
#define SFM_DISP_BILLBOARD_HALF_WIDTH (50) /*size of billboard in mm*/
#define SFM_DISP_BILLBOARD_OFFSET_Z (0)    /*height offset of billboard from top of box*/

/*DEPENDENT PARAMETERS*/
/**********************/
#define SFM_DISP_WORDLMAP_ASPECT_RATIO ((float)(SFM_DISP_WORLDMAP_LIMIT_XMAX-SFM_DISP_WORLDMAP_LIMIT_XMIN)/ \
		                                (float)(SFM_DISP_WORLDMAP_LIMIT_YMAX-SFM_DISP_WORLDMAP_LIMIT_YMIN))

#define SFM_DISP_MESH_MAX_NUM_LINES ((SFM_DISP_WORLDMAP_LIMIT_XMAX-SFM_DISP_WORLDMAP_LIMIT_XMIN)/SFM_DISP_MESH_CELL_WIDTH_X + \
									 (SFM_DISP_WORLDMAP_LIMIT_YMAX-SFM_DISP_WORLDMAP_LIMIT_YMIN)/SFM_DISP_MESH_CELL_WIDTH_Y + 4)

#define SFM_DISP_MAX_NUM_FREE_TILES ((SFM_DISP_MESH_MAX_NUM_LINES+1) * (SFM_DISP_MESH_MAX_NUM_LINES+1))

#endif /* __SGX_3D_SFM_DEFS_H    */
