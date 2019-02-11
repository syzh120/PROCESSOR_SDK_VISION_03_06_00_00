/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef __BOX_H
#define __BOX_H

#include "sgxRender3Dsfm_priv.h"

/*init functions*/
int boxes_init(void);
/*draw functions*/
void boxes_draw(SgxRender3DsfmSharedObj *pObj, float boxes[][24], UInt32 numBoxes, Pose3D_f *pose, int viewID);
void boxes_inputImage_draw(SgxRender3DsfmSharedObj *pObj, float boxes[][24], UInt32 numBoxes, Pose3D_f *poses, UInt32 camNo);
void boxes_legend_draw(SgxRender3DsfmSharedObj *pObj);
/*supporting functions*/
void boxes_projectToInputImage(SgxRender3DsfmSharedObj *pObj, float boxes[][24], UInt32 numBoxes, Pose3D_f *poses, UInt32 camNo, float boxes_projected[][24], UInt32 *numBoxes_projected);
UInt32 project3DPointToImage(SgxRender3DsfmSharedObj *pObj, Point3D_f *xyzc, Point3D_f *xyd);

#endif /* __BOX_H    */
