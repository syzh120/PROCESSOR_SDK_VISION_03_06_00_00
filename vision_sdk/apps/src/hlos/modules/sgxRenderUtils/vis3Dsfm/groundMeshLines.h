/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef _GROUND_MESH_LINES_INCLUDED_

#define _GROUND_MESH_LINES_INCLUDED_

#include "sgxRender3Dsfm_priv.h"

/*init functions*/
int groundMeshLines_init(void);
/*draw functions*/
void groundMeshLines_draw(SgxRender3DsfmSharedObj *pObj, Pose3D_f *systemPose_ewInPtr, ObjectBox *boxesInPtr, UInt8 bTileFree[], int viewID);
/*supporting functions*/
UInt32 getGlobalMeshLines(float meshLines[][6]);
void updateFreeTiles(ObjectBox * boxesPtr, Pose3D_f *systemPose_ew, UInt8 bTileFree[]);
UInt32 getFreeTiles(UInt8 bTileFree[], Pose3D_f *pose_ew, UInt32 viewID, float freeTiles[][12]);

#endif


