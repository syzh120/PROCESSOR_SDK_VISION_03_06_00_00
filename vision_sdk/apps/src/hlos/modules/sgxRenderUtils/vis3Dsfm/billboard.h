/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef _BILLBOARD_INCLUDED_

#define _BILLBOARD_INCLUDED_

#include "sgxRender3Dsfm_priv.h"

/*init functions*/
int billboard_init(void);
/*draw functions*/
void billboard_draw(SgxRender3DsfmSharedObj *pObj, float boxes[][24], Point3D_f base[],  UInt32 numBoxes, Pose3D_f *pose_ew, Pose3D_f *poses_cw, GLuint *texYuv);
void distance_info_draw(SgxRender3DsfmSharedObj *pObj, Point3D_f base[],  UInt32 numBoxes, Pose3D_f *pose, float dists[]);
/*supporting functions*/
void getDistancesBetweenBoxesAndCar(ObjectBox boxes[],  UInt32 numBoxes, Pose3D_f *pose_ew, Pose3D_f *pose_ec, float dists[]);
Flouble getDistanceCustom(Point3D_f box_e[], Point3D_f car_e[], Int32 quadrant);
Int32 getZone(Point3D_f p_e, Point3D_f car_e[]);

#endif


