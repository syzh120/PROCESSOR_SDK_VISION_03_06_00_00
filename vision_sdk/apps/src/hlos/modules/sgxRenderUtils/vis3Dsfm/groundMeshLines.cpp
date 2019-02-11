/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#include "groundMeshLines.h"

/*VBOs*/
static GLuint groundmesh_vbo[1];
static GLuint groundmesh_index_vbo[1];
static GLuint freetiles_vbo[1];
static GLuint freetiles_index_vbo[1];
static GLuint carbox_vbo[1];
static GLuint carbox_index_vbo[2];

/*variables across functions*/
static UInt32 numMeshLinesGlobal;

/*Defines*/
#ifndef MAX
#define MAX(X,Y) (((X)>(Y))?(X):(Y))
#endif
#ifndef MIN
#define MIN(X,Y) (((X)<(Y))?(X):(Y))
#endif

#define SFM_DISP_FREE_TILE_SHRINK_MARGIN (10.0f) /*shrink free tile to avoid overlap with mesh lines*/
#define SFM_DISP_FREE_TILE_Z_SHIFT (2.0f) /*shift free tile up to avoid overlap with mesh lines*/

int groundMeshLines_init()
{
    glGenBuffers(1, groundmesh_vbo);
    glGenBuffers(1, groundmesh_index_vbo);

    glGenBuffers(1, freetiles_vbo);
    glGenBuffers(1, freetiles_index_vbo);

    glGenBuffers(1, carbox_vbo);
    glGenBuffers(2, carbox_index_vbo);

    UInt32 ii;

    GLushort groundmesh_indices[2*SFM_DISP_MESH_MAX_NUM_LINES];
	for (ii=0; ii<2*SFM_DISP_MESH_MAX_NUM_LINES; ii++)
	{
		groundmesh_indices[ii] = ii;
	}

    GLushort freetiles_indices[4*SFM_DISP_MAX_NUM_FREE_TILES];
	GLushort freetiles_indices_single[]={0,1,3,2};
	for (ii=0; ii<4*SFM_DISP_MAX_NUM_FREE_TILES; ii++)
	{
		freetiles_indices[ii] = 4*(ii/4) + freetiles_indices_single[ii%4];
	}

    GLushort carbox_indices_surface[] = {0,1,2,3};
    GLushort carbox_indices_edge[] = {0,1,3,2,0};

    /*buffer data*/
    float meshLines[SFM_DISP_MESH_MAX_NUM_LINES][6]; /*[x1, y1,z1, x2, y2, z2]*/
	numMeshLinesGlobal = getGlobalMeshLines(meshLines);
	glBindBuffer(GL_ARRAY_BUFFER, groundmesh_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 6*numMeshLinesGlobal*sizeof(float), (void *)meshLines[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, freetiles_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 4*3*SFM_DISP_MAX_NUM_FREE_TILES*sizeof(float), (void *)0, GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, carbox_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 3*4*sizeof(float), (void *)0, GL_STREAM_DRAW);

	/*index data*/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundmesh_index_vbo[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(groundmesh_indices), groundmesh_indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, freetiles_index_vbo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(freetiles_indices), freetiles_indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, carbox_index_vbo[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(carbox_indices_surface), carbox_indices_surface, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, carbox_index_vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(carbox_indices_edge), carbox_indices_edge, GL_STATIC_DRAW);

    return 0;
}


/*=======================================================================
*
* Name:        void groundMeshLines_draw(Pose3D_f *systemPose_ewInPtr,
			ObjectBox *boxesInPtr, UInt8 bTileFree[], int viewID)
*
* Description: draw mesh lines, free tiles & car box (world view only)
*
=======================================================================*/
void groundMeshLines_draw(SgxRender3DsfmSharedObj *pObj, Pose3D_f *systemPose_ewInPtr, ObjectBox *boxesInPtr, UInt8 bTileFree[], int viewID)
{
	glm::mat4 mMVP_gml;

	/*compute free tiles*/
	float freeTiles[SFM_DISP_MAX_NUM_FREE_TILES][12];
	UInt32 numFreeTiles;
	numFreeTiles = getFreeTiles(bTileFree,systemPose_ewInPtr, 1, freeTiles);

	/*convert egopose to GL format*/
	if (viewID == 0)
	{
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(SGXRENDER3DSFM_GRID_CELL_SIZE_INV, SGXRENDER3DSFM_GRID_CELL_SIZE_INV, SGXRENDER3DSFM_GRID_CELL_SIZE_INV));
		Pose3D_f * pose = systemPose_ewInPtr;
		float m[16] = {(float)pose->R.xx, (float)pose->R.yx, (float)pose->R.zx, 0,
						(float)pose->R.xy, (float)pose->R.yy, (float)pose->R.zy, 0,
						(float)pose->R.xz, (float)pose->R.yz, (float)pose->R.zz, 0,
						(float)pose->t.x, (float)pose->t.y, (float)pose->t.z, 1};

		glm::mat4 mModel_box = glm::make_mat4(m);
		mMVP_gml = pObj->mProjection * pObj->mView * scale *mModel_box ;
	}
	else
	{
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(SFM_DISP_WORLDMAP_SCALE, SFM_DISP_WORLDMAP_SCALE, SFM_DISP_WORLDMAP_SCALE));
		glm::mat4 mProjection2 =glm::ortho(-2000.0f*SFM_DISP_WORDLMAP_ASPECT_RATIO, 2000.0f*SFM_DISP_WORDLMAP_ASPECT_RATIO, -2000.0f, 2000.0f, 1.0f, 1000.0f);
		glm::mat4 mView2 = glm::lookAt(
								glm::vec3(0, 0, SFM_DISP_WORLDMAP_VIEW_DISTANCE), // Camera is at (4,3,3), in World Space
							    glm::vec3(0, 0, 0), // and looks at the origin
								glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
									  );
		mMVP_gml = mProjection2*mView2 * scale;
	}

	/*render*/
	UInt32 ii;
	glUseProgram(pObj->points_program);
	GL_CHECK(glUseProgram);

	glUniformMatrix4fv(pObj->points_mvMatrixOffsetLoc, 1, GL_FALSE, &mMVP_gml[0][0]);

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*TILES*/
	/******************/
	if (numFreeTiles>0)
	{
		glUniform4f(pObj->colorLoc, FREE_SPACE_COLOR_R, FREE_SPACE_COLOR_G, FREE_SPACE_COLOR_B, 0.3f); //color

		glBindBuffer(GL_ARRAY_BUFFER, freetiles_vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 12*numFreeTiles*sizeof(float), (void *)freeTiles[0]);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, freetiles_index_vbo[0]);

		glVertexAttribPointer(pObj->vertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(pObj->vertexAttribPosition);

		for (ii=0; ii<numFreeTiles; ii++)
		{
			glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (void*)(4 * ii * sizeof(GLushort)));
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	/*MESHLINES*/
	/******************/
	if (numMeshLinesGlobal>0)
	{
		if (viewID==0)
			glLineWidth(5.0f);
		else
			glLineWidth(2.0f);
		glUniform4f(pObj->colorLoc, MESH_COLOR_R, MESH_COLOR_G, MESH_COLOR_B, 1.0f);

		glBindBuffer(GL_ARRAY_BUFFER, groundmesh_vbo[0]);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundmesh_index_vbo[0]);

		glVertexAttribPointer(pObj->vertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(pObj->vertexAttribPosition);

		for (ii=0; ii<numMeshLinesGlobal; ii++)
		{
			glDrawElements(GL_LINE_LOOP, 2, GL_UNSIGNED_SHORT,  (void*)(2 * ii * sizeof(GLushort)));
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	/*CAR BOX*/
	/******************/
	float carBoxHalfWidth;
	float carBoxHalfHeight;
	Point3D_f carBoxVert_e[4];
	Point3D_f tmp;
    float carBoxVertices[4][3];
    Pose3D_f pose_we;

	if (viewID==1)
	{
		carBoxHalfWidth = (float)SFM_DISP_CAR_BOX_HALF_WIDTH;
		carBoxHalfHeight= (float)SFM_DISP_CAR_BOX_HALF_HEIGHT;
        carBoxVert_e[0].x = -carBoxHalfWidth;  carBoxVert_e[0].y = -carBoxHalfHeight; carBoxVert_e[0].z = 0.0f;
        carBoxVert_e[1].x =  carBoxHalfWidth;  carBoxVert_e[1].y = -carBoxHalfHeight; carBoxVert_e[0].z = 0.0f;
        carBoxVert_e[2].x  = -carBoxHalfWidth; carBoxVert_e[2].y =  carBoxHalfHeight; carBoxVert_e[0].z = 0.0f;
        carBoxVert_e[3].x =  carBoxHalfWidth;  carBoxVert_e[3].y =  carBoxHalfHeight; carBoxVert_e[0].z = 0.0f;

        pose3Dinv(systemPose_ewInPtr, &pose_we);
        for (ii=0; ii<4; ii++)
        {
        	pose3Dtransform(&pose_we, &carBoxVert_e[ii], &tmp);
        	carBoxVertices[ii][0] = tmp.x;
        	carBoxVertices[ii][1] = tmp.y;
        	carBoxVertices[ii][2] = 0.0f;
        }

		glBindBuffer(GL_ARRAY_BUFFER, carbox_vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0,3*4*sizeof(float), (void *)carBoxVertices);

		glUniform4f(pObj->colorLoc, SFM_DISP_CAR_BOX_GRAY_LEVEL, SFM_DISP_CAR_BOX_GRAY_LEVEL, SFM_DISP_CAR_BOX_GRAY_LEVEL, 1.0f);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, carbox_index_vbo[0]);
		glVertexAttribPointer(pObj->vertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(pObj->vertexAttribPosition);

		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

#ifdef	ENABLE_CAR_ROI_BOX
	/*CAR BOX ROI*/
	/******************/
	carBoxHalfWidth = SFM_DISP_MESH_CELL_WIDTH_X*3.0f;
	carBoxHalfHeight= SFM_DISP_MESH_CELL_WIDTH_Y*3.0f;
    carBoxVert_e[0].x = -carBoxHalfWidth;  carBoxVert_e[0].y = -carBoxHalfHeight; carBoxVert_e[0].z = 0.0f;
    carBoxVert_e[1].x =  carBoxHalfWidth;  carBoxVert_e[1].y = -carBoxHalfHeight; carBoxVert_e[0].z = 0.0f;
    carBoxVert_e[2].x  = -carBoxHalfWidth; carBoxVert_e[2].y =  carBoxHalfHeight; carBoxVert_e[0].z = 0.0f;
    carBoxVert_e[3].x =  carBoxHalfWidth;  carBoxVert_e[3].y =  carBoxHalfHeight; carBoxVert_e[0].z = 0.0f;

    pose3Dinv(systemPose_ewInPtr, &pose_we);
    for (ii=0; ii<4; ii++)
    {
    	pose3Dtransform(&pose_we, &carBoxVert_e[ii], &tmp);
    	carBoxVertices[ii][0] = tmp.x;
    	carBoxVertices[ii][1] = tmp.y;
    	carBoxVertices[ii][2] = 20.0f;
    }

	glBindBuffer(GL_ARRAY_BUFFER, carbox_vbo[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0,3*4*sizeof(float), (void *)carBoxVertices);

	glUniform4f(pObj->colorLoc, 0.8f, 0.8f, 0.8f, 1.0f);
	if (viewID==0)
		glLineWidth(7.0f);
	else
		glLineWidth(3.0f);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, carbox_index_vbo[1]);
	glVertexAttribPointer(pObj->vertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pObj->vertexAttribPosition);

	glDrawElements(GL_LINE_LOOP, 5, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#endif

	glDisable(GL_BLEND);

	return;
}

/*=======================================================================
*
* Name:        UInt32 getGlobalMeshLines(float meshLines[][6])
*
* Description: compute ground mesh lines in world coordinates
*
=======================================================================*/
UInt32 getGlobalMeshLines(float meshLines[][6])
{
	Int32 ll;
	Int32 xymin, xymax;
	Int32 xyNumLines;

	UInt32 numLines = 0; /*number of meshlines*/
	/*x direction*/
	xymin = ceilf((float)SFM_DISP_WORLDMAP_LIMIT_XMIN/(float)SFM_DISP_MESH_CELL_WIDTH_X);
	xymax = floorf((float)SFM_DISP_WORLDMAP_LIMIT_XMAX/(float)SFM_DISP_MESH_CELL_WIDTH_X);
	xyNumLines = xymax-xymin+1;
	for (ll = 0; ll<xyNumLines; ll++)
	{
		meshLines[numLines][0] = (float)(xymin+ll)*SFM_DISP_MESH_CELL_WIDTH_X;
		meshLines[numLines][1] = SFM_DISP_WORLDMAP_LIMIT_YMIN;
		meshLines[numLines][2] = 0;
		meshLines[numLines][3] = (float)(xymin+ll)*SFM_DISP_MESH_CELL_WIDTH_X;
		meshLines[numLines][4] = SFM_DISP_WORLDMAP_LIMIT_YMAX;
		meshLines[numLines][5] = 0;
		numLines++;
	}

	/*y direction*/
	xymin = ceilf((float)SFM_DISP_WORLDMAP_LIMIT_YMIN/(float)SFM_DISP_MESH_CELL_WIDTH_Y);
	xymax = floorf((float)SFM_DISP_WORLDMAP_LIMIT_YMAX/(float)SFM_DISP_MESH_CELL_WIDTH_Y);
	xyNumLines = xymax-xymin+1;
	for (ll = 0; ll<xyNumLines; ll++)
	{
		meshLines[numLines][0] = SFM_DISP_WORLDMAP_LIMIT_XMIN;
		meshLines[numLines][1] = (float)(xymin+ll)*SFM_DISP_MESH_CELL_WIDTH_Y;
		meshLines[numLines][2] = 0;
		meshLines[numLines][3] = SFM_DISP_WORLDMAP_LIMIT_XMAX;
		meshLines[numLines][4] = (float)(xymin+ll)*SFM_DISP_MESH_CELL_WIDTH_Y;
		meshLines[numLines][5] = 0;
		numLines++;
	}

	return numLines;
}


/*=======================================================================
*
* Name:        updateFreeTiles
*
* Description: compute free ground tiles in world coordinates instantaneously
*
=======================================================================*/
void updateFreeTiles(ObjectBox * boxesPtr, Pose3D_f *systemPose_ew, UInt8 bTileFree[])
{

	/*count number of boxes*/
	Int32 bb;
	Int32 numBoxes = 0;
	for (bb = 0; bb < MAX_BOXES; bb++)
		if (boxesPtr[bb].age > 0)
			numBoxes++;

	/*initializations*/
	float xmin, xmax, ymin, ymax;
	xmin = ceilf((float)SFM_DISP_WORLDMAP_LIMIT_XMIN/(float)SFM_DISP_MESH_CELL_WIDTH_X);
	xmax = floorf((float)SFM_DISP_WORLDMAP_LIMIT_XMAX/(float)SFM_DISP_MESH_CELL_WIDTH_X);
	ymin = ceilf((float)SFM_DISP_WORLDMAP_LIMIT_YMIN/(float)SFM_DISP_MESH_CELL_WIDTH_Y);
	ymax = floorf((float)SFM_DISP_WORLDMAP_LIMIT_YMAX/(float)SFM_DISP_MESH_CELL_WIDTH_Y);
	Int32 widthX = (Int32)(xmax - xmin);
	Int32 widthY = (Int32)(ymax - ymin);

	/*parameters*/
	float ROI_radius_sc = (float)FREE_SPACE_ROI_RADIUS / (float)(MAX(SFM_DISP_MESH_CELL_WIDTH_X, SFM_DISP_MESH_CELL_WIDTH_Y));

	/*system (ego) center w.r.t scaled world coordinates*/
	float centerX, centerY;
	Pose3D_f systemPose_we;
	pose3Dinv(systemPose_ew, &systemPose_we);
	centerX = (float)systemPose_we.t.x / SFM_DISP_MESH_CELL_WIDTH_X;
	centerY = (float)systemPose_we.t.y / SFM_DISP_MESH_CELL_WIDTH_Y;

	/*If there are no boxes, no free tiles*/
	Int32 xx, yy;
	if (numBoxes == 0)
	{
		for (yy = 0; yy < widthY; yy++)
			for (xx = 0; xx < widthX; xx++)
				bTileFree[yy*widthX + xx] = 0;

		return;
	}

	/*Mark all tiles inside radius free*/
	float x, y;
	float diffX, diffY;
	for (yy = 0; yy < widthY; yy++)
	{
		for (xx = 0; xx < widthX; xx++)
		{
			x = xmin + (float)xx + 0.5f;
			y = ymin + (float)yy + 0.5f;
			diffX = x - centerX;
			diffY = y - centerY;
			if (diffX*diffX + diffY*diffY <= ROI_radius_sc * ROI_radius_sc)
				bTileFree[yy*widthX + xx] = 1;
		}
	}

	/*Mark tiles that touch boxes as not free*/
	float x1,y1, x2,y2;
	Int32 numX, numY;
	Int32 xn, yn;
	for (bb = 0; bb < MAX_BOXES; bb++)
	{
		if (boxesPtr[bb].age > 0)
		{
			x1 = floorf((float)(boxesPtr[bb].box.vertex[0].x) / SFM_DISP_MESH_CELL_WIDTH_X);
			y1 = floorf((float)(boxesPtr[bb].box.vertex[0].y) / SFM_DISP_MESH_CELL_WIDTH_Y);
			x2 = ceilf((float)(boxesPtr[bb].box.vertex[2].x) / SFM_DISP_MESH_CELL_WIDTH_X);
			y2 = ceilf((float)(boxesPtr[bb].box.vertex[2].y) / SFM_DISP_MESH_CELL_WIDTH_Y);
			numX = (Int32)(x2-x1);
			numY = (Int32)(y2-y1);
			for (yy=0; yy<numY; yy++)
			{
				for (xx=0; xx<numX; xx++)
				{
					x = x1+(float)xx;
					y = y1+(float)yy;
					if (x >= xmin && x <= xmax && y >= ymin && y <= ymax)
					{
						xn = (Int32)floorf(x-xmin);
						yn = (Int32)floorf(y-ymin);
						bTileFree[yn*widthX + xn] = 0;
					}
				}
			}
		}
	}

	return;
}

/*=======================================================================
*
* Name:        UInt32 getFreeTiles(UInt8 bTileFree[], Pose3D_f *pose_ew,
* 								UInt32 viewID, float freeTiles[][12])
*
* Description: compute free ground tiles in world coordinates
*
=======================================================================*/
UInt32 getFreeTiles(UInt8 bTileFree[], Pose3D_f *pose_ew, UInt32 viewID,
						float freeTiles[][12])
{

	float xmin, xmax, ymin, ymax;
	xmin = ceilf((float)SFM_DISP_WORLDMAP_LIMIT_XMIN/
			(float)SFM_DISP_MESH_CELL_WIDTH_X);
	xmax = floorf((float)SFM_DISP_WORLDMAP_LIMIT_XMAX/
			(float)SFM_DISP_MESH_CELL_WIDTH_X);
	ymin = ceilf((float)SFM_DISP_WORLDMAP_LIMIT_YMIN/
			(float)SFM_DISP_MESH_CELL_WIDTH_Y);
	ymax = floorf((float)SFM_DISP_WORLDMAP_LIMIT_YMAX/
			(float)SFM_DISP_MESH_CELL_WIDTH_Y);
	Int32 widthX = (Int32)(xmax - xmin);
	Int32 widthY = (Int32)(ymax - ymin);

	Int32 xx,yy;
	float x,y;

	UInt32 numFreeTiles=0;

	/*Write free tiles in world coordinates*/
	numFreeTiles = 0;
	for (yy = 0; yy < widthY; yy++)
	{
		for (xx = 0; xx < widthX; xx++)
		{
			if (bTileFree[yy*widthX + xx])
			{
				x = xmin + (float)xx;
				y = ymin + (float)yy;
				freeTiles[numFreeTiles][0] = (x * SFM_DISP_MESH_CELL_WIDTH_X)+SFM_DISP_FREE_TILE_SHRINK_MARGIN;
				freeTiles[numFreeTiles][1] = (y * SFM_DISP_MESH_CELL_WIDTH_Y)+SFM_DISP_FREE_TILE_SHRINK_MARGIN;
				freeTiles[numFreeTiles][2] = -SFM_DISP_FREE_TILE_Z_SHIFT;
				freeTiles[numFreeTiles][3] = ((x+1) * SFM_DISP_MESH_CELL_WIDTH_X)-SFM_DISP_FREE_TILE_SHRINK_MARGIN;
				freeTiles[numFreeTiles][4] = (y * SFM_DISP_MESH_CELL_WIDTH_Y)+SFM_DISP_FREE_TILE_SHRINK_MARGIN;
				freeTiles[numFreeTiles][5] = -SFM_DISP_FREE_TILE_Z_SHIFT;
				freeTiles[numFreeTiles][6] = ((x + 1) * SFM_DISP_MESH_CELL_WIDTH_X)-SFM_DISP_FREE_TILE_SHRINK_MARGIN;
				freeTiles[numFreeTiles][7] = ((y + 1) * SFM_DISP_MESH_CELL_WIDTH_Y)-SFM_DISP_FREE_TILE_SHRINK_MARGIN;
				freeTiles[numFreeTiles][8] = -SFM_DISP_FREE_TILE_Z_SHIFT;
				freeTiles[numFreeTiles][9] = (x * SFM_DISP_MESH_CELL_WIDTH_X)+SFM_DISP_FREE_TILE_SHRINK_MARGIN;
				freeTiles[numFreeTiles][10] = ((y + 1) * SFM_DISP_MESH_CELL_WIDTH_Y)-SFM_DISP_FREE_TILE_SHRINK_MARGIN;
				freeTiles[numFreeTiles][11] = -SFM_DISP_FREE_TILE_Z_SHIFT;
				numFreeTiles++;
			}
			if (numFreeTiles>=SFM_DISP_MAX_NUM_FREE_TILES)
			{
				OSA_assert(0);
			}
		}
	}

	return numFreeTiles;

}



